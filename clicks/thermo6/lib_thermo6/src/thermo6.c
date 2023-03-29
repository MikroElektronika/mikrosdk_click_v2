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

#include "thermo6.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Write data function
 *
 * @param reg_addr  8-bit register address
 * @param tx_data   16-bit data to be written into register
 *
 * @note Function writes 2 bytes of data into specified, register.
 */
static void write_data_u16 ( thermo6_t *ctx, uint8_t reg_addr, uint16_t tx_data );

/**
 * @brief Read data function
 *
 * @param reg_addr 8-bit register address
 *
 * @returns 16-bit data from address specified register
 *
 * @note Function reads 2 bytes of data from specified, register.
 */
static uint16_t read_data_u16 ( thermo6_t *ctx, uint8_t reg_addr );

/**
 * @brief Get resolutions parametar
 *
 * @param res Resolutions
 *
 * @returns resolutions value
 */
static float get_resolution_param ( uint8_t res );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo6_cfg_setup ( thermo6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMO6_SLAVE_ADDRESS;
}

THERMO6_RETVAL thermo6_init ( thermo6_t *ctx, thermo6_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMO6_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    ctx->temp_resolution = THERMO6_TEMP_RESOLUTION_12bit;

    return THERMO6_OK;
}

void thermo6_default_cfg ( thermo6_t *ctx )
{
    // Click default configuration

    thermo6_set_register_cfg ( ctx, THERMO6_CFG_CONVERSION_RATE_8 |
                                    THERMO6_CFG_PEC_ENABLE | THERMO6_CFG_TIMEOUT_ENABLE |
                                    THERMO6_CFG_RESOLUTION_12 | THERMO6_CFG_NORMAL_FORMAT |
                                    THERMO6_CFG_POWER_UP | THERMO6_CFG_COMPARATOR_MODE |
                                    THERMO6_CFG_FAULT_QUEUE_1 );
}

void thermo6_generic_write ( thermo6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void thermo6_generic_read ( thermo6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

float thermo6_get_temperature_data ( thermo6_t *ctx, uint8_t temp_format )
{
    uint16_t tmp;
    uint8_t rx_buf[ 2 ];
    float temperature;
    uint8_t temp_res;

    temp_res = get_resolution_param( ctx->temp_resolution );

    tmp = read_data_u16( ctx, THERMO6_REG_TEMPERATURE );

    rx_buf[ 0 ] = ( uint8_t )( tmp >> 4 );
    rx_buf[ 0 ] &= 0x07;
    rx_buf[ 1 ] = ( uint8_t )( tmp >> 8 );

    if( rx_buf[ 1 ] > 0x79 )
    {
        rx_buf[ 1 ] = ( ~rx_buf[ 1 ] ) + 1;
        temperature = ( float )rx_buf[ 1 ] + ( ( float )rx_buf[ 0 ] * temp_res );
        temperature *= -1.0;
    }
    else
    {
        temperature = ( float )rx_buf[ 1 ] + ( ( float )rx_buf[ 0 ] * temp_res );
    }

    if ( temp_format == THERMO6_TEMP_FORMAT_KELVIN )
    {
        temperature += 273.15;
    }
    else if ( temp_format == THERMO6_TEMP_FORMAT_FAHRENHEIT )
    {
        temperature = temperature * 1.8 + 32;
    }
    return temperature;
}

void thermo6_set_other_register ( thermo6_t *ctx, uint8_t reg, float tx_data )
{
    uint16_t dec_val;
    uint16_t wr_data;

    dec_val = tx_data * 16;

    if ( dec_val < 0 )
    {
        wr_data = ( ~dec_val ) + 1;
        wr_data <<= 4;

        write_data_u16( ctx, reg, wr_data );
    }
    else
    {
        dec_val <<= 4;
        write_data_u16( ctx, reg, dec_val );
    }
}

float thermo6_get_other_register( thermo6_t *ctx, uint8_t reg )
{
    uint16_t temp;
    uint8_t buff[ 2 ];
    float result = 0;
    uint8_t temp_res;

    temp_res = get_resolution_param( ctx->temp_resolution );

    temp = read_data_u16( ctx, reg );

    buff[ 0 ] = ( uint8_t )( temp >> 4 );
    buff[ 0 ] &= 0x07;
    buff[ 1 ] = ( uint8_t )( temp >> 8 );

    if(  buff[ 1 ] > 0x79 )
    {
        buff[ 1 ] = ( ~ buff[ 1 ] ) + 1;
        result = ( float )  buff[ 1 ] + ( ( float ) buff[ 0 ] * temp_res );
        result *= -1.0;
    }
    else
    {
        result = ( float ) buff[ 1 ] + ( ( float ) buff[ 0 ] * temp_res );
    }
    return result;
}

uint8_t thermo6_get_over_temp_status( thermo6_t *ctx )
{
    uint16_t temp;
    uint8_t result;

    temp = read_data_u16( ctx, THERMO6_REG_CONFIG );

    result = temp >> 15;
    result &= 0x01;

    return result;
}

void thermo6_set_register_cfg ( thermo6_t *ctx, uint16_t cfg_data )
{
    uint8_t res;

    write_data_u16( ctx, THERMO6_REG_CONFIG, cfg_data );

    res = (uint8_t)( cfg_data >> 5 ) & 0x03;
    ctx->temp_resolution = res;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// Write data function

static void write_data_u16 ( thermo6_t *ctx, uint8_t reg_addr, uint16_t tx_data )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = ( uint8_t ) tx_data;
    tx_buf[ 1 ] = ( uint8_t )( tx_data >> 8 );

    thermo6_generic_write( ctx, reg_addr, tx_buf, 2 );
}

// Read data function

static uint16_t read_data_u16 ( thermo6_t *ctx, uint8_t reg_addr )
{
    uint16_t rx_data;
    uint8_t rx_buf[ 2 ];

    thermo6_generic_read( ctx, reg_addr, rx_buf, 2 );

    rx_data = rx_buf[ 0 ];
    rx_data <<= 8;
    rx_data |= rx_buf[ 1 ];

    return rx_data;
}

static float get_resolution_param ( uint8_t res )
{
    float param;

    switch ( res )
    {
        case THERMO6_TEMP_RESOLUTION_8bit: // 8 bit
        {
            param = 1;
            break;
        }
        case THERMO6_TEMP_RESOLUTION_9bit: // 9 bit
        {
            param = 0.5;
            break;
        }
        case THERMO6_TEMP_RESOLUTION_10bit: // 10 bit
        {
            param = 0.25;
            break;
        }
        case THERMO6_TEMP_RESOLUTION_12bit: // 12 bit
        {
            param = 0.0625;
            break;
        }
        default:
        {
            param = 0.0625;
            break;
        }
    }
    return param;
}

// ------------------------------------------------------------------------- END

