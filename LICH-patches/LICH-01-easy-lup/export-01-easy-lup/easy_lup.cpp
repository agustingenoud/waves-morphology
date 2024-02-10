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
	Data m_nobufB_6;
	Data m_nobufA_10;
	Delay m_delay_4;
	Delay m_delay_3;
	Delay m_delay_5;
	Delta __m_delta_39;
	Delta __m_delta_51;
	Delta __m_delta_31;
	Delta __m_delta_35;
	Delta __m_delta_11;
	Delta __m_delta_33;
	Delta __m_delta_67;
	Delta __m_delta_29;
	Delta __m_delta_55;
	Phasor __m_phasor_37;
	Phasor __m_phasor_38;
	Phasor __m_phasor_28;
	Phasor __m_phasor_66;
	Phasor __m_phasor_54;
	Phasor __m_phasor_50;
	PlusEquals __m_pluseq_19;
	PlusEquals __m_pluseq_14;
	PlusEquals __m_pluseq_12;
	Sah __m_sah_30;
	Sah __m_sah_34;
	Sah __m_sah_36;
	Sah __m_sah_32;
	int __exception;
	int vectorsize;
	t_sample samples_to_seconds;
	t_sample m_history_2;
	t_sample __m_latch_53;
	t_sample __m_latch_52;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample __m_latch_56;
	t_sample __m_latch_68;
	t_sample m_B_7;
	t_sample __m_latch_40;
	t_sample __m_count_20;
	t_sample __m_carry_22;
	t_sample m_ButtonA_8;
	t_sample __m_carry_17;
	t_sample m_A_9;
	t_sample __m_count_15;
	t_sample __m_latch_69;
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
		m_nobufB_6.reset("nobufB", ((int)33600), ((int)1));
		m_B_7 = ((int)0);
		m_ButtonA_8 = ((int)0);
		m_A_9 = ((int)0);
		m_nobufA_10.reset("nobufA", ((int)38400), ((int)1));
		__m_delta_11.reset(0);
		__m_pluseq_12.reset(0);
		__m_pluseq_14.reset(0);
		__m_count_15 = 0;
		__m_carry_17 = 0;
		__m_pluseq_19.reset(0);
		__m_count_20 = 0;
		__m_carry_22 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_28.reset(0);
		__m_delta_29.reset(0);
		__m_sah_30.reset(0);
		__m_delta_31.reset(0);
		__m_sah_32.reset(0);
		__m_delta_33.reset(0);
		__m_sah_34.reset(0);
		__m_delta_35.reset(0);
		__m_sah_36.reset(0);
		__m_phasor_37.reset(0);
		__m_phasor_38.reset(0);
		__m_delta_39.reset(0);
		__m_latch_40 = 0;
		__m_phasor_50.reset(0);
		__m_delta_51.reset(0);
		__m_latch_52 = 0;
		__m_latch_53 = 0;
		__m_phasor_54.reset(0);
		__m_delta_55.reset(0);
		__m_latch_56 = 0;
		__m_phasor_66.reset(0);
		__m_delta_67.reset(0);
		__m_latch_68 = 0;
		__m_latch_69 = 0;
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
		int nobufA_dim = m_nobufA_10.dim;
		int nobufA_channels = m_nobufA_10.channels;
		int dim_1871 = nobufA_dim;
		int nobufB_dim = m_nobufB_6.dim;
		int nobufB_channels = m_nobufB_6.channels;
		int dim_1864 = nobufB_dim;
		t_sample paramA_195 = m_A_9;
		t_sample paramA_214 = paramA_195;
		t_sample sub_8817 = (m_A_9 - ((int)0));
		t_sample scale_8814 = ((safepow((sub_8817 * ((t_sample)20)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample clamp_7695 = ((scale_8814 <= ((int)0)) ? ((int)0) : ((scale_8814 >= ((int)1)) ? ((int)1) : scale_8814));
		t_sample sub_8821 = (m_B_7 - ((int)0));
		t_sample scale_8818 = ((safepow((sub_8821 * ((t_sample)1)), ((int)1)) * ((int)2)) + ((int)0));
		t_sample mstosamps_2379 = (((int)256) * (samplerate * 0.001));
		t_sample mul_3036 = (mstosamps_2379 * ((t_sample)0.2));
		t_sample rsub_2365 = (((int)1) - scale_8818);
		t_sample mul_2364 = (rsub_2365 * ((int)1000));
		t_sample div_2363 = (mul_2364 * ((t_sample)0.00390625));
		samples_to_seconds = (1 / samplerate);
		t_sample sub_8825 = (scale_8818 - ((int)0));
		t_sample scale_8822 = ((safepow((sub_8825 * ((t_sample)10)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample clamp_6105 = ((scale_8822 <= ((int)0)) ? ((int)0) : ((scale_8822 >= ((int)1)) ? ((int)1) : scale_8822));
		t_sample sub_8829 = (m_A_9 - ((t_sample)0.0001));
		t_sample scale_8826 = ((safepow((sub_8829 * ((t_sample)1.000200040008)), ((int)1)) * ((int)8)) + ((int)1));
		int int_254 = int(scale_8826);
		int dim_1695 = nobufA_dim;
		t_sample div_1753 = safediv(samplerate, dim_1695);
		t_sample sub_8833 = (paramA_214 - ((int)0));
		t_sample scale_8830 = ((safepow((sub_8833 * ((t_sample)1)), ((int)1)) * ((t_sample)5.8)) + ((t_sample)0.2));
		t_sample scale_209 = scale_8830;
		int dim_1792 = nobufB_dim;
		t_sample div_1812 = safediv(samplerate, dim_1792);
		t_sample sub_8838 = (paramA_195 - ((int)0));
		t_sample scale_8835 = ((safepow((sub_8838 * ((t_sample)1)), ((int)1)) * ((t_sample)5.8)) + ((t_sample)0.2));
		t_sample scale_190 = scale_8835;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample tap_1870 = m_delay_5.read_step(dim_1871);
			t_sample tap_1863 = m_delay_4.read_step(dim_1864);
			t_sample delta_1860 = __m_delta_11(m_ButtonA_8);
			t_sample gtp_1859 = ((delta_1860 > ((int)0)) ? delta_1860 : 0);
			t_sample plusequals_1858 = __m_pluseq_12.post(gtp_1859, ((int)0), 0);
			t_sample mod_1857 = safemod(plusequals_1858, ((int)2));
			t_sample add_1854 = (mod_1857 + ((int)1));
			t_sample choice_13 = int(add_1854);
			t_sample gate_1855 = (((choice_13 >= 1) && (choice_13 < 2)) ? gtp_1859 : 0);
			t_sample gate_1856 = ((choice_13 >= 2) ? gtp_1859 : 0);
			t_sample plusequals_1868 = __m_pluseq_14.post(gate_1855, tap_1870, 0);
			__m_count_15 = (gate_1855 ? 0 : (fixdenorm(__m_count_15 + plusequals_1868)));
			int carry_16 = 0;
			if ((gate_1855 != 0)) {
				__m_count_15 = 0;
				__m_carry_17 = 0;
				
			} else if (((dim_1871 > 0) && (__m_count_15 >= dim_1871))) {
				int wraps_18 = (__m_count_15 / dim_1871);
				__m_carry_17 = (__m_carry_17 + wraps_18);
				__m_count_15 = (__m_count_15 - (wraps_18 * dim_1871));
				carry_16 = 1;
				
			};
			t_sample counter_1872 = __m_count_15;
			int counter_1873 = carry_16;
			int counter_1874 = __m_carry_17;
			t_sample plusequals_1861 = __m_pluseq_19.post(gate_1856, tap_1863, 0);
			__m_count_20 = (gate_1856 ? 0 : (fixdenorm(__m_count_20 + plusequals_1861)));
			int carry_21 = 0;
			if ((gate_1856 != 0)) {
				__m_count_20 = 0;
				__m_carry_22 = 0;
				
			} else if (((dim_1864 > 0) && (__m_count_20 >= dim_1864))) {
				int wraps_23 = (__m_count_20 / dim_1864);
				__m_carry_22 = (__m_carry_22 + wraps_23);
				__m_count_20 = (__m_count_20 - (wraps_23 * dim_1864));
				carry_21 = 1;
				
			};
			t_sample counter_1865 = __m_count_20;
			int counter_1866 = carry_21;
			int counter_1867 = __m_carry_22;
			int index_trunc_24 = fixnan(floor(counter_1865));
			int index_wrap_25 = ((index_trunc_24 < 0) ? ((nobufB_dim - 1) + ((index_trunc_24 + 1) % nobufB_dim)) : (index_trunc_24 % nobufB_dim));
			m_nobufB_6.write(in1, index_wrap_25, 0);
			int index_trunc_26 = fixnan(floor(counter_1872));
			int index_wrap_27 = ((index_trunc_26 < 0) ? ((nobufA_dim - 1) + ((index_trunc_26 + 1) % nobufA_dim)) : (index_trunc_26 % nobufA_dim));
			m_nobufA_10.write(in1, index_wrap_27, 0);
			t_sample noise_242 = noise();
			t_sample noise_222 = noise();
			t_sample noise_2327 = noise();
			t_sample abs_2342 = fabs(noise_2327);
			t_sample mul_2341 = (abs_2342 * ((t_sample)0.25));
			t_sample add_2319 = (mul_2341 + ((int)1));
			t_sample mul_2381 = (add_2319 * mstosamps_2379);
			t_sample noise_2326 = noise();
			t_sample abs_2338 = fabs(noise_2326);
			t_sample mul_2337 = (abs_2338 * ((t_sample)0.25));
			t_sample add_2797 = (mul_2337 + ((int)3));
			t_sample mul_2373 = (add_2797 * mul_3036);
			t_sample noise_2325 = noise();
			t_sample abs_2334 = fabs(noise_2325);
			t_sample mul_2333 = (abs_2334 * ((t_sample)0.25));
			t_sample add_2845 = (mul_2333 + ((t_sample)1.7));
			t_sample mul_2357 = (add_2845 * mstosamps_2379);
			t_sample noise_2324 = noise();
			t_sample abs_2330 = fabs(noise_2324);
			t_sample mul_2329 = (abs_2330 * ((t_sample)0.25));
			t_sample add_2893 = (mul_2329 + ((t_sample)2.37));
			t_sample mul_2350 = (add_2893 * mstosamps_2379);
			t_sample phasor_2387 = __m_phasor_28(div_2363, samples_to_seconds);
			t_sample add_2386 = (phasor_2387 + ((int)0));
			t_sample mod_2385 = safemod(add_2386, ((int)1));
			t_sample delta_2344 = __m_delta_29(mod_2385);
			t_sample sah_2343 = __m_sah_30(mul_2381, delta_2344, ((int)0));
			t_sample mul_2323 = (sah_2343 * mod_2385);
			t_sample sub_2384 = (mod_2385 - ((t_sample)0.5));
			t_sample mul_2383 = (sub_2384 * ((t_sample)3.1415926535898));
			t_sample cos_2382 = cos(mul_2383);
			t_sample mul_2348 = (cos_2382 * cos_2382);
			t_sample add_2378 = (phasor_2387 + ((t_sample)0.25));
			t_sample mod_2377 = safemod(add_2378, ((int)1));
			t_sample delta_2340 = __m_delta_31(mod_2377);
			t_sample sah_2339 = __m_sah_32(mul_2373, delta_2340, ((int)0));
			t_sample mul_2322 = (sah_2339 * mod_2377);
			t_sample sub_2376 = (mod_2377 - ((t_sample)0.5));
			t_sample mul_2375 = (sub_2376 * ((t_sample)3.1415926535898));
			t_sample cos_2374 = cos(mul_2375);
			t_sample mul_2347 = (cos_2374 * cos_2374);
			t_sample add_2362 = (phasor_2387 + ((t_sample)0.5));
			t_sample mod_2361 = safemod(add_2362, ((int)1));
			t_sample delta_2336 = __m_delta_33(mod_2361);
			t_sample sah_2335 = __m_sah_34(mul_2357, delta_2336, ((int)0));
			t_sample mul_2321 = (sah_2335 * mod_2361);
			t_sample sub_2360 = (mod_2361 - ((t_sample)0.5));
			t_sample mul_2359 = (sub_2360 * ((t_sample)3.1415926535898));
			t_sample cos_2358 = cos(mul_2359);
			t_sample mul_2346 = (cos_2358 * cos_2358);
			t_sample add_2355 = (phasor_2387 + ((t_sample)0.75));
			t_sample mod_2354 = safemod(add_2355, ((int)1));
			t_sample delta_2332 = __m_delta_35(mod_2354);
			t_sample sah_2331 = __m_sah_36(mul_2350, delta_2332, ((int)0));
			t_sample mul_2320 = (sah_2331 * mod_2354);
			t_sample tap_2369 = m_delay_3.read_linear(mul_2323);
			t_sample tap_2370 = m_delay_3.read_linear(mul_2322);
			t_sample tap_2371 = m_delay_3.read_linear(mul_2321);
			t_sample tap_2372 = m_delay_3.read_linear(mul_2320);
			t_sample mul_2367 = (tap_2369 * mul_2348);
			t_sample mul_2356 = (tap_2371 * mul_2346);
			t_sample gen_3038 = (mul_2356 + mul_2367);
			t_sample mul_2366 = (tap_2370 * mul_2347);
			t_sample sub_2353 = (mod_2354 - ((t_sample)0.5));
			t_sample mul_2352 = (sub_2353 * ((t_sample)3.1415926535898));
			t_sample cos_2351 = cos(mul_2352);
			t_sample mul_2345 = (cos_2351 * cos_2351);
			t_sample mul_2349 = (tap_2372 * mul_2345);
			t_sample gen_3039 = (mul_2366 + mul_2349);
			t_sample mul_4673 = (gen_3038 * ((t_sample)0.666));
			t_sample mul_4726 = (gen_3039 * ((t_sample)0.666));
			t_sample phasor_3084 = __m_phasor_37(((int)22), samples_to_seconds);
			t_sample triangle_7267 = triangle(phasor_3084, ((t_sample)0.5));
			t_sample mul_3395 = (mul_4673 * triangle_7267);
			t_sample mul_6432 = (mul_3395 * clamp_6105);
			t_sample mul_3484 = (mul_4726 * triangle_7267);
			t_sample mul_6431 = (mul_3484 * clamp_6105);
			t_sample mul_239 = (noise_242 * m_A_9);
			t_sample mul_219 = (noise_222 * m_A_9);
			t_sample phasor_253 = __m_phasor_38(div_1753, samples_to_seconds);
			t_sample wrap_252 = wrap(phasor_253, ((int)0), ((int)1));
			t_sample mul_249 = (wrap_252 * int_254);
			t_sample wrap_247 = wrap(mul_249, ((int)0), ((int)1));
			t_sample delta_245 = __m_delta_39(wrap_247);
			t_sample abs_244 = fabs(delta_245);
			int gt_243 = (abs_244 > ((t_sample)0.9));
			t_sample mul_240 = (mul_249 * ((t_sample)3.767));
			t_sample floor_238 = floor((mul_239 + mul_240));
			__m_latch_40 = ((gt_243 != 0) ? floor_238 : __m_latch_40);
			t_sample latch_241 = __m_latch_40;
			t_sample add_246 = (wrap_247 + latch_241);
			t_sample div_236 = safediv(add_246, int_254);
			t_sample wrap_235 = wrap(div_236, ((int)0), ((int)1));
			double sample_index_41 = (wrap_235 * (nobufA_dim - 1));
			int index_trunc_42 = fixnan(floor(sample_index_41));
			double index_fract_43 = (sample_index_41 - index_trunc_42);
			int index_trunc_44 = (index_trunc_42 + 1);
			bool index_ignore_45 = ((index_trunc_42 >= nobufA_dim) || (index_trunc_42 < 0));
			bool index_ignore_46 = ((index_trunc_44 >= nobufA_dim) || (index_trunc_44 < 0));
			// phase nobufA channel 1;
			double read_nobufA_47 = (index_ignore_45 ? 0 : m_nobufA_10.read(index_trunc_42, 0));
			double read_nobufA_48 = (index_ignore_46 ? 0 : m_nobufA_10.read(index_trunc_44, 0));
			double readinterp_49 = linear_interp(index_fract_43, read_nobufA_47, read_nobufA_48);
			t_sample sample_nobufA_250 = readinterp_49;
			t_sample index_nobufA_251 = sample_index_41;
			t_sample abs_203 = fabs(noise_242);
			t_sample phasor_210 = __m_phasor_50(scale_209, samples_to_seconds);
			t_sample delta_206 = __m_delta_51(phasor_210);
			t_sample abs_205 = fabs(delta_206);
			int gt_204 = (abs_205 > ((t_sample)0.9));
			__m_latch_52 = ((gt_204 != 0) ? m_history_2 : __m_latch_52);
			t_sample latch_198 = __m_latch_52;
			__m_latch_53 = ((gt_204 != 0) ? abs_203 : __m_latch_53);
			t_sample latch_207 = __m_latch_53;
			t_sample mix_8834 = (latch_198 + (phasor_210 * (latch_207 - latch_198)));
			t_sample mix_200 = mix_8834;
			t_sample mul_202 = (sample_nobufA_250 * mix_200);
			t_sample rsub_208 = (((int)1) - mix_200);
			t_sample mul_201 = (sample_nobufA_250 * rsub_208);
			t_sample history_199_next_211 = fixdenorm(mix_200);
			t_sample mul_8120 = (mul_202 * clamp_7695);
			t_sample mul_7999 = (mul_201 * clamp_7695);
			t_sample phasor_233 = __m_phasor_54(div_1812, samples_to_seconds);
			t_sample wrap_232 = wrap(phasor_233, ((int)0), ((int)1));
			t_sample mul_229 = (wrap_232 * int_254);
			t_sample wrap_227 = wrap(mul_229, ((int)0), ((int)1));
			t_sample delta_225 = __m_delta_55(wrap_227);
			t_sample abs_224 = fabs(delta_225);
			int gt_223 = (abs_224 > ((t_sample)0.9));
			t_sample mul_220 = (mul_229 * ((t_sample)3.767));
			t_sample floor_218 = floor((mul_220 + mul_219));
			__m_latch_56 = ((gt_223 != 0) ? floor_218 : __m_latch_56);
			t_sample latch_221 = __m_latch_56;
			t_sample add_226 = (wrap_227 + latch_221);
			t_sample div_216 = safediv(add_226, int_254);
			t_sample wrap_215 = wrap(div_216, ((int)0), ((int)1));
			double sample_index_57 = (wrap_215 * (nobufB_dim - 1));
			int index_trunc_58 = fixnan(floor(sample_index_57));
			double index_fract_59 = (sample_index_57 - index_trunc_58);
			int index_trunc_60 = (index_trunc_58 + 1);
			bool index_ignore_61 = ((index_trunc_58 >= nobufB_dim) || (index_trunc_58 < 0));
			bool index_ignore_62 = ((index_trunc_60 >= nobufB_dim) || (index_trunc_60 < 0));
			// phase nobufB channel 1;
			double read_nobufB_63 = (index_ignore_61 ? 0 : m_nobufB_6.read(index_trunc_58, 0));
			double read_nobufB_64 = (index_ignore_62 ? 0 : m_nobufB_6.read(index_trunc_60, 0));
			double readinterp_65 = linear_interp(index_fract_59, read_nobufB_63, read_nobufB_64);
			t_sample sample_nobufB_230 = readinterp_65;
			t_sample index_nobufB_231 = sample_index_57;
			t_sample abs_184 = fabs(noise_222);
			t_sample phasor_191 = __m_phasor_66(scale_190, samples_to_seconds);
			t_sample delta_187 = __m_delta_67(phasor_191);
			t_sample abs_186 = fabs(delta_187);
			int gt_185 = (abs_186 > ((t_sample)0.9));
			__m_latch_68 = ((gt_185 != 0) ? m_history_1 : __m_latch_68);
			t_sample latch_179 = __m_latch_68;
			__m_latch_69 = ((gt_185 != 0) ? abs_184 : __m_latch_69);
			t_sample latch_188 = __m_latch_69;
			t_sample mix_8839 = (latch_179 + (phasor_191 * (latch_188 - latch_179)));
			t_sample mix_181 = mix_8839;
			t_sample mul_183 = (sample_nobufB_230 * mix_181);
			t_sample rsub_189 = (((int)1) - mix_181);
			t_sample mul_182 = (sample_nobufB_230 * rsub_189);
			t_sample history_180_next_192 = fixdenorm(mix_181);
			t_sample mul_8361 = (mul_183 * clamp_7695);
			t_sample OutLeft_197 = ((mul_8361 + mul_8120) + mul_6432);
			t_sample out1 = OutLeft_197;
			t_sample mul_8362 = (mul_182 * clamp_7695);
			t_sample OutRight_196 = ((mul_8362 + mul_7999) + mul_6431);
			t_sample out2 = OutRight_196;
			m_delay_5.write(plusequals_1868);
			m_delay_4.write(plusequals_1861);
			m_delay_3.write(in1);
			m_history_2 = history_199_next_211;
			m_history_1 = history_180_next_192;
			m_delay_3.step();
			m_delay_4.step();
			m_delay_5.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_nobufB(void * _value) {
		m_nobufB_6.setbuffer(_value);
	};
	inline void set_B(t_param _value) {
		m_B_7 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_ButtonA(t_param _value) {
		m_ButtonA_8 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_A(t_param _value) {
		m_A_9 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_nobufA(void * _value) {
		m_nobufA_10.setbuffer(_value);
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
int num_params() { return 5; }

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
		case 2: self->set_ButtonA(value); break;
		case 3: self->set_nobufA(ref); break;
		case 4: self->set_nobufB(ref); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_A_9; break;
		case 1: *value = self->m_B_7; break;
		case 2: *value = self->m_ButtonA_8; break;
		
		
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(5 * sizeof(ParamInfo));
	self->__commonstate.numparams = 5;
	// initialize parameter 0 ("m_A_9")
	pi = self->__commonstate.params + 0;
	pi->name = "A";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_A_9;
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
	// initialize parameter 2 ("m_ButtonA_8")
	pi = self->__commonstate.params + 2;
	pi->name = "ButtonA";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ButtonA_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_nobufA_10")
	pi = self->__commonstate.params + 3;
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
	// initialize parameter 4 ("m_nobufB_6")
	pi = self->__commonstate.params + 4;
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
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // easy_lup::
