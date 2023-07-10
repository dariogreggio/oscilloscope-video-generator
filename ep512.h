

#define SERNUM      1000
#define VERNUMH     1
#define VERNUML     0


//#define FLASH_TIME 7

#if defined (__PIC24)
#define X_SIZE 128UL
#define Y_SIZE 128UL
#define BPP 2
#define FPS 25
#else
#define X_SIZE 60UL
#define Y_SIZE 60UL
#define BPP 1
#define FPS 25
#endif

extern BYTE videoRAM[(X_SIZE*Y_SIZE*BPP)/8];

unsigned char screenCLS(BYTE c);
unsigned char drawLine(WORD x1, WORD y1, WORD x2, WORD y2, BYTE c);


#define NUM_SAMPLES 128


#if defined (__PIC24)
// il Timer0 conta ogni 14nSec*prescaler... (@140MHz CPUCLK => 70MHz) su PIC24EP
#define TMR2BASE (27355)		//   10Hz per timer
#define TMR3BASE ((1000000000.0/(X_SIZE*Y_SIZE*FPS)) / (1000000000.0/GetPeripheralClock()))	// 170;  2.5uS per 25FpS @128x128
#define TMR3BASE_2 300 // voglio 2KHz/200Hz => 4uS per 128 campioni
#define BEEP_STD_FREQ 1000
#else
// il Timer0 conta ogni 125nSec*prescaler... (@32MHz CPUCLK => 8MHz) su PIC16F
#define TMR2BASE (27355)		//   10Hz per timer
#define TMR3BASE ((1000000000.0/(X_SIZE*Y_SIZE*FPS)) / (1000000000.0/GetPeripheralClock()))	// 170;  2.5uS per 25FpS @128x128
#define TMR3BASE_2 300 // voglio 2KHz/200Hz => 4uS per 128 campioni
#define BEEP_STD_FREQ 100
#endif



BYTE EEleggi(BYTE);
void EEscrivi_(BYTE,BYTE);



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


