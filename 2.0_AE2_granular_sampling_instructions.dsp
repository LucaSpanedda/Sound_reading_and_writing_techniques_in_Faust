// AE Granular Sampling Instructions

/* 
Granular Sampling - 
version with - Overlap Add To One - Granulator 
for:
Agostino Di Scipio - AUDIBLE ECOSYSTEMICS
n.2a / Feedback Study (2003)
n.2b / Feedback Study, sound installation (2004).
*/

/*
- mem.pointer is the pointer to the next location in the memory
    buffer; in the present notation, it varies between -1 (beginning
    of buffer) and 1 (end of buffer)
- mem.pointer : timeIndex1 - a signal between -1 and -0.5

- mem.pointer.jitter is a random deviation of the current
    mem.pointer value; any viable method can be used to
    calculate the current actual value of mem.pointer
- mem.pointer.jitter: (1 - memWriteDel1) / 100

- memWriteDel1 = a signal between 0 and 1

- grain.duration: 0.023 + ((1 - memWriteDel1) / 21) s

- grain.dur.jitter is a random deviation of the current
    grain.duration value: the current actual grain duration =
    grain.duration + (rnd ⋅ grain.dur.jitter(0.1) ⋅ grain.duration) 
- with rnd = random value in the interval [-1, 1]
- grain.dur.jitter: 0.1 - constant value

- density: cntrlLev: a signal between 0 and 1 (1 max, 0 no grains)
*/
