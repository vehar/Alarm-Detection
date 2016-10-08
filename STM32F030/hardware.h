/*
 * hardware.h
 *
 * Created: March-14-16, 4:52:17 PM
 *  Author: K. C. Lee
 * Copyright (c) 2016 by K. C. Lee 
 
 	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.

	If not, see http://www.gnu.org/licenses/gpl-3.0.en.html
 */ 

#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include "main.h"
#include "gpio.h"

#define MIN(X,Y)							(((X)<=(Y))?(X):(Y))

#define CPU_CLOCK							8000000UL
#define UART_BAUD							115200

#define HSE_CLOCK							8000000UL

// SCK = Clk/2 = 4MHz
#define SPI_BR								0

#define LCD_DMA_IRQ_PRIORITY	3

// Enable Debug shell 
//#define DBG_SHELL
#undef DBG_SHELL

//#define ADC_RES_8
#define ADC_RES_12

#define BACKLIGHT							PB1
#define LCD_DC								PA6
#define ADC_BATT_IN						PA1
#define ADC_MIC_IN						PA0

#define ADC_SRC_GROUP					(1<<ADC_MIC_IN)
#define ADC_BATTERY						(1<<ADC_BATT_IN)

#define ADC_AVERAGES					(VOLUME_AVERAGE_PERIOD*ADC_SAMPLE_RATE/ADC_BLOCK_SIZE/1000)
#define ADC_BATT_SCALE_MULT		2505UL
#define ADC_BATT_SCALE_DIV		2509UL

// Max # of audio source
#define ADC_MAX_SRC						1
// L/R channels
#define ADC_CH_PER_SRC				1
#define ADC_MAX_AUD_CH				1
// Max # of channels per conversion
#define ADC_MAX_CH						ADC_MAX_AUD_CH

#include "main.h"
#include "nokia5110.h"
#include "adc.h"
#include "audio.h"
//#include "fifo.h"

void Hardware_Init(void);

enum ADC_Chs
{
	Audio_R1, Audio_L1, Audio_R0, Audio_L0, Buttons
};

#define GPIOA_MODER (PIN_ALT(PA14)|PIN_ALT(PA13)|				/* SWCLK, SWDIO */	\
										 PIN_OUTPUT(PA10)|PIN_OUTPUT(PA9)|	/* CTRL1, CTRL0	*/	\
										 PIN_ALT(PA7)|PIN_OUTPUT(PA6)|			/* MOSI, D/C 		*/	\
										 PIN_ALT(PA5)|PIN_OUTPUT(PA4)|			/* SCK, ???			*/	\
										 PIN_OUTPUT(PA3)|PIN_OUTPUT(PA2)|		/* ???, ???			*/	\
		                 PIN_ANALOG(PA1)|PIN_ANALOG(PA0))		/* ???, Analog in	*/
										 
#define CTRL1				PA3
#define CTRL0				PA2

#define GPIOA_AFR1	0

// low priority
#define SPI_DMA_PRIORITY    0

void SPI_Block_Write(const uint8_t *ptr, uint16_t size);
void SPI_Block_Fill(uint8_t Fill, uint16_t size);

void SPI_ByteWrite(uint8_t byte);

void DMA_memmove(void *Dst, void *Src, uint16_t Size);
void DMA_memset(void *Dst, uint8_t fill, uint16_t Size);
#endif
