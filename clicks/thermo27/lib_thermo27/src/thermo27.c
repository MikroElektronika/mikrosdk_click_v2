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
 * @file thermo27.c
 * @brief Thermo 27 Click Driver.
 */

#include "thermo27.h"


/**
 * @brief Thermo 27 SPI read bit.
 * @details Specified bit that is automatically added to address for SPI read mode
 * needed to calculate CRC data if the CRC is enabled.
 */
#define THERMO27_SPI_READ_BIT       0x01

/** 
 * @brief Reset delay function.
 * @details This function is used for generating delay after reset. 
 * @return Nothing.
 * @note None.
 */
void dev_reset_delay( void );

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x07 (x8 + x2 + x + 1 )
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t calculate_crc8( uint8_t *data_buf, uint8_t len );


void thermo27_cfg_setup ( thermo27_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMO27_DEVICE_ADDRESS;
}

err_t thermo27_init ( thermo27_t *ctx, thermo27_cfg_t *cfg ) 
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
    ctx->crc_mode = THERMO27_CRC_MODE_DISABLED;

    return I2C_MASTER_SUCCESS;
}

err_t thermo27_default_cfg ( thermo27_t *ctx ) 
{
    err_t error_flag = THERMO27_OK;
    
    error_flag = thermo27_sw_reset( ctx );
    dev_reset_delay( );
    error_flag |= thermo27_write_register( ctx, THERMO27_CONFIGURATION_REG, THERMO27_ADC_TIME_1mS_MODE_CMD | 
                                                                           THERMO27_ENABLE_AVG_CMD |    
                                                                           THERMO27_CONTINUOUS_MODE_CMD |       
                                                                           THERMO27_CONVERSION_TIME_1S_MODE_CMD );
    error_flag |= thermo27_set_low_temp_limit( ctx, THERMO27_LOW_TEMP_LIMIT_VAL );
    error_flag |= thermo27_set_low_temp_limit( ctx, THERMO27_HIGH_TEMP_LIMIT_VAL );
    
    return error_flag;
}

err_t thermo27_generic_write ( thermo27_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t thermo27_generic_read ( thermo27_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t thermo27_write_register ( thermo27_t *ctx, uint8_t reg, uint16_t data_in )
{
    err_t error_flag = THERMO27_OK;
    uint8_t reg_data[ 3 ];
    
    if ( THERMO27_CRC_MODE_DISABLED == ctx->crc_mode )
    {
        reg_data[ 0 ] = (uint8_t) (data_in >> 8);
        reg_data[ 1 ] = (uint8_t) (data_in & 0xFF);
        
        error_flag = thermo27_generic_write( ctx, reg, reg_data, 2 );
    }
    else
    {
        uint8_t crc_data[ 4 ];
        
        reg_data[ 0 ] = (uint8_t) (data_in >> 8);
        reg_data[ 1 ] = (uint8_t) (data_in & 0xFF);
        
        crc_data[ 0 ] = THERMO27_DEVICE_ADDRESS << 1;
        crc_data[ 1 ] = reg;
        crc_data[ 2 ] = reg_data[ 0 ];
        crc_data[ 3 ] = reg_data[ 1 ];
        
        reg_data[ 2 ] = calculate_crc8( crc_data, 4 );
        
        error_flag = thermo27_generic_write( ctx, reg, reg_data, 3 );
    }
    
    return error_flag;
}

err_t thermo27_read_register ( thermo27_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = THERMO27_OK;
    uint8_t tx_data[ 3 ];
    uint8_t rx_data[ 3 ];
    uint16_t read_data;
    
    if ( THERMO27_CRC_MODE_DISABLED == ctx->crc_mode )
    {
        error_flag = thermo27_generic_read( ctx, reg, rx_data, 2 );
    
        read_data = rx_data[ 0 ];
        read_data <<= 8;
        read_data |= rx_data[ 1 ];
        *data_out = read_data;
    }
    else
    {
        uint8_t crc_data[ 3 ];
        
        crc_data[ 0 ] = THERMO27_DEVICE_ADDRESS << 1;
        crc_data[ 1 ] = reg;
        
        tx_data[ 0 ] = reg; 
        tx_data[ 1 ] = calculate_crc8( crc_data, 2 );
        
        error_flag = i2c_master_write_then_read( &ctx->i2c, tx_data, 2, rx_data, 3 );
        
        crc_data[ 0 ] = ( THERMO27_DEVICE_ADDRESS << 1 ) | THERMO27_SPI_READ_BIT;
        crc_data[ 1 ] = rx_data[ 0 ];
        crc_data[ 2 ] = rx_data[ 1 ];
        
        if ( rx_data[ 2 ] != calculate_crc8( crc_data, 3 ) )
        {
            return THERMO27_ERROR;
        }
        
        read_data = rx_data[ 0 ];
        read_data <<= 8;
        read_data |= rx_data[ 1 ];
        *data_out = read_data;
    }
    
    return error_flag;
}

err_t thermo27_get_device_id ( thermo27_t *ctx, uint16_t *device_id )
{
    return thermo27_read_register( ctx, THERMO27_DEVICE_ID_REG, device_id );
}

err_t thermo27_sw_reset ( thermo27_t *ctx )
{
    err_t error_flag = THERMO27_OK;
    uint8_t data_in = THERMO27_SW_RESET;
    
    error_flag = i2c_master_set_slave_address( &ctx->i2c, THERMO27_RESET_DEVICE_ADDRESS ); 
    
    error_flag |= i2c_master_write( &ctx->i2c, &data_in, 1 );
    
    if ( THERMO27_OK == error_flag )
    {
        ctx->crc_mode = THERMO27_CRC_MODE_DISABLED;
    }
    
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, THERMO27_DEVICE_ADDRESS );
    
    return error_flag;
}

err_t thermo27_read_temp ( thermo27_t *ctx, float *temp_out )
{
    err_t error_flag = THERMO27_OK;
    uint16_t reg_data;
    float temp;
    
    error_flag = thermo27_read_register( ctx, THERMO27_TEMP_RESULT_REG, &reg_data );
    temp =  ( float ) ( ( int16_t ) reg_data ) *  THERMO27_TEMP_COEF;
    *temp_out = temp;
    
    return error_flag;
}

err_t thermo27_enable_crc ( thermo27_t *ctx )
{
    err_t error_flag = THERMO27_OK;
    uint16_t reg_val;
    
    error_flag = thermo27_read_register( ctx, THERMO27_CONFIGURATION_REG, &reg_val );
    
    reg_val |= THERMO27_ENABLE_CRC_CMD;
    
    error_flag |= thermo27_write_register( ctx, THERMO27_CONFIGURATION_REG, reg_val );
    
    if ( THERMO27_OK == error_flag )
    {
        ctx->crc_mode = THERMO27_CRC_MODE_ENABLED;
    }
    
    return error_flag;
}

err_t thermo27_set_low_temp_limit ( thermo27_t *ctx, float low_temp_limit )
{
    int16_t data_in;
    
    data_in = (int16_t)( low_temp_limit / THERMO27_LSB_VAL );
    data_in <<= 2;
        
    return thermo27_write_register( ctx, THERMO27_TLOW_LIMIT_REG, data_in );
}

err_t thermo27_set_high_temp_limit ( thermo27_t *ctx, float high_temp_limit )
{
    int16_t data_in;
    
    data_in = (int16_t)( high_temp_limit / THERMO27_LSB_VAL );
    data_in <<= 2;
    
    return thermo27_write_register( ctx, THERMO27_THIGH_LIMIT_REG, data_in );
}

err_t thermo27_set_hysteresis ( thermo27_t *ctx, uint8_t thigh_hyst, uint8_t tlow_hyst )
{
    uint16_t data_in;
    
    data_in = thigh_hyst;
    data_in <<= 8;
    data_in |= tlow_hyst;
    
    return thermo27_write_register( ctx, THERMO27_HYSTERESIS_REG, data_in );
}

err_t thermo27_set_slew_limit ( thermo27_t *ctx, float slew_limit )
{
    int16_t data_in;
    
    data_in = (int16_t)( slew_limit / THERMO27_LSB_VAL );
    data_in <<= 2;
    
    return thermo27_write_register( ctx, THERMO27_THIGH_LIMIT_REG, data_in );
}

err_t thermo27_get_alert_reg ( thermo27_t *ctx, uint8_t *register_flags )
{
    err_t error_flag = THERMO27_OK;
    uint16_t reg_data;
    
    error_flag = thermo27_read_register( ctx, THERMO27_ALERT_STATUS_REG, &reg_data );
    *register_flags = ( uint8_t )( reg_data & 0xff );
    
    return error_flag;
}

// ---------------------------  PRIVATE FUNCTIONS  -------------------------

static uint8_t calculate_crc8( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0xFF;
    
    for ( uint8_t cnt_0 = 0; cnt_0 < len; cnt_0++ ) 
    {
        uint8_t in_byte = data_buf[ cnt_0 ];
        crc ^= in_byte;
        for ( uint8_t cnt_1 = 0; cnt_1 < 8; cnt_1++ ) 
        {
            if ( ( crc & 0x80 ) != 0 )
            {
                crc = (uint8_t)( ( crc << 1 ) ^ THERMO27_POLYNOMIAL );
            }
            else 
            {
                crc <<= 1;
            }
        }
    }
    
    return crc;
}

void dev_reset_delay( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
