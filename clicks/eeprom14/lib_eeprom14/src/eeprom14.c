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
 * @file eeprom14.c
 * @brief EEPROM 14 Click Driver.
 */

#include "eeprom14.h"

void eeprom14_cfg_setup ( eeprom14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wp = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EEPROM14_DEVICE_ADDRESS_A2A1A0_000;
}

err_t eeprom14_init ( eeprom14_t *ctx, eeprom14_cfg_t *cfg ) 
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
    digital_out_low ( &ctx->wp );
    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t eeprom14_write_memory ( eeprom14_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = EEPROM14_OK;
    uint8_t data_buf[ EEPROM14_MEM_PAGE_SIZE + 2 ] = { 0 };
    if ( ( ( address + len - 1 ) > EEPROM14_MEM_ADDR_END ) ||
         ( len > EEPROM14_MEM_PAGE_SIZE ) ||
         ( NULL == data_in ) )
    {
        error_flag = EEPROM14_ERROR;
    }

    if ( EEPROM14_OK == error_flag )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( address & 0xFF );
        memcpy ( &data_buf[ 2 ], data_in, len );
        error_flag = i2c_master_write( &ctx->i2c, data_buf, len + 2 );
    }
    return error_flag;
}

err_t eeprom14_read_memory ( eeprom14_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len ) 
{
    err_t error_flag = EEPROM14_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( ( address + len - 1 ) > EEPROM14_MEM_ADDR_END ) ||
         ( len > EEPROM14_MEM_PAGE_SIZE ) ||
         ( NULL == data_out ) )
    {
        error_flag = EEPROM14_ERROR;
    }

    if ( EEPROM14_OK == error_flag )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( address & 0xFF );
        error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    }
    if ( EEPROM14_OK == error_flag )
    {
        error_flag = i2c_master_read( &ctx->i2c, data_out, len );
    }
    return error_flag;
}

void eeprom14_write_enable ( eeprom14_t *ctx )
{
    digital_out_low ( &ctx->wp );
}

void eeprom14_write_protect ( eeprom14_t *ctx )
{
    digital_out_high ( &ctx->wp );
}

// ------------------------------------------------------------------------- END
