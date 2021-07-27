/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/
/*!
 * @file  gpio.c
 * @brief Digital GPIO control implementation.
 */

#include "gpio.h"

#ifdef ARM
void inline init( void ) { GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_12); GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_12); }
        
void inline low( void ) { if (!GPIOD_MODER.B24) GPIOD_MODER.B24 = 1; GPIOD_ODR.B12 = 0; }

void inline high( void ) { if (!GPIOD_MODER.B24) GPIOD_MODER.B24 = 1; GPIOD_ODR.B12 = 1; }

void inline release( void ){ if (GPIOD_MODER.B24) GPIOD_MODER.B24 = 0; }

uint8_t inline get( void ) { if (GPIOD_MODER.B24) GPIOD_MODER.B24 = 0; return GPIOD_IDR.B12; }

#elif defined PIC        
void inline init( void ) { TRISG4_bit = 0; TRISG4_bit = 1; }

void inline low( void ) { if (TRISG4_bit) TRISG4_bit = 0; LATG4_bit = 0; }

void inline high( void ) { if (TRISG4_bit) TRISG4_bit = 0; LATG4_bit = 1; }

void inline release( void ) { if (!TRISG4_bit) TRISG4_bit = 1; }

uint8_t inline get( void ) { if (!TRISD1_bit) TRISD1_bit = 1; return RG4_bit; }
        
#elif defined PIC32
void inline init( void ) { TRISD1_bit = 0; TRISD1_bit = 1; }

void inline low( void ) { if (TRISD1_bit) TRISD1_bit = 0; LATD1_bit = 0; }

void inline high( void ) { if (TRISD1_bit) TRISD1_bit = 0; LATD1_bit = 1; }

void inline release( void ) { if (!TRISD1_bit) TRISD1_bit = 1; }

uint8_t inline get( void ) { if (!TRISD1_bit) TRISD1_bit = 1; return RD1_bit; }

#else

void inline init( void ) {  }

void inline low( void ) {  }

void inline high( void ) {  }

void inline release( void ) {  }

uint8_t inline get( void ) { return 1 }

#endif
        
    

void pin_init( void )
{
    init( );
}

void pin_low ( void )
{
    low( );
}

void pin_high ( void )
{
    high( );
}

void pin_release ( void )
{
    release( );
}

uint8_t pin_get ( void )
{
    return get( );
}


// ------------------------------------------------------------------------ END
