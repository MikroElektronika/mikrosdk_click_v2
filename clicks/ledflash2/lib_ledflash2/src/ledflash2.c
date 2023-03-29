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
 * \file
 *
 */

#include "ledflash2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ledflash2_cfg_setup ( ledflash2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->fi   = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->fen = HAL_PIN_NC;
    cfg->ten = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x5A;
}

LEDFLASH2_RETVAL ledflash2_init ( ledflash2_t *ctx, ledflash2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return LEDFLASH2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->fi, cfg->fi );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->fen, cfg->fen );
    digital_out_init( &ctx->ten, cfg->ten );

    return LEDFLASH2_OK;
}

void ledflash2_generic_write ( ledflash2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 ); 
}

void ledflash2_generic_read ( ledflash2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t ledflash2_read_register ( ledflash2_t *ctx, uint8_t reg_address )
{
    uint8_t ret_val;

    ledflash2_generic_read( ctx, reg_address, &ret_val, 1);

    return ret_val;
}

void ledflash2_write_register ( ledflash2_t *ctx, uint8_t reg_address, uint8_t reg_data )
{
    ledflash2_generic_write( ctx, reg_address, &reg_data, 1 );
}

void ledflash2_set_mode ( ledflash2_t *ctx, uint8_t mode, uint8_t intensity, uint8_t flash_duration )
{
    uint8_t write_data;

    if ( mode == LEDFLASH2_MODE_OFF )
    {
        ledflash2_write_register( ctx, 0x00, 0x00 );
        
        digital_out_low( &ctx->fi );
        digital_out_low( &ctx->en );
        digital_out_low( &ctx->fen );
        digital_out_low( &ctx->ten );
    }
    else if ( mode == LEDFLASH2_MODE_FLASH )
    {
        write_data = 0x10;
        write_data |= intensity;
        write_data |= flash_duration;
        ledflash2_write_register( ctx, 0x00, 0x08 );
		ledflash2_write_register( ctx, 0x02, 0x00 );
        ledflash2_write_register( ctx, 0x01, write_data);

        digital_out_low( &ctx->fi );
        digital_out_high( &ctx->en );
        digital_out_high( &ctx->fen );
        digital_out_low( &ctx->ten );
    }
    else if ( mode == LEDFLASH2_MODE_TORCH )
    {
        write_data = 0x10;
        write_data |= intensity;

        ledflash2_write_register( ctx, 0x00, 0x08 );
        ledflash2_write_register( ctx, 0x02, write_data );

        digital_out_low( &ctx->fi );
        digital_out_high( &ctx->en );
        digital_out_low( &ctx->fen );
        digital_out_high( &ctx->ten );
    }
}

void ledflash2_toggle_flash_inhibit ( ledflash2_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->en, pin_state );
}

// ------------------------------------------------------------------------- END

