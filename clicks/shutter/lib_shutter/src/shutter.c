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
 * @file shutter.c
 * @brief Shutter Click Driver.
 */

#include "shutter.h"

void shutter_cfg_setup ( shutter_cfg_t *cfg ) 
{
    cfg->af = HAL_PIN_NC;
    cfg->sht = HAL_PIN_NC;
}

err_t shutter_init ( shutter_t *ctx, shutter_cfg_t *cfg ) 
{
    err_t error_flag = SHUTTER_OK;
    error_flag |= digital_out_init( &ctx->af, cfg->af );
    error_flag |= digital_out_init( &ctx->sht, cfg->sht );
    digital_out_low ( &ctx->af );
    digital_out_low ( &ctx->sht );
    return error_flag;
}

void shutter_set_auto_focus ( shutter_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->af, state );
}

void shutter_set_shutter ( shutter_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->sht, state );
}

void shutter_take_picture ( shutter_t *ctx, uint8_t auto_focus )
{
    if ( SHUTTER_STATE_ON == auto_focus )
    {
        shutter_set_auto_focus ( ctx, SHUTTER_STATE_ON );
        Delay_1sec ( );
        Delay_1sec ( );
        Delay_1sec ( );
        shutter_set_shutter ( ctx, SHUTTER_STATE_ON );
        Delay_100ms ( );
        Delay_100ms ( );
        Delay_100ms ( );
        shutter_set_shutter ( ctx, SHUTTER_STATE_OFF );
        shutter_set_auto_focus ( ctx, SHUTTER_STATE_OFF );
    }
    else
    {
        shutter_set_auto_focus ( ctx, SHUTTER_STATE_OFF );
        shutter_set_shutter ( ctx, SHUTTER_STATE_ON );
        Delay_1sec ( );
        Delay_1sec ( );
        Delay_1sec ( );
        shutter_set_shutter ( ctx, SHUTTER_STATE_OFF );
    }
}

// ------------------------------------------------------------------------- END
