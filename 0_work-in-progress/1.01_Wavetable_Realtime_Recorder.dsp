// ---------------------------------------------------------------------------------
declare name        "Realtime Recorder";
declare version     "1.0";
declare author      "Luca Spanedda";

/*
Oscillator from wave-table recording
*/

// import Standard Faust library
// https://github.com/grame-cncm/faustlibraries/
import("stdfaust.lib");

// GUI
freqgui = hslider("[1] Frequency",1,0,2,0.001) : si.smoo;
ampgui = hslider("[2] Amp",1,0,2,0.001) : si.smoo;
buttongui = button("[0] Rec");

// WAVETABLE RECORDER
looptable(recstart,freq) = _*buttongui : rwtable(dimension,0.0,indexwrite,_,indexread)
with{
offset = 2 : int; // Offset for write and read. For point the write index at 0 when stopped.
record = recstart : int; // record the memory with the int value of 1
dimension = 1024+offset : int; // dimension in samples the memory table
decimal(x)= x-int(x); // rescale the int (for the phasor)
phasor = ((ma.SR/dimension)/ma.SR)*freq : (+ : decimal)~ _; // phasor from 0 to 1
indexwrite = ((phasor*recstart)*(dimension-offset)):_+offset*recstart :int; // write the input 
indexread =  ((phasor)*(dimension-offset)):_+offset :int; // read the written signal+offset
};

wavetable = _ : looptable(buttongui,freqgui)*ampgui; // routing of the GUI
process = wavetable <: _,_;

// ---------------------------------------------------------------------------------
