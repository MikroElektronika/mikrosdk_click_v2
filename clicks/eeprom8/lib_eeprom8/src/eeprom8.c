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
 * @file eeprom8.c
 * @brief EEPROM 8 Click Driver.
 */

#include "eeprom8.h"

void eeprom8_cfg_setup( eeprom8_cfg_t *cfg )
{
    cfg->wp  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = EEPROM_I2C_ADDR_SEL_0;
}

err_t eeprom8_init( eeprom8_t *ctx, eeprom8_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = EEPROM8_SET_DEV_ADDR | cfg->i2c_address;

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
    
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_init( &ctx->wp, cfg->wp ) )
    {
        return DIGITAL_OUT_UNSUPPORTED_PIN;
    }

    digital_out_low( &ctx->wp );

    return I2C_MASTER_SUCCESS;
}

err_t eeprom8_write_byte( eeprom8_t *ctx, uint16_t reg_addr, uint8_t data_in )
{
    uint8_t buff_data[ 3 ];
    err_t error_flag = EEPROM8_ERROR;

    buff_data[ 0 ] = reg_addr >> 8;
    buff_data[ 1 ] = reg_addr & 0x00FF;
    buff_data[ 2 ] = data_in;
    
    error_flag = i2c_master_write( &ctx->i2c, buff_data, 3 );
    
    return error_flag;
}

err_t eeprom8_write_page( eeprom8_t *ctx, uint16_t reg_addr, uint8_t *data_in )
{
    uint8_t buff_data[ EEPROM8_NBYTES_PAGE + 2 ];
    uint8_t cnt;
    err_t error_flag = EEPROM8_ERROR;
    
    if ( NULL == data_in )
    {
        return error_flag;
    }

    buff_data[ 0 ] = reg_addr >> 8;
	buff_data[ 1 ] = reg_addr & 0x00FF;

    for ( cnt = 2; cnt < EEPROM8_NBYTES_PAGE + 2; cnt++ )
    {
        buff_data[ cnt ] = *data_in;
        data_in++;
    }

    error_flag = i2c_master_write( &ctx->i2c, buff_data, EEPROM8_NBYTES_PAGE + 2 );
    Delay_1sec( );
    
    return error_flag;
}

err_t eeprom8_read_random_byte( eeprom8_t *ctx, uint16_t reg_addr, uint8_t *data_out )
{
    uint8_t write_data[ 2 ];
    err_t error_flag = EEPROM8_ERROR;
    
    write_data[ 0 ] = reg_addr >> 8;
    write_data[ 1 ] = reg_addr & 0x00FF;
    
    error_flag = i2c_master_write_then_read( &ctx->i2c, write_data, 2, data_out, 1 );

    return error_flag;
}

err_t eeprom8_read_current_byte( eeprom8_t *ctx, uint8_t *data_out )
{
    err_t error_flag = EEPROM8_ERROR;
    
    if ( NULL == data_out )
    {
        return error_flag;
    }
    
    error_flag = i2c_master_read( &ctx->i2c, data_out, 1 );

    return error_flag;
}

err_t eeprom8_read_sequential( eeprom8_t *ctx, uint16_t reg_addr, uint16_t n_bytes, uint8_t *data_out )
{
    uint8_t tmp_data[ 2 ];
    err_t error_flag = EEPROM8_ERROR;
    
    if ( 0 == n_bytes )
    {
        return error_flag;
    }
    
    if ( NULL == data_out )
    {
        return error_flag;
    }
    
    tmp_data[ 0 ] = reg_addr >> 8;
    tmp_data[ 1 ] = reg_addr & 0x00FF;
        
    error_flag = i2c_master_write_then_read( &ctx->i2c, tmp_data, 2, data_out, n_bytes );

    return error_flag;
}

void eeprom8_write_enable( eeprom8_t *ctx )
{
    digital_out_low( &ctx->wp );
}

void eeprom8_write_protect( eeprom8_t *ctx )
{
    digital_out_high( &ctx->wp );
}

// ------------------------------------------------------------------------- END
