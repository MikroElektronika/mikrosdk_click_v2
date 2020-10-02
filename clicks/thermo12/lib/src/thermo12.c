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

#include "thermo12.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo12_cfg_setup ( thermo12_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->ct   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMO12_DEVICE_ADDRESS_1;
}

THERMO12_RETVAL thermo12_init ( thermo12_t *ctx, thermo12_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMO12_INIT_ERROR;
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );


    // Input pins
    
    digital_in_init( &ctx->ct, cfg->ct );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return THERMO12_OK;

}

uint8_t thermo12_default_cfg ( thermo12_t *ctx )
{
    uint8_t aux_reg_value;

    thermo12_soft_reset( ctx );
    Delay_100ms( );
    thermo12_get( ctx, THERMO12_REG_ID, &aux_reg_value, 1 );

    if ( aux_reg_value != 0xCB )
    {
     return 1;
    }

    aux_reg_value = 0x93;
    thermo12_set( ctx, THERMO12_REG_CONFIG, &aux_reg_value, 1 );

    return 0;
}

uint8_t thermo12_set ( thermo12_t *ctx, uint8_t reg_address, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    if ( len > 2)
    {
        return 1;
    }
    tx_buf[ 0 ] = reg_address;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

uint8_t thermo12_get ( thermo12_t *ctx, uint8_t reg_address, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];

    if ( len > 2)
    {
        return 1;
    }
    tx_buf[ 0 ] = reg_address;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_buf, len );
}

uint8_t thermo12_int_get( thermo12_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t thermo12_ct_get( thermo12_t *ctx )
{
    return digital_in_read ( &ctx->ct );
}

void thermo12_soft_reset ( thermo12_t *ctx )
{
    uint8_t aux_reg_address;
    
    aux_reg_address = THERMO12_REG_SOFT_RESET;
    thermo12_set( ctx, aux_reg_address, 0, 0 );

}


float thermo12_get_temperature ( thermo12_t *ctx )
{
    uint8_t aux_buffer[ 2 ];
    int16_t aux_temp;
    float temp_retval;
    
    thermo12_get( ctx, THERMO12_REG_TEMP_MSB, aux_buffer, 2 );
    
    aux_temp = 0;
    aux_temp |= aux_buffer[ 0 ];
    aux_temp <<= 8;
    aux_temp |= aux_buffer[ 1 ];
    aux_temp &= 0xFFF8;
    
    temp_retval = ( float )( aux_temp );
    temp_retval *= 0.0078;
    
    return temp_retval;
}

uint8_t thermo12_get_status ( thermo12_t *ctx )
{
    uint8_t aux_reg_val;

    thermo12_get( ctx, THERMO12_REG_STATUS, &aux_reg_val, 1 );
    
    return aux_reg_val;
}

uint8_t thermo12_set_high_threshold ( thermo12_t *ctx, float high_threshold )
{
    uint8_t aux_buffer[ 2 ];
    int16_t aux_high_thres;
    
    if ( high_threshold > 150.0 ) return 1;
    if ( high_threshold < -40.0 ) return 1;
    
    aux_buffer[ 0 ] = 0x00;
    aux_buffer[ 1 ] = 0x00;
    
    high_threshold /= 0.0078;
    aux_high_thres = ( int16_t )( high_threshold );
    aux_buffer[ 0 ] = ( uint8_t )( aux_high_thres >> 8 );
    aux_buffer[ 1 ] = ( uint8_t )( aux_high_thres & 0x00FF );

    thermo12_set( ctx, THERMO12_REG_T_HIGH_SETP_MSB, aux_buffer, 2 );

    return 0;
}

uint8_t thermo12_set_low_threshold ( thermo12_t *ctx, float low_threshold )
{
    uint8_t aux_buffer[ 2 ];
    int16_t aux_low_thres;

    if ( low_threshold > 150.0 ) 
    {
        return 1;
    }
    if ( low_threshold < -40.0 ) 
    {
        return 1;
    }
    aux_buffer[ 0 ] = 0x00;
    aux_buffer[ 1 ] = 0x00;

    low_threshold /= 0.0078;
    aux_low_thres = ( int16_t )( low_threshold );
    aux_buffer[ 0 ] = ( uint8_t )( aux_low_thres >> 8 );
    aux_buffer[ 1 ] = ( uint8_t )( aux_low_thres & 0x00FF );

    thermo12_set( ctx, THERMO12_REG_T_LOW_SETP_MSB, aux_buffer, 2 );

    return 0;
}

uint8_t thermo12_set_critical_threshold( thermo12_t *ctx, float critical_threshold )
{
    uint8_t aux_buffer[ 2 ];
    int16_t aux_crit_thres;

     if ( critical_threshold > 150.0 ) 
    {
        return 1;
    }
    if ( critical_threshold < -40.0 ) 
    {
        return 1;
    }

    aux_buffer[ 0 ] = 0x00;
    aux_buffer[ 1 ] = 0x00;

    critical_threshold /= 0.0078;
    aux_crit_thres = ( int16_t )( critical_threshold );
    aux_buffer[ 0 ] = ( uint8_t )( aux_crit_thres >> 8 );
    aux_buffer[ 1 ] = ( uint8_t )( aux_crit_thres & 0x00FF );

    thermo12_set( ctx, THERMO12_REG_T_CRIT_SETP_MSB, aux_buffer, 2 );
    
    return 0;
}

uint8_t thermo12_set_hysteresis( thermo12_t *ctx, uint8_t hysteresis_value )
{
    if ( hysteresis_value > 15 ) return 1;
    
    thermo12_set( ctx, THERMO12_REG_T_HYST_SETP, &hysteresis_value, 1 );
    
    return 0;
}

// ------------------------------------------------------------------------- END

