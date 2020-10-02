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

#include "ledflash.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ledflash_cfg_setup ( ledflash_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->ch_ena = HAL_PIN_NC;
    cfg->fls    = HAL_PIN_NC;
    cfg->tor    = HAL_PIN_NC;
    cfg->flg    = HAL_PIN_NC;
}

LEDFLASH_RETVAL ledflash_init ( ledflash_t *ctx, ledflash_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->ch_ena, cfg->ch_ena );
    digital_out_init( &ctx->fls, cfg->fls );
    digital_out_init( &ctx->tor, cfg->tor );

    // Input pins

    digital_in_init( &ctx->flg, cfg->flg );

    return LEDFLASH_OK;
}

void ledflash_char_supcap_enable ( ledflash_t *ctx )
{
    digital_out_high( &ctx->ch_ena );
}

void ledflash_flash_enable ( ledflash_t *ctx )
{
    digital_out_high( &ctx->fls );
}

void ledflash_torch_enable ( ledflash_t *ctx )
{
    digital_out_high( &ctx->tor );
}

void ledflash_char_supcap_disable ( ledflash_t *ctx )
{
    digital_out_low( &ctx->ch_ena );
}

void ledflash_flash_disable ( ledflash_t *ctx )
{
    digital_out_low( &ctx->fls );
}

void ledflash_torch_disable ( ledflash_t *ctx )
{
    digital_out_low( &ctx->tor );
}
 
uint8_t ledflash_flash_rdy_flag ( ledflash_t *ctx )
{
    return digital_in_read( &ctx->flg );
}

// ------------------------------------------------------------------------- END

