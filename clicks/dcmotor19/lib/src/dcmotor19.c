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
 * @file dcmotor19.c
 * @brief DC Motor 19 Click Driver.
 */

#include "dcmotor19.h"

void dcmotor19_cfg_setup ( dcmotor19_cfg_t *cfg ) 
{
    cfg->in1 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->sby = HAL_PIN_NC;
    cfg->in3 = HAL_PIN_NC;
    cfg->in4 = HAL_PIN_NC;
}

err_t dcmotor19_init ( dcmotor19_t *ctx, dcmotor19_cfg_t *cfg ) 
{
    err_t return_flag = 0;

    return_flag |= digital_out_init( &ctx->in1, cfg->in1 );
    return_flag |= digital_out_init( &ctx->in2, cfg->in2 );
    return_flag |= digital_out_init( &ctx->sby, cfg->sby );
    return_flag |= digital_out_init( &ctx->in3, cfg->in3 );
    return_flag |= digital_out_init( &ctx->in4, cfg->in4 );

    return return_flag;
}

err_t dcmotor19_drive_motor ( dcmotor19_t *ctx, uint8_t speed, uint32_t time_ms ) 
{
    if ( ( 0 == ctx->active_ch ) || ( ctx->active_ch > 3 ) ||
         ( speed > DCMOTOR19_SPEED_MAX ) || ( speed < DCMOTOR19_SPEED_MIN ) ||
         ( ctx->mode > DCMOTOR19_MODE_SHORT_BRAKE ) )
    {
        return DCMOTOR19_ERROR;
    }
    uint8_t mode = ctx->mode;
    for ( uint32_t time_cnt = speed; time_cnt < ( time_ms * DCMOTOR19_MS_TIME_STEP ); time_cnt += speed )
    {
        dcmotor19_set_channel_mode( ctx, ctx->active_ch, mode );
        for ( uint8_t speed_cnt = 0; speed_cnt < speed; speed_cnt++ )
        {
            Delay_50us( );
        }
        dcmotor19_set_channel_mode( ctx, ctx->active_ch, DCMOTOR19_MODE_STOP );
        for ( uint8_t speed_cnt = 0; speed_cnt < speed; speed_cnt++ )
        {
            Delay_50us( );
        }
    }
    ctx->mode = mode;
    return DCMOTOR19_OK;
}

err_t dcmotor19_set_channel_mode ( dcmotor19_t *ctx, uint8_t channel, uint8_t mode ) 
{
    if ( ( 0 == channel ) || ( channel > 3 ) )
    {
        return DCMOTOR19_ERROR;
    }

    switch ( mode )
    {
        case DCMOTOR19_MODE_STOP:
        {
            if ( DCMOTOR19_CHANNEL_1 & channel )
            {
                digital_out_low ( &ctx->in1 );
                digital_out_low ( &ctx->in2 );
            }
            if ( DCMOTOR19_CHANNEL_2 & channel )
            {
                digital_out_low ( &ctx->in3 );
                digital_out_low ( &ctx->in4 );
            }
            ctx->active_ch = channel;
            ctx->mode = DCMOTOR19_MODE_STOP;
            return DCMOTOR19_OK;
        }
        case DCMOTOR19_MODE_FORWARD:
        {
            if ( DCMOTOR19_CHANNEL_1 & channel )
            {
                digital_out_high ( &ctx->in1 );
                digital_out_low ( &ctx->in2 );
            }
            if ( DCMOTOR19_CHANNEL_2 & channel )
            {
                digital_out_high ( &ctx->in3 );
                digital_out_low ( &ctx->in4 );
            }
            ctx->active_ch = channel;
            ctx->mode = DCMOTOR19_MODE_FORWARD;
            return DCMOTOR19_OK;
        }
        case DCMOTOR19_MODE_REVERSE:
        {
            if ( DCMOTOR19_CHANNEL_1 & channel )
            {
                digital_out_low ( &ctx->in1 );
                digital_out_high ( &ctx->in2 );
            }
            if ( DCMOTOR19_CHANNEL_2 & channel )
            {
                digital_out_low ( &ctx->in3 );
                digital_out_high ( &ctx->in4 );
            }
            ctx->active_ch = channel;
            ctx->mode = DCMOTOR19_MODE_REVERSE;
            return DCMOTOR19_OK;
        }
        case DCMOTOR19_MODE_SHORT_BRAKE:
        {
            if ( DCMOTOR19_CHANNEL_1 & channel )
            {
                digital_out_high ( &ctx->in1 );
                digital_out_high ( &ctx->in2 );
            }
            if ( DCMOTOR19_CHANNEL_2 & channel )
            {
                digital_out_high ( &ctx->in3 );
                digital_out_high ( &ctx->in4 );
            }
            ctx->active_ch = channel;
            ctx->mode = DCMOTOR19_MODE_SHORT_BRAKE;
            return DCMOTOR19_OK;
        }
        default:
        {
            return DCMOTOR19_ERROR;
        }
    }
}

void dcmotor19_disable_standby_mode ( dcmotor19_t *ctx ) 
{
    digital_out_high ( &ctx->sby );
}

void dcmotor19_enable_standby_mode ( dcmotor19_t *ctx ) 
{
    digital_out_low ( &ctx->sby );
}

// ------------------------------------------------------------------------- END
