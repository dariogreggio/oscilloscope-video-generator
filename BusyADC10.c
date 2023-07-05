 #include "adc.h"

#if defined (adc_v1_1)|| defined (adc_v1_2) || defined (adc_v1_3)|| defined (adc_v1_4) ||defined (adc_v1_5)||\
    defined (adc_v1_6) || defined (adc_v1_7) || defined (adc_v1_8)|| defined (adc_v2_1) ||defined (adc_v3_1) ||\
	defined (adc_v3_2) ||defined (adc_v4_1)||defined (adc_v4_2) || defined (adc_v4_3)||defined (adc_v5_1)||\
	defined (adc_v5_2)||defined (adc_v6_1)|| defined (adc_v6_2) || defined (adc_v6_3) || defined (adc_v7_1) || defined (adc_v7_2) ||\
	defined (LIB_BUILD) 
/*************************************************************************************
Function:    char BusyADC10(void)

Overview:    This function returns the ADC conversion status.  

Parameters:  None

Returns:     If the value of DONE is ‘0’, then ‘1’ is returned,indicating that the
             ADC is busy in conversion.If the value of DONE is ‘1’, then ‘0’ is 
             returned, indicating that the ADC has completed conversion. 

Remarks:     This function returns the complement of the ADCON1 <DONE> bit
             status which indicates whether the ADC is busy in conversion.
            
***************************************************************************************/  
char BusyADC10(void)
{
    return !(AD1CON1bits.DONE);	/* returns the DONE bit status */
}

#else
#warning "Does not build on this target"
#endif
