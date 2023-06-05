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
 * @file stepdown3.c
 * @brief Step Down 3 Click Driver.
 */

#include "stepdown3.h"

void stepdown3_cfg_setup ( stepdown3_cfg_t *cfg ) 
{
    cfg->d2  = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;
    cfg->aux = HAL_PIN_NC;
    cfg->d1  = HAL_PIN_NC;
    cfg->d0  = HAL_PIN_NC;
}

err_t stepdown3_init ( stepdown3_t *ctx, stepdown3_cfg_t *cfg ) 
{
    err_t return_flag = STEPDOWN3_OK;
    return_flag |= digital_out_init( &ctx->d2, cfg->d2 );
    return_flag |= digital_out_init( &ctx->en, cfg->en );
    return_flag |= digital_out_init( &ctx->aux, cfg->aux );
    return_flag |= digital_out_init( &ctx->d1, cfg->d1 );
    return_flag |= digital_out_init( &ctx->d0, cfg->d0 );
    return return_flag;
}

void stepdown3_enable_device ( stepdown3_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepdown3_disable_device ( stepdown3_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stepdown3_enable_aux_output ( stepdown3_t *ctx )
{
    digital_out_high ( &ctx->aux );
}

void stepdown3_disable_aux_output ( stepdown3_t *ctx )
{
    digital_out_low ( &ctx->aux );
}

void stepdown3_set_output_voltage ( stepdown3_t *ctx, uint8_t vout )
{
    switch ( vout )
    {
        case STEPDOWN3_OUT_VOLTAGE_1V6:
        {
            digital_out_high ( &ctx->d2 );
            digital_out_high ( &ctx->d1 );
            digital_out_low ( &ctx->d0 );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_1V8:
        {
            digital_out_low ( &ctx->d2 );
            digital_out_low ( &ctx->d1 );
            digital_out_low ( &ctx->d0 );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V1:
        {
            digital_out_high ( &ctx->d2 );
            digital_out_low ( &ctx->d1 );
            digital_out_high ( &ctx->d0 );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V5:
        {
            digital_out_high ( &ctx->d2 );
            digital_out_high ( &ctx->d1 );
            digital_out_high ( &ctx->d0 );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V7:
        {
            digital_out_low ( &ctx->d2 );
            digital_out_high ( &ctx->d1 );
            digital_out_high ( &ctx->d0 );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_2V8:
        {
            digital_out_low ( &ctx->d2 );
            digital_out_high ( &ctx->d1 );
            digital_out_low ( &ctx->d0 );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_3V0:
        {
            digital_out_high ( &ctx->d2 );
            digital_out_low ( &ctx->d1 );
            digital_out_low ( &ctx->d0 );
            break;
        }
        case STEPDOWN3_OUT_VOLTAGE_3V3:
        {
            digital_out_low ( &ctx->d2 );
            digital_out_low ( &ctx->d1 );
            digital_out_high ( &ctx->d0 );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
