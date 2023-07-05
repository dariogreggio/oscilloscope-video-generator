 
#include <timer.h>

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3)|| defined (tmr_v1_4) || defined (tmr_v2_1) || defined (tmr_v2_2) || defined (LIB_BUILD)
/*******************************************************************************
Function Prototype : void OpenTimer3(unsigned int config,unsigned int period)
 
Include            : timer.h
 
Description        : This function configures the 16-bit timer module.
 
Arguments          : config - This contains the parameters to be configured in
                     the TxCON register as defined below
					 
			Timer Module On/Off						
			   *	T3_ON						
			   *	T3_OFF						
			Timer Module Idle mode On/Off						
			   *	T3_IDLE_CON						
			   *	T3_IDLE_STOP						
			Timer Gate time accumulation enable						
			   *	T3_GATE_ON						
			   *	T3_GATE_OFF						
			Timer prescaler						
			   *	T3_PS_1_1						
			   *	T3_PS_1_8						
			   *	T3_PS_1_64						
			   *	T3_PS_1_256											
			Timer clock source						
			   *	T3_SOURCE_EXT						
			   *	T3_SOURCE_INT						
		  period - This contains the period match value to be stored 
		  into the PR register 
 
Return Value      : None
 
Remarks           : This function configures the 16-bit Timer Control register and 
                    sets the period match value into the PR register. 
**********************************************************************************/
void OpenTimer3(unsigned int  config,unsigned int period)
{
    TMR3  = 0;      /* Reset Timer3 to 0x0000 */
    #if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3)|| defined (tmr_v1_4)
	PR3   = period; /* assigning Period to Timer period register.*/
    #endif
	T3CON = config; /* configure timer control reg */
}

#else
#warning "Does not build on this target"
#endif
