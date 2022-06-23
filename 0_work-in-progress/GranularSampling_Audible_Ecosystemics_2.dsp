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
Author NOTES in the Score.

page 5:

- granular sampling = 
read sample sequences off subsequent buffer memory chunks, 
and envelopes the signal chunk with a pseudo-Gaussian envelope curve; ù
the particular implementation should allow for time-stretching ù
(slower memory pointer increments at grain level), 
as well as for "grain density" controls 
and slight random deviations ("jitter") on grain parameters; 
no frequency shift necessary

page 9:

- "grains" are short sequences of samples read off the memory
buffer, enveloped with a pseudo-gaussian function curve

- grain.dur.jitter is a random deviation of the current
grain.duration value: the current actual grain duration =
grain.duration + (rnd ⋅ grain.dur.jitter ⋅ grain.duration), with rnd
= random value in the interval [-1, 1]

- mem.pointer is the pointer to the next location in the memory
buffer; in the present notation, it varies between -1 (beginning
of buffer) and 1 (end of buffer)
mem.pointer.jitter is a random deviation of the current
mem.pointer value; any viable method can be used to
calculate the current actual value of mem.pointer

- density is the average number of sound grains active at any
time (1 = max, 0 = no grains)
*/


/* 
var1 = distance (in meters) between the two farthest removed loudspeakers 
on the left-right axis.
sample write (to mem buffer) looped recording, i.e. 
overwriting samples every var1 seconds
*/

// Buffer Dimension in Seconds
var1 = 3;

// DEMO GUI
// timeIndex1 - Manual control - Buffer position for the read
GUItimeIndex1 = ((hslider("[2]mem.pointer", 0, -1, 1, .001)+1)/2) : si.smoo;
// graindurjitter
GUIgraindurjitter = ((hslider("[1]grain.dur.jitter", -1, -1, 1, .001)+1)/2) : si.smoo;
// Jitter Amount in the position for the reads
GUIjitter = (hslider("[3]mem.pointer.jitter", 0, 0, 100, .001)+1) : si.smoo;
// Fixed grain duration position (change = frequency shift)
GUIfixedGrainMS = hslider("[0]grain.duration", 80, 1, 1000, 1) : si.smoo;

// -------- GRANULAR SAMPLING -------- 

GranularSampling
(var1,timeIndex1,memWriteDel1,fixedGrainMS,fixedgraindurjitter,density,x) = 
(x <: head1 + head2) 
    with{

        // TO DO:
        // grain.duration: 0.023 + ((1 - memWriteDel1) / 21) s 
        // density - adding multiple instances
        // multiple noises with External SEED - change seed in par func.

        // Receive AE Controls
        grainduration = 1000/fixedGrainMS;
        mempointer = timeIndex1;
        mempointerjitter = (1-memWriteDel1)/100;
        graindurjitter = fixedgraindurjitter*100;

        // Sample and Hold Function
        SAH2(trig,x) = loop~_
            with{
                loop(y) = (y,x : select2(trig));
            };
        // Phasor Function 
        Phasor(f) = Xn
            letrec{
                'Xn = (Xn+(f/ma.SR))-int(Xn);
            };

        // Waveshaping - Clipping (for drive the window func)
            Clipping(w) = (w<1)*w+(w>1);

        // tableMax = table Max Dimension
        tableMax = 192000*var1;
        // L = buffer dimension in seconds
        L = ma.SR*var1; 
        // Write index - ramp 0 to L
        wIdx = (+(1) : %(L)) ~ _ : int;
        buffer(p, x) = it.frwtable(3, tableMax, .0, wIdx, x, p);
        // Hanning window Equation
        hann(x) = sin(ma.frac(x) * ma.PI) ^ 2.0;
        // Position of the grain in the Buffer
        timePhase = (mempointer*L) * ((1 - mempointerjitter) + no.noise * mempointerjitter);
        // two Heads for the read
        // 0°
        ph1 = Phasor(grainduration);
        // 180*
        ph2 = ma.frac(.5 + ph1);
        // Buffer positions = Position in the Buffer + Grain Read
        pos1 = SAH2(ph1 < ph1', timePhase) + ph1*(ma.SR/grainduration);
        pos2 = SAH2(ph2 < ph2', timePhase) + ph2*(ma.SR/grainduration);
        // block graindur at new grain start
        posgraindur1 = SAH2(ph1 < ph1', (no.noise*graindurjitter):abs);
        posgraindur2 = SAH2(ph2 < ph2', (no.noise*graindurjitter):abs);
        // Windows in Clipping (for drive the window func) + Buffer Reads
        head1 = hann(ph1*(1+posgraindur1):Clipping) * buffer(pos1);
        head2 = hann(ph2*(1+posgraindur2):Clipping) * buffer(pos2);
    };

process = GranularSampling(var1,GUItimeIndex1,GUIjitter,GUIfixedGrainMS,GUIgraindurjitter,1) 
<: _,_;