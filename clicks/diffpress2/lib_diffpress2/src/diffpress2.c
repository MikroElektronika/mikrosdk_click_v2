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
 * @file diffpress2.c
 * @brief Diff Press 2 Click Driver.
 */

#include "diffpress2.h"

/**
 * @brief Diff Press 2 crc constants.
 * @details Specified constants for crc of Diff Press 2 Click driver.
 */
#define DIFFPRESS2_POLYNOM  0x31
#define DIFFPRESS2_INIT_VAL 0xFF

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
static uint8_t diffpress2_calculate_crc8 ( uint16_t data_to_calculate );

void diffpress2_cfg_setup ( diffpress2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DIFFPRESS2_SET_DEV_ADDR;
}

err_t diffpress2_init ( diffpress2_t *ctx, diffpress2_cfg_t *cfg ) 
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

    if ( I2C_MASTER_ERROR == i2c_master_set_timeout( &ctx->i2c, 0 ) ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t diffpress2_default_cfg ( diffpress2_t *ctx ) 
{
    err_t ret_val = DIFFPRESS2_ERROR;
    
    do
    {
        if ( diffpress2_reset( ctx ) )
        {
            break;
        }
        
        if ( diffpress2_get_id( ctx ) )
        {
            break;
        }
            
        ret_val = DIFFPRESS2_OK;
        
    } while( 0 );
    
    return ret_val;
}

err_t diffpress2_send_command ( diffpress2_t *ctx, uint16_t cmd ) 
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = cmd >> 8;
    data_buf[ 1 ] = cmd;
    
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t diffpress2_generic_read ( diffpress2_t *ctx, uint16_t cmd, uint16_t *rx_buf, uint8_t rx_len )
{
    uint8_t write_reg[ 2 ] = { 0 };
    uint8_t read_buf[ 0xFF ] = { 0 };
    uint8_t read_len;
    
    read_len = rx_len * 2 + rx_len;
    
    write_reg[ 0 ] = cmd >> 8;
    write_reg[ 1 ] = cmd;

    err_t error_flag = i2c_master_write( &ctx->i2c, write_reg, 2 );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    error_flag |= i2c_master_read( &ctx->i2c, read_buf, read_len );

    if ( DIFFPRESS2_OK == error_flag )
    {
        uint8_t rd_cnt = 0;
        for ( uint8_t cnt = 0; cnt < rx_len; cnt++ )
        {
            rx_buf[ cnt ] = ( uint16_t )read_buf[ rd_cnt++ ] << 8;
            rx_buf[ cnt ] |= read_buf[ rd_cnt++ ];
            
            if ( read_buf[ rd_cnt ]  != diffpress2_calculate_crc8( rx_buf[ cnt ] ) )
            {
                error_flag = DIFFPRESS2_ERROR;
                break;
            }
            rd_cnt++;
        }
    }
    
    return error_flag;
}

err_t diffpress2_raw_read ( diffpress2_t *ctx, uint16_t *rx_buf, uint8_t rx_len )
{
    uint8_t read_buf[ 0xFF ] = { 0 };
    uint8_t read_len;
    
    read_len = rx_len * 2 + rx_len;

    err_t error_flag = i2c_master_read( &ctx->i2c, read_buf, read_len );

    if ( DIFFPRESS2_OK == error_flag )
    {
        uint8_t rd_cnt = 0;
        for ( uint8_t cnt = 0; cnt < rx_len; cnt++ )
        {
            rx_buf[ cnt ] = ( uint16_t )read_buf[ rd_cnt++ ] << 8;
            rx_buf[ cnt ] |= read_buf[ rd_cnt++ ];
            
            if ( read_buf[ rd_cnt ]  != diffpress2_calculate_crc8( rx_buf[ cnt ] ) )
            {
                error_flag = DIFFPRESS2_ERROR;
                break;
            }
            rd_cnt++;
        }
    }
    
    return error_flag;
}

err_t diffpress2_get_id ( diffpress2_t *ctx )
{
    uint16_t ids[ 6 ] = { 0 };
    err_t error_flag = diffpress2_send_command( ctx, DIFFPRESS2_CMD_PRODUCT_ID_PT1 );
    error_flag |= diffpress2_generic_read( ctx, DIFFPRESS2_CMD_PRODUCT_ID_PT2, ids, 6 );
    
    if ( DIFFPRESS2_OK == error_flag )
    {
        ctx->product_id = ( ( uint32_t )ids[ 0 ] << 16 ) | ids[ 1 ];
        ctx->serial_id[ 0 ] = ( ( uint32_t )ids[ 2 ] << 16 ) | ids[ 3 ];;
        ctx->serial_id[ 1 ] = ( ( uint32_t )ids[ 4 ] << 16 ) | ids[ 5 ];;
    }
    
    if ( DIFFPRESS2_PRODUCT_ID != ctx->product_id )
    {
        error_flag = DIFFPRESS2_ERROR;
    }
    
    return error_flag;
}

err_t diffpress2_reset ( diffpress2_t *ctx )
{
    uint8_t reset_cmd = 0x06;/*< Reset command*/
    err_t error_flag;
    
    error_flag = i2c_master_set_slave_address( &ctx->i2c, 0x00 );/*< Reset I2C address*/
    error_flag |= i2c_master_write( &ctx->i2c, &reset_cmd, 1 );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    
    Delay_10ms( );
    Delay_10ms( );
    
    return error_flag;
}

err_t diffpress2_trigger_measurement ( diffpress2_t *ctx, uint16_t trigger_type, 
                                       float *diff_press, float *temperature )
{
    err_t ret_val = DIFFPRESS2_ERROR;
    *diff_press = 0;
    *temperature = 0;
    
    do
    {
        if ( ( DIFFPRESS2_CMD_TRIGGER_MEAS_MASS_FLOW != trigger_type ) && 
             ( DIFFPRESS2_CMD_TRIGGER_MEAS_MASS_FLOW_STRETCH != trigger_type ) && 
             ( DIFFPRESS2_CMD_TRIGGER_MEAS_DIFF_PRESS != trigger_type ) && 
             ( DIFFPRESS2_CMD_TRIGGER_MEAS_DIFF_PRESS_STRETCH != trigger_type ) )
        {
            break;
        }
        
        int16_t raw_data[ 3 ] = { 0 };
        ret_val = diffpress2_generic_read( ctx, DIFFPRESS2_CMD_TRIGGER_MEAS_MASS_FLOW, raw_data, 3 );
        
        if ( ret_val )
        {
            break;
        }
        
        *diff_press = ( float )raw_data[ 0 ] / DIFFPRESS2_PRESSURE_SCALE_FACOTR;
        *temperature = ( float )raw_data[ 1 ] / DIFFPRESS2_TEMPERATURE_SCALE_FACOTR;
    
    } while ( 0 );
    
    
    return ret_val;
}

static uint8_t diffpress2_calculate_crc8 ( uint16_t data_to_calculate )
{
    uint8_t crc = DIFFPRESS2_INIT_VAL;
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
                crc = ( uint8_t )( ( crc << 1 ) ^ DIFFPRESS2_POLYNOM );
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
