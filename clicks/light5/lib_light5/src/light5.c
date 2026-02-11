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
 * @file light5.c
 * @brief Light 5 Click Driver.
 */

#include "light5.h"

void light5_cfg_setup ( light5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LIGHT5_DEVICE_ADDRESS_1;
}

err_t light5_init ( light5_t *ctx, light5_cfg_t *cfg ) 
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

err_t light5_default_cfg ( light5_t *ctx ) 
{
    err_t error_flag = LIGHT5_OK;
    
    if ( LIGHT5_ERROR == light5_check_communication ( ctx ) )
    {
        return LIGHT5_ERROR;
    }
    error_flag |= light5_write_reg ( ctx, LIGHT5_REG_CONFIG_0, LIGHT5_CONFIG_0_QWAKE_DIS | 
                                                               LIGHT5_CONFIG_0_RANGE_AUTO | 
                                                               LIGHT5_CONFIG_0_CONV_50MS | 
                                                               LIGHT5_CONFIG_0_OP_MODE_CONTINUOUS | 
                                                               LIGHT5_CONFIG_0_LATCH_EN | 
                                                               LIGHT5_CONFIG_0_INT_POL_LOW | 
                                                               LIGHT5_CONFIG_0_FAULT_COUNT_1 );
    error_flag |= light5_write_reg ( ctx, LIGHT5_REG_CONFIG_1, LIGHT5_CONFIG_1_RESERVED | 
                                                               LIGHT5_CONFIG_1_THRESHOLD_CH0 | 
                                                               LIGHT5_CONFIG_1_INT_DIR_OUTPUT | 
                                                               LIGHT5_CONFIG_1_INT_CFG_EVERY_4_CONV | 
                                                               LIGHT5_CONFIG_1_I2C_BURST_ENABLE );

    return error_flag;
}

err_t light5_write_reg ( light5_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t light5_read_reg ( light5_t *ctx, uint8_t reg, uint16_t *data_out )
{
    return light5_read_regs ( ctx, reg, data_out, 1 );
}

err_t light5_read_regs ( light5_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len ) 
{
    err_t error_flag = LIGHT5_OK;
    uint8_t data_buf[ 36 ] = { 0 };
    if ( ( len > 18 ) || ( NULL == data_out ) )
    {
        return LIGHT5_ERROR;
    }
    error_flag |= i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len * 2 );

    for ( uint8_t cnt = 0; ( cnt < len ) && ( LIGHT5_OK == error_flag ); cnt++ )
    {
        data_out[ cnt ] = ( ( uint16_t ) data_buf[ cnt * 2 ] << 8 ) | data_buf[ ( cnt * 2 ) + 1 ];
    }
    return error_flag;
}

uint8_t light5_get_int_pin ( light5_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t light5_check_communication ( light5_t *ctx )
{
    uint16_t device_id = 0;
    if ( LIGHT5_OK == light5_read_reg ( ctx, LIGHT5_REG_DEVICE_ID, &device_id ) )
    {
        if ( LIGHT5_DEVICE_ID == device_id )
        {
            return LIGHT5_OK;
        }
    }
    return LIGHT5_ERROR;
}

err_t light5_read_raw_data ( light5_t *ctx, uint8_t ch_sel, light5_raw_data_t *data_out )
{
    uint16_t reg_data[ 2 ] = { 0 };
    err_t error_flag = light5_read_regs ( ctx, LIGHT5_REG_CH0_EXP_RESMSB + ( ch_sel * 2 ), reg_data, 2 );
    if ( LIGHT5_OK == error_flag )
    {
        data_out->exponent = ( uint8_t ) ( ( reg_data[ 0 ] >> 12 ) & 0x0F );
        data_out->mantissa = ( ( uint32_t ) ( reg_data[ 0 ] & 0x0FFF ) << 8 ) | ( ( reg_data[ 1 ] >> 8 ) & 0xFF );
        data_out->counter = ( uint8_t ) ( ( reg_data[ 1 ] >> 4 ) & 0x0F );
        data_out->crc = ( uint8_t ) ( reg_data[ 1 ] & 0x0F );
    }
    return error_flag;
}

err_t light5_read_adc_data ( light5_t *ctx, light5_adc_data_t *data_out )
{
    uint16_t reg_data[ 4 ] = { 0 };
    light5_raw_data_t ch_data[ 2 ];
    err_t error_flag = light5_read_regs ( ctx, LIGHT5_REG_CH0_EXP_RESMSB, reg_data, 4 );
    for ( uint8_t ch_sel = LIGHT5_CHANNEL_0; ch_sel <= LIGHT5_CHANNEL_1; ch_sel++ )
    {
        ch_data[ ch_sel ].exponent = ( uint8_t ) ( ( reg_data[ ch_sel * 2 ] >> 12 ) & 0x0F );
        ch_data[ ch_sel ].mantissa = ( ( uint32_t ) ( reg_data[ ch_sel * 2 ] & 0x0FFF ) << 8 ) | 
                                     ( ( reg_data[ ( ch_sel * 2 ) + 1 ] >> 8 ) & 0xFF );
        ch_data[ ch_sel ].counter = ( uint8_t ) ( ( reg_data[ ( ch_sel * 2 ) + 1 ] >> 4 ) & 0x0F );
        ch_data[ ch_sel ].crc = ( uint8_t ) ( reg_data[ ( ch_sel * 2 ) + 1 ] & 0x0F );
    }
    if ( LIGHT5_OK == error_flag )
    {
        data_out->ch0 = ch_data[ 0 ].mantissa << ch_data[ 0 ].exponent;
        data_out->ch1 = ch_data[ 1 ].mantissa << ch_data[ 1 ].exponent;
    }
    return error_flag;
}

err_t light5_read_data ( light5_t *ctx, light5_data_t *data_out )
{
    light5_adc_data_t adc_data;
    err_t error_flag = light5_read_adc_data ( ctx, &adc_data );
    if ( LIGHT5_OK == error_flag )
    {
        data_out->lux = ( adc_data.ch0 * LIGHT5_COEF_LUX );
        data_out->wide_band = ( adc_data.ch1 * LIGHT5_COEF_UW_CM2 );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
