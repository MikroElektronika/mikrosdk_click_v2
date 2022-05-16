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
 * @file adc16.c
 * @brief ADC 16 Click Driver.
 */

#include "adc16.h"

void adc16_cfg_setup ( adc16_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rdy = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ADC16_DEV_ADDR_R1_0_R2_DNP;
}

err_t adc16_init ( adc16_t *ctx, adc16_cfg_t *cfg ) 
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

    digital_in_init( &ctx->rdy, cfg->rdy );
    digital_in_init( &ctx->alr, cfg->alr );

    return I2C_MASTER_SUCCESS;
}

err_t adc16_default_cfg ( adc16_t *ctx ) 
{
    err_t error_flag = ADC16_OK;
    
    error_flag |= adc16_single_register_write ( ctx, ADC16_REG_WKEY, ADC16_WKEY_UNLOCK );
    error_flag |= adc16_single_register_write ( ctx, ADC16_REG_DEVICE_RESET, ADC16_DEVICE_RESET );
    Delay_100ms ( );
    error_flag |= adc16_single_register_write ( ctx, ADC16_REG_OFFSET_CAL, ADC16_START_CALIBRATION );
    error_flag |= adc16_single_register_write ( ctx, ADC16_REG_WKEY, ADC16_WKEY_LOCK );
    error_flag |= adc16_single_register_write ( ctx, ADC16_REG_CH_INPUT_CFG, ADC16_CH_CFG_TWO_CH_SINGLE_END );
    error_flag |= adc16_single_register_write ( ctx, ADC16_REG_OPMODE_SEL, ADC16_OPMODE_SEL_MAN_WITH_AUTO_SEQ );
    error_flag |= adc16_single_register_write ( ctx, ADC16_REG_AUTO_SEQ_CHEN, ADC16_AUTOSEQ_EN_BOTH_CH );
    
    return error_flag;
}

err_t adc16_single_register_write ( adc16_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 3 ] = { ADC16_OPCODE_SINGLE_WRITE, reg, data_in };
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t adc16_single_register_read ( adc16_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t data_buf[ 2 ] = { ADC16_OPCODE_SINGLE_READ, reg };
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 2, data_out, 1 );
}

err_t adc16_set_register_bits ( adc16_t *ctx, uint8_t reg, uint8_t bit_mask )
{
    uint8_t data_buf[ 3 ] = { ADC16_OPCODE_SET_BIT, reg, bit_mask };
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t adc16_clear_register_bits ( adc16_t *ctx, uint8_t reg, uint8_t bit_mask )
{
    uint8_t data_buf[ 3 ] = { ADC16_OPCODE_CLEAR_BIT, reg, bit_mask };
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t adc16_continuous_register_write ( adc16_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len )
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = ADC16_OPCODE_CONTINUOUS_WRITE;
    data_buf[ 1 ] = reg;

    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ )
    {
        data_buf[ cnt + 2 ] = tx_buf[ cnt ];
    }
    
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 2 );
}

err_t adc16_continuous_register_read ( adc16_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len )
{
    uint8_t data_buf[ 2 ] = { ADC16_OPCODE_CONTINUOUS_READ, reg };
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 2, rx_buf, rx_len );
}

uint8_t adc16_get_rdy_pin ( adc16_t *ctx )
{
    return digital_in_read ( &ctx->rdy );
}

uint8_t adc16_get_alr_pin ( adc16_t *ctx )
{
    return digital_in_read ( &ctx->alr );
}

err_t adc16_get_voltage ( adc16_t *ctx, float *ain0_voltage, float *ain1_voltage )
{
    uint8_t rx_buf[ 4 ];
    int16_t ain0_raw_adc, ain1_raw_adc;
    err_t error_flag = ADC16_OK;
    error_flag |= adc16_single_register_write ( ctx, ADC16_REG_START_SEQUENCE, ADC16_START_SEQUENCE );
    error_flag |= i2c_master_read( &ctx->i2c, rx_buf, 4 );
    error_flag |= adc16_single_register_write ( ctx, ADC16_REG_ABORT_SEQUENCE, ADC16_ABORT_SEQUENCE );
    
    ain0_raw_adc = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
    ain0_raw_adc = ( ain0_raw_adc >> 4 ) & ADC16_RESOLUTION;
    *ain0_voltage = ( ( float ) ain0_raw_adc / ADC16_RESOLUTION ) * ADC16_VREF;
    
    ain1_raw_adc = ( ( uint16_t ) rx_buf[ 2 ] << 8 ) | rx_buf[ 3 ];
    ain1_raw_adc = ( ain1_raw_adc >> 4 ) & ADC16_RESOLUTION;
    *ain1_voltage = ( ( float ) ain1_raw_adc / ADC16_RESOLUTION ) * ADC16_VREF;
    return error_flag;
    
}

// ------------------------------------------------------------------------- END
