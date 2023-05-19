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

#include "capsense.h"
// ------------------------------------------------ VARIABLES

static void cfg_delay_ms ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void capsense_cfg_setup ( capsense_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->an  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = CAPSENSE_I2C_ADDRESS_0;
}

err_t capsense_init ( capsense_t *ctx, capsense_cfg_t *cfg )
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
    
    if ( I2C_MASTER_ERROR == i2c_master_set_timeout( &ctx->i2c, 0 ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    // Output pins 
    digital_out_init( &ctx->an, cfg->an );

    // Input pins
    digital_in_init( &ctx->rst, cfg->rst );
    
    return CAPSENSE_OK;
}

err_t capsense_default_cfg ( capsense_t *ctx )
{
    err_t error_flag = CAPSENSE_OK;
    // Enable pins on B0,B1 and slider as CapSense
    error_flag |= capsense_write_data( ctx, CAPSENSE_COMMAND_REG, 0x08 );
    // Five pins will be used for Slider pads
    error_flag |= capsense_write_data( ctx, CAPSENSE_CS_ENABL1, 0x1F );     
    // Two pins will be used for Button pads
    error_flag |= capsense_write_data( ctx, CAPSENSE_CS_ENABL0, 0x18 );     
    // Three pins will be used as GPIO 2 for LED and 1 as GPIO2
    error_flag |= capsense_write_data( ctx, CAPSENSE_GPIO_ENABLE0, 0x03 );  
    // Enables strong drive mode for GPIOs
    error_flag |= capsense_write_data( ctx, CAPSENSE_DM_STRONG0, 0x03 );    
    // Enable slider
    error_flag |= capsense_write_data( ctx, CAPSENSE_CS_SLID_CONFIG, 0x01 );
    // Configure slider resolution
    error_flag |= capsense_write_data( ctx, CAPSENSE_CS_SLID_MULM, 0x10 );  
    error_flag |= capsense_write_data( ctx, CAPSENSE_CS_SLID_MULL, 0x00 );  

    // Store Current Configuration to NVM
    error_flag |= capsense_write_data( ctx, CAPSENSE_COMMAND_REG, 0x01 );   
    Delay_100ms ( );
    Delay_100ms ( );
    // Reconfigure Device (POR)
    error_flag |= capsense_write_data( ctx, CAPSENSE_COMMAND_REG, 0x06 );   
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    error_flag |= capsense_write_data( ctx, CAPSENSE_OUTPUT_PORT0, 0x03 );
    Delay_100ms ( );
    return error_flag;
}

err_t capsense_generic_write ( capsense_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

err_t capsense_generic_read ( capsense_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

err_t capsense_write_data( capsense_t *ctx, uint8_t reg_address, uint8_t write_command )
{
    return capsense_generic_write( ctx, reg_address, &write_command, 1 );
}

err_t capsense_read_data( capsense_t *ctx, uint8_t reg_address, uint8_t *read_data )
{
    return capsense_generic_read ( ctx, reg_address, read_data, 1 );
}

err_t capsense_read_data_bytes( capsense_t *ctx, uint8_t reg_address, uint16_t *read_data )
{
    err_t error_flag = CAPSENSE_OK;
    uint16_t result = 0;
    uint8_t write_bytes[ 2 ] = { 0 };
    uint8_t read_bytes[ 2 ] = { 0 };

    write_bytes[ 0 ] = reg_address;
    write_bytes[ 1 ] = reg_address;

    error_flag |= i2c_master_write ( &ctx->i2c, write_bytes, 2 );
    error_flag |= i2c_master_read ( &ctx->i2c, read_bytes, 2 );

    result = read_bytes[ 0 ];
    result <<= 8;
    result |= read_bytes[ 1 ];
    *read_data = result;
    
    return error_flag;
}

err_t capsense_get_slider_lvl( capsense_t *ctx, uint8_t *slider_lvl )
{
    err_t error_flag = CAPSENSE_OK;
    uint16_t tmp_slider_lvl = 0;

    error_flag |= capsense_read_data_bytes( ctx, CAPSENSE_CS_READ_RAW, &tmp_slider_lvl );

    if ( tmp_slider_lvl < 32 && tmp_slider_lvl > 0 )
    {
        *slider_lvl = ( uint8_t ) tmp_slider_lvl;
    }
    else
    {
        *slider_lvl = 0;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END

