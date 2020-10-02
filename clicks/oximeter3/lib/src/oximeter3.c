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

#include "oximeter3.h"

// ----------------------------------------------- PRIVATE FUNCTION DECLARATION

static uint8_t dev_data_ready ( oximeter3_t *ctx, uint8_t data_type );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void oximeter3_cfg_setup ( oximeter3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = OXIMETER3_SLAVE_ADDRESS;
}

OXIMETER3_RETVAL oximeter3_init ( oximeter3_t *ctx, oximeter3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return OXIMETER3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return OXIMETER3_OK;
}

void oximeter3_generic_write ( oximeter3_t *ctx, uint8_t reg, uint8_t data_buf )
{
    uint8_t tx_buf[ 3 ];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = data_buf;
    
    i2c_master_write( &ctx->i2c, tx_buf, 2 );   
}

uint8_t oximeter3_generic_read ( oximeter3_t *ctx, uint8_t reg )
{
    uint8_t tmp_data;

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, &tmp_data, 1 );

    return tmp_data;
}

uint16_t oximeter3_read_value ( oximeter3_t *ctx, uint8_t type_macro )
{
    uint16_t temp_data;

    switch ( type_macro )
    {
        case OXIMETER3_PROX:
        case OXIMETER3_HEART_RATE:
        {
            while ( OXIMETER3_OK != dev_data_ready( ctx, OXIMETER3_CMD_PROX_DATA_READY ) );

            temp_data = oximeter3_generic_read( ctx, OXIMETER3_REG_PROX_RESULT_MSB );
            temp_data <<= SHIFT_VALUE;
            temp_data |= oximeter3_generic_read( ctx, OXIMETER3_REG_PROX_RESULT_LSB );

            return temp_data;
        }
        case OXIMETER3_ALS:
        {
            while ( OXIMETER3_OK != dev_data_ready( ctx, OXIMETER3_CMD_ALS_DATA_READY ) );

            temp_data = oximeter3_generic_read( ctx, OXIMETER3_REG_ALS_RESULT_MSB );
            temp_data <<= SHIFT_VALUE;
            temp_data |= oximeter3_generic_read( ctx, OXIMETER3_REG_ALS_RESULT_LSB );
            
            return temp_data;
        }
        default:
        {
            return OXIMETER3_ERROR;
        }
    }
}

uint8_t oximeter3_get_int_status ( oximeter3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t dev_data_ready ( oximeter3_t *ctx, uint8_t data_type )
{
    uint8_t data_rdy;

    for ( ; ; )
    {
        data_rdy = oximeter3_generic_read( ctx, OXIMETER3_REG_COMMAND ); 

        if ( ( data_rdy & data_type ) == data_type )
        {
            return OXIMETER3_OK;
        }       
    }
}

// ------------------------------------------------------------------------- END

