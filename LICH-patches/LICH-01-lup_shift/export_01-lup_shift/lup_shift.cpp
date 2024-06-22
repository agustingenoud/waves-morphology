#include "lup_shift.h"

namespace lup_shift {

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
	Data m_nobufB_13;
	Data m_nobufA_15;
	Data m_nobufC_14;
	Delay m_delay_6;
	Delay m_delay_5;
	Delay m_delay_3;
	Delay m_delay_4;
	Delta __m_delta_16;
	Delta __m_delta_56;
	Delta __m_delta_58;
	Delta __m_delta_62;
	Delta __m_delta_74;
	Delta __m_delta_52;
	Delta __m_delta_33;
	Delta __m_delta_54;
	Delta __m_delta_90;
	Delta __m_delta_78;
	Phasor __m_phasor_41;
	Phasor __m_phasor_61;
	Phasor __m_phasor_60;
	Phasor __m_phasor_73;
	Phasor __m_phasor_77;
	Phasor __m_phasor_89;
	Phasor __m_phasor_51;
	PlusEquals __m_pluseq_34;
	PlusEquals __m_pluseq_24;
	PlusEquals __m_pluseq_19;
	PlusEquals __m_pluseq_17;
	Sah __m_sah_55;
	Sah __m_sah_53;
	Sah __m_sah_57;
	Sah __m_sah_59;
	int __exception;
	int vectorsize;
	t_sample __m_carry_37;
	t_sample __m_latch_75;
	t_sample m_B_7;
	t_sample __m_latch_76;
	t_sample m_A_8;
	t_sample m_history_2;
	t_sample __m_latch_79;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample samples_to_seconds;
	t_sample __m_latch_63;
	t_sample m_ButtonB_10;
	t_sample __m_carry_27;
	t_sample __m_latch_91;
	t_sample __m_count_35;
	t_sample m_C_9;
	t_sample __m_count_25;
	t_sample __m_count_20;
	t_sample __m_carry_22;
	t_sample m_D_11;
	t_sample m_ButtonA_12;
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
		m_B_7 = ((int)0);
		m_A_8 = ((int)0);
		m_C_9 = ((int)0);
		m_ButtonB_10 = ((int)0);
		m_D_11 = ((int)0);
		m_ButtonA_12 = ((int)0);
		m_nobufB_13.reset("nobufB", ((int)24000), ((int)1));
		m_nobufC_14.reset("nobufC", ((int)24000), ((int)1));
		m_nobufA_15.reset("nobufA", ((int)24000), ((int)1));
		__m_delta_16.reset(0);
		__m_pluseq_17.reset(0);
		__m_pluseq_19.reset(0);
		__m_count_20 = 0;
		__m_carry_22 = 0;
		__m_pluseq_24.reset(0);
		__m_count_25 = 0;
		__m_carry_27 = 0;
		__m_delta_33.reset(0);
		__m_pluseq_34.reset(0);
		__m_count_35 = 0;
		__m_carry_37 = 0;
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
		t_sample expr_263 = ((m_C_9 * ((int)2)) - ((int)1));
		int nobufB_dim = m_nobufB_13.dim;
		int nobufB_channels = m_nobufB_13.channels;
		int dim_146 = nobufB_dim;
		int nobufA_dim = m_nobufA_15.dim;
		int nobufA_channels = m_nobufA_15.channels;
		int dim_153 = nobufA_dim;
		int nobufC_dim = m_nobufC_14.dim;
		int nobufC_channels = m_nobufC_14.channels;
		int dim_9 = nobufC_dim;
		t_sample sub_303 = (m_D_11 - ((int)0));
		t_sample scale_300 = ((safepow((sub_303 * ((t_sample)1)), ((int)1)) * ((t_sample)1.25)) + ((int)0));
		t_sample sub_22 = (scale_300 - ((t_sample)0.25));
		samples_to_seconds = (1 / samplerate);
		t_sample paramA_190 = m_A_8;
		t_sample paramA_212 = paramA_190;
		t_sample sub_307 = (m_A_8 - ((int)0));
		t_sample scale_304 = ((safepow((sub_307 * ((t_sample)20)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample clamp_41 = ((scale_304 <= ((int)0)) ? ((int)0) : ((scale_304 >= ((int)1)) ? ((int)1) : scale_304));
		t_sample sub_311 = (m_B_7 - ((int)0));
		t_sample scale_308 = ((safepow((sub_311 * ((t_sample)1)), ((int)1)) * ((int)2)) + ((int)0));
		t_sample mstosamps_120 = (((int)256) * (samplerate * 0.001));
		t_sample mul_56 = (mstosamps_120 * ((t_sample)0.2));
		t_sample rsub_106 = (((int)1) - scale_308);
		t_sample mul_105 = (rsub_106 * ((int)1000));
		t_sample div_104 = (mul_105 * ((t_sample)0.00390625));
		t_sample sub_315 = (scale_308 - ((int)0));
		t_sample scale_312 = ((safepow((sub_315 * ((t_sample)10)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample clamp_46 = ((scale_312 <= ((int)0)) ? ((int)0) : ((scale_312 >= ((int)1)) ? ((int)1) : scale_312));
		t_sample sub_319 = (m_A_8 - ((t_sample)0.0001));
		t_sample scale_316 = ((safepow((sub_319 * ((t_sample)1.000200040008)), ((int)1)) * ((int)8)) + ((int)1));
		int int_251 = int(scale_316);
		int dim_164 = nobufA_dim;
		t_sample div_165 = safediv(samplerate, dim_164);
		t_sample sub_323 = (paramA_212 - ((int)0));
		t_sample scale_320 = ((safepow((sub_323 * ((t_sample)1)), ((int)1)) * ((t_sample)5.8)) + ((t_sample)0.2));
		t_sample scale_204 = scale_320;
		int dim_163 = nobufB_dim;
		t_sample div_170 = safediv(samplerate, dim_163);
		t_sample sub_328 = (paramA_190 - ((int)0));
		t_sample scale_325 = ((safepow((sub_328 * ((t_sample)1)), ((int)1)) * ((t_sample)5.8)) + ((t_sample)0.2));
		t_sample scale_182 = scale_325;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample tap_145 = m_delay_6.read_step(dim_146);
			t_sample tap_152 = m_delay_5.read_step(dim_153);
			t_sample delta_142 = __m_delta_16(m_ButtonA_12);
			t_sample gtp_141 = ((delta_142 > ((int)0)) ? delta_142 : 0);
			t_sample plusequals_140 = __m_pluseq_17.post(gtp_141, ((int)0), 0);
			t_sample mod_139 = safemod(plusequals_140, ((int)2));
			t_sample add_136 = (mod_139 + ((int)1));
			t_sample choice_18 = int(add_136);
			t_sample gate_137 = (((choice_18 >= 1) && (choice_18 < 2)) ? gtp_141 : 0);
			t_sample gate_138 = ((choice_18 >= 2) ? gtp_141 : 0);
			t_sample plusequals_143 = __m_pluseq_19.post(gate_138, tap_145, 0);
			__m_count_20 = (gate_138 ? 0 : (fixdenorm(__m_count_20 + plusequals_143)));
			int carry_21 = 0;
			if ((gate_138 != 0)) {
				__m_count_20 = 0;
				__m_carry_22 = 0;
				
			} else if (((dim_146 > 0) && (__m_count_20 >= dim_146))) {
				int wraps_23 = (__m_count_20 / dim_146);
				__m_carry_22 = (__m_carry_22 + wraps_23);
				__m_count_20 = (__m_count_20 - (wraps_23 * dim_146));
				carry_21 = 1;
				
			};
			t_sample counter_147 = __m_count_20;
			int counter_148 = carry_21;
			int counter_149 = __m_carry_22;
			t_sample plusequals_150 = __m_pluseq_24.post(gate_137, tap_152, 0);
			__m_count_25 = (gate_137 ? 0 : (fixdenorm(__m_count_25 + plusequals_150)));
			int carry_26 = 0;
			if ((gate_137 != 0)) {
				__m_count_25 = 0;
				__m_carry_27 = 0;
				
			} else if (((dim_153 > 0) && (__m_count_25 >= dim_153))) {
				int wraps_28 = (__m_count_25 / dim_153);
				__m_carry_27 = (__m_carry_27 + wraps_28);
				__m_count_25 = (__m_count_25 - (wraps_28 * dim_153));
				carry_26 = 1;
				
			};
			t_sample counter_154 = __m_count_25;
			int counter_155 = carry_26;
			int counter_156 = __m_carry_27;
			int index_trunc_29 = fixnan(floor(counter_154));
			int index_wrap_30 = ((index_trunc_29 < 0) ? ((nobufA_dim - 1) + ((index_trunc_29 + 1) % nobufA_dim)) : (index_trunc_29 % nobufA_dim));
			m_nobufA_15.write(in1, index_wrap_30, 0);
			int index_trunc_31 = fixnan(floor(counter_147));
			int index_wrap_32 = ((index_trunc_31 < 0) ? ((nobufB_dim - 1) + ((index_trunc_31 + 1) % nobufB_dim)) : (index_trunc_31 % nobufB_dim));
			m_nobufB_13.write(in1, index_wrap_32, 0);
			t_sample tap_8 = m_delay_4.read_step(dim_9);
			t_sample delta_14 = __m_delta_33(m_ButtonB_10);
			t_sample gtp_13 = ((delta_14 > ((int)0)) ? delta_14 : 0);
			t_sample plusequals_6 = __m_pluseq_34.post(gtp_13, tap_8, 0);
			__m_count_35 = (gtp_13 ? 0 : (fixdenorm(__m_count_35 + plusequals_6)));
			int carry_36 = 0;
			if ((gtp_13 != 0)) {
				__m_count_35 = 0;
				__m_carry_37 = 0;
				
			} else if (((dim_9 > 0) && (__m_count_35 >= dim_9))) {
				int wraps_38 = (__m_count_35 / dim_9);
				__m_carry_37 = (__m_carry_37 + wraps_38);
				__m_count_35 = (__m_count_35 - (wraps_38 * dim_9));
				carry_36 = 1;
				
			};
			t_sample counter_10 = __m_count_35;
			int counter_11 = carry_36;
			int counter_12 = __m_carry_37;
			int index_trunc_39 = fixnan(floor(counter_10));
			int index_wrap_40 = ((index_trunc_39 < 0) ? ((nobufC_dim - 1) + ((index_trunc_39 + 1) % nobufC_dim)) : (index_trunc_39 % nobufC_dim));
			m_nobufC_14.write(in1, index_wrap_40, 0);
			t_sample expr_32 = trapezoid_d_d_d_d_d(scale_300, ((t_sample)0.3), ((t_sample)0.4), ((t_sample)0.7), ((t_sample)0.8));
			t_sample expr_33 = trapezoid_d_d_d_d_d(sub_22, ((t_sample)0.3), ((t_sample)0.4), ((t_sample)0.7), ((t_sample)0.8));
			t_sample mul_26 = (in1 * expr_32);
			t_sample mul_20 = (in2 * expr_33);
			t_sample gen_34 = (mul_20 + mul_26);
			t_sample phasor_5 = __m_phasor_41(expr_263, samples_to_seconds);
			t_sample wrap_4 = wrap(phasor_5, ((int)0), ((int)1));
			double sample_index_42 = (wrap_4 * (nobufC_dim - 1));
			int index_trunc_43 = fixnan(floor(sample_index_42));
			double index_fract_44 = (sample_index_42 - index_trunc_43);
			int index_trunc_45 = (index_trunc_43 + 1);
			bool index_ignore_46 = ((index_trunc_43 >= nobufC_dim) || (index_trunc_43 < 0));
			bool index_ignore_47 = ((index_trunc_45 >= nobufC_dim) || (index_trunc_45 < 0));
			// phase nobufC channel 1;
			double read_nobufC_48 = (index_ignore_46 ? 0 : m_nobufC_14.read(index_trunc_43, 0));
			double read_nobufC_49 = (index_ignore_47 ? 0 : m_nobufC_14.read(index_trunc_45, 0));
			double readinterp_50 = linear_interp(index_fract_44, read_nobufC_48, read_nobufC_49);
			t_sample sample_nobufC_2 = readinterp_50;
			t_sample index_nobufC_3 = sample_index_42;
			t_sample noise_239 = noise();
			t_sample noise_220 = noise();
			t_sample noise_68 = noise();
			t_sample abs_83 = fabs(noise_68);
			t_sample mul_82 = (abs_83 * ((t_sample)0.25));
			t_sample add_60 = (mul_82 + ((int)1));
			t_sample mul_122 = (add_60 * mstosamps_120);
			t_sample noise_67 = noise();
			t_sample abs_79 = fabs(noise_67);
			t_sample mul_78 = (abs_79 * ((t_sample)0.25));
			t_sample add_59 = (mul_78 + ((int)3));
			t_sample mul_114 = (add_59 * mul_56);
			t_sample noise_66 = noise();
			t_sample abs_75 = fabs(noise_66);
			t_sample mul_74 = (abs_75 * ((t_sample)0.25));
			t_sample add_58 = (mul_74 + ((t_sample)1.7));
			t_sample mul_98 = (add_58 * mstosamps_120);
			t_sample noise_65 = noise();
			t_sample abs_71 = fabs(noise_65);
			t_sample mul_70 = (abs_71 * ((t_sample)0.25));
			t_sample add_57 = (mul_70 + ((t_sample)2.37));
			t_sample mul_91 = (add_57 * mstosamps_120);
			t_sample phasor_128 = __m_phasor_51(div_104, samples_to_seconds);
			t_sample add_127 = (phasor_128 + ((int)0));
			t_sample mod_126 = safemod(add_127, ((int)1));
			t_sample delta_85 = __m_delta_52(mod_126);
			t_sample sah_84 = __m_sah_53(mul_122, delta_85, ((int)0));
			t_sample mul_64 = (sah_84 * mod_126);
			t_sample sub_125 = (mod_126 - ((t_sample)0.5));
			t_sample mul_124 = (sub_125 * ((t_sample)3.1415926535898));
			t_sample cos_123 = cos(mul_124);
			t_sample mul_89 = (cos_123 * cos_123);
			t_sample add_119 = (phasor_128 + ((t_sample)0.25));
			t_sample mod_118 = safemod(add_119, ((int)1));
			t_sample delta_81 = __m_delta_54(mod_118);
			t_sample sah_80 = __m_sah_55(mul_114, delta_81, ((int)0));
			t_sample mul_63 = (sah_80 * mod_118);
			t_sample sub_117 = (mod_118 - ((t_sample)0.5));
			t_sample mul_116 = (sub_117 * ((t_sample)3.1415926535898));
			t_sample cos_115 = cos(mul_116);
			t_sample mul_88 = (cos_115 * cos_115);
			t_sample add_103 = (phasor_128 + ((t_sample)0.5));
			t_sample mod_102 = safemod(add_103, ((int)1));
			t_sample delta_77 = __m_delta_56(mod_102);
			t_sample sah_76 = __m_sah_57(mul_98, delta_77, ((int)0));
			t_sample mul_62 = (sah_76 * mod_102);
			t_sample sub_101 = (mod_102 - ((t_sample)0.5));
			t_sample mul_100 = (sub_101 * ((t_sample)3.1415926535898));
			t_sample cos_99 = cos(mul_100);
			t_sample mul_87 = (cos_99 * cos_99);
			t_sample add_96 = (phasor_128 + ((t_sample)0.75));
			t_sample mod_95 = safemod(add_96, ((int)1));
			t_sample delta_73 = __m_delta_58(mod_95);
			t_sample sah_72 = __m_sah_59(mul_91, delta_73, ((int)0));
			t_sample mul_61 = (sah_72 * mod_95);
			t_sample tap_110 = m_delay_3.read_linear(mul_64);
			t_sample tap_111 = m_delay_3.read_linear(mul_63);
			t_sample tap_112 = m_delay_3.read_linear(mul_62);
			t_sample tap_113 = m_delay_3.read_linear(mul_61);
			t_sample mul_107 = (tap_111 * mul_88);
			t_sample mul_108 = (tap_110 * mul_89);
			t_sample mul_97 = (tap_112 * mul_87);
			t_sample gen_132 = (mul_97 + mul_108);
			t_sample sub_94 = (mod_95 - ((t_sample)0.5));
			t_sample mul_93 = (sub_94 * ((t_sample)3.1415926535898));
			t_sample cos_92 = cos(mul_93);
			t_sample mul_86 = (cos_92 * cos_92);
			t_sample mul_90 = (tap_113 * mul_86);
			t_sample gen_133 = (mul_90 + mul_107);
			t_sample mul_54 = (gen_132 * ((t_sample)0.666));
			t_sample mul_53 = (gen_133 * ((t_sample)0.666));
			t_sample phasor_52 = __m_phasor_60(((int)22), samples_to_seconds);
			t_sample triangle_50 = triangle(phasor_52, ((t_sample)0.5));
			t_sample mul_49 = (mul_54 * triangle_50);
			t_sample mul_45 = (mul_49 * clamp_46);
			t_sample mul_48 = (mul_53 * triangle_50);
			t_sample mul_44 = (mul_48 * clamp_46);
			t_sample mul_236 = (noise_239 * m_A_8);
			t_sample mul_217 = (noise_220 * m_A_8);
			t_sample phasor_250 = __m_phasor_61(div_165, samples_to_seconds);
			t_sample wrap_249 = wrap(phasor_250, ((int)0), ((int)1));
			t_sample mul_246 = (wrap_249 * int_251);
			t_sample wrap_244 = wrap(mul_246, ((int)0), ((int)1));
			t_sample delta_242 = __m_delta_62(wrap_244);
			t_sample abs_241 = fabs(delta_242);
			int gt_240 = (abs_241 > ((t_sample)0.9));
			t_sample mul_237 = (mul_246 * ((t_sample)3.767));
			t_sample floor_235 = floor((mul_236 + mul_237));
			__m_latch_63 = ((gt_240 != 0) ? floor_235 : __m_latch_63);
			t_sample latch_238 = __m_latch_63;
			t_sample add_243 = (wrap_244 + latch_238);
			t_sample div_233 = safediv(add_243, int_251);
			t_sample wrap_232 = wrap(div_233, ((int)0), ((int)1));
			double sample_index_64 = (wrap_232 * (nobufA_dim - 1));
			int index_trunc_65 = fixnan(floor(sample_index_64));
			double index_fract_66 = (sample_index_64 - index_trunc_65);
			int index_trunc_67 = (index_trunc_65 + 1);
			bool index_ignore_68 = ((index_trunc_65 >= nobufA_dim) || (index_trunc_65 < 0));
			bool index_ignore_69 = ((index_trunc_67 >= nobufA_dim) || (index_trunc_67 < 0));
			// phase nobufA channel 1;
			double read_nobufA_70 = (index_ignore_68 ? 0 : m_nobufA_15.read(index_trunc_65, 0));
			double read_nobufA_71 = (index_ignore_69 ? 0 : m_nobufA_15.read(index_trunc_67, 0));
			double readinterp_72 = linear_interp(index_fract_66, read_nobufA_70, read_nobufA_71);
			t_sample sample_nobufA_247 = readinterp_72;
			t_sample index_nobufA_248 = sample_index_64;
			t_sample abs_198 = fabs(noise_239);
			t_sample phasor_205 = __m_phasor_73(scale_204, samples_to_seconds);
			t_sample delta_201 = __m_delta_74(phasor_205);
			t_sample abs_200 = fabs(delta_201);
			int gt_199 = (abs_200 > ((t_sample)0.9));
			__m_latch_75 = ((gt_199 != 0) ? m_history_2 : __m_latch_75);
			t_sample latch_193 = __m_latch_75;
			__m_latch_76 = ((gt_199 != 0) ? abs_198 : __m_latch_76);
			t_sample latch_202 = __m_latch_76;
			t_sample mix_324 = (latch_193 + (phasor_205 * (latch_202 - latch_193)));
			t_sample mix_195 = mix_324;
			t_sample mul_197 = (sample_nobufA_247 * mix_195);
			t_sample rsub_203 = (((int)1) - mix_195);
			t_sample mul_196 = (sample_nobufA_247 * rsub_203);
			t_sample history_194_next_209 = fixdenorm(mix_195);
			t_sample mul_38 = (mul_197 * clamp_41);
			t_sample mul_39 = (mul_196 * clamp_41);
			t_sample phasor_231 = __m_phasor_77(div_170, samples_to_seconds);
			t_sample wrap_230 = wrap(phasor_231, ((int)0), ((int)1));
			t_sample mul_227 = (wrap_230 * int_251);
			t_sample wrap_225 = wrap(mul_227, ((int)0), ((int)1));
			t_sample delta_223 = __m_delta_78(wrap_225);
			t_sample abs_222 = fabs(delta_223);
			int gt_221 = (abs_222 > ((t_sample)0.9));
			t_sample mul_218 = (mul_227 * ((t_sample)3.767));
			t_sample floor_216 = floor((mul_218 + mul_217));
			__m_latch_79 = ((gt_221 != 0) ? floor_216 : __m_latch_79);
			t_sample latch_219 = __m_latch_79;
			t_sample add_224 = (wrap_225 + latch_219);
			t_sample div_214 = safediv(add_224, int_251);
			t_sample wrap_213 = wrap(div_214, ((int)0), ((int)1));
			double sample_index_80 = (wrap_213 * (nobufB_dim - 1));
			int index_trunc_81 = fixnan(floor(sample_index_80));
			double index_fract_82 = (sample_index_80 - index_trunc_81);
			int index_trunc_83 = (index_trunc_81 + 1);
			bool index_ignore_84 = ((index_trunc_81 >= nobufB_dim) || (index_trunc_81 < 0));
			bool index_ignore_85 = ((index_trunc_83 >= nobufB_dim) || (index_trunc_83 < 0));
			// phase nobufB channel 1;
			double read_nobufB_86 = (index_ignore_84 ? 0 : m_nobufB_13.read(index_trunc_81, 0));
			double read_nobufB_87 = (index_ignore_85 ? 0 : m_nobufB_13.read(index_trunc_83, 0));
			double readinterp_88 = linear_interp(index_fract_82, read_nobufB_86, read_nobufB_87);
			t_sample sample_nobufB_228 = readinterp_88;
			t_sample index_nobufB_229 = sample_index_80;
			t_sample abs_176 = fabs(noise_220);
			t_sample phasor_183 = __m_phasor_89(scale_182, samples_to_seconds);
			t_sample delta_179 = __m_delta_90(phasor_183);
			t_sample abs_178 = fabs(delta_179);
			int gt_177 = (abs_178 > ((t_sample)0.9));
			__m_latch_91 = ((gt_177 != 0) ? m_history_1 : __m_latch_91);
			t_sample latch_171 = __m_latch_91;
			__m_latch_92 = ((gt_177 != 0) ? abs_176 : __m_latch_92);
			t_sample latch_180 = __m_latch_92;
			t_sample mix_329 = (latch_171 + (phasor_183 * (latch_180 - latch_171)));
			t_sample mix_173 = mix_329;
			t_sample mul_175 = (sample_nobufB_228 * mix_173);
			t_sample rsub_181 = (((int)1) - mix_173);
			t_sample mul_174 = (sample_nobufB_228 * rsub_181);
			t_sample history_172_next_187 = fixdenorm(mix_173);
			t_sample mul_35 = (mul_175 * clamp_41);
			t_sample OutLeft_192 = ((((mul_35 + mul_38) + mul_45) + gen_34) + sample_nobufC_2);
			t_sample out1 = OutLeft_192;
			t_sample mul_36 = (mul_174 * clamp_41);
			t_sample OutRight_191 = ((((mul_39 + mul_44) + gen_34) + sample_nobufC_2) + mul_36);
			t_sample out2 = OutRight_191;
			m_delay_6.write(plusequals_143);
			m_delay_5.write(plusequals_150);
			m_delay_4.write(plusequals_6);
			m_delay_3.write(in1);
			m_history_2 = history_194_next_209;
			m_history_1 = history_172_next_187;
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
	inline void set_B(t_param _value) {
		m_B_7 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_A(t_param _value) {
		m_A_8 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_C(t_param _value) {
		m_C_9 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_ButtonB(t_param _value) {
		m_ButtonB_10 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_D(t_param _value) {
		m_D_11 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_ButtonA(t_param _value) {
		m_ButtonA_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_nobufB(void * _value) {
		m_nobufB_13.setbuffer(_value);
	};
	inline void set_nobufC(void * _value) {
		m_nobufC_14.setbuffer(_value);
	};
	inline void set_nobufA(void * _value) {
		m_nobufA_15.setbuffer(_value);
	};
	inline t_sample trapezoid_d_d_d_d_d(t_sample x, t_sample a, t_sample b, t_sample c, t_sample d) {
		t_sample _trapezoid_ret_31 = ((int)0);
		if ((x < a)) {
			_trapezoid_ret_31 = ((int)0);
			
		} else {
			if ((x < b)) {
				_trapezoid_ret_31 = safediv((x - a), (b - a));
				
			} else {
				if ((x < c)) {
					_trapezoid_ret_31 = ((int)1);
					
				} else {
					if ((x < d)) {
						_trapezoid_ret_31 = safediv((d - x), (d - c));
						
					} else {
						_trapezoid_ret_31 = ((int)0);
						
					};
					
				};
				
			};
			
		};
		return _trapezoid_ret_31;
		
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
		case 0: *value = self->m_A_8; break;
		case 1: *value = self->m_B_7; break;
		case 2: *value = self->m_ButtonA_12; break;
		case 3: *value = self->m_ButtonB_10; break;
		case 4: *value = self->m_C_9; break;
		case 5: *value = self->m_D_11; break;
		
		
		
		
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
	// initialize parameter 0 ("m_A_8")
	pi = self->__commonstate.params + 0;
	pi->name = "A";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_A_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_B_7")
	pi = self->__commonstate.params + 1;
	pi->name = "B";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_B_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ButtonA_12")
	pi = self->__commonstate.params + 2;
	pi->name = "ButtonA";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ButtonA_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_ButtonB_10")
	pi = self->__commonstate.params + 3;
	pi->name = "ButtonB";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ButtonB_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_C_9")
	pi = self->__commonstate.params + 4;
	pi->name = "C";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_C_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_D_11")
	pi = self->__commonstate.params + 5;
	pi->name = "D";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_D_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_nobufA_15")
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
	// initialize parameter 7 ("m_nobufB_13")
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
	// initialize parameter 8 ("m_nobufC_14")
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


} // lup_shift::
