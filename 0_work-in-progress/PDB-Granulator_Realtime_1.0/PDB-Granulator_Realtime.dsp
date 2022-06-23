// ---------------------------------------------------------------------------------
declare name        "PDB_Realtime_Granulator";
declare version     "1.0";
declare author      "Luca Spanedda";
declare reference   "http://www.granularsynthesis.com/guide.php";

/*
RTSG - REAL TIME SYNCHRONOUS GRANULATOR with COUNTER:
100 to 100^-1000 Milliseconds grains - with Envelope window shape control.
PDB - ON PARALLEL FIXED TABLES OF 1 SECOND (TAPES): Parallel Data Buffers.
*/

// import Standard Faust library
// https://github.com/grame-cncm/faustlibraries/
import("stdfaust.lib");


// NUMBER OF PDB FOR GRAINS (INSTANCES)
graininstances = 80;


// GUI
ampguiin = hslider("[3] Grains Amp In",1,0,10,0.01) : si.smoo;
windowgui = hslider("[5] Grains Window",1,1,100,0.1) : si.smoo;
ampgui = hslider("[4] Grains Amp Out",1,0,10,0.01) : si.smoo;
freqguiplus = hslider("[7] Grains Freq+",1,1,100,0.1) : si.smoo;
freqguiminus = hslider("[8] Grains Freq/",1,1,100,0.1): si.smoo;
feedbackgui = hslider("[5] Rec Feedback",0,0,10,0.01) : si.smoo;
panningui = hslider("[6] Panning Speed",1,0,4,0.01) : si.smoo;
// COUNTER
buttoncount = os.osc(hslider("[0] Rec Grain",0,0,graininstances,0.1) : int) > 0;
buttontopulse(x)= x <: _,(_:mem) :> - : max(0);
deccountscale(x)= x%(graininstances);
counter = buttoncount : buttontopulse : +~_ : deccountscale+1 
: hbargraph("[2] Rec Grain Instance:[style:numerical]",1,graininstances);


// GRAIN
grain(numbpar,freq,seed,powwindow,amp,panspeed) =
(rwtable(tablesize,0.0,indexwrite,_,indexread)*envelope) <: panning
with{
    // COUNTER
    condpar = (counter == numbpar); // if counter match par then 1
    condmaj = (condpar > 0.5);
    condmin = (condpar < 0.5) : mem;
    diracmatch = condmaj*condmin;
    // GATE (FOR REC) - PEAK HOLD
    peakcond(holdTime, x_) = loop ~ _ // hold the dirac impulse for 1000 ms
            with {loop(pFB) = ba.if(pReset, abs(x_), pFB)
            with {pReset = timerCond | peakCond;
            peakCond = abs(x_) >= pFB;
            timerCond = loop ~ _
            with {loop(tFB) = fi.pole(tReset, tReset) >= (holdTime)
            with {tReset = 1 - (peakCond | tFB);
        };};};};
        partrigger = peakcond(ma.SR, diracmatch); // out 1 for 1 second when match

    rampnoise(frequency,seedx) = phasorout
    with{
    // NOISE GENERATION
    noise  = (+(seedx)~*(1103515245))/2147483647.0;
    // IMPULSE GENERATION
        // reset to 0 when int
        decimal(x)= x-int(x);
    phase = frequency/ma.SR : (+ : decimal) ~ _;
    saw = phase-0.5;
    ifpos = (saw > 0);
    trig = ( ifpos - ( ifpos:mem ) ) > 0;
    // SAH THE NOISE FUNCTION (with the impulse)
    sahrandom = (*(1 - trig) + noise * trig) ~ _;
    sehout = ((sahrandom>0)*2)-1;
    // PHASOR GENERATION
    phasor = (sehout/ma.SR) : (+ : decimal) ~ _;
    // PHASOR TO TRIANGLE
    triconditionpos(x) = (x<0.5)*(x) + ((x>0.5)*((x*-1)+1));
    trifunctionpos(x) = (x>0)*(x) : triconditionpos;
    triconditionneg(x) = (x>-0.5)*(x) + ((x<-0.5)*((x*-1)-1));
    trifunctionneg(x) = (x<0)*(x) : triconditionneg;
    phasorout = phasor <: trifunctionpos,trifunctionneg :> + : _+0.5;
    };
    noisepan = rampnoise(panspeed,seed);

    // NOISE & PHASOR GENERATION
    noise = (((+(seed)~*(1103515245))/2147483647.0)+1)*0.5;  
    decimale(step)=((step)-int(step));
    decorrelation = ((((seed)*(1103515245)/2147483647.0)+1)*0.5)*ma.SR; // rand
    fasore = (((freq*10)/ma.SR):(+:decimale)~ _) : _@(decorrelation);
    // IMPULSE GENERATION
    saw = (fasore*-1)+1;
    phasemaj = (saw > 0.5);
    phasemin = (saw < 0.5) : mem;
    diracphase = phasemaj*phasemin;
    // SAH THE NOISE FUNCTION (with the impulse)
    sahrandom = (*(1 - diracphase) + noise * diracphase) ~ _;
    sehout = (sahrandom +1)/2;

    // READER 
    offset = 2 : int; // Offset for write and read. For point the write index at 0 when stopped.
    recstart = partrigger; // when match the i (par) instance then record
    record = recstart : int; // record the memory with the int value of 1
    tablesize = 192000+offset : int; // dimension in samples of the buffer
    dimension = ma.SR : int; // dimension in samples the memory table 
    indexwrite = (+(1) : %((ma.SR-offset) : int))~ *(record):_+(offset*recstart):int;
    indexread = ((fasore*(dimension*0.1)) + (sehout*(dimension*0.9))):_+offset:int;

    // ENVELOPE & POW
    envelope = ((sin(fasore*ma.PI)):pow(powwindow)*amp); // reder used for env
    panning = _*(noisepan), _*(1-noisepan);
    };

// GRANULATOR: PARALLEL PROCESS OF THE GRAIN FUNCTION
parallelgrains = 
             // granulator (with par on grain function)
             // grain(==numbpar,Hz-read,seed-noise,window-shape(pow),amp)
_ <: par( i, graininstances, grain(i+1,freqguiplus/freqguiminus,219979*(i+1),
windowgui,1/graininstances,panningui) );

// ROUTING
clipz(a,v) = _*a : min(v) : max(-v);
routingranulator(a,b) = (a+b)*feedbackgui, a, b;
routeout(a,b,c) = b*ampgui, c*ampgui;
routegrains =  _*ampguiin : (+ : fi.dcblocker : clipz(1,1) : parallelgrains :> 
routingranulator ) ~ _ : routeout;

process = routegrains;
// ---------------------------------------------------------------------------------
