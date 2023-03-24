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

#include "capwheel2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void capwheel2_cfg_setup ( capwheel2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = CAPWHEEL2_DEVICE_ADDRESS;
}

CAPWHEEL2_RETVAL capwheel2_init ( capwheel2_t *ctx, capwheel2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CAPWHEEL2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->rdy, cfg->rdy );

    
    return CAPWHEEL2_OK;

}

uint8_t capwheel2_default_cfg ( capwheel2_t *ctx )
{
    uint8_t data_buffer[30];
    uint8_t i;

    if ( capwheel2_i2c_read_wait( ctx, CAPWHEEL2_DEVICE_INFO , &data_buffer[0], 2 ) )
    {
        return 1;
    }

    if ( ( data_buffer[0] != 0x3C ) && ( data_buffer[1] != 0x01 ) )
    {
        return 1;
    }

    data_buffer[0] = 0x10; 
    if ( capwheel2_i2c_write_wait( ctx, CAPWHEEL2_SYS_FLAGS, &data_buffer[0], 1 ) )
        return 1;

    data_buffer[0] = 0x00; 
    data_buffer[1] = 0x00; 
    data_buffer[2] = 0x00; 
    data_buffer[3] = 0x00;
    data_buffer[4] = 0x00; 
    if ( capwheel2_i2c_write_wait( ctx, CAPWHEEL2_MULTIPLIERS, &data_buffer[0], 5 ) )
    {
        return 1;
    }
    data_buffer[0] = 81;
    data_buffer[1] = 73;
    data_buffer[2] = 73;
    data_buffer[3] = 73;
    if ( capwheel2_i2c_write_wait( ctx, CAPWHEEL2_COMPENSATION, &data_buffer[0], 4 ) )
    {
        return 1;
    }
    data_buffer[0] = 0x22;  
    data_buffer[1] = 0x0B; 
    data_buffer[2] = 0x08; 
    data_buffer[3] = 0xB7;
    data_buffer[4] = 0x00;
    if ( capwheel2_i2c_write_wait( ctx, CAPWHEEL2_PROX_SETTINGS, &data_buffer[0], 5 ) )
    {
        return 1;
    }
    data_buffer[0] = 4;  
    data_buffer[1] = 16; 
    data_buffer[2] = 16; 
    data_buffer[3] = 16; 
    data_buffer[4] = 3; 
    data_buffer[5] = 0;  
    data_buffer[6] = 20; 
    data_buffer[7] = 4;  
    if ( capwheel2_i2c_write_wait( ctx, CAPWHEEL2_THRESHOLDS, &data_buffer[0], 8 ) )
    {
        return 1;
    }

    data_buffer[0] = 0x00; 
    data_buffer[1] = 48;    
    data_buffer[2] = 64;    
    if ( capwheel2_i2c_write_wait( ctx, CAPWHEEL2_TIMINGS_AND_TARGETS, &data_buffer[0], 3 ) )
    {
        return 1;
    }

    data_buffer[0] = 20;
    data_buffer[1] = 81; 
    data_buffer[2] = 51; 
    if ( capwheel2_i2c_write_wait( ctx, CAPWHEEL2_GESTURE_TIMERS, &data_buffer[0], 3 ) )
    {
        return 1;
    }

    data_buffer[0] = 0x0F;
    if ( capwheel2_i2c_write_wait(ctx, CAPWHEEL2_ACTIVE_CHANNELS, &data_buffer[0], 1 ) )
    {
        return 1;
    }

    data_buffer[0] = 0x10;
    if ( capwheel2_i2c_write_wait( ctx, CAPWHEEL2_PROX_SETTINGS, &data_buffer[0], 1 ) )
    {
        return 1;
    }
    do
    {
        if ( capwheel2_i2c_read_wait( ctx, CAPWHEEL2_SYS_FLAGS, &data_buffer[0], 1 ) )
        {
            return 1;
        }
    }
    while ( ( data_buffer[0] & 0x04 ) == 0x04 );

    if ( capwheel2_i2c_read_wait( ctx, CAPWHEEL2_SYS_FLAGS, &data_buffer[0], 2))
    {
        return 1;
    }

    if ( ( ( data_buffer[0] & 0xA4 ) == 0x00 ) )
    {
        return 0;
    }
    else 
    {
        return 1;
    }
}

void capwheel2_i2c_write_no_wait ( capwheel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void capwheel2_i2c_read_no_wait ( capwheel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t capwheel2_int_get ( capwheel2_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

uint8_t capwheel2_wait_for_rdy ( capwheel2_t *ctx )
{
    uint32_t aux_counter = 0;

    while ( ( capwheel2_int_get( ctx ) == 0 ) && ( aux_counter < 4294967295 ) )
    {
        aux_counter++;
    }
    if (aux_counter == 4294967295)
    {
        return 1;
    }

    aux_counter = 0;
    while ( ( capwheel2_int_get( ctx ) == 1 ) && ( aux_counter < 4294967295 ) )
    {
        aux_counter++;
    }
    if ( aux_counter == 4294967295 )
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

uint8_t capwheel2_i2c_read_wait ( capwheel2_t *ctx, uint8_t register_address, uint8_t * read_buffer, uint8_t n_bytes )
{
    if ( capwheel2_wait_for_rdy( ctx ) )
    {
       return 1;
    }

    capwheel2_i2c_read_no_wait( ctx, register_address, read_buffer, n_bytes );
    
    return 0;
}

uint8_t capwheel2_i2c_write_wait ( capwheel2_t *ctx, uint8_t register_address, uint8_t * register_values, uint8_t n_bytes )
{  
    if (capwheel2_wait_for_rdy( ctx ))
    {
       return 1;
    }

    capwheel2_i2c_write_no_wait( ctx, register_address, register_values, n_bytes );
    
    
    return 0;
}

// ------------------------------------------------------------------------- END

