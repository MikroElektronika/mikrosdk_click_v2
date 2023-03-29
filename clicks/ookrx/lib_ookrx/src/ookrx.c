/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "ookrx.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ookrx_cfg_setup ( ookrx_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->rsi   = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->sq   = HAL_PIN_NC;
    cfg->do_pin = HAL_PIN_NC;
}

OOKRX_RETVAL ookrx_init ( ookrx_t *ctx, ookrx_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->sq, cfg->sq );

    // Input pins

    digital_in_init( &ctx->rsi, cfg->rsi );
    digital_in_init( &ctx->do_pin, cfg->do_pin );

    digital_out_write( &ctx->sq, 0 );
    digital_out_write( &ctx->en, 1 );

    return OOKRX_OK;
}

uint8_t ookrx_receive_data ( ookrx_t *ctx, uint16_t start_package, 
                             uint8_t *receive_buffer, uint8_t bytes_num )
{
    uint8_t ext_cnt;
    uint8_t int_cnt;
    uint16_t data_buffer;
    uint16_t input_data;
    uint16_t timeout;

    data_buffer = 0;
    input_data = 0;
    timeout = 50000;

    while ( timeout )                         
    {
        if ( ookrx_read_do_pin( ctx ) )                
        {
            break;
        }

        Delay_1us();
        timeout--;
    }

    if ( timeout == 0 )                       
    {
        return 1;
    }

    for ( ext_cnt = 0; ext_cnt < 100; ext_cnt++ )              
    {
        data_buffer = ( data_buffer << 1 ) + ookrx_read_do_pin( ctx );    
        Delay_500us( );

        if ( data_buffer == start_package )                         
        {
            for( int_cnt = 0; int_cnt < bytes_num; int_cnt++ )                  
            {
                for( ext_cnt = 0; ext_cnt < 8; ext_cnt++ )
                {
                    input_data = ( input_data << 1 ) + ookrx_read_do_pin( ctx );
                    Delay_500us();
                }
                receive_buffer[ int_cnt ] = input_data;
            }

            return 0;
        }
    }
    
    for ( int_cnt = 0; int_cnt < bytes_num; int_cnt++ )
    {
        receive_buffer[ int_cnt ] = 0;
    }

    return 1;
}

uint8_t ookrx_read_do_pin ( ookrx_t *ctx )
{
    return digital_in_read( &ctx->do_pin );
}

uint8_t ookrx_read_rsi_pin ( ookrx_t *ctx )
{
    return digital_in_read( &ctx->rsi );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS


// ------------------------------------------------------------------------- END

