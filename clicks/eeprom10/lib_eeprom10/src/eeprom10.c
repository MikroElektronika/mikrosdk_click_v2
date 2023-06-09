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
 * @file eeprom10.c
 * @brief EEPROM 10 Click Driver.
 */

#include "eeprom10.h"

void eeprom10_cfg_setup ( eeprom10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wp = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EEPROM10_DEVICE_ADDRESS_0;
}

err_t eeprom10_init ( eeprom10_t *ctx, eeprom10_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

void eeprom10_write_enable( eeprom10_t *ctx )
{
    digital_out_low( &ctx->wp );
}

void eeprom10_write_protect( eeprom10_t *ctx )
{
    digital_out_high( &ctx->wp );
}

err_t eeprom10_write_byte ( eeprom10_t *ctx, uint16_t address, uint8_t data_in )
{
    err_t error_flag = EEPROM10_OK;
    
    if ( EEPROM10_BLOCK_ADDR_END < address )
    {
        error_flag |= EEPROM10_ERROR;
    }    
    else
    {
        uint8_t data_buf[ 3 ] = { 0 };
    
        data_buf[ 0 ] = ( uint8_t ) ( address >> 8 );
        data_buf[ 1 ] = ( uint8_t ) address;
        data_buf[ 2 ] = data_in;
    
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, 3 );
    }
    
    return error_flag;
}

err_t eeprom10_write_page ( eeprom10_t *ctx, uint8_t address, uint8_t *data_in )
{
    err_t error_flag = EEPROM10_OK;
    uint8_t data_buf[ EEPROM10_NBYTES_PAGE + 2 ] = { 0 };
    
    if ( EEPROM10_BLOCK_ADDR_END < ( address + EEPROM10_NBYTES_PAGE ) )
    {
        error_flag |= EEPROM10_ERROR;
    }    
    else
    {
        data_buf[ 0 ] = ( uint8_t ) ( address >> 8 );
        data_buf[ 1 ] = ( uint8_t ) address;
        for ( uint8_t cnt = 0; cnt < EEPROM10_NBYTES_PAGE; cnt++ )
        {
            data_buf[ cnt + 2 ] = data_in[ cnt ];
        }
    
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, EEPROM10_NBYTES_PAGE + 2 );
    }
    
    return error_flag;
}

err_t eeprom10_write_n_byte ( eeprom10_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = EEPROM10_OK;
    uint8_t data_buf[ EEPROM10_NBYTES_PAGE + 2 ] = { 0 };
    
    if ( EEPROM10_NBYTES_PAGE < len )
    { 
        return EEPROM10_ERROR;
    }
    
    if ( EEPROM10_BLOCK_ADDR_END < ( address + len ) )
    {
        error_flag |= EEPROM10_ERROR;
    }    
    else
    {
        data_buf[ 0 ] = ( uint8_t ) ( address >> 8 );
        data_buf[ 1 ] = ( uint8_t ) address;
    
        for ( uint8_t cnt = 0; cnt < len; cnt++ )
        {
            data_buf[ cnt + 2 ] = data_in[ cnt ];
        }
    
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, len + 2 );
    }
    
    return error_flag;
}

err_t eeprom10_read_byte ( eeprom10_t *ctx, uint16_t address, uint8_t *data_out )
{
    err_t error_flag = EEPROM10_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    
    if ( EEPROM10_BLOCK_ADDR_END < address )
    {
        error_flag |= EEPROM10_ERROR;
    }    
    else
    { 
        data_buf[ 0 ] = ( uint8_t ) ( address >> 8 );
        data_buf[ 1 ] = ( uint8_t ) address;
    
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, 2 );
        error_flag |= i2c_master_read( &ctx->i2c, data_out, 1 );
    }
    
    return error_flag;
}

err_t eeprom10_read_page ( eeprom10_t *ctx, uint8_t address, uint8_t *data_out )
{
    err_t error_flag = EEPROM10_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    
    if ( EEPROM10_BLOCK_ADDR_END < ( address + EEPROM10_NBYTES_PAGE ) )
    {
        error_flag |= EEPROM10_ERROR;
    }    
    else
    {
        data_buf[ 0 ] = ( uint8_t ) ( address >> 8 );
        data_buf[ 1 ] = ( uint8_t ) address;
    
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, 2 );
        error_flag |= i2c_master_read( &ctx->i2c, data_out, EEPROM10_NBYTES_PAGE );
    }
    
    return error_flag;
}

err_t eeprom10_read_n_byte ( eeprom10_t *ctx, uint16_t address, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = EEPROM10_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    
    if ( EEPROM10_BLOCK_ADDR_END < ( address + len ) )
    {
        error_flag |= EEPROM10_ERROR;
    }    
    else
    {
        data_buf[ 0 ] = ( uint8_t ) ( address >> 8 );
        data_buf[ 1 ] = ( uint8_t ) address;
    
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, 2 );
        error_flag |= i2c_master_read( &ctx->i2c, data_out, len );
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
