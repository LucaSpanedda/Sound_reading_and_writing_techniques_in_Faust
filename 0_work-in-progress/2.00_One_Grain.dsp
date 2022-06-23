// ---------------------------------------------------------------------------------

/*
ONE GRAIN:
FIXED READER PHASOR with 
Frequency Variable Noise - for change READING position,
same Frequency of the Noise for ENVELOPE Window.
ON A FIXED TABLE OF 1 SECOND (TAPE).
*/

// import Standard Faust library
// https://github.com/grame-cncm/faustlibraries/
import("stdfaust.lib");


// ONEGRAIN max. lenght 1 second for every sample rate
onegrain(reconoff,fnoise,fphasor,seed,powwindow,amprec) = 
rwtable(dimension,0.0,indexwrite,_,indexread) * (window*amprec)
with{
    // noise variable in frequency
    varnoise = ((seed) : (+ @(ma.SR/fnoise)~ *(1103515245)))/2147483647.0;
    // window envelope generation (same frequency of the noise)
    decimale(step)= step-int(step);
    fasore = (fnoise/ma.SR) : (+ : decimale) ~ _;
    window = sin(fasore* ma.PI) : pow(powwindow);
    // phasor scattering with jump based on noise
    scatteringphasor = (fphasor/float(ma.SR)) : (+ : ma.decimal)~ 
    (-(_<:(_,*(_,varnoise-varnoise@(1)))):+(varnoise-varnoise@(1)));

        // recorder (rwtable)
        record = reconoff : int; 
        dimension = 192000;
        indexwrite = (+(1) : %(ma.SR : int)) ~ *(record);
        indexread = scatteringphasor : *(float(ma.SR)) : int;
    };

// onegrain(reconoff,fnoise,fphasor,seed,powwindow,amprec)
process = onegrain(1,10,1,1657932344,10,1) <: _,_;

// ---------------------------------------------------------------------------------
