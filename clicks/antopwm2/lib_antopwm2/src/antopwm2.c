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
 * @file antopwm2.c
 * @brief AN to PWM 2 Click Driver.
 */

#include "antopwm2.h"

void antopwm2_cfg_setup ( antopwm2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ANTOPWM2_DEVICE_ADDRESS;
}

err_t antopwm2_init ( antopwm2_t *ctx, antopwm2_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t antopwm2_set_digipot ( antopwm2_t *ctx, uint8_t wiper )
{
    uint8_t data_buf[ 2 ] = { 0, wiper };
    if ( wiper > ANTOPWM2_DIGIPOT_WIPER_MAX )
    {
        return ANTOPWM2_ERROR;
    }
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t antopwm2_read_digipot ( antopwm2_t *ctx, uint8_t *data_out )
{
    return i2c_master_read( &ctx->i2c, data_out, 1 );
}

err_t antopwm2_set_digipot_otp ( antopwm2_t *ctx, uint8_t wiper )
{
    uint8_t data_buf[ 2 ] = { ANTOPWM2_OTP_BIT, wiper };
    uint8_t state = 0;
    if ( wiper > ANTOPWM2_DIGIPOT_WIPER_MAX )
    {
        return ANTOPWM2_ERROR;
    }
    err_t error_flag = antopwm2_read_digipot ( ctx, &state );
    if ( ( ANTOPWM2_OK == error_flag ) && 
         ( ANTOPWM2_STATUS_READY == ( state & ANTOPWM2_STATUS_MASK ) ) )
    {
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, 2 );
        Delay_1ms ( );
        error_flag |= antopwm2_read_digipot ( ctx, &state );
        if ( ( ANTOPWM2_OK == error_flag ) && 
             ( ANTOPWM2_STATUS_OTP_SUCCESS != ( state & ANTOPWM2_STATUS_MASK ) ) )
        {
            error_flag = ANTOPWM2_ERROR;
        }
    }
    return error_flag;
}

err_t antopwm2_set_frequency ( antopwm2_t *ctx, uint32_t freq )
{
    uint8_t wiper = 0;
    uint32_t rset = 0;
    uint32_t wiper_res = 0;
    if ( ( freq < ANTOPWM2_FREQ_MIN ) || ( freq > ANTOPWM2_FREQ_MAX ) )
    {
        return ANTOPWM2_ERROR;
    }
    rset = ( ( float ) ANTOPWM2_FREQ_MAX / freq ) * ( ( float ) ANTOPWM2_RSET_REF / ANTOPWM2_NDIV );
    wiper_res = ( rset - ANTOPWM2_DIGIPOT_R6 - ANTOPWM2_DIGIPOT_WIPER_RES );
    if ( wiper_res > ANTOPWM2_DIGIPOT_MAX_RES )
    {
        wiper_res = ANTOPWM2_DIGIPOT_MAX_RES;
    }
    wiper = ( float ) wiper_res / ANTOPWM2_DIGIPOT_MAX_RES * ANTOPWM2_DIGIPOT_WIPER_MAX;
    return antopwm2_set_digipot ( ctx, wiper );
}

err_t antopwm2_set_frequency_otp ( antopwm2_t *ctx, uint32_t freq )
{
    uint8_t wiper = 0;
    uint32_t rset = 0;
    uint32_t wiper_res = 0;
    if ( ( freq < ANTOPWM2_FREQ_MIN ) || ( freq > ANTOPWM2_FREQ_MAX ) )
    {
        return ANTOPWM2_ERROR;
    }
    rset = ( ( float ) ANTOPWM2_FREQ_MAX / freq ) * ( ( float ) ANTOPWM2_RSET_REF / ANTOPWM2_NDIV );
    wiper_res = ( rset - ANTOPWM2_DIGIPOT_R6 - ANTOPWM2_DIGIPOT_WIPER_RES );
    if ( wiper_res > ANTOPWM2_DIGIPOT_MAX_RES )
    {
        wiper_res = ANTOPWM2_DIGIPOT_MAX_RES;
    }
    wiper = ( float ) wiper_res / ANTOPWM2_DIGIPOT_MAX_RES * ANTOPWM2_DIGIPOT_WIPER_MAX;
    return antopwm2_set_digipot_otp ( ctx, wiper );
}

uint8_t antopwm2_get_int_pin ( antopwm2_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
