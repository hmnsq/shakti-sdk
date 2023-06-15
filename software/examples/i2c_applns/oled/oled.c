/****************************************************************************
 * Project           	        : shakti devt board
 * Name of the file	          : oled.c
 * Brief Description of file  : Implements functions for controlling and displaying 
                                content on an OLED display.
 * Name of Author             : Balaji Sivanallaperumal
 * Email ID                   : ospbalaji@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

*******************************************************************************/
/**
@file   oled.c
@brief  Implements functions for controlling and displaying content on an OLED display.
@detail This file provides functions to initialize the OLED display, write text and graphics,
and control the display's settings. It utilizes an OLED display driver to communicate
with the display hardware and provide a convenient interface for displaying information via I2C.
*/                                                                                                

#include <stdint.h> 
#include <stdbool.h>
#include "i2c.h"
#include "log.h"
#include "uart.h"

#define I2C i2c_instance[1]
#define SSD1306_SLAVE_ADDRESS 0x78
#define DS3231_REG_OFFSET 0
#define DELAY_VALUE 900
#define PRESCALER_COUNT 0x1F
#define SCLK_COUNT 0x91



#define SSD1306_LCDWIDTH            128
#define SSD1306_LCDHEIGHT            64


#define SSD1306_SETCONTRAST          0x81
#define SSD1306_DISPLAYALLON_RESUME  0xA4
#define SSD1306_DISPLAYALLON         0xA5
#define SSD1306_NORMALDISPLAY        0xA6
#define SSD1306_INVERTDISPLAY_       0xA7
#define SSD1306_DISPLAYOFF           0xAE
#define SSD1306_DISPLAYON            0xAF
#define SSD1306_SETDISPLAYOFFSET     0xD3
#define SSD1306_SETCOMPINS           0xDA
#define SSD1306_SETVCOMDETECT        0xDB
#define SSD1306_SETDISPLAYCLOCKDIV   0xD5
#define SSD1306_SETPRECHARGE         0xD9
#define SSD1306_SETMULTIPLEX         0xA8
#define SSD1306_SETLOWCOLUMN         0x00
#define SSD1306_SETHIGHCOLUMN        0x10
#define SSD1306_SETSTARTLINE         0x40
#define SSD1306_MEMORYMODE           0x20
#define SSD1306_COLUMNADDR           0x21
#define SSD1306_PAGEADDR             0x22
#define SSD1306_COMSCANINC           0xC0
#define SSD1306_COMSCANDEC           0xC8
#define SSD1306_SEGREMAP             0xA0
#define SSD1306_CHARGEPUMP           0x8D
#define SSD1306_EXTERNALVCC          0x01
#define SSD1306_SWITCHCAPVCC         0x02



// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL                      0x2F
#define SSD1306_DEACTIVATE_SCROLL                    0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A

#define BLACK   0
#define WHITE   1
#define INVERSE 2


unsigned int vccstate = SSD1306_SWITCHCAPVCC;
unsigned int i2caddr = SSD1306_SLAVE_ADDRESS;
unsigned int x_pos, y_pos, text_size;
unsigned int wrap = 1;




#define ssd1306_swap(a, b) { unsigned int t = a; a = b; b = t; }

	//unsigned long delay = 100;
	unsigned int write_buf[7] = {0x00};


unsigned int _vccstate, rotation = 0;         ///< Display rotation (0 thru 3)
#if !defined SSD1306_SPI_MODE
unsigned int _i2caddr;
#endif
unsigned int _width, _height;


//*************************** User Functions ***************************//
unsigned int c;
void SSD1306_begin(unsigned int vccstate, unsigned int i2caddr);  // I2C mode


void drawPixel(unsigned int x, unsigned int y, unsigned int color);
void drawHLine(unsigned int x, unsigned int y, unsigned int w, unsigned int color);
void drawVLine(unsigned int x, unsigned int y, unsigned int h, unsigned int color);
void fillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color);
void FillScreen(unsigned int color);
void DrawCircle(unsigned int x0, unsigned int y0, unsigned int r);
void DrawCircleHelper(unsigned int x0, unsigned int y0, unsigned int r, unsigned int cornername);
void FillCircle(unsigned int x0, unsigned int y0, unsigned int r, unsigned int color);
void FillCircleHelper(unsigned int x0, unsigned int y0, unsigned int r, unsigned int cornername, unsigned int delta, unsigned int color);

void DrawRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
void DrawRoundRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int r);
void FillRoundRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int r, unsigned int color);
void DrawTriangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void FillTriangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color);

void DrawChar(unsigned int x, unsigned int y, unsigned int c, unsigned int size);
void DrawText(unsigned int x, unsigned int y, unsigned char *_text, unsigned int size);
void TextSize(unsigned int t_size);
void GotoXY(unsigned int x, unsigned int y);
void Print(unsigned int c);
void invertDisplay(bool i);

void setRotation(unsigned int m);
void fillScreen(void);
void display_clear(void);
void display_dim(bool dim);
void display(void);
void invertDisplay(bool inv);

void display_startScrollRight(unsigned int start, unsigned int stop);
void display_startScrollLeft(unsigned int start, unsigned int stop);
void display_startScrollDiagRight(unsigned int start, unsigned int stop);
void display_startScrollDiagLeft(unsigned int start, unsigned int stop);
void display_stopScroll(void);


void DrawLine(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color);
void DrawFastHLine(unsigned int x, unsigned int y, unsigned int w, unsigned int color);
void DrawFastVLine(unsigned int x, unsigned int y, unsigned int h, unsigned int color);
void drawFastHLineInternal(unsigned int x, unsigned int y, unsigned int w, unsigned int color);
void drawFastVLineInternal(unsigned int x, unsigned int __y, unsigned int __h, unsigned int color);



static unsigned char ssd1306_buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0x80, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0xFF,
0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x0F,
0x87, 0xC7, 0xF7, 0xFF, 0xFF, 0x1F, 0x1F, 0x3D, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0x7C, 0x7D, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x00, 0x30, 0x30, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xC0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xC0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x1F,
0x0F, 0x07, 0x1F, 0x7F, 0xFF, 0xFF, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8, 0xE0,
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00,
0x00, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x00, 0x00, 0xF0, 0xF8, 0x1C, 0x0E,
0x06, 0x06, 0x06, 0x0C, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFC,
0xFE, 0xFC, 0x00, 0x18, 0x3C, 0x7E, 0x66, 0xE6, 0xCE, 0x84, 0x00, 0x00, 0x06, 0xFF, 0xFF, 0x06,
0x06, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x06, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0xC0, 0xF8,
0xFC, 0x4E, 0x46, 0x46, 0x46, 0x4E, 0x7C, 0x78, 0x40, 0x18, 0x3C, 0x76, 0xE6, 0xCE, 0xCC, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00,
0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x03, 0x07, 0x0E, 0x0C,
0x18, 0x18, 0x0C, 0x06, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x01, 0x0F, 0x0E, 0x0C, 0x18, 0x0C, 0x0F,
0x07, 0x01, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00,
0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x07,
0x07, 0x0C, 0x0C, 0x18, 0x1C, 0x0C, 0x06, 0x06, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



const char Font[] = {
0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x5F, 0x00, 0x00,
0x00, 0x07, 0x00, 0x07, 0x00,
0x14, 0x7F, 0x14, 0x7F, 0x14,
0x24, 0x2A, 0x7F, 0x2A, 0x12,
0x23, 0x13, 0x08, 0x64, 0x62,
0x36, 0x49, 0x56, 0x20, 0x50,
0x00, 0x08, 0x07, 0x03, 0x00,
0x00, 0x1C, 0x22, 0x41, 0x00,
0x00, 0x41, 0x22, 0x1C, 0x00,
0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
0x08, 0x08, 0x3E, 0x08, 0x08,
0x00, 0x80, 0x70, 0x30, 0x00,
0x08, 0x08, 0x08, 0x08, 0x08,
0x00, 0x00, 0x60, 0x60, 0x00,
0x20, 0x10, 0x08, 0x04, 0x02,
0x3E, 0x51, 0x49, 0x45, 0x3E,
0x00, 0x42, 0x7F, 0x40, 0x00,
0x72, 0x49, 0x49, 0x49, 0x46,
0x21, 0x41, 0x49, 0x4D, 0x33,
0x18, 0x14, 0x12, 0x7F, 0x10,
0x27, 0x45, 0x45, 0x45, 0x39,
0x3C, 0x4A, 0x49, 0x49, 0x31,
0x41, 0x21, 0x11, 0x09, 0x07,
0x36, 0x49, 0x49, 0x49, 0x36,
0x46, 0x49, 0x49, 0x29, 0x1E,
0x00, 0x00, 0x14, 0x00, 0x00,
0x00, 0x40, 0x34, 0x00, 0x00,
0x00, 0x08, 0x14, 0x22, 0x41,
0x14, 0x14, 0x14, 0x14, 0x14,
0x00, 0x41, 0x22, 0x14, 0x08,
0x02, 0x01, 0x59, 0x09, 0x06,
0x3E, 0x41, 0x5D, 0x59, 0x4E,
0x7C, 0x12, 0x11, 0x12, 0x7C,
0x7F, 0x49, 0x49, 0x49, 0x36,
0x3E, 0x41, 0x41, 0x41, 0x22,
0x7F, 0x41, 0x41, 0x41, 0x3E,
0x7F, 0x49, 0x49, 0x49, 0x41,
0x7F, 0x09, 0x09, 0x09, 0x01,
0x3E, 0x41, 0x41, 0x51, 0x73,
0x7F, 0x08, 0x08, 0x08, 0x7F,
0x00, 0x41, 0x7F, 0x41, 0x00,
0x20, 0x40, 0x41, 0x3F, 0x01,
0x7F, 0x08, 0x14, 0x22, 0x41,
0x7F, 0x40, 0x40, 0x40, 0x40,
0x7F, 0x02, 0x1C, 0x02, 0x7F,
0x7F, 0x04, 0x08, 0x10, 0x7F,
0x3E, 0x41, 0x41, 0x41, 0x3E,
0x7F, 0x09, 0x09, 0x09, 0x06,
0x3E, 0x41, 0x51, 0x21, 0x5E,
0x7F, 0x09, 0x19, 0x29, 0x46
};
const char Font2[] = {
0x26, 0x49, 0x49, 0x49, 0x32,
0x03, 0x01, 0x7F, 0x01, 0x03,
0x3F, 0x40, 0x40, 0x40, 0x3F,
0x1F, 0x20, 0x40, 0x20, 0x1F,
0x3F, 0x40, 0x38, 0x40, 0x3F,
0x63, 0x14, 0x08, 0x14, 0x63,
0x03, 0x04, 0x78, 0x04, 0x03,
0x61, 0x59, 0x49, 0x4D, 0x43,
0x00, 0x7F, 0x41, 0x41, 0x41,
0x02, 0x04, 0x08, 0x10, 0x20,
0x00, 0x41, 0x41, 0x41, 0x7F,
0x04, 0x02, 0x01, 0x02, 0x04,
0x40, 0x40, 0x40, 0x40, 0x40,
0x00, 0x03, 0x07, 0x08, 0x00,
0x20, 0x54, 0x54, 0x78, 0x40,
0x7F, 0x28, 0x44, 0x44, 0x38,
0x38, 0x44, 0x44, 0x44, 0x28,
0x38, 0x44, 0x44, 0x28, 0x7F,
0x38, 0x54, 0x54, 0x54, 0x18,
0x00, 0x08, 0x7E, 0x09, 0x02,
0x18, 0xA4, 0xA4, 0x9C, 0x78,
0x7F, 0x08, 0x04, 0x04, 0x78,
0x00, 0x44, 0x7D, 0x40, 0x00,
0x20, 0x40, 0x40, 0x3D, 0x00,
0x7F, 0x10, 0x28, 0x44, 0x00,
0x00, 0x41, 0x7F, 0x40, 0x00,
0x7C, 0x04, 0x78, 0x04, 0x78,
0x7C, 0x08, 0x04, 0x04, 0x78,
0x38, 0x44, 0x44, 0x44, 0x38,
0xFC, 0x18, 0x24, 0x24, 0x18,
0x18, 0x24, 0x24, 0x18, 0xFC,
0x7C, 0x08, 0x04, 0x04, 0x08,
0x48, 0x54, 0x54, 0x54, 0x24,
0x04, 0x04, 0x3F, 0x44, 0x24,
0x3C, 0x40, 0x40, 0x20, 0x7C,
0x1C, 0x20, 0x40, 0x20, 0x1C,
0x3C, 0x40, 0x30, 0x40, 0x3C,
0x44, 0x28, 0x10, 0x28, 0x44,
0x4C, 0x90, 0x90, 0x90, 0x7C,
0x44, 0x64, 0x54, 0x4C, 0x44,
0x00, 0x08, 0x36, 0x41, 0x00,
0x00, 0x00, 0x77, 0x00, 0x00,
0x00, 0x41, 0x36, 0x08, 0x00,
0x02, 0x01, 0x02, 0x04, 0x02
};


void ssd1306_command(unsigned int c)
{
	write_buf[0] = c;
    write_ssd1306_register(I2C, 0x00, &write_buf[0],10);
	printf("\n Write complete");
 
}

int write_ssd1306_register(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *write_value, unsigned long delay)
{
	int i = 0, j = 0,  k = 0, status=0;
	unsigned int temp = 0;
		i2c_send_slave_address(i2c_instance, SSD1306_SLAVE_ADDRESS, I2C_WRITE, delay);
		i2c_write_data(i2c_instance, reg_offset, delay);
		i2c_write_data(i2c_instance,  ( *write_value++  & 0xff) /*LM75_TEMP_REG_OFFSET */, delay);
		i2c_instance->control = I2C_STOP;
}



int write_ssd1306_registers(i2c_struct *i2c_instance, unsigned int reg_offset, unsigned int *write_value, unsigned long delay)
{


   unsigned int count = (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8);
  unsigned char *ptr = ssd1306_buffer;

    i2c_send_slave_address(i2c_instance, SSD1306_SLAVE_ADDRESS, I2C_WRITE, delay);
    i2c_write_data(i2c_instance,0x40, delay);
    unsigned int bytesOut = 1;
    while (count--) {
      if (bytesOut >= 32) {
        i2c_instance->control = I2C_STOP;
        i2c_send_slave_address(i2c_instance, SSD1306_SLAVE_ADDRESS, I2C_WRITE, delay);
        i2c_write_data(i2c_instance,0x40, delay);
        i2c_write_data(i2c_instance,*ptr++, delay);
        bytesOut = 1;
      }
      i2c_write_data(i2c_instance,*ptr++, delay);
      bytesOut++;
    }
    i2c_instance->control = I2C_STOP;
  
}





// ||||||||||||||||||||||||||||||| USER DEFINED FUNCTION ||||||||||||||||||||||||||||||||||||
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


void DrawChar(unsigned int x, unsigned int y, unsigned int c, unsigned int size)
{
  GotoXY(x, y);
  TextSize(size);
  Print(c);
}

void DrawText(unsigned int x, unsigned int y, unsigned char *_text, unsigned int size)
{
  GotoXY(x, y);
  TextSize(size);
  while(*_text != '\0')
    Print(*_text++);

}

// move cursor to position (x, y)
void GotoXY(unsigned int x, unsigned int y)
{
  if((x >= SSD1306_LCDWIDTH) || (y >= SSD1306_LCDHEIGHT))
  x_pos = x;
  y_pos = y;
}

// set text size
void TextSize(unsigned int t_size)
{
  if(t_size < 1)
    t_size = 1;
  text_size = t_size;
}

void Print(unsigned int c)
{
  unsigned int _color;
  unsigned int i, j, line;
  
  if (c == ' ' && x_pos == 0 && wrap)
    return;
  if(c == '\a') {
    x_pos = y_pos = 0;
    return;
  }
  if( (c == '\b') && (x_pos >= text_size * 6) ) {
    x_pos -= text_size * 6;
    return;
  }
  if(c == '\r') {
    x_pos = 0;
    return;
  }
  if(c == '\n') {
    y_pos += text_size * 8;
    if((y_pos + text_size * 7) > SSD1306_LCDHEIGHT)
      y_pos = 0;
    return;
  }

  if((c < ' ') || (c > '~'))
    c = '?';
  
  for(i = 0; i < 5; i++ ) {
    if(c < 'S')
      line = Font[(c - ' ') * 5 + i];
    else
      line = Font2[(c - 'S') * 5 + i];
    
    for(j = 0; j < 7; j++, line >>= 1) {
      if(line & 0x01)
        _color = WHITE;
      else
        _color = BLACK;
      if(text_size == 1) DrawPixel(x_pos + i, y_pos + j, _color);
      else               fillRect(x_pos + (i * text_size), y_pos + (j * text_size), text_size, text_size, _color);
    }
  }

  fillRect(x_pos + (5 * text_size), y_pos, text_size, 7 * text_size, BLACK);
  
  x_pos += text_size * 6;

  if( x_pos > (SSD1306_LCDWIDTH + text_size * 6) )
    x_pos = SSD1306_LCDWIDTH;

  if (wrap && (x_pos + (text_size * 5)) > SSD1306_LCDWIDTH)
  {
    x_pos = 0;
    y_pos += text_size * 8;
    if((y_pos + text_size * 7) > SSD1306_LCDHEIGHT)
      y_pos = 0;
  }
}


void DrawFastHLine(unsigned int x, unsigned int y, unsigned int w, unsigned int color)
{
   DrawLine(x, y, x + w - 1, y, color);
}

void DrawFastVLine(unsigned int x, unsigned int y, unsigned int h, unsigned int color)
{
  DrawLine(x, y, x, y + h - 1, color);
}



void DrawCircle(unsigned int x0, unsigned int y0, unsigned int r)
{
  unsigned int f = 1 - r;
  unsigned int ddF_x = 1;
  unsigned int ddF_y = -2 * r;
  unsigned int x = 0;
  unsigned int y = r;

  DrawPixel(x0  , y0 + r,WHITE);
  DrawPixel(x0  , y0 - r, WHITE);
  DrawPixel(x0 + r, y0, WHITE);
  DrawPixel(x0 - r, y0,WHITE);

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    DrawPixel(x0 + x, y0 + y,WHITE);
    DrawPixel(x0 - x, y0 + y,WHITE);
    DrawPixel(x0 + x, y0 - y,WHITE);
    DrawPixel(x0 - x, y0 - y,WHITE);
    DrawPixel(x0 + y, y0 + x,WHITE);
    DrawPixel(x0 - y, y0 + x,WHITE);
    DrawPixel(x0 + y, y0 - x,WHITE);
    DrawPixel(x0 - y, y0 - x,WHITE);
  }

}

void DrawCircleHelper(unsigned int x0, unsigned int y0, unsigned int r, unsigned int cornername)
{
  unsigned int f     = 1 - r;
  unsigned int ddF_x = 1;
  unsigned int ddF_y = -2 * r;
  unsigned int x     = 0;
  unsigned int y     = r;

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      DrawPixel(x0 + x, y0 + y,WHITE);
      DrawPixel(x0 + y, y0 + x,WHITE);
    }
    if (cornername & 0x2) {
      DrawPixel(x0 + x, y0 - y,WHITE);
      DrawPixel(x0 + y, y0 - x,WHITE);
    }
    if (cornername & 0x8) {
      DrawPixel(x0 - y, y0 + x,WHITE);
      DrawPixel(x0 - x, y0 + y,WHITE);
    }
    if (cornername & 0x1) {
      DrawPixel(x0 - y, y0 - x,WHITE);
      DrawPixel(x0 - x, y0 - y,WHITE);
    }
  }

}

void FillCircle(unsigned int x0, unsigned int y0, unsigned int r, unsigned int color)
{
  DrawFastVLine(x0, y0 - r, 2 * r + 1, color);
  FillCircleHelper(x0, y0, r, 3, 0, color);
}

// Used to do circles and roundrects
void FillCircleHelper(unsigned int x0, unsigned int y0, unsigned int r, unsigned int cornername, unsigned int delta, unsigned int color) {
  unsigned int f     = 1 - r;
  unsigned int ddF_x = 1;
  unsigned int ddF_y = -2 * r;
  unsigned int x     = 0;
  unsigned int y     = r;

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x01) {
      DrawFastVLine(x0 + x, y0 - y, 2 * y + 1 + delta, color);
      DrawFastVLine(x0 + y, y0 - x, 2 * x + 1 + delta, color);
    }
    if (cornername & 0x02) {
      DrawFastVLine(x0 - x, y0 - y, 2 * y + 1 + delta, color);
      DrawFastVLine(x0 - y, y0 - x, 2 * x + 1 + delta, color);
    }
  }

}

// Draw a rectangle
void DrawRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
  DrawFastHLine(x, y, w, WHITE);
  DrawFastHLine(x, y + h - 1, w,WHITE);
  DrawFastVLine(x, y, h, WHITE);
  DrawFastVLine(x + w - 1, y, h, WHITE);
}

// Draw a rounded rectangle
void DrawRoundRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int r)
{
  // smarter version
  DrawFastHLine(x + r, y, w - 2 * r, WHITE); // Top
  DrawFastHLine(x + r, y + h - 1, w - 2 * r, WHITE); // Bottom
  DrawFastVLine(x, y + r, h - 2 * r, WHITE); // Left
  DrawFastVLine(x + w - 1, y + r, h - 2 * r, WHITE); // Right
  // draw four corners
  DrawCircleHelper(x + r, y + r, r, 1);
  DrawCircleHelper(x + w - r - 1, y + r, r, 2);
  DrawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4);
  DrawCircleHelper(x + r, y + h - r - 1, r, 8);
}

// Fill a rounded rectangle
void FillRoundRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int r, unsigned int color)
{
  // smarter version
  fillRect(x + r, y, w - 2 * r, h,WHITE);
  // draw four corners
  FillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
  FillCircleHelper(x + r        , y + r, r, 2, h - 2 * r - 1, color);
}

// Draw a triangle
void DrawTriangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
  DrawLine(x0, y0, x1, y1,WHITE);
  DrawLine(x1, y1, x2, y2,WHITE);
  DrawLine(x2, y2, x0, y0,WHITE);
}

// Fill a triangle
void FillTriangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color)
{
  unsigned int a, b, y, last;
  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    ssd1306_swap(y0, y1); ssd1306_swap(x0, x1);
  }
  if (y1 > y2) {
    ssd1306_swap(y2, y1); ssd1306_swap(x2, x1);
  }
  if (y0 > y1) {
    ssd1306_swap(y0, y1); ssd1306_swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    DrawFastHLine(a, y0, b - a + 1, color);
    return;
  }

  unsigned int
  dx01 = x1 - x0,
  dy01 = y1 - y0,
  dx02 = x2 - x0,
  dy02 = y2 - y0,
  dx12 = x2 - x1,
  dy12 = y2 - y1;
  unsigned int  sa   = 0, sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1 - 1; // Skip it

  for(y = y0; y <= last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) ssd1306_swap(a, b);
    DrawFastHLine(a, y, b - a + 1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y <= y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) ssd1306_swap(a, b);
    DrawFastHLine(a, y, b - a + 1, color);
  }
}



// startscrollright
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display_scrollright(0x00, 0x0F)
void display_startScrollRight(unsigned int start, unsigned int stop)
{
  ssd1306_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
  ssd1306_command(0X00);
  ssd1306_command(start);
  ssd1306_command(0X00);
  ssd1306_command(stop);
  ssd1306_command(0X00);
  ssd1306_command(0XFF);
  ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

// startscrollleft
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display_scrollright(0x00, 0x0F)
void display_startScrollLeft(unsigned int start, unsigned int stop)
{
  ssd1306_command(SSD1306_LEFT_HORIZONTAL_SCROLL);
  ssd1306_command(0X00);
  ssd1306_command(start);
  ssd1306_command(0X00);
  ssd1306_command(stop);
  ssd1306_command(0X00);
  ssd1306_command(0XFF);
  ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

// startscrolldiagright
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display_scrollright(0x00, 0x0F)
void display_startScrollDiagRight(unsigned int start, unsigned int stop)
{
  ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
  ssd1306_command(0X00);
  ssd1306_command(SSD1306_LCDHEIGHT);
  ssd1306_command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
  ssd1306_command(0X00);
  ssd1306_command(start);
  ssd1306_command(0X00);
  ssd1306_command(stop);
  ssd1306_command(0X01);
  ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

// startscrolldiagleft
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display_scrollright(0x00, 0x0F)
void display_startScrollDiagLeft(unsigned int start, unsigned int stop)
{
  ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
  ssd1306_command(0X00);
  ssd1306_command(SSD1306_LCDHEIGHT);
  ssd1306_command(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
  ssd1306_command(0X00);
  ssd1306_command(start);
  ssd1306_command(0X00);
  ssd1306_command(stop);
  ssd1306_command(0X01);
  ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

void display_stopScroll(void)
{
  ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
}

// Dim the display
// dim = true: display is dimmed
// dim = BLACK: display is normal
void display_dim(bool dim)
{
  unsigned int contrast;
  if (dim)
    contrast = 0; // Dimmed display
  else
  {
    if (_vccstate == SSD1306_EXTERNALVCC)
      contrast = 0x9F;
    else
      contrast = 0xCF;
  }
  // the range of contrast to too small to be really useful
  // it is useful to dim the display
  ssd1306_command(SSD1306_SETCONTRAST);
  ssd1306_command(contrast);
}


void display(void)
{
  unsigned int i;
  ssd1306_command(SSD1306_COLUMNADDR);
  ssd1306_command(0);                    // Column start address (0 = reset)
  ssd1306_command(SSD1306_LCDWIDTH - 1); // Column end address (127 = reset)

  ssd1306_command(SSD1306_PAGEADDR);
  ssd1306_command(0); // Page start address (0 = reset)
#if SSD1306_LCDHEIGHT == 64
  ssd1306_command(7); // Page end address
#endif
#if SSD1306_LCDHEIGHT == 32
  ssd1306_command(3); // Page end address
#endif
#if SSD1306_LCDHEIGHT == 16
  ssd1306_command(1); // Page end address
#endif

  write_ssd1306_registers(I2C, 0x40, 0x00, 10);
}

void display_clear(void)
{
  unsigned int i;
  for (i = 0; i < (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT); i++)
    ssd1306_buffer[i] = 0;
}

void fillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color)
{
  unsigned int i;
  for (i = x; i < x + w; i++)
    drawVLine(i, y, h, color);
}


void fillScreen(void)
{
  fillRect(0, 0, SSD1306_LCDWIDTH, SSD1306_LCDHEIGHT, 1);
}

//invert the display
void invertDisplay(bool i)
{
  if (i)
    ssd1306_command(SSD1306_INVERTDISPLAY_);
  else
    ssd1306_command(SSD1306_NORMALDISPLAY);
}

void setRotation(unsigned int m)
{
  rotation = (m & 3);
  switch (rotation)
  {
  case 0:
  case 2:
    _width = SSD1306_LCDWIDTH;
    _height = SSD1306_LCDHEIGHT;
    break;
  case 1:
  case 3:
    _width = SSD1306_LCDHEIGHT;
    _height = SSD1306_LCDWIDTH;
    break;
  }
}


void DrawPixel(unsigned int x, unsigned int y, unsigned int color)
{
  if ((x >= 0) && (x < SSD1306_LCDWIDTH) && (y >= 0) && (y < SSD1306_LCDHEIGHT))
  {
  switch (color) {
    case 1:
      ssd1306_buffer[x + (y / 8) * SSD1306_LCDWIDTH] |= (1 << (y & 7));
      break;
    case 2:
      ssd1306_buffer[x + (y / 8) * SSD1306_LCDWIDTH] &= ~(1 << (y & 7));
      break;
    case 3:
      ssd1306_buffer[x + (y / 8) * SSD1306_LCDWIDTH] ^= (1 << (y & 7));
      break;
    }
  }
}

void DrawLine(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color)
{
  unsigned int steep;
  unsigned int ystep;
  unsigned int dx, dy;
  unsigned int err;
  steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    ssd1306_swap(x0, y0);
    ssd1306_swap(x1, y1);
  }
  if (x0 > x1) {
    ssd1306_swap(x0, x1);
    ssd1306_swap(y0, y1);
  }
  dx = x1 - x0;
  dy = abs(y1 - y0);

  err = dx / 2;
  if (y0 < y1)
    ystep = 1;
  else
    ystep = -1;

  for (; x0 <= x1; x0++) {
    if (steep) {
      if(color) DrawPixel(y0, x0,WHITE);
      else      DrawPixel(y0, x0,BLACK);
    }
    else {
      if(color) DrawPixel(x0, y0,WHITE);
      else      DrawPixel(x0, y0,BLACK);
    }
    err -= dy;
    if (err < 0) {
      y0  += ystep;
      err += dx;
    }
  }
}


void drawHLine(unsigned int x, unsigned int y, unsigned int w, unsigned int color)
{
  bool bSwap = false;
  switch (rotation)
  {
  case 0:
    // 0 degree rotation, do nothing
    break;
  case 1:
    // 90 degree rotation, swap x & y for rotation, then invert x
    bSwap = true;
    ssd1306_swap(x, y);
    x = SSD1306_LCDWIDTH - x - 1;
    break;
  case 2:
    // 180 degree rotation, invert x and y - then shift y around for _height.
    x = SSD1306_LCDWIDTH - x - 1;
    y = SSD1306_LCDHEIGHT - y - 1;
    x -= (w - 1);
    break;
  case 3:
    // 270 degree rotation, swap x & y for rotation, then invert y  and adjust y for w (not to become h)
    bSwap = true;
    ssd1306_swap(x, y);
    y = SSD1306_LCDHEIGHT - y - 1;
    y = y - (w - 1);
    break;
  }

  if (bSwap)
  {
    drawFastVLineInternal(x, y, w, color);
  }
  else
  {
    drawFastHLineInternal(x, y, w, color);
  }
}

void drawFastHLineInternal(unsigned int x, unsigned int y, unsigned int w, unsigned int color)
{
  register unsigned int *pBuf, mask;
  // Do bounds/limit checks
  if (y >= SSD1306_LCDHEIGHT)
  {
    return;
  }

  // make sure we don't go off the edge of the display
  if ((x + w) > SSD1306_LCDWIDTH)
  {
    w = (SSD1306_LCDWIDTH - x);
  }

  // set up the pointer for  movement through the buffer
  pBuf = ssd1306_buffer;
  // adjust the buffer pointer for the current row
  pBuf += ((unsigned int )(y / 8) * SSD1306_LCDWIDTH);
  // and offset x columns in
  pBuf += x;

  mask = 1 << (y & 7);
  unsigned int s = color;
  switch (s)
  {
  case WHITE:
    while (w--)
    {
      *pBuf++ |= mask;
    };
    break;
  case BLACK:
    mask = ~mask;
    while (w--)
    {
      *pBuf++ &= mask;
    };
    break;
  case INVERSE:
    while (w--)
    {
      *pBuf++ ^= mask;
    };
    break;
  }
}

void drawVLine(unsigned int x, unsigned int y, unsigned int h, unsigned int color)
{
  bool bSwap = false;
  switch (rotation)
  {
  case 0:
    break;
  case 1:
    // 90 degree rotation, swap x & y for rotation, then invert x and adjust x for h (now to become w)
    bSwap = true;
    ssd1306_swap(x, y);
    x = SSD1306_LCDWIDTH - x - 1;
    x -= (h - 1);
    break;
  case 2:
    // 180 degree rotation, invert x and y - then shift y around for _height.
    x = SSD1306_LCDWIDTH - x - 1;
    y = SSD1306_LCDHEIGHT - y - 1;
    y -= (h - 1);
    break;
  case 3:
    // 270 degree rotation, swap x & y for rotation, then invert y
    bSwap = true;
    ssd1306_swap(x, y);
    y = SSD1306_LCDHEIGHT - y - 1;
    break;
  }

  if (bSwap)
  {
    drawFastHLineInternal(x, y, h, color);
  }
  else
  {
    drawFastVLineInternal(x, y, h, color);
  }
}



void drawFastVLineInternal(unsigned int x, unsigned int __y, unsigned int __h, unsigned int color)
{

  register unsigned int *pBuf, mod, y, h, mask;
  static unsigned int premask[8] = {0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE};
  // do nothing if we're off the left or right side of the screen
  if (x >= SSD1306_LCDWIDTH)
  {
    return;
  }

  // make sure we don't go past the _height of the display
  if ((__y + __h) > SSD1306_LCDHEIGHT)
  {
    __h = (SSD1306_LCDHEIGHT - __y);
  }

  // this display doesn't need ints for coordinates, use local byte registers for faster juggling
  y = __y;
  h = __h;

  // set up the pointer for fast movement through the buffer
  pBuf = ssd1306_buffer;
  // adjust the buffer pointer for the current row
  pBuf += ((unsigned int )(y / 8) * SSD1306_LCDWIDTH);
  // and offset x columns in
  pBuf += x;

  // do the first partial byte, if necessary - this requires some masking
  mod = (y & 7);
  if (mod)
  {
    // mask off the high n bits we want to set
    mod = 8 - mod;

    mask = premask[mod];

    // adjust the mask if we're not going to reach the end of this byte
    if (h < mod)
    {
      mask &= (0XFF >> (mod - h));
    }

    switch (color)
    {
    case WHITE:
      *pBuf |= mask;
      break;
    case BLACK:
      *pBuf &= ~mask;
      break;
    case INVERSE:
      *pBuf ^= mask;
      break;
    }

    // fast exit if we're done here!
    if (h < mod)
    {
      return;
    }

    h -= mod;

    pBuf += SSD1306_LCDWIDTH;
  }

  // write solid bytes while we can - effectively doing 8 rows at a time
  if (h >= 8)
  {
    if (color == INVERSE)
    { // separate copy of the code so we don't impact performance of the black/white write version with an extra comparison per loop
      do
      {
        *pBuf = ~(*pBuf);

        // adjust the buffer forward 8 rows worth of data
        pBuf += SSD1306_LCDWIDTH;

        // adjust h & y (there's got to be a faster way for me to do this, but this should still help a fair bit for now)
        h -= 8;
      } while (h >= 8);
    }
    else
    {
      // store a local value to work with
      register unsigned int val = (color == WHITE) ? 255 : 0;

      do
      {
        // write our value in
        *pBuf = val;

        // adjust the buffer forward 8 rows worth of data
        pBuf += SSD1306_LCDWIDTH;

        // adjust h & y (there's got to be a faster way for me to do this, but this should still help a fair bit for now)
        h -= 8;
      } while (h >= 8);
    }
  }

  // now do the final partial byte, if necessary
  if (h)
  {
    // this time we want to mask the low bits of the byte, vs the high bits we did above
    // register unsigned int mask = (1 << mod) - 1;
    // note - lookup table results in a nearly 10% performance improvement in fill* functions
    static unsigned int postmask[8] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F};
    register unsigned int mask;
    mod = h & 7;
    mask = postmask[mod];
    switch (color)
    {
    case WHITE:
      *pBuf |= mask;
      break;
    case BLACK:
      *pBuf &= ~mask;
      break;
    case INVERSE:
      *pBuf ^= mask;
      break;
    }
  }
}


void drawBitmapV2(unsigned int x, unsigned int y, const unsigned int *bitmap, unsigned int w, unsigned int h) {

    uint8_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t _byte = 0;
    uint8_t i, j;

    for(j = 0; j < h; j++, y++) {
        for( i = 0; i < w; i++ ) {
            if(i & 7) _byte <<= 1;
            else      _byte   = &bitmap[j * byteWidth + i / 8];
            if(_byte & 0x80)
              DrawPixel(x+i, y, WHITE);
        }
    }
}

void printBitmap(unsigned int* bitmap, unsigned int width, unsigned int height) {
  
  unsigned int x, y;
  unsigned int byteIndex = 0;
  unsigned int bitIndex = 7;

  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      unsigned char pixel = (bitmap[byteIndex] >> bitIndex) & 1;
      
      DrawPixel(x, y, pixel);
      
      bitIndex--;
      if (bitIndex < 0) {
        bitIndex = 7;
        byteIndex++;
      }
    }
  }
}



//  |||||||||||||||||||||||||||||||||||||||      END       ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void testdrawcircle(void) {
  for (unsigned int i = 0; i < SSD1306_LCDHEIGHT; i += 2) {
    DrawCircle(SSD1306_LCDWIDTH/2, SSD1306_LCDHEIGHT/2, i);
    display();
    delay(100);
  }
}





void main()
{
		int timeout;
		unsigned int tempReadValue = 0;
	printf("\nHello Welcome to Shakti");

	i2c_init();

	if(config_i2c(I2C, PRESCALER_COUNT, SCLK_COUNT))
	{
		log_error("\tSomething Wrong In Initialization\n");
		return -1;
	}
	else
		log_info("\tIntilization Happened Fine\n");

ssd1306_command(SSD1306_SWITCHCAPVCC);

  _i2caddr = i2caddr;
  _vccstate = vccstate;
  delay(100);

  // Init sequence
  ssd1306_command(SSD1306_DISPLAYOFF);         // 0xAE
  ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV); // 0xD5
  ssd1306_command(0x80);                       // the suggested ratio 0x80

  ssd1306_command(SSD1306_SETMULTIPLEX); // 0xA8
  ssd1306_command(SSD1306_LCDHEIGHT - 1);

  ssd1306_command(SSD1306_SETDISPLAYOFFSET);   // 0xD3
  ssd1306_command(0x0);                        // no offset
  ssd1306_command(SSD1306_SETSTARTLINE | 0x0); // line #0
  ssd1306_command(SSD1306_CHARGEPUMP);         // 0x8D
  if (vccstate == SSD1306_EXTERNALVCC)
  {
    ssd1306_command(0x10);
  }
  else
  {
    ssd1306_command(0x14);
  }
  ssd1306_command(SSD1306_MEMORYMODE); // 0x20
  ssd1306_command(0x00);               // 0x0 act like ks0108
  ssd1306_command(SSD1306_SEGREMAP | 0x1);
  ssd1306_command(SSD1306_COMSCANDEC);

#if defined SSD1306_128_32
  ssd1306_command(SSD1306_SETCOMPINS); // 0xDA
  ssd1306_command(0x02);
  ssd1306_command(SSD1306_SETCONTRAST); // 0x81
  ssd1306_command(0x8F);

#elif defined SSD1306_128_64
  ssd1306_command(SSD1306_SETCOMPINS); // 0xDA
  ssd1306_command(0x12);
  ssd1306_command(SSD1306_SETCONTRAST); // 0x81
  if (vccstate == SSD1306_EXTERNALVCC)
  {
    ssd1306_command(0x9F);
  }
  else
  {
    ssd1306_command(0xCF);
  }

#elif defined SSD1306_96_16
  ssd1306_command(SSD1306_SETCOMPINS);  // 0xDA
  ssd1306_command(0x2);                 // ada x12
  ssd1306_command(SSD1306_SETCONTRAST); // 0x81
  if (vccstate == SSD1306_EXTERNALVCC)
  {
    ssd1306_command(0x10);
  }
  else
  {
    ssd1306_command(0xAF);
  }

#endif

  ssd1306_command(SSD1306_SETPRECHARGE); // 0xd9
  if (vccstate == SSD1306_EXTERNALVCC)
  {
    ssd1306_command(0x22);
  }
  else
  {
    ssd1306_command(0xF1);
  }
  ssd1306_command(SSD1306_SETVCOMDETECT); // 0xDB
  ssd1306_command(0x40);
  ssd1306_command(SSD1306_DISPLAYALLON_RESUME); // 0xA4
  ssd1306_command(SSD1306_NORMALDISPLAY);       // 0xA6

  ssd1306_command(SSD1306_DEACTIVATE_SCROLL);

  ssd1306_command(SSD1306_DISPLAYON); //--turn on oled panel

  _height = SSD1306_LCDHEIGHT;
  _width = SSD1306_LCDWIDTH;

   // set cursor to (0, 0)
  x_pos = 0;
  y_pos = 0;
  // set text size to 1
  text_size = 1;
  display();
  
  display_clear();
  delay(100);
 
  DrawText(20, 20, "HELLO SHAKTI !!!", 1);
  DrawText(-10, 0, " Booting on Vajra", 1);
  display();
  display_clear();
  delay(100);
  display_clear();
	}
