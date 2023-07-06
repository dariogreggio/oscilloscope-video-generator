/********************************************************************
 FileName:		main.c
 Dependencies:	See INCLUDES section
 Processor:		PIC18, PIC24, and PIC32 USB Microcontrollers
 Hardware:		This demo is natively intended to be used on Microchip USB demo
 				boards supported by the MCHPFSUSB stack.  See release notes for
 				support matrix.  This demo can be modified for use on other hardware
 				platforms.
 Complier:  	Microchip C18 (for PIC18), C30 (for PIC24), C32 (for PIC32)
 Company:		Microchip Technology, Inc.

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

 GD 6/7/2023
	Generatore figure di Lissajous per oscilloscopio (asse X-Y)
			
********************************************************************/

/** INCLUDES *******************************************************/

#include <timer.h>
//#include <ports.h>
#include <outcompare.h>
#include <ppsnew.h>
#include <adc.h>
#include "GenericTypedefs.h"
//#include "wdt.h"
//#include "PwrMgnt.h"

#include "HardwareProfile.h"

#include <libpic30.h>
#include "ep512.h"

#include "dee emulation 16-bit.h"


/** CONFIGURATION **************************************************/

#ifdef __XC16__

// PIC24EP512GP202 Configuration Bit Settings
// 'C' source line config statements

// FICD
#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FPOR
#pragma config ALTI2C1 = OFF            // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
#pragma config WDTWIN = WIN25           // Watchdog Window Select bits (WDT Window is 25% of WDT period)

// FWDT
#pragma config WDTPOST = PS4096         // Watchdog Timer Postscaler bits (1:4,096)
#pragma config WDTPRE = PR32            // Watchdog Timer Prescaler bit (1:32)
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bit (Watchdog timer always enabled)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration (Allow only one reconfiguration)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FOSCSEL
#pragma config FNOSC = FRCPLL           // Oscillator Source Selection (Fast RC Oscillator with divide-by-N with PLL module (FRCPLL))
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)
#endif
#if defined(__PIC24EP512GU810__)		// 
_FGS( GWRP_OFF & GSS_OFF & GSSK_OFF ) 
_FOSCSEL(FNOSC_PRIPLL & IESO_OFF)			//FNOSC_FRCPLL 
_FOSC( POSCMD_HS & OSCIOFNC_OFF & IOL1WAY_OFF & FCKSM_CSDCMD )
_FWDT( WDTPOST_PS4096 & WDTPRE_PR32 & PLLKEN_ON & WINDIS_OFF & FWDTEN_ON )
_FPOR( FPWRT_PWR8 & BOREN_ON & ALTI2C1_OFF & ALTI2C2_OFF )
_FICD( ICS_PGD3 & RSTPRI_PF & JTAGEN_OFF )		// 
_FAS( AWRP_OFF & APL_OFF & APLK_OFF)
//_FUID0(x) simpa..
#endif


/** VARIABLES ******************************************************/
#pragma udata


static const char CopyrString[]= {'O','s','c','i','l','l','o','s','c','o','p','e',' ','g','e','n','e','r','a','t','o','r',
	'v',VERNUMH+'0','.',VERNUML/10+'0',(VERNUML % 10)+'0', ' ','0','6','/','7','/','2','3', 0 };


const WORD SINE_WAVE_TABLE[NUM_SAMPLES]={
	0x8000,0x8654,0x8ca4,0x92ed,0x992a,0x9f57,0xa570,0xab72,
	0xb159,0xb720,0xbcc6,0xc245,0xc79a,0xccc3,0xd1bc,0xd681,
	0xdb10,0xdf67,0xe381,0xe75d,0xeaf9,0xee51,0xf164,0xf430,
	0xf6b4,0xf8ed,0xfada,0xfc7a,0xfdcd,0xfed0,0xff84,0xffe8,
	0xfffc,0xffc0,0xff34,0xfe58,0xfd2d,0xfbb4,0xf9ed,0xf7da,
	0xf57b,0xf2d3,0xefe3,0xecad,0xe933,0xe577,0xe17c,0xdd43,
	0xd8d0,0xd425,0xcf46,0xca35,0xc4f5,0xbf8a,0xb9f8,0xb441,
	0xae69,0xa874,0xa266,0x9c42,0x960d,0x8fca,0x897d,0x832a,
	0x7cd5,0x7682,0x7035,0x69f2,0x63bd,0x5d99,0x578b,0x5196,
	0x4bbe,0x4607,0x4075,0x3b0a,0x35ca,0x30b9,0x2bda,0x272f,
	0x22bc,0x1e83,0x1a88,0x16cc,0x1352,0x101c,0xd2c,0xa84,
	0x825,0x612,0x44b,0x2d2,0x1a7,0xcb,0x3f,0x3,
	0x17,0x7b,0x12f,0x232,0x385,0x525,0x712,0x94b,
	0xbcf,0xe9b,0x11ae,0x1506,0x18a2,0x1c7e,0x2098,0x24ef,
	0x297e,0x2e43,0x333c,0x3865,0x3dba,0x4339,0x48df,0x4ea6,
	0x548d,0x5a8f,0x60a8,0x66d5,0x6d12,0x735b,0x79ab,0x8000};
//https://daycounter.com/Calculators/Sine-Generator-Calculator.phtml
WORD samplesTable[NUM_SAMPLES],samplesTable2[NUM_SAMPLES];




volatile WORD tick10=0;
volatile BYTE second_10=0;
volatile DWORD milliseconds;

WORD LastAD;


#define TickGet() (tick10)

/** PRIVATE PROTOTYPES *********************************************/
static void InitializeSystem(void);
int UserInit(void);
BYTE initADC(void);
BYTE initGen(void);




/** DECLARATIONS ***************************************************/
#pragma code



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
	ClrWdt();
  InitializeSystem();

	__delay_ms(100);
	ClrWdt();

mLED_2=1;

	/*TRISA=0;
	while(1) {
		LATA ^= 0xffff;
		ClrWdt();
		}*/


//  DataEEInit();
	ClrWdt();
  dataEEFlags.val = 0;
  Nop();
  Nop();



	for(i=0; i<NUM_SAMPLES; i++)
		samplesTable[i]=SINE_WAVE_TABLE[i] >> 6;
	for(i=0; i<NUM_SAMPLES; i++)
		samplesTable2[i]=SINE_WAVE_TABLE[i] >> 6;


	UserInit();


	ConvertADC10();			// SCATENA la prima conversione :)


Beep();

	initADC();
	initGen();


  while(1) {

		ClrWdt();
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

	ClrWdt();

	LED0_TRIS=0; 	LED1_TRIS=0;
//	BUTTON0_TRIS=1; BUTTON1_TRIS=1; BUTTON2_TRIS=1; per debug no..
		// 
	LATA = 0b0000000000000000;
	LATB = 0b0000000000000000;
	TRISA= 0b0000000000000001;		// 1 ana
	TRISB= 0b1100000000000000;		// 2 switch; 2 led
	ANSELA=0x0000;
	ANSELB=0x0000;
	

	OSCTUN=0;			//
// (280*8)/(8*2) = 140

	PLLFBD = 74; // M = PLLFBD + 2 = 70; OVERCLOCCO per andare a 8 anziché 7.37 :) v. anche OSCTUNE
  CLKDIVbits.PLLPOST = 0; // N2 = 2
  CLKDIVbits.PLLPRE = 0; // N1 = 2

/*	
  Fosc= Fin*M/(N1*N2)
	0.8MHz<(Fin/N1)<8MHz
	100MHz<(Fin*M/N1)<340MHz
	M=2,3,4,...513
	N1=2...33
	N2=2,4,8
	
	PLLFBD    = M -2;
	CLKDIVbits.PLLPRE = N1 -2;
	CLKDIVbits.PLLPOST = 0b00; //N2={2,4,R,8} */

//OSCCONbits.CLKLOCK=1;OSCCONbits.NOSC=1;OSCCONbits.OSWEN=1;
//  while (OSCCONbits.COSC != 0x7)LATB ^= 1;; 


	//Wait for the Primary PLL to lock and then
       // configure the auxiliary PLL to provide 48MHz needed for USB
       // Operation.
#ifndef __DEBUG
  while(OSCCONbits.LOCK != 1) 
		ClrWdt();			// boh?
#endif

  OSCTUN=10;			// v.sopra PLL

	
    //********* Initialize Peripheral Pin Select (PPS) *************************
    //  This section only pertains to devices that have the PPS capabilities.
    //    When migrating code into an application, please verify that the PPS
    //    setting is correct for the port pins that are used in the application.
// non le trova... manco in XC... froci urfidi...@$%&
// http://www.microchip.com/forums/m801504.aspx  MBedder !
#define PPSIn(fn,pin)    iPPSInput(IN_FN_PPS##fn,IN_PIN_PPS##pin)
#define PPSOut(fn,pin)    iPPSOutput(OUT_PIN_PPS##pin,OUT_FN_PPS##fn)

//	PPSOut(_U1TX, _RP126);      // TXD 
//	PPSIn(_U1RX, _RP125);      // RXD 

	PPSUnLock;

	PPSOut(_OC4, _RP20);      // buzzer 4KHz , qua è rimappabile

	PPSOut(_OC1, _RP37);      // output (pwm cmq)
	PPSOut(_OC2, _RP38);      // 
	PPSOut(_OC3, _RP39);      // 

	PPSLock;




// non c'è...	EnablePullUpCN20;			//pulsanti
	CNPUBbits.CNPUB15=1;
	CNPUBbits.CNPUB14=1;



	OpenTimer2(T2_ON & T2_IDLE_CON & T2_GATE_OFF & T2_32BIT_MODE_OFF & T2_PS_1_256 & T2_SOURCE_INT,
		TMR2BASE);		//10Hz per timing
	ConfigIntTimer2(T2_INT_PRIOR_4 & T2_INT_ON);
	EnableIntT2;


	{__asm__ volatile ("clrwdt");}		// xché qua ho disattivato! ma lo lascio al boot...
	



  CM3CON=0;		// comparatori off ?? boh


// buzzer 4KHz
  /* Reset PWM */
  OC4CON1 = 0x0000;
  OC4CON2 = 0x0000;
  
  /* set PWM duty cycle to 50% */
  OC4R    = FCY/2/BEEP_STD_FREQ/2  /* basato su SysClock => 4KHz circa ecc (16MHz / 256) */; //PWM_PERIOD >> 1; /* set the duty cycle tp 50% */
  OC4RS   = FCY/2/BEEP_STD_FREQ  /* se uso Timer come Src SEMBRA NON FARE NULLA... qua boh! */;  //PWM_PERIOD - 1;  /* set the period */
  
  /* configure PWM */
  OC4CON2 = 0x001f;   /* 0x001F = Sync with This OC module                               */
  OC4CON1 = 0x1c00 /* 0x0400 => src=Timer3 */;  /* 0x1C08 = Clock source Fcyc, trigger mode 1, Mode 0 (disable OC1) */
  
  /* enable the PWM */
//  OC4CON1 |= 0x0006;   /* Mode 6, Edge-aligned PWM Mode */ //  v. beep



	} //end InitializeSystem


int UserInit(void) {

	ClrWdt();

  OC1CON1 = 0x0000;
  OC1CON2 = 0x0000;
  
  OC1RS  = 32768;
  OC1R   = 16384;
  
  OC1CON2 = 0x001f;
  OC1CON1 = 0x1c00;
  
  OC1CON1 |= 0x0006;   /* Mode 6, Edge-aligned PWM Mode */ //  

  OC2CON1 = 0x0000;
  OC2CON2 = 0x0000;
  
  OC2RS  = 32768;
  OC2R   = 16384;
  
  OC2CON2 = 0x001f;
  OC2CON1 = 0x1c00;
  
  OC2CON1 |= 0x0006;   /* Mode 6, Edge-aligned PWM Mode */ //  

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

		if(!BusyADC10()) {			// controllo solo di non essere in mezzo alla conv.
		  LastAD=ReadADC10(0);
			ConvertADC10();
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

			OpenTimer3(T3_ON & T3_IDLE_CON & T3_GATE_OFF & T3_PS_1_1 & T3_SOURCE_INT, 
				TMR3BASE_2);
			EnableIntT3;

		  OC1RS    = 0x3ff;		//70KHz
		  OC2RS    = 0x3ff;
  
		  OC1CON1 = 0x1c00;
  		OC1CON1 |= 0x0006;
		  OC2CON1 = 0x1c00;
  		OC2CON1 |= 0x0006;
/*			PPSUnLock;
			PPSOut(_OC1, _RP37);      // output (pwm cmq)
			PPSOut(_OC2, _RP38);      //
			PPSLock;*/

	return retVal;
	}

BYTE initADC(void) {

	{
	unsigned int Adcon5_reg, Adcon3_reg, Adcon2_reg, Adcon1_reg,
		configctmu_lo,configctmu_hi,configscan_lo,configscan_hi;
/*config1  This contains the parameters to be configured in the ADCON1 register 
config2  This contains the parameters to be configured in the ADCON2 register  
config3  This contains the parameters to be configured in the ADCON3  
config4  This contains the parameters to be configured in the ADCON5  
configctmu_low  This contains the scan select parameter to be configured into the AD1CTMUENL  
configctmu_high  This contains the scan select parameter to be configured into the AD1CTMUENH  
configscan_low  This contains the scan select parameter to be configured into the AD1CSSL  
configscan_high  This contains the scan select parameter to be configured into the AD1CSSH  
*/


   unsigned int Adcon4_reg;

     configscan_lo      =   ADC_SKIP_SCAN_AN0 &         // Scan for AN0-AN3
                            ADC_SKIP_SCAN_AN1 &
                            ADC_SKIP_SCAN_AN2 &
                            ADC_SKIP_SCAN_AN3 &
                            ADC_SKIP_SCAN_AN4 &
                            ADC_SKIP_SCAN_AN5 &
                            ADC_SKIP_SCAN_AN10 &
                            ADC_SKIP_SCAN_AN11;


     Adcon5_reg      =      0;    // AD1CON4 qua, ossia DMA

     Adcon4_reg      =     ENABLE_AN0_ANA &            // 
                          ENABLE_AN1_DIG &
                          ENABLE_AN2_DIG &
                          ENABLE_AN3_DIG &
													ENABLE_AN4_DIG &
													ENABLE_AN5_DIG &
													ENABLE_AN10_DIG &
													ENABLE_AN11_DIG ;

     Adcon3_reg      =      ADC_SAMPLE_TIME_16 &                  // Sample for 10 time
														ADC_CONV_CLK_SYSTEM  &      // system Clock
                            ADC_CONV_CLK_8Tcy;      		// così, con 8Tcy ci mette circa 28uSec per una conversione
     
     Adcon2_reg      =      ADC_VREF_AVDD_AVSS &            // Vref at Vdd and Vss
                            ADC_SCAN_OFF &                    // Enable scan for ADC
                            ADC_ALT_BUF_OFF &                // Disable alternate buffer
                            ADC_ALT_INPUT_OFF &            // Disable alternate input
                            ADC_INTR_16_CONV  /*ADC_INTR_EACH_CONV*/;      // 16 sample between interrupt
     

     Adcon1_reg      =      ADC_MODULE_ON &                  // Enable module ADC
                            ADC_IDLE_CONTINUE &            // ADC run on idle mode
														ADC_10BIT_MODE &
                            ADC_FORMAT_INTG &               // Output value integer format
                            ADC_SAMP_OFF &      			// ADC sampling simultaneous
                            ADC_AUTO_SAMPLING_ON;      // ADC auto sampling      

			AD1CON1 = 0b1001000011100000;			// On, 10bits, noDMA, integer mode, manual sampling and auto conversion
			AD1CON2 = 0b0000000000000000;			// VRef VDD/GND, channel 0, no scan, interrupt basic
			AD1CON3 = 0b0001000000100000;			// system clock, 16 Tad, 32*clock
			AD1CON4 = 0b0000000100000000;			//  DMA mode i.e. only ADC1BUF0
			AD1CHS123 = 0b0000000000000000;		// SampleB = VRef-, SampleA = CH0
			AD1CHS0 = 0b0000000000000000;			// CH0 = Sample+
			AD1CSSH = 0b0000000000000000;			// skips all
			AD1CSSL = 0b0000000000000000;			// "

//ahem  	OpenADC10(Adcon1_reg,Adcon2_reg,Adcon3_reg,Adcon4_reg,configscan_lo);      // Turn on ADC module
//		SetChanADC10(ADC_CH0_NEG_SAMPLEB_VREFN & ADC_CH0_NEG_SAMPLEA_VREFN 
//			&	ADC_CH0_POS_SAMPLEA_AN0	&	ADC_CH0_POS_SAMPLEB_AN0,0);
//		EnableADC1;
	}

	ANSELA= 0b0000000000000001;			// in caso mettere 1; v. sotto cmd 105 che legge e imposta!
	ANSELB= 0b0000000000000000;			// idem
	return 1;

	}


void Beep(void) {

  OC4R    = FCY/2/BEEP_STD_FREQ/2;
  OC4RS   = FCY/2/BEEP_STD_FREQ;

  OC4CON1 |= 0x0006;   /* Mode 6, Edge-aligned PWM Mode */
	__delay_ms(100);
	ClrWdt();
	__delay_ms(100);
	ClrWdt();
	__delay_ms(100);
	ClrWdt();
  OC4CON1 &= ~0x0006; 
	}


void EEscrivi_(BYTE addr,BYTE n) {	// 
  
  DataEEWrite(n,addr);
  }
BYTE EEleggi(BYTE addr) {
  
  return DataEERead(addr);
  }
