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

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c3xbuck_cfg_setup ( c3xbuck_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en1   = HAL_PIN_NC;
    cfg->en2 = HAL_PIN_NC;
    cfg->en3 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x60;
}

c3xbuck_RETVAL c3xbuck_init ( c3xbuck_t *ctx, c3xbuck_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return c3xbuck_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->en1, cfg->en1 );
    digital_out_init( &ctx->en2, cfg->en2 );
    digital_out_init( &ctx->en3, cfg->en3 );

    return c3xbuck_OK;
}

void c3xbuck_default_cfg ( c3xbuck_t *ctx )
{
    c3xbuck_enable_buck( ctx, C3XBUCK_SELECT_BUCK_1 );
    c3xbuck_enable_buck( ctx, C3XBUCK_SELECT_BUCK_2 );
    c3xbuck_enable_buck( ctx, C3XBUCK_SELECT_BUCK_3 );
    
    c3xbuck_configuration_buck( ctx, C3XBUCK_SELECT_BUCK_1, C3XBUCK_CFG_RATE_10mV_2cycles |
                                                      C3XBUCK_CFG_MODE_PSM_OPERATION |
                                                      C3XBUCK_CFG_SW_ENABLE_BUCK );
                                                  
    c3xbuck_configuration_buck( ctx, C3XBUCK_SELECT_BUCK_3, C3XBUCK_CFG_RATE_10mV_2cycles |
                                                      C3XBUCK_CFG_MODE_PSM_OPERATION |
                                                      C3XBUCK_CFG_SW_ENABLE_BUCK );
                                                  
    c3xbuck_configuration_buck( ctx, C3XBUCK_SELECT_BUCK_3, C3XBUCK_CFG_RATE_10mV_2cycles |
                                                      C3XBUCK_CFG_MODE_PSM_OPERATION |
                                                      C3XBUCK_CFG_SW_ENABLE_BUCK );
    Delay_100ms( );
}

void c3xbuck_generic_write ( c3xbuck_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void c3xbuck_generic_read ( c3xbuck_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void c3xbuck_enable_buck ( c3xbuck_t *ctx, uint8_t buck )
{
    if( buck == C3XBUCK_SELECT_BUCK_1 )
    {
        digital_out_high( &ctx->en1 );
    }
    else if( buck == C3XBUCK_SELECT_BUCK_2 )
    {
        digital_out_high( &ctx->en2 );
    }
    else if( buck == C3XBUCK_SELECT_BUCK_3 )
    {
        digital_out_high( &ctx->en3 );
    }
    Delay_100ms( );
    Delay_100ms( );
}

void c3xbuck_disable_buck ( c3xbuck_t *ctx, uint8_t buck )
{
    if ( buck == C3XBUCK_SELECT_BUCK_1 )
    {
        digital_out_low( &ctx->en1 );
    }
    else if( buck == C3XBUCK_SELECT_BUCK_2 )
    {
        digital_out_low( &ctx->en2 );
    }
    else if( buck == C3XBUCK_SELECT_BUCK_3 )
    {
        digital_out_low( &ctx->en3 );
    }
    Delay_100ms( );
    Delay_100ms( );
}

void c3xbuck_set_voltage ( c3xbuck_t *ctx, uint8_t buck, uint8_t voltage )
{
    uint8_t select_voltage;
    
    if( voltage == C3XBUCK_BUCK_DEFAULT_OUTPUT_VOLTAGE )
    {
        c3xbuck_generic_write( ctx, buck, 0x00, 1 );
    }
    else
    {
        select_voltage = 0x80 | voltage;
        c3xbuck_generic_write( ctx, buck, &select_voltage, 1 );
    }
}

uint8_t c3xbuck_get_status ( c3xbuck_t *ctx )
{
    uint8_t status;
    
    c3xbuck_generic_read(ctx, C3XBUCK_REG_SYS_STATUS, &status, 1 );
    return status;
}

void c3xbuck_configuration_buck ( c3xbuck_t *ctx, uint8_t buck, uint8_t config )
{
    uint8_t select_buck;
    
    select_buck = buck + 3;
    c3xbuck_generic_write( ctx, select_buck, &config, 1 );
}

// ------------------------------------------------------------------------- END

