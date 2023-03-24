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

#include "expand2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void expand2_cfg_setup ( expand2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = EXPAND2_I2C_MODULE_ADDRESS_0;
}

EXPAND2_RETVAL expand2_init ( expand2_t *ctx, expand2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return EXPAND2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return EXPAND2_OK;
}

void expand2_default_cfg ( expand2_t *ctx )
{
    expand2_reset( ctx );

    expand2_set_direction_port_a( ctx, EXPAND2_I2C_MODULE_ADDRESS_0, EXPAND2_PORT_DIRECTION_OUTPUT );

    expand2_set_direction_port_b( ctx, EXPAND2_I2C_MODULE_ADDRESS_0, EXPAND2_PORT_DIRECTION_INPUT );
    
    expand2_set_pull_ups_port_b ( ctx, EXPAND2_I2C_MODULE_ADDRESS_0, 0xFF );
}

void expand2_generic_write ( expand2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void expand2_generic_read ( expand2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void expand2_set_bits ( expand2_t *ctx, uint8_t module_address, uint8_t reg_address, uint8_t bit_mask )
{
    uint8_t temp;
    
    ctx->slave_address = module_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    
    expand2_generic_read( ctx, reg_address, &temp, 1 );
    
    temp |= bit_mask;
    
    expand2_generic_write( ctx, reg_address, &temp, 1 );
}

void expand2_clear_bits ( expand2_t *ctx, uint8_t module_address, uint8_t reg_address, uint8_t bit_mask )
{
    uint8_t temp;

    ctx->slave_address = module_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );

    expand2_generic_read( ctx, reg_address, &temp, 1 );
    
    temp &= ~bit_mask;
    
    expand2_generic_write( ctx, reg_address, &temp, 1 );
}

void expand2_toggle_bits ( expand2_t *ctx, uint8_t module_address, uint8_t reg_address, uint8_t bit_mask )
{
    uint8_t temp;

    ctx->slave_address = module_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    
    expand2_generic_read( ctx, reg_address, &temp, 1 );
    
    temp ^= bit_mask;
    
    expand2_generic_write( ctx, reg_address, &temp, 1 );
}

uint8_t expand2_read_port_a ( expand2_t *ctx, uint8_t module_address )
{
    uint8_t temp;

    ctx->slave_address = module_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );

    expand2_generic_read( ctx, EXPAND2_GPIOA_BANK0, &temp, 1 );

    return temp;
}

uint8_t expand2_read_port_b ( expand2_t *ctx, uint8_t module_address )
{
    uint8_t temp;

    ctx->slave_address = module_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );

    expand2_generic_read( ctx, EXPAND2_GPIOB_BANK0, &temp, 1 );

    return temp;
}

uint16_t expand2_read_both_ports ( expand2_t *ctx, uint8_t module_address )
{
    uint16_t result;
    uint8_t buffer[ 2 ];
    
    buffer[ 0 ] = expand2_read_port_a( ctx, module_address );
    buffer[ 1 ] = expand2_read_port_b( ctx, module_address );
    
    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

void expand2_write_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t write_data )
{
    ctx->slave_address = module_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    expand2_generic_write( ctx, EXPAND2_OLATA_BANK0, &write_data, 1 );
}

void expand2_clear_bit_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask )
{
    expand2_clear_bits( ctx, module_address, EXPAND2_OLATA_BANK0, bit_mask );
}

void expand2_set_bit_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask )
{
    expand2_set_bits( ctx, module_address, EXPAND2_OLATA_BANK0, bit_mask );
}

void expand2_toggle_bit_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask )
{
    expand2_toggle_bits ( ctx, module_address, EXPAND2_OLATA_BANK0, bit_mask );
}

void expand2_write_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t write_data )
{
    ctx->slave_address = module_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    expand2_generic_write( ctx, EXPAND2_OLATB_BANK0, &write_data, 1 );
}

void expand2_clear_bit_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask )
{
    expand2_clear_bits( ctx, module_address, EXPAND2_OLATB_BANK0, bit_mask );
}

void expand2_setBitPortB( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask )
{
    expand2_set_bits( ctx, module_address, EXPAND2_OLATB_BANK0, bit_mask );
}

void expand2_toggle_bit_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask )
{
    expand2_toggle_bits( ctx, module_address, EXPAND2_OLATB_BANK0, bit_mask );
}

void expand2_set_direction_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t write_data )
{
    ctx->slave_address = module_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    expand2_generic_write( ctx, EXPAND2_IODIRA_BANK0, &write_data, 1 );
}

void expand2_set_input_dir_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask )
{
    expand2_set_bits ( ctx, module_address, EXPAND2_IODIRA_BANK0, bit_mask );
}

void expand2_set_output_dir_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask )
{
    expand2_clear_bits( ctx, module_address, EXPAND2_IODIRA_BANK0, bit_mask );
}

void expand2_set_direction_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t write_data )
{
    ctx->slave_address = module_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    expand2_generic_write( ctx, EXPAND2_IODIRB_BANK0, &write_data, 1 );
}

void expand2_set_input_dir_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask )
{
    expand2_set_bits( ctx, module_address, EXPAND2_IODIRB_BANK0, bit_mask );
}

void expand2_set_output_dir_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t bit_mask )
{
    expand2_clear_bits( ctx, module_address, EXPAND2_IODIRB_BANK0, bit_mask );
}

void expand2_set_pull_ups_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t write_data )
{
    ctx->slave_address = module_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    expand2_generic_write( ctx, EXPAND2_GPPUA_BANK0, &write_data, 1 );
}

void expand2_set_pull_ups_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t write_data )
{
    ctx->slave_address = module_address;
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    expand2_generic_write( ctx, EXPAND2_GPPUB_BANK0, &write_data, 1 );
}

void expand2_set_port_a ( expand2_t *ctx, uint8_t module_address, uint8_t position )
{
    uint8_t write_data;
    
    position %= 8;
    
    write_data = 0x01 << position;
    
    expand2_write_port_a( ctx, module_address, write_data );
}

void expand2_set_port_b ( expand2_t *ctx, uint8_t module_address, uint8_t position )
{
    uint8_t write_data;

    position %= 8;

    write_data = 0x01 << position;

    expand2_write_port_b( ctx, module_address, write_data );
}

void expand2_reset( expand2_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_5ms();
    digital_out_low( &ctx->rst );
    Delay_5ms();
    digital_out_high( &ctx->rst );
    Delay_1ms();
}

uint8_t expand2_getInterrupt( expand2_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->int_pin );

    return state;
}

// ------------------------------------------------------------------------- END

