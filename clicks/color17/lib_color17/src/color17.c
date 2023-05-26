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
 * @file color17.c
 * @brief Color 17 Click Driver.
 */

#include "color17.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                        0x00

/**
 * @brief Color 17 light and color measurement values.
 * @details Definition of measurement values for light and color calculations.
 */
#define COLOR17_MATRIX_M0X           0.000234892992
#define COLOR17_MATRIX_M1X           0.0000407467441
#define COLOR17_MATRIX_M2X           0.0000928619404
#define COLOR17_MATRIX_M3X           0
#define COLOR17_MATRIX_M0Y          -0.0000189652390
#define COLOR17_MATRIX_M1Y           0.000198958202
#define COLOR17_MATRIX_M2Y          -0.0000169739553
#define COLOR17_MATRIX_M3Y           0
#define COLOR17_MATRIX_M0Z           0.0000120811684
#define COLOR17_MATRIX_M1Z          -0.000158848115
#define COLOR17_MATRIX_M2Z           0.000674021520
#define COLOR17_MATRIX_M3Z           0
#define COLOR17_MATRIX_M0L           0
#define COLOR17_MATRIX_M1L           0.00215
#define COLOR17_MATRIX_M2L           0
#define COLOR17_MATRIX_M3L           0
#define COLOR17_CCT_N_CIEX           0.3320
#define COLOR17_CCT_N_CIEY           0.1858
#define COLOR17_CCT_A3               437.0
#define COLOR17_CCT_A2               3601.0
#define COLOR17_CCT_A1               6861.0
#define COLOR17_CCT_A0               5517.0

void color17_cfg_setup ( color17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COLOR17_DEVICE_ADDRESS_GND;
}

err_t color17_init ( color17_t *ctx, color17_cfg_t *cfg ) 
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

err_t color17_default_cfg ( color17_t *ctx ) 
{
    uint16_t device_id = DUMMY;
    err_t err_flag = color17_get_device_id( ctx, &device_id );
    if ( COLOR17_DEVICE_ID == device_id )
    {
        color17_config_t config;
        config.qwake = COLOR17_CONFIG_0_QWAKE_DIS;
        config.range = COLOR17_CONFIG_0_RANGE_AUTO;
        config.conv_time = COLOR17_CONFIG_0_CONV_100MS;
        config.op_mode = COLOR17_CONFIG_0_OP_MODE_CONTINUOUS;
        config.latch = COLOR17_CONFIG_0_LATCH_EN;
        config.int_pol = COLOR17_CONFIG_0_INT_POL_LOW;
        config.fault_cnt = COLOR17_CONFIG_0_FAULT_COUNT_0;
        config.thld_ch_sel = COLOR17_CONFIG_1_THRESHOLD_CH0;
        config.int_dir = COLOR17_CONFIG_1_INT_DIR_OUTPUT;
        config.int_cfg = COLOR17_CONFIG_1_INT_CFG_ALL_CH;
        config.i2c_burst = COLOR17_CONFIG_1_I2C_BURST_ENABLE;
        err_flag |= color17_set_config( ctx, config );
    }
    else
    {
        err_flag = COLOR17_ERROR;
    }
    return err_flag;
}

err_t color17_generic_write ( color17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t color17_generic_read ( color17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t color17_write_reg ( color17_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in >> 8 );
    data_buf[ 1 ] = ( uint8_t )   data_in;
    err_t err_flag = color17_generic_write( ctx, reg, data_buf, 2 );
    return err_flag;
}

err_t color17_read_reg ( color17_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    *data_out = data_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 1 ];
    return err_flag;
}

err_t color17_get_device_id ( color17_t *ctx, uint16_t *device_id ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = color17_generic_read( ctx, COLOR17_REG_DEVICE_ID, data_buf, 2 );
    *device_id = data_buf[ 0 ];
    *device_id <<= 8;
    *device_id |= data_buf[ 1 ];
    return err_flag;
}

err_t color17_set_config ( color17_t *ctx, color17_config_t config ) 
{
    uint16_t data_buf = DUMMY;
    data_buf  = ( ( uint16_t ) config.qwake     & 0x01 ) << 15;
    data_buf |= ( ( uint16_t ) config.range     & 0x0F ) << 10;
    data_buf |= ( ( uint16_t ) config.conv_time & 0x0F ) << 6;
    data_buf |= ( ( uint16_t ) config.op_mode   & 0x03 ) << 4;
    data_buf |= ( ( uint16_t ) config.latch     & 0x01 ) << 3;
    data_buf |= ( ( uint16_t ) config.int_pol   & 0x01 ) << 2;
    data_buf |=   ( uint16_t ) config.fault_cnt & 0x03;
    err_t err_flag = color17_write_reg( ctx, COLOR17_REG_CONFIG_0, data_buf );
    data_buf  = COLOR17_CONFIG_1_MUST_READ_WRITE;
    data_buf |= ( ( uint16_t ) config.thld_ch_sel & 0x03 ) << 5;
    data_buf |= ( ( uint16_t ) config.int_dir     & 0x01 ) << 4;
    data_buf |= ( ( uint16_t ) config.int_cfg     & 0x03 ) << 2;
    data_buf |=   ( uint16_t ) config.i2c_burst   & 0x01;
    err_flag |= color17_write_reg( ctx, COLOR17_REG_CONFIG_1, data_buf );
    return err_flag;
}

err_t color17_get_status_flag ( color17_t *ctx, color17_status_flag_t *status_flag ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = color17_generic_read( ctx, COLOR17_REG_CONFIG_2, data_buf, 2 );
    status_flag->ovld_flag       = ( data_buf[ 1 ] >> 3 ) & 0x01;
    status_flag->conv_ready_flag = ( data_buf[ 1 ] >> 2 ) & 0x01;
    status_flag->flag_h          = ( data_buf[ 1 ] >> 1 ) & 0x01;
    status_flag->flag_h          =   data_buf[ 1 ]        & 0x01;
    return err_flag;
}

err_t color17_get_ch_measurement ( color17_t *ctx, uint8_t sel_ch, uint32_t *adc_codes ) 
{
    err_t err_flag;
    uint8_t data_buf[ 4 ] = { 0 };
    uint8_t exponent_ch = DUMMY;
    uint16_t mantissa_ch = DUMMY;
    if ( sel_ch <= COLOR17_SEL_CHANNEL_3 )
    {
        sel_ch <<= 1;
        color17_generic_read( ctx, COLOR17_REG_CH0_EXP_RESMSB + sel_ch, data_buf, 16 );
        exponent_ch = ( data_buf[ 0 ] >> 4 ) & 0x08;
        mantissa_ch = ( data_buf[ 0 ] & 0x0F );
        mantissa_ch <<= 8;
        mantissa_ch |= data_buf[ 1 ];
        mantissa_ch <<= 8;
        mantissa_ch |= data_buf[ 2 ];
        *adc_codes = mantissa_ch << exponent_ch;
    }
    else
    {
        err_flag = COLOR17_ERROR;
    }
    return err_flag;
}

err_t color17_get_measurement ( color17_t *ctx, uint32_t *adc_codes ) 
{
    uint8_t data_buf[ 16 ] = { 0 };
    uint8_t exponent_ch = DUMMY;
    uint32_t mantissa_ch = DUMMY;
    err_t err_flag = color17_generic_read( ctx, COLOR17_REG_CH0_EXP_RESMSB, data_buf, 16 );
    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    {
        exponent_ch = ( data_buf[ cnt * 4  ] >> 4 ) & 0x08;
        mantissa_ch = ( data_buf[ cnt * 4 ] & 0x0F );
        mantissa_ch <<= 8;
        mantissa_ch |= data_buf[ cnt * 4 + 1 ];
        mantissa_ch <<= 8;
        mantissa_ch |= data_buf[ cnt * 4 + 2 ];
        adc_codes[ cnt ] = ( ( uint32_t ) mantissa_ch ) << exponent_ch;
    }
    return err_flag;
}

err_t color17_get_cct ( color17_t *ctx, float *cct, float *light_intensity )
{
    uint32_t adc_codes[ 4 ] = { 0 };
    float x = 0, y = 0, z = 0, n = 0, cie_x = 0, cie_y = 0;
    err_t err_flag = color17_get_measurement( ctx, adc_codes );
    x  = ( ( float ) adc_codes[ 0 ] ) * COLOR17_MATRIX_M0X;
    x += ( ( float ) adc_codes[ 1 ] ) * COLOR17_MATRIX_M1X;
    x += ( ( float ) adc_codes[ 2 ] ) * COLOR17_MATRIX_M2X;
    y  = ( ( float ) adc_codes[ 0 ] ) * COLOR17_MATRIX_M0Y;
    y += ( ( float ) adc_codes[ 1 ] ) * COLOR17_MATRIX_M1Y;
    y += ( ( float ) adc_codes[ 2 ] ) * COLOR17_MATRIX_M2Y;
    z  = ( ( float ) adc_codes[ 0 ] ) * COLOR17_MATRIX_M0Z;
    z += ( ( float ) adc_codes[ 1 ] ) * COLOR17_MATRIX_M1Z;
    z += ( ( float ) adc_codes[ 2 ] ) * COLOR17_MATRIX_M2Z;
    cie_x = x / ( x + y + z );
    cie_y = y / ( x + y + z );
    n = ( cie_x - COLOR17_CCT_N_CIEX ) / ( COLOR17_CCT_N_CIEY - cie_y );
    *cct = ( COLOR17_CCT_A3 * n * n * n ) + ( COLOR17_CCT_A2 * n * n ) + ( COLOR17_CCT_A1 * n ) + COLOR17_CCT_A0;
    *light_intensity = ( float ) ( adc_codes[ 1 ] >> 1 ) * COLOR17_MATRIX_M1L;
    return err_flag;
}

uint8_t color17_get_int_pin ( color17_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
