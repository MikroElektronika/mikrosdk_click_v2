/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file chargepump.c
 * @brief Charge Pump Click Driver.
 */

#include "chargepump.h"

void chargepump_cfg_setup ( chargepump_cfg_t *cfg ) 
{
    cfg->run = HAL_PIN_NC;
    cfg->md  = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;
}

err_t chargepump_init ( chargepump_t *ctx, chargepump_cfg_t *cfg ) 
{
    err_t error_flag = CHARGEPUMP_OK;

    error_flag |= digital_out_init( &ctx->run, cfg->run );
    error_flag |= digital_out_init( &ctx->md, cfg->md );
    error_flag |= digital_in_init( &ctx->flt, cfg->flt );

    /* Safe initial state: device in shutdown and switching disabled */
    digital_out_low( &ctx->run );
    digital_out_low( &ctx->md );

    return error_flag;
}

void chargepump_enable_device ( chargepump_t *ctx ) 
{
    /* Enable the internal INTVCC regulator (datasheet page 11). */
    digital_out_high( &ctx->run );
}

void chargepump_disable_device ( chargepump_t *ctx ) 
{
    /* Turns off most internal circuits (datasheet page 11). */
    digital_out_low( &ctx->run );
}

void chargepump_enable_switching ( chargepump_t *ctx ) 
{
    /* Switching capacitors enabled (datasheet page 12). */
    digital_out_high( &ctx->md );
}

void chargepump_disable_switching ( chargepump_t *ctx ) 
{
    /* Enter standby mode -> switching capacitors disabled (datasheet page 12). */
    digital_out_low( &ctx->md );
}

uint8_t chargepump_get_flt_pin ( chargepump_t *ctx ) 
{
    return digital_in_read( &ctx->flt );
}

err_t chargepump_wait_output_ready ( chargepump_t *ctx )
{
    uint16_t timeout_cnt = CHARGEPUMP_TIMEOUT_MS;

    /* Poll until FLT pin is released -> device in full-power switching */
    while ( ( CHARGEPUMP_FAULT_ACTIVE == chargepump_get_flt_pin( ctx ) ) && ( timeout_cnt ) )
    {
        Delay_1ms( );
        timeout_cnt--;
    }

    if ( 0 == timeout_cnt )
    {
        return CHARGEPUMP_ERROR;
    }
    
    return CHARGEPUMP_OK;
}

// ------------------------------------------------------------------------- END
