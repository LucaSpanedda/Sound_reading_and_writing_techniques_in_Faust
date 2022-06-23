// ---------------------------------------------------------------------------------

// import Standard Faust library
// https://github.com/grame-cncm/faustlibraries/
import("stdfaust.lib");

// MICRO-TIME SPLICING max. lenght 1 second for every sample rate
microtimesplicing
(reconoff,fnoise,fphasor,seed,sampssplice,amprec,sampsimpulse,ampimpulse) = 
    rwtable(dimension,0.0,indexwrite,_,indexread) 
    * (impulsewindow*amprec) + impulseraw*ampimpulse
with{
    // noise variable in frequency
    varnoise = ((seed) : (+ @(ma.SR/fnoise)~ *(1103515245)))/2147483647.0;
    // impulse generation (same frequency of the noise)
    routeimpulseone(a) = (a-a@( sampssplice )) != 0;
    routeimpulsetwo(a) = (a-a@( sampsimpulse)) != 0;
    impulsewindow = varnoise : routeimpulseone;
    impulseraw =    varnoise : routeimpulsetwo;
    // phasor scattering with jump based on noise
    scatteringphasor = (fphasor/float(ma.SR)) : (+ : ma.decimal)~ 
    (-(_<:(_,*(_,varnoise-varnoise@(1)))):+(varnoise-varnoise@(1)));
    out = scatteringphasor*minzerofive;

        // recorder (rwtable)
        record = reconoff : int; 
        dimension = 192000;
        indexwrite = (+(1) : %(ma.SR : int)) ~ *(record);
        indexread = scatteringphasor : *(float(ma.SR)) : int;
    };

// microtimesplicing
// (reconoff,fnoise,fphasor,seed,sampssplice,amprec,sampsimpulse,ampimpulse)
process = 
microtimesplicing(1,4,1,1657932344,5000,1,3,0.2), 
microtimesplicing(1,4,1,1411931142,5000,1,3,0.2);

// ---------------------------------------------------------------------------------
