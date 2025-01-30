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
 * @file color19.c
 * @brief Color 19 Click Driver.
 */

#include "color19.h"

void color19_cfg_setup ( color19_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COLOR19_DEVICE_ADDRESS_0;
}

err_t color19_init ( color19_t *ctx, color19_cfg_t *cfg ) 
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

err_t color19_default_cfg ( color19_t *ctx ) 
{
    err_t error_flag = COLOR19_OK;
    if ( COLOR19_ERROR == color19_check_communication ( ctx ) )
    {
        return COLOR19_ERROR;
    }
    error_flag |= color19_write_reg ( ctx, COLOR19_REG_CONFIG_0, COLOR19_CONFIG_0_QWAKE_DIS | 
                                                                 COLOR19_CONFIG_0_RANGE_AUTO | 
                                                                 COLOR19_CONFIG_0_CONV_50MS | 
                                                                 COLOR19_CONFIG_0_OP_MODE_CONTINUOUS | 
                                                                 COLOR19_CONFIG_0_LATCH_EN | 
                                                                 COLOR19_CONFIG_0_INT_POL_LOW | 
                                                                 COLOR19_CONFIG_0_FAULT_COUNT_1 );
    error_flag |= color19_write_reg ( ctx, COLOR19_REG_CONFIG_1, COLOR19_CONFIG_1_RESERVED | 
                                                                 COLOR19_CONFIG_1_THRESHOLD_CH0 | 
                                                                 COLOR19_CONFIG_1_INT_DIR_OUTPUT | 
                                                                 COLOR19_CONFIG_1_INT_CFG_ALL_CH_RDY | 
                                                                 COLOR19_CONFIG_1_I2C_BURST_ENABLE );
    return error_flag;
}

err_t color19_write_reg ( color19_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t color19_read_reg ( color19_t *ctx, uint8_t reg, uint16_t *data_out )
{
    return color19_read_regs ( ctx, reg, data_out, 1 );
}

err_t color19_read_regs ( color19_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len ) 
{
    err_t error_flag = COLOR19_OK;
    uint8_t data_buf[ 36 ] = { 0 };
    if ( ( len > 18 ) || ( NULL == data_out ) )
    {
        return COLOR19_ERROR;
    }
    error_flag |= i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len * 2 );

    for ( uint8_t cnt = 0; ( cnt < len ) && ( COLOR19_OK == error_flag ); cnt++ )
    {
        data_out[ cnt ] = ( ( uint16_t ) data_buf[ cnt * 2 ] << 8 ) | data_buf[ ( cnt * 2 ) + 1 ];
    }
    return error_flag;
}

uint8_t color19_get_int_pin ( color19_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t color19_check_communication ( color19_t *ctx )
{
    uint16_t device_id = 0;
    if ( COLOR19_OK == color19_read_reg ( ctx, COLOR19_REG_DEVICE_ID, &device_id ) )
    {
        if ( COLOR19_DEVICE_ID == device_id )
        {
            return COLOR19_OK;
        }
    }
    return COLOR19_ERROR;
}

err_t color19_read_raw_data ( color19_t *ctx, uint8_t ch_sel, color19_raw_data_t *data_out )
{
    uint16_t reg_data[ 2 ] = { 0 };
    err_t error_flag = color19_read_regs ( ctx, COLOR19_REG_CH0_EXP_RESMSB + ( ch_sel * 2 ), reg_data, 2 );
    if ( COLOR19_OK == error_flag )
    {
        data_out->exponent = ( uint8_t ) ( ( reg_data[ 0 ] >> 12 ) & 0x0F );
        data_out->mantissa = ( ( uint32_t ) ( reg_data[ 0 ] & 0x0FFF ) << 8 ) | ( ( reg_data[ 1 ] >> 8 ) & 0xFF );
        data_out->counter = ( uint8_t ) ( ( reg_data[ 1 ] >> 4 ) & 0x0F );
        data_out->crc = ( uint8_t ) ( reg_data[ 1 ] & 0x0F );
    }
    return error_flag;
}

err_t color19_read_adc_data ( color19_t *ctx, color19_adc_data_t *data_out )
{
    uint16_t reg_data[ 8 ] = { 0 };
    color19_raw_data_t ch_data[ 4 ];
    err_t error_flag = color19_read_regs ( ctx, COLOR19_REG_CH0_EXP_RESMSB, reg_data, 8 );
    for ( uint8_t ch_sel = COLOR19_CHANNEL_0; ch_sel <= COLOR19_CHANNEL_3; ch_sel++ )
    {
        ch_data[ ch_sel ].exponent = ( uint8_t ) ( ( reg_data[ ch_sel * 2 ] >> 12 ) & 0x0F );
        ch_data[ ch_sel ].mantissa = ( ( uint32_t ) ( reg_data[ ch_sel * 2 ] & 0x0FFF ) << 8 ) | 
                                     ( ( reg_data[ ( ch_sel * 2 ) + 1 ] >> 8 ) & 0xFF );
        ch_data[ ch_sel ].counter = ( uint8_t ) ( ( reg_data[ ( ch_sel * 2 ) + 1 ] >> 4 ) & 0x0F );
        ch_data[ ch_sel ].crc = ( uint8_t ) ( reg_data[ ( ch_sel * 2 ) + 1 ] & 0x0F );
    }
    if ( COLOR19_OK == error_flag )
    {
        data_out->ch0 = ch_data[ 0 ].mantissa << ch_data[ 0 ].exponent;
        data_out->ch1 = ch_data[ 1 ].mantissa << ch_data[ 1 ].exponent;
        data_out->ch2 = ch_data[ 2 ].mantissa << ch_data[ 2 ].exponent;
        data_out->ch3 = ch_data[ 3 ].mantissa << ch_data[ 3 ].exponent;
    }
    return error_flag;
}

err_t color19_read_data ( color19_t *ctx, color19_data_t *data_out )
{
    color19_adc_data_t adc_data;
    err_t error_flag = color19_read_adc_data ( ctx, &adc_data );
    if ( COLOR19_OK == error_flag )
    {
        data_out->red = ( uint32_t ) ( adc_data.ch0 * COLOR19_COEF_RED );
        data_out->green = ( uint32_t ) ( adc_data.ch1 * COLOR19_COEF_GREEN );
        data_out->blue = ( uint32_t ) ( adc_data.ch2 * COLOR19_COEF_BLUE );
        data_out->white = adc_data.ch3;
        data_out->lux = ( uint32_t ) ( adc_data.ch1 * COLOR19_COEF_LUX );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
