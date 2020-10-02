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

#include "c3xbuck.h"

// ------------------------------------------------------------------ VARIABLES
static uint8_t buck1;
static uint8_t buck2;
static uint8_t buck3;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void enable_disable_buck_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c3xbuck_cfg_setup ( c3xbuck_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en1 = HAL_PIN_NC;
    cfg->en2 = HAL_PIN_NC;
    cfg->en3 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_STANDARD_SPEED; 
    cfg->i2c_address = 0x60;
}

C3XBUCK_RETVAL c3xbuck_init ( c3xbuck_t *ctx, c3xbuck_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.pins.scl = cfg->scl;
    i2c_cfg.pins.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) != I2C_SUCCESS )
    {
        return C3XBUCK_INIT_ERROR;
    }

    // Output pins 

    digital_out_init( &ctx->en1, cfg->en1 );
    digital_out_init( &ctx->en2, cfg->en2 );
    digital_out_init( &ctx->en3, cfg->en3 );

    return C3XBUCK_OK;

}

void c3xbuck_default_cfg ( c3xbuck_t *ctx )
{
    c3xbuck_enable_buck( ctx, C3XBUCK_SELECT_BUCK_1 );
    c3xbuck_enable_buck( ctx, C3XBUCK_SELECT_BUCK_2 );
    c3xbuck_enable_buck( ctx, C3XBUCK_SELECT_BUCK_3 );
    
    c3xbuck_configuration_buck( ctx, C3XBUCK_SELECT_BUCK_1, 
                                     C3XBUCK_CFG_RATE_10mV_2cycles |
                                     C3XBUCK_CFG_MODE_PSM_OPERATION |
                                     C3XBUCK_CFG_SW_ENABLE_BUCK );
                                                  
    c3xbuck_configuration_buck( ctx, C3XBUCK_SELECT_BUCK_2, 
                                     C3XBUCK_CFG_RATE_10mV_2cycles |
                                     C3XBUCK_CFG_MODE_PSM_OPERATION |
                                     C3XBUCK_CFG_SW_ENABLE_BUCK );
                                                  
    c3xbuck_configuration_buck( ctx, C3XBUCK_SELECT_BUCK_3, 
                                     C3XBUCK_CFG_RATE_10mV_2cycles |
                                     C3XBUCK_CFG_MODE_PSM_OPERATION |
                                     C3XBUCK_CFG_SW_ENABLE_BUCK );
}


void c3xbuck_write_byte ( c3xbuck_t *ctx, uint8_t reg, uint8_t data_value )
{
    i2c_master_transfer_t i2c_transfer;
    uint8_t write_reg[ 2 ];
    
    write_reg[ 0 ] = reg;
    write_reg[ 1 ] = data_value;
    
    i2c_transfer.slave_address = ctx->slave_address;
    i2c_transfer.buffer = write_reg;
    i2c_transfer.count = 2;
    i2c_transfer.end_mode = I2C_STOP_MODE;
    
    i2c_master_start( &ctx->i2c );
    i2c_master_write( &ctx->i2c, &i2c_transfer );

}

uint8_t c3xbuck_read_byte( c3xbuck_t *ctx, uint8_t reg )
{
    i2c_master_transfer_t i2c_transfer;
    uint8_t write_reg[ 1 ];
    uint8_t read_buf[ 1 ];
    
    write_reg[ 0 ] = reg;
    
    i2c_transfer.slave_address = ctx->slave_address;
    i2c_transfer.buffer - write_reg;
    i2c_transfer.count - 1;
    i2c_transfer.end_mode - I2C_RESTART_MODE;
    
    i2c_master_start( &ctx->i2c );
    i2c_master_write( &ctx->i2c, &i2c_transfer );
    
    i2c_transfer.buffer   = read_buf;
    i2c_transfer.count    = 1;
    i2c_transfer.end_mode = I2C_STOP_MODE;

    i2c_master_read( &ctx->i2c, &i2c_transfer );
    
    return read_buf[ 0 ];
}

void c3xbuck_enable_buck ( c3xbuck_t *ctx, uint8_t buck )
{
    if ( buck == C3XBUCK_SELECT_BUCK_1 )
    {
        digital_out_write( &ctx->en1, 1 );
    }
    else if ( buck == C3XBUCK_SELECT_BUCK_2 )
    {
        digital_out_write( &ctx->en2, 1 );
    }
    else if ( buck == C3XBUCK_SELECT_BUCK_3 )
    {
        digital_out_write( &ctx->en3, 1 );
    }
    enable_disable_buck_delay( );
}

void c3xbuck_disable_buck ( c3xbuck_t *ctx, uint8_t buck )
{
    if( buck == C3XBUCK_SELECT_BUCK_1 )
    {
        digital_out_write( &ctx->en1, 0 );
    }
    else if( buck == C3XBUCK_SELECT_BUCK_2 )
    {
        digital_out_write( &ctx->en2, 0 );
    }
    else if( buck == C3XBUCK_SELECT_BUCK_3 )
    {
        digital_out_write( &ctx->en2, 0 );
    }
    enable_disable_buck_delay( );
}

void c3xbuck_set_voltage ( c3xbuck_t *ctx, uint8_t buck, uint8_t voltage )
{
    volatile uint8_t select_voltage;
    
    if ( voltage == C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE )
    {
        c3xbuck_write_byte( ctx, buck, 0x00 );
    }
    else
    {
        select_voltage = 0x80 | voltage;
        c3xbuck_write_byte( ctx, buck, select_voltage );
    }
}

uint8_t c3xbuck_get_status( c3xbuck_t *ctx )
{
    volatile uint8_t status;
    
    status = c3xbuck_read_byte( ctx, C3XBUCK_REG_SYS_STATUS );
    
    return status;
}

void c3xbuck_configuration_buck ( c3xbuck_t *ctx, uint8_t buck, uint8_t config )
{
    volatile uint8_t select_buck;
    select_buck = buck + 3;
    
    c3xbuck_write_byte( ctx, select_buck, config );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void enable_disable_buck_delay ( void )
{
    Delay_100ms( );
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

