declare name "Timestretching Overlap Add to One";
declare version "xxx";
declare author "Luca Spanedda";
declare license "GNU-GPL-v3";
declare copyright "(c)Luca Spanedda 2022";
declare description "Overlap Add to One Timestretcher";

// import Reand and Write lib
import("RaW.lib");

wrap(x) = x-int(x);
stretch = LetrecPhasor(1-hslider("[7]Stretch Factor", 0, 0, 1, .001))
    * hslider("[5]Read Section", 0, 0, 1, .001);
jitter = no.noise*hslider("[6]Read Jitter", 0, 0, 1, .001);
cntrlRead = hslider("[4]Read Position", 0, 0, 1, .001)+stretch+jitter : wrap;

// Timestretcher - sum of the 2 Head Reads
timeStretcher(bufPos, x) = x <: head1 + head2 <: _,_, rIdxgraph, wIdxgraph
with{
    offset = 2;
    // tableMax = table Max Dimension - 10 Seconds
    tableMax = 192000 * 10 + offset;
    // L = buffer dimension in seconds
    L = ma.SR * hslider("[2]Table Dimension[unit:Sec]", 1, 1, 10, 1);
    // Write index - ramp 0 to L
    wIdx = offset + ((+(1) : %(L)) ~ _) * checkbox("[3]Record") : int;
    buffer(p, x) = it.frwtable(3, tableMax, .0, wIdx, x, p);
    // Hanning window Equation
    hann(x) = sin(ma.frac(x) * ma.PI) ^ 2.0;
    // Grain in Milliseconds
    grainms = 1000/hslider("[8]Grain Dimension[unit:ms.]", 80, 1, 1000, 1) : si.smoo;
    // stretchFactor - 0 Normal / 1 Extreme stretch (Freeze)
    stretchFactor = (ma.SR / L) * (1-hslider("[9]Stretch Factor", 0, 0, 1, .001)) : si.smoo;
    // Position of the grain in the Buffer
    timePhase = offset + (bufPos * L);
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
    rIdxgraph = bufPos : hbargraph("[1]Read Head",0,1) : _*ma.EPSILON; 
};


process = timeStretcher(cntrlRead);
