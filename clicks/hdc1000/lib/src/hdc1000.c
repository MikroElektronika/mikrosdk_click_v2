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

#include "hdc1000.h"

// ------------------------------------------------------------- PRIVATE MACROS 

// Slave address

               
// Value for 14-bit resolution calculation

#define HDC1000_TEMP_CONST           0.0025177          
#define HDC1000_HUMI_CONST           0.0015259

// Temperature calculation factor

#define HDC1000_TEMP_CALC_FACT       40

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_comm_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hdc1000_cfg_setup ( hdc1000_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = HDC1000_SLAVE_ADDRESS;
}

HDC1000_RETVAL hdc1000_init ( hdc1000_t *ctx, hdc1000_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) != I2C_MASTER_SUCCESS )
    {
        return HDC1000_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->rdy, cfg->rdy );
    
    return HDC1000_OK;

}

void hdc1000_default_cfg ( hdc1000_t *ctx )
{
    // Click default configuration
    
    uint8_t def_buf[ 2 ];
    def_buf[ 0 ] = HDC1000_BOTH_TEMP_HUMI;
    def_buf[ 1 ] = HDC1000_TEMP_HUMI_14BIT;
    
    hdc1000_generic_write( ctx, HDC1000_REG_CONFIG, def_buf, 2 );
}

void hdc1000_generic_write ( hdc1000_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void hdc1000_generic_read ( hdc1000_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

float hdc1000_get_temperature_data ( hdc1000_t *ctx )
{
    float temperature;
    uint16_t temp_data;
    uint8_t rx_buf[ 2 ];

    hdc1000_generic_read( ctx, HDC1000_REG_TEMP, rx_buf, 2 );
    
    temp_data = rx_buf[ 0 ];
    temp_data <<= 8;
    temp_data |= rx_buf[ 1 ];

    temperature = ( float ) temp_data;
    temperature *= HDC1000_TEMP_CONST;
    temperature -= HDC1000_TEMP_CALC_FACT;
    
    return temperature;
}

float hdc1000_get_humidity_data ( hdc1000_t *ctx )
{
    uint16_t hum_data;
    float humidity;
    uint8_t rx_buffer[ 2 ];

    hdc1000_generic_read( ctx, HDC1000_REG_HUMI, rx_buffer, 2 );
    hum_data = rx_buffer[ 0 ];
    hum_data <<= 8;
    hum_data |= rx_buffer[ 1 ];
    
    humidity = ( float ) hum_data;
    humidity *= HDC1000_HUMI_CONST;

    return humidity;
}

uint8_t hdc1000_get_interrupt ( hdc1000_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_comm_delay ( void )
{
    Delay_10ms();
    Delay_10ms();
}

// ------------------------------------------------------------------------- END

