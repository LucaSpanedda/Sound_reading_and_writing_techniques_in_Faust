import("stdfaust.lib");

// GRANULATOR Overlap Add To One

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


// tableMax = table Max Dimension
tableMax = 192000 * 3;
// L = buffer dimension in seconds
L = ma.SR * 3; 
// Write index - ramp 0 to L
wIdx = (+(1) : %(L)) ~ _ : int;
buffer(p, x) = it.frwtable(3, tableMax, .0, wIdx, x, p);
// Hanning window Equation
hann(x) = sin(ma.frac(x) * ma.PI) ^ 2.0;
// Grain in Ms.
grainms = 1000/(hslider("[1] Grain in ms.", 80, 1, 1000, 1):si.smoo);
// stretchFactor - 0 Normal / 1 Extreme stretch (Freeze)
stretchFactor = (ma.SR / L) * (1-hslider("[2] Stretch Factor", 0, 0, 1, .001)) : si.smoo;
// Jitter Amount in the position for the reads
jitter = hslider("[3] Jitter", 0, 0, 1, .001) : si.smoo;
// Position of the grain in the Buffer
timePhase = (Phasor(stretchFactor)*L) * ((1 - jitter) + no.noise * jitter);
// two Heads for the read
// 0°
ph1 = Phasor(grainms);
// 180*
ph2 = ma.frac(.5 + ph1);
// Buffer positions = Position in the Buffer + Grain Read
pos1 = SAH2(ph1 < ph1', timePhase) + ph1*(ma.SR/grainms);
pos2 = SAH2(ph2 < ph2', timePhase) + ph2*(ma.SR/grainms);
// Windows + Buffer Reads
head1 = hann(ph1) * buffer(pos1);
head2 = hann(ph2) * buffer(pos2);
// Timestretcher - sum of the 2 Head Reads
timeStretcher(x) = (x <: head1 + head2) <: _,_;

process = timeStretcher;
