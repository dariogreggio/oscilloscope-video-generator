 
#include <timer.h>

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3)|| defined (tmr_v1_4) || defined (tmr_v2_1) || defined (tmr_v2_2)|| defined (LIB_BUILD)
/****************************************************************************
Function Prototype : void ConfigIntTimer2(unsigned int config)

Include            : timer.h
 
Description        : This function configures the 16-bit timer interrupt.
 
Arguments          : config - Timer interrupt priority and enable/disable 
                     information as defined below
                     Timer Interrupt Priority
		   *	T2_INT_PRIOR_7					
		   *	T2_INT_PRIOR_6					
		   *	T2_INT_PRIOR_5					
		   *	T2_INT_PRIOR_4					
		   *	T2_INT_PRIOR_3					
		   *	T2_INT_PRIOR_2					
		   *	T2_INT_PRIOR_1					
		   *	T2_INT_PRIOR_0
		  Timer Interrupt Enable\Disable 					
		   *	T2_INT_ON					
		   *	T2_INT_OFF
					 
Return Value      : None
 
Remarks           : This function clears the 16-bit Interrupt Flag (TxIF) bit 
                    and then sets the interrupt priority and enables/disables 
                    the interrupt.
******************************************************************************/


void ConfigIntTimer2(unsigned int config)
{
    IFS0bits.T2IF = 0;                   /* clear IF bit */
    IPC1bits.T2IP = (config &0x0007);    /* assigning Interrupt Priority */
    IEC0bits.T2IE = (config &0x0008)>>3; /* Interrupt Enable /Disable */
}

#else
#warning "Does not build on this target"
#endif
