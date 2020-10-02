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

#include "remotetemp.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void remotetemp_cfg_setup ( remotetemp_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->thm = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = REMOTETEMP_DEVICE_ADDRESS_4p7;
}

REMOTETEMP_RETVAL remotetemp_init ( remotetemp_t *ctx, remotetemp_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return REMOTETEMP_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->thm, cfg->thm );
    digital_in_init( &ctx->alr, cfg->alr );

    return REMOTETEMP_OK;
}

void remotetemp_default_cfg ( remotetemp_t *ctx )
{
    uint8_t aux_reg_buf[ 1 ];
    uint8_t aux_reg_addr;

    aux_reg_addr = REMOTETEMP_CONFIG;
    if ( ctx->range_set == 1 ) 
    {
        aux_reg_buf[ 0 ] = 0x06;
    }
    if ( ctx->range_set == 0 ) 
    {
        aux_reg_buf[ 0 ] = 0x02;
    }
    remotetemp_write( ctx, aux_reg_addr, aux_reg_buf, 1 );

    aux_reg_addr = REMOTETEMP_CONVERT;
    aux_reg_buf[ 0 ] = 0x06;
    remotetemp_write( ctx, aux_reg_addr, aux_reg_buf, 1 );

    aux_reg_addr = REMOTETEMP_CONSEC_ALERT;
    aux_reg_buf[ 0 ] = 0x7E;
    remotetemp_write( ctx, aux_reg_addr, aux_reg_buf, 1 );

    aux_reg_addr = REMOTETEMP_EXT1_BETA_CONFIG;
    aux_reg_buf[ 0 ] = 0x10;
    remotetemp_write( ctx, aux_reg_addr, aux_reg_buf, 1 );

    aux_reg_addr = REMOTETEMP_EXT2_BETA_CONFIG;
    aux_reg_buf[ 0 ] = 0x10;
    remotetemp_write( ctx, aux_reg_addr, aux_reg_buf, 1 );

    aux_reg_addr = REMOTETEMP_HOTTEST_CONFIG;
    aux_reg_buf[ 0 ] = 0x27;
    remotetemp_write( ctx, aux_reg_addr, aux_reg_buf, 1 );

    aux_reg_addr = REMOTETEMP_THRM_HYS;
    aux_reg_buf[ 0 ] = 0x00;
    remotetemp_write( ctx, aux_reg_addr, aux_reg_buf, 1 );

    Delay_100ms( );
    remotetemp_set_int_diode_high_limit( ctx, 30 );
    remotetemp_set_int_diode_low_limit( ctx, 20 );
    remotetemp_set_ext_diode_high_limit( ctx, 30, REMOTETEMP_EXT_DIODE_1 );
    remotetemp_set_ext_diode_low_limit( ctx, 20, REMOTETEMP_EXT_DIODE_1 );
    remotetemp_set_ext_diode_high_limit( ctx, 30, REMOTETEMP_EXT_DIODE_2 );
    remotetemp_set_ext_diode_low_limit( ctx, 20, REMOTETEMP_EXT_DIODE_2 );
    remotetemp_set_ext_diode_high_limit( ctx, 30, REMOTETEMP_EXT_DIODE_3 );
    remotetemp_set_ext_diode_low_limit( ctx, 20, REMOTETEMP_EXT_DIODE_3 );
    remotetemp_set_ext_diode_high_limit( ctx, 30, REMOTETEMP_EXT_DIODE_4 );
    remotetemp_set_ext_diode_low_limit( ctx, 20, REMOTETEMP_EXT_DIODE_4 );
    remotetemp_set_int_diode_therm_limit( ctx, 30 );
    remotetemp_set_ext_diode_therm_limit( ctx, 30, REMOTETEMP_EXT_DIODE_1 );
    remotetemp_set_ext_diode_therm_limit( ctx, 30, REMOTETEMP_EXT_DIODE_2 );
    remotetemp_set_ext_diode_therm_limit( ctx, 30, REMOTETEMP_EXT_DIODE_3 );
    remotetemp_set_ext_diode_therm_limit( ctx, 30, REMOTETEMP_EXT_DIODE_4 );
}

void remotetemp_generic_write ( remotetemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void remotetemp_generic_read ( remotetemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t remotetemp_int_get ( remotetemp_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

uint8_t remotetemp_an_get ( remotetemp_t *ctx )
{
    return digital_in_read( &ctx->thm );
}

uint8_t remotetemp_set_range( remotetemp_t *ctx, uint8_t range_setting )
{
    if ( range_setting == 0 ) 
    { 
        ctx->range_set = 0; 
        return 0; 
    }
    if ( range_setting == 1 ) 
    { 
        ctx->range_set = 1; 
        return 0; 
    }
    if ( range_setting > 1 ) 
    {
        return 1;
    }
}

void remotetemp_read ( remotetemp_t *ctx, uint8_t register_address, uint8_t *read_buffer, uint8_t n_bytes )
{
    remotetemp_generic_read( ctx, register_address, read_buffer, n_bytes );
}

void remotetemp_write ( remotetemp_t *ctx, uint8_t register_address, uint8_t *register_values, uint8_t n_bytes )
{
    uint8_t aux_buffer[ 50 ];
    uint8_t i;

    aux_buffer[ 0 ] = register_address;

    for ( i = 0; i < n_bytes; i ++ )
    {
        aux_buffer[ i + 1 ] = register_values[ i ];
    }
    
    remotetemp_generic_read( ctx, register_address, aux_buffer, n_bytes );
}

void remotetemp_set_int_diode_high_limit ( remotetemp_t *ctx, int16_t limit_value )
{
    uint8_t aux_limit_value_u8;

    if ( ctx->range_set == 1 )
    {
        limit_value += 64;
    }

    aux_limit_value_u8 = 0;
    aux_limit_value_u8 |= ( uint8_t )( limit_value & 0x00FF );

    remotetemp_write( ctx, REMOTETEMP_INT_DIODE_HIGH_LIMIT, &aux_limit_value_u8, 1 );
}

void remotetemp_set_int_diode_low_limit ( remotetemp_t *ctx, int16_t limit_value )
{
    uint8_t aux_limit_value_u8;

    if ( ctx->range_set == 1 )
    {
        limit_value += 64;
    }

    aux_limit_value_u8 = 0;
    aux_limit_value_u8 |= ( uint8_t )( limit_value & 0x00FF );

    remotetemp_write( ctx, REMOTETEMP_INT_DIODE_LOW_LIMIT, &aux_limit_value_u8, 1 );
}

void remotetemp_set_ext_diode_high_limit ( remotetemp_t *ctx, int16_t limit_value, uint8_t diode )
{
    uint8_t aux_limit_value_u8;

    if ( ctx->range_set == 1 )
    {
        limit_value += 64;
    }

    aux_limit_value_u8 = 0;
    aux_limit_value_u8 |= ( uint8_t )( limit_value & 0x00FF );

    switch ( diode )
    {
        case 1 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT1_HIGH_LIMIT_HIGH_BYTE, &aux_limit_value_u8, 1 );
            break;
        }
        case 2 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT2_HIGH_LIMIT_HIGH_BYTE, &aux_limit_value_u8, 1 );
            break;
        }
        case 3 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT3_HIGH_LIMIT_HIGH_BYTE, &aux_limit_value_u8, 1 );
            break;
        }
        case 4 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT4_HIGH_LIMIT_HIGH_BYTE, &aux_limit_value_u8, 1 );
            break;
        }
        default :
        {
            break;
        }
    }
}

void remotetemp_set_ext_diode_low_limit ( remotetemp_t *ctx, int16_t limit_value, uint8_t diode )
{
    uint8_t aux_limit_value_u8;

    if ( ctx->range_set == 1 )
    {
        limit_value += 64;
    }

    aux_limit_value_u8 = 0;
    aux_limit_value_u8 |= ( uint8_t )( limit_value & 0x00FF );

    switch ( diode )
    {
        case 1 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT1_LOW_LIMIT_HIGH_BYTE, &aux_limit_value_u8, 1 );
            break;
        }
        case 2 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT2_LOW_LIMIT_HIGH_BYTE, &aux_limit_value_u8, 1 );
            break;
        }
        case 3 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT3_LOW_LIMIT_HIGH_BYTE, &aux_limit_value_u8, 1 );
            break;
        }
        case 4 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT4_LOW_LIMIT_HIGH_BYTE, &aux_limit_value_u8, 1 );
            break;
        }
        default :
        {
            break;
        }
    }
}

void remotetemp_set_ext_diode_therm_limit ( remotetemp_t *ctx, int16_t limit_value, uint8_t diode )
{
    uint8_t aux_limit_value_u8;

    if ( ctx->range_set == 1 )
    {
        limit_value += 64;
    }

    aux_limit_value_u8 = 0;
    aux_limit_value_u8 |= ( uint8_t )( limit_value & 0x00FF );

    switch ( diode )
    {
        case 1 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT1_THERM_LIMIT, &aux_limit_value_u8, 1 );
            break;
        }
        case 2 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT2_THERM_LIMIT, &aux_limit_value_u8, 1 );
            break;
        }
        case 3 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT3_THERM_LIMIT, &aux_limit_value_u8, 1 );
            break;
        }
        case 4 :
        {
            remotetemp_write( ctx, REMOTETEMP_EXT4_THERM_LIMIT, &aux_limit_value_u8, 1 );
            break;
        }
        default :
        {
            break;
        }
    }
}

void remotetemp_set_int_diode_therm_limit ( remotetemp_t *ctx, int16_t limit_value )
{
    uint8_t aux_limit_value_u8;

    if ( ctx->range_set == 1 )
    {
        limit_value += 64;
    }

    aux_limit_value_u8 = 0;
    aux_limit_value_u8 |= ( uint8_t )( limit_value & 0x00FF );

    remotetemp_write( ctx, REMOTETEMP_INT_DIODE_THERM_LIMIT, &aux_limit_value_u8, 1 );
}

float remotetemp_get_internal_diode ( remotetemp_t *ctx )
{
    uint8_t aux_buffer[ 2 ];
    float temp_value;
    float frac_value;

    remotetemp_read( ctx, REMOTETEMP_INT_HIGH_BYTE, aux_buffer, 2 );

    temp_value = ( float )( aux_buffer[ 0 ] );

    if ( ctx->range_set == 1 )
    {
        temp_value -= 64.0;
    }

    aux_buffer[ 1 ] >>= 5;
    aux_buffer[ 1 ] &= 0x07;
    frac_value = aux_buffer[ 1 ];
    frac_value *= 0.125;

    temp_value += frac_value;
    return temp_value;
}

float remotetemp_get_external_diode ( remotetemp_t *ctx, uint8_t diode )
{
    uint8_t aux_buffer[ 2 ];
    float temp_value;
    float frac_value;

    switch ( diode )
    {
        case 1 :
        {
            remotetemp_read( ctx, REMOTETEMP_EXT1_HIGH_BYTE, aux_buffer, 2 );
            break;
        }
        case 2 :
        {
            remotetemp_read( ctx, REMOTETEMP_EXT2_HIGH_BYTE, aux_buffer, 2 );
            break;
        }
        case 3 :
        {
            remotetemp_read( ctx, REMOTETEMP_EXT3_HIGH_BYTE, aux_buffer, 2 );
            break;
        }
        case 4 :
        {
            remotetemp_read( ctx, REMOTETEMP_EXT4_HIGH_BYTE, aux_buffer, 2 );
            break;
        }
        default :
        {
            break;
        }
    }

    temp_value = ( float )( aux_buffer[ 0 ] );

    if ( ctx->range_set == 1 )
    {
        temp_value -= 64.0;
    }

    aux_buffer[ 1 ] >>= 5;
    aux_buffer[ 1 ] &= 0x07;
    frac_value = aux_buffer[ 1 ];
    frac_value *= 0.125;

    temp_value += frac_value;
    return temp_value;
}

float remotetemp_get_hottest_diode ( remotetemp_t *ctx )
{
    uint8_t aux_buffer[ 2 ];
    float temp_value;
    float frac_value;

    remotetemp_read( ctx, REMOTETEMP_HOTTEST_DIODE_HIGH_BYTE, aux_buffer, 2 );

    temp_value = ( float )( aux_buffer[ 0 ] );

    if ( ctx->range_set == 1 )
    {
        temp_value -= 64.0;
    }

    aux_buffer[ 1 ] >>= 5;
    aux_buffer[ 1 ] &= 0x07;
    frac_value = aux_buffer[ 1 ];
    frac_value *= 0.125;

    temp_value += frac_value;
    return temp_value;
}

// ------------------------------------------------------------------------- END

