/******************************************************************************
/****************************************************************************** 
*
* Copyright (C) 2015 Xilinx, Inc.  All rights reserved.
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy 
* of this software and associated documentation files (the "Software"), to deal 
* in the Software without restriction, including without limitation the rights 
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
* copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions: 
* 
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software. 
* 
* Use of the Software is limited solely to applications: 
* (a) running on a Xilinx device, or 
* (b) that interact with a Xilinx device through a bus or interconnect. 
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
* XILINX CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
* SOFTWARE.
* 
* Except as contained in this notice, the name of the Xilinx shall not be used 
* in advertising or otherwise to promote the sale, use or other dealings in 
* this Software without prior written authorization from Xilinx. 
* 
******************************************************************************/ 

#include "psu_init_gpl.h"

static unsigned int RegMask = 0x0;

static unsigned int RegVal = 0x0;

unsigned long psu_pll_init_data() {
		// : RPLL INIT
		// : UPDATE FB_DIV
		/*Register : RPLL_CTRL @ 0XFF5E0030</p>

		The integer portion of the feedback divider to the PLL
		PSU_CRL_APB_RPLL_CTRL_FBDIV                                                     0x30

		This turns on the divide by 2 that is inside of the PLL. This does not change the VCO frequency, just the output frequency
		PSU_CRL_APB_RPLL_CTRL_DIV2                                                      0x1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFF5E0030, 0x00017F00U ,0x00013000U)  */
		RegMask = (CRL_APB_RPLL_CTRL_FBDIV_MASK | CRL_APB_RPLL_CTRL_DIV2_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000030U << CRL_APB_RPLL_CTRL_FBDIV_SHIFT
			| 0x00000001U << CRL_APB_RPLL_CTRL_DIV2_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : BY PASS PLL
		/*Register : RPLL_CTRL @ 0XFF5E0030</p>

		Bypasses the PLL clock. The usable clock will be determined from the POST_SRC field. (This signal may only be toggled after 4
		cycles of the old clock and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_RPLL_CTRL_BYPASS                                                    1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFF5E0030, 0x00000008U ,0x00000008U)  */
		RegMask = (CRL_APB_RPLL_CTRL_BYPASS_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_RPLL_CTRL_BYPASS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : ASSERT RESET
		/*Register : RPLL_CTRL @ 0XFF5E0030</p>

		Asserts Reset to the PLL
		PSU_CRL_APB_RPLL_CTRL_RESET                                                     1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFF5E0030, 0x00000001U ,0x00000001U)  */
		RegMask = (CRL_APB_RPLL_CTRL_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_RPLL_CTRL_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : DEASSERT RESET
		/*Register : RPLL_CTRL @ 0XFF5E0030</p>

		Asserts Reset to the PLL
		PSU_CRL_APB_RPLL_CTRL_RESET                                                     0

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFF5E0030, 0x00000001U ,0x00000000U)  */
		RegMask = (CRL_APB_RPLL_CTRL_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RPLL_CTRL_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : CHECK PLL STATUS
		/*Register : PLL_STATUS @ 0XFF5E0040</p>

		RPLL is locked
		PSU_CRL_APB_PLL_STATUS_RPLL_LOCK                                                1
		(OFFSET, MASK, VALUE)      (0XFF5E0040, 0x00000002U ,0x00000002U)  */
		while(!(Xil_In32 ( CRL_APB_PLL_STATUS_OFFSET) & 0x00000002U));

	/*############################################################################################################################ */

		// : REMOVE PLL BY PASS
		/*Register : RPLL_CTRL @ 0XFF5E0030</p>

		Bypasses the PLL clock. The usable clock will be determined from the POST_SRC field. (This signal may only be toggled after 4
		cycles of the old clock and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_RPLL_CTRL_BYPASS                                                    0

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFF5E0030, 0x00000008U ,0x00000000U)  */
		RegMask = (CRL_APB_RPLL_CTRL_BYPASS_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RPLL_CTRL_BYPASS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : RPLL_TO_FPD_CTRL @ 0XFF5E0048</p>

		Divisor value for this clock.
		PSU_CRL_APB_RPLL_TO_FPD_CTRL_DIVISOR0                                           0x3

		Control for a clock that will be generated in the LPD, but used in the FPD as a clock source for the peripheral clock muxes.
		(OFFSET, MASK, VALUE)      (0XFF5E0048, 0x00003F00U ,0x00000300U)  */
		RegMask = (CRL_APB_RPLL_TO_FPD_CTRL_DIVISOR0_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RPLL_TO_FPD_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000003U << CRL_APB_RPLL_TO_FPD_CTRL_DIVISOR0_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RPLL_TO_FPD_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : RPLL FRAC CFG
		// : IOPLL INIT
		// : UPDATE FB_DIV
		/*Register : IOPLL_CTRL @ 0XFF5E0020</p>

		The integer portion of the feedback divider to the PLL
		PSU_CRL_APB_IOPLL_CTRL_FBDIV                                                    0x3c

		This turns on the divide by 2 that is inside of the PLL. This does not change the VCO frequency, just the output frequency
		PSU_CRL_APB_IOPLL_CTRL_DIV2                                                     0x1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFF5E0020, 0x00017F00U ,0x00013C00U)  */
		RegMask = (CRL_APB_IOPLL_CTRL_FBDIV_MASK | CRL_APB_IOPLL_CTRL_DIV2_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_IOPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x0000003CU << CRL_APB_IOPLL_CTRL_FBDIV_SHIFT
			| 0x00000001U << CRL_APB_IOPLL_CTRL_DIV2_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_IOPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : BY PASS PLL
		/*Register : IOPLL_CTRL @ 0XFF5E0020</p>

		Bypasses the PLL clock. The usable clock will be determined from the POST_SRC field. (This signal may only be toggled after 4
		cycles of the old clock and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_IOPLL_CTRL_BYPASS                                                   1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFF5E0020, 0x00000008U ,0x00000008U)  */
		RegMask = (CRL_APB_IOPLL_CTRL_BYPASS_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_IOPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_IOPLL_CTRL_BYPASS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_IOPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : ASSERT RESET
		/*Register : IOPLL_CTRL @ 0XFF5E0020</p>

		Asserts Reset to the PLL
		PSU_CRL_APB_IOPLL_CTRL_RESET                                                    1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFF5E0020, 0x00000001U ,0x00000001U)  */
		RegMask = (CRL_APB_IOPLL_CTRL_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_IOPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_IOPLL_CTRL_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_IOPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : DEASSERT RESET
		/*Register : IOPLL_CTRL @ 0XFF5E0020</p>

		Asserts Reset to the PLL
		PSU_CRL_APB_IOPLL_CTRL_RESET                                                    0

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFF5E0020, 0x00000001U ,0x00000000U)  */
		RegMask = (CRL_APB_IOPLL_CTRL_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_IOPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_IOPLL_CTRL_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_IOPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : CHECK PLL STATUS
		/*Register : PLL_STATUS @ 0XFF5E0040</p>

		IOPLL is locked
		PSU_CRL_APB_PLL_STATUS_IOPLL_LOCK                                               1
		(OFFSET, MASK, VALUE)      (0XFF5E0040, 0x00000001U ,0x00000001U)  */
		while(!(Xil_In32 ( CRL_APB_PLL_STATUS_OFFSET) & 0x00000001U));

	/*############################################################################################################################ */

		// : REMOVE PLL BY PASS
		/*Register : IOPLL_CTRL @ 0XFF5E0020</p>

		Bypasses the PLL clock. The usable clock will be determined from the POST_SRC field. (This signal may only be toggled after 4
		cycles of the old clock and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_IOPLL_CTRL_BYPASS                                                   0

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFF5E0020, 0x00000008U ,0x00000000U)  */
		RegMask = (CRL_APB_IOPLL_CTRL_BYPASS_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_IOPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_IOPLL_CTRL_BYPASS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_IOPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : IOPLL_TO_FPD_CTRL @ 0XFF5E0044</p>

		Divisor value for this clock.
		PSU_CRL_APB_IOPLL_TO_FPD_CTRL_DIVISOR0                                          0x4

		Control for a clock that will be generated in the LPD, but used in the FPD as a clock source for the peripheral clock muxes.
		(OFFSET, MASK, VALUE)      (0XFF5E0044, 0x00003F00U ,0x00000400U)  */
		RegMask = (CRL_APB_IOPLL_TO_FPD_CTRL_DIVISOR0_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_IOPLL_TO_FPD_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000004U << CRL_APB_IOPLL_TO_FPD_CTRL_DIVISOR0_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_IOPLL_TO_FPD_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : IOPLL FRAC CFG
		// : APU_PLL INIT
		// : UPDATE FB_DIV
		/*Register : APLL_CTRL @ 0XFD1A0020</p>

		The integer portion of the feedback divider to the PLL
		PSU_CRF_APB_APLL_CTRL_FBDIV                                                     0x3c

		This turns on the divide by 2 that is inside of the PLL. This does not change the VCO frequency, just the output frequency
		PSU_CRF_APB_APLL_CTRL_DIV2                                                      0x1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A0020, 0x00017F00U ,0x00013C00U)  */
		RegMask = (CRF_APB_APLL_CTRL_FBDIV_MASK | CRF_APB_APLL_CTRL_DIV2_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_APLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x0000003CU << CRF_APB_APLL_CTRL_FBDIV_SHIFT
			| 0x00000001U << CRF_APB_APLL_CTRL_DIV2_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_APLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : BY PASS PLL
		/*Register : APLL_CTRL @ 0XFD1A0020</p>

		Bypasses the PLL clock. The usable clock will be determined from the POST_SRC field. (This signal may only be toggled after 4
		cycles of the old clock and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_APLL_CTRL_BYPASS                                                    1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A0020, 0x00000008U ,0x00000008U)  */
		RegMask = (CRF_APB_APLL_CTRL_BYPASS_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_APLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRF_APB_APLL_CTRL_BYPASS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_APLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : ASSERT RESET
		/*Register : APLL_CTRL @ 0XFD1A0020</p>

		Asserts Reset to the PLL
		PSU_CRF_APB_APLL_CTRL_RESET                                                     1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A0020, 0x00000001U ,0x00000001U)  */
		RegMask = (CRF_APB_APLL_CTRL_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_APLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRF_APB_APLL_CTRL_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_APLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : DEASSERT RESET
		/*Register : APLL_CTRL @ 0XFD1A0020</p>

		Asserts Reset to the PLL
		PSU_CRF_APB_APLL_CTRL_RESET                                                     0

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A0020, 0x00000001U ,0x00000000U)  */
		RegMask = (CRF_APB_APLL_CTRL_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_APLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRF_APB_APLL_CTRL_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_APLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : CHECK PLL STATUS
		/*Register : PLL_STATUS @ 0XFD1A0044</p>

		APLL is locked
		PSU_CRF_APB_PLL_STATUS_APLL_LOCK                                                1
		(OFFSET, MASK, VALUE)      (0XFD1A0044, 0x00000001U ,0x00000001U)  */
		while(!(Xil_In32 ( CRF_APB_PLL_STATUS_OFFSET) & 0x00000001U));

	/*############################################################################################################################ */

		// : REMOVE PLL BY PASS
		/*Register : APLL_CTRL @ 0XFD1A0020</p>

		Bypasses the PLL clock. The usable clock will be determined from the POST_SRC field. (This signal may only be toggled after 4
		cycles of the old clock and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_APLL_CTRL_BYPASS                                                    0

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A0020, 0x00000008U ,0x00000000U)  */
		RegMask = (CRF_APB_APLL_CTRL_BYPASS_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_APLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRF_APB_APLL_CTRL_BYPASS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_APLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : APLL_TO_LPD_CTRL @ 0XFD1A0048</p>

		Divisor value for this clock.
		PSU_CRF_APB_APLL_TO_LPD_CTRL_DIVISOR0                                           0x4

		Control for a clock that will be generated in the LPD, but used in the FPD as a clock source for the peripheral clock muxes.
		(OFFSET, MASK, VALUE)      (0XFD1A0048, 0x00003F00U ,0x00000400U)  */
		RegMask = (CRF_APB_APLL_TO_LPD_CTRL_DIVISOR0_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_APLL_TO_LPD_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000004U << CRF_APB_APLL_TO_LPD_CTRL_DIVISOR0_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_APLL_TO_LPD_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : APLL FRAC CFG
		// : DDR_PLL INIT
		// : UPDATE FB_DIV
		/*Register : DPLL_CTRL @ 0XFD1A002C</p>

		The integer portion of the feedback divider to the PLL
		PSU_CRF_APB_DPLL_CTRL_FBDIV                                                     0x3c

		This turns on the divide by 2 that is inside of the PLL. This does not change the VCO frequency, just the output frequency
		PSU_CRF_APB_DPLL_CTRL_DIV2                                                      0x1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A002C, 0x00017F00U ,0x00013C00U)  */
		RegMask = (CRF_APB_DPLL_CTRL_FBDIV_MASK | CRF_APB_DPLL_CTRL_DIV2_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x0000003CU << CRF_APB_DPLL_CTRL_FBDIV_SHIFT
			| 0x00000001U << CRF_APB_DPLL_CTRL_DIV2_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : BY PASS PLL
		/*Register : DPLL_CTRL @ 0XFD1A002C</p>

		Bypasses the PLL clock. The usable clock will be determined from the POST_SRC field. (This signal may only be toggled after 4
		cycles of the old clock and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_DPLL_CTRL_BYPASS                                                    1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A002C, 0x00000008U ,0x00000008U)  */
		RegMask = (CRF_APB_DPLL_CTRL_BYPASS_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRF_APB_DPLL_CTRL_BYPASS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : ASSERT RESET
		/*Register : DPLL_CTRL @ 0XFD1A002C</p>

		Asserts Reset to the PLL
		PSU_CRF_APB_DPLL_CTRL_RESET                                                     1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A002C, 0x00000001U ,0x00000001U)  */
		RegMask = (CRF_APB_DPLL_CTRL_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRF_APB_DPLL_CTRL_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : DEASSERT RESET
		/*Register : DPLL_CTRL @ 0XFD1A002C</p>

		Asserts Reset to the PLL
		PSU_CRF_APB_DPLL_CTRL_RESET                                                     0

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A002C, 0x00000001U ,0x00000000U)  */
		RegMask = (CRF_APB_DPLL_CTRL_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRF_APB_DPLL_CTRL_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : CHECK PLL STATUS
		/*Register : PLL_STATUS @ 0XFD1A0044</p>

		DPLL is locked
		PSU_CRF_APB_PLL_STATUS_DPLL_LOCK                                                1
		(OFFSET, MASK, VALUE)      (0XFD1A0044, 0x00000002U ,0x00000002U)  */
		while(!(Xil_In32 ( CRF_APB_PLL_STATUS_OFFSET) & 0x00000002U));

	/*############################################################################################################################ */

		// : REMOVE PLL BY PASS
		/*Register : DPLL_CTRL @ 0XFD1A002C</p>

		Bypasses the PLL clock. The usable clock will be determined from the POST_SRC field. (This signal may only be toggled after 4
		cycles of the old clock and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_DPLL_CTRL_BYPASS                                                    0

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A002C, 0x00000008U ,0x00000000U)  */
		RegMask = (CRF_APB_DPLL_CTRL_BYPASS_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRF_APB_DPLL_CTRL_BYPASS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : DPLL_TO_LPD_CTRL @ 0XFD1A004C</p>

		Divisor value for this clock.
		PSU_CRF_APB_DPLL_TO_LPD_CTRL_DIVISOR0                                           0x4

		Control for a clock that will be generated in the LPD, but used in the FPD as a clock source for the peripheral clock muxes.
		(OFFSET, MASK, VALUE)      (0XFD1A004C, 0x00003F00U ,0x00000400U)  */
		RegMask = (CRF_APB_DPLL_TO_LPD_CTRL_DIVISOR0_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DPLL_TO_LPD_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000004U << CRF_APB_DPLL_TO_LPD_CTRL_DIVISOR0_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DPLL_TO_LPD_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : DPLL FRAC CFG
		// : VIDEO_PLL INIT
		// : UPDATE FB_DIV
		/*Register : VPLL_CTRL @ 0XFD1A0038</p>

		The integer portion of the feedback divider to the PLL
		PSU_CRF_APB_VPLL_CTRL_FBDIV                                                     0x3f

		This turns on the divide by 2 that is inside of the PLL. This does not change the VCO frequency, just the output frequency
		PSU_CRF_APB_VPLL_CTRL_DIV2                                                      0x1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A0038, 0x00017F00U ,0x00013F00U)  */
		RegMask = (CRF_APB_VPLL_CTRL_FBDIV_MASK | CRF_APB_VPLL_CTRL_DIV2_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_VPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x0000003FU << CRF_APB_VPLL_CTRL_FBDIV_SHIFT
			| 0x00000001U << CRF_APB_VPLL_CTRL_DIV2_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_VPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : BY PASS PLL
		/*Register : VPLL_CTRL @ 0XFD1A0038</p>

		Bypasses the PLL clock. The usable clock will be determined from the POST_SRC field. (This signal may only be toggled after 4
		cycles of the old clock and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_VPLL_CTRL_BYPASS                                                    1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A0038, 0x00000008U ,0x00000008U)  */
		RegMask = (CRF_APB_VPLL_CTRL_BYPASS_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_VPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRF_APB_VPLL_CTRL_BYPASS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_VPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : ASSERT RESET
		/*Register : VPLL_CTRL @ 0XFD1A0038</p>

		Asserts Reset to the PLL
		PSU_CRF_APB_VPLL_CTRL_RESET                                                     1

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A0038, 0x00000001U ,0x00000001U)  */
		RegMask = (CRF_APB_VPLL_CTRL_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_VPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRF_APB_VPLL_CTRL_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_VPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : DEASSERT RESET
		/*Register : VPLL_CTRL @ 0XFD1A0038</p>

		Asserts Reset to the PLL
		PSU_CRF_APB_VPLL_CTRL_RESET                                                     0

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A0038, 0x00000001U ,0x00000000U)  */
		RegMask = (CRF_APB_VPLL_CTRL_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_VPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRF_APB_VPLL_CTRL_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_VPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : CHECK PLL STATUS
		/*Register : PLL_STATUS @ 0XFD1A0044</p>

		VPLL is locked
		PSU_CRF_APB_PLL_STATUS_VPLL_LOCK                                                1
		(OFFSET, MASK, VALUE)      (0XFD1A0044, 0x00000004U ,0x00000004U)  */
		while(!(Xil_In32 ( CRF_APB_PLL_STATUS_OFFSET) & 0x00000004U));

	/*############################################################################################################################ */

		// : REMOVE PLL BY PASS
		/*Register : VPLL_CTRL @ 0XFD1A0038</p>

		Bypasses the PLL clock. The usable clock will be determined from the POST_SRC field. (This signal may only be toggled after 4
		cycles of the old clock and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_VPLL_CTRL_BYPASS                                                    0

		PLL Basic Control
		(OFFSET, MASK, VALUE)      (0XFD1A0038, 0x00000008U ,0x00000000U)  */
		RegMask = (CRF_APB_VPLL_CTRL_BYPASS_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_VPLL_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRF_APB_VPLL_CTRL_BYPASS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_VPLL_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : VPLL_TO_LPD_CTRL @ 0XFD1A0050</p>

		Divisor value for this clock.
		PSU_CRF_APB_VPLL_TO_LPD_CTRL_DIVISOR0                                           0x4

		Control for a clock that will be generated in the LPD, but used in the FPD as a clock source for the peripheral clock muxes.
		(OFFSET, MASK, VALUE)      (0XFD1A0050, 0x00003F00U ,0x00000400U)  */
		RegMask = (CRF_APB_VPLL_TO_LPD_CTRL_DIVISOR0_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_VPLL_TO_LPD_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000004U << CRF_APB_VPLL_TO_LPD_CTRL_DIVISOR0_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_VPLL_TO_LPD_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : VIDEO FRAC CFG

}
unsigned long psu_clock_init_data() {
		// : CLOCK CONTROL SLCR REGISTER
		/*Register : GEM0_REF_CTRL @ 0XFF5E0050</p>

		Clock active for the RX channel
		PSU_CRL_APB_GEM0_REF_CTRL_RX_CLKACT                                             0x1

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_GEM0_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_GEM0_REF_CTRL_DIVISOR1                                              0x2

		6 bit divider
		PSU_CRL_APB_GEM0_REF_CTRL_DIVISOR0                                              0x28

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_GEM0_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0050, 0x063F3F07U ,0x06022800U)  */
		RegMask = (CRL_APB_GEM0_REF_CTRL_RX_CLKACT_MASK | CRL_APB_GEM0_REF_CTRL_CLKACT_MASK | CRL_APB_GEM0_REF_CTRL_DIVISOR1_MASK | CRL_APB_GEM0_REF_CTRL_DIVISOR0_MASK | CRL_APB_GEM0_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_GEM0_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_GEM0_REF_CTRL_RX_CLKACT_SHIFT
			| 0x00000001U << CRL_APB_GEM0_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_GEM0_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000028U << CRL_APB_GEM0_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_GEM0_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_GEM0_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : GEM1_REF_CTRL @ 0XFF5E0054</p>

		Clock active for the RX channel
		PSU_CRL_APB_GEM1_REF_CTRL_RX_CLKACT                                             0x1

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_GEM1_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_GEM1_REF_CTRL_DIVISOR1                                              0x2

		6 bit divider
		PSU_CRL_APB_GEM1_REF_CTRL_DIVISOR0                                              0x28

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_GEM1_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0054, 0x063F3F07U ,0x06022800U)  */
		RegMask = (CRL_APB_GEM1_REF_CTRL_RX_CLKACT_MASK | CRL_APB_GEM1_REF_CTRL_CLKACT_MASK | CRL_APB_GEM1_REF_CTRL_DIVISOR1_MASK | CRL_APB_GEM1_REF_CTRL_DIVISOR0_MASK | CRL_APB_GEM1_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_GEM1_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_GEM1_REF_CTRL_RX_CLKACT_SHIFT
			| 0x00000001U << CRL_APB_GEM1_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_GEM1_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000028U << CRL_APB_GEM1_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_GEM1_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_GEM1_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : GEM2_REF_CTRL @ 0XFF5E0058</p>

		Clock active for the RX channel
		PSU_CRL_APB_GEM2_REF_CTRL_RX_CLKACT                                             0x1

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_GEM2_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_GEM2_REF_CTRL_DIVISOR1                                              0x2

		6 bit divider
		PSU_CRL_APB_GEM2_REF_CTRL_DIVISOR0                                              0x28

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_GEM2_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0058, 0x063F3F07U ,0x06022800U)  */
		RegMask = (CRL_APB_GEM2_REF_CTRL_RX_CLKACT_MASK | CRL_APB_GEM2_REF_CTRL_CLKACT_MASK | CRL_APB_GEM2_REF_CTRL_DIVISOR1_MASK | CRL_APB_GEM2_REF_CTRL_DIVISOR0_MASK | CRL_APB_GEM2_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_GEM2_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_GEM2_REF_CTRL_RX_CLKACT_SHIFT
			| 0x00000001U << CRL_APB_GEM2_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_GEM2_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000028U << CRL_APB_GEM2_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_GEM2_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_GEM2_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : GEM3_REF_CTRL @ 0XFF5E005C</p>

		Clock active for the RX channel
		PSU_CRL_APB_GEM3_REF_CTRL_RX_CLKACT                                             0x1

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_GEM3_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_GEM3_REF_CTRL_DIVISOR1                                              0x2

		6 bit divider
		PSU_CRL_APB_GEM3_REF_CTRL_DIVISOR0                                              0x28

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_GEM3_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E005C, 0x063F3F07U ,0x06022800U)  */
		RegMask = (CRL_APB_GEM3_REF_CTRL_RX_CLKACT_MASK | CRL_APB_GEM3_REF_CTRL_CLKACT_MASK | CRL_APB_GEM3_REF_CTRL_DIVISOR1_MASK | CRL_APB_GEM3_REF_CTRL_DIVISOR0_MASK | CRL_APB_GEM3_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_GEM3_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_GEM3_REF_CTRL_RX_CLKACT_SHIFT
			| 0x00000001U << CRL_APB_GEM3_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_GEM3_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000028U << CRL_APB_GEM3_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_GEM3_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_GEM3_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : USB0_BUS_REF_CTRL @ 0XFF5E0060</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_USB0_BUS_REF_CTRL_CLKACT                                            0x1

		6 bit divider
		PSU_CRL_APB_USB0_BUS_REF_CTRL_DIVISOR1                                          0x1

		6 bit divider
		PSU_CRL_APB_USB0_BUS_REF_CTRL_DIVISOR0                                          0x32

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_USB0_BUS_REF_CTRL_SRCSEL                                            0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0060, 0x023F3F07U ,0x02013200U)  */
		RegMask = (CRL_APB_USB0_BUS_REF_CTRL_CLKACT_MASK | CRL_APB_USB0_BUS_REF_CTRL_DIVISOR1_MASK | CRL_APB_USB0_BUS_REF_CTRL_DIVISOR0_MASK | CRL_APB_USB0_BUS_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_USB0_BUS_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_USB0_BUS_REF_CTRL_CLKACT_SHIFT
			| 0x00000001U << CRL_APB_USB0_BUS_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000032U << CRL_APB_USB0_BUS_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_USB0_BUS_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_USB0_BUS_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : USB3_DUAL_REF_CTRL @ 0XFF5E004C</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_USB3_DUAL_REF_CTRL_CLKACT                                           0x1

		6 bit divider
		PSU_CRL_APB_USB3_DUAL_REF_CTRL_DIVISOR1                                         0x1

		6 bit divider
		PSU_CRL_APB_USB3_DUAL_REF_CTRL_DIVISOR0                                         0x8

		000 = IOPLL; 010 = RPLL; 011 = DPLL. (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_USB3_DUAL_REF_CTRL_SRCSEL                                           0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E004C, 0x023F3F07U ,0x02010800U)  */
		RegMask = (CRL_APB_USB3_DUAL_REF_CTRL_CLKACT_MASK | CRL_APB_USB3_DUAL_REF_CTRL_DIVISOR1_MASK | CRL_APB_USB3_DUAL_REF_CTRL_DIVISOR0_MASK | CRL_APB_USB3_DUAL_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_USB3_DUAL_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_USB3_DUAL_REF_CTRL_CLKACT_SHIFT
			| 0x00000001U << CRL_APB_USB3_DUAL_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000008U << CRL_APB_USB3_DUAL_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_USB3_DUAL_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_USB3_DUAL_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : QSPI_REF_CTRL @ 0XFF5E0068</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_QSPI_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_QSPI_REF_CTRL_DIVISOR1                                              0x2

		6 bit divider
		PSU_CRL_APB_QSPI_REF_CTRL_DIVISOR0                                              0x32

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_QSPI_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0068, 0x013F3F07U ,0x01023200U)  */
		RegMask = (CRL_APB_QSPI_REF_CTRL_CLKACT_MASK | CRL_APB_QSPI_REF_CTRL_DIVISOR1_MASK | CRL_APB_QSPI_REF_CTRL_DIVISOR0_MASK | CRL_APB_QSPI_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_QSPI_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_QSPI_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_QSPI_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000032U << CRL_APB_QSPI_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_QSPI_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_QSPI_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : SDIO0_REF_CTRL @ 0XFF5E006C</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_SDIO0_REF_CTRL_CLKACT                                               0x1

		6 bit divider
		PSU_CRL_APB_SDIO0_REF_CTRL_DIVISOR1                                             0x2

		6 bit divider
		PSU_CRL_APB_SDIO0_REF_CTRL_DIVISOR0                                             0x32

		000 = IOPLL; 010 = RPLL; 011 = VPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_SDIO0_REF_CTRL_SRCSEL                                               0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E006C, 0x013F3F07U ,0x01023200U)  */
		RegMask = (CRL_APB_SDIO0_REF_CTRL_CLKACT_MASK | CRL_APB_SDIO0_REF_CTRL_DIVISOR1_MASK | CRL_APB_SDIO0_REF_CTRL_DIVISOR0_MASK | CRL_APB_SDIO0_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_SDIO0_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_SDIO0_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_SDIO0_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000032U << CRL_APB_SDIO0_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_SDIO0_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_SDIO0_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : SDIO1_REF_CTRL @ 0XFF5E0070</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_SDIO1_REF_CTRL_CLKACT                                               0x1

		6 bit divider
		PSU_CRL_APB_SDIO1_REF_CTRL_DIVISOR1                                             0x2

		6 bit divider
		PSU_CRL_APB_SDIO1_REF_CTRL_DIVISOR0                                             0x32

		000 = IOPLL; 010 = RPLL; 011 = VPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_SDIO1_REF_CTRL_SRCSEL                                               0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0070, 0x013F3F07U ,0x01023200U)  */
		RegMask = (CRL_APB_SDIO1_REF_CTRL_CLKACT_MASK | CRL_APB_SDIO1_REF_CTRL_DIVISOR1_MASK | CRL_APB_SDIO1_REF_CTRL_DIVISOR0_MASK | CRL_APB_SDIO1_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_SDIO1_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_SDIO1_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_SDIO1_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000032U << CRL_APB_SDIO1_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_SDIO1_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_SDIO1_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : UART0_REF_CTRL @ 0XFF5E0074</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_UART0_REF_CTRL_CLKACT                                               0x1

		6 bit divider
		PSU_CRL_APB_UART0_REF_CTRL_DIVISOR1                                             0x2

		6 bit divider
		PSU_CRL_APB_UART0_REF_CTRL_DIVISOR0                                             0x28

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_UART0_REF_CTRL_SRCSEL                                               0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0074, 0x013F3F07U ,0x01022800U)  */
		RegMask = (CRL_APB_UART0_REF_CTRL_CLKACT_MASK | CRL_APB_UART0_REF_CTRL_DIVISOR1_MASK | CRL_APB_UART0_REF_CTRL_DIVISOR0_MASK | CRL_APB_UART0_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_UART0_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_UART0_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_UART0_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000028U << CRL_APB_UART0_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_UART0_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_UART0_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : UART1_REF_CTRL @ 0XFF5E0078</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_UART1_REF_CTRL_CLKACT                                               0x1

		6 bit divider
		PSU_CRL_APB_UART1_REF_CTRL_DIVISOR1                                             0x2

		6 bit divider
		PSU_CRL_APB_UART1_REF_CTRL_DIVISOR0                                             0x28

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_UART1_REF_CTRL_SRCSEL                                               0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0078, 0x013F3F07U ,0x01022800U)  */
		RegMask = (CRL_APB_UART1_REF_CTRL_CLKACT_MASK | CRL_APB_UART1_REF_CTRL_DIVISOR1_MASK | CRL_APB_UART1_REF_CTRL_DIVISOR0_MASK | CRL_APB_UART1_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_UART1_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_UART1_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_UART1_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000028U << CRL_APB_UART1_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_UART1_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_UART1_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : I2C0_REF_CTRL @ 0XFF5E0120</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_I2C0_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_I2C0_REF_CTRL_DIVISOR1                                              0x2

		6 bit divider
		PSU_CRL_APB_I2C0_REF_CTRL_DIVISOR0                                              0x28

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_I2C0_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0120, 0x013F3F07U ,0x01022800U)  */
		RegMask = (CRL_APB_I2C0_REF_CTRL_CLKACT_MASK | CRL_APB_I2C0_REF_CTRL_DIVISOR1_MASK | CRL_APB_I2C0_REF_CTRL_DIVISOR0_MASK | CRL_APB_I2C0_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_I2C0_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_I2C0_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_I2C0_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000028U << CRL_APB_I2C0_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_I2C0_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_I2C0_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : I2C1_REF_CTRL @ 0XFF5E0124</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_I2C1_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_I2C1_REF_CTRL_DIVISOR1                                              0xa

		6 bit divider
		PSU_CRL_APB_I2C1_REF_CTRL_DIVISOR0                                              0x32

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_I2C1_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0124, 0x013F3F07U ,0x010A3200U)  */
		RegMask = (CRL_APB_I2C1_REF_CTRL_CLKACT_MASK | CRL_APB_I2C1_REF_CTRL_DIVISOR1_MASK | CRL_APB_I2C1_REF_CTRL_DIVISOR0_MASK | CRL_APB_I2C1_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_I2C1_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_I2C1_REF_CTRL_CLKACT_SHIFT
			| 0x0000000AU << CRL_APB_I2C1_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000032U << CRL_APB_I2C1_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_I2C1_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_I2C1_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : SPI0_REF_CTRL @ 0XFF5E007C</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_SPI0_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_SPI0_REF_CTRL_DIVISOR1                                              0x2

		6 bit divider
		PSU_CRL_APB_SPI0_REF_CTRL_DIVISOR0                                              0x28

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_SPI0_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E007C, 0x013F3F07U ,0x01022800U)  */
		RegMask = (CRL_APB_SPI0_REF_CTRL_CLKACT_MASK | CRL_APB_SPI0_REF_CTRL_DIVISOR1_MASK | CRL_APB_SPI0_REF_CTRL_DIVISOR0_MASK | CRL_APB_SPI0_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_SPI0_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_SPI0_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_SPI0_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000028U << CRL_APB_SPI0_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_SPI0_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_SPI0_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : SPI1_REF_CTRL @ 0XFF5E0080</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_SPI1_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_SPI1_REF_CTRL_DIVISOR1                                              0xa

		6 bit divider
		PSU_CRL_APB_SPI1_REF_CTRL_DIVISOR0                                              0x32

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_SPI1_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0080, 0x013F3F07U ,0x010A3200U)  */
		RegMask = (CRL_APB_SPI1_REF_CTRL_CLKACT_MASK | CRL_APB_SPI1_REF_CTRL_DIVISOR1_MASK | CRL_APB_SPI1_REF_CTRL_DIVISOR0_MASK | CRL_APB_SPI1_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_SPI1_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_SPI1_REF_CTRL_CLKACT_SHIFT
			| 0x0000000AU << CRL_APB_SPI1_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000032U << CRL_APB_SPI1_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_SPI1_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_SPI1_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : CAN0_REF_CTRL @ 0XFF5E0084</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_CAN0_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_CAN0_REF_CTRL_DIVISOR1                                              0x2

		6 bit divider
		PSU_CRL_APB_CAN0_REF_CTRL_DIVISOR0                                              0x28

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_CAN0_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0084, 0x013F3F07U ,0x01022800U)  */
		RegMask = (CRL_APB_CAN0_REF_CTRL_CLKACT_MASK | CRL_APB_CAN0_REF_CTRL_DIVISOR1_MASK | CRL_APB_CAN0_REF_CTRL_DIVISOR0_MASK | CRL_APB_CAN0_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_CAN0_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_CAN0_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_CAN0_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000028U << CRL_APB_CAN0_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_CAN0_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_CAN0_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : CAN1_REF_CTRL @ 0XFF5E0088</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_CAN1_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_CAN1_REF_CTRL_DIVISOR1                                              0x2

		6 bit divider
		PSU_CRL_APB_CAN1_REF_CTRL_DIVISOR0                                              0x28

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_CAN1_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0088, 0x013F3F07U ,0x01022800U)  */
		RegMask = (CRL_APB_CAN1_REF_CTRL_CLKACT_MASK | CRL_APB_CAN1_REF_CTRL_DIVISOR1_MASK | CRL_APB_CAN1_REF_CTRL_DIVISOR0_MASK | CRL_APB_CAN1_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_CAN1_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_CAN1_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_CAN1_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000028U << CRL_APB_CAN1_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_CAN1_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_CAN1_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : CPU_R5_CTRL @ 0XFF5E0090</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_CPU_R5_CTRL_CLKACT                                                  0x1

		6 bit divider
		PSU_CRL_APB_CPU_R5_CTRL_DIVISOR0                                                0x1f4

		000 = RPLL; 010 = IOPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_CPU_R5_CTRL_SRCSEL                                                  0x2

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0090, 0x01003F07U ,0x01003F02U)  */
		RegMask = (CRL_APB_CPU_R5_CTRL_CLKACT_MASK | CRL_APB_CPU_R5_CTRL_DIVISOR0_MASK | CRL_APB_CPU_R5_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_CPU_R5_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_CPU_R5_CTRL_CLKACT_SHIFT
			| 0x000001F4U << CRL_APB_CPU_R5_CTRL_DIVISOR0_SHIFT
			| 0x00000002U << CRL_APB_CPU_R5_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_CPU_R5_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : IOU_SWITCH_CTRL @ 0XFF5E009C</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_IOU_SWITCH_CTRL_CLKACT                                              0x1

		6 bit divider
		PSU_CRL_APB_IOU_SWITCH_CTRL_DIVISOR0                                            0x6

		000 = RPLL; 010 = IOPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_IOU_SWITCH_CTRL_SRCSEL                                              0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E009C, 0x01003F07U ,0x01000600U)  */
		RegMask = (CRL_APB_IOU_SWITCH_CTRL_CLKACT_MASK | CRL_APB_IOU_SWITCH_CTRL_DIVISOR0_MASK | CRL_APB_IOU_SWITCH_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_IOU_SWITCH_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_IOU_SWITCH_CTRL_CLKACT_SHIFT
			| 0x00000006U << CRL_APB_IOU_SWITCH_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_IOU_SWITCH_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_IOU_SWITCH_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : PCAP_CTRL @ 0XFF5E00A4</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_PCAP_CTRL_CLKACT                                                    0x1

		6 bit divider
		PSU_CRL_APB_PCAP_CTRL_DIVISOR0                                                  0x8

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_PCAP_CTRL_SRCSEL                                                    0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E00A4, 0x01003F07U ,0x01000800U)  */
		RegMask = (CRL_APB_PCAP_CTRL_CLKACT_MASK | CRL_APB_PCAP_CTRL_DIVISOR0_MASK | CRL_APB_PCAP_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_PCAP_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_PCAP_CTRL_CLKACT_SHIFT
			| 0x00000008U << CRL_APB_PCAP_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_PCAP_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_PCAP_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : LPD_SWITCH_CTRL @ 0XFF5E00A8</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_LPD_SWITCH_CTRL_CLKACT                                              0x1

		6 bit divider
		PSU_CRL_APB_LPD_SWITCH_CTRL_DIVISOR0                                            0x4

		000 = RPLL; 010 = IOPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_LPD_SWITCH_CTRL_SRCSEL                                              0x2

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E00A8, 0x01003F07U ,0x01000402U)  */
		RegMask = (CRL_APB_LPD_SWITCH_CTRL_CLKACT_MASK | CRL_APB_LPD_SWITCH_CTRL_DIVISOR0_MASK | CRL_APB_LPD_SWITCH_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_LPD_SWITCH_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_LPD_SWITCH_CTRL_CLKACT_SHIFT
			| 0x00000004U << CRL_APB_LPD_SWITCH_CTRL_DIVISOR0_SHIFT
			| 0x00000002U << CRL_APB_LPD_SWITCH_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_LPD_SWITCH_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : LPD_LSBUS_CTRL @ 0XFF5E00AC</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_LPD_LSBUS_CTRL_CLKACT                                               0x1

		6 bit divider
		PSU_CRL_APB_LPD_LSBUS_CTRL_DIVISOR0                                             0x14

		000 = RPLL; 010 = IOPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_LPD_LSBUS_CTRL_SRCSEL                                               0x2

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E00AC, 0x01003F07U ,0x01001402U)  */
		RegMask = (CRL_APB_LPD_LSBUS_CTRL_CLKACT_MASK | CRL_APB_LPD_LSBUS_CTRL_DIVISOR0_MASK | CRL_APB_LPD_LSBUS_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_LPD_LSBUS_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_LPD_LSBUS_CTRL_CLKACT_SHIFT
			| 0x00000014U << CRL_APB_LPD_LSBUS_CTRL_DIVISOR0_SHIFT
			| 0x00000002U << CRL_APB_LPD_LSBUS_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_LPD_LSBUS_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : DBG_LPD_CTRL @ 0XFF5E00B0</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_DBG_LPD_CTRL_CLKACT                                                 0x1

		6 bit divider
		PSU_CRL_APB_DBG_LPD_CTRL_DIVISOR0                                               0x190

		000 = RPLL; 010 = IOPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_DBG_LPD_CTRL_SRCSEL                                                 0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E00B0, 0x01003F07U ,0x01003F00U)  */
		RegMask = (CRL_APB_DBG_LPD_CTRL_CLKACT_MASK | CRL_APB_DBG_LPD_CTRL_DIVISOR0_MASK | CRL_APB_DBG_LPD_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_DBG_LPD_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_DBG_LPD_CTRL_CLKACT_SHIFT
			| 0x00000190U << CRL_APB_DBG_LPD_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_DBG_LPD_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_DBG_LPD_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : NAND_REF_CTRL @ 0XFF5E00B4</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_NAND_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_NAND_REF_CTRL_DIVISOR1                                              0x2

		6 bit divider
		PSU_CRL_APB_NAND_REF_CTRL_DIVISOR0                                              0x32

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_NAND_REF_CTRL_SRCSEL                                                0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E00B4, 0x013F3F07U ,0x01023200U)  */
		RegMask = (CRL_APB_NAND_REF_CTRL_CLKACT_MASK | CRL_APB_NAND_REF_CTRL_DIVISOR1_MASK | CRL_APB_NAND_REF_CTRL_DIVISOR0_MASK | CRL_APB_NAND_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_NAND_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_NAND_REF_CTRL_CLKACT_SHIFT
			| 0x00000002U << CRL_APB_NAND_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000032U << CRL_APB_NAND_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_NAND_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_NAND_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : ADMA_REF_CTRL @ 0XFF5E00B8</p>

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_ADMA_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRL_APB_ADMA_REF_CTRL_DIVISOR0                                              0x4

		000 = RPLL; 010 = IOPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_ADMA_REF_CTRL_SRCSEL                                                0x2

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E00B8, 0x01003F07U ,0x01000402U)  */
		RegMask = (CRL_APB_ADMA_REF_CTRL_CLKACT_MASK | CRL_APB_ADMA_REF_CTRL_DIVISOR0_MASK | CRL_APB_ADMA_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_ADMA_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_ADMA_REF_CTRL_CLKACT_SHIFT
			| 0x00000004U << CRL_APB_ADMA_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000002U << CRL_APB_ADMA_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_ADMA_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : AMS_REF_CTRL @ 0XFF5E0108</p>

		6 bit divider
		PSU_CRL_APB_AMS_REF_CTRL_DIVISOR1                                               0x1

		6 bit divider
		PSU_CRL_APB_AMS_REF_CTRL_DIVISOR0                                               0x28

		000 = RPLL; 010 = IOPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_AMS_REF_CTRL_SRCSEL                                                 0x0

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_AMS_REF_CTRL_CLKACT                                                 0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0108, 0x013F3F07U ,0x01012800U)  */
		RegMask = (CRL_APB_AMS_REF_CTRL_DIVISOR1_MASK | CRL_APB_AMS_REF_CTRL_DIVISOR0_MASK | CRL_APB_AMS_REF_CTRL_SRCSEL_MASK | CRL_APB_AMS_REF_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_AMS_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << CRL_APB_AMS_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000028U << CRL_APB_AMS_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRL_APB_AMS_REF_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRL_APB_AMS_REF_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_AMS_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : DLL_REF_CTRL @ 0XFF5E0104</p>

		000 = IOPLL; 001 = RPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new clock. This
		is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_DLL_REF_CTRL_SRCSEL                                                 0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0104, 0x00000007U ,0x00000000U)  */
		RegMask = (CRL_APB_DLL_REF_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_DLL_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_DLL_REF_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_DLL_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : TIMESTAMP_REF_CTRL @ 0XFF5E0128</p>

		6 bit divider
		PSU_CRL_APB_TIMESTAMP_REF_CTRL_DIVISOR0                                         0x14

		1XX = pss_ref_clk; 000 = RPLL; 010 = IOPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 
		 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRL_APB_TIMESTAMP_REF_CTRL_SRCSEL                                           0x2

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRL_APB_TIMESTAMP_REF_CTRL_CLKACT                                           0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFF5E0128, 0x01003F07U ,0x01001402U)  */
		RegMask = (CRL_APB_TIMESTAMP_REF_CTRL_DIVISOR0_MASK | CRL_APB_TIMESTAMP_REF_CTRL_SRCSEL_MASK | CRL_APB_TIMESTAMP_REF_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_TIMESTAMP_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000014U << CRL_APB_TIMESTAMP_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000002U << CRL_APB_TIMESTAMP_REF_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRL_APB_TIMESTAMP_REF_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_TIMESTAMP_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : PCIE_REF_CTRL @ 0XFD1A00B4</p>

		000 = IOPLL; 010 = RPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_PCIE_REF_CTRL_SRCSEL                                                0x0

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRF_APB_PCIE_REF_CTRL_CLKACT                                                0x1

		6 bit divider
		PSU_CRF_APB_PCIE_REF_CTRL_DIVISOR0                                              0x7d

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A00B4, 0x01003F07U ,0x01003F00U)  */
		RegMask = (CRF_APB_PCIE_REF_CTRL_SRCSEL_MASK | CRF_APB_PCIE_REF_CTRL_CLKACT_MASK | CRF_APB_PCIE_REF_CTRL_DIVISOR0_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_PCIE_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRF_APB_PCIE_REF_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_PCIE_REF_CTRL_CLKACT_SHIFT
			| 0x0000007DU << CRF_APB_PCIE_REF_CTRL_DIVISOR0_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_PCIE_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : DP_VIDEO_REF_CTRL @ 0XFD1A0070</p>

		6 bit divider
		PSU_CRF_APB_DP_VIDEO_REF_CTRL_DIVISOR1                                          0x15

		6 bit divider
		PSU_CRF_APB_DP_VIDEO_REF_CTRL_DIVISOR0                                          0x32

		000 = VPLL; 010 = DPLL; 011 = RPLL - might be using extra mux; (This signal may only be toggled after 4 cycles of the old clo
		k and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_DP_VIDEO_REF_CTRL_SRCSEL                                            0x0

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRF_APB_DP_VIDEO_REF_CTRL_CLKACT                                            0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A0070, 0x013F3F07U ,0x01153200U)  */
		RegMask = (CRF_APB_DP_VIDEO_REF_CTRL_DIVISOR1_MASK | CRF_APB_DP_VIDEO_REF_CTRL_DIVISOR0_MASK | CRF_APB_DP_VIDEO_REF_CTRL_SRCSEL_MASK | CRF_APB_DP_VIDEO_REF_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DP_VIDEO_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000015U << CRF_APB_DP_VIDEO_REF_CTRL_DIVISOR1_SHIFT
			| 0x00000032U << CRF_APB_DP_VIDEO_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRF_APB_DP_VIDEO_REF_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_DP_VIDEO_REF_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DP_VIDEO_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : DP_AUDIO_REF_CTRL @ 0XFD1A0074</p>

		6 bit divider
		PSU_CRF_APB_DP_AUDIO_REF_CTRL_DIVISOR1                                          0x2

		6 bit divider
		PSU_CRF_APB_DP_AUDIO_REF_CTRL_DIVISOR0                                          0x2a

		000 = VPLL; 010 = DPLL; 011 = RPLL - might be using extra mux; (This signal may only be toggled after 4 cycles of the old clo
		k and 4 cycles of the new clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_DP_AUDIO_REF_CTRL_SRCSEL                                            0x0

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRF_APB_DP_AUDIO_REF_CTRL_CLKACT                                            0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A0074, 0x013F3F07U ,0x01022A00U)  */
		RegMask = (CRF_APB_DP_AUDIO_REF_CTRL_DIVISOR1_MASK | CRF_APB_DP_AUDIO_REF_CTRL_DIVISOR0_MASK | CRF_APB_DP_AUDIO_REF_CTRL_SRCSEL_MASK | CRF_APB_DP_AUDIO_REF_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DP_AUDIO_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000002U << CRF_APB_DP_AUDIO_REF_CTRL_DIVISOR1_SHIFT
			| 0x0000002AU << CRF_APB_DP_AUDIO_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRF_APB_DP_AUDIO_REF_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_DP_AUDIO_REF_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DP_AUDIO_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : DP_STC_REF_CTRL @ 0XFD1A007C</p>

		6 bit divider
		PSU_CRF_APB_DP_STC_REF_CTRL_DIVISOR1                                            0x2

		6 bit divider
		PSU_CRF_APB_DP_STC_REF_CTRL_DIVISOR0                                            0x2a

		000 = VPLL; 010 = DPLL; 011 = RPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new 
		lock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_DP_STC_REF_CTRL_SRCSEL                                              0x0

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRF_APB_DP_STC_REF_CTRL_CLKACT                                              0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A007C, 0x013F3F07U ,0x01022A00U)  */
		RegMask = (CRF_APB_DP_STC_REF_CTRL_DIVISOR1_MASK | CRF_APB_DP_STC_REF_CTRL_DIVISOR0_MASK | CRF_APB_DP_STC_REF_CTRL_SRCSEL_MASK | CRF_APB_DP_STC_REF_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DP_STC_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000002U << CRF_APB_DP_STC_REF_CTRL_DIVISOR1_SHIFT
			| 0x0000002AU << CRF_APB_DP_STC_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRF_APB_DP_STC_REF_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_DP_STC_REF_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DP_STC_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : ACPU_CTRL @ 0XFD1A0060</p>

		6 bit divider
		PSU_CRF_APB_ACPU_CTRL_DIVISOR0                                                  0xfa

		000 = APLL; 010 = DPLL; 011 = VPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new 
		lock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_ACPU_CTRL_SRCSEL                                                    0x0

		Clock active signal. Switch to 0 to disable the clock. For the half speed APU Clock
		PSU_CRF_APB_ACPU_CTRL_CLKACT_HALF                                               0x1

		Clock active signal. Switch to 0 to disable the clock. For the full speed ACPUX Clock. This will shut off the high speed cloc
		 to the entire APU
		PSU_CRF_APB_ACPU_CTRL_CLKACT_FULL                                               0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A0060, 0x03003F07U ,0x03003F00U)  */
		RegMask = (CRF_APB_ACPU_CTRL_DIVISOR0_MASK | CRF_APB_ACPU_CTRL_SRCSEL_MASK | CRF_APB_ACPU_CTRL_CLKACT_HALF_MASK | CRF_APB_ACPU_CTRL_CLKACT_FULL_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_ACPU_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x000000FAU << CRF_APB_ACPU_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRF_APB_ACPU_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_ACPU_CTRL_CLKACT_HALF_SHIFT
			| 0x00000001U << CRF_APB_ACPU_CTRL_CLKACT_FULL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_ACPU_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : DBG_TRACE_CTRL @ 0XFD1A0064</p>

		6 bit divider
		PSU_CRF_APB_DBG_TRACE_CTRL_DIVISOR0                                             0x1f4

		000 = IOPLL; 010 = DPLL; 011 = APLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_DBG_TRACE_CTRL_SRCSEL                                               0x2

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRF_APB_DBG_TRACE_CTRL_CLKACT                                               0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A0064, 0x01003F07U ,0x01003F02U)  */
		RegMask = (CRF_APB_DBG_TRACE_CTRL_DIVISOR0_MASK | CRF_APB_DBG_TRACE_CTRL_SRCSEL_MASK | CRF_APB_DBG_TRACE_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DBG_TRACE_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x000001F4U << CRF_APB_DBG_TRACE_CTRL_DIVISOR0_SHIFT
			| 0x00000002U << CRF_APB_DBG_TRACE_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_DBG_TRACE_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DBG_TRACE_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : DBG_FPD_CTRL @ 0XFD1A0068</p>

		6 bit divider
		PSU_CRF_APB_DBG_FPD_CTRL_DIVISOR0                                               0x1f4

		000 = IOPLL; 010 = DPLL; 011 = APLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_DBG_FPD_CTRL_SRCSEL                                                 0x2

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRF_APB_DBG_FPD_CTRL_CLKACT                                                 0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A0068, 0x01003F07U ,0x01003F02U)  */
		RegMask = (CRF_APB_DBG_FPD_CTRL_DIVISOR0_MASK | CRF_APB_DBG_FPD_CTRL_SRCSEL_MASK | CRF_APB_DBG_FPD_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DBG_FPD_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x000001F4U << CRF_APB_DBG_FPD_CTRL_DIVISOR0_SHIFT
			| 0x00000002U << CRF_APB_DBG_FPD_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_DBG_FPD_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DBG_FPD_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : DDR_CTRL @ 0XFD1A0080</p>

		6 bit divider
		PSU_CRF_APB_DDR_CTRL_DIVISOR0                                                   0xa

		000 = DPLL; 001 = VPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new clock. This 
		s not usually an issue, but designers must be aware.)
		PSU_CRF_APB_DDR_CTRL_SRCSEL                                                     0x0

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A0080, 0x00003F07U ,0x00000A00U)  */
		RegMask = (CRF_APB_DDR_CTRL_DIVISOR0_MASK | CRF_APB_DDR_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DDR_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x0000000AU << CRF_APB_DDR_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRF_APB_DDR_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DDR_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : GPU_REF_CTRL @ 0XFD1A0084</p>

		6 bit divider
		PSU_CRF_APB_GPU_REF_CTRL_DIVISOR0                                               0x20d

		000 = IOPLL; 010 = VPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_GPU_REF_CTRL_SRCSEL                                                 0x2

		Clock active signal. Switch to 0 to disable the clock. Will stop clock for both Pixel Processors below
		PSU_CRF_APB_GPU_REF_CTRL_CLKACT                                                 0x1

		Clock active signal for Pixel Processor. Switch to 0 to disable the clock
		PSU_CRF_APB_GPU_REF_CTRL_PP0_CLKACT                                             0x1

		Clock active signal for Pixel Processor. Switch to 0 to disable the clock
		PSU_CRF_APB_GPU_REF_CTRL_PP1_CLKACT                                             0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A0084, 0x07003F07U ,0x07003F02U)  */
		RegMask = (CRF_APB_GPU_REF_CTRL_DIVISOR0_MASK | CRF_APB_GPU_REF_CTRL_SRCSEL_MASK | CRF_APB_GPU_REF_CTRL_CLKACT_MASK | CRF_APB_GPU_REF_CTRL_PP0_CLKACT_MASK | CRF_APB_GPU_REF_CTRL_PP1_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_GPU_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x0000020DU << CRF_APB_GPU_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000002U << CRF_APB_GPU_REF_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_GPU_REF_CTRL_CLKACT_SHIFT
			| 0x00000001U << CRF_APB_GPU_REF_CTRL_PP0_CLKACT_SHIFT
			| 0x00000001U << CRF_APB_GPU_REF_CTRL_PP1_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_GPU_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : GDMA_REF_CTRL @ 0XFD1A00B8</p>

		6 bit divider
		PSU_CRF_APB_GDMA_REF_CTRL_DIVISOR0                                              0x3

		000 = APLL; 010 = VPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new 
		lock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_GDMA_REF_CTRL_SRCSEL                                                0x3

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRF_APB_GDMA_REF_CTRL_CLKACT                                                0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A00B8, 0x01003F07U ,0x01000303U)  */
		RegMask = (CRF_APB_GDMA_REF_CTRL_DIVISOR0_MASK | CRF_APB_GDMA_REF_CTRL_SRCSEL_MASK | CRF_APB_GDMA_REF_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_GDMA_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000003U << CRF_APB_GDMA_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000003U << CRF_APB_GDMA_REF_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_GDMA_REF_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_GDMA_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : DPDMA_REF_CTRL @ 0XFD1A00BC</p>

		6 bit divider
		PSU_CRF_APB_DPDMA_REF_CTRL_DIVISOR0                                             0x3

		000 = APLL; 010 = VPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new 
		lock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_DPDMA_REF_CTRL_SRCSEL                                               0x3

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRF_APB_DPDMA_REF_CTRL_CLKACT                                               0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A00BC, 0x01003F07U ,0x01000303U)  */
		RegMask = (CRF_APB_DPDMA_REF_CTRL_DIVISOR0_MASK | CRF_APB_DPDMA_REF_CTRL_SRCSEL_MASK | CRF_APB_DPDMA_REF_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DPDMA_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000003U << CRF_APB_DPDMA_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000003U << CRF_APB_DPDMA_REF_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_DPDMA_REF_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DPDMA_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : TOPSW_MAIN_CTRL @ 0XFD1A00C0</p>

		6 bit divider
		PSU_CRF_APB_TOPSW_MAIN_CTRL_DIVISOR0                                            0x3

		000 = APLL; 010 = VPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new 
		lock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_TOPSW_MAIN_CTRL_SRCSEL                                              0x3

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRF_APB_TOPSW_MAIN_CTRL_CLKACT                                              0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A00C0, 0x01003F07U ,0x01000303U)  */
		RegMask = (CRF_APB_TOPSW_MAIN_CTRL_DIVISOR0_MASK | CRF_APB_TOPSW_MAIN_CTRL_SRCSEL_MASK | CRF_APB_TOPSW_MAIN_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_TOPSW_MAIN_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000003U << CRF_APB_TOPSW_MAIN_CTRL_DIVISOR0_SHIFT
			| 0x00000003U << CRF_APB_TOPSW_MAIN_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_TOPSW_MAIN_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_TOPSW_MAIN_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : TOPSW_LSBUS_CTRL @ 0XFD1A00C4</p>

		6 bit divider
		PSU_CRF_APB_TOPSW_LSBUS_CTRL_DIVISOR0                                           0x14

		000 = APLL; 010 = IOPLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_TOPSW_LSBUS_CTRL_SRCSEL                                             0x0

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRF_APB_TOPSW_LSBUS_CTRL_CLKACT                                             0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A00C4, 0x01003F07U ,0x01001400U)  */
		RegMask = (CRF_APB_TOPSW_LSBUS_CTRL_DIVISOR0_MASK | CRF_APB_TOPSW_LSBUS_CTRL_SRCSEL_MASK | CRF_APB_TOPSW_LSBUS_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_TOPSW_LSBUS_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000014U << CRF_APB_TOPSW_LSBUS_CTRL_DIVISOR0_SHIFT
			| 0x00000000U << CRF_APB_TOPSW_LSBUS_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_TOPSW_LSBUS_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_TOPSW_LSBUS_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : GTGREF0_REF_CTRL @ 0XFD1A00C8</p>

		6 bit divider
		PSU_CRF_APB_GTGREF0_REF_CTRL_DIVISOR0                                           0x11

		000 = IOPLL; 010 = APLL; 011 = DPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new
		clock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_GTGREF0_REF_CTRL_SRCSEL                                             0x2

		Clock active signal. Switch to 0 to disable the clock
		PSU_CRF_APB_GTGREF0_REF_CTRL_CLKACT                                             0x1

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A00C8, 0x01003F07U ,0x01001102U)  */
		RegMask = (CRF_APB_GTGREF0_REF_CTRL_DIVISOR0_MASK | CRF_APB_GTGREF0_REF_CTRL_SRCSEL_MASK | CRF_APB_GTGREF0_REF_CTRL_CLKACT_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_GTGREF0_REF_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000011U << CRF_APB_GTGREF0_REF_CTRL_DIVISOR0_SHIFT
			| 0x00000002U << CRF_APB_GTGREF0_REF_CTRL_SRCSEL_SHIFT
			| 0x00000001U << CRF_APB_GTGREF0_REF_CTRL_CLKACT_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_GTGREF0_REF_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : DBG_TSTMP_CTRL @ 0XFD1A00F8</p>

		6 bit divider
		PSU_CRF_APB_DBG_TSTMP_CTRL_DIVISOR0                                             0x8

		000 = APLL; 010 = DPLL; 011 = VPLL; (This signal may only be toggled after 4 cycles of the old clock and 4 cycles of the new 
		lock. This is not usually an issue, but designers must be aware.)
		PSU_CRF_APB_DBG_TSTMP_CTRL_SRCSEL                                               0x2

		This register controls this reference clock
		(OFFSET, MASK, VALUE)      (0XFD1A00F8, 0x00003F07U ,0x00000802U)  */
		RegMask = (CRF_APB_DBG_TSTMP_CTRL_DIVISOR0_MASK | CRF_APB_DBG_TSTMP_CTRL_SRCSEL_MASK |  0 );

		RegVal = Xil_In32 (CRF_APB_DBG_TSTMP_CTRL_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000008U << CRF_APB_DBG_TSTMP_CTRL_DIVISOR0_SHIFT
			| 0x00000002U << CRF_APB_DBG_TSTMP_CTRL_SRCSEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRF_APB_DBG_TSTMP_CTRL_OFFSET , RegVal);

	/*############################################################################################################################ */


}
unsigned long psu_ddr_init_data_3_0() {

}
unsigned long psu_mio_init_data() {
		// : MIO PROGRAMMING
		/*Register : MIO_PIN_0 @ 0XFF180000</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Output, qspi_sclk_out- (QSPI Clock)
		PSU_IOU_SLCR_MIO_PIN_0_L0_SEL                                                   1

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_0_L1_SEL                                                   0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[0]- (Test Scan Port) = test_scan, Outp
		t, test_scan_out[0]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_0_L2_SEL                                                   0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[0]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[0]- (GPIO bank 0) 1= can
		, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL signa
		) 3= pjtag, Input, pjtag_tck- (PJTAG TCK) 4= spi0, Input, spi0_sclk_in- (SPI Clock) 4= spi0, Output, spi0_sclk_out- (SPI Cloc
		) 5= ttc3, Input, ttc3_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace, Output, trace_
		lk- (Trace Port Clock)
		PSU_IOU_SLCR_MIO_PIN_0_L3_SEL                                                   0

		Configures MIO Pin 0 peripheral interface mapping. S
		(OFFSET, MASK, VALUE)      (0XFF180000, 0x000000FEU ,0x00000002U)  */
		RegMask = (IOU_SLCR_MIO_PIN_0_L0_SEL_MASK | IOU_SLCR_MIO_PIN_0_L1_SEL_MASK | IOU_SLCR_MIO_PIN_0_L2_SEL_MASK | IOU_SLCR_MIO_PIN_0_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_0_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << IOU_SLCR_MIO_PIN_0_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_0_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_0_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_0_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_0_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_1 @ 0XFF180004</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Input, qspi_mi_mi1- (QSPI Databus) 1= qspi, Output, qspi_so_mo1- (QSPI Data
		us)
		PSU_IOU_SLCR_MIO_PIN_1_L0_SEL                                                   1

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_1_L1_SEL                                                   0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[1]- (Test Scan Port) = test_scan, Outp
		t, test_scan_out[1]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_1_L2_SEL                                                   0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[1]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[1]- (GPIO bank 0) 1= can
		, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA signal
		 3= pjtag, Input, pjtag_tdi- (PJTAG TDI) 4= spi0, Output, spi0_n_ss_out[2]- (SPI Master Selects) 5= ttc3, Output, ttc3_wave_o
		t- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input) 7= trace, Output, trace_ctl- (Trace Port Control
		Signal)
		PSU_IOU_SLCR_MIO_PIN_1_L3_SEL                                                   0

		Configures MIO Pin 1 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180004, 0x000000FEU ,0x00000002U)  */
		RegMask = (IOU_SLCR_MIO_PIN_1_L0_SEL_MASK | IOU_SLCR_MIO_PIN_1_L1_SEL_MASK | IOU_SLCR_MIO_PIN_1_L2_SEL_MASK | IOU_SLCR_MIO_PIN_1_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_1_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << IOU_SLCR_MIO_PIN_1_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_1_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_1_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_1_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_1_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_2 @ 0XFF180008</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Input, qspi_mi2- (QSPI Databus) 1= qspi, Output, qspi_mo2- (QSPI Databus)
		PSU_IOU_SLCR_MIO_PIN_2_L0_SEL                                                   1

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_2_L1_SEL                                                   0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[2]- (Test Scan Port) = test_scan, Outp
		t, test_scan_out[2]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_2_L2_SEL                                                   0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[2]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[2]- (GPIO bank 0) 1= can
		, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL signal
		 3= pjtag, Output, pjtag_tdo- (PJTAG TDO) 4= spi0, Output, spi0_n_ss_out[1]- (SPI Master Selects) 5= ttc2, Input, ttc2_clk_in
		 (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Output, tracedq[0]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_2_L3_SEL                                                   0

		Configures MIO Pin 2 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180008, 0x000000FEU ,0x00000002U)  */
		RegMask = (IOU_SLCR_MIO_PIN_2_L0_SEL_MASK | IOU_SLCR_MIO_PIN_2_L1_SEL_MASK | IOU_SLCR_MIO_PIN_2_L2_SEL_MASK | IOU_SLCR_MIO_PIN_2_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_2_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << IOU_SLCR_MIO_PIN_2_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_2_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_2_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_2_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_2_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_3 @ 0XFF18000C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Input, qspi_mi3- (QSPI Databus) 1= qspi, Output, qspi_mo3- (QSPI Databus)
		PSU_IOU_SLCR_MIO_PIN_3_L0_SEL                                                   1

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_3_L1_SEL                                                   0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[3]- (Test Scan Port) = test_scan, Outp
		t, test_scan_out[3]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_3_L2_SEL                                                   0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[3]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[3]- (GPIO bank 0) 1= can
		, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA signa
		) 3= pjtag, Input, pjtag_tms- (PJTAG TMS) 4= spi0, Input, spi0_n_ss_in- (SPI Master Selects) 4= spi0, Output, spi0_n_ss_out[0
		- (SPI Master Selects) 5= ttc2, Output, ttc2_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial
		output) 7= trace, Output, tracedq[1]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_3_L3_SEL                                                   0

		Configures MIO Pin 3 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18000C, 0x000000FEU ,0x00000002U)  */
		RegMask = (IOU_SLCR_MIO_PIN_3_L0_SEL_MASK | IOU_SLCR_MIO_PIN_3_L1_SEL_MASK | IOU_SLCR_MIO_PIN_3_L2_SEL_MASK | IOU_SLCR_MIO_PIN_3_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_3_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << IOU_SLCR_MIO_PIN_3_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_3_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_3_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_3_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_3_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_4 @ 0XFF180010</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Output, qspi_mo_mo0- (QSPI Databus) 1= qspi, Input, qspi_si_mi0- (QSPI Data
		us)
		PSU_IOU_SLCR_MIO_PIN_4_L0_SEL                                                   1

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_4_L1_SEL                                                   0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[4]- (Test Scan Port) = test_scan, Outp
		t, test_scan_out[4]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_4_L2_SEL                                                   0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[4]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[4]- (GPIO bank 0) 1= can
		, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL signa
		) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi0, Input, spi0_mi- (MISO signal) 4= spi0, Output, spi0_s
		- (MISO signal) 5= ttc1, Input, ttc1_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace, 
		utput, tracedq[2]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_4_L3_SEL                                                   0

		Configures MIO Pin 4 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180010, 0x000000FEU ,0x00000002U)  */
		RegMask = (IOU_SLCR_MIO_PIN_4_L0_SEL_MASK | IOU_SLCR_MIO_PIN_4_L1_SEL_MASK | IOU_SLCR_MIO_PIN_4_L2_SEL_MASK | IOU_SLCR_MIO_PIN_4_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_4_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << IOU_SLCR_MIO_PIN_4_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_4_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_4_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_4_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_4_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_5 @ 0XFF180014</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Output, qspi_n_ss_out- (QSPI Slave Select)
		PSU_IOU_SLCR_MIO_PIN_5_L0_SEL                                                   1

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_5_L1_SEL                                                   0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[5]- (Test Scan Port) = test_scan, Outp
		t, test_scan_out[5]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_5_L2_SEL                                                   0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[5]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[5]- (GPIO bank 0) 1= can
		, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA signal
		 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi0, Output, spi0_mo- (MOSI signal) 4= spi0, Input, spi0
		si- (MOSI signal) 5= ttc1, Output, ttc1_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input) 7
		 trace, Output, tracedq[3]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_5_L3_SEL                                                   0

		Configures MIO Pin 5 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180014, 0x000000FEU ,0x00000002U)  */
		RegMask = (IOU_SLCR_MIO_PIN_5_L0_SEL_MASK | IOU_SLCR_MIO_PIN_5_L1_SEL_MASK | IOU_SLCR_MIO_PIN_5_L2_SEL_MASK | IOU_SLCR_MIO_PIN_5_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_5_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000001U << IOU_SLCR_MIO_PIN_5_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_5_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_5_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_5_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_5_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_6 @ 0XFF180018</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Output, qspi_clk_for_lpbk- (QSPI Clock to be fed-back)
		PSU_IOU_SLCR_MIO_PIN_6_L0_SEL                                                   0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_6_L1_SEL                                                   0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[6]- (Test Scan Port) = test_scan, Outp
		t, test_scan_out[6]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_6_L2_SEL                                                   0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[6]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[6]- (GPIO bank 0) 1= can
		, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL signal
		 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi1, Input, spi1_sclk_in- (SPI Clock) 4= spi1, Output, spi1
		sclk_out- (SPI Clock) 5= ttc0, Input, ttc0_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace,
		Output, tracedq[4]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_6_L3_SEL                                                   0

		Configures MIO Pin 6 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180018, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_6_L0_SEL_MASK | IOU_SLCR_MIO_PIN_6_L1_SEL_MASK | IOU_SLCR_MIO_PIN_6_L2_SEL_MASK | IOU_SLCR_MIO_PIN_6_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_6_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_6_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_6_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_6_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_6_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_6_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_7 @ 0XFF18001C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Output, qspi_n_ss_out_upper- (QSPI Slave Select upper)
		PSU_IOU_SLCR_MIO_PIN_7_L0_SEL                                                   0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_7_L1_SEL                                                   0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[7]- (Test Scan Port) = test_scan, Outp
		t, test_scan_out[7]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_7_L2_SEL                                                   0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[7]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[7]- (GPIO bank 0) 1= can
		, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA signa
		) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi1, Output, spi1_n_ss_out[2]- (SPI Master Selects) 5= 
		tc0, Output, ttc0_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial output) 7= trace, Output, 
		racedq[5]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_7_L3_SEL                                                   0

		Configures MIO Pin 7 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18001C, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_7_L0_SEL_MASK | IOU_SLCR_MIO_PIN_7_L1_SEL_MASK | IOU_SLCR_MIO_PIN_7_L2_SEL_MASK | IOU_SLCR_MIO_PIN_7_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_7_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_7_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_7_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_7_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_7_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_7_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_8 @ 0XFF180020</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Input, qspi_mi_upper[0]- (QSPI Upper Databus) 1= qspi, Output, qspi_mo_uppe
		[0]- (QSPI Upper Databus)
		PSU_IOU_SLCR_MIO_PIN_8_L0_SEL                                                   0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_8_L1_SEL                                                   0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[8]- (Test Scan Port) = test_scan, Outp
		t, test_scan_out[8]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_8_L2_SEL                                                   0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[8]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[8]- (GPIO bank 0) 1= can
		, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL signa
		) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi1, Output, spi1_n_ss_out[1]- (SPI Master Selects) 5= ttc
		, Input, ttc3_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace, Output, tracedq[6]- (Tr
		ce Port Databus)
		PSU_IOU_SLCR_MIO_PIN_8_L3_SEL                                                   0

		Configures MIO Pin 8 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180020, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_8_L0_SEL_MASK | IOU_SLCR_MIO_PIN_8_L1_SEL_MASK | IOU_SLCR_MIO_PIN_8_L2_SEL_MASK | IOU_SLCR_MIO_PIN_8_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_8_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_8_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_8_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_8_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_8_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_8_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_9 @ 0XFF180024</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Input, qspi_mi_upper[1]- (QSPI Upper Databus) 1= qspi, Output, qspi_mo_uppe
		[1]- (QSPI Upper Databus)
		PSU_IOU_SLCR_MIO_PIN_9_L0_SEL                                                   0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Output, nfc_ce[1]- (NAND chip enable)
		PSU_IOU_SLCR_MIO_PIN_9_L1_SEL                                                   0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[9]- (Test Scan Port) = test_scan, Outp
		t, test_scan_out[9]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_9_L2_SEL                                                   0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[9]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[9]- (GPIO bank 0) 1= can
		, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA signal
		 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi1, Input, spi1_n_ss_in- (SPI Master Selects) 4= spi1, 
		utput, spi1_n_ss_out[0]- (SPI Master Selects) 5= ttc3, Output, ttc3_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (U
		RT receiver serial input) 7= trace, Output, tracedq[7]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_9_L3_SEL                                                   0

		Configures MIO Pin 9 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180024, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_9_L0_SEL_MASK | IOU_SLCR_MIO_PIN_9_L1_SEL_MASK | IOU_SLCR_MIO_PIN_9_L2_SEL_MASK | IOU_SLCR_MIO_PIN_9_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_9_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_9_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_9_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_9_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_9_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_9_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_10 @ 0XFF180028</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Input, qspi_mi_upper[2]- (QSPI Upper Databus) 1= qspi, Output, qspi_mo_uppe
		[2]- (QSPI Upper Databus)
		PSU_IOU_SLCR_MIO_PIN_10_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_rb_n[0]- (NAND Ready/Busy)
		PSU_IOU_SLCR_MIO_PIN_10_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[10]- (Test Scan Port) = test_scan, Out
		ut, test_scan_out[10]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_10_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[10]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[10]- (GPIO bank 0) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi1, Input, spi1_mi- (MISO signal) 4= spi1, Output, spi1_
		o- (MISO signal) 5= ttc2, Input, ttc2_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Outp
		t, tracedq[8]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_10_L3_SEL                                                  0

		Configures MIO Pin 10 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180028, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_10_L0_SEL_MASK | IOU_SLCR_MIO_PIN_10_L1_SEL_MASK | IOU_SLCR_MIO_PIN_10_L2_SEL_MASK | IOU_SLCR_MIO_PIN_10_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_10_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_10_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_10_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_10_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_10_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_10_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_11 @ 0XFF18002C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Input, qspi_mi_upper[3]- (QSPI Upper Databus) 1= qspi, Output, qspi_mo_uppe
		[3]- (QSPI Upper Databus)
		PSU_IOU_SLCR_MIO_PIN_11_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_rb_n[1]- (NAND Ready/Busy)
		PSU_IOU_SLCR_MIO_PIN_11_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[11]- (Test Scan Port) = test_scan, Out
		ut, test_scan_out[11]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_11_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[11]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[11]- (GPIO bank 0) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi1, Output, spi1_mo- (MOSI signal) 4= spi1, Input, s
		i1_si- (MOSI signal) 5= ttc2, Output, ttc2_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial o
		tput) 7= trace, Output, tracedq[9]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_11_L3_SEL                                                  0

		Configures MIO Pin 11 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18002C, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_11_L0_SEL_MASK | IOU_SLCR_MIO_PIN_11_L1_SEL_MASK | IOU_SLCR_MIO_PIN_11_L2_SEL_MASK | IOU_SLCR_MIO_PIN_11_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_11_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_11_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_11_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_11_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_11_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_11_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_12 @ 0XFF180030</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= qspi, Output, qspi_sclk_out_upper- (QSPI Upper Clock)
		PSU_IOU_SLCR_MIO_PIN_12_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_dqs_in- (NAND Strobe) 1= nand, Output, nfc_dqs_out- (NAND Strobe
		
		PSU_IOU_SLCR_MIO_PIN_12_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= test_scan, Input, test_scan_in[12]- (Test Scan Port) = test_scan, Out
		ut, test_scan_out[12]- (Test Scan Port) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_12_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[12]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[12]- (GPIO bank 0) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= pjtag, Input, pjtag_tck- (PJTAG TCK) 4= spi0, Input, spi0_sclk_in- (SPI Clock) 4= spi0, Output, spi0_sclk_out- (SPI Cl
		ck) 5= ttc1, Input, ttc1_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace, Output, trac
		dq[10]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_12_L3_SEL                                                  0

		Configures MIO Pin 12 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180030, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_12_L0_SEL_MASK | IOU_SLCR_MIO_PIN_12_L1_SEL_MASK | IOU_SLCR_MIO_PIN_12_L2_SEL_MASK | IOU_SLCR_MIO_PIN_12_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_12_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_12_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_12_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_12_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_12_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_12_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_13 @ 0XFF180034</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_13_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Output, nfc_ce[0]- (NAND chip enable)
		PSU_IOU_SLCR_MIO_PIN_13_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[0]- (8-bit Data bus) = sd0, Output, sdio0_data_out[0]- (8
		bit Data bus) 2= test_scan, Input, test_scan_in[13]- (Test Scan Port) = test_scan, Output, test_scan_out[13]- (Test Scan Port
		 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_13_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[13]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[13]- (GPIO bank 0) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= pjtag, Input, pjtag_tdi- (PJTAG TDI) 4= spi0, Output, spi0_n_ss_out[2]- (SPI Master Selects) 5= ttc1, Output, ttc1_wave
		out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input) 7= trace, Output, tracedq[11]- (Trace Port Dat
		bus)
		PSU_IOU_SLCR_MIO_PIN_13_L3_SEL                                                  0

		Configures MIO Pin 13 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180034, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_13_L0_SEL_MASK | IOU_SLCR_MIO_PIN_13_L1_SEL_MASK | IOU_SLCR_MIO_PIN_13_L2_SEL_MASK | IOU_SLCR_MIO_PIN_13_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_13_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_13_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_13_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_13_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_13_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_13_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_14 @ 0XFF180038</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_14_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Output, nfc_cle- (NAND Command Latch Enable)
		PSU_IOU_SLCR_MIO_PIN_14_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[1]- (8-bit Data bus) = sd0, Output, sdio0_data_out[1]- (8
		bit Data bus) 2= test_scan, Input, test_scan_in[14]- (Test Scan Port) = test_scan, Output, test_scan_out[14]- (Test Scan Port
		 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_14_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[14]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[14]- (GPIO bank 0) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= pjtag, Output, pjtag_tdo- (PJTAG TDO) 4= spi0, Output, spi0_n_ss_out[1]- (SPI Master Selects) 5= ttc0, Input, ttc0_clk_
		n- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Output, tracedq[12]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_14_L3_SEL                                                  0

		Configures MIO Pin 14 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180038, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_14_L0_SEL_MASK | IOU_SLCR_MIO_PIN_14_L1_SEL_MASK | IOU_SLCR_MIO_PIN_14_L2_SEL_MASK | IOU_SLCR_MIO_PIN_14_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_14_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_14_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_14_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_14_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_14_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_14_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_15 @ 0XFF18003C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_15_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Output, nfc_ale- (NAND Address Latch Enable)
		PSU_IOU_SLCR_MIO_PIN_15_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[2]- (8-bit Data bus) = sd0, Output, sdio0_data_out[2]- (8
		bit Data bus) 2= test_scan, Input, test_scan_in[15]- (Test Scan Port) = test_scan, Output, test_scan_out[15]- (Test Scan Port
		 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_15_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[15]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[15]- (GPIO bank 0) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= pjtag, Input, pjtag_tms- (PJTAG TMS) 4= spi0, Input, spi0_n_ss_in- (SPI Master Selects) 4= spi0, Output, spi0_n_ss_out
		0]- (SPI Master Selects) 5= ttc0, Output, ttc0_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter seri
		l output) 7= trace, Output, tracedq[13]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_15_L3_SEL                                                  0

		Configures MIO Pin 15 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18003C, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_15_L0_SEL_MASK | IOU_SLCR_MIO_PIN_15_L1_SEL_MASK | IOU_SLCR_MIO_PIN_15_L2_SEL_MASK | IOU_SLCR_MIO_PIN_15_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_15_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_15_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_15_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_15_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_15_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_15_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_16 @ 0XFF180040</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_16_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_dq_in[0]- (NAND Data Bus) 1= nand, Output, nfc_dq_out[0]- (NAND 
		ata Bus)
		PSU_IOU_SLCR_MIO_PIN_16_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[3]- (8-bit Data bus) = sd0, Output, sdio0_data_out[3]- (8
		bit Data bus) 2= test_scan, Input, test_scan_in[16]- (Test Scan Port) = test_scan, Output, test_scan_out[16]- (Test Scan Port
		 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_16_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[16]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[16]- (GPIO bank 0) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi0, Input, spi0_mi- (MISO signal) 4= spi0, Output, spi0
		so- (MISO signal) 5= ttc3, Input, ttc3_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace
		 Output, tracedq[14]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_16_L3_SEL                                                  0

		Configures MIO Pin 16 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180040, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_16_L0_SEL_MASK | IOU_SLCR_MIO_PIN_16_L1_SEL_MASK | IOU_SLCR_MIO_PIN_16_L2_SEL_MASK | IOU_SLCR_MIO_PIN_16_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_16_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_16_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_16_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_16_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_16_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_16_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_17 @ 0XFF180044</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_17_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_dq_in[1]- (NAND Data Bus) 1= nand, Output, nfc_dq_out[1]- (NAND 
		ata Bus)
		PSU_IOU_SLCR_MIO_PIN_17_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[4]- (8-bit Data bus) = sd0, Output, sdio0_data_out[4]- (8
		bit Data bus) 2= test_scan, Input, test_scan_in[17]- (Test Scan Port) = test_scan, Output, test_scan_out[17]- (Test Scan Port
		 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_17_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[17]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[17]- (GPIO bank 0) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi0, Output, spi0_mo- (MOSI signal) 4= spi0, Input, sp
		0_si- (MOSI signal) 5= ttc3, Output, ttc3_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input)
		7= trace, Output, tracedq[15]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_17_L3_SEL                                                  0

		Configures MIO Pin 17 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180044, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_17_L0_SEL_MASK | IOU_SLCR_MIO_PIN_17_L1_SEL_MASK | IOU_SLCR_MIO_PIN_17_L2_SEL_MASK | IOU_SLCR_MIO_PIN_17_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_17_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_17_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_17_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_17_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_17_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_17_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_18 @ 0XFF180048</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_18_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_dq_in[2]- (NAND Data Bus) 1= nand, Output, nfc_dq_out[2]- (NAND 
		ata Bus)
		PSU_IOU_SLCR_MIO_PIN_18_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[5]- (8-bit Data bus) = sd0, Output, sdio0_data_out[5]- (8
		bit Data bus) 2= test_scan, Input, test_scan_in[18]- (Test Scan Port) = test_scan, Output, test_scan_out[18]- (Test Scan Port
		 3= csu, Input, csu_ext_tamper- (CSU Ext Tamper)
		PSU_IOU_SLCR_MIO_PIN_18_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[18]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[18]- (GPIO bank 0) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi1, Input, spi1_mi- (MISO signal) 4= spi1, Output, spi1_
		o- (MISO signal) 5= ttc2, Input, ttc2_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_18_L3_SEL                                                  0

		Configures MIO Pin 18 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180048, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_18_L0_SEL_MASK | IOU_SLCR_MIO_PIN_18_L1_SEL_MASK | IOU_SLCR_MIO_PIN_18_L2_SEL_MASK | IOU_SLCR_MIO_PIN_18_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_18_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_18_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_18_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_18_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_18_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_18_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_19 @ 0XFF18004C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_19_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_dq_in[3]- (NAND Data Bus) 1= nand, Output, nfc_dq_out[3]- (NAND 
		ata Bus)
		PSU_IOU_SLCR_MIO_PIN_19_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[6]- (8-bit Data bus) = sd0, Output, sdio0_data_out[6]- (8
		bit Data bus) 2= test_scan, Input, test_scan_in[19]- (Test Scan Port) = test_scan, Output, test_scan_out[19]- (Test Scan Port
		 3= csu, Input, csu_ext_tamper- (CSU Ext Tamper)
		PSU_IOU_SLCR_MIO_PIN_19_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[19]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[19]- (GPIO bank 0) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi1, Output, spi1_n_ss_out[2]- (SPI Master Selects) 5
		 ttc2, Output, ttc2_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial output) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_19_L3_SEL                                                  0

		Configures MIO Pin 19 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18004C, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_19_L0_SEL_MASK | IOU_SLCR_MIO_PIN_19_L1_SEL_MASK | IOU_SLCR_MIO_PIN_19_L2_SEL_MASK | IOU_SLCR_MIO_PIN_19_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_19_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_19_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_19_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_19_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_19_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_19_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_20 @ 0XFF180050</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_20_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_dq_in[4]- (NAND Data Bus) 1= nand, Output, nfc_dq_out[4]- (NAND 
		ata Bus)
		PSU_IOU_SLCR_MIO_PIN_20_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[7]- (8-bit Data bus) = sd0, Output, sdio0_data_out[7]- (8
		bit Data bus) 2= test_scan, Input, test_scan_in[20]- (Test Scan Port) = test_scan, Output, test_scan_out[20]- (Test Scan Port
		 3= csu, Input, csu_ext_tamper- (CSU Ext Tamper)
		PSU_IOU_SLCR_MIO_PIN_20_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[20]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[20]- (GPIO bank 0) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi1, Output, spi1_n_ss_out[1]- (SPI Master Selects) 5= t
		c1, Input, ttc1_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_20_L3_SEL                                                  0

		Configures MIO Pin 20 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180050, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_20_L0_SEL_MASK | IOU_SLCR_MIO_PIN_20_L1_SEL_MASK | IOU_SLCR_MIO_PIN_20_L2_SEL_MASK | IOU_SLCR_MIO_PIN_20_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_20_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_20_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_20_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_20_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_20_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_20_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_21 @ 0XFF180054</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_21_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_dq_in[5]- (NAND Data Bus) 1= nand, Output, nfc_dq_out[5]- (NAND 
		ata Bus)
		PSU_IOU_SLCR_MIO_PIN_21_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_cmd_in- (Command Indicator) = sd0, Output, sdio0_cmd_out- (Comman
		 Indicator) 2= test_scan, Input, test_scan_in[21]- (Test Scan Port) = test_scan, Output, test_scan_out[21]- (Test Scan Port) 
		= csu, Input, csu_ext_tamper- (CSU Ext Tamper)
		PSU_IOU_SLCR_MIO_PIN_21_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[21]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[21]- (GPIO bank 0) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi1, Input, spi1_n_ss_in- (SPI Master Selects) 4= spi1
		 Output, spi1_n_ss_out[0]- (SPI Master Selects) 5= ttc1, Output, ttc1_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- 
		UART receiver serial input) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_21_L3_SEL                                                  0

		Configures MIO Pin 21 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180054, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_21_L0_SEL_MASK | IOU_SLCR_MIO_PIN_21_L1_SEL_MASK | IOU_SLCR_MIO_PIN_21_L2_SEL_MASK | IOU_SLCR_MIO_PIN_21_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_21_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_21_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_21_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_21_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_21_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_21_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_22 @ 0XFF180058</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_22_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Output, nfc_we_b- (NAND Write Enable)
		PSU_IOU_SLCR_MIO_PIN_22_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Output, sdio0_clk_out- (SDSDIO clock) 2= test_scan, Input, test_scan_in[22]-
		(Test Scan Port) = test_scan, Output, test_scan_out[22]- (Test Scan Port) 3= csu, Input, csu_ext_tamper- (CSU Ext Tamper)
		PSU_IOU_SLCR_MIO_PIN_22_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[22]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[22]- (GPIO bank 0) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi1, Input, spi1_sclk_in- (SPI Clock) 4= spi1, Output, sp
		1_sclk_out- (SPI Clock) 5= ttc0, Input, ttc0_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= Not 
		sed
		PSU_IOU_SLCR_MIO_PIN_22_L3_SEL                                                  0

		Configures MIO Pin 22 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180058, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_22_L0_SEL_MASK | IOU_SLCR_MIO_PIN_22_L1_SEL_MASK | IOU_SLCR_MIO_PIN_22_L2_SEL_MASK | IOU_SLCR_MIO_PIN_22_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_22_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_22_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_22_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_22_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_22_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_22_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_23 @ 0XFF18005C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_23_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_dq_in[6]- (NAND Data Bus) 1= nand, Output, nfc_dq_out[6]- (NAND 
		ata Bus)
		PSU_IOU_SLCR_MIO_PIN_23_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Output, sdio0_bus_pow- (SD card bus power) 2= test_scan, Input, test_scan_in
		23]- (Test Scan Port) = test_scan, Output, test_scan_out[23]- (Test Scan Port) 3= csu, Input, csu_ext_tamper- (CSU Ext Tamper
		
		PSU_IOU_SLCR_MIO_PIN_23_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[23]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[23]- (GPIO bank 0) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi1, Output, spi1_mo- (MOSI signal) 4= spi1, Input, s
		i1_si- (MOSI signal) 5= ttc0, Output, ttc0_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial o
		tput) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_23_L3_SEL                                                  0

		Configures MIO Pin 23 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18005C, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_23_L0_SEL_MASK | IOU_SLCR_MIO_PIN_23_L1_SEL_MASK | IOU_SLCR_MIO_PIN_23_L2_SEL_MASK | IOU_SLCR_MIO_PIN_23_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_23_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_23_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_23_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_23_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_23_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_23_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_24 @ 0XFF180060</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_24_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_dq_in[7]- (NAND Data Bus) 1= nand, Output, nfc_dq_out[7]- (NAND 
		ata Bus)
		PSU_IOU_SLCR_MIO_PIN_24_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sdio0_cd_n- (SD card detect from connector) 2= test_scan, Input, test
		scan_in[24]- (Test Scan Port) = test_scan, Output, test_scan_out[24]- (Test Scan Port) 3= csu, Input, csu_ext_tamper- (CSU Ex
		 Tamper)
		PSU_IOU_SLCR_MIO_PIN_24_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[24]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[24]- (GPIO bank 0) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= Not Used 5= ttc3, Input, ttc3_clk_in- (TTC Clock) 6= ua1,
		Output, ua1_txd- (UART transmitter serial output) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_24_L3_SEL                                                  0

		Configures MIO Pin 24 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180060, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_24_L0_SEL_MASK | IOU_SLCR_MIO_PIN_24_L1_SEL_MASK | IOU_SLCR_MIO_PIN_24_L2_SEL_MASK | IOU_SLCR_MIO_PIN_24_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_24_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_24_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_24_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_24_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_24_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_24_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_25 @ 0XFF180064</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_25_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Output, nfc_re_n- (NAND Read Enable)
		PSU_IOU_SLCR_MIO_PIN_25_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sdio0_wp- (SD card write protect from connector) 2= test_scan, Input,
		test_scan_in[25]- (Test Scan Port) = test_scan, Output, test_scan_out[25]- (Test Scan Port) 3= csu, Input, csu_ext_tamper- (C
		U Ext Tamper)
		PSU_IOU_SLCR_MIO_PIN_25_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio0, Input, gpio_0_pin_in[25]- (GPIO bank 0) 0= gpio0, Output, gpio_0_pin_out[25]- (GPIO bank 0) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= Not Used 5= ttc3, Output, ttc3_wave_out- (TTC Waveform 
		lock) 6= ua1, Input, ua1_rxd- (UART receiver serial input) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_25_L3_SEL                                                  0

		Configures MIO Pin 25 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180064, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_25_L0_SEL_MASK | IOU_SLCR_MIO_PIN_25_L1_SEL_MASK | IOU_SLCR_MIO_PIN_25_L2_SEL_MASK | IOU_SLCR_MIO_PIN_25_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_25_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_25_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_25_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_25_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_25_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_25_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_26 @ 0XFF180068</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Output, gem0_rgmii_tx_clk- (TX RGMII clock)
		PSU_IOU_SLCR_MIO_PIN_26_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Output, nfc_ce[1]- (NAND chip enable)
		PSU_IOU_SLCR_MIO_PIN_26_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpi[0]- (PMU GPI) 2= test_scan, Input, test_scan_in[26]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[26]- (Test Scan Port) 3= csu, Input, csu_ext_tamper- (CSU Ext Tamper)
		PSU_IOU_SLCR_MIO_PIN_26_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[0]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[0]- (GPIO bank 1) 1= can
		, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL signal
		 3= pjtag, Input, pjtag_tck- (PJTAG TCK) 4= spi0, Input, spi0_sclk_in- (SPI Clock) 4= spi0, Output, spi0_sclk_out- (SPI Clock
		 5= ttc2, Input, ttc2_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Output, tracedq[4]- 
		Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_26_L3_SEL                                                  0

		Configures MIO Pin 26 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180068, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_26_L0_SEL_MASK | IOU_SLCR_MIO_PIN_26_L1_SEL_MASK | IOU_SLCR_MIO_PIN_26_L2_SEL_MASK | IOU_SLCR_MIO_PIN_26_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_26_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_26_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_26_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_26_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_26_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_26_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_27 @ 0XFF18006C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Output, gem0_rgmii_txd[0]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_27_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_rb_n[0]- (NAND Ready/Busy)
		PSU_IOU_SLCR_MIO_PIN_27_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpi[1]- (PMU GPI) 2= test_scan, Input, test_scan_in[27]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[27]- (Test Scan Port) 3= dpaux, Input, dp_aux_data_in- (Dp Aux Data) = dpaux, Outp
		t, dp_aux_data_out- (Dp Aux Data)
		PSU_IOU_SLCR_MIO_PIN_27_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[1]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[1]- (GPIO bank 1) 1= can
		, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA signa
		) 3= pjtag, Input, pjtag_tdi- (PJTAG TDI) 4= spi0, Output, spi0_n_ss_out[2]- (SPI Master Selects) 5= ttc2, Output, ttc2_wave_
		ut- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial output) 7= trace, Output, tracedq[5]- (Trace Port 
		atabus)
		PSU_IOU_SLCR_MIO_PIN_27_L3_SEL                                                  0

		Configures MIO Pin 27 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18006C, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_27_L0_SEL_MASK | IOU_SLCR_MIO_PIN_27_L1_SEL_MASK | IOU_SLCR_MIO_PIN_27_L2_SEL_MASK | IOU_SLCR_MIO_PIN_27_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_27_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_27_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_27_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_27_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_27_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_27_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_28 @ 0XFF180070</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Output, gem0_rgmii_txd[1]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_28_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_rb_n[1]- (NAND Ready/Busy)
		PSU_IOU_SLCR_MIO_PIN_28_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpi[2]- (PMU GPI) 2= test_scan, Input, test_scan_in[28]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[28]- (Test Scan Port) 3= dpaux, Input, dp_hot_plug_detect- (Dp Aux Hot Plug)
		PSU_IOU_SLCR_MIO_PIN_28_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[2]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[2]- (GPIO bank 1) 1= can
		, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL signa
		) 3= pjtag, Output, pjtag_tdo- (PJTAG TDO) 4= spi0, Output, spi0_n_ss_out[1]- (SPI Master Selects) 5= ttc1, Input, ttc1_clk_i
		- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace, Output, tracedq[6]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_28_L3_SEL                                                  0

		Configures MIO Pin 28 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180070, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_28_L0_SEL_MASK | IOU_SLCR_MIO_PIN_28_L1_SEL_MASK | IOU_SLCR_MIO_PIN_28_L2_SEL_MASK | IOU_SLCR_MIO_PIN_28_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_28_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_28_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_28_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_28_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_28_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_28_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_29 @ 0XFF180074</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Output, gem0_rgmii_txd[2]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_29_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= pcie, Input, pcie_reset_n- (PCIE Reset signal)
		PSU_IOU_SLCR_MIO_PIN_29_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpi[3]- (PMU GPI) 2= test_scan, Input, test_scan_in[29]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[29]- (Test Scan Port) 3= dpaux, Input, dp_aux_data_in- (Dp Aux Data) = dpaux, Outp
		t, dp_aux_data_out- (Dp Aux Data)
		PSU_IOU_SLCR_MIO_PIN_29_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[3]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[3]- (GPIO bank 1) 1= can
		, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA signal
		 3= pjtag, Input, pjtag_tms- (PJTAG TMS) 4= spi0, Input, spi0_n_ss_in- (SPI Master Selects) 4= spi0, Output, spi0_n_ss_out[0]
		 (SPI Master Selects) 5= ttc1, Output, ttc1_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial inpu
		) 7= trace, Output, tracedq[7]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_29_L3_SEL                                                  4

		Configures MIO Pin 29 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180074, 0x000000FEU ,0x00000080U)  */
		RegMask = (IOU_SLCR_MIO_PIN_29_L0_SEL_MASK | IOU_SLCR_MIO_PIN_29_L1_SEL_MASK | IOU_SLCR_MIO_PIN_29_L2_SEL_MASK | IOU_SLCR_MIO_PIN_29_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_29_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_29_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_29_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_29_L2_SEL_SHIFT
			| 0x00000004U << IOU_SLCR_MIO_PIN_29_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_29_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_30 @ 0XFF180078</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Output, gem0_rgmii_txd[3]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_30_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= pcie, Input, pcie_reset_n- (PCIE Reset signal)
		PSU_IOU_SLCR_MIO_PIN_30_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpi[4]- (PMU GPI) 2= test_scan, Input, test_scan_in[30]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[30]- (Test Scan Port) 3= dpaux, Input, dp_hot_plug_detect- (Dp Aux Hot Plug)
		PSU_IOU_SLCR_MIO_PIN_30_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[4]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[4]- (GPIO bank 1) 1= can
		, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL signal
		 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi0, Input, spi0_mi- (MISO signal) 4= spi0, Output, spi0_so
		 (MISO signal) 5= ttc0, Input, ttc0_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Output
		 tracedq[8]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_30_L3_SEL                                                  0

		Configures MIO Pin 30 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180078, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_30_L0_SEL_MASK | IOU_SLCR_MIO_PIN_30_L1_SEL_MASK | IOU_SLCR_MIO_PIN_30_L2_SEL_MASK | IOU_SLCR_MIO_PIN_30_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_30_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_30_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_30_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_30_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_30_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_30_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_31 @ 0XFF18007C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Output, gem0_rgmii_tx_ctl- (TX RGMII control)
		PSU_IOU_SLCR_MIO_PIN_31_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= pcie, Input, pcie_reset_n- (PCIE Reset signal)
		PSU_IOU_SLCR_MIO_PIN_31_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpi[5]- (PMU GPI) 2= test_scan, Input, test_scan_in[31]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[31]- (Test Scan Port) 3= csu, Input, csu_ext_tamper- (CSU Ext Tamper)
		PSU_IOU_SLCR_MIO_PIN_31_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[5]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[5]- (GPIO bank 1) 1= can
		, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA signa
		) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi0, Output, spi0_mo- (MOSI signal) 4= spi0, Input, spi
		_si- (MOSI signal) 5= ttc0, Output, ttc0_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial out
		ut) 7= trace, Output, tracedq[9]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_31_L3_SEL                                                  0

		Configures MIO Pin 31 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18007C, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_31_L0_SEL_MASK | IOU_SLCR_MIO_PIN_31_L1_SEL_MASK | IOU_SLCR_MIO_PIN_31_L2_SEL_MASK | IOU_SLCR_MIO_PIN_31_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_31_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_31_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_31_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_31_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_31_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_31_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_32 @ 0XFF180080</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Input, gem0_rgmii_rx_clk- (RX RGMII clock)
		PSU_IOU_SLCR_MIO_PIN_32_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= nand, Input, nfc_dqs_in- (NAND Strobe) 1= nand, Output, nfc_dqs_out- (NAND Strobe
		
		PSU_IOU_SLCR_MIO_PIN_32_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpo[0]- (PMU GPI) 2= test_scan, Input, test_scan_in[32]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[32]- (Test Scan Port) 3= csu, Input, csu_ext_tamper- (CSU Ext Tamper)
		PSU_IOU_SLCR_MIO_PIN_32_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[6]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[6]- (GPIO bank 1) 1= can
		, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL signa
		) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi1, Input, spi1_sclk_in- (SPI Clock) 4= spi1, Output, spi
		_sclk_out- (SPI Clock) 5= ttc3, Input, ttc3_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= 
		race, Output, tracedq[10]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_32_L3_SEL                                                  0

		Configures MIO Pin 32 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180080, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_32_L0_SEL_MASK | IOU_SLCR_MIO_PIN_32_L1_SEL_MASK | IOU_SLCR_MIO_PIN_32_L2_SEL_MASK | IOU_SLCR_MIO_PIN_32_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_32_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_32_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_32_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_32_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_32_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_32_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_33 @ 0XFF180084</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Input, gem0_rgmii_rxd[0]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_33_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= pcie, Input, pcie_reset_n- (PCIE Reset signal)
		PSU_IOU_SLCR_MIO_PIN_33_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpo[1]- (PMU GPI) 2= test_scan, Input, test_scan_in[33]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[33]- (Test Scan Port) 3= csu, Input, csu_ext_tamper- (CSU Ext Tamper)
		PSU_IOU_SLCR_MIO_PIN_33_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[7]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[7]- (GPIO bank 1) 1= can
		, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA signal
		 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi1, Output, spi1_n_ss_out[2]- (SPI Master Selects) 5= t
		c3, Output, ttc3_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input) 7= trace, Output, traced
		[11]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_33_L3_SEL                                                  0

		Configures MIO Pin 33 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180084, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_33_L0_SEL_MASK | IOU_SLCR_MIO_PIN_33_L1_SEL_MASK | IOU_SLCR_MIO_PIN_33_L2_SEL_MASK | IOU_SLCR_MIO_PIN_33_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_33_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_33_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_33_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_33_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_33_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_33_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_34 @ 0XFF180088</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Input, gem0_rgmii_rxd[1]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_34_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= pcie, Input, pcie_reset_n- (PCIE Reset signal)
		PSU_IOU_SLCR_MIO_PIN_34_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpo[2]- (PMU GPI) 2= test_scan, Input, test_scan_in[34]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[34]- (Test Scan Port) 3= dpaux, Input, dp_aux_data_in- (Dp Aux Data) = dpaux, Outp
		t, dp_aux_data_out- (Dp Aux Data)
		PSU_IOU_SLCR_MIO_PIN_34_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[8]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[8]- (GPIO bank 1) 1= can
		, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL signal
		 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi1, Output, spi1_n_ss_out[1]- (SPI Master Selects) 5= ttc2
		 Input, ttc2_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Output, tracedq[12]- (Trace P
		rt Databus)
		PSU_IOU_SLCR_MIO_PIN_34_L3_SEL                                                  0

		Configures MIO Pin 34 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180088, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_34_L0_SEL_MASK | IOU_SLCR_MIO_PIN_34_L1_SEL_MASK | IOU_SLCR_MIO_PIN_34_L2_SEL_MASK | IOU_SLCR_MIO_PIN_34_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_34_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_34_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_34_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_34_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_34_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_34_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_35 @ 0XFF18008C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Input, gem0_rgmii_rxd[2]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_35_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= pcie, Input, pcie_reset_n- (PCIE Reset signal)
		PSU_IOU_SLCR_MIO_PIN_35_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpo[3]- (PMU GPI) 2= test_scan, Input, test_scan_in[35]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[35]- (Test Scan Port) 3= dpaux, Input, dp_hot_plug_detect- (Dp Aux Hot Plug)
		PSU_IOU_SLCR_MIO_PIN_35_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[9]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[9]- (GPIO bank 1) 1= can
		, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA signa
		) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi1, Input, spi1_n_ss_in- (SPI Master Selects) 4= spi1,
		Output, spi1_n_ss_out[0]- (SPI Master Selects) 5= ttc2, Output, ttc2_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- 
		UART transmitter serial output) 7= trace, Output, tracedq[13]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_35_L3_SEL                                                  4

		Configures MIO Pin 35 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18008C, 0x000000FEU ,0x00000080U)  */
		RegMask = (IOU_SLCR_MIO_PIN_35_L0_SEL_MASK | IOU_SLCR_MIO_PIN_35_L1_SEL_MASK | IOU_SLCR_MIO_PIN_35_L2_SEL_MASK | IOU_SLCR_MIO_PIN_35_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_35_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_35_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_35_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_35_L2_SEL_SHIFT
			| 0x00000004U << IOU_SLCR_MIO_PIN_35_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_35_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_36 @ 0XFF180090</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Input, gem0_rgmii_rxd[3]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_36_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= pcie, Input, pcie_reset_n- (PCIE Reset signal)
		PSU_IOU_SLCR_MIO_PIN_36_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpo[4]- (PMU GPI) 2= test_scan, Input, test_scan_in[36]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[36]- (Test Scan Port) 3= dpaux, Input, dp_aux_data_in- (Dp Aux Data) = dpaux, Outp
		t, dp_aux_data_out- (Dp Aux Data)
		PSU_IOU_SLCR_MIO_PIN_36_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[10]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[10]- (GPIO bank 1) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi1, Input, spi1_mi- (MISO signal) 4= spi1, Output, spi1
		so- (MISO signal) 5= ttc1, Input, ttc1_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace
		 Output, tracedq[14]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_36_L3_SEL                                                  0

		Configures MIO Pin 36 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180090, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_36_L0_SEL_MASK | IOU_SLCR_MIO_PIN_36_L1_SEL_MASK | IOU_SLCR_MIO_PIN_36_L2_SEL_MASK | IOU_SLCR_MIO_PIN_36_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_36_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_36_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_36_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_36_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_36_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_36_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_37 @ 0XFF180094</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem0, Input, gem0_rgmii_rx_ctl- (RX RGMII control )
		PSU_IOU_SLCR_MIO_PIN_37_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= pcie, Input, pcie_reset_n- (PCIE Reset signal)
		PSU_IOU_SLCR_MIO_PIN_37_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= pmu, Input, pmu_gpo[5]- (PMU GPI) 2= test_scan, Input, test_scan_in[37]- (Test Sc
		n Port) = test_scan, Output, test_scan_out[37]- (Test Scan Port) 3= dpaux, Input, dp_hot_plug_detect- (Dp Aux Hot Plug)
		PSU_IOU_SLCR_MIO_PIN_37_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[11]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[11]- (GPIO bank 1) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi1, Output, spi1_mo- (MOSI signal) 4= spi1, Input, sp
		1_si- (MOSI signal) 5= ttc1, Output, ttc1_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input)
		7= trace, Output, tracedq[15]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_37_L3_SEL                                                  0

		Configures MIO Pin 37 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180094, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_37_L0_SEL_MASK | IOU_SLCR_MIO_PIN_37_L1_SEL_MASK | IOU_SLCR_MIO_PIN_37_L2_SEL_MASK | IOU_SLCR_MIO_PIN_37_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_37_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_37_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_37_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_37_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_37_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_37_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_38 @ 0XFF180098</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Output, gem1_rgmii_tx_clk- (TX RGMII clock)
		PSU_IOU_SLCR_MIO_PIN_38_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_38_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Output, sdio0_clk_out- (SDSDIO clock) 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_38_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[12]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[12]- (GPIO bank 1) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= pjtag, Input, pjtag_tck- (PJTAG TCK) 4= spi0, Input, spi0_sclk_in- (SPI Clock) 4= spi0, Output, spi0_sclk_out- (SPI Clo
		k) 5= ttc0, Input, ttc0_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Output, trace_clk-
		(Trace Port Clock)
		PSU_IOU_SLCR_MIO_PIN_38_L3_SEL                                                  0

		Configures MIO Pin 38 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180098, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_38_L0_SEL_MASK | IOU_SLCR_MIO_PIN_38_L1_SEL_MASK | IOU_SLCR_MIO_PIN_38_L2_SEL_MASK | IOU_SLCR_MIO_PIN_38_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_38_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_38_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_38_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_38_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_38_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_38_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_39 @ 0XFF18009C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Output, gem1_rgmii_txd[0]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_39_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_39_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sdio0_cd_n- (SD card detect from connector) 2= sd1, Input, sd1_data_i
		[4]- (8-bit Data bus) = sd1, Output, sdio1_data_out[4]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_39_L2_SEL                                                  2

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[13]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[13]- (GPIO bank 1) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= pjtag, Input, pjtag_tdi- (PJTAG TDI) 4= spi0, Output, spi0_n_ss_out[2]- (SPI Master Selects) 5= ttc0, Output, ttc0_wav
		_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial output) 7= trace, Output, trace_ctl- (Trace Port
		Control Signal)
		PSU_IOU_SLCR_MIO_PIN_39_L3_SEL                                                  0

		Configures MIO Pin 39 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18009C, 0x000000FEU ,0x00000010U)  */
		RegMask = (IOU_SLCR_MIO_PIN_39_L0_SEL_MASK | IOU_SLCR_MIO_PIN_39_L1_SEL_MASK | IOU_SLCR_MIO_PIN_39_L2_SEL_MASK | IOU_SLCR_MIO_PIN_39_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_39_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_39_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_39_L1_SEL_SHIFT
			| 0x00000002U << IOU_SLCR_MIO_PIN_39_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_39_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_39_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_40 @ 0XFF1800A0</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Output, gem1_rgmii_txd[1]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_40_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_40_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_cmd_in- (Command Indicator) = sd0, Output, sdio0_cmd_out- (Comman
		 Indicator) 2= sd1, Input, sd1_data_in[5]- (8-bit Data bus) = sd1, Output, sdio1_data_out[5]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_40_L2_SEL                                                  2

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[14]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[14]- (GPIO bank 1) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= pjtag, Output, pjtag_tdo- (PJTAG TDO) 4= spi0, Output, spi0_n_ss_out[1]- (SPI Master Selects) 5= ttc3, Input, ttc3_clk
		in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace, Output, tracedq[0]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_40_L3_SEL                                                  0

		Configures MIO Pin 40 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800A0, 0x000000FEU ,0x00000010U)  */
		RegMask = (IOU_SLCR_MIO_PIN_40_L0_SEL_MASK | IOU_SLCR_MIO_PIN_40_L1_SEL_MASK | IOU_SLCR_MIO_PIN_40_L2_SEL_MASK | IOU_SLCR_MIO_PIN_40_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_40_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_40_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_40_L1_SEL_SHIFT
			| 0x00000002U << IOU_SLCR_MIO_PIN_40_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_40_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_40_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_41 @ 0XFF1800A4</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Output, gem1_rgmii_txd[2]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_41_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_41_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[0]- (8-bit Data bus) = sd0, Output, sdio0_data_out[0]- (8
		bit Data bus) 2= sd1, Input, sd1_data_in[6]- (8-bit Data bus) = sd1, Output, sdio1_data_out[6]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_41_L2_SEL                                                  2

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[15]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[15]- (GPIO bank 1) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= pjtag, Input, pjtag_tms- (PJTAG TMS) 4= spi0, Input, spi0_n_ss_in- (SPI Master Selects) 4= spi0, Output, spi0_n_ss_out[
		]- (SPI Master Selects) 5= ttc3, Output, ttc3_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial in
		ut) 7= trace, Output, tracedq[1]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_41_L3_SEL                                                  0

		Configures MIO Pin 41 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800A4, 0x000000FEU ,0x00000010U)  */
		RegMask = (IOU_SLCR_MIO_PIN_41_L0_SEL_MASK | IOU_SLCR_MIO_PIN_41_L1_SEL_MASK | IOU_SLCR_MIO_PIN_41_L2_SEL_MASK | IOU_SLCR_MIO_PIN_41_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_41_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_41_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_41_L1_SEL_SHIFT
			| 0x00000002U << IOU_SLCR_MIO_PIN_41_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_41_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_41_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_42 @ 0XFF1800A8</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Output, gem1_rgmii_txd[3]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_42_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_42_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[1]- (8-bit Data bus) = sd0, Output, sdio0_data_out[1]- (8
		bit Data bus) 2= sd1, Input, sd1_data_in[7]- (8-bit Data bus) = sd1, Output, sdio1_data_out[7]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_42_L2_SEL                                                  2

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[16]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[16]- (GPIO bank 1) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi0, Input, spi0_mi- (MISO signal) 4= spi0, Output, spi0_
		o- (MISO signal) 5= ttc2, Input, ttc2_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Outp
		t, tracedq[2]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_42_L3_SEL                                                  0

		Configures MIO Pin 42 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800A8, 0x000000FEU ,0x00000010U)  */
		RegMask = (IOU_SLCR_MIO_PIN_42_L0_SEL_MASK | IOU_SLCR_MIO_PIN_42_L1_SEL_MASK | IOU_SLCR_MIO_PIN_42_L2_SEL_MASK | IOU_SLCR_MIO_PIN_42_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_42_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_42_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_42_L1_SEL_SHIFT
			| 0x00000002U << IOU_SLCR_MIO_PIN_42_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_42_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_42_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_43 @ 0XFF1800AC</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Output, gem1_rgmii_tx_ctl- (TX RGMII control)
		PSU_IOU_SLCR_MIO_PIN_43_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_43_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[2]- (8-bit Data bus) = sd0, Output, sdio0_data_out[2]- (8
		bit Data bus) 2= sd1, Output, sdio1_bus_pow- (SD card bus power) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_43_L2_SEL                                                  2

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[17]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[17]- (GPIO bank 1) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi0, Output, spi0_mo- (MOSI signal) 4= spi0, Input, s
		i0_si- (MOSI signal) 5= ttc2, Output, ttc2_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial o
		tput) 7= trace, Output, tracedq[3]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_43_L3_SEL                                                  0

		Configures MIO Pin 43 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800AC, 0x000000FEU ,0x00000010U)  */
		RegMask = (IOU_SLCR_MIO_PIN_43_L0_SEL_MASK | IOU_SLCR_MIO_PIN_43_L1_SEL_MASK | IOU_SLCR_MIO_PIN_43_L2_SEL_MASK | IOU_SLCR_MIO_PIN_43_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_43_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_43_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_43_L1_SEL_SHIFT
			| 0x00000002U << IOU_SLCR_MIO_PIN_43_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_43_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_43_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_44 @ 0XFF1800B0</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Input, gem1_rgmii_rx_clk- (RX RGMII clock)
		PSU_IOU_SLCR_MIO_PIN_44_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_44_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[3]- (8-bit Data bus) = sd0, Output, sdio0_data_out[3]- (8
		bit Data bus) 2= sd1, Input, sdio1_wp- (SD card write protect from connector) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_44_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[18]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[18]- (GPIO bank 1) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi1, Input, spi1_sclk_in- (SPI Clock) 4= spi1, Output, s
		i1_sclk_out- (SPI Clock) 5= ttc1, Input, ttc1_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7
		 Not Used
		PSU_IOU_SLCR_MIO_PIN_44_L3_SEL                                                  0

		Configures MIO Pin 44 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800B0, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_44_L0_SEL_MASK | IOU_SLCR_MIO_PIN_44_L1_SEL_MASK | IOU_SLCR_MIO_PIN_44_L2_SEL_MASK | IOU_SLCR_MIO_PIN_44_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_44_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_44_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_44_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_44_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_44_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_44_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_45 @ 0XFF1800B4</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Input, gem1_rgmii_rxd[0]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_45_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_45_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[4]- (8-bit Data bus) = sd0, Output, sdio0_data_out[4]- (8
		bit Data bus) 2= sd1, Input, sdio1_cd_n- (SD card detect from connector) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_45_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[19]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[19]- (GPIO bank 1) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi1, Output, spi1_n_ss_out[2]- (SPI Master Selects) 5=
		ttc1, Output, ttc1_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_45_L3_SEL                                                  0

		Configures MIO Pin 45 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800B4, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_45_L0_SEL_MASK | IOU_SLCR_MIO_PIN_45_L1_SEL_MASK | IOU_SLCR_MIO_PIN_45_L2_SEL_MASK | IOU_SLCR_MIO_PIN_45_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_45_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_45_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_45_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_45_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_45_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_45_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_46 @ 0XFF1800B8</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Input, gem1_rgmii_rxd[1]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_46_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_46_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[5]- (8-bit Data bus) = sd0, Output, sdio0_data_out[5]- (8
		bit Data bus) 2= sd1, Input, sd1_data_in[0]- (8-bit Data bus) = sd1, Output, sdio1_data_out[0]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_46_L2_SEL                                                  2

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[20]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[20]- (GPIO bank 1) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi1, Output, spi1_n_ss_out[1]- (SPI Master Selects) 5= tt
		0, Input, ttc0_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_46_L3_SEL                                                  0

		Configures MIO Pin 46 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800B8, 0x000000FEU ,0x00000010U)  */
		RegMask = (IOU_SLCR_MIO_PIN_46_L0_SEL_MASK | IOU_SLCR_MIO_PIN_46_L1_SEL_MASK | IOU_SLCR_MIO_PIN_46_L2_SEL_MASK | IOU_SLCR_MIO_PIN_46_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_46_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_46_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_46_L1_SEL_SHIFT
			| 0x00000002U << IOU_SLCR_MIO_PIN_46_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_46_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_46_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_47 @ 0XFF1800BC</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Input, gem1_rgmii_rxd[2]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_47_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_47_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[6]- (8-bit Data bus) = sd0, Output, sdio0_data_out[6]- (8
		bit Data bus) 2= sd1, Input, sd1_data_in[1]- (8-bit Data bus) = sd1, Output, sdio1_data_out[1]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_47_L2_SEL                                                  2

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[21]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[21]- (GPIO bank 1) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi1, Input, spi1_n_ss_in- (SPI Master Selects) 4= spi
		, Output, spi1_n_ss_out[0]- (SPI Master Selects) 5= ttc0, Output, ttc0_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd
		 (UART transmitter serial output) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_47_L3_SEL                                                  0

		Configures MIO Pin 47 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800BC, 0x000000FEU ,0x00000010U)  */
		RegMask = (IOU_SLCR_MIO_PIN_47_L0_SEL_MASK | IOU_SLCR_MIO_PIN_47_L1_SEL_MASK | IOU_SLCR_MIO_PIN_47_L2_SEL_MASK | IOU_SLCR_MIO_PIN_47_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_47_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_47_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_47_L1_SEL_SHIFT
			| 0x00000002U << IOU_SLCR_MIO_PIN_47_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_47_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_47_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_48 @ 0XFF1800C0</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Input, gem1_rgmii_rxd[3]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_48_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_48_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[7]- (8-bit Data bus) = sd0, Output, sdio0_data_out[7]- (8
		bit Data bus) 2= sd1, Input, sd1_data_in[2]- (8-bit Data bus) = sd1, Output, sdio1_data_out[2]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_48_L2_SEL                                                  2

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[22]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[22]- (GPIO bank 1) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi1, Input, spi1_mi- (MISO signal) 4= spi1, Output, spi1
		so- (MISO signal) 5= ttc3, Input, ttc3_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= Not U
		ed
		PSU_IOU_SLCR_MIO_PIN_48_L3_SEL                                                  0

		Configures MIO Pin 48 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800C0, 0x000000FEU ,0x00000010U)  */
		RegMask = (IOU_SLCR_MIO_PIN_48_L0_SEL_MASK | IOU_SLCR_MIO_PIN_48_L1_SEL_MASK | IOU_SLCR_MIO_PIN_48_L2_SEL_MASK | IOU_SLCR_MIO_PIN_48_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_48_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_48_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_48_L1_SEL_SHIFT
			| 0x00000002U << IOU_SLCR_MIO_PIN_48_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_48_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_48_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_49 @ 0XFF1800C4</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem1, Input, gem1_rgmii_rx_ctl- (RX RGMII control )
		PSU_IOU_SLCR_MIO_PIN_49_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_49_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Output, sdio0_bus_pow- (SD card bus power) 2= sd1, Input, sd1_data_in[3]- (8
		bit Data bus) = sd1, Output, sdio1_data_out[3]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_49_L2_SEL                                                  2

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[23]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[23]- (GPIO bank 1) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi1, Output, spi1_mo- (MOSI signal) 4= spi1, Input, sp
		1_si- (MOSI signal) 5= ttc3, Output, ttc3_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input)
		7= Not Used
		PSU_IOU_SLCR_MIO_PIN_49_L3_SEL                                                  0

		Configures MIO Pin 49 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800C4, 0x000000FEU ,0x00000010U)  */
		RegMask = (IOU_SLCR_MIO_PIN_49_L0_SEL_MASK | IOU_SLCR_MIO_PIN_49_L1_SEL_MASK | IOU_SLCR_MIO_PIN_49_L2_SEL_MASK | IOU_SLCR_MIO_PIN_49_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_49_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_49_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_49_L1_SEL_SHIFT
			| 0x00000002U << IOU_SLCR_MIO_PIN_49_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_49_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_49_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_50 @ 0XFF1800C8</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem_tsu, Input, gem_tsu_clk- (TSU clock)
		PSU_IOU_SLCR_MIO_PIN_50_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_50_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sdio0_wp- (SD card write protect from connector) 2= sd1, Input, sd1_c
		d_in- (Command Indicator) = sd1, Output, sdio1_cmd_out- (Command Indicator) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_50_L2_SEL                                                  2

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[24]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[24]- (GPIO bank 1) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= mdio1, Output, gem1_mdc- (MDIO Clock) 5= ttc2, Input, ttc2
		clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_50_L3_SEL                                                  0

		Configures MIO Pin 50 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800C8, 0x000000FEU ,0x00000010U)  */
		RegMask = (IOU_SLCR_MIO_PIN_50_L0_SEL_MASK | IOU_SLCR_MIO_PIN_50_L1_SEL_MASK | IOU_SLCR_MIO_PIN_50_L2_SEL_MASK | IOU_SLCR_MIO_PIN_50_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_50_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_50_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_50_L1_SEL_SHIFT
			| 0x00000002U << IOU_SLCR_MIO_PIN_50_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_50_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_50_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_51 @ 0XFF1800CC</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem_tsu, Input, gem_tsu_clk- (TSU clock)
		PSU_IOU_SLCR_MIO_PIN_51_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_51_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= sd1, Output, sdio1_clk_out- (SDSDIO clock) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_51_L2_SEL                                                  2

		Level 3 Mux Select 0= gpio1, Input, gpio_1_pin_in[25]- (GPIO bank 1) 0= gpio1, Output, gpio_1_pin_out[25]- (GPIO bank 1) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= mdio1, Input, gem1_mdio_in- (MDIO Data) 4= mdio1, Outp
		t, gem1_mdio_out- (MDIO Data) 5= ttc2, Output, ttc2_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter
		serial output) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_51_L3_SEL                                                  0

		Configures MIO Pin 51 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800CC, 0x000000FEU ,0x00000010U)  */
		RegMask = (IOU_SLCR_MIO_PIN_51_L0_SEL_MASK | IOU_SLCR_MIO_PIN_51_L1_SEL_MASK | IOU_SLCR_MIO_PIN_51_L2_SEL_MASK | IOU_SLCR_MIO_PIN_51_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_51_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_51_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_51_L1_SEL_SHIFT
			| 0x00000002U << IOU_SLCR_MIO_PIN_51_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_51_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_51_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_52 @ 0XFF1800D0</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Output, gem2_rgmii_tx_clk- (TX RGMII clock)
		PSU_IOU_SLCR_MIO_PIN_52_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Input, usb0_ulpi_clk_in- (ULPI Clock)
		PSU_IOU_SLCR_MIO_PIN_52_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_52_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[0]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[0]- (GPIO bank 2) 1= can
		, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL signa
		) 3= pjtag, Input, pjtag_tck- (PJTAG TCK) 4= spi0, Input, spi0_sclk_in- (SPI Clock) 4= spi0, Output, spi0_sclk_out- (SPI Cloc
		) 5= ttc1, Input, ttc1_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace, Output, trace_
		lk- (Trace Port Clock)
		PSU_IOU_SLCR_MIO_PIN_52_L3_SEL                                                  0

		Configures MIO Pin 52 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800D0, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_52_L0_SEL_MASK | IOU_SLCR_MIO_PIN_52_L1_SEL_MASK | IOU_SLCR_MIO_PIN_52_L2_SEL_MASK | IOU_SLCR_MIO_PIN_52_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_52_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_52_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_52_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_52_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_52_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_52_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_53 @ 0XFF1800D4</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Output, gem2_rgmii_txd[0]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_53_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Input, usb0_ulpi_dir- (Data bus direction control)
		PSU_IOU_SLCR_MIO_PIN_53_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_53_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[1]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[1]- (GPIO bank 2) 1= can
		, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA signal
		 3= pjtag, Input, pjtag_tdi- (PJTAG TDI) 4= spi0, Output, spi0_n_ss_out[2]- (SPI Master Selects) 5= ttc1, Output, ttc1_wave_o
		t- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input) 7= trace, Output, trace_ctl- (Trace Port Control
		Signal)
		PSU_IOU_SLCR_MIO_PIN_53_L3_SEL                                                  0

		Configures MIO Pin 53 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800D4, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_53_L0_SEL_MASK | IOU_SLCR_MIO_PIN_53_L1_SEL_MASK | IOU_SLCR_MIO_PIN_53_L2_SEL_MASK | IOU_SLCR_MIO_PIN_53_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_53_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_53_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_53_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_53_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_53_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_53_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_54 @ 0XFF1800D8</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Output, gem2_rgmii_txd[1]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_54_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Input, usb0_ulpi_rx_data[2]- (ULPI data bus) 1= usb0, Output, usb0_ulpi_tx_
		ata[2]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_54_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_54_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[2]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[2]- (GPIO bank 2) 1= can
		, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL signal
		 3= pjtag, Output, pjtag_tdo- (PJTAG TDO) 4= spi0, Output, spi0_n_ss_out[1]- (SPI Master Selects) 5= ttc0, Input, ttc0_clk_in
		 (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Output, tracedq[0]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_54_L3_SEL                                                  0

		Configures MIO Pin 54 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800D8, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_54_L0_SEL_MASK | IOU_SLCR_MIO_PIN_54_L1_SEL_MASK | IOU_SLCR_MIO_PIN_54_L2_SEL_MASK | IOU_SLCR_MIO_PIN_54_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_54_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_54_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_54_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_54_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_54_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_54_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_55 @ 0XFF1800DC</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Output, gem2_rgmii_txd[2]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_55_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Input, usb0_ulpi_nxt- (Data flow control signal from the PHY)
		PSU_IOU_SLCR_MIO_PIN_55_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_55_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[3]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[3]- (GPIO bank 2) 1= can
		, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA signa
		) 3= pjtag, Input, pjtag_tms- (PJTAG TMS) 4= spi0, Input, spi0_n_ss_in- (SPI Master Selects) 4= spi0, Output, spi0_n_ss_out[0
		- (SPI Master Selects) 5= ttc0, Output, ttc0_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial
		output) 7= trace, Output, tracedq[1]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_55_L3_SEL                                                  0

		Configures MIO Pin 55 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800DC, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_55_L0_SEL_MASK | IOU_SLCR_MIO_PIN_55_L1_SEL_MASK | IOU_SLCR_MIO_PIN_55_L2_SEL_MASK | IOU_SLCR_MIO_PIN_55_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_55_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_55_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_55_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_55_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_55_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_55_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_56 @ 0XFF1800E0</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Output, gem2_rgmii_txd[3]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_56_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Input, usb0_ulpi_rx_data[0]- (ULPI data bus) 1= usb0, Output, usb0_ulpi_tx_
		ata[0]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_56_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_56_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[4]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[4]- (GPIO bank 2) 1= can
		, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL signa
		) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi0, Input, spi0_mi- (MISO signal) 4= spi0, Output, spi0_s
		- (MISO signal) 5= ttc3, Input, ttc3_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace, 
		utput, tracedq[2]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_56_L3_SEL                                                  0

		Configures MIO Pin 56 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800E0, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_56_L0_SEL_MASK | IOU_SLCR_MIO_PIN_56_L1_SEL_MASK | IOU_SLCR_MIO_PIN_56_L2_SEL_MASK | IOU_SLCR_MIO_PIN_56_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_56_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_56_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_56_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_56_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_56_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_56_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_57 @ 0XFF1800E4</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Output, gem2_rgmii_tx_ctl- (TX RGMII control)
		PSU_IOU_SLCR_MIO_PIN_57_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Input, usb0_ulpi_rx_data[1]- (ULPI data bus) 1= usb0, Output, usb0_ulpi_tx_
		ata[1]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_57_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_57_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[5]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[5]- (GPIO bank 2) 1= can
		, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA signal
		 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi0, Output, spi0_mo- (MOSI signal) 4= spi0, Input, spi0
		si- (MOSI signal) 5= ttc3, Output, ttc3_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input) 7
		 trace, Output, tracedq[3]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_57_L3_SEL                                                  0

		Configures MIO Pin 57 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800E4, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_57_L0_SEL_MASK | IOU_SLCR_MIO_PIN_57_L1_SEL_MASK | IOU_SLCR_MIO_PIN_57_L2_SEL_MASK | IOU_SLCR_MIO_PIN_57_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_57_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_57_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_57_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_57_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_57_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_57_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_58 @ 0XFF1800E8</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Input, gem2_rgmii_rx_clk- (RX RGMII clock)
		PSU_IOU_SLCR_MIO_PIN_58_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Output, usb0_ulpi_stp- (Asserted to end or interrupt transfers)
		PSU_IOU_SLCR_MIO_PIN_58_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_58_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[6]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[6]- (GPIO bank 2) 1= can
		, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL signal
		 3= pjtag, Input, pjtag_tck- (PJTAG TCK) 4= spi1, Input, spi1_sclk_in- (SPI Clock) 4= spi1, Output, spi1_sclk_out- (SPI Clock
		 5= ttc2, Input, ttc2_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Output, tracedq[4]- 
		Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_58_L3_SEL                                                  0

		Configures MIO Pin 58 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800E8, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_58_L0_SEL_MASK | IOU_SLCR_MIO_PIN_58_L1_SEL_MASK | IOU_SLCR_MIO_PIN_58_L2_SEL_MASK | IOU_SLCR_MIO_PIN_58_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_58_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_58_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_58_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_58_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_58_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_58_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_59 @ 0XFF1800EC</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Input, gem2_rgmii_rxd[0]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_59_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Input, usb0_ulpi_rx_data[3]- (ULPI data bus) 1= usb0, Output, usb0_ulpi_tx_
		ata[3]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_59_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_59_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[7]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[7]- (GPIO bank 2) 1= can
		, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA signa
		) 3= pjtag, Input, pjtag_tdi- (PJTAG TDI) 4= spi1, Output, spi1_n_ss_out[2]- (SPI Master Selects) 5= ttc2, Output, ttc2_wave_
		ut- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial output) 7= trace, Output, tracedq[5]- (Trace Port 
		atabus)
		PSU_IOU_SLCR_MIO_PIN_59_L3_SEL                                                  0

		Configures MIO Pin 59 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800EC, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_59_L0_SEL_MASK | IOU_SLCR_MIO_PIN_59_L1_SEL_MASK | IOU_SLCR_MIO_PIN_59_L2_SEL_MASK | IOU_SLCR_MIO_PIN_59_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_59_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_59_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_59_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_59_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_59_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_59_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_60 @ 0XFF1800F0</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Input, gem2_rgmii_rxd[1]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_60_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Input, usb0_ulpi_rx_data[4]- (ULPI data bus) 1= usb0, Output, usb0_ulpi_tx_
		ata[4]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_60_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_60_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[8]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[8]- (GPIO bank 2) 1= can
		, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL signa
		) 3= pjtag, Output, pjtag_tdo- (PJTAG TDO) 4= spi1, Output, spi1_n_ss_out[1]- (SPI Master Selects) 5= ttc1, Input, ttc1_clk_i
		- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace, Output, tracedq[6]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_60_L3_SEL                                                  0

		Configures MIO Pin 60 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800F0, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_60_L0_SEL_MASK | IOU_SLCR_MIO_PIN_60_L1_SEL_MASK | IOU_SLCR_MIO_PIN_60_L2_SEL_MASK | IOU_SLCR_MIO_PIN_60_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_60_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_60_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_60_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_60_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_60_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_60_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_61 @ 0XFF1800F4</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Input, gem2_rgmii_rxd[2]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_61_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Input, usb0_ulpi_rx_data[5]- (ULPI data bus) 1= usb0, Output, usb0_ulpi_tx_
		ata[5]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_61_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_61_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[9]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[9]- (GPIO bank 2) 1= can
		, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA signal
		 3= pjtag, Input, pjtag_tms- (PJTAG TMS) 4= spi1, Input, spi1_n_ss_in- (SPI Master Selects) 4= spi1, Output, spi1_n_ss_out[0]
		 (SPI Master Selects) 5= ttc1, Output, ttc1_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial inpu
		) 7= trace, Output, tracedq[7]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_61_L3_SEL                                                  0

		Configures MIO Pin 61 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800F4, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_61_L0_SEL_MASK | IOU_SLCR_MIO_PIN_61_L1_SEL_MASK | IOU_SLCR_MIO_PIN_61_L2_SEL_MASK | IOU_SLCR_MIO_PIN_61_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_61_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_61_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_61_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_61_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_61_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_61_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_62 @ 0XFF1800F8</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Input, gem2_rgmii_rxd[3]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_62_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Input, usb0_ulpi_rx_data[6]- (ULPI data bus) 1= usb0, Output, usb0_ulpi_tx_
		ata[6]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_62_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_62_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[10]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[10]- (GPIO bank 2) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi1, Input, spi1_mi- (MISO signal) 4= spi1, Output, spi1_
		o- (MISO signal) 5= ttc0, Input, ttc0_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Outp
		t, tracedq[8]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_62_L3_SEL                                                  0

		Configures MIO Pin 62 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800F8, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_62_L0_SEL_MASK | IOU_SLCR_MIO_PIN_62_L1_SEL_MASK | IOU_SLCR_MIO_PIN_62_L2_SEL_MASK | IOU_SLCR_MIO_PIN_62_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_62_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_62_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_62_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_62_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_62_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_62_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_63 @ 0XFF1800FC</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem2, Input, gem2_rgmii_rx_ctl- (RX RGMII control )
		PSU_IOU_SLCR_MIO_PIN_63_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb0, Input, usb0_ulpi_rx_data[7]- (ULPI data bus) 1= usb0, Output, usb0_ulpi_tx_
		ata[7]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_63_L1_SEL                                                  1

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_63_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[11]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[11]- (GPIO bank 2) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi1, Output, spi1_mo- (MOSI signal) 4= spi1, Input, s
		i1_si- (MOSI signal) 5= ttc0, Output, ttc0_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial o
		tput) 7= trace, Output, tracedq[9]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_63_L3_SEL                                                  0

		Configures MIO Pin 63 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF1800FC, 0x000000FEU ,0x00000004U)  */
		RegMask = (IOU_SLCR_MIO_PIN_63_L0_SEL_MASK | IOU_SLCR_MIO_PIN_63_L1_SEL_MASK | IOU_SLCR_MIO_PIN_63_L2_SEL_MASK | IOU_SLCR_MIO_PIN_63_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_63_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_63_L0_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_63_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_63_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_63_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_63_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_64 @ 0XFF180100</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Output, gem3_rgmii_tx_clk- (TX RGMII clock)
		PSU_IOU_SLCR_MIO_PIN_64_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Input, usb1_ulpi_clk_in- (ULPI Clock)
		PSU_IOU_SLCR_MIO_PIN_64_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Output, sdio0_clk_out- (SDSDIO clock) 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_64_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[12]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[12]- (GPIO bank 2) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi0, Input, spi0_sclk_in- (SPI Clock) 4= spi0, Output, s
		i0_sclk_out- (SPI Clock) 5= ttc3, Input, ttc3_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7
		 trace, Output, tracedq[10]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_64_L3_SEL                                                  0

		Configures MIO Pin 64 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180100, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_64_L0_SEL_MASK | IOU_SLCR_MIO_PIN_64_L1_SEL_MASK | IOU_SLCR_MIO_PIN_64_L2_SEL_MASK | IOU_SLCR_MIO_PIN_64_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_64_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_64_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_64_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_64_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_64_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_64_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_65 @ 0XFF180104</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Output, gem3_rgmii_txd[0]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_65_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Input, usb1_ulpi_dir- (Data bus direction control)
		PSU_IOU_SLCR_MIO_PIN_65_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sdio0_cd_n- (SD card detect from connector) 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_65_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[13]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[13]- (GPIO bank 2) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi0, Output, spi0_n_ss_out[2]- (SPI Master Selects) 5=
		ttc3, Output, ttc3_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input) 7= trace, Output, trac
		dq[11]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_65_L3_SEL                                                  0

		Configures MIO Pin 65 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180104, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_65_L0_SEL_MASK | IOU_SLCR_MIO_PIN_65_L1_SEL_MASK | IOU_SLCR_MIO_PIN_65_L2_SEL_MASK | IOU_SLCR_MIO_PIN_65_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_65_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_65_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_65_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_65_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_65_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_65_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_66 @ 0XFF180108</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Output, gem3_rgmii_txd[1]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_66_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Input, usb1_ulpi_rx_data[2]- (ULPI data bus) 1= usb1, Output, usb1_ulpi_tx_
		ata[2]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_66_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_cmd_in- (Command Indicator) = sd0, Output, sdio0_cmd_out- (Comman
		 Indicator) 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_66_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[14]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[14]- (GPIO bank 2) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi0, Output, spi0_n_ss_out[1]- (SPI Master Selects) 5= tt
		2, Input, ttc2_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= trace, Output, tracedq[12]- (Trace
		Port Databus)
		PSU_IOU_SLCR_MIO_PIN_66_L3_SEL                                                  0

		Configures MIO Pin 66 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180108, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_66_L0_SEL_MASK | IOU_SLCR_MIO_PIN_66_L1_SEL_MASK | IOU_SLCR_MIO_PIN_66_L2_SEL_MASK | IOU_SLCR_MIO_PIN_66_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_66_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_66_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_66_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_66_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_66_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_66_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_67 @ 0XFF18010C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Output, gem3_rgmii_txd[2]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_67_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Input, usb1_ulpi_nxt- (Data flow control signal from the PHY)
		PSU_IOU_SLCR_MIO_PIN_67_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[0]- (8-bit Data bus) = sd0, Output, sdio0_data_out[0]- (8
		bit Data bus) 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_67_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[15]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[15]- (GPIO bank 2) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi0, Input, spi0_n_ss_in- (SPI Master Selects) 4= spi
		, Output, spi0_n_ss_out[0]- (SPI Master Selects) 5= ttc2, Output, ttc2_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd
		 (UART transmitter serial output) 7= trace, Output, tracedq[13]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_67_L3_SEL                                                  0

		Configures MIO Pin 67 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18010C, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_67_L0_SEL_MASK | IOU_SLCR_MIO_PIN_67_L1_SEL_MASK | IOU_SLCR_MIO_PIN_67_L2_SEL_MASK | IOU_SLCR_MIO_PIN_67_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_67_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_67_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_67_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_67_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_67_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_67_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_68 @ 0XFF180110</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Output, gem3_rgmii_txd[3]- (TX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_68_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Input, usb1_ulpi_rx_data[0]- (ULPI data bus) 1= usb1, Output, usb1_ulpi_tx_
		ata[0]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_68_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[1]- (8-bit Data bus) = sd0, Output, sdio0_data_out[1]- (8
		bit Data bus) 2= Not Used 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_68_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[16]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[16]- (GPIO bank 2) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi0, Input, spi0_mi- (MISO signal) 4= spi0, Output, spi0
		so- (MISO signal) 5= ttc1, Input, ttc1_clk_in- (TTC Clock) 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= trace
		 Output, tracedq[14]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_68_L3_SEL                                                  0

		Configures MIO Pin 68 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180110, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_68_L0_SEL_MASK | IOU_SLCR_MIO_PIN_68_L1_SEL_MASK | IOU_SLCR_MIO_PIN_68_L2_SEL_MASK | IOU_SLCR_MIO_PIN_68_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_68_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_68_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_68_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_68_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_68_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_68_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_69 @ 0XFF180114</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Output, gem3_rgmii_tx_ctl- (TX RGMII control)
		PSU_IOU_SLCR_MIO_PIN_69_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Input, usb1_ulpi_rx_data[1]- (ULPI data bus) 1= usb1, Output, usb1_ulpi_tx_
		ata[1]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_69_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[2]- (8-bit Data bus) = sd0, Output, sdio0_data_out[2]- (8
		bit Data bus) 2= sd1, Input, sdio1_wp- (SD card write protect from connector) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_69_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[17]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[17]- (GPIO bank 2) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi0, Output, spi0_mo- (MOSI signal) 4= spi0, Input, sp
		0_si- (MOSI signal) 5= ttc1, Output, ttc1_wave_out- (TTC Waveform Clock) 6= ua1, Input, ua1_rxd- (UART receiver serial input)
		7= trace, Output, tracedq[15]- (Trace Port Databus)
		PSU_IOU_SLCR_MIO_PIN_69_L3_SEL                                                  0

		Configures MIO Pin 69 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180114, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_69_L0_SEL_MASK | IOU_SLCR_MIO_PIN_69_L1_SEL_MASK | IOU_SLCR_MIO_PIN_69_L2_SEL_MASK | IOU_SLCR_MIO_PIN_69_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_69_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_69_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_69_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_69_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_69_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_69_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_70 @ 0XFF180118</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Input, gem3_rgmii_rx_clk- (RX RGMII clock)
		PSU_IOU_SLCR_MIO_PIN_70_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Output, usb1_ulpi_stp- (Asserted to end or interrupt transfers)
		PSU_IOU_SLCR_MIO_PIN_70_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[3]- (8-bit Data bus) = sd0, Output, sdio0_data_out[3]- (8
		bit Data bus) 2= sd1, Output, sdio1_bus_pow- (SD card bus power) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_70_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[18]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[18]- (GPIO bank 2) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi1, Input, spi1_sclk_in- (SPI Clock) 4= spi1, Output, sp
		1_sclk_out- (SPI Clock) 5= ttc0, Input, ttc0_clk_in- (TTC Clock) 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= Not 
		sed
		PSU_IOU_SLCR_MIO_PIN_70_L3_SEL                                                  0

		Configures MIO Pin 70 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180118, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_70_L0_SEL_MASK | IOU_SLCR_MIO_PIN_70_L1_SEL_MASK | IOU_SLCR_MIO_PIN_70_L2_SEL_MASK | IOU_SLCR_MIO_PIN_70_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_70_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_70_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_70_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_70_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_70_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_70_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_71 @ 0XFF18011C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Input, gem3_rgmii_rxd[0]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_71_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Input, usb1_ulpi_rx_data[3]- (ULPI data bus) 1= usb1, Output, usb1_ulpi_tx_
		ata[3]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_71_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[4]- (8-bit Data bus) = sd0, Output, sdio0_data_out[4]- (8
		bit Data bus) 2= sd1, Input, sd1_data_in[0]- (8-bit Data bus) = sd1, Output, sdio1_data_out[0]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_71_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[19]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[19]- (GPIO bank 2) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi1, Output, spi1_n_ss_out[2]- (SPI Master Selects) 5
		 ttc0, Output, ttc0_wave_out- (TTC Waveform Clock) 6= ua0, Output, ua0_txd- (UART transmitter serial output) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_71_L3_SEL                                                  0

		Configures MIO Pin 71 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18011C, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_71_L0_SEL_MASK | IOU_SLCR_MIO_PIN_71_L1_SEL_MASK | IOU_SLCR_MIO_PIN_71_L2_SEL_MASK | IOU_SLCR_MIO_PIN_71_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_71_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_71_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_71_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_71_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_71_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_71_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_72 @ 0XFF180120</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Input, gem3_rgmii_rxd[1]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_72_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Input, usb1_ulpi_rx_data[4]- (ULPI data bus) 1= usb1, Output, usb1_ulpi_tx_
		ata[4]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_72_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[5]- (8-bit Data bus) = sd0, Output, sdio0_data_out[5]- (8
		bit Data bus) 2= sd1, Input, sd1_data_in[1]- (8-bit Data bus) = sd1, Output, sdio1_data_out[1]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_72_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[20]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[20]- (GPIO bank 2) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= swdt1, Input, swdt1_clk_in- (Watch Dog Timer Input clock) 4= spi1, Output, spi1_n_ss_out[1]- (SPI Master Selects) 5= N
		t Used 6= ua1, Output, ua1_txd- (UART transmitter serial output) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_72_L3_SEL                                                  0

		Configures MIO Pin 72 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180120, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_72_L0_SEL_MASK | IOU_SLCR_MIO_PIN_72_L1_SEL_MASK | IOU_SLCR_MIO_PIN_72_L2_SEL_MASK | IOU_SLCR_MIO_PIN_72_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_72_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_72_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_72_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_72_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_72_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_72_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_73 @ 0XFF180124</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Input, gem3_rgmii_rxd[2]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_73_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Input, usb1_ulpi_rx_data[5]- (ULPI data bus) 1= usb1, Output, usb1_ulpi_tx_
		ata[5]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_73_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[6]- (8-bit Data bus) = sd0, Output, sdio0_data_out[6]- (8
		bit Data bus) 2= sd1, Input, sd1_data_in[2]- (8-bit Data bus) = sd1, Output, sdio1_data_out[2]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_73_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[21]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[21]- (GPIO bank 2) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= swdt1, Output, swdt1_rst_out- (Watch Dog Timer Output clock) 4= spi1, Input, spi1_n_ss_in- (SPI Master Selects) 4= spi1
		 Output, spi1_n_ss_out[0]- (SPI Master Selects) 5= Not Used 6= ua1, Input, ua1_rxd- (UART receiver serial input) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_73_L3_SEL                                                  0

		Configures MIO Pin 73 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180124, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_73_L0_SEL_MASK | IOU_SLCR_MIO_PIN_73_L1_SEL_MASK | IOU_SLCR_MIO_PIN_73_L2_SEL_MASK | IOU_SLCR_MIO_PIN_73_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_73_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_73_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_73_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_73_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_73_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_73_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_74 @ 0XFF180128</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Input, gem3_rgmii_rxd[3]- (RX RGMII data)
		PSU_IOU_SLCR_MIO_PIN_74_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Input, usb1_ulpi_rx_data[6]- (ULPI data bus) 1= usb1, Output, usb1_ulpi_tx_
		ata[6]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_74_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sd0_data_in[7]- (8-bit Data bus) = sd0, Output, sdio0_data_out[7]- (8
		bit Data bus) 2= sd1, Input, sd1_data_in[3]- (8-bit Data bus) = sd1, Output, sdio1_data_out[3]- (8-bit Data bus) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_74_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[22]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[22]- (GPIO bank 2) 1= c
		n0, Input, can0_phy_rx- (Can RX signal) 2= i2c0, Input, i2c0_scl_input- (SCL signal) 2= i2c0, Output, i2c0_scl_out- (SCL sign
		l) 3= swdt0, Input, swdt0_clk_in- (Watch Dog Timer Input clock) 4= spi1, Input, spi1_mi- (MISO signal) 4= spi1, Output, spi1_
		o- (MISO signal) 5= Not Used 6= ua0, Input, ua0_rxd- (UART receiver serial input) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_74_L3_SEL                                                  0

		Configures MIO Pin 74 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180128, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_74_L0_SEL_MASK | IOU_SLCR_MIO_PIN_74_L1_SEL_MASK | IOU_SLCR_MIO_PIN_74_L2_SEL_MASK | IOU_SLCR_MIO_PIN_74_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_74_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_74_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_74_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_74_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_74_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_74_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_75 @ 0XFF18012C</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= gem3, Input, gem3_rgmii_rx_ctl- (RX RGMII control )
		PSU_IOU_SLCR_MIO_PIN_75_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= usb1, Input, usb1_ulpi_rx_data[7]- (ULPI data bus) 1= usb1, Output, usb1_ulpi_tx_
		ata[7]- (ULPI data bus)
		PSU_IOU_SLCR_MIO_PIN_75_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Output, sdio0_bus_pow- (SD card bus power) 2= sd1, Input, sd1_cmd_in- (Comma
		d Indicator) = sd1, Output, sdio1_cmd_out- (Command Indicator) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_75_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[23]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[23]- (GPIO bank 2) 1= c
		n0, Output, can0_phy_tx- (Can TX signal) 2= i2c0, Input, i2c0_sda_input- (SDA signal) 2= i2c0, Output, i2c0_sda_out- (SDA sig
		al) 3= swdt0, Output, swdt0_rst_out- (Watch Dog Timer Output clock) 4= spi1, Output, spi1_mo- (MOSI signal) 4= spi1, Input, s
		i1_si- (MOSI signal) 5= Not Used 6= ua0, Output, ua0_txd- (UART transmitter serial output) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_75_L3_SEL                                                  0

		Configures MIO Pin 75 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF18012C, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_75_L0_SEL_MASK | IOU_SLCR_MIO_PIN_75_L1_SEL_MASK | IOU_SLCR_MIO_PIN_75_L2_SEL_MASK | IOU_SLCR_MIO_PIN_75_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_75_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_75_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_75_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_75_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_75_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_75_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_76 @ 0XFF180130</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_76_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_76_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= sd0, Input, sdio0_wp- (SD card write protect from connector) 2= sd1, Output, sdio
		_clk_out- (SDSDIO clock) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_76_L2_SEL                                                  1

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[24]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[24]- (GPIO bank 2) 1= c
		n1, Output, can1_phy_tx- (Can TX signal) 2= i2c1, Input, i2c1_scl_input- (SCL signal) 2= i2c1, Output, i2c1_scl_out- (SCL sig
		al) 3= mdio0, Output, gem0_mdc- (MDIO Clock) 4= mdio1, Output, gem1_mdc- (MDIO Clock) 5= mdio2, Output, gem2_mdc- (MDIO Clock
		 6= mdio3, Output, gem3_mdc- (MDIO Clock) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_76_L3_SEL                                                  0

		Configures MIO Pin 76 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180130, 0x000000FEU ,0x00000008U)  */
		RegMask = (IOU_SLCR_MIO_PIN_76_L0_SEL_MASK | IOU_SLCR_MIO_PIN_76_L1_SEL_MASK | IOU_SLCR_MIO_PIN_76_L2_SEL_MASK | IOU_SLCR_MIO_PIN_76_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_76_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_76_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_76_L1_SEL_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_PIN_76_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_76_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_76_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_PIN_77 @ 0XFF180134</p>

		Level 0 Mux Select 0= Level 1 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_77_L0_SEL                                                  0

		Level 1 Mux Select 0= Level 2 Mux Output 1= Not Used
		PSU_IOU_SLCR_MIO_PIN_77_L1_SEL                                                  0

		Level 2 Mux Select 0= Level 3 Mux Output 1= Not Used 2= sd1, Input, sdio1_cd_n- (SD card detect from connector) 3= Not Used
		PSU_IOU_SLCR_MIO_PIN_77_L2_SEL                                                  0

		Level 3 Mux Select 0= gpio2, Input, gpio_2_pin_in[25]- (GPIO bank 2) 0= gpio2, Output, gpio_2_pin_out[25]- (GPIO bank 2) 1= c
		n1, Input, can1_phy_rx- (Can RX signal) 2= i2c1, Input, i2c1_sda_input- (SDA signal) 2= i2c1, Output, i2c1_sda_out- (SDA sign
		l) 3= mdio0, Input, gem0_mdio_in- (MDIO Data) 3= mdio0, Output, gem0_mdio_out- (MDIO Data) 4= mdio1, Input, gem1_mdio_in- (MD
		O Data) 4= mdio1, Output, gem1_mdio_out- (MDIO Data) 5= mdio2, Input, gem2_mdio_in- (MDIO Data) 5= mdio2, Output, gem2_mdio_o
		t- (MDIO Data) 6= mdio3, Input, gem3_mdio_in- (MDIO Data) 6= mdio3, Output, gem3_mdio_out- (MDIO Data) 7= Not Used
		PSU_IOU_SLCR_MIO_PIN_77_L3_SEL                                                  0

		Configures MIO Pin 77 peripheral interface mapping
		(OFFSET, MASK, VALUE)      (0XFF180134, 0x000000FEU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_PIN_77_L0_SEL_MASK | IOU_SLCR_MIO_PIN_77_L1_SEL_MASK | IOU_SLCR_MIO_PIN_77_L2_SEL_MASK | IOU_SLCR_MIO_PIN_77_L3_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_PIN_77_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_PIN_77_L0_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_77_L1_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_77_L2_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_PIN_77_L3_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_PIN_77_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_MST_TRI0 @ 0XFF180204</p>

		Master Tri-state Enable for pin 0, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_00_TRI                                            0

		Master Tri-state Enable for pin 1, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_01_TRI                                            0

		Master Tri-state Enable for pin 2, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_02_TRI                                            0

		Master Tri-state Enable for pin 3, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_03_TRI                                            0

		Master Tri-state Enable for pin 4, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_04_TRI                                            0

		Master Tri-state Enable for pin 5, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_05_TRI                                            0

		Master Tri-state Enable for pin 6, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_06_TRI                                            0

		Master Tri-state Enable for pin 7, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_07_TRI                                            0

		Master Tri-state Enable for pin 8, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_08_TRI                                            0

		Master Tri-state Enable for pin 9, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_09_TRI                                            0

		Master Tri-state Enable for pin 10, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_10_TRI                                            1

		Master Tri-state Enable for pin 11, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_11_TRI                                            1

		Master Tri-state Enable for pin 12, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_12_TRI                                            0

		Master Tri-state Enable for pin 13, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_13_TRI                                            0

		Master Tri-state Enable for pin 14, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_14_TRI                                            0

		Master Tri-state Enable for pin 15, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_15_TRI                                            0

		Master Tri-state Enable for pin 16, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_16_TRI                                            0

		Master Tri-state Enable for pin 17, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_17_TRI                                            0

		Master Tri-state Enable for pin 18, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_18_TRI                                            0

		Master Tri-state Enable for pin 19, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_19_TRI                                            0

		Master Tri-state Enable for pin 20, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_20_TRI                                            0

		Master Tri-state Enable for pin 21, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_21_TRI                                            0

		Master Tri-state Enable for pin 22, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_22_TRI                                            0

		Master Tri-state Enable for pin 23, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_23_TRI                                            0

		Master Tri-state Enable for pin 24, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_24_TRI                                            0

		Master Tri-state Enable for pin 25, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_25_TRI                                            0

		Master Tri-state Enable for pin 26, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_26_TRI                                            0

		Master Tri-state Enable for pin 27, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_27_TRI                                            0

		Master Tri-state Enable for pin 28, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_28_TRI                                            0

		Master Tri-state Enable for pin 29, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_29_TRI                                            0

		Master Tri-state Enable for pin 30, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_30_TRI                                            0

		Master Tri-state Enable for pin 31, active high
		PSU_IOU_SLCR_MIO_MST_TRI0_PIN_31_TRI                                            0

		MIO pin Tri-state Enables, 31:0
		(OFFSET, MASK, VALUE)      (0XFF180204, 0xFFFFFFFFU ,0x00000C00U)  */
		RegMask = (IOU_SLCR_MIO_MST_TRI0_PIN_00_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_01_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_02_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_03_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_04_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_05_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_06_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_07_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_08_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_09_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_10_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_11_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_12_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_13_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_14_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_15_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_16_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_17_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_18_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_19_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_20_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_21_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_22_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_23_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_24_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_25_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_26_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_27_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_28_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_29_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_30_TRI_MASK | IOU_SLCR_MIO_MST_TRI0_PIN_31_TRI_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_MST_TRI0_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_00_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_01_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_02_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_03_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_04_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_05_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_06_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_07_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_08_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_09_TRI_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_MST_TRI0_PIN_10_TRI_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_MST_TRI0_PIN_11_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_12_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_13_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_14_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_15_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_16_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_17_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_18_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_19_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_20_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_21_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_22_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_23_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_24_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_25_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_26_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_27_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_28_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_29_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_30_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI0_PIN_31_TRI_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_MST_TRI0_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_MST_TRI1 @ 0XFF180208</p>

		Master Tri-state Enable for pin 32, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_32_TRI                                            0

		Master Tri-state Enable for pin 33, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_33_TRI                                            0

		Master Tri-state Enable for pin 34, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_34_TRI                                            0

		Master Tri-state Enable for pin 35, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_35_TRI                                            0

		Master Tri-state Enable for pin 36, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_36_TRI                                            0

		Master Tri-state Enable for pin 37, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_37_TRI                                            0

		Master Tri-state Enable for pin 38, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_38_TRI                                            0

		Master Tri-state Enable for pin 39, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_39_TRI                                            0

		Master Tri-state Enable for pin 40, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_40_TRI                                            0

		Master Tri-state Enable for pin 41, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_41_TRI                                            0

		Master Tri-state Enable for pin 42, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_42_TRI                                            0

		Master Tri-state Enable for pin 43, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_43_TRI                                            0

		Master Tri-state Enable for pin 44, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_44_TRI                                            0

		Master Tri-state Enable for pin 45, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_45_TRI                                            0

		Master Tri-state Enable for pin 46, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_46_TRI                                            0

		Master Tri-state Enable for pin 47, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_47_TRI                                            0

		Master Tri-state Enable for pin 48, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_48_TRI                                            0

		Master Tri-state Enable for pin 49, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_49_TRI                                            0

		Master Tri-state Enable for pin 50, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_50_TRI                                            0

		Master Tri-state Enable for pin 51, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_51_TRI                                            0

		Master Tri-state Enable for pin 52, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_52_TRI                                            1

		Master Tri-state Enable for pin 53, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_53_TRI                                            1

		Master Tri-state Enable for pin 54, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_54_TRI                                            0

		Master Tri-state Enable for pin 55, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_55_TRI                                            1

		Master Tri-state Enable for pin 56, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_56_TRI                                            0

		Master Tri-state Enable for pin 57, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_57_TRI                                            0

		Master Tri-state Enable for pin 58, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_58_TRI                                            0

		Master Tri-state Enable for pin 59, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_59_TRI                                            0

		Master Tri-state Enable for pin 60, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_60_TRI                                            0

		Master Tri-state Enable for pin 61, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_61_TRI                                            0

		Master Tri-state Enable for pin 62, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_62_TRI                                            0

		Master Tri-state Enable for pin 63, active high
		PSU_IOU_SLCR_MIO_MST_TRI1_PIN_63_TRI                                            0

		MIO pin Tri-state Enables, 63:32
		(OFFSET, MASK, VALUE)      (0XFF180208, 0xFFFFFFFFU ,0x00B00000U)  */
		RegMask = (IOU_SLCR_MIO_MST_TRI1_PIN_32_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_33_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_34_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_35_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_36_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_37_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_38_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_39_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_40_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_41_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_42_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_43_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_44_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_45_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_46_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_47_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_48_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_49_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_50_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_51_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_52_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_53_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_54_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_55_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_56_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_57_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_58_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_59_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_60_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_61_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_62_TRI_MASK | IOU_SLCR_MIO_MST_TRI1_PIN_63_TRI_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_MST_TRI1_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_32_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_33_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_34_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_35_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_36_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_37_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_38_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_39_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_40_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_41_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_42_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_43_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_44_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_45_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_46_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_47_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_48_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_49_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_50_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_51_TRI_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_MST_TRI1_PIN_52_TRI_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_MST_TRI1_PIN_53_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_54_TRI_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_MST_TRI1_PIN_55_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_56_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_57_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_58_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_59_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_60_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_61_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_62_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI1_PIN_63_TRI_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_MST_TRI1_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MIO_MST_TRI2 @ 0XFF18020C</p>

		Master Tri-state Enable for pin 64, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_64_TRI                                            0

		Master Tri-state Enable for pin 65, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_65_TRI                                            1

		Master Tri-state Enable for pin 66, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_66_TRI                                            0

		Master Tri-state Enable for pin 67, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_67_TRI                                            0

		Master Tri-state Enable for pin 68, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_68_TRI                                            0

		Master Tri-state Enable for pin 69, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_69_TRI                                            0

		Master Tri-state Enable for pin 70, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_70_TRI                                            0

		Master Tri-state Enable for pin 71, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_71_TRI                                            0

		Master Tri-state Enable for pin 72, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_72_TRI                                            0

		Master Tri-state Enable for pin 73, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_73_TRI                                            0

		Master Tri-state Enable for pin 74, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_74_TRI                                            0

		Master Tri-state Enable for pin 75, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_75_TRI                                            0

		Master Tri-state Enable for pin 76, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_76_TRI                                            1

		Master Tri-state Enable for pin 77, active high
		PSU_IOU_SLCR_MIO_MST_TRI2_PIN_77_TRI                                            0

		MIO pin Tri-state Enables, 77:64
		(OFFSET, MASK, VALUE)      (0XFF18020C, 0x00003FFFU ,0x00001002U)  */
		RegMask = (IOU_SLCR_MIO_MST_TRI2_PIN_64_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_65_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_66_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_67_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_68_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_69_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_70_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_71_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_72_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_73_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_74_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_75_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_76_TRI_MASK | IOU_SLCR_MIO_MST_TRI2_PIN_77_TRI_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_MST_TRI2_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_64_TRI_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_MST_TRI2_PIN_65_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_66_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_67_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_68_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_69_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_70_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_71_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_72_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_73_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_74_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_75_TRI_SHIFT
			| 0x00000001U << IOU_SLCR_MIO_MST_TRI2_PIN_76_TRI_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_MST_TRI2_PIN_77_TRI_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_MST_TRI2_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : LOOPBACK
		/*Register : MIO_LOOPBACK @ 0XFF180200</p>

		I2C Loopback Control. 0 = Connect I2C inputs according to MIO mapping. 1 = Loop I2C 0 outputs to I2C 1 inputs, and I2C 1 outp
		ts to I2C 0 inputs.
		PSU_IOU_SLCR_MIO_LOOPBACK_I2C0_LOOP_I2C1                                        0

		CAN Loopback Control. 0 = Connect CAN inputs according to MIO mapping. 1 = Loop CAN 0 Tx to CAN 1 Rx, and CAN 1 Tx to CAN 0 R
		.
		PSU_IOU_SLCR_MIO_LOOPBACK_CAN0_LOOP_CAN1                                        0

		UART Loopback Control. 0 = Connect UART inputs according to MIO mapping. 1 = Loop UART 0 outputs to UART 1 inputs, and UART 1
		outputs to UART 0 inputs. RXD/TXD cross-connected. RTS/CTS cross-connected. DSR, DTR, DCD and RI not used.
		PSU_IOU_SLCR_MIO_LOOPBACK_UA0_LOOP_UA1                                          0

		SPI Loopback Control. 0 = Connect SPI inputs according to MIO mapping. 1 = Loop SPI 0 outputs to SPI 1 inputs, and SPI 1 outp
		ts to SPI 0 inputs. The other SPI core will appear on the LS Slave Select.
		PSU_IOU_SLCR_MIO_LOOPBACK_SPI0_LOOP_SPI1                                        0

		Loopback function within MIO
		(OFFSET, MASK, VALUE)      (0XFF180200, 0x0000000FU ,0x00000000U)  */
		RegMask = (IOU_SLCR_MIO_LOOPBACK_I2C0_LOOP_I2C1_MASK | IOU_SLCR_MIO_LOOPBACK_CAN0_LOOP_CAN1_MASK | IOU_SLCR_MIO_LOOPBACK_UA0_LOOP_UA1_MASK | IOU_SLCR_MIO_LOOPBACK_SPI0_LOOP_SPI1_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_MIO_LOOPBACK_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_MIO_LOOPBACK_I2C0_LOOP_I2C1_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_LOOPBACK_CAN0_LOOP_CAN1_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_LOOPBACK_UA0_LOOP_UA1_SHIFT
			| 0x00000000U << IOU_SLCR_MIO_LOOPBACK_SPI0_LOOP_SPI1_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_MIO_LOOPBACK_OFFSET , RegVal);

	/*############################################################################################################################ */


}
unsigned long psu_peripherals_init_data_3_0() {
		// : ENET
		/*Register : RST_LPD_IOU0 @ 0XFF5E0230</p>

		GEM 0 reset
		PSU_CRL_APB_RST_LPD_IOU0_GEM0_RESET                                             0

		GEM 1 reset
		PSU_CRL_APB_RST_LPD_IOU0_GEM1_RESET                                             0

		GEM 2 reset
		PSU_CRL_APB_RST_LPD_IOU0_GEM2_RESET                                             0

		GEM 3 reset
		PSU_CRL_APB_RST_LPD_IOU0_GEM3_RESET                                             0

		Software controlled reset for the GEMs
		(OFFSET, MASK, VALUE)      (0XFF5E0230, 0x0000000FU ,0x00000000U)  */
		RegMask = (CRL_APB_RST_LPD_IOU0_GEM0_RESET_MASK | CRL_APB_RST_LPD_IOU0_GEM1_RESET_MASK | CRL_APB_RST_LPD_IOU0_GEM2_RESET_MASK | CRL_APB_RST_LPD_IOU0_GEM3_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RST_LPD_IOU0_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RST_LPD_IOU0_GEM0_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_IOU0_GEM1_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_IOU0_GEM2_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_IOU0_GEM3_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RST_LPD_IOU0_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : QSPI
		/*Register : RST_LPD_IOU2 @ 0XFF5E0238</p>

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_QSPI_RESET                                             0

		Software control register for the IOU block. Each bit will cause a singlerperipheral or part of the peripheral to be reset.
		(OFFSET, MASK, VALUE)      (0XFF5E0238, 0x00000001U ,0x00000000U)  */
		RegMask = (CRL_APB_RST_LPD_IOU2_QSPI_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RST_LPD_IOU2_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RST_LPD_IOU2_QSPI_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RST_LPD_IOU2_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : NAND
		/*Register : RST_LPD_IOU2 @ 0XFF5E0238</p>

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_NAND_RESET                                             0

		Software control register for the IOU block. Each bit will cause a singlerperipheral or part of the peripheral to be reset.
		(OFFSET, MASK, VALUE)      (0XFF5E0238, 0x00010000U ,0x00000000U)  */
		RegMask = (CRL_APB_RST_LPD_IOU2_NAND_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RST_LPD_IOU2_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RST_LPD_IOU2_NAND_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RST_LPD_IOU2_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : USB
		/*Register : RST_LPD_TOP @ 0XFF5E023C</p>

		USB 0 reset for control registers
		PSU_CRL_APB_RST_LPD_TOP_USB0_APB_RESET                                          0

		USB 0 sleep circuit reset
		PSU_CRL_APB_RST_LPD_TOP_USB0_HIBERRESET                                         0

		USB 0 reset
		PSU_CRL_APB_RST_LPD_TOP_USB0_CORERESET                                          0

		Software control register for the LPD block.
		(OFFSET, MASK, VALUE)      (0XFF5E023C, 0x00000540U ,0x00000000U)  */
		RegMask = (CRL_APB_RST_LPD_TOP_USB0_APB_RESET_MASK | CRL_APB_RST_LPD_TOP_USB0_HIBERRESET_MASK | CRL_APB_RST_LPD_TOP_USB0_CORERESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RST_LPD_TOP_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RST_LPD_TOP_USB0_APB_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_TOP_USB0_HIBERRESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_TOP_USB0_CORERESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RST_LPD_TOP_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : SD
		/*Register : RST_LPD_IOU2 @ 0XFF5E0238</p>

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_SDIO0_RESET                                            0

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_SDIO1_RESET                                            0

		Software control register for the IOU block. Each bit will cause a singlerperipheral or part of the peripheral to be reset.
		(OFFSET, MASK, VALUE)      (0XFF5E0238, 0x00000060U ,0x00000000U)  */
		RegMask = (CRL_APB_RST_LPD_IOU2_SDIO0_RESET_MASK | CRL_APB_RST_LPD_IOU2_SDIO1_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RST_LPD_IOU2_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RST_LPD_IOU2_SDIO0_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_IOU2_SDIO1_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RST_LPD_IOU2_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : CTRL_REG_SD @ 0XFF180310</p>

		SD or eMMC selection on SDIO0 0: SD enabled 1: eMMC enabled
		PSU_IOU_SLCR_CTRL_REG_SD_SD0_EMMC_SEL                                           0

		SD or eMMC selection on SDIO1 0: SD enabled 1: eMMC enabled
		PSU_IOU_SLCR_CTRL_REG_SD_SD1_EMMC_SEL                                           0

		SD eMMC selection
		(OFFSET, MASK, VALUE)      (0XFF180310, 0x00008001U ,0x00000000U)  */
		RegMask = (IOU_SLCR_CTRL_REG_SD_SD0_EMMC_SEL_MASK | IOU_SLCR_CTRL_REG_SD_SD1_EMMC_SEL_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_CTRL_REG_SD_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_CTRL_REG_SD_SD0_EMMC_SEL_SHIFT
			| 0x00000000U << IOU_SLCR_CTRL_REG_SD_SD1_EMMC_SEL_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_CTRL_REG_SD_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : SD_CONFIG_REG2 @ 0XFF180320</p>

		Should be set based on the final product usage 00 - Removable SCard Slot 01 - Embedded Slot for One Device 10 - Shared Bus Sl
		t 11 - Reserved
		PSU_IOU_SLCR_SD_CONFIG_REG2_SD0_SLOTTYPE                                        0

		Should be set based on the final product usage 00 - Removable SCard Slot 01 - Embedded Slot for One Device 10 - Shared Bus Sl
		t 11 - Reserved
		PSU_IOU_SLCR_SD_CONFIG_REG2_SD1_SLOTTYPE                                        0

		1.8V Support 1: 1.8V supported 0: 1.8V not supported support
		PSU_IOU_SLCR_SD_CONFIG_REG2_SD0_1P8V                                            1

		3.0V Support 1: 3.0V supported 0: 3.0V not supported support
		PSU_IOU_SLCR_SD_CONFIG_REG2_SD0_3P0V                                            0

		3.3V Support 1: 3.3V supported 0: 3.3V not supported support
		PSU_IOU_SLCR_SD_CONFIG_REG2_SD0_3P3V                                            1

		1.8V Support 1: 1.8V supported 0: 1.8V not supported support
		PSU_IOU_SLCR_SD_CONFIG_REG2_SD1_1P8V                                            1

		3.0V Support 1: 3.0V supported 0: 3.0V not supported support
		PSU_IOU_SLCR_SD_CONFIG_REG2_SD1_3P0V                                            0

		3.3V Support 1: 3.3V supported 0: 3.3V not supported support
		PSU_IOU_SLCR_SD_CONFIG_REG2_SD1_3P3V                                            1

		SD Config Register 2
		(OFFSET, MASK, VALUE)      (0XFF180320, 0x33803380U ,0x02800280U)  */
		RegMask = (IOU_SLCR_SD_CONFIG_REG2_SD0_SLOTTYPE_MASK | IOU_SLCR_SD_CONFIG_REG2_SD1_SLOTTYPE_MASK | IOU_SLCR_SD_CONFIG_REG2_SD0_1P8V_MASK | IOU_SLCR_SD_CONFIG_REG2_SD0_3P0V_MASK | IOU_SLCR_SD_CONFIG_REG2_SD0_3P3V_MASK | IOU_SLCR_SD_CONFIG_REG2_SD1_1P8V_MASK | IOU_SLCR_SD_CONFIG_REG2_SD1_3P0V_MASK | IOU_SLCR_SD_CONFIG_REG2_SD1_3P3V_MASK |  0 );

		RegVal = Xil_In32 (IOU_SLCR_SD_CONFIG_REG2_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << IOU_SLCR_SD_CONFIG_REG2_SD0_SLOTTYPE_SHIFT
			| 0x00000000U << IOU_SLCR_SD_CONFIG_REG2_SD1_SLOTTYPE_SHIFT
			| 0x00000001U << IOU_SLCR_SD_CONFIG_REG2_SD0_1P8V_SHIFT
			| 0x00000000U << IOU_SLCR_SD_CONFIG_REG2_SD0_3P0V_SHIFT
			| 0x00000001U << IOU_SLCR_SD_CONFIG_REG2_SD0_3P3V_SHIFT
			| 0x00000001U << IOU_SLCR_SD_CONFIG_REG2_SD1_1P8V_SHIFT
			| 0x00000000U << IOU_SLCR_SD_CONFIG_REG2_SD1_3P0V_SHIFT
			| 0x00000001U << IOU_SLCR_SD_CONFIG_REG2_SD1_3P3V_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( IOU_SLCR_SD_CONFIG_REG2_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : CAN
		/*Register : RST_LPD_IOU2 @ 0XFF5E0238</p>

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_CAN0_RESET                                             0

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_CAN1_RESET                                             0

		Software control register for the IOU block. Each bit will cause a singlerperipheral or part of the peripheral to be reset.
		(OFFSET, MASK, VALUE)      (0XFF5E0238, 0x00000180U ,0x00000000U)  */
		RegMask = (CRL_APB_RST_LPD_IOU2_CAN0_RESET_MASK | CRL_APB_RST_LPD_IOU2_CAN1_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RST_LPD_IOU2_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RST_LPD_IOU2_CAN0_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_IOU2_CAN1_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RST_LPD_IOU2_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : I2C
		/*Register : RST_LPD_IOU2 @ 0XFF5E0238</p>

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_I2C0_RESET                                             0

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_I2C1_RESET                                             0

		Software control register for the IOU block. Each bit will cause a singlerperipheral or part of the peripheral to be reset.
		(OFFSET, MASK, VALUE)      (0XFF5E0238, 0x00000600U ,0x00000000U)  */
		RegMask = (CRL_APB_RST_LPD_IOU2_I2C0_RESET_MASK | CRL_APB_RST_LPD_IOU2_I2C1_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RST_LPD_IOU2_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RST_LPD_IOU2_I2C0_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_IOU2_I2C1_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RST_LPD_IOU2_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : SWDT
		// : SPI
		/*Register : RST_LPD_IOU2 @ 0XFF5E0238</p>

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_SPI0_RESET                                             0

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_SPI1_RESET                                             0

		Software control register for the IOU block. Each bit will cause a singlerperipheral or part of the peripheral to be reset.
		(OFFSET, MASK, VALUE)      (0XFF5E0238, 0x00000018U ,0x00000000U)  */
		RegMask = (CRL_APB_RST_LPD_IOU2_SPI0_RESET_MASK | CRL_APB_RST_LPD_IOU2_SPI1_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RST_LPD_IOU2_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RST_LPD_IOU2_SPI0_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_IOU2_SPI1_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RST_LPD_IOU2_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : TTC
		/*Register : RST_LPD_IOU2 @ 0XFF5E0238</p>

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_TTC0_RESET                                             0

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_TTC1_RESET                                             0

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_TTC2_RESET                                             0

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_TTC3_RESET                                             0

		Software control register for the IOU block. Each bit will cause a singlerperipheral or part of the peripheral to be reset.
		(OFFSET, MASK, VALUE)      (0XFF5E0238, 0x00007800U ,0x00000000U)  */
		RegMask = (CRL_APB_RST_LPD_IOU2_TTC0_RESET_MASK | CRL_APB_RST_LPD_IOU2_TTC1_RESET_MASK | CRL_APB_RST_LPD_IOU2_TTC2_RESET_MASK | CRL_APB_RST_LPD_IOU2_TTC3_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RST_LPD_IOU2_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RST_LPD_IOU2_TTC0_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_IOU2_TTC1_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_IOU2_TTC2_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_IOU2_TTC3_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RST_LPD_IOU2_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : UART
		/*Register : RST_LPD_IOU2 @ 0XFF5E0238</p>

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_UART0_RESET                                            0

		Block level reset
		PSU_CRL_APB_RST_LPD_IOU2_UART1_RESET                                            0

		Software control register for the IOU block. Each bit will cause a singlerperipheral or part of the peripheral to be reset.
		(OFFSET, MASK, VALUE)      (0XFF5E0238, 0x00000006U ,0x00000000U)  */
		RegMask = (CRL_APB_RST_LPD_IOU2_UART0_RESET_MASK | CRL_APB_RST_LPD_IOU2_UART1_RESET_MASK |  0 );

		RegVal = Xil_In32 (CRL_APB_RST_LPD_IOU2_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CRL_APB_RST_LPD_IOU2_UART0_RESET_SHIFT
			| 0x00000000U << CRL_APB_RST_LPD_IOU2_UART1_RESET_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CRL_APB_RST_LPD_IOU2_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : Baud_rate_divider_reg0 @ 0XFF000034</p>

		Baud rate divider value: 0 - 3: ignored 4 - 255: Baud rate
		PSU_UART0_BAUD_RATE_DIVIDER_REG0_BDIV                                           0x0

		Baud Rate Divider Register
		(OFFSET, MASK, VALUE)      (0XFF000034, 0x000000FFU ,0x00000000U)  */
		RegMask = (UART0_BAUD_RATE_DIVIDER_REG0_BDIV_MASK |  0 );

		RegVal = Xil_In32 (UART0_BAUD_RATE_DIVIDER_REG0_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << UART0_BAUD_RATE_DIVIDER_REG0_BDIV_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( UART0_BAUD_RATE_DIVIDER_REG0_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : Baud_rate_gen_reg0 @ 0XFF000018</p>

		Baud Rate Clock Divisor Value: 0: Disables baud_sample 1: Clock divisor bypass (baud_sample = sel_clk) 2 - 65535: baud_sample
		PSU_UART0_BAUD_RATE_GEN_REG0_CD                                                 0x0

		Baud Rate Generator Register.
		(OFFSET, MASK, VALUE)      (0XFF000018, 0x0000FFFFU ,0x00000000U)  */
		RegMask = (UART0_BAUD_RATE_GEN_REG0_CD_MASK |  0 );

		RegVal = Xil_In32 (UART0_BAUD_RATE_GEN_REG0_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << UART0_BAUD_RATE_GEN_REG0_CD_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( UART0_BAUD_RATE_GEN_REG0_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : Control_reg0 @ 0XFF000000</p>

		Stop transmitter break: 0: no affect 1: stop transmission of the break after a minimum of one character length and transmit a
		high level during 12 bit periods. It can be set regardless of the value of STTBRK.
		PSU_UART0_CONTROL_REG0_STPBRK                                                   0x0

		Start transmitter break: 0: no affect 1: start to transmit a break after the characters currently present in the FIFO and the
		transmit shift register have been transmitted. It can only be set if STPBRK (Stop transmitter break) is not high.
		PSU_UART0_CONTROL_REG0_STTBRK                                                   0x0

		Restart receiver timeout counter: 1: receiver timeout counter is restarted. This bit is self clearing once the restart has co
		pleted.
		PSU_UART0_CONTROL_REG0_RSTTO                                                    0x0

		Transmit disable: 0: enable transmitter 1: disable transmitter
		PSU_UART0_CONTROL_REG0_TXDIS                                                    0x0

		Transmit enable: 0: disable transmitter 1: enable transmitter, provided the TXDIS field is set to 0.
		PSU_UART0_CONTROL_REG0_TXEN                                                     0x1

		Receive disable: 0: enable 1: disable, regardless of the value of RXEN
		PSU_UART0_CONTROL_REG0_RXDIS                                                    0x0

		Receive enable: 0: disable 1: enable When set to one, the receiver logic is enabled, provided the RXDIS field is set to zero.
		PSU_UART0_CONTROL_REG0_RXEN                                                     0x1

		Software reset for Tx data path: 0: no affect 1: transmitter logic is reset and all pending transmitter data is discarded Thi
		 bit is self clearing once the reset has completed.
		PSU_UART0_CONTROL_REG0_TXRES                                                    0x1

		Software reset for Rx data path: 0: no affect 1: receiver logic is reset and all pending receiver data is discarded. This bit
		is self clearing once the reset has completed.
		PSU_UART0_CONTROL_REG0_RXRES                                                    0x1

		UART Control Register
		(OFFSET, MASK, VALUE)      (0XFF000000, 0x000001FFU ,0x00000017U)  */
		RegMask = (UART0_CONTROL_REG0_STPBRK_MASK | UART0_CONTROL_REG0_STTBRK_MASK | UART0_CONTROL_REG0_RSTTO_MASK | UART0_CONTROL_REG0_TXDIS_MASK | UART0_CONTROL_REG0_TXEN_MASK | UART0_CONTROL_REG0_RXDIS_MASK | UART0_CONTROL_REG0_RXEN_MASK | UART0_CONTROL_REG0_TXRES_MASK | UART0_CONTROL_REG0_RXRES_MASK |  0 );

		RegVal = Xil_In32 (UART0_CONTROL_REG0_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << UART0_CONTROL_REG0_STPBRK_SHIFT
			| 0x00000000U << UART0_CONTROL_REG0_STTBRK_SHIFT
			| 0x00000000U << UART0_CONTROL_REG0_RSTTO_SHIFT
			| 0x00000000U << UART0_CONTROL_REG0_TXDIS_SHIFT
			| 0x00000001U << UART0_CONTROL_REG0_TXEN_SHIFT
			| 0x00000000U << UART0_CONTROL_REG0_RXDIS_SHIFT
			| 0x00000001U << UART0_CONTROL_REG0_RXEN_SHIFT
			| 0x00000001U << UART0_CONTROL_REG0_TXRES_SHIFT
			| 0x00000001U << UART0_CONTROL_REG0_RXRES_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( UART0_CONTROL_REG0_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : mode_reg0 @ 0XFF000004</p>

		Channel mode: Defines the mode of operation of the UART. 00: normal 01: automatic echo 10: local loopback 11: remote loopback
		PSU_UART0_MODE_REG0_CHMODE                                                      0x0

		Number of stop bits: Defines the number of stop bits to detect on receive and to generate on transmit. 00: 1 stop bit 01: 1.5
		stop bits 10: 2 stop bits 11: reserved
		PSU_UART0_MODE_REG0_NBSTOP                                                      0x0

		Parity type select: Defines the expected parity to check on receive and the parity to generate on transmit. 000: even parity 
		01: odd parity 010: forced to 0 parity (space) 011: forced to 1 parity (mark) 1xx: no parity
		PSU_UART0_MODE_REG0_PAR                                                         0x4

		Character length select: Defines the number of bits in each character. 11: 6 bits 10: 7 bits 0x: 8 bits
		PSU_UART0_MODE_REG0_CHRL                                                        0x0

		Clock source select: This field defines whether a pre-scalar of 8 is applied to the baud rate generator input clock. 0: clock
		source is uart_ref_clk 1: clock source is uart_ref_clk/8
		PSU_UART0_MODE_REG0_CLKS                                                        0x0

		UART Mode Register
		(OFFSET, MASK, VALUE)      (0XFF000004, 0x000003FFU ,0x00000020U)  */
		RegMask = (UART0_MODE_REG0_CHMODE_MASK | UART0_MODE_REG0_NBSTOP_MASK | UART0_MODE_REG0_PAR_MASK | UART0_MODE_REG0_CHRL_MASK | UART0_MODE_REG0_CLKS_MASK |  0 );

		RegVal = Xil_In32 (UART0_MODE_REG0_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << UART0_MODE_REG0_CHMODE_SHIFT
			| 0x00000000U << UART0_MODE_REG0_NBSTOP_SHIFT
			| 0x00000004U << UART0_MODE_REG0_PAR_SHIFT
			| 0x00000000U << UART0_MODE_REG0_CHRL_SHIFT
			| 0x00000000U << UART0_MODE_REG0_CLKS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( UART0_MODE_REG0_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : Baud_rate_divider_reg0 @ 0XFF010034</p>

		Baud rate divider value: 0 - 3: ignored 4 - 255: Baud rate
		PSU_UART1_BAUD_RATE_DIVIDER_REG0_BDIV                                           0x0

		Baud Rate Divider Register
		(OFFSET, MASK, VALUE)      (0XFF010034, 0x000000FFU ,0x00000000U)  */
		RegMask = (UART1_BAUD_RATE_DIVIDER_REG0_BDIV_MASK |  0 );

		RegVal = Xil_In32 (UART1_BAUD_RATE_DIVIDER_REG0_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << UART1_BAUD_RATE_DIVIDER_REG0_BDIV_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( UART1_BAUD_RATE_DIVIDER_REG0_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : Baud_rate_gen_reg0 @ 0XFF010018</p>

		Baud Rate Clock Divisor Value: 0: Disables baud_sample 1: Clock divisor bypass (baud_sample = sel_clk) 2 - 65535: baud_sample
		PSU_UART1_BAUD_RATE_GEN_REG0_CD                                                 0x0

		Baud Rate Generator Register.
		(OFFSET, MASK, VALUE)      (0XFF010018, 0x0000FFFFU ,0x00000000U)  */
		RegMask = (UART1_BAUD_RATE_GEN_REG0_CD_MASK |  0 );

		RegVal = Xil_In32 (UART1_BAUD_RATE_GEN_REG0_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << UART1_BAUD_RATE_GEN_REG0_CD_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( UART1_BAUD_RATE_GEN_REG0_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : Control_reg0 @ 0XFF010000</p>

		Stop transmitter break: 0: no affect 1: stop transmission of the break after a minimum of one character length and transmit a
		high level during 12 bit periods. It can be set regardless of the value of STTBRK.
		PSU_UART1_CONTROL_REG0_STPBRK                                                   0x0

		Start transmitter break: 0: no affect 1: start to transmit a break after the characters currently present in the FIFO and the
		transmit shift register have been transmitted. It can only be set if STPBRK (Stop transmitter break) is not high.
		PSU_UART1_CONTROL_REG0_STTBRK                                                   0x0

		Restart receiver timeout counter: 1: receiver timeout counter is restarted. This bit is self clearing once the restart has co
		pleted.
		PSU_UART1_CONTROL_REG0_RSTTO                                                    0x0

		Transmit disable: 0: enable transmitter 1: disable transmitter
		PSU_UART1_CONTROL_REG0_TXDIS                                                    0x0

		Transmit enable: 0: disable transmitter 1: enable transmitter, provided the TXDIS field is set to 0.
		PSU_UART1_CONTROL_REG0_TXEN                                                     0x1

		Receive disable: 0: enable 1: disable, regardless of the value of RXEN
		PSU_UART1_CONTROL_REG0_RXDIS                                                    0x0

		Receive enable: 0: disable 1: enable When set to one, the receiver logic is enabled, provided the RXDIS field is set to zero.
		PSU_UART1_CONTROL_REG0_RXEN                                                     0x1

		Software reset for Tx data path: 0: no affect 1: transmitter logic is reset and all pending transmitter data is discarded Thi
		 bit is self clearing once the reset has completed.
		PSU_UART1_CONTROL_REG0_TXRES                                                    0x1

		Software reset for Rx data path: 0: no affect 1: receiver logic is reset and all pending receiver data is discarded. This bit
		is self clearing once the reset has completed.
		PSU_UART1_CONTROL_REG0_RXRES                                                    0x1

		UART Control Register
		(OFFSET, MASK, VALUE)      (0XFF010000, 0x000001FFU ,0x00000017U)  */
		RegMask = (UART1_CONTROL_REG0_STPBRK_MASK | UART1_CONTROL_REG0_STTBRK_MASK | UART1_CONTROL_REG0_RSTTO_MASK | UART1_CONTROL_REG0_TXDIS_MASK | UART1_CONTROL_REG0_TXEN_MASK | UART1_CONTROL_REG0_RXDIS_MASK | UART1_CONTROL_REG0_RXEN_MASK | UART1_CONTROL_REG0_TXRES_MASK | UART1_CONTROL_REG0_RXRES_MASK |  0 );

		RegVal = Xil_In32 (UART1_CONTROL_REG0_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << UART1_CONTROL_REG0_STPBRK_SHIFT
			| 0x00000000U << UART1_CONTROL_REG0_STTBRK_SHIFT
			| 0x00000000U << UART1_CONTROL_REG0_RSTTO_SHIFT
			| 0x00000000U << UART1_CONTROL_REG0_TXDIS_SHIFT
			| 0x00000001U << UART1_CONTROL_REG0_TXEN_SHIFT
			| 0x00000000U << UART1_CONTROL_REG0_RXDIS_SHIFT
			| 0x00000001U << UART1_CONTROL_REG0_RXEN_SHIFT
			| 0x00000001U << UART1_CONTROL_REG0_TXRES_SHIFT
			| 0x00000001U << UART1_CONTROL_REG0_RXRES_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( UART1_CONTROL_REG0_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : mode_reg0 @ 0XFF010004</p>

		Channel mode: Defines the mode of operation of the UART. 00: normal 01: automatic echo 10: local loopback 11: remote loopback
		PSU_UART1_MODE_REG0_CHMODE                                                      0x0

		Number of stop bits: Defines the number of stop bits to detect on receive and to generate on transmit. 00: 1 stop bit 01: 1.5
		stop bits 10: 2 stop bits 11: reserved
		PSU_UART1_MODE_REG0_NBSTOP                                                      0x0

		Parity type select: Defines the expected parity to check on receive and the parity to generate on transmit. 000: even parity 
		01: odd parity 010: forced to 0 parity (space) 011: forced to 1 parity (mark) 1xx: no parity
		PSU_UART1_MODE_REG0_PAR                                                         0x4

		Character length select: Defines the number of bits in each character. 11: 6 bits 10: 7 bits 0x: 8 bits
		PSU_UART1_MODE_REG0_CHRL                                                        0x0

		Clock source select: This field defines whether a pre-scalar of 8 is applied to the baud rate generator input clock. 0: clock
		source is uart_ref_clk 1: clock source is uart_ref_clk/8
		PSU_UART1_MODE_REG0_CLKS                                                        0x0

		UART Mode Register
		(OFFSET, MASK, VALUE)      (0XFF010004, 0x000003FFU ,0x00000020U)  */
		RegMask = (UART1_MODE_REG0_CHMODE_MASK | UART1_MODE_REG0_NBSTOP_MASK | UART1_MODE_REG0_PAR_MASK | UART1_MODE_REG0_CHRL_MASK | UART1_MODE_REG0_CLKS_MASK |  0 );

		RegVal = Xil_In32 (UART1_MODE_REG0_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << UART1_MODE_REG0_CHMODE_SHIFT
			| 0x00000000U << UART1_MODE_REG0_NBSTOP_SHIFT
			| 0x00000004U << UART1_MODE_REG0_PAR_SHIFT
			| 0x00000000U << UART1_MODE_REG0_CHRL_SHIFT
			| 0x00000000U << UART1_MODE_REG0_CLKS_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( UART1_MODE_REG0_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : GPIO
		// : ADMA TZ
		/*Register : slcr_adma @ 0XFF4B0024</p>

		TrustZone Classification for ADMA
		PSU_LPD_SLCR_SECURE_SLCR_ADMA_TZ                                                0XFF

		RPU TrustZone settings
		(OFFSET, MASK, VALUE)      (0XFF4B0024, 0x000000FFU ,0x000000FFU)  */
		RegMask = (LPD_SLCR_SECURE_SLCR_ADMA_TZ_MASK |  0 );

		RegVal = Xil_In32 (LPD_SLCR_SECURE_SLCR_ADMA_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x000000FFU << LPD_SLCR_SECURE_SLCR_ADMA_TZ_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_SLCR_SECURE_SLCR_ADMA_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : CSU TAMPERING
		// : CSU TAMPER STATUS
		/*Register : tamper_status @ 0XFFCA5000</p>

		CSU regsiter
		PSU_CSU_TAMPER_STATUS_TAMPER_0                                                  0

		External MIO
		PSU_CSU_TAMPER_STATUS_TAMPER_1                                                  0

		JTAG toggle detect
		PSU_CSU_TAMPER_STATUS_TAMPER_2                                                  0

		PL SEU error
		PSU_CSU_TAMPER_STATUS_TAMPER_3                                                  0

		AMS over temperature alarm for LPD
		PSU_CSU_TAMPER_STATUS_TAMPER_4                                                  0

		AMS over temperature alarm for APU
		PSU_CSU_TAMPER_STATUS_TAMPER_5                                                  0

		AMS voltage alarm for VCCPINT_FPD
		PSU_CSU_TAMPER_STATUS_TAMPER_6                                                  0

		AMS voltage alarm for VCCPINT_LPD
		PSU_CSU_TAMPER_STATUS_TAMPER_7                                                  0

		AMS voltage alarm for VCCPAUX
		PSU_CSU_TAMPER_STATUS_TAMPER_8                                                  0

		AMS voltage alarm for DDRPHY
		PSU_CSU_TAMPER_STATUS_TAMPER_9                                                  0

		AMS voltage alarm for PSIO bank 0/1/2
		PSU_CSU_TAMPER_STATUS_TAMPER_10                                                 0

		AMS voltage alarm for PSIO bank 3 (dedicated pins)
		PSU_CSU_TAMPER_STATUS_TAMPER_11                                                 0

		AMS voltaage alarm for GT
		PSU_CSU_TAMPER_STATUS_TAMPER_12                                                 0

		Tamper Response Status
		(OFFSET, MASK, VALUE)      (0XFFCA5000, 0x00001FFFU ,0x00000000U)  */
		RegMask = (CSU_TAMPER_STATUS_TAMPER_0_MASK | CSU_TAMPER_STATUS_TAMPER_1_MASK | CSU_TAMPER_STATUS_TAMPER_2_MASK | CSU_TAMPER_STATUS_TAMPER_3_MASK | CSU_TAMPER_STATUS_TAMPER_4_MASK | CSU_TAMPER_STATUS_TAMPER_5_MASK | CSU_TAMPER_STATUS_TAMPER_6_MASK | CSU_TAMPER_STATUS_TAMPER_7_MASK | CSU_TAMPER_STATUS_TAMPER_8_MASK | CSU_TAMPER_STATUS_TAMPER_9_MASK | CSU_TAMPER_STATUS_TAMPER_10_MASK | CSU_TAMPER_STATUS_TAMPER_11_MASK | CSU_TAMPER_STATUS_TAMPER_12_MASK |  0 );

		RegVal = Xil_In32 (CSU_TAMPER_STATUS_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << CSU_TAMPER_STATUS_TAMPER_0_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_1_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_2_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_3_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_4_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_5_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_6_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_7_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_8_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_9_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_10_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_11_SHIFT
			| 0x00000000U << CSU_TAMPER_STATUS_TAMPER_12_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( CSU_TAMPER_STATUS_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : CSU TAMPER RESPONSE

}
unsigned long psu_post_config() {

}
unsigned long psu_peripherals_powerdwn_data_3_0() {
		// : POWER DOWN REQUEST INTERRUPT ENABLE
		// : POWER DOWN TRIGGER

}
unsigned long psu_security_data_3_0() {
		// : DDR XMPU0
		// : DDR XMPU1
		// : DDR XMPU2
		// : DDR XMPU3
		// : DDR XMPU4
		// : DDR XMPU5
		// : FPD XMPU
		// : OCM XMPU
		// : XPPU
		// : MASTER ID LIST
		/*Register : MASTER_ID00 @ 0XFF980100</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID00_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID00_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID00_MIDM                                               0

		Predefined Master ID for PMU
		PSU_LPD_XPPU_CFG_MASTER_ID00_MID                                                0

		Master ID 00 Register
		(OFFSET, MASK, VALUE)      (0XFF980100, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID00_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID00_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID00_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID00_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID00_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID00_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID00_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID00_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID00_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID00_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID01 @ 0XFF980104</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID01_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID01_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID01_MIDM                                               0

		Predefined Master ID for RPU0
		PSU_LPD_XPPU_CFG_MASTER_ID01_MID                                                0

		Master ID 01 Register
		(OFFSET, MASK, VALUE)      (0XFF980104, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID01_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID01_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID01_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID01_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID01_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID01_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID01_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID01_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID01_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID01_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID02 @ 0XFF980108</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID02_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID02_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID02_MIDM                                               0

		Predefined Master ID for RPU1
		PSU_LPD_XPPU_CFG_MASTER_ID02_MID                                                0

		Master ID 02 Register
		(OFFSET, MASK, VALUE)      (0XFF980108, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID02_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID02_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID02_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID02_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID02_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID02_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID02_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID02_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID02_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID02_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID03 @ 0XFF98010C</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID03_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID03_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID03_MIDM                                               0

		Predefined Master ID for APU
		PSU_LPD_XPPU_CFG_MASTER_ID03_MID                                                0

		Master ID 03 Register
		(OFFSET, MASK, VALUE)      (0XFF98010C, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID03_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID03_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID03_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID03_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID03_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID03_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID03_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID03_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID03_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID03_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID04 @ 0XFF980110</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID04_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID04_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID04_MIDM                                               0

		Predefined Master ID for A53 Core 0
		PSU_LPD_XPPU_CFG_MASTER_ID04_MID                                                0

		Master ID 04 Register
		(OFFSET, MASK, VALUE)      (0XFF980110, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID04_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID04_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID04_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID04_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID04_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID04_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID04_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID04_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID04_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID04_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID05 @ 0XFF980114</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID05_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID05_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID05_MIDM                                               0

		Predefined Master ID for A53 Core 1
		PSU_LPD_XPPU_CFG_MASTER_ID05_MID                                                0

		Master ID 05 Register
		(OFFSET, MASK, VALUE)      (0XFF980114, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID05_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID05_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID05_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID05_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID05_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID05_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID05_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID05_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID05_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID05_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID06 @ 0XFF980118</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID06_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID06_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID06_MIDM                                               0

		Predefined Master ID for A53 Core 2
		PSU_LPD_XPPU_CFG_MASTER_ID06_MID                                                0

		Master ID 06 Register
		(OFFSET, MASK, VALUE)      (0XFF980118, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID06_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID06_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID06_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID06_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID06_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID06_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID06_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID06_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID06_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID06_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID07 @ 0XFF98011C</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID07_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID07_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID07_MIDM                                               0

		Predefined Master ID for A53 Core 3
		PSU_LPD_XPPU_CFG_MASTER_ID07_MID                                                0

		Master ID 07 Register
		(OFFSET, MASK, VALUE)      (0XFF98011C, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID07_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID07_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID07_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID07_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID07_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID07_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID07_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID07_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID07_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID07_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID08 @ 0XFF980120</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID08_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID08_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID08_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID08_MID                                                0

		Master ID 08 Register
		(OFFSET, MASK, VALUE)      (0XFF980120, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID08_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID08_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID08_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID08_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID08_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID08_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID08_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID08_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID08_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID08_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID09 @ 0XFF980124</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID09_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID09_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID09_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID09_MID                                                0

		Master ID 09 Register
		(OFFSET, MASK, VALUE)      (0XFF980124, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID09_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID09_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID09_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID09_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID09_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID09_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID09_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID09_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID09_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID09_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID10 @ 0XFF980128</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID10_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID10_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID10_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID10_MID                                                0

		Master ID 10 Register
		(OFFSET, MASK, VALUE)      (0XFF980128, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID10_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID10_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID10_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID10_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID10_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID10_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID10_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID10_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID10_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID10_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID11 @ 0XFF98012C</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID11_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID11_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID11_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID11_MID                                                0

		Master ID 11 Register
		(OFFSET, MASK, VALUE)      (0XFF98012C, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID11_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID11_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID11_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID11_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID11_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID11_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID11_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID11_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID11_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID11_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID12 @ 0XFF980130</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID12_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID12_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID12_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID12_MID                                                0

		Master ID 12 Register
		(OFFSET, MASK, VALUE)      (0XFF980130, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID12_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID12_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID12_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID12_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID12_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID12_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID12_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID12_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID12_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID12_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID13 @ 0XFF980134</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID13_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID13_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID13_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID13_MID                                                0

		Master ID 13 Register
		(OFFSET, MASK, VALUE)      (0XFF980134, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID13_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID13_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID13_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID13_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID13_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID13_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID13_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID13_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID13_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID13_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID14 @ 0XFF980138</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID14_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID14_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID14_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID14_MID                                                0

		Master ID 14 Register
		(OFFSET, MASK, VALUE)      (0XFF980138, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID14_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID14_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID14_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID14_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID14_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID14_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID14_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID14_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID14_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID14_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID15 @ 0XFF98013C</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID15_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID15_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID15_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID15_MID                                                0

		Master ID 15 Register
		(OFFSET, MASK, VALUE)      (0XFF98013C, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID15_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID15_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID15_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID15_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID15_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID15_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID15_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID15_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID15_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID15_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID16 @ 0XFF980140</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID16_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID16_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID16_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID16_MID                                                0

		Master ID 16 Register
		(OFFSET, MASK, VALUE)      (0XFF980140, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID16_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID16_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID16_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID16_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID16_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID16_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID16_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID16_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID16_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID16_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID17 @ 0XFF980144</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID17_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID17_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID17_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID17_MID                                                0

		Master ID 17 Register
		(OFFSET, MASK, VALUE)      (0XFF980144, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID17_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID17_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID17_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID17_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID17_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID17_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID17_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID17_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID17_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID17_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID18 @ 0XFF980148</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID18_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID18_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID18_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID18_MID                                                0

		Master ID 18 Register
		(OFFSET, MASK, VALUE)      (0XFF980148, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID18_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID18_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID18_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID18_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID18_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID18_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID18_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID18_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID18_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID18_OFFSET , RegVal);

	/*############################################################################################################################ */

		/*Register : MASTER_ID19 @ 0XFF98014C</p>

		Parity of all non-reserved fields (i.e. MIDR, MIDM, MID)
		PSU_LPD_XPPU_CFG_MASTER_ID19_MIDP                                               0

		If set, only read transactions are allowed for the masters matching this register
		PSU_LPD_XPPU_CFG_MASTER_ID19_MIDR                                               0

		Mask to be applied before comparing
		PSU_LPD_XPPU_CFG_MASTER_ID19_MIDM                                               0

		Programmable Master ID
		PSU_LPD_XPPU_CFG_MASTER_ID19_MID                                                0

		Master ID 19 Register
		(OFFSET, MASK, VALUE)      (0XFF98014C, 0xC3FF03FFU ,0x00000000U)  */
		RegMask = (LPD_XPPU_CFG_MASTER_ID19_MIDP_MASK | LPD_XPPU_CFG_MASTER_ID19_MIDR_MASK | LPD_XPPU_CFG_MASTER_ID19_MIDM_MASK | LPD_XPPU_CFG_MASTER_ID19_MID_MASK |  0 );

		RegVal = Xil_In32 (LPD_XPPU_CFG_MASTER_ID19_OFFSET);
		RegVal &= ~(RegMask);
		RegVal |= ((0x00000000U << LPD_XPPU_CFG_MASTER_ID19_MIDP_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID19_MIDR_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID19_MIDM_SHIFT
			| 0x00000000U << LPD_XPPU_CFG_MASTER_ID19_MID_SHIFT
			|  0 ) & RegMask);
		Xil_Out32 ( LPD_XPPU_CFG_MASTER_ID19_OFFSET , RegVal);

	/*############################################################################################################################ */

		// : APERTURE PERMISIION LIST

}
/**
 * CRL_APB Base Address
 */
#define CRL_APB_BASEADDR      0XFF5E0000U
#define CRL_APB_RST_LPD_IOU0    ( ( CRL_APB_BASEADDR ) + 0X00000230U )
#define CRL_APB_RST_LPD_IOU1    ( ( CRL_APB_BASEADDR ) + 0X00000234U )
#define CRL_APB_RST_LPD_IOU2    ( ( CRL_APB_BASEADDR ) + 0X00000238U )
#define CRL_APB_RST_LPD_TOP    ( ( CRL_APB_BASEADDR ) + 0X0000023CU )
#define CRL_APB_IOU_SWITCH_CTRL    ( ( CRL_APB_BASEADDR ) + 0X0000009CU )

/**
 * CRF_APB Base Address
 */
#define CRF_APB_BASEADDR      0XFD1A0000U

#define CRF_APB_RST_FPD_TOP    ( ( CRF_APB_BASEADDR ) + 0X00000100U )
#define CRF_APB_GPU_REF_CTRL    ( ( CRF_APB_BASEADDR ) + 0X00000084U )
#define CRF_APB_RST_DDR_SS    ( ( CRF_APB_BASEADDR ) + 0X00000108U )

void init_ddrc()
{

	Xil_Out32(  0XFD1A0108, 0x0000000F)  ; //#RST_DDR_SS 0xFE500108
		Xil_Out32(  0xFD070000, 0x41040001)  ; //#MSTR
		Xil_Out32(  0xFD070034, 0x00404310)  ; //#PWRTMG
		Xil_Out32(  0xFD070064, 0x0040001E)  ; //#RFSHTMG 
		Xil_Out32(  0xFD070070, 0x00000010)  ; //#ECCCFG0
		Xil_Out32(  0xFD070074, 0x00000000)  ; //#ECCCFG1
		Xil_Out32(  0xFD0700C4, 0x10000200)  ; //#CRCPARCTL1
		Xil_Out32(  0xFD0700C8, 0x0030051F)  ; //#CRCPARCTL2
		Xil_Out32(  0xFD0700D0, 0x40020004)  ; //#INIT0  
		Xil_Out32(  0xFD0700D4, 0x00010000)  ; //#INIT1 
		Xil_Out32(  0xFD0700D8, 0x00001205)  ; //#INIT2
		Xil_Out32(  0xFD0700DC, 0x09300000)  ; //#INIT3
		Xil_Out32(  0xFD0700E0, 0x02080000)  ; //#INIT4
		Xil_Out32(  0xFD0700E4, 0x00110004)  ; //#INIT5
		Xil_Out32(  0xFD070100, 0x090E110A)  ; //#DRAMTMG0
		Xil_Out32(  0xFD070104, 0x0007020E)  ; //#DRAMTMG1
		Xil_Out32(  0xFD070108, 0x03040407)  ; //#DRAMTMG2
		Xil_Out32(  0xFD07010C, 0x00502006)  ; //#DRAMTMG3
		Xil_Out32(  0xFD070110, 0x04020205)  ; //#DRAMTMG4
		Xil_Out32(  0xFD070114, 0x03030202)  ; //#DRAMTMG5
		Xil_Out32(  0xFD070118, 0x01010003)  ; //#DRAMTMG6
		Xil_Out32(  0xFD07011C, 0x00000101)  ; //#DRAMTMG7
		Xil_Out32(  0xFD070120, 0x03030903)  ; //#DRAMTMG8
		Xil_Out32(  0xFD070130, 0x00020608)  ; //#DRAMTMG12
		Xil_Out32(  0xFD070180, 0x00800020)  ; //#ZQCTL0
		Xil_Out32(  0xFD070184, 0x0200CB52)  ; //#ZQCTL1
		Xil_Out32(  0xFD070190, 0x02838204)  ; //#DFITMG0 
		Xil_Out32(  0xFD070194, 0x00020404)  ; //#DFITMG1 
		Xil_Out32(  0xFD0701A4, 0x00010087)  ; //#DFIUPD1
		Xil_Out32(  0xFD0701B0, 0x00000001)  ; //#DFIMISC #change-reset value
		Xil_Out32(  0xFD0701B4, 0x00000202)  ; //#DFITMG2
		Xil_Out32(  0xFD0701C0, 0x00000000)  ; //#DBICTL
		Xil_Out32(  0xFD070200, 0x0000001F)  ; //#ADDRMAP0
		Xil_Out32(  0xFD070204, 0x00080808)  ; //#ADDRMAP1
		Xil_Out32(  0xFD070208, 0x00000000)  ; //#ADDRMAP2
		Xil_Out32(  0xFD07020C, 0x00000000)  ; //#ADDRMAP3
		Xil_Out32(  0xFD070210, 0x00000F0F)  ; //#ADDRMAP4
		Xil_Out32(  0xFD070214, 0x07070707)  ; //#ADDRMAP5 
		Xil_Out32(  0xFD070218, 0x07070707)  ; //#ADDRMAP6
		Xil_Out32(  0xFD07021C, 0x00000F0F)  ; //#ADDRMAP7
		Xil_Out32(  0xFD070220, 0x00000000)  ; //#ADDRMAP8
		Xil_Out32(  0xFD070240, 0x06000604)  ; //#ODTCFG
		Xil_Out32(  0xFD070244, 0x00000001)  ; //#ODTMAP
		Xil_Out32(  0xFD070250, 0x01002001)  ; //#SCHED
		Xil_Out32(  0xFD070264, 0x08000040)  ; //#PERFLPR1
		Xil_Out32(  0xFD07026C, 0x08000040)  ; //#PERFWR1
		Xil_Out32(  0xFD070294, 0x00000001)  ; //#DQMAP5
		Xil_Out32(  0xFD07030C, 0x00000000)  ; //#DBGCMD
		Xil_Out32(  0xFD070320, 0x00000000)  ; //#SWCTL
		Xil_Out32(  0xFD070400, 0x00000001)  ; //#PCCFG
		Xil_Out32(  0xFD070404, 0x0000600F)  ; //#PCFGR_0
		Xil_Out32(  0xFD070408, 0x0000600F)  ; //#PCFGW_0
		Xil_Out32(  0xFD070490, 0x00000001)  ; //#PCTRL_0
		Xil_Out32(  0xFD070494, 0x0021000B)  ; //#PCFGQOS0_0
		Xil_Out32(  0xFD070498, 0x004F004F)  ; //#PCFGQOS1_0
		Xil_Out32(  0xFD0704B4, 0x0000600F)  ; //#PCFGR_1
		Xil_Out32(  0xFD0704B8, 0x0000600F)  ; //#PCFGW_1
		Xil_Out32(  0xFD070540, 0x00000001)  ; //#PCTRL_1
		Xil_Out32(  0xFD070544, 0x02000B03)  ; //#PCFGQOS0_1
		Xil_Out32(  0xFD070548, 0x00010040)  ; //#PCFGQOS1_1
		Xil_Out32(  0xFD070564, 0x0000600F)  ; //#PCFGR_2
		Xil_Out32(  0xFD070568, 0x0000600F)  ; //#PCFGW_2
		Xil_Out32(  0xFD0705F0, 0x00000001)  ; //#PCTRL_2
		Xil_Out32(  0xFD0705F4, 0x02000B03)  ; //#PCFGQOS0_2
		Xil_Out32(  0xFD0705F8, 0x00010040)  ; //#PCFGQOS1_2
		Xil_Out32(  0xFD070614, 0x0000600F)  ; //#PCFGR_3
		Xil_Out32(  0xFD070618, 0x0000600F)  ; //#PCFGW_3
		Xil_Out32(  0xFD0706A0, 0x00000001)  ; //#PCTRL_3
		Xil_Out32(  0xFD0706A4, 0x00100003)  ; //#PCFGQOS0_3
		Xil_Out32(  0xFD0706A8, 0x002F004F)  ; //#PCFGQOS1_3
		Xil_Out32(  0xFD0706AC, 0x00100007)  ; //#PCFGWQOS0_3
		Xil_Out32(  0xFD0706B0, 0x0000004F)  ; //#PCFGWQOS1_3
		Xil_Out32(  0xFD0706C4, 0x0000600F)  ; //#PCFGR_4
		Xil_Out32(  0xFD0706C8, 0x0000600F)  ; //#PCFGW_4
		Xil_Out32(  0xFD070750, 0x00000001)  ; //#PCTRL_4
		Xil_Out32(  0xFD070754, 0x00100003)  ; //#PCFGQOS0_4
		Xil_Out32(  0xFD070758, 0x002F004F)  ; //#PCFGQOS1_4
		Xil_Out32(  0xFD07075C, 0x00100007)  ; //#PCFGWQOS0_4
		Xil_Out32(  0xFD070760, 0x0000004F)  ; //#PCFGWQOS1_4
		Xil_Out32(  0xFD070774, 0x0000600F)  ; //#PCFGR_5
		Xil_Out32(  0xFD070778, 0x0000600F)  ; //#PCFGW_5
		Xil_Out32(  0xFD070800, 0x00000001)  ; //#PCTRL_5
		Xil_Out32(  0xFD070804, 0x00100003)  ; //#PCFGQOS0_5
		Xil_Out32(  0xFD070808, 0x002F004F)  ; //#PCFGQOS1_5
		Xil_Out32(  0xFD07080C, 0x00100007)  ; //#PCFGWQOS0_5
		Xil_Out32(  0xFD070810, 0x0000004F)  ; //#PCFGWQOS1_5
		Xil_Out32(  0xFD070F04, 0x00000000)  ; //#SARBASE0
		Xil_Out32(  0xFD070F08, 0x00000000)  ; //#SARSIZE0
		Xil_Out32(  0xFD070F0C, 0x00000010)  ; //#SARBASE1
		Xil_Out32(  0xFD070F10, 0x0000000F)  ; //#SARSIZE1
		      
		Xil_In32( 0XFD1A0108)  ; //#RST_DDR_SS 0xFE500108
		Xil_Out32(  0XFD1A0108, 0x00000000)  ; //#RST_DDR_SS 0xFE500108 0
		Xil_In32( 0XFD1A0108           )  ; //#RST_DDR_SS 0xFE500108  

	/* Take DDR out of reset */
	Xil_Out32( CRF_APB_RST_DDR_SS, 0x00000000);
}

void init_peripheral()
{
	unsigned int RegValue;

	/* Turn on IOU Clock */
	Xil_Out32( CRL_APB_IOU_SWITCH_CTRL, 0x01001500);

	/* Release all resets in the IOU */
	Xil_Out32( CRL_APB_RST_LPD_IOU0, 0x00000000);
	Xil_Out32( CRL_APB_RST_LPD_IOU1, 0x00000000);
	Xil_Out32( CRL_APB_RST_LPD_IOU2, 0x00000000);

	/* Activate GPU clocks */
	Xil_Out32(CRF_APB_GPU_REF_CTRL, 0x07001500);

	/* Take LPD out of reset except R5 */
	RegValue = Xil_In32(CRL_APB_RST_LPD_TOP);
	RegValue &= 0x3;
	Xil_Out32( CRL_APB_RST_LPD_TOP, RegValue);

	/* Take most of FPD out of reset */
	Xil_Out32( CRF_APB_RST_FPD_TOP, 0x00000000);
}
int
psu_init() 
{
    psu_mio_init_data ();
    psu_pll_init_data ();
    psu_clock_init_data ();
    psu_ddr_init_data_3_0 ();
    init_ddrc();
    init_peripheral ();
    psu_peripherals_init_data_3_0 ();
    psu_peripherals_powerdwn_data_3_0 ();
    psu_security_data_3_0();
    return 0;
}
