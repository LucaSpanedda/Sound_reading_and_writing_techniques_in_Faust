// import Standard Faust library
// https://github.com/grame-cncm/faustlibraries/
import("stdfaust.lib");

decimale(x)= x-int(x);

counter(freq) = 
            // RESET at 1: 0.001 = counter reset at 1.000 (1000)
            ((0.001 
            : (+ :decimale@(ma.SR/freq))~ _) 
            // OFFSET (START COUNT FROM 0.001)
            + 0.001) 
            // COUNTER to int again
            * 1000 : int;

process = counter(1) *0; // *0 avoid DC Offset
