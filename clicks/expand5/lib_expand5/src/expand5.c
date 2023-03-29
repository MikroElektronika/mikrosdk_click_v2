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

#include "expand5.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void expand5_cfg_setup ( expand5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = EXPAND5_I2C_ADR_GND;
}

EXPAND5_RETVAL expand5_init ( expand5_t *ctx, expand5_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return EXPAND5_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );

    return EXPAND5_OK;
} 

void expand5_generic_write ( expand5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void expand5_generic_read ( expand5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t expand5_read_bit ( expand5_t *ctx, uint8_t reg_adr, uint8_t bit_num )
{
    uint8_t bit_chk;
    uint8_t res;

    expand5_generic_read( ctx, reg_adr, &bit_chk, 1 );
    res = bit_chk & ( 1 << bit_num );

    return res;
}

void expand5_write_bit ( expand5_t *ctx, uint8_t reg_adr, uint8_t bit_num, uint8_t pin_val )
{
    uint8_t bit_chk;
    
    expand5_generic_read( ctx, reg_adr, &bit_chk, 1 );
    bit_chk = ( pin_val != 0 ) ? ( bit_chk | ( 1 << bit_num ) ) : ( bit_chk & ~( 1 << bit_num ) );

    expand5_generic_write( ctx, reg_adr, &bit_chk, 1 );
}

// Get a single INPUT pin's logic level
uint8_t expand5_read_pin ( expand5_t *ctx, uint16_t pin )
{
    uint8_t buf;
    
    buf = expand5_read_bit( ctx, ( EXPAND5_RA_IN_0 + ( pin / 8 ) ), ( pin % 8 ) );
    
    return buf;
}

// Get all pin logic levels from one bank
uint8_t expand5_read_bank ( expand5_t *ctx, uint8_t bank )
{
    uint8_t buf;
    
    expand5_generic_read( ctx, EXPAND5_RA_IN_0 + bank, &buf, 1 );
    
    return buf;
}

// Get all pin logic levels from all banks
void expand5_read_all_banks ( expand5_t *ctx, uint8_t *bank0, uint8_t *bank1, uint8_t *bank2 )
{
    uint8_t buf[ 3 ];
    
    expand5_generic_read( ctx, EXPAND5_RA_IN_0, buf , 3 );
    
    *bank0 = buf[ 0 ];
    *bank1 = buf[ 1 ];
    *bank2 = buf[ 2 ];
}

// Get a single OUTPUT pin's setting
uint8_t expand5_get_pin_out_lvl ( expand5_t *ctx, uint16_t pin )
{
    uint8_t buf;

    buf = expand5_read_bit( ctx, ( EXPAND5_RA_OUT_0 + (pin / 8) ), ( pin % 8 ) );

    return buf;
}
// Get all pin output settings from one bank
uint8_t expand5_get_bank_out_lvl ( expand5_t *ctx, uint8_t bank )
{
    uint8_t buf;

    expand5_generic_read ( ctx, EXPAND5_RA_OUT_0 + bank, &buf, 1 );
    
    return buf;
}

// Get all pin output settings from all banks
void expand5_get_all_banks_out_lvl ( expand5_t *ctx, uint8_t *bank0, uint8_t *bank1, uint8_t *bank2 )
{
    uint8_t buf[ 3 ];

    expand5_generic_read( ctx, EXPAND5_RA_IN_0, buf, 3 );

    *bank0 = buf[ 0 ];
    *bank1 = buf[ 1 ];
    *bank2 = buf[ 2 ];
}

// Set a single OUTPUT pin's logic level
void expand5_write_pin ( expand5_t *ctx, uint16_t pin, uint8_t pin_val )
{
    expand5_write_bit( ctx, ( EXPAND5_RA_OUT_0 + ( pin / 8 ) ), ( pin % 8 ), pin_val );
}

// Set all OUTPUT pins' logic levels in one bank
void expand5_write_bank ( expand5_t *ctx, uint8_t bank, uint8_t value )
{
    expand5_generic_write( ctx, ( EXPAND5_RA_OUT_0 + bank ), &value, 1 );
}

// Set all OUTPUT pins' logic levels in all banks
void expand5_write_all_banks ( expand5_t *ctx, uint8_t bank0, uint8_t bank1, uint8_t bank2 )
{
    uint8_t buf[ 3 ];
    
    buf[ 0 ] = bank0;
    buf[ 1 ] = bank1;
    buf[ 2 ] = bank2;

    expand5_generic_write( ctx, ( EXPAND5_RA_OUT_0 | EXPAND5_AUTO_INC ), buf, 3 );
}

// Get a single pin's polarity ( normal/inverted ) setting
uint8_t expand5_get_pin_pol ( expand5_t *ctx, uint16_t pin )
{
    uint8_t buf;

    buf = expand5_read_bit( ctx, ( EXPAND5_RA_POL_0 + ( pin / 8 ) ), ( pin % 8 ) );

    return buf;
}

// Get all pin polarity ( normal/inverted ) settings from one bank
uint8_t expand5_get_bank_pol ( expand5_t *ctx, uint8_t bank )
{
    uint8_t buf;

    expand5_generic_read( ctx, ( EXPAND5_RA_POL_0 + bank ), &buf, 1 );

    return buf;
}

// Get all pin polarity ( normal/inverted ) settings from all banks
void expand5_get_all_banks_pol ( expand5_t *ctx, uint8_t *bank0, uint8_t *bank1, uint8_t *bank2 )
{
    uint8_t buf[ 3 ];

    expand5_generic_read( ctx, EXPAND5_RA_POL_0, buf, 3 );

    *bank0 = buf[ 0 ];
    *bank1 = buf[ 1 ];
    *bank2 = buf[ 2 ];
}

// Set a single pin's polarity ( normal/inverted ) setting
void expand5_set_pin_pol ( expand5_t *ctx, uint16_t pin, uint8_t polarity )
{
    expand5_write_bit( ctx, ( EXPAND5_RA_POL_0 + ( pin / 8) ), ( pin % 8 ), polarity );
}

// Set all pin polarity ( normal/inverted ) settings in one bank
void expand5_set_bank_pol ( expand5_t *ctx, uint8_t bank, uint8_t polarity )
{
    expand5_generic_write( ctx, ( EXPAND5_RA_POL_0 + bank ), &polarity, 1 );
}

// Set all pin polarity ( normal/inverted ) settings in all banks
void expand5_set_all_banks_pol ( expand5_t *ctx, uint8_t bank0, uint8_t bank1, uint8_t bank2 )
{
    uint8_t buf[ 3 ];

    buf[ 0 ] = bank0;
    buf[ 1 ] = bank1;
    buf[ 2 ] = bank2;

    expand5_generic_write( ctx, ( EXPAND5_RA_POL_0 | EXPAND5_AUTO_INC ), buf, 3 );
}

// Get a single pin's direction ( I/O ) setting
uint8_t expand5_get_pin_dir ( expand5_t *ctx, uint16_t pin )
{
    uint8_t buf;

    buf = expand5_read_bit( ctx, ( EXPAND5_RA_CFG_0 + ( pin / 8 ) ), ( pin % 8 ) );

    return buf;
}

// Get all pin direction ( I/O ) settings from one bank
uint8_t expand5_get_bank_dir ( expand5_t *ctx, uint8_t bank )
{
    uint8_t buf;

    expand5_generic_read( ctx, ( EXPAND5_RA_CFG_0 + bank ), &buf, 1 );

    return buf;
}

// Get all pin direction ( I/O ) settings from all banks
void expand5_get_all_dir ( expand5_t *ctx, uint8_t *bank0, uint8_t *bank1, uint8_t *bank2 )
{
    uint8_t buf[ 3 ];
    
    expand5_generic_read( ctx, EXPAND5_RA_CFG_0, buf, 3 );

    *bank0 = buf[ 0 ];
    *bank1 = buf[ 1 ];
    *bank2 = buf[ 2 ];
}

// Set a single pin's direction ( I/O ) setting
void expand5_set_pin_dir( expand5_t *ctx, uint16_t pin, uint8_t direction )
{
    expand5_write_bit( ctx, ( EXPAND5_RA_CFG_0 + ( pin / 8 ) ), ( pin % 8 ), direction );
}

// Set all pin direction ( I/O ) settings in one bank
void expand5_set_bank_dir ( expand5_t *ctx, uint8_t bank, uint8_t direction )
{
    expand5_generic_write( ctx, ( EXPAND5_RA_CFG_0 + bank ), &direction, 1 );
}

// Set all pin direction ( I/O ) settings in all banks
void expand5_set_all_dir ( expand5_t *ctx, uint8_t bank0, uint8_t bank1, uint8_t bank2 )
{
    uint8_t buf[ 3 ];

    buf[ 0 ] = bank0;
    buf[ 1 ] = bank1;
    buf[ 2 ] = bank2;
    
    expand5_generic_write( ctx, ( EXPAND5_RA_CFG_0 | EXPAND5_AUTO_INC ), buf, 3 );
}

// Reset
void expand5_reset ( expand5_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

// Check interrupt
uint8_t expand5_check_int ( expand5_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

