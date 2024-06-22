#include "dl_fdbck.h"

namespace dl_fdbck {

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
	Change __m_change_11;
	Change __m_change_15;
	Delay m_delay_2;
	PlusEquals __m_pluseq_14;
	PlusEquals __m_pluseq_18;
	int __exception;
	int vectorsize;
	t_sample m_history_4;
	t_sample __m_latch_13;
	t_sample __m_latch_12;
	t_sample samplerate;
	t_sample __m_latch_16;
	t_sample m_history_3;
	t_sample m_history_1;
	t_sample m_B_9;
	t_sample m_ButtonA_5;
	t_sample m_A_10;
	t_sample m_ButtonB_6;
	t_sample __m_latch_17;
	t_sample m_C_7;
	t_sample m_D_8;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_delay_2.reset("m_delay_2", ((int)44100));
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_ButtonA_5 = ((int)0);
		m_ButtonB_6 = ((int)0);
		m_C_7 = ((int)0);
		m_D_8 = ((int)0);
		m_B_9 = 0.5;
		m_A_10 = 200;
		__m_change_11.reset(0);
		__m_latch_12 = 0;
		__m_latch_13 = 0;
		__m_pluseq_14.reset(0);
		__m_change_15.reset(0);
		__m_latch_16 = 0;
		__m_latch_17 = 0;
		__m_pluseq_18.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		t_sample * __out4 = __outs[3];
		t_sample * __out5 = __outs[4];
		t_sample * __out6 = __outs[5];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample sub_516 = (m_D_8 - ((int)0));
		t_sample scale_513 = ((safepow((sub_516 * ((t_sample)1)), ((int)1)) * ((t_sample)1.25)) + ((int)0));
		t_sample sub_434 = (scale_513 - ((t_sample)0.25));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out4 = ((int)0);
			t_sample out3 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample expr_440 = trapezoid_d_d_d_d_d(scale_513, ((t_sample)0.3), ((t_sample)0.4), ((t_sample)0.7), ((t_sample)0.8));
			t_sample expr_441 = trapezoid_d_d_d_d_d(sub_434, ((t_sample)0.3), ((t_sample)0.4), ((t_sample)0.7), ((t_sample)0.8));
			t_sample mul_438 = (in1 * expr_440);
			t_sample mul_432 = (in2 * expr_441);
			t_sample gen_442 = (mul_432 + mul_438);
			int change_452 = __m_change_11(m_B_9);
			__m_latch_12 = ((change_452 != 0) ? m_history_4 : __m_latch_12);
			t_sample latch_449 = __m_latch_12;
			__m_latch_13 = ((change_452 != 0) ? m_B_9 : __m_latch_13);
			t_sample latch_448 = __m_latch_13;
			t_sample plusequals_450 = __m_pluseq_14.pre(((t_sample)0.0020614306328592), change_452, 0);
			t_sample clamp_445 = ((plusequals_450 <= ((int)0)) ? ((int)0) : ((plusequals_450 >= ((int)1)) ? ((int)1) : plusequals_450));
			t_sample mix_517 = (latch_449 + (clamp_445 * (latch_448 - latch_449)));
			t_sample mix_447 = mix_517;
			t_sample gen_476 = mix_447;
			t_sample history_446_next_453 = fixdenorm(mix_447);
			t_sample fdbck_474 = gen_476;
			t_sample fdbck_472 = fdbck_474;
			int change_503 = __m_change_15(m_A_10);
			__m_latch_16 = ((change_503 != 0) ? m_history_3 : __m_latch_16);
			t_sample latch_511 = __m_latch_16;
			__m_latch_17 = ((change_503 != 0) ? m_A_10 : __m_latch_17);
			t_sample latch_509 = __m_latch_17;
			t_sample plusequals_506 = __m_pluseq_18.pre(((t_sample)0.00018435558505245), change_503, 0);
			t_sample clamp_507 = ((plusequals_506 <= ((int)0)) ? ((int)0) : ((plusequals_506 >= ((int)1)) ? ((int)1) : plusequals_506));
			t_sample mix_518 = (latch_511 + (clamp_507 * (latch_509 - latch_511)));
			t_sample mix_502 = mix_518;
			t_sample gen_454 = mix_502;
			t_sample history_446_next_508 = fixdenorm(mix_502);
			t_sample sub_522 = (gen_454 - ((int)0));
			t_sample scale_519 = ((safepow((sub_522 * ((t_sample)1)), ((int)1)) * ((int)999)) + ((int)1));
			t_sample scale_495 = scale_519;
			t_sample mstosamps_496 = (scale_495 * (samplerate * 0.001));
			t_sample tap_498 = m_delay_2.read_linear(mstosamps_496);
			t_sample clamp_468 = ((tap_498 <= ((t_sample)-0.9)) ? ((t_sample)-0.9) : ((tap_498 >= ((t_sample)0.9)) ? ((t_sample)0.9) : tap_498));
			t_sample sub_465 = (tap_498 - clamp_468);
			t_sample div_464 = (sub_465 * ((t_sample)10));
			t_sample mul_460 = (div_464 * div_464);
			t_sample add_459 = (mul_460 + ((int)1));
			t_sample sqrt_458 = sqrt(add_459);
			t_sample div_461 = safediv(div_464, sqrt_458);
			t_sample gen_462 = div_461;
			t_sample mul_457 = (gen_462 * ((t_sample)0.1));
			t_sample add_456 = (mul_457 + clamp_468);
			t_sample mul_473 = (add_456 * fdbck_472);
			t_sample mul_471 = (mul_473 * ((t_sample)0.5));
			t_sample OutRight_500 = (gen_442 + mul_471);
			t_sample out2 = OutRight_500;
			t_sample mul_494 = (add_456 * fdbck_474);
			t_sample mul_470 = (mul_494 * ((t_sample)0.5));
			t_sample OutLeft_501 = (gen_442 + mul_470);
			t_sample out1 = OutLeft_501;
			t_sample add_493 = (in1 + (mul_470 + mul_471));
			t_sample sub_488 = (add_493 - m_history_1);
			t_sample mul_487 = (sub_488 * ((t_sample)0.00021366812538747));
			t_sample add_486 = (mul_487 + m_history_1);
			t_sample sub_478 = (add_493 - add_486);
			t_sample history_485_next_489 = fixdenorm((add_486 + mul_487));
			m_history_4 = history_446_next_453;
			m_history_3 = history_446_next_508;
			m_delay_2.write(sub_478);
			m_history_1 = history_485_next_489;
			m_delay_2.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			
		};
		return __exception;
		
	};
	inline void set_ButtonA(t_param _value) {
		m_ButtonA_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ButtonB(t_param _value) {
		m_ButtonB_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_C(t_param _value) {
		m_C_7 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_D(t_param _value) {
		m_D_8 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_B(t_param _value) {
		m_B_9 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_A(t_param _value) {
		m_A_10 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline t_sample trapezoid_d_d_d_d_d(t_sample x, t_sample a, t_sample b, t_sample c, t_sample d) {
		t_sample _trapezoid_ret_439 = ((int)0);
		if ((x < a)) {
			_trapezoid_ret_439 = ((int)0);
			
		} else {
			if ((x < b)) {
				_trapezoid_ret_439 = safediv((x - a), (b - a));
				
			} else {
				if ((x < c)) {
					_trapezoid_ret_439 = ((int)1);
					
				} else {
					if ((x < d)) {
						_trapezoid_ret_439 = safediv((d - x), (d - c));
						
					} else {
						_trapezoid_ret_439 = ((int)0);
						
					};
					
				};
				
			};
			
		};
		return _trapezoid_ret_439;
		
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 6;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 6; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3", "out4", "out5", "out6" };

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
		case 2: self->set_ButtonA(value); break;
		case 3: self->set_ButtonB(value); break;
		case 4: self->set_C(value); break;
		case 5: self->set_D(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_A_10; break;
		case 1: *value = self->m_B_9; break;
		case 2: *value = self->m_ButtonA_5; break;
		case 3: *value = self->m_ButtonB_6; break;
		case 4: *value = self->m_C_7; break;
		case 5: *value = self->m_D_8; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(6 * sizeof(ParamInfo));
	self->__commonstate.numparams = 6;
	// initialize parameter 0 ("m_A_10")
	pi = self->__commonstate.params + 0;
	pi->name = "A";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_A_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_B_9")
	pi = self->__commonstate.params + 1;
	pi->name = "B";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_B_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ButtonA_5")
	pi = self->__commonstate.params + 2;
	pi->name = "ButtonA";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ButtonA_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_ButtonB_6")
	pi = self->__commonstate.params + 3;
	pi->name = "ButtonB";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ButtonB_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_C_7")
	pi = self->__commonstate.params + 4;
	pi->name = "C";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_C_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_D_8")
	pi = self->__commonstate.params + 5;
	pi->name = "D";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_D_8;
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


} // dl_fdbck::
