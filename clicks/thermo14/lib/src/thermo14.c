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

#include "thermo14.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo14_cfg_setup ( thermo14_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMO14_I2C_ADR_GND;
}

THERMO14_RETVAL thermo14_init ( thermo14_t *ctx, thermo14_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMO14_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return THERMO14_OK;
}

void thermo14_default_cfg ( thermo14_t *ctx )
{
    uint8_t tmp;

    thermo14_sensor_enable( ctx );

    tmp = THERMO14_SW_RST_LOW_ODR_EN | THERMO14_SW_RST_RST_CMD;
    thermo14_generic_write( ctx, THERMO14_SW_RST, &tmp, 1 );
    
    tmp = THERMO14_SW_RST_LOW_ODR_EN;
    thermo14_generic_write( ctx, THERMO14_SW_RST, &tmp, 1 );
    thermo14_high_temp_trsh( ctx, 49.5 );
    thermo14_low_temp_trsh( ctx, 2.5 );
    
    tmp = THERMO14_CTL_LOW_ODR_ST | 
    THERMO14_CTL_BDU | THERMO14_CTL_AVG_8 | THERMO14_CTL_IF_ADR_INC | 
    THERMO14_CTL_TIME_OUT_DIS | THERMO14_CTL_ONE_SHOT;
    thermo14_generic_write( ctx, THERMO14_CTL, &tmp, 1 ); 
}

void thermo14_generic_write ( thermo14_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void thermo14_generic_read ( thermo14_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}
void thermo14_reset ( thermo14_t *ctx )
{
    uint8_t aux_reg_val;

    thermo14_generic_read( ctx, THERMO14_SW_RST, &aux_reg_val, 1 );
    aux_reg_val |= THERMO14_SW_RST_RST_CMD;
    thermo14_generic_write( ctx, THERMO14_SW_RST, &aux_reg_val, 1 );
    Delay_10ms( );
    thermo14_generic_read( ctx, THERMO14_SW_RST, &aux_reg_val, 1 );
    aux_reg_val &= ~THERMO14_SW_RST_RST_CMD;
    thermo14_generic_write( ctx, THERMO14_SW_RST, &aux_reg_val, 1 );
}

void thermo14_sensor_enable ( thermo14_t *ctx )
{
    uint8_t tmp;
    tmp = THERMO14_CTL_BDU | THERMO14_CTL_IF_ADR_INC;
    thermo14_generic_write( ctx, THERMO14_CTL, &tmp, 1 );
    thermo14_reset( ctx );
}

int16_t thermo14_temp_raw_get ( thermo14_t *ctx )
{
    uint8_t tmp[ 2 ];
    int16_t temp_raw;

    thermo14_generic_read( ctx, THERMO14_TEMP_L_OUT, &tmp[ 0 ], 1 );

    thermo14_generic_read( ctx, THERMO14_TEMP_H_OUT, &tmp[ 1 ], 1 );
    temp_raw = tmp[ 1 ] << 8;
    temp_raw |= tmp[ 0 ];

    return temp_raw;
}

float thermo14_raw_to_celsius ( thermo14_t *ctx, int16_t temp_raw )
{
    return ( ( float )temp_raw / 100.0 );
}

float thermo14_get_temperature ( thermo14_t *ctx )
{
    int16_t raw_temp;
    float temperature;

    raw_temp = thermo14_temp_raw_get( ctx );

    temperature = thermo14_raw_to_celsius( ctx, raw_temp );

    return temperature;
}

uint8_t thermo14_get_int ( thermo14_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void thermo14_low_temp_trsh ( thermo14_t *ctx, float trsh_val )
{
    uint8_t raw_value;

    raw_value = ( uint8_t )( ( trsh_val / 0.64 ) + 63.0 );
    thermo14_generic_write ( ctx, THERMO14_TEMP_L_LIMIT, &raw_value, 1 );
}

void thermo14_high_temp_trsh ( thermo14_t *ctx, float trsh_val )
{
    uint8_t raw_value;

    raw_value = (uint8_t)( ( trsh_val / 0.64 ) + 63.0 );
    thermo14_generic_write ( ctx, THERMO14_TEMP_H_LIMIT, &raw_value, 1 );
}

// ------------------------------------------------------------------------- END

