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
 * @file stepdown13.c
 * @brief Step Down 13 Click Driver.
 */

#include "stepdown13.h"

void stepdown13_cfg_setup ( stepdown13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->mode = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPDOWN13_DEVICE_ADDRESS_0;
}

err_t stepdown13_init ( stepdown13_t *ctx, stepdown13_cfg_t *cfg ) 
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

    digital_out_init( &ctx->mode, cfg->mode );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_low ( &ctx->mode );
    digital_out_low ( &ctx->en );
    Delay_1ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t stepdown13_set_vreg ( stepdown13_t *ctx, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = STEPDOWN13_CONTROL_VREG;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepdown13_set_nvreg ( stepdown13_t *ctx, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = STEPDOWN13_CONTROL_NVREG;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t stepdown13_move_vreg_to_nvreg ( stepdown13_t *ctx )
{
    uint8_t control = STEPDOWN13_CONTROL_VREG_X_NVREG;
    return i2c_master_write( &ctx->i2c, &control, 1 );
}

err_t stepdown13_move_nvreg_to_vreg ( stepdown13_t *ctx )
{
    uint8_t control = STEPDOWN13_CONTROL_NVREG_X_VREG;
    return i2c_master_write( &ctx->i2c, &control, 1 );
}

void stepdown13_enable_output ( stepdown13_t *ctx )
{
    digital_out_high ( &ctx->en );
    Delay_1ms ( );
}

void stepdown13_disable_output ( stepdown13_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_1ms ( );
}

void stepdown13_set_cot_mode ( stepdown13_t *ctx )
{
    digital_out_high ( &ctx->mode );
    Delay_1ms ( );
}

void stepdown13_set_pfm_mode ( stepdown13_t *ctx )
{
    digital_out_low ( &ctx->mode );
    Delay_1ms ( );
}

err_t stepdown13_set_vout ( stepdown13_t *ctx, float vout )
{
    err_t error_flag = STEPDOWN13_OK;
    uint16_t wiper = 0;
    float rfbb = 0;
    if ( ( vout > ( STEPDOWN13_VOUT_MAX + STEPDOWN13_FLOAT_COMPARE_OFFSET ) ) || 
         ( vout < ( STEPDOWN13_VOUT_MIN - STEPDOWN13_FLOAT_COMPARE_OFFSET ) ) )
    {
        return STEPDOWN13_ERROR;
    }
    rfbb = STEPDOWN13_R10_OHM / ( ( vout / STEPDOWN13_FB_VOLTAGE ) - 1 ) - STEPDOWN13_WIPER_RES_OHM - STEPDOWN13_R9_OHM;
    wiper = ( ( rfbb / ( STEPDOWN13_FULL_SCALE_OHM * STEPDOWN13_ACTUAL_FULL_SCALE_PCT ) ) * STEPDOWN13_WIPER_POS_MAX );
    if ( wiper > STEPDOWN13_WIPER_POS_MAX )
    {
        wiper = STEPDOWN13_WIPER_POS_MAX;
    }
    return stepdown13_set_vreg( ctx, ( uint8_t ) wiper );
}

// ------------------------------------------------------------------------- END
