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
 * @file light4.c
 * @brief Light 4 Click Driver.
 */

#include "light4.h"

void light4_cfg_setup ( light4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en  = HAL_PIN_NC;
    cfg->snc = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LIGHT4_DEVICE_ADDRESS;
}

err_t light4_init ( light4_t *ctx, light4_cfg_t *cfg ) 
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
    digital_out_init( &ctx->snc, cfg->snc );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t light4_default_cfg ( light4_t *ctx ) 
{
    err_t error_flag = LIGHT4_OK;

    light4_set_en_pin( ctx, LIGHT4_PIN_STATE_HIGH );
    Delay_100ms( );
    
    error_flag |= light4_sw_reset( ctx );
    Delay_100ms( );

    error_flag |= light4_write_reg( ctx, LIGHT4_REG_ENABLE, LIGHT4_FDEN | LIGHT4_AEN | LIGHT4_PON );
    error_flag |= light4_write_reg( ctx, LIGHT4_REG_MOD_CHANNEL_CTRL, LIGHT4_MOD_ENABLE_ALL );
    error_flag |= light4_write_reg( ctx, LIGHT4_REG_INTENAB, LIGHT4_MIEN );
    
    return error_flag;
}

err_t light4_generic_write ( light4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t light4_generic_read ( light4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void light4_set_en_pin ( light4_t *ctx, uint8_t pin_state )
{
    if ( LIGHT4_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

void light4_set_snc_pin ( light4_t *ctx, uint8_t pin_state )
{
    if ( LIGHT4_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->snc );
    }
    else
    {
        digital_out_low( &ctx->snc );
    }
}

uint8_t light4_get_int_pin ( light4_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t light4_write_reg ( light4_t *ctx, uint8_t reg, uint8_t data_in )
{
    return light4_generic_write( ctx, reg, &data_in, 1 );
}

err_t light4_read_reg ( light4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return light4_generic_read( ctx, reg, data_out, 1 );
}

err_t light4_sw_reset ( light4_t *ctx )
{
    err_t error_flag = LIGHT4_OK;
    
    error_flag |= light4_write_reg( ctx, LIGHT4_REG_ENABLE, LIGHT4_PON );
    error_flag |= light4_write_reg( ctx, LIGHT4_REG_CONTROL, LIGHT4_SOFT_RESET );
    
    return error_flag;
}

err_t light4_read_channel_data ( light4_t *ctx, uint8_t channel_sel, float *channel_data )
{
    err_t error_flag = LIGHT4_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    uint8_t status_data = 0;
    uint8_t multiplier = 0;
    uint8_t als_scale = 0;
    uint8_t channel_sel_adr = 0;
    uint8_t sat_mask = 0;
    uint8_t mul_mask = 0;
    uint32_t raw_data = 0;
    float calib_data = 0;

    switch ( channel_sel )
    {
        case ( LIGHT4_CHANNEL0_SEL ):
        {
            channel_sel_adr = LIGHT4_REG_ALS_DATA0_LSB;
            sat_mask = LIGHT4_ALS_DATA0_ANALOG_SATURATION_STATUS;
            mul_mask = LIGHT4_ALS_DATA0_SCALED_STATUS;
            break;
        }
        case ( LIGHT4_CHANNEL1_SEL ):
        {
            channel_sel_adr = LIGHT4_REG_ALS_DATA1_LSB;
            sat_mask = LIGHT4_ALS_DATA1_ANALOG_SATURATION_STATUS;
            mul_mask = LIGHT4_ALS_DATA1_SCALED_STATUS;
            break;
        }
        case ( LIGHT4_CHANNEL2_SEL ):
        {
            channel_sel_adr = LIGHT4_REG_ALS_DATA1_LSB;
            sat_mask = LIGHT4_ALS_DATA2_ANALOG_SATURATION_STATUS;
            mul_mask = LIGHT4_ALS_DATA2_SCALED_STATUS;
            break;
        }
        default:
        {
            return LIGHT4_ERROR;
        }
    }

    error_flag |= light4_read_reg( ctx, LIGHT4_REG_UV_CALIB, &tmp_data[ 0 ] );
    calib_data = 1 - ( ( ( float ) tmp_data[ 0 ] - 127 ) / 100 );

    error_flag |= light4_read_reg( ctx, LIGHT4_REG_ALS_STATUS, &status_data );

    if ( status_data & sat_mask )
    {
        return LIGHT4_ANALOG_SAT;
    }

    if ( status_data & mul_mask )
    {
        multiplier = 1;
    }
    else
    {
        error_flag |= light4_read_reg( ctx, LIGHT4_REG_MEAS_MODE0, &als_scale );
        als_scale &= 0x0F;
        multiplier = 1 << als_scale;
    }

    error_flag |= light4_generic_read( ctx, channel_sel_adr, tmp_data, 2 );
    raw_data = ( ( ( uint16_t ) tmp_data[ 1 ] << 8 ) | tmp_data[ 0 ] ) * multiplier;

    *channel_data = ( float ) raw_data / calib_data;

    return error_flag;
}

// ------------------------------------------------------------------------- END
