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
 * @file heartrate10.c
 * @brief Heart Rate 10 Click Driver.
 */

#include "heartrate10.h"

void heartrate10_cfg_setup ( heartrate10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HEARTRATE10_SET_DEV_ADDR;
}

err_t heartrate10_init ( heartrate10_t *ctx, heartrate10_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t heartrate10_default_cfg ( heartrate10_t *ctx ) 
{
    //Shutdown device
    heartrate10_generic_write( ctx, HEARTRATE10_REG_MODE_CFG1, 0x80 );
    Delay_1sec( );
    //Reset device
    heartrate10_reset( ctx );
    //Part ID
    uint8_t id_data = 0;
    heartrate10_generic_read( ctx, HEARTRATE10_REG_PART_ID, &id_data );
    if ( HEARTRATE10_PART_ID != id_data )
    {
        return HEARTRATE10_ERROR;
    }
    //Set flex led mode
    heartrate10_generic_write( ctx, HEARTRATE10_REG_MODE_CFG1, 0x03 );
    //Set scale range, sample per second and led pulse widths
    heartrate10_generic_write( ctx, HEARTRATE10_REG_MODE_CFG2, 0x64 );
    //Set led sequences [ IR, RED, GREEN, BLUE ]
    heartrate10_generic_write( ctx, HEARTRATE10_REG_LED_SEQ1, 0x21 );//RED-IR
    heartrate10_generic_write( ctx, HEARTRATE10_REG_LED_SEQ2, 0x43 );//BLUE-GREEN
    //Set led range
    heartrate10_generic_write( ctx, HEARTRATE10_REG_LED_RANGE, 0x00 );
    //Set led power
    heartrate10_generic_write( ctx, HEARTRATE10_REG_LED1_PA, 0xFF );//IR
    heartrate10_generic_write( ctx, HEARTRATE10_REG_LED2_PA, 0xFF );//RED
    heartrate10_generic_write( ctx, HEARTRATE10_REG_LED3_PA, 0xFF );//GREEN
    heartrate10_generic_write( ctx, HEARTRATE10_REG_LED4_PA, 0xFF );//BLUE
    //Enable fifo overflow
    heartrate10_generic_write( ctx, HEARTRATE10_REG_FIFO_CFG, 0x10 );
    //Enable Int on data ready
    heartrate10_generic_write( ctx, HEARTRATE10_REG_INT_ENABLE, 0x40 );
    
    return HEARTRATE10_OK;
}

err_t heartrate10_generic_write ( heartrate10_t *ctx, uint8_t reg, uint8_t tx_data ) 
{
    uint8_t data_buf[ 2 ];

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_data;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t heartrate10_generic_read ( heartrate10_t *ctx, uint8_t reg, uint8_t *rx_data ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_data, 1 );
}

uint8_t heartrate10_get_int_pin ( heartrate10_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void heartrate10_reset ( heartrate10_t *ctx )
{
    heartrate10_generic_write( ctx, HEARTRATE10_REG_MODE_CFG1, 0x40 );
    uint8_t reg_data;
    do {
        heartrate10_generic_read( ctx, HEARTRATE10_REG_INT_STATUS, &reg_data );
        reg_data &= 0x01;
    } while ( reg_data );
}

err_t heartrate10_fifo_read ( heartrate10_t *ctx, uint8_t *rx_buf, uint8_t rx_len )
{
    uint8_t reg = HEARTRATE10_REG_FIFO_DATA;
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

uint32_t heartrate10_read_fifo_sample ( heartrate10_t *ctx )
{
    uint32_t sample;
    uint8_t sample_parts[ 3 ] = { 0 };
    uint8_t fifo_reg = HEARTRATE10_REG_FIFO_DATA;
    heartrate10_fifo_read( ctx, sample_parts, 3 );
    sample = sample_parts[ 2 ] | ( ( uint32_t )sample_parts[ 1 ] << 8 ) | ( ( uint32_t )sample_parts[ 0 ] << 16 );
    sample &= 0x0007FFFF;
    return sample;
}

err_t heartrate10_read_complete_fifo_data ( heartrate10_t *ctx, uint32_t *led1, uint32_t *led2, uint32_t *led3, uint32_t *led4 )
{
    uint8_t sample_parts[ 12 ] = { 0 };
    err_t error_flag = heartrate10_fifo_read( ctx, sample_parts, 12 );
    *led1 = sample_parts[ 2 ] | ( ( uint32_t )sample_parts[ 1 ] << 8 ) | ( ( uint32_t )sample_parts[ 0 ] << 16 );
    *led1 &= 0x0007FFFF;
    *led2 = sample_parts[ 5 ] | ( ( uint32_t )sample_parts[ 4 ] << 8 ) | ( ( uint32_t )sample_parts[ 3 ] << 16 );
    *led2 &= 0x0007FFFF;
    *led3 = sample_parts[ 8 ] | ( ( uint32_t )sample_parts[ 7 ] << 8 ) | ( ( uint32_t )sample_parts[ 6 ] << 16 );
    *led3 &= 0x0007FFFF;
    *led4 = sample_parts[ 11 ] | ( ( uint32_t )sample_parts[ 10 ] << 8 ) | ( ( uint32_t )sample_parts[ 9 ] << 16 );
    *led4 &= 0x0007FFFF;
    return error_flag;
}

// ------------------------------------------------------------------------- END
