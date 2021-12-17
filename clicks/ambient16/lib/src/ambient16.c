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
 * @file ambient16.c
 * @brief Ambient 16 Click Driver.
 */

#include "ambient16.h"

/**
 * @brief Ambient 16 threshold values.
 * @details Specified threshold values of Ambient 16 Click driver.
 */
#define AMBIENT16_LOW_TH_VALUE              0x0000
#define AMBIENT16_HIGH_TH_VALUE             0xffff

/**
 * @brief Ambient 16 register mask.
 * @details Specified register bit mask of Ambient 16 Click driver.
 */
#define AMBIENT16_REG_MASK                    0x80

void ambient16_cfg_setup ( ambient16_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT16_I2C_SLAVE_ADR_0;
}

err_t ambient16_init ( ambient16_t *ctx, ambient16_cfg_t *cfg ) 
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

err_t ambient16_default_cfg ( ambient16_t *ctx ) 
{
    err_t error_flag = AMBIENT16_OK;
    
    error_flag |= ambient16_sw_reset( ctx );
    
    error_flag |= ambient16_set_reg( ctx, AMBIENT16_CONTROL_REG, AMBIENT16_ADC_ENABLE |
                                                                 AMBIENT16_POWER_ENABLE );
    error_flag |= ambient16_set_reg( ctx, AMBIENT16_INTERRUPT_REG, AMBIENT16_INTERRUPT_DISABLE );
    error_flag |= ambient16_set_th_low( ctx, AMBIENT16_LOW_TH_VALUE );
    error_flag |= ambient16_set_th_high( ctx, AMBIENT16_HIGH_TH_VALUE );
    error_flag |= ambient16_set_gain( ctx, AMBIENT16_X1_GAIN, AMBIENT16_X1_GAIN );
    
    ambient16_set_wait( ctx, AMBIENT16_DISABLE_WAIT );
    
    return error_flag;
}

err_t ambient16_generic_write ( ambient16_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg | AMBIENT16_REG_MASK;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t ambient16_generic_read ( ambient16_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    uint8_t tx_buf;
    tx_buf = reg | AMBIENT16_REG_MASK;

    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &tx_buf, 1, rx_buf, rx_len );

    return error_flag;
}

uint8_t ambient16_get_int_state ( ambient16_t *ctx )
{   
    return digital_in_read( &ctx->int_pin );
}

err_t ambient16_set_reg ( ambient16_t *ctx, uint8_t reg, uint8_t value )
{
    return ambient16_generic_write( ctx, reg, &value, 1 );
}

err_t ambient16_send_cmd ( ambient16_t *ctx, uint8_t cmd )
{
    return i2c_master_write( &ctx->i2c, &cmd, 1 );
}

err_t ambient16_sw_reset ( ambient16_t *ctx )
{
    return ambient16_send_cmd( ctx, AMBIENT16_SOFTWARE_RESET );
}

err_t ambient16_int_reset ( ambient16_t *ctx )
{
    return ambient16_send_cmd( ctx, AMBIENT16_INTERRUPT_RESET );
}

err_t ambient16_set_th_low ( ambient16_t *ctx, uint16_t th_val )
{
    uint8_t tx_buf;
    
    tx_buf = ( uint8_t ) th_val;
    err_t error_flag = ambient16_set_reg( ctx, AMBIENT16_TH_LOW_LSB_REG, tx_buf );
    tx_buf = ( uint8_t ) ( th_val >> 8 );
    error_flag |= ambient16_set_reg( ctx, AMBIENT16_TH_LOW_MSB_REG, tx_buf );
    
    return error_flag;
}

err_t ambient16_set_th_high ( ambient16_t *ctx, uint16_t th_val )
{
    uint8_t tx_buf;
    
    tx_buf = ( uint8_t ) th_val;
    err_t error_flag = ambient16_set_reg( ctx, AMBIENT16_TH_HIGH_LSB_REG, tx_buf );
    tx_buf = ( uint8_t ) ( th_val >> 8 );
    error_flag |= ambient16_set_reg( ctx, AMBIENT16_TH_HIGH_MSB_REG, tx_buf );
    
    return error_flag;
}

err_t ambient16_set_gain ( ambient16_t *ctx, uint8_t data0_gain, uint8_t data1_gain )
{
    uint8_t tx_buf;
    
    tx_buf = ( data0_gain << 2 ) | data1_gain;
    err_t error_flag = ambient16_set_reg( ctx, AMBIENT16_GAIN_REG, tx_buf );
    
    return error_flag;
}

err_t ambient16_get_part_id ( ambient16_t *ctx, uint8_t *part_id )
{
    return ambient16_generic_read( ctx, AMBIENT16_PART_ID_REG, part_id, 1 );
}

err_t ambient16_get_data ( ambient16_t *ctx, uint16_t *data0, uint16_t *data1 )
{
    uint8_t rx_data;
    uint16_t tmp_data;
    
    err_t error_flag = ambient16_generic_read( ctx, AMBIENT16_DATA0_MSB_REG, &rx_data, 1 );
    tmp_data = rx_data;
    tmp_data <<= 8;
    error_flag |= ambient16_generic_read( ctx, AMBIENT16_DATA0_LSB_REG, &rx_data, 1 );
    tmp_data |= rx_data;
    
    *data0 = tmp_data;
    
    error_flag |= ambient16_generic_read( ctx, AMBIENT16_DATA1_MSB_REG, &rx_data, 1 );
    tmp_data = rx_data;
    tmp_data <<= 8;
    error_flag |= ambient16_generic_read( ctx, AMBIENT16_DATA1_LSB_REG, &rx_data, 1 );
    tmp_data |= rx_data;
    
    *data1 = tmp_data;
    
    return error_flag;
}

err_t ambient16_read_data ( ambient16_t *ctx, float *data0, float *data1 )
{
    uint8_t temp_data;
    uint8_t data0_gain;
    uint8_t data1_gain;
    uint16_t data0_val;
    uint16_t data1_val;
    float data0_data;
    float data1_data;
    
    err_t error_flag = ambient16_generic_read( ctx, AMBIENT16_GAIN_REG, &temp_data, 1 );
    
    data1_gain = temp_data & 0x03;
    data0_gain = ( temp_data & 0x0C ) >> 2; 
    
    error_flag |= ambient16_get_data( ctx, &data0_val, &data1_val );
    
    data0_data =  ( ( float ) data0_val ) / 4;
    data1_data =  ( ( float ) data1_val ) * 2;
    
    if ( AMBIENT16_X1_GAIN == data0_gain )
    {
        *data0 = data0_data;
    }
    if ( AMBIENT16_X2_GAIN == data0_gain )
    {
        *data0 = ( data0_data / 2 );
    }
    if ( AMBIENT16_X64_GAIN == data0_gain )
    {
        *data0 = ( data0_data / 64 );
    }
    if ( AMBIENT16_X128_GAIN == data0_gain )
    {
        *data0 = ( data0_data / 128 );
    }

    if ( AMBIENT16_X1_GAIN == data1_gain )
    {
        *data1 = data1_data;
    }
    if ( AMBIENT16_X2_GAIN == data1_gain )
    {
        *data1 = ( data1_data / 2 );
    }
    if ( AMBIENT16_X64_GAIN == data1_gain )
    {
        *data1 = ( data1_data / 64 );
    }
    if ( AMBIENT16_X128_GAIN == data1_gain )
    {
        *data1 = ( data1_data / 128 );
    }
    
    return error_flag;
    
}

void ambient16_set_wait ( ambient16_t *ctx, uint8_t wait_mode )
{
    ambient16_set_reg( ctx, AMBIENT16_WAIT_REG, wait_mode );
}

// ------------------------------------------------------------------------- END
