 
#include <timer.h>

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3)|| defined (tmr_v1_4) || defined (tmr_v2_1) || defined (tmr_v2_2) || defined (LIB_BUILD)
/****************************************************************************
Function Prototype : void CloseTimer2(void)
 
Include            : timer.h
 
Description        : This function turns off the 16-bit timer module.
 
Arguments          : None
 
Return Value       : None
 
Remarks            : This function first disables the 16-bit timer interrupt
                     and then turns off the timer module. The Interrupt 
                     Flag bit (TxIF) is also cleared.
****************************************************************************/

void CloseTimer2(void)
{
    IEC0bits.T2IE = 0;      /* Disable the Timer2 interrupt */
    T2CONbits.TON = 0;      /* Disable timer2 */
    IFS0bits.T2IF = 0;      /* Clear Timer interrupt flag */
}

#else
#warning "Does not build on this target"
#endif
