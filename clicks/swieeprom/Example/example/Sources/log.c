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
 * @file  log.c
 * @brief LOG driver implementation.
 */

#include "log.h"

void log_init ( void )
{
    #ifdef ARM
    UART6_Init_Advanced( 115200, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_ONE_STOPBIT, &_GPIO_MODULE_USART6_PC67 );
    UART6_Write_Text( "\r\n" );
    #elif defined PIC
    ANCON1 = 0x00;
    ANCON2 = 0x00;
    UART1_Init( 115200 );
    #elif defined PIC32
    AD1PCFG = 0xFFFF;           
    UART2_Init( 115200 );       
    #else
    #endif
    Delay_ms( 10 );
}

void log_line ( char *txt )
{
    #if defined ARM || defined PIC || defined PIC32
    UART_Write_Text( txt );
    UART_Write_Text( "\r\n" );
    #endif
}

void log_txt ( char *txt )
{
    #if defined ARM || defined PIC || defined PIC32
    UART_Write_Text( txt );
    #endif
}

void log_byte ( char t_char )
{
    #if defined ARM || defined PIC || defined PIC32
    UART_Write( t_char );
    #endif
}


// ------------------------------------------------------------------------ END
