import("stdfaust.lib");


// buffer(p, x) = de.fdelay(L * ma.SR, p, x);
wIdx = ba.period(L);
buffer(p, x) = it.frwtable(3, L, .0, wIdx, x, p);
hann(x) = sin(ma.frac(x) * ma.PI) ^ 2.0;
grainRate = hslider("grain rate", 50, 10, 100, 1) : si.smoo;
// timeFactor = 1 - hslider("factor", 1, .125, 8.0, .001);
timeFactor = (ma.SR / L) * hslider("factor", 1, .125, 8.0, .001) : si.smoo;
// timePhase = os.phasor(L * ma.SR, (1.0 / L) * timeFactor);
jitter = hslider("jitter", 0, 0, 1, .001) : si.smoo;
timePhase = os.phasor(L, timeFactor) * ((1 - jitter) + no.noise * jitter);
ph1 = os.phasor(1, grainRate);
ph2 = ma.frac(.5 + ph1);
pos1 = ba.sAndH(ph1 < ph1', timePhase) + ph1 * (ma.SR / grainRate);
pos2 = ba.sAndH(ph2 < ph2', timePhase) + ph2 * (ma.SR / grainRate);
head1 = hann(ph1) * buffer(pos1);
head2 = hann(ph2) * buffer(pos2);
L = 48000 * 3; // seconds
timeStretcher(x) = (x <: head1 + head2) <: _ , _;
rIdx = timePhase;

process = timeStretcher;
