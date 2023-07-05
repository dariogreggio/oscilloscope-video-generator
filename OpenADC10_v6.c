 
#include "adc.h"

#if defined (adc_v6_1) || defined (adc_v6_2) || defined (adc_v6_3) || defined (LIB_BUILD) 
/*************************************************************************************
Function           : void OpenADC10_v6(unsigned int config1, unsigned int config2, unsigned int config3,
                                        unsigned int configport_low,unsigned int configscan_low)					
					                                
Overview           : For seamless migration, it is recommended to call the above function as "OpenADC10". 

Parameters         : config1 - This contains the parameters to be configured in the ADCON1 register	                    
                     config2 - This contains the parameters to be configured in the ADCON2 register 
					 config3 - This contains the parameters to be configured in the ADCON3 register
					 configport_low - This contains the pin select to be configured into ADPCFGL register 				
					 configscan _low- This contains the scan select parameter to be configured into the  AD1CSSL 
					 
Returns     : None
			
Remarks     : This function configures the ADC for the following parameters:
			Operating mode, Sleep mode behavior, Data o/p format, Sample Clk
			Source, VREF source, No of samples/int, Buffer Fill mode, Alternate i/p
			sample mode, Auto sample time,Conv clock source, 
			Conv Clock Select bits, Port Config Control bits.
		
************************************************************************************************/

void OpenADC10_v6(unsigned int config1, unsigned int config2, unsigned int config3,
                  unsigned int configport_low, unsigned int configscan_low)
{

    /* digital/analog mode selection on the port bits */
    // non c'è su GP202, v. ANSEL AD1PCFGL = configport_low;
	
    /* configures the input scan selection bits */
    AD1CSSL = configscan_low;
    	
    /* config AD1CON3 */
    AD1CON3 = config3;

    /* config AD1CON2 */
    AD1CON2 = config2;

    /* config AD1CON1 */
    AD1CON1 = config1;

    /* assign SAMP bit */
    AD1CON1bits.SAMP = config1 >> 1;
}

#else
#warning "Does not build on this target"
#endif
