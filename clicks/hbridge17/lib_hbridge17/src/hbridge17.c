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
 * @file hbridge17.c
 * @brief H-Bridge 17 Click Driver.
 */

#include "hbridge17.h"

void hbridge17_cfg_setup ( hbridge17_cfg_t *cfg ) 
{
    cfg->in2 = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;
}

err_t hbridge17_init ( hbridge17_t *ctx, hbridge17_cfg_t *cfg ) 
{
    err_t err_flag = HBRIDGE17_OK;
    
    err_flag |= digital_out_init( &ctx->in2, cfg->in2 );
    err_flag |= digital_out_init( &ctx->en, cfg->en );
    err_flag |= digital_out_init( &ctx->in1, cfg->in1 );

    err_flag |= digital_in_init( &ctx->flt, cfg->flt );

    return err_flag;
}

void hbridge17_ic_enable ( hbridge17_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void hbridge17_ic_disable ( hbridge17_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

void hbridge17_set_in1_pin ( hbridge17_t *ctx ) 
{
    digital_out_high( &ctx->in1 );
}

void hbridge17_clear_in1_pin ( hbridge17_t *ctx ) 
{
    digital_out_low( &ctx->in1 );
}

void hbridge17_set_in2_pin ( hbridge17_t *ctx ) 
{
    digital_out_high( &ctx->in2 );
}

void hbridge17_clear_in2_pin ( hbridge17_t *ctx ) 
{
    digital_out_low( &ctx->in2 );
}

err_t hbridge17_set_out_state ( hbridge17_t *ctx, hbridge17_out_state_t out_state )
{
    err_t err_flag = HBRIDGE17_OK;
    switch ( out_state )
    {
        case ( HBRIDGE17_DRIVE_MOTOR_FORWARD ):
        {
            hbridge17_ic_disable( ctx );
            hbridge17_set_in1_pin( ctx );
            hbridge17_clear_in2_pin( ctx );
            hbridge17_ic_enable( ctx );
            break;
        }
        case ( HBRIDGE17_DRIVE_MOTOR_BRAKE ):
        {
            hbridge17_ic_disable( ctx );
            hbridge17_set_in1_pin( ctx );
            hbridge17_set_in2_pin( ctx );
            hbridge17_ic_enable( ctx );
            break;
        }
        case ( HBRIDGE17_DRIVE_MOTOR_REVERSE ):
        {
            hbridge17_ic_disable( ctx );
            hbridge17_clear_in1_pin( ctx );
            hbridge17_set_in2_pin( ctx );
            hbridge17_ic_enable( ctx );
            break;
        }
        case ( HBRIDGE17_DRIVE_MOTOR_FREEWHEEL ):
        {
            hbridge17_ic_disable( ctx );
            hbridge17_clear_in1_pin( ctx );
            hbridge17_clear_in2_pin( ctx );
            break;
        }
        default:
        {
           err_flag = HBRIDGE17_ERROR;
           break;
        }
    }
    return err_flag;
}

uint8_t hbridge17_fault_indication ( hbridge17_t *ctx ) 
{
    return digital_in_read( &ctx->flt );
}

// ------------------------------------------------------------------------- END
