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
 * @file fram5.c
 * @brief FRAM 5 Click Driver.
 */

#include "fram5.h"

void fram5_cfg_setup ( fram5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wp = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = FRAM5_DEVICE_ADDRESS_A2A1_00;
}

err_t fram5_init ( fram5_t *ctx, fram5_cfg_t *cfg ) 
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

    digital_out_init( &ctx->wp, cfg->wp );
    
    fram5_write_protect ( ctx );

    return I2C_MASTER_SUCCESS;
}

err_t fram5_memory_write ( fram5_t *ctx, uint32_t address, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 257 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t )( ( address >> 8 ) & 0xFF ); 
    data_buf[ 1 ] = ( uint8_t ) ( address & 0xFF );
    memcpy ( &data_buf[ 2 ], data_in, len );
    fram5_write_enable ( ctx );
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address | ( uint8_t ) ( ( address >> 16 ) & 0x01 ) );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, len + 2 );
    fram5_write_protect ( ctx );
    return error_flag;
}

err_t fram5_memory_read ( fram5_t *ctx, uint32_t address, uint8_t *data_out, uint8_t len )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t )( ( address >> 8 ) & 0xFF ); 
    data_buf[ 1 ] = ( uint8_t ) ( address & 0xFF );
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address | ( uint8_t ) ( ( address >> 16 ) & 0x01 ) );
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, data_buf, 2, data_out, len );
    return error_flag;
}

err_t fram5_check_communication ( fram5_t *ctx )
{
    i2c_master_set_slave_address( &ctx->i2c, FRAM5_SLAVE_ID );
    uint8_t data_buf[ 3 ];
    uint8_t slave_address = ctx->slave_address << 1;
    if ( FRAM5_OK == i2c_master_write_then_read( &ctx->i2c, &slave_address, 1, data_buf, 3 ) )
    {
        if ( FRAM5_MANUFACTURER_ID_DENSITY == data_buf[ 1 ] )
        {
            i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
            return FRAM5_OK;
        }
    }
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    return FRAM5_ERROR;
}

void fram5_write_protect ( fram5_t *ctx )
{
    digital_out_high ( &ctx->wp );
}

void fram5_write_enable ( fram5_t *ctx )
{
    digital_out_low ( &ctx->wp );
}

// ------------------------------------------------------------------------- END
