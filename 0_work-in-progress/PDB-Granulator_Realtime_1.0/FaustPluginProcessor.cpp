/* ------------------------------------------------------------
author: "Luca Spanedda"
name: "PDB_Realtime_Granulator"
version: "1.0"
Code generated with Faust 2.35.0 (https://faust.grame.fr)
Compilation options: -a /usr/local/share/faust/juce/juce-plugin.cpp -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2016 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

#include <algorithm>
#include <assert.h>

#if JUCE_WINDOWS
#define JUCE_CORE_INCLUDE_NATIVE_HEADERS 1
#endif

#include "JuceLibraryCode/JuceHeader.h"

/************************** BEGIN MapUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>
#include <stdio.h>

/************************** BEGIN UI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct UIReal
{
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
    
    // To be used by LLVM client
    virtual int sizeOfFAUSTFLOAT() { return sizeof(FAUSTFLOAT); }
};

struct UI : public UIReal<FAUSTFLOAT>
{
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string replaceCharList(std::string str, const std::vector<char>& ch1, char ch2)
        {
            std::vector<char>::const_iterator beg = ch1.begin();
            std::vector<char>::const_iterator end = ch1.end();
            for (size_t i = 0; i < str.length(); ++i) {
                if (std::find(beg, end, str[i]) != end) {
                    str[i] = ch2;
                }
            }
            return str;
        }
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::vector<char> rep = {' ', '#', '*', ',', '/', '?', '[', ']', '{', '}', '(', ')'};
            replaceCharList(res, rep, '_');
            return res;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // setParamValue/getParamValue
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            } else {
                fprintf(stderr, "ERROR : setParamValue '%s' not found\n", path.c_str());
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                fprintf(stderr, "ERROR : getParamValue '%s' not found\n", path.c_str());
                return 0;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        std::string getParamAddress(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return "";
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamAddress1(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            for (const auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return "";
        }
    
        FAUSTFLOAT* getParamZone(const std::string& str)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                return fPathZoneMap[str];
            } else if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
                return fLabelZoneMap[str];
            }
            return nullptr;
        }
    
        FAUSTFLOAT* getParamZone(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->second;
            }
        }
    
        static bool endsWith(const std::string& str, const std::string& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
};


#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN base_dsp-adapter.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp_adapter__
#define __dsp_adapter__

#ifndef _WIN32
#include <alloca.h>
#endif
#include <string.h>
#include <cmath>
#include <assert.h>
#include <stdio.h>

/************************** BEGIN base_dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class base_dsp {

    public:

        base_dsp() {}
        virtual ~base_dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Return the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceInit(int sample_rate) = 0;
    
        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual base_dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public base_dsp {

    protected:

        base_dsp* fDSP;

    public:

        decorator_dsp(base_dsp* base_dsp = nullptr):fDSP(base_dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class, used with LLVM and Interpreter backends
 * to create DSP instances from a compiled DSP program.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual base_dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/************************** END base_dsp.h **************************/

// Adapts a DSP for a different number of inputs/outputs
class dsp_adapter : public decorator_dsp {
    
    private:
    
        FAUSTFLOAT** fAdaptedInputs;
        FAUSTFLOAT** fAdaptedOutputs;
        int fHWInputs;
        int fHWOutputs;
        int fBufferSize;
    
        void adaptBuffers(FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int i = 0; i < fHWInputs; i++) {
                fAdaptedInputs[i] = inputs[i];
            }
            for (int i = 0; i < fHWOutputs; i++) {
                fAdaptedOutputs[i] = outputs[i];
            }
        }
    
    public:
    
        dsp_adapter(base_dsp* base_dsp, int hw_inputs, int hw_outputs, int buffer_size):decorator_dsp(base_dsp)
        {
            fHWInputs = hw_inputs;
            fHWOutputs = hw_outputs;
            fBufferSize = buffer_size;
            
            fAdaptedInputs = new FAUSTFLOAT*[base_dsp->getNumInputs()];
            for (int i = 0; i < base_dsp->getNumInputs() - fHWInputs; i++) {
                fAdaptedInputs[i + fHWInputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedInputs[i + fHWInputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
            
            fAdaptedOutputs = new FAUSTFLOAT*[base_dsp->getNumOutputs()];
            for (int i = 0; i < base_dsp->getNumOutputs() - fHWOutputs; i++) {
                fAdaptedOutputs[i + fHWOutputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedOutputs[i + fHWOutputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
        }
    
        virtual ~dsp_adapter()
        {
            for (int i = 0; i < fDSP->getNumInputs() - fHWInputs; i++) {
                delete [] fAdaptedInputs[i + fHWInputs];
            }
            delete [] fAdaptedInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs() - fHWOutputs; i++) {
                delete [] fAdaptedOutputs[i + fHWOutputs];
            }
            delete [] fAdaptedOutputs;
        }
    
        virtual int getNumInputs() { return fHWInputs; }
        virtual int getNumOutputs() { return fHWOutputs; }
    
        virtual dsp_adapter* clone() { return new dsp_adapter(fDSP->clone(), fHWInputs, fHWOutputs, fBufferSize); }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptBuffers(inputs, outputs);
            fDSP->compute(date_usec, count, fAdaptedInputs, fAdaptedOutputs);
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptBuffers(inputs, outputs);
            fDSP->compute(count, fAdaptedInputs, fAdaptedOutputs);
        }
};

// Adapts a DSP for a different sample size
template <typename REAL_INT, typename REAL_EXT>
class dsp_sample_adapter : public decorator_dsp {
    
    private:
    
        REAL_INT** fAdaptedInputs;
        REAL_INT** fAdaptedOutputs;
    
        void adaptInputBuffers(int count, FAUSTFLOAT** inputs)
        {
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    fAdaptedInputs[chan][frame] = REAL_INT(reinterpret_cast<REAL_EXT**>(inputs)[chan][frame]);
                }
            }
        }
    
        void adaptOutputsBuffers(int count, FAUSTFLOAT** outputs)
        {
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    reinterpret_cast<REAL_EXT**>(outputs)[chan][frame] = REAL_EXT(fAdaptedOutputs[chan][frame]);
                }
            }
        }
    
    public:
    
        dsp_sample_adapter(base_dsp* base_dsp):decorator_dsp(base_dsp)
        {
            fAdaptedInputs = new REAL_INT*[base_dsp->getNumInputs()];
            for (int i = 0; i < base_dsp->getNumInputs(); i++) {
                fAdaptedInputs[i] = new REAL_INT[4096];
            }
            
            fAdaptedOutputs = new REAL_INT*[base_dsp->getNumOutputs()];
            for (int i = 0; i < base_dsp->getNumOutputs(); i++) {
                fAdaptedOutputs[i] = new REAL_INT[4096];
            }
        }
    
        virtual ~dsp_sample_adapter()
        {
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                delete [] fAdaptedInputs[i];
            }
            delete [] fAdaptedInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                delete [] fAdaptedOutputs[i];
            }
            delete [] fAdaptedOutputs;
        }
    
        virtual dsp_sample_adapter* clone() { return new dsp_sample_adapter(fDSP->clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= 4096);
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses REAL_INT
            fDSP->compute(count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= 4096);
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses REAL_INT
            fDSP->compute(date_usec, count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
        }
};

// Template used to specialize double parameters expressed as NUM/DENOM
template <int NUM, int DENOM>
struct Double {
    static constexpr double value() { return double(NUM)/double(DENOM); }
};

// Base class for filters
template <class fVslider0, int fVslider1>
struct Filter {
    inline int getFactor() { return fVslider1; }
};

// Identity filter: copy input to output
template <class fVslider0, int fVslider1>
struct Identity : public Filter<fVslider0, fVslider1> {
    inline int getFactor() { return fVslider1; }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        memcpy(output0, input0, count * sizeof(FAUSTFLOAT));
    }
};

// Generated with process = fi.lowpass(3, ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass3 : public Filter<fVslider0, fVslider1> {
    
    REAL fVec0[2];
    REAL fRec1[2];
    REAL fRec0[3];
    
    inline REAL LowPass3_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass3()
    {
        for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
            fVec0[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
            fRec1[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 1.0000000000000002) / fSlow0) + 1.0));
        REAL fSlow3 = (1.0 / (fSlow1 + 1.0));
        REAL fSlow4 = (1.0 - fSlow1);
        REAL fSlow5 = (((fSlow1 + -1.0000000000000002) / fSlow0) + 1.0);
        REAL fSlow6 = (2.0 * (1.0 - (1.0 / LowPass3_faustpower2_f(fSlow0))));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            REAL fTemp0 = REAL(input0[i]);
            fVec0[0] = fTemp0;
            fRec1[0] = (0.0 - (fSlow3 * ((fSlow4 * fRec1[1]) - (fTemp0 + fVec0[1]))));
            fRec0[0] = (fRec1[0] - (fSlow2 * ((fSlow5 * fRec0[2]) + (fSlow6 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (fRec0[2] + (fRec0[0] + (2.0 * fRec0[1])))));
            fVec0[1] = fVec0[0];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass(4, ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass4 : public Filter<fVslider0, fVslider1> {
    
    REAL fRec1[3];
    REAL fRec0[3];
    
    inline REAL LowPass4_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass4()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec1[l0] = 0.0f;
        }
        for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
            fRec0[l1] = 0.0f;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 0.76536686473017945) / fSlow0) + 1.0));
        REAL fSlow3 = (1.0 / (((fSlow1 + 1.8477590650225735) / fSlow0) + 1.0));
        REAL fSlow4 = (((fSlow1 + -1.8477590650225735) / fSlow0) + 1.0);
        REAL fSlow5 = (2.0 * (1.0 - (1.0 / LowPass4_faustpower2_f(fSlow0))));
        REAL fSlow6 = (((fSlow1 + -0.76536686473017945) / fSlow0) + 1.0);
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec1[0] = (REAL(input0[i]) - (fSlow3 * ((fSlow4 * fRec1[2]) + (fSlow5 * fRec1[1]))));
            fRec0[0] = ((fSlow3 * (fRec1[2] + (fRec1[0] + (2.0 * fRec1[1])))) - (fSlow2 * ((fSlow6 * fRec0[2]) + (fSlow5 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (fRec0[2] + (fRec0[0] + (2.0 * fRec0[1])))));
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass3e(ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass3e : public Filter<fVslider0, fVslider1> {
    
    REAL fRec1[3];
    REAL fVec0[2];
    REAL fRec0[2];
    
    inline REAL LowPass3e_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass3e()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec1[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
            fVec0[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (fSlow1 + 0.82244590899881598));
        REAL fSlow3 = (0.82244590899881598 - fSlow1);
        REAL fSlow4 = (1.0 / (((fSlow1 + 0.80263676416103003) / fSlow0) + 1.4122708937742039));
        REAL fSlow5 = LowPass3e_faustpower2_f(fSlow0);
        REAL fSlow6 = (0.019809144837788999 / fSlow5);
        REAL fSlow7 = (fSlow6 + 1.1615164189826961);
        REAL fSlow8 = (((fSlow1 + -0.80263676416103003) / fSlow0) + 1.4122708937742039);
        REAL fSlow9 = (2.0 * (1.4122708937742039 - (1.0 / fSlow5)));
        REAL fSlow10 = (2.0 * (1.1615164189826961 - fSlow6));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec1[0] = (REAL(input0[i]) - (fSlow4 * ((fSlow8 * fRec1[2]) + (fSlow9 * fRec1[1]))));
            REAL fTemp0 = (fSlow4 * (((fSlow7 * fRec1[0]) + (fSlow10 * fRec1[1])) + (fSlow7 * fRec1[2])));
            fVec0[0] = fTemp0;
            fRec0[0] = (0.0 - (fSlow2 * ((fSlow3 * fRec0[1]) - (fTemp0 + fVec0[1]))));
            output0[i] = FAUSTFLOAT(fRec0[0]);
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fVec0[1] = fVec0[0];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass6e(ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass6e : public Filter<fVslider0, fVslider1> {
    
    REAL fRec2[3];
    REAL fRec1[3];
    REAL fRec0[3];
    
    inline REAL LowPass6e_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass6e()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec2[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
            fRec1[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 0.16840487111358901) / fSlow0) + 1.0693584077073119));
        REAL fSlow3 = LowPass6e_faustpower2_f(fSlow0);
        REAL fSlow4 = (1.0 / fSlow3);
        REAL fSlow5 = (fSlow4 + 53.536152954556727);
        REAL fSlow6 = (1.0 / (((fSlow1 + 0.51247864188914105) / fSlow0) + 0.68962136448467504));
        REAL fSlow7 = (fSlow4 + 7.6217312988706034);
        REAL fSlow8 = (1.0 / (((fSlow1 + 0.78241304682164503) / fSlow0) + 0.24529150870616001));
        REAL fSlow9 = (9.9999997054999994e-05 / fSlow3);
        REAL fSlow10 = (fSlow9 + 0.00043322720055500002);
        REAL fSlow11 = (((fSlow1 + -0.78241304682164503) / fSlow0) + 0.24529150870616001);
        REAL fSlow12 = (2.0 * (0.24529150870616001 - fSlow4));
        REAL fSlow13 = (2.0 * (0.00043322720055500002 - fSlow9));
        REAL fSlow14 = (((fSlow1 + -0.51247864188914105) / fSlow0) + 0.68962136448467504);
        REAL fSlow15 = (2.0 * (0.68962136448467504 - fSlow4));
        REAL fSlow16 = (2.0 * (7.6217312988706034 - fSlow4));
        REAL fSlow17 = (((fSlow1 + -0.16840487111358901) / fSlow0) + 1.0693584077073119);
        REAL fSlow18 = (2.0 * (1.0693584077073119 - fSlow4));
        REAL fSlow19 = (2.0 * (53.536152954556727 - fSlow4));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec2[0] = (REAL(input0[i]) - (fSlow8 * ((fSlow11 * fRec2[2]) + (fSlow12 * fRec2[1]))));
            fRec1[0] = ((fSlow8 * (((fSlow10 * fRec2[0]) + (fSlow13 * fRec2[1])) + (fSlow10 * fRec2[2]))) - (fSlow6 * ((fSlow14 * fRec1[2]) + (fSlow15 * fRec1[1]))));
            fRec0[0] = ((fSlow6 * (((fSlow7 * fRec1[0]) + (fSlow16 * fRec1[1])) + (fSlow7 * fRec1[2]))) - (fSlow2 * ((fSlow17 * fRec0[2]) + (fSlow18 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (((fSlow5 * fRec0[0]) + (fSlow19 * fRec0[1])) + (fSlow5 * fRec0[2]))));
            fRec2[2] = fRec2[1];
            fRec2[1] = fRec2[0];
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// A "si.bus(N)" like hard-coded class
struct dsp_bus : public base_dsp {
    
    int fChannels;
    int fSampleRate;
    
    dsp_bus(int channels):fChannels(channels), fSampleRate(-1)
    {}
    
    virtual int getNumInputs() { return fChannels; }
    virtual int getNumOutputs() { return fChannels; }
    
    virtual int getSampleRate() { return fSampleRate; }
    
    virtual void buildUserInterface(UI* ui_interface) {}
    virtual void init(int sample_rate)
    {
        //classInit(sample_rate);
        instanceInit(sample_rate);
    }
    
    virtual void instanceInit(int sample_rate)
    {
        fSampleRate = sample_rate;
        instanceConstants(sample_rate);
        instanceResetUserInterface();
        instanceClear();
    }
    
    virtual void instanceConstants(int sample_rate) {}
    virtual void instanceResetUserInterface() {}
    virtual void instanceClear() {}
    
    virtual base_dsp* clone() { return new dsp_bus(fChannels); }
    
    virtual void metadata(Meta* m) {}
    
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        for (int chan = 0; chan < fChannels; chan++) {
            memcpy(outputs[chan], inputs[chan], sizeof(FAUSTFLOAT) * count);
        }
    }
    
    virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        compute(count, inputs, outputs);
    }
    
};

// Base class for sample-rate adapter
template <typename FILTER>
class sr_sampler : public decorator_dsp {
    
    protected:
    
        std::vector<FILTER> fInputLowPass;
        std::vector<FILTER> fOutputLowPass;
    
        inline int getFactor() { return this->fOutputLowPass[0].getFactor(); }
    
    public:
    
        sr_sampler(base_dsp* base_dsp):decorator_dsp(base_dsp)
        {
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                fInputLowPass.push_back(FILTER());
            }
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                fOutputLowPass.push_back(FILTER());
            }
        }
};

// Down sample-rate adapter
template <typename FILTER>
class dsp_down_sampler : public sr_sampler<FILTER> {
    
    public:
    
        dsp_down_sampler(base_dsp* base_dsp):sr_sampler<FILTER>(base_dsp)
        {}
    
        virtual void init(int sample_rate)
        {
            this->fDSP->init(sample_rate / this->getFactor());
        }
    
        virtual void instanceInit(int sample_rate)
        {
            this->fDSP->instanceInit(sample_rate / this->getFactor());
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            this->fDSP->instanceConstants(sample_rate / this->getFactor());
        }
    
        virtual dsp_down_sampler* clone() { return new dsp_down_sampler(decorator_dsp::clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            int real_count = count / this->getFactor();
            
            // Adapt inputs
            FAUSTFLOAT** fInputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumInputs() * sizeof(FAUSTFLOAT*));
            for (int chan = 0; chan < this->fDSP->getNumInputs(); chan++) {
                // Lowpass filtering in place on 'inputs'
                this->fInputLowPass[chan].compute(count, inputs[chan], inputs[chan]);
                // Allocate fInputs with 'real_count' frames
                fInputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
                // Decimate
                for (int frame = 0; frame < real_count; frame++) {
                    fInputs[chan][frame] = inputs[chan][frame * this->getFactor()];
                }
            }
            
            // Allocate fOutputs with 'real_count' frames
            FAUSTFLOAT** fOutputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumOutputs() * sizeof(FAUSTFLOAT*));
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                fOutputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
            }
            
            // Compute at lower rate
            this->fDSP->compute(real_count, fInputs, fOutputs);
            
            // Adapt outputs
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                // Puts zeros
                memset(outputs[chan], 0, sizeof(FAUSTFLOAT) * count);
                for (int frame = 0; frame < real_count; frame++) {
                    // Copy one sample every 'DownFactor'
                    // Apply volume
                    //outputs[chan][frame * this->getFactor()] = fOutputs[chan][frame] * this->getFactor();
                    outputs[chan][frame * this->getFactor()] = fOutputs[chan][frame];
                }
                // Lowpass filtering in place on 'outputs'
                this->fOutputLowPass[chan].compute(count, outputs[chan], outputs[chan]);
            }
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

// Up sample-rate adapter
template <typename FILTER>
class dsp_up_sampler : public sr_sampler<FILTER> {
    
    public:
    
        dsp_up_sampler(base_dsp* base_dsp):sr_sampler<FILTER>(base_dsp)
        {}
    
        virtual void init(int sample_rate)
        {
            this->fDSP->init(sample_rate * this->getFactor());
        }
    
        virtual void instanceInit(int sample_rate)
        {
            this->fDSP->instanceInit(sample_rate * this->getFactor());
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            this->fDSP->instanceConstants(sample_rate * this->getFactor());
        }
    
        virtual dsp_up_sampler* clone() { return new dsp_up_sampler(decorator_dsp::clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            int real_count = count * this->getFactor();
            
            // Adapt inputs
            FAUSTFLOAT** fInputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumInputs() * sizeof(FAUSTFLOAT*));
            
            for (int chan = 0; chan < this->fDSP->getNumInputs(); chan++) {
                // Allocate fInputs with 'real_count' frames
                fInputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
                // Puts zeros
                memset(fInputs[chan], 0, sizeof(FAUSTFLOAT) * real_count);
                for (int frame = 0; frame < count; frame++) {
                    // Copy one sample every 'UpFactor'
                    fInputs[chan][frame * this->getFactor()] = inputs[chan][frame];
                }
                // Lowpass filtering in place on 'fInputs'
                this->fInputLowPass[chan].compute(real_count, fInputs[chan], fInputs[chan]);
            }
            
            // Allocate fOutputs with 'real_count' frames
            FAUSTFLOAT** fOutputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumOutputs() * sizeof(FAUSTFLOAT*));
            
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                fOutputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
            }
            
            // Compute at upper rate
            this->fDSP->compute(real_count, fInputs, fOutputs);
            
            // Adapt outputs
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                // Lowpass filtering in place on 'fOutputs'
                this->fOutputLowPass[chan].compute(real_count, fOutputs[chan], fOutputs[chan]);
                // Decimate
                for (int frame = 0; frame < count; frame++) {
                    // Apply volume
                    //outputs[chan][frame] = fOutputs[chan][frame * this->getFactor()] * this->getFactor();
                    outputs[chan][frame] = fOutputs[chan][frame * this->getFactor()];
                }
            }
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

// Create a UP/DS + Filter adapted DSP
template <typename REAL>
base_dsp* createSRAdapter(base_dsp* DSP, int ds = 0, int us = 0, int filter = 0)
{
    if (ds > 0) {
        switch (filter) {
            case 0:
                if (ds == 2) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 2>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 3>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 4>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 8>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 16>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 32>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 1:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 2:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 3:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 4:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            default:
                fprintf(stderr, "ERROR : filter type must be in [0..4] range\n");
                assert(false);
                return nullptr;
        }
    } else if (us > 0) {
        
        switch (filter) {
            case 0:
                if (us == 2) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 2>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 3>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 4>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 8>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 16>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 32>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 1:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 2:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 3:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 4:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            default:
                fprintf(stderr, "ERROR : filter type must be in [0..4] range\n");
                assert(false);
                return nullptr;
        }
    } else {
        return DSP;
    }
}
    
#endif
/************************** END base_dsp-adapter.h **************************/
/************************** BEGIN MidiUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_MIDIUI_H
#define FAUST_MIDIUI_H

#include <vector>
#include <string>
#include <utility>
#include <cstdlib>
#include <cmath>

/************************** BEGIN meta.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__

/**
 The base class of Meta handler to be used in base_dsp::metadata(Meta* m) method to retrieve (key, value) metadata.
 */
struct Meta
{
    virtual ~Meta() {};
    virtual void declare(const char* key, const char* value) = 0;
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN GUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef __GUI_H__
#define __GUI_H__

#include <list>
#include <map>
#include <vector>
#include <assert.h>

#ifdef _WIN32
# pragma warning (disable: 4100)
#else
# pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

/************************** BEGIN ValueConverter.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __ValueConverter__
#define __ValueConverter__

/***************************************************************************************
 ValueConverter.h
 (GRAME, Copyright 2015-2019)
 
 Set of conversion objects used to map user interface values (for example a gui slider
 delivering values between 0 and 1) to faust values (for example a vslider between
 20 and 20000) using a log scale.
 
 -- Utilities
 
 Range(lo,hi) : clip a value x between lo and hi
 Interpolator(lo,hi,v1,v2) : Maps a value x between lo and hi to a value y between v1 and v2
 Interpolator3pt(lo,mi,hi,v1,vm,v2) : Map values between lo mid hi to values between v1 vm v2
 
 -- Value Converters
 
 ValueConverter::ui2faust(x)
 ValueConverter::faust2ui(x)
 
 -- ValueConverters used for sliders depending of the scale
 
 LinearValueConverter(umin, umax, fmin, fmax)
 LinearValueConverter2(lo, mi, hi, v1, vm, v2) using 2 segments
 LogValueConverter(umin, umax, fmin, fmax)
 ExpValueConverter(umin, umax, fmin, fmax)
 
 -- ValueConverters used for accelerometers based on 3 points
 
 AccUpConverter(amin, amid, amax, fmin, fmid, fmax)        -- curve 0
 AccDownConverter(amin, amid, amax, fmin, fmid, fmax)      -- curve 1
 AccUpDownConverter(amin, amid, amax, fmin, fmid, fmax)    -- curve 2
 AccDownUpConverter(amin, amid, amax, fmin, fmid, fmax)    -- curve 3
 
 -- lists of ZoneControl are used to implement accelerometers metadata for each axes
 
 ZoneControl(zone, valueConverter) : a zone with an accelerometer data converter
 
 -- ZoneReader are used to implement screencolor metadata
 
 ZoneReader(zone, valueConverter) : a zone with a data converter

****************************************************************************************/

#include <float.h>
#include <algorithm>    // std::max
#include <cmath>
#include <vector>
#include <assert.h>

//--------------------------------------------------------------------------------------
// Interpolator(lo,hi,v1,v2)
// Maps a value x between lo and hi to a value y between v1 and v2
// y = v1 + (x-lo)/(hi-lo)*(v2-v1)
// y = v1 + (x-lo) * coef           with coef = (v2-v1)/(hi-lo)
// y = v1 + x*coef - lo*coef
// y = v1 - lo*coef + x*coef
// y = offset + x*coef              with offset = v1 - lo*coef
//--------------------------------------------------------------------------------------
class Interpolator
{
    private:

        //--------------------------------------------------------------------------------------
        // Range(lo,hi) clip a value between lo and hi
        //--------------------------------------------------------------------------------------
        struct Range
        {
            double fLo;
            double fHi;

            Range(double x, double y) : fLo(std::min<double>(x,y)), fHi(std::max<double>(x,y)) {}
            double operator()(double x) { return (x<fLo) ? fLo : (x>fHi) ? fHi : x; }
        };


        Range fRange;
        double fCoef;
        double fOffset;

    public:

        Interpolator(double lo, double hi, double v1, double v2) : fRange(lo,hi)
        {
            if (hi != lo) {
                // regular case
                fCoef = (v2-v1)/(hi-lo);
                fOffset = v1 - lo*fCoef;
            } else {
                // degenerate case, avoids division by zero
                fCoef = 0;
                fOffset = (v1+v2)/2;
            }
        }
        double operator()(double v)
        {
            double x = fRange(v);
            return  fOffset + x*fCoef;
        }

        void getLowHigh(double& amin, double& amax)
        {
            amin = fRange.fLo;
            amax = fRange.fHi;
        }
};

//--------------------------------------------------------------------------------------
// Interpolator3pt(lo,mi,hi,v1,vm,v2)
// Map values between lo mid hi to values between v1 vm v2
//--------------------------------------------------------------------------------------
class Interpolator3pt
{

    private:

        Interpolator fSegment1;
        Interpolator fSegment2;
        double fMid;

    public:

        Interpolator3pt(double lo, double mi, double hi, double v1, double vm, double v2) :
            fSegment1(lo, mi, v1, vm),
            fSegment2(mi, hi, vm, v2),
            fMid(mi) {}
        double operator()(double x) { return  (x < fMid) ? fSegment1(x) : fSegment2(x); }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fSegment1.getLowHigh(amin, amid);
            fSegment2.getLowHigh(amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Abstract ValueConverter class. Converts values between UI and Faust representations
//--------------------------------------------------------------------------------------
class ValueConverter // Identity by default
{

    public:

        virtual ~ValueConverter() {}
        virtual double ui2faust(double x) { return x; };
        virtual double faust2ui(double x) { return x; };
};

//--------------------------------------------------------------------------------------
// A converter than can be updated
//--------------------------------------------------------------------------------------

class UpdatableValueConverter : public ValueConverter {
    
    protected:
        
        bool fActive;
        
    public:
        
        UpdatableValueConverter():fActive(true)
        {}
        virtual ~UpdatableValueConverter()
        {}
        
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max) = 0;
        virtual void getMappingValues(double& amin, double& amid, double& amax) = 0;
        
        void setActive(bool on_off) { fActive = on_off; }
        bool getActive() { return fActive; }
    
};

//--------------------------------------------------------------------------------------
// Linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter : public ValueConverter
{
    
    private:
        
        Interpolator fUI2F;
        Interpolator fF2UI;
        
    public:
        
        LinearValueConverter(double umin, double umax, double fmin, double fmax) :
            fUI2F(umin,umax,fmin,fmax), fF2UI(fmin,fmax,umin,umax)
        {}
        
        LinearValueConverter() : fUI2F(0.,0.,0.,0.), fF2UI(0.,0.,0.,0.)
        {}
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
};

//--------------------------------------------------------------------------------------
// Two segments linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter2 : public UpdatableValueConverter
{
    
    private:
    
        Interpolator3pt fUI2F;
        Interpolator3pt fF2UI;
        
    public:
    
        LinearValueConverter2(double amin, double amid, double amax, double min, double init, double max) :
            fUI2F(amin, amid, amax, min, init, max), fF2UI(min, init, max, amin, amid, amax)
        {}
        
        LinearValueConverter2() : fUI2F(0.,0.,0.,0.,0.,0.), fF2UI(0.,0.,0.,0.,0.,0.)
        {}
    
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max)
        {
            fUI2F = Interpolator3pt(amin, amid, amax, min, init, max);
            fF2UI = Interpolator3pt(min, init, max, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fUI2F.getMappingValues(amin, amid, amax);
        }
    
};

//--------------------------------------------------------------------------------------
// Logarithmic conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LogValueConverter : public LinearValueConverter
{

    public:

        LogValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::log(std::max<double>(DBL_MIN, fmin)), std::log(std::max<double>(DBL_MIN, fmax)))
        {}

        virtual double ui2faust(double x) { return std::exp(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::log(std::max<double>(x, DBL_MIN))); }

};

//--------------------------------------------------------------------------------------
// Exponential conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class ExpValueConverter : public LinearValueConverter
{

    public:

        ExpValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::min<double>(DBL_MAX, std::exp(fmin)), std::min<double>(DBL_MAX, std::exp(fmax)))
        {}

        virtual double ui2faust(double x) { return std::log(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::min<double>(DBL_MAX, std::exp(x))); }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up curve (curve 0)
//--------------------------------------------------------------------------------------
class AccUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt fA2F;
        Interpolator3pt fF2A;

    public:

        AccUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmid,fmax),
            fF2A(fmin,fmid,fmax,amin,amid,amax)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmid, fmax);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down curve (curve 1)
//--------------------------------------------------------------------------------------
class AccDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator3pt	fF2A;

    public:

        AccDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmid,fmin),
            fF2A(fmin,fmid,fmax,amax,amid,amin)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
             //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmid, fmin);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amax, amid, amin);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up-Down curve (curve 2)
//--------------------------------------------------------------------------------------
class AccUpDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccUpDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmax,fmin),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmax, fmin);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down-Up curve (curve 3)
//--------------------------------------------------------------------------------------
class AccDownUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccDownUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmin,fmax),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmin, fmax);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Base class for ZoneControl
//--------------------------------------------------------------------------------------
class ZoneControl
{

    protected:

        FAUSTFLOAT*	fZone;

    public:

        ZoneControl(FAUSTFLOAT* zone) : fZone(zone) {}
        virtual ~ZoneControl() {}

        virtual void update(double v) const {}

        virtual void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max) {}
        virtual void getMappingValues(double& amin, double& amid, double& amax) {}

        FAUSTFLOAT* getZone() { return fZone; }

        virtual void setActive(bool on_off) {}
        virtual bool getActive() { return false; }

        virtual int getCurve() { return -1; }

};

//--------------------------------------------------------------------------------------
//  Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class ConverterZoneControl : public ZoneControl
{

    protected:

        ValueConverter* fValueConverter;

    public:

        ConverterZoneControl(FAUSTFLOAT* zone, ValueConverter* converter) : ZoneControl(zone), fValueConverter(converter) {}
        virtual ~ConverterZoneControl() { delete fValueConverter; } // Assuming fValueConverter is not kept elsewhere...

        virtual void update(double v) const { *fZone = fValueConverter->ui2faust(v); }

        ValueConverter* getConverter() { return fValueConverter; }

};

//--------------------------------------------------------------------------------------
// Association of a zone and a four value converter, each one for each possible curve.
// Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class CurveZoneControl : public ZoneControl
{

    private:

        std::vector<UpdatableValueConverter*> fValueConverters;
        int fCurve;

    public:

        CurveZoneControl(FAUSTFLOAT* zone, int curve, double amin, double amid, double amax, double min, double init, double max) : ZoneControl(zone), fCurve(0)
        {
            assert(curve >= 0 && curve <= 3);
            fValueConverters.push_back(new AccUpConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccUpDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownUpConverter(amin, amid, amax, min, init, max));
            fCurve = curve;
        }
        virtual ~CurveZoneControl()
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                delete(*it);
            }
        }
        void update(double v) const { if (fValueConverters[fCurve]->getActive()) *fZone = fValueConverters[fCurve]->ui2faust(v); }

        void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max)
        {
            fValueConverters[curve]->setMappingValues(amin, amid, amax, min, init, max);
            fCurve = curve;
        }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fValueConverters[fCurve]->getMappingValues(amin, amid, amax);
        }

        void setActive(bool on_off)
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                (*it)->setActive(on_off);
            }
        }

        int getCurve() { return fCurve; }
};

class ZoneReader
{

    private:

        FAUSTFLOAT* fZone;
        Interpolator fInterpolator;

    public:

        ZoneReader(FAUSTFLOAT* zone, double lo, double hi) : fZone(zone), fInterpolator(lo, hi, 0, 255) {}

        virtual ~ZoneReader() {}

        int getValue()
        {
            return (fZone != nullptr) ? int(fInterpolator(*fZone)) : 127;
        }

};

#endif
/**************************  END  ValueConverter.h **************************/
/************************** BEGIN MetaDataUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef MetaData_UI_H
#define MetaData_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <map>
#include <set>
#include <string>
#include <string.h>
#include <assert.h>
#include <stdio.h> // We use the lighter fprintf code

/************************** BEGIN SimpleParser.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef SIMPLEPARSER_H
#define SIMPLEPARSER_H

// ---------------------------------------------------------------------
//                          Simple Parser
// A parser returns true if it was able to parse what it is
// supposed to parse and advance the pointer. Otherwise it returns false
// and the pointer is not advanced so that another parser can be tried.
// ---------------------------------------------------------------------

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdio.h> // We use the lighter fprintf code
#include <ctype.h>

#ifndef _WIN32
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

struct itemInfo {
    std::string type;
    std::string label;
    std::string url;
    std::string address;
    int index;
    double init;
    double fmin;
    double fmax;
    double step;
    std::vector<std::pair<std::string, std::string> > meta;
    
    itemInfo():index(0), init(0.), fmin(0.), fmax(0.), step(0.)
    {}
};

// ---------------------------------------------------------------------
//                          Elementary parsers
// ---------------------------------------------------------------------

// Report a parsing error
static bool parseError(const char*& p, const char* errmsg)
{
    fprintf(stderr, "Parse error : %s here : %s\n", errmsg, p);
    return true;
}

/**
 * @brief skipBlank : advance pointer p to the first non blank character
 * @param p the string to parse, then the remaining string
 */
static void skipBlank(const char*& p)
{
    while (isspace(*p)) { p++; }
}

// Parse character x, but don't report error if fails
static bool tryChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseChar : parse a specific character x
 * @param p the string to parse, then the remaining string
 * @param x the character to recognize
 * @return true if x was found at the begin of p
 */
static bool parseChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseWord : parse a specific string w
 * @param p the string to parse, then the remaining string
 * @param w the string to recognize
 * @return true if string w was found at the begin of p
 */
static bool parseWord(const char*& p, const char* w)
{
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail
    while ((*w == *p) && (*w)) {++w; ++p;}
    if (*w) {
        p = saved;
        return false;
    } else {
        return true;
    }
}

/**
 * @brief parseDouble : parse number [s]dddd[.dddd] or [s]d[.dddd][E|e][s][dddd] and store the result in x
 * @param p the string to parse, then the remaining string
 * @param x the float number found if any
 * @return true if a float number was found at the begin of p
 */
static bool parseDouble(const char*& p, double& x)
{
    double sign = 1.0;     // sign of the number
    double ipart = 0;      // integral part of the number
    double dpart = 0;      // decimal part of the number before division
    double dcoef = 1.0;    // division factor for the decimal part
    double expsign = 1.0;  // sign of the E|e part
    double expcoef = 0.0;  // multiplication factor of E|e part
    
    bool valid = false;    // true if the number contains at least one digit
    
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail
    
    // Sign
    if (parseChar(p, '+')) {
        sign = 1.0;
    } else if (parseChar(p, '-')) {
        sign = -1.0;
    }
    
    // Integral part
    while (isdigit(*p)) {
        valid = true;
        ipart = ipart*10 + (*p - '0');
        p++;
    }
    
    // Possible decimal part
    if (parseChar(p, '.')) {
        while (isdigit(*p)) {
            valid = true;
            dpart = dpart*10 + (*p - '0');
            dcoef *= 10.0;
            p++;
        }
    }
    
    // Possible E|e part
    if (parseChar(p, 'E') || parseChar(p, 'e')) {
        if (parseChar(p, '+')) {
            expsign = 1.0;
        } else if (parseChar(p, '-')) {
            expsign = -1.0;
        }
        while (isdigit(*p)) {
            expcoef = expcoef*10 + (*p - '0');
            p++;
        }
    }
    
    if (valid)  {
        x = (sign*(ipart + dpart/dcoef)) * std::pow(10.0, expcoef*expsign);
    } else {
        p = saved;
    }
    return valid;
}

/**
 * @brief parseString, parse an arbitrary quoted string q...q and store the result in s
 * @param p the string to parse, then the remaining string
 * @param quote the character used to quote the string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseString(const char*& p, char quote, std::string& s)
{
    std::string str;
    skipBlank(p);
    
    const char* saved = p;  // to restore position if we fail
    if (*p++ == quote) {
        while ((*p != 0) && (*p != quote)) {
            str += *p++;
        }
        if (*p++ == quote) {
            s = str;
            return true;
        }
    }
    p = saved;
    return false;
}

/**
 * @brief parseSQString, parse a single quoted string '...' and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseSQString(const char*& p, std::string& s)
{
    return parseString(p, '\'', s);
}

/**
 * @brief parseDQString, parse a double quoted string "..." and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseDQString(const char*& p, std::string& s)
{
    return parseString(p, '"', s);
}

// ---------------------------------------------------------------------
//
//                          IMPLEMENTATION
// 
// ---------------------------------------------------------------------

/**
 * @brief parseMenuItem, parse a menu item ...'low':440.0...
 * @param p the string to parse, then the remaining string
 * @param name the name found
 * @param value the value found
 * @return true if a nemu item was found
 */
static bool parseMenuItem(const char*& p, std::string& name, double& value)
{
    const char* saved = p;  // to restore position if we fail
    if (parseSQString(p, name) && parseChar(p, ':') && parseDouble(p, value)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

static bool parseMenuItem2(const char*& p, std::string& name)
{
    const char* saved = p;  // to restore position if we fail
    // single quoted
    if (parseSQString(p, name)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

/**
 * @brief parseMenuList, parse a menu list {'low' : 440.0; 'mid' : 880.0; 'hi' : 1760.0}...
 * @param p the string to parse, then the remaining string
 * @param names the vector of names found
 * @param values the vector of values found
 * @return true if a menu list was found
 */
static bool parseMenuList(const char*& p, std::vector<std::string>& names, std::vector<double>& values)
{
    std::vector<std::string> tmpnames;
    std::vector<double> tmpvalues;
    const char* saved = p; // to restore position if we fail

    if (parseChar(p, '{')) {
        do {
            std::string n;
            double v;
            if (parseMenuItem(p, n, v)) {
                tmpnames.push_back(n);
                tmpvalues.push_back(v);
            } else {
                p = saved;
                return false;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            values = tmpvalues;
            return true;
        }
    }
    p = saved;
    return false;
}

static bool parseMenuList2(const char*& p, std::vector<std::string>& names, bool debug)
{
    std::vector<std::string> tmpnames;
    const char* saved = p;  // to restore position if we fail
    
    if (parseChar(p, '{')) {
        do {
            std::string n;
            if (parseMenuItem2(p, n)) {
                tmpnames.push_back(n);
            } else {
                goto error;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            return true;
        }
    }
    
error:
    if (debug) { fprintf(stderr, "parseMenuList2 : (%s) is not a valid list !\n", p); }
    p = saved;
    return false;
}

/// ---------------------------------------------------------------------
// Parse list of strings
/// ---------------------------------------------------------------------
static bool parseList(const char*& p, std::vector<std::string>& items)
{
    const char* saved = p;  // to restore position if we fail
    if (parseChar(p, '[')) {
        do {
            std::string item;
            if (!parseDQString(p, item)) {
                p = saved;
                return false;
            }
            items.push_back(item);
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseMetaData(const char*& p, std::map<std::string, std::string>& metadatas)
{
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas[metaKey] = metaValue;
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseItemMetaData(const char*& p, std::vector<std::pair<std::string, std::string> >& metadatas)
{
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas.push_back(std::make_pair(metaKey, metaValue));
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse metadatas of the interface:
// "name" : "...", "inputs" : "...", "outputs" : "...", ...
// and store the result as key/value
/// ---------------------------------------------------------------------
static bool parseGlobalMetaData(const char*& p, std::string& key, std::string& value, double& dbl, std::map<std::string, std::string>& metadatas, std::vector<std::string>& items)
{
    const char* saved = p; // to restore position if we fail
    if (parseDQString(p, key)) {
        if (key == "meta") {
            return parseMetaData(p, metadatas);
        } else {
            return parseChar(p, ':') && (parseDQString(p, value) || parseList(p, items) || parseDouble(p, dbl));
        }
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse gui:
// "type" : "...", "label" : "...", "address" : "...", ...
// and store the result in uiItems Vector
/// ---------------------------------------------------------------------
static bool parseUI(const char*& p, std::vector<itemInfo>& uiItems, int& numItems)
{
    const char* saved = p; // to restore position if we fail
    if (parseChar(p, '{')) {
   
        std::string label;
        std::string value;
        double dbl = 0;
        
        do {
            if (parseDQString(p, label)) {
                if (label == "type") {
                    if (uiItems.size() != 0) {
                        numItems++;
                    }
                    if (parseChar(p, ':') && parseDQString(p, value)) {   
                        itemInfo item;
                        item.type = value;
                        uiItems.push_back(item);
                    }
                }
                
                else if (label == "label") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].label = value;
                    }
                }
                
                else if (label == "url") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].url = value;
                    }
                }
                
                else if (label == "address") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].address = value;
                    }
                }
                
                else if (label == "index") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].index = int(dbl);
                    }
                }
                
                else if (label == "meta") {
                    if (!parseItemMetaData(p, uiItems[numItems].meta)) {
                        return false;
                    }
                }
                
                else if (label == "init") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].init = dbl;
                    }
                }
                
                else if (label == "min") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].fmin = dbl;
                    }
                }
                
                else if (label == "max") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].fmax = dbl;
                    }
                }
                
                else if (label == "step") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].step = dbl;
                    }
                }
                
                else if (label == "items") {
                    if (parseChar(p, ':') && parseChar(p, '[')) {
                        do {
                            if (!parseUI(p, uiItems, numItems)) {
                                p = saved;
                                return false;
                            }
                        } while (tryChar(p, ','));
                        if (parseChar(p, ']')) {
                            itemInfo item;
                            item.type = "close";
                            uiItems.push_back(item);
                            numItems++;
                        }
                    }
                }
            } else {
                p = saved;
                return false;
            }
            
        } while (tryChar(p, ','));
    
        return parseChar(p, '}');
    } else {
        return true; // "items": [] is valid
    }
}

// ---------------------------------------------------------------------
// Parse full JSON record describing a JSON/Faust interface :
// {"metadatas": "...", "ui": [{ "type": "...", "label": "...", "items": [...], "address": "...","init": "...", "min": "...", "max": "...","step": "..."}]}
//
// and store the result in map Metadatas and vector containing the items of the interface. Returns true if parsing was successfull.
/// ---------------------------------------------------------------------
static bool parseJson(const char*& p,
                      std::map<std::string, std::pair<std::string, double> >& metaDatas0,
                      std::map<std::string, std::string>& metaDatas1,
                      std::map<std::string, std::vector<std::string> >& metaDatas2,
                      std::vector<itemInfo>& uiItems)
{
    parseChar(p, '{');
    
    do {
        std::string key;
        std::string value;
        double dbl = 0;
        std::vector<std::string> items;
        if (parseGlobalMetaData(p, key, value, dbl, metaDatas1, items)) {
            if (key != "meta") {
                // keep "name", "inputs", "outputs" key/value pairs
                if (items.size() > 0) {
                    metaDatas2[key] = items;
                    items.clear();
                } else if (value != "") {
                    metaDatas0[key].first = value;
                } else {
                    metaDatas0[key].second = dbl;
                }
            }
        } else if (key == "ui") {
            int numItems = 0;
            parseChar(p, '[') && parseUI(p, uiItems, numItems);
        }
    } while (tryChar(p, ','));
    
    return parseChar(p, '}');
}

#endif // SIMPLEPARSER_H
/**************************  END  SimpleParser.h **************************/

static bool startWith(const std::string& str, const std::string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix);
}

/**
 * Convert a dB value into a scale between 0 and 1 (following IEC standard ?)
 */
static FAUSTFLOAT dB2Scale(FAUSTFLOAT dB)
{
    FAUSTFLOAT scale = FAUSTFLOAT(1.0);
    
    /*if (dB < -70.0f)
     scale = 0.0f;
     else*/
    if (dB < FAUSTFLOAT(-60.0))
        scale = (dB + FAUSTFLOAT(70.0)) * FAUSTFLOAT(0.0025);
    else if (dB < FAUSTFLOAT(-50.0))
        scale = (dB + FAUSTFLOAT(60.0)) * FAUSTFLOAT(0.005) + FAUSTFLOAT(0.025);
    else if (dB < FAUSTFLOAT(-40.0))
        scale = (dB + FAUSTFLOAT(50.0)) * FAUSTFLOAT(0.0075) + FAUSTFLOAT(0.075);
    else if (dB < FAUSTFLOAT(-30.0))
        scale = (dB + FAUSTFLOAT(40.0)) * FAUSTFLOAT(0.015) + FAUSTFLOAT(0.15);
    else if (dB < FAUSTFLOAT(-20.0))
        scale = (dB + FAUSTFLOAT(30.0)) * FAUSTFLOAT(0.02) + FAUSTFLOAT(0.3);
    else if (dB < FAUSTFLOAT(-0.001) || dB > FAUSTFLOAT(0.001))  /* if (dB < 0.0) */
        scale = (dB + FAUSTFLOAT(20.0)) * FAUSTFLOAT(0.025) + FAUSTFLOAT(0.5);
    
    return scale;
}

/*******************************************************************************
 * MetaDataUI : Common class for MetaData handling
 ******************************************************************************/

//============================= BEGIN GROUP LABEL METADATA===========================
// Unlike widget's label, metadata inside group's label are not extracted directly by
// the Faust compiler. Therefore they must be extracted within the architecture file
//-----------------------------------------------------------------------------------

class MetaDataUI {
    
    protected:
        
        std::string                         fGroupTooltip;
        std::map<FAUSTFLOAT*, FAUSTFLOAT>   fGuiSize;            // map widget zone with widget size coef
        std::map<FAUSTFLOAT*, std::string>  fTooltip;            // map widget zone with tooltip strings
        std::map<FAUSTFLOAT*, std::string>  fUnit;               // map widget zone to unit string (i.e. "dB")
        std::map<FAUSTFLOAT*, std::string>  fRadioDescription;   // map zone to {'low':440; ...; 'hi':1000.0}
        std::map<FAUSTFLOAT*, std::string>  fMenuDescription;    // map zone to {'low':440; ...; 'hi':1000.0}
        std::set<FAUSTFLOAT*>               fKnobSet;            // set of widget zone to be knobs
        std::set<FAUSTFLOAT*>               fLedSet;             // set of widget zone to be LEDs
        std::set<FAUSTFLOAT*>               fNumSet;             // set of widget zone to be numerical bargraphs
        std::set<FAUSTFLOAT*>               fLogSet;             // set of widget zone having a log UI scale
        std::set<FAUSTFLOAT*>               fExpSet;             // set of widget zone having an exp UI scale
        std::set<FAUSTFLOAT*>               fHiddenSet;          // set of hidden widget zone
        
        void clearMetadata()
        {
            fGuiSize.clear();
            fTooltip.clear();
            fUnit.clear();
            fRadioDescription.clear();
            fMenuDescription.clear();
            fKnobSet.clear();
            fLedSet.clear();
            fNumSet.clear();
            fLogSet.clear();
            fExpSet.clear();
            fHiddenSet.clear();
            fGroupTooltip = "";
        }
        
        /**
         * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
         * (but not those in the middle of the string)
         */
        static std::string rmWhiteSpaces(const std::string& s)
        {
            size_t i = s.find_first_not_of(" \t");
            size_t j = s.find_last_not_of(" \t");
            if ((i != std::string::npos) && (j != std::string::npos)) {
                return s.substr(i, 1+j-i);
            } else {
                return "";
            }
        }
        
        /**
         * Format tooltip string by replacing some white spaces by
         * return characters so that line width doesn't exceed n.
         * Limitation : long words exceeding n are not cut.
         */
        std::string formatTooltip(int n, const std::string& tt)
        {
            std::string ss = tt;  // ss string we are going to format
            int lws = 0;          // last white space encountered
            int lri = 0;          // last return inserted
            for (int i = 0; i < (int)tt.size(); i++) {
                if (tt[i] == ' ') lws = i;
                if (((i-lri) >= n) && (lws > lri)) {
                    // insert return here
                    ss[lws] = '\n';
                    lri = lws;
                }
            }
            return ss;
        }
        
    public:
        
        virtual ~MetaDataUI()
        {}
        
        enum Scale {
            kLin,
            kLog,
            kExp
        };
        
        Scale getScale(FAUSTFLOAT* zone)
        {
            if (fLogSet.count(zone) > 0) return kLog;
            if (fExpSet.count(zone) > 0) return kExp;
            return kLin;
        }
        
        bool isKnob(FAUSTFLOAT* zone)
        {
            return fKnobSet.count(zone) > 0;
        }
        
        bool isRadio(FAUSTFLOAT* zone)
        {
            return fRadioDescription.count(zone) > 0;
        }
        
        bool isMenu(FAUSTFLOAT* zone)
        {
            return fMenuDescription.count(zone) > 0;
        }
        
        bool isLed(FAUSTFLOAT* zone)
        {
            return fLedSet.count(zone) > 0;
        }
        
        bool isNumerical(FAUSTFLOAT* zone)
        {
            return fNumSet.count(zone) > 0;
        }
        
        bool isHidden(FAUSTFLOAT* zone)
        {
            return fHiddenSet.count(zone) > 0;
        }
        
        /**
         * Extracts metadata from a label : 'vol [unit: dB]' -> 'vol' + metadata(unit=dB)
         */
        static void extractMetadata(const std::string& fulllabel, std::string& label, std::map<std::string, std::string>& metadata)
        {
            enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
            int state = kLabel; int deep = 0;
            std::string key, value;
            
            for (unsigned int i = 0; i < fulllabel.size(); i++) {
                char c = fulllabel[i];
                switch (state) {
                    case kLabel :
                        assert(deep == 0);
                        switch (c) {
                            case '\\' : state = kEscape1; break;
                            case '[' : state = kKey; deep++; break;
                            default : label += c;
                        }
                        break;
                        
                    case kEscape1:
                        label += c;
                        state = kLabel;
                        break;
                        
                    case kEscape2:
                        key += c;
                        state = kKey;
                        break;
                        
                    case kEscape3:
                        value += c;
                        state = kValue;
                        break;
                        
                    case kKey:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape2;
                                break;
                                
                            case '[':
                                deep++;
                                key += c;
                                break;
                                
                            case ':':
                                if (deep == 1) {
                                    state = kValue;
                                } else {
                                    key += c;
                                }
                                break;
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = "";
                                    state = kLabel;
                                    key = "";
                                    value = "";
                                } else {
                                    key += c;
                                }
                                break;
                            default : key += c;
                        }
                        break;
                        
                    case kValue:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape3;
                                break;
                                
                            case '[':
                                deep++;
                                value += c;
                                break;
                                
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = rmWhiteSpaces(value);
                                    state = kLabel;
                                    key = "";
                                    value = "";
                                } else {
                                    value += c;
                                }
                                break;
                            default : value += c;
                        }
                        break;
                        
                    default:
                        fprintf(stderr, "ERROR unrecognized state %d\n", state);
                }
            }
            label = rmWhiteSpaces(label);
        }
        
        /**
         * Analyses the widget zone metadata declarations and takes appropriate actions.
         */
        void declare(FAUSTFLOAT* zone, const char* key, const char* value)
        {
            if (zone == 0) {
                // special zone 0 means group metadata
                if (strcmp(key, "tooltip") == 0) {
                    // only group tooltip are currently implemented
                    fGroupTooltip = formatTooltip(30, value);
                } else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
            } else {
                if (strcmp(key, "size") == 0) {
                    fGuiSize[zone] = atof(value);
                }
                else if (strcmp(key, "tooltip") == 0) {
                    fTooltip[zone] = formatTooltip(30, value);
                }
                else if (strcmp(key, "unit") == 0) {
                    fUnit[zone] = value;
                }
                else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
                else if (strcmp(key, "scale") == 0) {
                    if (strcmp(value, "log") == 0) {
                        fLogSet.insert(zone);
                    } else if (strcmp(value, "exp") == 0) {
                        fExpSet.insert(zone);
                    }
                }
                else if (strcmp(key, "style") == 0) {
                    if (strcmp(value, "knob") == 0) {
                        fKnobSet.insert(zone);
                    } else if (strcmp(value, "led") == 0) {
                        fLedSet.insert(zone);
                    } else if (strcmp(value, "numerical") == 0) {
                        fNumSet.insert(zone);
                    } else {
                        const char* p = value;
                        if (parseWord(p, "radio")) {
                            fRadioDescription[zone] = std::string(p);
                        } else if (parseWord(p, "menu")) {
                            fMenuDescription[zone] = std::string(p);
                        }
                    }
                }
            }
        }
    
};

#endif
/**************************  END  MetaDataUI.h **************************/
/************************** BEGIN ring-buffer.h **************************/
/*
  Copyright (C) 2000 Paul Davis
  Copyright (C) 2003 Rohan Drape
  Copyright (C) 2016 GRAME (renaming for internal use)

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

  ISO/POSIX C version of Paul Davis's lock free ringbuffer C++ code.
  This is safe for the case of one read thread and one write thread.
*/

#ifndef __ring_buffer__
#define __ring_buffer__

#include <stdlib.h>
#include <string.h>

#ifdef WIN32
# pragma warning (disable: 4334)
#else
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

typedef struct {
    char *buf;
    size_t len;
}
ringbuffer_data_t;

typedef struct {
    char *buf;
    volatile size_t write_ptr;
    volatile size_t read_ptr;
    size_t	size;
    size_t	size_mask;
    int	mlocked;
}
ringbuffer_t;

static ringbuffer_t *ringbuffer_create(size_t sz);
static void ringbuffer_free(ringbuffer_t *rb);
static void ringbuffer_get_read_vector(const ringbuffer_t *rb,
                                         ringbuffer_data_t *vec);
static void ringbuffer_get_write_vector(const ringbuffer_t *rb,
                                          ringbuffer_data_t *vec);
static size_t ringbuffer_read(ringbuffer_t *rb, char *dest, size_t cnt);
static size_t ringbuffer_peek(ringbuffer_t *rb, char *dest, size_t cnt);
static void ringbuffer_read_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_read_space(const ringbuffer_t *rb);
static int ringbuffer_mlock(ringbuffer_t *rb);
static void ringbuffer_reset(ringbuffer_t *rb);
static void ringbuffer_reset_size (ringbuffer_t * rb, size_t sz);
static size_t ringbuffer_write(ringbuffer_t *rb, const char *src,
                                 size_t cnt);
static void ringbuffer_write_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_write_space(const ringbuffer_t *rb);

/* Create a new ringbuffer to hold at least `sz' bytes of data. The
   actual buffer size is rounded up to the next power of two. */

static ringbuffer_t *
ringbuffer_create (size_t sz)
{
	size_t power_of_two;
	ringbuffer_t *rb;

	if ((rb = (ringbuffer_t *) malloc (sizeof (ringbuffer_t))) == NULL) {
		return NULL;
	}

	for (power_of_two = 1u; 1u << power_of_two < sz; power_of_two++);

	rb->size = 1u << power_of_two;
	rb->size_mask = rb->size;
	rb->size_mask -= 1;
	rb->write_ptr = 0;
	rb->read_ptr = 0;
	if ((rb->buf = (char *) malloc (rb->size)) == NULL) {
		free (rb);
		return NULL;
	}
	rb->mlocked = 0;

	return rb;
}

/* Free all data associated with the ringbuffer `rb'. */

static void
ringbuffer_free (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (rb->mlocked) {
		munlock (rb->buf, rb->size);
	}
#endif /* USE_MLOCK */
	free (rb->buf);
	free (rb);
}

/* Lock the data block of `rb' using the system call 'mlock'.  */

static int
ringbuffer_mlock (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (mlock (rb->buf, rb->size)) {
		return -1;
	}
#endif /* USE_MLOCK */
	rb->mlocked = 1;
	return 0;
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset (ringbuffer_t * rb)
{
	rb->read_ptr = 0;
	rb->write_ptr = 0;
    memset(rb->buf, 0, rb->size);
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset_size (ringbuffer_t * rb, size_t sz)
{
    rb->size = sz;
    rb->size_mask = rb->size;
    rb->size_mask -= 1;
    rb->read_ptr = 0;
    rb->write_ptr = 0;
}

/* Return the number of bytes available for reading. This is the
   number of bytes in front of the read pointer and behind the write
   pointer.  */

static size_t
ringbuffer_read_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return w - r;
	} else {
		return (w - r + rb->size) & rb->size_mask;
	}
}

/* Return the number of bytes available for writing. This is the
   number of bytes in front of the write pointer and behind the read
   pointer.  */

static size_t
ringbuffer_write_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		return (r - w) - 1;
	} else {
		return rb->size - 1;
	}
}

/* The copying data reader. Copy at most `cnt' bytes from `rb' to
   `dest'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_read (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[rb->read_ptr]), n1);
	rb->read_ptr = (rb->read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[rb->read_ptr]), n2);
		rb->read_ptr = (rb->read_ptr + n2) & rb->size_mask;
	}

	return to_read;
}

/* The copying data reader w/o read pointer advance. Copy at most
   `cnt' bytes from `rb' to `dest'.  Returns the actual number of bytes
   copied. */

static size_t
ringbuffer_peek (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;
	size_t tmp_read_ptr;

	tmp_read_ptr = rb->read_ptr;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = tmp_read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - tmp_read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[tmp_read_ptr]), n1);
	tmp_read_ptr = (tmp_read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[tmp_read_ptr]), n2);
	}

	return to_read;
}

/* The copying data writer. Copy at most `cnt' bytes to `rb' from
   `src'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_write (ringbuffer_t * rb, const char *src, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_write;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_write_space (rb)) == 0) {
		return 0;
	}

	to_write = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->write_ptr + to_write;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->write_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_write;
		n2 = 0;
	}

	memcpy (&(rb->buf[rb->write_ptr]), src, n1);
	rb->write_ptr = (rb->write_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (&(rb->buf[rb->write_ptr]), src + n1, n2);
		rb->write_ptr = (rb->write_ptr + n2) & rb->size_mask;
	}

	return to_write;
}

/* Advance the read pointer `cnt' places. */

static void
ringbuffer_read_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->read_ptr + cnt) & rb->size_mask;
	rb->read_ptr = tmp;
}

/* Advance the write pointer `cnt' places. */

static void
ringbuffer_write_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->write_ptr + cnt) & rb->size_mask;
	rb->write_ptr = tmp;
}

/* The non-copying data reader. `vec' is an array of two places. Set
   the values at `vec' to hold the current readable data at `rb'. If
   the readable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_read_vector (const ringbuffer_t * rb,
				 ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = w - r;
	} else {
		free_cnt = (w - r + rb->size) & rb->size_mask;
	}

	cnt2 = r + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = rb->size - r;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;

	} else {

		/* Single part vector: just the rest of the buffer */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

/* The non-copying data writer. `vec' is an array of two places. Set
   the values at `vec' to hold the current writeable data at `rb'. If
   the writeable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_write_vector (const ringbuffer_t * rb,
				  ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		free_cnt = (r - w) - 1;
	} else {
		free_cnt = rb->size - 1;
	}

	cnt2 = w + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[w]);
		vec[0].len = rb->size - w;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;
	} else {
		vec[0].buf = &(rb->buf[w]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

#endif // __ring_buffer__
/**************************  END  ring-buffer.h **************************/

/*******************************************************************************
 * GUI : Abstract Graphic User Interface
 * Provides additional mechanisms to synchronize widgets and zones. Widgets
 * should both reflect the value of a zone and allow to change this value.
 ******************************************************************************/

class uiItem;
class GUI;
struct clist;

typedef void (*uiCallback)(FAUSTFLOAT val, void* data);

/**
 * Base class for uiTypedItem: memory zones that can be grouped and synchronized, using an internal cache.
 */
struct uiItemBase
{
    
    uiItemBase(GUI* ui, FAUSTFLOAT* zone)
    {
        assert(ui);
        assert(zone);
    }
    
    virtual ~uiItemBase()
    {}
    
    /**
     * This method will be called when the value changes externally,
     * and will signal the new value to all linked uItem
     * when the value is different from the cached one.
     *
     * @param v - the new value
     */
    virtual void modifyZone(FAUSTFLOAT v) = 0;
    
    /**
     * This method will be called when the value changes externally,
     * and will signal the new value to all linked uItem
     * when the value is different from the cached one.
     *
     * @param date - the timestamp of the received value in usec
     * @param v - the new value
     */
    virtual void modifyZone(double date, FAUSTFLOAT v) {}
    
    /**
     * This method is called by the synchronisation mecanism and is expected
     * to 'reflect' the new value, by changing the Widget layout for instance,
     * or sending a message (OSC, MIDI...)
     */
    virtual void reflectZone() = 0;
    
    /**
     * Return the cached value.
     *
     * @return - the cached value
     */
    virtual double cache() = 0;
    
};

// Declared as 'static' to avoid code duplication at link time
static void deleteClist(clist* cl);

/**
 * A list containing all groupe uiItemBase objects.
 */
struct clist : public std::list<uiItemBase*>
{
    
    virtual ~clist()
    {
        deleteClist(this);
    }
        
};

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data);

typedef std::map<FAUSTFLOAT*, clist*> zmap;

typedef std::map<FAUSTFLOAT*, ringbuffer_t*> ztimedmap;

class GUI : public UI
{
		
    private:
     
        static std::list<GUI*> fGuiList;
        zmap fZoneMap;
        bool fStopped;
    
     public:
            
        GUI():fStopped(false)
        {	
            fGuiList.push_back(this);
        }
        
        virtual ~GUI() 
        {   
            // delete all items
            for (const auto& it : fZoneMap) {
                delete it.second;
            }
            // suppress 'this' in static fGuiList
            fGuiList.remove(this);
        }

        // -- registerZone(z,c) : zone management
        
        void registerZone(FAUSTFLOAT* z, uiItemBase* c)
        {
            if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
            fZoneMap[z]->push_back(c);
        }
    
        void updateZone(FAUSTFLOAT* z)
        {
            FAUSTFLOAT v = *z;
            clist* cl = fZoneMap[z];
            for (const auto& c : *cl) {
                if (c->cache() != v) c->reflectZone();
            }
        }
    
        void updateAllZones()
        {
            for (const auto& m : fZoneMap) {
                updateZone(m.first);
            }
        }
    
        static void updateAllGuis()
        {
            for (const auto& g : fGuiList) {
                g->updateAllZones();
            }
        }
    
        void addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data)
        {
            createUiCallbackItem(this, zone, foo, data);
        }

        // Start event or message processing
        virtual bool run() { return false; };
        // Stop event or message processing
        virtual void stop() { fStopped = true; }
        bool stopped() { return fStopped; }
    
        // -- widget's layouts
        
        virtual void openTabBox(const char* label) {};
        virtual void openHorizontalBox(const char* label) {}
        virtual void openVerticalBox(const char* label) {}
        virtual void closeBox() {}
        
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
    
        // Static global for timed zones, shared between all UI that will set timed values
        static ztimedmap gTimedZoneMap;

};

/**
 * User Interface Item: abstract definition.
 */
template <typename REAL>
class uiTypedItemReal : public uiItemBase
{
    protected:
        
        GUI* fGUI;
        REAL* fZone;
        REAL fCache;
        
        uiTypedItemReal(GUI* ui, REAL* zone):uiItemBase(ui, static_cast<FAUSTFLOAT*>(zone)),
        fGUI(ui), fZone(zone), fCache(REAL(-123456.654321))
        {
            ui->registerZone(zone, this);
        }
        
    public:
        
        virtual ~uiTypedItemReal()
        {}
    
        void modifyZone(REAL v)
        {
            fCache = v;
            if (*fZone != v) {
                *fZone = v;
                fGUI->updateZone(fZone);
            }
        }
    
        double cache() { return fCache; }
    
};

class uiItem : public uiTypedItemReal<FAUSTFLOAT> {
    
    protected:
    
        uiItem(GUI* ui, FAUSTFLOAT* zone):uiTypedItemReal<FAUSTFLOAT>(ui, zone)
        {}

    public:

        virtual ~uiItem() 
        {}

		void modifyZone(FAUSTFLOAT v)
		{
			fCache = v;
			if (*fZone != v) {
				*fZone = v;
				fGUI->updateZone(fZone);
			}
		}

};

/**
 * Base class for items with a value converter.
 */
struct uiConverter {
    
    ValueConverter* fConverter;
    
    uiConverter(MetaDataUI::Scale scale, FAUSTFLOAT umin, FAUSTFLOAT umax, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
    {
        // Select appropriate converter according to scale mode
        if (scale == MetaDataUI::kLog) {
            fConverter = new LogValueConverter(umin, umax, fmin, fmax);
        } else if (scale == MetaDataUI::kExp) {
            fConverter = new ExpValueConverter(umin, umax, fmin, fmax);
        } else {
            fConverter = new LinearValueConverter(umin, umax, fmin, fmax);
        }
    }
    
    virtual ~uiConverter()
    {
        delete fConverter;
    }
};

/**
 * User Interface item owned (and so deleted) by external code.
 */
class uiOwnedItem : public uiItem {
    
    protected:
    
        uiOwnedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
    
     public:
    
        virtual ~uiOwnedItem()
        {}
    
        virtual void reflectZone() {}
};

/**
 * Callback Item.
 */
class uiCallbackItem : public uiItem {
    
    protected:
    
        uiCallback fCallback;
        void* fData;
    
    public:
    
        uiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
        : uiItem(ui, zone), fCallback(foo), fData(data) {}
        
        virtual void reflectZone() 
        {		
            FAUSTFLOAT v = *fZone;
            fCache = v; 
            fCallback(v, fData);	
        }
};

/**
 *  For timestamped control.
 */
struct DatedControl {
    
    double fDate;
    FAUSTFLOAT fValue;
    
    DatedControl(double d = 0., FAUSTFLOAT v = FAUSTFLOAT(0)):fDate(d), fValue(v) {}
    
};

/**
 * Base class for timed items.
 */
class uiTimedItem : public uiItem
{
    
    protected:
        
        bool fDelete;
        
    public:
    
        using uiItem::modifyZone;
        
        uiTimedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {
            if (GUI::gTimedZoneMap.find(fZone) == GUI::gTimedZoneMap.end()) {
                GUI::gTimedZoneMap[fZone] = ringbuffer_create(8192);
                fDelete = true;
            } else {
                fDelete = false;
            }
        }
        
        virtual ~uiTimedItem()
        {
            ztimedmap::iterator it;
            if (fDelete && ((it = GUI::gTimedZoneMap.find(fZone)) != GUI::gTimedZoneMap.end())) {
                ringbuffer_free((*it).second);
                GUI::gTimedZoneMap.erase(it);
            }
        }
        
        virtual void modifyZone(double date, FAUSTFLOAT v)
        {
            size_t res;
            DatedControl dated_val(date, v);
            if ((res = ringbuffer_write(GUI::gTimedZoneMap[fZone], (const char*)&dated_val, sizeof(DatedControl))) != sizeof(DatedControl)) {
                fprintf(stderr, "ringbuffer_write error DatedControl\n");
            }
        }
    
};

/**
 * Allows to group a set of zones.
 */
class uiGroupItem : public uiItem
{
    protected:
    
        std::vector<FAUSTFLOAT*> fZoneMap;

    public:
    
        uiGroupItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
        virtual ~uiGroupItem() 
        {}
        
        virtual void reflectZone() 
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            
            // Update all zones of the same group
            for (const auto& it : fZoneMap) {
                *it = v;
            }
        }
        
        void addZone(FAUSTFLOAT* zone) { fZoneMap.push_back(zone); }

};

// Cannot be defined as method in the classes.

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
{
    new uiCallbackItem(ui, zone, foo, data);
}

static void deleteClist(clist* cl)
{
    for (const auto& it : *cl) {
        // This specific code is only used in JUCE context. TODO: use proper 'shared_ptr' based memory management.
    #if defined(JUCE_32BIT) || defined(JUCE_64BIT)
        uiOwnedItem* owned = dynamic_cast<uiOwnedItem*>(it);
        // owned items are deleted by external code
        if (!owned) {
            delete it;
        }
    #else
        delete it;
    #endif
    }
}

#endif
/**************************  END  GUI.h **************************/
/************************** BEGIN JSONUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef FAUST_JSONUI_H
#define FAUST_JSONUI_H

#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <limits>


/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

template <typename REAL>
class JSONUIReal : public PathBuilder, public Meta, public UIReal<REAL>
{

    protected:
    
        std::stringstream fUI;
        std::stringstream fMeta;
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        std::string fVersion;           // Compiler version
        std::string fCompileOptions;    // Compilation options
        std::vector<std::string> fLibraryList;
        std::vector<std::string> fIncludePathnames;
        std::string fName;
        std::string fFileName;
        std::string fExpandedCode;
        std::string fSHAKey;
        int fDSPSize;                   // In bytes
        std::map<std::string, int> fPathTable;
        bool fExtended;
    
        char fCloseUIPar;
        char fCloseMetaPar;
        int fTab;
    
        int fInputs, fOutputs, fSRIndex;
         
        void tab(int n, std::ostream& fout)
        {
            fout << '\n';
            while (n-- > 0) {
                fout << '\t';
            }
        }
    
        std::string flatten(const std::string& src)
        {
            std::string dst;
            for (size_t i = 0; i < src.size(); i++) {
                switch (src[i]) {
                    case '\n':
                    case '\t':
                        break;
                    default:
                        dst += src[i];
                        break;
                }
            }
            return dst;
        }
    
        void addMeta(int tab_val, bool quote = true)
        {
            if (fMetaAux.size() > 0) {
                tab(tab_val, fUI); fUI << "\"meta\": [";
                std::string sep = "";
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    fUI << sep;
                    tab(tab_val + 1, fUI); fUI << "{ \"" << fMetaAux[i].first << "\": \"" << fMetaAux[i].second << "\" }";
                    sep = ",";
                }
                tab(tab_val, fUI); fUI << ((quote) ? "],": "]");
                fMetaAux.clear();
            }
        }
    
        int getAddressIndex(const std::string& path)
        {
            return (fPathTable.find(path) != fPathTable.end()) ? fPathTable[path] : -1;
        }
      
     public:
     
        JSONUIReal(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const std::map<std::string, int>& path_table)
        {
            init(name, filename, inputs, outputs, sr_index, sha_key, dsp_code, version, compile_options, library_list, include_pathnames, size, path_table);
        }

        JSONUIReal(const std::string& name, const std::string& filename, int inputs, int outputs)
        {
            init(name, filename, inputs, outputs, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }

        JSONUIReal(int inputs, int outputs)
        {
            init("", "", inputs, outputs, -1, "", "","", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }
        
        JSONUIReal()
        {
            init("", "", -1, -1, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }
 
        virtual ~JSONUIReal() {}
        
        void setInputs(int inputs) { fInputs = inputs; }
        void setOutputs(int outputs) { fOutputs = outputs; }
    
        void setSRIndex(int sr_index) { fSRIndex = sr_index; }
    
        // Init may be called multiple times so fMeta and fUI are reinitialized
        void init(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const std::map<std::string, int>& path_table,
                  bool extended = false)
        {
            fTab = 1;
            fExtended = extended;
            if (fExtended) {
                fUI << std::setprecision(std::numeric_limits<REAL>::max_digits10);
                fMeta << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            
            // Start Meta generation
            fMeta.str("");
            tab(fTab, fMeta); fMeta << "\"meta\": [";
            fCloseMetaPar = ' ';
            
            // Start UI generation
            fUI.str("");
            tab(fTab, fUI); fUI << "\"ui\": [";
            fCloseUIPar = ' ';
            fTab += 1;
            
            fName = name;
            fFileName = filename;
            fInputs = inputs;
            fOutputs = outputs;
            fSRIndex = sr_index;
            fExpandedCode = dsp_code;
            fSHAKey = sha_key;
            fDSPSize = size;
            fPathTable = path_table;
            fVersion = version;
            fCompileOptions = compile_options;
            fLibraryList = library_list;
            fIncludePathnames = include_pathnames;
        }
   
        // -- widget's layouts
    
        virtual void openGenericGroup(const char* label, const char* name)
        {
            pushLabel(label);
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"items\": [";
            fCloseUIPar = ' ';
            fTab += 1;
        }

        virtual void openTabBox(const char* label)
        {
            openGenericGroup(label, "tgroup");
        }
    
        virtual void openHorizontalBox(const char* label)
        {
            openGenericGroup(label, "hgroup");
        }
    
        virtual void openVerticalBox(const char* label)
        {
            openGenericGroup(label, "vgroup");
        }
    
        virtual void closeBox()
        {
            popLabel();
            fTab -= 1;
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        // -- active widgets
  
        virtual void addGenericButton(const char* label, const char* name)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ((fMetaAux.size() > 0) ? "," : "");
            } else {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fMetaAux.size() > 0) ? "," : "");
            }
            addMeta(fTab, false);
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "button");
        }
    
        virtual void addCheckButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "checkbox");
        }

        virtual void addGenericEntry(const char* label, const char* name, REAL init, REAL min, REAL max, REAL step)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"init\": " << init << ",";
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max << ",";
            tab(fTab, fUI); fUI << "\"step\": " << step;
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "vslider", init, min, max, step);
        }
    
        virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "hslider", init, min, max, step);
        }
    
        virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "nentry", init, min, max, step);
        }

        // -- passive widgets
    
        virtual void addGenericBargraph(const char* label, const char* name, REAL min, REAL max) 
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max;
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) 
        {
            addGenericBargraph(label, "hbargraph", min, max);
        }
    
        virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max)
        {
            addGenericBargraph(label, "vbargraph", min, max);
        }
    
        virtual void addSoundfile(const char* label, const char* url, Soundfile** zone)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << "soundfile" << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab, fUI); fUI << "\"url\": \"" << url << "\"" << ",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fPathTable.size() > 0) ? "," : "");
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path);
            }
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        // -- metadata declarations

        virtual void declare(REAL* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
    
        // Meta interface
        virtual void declare(const char* key, const char* value)
        {
            fMeta << fCloseMetaPar;
            // fName found in metadata
            if ((strcmp(key, "name") == 0) && (fName == "")) fName = value;
            // fFileName found in metadata
            if ((strcmp(key, "filename") == 0) && (fFileName == "")) fFileName = value;
            tab(fTab, fMeta); fMeta << "{ " << "\"" << key << "\"" << ": " << "\"" << value << "\" }";
            fCloseMetaPar = ',';
        }
    
        std::string JSON(bool flat = false)
        {
            fTab = 0;
            std::stringstream JSON;
            if (fExtended) {
                JSON << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            JSON << "{";
            fTab += 1;
            tab(fTab, JSON); JSON << "\"name\": \"" << fName << "\",";
            tab(fTab, JSON); JSON << "\"filename\": \"" << fFileName << "\",";
            if (fVersion != "") { tab(fTab, JSON); JSON << "\"version\": \"" << fVersion << "\","; }
            if (fCompileOptions != "") { tab(fTab, JSON); JSON << "\"compile_options\": \"" <<  fCompileOptions << "\","; }
            if (fLibraryList.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"library_list\": [";
                for (size_t i = 0; i < fLibraryList.size(); i++) {
                    JSON << "\"" << fLibraryList[i] << "\"";
                    if (i < (fLibraryList.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fIncludePathnames.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"include_pathnames\": [";
                for (size_t i = 0; i < fIncludePathnames.size(); i++) {
                    JSON << "\"" << fIncludePathnames[i] << "\"";
                    if (i < (fIncludePathnames.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fDSPSize != -1) { tab(fTab, JSON); JSON << "\"size\": " << fDSPSize << ","; }
            if (fSHAKey != "") { tab(fTab, JSON); JSON << "\"sha_key\": \"" << fSHAKey << "\","; }
            if (fExpandedCode != "") { tab(fTab, JSON); JSON << "\"code\": \"" << fExpandedCode << "\","; }
            tab(fTab, JSON); JSON << "\"inputs\": " << fInputs << ",";
            tab(fTab, JSON); JSON << "\"outputs\": " << fOutputs << ",";
            if (fSRIndex != -1) { tab(fTab, JSON); JSON << "\"sr_index\": " << fSRIndex << ","; }
            tab(fTab, fMeta); fMeta << "],";
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            if (fCloseMetaPar == ',') { // If "declare" has been called, fCloseMetaPar state is now ','
                JSON << fMeta.str() << fUI.str();
            } else {
                JSON << fUI.str();
            }
            tab(fTab, JSON); JSON << "}";
            return (flat) ? flatten(JSON.str()) : JSON.str();
        }
    
};

// Externally available class using FAUSTFLOAT

struct JSONUI : public JSONUIReal<FAUSTFLOAT>, public UI
{
    
    JSONUI(const std::string& name,
           const std::string& filename,
           int inputs,
           int outputs,
           int sr_index,
           const std::string& sha_key,
           const std::string& dsp_code,
           const std::string& version,
           const std::string& compile_options,
           const std::vector<std::string>& library_list,
           const std::vector<std::string>& include_pathnames,
           int size,
           const std::map<std::string, int>& path_table):
    JSONUIReal<FAUSTFLOAT>(name, filename,
                          inputs, outputs,
                          sr_index,
                          sha_key, dsp_code,
                          version, compile_options,
                          library_list, include_pathnames,
                          size, path_table)
    {}
    
    JSONUI(const std::string& name, const std::string& filename, int inputs, int outputs):
    JSONUIReal<FAUSTFLOAT>(name, filename, inputs, outputs)
    {}
    
    JSONUI(int inputs, int outputs):JSONUIReal<FAUSTFLOAT>(inputs, outputs)
    {}
    
    JSONUI():JSONUIReal<FAUSTFLOAT>()
    {}

    virtual void openTabBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openTabBox(label);
    }
    virtual void openHorizontalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openHorizontalBox(label);
    }
    virtual void openVerticalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openVerticalBox(label);
    }
    virtual void closeBox()
    {
        JSONUIReal<FAUSTFLOAT>::closeBox();
    }
    
    // -- active widgets
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addButton(label, zone);
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addCheckButton(label, zone);
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalSlider(label, zone, init, min, max, step);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalSlider(label, zone, init, min, max, step);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addNumEntry(label, zone, init, min, max, step);
    }
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalBargraph(label, zone, min, max);
    }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalBargraph(label, zone, min, max);
    }
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone)
    {
        JSONUIReal<FAUSTFLOAT>::addSoundfile(label, filename, sf_zone);
    }
    
    // -- metadata declarations
    
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(zone, key, val);
    }

    virtual void declare(const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(key, val);
    }

    virtual ~JSONUI() {}
    
};

#endif // FAUST_JSONUI_H
/**************************  END  JSONUI.h **************************/
/************************** BEGIN midi.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __midi__
#define __midi__

#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

class MapUI;

/**
 * A timestamped short MIDI message used with SOUL.
 */

// Force contiguous memory layout
#pragma pack (push, 1)
struct MIDIMessage
{
    uint32_t frameIndex;
    uint8_t byte0, byte1, byte2;
};
#pragma pack (pop)

/**
 * For timestamped MIDI messages.
 */
struct DatedMessage {
    
    double fDate;
    unsigned char fBuffer[3];
    size_t fSize;
    
    DatedMessage(double date, unsigned char* buffer, size_t size)
    :fDate(date), fSize(size)
    {
        assert(size <= 3);
        memcpy(fBuffer, buffer, size);
    }
    
    DatedMessage():fDate(0.0), fSize(0)
    {}
    
};

/**
 * MIDI processor definition.
 *
 * MIDI input or output handling classes will implement this interface,
 * so the same method names (keyOn, keyOff, ctrlChange...) will be used either
 * when decoding MIDI input or encoding MIDI output events.
 * MIDI channel is numbered in [0..15] in this layer.
 */
class midi {

    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual MapUI* keyOn(double, int channel, int pitch, int velocity)
        {
            return keyOn(channel, pitch, velocity);
        }
        
        virtual void keyOff(double, int channel, int pitch, int velocity = 0)
        {
            keyOff(channel, pitch, velocity);
        }
    
        virtual void keyPress(double, int channel, int pitch, int press)
        {
            keyPress(channel, pitch, press);
        }
        
        virtual void chanPress(double date, int channel, int press)
        {
            chanPress(channel, press);
        }
    
        virtual void pitchWheel(double, int channel, int wheel)
        {
            pitchWheel(channel, wheel);
        }
           
        virtual void ctrlChange(double, int channel, int ctrl, int value)
        {
            ctrlChange(channel, ctrl, value);
        }
    
        virtual void ctrlChange14bits(double, int channel, int ctrl, int value)
        {
            ctrlChange14bits(channel, ctrl, value);
        }
    
        virtual void rpn(double, int channel, int ctrl, int value)
        {
            rpn(channel, ctrl, value);
        }

        virtual void progChange(double, int channel, int pgm)
        {
            progChange(channel, pgm);
        }
    
        virtual void sysEx(double, std::vector<unsigned char>& message)
        {
            sysEx(message);
        }

        // MIDI sync
        virtual void startSync(double date)  {}
        virtual void stopSync(double date)   {}
        virtual void clock(double date)  {}

        // Standard MIDI API
        virtual MapUI* keyOn(int channel, int pitch, int velocity)      { return nullptr; }
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void rpn(int channel, int ctrl, int value)              {}
        virtual void pitchWheel(int channel, int wheel)                 {}
        virtual void progChange(int channel, int pgm)                   {}
        virtual void sysEx(std::vector<unsigned char>& message)         {}

        enum MidiStatus {
            // channel voice messages
            MIDI_NOTE_OFF = 0x80,
            MIDI_NOTE_ON = 0x90,
            MIDI_CONTROL_CHANGE = 0xB0,
            MIDI_PROGRAM_CHANGE = 0xC0,
            MIDI_PITCH_BEND = 0xE0,
            MIDI_AFTERTOUCH = 0xD0,         // aka channel pressure
            MIDI_POLY_AFTERTOUCH = 0xA0,    // aka key pressure
            MIDI_CLOCK = 0xF8,
            MIDI_START = 0xFA,
            MIDI_CONT = 0xFB,
            MIDI_STOP = 0xFC,
            MIDI_SYSEX_START = 0xF0,
            MIDI_SYSEX_STOP = 0xF7
        };

        enum MidiCtrl {
            ALL_NOTES_OFF = 123,
            ALL_SOUND_OFF = 120
        };
    
        enum MidiNPN {
            PITCH_BEND_RANGE = 0
        };

};

/**
 * A class to decode NRPN and RPN messages, adapted from JUCE forum message:
 * https://forum.juce.com/t/14bit-midi-controller-support/11517
 */
class MidiNRPN {
    
    private:
    
        bool ctrlnew;
        int ctrlnum;
        int ctrlval;
        
        int nrpn_lsb, nrpn_msb;
        int data_lsb, data_msb;
        
        enum
        {
            midi_nrpn_lsb = 98,
            midi_nrpn_msb = 99,
            midi_rpn_lsb  = 100,
            midi_rpn_msb  = 101,
            midi_data_lsb = 38,
            midi_data_msb = 6
        };
    
    public:
        
        MidiNRPN(): ctrlnew(false), nrpn_lsb(-1), nrpn_msb(-1), data_lsb(-1), data_msb(-1)
        {}
        
        // return true if the message has been filtered
        bool process(int data1, int data2)
        {
            switch (data1)
            {
                case midi_nrpn_lsb: nrpn_lsb = data2; return true;
                case midi_nrpn_msb: nrpn_msb = data2; return true;
                case midi_rpn_lsb: {
                    if (data2 == 127) {
                        nrpn_lsb = data_lsb = -1;
                    } else {
                        nrpn_lsb = 0;
                        data_lsb = -1;
                    }
                    return true;
                }
                case midi_rpn_msb: {
                    if (data2 == 127) {
                        nrpn_msb = data_msb = -1;
                    } else {
                        nrpn_msb = 0;
                        data_msb = -1;
                    }
                    return true;
                }
                case midi_data_lsb:
                case midi_data_msb:
                {
                    if (data1 == midi_data_msb) {
                        if (nrpn_msb < 0) {
                            return false;
                        }
                        data_msb = data2;
                    } else { // midi_data_lsb
                        if (nrpn_lsb < 0) {
                            return false;
                        }
                        data_lsb = data2;
                    }
                    if (data_lsb >= 0 && data_msb >= 0) {
                        ctrlnum = (nrpn_msb << 7) | nrpn_lsb;
                        ctrlval = (data_msb << 7) | data_lsb;
                        data_lsb = data_msb = -1;
                        nrpn_msb = nrpn_lsb = -1;
                        ctrlnew = true;
                    }
                    return true;
                }
                default: return false;
            };
        }
        
        bool hasNewNRPN() { bool res = ctrlnew; ctrlnew = false; return res; }
        
        // results in [0, 16383]
        int getCtrl() const { return ctrlnum; }
        int getVal() const { return ctrlval; }
    
};

/**
 * A pure interface for MIDI handlers that can send/receive MIDI messages to/from 'midi' objects.
 */
struct midi_interface {
    virtual void addMidiIn(midi* midi_dsp)      = 0;
    virtual void removeMidiIn(midi* midi_dsp)   = 0;
    virtual ~midi_interface() {}
};

/****************************************************
 * Base class for MIDI input handling.
 *
 * Shared common code used for input handling:
 * - decoding Real-Time messages: handleSync
 * - decoding one data byte messages: handleData1
 * - decoding two data byte messages: handleData2
 * - getting ready messages in polling mode
 ****************************************************/
class midi_handler : public midi, public midi_interface {

    protected:

        std::vector<midi*> fMidiInputs;
        std::string fName;
        MidiNRPN fNRPN;
    
        int range(int min, int max, int val) { return (val < min) ? min : ((val >= max) ? max : val); }
  
    public:

        midi_handler(const std::string& name = "MIDIHandler"):midi_interface(), fName(name) {}
        virtual ~midi_handler() {}

        void addMidiIn(midi* midi_dsp) { if (midi_dsp) fMidiInputs.push_back(midi_dsp); }
        void removeMidiIn(midi* midi_dsp)
        {
            std::vector<midi*>::iterator it = std::find(fMidiInputs.begin(), fMidiInputs.end(), midi_dsp);
            if (it != fMidiInputs.end()) {
                fMidiInputs.erase(it);
            }
        }

        // Those 2 methods have to be implemented by subclasses
        virtual bool startMidi() { return true; }
        virtual void stopMidi() {}
    
        void setName(const std::string& name) { fName = name; }
        std::string getName() { return fName; }
    
        // To be used in polling mode
        virtual int recvMessages(std::vector<MIDIMessage>* message) { return 0; }
        virtual void sendMessages(std::vector<MIDIMessage>* message, int count) {}
    
        // MIDI Real-Time
        void handleClock(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->clock(time);
            }
        }
        
        void handleStart(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->startSync(time);
            }
        }
        
        void handleStop(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->stopSync(time);
            }
        }
    
        void handleSync(double time, int type)
        {
            if (type == MIDI_CLOCK) {
                handleClock(time);
            // We can consider start and continue as identical messages
            } else if ((type == MIDI_START) || (type == MIDI_CONT)) {
                handleStart(time);
            } else if (type == MIDI_STOP) {
                handleStop(time);
            }
        }
    
        // MIDI 1 data
        void handleProgChange(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->progChange(time, channel, data1);
            }
        }
    
        void handleAfterTouch(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->chanPress(time, channel, data1);
            }
        }

        void handleData1(double time, int type, int channel, int data1)
        {
            if (type == MIDI_PROGRAM_CHANGE) {
                handleProgChange(time, channel, data1);
            } else if (type == MIDI_AFTERTOUCH) {
                handleAfterTouch(time, channel, data1);
            }
        }
    
        // MIDI 2 datas
        void handleKeyOff(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyOff(time, channel, data1, data2);
            }
        }
        
        void handleKeyOn(double time, int channel, int data1, int data2)
        {
            if (data2 == 0) {
                handleKeyOff(time, channel, data1, data2);
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOn(time, channel, data1, data2);
                }
            }
        }
    
        void handleCtrlChange(double time, int channel, int data1, int data2)
        {
            // Special processing for NRPN and RPN
            if (fNRPN.process(data1, data2)) {
                if (fNRPN.hasNewNRPN()) {
                    for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                        fMidiInputs[i]->rpn(time, channel, fNRPN.getCtrl(), fNRPN.getVal());
                    }
                }
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                }
            }
        }
        
        void handlePitchWheel(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, (data2 << 7) + data1);
            }
        }
    
        void handlePitchWheel(double time, int channel, int bend)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, bend);
            }
        }
        
        void handlePolyAfterTouch(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyPress(time, channel, data1, data2);
            }
        }
  
        void handleData2(double time, int type, int channel, int data1, int data2)
        {
            if (type == MIDI_NOTE_OFF) {
                handleKeyOff(time, channel,  data1, data2);
            } else if (type == MIDI_NOTE_ON) {
                handleKeyOn(time, channel, data1, data2);
            } else if (type == MIDI_CONTROL_CHANGE) {
                handleCtrlChange(time, channel, data1, data2);
            } else if (type == MIDI_PITCH_BEND) {
                handlePitchWheel(time, channel, data1, data2);
            } else if (type == MIDI_POLY_AFTERTOUCH) {
                handlePolyAfterTouch(time, channel, data1, data2);
            }
        }
    
        // SysEx
        void handleSysex(double time, std::vector<unsigned char>& message)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->sysEx(time, message);
            }
        }
    
        void handleMessage(double time, int type, std::vector<unsigned char>& message)
        {
            if (type == MIDI_SYSEX_START) {
                handleSysex(time, message);
            }
        }
  
};

#endif // __midi__
/**************************  END  midi.h **************************/

#ifdef _MSC_VER
#define gsscanf sscanf_s
#else
#define gsscanf sscanf
#endif

/**
 * Helper code for MIDI meta and polyphonic 'nvoices' parsing.
 */
struct MidiMeta : public Meta, public std::map<std::string, std::string> {
    
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
    
    const std::string get(const char* key, const char* def)
    {
        return (this->find(key) != this->end()) ? (*this)[key] : def;
    }
    
    static void analyse(base_dsp* mono_dsp, bool& midi_sync, int& nvoices)
    {
        JSONUI jsonui;
        mono_dsp->buildUserInterface(&jsonui);
        std::string json = jsonui.JSON();
        midi_sync = ((json.find("midi") != std::string::npos) &&
                     ((json.find("start") != std::string::npos) ||
                      (json.find("stop") != std::string::npos) ||
                      (json.find("clock") != std::string::npos) ||
                      (json.find("timestamp") != std::string::npos)));
    
    #if defined(NVOICES) && NVOICES!=NUM_VOICES
        nvoices = NVOICES;
    #else
        MidiMeta meta;
        mono_dsp->metadata(&meta);
        bool found_voices = false;
        // If "options" metadata is used
        std::string options = meta.get("options", "");
        if (options != "") {
            std::map<std::string, std::string> metadata;
            std::string res;
            MetaDataUI::extractMetadata(options, res, metadata);
            if (metadata.find("nvoices") != metadata.end()) {
                nvoices = std::atoi(metadata["nvoices"].c_str());
                found_voices = true;
            }
        }
        // Otherwise test for "nvoices" metadata
        if (!found_voices) {
            std::string numVoices = meta.get("nvoices", "0");
            nvoices = std::atoi(numVoices.c_str());
        }
        nvoices = std::max<int>(0, nvoices);
    #endif
    }
    
    static bool checkPolyphony(base_dsp* mono_dsp)
    {
        MapUI map_ui;
        mono_dsp->buildUserInterface(&map_ui);
        bool has_freq = false;
        bool has_gate = false;
        bool has_gain = false;
        for (int i = 0; i < map_ui.getParamsCount(); i++) {
            std::string path = map_ui.getParamAddress(i);
            has_freq |= MapUI::endsWith(path, "/freq");
            has_gate |= MapUI::endsWith(path, "/gate");
            has_gain |= MapUI::endsWith(path, "/gain");
        }
        return (has_freq && has_gate && has_gain);
    }
    
};

/**
 * uiMidi : Faust User Interface
 * This class decodes MIDI meta data and maps incoming MIDI messages to them.
 * Currently ctrlChange, keyOn/keyOff, keyPress, progChange, chanPress, pitchWheel/pitchBend
 * start/stop/clock meta data is handled.
 * MIDI channel is numbered in [1..16] in this layer.
 * Channel 0 means "all channels" when receiving or sending.
 */
class uiMidi {
    
    friend class MidiUI;
    
    protected:
        
        midi* fMidiOut;
        bool fInputCtrl;
        int fChan;
    
        bool inRange(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT v) { return (min <= v && v <= max); }
    
    public:
        
        uiMidi(midi* midi_out, bool input, int chan = 0):fMidiOut(midi_out), fInputCtrl(input), fChan(chan)
        {}
        virtual ~uiMidi()
        {}

};

/**
 * Base class for MIDI aware UI items.
 */
class uiMidiItem : public uiMidi, public uiItem {
    
    public:
        
        uiMidiItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = 0)
            :uiMidi(midi_out, input, chan), uiItem(ui, zone)
        {}
        virtual ~uiMidiItem()
        {}
    
        virtual void reflectZone() {}
    
};

/**
 * Base class for MIDI aware UI items with timestamp support.
 */
class uiMidiTimedItem : public uiMidi, public uiTimedItem {
    
    public:
        
        uiMidiTimedItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = 0)
            :uiMidi(midi_out, input, chan), uiTimedItem(ui, zone)
        {}
        virtual ~uiMidiTimedItem()
        {}
    
        virtual void reflectZone() {}
    
};

/**
 * MIDI sync.
 */
class uiMidiStart : public uiMidiTimedItem
{
  
    public:
    
        uiMidiStart(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStart()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->startSync(0);
            }
        }
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
        
};

class uiMidiStop : public uiMidiTimedItem {
  
    public:
    
        uiMidiStop(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStop()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(1)) {
                fMidiOut->stopSync(0);
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
};

class uiMidiClock : public uiMidiTimedItem {

    private:
        
        bool fState;
  
    public:
    
        uiMidiClock(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fState(false)
        {}
        virtual ~uiMidiClock()
        {}
    
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->clock(0);
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                fState = !fState;
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fState));
            }
        }

};

/**
 * Standard MIDI events.
 */

/**
 * uiMidiProgChange uses the [min...max] range.
 */
class uiMidiProgChange : public uiMidiTimedItem {
    
    public:
    
        FAUSTFLOAT fMin, fMax;
    
        uiMidiProgChange(midi* midi_out, GUI* ui, FAUSTFLOAT* zone,
                         FAUSTFLOAT min, FAUSTFLOAT max,
                         bool input = true, int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fMin(min), fMax(max)
        {}
        virtual ~uiMidiProgChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (inRange(fMin, fMax, v)) {
                if (fChan == 0) {
                    // Send on [0..15] channels on the MIDI layer
                    for (int chan = 0; chan < 16; chan++) {
                        fMidiOut->progChange(chan, v);
                    }
                } else {
                    fMidiOut->progChange(fChan - 1, v);
                }
            }
        }
    
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl && inRange(fMin, fMax, v)) {
                uiItem::modifyZone(v);
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl && inRange(fMin, fMax, v)) {
                uiMidiTimedItem::modifyZone(date, v);
            }
        }
        
};

/**
 * uiMidiChanPress.
 */
class uiMidiChanPress : public uiMidiTimedItem, public uiConverter {
    
    public:
    
        uiMidiChanPress(midi* midi_out, GUI* ui,
                        FAUSTFLOAT* zone,
                        FAUSTFLOAT min, FAUSTFLOAT max,
                        bool input = true,
                        MetaDataUI::Scale scale = MetaDataUI::kLin,
                        int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max)
        {}
        virtual ~uiMidiChanPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->chanPress(chan, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->chanPress(fChan - 1, fConverter->faust2ui(v));
            }
        }
    
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
        
};

/**
 * uiMidiCtrlChange does scale (kLin/kLog/kExp) mapping.
 */
class uiMidiCtrlChange : public uiMidiTimedItem, public uiConverter {
    
    private:
    
        int fCtrl;
 
    public:

        uiMidiCtrlChange(midi* midi_out, int ctrl, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fCtrl(ctrl)
        {}
        virtual ~uiMidiCtrlChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->ctrlChange(chan, fCtrl, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->ctrlChange(fChan - 1, fCtrl, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
};

class uiMidiPitchWheel : public uiMidiTimedItem {

    private:
    
        LinearValueConverter2 fConverter;
    
    public:
    
        uiMidiPitchWheel(midi* midi_out, GUI* ui, FAUSTFLOAT* zone,
                         FAUSTFLOAT min, FAUSTFLOAT max,
                         bool input = true, int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan)
        {
            if (min <= 0 && max >= 0) {
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min), 0., double(max));
            } else {
                // Degenerated case...
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min),double(min + (max - min)/FAUSTFLOAT(2)), double(max));
            }
        }
    
        virtual ~uiMidiPitchWheel()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->pitchWheel(chan, fConverter.faust2ui(v));
                }
            } else {
                fMidiOut->pitchWheel(fChan - 1, fConverter.faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void setRange(int val)
        {
            double semi = (val / 128) + ((val % 128) / 100.);
            fConverter.setMappingValues(0., 8191., 16383., -semi, 0., semi);
        }
 
};

/**
 * uiMidiKeyOn does scale (kLin/kLog/kExp) mapping for velocity.
 */
class uiMidiKeyOn : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOn;
  
    public:
    
        uiMidiKeyOn(midi* midi_out, int key, GUI* ui,
                    FAUSTFLOAT* zone,
                    FAUSTFLOAT min, FAUSTFLOAT max,
                    bool input = true,
                    MetaDataUI::Scale scale = MetaDataUI::kLin,
                    int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOn(key)
        {}
        virtual ~uiMidiKeyOn()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKeyOn, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKeyOn, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/**
 * uiMidiKeyOff does scale (kLin/kLog/kExp) mapping for velocity.
 */
class uiMidiKeyOff : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOff;
  
    public:
    
        uiMidiKeyOff(midi* midi_out, int key, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOff(key)
        {}
        virtual ~uiMidiKeyOff()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKeyOff, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKeyOff, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/**
 * uiMidiKeyPress does scale (kLin/kLog/kExp) mapping for velocity.
 */
class uiMidiKeyPress : public uiMidiTimedItem, public uiConverter {

    private:
    
        int fKey;
  
    public:
    
        uiMidiKeyPress(midi* midi_out, int key, GUI* ui,
                       FAUSTFLOAT* zone,
                       FAUSTFLOAT min, FAUSTFLOAT max,
                       bool input = true,
                       MetaDataUI::Scale scale = MetaDataUI::kLin,
                       int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKey(key)
        {}
        virtual ~uiMidiKeyPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKey, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKey, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/******************************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI metadata and maps incoming MIDI messages to them.
 * Currently ctrlChange, keyOn/keyOff, keyPress, progChange, chanPress, pitchWheel/pitchBend
 * start/stop/clock meta data are handled.
 *
 * Maps associating MIDI event ID (like each ctrl number) with all MIDI aware UI items
 * are defined and progressively filled when decoding MIDI related metadata.
 * MIDI aware UI items are used in both directions:
 *  - modifying their internal state when receving MIDI input events
 *  - sending their internal state as MIDI output events
 *******************************************************************************************/

class MidiUI : public GUI, public midi, public midi_interface, public MetaDataUI {

    // Add uiItem subclasses objects are deallocated by the inherited GUI class
    typedef std::map <int, std::vector<uiMidiCtrlChange*> > TCtrlChangeTable;
    typedef std::vector<uiMidiProgChange*>                  TProgChangeTable;
    typedef std::vector<uiMidiChanPress*>                   TChanPressTable;
    typedef std::map <int, std::vector<uiMidiKeyOn*> >      TKeyOnTable;
    typedef std::map <int, std::vector<uiMidiKeyOff*> >     TKeyOffTable;
    typedef std::map <int, std::vector<uiMidiKeyPress*> >   TKeyPressTable;
    typedef std::vector<uiMidiPitchWheel*>                  TPitchWheelTable;
    
    protected:
    
        TCtrlChangeTable fCtrlChangeTable;
        TProgChangeTable fProgChangeTable;
        TChanPressTable  fChanPressTable;
        TKeyOnTable      fKeyOnTable;
        TKeyOffTable     fKeyOffTable;
        TKeyOnTable      fKeyTable;
        TKeyPressTable   fKeyPressTable;
        TPitchWheelTable fPitchWheelTable;
        
        std::vector<uiMidiStart*> fStartTable;
        std::vector<uiMidiStop*>  fStopTable;
        std::vector<uiMidiClock*> fClockTable;
        
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        
        midi_handler* fMidiHandler;
        bool fDelete;
        bool fTimeStamp;
    
        void addGenericZone(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
        {
            if (fMetaAux.size() > 0) {
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    unsigned num;
                    unsigned chan;
                    if (fMetaAux[i].first == "midi") {
                        if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u %u", &num, &chan) == 2) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u %u", &num, &chan) == 2) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u %u", &num, &chan) == 2) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u", &num) == 1) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u %u", &num, &chan) == 2) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u", &num) == 1) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u %u", &num, &chan) == 2) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u", &num) == 1) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "pgm %u", &chan) == 1) {
                            fProgChangeTable.push_back(new uiMidiProgChange(fMidiHandler, this, zone, min, max, input, chan));
                        } else if (strcmp(fMetaAux[i].second.c_str(), "pgm") == 0) {
                            fProgChangeTable.push_back(new uiMidiProgChange(fMidiHandler, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "chanpress %u", &chan) == 1) {
                            fChanPressTable.push_back(new uiMidiChanPress(fMidiHandler, this, zone, min, max, input, getScale(zone), chan));
                        } else if ((fMetaAux[i].second == "chanpress")) {
                            fChanPressTable.push_back(new uiMidiChanPress(fMidiHandler, this, zone, min, max, input, getScale(zone)));
                        } else if ((gsscanf(fMetaAux[i].second.c_str(), "pitchwheel %u", &chan) == 1) || (gsscanf(fMetaAux[i].second.c_str(), "pitchbend %u", &chan) == 1)) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input, chan));
                        } else if ((fMetaAux[i].second == "pitchwheel") || (fMetaAux[i].second == "pitchbend")) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input));
                        // MIDI sync
                        } else if (fMetaAux[i].second == "start") {
                            fStartTable.push_back(new uiMidiStart(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "stop") {
                            fStopTable.push_back(new uiMidiStop(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "clock") {
                            fClockTable.push_back(new uiMidiClock(fMidiHandler, this, zone, input));
                        // Explicit metadata to activate 'timestamp' mode
                        } else if (fMetaAux[i].second == "timestamp") {
                            fTimeStamp = true;
                        }
                    }
                }
            }
            fMetaAux.clear();
        }
    
        template <typename TABLE>
        void updateTable1(TABLE& table, double date, int channel, int val1)
        {
            for (size_t i = 0; i < table.size(); i++) {
                int channel_aux = table[i]->fChan;
                // channel_aux == 0 means "all channels"
                if (channel_aux == 0 || channel == channel_aux - 1) {
                    if (fTimeStamp) {
                        table[i]->modifyZone(date, FAUSTFLOAT(val1));
                    } else {
                        table[i]->modifyZone(FAUSTFLOAT(val1));
                    }
                }
            }
        }
        
        template <typename TABLE>
        void updateTable2(TABLE& table, double date, int channel, int val1, int val2)
        {
            if (table.find(val1) != table.end()) {
                for (size_t i = 0; i < table[val1].size(); i++) {
                    int channel_aux = table[val1][i]->fChan;
                    // channel_aux == 0 means "all channels"
                    if (channel_aux == 0 || channel == channel_aux - 1) {
                        if (fTimeStamp) {
                            table[val1][i]->modifyZone(date, FAUSTFLOAT(val2));
                        } else {
                            table[val1][i]->modifyZone(FAUSTFLOAT(val2));
                        }
                    }
                }
            }
        }
    
    public:
    
        MidiUI(midi_handler* midi_handler, bool delete_handler = false)
        {
            fMidiHandler = midi_handler;
            fMidiHandler->addMidiIn(this);
            // TODO: use shared_ptr based implementation
            fDelete = delete_handler;
            fTimeStamp = false;
        }
 
        virtual ~MidiUI() 
        {
            // Remove from fMidiHandler
            fMidiHandler->removeMidiIn(this);
            // TODO: use shared_ptr based implementation
            if (fDelete) delete fMidiHandler;
        }
    
        bool run() { return fMidiHandler->startMidi(); }
        void stop() { fMidiHandler->stopMidi(); }
        
        void addMidiIn(midi* midi_dsp) { fMidiHandler->addMidiIn(midi_dsp); }
        void removeMidiIn(midi* midi_dsp) { fMidiHandler->removeMidiIn(midi_dsp); }
      
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericZone(zone, min, max, false);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericZone(zone, min, max, false);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            MetaDataUI::declare(zone, key, val);
            fMetaAux.push_back(std::make_pair(key, val));
        }
        
        // -- MIDI API
    
        void key(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyTable, date, channel, note, velocity);
        }
    
        MapUI* keyOn(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyOnTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOn
            key(date, channel, note, velocity);
            return nullptr;
        }
        
        void keyOff(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOffTable>(fKeyOffTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOff with a 0 velocity
            key(date, channel, note, 0);
        }
        
        void ctrlChange(double date, int channel, int ctrl, int value)
        {
            updateTable2<TCtrlChangeTable>(fCtrlChangeTable, date, channel, ctrl, value);
        }
    
        void rpn(double date, int channel, int ctrl, int value)
        {
            if (ctrl == midi::PITCH_BEND_RANGE) {
                for (size_t i = 0; i < fPitchWheelTable.size(); i++) {
                    // channel_aux == 0 means "all channels"
                    int channel_aux = fPitchWheelTable[i]->fChan;
                    if (channel_aux == 0 || channel == channel_aux - 1) {
                        fPitchWheelTable[i]->setRange(value);
                    }
                }
            }
        }
    
        void progChange(double date, int channel, int pgm)
        {
            updateTable1<TProgChangeTable>(fProgChangeTable, date, channel, pgm);
        }
        
        void pitchWheel(double date, int channel, int wheel) 
        {
            updateTable1<TPitchWheelTable>(fPitchWheelTable, date, channel, wheel);
        }
        
        void keyPress(double date, int channel, int pitch, int press) 
        {
            updateTable2<TKeyPressTable>(fKeyPressTable, date, channel, pitch, press);
        }
        
        void chanPress(double date, int channel, int press)
        {
            updateTable1<TChanPressTable>(fChanPressTable, date, channel, press);
        }
        
        void ctrlChange14bits(double date, int channel, int ctrl, int value) {}
        
        // MIDI sync
        
        void startSync(double date)
        {
            for (size_t i = 0; i < fStartTable.size(); i++) {
                fStartTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
        
        void stopSync(double date)
        {
            for (size_t i = 0; i < fStopTable.size(); i++) {
                fStopTable[i]->modifyZone(date, FAUSTFLOAT(0));
            }
        }
        
        void clock(double date)
        {
            for (size_t i = 0; i < fClockTable.size(); i++) {
                fClockTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
};

#endif // FAUST_MIDIUI_H
/**************************  END  MidiUI.h **************************/
/************************** BEGIN poly-base_dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __poly_dsp__
#define __poly_dsp__

#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>
#include <functional>
#include <ostream>
#include <sstream>
#include <vector>
#include <limits.h>
#include <float.h>
#include <assert.h>

/************************** BEGIN base_dsp-combiner.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp_combiner__
#define __dsp_combiner__

#include <string.h>
#include <string>
#include <assert.h>
#include <sstream>


// Base class and common code for binary combiners

enum Layout { kVerticalGroup, kHorizontalGroup, kTabGroup };

class dsp_binary_combiner : public base_dsp {

    protected:

        base_dsp* fDSP1;
        base_dsp* fDSP2;
        int fBufferSize;
        Layout fLayout;
        std::string fLabel;

        void buildUserInterfaceAux(UI* ui_interface)
        {
            switch (fLayout) {
                case kHorizontalGroup:
                    ui_interface->openHorizontalBox(fLabel.c_str());
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kVerticalGroup:
                    ui_interface->openVerticalBox(fLabel.c_str());
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kTabGroup:
                    ui_interface->openTabBox(fLabel.c_str());
                    ui_interface->openVerticalBox("DSP1");
                    fDSP1->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->openVerticalBox("DSP2");
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->closeBox();
                    break;
            }
        }

        FAUSTFLOAT** allocateChannels(int num)
        {
            FAUSTFLOAT** channels = new FAUSTFLOAT*[num];
            for (int chan = 0; chan < num; chan++) {
                channels[chan] = new FAUSTFLOAT[fBufferSize];
                memset(channels[chan], 0, sizeof(FAUSTFLOAT) * fBufferSize);
            }
            return channels;
        }

        void deleteChannels(FAUSTFLOAT** channels, int num)
        {
            for (int chan = 0; chan < num; chan++) {
                delete [] channels[chan];
            }
            delete [] channels;
        }

     public:

        dsp_binary_combiner(base_dsp* dsp1, base_dsp* dsp2, int buffer_size, Layout layout, const std::string& label)
        :fDSP1(dsp1), fDSP2(dsp2), fBufferSize(buffer_size), fLayout(layout), fLabel(label)
        {}

        virtual ~dsp_binary_combiner()
        {
            delete fDSP1;
            delete fDSP2;
        }

        virtual int getSampleRate()
        {
            return fDSP1->getSampleRate();
        }
        virtual void init(int sample_rate)
        {
            fDSP1->init(sample_rate);
            fDSP2->init(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            fDSP1->instanceInit(sample_rate);
            fDSP2->instanceInit(sample_rate);
        }
        virtual void instanceConstants(int sample_rate)
        {
            fDSP1->instanceConstants(sample_rate);
            fDSP2->instanceConstants(sample_rate);
        }

        virtual void instanceResetUserInterface()
        {
            fDSP1->instanceResetUserInterface();
            fDSP2->instanceResetUserInterface();
        }

        virtual void instanceClear()
        {
            fDSP1->instanceClear();
            fDSP2->instanceClear();
        }

        virtual void metadata(Meta* m)
        {
            fDSP1->metadata(m);
            fDSP2->metadata(m);
        }

};

// Combine two 'compatible' DSP in sequence

class dsp_sequencer : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Outputs;

    public:

        dsp_sequencer(base_dsp* dsp1, base_dsp* dsp2,
                      int buffer_size = 4096,
                      Layout layout = Layout::kTabGroup,
                      const std::string& label = "Sequencer")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
        }

        virtual ~dsp_sequencer()
        {
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual base_dsp* clone()
        {
            return new dsp_sequencer(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fDSP1Outputs);
            fDSP2->compute(count, fDSP1Outputs, outputs);
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

// Combine two DSP in parallel

class dsp_parallelizer : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP2Inputs;
        FAUSTFLOAT** fDSP2Outputs;

    public:

        dsp_parallelizer(base_dsp* dsp1, base_dsp* dsp2,
                     int buffer_size = 4096,
                     Layout layout = Layout::kTabGroup,
                     const std::string& label = "Parallelizer")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
            fDSP2Outputs = new FAUSTFLOAT*[fDSP2->getNumOutputs()];
        }

        virtual ~dsp_parallelizer()
        {
            delete [] fDSP2Inputs;
            delete [] fDSP2Outputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs() + fDSP2->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs() + fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual base_dsp* clone()
        {
            return new dsp_parallelizer(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, outputs);

            // Shift inputs/outputs channels for fDSP2
            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                fDSP2Inputs[chan] = inputs[fDSP1->getNumInputs() + chan];
            }
            for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                fDSP2Outputs[chan] = outputs[fDSP1->getNumOutputs() + chan];
            }

            fDSP2->compute(count, fDSP2Inputs, fDSP2Outputs);
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

// Combine two 'compatible' DSP in splitter

class dsp_splitter : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Outputs;
        FAUSTFLOAT** fDSP2Inputs;

    public:

        dsp_splitter(base_dsp* dsp1, base_dsp* dsp2,
                     int buffer_size = 4096,
                     Layout layout = Layout::kTabGroup,
                     const std::string& label = "Splitter")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
        }

        virtual ~dsp_splitter()
        {
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            delete [] fDSP2Inputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual base_dsp* clone()
        {
            return new dsp_splitter(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fDSP1Outputs);

            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                 fDSP2Inputs[chan] = fDSP1Outputs[chan % fDSP1->getNumOutputs()];
            }

            fDSP2->compute(count, fDSP2Inputs, outputs);
        }
};

// Combine two 'compatible' DSP in merger

class dsp_merger : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Inputs;
        FAUSTFLOAT** fDSP1Outputs;
        FAUSTFLOAT** fDSP2Inputs;

        void mix(int count, FAUSTFLOAT* dst, FAUSTFLOAT* src)
        {
            for (int frame = 0; frame < count; frame++) {
                dst[frame] += src[frame];
            }
        }

    public:

        dsp_merger(base_dsp* dsp1, base_dsp* dsp2,
                   int buffer_size = 4096,
                   Layout layout = Layout::kTabGroup,
                   const std::string& label = "Merger")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs());
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
        }

        virtual ~dsp_merger()
        {
            deleteChannels(fDSP1Inputs, fDSP1->getNumInputs());
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            delete [] fDSP2Inputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual base_dsp* clone()
        {
            return new dsp_merger(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, fDSP1Inputs, fDSP1Outputs);

            memset(fDSP2Inputs, 0, sizeof(FAUSTFLOAT*) * fDSP2->getNumInputs());

            for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                int mchan = chan % fDSP2->getNumInputs();
                if (fDSP2Inputs[mchan]) {
                    mix(count, fDSP2Inputs[mchan], fDSP1Outputs[chan]);
                } else {
                    fDSP2Inputs[mchan] = fDSP1Outputs[chan];
                }
            }

            fDSP2->compute(count, fDSP2Inputs, outputs);
        }
};

// Combine two 'compatible' DSP in a recursive way

class dsp_recursiver : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Inputs;
        FAUSTFLOAT** fDSP1Outputs;

        FAUSTFLOAT** fDSP2Inputs;
        FAUSTFLOAT** fDSP2Outputs;

    public:

        dsp_recursiver(base_dsp* dsp1, base_dsp* dsp2,
                       Layout layout = Layout::kTabGroup,
                       const std::string& label = "Recursiver")
        :dsp_binary_combiner(dsp1, dsp2, 1, layout, label)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs());
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = allocateChannels(fDSP2->getNumInputs());
            fDSP2Outputs = allocateChannels(fDSP2->getNumOutputs());
        }

        virtual ~dsp_recursiver()
        {
            deleteChannels(fDSP1Inputs, fDSP1->getNumInputs());
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            deleteChannels(fDSP2Inputs, fDSP2->getNumInputs());
            deleteChannels(fDSP2Outputs, fDSP2->getNumOutputs());
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs() - fDSP2->getNumOutputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual base_dsp* clone()
        {
            return new dsp_recursiver(fDSP1->clone(), fDSP2->clone(), fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int frame = 0; (frame < count); frame++) {

                for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                    fDSP1Inputs[chan][0] = fDSP2Outputs[chan][0];
                }

                for (int chan = 0; chan < fDSP1->getNumInputs() - fDSP2->getNumOutputs(); chan++) {
                    fDSP1Inputs[chan + fDSP2->getNumOutputs()][0] = inputs[chan][frame];
                }

                fDSP1->compute(1, fDSP1Inputs, fDSP1Outputs);

                for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                    outputs[chan][frame] = fDSP1Outputs[chan][0];
                }

                for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                    fDSP2Inputs[chan][0] = fDSP1Outputs[chan][0];
                }

                fDSP2->compute(1, fDSP2Inputs, fDSP2Outputs);
            }
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

/*
 Crossfade between two DSP.
 When fCrossfade = 1, the first DSP only is computed, when fCrossfade = 0,
 the second DSP only is computed, otherwise both DSPs are computed and mixed.
*/

class dsp_crossfader: public dsp_binary_combiner {

    private:
    
        FAUSTFLOAT fCrossfade;
        FAUSTFLOAT** fDSPOutputs1;
        FAUSTFLOAT** fDSPOutputs2;
    
    public:
    
        dsp_crossfader(base_dsp* dsp1, base_dsp* dsp2,
                       Layout layout = Layout::kTabGroup,
                       const std::string& label = "Crossfade")
        :dsp_binary_combiner(dsp1, dsp2, 4096, layout, label),fCrossfade(FAUSTFLOAT(0.5))
        {
            fDSPOutputs1 = allocateChannels(fDSP1->getNumOutputs());
            fDSPOutputs2 = allocateChannels(fDSP1->getNumOutputs());
        }
    
        virtual ~dsp_crossfader()
        {
            deleteChannels(fDSPOutputs1, fDSP1->getNumInputs());
            deleteChannels(fDSPOutputs2, fDSP1->getNumOutputs());
        }
    
        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs(); }

        void buildUserInterface(UI* ui_interface)
        {
            switch (fLayout) {
                case kHorizontalGroup:
                    ui_interface->openHorizontalBox(fLabel.c_str());
                    ui_interface->addHorizontalSlider("Crossfade", &fCrossfade, FAUSTFLOAT(0.5), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kVerticalGroup:
                    ui_interface->openVerticalBox(fLabel.c_str());
                    ui_interface->addHorizontalSlider("Crossfade", &fCrossfade, FAUSTFLOAT(0.5), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kTabGroup:
                    ui_interface->openTabBox(fLabel.c_str());
                    ui_interface->openVerticalBox("Crossfade");
                    ui_interface->addHorizontalSlider("Crossfade", &fCrossfade, FAUSTFLOAT(0.5), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
                    ui_interface->closeBox();
                    ui_interface->openVerticalBox("DSP1");
                    fDSP1->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->openVerticalBox("DSP2");
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->closeBox();
                    break;
            }
        }
    
        virtual base_dsp* clone()
        {
            return new dsp_crossfader(fDSP1->clone(), fDSP2->clone(), fLayout, fLabel);
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            if (fCrossfade == FAUSTFLOAT(1)) {
                fDSP1->compute(count, inputs, outputs);
            } else if (fCrossfade == FAUSTFLOAT(0)) {
                fDSP2->compute(count, inputs, outputs);
            } else {
                // Compute each effect
                fDSP1->compute(count, inputs, fDSPOutputs1);
                fDSP2->compute(count, inputs, fDSPOutputs2);
                // Mix between the two effects
                FAUSTFLOAT gain1 = fCrossfade;
                FAUSTFLOAT gain2 = FAUSTFLOAT(1) - gain1;
                for (int frame = 0; (frame < count); frame++) {
                    for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                        outputs[chan][frame] = fDSPOutputs1[chan][frame] * gain1 + fDSPOutputs2[chan][frame] * gain2;
                    }
                }
            }
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

#ifndef __dsp_algebra_api__
#define __dsp_algebra_api__

// DSP algebra API
/*
 Each operation takes two DSP and a optional Layout and Label parameters, returns the combined DSPs, or null if failure with an error message.
 */

static base_dsp* createDSPSequencer(base_dsp* dsp1, base_dsp* dsp2,
                               std::string& error,
                               Layout layout = Layout::kTabGroup,
                               const std::string& label = "Sequencer")
{
    if (dsp1->getNumOutputs() != dsp2->getNumInputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_sequencer : the number of outputs ("
                  << dsp1->getNumOutputs() << ") of A "
                  << "must be equal to the number of inputs (" << dsp2->getNumInputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    }
}

static base_dsp* createDSPParallelizer(base_dsp* dsp1, base_dsp* dsp2,
                                  std::string& error,
                                  Layout layout = Layout::kTabGroup,
                                  const std::string& label = "Parallelizer")
{
    return new dsp_parallelizer(dsp1, dsp2, 4096, layout, label);
}

static base_dsp* createDSPSplitter(base_dsp* dsp1, base_dsp* dsp2, std::string& error, Layout layout = Layout::kTabGroup, const std::string& label = "Splitter")
{
    if (dsp1->getNumOutputs() == 0) {
        error = "Connection error in dsp_splitter : the first expression has no outputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() == 0) {
        error = "Connection error in dsp_splitter : the second expression has no inputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() % dsp1->getNumOutputs() != 0) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_splitter : the number of outputs (" << dsp1->getNumOutputs()
                  << ") of the first expression should be a divisor of the number of inputs ("
                  << dsp2->getNumInputs()
                  << ") of the second expression" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp2->getNumInputs() == dsp1->getNumOutputs()) {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    } else {
        return new dsp_splitter(dsp1, dsp2, 4096, layout, label);
    }
}

static base_dsp* createDSPMerger(base_dsp* dsp1, base_dsp* dsp2,
                            std::string& error,
                            Layout layout = Layout::kTabGroup,
                            const std::string& label = "Merger")
{
    if (dsp1->getNumOutputs() == 0) {
        error = "Connection error in dsp_merger : the first expression has no outputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() == 0) {
        error = "Connection error in dsp_merger : the second expression has no inputs\n";
        return nullptr;
    } else if (dsp1->getNumOutputs() % dsp2->getNumInputs() != 0) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_merger : the number of outputs (" << dsp1->getNumOutputs()
                  << ") of the first expression should be a multiple of the number of inputs ("
                  << dsp2->getNumInputs()
                  << ") of the second expression" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp2->getNumInputs() == dsp1->getNumOutputs()) {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    } else {
        return new dsp_merger(dsp1, dsp2, 4096, layout, label);
    }
}

static base_dsp* createDSPRecursiver(base_dsp* dsp1, base_dsp* dsp2,
                                std::string& error,
                                Layout layout = Layout::kTabGroup,
                                const std::string& label = "Recursiver")
{
    if ((dsp2->getNumInputs() > dsp1->getNumOutputs()) || (dsp2->getNumOutputs() > dsp1->getNumInputs())) {
        std::stringstream error_aux;
        error_aux << "Connection error in : dsp_recursiver" << std::endl;
        if (dsp2->getNumInputs() > dsp1->getNumOutputs()) {
            error_aux << "The number of outputs " << dsp1->getNumOutputs()
                      << " of the first expression should be greater or equal to the number of inputs ("
                      << dsp2->getNumInputs()
                      << ") of the second expression" << std::endl;
        }
        if (dsp2->getNumOutputs() > dsp1->getNumInputs()) {
            error_aux << "The number of inputs " << dsp1->getNumInputs()
                      << " of the first expression should be greater or equal to the number of outputs ("
                      << dsp2->getNumOutputs()
                      << ") of the second expression" << std::endl;
        }
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_recursiver(dsp1, dsp2, layout, label);
    }
}

static base_dsp* createDSPCrossfader(base_dsp* dsp1, base_dsp* dsp2,
                                 std::string& error,
                                 Layout layout = Layout::kTabGroup,
                                 const std::string& label = "Crossfade")
{
    if (dsp1->getNumInputs() != dsp2->getNumInputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_crossfader : the number of inputs ("
        << dsp1->getNumInputs() << ") of A "
        << "must be equal to the number of inputs (" << dsp2->getNumInputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp1->getNumOutputs() != dsp2->getNumOutputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_crossfader : the number of outputs ("
        << dsp1->getNumOutputs() << ") of A "
        << "must be equal to the number of outputs (" << dsp2->getNumOutputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_crossfader(dsp1, dsp2, layout, label);
    }
}

#endif

#endif
/************************** END base_dsp-combiner.h **************************/
/************************** BEGIN proxy-base_dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __proxy_dsp__
#define __proxy_dsp__

#include <vector>
#include <map>

/************************** BEGIN JSONUIDecoder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __JSONUIDecoder__
#define __JSONUIDecoder__

#include <vector>
#include <map>
#include <utility>
#include <cstdlib>
#include <sstream>
#include <functional>

/************************** BEGIN CGlue.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef CGLUE_H
#define CGLUE_H

/************************** BEGIN CInterface.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef CINTERFACE_H
#define CINTERFACE_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
struct Soundfile;

/*******************************************************************************
 * UI, Meta and MemoryManager structures for C code.
 ******************************************************************************/

// -- widget's layouts

typedef void (* openTabBoxFun) (void* ui_interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* ui_interface, const char* label);
typedef void (* openVerticalBoxFun) (void* ui_interface, const char* label);
typedef void (* closeBoxFun) (void* ui_interface);

// -- active widgets

typedef void (* addButtonFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addCheckButtonFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addVerticalSliderFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addHorizontalSliderFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addNumEntryFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

// -- passive widgets

typedef void (* addHorizontalBargraphFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addVerticalBargraphFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

// -- soundfiles
    
typedef void (* addSoundfileFun) (void* ui_interface, const char* label, const char* url, struct Soundfile** sf_zone);

typedef void (* declareFun) (void* ui_interface, FAUSTFLOAT* zone, const char* key, const char* value);

typedef struct {

    void* uiInterface;

    openTabBoxFun openTabBox;
    openHorizontalBoxFun openHorizontalBox;
    openVerticalBoxFun openVerticalBox;
    closeBoxFun closeBox;
    addButtonFun addButton;
    addCheckButtonFun addCheckButton;
    addVerticalSliderFun addVerticalSlider;
    addHorizontalSliderFun addHorizontalSlider;
    addNumEntryFun addNumEntry;
    addHorizontalBargraphFun addHorizontalBargraph;
    addVerticalBargraphFun addVerticalBargraph;
    addSoundfileFun addSoundfile;
    declareFun declare;

} UIGlue;

typedef void (* metaDeclareFun) (void* ui_interface, const char* key, const char* value);

typedef struct {

    void* metaInterface;
    
    metaDeclareFun declare;

} MetaGlue;

/***************************************
 *  Interface for the DSP object
 ***************************************/

typedef char dsp_imp;
    
typedef dsp_imp* (* newDspFun) ();
typedef void (* destroyDspFun) (dsp_imp* base_dsp);
typedef int (* getNumInputsFun) (dsp_imp* base_dsp);
typedef int (* getNumOutputsFun) (dsp_imp* base_dsp);
typedef void (* buildUserInterfaceFun) (dsp_imp* base_dsp, UIGlue* ui);
typedef int (* getSampleRateFun) (dsp_imp* base_dsp);
typedef void (* initFun) (dsp_imp* base_dsp, int sample_rate);
typedef void (* classInitFun) (int sample_rate);
typedef void (* instanceInitFun) (dsp_imp* base_dsp, int sample_rate);
typedef void (* instanceConstantsFun) (dsp_imp* base_dsp, int sample_rate);
typedef void (* instanceResetUserInterfaceFun) (dsp_imp* base_dsp);
typedef void (* instanceClearFun) (dsp_imp* base_dsp);
typedef void (* computeFun) (dsp_imp* base_dsp, int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
typedef void (* metadataFun) (MetaGlue* meta);
    
/***************************************
 * DSP memory manager functions
 ***************************************/

typedef void* (* allocateFun) (void* manager_interface, size_t size);
typedef void (* destroyFun) (void* manager_interface, void* ptr);

typedef struct {
    
    void* managerInterface;
    
    allocateFun allocate;
    destroyFun destroy;
    
} MemoryManagerGlue;

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CInterface.h **************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * UI glue code
 ******************************************************************************/
 
class UIFloat
{

    public:

        UIFloat() {}

        virtual ~UIFloat() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, float* zone) = 0;
        virtual void addCheckButton(const char* label, float* zone) = 0;
        virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
        virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(float* zone, const char* key, const char* val) {}
};

static void openTabBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openTabBox(label);
}

static void openHorizontalBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openHorizontalBox(label);
}

static void openVerticalBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openVerticalBox(label);
}

static void closeBoxGlueFloat(void* cpp_interface)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->closeBox();
}

static void addButtonGlueFloat(void* cpp_interface, const char* label, float* zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addButton(label, zone);
}

static void addCheckButtonGlueFloat(void* cpp_interface, const char* label, float* zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addCheckButton(label, zone);
}

static void addVerticalSliderGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addVerticalSlider(label, zone, init, min, max, step);
}

static void addHorizontalSliderGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addHorizontalSlider(label, zone, init, min, max, step);
}

static void addNumEntryGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addNumEntry(label, zone, init, min, max, step);
}

static void addHorizontalBargraphGlueFloat(void* cpp_interface, const char* label, float* zone, float min, float max)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addHorizontalBargraph(label, zone, min, max);
}

static void addVerticalBargraphGlueFloat(void* cpp_interface, const char* label, float* zone, float min, float max)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addVerticalBargraph(label, zone, min, max);
}
    
static void addSoundfileGlueFloat(void* cpp_interface, const char* label, const char* url, Soundfile** sf_zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addSoundfile(label, url, sf_zone);
}

static void declareGlueFloat(void* cpp_interface, float* zone, const char* key, const char* value)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->declare(zone, key, value);
}

class UIDouble
{

    public:

        UIDouble() {}

        virtual ~UIDouble() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, double* zone) = 0;
        virtual void addCheckButton(const char* label, double* zone) = 0;
        virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
        virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
        virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max) = 0;
        virtual void addVerticalBargraph(const char* label, double* zone, double min, double max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(double* zone, const char* key, const char* val) {}
};

static void openTabBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openTabBox(label);
}

static void openHorizontalBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openHorizontalBox(label);
}

static void openVerticalBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openVerticalBox(label);
}

static void closeBoxGlueDouble(void* cpp_interface)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->closeBox();
}

static void addButtonGlueDouble(void* cpp_interface, const char* label, double* zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addButton(label, zone);
}

static void addCheckButtonGlueDouble(void* cpp_interface, const char* label, double* zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addCheckButton(label, zone);
}

static void addVerticalSliderGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addVerticalSlider(label, zone, init, min, max, step);
}

static void addHorizontalSliderGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addHorizontalSlider(label, zone, init, min, max, step);
}

static void addNumEntryGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addNumEntry(label, zone, init, min, max, step);
}

static void addHorizontalBargraphGlueDouble(void* cpp_interface, const char* label, double* zone, double min, double max)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addHorizontalBargraph(label, zone, min, max);
}

static void addVerticalBargraphGlueDouble(void* cpp_interface, const char* label, double* zone, double min, double max)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addVerticalBargraph(label, zone, min, max);
}
    
static void addSoundfileGlueDouble(void* cpp_interface, const char* label, const char* url, Soundfile** sf_zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addSoundfile(label, url, sf_zone);
}

static void declareGlueDouble(void* cpp_interface, double* zone, const char* key, const char* value)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->declare(zone, key, value);
}

static void buildUIGlue(UIGlue* glue, UI* ui_interface, bool is_double)
{
    glue->uiInterface = ui_interface;
    
    if (is_double) {
        glue->openTabBox = reinterpret_cast<openTabBoxFun>(openTabBoxGlueDouble);
        glue->openHorizontalBox = reinterpret_cast<openHorizontalBoxFun>(openHorizontalBoxGlueDouble);
        glue->openVerticalBox = reinterpret_cast<openVerticalBoxFun>(openVerticalBoxGlueDouble);
        glue->closeBox = reinterpret_cast<closeBoxFun>(closeBoxGlueDouble);
        glue->addButton = reinterpret_cast<addButtonFun>(addButtonGlueDouble);
        glue->addCheckButton = reinterpret_cast<addCheckButtonFun>(addCheckButtonGlueDouble);
        glue->addVerticalSlider = reinterpret_cast<addVerticalSliderFun>(addVerticalSliderGlueDouble);
        glue->addHorizontalSlider = reinterpret_cast<addHorizontalSliderFun>(addHorizontalSliderGlueDouble);
        glue->addNumEntry = reinterpret_cast<addNumEntryFun>(addNumEntryGlueDouble);
        glue->addHorizontalBargraph = reinterpret_cast<addHorizontalBargraphFun>(addHorizontalBargraphGlueDouble);
        glue->addVerticalBargraph = reinterpret_cast<addVerticalBargraphFun>(addVerticalBargraphGlueDouble);
        glue->addSoundfile = reinterpret_cast<addSoundfileFun>(addSoundfileGlueDouble);
        glue->declare = reinterpret_cast<declareFun>(declareGlueDouble);
    } else {
        glue->openTabBox = reinterpret_cast<openTabBoxFun>(openTabBoxGlueFloat);
        glue->openHorizontalBox = reinterpret_cast<openHorizontalBoxFun>(openHorizontalBoxGlueFloat);
        glue->openVerticalBox = reinterpret_cast<openVerticalBoxFun>(openVerticalBoxGlueFloat);
        glue->closeBox = reinterpret_cast<closeBoxFun>(closeBoxGlueFloat);
        glue->addButton = reinterpret_cast<addButtonFun>(addButtonGlueFloat);
        glue->addCheckButton = reinterpret_cast<addCheckButtonFun>(addCheckButtonGlueFloat);
        glue->addVerticalSlider = reinterpret_cast<addVerticalSliderFun>(addVerticalSliderGlueFloat);
        glue->addHorizontalSlider = reinterpret_cast<addHorizontalSliderFun>(addHorizontalSliderGlueFloat);
        glue->addNumEntry = reinterpret_cast<addNumEntryFun>(addNumEntryGlueFloat);
        glue->addHorizontalBargraph = reinterpret_cast<addHorizontalBargraphFun>(addHorizontalBargraphGlueFloat);
        glue->addVerticalBargraph = reinterpret_cast<addVerticalBargraphFun>(addVerticalBargraphGlueFloat);
        glue->addSoundfile = reinterpret_cast<addSoundfileFun>(addSoundfileGlueFloat);
        glue->declare = reinterpret_cast<declareFun>(declareGlueFloat);
    }
}
    
struct UITemplate
{
    
    void* fCPPInterface;

    UITemplate(void* cpp_interface):fCPPInterface(cpp_interface)
    {}
    
    virtual ~UITemplate() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label)
    {
        openTabBoxGlueFloat(fCPPInterface, label);
    }
    virtual void openHorizontalBox(const char* label)
    {
        openHorizontalBoxGlueFloat(fCPPInterface, label);
    }
    virtual void openVerticalBox(const char* label)
    {
        openVerticalBoxGlueFloat(fCPPInterface, label);
    }
    virtual void closeBox()
    {
        closeBoxGlueFloat(fCPPInterface);
    }
    
    // float version
    
    // -- active widgets
    
    virtual void addButton(const char* label, float* zone)
    {
        addButtonGlueFloat(fCPPInterface, label, zone);
    }
    virtual void addCheckButton(const char* label, float* zone)
    {
        addCheckButtonGlueFloat(fCPPInterface, label, zone);
    }
    
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        addVerticalSliderGlueFloat(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        addHorizontalSliderGlueFloat(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
    {
        addNumEntryGlueFloat(fCPPInterface, label, zone, init, min, max, step);
    }
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max)
    {
        addHorizontalBargraphGlueFloat(fCPPInterface, label, zone, min, max);
    }
    
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)
    {
        addVerticalBargraphGlueFloat(fCPPInterface, label, zone, min, max);
    }

    // -- metadata declarations
    
    virtual void declare(float* zone, const char* key, const char* val)
    {
        declareGlueFloat(fCPPInterface, zone, key, val);
    }
    
    // double version
    
    virtual void addButton(const char* label, double* zone)
    {
        addButtonGlueDouble(fCPPInterface, label, zone);
    }
    virtual void addCheckButton(const char* label, double* zone)
    {
        addCheckButtonGlueDouble(fCPPInterface, label, zone);
    }
    
    virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step)
    {
        addVerticalSliderGlueDouble(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step)
    {
        addHorizontalSliderGlueDouble(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step)
    {
        addNumEntryGlueDouble(fCPPInterface, label, zone, init, min, max, step);
    }

    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* url, Soundfile** sf_zone)
    {
        addSoundfileGlueFloat(fCPPInterface, label, url, sf_zone);
    }

    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max)
    {
        addHorizontalBargraphGlueDouble(fCPPInterface, label, zone, min, max);
    }
    
    virtual void addVerticalBargraph(const char* label, double* zone, double min, double max)
    {
        addVerticalBargraphGlueDouble(fCPPInterface, label, zone, min, max);
    }

    // -- metadata declarations
    
    virtual void declare(double* zone, const char* key, const char* val)
    {
        declareGlueDouble(fCPPInterface, zone, key, val);
    }

};

/*******************************************************************************
 * Meta glue code
 ******************************************************************************/

static void declareMetaGlue(void* cpp_interface, const char* key, const char* value)
{
    Meta* meta_interface = static_cast<Meta*>(cpp_interface);
    meta_interface->declare(key, value);
}

static void buildMetaGlue(MetaGlue* glue, Meta* meta)
{
    glue->metaInterface = meta;
    glue->declare = declareMetaGlue;
}
    
/*******************************************************************************
 * Memory manager glue code
 ******************************************************************************/

static void* allocateMemoryManagerGlue(void* cpp_interface, size_t size)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    return manager_interface->allocate(size);
}
    
static void destroyMemoryManagerGlue(void* cpp_interface, void* ptr)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    manager_interface->destroy(ptr);
}

static void buildManagerGlue(MemoryManagerGlue* glue, dsp_memory_manager* manager)
{
    glue->managerInterface = manager;
    glue->allocate = allocateMemoryManagerGlue;
    glue->destroy = destroyMemoryManagerGlue;
}

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CGlue.h **************************/

#ifdef _WIN32
#include <windows.h>
#define snprintf _snprintf
#endif

//------------------------------------------------------------------------------------------
//  Decode a base_dsp JSON description and implement 'buildUserInterface' and 'metadata' methods
//------------------------------------------------------------------------------------------

#define REAL_UI(ui_interface) reinterpret_cast<UIReal<REAL>*>(ui_interface)
#define REAL_ADR(index)      reinterpret_cast<REAL*>(&memory_block[index])
#define REAL_EXT_ADR(index)  reinterpret_cast<FAUSTFLOAT*>(&memory_block[index])
#define SOUNDFILE_ADR(index) reinterpret_cast<Soundfile**>(&memory_block[index])

typedef std::function<void(double)> ReflectFunction;
typedef std::function<double()> ModifyFunction;

struct ExtZoneParam {

    virtual void reflectZone() = 0;
    virtual void modifyZone() = 0;
    
    virtual void setReflectZoneFun(ReflectFunction reflect) = 0;
    virtual void setModifyZoneFun(ModifyFunction modify) = 0;
    
    virtual ~ExtZoneParam()
    {}
    
};

// Templated decoder

struct JSONUIDecoderBase
{
    virtual ~JSONUIDecoderBase()
    {}
    
    virtual void metadata(Meta* m) = 0;
    virtual void metadata(MetaGlue* glue) = 0;
    virtual int getDSPSize() = 0;
    virtual std::string getName() = 0;
    virtual std::string getLibVersion() = 0;
    virtual std::string getCompileOptions() = 0;
    virtual std::vector<std::string> getLibraryList() = 0;
    virtual std::vector<std::string> getIncludePathnames() = 0;
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual int getSampleRate(char* memory_block) = 0;
    virtual void setReflectZoneFun(int index, ReflectFunction fun) = 0;
    virtual void setModifyZoneFun(int index, ModifyFunction fun) = 0;
    virtual void setupDSPProxy(UI* ui_interface, char* memory_block) = 0;
    virtual bool hasDSPProxy() = 0;
    virtual std::vector<ExtZoneParam*>& getInputControls() = 0;
    virtual std::vector<ExtZoneParam*>& getOutputControls() = 0;
    virtual void resetUserInterface() = 0;
    virtual void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr) = 0;
    virtual void buildUserInterface(UI* ui_interface) = 0;
    virtual void buildUserInterface(UI* ui_interface, char* memory_block) = 0;
    virtual void buildUserInterface(UIGlue* ui_interface, char* memory_block) = 0;
    virtual bool hasCompileOption(const std::string& option) = 0;
};

template <typename REAL>
struct JSONUIDecoderReal : public JSONUIDecoderBase {
    
    struct ZoneParam : public ExtZoneParam {
        
        FAUSTFLOAT fZone;
        ReflectFunction fReflect;
        ModifyFunction fModify;
        
    #if defined(TARGET_OS_IPHONE) || defined(WIN32)
        ZoneParam(ReflectFunction reflect = nullptr, ModifyFunction modify = nullptr)
        :fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { if (fReflect) fReflect(fZone); }
        void modifyZone() { if (fModify) fZone = fModify(); }
    #else
        ZoneParam(ReflectFunction reflect = [](REAL value) {}, ModifyFunction modify = []() { return REAL(-1); })
        :fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { fReflect(fZone); }
        void modifyZone() { fZone = fModify(); }
    #endif
        
        void setReflectZoneFun(ReflectFunction reflect) { fReflect = reflect; }
        void setModifyZoneFun(ModifyFunction modify) { fModify = modify; }
        
    };
    
    typedef std::vector<ExtZoneParam*> controlMap;
  
    std::string fName;
    std::string fFileName;
    std::string fJSON;
    std::string fVersion;
    std::string fCompileOptions;
    
    std::map<std::string, std::string> fMetadata;
    std::vector<itemInfo> fUiItems;
    
    std::vector<std::string> fLibraryList;
    std::vector<std::string> fIncludePathnames;
    
    int fNumInputs, fNumOutputs, fSRIndex;
    int fDSPSize;
    bool fDSPProxy;
    
    controlMap fPathInputTable;     // [path, ZoneParam]
    controlMap fPathOutputTable;    // [path, ZoneParam]

    bool isInput(const std::string& type)
    {
        return (type == "vslider" || type == "hslider" || type == "nentry" || type == "button" || type == "checkbox");
    }
    bool isOutput(const std::string& type) { return (type == "hbargraph" || type == "vbargraph"); }
    bool isSoundfile(const std::string& type) { return (type == "soundfile"); }
    
    std::string getString(std::map<std::string, std::pair<std::string, double> >& map, const std::string& key)
    {
        return (map.find(key) != map.end()) ? map[key].first : "";
    }
    
    int getInt(std::map<std::string, std::pair<std::string, double> >& map, const std::string& key)
    {
        return (map.find(key) != map.end()) ? int(map[key].second) : -1;
    }
    
    void setReflectZoneFun(int index, ReflectFunction fun)
    {
        fPathInputTable[index]->setReflectZoneFun(fun);
    }
    
    void setModifyZoneFun(int index, ModifyFunction fun)
    {
        fPathOutputTable[index]->setModifyZoneFun(fun);
    }

    JSONUIDecoderReal(const std::string& json)
    {
        fJSON = json;
        const char* p = fJSON.c_str();
        std::map<std::string, std::pair<std::string, double> > meta_data1;
        std::map<std::string, std::vector<std::string> > meta_data2;
        parseJson(p, meta_data1, fMetadata, meta_data2, fUiItems);
        
        // meta_data1 contains <name : val>, <inputs : val>, <ouputs : val> pairs etc...
        fName = getString(meta_data1, "name");
        fFileName = getString(meta_data1, "filename");
        fVersion = getString(meta_data1, "version");
        fCompileOptions = getString(meta_data1, "compile_options");
        
        if (meta_data2.find("library_list") != meta_data2.end()) {
            fLibraryList = meta_data2["library_list"];
        }
        if (meta_data2.find("include_pathnames") != meta_data2.end()) {
            fIncludePathnames = meta_data2["include_pathnames"];
        }
        
        fDSPSize = getInt(meta_data1, "size");
        fNumInputs = getInt(meta_data1, "inputs");
        fNumOutputs = getInt(meta_data1, "outputs");
        fSRIndex = getInt(meta_data1, "sr_index");
        fDSPProxy = false;
        
        // Prepare the fPathTable and init zone
        for (const auto& it : fUiItems) {
            std::string type = it.type;
            // Meta data declaration for input items
            if (isInput(type)) {
                ZoneParam* param = new ZoneParam();
                fPathInputTable.push_back(param);
                param->fZone = it.init;
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                ZoneParam* param = new ZoneParam();
                fPathOutputTable.push_back(param);
                param->fZone = REAL(0);
            }
        }
    }
    
    virtual ~JSONUIDecoderReal()
    {
        for (const auto& it : fPathInputTable) {
            delete it;
        }
        for (const auto& it : fPathOutputTable) {
            delete it;
        }
    }
    
    void metadata(Meta* m)
    {
        for (const auto& it : fMetadata) {
            m->declare(it.first.c_str(), it.second.c_str());
        }
    }
    
    void metadata(MetaGlue* m)
    {
        for (const auto& it : fMetadata) {
            m->declare(m->metaInterface, it.first.c_str(), it.second.c_str());
        }
    }
    
    void resetUserInterface()
    {
        int item = 0;
        for (const auto& it : fUiItems) {
            if (isInput(it.type)) {
                static_cast<ZoneParam*>(fPathInputTable[item++])->fZone = it.init;
            }
        }
    }
    
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        for (const auto& it : fUiItems) {
            int index = it.index;
            if (isInput(it.type)) {
                *REAL_ADR(index) = it.init;
            } else if (isSoundfile(it.type)) {
                if (*SOUNDFILE_ADR(index) == nullptr) {
                    *SOUNDFILE_ADR(index) = defaultsound;
                }
            }
        }
    }
    
    int getSampleRate(char* memory_block)
    {
        return *reinterpret_cast<int*>(&memory_block[fSRIndex]);
    }
    
    void setupDSPProxy(UI* ui_interface, char* memory_block)
    {
        if (!fDSPProxy) {
            fDSPProxy = true;
            int countIn = 0;
            int countOut = 0;
            for (const auto& it : fUiItems) {
                std::string type = it.type;
                int index = it.index;
                if (isInput(type)) {
                    fPathInputTable[countIn++]->setReflectZoneFun([=](REAL value) { *REAL_ADR(index) = value; });
                } else if (isOutput(type)) {
                    fPathOutputTable[countOut++]->setModifyZoneFun([=]() { return *REAL_ADR(index); });
                }
            }
        }
        
        // Setup soundfile in any case
        for (const auto& it : fUiItems) {
            if (isSoundfile(it.type)) {
                ui_interface->addSoundfile(it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(it.index));
            }
        }
    }
    
    bool hasDSPProxy() { return fDSPProxy; }
  
    void buildUserInterface(UI* ui_interface)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        int countIn = 0;
        int countOut = 0;
        int countSound = 0;
        
        for (const auto& it : fUiItems) {
            
            std::string type = it.type;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(&static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(&static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                ui_interface->openHorizontalBox(it.label.c_str());
            } else if (type == "vgroup") {
                ui_interface->openVerticalBox(it.label.c_str());
            } else if (type == "tgroup") {
                ui_interface->openTabBox(it.label.c_str());
            } else if (type == "vslider") {
                ui_interface->addVerticalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "hslider") {
                ui_interface->addHorizontalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "checkbox") {
                ui_interface->addCheckButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "soundfile") {
                // Nothing
            } else if (type == "hbargraph") {
                ui_interface->addHorizontalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "vbargraph") {
                ui_interface->addVerticalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "nentry") {
                ui_interface->addNumEntry(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "button") {
                ui_interface->addButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "close") {
                ui_interface->closeBox();
            }
            
            if (isInput(type)) {
                countIn++;
            } else if (isOutput(type)) {
                countOut++;
            } else if (isSoundfile(type)) {
                countSound++;
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        for (const auto& it : fUiItems) {
            
            std::string type = it.type;
            int index = it.index;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                REAL_UI(ui_interface)->openHorizontalBox(it.label.c_str());
            } else if (type == "vgroup") {
                REAL_UI(ui_interface)->openVerticalBox(it.label.c_str());
            } else if (type == "tgroup") {
                REAL_UI(ui_interface)->openTabBox(it.label.c_str());
            } else if (type == "vslider") {
                REAL_UI(ui_interface)->addVerticalSlider(it.label.c_str(), REAL_ADR(index), init, min, max, step);
            } else if (type == "hslider") {
                REAL_UI(ui_interface)->addHorizontalSlider(it.label.c_str(), REAL_ADR(index), init, min, max, step);
            } else if (type == "checkbox") {
                REAL_UI(ui_interface)->addCheckButton(it.label.c_str(), REAL_ADR(index));
            } else if (type == "soundfile") {
                REAL_UI(ui_interface)->addSoundfile(it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(index));
            } else if (type == "hbargraph") {
                REAL_UI(ui_interface)->addHorizontalBargraph(it.label.c_str(), REAL_ADR(index), min, max);
            } else if (type == "vbargraph") {
                REAL_UI(ui_interface)->addVerticalBargraph(it.label.c_str(), REAL_ADR(index), min, max);
            } else if (type == "nentry") {
                REAL_UI(ui_interface)->addNumEntry(it.label.c_str(), REAL_ADR(index), init, min, max, step);
            } else if (type == "button") {
                REAL_UI(ui_interface)->addButton(it.label.c_str(), REAL_ADR(index));
            } else if (type == "close") {
                REAL_UI(ui_interface)->closeBox();
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        for (const auto& it : fUiItems) {
            
            std::string type = it.type;
            int index = it.index;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_EXT_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_EXT_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, 0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                ui_interface->openHorizontalBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "vgroup") {
                ui_interface->openVerticalBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "tgroup") {
                ui_interface->openTabBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "vslider") {
                ui_interface->addVerticalSlider(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), init, min, max, step);
            } else if (type == "hslider") {
                ui_interface->addHorizontalSlider(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), init, min, max, step);
            } else if (type == "checkbox") {
                ui_interface->addCheckButton(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index));
            } else if (type == "soundfile") {
                ui_interface->addSoundfile(ui_interface->uiInterface, it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(index));
            } else if (type == "hbargraph") {
                ui_interface->addHorizontalBargraph(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), min, max);
            } else if (type == "vbargraph") {
                ui_interface->addVerticalBargraph(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), min, max);
            } else if (type == "nentry") {
                ui_interface->addNumEntry(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), init, min, max, step);
            } else if (type == "button") {
                ui_interface->addButton(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index));
            } else if (type == "close") {
                ui_interface->closeBox(ui_interface->uiInterface);
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    bool hasCompileOption(const std::string& option)
    {
        std::istringstream iss(fCompileOptions);
        std::string token;
        while (std::getline(iss, token, ' ')) {
            if (token == option) return true;
        }
        return false;
    }
    
    int getDSPSize() { return fDSPSize; }
    std::string getName() { return fName; }
    std::string getLibVersion() { return fVersion; }
    std::string getCompileOptions() { return fCompileOptions; }
    std::vector<std::string> getLibraryList() { return fLibraryList; }
    std::vector<std::string> getIncludePathnames() { return fIncludePathnames; }
    int getNumInputs() { return fNumInputs; }
    int getNumOutputs() { return fNumOutputs; }
    
    std::vector<ExtZoneParam*>& getInputControls()
    {
        return fPathInputTable;
    }
    std::vector<ExtZoneParam*>& getOutputControls()
    {
        return fPathOutputTable;
    }
    
};

// FAUSTFLOAT templated decoder

struct JSONUIDecoder : public JSONUIDecoderReal<FAUSTFLOAT>
{
    JSONUIDecoder(const std::string& json):JSONUIDecoderReal<FAUSTFLOAT>(json)
    {}
};

// Generic factory

static JSONUIDecoderBase* createJSONUIDecoder(const std::string& json)
{
    JSONUIDecoder decoder(json);
    if (decoder.hasCompileOption("-double")) {
        return new JSONUIDecoderReal<double>(json);
    } else {
        return new JSONUIDecoderReal<float>(json);
    }
}

#endif
/**************************  END  JSONUIDecoder.h **************************/

/**
 * Proxy base_dsp definition created from the DSP JSON description.
 * This class allows a 'proxy' base_dsp to control a real base_dsp
 * possibly running somewhere else.
 */
class proxy_dsp : public base_dsp {

    protected:
    
        JSONUIDecoder* fDecoder;
        int fSampleRate;
    
        void init(const std::string& json)
        {
            fDecoder = new JSONUIDecoder(json);
            fSampleRate = -1;
        }
        
    public:
    
        proxy_dsp():fDecoder(nullptr), fSampleRate(-1)
        {}
    
        proxy_dsp(const std::string& json)
        {
            init(json);
        }
          
        proxy_dsp(base_dsp* base_dsp)
        {
            JSONUI builder(base_dsp->getNumInputs(), base_dsp->getNumOutputs());
            base_dsp->metadata(&builder);
            base_dsp->buildUserInterface(&builder);
            fSampleRate = base_dsp->getSampleRate();
            fDecoder = new JSONUIDecoder(builder.JSON());
        }
      
        virtual ~proxy_dsp()
        {
            delete fDecoder;
        }
    
        virtual int getNumInputs() { return fDecoder->fNumInputs; }
        virtual int getNumOutputs() { return fDecoder->fNumOutputs; }
        
        virtual void buildUserInterface(UI* ui) { fDecoder->buildUserInterface(ui); }
        
        // To possibly implement in a concrete proxy base_dsp 
        virtual void init(int sample_rate)
        {
            instanceInit(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }
        virtual void instanceConstants(int sample_rate) { fSampleRate = sample_rate; }
        virtual void instanceResetUserInterface() { fDecoder->resetUserInterface(); }
        virtual void instanceClear() {}
    
        virtual int getSampleRate() { return fSampleRate; }
    
        virtual proxy_dsp* clone() { return new proxy_dsp(fDecoder->fJSON); }
        virtual void metadata(Meta* m) { fDecoder->metadata(m); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {} 
        
};

#endif
/************************** END proxy-base_dsp.h **************************/

/************************** BEGIN DecoratorUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef Decorator_UI_H
#define Decorator_UI_H


//----------------------------------------------------------------
//  Generic UI empty implementation
//----------------------------------------------------------------

class GenericUI : public UI
{
    
    public:
        
        GenericUI() {}
        virtual ~GenericUI() {}
        
        // -- widget's layouts
        virtual void openTabBox(const char* label) {}
        virtual void openHorizontalBox(const char* label) {}
        virtual void openVerticalBox(const char* label) {}
        virtual void closeBox() {}
        
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    
        // -- passive widgets
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* soundpath, Soundfile** sf_zone) {}
    
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) {}
    
};

//----------------------------------------------------------------
//  Generic UI decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    
    protected:
        
        UI* fUI;
        
    public:
        
        DecoratorUI(UI* ui = 0):fUI(ui) {}
        virtual ~DecoratorUI() { delete fUI; }
        
        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }
        
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addNumEntry(label, zone, init, min, max, step); }
        
        // -- passive widgets
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        { fUI->addVerticalBargraph(label, zone, min, max); }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) { fUI->addSoundfile(label, filename, sf_zone); }
    
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }
    
};

// Defined here to simplify header #include inclusion 
class SoundUIInterface : public GenericUI {};

#endif
/**************************  END  DecoratorUI.h **************************/
/************************** BEGIN JSONControl.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __JSON_CONTROL__
#define __JSON_CONTROL__

#include <string>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct JSONControl {
    
    virtual std::string getJSON() { return ""; }

    virtual void setParamValue(const std::string& path, FAUSTFLOAT value) {}

    virtual FAUSTFLOAT getParamValue(const std::string& path) { return 0; }
    
    virtual ~JSONControl()
    {}
    
};

#endif
/**************************  END  JSONControl.h **************************/

#define kActiveVoice    0
#define kFreeVoice     -1
#define kReleaseVoice  -2
#define kLegatoVoice   -3
#define kNoVoice       -4

#define VOICE_STOP_LEVEL  0.0005    // -70 db
#define MIX_BUFFER_SIZE   4096

/**
 * Allows to control zones in a grouped manner.
 */
class GroupUI : public GUI, public PathBuilder {

    private:

        std::map<std::string, uiGroupItem*> fLabelZoneMap;

        void insertMap(std::string label, FAUSTFLOAT* zone)
        {
            if (!MapUI::endsWith(label, "/gate")
                && !MapUI::endsWith(label, "/freq")
                && !MapUI::endsWith(label, "/key")
                && !MapUI::endsWith(label, "/gain")
                && !MapUI::endsWith(label, "/vel")
                && !MapUI::endsWith(label, "/velocity")) {

                // Groups all controllers except 'freq/key', 'gate', and 'gain/vel|velocity'
                if (fLabelZoneMap.find(label) != fLabelZoneMap.end()) {
                    fLabelZoneMap[label]->addZone(zone);
                } else {
                    fLabelZoneMap[label] = new uiGroupItem(this, zone);
                }
            }
        }

        uiCallbackItem* fPanic;

    public:

        GroupUI(FAUSTFLOAT* zone, uiCallback cb, void* arg)
        {
            fPanic = new uiCallbackItem(this, zone, cb, arg);
        }
    
        virtual ~GroupUI()
        {
            // 'fPanic' is kept and deleted in GUI, so do not delete here
        }

        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }

        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }

        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }

};

/**
 * One voice of polyphony.
 */
struct dsp_voice : public MapUI, public decorator_dsp {
    
    typedef std::function<double(int)> TransformFunction;
  
    static double midiToFreq(double note)
    {
        return 440.0 * std::pow(2.0, (note-69.0)/12.0);
    }
    
    int fCurNote;                       // Playing note pitch
    int fNextNote;                      // In kLegatoVoice state, next note to play
    int fNextVel;                       // In kLegatoVoice state, next velocity to play
    int fDate;                          // KeyOn date
    int fRelease;                       // Current number of samples used in release mode to detect end of note
    FAUSTFLOAT fLevel;                  // Last audio block level
    std::vector<std::string> fGatePath; // Paths of 'gate' control
    std::vector<std::string> fGainPath; // Paths of 'gain/vel|velocity' control
    std::vector<std::string> fFreqPath; // Paths of 'freq/key' control
    TransformFunction        fKeyFun;   // MIDI key to freq conversion function
    TransformFunction        fVelFun;   // MIDI velocity to gain conversion function
    
    FAUSTFLOAT** fInputsSlice;
    FAUSTFLOAT** fOutputsSlice;
 
    dsp_voice(base_dsp* base_dsp):decorator_dsp(base_dsp)
    {
        // Default versions
        fVelFun = [](int velocity) { return double(velocity)/127.0; };
        fKeyFun = [](int pitch) { return midiToFreq(pitch); };
        base_dsp->buildUserInterface(this);
        fCurNote = kFreeVoice;
        fNextNote = fNextVel = -1;
        fLevel = FAUSTFLOAT(0);
        fDate = fRelease = 0;
        extractPaths(fGatePath, fFreqPath, fGainPath);
    }
    virtual ~dsp_voice()
    {}
    
    void computeSlice(int offset, int slice, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        FAUSTFLOAT** inputsSlice = static_cast<FAUSTFLOAT**>(alloca(sizeof(FAUSTFLOAT*) * getNumInputs()));
        for (int chan = 0; chan < getNumInputs(); chan++) {
            inputsSlice[chan] = &(inputs[chan][offset]);
        }
        FAUSTFLOAT** outputsSlice = static_cast<FAUSTFLOAT**>(alloca(sizeof(FAUSTFLOAT*) * getNumOutputs()));
        for (int chan = 0; chan < getNumOutputs(); chan++) {
            outputsSlice[chan] = &(outputs[chan][offset]);
        }
        compute(slice, inputsSlice, outputsSlice);
    }
    
    void computeLegato(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        int slice = count/2;
        
        // Reset envelops
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(0));
        }
        
        // Compute current voice on half buffer
        computeSlice(0, slice, inputs, outputs);
         
        // Start next keyOn
        keyOn(fNextNote, fNextVel);
        
        // Compute on second half buffer
        computeSlice(slice, slice, inputs, outputs);
    }

    void extractPaths(std::vector<std::string>& gate, std::vector<std::string>& freq, std::vector<std::string>& gain)
    {
        // Keep gain/vel|velocity, freq/key and gate labels
        for (const auto& it : getMap()) {
            std::string path = it.first;
            if (endsWith(path, "/gate")) {
                gate.push_back(path);
            } else if (endsWith(path, "/freq")) {
                fKeyFun = [](int pitch) { return midiToFreq(pitch); };
                freq.push_back(path);
            } else if (endsWith(path, "/key")) {
                fKeyFun = [](int pitch) { return pitch; };
                freq.push_back(path);
            } else if (endsWith(path, "/gain")) {
                fVelFun = [](int velocity) { return double(velocity)/127.0; };
                gain.push_back(path);
            } else if (endsWith(path, "/vel") || endsWith(path, "/velocity")) {
                fVelFun = [](int velocity) { return double(velocity); };
                gain.push_back(path);
            }
        }
    }
 
    void instanceClear()
    {
        decorator_dsp::instanceClear();
        fCurNote = kFreeVoice;
        fNextNote = fNextVel = -1;
        fLevel = FAUSTFLOAT(0);
        fDate = fRelease = 0;
    }
    
    // Keep 'pitch' and 'velocity' to fadeOut the current voice and start next one in the next buffer
    void keyOn(int pitch, int velocity, bool legato = false)
    {
        if (legato) {
            fNextNote = pitch;
            fNextVel = velocity;
        } else {
            keyOn(pitch, fVelFun(velocity));
        }
    }

    // Normalized MIDI velocity [0..1]
    void keyOn(int pitch, double velocity)
    {
        for (size_t i = 0; i < fFreqPath.size(); i++) {
            setParamValue(fFreqPath[i], fKeyFun(pitch));
        }
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(1));
        }
        for (size_t i = 0; i < fGainPath.size(); i++) {
            setParamValue(fGainPath[i], velocity);
        }
        
        fCurNote = pitch;
    }

    void keyOff(bool hard = false)
    {
        // No use of velocity for now...
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(0));
        }
        
        if (hard) {
            // Immediately stop voice
            fCurNote = kFreeVoice;
        } else {
            // Release voice
            fRelease = fDSP->getSampleRate()/2; // Half sec used in release mode to detect end of note
            fCurNote = kReleaseVoice;
        }
    }

};

/**
 * A group of voices.
 */
struct dsp_voice_group {

    GroupUI fGroups;

    std::vector<dsp_voice*> fVoiceTable; // Individual voices
    base_dsp* fVoiceGroup;                    // Voices group to be used for GUI grouped control

    FAUSTFLOAT fPanic;

    bool fVoiceControl;
    bool fGroupControl;

    dsp_voice_group(uiCallback cb, void* arg, bool control, bool group)
        :fGroups(&fPanic, cb, arg),
        fVoiceGroup(0), fPanic(FAUSTFLOAT(0)),
        fVoiceControl(control), fGroupControl(group)
    {}

    virtual ~dsp_voice_group()
    {
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            delete fVoiceTable[i];
        }
        delete fVoiceGroup;
    }

    void addVoice(dsp_voice* voice)
    {
        fVoiceTable.push_back(voice);
    }

    void clearVoices()
    {
        fVoiceTable.clear();
    }

    void init()
    {
        // Groups all uiItem for a given path
        fVoiceGroup = new proxy_dsp(fVoiceTable[0]);
        fVoiceGroup->buildUserInterface(&fGroups);
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            fVoiceTable[i]->buildUserInterface(&fGroups);
        }
    }
    
    void instanceResetUserInterface()
    {
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            fVoiceTable[i]->instanceResetUserInterface();
        }
    }

    void buildUserInterface(UI* ui_interface)
    {
        if (fVoiceTable.size() > 1) {
            ui_interface->openTabBox("Polyphonic");

            // Grouped voices UI
            ui_interface->openVerticalBox("Voices");
            ui_interface->addButton("Panic", &fPanic);
            fVoiceGroup->buildUserInterface(ui_interface);
            ui_interface->closeBox();

            // If not grouped, also add individual voices UI
            if (!fGroupControl || dynamic_cast<SoundUIInterface*>(ui_interface)) {
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    char buffer[32];
                    snprintf(buffer, 32, ((fVoiceTable.size() < 8) ? "Voice%ld" : "V%ld"), long(i+1));
                    ui_interface->openHorizontalBox(buffer);
                    fVoiceTable[i]->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                }
            }

            ui_interface->closeBox();
        } else {
            fVoiceTable[0]->buildUserInterface(ui_interface);
        }
    }

};

/**
 * Base class for MIDI controllable polyphonic DSP.
 */
#ifdef EMCC
#endif

class dsp_poly : public decorator_dsp, public midi, public JSONControl {

    protected:
    
    #ifdef EMCC
        MapUI fMapUI;
        std::string fJSON;
        midi_handler fMidiHandler;
        MidiUI fMIDIUI;
    #endif
    
    public:
    
    #ifdef EMCC
        dsp_poly(base_dsp* base_dsp):decorator_dsp(base_dsp), fMIDIUI(&fMidiHandler)
        {
            JSONUI jsonui(getNumInputs(), getNumOutputs());
            buildUserInterface(&jsonui);
            fJSON = jsonui.JSON(true);
            buildUserInterface(&fMapUI);
            buildUserInterface(&fMIDIUI);
        }
    #else
        dsp_poly(base_dsp* base_dsp):decorator_dsp(base_dsp)
        {}
    #endif
    
        virtual ~dsp_poly() {}
    
        // Reimplemented for EMCC
    #ifdef EMCC
        virtual int getNumInputs() { return decorator_dsp::getNumInputs(); }
        virtual int getNumOutputs() { return decorator_dsp::getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { decorator_dsp::buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return decorator_dsp::getSampleRate(); }
        virtual void init(int sample_rate) { decorator_dsp::init(sample_rate); }
        virtual void instanceInit(int sample_rate) { decorator_dsp::instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { decorator_dsp::instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { decorator_dsp::instanceResetUserInterface(); }
        virtual void instanceClear() { decorator_dsp::instanceClear(); }
        virtual dsp_poly* clone() { return new dsp_poly(fDSP->clone()); }
        virtual void metadata(Meta* m) { decorator_dsp::metadata(m); }
    
        // Additional API
        std::string getJSON()
        {
            return fJSON;
        }
    
        virtual void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            fMapUI.setParamValue(path, value);
            GUI::updateAllGuis();
        }
        
        virtual FAUSTFLOAT getParamValue(const std::string& path) { return fMapUI.getParamValue(path); }

        virtual void computeJS(int count, uintptr_t inputs, uintptr_t outputs)
        {
            decorator_dsp::compute(count, reinterpret_cast<FAUSTFLOAT**>(inputs),reinterpret_cast<FAUSTFLOAT**>(outputs));
        }
    #endif
    
        virtual MapUI* keyOn(int channel, int pitch, int velocity)
        {
            return midi::keyOn(channel, pitch, velocity);
        }
        virtual void keyOff(int channel, int pitch, int velocity)
        {
            midi::keyOff(channel, pitch, velocity);
        }
        virtual void keyPress(int channel, int pitch, int press)
        {
            midi::keyPress(channel, pitch, press);
        }
        virtual void chanPress(int channel, int press)
        {
            midi::chanPress(channel, press);
        }
        virtual void ctrlChange(int channel, int ctrl, int value)
        {
            midi::ctrlChange(channel, ctrl, value);
        }
        virtual void ctrlChange14bits(int channel, int ctrl, int value)
        {
            midi::ctrlChange14bits(channel, ctrl, value);
        }
        virtual void pitchWheel(int channel, int wheel)
        {
        #ifdef EMCC
            fMIDIUI.pitchWheel(0., channel, wheel);
            GUI::updateAllGuis();
        #else
            midi::pitchWheel(channel, wheel);
        #endif
        }
        virtual void progChange(int channel, int pgm)
        {
            midi::progChange(channel, pgm);
        }
    
};

/**
 * Polyphonic DSP: groups a set of DSP to be played together or triggered by MIDI.
 *
 * All voices are preallocated by cloning the single DSP voice given at creation time.
 * Dynamic voice allocation is done in 'getFreeVoice'
 */
class mydsp_poly : public dsp_voice_group, public dsp_poly {

    private:

        FAUSTFLOAT** fMixBuffer;
        FAUSTFLOAT** fOutBuffer;
        midi_interface* fMidiHandler; // The midi_interface the DSP is connected to
        int fDate;
    
        void fadeOut(int count, FAUSTFLOAT** outBuffer)
        {
            // FadeOut on half buffer
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                double factor = 1., step = 1./double(count);
                for (int frame = 0; frame < count; frame++) {
                    outBuffer[chan][frame] *= factor;
                    factor -= step;
                }
            }
        }
    
        FAUSTFLOAT mixCheckVoice(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            FAUSTFLOAT level = 0;
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                FAUSTFLOAT* mixChannel = mixBuffer[chan];
                FAUSTFLOAT* outChannel = outBuffer[chan];
                for (int frame = 0; frame < count; frame++) {
                    level = std::max<FAUSTFLOAT>(level, (FAUSTFLOAT)fabs(mixChannel[frame]));
                    outChannel[frame] += mixChannel[frame];
                }
            }
            return level;
        }
    
        void mixVoice(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                FAUSTFLOAT* mixChannel = mixBuffer[chan];
                FAUSTFLOAT* outChannel = outBuffer[chan];
                for (int frame = 0; frame < count; frame++) {
                    outChannel[frame] += mixChannel[frame];
                }
            }
        }
    
        void copy(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                memcpy(outBuffer[chan], mixBuffer[chan], count * sizeof(FAUSTFLOAT));
            }
        }

        void clear(int count, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                memset(outBuffer[chan], 0, count * sizeof(FAUSTFLOAT));
            }
        }
    
        int getPlayingVoice(int pitch)
        {
            int voice_playing = kNoVoice;
            int oldest_date_playing = INT_MAX;
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fCurNote == pitch) {
                    // Keeps oldest playing voice
                    if (fVoiceTable[i]->fDate < oldest_date_playing) {
                        oldest_date_playing = fVoiceTable[i]->fDate;
                        voice_playing = int(i);
                    }
                }
            }
            
            return voice_playing;
        }
    
        int allocVoice(int voice, int type)
        {
            fVoiceTable[voice]->fDate++;
            fVoiceTable[voice]->fCurNote = type;
            return voice;
        }
    
        // Always returns a voice
        int getFreeVoice()
        {
            // Looks for the first available voice
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fCurNote == kFreeVoice) {
                    return allocVoice(i, kActiveVoice);
                }
            }

            // Otherwise steal one
            int voice_release = kNoVoice;
            int voice_playing = kNoVoice;
            int oldest_date_release = INT_MAX;
            int oldest_date_playing = INT_MAX;

            // Scan all voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fCurNote == kReleaseVoice) {
                    // Keeps oldest release voice
                    if (fVoiceTable[i]->fDate < oldest_date_release) {
                        oldest_date_release = fVoiceTable[i]->fDate;
                        voice_release = int(i);
                    }
                } else {
                    // Otherwise keeps oldest playing voice
                    if (fVoiceTable[i]->fDate < oldest_date_playing) {
                        oldest_date_playing = fVoiceTable[i]->fDate;
                        voice_playing = int(i);
                    }
                }
            }
        
            // Then decide which one to steal
            if (oldest_date_release != INT_MAX) {
                fprintf(stderr, "Steal release voice : voice_date = %d cur_date = %d voice = %d \n",
                        fVoiceTable[voice_release]->fDate,
                        fDate,
                        voice_release);
                return allocVoice(voice_release, kLegatoVoice);
            } else if (oldest_date_playing != INT_MAX) {
                fprintf(stderr, "Steal playing voice : voice_date = %d cur_date = %d voice = %d \n",
                        fVoiceTable[voice_playing]->fDate,
                        fDate,
                        voice_release);
                return allocVoice(voice_playing, kLegatoVoice);
            } else {
                assert(false);
                return kNoVoice;
            }
        }

        static void panic(FAUSTFLOAT val, void* arg)
        {
            if (val == FAUSTFLOAT(1)) {
                static_cast<mydsp_poly*>(arg)->allNotesOff(true);
            }
        }

        bool checkPolyphony()
        {
            if (fVoiceTable.size() > 0) {
                return true;
            } else {
                fprintf(stderr, "DSP is not polyphonic...\n");
                return false;
            }
        }

    public:
    
        /**
         * Constructor.
         *
         * @param base_dsp - the base_dsp to be used for one voice. Beware: mydsp_poly will use and finally delete the pointer.
         * @param nvoices - number of polyphony voices, should be at least 1
         * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
         *                If false all voices are always running.
         * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
         *                a given control on all voices, assuming GUI::updateAllGuis() is called.
         *                If false, all voices can be individually controlled.
         *
         */
        mydsp_poly(base_dsp* base_dsp,
                   int nvoices,
                   bool control = false,
                   bool group = true)
        : dsp_voice_group(panic, this, control, group), dsp_poly(base_dsp) // base_dsp parameter is deallocated by ~dsp_poly
        {
            fDate = 0;
            fMidiHandler = nullptr;

            // Create voices
            assert(nvoices > 0);
            for (int i = 0; i < nvoices; i++) {
                addVoice(new dsp_voice(base_dsp->clone()));
            }

            // Init audio output buffers
            fMixBuffer = new FAUSTFLOAT*[getNumOutputs()];
            fOutBuffer = new FAUSTFLOAT*[getNumOutputs()];
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                fMixBuffer[chan] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
                fOutBuffer[chan] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
            }

            dsp_voice_group::init();
        }

        virtual ~mydsp_poly()
        {
            // Remove from fMidiHandler
            if (fMidiHandler) fMidiHandler->removeMidiIn(this);
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                delete[] fMixBuffer[chan];
                delete[] fOutBuffer[chan];
            }
            delete[] fMixBuffer;
            delete[] fOutBuffer;
            
        }

        // DSP API
        void buildUserInterface(UI* ui_interface)
        {
            // MidiUI ui_interface contains the midi_handler connected to the MIDI driver
            if (dynamic_cast<midi_interface*>(ui_interface)) {
                fMidiHandler = dynamic_cast<midi_interface*>(ui_interface);
                fMidiHandler->addMidiIn(this);
            }
            dsp_voice_group::buildUserInterface(ui_interface);
        }

        void init(int sample_rate)
        {
            decorator_dsp::init(sample_rate);
            fVoiceGroup->init(sample_rate);
            fPanic = FAUSTFLOAT(0);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->init(sample_rate);
            }
        }
    
        void instanceInit(int samplingFreq)
        {
            instanceConstants(samplingFreq);
            instanceResetUserInterface();
            instanceClear();
        }

        void instanceConstants(int sample_rate)
        {
            decorator_dsp::instanceConstants(sample_rate);
            fVoiceGroup->instanceConstants(sample_rate);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceConstants(sample_rate);
            }
        }

        void instanceResetUserInterface()
        {
            decorator_dsp::instanceResetUserInterface();
            fVoiceGroup->instanceResetUserInterface();
            fPanic = FAUSTFLOAT(0);
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceResetUserInterface();
            }
        }

        void instanceClear()
        {
            decorator_dsp::instanceClear();
            fVoiceGroup->instanceClear();
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceClear();
            }
        }

        virtual mydsp_poly* clone()
        {
            return new mydsp_poly(fDSP->clone(), int(fVoiceTable.size()), fVoiceControl, fGroupControl);
        }

        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= MIX_BUFFER_SIZE);

            // First clear the intermediate fOutBuffer
            clear(count, fOutBuffer);

            if (fVoiceControl) {
                // Mix all playing voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    dsp_voice* voice = fVoiceTable[i];
                    if (voice->fCurNote == kLegatoVoice) {
                        // Play from current note and next note
                        voice->computeLegato(count, inputs, fMixBuffer);
                        // FadeOut on first half buffer
                        fadeOut(count/2, fMixBuffer);
                        // Mix it in result
                        voice->fLevel = mixCheckVoice(count, fMixBuffer, fOutBuffer);
                    } else if (voice->fCurNote != kFreeVoice) {
                        // Compute current note
                        voice->compute(count, inputs, fMixBuffer);
                        // Mix it in result
                        voice->fLevel = mixCheckVoice(count, fMixBuffer, fOutBuffer);
                        // Check the level to possibly set the voice in kFreeVoice again
                        voice->fRelease -= count;
                        if ((voice->fCurNote == kReleaseVoice)
                            && (voice->fRelease < 0)
                            && (voice->fLevel < VOICE_STOP_LEVEL)) {
                            voice->fCurNote = kFreeVoice;
                        }
                    }
                }
            } else {
                // Mix all voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                    mixVoice(count, fMixBuffer, fOutBuffer);
                }
            }
            
            // Finally copy intermediate buffer to outputs
            copy(count, fOutBuffer, outputs);
        }

        void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
        }
    
        // Terminate all active voices, gently or immediately (depending of 'hard' value)
        void allNotesOff(bool hard = false)
        {
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->keyOff(hard);
            }
        }

        // Additional polyphonic API
        MapUI* newVoice()
        {
            return fVoiceTable[getFreeVoice()];
        }

        void deleteVoice(MapUI* voice)
        {
            auto it = find(fVoiceTable.begin(), fVoiceTable.end(), reinterpret_cast<dsp_voice*>(voice));
            if (it != fVoiceTable.end()) {
                (*it)->keyOff();
            } else {
                fprintf(stderr, "Voice not found\n");
            }
        }

        // MIDI API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            if (checkPolyphony()) {
                int voice = getFreeVoice();
                fVoiceTable[voice]->keyOn(pitch, velocity, fVoiceTable[voice]->fCurNote == kLegatoVoice);
                return fVoiceTable[voice];
            } else {
                return 0;
            }
        }

        void keyOff(int channel, int pitch, int velocity = 127)
        {
            if (checkPolyphony()) {
                int voice = getPlayingVoice(pitch);
                if (voice != kNoVoice) {
                    fVoiceTable[voice]->keyOff();
                } else {
                    fprintf(stderr, "Playing pitch = %d not found\n", pitch);
                }
            }
        }

        void ctrlChange(int channel, int ctrl, int value)
        {
            if (ctrl == ALL_NOTES_OFF || ctrl == ALL_SOUND_OFF) {
                allNotesOff();
            }
        }

};

/**
 * Polyphonic DSP with an integrated effect.
 */
class dsp_poly_effect : public dsp_poly {
    
    private:
    
        // fPolyDSP will respond to MIDI messages.
        dsp_poly* fPolyDSP;
        
    public:
        
        dsp_poly_effect(dsp_poly* voice, base_dsp* combined)
        :dsp_poly(combined), fPolyDSP(voice)
        {}
        
        virtual ~dsp_poly_effect()
        {
            // dsp_poly_effect is also a decorator_dsp, which will free fPolyDSP
        }
        
        // MIDI API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            return fPolyDSP->keyOn(channel, pitch, velocity);
        }
        void keyOff(int channel, int pitch, int velocity)
        {
            fPolyDSP->keyOff(channel, pitch, velocity);
        }
        void keyPress(int channel, int pitch, int press)
        {
            fPolyDSP->keyPress(channel, pitch, press);
        }
        void chanPress(int channel, int press)
        {
            fPolyDSP->chanPress(channel, press);
        }
        void ctrlChange(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange(channel, ctrl, value);
        }
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange14bits(channel, ctrl, value);
        }
        void pitchWheel(int channel, int wheel)
        {
            fPolyDSP->pitchWheel(channel, wheel);
        }
        void progChange(int channel, int pgm)
        {
            fPolyDSP->progChange(channel, pgm);
        }
    
};

/**
 * Polyphonic DSP factory class. Helper code to support polyphonic DSP source with an integrated effect.
 */
struct dsp_poly_factory : public dsp_factory {
    
    dsp_factory* fProcessFactory;
    dsp_factory* fEffectFactory;
    
    base_dsp* adaptDSP(base_dsp* base_dsp, bool is_double)
    {
        return (is_double) ? new dsp_sample_adapter<double, float>(base_dsp) : base_dsp;
    }

    dsp_poly_factory(dsp_factory* process_factory = nullptr,
                     dsp_factory* effect_factory = nullptr):
    fProcessFactory(process_factory)
    ,fEffectFactory(effect_factory)
    {}

    virtual ~dsp_poly_factory()
    {}

    virtual std::string getName() { return fProcessFactory->getName(); }
    virtual std::string getSHAKey() { return fProcessFactory->getSHAKey(); }
    virtual std::string getDSPCode() { return fProcessFactory->getDSPCode(); }
    virtual std::string getCompileOptions() { return fProcessFactory->getCompileOptions(); }
    virtual std::vector<std::string> getLibraryList() { return fProcessFactory->getLibraryList(); }
    virtual std::vector<std::string> getIncludePathnames() { return fProcessFactory->getIncludePathnames(); }

    std::string getEffectCode(const std::string& dsp_content)
    {
        std::stringstream effect_code;
        effect_code << "adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;";
        effect_code << "adaptor(F,G) = adapt(outputs(F),inputs(G)); dsp_code = environment{ " << dsp_content << " };";
        effect_code << "process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;";
        return effect_code.str();
    }

    virtual void setMemoryManager(dsp_memory_manager* manager)
    {
        fProcessFactory->setMemoryManager(manager);
        if (fEffectFactory) {
            fEffectFactory->setMemoryManager(manager);
        }
    }
    virtual dsp_memory_manager* getMemoryManager() { return fProcessFactory->getMemoryManager(); }

    /* Create a new polyphonic DSP instance with global effect, to be deleted with C++ 'delete'
     *
     * @param nvoices - number of polyphony voices, should be at least 1
     * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
     *                If false all voices are always running.
     * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
     *                a given control on all voices, assuming GUI::updateAllGuis() is called.
     *                If false, all voices can be individually controlled.
     * @param is_double - if true, internally allocated DSPs will be adapted to receive 'double' samples.
     */
    dsp_poly* createPolyDSPInstance(int nvoices, bool control, bool group, bool is_double = false)
    {
        dsp_poly* dsp_poly = new mydsp_poly(adaptDSP(fProcessFactory->createDSPInstance(), is_double), nvoices, control, group);
        if (fEffectFactory) {
            // the 'dsp_poly' object has to be controlled with MIDI, so kept separated from new dsp_sequencer(...) object
            return new dsp_poly_effect(dsp_poly, new dsp_sequencer(dsp_poly, adaptDSP(fEffectFactory->createDSPInstance(), is_double)));
        } else {
            return new dsp_poly_effect(dsp_poly, dsp_poly);
        }
    }

    /* Create a new DSP instance, to be deleted with C++ 'delete' */
    base_dsp* createDSPInstance()
    {
        return fProcessFactory->createDSPInstance();
    }

};

#endif // __poly_dsp__
/************************** END poly-base_dsp.h **************************/
#ifndef PLUGIN_MAGIC
/************************** BEGIN JuceGUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef JUCE_GUI_H
#define JUCE_GUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <stack>

#include "../JuceLibraryCode/JuceHeader.h"


// Definition of the standard size of the different elements

#define kKnobWidth 100
#define kKnobHeight 100

#define kVSliderWidth 80
#define kVSliderHeight 250

#define kHSliderWidth 350
#define kHSliderHeight 50

#define kButtonWidth 100
#define kButtonHeight 50

#define kCheckButtonWidth 60
#define kCheckButtonHeight 40

#define kMenuWidth 100
#define kMenuHeight 50

#define kRadioButtonWidth 100
#define kRadioButtonHeight 55

#define kNumEntryWidth 100
#define kNumEntryHeight 50

#define kNumDisplayWidth 75
#define kNumDisplayHeight 50

#define kVBargraphWidth 60
#define kVBargraphHeight 250

#define kHBargraphWidth 350
#define kHBargraphHeight 50

#define kLedWidth 25
#define kLedHeight 25

#define kNameHeight 14

#define kMargin 4

/**
 * \brief       Custom LookAndFeel class.
 * \details     Define the appearance of all the JUCE widgets.
 */

struct CustomLookAndFeel : public juce::LookAndFeel_V3
{
    void drawRoundThumb (juce::Graphics& g, const float x, const float y,
                         const float diameter, const juce::Colour& colour, float outlineThickness)
    {
        const juce::Rectangle<float> a (x, y, diameter, diameter);
        const float halfThickness = outlineThickness * 0.5f;

        juce::Path p;
        p.addEllipse (x + halfThickness, y + halfThickness, diameter - outlineThickness, diameter - outlineThickness);

        const juce::DropShadow ds (juce::Colours::black, 1, juce::Point<int> (0, 0));
        ds.drawForPath (g, p);

        g.setColour (colour);
        g.fillPath (p);

        g.setColour (colour.brighter());
        g.strokePath (p, juce::PathStrokeType (outlineThickness));
    }

    void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        juce::Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

        if (isButtonDown || isMouseOverButton)
            baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);

        const bool flatOnLeft   = button.isConnectedOnLeft();
        const bool flatOnRight  = button.isConnectedOnRight();
        const bool flatOnTop    = button.isConnectedOnTop();
        const bool flatOnBottom = button.isConnectedOnBottom();

        const float width  = button.getWidth() - 1.0f;
        const float height = button.getHeight() - 1.0f;

        if (width > 0 && height > 0)
        {
            const float cornerSize = juce::jmin(15.0f, juce::jmin(width, height) * 0.45f);
            const float lineThickness = cornerSize * 0.1f;
            const float halfThickness = lineThickness * 0.5f;

            juce::Path outline;
            outline.addRoundedRectangle (0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness,
                                         cornerSize, cornerSize,
                                         ! (flatOnLeft  || flatOnTop),
                                         ! (flatOnRight || flatOnTop),
                                         ! (flatOnLeft  || flatOnBottom),
                                         ! (flatOnRight || flatOnBottom));

            const juce::Colour outlineColour (button.findColour (button.getToggleState() ? juce::TextButton::textColourOnId
                                        : juce::TextButton::textColourOffId));

            g.setColour (baseColour);
            g.fillPath (outline);

            if (! button.getToggleState()) {
                g.setColour (outlineColour);
                g.strokePath (outline, juce::PathStrokeType (lineThickness));
            }
        }
    }

    void drawTickBox (juce::Graphics& g, juce::Component& component,
                      float x, float y, float w, float h,
                      bool ticked,
                      bool isEnabled,
                      bool isMouseOverButton,
                      bool isButtonDown) override
    {
        const float boxSize = w * 0.7f;

        bool isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());
        const juce::Colour colour (component.findColour (juce::TextButton::buttonColourId).withMultipliedSaturation ((component.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                             .withMultipliedAlpha (component.isEnabled() ? 1.0f : 0.7f));

        drawRoundThumb (g, x, y + (h - boxSize) * 0.5f, boxSize, colour,
                        isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.1f : 0.5f) : 0.3f);

        if (ticked) {
            const juce::Path tick (juce::LookAndFeel_V2::getTickShape (6.0f));
            g.setColour (isEnabled ? findColour (juce::TextButton::buttonOnColourId) : juce::Colours::grey);

            const float scale = 9.0f;
            const juce::AffineTransform trans (juce::AffineTransform::scale (w / scale, h / scale)
                                         .translated (x - 2.5f, y + 1.0f));
            g.fillPath (tick, trans);
        }
    }

    void drawLinearSliderThumb (juce::Graphics& g, int x, int y, int width, int height,
                                float sliderPos, float minSliderPos, float maxSliderPos,
                                const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        const float sliderRadius = (float)(getSliderThumbRadius (slider) - 2);

        bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
        juce::Colour knobColour (slider.findColour (juce::Slider::thumbColourId).withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f));

        if (style == juce::Slider::LinearHorizontal || style == juce::Slider::LinearVertical) {
            float kx, ky;

            if (style == juce::Slider::LinearVertical) {
                kx = x + width * 0.5f;
                ky = sliderPos;
            } else {
                kx = sliderPos;
                ky = y + height * 0.5f;
            }

            const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

            drawRoundThumb (g,
                            kx - sliderRadius,
                            ky - sliderRadius,
                            sliderRadius * 2.0f,
                            knobColour, outlineThickness);
        } else {
            // Just call the base class for the demo
            juce::LookAndFeel_V2::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        g.fillAll (slider.findColour (juce::Slider::backgroundColourId));

        if (style == juce::Slider::LinearBar || style == juce::Slider::LinearBarVertical) {
            const float fx = (float)x, fy = (float)y, fw = (float)width, fh = (float)height;

            juce::Path p;

            if (style == juce::Slider::LinearBarVertical)
                p.addRectangle (fx, sliderPos, fw, 1.0f + fh - sliderPos);
            else
                p.addRectangle (fx, fy, sliderPos - fx, fh);

            juce::Colour baseColour (slider.findColour (juce::Slider::rotarySliderFillColourId)
                               .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f)
                               .withMultipliedAlpha (0.8f));

            g.setColour (baseColour);
            g.fillPath (p);

            const float lineThickness = juce::jmin(15.0f, juce::jmin(width, height) * 0.45f) * 0.1f;
            g.drawRect (slider.getLocalBounds().toFloat(), lineThickness);
        } else {
            drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
            drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawLinearSliderBackground (juce::Graphics& g, int x, int y, int width, int height,
                                     float /*sliderPos*/,
                                     float /*minSliderPos*/,
                                     float /*maxSliderPos*/,
                                     const juce::Slider::SliderStyle /*style*/, juce::Slider& slider) override
    {
        const float sliderRadius = getSliderThumbRadius (slider) - 5.0f;
        juce::Path on, off;

        if (slider.isHorizontal()) {
            const float iy = y + height * 0.5f - sliderRadius * 0.5f;
            juce::Rectangle<float> r (x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius);
            const float onW = r.getWidth() * ((float)slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromLeft (onW));
            off.addRectangle (r);
        } else {
            const float ix = x + width * 0.5f - sliderRadius * 0.5f;
            juce::Rectangle<float> r (ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius);
            const float onH = r.getHeight() * ((float)slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromBottom (onH));
            off.addRectangle (r);
        }

        g.setColour (slider.findColour (juce::Slider::rotarySliderFillColourId));
        g.fillPath (on);

        g.setColour (slider.findColour (juce::Slider::trackColourId));
        g.fillPath (off);
    }

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override
    {
        const float radius = juce::jmin(width / 2, height / 2) - 4.0f;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

        //Background
        {
            g.setColour(juce::Colours::lightgrey.withAlpha (isMouseOver ? 1.0f : 0.7f));
            juce::Path intFilledArc;
            intFilledArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.8);
            g.fillPath(intFilledArc);
        }

        if (slider.isEnabled()) {
            g.setColour(slider.findColour (juce::Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
        } else {
            g.setColour(juce::Colour (0x80808080));
        }

        //Render knob value
        {
            juce::Path pathArc;
            pathArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, 0.8);
            g.fillPath(pathArc);

            juce::Path cursor, cursorShadow;
            float rectWidth = radius*0.4;
            float rectHeight = rectWidth/2;
            float rectX = centreX + radius*0.9 - rectHeight/2;
            float rectY = centreY - rectWidth/2;

            cursor.addRectangle(rectX, rectY, rectWidth, rectHeight);
            cursorShadow.addRectangle(rectX-1, rectY-1, rectWidth+2, rectHeight+2);

            juce::AffineTransform t = juce::AffineTransform::translation(-rectWidth + 2, rectHeight/2);
            t = t.rotated((angle - juce::float_Pi/2), centreX, centreY);

            cursor.applyTransform(t);
            cursorShadow.applyTransform(t);

            g.setColour(juce::Colours::black);
            g.fillPath(cursor);

            g.setColour(juce::Colours::black .withAlpha(0.15f));
            g.fillPath(cursorShadow);
        }
    }
};

/**
 * \brief   Different kind of slider available
 * \see     uiSlider
 */
enum SliderType {
    HSlider,    /*!< Horizontal Slider      */
    VSlider,    /*!< Vertical Slider        */
    NumEntry,   /*!< Numerical Entry Box    */
    Knob        /*!< Circular Slider        */
};

/**
 * \brief   Different kind of VU-meter available.
 */
enum VUMeterType {
    HVUMeter,   /*!< Horizontal VU-meter    */
    VVUMeter,   /*!< Vertical VU-meter      */
    Led,        /*!< LED VU-meter           */
    NumDisplay  /*!< TextBox VU-meter       */
};

/**
 * \brief   Intern class for all FAUST widgets.
 * \details Every active, passive or box widgets derive from this class.
 */
class uiBase
{
    
    protected:
        
        int fTotalWidth, fTotalHeight;              // Size with margins included (for a uiBox)
        int fDisplayRectWidth, fDisplayRectHeight;  // Size without margin, just the child dimensions, sum on one dimension, max on the other
        float fHRatio, fVRatio;
        
    public:
        
        /**
         * \brief   Constructor.
         * \details Initialize a uiBase with all its sizes.
         *
         * \param   totWidth    Minimal total width.
         * \param   totHeight   Minimal total Height.
         */
        uiBase(int totWidth = 0, int totHeight = 0):
            fTotalWidth(totWidth), fTotalHeight(totHeight),
            fDisplayRectWidth(0), fDisplayRectHeight(0),
            fHRatio(1), fVRatio(1)
        {}
        
        virtual ~uiBase()
        {}
        
        /** Return the size. */
        juce::Rectangle<int> getSize()
        {
            return juce::Rectangle<int>(0, 0, fTotalWidth, fTotalHeight);
        }
        
        /** Return the total height in pixels. */
        int getTotalHeight()
        {
            return fTotalHeight;
        }
        
        /** Return the total width in pixels. */
        int getTotalWidth()
        {
            return fTotalWidth;
        }
        
        /** Return the horizontal ratio, between 0 and 1. */
        float getHRatio()
        {
            return fHRatio;
        }
        
        /** Return the vertical ratio, between 0 and 1. */
        float getVRatio()
        {
            return fVRatio;
        }
        
        /**
         * \brief   Set the uiBase bounds.
         * \details Convert absolute bounds to relative bounds,
         *          used in JUCE Component mechanics.
         *
         * \param r The absolute bounds.
         *
         */
        void setRelativeSize(juce::Component* comp, const juce::Rectangle<int>& r)
        {
            comp->setBounds(r.getX() - comp->getParentComponent()->getX(),
                            r.getY() - comp->getParentComponent()->getY(),
                            r.getWidth(),
                            r.getHeight());
        }
    
        virtual void init(juce::Component* comp = nullptr)
        {
            /** Initialize both vertical and horizontal ratios. */
            assert(comp);
            uiBase* parentBox = comp->findParentComponentOfClass<uiBase>();
            if (parentBox != nullptr) {
                fHRatio = (float)fTotalWidth / (float)parentBox->fDisplayRectWidth;
                fVRatio = (float)fTotalHeight / (float)parentBox->fDisplayRectHeight;
            }
        }
    
        virtual void setRecommendedSize()
        {}
        
        virtual void add(juce::Component* comp)
        {}
    
};

/**
 * \brief   Intern class for all FAUST active or passive widgets.
 * \details Every activ or passive widgets derive from this class.
 */
class uiComponent : public uiBase, public juce::Component, public uiItem
{

    public:
        /**
         * \brief   Constructor.
         * \details Initialize all uiItem, uiBase and the tooltip variables.
         *
         * \param   gui     Current FAUST GUI.
         * \param   zone    Zone of the widget.
         * \param   w       Width of the widget.
         * \param   h       Height of the widget.
         * \param   name    Name of the widget.
         */
        uiComponent(GUI* gui, FAUSTFLOAT* zone, int w, int h, juce::String name):uiBase(w, h), Component(name), uiItem(gui, zone)
        {}

};

/** 
 * \brief   Intern class for all kind of sliders.
 * \see     SliderType
 */
class uiSlider : public uiComponent, public uiConverter, private juce::Slider::Listener
{
    
    private:
        
        juce::Slider::SliderStyle fStyle;
        juce::Label fLabel;
        SliderType fType;
        juce::Slider fSlider;

    public:
        /**
         * \brief   Constructor.
         * \details Initialize all uiComponent variables, and Slider specific ones.
         *          Initialize juce::Slider parameters.
         *
         * \param   gui, zone, w, h, tooltip, name  uiComponent variables.
         * \param   min                             Minimum value of the slider.
         * \param   max                             Maximum value of the slider.
         * \param   cur                             Initial value of the slider.
         * \param   step                            Step of the slider.
         * \param   unit                            Unit of the slider value.
         * \param   scale                           Scale of the slider, exponential, logarithmic, or linear.
         * \param   type                            Type of slider (see SliderType).
         */
        uiSlider(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, juce::String name, juce::String unit, juce::String tooltip, MetaDataUI::Scale scale, SliderType type)
            : uiComponent(gui, zone, w, h, name), uiConverter(scale, min, max, min, max), fType(type)
        {
            // Set the JUCE widget initalization variables.
            switch(fType) {
                case HSlider:
                    fStyle = juce::Slider::SliderStyle::LinearHorizontal;
                    break;
                case VSlider:
                    fStyle = juce::Slider::SliderStyle::LinearVertical;
                    fSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
                    break;
                case NumEntry:
                    fSlider.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_AutoDirection);
                    fStyle = juce::Slider::SliderStyle::IncDecButtons;
                    break;
                case Knob:
                    fStyle = juce::Slider::SliderStyle::Rotary;
                    fSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
                    break;
                default:
                    break;
            }
            addAndMakeVisible(fSlider);

            // Slider settings
            fSlider.setRange(min, max, step);
            fSlider.setValue(fConverter->faust2ui(cur));
            fSlider.addListener(this);
            fSlider.setSliderStyle(fStyle);
            fSlider.setTextValueSuffix(" " + unit);
            fSlider.setTooltip(tooltip);
            switch (scale) {
                case MetaDataUI::kLog:
                    fSlider.setSkewFactor(0.25);
                    break;
                case MetaDataUI::kExp:
                    fSlider.setSkewFactor(0.75);
                    break;
                default:
                    break;
            }
      
            // Label settings, only happens for a horizontal of numerical entry slider
            // because the method attachToComponent only give the choice to place the
            // slider name on centered top, which is what we want. It's done manually
            // in the paint method.
            if (fType == HSlider || fType == NumEntry) {
                fLabel.setText(getName(), juce::dontSendNotification);
                fLabel.attachToComponent(&fSlider, true);
                fLabel.setTooltip(tooltip);
                addAndMakeVisible(fLabel);
            }
        }

        /** Draw the name of a vertical or circular slider. */
        virtual void paint(juce::Graphics& g) override
        {
            if (fType == VSlider || fType == Knob) {
                g.setColour(juce::Colours::black);
                g.drawText(getName(), getLocalBounds(), juce::Justification::centredTop);
            }
        }

        /** Allow to control the slider when its value is changed, but not by the user. */
        void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fSlider.setValue(fConverter->faust2ui(v));
        }

        /** JUCE callback for a slider value change, give the value to the FAUST module. */
        void sliderValueChanged(juce::Slider* slider) override
        {
            float v = slider->getValue();
            modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
        }

        /** 
         * Set the good coordinates and size for the juce::Slider object depending 
         * on its SliderType, whenever the layout size changes.
         */
        void resized() override
        {
            int x, y, width, height;
            
            switch (fType) {
                    
                case HSlider: {
                    int nameWidth = juce::Font().getStringWidth(getName()) + kMargin * 2;
                    x = nameWidth;
                    y = 0;
                    width = getWidth() - nameWidth;
                    height = getHeight();
                    break;
                }
                    
                case VSlider:
                    x = 0;
                    y = kNameHeight; // kNameHeight pixels for the name
                    height = getHeight() - kNameHeight;
                    width = getWidth();
                    break;

                case NumEntry:
                    width = kNumEntryWidth;
                    height = kNumEntryHeight;
                    // x position is the top left corner horizontal position of the box
                    // and not the top left of the NumEntry label, so we have to do that
                    x = (getWidth() - width)/2 + (juce::Font().getStringWidth(getName()) + kMargin)/2;
                    y = (getHeight() - height)/2;
                    break;
                    
                case Knob:
                    // The knob name needs to be displayed, kNameHeight pixels
                    height = width = juce::jmin(getHeight() - kNameHeight, kKnobHeight);
                    x = (getWidth() - width)/2;
                    // kNameHeight pixels for the knob name still
                    y = juce::jmax((getHeight() - height)/2, kNameHeight);
                    break;
                    
                default:
                    assert(false);
                    break;
            }
            
            fSlider.setBounds(x, y, width, height);
        }
    
};

/** Intern class for button */
class uiButton : public uiComponent, private juce::Button::Listener
{
    
    private:
        
        juce::TextButton fButton;

    public:
        /**
         * \brief   Constructor.
         * \details Initialize all uiComponent variables and juce::TextButton parameters.
         *
         * \param   gui, zone, w, h, tooltip, label uiComponent variable.
         */
        uiButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, juce::String label, juce::String tooltip) :  uiComponent(gui, zone, w, h, label)
        {
            int x = 0;
            int y = (getHeight() - kButtonHeight)/2;

            fButton.setButtonText(label);
            fButton.setBounds(x, y, kButtonWidth, kButtonHeight);
            fButton.addListener(this);
            fButton.setTooltip(tooltip);
            addAndMakeVisible(fButton);
        }

        /** 
         * Has to be defined because its a pure virtual function of juce::Button::Listener, 
         * which uiButton derives from. Control of user actions is done in buttonStateChanged.
         * \see buttonStateChanged
         */
        void buttonClicked (juce::Button* button) override
        {}

        /** Indicate to the FAUST module when the button is pressed and released. */
        void buttonStateChanged (juce::Button* button) override
        {
            if (button->isDown()) {
                modifyZone(FAUSTFLOAT(1));
            } else {
                modifyZone(FAUSTFLOAT(0));
            }
        }
        
        void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v == FAUSTFLOAT(1)) {
                fButton.triggerClick();
            }
        }

        /** Set the good coordinates and size to the juce::TextButton widget whenever the layout size changes. */
        virtual void resized() override
        {
            int x = kMargin;
            int width = getWidth() - 2 * kMargin;
            int height = juce::jmin(getHeight(), kButtonHeight);
            int y = (getHeight()-height)/2;
            fButton.setBounds(x, y, width, height);
        }
    
};

/** Intern class for checkButton */
class uiCheckButton : public uiComponent, private juce::Button::Listener
{
    
    private:
        
        juce::ToggleButton fCheckButton;

    public:
        /**
         * \brief   Constructor.
         * \details Initialize all uiComponent variables and juce::ToggleButton parameters.
         *
         * \param   gui, zone, w, h, label, tooltip  uiComponent variables.
         */
        uiCheckButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, juce::String label, juce::String tooltip) : uiComponent(gui, zone, w, h, label)
        {
            int x = 0;
            int y = (getHeight()-h)/2;
            
            fCheckButton.setButtonText(label);
            fCheckButton.setBounds(x, y, w, h);
            fCheckButton.addListener(this);
            fCheckButton.setTooltip(tooltip);
            addAndMakeVisible(fCheckButton);
        }

        /** Indicate to the FAUST module when the button is toggled or not. */
        void buttonClicked(juce::Button* button) override
        {
            //std::cout << getName() << " : " << button->getToggleState() << std::endl;
            modifyZone(button->getToggleState());
        }

        void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fCheckButton.triggerClick();
        }

        /** Set the good coordinates and size to the juce::ToggleButton widget, whenever the layout size changes. */
        virtual void resized() override
        {
            fCheckButton.setBounds(getLocalBounds());
        }
    
};

/** Intern class for Menu */
class uiMenu : public uiComponent, private juce::ComboBox::Listener
{
    
    private:
        
        juce::ComboBox fComboBox;
        std::vector<double> fValues;

    public:
        /**
         * \brief   Constructor.
         * \details Initialize the uiComponent and Menu specific variables, and the juce::ComboBox parameters.
         *          Menu is considered as a slider in the FAUST logic, with a step of one. The first item
         *          would be 0 on a slider, the second 1, etc. Each "slider value" is associated with a 
         *          string.
         *
         * \param   gui, zone, w, h, tooltip, label     uiComponent variables.
         * \param   cur                                 Current "slider value" associated with the current item selected.
         * \param   low                                 Lowest value possible.
         * \param   hi                                  Highest value possible.
         * \param   mdescr                              Menu description. Contains the names of the items associated with their "value".
         */
        uiMenu(GUI* gui, FAUSTFLOAT* zone, juce::String label, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, juce::String tooltip, const char* mdescr) : uiComponent(gui, zone, w, h, label)
        {
            //Init ComboBox parameters
            fComboBox.setEditableText(false);
            fComboBox.setJustificationType(juce::Justification::centred);
            fComboBox.addListener(this);
            addAndMakeVisible(fComboBox);

            std::vector<std::string> names;
            std::vector<double> values;

            if (parseMenuList(mdescr, names, values)) {

                int defaultitem = -1;
                double mindelta = FLT_MAX;
                int item = 1;

                // Go through all the Menu's items.
                for (int i = 0; i < names.size(); i++) {
                    double v = values[i];
                    if ((v >= lo) && (v <= hi)) {
                        // It is a valid value : add corresponding menu item
                        // item astrating at 1 because index 0 is reserved for a non-defined item.
                        fComboBox.addItem(juce::String(names[i].c_str()), item++);
                        fValues.push_back(v);

                        // Check if this item is a good candidate to represent the current value
                        double delta = fabs(cur-v);
                        if (delta < mindelta) {
                            mindelta = delta;
                            defaultitem = fComboBox.getNumItems();
                        }
                    }
                }
                // check the best candidate to represent the current value
                if (defaultitem > -1) {
                    fComboBox.setSelectedItemIndex(defaultitem);
                }
            }

            *fZone = cur;
        }

        /** Indicate to the FAUST module when the selected items is changed. */
        void comboBoxChanged (juce::ComboBox* cb) override
        {
            //std::cout << getName( )<< " : " << cb->getSelectedId() - 1 << std::endl;
            // -1 because of the starting item  at 1 at the initialization
            modifyZone(fValues[cb->getSelectedId() - 1]);
        }

        virtual void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;

            // search closest value
            int defaultitem = -1;
            double mindelta = FLT_MAX;

            for (unsigned int i = 0; i < fValues.size(); i++) {
                double delta = fabs(fValues[i]-v);
                if (delta < mindelta) {
                    mindelta = delta;
                    defaultitem = i;
                }
            }
            if (defaultitem > -1) {
                fComboBox.setSelectedItemIndex(defaultitem);
            }
        }

        /** Set the good coordinates and size to the juce::ComboBox widget whenever the layout get reiszed */
        virtual void resized() override
        {
            fComboBox.setBounds(0, 0 + kMenuHeight/2, getWidth(), kMenuHeight/2);
        }

        /** Display the name of the Menu */
        virtual void paint(juce::Graphics& g) override
        {
            g.setColour(juce::Colours::black);
            g.drawText(getName(), getLocalBounds().withHeight(getHeight()/2), juce::Justification::centredTop);
        }
    
};

/** Intern class for RadioButton */
class uiRadioButton : public uiComponent, private juce::Button::Listener
{
    
    private:
        
        bool fIsVertical;
        juce::OwnedArray<juce::ToggleButton> fButtons;
        std::vector<double> fValues;

    public:
        /**
         * \brief   Constructor.
         * \details Initialize the uiComponent variables, and the RadioButton specific variables
         *          and parameters. Works in a similar way to the Menu, because it is a special
         *          kind of sliders in the faust logic. 
         * \see     uiMenu
         * 
         * \param   gui, zone, tooltip, label   uiComponent variables.
         * \param   w                           uiComponent variable and width of the RadioButton widget.
         * \param   h                           uiComponent variable and height of the RadioButton widget.
         * \param   cur                         Current "value" associated with the item selected.
         * \param   low                         Lowest "value" possible.
         * \param   hi                          Highest "value" possible.
         * \param   vert                        True if vertical, false if horizontal.
         * \param   names                       Contain the names of the different items.
         * \param   values                      Contain the "values" of the different items.
         * \param   fRadioGroupID               RadioButton being multiple CheckButton in JUCE,
         *                                      we need an ID to know which are linked together.
         */
        uiRadioButton(GUI* gui, FAUSTFLOAT* zone, juce::String label, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, bool vert, std::vector<std::string>& names, std::vector<double>& values, juce::String tooltip, int radioGroupID) : uiComponent(gui, zone, w, h, label), fIsVertical(vert)
        {
            juce::ToggleButton* defaultbutton = 0;
            double mindelta = FLT_MAX;

            for (int i = 0; i < names.size(); i++) {
                double v = values[i];
                if ((v >= lo) && (v <= hi)) {

                    // It is a valid value included in slider's range
                    juce::ToggleButton* tb = new juce::ToggleButton(names[i]);
                    addAndMakeVisible(tb);
                    tb->setRadioGroupId (radioGroupID);
                    tb->addListener(this);
                    tb->setTooltip(tooltip);
                    fValues.push_back(v);
                    fButtons.add(tb);
      
                    // Check if this item is a good candidate to represent the current value
                    double delta = fabs(cur-v);
                    if (delta < mindelta) {
                        mindelta = delta;
                        defaultbutton = tb;
                    }
                }
            }
            // check the best candidate to represent the current value
            if (defaultbutton) {
                defaultbutton->setToggleState (true, juce::dontSendNotification);
            }
        }
     
        virtual void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;

            // select closest value
            int defaultitem = -1;
            double mindelta = FLT_MAX;

            for (unsigned int i = 0; i < fValues.size(); i++) {
                double delta = fabs(fValues[i]-v);
                if (delta < mindelta) {
                    mindelta = delta;
                    defaultitem = i;
                }
            }
            if (defaultitem > -1) {
                fButtons.operator[](defaultitem)->setToggleState (true, juce::dontSendNotification);
            }
        }

        /** Handle the placement of each juce::ToggleButton everytime the layout size is changed. */
        virtual void resized() override
        {
            int width, height;
            fIsVertical ? (height = (getHeight() - kNameHeight) / fButtons.size()) : (width = getWidth() / fButtons.size());

            for (int i = 0; i < fButtons.size(); i++) {
                if (fIsVertical) {
                    fButtons.operator[](i)->setBounds(0, i * height + kNameHeight, getWidth(), height);
                } else {
                    // kNameHeight pixels offset for the title
                    fButtons.operator[](i)->setBounds(i * width, kNameHeight, width, getHeight() - kNameHeight);
                }
            }
        }
        
        /** Display the RadioButton name */
        virtual void paint(juce::Graphics& g) override
        {
            g.setColour(juce::Colours::black);
            g.drawText(getName(), getLocalBounds().withHeight(kNameHeight), juce::Justification::centredTop);
        }

        /** Check which button is checked, and give its "value" to the FAUST module */
    void buttonClicked(juce::Button* button) override
        {
            juce::ToggleButton* checkButton = dynamic_cast<juce::ToggleButton*>(button);
            //std::cout << getName() << " : " << fButtons.indexOf(checkButton) << std::endl;
            modifyZone(fButtons.indexOf(checkButton));
        }
    
};

/**
 * \brief   Intern class for VU-meter
 * \details There is no JUCE widgets for VU-meter, so its fully designed in this class.
 */
class uiVUMeter : public uiComponent, public juce::SettableTooltipClient, public juce::Timer
{
    
    private:
    
        FAUSTFLOAT fLevel;               // Current level of the VU-meter.
        FAUSTFLOAT fMin, fMax;           // Linear range of the VU-meter.
        FAUSTFLOAT fScaleMin, fScaleMax; // Range in dB if needed.
        bool fDB;                        // True if it's a dB VU-meter, false otherwise.
        VUMeterType fStyle;
        juce::String fUnit;
        juce::Label fLabel;               // Name of the VU-meter.
    
        bool isNameDisplayed()
        {
            return (!(getName().startsWith("0x")) && getName().isNotEmpty());
        }
        
        /** Give the right coordinates and size to the text of Label depending on the VU-meter style */
        void setLabelPos()
        {
            if (fStyle == VVUMeter) {
                // -22 on the height because of the text box.
                fLabel.setBounds((getWidth()-50)/2, getHeight()-22, 50, 20);
            } else if (fStyle == HVUMeter) {
                isNameDisplayed() ? fLabel.setBounds(63, (getHeight()-20)/2, 50, 20)
                : fLabel.setBounds(3, (getHeight()-20)/2, 50, 20);
            } else if (fStyle == NumDisplay) {
                fLabel.setBounds((getWidth()-kNumDisplayWidth)/2,
                                 (getHeight()-kNumDisplayHeight/2)/2,
                                 kNumDisplayWidth,
                                 kNumDisplayHeight/2);
            }
        }
        
        /** Contain all the initialization need for our Label */
        void setupLabel(juce::String tooltip)
        {
            setLabelPos();
            fLabel.setEditable(false, false, false);
            fLabel.setJustificationType(juce::Justification::centred);
            fLabel.setText(juce::String((int)*fZone) + " " + fUnit, juce::dontSendNotification);
            fLabel.setTooltip(tooltip);
            addAndMakeVisible(fLabel);
        }
        
        /**
         * \brief   Generic method to draw an horizontal VU-meter.
         * \details Draw the background of the bargraph, and the TextBox box, without taking
         *          care of the actual level of the VU-meter
         * \see     drawHBargraphDB
         * \see     drawHBargraphLin
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   width   Width of the VU-meter widget.
         * \param   height  Height of the VU-meter widget.
         * \param   level   Current level that needs to be displayed.
         * \param   dB      True if it's a db level, false otherwise.
         */
        void drawHBargraph(juce::Graphics& g, int width, int height)
        {
            float x;
            float y = (float)(getHeight()-height)/2;
            if (isNameDisplayed()) {
                x = 120;
                width -= x;
                // VUMeter Name
                g.setColour(juce::Colours::black);
                g.drawText(getName(), 0, y, 60, height, juce::Justification::centredRight);
            } else {
                x = 60;
                width -= x;
            }
            
            // VUMeter Background
            g.setColour(juce::Colours::lightgrey);
            g.fillRect(x, y, (float)width, (float)height);
            g.setColour(juce::Colours::black);
            g.fillRect(x+1.0f, y+1.0f, (float)width-2, (float)height-2);
            
            // Label Window
            g.setColour(juce::Colours::darkgrey);
            g.fillRect((int)x-58, (getHeight()-22)/2, 52, 22);
            g.setColour(juce::Colours::white.withAlpha(0.8f));
            g.fillRect((int)x-57, (getHeight()-20)/2, 50, 20);
            
            // Call the appropriate drawing method for the level.
            fDB ? drawHBargraphDB (g, y, height) : drawHBargraphLin(g, x, y, width, height);
        }
        
        /**
         * Method in charge of drawing the level of a horizontal dB VU-meter.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   y       y coordinate of the VU-meter.
         * \param   height  Height of the VU-meter.
         * \param   level   Current level of the VU-meter, in dB.
         */
        void drawHBargraphDB(juce::Graphics& g, int y, int height)
        {
            // Drawing Scale
            g.setFont(9.0f);
            g.setColour(juce::Colours::white);
            for (int i = -10; i > fMin; i -= 10) {
                paintScale(g, i);
            }
            for (int i = -6; i < fMax; i += 3)  {
                paintScale(g, i);
            }
            
            int alpha = 200;
            FAUSTFLOAT dblevel = dB2Scale(fLevel);
            
            // We need to test here every color changing levels, to avoid to mix colors because of the alpha,
            // and so to start the new color rectangle at the end of the previous one.
            
            // Drawing from the minimal range to the current level, or -10dB.
            g.setColour(juce::Colour((juce::uint8)40, (juce::uint8)160, (juce::uint8)40, (juce::uint8)alpha));
            g.fillRect(dB2x(fMin), y+1.0f, juce::jmin(dB2x(fLevel)-dB2x(fMin), dB2x(-10)-dB2x(fMin)), (float)height-2);
            
            // Drawing from -10dB to the current level, or -6dB.
            if (dblevel > dB2Scale(-10)) {
                g.setColour(juce::Colour((juce::uint8)160, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(dB2x(-10), y+1.0f, juce::jmin(dB2x(fLevel)-dB2x(-10), dB2x(-6)-dB2x(-10)), (float)height-2);
            }
            // Drawing from -6dB to the current level, or -3dB.
            if (dblevel > dB2Scale(-6)) {
                g.setColour(juce::Colour((juce::uint8)220, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(dB2x(-6), y+1.0f, juce::jmin(dB2x(fLevel)-dB2x(-6), dB2x(-3)-dB2x(-6)), (float)height-2);
            }
            // Drawing from -3dB to the current level, or 0dB.
            if (dblevel > dB2Scale(-3)) {
                g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)160, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(dB2x(-3), y+1.0f, juce::jmin(dB2x(fLevel)-dB2x(-3), dB2x(0)-dB2x(-3)), (float)height-2);
            }
            // Drawing from 0dB to the current level, or the max range.
            if (dblevel > dB2Scale(0)) {
                g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)0, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(dB2x(0), y+1.0f, juce::jmin(dB2x(fLevel)-dB2x(0), dB2x(fMax)-dB2x(0)), (float)height-2);
            }
        }
        
        /**
         * Method in charge of drawing the level of a horizontal linear VU-meter.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   x       x coordinate of the VU-meter.
         * \param   y       y coordinate of the VU-meter.
         * \param   height  Height of the VU-meter.
         * \param   width   Width of the VU-meter.
         * \param   level   Current level of the VU-meter, in linear logic.
         */
        void drawHBargraphLin(juce::Graphics& g, int x, int y, int width, int height)
        {
            int alpha = 200;
            juce::Colour c = juce::Colour((juce::uint8)255, (juce::uint8)165, (juce::uint8)0, (juce::uint8)alpha);
            
            // Drawing from the minimal range to the current level, or 20% of the VU-meter
            g.setColour(c.brighter());
            g.fillRect(x+1.0f, y+1.0f, juce::jmin<float>(fLevel*(width-2), 0.2f*(width-2)), (float)height-2);
            // Drawing from 20% of the VU-meter to the current level, or 90% of the VU-meter
            if (fLevel > 0.2f) {
                g.setColour(c);
                g.fillRect(x+1.0f + 0.2f*(width-2), y+1.0f, juce::jmin<float>((fLevel-0.2f) * (width-2), (0.9f-0.2f) * (width-2)), (float)height-2);
            }
            // Drawing from 90% of the VU-meter to the current level, or the maximal range of the VU-meter
            if (fLevel > 0.9f) {
                g.setColour(c.darker());
                g.fillRect(x+1.0f + 0.9f*(width-2), y+1.0f, juce::jmin<float>((fLevel-0.9f) * (width-2), (1.0f-0.9f) * (width-2)), (float)height-2);
            }
        }
        /**
         * \brief   Generic method to draw a vertical VU-meter.
         * \details Draw the background of the bargraph, and the TextBox box, without taking
         *          care of the actual level of the VU-meter
         * \see     drawHBargraphDB
         * \see     drawHBargraphLin
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   width   Width of the VU-meter widget.
         * \param   height  Height of the VU-meter widget.
         * \param   level   Current level that needs to be displayed.
         * \param   dB      True if it's a db level, false otherwise.
         */
        void drawVBargraph(juce::Graphics& g, int width, int height)
        {
            float x = (float)(getWidth()-width)/2;
            float y;
            if (isNameDisplayed()) {
                y = (float)getHeight()-height+15;
                height -= 40;
                // VUMeter Name
                g.setColour(juce::Colours::black);
                g.drawText(getName(), getLocalBounds(), juce::Justification::centredTop);
            } else {
                y = (float)getHeight()-height;
                height -= 25;
            }
            
            // VUMeter Background
            g.setColour(juce::Colours::lightgrey);
            g.fillRect(x, y, (float)width, (float)height);
            g.setColour(juce::Colours::black);
            g.fillRect(x+1.0f, y+1.0f, (float)width-2, (float)height-2);
            
            // Label window
            g.setColour(juce::Colours::darkgrey);
            g.fillRect(juce::jmax((getWidth()-50)/2, 0), getHeight()-23, juce::jmin(getWidth(), 50), 22);
            g.setColour(juce::Colours::white.withAlpha(0.8f));
            g.fillRect(juce::jmax((getWidth()-48)/2, 1), getHeight()-22, juce::jmin(getWidth()-2, 48), 20);
            
            fDB ? drawVBargraphDB (g, x, width) : drawVBargraphLin(g, x, width);
        }
        
        /**
         * Method in charge of drawing the level of a vertical dB VU-meter.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   x       x coordinate of the VU-meter.
         * \param   width   Width of the VU-meter.
         * \param   level   Current level of the VU-meter, in dB.
         */
        void drawVBargraphDB(juce::Graphics& g, int x, int width)
        {
            // Drawing Scale
            g.setFont(9.0f);
            g.setColour(juce::Colours::white);
            for (int i = -10; i > fMin; i -= 10) {
                paintScale(g, i);
            }
            for (int i = -6; i < fMax; i += 3)  {
                paintScale(g, i);
            }
            
            int alpha = 200;
            FAUSTFLOAT dblevel = dB2Scale(fLevel);
            
            // We need to test here every color changing levels, to avoid to mix colors because of the alpha,
            // and so to start the new color rectangle at the end of the previous one.
            
            // Drawing from the minimal range to the current level, or -10dB.
            g.setColour(juce::Colour((juce::uint8)40, (juce::uint8)160, (juce::uint8)40, (juce::uint8)alpha));
            g.fillRect(x+1.0f, juce::jmax(dB2y(fLevel), dB2y(-10)), (float)width-2, dB2y(fMin)-juce::jmax(dB2y(fLevel), dB2y(-10)));
            
            // Drawing from -10dB to the current level, or -6dB.
            if (dblevel > dB2Scale(-10)) {
                g.setColour(juce::Colour((juce::uint8)160, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(x+1.0f, juce::jmax(dB2y(fLevel), dB2y(-6)), (float)width-2, dB2y(-10)-juce::jmax(dB2y(fLevel), dB2y(-6)));
            }
            // Drawing from -6dB to the current level, or -3dB.
            if (dblevel > dB2Scale(-6)) {
                g.setColour(juce::Colour((juce::uint8)220, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(x+1.0f, juce::jmax(dB2y(fLevel), dB2y(-3)), (float)width-2, dB2y(-6)-juce::jmax(dB2y(fLevel), dB2y(-3)));
            }
            // Drawing from -3dB to the current level, or 0dB.
            if (dblevel > dB2Scale(-3)) {
                g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)160, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(x+1.0f, juce::jmax(dB2y(fLevel), dB2y(0)), (float)width-2, dB2y(-3)-juce::jmax(dB2y(fLevel), dB2y(0)));
            }
            // Drawing from 0dB to the current level, or the maximum range.
            if (dblevel > dB2Scale(0)) {
                g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)0, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(x+1.0f, juce::jmax(dB2y(fLevel), dB2y(fMax)), (float)width-2, dB2y(0)-juce::jmax(dB2y(fLevel), dB2y(fMax)));
            }
        }
        
        /**
         * Method in charge of drawing the level of a vertical linear VU-meter.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   x       x coordinate of the VU-meter.
         * \param   width   Width of the VU-meter.
         * \param   level   Current level of the VU-meter, in linear logic.
         */
        void drawVBargraphLin(juce::Graphics& g, int x, int width)
        {
            int alpha = 200;
            juce::Colour c = juce::Colour((juce::uint8)255, (juce::uint8)165, (juce::uint8)0, (juce::uint8)alpha);
            
            // Drawing from the minimal range to the current level, or 20% of the VU-meter.
            g.setColour(c.brighter());
            g.fillRect(x+1.0f, juce::jmax(lin2y(fLevel), lin2y(0.2)), (float)width-2, lin2y(fMin)-juce::jmax(lin2y(fLevel), lin2y(0.2)));
            
            // Drawing from 20% of the VU-meter to the current level, or 90% of the VU-meter.
            if (fLevel > 0.2f) {
                g.setColour(c);
                g.fillRect(x+1.0f, juce::jmax(lin2y(fLevel), lin2y(0.9)), (float)width-2, lin2y(0.2)-juce::jmax(lin2y(fLevel), lin2y(0.9)));
            }
            
            // Drawing from 90% of the VU-meter to the current level, or the maximum range.
            if (fLevel > 0.9f) {
                g.setColour(c.darker());
                g.fillRect(x+1.0f, juce::jmax(lin2y(fLevel), lin2y(fMax)), (float)width-2, lin2y(0.9)-juce::jmax(lin2y(fLevel), lin2y(fMax)));
            }
        }
        
        /**
         * Method in charge of drawing the LED VU-meter, dB or not.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   width   Width of the LED.
         * \param   height  Height of the LED.
         * \param   level   Current level of the VU-meter, dB or not.
         */
        void drawLed(juce::Graphics& g, int width, int height)
        {
            float x = (float)(getWidth() - width)/2;
            float y = (float)(getHeight() - height)/2;
            g.setColour(juce::Colours::black);
            g.fillEllipse(x, y, width, height);
            
            if (fDB) {
                int alpha = 200;
                FAUSTFLOAT dblevel = dB2Scale(fLevel);
                
                // Adjust the color depending on the current level
                g.setColour(juce::Colour((juce::uint8)40, (juce::uint8)160, (juce::uint8)40, (juce::uint8)alpha));
                if (dblevel > dB2Scale(-10)) {
                    g.setColour(juce::Colour((juce::uint8)160, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                }
                if (dblevel > dB2Scale(-6)) {
                    g.setColour(juce::Colour((juce::uint8)220, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                }
                if (dblevel > dB2Scale(-3)) {
                    g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)160, (juce::uint8)20, (juce::uint8)alpha));
                }
                if (dblevel > dB2Scale(0))  {
                    g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)0, (juce::uint8)20, (juce::uint8)alpha));
                }
                
                g.fillEllipse(x+1, y+1, width-2, height-2);
            } else {
                // The alpha depend on the level, from 0 to 1
                g.setColour(juce::Colours::red.withAlpha((float)fLevel));
                g.fillEllipse(x+1, y+1, width-2, height-2);
            }
        }
        
        /**
         * Method in charge of drawing the Numerical Display VU-meter, dB or not.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   width   Width of the Numerical Display.
         * \param   height  Height of the Numerical Display.
         * \param   level   Current level of the VU-meter.
         */
        void drawNumDisplay(juce::Graphics& g, int width, int height)
        {
            // Centering it
            int x = (getWidth()-width) / 2;
            int y = (getHeight()-height) / 2;
            
            // Draw box.
            g.setColour(juce::Colours::darkgrey);
            g.fillRect(x, y, width, height);
            g.setColour(juce::Colours::white.withAlpha(0.8f));
            g.fillRect(x+1, y+1, width-2, height-2);
            
            // Text is handled by the setLabelPos() function
        }
        
        /** Convert a dB level to a y coordinate, for easier draw methods. */
        FAUSTFLOAT dB2y(FAUSTFLOAT dB)
        {
            FAUSTFLOAT s0 = fScaleMin;      // Minimal range.
            FAUSTFLOAT s1 = fScaleMax;      // Maximum range.
            FAUSTFLOAT sx = dB2Scale(dB);   // Current level.
            
            int h;
            int treshold;   // Value depend if the name is displayed
            
            if (isNameDisplayed()) {
                h = getHeight()-42; // 15 pixels for the VU-Meter name,
                // 25 for the textBox, 2 pixels margin.
                treshold = 16;      // 15 pixels for the VU-Meter name.
            } else {
                h = getHeight()-27; // 25 for the textBox, 2 pixels margin.
                treshold = 1;       // 1 pixel margin.
            }
            
            return (h - h*(s0-sx)/(s0-s1)) + treshold;
        }
        
        /** Convert a linear level to a y coordinate, for easier draw methods. */
        FAUSTFLOAT lin2y(FAUSTFLOAT level)
        {
            int h;
            int treshold;
            
            if (isNameDisplayed()) {
                h = getHeight()-42; // 15 pixels for the VU-Meter name,
                // 25 for the textBox, 2 pixels margin.
                treshold = 16;      // 15 pixels for the VU-Meter name.
            } else {
                h = getHeight()-27; // 25 for the textBox, 2 pixels margin.
                treshold = 1;       // 1 pixel margin.
            }
            
            return h * (1 - level) + treshold;
        }
        
        /** Convert a dB level to a x coordinate, for easier draw methods. */
        FAUSTFLOAT dB2x(FAUSTFLOAT dB)
        {
            FAUSTFLOAT s0 = fScaleMin;      // Minimal range.
            FAUSTFLOAT s1 = fScaleMax;      // Maximal range.
            FAUSTFLOAT sx = dB2Scale(dB);   // Current level.
            
            int w;
            int treshold;
            
            if (isNameDisplayed()) {
                w = getWidth()-122; // 60 pixels for the VU-Meter name,
                // 60 for the TextBox, 2 pixels margin.
                treshold = 121;     // 60 pixels for the VU-Meter name,
                // 60 for the TextBox, and 1 pixel margin.
            } else {
                w = getWidth()-62;  // 60 pixels for the TextBox, 2 pixels margin.
                treshold = 61;      // 60 pixels for the TextBox, 1 pixel margin.
            }
            
            return treshold + w - w*(s1-sx)/(s1-s0);
        }
        
        /** Write the different level included in the VU-Meter range. */
        void paintScale(juce::Graphics& g, float num)
        {
            juce::Rectangle<int> r;
            
            if (fStyle == VVUMeter) {
                r = juce::Rectangle<int>((getWidth()-(kVBargraphWidth/2))/2 + 1,  // Left side of the VU-Meter.
                                         dB2y(num),                               // Vertically centred with 20 height.
                                         (kVBargraphWidth/2)-2,                   // VU-Meter width with margin.
                                         20);                                     // 20 height.
                g.drawText(juce::String(num), r, juce::Justification::centredRight, false);
            } else {
                r = juce::Rectangle<int>(dB2x(num)-10,                            // Horizontally centred with 20 width.
                                        (getHeight()-kHBargraphHeight/2)/2 + 1,  // Top side of the VU-Meter.
                                        20,                                      // 20 width.
                                        (kHBargraphHeight/2)-2);                 // VU-Meter height with margin
                g.drawText(juce::String(num), r, juce::Justification::centredTop, false);
            }
        }
        
        /** Set the level, keep it in the range of the VU-Meter, and set the TextBox text. */
        void setLevel()
        {
            FAUSTFLOAT rawLevel = *fZone;
        #if JUCE_DEBUG
            if (std::isnan(rawLevel)) {
                std::cerr << "uiVUMeter: NAN\n";
            }
        #endif
            if (fDB) {
                fLevel = range(rawLevel);
            } else {
                fLevel = range((rawLevel-fMin)/(fMax-fMin));
            }
            fLabel.setText(juce::String((int)rawLevel) + " " + fUnit, juce::dontSendNotification);
        }
        
        FAUSTFLOAT range(FAUSTFLOAT level) { return (level > fMax) ? fMax : ((level < fMin) ? fMin : level); }
    
    public:
    
        /**
         * \brief   Constructor.
         * \details Initialize the uiComponent variables and the VU-meter specific ones.
         *
         * \param   gui, zone, w, h, tooltip, label     uiComponent variables.
         * \param   mini                                Minimal value of the VU-meter range.
         * \param   maxi                                Maximal value of the VU-meter range.
         * \param   unit                                Unit of the VU-meter (dB or not).
         * \param   style                               Type of the VU-meter (see VUMeterType).
         * \param   vert                                True if vertical, false if horizontal.
         */
        uiVUMeter (GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, juce::String label, FAUSTFLOAT mini, FAUSTFLOAT maxi, juce::String unit, juce::String tooltip, VUMeterType style, bool vert)
            : uiComponent(gui, zone, w, h, label), fMin(mini), fMax(maxi), fStyle(style)
        {
            fLevel = 0;         // Initialization of the level
            startTimer(50);     // Launch a timer that trigger a callback every 50ms
            this->fUnit = unit;
            fDB = (unit == "dB");
            
            if (fDB) {
                // Conversion in dB of the range
                fScaleMin = dB2Scale(fMin);
                fScaleMax = dB2Scale(fMax);
            }
            setTooltip(tooltip);
            
            // No text editor for LEDs
            if (fStyle != Led) {
                setupLabel(tooltip);
            }
        }
        
        /** Method called by the timer every 50ms, to refresh the VU-meter if it needs to */
        void timerCallback() override
        {
            if (isShowing()) {
                //Force painting at the initialisation
                bool forceRepaint = (fLevel == 0);
                FAUSTFLOAT lastLevel = fLevel;   //t-1
                setLevel(); //t
                
                // Following condition means that we're repainting our VUMeter only if
                // there's one or more changing pixels between last state and this one,
                // and if the curent level is included in the VUMeter range. It improves
                // performances a lot in IDLE. It's the same for the other style of VUMeter
                
                if (fDB) {
                    switch (fStyle) {
                        case VVUMeter:
                            if (((int)dB2y(lastLevel) != (int)dB2y(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case HVUMeter:
                            if (((int)dB2x(lastLevel) != (int)dB2x(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case NumDisplay:
                            if (((int)lastLevel != (int)fLevel && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case Led:
                            if ((dB2Scale(lastLevel) != dB2Scale(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        default:
                            break;
                    }
                } else {
                    switch (fStyle) {
                        case VVUMeter:
                            if (((int)lin2y(lastLevel) != (int)lin2y(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case HVUMeter:
                            if ((std::abs(lastLevel-fLevel) > 0.01 && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case NumDisplay:
                            if ((std::abs(lastLevel-fLevel) > 0.01 && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case Led:
                            if (((int)lastLevel != (int)fLevel && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        default:
                            break;
                    }
                }
            } else {
                fLevel = 0;
            }
        }
        
        /**
         * Call the appropriate drawing method according to the VU-meter style
         * \see drawLed
         * \see drawNumDisplay
         * \see drawVBargraph
         * \see drawHBargraph
         */
        void paint(juce::Graphics& g) override
        {
            switch (fStyle) {
                case Led:
                    drawLed(g, kLedWidth, kLedHeight);
                    break;
                case NumDisplay:
                    drawNumDisplay(g, kNumDisplayWidth, kNumDisplayHeight/2);
                    break;
                case VVUMeter:
                    drawVBargraph(g, kVBargraphWidth/2, getHeight());
                    break;
                case HVUMeter:
                    drawHBargraph(g, getWidth(), kHBargraphHeight/2);
                    break;
                default:
                    break;
            }
        }
        
        /** Set the Label position whenever the layout size changes. */
        void resized() override
        {
            setLabelPos();
        }
        
        void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
        }
    
};

/** Intern class for tab widget */
class uiTabBox : public uiBase, public juce::TabbedComponent
{
    
public:
    /**
     * \brief   Constructor.
     * \details Initalize the juce::TabbedComponent tabs to be at top, and the uiTabBox size at 0
     */
    uiTabBox():uiBase(),juce::TabbedComponent(juce::TabbedButtonBar::TabsAtTop)
    {}
    
    /**
     * Initialize all his child ratios (1 uiBox per tabs), the LookAndFeel
     * and the uiTabBox size to fit the biggest of its child.
     */
    void init(juce::Component* comp = nullptr) override
    {
        for (int i = 0; i < getNumTabs(); i++) {
            Component* comp = getTabContentComponent(i);
            uiBase* base_comp = dynamic_cast<uiBase*>(comp);
            base_comp->init(comp);
            
            // The TabbedComponent size should be as big as its bigger child's dimension, done here
            fTotalWidth = juce::jmax(fTotalWidth, base_comp->getTotalWidth());
            fTotalHeight = juce::jmax(fTotalHeight, base_comp->getTotalHeight());
        }
        
        fTotalHeight += 30;  // 30 height for the TabBar.
    }
    
    void setRecommendedSize() override
    {
        for (int i = 0; i < getNumTabs(); i++) {
            uiBase* comp = dynamic_cast<uiBase*>(getTabContentComponent(i));
            comp->setRecommendedSize();
            
            // The TabbedComponent size should be as big as its bigger child's dimension, done here
            fTotalWidth = juce::jmax(fTotalWidth, comp->getTotalWidth());
            fTotalHeight = juce::jmax(fTotalHeight, comp->getTotalHeight());
        }
        
        fTotalHeight += 30;  // 30 height for the TabBar
    }
    
    void add(Component* comp) override
    {
        // Name of the component is moved in Tab (so removed from component)
        juce::TabbedComponent::addTab(comp->getName(), juce::Colours::white, comp, true);
        comp->setName("");
    }
    
};

/**
 * \brief   Intern class for box widgets
 * \details That's the class where the whole layout is calculated.
 */
class uiBox : public uiBase, public juce::Component
{
  
    private:
    
        bool fIsVertical;
    
        bool isNameDisplayed()
        {
            return (!(getName().startsWith("0x")) && getName().isNotEmpty());
        }
    
        /**
         * \brief   Return the vertical dimension size for a child to be displayed in.
         *
         */
        int getVSpaceToRemove()
        {
            // Checking if the name is displayed, to give to good amount space for child components
            // kNameHeight pixels is the bix name, kMargin pixel per child components for the margins
            if (isNameDisplayed()) {
                return (getHeight() - kNameHeight - kMargin * getNumChildComponents());
            } else {
                return (getHeight() - kMargin * getNumChildComponents());
            }
        }
    
        /**
         * \brief   Return the vertical dimension size for a child to be displayed in.
         *
         */
        int getHSpaceToRemove()
        {
            // Don't need to check for an horizontal box, as it height doesn't matter
            return (getWidth() - kMargin * getNumChildComponents());
        }
    
    public:
        /**
         * \brief   Constructor.
         * \details Initialize uiBase variables and uiBox specific ones.
         *
         * \param   vert        True if it's a vertical box, false otherwise.
         * \param   boxName     Name of the uiBox.
         */
        uiBox(bool vert, juce::String boxName): uiBase(0,0), juce::Component(boxName), fIsVertical(vert)
        {}
    
        /**
         * \brief   Destructor.
         * \details Delete all uiBox recusively, but not the uiComponent,
         *          because it's handled by the uiItem FAUST objects.
         */
        virtual ~uiBox()
        {
            /*
             Deleting boxes, from leaves to root:
             - leaves (uiComponent) are deleted by the uiItem mechanism
             - containers (uiBox and uiTabBox) have to be explicitly deleted
             */
            for (int i = getNumChildComponents()-1; i >= 0; i--) {
                delete dynamic_cast<uiBox*>(getChildComponent(i));
                delete dynamic_cast<uiTabBox*>(getChildComponent(i));
            }
        }

        /**
         * \brief   Initialization of the DisplayRect and Total size.
         * \details Calculate the correct size for each box, depending on its child sizes.
         */
        void setRecommendedSize() override
        {
            // Initialized each time
            fDisplayRectWidth = fDisplayRectHeight = 0;
            
            // Display rectangle size is the sum of a dimension on a side, and the max of the other one
            // on the other side, depending on its orientation (horizontal/vertical).
            // Using child's totalSize, because the display rectangle size need to be as big as
            // all of its child components with their margins included.
            for (int j = 0; j < getNumChildComponents(); j++) {
                uiBase* base_comp = dynamic_cast<uiBase*>(getChildComponent(j));
                if (fIsVertical) {
                    fDisplayRectWidth = juce::jmax(fDisplayRectWidth, base_comp->getTotalWidth());
                    fDisplayRectHeight += base_comp->getTotalHeight();
                } else {
                    fDisplayRectWidth += base_comp->getTotalWidth();
                    fDisplayRectHeight = juce::jmax(fDisplayRectHeight, base_comp->getTotalHeight());
                }
            }
            
            fTotalHeight = fDisplayRectHeight;
            fTotalWidth = fDisplayRectWidth;
            
            // Adding kMargin pixels of margins per child component on a dimension, and just kMargin on
            // the other one, depending on its orientation
            
            if (fIsVertical) {
                fTotalHeight += kMargin * getNumChildComponents();
                fTotalWidth += kMargin;
            } else {
                fTotalWidth += kMargin * getNumChildComponents();
                fTotalHeight += kMargin;
            }
         
            // Adding kNameHeight pixels on its height to allow the name to be displayed
            if (isNameDisplayed()) {
                fTotalHeight += kNameHeight;
            }
        }

        /** Initiate the current box ratio, and its child's ones recursively. */
        void init(juce::Component* comp = nullptr) override
        {
            uiBase::init(this);
            
            // Going through the Component tree recursively
            for (int i = 0; i < getNumChildComponents(); i++) {
                Component* comp = getChildComponent(i);
                uiBase* base_comp = dynamic_cast<uiBase*>(comp);
                base_comp->init(comp);
            }
        }

        /**
         * \brief   Main layout function.
         * \details Allow to place all uiBase child correctly according to their ratios
         *          and the current box size.
         *
         * \param   displayRect    Absolute raw bounds of the current box (with margins
         *                          and space for the title).
         */
        void resized() override
        {
            juce::Rectangle<int> displayRect = getBounds();
            
            // Deleting space for the box name if it needs to be shown
            if (isNameDisplayed()) {
                displayRect.removeFromTop(kNameHeight);
            }
            
            // Putting the margins
            displayRect.reduce(kMargin/2, kMargin/2);
            
            // Give child components an adapt size depending on its ratio and the current box size
            for (int i = 0; i < getNumChildComponents(); i++) {
                juce::Component* comp = getChildComponent(i);
                uiBase* base_comp = dynamic_cast<uiBase*>(comp);
                
                if (fIsVertical) {
                    int heightToRemove = getVSpaceToRemove() * base_comp->getVRatio();
                    // Remove the space needed from the displayRect, and translate it to show the margins
                    base_comp->setRelativeSize(comp, displayRect.removeFromTop(heightToRemove).translated(0, kMargin * i));
                } else {
                    int widthToRemove = getHSpaceToRemove() * base_comp->getHRatio();
                    // Remove the space needed from the displayRect, and translate it to show the margins
                    base_comp->setRelativeSize(comp, displayRect.removeFromLeft(widthToRemove).translated(kMargin * i, 0));
                }
            }
        }

        /** 
         * Fill the uiBox bounds with a grey color, different shades depending on its order.
         * Write the uiBox name if it needs to.
         */
        void paint(juce::Graphics& g) override
        {
            // Fill the box background in gray shades
            g.setColour(juce::Colours::black.withAlpha(0.05f));
            g.fillRect(getLocalBounds());

            // Display the name if it's needed
            if (isNameDisplayed()) {
                g.setColour(juce::Colours::black);
                g.drawText(getName(), getLocalBounds().withHeight(kNameHeight), juce::Justification::centred);
            }
        }
        
        void add(juce::Component* comp) override
        {
            addAndMakeVisible(comp);
        }
    
};

/** Class in charge of doing the glue between FAUST and JUCE */
class JuceGUI : public GUI, public MetaDataUI, public juce::Component
{
    
    private:
    
        bool fDefault = true;
        std::stack<uiBase*> fBoxStack;
        uiBase* fCurrentBox = nullptr;   // Current box used in buildUserInterface logic.
        
        int fRadioGroupID;               // In case of radio buttons.
        std::unique_ptr<juce::LookAndFeel> fLaf = std::make_unique<juce::LookAndFeel_V4>();
    
        FAUSTFLOAT defaultVal(FAUSTFLOAT* zone, FAUSTFLOAT def)
        {
            return (fDefault) ? def : *zone;
        }
    
        /** Add generic box to the user interface. */
        void openBox(uiBase* box)
        {
            if (fCurrentBox) {
                fCurrentBox->add(dynamic_cast<juce::Component*>(box));
                fBoxStack.push(fCurrentBox);
            }
            fCurrentBox = box;
        }
     
        /** Add a slider to the user interface. */
        void addSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, int kWidth, int kHeight, SliderType type)
        {
            if (isKnob(zone)) {
                addKnob(label, zone, defaultVal(zone, init), min, max, step);
            } else if (isRadio(zone)) {
                addRadioButtons(label, zone, defaultVal(zone, init), min, max, step, fRadioDescription[zone].c_str(), false);
            } else if (isMenu(zone)) {
                addMenu(label, zone, defaultVal(zone, init), min, max, step, fMenuDescription[zone].c_str());
            } else {
                fCurrentBox->add(new uiSlider(this, zone, kWidth, kHeight, defaultVal(zone, init), min, max, step, juce::String(label), juce::String(fUnit[zone]), juce::String(fTooltip[zone]), getScale(zone), type));
            }
        }
        
        /** Add a radio buttons to the user interface. */
        void addRadioButtons(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, const char* mdescr, bool vert)
        {
            std::vector<std::string> names;
            std::vector<double> values;
            parseMenuList(mdescr, names, values); // Set names and values vectors
            
            // and not just n checkButtons :
            // TODO : check currently unused checkButtonWidth...
            int checkButtonWidth = 0;
            for (int i = 0; i < names.size(); i++) {
                // Checking the maximum of horizontal space needed to display the radio buttons
                checkButtonWidth = juce::jmax(juce::Font().getStringWidth(juce::String(names[i])) + 15, checkButtonWidth);
            }
            
            if (vert) {
                fCurrentBox->add(new uiRadioButton(this, zone, juce::String(label), kCheckButtonWidth, names.size() * (kRadioButtonHeight - 25) + 25, defaultVal(zone, init), min, max, true, names, values, juce::String(fTooltip[zone]), fRadioGroupID++));
            } else {
                fCurrentBox->add(new uiRadioButton(this, zone, juce::String(label), kCheckButtonWidth, kRadioButtonHeight, defaultVal(zone, init), min, max, false, names, values, juce::String(fTooltip[zone]), fRadioGroupID++));
            }
        }
        
        /** Add a menu to the user interface. */
        void addMenu(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, const char* mdescr)
        {
            fCurrentBox->add(new uiMenu(this, zone, juce::String(label), kMenuWidth, kMenuHeight, defaultVal(zone, init), min, max, juce::String(fTooltip[zone]), mdescr));
        }
        
        /** Add a ciruclar slider to the user interface. */
        void addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
            fCurrentBox->add(new uiSlider(this, zone, kKnobWidth, kKnobHeight, defaultVal(zone, init), min, max, step, juce::String(label), juce::String(fUnit[zone]), juce::String(fTooltip[zone]), getScale(zone), Knob));
        }
        
        /** Add a bargraph to the user interface. */
        void addBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, int kWidth, int kHeight, VUMeterType type)
        {
            if (isLed(zone)) {
                addLed(juce::String(label), zone, min, max);
            } else if (isNumerical(zone)) {
                addNumericalDisplay(juce::String(label), zone, min, max);
            } else {
                fCurrentBox->add(new uiVUMeter (this, zone, kWidth, kHeight, juce::String(label), min, max, juce::String(fUnit[zone]), juce::String(fTooltip[zone]), type, false));
            }
        }
        
    public:
        /**
         * \brief   Constructor.
         * \details Initialize the JuceGUI specific variables. 
         */
        JuceGUI(bool def = true):fDefault(def), fRadioGroupID(1) // fRadioGroupID must start at 1
        {
            setLookAndFeel(fLaf.get());
        }
        
        /**
         * \brief   Destructor.
         * \details Delete root box used in buildUserInterface logic.
         */
        virtual ~JuceGUI()
        {
            setLookAndFeel(nullptr);
            delete fCurrentBox;
        }

        /** Return the size of the FAUST program */
        juce::Rectangle<int> getSize()
        {
            // Mininum size in case of empty GUI
            if (fCurrentBox) {
                juce::Rectangle<int> res = fCurrentBox->getSize();
                res.setSize(std::max<int>(1, res.getWidth()), std::max<int>(1, res.getHeight()));
                return res;
            } else {
                return juce::Rectangle<int>(0, 0, 1, 1);
            }
        }

        /** Initialize the uiTabBox component to be visible. */
        virtual void openTabBox(const char* label) override
        {
            openBox(new uiTabBox());
        }
        
        /** Add a new vertical box to the user interface. */
        virtual void openVerticalBox(const char* label) override
        {
            openBox(new uiBox(true, juce::String(label)));
        }

        /** Add a new horizontal box to the user interface. */
        virtual void openHorizontalBox(const char* label) override
        {
            openBox(new uiBox(false, juce::String(label)));
        }

        /** Close the current box. */
        virtual void closeBox() override
        {
            fCurrentBox->setRecommendedSize();
            
            if (fBoxStack.empty()) {
                // Add root box in JuceGUI component
                addAndMakeVisible(dynamic_cast<juce::Component*>(fCurrentBox));
                fCurrentBox->init();
                // Force correct draw
                resized();
            } else {
                fCurrentBox = fBoxStack.top();
                fBoxStack.pop();
            }
        }
     
        /** Add an horizontal slider to the user interface. */
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        {
            addSlider(label, zone, init, min, max, step, kHSliderWidth, kHSliderHeight, HSlider);
        }
        
        /** Add a vertical slider to the user interface. */
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        {
            int newWidth = juce::jmax(juce::Font().getStringWidth(juce::String(label)), kVSliderWidth) + kMargin;
            addSlider(label, zone, init, min, max, step, newWidth, kVSliderHeight, VSlider);
        }
        
        /** Add a button to the user interface. */
        virtual void addButton(const char* label, FAUSTFLOAT* zone) override
        {
            fCurrentBox->add(new uiButton(this, zone, kButtonWidth, kButtonHeight, juce::String(label), juce::String(fTooltip[zone])));
        }
        
        /** Add a check button to the user interface. */
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) override
        {
            // newWidth is his text size, plus the check box size
            int newWidth = juce::Font().getStringWidth(juce::String(label)) + kCheckButtonWidth;
            fCurrentBox->add(new uiCheckButton(this, zone, newWidth, kCheckButtonHeight, juce::String(label), juce::String(fTooltip[zone])));
        }
        
        /** Add a numerical entry to the user interface. */
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        {
            // kMargin pixels between the slider and his name
            int newWidth = juce::Font().getStringWidth(juce::String(label)) + kNumEntryWidth + kMargin;
            fCurrentBox->add(new uiSlider(this, zone, newWidth, kNumEntryHeight, defaultVal(zone, init), min, max, step, juce::String(label), juce::String(fUnit[zone]), juce::String(fTooltip[zone]), getScale(zone), NumEntry));
        }
        
        /** Add a vertical bargraph to the user interface. */
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
        {
            addBargraph(label, zone, min, max, kVBargraphWidth, kVBargraphHeight, VVUMeter);
        }
        
        /** Add a vertical bargraph to the user interface. */
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
        {
            addBargraph(label, zone, min, max, kHBargraphWidth, kHBargraphHeight, HVUMeter);
        }
      
        /** Add a LED to the user interface. */
        void addLed(juce::String label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fCurrentBox->add(new uiVUMeter(this, zone, kLedWidth, kLedHeight, label, min, max, juce::String(fUnit[zone]), juce::String(fTooltip[zone]), Led, false));
        }
        
        /** Add a numerical display to the user interface. */
        void addNumericalDisplay(juce::String label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {
            fCurrentBox->add(new uiVUMeter(this, zone, kNumDisplayWidth, kNumDisplayHeight, label, min, max, juce::String(fUnit[zone]), juce::String(fTooltip[zone]), NumDisplay, false));
        }
        
        /** Declare a metadata. */
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* value) override
        {
            MetaDataUI::declare(zone, key, value);
        }

        /** Resize its child to match the new bounds */
        void resized() override
        {
            if (fCurrentBox) {
                dynamic_cast<Component*>(fCurrentBox)->setBounds(getLocalBounds());
            }
        }
    
};

#endif
/**************************  END  JuceGUI.h **************************/
#endif
/************************** BEGIN JuceParameterUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef JuceParameterUI_H
#define JuceParameterUI_H

#include "../JuceLibraryCode/JuceHeader.h"


// Link AudioParameterBool with on/off parameter

struct FaustPlugInAudioParameterBool : public juce::AudioParameterBool, public uiOwnedItem {
    
    FaustPlugInAudioParameterBool(GUI* gui, FAUSTFLOAT* zone, const std::string& path, const std::string& label)
    :juce::AudioParameterBool(path, label, false), uiOwnedItem(gui, zone)
    {}
    
    virtual ~FaustPlugInAudioParameterBool() {}
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        setValueNotifyingHost(float(v));
    }
    
    virtual void setValue (float newValue) override
    {
        modifyZone(FAUSTFLOAT(newValue));
    }
    
};

// Link AudioParameterFloat with range parameters

struct FaustPlugInAudioParameterFloat : public juce::AudioParameterFloat, public uiOwnedItem {
    
    FaustPlugInAudioParameterFloat(GUI* gui, FAUSTFLOAT* zone, const std::string& path, const std::string& label, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    :juce::AudioParameterFloat(path, label, float(min), float(max), float(init)), uiOwnedItem(gui, zone)
    {}
    
    virtual ~FaustPlugInAudioParameterFloat() {}
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        if (v >= range.start && v <= range.end) {
            setValueNotifyingHost(range.convertTo0to1(float(v)));
        }
    }
    
    virtual void setValue (float newValue) override
    {
        modifyZone(FAUSTFLOAT(range.convertFrom0to1(newValue)));
    }
    
};

// A class to create AudioProcessorParameter objects for each zone

class JuceParameterUI : public GUI, public PathBuilder {
    
    private:
        
        juce::AudioProcessor* fProcessor;
        
    public:
        
        JuceParameterUI(juce::AudioProcessor* processor):fProcessor(processor)
        {}
    
        virtual ~JuceParameterUI() {}
        
        // -- widget's layouts
        
        virtual void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        virtual void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        virtual void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        virtual void closeBox()
        {
            popLabel();
        }
        
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterBool(this, zone, buildPath(label), label));
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterBool(this, zone, buildPath(label), label));
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterFloat(this, zone, buildPath(label), label, init, min, max, step));
        }
        
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterFloat(this, zone, buildPath(label), label, init, min, max, step));
        }
        
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterFloat(this, zone, buildPath(label), label, init, min, max, step));
        }
        
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterFloat(this, zone, buildPath(label), label, 0, min, max, 0));
        }
        
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterFloat(this, zone, buildPath(label), label, 0, min, max, 0));
        }
    
};

#endif
/**************************  END  JuceParameterUI.h **************************/
/************************** BEGIN JuceStateUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef JuceStateUI_H
#define JuceStateUI_H

#include "../JuceLibraryCode/JuceHeader.h"


// A class to save/restore DSP state using JUCE, which also set default values at construction time.

struct JuceStateUI : public MapUI {
    
    bool fRestored;
    
    JuceStateUI():fRestored(false) {}
    virtual ~JuceStateUI() {}
    
    void getStateInformation (juce::MemoryBlock& destData)
    {
        juce::MemoryOutputStream stream (destData, true);
        
        // Write path and values
        if (sizeof(FAUSTFLOAT) == sizeof(float)) {
            for (const auto& it : fPathZoneMap) {
                stream.writeString(it.first);
                stream.writeFloat(*it.second);
            }
        } else {
            for (const auto& it : fPathZoneMap) {
                stream.writeString(it.first);
                stream.writeDouble(*it.second);
            }
        }
    }
    
    void setStateInformation (const void* data, int sizeInBytes)
    {
        fRestored = true;
        juce::MemoryInputStream stream (data, static_cast<size_t> (sizeInBytes), false);
        std::string path;
        
        // Read path then value and try to restore them
        if (sizeof(FAUSTFLOAT) == sizeof(float)) {
            while ((path = stream.readString().toStdString()) != "") {
                setParamValue(path, stream.readFloat());
            }
        } else {
            while ((path = stream.readString().toStdString()) != "") {
                setParamValue(path, stream.readDouble());
            }
        }
    }
    
    // -- active widgets
    // use MapUI derived methods
    
    // -- passive widgets
    // empty si we don't want to save/restore them
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax) {}
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax) {}
    
};

#endif
/**************************  END  JuceStateUI.h **************************/

// Always included otherwise -i mode sometimes fails...

#if defined(SOUNDFILE)
/************************** BEGIN SoundUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef __SoundUI_H__
#define __SoundUI_H__

#include <map>
#include <vector>
#include <string>
#include <iostream>


#if defined(__APPLE__) && !defined(__VCVRACK__) && !defined(JUCE_32BIT) && !defined(JUCE_64BIT)
#include <CoreFoundation/CFBundle.h>
#endif

// Always included otherwise -i mode later on will not always include it (with the conditional includes)
/************************** BEGIN Soundfile.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __Soundfile__
#define __Soundfile__

#include <string.h>
#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#define BUFFER_SIZE 1024
#define SAMPLE_RATE 44100
#define MAX_CHAN 64
#define MAX_SOUNDFILE_PARTS 256

#ifdef _MSC_VER
#define PRE_PACKED_STRUCTURE __pragma(pack(push, 1))
#define POST_PACKED_STRUCTURE \
    ;                         \
    __pragma(pack(pop))
#else
#define PRE_PACKED_STRUCTURE
#define POST_PACKED_STRUCTURE __attribute__((__packed__))
#endif

/*
 The soundfile structure to be used by the DSP code. Soundfile has a MAX_SOUNDFILE_PARTS parts 
 (even a single soundfile or an empty soundfile). 
 fLength, fOffset and fSR fields are filled accordingly by repeating
 the actual parts if needed.
 
 It has to be 'packed' to that the LLVM backend can correctly access it.

 Index computation:
    - p is the current part number [0..MAX_SOUNDFILE_PARTS-1] (must be proved by the type system)
    - i is the current position in the part. It will be constrained between [0..length]
    - idx(p,i) = fOffset[p] + max(0, min(i, fLength[p]));
*/

PRE_PACKED_STRUCTURE
struct Soundfile {
    void* fBuffers; // will be set with double** or float** chosen at runtime
    int* fLength;   // length of each part (so fLength[P] contains the length in frames of part P)
    int* fSR;       // sample rate of each part (so fSR[P] contains the SR of part P)
    int* fOffset;   // offset of each part in the global buffer (so fOffset[P] contains the offset in frames of part P)
    int fChannels;  // max number of channels of all concatenated files
    bool fIsDouble; // keep the sample format (float or double)

    Soundfile(int cur_chan, int length, int max_chan, bool is_double)
    {
        fLength   = new int[MAX_SOUNDFILE_PARTS];
        fSR       = new int[MAX_SOUNDFILE_PARTS];
        fOffset   = new int[MAX_SOUNDFILE_PARTS];
        fIsDouble = is_double;
        fChannels = cur_chan;
        if (fIsDouble) {
            fBuffers = allocBufferReal<double>(cur_chan, length, max_chan);
        } else {
            fBuffers = allocBufferReal<float>(cur_chan, length, max_chan);
        }
    }
    
    template <typename REAL>
    void* allocBufferReal(int cur_chan, int length, int max_chan)
    {
        REAL** buffers = new REAL*[max_chan];
        for (int chan = 0; chan < cur_chan; chan++) {
            buffers[chan] = new REAL[length];
            memset(buffers[chan], 0, sizeof(REAL) * length);
        }
        return buffers;
    }
    
    void copyToOut(int size, int channels, int max_channels, int offset, void* buffer)
    {
        if (fIsDouble) {
            copyToOutReal<double>(size, channels, max_channels, offset, buffer);
       } else {
            copyToOutReal<float>(size, channels, max_channels, offset, buffer);
        }
    }
    
    void shareBuffers(int cur_chan, int max_chan)
    {
        // Share the same buffers for all other channels so that we have max_chan channels available
        if (fIsDouble) {
            for (int chan = cur_chan; chan < max_chan; chan++) {
                static_cast<double**>(fBuffers)[chan] = static_cast<double**>(fBuffers)[chan % cur_chan];
            }
        } else {
            for (int chan = cur_chan; chan < max_chan; chan++) {
                static_cast<float**>(fBuffers)[chan] = static_cast<float**>(fBuffers)[chan % cur_chan];
            }
        }
    }
    
    template <typename REAL>
    void copyToOutReal(int size, int channels, int max_channels, int offset, void* buffer)
    {
        for (int sample = 0; sample < size; sample++) {
            for (int chan = 0; chan < channels; chan++) {
                static_cast<REAL**>(fBuffers)[chan][offset + sample] = static_cast<REAL*>(buffer)[sample * max_channels + chan];
            }
        }
    }
    
    template <typename REAL>
    void getBuffersOffsetReal(void* buffers, int offset)
    {
        for (int chan = 0; chan < fChannels; chan++) {
            static_cast<REAL**>(buffers)[chan] = &(static_cast<REAL**>(fBuffers))[chan][offset];
        }
    }
    
    void emptyFile(int part, int& offset)
    {
        fLength[part] = BUFFER_SIZE;
        fSR[part] = SAMPLE_RATE;
        fOffset[part] = offset;
        // Update offset
        offset += fLength[part];
    }
 
    ~Soundfile()
    {
        // Free the real channels only
        if (fIsDouble) {
            for (int chan = 0; chan < fChannels; chan++) {
                delete[] static_cast<double**>(fBuffers)[chan];
            }
            delete[] static_cast<double**>(fBuffers);
        } else {
            for (int chan = 0; chan < fChannels; chan++) {
                delete[] static_cast<float**>(fBuffers)[chan];
            }
            delete[] static_cast<float**>(fBuffers);
        }
        delete[] fLength;
        delete[] fSR;
        delete[] fOffset;
    }

} POST_PACKED_STRUCTURE;

/*
 The generic soundfile reader.
 */

class SoundfileReader {
    
   protected:
    
    int fDriverSR;
   
    // Check if a soundfile exists and return its real path_name
    std::string checkFile(const std::vector<std::string>& sound_directories, const std::string& file_name)
    {
        if (checkFile(file_name)) {
            return file_name;
        } else {
            for (size_t i = 0; i < sound_directories.size(); i++) {
                std::string path_name = sound_directories[i] + "/" + file_name;
                if (checkFile(path_name)) { return path_name; }
            }
            return "";
        }
    }
    
    bool isResampling(int sample_rate) { return (fDriverSR > 0 && fDriverSR != sample_rate); }
 
    // To be implemented by subclasses

    /**
     * Check the availability of a sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     *
     * @return true if the sound resource is available, false otherwise.
     */
    virtual bool checkFile(const std::string& path_name) = 0;
    
    /**
     * Check the availability of a sound resource.
     *
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     *
     * @return true if the sound resource is available, false otherwise.
     */

    virtual bool checkFile(unsigned char* buffer, size_t size) { return true; }

    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    virtual void getParamsFile(const std::string& path_name, int& channels, int& length) = 0;
    
    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    virtual void getParamsFile(unsigned char* buffer, size_t size, int& channels, int& length) {}

    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param soundfile - the soundfile to be filled
     * @param path_name - the name of the file, or sound resource identified this way
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    virtual void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan) = 0;
    
    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param soundfile - the soundfile to be filled
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    virtual void readFile(Soundfile* soundfile, unsigned char* buffer, size_t size, int part, int& offset, int max_chan) {}

  public:
    
    virtual ~SoundfileReader() {}
    
    void setSampleRate(int sample_rate) { fDriverSR = sample_rate; }
   
    Soundfile* createSoundfile(const std::vector<std::string>& path_name_list, int max_chan, bool is_double)
    {
        try {
            int cur_chan = 1; // At least one channel
            int total_length = 0;
            
            // Compute total length and channels max of all files
            for (int i = 0; i < int(path_name_list.size()); i++) {
                int chan, length;
                if (path_name_list[i] == "__empty_sound__") {
                    length = BUFFER_SIZE;
                    chan = 1;
                } else {
                    getParamsFile(path_name_list[i], chan, length);
                }
                cur_chan = std::max<int>(cur_chan, chan);
                total_length += length;
            }
           
            // Complete with empty parts
            total_length += (MAX_SOUNDFILE_PARTS - path_name_list.size()) * BUFFER_SIZE;
            
            // Create the soundfile
            Soundfile* soundfile = new Soundfile(cur_chan, total_length, max_chan, is_double);
            
            // Init offset
            int offset = 0;
            
            // Read all files
            for (int i = 0; i < int(path_name_list.size()); i++) {
                if (path_name_list[i] == "__empty_sound__") {
                    soundfile->emptyFile(i, offset);
                } else {
                    readFile(soundfile, path_name_list[i], i, offset, max_chan);
                }
            }
            
            // Complete with empty parts
            for (int i = int(path_name_list.size()); i < MAX_SOUNDFILE_PARTS; i++) {
                soundfile->emptyFile(i, offset);
            }
            
            // Share the same buffers for all other channels so that we have max_chan channels available
            soundfile->shareBuffers(cur_chan, max_chan);
            return soundfile;
            
        } catch (...) {
            return nullptr;
        }
    }

    // Check if all soundfiles exist and return their real path_name
    std::vector<std::string> checkFiles(const std::vector<std::string>& sound_directories,
                                        const std::vector<std::string>& file_name_list)
    {
        std::vector<std::string> path_name_list;
        for (size_t i = 0; i < file_name_list.size(); i++) {
            std::string path_name = checkFile(sound_directories, file_name_list[i]);
            // If 'path_name' is not found, it is replaced by an empty sound (= silence)
            path_name_list.push_back((path_name == "") ? "__empty_sound__" : path_name);
        }
        return path_name_list;
    }

};

#endif
/**************************  END  Soundfile.h **************************/

#if defined(JUCE_32BIT) || defined(JUCE_64BIT)
/************************** BEGIN JuceReader.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __JuceReader__
#define __JuceReader__

#include <assert.h>

#include "../JuceLibraryCode/JuceHeader.h"


struct JuceReader : public SoundfileReader {
    
    juce::AudioFormatManager fFormatManager;
    
    JuceReader() { fFormatManager.registerBasicFormats(); }
    virtual ~JuceReader()
    {}
    
    bool checkFile(const std::string& path_name)
    {
        juce::File file(path_name);
        if (file.existsAsFile()) {
            return true;
        } else {
            std::cerr << "ERROR : cannot open '" << path_name << "'" << std::endl;
            return false;
        }
    }
    
    void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        std::unique_ptr<juce::AudioFormatReader> formatReader (fFormatManager.createReaderFor (juce::File (path_name)));
        channels = int(formatReader->numChannels);
        length = int(formatReader->lengthInSamples);
    }
    
    void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        std::unique_ptr<juce::AudioFormatReader> formatReader (fFormatManager.createReaderFor (juce::File (path_name)));
        
        soundfile->fLength[part] = int(formatReader->lengthInSamples);
        soundfile->fSR[part] = int(formatReader->sampleRate);
        soundfile->fOffset[part] = offset;
        
        void* buffers;
        if (soundfile->fIsDouble) {
            buffers = alloca(soundfile->fChannels * sizeof(double*));
            soundfile->getBuffersOffsetReal<double>(buffers, offset);
        } else {
            buffers = alloca(soundfile->fChannels * sizeof(float*));
            soundfile->getBuffersOffsetReal<float>(buffers, offset);
        }
        
        if (formatReader->read(reinterpret_cast<int *const *>(buffers), int(formatReader->numChannels), 0, int(formatReader->lengthInSamples), false)) {
            
            // Possibly convert samples
            if (!formatReader->usesFloatingPointData) {
                for (int chan = 0; chan < int(formatReader->numChannels); ++chan) {
                    if (soundfile->fIsDouble) {
                        // TODO
                    } else {
                        float* buffer = &(static_cast<float**>(soundfile->fBuffers))[chan][soundfile->fOffset[part]];
                        juce::FloatVectorOperations::convertFixedToFloat(buffer, reinterpret_cast<const int*>(buffer),
                                                                         1.0f/0x7fffffff, int(formatReader->lengthInSamples));
                    }
                }
            }
            
        } else {
            std::cerr << "Error reading the file : " << path_name << std::endl;
        }
            
        // Update offset
        offset += soundfile->fLength[part];
    }
    
};

#endif
/**************************  END  JuceReader.h **************************/
static JuceReader gReader;
#elif defined(ESP32)
/************************** BEGIN Esp32Reader.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_ESP32READER_H
#define FAUST_ESP32READER_H

#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"

/************************** BEGIN WaveReader.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __WaveReader__
#define __WaveReader__

#include <string.h>
#include <assert.h>
#include <stdio.h>


// WAVE file description
typedef struct {
    
    // The canonical WAVE format starts with the RIFF header
    
    /**
     Variable: chunk_id
     Contains the letters "RIFF" in ASCII form (0x52494646 big-endian form).
     **/
    int chunk_id;
    
    /**
     Variable: chunk_size
     36 + SubChunk2Size, or more precisely: 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
     This is the size of the rest of the chunk following this number.
     This is the size of the entire file in bytes minus 8 bytes for the
     two fields not included in this count: ChunkID and ChunkSize.
     **/
    int chunk_size;
    
    /**
     Variable: format
     Contains the letters "WAVE" (0x57415645 big-endian form).
     **/
    int format;
    
    // The "WAVE" format consists of two subchunks: "fmt " and "data":
    // The "fmt " subchunk describes the sound data's format:
    
    /**
     Variable: subchunk_1_id
     Contains the letters "fmt " (0x666d7420 big-endian form).
     **/
    int subchunk_1_id;
    
    /**
     Variable: subchunk_1_size
     16 for PCM. This is the size of the rest of the Subchunk which follows this number.
     **/
    int subchunk_1_size;
    
    /**
     Variable: audio_format
     PCM = 1 (i.e. Linear quantization) Values other than 1 indicate some form of compression.
     **/
    short audio_format;
    
    /**
     Variable: num_channels
     Mono = 1, Stereo = 2, etc.
     **/
    short num_channels;
    
    /**
     Variable: sample_rate
     8000, 44100, etc.
     **/
    int sample_rate;
    
    /**
     Variable: byte_rate
     == SampleRate * NumChannels * BitsPerSample/8
     **/
    int byte_rate;
    
    /**
     Variable: block_align
     == NumChannels * BitsPerSample/8
     The number of bytes for one sample including all channels. I wonder what happens
     when this number isn't an integer?
     **/
    short block_align;
    
    /**
     Variable: bits_per_sample
     8 bits = 8, 16 bits = 16, etc.
     **/
    short bits_per_sample;
    
    /**
     Here should come some extra parameters which i will avoid.
     **/
    
    // The "data" subchunk contains the size of the data and the actual sound:
    
    /**
     Variable: subchunk_2_id
     Contains the letters "data" (0x64617461 big-endian form).
     **/
    int subchunk_2_id;
    
    /**
     Variable: subchunk_2_size
     == NumSamples * NumChannels * BitsPerSample/8
     This is the number of bytes in the data. You can also think of this as the size
     of the read of the subchunk following this number.
     **/
    int subchunk_2_size;
    
    /**
     Variable: data
     The actual sound data.
     **/
    char* data;
    
} wave_t;

// Base reader
struct Reader {
    
    wave_t* fWave;

    inline int is_big_endian()
    {
        int a = 1;
        return !((char*)&a)[0];
    }
    
    inline int convert_to_int(char* buffer, int len)
    {
        int a = 0;
        if (!is_big_endian()) {
            for(int i = 0; i < len; i++) {
                ((char*)&a)[i] = buffer[i];
            }
        } else {
            for(int i = 0; i < len; i++) {
                ((char*)&a)[3-i] = buffer[i];
            }
        }
        return a;
    }
    
    Reader()
    {
        fWave = (wave_t*)calloc(1, sizeof(wave_t));
    }

    virtual ~Reader()
    {
        free(fWave->data);
        free(fWave);
    }

    bool load_wave_header()
    {
        char buffer[4];
        
        read(buffer, 4);
        if (strncmp(buffer, "RIFF", 4) != 0) {
            fprintf(stderr, "This is not valid WAV file!\n");
            return false;
        }
        fWave->chunk_id = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->chunk_size = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->format = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->subchunk_1_id = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->subchunk_1_size = convert_to_int(buffer, 4);
        
        read(buffer, 2);
        fWave->audio_format = convert_to_int(buffer, 2);
        
        read(buffer, 2);
        fWave->num_channels = convert_to_int(buffer, 2);
        
        read(buffer, 4);
        fWave->sample_rate = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->byte_rate = convert_to_int(buffer, 4);
        
        read(buffer, 2);
        fWave->block_align = convert_to_int(buffer, 2);
        
        read(buffer, 2);
        fWave->bits_per_sample = convert_to_int(buffer, 2);
        
        read(buffer, 4);
        if (strncmp(buffer, "data", 4) != 0) {
            read(buffer, 4);
            int _extra_size = convert_to_int(buffer, 4);
            char _extra_data[_extra_size];
            read(_extra_data, _extra_size);
            read(buffer, 4);
            fWave->subchunk_2_id = convert_to_int(buffer, 4);
        } else {
            fWave->subchunk_2_id = convert_to_int(buffer, 4);
        }
        
        read(buffer, 4);
        fWave->subchunk_2_size = convert_to_int(buffer, 4);
        return true;
    }
    
    void load_wave()
    {
        // Read sound data
        fWave->data = (char*)malloc(fWave->subchunk_2_size);
        read(fWave->data, fWave->subchunk_2_size);
    }

    virtual void read(char* buffer, unsigned int size) = 0;
   
};

struct FileReader : public Reader {
    
    FILE* fFile;
    
    FileReader(const std::string& file_path)
    {
        fFile = fopen(file_path.c_str(), "rb");
        if (!fFile) {
            fprintf(stderr, "FileReader : cannot open file!\n");
            throw -1;
        }
        if (!load_wave_header()) {
            fprintf(stderr, "FileReader : not a WAV file!\n");
            throw -1;
        }
    }
    
    virtual ~FileReader()
    {
        fclose(fFile);
    }
    
    void read(char* buffer, unsigned int size)
    {
        fread(buffer, 1, size, fFile);
    }
    
};

extern const uint8_t file_start[] asm("_binary_FILE_start");
extern const uint8_t file_end[]   asm("_binary_FILE_end");

struct MemoryReader : public Reader {
    
    int fPos;
    const uint8_t* fStart;
    const uint8_t* fEnd;
    
    MemoryReader(const uint8_t* start, const uint8_t* end):fPos(0)
    {
        fStart = start;
        fEnd = end;
        if (!load_wave_header()) {
            fprintf(stderr, "MemoryReader : not a WAV file!\n");
            throw -1;
        }
    }
    
    virtual ~MemoryReader()
    {}
    
    void read(char* buffer, unsigned int size)
    {
        memcpy(buffer, fStart + fPos, size);
        fPos += size;
    }
    
};

// Using a FileReader to implement SoundfileReader

struct WaveReader : public SoundfileReader {
    
    WaveReader() {}
    virtual ~WaveReader() {}
    
    virtual bool checkFile(const std::string& path_name)
    {
        try {
            FileReader reader(path_name);
            return true;
        } catch (...)  {
            return false;
        }
    }
    
    virtual void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        FileReader reader(path_name);
        channels = reader.fWave->num_channels;
        length = (reader.fWave->subchunk_2_size * 8) / (reader.fWave->num_channels * reader.fWave->bits_per_sample);
    }
    
    virtual void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        FileReader reader(path_name);
        reader.load_wave();
        
        soundfile->fLength[part] = (reader.fWave->subchunk_2_size * 8) / (reader.fWave->num_channels * reader.fWave->bits_per_sample);
        soundfile->fSR[part] = reader.fWave->sample_rate;
        soundfile->fOffset[part] = offset;
        
        // Audio frames have to be written for each chan
        if (reader.fWave->bits_per_sample == 16) {
            float factor = 1.f/32767.f;
            for (int sample = 0; sample < soundfile->fLength[part]; sample++) {
                short* frame = (short*)&reader.fWave->data[reader.fWave->block_align * sample];
                for (int chan = 0; chan < reader.fWave->num_channels; chan++) {
                    soundfile->fBuffers[chan][offset + sample] = frame[chan] * factor;
                }
            }
        } else if (reader.fWave->bits_per_sample == 32) {
            fprintf(stderr, "readFile : not implemented\n");
        }
        
        // Update offset
        offset += soundfile->fLength[part];
    }
};

#endif
/**************************  END  WaveReader.h **************************/

#define TAG "Esp32Reader"

#define SD_PIN_NUM_MISO GPIO_NUM_2
#define SD_PIN_NUM_MOSI GPIO_NUM_15
#define SD_PIN_NUM_CLK  GPIO_NUM_14
#define SD_PIN_NUM_CS   GPIO_NUM_13

struct Esp32Reader : public WaveReader {
    
    void sdcard_init()
    {
        ESP_LOGI(TAG, "Initializing SD card");
        ESP_LOGI(TAG, "Using SPI peripheral");
        
        sdmmc_host_t host = SDSPI_HOST_DEFAULT();
        sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
        slot_config.gpio_miso = SD_PIN_NUM_MISO;
        slot_config.gpio_mosi = SD_PIN_NUM_MOSI;
        slot_config.gpio_sck  = SD_PIN_NUM_CLK;
        slot_config.gpio_cs   = SD_PIN_NUM_CS;
        // This initializes the slot without card detect (CD) and write protect (WP) signals.
        // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
        
        // Options for mounting the filesystem.
        // If format_if_mount_failed is set to true, SD card will be partitioned and
        // formatted in case when mounting fails.
        esp_vfs_fat_sdmmc_mount_config_t mount_config = {
            .format_if_mount_failed = false,
            .max_files = 5,
            .allocation_unit_size = 16 * 1024
        };
        
        // Use settings defined above to initialize SD card and mount FAT filesystem.
        // Note: esp_vfs_fat_sdmmc_mount is an all-in-one convenience function.
        // Please check its source code and implement error recovery when developing
        // production applications.
        sdmmc_card_t* card;
        esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);
        
        if (ret != ESP_OK) {
            if (ret == ESP_FAIL) {
                ESP_LOGE(TAG, "Failed to mount filesystem. "
                         "If you want the card to be formatted, set format_if_mount_failed = true.");
            } else {
                ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                         "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
            }
            return;
        }
        
        // Card has been initialized, print its properties
        sdmmc_card_print_info(stdout, card);
        ESP_LOGI(TAG, "SD card initialized");
    }
    
    Esp32Reader()
    {
        sdcard_init();
    }
   
    // Access methods inherited from WaveReader
};

#endif // FAUST_ESP32READER_H
/**************************  END  Esp32Reader.h **************************/
static Esp32Reader gReader;
#elif defined(DAISY)
static WaveReader gReader;
#elif defined(MEMORY_READER)
/************************** BEGIN MemoryReader.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __MemoryReader__
#define __MemoryReader__


/*
 A 'MemoryReader' object can be used to prepare a set of sound resources in memory, to be used by SoundUI::addSoundfile.
 
 A Soundfile* object will have to be filled with a list of sound resources: the fLength, fOffset, fSampleRate and fBuffers fields 
 have to be completed with the appropriate values, and will be accessed in the DSP object while running.
 *
 */

// To adapt for a real case use

#define SOUND_CHAN      2
#define SOUND_LENGTH    4096
#define SOUND_SR        44100

struct MemoryReader : public SoundfileReader {
    
    MemoryReader()
    {}
    
    /**
     * Check the availability of a sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     *
     * @return true if the sound resource is available, false otherwise.
     */
    virtual bool checkFile(const std::string& path_name) { return true; }
    
    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    virtual void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        channels = SOUND_CHAN;
        length = SOUND_LENGTH;
    }
    
    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    virtual void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        soundfile->fLength[part] = SOUND_LENGTH;
        soundfile->fSR[part] = SOUND_SR;
        soundfile->fOffset[part] = offset;
        
        // Audio frames have to be written for each chan
        if (soundfile->fIsDouble) {
            for (int sample = 0; sample < SOUND_LENGTH; sample++) {
                for (int chan = 0; chan < SOUND_CHAN; chan++) {
                    static_cast<double**>(soundfile->fBuffers)[chan][offset + sample] = 0.f;
                }
            }
        } else {
            for (int sample = 0; sample < SOUND_LENGTH; sample++) {
                for (int chan = 0; chan < SOUND_CHAN; chan++) {
                    static_cast<float**>(soundfile->fBuffers)[chan][offset + sample] = 0.f;
                }
            }
        }
        
        // Update offset
        offset += SOUND_LENGTH;
    }
    
};

#endif
/**************************  END  MemoryReader.h **************************/
static MemoryReader gReader;
#else
/************************** BEGIN LibsndfileReader.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __LibsndfileReader__
#define __LibsndfileReader__

#ifdef SAMPLERATE
#include <samplerate.h>
#endif
#include <sndfile.h>
#include <string.h>
#include <assert.h>
#include <iostream>


struct VFLibsndfile {
    
    #define SIGNED_SIZEOF(x) ((int)sizeof(x))
    
    unsigned char* fBuffer;
    size_t fLength;
    size_t fOffset;
    SF_VIRTUAL_IO fVIO;
    
    VFLibsndfile(unsigned char* buffer, size_t length):fBuffer(buffer), fLength(length), fOffset(0)
    {
        fVIO.get_filelen = vfget_filelen;
        fVIO.seek = vfseek;
        fVIO.read = vfread;
        fVIO.write = vfwrite;
        fVIO.tell = vftell;
    }
    
    static sf_count_t vfget_filelen(void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        return vf->fLength;
    }
  
    static sf_count_t vfseek(sf_count_t offset, int whence, void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        switch (whence) {
            case SEEK_SET:
                vf->fOffset = offset;
                break;
                
            case SEEK_CUR:
                vf->fOffset = vf->fOffset + offset;
                break;
                
            case SEEK_END:
                vf->fOffset = vf->fLength + offset;
                break;
                
            default:
                break;
        };
        
        return vf->fOffset;
    }
    
    static sf_count_t vfread(void* ptr, sf_count_t count, void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        
        /*
         **	This will break badly for files over 2Gig in length, but
         **	is sufficient for testing.
         */
        if (vf->fOffset + count > vf->fLength) {
            count = vf->fLength - vf->fOffset;
        }
        
        memcpy(ptr, vf->fBuffer + vf->fOffset, count);
        vf->fOffset += count;
        
        return count;
    }
    
    static sf_count_t vfwrite(const void* ptr, sf_count_t count, void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        
        /*
         **	This will break badly for files over 2Gig in length, but
         **	is sufficient for testing.
         */
        if (vf->fOffset >= SIGNED_SIZEOF(vf->fBuffer)) {
            return 0;
        }
        
        if (vf->fOffset + count > SIGNED_SIZEOF(vf->fBuffer)) {
            count = sizeof (vf->fBuffer) - vf->fOffset;
        }
        
        memcpy(vf->fBuffer + vf->fOffset, ptr, (size_t)count);
        vf->fOffset += count;
        
        if (vf->fOffset > vf->fLength) {
            vf->fLength = vf->fOffset;
        }
        
        return count;
    }
    
    static sf_count_t vftell(void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        return vf->fOffset;
    }
 
};

struct LibsndfileReader : public SoundfileReader {
	
    LibsndfileReader() {}
	
    typedef sf_count_t (* sample_read)(SNDFILE* sndfile, void* buffer, sf_count_t frames);
	
    // Check file
    bool checkFile(const std::string& path_name)
    {
        SF_INFO snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        return checkFileAux(snd_file, path_name);
    }
    
    bool checkFile(unsigned char* buffer, size_t length)
    {
        SF_INFO snd_info;
        snd_info.format = 0;
        VFLibsndfile vio(buffer, length);
        SNDFILE* snd_file = sf_open_virtual(&vio.fVIO, SFM_READ, &snd_info, &vio);
        return checkFileAux(snd_file, "virtual file");
    }
    
    bool checkFileAux(SNDFILE* snd_file, const std::string& path_name)
    {
        if (snd_file) {
            sf_close(snd_file);
            return true;
        } else {
            std::cerr << "ERROR : cannot open '" << path_name << "' (" << sf_strerror(NULL) << ")" << std::endl;
            return false;
        }
    }

    // Open the file and returns its length and channels
    void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        getParamsFileAux(snd_file, snd_info, channels, length);
    }
    
    void getParamsFile(unsigned char* buffer, size_t size, int& channels, int& length)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        VFLibsndfile vio(buffer, size);
        SNDFILE* snd_file = sf_open_virtual(&vio.fVIO, SFM_READ, &snd_info, &vio);
        getParamsFileAux(snd_file, snd_info, channels, length);
    }
    
    void getParamsFileAux(SNDFILE* snd_file, const SF_INFO& snd_info, int& channels, int& length)
    {
        assert(snd_file);
        channels = int(snd_info.channels);
    #ifdef SAMPLERATE
        length = (isResampling(snd_info.samplerate)) ? ((double(snd_info.frames) * double(fDriverSR) / double(snd_info.samplerate)) + BUFFER_SIZE) : int(snd_info.frames);
    #else
        length = int(snd_info.frames);
    #endif
        sf_close(snd_file);
    }
    
    // Read the file
    void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        readFileAux(soundfile, snd_file, snd_info, part, offset, max_chan);
    }
    
    void readFile(Soundfile* soundfile, unsigned char* buffer, size_t length, int part, int& offset, int max_chan)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        VFLibsndfile vio(buffer, length);
        SNDFILE* snd_file = sf_open_virtual(&vio.fVIO, SFM_READ, &snd_info, &vio);
        readFileAux(soundfile, snd_file, snd_info, part, offset, max_chan);
    }
	
    // Will be called to fill all parts from 0 to MAX_SOUNDFILE_PARTS-1
    void readFileAux(Soundfile* soundfile, SNDFILE* snd_file, const SF_INFO& snd_info, int part, int& offset, int max_chan)
    {
        assert(snd_file);
        int channels = std::min<int>(max_chan, snd_info.channels);
    #ifdef SAMPLERATE
        if (isResampling(snd_info.samplerate)) {
            soundfile->fLength[part] = int(double(snd_info.frames) * double(fDriverSR) / double(snd_info.samplerate));
            soundfile->fSR[part] = fDriverSR;
        } else {
            soundfile->fLength[part] = int(snd_info.frames);
            soundfile->fSR[part] = snd_info.samplerate;
        }
    #else
        soundfile->fLength[part] = int(snd_info.frames);
        soundfile->fSR[part] = snd_info.samplerate;
    #endif
        soundfile->fOffset[part] = offset;
		
        // Read and fill snd_info.channels number of channels
        sf_count_t nbf;
        
        sample_read reader;
        void* buffer_in = nullptr;
        if (soundfile->fIsDouble) {
            buffer_in = static_cast<double*>(alloca(BUFFER_SIZE * sizeof(double) * snd_info.channels));
            reader = reinterpret_cast<sample_read>(sf_readf_double);
        } else {
            buffer_in = static_cast<float*>(alloca(BUFFER_SIZE * sizeof(float) * snd_info.channels));
            reader = reinterpret_cast<sample_read>(sf_readf_float);
        }
        
    #ifdef SAMPLERATE
        // Resampling
        SRC_STATE* resampler = nullptr;
        float* src_buffer_out = nullptr;
        float* src_buffer_in = nullptr;
        void* buffer_out = nullptr;
        if  (isResampling(snd_info.samplerate)) {
            int error;
            resampler = src_new(SRC_SINC_FASTEST, channels, &error);
            if (error != 0) {
                std::cerr << "ERROR : src_new " << src_strerror(error) << std::endl;
                throw -1;
            }
            if (soundfile->fIsDouble) {
                // Additional buffers for SRC resampling
                src_buffer_in = static_cast<float*>(alloca(BUFFER_SIZE * sizeof(float) * snd_info.channels));
                src_buffer_out = static_cast<float*>(alloca(BUFFER_SIZE * sizeof(float) * snd_info.channels));
                buffer_out = static_cast<double*>(alloca(BUFFER_SIZE * sizeof(double) * snd_info.channels));
            } else {
                buffer_out = static_cast<float*>(alloca(BUFFER_SIZE * sizeof(float) * snd_info.channels));
            }
        }
    #endif
        
        do {
            nbf = reader(snd_file, buffer_in, BUFFER_SIZE);
        #ifdef SAMPLERATE
            // Resampling
            if  (isResampling(snd_info.samplerate)) {
                int in_offset = 0;
                SRC_DATA src_data;
                src_data.src_ratio = double(fDriverSR)/double(snd_info.samplerate);
                if (soundfile->fIsDouble) {
                    for (int frame = 0; frame < (BUFFER_SIZE * snd_info.channels); frame++) {
                        src_buffer_in[frame] = float(static_cast<float*>(buffer_in)[frame]);
                    }
                }
                do {
                    if (soundfile->fIsDouble) {
                        src_data.data_in = src_buffer_in;
                        src_data.data_out = src_buffer_out;
                    } else {
                        src_data.data_in = static_cast<const float*>(buffer_in);
                        src_data.data_out = static_cast<float*>(buffer_out);
                    }
                    src_data.input_frames = nbf - in_offset;
                    src_data.output_frames = BUFFER_SIZE;
                    src_data.end_of_input = (nbf < BUFFER_SIZE);
                    int res = src_process(resampler, &src_data);
                    if (res != 0) {
                        std::cerr << "ERROR : src_process " << src_strerror(res) << std::endl;
                        throw -1;
                    }
                    if (soundfile->fIsDouble) {
                        for (int frame = 0; frame < (BUFFER_SIZE * snd_info.channels); frame++) {
                            static_cast<double*>(buffer_out)[frame] = double(src_buffer_out[frame]);
                        }
                    }
                    soundfile->copyToOut(src_data.output_frames_gen, channels, snd_info.channels, offset, buffer_out);
                    in_offset += src_data.input_frames_used;
                    // Update offset
                    offset += src_data.output_frames_gen;
                } while (in_offset < nbf);
            } else {
                soundfile->copyToOut(nbf, channels, snd_info.channels, offset, buffer_in);
                // Update offset
                offset += nbf;
            }
        #else
            soundfile->copyToOut(nbf, channels, snd_info.channels, offset, buffer_in);
            // Update offset
            offset += nbf;
        #endif
        } while (nbf == BUFFER_SIZE);
		
        sf_close(snd_file);
    #ifdef SAMPLERATE
        if (resampler) src_delete(resampler);
    #endif
    }

};

#endif
/**************************  END  LibsndfileReader.h **************************/
static LibsndfileReader gReader;
#endif

// To be used by DSP code if no SoundUI is used
static std::vector<std::string> path_name_list;
static Soundfile* defaultsound = nullptr;

class SoundUI : public SoundUIInterface
{
		
    protected:
    
        std::vector<std::string> fSoundfileDir;             // The soundfile directories
        std::map<std::string, Soundfile*> fSoundfileMap;    // Map to share loaded soundfiles
        SoundfileReader* fSoundReader;
        bool fIsDouble;

     public:
    
        /**
         * Create a soundfile loader which will typically use a concrete SoundfileReader like LibsndfileReader or JuceReader to load soundfiles.
         *
         * @param sound_directory - the base directory to look for files, which paths will be relative to this one
         * @param sample_rate - the audio driver SR which may be different from the file SR, to possibly resample files
         * @param reader - an alternative soundfile reader
         *
         * @return the soundfile loader.
         */
        SoundUI(const std::string& sound_directory = "", int sample_rate = -1, SoundfileReader* reader = nullptr, bool is_double = false)
        {
            fSoundfileDir.push_back(sound_directory);
            fSoundReader = (reader) ? reader : &gReader;
            fSoundReader->setSampleRate(sample_rate);
            fIsDouble = is_double;
            if (!defaultsound) defaultsound = gReader.createSoundfile(path_name_list, MAX_CHAN, is_double);
        }
    
        /**
         * Create a soundfile loader which will typically use a concrete SoundfileReader like LibsndfileReader or JuceReader to load soundfiles.
         *
         * @param sound_directories - a vector of base directories to look for files, which paths will be relative to these ones
         * @param sample_rate - the audio driver SR which may be different from the file SR, to possibly resample files
         * @param reader - an alternative soundfile reader
         *
         * @return the soundfile loader.
         */
        SoundUI(const std::vector<std::string>& sound_directories, int sample_rate = -1, SoundfileReader* reader = nullptr, bool is_double = false)
        :fSoundfileDir(sound_directories)
        {
            fSoundReader = (reader) ? reader : &gReader;
            fSoundReader->setSampleRate(sample_rate);
            fIsDouble = is_double;
            if (!defaultsound) defaultsound = gReader.createSoundfile(path_name_list, MAX_CHAN, is_double);
        }
    
        virtual ~SoundUI()
        {   
            // Delete all soundfiles
            for (const auto& it : fSoundfileMap) {
                delete it.second;
            }
        }

        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* url, Soundfile** sf_zone)
        {
            const char* saved_url = url; // 'url' is consumed by parseMenuList2
            std::vector<std::string> file_name_list;
            
            bool menu = parseMenuList2(url, file_name_list, true);
            // If not a list, we have as single file
            if (!menu) { file_name_list.push_back(saved_url); }
            
            // Parse the possible list
            std::string saved_url_real = std::string(saved_url) + "_" + std::to_string(fIsDouble); // fIsDouble is used in the key
            if (fSoundfileMap.find(saved_url_real) == fSoundfileMap.end()) {
                // Check all files and get their complete path
                std::vector<std::string> path_name_list = fSoundReader->checkFiles(fSoundfileDir, file_name_list);
                // Read them and create the Soundfile
                Soundfile* sound_file = fSoundReader->createSoundfile(path_name_list, MAX_CHAN, fIsDouble);
                if (sound_file) {
                    fSoundfileMap[saved_url_real] = sound_file;
                } else {
                    // If failure, use 'defaultsound'
                    std::cerr << "addSoundfile : soundfile for " << saved_url << " cannot be created !" << std::endl;
                    *sf_zone = defaultsound;
                    return;
                }
            }
            
            // Get the soundfile
            *sf_zone = fSoundfileMap[saved_url_real];
        }
    
        /**
         * An OS dependant function to get the path of the running executable or plugin.
         * This will typically be used when creating a SoundUI soundfile loader, like new SoundUI(SoundUI::getBinaryPath());
         *
         * @return the running executable or plugin path.
         */
        static std::string getBinaryPath()
        {
            std::string bundle_path_str;
        #if defined(__APPLE__) && !defined(__VCVRACK__) && !defined(JUCE_32BIT) && !defined(JUCE_64BIT)
            CFURLRef bundle_ref = CFBundleCopyBundleURL(CFBundleGetMainBundle());
            if (!bundle_ref) { std::cerr << "getBinaryPath CFBundleCopyBundleURL error\n"; return ""; }
      
            UInt8 bundle_path[1024];
            if (CFURLGetFileSystemRepresentation(bundle_ref, true, bundle_path, 1024)) {
                bundle_path_str = std::string((char*)bundle_path);
            } else {
                std::cerr << "getBinaryPath CFURLGetFileSystemRepresentation error\n";
            }
        #endif
        #ifdef ANDROID_DRIVER
            bundle_path_str = "/data/data/__CURRENT_ANDROID_PACKAGE__/files";
        #endif
            return bundle_path_str;
        }
    
        /**
         * An OS dependant function to get the path of the running executable or plugin.
         * This will typically be used when creating a SoundUI soundfile loader, like new SoundUI(SoundUI::getBinaryPathFrom());
         *
         * @param path - entry point to start getting the path of the running executable or plugin.
         *
         * @return the running executable or plugin path.
         */
        static std::string getBinaryPathFrom(const std::string& path)
        {
            std::string bundle_path_str;
        #if defined(__APPLE__) && !defined(__VCVRACK__) && !defined(JUCE_32BIT) && !defined(JUCE_64BIT)
            CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFStringCreateWithCString(kCFAllocatorDefault, path.c_str(), CFStringGetSystemEncoding()));
            if (!bundle) { std::cerr << "getBinaryPathFrom CFBundleGetBundleWithIdentifier error '" << path << "'" << std::endl; return ""; }
         
            CFURLRef bundle_ref = CFBundleCopyBundleURL(bundle);
            if (!bundle_ref) { std::cerr << "getBinaryPathFrom CFBundleCopyBundleURL error\n"; return ""; }
            
            UInt8 bundle_path[1024];
            if (CFURLGetFileSystemRepresentation(bundle_ref, true, bundle_path, 1024)) {
                bundle_path_str = std::string((char*)bundle_path);
            } else {
                std::cerr << "getBinaryPathFrom CFURLGetFileSystemRepresentation error\n";
            }
        #endif
        #ifdef ANDROID_DRIVER
            bundle_path_str = "/data/data/__CURRENT_ANDROID_PACKAGE__/files";
        #endif
            return bundle_path_str;
        }
};

#endif
/**************************  END  SoundUI.h **************************/
#endif

#if defined(OSCCTRL)
/************************** BEGIN JuceOSCUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef __juce_osc__
#define __juce_osc__
 
#include "../JuceLibraryCode/JuceHeader.h"

/************************** BEGIN APIUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef API_UI_H
#define API_UI_H

#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <map>


class APIUI : public PathBuilder, public Meta, public UI
{
    public:
        
        enum ItemType { kButton = 0, kCheckButton, kVSlider, kHSlider, kNumEntry, kHBargraph, kVBargraph };
        
    protected:
        
        enum { kLin = 0, kLog = 1, kExp = 2 };
        
        int fNumParameters;
        std::vector<std::string> fPaths;
        std::vector<std::string> fLabels;
        std::map<std::string, int> fPathMap;
        std::map<std::string, int> fLabelMap;
        std::vector<ValueConverter*> fConversion;
        std::vector<FAUSTFLOAT*> fZone;
        std::vector<FAUSTFLOAT> fInit;
        std::vector<FAUSTFLOAT> fMin;
        std::vector<FAUSTFLOAT> fMax;
        std::vector<FAUSTFLOAT> fStep;
        std::vector<ItemType> fItemType;
        std::vector<std::map<std::string, std::string> > fMetaData;
        std::vector<ZoneControl*> fAcc[3];
        std::vector<ZoneControl*> fGyr[3];
        
        // Screen color control
        // "...[screencolor:red]..." etc.
        bool fHasScreenControl;      // true if control screen color metadata
        ZoneReader* fRedReader;
        ZoneReader* fGreenReader;
        ZoneReader* fBlueReader;
        
        // Current values controlled by metadata
        std::string fCurrentUnit;
        int fCurrentScale;
        std::string fCurrentAcc;
        std::string fCurrentGyr;
        std::string fCurrentColor;
        std::string fCurrentTooltip;
        std::map<std::string, std::string> fCurrentMetadata;
        
        // Add a generic parameter
        virtual void addParameter(const char* label,
                                  FAUSTFLOAT* zone,
                                  FAUSTFLOAT init,
                                  FAUSTFLOAT min,
                                  FAUSTFLOAT max,
                                  FAUSTFLOAT step,
                                  ItemType type)
        {
            std::string path = buildPath(label);
            fPathMap[path] = fLabelMap[label] = fNumParameters++;
            fPaths.push_back(path);
            fLabels.push_back(label);
            fZone.push_back(zone);
            fInit.push_back(init);
            fMin.push_back(min);
            fMax.push_back(max);
            fStep.push_back(step);
            fItemType.push_back(type);
            
            // handle scale metadata
            switch (fCurrentScale) {
                case kLin:
                    fConversion.push_back(new LinearValueConverter(0, 1, min, max));
                    break;
                case kLog:
                    fConversion.push_back(new LogValueConverter(0, 1, min, max));
                    break;
                case kExp: fConversion.push_back(new ExpValueConverter(0, 1, min, max));
                    break;
            }
            fCurrentScale = kLin;
            
            if (fCurrentAcc.size() > 0 && fCurrentGyr.size() > 0) {
                fprintf(stderr, "warning : 'acc' and 'gyr' metadata used for the same %s parameter !!\n", label);
            }
            
            // handle acc metadata "...[acc : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentAcc.size() > 0) {
                std::istringstream iss(fCurrentAcc);
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;
                
                if ((0 <= axe) && (axe < 3) &&
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax))
                {
                    fAcc[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    fprintf(stderr, "incorrect acc metadata : %s \n", fCurrentAcc.c_str());
                }
                fCurrentAcc = "";
            }
            
            // handle gyr metadata "...[gyr : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentGyr.size() > 0) {
                std::istringstream iss(fCurrentGyr);
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;
                
                if ((0 <= axe) && (axe < 3) &&
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax))
                {
                    fGyr[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    fprintf(stderr, "incorrect gyr metadata : %s \n", fCurrentGyr.c_str());
                }
                fCurrentGyr = "";
            }
            
            // handle screencolor metadata "...[screencolor:red|green|blue|white]..."
            if (fCurrentColor.size() > 0) {
                if ((fCurrentColor == "red") && (fRedReader == 0)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "green") && (fGreenReader == 0)) {
                    fGreenReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "blue") && (fBlueReader == 0)) {
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "white") && (fRedReader == 0) && (fGreenReader == 0) && (fBlueReader == 0)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fGreenReader = new ZoneReader(zone, min, max);
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else {
                    fprintf(stderr, "incorrect screencolor metadata : %s \n", fCurrentColor.c_str());
                }
            }
            fCurrentColor = "";
            
            fMetaData.push_back(fCurrentMetadata);
            fCurrentMetadata.clear();
        }
        
        int getZoneIndex(std::vector<ZoneControl*>* table, int p, int val)
        {
            FAUSTFLOAT* zone = fZone[p];
            for (size_t i = 0; i < table[val].size(); i++) {
                if (zone == table[val][i]->getZone()) return int(i);
            }
            return -1;
        }
        
        void setConverter(std::vector<ZoneControl*>* table, int p, int val, int curve, double amin, double amid, double amax)
        {
            int id1 = getZoneIndex(table, p, 0);
            int id2 = getZoneIndex(table, p, 1);
            int id3 = getZoneIndex(table, p, 2);
            
            // Deactivates everywhere..
            if (id1 != -1) table[0][id1]->setActive(false);
            if (id2 != -1) table[1][id2]->setActive(false);
            if (id3 != -1) table[2][id3]->setActive(false);
            
            if (val == -1) { // Means: no more mapping...
                // So stay all deactivated...
            } else {
                int id4 = getZoneIndex(table, p, val);
                if (id4 != -1) {
                    // Reactivate the one we edit...
                    table[val][id4]->setMappingValues(curve, amin, amid, amax, fMin[p], fInit[p], fMax[p]);
                    table[val][id4]->setActive(true);
                } else {
                    // Allocate a new CurveZoneControl which is 'active' by default
                    FAUSTFLOAT* zone = fZone[p];
                    table[val].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, fMin[p], fInit[p], fMax[p]));
                }
            }
        }
        
        void getConverter(std::vector<ZoneControl*>* table, int p, int& val, int& curve, double& amin, double& amid, double& amax)
        {
            int id1 = getZoneIndex(table, p, 0);
            int id2 = getZoneIndex(table, p, 1);
            int id3 = getZoneIndex(table, p, 2);
            
            if (id1 != -1) {
                val = 0;
                curve = table[val][id1]->getCurve();
                table[val][id1]->getMappingValues(amin, amid, amax);
            } else if (id2 != -1) {
                val = 1;
                curve = table[val][id2]->getCurve();
                table[val][id2]->getMappingValues(amin, amid, amax);
            } else if (id3 != -1) {
                val = 2;
                curve = table[val][id3]->getCurve();
                table[val][id3]->getMappingValues(amin, amid, amax);
            } else {
                val = -1; // No mapping
                curve = 0;
                amin = -100.;
                amid = 0.;
                amax = 100.;
            }
        }
        
    public:
        
        enum Type { kAcc = 0, kGyr = 1, kNoType };
        
        APIUI() : fNumParameters(0), fHasScreenControl(false), fRedReader(0), fGreenReader(0), fBlueReader(0), fCurrentScale(kLin)
        {}
        
        virtual ~APIUI()
        {
            for (const auto& it : fConversion) delete it;
            for (int i = 0; i < 3; i++) {
                for (const auto& it : fAcc[i]) delete it;
                for (const auto& it : fGyr[i]) delete it;
            }
            delete fRedReader;
            delete fGreenReader;
            delete fBlueReader;
        }
        
        // -- widget's layouts
        
        virtual void openTabBox(const char* label) { pushLabel(label); }
        virtual void openHorizontalBox(const char* label) { pushLabel(label); }
        virtual void openVerticalBox(const char* label) { pushLabel(label); }
        virtual void closeBox() { popLabel(); }
        
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1, kButton);
        }
        
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1, kCheckButton);
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kVSlider);
        }
        
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kHSlider);
        }
        
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kNumEntry);
        }
        
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0, kHBargraph);
        }
        
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0, kVBargraph);
        }
        
        // -- soundfiles
        
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            // Keep metadata
            fCurrentMetadata[key] = val;
            
            if (strcmp(key, "scale") == 0) {
                if (strcmp(val, "log") == 0) {
                    fCurrentScale = kLog;
                } else if (strcmp(val, "exp") == 0) {
                    fCurrentScale = kExp;
                } else {
                    fCurrentScale = kLin;
                }
            } else if (strcmp(key, "unit") == 0) {
                fCurrentUnit = val;
            } else if (strcmp(key, "acc") == 0) {
                fCurrentAcc = val;
            } else if (strcmp(key, "gyr") == 0) {
                fCurrentGyr = val;
            } else if (strcmp(key, "screencolor") == 0) {
                fCurrentColor = val; // val = "red", "green", "blue" or "white"
            } else if (strcmp(key, "tooltip") == 0) {
                fCurrentTooltip = val;
            }
        }
        
        virtual void declare(const char* key, const char* val)
        {}
        
        //-------------------------------------------------------------------------------
        // Simple API part
        //-------------------------------------------------------------------------------
        int getParamsCount() { return fNumParameters; }
        
        int getParamIndex(const char* path)
        {
            if (fPathMap.find(path) != fPathMap.end()) {
                return fPathMap[path];
            } else if (fLabelMap.find(path) != fLabelMap.end()) {
                return fLabelMap[path];
            } else {
                return -1;
            }
        }
        const char* getParamAddress(int p) { return fPaths[p].c_str(); }
        const char* getParamLabel(int p) { return fLabels[p].c_str(); }
        std::map<const char*, const char*> getMetadata(int p)
        {
            std::map<const char*, const char*> res;
            std::map<std::string, std::string> metadata = fMetaData[p];
            for (auto it : metadata) {
                res[it.first.c_str()] = it.second.c_str();
            }
            return res;
        }
        
        const char* getMetadata(int p, const char* key)
        {
            return (fMetaData[p].find(key) != fMetaData[p].end()) ? fMetaData[p][key].c_str() : "";
        }
        FAUSTFLOAT getParamMin(int p) { return fMin[p]; }
        FAUSTFLOAT getParamMax(int p) { return fMax[p]; }
        FAUSTFLOAT getParamStep(int p) { return fStep[p]; }
        FAUSTFLOAT getParamInit(int p) { return fInit[p]; }
        
        FAUSTFLOAT* getParamZone(int p) { return fZone[p]; }
        
        FAUSTFLOAT getParamValue(int p) { return *fZone[p]; }
        FAUSTFLOAT getParamValue(const char* path)
        {
            int index = getParamIndex(path);
            return (index >= 0) ? getParamValue(index) : FAUSTFLOAT(0);
        }
        
        void setParamValue(int p, FAUSTFLOAT v) { *fZone[p] = v; }
        void setParamValue(const char* path, FAUSTFLOAT v)
        {
            int index = getParamIndex(path);
            if (index >= 0) setParamValue(index, v);
        }
        
        double getParamRatio(int p) { return fConversion[p]->faust2ui(*fZone[p]); }
        void setParamRatio(int p, double r) { *fZone[p] = fConversion[p]->ui2faust(r); }
        
        double value2ratio(int p, double r)    { return fConversion[p]->faust2ui(r); }
        double ratio2value(int p, double r)    { return fConversion[p]->ui2faust(r); }
        
        /**
         * Return the control type (kAcc, kGyr, or -1) for a given parameter
         *
         * @param p - the UI parameter index
         *
         * @return the type
         */
        Type getParamType(int p)
        {
            if (p >= 0) {
                if (getZoneIndex(fAcc, p, 0) != -1
                    || getZoneIndex(fAcc, p, 1) != -1
                    || getZoneIndex(fAcc, p, 2) != -1) {
                    return kAcc;
                } else if (getZoneIndex(fGyr, p, 0) != -1
                           || getZoneIndex(fGyr, p, 1) != -1
                           || getZoneIndex(fGyr, p, 2) != -1) {
                    return kGyr;
                }
            }
            return kNoType;
        }
        
        /**
         * Return the Item type (kButton = 0, kCheckButton, kVSlider, kHSlider, kNumEntry, kHBargraph, kVBargraph) for a given parameter
         *
         * @param p - the UI parameter index
         *
         * @return the Item type
         */
        ItemType getParamItemType(int p)
        {
            return fItemType[p];
        }
        
        /**
         * Set a new value coming from an accelerometer, propagate it to all relevant FAUSTFLOAT* zones.
         *
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer
         * @param value - the new value
         *
         */
        void propagateAcc(int acc, double value)
        {
            for (size_t i = 0; i < fAcc[acc].size(); i++) {
                fAcc[acc][i]->update(value);
            }
        }
        
        /**
         * Used to edit accelerometer curves and mapping. Set curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer (-1 means "no mapping")
         * @param curve - between 0 and 3
         * @param amin - mapping 'min' point
         * @param amid - mapping 'middle' point
         * @param amax - mapping 'max' point
         *
         */
        void setAccConverter(int p, int acc, int curve, double amin, double amid, double amax)
        {
            setConverter(fAcc, p, acc, curve, amin, amid, amax);
        }
        
        /**
         * Used to edit gyroscope curves and mapping. Set curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope (-1 means "no mapping")
         * @param curve - between 0 and 3
         * @param amin - mapping 'min' point
         * @param amid - mapping 'middle' point
         * @param amax - mapping 'max' point
         *
         */
        void setGyrConverter(int p, int gyr, int curve, double amin, double amid, double amax)
        {
            setConverter(fGyr, p, gyr, curve, amin, amid, amax);
        }
        
        /**
         * Used to edit accelerometer curves and mapping. Get curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - the acc value to be retrieved (-1 means "no mapping")
         * @param curve - the curve value to be retrieved
         * @param amin - the amin value to be retrieved
         * @param amid - the amid value to be retrieved
         * @param amax - the amax value to be retrieved
         *
         */
        void getAccConverter(int p, int& acc, int& curve, double& amin, double& amid, double& amax)
        {
            getConverter(fAcc, p, acc, curve, amin, amid, amax);
        }
        
        /**
         * Used to edit gyroscope curves and mapping. Get curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param gyr - the gyr value to be retrieved (-1 means "no mapping")
         * @param curve - the curve value to be retrieved
         * @param amin - the amin value to be retrieved
         * @param amid - the amid value to be retrieved
         * @param amax - the amax value to be retrieved
         *
         */
        void getGyrConverter(int p, int& gyr, int& curve, double& amin, double& amid, double& amax)
        {
            getConverter(fGyr, p, gyr, curve, amin, amid, amax);
        }
        
        /**
         * Set a new value coming from an gyroscope, propagate it to all relevant FAUSTFLOAT* zones.
         *
         * @param gyr - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope
         * @param value - the new value
         *
         */
        void propagateGyr(int gyr, double value)
        {
            for (size_t i = 0; i < fGyr[gyr].size(); i++) {
                fGyr[gyr][i]->update(value);
            }
        }
        
        /**
         * Get the number of FAUSTFLOAT* zones controlled with the accelerometer
         *
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer
         * @return the number of zones
         *
         */
        int getAccCount(int acc)
        {
            return (acc >= 0 && acc < 3) ? int(fAcc[acc].size()) : 0;
        }
        
        /**
         * Get the number of FAUSTFLOAT* zones controlled with the gyroscope
         *
         * @param gyr - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope
         * @param the number of zones
         *
         */
        int getGyrCount(int gyr)
        {
            return (gyr >= 0 && gyr < 3) ? int(fGyr[gyr].size()) : 0;
        }
        
        // getScreenColor() : -1 means no screen color control (no screencolor metadata found)
        // otherwise return 0x00RRGGBB a ready to use color
        int getScreenColor()
        {
            if (fHasScreenControl) {
                int r = (fRedReader) ? fRedReader->getValue() : 0;
                int g = (fGreenReader) ? fGreenReader->getValue() : 0;
                int b = (fBlueReader) ? fBlueReader->getValue() : 0;
                return (r<<16) | (g<<8) | b;
            } else {
                return -1;
            }
        }
    
};

#endif
/**************************  END  APIUI.h **************************/

class oscItem : public uiItem {
    
    protected:
        
        juce::OSCSender* fSender;
        juce::String fPath;
        
    public:
        
        oscItem(juce::OSCSender* sender, GUI* ui, const juce::String& path, FAUSTFLOAT* zone)
        :uiItem(ui, zone), fSender(sender), fPath(path) {}
        virtual ~oscItem()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fSender->send(fPath, float(v));
        }
    
};

class JuceOSCUI : private juce::OSCReceiver, private juce::OSCReceiver::Listener<juce::OSCReceiver::RealtimeCallback>, public GUI {
    
    private:
        
        juce::OSCSender fSender;
        juce::String fIP;
        int fInputPort, fOutputPort;
        APIUI fAPIUI;
        juce::Array<oscItem*> fOSCItems;  // Pointers are kept and desallocated by the GUI class
        
    public:
        
        JuceOSCUI(const std::string& ip, int in_port, int out_port)
        :fIP(ip), fInputPort(in_port), fOutputPort(out_port)
        {}
        
        virtual ~JuceOSCUI()
        {}
        
        void oscMessageReceived(const juce::OSCMessage& message) override
        {
            juce::String address = message.getAddressPattern().toString();
            
            for (int i = 0; i < message.size(); ++i) {
                if (message[i].isFloat32()) {
                    fAPIUI.setParamValue(fAPIUI.getParamIndex(address.toStdString().c_str()), FAUSTFLOAT(message[i].getFloat32()));
                    // "get" message with correct address
                } else if (message[i].isString()
                           && message[i].getString().equalsIgnoreCase("get")
                           && juce::String(fAPIUI.getParamAddress(0)).startsWith(address)) {
                    for (int p = 0; p < fAPIUI.getParamsCount(); ++p) {
                        fSender.send(fAPIUI.getParamAddress(p), float(fAPIUI.getParamValue(p)), float(fAPIUI.getParamMin(p)), float(fAPIUI.getParamMax(p)));
                    }
                    // "hello" message
                } else if (message[i].isString()
                           && address.equalsIgnoreCase("/*")
                           && message[i].getString().equalsIgnoreCase("hello")) {
                    juce::String path = fAPIUI.getParamAddress(0);
                    int pos1 = path.indexOfChar('/');
                    int pos2 = path.indexOfChar(pos1 + 1, '/');
                    fSender.send(path.substring(pos1, pos2), fIP, fInputPort, fOutputPort);
                }
            }
        }
        
        bool run() override
        {
            // Keep all zones for update when OSC messages are received
            if (fOSCItems.size() == 0) {
                for (int p = 0; p < fAPIUI.getParamsCount(); ++p) {
                    fOSCItems.add(new oscItem(&fSender, this, fAPIUI.getParamAddress(p), fAPIUI.getParamZone(p)));
                }
            }
            
            if (!fSender.connect(fIP, fOutputPort)) {
                std::cerr << "Error: could not connect to UDP port " << fInputPort << std::endl;
                return false;
            }
            
            if (!connect(fInputPort)) {
                std::cerr << "Error: could not connect to UDP port " << fOutputPort << std::endl;
                return false;
            }
            addListener(this);
            return true;
        }
        
        void stop() override
        {
            fSender.disconnect();
            disconnect();
            removeListener(this);
        }
        
        // -- widget's layouts
        
        void openTabBox(const char* label) override { fAPIUI.openTabBox(label); }
        void openHorizontalBox(const char* label) override { fAPIUI.openHorizontalBox(label); }
        void openVerticalBox(const char* label) override { fAPIUI.openVerticalBox(label); }
        void closeBox() override { fAPIUI.closeBox(); }
        
        // -- active widgets
        
        void addButton(const char* label, FAUSTFLOAT* zone) override { fAPIUI.addButton(label, zone); }
        void addCheckButton(const char* label, FAUSTFLOAT* zone) override { fAPIUI.addCheckButton(label, zone); }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        { fAPIUI.addVerticalSlider(label, zone, init, min, max, step); }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        { fAPIUI.addHorizontalSlider(label, zone, init, min, max, step); }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        { fAPIUI.addNumEntry(label, zone, init, min, max, step); }
        
        // -- passive widgets
        
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
        { fAPIUI.addHorizontalBargraph(label, zone, min, max); }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
        { fAPIUI.addVerticalBargraph(label, zone, min, max); }
        
        // -- metadata declarations
        
        void declare(FAUSTFLOAT* zone, const char* key, const char* val) override { fAPIUI.declare(zone, key, val); }
    
};

#endif // __juce_osc__

/**************************  END  JuceOSCUI.h **************************/
#endif

#if defined(MIDICTRL)
/************************** BEGIN juce-midi.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __juce_midi__
#define __juce_midi__
 

class MapUI;

/**
 *  MIDI input/output handling using JUCE framework: https://juce.com
 */
class juce_midi_handler : public midi_handler {
    
    protected:
    
        juce::MidiBuffer fOutputBuffer;
        juce::CriticalSection fMutex;
    
        void decodeMessage(const juce::MidiMessage& message)
        {
            const juce::uint8* data = message.getRawData();
            int channel = message.getChannel() - 1; // which MIDI channel, 0-15
            double time = message.getTimeStamp();
            
            if (message.isNoteOff()) {
                handleKeyOff(time, channel, data[1], data[2]);
            } else if (message.isNoteOn()) {
                handleKeyOn(time, channel, data[1], data[2]);
            } else if (message.isAftertouch()) {
                handlePolyAfterTouch(time, channel, data[1], data[2]);
            } else if (message.isController()) {
                handleCtrlChange(time, channel, data[1], data[2]);
            } else if (message.isProgramChange()) {
                handleProgChange(time, channel, data[1]);
            } else if (message.isChannelPressure()) {
                handleAfterTouch(time, channel, data[1]);
            } else if (message.isPitchWheel()) {
                handlePitchWheel(time, channel, data[1], data[2]);
            } else if (message.isMidiClock()) {
                handleClock(time);
            // We can consider start and continue as identical messages.
            } else if (message.isMidiStart() || message.isMidiContinue()) {
                handleStart(time);
            } else if (message.isMidiStop()) {
                handleStop(time);
            } else if (message.isSysEx()) {
                std::vector<unsigned char> sysex(data, data + message.getRawDataSize());
                handleSysex(time, sysex);
            } else {
                std::cerr << "Unused MIDI message" << std::endl;
            }
        }
    
    public:
    
        juce_midi_handler():midi_handler("JUCE")
        {}
    
        virtual ~juce_midi_handler() {}
    
        // Used with MidiBuffer (containing several messages)
        void encodeBuffer(juce::MidiBuffer& buffer)
        {
            const juce::ScopedTryLock lock(fMutex);
            if (lock.isLocked()) {
                buffer.swapWith(fOutputBuffer);
                fOutputBuffer.clear();
            } else {
                std::cerr << "encodeBuffer fails..." << std::endl;
            }
        }
        
        void decodeBuffer(juce::MidiBuffer& buffer)
        {
            juce::MidiMessage msg;
            int ignore;
            for (juce::MidiBuffer::Iterator it(buffer); it.getNextEvent(msg, ignore);) {
                decodeMessage(msg);
            }
            buffer.clear();
        }
    
        // MIDI output API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::noteOn(channel + 1, pitch, juce::uint8(velocity)), 0);
            return nullptr;
        }
        
        void keyOff(int channel, int pitch, int velocity)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::noteOff(channel + 1, pitch, juce::uint8(velocity)), 0);
        }
        
        void ctrlChange(int channel, int ctrl, int val)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::controllerEvent(channel + 1, ctrl, juce::uint8(val)), 0);
        }
        
        void chanPress(int channel, int press)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::channelPressureChange(channel + 1, press), 0);
        }
        
        void progChange(int channel, int pgm)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::programChange(channel + 1, pgm), 0);
        }
        
        void keyPress(int channel, int pitch, int press)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::aftertouchChange(channel + 1, pitch, press), 0);
        }
        
        void pitchWheel(int channel, int wheel)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::pitchWheel(channel + 1, range(0, 16383, wheel)), 0);
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            // TODO
        }
        
        void startSync(double date)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::midiStart(), 0);
        }
        
        void stopSync(double date)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::midiStop(), 0);
        }
        
        void clock(double date)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::midiClock(), 0);
        }
    
        void sysEx(double date, std::vector<unsigned char>& message)
        {
            fOutputBuffer.addEvent(juce::MidiMessage(message.data(), (int)message.size()), 0);
        }

};

class juce_midi : public juce_midi_handler, public juce::MidiInputCallback {

    private:
    
        std::unique_ptr<juce::MidiInput> fMidiIn;
        std::unique_ptr<juce::MidiOutput> fMidiOut;
    
        void handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage& message)
        {
            decodeMessage(message);
        }
    
    public:
    
        juce_midi():juce_midi_handler()
        {}
    
        virtual ~juce_midi()
        {
            stopMidi();
        }
        
        bool startMidi()
        {
            if ((fMidiIn = juce::MidiInput::openDevice(juce::MidiInput::getDefaultDeviceIndex(), this)) == nullptr) {
                return false;
            }
            if ((fMidiOut = juce::MidiOutput::openDevice(juce::MidiOutput::getDefaultDeviceIndex())) == nullptr) {
                return false;
            }
            fMidiIn->start();
            return true;
        }
        
        void stopMidi()
        { 
            fMidiIn->stop();
        }
    
        // MIDI output API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::noteOn(channel + 1, pitch, juce::uint8(velocity)));
            return nullptr;
        }
        
        void keyOff(int channel, int pitch, int velocity) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::noteOff(channel + 1, pitch, juce::uint8(velocity)));
        }
        
        void ctrlChange(int channel, int ctrl, int val) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::controllerEvent(channel + 1, ctrl, juce::uint8(val)));
        }
        
        void chanPress(int channel, int press) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::channelPressureChange(channel + 1, press));
        }
        
        void progChange(int channel, int pgm) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::programChange(channel + 1, pgm));
        }
          
        void keyPress(int channel, int pitch, int press) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::aftertouchChange(channel + 1, pitch, press));
        }
   
        void pitchWheel(int channel, int wheel) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::pitchWheel(channel + 1, range(0, 16383, wheel)));
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            // TODO
        }
    
        void startSync(double date) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::midiStart());
        }
       
        void stopSync(double date) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::midiStop());
        }
        
        void clock(double date) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::midiClock());
        }
    
        void sysEx(double date, std::vector<unsigned char>& message)
        {
            fMidiOut->sendMessageNow(juce::MidiMessage(message.data(), (int)message.size()));
        }
    
};

#endif // __juce_midi__

/**************************  END  juce-midi.h **************************/
/************************** BEGIN timed-base_dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __timed_dsp__
#define __timed_dsp__

#include <set>
#include <float.h>
#include <assert.h>


namespace {
    
#if __APPLE__
#if TARGET_OS_IPHONE
    //inline double GetCurrentTimeInUsec() { return double(CAHostTimeBase::GetCurrentTimeInNanos()) / 1000.; }
    // TODO
    inline double GetCurrentTimeInUsec() { return 0.0; }
#else
    #include <CoreAudio/HostTime.h>
    inline double GetCurrentTimeInUsec() { return double(AudioConvertHostTimeToNanos(AudioGetCurrentHostTime())) / 1000.; }
#endif
#endif

#if __linux__
#include <sys/time.h>
inline double GetCurrentTimeInUsec() 
{
    struct timeval tv;
    (void)gettimeofday(&tv, (struct timezone *)NULL);
    return double((tv.tv_sec * 1000000) + tv.tv_usec);
}
#endif

#if _WIN32
#include <windows.h>
inline double GetCurrentTimeInUsec(void)
{
    LARGE_INTEGER time;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);
    return double(time.QuadPart) / double(frequency.QuadPart) * 1000000.0;
}
#endif
    
}

/**
 * ZoneUI : this class collect zones in a set.
 */

struct ZoneUI : public GenericUI
{
    
    std::set<FAUSTFLOAT*> fZoneSet;
    
    ZoneUI():GenericUI() {}
    virtual ~ZoneUI() {}
    
    void insertZone(FAUSTFLOAT* zone) 
    { 
        if (GUI::gTimedZoneMap.find(zone) != GUI::gTimedZoneMap.end()) {
            fZoneSet.insert(zone);
        } 
    }
    
    // -- active widgets
    void addButton(const char* label, FAUSTFLOAT* zone)
    {
        insertZone(zone);
    }
    void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        insertZone(zone);
    }
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
    {
        insertZone(zone);
    }
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
    {
        insertZone(zone);
    }
    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
    {
        insertZone(zone);
    }
    
    // -- passive widgets
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
    {
        insertZone(zone);
    }
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
    {
        insertZone(zone);
    }
  
};

/**
 * Timed signal processor that allows to handle the decorated DSP by 'slices'
 * that is, calling the 'compute' method several times and changing control
 * parameters between slices.
 */

class timed_dsp : public decorator_dsp {

    protected:
        
        double fDateUsec;       // Compute call date in usec
        double fOffsetUsec;     // Compute call offset in usec
        bool fFirstCallback;
        ZoneUI fZoneUI;
    
        FAUSTFLOAT** fInputsSlice;
        FAUSTFLOAT** fOutputsSlice;
    
        void computeSlice(int offset, int slice, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
        {
            if (slice > 0) {
                for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                    fInputsSlice[chan] = &(inputs[chan][offset]);
                }
                for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                    fOutputsSlice[chan] = &(outputs[chan][offset]);
                }
                fDSP->compute(slice, fInputsSlice, fOutputsSlice);
            } 
        }
        
        double convertUsecToSample(double usec)
        {
            return std::max<double>(0., (double(getSampleRate()) * (usec - fDateUsec)) / 1000000.);
        }
        
        ztimedmap::iterator getNextControl(DatedControl& res)
        {
            DatedControl date1(DBL_MAX, 0);
            ztimedmap::iterator it1, it2 = GUI::gTimedZoneMap.end();
            std::set<FAUSTFLOAT*>::iterator it3;
              
            // Find date of next audio slice to compute
            for (it3 = fZoneUI.fZoneSet.begin(); it3 != fZoneUI.fZoneSet.end(); it3++) {
                // If value list is not empty, get the date and keep the minimal one
                it1 = GUI::gTimedZoneMap.find(*it3);
                if (it1 != GUI::gTimedZoneMap.end()) { // Check if zone still in global GUI::gTimedZoneMap (since MidiUI may have been desallocated)
                    DatedControl date2;
                    if (ringbuffer_peek((*it1).second, (char*)&date2, sizeof(DatedControl)) == sizeof(DatedControl) 
                        && date2.fDate < date1.fDate) {
                        it2 = it1;
                        date1 = date2;
                    }
                }
            }
            
            res = date1;
            return it2;
        }
        
        virtual void computeAux(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs, bool convert_ts)
        {
            int slice, offset = 0;
            ztimedmap::iterator it;
            DatedControl next_control;
             
            // Do audio computation "slice" by "slice"
            while ((it = getNextControl(next_control)) != GUI::gTimedZoneMap.end()) {
                
                // If needed, convert next_control in samples from begining of the buffer, possible moving to 0 (if negative)
                if (convert_ts) {
                    next_control.fDate = convertUsecToSample(next_control.fDate);
                }
                     
                // Compute audio slice
                slice = int(next_control.fDate) - offset;
                computeSlice(offset, slice, inputs, outputs);
                offset += slice;
               
                // Update control
                ringbuffer_t* control_values = (*it).second;
                *((*it).first) = next_control.fValue;
                
                // Move ringbuffer pointer
                ringbuffer_read_advance(control_values, sizeof(DatedControl));
            } 
            
            // Compute last audio slice
            slice = count - offset;
            computeSlice(offset, slice, inputs, outputs);
        }

    public:

        timed_dsp(base_dsp* base_dsp):decorator_dsp(base_dsp), fDateUsec(0), fOffsetUsec(0), fFirstCallback(true)
        {
            fInputsSlice = new FAUSTFLOAT*[base_dsp->getNumInputs()];
            fOutputsSlice = new FAUSTFLOAT*[base_dsp->getNumOutputs()];
        }
        virtual ~timed_dsp() 
        {
            delete [] fInputsSlice;
            delete [] fOutputsSlice;
        }
        
        virtual void init(int sample_rate)
        {
            fDSP->init(sample_rate);
        }
        
        virtual void buildUserInterface(UI* ui_interface)   
        { 
            fDSP->buildUserInterface(ui_interface); 
            // Only keep zones that are in GUI::gTimedZoneMap
            fDSP->buildUserInterface(&fZoneUI);
        }
    
        virtual timed_dsp* clone()
        {
            return new timed_dsp(fDSP->clone());
        }
    
        // Default method take a timestamp at 'compute' call time
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(::GetCurrentTimeInUsec(), count, inputs, outputs);
        }    
        
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            if (date_usec == -1) {
                // Timestamp is expressed in frames
                computeAux(count, inputs, outputs, false);
            } else {
                // Save the timestamp offset in the first callback
                if (fFirstCallback) {
                    fFirstCallback = false;
                    double current_date_usec = ::GetCurrentTimeInUsec();
                    fDateUsec = current_date_usec;
                    fOffsetUsec = current_date_usec - date_usec;
                }
                
                // RtMidi mode: timestamp must be converted in frames
                computeAux(count, inputs, outputs, true);
                
                // Keep call date 
                fDateUsec = date_usec + fOffsetUsec;
            }
        }
        
};

#endif
/************************** END timed-base_dsp.h **************************/
#endif

#if defined(POLY2)
#include "effect.h"
#endif 

// we require macro declarations
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDSOUNDFILE(l,s)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class mydspSIG0 {
	
  public:
	
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			table[i1] = 0.0f;
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

class mydspSIG1 {
	
  public:
	
	int iVec1[2];
	int iRec11[2];
	
  public:
	
	int getNumInputsmydspSIG1() {
		return 0;
	}
	int getNumOutputsmydspSIG1() {
		return 1;
	}
	
	void instanceInitmydspSIG1(int sample_rate) {
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			iVec1[l4] = 0;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			iRec11[l5] = 0;
		}
	}
	
	void fillmydspSIG1(int count, float* table) {
		for (int i2 = 0; (i2 < count); i2 = (i2 + 1)) {
			iVec1[0] = 1;
			iRec11[0] = ((iVec1[1] + iRec11[1]) % 65536);
			table[i2] = std::sin((9.58738019e-05f * float(iRec11[0])));
			iVec1[1] = iVec1[0];
			iRec11[1] = iRec11[0];
		}
	}

};

static mydspSIG1* newmydspSIG1() { return (mydspSIG1*)new mydspSIG1(); }
static void deletemydspSIG1(mydspSIG1* dsp) { delete dsp; }

static float ftbl1mydspSIG1[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public base_dsp {
	
 public:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fRec3[2];
	float ftbl0[192002];
	FAUSTFLOAT fHslider1;
	float fRec5[2];
	float fVec0[2];
	float fRec4[2];
	float fConst3;
	FAUSTFLOAT fHslider2;
	float fRec12[2];
	int iVec2[2];
	int iRec10[2];
	FAUSTFLOAT fHbargraph0;
	int iVec3[2];
	int iRec9[2];
	int iRec8[2];
	int iRec7[2];
	int iConst4;
	int iRec6[2];
	float fConst5;
	float fConst6;
	FAUSTFLOAT fHslider3;
	float fRec15[2];
	FAUSTFLOAT fHslider4;
	float fRec16[2];
	int IOTA;
	float fRec14[262144];
	int iConst7;
	int iVec4[2];
	int iRec17[2];
	float fRec13[2];
	FAUSTFLOAT fHslider5;
	float fRec18[2];
	FAUSTFLOAT fHslider6;
	float fRec22[2];
	float fRec21[2];
	int iVec5[2];
	float fRec20[2];
	float fRec19[2];
	float ftbl2[192002];
	int iVec6[2];
	int iRec26[2];
	int iRec25[2];
	int iRec24[2];
	int iRec23[2];
	int iConst8;
	int iVec7[2];
	int iRec28[2];
	float fRec27[2];
	float fRec30[2];
	float fRec29[2];
	float ftbl3[192002];
	int iVec8[2];
	int iRec34[2];
	int iRec33[2];
	int iRec32[2];
	int iRec31[2];
	int iConst9;
	int iVec9[2];
	int iRec36[2];
	float fRec35[2];
	float fRec38[2];
	float fRec37[2];
	float ftbl4[192002];
	int iVec10[2];
	int iRec42[2];
	int iRec41[2];
	int iRec40[2];
	int iRec39[2];
	int iConst10;
	int iVec11[2];
	int iRec44[2];
	float fRec43[2];
	float fRec46[2];
	float fRec45[2];
	float ftbl5[192002];
	int iVec12[2];
	int iRec50[2];
	int iRec49[2];
	int iRec48[2];
	int iRec47[2];
	int iConst11;
	int iVec13[2];
	int iRec52[2];
	float fRec51[2];
	float fRec54[2];
	float fRec53[2];
	float ftbl6[192002];
	int iVec14[2];
	int iRec58[2];
	int iRec57[2];
	int iRec56[2];
	int iRec55[2];
	int iConst12;
	int iVec15[2];
	int iRec60[2];
	float fRec59[2];
	float fRec62[2];
	float fRec61[2];
	float ftbl7[192002];
	int iVec16[2];
	int iRec66[2];
	int iRec65[2];
	int iRec64[2];
	int iRec63[2];
	int iConst13;
	int iVec17[2];
	int iRec68[2];
	float fRec67[2];
	float fRec70[2];
	float fRec69[2];
	float ftbl8[192002];
	int iVec18[2];
	int iRec74[2];
	int iRec73[2];
	int iRec72[2];
	int iRec71[2];
	int iConst14;
	int iVec19[2];
	int iRec76[2];
	float fRec75[2];
	float fRec78[2];
	float fRec77[2];
	float ftbl9[192002];
	int iVec20[2];
	int iRec82[2];
	int iRec81[2];
	int iRec80[2];
	int iRec79[2];
	int iConst15;
	int iVec21[2];
	int iRec84[2];
	float fRec83[2];
	float fRec86[2];
	float fRec85[2];
	float ftbl10[192002];
	int iVec22[2];
	int iRec90[2];
	int iRec89[2];
	int iRec88[2];
	int iRec87[2];
	int iConst16;
	int iVec23[2];
	int iRec92[2];
	float fRec91[2];
	float fRec94[2];
	float fRec93[2];
	float ftbl11[192002];
	int iVec24[2];
	int iRec98[2];
	int iRec97[2];
	int iRec96[2];
	int iRec95[2];
	int iConst17;
	int iVec25[2];
	int iRec100[2];
	float fRec99[2];
	float fRec102[2];
	float fRec101[2];
	float ftbl12[192002];
	int iVec26[2];
	int iRec106[2];
	int iRec105[2];
	int iRec104[2];
	int iRec103[2];
	int iConst18;
	int iVec27[2];
	int iRec108[2];
	float fRec107[2];
	float fRec110[2];
	float fRec109[2];
	float ftbl13[192002];
	int iVec28[2];
	int iRec114[2];
	int iRec113[2];
	int iRec112[2];
	int iRec111[2];
	int iConst19;
	int iVec29[2];
	int iRec116[2];
	float fRec115[2];
	float fRec118[2];
	float fRec117[2];
	float ftbl14[192002];
	int iVec30[2];
	int iRec122[2];
	int iRec121[2];
	int iRec120[2];
	int iRec119[2];
	int iConst20;
	int iVec31[2];
	int iRec124[2];
	float fRec123[2];
	float fRec126[2];
	float fRec125[2];
	float ftbl15[192002];
	int iVec32[2];
	int iRec130[2];
	int iRec129[2];
	int iRec128[2];
	int iRec127[2];
	int iConst21;
	int iVec33[2];
	int iRec132[2];
	float fRec131[2];
	float fRec134[2];
	float fRec133[2];
	float ftbl16[192002];
	int iVec34[2];
	int iRec138[2];
	int iRec137[2];
	int iRec136[2];
	int iRec135[2];
	int iConst22;
	int iVec35[2];
	int iRec140[2];
	float fRec139[2];
	float fRec142[2];
	float fRec141[2];
	float ftbl17[192002];
	int iVec36[2];
	int iRec146[2];
	int iRec145[2];
	int iRec144[2];
	int iRec143[2];
	int iConst23;
	int iVec37[2];
	int iRec148[2];
	float fRec147[2];
	float fRec150[2];
	float fRec149[2];
	float ftbl18[192002];
	int iVec38[2];
	int iRec154[2];
	int iRec153[2];
	int iRec152[2];
	int iRec151[2];
	int iConst24;
	int iVec39[2];
	int iRec156[2];
	float fRec155[2];
	float fRec158[2];
	float fRec157[2];
	float ftbl19[192002];
	int iVec40[2];
	int iRec162[2];
	int iRec161[2];
	int iRec160[2];
	int iRec159[2];
	int iConst25;
	int iVec41[2];
	int iRec164[2];
	float fRec163[2];
	float fRec166[2];
	float fRec165[2];
	float ftbl20[192002];
	int iVec42[2];
	int iRec170[2];
	int iRec169[2];
	int iRec168[2];
	int iRec167[2];
	int iConst26;
	int iVec43[2];
	int iRec172[2];
	float fRec171[2];
	float fRec174[2];
	float fRec173[2];
	float ftbl21[192002];
	int iVec44[2];
	int iRec178[2];
	int iRec177[2];
	int iRec176[2];
	int iRec175[2];
	int iConst27;
	int iVec45[2];
	int iRec180[2];
	float fRec179[2];
	float fRec182[2];
	float fRec181[2];
	float ftbl22[192002];
	int iVec46[2];
	int iRec186[2];
	int iRec185[2];
	int iRec184[2];
	int iRec183[2];
	int iConst28;
	int iVec47[2];
	int iRec188[2];
	float fRec187[2];
	float fRec190[2];
	float fRec189[2];
	float ftbl23[192002];
	int iVec48[2];
	int iRec194[2];
	int iRec193[2];
	int iRec192[2];
	int iRec191[2];
	int iConst29;
	int iVec49[2];
	int iRec196[2];
	float fRec195[2];
	float fRec198[2];
	float fRec197[2];
	float ftbl24[192002];
	int iVec50[2];
	int iRec202[2];
	int iRec201[2];
	int iRec200[2];
	int iRec199[2];
	int iConst30;
	int iVec51[2];
	int iRec204[2];
	float fRec203[2];
	float fRec206[2];
	float fRec205[2];
	float ftbl25[192002];
	int iVec52[2];
	int iRec210[2];
	int iRec209[2];
	int iRec208[2];
	int iRec207[2];
	int iConst31;
	int iVec53[2];
	int iRec212[2];
	float fRec211[2];
	float fRec214[2];
	float fRec213[2];
	float ftbl26[192002];
	int iVec54[2];
	int iRec218[2];
	int iRec217[2];
	int iRec216[2];
	int iRec215[2];
	int iConst32;
	int iVec55[2];
	int iRec220[2];
	float fRec219[2];
	float fRec222[2];
	float fRec221[2];
	float ftbl27[192002];
	int iVec56[2];
	int iRec226[2];
	int iRec225[2];
	int iRec224[2];
	int iRec223[2];
	int iConst33;
	int iVec57[2];
	int iRec228[2];
	float fRec227[2];
	float fRec230[2];
	float fRec229[2];
	float ftbl28[192002];
	int iVec58[2];
	int iRec234[2];
	int iRec233[2];
	int iRec232[2];
	int iRec231[2];
	int iConst34;
	int iVec59[2];
	int iRec236[2];
	float fRec235[2];
	float fRec238[2];
	float fRec237[2];
	float ftbl29[192002];
	int iVec60[2];
	int iRec242[2];
	int iRec241[2];
	int iRec240[2];
	int iRec239[2];
	int iConst35;
	int iVec61[2];
	int iRec244[2];
	float fRec243[2];
	float fRec246[2];
	float fRec245[2];
	float ftbl30[192002];
	int iVec62[2];
	int iRec250[2];
	int iRec249[2];
	int iRec248[2];
	int iRec247[2];
	int iConst36;
	int iVec63[2];
	int iRec252[2];
	float fRec251[2];
	float fRec254[2];
	float fRec253[2];
	float ftbl31[192002];
	int iVec64[2];
	int iRec258[2];
	int iRec257[2];
	int iRec256[2];
	int iRec255[2];
	int iConst37;
	int iVec65[2];
	int iRec260[2];
	float fRec259[2];
	float fRec262[2];
	float fRec261[2];
	float ftbl32[192002];
	int iVec66[2];
	int iRec266[2];
	int iRec265[2];
	int iRec264[2];
	int iRec263[2];
	int iConst38;
	int iVec67[2];
	int iRec268[2];
	float fRec267[2];
	float fRec270[2];
	float fRec269[2];
	float ftbl33[192002];
	int iVec68[2];
	int iRec274[2];
	int iRec273[2];
	int iRec272[2];
	int iRec271[2];
	int iConst39;
	int iVec69[2];
	int iRec276[2];
	float fRec275[2];
	float fRec278[2];
	float fRec277[2];
	float ftbl34[192002];
	int iVec70[2];
	int iRec282[2];
	int iRec281[2];
	int iRec280[2];
	int iRec279[2];
	int iConst40;
	int iVec71[2];
	int iRec284[2];
	float fRec283[2];
	float fRec286[2];
	float fRec285[2];
	float ftbl35[192002];
	int iVec72[2];
	int iRec290[2];
	int iRec289[2];
	int iRec288[2];
	int iRec287[2];
	int iConst41;
	int iVec73[2];
	int iRec292[2];
	float fRec291[2];
	float fRec294[2];
	float fRec293[2];
	float ftbl36[192002];
	int iVec74[2];
	int iRec298[2];
	int iRec297[2];
	int iRec296[2];
	int iRec295[2];
	int iConst42;
	int iVec75[2];
	int iRec300[2];
	float fRec299[2];
	float fRec302[2];
	float fRec301[2];
	float ftbl37[192002];
	int iVec76[2];
	int iRec306[2];
	int iRec305[2];
	int iRec304[2];
	int iRec303[2];
	int iConst43;
	int iVec77[2];
	int iRec308[2];
	float fRec307[2];
	float fRec310[2];
	float fRec309[2];
	float ftbl38[192002];
	int iVec78[2];
	int iRec314[2];
	int iRec313[2];
	int iRec312[2];
	int iRec311[2];
	int iConst44;
	int iVec79[2];
	int iRec316[2];
	float fRec315[2];
	float fRec318[2];
	float fRec317[2];
	float ftbl39[192002];
	int iVec80[2];
	int iRec322[2];
	int iRec321[2];
	int iRec320[2];
	int iRec319[2];
	int iConst45;
	int iVec81[2];
	int iRec324[2];
	float fRec323[2];
	float fRec326[2];
	float fRec325[2];
	float ftbl40[192002];
	int iVec82[2];
	int iRec330[2];
	int iRec329[2];
	int iRec328[2];
	int iRec327[2];
	int iConst46;
	int iVec83[2];
	int iRec332[2];
	float fRec331[2];
	float fRec334[2];
	float fRec333[2];
	float ftbl41[192002];
	int iVec84[2];
	int iRec338[2];
	int iRec337[2];
	int iRec336[2];
	int iRec335[2];
	int iConst47;
	int iVec85[2];
	int iRec340[2];
	float fRec339[2];
	float fRec342[2];
	float fRec341[2];
	float ftbl42[192002];
	int iVec86[2];
	int iRec346[2];
	int iRec345[2];
	int iRec344[2];
	int iRec343[2];
	int iConst48;
	int iVec87[2];
	int iRec348[2];
	float fRec347[2];
	float fRec350[2];
	float fRec349[2];
	float ftbl43[192002];
	int iVec88[2];
	int iRec354[2];
	int iRec353[2];
	int iRec352[2];
	int iRec351[2];
	int iConst49;
	int iVec89[2];
	int iRec356[2];
	float fRec355[2];
	float fRec358[2];
	float fRec357[2];
	float ftbl44[192002];
	int iVec90[2];
	int iRec362[2];
	int iRec361[2];
	int iRec360[2];
	int iRec359[2];
	int iConst50;
	int iVec91[2];
	int iRec364[2];
	float fRec363[2];
	float fRec366[2];
	float fRec365[2];
	float ftbl45[192002];
	int iVec92[2];
	int iRec370[2];
	int iRec369[2];
	int iRec368[2];
	int iRec367[2];
	int iConst51;
	int iVec93[2];
	int iRec372[2];
	float fRec371[2];
	float fRec374[2];
	float fRec373[2];
	float ftbl46[192002];
	int iVec94[2];
	int iRec378[2];
	int iRec377[2];
	int iRec376[2];
	int iRec375[2];
	int iConst52;
	int iVec95[2];
	int iRec380[2];
	float fRec379[2];
	float fRec382[2];
	float fRec381[2];
	float ftbl47[192002];
	int iVec96[2];
	int iRec386[2];
	int iRec385[2];
	int iRec384[2];
	int iRec383[2];
	int iConst53;
	int iVec97[2];
	int iRec388[2];
	float fRec387[2];
	float fRec390[2];
	float fRec389[2];
	float ftbl48[192002];
	int iVec98[2];
	int iRec394[2];
	int iRec393[2];
	int iRec392[2];
	int iRec391[2];
	int iConst54;
	int iVec99[2];
	int iRec396[2];
	float fRec395[2];
	float fRec398[2];
	float fRec397[2];
	float ftbl49[192002];
	int iVec100[2];
	int iRec402[2];
	int iRec401[2];
	int iRec400[2];
	int iRec399[2];
	int iConst55;
	int iVec101[2];
	int iRec404[2];
	float fRec403[2];
	float fRec406[2];
	float fRec405[2];
	float ftbl50[192002];
	int iVec102[2];
	int iRec410[2];
	int iRec409[2];
	int iRec408[2];
	int iRec407[2];
	int iConst56;
	int iVec103[2];
	int iRec412[2];
	float fRec411[2];
	float fRec414[2];
	float fRec413[2];
	float ftbl51[192002];
	int iVec104[2];
	int iRec418[2];
	int iRec417[2];
	int iRec416[2];
	int iRec415[2];
	int iConst57;
	int iVec105[2];
	int iRec420[2];
	float fRec419[2];
	float fRec422[2];
	float fRec421[2];
	float ftbl52[192002];
	int iVec106[2];
	int iRec426[2];
	int iRec425[2];
	int iRec424[2];
	int iRec423[2];
	int iConst58;
	int iVec107[2];
	int iRec428[2];
	float fRec427[2];
	float fRec430[2];
	float fRec429[2];
	float ftbl53[192002];
	int iVec108[2];
	int iRec434[2];
	int iRec433[2];
	int iRec432[2];
	int iRec431[2];
	int iConst59;
	int iVec109[2];
	int iRec436[2];
	float fRec435[2];
	float fRec438[2];
	float fRec437[2];
	float ftbl54[192002];
	int iVec110[2];
	int iRec442[2];
	int iRec441[2];
	int iRec440[2];
	int iRec439[2];
	int iConst60;
	int iVec111[2];
	int iRec444[2];
	float fRec443[2];
	float fRec446[2];
	float fRec445[2];
	float ftbl55[192002];
	int iVec112[2];
	int iRec450[2];
	int iRec449[2];
	int iRec448[2];
	int iRec447[2];
	int iConst61;
	int iVec113[2];
	int iRec452[2];
	float fRec451[2];
	float fRec454[2];
	float fRec453[2];
	float ftbl56[192002];
	int iVec114[2];
	int iRec458[2];
	int iRec457[2];
	int iRec456[2];
	int iRec455[2];
	int iConst62;
	int iVec115[2];
	int iRec460[2];
	float fRec459[2];
	float fRec462[2];
	float fRec461[2];
	float ftbl57[192002];
	int iVec116[2];
	int iRec466[2];
	int iRec465[2];
	int iRec464[2];
	int iRec463[2];
	int iConst63;
	int iVec117[2];
	int iRec468[2];
	float fRec467[2];
	float fRec470[2];
	float fRec469[2];
	float ftbl58[192002];
	int iVec118[2];
	int iRec474[2];
	int iRec473[2];
	int iRec472[2];
	int iRec471[2];
	int iConst64;
	int iVec119[2];
	int iRec476[2];
	float fRec475[2];
	float fRec478[2];
	float fRec477[2];
	float ftbl59[192002];
	int iVec120[2];
	int iRec482[2];
	int iRec481[2];
	int iRec480[2];
	int iRec479[2];
	int iConst65;
	int iVec121[2];
	int iRec484[2];
	float fRec483[2];
	float fRec486[2];
	float fRec485[2];
	float ftbl60[192002];
	int iVec122[2];
	int iRec490[2];
	int iRec489[2];
	int iRec488[2];
	int iRec487[2];
	int iConst66;
	int iVec123[2];
	int iRec492[2];
	float fRec491[2];
	float fRec494[2];
	float fRec493[2];
	float ftbl61[192002];
	int iVec124[2];
	int iRec498[2];
	int iRec497[2];
	int iRec496[2];
	int iRec495[2];
	int iConst67;
	int iVec125[2];
	int iRec500[2];
	float fRec499[2];
	float fRec502[2];
	float fRec501[2];
	float ftbl62[192002];
	int iVec126[2];
	int iRec506[2];
	int iRec505[2];
	int iRec504[2];
	int iRec503[2];
	int iConst68;
	int iVec127[2];
	int iRec508[2];
	float fRec507[2];
	float fRec510[2];
	float fRec509[2];
	float ftbl63[192002];
	int iVec128[2];
	int iRec514[2];
	int iRec513[2];
	int iRec512[2];
	int iRec511[2];
	int iConst69;
	int iVec129[2];
	int iRec516[2];
	float fRec515[2];
	float fRec518[2];
	float fRec517[2];
	float ftbl64[192002];
	int iVec130[2];
	int iRec522[2];
	int iRec521[2];
	int iRec520[2];
	int iRec519[2];
	int iConst70;
	int iVec131[2];
	int iRec524[2];
	float fRec523[2];
	float fRec526[2];
	float fRec525[2];
	float ftbl65[192002];
	int iVec132[2];
	int iRec530[2];
	int iRec529[2];
	int iRec528[2];
	int iRec527[2];
	int iConst71;
	int iVec133[2];
	int iRec532[2];
	float fRec531[2];
	float fRec534[2];
	float fRec533[2];
	float ftbl66[192002];
	int iVec134[2];
	int iRec538[2];
	int iRec537[2];
	int iRec536[2];
	int iRec535[2];
	int iConst72;
	int iVec135[2];
	int iRec540[2];
	float fRec539[2];
	float fRec542[2];
	float fRec541[2];
	float ftbl67[192002];
	int iVec136[2];
	int iRec546[2];
	int iRec545[2];
	int iRec544[2];
	int iRec543[2];
	int iConst73;
	int iVec137[2];
	int iRec548[2];
	float fRec547[2];
	float fRec550[2];
	float fRec549[2];
	float ftbl68[192002];
	int iVec138[2];
	int iRec554[2];
	int iRec553[2];
	int iRec552[2];
	int iRec551[2];
	int iConst74;
	int iVec139[2];
	int iRec556[2];
	float fRec555[2];
	float fRec558[2];
	float fRec557[2];
	float ftbl69[192002];
	int iVec140[2];
	int iRec562[2];
	int iRec561[2];
	int iRec560[2];
	int iRec559[2];
	int iConst75;
	int iVec141[2];
	int iRec564[2];
	float fRec563[2];
	float fRec566[2];
	float fRec565[2];
	float ftbl70[192002];
	int iVec142[2];
	int iRec570[2];
	int iRec569[2];
	int iRec568[2];
	int iRec567[2];
	int iConst76;
	int iVec143[2];
	int iRec572[2];
	float fRec571[2];
	float fRec574[2];
	float fRec573[2];
	float ftbl71[192002];
	int iVec144[2];
	int iRec578[2];
	int iRec577[2];
	int iRec576[2];
	int iRec575[2];
	int iConst77;
	int iVec145[2];
	int iRec580[2];
	float fRec579[2];
	float fRec582[2];
	float fRec581[2];
	float ftbl72[192002];
	int iVec146[2];
	int iRec586[2];
	int iRec585[2];
	int iRec584[2];
	int iRec583[2];
	int iConst78;
	int iVec147[2];
	int iRec588[2];
	float fRec587[2];
	float fRec590[2];
	float fRec589[2];
	float ftbl73[192002];
	int iVec148[2];
	int iRec594[2];
	int iRec593[2];
	int iRec592[2];
	int iRec591[2];
	int iConst79;
	int iVec149[2];
	int iRec596[2];
	float fRec595[2];
	float fRec598[2];
	float fRec597[2];
	float ftbl74[192002];
	int iVec150[2];
	int iRec602[2];
	int iRec601[2];
	int iRec600[2];
	int iRec599[2];
	int iConst80;
	int iVec151[2];
	int iRec604[2];
	float fRec603[2];
	float fRec606[2];
	float fRec605[2];
	float ftbl75[192002];
	int iVec152[2];
	int iRec610[2];
	int iRec609[2];
	int iRec608[2];
	int iRec607[2];
	int iConst81;
	int iVec153[2];
	int iRec612[2];
	float fRec611[2];
	float fRec614[2];
	float fRec613[2];
	float ftbl76[192002];
	int iVec154[2];
	int iRec618[2];
	int iRec617[2];
	int iRec616[2];
	int iRec615[2];
	int iConst82;
	int iVec155[2];
	int iRec620[2];
	float fRec619[2];
	float fRec622[2];
	float fRec621[2];
	float ftbl77[192002];
	int iVec156[2];
	int iRec626[2];
	int iRec625[2];
	int iRec624[2];
	int iRec623[2];
	int iConst83;
	int iVec157[2];
	int iRec628[2];
	float fRec627[2];
	float fRec630[2];
	float fRec629[2];
	float ftbl78[192002];
	int iVec158[2];
	int iRec634[2];
	int iRec633[2];
	int iRec632[2];
	int iRec631[2];
	int iConst84;
	int iVec159[2];
	int iRec636[2];
	float fRec635[2];
	float fRec638[2];
	float fRec637[2];
	float ftbl79[192002];
	int iVec160[2];
	int iRec642[2];
	int iRec641[2];
	int iRec640[2];
	int iRec639[2];
	int iConst85;
	int iVec161[2];
	int iRec644[2];
	float fRec643[2];
	float fRec646[2];
	float fRec645[2];
	float ftbl80[192002];
	int iVec162[2];
	int iRec650[2];
	int iRec649[2];
	int iRec648[2];
	int iRec647[2];
	int iConst86;
	int iVec163[2];
	int iRec652[2];
	float fRec651[2];
	float fRec654[2];
	float fRec653[2];
	float fRec0[2];
	FAUSTFLOAT fHslider7;
	float fRec655[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Luca Spanedda");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.2");
		m->declare("compile_options", "-a /usr/local/share/faust/juce/juce-plugin.cpp -lang cpp -es 1 -single -ftz 0");
		m->declare("filename", "PDB-Granulator_Realtime.dsp");
		m->declare("filters.lib/dcblocker:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblocker:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblocker:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.4");
		m->declare("name", "PDB_Realtime_Granulator");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("reference", "http://www.granularsynthesis.com/guide.php");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG1* sig1 = newmydspSIG1();
		sig1->instanceInitmydspSIG1(sample_rate);
		sig1->fillmydspSIG1(65536, ftbl1mydspSIG1);
		deletemydspSIG1(sig1);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (44.0999985f / fConst0);
		fConst2 = (1.0f - fConst1);
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl0);
		fConst3 = (1.0f / fConst0);
		iConst4 = int((fConst0 + -2.0f));
		fConst5 = float(int(fConst0));
		fConst6 = (10.0f / fConst0);
		iConst7 = int((0.180675089f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl2);
		iConst8 = int((0.861350179f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl3);
		iConst9 = int((0.542025268f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl4);
		iConst10 = int((0.222700343f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl5);
		iConst11 = int((0.903375447f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl6);
		iConst12 = int((0.584050536f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl7);
		iConst13 = int((0.264725596f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl8);
		iConst14 = int((0.945400655f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl9);
		iConst15 = int((0.626075745f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl10);
		iConst16 = int((0.306750864f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl11);
		iConst17 = int((0.987425923f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl12);
		iConst18 = int((0.668101013f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl13);
		iConst19 = int((0.348776102f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl14);
		iConst20 = int((0.0294511952f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl15);
		iConst21 = int((0.710126281f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl16);
		iConst22 = int((0.39080137f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl17);
		iConst23 = int((0.0714764521f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl18);
		iConst24 = int((0.752151549f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl19);
		iConst25 = int((0.432826608f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl20);
		iConst26 = int((0.113501705f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl21);
		iConst27 = int((0.794176817f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl22);
		iConst28 = int((0.474851876f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl23);
		iConst29 = int((0.155526966f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl24);
		iConst30 = int((0.836202025f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl25);
		iConst31 = int((0.516877115f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl26);
		iConst32 = int((0.197552219f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl27);
		iConst33 = int((0.878227293f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl28);
		iConst34 = int((0.558902383f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl29);
		iConst35 = int((0.239577472f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl30);
		iConst36 = int((0.920252562f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl31);
		iConst37 = int((0.600927651f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl32);
		iConst38 = int((0.28160274f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl33);
		iConst39 = int((0.96227783f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl34);
		iConst40 = int((0.642952919f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl35);
		iConst41 = int((0.323627979f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl36);
		iConst42 = int((0.00430307444f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl37);
		iConst43 = int((0.684978187f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl38);
		iConst44 = int((0.365653247f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl39);
		iConst45 = int((0.0463283323f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl40);
		iConst46 = int((0.727003396f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl41);
		iConst47 = int((0.407678515f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl42);
		iConst48 = int((0.0883535892f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl43);
		iConst49 = int((0.769028664f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl44);
		iConst50 = int((0.449703753f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl45);
		iConst51 = int((0.130378842f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl46);
		iConst52 = int((0.811053932f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl47);
		iConst53 = int((0.491729021f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl48);
		iConst54 = int((0.172404096f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl49);
		iConst55 = int((0.8530792f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl50);
		iConst56 = int((0.533754289f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl51);
		iConst57 = int((0.214429349f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl52);
		iConst58 = int((0.895104468f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl53);
		iConst59 = int((0.575779498f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl54);
		iConst60 = int((0.256454617f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl55);
		iConst61 = int((0.937129676f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl56);
		iConst62 = int((0.617804766f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl57);
		iConst63 = int((0.298479855f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl58);
		iConst64 = int((0.979154944f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl59);
		iConst65 = int((0.659830034f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl60);
		iConst66 = int((0.340505123f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl61);
		iConst67 = int((0.0211802088f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl62);
		iConst68 = int((0.701855302f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl63);
		iConst69 = int((0.382530391f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl64);
		iConst70 = int((0.0632054657f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl65);
		iConst71 = int((0.74388057f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl66);
		iConst72 = int((0.424555629f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl67);
		iConst73 = int((0.105230719f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl68);
		iConst74 = int((0.785905778f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl69);
		iConst75 = int((0.466580898f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl70);
		iConst76 = int((0.147255972f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl71);
		iConst77 = int((0.827931046f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl72);
		iConst78 = int((0.508606136f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl73);
		iConst79 = int((0.18928124f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl74);
		iConst80 = int((0.869956315f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl75);
		iConst81 = int((0.550631404f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl76);
		iConst82 = int((0.231306493f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl77);
		iConst83 = int((0.911981583f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl78);
		iConst84 = int((0.592656672f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl79);
		iConst85 = int((0.273331761f * fConst0));
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(192002, ftbl80);
		iConst86 = int((0.954006851f * fConst0));
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(1.0f);
		fHslider4 = FAUSTFLOAT(1.0f);
		fHslider5 = FAUSTFLOAT(1.0f);
		fHslider6 = FAUSTFLOAT(1.0f);
		fHslider7 = FAUSTFLOAT(1.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec3[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec5[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec0[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec4[l3] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec12[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			iVec2[l7] = 0;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			iRec10[l8] = 0;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			iVec3[l9] = 0;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			iRec9[l10] = 0;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			iRec8[l11] = 0;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			iRec7[l12] = 0;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			iRec6[l13] = 0;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec15[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec16[l15] = 0.0f;
		}
		IOTA = 0;
		for (int l16 = 0; (l16 < 262144); l16 = (l16 + 1)) {
			fRec14[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			iVec4[l17] = 0;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			iRec17[l18] = 0;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec13[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec18[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec22[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec21[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			iVec5[l23] = 0;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec20[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec19[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			iVec6[l26] = 0;
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			iRec26[l27] = 0;
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			iRec25[l28] = 0;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			iRec24[l29] = 0;
		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			iRec23[l30] = 0;
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			iVec7[l31] = 0;
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			iRec28[l32] = 0;
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec27[l33] = 0.0f;
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec30[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec29[l35] = 0.0f;
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			iVec8[l36] = 0;
		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			iRec34[l37] = 0;
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			iRec33[l38] = 0;
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			iRec32[l39] = 0;
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			iRec31[l40] = 0;
		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			iVec9[l41] = 0;
		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			iRec36[l42] = 0;
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec35[l43] = 0.0f;
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec38[l44] = 0.0f;
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec37[l45] = 0.0f;
		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			iVec10[l46] = 0;
		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			iRec42[l47] = 0;
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			iRec41[l48] = 0;
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			iRec40[l49] = 0;
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			iRec39[l50] = 0;
		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			iVec11[l51] = 0;
		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			iRec44[l52] = 0;
		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec43[l53] = 0.0f;
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec46[l54] = 0.0f;
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec45[l55] = 0.0f;
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			iVec12[l56] = 0;
		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			iRec50[l57] = 0;
		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			iRec49[l58] = 0;
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			iRec48[l59] = 0;
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			iRec47[l60] = 0;
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			iVec13[l61] = 0;
		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			iRec52[l62] = 0;
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec51[l63] = 0.0f;
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec54[l64] = 0.0f;
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec53[l65] = 0.0f;
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			iVec14[l66] = 0;
		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			iRec58[l67] = 0;
		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			iRec57[l68] = 0;
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			iRec56[l69] = 0;
		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			iRec55[l70] = 0;
		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			iVec15[l71] = 0;
		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			iRec60[l72] = 0;
		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec59[l73] = 0.0f;
		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec62[l74] = 0.0f;
		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec61[l75] = 0.0f;
		}
		for (int l76 = 0; (l76 < 2); l76 = (l76 + 1)) {
			iVec16[l76] = 0;
		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			iRec66[l77] = 0;
		}
		for (int l78 = 0; (l78 < 2); l78 = (l78 + 1)) {
			iRec65[l78] = 0;
		}
		for (int l79 = 0; (l79 < 2); l79 = (l79 + 1)) {
			iRec64[l79] = 0;
		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			iRec63[l80] = 0;
		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			iVec17[l81] = 0;
		}
		for (int l82 = 0; (l82 < 2); l82 = (l82 + 1)) {
			iRec68[l82] = 0;
		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			fRec67[l83] = 0.0f;
		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fRec70[l84] = 0.0f;
		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec69[l85] = 0.0f;
		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			iVec18[l86] = 0;
		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			iRec74[l87] = 0;
		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			iRec73[l88] = 0;
		}
		for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			iRec72[l89] = 0;
		}
		for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			iRec71[l90] = 0;
		}
		for (int l91 = 0; (l91 < 2); l91 = (l91 + 1)) {
			iVec19[l91] = 0;
		}
		for (int l92 = 0; (l92 < 2); l92 = (l92 + 1)) {
			iRec76[l92] = 0;
		}
		for (int l93 = 0; (l93 < 2); l93 = (l93 + 1)) {
			fRec75[l93] = 0.0f;
		}
		for (int l94 = 0; (l94 < 2); l94 = (l94 + 1)) {
			fRec78[l94] = 0.0f;
		}
		for (int l95 = 0; (l95 < 2); l95 = (l95 + 1)) {
			fRec77[l95] = 0.0f;
		}
		for (int l96 = 0; (l96 < 2); l96 = (l96 + 1)) {
			iVec20[l96] = 0;
		}
		for (int l97 = 0; (l97 < 2); l97 = (l97 + 1)) {
			iRec82[l97] = 0;
		}
		for (int l98 = 0; (l98 < 2); l98 = (l98 + 1)) {
			iRec81[l98] = 0;
		}
		for (int l99 = 0; (l99 < 2); l99 = (l99 + 1)) {
			iRec80[l99] = 0;
		}
		for (int l100 = 0; (l100 < 2); l100 = (l100 + 1)) {
			iRec79[l100] = 0;
		}
		for (int l101 = 0; (l101 < 2); l101 = (l101 + 1)) {
			iVec21[l101] = 0;
		}
		for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			iRec84[l102] = 0;
		}
		for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
			fRec83[l103] = 0.0f;
		}
		for (int l104 = 0; (l104 < 2); l104 = (l104 + 1)) {
			fRec86[l104] = 0.0f;
		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			fRec85[l105] = 0.0f;
		}
		for (int l106 = 0; (l106 < 2); l106 = (l106 + 1)) {
			iVec22[l106] = 0;
		}
		for (int l107 = 0; (l107 < 2); l107 = (l107 + 1)) {
			iRec90[l107] = 0;
		}
		for (int l108 = 0; (l108 < 2); l108 = (l108 + 1)) {
			iRec89[l108] = 0;
		}
		for (int l109 = 0; (l109 < 2); l109 = (l109 + 1)) {
			iRec88[l109] = 0;
		}
		for (int l110 = 0; (l110 < 2); l110 = (l110 + 1)) {
			iRec87[l110] = 0;
		}
		for (int l111 = 0; (l111 < 2); l111 = (l111 + 1)) {
			iVec23[l111] = 0;
		}
		for (int l112 = 0; (l112 < 2); l112 = (l112 + 1)) {
			iRec92[l112] = 0;
		}
		for (int l113 = 0; (l113 < 2); l113 = (l113 + 1)) {
			fRec91[l113] = 0.0f;
		}
		for (int l114 = 0; (l114 < 2); l114 = (l114 + 1)) {
			fRec94[l114] = 0.0f;
		}
		for (int l115 = 0; (l115 < 2); l115 = (l115 + 1)) {
			fRec93[l115] = 0.0f;
		}
		for (int l116 = 0; (l116 < 2); l116 = (l116 + 1)) {
			iVec24[l116] = 0;
		}
		for (int l117 = 0; (l117 < 2); l117 = (l117 + 1)) {
			iRec98[l117] = 0;
		}
		for (int l118 = 0; (l118 < 2); l118 = (l118 + 1)) {
			iRec97[l118] = 0;
		}
		for (int l119 = 0; (l119 < 2); l119 = (l119 + 1)) {
			iRec96[l119] = 0;
		}
		for (int l120 = 0; (l120 < 2); l120 = (l120 + 1)) {
			iRec95[l120] = 0;
		}
		for (int l121 = 0; (l121 < 2); l121 = (l121 + 1)) {
			iVec25[l121] = 0;
		}
		for (int l122 = 0; (l122 < 2); l122 = (l122 + 1)) {
			iRec100[l122] = 0;
		}
		for (int l123 = 0; (l123 < 2); l123 = (l123 + 1)) {
			fRec99[l123] = 0.0f;
		}
		for (int l124 = 0; (l124 < 2); l124 = (l124 + 1)) {
			fRec102[l124] = 0.0f;
		}
		for (int l125 = 0; (l125 < 2); l125 = (l125 + 1)) {
			fRec101[l125] = 0.0f;
		}
		for (int l126 = 0; (l126 < 2); l126 = (l126 + 1)) {
			iVec26[l126] = 0;
		}
		for (int l127 = 0; (l127 < 2); l127 = (l127 + 1)) {
			iRec106[l127] = 0;
		}
		for (int l128 = 0; (l128 < 2); l128 = (l128 + 1)) {
			iRec105[l128] = 0;
		}
		for (int l129 = 0; (l129 < 2); l129 = (l129 + 1)) {
			iRec104[l129] = 0;
		}
		for (int l130 = 0; (l130 < 2); l130 = (l130 + 1)) {
			iRec103[l130] = 0;
		}
		for (int l131 = 0; (l131 < 2); l131 = (l131 + 1)) {
			iVec27[l131] = 0;
		}
		for (int l132 = 0; (l132 < 2); l132 = (l132 + 1)) {
			iRec108[l132] = 0;
		}
		for (int l133 = 0; (l133 < 2); l133 = (l133 + 1)) {
			fRec107[l133] = 0.0f;
		}
		for (int l134 = 0; (l134 < 2); l134 = (l134 + 1)) {
			fRec110[l134] = 0.0f;
		}
		for (int l135 = 0; (l135 < 2); l135 = (l135 + 1)) {
			fRec109[l135] = 0.0f;
		}
		for (int l136 = 0; (l136 < 2); l136 = (l136 + 1)) {
			iVec28[l136] = 0;
		}
		for (int l137 = 0; (l137 < 2); l137 = (l137 + 1)) {
			iRec114[l137] = 0;
		}
		for (int l138 = 0; (l138 < 2); l138 = (l138 + 1)) {
			iRec113[l138] = 0;
		}
		for (int l139 = 0; (l139 < 2); l139 = (l139 + 1)) {
			iRec112[l139] = 0;
		}
		for (int l140 = 0; (l140 < 2); l140 = (l140 + 1)) {
			iRec111[l140] = 0;
		}
		for (int l141 = 0; (l141 < 2); l141 = (l141 + 1)) {
			iVec29[l141] = 0;
		}
		for (int l142 = 0; (l142 < 2); l142 = (l142 + 1)) {
			iRec116[l142] = 0;
		}
		for (int l143 = 0; (l143 < 2); l143 = (l143 + 1)) {
			fRec115[l143] = 0.0f;
		}
		for (int l144 = 0; (l144 < 2); l144 = (l144 + 1)) {
			fRec118[l144] = 0.0f;
		}
		for (int l145 = 0; (l145 < 2); l145 = (l145 + 1)) {
			fRec117[l145] = 0.0f;
		}
		for (int l146 = 0; (l146 < 2); l146 = (l146 + 1)) {
			iVec30[l146] = 0;
		}
		for (int l147 = 0; (l147 < 2); l147 = (l147 + 1)) {
			iRec122[l147] = 0;
		}
		for (int l148 = 0; (l148 < 2); l148 = (l148 + 1)) {
			iRec121[l148] = 0;
		}
		for (int l149 = 0; (l149 < 2); l149 = (l149 + 1)) {
			iRec120[l149] = 0;
		}
		for (int l150 = 0; (l150 < 2); l150 = (l150 + 1)) {
			iRec119[l150] = 0;
		}
		for (int l151 = 0; (l151 < 2); l151 = (l151 + 1)) {
			iVec31[l151] = 0;
		}
		for (int l152 = 0; (l152 < 2); l152 = (l152 + 1)) {
			iRec124[l152] = 0;
		}
		for (int l153 = 0; (l153 < 2); l153 = (l153 + 1)) {
			fRec123[l153] = 0.0f;
		}
		for (int l154 = 0; (l154 < 2); l154 = (l154 + 1)) {
			fRec126[l154] = 0.0f;
		}
		for (int l155 = 0; (l155 < 2); l155 = (l155 + 1)) {
			fRec125[l155] = 0.0f;
		}
		for (int l156 = 0; (l156 < 2); l156 = (l156 + 1)) {
			iVec32[l156] = 0;
		}
		for (int l157 = 0; (l157 < 2); l157 = (l157 + 1)) {
			iRec130[l157] = 0;
		}
		for (int l158 = 0; (l158 < 2); l158 = (l158 + 1)) {
			iRec129[l158] = 0;
		}
		for (int l159 = 0; (l159 < 2); l159 = (l159 + 1)) {
			iRec128[l159] = 0;
		}
		for (int l160 = 0; (l160 < 2); l160 = (l160 + 1)) {
			iRec127[l160] = 0;
		}
		for (int l161 = 0; (l161 < 2); l161 = (l161 + 1)) {
			iVec33[l161] = 0;
		}
		for (int l162 = 0; (l162 < 2); l162 = (l162 + 1)) {
			iRec132[l162] = 0;
		}
		for (int l163 = 0; (l163 < 2); l163 = (l163 + 1)) {
			fRec131[l163] = 0.0f;
		}
		for (int l164 = 0; (l164 < 2); l164 = (l164 + 1)) {
			fRec134[l164] = 0.0f;
		}
		for (int l165 = 0; (l165 < 2); l165 = (l165 + 1)) {
			fRec133[l165] = 0.0f;
		}
		for (int l166 = 0; (l166 < 2); l166 = (l166 + 1)) {
			iVec34[l166] = 0;
		}
		for (int l167 = 0; (l167 < 2); l167 = (l167 + 1)) {
			iRec138[l167] = 0;
		}
		for (int l168 = 0; (l168 < 2); l168 = (l168 + 1)) {
			iRec137[l168] = 0;
		}
		for (int l169 = 0; (l169 < 2); l169 = (l169 + 1)) {
			iRec136[l169] = 0;
		}
		for (int l170 = 0; (l170 < 2); l170 = (l170 + 1)) {
			iRec135[l170] = 0;
		}
		for (int l171 = 0; (l171 < 2); l171 = (l171 + 1)) {
			iVec35[l171] = 0;
		}
		for (int l172 = 0; (l172 < 2); l172 = (l172 + 1)) {
			iRec140[l172] = 0;
		}
		for (int l173 = 0; (l173 < 2); l173 = (l173 + 1)) {
			fRec139[l173] = 0.0f;
		}
		for (int l174 = 0; (l174 < 2); l174 = (l174 + 1)) {
			fRec142[l174] = 0.0f;
		}
		for (int l175 = 0; (l175 < 2); l175 = (l175 + 1)) {
			fRec141[l175] = 0.0f;
		}
		for (int l176 = 0; (l176 < 2); l176 = (l176 + 1)) {
			iVec36[l176] = 0;
		}
		for (int l177 = 0; (l177 < 2); l177 = (l177 + 1)) {
			iRec146[l177] = 0;
		}
		for (int l178 = 0; (l178 < 2); l178 = (l178 + 1)) {
			iRec145[l178] = 0;
		}
		for (int l179 = 0; (l179 < 2); l179 = (l179 + 1)) {
			iRec144[l179] = 0;
		}
		for (int l180 = 0; (l180 < 2); l180 = (l180 + 1)) {
			iRec143[l180] = 0;
		}
		for (int l181 = 0; (l181 < 2); l181 = (l181 + 1)) {
			iVec37[l181] = 0;
		}
		for (int l182 = 0; (l182 < 2); l182 = (l182 + 1)) {
			iRec148[l182] = 0;
		}
		for (int l183 = 0; (l183 < 2); l183 = (l183 + 1)) {
			fRec147[l183] = 0.0f;
		}
		for (int l184 = 0; (l184 < 2); l184 = (l184 + 1)) {
			fRec150[l184] = 0.0f;
		}
		for (int l185 = 0; (l185 < 2); l185 = (l185 + 1)) {
			fRec149[l185] = 0.0f;
		}
		for (int l186 = 0; (l186 < 2); l186 = (l186 + 1)) {
			iVec38[l186] = 0;
		}
		for (int l187 = 0; (l187 < 2); l187 = (l187 + 1)) {
			iRec154[l187] = 0;
		}
		for (int l188 = 0; (l188 < 2); l188 = (l188 + 1)) {
			iRec153[l188] = 0;
		}
		for (int l189 = 0; (l189 < 2); l189 = (l189 + 1)) {
			iRec152[l189] = 0;
		}
		for (int l190 = 0; (l190 < 2); l190 = (l190 + 1)) {
			iRec151[l190] = 0;
		}
		for (int l191 = 0; (l191 < 2); l191 = (l191 + 1)) {
			iVec39[l191] = 0;
		}
		for (int l192 = 0; (l192 < 2); l192 = (l192 + 1)) {
			iRec156[l192] = 0;
		}
		for (int l193 = 0; (l193 < 2); l193 = (l193 + 1)) {
			fRec155[l193] = 0.0f;
		}
		for (int l194 = 0; (l194 < 2); l194 = (l194 + 1)) {
			fRec158[l194] = 0.0f;
		}
		for (int l195 = 0; (l195 < 2); l195 = (l195 + 1)) {
			fRec157[l195] = 0.0f;
		}
		for (int l196 = 0; (l196 < 2); l196 = (l196 + 1)) {
			iVec40[l196] = 0;
		}
		for (int l197 = 0; (l197 < 2); l197 = (l197 + 1)) {
			iRec162[l197] = 0;
		}
		for (int l198 = 0; (l198 < 2); l198 = (l198 + 1)) {
			iRec161[l198] = 0;
		}
		for (int l199 = 0; (l199 < 2); l199 = (l199 + 1)) {
			iRec160[l199] = 0;
		}
		for (int l200 = 0; (l200 < 2); l200 = (l200 + 1)) {
			iRec159[l200] = 0;
		}
		for (int l201 = 0; (l201 < 2); l201 = (l201 + 1)) {
			iVec41[l201] = 0;
		}
		for (int l202 = 0; (l202 < 2); l202 = (l202 + 1)) {
			iRec164[l202] = 0;
		}
		for (int l203 = 0; (l203 < 2); l203 = (l203 + 1)) {
			fRec163[l203] = 0.0f;
		}
		for (int l204 = 0; (l204 < 2); l204 = (l204 + 1)) {
			fRec166[l204] = 0.0f;
		}
		for (int l205 = 0; (l205 < 2); l205 = (l205 + 1)) {
			fRec165[l205] = 0.0f;
		}
		for (int l206 = 0; (l206 < 2); l206 = (l206 + 1)) {
			iVec42[l206] = 0;
		}
		for (int l207 = 0; (l207 < 2); l207 = (l207 + 1)) {
			iRec170[l207] = 0;
		}
		for (int l208 = 0; (l208 < 2); l208 = (l208 + 1)) {
			iRec169[l208] = 0;
		}
		for (int l209 = 0; (l209 < 2); l209 = (l209 + 1)) {
			iRec168[l209] = 0;
		}
		for (int l210 = 0; (l210 < 2); l210 = (l210 + 1)) {
			iRec167[l210] = 0;
		}
		for (int l211 = 0; (l211 < 2); l211 = (l211 + 1)) {
			iVec43[l211] = 0;
		}
		for (int l212 = 0; (l212 < 2); l212 = (l212 + 1)) {
			iRec172[l212] = 0;
		}
		for (int l213 = 0; (l213 < 2); l213 = (l213 + 1)) {
			fRec171[l213] = 0.0f;
		}
		for (int l214 = 0; (l214 < 2); l214 = (l214 + 1)) {
			fRec174[l214] = 0.0f;
		}
		for (int l215 = 0; (l215 < 2); l215 = (l215 + 1)) {
			fRec173[l215] = 0.0f;
		}
		for (int l216 = 0; (l216 < 2); l216 = (l216 + 1)) {
			iVec44[l216] = 0;
		}
		for (int l217 = 0; (l217 < 2); l217 = (l217 + 1)) {
			iRec178[l217] = 0;
		}
		for (int l218 = 0; (l218 < 2); l218 = (l218 + 1)) {
			iRec177[l218] = 0;
		}
		for (int l219 = 0; (l219 < 2); l219 = (l219 + 1)) {
			iRec176[l219] = 0;
		}
		for (int l220 = 0; (l220 < 2); l220 = (l220 + 1)) {
			iRec175[l220] = 0;
		}
		for (int l221 = 0; (l221 < 2); l221 = (l221 + 1)) {
			iVec45[l221] = 0;
		}
		for (int l222 = 0; (l222 < 2); l222 = (l222 + 1)) {
			iRec180[l222] = 0;
		}
		for (int l223 = 0; (l223 < 2); l223 = (l223 + 1)) {
			fRec179[l223] = 0.0f;
		}
		for (int l224 = 0; (l224 < 2); l224 = (l224 + 1)) {
			fRec182[l224] = 0.0f;
		}
		for (int l225 = 0; (l225 < 2); l225 = (l225 + 1)) {
			fRec181[l225] = 0.0f;
		}
		for (int l226 = 0; (l226 < 2); l226 = (l226 + 1)) {
			iVec46[l226] = 0;
		}
		for (int l227 = 0; (l227 < 2); l227 = (l227 + 1)) {
			iRec186[l227] = 0;
		}
		for (int l228 = 0; (l228 < 2); l228 = (l228 + 1)) {
			iRec185[l228] = 0;
		}
		for (int l229 = 0; (l229 < 2); l229 = (l229 + 1)) {
			iRec184[l229] = 0;
		}
		for (int l230 = 0; (l230 < 2); l230 = (l230 + 1)) {
			iRec183[l230] = 0;
		}
		for (int l231 = 0; (l231 < 2); l231 = (l231 + 1)) {
			iVec47[l231] = 0;
		}
		for (int l232 = 0; (l232 < 2); l232 = (l232 + 1)) {
			iRec188[l232] = 0;
		}
		for (int l233 = 0; (l233 < 2); l233 = (l233 + 1)) {
			fRec187[l233] = 0.0f;
		}
		for (int l234 = 0; (l234 < 2); l234 = (l234 + 1)) {
			fRec190[l234] = 0.0f;
		}
		for (int l235 = 0; (l235 < 2); l235 = (l235 + 1)) {
			fRec189[l235] = 0.0f;
		}
		for (int l236 = 0; (l236 < 2); l236 = (l236 + 1)) {
			iVec48[l236] = 0;
		}
		for (int l237 = 0; (l237 < 2); l237 = (l237 + 1)) {
			iRec194[l237] = 0;
		}
		for (int l238 = 0; (l238 < 2); l238 = (l238 + 1)) {
			iRec193[l238] = 0;
		}
		for (int l239 = 0; (l239 < 2); l239 = (l239 + 1)) {
			iRec192[l239] = 0;
		}
		for (int l240 = 0; (l240 < 2); l240 = (l240 + 1)) {
			iRec191[l240] = 0;
		}
		for (int l241 = 0; (l241 < 2); l241 = (l241 + 1)) {
			iVec49[l241] = 0;
		}
		for (int l242 = 0; (l242 < 2); l242 = (l242 + 1)) {
			iRec196[l242] = 0;
		}
		for (int l243 = 0; (l243 < 2); l243 = (l243 + 1)) {
			fRec195[l243] = 0.0f;
		}
		for (int l244 = 0; (l244 < 2); l244 = (l244 + 1)) {
			fRec198[l244] = 0.0f;
		}
		for (int l245 = 0; (l245 < 2); l245 = (l245 + 1)) {
			fRec197[l245] = 0.0f;
		}
		for (int l246 = 0; (l246 < 2); l246 = (l246 + 1)) {
			iVec50[l246] = 0;
		}
		for (int l247 = 0; (l247 < 2); l247 = (l247 + 1)) {
			iRec202[l247] = 0;
		}
		for (int l248 = 0; (l248 < 2); l248 = (l248 + 1)) {
			iRec201[l248] = 0;
		}
		for (int l249 = 0; (l249 < 2); l249 = (l249 + 1)) {
			iRec200[l249] = 0;
		}
		for (int l250 = 0; (l250 < 2); l250 = (l250 + 1)) {
			iRec199[l250] = 0;
		}
		for (int l251 = 0; (l251 < 2); l251 = (l251 + 1)) {
			iVec51[l251] = 0;
		}
		for (int l252 = 0; (l252 < 2); l252 = (l252 + 1)) {
			iRec204[l252] = 0;
		}
		for (int l253 = 0; (l253 < 2); l253 = (l253 + 1)) {
			fRec203[l253] = 0.0f;
		}
		for (int l254 = 0; (l254 < 2); l254 = (l254 + 1)) {
			fRec206[l254] = 0.0f;
		}
		for (int l255 = 0; (l255 < 2); l255 = (l255 + 1)) {
			fRec205[l255] = 0.0f;
		}
		for (int l256 = 0; (l256 < 2); l256 = (l256 + 1)) {
			iVec52[l256] = 0;
		}
		for (int l257 = 0; (l257 < 2); l257 = (l257 + 1)) {
			iRec210[l257] = 0;
		}
		for (int l258 = 0; (l258 < 2); l258 = (l258 + 1)) {
			iRec209[l258] = 0;
		}
		for (int l259 = 0; (l259 < 2); l259 = (l259 + 1)) {
			iRec208[l259] = 0;
		}
		for (int l260 = 0; (l260 < 2); l260 = (l260 + 1)) {
			iRec207[l260] = 0;
		}
		for (int l261 = 0; (l261 < 2); l261 = (l261 + 1)) {
			iVec53[l261] = 0;
		}
		for (int l262 = 0; (l262 < 2); l262 = (l262 + 1)) {
			iRec212[l262] = 0;
		}
		for (int l263 = 0; (l263 < 2); l263 = (l263 + 1)) {
			fRec211[l263] = 0.0f;
		}
		for (int l264 = 0; (l264 < 2); l264 = (l264 + 1)) {
			fRec214[l264] = 0.0f;
		}
		for (int l265 = 0; (l265 < 2); l265 = (l265 + 1)) {
			fRec213[l265] = 0.0f;
		}
		for (int l266 = 0; (l266 < 2); l266 = (l266 + 1)) {
			iVec54[l266] = 0;
		}
		for (int l267 = 0; (l267 < 2); l267 = (l267 + 1)) {
			iRec218[l267] = 0;
		}
		for (int l268 = 0; (l268 < 2); l268 = (l268 + 1)) {
			iRec217[l268] = 0;
		}
		for (int l269 = 0; (l269 < 2); l269 = (l269 + 1)) {
			iRec216[l269] = 0;
		}
		for (int l270 = 0; (l270 < 2); l270 = (l270 + 1)) {
			iRec215[l270] = 0;
		}
		for (int l271 = 0; (l271 < 2); l271 = (l271 + 1)) {
			iVec55[l271] = 0;
		}
		for (int l272 = 0; (l272 < 2); l272 = (l272 + 1)) {
			iRec220[l272] = 0;
		}
		for (int l273 = 0; (l273 < 2); l273 = (l273 + 1)) {
			fRec219[l273] = 0.0f;
		}
		for (int l274 = 0; (l274 < 2); l274 = (l274 + 1)) {
			fRec222[l274] = 0.0f;
		}
		for (int l275 = 0; (l275 < 2); l275 = (l275 + 1)) {
			fRec221[l275] = 0.0f;
		}
		for (int l276 = 0; (l276 < 2); l276 = (l276 + 1)) {
			iVec56[l276] = 0;
		}
		for (int l277 = 0; (l277 < 2); l277 = (l277 + 1)) {
			iRec226[l277] = 0;
		}
		for (int l278 = 0; (l278 < 2); l278 = (l278 + 1)) {
			iRec225[l278] = 0;
		}
		for (int l279 = 0; (l279 < 2); l279 = (l279 + 1)) {
			iRec224[l279] = 0;
		}
		for (int l280 = 0; (l280 < 2); l280 = (l280 + 1)) {
			iRec223[l280] = 0;
		}
		for (int l281 = 0; (l281 < 2); l281 = (l281 + 1)) {
			iVec57[l281] = 0;
		}
		for (int l282 = 0; (l282 < 2); l282 = (l282 + 1)) {
			iRec228[l282] = 0;
		}
		for (int l283 = 0; (l283 < 2); l283 = (l283 + 1)) {
			fRec227[l283] = 0.0f;
		}
		for (int l284 = 0; (l284 < 2); l284 = (l284 + 1)) {
			fRec230[l284] = 0.0f;
		}
		for (int l285 = 0; (l285 < 2); l285 = (l285 + 1)) {
			fRec229[l285] = 0.0f;
		}
		for (int l286 = 0; (l286 < 2); l286 = (l286 + 1)) {
			iVec58[l286] = 0;
		}
		for (int l287 = 0; (l287 < 2); l287 = (l287 + 1)) {
			iRec234[l287] = 0;
		}
		for (int l288 = 0; (l288 < 2); l288 = (l288 + 1)) {
			iRec233[l288] = 0;
		}
		for (int l289 = 0; (l289 < 2); l289 = (l289 + 1)) {
			iRec232[l289] = 0;
		}
		for (int l290 = 0; (l290 < 2); l290 = (l290 + 1)) {
			iRec231[l290] = 0;
		}
		for (int l291 = 0; (l291 < 2); l291 = (l291 + 1)) {
			iVec59[l291] = 0;
		}
		for (int l292 = 0; (l292 < 2); l292 = (l292 + 1)) {
			iRec236[l292] = 0;
		}
		for (int l293 = 0; (l293 < 2); l293 = (l293 + 1)) {
			fRec235[l293] = 0.0f;
		}
		for (int l294 = 0; (l294 < 2); l294 = (l294 + 1)) {
			fRec238[l294] = 0.0f;
		}
		for (int l295 = 0; (l295 < 2); l295 = (l295 + 1)) {
			fRec237[l295] = 0.0f;
		}
		for (int l296 = 0; (l296 < 2); l296 = (l296 + 1)) {
			iVec60[l296] = 0;
		}
		for (int l297 = 0; (l297 < 2); l297 = (l297 + 1)) {
			iRec242[l297] = 0;
		}
		for (int l298 = 0; (l298 < 2); l298 = (l298 + 1)) {
			iRec241[l298] = 0;
		}
		for (int l299 = 0; (l299 < 2); l299 = (l299 + 1)) {
			iRec240[l299] = 0;
		}
		for (int l300 = 0; (l300 < 2); l300 = (l300 + 1)) {
			iRec239[l300] = 0;
		}
		for (int l301 = 0; (l301 < 2); l301 = (l301 + 1)) {
			iVec61[l301] = 0;
		}
		for (int l302 = 0; (l302 < 2); l302 = (l302 + 1)) {
			iRec244[l302] = 0;
		}
		for (int l303 = 0; (l303 < 2); l303 = (l303 + 1)) {
			fRec243[l303] = 0.0f;
		}
		for (int l304 = 0; (l304 < 2); l304 = (l304 + 1)) {
			fRec246[l304] = 0.0f;
		}
		for (int l305 = 0; (l305 < 2); l305 = (l305 + 1)) {
			fRec245[l305] = 0.0f;
		}
		for (int l306 = 0; (l306 < 2); l306 = (l306 + 1)) {
			iVec62[l306] = 0;
		}
		for (int l307 = 0; (l307 < 2); l307 = (l307 + 1)) {
			iRec250[l307] = 0;
		}
		for (int l308 = 0; (l308 < 2); l308 = (l308 + 1)) {
			iRec249[l308] = 0;
		}
		for (int l309 = 0; (l309 < 2); l309 = (l309 + 1)) {
			iRec248[l309] = 0;
		}
		for (int l310 = 0; (l310 < 2); l310 = (l310 + 1)) {
			iRec247[l310] = 0;
		}
		for (int l311 = 0; (l311 < 2); l311 = (l311 + 1)) {
			iVec63[l311] = 0;
		}
		for (int l312 = 0; (l312 < 2); l312 = (l312 + 1)) {
			iRec252[l312] = 0;
		}
		for (int l313 = 0; (l313 < 2); l313 = (l313 + 1)) {
			fRec251[l313] = 0.0f;
		}
		for (int l314 = 0; (l314 < 2); l314 = (l314 + 1)) {
			fRec254[l314] = 0.0f;
		}
		for (int l315 = 0; (l315 < 2); l315 = (l315 + 1)) {
			fRec253[l315] = 0.0f;
		}
		for (int l316 = 0; (l316 < 2); l316 = (l316 + 1)) {
			iVec64[l316] = 0;
		}
		for (int l317 = 0; (l317 < 2); l317 = (l317 + 1)) {
			iRec258[l317] = 0;
		}
		for (int l318 = 0; (l318 < 2); l318 = (l318 + 1)) {
			iRec257[l318] = 0;
		}
		for (int l319 = 0; (l319 < 2); l319 = (l319 + 1)) {
			iRec256[l319] = 0;
		}
		for (int l320 = 0; (l320 < 2); l320 = (l320 + 1)) {
			iRec255[l320] = 0;
		}
		for (int l321 = 0; (l321 < 2); l321 = (l321 + 1)) {
			iVec65[l321] = 0;
		}
		for (int l322 = 0; (l322 < 2); l322 = (l322 + 1)) {
			iRec260[l322] = 0;
		}
		for (int l323 = 0; (l323 < 2); l323 = (l323 + 1)) {
			fRec259[l323] = 0.0f;
		}
		for (int l324 = 0; (l324 < 2); l324 = (l324 + 1)) {
			fRec262[l324] = 0.0f;
		}
		for (int l325 = 0; (l325 < 2); l325 = (l325 + 1)) {
			fRec261[l325] = 0.0f;
		}
		for (int l326 = 0; (l326 < 2); l326 = (l326 + 1)) {
			iVec66[l326] = 0;
		}
		for (int l327 = 0; (l327 < 2); l327 = (l327 + 1)) {
			iRec266[l327] = 0;
		}
		for (int l328 = 0; (l328 < 2); l328 = (l328 + 1)) {
			iRec265[l328] = 0;
		}
		for (int l329 = 0; (l329 < 2); l329 = (l329 + 1)) {
			iRec264[l329] = 0;
		}
		for (int l330 = 0; (l330 < 2); l330 = (l330 + 1)) {
			iRec263[l330] = 0;
		}
		for (int l331 = 0; (l331 < 2); l331 = (l331 + 1)) {
			iVec67[l331] = 0;
		}
		for (int l332 = 0; (l332 < 2); l332 = (l332 + 1)) {
			iRec268[l332] = 0;
		}
		for (int l333 = 0; (l333 < 2); l333 = (l333 + 1)) {
			fRec267[l333] = 0.0f;
		}
		for (int l334 = 0; (l334 < 2); l334 = (l334 + 1)) {
			fRec270[l334] = 0.0f;
		}
		for (int l335 = 0; (l335 < 2); l335 = (l335 + 1)) {
			fRec269[l335] = 0.0f;
		}
		for (int l336 = 0; (l336 < 2); l336 = (l336 + 1)) {
			iVec68[l336] = 0;
		}
		for (int l337 = 0; (l337 < 2); l337 = (l337 + 1)) {
			iRec274[l337] = 0;
		}
		for (int l338 = 0; (l338 < 2); l338 = (l338 + 1)) {
			iRec273[l338] = 0;
		}
		for (int l339 = 0; (l339 < 2); l339 = (l339 + 1)) {
			iRec272[l339] = 0;
		}
		for (int l340 = 0; (l340 < 2); l340 = (l340 + 1)) {
			iRec271[l340] = 0;
		}
		for (int l341 = 0; (l341 < 2); l341 = (l341 + 1)) {
			iVec69[l341] = 0;
		}
		for (int l342 = 0; (l342 < 2); l342 = (l342 + 1)) {
			iRec276[l342] = 0;
		}
		for (int l343 = 0; (l343 < 2); l343 = (l343 + 1)) {
			fRec275[l343] = 0.0f;
		}
		for (int l344 = 0; (l344 < 2); l344 = (l344 + 1)) {
			fRec278[l344] = 0.0f;
		}
		for (int l345 = 0; (l345 < 2); l345 = (l345 + 1)) {
			fRec277[l345] = 0.0f;
		}
		for (int l346 = 0; (l346 < 2); l346 = (l346 + 1)) {
			iVec70[l346] = 0;
		}
		for (int l347 = 0; (l347 < 2); l347 = (l347 + 1)) {
			iRec282[l347] = 0;
		}
		for (int l348 = 0; (l348 < 2); l348 = (l348 + 1)) {
			iRec281[l348] = 0;
		}
		for (int l349 = 0; (l349 < 2); l349 = (l349 + 1)) {
			iRec280[l349] = 0;
		}
		for (int l350 = 0; (l350 < 2); l350 = (l350 + 1)) {
			iRec279[l350] = 0;
		}
		for (int l351 = 0; (l351 < 2); l351 = (l351 + 1)) {
			iVec71[l351] = 0;
		}
		for (int l352 = 0; (l352 < 2); l352 = (l352 + 1)) {
			iRec284[l352] = 0;
		}
		for (int l353 = 0; (l353 < 2); l353 = (l353 + 1)) {
			fRec283[l353] = 0.0f;
		}
		for (int l354 = 0; (l354 < 2); l354 = (l354 + 1)) {
			fRec286[l354] = 0.0f;
		}
		for (int l355 = 0; (l355 < 2); l355 = (l355 + 1)) {
			fRec285[l355] = 0.0f;
		}
		for (int l356 = 0; (l356 < 2); l356 = (l356 + 1)) {
			iVec72[l356] = 0;
		}
		for (int l357 = 0; (l357 < 2); l357 = (l357 + 1)) {
			iRec290[l357] = 0;
		}
		for (int l358 = 0; (l358 < 2); l358 = (l358 + 1)) {
			iRec289[l358] = 0;
		}
		for (int l359 = 0; (l359 < 2); l359 = (l359 + 1)) {
			iRec288[l359] = 0;
		}
		for (int l360 = 0; (l360 < 2); l360 = (l360 + 1)) {
			iRec287[l360] = 0;
		}
		for (int l361 = 0; (l361 < 2); l361 = (l361 + 1)) {
			iVec73[l361] = 0;
		}
		for (int l362 = 0; (l362 < 2); l362 = (l362 + 1)) {
			iRec292[l362] = 0;
		}
		for (int l363 = 0; (l363 < 2); l363 = (l363 + 1)) {
			fRec291[l363] = 0.0f;
		}
		for (int l364 = 0; (l364 < 2); l364 = (l364 + 1)) {
			fRec294[l364] = 0.0f;
		}
		for (int l365 = 0; (l365 < 2); l365 = (l365 + 1)) {
			fRec293[l365] = 0.0f;
		}
		for (int l366 = 0; (l366 < 2); l366 = (l366 + 1)) {
			iVec74[l366] = 0;
		}
		for (int l367 = 0; (l367 < 2); l367 = (l367 + 1)) {
			iRec298[l367] = 0;
		}
		for (int l368 = 0; (l368 < 2); l368 = (l368 + 1)) {
			iRec297[l368] = 0;
		}
		for (int l369 = 0; (l369 < 2); l369 = (l369 + 1)) {
			iRec296[l369] = 0;
		}
		for (int l370 = 0; (l370 < 2); l370 = (l370 + 1)) {
			iRec295[l370] = 0;
		}
		for (int l371 = 0; (l371 < 2); l371 = (l371 + 1)) {
			iVec75[l371] = 0;
		}
		for (int l372 = 0; (l372 < 2); l372 = (l372 + 1)) {
			iRec300[l372] = 0;
		}
		for (int l373 = 0; (l373 < 2); l373 = (l373 + 1)) {
			fRec299[l373] = 0.0f;
		}
		for (int l374 = 0; (l374 < 2); l374 = (l374 + 1)) {
			fRec302[l374] = 0.0f;
		}
		for (int l375 = 0; (l375 < 2); l375 = (l375 + 1)) {
			fRec301[l375] = 0.0f;
		}
		for (int l376 = 0; (l376 < 2); l376 = (l376 + 1)) {
			iVec76[l376] = 0;
		}
		for (int l377 = 0; (l377 < 2); l377 = (l377 + 1)) {
			iRec306[l377] = 0;
		}
		for (int l378 = 0; (l378 < 2); l378 = (l378 + 1)) {
			iRec305[l378] = 0;
		}
		for (int l379 = 0; (l379 < 2); l379 = (l379 + 1)) {
			iRec304[l379] = 0;
		}
		for (int l380 = 0; (l380 < 2); l380 = (l380 + 1)) {
			iRec303[l380] = 0;
		}
		for (int l381 = 0; (l381 < 2); l381 = (l381 + 1)) {
			iVec77[l381] = 0;
		}
		for (int l382 = 0; (l382 < 2); l382 = (l382 + 1)) {
			iRec308[l382] = 0;
		}
		for (int l383 = 0; (l383 < 2); l383 = (l383 + 1)) {
			fRec307[l383] = 0.0f;
		}
		for (int l384 = 0; (l384 < 2); l384 = (l384 + 1)) {
			fRec310[l384] = 0.0f;
		}
		for (int l385 = 0; (l385 < 2); l385 = (l385 + 1)) {
			fRec309[l385] = 0.0f;
		}
		for (int l386 = 0; (l386 < 2); l386 = (l386 + 1)) {
			iVec78[l386] = 0;
		}
		for (int l387 = 0; (l387 < 2); l387 = (l387 + 1)) {
			iRec314[l387] = 0;
		}
		for (int l388 = 0; (l388 < 2); l388 = (l388 + 1)) {
			iRec313[l388] = 0;
		}
		for (int l389 = 0; (l389 < 2); l389 = (l389 + 1)) {
			iRec312[l389] = 0;
		}
		for (int l390 = 0; (l390 < 2); l390 = (l390 + 1)) {
			iRec311[l390] = 0;
		}
		for (int l391 = 0; (l391 < 2); l391 = (l391 + 1)) {
			iVec79[l391] = 0;
		}
		for (int l392 = 0; (l392 < 2); l392 = (l392 + 1)) {
			iRec316[l392] = 0;
		}
		for (int l393 = 0; (l393 < 2); l393 = (l393 + 1)) {
			fRec315[l393] = 0.0f;
		}
		for (int l394 = 0; (l394 < 2); l394 = (l394 + 1)) {
			fRec318[l394] = 0.0f;
		}
		for (int l395 = 0; (l395 < 2); l395 = (l395 + 1)) {
			fRec317[l395] = 0.0f;
		}
		for (int l396 = 0; (l396 < 2); l396 = (l396 + 1)) {
			iVec80[l396] = 0;
		}
		for (int l397 = 0; (l397 < 2); l397 = (l397 + 1)) {
			iRec322[l397] = 0;
		}
		for (int l398 = 0; (l398 < 2); l398 = (l398 + 1)) {
			iRec321[l398] = 0;
		}
		for (int l399 = 0; (l399 < 2); l399 = (l399 + 1)) {
			iRec320[l399] = 0;
		}
		for (int l400 = 0; (l400 < 2); l400 = (l400 + 1)) {
			iRec319[l400] = 0;
		}
		for (int l401 = 0; (l401 < 2); l401 = (l401 + 1)) {
			iVec81[l401] = 0;
		}
		for (int l402 = 0; (l402 < 2); l402 = (l402 + 1)) {
			iRec324[l402] = 0;
		}
		for (int l403 = 0; (l403 < 2); l403 = (l403 + 1)) {
			fRec323[l403] = 0.0f;
		}
		for (int l404 = 0; (l404 < 2); l404 = (l404 + 1)) {
			fRec326[l404] = 0.0f;
		}
		for (int l405 = 0; (l405 < 2); l405 = (l405 + 1)) {
			fRec325[l405] = 0.0f;
		}
		for (int l406 = 0; (l406 < 2); l406 = (l406 + 1)) {
			iVec82[l406] = 0;
		}
		for (int l407 = 0; (l407 < 2); l407 = (l407 + 1)) {
			iRec330[l407] = 0;
		}
		for (int l408 = 0; (l408 < 2); l408 = (l408 + 1)) {
			iRec329[l408] = 0;
		}
		for (int l409 = 0; (l409 < 2); l409 = (l409 + 1)) {
			iRec328[l409] = 0;
		}
		for (int l410 = 0; (l410 < 2); l410 = (l410 + 1)) {
			iRec327[l410] = 0;
		}
		for (int l411 = 0; (l411 < 2); l411 = (l411 + 1)) {
			iVec83[l411] = 0;
		}
		for (int l412 = 0; (l412 < 2); l412 = (l412 + 1)) {
			iRec332[l412] = 0;
		}
		for (int l413 = 0; (l413 < 2); l413 = (l413 + 1)) {
			fRec331[l413] = 0.0f;
		}
		for (int l414 = 0; (l414 < 2); l414 = (l414 + 1)) {
			fRec334[l414] = 0.0f;
		}
		for (int l415 = 0; (l415 < 2); l415 = (l415 + 1)) {
			fRec333[l415] = 0.0f;
		}
		for (int l416 = 0; (l416 < 2); l416 = (l416 + 1)) {
			iVec84[l416] = 0;
		}
		for (int l417 = 0; (l417 < 2); l417 = (l417 + 1)) {
			iRec338[l417] = 0;
		}
		for (int l418 = 0; (l418 < 2); l418 = (l418 + 1)) {
			iRec337[l418] = 0;
		}
		for (int l419 = 0; (l419 < 2); l419 = (l419 + 1)) {
			iRec336[l419] = 0;
		}
		for (int l420 = 0; (l420 < 2); l420 = (l420 + 1)) {
			iRec335[l420] = 0;
		}
		for (int l421 = 0; (l421 < 2); l421 = (l421 + 1)) {
			iVec85[l421] = 0;
		}
		for (int l422 = 0; (l422 < 2); l422 = (l422 + 1)) {
			iRec340[l422] = 0;
		}
		for (int l423 = 0; (l423 < 2); l423 = (l423 + 1)) {
			fRec339[l423] = 0.0f;
		}
		for (int l424 = 0; (l424 < 2); l424 = (l424 + 1)) {
			fRec342[l424] = 0.0f;
		}
		for (int l425 = 0; (l425 < 2); l425 = (l425 + 1)) {
			fRec341[l425] = 0.0f;
		}
		for (int l426 = 0; (l426 < 2); l426 = (l426 + 1)) {
			iVec86[l426] = 0;
		}
		for (int l427 = 0; (l427 < 2); l427 = (l427 + 1)) {
			iRec346[l427] = 0;
		}
		for (int l428 = 0; (l428 < 2); l428 = (l428 + 1)) {
			iRec345[l428] = 0;
		}
		for (int l429 = 0; (l429 < 2); l429 = (l429 + 1)) {
			iRec344[l429] = 0;
		}
		for (int l430 = 0; (l430 < 2); l430 = (l430 + 1)) {
			iRec343[l430] = 0;
		}
		for (int l431 = 0; (l431 < 2); l431 = (l431 + 1)) {
			iVec87[l431] = 0;
		}
		for (int l432 = 0; (l432 < 2); l432 = (l432 + 1)) {
			iRec348[l432] = 0;
		}
		for (int l433 = 0; (l433 < 2); l433 = (l433 + 1)) {
			fRec347[l433] = 0.0f;
		}
		for (int l434 = 0; (l434 < 2); l434 = (l434 + 1)) {
			fRec350[l434] = 0.0f;
		}
		for (int l435 = 0; (l435 < 2); l435 = (l435 + 1)) {
			fRec349[l435] = 0.0f;
		}
		for (int l436 = 0; (l436 < 2); l436 = (l436 + 1)) {
			iVec88[l436] = 0;
		}
		for (int l437 = 0; (l437 < 2); l437 = (l437 + 1)) {
			iRec354[l437] = 0;
		}
		for (int l438 = 0; (l438 < 2); l438 = (l438 + 1)) {
			iRec353[l438] = 0;
		}
		for (int l439 = 0; (l439 < 2); l439 = (l439 + 1)) {
			iRec352[l439] = 0;
		}
		for (int l440 = 0; (l440 < 2); l440 = (l440 + 1)) {
			iRec351[l440] = 0;
		}
		for (int l441 = 0; (l441 < 2); l441 = (l441 + 1)) {
			iVec89[l441] = 0;
		}
		for (int l442 = 0; (l442 < 2); l442 = (l442 + 1)) {
			iRec356[l442] = 0;
		}
		for (int l443 = 0; (l443 < 2); l443 = (l443 + 1)) {
			fRec355[l443] = 0.0f;
		}
		for (int l444 = 0; (l444 < 2); l444 = (l444 + 1)) {
			fRec358[l444] = 0.0f;
		}
		for (int l445 = 0; (l445 < 2); l445 = (l445 + 1)) {
			fRec357[l445] = 0.0f;
		}
		for (int l446 = 0; (l446 < 2); l446 = (l446 + 1)) {
			iVec90[l446] = 0;
		}
		for (int l447 = 0; (l447 < 2); l447 = (l447 + 1)) {
			iRec362[l447] = 0;
		}
		for (int l448 = 0; (l448 < 2); l448 = (l448 + 1)) {
			iRec361[l448] = 0;
		}
		for (int l449 = 0; (l449 < 2); l449 = (l449 + 1)) {
			iRec360[l449] = 0;
		}
		for (int l450 = 0; (l450 < 2); l450 = (l450 + 1)) {
			iRec359[l450] = 0;
		}
		for (int l451 = 0; (l451 < 2); l451 = (l451 + 1)) {
			iVec91[l451] = 0;
		}
		for (int l452 = 0; (l452 < 2); l452 = (l452 + 1)) {
			iRec364[l452] = 0;
		}
		for (int l453 = 0; (l453 < 2); l453 = (l453 + 1)) {
			fRec363[l453] = 0.0f;
		}
		for (int l454 = 0; (l454 < 2); l454 = (l454 + 1)) {
			fRec366[l454] = 0.0f;
		}
		for (int l455 = 0; (l455 < 2); l455 = (l455 + 1)) {
			fRec365[l455] = 0.0f;
		}
		for (int l456 = 0; (l456 < 2); l456 = (l456 + 1)) {
			iVec92[l456] = 0;
		}
		for (int l457 = 0; (l457 < 2); l457 = (l457 + 1)) {
			iRec370[l457] = 0;
		}
		for (int l458 = 0; (l458 < 2); l458 = (l458 + 1)) {
			iRec369[l458] = 0;
		}
		for (int l459 = 0; (l459 < 2); l459 = (l459 + 1)) {
			iRec368[l459] = 0;
		}
		for (int l460 = 0; (l460 < 2); l460 = (l460 + 1)) {
			iRec367[l460] = 0;
		}
		for (int l461 = 0; (l461 < 2); l461 = (l461 + 1)) {
			iVec93[l461] = 0;
		}
		for (int l462 = 0; (l462 < 2); l462 = (l462 + 1)) {
			iRec372[l462] = 0;
		}
		for (int l463 = 0; (l463 < 2); l463 = (l463 + 1)) {
			fRec371[l463] = 0.0f;
		}
		for (int l464 = 0; (l464 < 2); l464 = (l464 + 1)) {
			fRec374[l464] = 0.0f;
		}
		for (int l465 = 0; (l465 < 2); l465 = (l465 + 1)) {
			fRec373[l465] = 0.0f;
		}
		for (int l466 = 0; (l466 < 2); l466 = (l466 + 1)) {
			iVec94[l466] = 0;
		}
		for (int l467 = 0; (l467 < 2); l467 = (l467 + 1)) {
			iRec378[l467] = 0;
		}
		for (int l468 = 0; (l468 < 2); l468 = (l468 + 1)) {
			iRec377[l468] = 0;
		}
		for (int l469 = 0; (l469 < 2); l469 = (l469 + 1)) {
			iRec376[l469] = 0;
		}
		for (int l470 = 0; (l470 < 2); l470 = (l470 + 1)) {
			iRec375[l470] = 0;
		}
		for (int l471 = 0; (l471 < 2); l471 = (l471 + 1)) {
			iVec95[l471] = 0;
		}
		for (int l472 = 0; (l472 < 2); l472 = (l472 + 1)) {
			iRec380[l472] = 0;
		}
		for (int l473 = 0; (l473 < 2); l473 = (l473 + 1)) {
			fRec379[l473] = 0.0f;
		}
		for (int l474 = 0; (l474 < 2); l474 = (l474 + 1)) {
			fRec382[l474] = 0.0f;
		}
		for (int l475 = 0; (l475 < 2); l475 = (l475 + 1)) {
			fRec381[l475] = 0.0f;
		}
		for (int l476 = 0; (l476 < 2); l476 = (l476 + 1)) {
			iVec96[l476] = 0;
		}
		for (int l477 = 0; (l477 < 2); l477 = (l477 + 1)) {
			iRec386[l477] = 0;
		}
		for (int l478 = 0; (l478 < 2); l478 = (l478 + 1)) {
			iRec385[l478] = 0;
		}
		for (int l479 = 0; (l479 < 2); l479 = (l479 + 1)) {
			iRec384[l479] = 0;
		}
		for (int l480 = 0; (l480 < 2); l480 = (l480 + 1)) {
			iRec383[l480] = 0;
		}
		for (int l481 = 0; (l481 < 2); l481 = (l481 + 1)) {
			iVec97[l481] = 0;
		}
		for (int l482 = 0; (l482 < 2); l482 = (l482 + 1)) {
			iRec388[l482] = 0;
		}
		for (int l483 = 0; (l483 < 2); l483 = (l483 + 1)) {
			fRec387[l483] = 0.0f;
		}
		for (int l484 = 0; (l484 < 2); l484 = (l484 + 1)) {
			fRec390[l484] = 0.0f;
		}
		for (int l485 = 0; (l485 < 2); l485 = (l485 + 1)) {
			fRec389[l485] = 0.0f;
		}
		for (int l486 = 0; (l486 < 2); l486 = (l486 + 1)) {
			iVec98[l486] = 0;
		}
		for (int l487 = 0; (l487 < 2); l487 = (l487 + 1)) {
			iRec394[l487] = 0;
		}
		for (int l488 = 0; (l488 < 2); l488 = (l488 + 1)) {
			iRec393[l488] = 0;
		}
		for (int l489 = 0; (l489 < 2); l489 = (l489 + 1)) {
			iRec392[l489] = 0;
		}
		for (int l490 = 0; (l490 < 2); l490 = (l490 + 1)) {
			iRec391[l490] = 0;
		}
		for (int l491 = 0; (l491 < 2); l491 = (l491 + 1)) {
			iVec99[l491] = 0;
		}
		for (int l492 = 0; (l492 < 2); l492 = (l492 + 1)) {
			iRec396[l492] = 0;
		}
		for (int l493 = 0; (l493 < 2); l493 = (l493 + 1)) {
			fRec395[l493] = 0.0f;
		}
		for (int l494 = 0; (l494 < 2); l494 = (l494 + 1)) {
			fRec398[l494] = 0.0f;
		}
		for (int l495 = 0; (l495 < 2); l495 = (l495 + 1)) {
			fRec397[l495] = 0.0f;
		}
		for (int l496 = 0; (l496 < 2); l496 = (l496 + 1)) {
			iVec100[l496] = 0;
		}
		for (int l497 = 0; (l497 < 2); l497 = (l497 + 1)) {
			iRec402[l497] = 0;
		}
		for (int l498 = 0; (l498 < 2); l498 = (l498 + 1)) {
			iRec401[l498] = 0;
		}
		for (int l499 = 0; (l499 < 2); l499 = (l499 + 1)) {
			iRec400[l499] = 0;
		}
		for (int l500 = 0; (l500 < 2); l500 = (l500 + 1)) {
			iRec399[l500] = 0;
		}
		for (int l501 = 0; (l501 < 2); l501 = (l501 + 1)) {
			iVec101[l501] = 0;
		}
		for (int l502 = 0; (l502 < 2); l502 = (l502 + 1)) {
			iRec404[l502] = 0;
		}
		for (int l503 = 0; (l503 < 2); l503 = (l503 + 1)) {
			fRec403[l503] = 0.0f;
		}
		for (int l504 = 0; (l504 < 2); l504 = (l504 + 1)) {
			fRec406[l504] = 0.0f;
		}
		for (int l505 = 0; (l505 < 2); l505 = (l505 + 1)) {
			fRec405[l505] = 0.0f;
		}
		for (int l506 = 0; (l506 < 2); l506 = (l506 + 1)) {
			iVec102[l506] = 0;
		}
		for (int l507 = 0; (l507 < 2); l507 = (l507 + 1)) {
			iRec410[l507] = 0;
		}
		for (int l508 = 0; (l508 < 2); l508 = (l508 + 1)) {
			iRec409[l508] = 0;
		}
		for (int l509 = 0; (l509 < 2); l509 = (l509 + 1)) {
			iRec408[l509] = 0;
		}
		for (int l510 = 0; (l510 < 2); l510 = (l510 + 1)) {
			iRec407[l510] = 0;
		}
		for (int l511 = 0; (l511 < 2); l511 = (l511 + 1)) {
			iVec103[l511] = 0;
		}
		for (int l512 = 0; (l512 < 2); l512 = (l512 + 1)) {
			iRec412[l512] = 0;
		}
		for (int l513 = 0; (l513 < 2); l513 = (l513 + 1)) {
			fRec411[l513] = 0.0f;
		}
		for (int l514 = 0; (l514 < 2); l514 = (l514 + 1)) {
			fRec414[l514] = 0.0f;
		}
		for (int l515 = 0; (l515 < 2); l515 = (l515 + 1)) {
			fRec413[l515] = 0.0f;
		}
		for (int l516 = 0; (l516 < 2); l516 = (l516 + 1)) {
			iVec104[l516] = 0;
		}
		for (int l517 = 0; (l517 < 2); l517 = (l517 + 1)) {
			iRec418[l517] = 0;
		}
		for (int l518 = 0; (l518 < 2); l518 = (l518 + 1)) {
			iRec417[l518] = 0;
		}
		for (int l519 = 0; (l519 < 2); l519 = (l519 + 1)) {
			iRec416[l519] = 0;
		}
		for (int l520 = 0; (l520 < 2); l520 = (l520 + 1)) {
			iRec415[l520] = 0;
		}
		for (int l521 = 0; (l521 < 2); l521 = (l521 + 1)) {
			iVec105[l521] = 0;
		}
		for (int l522 = 0; (l522 < 2); l522 = (l522 + 1)) {
			iRec420[l522] = 0;
		}
		for (int l523 = 0; (l523 < 2); l523 = (l523 + 1)) {
			fRec419[l523] = 0.0f;
		}
		for (int l524 = 0; (l524 < 2); l524 = (l524 + 1)) {
			fRec422[l524] = 0.0f;
		}
		for (int l525 = 0; (l525 < 2); l525 = (l525 + 1)) {
			fRec421[l525] = 0.0f;
		}
		for (int l526 = 0; (l526 < 2); l526 = (l526 + 1)) {
			iVec106[l526] = 0;
		}
		for (int l527 = 0; (l527 < 2); l527 = (l527 + 1)) {
			iRec426[l527] = 0;
		}
		for (int l528 = 0; (l528 < 2); l528 = (l528 + 1)) {
			iRec425[l528] = 0;
		}
		for (int l529 = 0; (l529 < 2); l529 = (l529 + 1)) {
			iRec424[l529] = 0;
		}
		for (int l530 = 0; (l530 < 2); l530 = (l530 + 1)) {
			iRec423[l530] = 0;
		}
		for (int l531 = 0; (l531 < 2); l531 = (l531 + 1)) {
			iVec107[l531] = 0;
		}
		for (int l532 = 0; (l532 < 2); l532 = (l532 + 1)) {
			iRec428[l532] = 0;
		}
		for (int l533 = 0; (l533 < 2); l533 = (l533 + 1)) {
			fRec427[l533] = 0.0f;
		}
		for (int l534 = 0; (l534 < 2); l534 = (l534 + 1)) {
			fRec430[l534] = 0.0f;
		}
		for (int l535 = 0; (l535 < 2); l535 = (l535 + 1)) {
			fRec429[l535] = 0.0f;
		}
		for (int l536 = 0; (l536 < 2); l536 = (l536 + 1)) {
			iVec108[l536] = 0;
		}
		for (int l537 = 0; (l537 < 2); l537 = (l537 + 1)) {
			iRec434[l537] = 0;
		}
		for (int l538 = 0; (l538 < 2); l538 = (l538 + 1)) {
			iRec433[l538] = 0;
		}
		for (int l539 = 0; (l539 < 2); l539 = (l539 + 1)) {
			iRec432[l539] = 0;
		}
		for (int l540 = 0; (l540 < 2); l540 = (l540 + 1)) {
			iRec431[l540] = 0;
		}
		for (int l541 = 0; (l541 < 2); l541 = (l541 + 1)) {
			iVec109[l541] = 0;
		}
		for (int l542 = 0; (l542 < 2); l542 = (l542 + 1)) {
			iRec436[l542] = 0;
		}
		for (int l543 = 0; (l543 < 2); l543 = (l543 + 1)) {
			fRec435[l543] = 0.0f;
		}
		for (int l544 = 0; (l544 < 2); l544 = (l544 + 1)) {
			fRec438[l544] = 0.0f;
		}
		for (int l545 = 0; (l545 < 2); l545 = (l545 + 1)) {
			fRec437[l545] = 0.0f;
		}
		for (int l546 = 0; (l546 < 2); l546 = (l546 + 1)) {
			iVec110[l546] = 0;
		}
		for (int l547 = 0; (l547 < 2); l547 = (l547 + 1)) {
			iRec442[l547] = 0;
		}
		for (int l548 = 0; (l548 < 2); l548 = (l548 + 1)) {
			iRec441[l548] = 0;
		}
		for (int l549 = 0; (l549 < 2); l549 = (l549 + 1)) {
			iRec440[l549] = 0;
		}
		for (int l550 = 0; (l550 < 2); l550 = (l550 + 1)) {
			iRec439[l550] = 0;
		}
		for (int l551 = 0; (l551 < 2); l551 = (l551 + 1)) {
			iVec111[l551] = 0;
		}
		for (int l552 = 0; (l552 < 2); l552 = (l552 + 1)) {
			iRec444[l552] = 0;
		}
		for (int l553 = 0; (l553 < 2); l553 = (l553 + 1)) {
			fRec443[l553] = 0.0f;
		}
		for (int l554 = 0; (l554 < 2); l554 = (l554 + 1)) {
			fRec446[l554] = 0.0f;
		}
		for (int l555 = 0; (l555 < 2); l555 = (l555 + 1)) {
			fRec445[l555] = 0.0f;
		}
		for (int l556 = 0; (l556 < 2); l556 = (l556 + 1)) {
			iVec112[l556] = 0;
		}
		for (int l557 = 0; (l557 < 2); l557 = (l557 + 1)) {
			iRec450[l557] = 0;
		}
		for (int l558 = 0; (l558 < 2); l558 = (l558 + 1)) {
			iRec449[l558] = 0;
		}
		for (int l559 = 0; (l559 < 2); l559 = (l559 + 1)) {
			iRec448[l559] = 0;
		}
		for (int l560 = 0; (l560 < 2); l560 = (l560 + 1)) {
			iRec447[l560] = 0;
		}
		for (int l561 = 0; (l561 < 2); l561 = (l561 + 1)) {
			iVec113[l561] = 0;
		}
		for (int l562 = 0; (l562 < 2); l562 = (l562 + 1)) {
			iRec452[l562] = 0;
		}
		for (int l563 = 0; (l563 < 2); l563 = (l563 + 1)) {
			fRec451[l563] = 0.0f;
		}
		for (int l564 = 0; (l564 < 2); l564 = (l564 + 1)) {
			fRec454[l564] = 0.0f;
		}
		for (int l565 = 0; (l565 < 2); l565 = (l565 + 1)) {
			fRec453[l565] = 0.0f;
		}
		for (int l566 = 0; (l566 < 2); l566 = (l566 + 1)) {
			iVec114[l566] = 0;
		}
		for (int l567 = 0; (l567 < 2); l567 = (l567 + 1)) {
			iRec458[l567] = 0;
		}
		for (int l568 = 0; (l568 < 2); l568 = (l568 + 1)) {
			iRec457[l568] = 0;
		}
		for (int l569 = 0; (l569 < 2); l569 = (l569 + 1)) {
			iRec456[l569] = 0;
		}
		for (int l570 = 0; (l570 < 2); l570 = (l570 + 1)) {
			iRec455[l570] = 0;
		}
		for (int l571 = 0; (l571 < 2); l571 = (l571 + 1)) {
			iVec115[l571] = 0;
		}
		for (int l572 = 0; (l572 < 2); l572 = (l572 + 1)) {
			iRec460[l572] = 0;
		}
		for (int l573 = 0; (l573 < 2); l573 = (l573 + 1)) {
			fRec459[l573] = 0.0f;
		}
		for (int l574 = 0; (l574 < 2); l574 = (l574 + 1)) {
			fRec462[l574] = 0.0f;
		}
		for (int l575 = 0; (l575 < 2); l575 = (l575 + 1)) {
			fRec461[l575] = 0.0f;
		}
		for (int l576 = 0; (l576 < 2); l576 = (l576 + 1)) {
			iVec116[l576] = 0;
		}
		for (int l577 = 0; (l577 < 2); l577 = (l577 + 1)) {
			iRec466[l577] = 0;
		}
		for (int l578 = 0; (l578 < 2); l578 = (l578 + 1)) {
			iRec465[l578] = 0;
		}
		for (int l579 = 0; (l579 < 2); l579 = (l579 + 1)) {
			iRec464[l579] = 0;
		}
		for (int l580 = 0; (l580 < 2); l580 = (l580 + 1)) {
			iRec463[l580] = 0;
		}
		for (int l581 = 0; (l581 < 2); l581 = (l581 + 1)) {
			iVec117[l581] = 0;
		}
		for (int l582 = 0; (l582 < 2); l582 = (l582 + 1)) {
			iRec468[l582] = 0;
		}
		for (int l583 = 0; (l583 < 2); l583 = (l583 + 1)) {
			fRec467[l583] = 0.0f;
		}
		for (int l584 = 0; (l584 < 2); l584 = (l584 + 1)) {
			fRec470[l584] = 0.0f;
		}
		for (int l585 = 0; (l585 < 2); l585 = (l585 + 1)) {
			fRec469[l585] = 0.0f;
		}
		for (int l586 = 0; (l586 < 2); l586 = (l586 + 1)) {
			iVec118[l586] = 0;
		}
		for (int l587 = 0; (l587 < 2); l587 = (l587 + 1)) {
			iRec474[l587] = 0;
		}
		for (int l588 = 0; (l588 < 2); l588 = (l588 + 1)) {
			iRec473[l588] = 0;
		}
		for (int l589 = 0; (l589 < 2); l589 = (l589 + 1)) {
			iRec472[l589] = 0;
		}
		for (int l590 = 0; (l590 < 2); l590 = (l590 + 1)) {
			iRec471[l590] = 0;
		}
		for (int l591 = 0; (l591 < 2); l591 = (l591 + 1)) {
			iVec119[l591] = 0;
		}
		for (int l592 = 0; (l592 < 2); l592 = (l592 + 1)) {
			iRec476[l592] = 0;
		}
		for (int l593 = 0; (l593 < 2); l593 = (l593 + 1)) {
			fRec475[l593] = 0.0f;
		}
		for (int l594 = 0; (l594 < 2); l594 = (l594 + 1)) {
			fRec478[l594] = 0.0f;
		}
		for (int l595 = 0; (l595 < 2); l595 = (l595 + 1)) {
			fRec477[l595] = 0.0f;
		}
		for (int l596 = 0; (l596 < 2); l596 = (l596 + 1)) {
			iVec120[l596] = 0;
		}
		for (int l597 = 0; (l597 < 2); l597 = (l597 + 1)) {
			iRec482[l597] = 0;
		}
		for (int l598 = 0; (l598 < 2); l598 = (l598 + 1)) {
			iRec481[l598] = 0;
		}
		for (int l599 = 0; (l599 < 2); l599 = (l599 + 1)) {
			iRec480[l599] = 0;
		}
		for (int l600 = 0; (l600 < 2); l600 = (l600 + 1)) {
			iRec479[l600] = 0;
		}
		for (int l601 = 0; (l601 < 2); l601 = (l601 + 1)) {
			iVec121[l601] = 0;
		}
		for (int l602 = 0; (l602 < 2); l602 = (l602 + 1)) {
			iRec484[l602] = 0;
		}
		for (int l603 = 0; (l603 < 2); l603 = (l603 + 1)) {
			fRec483[l603] = 0.0f;
		}
		for (int l604 = 0; (l604 < 2); l604 = (l604 + 1)) {
			fRec486[l604] = 0.0f;
		}
		for (int l605 = 0; (l605 < 2); l605 = (l605 + 1)) {
			fRec485[l605] = 0.0f;
		}
		for (int l606 = 0; (l606 < 2); l606 = (l606 + 1)) {
			iVec122[l606] = 0;
		}
		for (int l607 = 0; (l607 < 2); l607 = (l607 + 1)) {
			iRec490[l607] = 0;
		}
		for (int l608 = 0; (l608 < 2); l608 = (l608 + 1)) {
			iRec489[l608] = 0;
		}
		for (int l609 = 0; (l609 < 2); l609 = (l609 + 1)) {
			iRec488[l609] = 0;
		}
		for (int l610 = 0; (l610 < 2); l610 = (l610 + 1)) {
			iRec487[l610] = 0;
		}
		for (int l611 = 0; (l611 < 2); l611 = (l611 + 1)) {
			iVec123[l611] = 0;
		}
		for (int l612 = 0; (l612 < 2); l612 = (l612 + 1)) {
			iRec492[l612] = 0;
		}
		for (int l613 = 0; (l613 < 2); l613 = (l613 + 1)) {
			fRec491[l613] = 0.0f;
		}
		for (int l614 = 0; (l614 < 2); l614 = (l614 + 1)) {
			fRec494[l614] = 0.0f;
		}
		for (int l615 = 0; (l615 < 2); l615 = (l615 + 1)) {
			fRec493[l615] = 0.0f;
		}
		for (int l616 = 0; (l616 < 2); l616 = (l616 + 1)) {
			iVec124[l616] = 0;
		}
		for (int l617 = 0; (l617 < 2); l617 = (l617 + 1)) {
			iRec498[l617] = 0;
		}
		for (int l618 = 0; (l618 < 2); l618 = (l618 + 1)) {
			iRec497[l618] = 0;
		}
		for (int l619 = 0; (l619 < 2); l619 = (l619 + 1)) {
			iRec496[l619] = 0;
		}
		for (int l620 = 0; (l620 < 2); l620 = (l620 + 1)) {
			iRec495[l620] = 0;
		}
		for (int l621 = 0; (l621 < 2); l621 = (l621 + 1)) {
			iVec125[l621] = 0;
		}
		for (int l622 = 0; (l622 < 2); l622 = (l622 + 1)) {
			iRec500[l622] = 0;
		}
		for (int l623 = 0; (l623 < 2); l623 = (l623 + 1)) {
			fRec499[l623] = 0.0f;
		}
		for (int l624 = 0; (l624 < 2); l624 = (l624 + 1)) {
			fRec502[l624] = 0.0f;
		}
		for (int l625 = 0; (l625 < 2); l625 = (l625 + 1)) {
			fRec501[l625] = 0.0f;
		}
		for (int l626 = 0; (l626 < 2); l626 = (l626 + 1)) {
			iVec126[l626] = 0;
		}
		for (int l627 = 0; (l627 < 2); l627 = (l627 + 1)) {
			iRec506[l627] = 0;
		}
		for (int l628 = 0; (l628 < 2); l628 = (l628 + 1)) {
			iRec505[l628] = 0;
		}
		for (int l629 = 0; (l629 < 2); l629 = (l629 + 1)) {
			iRec504[l629] = 0;
		}
		for (int l630 = 0; (l630 < 2); l630 = (l630 + 1)) {
			iRec503[l630] = 0;
		}
		for (int l631 = 0; (l631 < 2); l631 = (l631 + 1)) {
			iVec127[l631] = 0;
		}
		for (int l632 = 0; (l632 < 2); l632 = (l632 + 1)) {
			iRec508[l632] = 0;
		}
		for (int l633 = 0; (l633 < 2); l633 = (l633 + 1)) {
			fRec507[l633] = 0.0f;
		}
		for (int l634 = 0; (l634 < 2); l634 = (l634 + 1)) {
			fRec510[l634] = 0.0f;
		}
		for (int l635 = 0; (l635 < 2); l635 = (l635 + 1)) {
			fRec509[l635] = 0.0f;
		}
		for (int l636 = 0; (l636 < 2); l636 = (l636 + 1)) {
			iVec128[l636] = 0;
		}
		for (int l637 = 0; (l637 < 2); l637 = (l637 + 1)) {
			iRec514[l637] = 0;
		}
		for (int l638 = 0; (l638 < 2); l638 = (l638 + 1)) {
			iRec513[l638] = 0;
		}
		for (int l639 = 0; (l639 < 2); l639 = (l639 + 1)) {
			iRec512[l639] = 0;
		}
		for (int l640 = 0; (l640 < 2); l640 = (l640 + 1)) {
			iRec511[l640] = 0;
		}
		for (int l641 = 0; (l641 < 2); l641 = (l641 + 1)) {
			iVec129[l641] = 0;
		}
		for (int l642 = 0; (l642 < 2); l642 = (l642 + 1)) {
			iRec516[l642] = 0;
		}
		for (int l643 = 0; (l643 < 2); l643 = (l643 + 1)) {
			fRec515[l643] = 0.0f;
		}
		for (int l644 = 0; (l644 < 2); l644 = (l644 + 1)) {
			fRec518[l644] = 0.0f;
		}
		for (int l645 = 0; (l645 < 2); l645 = (l645 + 1)) {
			fRec517[l645] = 0.0f;
		}
		for (int l646 = 0; (l646 < 2); l646 = (l646 + 1)) {
			iVec130[l646] = 0;
		}
		for (int l647 = 0; (l647 < 2); l647 = (l647 + 1)) {
			iRec522[l647] = 0;
		}
		for (int l648 = 0; (l648 < 2); l648 = (l648 + 1)) {
			iRec521[l648] = 0;
		}
		for (int l649 = 0; (l649 < 2); l649 = (l649 + 1)) {
			iRec520[l649] = 0;
		}
		for (int l650 = 0; (l650 < 2); l650 = (l650 + 1)) {
			iRec519[l650] = 0;
		}
		for (int l651 = 0; (l651 < 2); l651 = (l651 + 1)) {
			iVec131[l651] = 0;
		}
		for (int l652 = 0; (l652 < 2); l652 = (l652 + 1)) {
			iRec524[l652] = 0;
		}
		for (int l653 = 0; (l653 < 2); l653 = (l653 + 1)) {
			fRec523[l653] = 0.0f;
		}
		for (int l654 = 0; (l654 < 2); l654 = (l654 + 1)) {
			fRec526[l654] = 0.0f;
		}
		for (int l655 = 0; (l655 < 2); l655 = (l655 + 1)) {
			fRec525[l655] = 0.0f;
		}
		for (int l656 = 0; (l656 < 2); l656 = (l656 + 1)) {
			iVec132[l656] = 0;
		}
		for (int l657 = 0; (l657 < 2); l657 = (l657 + 1)) {
			iRec530[l657] = 0;
		}
		for (int l658 = 0; (l658 < 2); l658 = (l658 + 1)) {
			iRec529[l658] = 0;
		}
		for (int l659 = 0; (l659 < 2); l659 = (l659 + 1)) {
			iRec528[l659] = 0;
		}
		for (int l660 = 0; (l660 < 2); l660 = (l660 + 1)) {
			iRec527[l660] = 0;
		}
		for (int l661 = 0; (l661 < 2); l661 = (l661 + 1)) {
			iVec133[l661] = 0;
		}
		for (int l662 = 0; (l662 < 2); l662 = (l662 + 1)) {
			iRec532[l662] = 0;
		}
		for (int l663 = 0; (l663 < 2); l663 = (l663 + 1)) {
			fRec531[l663] = 0.0f;
		}
		for (int l664 = 0; (l664 < 2); l664 = (l664 + 1)) {
			fRec534[l664] = 0.0f;
		}
		for (int l665 = 0; (l665 < 2); l665 = (l665 + 1)) {
			fRec533[l665] = 0.0f;
		}
		for (int l666 = 0; (l666 < 2); l666 = (l666 + 1)) {
			iVec134[l666] = 0;
		}
		for (int l667 = 0; (l667 < 2); l667 = (l667 + 1)) {
			iRec538[l667] = 0;
		}
		for (int l668 = 0; (l668 < 2); l668 = (l668 + 1)) {
			iRec537[l668] = 0;
		}
		for (int l669 = 0; (l669 < 2); l669 = (l669 + 1)) {
			iRec536[l669] = 0;
		}
		for (int l670 = 0; (l670 < 2); l670 = (l670 + 1)) {
			iRec535[l670] = 0;
		}
		for (int l671 = 0; (l671 < 2); l671 = (l671 + 1)) {
			iVec135[l671] = 0;
		}
		for (int l672 = 0; (l672 < 2); l672 = (l672 + 1)) {
			iRec540[l672] = 0;
		}
		for (int l673 = 0; (l673 < 2); l673 = (l673 + 1)) {
			fRec539[l673] = 0.0f;
		}
		for (int l674 = 0; (l674 < 2); l674 = (l674 + 1)) {
			fRec542[l674] = 0.0f;
		}
		for (int l675 = 0; (l675 < 2); l675 = (l675 + 1)) {
			fRec541[l675] = 0.0f;
		}
		for (int l676 = 0; (l676 < 2); l676 = (l676 + 1)) {
			iVec136[l676] = 0;
		}
		for (int l677 = 0; (l677 < 2); l677 = (l677 + 1)) {
			iRec546[l677] = 0;
		}
		for (int l678 = 0; (l678 < 2); l678 = (l678 + 1)) {
			iRec545[l678] = 0;
		}
		for (int l679 = 0; (l679 < 2); l679 = (l679 + 1)) {
			iRec544[l679] = 0;
		}
		for (int l680 = 0; (l680 < 2); l680 = (l680 + 1)) {
			iRec543[l680] = 0;
		}
		for (int l681 = 0; (l681 < 2); l681 = (l681 + 1)) {
			iVec137[l681] = 0;
		}
		for (int l682 = 0; (l682 < 2); l682 = (l682 + 1)) {
			iRec548[l682] = 0;
		}
		for (int l683 = 0; (l683 < 2); l683 = (l683 + 1)) {
			fRec547[l683] = 0.0f;
		}
		for (int l684 = 0; (l684 < 2); l684 = (l684 + 1)) {
			fRec550[l684] = 0.0f;
		}
		for (int l685 = 0; (l685 < 2); l685 = (l685 + 1)) {
			fRec549[l685] = 0.0f;
		}
		for (int l686 = 0; (l686 < 2); l686 = (l686 + 1)) {
			iVec138[l686] = 0;
		}
		for (int l687 = 0; (l687 < 2); l687 = (l687 + 1)) {
			iRec554[l687] = 0;
		}
		for (int l688 = 0; (l688 < 2); l688 = (l688 + 1)) {
			iRec553[l688] = 0;
		}
		for (int l689 = 0; (l689 < 2); l689 = (l689 + 1)) {
			iRec552[l689] = 0;
		}
		for (int l690 = 0; (l690 < 2); l690 = (l690 + 1)) {
			iRec551[l690] = 0;
		}
		for (int l691 = 0; (l691 < 2); l691 = (l691 + 1)) {
			iVec139[l691] = 0;
		}
		for (int l692 = 0; (l692 < 2); l692 = (l692 + 1)) {
			iRec556[l692] = 0;
		}
		for (int l693 = 0; (l693 < 2); l693 = (l693 + 1)) {
			fRec555[l693] = 0.0f;
		}
		for (int l694 = 0; (l694 < 2); l694 = (l694 + 1)) {
			fRec558[l694] = 0.0f;
		}
		for (int l695 = 0; (l695 < 2); l695 = (l695 + 1)) {
			fRec557[l695] = 0.0f;
		}
		for (int l696 = 0; (l696 < 2); l696 = (l696 + 1)) {
			iVec140[l696] = 0;
		}
		for (int l697 = 0; (l697 < 2); l697 = (l697 + 1)) {
			iRec562[l697] = 0;
		}
		for (int l698 = 0; (l698 < 2); l698 = (l698 + 1)) {
			iRec561[l698] = 0;
		}
		for (int l699 = 0; (l699 < 2); l699 = (l699 + 1)) {
			iRec560[l699] = 0;
		}
		for (int l700 = 0; (l700 < 2); l700 = (l700 + 1)) {
			iRec559[l700] = 0;
		}
		for (int l701 = 0; (l701 < 2); l701 = (l701 + 1)) {
			iVec141[l701] = 0;
		}
		for (int l702 = 0; (l702 < 2); l702 = (l702 + 1)) {
			iRec564[l702] = 0;
		}
		for (int l703 = 0; (l703 < 2); l703 = (l703 + 1)) {
			fRec563[l703] = 0.0f;
		}
		for (int l704 = 0; (l704 < 2); l704 = (l704 + 1)) {
			fRec566[l704] = 0.0f;
		}
		for (int l705 = 0; (l705 < 2); l705 = (l705 + 1)) {
			fRec565[l705] = 0.0f;
		}
		for (int l706 = 0; (l706 < 2); l706 = (l706 + 1)) {
			iVec142[l706] = 0;
		}
		for (int l707 = 0; (l707 < 2); l707 = (l707 + 1)) {
			iRec570[l707] = 0;
		}
		for (int l708 = 0; (l708 < 2); l708 = (l708 + 1)) {
			iRec569[l708] = 0;
		}
		for (int l709 = 0; (l709 < 2); l709 = (l709 + 1)) {
			iRec568[l709] = 0;
		}
		for (int l710 = 0; (l710 < 2); l710 = (l710 + 1)) {
			iRec567[l710] = 0;
		}
		for (int l711 = 0; (l711 < 2); l711 = (l711 + 1)) {
			iVec143[l711] = 0;
		}
		for (int l712 = 0; (l712 < 2); l712 = (l712 + 1)) {
			iRec572[l712] = 0;
		}
		for (int l713 = 0; (l713 < 2); l713 = (l713 + 1)) {
			fRec571[l713] = 0.0f;
		}
		for (int l714 = 0; (l714 < 2); l714 = (l714 + 1)) {
			fRec574[l714] = 0.0f;
		}
		for (int l715 = 0; (l715 < 2); l715 = (l715 + 1)) {
			fRec573[l715] = 0.0f;
		}
		for (int l716 = 0; (l716 < 2); l716 = (l716 + 1)) {
			iVec144[l716] = 0;
		}
		for (int l717 = 0; (l717 < 2); l717 = (l717 + 1)) {
			iRec578[l717] = 0;
		}
		for (int l718 = 0; (l718 < 2); l718 = (l718 + 1)) {
			iRec577[l718] = 0;
		}
		for (int l719 = 0; (l719 < 2); l719 = (l719 + 1)) {
			iRec576[l719] = 0;
		}
		for (int l720 = 0; (l720 < 2); l720 = (l720 + 1)) {
			iRec575[l720] = 0;
		}
		for (int l721 = 0; (l721 < 2); l721 = (l721 + 1)) {
			iVec145[l721] = 0;
		}
		for (int l722 = 0; (l722 < 2); l722 = (l722 + 1)) {
			iRec580[l722] = 0;
		}
		for (int l723 = 0; (l723 < 2); l723 = (l723 + 1)) {
			fRec579[l723] = 0.0f;
		}
		for (int l724 = 0; (l724 < 2); l724 = (l724 + 1)) {
			fRec582[l724] = 0.0f;
		}
		for (int l725 = 0; (l725 < 2); l725 = (l725 + 1)) {
			fRec581[l725] = 0.0f;
		}
		for (int l726 = 0; (l726 < 2); l726 = (l726 + 1)) {
			iVec146[l726] = 0;
		}
		for (int l727 = 0; (l727 < 2); l727 = (l727 + 1)) {
			iRec586[l727] = 0;
		}
		for (int l728 = 0; (l728 < 2); l728 = (l728 + 1)) {
			iRec585[l728] = 0;
		}
		for (int l729 = 0; (l729 < 2); l729 = (l729 + 1)) {
			iRec584[l729] = 0;
		}
		for (int l730 = 0; (l730 < 2); l730 = (l730 + 1)) {
			iRec583[l730] = 0;
		}
		for (int l731 = 0; (l731 < 2); l731 = (l731 + 1)) {
			iVec147[l731] = 0;
		}
		for (int l732 = 0; (l732 < 2); l732 = (l732 + 1)) {
			iRec588[l732] = 0;
		}
		for (int l733 = 0; (l733 < 2); l733 = (l733 + 1)) {
			fRec587[l733] = 0.0f;
		}
		for (int l734 = 0; (l734 < 2); l734 = (l734 + 1)) {
			fRec590[l734] = 0.0f;
		}
		for (int l735 = 0; (l735 < 2); l735 = (l735 + 1)) {
			fRec589[l735] = 0.0f;
		}
		for (int l736 = 0; (l736 < 2); l736 = (l736 + 1)) {
			iVec148[l736] = 0;
		}
		for (int l737 = 0; (l737 < 2); l737 = (l737 + 1)) {
			iRec594[l737] = 0;
		}
		for (int l738 = 0; (l738 < 2); l738 = (l738 + 1)) {
			iRec593[l738] = 0;
		}
		for (int l739 = 0; (l739 < 2); l739 = (l739 + 1)) {
			iRec592[l739] = 0;
		}
		for (int l740 = 0; (l740 < 2); l740 = (l740 + 1)) {
			iRec591[l740] = 0;
		}
		for (int l741 = 0; (l741 < 2); l741 = (l741 + 1)) {
			iVec149[l741] = 0;
		}
		for (int l742 = 0; (l742 < 2); l742 = (l742 + 1)) {
			iRec596[l742] = 0;
		}
		for (int l743 = 0; (l743 < 2); l743 = (l743 + 1)) {
			fRec595[l743] = 0.0f;
		}
		for (int l744 = 0; (l744 < 2); l744 = (l744 + 1)) {
			fRec598[l744] = 0.0f;
		}
		for (int l745 = 0; (l745 < 2); l745 = (l745 + 1)) {
			fRec597[l745] = 0.0f;
		}
		for (int l746 = 0; (l746 < 2); l746 = (l746 + 1)) {
			iVec150[l746] = 0;
		}
		for (int l747 = 0; (l747 < 2); l747 = (l747 + 1)) {
			iRec602[l747] = 0;
		}
		for (int l748 = 0; (l748 < 2); l748 = (l748 + 1)) {
			iRec601[l748] = 0;
		}
		for (int l749 = 0; (l749 < 2); l749 = (l749 + 1)) {
			iRec600[l749] = 0;
		}
		for (int l750 = 0; (l750 < 2); l750 = (l750 + 1)) {
			iRec599[l750] = 0;
		}
		for (int l751 = 0; (l751 < 2); l751 = (l751 + 1)) {
			iVec151[l751] = 0;
		}
		for (int l752 = 0; (l752 < 2); l752 = (l752 + 1)) {
			iRec604[l752] = 0;
		}
		for (int l753 = 0; (l753 < 2); l753 = (l753 + 1)) {
			fRec603[l753] = 0.0f;
		}
		for (int l754 = 0; (l754 < 2); l754 = (l754 + 1)) {
			fRec606[l754] = 0.0f;
		}
		for (int l755 = 0; (l755 < 2); l755 = (l755 + 1)) {
			fRec605[l755] = 0.0f;
		}
		for (int l756 = 0; (l756 < 2); l756 = (l756 + 1)) {
			iVec152[l756] = 0;
		}
		for (int l757 = 0; (l757 < 2); l757 = (l757 + 1)) {
			iRec610[l757] = 0;
		}
		for (int l758 = 0; (l758 < 2); l758 = (l758 + 1)) {
			iRec609[l758] = 0;
		}
		for (int l759 = 0; (l759 < 2); l759 = (l759 + 1)) {
			iRec608[l759] = 0;
		}
		for (int l760 = 0; (l760 < 2); l760 = (l760 + 1)) {
			iRec607[l760] = 0;
		}
		for (int l761 = 0; (l761 < 2); l761 = (l761 + 1)) {
			iVec153[l761] = 0;
		}
		for (int l762 = 0; (l762 < 2); l762 = (l762 + 1)) {
			iRec612[l762] = 0;
		}
		for (int l763 = 0; (l763 < 2); l763 = (l763 + 1)) {
			fRec611[l763] = 0.0f;
		}
		for (int l764 = 0; (l764 < 2); l764 = (l764 + 1)) {
			fRec614[l764] = 0.0f;
		}
		for (int l765 = 0; (l765 < 2); l765 = (l765 + 1)) {
			fRec613[l765] = 0.0f;
		}
		for (int l766 = 0; (l766 < 2); l766 = (l766 + 1)) {
			iVec154[l766] = 0;
		}
		for (int l767 = 0; (l767 < 2); l767 = (l767 + 1)) {
			iRec618[l767] = 0;
		}
		for (int l768 = 0; (l768 < 2); l768 = (l768 + 1)) {
			iRec617[l768] = 0;
		}
		for (int l769 = 0; (l769 < 2); l769 = (l769 + 1)) {
			iRec616[l769] = 0;
		}
		for (int l770 = 0; (l770 < 2); l770 = (l770 + 1)) {
			iRec615[l770] = 0;
		}
		for (int l771 = 0; (l771 < 2); l771 = (l771 + 1)) {
			iVec155[l771] = 0;
		}
		for (int l772 = 0; (l772 < 2); l772 = (l772 + 1)) {
			iRec620[l772] = 0;
		}
		for (int l773 = 0; (l773 < 2); l773 = (l773 + 1)) {
			fRec619[l773] = 0.0f;
		}
		for (int l774 = 0; (l774 < 2); l774 = (l774 + 1)) {
			fRec622[l774] = 0.0f;
		}
		for (int l775 = 0; (l775 < 2); l775 = (l775 + 1)) {
			fRec621[l775] = 0.0f;
		}
		for (int l776 = 0; (l776 < 2); l776 = (l776 + 1)) {
			iVec156[l776] = 0;
		}
		for (int l777 = 0; (l777 < 2); l777 = (l777 + 1)) {
			iRec626[l777] = 0;
		}
		for (int l778 = 0; (l778 < 2); l778 = (l778 + 1)) {
			iRec625[l778] = 0;
		}
		for (int l779 = 0; (l779 < 2); l779 = (l779 + 1)) {
			iRec624[l779] = 0;
		}
		for (int l780 = 0; (l780 < 2); l780 = (l780 + 1)) {
			iRec623[l780] = 0;
		}
		for (int l781 = 0; (l781 < 2); l781 = (l781 + 1)) {
			iVec157[l781] = 0;
		}
		for (int l782 = 0; (l782 < 2); l782 = (l782 + 1)) {
			iRec628[l782] = 0;
		}
		for (int l783 = 0; (l783 < 2); l783 = (l783 + 1)) {
			fRec627[l783] = 0.0f;
		}
		for (int l784 = 0; (l784 < 2); l784 = (l784 + 1)) {
			fRec630[l784] = 0.0f;
		}
		for (int l785 = 0; (l785 < 2); l785 = (l785 + 1)) {
			fRec629[l785] = 0.0f;
		}
		for (int l786 = 0; (l786 < 2); l786 = (l786 + 1)) {
			iVec158[l786] = 0;
		}
		for (int l787 = 0; (l787 < 2); l787 = (l787 + 1)) {
			iRec634[l787] = 0;
		}
		for (int l788 = 0; (l788 < 2); l788 = (l788 + 1)) {
			iRec633[l788] = 0;
		}
		for (int l789 = 0; (l789 < 2); l789 = (l789 + 1)) {
			iRec632[l789] = 0;
		}
		for (int l790 = 0; (l790 < 2); l790 = (l790 + 1)) {
			iRec631[l790] = 0;
		}
		for (int l791 = 0; (l791 < 2); l791 = (l791 + 1)) {
			iVec159[l791] = 0;
		}
		for (int l792 = 0; (l792 < 2); l792 = (l792 + 1)) {
			iRec636[l792] = 0;
		}
		for (int l793 = 0; (l793 < 2); l793 = (l793 + 1)) {
			fRec635[l793] = 0.0f;
		}
		for (int l794 = 0; (l794 < 2); l794 = (l794 + 1)) {
			fRec638[l794] = 0.0f;
		}
		for (int l795 = 0; (l795 < 2); l795 = (l795 + 1)) {
			fRec637[l795] = 0.0f;
		}
		for (int l796 = 0; (l796 < 2); l796 = (l796 + 1)) {
			iVec160[l796] = 0;
		}
		for (int l797 = 0; (l797 < 2); l797 = (l797 + 1)) {
			iRec642[l797] = 0;
		}
		for (int l798 = 0; (l798 < 2); l798 = (l798 + 1)) {
			iRec641[l798] = 0;
		}
		for (int l799 = 0; (l799 < 2); l799 = (l799 + 1)) {
			iRec640[l799] = 0;
		}
		for (int l800 = 0; (l800 < 2); l800 = (l800 + 1)) {
			iRec639[l800] = 0;
		}
		for (int l801 = 0; (l801 < 2); l801 = (l801 + 1)) {
			iVec161[l801] = 0;
		}
		for (int l802 = 0; (l802 < 2); l802 = (l802 + 1)) {
			iRec644[l802] = 0;
		}
		for (int l803 = 0; (l803 < 2); l803 = (l803 + 1)) {
			fRec643[l803] = 0.0f;
		}
		for (int l804 = 0; (l804 < 2); l804 = (l804 + 1)) {
			fRec646[l804] = 0.0f;
		}
		for (int l805 = 0; (l805 < 2); l805 = (l805 + 1)) {
			fRec645[l805] = 0.0f;
		}
		for (int l806 = 0; (l806 < 2); l806 = (l806 + 1)) {
			iVec162[l806] = 0;
		}
		for (int l807 = 0; (l807 < 2); l807 = (l807 + 1)) {
			iRec650[l807] = 0;
		}
		for (int l808 = 0; (l808 < 2); l808 = (l808 + 1)) {
			iRec649[l808] = 0;
		}
		for (int l809 = 0; (l809 < 2); l809 = (l809 + 1)) {
			iRec648[l809] = 0;
		}
		for (int l810 = 0; (l810 < 2); l810 = (l810 + 1)) {
			iRec647[l810] = 0;
		}
		for (int l811 = 0; (l811 < 2); l811 = (l811 + 1)) {
			iVec163[l811] = 0;
		}
		for (int l812 = 0; (l812 < 2); l812 = (l812 + 1)) {
			iRec652[l812] = 0;
		}
		for (int l813 = 0; (l813 < 2); l813 = (l813 + 1)) {
			fRec651[l813] = 0.0f;
		}
		for (int l814 = 0; (l814 < 2); l814 = (l814 + 1)) {
			fRec654[l814] = 0.0f;
		}
		for (int l815 = 0; (l815 < 2); l815 = (l815 + 1)) {
			fRec653[l815] = 0.0f;
		}
		for (int l816 = 0; (l816 < 2); l816 = (l816 + 1)) {
			fRec0[l816] = 0.0f;
		}
		for (int l817 = 0; (l817 < 2); l817 = (l817 + 1)) {
			fRec655[l817] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("PDB_Realtime_Granulator");
		ui_interface->declare(&fHslider2, "0", "");
		ui_interface->addHorizontalSlider("Rec Grain", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(80.0f), FAUSTFLOAT(0.100000001f));
		ui_interface->declare(&fHbargraph0, "2", "");
		ui_interface->declare(&fHbargraph0, "style", "numerical");
		ui_interface->addHorizontalBargraph("Rec Grain Instance:", &fHbargraph0, FAUSTFLOAT(1.0f), FAUSTFLOAT(80.0f));
		ui_interface->declare(&fHslider1, "3", "");
		ui_interface->addHorizontalSlider("Grains Amp In", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider7, "4", "");
		ui_interface->addHorizontalSlider("Grains Amp Out", &fHslider7, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider5, "5", "");
		ui_interface->addHorizontalSlider("Grains Window", &fHslider5, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(100.0f), FAUSTFLOAT(0.100000001f));
		ui_interface->declare(&fHslider0, "5", "");
		ui_interface->addHorizontalSlider("Rec Feedback", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider6, "6", "");
		ui_interface->addHorizontalSlider("Panning Speed", &fHslider6, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fHslider3, "7", "");
		ui_interface->addHorizontalSlider("Grains Freq+", &fHslider3, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(100.0f), FAUSTFLOAT(0.100000001f));
		ui_interface->declare(&fHslider4, "8", "");
		ui_interface->addHorizontalSlider("Grains Freq/", &fHslider4, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(100.0f), FAUSTFLOAT(0.100000001f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (fConst1 * float(fHslider0));
		float fSlow1 = (fConst1 * float(fHslider1));
		float fSlow2 = (fConst3 * float(int(float(fHslider2))));
		float fSlow3 = (fConst1 * float(fHslider3));
		float fSlow4 = (fConst1 * float(fHslider4));
		float fSlow5 = (fConst1 * float(fHslider5));
		float fSlow6 = (fConst1 * float(fHslider6));
		float fSlow7 = (fConst1 * float(fHslider7));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			fRec3[0] = (fSlow0 + (fConst2 * fRec3[1]));
			fRec5[0] = (fSlow1 + (fConst2 * fRec5[1]));
			float fTemp0 = (float(input0[i0]) * fRec5[0]);
			fVec0[0] = (fTemp0 + fRec0[1]);
			fRec4[0] = ((fRec0[1] + (fTemp0 + (0.995000005f * fRec4[1]))) - fVec0[1]);
			float fTemp1 = std::max<float>(-1.0f, std::min<float>(1.0f, fRec4[0]));
			fRec12[0] = (fSlow2 + (fRec12[1] - std::floor((fSlow2 + fRec12[1]))));
			int iTemp2 = (ftbl1mydspSIG1[int((65536.0f * fRec12[0]))] > 0.0f);
			iVec2[0] = iTemp2;
			iRec10[0] = (iRec10[1] + std::max<int>(0, int((iTemp2 - iVec2[1]))));
			fHbargraph0 = FAUSTFLOAT(((iRec10[0] % 80) + 1));
			int iTemp3 = int(fHbargraph0);
			float fTemp4 = float((iTemp3 == 1));
			iVec3[0] = (fTemp4 < 0.5f);
			int iTemp5 = std::abs(((fTemp4 > 0.5f) * iVec3[1]));
			int iTemp6 = (iTemp5 >= iRec7[1]);
			int iTemp7 = (1 - (iTemp6 | iRec8[1]));
			iRec9[0] = ((iRec9[1] * iTemp7) + iTemp7);
			iRec8[0] = (float(iRec9[0]) >= fConst0);
			iRec7[0] = ((iRec8[0] | iTemp6) ? iTemp5 : iRec7[1]);
			iRec6[0] = (((iRec7[0] * iRec6[1]) + 1) % iConst4);
			ftbl0[(iRec6[0] + (2 * iRec7[0]))] = fTemp1;
			fRec15[0] = (fSlow3 + (fConst2 * fRec15[1]));
			fRec16[0] = (fSlow4 + (fConst2 * fRec16[1]));
			float fTemp8 = (fRec14[((IOTA - 1) & 262143)] + (fConst6 * (fRec15[0] / fRec16[0])));
			fRec14[(IOTA & 262143)] = (fTemp8 - float(int(fTemp8)));
			float fTemp9 = fRec14[((IOTA - iConst7) & 262143)];
			float fTemp10 = (1.0f - fTemp9);
			iVec4[0] = (fTemp10 < 0.5f);
			int iTemp11 = ((fTemp10 > 0.5f) * iVec4[1]);
			iRec17[0] = ((1103515245 * iRec17[1]) + 219979);
			float fTemp12 = float(iRec17[0]);
			fRec13[0] = ((fRec13[1] * float((1 - iTemp11))) + (0.5f * (((4.65661287e-10f * fTemp12) + 1.0f) * float(iTemp11))));
			fRec18[0] = (fSlow5 + (fConst2 * fRec18[1]));
			float fTemp13 = (ftbl0[int(((fConst5 * ((0.449999988f * (fRec13[0] + 1.0f)) + (0.100000001f * fTemp9))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp9)), fRec18[0]));
			fRec22[0] = (fSlow6 + (fConst2 * fRec22[1]));
			float fTemp14 = (fRec21[1] + (fConst3 * fRec22[0]));
			fRec21[0] = (fTemp14 - float(int(fTemp14)));
			int iTemp15 = ((fRec21[0] + -0.5f) > 0.0f);
			iVec5[0] = iTemp15;
			int iTemp16 = ((iTemp15 - iVec5[1]) > 0);
			float fTemp17 = float((1 - iTemp16));
			float fTemp18 = float(iTemp16);
			fRec20[0] = ((fRec20[1] * fTemp17) + (4.65661287e-10f * (fTemp12 * fTemp18)));
			float fTemp19 = (fRec19[1] + (fConst3 * float(((2 * (fRec20[0] > 0.0f)) + -1))));
			fRec19[0] = (fTemp19 - float(int(fTemp19)));
			float fTemp20 = float((fRec19[0] > 0.0f));
			float fTemp21 = (fRec19[0] * fTemp20);
			float fTemp22 = float((fRec19[0] < 0.0f));
			float fTemp23 = (fRec19[0] * fTemp22);
			float fTemp24 = ((fRec19[0] * ((fTemp20 * float((fTemp21 < 0.5f))) + (fTemp22 * float((fTemp23 > -0.5f))))) + ((float((fTemp21 > 0.5f)) * (1.0f - fTemp21)) + (float((fTemp23 < -0.5f)) * (-1.0f - fTemp23))));
			float fTemp25 = float((iTemp3 == 2));
			iVec6[0] = (fTemp25 < 0.5f);
			int iTemp26 = std::abs(((fTemp25 > 0.5f) * iVec6[1]));
			int iTemp27 = (iTemp26 >= iRec24[1]);
			int iTemp28 = (1 - (iTemp27 | iRec25[1]));
			iRec26[0] = ((iRec26[1] * iTemp28) + iTemp28);
			iRec25[0] = (float(iRec26[0]) >= fConst0);
			iRec24[0] = ((iRec25[0] | iTemp27) ? iTemp26 : iRec24[1]);
			iRec23[0] = (((iRec24[0] * iRec23[1]) + 1) % iConst4);
			ftbl2[(iRec23[0] + (2 * iRec24[0]))] = fTemp1;
			float fTemp29 = fRec14[((IOTA - iConst8) & 262143)];
			float fTemp30 = (1.0f - fTemp29);
			iVec7[0] = (fTemp30 < 0.5f);
			int iTemp31 = ((fTemp30 > 0.5f) * iVec7[1]);
			iRec28[0] = ((1103515245 * iRec28[1]) + 439958);
			float fTemp32 = float(iRec28[0]);
			fRec27[0] = ((fRec27[1] * float((1 - iTemp31))) + (0.5f * (((4.65661287e-10f * fTemp32) + 1.0f) * float(iTemp31))));
			float fTemp33 = (ftbl2[int(((fConst5 * ((0.449999988f * (fRec27[0] + 1.0f)) + (0.100000001f * fTemp29))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp29)), fRec18[0]));
			fRec30[0] = ((fTemp17 * fRec30[1]) + (4.65661287e-10f * (fTemp32 * fTemp18)));
			float fTemp34 = (fRec29[1] + (fConst3 * float(((2 * (fRec30[0] > 0.0f)) + -1))));
			fRec29[0] = (fTemp34 - float(int(fTemp34)));
			float fTemp35 = float((fRec29[0] > 0.0f));
			float fTemp36 = (fRec29[0] * fTemp35);
			float fTemp37 = float((fRec29[0] < 0.0f));
			float fTemp38 = (fRec29[0] * fTemp37);
			float fTemp39 = ((fRec29[0] * ((fTemp35 * float((fTemp36 < 0.5f))) + (fTemp37 * float((fTemp38 > -0.5f))))) + ((float((fTemp36 > 0.5f)) * (1.0f - fTemp36)) + (float((fTemp38 < -0.5f)) * (-1.0f - fTemp38))));
			float fTemp40 = float((iTemp3 == 3));
			iVec8[0] = (fTemp40 < 0.5f);
			int iTemp41 = std::abs(((fTemp40 > 0.5f) * iVec8[1]));
			int iTemp42 = (iTemp41 >= iRec32[1]);
			int iTemp43 = (1 - (iTemp42 | iRec33[1]));
			iRec34[0] = ((iRec34[1] * iTemp43) + iTemp43);
			iRec33[0] = (float(iRec34[0]) >= fConst0);
			iRec32[0] = ((iRec33[0] | iTemp42) ? iTemp41 : iRec32[1]);
			iRec31[0] = (((iRec32[0] * iRec31[1]) + 1) % iConst4);
			ftbl3[(iRec31[0] + (2 * iRec32[0]))] = fTemp1;
			float fTemp44 = fRec14[((IOTA - iConst9) & 262143)];
			float fTemp45 = (1.0f - fTemp44);
			iVec9[0] = (fTemp45 < 0.5f);
			int iTemp46 = ((fTemp45 > 0.5f) * iVec9[1]);
			iRec36[0] = ((1103515245 * iRec36[1]) + 659937);
			float fTemp47 = float(iRec36[0]);
			fRec35[0] = ((fRec35[1] * float((1 - iTemp46))) + (0.5f * (((4.65661287e-10f * fTemp47) + 1.0f) * float(iTemp46))));
			float fTemp48 = (ftbl3[int(((fConst5 * ((0.449999988f * (fRec35[0] + 1.0f)) + (0.100000001f * fTemp44))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp44)), fRec18[0]));
			fRec38[0] = ((fTemp17 * fRec38[1]) + (4.65661287e-10f * (fTemp47 * fTemp18)));
			float fTemp49 = (fRec37[1] + (fConst3 * float(((2 * (fRec38[0] > 0.0f)) + -1))));
			fRec37[0] = (fTemp49 - float(int(fTemp49)));
			float fTemp50 = float((fRec37[0] > 0.0f));
			float fTemp51 = (fRec37[0] * fTemp50);
			float fTemp52 = float((fRec37[0] < 0.0f));
			float fTemp53 = (fRec37[0] * fTemp52);
			float fTemp54 = ((fRec37[0] * ((fTemp50 * float((fTemp51 < 0.5f))) + (fTemp52 * float((fTemp53 > -0.5f))))) + ((float((fTemp51 > 0.5f)) * (1.0f - fTemp51)) + (float((fTemp53 < -0.5f)) * (-1.0f - fTemp53))));
			float fTemp55 = float((iTemp3 == 4));
			iVec10[0] = (fTemp55 < 0.5f);
			int iTemp56 = std::abs(((fTemp55 > 0.5f) * iVec10[1]));
			int iTemp57 = (iTemp56 >= iRec40[1]);
			int iTemp58 = (1 - (iTemp57 | iRec41[1]));
			iRec42[0] = ((iRec42[1] * iTemp58) + iTemp58);
			iRec41[0] = (float(iRec42[0]) >= fConst0);
			iRec40[0] = ((iRec41[0] | iTemp57) ? iTemp56 : iRec40[1]);
			iRec39[0] = (((iRec40[0] * iRec39[1]) + 1) % iConst4);
			ftbl4[(iRec39[0] + (2 * iRec40[0]))] = fTemp1;
			float fTemp59 = fRec14[((IOTA - iConst10) & 262143)];
			float fTemp60 = (1.0f - fTemp59);
			iVec11[0] = (fTemp60 < 0.5f);
			int iTemp61 = ((fTemp60 > 0.5f) * iVec11[1]);
			iRec44[0] = ((1103515245 * iRec44[1]) + 879916);
			float fTemp62 = float(iRec44[0]);
			fRec43[0] = ((fRec43[1] * float((1 - iTemp61))) + (0.5f * (((4.65661287e-10f * fTemp62) + 1.0f) * float(iTemp61))));
			float fTemp63 = (ftbl4[int(((fConst5 * ((0.449999988f * (fRec43[0] + 1.0f)) + (0.100000001f * fTemp59))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp59)), fRec18[0]));
			fRec46[0] = ((fTemp17 * fRec46[1]) + (4.65661287e-10f * (fTemp62 * fTemp18)));
			float fTemp64 = (fRec45[1] + (fConst3 * float(((2 * (fRec46[0] > 0.0f)) + -1))));
			fRec45[0] = (fTemp64 - float(int(fTemp64)));
			float fTemp65 = float((fRec45[0] > 0.0f));
			float fTemp66 = (fRec45[0] * fTemp65);
			float fTemp67 = float((fRec45[0] < 0.0f));
			float fTemp68 = (fRec45[0] * fTemp67);
			float fTemp69 = ((fRec45[0] * ((fTemp65 * float((fTemp66 < 0.5f))) + (fTemp67 * float((fTemp68 > -0.5f))))) + ((float((fTemp66 > 0.5f)) * (1.0f - fTemp66)) + (float((fTemp68 < -0.5f)) * (-1.0f - fTemp68))));
			float fTemp70 = float((iTemp3 == 5));
			iVec12[0] = (fTemp70 < 0.5f);
			int iTemp71 = std::abs(((fTemp70 > 0.5f) * iVec12[1]));
			int iTemp72 = (iTemp71 >= iRec48[1]);
			int iTemp73 = (1 - (iTemp72 | iRec49[1]));
			iRec50[0] = ((iRec50[1] * iTemp73) + iTemp73);
			iRec49[0] = (float(iRec50[0]) >= fConst0);
			iRec48[0] = ((iRec49[0] | iTemp72) ? iTemp71 : iRec48[1]);
			iRec47[0] = (((iRec48[0] * iRec47[1]) + 1) % iConst4);
			ftbl5[(iRec47[0] + (2 * iRec48[0]))] = fTemp1;
			float fTemp74 = fRec14[((IOTA - iConst11) & 262143)];
			float fTemp75 = (1.0f - fTemp74);
			iVec13[0] = (fTemp75 < 0.5f);
			int iTemp76 = ((fTemp75 > 0.5f) * iVec13[1]);
			iRec52[0] = ((1103515245 * iRec52[1]) + 1099895);
			float fTemp77 = float(iRec52[0]);
			fRec51[0] = ((fRec51[1] * float((1 - iTemp76))) + (0.5f * (((4.65661287e-10f * fTemp77) + 1.0f) * float(iTemp76))));
			float fTemp78 = (ftbl5[int(((fConst5 * ((0.449999988f * (fRec51[0] + 1.0f)) + (0.100000001f * fTemp74))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp74)), fRec18[0]));
			fRec54[0] = ((fTemp17 * fRec54[1]) + (4.65661287e-10f * (fTemp77 * fTemp18)));
			float fTemp79 = (fRec53[1] + (fConst3 * float(((2 * (fRec54[0] > 0.0f)) + -1))));
			fRec53[0] = (fTemp79 - float(int(fTemp79)));
			float fTemp80 = float((fRec53[0] > 0.0f));
			float fTemp81 = (fRec53[0] * fTemp80);
			float fTemp82 = float((fRec53[0] < 0.0f));
			float fTemp83 = (fRec53[0] * fTemp82);
			float fTemp84 = ((fRec53[0] * ((fTemp80 * float((fTemp81 < 0.5f))) + (fTemp82 * float((fTemp83 > -0.5f))))) + ((float((fTemp81 > 0.5f)) * (1.0f - fTemp81)) + (float((fTemp83 < -0.5f)) * (-1.0f - fTemp83))));
			float fTemp85 = float((iTemp3 == 6));
			iVec14[0] = (fTemp85 < 0.5f);
			int iTemp86 = std::abs(((fTemp85 > 0.5f) * iVec14[1]));
			int iTemp87 = (iTemp86 >= iRec56[1]);
			int iTemp88 = (1 - (iTemp87 | iRec57[1]));
			iRec58[0] = ((iRec58[1] * iTemp88) + iTemp88);
			iRec57[0] = (float(iRec58[0]) >= fConst0);
			iRec56[0] = ((iRec57[0] | iTemp87) ? iTemp86 : iRec56[1]);
			iRec55[0] = (((iRec56[0] * iRec55[1]) + 1) % iConst4);
			ftbl6[(iRec55[0] + (2 * iRec56[0]))] = fTemp1;
			float fTemp89 = fRec14[((IOTA - iConst12) & 262143)];
			float fTemp90 = (1.0f - fTemp89);
			iVec15[0] = (fTemp90 < 0.5f);
			int iTemp91 = ((fTemp90 > 0.5f) * iVec15[1]);
			iRec60[0] = ((1103515245 * iRec60[1]) + 1319874);
			float fTemp92 = float(iRec60[0]);
			fRec59[0] = ((fRec59[1] * float((1 - iTemp91))) + (0.5f * (((4.65661287e-10f * fTemp92) + 1.0f) * float(iTemp91))));
			float fTemp93 = (ftbl6[int(((fConst5 * ((0.449999988f * (fRec59[0] + 1.0f)) + (0.100000001f * fTemp89))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp89)), fRec18[0]));
			fRec62[0] = ((fTemp17 * fRec62[1]) + (4.65661287e-10f * (fTemp92 * fTemp18)));
			float fTemp94 = (fRec61[1] + (fConst3 * float(((2 * (fRec62[0] > 0.0f)) + -1))));
			fRec61[0] = (fTemp94 - float(int(fTemp94)));
			float fTemp95 = float((fRec61[0] > 0.0f));
			float fTemp96 = (fRec61[0] * fTemp95);
			float fTemp97 = float((fRec61[0] < 0.0f));
			float fTemp98 = (fRec61[0] * fTemp97);
			float fTemp99 = ((fRec61[0] * ((fTemp95 * float((fTemp96 < 0.5f))) + (fTemp97 * float((fTemp98 > -0.5f))))) + ((float((fTemp96 > 0.5f)) * (1.0f - fTemp96)) + (float((fTemp98 < -0.5f)) * (-1.0f - fTemp98))));
			float fTemp100 = float((iTemp3 == 7));
			iVec16[0] = (fTemp100 < 0.5f);
			int iTemp101 = std::abs(((fTemp100 > 0.5f) * iVec16[1]));
			int iTemp102 = (iTemp101 >= iRec64[1]);
			int iTemp103 = (1 - (iTemp102 | iRec65[1]));
			iRec66[0] = ((iRec66[1] * iTemp103) + iTemp103);
			iRec65[0] = (float(iRec66[0]) >= fConst0);
			iRec64[0] = ((iRec65[0] | iTemp102) ? iTemp101 : iRec64[1]);
			iRec63[0] = (((iRec64[0] * iRec63[1]) + 1) % iConst4);
			ftbl7[(iRec63[0] + (2 * iRec64[0]))] = fTemp1;
			float fTemp104 = fRec14[((IOTA - iConst13) & 262143)];
			float fTemp105 = (1.0f - fTemp104);
			iVec17[0] = (fTemp105 < 0.5f);
			int iTemp106 = ((fTemp105 > 0.5f) * iVec17[1]);
			iRec68[0] = ((1103515245 * iRec68[1]) + 1539853);
			float fTemp107 = float(iRec68[0]);
			fRec67[0] = ((fRec67[1] * float((1 - iTemp106))) + (0.5f * (((4.65661287e-10f * fTemp107) + 1.0f) * float(iTemp106))));
			float fTemp108 = (ftbl7[int(((fConst5 * ((0.449999988f * (fRec67[0] + 1.0f)) + (0.100000001f * fTemp104))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp104)), fRec18[0]));
			fRec70[0] = ((fTemp17 * fRec70[1]) + (4.65661287e-10f * (fTemp107 * fTemp18)));
			float fTemp109 = (fRec69[1] + (fConst3 * float(((2 * (fRec70[0] > 0.0f)) + -1))));
			fRec69[0] = (fTemp109 - float(int(fTemp109)));
			float fTemp110 = float((fRec69[0] > 0.0f));
			float fTemp111 = (fRec69[0] * fTemp110);
			float fTemp112 = float((fRec69[0] < 0.0f));
			float fTemp113 = (fRec69[0] * fTemp112);
			float fTemp114 = ((fRec69[0] * ((fTemp110 * float((fTemp111 < 0.5f))) + (fTemp112 * float((fTemp113 > -0.5f))))) + ((float((fTemp111 > 0.5f)) * (1.0f - fTemp111)) + (float((fTemp113 < -0.5f)) * (-1.0f - fTemp113))));
			float fTemp115 = float((iTemp3 == 8));
			iVec18[0] = (fTemp115 < 0.5f);
			int iTemp116 = std::abs(((fTemp115 > 0.5f) * iVec18[1]));
			int iTemp117 = (iTemp116 >= iRec72[1]);
			int iTemp118 = (1 - (iTemp117 | iRec73[1]));
			iRec74[0] = ((iRec74[1] * iTemp118) + iTemp118);
			iRec73[0] = (float(iRec74[0]) >= fConst0);
			iRec72[0] = ((iRec73[0] | iTemp117) ? iTemp116 : iRec72[1]);
			iRec71[0] = (((iRec72[0] * iRec71[1]) + 1) % iConst4);
			ftbl8[(iRec71[0] + (2 * iRec72[0]))] = fTemp1;
			float fTemp119 = fRec14[((IOTA - iConst14) & 262143)];
			float fTemp120 = (1.0f - fTemp119);
			iVec19[0] = (fTemp120 < 0.5f);
			int iTemp121 = ((fTemp120 > 0.5f) * iVec19[1]);
			iRec76[0] = ((1103515245 * iRec76[1]) + 1759832);
			float fTemp122 = float(iRec76[0]);
			fRec75[0] = ((fRec75[1] * float((1 - iTemp121))) + (0.5f * (((4.65661287e-10f * fTemp122) + 1.0f) * float(iTemp121))));
			float fTemp123 = (ftbl8[int(((fConst5 * ((0.449999988f * (fRec75[0] + 1.0f)) + (0.100000001f * fTemp119))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp119)), fRec18[0]));
			fRec78[0] = ((fTemp17 * fRec78[1]) + (4.65661287e-10f * (fTemp122 * fTemp18)));
			float fTemp124 = (fRec77[1] + (fConst3 * float(((2 * (fRec78[0] > 0.0f)) + -1))));
			fRec77[0] = (fTemp124 - float(int(fTemp124)));
			float fTemp125 = float((fRec77[0] > 0.0f));
			float fTemp126 = (fRec77[0] * fTemp125);
			float fTemp127 = float((fRec77[0] < 0.0f));
			float fTemp128 = (fRec77[0] * fTemp127);
			float fTemp129 = ((fRec77[0] * ((fTemp125 * float((fTemp126 < 0.5f))) + (fTemp127 * float((fTemp128 > -0.5f))))) + ((float((fTemp126 > 0.5f)) * (1.0f - fTemp126)) + (float((fTemp128 < -0.5f)) * (-1.0f - fTemp128))));
			float fTemp130 = float((iTemp3 == 9));
			iVec20[0] = (fTemp130 < 0.5f);
			int iTemp131 = std::abs(((fTemp130 > 0.5f) * iVec20[1]));
			int iTemp132 = (iTemp131 >= iRec80[1]);
			int iTemp133 = (1 - (iTemp132 | iRec81[1]));
			iRec82[0] = ((iRec82[1] * iTemp133) + iTemp133);
			iRec81[0] = (float(iRec82[0]) >= fConst0);
			iRec80[0] = ((iRec81[0] | iTemp132) ? iTemp131 : iRec80[1]);
			iRec79[0] = (((iRec80[0] * iRec79[1]) + 1) % iConst4);
			ftbl9[(iRec79[0] + (2 * iRec80[0]))] = fTemp1;
			float fTemp134 = fRec14[((IOTA - iConst15) & 262143)];
			float fTemp135 = (1.0f - fTemp134);
			iVec21[0] = (fTemp135 < 0.5f);
			int iTemp136 = ((fTemp135 > 0.5f) * iVec21[1]);
			iRec84[0] = ((1103515245 * iRec84[1]) + 1979811);
			float fTemp137 = float(iRec84[0]);
			fRec83[0] = ((fRec83[1] * float((1 - iTemp136))) + (0.5f * (((4.65661287e-10f * fTemp137) + 1.0f) * float(iTemp136))));
			float fTemp138 = (ftbl9[int(((fConst5 * ((0.449999988f * (fRec83[0] + 1.0f)) + (0.100000001f * fTemp134))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp134)), fRec18[0]));
			fRec86[0] = ((fTemp17 * fRec86[1]) + (4.65661287e-10f * (fTemp137 * fTemp18)));
			float fTemp139 = (fRec85[1] + (fConst3 * float(((2 * (fRec86[0] > 0.0f)) + -1))));
			fRec85[0] = (fTemp139 - float(int(fTemp139)));
			float fTemp140 = float((fRec85[0] > 0.0f));
			float fTemp141 = (fRec85[0] * fTemp140);
			float fTemp142 = float((fRec85[0] < 0.0f));
			float fTemp143 = (fRec85[0] * fTemp142);
			float fTemp144 = ((fRec85[0] * ((fTemp140 * float((fTemp141 < 0.5f))) + (fTemp142 * float((fTemp143 > -0.5f))))) + ((float((fTemp141 > 0.5f)) * (1.0f - fTemp141)) + (float((fTemp143 < -0.5f)) * (-1.0f - fTemp143))));
			float fTemp145 = float((iTemp3 == 10));
			iVec22[0] = (fTemp145 < 0.5f);
			int iTemp146 = std::abs(((fTemp145 > 0.5f) * iVec22[1]));
			int iTemp147 = (iTemp146 >= iRec88[1]);
			int iTemp148 = (1 - (iTemp147 | iRec89[1]));
			iRec90[0] = ((iRec90[1] * iTemp148) + iTemp148);
			iRec89[0] = (float(iRec90[0]) >= fConst0);
			iRec88[0] = ((iRec89[0] | iTemp147) ? iTemp146 : iRec88[1]);
			iRec87[0] = (((iRec88[0] * iRec87[1]) + 1) % iConst4);
			ftbl10[(iRec87[0] + (2 * iRec88[0]))] = fTemp1;
			float fTemp149 = fRec14[((IOTA - iConst16) & 262143)];
			float fTemp150 = (1.0f - fTemp149);
			iVec23[0] = (fTemp150 < 0.5f);
			int iTemp151 = ((fTemp150 > 0.5f) * iVec23[1]);
			iRec92[0] = ((1103515245 * iRec92[1]) + 2199790);
			float fTemp152 = float(iRec92[0]);
			fRec91[0] = ((fRec91[1] * float((1 - iTemp151))) + (0.5f * (((4.65661287e-10f * fTemp152) + 1.0f) * float(iTemp151))));
			float fTemp153 = (ftbl10[int(((fConst5 * ((0.449999988f * (fRec91[0] + 1.0f)) + (0.100000001f * fTemp149))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp149)), fRec18[0]));
			fRec94[0] = ((fTemp17 * fRec94[1]) + (4.65661287e-10f * (fTemp152 * fTemp18)));
			float fTemp154 = (fRec93[1] + (fConst3 * float(((2 * (fRec94[0] > 0.0f)) + -1))));
			fRec93[0] = (fTemp154 - float(int(fTemp154)));
			float fTemp155 = float((fRec93[0] > 0.0f));
			float fTemp156 = (fRec93[0] * fTemp155);
			float fTemp157 = float((fRec93[0] < 0.0f));
			float fTemp158 = (fRec93[0] * fTemp157);
			float fTemp159 = ((fRec93[0] * ((fTemp155 * float((fTemp156 < 0.5f))) + (fTemp157 * float((fTemp158 > -0.5f))))) + ((float((fTemp156 > 0.5f)) * (1.0f - fTemp156)) + (float((fTemp158 < -0.5f)) * (-1.0f - fTemp158))));
			float fTemp160 = float((iTemp3 == 11));
			iVec24[0] = (fTemp160 < 0.5f);
			int iTemp161 = std::abs(((fTemp160 > 0.5f) * iVec24[1]));
			int iTemp162 = (iTemp161 >= iRec96[1]);
			int iTemp163 = (1 - (iTemp162 | iRec97[1]));
			iRec98[0] = ((iRec98[1] * iTemp163) + iTemp163);
			iRec97[0] = (float(iRec98[0]) >= fConst0);
			iRec96[0] = ((iRec97[0] | iTemp162) ? iTemp161 : iRec96[1]);
			iRec95[0] = (((iRec96[0] * iRec95[1]) + 1) % iConst4);
			ftbl11[(iRec95[0] + (2 * iRec96[0]))] = fTemp1;
			float fTemp164 = fRec14[((IOTA - iConst17) & 262143)];
			float fTemp165 = (1.0f - fTemp164);
			iVec25[0] = (fTemp165 < 0.5f);
			int iTemp166 = ((fTemp165 > 0.5f) * iVec25[1]);
			iRec100[0] = ((1103515245 * iRec100[1]) + 2419769);
			float fTemp167 = float(iRec100[0]);
			fRec99[0] = ((fRec99[1] * float((1 - iTemp166))) + (0.5f * (((4.65661287e-10f * fTemp167) + 1.0f) * float(iTemp166))));
			float fTemp168 = (ftbl11[int(((fConst5 * ((0.449999988f * (fRec99[0] + 1.0f)) + (0.100000001f * fTemp164))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp164)), fRec18[0]));
			fRec102[0] = ((fTemp17 * fRec102[1]) + (4.65661287e-10f * (fTemp167 * fTemp18)));
			float fTemp169 = (fRec101[1] + (fConst3 * float(((2 * (fRec102[0] > 0.0f)) + -1))));
			fRec101[0] = (fTemp169 - float(int(fTemp169)));
			float fTemp170 = float((fRec101[0] > 0.0f));
			float fTemp171 = (fRec101[0] * fTemp170);
			float fTemp172 = float((fRec101[0] < 0.0f));
			float fTemp173 = (fRec101[0] * fTemp172);
			float fTemp174 = ((fRec101[0] * ((fTemp170 * float((fTemp171 < 0.5f))) + (fTemp172 * float((fTemp173 > -0.5f))))) + ((float((fTemp171 > 0.5f)) * (1.0f - fTemp171)) + (float((fTemp173 < -0.5f)) * (-1.0f - fTemp173))));
			float fTemp175 = float((iTemp3 == 12));
			iVec26[0] = (fTemp175 < 0.5f);
			int iTemp176 = std::abs(((fTemp175 > 0.5f) * iVec26[1]));
			int iTemp177 = (iTemp176 >= iRec104[1]);
			int iTemp178 = (1 - (iTemp177 | iRec105[1]));
			iRec106[0] = ((iRec106[1] * iTemp178) + iTemp178);
			iRec105[0] = (float(iRec106[0]) >= fConst0);
			iRec104[0] = ((iRec105[0] | iTemp177) ? iTemp176 : iRec104[1]);
			iRec103[0] = (((iRec104[0] * iRec103[1]) + 1) % iConst4);
			ftbl12[(iRec103[0] + (2 * iRec104[0]))] = fTemp1;
			float fTemp179 = fRec14[((IOTA - iConst18) & 262143)];
			float fTemp180 = (1.0f - fTemp179);
			iVec27[0] = (fTemp180 < 0.5f);
			int iTemp181 = ((fTemp180 > 0.5f) * iVec27[1]);
			iRec108[0] = ((1103515245 * iRec108[1]) + 2639748);
			float fTemp182 = float(iRec108[0]);
			fRec107[0] = ((fRec107[1] * float((1 - iTemp181))) + (0.5f * (((4.65661287e-10f * fTemp182) + 1.0f) * float(iTemp181))));
			float fTemp183 = (ftbl12[int(((fConst5 * ((0.449999988f * (fRec107[0] + 1.0f)) + (0.100000001f * fTemp179))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp179)), fRec18[0]));
			fRec110[0] = ((fTemp17 * fRec110[1]) + (4.65661287e-10f * (fTemp182 * fTemp18)));
			float fTemp184 = (fRec109[1] + (fConst3 * float(((2 * (fRec110[0] > 0.0f)) + -1))));
			fRec109[0] = (fTemp184 - float(int(fTemp184)));
			float fTemp185 = float((fRec109[0] > 0.0f));
			float fTemp186 = (fRec109[0] * fTemp185);
			float fTemp187 = float((fRec109[0] < 0.0f));
			float fTemp188 = (fRec109[0] * fTemp187);
			float fTemp189 = ((fRec109[0] * ((fTemp185 * float((fTemp186 < 0.5f))) + (fTemp187 * float((fTemp188 > -0.5f))))) + ((float((fTemp186 > 0.5f)) * (1.0f - fTemp186)) + (float((fTemp188 < -0.5f)) * (-1.0f - fTemp188))));
			float fTemp190 = float((iTemp3 == 13));
			iVec28[0] = (fTemp190 < 0.5f);
			int iTemp191 = std::abs(((fTemp190 > 0.5f) * iVec28[1]));
			int iTemp192 = (iTemp191 >= iRec112[1]);
			int iTemp193 = (1 - (iTemp192 | iRec113[1]));
			iRec114[0] = ((iRec114[1] * iTemp193) + iTemp193);
			iRec113[0] = (float(iRec114[0]) >= fConst0);
			iRec112[0] = ((iRec113[0] | iTemp192) ? iTemp191 : iRec112[1]);
			iRec111[0] = (((iRec112[0] * iRec111[1]) + 1) % iConst4);
			ftbl13[(iRec111[0] + (2 * iRec112[0]))] = fTemp1;
			float fTemp194 = fRec14[((IOTA - iConst19) & 262143)];
			float fTemp195 = (1.0f - fTemp194);
			iVec29[0] = (fTemp195 < 0.5f);
			int iTemp196 = ((fTemp195 > 0.5f) * iVec29[1]);
			iRec116[0] = ((1103515245 * iRec116[1]) + 2859727);
			float fTemp197 = float(iRec116[0]);
			fRec115[0] = ((fRec115[1] * float((1 - iTemp196))) + (0.5f * (((4.65661287e-10f * fTemp197) + 1.0f) * float(iTemp196))));
			float fTemp198 = (ftbl13[int(((fConst5 * ((0.449999988f * (fRec115[0] + 1.0f)) + (0.100000001f * fTemp194))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp194)), fRec18[0]));
			fRec118[0] = ((fTemp17 * fRec118[1]) + (4.65661287e-10f * (fTemp197 * fTemp18)));
			float fTemp199 = (fRec117[1] + (fConst3 * float(((2 * (fRec118[0] > 0.0f)) + -1))));
			fRec117[0] = (fTemp199 - float(int(fTemp199)));
			float fTemp200 = float((fRec117[0] > 0.0f));
			float fTemp201 = (fRec117[0] * fTemp200);
			float fTemp202 = float((fRec117[0] < 0.0f));
			float fTemp203 = (fRec117[0] * fTemp202);
			float fTemp204 = ((fRec117[0] * ((fTemp200 * float((fTemp201 < 0.5f))) + (fTemp202 * float((fTemp203 > -0.5f))))) + ((float((fTemp201 > 0.5f)) * (1.0f - fTemp201)) + (float((fTemp203 < -0.5f)) * (-1.0f - fTemp203))));
			float fTemp205 = float((iTemp3 == 14));
			iVec30[0] = (fTemp205 < 0.5f);
			int iTemp206 = std::abs(((fTemp205 > 0.5f) * iVec30[1]));
			int iTemp207 = (iTemp206 >= iRec120[1]);
			int iTemp208 = (1 - (iTemp207 | iRec121[1]));
			iRec122[0] = ((iRec122[1] * iTemp208) + iTemp208);
			iRec121[0] = (float(iRec122[0]) >= fConst0);
			iRec120[0] = ((iRec121[0] | iTemp207) ? iTemp206 : iRec120[1]);
			iRec119[0] = (((iRec120[0] * iRec119[1]) + 1) % iConst4);
			ftbl14[(iRec119[0] + (2 * iRec120[0]))] = fTemp1;
			float fTemp209 = fRec14[((IOTA - iConst20) & 262143)];
			float fTemp210 = (1.0f - fTemp209);
			iVec31[0] = (fTemp210 < 0.5f);
			int iTemp211 = ((fTemp210 > 0.5f) * iVec31[1]);
			iRec124[0] = ((1103515245 * iRec124[1]) + 3079706);
			float fTemp212 = float(iRec124[0]);
			fRec123[0] = ((fRec123[1] * float((1 - iTemp211))) + (0.5f * (((4.65661287e-10f * fTemp212) + 1.0f) * float(iTemp211))));
			float fTemp213 = (ftbl14[int(((fConst5 * ((0.449999988f * (fRec123[0] + 1.0f)) + (0.100000001f * fTemp209))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp209)), fRec18[0]));
			fRec126[0] = ((fTemp17 * fRec126[1]) + (4.65661287e-10f * (fTemp212 * fTemp18)));
			float fTemp214 = (fRec125[1] + (fConst3 * float(((2 * (fRec126[0] > 0.0f)) + -1))));
			fRec125[0] = (fTemp214 - float(int(fTemp214)));
			float fTemp215 = float((fRec125[0] > 0.0f));
			float fTemp216 = (fRec125[0] * fTemp215);
			float fTemp217 = float((fRec125[0] < 0.0f));
			float fTemp218 = (fRec125[0] * fTemp217);
			float fTemp219 = ((fRec125[0] * ((fTemp215 * float((fTemp216 < 0.5f))) + (fTemp217 * float((fTemp218 > -0.5f))))) + ((float((fTemp216 > 0.5f)) * (1.0f - fTemp216)) + (float((fTemp218 < -0.5f)) * (-1.0f - fTemp218))));
			float fTemp220 = float((iTemp3 == 15));
			iVec32[0] = (fTemp220 < 0.5f);
			int iTemp221 = std::abs(((fTemp220 > 0.5f) * iVec32[1]));
			int iTemp222 = (iTemp221 >= iRec128[1]);
			int iTemp223 = (1 - (iTemp222 | iRec129[1]));
			iRec130[0] = ((iRec130[1] * iTemp223) + iTemp223);
			iRec129[0] = (float(iRec130[0]) >= fConst0);
			iRec128[0] = ((iRec129[0] | iTemp222) ? iTemp221 : iRec128[1]);
			iRec127[0] = (((iRec128[0] * iRec127[1]) + 1) % iConst4);
			ftbl15[(iRec127[0] + (2 * iRec128[0]))] = fTemp1;
			float fTemp224 = fRec14[((IOTA - iConst21) & 262143)];
			float fTemp225 = (1.0f - fTemp224);
			iVec33[0] = (fTemp225 < 0.5f);
			int iTemp226 = ((fTemp225 > 0.5f) * iVec33[1]);
			iRec132[0] = ((1103515245 * iRec132[1]) + 3299685);
			float fTemp227 = float(iRec132[0]);
			fRec131[0] = ((fRec131[1] * float((1 - iTemp226))) + (0.5f * (((4.65661287e-10f * fTemp227) + 1.0f) * float(iTemp226))));
			float fTemp228 = (ftbl15[int(((fConst5 * ((0.449999988f * (fRec131[0] + 1.0f)) + (0.100000001f * fTemp224))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp224)), fRec18[0]));
			fRec134[0] = ((fTemp17 * fRec134[1]) + (4.65661287e-10f * (fTemp227 * fTemp18)));
			float fTemp229 = (fRec133[1] + (fConst3 * float(((2 * (fRec134[0] > 0.0f)) + -1))));
			fRec133[0] = (fTemp229 - float(int(fTemp229)));
			float fTemp230 = float((fRec133[0] > 0.0f));
			float fTemp231 = (fRec133[0] * fTemp230);
			float fTemp232 = float((fRec133[0] < 0.0f));
			float fTemp233 = (fRec133[0] * fTemp232);
			float fTemp234 = ((fRec133[0] * ((fTemp230 * float((fTemp231 < 0.5f))) + (fTemp232 * float((fTemp233 > -0.5f))))) + ((float((fTemp231 > 0.5f)) * (1.0f - fTemp231)) + (float((fTemp233 < -0.5f)) * (-1.0f - fTemp233))));
			float fTemp235 = float((iTemp3 == 16));
			iVec34[0] = (fTemp235 < 0.5f);
			int iTemp236 = std::abs(((fTemp235 > 0.5f) * iVec34[1]));
			int iTemp237 = (iTemp236 >= iRec136[1]);
			int iTemp238 = (1 - (iTemp237 | iRec137[1]));
			iRec138[0] = ((iRec138[1] * iTemp238) + iTemp238);
			iRec137[0] = (float(iRec138[0]) >= fConst0);
			iRec136[0] = ((iRec137[0] | iTemp237) ? iTemp236 : iRec136[1]);
			iRec135[0] = (((iRec136[0] * iRec135[1]) + 1) % iConst4);
			ftbl16[(iRec135[0] + (2 * iRec136[0]))] = fTemp1;
			float fTemp239 = fRec14[((IOTA - iConst22) & 262143)];
			float fTemp240 = (1.0f - fTemp239);
			iVec35[0] = (fTemp240 < 0.5f);
			int iTemp241 = ((fTemp240 > 0.5f) * iVec35[1]);
			iRec140[0] = ((1103515245 * iRec140[1]) + 3519664);
			float fTemp242 = float(iRec140[0]);
			fRec139[0] = ((fRec139[1] * float((1 - iTemp241))) + (0.5f * (((4.65661287e-10f * fTemp242) + 1.0f) * float(iTemp241))));
			float fTemp243 = (ftbl16[int(((fConst5 * ((0.449999988f * (fRec139[0] + 1.0f)) + (0.100000001f * fTemp239))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp239)), fRec18[0]));
			fRec142[0] = ((fTemp17 * fRec142[1]) + (4.65661287e-10f * (fTemp242 * fTemp18)));
			float fTemp244 = (fRec141[1] + (fConst3 * float(((2 * (fRec142[0] > 0.0f)) + -1))));
			fRec141[0] = (fTemp244 - float(int(fTemp244)));
			float fTemp245 = float((fRec141[0] > 0.0f));
			float fTemp246 = (fRec141[0] * fTemp245);
			float fTemp247 = float((fRec141[0] < 0.0f));
			float fTemp248 = (fRec141[0] * fTemp247);
			float fTemp249 = ((fRec141[0] * ((fTemp245 * float((fTemp246 < 0.5f))) + (fTemp247 * float((fTemp248 > -0.5f))))) + ((float((fTemp246 > 0.5f)) * (1.0f - fTemp246)) + (float((fTemp248 < -0.5f)) * (-1.0f - fTemp248))));
			float fTemp250 = float((iTemp3 == 17));
			iVec36[0] = (fTemp250 < 0.5f);
			int iTemp251 = std::abs(((fTemp250 > 0.5f) * iVec36[1]));
			int iTemp252 = (iTemp251 >= iRec144[1]);
			int iTemp253 = (1 - (iTemp252 | iRec145[1]));
			iRec146[0] = ((iRec146[1] * iTemp253) + iTemp253);
			iRec145[0] = (float(iRec146[0]) >= fConst0);
			iRec144[0] = ((iRec145[0] | iTemp252) ? iTemp251 : iRec144[1]);
			iRec143[0] = (((iRec144[0] * iRec143[1]) + 1) % iConst4);
			ftbl17[(iRec143[0] + (2 * iRec144[0]))] = fTemp1;
			float fTemp254 = fRec14[((IOTA - iConst23) & 262143)];
			float fTemp255 = (1.0f - fTemp254);
			iVec37[0] = (fTemp255 < 0.5f);
			int iTemp256 = ((fTemp255 > 0.5f) * iVec37[1]);
			iRec148[0] = ((1103515245 * iRec148[1]) + 3739643);
			float fTemp257 = float(iRec148[0]);
			fRec147[0] = ((fRec147[1] * float((1 - iTemp256))) + (0.5f * (((4.65661287e-10f * fTemp257) + 1.0f) * float(iTemp256))));
			float fTemp258 = (ftbl17[int(((fConst5 * ((0.449999988f * (fRec147[0] + 1.0f)) + (0.100000001f * fTemp254))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp254)), fRec18[0]));
			fRec150[0] = ((fTemp17 * fRec150[1]) + (4.65661287e-10f * (fTemp257 * fTemp18)));
			float fTemp259 = (fRec149[1] + (fConst3 * float(((2 * (fRec150[0] > 0.0f)) + -1))));
			fRec149[0] = (fTemp259 - float(int(fTemp259)));
			float fTemp260 = float((fRec149[0] > 0.0f));
			float fTemp261 = (fRec149[0] * fTemp260);
			float fTemp262 = float((fRec149[0] < 0.0f));
			float fTemp263 = (fRec149[0] * fTemp262);
			float fTemp264 = ((fRec149[0] * ((fTemp260 * float((fTemp261 < 0.5f))) + (fTemp262 * float((fTemp263 > -0.5f))))) + ((float((fTemp261 > 0.5f)) * (1.0f - fTemp261)) + (float((fTemp263 < -0.5f)) * (-1.0f - fTemp263))));
			float fTemp265 = float((iTemp3 == 18));
			iVec38[0] = (fTemp265 < 0.5f);
			int iTemp266 = std::abs(((fTemp265 > 0.5f) * iVec38[1]));
			int iTemp267 = (iTemp266 >= iRec152[1]);
			int iTemp268 = (1 - (iTemp267 | iRec153[1]));
			iRec154[0] = ((iRec154[1] * iTemp268) + iTemp268);
			iRec153[0] = (float(iRec154[0]) >= fConst0);
			iRec152[0] = ((iRec153[0] | iTemp267) ? iTemp266 : iRec152[1]);
			iRec151[0] = (((iRec152[0] * iRec151[1]) + 1) % iConst4);
			ftbl18[(iRec151[0] + (2 * iRec152[0]))] = fTemp1;
			float fTemp269 = fRec14[((IOTA - iConst24) & 262143)];
			float fTemp270 = (1.0f - fTemp269);
			iVec39[0] = (fTemp270 < 0.5f);
			int iTemp271 = ((fTemp270 > 0.5f) * iVec39[1]);
			iRec156[0] = ((1103515245 * iRec156[1]) + 3959622);
			float fTemp272 = float(iRec156[0]);
			fRec155[0] = ((fRec155[1] * float((1 - iTemp271))) + (0.5f * (((4.65661287e-10f * fTemp272) + 1.0f) * float(iTemp271))));
			float fTemp273 = (ftbl18[int(((fConst5 * ((0.449999988f * (fRec155[0] + 1.0f)) + (0.100000001f * fTemp269))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp269)), fRec18[0]));
			fRec158[0] = ((fTemp17 * fRec158[1]) + (4.65661287e-10f * (fTemp272 * fTemp18)));
			float fTemp274 = (fRec157[1] + (fConst3 * float(((2 * (fRec158[0] > 0.0f)) + -1))));
			fRec157[0] = (fTemp274 - float(int(fTemp274)));
			float fTemp275 = float((fRec157[0] > 0.0f));
			float fTemp276 = (fRec157[0] * fTemp275);
			float fTemp277 = float((fRec157[0] < 0.0f));
			float fTemp278 = (fRec157[0] * fTemp277);
			float fTemp279 = ((fRec157[0] * ((fTemp275 * float((fTemp276 < 0.5f))) + (fTemp277 * float((fTemp278 > -0.5f))))) + ((float((fTemp276 > 0.5f)) * (1.0f - fTemp276)) + (float((fTemp278 < -0.5f)) * (-1.0f - fTemp278))));
			float fTemp280 = float((iTemp3 == 19));
			iVec40[0] = (fTemp280 < 0.5f);
			int iTemp281 = std::abs(((fTemp280 > 0.5f) * iVec40[1]));
			int iTemp282 = (iTemp281 >= iRec160[1]);
			int iTemp283 = (1 - (iTemp282 | iRec161[1]));
			iRec162[0] = ((iRec162[1] * iTemp283) + iTemp283);
			iRec161[0] = (float(iRec162[0]) >= fConst0);
			iRec160[0] = ((iRec161[0] | iTemp282) ? iTemp281 : iRec160[1]);
			iRec159[0] = (((iRec160[0] * iRec159[1]) + 1) % iConst4);
			ftbl19[(iRec159[0] + (2 * iRec160[0]))] = fTemp1;
			float fTemp284 = fRec14[((IOTA - iConst25) & 262143)];
			float fTemp285 = (1.0f - fTemp284);
			iVec41[0] = (fTemp285 < 0.5f);
			int iTemp286 = ((fTemp285 > 0.5f) * iVec41[1]);
			iRec164[0] = ((1103515245 * iRec164[1]) + 4179601);
			float fTemp287 = float(iRec164[0]);
			fRec163[0] = ((fRec163[1] * float((1 - iTemp286))) + (0.5f * (((4.65661287e-10f * fTemp287) + 1.0f) * float(iTemp286))));
			float fTemp288 = (ftbl19[int(((fConst5 * ((0.449999988f * (fRec163[0] + 1.0f)) + (0.100000001f * fTemp284))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp284)), fRec18[0]));
			fRec166[0] = ((fTemp17 * fRec166[1]) + (4.65661287e-10f * (fTemp287 * fTemp18)));
			float fTemp289 = (fRec165[1] + (fConst3 * float(((2 * (fRec166[0] > 0.0f)) + -1))));
			fRec165[0] = (fTemp289 - float(int(fTemp289)));
			float fTemp290 = float((fRec165[0] > 0.0f));
			float fTemp291 = (fRec165[0] * fTemp290);
			float fTemp292 = float((fRec165[0] < 0.0f));
			float fTemp293 = (fRec165[0] * fTemp292);
			float fTemp294 = ((fRec165[0] * ((fTemp290 * float((fTemp291 < 0.5f))) + (fTemp292 * float((fTemp293 > -0.5f))))) + ((float((fTemp291 > 0.5f)) * (1.0f - fTemp291)) + (float((fTemp293 < -0.5f)) * (-1.0f - fTemp293))));
			float fTemp295 = float((iTemp3 == 20));
			iVec42[0] = (fTemp295 < 0.5f);
			int iTemp296 = std::abs(((fTemp295 > 0.5f) * iVec42[1]));
			int iTemp297 = (iTemp296 >= iRec168[1]);
			int iTemp298 = (1 - (iTemp297 | iRec169[1]));
			iRec170[0] = ((iRec170[1] * iTemp298) + iTemp298);
			iRec169[0] = (float(iRec170[0]) >= fConst0);
			iRec168[0] = ((iRec169[0] | iTemp297) ? iTemp296 : iRec168[1]);
			iRec167[0] = (((iRec168[0] * iRec167[1]) + 1) % iConst4);
			ftbl20[(iRec167[0] + (2 * iRec168[0]))] = fTemp1;
			float fTemp299 = fRec14[((IOTA - iConst26) & 262143)];
			float fTemp300 = (1.0f - fTemp299);
			iVec43[0] = (fTemp300 < 0.5f);
			int iTemp301 = ((fTemp300 > 0.5f) * iVec43[1]);
			iRec172[0] = ((1103515245 * iRec172[1]) + 4399580);
			float fTemp302 = float(iRec172[0]);
			fRec171[0] = ((fRec171[1] * float((1 - iTemp301))) + (0.5f * (((4.65661287e-10f * fTemp302) + 1.0f) * float(iTemp301))));
			float fTemp303 = (ftbl20[int(((fConst5 * ((0.449999988f * (fRec171[0] + 1.0f)) + (0.100000001f * fTemp299))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp299)), fRec18[0]));
			fRec174[0] = ((fTemp17 * fRec174[1]) + (4.65661287e-10f * (fTemp302 * fTemp18)));
			float fTemp304 = (fRec173[1] + (fConst3 * float(((2 * (fRec174[0] > 0.0f)) + -1))));
			fRec173[0] = (fTemp304 - float(int(fTemp304)));
			float fTemp305 = float((fRec173[0] > 0.0f));
			float fTemp306 = (fRec173[0] * fTemp305);
			float fTemp307 = float((fRec173[0] < 0.0f));
			float fTemp308 = (fRec173[0] * fTemp307);
			float fTemp309 = ((fRec173[0] * ((fTemp305 * float((fTemp306 < 0.5f))) + (fTemp307 * float((fTemp308 > -0.5f))))) + ((float((fTemp306 > 0.5f)) * (1.0f - fTemp306)) + (float((fTemp308 < -0.5f)) * (-1.0f - fTemp308))));
			float fTemp310 = float((iTemp3 == 21));
			iVec44[0] = (fTemp310 < 0.5f);
			int iTemp311 = std::abs(((fTemp310 > 0.5f) * iVec44[1]));
			int iTemp312 = (iTemp311 >= iRec176[1]);
			int iTemp313 = (1 - (iTemp312 | iRec177[1]));
			iRec178[0] = ((iRec178[1] * iTemp313) + iTemp313);
			iRec177[0] = (float(iRec178[0]) >= fConst0);
			iRec176[0] = ((iRec177[0] | iTemp312) ? iTemp311 : iRec176[1]);
			iRec175[0] = (((iRec176[0] * iRec175[1]) + 1) % iConst4);
			ftbl21[(iRec175[0] + (2 * iRec176[0]))] = fTemp1;
			float fTemp314 = fRec14[((IOTA - iConst27) & 262143)];
			float fTemp315 = (1.0f - fTemp314);
			iVec45[0] = (fTemp315 < 0.5f);
			int iTemp316 = ((fTemp315 > 0.5f) * iVec45[1]);
			iRec180[0] = ((1103515245 * iRec180[1]) + 4619559);
			float fTemp317 = float(iRec180[0]);
			fRec179[0] = ((fRec179[1] * float((1 - iTemp316))) + (0.5f * (((4.65661287e-10f * fTemp317) + 1.0f) * float(iTemp316))));
			float fTemp318 = (ftbl21[int(((fConst5 * ((0.449999988f * (fRec179[0] + 1.0f)) + (0.100000001f * fTemp314))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp314)), fRec18[0]));
			fRec182[0] = ((fTemp17 * fRec182[1]) + (4.65661287e-10f * (fTemp317 * fTemp18)));
			float fTemp319 = (fRec181[1] + (fConst3 * float(((2 * (fRec182[0] > 0.0f)) + -1))));
			fRec181[0] = (fTemp319 - float(int(fTemp319)));
			float fTemp320 = float((fRec181[0] > 0.0f));
			float fTemp321 = (fRec181[0] * fTemp320);
			float fTemp322 = float((fRec181[0] < 0.0f));
			float fTemp323 = (fRec181[0] * fTemp322);
			float fTemp324 = ((fRec181[0] * ((fTemp320 * float((fTemp321 < 0.5f))) + (fTemp322 * float((fTemp323 > -0.5f))))) + ((float((fTemp321 > 0.5f)) * (1.0f - fTemp321)) + (float((fTemp323 < -0.5f)) * (-1.0f - fTemp323))));
			float fTemp325 = float((iTemp3 == 22));
			iVec46[0] = (fTemp325 < 0.5f);
			int iTemp326 = std::abs(((fTemp325 > 0.5f) * iVec46[1]));
			int iTemp327 = (iTemp326 >= iRec184[1]);
			int iTemp328 = (1 - (iTemp327 | iRec185[1]));
			iRec186[0] = ((iRec186[1] * iTemp328) + iTemp328);
			iRec185[0] = (float(iRec186[0]) >= fConst0);
			iRec184[0] = ((iRec185[0] | iTemp327) ? iTemp326 : iRec184[1]);
			iRec183[0] = (((iRec184[0] * iRec183[1]) + 1) % iConst4);
			ftbl22[(iRec183[0] + (2 * iRec184[0]))] = fTemp1;
			float fTemp329 = fRec14[((IOTA - iConst28) & 262143)];
			float fTemp330 = (1.0f - fTemp329);
			iVec47[0] = (fTemp330 < 0.5f);
			int iTemp331 = ((fTemp330 > 0.5f) * iVec47[1]);
			iRec188[0] = ((1103515245 * iRec188[1]) + 4839538);
			float fTemp332 = float(iRec188[0]);
			fRec187[0] = ((fRec187[1] * float((1 - iTemp331))) + (0.5f * (((4.65661287e-10f * fTemp332) + 1.0f) * float(iTemp331))));
			float fTemp333 = (ftbl22[int(((fConst5 * ((0.449999988f * (fRec187[0] + 1.0f)) + (0.100000001f * fTemp329))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp329)), fRec18[0]));
			fRec190[0] = ((fTemp17 * fRec190[1]) + (4.65661287e-10f * (fTemp332 * fTemp18)));
			float fTemp334 = (fRec189[1] + (fConst3 * float(((2 * (fRec190[0] > 0.0f)) + -1))));
			fRec189[0] = (fTemp334 - float(int(fTemp334)));
			float fTemp335 = float((fRec189[0] > 0.0f));
			float fTemp336 = (fRec189[0] * fTemp335);
			float fTemp337 = float((fRec189[0] < 0.0f));
			float fTemp338 = (fRec189[0] * fTemp337);
			float fTemp339 = ((fRec189[0] * ((fTemp335 * float((fTemp336 < 0.5f))) + (fTemp337 * float((fTemp338 > -0.5f))))) + ((float((fTemp336 > 0.5f)) * (1.0f - fTemp336)) + (float((fTemp338 < -0.5f)) * (-1.0f - fTemp338))));
			float fTemp340 = float((iTemp3 == 23));
			iVec48[0] = (fTemp340 < 0.5f);
			int iTemp341 = std::abs(((fTemp340 > 0.5f) * iVec48[1]));
			int iTemp342 = (iTemp341 >= iRec192[1]);
			int iTemp343 = (1 - (iTemp342 | iRec193[1]));
			iRec194[0] = ((iRec194[1] * iTemp343) + iTemp343);
			iRec193[0] = (float(iRec194[0]) >= fConst0);
			iRec192[0] = ((iRec193[0] | iTemp342) ? iTemp341 : iRec192[1]);
			iRec191[0] = (((iRec192[0] * iRec191[1]) + 1) % iConst4);
			ftbl23[(iRec191[0] + (2 * iRec192[0]))] = fTemp1;
			float fTemp344 = fRec14[((IOTA - iConst29) & 262143)];
			float fTemp345 = (1.0f - fTemp344);
			iVec49[0] = (fTemp345 < 0.5f);
			int iTemp346 = ((fTemp345 > 0.5f) * iVec49[1]);
			iRec196[0] = ((1103515245 * iRec196[1]) + 5059517);
			float fTemp347 = float(iRec196[0]);
			fRec195[0] = ((fRec195[1] * float((1 - iTemp346))) + (0.5f * (((4.65661287e-10f * fTemp347) + 1.0f) * float(iTemp346))));
			float fTemp348 = (ftbl23[int(((fConst5 * ((0.449999988f * (fRec195[0] + 1.0f)) + (0.100000001f * fTemp344))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp344)), fRec18[0]));
			fRec198[0] = ((fTemp17 * fRec198[1]) + (4.65661287e-10f * (fTemp347 * fTemp18)));
			float fTemp349 = (fRec197[1] + (fConst3 * float(((2 * (fRec198[0] > 0.0f)) + -1))));
			fRec197[0] = (fTemp349 - float(int(fTemp349)));
			float fTemp350 = float((fRec197[0] > 0.0f));
			float fTemp351 = (fRec197[0] * fTemp350);
			float fTemp352 = float((fRec197[0] < 0.0f));
			float fTemp353 = (fRec197[0] * fTemp352);
			float fTemp354 = ((fRec197[0] * ((fTemp350 * float((fTemp351 < 0.5f))) + (fTemp352 * float((fTemp353 > -0.5f))))) + ((float((fTemp351 > 0.5f)) * (1.0f - fTemp351)) + (float((fTemp353 < -0.5f)) * (-1.0f - fTemp353))));
			float fTemp355 = float((iTemp3 == 24));
			iVec50[0] = (fTemp355 < 0.5f);
			int iTemp356 = std::abs(((fTemp355 > 0.5f) * iVec50[1]));
			int iTemp357 = (iTemp356 >= iRec200[1]);
			int iTemp358 = (1 - (iTemp357 | iRec201[1]));
			iRec202[0] = ((iRec202[1] * iTemp358) + iTemp358);
			iRec201[0] = (float(iRec202[0]) >= fConst0);
			iRec200[0] = ((iRec201[0] | iTemp357) ? iTemp356 : iRec200[1]);
			iRec199[0] = (((iRec200[0] * iRec199[1]) + 1) % iConst4);
			ftbl24[(iRec199[0] + (2 * iRec200[0]))] = fTemp1;
			float fTemp359 = fRec14[((IOTA - iConst30) & 262143)];
			float fTemp360 = (1.0f - fTemp359);
			iVec51[0] = (fTemp360 < 0.5f);
			int iTemp361 = ((fTemp360 > 0.5f) * iVec51[1]);
			iRec204[0] = ((1103515245 * iRec204[1]) + 5279496);
			float fTemp362 = float(iRec204[0]);
			fRec203[0] = ((fRec203[1] * float((1 - iTemp361))) + (0.5f * (((4.65661287e-10f * fTemp362) + 1.0f) * float(iTemp361))));
			float fTemp363 = (ftbl24[int(((fConst5 * ((0.449999988f * (fRec203[0] + 1.0f)) + (0.100000001f * fTemp359))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp359)), fRec18[0]));
			fRec206[0] = ((fTemp17 * fRec206[1]) + (4.65661287e-10f * (fTemp362 * fTemp18)));
			float fTemp364 = (fRec205[1] + (fConst3 * float(((2 * (fRec206[0] > 0.0f)) + -1))));
			fRec205[0] = (fTemp364 - float(int(fTemp364)));
			float fTemp365 = float((fRec205[0] > 0.0f));
			float fTemp366 = (fRec205[0] * fTemp365);
			float fTemp367 = float((fRec205[0] < 0.0f));
			float fTemp368 = (fRec205[0] * fTemp367);
			float fTemp369 = ((fRec205[0] * ((fTemp365 * float((fTemp366 < 0.5f))) + (fTemp367 * float((fTemp368 > -0.5f))))) + ((float((fTemp366 > 0.5f)) * (1.0f - fTemp366)) + (float((fTemp368 < -0.5f)) * (-1.0f - fTemp368))));
			float fTemp370 = float((iTemp3 == 25));
			iVec52[0] = (fTemp370 < 0.5f);
			int iTemp371 = std::abs(((fTemp370 > 0.5f) * iVec52[1]));
			int iTemp372 = (iTemp371 >= iRec208[1]);
			int iTemp373 = (1 - (iTemp372 | iRec209[1]));
			iRec210[0] = ((iRec210[1] * iTemp373) + iTemp373);
			iRec209[0] = (float(iRec210[0]) >= fConst0);
			iRec208[0] = ((iRec209[0] | iTemp372) ? iTemp371 : iRec208[1]);
			iRec207[0] = (((iRec208[0] * iRec207[1]) + 1) % iConst4);
			ftbl25[(iRec207[0] + (2 * iRec208[0]))] = fTemp1;
			float fTemp374 = fRec14[((IOTA - iConst31) & 262143)];
			float fTemp375 = (1.0f - fTemp374);
			iVec53[0] = (fTemp375 < 0.5f);
			int iTemp376 = ((fTemp375 > 0.5f) * iVec53[1]);
			iRec212[0] = ((1103515245 * iRec212[1]) + 5499475);
			float fTemp377 = float(iRec212[0]);
			fRec211[0] = ((fRec211[1] * float((1 - iTemp376))) + (0.5f * (((4.65661287e-10f * fTemp377) + 1.0f) * float(iTemp376))));
			float fTemp378 = (ftbl25[int(((fConst5 * ((0.449999988f * (fRec211[0] + 1.0f)) + (0.100000001f * fTemp374))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp374)), fRec18[0]));
			fRec214[0] = ((fTemp17 * fRec214[1]) + (4.65661287e-10f * (fTemp377 * fTemp18)));
			float fTemp379 = (fRec213[1] + (fConst3 * float(((2 * (fRec214[0] > 0.0f)) + -1))));
			fRec213[0] = (fTemp379 - float(int(fTemp379)));
			float fTemp380 = float((fRec213[0] > 0.0f));
			float fTemp381 = (fRec213[0] * fTemp380);
			float fTemp382 = float((fRec213[0] < 0.0f));
			float fTemp383 = (fRec213[0] * fTemp382);
			float fTemp384 = ((fRec213[0] * ((fTemp380 * float((fTemp381 < 0.5f))) + (fTemp382 * float((fTemp383 > -0.5f))))) + ((float((fTemp381 > 0.5f)) * (1.0f - fTemp381)) + (float((fTemp383 < -0.5f)) * (-1.0f - fTemp383))));
			float fTemp385 = float((iTemp3 == 26));
			iVec54[0] = (fTemp385 < 0.5f);
			int iTemp386 = std::abs(((fTemp385 > 0.5f) * iVec54[1]));
			int iTemp387 = (iTemp386 >= iRec216[1]);
			int iTemp388 = (1 - (iTemp387 | iRec217[1]));
			iRec218[0] = ((iRec218[1] * iTemp388) + iTemp388);
			iRec217[0] = (float(iRec218[0]) >= fConst0);
			iRec216[0] = ((iRec217[0] | iTemp387) ? iTemp386 : iRec216[1]);
			iRec215[0] = (((iRec216[0] * iRec215[1]) + 1) % iConst4);
			ftbl26[(iRec215[0] + (2 * iRec216[0]))] = fTemp1;
			float fTemp389 = fRec14[((IOTA - iConst32) & 262143)];
			float fTemp390 = (1.0f - fTemp389);
			iVec55[0] = (fTemp390 < 0.5f);
			int iTemp391 = ((fTemp390 > 0.5f) * iVec55[1]);
			iRec220[0] = ((1103515245 * iRec220[1]) + 5719454);
			float fTemp392 = float(iRec220[0]);
			fRec219[0] = ((fRec219[1] * float((1 - iTemp391))) + (0.5f * (((4.65661287e-10f * fTemp392) + 1.0f) * float(iTemp391))));
			float fTemp393 = (ftbl26[int(((fConst5 * ((0.449999988f * (fRec219[0] + 1.0f)) + (0.100000001f * fTemp389))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp389)), fRec18[0]));
			fRec222[0] = ((fTemp17 * fRec222[1]) + (4.65661287e-10f * (fTemp392 * fTemp18)));
			float fTemp394 = (fRec221[1] + (fConst3 * float(((2 * (fRec222[0] > 0.0f)) + -1))));
			fRec221[0] = (fTemp394 - float(int(fTemp394)));
			float fTemp395 = float((fRec221[0] > 0.0f));
			float fTemp396 = (fRec221[0] * fTemp395);
			float fTemp397 = float((fRec221[0] < 0.0f));
			float fTemp398 = (fRec221[0] * fTemp397);
			float fTemp399 = ((fRec221[0] * ((fTemp395 * float((fTemp396 < 0.5f))) + (fTemp397 * float((fTemp398 > -0.5f))))) + ((float((fTemp396 > 0.5f)) * (1.0f - fTemp396)) + (float((fTemp398 < -0.5f)) * (-1.0f - fTemp398))));
			float fTemp400 = float((iTemp3 == 27));
			iVec56[0] = (fTemp400 < 0.5f);
			int iTemp401 = std::abs(((fTemp400 > 0.5f) * iVec56[1]));
			int iTemp402 = (iTemp401 >= iRec224[1]);
			int iTemp403 = (1 - (iTemp402 | iRec225[1]));
			iRec226[0] = ((iRec226[1] * iTemp403) + iTemp403);
			iRec225[0] = (float(iRec226[0]) >= fConst0);
			iRec224[0] = ((iRec225[0] | iTemp402) ? iTemp401 : iRec224[1]);
			iRec223[0] = (((iRec224[0] * iRec223[1]) + 1) % iConst4);
			ftbl27[(iRec223[0] + (2 * iRec224[0]))] = fTemp1;
			float fTemp404 = fRec14[((IOTA - iConst33) & 262143)];
			float fTemp405 = (1.0f - fTemp404);
			iVec57[0] = (fTemp405 < 0.5f);
			int iTemp406 = ((fTemp405 > 0.5f) * iVec57[1]);
			iRec228[0] = ((1103515245 * iRec228[1]) + 5939433);
			float fTemp407 = float(iRec228[0]);
			fRec227[0] = ((fRec227[1] * float((1 - iTemp406))) + (0.5f * (((4.65661287e-10f * fTemp407) + 1.0f) * float(iTemp406))));
			float fTemp408 = (ftbl27[int(((fConst5 * ((0.449999988f * (fRec227[0] + 1.0f)) + (0.100000001f * fTemp404))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp404)), fRec18[0]));
			fRec230[0] = ((fTemp17 * fRec230[1]) + (4.65661287e-10f * (fTemp407 * fTemp18)));
			float fTemp409 = (fRec229[1] + (fConst3 * float(((2 * (fRec230[0] > 0.0f)) + -1))));
			fRec229[0] = (fTemp409 - float(int(fTemp409)));
			float fTemp410 = float((fRec229[0] > 0.0f));
			float fTemp411 = (fRec229[0] * fTemp410);
			float fTemp412 = float((fRec229[0] < 0.0f));
			float fTemp413 = (fRec229[0] * fTemp412);
			float fTemp414 = ((fRec229[0] * ((fTemp410 * float((fTemp411 < 0.5f))) + (fTemp412 * float((fTemp413 > -0.5f))))) + ((float((fTemp411 > 0.5f)) * (1.0f - fTemp411)) + (float((fTemp413 < -0.5f)) * (-1.0f - fTemp413))));
			float fTemp415 = float((iTemp3 == 28));
			iVec58[0] = (fTemp415 < 0.5f);
			int iTemp416 = std::abs(((fTemp415 > 0.5f) * iVec58[1]));
			int iTemp417 = (iTemp416 >= iRec232[1]);
			int iTemp418 = (1 - (iTemp417 | iRec233[1]));
			iRec234[0] = ((iRec234[1] * iTemp418) + iTemp418);
			iRec233[0] = (float(iRec234[0]) >= fConst0);
			iRec232[0] = ((iRec233[0] | iTemp417) ? iTemp416 : iRec232[1]);
			iRec231[0] = (((iRec232[0] * iRec231[1]) + 1) % iConst4);
			ftbl28[(iRec231[0] + (2 * iRec232[0]))] = fTemp1;
			float fTemp419 = fRec14[((IOTA - iConst34) & 262143)];
			float fTemp420 = (1.0f - fTemp419);
			iVec59[0] = (fTemp420 < 0.5f);
			int iTemp421 = ((fTemp420 > 0.5f) * iVec59[1]);
			iRec236[0] = ((1103515245 * iRec236[1]) + 6159412);
			float fTemp422 = float(iRec236[0]);
			fRec235[0] = ((fRec235[1] * float((1 - iTemp421))) + (0.5f * (((4.65661287e-10f * fTemp422) + 1.0f) * float(iTemp421))));
			float fTemp423 = (ftbl28[int(((fConst5 * ((0.449999988f * (fRec235[0] + 1.0f)) + (0.100000001f * fTemp419))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp419)), fRec18[0]));
			fRec238[0] = ((fTemp17 * fRec238[1]) + (4.65661287e-10f * (fTemp422 * fTemp18)));
			float fTemp424 = (fRec237[1] + (fConst3 * float(((2 * (fRec238[0] > 0.0f)) + -1))));
			fRec237[0] = (fTemp424 - float(int(fTemp424)));
			float fTemp425 = float((fRec237[0] > 0.0f));
			float fTemp426 = (fRec237[0] * fTemp425);
			float fTemp427 = float((fRec237[0] < 0.0f));
			float fTemp428 = (fRec237[0] * fTemp427);
			float fTemp429 = ((fRec237[0] * ((fTemp425 * float((fTemp426 < 0.5f))) + (fTemp427 * float((fTemp428 > -0.5f))))) + ((float((fTemp426 > 0.5f)) * (1.0f - fTemp426)) + (float((fTemp428 < -0.5f)) * (-1.0f - fTemp428))));
			float fTemp430 = float((iTemp3 == 29));
			iVec60[0] = (fTemp430 < 0.5f);
			int iTemp431 = std::abs(((fTemp430 > 0.5f) * iVec60[1]));
			int iTemp432 = (iTemp431 >= iRec240[1]);
			int iTemp433 = (1 - (iTemp432 | iRec241[1]));
			iRec242[0] = ((iRec242[1] * iTemp433) + iTemp433);
			iRec241[0] = (float(iRec242[0]) >= fConst0);
			iRec240[0] = ((iRec241[0] | iTemp432) ? iTemp431 : iRec240[1]);
			iRec239[0] = (((iRec240[0] * iRec239[1]) + 1) % iConst4);
			ftbl29[(iRec239[0] + (2 * iRec240[0]))] = fTemp1;
			float fTemp434 = fRec14[((IOTA - iConst35) & 262143)];
			float fTemp435 = (1.0f - fTemp434);
			iVec61[0] = (fTemp435 < 0.5f);
			int iTemp436 = ((fTemp435 > 0.5f) * iVec61[1]);
			iRec244[0] = ((1103515245 * iRec244[1]) + 6379391);
			float fTemp437 = float(iRec244[0]);
			fRec243[0] = ((fRec243[1] * float((1 - iTemp436))) + (0.5f * (((4.65661287e-10f * fTemp437) + 1.0f) * float(iTemp436))));
			float fTemp438 = (ftbl29[int(((fConst5 * ((0.449999988f * (fRec243[0] + 1.0f)) + (0.100000001f * fTemp434))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp434)), fRec18[0]));
			fRec246[0] = ((fTemp17 * fRec246[1]) + (4.65661287e-10f * (fTemp437 * fTemp18)));
			float fTemp439 = (fRec245[1] + (fConst3 * float(((2 * (fRec246[0] > 0.0f)) + -1))));
			fRec245[0] = (fTemp439 - float(int(fTemp439)));
			float fTemp440 = float((fRec245[0] > 0.0f));
			float fTemp441 = (fRec245[0] * fTemp440);
			float fTemp442 = float((fRec245[0] < 0.0f));
			float fTemp443 = (fRec245[0] * fTemp442);
			float fTemp444 = ((fRec245[0] * ((fTemp440 * float((fTemp441 < 0.5f))) + (fTemp442 * float((fTemp443 > -0.5f))))) + ((float((fTemp441 > 0.5f)) * (1.0f - fTemp441)) + (float((fTemp443 < -0.5f)) * (-1.0f - fTemp443))));
			float fTemp445 = float((iTemp3 == 30));
			iVec62[0] = (fTemp445 < 0.5f);
			int iTemp446 = std::abs(((fTemp445 > 0.5f) * iVec62[1]));
			int iTemp447 = (iTemp446 >= iRec248[1]);
			int iTemp448 = (1 - (iTemp447 | iRec249[1]));
			iRec250[0] = ((iRec250[1] * iTemp448) + iTemp448);
			iRec249[0] = (float(iRec250[0]) >= fConst0);
			iRec248[0] = ((iRec249[0] | iTemp447) ? iTemp446 : iRec248[1]);
			iRec247[0] = (((iRec248[0] * iRec247[1]) + 1) % iConst4);
			ftbl30[(iRec247[0] + (2 * iRec248[0]))] = fTemp1;
			float fTemp449 = fRec14[((IOTA - iConst36) & 262143)];
			float fTemp450 = (1.0f - fTemp449);
			iVec63[0] = (fTemp450 < 0.5f);
			int iTemp451 = ((fTemp450 > 0.5f) * iVec63[1]);
			iRec252[0] = ((1103515245 * iRec252[1]) + 6599370);
			float fTemp452 = float(iRec252[0]);
			fRec251[0] = ((fRec251[1] * float((1 - iTemp451))) + (0.5f * (((4.65661287e-10f * fTemp452) + 1.0f) * float(iTemp451))));
			float fTemp453 = (ftbl30[int(((fConst5 * ((0.449999988f * (fRec251[0] + 1.0f)) + (0.100000001f * fTemp449))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp449)), fRec18[0]));
			fRec254[0] = ((fTemp17 * fRec254[1]) + (4.65661287e-10f * (fTemp452 * fTemp18)));
			float fTemp454 = (fRec253[1] + (fConst3 * float(((2 * (fRec254[0] > 0.0f)) + -1))));
			fRec253[0] = (fTemp454 - float(int(fTemp454)));
			float fTemp455 = float((fRec253[0] > 0.0f));
			float fTemp456 = (fRec253[0] * fTemp455);
			float fTemp457 = float((fRec253[0] < 0.0f));
			float fTemp458 = (fRec253[0] * fTemp457);
			float fTemp459 = ((fRec253[0] * ((fTemp455 * float((fTemp456 < 0.5f))) + (fTemp457 * float((fTemp458 > -0.5f))))) + ((float((fTemp456 > 0.5f)) * (1.0f - fTemp456)) + (float((fTemp458 < -0.5f)) * (-1.0f - fTemp458))));
			float fTemp460 = float((iTemp3 == 31));
			iVec64[0] = (fTemp460 < 0.5f);
			int iTemp461 = std::abs(((fTemp460 > 0.5f) * iVec64[1]));
			int iTemp462 = (iTemp461 >= iRec256[1]);
			int iTemp463 = (1 - (iTemp462 | iRec257[1]));
			iRec258[0] = ((iRec258[1] * iTemp463) + iTemp463);
			iRec257[0] = (float(iRec258[0]) >= fConst0);
			iRec256[0] = ((iRec257[0] | iTemp462) ? iTemp461 : iRec256[1]);
			iRec255[0] = (((iRec256[0] * iRec255[1]) + 1) % iConst4);
			ftbl31[(iRec255[0] + (2 * iRec256[0]))] = fTemp1;
			float fTemp464 = fRec14[((IOTA - iConst37) & 262143)];
			float fTemp465 = (1.0f - fTemp464);
			iVec65[0] = (fTemp465 < 0.5f);
			int iTemp466 = ((fTemp465 > 0.5f) * iVec65[1]);
			iRec260[0] = ((1103515245 * iRec260[1]) + 6819349);
			float fTemp467 = float(iRec260[0]);
			fRec259[0] = ((fRec259[1] * float((1 - iTemp466))) + (0.5f * (((4.65661287e-10f * fTemp467) + 1.0f) * float(iTemp466))));
			float fTemp468 = (ftbl31[int(((fConst5 * ((0.449999988f * (fRec259[0] + 1.0f)) + (0.100000001f * fTemp464))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp464)), fRec18[0]));
			fRec262[0] = ((fTemp17 * fRec262[1]) + (4.65661287e-10f * (fTemp467 * fTemp18)));
			float fTemp469 = (fRec261[1] + (fConst3 * float(((2 * (fRec262[0] > 0.0f)) + -1))));
			fRec261[0] = (fTemp469 - float(int(fTemp469)));
			float fTemp470 = float((fRec261[0] > 0.0f));
			float fTemp471 = (fRec261[0] * fTemp470);
			float fTemp472 = float((fRec261[0] < 0.0f));
			float fTemp473 = (fRec261[0] * fTemp472);
			float fTemp474 = ((fRec261[0] * ((fTemp470 * float((fTemp471 < 0.5f))) + (fTemp472 * float((fTemp473 > -0.5f))))) + ((float((fTemp471 > 0.5f)) * (1.0f - fTemp471)) + (float((fTemp473 < -0.5f)) * (-1.0f - fTemp473))));
			float fTemp475 = float((iTemp3 == 32));
			iVec66[0] = (fTemp475 < 0.5f);
			int iTemp476 = std::abs(((fTemp475 > 0.5f) * iVec66[1]));
			int iTemp477 = (iTemp476 >= iRec264[1]);
			int iTemp478 = (1 - (iTemp477 | iRec265[1]));
			iRec266[0] = ((iRec266[1] * iTemp478) + iTemp478);
			iRec265[0] = (float(iRec266[0]) >= fConst0);
			iRec264[0] = ((iRec265[0] | iTemp477) ? iTemp476 : iRec264[1]);
			iRec263[0] = (((iRec264[0] * iRec263[1]) + 1) % iConst4);
			ftbl32[(iRec263[0] + (2 * iRec264[0]))] = fTemp1;
			float fTemp479 = fRec14[((IOTA - iConst38) & 262143)];
			float fTemp480 = (1.0f - fTemp479);
			iVec67[0] = (fTemp480 < 0.5f);
			int iTemp481 = ((fTemp480 > 0.5f) * iVec67[1]);
			iRec268[0] = ((1103515245 * iRec268[1]) + 7039328);
			float fTemp482 = float(iRec268[0]);
			fRec267[0] = ((fRec267[1] * float((1 - iTemp481))) + (0.5f * (((4.65661287e-10f * fTemp482) + 1.0f) * float(iTemp481))));
			float fTemp483 = (ftbl32[int(((fConst5 * ((0.449999988f * (fRec267[0] + 1.0f)) + (0.100000001f * fTemp479))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp479)), fRec18[0]));
			fRec270[0] = ((fTemp17 * fRec270[1]) + (4.65661287e-10f * (fTemp482 * fTemp18)));
			float fTemp484 = (fRec269[1] + (fConst3 * float(((2 * (fRec270[0] > 0.0f)) + -1))));
			fRec269[0] = (fTemp484 - float(int(fTemp484)));
			float fTemp485 = float((fRec269[0] > 0.0f));
			float fTemp486 = (fRec269[0] * fTemp485);
			float fTemp487 = float((fRec269[0] < 0.0f));
			float fTemp488 = (fRec269[0] * fTemp487);
			float fTemp489 = ((fRec269[0] * ((fTemp485 * float((fTemp486 < 0.5f))) + (fTemp487 * float((fTemp488 > -0.5f))))) + ((float((fTemp486 > 0.5f)) * (1.0f - fTemp486)) + (float((fTemp488 < -0.5f)) * (-1.0f - fTemp488))));
			float fTemp490 = float((iTemp3 == 33));
			iVec68[0] = (fTemp490 < 0.5f);
			int iTemp491 = std::abs(((fTemp490 > 0.5f) * iVec68[1]));
			int iTemp492 = (iTemp491 >= iRec272[1]);
			int iTemp493 = (1 - (iTemp492 | iRec273[1]));
			iRec274[0] = ((iRec274[1] * iTemp493) + iTemp493);
			iRec273[0] = (float(iRec274[0]) >= fConst0);
			iRec272[0] = ((iRec273[0] | iTemp492) ? iTemp491 : iRec272[1]);
			iRec271[0] = (((iRec272[0] * iRec271[1]) + 1) % iConst4);
			ftbl33[(iRec271[0] + (2 * iRec272[0]))] = fTemp1;
			float fTemp494 = fRec14[((IOTA - iConst39) & 262143)];
			float fTemp495 = (1.0f - fTemp494);
			iVec69[0] = (fTemp495 < 0.5f);
			int iTemp496 = ((fTemp495 > 0.5f) * iVec69[1]);
			iRec276[0] = ((1103515245 * iRec276[1]) + 7259307);
			float fTemp497 = float(iRec276[0]);
			fRec275[0] = ((fRec275[1] * float((1 - iTemp496))) + (0.5f * (((4.65661287e-10f * fTemp497) + 1.0f) * float(iTemp496))));
			float fTemp498 = (ftbl33[int(((fConst5 * ((0.449999988f * (fRec275[0] + 1.0f)) + (0.100000001f * fTemp494))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp494)), fRec18[0]));
			fRec278[0] = ((fTemp17 * fRec278[1]) + (4.65661287e-10f * (fTemp497 * fTemp18)));
			float fTemp499 = (fRec277[1] + (fConst3 * float(((2 * (fRec278[0] > 0.0f)) + -1))));
			fRec277[0] = (fTemp499 - float(int(fTemp499)));
			float fTemp500 = float((fRec277[0] > 0.0f));
			float fTemp501 = (fRec277[0] * fTemp500);
			float fTemp502 = float((fRec277[0] < 0.0f));
			float fTemp503 = (fRec277[0] * fTemp502);
			float fTemp504 = ((fRec277[0] * ((fTemp500 * float((fTemp501 < 0.5f))) + (fTemp502 * float((fTemp503 > -0.5f))))) + ((float((fTemp501 > 0.5f)) * (1.0f - fTemp501)) + (float((fTemp503 < -0.5f)) * (-1.0f - fTemp503))));
			float fTemp505 = float((iTemp3 == 34));
			iVec70[0] = (fTemp505 < 0.5f);
			int iTemp506 = std::abs(((fTemp505 > 0.5f) * iVec70[1]));
			int iTemp507 = (iTemp506 >= iRec280[1]);
			int iTemp508 = (1 - (iTemp507 | iRec281[1]));
			iRec282[0] = ((iRec282[1] * iTemp508) + iTemp508);
			iRec281[0] = (float(iRec282[0]) >= fConst0);
			iRec280[0] = ((iRec281[0] | iTemp507) ? iTemp506 : iRec280[1]);
			iRec279[0] = (((iRec280[0] * iRec279[1]) + 1) % iConst4);
			ftbl34[(iRec279[0] + (2 * iRec280[0]))] = fTemp1;
			float fTemp509 = fRec14[((IOTA - iConst40) & 262143)];
			float fTemp510 = (1.0f - fTemp509);
			iVec71[0] = (fTemp510 < 0.5f);
			int iTemp511 = ((fTemp510 > 0.5f) * iVec71[1]);
			iRec284[0] = ((1103515245 * iRec284[1]) + 7479286);
			float fTemp512 = float(iRec284[0]);
			fRec283[0] = ((fRec283[1] * float((1 - iTemp511))) + (0.5f * (((4.65661287e-10f * fTemp512) + 1.0f) * float(iTemp511))));
			float fTemp513 = (ftbl34[int(((fConst5 * ((0.449999988f * (fRec283[0] + 1.0f)) + (0.100000001f * fTemp509))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp509)), fRec18[0]));
			fRec286[0] = ((fTemp17 * fRec286[1]) + (4.65661287e-10f * (fTemp512 * fTemp18)));
			float fTemp514 = (fRec285[1] + (fConst3 * float(((2 * (fRec286[0] > 0.0f)) + -1))));
			fRec285[0] = (fTemp514 - float(int(fTemp514)));
			float fTemp515 = float((fRec285[0] > 0.0f));
			float fTemp516 = (fRec285[0] * fTemp515);
			float fTemp517 = float((fRec285[0] < 0.0f));
			float fTemp518 = (fRec285[0] * fTemp517);
			float fTemp519 = ((fRec285[0] * ((fTemp515 * float((fTemp516 < 0.5f))) + (fTemp517 * float((fTemp518 > -0.5f))))) + ((float((fTemp516 > 0.5f)) * (1.0f - fTemp516)) + (float((fTemp518 < -0.5f)) * (-1.0f - fTemp518))));
			float fTemp520 = float((iTemp3 == 35));
			iVec72[0] = (fTemp520 < 0.5f);
			int iTemp521 = std::abs(((fTemp520 > 0.5f) * iVec72[1]));
			int iTemp522 = (iTemp521 >= iRec288[1]);
			int iTemp523 = (1 - (iTemp522 | iRec289[1]));
			iRec290[0] = ((iRec290[1] * iTemp523) + iTemp523);
			iRec289[0] = (float(iRec290[0]) >= fConst0);
			iRec288[0] = ((iRec289[0] | iTemp522) ? iTemp521 : iRec288[1]);
			iRec287[0] = (((iRec288[0] * iRec287[1]) + 1) % iConst4);
			ftbl35[(iRec287[0] + (2 * iRec288[0]))] = fTemp1;
			float fTemp524 = fRec14[((IOTA - iConst41) & 262143)];
			float fTemp525 = (1.0f - fTemp524);
			iVec73[0] = (fTemp525 < 0.5f);
			int iTemp526 = ((fTemp525 > 0.5f) * iVec73[1]);
			iRec292[0] = ((1103515245 * iRec292[1]) + 7699265);
			float fTemp527 = float(iRec292[0]);
			fRec291[0] = ((fRec291[1] * float((1 - iTemp526))) + (0.5f * (((4.65661287e-10f * fTemp527) + 1.0f) * float(iTemp526))));
			float fTemp528 = (ftbl35[int(((fConst5 * ((0.449999988f * (fRec291[0] + 1.0f)) + (0.100000001f * fTemp524))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp524)), fRec18[0]));
			fRec294[0] = ((fTemp17 * fRec294[1]) + (4.65661287e-10f * (fTemp527 * fTemp18)));
			float fTemp529 = (fRec293[1] + (fConst3 * float(((2 * (fRec294[0] > 0.0f)) + -1))));
			fRec293[0] = (fTemp529 - float(int(fTemp529)));
			float fTemp530 = float((fRec293[0] > 0.0f));
			float fTemp531 = (fRec293[0] * fTemp530);
			float fTemp532 = float((fRec293[0] < 0.0f));
			float fTemp533 = (fRec293[0] * fTemp532);
			float fTemp534 = ((fRec293[0] * ((fTemp530 * float((fTemp531 < 0.5f))) + (fTemp532 * float((fTemp533 > -0.5f))))) + ((float((fTemp531 > 0.5f)) * (1.0f - fTemp531)) + (float((fTemp533 < -0.5f)) * (-1.0f - fTemp533))));
			float fTemp535 = float((iTemp3 == 36));
			iVec74[0] = (fTemp535 < 0.5f);
			int iTemp536 = std::abs(((fTemp535 > 0.5f) * iVec74[1]));
			int iTemp537 = (iTemp536 >= iRec296[1]);
			int iTemp538 = (1 - (iTemp537 | iRec297[1]));
			iRec298[0] = ((iRec298[1] * iTemp538) + iTemp538);
			iRec297[0] = (float(iRec298[0]) >= fConst0);
			iRec296[0] = ((iRec297[0] | iTemp537) ? iTemp536 : iRec296[1]);
			iRec295[0] = (((iRec296[0] * iRec295[1]) + 1) % iConst4);
			ftbl36[(iRec295[0] + (2 * iRec296[0]))] = fTemp1;
			float fTemp539 = fRec14[((IOTA - iConst42) & 262143)];
			float fTemp540 = (1.0f - fTemp539);
			iVec75[0] = (fTemp540 < 0.5f);
			int iTemp541 = ((fTemp540 > 0.5f) * iVec75[1]);
			iRec300[0] = ((1103515245 * iRec300[1]) + 7919244);
			float fTemp542 = float(iRec300[0]);
			fRec299[0] = ((fRec299[1] * float((1 - iTemp541))) + (0.5f * (((4.65661287e-10f * fTemp542) + 1.0f) * float(iTemp541))));
			float fTemp543 = (ftbl36[int(((fConst5 * ((0.449999988f * (fRec299[0] + 1.0f)) + (0.100000001f * fTemp539))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp539)), fRec18[0]));
			fRec302[0] = ((fTemp17 * fRec302[1]) + (4.65661287e-10f * (fTemp542 * fTemp18)));
			float fTemp544 = (fRec301[1] + (fConst3 * float(((2 * (fRec302[0] > 0.0f)) + -1))));
			fRec301[0] = (fTemp544 - float(int(fTemp544)));
			float fTemp545 = float((fRec301[0] > 0.0f));
			float fTemp546 = (fRec301[0] * fTemp545);
			float fTemp547 = float((fRec301[0] < 0.0f));
			float fTemp548 = (fRec301[0] * fTemp547);
			float fTemp549 = ((fRec301[0] * ((fTemp545 * float((fTemp546 < 0.5f))) + (fTemp547 * float((fTemp548 > -0.5f))))) + ((float((fTemp546 > 0.5f)) * (1.0f - fTemp546)) + (float((fTemp548 < -0.5f)) * (-1.0f - fTemp548))));
			float fTemp550 = float((iTemp3 == 37));
			iVec76[0] = (fTemp550 < 0.5f);
			int iTemp551 = std::abs(((fTemp550 > 0.5f) * iVec76[1]));
			int iTemp552 = (iTemp551 >= iRec304[1]);
			int iTemp553 = (1 - (iTemp552 | iRec305[1]));
			iRec306[0] = ((iRec306[1] * iTemp553) + iTemp553);
			iRec305[0] = (float(iRec306[0]) >= fConst0);
			iRec304[0] = ((iRec305[0] | iTemp552) ? iTemp551 : iRec304[1]);
			iRec303[0] = (((iRec304[0] * iRec303[1]) + 1) % iConst4);
			ftbl37[(iRec303[0] + (2 * iRec304[0]))] = fTemp1;
			float fTemp554 = fRec14[((IOTA - iConst43) & 262143)];
			float fTemp555 = (1.0f - fTemp554);
			iVec77[0] = (fTemp555 < 0.5f);
			int iTemp556 = ((fTemp555 > 0.5f) * iVec77[1]);
			iRec308[0] = ((1103515245 * iRec308[1]) + 8139223);
			float fTemp557 = float(iRec308[0]);
			fRec307[0] = ((fRec307[1] * float((1 - iTemp556))) + (0.5f * (((4.65661287e-10f * fTemp557) + 1.0f) * float(iTemp556))));
			float fTemp558 = (ftbl37[int(((fConst5 * ((0.449999988f * (fRec307[0] + 1.0f)) + (0.100000001f * fTemp554))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp554)), fRec18[0]));
			fRec310[0] = ((fTemp17 * fRec310[1]) + (4.65661287e-10f * (fTemp557 * fTemp18)));
			float fTemp559 = (fRec309[1] + (fConst3 * float(((2 * (fRec310[0] > 0.0f)) + -1))));
			fRec309[0] = (fTemp559 - float(int(fTemp559)));
			float fTemp560 = float((fRec309[0] > 0.0f));
			float fTemp561 = (fRec309[0] * fTemp560);
			float fTemp562 = float((fRec309[0] < 0.0f));
			float fTemp563 = (fRec309[0] * fTemp562);
			float fTemp564 = ((fRec309[0] * ((fTemp560 * float((fTemp561 < 0.5f))) + (fTemp562 * float((fTemp563 > -0.5f))))) + ((float((fTemp561 > 0.5f)) * (1.0f - fTemp561)) + (float((fTemp563 < -0.5f)) * (-1.0f - fTemp563))));
			float fTemp565 = float((iTemp3 == 38));
			iVec78[0] = (fTemp565 < 0.5f);
			int iTemp566 = std::abs(((fTemp565 > 0.5f) * iVec78[1]));
			int iTemp567 = (iTemp566 >= iRec312[1]);
			int iTemp568 = (1 - (iTemp567 | iRec313[1]));
			iRec314[0] = ((iRec314[1] * iTemp568) + iTemp568);
			iRec313[0] = (float(iRec314[0]) >= fConst0);
			iRec312[0] = ((iRec313[0] | iTemp567) ? iTemp566 : iRec312[1]);
			iRec311[0] = (((iRec312[0] * iRec311[1]) + 1) % iConst4);
			ftbl38[(iRec311[0] + (2 * iRec312[0]))] = fTemp1;
			float fTemp569 = fRec14[((IOTA - iConst44) & 262143)];
			float fTemp570 = (1.0f - fTemp569);
			iVec79[0] = (fTemp570 < 0.5f);
			int iTemp571 = ((fTemp570 > 0.5f) * iVec79[1]);
			iRec316[0] = ((1103515245 * iRec316[1]) + 8359202);
			float fTemp572 = float(iRec316[0]);
			fRec315[0] = ((fRec315[1] * float((1 - iTemp571))) + (0.5f * (((4.65661287e-10f * fTemp572) + 1.0f) * float(iTemp571))));
			float fTemp573 = (ftbl38[int(((fConst5 * ((0.449999988f * (fRec315[0] + 1.0f)) + (0.100000001f * fTemp569))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp569)), fRec18[0]));
			fRec318[0] = ((fTemp17 * fRec318[1]) + (4.65661287e-10f * (fTemp572 * fTemp18)));
			float fTemp574 = (fRec317[1] + (fConst3 * float(((2 * (fRec318[0] > 0.0f)) + -1))));
			fRec317[0] = (fTemp574 - float(int(fTemp574)));
			float fTemp575 = float((fRec317[0] > 0.0f));
			float fTemp576 = (fRec317[0] * fTemp575);
			float fTemp577 = float((fRec317[0] < 0.0f));
			float fTemp578 = (fRec317[0] * fTemp577);
			float fTemp579 = ((fRec317[0] * ((fTemp575 * float((fTemp576 < 0.5f))) + (fTemp577 * float((fTemp578 > -0.5f))))) + ((float((fTemp576 > 0.5f)) * (1.0f - fTemp576)) + (float((fTemp578 < -0.5f)) * (-1.0f - fTemp578))));
			float fTemp580 = float((iTemp3 == 39));
			iVec80[0] = (fTemp580 < 0.5f);
			int iTemp581 = std::abs(((fTemp580 > 0.5f) * iVec80[1]));
			int iTemp582 = (iTemp581 >= iRec320[1]);
			int iTemp583 = (1 - (iTemp582 | iRec321[1]));
			iRec322[0] = ((iRec322[1] * iTemp583) + iTemp583);
			iRec321[0] = (float(iRec322[0]) >= fConst0);
			iRec320[0] = ((iRec321[0] | iTemp582) ? iTemp581 : iRec320[1]);
			iRec319[0] = (((iRec320[0] * iRec319[1]) + 1) % iConst4);
			ftbl39[(iRec319[0] + (2 * iRec320[0]))] = fTemp1;
			float fTemp584 = fRec14[((IOTA - iConst45) & 262143)];
			float fTemp585 = (1.0f - fTemp584);
			iVec81[0] = (fTemp585 < 0.5f);
			int iTemp586 = ((fTemp585 > 0.5f) * iVec81[1]);
			iRec324[0] = ((1103515245 * iRec324[1]) + 8579181);
			float fTemp587 = float(iRec324[0]);
			fRec323[0] = ((fRec323[1] * float((1 - iTemp586))) + (0.5f * (((4.65661287e-10f * fTemp587) + 1.0f) * float(iTemp586))));
			float fTemp588 = (ftbl39[int(((fConst5 * ((0.449999988f * (fRec323[0] + 1.0f)) + (0.100000001f * fTemp584))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp584)), fRec18[0]));
			fRec326[0] = ((fTemp17 * fRec326[1]) + (4.65661287e-10f * (fTemp587 * fTemp18)));
			float fTemp589 = (fRec325[1] + (fConst3 * float(((2 * (fRec326[0] > 0.0f)) + -1))));
			fRec325[0] = (fTemp589 - float(int(fTemp589)));
			float fTemp590 = float((fRec325[0] > 0.0f));
			float fTemp591 = (fRec325[0] * fTemp590);
			float fTemp592 = float((fRec325[0] < 0.0f));
			float fTemp593 = (fRec325[0] * fTemp592);
			float fTemp594 = ((fRec325[0] * ((fTemp590 * float((fTemp591 < 0.5f))) + (fTemp592 * float((fTemp593 > -0.5f))))) + ((float((fTemp591 > 0.5f)) * (1.0f - fTemp591)) + (float((fTemp593 < -0.5f)) * (-1.0f - fTemp593))));
			float fTemp595 = float((iTemp3 == 40));
			iVec82[0] = (fTemp595 < 0.5f);
			int iTemp596 = std::abs(((fTemp595 > 0.5f) * iVec82[1]));
			int iTemp597 = (iTemp596 >= iRec328[1]);
			int iTemp598 = (1 - (iTemp597 | iRec329[1]));
			iRec330[0] = ((iRec330[1] * iTemp598) + iTemp598);
			iRec329[0] = (float(iRec330[0]) >= fConst0);
			iRec328[0] = ((iRec329[0] | iTemp597) ? iTemp596 : iRec328[1]);
			iRec327[0] = (((iRec328[0] * iRec327[1]) + 1) % iConst4);
			ftbl40[(iRec327[0] + (2 * iRec328[0]))] = fTemp1;
			float fTemp599 = fRec14[((IOTA - iConst46) & 262143)];
			float fTemp600 = (1.0f - fTemp599);
			iVec83[0] = (fTemp600 < 0.5f);
			int iTemp601 = ((fTemp600 > 0.5f) * iVec83[1]);
			iRec332[0] = ((1103515245 * iRec332[1]) + 8799160);
			float fTemp602 = float(iRec332[0]);
			fRec331[0] = ((fRec331[1] * float((1 - iTemp601))) + (0.5f * (((4.65661287e-10f * fTemp602) + 1.0f) * float(iTemp601))));
			float fTemp603 = (ftbl40[int(((fConst5 * ((0.449999988f * (fRec331[0] + 1.0f)) + (0.100000001f * fTemp599))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp599)), fRec18[0]));
			fRec334[0] = ((fTemp17 * fRec334[1]) + (4.65661287e-10f * (fTemp602 * fTemp18)));
			float fTemp604 = (fRec333[1] + (fConst3 * float(((2 * (fRec334[0] > 0.0f)) + -1))));
			fRec333[0] = (fTemp604 - float(int(fTemp604)));
			float fTemp605 = float((fRec333[0] > 0.0f));
			float fTemp606 = (fRec333[0] * fTemp605);
			float fTemp607 = float((fRec333[0] < 0.0f));
			float fTemp608 = (fRec333[0] * fTemp607);
			float fTemp609 = ((fRec333[0] * ((fTemp605 * float((fTemp606 < 0.5f))) + (fTemp607 * float((fTemp608 > -0.5f))))) + ((float((fTemp606 > 0.5f)) * (1.0f - fTemp606)) + (float((fTemp608 < -0.5f)) * (-1.0f - fTemp608))));
			float fTemp610 = float((iTemp3 == 41));
			iVec84[0] = (fTemp610 < 0.5f);
			int iTemp611 = std::abs(((fTemp610 > 0.5f) * iVec84[1]));
			int iTemp612 = (iTemp611 >= iRec336[1]);
			int iTemp613 = (1 - (iTemp612 | iRec337[1]));
			iRec338[0] = ((iRec338[1] * iTemp613) + iTemp613);
			iRec337[0] = (float(iRec338[0]) >= fConst0);
			iRec336[0] = ((iRec337[0] | iTemp612) ? iTemp611 : iRec336[1]);
			iRec335[0] = (((iRec336[0] * iRec335[1]) + 1) % iConst4);
			ftbl41[(iRec335[0] + (2 * iRec336[0]))] = fTemp1;
			float fTemp614 = fRec14[((IOTA - iConst47) & 262143)];
			float fTemp615 = (1.0f - fTemp614);
			iVec85[0] = (fTemp615 < 0.5f);
			int iTemp616 = ((fTemp615 > 0.5f) * iVec85[1]);
			iRec340[0] = ((1103515245 * iRec340[1]) + 9019139);
			float fTemp617 = float(iRec340[0]);
			fRec339[0] = ((fRec339[1] * float((1 - iTemp616))) + (0.5f * (((4.65661287e-10f * fTemp617) + 1.0f) * float(iTemp616))));
			float fTemp618 = (ftbl41[int(((fConst5 * ((0.449999988f * (fRec339[0] + 1.0f)) + (0.100000001f * fTemp614))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp614)), fRec18[0]));
			fRec342[0] = ((fTemp17 * fRec342[1]) + (4.65661287e-10f * (fTemp617 * fTemp18)));
			float fTemp619 = (fRec341[1] + (fConst3 * float(((2 * (fRec342[0] > 0.0f)) + -1))));
			fRec341[0] = (fTemp619 - float(int(fTemp619)));
			float fTemp620 = float((fRec341[0] > 0.0f));
			float fTemp621 = (fRec341[0] * fTemp620);
			float fTemp622 = float((fRec341[0] < 0.0f));
			float fTemp623 = (fRec341[0] * fTemp622);
			float fTemp624 = ((fRec341[0] * ((fTemp620 * float((fTemp621 < 0.5f))) + (fTemp622 * float((fTemp623 > -0.5f))))) + ((float((fTemp621 > 0.5f)) * (1.0f - fTemp621)) + (float((fTemp623 < -0.5f)) * (-1.0f - fTemp623))));
			float fTemp625 = float((iTemp3 == 42));
			iVec86[0] = (fTemp625 < 0.5f);
			int iTemp626 = std::abs(((fTemp625 > 0.5f) * iVec86[1]));
			int iTemp627 = (iTemp626 >= iRec344[1]);
			int iTemp628 = (1 - (iTemp627 | iRec345[1]));
			iRec346[0] = ((iRec346[1] * iTemp628) + iTemp628);
			iRec345[0] = (float(iRec346[0]) >= fConst0);
			iRec344[0] = ((iRec345[0] | iTemp627) ? iTemp626 : iRec344[1]);
			iRec343[0] = (((iRec344[0] * iRec343[1]) + 1) % iConst4);
			ftbl42[(iRec343[0] + (2 * iRec344[0]))] = fTemp1;
			float fTemp629 = fRec14[((IOTA - iConst48) & 262143)];
			float fTemp630 = (1.0f - fTemp629);
			iVec87[0] = (fTemp630 < 0.5f);
			int iTemp631 = ((fTemp630 > 0.5f) * iVec87[1]);
			iRec348[0] = ((1103515245 * iRec348[1]) + 9239118);
			float fTemp632 = float(iRec348[0]);
			fRec347[0] = ((fRec347[1] * float((1 - iTemp631))) + (0.5f * (((4.65661287e-10f * fTemp632) + 1.0f) * float(iTemp631))));
			float fTemp633 = (ftbl42[int(((fConst5 * ((0.449999988f * (fRec347[0] + 1.0f)) + (0.100000001f * fTemp629))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp629)), fRec18[0]));
			fRec350[0] = ((fTemp17 * fRec350[1]) + (4.65661287e-10f * (fTemp632 * fTemp18)));
			float fTemp634 = (fRec349[1] + (fConst3 * float(((2 * (fRec350[0] > 0.0f)) + -1))));
			fRec349[0] = (fTemp634 - float(int(fTemp634)));
			float fTemp635 = float((fRec349[0] > 0.0f));
			float fTemp636 = (fRec349[0] * fTemp635);
			float fTemp637 = float((fRec349[0] < 0.0f));
			float fTemp638 = (fRec349[0] * fTemp637);
			float fTemp639 = ((fRec349[0] * ((fTemp635 * float((fTemp636 < 0.5f))) + (fTemp637 * float((fTemp638 > -0.5f))))) + ((float((fTemp636 > 0.5f)) * (1.0f - fTemp636)) + (float((fTemp638 < -0.5f)) * (-1.0f - fTemp638))));
			float fTemp640 = float((iTemp3 == 43));
			iVec88[0] = (fTemp640 < 0.5f);
			int iTemp641 = std::abs(((fTemp640 > 0.5f) * iVec88[1]));
			int iTemp642 = (iTemp641 >= iRec352[1]);
			int iTemp643 = (1 - (iTemp642 | iRec353[1]));
			iRec354[0] = ((iRec354[1] * iTemp643) + iTemp643);
			iRec353[0] = (float(iRec354[0]) >= fConst0);
			iRec352[0] = ((iRec353[0] | iTemp642) ? iTemp641 : iRec352[1]);
			iRec351[0] = (((iRec352[0] * iRec351[1]) + 1) % iConst4);
			ftbl43[(iRec351[0] + (2 * iRec352[0]))] = fTemp1;
			float fTemp644 = fRec14[((IOTA - iConst49) & 262143)];
			float fTemp645 = (1.0f - fTemp644);
			iVec89[0] = (fTemp645 < 0.5f);
			int iTemp646 = ((fTemp645 > 0.5f) * iVec89[1]);
			iRec356[0] = ((1103515245 * iRec356[1]) + 9459097);
			float fTemp647 = float(iRec356[0]);
			fRec355[0] = ((fRec355[1] * float((1 - iTemp646))) + (0.5f * (((4.65661287e-10f * fTemp647) + 1.0f) * float(iTemp646))));
			float fTemp648 = (ftbl43[int(((fConst5 * ((0.449999988f * (fRec355[0] + 1.0f)) + (0.100000001f * fTemp644))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp644)), fRec18[0]));
			fRec358[0] = ((fTemp17 * fRec358[1]) + (4.65661287e-10f * (fTemp647 * fTemp18)));
			float fTemp649 = (fRec357[1] + (fConst3 * float(((2 * (fRec358[0] > 0.0f)) + -1))));
			fRec357[0] = (fTemp649 - float(int(fTemp649)));
			float fTemp650 = float((fRec357[0] > 0.0f));
			float fTemp651 = (fRec357[0] * fTemp650);
			float fTemp652 = float((fRec357[0] < 0.0f));
			float fTemp653 = (fRec357[0] * fTemp652);
			float fTemp654 = ((fRec357[0] * ((fTemp650 * float((fTemp651 < 0.5f))) + (fTemp652 * float((fTemp653 > -0.5f))))) + ((float((fTemp651 > 0.5f)) * (1.0f - fTemp651)) + (float((fTemp653 < -0.5f)) * (-1.0f - fTemp653))));
			float fTemp655 = float((iTemp3 == 44));
			iVec90[0] = (fTemp655 < 0.5f);
			int iTemp656 = std::abs(((fTemp655 > 0.5f) * iVec90[1]));
			int iTemp657 = (iTemp656 >= iRec360[1]);
			int iTemp658 = (1 - (iTemp657 | iRec361[1]));
			iRec362[0] = ((iRec362[1] * iTemp658) + iTemp658);
			iRec361[0] = (float(iRec362[0]) >= fConst0);
			iRec360[0] = ((iRec361[0] | iTemp657) ? iTemp656 : iRec360[1]);
			iRec359[0] = (((iRec360[0] * iRec359[1]) + 1) % iConst4);
			ftbl44[(iRec359[0] + (2 * iRec360[0]))] = fTemp1;
			float fTemp659 = fRec14[((IOTA - iConst50) & 262143)];
			float fTemp660 = (1.0f - fTemp659);
			iVec91[0] = (fTemp660 < 0.5f);
			int iTemp661 = ((fTemp660 > 0.5f) * iVec91[1]);
			iRec364[0] = ((1103515245 * iRec364[1]) + 9679076);
			float fTemp662 = float(iRec364[0]);
			fRec363[0] = ((fRec363[1] * float((1 - iTemp661))) + (0.5f * (((4.65661287e-10f * fTemp662) + 1.0f) * float(iTemp661))));
			float fTemp663 = (ftbl44[int(((fConst5 * ((0.449999988f * (fRec363[0] + 1.0f)) + (0.100000001f * fTemp659))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp659)), fRec18[0]));
			fRec366[0] = ((fTemp17 * fRec366[1]) + (4.65661287e-10f * (fTemp662 * fTemp18)));
			float fTemp664 = (fRec365[1] + (fConst3 * float(((2 * (fRec366[0] > 0.0f)) + -1))));
			fRec365[0] = (fTemp664 - float(int(fTemp664)));
			float fTemp665 = float((fRec365[0] > 0.0f));
			float fTemp666 = (fRec365[0] * fTemp665);
			float fTemp667 = float((fRec365[0] < 0.0f));
			float fTemp668 = (fRec365[0] * fTemp667);
			float fTemp669 = ((fRec365[0] * ((fTemp665 * float((fTemp666 < 0.5f))) + (fTemp667 * float((fTemp668 > -0.5f))))) + ((float((fTemp666 > 0.5f)) * (1.0f - fTemp666)) + (float((fTemp668 < -0.5f)) * (-1.0f - fTemp668))));
			float fTemp670 = float((iTemp3 == 45));
			iVec92[0] = (fTemp670 < 0.5f);
			int iTemp671 = std::abs(((fTemp670 > 0.5f) * iVec92[1]));
			int iTemp672 = (iTemp671 >= iRec368[1]);
			int iTemp673 = (1 - (iTemp672 | iRec369[1]));
			iRec370[0] = ((iRec370[1] * iTemp673) + iTemp673);
			iRec369[0] = (float(iRec370[0]) >= fConst0);
			iRec368[0] = ((iRec369[0] | iTemp672) ? iTemp671 : iRec368[1]);
			iRec367[0] = (((iRec368[0] * iRec367[1]) + 1) % iConst4);
			ftbl45[(iRec367[0] + (2 * iRec368[0]))] = fTemp1;
			float fTemp674 = fRec14[((IOTA - iConst51) & 262143)];
			float fTemp675 = (1.0f - fTemp674);
			iVec93[0] = (fTemp675 < 0.5f);
			int iTemp676 = ((fTemp675 > 0.5f) * iVec93[1]);
			iRec372[0] = ((1103515245 * iRec372[1]) + 9899055);
			float fTemp677 = float(iRec372[0]);
			fRec371[0] = ((fRec371[1] * float((1 - iTemp676))) + (0.5f * (((4.65661287e-10f * fTemp677) + 1.0f) * float(iTemp676))));
			float fTemp678 = (ftbl45[int(((fConst5 * ((0.449999988f * (fRec371[0] + 1.0f)) + (0.100000001f * fTemp674))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp674)), fRec18[0]));
			fRec374[0] = ((fTemp17 * fRec374[1]) + (4.65661287e-10f * (fTemp677 * fTemp18)));
			float fTemp679 = (fRec373[1] + (fConst3 * float(((2 * (fRec374[0] > 0.0f)) + -1))));
			fRec373[0] = (fTemp679 - float(int(fTemp679)));
			float fTemp680 = float((fRec373[0] > 0.0f));
			float fTemp681 = (fRec373[0] * fTemp680);
			float fTemp682 = float((fRec373[0] < 0.0f));
			float fTemp683 = (fRec373[0] * fTemp682);
			float fTemp684 = ((fRec373[0] * ((fTemp680 * float((fTemp681 < 0.5f))) + (fTemp682 * float((fTemp683 > -0.5f))))) + ((float((fTemp681 > 0.5f)) * (1.0f - fTemp681)) + (float((fTemp683 < -0.5f)) * (-1.0f - fTemp683))));
			float fTemp685 = float((iTemp3 == 46));
			iVec94[0] = (fTemp685 < 0.5f);
			int iTemp686 = std::abs(((fTemp685 > 0.5f) * iVec94[1]));
			int iTemp687 = (iTemp686 >= iRec376[1]);
			int iTemp688 = (1 - (iTemp687 | iRec377[1]));
			iRec378[0] = ((iRec378[1] * iTemp688) + iTemp688);
			iRec377[0] = (float(iRec378[0]) >= fConst0);
			iRec376[0] = ((iRec377[0] | iTemp687) ? iTemp686 : iRec376[1]);
			iRec375[0] = (((iRec376[0] * iRec375[1]) + 1) % iConst4);
			ftbl46[(iRec375[0] + (2 * iRec376[0]))] = fTemp1;
			float fTemp689 = fRec14[((IOTA - iConst52) & 262143)];
			float fTemp690 = (1.0f - fTemp689);
			iVec95[0] = (fTemp690 < 0.5f);
			int iTemp691 = ((fTemp690 > 0.5f) * iVec95[1]);
			iRec380[0] = ((1103515245 * iRec380[1]) + 10119034);
			float fTemp692 = float(iRec380[0]);
			fRec379[0] = ((fRec379[1] * float((1 - iTemp691))) + (0.5f * (((4.65661287e-10f * fTemp692) + 1.0f) * float(iTemp691))));
			float fTemp693 = (ftbl46[int(((fConst5 * ((0.449999988f * (fRec379[0] + 1.0f)) + (0.100000001f * fTemp689))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp689)), fRec18[0]));
			fRec382[0] = ((fTemp17 * fRec382[1]) + (4.65661287e-10f * (fTemp692 * fTemp18)));
			float fTemp694 = (fRec381[1] + (fConst3 * float(((2 * (fRec382[0] > 0.0f)) + -1))));
			fRec381[0] = (fTemp694 - float(int(fTemp694)));
			float fTemp695 = float((fRec381[0] > 0.0f));
			float fTemp696 = (fRec381[0] * fTemp695);
			float fTemp697 = float((fRec381[0] < 0.0f));
			float fTemp698 = (fRec381[0] * fTemp697);
			float fTemp699 = ((fRec381[0] * ((fTemp695 * float((fTemp696 < 0.5f))) + (fTemp697 * float((fTemp698 > -0.5f))))) + ((float((fTemp696 > 0.5f)) * (1.0f - fTemp696)) + (float((fTemp698 < -0.5f)) * (-1.0f - fTemp698))));
			float fTemp700 = float((iTemp3 == 47));
			iVec96[0] = (fTemp700 < 0.5f);
			int iTemp701 = std::abs(((fTemp700 > 0.5f) * iVec96[1]));
			int iTemp702 = (iTemp701 >= iRec384[1]);
			int iTemp703 = (1 - (iTemp702 | iRec385[1]));
			iRec386[0] = ((iRec386[1] * iTemp703) + iTemp703);
			iRec385[0] = (float(iRec386[0]) >= fConst0);
			iRec384[0] = ((iRec385[0] | iTemp702) ? iTemp701 : iRec384[1]);
			iRec383[0] = (((iRec384[0] * iRec383[1]) + 1) % iConst4);
			ftbl47[(iRec383[0] + (2 * iRec384[0]))] = fTemp1;
			float fTemp704 = fRec14[((IOTA - iConst53) & 262143)];
			float fTemp705 = (1.0f - fTemp704);
			iVec97[0] = (fTemp705 < 0.5f);
			int iTemp706 = ((fTemp705 > 0.5f) * iVec97[1]);
			iRec388[0] = ((1103515245 * iRec388[1]) + 10339013);
			float fTemp707 = float(iRec388[0]);
			fRec387[0] = ((fRec387[1] * float((1 - iTemp706))) + (0.5f * (((4.65661287e-10f * fTemp707) + 1.0f) * float(iTemp706))));
			float fTemp708 = (ftbl47[int(((fConst5 * ((0.449999988f * (fRec387[0] + 1.0f)) + (0.100000001f * fTemp704))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp704)), fRec18[0]));
			fRec390[0] = ((fTemp17 * fRec390[1]) + (4.65661287e-10f * (fTemp707 * fTemp18)));
			float fTemp709 = (fRec389[1] + (fConst3 * float(((2 * (fRec390[0] > 0.0f)) + -1))));
			fRec389[0] = (fTemp709 - float(int(fTemp709)));
			float fTemp710 = float((fRec389[0] > 0.0f));
			float fTemp711 = (fRec389[0] * fTemp710);
			float fTemp712 = float((fRec389[0] < 0.0f));
			float fTemp713 = (fRec389[0] * fTemp712);
			float fTemp714 = ((fRec389[0] * ((fTemp710 * float((fTemp711 < 0.5f))) + (fTemp712 * float((fTemp713 > -0.5f))))) + ((float((fTemp711 > 0.5f)) * (1.0f - fTemp711)) + (float((fTemp713 < -0.5f)) * (-1.0f - fTemp713))));
			float fTemp715 = float((iTemp3 == 48));
			iVec98[0] = (fTemp715 < 0.5f);
			int iTemp716 = std::abs(((fTemp715 > 0.5f) * iVec98[1]));
			int iTemp717 = (iTemp716 >= iRec392[1]);
			int iTemp718 = (1 - (iTemp717 | iRec393[1]));
			iRec394[0] = ((iRec394[1] * iTemp718) + iTemp718);
			iRec393[0] = (float(iRec394[0]) >= fConst0);
			iRec392[0] = ((iRec393[0] | iTemp717) ? iTemp716 : iRec392[1]);
			iRec391[0] = (((iRec392[0] * iRec391[1]) + 1) % iConst4);
			ftbl48[(iRec391[0] + (2 * iRec392[0]))] = fTemp1;
			float fTemp719 = fRec14[((IOTA - iConst54) & 262143)];
			float fTemp720 = (1.0f - fTemp719);
			iVec99[0] = (fTemp720 < 0.5f);
			int iTemp721 = ((fTemp720 > 0.5f) * iVec99[1]);
			iRec396[0] = ((1103515245 * iRec396[1]) + 10558992);
			float fTemp722 = float(iRec396[0]);
			fRec395[0] = ((fRec395[1] * float((1 - iTemp721))) + (0.5f * (((4.65661287e-10f * fTemp722) + 1.0f) * float(iTemp721))));
			float fTemp723 = (ftbl48[int(((fConst5 * ((0.449999988f * (fRec395[0] + 1.0f)) + (0.100000001f * fTemp719))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp719)), fRec18[0]));
			fRec398[0] = ((fTemp17 * fRec398[1]) + (4.65661287e-10f * (fTemp722 * fTemp18)));
			float fTemp724 = (fRec397[1] + (fConst3 * float(((2 * (fRec398[0] > 0.0f)) + -1))));
			fRec397[0] = (fTemp724 - float(int(fTemp724)));
			float fTemp725 = float((fRec397[0] > 0.0f));
			float fTemp726 = (fRec397[0] * fTemp725);
			float fTemp727 = float((fRec397[0] < 0.0f));
			float fTemp728 = (fRec397[0] * fTemp727);
			float fTemp729 = ((fRec397[0] * ((fTemp725 * float((fTemp726 < 0.5f))) + (fTemp727 * float((fTemp728 > -0.5f))))) + ((float((fTemp726 > 0.5f)) * (1.0f - fTemp726)) + (float((fTemp728 < -0.5f)) * (-1.0f - fTemp728))));
			float fTemp730 = float((iTemp3 == 49));
			iVec100[0] = (fTemp730 < 0.5f);
			int iTemp731 = std::abs(((fTemp730 > 0.5f) * iVec100[1]));
			int iTemp732 = (iTemp731 >= iRec400[1]);
			int iTemp733 = (1 - (iTemp732 | iRec401[1]));
			iRec402[0] = ((iRec402[1] * iTemp733) + iTemp733);
			iRec401[0] = (float(iRec402[0]) >= fConst0);
			iRec400[0] = ((iRec401[0] | iTemp732) ? iTemp731 : iRec400[1]);
			iRec399[0] = (((iRec400[0] * iRec399[1]) + 1) % iConst4);
			ftbl49[(iRec399[0] + (2 * iRec400[0]))] = fTemp1;
			float fTemp734 = fRec14[((IOTA - iConst55) & 262143)];
			float fTemp735 = (1.0f - fTemp734);
			iVec101[0] = (fTemp735 < 0.5f);
			int iTemp736 = ((fTemp735 > 0.5f) * iVec101[1]);
			iRec404[0] = ((1103515245 * iRec404[1]) + 10778971);
			float fTemp737 = float(iRec404[0]);
			fRec403[0] = ((fRec403[1] * float((1 - iTemp736))) + (0.5f * (((4.65661287e-10f * fTemp737) + 1.0f) * float(iTemp736))));
			float fTemp738 = (ftbl49[int(((fConst5 * ((0.449999988f * (fRec403[0] + 1.0f)) + (0.100000001f * fTemp734))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp734)), fRec18[0]));
			fRec406[0] = ((fTemp17 * fRec406[1]) + (4.65661287e-10f * (fTemp737 * fTemp18)));
			float fTemp739 = (fRec405[1] + (fConst3 * float(((2 * (fRec406[0] > 0.0f)) + -1))));
			fRec405[0] = (fTemp739 - float(int(fTemp739)));
			float fTemp740 = float((fRec405[0] > 0.0f));
			float fTemp741 = (fRec405[0] * fTemp740);
			float fTemp742 = float((fRec405[0] < 0.0f));
			float fTemp743 = (fRec405[0] * fTemp742);
			float fTemp744 = ((fRec405[0] * ((fTemp740 * float((fTemp741 < 0.5f))) + (fTemp742 * float((fTemp743 > -0.5f))))) + ((float((fTemp741 > 0.5f)) * (1.0f - fTemp741)) + (float((fTemp743 < -0.5f)) * (-1.0f - fTemp743))));
			float fTemp745 = float((iTemp3 == 50));
			iVec102[0] = (fTemp745 < 0.5f);
			int iTemp746 = std::abs(((fTemp745 > 0.5f) * iVec102[1]));
			int iTemp747 = (iTemp746 >= iRec408[1]);
			int iTemp748 = (1 - (iTemp747 | iRec409[1]));
			iRec410[0] = ((iRec410[1] * iTemp748) + iTemp748);
			iRec409[0] = (float(iRec410[0]) >= fConst0);
			iRec408[0] = ((iRec409[0] | iTemp747) ? iTemp746 : iRec408[1]);
			iRec407[0] = (((iRec408[0] * iRec407[1]) + 1) % iConst4);
			ftbl50[(iRec407[0] + (2 * iRec408[0]))] = fTemp1;
			float fTemp749 = fRec14[((IOTA - iConst56) & 262143)];
			float fTemp750 = (1.0f - fTemp749);
			iVec103[0] = (fTemp750 < 0.5f);
			int iTemp751 = ((fTemp750 > 0.5f) * iVec103[1]);
			iRec412[0] = ((1103515245 * iRec412[1]) + 10998950);
			float fTemp752 = float(iRec412[0]);
			fRec411[0] = ((fRec411[1] * float((1 - iTemp751))) + (0.5f * (((4.65661287e-10f * fTemp752) + 1.0f) * float(iTemp751))));
			float fTemp753 = (ftbl50[int(((fConst5 * ((0.449999988f * (fRec411[0] + 1.0f)) + (0.100000001f * fTemp749))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp749)), fRec18[0]));
			fRec414[0] = ((fTemp17 * fRec414[1]) + (4.65661287e-10f * (fTemp752 * fTemp18)));
			float fTemp754 = (fRec413[1] + (fConst3 * float(((2 * (fRec414[0] > 0.0f)) + -1))));
			fRec413[0] = (fTemp754 - float(int(fTemp754)));
			float fTemp755 = float((fRec413[0] > 0.0f));
			float fTemp756 = (fRec413[0] * fTemp755);
			float fTemp757 = float((fRec413[0] < 0.0f));
			float fTemp758 = (fRec413[0] * fTemp757);
			float fTemp759 = ((fRec413[0] * ((fTemp755 * float((fTemp756 < 0.5f))) + (fTemp757 * float((fTemp758 > -0.5f))))) + ((float((fTemp756 > 0.5f)) * (1.0f - fTemp756)) + (float((fTemp758 < -0.5f)) * (-1.0f - fTemp758))));
			float fTemp760 = float((iTemp3 == 51));
			iVec104[0] = (fTemp760 < 0.5f);
			int iTemp761 = std::abs(((fTemp760 > 0.5f) * iVec104[1]));
			int iTemp762 = (iTemp761 >= iRec416[1]);
			int iTemp763 = (1 - (iTemp762 | iRec417[1]));
			iRec418[0] = ((iRec418[1] * iTemp763) + iTemp763);
			iRec417[0] = (float(iRec418[0]) >= fConst0);
			iRec416[0] = ((iRec417[0] | iTemp762) ? iTemp761 : iRec416[1]);
			iRec415[0] = (((iRec416[0] * iRec415[1]) + 1) % iConst4);
			ftbl51[(iRec415[0] + (2 * iRec416[0]))] = fTemp1;
			float fTemp764 = fRec14[((IOTA - iConst57) & 262143)];
			float fTemp765 = (1.0f - fTemp764);
			iVec105[0] = (fTemp765 < 0.5f);
			int iTemp766 = ((fTemp765 > 0.5f) * iVec105[1]);
			iRec420[0] = ((1103515245 * iRec420[1]) + 11218929);
			float fTemp767 = float(iRec420[0]);
			fRec419[0] = ((fRec419[1] * float((1 - iTemp766))) + (0.5f * (((4.65661287e-10f * fTemp767) + 1.0f) * float(iTemp766))));
			float fTemp768 = (ftbl51[int(((fConst5 * ((0.449999988f * (fRec419[0] + 1.0f)) + (0.100000001f * fTemp764))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp764)), fRec18[0]));
			fRec422[0] = ((fTemp17 * fRec422[1]) + (4.65661287e-10f * (fTemp767 * fTemp18)));
			float fTemp769 = (fRec421[1] + (fConst3 * float(((2 * (fRec422[0] > 0.0f)) + -1))));
			fRec421[0] = (fTemp769 - float(int(fTemp769)));
			float fTemp770 = float((fRec421[0] > 0.0f));
			float fTemp771 = (fRec421[0] * fTemp770);
			float fTemp772 = float((fRec421[0] < 0.0f));
			float fTemp773 = (fRec421[0] * fTemp772);
			float fTemp774 = ((fRec421[0] * ((fTemp770 * float((fTemp771 < 0.5f))) + (fTemp772 * float((fTemp773 > -0.5f))))) + ((float((fTemp771 > 0.5f)) * (1.0f - fTemp771)) + (float((fTemp773 < -0.5f)) * (-1.0f - fTemp773))));
			float fTemp775 = float((iTemp3 == 52));
			iVec106[0] = (fTemp775 < 0.5f);
			int iTemp776 = std::abs(((fTemp775 > 0.5f) * iVec106[1]));
			int iTemp777 = (iTemp776 >= iRec424[1]);
			int iTemp778 = (1 - (iTemp777 | iRec425[1]));
			iRec426[0] = ((iRec426[1] * iTemp778) + iTemp778);
			iRec425[0] = (float(iRec426[0]) >= fConst0);
			iRec424[0] = ((iRec425[0] | iTemp777) ? iTemp776 : iRec424[1]);
			iRec423[0] = (((iRec424[0] * iRec423[1]) + 1) % iConst4);
			ftbl52[(iRec423[0] + (2 * iRec424[0]))] = fTemp1;
			float fTemp779 = fRec14[((IOTA - iConst58) & 262143)];
			float fTemp780 = (1.0f - fTemp779);
			iVec107[0] = (fTemp780 < 0.5f);
			int iTemp781 = ((fTemp780 > 0.5f) * iVec107[1]);
			iRec428[0] = ((1103515245 * iRec428[1]) + 11438908);
			float fTemp782 = float(iRec428[0]);
			fRec427[0] = ((fRec427[1] * float((1 - iTemp781))) + (0.5f * (((4.65661287e-10f * fTemp782) + 1.0f) * float(iTemp781))));
			float fTemp783 = (ftbl52[int(((fConst5 * ((0.449999988f * (fRec427[0] + 1.0f)) + (0.100000001f * fTemp779))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp779)), fRec18[0]));
			fRec430[0] = ((fTemp17 * fRec430[1]) + (4.65661287e-10f * (fTemp782 * fTemp18)));
			float fTemp784 = (fRec429[1] + (fConst3 * float(((2 * (fRec430[0] > 0.0f)) + -1))));
			fRec429[0] = (fTemp784 - float(int(fTemp784)));
			float fTemp785 = float((fRec429[0] > 0.0f));
			float fTemp786 = (fRec429[0] * fTemp785);
			float fTemp787 = float((fRec429[0] < 0.0f));
			float fTemp788 = (fRec429[0] * fTemp787);
			float fTemp789 = ((fRec429[0] * ((fTemp785 * float((fTemp786 < 0.5f))) + (fTemp787 * float((fTemp788 > -0.5f))))) + ((float((fTemp786 > 0.5f)) * (1.0f - fTemp786)) + (float((fTemp788 < -0.5f)) * (-1.0f - fTemp788))));
			float fTemp790 = float((iTemp3 == 53));
			iVec108[0] = (fTemp790 < 0.5f);
			int iTemp791 = std::abs(((fTemp790 > 0.5f) * iVec108[1]));
			int iTemp792 = (iTemp791 >= iRec432[1]);
			int iTemp793 = (1 - (iTemp792 | iRec433[1]));
			iRec434[0] = ((iRec434[1] * iTemp793) + iTemp793);
			iRec433[0] = (float(iRec434[0]) >= fConst0);
			iRec432[0] = ((iRec433[0] | iTemp792) ? iTemp791 : iRec432[1]);
			iRec431[0] = (((iRec432[0] * iRec431[1]) + 1) % iConst4);
			ftbl53[(iRec431[0] + (2 * iRec432[0]))] = fTemp1;
			float fTemp794 = fRec14[((IOTA - iConst59) & 262143)];
			float fTemp795 = (1.0f - fTemp794);
			iVec109[0] = (fTemp795 < 0.5f);
			int iTemp796 = ((fTemp795 > 0.5f) * iVec109[1]);
			iRec436[0] = ((1103515245 * iRec436[1]) + 11658887);
			float fTemp797 = float(iRec436[0]);
			fRec435[0] = ((fRec435[1] * float((1 - iTemp796))) + (0.5f * (((4.65661287e-10f * fTemp797) + 1.0f) * float(iTemp796))));
			float fTemp798 = (ftbl53[int(((fConst5 * ((0.449999988f * (fRec435[0] + 1.0f)) + (0.100000001f * fTemp794))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp794)), fRec18[0]));
			fRec438[0] = ((fTemp17 * fRec438[1]) + (4.65661287e-10f * (fTemp797 * fTemp18)));
			float fTemp799 = (fRec437[1] + (fConst3 * float(((2 * (fRec438[0] > 0.0f)) + -1))));
			fRec437[0] = (fTemp799 - float(int(fTemp799)));
			float fTemp800 = float((fRec437[0] > 0.0f));
			float fTemp801 = (fRec437[0] * fTemp800);
			float fTemp802 = float((fRec437[0] < 0.0f));
			float fTemp803 = (fRec437[0] * fTemp802);
			float fTemp804 = ((fRec437[0] * ((fTemp800 * float((fTemp801 < 0.5f))) + (fTemp802 * float((fTemp803 > -0.5f))))) + ((float((fTemp801 > 0.5f)) * (1.0f - fTemp801)) + (float((fTemp803 < -0.5f)) * (-1.0f - fTemp803))));
			float fTemp805 = float((iTemp3 == 54));
			iVec110[0] = (fTemp805 < 0.5f);
			int iTemp806 = std::abs(((fTemp805 > 0.5f) * iVec110[1]));
			int iTemp807 = (iTemp806 >= iRec440[1]);
			int iTemp808 = (1 - (iTemp807 | iRec441[1]));
			iRec442[0] = ((iRec442[1] * iTemp808) + iTemp808);
			iRec441[0] = (float(iRec442[0]) >= fConst0);
			iRec440[0] = ((iRec441[0] | iTemp807) ? iTemp806 : iRec440[1]);
			iRec439[0] = (((iRec440[0] * iRec439[1]) + 1) % iConst4);
			ftbl54[(iRec439[0] + (2 * iRec440[0]))] = fTemp1;
			float fTemp809 = fRec14[((IOTA - iConst60) & 262143)];
			float fTemp810 = (1.0f - fTemp809);
			iVec111[0] = (fTemp810 < 0.5f);
			int iTemp811 = ((fTemp810 > 0.5f) * iVec111[1]);
			iRec444[0] = ((1103515245 * iRec444[1]) + 11878866);
			float fTemp812 = float(iRec444[0]);
			fRec443[0] = ((fRec443[1] * float((1 - iTemp811))) + (0.5f * (((4.65661287e-10f * fTemp812) + 1.0f) * float(iTemp811))));
			float fTemp813 = (ftbl54[int(((fConst5 * ((0.449999988f * (fRec443[0] + 1.0f)) + (0.100000001f * fTemp809))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp809)), fRec18[0]));
			fRec446[0] = ((fTemp17 * fRec446[1]) + (4.65661287e-10f * (fTemp812 * fTemp18)));
			float fTemp814 = (fRec445[1] + (fConst3 * float(((2 * (fRec446[0] > 0.0f)) + -1))));
			fRec445[0] = (fTemp814 - float(int(fTemp814)));
			float fTemp815 = float((fRec445[0] > 0.0f));
			float fTemp816 = (fRec445[0] * fTemp815);
			float fTemp817 = float((fRec445[0] < 0.0f));
			float fTemp818 = (fRec445[0] * fTemp817);
			float fTemp819 = ((fRec445[0] * ((fTemp815 * float((fTemp816 < 0.5f))) + (fTemp817 * float((fTemp818 > -0.5f))))) + ((float((fTemp816 > 0.5f)) * (1.0f - fTemp816)) + (float((fTemp818 < -0.5f)) * (-1.0f - fTemp818))));
			float fTemp820 = float((iTemp3 == 55));
			iVec112[0] = (fTemp820 < 0.5f);
			int iTemp821 = std::abs(((fTemp820 > 0.5f) * iVec112[1]));
			int iTemp822 = (iTemp821 >= iRec448[1]);
			int iTemp823 = (1 - (iTemp822 | iRec449[1]));
			iRec450[0] = ((iRec450[1] * iTemp823) + iTemp823);
			iRec449[0] = (float(iRec450[0]) >= fConst0);
			iRec448[0] = ((iRec449[0] | iTemp822) ? iTemp821 : iRec448[1]);
			iRec447[0] = (((iRec448[0] * iRec447[1]) + 1) % iConst4);
			ftbl55[(iRec447[0] + (2 * iRec448[0]))] = fTemp1;
			float fTemp824 = fRec14[((IOTA - iConst61) & 262143)];
			float fTemp825 = (1.0f - fTemp824);
			iVec113[0] = (fTemp825 < 0.5f);
			int iTemp826 = ((fTemp825 > 0.5f) * iVec113[1]);
			iRec452[0] = ((1103515245 * iRec452[1]) + 12098845);
			float fTemp827 = float(iRec452[0]);
			fRec451[0] = ((fRec451[1] * float((1 - iTemp826))) + (0.5f * (((4.65661287e-10f * fTemp827) + 1.0f) * float(iTemp826))));
			float fTemp828 = (ftbl55[int(((fConst5 * ((0.449999988f * (fRec451[0] + 1.0f)) + (0.100000001f * fTemp824))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp824)), fRec18[0]));
			fRec454[0] = ((fTemp17 * fRec454[1]) + (4.65661287e-10f * (fTemp827 * fTemp18)));
			float fTemp829 = (fRec453[1] + (fConst3 * float(((2 * (fRec454[0] > 0.0f)) + -1))));
			fRec453[0] = (fTemp829 - float(int(fTemp829)));
			float fTemp830 = float((fRec453[0] > 0.0f));
			float fTemp831 = (fRec453[0] * fTemp830);
			float fTemp832 = float((fRec453[0] < 0.0f));
			float fTemp833 = (fRec453[0] * fTemp832);
			float fTemp834 = ((fRec453[0] * ((fTemp830 * float((fTemp831 < 0.5f))) + (fTemp832 * float((fTemp833 > -0.5f))))) + ((float((fTemp831 > 0.5f)) * (1.0f - fTemp831)) + (float((fTemp833 < -0.5f)) * (-1.0f - fTemp833))));
			float fTemp835 = float((iTemp3 == 56));
			iVec114[0] = (fTemp835 < 0.5f);
			int iTemp836 = std::abs(((fTemp835 > 0.5f) * iVec114[1]));
			int iTemp837 = (iTemp836 >= iRec456[1]);
			int iTemp838 = (1 - (iTemp837 | iRec457[1]));
			iRec458[0] = ((iRec458[1] * iTemp838) + iTemp838);
			iRec457[0] = (float(iRec458[0]) >= fConst0);
			iRec456[0] = ((iRec457[0] | iTemp837) ? iTemp836 : iRec456[1]);
			iRec455[0] = (((iRec456[0] * iRec455[1]) + 1) % iConst4);
			ftbl56[(iRec455[0] + (2 * iRec456[0]))] = fTemp1;
			float fTemp839 = fRec14[((IOTA - iConst62) & 262143)];
			float fTemp840 = (1.0f - fTemp839);
			iVec115[0] = (fTemp840 < 0.5f);
			int iTemp841 = ((fTemp840 > 0.5f) * iVec115[1]);
			iRec460[0] = ((1103515245 * iRec460[1]) + 12318824);
			float fTemp842 = float(iRec460[0]);
			fRec459[0] = ((fRec459[1] * float((1 - iTemp841))) + (0.5f * (((4.65661287e-10f * fTemp842) + 1.0f) * float(iTemp841))));
			float fTemp843 = (ftbl56[int(((fConst5 * ((0.449999988f * (fRec459[0] + 1.0f)) + (0.100000001f * fTemp839))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp839)), fRec18[0]));
			fRec462[0] = ((fTemp17 * fRec462[1]) + (4.65661287e-10f * (fTemp842 * fTemp18)));
			float fTemp844 = (fRec461[1] + (fConst3 * float(((2 * (fRec462[0] > 0.0f)) + -1))));
			fRec461[0] = (fTemp844 - float(int(fTemp844)));
			float fTemp845 = float((fRec461[0] > 0.0f));
			float fTemp846 = (fRec461[0] * fTemp845);
			float fTemp847 = float((fRec461[0] < 0.0f));
			float fTemp848 = (fRec461[0] * fTemp847);
			float fTemp849 = ((fRec461[0] * ((fTemp845 * float((fTemp846 < 0.5f))) + (fTemp847 * float((fTemp848 > -0.5f))))) + ((float((fTemp846 > 0.5f)) * (1.0f - fTemp846)) + (float((fTemp848 < -0.5f)) * (-1.0f - fTemp848))));
			float fTemp850 = float((iTemp3 == 57));
			iVec116[0] = (fTemp850 < 0.5f);
			int iTemp851 = std::abs(((fTemp850 > 0.5f) * iVec116[1]));
			int iTemp852 = (iTemp851 >= iRec464[1]);
			int iTemp853 = (1 - (iTemp852 | iRec465[1]));
			iRec466[0] = ((iRec466[1] * iTemp853) + iTemp853);
			iRec465[0] = (float(iRec466[0]) >= fConst0);
			iRec464[0] = ((iRec465[0] | iTemp852) ? iTemp851 : iRec464[1]);
			iRec463[0] = (((iRec464[0] * iRec463[1]) + 1) % iConst4);
			ftbl57[(iRec463[0] + (2 * iRec464[0]))] = fTemp1;
			float fTemp854 = fRec14[((IOTA - iConst63) & 262143)];
			float fTemp855 = (1.0f - fTemp854);
			iVec117[0] = (fTemp855 < 0.5f);
			int iTemp856 = ((fTemp855 > 0.5f) * iVec117[1]);
			iRec468[0] = ((1103515245 * iRec468[1]) + 12538803);
			float fTemp857 = float(iRec468[0]);
			fRec467[0] = ((fRec467[1] * float((1 - iTemp856))) + (0.5f * (((4.65661287e-10f * fTemp857) + 1.0f) * float(iTemp856))));
			float fTemp858 = (ftbl57[int(((fConst5 * ((0.449999988f * (fRec467[0] + 1.0f)) + (0.100000001f * fTemp854))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp854)), fRec18[0]));
			fRec470[0] = ((fTemp17 * fRec470[1]) + (4.65661287e-10f * (fTemp857 * fTemp18)));
			float fTemp859 = (fRec469[1] + (fConst3 * float(((2 * (fRec470[0] > 0.0f)) + -1))));
			fRec469[0] = (fTemp859 - float(int(fTemp859)));
			float fTemp860 = float((fRec469[0] > 0.0f));
			float fTemp861 = (fRec469[0] * fTemp860);
			float fTemp862 = float((fRec469[0] < 0.0f));
			float fTemp863 = (fRec469[0] * fTemp862);
			float fTemp864 = ((fRec469[0] * ((fTemp860 * float((fTemp861 < 0.5f))) + (fTemp862 * float((fTemp863 > -0.5f))))) + ((float((fTemp861 > 0.5f)) * (1.0f - fTemp861)) + (float((fTemp863 < -0.5f)) * (-1.0f - fTemp863))));
			float fTemp865 = float((iTemp3 == 58));
			iVec118[0] = (fTemp865 < 0.5f);
			int iTemp866 = std::abs(((fTemp865 > 0.5f) * iVec118[1]));
			int iTemp867 = (iTemp866 >= iRec472[1]);
			int iTemp868 = (1 - (iTemp867 | iRec473[1]));
			iRec474[0] = ((iRec474[1] * iTemp868) + iTemp868);
			iRec473[0] = (float(iRec474[0]) >= fConst0);
			iRec472[0] = ((iRec473[0] | iTemp867) ? iTemp866 : iRec472[1]);
			iRec471[0] = (((iRec472[0] * iRec471[1]) + 1) % iConst4);
			ftbl58[(iRec471[0] + (2 * iRec472[0]))] = fTemp1;
			float fTemp869 = fRec14[((IOTA - iConst64) & 262143)];
			float fTemp870 = (1.0f - fTemp869);
			iVec119[0] = (fTemp870 < 0.5f);
			int iTemp871 = ((fTemp870 > 0.5f) * iVec119[1]);
			iRec476[0] = ((1103515245 * iRec476[1]) + 12758782);
			float fTemp872 = float(iRec476[0]);
			fRec475[0] = ((fRec475[1] * float((1 - iTemp871))) + (0.5f * (((4.65661287e-10f * fTemp872) + 1.0f) * float(iTemp871))));
			float fTemp873 = (ftbl58[int(((fConst5 * ((0.449999988f * (fRec475[0] + 1.0f)) + (0.100000001f * fTemp869))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp869)), fRec18[0]));
			fRec478[0] = ((fTemp17 * fRec478[1]) + (4.65661287e-10f * (fTemp872 * fTemp18)));
			float fTemp874 = (fRec477[1] + (fConst3 * float(((2 * (fRec478[0] > 0.0f)) + -1))));
			fRec477[0] = (fTemp874 - float(int(fTemp874)));
			float fTemp875 = float((fRec477[0] > 0.0f));
			float fTemp876 = (fRec477[0] * fTemp875);
			float fTemp877 = float((fRec477[0] < 0.0f));
			float fTemp878 = (fRec477[0] * fTemp877);
			float fTemp879 = ((fRec477[0] * ((fTemp875 * float((fTemp876 < 0.5f))) + (fTemp877 * float((fTemp878 > -0.5f))))) + ((float((fTemp876 > 0.5f)) * (1.0f - fTemp876)) + (float((fTemp878 < -0.5f)) * (-1.0f - fTemp878))));
			float fTemp880 = float((iTemp3 == 59));
			iVec120[0] = (fTemp880 < 0.5f);
			int iTemp881 = std::abs(((fTemp880 > 0.5f) * iVec120[1]));
			int iTemp882 = (iTemp881 >= iRec480[1]);
			int iTemp883 = (1 - (iTemp882 | iRec481[1]));
			iRec482[0] = ((iRec482[1] * iTemp883) + iTemp883);
			iRec481[0] = (float(iRec482[0]) >= fConst0);
			iRec480[0] = ((iRec481[0] | iTemp882) ? iTemp881 : iRec480[1]);
			iRec479[0] = (((iRec480[0] * iRec479[1]) + 1) % iConst4);
			ftbl59[(iRec479[0] + (2 * iRec480[0]))] = fTemp1;
			float fTemp884 = fRec14[((IOTA - iConst65) & 262143)];
			float fTemp885 = (1.0f - fTemp884);
			iVec121[0] = (fTemp885 < 0.5f);
			int iTemp886 = ((fTemp885 > 0.5f) * iVec121[1]);
			iRec484[0] = ((1103515245 * iRec484[1]) + 12978761);
			float fTemp887 = float(iRec484[0]);
			fRec483[0] = ((fRec483[1] * float((1 - iTemp886))) + (0.5f * (((4.65661287e-10f * fTemp887) + 1.0f) * float(iTemp886))));
			float fTemp888 = (ftbl59[int(((fConst5 * ((0.449999988f * (fRec483[0] + 1.0f)) + (0.100000001f * fTemp884))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp884)), fRec18[0]));
			fRec486[0] = ((fTemp17 * fRec486[1]) + (4.65661287e-10f * (fTemp887 * fTemp18)));
			float fTemp889 = (fRec485[1] + (fConst3 * float(((2 * (fRec486[0] > 0.0f)) + -1))));
			fRec485[0] = (fTemp889 - float(int(fTemp889)));
			float fTemp890 = float((fRec485[0] > 0.0f));
			float fTemp891 = (fRec485[0] * fTemp890);
			float fTemp892 = float((fRec485[0] < 0.0f));
			float fTemp893 = (fRec485[0] * fTemp892);
			float fTemp894 = ((fRec485[0] * ((fTemp890 * float((fTemp891 < 0.5f))) + (fTemp892 * float((fTemp893 > -0.5f))))) + ((float((fTemp891 > 0.5f)) * (1.0f - fTemp891)) + (float((fTemp893 < -0.5f)) * (-1.0f - fTemp893))));
			float fTemp895 = float((iTemp3 == 60));
			iVec122[0] = (fTemp895 < 0.5f);
			int iTemp896 = std::abs(((fTemp895 > 0.5f) * iVec122[1]));
			int iTemp897 = (iTemp896 >= iRec488[1]);
			int iTemp898 = (1 - (iTemp897 | iRec489[1]));
			iRec490[0] = ((iRec490[1] * iTemp898) + iTemp898);
			iRec489[0] = (float(iRec490[0]) >= fConst0);
			iRec488[0] = ((iRec489[0] | iTemp897) ? iTemp896 : iRec488[1]);
			iRec487[0] = (((iRec488[0] * iRec487[1]) + 1) % iConst4);
			ftbl60[(iRec487[0] + (2 * iRec488[0]))] = fTemp1;
			float fTemp899 = fRec14[((IOTA - iConst66) & 262143)];
			float fTemp900 = (1.0f - fTemp899);
			iVec123[0] = (fTemp900 < 0.5f);
			int iTemp901 = ((fTemp900 > 0.5f) * iVec123[1]);
			iRec492[0] = ((1103515245 * iRec492[1]) + 13198740);
			float fTemp902 = float(iRec492[0]);
			fRec491[0] = ((fRec491[1] * float((1 - iTemp901))) + (0.5f * (((4.65661287e-10f * fTemp902) + 1.0f) * float(iTemp901))));
			float fTemp903 = (ftbl60[int(((fConst5 * ((0.449999988f * (fRec491[0] + 1.0f)) + (0.100000001f * fTemp899))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp899)), fRec18[0]));
			fRec494[0] = ((fTemp17 * fRec494[1]) + (4.65661287e-10f * (fTemp902 * fTemp18)));
			float fTemp904 = (fRec493[1] + (fConst3 * float(((2 * (fRec494[0] > 0.0f)) + -1))));
			fRec493[0] = (fTemp904 - float(int(fTemp904)));
			float fTemp905 = float((fRec493[0] > 0.0f));
			float fTemp906 = (fRec493[0] * fTemp905);
			float fTemp907 = float((fRec493[0] < 0.0f));
			float fTemp908 = (fRec493[0] * fTemp907);
			float fTemp909 = ((fRec493[0] * ((fTemp905 * float((fTemp906 < 0.5f))) + (fTemp907 * float((fTemp908 > -0.5f))))) + ((float((fTemp906 > 0.5f)) * (1.0f - fTemp906)) + (float((fTemp908 < -0.5f)) * (-1.0f - fTemp908))));
			float fTemp910 = float((iTemp3 == 61));
			iVec124[0] = (fTemp910 < 0.5f);
			int iTemp911 = std::abs(((fTemp910 > 0.5f) * iVec124[1]));
			int iTemp912 = (iTemp911 >= iRec496[1]);
			int iTemp913 = (1 - (iTemp912 | iRec497[1]));
			iRec498[0] = ((iRec498[1] * iTemp913) + iTemp913);
			iRec497[0] = (float(iRec498[0]) >= fConst0);
			iRec496[0] = ((iRec497[0] | iTemp912) ? iTemp911 : iRec496[1]);
			iRec495[0] = (((iRec496[0] * iRec495[1]) + 1) % iConst4);
			ftbl61[(iRec495[0] + (2 * iRec496[0]))] = fTemp1;
			float fTemp914 = fRec14[((IOTA - iConst67) & 262143)];
			float fTemp915 = (1.0f - fTemp914);
			iVec125[0] = (fTemp915 < 0.5f);
			int iTemp916 = ((fTemp915 > 0.5f) * iVec125[1]);
			iRec500[0] = ((1103515245 * iRec500[1]) + 13418719);
			float fTemp917 = float(iRec500[0]);
			fRec499[0] = ((fRec499[1] * float((1 - iTemp916))) + (0.5f * (((4.65661287e-10f * fTemp917) + 1.0f) * float(iTemp916))));
			float fTemp918 = (ftbl61[int(((fConst5 * ((0.449999988f * (fRec499[0] + 1.0f)) + (0.100000001f * fTemp914))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp914)), fRec18[0]));
			fRec502[0] = ((fTemp17 * fRec502[1]) + (4.65661287e-10f * (fTemp917 * fTemp18)));
			float fTemp919 = (fRec501[1] + (fConst3 * float(((2 * (fRec502[0] > 0.0f)) + -1))));
			fRec501[0] = (fTemp919 - float(int(fTemp919)));
			float fTemp920 = float((fRec501[0] > 0.0f));
			float fTemp921 = (fRec501[0] * fTemp920);
			float fTemp922 = float((fRec501[0] < 0.0f));
			float fTemp923 = (fRec501[0] * fTemp922);
			float fTemp924 = ((fRec501[0] * ((fTemp920 * float((fTemp921 < 0.5f))) + (fTemp922 * float((fTemp923 > -0.5f))))) + ((float((fTemp921 > 0.5f)) * (1.0f - fTemp921)) + (float((fTemp923 < -0.5f)) * (-1.0f - fTemp923))));
			float fTemp925 = float((iTemp3 == 62));
			iVec126[0] = (fTemp925 < 0.5f);
			int iTemp926 = std::abs(((fTemp925 > 0.5f) * iVec126[1]));
			int iTemp927 = (iTemp926 >= iRec504[1]);
			int iTemp928 = (1 - (iTemp927 | iRec505[1]));
			iRec506[0] = ((iRec506[1] * iTemp928) + iTemp928);
			iRec505[0] = (float(iRec506[0]) >= fConst0);
			iRec504[0] = ((iRec505[0] | iTemp927) ? iTemp926 : iRec504[1]);
			iRec503[0] = (((iRec504[0] * iRec503[1]) + 1) % iConst4);
			ftbl62[(iRec503[0] + (2 * iRec504[0]))] = fTemp1;
			float fTemp929 = fRec14[((IOTA - iConst68) & 262143)];
			float fTemp930 = (1.0f - fTemp929);
			iVec127[0] = (fTemp930 < 0.5f);
			int iTemp931 = ((fTemp930 > 0.5f) * iVec127[1]);
			iRec508[0] = ((1103515245 * iRec508[1]) + 13638698);
			float fTemp932 = float(iRec508[0]);
			fRec507[0] = ((fRec507[1] * float((1 - iTemp931))) + (0.5f * (((4.65661287e-10f * fTemp932) + 1.0f) * float(iTemp931))));
			float fTemp933 = (ftbl62[int(((fConst5 * ((0.449999988f * (fRec507[0] + 1.0f)) + (0.100000001f * fTemp929))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp929)), fRec18[0]));
			fRec510[0] = ((fTemp17 * fRec510[1]) + (4.65661287e-10f * (fTemp932 * fTemp18)));
			float fTemp934 = (fRec509[1] + (fConst3 * float(((2 * (fRec510[0] > 0.0f)) + -1))));
			fRec509[0] = (fTemp934 - float(int(fTemp934)));
			float fTemp935 = float((fRec509[0] > 0.0f));
			float fTemp936 = (fRec509[0] * fTemp935);
			float fTemp937 = float((fRec509[0] < 0.0f));
			float fTemp938 = (fRec509[0] * fTemp937);
			float fTemp939 = ((fRec509[0] * ((fTemp935 * float((fTemp936 < 0.5f))) + (fTemp937 * float((fTemp938 > -0.5f))))) + ((float((fTemp936 > 0.5f)) * (1.0f - fTemp936)) + (float((fTemp938 < -0.5f)) * (-1.0f - fTemp938))));
			float fTemp940 = float((iTemp3 == 63));
			iVec128[0] = (fTemp940 < 0.5f);
			int iTemp941 = std::abs(((fTemp940 > 0.5f) * iVec128[1]));
			int iTemp942 = (iTemp941 >= iRec512[1]);
			int iTemp943 = (1 - (iTemp942 | iRec513[1]));
			iRec514[0] = ((iRec514[1] * iTemp943) + iTemp943);
			iRec513[0] = (float(iRec514[0]) >= fConst0);
			iRec512[0] = ((iRec513[0] | iTemp942) ? iTemp941 : iRec512[1]);
			iRec511[0] = (((iRec512[0] * iRec511[1]) + 1) % iConst4);
			ftbl63[(iRec511[0] + (2 * iRec512[0]))] = fTemp1;
			float fTemp944 = fRec14[((IOTA - iConst69) & 262143)];
			float fTemp945 = (1.0f - fTemp944);
			iVec129[0] = (fTemp945 < 0.5f);
			int iTemp946 = ((fTemp945 > 0.5f) * iVec129[1]);
			iRec516[0] = ((1103515245 * iRec516[1]) + 13858677);
			float fTemp947 = float(iRec516[0]);
			fRec515[0] = ((fRec515[1] * float((1 - iTemp946))) + (0.5f * (((4.65661287e-10f * fTemp947) + 1.0f) * float(iTemp946))));
			float fTemp948 = (ftbl63[int(((fConst5 * ((0.449999988f * (fRec515[0] + 1.0f)) + (0.100000001f * fTemp944))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp944)), fRec18[0]));
			fRec518[0] = ((fTemp17 * fRec518[1]) + (4.65661287e-10f * (fTemp947 * fTemp18)));
			float fTemp949 = (fRec517[1] + (fConst3 * float(((2 * (fRec518[0] > 0.0f)) + -1))));
			fRec517[0] = (fTemp949 - float(int(fTemp949)));
			float fTemp950 = float((fRec517[0] > 0.0f));
			float fTemp951 = (fRec517[0] * fTemp950);
			float fTemp952 = float((fRec517[0] < 0.0f));
			float fTemp953 = (fRec517[0] * fTemp952);
			float fTemp954 = ((fRec517[0] * ((fTemp950 * float((fTemp951 < 0.5f))) + (fTemp952 * float((fTemp953 > -0.5f))))) + ((float((fTemp951 > 0.5f)) * (1.0f - fTemp951)) + (float((fTemp953 < -0.5f)) * (-1.0f - fTemp953))));
			float fTemp955 = float((iTemp3 == 64));
			iVec130[0] = (fTemp955 < 0.5f);
			int iTemp956 = std::abs(((fTemp955 > 0.5f) * iVec130[1]));
			int iTemp957 = (iTemp956 >= iRec520[1]);
			int iTemp958 = (1 - (iTemp957 | iRec521[1]));
			iRec522[0] = ((iRec522[1] * iTemp958) + iTemp958);
			iRec521[0] = (float(iRec522[0]) >= fConst0);
			iRec520[0] = ((iRec521[0] | iTemp957) ? iTemp956 : iRec520[1]);
			iRec519[0] = (((iRec520[0] * iRec519[1]) + 1) % iConst4);
			ftbl64[(iRec519[0] + (2 * iRec520[0]))] = fTemp1;
			float fTemp959 = fRec14[((IOTA - iConst70) & 262143)];
			float fTemp960 = (1.0f - fTemp959);
			iVec131[0] = (fTemp960 < 0.5f);
			int iTemp961 = ((fTemp960 > 0.5f) * iVec131[1]);
			iRec524[0] = ((1103515245 * iRec524[1]) + 14078656);
			float fTemp962 = float(iRec524[0]);
			fRec523[0] = ((fRec523[1] * float((1 - iTemp961))) + (0.5f * (((4.65661287e-10f * fTemp962) + 1.0f) * float(iTemp961))));
			float fTemp963 = (ftbl64[int(((fConst5 * ((0.449999988f * (fRec523[0] + 1.0f)) + (0.100000001f * fTemp959))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp959)), fRec18[0]));
			fRec526[0] = ((fTemp17 * fRec526[1]) + (4.65661287e-10f * (fTemp962 * fTemp18)));
			float fTemp964 = (fRec525[1] + (fConst3 * float(((2 * (fRec526[0] > 0.0f)) + -1))));
			fRec525[0] = (fTemp964 - float(int(fTemp964)));
			float fTemp965 = float((fRec525[0] > 0.0f));
			float fTemp966 = (fRec525[0] * fTemp965);
			float fTemp967 = float((fRec525[0] < 0.0f));
			float fTemp968 = (fRec525[0] * fTemp967);
			float fTemp969 = ((fRec525[0] * ((fTemp965 * float((fTemp966 < 0.5f))) + (fTemp967 * float((fTemp968 > -0.5f))))) + ((float((fTemp966 > 0.5f)) * (1.0f - fTemp966)) + (float((fTemp968 < -0.5f)) * (-1.0f - fTemp968))));
			float fTemp970 = float((iTemp3 == 65));
			iVec132[0] = (fTemp970 < 0.5f);
			int iTemp971 = std::abs(((fTemp970 > 0.5f) * iVec132[1]));
			int iTemp972 = (iTemp971 >= iRec528[1]);
			int iTemp973 = (1 - (iTemp972 | iRec529[1]));
			iRec530[0] = ((iRec530[1] * iTemp973) + iTemp973);
			iRec529[0] = (float(iRec530[0]) >= fConst0);
			iRec528[0] = ((iRec529[0] | iTemp972) ? iTemp971 : iRec528[1]);
			iRec527[0] = (((iRec528[0] * iRec527[1]) + 1) % iConst4);
			ftbl65[(iRec527[0] + (2 * iRec528[0]))] = fTemp1;
			float fTemp974 = fRec14[((IOTA - iConst71) & 262143)];
			float fTemp975 = (1.0f - fTemp974);
			iVec133[0] = (fTemp975 < 0.5f);
			int iTemp976 = ((fTemp975 > 0.5f) * iVec133[1]);
			iRec532[0] = ((1103515245 * iRec532[1]) + 14298635);
			float fTemp977 = float(iRec532[0]);
			fRec531[0] = ((fRec531[1] * float((1 - iTemp976))) + (0.5f * (((4.65661287e-10f * fTemp977) + 1.0f) * float(iTemp976))));
			float fTemp978 = (ftbl65[int(((fConst5 * ((0.449999988f * (fRec531[0] + 1.0f)) + (0.100000001f * fTemp974))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp974)), fRec18[0]));
			fRec534[0] = ((fTemp17 * fRec534[1]) + (4.65661287e-10f * (fTemp977 * fTemp18)));
			float fTemp979 = (fRec533[1] + (fConst3 * float(((2 * (fRec534[0] > 0.0f)) + -1))));
			fRec533[0] = (fTemp979 - float(int(fTemp979)));
			float fTemp980 = float((fRec533[0] > 0.0f));
			float fTemp981 = (fRec533[0] * fTemp980);
			float fTemp982 = float((fRec533[0] < 0.0f));
			float fTemp983 = (fRec533[0] * fTemp982);
			float fTemp984 = ((fRec533[0] * ((fTemp980 * float((fTemp981 < 0.5f))) + (fTemp982 * float((fTemp983 > -0.5f))))) + ((float((fTemp981 > 0.5f)) * (1.0f - fTemp981)) + (float((fTemp983 < -0.5f)) * (-1.0f - fTemp983))));
			float fTemp985 = float((iTemp3 == 66));
			iVec134[0] = (fTemp985 < 0.5f);
			int iTemp986 = std::abs(((fTemp985 > 0.5f) * iVec134[1]));
			int iTemp987 = (iTemp986 >= iRec536[1]);
			int iTemp988 = (1 - (iTemp987 | iRec537[1]));
			iRec538[0] = ((iRec538[1] * iTemp988) + iTemp988);
			iRec537[0] = (float(iRec538[0]) >= fConst0);
			iRec536[0] = ((iRec537[0] | iTemp987) ? iTemp986 : iRec536[1]);
			iRec535[0] = (((iRec536[0] * iRec535[1]) + 1) % iConst4);
			ftbl66[(iRec535[0] + (2 * iRec536[0]))] = fTemp1;
			float fTemp989 = fRec14[((IOTA - iConst72) & 262143)];
			float fTemp990 = (1.0f - fTemp989);
			iVec135[0] = (fTemp990 < 0.5f);
			int iTemp991 = ((fTemp990 > 0.5f) * iVec135[1]);
			iRec540[0] = ((1103515245 * iRec540[1]) + 14518614);
			float fTemp992 = float(iRec540[0]);
			fRec539[0] = ((fRec539[1] * float((1 - iTemp991))) + (0.5f * (((4.65661287e-10f * fTemp992) + 1.0f) * float(iTemp991))));
			float fTemp993 = (ftbl66[int(((fConst5 * ((0.449999988f * (fRec539[0] + 1.0f)) + (0.100000001f * fTemp989))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp989)), fRec18[0]));
			fRec542[0] = ((fTemp17 * fRec542[1]) + (4.65661287e-10f * (fTemp992 * fTemp18)));
			float fTemp994 = (fRec541[1] + (fConst3 * float(((2 * (fRec542[0] > 0.0f)) + -1))));
			fRec541[0] = (fTemp994 - float(int(fTemp994)));
			float fTemp995 = float((fRec541[0] > 0.0f));
			float fTemp996 = (fRec541[0] * fTemp995);
			float fTemp997 = float((fRec541[0] < 0.0f));
			float fTemp998 = (fRec541[0] * fTemp997);
			float fTemp999 = ((fRec541[0] * ((fTemp995 * float((fTemp996 < 0.5f))) + (fTemp997 * float((fTemp998 > -0.5f))))) + ((float((fTemp996 > 0.5f)) * (1.0f - fTemp996)) + (float((fTemp998 < -0.5f)) * (-1.0f - fTemp998))));
			float fTemp1000 = float((iTemp3 == 67));
			iVec136[0] = (fTemp1000 < 0.5f);
			int iTemp1001 = std::abs(((fTemp1000 > 0.5f) * iVec136[1]));
			int iTemp1002 = (iTemp1001 >= iRec544[1]);
			int iTemp1003 = (1 - (iTemp1002 | iRec545[1]));
			iRec546[0] = ((iRec546[1] * iTemp1003) + iTemp1003);
			iRec545[0] = (float(iRec546[0]) >= fConst0);
			iRec544[0] = ((iRec545[0] | iTemp1002) ? iTemp1001 : iRec544[1]);
			iRec543[0] = (((iRec544[0] * iRec543[1]) + 1) % iConst4);
			ftbl67[(iRec543[0] + (2 * iRec544[0]))] = fTemp1;
			float fTemp1004 = fRec14[((IOTA - iConst73) & 262143)];
			float fTemp1005 = (1.0f - fTemp1004);
			iVec137[0] = (fTemp1005 < 0.5f);
			int iTemp1006 = ((fTemp1005 > 0.5f) * iVec137[1]);
			iRec548[0] = ((1103515245 * iRec548[1]) + 14738593);
			float fTemp1007 = float(iRec548[0]);
			fRec547[0] = ((fRec547[1] * float((1 - iTemp1006))) + (0.5f * (((4.65661287e-10f * fTemp1007) + 1.0f) * float(iTemp1006))));
			float fTemp1008 = (ftbl67[int(((fConst5 * ((0.449999988f * (fRec547[0] + 1.0f)) + (0.100000001f * fTemp1004))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1004)), fRec18[0]));
			fRec550[0] = ((fTemp17 * fRec550[1]) + (4.65661287e-10f * (fTemp1007 * fTemp18)));
			float fTemp1009 = (fRec549[1] + (fConst3 * float(((2 * (fRec550[0] > 0.0f)) + -1))));
			fRec549[0] = (fTemp1009 - float(int(fTemp1009)));
			float fTemp1010 = float((fRec549[0] > 0.0f));
			float fTemp1011 = (fRec549[0] * fTemp1010);
			float fTemp1012 = float((fRec549[0] < 0.0f));
			float fTemp1013 = (fRec549[0] * fTemp1012);
			float fTemp1014 = ((fRec549[0] * ((fTemp1010 * float((fTemp1011 < 0.5f))) + (fTemp1012 * float((fTemp1013 > -0.5f))))) + ((float((fTemp1011 > 0.5f)) * (1.0f - fTemp1011)) + (float((fTemp1013 < -0.5f)) * (-1.0f - fTemp1013))));
			float fTemp1015 = float((iTemp3 == 68));
			iVec138[0] = (fTemp1015 < 0.5f);
			int iTemp1016 = std::abs(((fTemp1015 > 0.5f) * iVec138[1]));
			int iTemp1017 = (iTemp1016 >= iRec552[1]);
			int iTemp1018 = (1 - (iTemp1017 | iRec553[1]));
			iRec554[0] = ((iRec554[1] * iTemp1018) + iTemp1018);
			iRec553[0] = (float(iRec554[0]) >= fConst0);
			iRec552[0] = ((iRec553[0] | iTemp1017) ? iTemp1016 : iRec552[1]);
			iRec551[0] = (((iRec552[0] * iRec551[1]) + 1) % iConst4);
			ftbl68[(iRec551[0] + (2 * iRec552[0]))] = fTemp1;
			float fTemp1019 = fRec14[((IOTA - iConst74) & 262143)];
			float fTemp1020 = (1.0f - fTemp1019);
			iVec139[0] = (fTemp1020 < 0.5f);
			int iTemp1021 = ((fTemp1020 > 0.5f) * iVec139[1]);
			iRec556[0] = ((1103515245 * iRec556[1]) + 14958572);
			float fTemp1022 = float(iRec556[0]);
			fRec555[0] = ((fRec555[1] * float((1 - iTemp1021))) + (0.5f * (((4.65661287e-10f * fTemp1022) + 1.0f) * float(iTemp1021))));
			float fTemp1023 = (ftbl68[int(((fConst5 * ((0.449999988f * (fRec555[0] + 1.0f)) + (0.100000001f * fTemp1019))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1019)), fRec18[0]));
			fRec558[0] = ((fTemp17 * fRec558[1]) + (4.65661287e-10f * (fTemp1022 * fTemp18)));
			float fTemp1024 = (fRec557[1] + (fConst3 * float(((2 * (fRec558[0] > 0.0f)) + -1))));
			fRec557[0] = (fTemp1024 - float(int(fTemp1024)));
			float fTemp1025 = float((fRec557[0] > 0.0f));
			float fTemp1026 = (fRec557[0] * fTemp1025);
			float fTemp1027 = float((fRec557[0] < 0.0f));
			float fTemp1028 = (fRec557[0] * fTemp1027);
			float fTemp1029 = ((fRec557[0] * ((fTemp1025 * float((fTemp1026 < 0.5f))) + (fTemp1027 * float((fTemp1028 > -0.5f))))) + ((float((fTemp1026 > 0.5f)) * (1.0f - fTemp1026)) + (float((fTemp1028 < -0.5f)) * (-1.0f - fTemp1028))));
			float fTemp1030 = float((iTemp3 == 69));
			iVec140[0] = (fTemp1030 < 0.5f);
			int iTemp1031 = std::abs(((fTemp1030 > 0.5f) * iVec140[1]));
			int iTemp1032 = (iTemp1031 >= iRec560[1]);
			int iTemp1033 = (1 - (iTemp1032 | iRec561[1]));
			iRec562[0] = ((iRec562[1] * iTemp1033) + iTemp1033);
			iRec561[0] = (float(iRec562[0]) >= fConst0);
			iRec560[0] = ((iRec561[0] | iTemp1032) ? iTemp1031 : iRec560[1]);
			iRec559[0] = (((iRec560[0] * iRec559[1]) + 1) % iConst4);
			ftbl69[(iRec559[0] + (2 * iRec560[0]))] = fTemp1;
			float fTemp1034 = fRec14[((IOTA - iConst75) & 262143)];
			float fTemp1035 = (1.0f - fTemp1034);
			iVec141[0] = (fTemp1035 < 0.5f);
			int iTemp1036 = ((fTemp1035 > 0.5f) * iVec141[1]);
			iRec564[0] = ((1103515245 * iRec564[1]) + 15178551);
			float fTemp1037 = float(iRec564[0]);
			fRec563[0] = ((fRec563[1] * float((1 - iTemp1036))) + (0.5f * (((4.65661287e-10f * fTemp1037) + 1.0f) * float(iTemp1036))));
			float fTemp1038 = (ftbl69[int(((fConst5 * ((0.449999988f * (fRec563[0] + 1.0f)) + (0.100000001f * fTemp1034))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1034)), fRec18[0]));
			fRec566[0] = ((fTemp17 * fRec566[1]) + (4.65661287e-10f * (fTemp1037 * fTemp18)));
			float fTemp1039 = (fRec565[1] + (fConst3 * float(((2 * (fRec566[0] > 0.0f)) + -1))));
			fRec565[0] = (fTemp1039 - float(int(fTemp1039)));
			float fTemp1040 = float((fRec565[0] > 0.0f));
			float fTemp1041 = (fRec565[0] * fTemp1040);
			float fTemp1042 = float((fRec565[0] < 0.0f));
			float fTemp1043 = (fRec565[0] * fTemp1042);
			float fTemp1044 = ((fRec565[0] * ((fTemp1040 * float((fTemp1041 < 0.5f))) + (fTemp1042 * float((fTemp1043 > -0.5f))))) + ((float((fTemp1041 > 0.5f)) * (1.0f - fTemp1041)) + (float((fTemp1043 < -0.5f)) * (-1.0f - fTemp1043))));
			float fTemp1045 = float((iTemp3 == 70));
			iVec142[0] = (fTemp1045 < 0.5f);
			int iTemp1046 = std::abs(((fTemp1045 > 0.5f) * iVec142[1]));
			int iTemp1047 = (iTemp1046 >= iRec568[1]);
			int iTemp1048 = (1 - (iTemp1047 | iRec569[1]));
			iRec570[0] = ((iRec570[1] * iTemp1048) + iTemp1048);
			iRec569[0] = (float(iRec570[0]) >= fConst0);
			iRec568[0] = ((iRec569[0] | iTemp1047) ? iTemp1046 : iRec568[1]);
			iRec567[0] = (((iRec568[0] * iRec567[1]) + 1) % iConst4);
			ftbl70[(iRec567[0] + (2 * iRec568[0]))] = fTemp1;
			float fTemp1049 = fRec14[((IOTA - iConst76) & 262143)];
			float fTemp1050 = (1.0f - fTemp1049);
			iVec143[0] = (fTemp1050 < 0.5f);
			int iTemp1051 = ((fTemp1050 > 0.5f) * iVec143[1]);
			iRec572[0] = ((1103515245 * iRec572[1]) + 15398530);
			float fTemp1052 = float(iRec572[0]);
			fRec571[0] = ((fRec571[1] * float((1 - iTemp1051))) + (0.5f * (((4.65661287e-10f * fTemp1052) + 1.0f) * float(iTemp1051))));
			float fTemp1053 = (ftbl70[int(((fConst5 * ((0.449999988f * (fRec571[0] + 1.0f)) + (0.100000001f * fTemp1049))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1049)), fRec18[0]));
			fRec574[0] = ((fTemp17 * fRec574[1]) + (4.65661287e-10f * (fTemp1052 * fTemp18)));
			float fTemp1054 = (fRec573[1] + (fConst3 * float(((2 * (fRec574[0] > 0.0f)) + -1))));
			fRec573[0] = (fTemp1054 - float(int(fTemp1054)));
			float fTemp1055 = float((fRec573[0] > 0.0f));
			float fTemp1056 = (fRec573[0] * fTemp1055);
			float fTemp1057 = float((fRec573[0] < 0.0f));
			float fTemp1058 = (fRec573[0] * fTemp1057);
			float fTemp1059 = ((fRec573[0] * ((fTemp1055 * float((fTemp1056 < 0.5f))) + (fTemp1057 * float((fTemp1058 > -0.5f))))) + ((float((fTemp1056 > 0.5f)) * (1.0f - fTemp1056)) + (float((fTemp1058 < -0.5f)) * (-1.0f - fTemp1058))));
			float fTemp1060 = float((iTemp3 == 71));
			iVec144[0] = (fTemp1060 < 0.5f);
			int iTemp1061 = std::abs(((fTemp1060 > 0.5f) * iVec144[1]));
			int iTemp1062 = (iTemp1061 >= iRec576[1]);
			int iTemp1063 = (1 - (iTemp1062 | iRec577[1]));
			iRec578[0] = ((iRec578[1] * iTemp1063) + iTemp1063);
			iRec577[0] = (float(iRec578[0]) >= fConst0);
			iRec576[0] = ((iRec577[0] | iTemp1062) ? iTemp1061 : iRec576[1]);
			iRec575[0] = (((iRec576[0] * iRec575[1]) + 1) % iConst4);
			ftbl71[(iRec575[0] + (2 * iRec576[0]))] = fTemp1;
			float fTemp1064 = fRec14[((IOTA - iConst77) & 262143)];
			float fTemp1065 = (1.0f - fTemp1064);
			iVec145[0] = (fTemp1065 < 0.5f);
			int iTemp1066 = ((fTemp1065 > 0.5f) * iVec145[1]);
			iRec580[0] = ((1103515245 * iRec580[1]) + 15618509);
			float fTemp1067 = float(iRec580[0]);
			fRec579[0] = ((fRec579[1] * float((1 - iTemp1066))) + (0.5f * (((4.65661287e-10f * fTemp1067) + 1.0f) * float(iTemp1066))));
			float fTemp1068 = (ftbl71[int(((fConst5 * ((0.449999988f * (fRec579[0] + 1.0f)) + (0.100000001f * fTemp1064))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1064)), fRec18[0]));
			fRec582[0] = ((fTemp17 * fRec582[1]) + (4.65661287e-10f * (fTemp1067 * fTemp18)));
			float fTemp1069 = (fRec581[1] + (fConst3 * float(((2 * (fRec582[0] > 0.0f)) + -1))));
			fRec581[0] = (fTemp1069 - float(int(fTemp1069)));
			float fTemp1070 = float((fRec581[0] > 0.0f));
			float fTemp1071 = (fRec581[0] * fTemp1070);
			float fTemp1072 = float((fRec581[0] < 0.0f));
			float fTemp1073 = (fRec581[0] * fTemp1072);
			float fTemp1074 = ((fRec581[0] * ((fTemp1070 * float((fTemp1071 < 0.5f))) + (fTemp1072 * float((fTemp1073 > -0.5f))))) + ((float((fTemp1071 > 0.5f)) * (1.0f - fTemp1071)) + (float((fTemp1073 < -0.5f)) * (-1.0f - fTemp1073))));
			float fTemp1075 = float((iTemp3 == 72));
			iVec146[0] = (fTemp1075 < 0.5f);
			int iTemp1076 = std::abs(((fTemp1075 > 0.5f) * iVec146[1]));
			int iTemp1077 = (iTemp1076 >= iRec584[1]);
			int iTemp1078 = (1 - (iTemp1077 | iRec585[1]));
			iRec586[0] = ((iRec586[1] * iTemp1078) + iTemp1078);
			iRec585[0] = (float(iRec586[0]) >= fConst0);
			iRec584[0] = ((iRec585[0] | iTemp1077) ? iTemp1076 : iRec584[1]);
			iRec583[0] = (((iRec584[0] * iRec583[1]) + 1) % iConst4);
			ftbl72[(iRec583[0] + (2 * iRec584[0]))] = fTemp1;
			float fTemp1079 = fRec14[((IOTA - iConst78) & 262143)];
			float fTemp1080 = (1.0f - fTemp1079);
			iVec147[0] = (fTemp1080 < 0.5f);
			int iTemp1081 = ((fTemp1080 > 0.5f) * iVec147[1]);
			iRec588[0] = ((1103515245 * iRec588[1]) + 15838488);
			float fTemp1082 = float(iRec588[0]);
			fRec587[0] = ((fRec587[1] * float((1 - iTemp1081))) + (0.5f * (((4.65661287e-10f * fTemp1082) + 1.0f) * float(iTemp1081))));
			float fTemp1083 = (ftbl72[int(((fConst5 * ((0.449999988f * (fRec587[0] + 1.0f)) + (0.100000001f * fTemp1079))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1079)), fRec18[0]));
			fRec590[0] = ((fTemp17 * fRec590[1]) + (4.65661287e-10f * (fTemp1082 * fTemp18)));
			float fTemp1084 = (fRec589[1] + (fConst3 * float(((2 * (fRec590[0] > 0.0f)) + -1))));
			fRec589[0] = (fTemp1084 - float(int(fTemp1084)));
			float fTemp1085 = float((fRec589[0] > 0.0f));
			float fTemp1086 = (fRec589[0] * fTemp1085);
			float fTemp1087 = float((fRec589[0] < 0.0f));
			float fTemp1088 = (fRec589[0] * fTemp1087);
			float fTemp1089 = ((fRec589[0] * ((fTemp1085 * float((fTemp1086 < 0.5f))) + (fTemp1087 * float((fTemp1088 > -0.5f))))) + ((float((fTemp1086 > 0.5f)) * (1.0f - fTemp1086)) + (float((fTemp1088 < -0.5f)) * (-1.0f - fTemp1088))));
			float fTemp1090 = float((iTemp3 == 73));
			iVec148[0] = (fTemp1090 < 0.5f);
			int iTemp1091 = std::abs(((fTemp1090 > 0.5f) * iVec148[1]));
			int iTemp1092 = (iTemp1091 >= iRec592[1]);
			int iTemp1093 = (1 - (iTemp1092 | iRec593[1]));
			iRec594[0] = ((iRec594[1] * iTemp1093) + iTemp1093);
			iRec593[0] = (float(iRec594[0]) >= fConst0);
			iRec592[0] = ((iRec593[0] | iTemp1092) ? iTemp1091 : iRec592[1]);
			iRec591[0] = (((iRec592[0] * iRec591[1]) + 1) % iConst4);
			ftbl73[(iRec591[0] + (2 * iRec592[0]))] = fTemp1;
			float fTemp1094 = fRec14[((IOTA - iConst79) & 262143)];
			float fTemp1095 = (1.0f - fTemp1094);
			iVec149[0] = (fTemp1095 < 0.5f);
			int iTemp1096 = ((fTemp1095 > 0.5f) * iVec149[1]);
			iRec596[0] = ((1103515245 * iRec596[1]) + 16058467);
			float fTemp1097 = float(iRec596[0]);
			fRec595[0] = ((fRec595[1] * float((1 - iTemp1096))) + (0.5f * (((4.65661287e-10f * fTemp1097) + 1.0f) * float(iTemp1096))));
			float fTemp1098 = (ftbl73[int(((fConst5 * ((0.449999988f * (fRec595[0] + 1.0f)) + (0.100000001f * fTemp1094))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1094)), fRec18[0]));
			fRec598[0] = ((fTemp17 * fRec598[1]) + (4.65661287e-10f * (fTemp1097 * fTemp18)));
			float fTemp1099 = (fRec597[1] + (fConst3 * float(((2 * (fRec598[0] > 0.0f)) + -1))));
			fRec597[0] = (fTemp1099 - float(int(fTemp1099)));
			float fTemp1100 = float((fRec597[0] > 0.0f));
			float fTemp1101 = (fRec597[0] * fTemp1100);
			float fTemp1102 = float((fRec597[0] < 0.0f));
			float fTemp1103 = (fRec597[0] * fTemp1102);
			float fTemp1104 = ((fRec597[0] * ((fTemp1100 * float((fTemp1101 < 0.5f))) + (fTemp1102 * float((fTemp1103 > -0.5f))))) + ((float((fTemp1101 > 0.5f)) * (1.0f - fTemp1101)) + (float((fTemp1103 < -0.5f)) * (-1.0f - fTemp1103))));
			float fTemp1105 = float((iTemp3 == 74));
			iVec150[0] = (fTemp1105 < 0.5f);
			int iTemp1106 = std::abs(((fTemp1105 > 0.5f) * iVec150[1]));
			int iTemp1107 = (iTemp1106 >= iRec600[1]);
			int iTemp1108 = (1 - (iTemp1107 | iRec601[1]));
			iRec602[0] = ((iRec602[1] * iTemp1108) + iTemp1108);
			iRec601[0] = (float(iRec602[0]) >= fConst0);
			iRec600[0] = ((iRec601[0] | iTemp1107) ? iTemp1106 : iRec600[1]);
			iRec599[0] = (((iRec600[0] * iRec599[1]) + 1) % iConst4);
			ftbl74[(iRec599[0] + (2 * iRec600[0]))] = fTemp1;
			float fTemp1109 = fRec14[((IOTA - iConst80) & 262143)];
			float fTemp1110 = (1.0f - fTemp1109);
			iVec151[0] = (fTemp1110 < 0.5f);
			int iTemp1111 = ((fTemp1110 > 0.5f) * iVec151[1]);
			iRec604[0] = ((1103515245 * iRec604[1]) + 16278446);
			float fTemp1112 = float(iRec604[0]);
			fRec603[0] = ((fRec603[1] * float((1 - iTemp1111))) + (0.5f * (((4.65661287e-10f * fTemp1112) + 1.0f) * float(iTemp1111))));
			float fTemp1113 = (ftbl74[int(((fConst5 * ((0.449999988f * (fRec603[0] + 1.0f)) + (0.100000001f * fTemp1109))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1109)), fRec18[0]));
			fRec606[0] = ((fTemp17 * fRec606[1]) + (4.65661287e-10f * (fTemp1112 * fTemp18)));
			float fTemp1114 = (fRec605[1] + (fConst3 * float(((2 * (fRec606[0] > 0.0f)) + -1))));
			fRec605[0] = (fTemp1114 - float(int(fTemp1114)));
			float fTemp1115 = float((fRec605[0] > 0.0f));
			float fTemp1116 = (fRec605[0] * fTemp1115);
			float fTemp1117 = float((fRec605[0] < 0.0f));
			float fTemp1118 = (fRec605[0] * fTemp1117);
			float fTemp1119 = ((fRec605[0] * ((fTemp1115 * float((fTemp1116 < 0.5f))) + (fTemp1117 * float((fTemp1118 > -0.5f))))) + ((float((fTemp1116 > 0.5f)) * (1.0f - fTemp1116)) + (float((fTemp1118 < -0.5f)) * (-1.0f - fTemp1118))));
			float fTemp1120 = float((iTemp3 == 75));
			iVec152[0] = (fTemp1120 < 0.5f);
			int iTemp1121 = std::abs(((fTemp1120 > 0.5f) * iVec152[1]));
			int iTemp1122 = (iTemp1121 >= iRec608[1]);
			int iTemp1123 = (1 - (iTemp1122 | iRec609[1]));
			iRec610[0] = ((iRec610[1] * iTemp1123) + iTemp1123);
			iRec609[0] = (float(iRec610[0]) >= fConst0);
			iRec608[0] = ((iRec609[0] | iTemp1122) ? iTemp1121 : iRec608[1]);
			iRec607[0] = (((iRec608[0] * iRec607[1]) + 1) % iConst4);
			ftbl75[(iRec607[0] + (2 * iRec608[0]))] = fTemp1;
			float fTemp1124 = fRec14[((IOTA - iConst81) & 262143)];
			float fTemp1125 = (1.0f - fTemp1124);
			iVec153[0] = (fTemp1125 < 0.5f);
			int iTemp1126 = ((fTemp1125 > 0.5f) * iVec153[1]);
			iRec612[0] = ((1103515245 * iRec612[1]) + 16498425);
			float fTemp1127 = float(iRec612[0]);
			fRec611[0] = ((fRec611[1] * float((1 - iTemp1126))) + (0.5f * (((4.65661287e-10f * fTemp1127) + 1.0f) * float(iTemp1126))));
			float fTemp1128 = (ftbl75[int(((fConst5 * ((0.449999988f * (fRec611[0] + 1.0f)) + (0.100000001f * fTemp1124))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1124)), fRec18[0]));
			fRec614[0] = ((fTemp17 * fRec614[1]) + (4.65661287e-10f * (fTemp1127 * fTemp18)));
			float fTemp1129 = (fRec613[1] + (fConst3 * float(((2 * (fRec614[0] > 0.0f)) + -1))));
			fRec613[0] = (fTemp1129 - float(int(fTemp1129)));
			float fTemp1130 = float((fRec613[0] > 0.0f));
			float fTemp1131 = (fRec613[0] * fTemp1130);
			float fTemp1132 = float((fRec613[0] < 0.0f));
			float fTemp1133 = (fRec613[0] * fTemp1132);
			float fTemp1134 = ((fRec613[0] * ((fTemp1130 * float((fTemp1131 < 0.5f))) + (fTemp1132 * float((fTemp1133 > -0.5f))))) + ((float((fTemp1131 > 0.5f)) * (1.0f - fTemp1131)) + (float((fTemp1133 < -0.5f)) * (-1.0f - fTemp1133))));
			float fTemp1135 = float((iTemp3 == 76));
			iVec154[0] = (fTemp1135 < 0.5f);
			int iTemp1136 = std::abs(((fTemp1135 > 0.5f) * iVec154[1]));
			int iTemp1137 = (iTemp1136 >= iRec616[1]);
			int iTemp1138 = (1 - (iTemp1137 | iRec617[1]));
			iRec618[0] = ((iRec618[1] * iTemp1138) + iTemp1138);
			iRec617[0] = (float(iRec618[0]) >= fConst0);
			iRec616[0] = ((iRec617[0] | iTemp1137) ? iTemp1136 : iRec616[1]);
			iRec615[0] = (((iRec616[0] * iRec615[1]) + 1) % iConst4);
			ftbl76[(iRec615[0] + (2 * iRec616[0]))] = fTemp1;
			float fTemp1139 = fRec14[((IOTA - iConst82) & 262143)];
			float fTemp1140 = (1.0f - fTemp1139);
			iVec155[0] = (fTemp1140 < 0.5f);
			int iTemp1141 = ((fTemp1140 > 0.5f) * iVec155[1]);
			iRec620[0] = ((1103515245 * iRec620[1]) + 16718404);
			float fTemp1142 = float(iRec620[0]);
			fRec619[0] = ((fRec619[1] * float((1 - iTemp1141))) + (0.5f * (((4.65661287e-10f * fTemp1142) + 1.0f) * float(iTemp1141))));
			float fTemp1143 = (ftbl76[int(((fConst5 * ((0.449999988f * (fRec619[0] + 1.0f)) + (0.100000001f * fTemp1139))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1139)), fRec18[0]));
			fRec622[0] = ((fTemp17 * fRec622[1]) + (4.65661287e-10f * (fTemp1142 * fTemp18)));
			float fTemp1144 = (fRec621[1] + (fConst3 * float(((2 * (fRec622[0] > 0.0f)) + -1))));
			fRec621[0] = (fTemp1144 - float(int(fTemp1144)));
			float fTemp1145 = float((fRec621[0] > 0.0f));
			float fTemp1146 = (fRec621[0] * fTemp1145);
			float fTemp1147 = float((fRec621[0] < 0.0f));
			float fTemp1148 = (fRec621[0] * fTemp1147);
			float fTemp1149 = ((fRec621[0] * ((fTemp1145 * float((fTemp1146 < 0.5f))) + (fTemp1147 * float((fTemp1148 > -0.5f))))) + ((float((fTemp1146 > 0.5f)) * (1.0f - fTemp1146)) + (float((fTemp1148 < -0.5f)) * (-1.0f - fTemp1148))));
			float fTemp1150 = float((iTemp3 == 77));
			iVec156[0] = (fTemp1150 < 0.5f);
			int iTemp1151 = std::abs(((fTemp1150 > 0.5f) * iVec156[1]));
			int iTemp1152 = (iTemp1151 >= iRec624[1]);
			int iTemp1153 = (1 - (iTemp1152 | iRec625[1]));
			iRec626[0] = ((iRec626[1] * iTemp1153) + iTemp1153);
			iRec625[0] = (float(iRec626[0]) >= fConst0);
			iRec624[0] = ((iRec625[0] | iTemp1152) ? iTemp1151 : iRec624[1]);
			iRec623[0] = (((iRec624[0] * iRec623[1]) + 1) % iConst4);
			ftbl77[(iRec623[0] + (2 * iRec624[0]))] = fTemp1;
			float fTemp1154 = fRec14[((IOTA - iConst83) & 262143)];
			float fTemp1155 = (1.0f - fTemp1154);
			iVec157[0] = (fTemp1155 < 0.5f);
			int iTemp1156 = ((fTemp1155 > 0.5f) * iVec157[1]);
			iRec628[0] = ((1103515245 * iRec628[1]) + 16938383);
			float fTemp1157 = float(iRec628[0]);
			fRec627[0] = ((fRec627[1] * float((1 - iTemp1156))) + (0.5f * (((4.65661287e-10f * fTemp1157) + 1.0f) * float(iTemp1156))));
			float fTemp1158 = (ftbl77[int(((fConst5 * ((0.449999988f * (fRec627[0] + 1.0f)) + (0.100000001f * fTemp1154))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1154)), fRec18[0]));
			fRec630[0] = ((fTemp17 * fRec630[1]) + (4.65661287e-10f * (fTemp1157 * fTemp18)));
			float fTemp1159 = (fRec629[1] + (fConst3 * float(((2 * (fRec630[0] > 0.0f)) + -1))));
			fRec629[0] = (fTemp1159 - float(int(fTemp1159)));
			float fTemp1160 = float((fRec629[0] > 0.0f));
			float fTemp1161 = (fRec629[0] * fTemp1160);
			float fTemp1162 = float((fRec629[0] < 0.0f));
			float fTemp1163 = (fRec629[0] * fTemp1162);
			float fTemp1164 = ((fRec629[0] * ((fTemp1160 * float((fTemp1161 < 0.5f))) + (fTemp1162 * float((fTemp1163 > -0.5f))))) + ((float((fTemp1161 > 0.5f)) * (1.0f - fTemp1161)) + (float((fTemp1163 < -0.5f)) * (-1.0f - fTemp1163))));
			float fTemp1165 = float((iTemp3 == 78));
			iVec158[0] = (fTemp1165 < 0.5f);
			int iTemp1166 = std::abs(((fTemp1165 > 0.5f) * iVec158[1]));
			int iTemp1167 = (iTemp1166 >= iRec632[1]);
			int iTemp1168 = (1 - (iTemp1167 | iRec633[1]));
			iRec634[0] = ((iRec634[1] * iTemp1168) + iTemp1168);
			iRec633[0] = (float(iRec634[0]) >= fConst0);
			iRec632[0] = ((iRec633[0] | iTemp1167) ? iTemp1166 : iRec632[1]);
			iRec631[0] = (((iRec632[0] * iRec631[1]) + 1) % iConst4);
			ftbl78[(iRec631[0] + (2 * iRec632[0]))] = fTemp1;
			float fTemp1169 = fRec14[((IOTA - iConst84) & 262143)];
			float fTemp1170 = (1.0f - fTemp1169);
			iVec159[0] = (fTemp1170 < 0.5f);
			int iTemp1171 = ((fTemp1170 > 0.5f) * iVec159[1]);
			iRec636[0] = ((1103515245 * iRec636[1]) + 17158362);
			float fTemp1172 = float(iRec636[0]);
			fRec635[0] = ((fRec635[1] * float((1 - iTemp1171))) + (0.5f * (((4.65661287e-10f * fTemp1172) + 1.0f) * float(iTemp1171))));
			float fTemp1173 = (ftbl78[int(((fConst5 * ((0.449999988f * (fRec635[0] + 1.0f)) + (0.100000001f * fTemp1169))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1169)), fRec18[0]));
			fRec638[0] = ((fTemp17 * fRec638[1]) + (4.65661287e-10f * (fTemp1172 * fTemp18)));
			float fTemp1174 = (fRec637[1] + (fConst3 * float(((2 * (fRec638[0] > 0.0f)) + -1))));
			fRec637[0] = (fTemp1174 - float(int(fTemp1174)));
			float fTemp1175 = float((fRec637[0] > 0.0f));
			float fTemp1176 = (fRec637[0] * fTemp1175);
			float fTemp1177 = float((fRec637[0] < 0.0f));
			float fTemp1178 = (fRec637[0] * fTemp1177);
			float fTemp1179 = ((fRec637[0] * ((fTemp1175 * float((fTemp1176 < 0.5f))) + (fTemp1177 * float((fTemp1178 > -0.5f))))) + ((float((fTemp1176 > 0.5f)) * (1.0f - fTemp1176)) + (float((fTemp1178 < -0.5f)) * (-1.0f - fTemp1178))));
			float fTemp1180 = float((iTemp3 == 79));
			iVec160[0] = (fTemp1180 < 0.5f);
			int iTemp1181 = std::abs(((fTemp1180 > 0.5f) * iVec160[1]));
			int iTemp1182 = (iTemp1181 >= iRec640[1]);
			int iTemp1183 = (1 - (iTemp1182 | iRec641[1]));
			iRec642[0] = ((iRec642[1] * iTemp1183) + iTemp1183);
			iRec641[0] = (float(iRec642[0]) >= fConst0);
			iRec640[0] = ((iRec641[0] | iTemp1182) ? iTemp1181 : iRec640[1]);
			iRec639[0] = (((iRec640[0] * iRec639[1]) + 1) % iConst4);
			ftbl79[(iRec639[0] + (2 * iRec640[0]))] = fTemp1;
			float fTemp1184 = fRec14[((IOTA - iConst85) & 262143)];
			float fTemp1185 = (1.0f - fTemp1184);
			iVec161[0] = (fTemp1185 < 0.5f);
			int iTemp1186 = ((fTemp1185 > 0.5f) * iVec161[1]);
			iRec644[0] = ((1103515245 * iRec644[1]) + 17378341);
			float fTemp1187 = float(iRec644[0]);
			fRec643[0] = ((fRec643[1] * float((1 - iTemp1186))) + (0.5f * (((4.65661287e-10f * fTemp1187) + 1.0f) * float(iTemp1186))));
			float fTemp1188 = (ftbl79[int(((fConst5 * ((0.449999988f * (fRec643[0] + 1.0f)) + (0.100000001f * fTemp1184))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1184)), fRec18[0]));
			fRec646[0] = ((fTemp17 * fRec646[1]) + (4.65661287e-10f * (fTemp1187 * fTemp18)));
			float fTemp1189 = (fRec645[1] + (fConst3 * float(((2 * (fRec646[0] > 0.0f)) + -1))));
			fRec645[0] = (fTemp1189 - float(int(fTemp1189)));
			float fTemp1190 = float((fRec645[0] > 0.0f));
			float fTemp1191 = (fRec645[0] * fTemp1190);
			float fTemp1192 = float((fRec645[0] < 0.0f));
			float fTemp1193 = (fRec645[0] * fTemp1192);
			float fTemp1194 = ((fRec645[0] * ((fTemp1190 * float((fTemp1191 < 0.5f))) + (fTemp1192 * float((fTemp1193 > -0.5f))))) + ((float((fTemp1191 > 0.5f)) * (1.0f - fTemp1191)) + (float((fTemp1193 < -0.5f)) * (-1.0f - fTemp1193))));
			float fTemp1195 = float((iTemp3 == 80));
			iVec162[0] = (fTemp1195 < 0.5f);
			int iTemp1196 = std::abs(((fTemp1195 > 0.5f) * iVec162[1]));
			int iTemp1197 = (iTemp1196 >= iRec648[1]);
			int iTemp1198 = (1 - (iTemp1197 | iRec649[1]));
			iRec650[0] = ((iRec650[1] * iTemp1198) + iTemp1198);
			iRec649[0] = (float(iRec650[0]) >= fConst0);
			iRec648[0] = ((iRec649[0] | iTemp1197) ? iTemp1196 : iRec648[1]);
			iRec647[0] = (((iRec648[0] * iRec647[1]) + 1) % iConst4);
			ftbl80[(iRec647[0] + (2 * iRec648[0]))] = fTemp1;
			float fTemp1199 = fRec14[((IOTA - iConst86) & 262143)];
			float fTemp1200 = (1.0f - fTemp1199);
			iVec163[0] = (fTemp1200 < 0.5f);
			int iTemp1201 = ((fTemp1200 > 0.5f) * iVec163[1]);
			iRec652[0] = ((1103515245 * iRec652[1]) + 17598320);
			float fTemp1202 = float(iRec652[0]);
			fRec651[0] = ((fRec651[1] * float((1 - iTemp1201))) + (0.5f * (((4.65661287e-10f * fTemp1202) + 1.0f) * float(iTemp1201))));
			float fTemp1203 = (ftbl80[int(((fConst5 * ((0.449999988f * (fRec651[0] + 1.0f)) + (0.100000001f * fTemp1199))) + 2.0f))] * std::pow(std::sin((3.14159274f * fTemp1199)), fRec18[0]));
			fRec654[0] = ((fTemp17 * fRec654[1]) + (4.65661287e-10f * (fTemp1202 * fTemp18)));
			float fTemp1204 = (fRec653[1] + (fConst3 * float(((2 * (fRec654[0] > 0.0f)) + -1))));
			fRec653[0] = (fTemp1204 - float(int(fTemp1204)));
			float fTemp1205 = float((fRec653[0] > 0.0f));
			float fTemp1206 = (fRec653[0] * fTemp1205);
			float fTemp1207 = float((fRec653[0] < 0.0f));
			float fTemp1208 = (fRec653[0] * fTemp1207);
			float fTemp1209 = ((fRec653[0] * ((fTemp1205 * float((fTemp1206 < 0.5f))) + (fTemp1207 * float((fTemp1208 > -0.5f))))) + ((float((fTemp1206 > 0.5f)) * (1.0f - fTemp1206)) + (float((fTemp1208 < -0.5f)) * (-1.0f - fTemp1208))));
			float fTemp1210 = ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((fTemp13 * (fTemp24 + 0.5f)) + (fTemp33 * (fTemp39 + 0.5f))) + (fTemp48 * (fTemp54 + 0.5f))) + (fTemp63 * (fTemp69 + 0.5f))) + (fTemp78 * (fTemp84 + 0.5f))) + (fTemp93 * (fTemp99 + 0.5f))) + (fTemp108 * (fTemp114 + 0.5f))) + (fTemp123 * (fTemp129 + 0.5f))) + (fTemp138 * (fTemp144 + 0.5f))) + (fTemp153 * (fTemp159 + 0.5f))) + (fTemp168 * (fTemp174 + 0.5f))) + (fTemp183 * (fTemp189 + 0.5f))) + (fTemp198 * (fTemp204 + 0.5f))) + (fTemp213 * (fTemp219 + 0.5f))) + (fTemp228 * (fTemp234 + 0.5f))) + (fTemp243 * (fTemp249 + 0.5f))) + (fTemp258 * (fTemp264 + 0.5f))) + (fTemp273 * (fTemp279 + 0.5f))) + (fTemp288 * (fTemp294 + 0.5f))) + (fTemp303 * (fTemp309 + 0.5f))) + (fTemp318 * (fTemp324 + 0.5f))) + (fTemp333 * (fTemp339 + 0.5f))) + (fTemp348 * (fTemp354 + 0.5f))) + (fTemp363 * (fTemp369 + 0.5f))) + (fTemp378 * (fTemp384 + 0.5f))) + (fTemp393 * (fTemp399 + 0.5f))) + (fTemp408 * (fTemp414 + 0.5f))) + (fTemp423 * (fTemp429 + 0.5f))) + (fTemp438 * (fTemp444 + 0.5f))) + (fTemp453 * (fTemp459 + 0.5f))) + (fTemp468 * (fTemp474 + 0.5f))) + (fTemp483 * (fTemp489 + 0.5f))) + (fTemp498 * (fTemp504 + 0.5f))) + (fTemp513 * (fTemp519 + 0.5f))) + (fTemp528 * (fTemp534 + 0.5f))) + (fTemp543 * (fTemp549 + 0.5f))) + (fTemp558 * (fTemp564 + 0.5f))) + (fTemp573 * (fTemp579 + 0.5f))) + (fTemp588 * (fTemp594 + 0.5f))) + (fTemp603 * (fTemp609 + 0.5f))) + (fTemp618 * (fTemp624 + 0.5f))) + (fTemp633 * (fTemp639 + 0.5f))) + (fTemp648 * (fTemp654 + 0.5f))) + (fTemp663 * (fTemp669 + 0.5f))) + (fTemp678 * (fTemp684 + 0.5f))) + (fTemp693 * (fTemp699 + 0.5f))) + (fTemp708 * (fTemp714 + 0.5f))) + (fTemp723 * (fTemp729 + 0.5f))) + (fTemp738 * (fTemp744 + 0.5f))) + (fTemp753 * (fTemp759 + 0.5f))) + (fTemp768 * (fTemp774 + 0.5f))) + (fTemp783 * (fTemp789 + 0.5f))) + (fTemp798 * (fTemp804 + 0.5f))) + (fTemp813 * (fTemp819 + 0.5f))) + (fTemp828 * (fTemp834 + 0.5f))) + (fTemp843 * (fTemp849 + 0.5f))) + (fTemp858 * (fTemp864 + 0.5f))) + (fTemp873 * (fTemp879 + 0.5f))) + (fTemp888 * (fTemp894 + 0.5f))) + (fTemp903 * (fTemp909 + 0.5f))) + (fTemp918 * (fTemp924 + 0.5f))) + (fTemp933 * (fTemp939 + 0.5f))) + (fTemp948 * (fTemp954 + 0.5f))) + (fTemp963 * (fTemp969 + 0.5f))) + (fTemp978 * (fTemp984 + 0.5f))) + (fTemp993 * (fTemp999 + 0.5f))) + (fTemp1008 * (fTemp1014 + 0.5f))) + (fTemp1023 * (fTemp1029 + 0.5f))) + (fTemp1038 * (fTemp1044 + 0.5f))) + (fTemp1053 * (fTemp1059 + 0.5f))) + (fTemp1068 * (fTemp1074 + 0.5f))) + (fTemp1083 * (fTemp1089 + 0.5f))) + (fTemp1098 * (fTemp1104 + 0.5f))) + (fTemp1113 * (fTemp1119 + 0.5f))) + (fTemp1128 * (fTemp1134 + 0.5f))) + (fTemp1143 * (fTemp1149 + 0.5f))) + (fTemp1158 * (fTemp1164 + 0.5f))) + (fTemp1173 * (fTemp1179 + 0.5f))) + (fTemp1188 * (fTemp1194 + 0.5f))) + (fTemp1203 * (fTemp1209 + 0.5f)));
			float fTemp1211 = ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((fTemp13 * (0.5f - fTemp24)) + (fTemp33 * (0.5f - fTemp39))) + (fTemp48 * (0.5f - fTemp54))) + (fTemp63 * (0.5f - fTemp69))) + (fTemp78 * (0.5f - fTemp84))) + (fTemp93 * (0.5f - fTemp99))) + (fTemp108 * (0.5f - fTemp114))) + (fTemp123 * (0.5f - fTemp129))) + (fTemp138 * (0.5f - fTemp144))) + (fTemp153 * (0.5f - fTemp159))) + (fTemp168 * (0.5f - fTemp174))) + (fTemp183 * (0.5f - fTemp189))) + (fTemp198 * (0.5f - fTemp204))) + (fTemp213 * (0.5f - fTemp219))) + (fTemp228 * (0.5f - fTemp234))) + (fTemp243 * (0.5f - fTemp249))) + (fTemp258 * (0.5f - fTemp264))) + (fTemp273 * (0.5f - fTemp279))) + (fTemp288 * (0.5f - fTemp294))) + (fTemp303 * (0.5f - fTemp309))) + (fTemp318 * (0.5f - fTemp324))) + (fTemp333 * (0.5f - fTemp339))) + (fTemp348 * (0.5f - fTemp354))) + (fTemp363 * (0.5f - fTemp369))) + (fTemp378 * (0.5f - fTemp384))) + (fTemp393 * (0.5f - fTemp399))) + (fTemp408 * (0.5f - fTemp414))) + (fTemp423 * (0.5f - fTemp429))) + (fTemp438 * (0.5f - fTemp444))) + (fTemp453 * (0.5f - fTemp459))) + (fTemp468 * (0.5f - fTemp474))) + (fTemp483 * (0.5f - fTemp489))) + (fTemp498 * (0.5f - fTemp504))) + (fTemp513 * (0.5f - fTemp519))) + (fTemp528 * (0.5f - fTemp534))) + (fTemp543 * (0.5f - fTemp549))) + (fTemp558 * (0.5f - fTemp564))) + (fTemp573 * (0.5f - fTemp579))) + (fTemp588 * (0.5f - fTemp594))) + (fTemp603 * (0.5f - fTemp609))) + (fTemp618 * (0.5f - fTemp624))) + (fTemp633 * (0.5f - fTemp639))) + (fTemp648 * (0.5f - fTemp654))) + (fTemp663 * (0.5f - fTemp669))) + (fTemp678 * (0.5f - fTemp684))) + (fTemp693 * (0.5f - fTemp699))) + (fTemp708 * (0.5f - fTemp714))) + (fTemp723 * (0.5f - fTemp729))) + (fTemp738 * (0.5f - fTemp744))) + (fTemp753 * (0.5f - fTemp759))) + (fTemp768 * (0.5f - fTemp774))) + (fTemp783 * (0.5f - fTemp789))) + (fTemp798 * (0.5f - fTemp804))) + (fTemp813 * (0.5f - fTemp819))) + (fTemp828 * (0.5f - fTemp834))) + (fTemp843 * (0.5f - fTemp849))) + (fTemp858 * (0.5f - fTemp864))) + (fTemp873 * (0.5f - fTemp879))) + (fTemp888 * (0.5f - fTemp894))) + (fTemp903 * (0.5f - fTemp909))) + (fTemp918 * (0.5f - fTemp924))) + (fTemp933 * (0.5f - fTemp939))) + (fTemp948 * (0.5f - fTemp954))) + (fTemp963 * (0.5f - fTemp969))) + (fTemp978 * (0.5f - fTemp984))) + (fTemp993 * (0.5f - fTemp999))) + (fTemp1008 * (0.5f - fTemp1014))) + (fTemp1023 * (0.5f - fTemp1029))) + (fTemp1038 * (0.5f - fTemp1044))) + (fTemp1053 * (0.5f - fTemp1059))) + (fTemp1068 * (0.5f - fTemp1074))) + (fTemp1083 * (0.5f - fTemp1089))) + (fTemp1098 * (0.5f - fTemp1104))) + (fTemp1113 * (0.5f - fTemp1119))) + (fTemp1128 * (0.5f - fTemp1134))) + (fTemp1143 * (0.5f - fTemp1149))) + (fTemp1158 * (0.5f - fTemp1164))) + (fTemp1173 * (0.5f - fTemp1179))) + (fTemp1188 * (0.5f - fTemp1194))) + (fTemp1203 * (0.5f - fTemp1209)));
			fRec0[0] = (0.0125000002f * (fRec3[0] * (fTemp1210 + fTemp1211)));
			float fRec1 = (0.0125000002f * fTemp1210);
			float fRec2 = (0.0125000002f * fTemp1211);
			fRec655[0] = (fSlow7 + (fConst2 * fRec655[1]));
			output0[i0] = FAUSTFLOAT((fRec1 * fRec655[0]));
			output1[i0] = FAUSTFLOAT((fRec655[0] * fRec2));
			fRec3[1] = fRec3[0];
			fRec5[1] = fRec5[0];
			fVec0[1] = fVec0[0];
			fRec4[1] = fRec4[0];
			fRec12[1] = fRec12[0];
			iVec2[1] = iVec2[0];
			iRec10[1] = iRec10[0];
			iVec3[1] = iVec3[0];
			iRec9[1] = iRec9[0];
			iRec8[1] = iRec8[0];
			iRec7[1] = iRec7[0];
			iRec6[1] = iRec6[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			IOTA = (IOTA + 1);
			iVec4[1] = iVec4[0];
			iRec17[1] = iRec17[0];
			fRec13[1] = fRec13[0];
			fRec18[1] = fRec18[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			iVec5[1] = iVec5[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			iVec6[1] = iVec6[0];
			iRec26[1] = iRec26[0];
			iRec25[1] = iRec25[0];
			iRec24[1] = iRec24[0];
			iRec23[1] = iRec23[0];
			iVec7[1] = iVec7[0];
			iRec28[1] = iRec28[0];
			fRec27[1] = fRec27[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			iVec8[1] = iVec8[0];
			iRec34[1] = iRec34[0];
			iRec33[1] = iRec33[0];
			iRec32[1] = iRec32[0];
			iRec31[1] = iRec31[0];
			iVec9[1] = iVec9[0];
			iRec36[1] = iRec36[0];
			fRec35[1] = fRec35[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			iVec10[1] = iVec10[0];
			iRec42[1] = iRec42[0];
			iRec41[1] = iRec41[0];
			iRec40[1] = iRec40[0];
			iRec39[1] = iRec39[0];
			iVec11[1] = iVec11[0];
			iRec44[1] = iRec44[0];
			fRec43[1] = fRec43[0];
			fRec46[1] = fRec46[0];
			fRec45[1] = fRec45[0];
			iVec12[1] = iVec12[0];
			iRec50[1] = iRec50[0];
			iRec49[1] = iRec49[0];
			iRec48[1] = iRec48[0];
			iRec47[1] = iRec47[0];
			iVec13[1] = iVec13[0];
			iRec52[1] = iRec52[0];
			fRec51[1] = fRec51[0];
			fRec54[1] = fRec54[0];
			fRec53[1] = fRec53[0];
			iVec14[1] = iVec14[0];
			iRec58[1] = iRec58[0];
			iRec57[1] = iRec57[0];
			iRec56[1] = iRec56[0];
			iRec55[1] = iRec55[0];
			iVec15[1] = iVec15[0];
			iRec60[1] = iRec60[0];
			fRec59[1] = fRec59[0];
			fRec62[1] = fRec62[0];
			fRec61[1] = fRec61[0];
			iVec16[1] = iVec16[0];
			iRec66[1] = iRec66[0];
			iRec65[1] = iRec65[0];
			iRec64[1] = iRec64[0];
			iRec63[1] = iRec63[0];
			iVec17[1] = iVec17[0];
			iRec68[1] = iRec68[0];
			fRec67[1] = fRec67[0];
			fRec70[1] = fRec70[0];
			fRec69[1] = fRec69[0];
			iVec18[1] = iVec18[0];
			iRec74[1] = iRec74[0];
			iRec73[1] = iRec73[0];
			iRec72[1] = iRec72[0];
			iRec71[1] = iRec71[0];
			iVec19[1] = iVec19[0];
			iRec76[1] = iRec76[0];
			fRec75[1] = fRec75[0];
			fRec78[1] = fRec78[0];
			fRec77[1] = fRec77[0];
			iVec20[1] = iVec20[0];
			iRec82[1] = iRec82[0];
			iRec81[1] = iRec81[0];
			iRec80[1] = iRec80[0];
			iRec79[1] = iRec79[0];
			iVec21[1] = iVec21[0];
			iRec84[1] = iRec84[0];
			fRec83[1] = fRec83[0];
			fRec86[1] = fRec86[0];
			fRec85[1] = fRec85[0];
			iVec22[1] = iVec22[0];
			iRec90[1] = iRec90[0];
			iRec89[1] = iRec89[0];
			iRec88[1] = iRec88[0];
			iRec87[1] = iRec87[0];
			iVec23[1] = iVec23[0];
			iRec92[1] = iRec92[0];
			fRec91[1] = fRec91[0];
			fRec94[1] = fRec94[0];
			fRec93[1] = fRec93[0];
			iVec24[1] = iVec24[0];
			iRec98[1] = iRec98[0];
			iRec97[1] = iRec97[0];
			iRec96[1] = iRec96[0];
			iRec95[1] = iRec95[0];
			iVec25[1] = iVec25[0];
			iRec100[1] = iRec100[0];
			fRec99[1] = fRec99[0];
			fRec102[1] = fRec102[0];
			fRec101[1] = fRec101[0];
			iVec26[1] = iVec26[0];
			iRec106[1] = iRec106[0];
			iRec105[1] = iRec105[0];
			iRec104[1] = iRec104[0];
			iRec103[1] = iRec103[0];
			iVec27[1] = iVec27[0];
			iRec108[1] = iRec108[0];
			fRec107[1] = fRec107[0];
			fRec110[1] = fRec110[0];
			fRec109[1] = fRec109[0];
			iVec28[1] = iVec28[0];
			iRec114[1] = iRec114[0];
			iRec113[1] = iRec113[0];
			iRec112[1] = iRec112[0];
			iRec111[1] = iRec111[0];
			iVec29[1] = iVec29[0];
			iRec116[1] = iRec116[0];
			fRec115[1] = fRec115[0];
			fRec118[1] = fRec118[0];
			fRec117[1] = fRec117[0];
			iVec30[1] = iVec30[0];
			iRec122[1] = iRec122[0];
			iRec121[1] = iRec121[0];
			iRec120[1] = iRec120[0];
			iRec119[1] = iRec119[0];
			iVec31[1] = iVec31[0];
			iRec124[1] = iRec124[0];
			fRec123[1] = fRec123[0];
			fRec126[1] = fRec126[0];
			fRec125[1] = fRec125[0];
			iVec32[1] = iVec32[0];
			iRec130[1] = iRec130[0];
			iRec129[1] = iRec129[0];
			iRec128[1] = iRec128[0];
			iRec127[1] = iRec127[0];
			iVec33[1] = iVec33[0];
			iRec132[1] = iRec132[0];
			fRec131[1] = fRec131[0];
			fRec134[1] = fRec134[0];
			fRec133[1] = fRec133[0];
			iVec34[1] = iVec34[0];
			iRec138[1] = iRec138[0];
			iRec137[1] = iRec137[0];
			iRec136[1] = iRec136[0];
			iRec135[1] = iRec135[0];
			iVec35[1] = iVec35[0];
			iRec140[1] = iRec140[0];
			fRec139[1] = fRec139[0];
			fRec142[1] = fRec142[0];
			fRec141[1] = fRec141[0];
			iVec36[1] = iVec36[0];
			iRec146[1] = iRec146[0];
			iRec145[1] = iRec145[0];
			iRec144[1] = iRec144[0];
			iRec143[1] = iRec143[0];
			iVec37[1] = iVec37[0];
			iRec148[1] = iRec148[0];
			fRec147[1] = fRec147[0];
			fRec150[1] = fRec150[0];
			fRec149[1] = fRec149[0];
			iVec38[1] = iVec38[0];
			iRec154[1] = iRec154[0];
			iRec153[1] = iRec153[0];
			iRec152[1] = iRec152[0];
			iRec151[1] = iRec151[0];
			iVec39[1] = iVec39[0];
			iRec156[1] = iRec156[0];
			fRec155[1] = fRec155[0];
			fRec158[1] = fRec158[0];
			fRec157[1] = fRec157[0];
			iVec40[1] = iVec40[0];
			iRec162[1] = iRec162[0];
			iRec161[1] = iRec161[0];
			iRec160[1] = iRec160[0];
			iRec159[1] = iRec159[0];
			iVec41[1] = iVec41[0];
			iRec164[1] = iRec164[0];
			fRec163[1] = fRec163[0];
			fRec166[1] = fRec166[0];
			fRec165[1] = fRec165[0];
			iVec42[1] = iVec42[0];
			iRec170[1] = iRec170[0];
			iRec169[1] = iRec169[0];
			iRec168[1] = iRec168[0];
			iRec167[1] = iRec167[0];
			iVec43[1] = iVec43[0];
			iRec172[1] = iRec172[0];
			fRec171[1] = fRec171[0];
			fRec174[1] = fRec174[0];
			fRec173[1] = fRec173[0];
			iVec44[1] = iVec44[0];
			iRec178[1] = iRec178[0];
			iRec177[1] = iRec177[0];
			iRec176[1] = iRec176[0];
			iRec175[1] = iRec175[0];
			iVec45[1] = iVec45[0];
			iRec180[1] = iRec180[0];
			fRec179[1] = fRec179[0];
			fRec182[1] = fRec182[0];
			fRec181[1] = fRec181[0];
			iVec46[1] = iVec46[0];
			iRec186[1] = iRec186[0];
			iRec185[1] = iRec185[0];
			iRec184[1] = iRec184[0];
			iRec183[1] = iRec183[0];
			iVec47[1] = iVec47[0];
			iRec188[1] = iRec188[0];
			fRec187[1] = fRec187[0];
			fRec190[1] = fRec190[0];
			fRec189[1] = fRec189[0];
			iVec48[1] = iVec48[0];
			iRec194[1] = iRec194[0];
			iRec193[1] = iRec193[0];
			iRec192[1] = iRec192[0];
			iRec191[1] = iRec191[0];
			iVec49[1] = iVec49[0];
			iRec196[1] = iRec196[0];
			fRec195[1] = fRec195[0];
			fRec198[1] = fRec198[0];
			fRec197[1] = fRec197[0];
			iVec50[1] = iVec50[0];
			iRec202[1] = iRec202[0];
			iRec201[1] = iRec201[0];
			iRec200[1] = iRec200[0];
			iRec199[1] = iRec199[0];
			iVec51[1] = iVec51[0];
			iRec204[1] = iRec204[0];
			fRec203[1] = fRec203[0];
			fRec206[1] = fRec206[0];
			fRec205[1] = fRec205[0];
			iVec52[1] = iVec52[0];
			iRec210[1] = iRec210[0];
			iRec209[1] = iRec209[0];
			iRec208[1] = iRec208[0];
			iRec207[1] = iRec207[0];
			iVec53[1] = iVec53[0];
			iRec212[1] = iRec212[0];
			fRec211[1] = fRec211[0];
			fRec214[1] = fRec214[0];
			fRec213[1] = fRec213[0];
			iVec54[1] = iVec54[0];
			iRec218[1] = iRec218[0];
			iRec217[1] = iRec217[0];
			iRec216[1] = iRec216[0];
			iRec215[1] = iRec215[0];
			iVec55[1] = iVec55[0];
			iRec220[1] = iRec220[0];
			fRec219[1] = fRec219[0];
			fRec222[1] = fRec222[0];
			fRec221[1] = fRec221[0];
			iVec56[1] = iVec56[0];
			iRec226[1] = iRec226[0];
			iRec225[1] = iRec225[0];
			iRec224[1] = iRec224[0];
			iRec223[1] = iRec223[0];
			iVec57[1] = iVec57[0];
			iRec228[1] = iRec228[0];
			fRec227[1] = fRec227[0];
			fRec230[1] = fRec230[0];
			fRec229[1] = fRec229[0];
			iVec58[1] = iVec58[0];
			iRec234[1] = iRec234[0];
			iRec233[1] = iRec233[0];
			iRec232[1] = iRec232[0];
			iRec231[1] = iRec231[0];
			iVec59[1] = iVec59[0];
			iRec236[1] = iRec236[0];
			fRec235[1] = fRec235[0];
			fRec238[1] = fRec238[0];
			fRec237[1] = fRec237[0];
			iVec60[1] = iVec60[0];
			iRec242[1] = iRec242[0];
			iRec241[1] = iRec241[0];
			iRec240[1] = iRec240[0];
			iRec239[1] = iRec239[0];
			iVec61[1] = iVec61[0];
			iRec244[1] = iRec244[0];
			fRec243[1] = fRec243[0];
			fRec246[1] = fRec246[0];
			fRec245[1] = fRec245[0];
			iVec62[1] = iVec62[0];
			iRec250[1] = iRec250[0];
			iRec249[1] = iRec249[0];
			iRec248[1] = iRec248[0];
			iRec247[1] = iRec247[0];
			iVec63[1] = iVec63[0];
			iRec252[1] = iRec252[0];
			fRec251[1] = fRec251[0];
			fRec254[1] = fRec254[0];
			fRec253[1] = fRec253[0];
			iVec64[1] = iVec64[0];
			iRec258[1] = iRec258[0];
			iRec257[1] = iRec257[0];
			iRec256[1] = iRec256[0];
			iRec255[1] = iRec255[0];
			iVec65[1] = iVec65[0];
			iRec260[1] = iRec260[0];
			fRec259[1] = fRec259[0];
			fRec262[1] = fRec262[0];
			fRec261[1] = fRec261[0];
			iVec66[1] = iVec66[0];
			iRec266[1] = iRec266[0];
			iRec265[1] = iRec265[0];
			iRec264[1] = iRec264[0];
			iRec263[1] = iRec263[0];
			iVec67[1] = iVec67[0];
			iRec268[1] = iRec268[0];
			fRec267[1] = fRec267[0];
			fRec270[1] = fRec270[0];
			fRec269[1] = fRec269[0];
			iVec68[1] = iVec68[0];
			iRec274[1] = iRec274[0];
			iRec273[1] = iRec273[0];
			iRec272[1] = iRec272[0];
			iRec271[1] = iRec271[0];
			iVec69[1] = iVec69[0];
			iRec276[1] = iRec276[0];
			fRec275[1] = fRec275[0];
			fRec278[1] = fRec278[0];
			fRec277[1] = fRec277[0];
			iVec70[1] = iVec70[0];
			iRec282[1] = iRec282[0];
			iRec281[1] = iRec281[0];
			iRec280[1] = iRec280[0];
			iRec279[1] = iRec279[0];
			iVec71[1] = iVec71[0];
			iRec284[1] = iRec284[0];
			fRec283[1] = fRec283[0];
			fRec286[1] = fRec286[0];
			fRec285[1] = fRec285[0];
			iVec72[1] = iVec72[0];
			iRec290[1] = iRec290[0];
			iRec289[1] = iRec289[0];
			iRec288[1] = iRec288[0];
			iRec287[1] = iRec287[0];
			iVec73[1] = iVec73[0];
			iRec292[1] = iRec292[0];
			fRec291[1] = fRec291[0];
			fRec294[1] = fRec294[0];
			fRec293[1] = fRec293[0];
			iVec74[1] = iVec74[0];
			iRec298[1] = iRec298[0];
			iRec297[1] = iRec297[0];
			iRec296[1] = iRec296[0];
			iRec295[1] = iRec295[0];
			iVec75[1] = iVec75[0];
			iRec300[1] = iRec300[0];
			fRec299[1] = fRec299[0];
			fRec302[1] = fRec302[0];
			fRec301[1] = fRec301[0];
			iVec76[1] = iVec76[0];
			iRec306[1] = iRec306[0];
			iRec305[1] = iRec305[0];
			iRec304[1] = iRec304[0];
			iRec303[1] = iRec303[0];
			iVec77[1] = iVec77[0];
			iRec308[1] = iRec308[0];
			fRec307[1] = fRec307[0];
			fRec310[1] = fRec310[0];
			fRec309[1] = fRec309[0];
			iVec78[1] = iVec78[0];
			iRec314[1] = iRec314[0];
			iRec313[1] = iRec313[0];
			iRec312[1] = iRec312[0];
			iRec311[1] = iRec311[0];
			iVec79[1] = iVec79[0];
			iRec316[1] = iRec316[0];
			fRec315[1] = fRec315[0];
			fRec318[1] = fRec318[0];
			fRec317[1] = fRec317[0];
			iVec80[1] = iVec80[0];
			iRec322[1] = iRec322[0];
			iRec321[1] = iRec321[0];
			iRec320[1] = iRec320[0];
			iRec319[1] = iRec319[0];
			iVec81[1] = iVec81[0];
			iRec324[1] = iRec324[0];
			fRec323[1] = fRec323[0];
			fRec326[1] = fRec326[0];
			fRec325[1] = fRec325[0];
			iVec82[1] = iVec82[0];
			iRec330[1] = iRec330[0];
			iRec329[1] = iRec329[0];
			iRec328[1] = iRec328[0];
			iRec327[1] = iRec327[0];
			iVec83[1] = iVec83[0];
			iRec332[1] = iRec332[0];
			fRec331[1] = fRec331[0];
			fRec334[1] = fRec334[0];
			fRec333[1] = fRec333[0];
			iVec84[1] = iVec84[0];
			iRec338[1] = iRec338[0];
			iRec337[1] = iRec337[0];
			iRec336[1] = iRec336[0];
			iRec335[1] = iRec335[0];
			iVec85[1] = iVec85[0];
			iRec340[1] = iRec340[0];
			fRec339[1] = fRec339[0];
			fRec342[1] = fRec342[0];
			fRec341[1] = fRec341[0];
			iVec86[1] = iVec86[0];
			iRec346[1] = iRec346[0];
			iRec345[1] = iRec345[0];
			iRec344[1] = iRec344[0];
			iRec343[1] = iRec343[0];
			iVec87[1] = iVec87[0];
			iRec348[1] = iRec348[0];
			fRec347[1] = fRec347[0];
			fRec350[1] = fRec350[0];
			fRec349[1] = fRec349[0];
			iVec88[1] = iVec88[0];
			iRec354[1] = iRec354[0];
			iRec353[1] = iRec353[0];
			iRec352[1] = iRec352[0];
			iRec351[1] = iRec351[0];
			iVec89[1] = iVec89[0];
			iRec356[1] = iRec356[0];
			fRec355[1] = fRec355[0];
			fRec358[1] = fRec358[0];
			fRec357[1] = fRec357[0];
			iVec90[1] = iVec90[0];
			iRec362[1] = iRec362[0];
			iRec361[1] = iRec361[0];
			iRec360[1] = iRec360[0];
			iRec359[1] = iRec359[0];
			iVec91[1] = iVec91[0];
			iRec364[1] = iRec364[0];
			fRec363[1] = fRec363[0];
			fRec366[1] = fRec366[0];
			fRec365[1] = fRec365[0];
			iVec92[1] = iVec92[0];
			iRec370[1] = iRec370[0];
			iRec369[1] = iRec369[0];
			iRec368[1] = iRec368[0];
			iRec367[1] = iRec367[0];
			iVec93[1] = iVec93[0];
			iRec372[1] = iRec372[0];
			fRec371[1] = fRec371[0];
			fRec374[1] = fRec374[0];
			fRec373[1] = fRec373[0];
			iVec94[1] = iVec94[0];
			iRec378[1] = iRec378[0];
			iRec377[1] = iRec377[0];
			iRec376[1] = iRec376[0];
			iRec375[1] = iRec375[0];
			iVec95[1] = iVec95[0];
			iRec380[1] = iRec380[0];
			fRec379[1] = fRec379[0];
			fRec382[1] = fRec382[0];
			fRec381[1] = fRec381[0];
			iVec96[1] = iVec96[0];
			iRec386[1] = iRec386[0];
			iRec385[1] = iRec385[0];
			iRec384[1] = iRec384[0];
			iRec383[1] = iRec383[0];
			iVec97[1] = iVec97[0];
			iRec388[1] = iRec388[0];
			fRec387[1] = fRec387[0];
			fRec390[1] = fRec390[0];
			fRec389[1] = fRec389[0];
			iVec98[1] = iVec98[0];
			iRec394[1] = iRec394[0];
			iRec393[1] = iRec393[0];
			iRec392[1] = iRec392[0];
			iRec391[1] = iRec391[0];
			iVec99[1] = iVec99[0];
			iRec396[1] = iRec396[0];
			fRec395[1] = fRec395[0];
			fRec398[1] = fRec398[0];
			fRec397[1] = fRec397[0];
			iVec100[1] = iVec100[0];
			iRec402[1] = iRec402[0];
			iRec401[1] = iRec401[0];
			iRec400[1] = iRec400[0];
			iRec399[1] = iRec399[0];
			iVec101[1] = iVec101[0];
			iRec404[1] = iRec404[0];
			fRec403[1] = fRec403[0];
			fRec406[1] = fRec406[0];
			fRec405[1] = fRec405[0];
			iVec102[1] = iVec102[0];
			iRec410[1] = iRec410[0];
			iRec409[1] = iRec409[0];
			iRec408[1] = iRec408[0];
			iRec407[1] = iRec407[0];
			iVec103[1] = iVec103[0];
			iRec412[1] = iRec412[0];
			fRec411[1] = fRec411[0];
			fRec414[1] = fRec414[0];
			fRec413[1] = fRec413[0];
			iVec104[1] = iVec104[0];
			iRec418[1] = iRec418[0];
			iRec417[1] = iRec417[0];
			iRec416[1] = iRec416[0];
			iRec415[1] = iRec415[0];
			iVec105[1] = iVec105[0];
			iRec420[1] = iRec420[0];
			fRec419[1] = fRec419[0];
			fRec422[1] = fRec422[0];
			fRec421[1] = fRec421[0];
			iVec106[1] = iVec106[0];
			iRec426[1] = iRec426[0];
			iRec425[1] = iRec425[0];
			iRec424[1] = iRec424[0];
			iRec423[1] = iRec423[0];
			iVec107[1] = iVec107[0];
			iRec428[1] = iRec428[0];
			fRec427[1] = fRec427[0];
			fRec430[1] = fRec430[0];
			fRec429[1] = fRec429[0];
			iVec108[1] = iVec108[0];
			iRec434[1] = iRec434[0];
			iRec433[1] = iRec433[0];
			iRec432[1] = iRec432[0];
			iRec431[1] = iRec431[0];
			iVec109[1] = iVec109[0];
			iRec436[1] = iRec436[0];
			fRec435[1] = fRec435[0];
			fRec438[1] = fRec438[0];
			fRec437[1] = fRec437[0];
			iVec110[1] = iVec110[0];
			iRec442[1] = iRec442[0];
			iRec441[1] = iRec441[0];
			iRec440[1] = iRec440[0];
			iRec439[1] = iRec439[0];
			iVec111[1] = iVec111[0];
			iRec444[1] = iRec444[0];
			fRec443[1] = fRec443[0];
			fRec446[1] = fRec446[0];
			fRec445[1] = fRec445[0];
			iVec112[1] = iVec112[0];
			iRec450[1] = iRec450[0];
			iRec449[1] = iRec449[0];
			iRec448[1] = iRec448[0];
			iRec447[1] = iRec447[0];
			iVec113[1] = iVec113[0];
			iRec452[1] = iRec452[0];
			fRec451[1] = fRec451[0];
			fRec454[1] = fRec454[0];
			fRec453[1] = fRec453[0];
			iVec114[1] = iVec114[0];
			iRec458[1] = iRec458[0];
			iRec457[1] = iRec457[0];
			iRec456[1] = iRec456[0];
			iRec455[1] = iRec455[0];
			iVec115[1] = iVec115[0];
			iRec460[1] = iRec460[0];
			fRec459[1] = fRec459[0];
			fRec462[1] = fRec462[0];
			fRec461[1] = fRec461[0];
			iVec116[1] = iVec116[0];
			iRec466[1] = iRec466[0];
			iRec465[1] = iRec465[0];
			iRec464[1] = iRec464[0];
			iRec463[1] = iRec463[0];
			iVec117[1] = iVec117[0];
			iRec468[1] = iRec468[0];
			fRec467[1] = fRec467[0];
			fRec470[1] = fRec470[0];
			fRec469[1] = fRec469[0];
			iVec118[1] = iVec118[0];
			iRec474[1] = iRec474[0];
			iRec473[1] = iRec473[0];
			iRec472[1] = iRec472[0];
			iRec471[1] = iRec471[0];
			iVec119[1] = iVec119[0];
			iRec476[1] = iRec476[0];
			fRec475[1] = fRec475[0];
			fRec478[1] = fRec478[0];
			fRec477[1] = fRec477[0];
			iVec120[1] = iVec120[0];
			iRec482[1] = iRec482[0];
			iRec481[1] = iRec481[0];
			iRec480[1] = iRec480[0];
			iRec479[1] = iRec479[0];
			iVec121[1] = iVec121[0];
			iRec484[1] = iRec484[0];
			fRec483[1] = fRec483[0];
			fRec486[1] = fRec486[0];
			fRec485[1] = fRec485[0];
			iVec122[1] = iVec122[0];
			iRec490[1] = iRec490[0];
			iRec489[1] = iRec489[0];
			iRec488[1] = iRec488[0];
			iRec487[1] = iRec487[0];
			iVec123[1] = iVec123[0];
			iRec492[1] = iRec492[0];
			fRec491[1] = fRec491[0];
			fRec494[1] = fRec494[0];
			fRec493[1] = fRec493[0];
			iVec124[1] = iVec124[0];
			iRec498[1] = iRec498[0];
			iRec497[1] = iRec497[0];
			iRec496[1] = iRec496[0];
			iRec495[1] = iRec495[0];
			iVec125[1] = iVec125[0];
			iRec500[1] = iRec500[0];
			fRec499[1] = fRec499[0];
			fRec502[1] = fRec502[0];
			fRec501[1] = fRec501[0];
			iVec126[1] = iVec126[0];
			iRec506[1] = iRec506[0];
			iRec505[1] = iRec505[0];
			iRec504[1] = iRec504[0];
			iRec503[1] = iRec503[0];
			iVec127[1] = iVec127[0];
			iRec508[1] = iRec508[0];
			fRec507[1] = fRec507[0];
			fRec510[1] = fRec510[0];
			fRec509[1] = fRec509[0];
			iVec128[1] = iVec128[0];
			iRec514[1] = iRec514[0];
			iRec513[1] = iRec513[0];
			iRec512[1] = iRec512[0];
			iRec511[1] = iRec511[0];
			iVec129[1] = iVec129[0];
			iRec516[1] = iRec516[0];
			fRec515[1] = fRec515[0];
			fRec518[1] = fRec518[0];
			fRec517[1] = fRec517[0];
			iVec130[1] = iVec130[0];
			iRec522[1] = iRec522[0];
			iRec521[1] = iRec521[0];
			iRec520[1] = iRec520[0];
			iRec519[1] = iRec519[0];
			iVec131[1] = iVec131[0];
			iRec524[1] = iRec524[0];
			fRec523[1] = fRec523[0];
			fRec526[1] = fRec526[0];
			fRec525[1] = fRec525[0];
			iVec132[1] = iVec132[0];
			iRec530[1] = iRec530[0];
			iRec529[1] = iRec529[0];
			iRec528[1] = iRec528[0];
			iRec527[1] = iRec527[0];
			iVec133[1] = iVec133[0];
			iRec532[1] = iRec532[0];
			fRec531[1] = fRec531[0];
			fRec534[1] = fRec534[0];
			fRec533[1] = fRec533[0];
			iVec134[1] = iVec134[0];
			iRec538[1] = iRec538[0];
			iRec537[1] = iRec537[0];
			iRec536[1] = iRec536[0];
			iRec535[1] = iRec535[0];
			iVec135[1] = iVec135[0];
			iRec540[1] = iRec540[0];
			fRec539[1] = fRec539[0];
			fRec542[1] = fRec542[0];
			fRec541[1] = fRec541[0];
			iVec136[1] = iVec136[0];
			iRec546[1] = iRec546[0];
			iRec545[1] = iRec545[0];
			iRec544[1] = iRec544[0];
			iRec543[1] = iRec543[0];
			iVec137[1] = iVec137[0];
			iRec548[1] = iRec548[0];
			fRec547[1] = fRec547[0];
			fRec550[1] = fRec550[0];
			fRec549[1] = fRec549[0];
			iVec138[1] = iVec138[0];
			iRec554[1] = iRec554[0];
			iRec553[1] = iRec553[0];
			iRec552[1] = iRec552[0];
			iRec551[1] = iRec551[0];
			iVec139[1] = iVec139[0];
			iRec556[1] = iRec556[0];
			fRec555[1] = fRec555[0];
			fRec558[1] = fRec558[0];
			fRec557[1] = fRec557[0];
			iVec140[1] = iVec140[0];
			iRec562[1] = iRec562[0];
			iRec561[1] = iRec561[0];
			iRec560[1] = iRec560[0];
			iRec559[1] = iRec559[0];
			iVec141[1] = iVec141[0];
			iRec564[1] = iRec564[0];
			fRec563[1] = fRec563[0];
			fRec566[1] = fRec566[0];
			fRec565[1] = fRec565[0];
			iVec142[1] = iVec142[0];
			iRec570[1] = iRec570[0];
			iRec569[1] = iRec569[0];
			iRec568[1] = iRec568[0];
			iRec567[1] = iRec567[0];
			iVec143[1] = iVec143[0];
			iRec572[1] = iRec572[0];
			fRec571[1] = fRec571[0];
			fRec574[1] = fRec574[0];
			fRec573[1] = fRec573[0];
			iVec144[1] = iVec144[0];
			iRec578[1] = iRec578[0];
			iRec577[1] = iRec577[0];
			iRec576[1] = iRec576[0];
			iRec575[1] = iRec575[0];
			iVec145[1] = iVec145[0];
			iRec580[1] = iRec580[0];
			fRec579[1] = fRec579[0];
			fRec582[1] = fRec582[0];
			fRec581[1] = fRec581[0];
			iVec146[1] = iVec146[0];
			iRec586[1] = iRec586[0];
			iRec585[1] = iRec585[0];
			iRec584[1] = iRec584[0];
			iRec583[1] = iRec583[0];
			iVec147[1] = iVec147[0];
			iRec588[1] = iRec588[0];
			fRec587[1] = fRec587[0];
			fRec590[1] = fRec590[0];
			fRec589[1] = fRec589[0];
			iVec148[1] = iVec148[0];
			iRec594[1] = iRec594[0];
			iRec593[1] = iRec593[0];
			iRec592[1] = iRec592[0];
			iRec591[1] = iRec591[0];
			iVec149[1] = iVec149[0];
			iRec596[1] = iRec596[0];
			fRec595[1] = fRec595[0];
			fRec598[1] = fRec598[0];
			fRec597[1] = fRec597[0];
			iVec150[1] = iVec150[0];
			iRec602[1] = iRec602[0];
			iRec601[1] = iRec601[0];
			iRec600[1] = iRec600[0];
			iRec599[1] = iRec599[0];
			iVec151[1] = iVec151[0];
			iRec604[1] = iRec604[0];
			fRec603[1] = fRec603[0];
			fRec606[1] = fRec606[0];
			fRec605[1] = fRec605[0];
			iVec152[1] = iVec152[0];
			iRec610[1] = iRec610[0];
			iRec609[1] = iRec609[0];
			iRec608[1] = iRec608[0];
			iRec607[1] = iRec607[0];
			iVec153[1] = iVec153[0];
			iRec612[1] = iRec612[0];
			fRec611[1] = fRec611[0];
			fRec614[1] = fRec614[0];
			fRec613[1] = fRec613[0];
			iVec154[1] = iVec154[0];
			iRec618[1] = iRec618[0];
			iRec617[1] = iRec617[0];
			iRec616[1] = iRec616[0];
			iRec615[1] = iRec615[0];
			iVec155[1] = iVec155[0];
			iRec620[1] = iRec620[0];
			fRec619[1] = fRec619[0];
			fRec622[1] = fRec622[0];
			fRec621[1] = fRec621[0];
			iVec156[1] = iVec156[0];
			iRec626[1] = iRec626[0];
			iRec625[1] = iRec625[0];
			iRec624[1] = iRec624[0];
			iRec623[1] = iRec623[0];
			iVec157[1] = iVec157[0];
			iRec628[1] = iRec628[0];
			fRec627[1] = fRec627[0];
			fRec630[1] = fRec630[0];
			fRec629[1] = fRec629[0];
			iVec158[1] = iVec158[0];
			iRec634[1] = iRec634[0];
			iRec633[1] = iRec633[0];
			iRec632[1] = iRec632[0];
			iRec631[1] = iRec631[0];
			iVec159[1] = iVec159[0];
			iRec636[1] = iRec636[0];
			fRec635[1] = fRec635[0];
			fRec638[1] = fRec638[0];
			fRec637[1] = fRec637[0];
			iVec160[1] = iVec160[0];
			iRec642[1] = iRec642[0];
			iRec641[1] = iRec641[0];
			iRec640[1] = iRec640[0];
			iRec639[1] = iRec639[0];
			iVec161[1] = iVec161[0];
			iRec644[1] = iRec644[0];
			fRec643[1] = fRec643[0];
			fRec646[1] = fRec646[0];
			fRec645[1] = fRec645[0];
			iVec162[1] = iVec162[0];
			iRec650[1] = iRec650[0];
			iRec649[1] = iRec649[0];
			iRec648[1] = iRec648[0];
			iRec647[1] = iRec647[0];
			iVec163[1] = iVec163[0];
			iRec652[1] = iRec652[0];
			fRec651[1] = fRec651[0];
			fRec654[1] = fRec654[0];
			fRec653[1] = fRec653[0];
			fRec0[1] = fRec0[0];
			fRec655[1] = fRec655[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "PDB-Granulator_Realtime.dsp"
	#define FAUST_CLASS_NAME "mydsp"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 8
	#define FAUST_PASSIVES 1

	FAUST_ADDHORIZONTALSLIDER("Rec Grain", fHslider2, 0.0f, 0.0f, 80.0f, 0.10000000000000001f);
	FAUST_ADDHORIZONTALBARGRAPH("Rec Grain Instance:", fHbargraph0, 1.0f, 80.0f);
	FAUST_ADDHORIZONTALSLIDER("Grains Amp In", fHslider1, 1.0f, 0.0f, 10.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Grains Amp Out", fHslider7, 1.0f, 0.0f, 10.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Grains Window", fHslider5, 1.0f, 1.0f, 100.0f, 0.10000000000000001f);
	FAUST_ADDHORIZONTALSLIDER("Rec Feedback", fHslider0, 0.0f, 0.0f, 10.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Panning Speed", fHslider6, 1.0f, 0.0f, 4.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("Grains Freq+", fHslider3, 1.0f, 1.0f, 100.0f, 0.10000000000000001f);
	FAUST_ADDHORIZONTALSLIDER("Grains Freq/", fHslider4, 1.0f, 1.0f, 100.0f, 0.10000000000000001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Rec_Grain, "Rec Grain", fHslider2, 0.0f, 0.0f, 80.0f, 0.10000000000000001f) \
		p(HORIZONTALSLIDER, Grains_Amp_In, "Grains Amp In", fHslider1, 1.0f, 0.0f, 10.0f, 0.01f) \
		p(HORIZONTALSLIDER, Grains_Amp_Out, "Grains Amp Out", fHslider7, 1.0f, 0.0f, 10.0f, 0.01f) \
		p(HORIZONTALSLIDER, Grains_Window, "Grains Window", fHslider5, 1.0f, 1.0f, 100.0f, 0.10000000000000001f) \
		p(HORIZONTALSLIDER, Rec_Feedback, "Rec Feedback", fHslider0, 0.0f, 0.0f, 10.0f, 0.01f) \
		p(HORIZONTALSLIDER, Panning_Speed, "Panning Speed", fHslider6, 1.0f, 0.0f, 4.0f, 0.01f) \
		p(HORIZONTALSLIDER, Grains_Freq+, "Grains Freq+", fHslider3, 1.0f, 1.0f, 100.0f, 0.10000000000000001f) \
		p(HORIZONTALSLIDER, Grains_Freq/, "Grains Freq/", fHslider4, 1.0f, 1.0f, 100.0f, 0.10000000000000001f) \

	#define FAUST_LIST_PASSIVES(p) \
		p(HORIZONTALBARGRAPH, Rec_Grain_Instance:, "Rec Grain Instance:", fHbargraph0, 0.0, 1.0f, 80.0f, 0.0) \

#endif

#if defined(JUCE_POLY)

struct FaustSound : public juce::SynthesiserSound {
    
    bool appliesToNote (int /*midiNoteNumber*/) override        { return true; }
    bool appliesToChannel (int /*midiChannel*/) override        { return true; }
};

// An hybrid JUCE and Faust voice

class FaustVoice : public juce::SynthesiserVoice, public dsp_voice {
    
    private:
        
        std::unique_ptr<juce::AudioBuffer<FAUSTFLOAT>> fBuffer;
        
    public:
        
        FaustVoice(base_dsp* base_dsp):dsp_voice(base_dsp)
        {
            // Allocate buffer for mixing
            fBuffer = std::make_unique<juce::AudioBuffer<FAUSTFLOAT>>(base_dsp->getNumOutputs(), 8192);
            fDSP->init(juce::SynthesiserVoice::getSampleRate());
        }
        
        bool canPlaySound (juce::SynthesiserSound* sound) override
        {
            return dynamic_cast<FaustSound*> (sound) != nullptr;
        }
        
        void startNote (int midiNoteNumber,
                        float velocity,
                        juce::SynthesiserSound* s,
                        int currentPitchWheelPosition) override
        {
            // Note is triggered
            keyOn(midiNoteNumber, velocity);
        }
        
        void stopNote (float velocity, bool allowTailOff) override
        {
            keyOff(!allowTailOff);
        }
        
        void pitchWheelMoved (int newPitchWheelValue) override
        {
            // not implemented for now
        }
        
        void controllerMoved (int controllerNumber, int newControllerValue) override
        {
            // not implemented for now
        }
        
        void renderNextBlock (juce::AudioBuffer<FAUSTFLOAT>& outputBuffer,
                              int startSample,
                              int numSamples) override
        {
            // Only plays when the voice is active
            if (isVoiceActive()) {
                
                // Play the voice
                compute(numSamples, nullptr, (FAUSTFLOAT**)fBuffer->getArrayOfWritePointers());
                
                // Mix it in outputs
                for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                    outputBuffer.addFrom(i, startSample, *fBuffer, i, 0, numSamples);
                }
            }
        }
    
};

// Decorates the JUCE Synthesiser and adds Faust polyphonic code for GUI handling

class FaustSynthesiser : public juce::Synthesiser, public dsp_voice_group {
    
    private:
        
        juce::Synthesiser fSynth;
    
        static void panic(float val, void* arg)
        {
            static_cast<FaustSynthesiser*>(arg)->allNotesOff(0, false); // 0 stops all voices
        }
  
    public:
        
        FaustSynthesiser():dsp_voice_group(panic, this, true, true)
        {
            setNoteStealingEnabled(true);
        }
        
        virtual ~FaustSynthesiser()
        {
            // Voices will be deallocated by fSynth
            dsp_voice_group::clearVoices();
        }
        
        void addVoice(FaustVoice* voice)
        {
            fSynth.addVoice(voice);
            dsp_voice_group::addVoice(voice);
        }
        
        void addSound(juce::SynthesiserSound* sound)
        {
            fSynth.addSound(sound);
        }
        
        void allNotesOff(int midiChannel, bool allowTailOff)
        {
            fSynth.allNotesOff(midiChannel, allowTailOff);
        }
        
        void setCurrentPlaybackSampleRate (double newRate)
        {
            fSynth.setCurrentPlaybackSampleRate(newRate);
        }
        
        void renderNextBlock (juce::AudioBuffer<float>& outputAudio,
                              const juce::MidiBuffer& inputMidi,
                              int startSample,
                              int numSamples)
        {
            fSynth.renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        }
        
        void renderNextBlock (juce::AudioBuffer<double>& outputAudio,
                              const juce::MidiBuffer& inputMidi,
                              int startSample,
                              int numSamples)
        {
            fSynth.renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        }
    
};

#endif

// Using the PluginGuiMagic project (https://foleysfinest.com/developer/pluginguimagic/)

#if defined(PLUGIN_MAGIC)

class FaustPlugInAudioProcessor : public foleys::MagicProcessor, private juce::Timer
{
    
    public:
        FaustPlugInAudioProcessor();
        virtual ~FaustPlugInAudioProcessor() {}
        
        void prepareToPlay (double sampleRate, int samplesPerBlock) override;
        
        bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
        
        void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (! isUsingDoublePrecision());
            process (buffer, midiMessages);
    #ifdef MAGIC_LEVEL_SOURCE
            fOutputMeter->pushSamples(buffer);
    #endif
        }
        
        void processBlock (juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (isUsingDoublePrecision());
            process (buffer, midiMessages);
        }
        
        const juce::String getName() const override;
        
        bool acceptsMidi() const override;
        bool producesMidi() const override;
        double getTailLengthSeconds() const override;
        
        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram (int index) override;
        const juce::String getProgramName (int index) override;
        void changeProgramName (int index, const juce::String& newName) override;
        
        void releaseResources() override
        {}
        
        void timerCallback() override;
        
        juce::AudioProcessor::BusesProperties getBusesProperties();
        bool supportsDoublePrecisionProcessing() const override;
      
    #ifdef MAGIC_LEVEL_SOURCE
        foleys::MagicLevelSource* fOutputMeter = nullptr;
    #endif
        juce::AudioProcessorValueTreeState treeState{ *this, nullptr };
    
    #ifdef JUCE_POLY
        std::unique_ptr<FaustSynthesiser> fSynth;
    #else
    #if defined(MIDICTRL)
        std::unique_ptr<juce_midi_handler> fMIDIHandler;
        std::unique_ptr<MidiUI> fMIDIUI;
    #endif
        std::unique_ptr<base_dsp> fDSP;
    #endif
        
    #if defined(OSCCTRL)
        std::unique_ptr<JuceOSCUI> fOSCUI;
    #endif
        
    #if defined(SOUNDFILE)
        std::unique_ptr<SoundUI> fSoundUI;
    #endif
        
        JuceStateUI fStateUI;
        JuceParameterUI fParameterUI;
        
        bool fIsPrepared = false;
        
    private:
        
        template <typename FloatType>
        void process (juce::AudioBuffer<FloatType>& buffer, juce::MidiBuffer& midiMessages);
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessor)
    
};

#else

class FaustPlugInAudioProcessor : public juce::AudioProcessor, private juce::Timer
{

    public:
        
        FaustPlugInAudioProcessor();
        virtual ~FaustPlugInAudioProcessor() {}
        
        void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    
        bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
        
        void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (! isUsingDoublePrecision());
            process (buffer, midiMessages);
        }
        
        void processBlock (juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (isUsingDoublePrecision());
            process (buffer, midiMessages);
        }
    
        juce::AudioProcessorEditor* createEditor() override;
        bool hasEditor() const override;
        
        const juce::String getName() const override;
        
        bool acceptsMidi() const override;
        bool producesMidi() const override;
        double getTailLengthSeconds() const override;
        
        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram (int index) override;
        const juce::String getProgramName (int index) override;
        void changeProgramName (int index, const juce::String& newName) override;
        
        void getStateInformation (juce::MemoryBlock& destData) override;
        void setStateInformation (const void* data, int sizeInBytes) override;
    
        void releaseResources() override
        {}
        
        void timerCallback() override;
    
        juce::AudioProcessor::BusesProperties getBusesProperties();
        bool supportsDoublePrecisionProcessing() const override;
    
    #ifdef JUCE_POLY
        std::unique_ptr<FaustSynthesiser> fSynth;
    #else
    #if defined(MIDICTRL)
        std::unique_ptr<juce_midi_handler> fMIDIHandler;
        std::unique_ptr<MidiUI> fMIDIUI;
    #endif
        std::unique_ptr<base_dsp> fDSP;
    #endif
        
    #if defined(OSCCTRL)
        std::unique_ptr<JuceOSCUI> fOSCUI;
    #endif
    
    #if defined(SOUNDFILE)
        std::unique_ptr<SoundUI> fSoundUI;
    #endif
    
        JuceStateUI fStateUI;
        JuceParameterUI fParameterUI;
    
        bool fIsPrepared = false;
    
    private:
    
        template <typename FloatType>
        void process (juce::AudioBuffer<FloatType>& buffer, juce::MidiBuffer& midiMessages);
    
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessor)
    
};

#endif

class FaustPlugInAudioProcessorEditor : public juce::AudioProcessorEditor
{
    
    public:
        
        FaustPlugInAudioProcessorEditor (FaustPlugInAudioProcessor&);
        virtual ~FaustPlugInAudioProcessorEditor() {}
        
        void paint (juce::Graphics&) override;
        void resized() override;
        
    private:
        
        // This reference is provided as a quick way for your editor to
        // access the processor object that created it.
        FaustPlugInAudioProcessor& processor;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessorEditor)
#ifndef PLUGIN_MAGIC        
        JuceGUI fJuceGUI;
#endif    
};

#ifndef PLUGIN_MAGIC
FaustPlugInAudioProcessor::FaustPlugInAudioProcessor()
: juce::AudioProcessor (getBusesProperties()), fParameterUI(this)
#else
FaustPlugInAudioProcessor::FaustPlugInAudioProcessor()
: foleys::MagicProcessor (getBusesProperties()), fParameterUI(this)	
#endif
{
    bool midi_sync = false;
    int nvoices = 0;
    
    mydsp* tmp_dsp = new mydsp();
    MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
    delete tmp_dsp;
	
#ifdef PLUGIN_MAGIC
#ifdef MAGIC_LOAD_BINARY
    // change magic_xml and magic_xmlSize to match the name of your included
    // XML file from Plugin GUI Magic
    magicState.setGuiValueTree(BinaryData::magic_xml, BinaryData::magic_xmlSize);
#endif
// put other GUI Magic sources here, similar to expression below.
#ifdef MAGIC_LEVEL_SOURCE
    fOutputMeter = magicState.createAndAddObject<foleys::MagicLevelSource>("output");
#endif
#endif
   
#ifdef JUCE_POLY
    assert(nvoices > 0);
    fSynth = std::make_unique<FaustSynthesiser>();
    for (int i = 0; i < nvoices; i++) {
        fSynth->addVoice(new FaustVoice(new mydsp()));
    }
    fSynth->init();
    fSynth->addSound(new FaustSound());
#else
    
    bool group = true;
    
#ifdef POLY2
    assert(nvoices > 0);
    std::cout << "Started with " << nvoices << " voices\n";
    base_dsp* base_dsp = new mydsp_poly(new mydsp(), nvoices, true, group);
    
#if MIDICTRL
    if (midi_sync) {
        fDSP = std::make_unique<timed_dsp>(new dsp_sequencer(base_dsp, new effect()));
    } else {
        fDSP = std::make_unique<dsp_sequencer>(base_dsp, new effect());
    }
#else
    fDSP = std::make_unique<dsp_sequencer>(base_dsp, new effects());
#endif
    
#else
    if (nvoices > 0) {
        std::cout << "Started with " << nvoices << " voices\n";
        base_dsp* base_dsp = new mydsp_poly(new mydsp(), nvoices, true, group);
        
#if MIDICTRL
        if (midi_sync) {
            fDSP = std::make_unique<timed_dsp>(base_dsp);
        } else {
            fDSP = std::make_unique<decorator_dsp>(base_dsp);
        }
#else
        fDSP = std::make_unique<decorator_dsp>(base_dsp);
#endif
    } else {
#if MIDICTRL
        if (midi_sync) {
            fDSP = std::make_unique<timed_dsp>(new mydsp());
        } else {
            fDSP = std::make_unique<mydsp>();
        }
#else
        fDSP = std::make_unique<mydsp>();
#endif
    }
    
#endif
    
#if defined(MIDICTRL)
    fMIDIHandler = std::make_unique<juce_midi_handler>();
    fMIDIUI = std::make_unique<MidiUI>(fMIDIHandler.get());
    fDSP->buildUserInterface(fMIDIUI.get());
    if (!fMIDIUI->run()) {
        std::cerr << "JUCE MIDI handler cannot be started..." << std::endl;
    }
#endif
    
#endif
    
#if defined(OSCCTRL)
    fOSCUI = std::make_unique<JuceOSCUI>("127.0.0.1", 5510, 5511);
#ifdef JUCE_POLY
    fSynth->buildUserInterface(fOSCUI.get());
#else
    fDSP->buildUserInterface(fOSCUI.get());
#endif
    if (!fOSCUI->run()) {
        std::cerr << "JUCE OSC handler cannot be started..." << std::endl;
    }
#endif
    
#if defined(SOUNDFILE)
    // Use bundle path
    auto file = juce::File::getSpecialLocation(juce::File::currentExecutableFile)
        .getParentDirectory().getParentDirectory().getChildFile("Resources");
    fSoundUI = std::make_unique<SoundUI>(file.getFullPathName().toStdString());
    fDSP->buildUserInterface(fSoundUI.get());
#endif
    
#ifdef JUCE_POLY
    fSynth->buildUserInterface(&fStateUI);
    fSynth->buildUserInterface(&fParameterUI);
    // When no previous state was restored, init DSP controllers with their default values
    if (!fStateUI.fRestored) {
        fSynth->instanceResetUserInterface();
    }
#else
    fDSP->buildUserInterface(&fStateUI);
    fDSP->buildUserInterface(&fParameterUI);
    // When no previous state was restored, init DSP controllers with their default values
    if (!fStateUI.fRestored) {
        fDSP->instanceResetUserInterface();
    }
#endif
    
    startTimerHz(25);
}

juce::AudioProcessor::BusesProperties FaustPlugInAudioProcessor::getBusesProperties()
{
    if (juce::PluginHostType::getPluginLoadedAs() == wrapperType_Standalone) {
        if (FAUST_INPUTS == 0) {
            return BusesProperties().withOutput("Output", juce::AudioChannelSet::discreteChannels(std::min<int>(2, FAUST_OUTPUTS)), true);
        } else {
            return BusesProperties()
            .withInput("Input", juce::AudioChannelSet::discreteChannels(std::min<int>(2, FAUST_INPUTS)), true)
            .withOutput("Output", juce::AudioChannelSet::discreteChannels(std::min<int>(2, FAUST_OUTPUTS)), true);
        }
    } else {
        if (FAUST_OUTPUTS == 0) {
            return BusesProperties().withOutput("Output", juce::AudioChannelSet::discreteChannels(FAUST_OUTPUTS), true);
        } else {
            return BusesProperties()
            .withInput("Input", juce::AudioChannelSet::discreteChannels(FAUST_INPUTS), true)
            .withOutput("Output", juce::AudioChannelSet::discreteChannels(FAUST_OUTPUTS), true);
        }
    }
}

void FaustPlugInAudioProcessor::timerCallback()
{
    GUI::updateAllGuis();
}

//==============================================================================
const juce::String FaustPlugInAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FaustPlugInAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool FaustPlugInAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

double FaustPlugInAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FaustPlugInAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int FaustPlugInAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FaustPlugInAudioProcessor::setCurrentProgram (int index)
{}

const juce::String FaustPlugInAudioProcessor::getProgramName (int index)
{
    return juce::String();
}

void FaustPlugInAudioProcessor::changeProgramName (int index, const juce::String& newName)
{}

bool FaustPlugInAudioProcessor::supportsDoublePrecisionProcessing() const
{
    return sizeof(FAUSTFLOAT) == 8;
}

//==============================================================================
void FaustPlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // prepareToPlay may be called several times (like in VST3 context)
    if (fIsPrepared) return;
    
    // Use this method as the place to do any pre-playback
    // initialisation that you need...
    
    fIsPrepared = true;
    
#ifdef JUCE_POLY
    fSynth->setCurrentPlaybackSampleRate (sampleRate);
#else
    
    // Possible sample size adaptation
    if (sizeof(FAUSTFLOAT) == 8) {
        fDSP = std::make_unique<dsp_sample_adapter<FAUSTFLOAT, float>>(fDSP.release());
    }
    
    // Possibly adapt DSP inputs/outputs number
    if (fDSP->getNumInputs() > getTotalNumInputChannels() || fDSP->getNumOutputs() > getTotalNumOutputChannels()) {
        fDSP = std::make_unique<dsp_adapter>(fDSP.release(), getTotalNumInputChannels(), getTotalNumOutputChannels(), 4096);
    }
   
    // Setting the DSP control values has already been done
    // by 'buildUserInterface(&fStateUI)', using the saved values or the default ones.
    // What has to be done to finish the DSP initialization is done now.
    mydsp::classInit(int(sampleRate));
    fDSP->instanceConstants(int(sampleRate));
    fDSP->instanceClear();
    
#endif
#ifdef MAGIC_LEVEL_SOURCE
    magicState.prepareToPlay(sampleRate, samplesPerBlock);
    fOutputMeter->setupSource(getMainBusNumOutputChannels(), sampleRate, 500, 200);
#endif
}

bool FaustPlugInAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#ifdef JUCE_POLY
    return true;
#else
    
#if JucePlugin_IsSynth
    // Stereo is supported
    return (layouts.getMainOutputChannelSet().size() == 2) || (layouts.getMainOutputChannelSet().size() == fDSP->getNumOutputs());
#else
    // Stereo is supported
    return
    ((layouts.getMainInputChannelSet().size() == 2) && (layouts.getMainOutputChannelSet().size() == 2))
    ||
    ((layouts.getMainInputChannelSet().size() == fDSP->getNumInputs()) && (layouts.getMainOutputChannelSet().size() == fDSP->getNumOutputs()));
#endif
    
#endif
}

template <typename FloatType>
void FaustPlugInAudioProcessor::process (juce::AudioBuffer<FloatType>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
#ifdef JUCE_POLY
    fSynth->renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
#else
#if defined(MIDICTRL)
    // Read MIDI input events from midiMessages
    fMIDIHandler->decodeBuffer(midiMessages);
    // Then write MIDI output events to midiMessages
    fMIDIHandler->encodeBuffer(midiMessages);
#endif
    // MIDI timestamp is expressed in frames
    fDSP->compute(-1, buffer.getNumSamples(),
                  (FAUSTFLOAT**)buffer.getArrayOfReadPointers(),
                  (FAUSTFLOAT**)buffer.getArrayOfWritePointers());
#endif
}

//==============================================================================
#ifndef PLUGIN_MAGIC
bool FaustPlugInAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* FaustPlugInAudioProcessor::createEditor()
{
    return new FaustPlugInAudioProcessorEditor (*this);
}

//==============================================================================
void FaustPlugInAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    fStateUI.getStateInformation(destData);
}

void FaustPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    fStateUI.setStateInformation(data, sizeInBytes);
 }
#endif
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FaustPlugInAudioProcessor();
}

//==============================================================================
#ifndef PLUGIN_MAGIC
FaustPlugInAudioProcessorEditor::FaustPlugInAudioProcessorEditor (FaustPlugInAudioProcessor& p)
: juce::AudioProcessorEditor (&p), processor (p), fJuceGUI(!p.fStateUI.fRestored)  // When no previous state was restored, setup GUI with default state of controllers
{
#ifdef JUCE_POLY
    p.fSynth->buildUserInterface(&fJuceGUI);
#else
    p.fDSP->buildUserInterface(&fJuceGUI);
#endif
    
    addAndMakeVisible(fJuceGUI);
    
    juce::Rectangle<int> recommendedSize = fJuceGUI.getSize();
    setSize (recommendedSize.getWidth(), recommendedSize.getHeight());
}

//==============================================================================
void FaustPlugInAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void FaustPlugInAudioProcessorEditor::resized()
{
    fJuceGUI.setBounds(getLocalBounds());
}

#endif
// Globals
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

#endif
