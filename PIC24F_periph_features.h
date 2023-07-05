#ifndef __PIC24F_PERIPH_FEATURES_H
#define __PIC24F_PERIPH_FEATURES_H


/******************************************************************************
 *                  PERIPHERAL SELECT HEADER FILE
 ******************************************************************************
 * FileName:        pic24f_periph_features.h
 * Dependencies:    See include below
 * Processor:       PIC24
 * Compiler:        MPLAB C30
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * GC porting to GA702 - Jul 2017 (XC16)
 *****************************************************************************/

#ifdef __PIC24E__
#include <p24exxxx.h>
#else
#include <p24Fxxxx.h>
#endif

#include <GenericTypeDefs.h>

/* By default, configuration constants are assembled from macros */
/* using the bit-wise AND operator (&). An alternate mode is */
/* available in which constants are assembled using the bit-wise */
/* OR operator (|) to set values and bit-wise AND (&) masks to */
/* clear values. To enable the alternate mode, define the */
/* USE_AND_OR symbol. */
/* */
/* To define this macro as a compiler option: */
/* -DUSE_AND_OR */
/* To define this macro in source code: */
/* #define USE_AND_OR */


#ifdef   __PIC24FJ256GB210__
/*############################################################*/
/*          Configuration for device =  'PIC24FJ256GB210'     */
/*############################################################*/

/* ADC */
#define adc_v3_2

/* CMP */
#define cmp_v2_5

/* CN */
#define cn_v2_11

/* CTMU */
#define ctmu_v1_1

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_2

/* I2C */
#define i2c_v1_3

/* SPI */
#define spi_v1_3

/* OUTCMP */
#define ocmp_v2_1

/* IOPORT */
#define port_v1_4

/* PWRMGNT */
#define pwrmgnt_v1_1

/* TIMERS */
#define tmr_v1_3

/* UART */
#define uart_v1_2

/* PMP */
#define epmp_v2_1

/* pps */
#define pps_v2_5

/* CRC */
#define ecrc_v1_1

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
/*No configuration chosen for this peripheral*/

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24F16KA301__
/*############################################################*/
/*          Configuration for device =  'PIC24F16KA301'       */
/*############################################################*/

/* ADC */
#define adc_v4_1

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_5

/* CTMU */
#define ctmu_v2_1

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_1

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24F32KA301__
/*############################################################*/
/*          Configuration for device =  'PIC24F32KA301'       */
/*############################################################*/

/* ADC */
#define adc_v4_1

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_5

/* CTMU */
#define ctmu_v2_1

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_1

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24F16KA302__
/*############################################################*/
/*          Configuration for device =  'PIC24F16KA302'       */
/*############################################################*/

/* ADC */
#define adc_v4_2

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_6

/* CTMU */
#define ctmu_v2_2

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_1

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24F32KA302__
/*############################################################*/
/*          Configuration for device =  'PIC24F32KA302'       */
/*############################################################*/

/* ADC */
#define adc_v4_2

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_6

/* CTMU */
#define ctmu_v2_2

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_1

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24F16KA304__
/*############################################################*/
/*          Configuration for device =  'PIC24F16KA304'       */
/*############################################################*/

/* ADC */
#define adc_v4_3

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_7

/* CTMU */
#define ctmu_v2_3

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_2

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24F32KA304__
/*############################################################*/
/*          Configuration for device =  'PIC24F32KA304'       */
/*############################################################*/

/* ADC */
#define adc_v4_3

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_7

/* CTMU */
#define ctmu_v2_3

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_2

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24FV16KA301__
/*############################################################*/
/*          Configuration for device =  'PIC24FV16KA301'      */
/*############################################################*/

/* ADC */
#define adc_v4_1

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_5

/* CTMU */
#define ctmu_v2_1

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_1

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24FV32KA301__
/*############################################################*/
/*          Configuration for device =  'PIC24FV32KA301'      */
/*############################################################*/

/* ADC */
#define adc_v4_1

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_5

/* CTMU */
#define ctmu_v2_1

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_1

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24FV16KA302__
/*############################################################*/
/*          Configuration for device =  'PIC24FV16KA302'      */
/*############################################################*/

/* ADC */
#define adc_v4_2

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_6

/* CTMU */
#define ctmu_v2_2

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_1

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24FV32KA302__
/*############################################################*/
/*          Configuration for device =  'PIC24FV32KA302'      */
/*############################################################*/

/* ADC */
#define adc_v4_2

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_6

/* CTMU */
#define ctmu_v2_2

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_1

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24FV16KA304__
/*############################################################*/
/*          Configuration for device =  'PIC24FV16KA304'      */
/*############################################################*/

/* ADC */
#define adc_v4_3

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_7

/* CTMU */
#define ctmu_v2_3

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_2

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24FV32KA304__
/*############################################################*/
/*          Configuration for device =  'PIC24FV32KA304'      */
/*############################################################*/

/* ADC */
#define adc_v4_3

/* CMP */
#define cmp_v2_6

/* CN */
#define cn_v3_7

/* CTMU */
#define ctmu_v2_3

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_3

/* I2C */
#define i2c_v1_4

/* SPI */
#define spi_v1_2

/* OUTCMP */
#define ocmp_v2_4

/* IOPORT */
#define port_v1_2

/* PWRMGNT */
#define pwrmgnt_v2_2

/* TIMERS */
#define tmr_v1_2

/* UART */
#define uart_v1_1

/* PMP */
/*No configuration chosen for this peripheral*/

/* pps */
/*No configuration chosen for this peripheral*/

/* CRC */
#define crc_v1_2

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
#define dpslp_v2_1

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#ifdef   __PIC24FJ256GA702__
/*############################################################*/
/*          Configuration for device =  'PIC24FJ256GA702'     */
/*############################################################*/

/* ADC */
#define adc_v4_1

/* CMP */
#define cmp_v2_5

/* CN */
#define cn_v2_11

/* CTMU */
#define ctmu_v1_1

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_2

/* I2C */
#define i2c_v1_3

/* SPI */
#define spi_v1_3

/* OUTCMP */
#define ocmp_v2_1

/* IOPORT */
#define port_v1_4

/* PWRMGNT */
#define pwrmgnt_v1_1

/* TIMERS */
#define tmr_v1_3

/* UART */
#define uart_v1_2

/* PMP */
#define epmp_v2_1

/* pps */
#define pps_v2_5

/* CRC */
#define ecrc_v1_1

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
/*No configuration chosen for this peripheral*/

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif
#if defined(__PIC24EP512GP202__) || defined(__PIC24EP256GP202__)
/*############################################################*/
/*          Configuration for device =  'PIC24EP256GP202'     */
/*############################################################*/

/* ADC */
#define adc_v6_3

/* CMP */
#define cmp_v2_5

/* CN */
#define cn_v2_11

/* CTMU */
#define ctmu_v1_1

/* INTERRUPT */
#define int_v1_1

/* INCAP */
#define icap_v2_2

/* I2C */
#define i2c_v1_3

/* SPI */
#define spi_v1_3

/* OUTCMP */
#define ocmp_v2_1

/* IOPORT */
#define port_v1_4

/* PWRMGNT */
#define pwrmgnt_v1_1

/* TIMERS */
#define tmr_v1_3

/* UART */
#define uart_v1_2

/* PMP */
#define epmp_v2_1

/* pps */
#define pps_v2_5

/* CRC */
#define ecrc_v1_1

/* RTCC */
#define rtcc_v1_1

/* WDT */
#define wdt_v1_1

/* DPSLP */
/*No configuration chosen for this peripheral*/

/* SRAM */
#define sram_v1_1

/* DMA */
/*No configuration chosen for this peripheral*/

/* PWM */
/*No configuration chosen for this peripheral*/

#endif


/* The following macros can be used to modify the current CPU */
/* IPL. The definition of the macro may vary from device to   */
/* device.                                                    */
/*                                                            */
/* To safely set the CPU IPL, use mSET_CPU_IP(ipl); the       */
/* valid range of ipl is 0-7, it may be any expression.       */
/*                                                            */
/* mSET_CPU_IP(7);                                            */
/*                                                            */
/* To preserve the current IPL and save it use                */
/* mSET_AND_SAVE_CPU_IP(save_to, ipl); the valid range of ipl */
/* is 0-7 and may be any expression, save_to should denote    */
/* some temporary storage.                                    */
/*                                                            */
/* int old_ipl;                                               */
/*                                                            */
/* mSET_AND_SAVE_CPU_IP(old_ipl, 7);                          */
/*                                                            */
/* The IPL can be restored with mRESTORE_CPU_IP(saved_to)     */
/*                                                            */
/* mRESTORE_CPU_IP(old_ipl);                                  */

#define mSET_CPU_IP(ipl)  SET_CPU_IPL(ipl)

#define mSET_AND_SAVE_CPU_IP(save_to, ipl) SET_AND_SAVE_CPU_IPL(save_to, ipl)

#define mRESTORE_CPU_IP(saved_to) mSET_CPU_IP(saved_to)

#endif /*__PIC24F_PERIPH_FEATURES_H*/

