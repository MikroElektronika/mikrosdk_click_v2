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

#include "ooktx.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

void drv_start_condition_signal ( ooktx_t *ctx );

void drv_word_start_signal ( ooktx_t *ctx, uint8_t word );

void drv_word_end_signal ( ooktx_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ooktx_cfg_setup ( ooktx_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->sda   = HAL_PIN_NC;
    cfg->scl   = HAL_PIN_NC;
}

OOKTX_RETVAL ooktx_init ( ooktx_t *ctx, ooktx_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->sda, cfg->sda );
    digital_out_init( &ctx->scl, cfg->scl );

    digital_out_write( &ctx->scl, 1 );
    digital_out_write( &ctx->sda, 1 );

    return OOKTX_OK;
}

void ooktx_communication_init ( ooktx_t *ctx, uint8_t calibration, 
                                uint8_t configuration, uint16_t cfg_settings )
{
    uint8_t cnt;
    uint16_t config_word;

    Delay_10ms(  );
    Delay_10ms(  );

    drv_start_condition_signal( ctx );

    drv_word_start_signal( ctx, calibration );
    drv_word_end_signal( ctx );

    drv_word_start_signal( ctx, configuration );
    drv_word_end_signal( ctx );

    if ( configuration )
    {
        for ( cnt = 0; cnt < 16; cnt++ )
        {
            config_word = ( cfg_settings >> ( 15 - cnt ) );
            drv_word_start_signal( ctx, config_word & 0x01 );
            digital_out_write( &ctx->scl, 0 );
        }

        drv_word_start_signal( ctx, 0 );
        digital_out_write( &ctx->scl, 0 );
    }

    Delay_5ms( );
}

void ooktx_communication_stop ( ooktx_t *ctx )
{
    digital_out_write( &ctx->sda, 0 );
    digital_out_write( &ctx->scl, 1 );
    digital_out_write( &ctx->sda, 1 );
}

void ooktx_communication_transmit ( ooktx_t *ctx, uint8_t transmit_data )
{
    uint8_t cnt;
    uint8_t transmit_bit;

    for ( cnt = 0; cnt < 8; cnt++ )                    
    {
        transmit_bit = ( transmit_data >> ( 7 - cnt ) ) & 0x01;
        digital_out_write( &ctx->sda, transmit_bit );
        Delay_500us( );
    }
}

void ooktx_transmit_byte ( ooktx_t *ctx, uint16_t preable_word, uint8_t transmit_byte )
{
    uint8_t transmit_bit;

    for ( uint8_t cnt = 0; cnt < 16; cnt++ )                    
    {
        transmit_bit = ( preable_word >> ( 15 - cnt ) ) & 0x01;
        digital_out_write( &ctx->sda, transmit_bit );
        Delay_500us( );
    }
    
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )                    
    {
        transmit_bit = ( transmit_byte >> ( 7 - cnt ) ) & 0x01;
        digital_out_write( &ctx->sda, transmit_bit );
        Delay_500us( );
    }
}

void ooktx_transmit_data ( ooktx_t *ctx, uint16_t preable_word, uint8_t *transmit_data, uint8_t transmit_len )
{
    uint8_t transmit_bit;

    for ( uint8_t cnt = 0; cnt < 16; cnt++ )                    
    {
        transmit_bit = ( preable_word >> ( 15 - cnt ) ) & 0x01;
        digital_out_write( &ctx->sda, transmit_bit );
        Delay_500us( );
    }
    
    for ( uint8_t len_cnt = 0; len_cnt < transmit_len; len_cnt++ )
    {
        for ( uint8_t cnt = 0; cnt < 8; cnt++ )                    
        {
            transmit_bit = ( transmit_data[ len_cnt ] >> ( 7 - cnt ) ) & 0x01;
            digital_out_write( &ctx->sda, transmit_bit );
            Delay_500us( );
        }
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void drv_start_condition_signal ( ooktx_t *ctx )
{
    digital_out_write( &ctx->sda, 0 );
    digital_out_write( &ctx->scl, 0 );
    Delay_80us( );
}

void drv_word_start_signal ( ooktx_t *ctx, uint8_t word )
{
    digital_out_write( &ctx->sda, word );
    digital_out_write( &ctx->scl, 1 );
    Delay_80us( );
}

void drv_word_end_signal ( ooktx_t *ctx )
{
    digital_out_write( &ctx->scl, 0 );
    Delay_80us( );
}

// ------------------------------------------------------------------------- END

