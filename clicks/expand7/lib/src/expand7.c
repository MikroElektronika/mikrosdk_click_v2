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

#include "expand7.h"

// ------------------------------------------------------------------ VARIABLES

static uint8_t port_slave_addr;
static uint8_t eeprom_slave_addr;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_rst_delay ( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void expand7_cfg_setup ( expand7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = EXPAND7_DEV_ADR_GND;
}

EXPAND7_RETVAL expand7_init ( expand7_t *ctx, expand7_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return EXPAND7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    port_slave_addr = EXPAND7_M_PORT_BASE_ADR | ctx->slave_address;
    eeprom_slave_addr = EXPAND7_EEPROM_BASE_ADR | ctx->slave_address;

    return EXPAND7_OK;
}

void expand7_generic_write ( expand7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void expand7_generic_read ( expand7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

// Write the byte of data function
void expand7_write_byte ( expand7_t *ctx, uint8_t reg_adr, uint8_t wr_data )
{
    i2c_master_set_slave_address( &ctx->i2c, port_slave_addr );
    expand7_generic_write( ctx, reg_adr, &wr_data, 1 );
}

// Read the byte of data function
uint8_t expand7_read_byte ( expand7_t *ctx, uint8_t reg_adr )
{
    uint8_t result = 0x00;

    i2c_master_set_slave_address( &ctx->i2c, port_slave_addr );
    expand7_generic_read( ctx, reg_adr, &result, 1 );

    return result;
}

void expand7_write_port_exp ( expand7_t *ctx, uint8_t reg, uint8_t *buf, uint8_t len )
{
    uint8_t tx_buf[ 255 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;

    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = buf[ cnt ];
    }
    i2c_master_set_slave_address( &ctx->i2c, port_slave_addr );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

void expand7_read_port_exp ( expand7_t *ctx, uint8_t reg, uint8_t *buf, uint8_t len )
{
    i2c_master_set_slave_address( &ctx->i2c, port_slave_addr );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, buf, len );
}

// Send Command to EEPROM function
void expand7_send_eeprom_cmd ( expand7_t *ctx, uint8_t cmd )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = EXPAND7_REG_CMD_ADR;
    tx_buf[ 1 ] = cmd;

    i2c_master_set_slave_address( &ctx->i2c, port_slave_addr );
    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

void expand7_write_eeprom ( expand7_t *ctx, uint16_t mem_adr, uint8_t *buf, uint8_t len )
{
    uint8_t tx_buf[ 255 ];
    uint8_t cnt;

    tx_buf[ 1 ] = (uint8_t)( mem_adr & 0x00FF );
    tx_buf[ 0 ] = (uint8_t)( ( mem_adr >> 8 ) & 0x00FF );

    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 2 ] = buf[ cnt ];
    }

    i2c_master_set_slave_address( &ctx->i2c, eeprom_slave_addr );
    i2c_master_write( &ctx->i2c, tx_buf, len + 2 );
}

void expand7_read_eeprom ( expand7_t *ctx, uint16_t mem_adr, uint8_t *buf, uint8_t len )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 1 ] = (uint8_t)( mem_adr & 0x00FF );
    tx_buf[ 0 ] = (uint8_t)( ( mem_adr >> 8 ) & 0x00FF );

    i2c_master_set_slave_address( &ctx->i2c, eeprom_slave_addr );
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, buf, len );
}

// Read bit
uint8_t expand7_read_bit ( expand7_t *ctx, uint8_t reg_adr, uint8_t bit_num )
{
    uint8_t bit_chk;
    uint8_t res;

    bit_chk = expand7_read_byte( ctx, reg_adr );
    res = bit_chk & ( 1 << bit_num );

    return res;
}

// Write bit
void expand7_write_bit ( expand7_t *ctx, uint8_t reg_adr, uint8_t bit_num, uint8_t pin_val )
{
    uint8_t bit_chk;

    bit_chk = expand7_read_byte( ctx, reg_adr );
    bit_chk = ( pin_val != 0 ) ? ( bit_chk | ( 1 << bit_num ) ) : ( bit_chk & ~( 1 << bit_num ) );

    expand7_write_byte( ctx, reg_adr, bit_chk );
}

// Get a single INPUT pin's logic level
uint8_t expand7_read_pin ( expand7_t *ctx, uint16_t pin, uint8_t inv )
{
    uint8_t buf;
    
    if ( pin > 19 )
    {
        pin += 4;
    }

    if ( inv == 0x01 )
    {
        expand7_write_byte( ctx, EXPAND7_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
        expand7_write_byte( ctx, EXPAND7_REG_INV_ADR, ( pin % 8 ) );
    }

    expand7_write_byte( ctx, EXPAND7_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    expand7_write_byte( ctx, EXPAND7_REG_PORT_DIR_ADR, 0xFF );

    buf = expand7_read_bit( ctx, ( EXPAND7_REG_IN_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ) );

    return buf;
}

// Get all pin logic levels from one port
uint8_t expand7_read_port ( expand7_t *ctx, uint8_t port, uint8_t inv )
{
    uint8_t buf;

    if ( inv == 0x01 )
    {
        expand7_write_byte( ctx, EXPAND7_REG_PORT_SEL_ADR, port );
        expand7_write_byte( ctx, EXPAND7_REG_INV_ADR, 0xFF );
    }

    expand7_write_byte( ctx, EXPAND7_REG_PORT_SEL_ADR, port );
    expand7_write_byte( ctx, EXPAND7_REG_PORT_DIR_ADR, 0xFF );

    buf = expand7_read_byte( ctx, EXPAND7_REG_IN_PORT0_ADR + port );

    return buf;
}

// Get a single OUTPUT pin's setting
uint8_t expand7_get_pin_out_lvl ( expand7_t *ctx, uint16_t pin )
{
    uint8_t buf;
    
    if ( pin > 19 )
    {
        pin += 4;
    }

    expand7_write_byte( ctx, EXPAND7_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    expand7_write_byte( ctx, EXPAND7_REG_PORT_DIR_ADR, 0xFF );

    buf = expand7_read_bit( ctx, ( EXPAND7_REG_OUT_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ) );

    return buf;
}
// Get all pin output settings from one port
uint8_t expand7_get_port_out_lvl ( expand7_t *ctx, uint8_t port )
{
    uint8_t buf;

    expand7_write_byte( ctx, EXPAND7_REG_PORT_SEL_ADR, port );
    expand7_write_byte( ctx, EXPAND7_REG_PORT_DIR_ADR, 0xFF );

    buf = expand7_read_byte ( ctx, EXPAND7_REG_OUT_PORT0_ADR + port );

    return buf;
}

// Set a single OUTPUT pin's logic level
void expand7_write_pin ( expand7_t *ctx, uint16_t pin, uint8_t pin_val )
{
    if ( pin > 19 )
    {
        pin += 4;
    }
    expand7_write_byte( ctx, EXPAND7_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    expand7_write_byte( ctx, EXPAND7_REG_PORT_DIR_ADR, 0x00 );

    expand7_write_bit( ctx, ( EXPAND7_REG_OUT_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ), pin_val );
}

// Set all OUTPUT pins' logic levels in one port
void expand7_write_port ( expand7_t *ctx, uint8_t port, uint8_t value )
{
    expand7_write_byte( ctx, EXPAND7_REG_PORT_SEL_ADR, port );
    expand7_write_byte( ctx, EXPAND7_REG_PORT_DIR_ADR, 0xFF );

    expand7_write_byte( ctx, ( EXPAND7_REG_OUT_PORT0_ADR + port ), value );
}

// Set all OUTPUT pins' logic levels in one port
void expand7_write_all ( expand7_t *ctx, uint8_t value )
{
    expand7_write_port( ctx, EXPAND7_PORT_0, value );
    expand7_write_port( ctx, EXPAND7_PORT_1, value );
    expand7_write_port( ctx, EXPAND7_PORT_2, ( value & 0x0F ) );
    expand7_write_port( ctx, EXPAND7_PORT_3, value );
    expand7_write_port( ctx, EXPAND7_PORT_4, value );
    expand7_write_port( ctx, EXPAND7_PORT_5, ( value & 0x0F ) );
}

// Select a PWM pin output pin
void expand7_sel_pwm_pin ( expand7_t *ctx, uint16_t pin, uint8_t pwm_en )
{
    if ( pin > 19 )
    {
        pin += 4;
    }

    expand7_write_byte( ctx, EXPAND7_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    expand7_write_byte( ctx, EXPAND7_REG_PORT_DIR_ADR, 0x00 );

    expand7_write_bit( ctx, ( EXPAND7_REG_OUT_PORT0_ADR + ( pin / 8 ) ), ( pin % 8 ), pwm_en );

    expand7_write_byte( ctx, EXPAND7_REG_PORT_SEL_ADR, ( 0x00 + ( pin / 8 ) ) );
    expand7_write_byte( ctx, EXPAND7_REG_SEL_PWM_OUT_ADR, ( pwm_en << ( pin % 8 ) ) );
}

// PWM Configuration
void expand7_pwm_cfg ( expand7_t *ctx, expand7_pwm_cfg_t pwm_cfg, float *duty_cyc, float *freq )
{
    uint8_t buf[ 5 ];

    buf[ 0 ] = pwm_cfg.pwm_sel;
    buf[ 1 ] = pwm_cfg.clk_src;
    buf[ 2 ] = pwm_cfg.period;
    buf[ 3 ] = pwm_cfg.pulse_wid;
    buf[ 4 ] = pwm_cfg.devider;

    if( buf[ 3 ] >= buf[ 2 ] )
    {
        buf[ 3 ] = ( buf[ 2 ] - 1 );
    }

    expand7_write_byte( ctx, EXPAND7_REG_PWM_SEL_ADR, buf[ 0 ] );
    expand7_write_byte( ctx, EXPAND7_REG_CFG_PWM_ADR, buf[ 1 ] );
    expand7_write_byte( ctx, EXPAND7_REG_PERIOD_PWM_ADR, buf[ 2 ] );
    expand7_write_byte( ctx, EXPAND7_REG_PULSE_WIDTH_PWM_ADR, buf[ 3 ] );
    expand7_write_byte( ctx, EXPAND7_REG_DIVIDER_ADR, buf[ 4 ] );

    *duty_cyc = (float)buf[ 3 ] / (float)buf[ 2 ];
    *freq = 93750.0 / (float)buf[ 4 ];
}

// Enable Register Configuration
void expand7_eeprom_enable ( expand7_t *ctx, uint8_t cmd )
{
    uint8_t tx_buf[ 4 ];

    tx_buf[ 0 ] = 0x43;
    tx_buf[ 1 ] = 0x4D;
    tx_buf[ 2 ] = 0x53;
    tx_buf[ 3 ] = cmd;

    expand7_write_port_exp( ctx, EXPAND7_REG_EEPROM_ADR, tx_buf, 4 );
}

// Reset
void expand7_reset ( expand7_t *ctx )
{
    digital_out_high( &ctx->rst );
    dev_rst_delay( );
    digital_out_low( &ctx->rst );
    dev_rst_delay( );
}

// Check interrupt
uint8_t expand7_check_int ( expand7_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_rst_delay ( )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

