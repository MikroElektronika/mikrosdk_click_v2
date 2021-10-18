/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file irgrid.c
 * @brief IR Grid Click Driver.
 */

#include "irgrid.h"
#include "math.h"

static uint16_t get_cfg ( irgrid_t *ctx );
static void get_eeprom ( irgrid_t *ctx, irgrid_data_t *data_str );
static void get_ir ( irgrid_t *ctx, irgrid_data_t *data_str );
static void get_ptat ( irgrid_t *ctx );
static void get_cpix ( irgrid_t *ctx );
static void set_cfg ( irgrid_t *ctx );
static void set_trim ( irgrid_t *ctx, irgrid_data_t *data_str );
static void calc_ta ( irgrid_t *ctx, irgrid_data_t *data_str );
static void calc_to ( irgrid_t *ctx, irgrid_data_t *data_str );

void irgrid_cfg_setup ( irgrid_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_ram_address = 0x60;
    cfg->i2c_eeprom_address = 0x50;
}

err_t irgrid_init ( irgrid_t *ctx, irgrid_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_ram_address = cfg->i2c_ram_address;
    ctx->slave_eeprom_address = cfg->i2c_eeprom_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_ram_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

void irgrid_write_ram( irgrid_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_ram_address );
    i2c_master_write( &ctx->i2c, data_buf, len );   
}

void irgrid_read_ram ( irgrid_t *ctx, uint8_t *reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 4 ];

    tx_buf [ 0 ] = reg[ 0 ];
    tx_buf [ 1 ] = reg[ 1 ];
    tx_buf [ 2 ] = reg[ 2 ];
    tx_buf [ 3 ] = reg[ 3 ];

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_ram_address );
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 4, data_buf, len );
}

void irgrid_write_eeprom ( irgrid_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_eeprom_address );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
}

void irgrid_read_eeprom ( irgrid_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_eeprom_address );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t irgrid_device_init (  irgrid_t *ctx, irgrid_data_t *data_str, uint8_t refrate )
{
    uint8_t i;

    i = 0;
    ctx->refresh_rate = refrate;
    
    do 
    {
        get_eeprom( ctx, data_str );
        set_trim( ctx, data_str );
        set_cfg( ctx );

        if ( i++ > 16 )
        {
            return 1;
        }
    
    } while ( !( ( get_cfg( ctx ) & 0x0400 ) >> 10 ) );

    return 0;
}

uint8_t irgrid_measure ( irgrid_t *ctx, irgrid_data_t *data_str )
{
    uint8_t i;

    i = 0;

    do 
    {
        get_eeprom( ctx, data_str );
        set_trim( ctx, data_str );
        set_cfg( ctx );

        if (i++ > 16)
        {
            return 1;
        }
    
    } while ( !( ( get_cfg( ctx ) & 0x0400 ) >> 10 ) );

    get_ptat( ctx );
    get_ir( ctx, data_str );
    calc_ta( ctx, data_str );
    get_cpix( ctx );
    calc_to( ctx, data_str );

    return 0;
}

float irgrid_get_amb_temperature ( irgrid_t *ctx ) 
{
    return ctx->temperature_amb;
}

void irgrid_get_ir_raw ( irgrid_data_t *data_str, int16_t *buffer )
{
    memcpy( buffer, data_str->ir_data, sizeof( int16_t ) * 64 );
}

void irgrid_get_temperature ( irgrid_data_t *data_str, float *buffer )
{
    memcpy( buffer, data_str->temperature_data, sizeof( float ) * 64 );
}

static void get_eeprom ( irgrid_t *ctx, irgrid_data_t *data_str ) 
{
    uint8_t write_reg;
    
    write_reg = 0;

    irgrid_read_eeprom ( ctx, write_reg, data_str->eeprom_data, 255 );
}

static void set_cfg ( irgrid_t *ctx )
{
    uint8_t tmp[ 5 ];
    uint8_t hz_lsb;
    uint8_t hz_msb;

    switch ( ctx->refresh_rate )
    {
        case 0:
        {
            hz_lsb = 0x3F;
            break;
        }
        case 1:
        {
            hz_lsb = 0x3E;
            break;
        }
        case 2:
        {
            hz_lsb = 0x3D;
            break;
        }
        case 4:
        {
            hz_lsb = 0x3C;
            break;
        }
        case 8:
        {
            hz_lsb = 0x3B;
            break;
        }
        case 16:
        {
            hz_lsb = 0x3A;
            break;
        }
        case 32:
        {
            hz_lsb = 0x39;
            break;
        }
        default:
        {
            hz_lsb = 0x3E;
            break;
        }
    }

    hz_msb = 0x46;

    tmp[ 0 ] = 0x03;
    tmp[ 1 ] = ( uint8_t ) hz_lsb - 0x55;
    tmp[ 2 ] = ( hz_lsb );
    tmp[ 3 ] = hz_msb - 0x55;
    tmp[ 4 ] = hz_msb;

    irgrid_write_ram( ctx, tmp, 5 );
    ctx->resolution = ( get_cfg( ctx ) & 0x30) >> 4;
}

static void set_trim ( irgrid_t *ctx, irgrid_data_t *data_str ) 
{
    uint8_t tmp[ 5 ];

    tmp[ 0 ] = 0x04;
    tmp[ 1 ] = ( uint8_t ) data_str->eeprom_data[ IRGRID_OSC_TRIM_VALUE ] - 0xAA;
    tmp[ 2 ] = data_str->eeprom_data[ IRGRID_OSC_TRIM_VALUE ];
    tmp[ 3 ] = 0x56;
    tmp[ 4 ] = 0x00;

    irgrid_write_ram( ctx, tmp, 5 );
}

static void get_ir( irgrid_t *ctx, irgrid_data_t *data_str ) 
{
    uint8_t i;
    uint8_t tmp_w[ 4 ];
    uint8_t tmp_r[ 128 ];

    tmp_w[ 0 ] = 0x02;
    tmp_w[ 1 ] = 0x00;
    tmp_w[ 2 ] = 0x01;
    tmp_w[ 3 ] = 0x40;

    irgrid_read_ram( ctx, tmp_w, tmp_r, 128 );

    for ( i = 0; i < 64; i++ )
    {
        data_str->ir_data[ i ] = 0;
        data_str->ir_data[ i ] |= tmp_r[ ( i * 2 ) + 1 ];
        data_str->ir_data[ i ] <<= 8;
        data_str->ir_data[ i ] |= tmp_r[ i * 2 ];
    }
}

static void get_ptat ( irgrid_t *ctx ) 
{
    uint8_t rd[ 2 ];
    uint8_t tmp[ 4 ];

    tmp[ 0 ] = 0x02;
    tmp[ 1 ] = 0x40;
    tmp[ 2 ] = 0x00;
    tmp[ 3 ] = 0x01;

    irgrid_read_ram( ctx, tmp, rd, 2 );

    ctx->ptat = ( ( uint16_t ) ( rd[ 1 ] << 8 ) | rd[ 0 ] );
}

static void get_cpix ( irgrid_t *ctx ) 
{
    uint8_t rd[ 2 ];
    uint8_t tmp[ 4 ];

    tmp[ 0 ] = 0x02;
    tmp[ 1 ] = 0x41;
    tmp[ 2 ] = 0x00;
    tmp[ 3 ] = 0x01;

    irgrid_read_ram( ctx, tmp, rd, 2 );

    ctx->cpix = ( ( uint16_t ) ( rd[ 1 ] << 8 ) | rd[ 0 ] );
    
    if ( ctx->cpix >= 32768 )
    {
        ctx->cpix -= 65536;
    }
}

static uint16_t get_cfg ( irgrid_t *ctx ) 
{
    uint8_t rd[ 2 ];
    uint8_t tmp[ 4 ];
    uint16_t config;

    tmp[ 0 ] = 0x02;
    tmp[ 1 ] = 0x92;
    tmp[ 2 ] = 0x00;
    tmp[ 3 ] = 0x01;

    irgrid_read_ram( ctx, tmp, rd, 2 );

    config = ( ( uint16_t ) ( rd[ 1 ] << 8 ) | rd[ 0 ] );
    return config;
}

static void calc_ta ( irgrid_t *ctx, irgrid_data_t *data_str ) 
{
    int16_t k_t1_scale;
    int16_t k_t2_scale;

    float k_t1; 
    float k_t2;
    float v_th;

    k_t1_scale = ( int16_t ) ( data_str->eeprom_data[ IRGRID_KT_SCALE ] & 0xF0 ) >> 4;
    k_t2_scale = ( int16_t ) ( data_str->eeprom_data[ IRGRID_KT_SCALE ] & 0x0F ) + 10;
    v_th = ( float ) 256 * data_str->eeprom_data[ IRGRID_VTH_H ] + data_str->eeprom_data[ IRGRID_VTH_L ];
    
    if ( v_th >= 32768.0 )
    {
        v_th -= 65536.0;
    }
    v_th = v_th / pow( 2, ( 3 - ctx->resolution ) );
    k_t1 = ( float ) 256 * data_str->eeprom_data[ IRGRID_KT1_H ] + data_str->eeprom_data[ IRGRID_KT1_L ];
    
    if ( k_t1 >= 32768.0 )
    {
        k_t1 -= 65536.0;
    }

    k_t1 /= ( pow(2, k_t1_scale ) * pow( 2, ( 3 - ctx->resolution ) ) );
    k_t2 = ( float ) 256 * data_str->eeprom_data[ IRGRID_KT2_H ] + data_str->eeprom_data[ IRGRID_KT2_L ];
    
    if ( k_t2 >= 32768.0 )
    {
        k_t2 -= 65536.0;
    }

    k_t2 /= ( pow( 2, k_t2_scale ) * pow( 2, ( 3 - ctx->resolution ) ) );
    
    ctx->temperature_amb = ( (-k_t1 + sqrt( pow( k_t1, 2 ) - ( 4 * k_t2 * ( v_th - ( float ) ctx->ptat ) ) ) ) / ( 2 * k_t2 ) ) + 25.0;
}

static void calc_to ( irgrid_t *ctx, irgrid_data_t *data_str ) 
{
    uint16_t i;
    int16_t a_common;
    int16_t a_i_scale; 
    int16_t b_i_scale;
    
    float vcp_offset_compensated;
    float vir_offset_compensated;
    float vir_tgc_compensated;
    float vir_normal;
    float vir_compensated;
    float emissivity;
    float tgc;
    float alpha_cp;
    float a_cp;
    float b_cp;

    emissivity = ( 256 * data_str->eeprom_data[ IRGRID_CAL_EMIS_H ] + data_str->eeprom_data[ IRGRID_CAL_EMIS_L ] ) / 32768.0;
    a_common = ( int16_t ) 256 * data_str->eeprom_data[ IRGRID_CAL_ACOMMON_H ] + data_str->eeprom_data[ IRGRID_CAL_ACOMMON_L ];
    
    alpha_cp = ( 256 * data_str->eeprom_data[ IRGRID_CAL_ALPHA_CP_H ] + data_str->eeprom_data[ IRGRID_CAL_ALPHA_CP_L ] ) / ( pow( 2, data_str->eeprom_data[ IRGRID_CAL_A0_SCALE ] ) * pow( 2, ( 3 - ctx->resolution ) ) );
    a_i_scale = ( int16_t ) ( data_str->eeprom_data[ IRGRID_CAL_AI_SCALE ] & 0xF0 ) >> 4;
    b_i_scale = ( int16_t ) data_str->eeprom_data[ IRGRID_CAL_BI_SCALE ] & 0x0F;
    
    a_cp = ( float ) 256 * data_str->eeprom_data[ IRGRID_CAL_ACP_H ] + data_str->eeprom_data[ IRGRID_CAL_ACP_L ];
    a_cp /= pow( 2, ( 3 - ctx->resolution ) );
    b_cp = ( float ) data_str->eeprom_data[ IRGRID_CAL_BCP ];
    b_cp /= ( pow( 2, b_i_scale ) * pow( 2, ( 3 - ctx->resolution ) ) );
    tgc = ( float ) data_str->eeprom_data[ IRGRID_CAL_TGC ];
    tgc /= 32.0;
    vcp_offset_compensated = ( float ) ctx->cpix - ( a_cp + b_cp * ( ctx->temperature_amb - 25.0 ) );
    
    for ( i = 0; i < 64; i++ )
    {
        data_str->a_data[ i ] = ( ( float ) a_common + data_str->eeprom_data[ i ] * pow( 2, a_i_scale ) ) / pow( 2, ( 3 - ctx->resolution ) );
        data_str->b_data[ i ] = data_str->eeprom_data[ 0x40 + i ];

        if ( data_str->b_data[ i ] > 127 )
        {
            data_str->b_data[ i ] -= 256;
        }

        data_str->b_data[ i ] = data_str->b_data[ i ] / ( pow( 2, b_i_scale ) * pow( 2, ( 3 - ctx->resolution ) ) );
        vir_offset_compensated = data_str->ir_data[ i ] - ( data_str->a_data[ i ] + data_str->b_data[ i ] * ( ctx->temperature_amb - 25.0 ) );
        vir_tgc_compensated = vir_offset_compensated - tgc * vcp_offset_compensated;
        data_str->alpha_a_data[ i ] = ( ( 256 * data_str->eeprom_data[ IRGRID_CAL_A0_H ] + data_str->eeprom_data[ IRGRID_CAL_A0_L ]) / pow( 2, data_str->eeprom_data[ IRGRID_CAL_A0_SCALE ] ) );
        data_str->alpha_a_data[ i ] += ( data_str->eeprom_data[0x80 + i] / pow( 2, data_str->eeprom_data[ IRGRID_CAL_DELTA_A_SCALE ] ) );
        data_str->alpha_a_data[ i ] = data_str->alpha_a_data[ i ] / pow(2, 3 - ctx->resolution);
        vir_normal = vir_tgc_compensated / ( data_str->alpha_a_data[ i ] - tgc * alpha_cp );
        vir_compensated = vir_normal / emissivity;
        
        // Compensated compared to original formula ... 
        data_str->temperature_data[ i ] = 329.5 - ( exp( ( log( ( vir_compensated + pow( ( ctx->temperature_amb + 273.15 ), 4 ) ) ) / 4.0 ) ) );
    }
}

// ------------------------------------------------------------------------- END
