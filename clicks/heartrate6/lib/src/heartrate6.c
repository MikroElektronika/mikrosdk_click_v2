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

#include "heartrate6.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t check_addr ( uint8_t register_addr );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void heartrate6_cfg_setup ( heartrate6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_FULL; 
    cfg->i2c_address = HEARTRATE6_SLAVE_ADDR;
}

HEARTRATE6_RETVAL heartrate6_init ( heartrate6_t *ctx, heartrate6_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HEARTRATE6_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    ctx->res = 0;
    ctx->wait_time = 0;

    return HEARTRATE6_OK;
}

void heartrate6_default_cfg ( heartrate6_t *ctx )
{
    heartrate6_reset( ctx );
    heartrate6_set_freq( ctx, HEARTRATE6_OSC_ACTIVE | 
                                      HEARTRATE6_LED_FREQ_128HZ | 
                                      HEARTRATE6_DATAREAD_FREQ_32HZ );
    heartrate6_write_single_byte( ctx, HEARTRATE6_MEAS_CTRL2_REG, HEARTRATE6_LEDS_PULSED | 
                                                                                                HEARTRATE6_LED_TIME_300MICROSEC | 
                                                                                                HEARTRATE6_LED_CURR_20MA );
    heartrate6_start_measure( ctx );
    Delay_100ms( );
    Delay_100ms( );
}

uint8_t heartrate6_write_single_byte ( heartrate6_t *ctx, uint8_t reg_addr, uint8_t data_in )
{
    uint8_t temp_data[ 2 ];
    
    if ( ( reg_addr < HEARTRATE6_RESET_REG ) || ( reg_addr > HEARTRATE6_MEAS_START_REG ) )
    {
        return HEARTRATE6_WRONG_ADDR;
    }
    
    temp_data[ 0 ] = reg_addr;
    temp_data[ 1 ] = data_in;

    i2c_master_write( &ctx->i2c, temp_data, 2 );   

    return HEARTRATE6_OK;
}

uint8_t heartrate6_write_bytes ( heartrate6_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_bytes )
{
    uint8_t temp_data[ 5 ];
    uint8_t cnt;
    
    if ( ( start_addr < HEARTRATE6_RESET_REG ) || ( start_addr > HEARTRATE6_MEAS_START_REG ) )
    {
        return HEARTRATE6_WRONG_ADDR;
    }
    if ( n_bytes > ( 0x44 - start_addr ) )
    {
        return HEARTRATE6_NBYTES_RANGE_ERROR;
    }
    
    temp_data[ 0 ] = start_addr;

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        temp_data[ cnt + 1 ] = data_in[ cnt ];
    }

    i2c_master_write( &ctx->i2c, temp_data, n_bytes + 1 );   
    
    return HEARTRATE6_OK;
}

uint8_t heartrate6_read_bytes( heartrate6_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_bytes )
{
    uint8_t reg_addr = start_addr;
    uint8_t ret_val;
    
    ret_val = check_addr ( reg_addr );
    
    if ( ret_val == HEARTRATE6_WRONG_ADDR )
    {
        return ret_val;
    }

    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, data_out, n_bytes );
    
    return ret_val;
}

void heartrate6_start_measure ( heartrate6_t *ctx )
{
    heartrate6_write_single_byte( ctx, HEARTRATE6_MEAS_START_REG, HEARTRATE6_START_MEAS );
}

void heartrate6_reset ( heartrate6_t *ctx )
{
    heartrate6_write_single_byte( ctx, HEARTRATE6_RESET_REG, HEARTRATE6_RESET_CMD );
    Delay_100ms();
    Delay_100ms();
}

void heartrate6_set_freq ( heartrate6_t *ctx, uint8_t freq_data )
{
    heartrate6_write_single_byte( ctx, HEARTRATE6_MEAS_CTRL1_REG, freq_data );
    
    if ( ( freq_data & 0x03 ) == HEARTRATE6_DATAREAD_FREQ_64HZ )
    {
        ctx->res = 7370.0 * 0.0019;
    }
    else
    {
        ctx->res = 14740.0 * 0.0019;
    }
    ctx->wait_time = ( uint8_t ) ctx->res;
}

void heartrate6_get_data ( heartrate6_t *ctx, uint16_t *led_off_data, uint16_t *led_on_data )
{
    uint8_t data_buff[ 4 ];
    
    heartrate6_read_bytes( ctx, HEARTRATE6_DATA_LEDOFF_LSB_REG, data_buff, 4 );
    
    *led_off_data = data_buff[ 1 ];
    *led_off_data <<= 8;
    *led_off_data |= data_buff[ 0 ];
    
    *led_on_data = data_buff[ 3 ];
    *led_on_data <<= 8;
    *led_on_data |= data_buff[ 2 ];
}

void heartrate6_wait_measure( heartrate6_t *ctx )
{
    uint8_t cnt;
    
    for ( cnt = 0; cnt < ctx->wait_time; cnt++ )
    {
         Delay_1ms( );
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t check_addr ( uint8_t register_addr )
{
    switch ( register_addr )
    {
        case HEARTRATE6_MANUFACT_ID_REG1 :
        {
            return HEARTRATE6_OK;
        }
        case HEARTRATE6_MANUFACT_ID_REG2 :
        {
            return HEARTRATE6_OK;
        }
        case HEARTRATE6_PART_ID_REG :
        {
            return HEARTRATE6_OK;
        }
        case HEARTRATE6_RESET_REG :
        {
            return HEARTRATE6_OK;
        }
        case HEARTRATE6_MEAS_CTRL1_REG :
        {
            return HEARTRATE6_OK;
        }
        case HEARTRATE6_MEAS_CTRL2_REG :
        {
            return HEARTRATE6_OK;
        }
        case HEARTRATE6_MEAS_START_REG :
        {
            return HEARTRATE6_OK;
        }
        case HEARTRATE6_DATA_LEDOFF_LSB_REG :
        {
            return HEARTRATE6_OK;
        }
        case HEARTRATE6_DATA_LEDOFF_MSB_REG :
        {
            return HEARTRATE6_OK;
        }
        case HEARTRATE6_DATA_LEDON_LSB_REG :
        {
            return HEARTRATE6_OK;
        }
        case HEARTRATE6_DATA_LEDON_MSB_REG :
        {
            return HEARTRATE6_OK;
        }
        default :
        {
            return HEARTRATE6_WRONG_ADDR;
        }
    }
}

// ------------------------------------------------------------------------- END

