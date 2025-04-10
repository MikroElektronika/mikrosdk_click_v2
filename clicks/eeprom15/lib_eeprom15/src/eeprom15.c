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
 * @file eeprom15.c
 * @brief EEPROM 15 Click Driver.
 */

#include "eeprom15.h"

void eeprom15_cfg_setup ( eeprom15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wp = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EEPROM15_ADDRESS_A2A1A0_000;
}

err_t eeprom15_init ( eeprom15_t *ctx, eeprom15_cfg_t *cfg ) 
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

err_t eeprom15_write_memory ( eeprom15_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = EEPROM15_OK;
    uint8_t data_buf[ EEPROM15_MEM_PAGE_SIZE + 1 ] = { 0 };
    if ( ( ( ( address & ( ~EEPROM15_MEM_PAGE_BITMASK ) ) + len ) > EEPROM15_MEM_PAGE_SIZE ) || 
         ( NULL == data_in ) )
    {
        error_flag |= EEPROM15_ERROR;
    }

    if ( EEPROM15_OK == error_flag )
    {
        error_flag |= i2c_master_set_slave_address( &ctx->i2c, EEPROM15_REG_RW_EE_MEMORY | ctx->slave_address );
    }
    
    if ( EEPROM15_OK == error_flag )
    {
        data_buf[ 0 ] = address;
        memcpy ( &data_buf[ 1 ], data_in, len );
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, len + 1 );
    }
    return error_flag;
}

err_t eeprom15_read_memory ( eeprom15_t *ctx, uint8_t address, uint8_t *data_out, uint16_t len ) 
{
    err_t error_flag = EEPROM15_OK;
    if ( ( ( ( uint16_t ) address + len ) > EEPROM15_MEM_BANK_SIZE ) || ( NULL == data_out ) )
    {
        error_flag |= EEPROM15_ERROR;
    }

    if ( EEPROM15_OK == error_flag )
    {
        error_flag |= i2c_master_set_slave_address( &ctx->i2c, EEPROM15_REG_RW_EE_MEMORY | ctx->slave_address );
    }
    
    if ( EEPROM15_OK == error_flag )
    {
        error_flag |= i2c_master_write_then_read( &ctx->i2c, &address, 1, data_out, len );
    }
    return error_flag;
}

void eeprom15_set_wp_pin ( eeprom15_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wp, state );
}

err_t eeprom15_select_bank ( eeprom15_t *ctx, uint8_t bank_sel ) 
{
    err_t error_flag = EEPROM15_OK;
    uint8_t data_buf[ 2 ] = { 0 }; 
    if ( bank_sel > EEPROM15_BANK_SEL_1 )
    {
        error_flag |= EEPROM15_ERROR;
    }

    if ( EEPROM15_OK == error_flag )
    {
        if ( bank_sel )
        {
            error_flag |= i2c_master_set_slave_address( &ctx->i2c, EEPROM15_REG_SET_PAGE_ADDR_1 );
        }
        else
        {
            error_flag |= i2c_master_set_slave_address( &ctx->i2c, EEPROM15_REG_SET_PAGE_ADDR_0 );
        }
    }
    
    if ( EEPROM15_OK == error_flag )
    {
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, 2 );
    }
    return error_flag;
}

err_t eeprom15_set_wp_block ( eeprom15_t *ctx, uint8_t block_num ) 
{
    err_t error_flag = EEPROM15_OK;
    uint8_t data_buf[ 2 ] = { 0 }; 
    if ( block_num > EEPROM15_WP_BLOCK_SEL_3 )
    {
        error_flag |= EEPROM15_ERROR;
    }

    if ( EEPROM15_OK == error_flag )
    {
        if ( EEPROM15_WP_BLOCK_SEL_0 == block_num )
        {
            error_flag |= i2c_master_set_slave_address( &ctx->i2c, EEPROM15_REG_RW_WP_BLOCK_0 );
        }
        else if ( EEPROM15_WP_BLOCK_SEL_1 == block_num )
        {
            error_flag |= i2c_master_set_slave_address( &ctx->i2c, EEPROM15_REG_RW_WP_BLOCK_1 );
        }
        else if ( EEPROM15_WP_BLOCK_SEL_2 == block_num )
        {
            error_flag |= i2c_master_set_slave_address( &ctx->i2c, EEPROM15_REG_RW_WP_BLOCK_2 );
        }
        else
        {
            error_flag |= i2c_master_set_slave_address( &ctx->i2c, EEPROM15_REG_RW_WP_BLOCK_3 );
        }
    }
    
    if ( EEPROM15_OK == error_flag )
    {
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, 2 );
    }
    return error_flag;
}

err_t eeprom15_clear_wp ( eeprom15_t *ctx ) 
{
    err_t error_flag = EEPROM15_OK;
    uint8_t data_buf[ 2 ] = { 0 }; 
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, EEPROM15_REG_CLEAR_ALL_WP );
    if ( EEPROM15_OK == error_flag )
    {
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, 2 );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
