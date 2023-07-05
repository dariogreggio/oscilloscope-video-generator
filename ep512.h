

#define SERNUM      1000
#define VERNUMH     0
#define VERNUML     1


//#define FLASH_TIME 7

#define X_SIZE 128UL
#define Y_SIZE 128UL
#define BPP 2
#define FPS 25

extern BYTE videoRAM[(X_SIZE*Y_SIZE*BPP)/8];


// il Timer0 conta ogni 14nSec*prescaler... (@140MHz CPUCLK => 70MHz) su PIC24EP
#define TMR2BASE (27355)		//   10Hz per timer
#define TMR3BASE 170 //((1000000.0/(X_SIZE*Y_SIZE*FPS)) * (2*1000000000.0/GetPeripheralClock()))	//   2.5uS per 25FpS @128x128



BYTE EEleggi(BYTE);
void EEscrivi_(BYTE,BYTE);


#define BEEP_STD_FREQ 1000

#define EEcopiaARAM(p) { *p=EEleggi(p); }
#define EEcopiaAEEPROM(p) EEscrivi_(p,*p)



	
#define DELAY_SPI_FAST 5
#define Delay08()	__delay_us(TIME_GRANULARITY)			// 1 bit-time 
#define Delay_SPI() __delay_us(DELAY_SPI_FAST /*DelaySPIVal*/)
#define Delay_1uS() __delay_us(1)
#define Delay_uS(x) __delay_us(x)
#define Delay_mS(x) __delay_ms(x)
#define Delay_1mS() Delay_mS(1)
void Delay_mS_LP(BYTE);


void Beep(void);


void UserTasks(void);


