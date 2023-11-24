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
 * @file ooktx.c
 * @brief OOK TX Click Driver.
 */

#include "ooktx.h"

void ooktx_cfg_setup ( ooktx_cfg_t *cfg ) 
{
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
}

err_t ooktx_init ( ooktx_t *ctx, ooktx_cfg_t *cfg ) 
{
    err_t error_flag = OOKTX_OK;

    error_flag |= digital_out_init( &ctx->sda, cfg->sda );
    error_flag |= digital_out_init( &ctx->sck, cfg->sck );

    return error_flag;
}

void ooktx_set_data_pin ( ooktx_t *ctx )
{
    digital_out_high( &ctx->sda );
}

void ooktx_clear_data_pin ( ooktx_t *ctx )
{
    digital_out_low( &ctx->sda );
}

void ooktx_set_clock_pin ( ooktx_t *ctx )
{
    digital_out_high( &ctx->sck );
}

void ooktx_clear_clock_pin ( ooktx_t *ctx )
{
    digital_out_low( &ctx->sck );
}

void ooktx_start ( ooktx_t *ctx, uint8_t calib_en, uint8_t cfg_en, uint16_t cfg )
{
    uint8_t bit_cnt = 0;
    uint16_t config_word = cfg;

    Delay_10ms( );
    Delay_10ms( );

    ooktx_clear_data_pin( ctx );
    ooktx_clear_clock_pin( ctx );
    Delay_80us( );

    if ( calib_en )
    {
        ooktx_set_data_pin( ctx );
    }
    ooktx_set_clock_pin( ctx );
    Delay_80us( );
    ooktx_clear_clock_pin( ctx );
    Delay_80us( );

    if ( cfg_en )
    {
        ooktx_set_data_pin( ctx );
    }
    else
    {
        ooktx_clear_data_pin( ctx );
    }
    ooktx_set_clock_pin( ctx );
    Delay_80us( );
    ooktx_clear_clock_pin( ctx );
    Delay_80us( );

    if ( cfg_en )
    {
        for ( bit_cnt = 0; bit_cnt < 16; bit_cnt++ )
        {
            if ( config_word & OOKTX_MAN_MSB )
            {
                ooktx_set_data_pin ( ctx );
            }
            else
            {
                ooktx_clear_data_pin ( ctx );
            }
            config_word <<= 1;
            ooktx_set_clock_pin( ctx );
            Delay_80us( );
            ooktx_clear_clock_pin( ctx );
        }
        ooktx_clear_data_pin( ctx );
        ooktx_set_clock_pin( ctx );
        Delay_80us( );
        ooktx_clear_clock_pin( ctx );
    }
    Delay_5ms( );
}

void ooktx_stop ( ooktx_t *ctx )
{
    ooktx_clear_data_pin( ctx );
    ooktx_set_clock_pin( ctx );
    ooktx_set_data_pin( ctx );
}

// ------------------------------------------------------------------------- END
