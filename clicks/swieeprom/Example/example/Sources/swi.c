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
 * @file  swi.c
 * @brief SWI master driver implementation.
 */

#include "swi.h"
#include "gpio.h"

/**
 * @brief Mask for bit sampling
 * @details Mask for bit sampling for data read/write
 */
#define BIT_MASK_VAL                    0x80

/**
 * @brief Reset and Discovery Response Timing
 * @details Reset and Discovery Response Timing for HIGH SPEED functionality
 */
#define HS_TRESET                       96
#define HS_TDSCHG                       150
#define HS_TRRT                         8
#define HS_TDRR                         1 //1-2     <- DS
#define HS_TDACK                        8 //8-24    <- DS
#define HS_TMSDR                        2 //2-6     <- DS
#define HS_THTSS                        150

/**
 * @brief Data Communication Timing
 * @details Data Communication Timing for HIGH SPEED functionality
 */
#define HS_TBIT                         8 //8-25    <- DS
#define HS_TLOW0                        6 //6-16    <- DS
#define HS_TLOW1                        1 //1-2     <- DS
#define HS_TRD                          1 //1-2     <- DS
#define HS_TMRS                         1 //1-2     <- DS
#define HS_THLD0                        2 //2-6     <- DS
#define HS_TRCV                         2

/**
 * @brief Discover device.
 * @details Sends signal discovering device
 * @return @li @c  0 - Device found,
 *         @li @c -1 - No device.
 */
static int8_t discover_device ( void );

int8_t swi_init ( void )
{
    if ( swi_reset(  ) )
    {
        return SWI_RET_VAL_ERROR;
    }

    pin_init( );

    return SWI_RET_VAL_OK;
}

int8_t swi_reset ( void )
{
    //reset
    pin_low( );
    Delay_us( HS_TDSCHG );
    pin_release( );
    Delay_us( HS_TRRT );
    
    //discovery
    if ( discover_device( ) )
        return SWI_RET_VAL_ERROR;
    else
        return SWI_RET_VAL_OK;
}

void swi_start ( void )
{
    pin_release( );
    Delay_us( HS_THTSS );
}

void swi_stop ( void )
{
    pin_release( );
    Delay_us( HS_THTSS + HS_TRCV );
}

void swi_logic_write ( swi_logic_lvl_t logic_level )
{
    if ( logic_level )
    {   //LOGIC 1
        pin_low( );
        Delay_us( HS_TLOW1 );
        pin_release( );
        Delay_us( HS_TBIT - HS_TLOW1 );
    }
    else
    {   //LOGIC 0
        pin_low( );
        Delay_us( HS_TLOW0 );
        pin_release( );
        Delay_us( HS_TBIT - HS_TLOW0 );
    }
}

uint8_t swi_logic_read ( void )
{
    pin_low( );
    Delay_us( HS_TRD );
    pin_release( );
    Delay_us( HS_TMRS );
    uint8_t pin_state = pin_get();
    Delay_us( HS_TBIT - HS_TRD - HS_TMRS );
    return pin_state;
}

uint8_t swi_send_byte ( uint8_t byte_to_send )
{
    for ( uint8_t bit_mask = BIT_MASK_VAL; bit_mask >= 1; bit_mask >>= 1 )
    {
        if ( bit_mask & byte_to_send )
        {
            swi_logic_write( SWI_LOGIC_1 );
        }
        else
        {
            swi_logic_write( SWI_LOGIC_0 );
        }
    }

    return swi_logic_read(  );
}

void swi_receive_byte ( uint8_t *byte_to_receive, swi_acknowledgement_t ack_nack )
{
    for ( uint8_t bit_mask = BIT_MASK_VAL; bit_mask >= 1; bit_mask >>= 1 )
    {
        if ( swi_logic_read() )
        {
            *byte_to_receive |= bit_mask;
        }
    }

    swi_logic_write( ack_nack );
}

static int8_t discover_device ( void )
{
    pin_low( );
    Delay_us( HS_TDRR );
    pin_release( );
    Delay_us( HS_TDACK );
    
    if ( pin_get( ) )
        return SWI_RET_VAL_ERROR;
    else
        return SWI_RET_VAL_OK;
}


// ------------------------------------------------------------------------ END
