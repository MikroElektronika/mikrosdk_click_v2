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

#include "surfacetemp2.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_temp_conv_time ( );
static void dev_rst_wait_time ( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void surfacetemp2_cfg_setup ( surfacetemp2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = SURFACETEMP2_I2C_DEV_ADR_0_0;
}

SURFACETEMP2_RETVAL surfacetemp2_init ( surfacetemp2_t *ctx, surfacetemp2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return SURFACETEMP2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->pwm, cfg->pwm );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SURFACETEMP2_OK;
}

void surfacetemp2_generic_write ( surfacetemp2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void surfacetemp2_generic_read ( surfacetemp2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

// Software Reset function
void surfacetemp2_soft_reset ( surfacetemp2_t *ctx )
{
    uint8_t buf;

    buf = SURFACETEMP2_REG_SOFT_RESET;

    i2c_master_write( &ctx->i2c, &buf, 1 );
    dev_rst_wait_time( );
}

// Setup function
uint8_t surfacetemp2_setup ( surfacetemp2_t *ctx, uint8_t setup )
{
    uint8_t tmp = 0;
    surfacetemp2_soft_reset( ctx );
    
    surfacetemp2_generic_read( ctx, SURFACETEMP2_REG_ID, &tmp, 1 );
    if ( tmp != SURFACETEMP2_DEV_ID_VAL )
    {
        return SURFACETEMP2_DEV_NOK;
    }

    surfacetemp2_generic_write( ctx, SURFACETEMP2_REG_CFG, &setup, 1 );

    return SURFACETEMP2_DEV_OK;
}

// Set hysteresis function
void surfacetemp2_set_hys_val ( surfacetemp2_t *ctx, uint8_t hys_val )
{
    if ( hys_val > 15 )
    {
        hys_val &= 0x0F;
    }
    surfacetemp2_generic_write( ctx, SURFACETEMP2_REG_T_HYST_SETP, &hys_val, 1 );
}

// Get Temperature function
float surfacetemp2_get_temperature ( surfacetemp2_t *ctx )
{
    uint8_t rx_buff[ 2 ];
    uint8_t chk = 0;
    int16_t tmp_val;
    float temp;

    surfacetemp2_generic_read( ctx, SURFACETEMP2_REG_CFG, &chk, 1 );

    surfacetemp2_generic_read( ctx, SURFACETEMP2_REG_TEMP_MSB, rx_buff, 2 );
    dev_temp_conv_time( );

    tmp_val = rx_buff[ 0 ];
    tmp_val <<= 8;
    tmp_val |= rx_buff[ 1 ];

    if( ( chk & 0x80 ) == 0x00 )
    {
        tmp_val >>= 3;

        if ( (tmp_val & 0x2000 ) != 0x00 )
        {
            tmp_val = ( ~ tmp_val ) + 1;
        }

        temp = (float)( tmp_val );
        temp *= SURFACETEMP2_RES_13_BIT;
    }
    else
    {
        temp = (float)( tmp_val );
        temp *= SURFACETEMP2_RES_16_BIT;
    }

    return temp;
}

// Set Over Temperature Threshold function
void surfacetemp2_set_high_trsh ( surfacetemp2_t *ctx, float trsh )
{
    uint8_t tx_buff[ 2 ];
    int16_t high_thres;

    if ( trsh > 150.0 )
    {
        trsh = 150.0;
    }

    if ( trsh < -40.0 )
    {
        trsh = -40.0;
    }

    high_thres = ( int16_t )(trsh / SURFACETEMP2_RES_16_BIT );
    tx_buff[ 0 ] = ( uint8_t )( high_thres >> 8 );
    tx_buff[ 1 ] = ( uint8_t )( high_thres & 0x00FF );

    surfacetemp2_generic_write( ctx, SURFACETEMP2_REG_T_HIGH_SETP_MSB, tx_buff, 2 );
}

// Set Under Temperature Threshold function
void surfacetemp2_set_low_trsh ( surfacetemp2_t *ctx, float trsh )
{
    uint8_t tx_buff[ 2 ];
    int16_t low_trsh;

    if ( trsh > 150.0 )
    {
        trsh = 150.0;
    }

    if ( trsh < -40.0 )
    {
        trsh = -40.0;
    }

    low_trsh = ( int16_t )(trsh / SURFACETEMP2_RES_16_BIT );
    tx_buff[ 0 ] = ( uint8_t )( low_trsh >> 8 );
    tx_buff[ 1 ] = ( uint8_t )( low_trsh & 0x00FF );

    surfacetemp2_generic_write( ctx, SURFACETEMP2_REG_T_LOW_SETP_MSB, tx_buff, 2 );
}

// Set Critical Temperature Threshold function
void surfacetemp2_set_crit_trsh ( surfacetemp2_t *ctx, float trsh )
{
    uint8_t tx_buff[ 2 ];
    int16_t crit_trsh;

    if ( trsh > 150.0 )
    {
        trsh = 150.0;
    }

    if ( trsh < -40.0 )
    {
        trsh = -40.0;
    }

    crit_trsh = ( int16_t )(trsh / SURFACETEMP2_RES_16_BIT );
    tx_buff[ 0 ] = ( uint8_t )( crit_trsh >> 8 );
    tx_buff[ 1 ] = ( uint8_t )( crit_trsh & 0x00FF );

    surfacetemp2_generic_write( ctx, SURFACETEMP2_REG_T_CRIT_SETP_MSB, tx_buff, 2 );
}

// Get INT pin state
uint8_t surfacetemp2_get_int_pin ( surfacetemp2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// Get CT pin state
uint8_t surfacetemp2_get_ct_pin ( surfacetemp2_t *ctx )
{
    return digital_in_read( &ctx->pwm );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_rst_wait_time ( )
{
    Delay_100ms( );
}

static void dev_temp_conv_time ( )
{
    Delay_100ms( );
    Delay_100ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

