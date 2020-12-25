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

#include "dac3.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t drv_read_all ( dac3_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dac3_cfg_setup ( dac3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->dac_cfg.vrl = 0;
    cfg->dac_cfg.power = 0;
    cfg->dac_cfg.gain = 0;
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x60;
}

DAC3_RETVAL dac3_init ( dac3_t *ctx, dac3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->dac_cfg.vrl = cfg->dac_cfg.vrl;
    ctx->dac_cfg.power = cfg->dac_cfg.power;
    ctx->dac_cfg.gain = cfg->dac_cfg.gain;
    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return DAC3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
	i2c_master_set_timeout( &ctx->i2c, 0 );

    return DAC3_OK;
}

void dac3_write_all_mem ( dac3_t *ctx, uint16_t value )
{
    uint8_t tx_buf[ 3 ] = { 0 };
    uint8_t ready;

    tx_buf[ 0 ] |= DAC3_VOLATILE_ALL_MEM;
    tx_buf[ 0 ] |= ( ( uint8_t ) ctx->dac_cfg.vrl << 3 );
    tx_buf[ 0 ] |= ( ( uint8_t ) ctx->dac_cfg.power << 1 );
    tx_buf[ 0 ] |= ctx->dac_cfg.gain;
    tx_buf[ 1 ] = ( value & 0x0FF0 ) >> 4;
    tx_buf[ 2 ] = ( value & 0x000F ) << 4;

    i2c_master_write( &ctx->i2c, tx_buf, 3 );  

    do 
    {
        ready = drv_read_all( ctx );
    
    } while ( ready );
}

void dac3_send_command ( dac3_t *ctx, uint8_t cmd )
{
    i2c_master_write( &ctx->i2c, &cmd, 1 );  
}

void dac3_set_out_voltage ( dac3_t *ctx, uint16_t output )
{
    output %= 4096;

    ctx->dac_cfg.vrl = VREF_BUFFERED;
    ctx->dac_cfg.power = NORMAL;
    ctx->dac_cfg.gain = GAIN_1x;

    dac3_write_all_mem( ctx, output );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t drv_read_all ( dac3_t *ctx )
{
    uint8_t rx_buf[ 6 ] = { 0 };

    i2c_master_read( &ctx->i2c, rx_buf, 6 ); 

    return rx_buf[ 0 ] >> 7;
}

// ------------------------------------------------------------------------- END

