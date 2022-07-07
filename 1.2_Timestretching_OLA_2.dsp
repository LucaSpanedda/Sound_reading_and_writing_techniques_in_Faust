declare name        "Timestretching_OLA";
declare author      "Luca Spanedda";

// import Reand and Write lib
import("raw.lib");

// Timestretching via Overlap Add Method

offsetSamp = 2;
// tableMax = table Max Dimension - 10 Seconds
tableMax = 192000 * 10 + offsetSamp;
// L = buffer dimension in seconds
L = ma.SR * (hslider("Table in Seconds", 1, 1, 10, 1)); 
// Write index - ramp 0 to L
wIdx = (offsetSamp+((+(1) : %(L)) ~ _ )) * checkbox("Record") : int;
wIdxgraph = (wIdx/L) : hbargraph("Write Head",0,1);
buffer(p, x) = it.frwtable(3, tableMax, .0, wIdx, x, p);
// Hanning window Equation
hann(x) = sin(ma.frac(x) * ma.PI) ^ 2.0;
// Grain in Ms.
grainms = 1000/(hslider("Grain in ms.", 80, 1, 1000, 1) : si.smoo);
// stretchFactor - 0 Normal / 1 Extreme stretch (Freeze)
stretchFactor = (ma.SR / L) * (1-hslider("Stretch Factor", 0, 0, 1, .001)) : si.smoo;
// Jitter Amount in the position for the reads
jitter = hslider("Jitter", 0, 0, 1, .001) : si.smoo;
// Position of the grain in the Buffer
timePhase = offsetSamp+(raw.LetrecPhasor(stretchFactor) * ((1 - jitter) + no.noise * jitter) * L);
rIdxgraph = raw.LetrecPhasor(stretchFactor) * ((1 - jitter) + no.noise * jitter) 
    : hbargraph("Read Head",0,1);
// two Heads for the read
// 0°
ph1 = raw.LetrecPhasor(grainms);
// 180*
ph2 = ma.frac(.5 + ph1);
// Buffer positions = Position in the Buffer + Grain Read
pos1 = raw.SAH(ph1 < ph1', timePhase) + ph1*(ma.SR/grainms);
pos2 = raw.SAH(ph2 < ph2', timePhase) + ph2*(ma.SR/grainms);
// Windows + Buffer Reads
head1 = hann(ph1) * buffer(pos1);
head2 = hann(ph2) * buffer(pos2);
// Timestretcher - sum of the 2 Head Reads
timeStretcher(x) = (x <: head1 + head2) <: _,_;

process = _ : timeStretcher,rIdxgraph,wIdxgraph;
