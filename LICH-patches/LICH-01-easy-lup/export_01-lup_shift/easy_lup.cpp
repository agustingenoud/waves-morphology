#include "easy_lup.h"

namespace easy_lup {

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
	Data m_nobufB_15;
	Data m_nobufC_12;
	Data m_nobufA_10;
	Delay m_delay_5;
	Delay m_delay_4;
	Delay m_delay_3;
	Delay m_delay_6;
	Delta __m_delta_78;
	Delta __m_delta_24;
	Delta __m_delta_90;
	Delta __m_delta_58;
	Delta __m_delta_54;
	Delta __m_delta_52;
	Delta __m_delta_56;
	Delta __m_delta_62;
	Delta __m_delta_16;
	Delta __m_delta_74;
	Phasor __m_phasor_41;
	Phasor __m_phasor_60;
	Phasor __m_phasor_73;
	Phasor __m_phasor_61;
	Phasor __m_phasor_77;
	Phasor __m_phasor_89;
	Phasor __m_phasor_51;
	PlusEquals __m_pluseq_27;
	PlusEquals __m_pluseq_17;
	PlusEquals __m_pluseq_32;
	PlusEquals __m_pluseq_25;
	Sah __m_sah_57;
	Sah __m_sah_53;
	Sah __m_sah_59;
	Sah __m_sah_55;
	int __exception;
	int vectorsize;
	t_sample __m_carry_35;
	t_sample __m_latch_75;
	t_sample m_C_7;
	t_sample __m_latch_76;
	t_sample m_D_8;
	t_sample m_history_2;
	t_sample __m_latch_79;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample samples_to_seconds;
	t_sample __m_latch_63;
	t_sample m_A_11;
	t_sample __m_carry_30;
	t_sample __m_latch_91;
	t_sample __m_count_33;
	t_sample m_ButtonA_9;
	t_sample __m_count_28;
	t_sample __m_count_18;
	t_sample __m_carry_20;
	t_sample m_ButtonB_13;
	t_sample m_B_14;
	t_sample __m_latch_92;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_delay_3.reset("m_delay_3", ((int)88200));
		m_delay_4.reset("m_delay_4", samplerate);
		m_delay_5.reset("m_delay_5", samplerate);
		m_delay_6.reset("m_delay_6", samplerate);
		m_C_7 = ((int)0);
		m_D_8 = ((int)0);
		m_ButtonA_9 = ((int)0);
		m_nobufA_10.reset("nobufA", ((int)38400), ((int)1));
		m_A_11 = ((int)0);
		m_nobufC_12.reset("nobufC", ((int)48000), ((int)1));
		m_ButtonB_13 = ((int)0);
		m_B_14 = ((int)0);
		m_nobufB_15.reset("nobufB", ((int)33600), ((int)1));
		__m_delta_16.reset(0);
		__m_pluseq_17.reset(0);
		__m_count_18 = 0;
		__m_carry_20 = 0;
		__m_delta_24.reset(0);
		__m_pluseq_25.reset(0);
		__m_pluseq_27.reset(0);
		__m_count_28 = 0;
		__m_carry_30 = 0;
		__m_pluseq_32.reset(0);
		__m_count_33 = 0;
		__m_carry_35 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_41.reset(0);
		__m_phasor_51.reset(0);
		__m_delta_52.reset(0);
		__m_sah_53.reset(0);
		__m_delta_54.reset(0);
		__m_sah_55.reset(0);
		__m_delta_56.reset(0);
		__m_sah_57.reset(0);
		__m_delta_58.reset(0);
		__m_sah_59.reset(0);
		__m_phasor_60.reset(0);
		__m_phasor_61.reset(0);
		__m_delta_62.reset(0);
		__m_latch_63 = 0;
		__m_phasor_73.reset(0);
		__m_delta_74.reset(0);
		__m_latch_75 = 0;
		__m_latch_76 = 0;
		__m_phasor_77.reset(0);
		__m_delta_78.reset(0);
		__m_latch_79 = 0;
		__m_phasor_89.reset(0);
		__m_delta_90.reset(0);
		__m_latch_91 = 0;
		__m_latch_92 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample expr_486 = ((m_C_7 * ((int)2)) - ((int)1));
		int nobufC_dim = m_nobufC_12.dim;
		int nobufC_channels = m_nobufC_12.channels;
		int dim_466 = nobufC_dim;
		int nobufA_dim = m_nobufA_10.dim;
		int nobufA_channels = m_nobufA_10.channels;
		int dim_120 = nobufA_dim;
		int nobufB_dim = m_nobufB_15.dim;
		int nobufB_channels = m_nobufB_15.channels;
		int dim_113 = nobufB_dim;
		t_sample paramA_157 = m_A_11;
		t_sample paramA_179 = paramA_157;
		samples_to_seconds = (1 / samplerate);
		t_sample sub_587 = (m_A_11 - ((int)0));
		t_sample scale_584 = ((safepow((sub_587 * ((t_sample)20)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample clamp_8 = ((scale_584 <= ((int)0)) ? ((int)0) : ((scale_584 >= ((int)1)) ? ((int)1) : scale_584));
		t_sample sub_591 = (m_B_14 - ((int)0));
		t_sample scale_588 = ((safepow((sub_591 * ((t_sample)1)), ((int)1)) * ((int)2)) + ((int)0));
		t_sample mstosamps_87 = (((int)256) * (samplerate * 0.001));
		t_sample mul_23 = (mstosamps_87 * ((t_sample)0.2));
		t_sample rsub_73 = (((int)1) - scale_588);
		t_sample mul_72 = (rsub_73 * ((int)1000));
		t_sample div_71 = (mul_72 * ((t_sample)0.00390625));
		t_sample sub_595 = (scale_588 - ((int)0));
		t_sample scale_592 = ((safepow((sub_595 * ((t_sample)10)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample clamp_13 = ((scale_592 <= ((int)0)) ? ((int)0) : ((scale_592 >= ((int)1)) ? ((int)1) : scale_592));
		t_sample sub_599 = (m_A_11 - ((t_sample)0.0001));
		t_sample scale_596 = ((safepow((sub_599 * ((t_sample)1.000200040008)), ((int)1)) * ((int)8)) + ((int)1));
		int int_218 = int(scale_596);
		int dim_131 = nobufA_dim;
		t_sample div_132 = safediv(samplerate, dim_131);
		t_sample sub_603 = (paramA_179 - ((int)0));
		t_sample scale_600 = ((safepow((sub_603 * ((t_sample)1)), ((int)1)) * ((t_sample)5.8)) + ((t_sample)0.2));
		t_sample scale_171 = scale_600;
		int dim_130 = nobufB_dim;
		t_sample div_137 = safediv(samplerate, dim_130);
		t_sample sub_608 = (paramA_157 - ((int)0));
		t_sample scale_605 = ((safepow((sub_608 * ((t_sample)1)), ((int)1)) * ((t_sample)5.8)) + ((t_sample)0.2));
		t_sample scale_149 = scale_605;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample tap_465 = m_delay_6.read_step(dim_466);
			t_sample delta_471 = __m_delta_16(m_ButtonB_13);
			t_sample gtp_470 = ((delta_471 > ((int)0)) ? delta_471 : 0);
			t_sample plusequals_463 = __m_pluseq_17.post(gtp_470, tap_465, 0);
			__m_count_18 = (gtp_470 ? 0 : (fixdenorm(__m_count_18 + plusequals_463)));
			int carry_19 = 0;
			if ((gtp_470 != 0)) {
				__m_count_18 = 0;
				__m_carry_20 = 0;
				
			} else if (((dim_466 > 0) && (__m_count_18 >= dim_466))) {
				int wraps_21 = (__m_count_18 / dim_466);
				__m_carry_20 = (__m_carry_20 + wraps_21);
				__m_count_18 = (__m_count_18 - (wraps_21 * dim_466));
				carry_19 = 1;
				
			};
			t_sample counter_467 = __m_count_18;
			int counter_468 = carry_19;
			int counter_469 = __m_carry_20;
			int index_trunc_22 = fixnan(floor(counter_467));
			int index_wrap_23 = ((index_trunc_22 < 0) ? ((nobufC_dim - 1) + ((index_trunc_22 + 1) % nobufC_dim)) : (index_trunc_22 % nobufC_dim));
			m_nobufC_12.write(in1, index_wrap_23, 0);
			t_sample tap_119 = m_delay_5.read_step(dim_120);
			t_sample tap_112 = m_delay_4.read_step(dim_113);
			t_sample delta_109 = __m_delta_24(m_ButtonA_9);
			t_sample gtp_108 = ((delta_109 > ((int)0)) ? delta_109 : 0);
			t_sample plusequals_107 = __m_pluseq_25.post(gtp_108, ((int)0), 0);
			t_sample mod_106 = safemod(plusequals_107, ((int)2));
			t_sample add_103 = (mod_106 + ((int)1));
			t_sample choice_26 = int(add_103);
			t_sample gate_104 = (((choice_26 >= 1) && (choice_26 < 2)) ? gtp_108 : 0);
			t_sample gate_105 = ((choice_26 >= 2) ? gtp_108 : 0);
			t_sample plusequals_117 = __m_pluseq_27.post(gate_104, tap_119, 0);
			__m_count_28 = (gate_104 ? 0 : (fixdenorm(__m_count_28 + plusequals_117)));
			int carry_29 = 0;
			if ((gate_104 != 0)) {
				__m_count_28 = 0;
				__m_carry_30 = 0;
				
			} else if (((dim_120 > 0) && (__m_count_28 >= dim_120))) {
				int wraps_31 = (__m_count_28 / dim_120);
				__m_carry_30 = (__m_carry_30 + wraps_31);
				__m_count_28 = (__m_count_28 - (wraps_31 * dim_120));
				carry_29 = 1;
				
			};
			t_sample counter_121 = __m_count_28;
			int counter_122 = carry_29;
			int counter_123 = __m_carry_30;
			t_sample plusequals_110 = __m_pluseq_32.post(gate_105, tap_112, 0);
			__m_count_33 = (gate_105 ? 0 : (fixdenorm(__m_count_33 + plusequals_110)));
			int carry_34 = 0;
			if ((gate_105 != 0)) {
				__m_count_33 = 0;
				__m_carry_35 = 0;
				
			} else if (((dim_113 > 0) && (__m_count_33 >= dim_113))) {
				int wraps_36 = (__m_count_33 / dim_113);
				__m_carry_35 = (__m_carry_35 + wraps_36);
				__m_count_33 = (__m_count_33 - (wraps_36 * dim_113));
				carry_34 = 1;
				
			};
			t_sample counter_114 = __m_count_33;
			int counter_115 = carry_34;
			int counter_116 = __m_carry_35;
			int index_trunc_37 = fixnan(floor(counter_121));
			int index_wrap_38 = ((index_trunc_37 < 0) ? ((nobufA_dim - 1) + ((index_trunc_37 + 1) % nobufA_dim)) : (index_trunc_37 % nobufA_dim));
			m_nobufA_10.write(in1, index_wrap_38, 0);
			int index_trunc_39 = fixnan(floor(counter_114));
			int index_wrap_40 = ((index_trunc_39 < 0) ? ((nobufB_dim - 1) + ((index_trunc_39 + 1) % nobufB_dim)) : (index_trunc_39 % nobufB_dim));
			m_nobufB_15.write(in1, index_wrap_40, 0);
			t_sample mul_1 = (in2 * m_D_8);
			t_sample noise_206 = noise();
			t_sample noise_187 = noise();
			t_sample phasor_480 = __m_phasor_41(expr_486, samples_to_seconds);
			t_sample wrap_479 = wrap(phasor_480, ((int)0), ((int)1));
			double sample_index_42 = (wrap_479 * (nobufC_dim - 1));
			int index_trunc_43 = fixnan(floor(sample_index_42));
			double index_fract_44 = (sample_index_42 - index_trunc_43);
			int index_trunc_45 = (index_trunc_43 + 1);
			bool index_ignore_46 = ((index_trunc_43 >= nobufC_dim) || (index_trunc_43 < 0));
			bool index_ignore_47 = ((index_trunc_45 >= nobufC_dim) || (index_trunc_45 < 0));
			// phase nobufC channel 1;
			double read_nobufC_48 = (index_ignore_46 ? 0 : m_nobufC_12.read(index_trunc_43, 0));
			double read_nobufC_49 = (index_ignore_47 ? 0 : m_nobufC_12.read(index_trunc_45, 0));
			double readinterp_50 = linear_interp(index_fract_44, read_nobufC_48, read_nobufC_49);
			t_sample sample_nobufC_477 = readinterp_50;
			t_sample index_nobufC_478 = sample_index_42;
			t_sample noise_35 = noise();
			t_sample abs_50 = fabs(noise_35);
			t_sample mul_49 = (abs_50 * ((t_sample)0.25));
			t_sample add_27 = (mul_49 + ((int)1));
			t_sample mul_89 = (add_27 * mstosamps_87);
			t_sample noise_34 = noise();
			t_sample abs_46 = fabs(noise_34);
			t_sample mul_45 = (abs_46 * ((t_sample)0.25));
			t_sample add_26 = (mul_45 + ((int)3));
			t_sample mul_81 = (add_26 * mul_23);
			t_sample noise_33 = noise();
			t_sample abs_42 = fabs(noise_33);
			t_sample mul_41 = (abs_42 * ((t_sample)0.25));
			t_sample add_25 = (mul_41 + ((t_sample)1.7));
			t_sample mul_65 = (add_25 * mstosamps_87);
			t_sample noise_32 = noise();
			t_sample abs_38 = fabs(noise_32);
			t_sample mul_37 = (abs_38 * ((t_sample)0.25));
			t_sample add_24 = (mul_37 + ((t_sample)2.37));
			t_sample mul_58 = (add_24 * mstosamps_87);
			t_sample phasor_95 = __m_phasor_51(div_71, samples_to_seconds);
			t_sample add_94 = (phasor_95 + ((int)0));
			t_sample mod_93 = safemod(add_94, ((int)1));
			t_sample delta_52 = __m_delta_52(mod_93);
			t_sample sah_51 = __m_sah_53(mul_89, delta_52, ((int)0));
			t_sample mul_31 = (sah_51 * mod_93);
			t_sample sub_92 = (mod_93 - ((t_sample)0.5));
			t_sample mul_91 = (sub_92 * ((t_sample)3.1415926535898));
			t_sample cos_90 = cos(mul_91);
			t_sample mul_56 = (cos_90 * cos_90);
			t_sample add_86 = (phasor_95 + ((t_sample)0.25));
			t_sample mod_85 = safemod(add_86, ((int)1));
			t_sample delta_48 = __m_delta_54(mod_85);
			t_sample sah_47 = __m_sah_55(mul_81, delta_48, ((int)0));
			t_sample mul_30 = (sah_47 * mod_85);
			t_sample sub_84 = (mod_85 - ((t_sample)0.5));
			t_sample mul_83 = (sub_84 * ((t_sample)3.1415926535898));
			t_sample cos_82 = cos(mul_83);
			t_sample mul_55 = (cos_82 * cos_82);
			t_sample add_70 = (phasor_95 + ((t_sample)0.5));
			t_sample mod_69 = safemod(add_70, ((int)1));
			t_sample delta_44 = __m_delta_56(mod_69);
			t_sample sah_43 = __m_sah_57(mul_65, delta_44, ((int)0));
			t_sample mul_29 = (sah_43 * mod_69);
			t_sample sub_68 = (mod_69 - ((t_sample)0.5));
			t_sample mul_67 = (sub_68 * ((t_sample)3.1415926535898));
			t_sample cos_66 = cos(mul_67);
			t_sample mul_54 = (cos_66 * cos_66);
			t_sample add_63 = (phasor_95 + ((t_sample)0.75));
			t_sample mod_62 = safemod(add_63, ((int)1));
			t_sample delta_40 = __m_delta_58(mod_62);
			t_sample sah_39 = __m_sah_59(mul_58, delta_40, ((int)0));
			t_sample mul_28 = (sah_39 * mod_62);
			t_sample tap_77 = m_delay_3.read_linear(mul_31);
			t_sample tap_78 = m_delay_3.read_linear(mul_30);
			t_sample tap_79 = m_delay_3.read_linear(mul_29);
			t_sample tap_80 = m_delay_3.read_linear(mul_28);
			t_sample mul_75 = (tap_77 * mul_56);
			t_sample mul_64 = (tap_79 * mul_54);
			t_sample gen_99 = (mul_64 + mul_75);
			t_sample mul_74 = (tap_78 * mul_55);
			t_sample sub_61 = (mod_62 - ((t_sample)0.5));
			t_sample mul_60 = (sub_61 * ((t_sample)3.1415926535898));
			t_sample cos_59 = cos(mul_60);
			t_sample mul_53 = (cos_59 * cos_59);
			t_sample mul_57 = (tap_80 * mul_53);
			t_sample gen_100 = (mul_57 + mul_74);
			t_sample mul_21 = (gen_99 * ((t_sample)0.666));
			t_sample mul_20 = (gen_100 * ((t_sample)0.666));
			t_sample phasor_19 = __m_phasor_60(((int)22), samples_to_seconds);
			t_sample triangle_17 = triangle(phasor_19, ((t_sample)0.5));
			t_sample mul_16 = (mul_21 * triangle_17);
			t_sample mul_12 = (mul_16 * clamp_13);
			t_sample mul_15 = (mul_20 * triangle_17);
			t_sample mul_11 = (mul_15 * clamp_13);
			t_sample mul_203 = (noise_206 * m_A_11);
			t_sample mul_184 = (noise_187 * m_A_11);
			t_sample phasor_217 = __m_phasor_61(div_132, samples_to_seconds);
			t_sample wrap_216 = wrap(phasor_217, ((int)0), ((int)1));
			t_sample mul_213 = (wrap_216 * int_218);
			t_sample wrap_211 = wrap(mul_213, ((int)0), ((int)1));
			t_sample delta_209 = __m_delta_62(wrap_211);
			t_sample abs_208 = fabs(delta_209);
			int gt_207 = (abs_208 > ((t_sample)0.9));
			t_sample mul_204 = (mul_213 * ((t_sample)3.767));
			t_sample floor_202 = floor((mul_203 + mul_204));
			__m_latch_63 = ((gt_207 != 0) ? floor_202 : __m_latch_63);
			t_sample latch_205 = __m_latch_63;
			t_sample add_210 = (wrap_211 + latch_205);
			t_sample div_200 = safediv(add_210, int_218);
			t_sample wrap_199 = wrap(div_200, ((int)0), ((int)1));
			double sample_index_64 = (wrap_199 * (nobufA_dim - 1));
			int index_trunc_65 = fixnan(floor(sample_index_64));
			double index_fract_66 = (sample_index_64 - index_trunc_65);
			int index_trunc_67 = (index_trunc_65 + 1);
			bool index_ignore_68 = ((index_trunc_65 >= nobufA_dim) || (index_trunc_65 < 0));
			bool index_ignore_69 = ((index_trunc_67 >= nobufA_dim) || (index_trunc_67 < 0));
			// phase nobufA channel 1;
			double read_nobufA_70 = (index_ignore_68 ? 0 : m_nobufA_10.read(index_trunc_65, 0));
			double read_nobufA_71 = (index_ignore_69 ? 0 : m_nobufA_10.read(index_trunc_67, 0));
			double readinterp_72 = linear_interp(index_fract_66, read_nobufA_70, read_nobufA_71);
			t_sample sample_nobufA_214 = readinterp_72;
			t_sample index_nobufA_215 = sample_index_64;
			t_sample abs_165 = fabs(noise_206);
			t_sample phasor_172 = __m_phasor_73(scale_171, samples_to_seconds);
			t_sample delta_168 = __m_delta_74(phasor_172);
			t_sample abs_167 = fabs(delta_168);
			int gt_166 = (abs_167 > ((t_sample)0.9));
			__m_latch_75 = ((gt_166 != 0) ? m_history_2 : __m_latch_75);
			t_sample latch_160 = __m_latch_75;
			__m_latch_76 = ((gt_166 != 0) ? abs_165 : __m_latch_76);
			t_sample latch_169 = __m_latch_76;
			t_sample mix_604 = (latch_160 + (phasor_172 * (latch_169 - latch_160)));
			t_sample mix_162 = mix_604;
			t_sample mul_164 = (sample_nobufA_214 * mix_162);
			t_sample rsub_170 = (((int)1) - mix_162);
			t_sample mul_163 = (sample_nobufA_214 * rsub_170);
			t_sample history_161_next_176 = fixdenorm(mix_162);
			t_sample mul_5 = (mul_164 * clamp_8);
			t_sample mul_6 = (mul_163 * clamp_8);
			t_sample phasor_198 = __m_phasor_77(div_137, samples_to_seconds);
			t_sample wrap_197 = wrap(phasor_198, ((int)0), ((int)1));
			t_sample mul_194 = (wrap_197 * int_218);
			t_sample wrap_192 = wrap(mul_194, ((int)0), ((int)1));
			t_sample delta_190 = __m_delta_78(wrap_192);
			t_sample abs_189 = fabs(delta_190);
			int gt_188 = (abs_189 > ((t_sample)0.9));
			t_sample mul_185 = (mul_194 * ((t_sample)3.767));
			t_sample floor_183 = floor((mul_185 + mul_184));
			__m_latch_79 = ((gt_188 != 0) ? floor_183 : __m_latch_79);
			t_sample latch_186 = __m_latch_79;
			t_sample add_191 = (wrap_192 + latch_186);
			t_sample div_181 = safediv(add_191, int_218);
			t_sample wrap_180 = wrap(div_181, ((int)0), ((int)1));
			double sample_index_80 = (wrap_180 * (nobufB_dim - 1));
			int index_trunc_81 = fixnan(floor(sample_index_80));
			double index_fract_82 = (sample_index_80 - index_trunc_81);
			int index_trunc_83 = (index_trunc_81 + 1);
			bool index_ignore_84 = ((index_trunc_81 >= nobufB_dim) || (index_trunc_81 < 0));
			bool index_ignore_85 = ((index_trunc_83 >= nobufB_dim) || (index_trunc_83 < 0));
			// phase nobufB channel 1;
			double read_nobufB_86 = (index_ignore_84 ? 0 : m_nobufB_15.read(index_trunc_81, 0));
			double read_nobufB_87 = (index_ignore_85 ? 0 : m_nobufB_15.read(index_trunc_83, 0));
			double readinterp_88 = linear_interp(index_fract_82, read_nobufB_86, read_nobufB_87);
			t_sample sample_nobufB_195 = readinterp_88;
			t_sample index_nobufB_196 = sample_index_80;
			t_sample abs_143 = fabs(noise_187);
			t_sample phasor_150 = __m_phasor_89(scale_149, samples_to_seconds);
			t_sample delta_146 = __m_delta_90(phasor_150);
			t_sample abs_145 = fabs(delta_146);
			int gt_144 = (abs_145 > ((t_sample)0.9));
			__m_latch_91 = ((gt_144 != 0) ? m_history_1 : __m_latch_91);
			t_sample latch_138 = __m_latch_91;
			__m_latch_92 = ((gt_144 != 0) ? abs_143 : __m_latch_92);
			t_sample latch_147 = __m_latch_92;
			t_sample mix_609 = (latch_138 + (phasor_150 * (latch_147 - latch_138)));
			t_sample mix_140 = mix_609;
			t_sample mul_142 = (sample_nobufB_195 * mix_140);
			t_sample rsub_148 = (((int)1) - mix_140);
			t_sample mul_141 = (sample_nobufB_195 * rsub_148);
			t_sample history_139_next_154 = fixdenorm(mix_140);
			t_sample mul_2 = (mul_142 * clamp_8);
			t_sample OutLeft_159 = ((((sample_nobufC_477 + mul_2) + mul_5) + mul_12) + mul_1);
			t_sample out1 = OutLeft_159;
			t_sample mul_3 = (mul_141 * clamp_8);
			t_sample OutRight_158 = ((((sample_nobufC_477 + mul_6) + mul_11) + mul_1) + mul_3);
			t_sample out2 = OutRight_158;
			m_delay_6.write(plusequals_463);
			m_delay_5.write(plusequals_117);
			m_delay_4.write(plusequals_110);
			m_delay_3.write(in1);
			m_history_2 = history_161_next_176;
			m_history_1 = history_139_next_154;
			m_delay_3.step();
			m_delay_4.step();
			m_delay_5.step();
			m_delay_6.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_C(t_param _value) {
		m_C_7 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_D(t_param _value) {
		m_D_8 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_ButtonA(t_param _value) {
		m_ButtonA_9 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_nobufA(void * _value) {
		m_nobufA_10.setbuffer(_value);
	};
	inline void set_A(t_param _value) {
		m_A_11 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_nobufC(void * _value) {
		m_nobufC_12.setbuffer(_value);
	};
	inline void set_ButtonB(t_param _value) {
		m_ButtonB_13 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_B(t_param _value) {
		m_B_14 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_nobufB(void * _value) {
		m_nobufB_15.setbuffer(_value);
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 9; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
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
		case 2: self->set_ButtonA(value); break;
		case 3: self->set_ButtonB(value); break;
		case 4: self->set_C(value); break;
		case 5: self->set_D(value); break;
		case 6: self->set_nobufA(ref); break;
		case 7: self->set_nobufB(ref); break;
		case 8: self->set_nobufC(ref); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_A_11; break;
		case 1: *value = self->m_B_14; break;
		case 2: *value = self->m_ButtonA_9; break;
		case 3: *value = self->m_ButtonB_13; break;
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(9 * sizeof(ParamInfo));
	self->__commonstate.numparams = 9;
	// initialize parameter 0 ("m_A_11")
	pi = self->__commonstate.params + 0;
	pi->name = "A";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_A_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_B_14")
	pi = self->__commonstate.params + 1;
	pi->name = "B";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_B_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ButtonA_9")
	pi = self->__commonstate.params + 2;
	pi->name = "ButtonA";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ButtonA_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_ButtonB_13")
	pi = self->__commonstate.params + 3;
	pi->name = "ButtonB";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ButtonB_13;
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
	// initialize parameter 6 ("m_nobufA_10")
	pi = self->__commonstate.params + 6;
	pi->name = "nobufA";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_nobufB_15")
	pi = self->__commonstate.params + 7;
	pi->name = "nobufB";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_nobufC_12")
	pi = self->__commonstate.params + 8;
	pi->name = "nobufC";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
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


} // easy_lup::
