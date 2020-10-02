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

#include "surfacetemp.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void surfacetemp_cfg_setup ( surfacetemp_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = SURFACETEMP_SLAVE_DEVICE_ADDR_0_0;
}

SURFACETEMP_RETVAL surfacetemp_init ( surfacetemp_t *ctx, surfacetemp_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return SURFACETEMP_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->pwm, cfg->pwm );

    return SURFACETEMP_OK;
}

void surfacetemp_generic_write ( surfacetemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void surfacetemp_generic_read ( surfacetemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t surfacetemp_get_pwm_pin ( surfacetemp_t *ctx )
{
    return digital_in_read( &ctx->pwm );
}

void surfacetemp_soft_reset ( surfacetemp_t *ctx )
{
    uint8_t tx_data;

    tx_data = SURFACETEMP_REG_SOFT_RESET;

    i2c_master_write( &ctx->i2c, &tx_data, 1 );
}

float surfacetemp_get_temperature ( surfacetemp_t *ctx )
{
    uint8_t rx_buff[ 2 ];
    int16_t temp;
    float temperature;

    surfacetemp_generic_read( ctx, SURFACETEMP_REG_TEMP_MSB, rx_buff, 2 );

    temp = rx_buff[ 0 ];
    temp <<= 8;
    temp |= rx_buff[ 1 ];
    temp &= 0xFFF8;

    temperature = ( float ) ( temp );
    temperature *= 0.0078;

    return temperature;
}

uint8_t surfacetemp_get_status ( surfacetemp_t *ctx )
{
    uint8_t status;

    surfacetemp_generic_read( ctx, SURFACETEMP_REG_STATUS, &status, 1 );

    return status;
}

uint8_t surfacetemp_set_high_threshold ( surfacetemp_t *ctx, float high_threshold )
{
    uint8_t tx_buff[ 2 ];
    int16_t high_thres;

    if ( high_threshold > 150.0 || high_threshold < -40.0 )
    {
        return DEVICE_ERROR;
    }

    high_thres = ( int16_t ) ( high_threshold / 0.0078 );
    tx_buff[ 0 ] = ( uint8_t ) ( high_thres >> 8 );
    tx_buff[ 1 ] = ( uint8_t ) ( high_thres & 0x00FF );

    surfacetemp_generic_write( ctx, SURFACETEMP_REG_T_HIGH_SETP_MSB, tx_buff, 2 );

    return DEVICE_OK;
}

uint8_t surfacetemp_set_low_threshold ( surfacetemp_t *ctx, float high_threshold )
{
    uint8_t tx_buff[ 2 ];
    int16_t high_thres;

    if ( high_threshold > 150.0 || high_threshold < -40.0 )
    {
        return DEVICE_ERROR;
    }

    high_thres = ( int16_t ) ( high_threshold / 0.0078 );
    tx_buff[ 0 ] = ( uint8_t ) ( high_thres >> 8 );
    tx_buff[ 1 ] = ( uint8_t ) ( high_thres & 0x00FF );

    surfacetemp_generic_write( ctx, SURFACETEMP_REG_T_LOW_SETP_MSB, tx_buff, 2 );

    return DEVICE_OK;
}

uint8_t surfacetemp_set_critical_threshold ( surfacetemp_t *ctx, float high_threshold )
{
    uint8_t tx_buff[ 2 ];
    int16_t high_thres;

    if ( high_threshold > 150.0 || high_threshold < -40.0 )
    {
        return DEVICE_ERROR;
    }

    high_thres = ( int16_t ) ( high_threshold / 0.0078 );
    tx_buff[ 0 ] = ( uint8_t ) ( high_thres >> 8 );
    tx_buff[ 1 ] = ( uint8_t ) ( high_thres & 0x00FF );

    surfacetemp_generic_write( ctx, SURFACETEMP_REG_T_CRIT_SETP_MSB, tx_buff, 2 );

    return DEVICE_OK;
}

uint8_t surfacetemp_set_hysteresis ( surfacetemp_t *ctx, uint8_t hysteresis )
{
    if ( hysteresis > 15 )
    {
        return DEVICE_ERROR;
    }
    surfacetemp_generic_write( ctx, SURFACETEMP_REG_T_HYST_SETP, &hysteresis, 1 );

    return DEVICE_OK;
}

uint8_t surfacetemp_setup ( surfacetemp_t *ctx )
{
    uint8_t tmp;

    surfacetemp_soft_reset( ctx );
    Delay_100ms( );
    surfacetemp_generic_read( ctx, SURFACETEMP_REG_ID, &tmp, 1 );

    if ( tmp != 0xCB )
    {
        return DEVICE_ERROR;
    }
    tmp = 0x93;
    surfacetemp_generic_write( ctx, SURFACETEMP_REG_CONFIG, &tmp, 1 );

    return DEVICE_OK;
}

// ------------------------------------------------------------------------- END

