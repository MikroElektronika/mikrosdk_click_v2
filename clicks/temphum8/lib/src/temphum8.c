/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright ( c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 */

#include "temphum8.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define RESOLUTION_8  256
#define RESOLUTION_10 1024
#define RESOLUTION_11 2048
#define RESOLUTION_12 4096
#define RESOLUTION_13 8192
#define RESOLUTION_14 16384

#define POLYNOMIAL 0x131  // P(x)=x^8+x^5+x^4+1 = 100110001

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t dev_crc8 ( uint8_t *data_buffer, uint8_t n_bytes, uint8_t checksum );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum8_cfg_setup ( temphum8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TEMPHUM8_DEVICE_SLAVE_ADDRESS;
}

TEMPHUM8_RETVAL temphum8_init ( temphum8_t *ctx, temphum8_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM8_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    return TEMPHUM8_OK;
}

void temphum8_default_cfg ( temphum8_t *ctx )
{
    temphum8_set_cfg_register( ctx, TEMPHUM8_CFG_RESOLUTION_H12_T14 |
                                        TEMPHUM8_CFG_ENABLE_ON_CHIP_HEATER |
                                        TEMPHUM8_CFG_DISABLE_OTP_RELOAD );
}

void temphum8_generic_write ( temphum8_t *ctx, uint8_t reg, uint8_t *data_buffer, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buffer[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
}

void temphum8_generic_read ( temphum8_t *ctx, uint8_t reg, uint8_t *data_buffer, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buffer, len );
}

void temphum8_software_reset ( temphum8_t *ctx )
{
    uint8_t rst_cmd = TEMPHUM8_SOFT_RESET;
    i2c_master_write( &ctx->i2c, &rst_cmd, 1 ); 
    Delay_100ms();
}

void temphum8_set_cfg_register ( temphum8_t *ctx, uint8_t cfg )
{
    uint8_t tx_buffer[ 1 ];

    tx_buffer[ 0 ] = 0x3A | cfg;

    temphum8_generic_write( ctx, TEMPHUM8_USER_REGISTER_WRITE, tx_buffer, 1 );

    if ( ( cfg & TEMPHUM8_CFG_RESOLUTION_H8_T12 ) != 0 )
    {
        ctx->measure_resolution = 1;
    }
    else if ( ( cfg & TEMPHUM8_CFG_RESOLUTION_H10_T13 ) != 0 )
    {
        ctx->measure_resolution = 2;
    }
    else if ( ( cfg & TEMPHUM8_CFG_RESOLUTION_H11_T11 ) != 0 )
    {
        ctx->measure_resolution = 3;
    }
    else
    {
        ctx->measure_resolution = 0;
    }
}

float temphum8_get_temperature_data ( temphum8_t *ctx, uint8_t temp_format )
{
    uint16_t raw_temp;
    float temperature;
    uint16_t res;
    uint8_t rx_buffer[ 3 ];

    temphum8_generic_read( ctx, TEMPHUM8_TEMP_MEASUREMENT_HOLD_MODE, rx_buffer, 3 );

    raw_temp = rx_buffer[ 0 ];
    raw_temp <<= 8;
    raw_temp |= rx_buffer[ 1 ];

    if ( dev_crc8( rx_buffer, 2, rx_buffer[ 2 ] ) )
    {
        temphum8_software_reset( ctx );
        return 1;
    }

    if ( ctx->measure_resolution == 0 )
    {
        raw_temp = ( raw_temp >> 2 );
        res = RESOLUTION_14;
    }
    else if ( ctx->measure_resolution == 1 )
    {
        raw_temp = ( raw_temp >> 4 );
        res = RESOLUTION_12;
    }
    else if ( ctx->measure_resolution == 2 )
    {
        raw_temp = ( raw_temp >> 3 );
        res = RESOLUTION_13;
    }
    else
    {
        raw_temp = ( raw_temp >> 5 );
        res = RESOLUTION_11;
    }

    temperature = ( -46.85 + 175.72 / res * ( float )raw_temp );

    if ( temp_format == TEMPHUM8_TEMPERATURE_IN_FARENHAJT )
    {
        return temperature * 9/5 + 32;
    }
    else if ( temp_format == TEMPHUM8_TEMPERATURE_IN_KELVIN )
    {
        return temperature + 273.15;
    }

    return temperature;
}


float temphum8_get_humidity_data ( temphum8_t *ctx )
{
    uint16_t raw_hum;
    uint16_t res;
    uint8_t rx_buffer[ 3 ];

    temphum8_generic_read( ctx, TEMPHUM8_HUM_MEASUREMENT_HOLD_MODE, rx_buffer, 3 );

    raw_hum = rx_buffer[ 0 ];
    raw_hum <<= 8;
    raw_hum |= rx_buffer[ 1 ];

    if ( dev_crc8( rx_buffer, 2, rx_buffer[ 2 ] ) )
    {
        temphum8_software_reset( ctx );
        return 1;
    }

    if ( ctx->measure_resolution == 0 )
    {
        raw_hum = raw_hum >> 4;
        res = RESOLUTION_12;
    }
    else if ( ctx->measure_resolution == 1 )
    {
        raw_hum = raw_hum >> 8;
        res = RESOLUTION_8;
    }
    else if ( ctx->measure_resolution == 2 )
    {
        raw_hum = raw_hum >> 6;
        res = RESOLUTION_10;
    }
    else
    {
        raw_hum = raw_hum >> 5;
        res = RESOLUTION_11;
    }

    return ( -6.0 + 125.0/ res * ( float )raw_hum );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t dev_crc8 ( uint8_t *data_buffer, uint8_t n_bytes, uint8_t checksum )
{
    uint8_t crc = 0;
    uint8_t byte_ctr;
    uint8_t n_bit;

    for ( byte_ctr = 0; byte_ctr < n_bytes; ++byte_ctr )
    {
        crc ^= ( data_buffer[ byte_ctr ] );
        for ( n_bit = 8; n_bit > 0; --n_bit )
        {
            if ( crc & 0x80 )
            {
                crc = ( crc << 1 ) ^ POLYNOMIAL;
            }
            else
            {
                crc = ( crc << 1 );
            }
        }
    }
    if ( crc != checksum )
    {
        return 1;
    }
    return 0;
}

// ------------------------------------------------------------------------- END

