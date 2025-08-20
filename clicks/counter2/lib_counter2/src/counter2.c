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
 * @file counter2.c
 * @brief Counter 2 Click Driver.
 */

#include "counter2.h"

void counter2_cfg_setup ( counter2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->loop = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COUNTER2_DEVICE_ADDRESS;
}

err_t counter2_init ( counter2_t *ctx, counter2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->loop, cfg->loop );

    return I2C_MASTER_SUCCESS;
}

void counter2_set_rst_pin ( counter2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void counter2_reset_counter ( counter2_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_1ms ( );
    counter2_check_loop ( ctx );
    Delay_1ms ( );
    digital_out_high ( &ctx->rst );
}

uint8_t counter2_get_loop_pin ( counter2_t *ctx )
{
    return digital_in_read ( &ctx->loop );
}

uint8_t counter2_check_loop ( counter2_t *ctx )
{
    static uint8_t old_loop = COUNTER2_LOOP_IDLE;
    uint8_t loop = digital_in_read ( &ctx->loop );
    if ( old_loop != loop )
    {
        old_loop = loop;
        return COUNTER2_LOOP_TOGGLED;
    }
    return COUNTER2_LOOP_IDLE;
}

err_t counter2_get_counter ( counter2_t *ctx, uint32_t *counter )
{
    err_t error_flag = COUNTER2_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    if ( NULL == counter )
    {
        return COUNTER2_ERROR;
    }
    error_flag = i2c_master_read ( &ctx->i2c, data_buf, 3 );
    if ( COUNTER2_OK == error_flag )
    {
        *counter = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    }
    return error_flag;
}

err_t counter2_read_free_data ( counter2_t *ctx, uint32_t *free_data )
{
    err_t error_flag = COUNTER2_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    if ( NULL == free_data )
    {
        return COUNTER2_ERROR;
    }
    data_buf[ 0 ] = COUNTER2_FREE_DATA_READ;
    error_flag = i2c_master_write_then_read ( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 1 ], 3 );
    if ( COUNTER2_OK == error_flag )
    {
        *free_data = ( ( uint32_t ) data_buf[ 1 ] << 13 ) | ( ( uint16_t ) data_buf[ 2 ] << 5 ) | ( data_buf[ 3 ] >> 3 );
    }
    return error_flag;
}

err_t counter2_write_free_data ( counter2_t *ctx, uint32_t free_data )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = COUNTER2_FREE_DATA_WRITE;
    data_buf[ 1 ] = ( uint8_t ) ( ( free_data >> 13 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( free_data >> 5 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( free_data << 3 ) & 0xF8 );
    return i2c_master_write ( &ctx->i2c, data_buf, 4 );
}

err_t counter2_sw_reset_counter ( counter2_t *ctx )
{
    err_t error_flag = COUNTER2_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    uint32_t free_data = 0;
    error_flag |= counter2_read_free_data ( ctx, &free_data );
    if ( COUNTER2_OK == error_flag )
    {
        data_buf[ 0 ] = COUNTER2_FREE_DATA_WRITE;
        data_buf[ 1 ] = ( uint8_t ) ( ( free_data >> 13 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( ( free_data >> 5 ) & 0xFF );
        data_buf[ 3 ] = ( uint8_t ) ( ( free_data << 3 ) & 0xF8 ) | COUNTER2_FREE_DATA_RESET_CNT;
        error_flag |= i2c_master_write ( &ctx->i2c, data_buf, 4 );
        counter2_check_loop ( ctx );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
