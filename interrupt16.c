#include <xc.h>


#include "HardwareProfile.h"
#include "generictypedefs.h"


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

	

void interrupt _T1Interrupt(void) {
  
  if(PIR1bits.TMR2IF) {
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
      DAC2REFH = ycnt;
      }
    DAC1REFH = xcnt;

#if BPP==1
    switch(xcnt & 7) {			// 1bpp
      case 0:
        b = (*pixelPos >> 7) & 1;
        break;
      case 1:
        b = (*pixelPos >> 6) & 1;
        break;
      case 2:
        b = (*pixelPos >> 5) & 1;
        break;
      case 3:
        b = (*pixelPos >> 4) & 1;
        break;
      case 4:
        b = (*pixelPos >> 3) & 1;
        break;
      case 5:
        b = (*pixelPos >> 2) & 1;
        break;
      case 6:
        b = (*pixelPos >> 1) & 1;
        break;
      case 7:
        b = *pixelPos & 1;
        pixelPos++;
        break;
      }
    switch(b) {			// 2bpp
      case 0:
        DAC5REFH = 0;
        break;
      case 1:
        DAC5REFH = 255;
        break;
      }
#endif
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
        DAC5REFH = 0;
        break;
      case 1:
        DAC5REFH = 5;
        break;
      case 2:
        DAC5REFH = 10;
        break;
      case 3:
        DAC5REFH = 15;
        break;
      }
#endif

    DACLD=0b00010011;   // SERVE??

    PIR1bits.TMR2IF = 0; 			//Clear the Timer3 interrupt status flag
    }
  
  if(PIR1bits.TMR1IF) {
  // dev'essere 10Hz

  //		mLED_2^=1;		// check timing 10mS 5/7/2023 MORTE AGLI INGLESI MORTE AGLI AMERICANI MORTE A VOI TUTTI MERDE DI MERDA

    tick10++;
    divider1s++;

    second_10=1;					// flag
    if(divider1s==10) {		// per RealTimeClock
      divider1s=0;

      }

    PIR1bits.TMR1IF = 0; 			//Clear the Timer1 interrupt status flag
    }
	}





