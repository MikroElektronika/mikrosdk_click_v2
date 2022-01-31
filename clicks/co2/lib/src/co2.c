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
 * @file co2.c
 * @brief CO2 Click Driver.
 */

#include "co2.h"

/** 
 * @brief Dallas/Maxim calculation for CRC8.
 * @details This function calculates CRC8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x31 (x8 + x5 + x4 +1)
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0x00
 * @li @c  Example CRC(0xBEEF) = 0x92
 * @param[in] data_to_calculate : Word to calculate crc from.
 * @return Calculated CRC
 */
static uint8_t co2_calculate_crc8( uint16_t data_to_calculate );

void co2_cfg_setup ( co2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    
    cfg->i2c_address = CO2_SET_DEV_ADDR_1KOHMS;
}

err_t co2_init ( co2_t *ctx, co2_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    ctx->slave_address = cfg->i2c_address;
    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    ctx->device_id = 0;
    memset( ctx->serial_id, 0, 2 );
    ctx->crc_enabled = 1;
    
    return I2C_MASTER_SUCCESS;
}

err_t co2_default_cfg ( co2_t *ctx ) 
{
    err_t error_flag = CO2_OK;
    uint16_t configuration_data;
    
    error_flag |= co2_reset( ctx );
    
    configuration_data = 0;
    error_flag |= co2_generic_read( ctx, CO2_REG_SELF_TEST, &configuration_data, 1 );
    if ( configuration_data )
    {
        error_flag |= CO2_ERROR_SELF_TEST;
    }
    
    if ( CO2_OK == error_flag )
    {
        configuration_data = CO2_SET_BINARY_GAS_IN_AIR_100PCT;
        error_flag |= co2_generic_write( ctx, CO2_REG_SET_BINARY_GAS, &configuration_data, 1 );
        
        error_flag |= co2_generic_write( ctx, CO2_REG_ENABLE_AUTO_SELF_CALIB, NULL, 0 );
    }
    
    return error_flag;
}

err_t co2_generic_write ( co2_t *ctx, uint16_t reg, uint16_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 64 ] = { 0 };
    uint8_t buf_cnt = 2;

    data_buf[ 0 ] = reg >> 8;
    data_buf[ 1 ] = reg;

    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ )
    {
        data_buf[ buf_cnt++ ] = tx_buf[ cnt ] >> 8;
        data_buf[ buf_cnt++ ] = tx_buf[ cnt ];
        
        if ( ctx->crc_enabled )
        {
            data_buf[ buf_cnt++ ] = co2_calculate_crc8( tx_buf[ cnt ] );
        }
    }
    
    err_t error_flag =  i2c_master_write( &ctx->i2c, data_buf, buf_cnt );
    return error_flag;
}

err_t co2_generic_read ( co2_t *ctx, uint16_t reg, uint16_t *rx_buf, uint8_t rx_len ) 
{
    uint8_t write_reg[ 2 ] = { 0 };
    uint8_t read_buf[ 64 ] = { 0 };
    uint8_t read_len;
    
    if ( ctx->crc_enabled )
    {
        read_len = rx_len * 2 + rx_len;
    }
    else
    {
        read_len = rx_len * 2;
    }
    
    write_reg[ 0 ] = reg >> 8;
    write_reg[ 1 ] = reg;

    err_t error_flag = i2c_master_write( &ctx->i2c, write_reg, 2 );
    Delay_100ms( );
    error_flag |= i2c_master_read( &ctx->i2c, read_buf, read_len );

    if ( CO2_OK == error_flag )
    {
        uint8_t rd_cnt = 0;
        for ( uint8_t cnt = 0; cnt < rx_len; cnt++ )
        {
            rx_buf[ cnt ] = ( uint16_t )read_buf[ rd_cnt++ ] << 8;
            rx_buf[ cnt ] |= read_buf[ rd_cnt++ ];
            
            if ( ctx->crc_enabled )
            {
                if ( read_buf[ rd_cnt ]  != co2_calculate_crc8( rx_buf[ cnt ] ) )
                {
                    error_flag = CO2_ERROR_CRC;
                    break;
                }
                rd_cnt++;
            }
        }
    }
    
    return error_flag;
}

err_t co2_reset ( co2_t *ctx )
{
    uint8_t reset_cmd = 0x06;
    err_t error_flag = CO2_OK;
    
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, 0x00 );
    error_flag |= i2c_master_write( &ctx->i2c, &reset_cmd, 1 );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    
    Delay_100ms( );
    
    return error_flag;
}

err_t co2_get_id ( co2_t *ctx )
{
    uint16_t ids[ 6 ] = { 0 };
    co2_generic_write( ctx, 0x367C, NULL, 0 );
    err_t error_flag = co2_generic_read( ctx, 0xE102, ids, 6 );
    
    if ( CO2_OK == error_flag )
    {
        ctx->device_id = ( ( uint32_t )ids[ 0 ] << 16 ) | ids[ 1 ];
        ctx->serial_id[ 0 ] = ( ( uint32_t )ids[ 2 ] << 16 ) | ids[ 3 ];;
        ctx->serial_id[ 1 ] = ( ( uint32_t )ids[ 4 ] << 16 ) | ids[ 5 ];;
    }
    
    return error_flag;
}

err_t co2_set_reference ( co2_t *ctx, uint16_t humidity, uint16_t pressure )
{
    err_t error_flag = CO2_OK;
    
    uint16_t temp_data = 65535.0 * humidity / 100.0;/*< Constants are from datasheet 
                                                        formula for humidity*/
    error_flag |= co2_generic_write( ctx, CO2_REG_SET_RELATIVE_HUMIDITY, &temp_data, 1 );
    temp_data = pressure;
    error_flag |= co2_generic_write( ctx, CO2_REG_SET_PRESSURE, &temp_data, 1 );
    
    return error_flag;
}

err_t co2_read_gas ( co2_t *ctx, float *gas_concentration, float *temperature )
{
    uint16_t read_data[ 3 ] = { 0 };
    err_t error_flag = CO2_OK;
    
    error_flag = co2_generic_read( ctx, CO2_REG_MEASURE_GAS_CONCENTRATION, read_data, 3 );
    
    if ( CO2_OK == error_flag )
    {
        //Gas calculation
        *gas_concentration = ( read_data[ 0 ] - 16384 ) / 32768.0 * 100;/*< Constants are from datasheet 
                                                                            formula for gas concentration*/
        //Temperature calculation
        *temperature = ( int16_t )read_data[ 1 ] / 200.0;/*< Constants are from datasheet 
                                                            formula for temperature*/
    }
    
    return error_flag;
}

err_t co2_disable_crc ( co2_t *ctx )
{
    ctx->crc_enabled = 0;
    return co2_generic_write( ctx, CO2_REG_DISABLE_CRC, NULL, 0 );
}

static uint8_t co2_calculate_crc8( uint16_t data_to_calculate )
{
    uint8_t crc = 0xFF;
    uint8_t ptr[ 2 ] = { 0 };
    
    ptr[ 0 ] = data_to_calculate >> 8;
    ptr[ 1 ] = data_to_calculate;
    
    for ( uint8_t i = 0; i < 2; i++ ) 
    {
        crc ^= ptr[ i ];
        for ( uint8_t j = 0; j < 8; j++ ) 
        {
            if ( ( crc & 0x80 ) != 0 )
            {
                crc = ( uint8_t )( ( crc << 1 ) ^ 0x31 );
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END
