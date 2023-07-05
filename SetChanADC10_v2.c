#include "adc.h"

#if defined (adc_v6_1)|| defined (adc_v6_2) || defined (adc_v6_3) || defined (LIB_BUILD)

/*********************************************************************
Function           : void SetChanADC10_v2(unsigned int channel0,unsigned int channel123) 

Overview           : This function sets the positive and negative inputs for 
                     the sample multiplexers A and B for input channels 0,1,2,3. 

Parameters         : channel0 - This contains the input select parameter to be 
                          configured into the AD1CHS0 register
					 channel123 - This contains the input select parameter to be
							configured into the AD1CHS123 register.
						  
Returns            : None 

Remarks            : This function configures the inputs for sample multiplexers 
                     A and B by writing to AD1CHS0 and AD1CHS123 register.
*********************************************************************/

void SetChanADC10_v2(unsigned int channel0,unsigned int channel123)
{
	AD1CHS0 = channel0;
    AD1CHS123 = channel123;
}

#else
#warning "Does not build on this target"
#endif
