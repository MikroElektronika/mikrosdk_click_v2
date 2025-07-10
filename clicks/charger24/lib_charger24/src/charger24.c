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
 * @file charger24.c
 * @brief Charger 24 Click Driver.
 */

#include "charger24.h"

void charger24_cfg_setup ( charger24_cfg_t *cfg ) 
{
    cfg->iok = HAL_PIN_NC;
    cfg->dsb = HAL_PIN_NC;
    cfg->dis = HAL_PIN_NC;
    cfg->stat = HAL_PIN_NC;
}

err_t charger24_init ( charger24_t *ctx, charger24_cfg_t *cfg ) 
{
    err_t error_flag = CHARGER24_OK;

    error_flag |= digital_out_init( &ctx->dsb, cfg->dsb );
    error_flag |= digital_out_init( &ctx->dis, cfg->dis );

    error_flag |= digital_in_init( &ctx->iok, cfg->iok );
    error_flag |= digital_in_init( &ctx->stat, cfg->stat );

    return error_flag;
}

void charger24_enable_boost ( charger24_t *ctx ) 
{
    digital_out_low( &ctx->dsb );
}

void charger24_disable_boost ( charger24_t *ctx ) 
{
    digital_out_high( &ctx->dsb );
}

void charger24_enable_charging ( charger24_t *ctx ) 
{
    digital_out_low( &ctx->dis );
}

void charger24_disable_charging ( charger24_t *ctx ) 
{
    digital_out_high( &ctx->dis );
}

uint8_t charger24_get_stat_pin ( charger24_t *ctx ) 
{
    return digital_in_read( &ctx->stat ) & 1;
}

uint8_t charger24_get_iok_pin ( charger24_t *ctx ) 
{
    return digital_in_read( &ctx->iok ) & 1;
}

uint8_t charger24_get_status ( charger24_t *ctx ) 
{
    uint16_t timeout = 0;
    
    while ( charger24_get_stat_pin( ctx ) )
    {
        if ( ++timeout > 1000 )
        {
            return CHARGER24_STATE_NO_INPUT;
        }
        Delay_1ms ( );
    }
    timeout = 0;
    
    while ( !charger24_get_stat_pin( ctx ) )
    {
        if ( ++timeout > 1000 )
        {
            return CHARGER24_STATE_CHARGE_DONE;
        }
        Delay_1ms ( );
    }
    return CHARGER24_STATE_CHARGING;
}

// ------------------------------------------------------------------------- END
