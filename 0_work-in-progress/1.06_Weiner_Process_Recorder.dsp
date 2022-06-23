// ---------------------------------------------------------------------------------
declare name        "Weiner Process Recorder";
declare version     "1.0";
declare author      "Luca Spanedda";

/*
rwtable with weiner process read
*/

// import Standard Faust library
// https://github.com/grame-cncm/faustlibraries/
import("stdfaust.lib");

// GUI
freqgui = hslider("[1] Read Frequency",1,0,2,0.001) : si.smoo;
walkfreqgui = hslider("[1] Walk Frequency",1,0,40,0.01) : si.smoo;
walkseedgui = hslider("[1] Walk Seed",1,1,100000,1) : si.smoo;
ampgui = hslider("[2] Amp",1,0,2,0.001) : si.smoo;
buttongui = button("[0] Rec");

// import Standard Faust library
// https://github.com/grame-cncm/faustlibraries/
import("stdfaust.lib");


delayline(buttonx,frw,fwalk,wseed) = delaylineout
with{

constrainedwalk(cwalkfreq,cnoisefreq,cnoiseseed) = crwlkout
with{


    randomwalk(walkfreq,noisefreq,noiseseed) = randomwalkout
    with{

        // NOISE GENERATION - function
        noise(seed) = noiseout
        with{  
        noiseout = (+(seed)~*(1103515245))/2147483647.0;
            };


        // SAMPLE AND HOLD - function
        sampleandhold(frequency) = sampleandholdout
        with{
            // PHASOR
            decimal(x)= x-int(x); // reset to 0 when int
            phase = frequency/ma.SR : (+ : decimal) ~ _; // phasor with frequency
            // PHASOR to 0 and 1
            saw = phase-0.5; // phasor : -0.5 to +0.5
            ifpos = (saw > 0); // phasor positive =1; phasor negative =0
            // PHASOR 1 to Impulse
            trainpulse = ( ifpos - ( ifpos:mem ) ) > 0; // impulse and delette all under 0
            // SAMPLE AND HOLD
            sampleandholdout(a) = (*(1 - trainpulse) + a * trainpulse) ~ _;
            };


        
            // SAMPLE AND HOLD THE NOISE: noise ---> sample and hold ---> pos
            sahnoise = noise(noiseseed) : sampleandhold(noisefreq);
            // BINARY NOISE (-1 and +1)
            plusminuscond(a) = (a>0)+(a<0)*-1;
            noisebinary = sahnoise : plusminuscond;
            // PHASOR GENERATION
            randomwalkout = (walkfreq/ma.SR)*noisebinary : + ~ _;
    };


        // CONSTRAINED - function
        wavefolding = constrainedout
        with{
        intreset(x)= x-int(x);
        triconditionpos(x) = (x<0.5)*(x) + ((x>0.5)*((x*-1)+1));
        trifunctionpos(x) = (x>0)*(x) : triconditionpos;
        triconditionneg(x) = (x>-0.5)*(x) + ((x<-0.5)*((x*-1)-1));
        trifunctionneg(x) = (x<0)*(x) : triconditionneg;
        constrainedout = intreset <: trifunctionpos,trifunctionneg :> + : _*2;
        };


crwlkout = randomwalk(cwalkfreq,cnoisefreq,cnoiseseed) : wavefolding : _+1 : _*0.5;

};

// DELAY TABLE
delaytable(recstart,rwfreq,walkfreq,walkseed) = rwtable(tablesize,0.0,indexwrite,_,indexread)
with{
    // READER 
    record = recstart : int; // record the memory with the int value of 1
    tablesize = 192000; // dimension in samples of the buffer
    dimension = ma.SR; // dimension in samples for write/read 
    decimal(x)= x-int(x); // rescale int 
    fasore = ((ma.SR/dimension)/ma.SR)* rwfreq : (+ : decimal)~ _; // signal from 0 to 1
    // write the input signal: fasore*dimension (table)
    indexwrite = ((fasore * dimension) * recstart : int); 
    // read the written signal: randomwalk * dimension (table)
    indexread = ((constrainedwalk(rwfreq,walkfreq,walkseed) * dimension) : int); 
    };


delaylineout = _*buttongui : delaytable(buttonx,frw,fwalk,wseed); 

};


process = 
delayline(buttongui,freqgui,walkfreqgui,24778912),
delayline(buttongui,freqgui,walkfreqgui,89122212);


// ---------------------------------------------------------------------------------
