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
 * @file light3.c
 * @brief Light 3 Click Driver.
 */

#include "light3.h"

void light3_cfg_setup ( light3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LIGHT3_DEVICE_ADDRESS_0;
}

err_t light3_init ( light3_t *ctx, light3_cfg_t *cfg ) 
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

err_t light3_default_cfg ( light3_t *ctx ) 
{
    err_t error_flag = LIGHT3_OK;
    
    error_flag |= light3_sw_reset( ctx );
    
    error_flag |= light3_write_reg( ctx, LIGHT3_REG_CONFIG, LIGHT3_QWAKE_EN | LIGHT3_RANGE_2_2_KLUX | 
                                                            LIGHT3_CONV_TIME_800_MS | LIGHT3_MODE_CONTINUOUS | 
                                                            LIGHT3_LATCH | LIGHT3_INT_POL_ACTIVE_LOW );
    error_flag |= light3_write_reg( ctx, LIGHT3_REG_INT_CONFIG, LIGHT3_INT_CONFIG_REG_DEF_VALUE | 
                                                                LIGHT3_INT_DIR_OUTPUT | LIGHT3_INT_EVERY_2_CONV );


    return error_flag;
}

err_t light3_generic_write ( light3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t light3_generic_read ( light3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t light3_get_int_pin ( light3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t light3_sw_reset ( light3_t *ctx )
{
    err_t error_flag = LIGHT3_OK;
    uint8_t tmp_data = LIGHT3_SW_RESET_COMMAND;

    error_flag |= i2c_master_set_slave_address( &ctx->i2c, LIGHT3_SW_RESET_ADDRESS );
    error_flag |= i2c_master_write( &ctx->i2c, &tmp_data, 1 );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    Delay_100ms( );

    return error_flag;
}

err_t light3_write_reg ( light3_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t tmp_data[ 2 ] = { 0 };

    tmp_data[ 0 ] = ( uint8_t ) ( data_in >> 8 );
    tmp_data[ 1 ] = ( uint8_t ) data_in;

    return light3_generic_write( ctx, reg, tmp_data, 2 );
}

err_t light3_read_reg ( light3_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = LIGHT3_OK;
    uint8_t tmp_data[ 2 ] = { 0 };

    error_flag |= light3_generic_read( ctx, reg, tmp_data, 2 );

    *data_out =  ( ( uint16_t ) tmp_data[ 0 ] << 8 ) | ( uint16_t ) tmp_data[ 1 ];

    return error_flag;
}

err_t light3_get_ch0_data ( light3_t *ctx, float *lux )
{
    err_t error_flag = LIGHT3_OK;
    uint16_t tmp_data[ 2 ] = { 0 };
    uint32_t mantissa = 0;
    uint32_t adc_code = 0;

    error_flag |= light3_read_reg( ctx, LIGHT3_REG_RESULT_MSB_CH0, &tmp_data[ 0 ] );
    error_flag |= light3_read_reg( ctx, LIGHT3_REG_RESULT_LSB_CH0, &tmp_data[ 1 ] );

    mantissa = ( ( uint32_t ) (  tmp_data[ 0 ] & 0x0FFF ) << 8 ) | ( ( uint32_t ) tmp_data[ 1 ] >> 8 );
    adc_code = ( uint32_t ) mantissa << ( tmp_data[ 0 ] >> 12 );
    *lux = ( float ) adc_code * LIGHT3_LUX_CONV_FACTOR;

    return error_flag;
}

err_t light3_get_ch1_data ( light3_t *ctx, float *lux )
{
    err_t error_flag = LIGHT3_OK;
    uint16_t tmp_data[ 2 ] = { 0 };
    uint32_t mantissa = 0;
    uint32_t adc_code = 0;

    error_flag |= light3_read_reg( ctx, LIGHT3_REG_RESULT_MSB_CH1, &tmp_data[ 0 ] );
    error_flag |= light3_read_reg( ctx, LIGHT3_REG_RESULT_LSB_CH1, &tmp_data[ 1 ] );

    mantissa = ( ( uint32_t ) (  tmp_data[ 0 ] & 0x0FFF ) << 8 ) | ( ( uint32_t ) tmp_data[ 1 ] >> 8 );
    adc_code = ( uint32_t ) mantissa << ( tmp_data[ 0 ] >> 12 );
    *lux = ( float ) adc_code * LIGHT3_LUX_CONV_FACTOR;

    return error_flag;
}

err_t light3_get_ch0_fifo_data ( light3_t *ctx, float *lux )
{
    err_t error_flag = LIGHT3_OK;
    uint16_t tmp_data[ 2 ] = { 0 };
    uint32_t mantissa = 0;
    uint32_t adc_code = 0;

    error_flag |= light3_read_reg( ctx, LIGHT3_REG_RESULT_FIFO_MSB_CH0, &tmp_data[ 0 ] );
    error_flag |= light3_read_reg( ctx, LIGHT3_REG_RESULT_FIFO_LSB_CH0, &tmp_data[ 1 ] );

    mantissa = ( ( uint32_t ) (  tmp_data[ 0 ] & 0x0FFF ) << 8 ) | ( ( uint32_t ) tmp_data[ 1 ] >> 8 );
    adc_code = ( uint32_t ) mantissa << ( tmp_data[ 0 ] >> 12 );
    *lux = ( float ) adc_code * LIGHT3_LUX_CONV_FACTOR;

    return error_flag;
}

err_t light3_get_ch1_fifo_data ( light3_t *ctx, float *lux )
{
    err_t error_flag = LIGHT3_OK;
    uint16_t tmp_data[ 2 ] = { 0 };
    uint32_t mantissa = 0;
    uint32_t adc_code = 0;

    error_flag |= light3_read_reg( ctx, LIGHT3_REG_RESULT_MSB_CH1, &tmp_data[ 0 ] );
    error_flag |= light3_read_reg( ctx, LIGHT3_REG_RESULT_LSB_CH1, &tmp_data[ 1 ] );

    mantissa = ( ( uint32_t ) (  tmp_data[ 0 ] & 0x0FFF ) << 8 ) | ( ( uint32_t ) tmp_data[ 1 ] >> 8 );
    adc_code = ( uint32_t ) mantissa << ( tmp_data[ 0 ] >> 12 );
    *lux = ( float ) adc_code * LIGHT3_LUX_CONV_FACTOR;

    return error_flag;
}

// ------------------------------------------------------------------------- END
