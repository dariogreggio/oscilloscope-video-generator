#include "adc.h"

#if defined (adc_v1_1)|| defined (adc_v1_2) || defined (adc_v1_3)|| defined (adc_v1_4) ||defined (adc_v1_5)||\
    defined (adc_v1_6) || defined (adc_v1_7) || defined (adc_v1_8)|| defined (adc_v2_1) ||defined (adc_v3_1) ||\
	defined (adc_v3_2) ||defined (adc_v4_1)||defined (adc_v4_2) || defined (adc_v4_3)||defined (adc_v5_1)||\
	defined (adc_v5_2)|| defined (adc_v6_1)|| defined (adc_v6_2) || defined (adc_v6_3) ||defined (adc_v7_1) || defined (adc_v7_2) ||\
	defined (LIB_BUILD) 
/************************************************************************
Function           : unsigned int ReadADC10(unsigned char bufIndex) 

Overview           : This function reads the ADC Buffer register which contains 
                     the conversion value. 

Parameters         : bufIndex - This is the ADC buffer number which is to be read. 

Returns            : Returns the ADC Buffer value

Remarks            : This function returns the contents of the ADC Buffer register.
                     User should provide bufIndex value between ‘0’ to ‘15’ to 
                     ensure correct read of the ADCBUF0 to ADCBUFF.
 ************************************************************************/

unsigned int ReadADC10(unsigned char bufIndex)
{
     return(*(&ADC1BUF0+bufIndex));
}

#else
#warning "Does not build on this target"
#endif
