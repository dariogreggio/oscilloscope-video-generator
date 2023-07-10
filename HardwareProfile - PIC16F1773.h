/********************************************************************
 FileName:     	HardwareProfile - PIC16F1773 PIM.h
 Dependencies:  See INCLUDES section
 Processor:     PIC16F1773
 Hardware:      PIC16F1773 PIM
 Compiler:      Microchip XC8
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
				22.6.2017		porcodio GC
 * morti ovunque 8/7/23 GD/C
********************************************************************/

#ifndef HARDWARE_PROFILE_PIC16F1773_PIM_H
#define HARDWARE_PROFILE_PIC16F1773_PIM_H

    //Uncomment this to make the output HEX of this project 
    //   to be able to be bootloaded using the HID bootloader
//    #define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER	

    //If the application is going to be used with the HID bootloader
    //  then this will provide a function for the application to 
    //  enter the bootloader from the application (optional)
    #if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
//        #define EnterBootloader() __asm__("goto 0x400")
    #endif   


    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/

    /** Board definition ***********************************************/
    //These definitions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
    
        #define GetSystemClock()            32000000UL
        #define GetPeripheralClock()        (GetSystemClock()/4)
        #define GetInstructionClock()       (GetSystemClock()/4)
				#define _XTAL_FREQ (GetSystemClock()/4)

    


    /** LED ************************************************************/

		#define mInitAllLEDs()      LATB &= 0b11111111; TRISB &= 0b11001111; 
    
#define LED0_TRIS			(TRISBbits.TRISB2)	// simil pin del pic24
#define LED0_IO				(LATBbits.LATB2)
#define LED1_TRIS			(TRISBbits.TRISB3)	// 
#define LED1_IO				(LATBbits.LATB3)

		// 
    #define mLED_1              LATBbits.LATB2
    #define mGetLED_1()         mLED_1
    #define mLED_1_On()         mLED_1 = 1;
    #define mLED_1_Off()        mLED_1 = 0;
    #define mLED_1_Toggle()     mLED_1 ^= 1;
    #define mLED_2              LATBbits.LATB3
    #define mGetLED_2()         mLED_2
    #define mLED_2_On()         mLED_2 = 1;
    #define mLED_2_Off()        mLED_2 = 0;
    #define mLED_2_Toggle()     mLED_2 ^= 1;


    
		// OSCI e OSCO, come pure SOSCI e SOSCO .. meglio lasciarli liberi...

    /** SWITCH *********************************************************/
    #define mInitSwitch1()      TRISBbits.TRISB0=1;
    #define mInitSwitch2()      TRISBbits.TRISB1=1;

    #define mInitAllSwitches()  mInitSwitch1();mInitSwitch2();
    #define sw1                 PORTBbits.RB0
    #define sw2                 PORTBbits.RB1


		#define mSwitch1 PORTBbits.RB0
		#define mSwitch2 PORTBbits.RB1



    /** POT ************************************************************/
//    #define mInitPOT()  {AD1PCFGLbits.PCFG5 = 0;    AD1CON2bits.VCFG = 0x0;    AD1CON3bits.ADCS = 0xFF;    AD1CON1bits.SSRC = 0x0;    AD1CON3bits.SAMC = 0b10000;    AD1CON1bits.FORM = 0b00;    AD1CON2bits.SMPI = 0x0;    AD1CON1bits.ADON = 1;}
// 		RB13

    
    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0


#endif  //HARDWARE_PROFILE_PIC16F1773_PIM_H

