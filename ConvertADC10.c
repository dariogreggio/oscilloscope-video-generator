#include "adc.h"

#if defined (adc_v1_1)|| defined (adc_v1_2) || defined (adc_v1_3)|| defined (adc_v1_4) ||defined (adc_v1_5)||\
    defined (adc_v1_6) || defined (adc_v1_7) || defined (adc_v1_8)|| defined (adc_v2_1) ||defined (adc_v3_1) ||\
	defined (adc_v3_2) ||defined (adc_v4_1)||defined (adc_v4_2) || defined (adc_v4_3)||defined (adc_v5_1)||\
	defined (adc_v5_2) || defined (adc_v6_1) || defined (adc_v6_2) || defined (adc_v6_3) || defined (adc_v7_1) || defined (adc_v7_2) ||\
	defined (LIB_BUILD) 
/************************************************************************************
Function           :void ConvertADC10(void)
 
Overview           :This function starts the A/D conversion.
 
Parameters         :None

Returns            :None 

Remarks            :This function clears the ADCON1<SAMP> bit and thus stops 
                    sampling and starts conversion.This happens only when 
                    trigger source for the A/D conversion is selected as Manual,
                    by clearing the ADCON1 <SSRC> bits.
**************************************************************************************/

void ConvertADC10(void) {

#if defined (__PIC24EP512GP202__)||defined(__PIC24EP256GP202__)

	AD1CON1bits.DONE=0;
	AD1CON1bits.SAMP=1;

#else		//GS??

  AD1CON1bits.SAMP = 0; /* clear SAMP to start conversion*/

#endif


	}

#else
#warning "Does not build on this target"
#endif
