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
extern WORD LastAD;

extern const WORD SINE_WAVE_TABLE[NUM_SAMPLES];
extern WORD samplesTable[NUM_SAMPLES],samplesTable2[NUM_SAMPLES];



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
	static BYTE divider;
	static const WORD *ptr1=samplesTable,*ptr2=samplesTable+25  /*32*/;			// 90°
	static const short int *ptr3=samplesTable2;


		mLED_1^=1;		// check timing ~4uS 6/7/2023 MORTE AGLI INGLESI MORTE AGLI AMERICANI MORTE A VOI MERDE DI MERDA

	
  OC1R   = *ptr1;
  OC2R   = (*ptr2 /2) + (*ptr3 /5);

	divider++;
	ptr3++;
	if(divider>=10) {
		divider=0;
		ptr1++;
		ptr2++;
		}

	if(ptr1 >= (samplesTable+(NUM_SAMPLES))) {
		ptr1=samplesTable;
		}	
	if(ptr2 >= (samplesTable+(NUM_SAMPLES))) {
		ptr2=samplesTable;

#warning AGGANCIARE a LastAD per spostare fase!

		}	
	if(ptr3 >= (samplesTable2+(NUM_SAMPLES))) {
		ptr3=samplesTable2;
		}	

	IFS0bits.T3IF = 0; 			//Clear the Timer3 interrupt status flag
	// non lo trova @#£$% T3_Clear_Intr_Status_Bit; 	
	}


