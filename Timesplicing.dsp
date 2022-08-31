// import Standard Faust library
// https://github.com/grame-cncm/faustlibraries/
import("stdfaust.lib");


/*
TIME SPLICING:
WRITING AND READING WITH SCATTERING
ON A FIXED TABLE OF 1 SECOND (TAPE)
*/


// 16 Primes Numbers List
somePrimes = (10487, 10499, 10501, 10513, 10529, 10531, 10559, 10567, 
              10589, 10597, 10601, 10607, 10613, 10627, 10631, 10639);
// index of the somePrimes numbers
primeI(index) = ba.take(index , list)
  with{
    list = somePrimes;
};
// only decimal pass
decimal(x) = x-int(x); 
// only integer pass
integer(x) = int(x);
// pole inverter
poleinv(x) = abs(x*-1);
// binary selector 0 - 1
selector(sel,x,y) = ( x * (1-sel) + y * (sel) );
// noise with prime numbers
noise(seed) = ((+(primeI(seed))~ * (1103515245)) / 2147483647);

phsplice(seed) = ph, phTrigInv(fT), phTrig(fT)
    with{
        ph = (f/ma.SR): ( + : 
                            \(x).(
                                 selector(  phTrig(fT),
                                            x,
                                            SAHnoise(phTrigInv(fT))
                                         ) 
                                 ) 
                            
                            : decimal ) ~ _;
        phTrig(f) = f/ma.SR : (+  : decimal)~_ : \(x).(x-(1-dim) > 0);
        phTrigInv(f) = phTrig(f) : \(x).( (x*-1) + 1 );
        ABSnoise = abs(noise(seed));
        SAHnoise(x) = \(fb).(selector((x < x'),fb,ABSnoise))~_;
        dim = hslider("scatter dimension",0,0,1,.001);
        fT = hslider("scatter frequency",0,0,100,.001);
        f = 1;
};
// TAPE-SPLICER max. lenght 1 second for every sample rate
tapesplicer(phspliceIN, silence, x) = rwtable( dimension,
                                  0.0,
                                  indexwrite,
                                  x,
                                  indexread) * (phspliceIN : !,_,!)
                                             + (phspliceIN : !,!,_) * silence
    with{
        rec = 1-checkbox("freeze") : int; 
        dimension = 192000;
        indexwrite = (+(1) : %(ma.SR : int)) ~ *(rec);
        indexread = (phspliceIN : _,!,!) : *(float(ma.SR)) : int;
    };

process = _ <: tapesplicer( phsplice(1), 0 ),
               tapesplicer( phsplice(2), 0 );
