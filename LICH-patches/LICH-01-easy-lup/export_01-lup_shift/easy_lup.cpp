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
	Data m_nobufC_15;
	Data m_nobufB_9;
	Data m_nobufA_7;
	Delay m_delay_5;
	Delay m_delay_4;
	Delay m_delay_3;
	Delay m_delay_6;
	Delta __m_delta_78;
	Delta __m_delta_62;
	Delta __m_delta_56;
	Delta __m_delta_58;
	Delta __m_delta_54;
	Delta __m_delta_33;
	Delta __m_delta_74;
	Delta __m_delta_90;
	Delta __m_delta_16;
	Delta __m_delta_52;
	Phasor __m_phasor_41;
	Phasor __m_phasor_60;
	Phasor __m_phasor_61;
	Phasor __m_phasor_77;
	Phasor __m_phasor_73;
	Phasor __m_phasor_51;
	Phasor __m_phasor_89;
	PlusEquals __m_pluseq_17;
	PlusEquals __m_pluseq_34;
	PlusEquals __m_pluseq_24;
	PlusEquals __m_pluseq_19;
	Sah __m_sah_59;
	Sah __m_sah_53;
	Sah __m_sah_57;
	Sah __m_sah_55;
	int __exception;
	int vectorsize;
	t_sample __m_carry_37;
	t_sample __m_latch_75;
	t_sample m_B_8;
	t_sample __m_latch_76;
	t_sample m_D_10;
	t_sample m_history_2;
	t_sample __m_latch_79;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample samples_to_seconds;
	t_sample __m_latch_63;
	t_sample m_A_12;
	t_sample __m_carry_27;
	t_sample __m_latch_91;
	t_sample __m_count_35;
	t_sample m_C_11;
	t_sample __m_count_25;
	t_sample __m_count_20;
	t_sample __m_carry_22;
	t_sample m_ButtonA_13;
	t_sample m_ButtonB_14;
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
		m_nobufA_7.reset("nobufA", ((int)38400), ((int)1));
		m_B_8 = ((int)0);
		m_nobufB_9.reset("nobufB", ((int)33600), ((int)1));
		m_D_10 = ((int)0);
		m_C_11 = ((int)0);
		m_A_12 = ((int)0);
		m_ButtonA_13 = ((int)0);
		m_ButtonB_14 = ((int)0);
		m_nobufC_15.reset("nobufC", ((int)48000), ((int)1));
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
		t_sample expr_573 = ((m_C_11 * ((int)2)) - ((int)1));
		int nobufB_dim = m_nobufB_9.dim;
		int nobufB_channels = m_nobufB_9.channels;
		int dim_476 = nobufB_dim;
		int nobufA_dim = m_nobufA_7.dim;
		int nobufA_channels = m_nobufA_7.channels;
		int dim_483 = nobufA_dim;
		int nobufC_dim = m_nobufC_15.dim;
		int nobufC_channels = m_nobufC_15.channels;
		int dim_348 = nobufC_dim;
		t_sample sub_577 = (m_D_10 - ((int)0));
		t_sample scale_574 = ((safepow((sub_577 * ((t_sample)1)), ((int)1)) * ((t_sample)1.25)) + ((int)0));
		t_sample sub_359 = (scale_574 - ((t_sample)0.25));
		samples_to_seconds = (1 / samplerate);
		t_sample paramA_532 = m_A_12;
		t_sample paramA_513 = paramA_532;
		t_sample sub_581 = (m_A_12 - ((int)0));
		t_sample scale_578 = ((safepow((sub_581 * ((t_sample)20)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample clamp_374 = ((scale_578 <= ((int)0)) ? ((int)0) : ((scale_578 >= ((int)1)) ? ((int)1) : scale_578));
		t_sample sub_585 = (m_B_8 - ((int)0));
		t_sample scale_582 = ((safepow((sub_585 * ((t_sample)1)), ((int)1)) * ((int)2)) + ((int)0));
		t_sample mstosamps_453 = (((int)256) * (samplerate * 0.001));
		t_sample mul_389 = (mstosamps_453 * ((t_sample)0.2));
		t_sample rsub_439 = (((int)1) - scale_582);
		t_sample mul_438 = (rsub_439 * ((int)1000));
		t_sample div_437 = (mul_438 * ((t_sample)0.00390625));
		t_sample sub_589 = (scale_582 - ((int)0));
		t_sample scale_586 = ((safepow((sub_589 * ((t_sample)10)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample clamp_379 = ((scale_586 <= ((int)0)) ? ((int)0) : ((scale_586 >= ((int)1)) ? ((int)1) : scale_586));
		t_sample sub_593 = (m_A_12 - ((t_sample)0.0001));
		t_sample scale_590 = ((safepow((sub_593 * ((t_sample)1.000200040008)), ((int)1)) * ((int)8)) + ((int)1));
		int int_571 = int(scale_590);
		int dim_490 = nobufA_dim;
		t_sample div_491 = safediv(samplerate, dim_490);
		t_sample sub_597 = (paramA_532 - ((int)0));
		t_sample scale_594 = ((safepow((sub_597 * ((t_sample)1)), ((int)1)) * ((t_sample)5.8)) + ((t_sample)0.2));
		t_sample scale_527 = scale_594;
		int dim_489 = nobufB_dim;
		t_sample div_496 = safediv(samplerate, dim_489);
		t_sample sub_602 = (paramA_513 - ((int)0));
		t_sample scale_599 = ((safepow((sub_602 * ((t_sample)1)), ((int)1)) * ((t_sample)5.8)) + ((t_sample)0.2));
		t_sample scale_508 = scale_599;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample tap_475 = m_delay_6.read_step(dim_476);
			t_sample tap_482 = m_delay_5.read_step(dim_483);
			t_sample delta_472 = __m_delta_16(m_ButtonA_13);
			t_sample gtp_471 = ((delta_472 > ((int)0)) ? delta_472 : 0);
			t_sample plusequals_470 = __m_pluseq_17.post(gtp_471, ((int)0), 0);
			t_sample mod_469 = safemod(plusequals_470, ((int)2));
			t_sample add_466 = (mod_469 + ((int)1));
			t_sample choice_18 = int(add_466);
			t_sample gate_467 = (((choice_18 >= 1) && (choice_18 < 2)) ? gtp_471 : 0);
			t_sample gate_468 = ((choice_18 >= 2) ? gtp_471 : 0);
			t_sample plusequals_473 = __m_pluseq_19.post(gate_468, tap_475, 0);
			__m_count_20 = (gate_468 ? 0 : (fixdenorm(__m_count_20 + plusequals_473)));
			int carry_21 = 0;
			if ((gate_468 != 0)) {
				__m_count_20 = 0;
				__m_carry_22 = 0;
				
			} else if (((dim_476 > 0) && (__m_count_20 >= dim_476))) {
				int wraps_23 = (__m_count_20 / dim_476);
				__m_carry_22 = (__m_carry_22 + wraps_23);
				__m_count_20 = (__m_count_20 - (wraps_23 * dim_476));
				carry_21 = 1;
				
			};
			t_sample counter_477 = __m_count_20;
			int counter_478 = carry_21;
			int counter_479 = __m_carry_22;
			t_sample plusequals_480 = __m_pluseq_24.post(gate_467, tap_482, 0);
			__m_count_25 = (gate_467 ? 0 : (fixdenorm(__m_count_25 + plusequals_480)));
			int carry_26 = 0;
			if ((gate_467 != 0)) {
				__m_count_25 = 0;
				__m_carry_27 = 0;
				
			} else if (((dim_483 > 0) && (__m_count_25 >= dim_483))) {
				int wraps_28 = (__m_count_25 / dim_483);
				__m_carry_27 = (__m_carry_27 + wraps_28);
				__m_count_25 = (__m_count_25 - (wraps_28 * dim_483));
				carry_26 = 1;
				
			};
			t_sample counter_484 = __m_count_25;
			int counter_485 = carry_26;
			int counter_486 = __m_carry_27;
			int index_trunc_29 = fixnan(floor(counter_484));
			int index_wrap_30 = ((index_trunc_29 < 0) ? ((nobufA_dim - 1) + ((index_trunc_29 + 1) % nobufA_dim)) : (index_trunc_29 % nobufA_dim));
			m_nobufA_7.write(in1, index_wrap_30, 0);
			int index_trunc_31 = fixnan(floor(counter_477));
			int index_wrap_32 = ((index_trunc_31 < 0) ? ((nobufB_dim - 1) + ((index_trunc_31 + 1) % nobufB_dim)) : (index_trunc_31 % nobufB_dim));
			m_nobufB_9.write(in1, index_wrap_32, 0);
			t_sample tap_347 = m_delay_4.read_step(dim_348);
			t_sample delta_353 = __m_delta_33(m_ButtonB_14);
			t_sample gtp_352 = ((delta_353 > ((int)0)) ? delta_353 : 0);
			t_sample plusequals_345 = __m_pluseq_34.post(gtp_352, tap_347, 0);
			__m_count_35 = (gtp_352 ? 0 : (fixdenorm(__m_count_35 + plusequals_345)));
			int carry_36 = 0;
			if ((gtp_352 != 0)) {
				__m_count_35 = 0;
				__m_carry_37 = 0;
				
			} else if (((dim_348 > 0) && (__m_count_35 >= dim_348))) {
				int wraps_38 = (__m_count_35 / dim_348);
				__m_carry_37 = (__m_carry_37 + wraps_38);
				__m_count_35 = (__m_count_35 - (wraps_38 * dim_348));
				carry_36 = 1;
				
			};
			t_sample counter_349 = __m_count_35;
			int counter_350 = carry_36;
			int counter_351 = __m_carry_37;
			int index_trunc_39 = fixnan(floor(counter_349));
			int index_wrap_40 = ((index_trunc_39 < 0) ? ((nobufC_dim - 1) + ((index_trunc_39 + 1) % nobufC_dim)) : (index_trunc_39 % nobufC_dim));
			m_nobufC_15.write(in1, index_wrap_40, 0);
			t_sample expr_365 = trapezoid_d_d_d_d_d(scale_574, ((t_sample)0.3), ((t_sample)0.4), ((t_sample)0.7), ((t_sample)0.8));
			t_sample expr_366 = trapezoid_d_d_d_d_d(sub_359, ((t_sample)0.3), ((t_sample)0.4), ((t_sample)0.7), ((t_sample)0.8));
			t_sample mul_363 = (in1 * expr_365);
			t_sample mul_357 = (in2 * expr_366);
			t_sample gen_367 = (mul_357 + mul_363);
			t_sample phasor_344 = __m_phasor_41(expr_573, samples_to_seconds);
			t_sample wrap_343 = wrap(phasor_344, ((int)0), ((int)1));
			double sample_index_42 = (wrap_343 * (nobufC_dim - 1));
			int index_trunc_43 = fixnan(floor(sample_index_42));
			double index_fract_44 = (sample_index_42 - index_trunc_43);
			int index_trunc_45 = (index_trunc_43 + 1);
			bool index_ignore_46 = ((index_trunc_43 >= nobufC_dim) || (index_trunc_43 < 0));
			bool index_ignore_47 = ((index_trunc_45 >= nobufC_dim) || (index_trunc_45 < 0));
			// phase nobufC channel 1;
			double read_nobufC_48 = (index_ignore_46 ? 0 : m_nobufC_15.read(index_trunc_43, 0));
			double read_nobufC_49 = (index_ignore_47 ? 0 : m_nobufC_15.read(index_trunc_45, 0));
			double readinterp_50 = linear_interp(index_fract_44, read_nobufC_48, read_nobufC_49);
			t_sample sample_nobufC_341 = readinterp_50;
			t_sample index_nobufC_342 = sample_index_42;
			t_sample noise_559 = noise();
			t_sample noise_540 = noise();
			t_sample noise_401 = noise();
			t_sample abs_416 = fabs(noise_401);
			t_sample mul_415 = (abs_416 * ((t_sample)0.25));
			t_sample add_393 = (mul_415 + ((int)1));
			t_sample mul_455 = (add_393 * mstosamps_453);
			t_sample noise_400 = noise();
			t_sample abs_412 = fabs(noise_400);
			t_sample mul_411 = (abs_412 * ((t_sample)0.25));
			t_sample add_392 = (mul_411 + ((int)3));
			t_sample mul_447 = (add_392 * mul_389);
			t_sample noise_399 = noise();
			t_sample abs_408 = fabs(noise_399);
			t_sample mul_407 = (abs_408 * ((t_sample)0.25));
			t_sample add_391 = (mul_407 + ((t_sample)1.7));
			t_sample mul_431 = (add_391 * mstosamps_453);
			t_sample noise_398 = noise();
			t_sample abs_404 = fabs(noise_398);
			t_sample mul_403 = (abs_404 * ((t_sample)0.25));
			t_sample add_390 = (mul_403 + ((t_sample)2.37));
			t_sample mul_424 = (add_390 * mstosamps_453);
			t_sample phasor_461 = __m_phasor_51(div_437, samples_to_seconds);
			t_sample add_460 = (phasor_461 + ((int)0));
			t_sample mod_459 = safemod(add_460, ((int)1));
			t_sample delta_418 = __m_delta_52(mod_459);
			t_sample sah_417 = __m_sah_53(mul_455, delta_418, ((int)0));
			t_sample mul_397 = (sah_417 * mod_459);
			t_sample sub_458 = (mod_459 - ((t_sample)0.5));
			t_sample mul_457 = (sub_458 * ((t_sample)3.1415926535898));
			t_sample cos_456 = cos(mul_457);
			t_sample mul_422 = (cos_456 * cos_456);
			t_sample add_452 = (phasor_461 + ((t_sample)0.25));
			t_sample mod_451 = safemod(add_452, ((int)1));
			t_sample delta_414 = __m_delta_54(mod_451);
			t_sample sah_413 = __m_sah_55(mul_447, delta_414, ((int)0));
			t_sample mul_396 = (sah_413 * mod_451);
			t_sample sub_450 = (mod_451 - ((t_sample)0.5));
			t_sample mul_449 = (sub_450 * ((t_sample)3.1415926535898));
			t_sample cos_448 = cos(mul_449);
			t_sample mul_421 = (cos_448 * cos_448);
			t_sample add_436 = (phasor_461 + ((t_sample)0.5));
			t_sample mod_435 = safemod(add_436, ((int)1));
			t_sample delta_410 = __m_delta_56(mod_435);
			t_sample sah_409 = __m_sah_57(mul_431, delta_410, ((int)0));
			t_sample mul_395 = (sah_409 * mod_435);
			t_sample sub_434 = (mod_435 - ((t_sample)0.5));
			t_sample mul_433 = (sub_434 * ((t_sample)3.1415926535898));
			t_sample cos_432 = cos(mul_433);
			t_sample mul_420 = (cos_432 * cos_432);
			t_sample add_429 = (phasor_461 + ((t_sample)0.75));
			t_sample mod_428 = safemod(add_429, ((int)1));
			t_sample delta_406 = __m_delta_58(mod_428);
			t_sample sah_405 = __m_sah_59(mul_424, delta_406, ((int)0));
			t_sample mul_394 = (sah_405 * mod_428);
			t_sample tap_443 = m_delay_3.read_linear(mul_397);
			t_sample tap_444 = m_delay_3.read_linear(mul_396);
			t_sample tap_445 = m_delay_3.read_linear(mul_395);
			t_sample tap_446 = m_delay_3.read_linear(mul_394);
			t_sample mul_441 = (tap_443 * mul_422);
			t_sample mul_430 = (tap_445 * mul_420);
			t_sample gen_462 = (mul_430 + mul_441);
			t_sample mul_440 = (tap_444 * mul_421);
			t_sample sub_427 = (mod_428 - ((t_sample)0.5));
			t_sample mul_426 = (sub_427 * ((t_sample)3.1415926535898));
			t_sample cos_425 = cos(mul_426);
			t_sample mul_419 = (cos_425 * cos_425);
			t_sample mul_423 = (tap_446 * mul_419);
			t_sample gen_463 = (mul_423 + mul_440);
			t_sample mul_387 = (gen_462 * ((t_sample)0.666));
			t_sample mul_386 = (gen_463 * ((t_sample)0.666));
			t_sample phasor_385 = __m_phasor_60(((int)22), samples_to_seconds);
			t_sample triangle_383 = triangle(phasor_385, ((t_sample)0.5));
			t_sample mul_382 = (mul_387 * triangle_383);
			t_sample mul_378 = (mul_382 * clamp_379);
			t_sample mul_381 = (mul_386 * triangle_383);
			t_sample mul_377 = (mul_381 * clamp_379);
			t_sample mul_556 = (noise_559 * m_A_12);
			t_sample mul_537 = (noise_540 * m_A_12);
			t_sample phasor_570 = __m_phasor_61(div_491, samples_to_seconds);
			t_sample wrap_569 = wrap(phasor_570, ((int)0), ((int)1));
			t_sample mul_566 = (wrap_569 * int_571);
			t_sample wrap_564 = wrap(mul_566, ((int)0), ((int)1));
			t_sample delta_562 = __m_delta_62(wrap_564);
			t_sample abs_561 = fabs(delta_562);
			int gt_560 = (abs_561 > ((t_sample)0.9));
			t_sample mul_557 = (mul_566 * ((t_sample)3.767));
			t_sample floor_555 = floor((mul_556 + mul_557));
			__m_latch_63 = ((gt_560 != 0) ? floor_555 : __m_latch_63);
			t_sample latch_558 = __m_latch_63;
			t_sample add_563 = (wrap_564 + latch_558);
			t_sample div_553 = safediv(add_563, int_571);
			t_sample wrap_552 = wrap(div_553, ((int)0), ((int)1));
			double sample_index_64 = (wrap_552 * (nobufA_dim - 1));
			int index_trunc_65 = fixnan(floor(sample_index_64));
			double index_fract_66 = (sample_index_64 - index_trunc_65);
			int index_trunc_67 = (index_trunc_65 + 1);
			bool index_ignore_68 = ((index_trunc_65 >= nobufA_dim) || (index_trunc_65 < 0));
			bool index_ignore_69 = ((index_trunc_67 >= nobufA_dim) || (index_trunc_67 < 0));
			// phase nobufA channel 1;
			double read_nobufA_70 = (index_ignore_68 ? 0 : m_nobufA_7.read(index_trunc_65, 0));
			double read_nobufA_71 = (index_ignore_69 ? 0 : m_nobufA_7.read(index_trunc_67, 0));
			double readinterp_72 = linear_interp(index_fract_66, read_nobufA_70, read_nobufA_71);
			t_sample sample_nobufA_567 = readinterp_72;
			t_sample index_nobufA_568 = sample_index_64;
			t_sample abs_521 = fabs(noise_559);
			t_sample phasor_528 = __m_phasor_73(scale_527, samples_to_seconds);
			t_sample delta_524 = __m_delta_74(phasor_528);
			t_sample abs_523 = fabs(delta_524);
			int gt_522 = (abs_523 > ((t_sample)0.9));
			__m_latch_75 = ((gt_522 != 0) ? m_history_2 : __m_latch_75);
			t_sample latch_516 = __m_latch_75;
			__m_latch_76 = ((gt_522 != 0) ? abs_521 : __m_latch_76);
			t_sample latch_525 = __m_latch_76;
			t_sample mix_598 = (latch_516 + (phasor_528 * (latch_525 - latch_516)));
			t_sample mix_518 = mix_598;
			t_sample mul_520 = (sample_nobufA_567 * mix_518);
			t_sample rsub_526 = (((int)1) - mix_518);
			t_sample mul_519 = (sample_nobufA_567 * rsub_526);
			t_sample history_517_next_529 = fixdenorm(mix_518);
			t_sample mul_371 = (mul_520 * clamp_374);
			t_sample mul_372 = (mul_519 * clamp_374);
			t_sample phasor_551 = __m_phasor_77(div_496, samples_to_seconds);
			t_sample wrap_550 = wrap(phasor_551, ((int)0), ((int)1));
			t_sample mul_547 = (wrap_550 * int_571);
			t_sample wrap_545 = wrap(mul_547, ((int)0), ((int)1));
			t_sample delta_543 = __m_delta_78(wrap_545);
			t_sample abs_542 = fabs(delta_543);
			int gt_541 = (abs_542 > ((t_sample)0.9));
			t_sample mul_538 = (mul_547 * ((t_sample)3.767));
			t_sample floor_536 = floor((mul_538 + mul_537));
			__m_latch_79 = ((gt_541 != 0) ? floor_536 : __m_latch_79);
			t_sample latch_539 = __m_latch_79;
			t_sample add_544 = (wrap_545 + latch_539);
			t_sample div_534 = safediv(add_544, int_571);
			t_sample wrap_533 = wrap(div_534, ((int)0), ((int)1));
			double sample_index_80 = (wrap_533 * (nobufB_dim - 1));
			int index_trunc_81 = fixnan(floor(sample_index_80));
			double index_fract_82 = (sample_index_80 - index_trunc_81);
			int index_trunc_83 = (index_trunc_81 + 1);
			bool index_ignore_84 = ((index_trunc_81 >= nobufB_dim) || (index_trunc_81 < 0));
			bool index_ignore_85 = ((index_trunc_83 >= nobufB_dim) || (index_trunc_83 < 0));
			// phase nobufB channel 1;
			double read_nobufB_86 = (index_ignore_84 ? 0 : m_nobufB_9.read(index_trunc_81, 0));
			double read_nobufB_87 = (index_ignore_85 ? 0 : m_nobufB_9.read(index_trunc_83, 0));
			double readinterp_88 = linear_interp(index_fract_82, read_nobufB_86, read_nobufB_87);
			t_sample sample_nobufB_548 = readinterp_88;
			t_sample index_nobufB_549 = sample_index_80;
			t_sample abs_502 = fabs(noise_540);
			t_sample phasor_509 = __m_phasor_89(scale_508, samples_to_seconds);
			t_sample delta_505 = __m_delta_90(phasor_509);
			t_sample abs_504 = fabs(delta_505);
			int gt_503 = (abs_504 > ((t_sample)0.9));
			__m_latch_91 = ((gt_503 != 0) ? m_history_1 : __m_latch_91);
			t_sample latch_497 = __m_latch_91;
			__m_latch_92 = ((gt_503 != 0) ? abs_502 : __m_latch_92);
			t_sample latch_506 = __m_latch_92;
			t_sample mix_603 = (latch_497 + (phasor_509 * (latch_506 - latch_497)));
			t_sample mix_499 = mix_603;
			t_sample mul_501 = (sample_nobufB_548 * mix_499);
			t_sample rsub_507 = (((int)1) - mix_499);
			t_sample mul_500 = (sample_nobufB_548 * rsub_507);
			t_sample history_498_next_510 = fixdenorm(mix_499);
			t_sample mul_368 = (mul_501 * clamp_374);
			t_sample OutLeft_515 = ((((mul_368 + mul_371) + mul_378) + gen_367) + sample_nobufC_341);
			t_sample out1 = OutLeft_515;
			t_sample mul_369 = (mul_500 * clamp_374);
			t_sample OutRight_514 = ((((mul_372 + mul_377) + gen_367) + sample_nobufC_341) + mul_369);
			t_sample out2 = OutRight_514;
			m_delay_6.write(plusequals_473);
			m_delay_5.write(plusequals_480);
			m_delay_4.write(plusequals_345);
			m_delay_3.write(in1);
			m_history_2 = history_517_next_529;
			m_history_1 = history_498_next_510;
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
	inline void set_nobufA(void * _value) {
		m_nobufA_7.setbuffer(_value);
	};
	inline void set_B(t_param _value) {
		m_B_8 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_nobufB(void * _value) {
		m_nobufB_9.setbuffer(_value);
	};
	inline void set_D(t_param _value) {
		m_D_10 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_C(t_param _value) {
		m_C_11 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_A(t_param _value) {
		m_A_12 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_ButtonA(t_param _value) {
		m_ButtonA_13 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ButtonB(t_param _value) {
		m_ButtonB_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_nobufC(void * _value) {
		m_nobufC_15.setbuffer(_value);
	};
	inline t_sample trapezoid_d_d_d_d_d(t_sample x, t_sample a, t_sample b, t_sample c, t_sample d) {
		t_sample _trapezoid_ret_364 = ((int)0);
		if ((x < a)) {
			_trapezoid_ret_364 = ((int)0);
			
		} else {
			if ((x < b)) {
				_trapezoid_ret_364 = safediv((x - a), (b - a));
				
			} else {
				if ((x < c)) {
					_trapezoid_ret_364 = ((int)1);
					
				} else {
					if ((x < d)) {
						_trapezoid_ret_364 = safediv((d - x), (d - c));
						
					} else {
						_trapezoid_ret_364 = ((int)0);
						
					};
					
				};
				
			};
			
		};
		return _trapezoid_ret_364;
		
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
		case 0: *value = self->m_A_12; break;
		case 1: *value = self->m_B_8; break;
		case 2: *value = self->m_ButtonA_13; break;
		case 3: *value = self->m_ButtonB_14; break;
		case 4: *value = self->m_C_11; break;
		case 5: *value = self->m_D_10; break;
		
		
		
		
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
	// initialize parameter 1 ("m_B_8")
	pi = self->__commonstate.params + 1;
	pi->name = "B";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_B_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ButtonA_13")
	pi = self->__commonstate.params + 2;
	pi->name = "ButtonA";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ButtonA_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_ButtonB_14")
	pi = self->__commonstate.params + 3;
	pi->name = "ButtonB";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ButtonB_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_C_11")
	pi = self->__commonstate.params + 4;
	pi->name = "C";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_C_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_D_10")
	pi = self->__commonstate.params + 5;
	pi->name = "D";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_D_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_nobufA_7")
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
	// initialize parameter 7 ("m_nobufB_9")
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
	// initialize parameter 8 ("m_nobufC_15")
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
