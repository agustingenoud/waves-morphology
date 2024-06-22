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
	Data m_nobufB_15;
	Data m_nobufA_9;
	Data m_nobufC_7;
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
	t_sample m_ButtonB_8;
	t_sample __m_latch_76;
	t_sample m_B_10;
	t_sample m_history_2;
	t_sample __m_latch_79;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample samples_to_seconds;
	t_sample __m_latch_63;
	t_sample m_C_12;
	t_sample __m_carry_27;
	t_sample __m_latch_91;
	t_sample __m_count_35;
	t_sample m_ButtonA_11;
	t_sample __m_count_25;
	t_sample __m_count_20;
	t_sample __m_carry_22;
	t_sample m_A_13;
	t_sample m_D_14;
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
		m_nobufC_7.reset("nobufC", ((int)48000), ((int)1));
		m_ButtonB_8 = ((int)0);
		m_nobufA_9.reset("nobufA", ((int)38400), ((int)1));
		m_B_10 = ((int)0);
		m_ButtonA_11 = ((int)0);
		m_C_12 = ((int)0);
		m_A_13 = ((int)0);
		m_D_14 = ((int)0);
		m_nobufB_15.reset("nobufB", ((int)33600), ((int)1));
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
		t_sample expr_756 = ((m_C_12 * ((int)2)) - ((int)1));
		int nobufB_dim = m_nobufB_15.dim;
		int nobufB_channels = m_nobufB_15.channels;
		int dim_659 = nobufB_dim;
		int nobufA_dim = m_nobufA_9.dim;
		int nobufA_channels = m_nobufA_9.channels;
		int dim_666 = nobufA_dim;
		int nobufC_dim = m_nobufC_7.dim;
		int nobufC_channels = m_nobufC_7.channels;
		int dim_531 = nobufC_dim;
		t_sample sub_760 = (m_D_14 - ((int)0));
		t_sample scale_757 = ((safepow((sub_760 * ((t_sample)1)), ((int)1)) * ((t_sample)1.25)) + ((int)0));
		t_sample sub_542 = (scale_757 - ((t_sample)0.25));
		samples_to_seconds = (1 / samplerate);
		t_sample paramA_696 = m_A_13;
		t_sample paramA_715 = paramA_696;
		t_sample sub_764 = (m_A_13 - ((int)0));
		t_sample scale_761 = ((safepow((sub_764 * ((t_sample)20)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample clamp_557 = ((scale_761 <= ((int)0)) ? ((int)0) : ((scale_761 >= ((int)1)) ? ((int)1) : scale_761));
		t_sample sub_768 = (m_B_10 - ((int)0));
		t_sample scale_765 = ((safepow((sub_768 * ((t_sample)1)), ((int)1)) * ((int)2)) + ((int)0));
		t_sample mstosamps_636 = (((int)256) * (samplerate * 0.001));
		t_sample mul_572 = (mstosamps_636 * ((t_sample)0.2));
		t_sample rsub_622 = (((int)1) - scale_765);
		t_sample mul_621 = (rsub_622 * ((int)1000));
		t_sample div_620 = (mul_621 * ((t_sample)0.00390625));
		t_sample sub_772 = (scale_765 - ((int)0));
		t_sample scale_769 = ((safepow((sub_772 * ((t_sample)10)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample clamp_562 = ((scale_769 <= ((int)0)) ? ((int)0) : ((scale_769 >= ((int)1)) ? ((int)1) : scale_769));
		t_sample sub_776 = (m_A_13 - ((t_sample)0.0001));
		t_sample scale_773 = ((safepow((sub_776 * ((t_sample)1.000200040008)), ((int)1)) * ((int)8)) + ((int)1));
		int int_754 = int(scale_773);
		int dim_673 = nobufA_dim;
		t_sample div_674 = safediv(samplerate, dim_673);
		t_sample sub_780 = (paramA_715 - ((int)0));
		t_sample scale_777 = ((safepow((sub_780 * ((t_sample)1)), ((int)1)) * ((t_sample)5.8)) + ((t_sample)0.2));
		t_sample scale_710 = scale_777;
		int dim_672 = nobufB_dim;
		t_sample div_679 = safediv(samplerate, dim_672);
		t_sample sub_785 = (paramA_696 - ((int)0));
		t_sample scale_782 = ((safepow((sub_785 * ((t_sample)1)), ((int)1)) * ((t_sample)5.8)) + ((t_sample)0.2));
		t_sample scale_691 = scale_782;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample tap_658 = m_delay_6.read_step(dim_659);
			t_sample tap_665 = m_delay_5.read_step(dim_666);
			t_sample delta_655 = __m_delta_16(m_ButtonA_11);
			t_sample gtp_654 = ((delta_655 > ((int)0)) ? delta_655 : 0);
			t_sample plusequals_653 = __m_pluseq_17.post(gtp_654, ((int)0), 0);
			t_sample mod_652 = safemod(plusequals_653, ((int)2));
			t_sample add_649 = (mod_652 + ((int)1));
			t_sample choice_18 = int(add_649);
			t_sample gate_650 = (((choice_18 >= 1) && (choice_18 < 2)) ? gtp_654 : 0);
			t_sample gate_651 = ((choice_18 >= 2) ? gtp_654 : 0);
			t_sample plusequals_656 = __m_pluseq_19.post(gate_651, tap_658, 0);
			__m_count_20 = (gate_651 ? 0 : (fixdenorm(__m_count_20 + plusequals_656)));
			int carry_21 = 0;
			if ((gate_651 != 0)) {
				__m_count_20 = 0;
				__m_carry_22 = 0;
				
			} else if (((dim_659 > 0) && (__m_count_20 >= dim_659))) {
				int wraps_23 = (__m_count_20 / dim_659);
				__m_carry_22 = (__m_carry_22 + wraps_23);
				__m_count_20 = (__m_count_20 - (wraps_23 * dim_659));
				carry_21 = 1;
				
			};
			t_sample counter_660 = __m_count_20;
			int counter_661 = carry_21;
			int counter_662 = __m_carry_22;
			t_sample plusequals_663 = __m_pluseq_24.post(gate_650, tap_665, 0);
			__m_count_25 = (gate_650 ? 0 : (fixdenorm(__m_count_25 + plusequals_663)));
			int carry_26 = 0;
			if ((gate_650 != 0)) {
				__m_count_25 = 0;
				__m_carry_27 = 0;
				
			} else if (((dim_666 > 0) && (__m_count_25 >= dim_666))) {
				int wraps_28 = (__m_count_25 / dim_666);
				__m_carry_27 = (__m_carry_27 + wraps_28);
				__m_count_25 = (__m_count_25 - (wraps_28 * dim_666));
				carry_26 = 1;
				
			};
			t_sample counter_667 = __m_count_25;
			int counter_668 = carry_26;
			int counter_669 = __m_carry_27;
			int index_trunc_29 = fixnan(floor(counter_667));
			int index_wrap_30 = ((index_trunc_29 < 0) ? ((nobufA_dim - 1) + ((index_trunc_29 + 1) % nobufA_dim)) : (index_trunc_29 % nobufA_dim));
			m_nobufA_9.write(in1, index_wrap_30, 0);
			int index_trunc_31 = fixnan(floor(counter_660));
			int index_wrap_32 = ((index_trunc_31 < 0) ? ((nobufB_dim - 1) + ((index_trunc_31 + 1) % nobufB_dim)) : (index_trunc_31 % nobufB_dim));
			m_nobufB_15.write(in1, index_wrap_32, 0);
			t_sample tap_530 = m_delay_4.read_step(dim_531);
			t_sample delta_536 = __m_delta_33(m_ButtonB_8);
			t_sample gtp_535 = ((delta_536 > ((int)0)) ? delta_536 : 0);
			t_sample plusequals_528 = __m_pluseq_34.post(gtp_535, tap_530, 0);
			__m_count_35 = (gtp_535 ? 0 : (fixdenorm(__m_count_35 + plusequals_528)));
			int carry_36 = 0;
			if ((gtp_535 != 0)) {
				__m_count_35 = 0;
				__m_carry_37 = 0;
				
			} else if (((dim_531 > 0) && (__m_count_35 >= dim_531))) {
				int wraps_38 = (__m_count_35 / dim_531);
				__m_carry_37 = (__m_carry_37 + wraps_38);
				__m_count_35 = (__m_count_35 - (wraps_38 * dim_531));
				carry_36 = 1;
				
			};
			t_sample counter_532 = __m_count_35;
			int counter_533 = carry_36;
			int counter_534 = __m_carry_37;
			int index_trunc_39 = fixnan(floor(counter_532));
			int index_wrap_40 = ((index_trunc_39 < 0) ? ((nobufC_dim - 1) + ((index_trunc_39 + 1) % nobufC_dim)) : (index_trunc_39 % nobufC_dim));
			m_nobufC_7.write(in1, index_wrap_40, 0);
			t_sample expr_548 = trapezoid_d_d_d_d_d(scale_757, ((t_sample)0.3), ((t_sample)0.4), ((t_sample)0.7), ((t_sample)0.8));
			t_sample expr_549 = trapezoid_d_d_d_d_d(sub_542, ((t_sample)0.3), ((t_sample)0.4), ((t_sample)0.7), ((t_sample)0.8));
			t_sample mul_546 = (in1 * expr_548);
			t_sample mul_540 = (in2 * expr_549);
			t_sample gen_550 = (mul_540 + mul_546);
			t_sample phasor_527 = __m_phasor_41(expr_756, samples_to_seconds);
			t_sample wrap_526 = wrap(phasor_527, ((int)0), ((int)1));
			double sample_index_42 = (wrap_526 * (nobufC_dim - 1));
			int index_trunc_43 = fixnan(floor(sample_index_42));
			double index_fract_44 = (sample_index_42 - index_trunc_43);
			int index_trunc_45 = (index_trunc_43 + 1);
			bool index_ignore_46 = ((index_trunc_43 >= nobufC_dim) || (index_trunc_43 < 0));
			bool index_ignore_47 = ((index_trunc_45 >= nobufC_dim) || (index_trunc_45 < 0));
			// phase nobufC channel 1;
			double read_nobufC_48 = (index_ignore_46 ? 0 : m_nobufC_7.read(index_trunc_43, 0));
			double read_nobufC_49 = (index_ignore_47 ? 0 : m_nobufC_7.read(index_trunc_45, 0));
			double readinterp_50 = linear_interp(index_fract_44, read_nobufC_48, read_nobufC_49);
			t_sample sample_nobufC_524 = readinterp_50;
			t_sample index_nobufC_525 = sample_index_42;
			t_sample noise_742 = noise();
			t_sample noise_723 = noise();
			t_sample noise_584 = noise();
			t_sample abs_599 = fabs(noise_584);
			t_sample mul_598 = (abs_599 * ((t_sample)0.25));
			t_sample add_576 = (mul_598 + ((int)1));
			t_sample mul_638 = (add_576 * mstosamps_636);
			t_sample noise_583 = noise();
			t_sample abs_595 = fabs(noise_583);
			t_sample mul_594 = (abs_595 * ((t_sample)0.25));
			t_sample add_575 = (mul_594 + ((int)3));
			t_sample mul_630 = (add_575 * mul_572);
			t_sample noise_582 = noise();
			t_sample abs_591 = fabs(noise_582);
			t_sample mul_590 = (abs_591 * ((t_sample)0.25));
			t_sample add_574 = (mul_590 + ((t_sample)1.7));
			t_sample mul_614 = (add_574 * mstosamps_636);
			t_sample noise_581 = noise();
			t_sample abs_587 = fabs(noise_581);
			t_sample mul_586 = (abs_587 * ((t_sample)0.25));
			t_sample add_573 = (mul_586 + ((t_sample)2.37));
			t_sample mul_607 = (add_573 * mstosamps_636);
			t_sample phasor_644 = __m_phasor_51(div_620, samples_to_seconds);
			t_sample add_643 = (phasor_644 + ((int)0));
			t_sample mod_642 = safemod(add_643, ((int)1));
			t_sample delta_601 = __m_delta_52(mod_642);
			t_sample sah_600 = __m_sah_53(mul_638, delta_601, ((int)0));
			t_sample mul_580 = (sah_600 * mod_642);
			t_sample sub_641 = (mod_642 - ((t_sample)0.5));
			t_sample mul_640 = (sub_641 * ((t_sample)3.1415926535898));
			t_sample cos_639 = cos(mul_640);
			t_sample mul_605 = (cos_639 * cos_639);
			t_sample add_635 = (phasor_644 + ((t_sample)0.25));
			t_sample mod_634 = safemod(add_635, ((int)1));
			t_sample delta_597 = __m_delta_54(mod_634);
			t_sample sah_596 = __m_sah_55(mul_630, delta_597, ((int)0));
			t_sample mul_579 = (sah_596 * mod_634);
			t_sample sub_633 = (mod_634 - ((t_sample)0.5));
			t_sample mul_632 = (sub_633 * ((t_sample)3.1415926535898));
			t_sample cos_631 = cos(mul_632);
			t_sample mul_604 = (cos_631 * cos_631);
			t_sample add_619 = (phasor_644 + ((t_sample)0.5));
			t_sample mod_618 = safemod(add_619, ((int)1));
			t_sample delta_593 = __m_delta_56(mod_618);
			t_sample sah_592 = __m_sah_57(mul_614, delta_593, ((int)0));
			t_sample mul_578 = (sah_592 * mod_618);
			t_sample sub_617 = (mod_618 - ((t_sample)0.5));
			t_sample mul_616 = (sub_617 * ((t_sample)3.1415926535898));
			t_sample cos_615 = cos(mul_616);
			t_sample mul_603 = (cos_615 * cos_615);
			t_sample add_612 = (phasor_644 + ((t_sample)0.75));
			t_sample mod_611 = safemod(add_612, ((int)1));
			t_sample delta_589 = __m_delta_58(mod_611);
			t_sample sah_588 = __m_sah_59(mul_607, delta_589, ((int)0));
			t_sample mul_577 = (sah_588 * mod_611);
			t_sample tap_626 = m_delay_3.read_linear(mul_580);
			t_sample tap_627 = m_delay_3.read_linear(mul_579);
			t_sample tap_628 = m_delay_3.read_linear(mul_578);
			t_sample tap_629 = m_delay_3.read_linear(mul_577);
			t_sample mul_623 = (tap_627 * mul_604);
			t_sample mul_624 = (tap_626 * mul_605);
			t_sample mul_613 = (tap_628 * mul_603);
			t_sample gen_645 = (mul_613 + mul_624);
			t_sample sub_610 = (mod_611 - ((t_sample)0.5));
			t_sample mul_609 = (sub_610 * ((t_sample)3.1415926535898));
			t_sample cos_608 = cos(mul_609);
			t_sample mul_602 = (cos_608 * cos_608);
			t_sample mul_606 = (tap_629 * mul_602);
			t_sample gen_646 = (mul_606 + mul_623);
			t_sample mul_570 = (gen_645 * ((t_sample)0.666));
			t_sample mul_569 = (gen_646 * ((t_sample)0.666));
			t_sample phasor_568 = __m_phasor_60(((int)22), samples_to_seconds);
			t_sample triangle_566 = triangle(phasor_568, ((t_sample)0.5));
			t_sample mul_565 = (mul_570 * triangle_566);
			t_sample mul_561 = (mul_565 * clamp_562);
			t_sample mul_564 = (mul_569 * triangle_566);
			t_sample mul_560 = (mul_564 * clamp_562);
			t_sample mul_739 = (noise_742 * m_A_13);
			t_sample mul_720 = (noise_723 * m_A_13);
			t_sample phasor_753 = __m_phasor_61(div_674, samples_to_seconds);
			t_sample wrap_752 = wrap(phasor_753, ((int)0), ((int)1));
			t_sample mul_749 = (wrap_752 * int_754);
			t_sample wrap_747 = wrap(mul_749, ((int)0), ((int)1));
			t_sample delta_745 = __m_delta_62(wrap_747);
			t_sample abs_744 = fabs(delta_745);
			int gt_743 = (abs_744 > ((t_sample)0.9));
			t_sample mul_740 = (mul_749 * ((t_sample)3.767));
			t_sample floor_738 = floor((mul_739 + mul_740));
			__m_latch_63 = ((gt_743 != 0) ? floor_738 : __m_latch_63);
			t_sample latch_741 = __m_latch_63;
			t_sample add_746 = (wrap_747 + latch_741);
			t_sample div_736 = safediv(add_746, int_754);
			t_sample wrap_735 = wrap(div_736, ((int)0), ((int)1));
			double sample_index_64 = (wrap_735 * (nobufA_dim - 1));
			int index_trunc_65 = fixnan(floor(sample_index_64));
			double index_fract_66 = (sample_index_64 - index_trunc_65);
			int index_trunc_67 = (index_trunc_65 + 1);
			bool index_ignore_68 = ((index_trunc_65 >= nobufA_dim) || (index_trunc_65 < 0));
			bool index_ignore_69 = ((index_trunc_67 >= nobufA_dim) || (index_trunc_67 < 0));
			// phase nobufA channel 1;
			double read_nobufA_70 = (index_ignore_68 ? 0 : m_nobufA_9.read(index_trunc_65, 0));
			double read_nobufA_71 = (index_ignore_69 ? 0 : m_nobufA_9.read(index_trunc_67, 0));
			double readinterp_72 = linear_interp(index_fract_66, read_nobufA_70, read_nobufA_71);
			t_sample sample_nobufA_750 = readinterp_72;
			t_sample index_nobufA_751 = sample_index_64;
			t_sample abs_704 = fabs(noise_742);
			t_sample phasor_711 = __m_phasor_73(scale_710, samples_to_seconds);
			t_sample delta_707 = __m_delta_74(phasor_711);
			t_sample abs_706 = fabs(delta_707);
			int gt_705 = (abs_706 > ((t_sample)0.9));
			__m_latch_75 = ((gt_705 != 0) ? m_history_2 : __m_latch_75);
			t_sample latch_699 = __m_latch_75;
			__m_latch_76 = ((gt_705 != 0) ? abs_704 : __m_latch_76);
			t_sample latch_708 = __m_latch_76;
			t_sample mix_781 = (latch_699 + (phasor_711 * (latch_708 - latch_699)));
			t_sample mix_701 = mix_781;
			t_sample mul_703 = (sample_nobufA_750 * mix_701);
			t_sample rsub_709 = (((int)1) - mix_701);
			t_sample mul_702 = (sample_nobufA_750 * rsub_709);
			t_sample history_700_next_712 = fixdenorm(mix_701);
			t_sample mul_554 = (mul_703 * clamp_557);
			t_sample mul_555 = (mul_702 * clamp_557);
			t_sample phasor_734 = __m_phasor_77(div_679, samples_to_seconds);
			t_sample wrap_733 = wrap(phasor_734, ((int)0), ((int)1));
			t_sample mul_730 = (wrap_733 * int_754);
			t_sample wrap_728 = wrap(mul_730, ((int)0), ((int)1));
			t_sample delta_726 = __m_delta_78(wrap_728);
			t_sample abs_725 = fabs(delta_726);
			int gt_724 = (abs_725 > ((t_sample)0.9));
			t_sample mul_721 = (mul_730 * ((t_sample)3.767));
			t_sample floor_719 = floor((mul_721 + mul_720));
			__m_latch_79 = ((gt_724 != 0) ? floor_719 : __m_latch_79);
			t_sample latch_722 = __m_latch_79;
			t_sample add_727 = (wrap_728 + latch_722);
			t_sample div_717 = safediv(add_727, int_754);
			t_sample wrap_716 = wrap(div_717, ((int)0), ((int)1));
			double sample_index_80 = (wrap_716 * (nobufB_dim - 1));
			int index_trunc_81 = fixnan(floor(sample_index_80));
			double index_fract_82 = (sample_index_80 - index_trunc_81);
			int index_trunc_83 = (index_trunc_81 + 1);
			bool index_ignore_84 = ((index_trunc_81 >= nobufB_dim) || (index_trunc_81 < 0));
			bool index_ignore_85 = ((index_trunc_83 >= nobufB_dim) || (index_trunc_83 < 0));
			// phase nobufB channel 1;
			double read_nobufB_86 = (index_ignore_84 ? 0 : m_nobufB_15.read(index_trunc_81, 0));
			double read_nobufB_87 = (index_ignore_85 ? 0 : m_nobufB_15.read(index_trunc_83, 0));
			double readinterp_88 = linear_interp(index_fract_82, read_nobufB_86, read_nobufB_87);
			t_sample sample_nobufB_731 = readinterp_88;
			t_sample index_nobufB_732 = sample_index_80;
			t_sample abs_685 = fabs(noise_723);
			t_sample phasor_692 = __m_phasor_89(scale_691, samples_to_seconds);
			t_sample delta_688 = __m_delta_90(phasor_692);
			t_sample abs_687 = fabs(delta_688);
			int gt_686 = (abs_687 > ((t_sample)0.9));
			__m_latch_91 = ((gt_686 != 0) ? m_history_1 : __m_latch_91);
			t_sample latch_680 = __m_latch_91;
			__m_latch_92 = ((gt_686 != 0) ? abs_685 : __m_latch_92);
			t_sample latch_689 = __m_latch_92;
			t_sample mix_786 = (latch_680 + (phasor_692 * (latch_689 - latch_680)));
			t_sample mix_682 = mix_786;
			t_sample mul_684 = (sample_nobufB_731 * mix_682);
			t_sample rsub_690 = (((int)1) - mix_682);
			t_sample mul_683 = (sample_nobufB_731 * rsub_690);
			t_sample history_681_next_693 = fixdenorm(mix_682);
			t_sample mul_551 = (mul_684 * clamp_557);
			t_sample OutLeft_698 = ((((mul_551 + mul_554) + mul_561) + gen_550) + sample_nobufC_524);
			t_sample out1 = OutLeft_698;
			t_sample mul_552 = (mul_683 * clamp_557);
			t_sample OutRight_697 = ((((mul_555 + mul_560) + gen_550) + sample_nobufC_524) + mul_552);
			t_sample out2 = OutRight_697;
			m_delay_6.write(plusequals_656);
			m_delay_5.write(plusequals_663);
			m_delay_4.write(plusequals_528);
			m_delay_3.write(in1);
			m_history_2 = history_700_next_712;
			m_history_1 = history_681_next_693;
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
	inline void set_nobufC(void * _value) {
		m_nobufC_7.setbuffer(_value);
	};
	inline void set_ButtonB(t_param _value) {
		m_ButtonB_8 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_nobufA(void * _value) {
		m_nobufA_9.setbuffer(_value);
	};
	inline void set_B(t_param _value) {
		m_B_10 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_ButtonA(t_param _value) {
		m_ButtonA_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_C(t_param _value) {
		m_C_12 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_A(t_param _value) {
		m_A_13 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_D(t_param _value) {
		m_D_14 = (_value < 0.0001 ? 0.0001 : (_value > 0.9999 ? 0.9999 : _value));
	};
	inline void set_nobufB(void * _value) {
		m_nobufB_15.setbuffer(_value);
	};
	inline t_sample trapezoid_d_d_d_d_d(t_sample x, t_sample a, t_sample b, t_sample c, t_sample d) {
		t_sample _trapezoid_ret_547 = ((int)0);
		if ((x < a)) {
			_trapezoid_ret_547 = ((int)0);
			
		} else {
			if ((x < b)) {
				_trapezoid_ret_547 = safediv((x - a), (b - a));
				
			} else {
				if ((x < c)) {
					_trapezoid_ret_547 = ((int)1);
					
				} else {
					if ((x < d)) {
						_trapezoid_ret_547 = safediv((d - x), (d - c));
						
					} else {
						_trapezoid_ret_547 = ((int)0);
						
					};
					
				};
				
			};
			
		};
		return _trapezoid_ret_547;
		
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
		case 0: *value = self->m_A_13; break;
		case 1: *value = self->m_B_10; break;
		case 2: *value = self->m_ButtonA_11; break;
		case 3: *value = self->m_ButtonB_8; break;
		case 4: *value = self->m_C_12; break;
		case 5: *value = self->m_D_14; break;
		
		
		
		
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
	// initialize parameter 0 ("m_A_13")
	pi = self->__commonstate.params + 0;
	pi->name = "A";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_A_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_B_10")
	pi = self->__commonstate.params + 1;
	pi->name = "B";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_B_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ButtonA_11")
	pi = self->__commonstate.params + 2;
	pi->name = "ButtonA";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ButtonA_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_ButtonB_8")
	pi = self->__commonstate.params + 3;
	pi->name = "ButtonB";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ButtonB_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_C_12")
	pi = self->__commonstate.params + 4;
	pi->name = "C";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_C_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_D_14")
	pi = self->__commonstate.params + 5;
	pi->name = "D";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_D_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.0001;
	pi->outputmax = 0.9999;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_nobufA_9")
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
	// initialize parameter 8 ("m_nobufC_7")
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
