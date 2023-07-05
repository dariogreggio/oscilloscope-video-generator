 
#include <timer.h>

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3)|| defined (tmr_v1_4) || defined (tmr_v2_1) || defined (tmr_v2_2) || defined (LIB_BUILD)
/*******************************************************************************
Function Prototype : void OpenTimer2(unsigned int config,unsigned int period)
 
Include            : timer.h
 
Description        : This function configures the 16-bit timer module.
 
Arguments          : config - This contains the parameters to be configured in
                     the T2CON register as defined below
					 
			Timer Module On/Off						
			   *	T2_ON						
			   *	T2_OFF						
			Timer Module Idle mode On/Off						
			   *	T2_IDLE_CON						
			   *	T2_IDLE_STOP						
			Timer Gate time accumulation enable						
			   *	T2_GATE_ON						
			   *	T2_GATE_OFF						
			Timer prescaler						
			   *	T2_PS_1_1						
			   *	T2_PS_1_8						
			   *	T2_PS_1_64						
			   *	T2_PS_1_256						
			Timer 32bit mode enable/disable					
			   *	T2_32BIT_MODE_ON						
			   *	T2_32BIT_MODE_OFF					
			Timer clock source						
			   *	T2_SOURCE_EXT						
			   *	T2_SOURCE_INT						
			   
		  period - This contains the period match value to be stored 
		  into the PR register 
 
Return Value      : None
 
Remarks           : This function configures the 16-bit Timer Control register and 
                    sets the period match value into the PR register. 
**********************************************************************************/
void OpenTimer2(unsigned int config,unsigned int period)
{
    TMR2  = 0;          /* Reset Timer2 to 0x0000 */
    PR2   = period;     /* assigning Period to Timer period register */
    T2CON = config;     /* configure control reg */
    #if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3)|| defined (tmr_v1_4)
	T2CONbits.T32 = 0;
	#endif
	
}

#else
#warning "Does not build on this target"
#endif
