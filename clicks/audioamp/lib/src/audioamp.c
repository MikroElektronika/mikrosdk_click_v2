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

#include "audioamp.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void audioamp_cfg_setup ( audioamp_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AUDIOAMP_I2C_ADDRESS_0;
}

AUDIOAMP_RETVAL audioamp_init ( audioamp_t *ctx, audioamp_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AUDIOAMP_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    

    return AUDIOAMP_OK;
}


void audioamp_generic_write ( audioamp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void audioamp_generic_read ( audioamp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void audioamp_power_on ( audioamp_t *ctx )
{
    uint8_t buffer[ 1 ];
    uint8_t dummy;

    buffer[ 0 ] = AUDIOAMP_CMD_ENABLE | AUDIOAMP_MUX_BIT;

    audioamp_generic_write( ctx, buffer[ 0 ], &dummy, 1 );
}

void audioamp_power_off ( audioamp_t *ctx )
{
    uint8_t buffer[ 1 ];
    uint8_t dummy;

    buffer[ 0 ] = AUDIOAMP_CMD_DISABLE;

    audioamp_generic_write( ctx, buffer[ 0 ], &dummy, 1 );
}

void audioamp_set_volume ( audioamp_t *ctx, uint8_t volume_value )
{
    uint8_t buffer[ 1 ];
    uint8_t dummy;

    volume_value %= 32;

    buffer[ 0 ] = volume_value;
    buffer[ 0 ] |= AUDIOAMP_REG_VOL_1;

    audioamp_generic_write( ctx, buffer[ 0 ], &dummy, 1 );

    buffer[ 0 ] = volume_value;
    buffer[ 0 ] |= AUDIOAMP_REG_VOL_2;

    audioamp_generic_write( ctx, buffer[ 0 ], &dummy, 1 );
}

void audioamp_set_volume_channel ( audioamp_t *ctx, uint8_t channel, uint8_t volume_value )
{
    uint8_t buffer[ 1 ];
    uint8_t dummy;

    volume_value %= 32;
    
    buffer[ 0 ] = volume_value;

    if ( channel == AUDIOAMP_MODE_CH_1 )
    {
        buffer[ 0 ] |= AUDIOAMP_CMD_VOLUME_1;
    }
     
    if ( channel == AUDIOAMP_MODE_CH_2 )
    {
       buffer[ 0 ] |= AUDIOAMP_CMD_VOLUME_2;
    }
   
    audioamp_generic_write( ctx, buffer[ 0 ], &dummy, 1 );
}

void audioamp_enable ( audioamp_t *ctx )
{
    uint8_t tmp;
    uint8_t dummy;

    tmp = AUDIOAMP_REG_MODE;
    tmp |= AUDIOAMP_CMD_ENABLE;

    audioamp_generic_write( ctx, tmp, &dummy, 1 );
}

void audioamp_disable ( audioamp_t *ctx )
{
    uint8_t tmp;
    uint8_t dummy;

    tmp = AUDIOAMP_REG_MODE;
    tmp |= AUDIOAMP_CMD_DISABLE;

    audioamp_generic_write( ctx, tmp, &dummy, 1 );
}

void audioamp_mute_mode ( audioamp_t *ctx )
{
    uint8_t buffer[ 1 ];
    uint8_t dummy;

    buffer[ 0 ] = AUDIOAMP_CMD_ENABLE | AUDIOAMP_MUTE_BIT;

    audioamp_generic_write( ctx, buffer[ 0 ], &dummy, 1 );
}

void audioamp_unmute_mode ( audioamp_t *ctx )
{
    uint8_t buffer[ 1 ];
    uint8_t dummy;

    buffer[ 0 ] = AUDIOAMP_CMD_ENABLE | AUDIOAMP_MUX_BIT;

    audioamp_generic_write( ctx, buffer[ 0 ], &dummy, 1 );
}

void audioamp_set_normal_operation ( audioamp_t *ctx )
{
    uint8_t tmp;
    uint8_t dummy;

    tmp = AUDIOAMP_REG_FAULT;
    tmp |= 0x00;

    audioamp_generic_write( ctx, tmp, &dummy, 1 );
}

void audioamp_set_fault_detecton_control( audioamp_t *ctx, uint8_t input_command )
{
    uint8_t temp;
    uint8_t tmp;
    uint8_t dummy;

    temp = 0x01;
    
    input_command %= 5;
    
    temp <<= input_command;

    tmp = AUDIOAMP_REG_FAULT;
    tmp |= temp;

    audioamp_generic_write( ctx, tmp, &dummy, 1 );
}

void audioamp_set_input( audioamp_t *ctx, uint8_t input_mode )
{
    uint8_t temp;
    uint8_t tmp;
    uint8_t dummy;
    
    if ( input_mode == AUDIOAMP_MODE_CH_1 )
    {
       temp = AUDIOAMP_CH_1_BIT;
    }
        
    if ( input_mode == AUDIOAMP_MODE_CH_2 )
    {
       temp = AUDIOAMP_CH_2_BIT;
    }
        
    if ( input_mode == AUDIOAMP_MODE_MUX )
    {
       temp = AUDIOAMP_MUX_BIT;
    }
        
    if ( input_mode == AUDIOAMP_MODE_MUTE )
    {
       temp = AUDIOAMP_MUTE_BIT;
    }

    tmp = AUDIOAMP_REG_MODE;
    tmp |= temp | AUDIOAMP_CMD_ENABLE;

    audioamp_generic_write( ctx, tmp, &dummy, 1 );
}

/* Check interrupt status function */
uint8_t audioamp_check_status ( audioamp_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS


// ------------------------------------------------------------------------- END

