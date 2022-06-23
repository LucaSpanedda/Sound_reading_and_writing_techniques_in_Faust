// FAUST standard library
import("stdfaust.lib");

/* 
Granular Sampling - 
version with - Overlap Add To One - Granulator 
for:
Agostino Di Scipio - AUDIBLE ECOSYSTEMICS
n.2a / Feedback Study (2003)
n.2b / Feedback Study, sound installation (2004).
*/

/*
- mem.pointer is the pointer to the next location in the memory
    buffer; in the present notation, it varies between -1 (beginning
    of buffer) and 1 (end of buffer)
- mem.pointer : timeIndex1 - a signal between -1 and -0.5

- mem.pointer.jitter is a random deviation of the current
    mem.pointer value; any viable method can be used to
    calculate the current actual value of mem.pointer
- mem.pointer.jitter: (1 - memWriteDel1) / 100

- memWriteDel1 = a signal between 0 and 1

- grain.duration: 0.023 + ((1 - memWriteDel1) / 21) s

- grain.dur.jitter is a random deviation of the current
    grain.duration value: the current actual grain duration =
    grain.duration + (rnd ⋅ grain.dur.jitter(0.1) ⋅ grain.duration) 
- with rnd = random value in the interval [-1, 1]
- grain.dur.jitter: 0.1 - constant value

- density: cntrlLev: a signal between 0 and 1 (1 max, 0 no grains)
*/

// -------- DEMO SIGNALS -------------

// var1 distance (in meters) between the two farthest removed loudspeakers
var1 = 3;
// timeIndex1 - a signal between -1 and -0.5
timeIndex1 = ( ((os.osc(63.845682)+1)/2) -2)*0.5;
// memWriteDel1 = a signal between 0 and 1
memWriteDel1 = (1 - (((os.osc(32.245682)+1)/2)^2) );
// memWriteDel1 = a signal between 0 and 1
cntrlLev1 = (os.osc(1.445682)+1)/2;

// -------- GRANULAR SAMPLING -------- 

granular_sampling(bufferDim,timeIndex,memWriteDel,cntrlLev,x) = x <: head1 + head2
    with{

        // Receive AE Controls
        mempointer = ((timeIndex+1)/2)*L;
        mempointerjitter = (1-memWriteDel)/100;
        grainduration = (0.023+((1 - memWriteDel)/21)); //sec.
        graindurjitter = 0.1;
        density = cntrlLev;

        // L = buffer dimension in seconds
        L = ma.SR*bufferDim; 
        // tableMax = table Max Dimension
        tableMax = 192000*bufferDim;
        // Write index - ramp 0 to L
        wIdx = (+(1) : %(L)) ~ _ : int;
        buffer(p, x) = it.frwtable(3, tableMax, .0, wIdx, x, p);
        // Hanning window Equation
        hann(x) = sin(ma.frac(x) * ma.PI) ^ 2.0;
        // noise generation for this instance
        iNoise = no.noise;
        // Position of the grain in the Buffer
        timePhase = (mempointer)+((iNoise*mempointerjitter)*L);
        fixedDimension = ma.SR/10;
        frequency = ma.SR/(fixedDimension);
        // two Heads for the read
        // 0°
        ph1 = os.phasor(1, frequency);
        // 180*
        ph2 = ma.frac(.5 + ph1);
        // Buffer positions = Position in the Buffer + Grain Read
        pos1 = ba.sAndH(ph1 < ph1', timePhase) + ph1*(fixedDimension);
        pos2 = ba.sAndH(ph2 < ph2', timePhase) + ph2*(fixedDimension);
        // Noises of this Instance
        iNoise1 = ba.sAndH(ph1 < ph1', iNoise);
        iNoise2 = ba.sAndH(ph2 < ph2', iNoise);
        // variableDimension = grain.duration(variable) + grain.dur.jitter
        graindurjitterfunc = (grainduration*1000)*(iNoise1*graindurjitter);
        variableDimension1(x) = x*((1+(grainduration*1000))+(graindurjitterfunc)) : min(1);
        variableDimension2(x) = x*((1+(grainduration*1000))+(graindurjitterfunc)) : min(1);
        head1 = hann(ph1: variableDimension1) * buffer(pos1);
        head2 = hann(ph2: variableDimension2) * buffer(pos2);
    };

process = granular_sampling(var1,timeIndex1,memWriteDel1,cntrlLev1) <: _,_;
