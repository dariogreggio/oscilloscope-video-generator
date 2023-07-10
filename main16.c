/********************************************************************
 FileName:		main.c
 Dependencies:	See INCLUDES section
 Processor:		PIC18, PIC24, and PIC32 USB Microcontrollers
 Hardware:		This demo is natively intended to be used on Microchip USB demo
 				boards supported by the MCHPFSUSB stack.  See release notes for
 				support matrix.  This demo can be modified for use on other hardware
 				platforms.
 Compiler:  	Microchip C18 (for PIC18), C30 (for PIC24), C32 (for PIC32)
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the ?Company?) for its PIC� Microcontroller is intended and
 supplied to you, the Company?s customer, for use solely and
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
  Rev   Description
  ----  -----------------------------------------
  2.6a  Added support for PIC24FJ256GB210

  2.7   No change

  2.8   Improvements to USBCBSendResume(), to make it easier to use.
  2.9   Added event transfer terminated handler code, for improved MSD
        error case handling.  Increased RAM reserved for the C software 
        stack on PIC18 devices.  The previous version did not allocate
        enough RAM for the worst case scenario, when USB_INTERRUPTS mode
        was used, causing potentially unexpected operation.

 GD 2/7/2023
	Generatore segnali video per oscilloscopio (asse X-Y-Z)
			
********************************************************************/


/** CONFIGURATION **************************************************/


// PIC16F1773 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = ON        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit cannot be cleared once it is set by software)
#pragma config ZCD = OFF        // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR)
#pragma config PLLEN = ON       // Phase Lock Loop enable (4x PLL is always enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

/** INCLUDES *******************************************************/

#include "GenericTypeDefs.h"

#include "HardwareProfile.h"

#include "ep512.h"


/** VARIABLES ******************************************************/


static const char CopyrString[]= {'O','s','c','i','l','l','o','s','c','o','p','e',' ','g','e','n','e','r','a','t','o','r',
	'v',VERNUMH+'0','.',VERNUML/10+'0',(VERNUML % 10)+'0', ' ','1','0','/','7','/','2','3', 0 };





volatile WORD tick10=0;
volatile BYTE second_10=0;
volatile DWORD milliseconds;

WORD LastAD;

BYTE videoRAM[(X_SIZE*Y_SIZE*BPP)/8];


#define TickGet() (tick10)

/** PRIVATE PROTOTYPES *********************************************/
static void InitializeSystem(void);
int UserInit(void);
BYTE initADC(void);
BYTE initGen(void);

BYTE OpenTimer1(BYTE control,WORD time);
BYTE OpenTimer2(BYTE control,BYTE control2,WORD time);
void ConvertADC(void);
BYTE BusyADC(void);
WORD ReadADC(void);



/** DECLARATIONS ***************************************************/



/********************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *******************************************************************/

int main(void) {   
	WORD i;

TRISB=0;
mLED_1=mLED_2=0;

mLED_1=1;

//	ecan1ClkInit(250000L);

	__delay_ms(50);		// vale *20~ non essendoci ancora PLL!
	CLRWDT();
  InitializeSystem();

	__delay_ms(100);
	CLRWDT();

mLED_2=1;

	/*TRISA=0;
	while(1) {
		LATA ^= 0xffff;
		CLRWDT();
		}*/


//  USARE HEF ! DataEEInit();
	CLRWDT();
//  dataEEFlags.val = 0;
  NOP();
  NOP();



	UserInit();


	ConvertADC();			// SCATENA la prima conversione :)


Beep();

	initADC();
	initGen();


	screenCLS(0);
	drawLine(10, 60, 90, 60, 1);


  while(1) {

		CLRWDT();
//		LATB ^= 0xffff;


// Application-specific tasks.

//	mLED_2_Toggle(); 




		UserTasks();
	
	  } //end while
    
  
	} //end main

/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 *******************************************************************/
static void InitializeSystem(void) {

	CLRWDT();

	LED0_TRIS=0; 	LED1_TRIS=0;
//	BUTTON0_TRIS=1; BUTTON1_TRIS=1; BUTTON2_TRIS=1; per debug no..
		// 
	LATA = 0b00000000;
	LATB = 0b00000000;
	TRISA= 0b00000001;		// 1 ana
	TRISB= 0b11000011;		// 2 switch; 2 led
	ANSELA=0x00;
	ANSELB=0x00;
	


// 		//pulsanti
	WPUBbits.WPUB1=1;
	WPUBbits.WPUB0=1;



	OpenTimer1(0b00110001 /* PS 1:8*/, TMR2BASE);		//10Hz per timing
  PIE1bits.TMR1IE=1;      //EnableIntT1;


	CLRWDT();		// xch� qua ho disattivato! ma lo lascio al boot...
	



  CM1CON0=0;		// comparatori off qua ?? boh


// buzzer 4KHz
  /* Reset PWM */
  CCPTMRS1 = 0b00000000;     // FINIRE!
  
  CCP1CON = 0b00000000;
  
  
  /* set PWM duty cycle to 50% */
  CCPR2L  = BEEP_STD_FREQ/2  /* basato su SysClock => 4KHz circa ecc (16MHz / 256) */; //PWM_PERIOD >> 1; /* set the duty cycle tp 50% */
  CCPR2H  = BEEP_STD_FREQ  /* se uso Timer come Src SEMBRA NON FARE NULLA... qua boh! */;  //PWM_PERIOD - 1;  /* set the period */
  
  /* configure PWM */
	CCPR2L=(BEEP_STD_FREQ/2);
//	CCP1CONbits.DC1B=0;
	PR4=BEEP_STD_FREQ;

	T4CONbits.TMR4ON=1;
  
  /* enable the PWM */
//  OC4CON1 |= 0x0006;   /* Mode 6, Edge-aligned PWM Mode */ //  v. beep



	} //end InitializeSystem


int UserInit(void) {

	CLRWDT();

  DAC1CON0=0b11100000;    // ON, left justified, output on pin 1
  DAC2CON0=0b11100000;
  DAC5CON0=0b11100000;

	initADC();

	return 1;
	}



void UserTasks(void) {
	static BYTE oldSw=3;
	static WORD cnt=0,cnt2=0;


	if(second_10) {			// 
		second_10=0;

		cnt++;
		cnt2++;

		mLED_2^=1;


		if(cnt2>=8) {
			cnt2=0;
			if(!PORTBbits.RB5) {		// TEST MESSAGGI USB
				}
			}

		if(!BusyADC()) {			// controllo solo di non essere in mezzo alla conv.
		  LastAD=ReadADC();
			ConvertADC();
			}
	

/*	  if(LastAD>500)
			mLED_1=1;
		else
			mLED_1=0;
*/
		

		oldSw=(sw1 ? 1 : 0) | (sw2 ? 2 : 0);

		}		// second_10



	}


BYTE initGen(void) {
	WORD n;
	int i;
	BYTE retVal=1;

			OpenTimer2(0b10000000, 0b00000001, TMR3BASE);
			PIE1bits.TMR2IE=1;      //EnableIntT2;

/*			PPSUnLock;
			PPSOut(_OC1, _RP37);      // output (pwm cmq)
			PPSOut(_OC2, _RP38);      //
			PPSOut(_OC3, _RP39);      //
			PPSLock;*/

	return retVal;
	}

BYTE initADC(void) {

	{

			ADCON0 = 0b00000000;			// On, AN0
			ADCON1 = 0b11100000;			// VRef VDD/GND, left justify, Fosc/64
			ADCON2 = 0b00000000;			// no auto trigger

//ahem  	OpenADC(Adcon1_reg,Adcon2_reg,Adcon3_reg,Adcon4_reg,configscan_lo);      // Turn on ADC module
//		SetChanADC(ADC_CH0_NEG_SAMPLEB_VREFN & ADC_CH0_NEG_SAMPLEA_VREFN 
//			&	ADC_CH0_POS_SAMPLEA_AN0	&	ADC_CH0_POS_SAMPLEB_AN0,0);
//		EnableADC;
	}

	ANSELA= 0b00000001;			// in caso mettere 1; 
	ANSELB= 0b00000000;			// idem
	return 1;

	}


void Beep(void) {

  CCPR2L  = BEEP_STD_FREQ/2;
  CCPR2H  = BEEP_STD_FREQ;

  T4CONbits.ON=1;
	__delay_ms(100);
	CLRWDT();
	__delay_ms(100);
	CLRWDT();
	__delay_ms(100);
	CLRWDT();
  T4CONbits.ON=0;
	}


void EEscrivi_(BYTE addr,BYTE n) {	// 
  
  DataEEWrite(n,addr);
  }
BYTE EEleggi(BYTE addr) {
  
  return DataEERead(addr);
  }



BYTE OpenTimer1(BYTE control,WORD time) {
  
  T1CON=control;
  T1GCON=0b00000000;
  
  }

BYTE OpenTimer2(BYTE control,BYTE control2,WORD time) {
  
  T2CON=control;
  T2CLKCON=control2;
  T2HLT=0b00000000;
  T2RST=0b00000000;
  T2PR=time;
  }


void ConvertADC(void) {
  
  ADCON0bits.GO=1;
  }

BYTE BusyADC(void) {
  
  return ADCON0bits.GO;
  }

WORD ReadADC(void) {
  
  return ADRESH;
  }

