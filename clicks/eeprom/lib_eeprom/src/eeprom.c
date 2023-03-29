/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file eeprom.c
 *
 */

#include "eeprom.h"


// ------------------------------------------------------------- PRIVATE MACROS

#define EEPROM_DEFAULT_SLAVE_ADDR  0x50

#define EEPROM_WRITE_ENABLE   0
#define EEPROM_WRITE_PROTECT  1

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void eeprom_cfg_setup( eeprom_cfg_t *cfg )
{
    cfg->wp  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->addr_sel = EEPROM_I2C_ADDR_SEL_0;
}

eeprom_retval_t eeprom_init( eeprom_t *ctx, eeprom_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_addr = EEPROM_DEFAULT_SLAVE_ADDR | cfg->addr_sel;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return EEPROM_RETVAL_ERR_DRV_INIT;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_addr );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_out_init( &ctx->wp, cfg->wp );
    digital_out_write( &ctx->wp, EEPROM_WRITE_ENABLE );


    return EEPROM_RETVAL_OK;
}

void eeprom_write_byte( eeprom_t *context, uint8_t reg_addr, uint8_t data_in )
{
    uint8_t buff_data[ 2 ];

    buff_data[ 0 ] = reg_addr;
    buff_data[ 1 ] = data_in;

    i2c_master_write( &context->i2c, buff_data, 2 );
}

void eeprom_write_page( eeprom_t *context, uint8_t reg_addr, uint8_t *data_in )
{
    uint8_t buff_data[ 17 ];
    uint8_t cnt;

    buff_data[ 0 ] = reg_addr;

    for ( cnt = 1; cnt < 17; cnt++ )
    {
        buff_data[ cnt ] = *data_in;
        data_in++;
    }

    i2c_master_write( &context->i2c, buff_data, EEPROM_NBYTES_PAGE + 1 );
    Delay_1sec( );
}

uint8_t eeprom_read_byte( eeprom_t *ctx, uint8_t reg_addr )
{
    uint8_t tmp_data;

    i2c_master_write( &ctx->i2c, &reg_addr, 1 );

    i2c_master_read( &ctx->i2c, &tmp_data, 1 );

    return tmp_data;
}

eeprom_retval_t eeprom_read_sequential( eeprom_t *ctx, uint8_t reg_addr, uint16_t n_bytes, uint8_t *data_out )
{
    uint8_t tmp_data;

    if ( ( n_bytes < EEPROM_NBYTES_MIN ) || ( n_bytes > EEPROM_NBYTES_MAX ) )
    {
        return EEPROM_RETVAL_ERR_NBYTES;
    }

    tmp_data = reg_addr;

    i2c_master_write_then_read( &ctx->i2c, &tmp_data, 1, data_out, n_bytes );

    return EEPROM_RETVAL_OK;
}

void eeprom_write_enable( eeprom_t *context )
{
    digital_out_write( &context->wp, EEPROM_WRITE_ENABLE );
}

void eeprom_write_protect( eeprom_t *context )
{
    digital_out_write( &context->wp, EEPROM_WRITE_PROTECT );
}

// ------------------------------------------------------------------------ END
