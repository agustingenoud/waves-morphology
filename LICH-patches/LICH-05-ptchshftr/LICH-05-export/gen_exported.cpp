#include "gen_exported.h"

namespace gen_exported {

/****************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER 200k USD in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below 200k USD annual revenue or funding.

For entities with OVER 200k USD in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing (at) cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/360050779193-Gen-Code-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
****************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Delay m_delay_5;
	Delay m_delay_10;
	Delta __m_delta_25;
	Delta __m_delta_19;
	Delta __m_delta_32;
	Delta __m_delta_16;
	Delta __m_delta_29;
	Delta __m_delta_22;
	Delta __m_delta_35;
	Delta __m_delta_38;
	Phasor __m_phasor_15;
	Phasor __m_phasor_28;
	Sah __m_sah_23;
	Sah __m_sah_24;
	Sah __m_sah_26;
	Sah __m_sah_40;
	Sah __m_sah_30;
	Sah __m_sah_36;
	Sah __m_sah_37;
	Sah __m_sah_27;
	Sah __m_sah_34;
	Sah __m_sah_31;
	Sah __m_sah_33;
	Sah __m_sah_21;
	Sah __m_sah_18;
	Sah __m_sah_39;
	Sah __m_sah_17;
	Sah __m_sah_20;
	int vectorsize;
	int __exception;
	t_sample m_A_12;
	t_sample m_history_2;
	t_sample m_history_3;
	t_sample m_history_1;
	t_sample samples_to_seconds;
	t_sample samplerate;
	t_sample m_D_13;
	t_sample m_history_4;
	t_sample m_C_14;
	t_sample m_B_11;
	t_sample m_history_6;
	t_sample m_history_9;
	t_sample m_history_8;
	t_sample m_history_7;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_delay_5.reset("m_delay_5", ((int)88200));
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_delay_10.reset("m_delay_10", ((int)88200));
		m_B_11 = ((int)0);
		m_A_12 = ((int)0);
		m_D_13 = ((int)0);
		m_C_14 = ((int)0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_15.reset(0);
		__m_delta_16.reset(0);
		__m_sah_17.reset(0);
		__m_sah_18.reset(0);
		__m_delta_19.reset(0);
		__m_sah_20.reset(0);
		__m_sah_21.reset(0);
		__m_delta_22.reset(0);
		__m_sah_23.reset(0);
		__m_sah_24.reset(0);
		__m_delta_25.reset(0);
		__m_sah_26.reset(0);
		__m_sah_27.reset(0);
		__m_phasor_28.reset(0);
		__m_delta_29.reset(0);
		__m_sah_30.reset(0);
		__m_sah_31.reset(0);
		__m_delta_32.reset(0);
		__m_sah_33.reset(0);
		__m_sah_34.reset(0);
		__m_delta_35.reset(0);
		__m_sah_36.reset(0);
		__m_sah_37.reset(0);
		__m_delta_38.reset(0);
		__m_sah_39.reset(0);
		__m_sah_40.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample mul_2729 = (m_A_12 * ((int)2));
		t_sample mstosamps_2145 = (((int)64) * (samplerate * 0.001));
		t_sample rsub_2131 = (((int)1) - mul_2729);
		t_sample mul_2130 = (rsub_2131 * ((int)1000));
		t_sample div_2129 = (mul_2130 * ((t_sample)0.015625));
		samples_to_seconds = (1 / samplerate);
		t_sample add_3047 = (m_B_11 + ((t_sample)0.11));
		t_sample add_3058 = (mul_2729 + add_3047);
		t_sample mstosamps_2319 = (((int)64) * (samplerate * 0.001));
		t_sample rsub_2305 = (((int)1) - add_3058);
		t_sample mul_2304 = (rsub_2305 * ((int)1000));
		t_sample div_2303 = (mul_2304 * ((t_sample)0.015625));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample phasor_2090 = __m_phasor_15(div_2129, samples_to_seconds);
			t_sample add_2122 = ((m_history_9 + phasor_2090) + ((t_sample)0.75));
			t_sample mod_2121 = safemod(add_2122, ((int)1));
			t_sample delta_2107 = __m_delta_16(mod_2121);
			int sah_2092 = __m_sah_17(((int)0), delta_2107, ((int)0));
			t_sample sah_2106 = __m_sah_18(mstosamps_2145, delta_2107, ((int)0));
			t_sample mul_2102 = (sah_2106 * mod_2121);
			t_sample sub_2120 = (mod_2121 - ((t_sample)0.5));
			t_sample mul_2119 = (sub_2120 * ((t_sample)3.1415926535898));
			t_sample cos_2118 = cos(mul_2119);
			t_sample mul_2113 = (cos_2118 * cos_2118);
			t_sample add_2128 = ((m_history_8 + phasor_2090) + ((t_sample)0.5));
			t_sample mod_2127 = safemod(add_2128, ((int)1));
			t_sample delta_2109 = __m_delta_19(mod_2127);
			int sah_2094 = __m_sah_20(((int)0), delta_2109, ((int)0));
			t_sample sah_2108 = __m_sah_21(mstosamps_2145, delta_2109, ((int)0));
			t_sample mul_2103 = (sah_2108 * mod_2127);
			t_sample sub_2126 = (mod_2127 - ((t_sample)0.5));
			t_sample mul_2125 = (sub_2126 * ((t_sample)3.1415926535898));
			t_sample cos_2124 = cos(mul_2125);
			t_sample mul_2114 = (cos_2124 * cos_2124);
			t_sample add_2144 = ((m_history_7 + phasor_2090) + ((t_sample)0.25));
			t_sample mod_2143 = safemod(add_2144, ((int)1));
			t_sample delta_2111 = __m_delta_22(mod_2143);
			int sah_2096 = __m_sah_23(((int)0), delta_2111, ((int)0));
			t_sample sah_2110 = __m_sah_24(mstosamps_2145, delta_2111, ((int)0));
			t_sample mul_2104 = (sah_2110 * mod_2143);
			t_sample sub_2142 = (mod_2143 - ((t_sample)0.5));
			t_sample mul_2141 = (sub_2142 * ((t_sample)3.1415926535898));
			t_sample cos_2140 = cos(mul_2141);
			t_sample mul_2115 = (cos_2140 * cos_2140);
			t_sample add_2150 = ((m_history_6 + phasor_2090) + ((int)0));
			t_sample mod_2149 = safemod(add_2150, ((int)1));
			t_sample delta_2099 = __m_delta_25(mod_2149);
			int sah_2098 = __m_sah_26(((int)0), delta_2099, ((int)0));
			t_sample sah_2112 = __m_sah_27(mstosamps_2145, delta_2099, ((int)0));
			t_sample mul_2105 = (sah_2112 * mod_2149);
			t_sample tap_2136 = m_delay_10.read_linear(mul_2105);
			t_sample tap_2137 = m_delay_10.read_linear(mul_2104);
			t_sample tap_2138 = m_delay_10.read_linear(mul_2103);
			t_sample tap_2139 = m_delay_10.read_linear(mul_2102);
			t_sample mul_2123 = (tap_2138 * mul_2114);
			t_sample mul_2133 = (tap_2137 * mul_2115);
			t_sample mul_2117 = (tap_2139 * mul_2113);
			t_sample add_3090 = (mul_2117 + mul_2133);
			t_sample mix_3089 = (in1 + (((int)1) * (add_3090 - in1)));
			t_sample sub_2148 = (mod_2149 - ((t_sample)0.5));
			t_sample mul_2147 = (sub_2148 * ((t_sample)3.1415926535898));
			t_sample cos_2146 = cos(mul_2147);
			t_sample mul_2116 = (cos_2146 * cos_2146);
			t_sample mul_2134 = (tap_2136 * mul_2116);
			t_sample add_3092 = (mul_2123 + mul_2134);
			t_sample mix_3091 = (in1 + (((int)1) * (add_3092 - in1)));
			t_sample history_2093_next_2254 = fixdenorm(sah_2092);
			t_sample history_2095_next_2255 = fixdenorm(sah_2094);
			t_sample history_2097_next_2256 = fixdenorm(sah_2096);
			t_sample history_2100_next_2257 = fixdenorm(sah_2098);
			t_sample mul_1701 = (mix_3089 * ((int)1));
			t_sample mul_1702 = (mix_3091 * ((int)1));
			t_sample phasor_2264 = __m_phasor_28(div_2303, samples_to_seconds);
			t_sample add_2302 = ((phasor_2264 + m_history_4) + ((t_sample)0.5));
			t_sample mod_2301 = safemod(add_2302, ((int)1));
			t_sample delta_2283 = __m_delta_29(mod_2301);
			int sah_2268 = __m_sah_30(((int)0), delta_2283, ((int)0));
			t_sample sah_2282 = __m_sah_31(mstosamps_2319, delta_2283, ((int)0));
			t_sample mul_2277 = (sah_2282 * mod_2301);
			t_sample sub_2300 = (mod_2301 - ((t_sample)0.5));
			t_sample mul_2299 = (sub_2300 * ((t_sample)3.1415926535898));
			t_sample cos_2298 = cos(mul_2299);
			t_sample mul_2288 = (cos_2298 * cos_2298);
			t_sample add_2318 = ((phasor_2264 + m_history_3) + ((t_sample)0.25));
			t_sample mod_2317 = safemod(add_2318, ((int)1));
			t_sample delta_2285 = __m_delta_32(mod_2317);
			int sah_2270 = __m_sah_33(((int)0), delta_2285, ((int)0));
			t_sample sah_2284 = __m_sah_34(mstosamps_2319, delta_2285, ((int)0));
			t_sample mul_2278 = (sah_2284 * mod_2317);
			t_sample sub_2316 = (mod_2317 - ((t_sample)0.5));
			t_sample mul_2315 = (sub_2316 * ((t_sample)3.1415926535898));
			t_sample cos_2314 = cos(mul_2315);
			t_sample mul_2289 = (cos_2314 * cos_2314);
			t_sample add_2296 = ((phasor_2264 + m_history_2) + ((t_sample)0.75));
			t_sample mod_2295 = safemod(add_2296, ((int)1));
			t_sample delta_2281 = __m_delta_35(mod_2295);
			int sah_2266 = __m_sah_36(((int)0), delta_2281, ((int)0));
			t_sample sah_2280 = __m_sah_37(mstosamps_2319, delta_2281, ((int)0));
			t_sample mul_2276 = (sah_2280 * mod_2295);
			t_sample sub_2294 = (mod_2295 - ((t_sample)0.5));
			t_sample mul_2293 = (sub_2294 * ((t_sample)3.1415926535898));
			t_sample cos_2292 = cos(mul_2293);
			t_sample mul_2287 = (cos_2292 * cos_2292);
			t_sample add_2324 = ((phasor_2264 + m_history_1) + ((int)0));
			t_sample mod_2323 = safemod(add_2324, ((int)1));
			t_sample delta_2273 = __m_delta_38(mod_2323);
			int sah_2272 = __m_sah_39(((int)0), delta_2273, ((int)0));
			t_sample sah_2286 = __m_sah_40(mstosamps_2319, delta_2273, ((int)0));
			t_sample mul_2279 = (sah_2286 * mod_2323);
			t_sample tap_2310 = m_delay_5.read_linear(mul_2279);
			t_sample tap_2311 = m_delay_5.read_linear(mul_2278);
			t_sample tap_2312 = m_delay_5.read_linear(mul_2277);
			t_sample tap_2313 = m_delay_5.read_linear(mul_2276);
			t_sample mul_2291 = (tap_2313 * mul_2287);
			t_sample mul_2307 = (tap_2311 * mul_2289);
			t_sample add_3094 = (mul_2307 + mul_2291);
			t_sample mix_3093 = (in1 + (((int)1) * (add_3094 - in1)));
			t_sample mul_2297 = (tap_2312 * mul_2288);
			t_sample sub_2322 = (mod_2323 - ((t_sample)0.5));
			t_sample mul_2321 = (sub_2322 * ((t_sample)3.1415926535898));
			t_sample cos_2320 = cos(mul_2321);
			t_sample mul_2290 = (cos_2320 * cos_2320);
			t_sample mul_2308 = (tap_2310 * mul_2290);
			t_sample add_3096 = (mul_2308 + mul_2297);
			t_sample mix_3095 = (in1 + (((int)1) * (add_3096 - in1)));
			t_sample history_2269_next_2325 = fixdenorm(sah_2268);
			t_sample history_2271_next_2326 = fixdenorm(sah_2270);
			t_sample history_2267_next_2327 = fixdenorm(sah_2266);
			t_sample history_2274_next_2328 = fixdenorm(sah_2272);
			t_sample out2 = (mix_3093 + mul_1701);
			t_sample out1 = (mix_3095 + mul_1702);
			m_delay_10.write(in1);
			m_history_6 = history_2100_next_2257;
			m_history_7 = history_2097_next_2256;
			m_history_8 = history_2095_next_2255;
			m_history_9 = history_2093_next_2254;
			m_delay_5.write(in1);
			m_history_1 = history_2274_next_2328;
			m_history_2 = history_2267_next_2327;
			m_history_3 = history_2271_next_2326;
			m_history_4 = history_2269_next_2325;
			m_delay_5.step();
			m_delay_10.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_B(t_param _value) {
		m_B_11 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_A(t_param _value) {
		m_A_12 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_D(t_param _value) {
		m_D_13 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_C(t_param _value) {
		m_C_14 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 4; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_A(value); break;
		case 1: self->set_B(value); break;
		case 2: self->set_C(value); break;
		case 3: self->set_D(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_A_12; break;
		case 1: *value = self->m_B_11; break;
		case 2: *value = self->m_C_14; break;
		case 3: *value = self->m_D_13; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(4 * sizeof(ParamInfo));
	self->__commonstate.numparams = 4;
	// initialize parameter 0 ("m_A_12")
	pi = self->__commonstate.params + 0;
	pi->name = "A";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_A_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_B_11")
	pi = self->__commonstate.params + 1;
	pi->name = "B";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_B_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_C_14")
	pi = self->__commonstate.params + 2;
	pi->name = "C";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_C_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_D_13")
	pi = self->__commonstate.params + 3;
	pi->name = "D";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_D_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // gen_exported::
