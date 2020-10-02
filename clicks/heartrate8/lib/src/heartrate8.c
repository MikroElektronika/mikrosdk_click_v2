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

#include "heartrate8.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void heartrate8_cfg_setup ( heartrate8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = HEARTRATE8_SLAVE_ADDR;
}

HEARTRATE8_RETVAL heartrate8_init ( heartrate8_t *ctx, heartrate8_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HEARTRATE8_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return HEARTRATE8_OK;
}

void heartrate8_default_cfg ( heartrate8_t *ctx )
{
    heartrate8_reset( ctx );
    heartrate8_write_single_byte( ctx, HEARTRATE8_MEAS_CTRL1_REG, HEARTRATE8_OSC_ACTIVE | HEARTRATE8_GREEN_MEAS_MODE | HEARTRATE8_SINGLE_MEAS_MODE );
    heartrate8_write_single_byte( ctx, HEARTRATE8_MEAS_CTRL2_REG, HEARTRATE8_LEDS_PULSED | HEARTRATE8_LED_CURR_2MA );
    heartrate8_write_single_byte( ctx, HEARTRATE8_MEAS_CTRL3_REG, HEARTRATE8_LED3_ON | HEARTRATE8_LED_CURR_10MA );
    heartrate8_write_single_byte( ctx, HEARTRATE8_MEAS_CTRL5_REG, HEARTRATE8_INT_MEAS_COMPLET );
}

uint8_t heartrate8_write_single_byte ( heartrate8_t *ctx, uint8_t reg_addr, uint8_t data_in )
{
    uint8_t temp_data[ 2 ];

    if ( ( reg_addr < HEARTRATE8_RESET_REG ) || ( reg_addr > HEARTRATE8_MEAS_SYNC_REG ) )
    {
        return HEARTRATE8_WRONG_ADDR;
    }

    temp_data[ 0 ] = reg_addr;
    temp_data[ 1 ] = data_in;   

    i2c_master_write( &ctx->i2c, temp_data, 2 ); 

    return HEARTRATE8_OK;
}

uint8_t heartrate8_write_bytes ( heartrate8_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_bytes )
{
    uint8_t temp_data[ 10 ];
    uint8_t cnt;

    if ( ( start_addr < HEARTRATE8_RESET_REG ) || ( start_addr > HEARTRATE8_MEAS_SYNC_REG ) )
    {
        return HEARTRATE8_WRONG_ADDR;
    }
    if ( n_bytes > ( 0x49 - start_addr ) )
    {
        return HEARTRATE8_NBYTES_RANGE_ERROR;
    }

    temp_data[ 0 ] = start_addr;

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        temp_data[ cnt + 1 ] = data_in[ cnt ];
    }

    i2c_master_write( &ctx->i2c, temp_data, n_bytes + 1 );   

    return HEARTRATE8_OK;
}

uint8_t heartrate8_read_bytes ( heartrate8_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_bytes )
{
    uint8_t reg_addr = start_addr;

    if ( ( ( start_addr < 0x40 ) && ( start_addr != 0x0F ) && ( start_addr != 0x10 ) ) || ( start_addr == 0x49 ) || ( start_addr == 0x4A ) || ( start_addr > 0x58 ) )
    {
        return HEARTRATE8_WRONG_ADDR;
    }

    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, data_out, n_bytes );

    return HEARTRATE8_OK;
}

void heartrate8_start_measure ( heartrate8_t *ctx )
{
    heartrate8_write_single_byte( ctx, HEARTRATE8_MEAS_START_REG, HEARTRATE8_MEAS_START_CMD );
}

void heartrate8_reset ( heartrate8_t *ctx )
{
    heartrate8_write_single_byte( ctx, HEARTRATE8_RESET_REG, HEARTRATE8_RESET_CMD );
    Delay_100ms( );
}

void heartrate8_meas_sync ( heartrate8_t *ctx )
{
    heartrate8_write_single_byte( ctx, HEARTRATE8_MEAS_SYNC_REG, HEARTRATE8_MEAS_SYNC_CMD );
}

uint8_t heartrate8_int_clear ( heartrate8_t *ctx )
{
    uint8_t int_byte;
    
    heartrate8_read_bytes( ctx, HEARTRATE8_INT_CLEAR_REG, &int_byte, 1 );
    
    return int_byte;
}

uint8_t heartrate8_check_int ( heartrate8_t *ctx )
{
    if ( digital_in_read( &ctx->int_pin ) )
    {
        return HEARTRATE8_INT_INACTIVE;
    }
    else
    {
        return HEARTRATE8_INT_ACTIVE;
    }
}

uint8_t heartrate8_get_data ( heartrate8_t *ctx, uint8_t data_select, uint16_t *led_out_on, uint16_t *led_out_off )
{
    uint8_t temp_data[ 4 ];
    uint8_t register_addr;
    
    switch ( data_select )
    {
        case HEARTRATE8_FIFO_DATA_GET :
        {
            register_addr = HEARTRATE8_FIFO_DATA0_LSB_REG;
        break;
        }
        case HEARTRATE8_IR_DATA_GET :
        {
            register_addr = HEARTRATE8_IRDATA_LEDOFF_LSB_REG;
        break;
        }
        case HEARTRATE8_GREEN_DATA_GET :
        {
            register_addr = HEARTRATE8_GDATA_LEDOFF_LSB_REG;
        break;
        }
        default :
        {
            return HEARTRATE8_DATA_SEL_ERROR;
        }
    }
    
    heartrate8_read_bytes( ctx, register_addr, temp_data, 4 );
    
    *led_out_off = temp_data[ 1 ];
    *led_out_off <<= 8;
    *led_out_off |= temp_data[ 0 ];
    
    *led_out_on = temp_data[ 3 ];
    *led_out_on <<= 8;
    *led_out_on |= temp_data[ 2 ];
    
    return HEARTRATE8_OK;
}

// ------------------------------------------------------------------------- END

