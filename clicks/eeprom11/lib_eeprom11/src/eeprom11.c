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
 * @file eeprom11.c
 * @brief EEPROM 11 Click Driver.
 */

#include "eeprom11.h"

#define EEPROM11_DUMMY             0x00

void eeprom11_cfg_setup ( eeprom11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EEPROM11_DEVICE_ADDRESS_0;
}

err_t eeprom11_init ( eeprom11_t *ctx, eeprom11_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t eeprom11_default_cfg ( eeprom11_t *ctx ) 
{
    err_t error_flag = EEPROM11_OK;
    
    error_flag |= eeprom11_set_page_addr( ctx, EEPROM11_SET_PAGE_ADDR_0 );

    return error_flag;
}

err_t eeprom11_generic_write ( eeprom11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t eeprom11_generic_read ( eeprom11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t eeprom11_page_write ( eeprom11_t *ctx, uint8_t address, uint8_t *data_in )
{
    return eeprom11_generic_write( ctx, address, data_in, 16 );
}

err_t eeprom11_clear_page ( eeprom11_t *ctx, uint8_t address )
{
    uint8_t tmp_data[ 16 ];
    
    for ( uint8_t n_cnt = 0; n_cnt < 16; n_cnt++)
    {
        tmp_data[ n_cnt ] = 0xFF;
    }    
    
    return eeprom11_page_write( ctx, address, tmp_data );
}

err_t eeprom11_set_wp ( eeprom11_t *ctx, uint8_t block_addr )
{
    err_t error_flag = EEPROM11_OK;
    uint8_t tmp_data = 0;
    
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, block_addr ) ) 
    {
        return EEPROM11_ERROR;
    }
    
    error_flag = i2c_master_write( &ctx->i2c, &tmp_data, 1 );
    
    
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return EEPROM11_ERROR;
    }
    
    return error_flag;
}

err_t eeprom11_clear_wp ( eeprom11_t *ctx )
{
    err_t error_flag = EEPROM11_OK;
    uint8_t tmp_data = 0;
    
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, EEPROM11_CLEAR_ALL_WP ) ) 
    {
        return EEPROM11_ERROR;
    }
    
    error_flag = i2c_master_write( &ctx->i2c, &tmp_data, 1 );
    
    
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return EEPROM11_ERROR;
    }
    
    return error_flag;
}

err_t eeprom11_set_page_addr ( eeprom11_t *ctx, uint8_t page_addr )
{
    err_t error_flag = EEPROM11_OK;
    uint8_t tmp_data = 0;
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, page_addr ) ) 
    {
        return EEPROM11_ERROR;
    }
    
    error_flag = i2c_master_write( &ctx->i2c, &tmp_data, 1 );
    
    
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return EEPROM11_ERROR;
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
