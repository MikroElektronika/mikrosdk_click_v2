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

#include "stereoamp.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define STEREOAMP_VOLUME_BALANCE             32

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_comm_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void stereoamp_cfg_setup ( stereoamp_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->fll = HAL_PIN_NC;
    cfg->flr = HAL_PIN_NC;

    cfg->i2c_speed     = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address_0 = STEREOAMP_I2C_ADDRESS_0;
    cfg->i2c_address_1 = STEREOAMP_I2C_ADDRESS_1;
}

STEREOAMP_RETVAL stereoamp_init ( stereoamp_t *ctx, stereoamp_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address_0  = cfg->i2c_address_0;
    ctx->slave_address_1  = cfg->i2c_address_1;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return STEREOAMP_INIT_ERROR;
    }

    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->fll, cfg->fll );
    digital_in_init( &ctx->flr, cfg->flr );

    return STEREOAMP_OK;

}

void stereoamp_default_cfg ( stereoamp_t *ctx )
{
    // Reset function
    
    stereoamp_soft_reset( ctx );
    dev_comm_delay( );
}

void stereoamp_generic_write ( stereoamp_t *ctx, uint8_t ch_addr, uint8_t reg_addr, uint8_t tx_data )
{
    uint8_t tx_buf[ 1 ];
    
    tx_buf[ 0 ]  = ( reg_addr & STEREOAMP_MASK_ADDR ) | ( tx_data & STEREOAMP_MASK_DATA );
    
    if ( ch_addr == STEREOAMP_OUTPUT_RIGHT_SPEAKER )
    {
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_0 );
    }
    else
    {
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_1 );
    }

    i2c_master_write( &ctx->i2c, tx_buf, 1 ); 
}


void stereoamp_set_volume ( stereoamp_t *ctx, uint8_t volume )
{
    volume %= STEREOAMP_VOLUME_BALANCE;

    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_LEFT_SPEAKER, STEREOAMP_CTRL_REG_VOLUME_CONTROL1, volume );
    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_RIGHT_SPEAKER, STEREOAMP_CTRL_REG_VOLUME_CONTROL1, volume );
}

void stereoamp_mute ( stereoamp_t *ctx )
{
    uint8_t mode_buf;
    
    mode_buf  = STEREOAMP_MODE_POWER_ON;
    mode_buf |= STEREOAMP_MODE_INPUT1_OFF;
    mode_buf |= STEREOAMP_MODE_INPUT2_OFF;
    
    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_LEFT_SPEAKER, STEREOAMP_CTRL_REG_MODE_CONTROL, mode_buf );
    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_RIGHT_SPEAKER, STEREOAMP_CTRL_REG_MODE_CONTROL, mode_buf );
}

void stereoamp_soft_reset ( stereoamp_t *ctx )
{
    uint8_t mode_buf;
    
    mode_buf  = STEREOAMP_DIAG_REG_DG_RESET;
    
    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_LEFT_SPEAKER, STEREOAMP_CTRL_REG_DIAGNOSTIC_CONTROL, mode_buf );
    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_RIGHT_SPEAKER, STEREOAMP_CTRL_REG_DIAGNOSTIC_CONTROL, mode_buf );
}

void stereoamp_enable_diagnostic ( stereoamp_t *ctx )
{
    uint8_t mode_buf;
    
    mode_buf  = STEREOAMP_DIAG_REG_DG_EN;
    mode_buf |= STEREOAMP_DIAG_REG_DG_RESET;
    mode_buf |= STEREOAMP_DIAG_REG_ILIMIT;
    
    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_LEFT_SPEAKER, STEREOAMP_CTRL_REG_DIAGNOSTIC_CONTROL, mode_buf );
    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_RIGHT_SPEAKER, STEREOAMP_CTRL_REG_DIAGNOSTIC_CONTROL, mode_buf );
}

void stereoamp_set_power_on ( stereoamp_t *ctx )
{
    uint8_t mode_buf;
    
    mode_buf  = STEREOAMP_MODE_POWER_ON;
    mode_buf |= STEREOAMP_MODE_BOTH_CHANNELS;
    
    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_LEFT_SPEAKER, STEREOAMP_CTRL_REG_MODE_CONTROL, mode_buf );
    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_RIGHT_SPEAKER, STEREOAMP_CTRL_REG_MODE_CONTROL, mode_buf );
}

void stereoamp_enable_fault ( stereoamp_t *ctx )
{
    uint8_t mode_buf;
    
    mode_buf  = STEREOAMP_FLT_DET_REG_OUTPUT_OPEN;
    mode_buf |= STEREOAMP_FLT_DET_REG_OUTPUT_SHT;
    mode_buf |= STEREOAMP_FLT_DET_REG_RAIL_SHT;
    mode_buf |= STEREOAMP_FLT_DET_REG_OVF;
    mode_buf |= STEREOAMP_FLT_DET_REG_TSD;
    
    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_LEFT_SPEAKER, STEREOAMP_CTRL_REG_FAULT_DETECTION, mode_buf );
    stereoamp_generic_write( ctx, STEREOAMP_OUTPUT_RIGHT_SPEAKER, STEREOAMP_CTRL_REG_FAULT_DETECTION, mode_buf );
}

uint8_t stereoamp_check_fault_left ( stereoamp_t *ctx )
{
    return digital_in_read( &ctx->fll );
}

uint8_t stereoamp_check_fault_right ( stereoamp_t *ctx )
{
    return digital_in_read( &ctx->flr );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_comm_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

