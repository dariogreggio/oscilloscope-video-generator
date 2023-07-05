 
#include <timer.h>

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3)|| defined (tmr_v1_4) || defined (tmr_v2_1) || defined (tmr_v2_2)|| defined (LIB_BUILD)

/****************************************************************************
Function Prototype : void ConfigIntTimer3(unsigned int config)

Include            : timer.h
 
Description        : This function configures the 16-bit timer interrupt.
 
Arguments          : config - Timer interrupt priority and enable/disable 
                     information as defined below
					 
                     Timer Interrupt Priority
		   *	T3_INT_PRIOR_7					
		   *	T3_INT_PRIOR_6					
		   *	T3_INT_PRIOR_5					
		   *	T3_INT_PRIOR_4					
		   *	T3_INT_PRIOR_3					
		   *	T3_INT_PRIOR_2					
		   *	T3_INT_PRIOR_1					
		   *	T3_INT_PRIOR_0
		  Timer Interrupt Enable\Disable 					
		   *	T3_INT_ON					
		   *	T3_INT_OFF
					 
Return Value      : None
 
Remarks           : This function clears the 16-bit Interrupt Flag (TxIF) bit 
                    and then sets the interrupt priority and enables/disables 
                    the interrupt.
******************************************************************************/

void ConfigIntTimer3(unsigned int config)
{
    IFS0bits.T3IF = 0;                   /* clear IF bit */
    IPC2bits.T3IP = (config &0x0007);    /* assigning Interrupt Priority */
    IEC0bits.T3IE = (config &0x0008)>>3; /* Interrupt Enable /Disable */
	#if defined (tmr_v2_1) || defined (tmr_v2_2)
	IFS2bits.T3GIF=0;		 					/* clear IF bit */
	IPC9bits.T3GIP = (config &0x0007);    /* assigning Interrupt Priority */
	IEC2bits.T3GIE = (config &0x0008)>>3;      /* Interrupt Enable /Disable */	
	#endif
	
}


#else
#warning "Does not build on this target"
#endif
