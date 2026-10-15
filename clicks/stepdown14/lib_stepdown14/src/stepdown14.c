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
 * @file stepdown14.c
 * @brief Step Down 14 Click Driver.
 */

#include "stepdown14.h"

void stepdown14_cfg_setup ( stepdown14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPDOWN14_DEVICE_ADDRESS_0;
}

err_t stepdown14_init ( stepdown14_t *ctx, stepdown14_cfg_t *cfg ) 
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
    digital_out_low ( &ctx->en );

    digital_in_init( &ctx->pg, cfg->pg );
    Delay_10ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t stepdown14_set_vreg ( stepdown14_t *ctx, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = STEPDOWN14_CONTROL_VREG;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepdown14_set_nvreg ( stepdown14_t *ctx, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = STEPDOWN14_CONTROL_NVREG;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepdown14_move_vreg_to_nvreg ( stepdown14_t *ctx )
{
    uint8_t control = STEPDOWN14_CONTROL_VREG_X_NVREG;
    return i2c_master_write( &ctx->i2c, &control, 1 );
}

err_t stepdown14_move_nvreg_to_vreg ( stepdown14_t *ctx )
{
    uint8_t control = STEPDOWN14_CONTROL_NVREG_X_VREG;
    return i2c_master_write( &ctx->i2c, &control, 1 );
}

void stepdown14_enable_device ( stepdown14_t *ctx )
{
    digital_out_high ( &ctx->en );
    Delay_10ms ( );
}

void stepdown14_disable_device ( stepdown14_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_10ms ( );
}

uint8_t stepdown14_get_pg_pin ( stepdown14_t *ctx )
{
    return !!digital_in_read ( &ctx->pg );
}

err_t stepdown14_set_vout ( stepdown14_t *ctx, float target_vout, float *set_vout )
{
    err_t error_flag = STEPDOWN14_OK;
    uint16_t wiper = 0;
    float target_rfbb = 0;
    float set_rfbb = 0;
    if ( ( target_vout > ( STEPDOWN14_VOUT_MAX + STEPDOWN14_FLOAT_COMPARE_OFFSET ) ) || 
         ( target_vout < ( STEPDOWN14_VOUT_MIN - STEPDOWN14_FLOAT_COMPARE_OFFSET ) ) )
    {
        return STEPDOWN14_ERROR;
    }
    target_rfbb = STEPDOWN14_R7_OHM / ( ( target_vout / STEPDOWN14_FB_VOLTAGE ) - 1 ) - STEPDOWN14_WIPER_RES_OHM - STEPDOWN14_R10_OHM;
    wiper = ( ( target_rfbb / STEPDOWN14_FULL_SCALE_OHM ) * STEPDOWN14_WIPER_POS_MAX );
    if ( wiper > STEPDOWN14_WIPER_POS_MAX )
    {
        wiper = STEPDOWN14_WIPER_POS_MAX;
    }
    if ( NULL != set_vout )
    {
        set_rfbb = ( wiper * STEPDOWN14_FULL_SCALE_OHM ) / STEPDOWN14_WIPER_POS_MAX;
        *set_vout = ( STEPDOWN14_R7_OHM / ( set_rfbb + STEPDOWN14_WIPER_RES_OHM + STEPDOWN14_R10_OHM ) + 1 ) * STEPDOWN14_FB_VOLTAGE;
    }
    return stepdown14_set_vreg( ctx, ( uint8_t ) wiper );
}

// ------------------------------------------------------------------------- END
