 
#include <timer.h>

#if defined (tmr_v1_1) || defined (tmr_v1_2)|| defined (tmr_v1_3)|| defined (tmr_v1_4) || defined (tmr_v2_1) || defined (tmr_v2_2) || defined (LIB_BUILD)

/****************************************************************************
Function Prototype : void CloseTimer1(void)
 
Include            : timer.h
 
Description        : This function turns off the 16-bit timer module.
 
Arguments          : None
 
Return Value       : None
 
Remarks            : This function first disables the 16-bit timer interrupt
                     and then turns off the timer module. The Interrupt 
                     Flag bit (TxIF) is also cleared.
****************************************************************************/

void CloseTimer1(void)
{
    IEC0bits.T1IE = 0;      /* Disable the Timer1 interrupt */
    T1CONbits.TON = 0;      /* Disable timer1 */
    IFS0bits.T1IF = 0;      /* Clear Timer interrupt flag */
}

#else
#warning "Does not build on this target"
#endif
