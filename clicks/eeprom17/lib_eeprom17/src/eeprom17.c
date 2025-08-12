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
 * @file eeprom17.c
 * @brief EEPROM 17 Click Driver.
 */

#include "eeprom17.h"

void eeprom17_cfg_setup ( eeprom17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wc = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EEPROM17_DEVICE_ADDRESS_1;
}

err_t eeprom17_init ( eeprom17_t *ctx, eeprom17_cfg_t *cfg ) 
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

    digital_out_init( &ctx->wc, cfg->wc );
    digital_out_low ( &ctx->wc );
    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t eeprom17_write_memory ( eeprom17_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = EEPROM17_OK;
    uint8_t data_buf[ EEPROM17_MEM_PAGE_SIZE + 1 ] = { 0 };
    if ( ( ( ( address & ( ~EEPROM17_MEM_PAGE_BITMASK ) ) + len ) > EEPROM17_MEM_PAGE_SIZE ) || 
         ( NULL == data_in ) )
    {
        error_flag |= EEPROM17_ERROR;
    }

    if ( EEPROM17_OK == error_flag )
    {
        data_buf[ 0 ] = address;
        memcpy ( &data_buf[ 1 ], data_in, len );
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, len + 1 );
    }
    return error_flag;
}

err_t eeprom17_read_memory ( eeprom17_t *ctx, uint8_t address, uint8_t *data_out, uint16_t len ) 
{
    err_t error_flag = EEPROM17_OK;
    if ( ( ( ( uint16_t ) address + len ) > EEPROM17_MEM_BANK_SIZE ) || ( NULL == data_out ) )
    {
        error_flag |= EEPROM17_ERROR;
    }

    if ( EEPROM17_OK == error_flag )
    {
        error_flag |= i2c_master_write_then_read( &ctx->i2c, &address, 1, data_out, len );
    }
    return error_flag;
}

void eeprom17_set_wc_pin ( eeprom17_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wc, state );
}

err_t eeprom17_select_bank ( eeprom17_t *ctx, uint8_t bank_sel ) 
{
    err_t error_flag = EEPROM17_OK;
    if ( bank_sel > EEPROM17_BANK_SEL_1 )
    {
        error_flag |= EEPROM17_ERROR;
    }

    if ( EEPROM17_OK == error_flag )
    {
        error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address | bank_sel );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
