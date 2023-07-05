#include "adc.h"

#if defined (adc_v1_1)|| defined (adc_v1_2) || defined (adc_v1_3)|| defined (adc_v1_4) ||defined (adc_v1_5)||\
    defined (adc_v1_6) || defined (adc_v1_7) || defined (adc_v1_8)|| defined (adc_v2_1) ||defined (adc_v3_1) ||\
	defined (adc_v3_2) ||defined (adc_v4_1)||defined (adc_v4_2) || defined (adc_v4_3)||defined (adc_v5_1)||\
	defined (adc_v5_2)|| defined (adc_v6_1)|| defined (adc_v6_2) || defined (adc_v6_3) || defined (adc_v7_1) || defined (adc_v7_2) ||\
	defined (LIB_BUILD) 
	
/***********************************************************************************************
Function:    void CloseADC10(void)

Overview:    This function turns off the ADC module and disables the ADC interrupts. 

Parameters:  None 

Returns:     None
 
Remarks:     This function first disables the ADC interrupt and then turns off the ADC
             module.The Interrupt Flag bit (ADIF) is also cleared.
***********************************************************************************************/

void CloseADC10(void)
{
    /* disable ADC interrupt */
    IEC0bits.AD1IE = 0;

    /* turn off ADC */
    AD1CON1bits.ADON = 0;

    /* clear ADIF bit */
    IFS0bits.AD1IF = 0;
}


#else
#warning "Does not build on this target"
#endif
