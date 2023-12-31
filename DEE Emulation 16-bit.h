/************************************************************************
*
*   Emulating Data EEPROM for PIC24 Microcontrollers and
*           dsPIC Digital Signal Controllers
*
*************************************************************************
* FileName:     DEE Emulation 16-bit.h
* Compiler:     MPLAB XC16, v1.30 or higher
* Company:      Microchip Technology, Inc.
*
* Software License Agreement
*
* Copyright � 2016 Microchip Technology Inc. All rights reserved.
*
* Microchip licenses to you the right to use, modify, copy and distribute
* Software only when embedded on a Microchip microcontroller or digital
* signal controller, which is integrated into your product or third party
* product (pursuant to the sublicense terms in the accompanying license
* agreement).
*
* You should refer to the license agreement accompanying this Software for
* additional information regarding your rights and obligations.
*
*
* Author            Date        Comment
*************************************************************************
* D. Otten          2007/05/01  Version 1.0.0 - Initial Release
* D. Otten          2007/05/15  Version 1.0.1 - First publication release
* Pradeep Budagutta 2008/04/02  Version 1.1.0 - Multi EEPROM banks included
* Priyabrata Sinha  2011/01/20  Version 2.0.0 - Added dsPIC33E/PIC24E support
* Priyabrata Sinha  2016/12/20  Version 3.0.0 - Added support for new devices
************************************************************************/

// User defined constants
#define DATA_EE_BANKS       2
#define DATA_EE_SIZE        255
#define DATA_EE_TOTAL_SIZE  (DATA_EE_BANKS * DATA_EE_SIZE)
#define NUM_DATA_EE_PAGES   2

// Modify the following constants based on the specific device being used
#if defined(__dsPIC33E__) || defined(__PIC24E__)
//#define	NUMBER_OF_INSTRUCTIONS_IN_PAGE  512 PORCAMADONNA NON � COS� pic24ep512gp202 (v. DEE del 2014, Larry)); anche CAN GU810
//#define	NUMBER_OF_INSTRUCTIONS_IN_ROW   64
#define	NUMBER_OF_INSTRUCTIONS_IN_PAGE  1024 //_FLASH_PAGE         //1024
#define	NUMBER_OF_INSTRUCTIONS_IN_ROW   128         // _FLASH_ROW ??
#elif defined(__PIC24F__)
#define	NUMBER_OF_INSTRUCTIONS_IN_PAGE  1024
#define	NUMBER_OF_INSTRUCTIONS_IN_ROW   128
// sul PIC24FV32KA302, la riga � di 32 e l'erase pu� andare da 32 a 96...
#elif defined(__dsPIC33F__) || defined(__PIC24H__)
#define	NUMBER_OF_INSTRUCTIONS_IN_PAGE  512
#define	NUMBER_OF_INSTRUCTIONS_IN_ROW   64
#endif

// Uncomment the following line if using a device with Flash ECC feature
#define __HAS_ECC	1

// Uncomment the following line if using Auxiliary Flash for EEPROM Emulation
//#define __AUXFLASH	1

#if defined(__dsPIC33E__) || defined(__PIC24E__)

#define ERASE_PAGE          0x4003
#define PROGRAM_ROW         0x4002      // sul GP202 non c'�, ma pare che il codice non la usi
#define PROGRAM_WORD        0x4001

#else

#if defined(__HAS_ECC)
#define ERASE_PAGE          0x4003
#define PROGRAM_ROW         0x4002
#define PROGRAM_WORD        0x4001
#else
#define ERASE_PAGE          0x4042
#define PROGRAM_ROW         0x4001
#define PROGRAM_WORD        0x4003
#endif

#endif

#define ERASE_WRITE_CYCLE_MAX           5
#define NUMBER_OF_ROWS_IN_PAGE          (_FLASH_PAGE / _FLASH_ROW)
#define PAGE_AVAILABLE                  1
#define PAGE_CURRENT                    0
#define PAGE_EXPIRED                    0
#define PAGE_NOT_AVAILABLE              0
#define PAGE_NOT_CURRENT                1
#define PAGE_NOT_EXPIRED                1
#define STATUS_AVAILABLE                18
#define STATUS_CURRENT                  19
#define STATUS_EXPIRED                  20

#define GetaddrNotFound() dataEEFlags.addrNotFound
#define SetaddrNotFound(x) dataEEFlags.addrNotFound = x

#define GetPageCorruptStatus() dataEEFlags.pageCorrupt
#define SetPageCorruptStatus(x) dataEEFlags.pageCorrupt = x

#define GetPageExpiredPage() dataEEFlags.expiredPage
#define SetPageExpiredPage(x) dataEEFlags.expiredPage = x

#define GetPageIllegalAddress() dataEEFlags.IllegalAddress
#define SetPageIllegalAddress(x) dataEEFlags.IllegalAddress = x

#define GetPagePackBeforeInit() dataEEFlags.packBeforeInit
#define SetPagePackBeforeInit(x) dataEEFlags.packBeforeInit = x

#define GetPagePackBeforePageFull() dataEEFlags.packBeforePageFull
#define SetPagePackBeforePageFull(x) dataEEFlags.packBeforePageFull = x

#define GetPagePackSkipped() dataEEFlags.packSkipped
#define SetPagePackSkipped(x) dataEEFlags.packSkipped = x

#define GetPageWriteError() dataEEFlags.writeError
#define SetPageWriteError(x) dataEEFlags.writeError = x

typedef union {
    unsigned char val;
    struct {
        unsigned addrNotFound:1;	    // Return 0xFFFF
        unsigned expiredPage:1;	   	    // Return 0x1
        unsigned packBeforePageFull:1;	// Not a return condition
        unsigned packBeforeInit:1;		// Return 0x3
        unsigned packSkipped:1;		    // Return 0x4
        unsigned IllegalAddress:1;	    // Return 0x5
        unsigned pageCorrupt:1;		    // Return 0x6
        unsigned writeError:1;		    // Return 0x7
    };
	} DATA_EE_FLAGS;

extern DATA_EE_FLAGS dataEEFlags;

extern int  ReadPMHigh(int);
extern int  ReadPMLow(int);
extern void UnlockPM(void);
extern int  WritePMHigh(int, int);
extern int  WritePMLow(int, int);

void            UnlockWrite         (void);
int             GetPageStatus       (unsigned char bank, unsigned volatile char page, unsigned volatile char field);
void            ErasePage           (unsigned char bank, unsigned char page);
char            IncEWCount          (unsigned char *index);
unsigned int    GetNextAvailCount   (unsigned char bank);
int             PackEE              (unsigned char bank);
unsigned char   DataEEInit          (void);
unsigned int    DataEERead          (unsigned int addr);
unsigned char   DataEEWrite         (unsigned int data, unsigned int addr);

