declare name "Timestretching Overlap Add to One";
declare version "xxx";
declare author "Luca Spanedda";
declare license "GNU-GPL-v3";
declare copyright "(c)Luca Spanedda 2022";
declare description "Overlap Add to One Timestretcher";

// import Reand and Write lib
import("RaW.lib");

// Timestretching via Overlap Add Method

offsetSamp = 2;
// tableMax = table Max Dimension - 10 Seconds
tableMax = 192000 * 10 + offsetSamp;
// L = buffer dimension in seconds
L = ma.SR * (hslider("[3]Table[unit:Sec]", 1, 1, 10, 1)); 
// Write index - ramp 0 to L
wIdx = (offsetSamp+((+(1) : %(L)) ~ _ )) * checkbox("[2]Record") : int;
buffer(p, x) = it.frwtable(3, tableMax, .0, wIdx, x, p);
// Hanning window Equation
hann(x) = sin(ma.frac(x) * ma.PI) ^ 2.0;
// Grain in Ms.
grainms = 1000/(hslider("[4]Grain[unit:ms.]", 80, 1, 1000, 1) : si.smoo);
// stretchFactor - 0 Normal / 1 Extreme stretch (Freeze)
stretchFactor = (ma.SR / L) * (1-hslider("[5]Stretch Factor", 0, 0, 1, .001)) : si.smoo;
// Jitter Amount in the position for the reads
jitter = hslider("[6]Jitter", 0, 0, 1, .001) : si.smoo;
// Position of the grain in the Buffer
timePhase = offsetSamp+(RaW.LetrecPhasor(stretchFactor) * ((1 - jitter) + no.noise * jitter) *L);

// two Heads for the read
// 0°
ph1 = RaW.LetrecPhasor(grainms);
// 180*
ph2 = ma.frac(.5 + ph1);
// Buffer positions = Position in the Buffer + Grain Read
pos1 = RaW.SAH(ph1 < ph1', timePhase) + ph1*(ma.SR/grainms);
pos2 = RaW.SAH(ph2 < ph2', timePhase) + ph2*(ma.SR/grainms);
// Windows + Buffer Reads
head1 = hann(ph1) * buffer(pos1);
head2 = hann(ph2) * buffer(pos2);

wIdxgraph = (wIdx/L) : hbargraph("[0]Write Head",0,1) : _*ma.EPSILON;
rIdxgraph = RaW.LetrecPhasor(stretchFactor) * ((1 - jitter) + no.noise * jitter) 
    : hbargraph("[1]Read Head",0,1) : _*ma.EPSILON; 
// Timestretcher - sum of the 2 Head Reads
timeStretcher(x) = (x <: head1 + head2);

process = timeStretcher <: _,_, rIdxgraph, wIdxgraph;
