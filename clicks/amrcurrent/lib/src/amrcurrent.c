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

#include "amrcurrent.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t averaging_data( amrcurent_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void amrcurent_cfg_setup ( amrcurent_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an  = HAL_PIN_NC;
    cfg->voc = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x4D;
}

AMRCURENT_RETVAL amrcurent_init ( amrcurent_t *ctx, amrcurent_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AMRCURENT_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->voc, cfg->voc );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->flt, cfg->flt );

    return AMRCURENT_OK;
}

void amrcurent_generic_write ( amrcurent_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void amrcurent_generic_read ( amrcurent_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t amrcurrent_read_value (  amrcurent_t *ctx )
{
    uint8_t cmd;
    uint8_t data_buf[ 2 ];
    uint16_t temp_data;

    cmd = 0x00;

    amrcurent_generic_read( ctx, cmd, data_buf, 2 );

    temp_data = data_buf[ 0 ];
    temp_data = temp_data << 8;
    temp_data = temp_data | data_buf[ 1 ];

    return temp_data;
}

uint8_t amrcurrent_get_int_pin_state ( amrcurent_t *ctx )
{
    uint8_t temp_data;
    temp_data = digital_in_read( &ctx->flt );
    return temp_data;
}

void amrcurrent_set_rst_pin_state ( amrcurent_t *ctx, uint8_t pin_state )
{
    if ( pin_state == 1 )
    {
        digital_out_high( &ctx->voc );
    }
    else
    {
       digital_out_low( &ctx->voc );  
    }
}

void amrcurrent_hw_reset ( amrcurent_t *ctx )
{
    digital_out_low( &ctx->voc );
    Delay_1ms(  );
    digital_out_high( &ctx->voc );
    Delay_1ms(  );
    digital_out_low( &ctx->voc );
    Delay_1ms(  );
}

float amrcurrent_get_current ( amrcurent_t *ctx )
{
    float current;
    float voltage;
    uint16_t sensor_value;
    uint8_t polarity_val = 1;

    sensor_value = averaging_data( ctx );

    if ( sensor_value < 2052 )
    {
        sensor_value = 2052 - sensor_value;
        polarity_val = 1;
    }
    else
    {
        sensor_value -= 2052;
        polarity_val = 0;
    }

    voltage = ( sensor_value / 3700.0 ) * 4590.0; 
    current  = ( voltage / 100.0 ) * 1000.0; 

    if ( polarity_val == 1 )
    {
        current = - current;
    }
    return current;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t averaging_data( amrcurent_t *ctx )
{
    uint32_t sum_data = 0;
    uint16_t new_data = 0;
    uint8_t cnt = 0;
    
    for ( cnt = 0; cnt < 10; cnt++ )
    {
        new_data = amrcurrent_read_value( ctx );
        sum_data = sum_data + new_data;
        Delay_10ms(  );
        Delay_10ms(  );
    }
    new_data = sum_data / 10;
    
    return new_data;
}

// ------------------------------------------------------------------------- END

