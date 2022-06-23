// ---------------------------------------------------------------------------------

// import Standard Faust library
// https://github.com/grame-cncm/faustlibraries/
import("stdfaust.lib");

/*
GLITCHER READER:
WRITING AND READING WITH AN ENVELOPE
ON A FIXED TABLE OF 1 SECOND (TAPE)
*/


// GLITCHER max. lenght 1 second for every sample rate
glitcher(recstart,seed,f,fb) = 
rwtable(dimension,0.0,indexwrite,_,indexread)
    with{   

            clicks(seed,f,fb) = phase
            with{
            varnoise = (((seed) : (+ @(ma.SR/f)~ *(1103515245)))/2147483647.0);
            routeimpulse(a,b) = a : mem, b :> - : _ > 0;
            noisemaj = varnoise>0;
            majimpulse = noisemaj <: routeimpulse;
            imphasor = majimpulse : -~(_ : *(fb));
            decimale(x)= x-int(x);
            phase = (imphasor : decimale) + 1;
            };

    record = recstart : int; 
    dimension = 192000;
    indexwrite = (+(1) : %(ma.SR : int)) ~ *(record);
    indexread = clicks(seed,f,fb) : *(float(ma.SR)) : int;
    };


//glitcher(recstart,seed,f,fb)
process = glitcher(1,100,10,0.998), glitcher(1,120,10,0.998);

// ---------------------------------------------------------------------------------
