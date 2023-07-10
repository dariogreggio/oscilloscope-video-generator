#include <stdio.h>

#include <timer.h>

#include "HardwareProfile.h"
#include "generictypedefs.h"

#include <libpic30.h>

#include "ep512.h"


extern volatile WORD tick10;
extern volatile BYTE second_10;
BYTE divider1s;
extern volatile DWORD milliseconds;

extern BYTE videoRAM[(X_SIZE*Y_SIZE*BPP)/8];



/** VECTOR REMAPPING ***********************************************/
    #if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
        /*
         *	ISR JUMP TABLE
         *
         *	It is necessary to define jump table as a function because C30 will
         *	not store 24-bit wide values in program memory as variables.
         *
         *	This function should be stored at an address where the goto instructions 
         *	line up with the remapped vectors from the bootloader's linker script.
         *  
         *  For more information about how to remap the interrupt vectors,
         *  please refer to AN1157.  An example is provided below for the T2
         *  interrupt with a bootloader ending at address 0x1400
         */
//        void __attribute__ ((address(0x1404))) ISRTable(){
//        
//        	asm("reset"); //reset instruction to prevent runaway code
//        	asm("goto %0"::"i"(&_T2Interrupt));  //T2Interrupt's address
//        }
    #endif


// ---------------------------------------------------------------------------------------
void _ISR __attribute__((__no_auto_psv__)) _AddressError(void) {
	Nop();
	Nop();
	}

void _ISR __attribute__((__no_auto_psv__)) _StackError(void) {
	Nop();
	Nop();
	}
	

void __attribute__ (( interrupt, /*shadow*/,  no_auto_psv )) _T2Interrupt(void) {
// dev'essere 10Hz

//		mLED_2^=1;		// check timing 10mS 5/7/2023 MORTE AGLI INGLESI MORTE AGLI AMERICANI MORTE A VOI TUTTI MERDE DI MERDA

	tick10++;
	divider1s++;

	second_10=1;					// flag
	if(divider1s==10) {		// per RealTimeClock
		divider1s=0;

		}

	IFS0bits.T2IF = 0; 			//Clear the Timer2 interrupt status flag
	// non lo trova @#£$% T2_Clear_Intr_Status_Bit; 	
	}



void __attribute__ (( interrupt, shadow,  no_auto_psv )) _T3Interrupt(void) {
	static BYTE *pixelPos=&videoRAM;
	static BYTE xcnt,ycnt;
	BYTE b;


		mLED_1^=1;		// check timing ~2.5uS 5/7/2023 MORTE AGLI INGLESI MORTE AGLI AMERICANI MORTE A VOI MERDE DI MERDA

	xcnt++;
	if(xcnt>=X_SIZE) {
		xcnt=0;
		ycnt++;
		if(ycnt>=Y_SIZE) {
			ycnt=0;
		  pixelPos=&videoRAM;
			}
  	OC2R   = ycnt;
		}
	OC1R   = xcnt;

#if BPP==2
	switch(xcnt & 3) {			// 2bpp
		case 0:
		  b = (*pixelPos >> 6) & 3;
			break;
		case 1:
		  b = (*pixelPos >> 4) & 3;
			break;
		case 2:
		  b = (*pixelPos >> 2) & 3;
			break;
		case 3:
		  b = *pixelPos & 3;
		  pixelPos++;
			break;
		}
	switch(b) {			// 2bpp
		case 0:
		  OC3R   = 0;
			break;
		case 1:
		  OC3R   = 5;
			break;
		case 2:
		  OC3R   = 10;
			break;
		case 3:
		  OC3R   = 15;
			break;
		}
#endif


	IFS0bits.T3IF = 0; 			//Clear the Timer3 interrupt status flag
	// non lo trova @#£$% T3_Clear_Intr_Status_Bit; 	
	}


