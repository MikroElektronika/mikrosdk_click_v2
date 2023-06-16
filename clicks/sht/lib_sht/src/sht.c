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

#include "sht.h"
// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void sht_ss ( sht_t *ctx, uint8_t *raw_measurement );

static uint8_t calc_crc ( uint8_t crc, uint8_t *raw_data );

static float calc_hum ( uint8_t *raw_data );

static float calc_temp ( uint8_t *raw_data );

static void read_status ( sht_t *ctx, uint16_t *reg_data );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void sht_cfg_setup ( sht_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = SHT_I2C_ADDR0;

    cfg->vars_cfg.clk_stretching = 1;
    cfg->vars_cfg.repeatability = SHT_RPT_MEDIUM;
    cfg->vars_cfg.mps = SHT_MPS_1;
}

err_t sht_init ( sht_t *ctx, sht_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) )
    {
        return SHT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SHT_OK;
}

void sht_generic_write ( sht_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    Delay_5ms ( );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

void sht_generic_read ( sht_t *ctx, uint8_t *reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write( &ctx->i2c, reg, 2 );
    Delay_5ms ( );
    i2c_master_read( &ctx->i2c, data_buf, len );
}

void sht_reset ( sht_t *ctx )
{
    ctx->vars.clk_stretching = 1;
    ctx->vars.repeatability = SHT_RPT_MEDIUM;
    ctx->vars.mps = SHT_MPS_1;
}

void sht_hw_reset ( sht_t *ctx )
{
    sht_rst_set( ctx, 0 );
    Delay_100ms( );
    sht_rst_set( ctx, 1 );
    Delay_1sec( );
}

uint8_t sht_int_get ( sht_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void sht_rst_set ( sht_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void sht_set_clk_strecth ( sht_t *ctx, uint8_t clk_stretching )
{
    ctx->vars.clk_stretching = clk_stretching;
}

void sht_set_repeats ( sht_t *ctx, uint8_t repeatability )
{
    ctx->vars.repeatability = repeatability;
}

void sht_set_mps ( sht_t *ctx, uint8_t measure_per_second )
{
    ctx->vars.mps = measure_per_second;
}

float sht_temp_ss ( sht_t *ctx )
{
    uint8_t raw_data[ 6 ] = { 0 };
    uint8_t test = 0;

    do 
    {
        sht_ss( ctx, raw_data );
        test = calc_crc( raw_data[ 2 ], &raw_data[ 0 ] );
    } 
    while ( !test );

    return calc_temp( raw_data );
}

float sht_hum_ss ( sht_t *ctx )
{
    uint8_t raw_data[ 6 ] = { 0 };
    uint8_t test = 0;

    do 
    {
        sht_ss( ctx, raw_data );
        test = calc_crc( raw_data[ 5 ], &raw_data[ 3 ] );
    } 
    while ( !test );

    return calc_hum( raw_data );
}

void sht_start_pm ( sht_t *ctx )
{
    uint8_t tmp_cmd[ 2 ] = { 0 };

    tmp_cmd[ 0 ] = ctx->vars.mps;

    switch ( ctx->vars.mps )
    {
        case SHT_MPS_05 :
        {
            switch ( ctx->vars.repeatability )
            {
                case SHT_RPT_HIGH :
                {
                    tmp_cmd[ 1 ] = 0x32;
                    break;
                }
                case SHT_RPT_MEDIUM :
                {
                    tmp_cmd[ 1 ] = 0x24;
                    break;
                }
                case SHT_RPT_LOW :
                {
                    tmp_cmd[ 1 ] = 0x2F;
                    break;
                }
            }
            break;
        }

        case SHT_MPS_1 :
        {
            switch ( ctx->vars.repeatability )
            {
                case SHT_RPT_HIGH :
                {
                    tmp_cmd[ 1 ] = 0x30;
                    break;
                }
                case SHT_RPT_MEDIUM :
                {
                    tmp_cmd[ 1 ] = 0x26;
                    break;
                }
                case SHT_RPT_LOW :
                {
                    tmp_cmd[ 1 ] = 0x2D;
                    break;
                }
            }
            break;
        }

        case SHT_MPS_2 :
        {
            switch ( ctx->vars.repeatability )
            {
                case SHT_RPT_HIGH :
                {
                    tmp_cmd[ 1 ] = 0x36;
                    break;
                }
                case SHT_RPT_MEDIUM :
                {
                    tmp_cmd[ 1 ] = 0x20;
                    break;
                }
                case SHT_RPT_LOW :
                {
                    tmp_cmd[ 1 ] = 0x2B;
                    break;
                }
            }
            break;
        }

        case SHT_MPS_4 :
        {
            switch ( ctx->vars.repeatability )
            {
                case SHT_RPT_HIGH :
                {
                    tmp_cmd[ 1 ] = 0x34;
                    break;
                }
                case SHT_RPT_MEDIUM :
                {
                    tmp_cmd[ 1 ] = 0x22;
                    break;
                }
                case SHT_RPT_LOW :
                {
                    tmp_cmd[ 1 ] = 0x29;
                    break;
                }
            }
            break;
        }

        case SHT_MPS_10 :
        {
            switch ( ctx->vars.repeatability )
            {
                case SHT_RPT_HIGH :
                {
                    tmp_cmd[ 1 ] = 0x37;
                    break;
                }
                case SHT_RPT_MEDIUM :
                {
                    tmp_cmd[ 1 ] = 0x21;
                    break;
                }
                case SHT_RPT_LOW :
                {
                    tmp_cmd[ 1 ] = 0x2A;
                    break;
                }
            }
            break;
        }
    }

    sht_generic_write( ctx, tmp_cmd[ 0 ], &tmp_cmd[ 1 ], 1 );
}

float sht_temp_pm ( sht_t *ctx )
{
    uint8_t tmp_cmd[ 2 ] = { 0 };
    uint8_t raw_data[ 6 ] = { 0 };
    uint8_t test = 0;

    tmp_cmd[ 0 ] = ( SHT_FETCH_DATA & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = SHT_FETCH_DATA & 0x00FF;

    do  
    {
        sht_generic_read( ctx, tmp_cmd, raw_data, 6 );
        test = calc_crc( raw_data[ 2 ], &raw_data[ 0 ] );
    } 
    while ( !test );

    return calc_temp( raw_data );
}

float sht_hum_pm ( sht_t *ctx )
{
    uint8_t tmp_cmd[ 2 ] = { 0 };
    uint8_t raw_data[ 6 ] = { 0 };
    uint8_t test = 0;

    tmp_cmd[ 0 ] = ( SHT_FETCH_DATA  & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = SHT_FETCH_DATA & 0x00FF;

    do 
    {
        sht_generic_read( ctx, tmp_cmd, raw_data, 6 );
        test = calc_crc( raw_data[ 5 ], &raw_data[ 3 ] );
    } 
    while ( !test );

    return calc_hum( raw_data );
}

void sht_stop_pm ( sht_t *ctx )
{   
    uint8_t addr = 0;
    uint8_t tmp_cmd = 0;

    addr = ( SHT_BREAK & 0xFF00 ) >> 8;
    tmp_cmd = SHT_BREAK & 0x00FF;

    sht_generic_write( ctx, addr, &tmp_cmd, 1 );
}

void sht_software_rst ( sht_t *ctx )
{
    uint8_t addr = 0;
    uint8_t tmp_cmd = 0;

    addr = ( SHT_SOFT_RESET & 0xFF00 ) >> 8;
    tmp_cmd = SHT_SOFT_RESET & 0x00FF;

    sht_generic_write( ctx, addr, &tmp_cmd, 1 );
}

void sht_heater_control ( sht_t *ctx, uint8_t state )
{
    uint8_t addr = 0;
    uint8_t tmp_cmd = 0;

    addr = SHT_HEATER;

    if ( state & 0x01 )
    {
        tmp_cmd = 0x6D;
    }
    else
    {
        tmp_cmd = 0x66;
    }

    sht_generic_write( ctx, addr, &tmp_cmd, 1 );
}

void sht_clear_status ( sht_t *ctx )
{
    uint8_t addr = 0;
    uint8_t tmp_cmd = 0;

    addr = ( SHT_CLEAR_STATUS1 & 0xFF00 ) >> 8;
    tmp_cmd = SHT_CLEAR_STATUS1 & 0x00FF;

    sht_generic_write( ctx, addr, &tmp_cmd, 1 );
}

uint8_t sht_alert_status ( sht_t *ctx )
{
    uint16_t status_reg = 0;

    read_status( ctx, &status_reg );

    return ( uint8_t ) ( ( status_reg >> 15 ) & 0x01 );
}

uint8_t sht_heater_status ( sht_t *ctx )
{
    uint16_t status_reg = 0;

    read_status( ctx, &status_reg );

    return ( uint8_t ) ( ( status_reg >> 13 ) & 0x01 );
}

uint8_t sht_hum_status ( sht_t *ctx )
{
    uint16_t status_reg = 0;

    read_status( ctx, &status_reg );

    return ( uint8_t ) ( ( status_reg >> 11 ) & 0x01 );
}

uint8_t sht_temp_status ( sht_t *ctx )
{
    uint16_t status_reg = 0;

    read_status( ctx, &status_reg );

    return ( uint8_t ) ( ( status_reg >> 10 ) & 0x01 );
}

uint8_t sht_reset_status ( sht_t *ctx )
{
    uint16_t status_reg = 0;

    read_status( ctx, &status_reg );

    return ( uint8_t ) ( ( status_reg >> 4 ) & 0x01 );
}

uint8_t sht_cmd_status ( sht_t *ctx )
{
    uint16_t status_reg = 0;

    read_status( ctx, &status_reg );

    return ( uint8_t ) ( ( status_reg >> 1 ) & 0x01 );
}

uint8_t sht_wr_chksum_status ( sht_t *ctx )
{
    uint16_t status_reg = 0;

    read_status( ctx, &status_reg );

    return ( uint8_t ) ( ( status_reg >> 1 ) & 0x01 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void sht_ss ( sht_t *ctx, uint8_t *raw_measurement )
{
    uint8_t tmp_cmd[ 2 ] = { 0 };

    switch ( ctx->vars.clk_stretching )
    {
        case 1 :
        {
            tmp_cmd[ 0 ] = SHT_STR_ENABLE;
            switch ( ctx->vars.repeatability )
            {
                case SHT_RPT_HIGH :
                {
                    tmp_cmd[ 1 ] = 0x06;
                    break;
                }
                case SHT_RPT_MEDIUM :
                {
                    tmp_cmd[ 1 ] = 0x0D;
                    break;
                }
                case SHT_RPT_LOW :
                {
                    tmp_cmd[ 1 ] = 0x10;
                    break;
                }
            }
            break;
        }
        case 0 :
        {
            tmp_cmd[ 0 ] = SHT_STR_DISABLE;
            switch ( ctx->vars.repeatability )
            {
                case SHT_RPT_HIGH :
                {
                    tmp_cmd[ 1 ] = 0x00;
                    break;
                }
                case SHT_RPT_MEDIUM :
                {
                    tmp_cmd[ 1 ] = 0x0B;
                    break;
                }
                case SHT_RPT_LOW :
                {
                    tmp_cmd[ 1 ] = 0x16;
                    break;
                }
            }
            break;
        }
    }
    sht_generic_read( ctx, tmp_cmd, raw_measurement, 6 );
}

static uint8_t calc_crc ( uint8_t crc, uint8_t *raw_data )
{
    uint8_t *end = 0;

    crc ^= 0xFF;
    end = raw_data + 2;

    do 
    {
        crc ^= *( raw_data++ );
        crc = ( crc & 1 ) ? ( ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL ): ( crc >> 1 );
        crc = ( crc & 1 ) ? ( ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL ): ( crc >> 1 );
        crc = ( crc & 1 ) ? ( ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL ): ( crc >> 1 );
        crc = ( crc & 1 ) ? ( ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL ): ( crc >> 1 );
        crc = ( crc & 1 ) ? ( ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL ): ( crc >> 1 );
        crc = ( crc & 1 ) ? ( ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL ): ( crc >> 1 );
        crc = ( crc & 1 ) ? ( ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL ): ( crc >> 1 );
        crc = ( crc & 1 ) ? ( ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL ): ( crc >> 1 );
    } 
    while ( raw_data < end );

    return crc ^ 0xFF;
}

static float calc_hum ( uint8_t *raw_data )
{
    uint16_t raw_humididty = 0;
    float retval = 0;
    
    raw_humididty = ( ( uint16_t ) raw_data[ 3 ] << 8 ) & 0xFF00;
    raw_humididty |= raw_data[ 4 ];

    retval = ( 100.0f * ( ( float ) raw_humididty / 65535.0f ) );

    return retval;
}

static float calc_temp ( uint8_t *raw_data )
{
    uint16_t raw_temperature = 0;
    float retval = 0;

    raw_temperature = ( ( uint16_t ) raw_data[ 0 ] << 8 ) & 0xFF00;
    raw_temperature |= raw_data[ 1 ];

    retval = ( ( 175.0f * ( ( float ) raw_temperature / 65535.0f ) ) - 45.0f );

    return retval;
}

static void read_status ( sht_t *ctx, uint16_t *reg_data )
{
    uint8_t tmp_cmd[ 2 ] = { 0 };
    uint8_t raw_data[ 2 ] = { 0 };

    tmp_cmd[ 0 ] = ( SHT_READ_STATUS & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = SHT_READ_STATUS & 0x00FF;

    sht_generic_read( ctx, tmp_cmd, raw_data, 2 );

    *reg_data = ( ( uint16_t ) raw_data[ 0 ] << 8 ) | raw_data[ 1 ];
}

// ------------------------------------------------------------------------- END

