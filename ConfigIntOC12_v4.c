 
#include <outcompare.h>

#if defined (ocmp_v2_1) || defined (ocmp_v2_2) || defined (ocmp_v2_3)|| defined (ocmp_v2_4) || defined (ocmp_v2_5)|| defined (LIB_BUILD)
/***********************************************************************************
Function Prototype : void ConfigIntOC12(unsigned int config)

Include            : outcompare.h
 
Description        : This function configures the Output Compare interrupt.
 
Arguments          : config - Output Compare interrupt priority and enable/disable
				 information as defined below
					Interrupt enable/disable						
					   *	OC_INT_ON						
					   *	OC_INT_OFF						
					Interrupt Priority						
					   *	OC_INT_PRIOR_0						
					   *	OC_INT_PRIOR_1						
					   *	OC_INT_PRIOR_2		
					   *	OC_INT_PRIOR_3						
					   *	OC_INT_PRIOR_4						
					   *	OC_INT_PRIOR_5						
					   *	OC_INT_PRIOR_6						
					   *	OC_INT_PRIOR_7

 
Return Value        : None
 
Remarks             : This function clears the Interrupt Flag bit and then sets 
                      the interrupt priority and enables/disables the interrupt.
************************************************************************************/

void ConfigIntOC12(unsigned int config)
{
	IFS0bits.OC1IF = 0; /* Clear IF bit */
    IFS0bits.OC2IF = 0;  
    
    IPC0bits.OC1IP = (config & 0x0007);                 
    IPC1bits.OC2IP = (config & 0x0007);    /* Assign Interrupt Priority */ 
    
    IEC0bits.OC1IE = (config &0x0008)>>3; /* Enable/disable Interrupt */
    IEC0bits.OC2IE = (config &0x0008)>>3;
}

#else
#warning "Does not build on this target"
#endif
