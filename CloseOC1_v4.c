 
#include <outcompare.h>

#if defined (ocmp_v2_1) ||defined (ocmp_v2_2)|| defined (ocmp_v2_3)|| defined (ocmp_v2_4)|| defined (ocmp_v2_5)|| defined (LIB_BUILD)
/**************************************************************************
Function Prototype : void CloseOC1_v4(void) 

Include            : outcompare.h
 
Description        : This function turns off the Output Compare module.
 
Arguments          : None
 
Return Value       : None
 
Remarks            : This function disables the Output Compare interrupt and 
                     then turns off the module. The Interrupt Flag bit is 
                     also cleared.
**************************************************************************/

void CloseOC1_v4(void)
{   
    IEC0bits.OC1IE = 0;  /* Disable the Interrupt bit in IEC Register */
    OC1CON1bits.OCM = 0;  /* Turn off Output Compare1 */
    IFS0bits.OC1IF = 0;  /* Disable the Interrupt Flag bit in IFS Register */
}

#else
#warning "Does not build on this target"
#endif
