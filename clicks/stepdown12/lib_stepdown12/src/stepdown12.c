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
 * @file stepdown12.c
 * @brief Step Down 12 Click Driver.
 */

#include "stepdown12.h"

void stepdown12_cfg_setup ( stepdown12_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->mode = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPDOWN12_ADDR_A2A1A0_000;
}

err_t stepdown12_init ( stepdown12_t *ctx, stepdown12_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->mode, cfg->mode );

    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

void stepdown12_default_cfg ( stepdown12_t *ctx ) 
{
    stepdown12_enable_device ( ctx );
    stepdown12_mode_auto_pwm ( ctx );
    Delay_100ms ( );
}

err_t stepdown12_set_resistance ( stepdown12_t *ctx, uint32_t res_ohm )
{
    if ( res_ohm > STEPDOWN12_DIGIPOT_MAX_VALUE )
    {
        return STEPDOWN12_ERROR;
    }
    uint16_t raw_res = ( uint16_t ) ( ( ( float ) res_ohm / STEPDOWN12_DIGIPOT_MAX_VALUE ) * 
                                      STEPDOWN12_DIGIPOT_RESOLUTION + STEPDOWN12_ROUND_TO_NEAREST_INT );
    
    uint8_t data_buf[ 2 ] = { ( uint8_t ) ( ( raw_res >> 8 ) & 0x01 ), ( uint8_t ) ( raw_res & 0xFF ) };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepdown12_set_vout ( stepdown12_t *ctx, float vout )
{
    if ( ( vout < STEPDOWN12_VOUT_MIN ) || ( vout > STEPDOWN12_VOUT_MAX ) )
    {
        return STEPDOWN12_ERROR;
    }
    int32_t res_ohm = STEPDOWN12_R1 / ( ( vout - STEPDOWN12_VFB ) / STEPDOWN12_VFB ) - 
                     ( STEPDOWN12_R2 + STEPDOWN12_WIPER_RESISTANCE );
    if ( res_ohm < STEPDOWN12_DIGIPOT_MIN_VALUE )
    {
        res_ohm = STEPDOWN12_DIGIPOT_MIN_VALUE;
    }
    else if ( res_ohm > STEPDOWN12_DIGIPOT_MAX_VALUE )
    {
        res_ohm = STEPDOWN12_DIGIPOT_MAX_VALUE;
    }
    return stepdown12_set_resistance( ctx, res_ohm );
}

uint8_t stepdown12_get_pg_pin ( stepdown12_t *ctx )
{
    return digital_in_read ( &ctx->pg );
}

void stepdown12_enable_device ( stepdown12_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepdown12_disable_device ( stepdown12_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stepdown12_mode_forced_pwm ( stepdown12_t *ctx )
{
    digital_out_high ( &ctx->mode );
}

void stepdown12_mode_auto_pwm ( stepdown12_t *ctx )
{
    digital_out_low ( &ctx->mode );
}

// ------------------------------------------------------------------------- END
