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

#include "charger8.h"

// -------------------------------------------------------------------- VARIABLE 

static uint16_t nv_configuration[ 96 ] =
{
    0x0081, 0x1393, 0x1100, 0x1400, 0x110D, 0x1484, 0x0CC0, 0x0C37, 0x084F, 0x08A0,
    0x0B65, 0x05FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x8EFB, 0xB6B9, 0xB82C, 0xBCAC,
    0xBE10, 0xBFAC, 0xC2CC, 0xC418, 0xC578, 0xCB9D, 0xD015, 0xD1F1, 0x00D3, 0x0EA4,
    0x965A, 0x2602, 0x1B80, 0x0D80, 0x068A, 0x048C, 0x0000, 0x0496, 0x1036, 0x243A,
    0xFC55, 0x0496, 0x0000, 0x7F80, 0xFF00, 0x7F80, 0x0000, 0x0000, 0x0000, 0x0204,
    0x0870, 0x0496, 0x0000, 0x0E01, 0x2039, 0x2241, 0xC9BE, 0x2006, 0x810A, 0x0004,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x5F05, 0x0000, 0x4000, 0x0025, 0xEB8D, 0x20AA, 0x0000, 0x0000, 0x0000, 0x03E8,
    0x0000, 0x0000, 0xD5E3, 0x0E73, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static long stat_map ( long x, long out_max ) ;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void charger8_cfg_setup ( charger8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->dok = HAL_PIN_NC;
    cfg->alt = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->us = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = CHARGER8_DEVICE_SLAVE_ADDRESS;
    cfg->i2c_nv_address = CHARGER8_DEVICE_NV_SLAVE_ADDRESS;
}

CHARGER8_RETVAL charger8_init ( charger8_t *ctx, charger8_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->nv_slave_address = cfg->i2c_nv_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return CHARGER8_INIT_ERROR;
    }

//     i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    ctx->max_bat_capacity = 4000;

    // Output pins 
    
    digital_out_init( &ctx->alt, cfg->alt );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->us, cfg->us );
   

    // Input pins

    digital_in_init( &ctx->dok, cfg->dok );
    digital_in_init( &ctx->flt, cfg->flt );

    return CHARGER8_OK;

}

void charger8_default_cfg ( charger8_t *ctx )
{    
    uint8_t cnt = 0;
    uint8_t index = 0;
    uint8_t cnt1 = 0;
    
    for(cnt = 0; cnt < 6; cnt++)
    {
        for (cnt1 = 0; cnt1 < 16; cnt1++)
        {
            index = (cnt) * 16 + cnt1;
            charger8_generic_write( ctx, index + 0x80, nv_configuration[index] );
        }
    }
}

void charger8_generic_write ( charger8_t *ctx, uint8_t reg, uint16_t data_wr )
{
    uint8_t tx_buf[ 3 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = (uint8_t)( data_wr >> 8 );
    tx_buf[ 2 ] = (uint8_t)( data_wr );
    
    if ( reg < 0x80 )
    {
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    else
    {
        i2c_master_set_slave_address( &ctx->i2c, ctx->nv_slave_address );
    }

    i2c_master_write( &ctx->i2c, tx_buf, 3 );  
}

uint16_t charger8_generic_read ( charger8_t *ctx, uint8_t reg )
{    
    uint8_t rd_buf[ 2 ] = { 0 };
    uint16_t temp_data = 0;
    
    if ( reg < 0x80 )
    {
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    else
    {
        i2c_master_set_slave_address( &ctx->i2c, ctx->nv_slave_address );
    }

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, rd_buf, 2 );
    
    temp_data = rd_buf[ 1 ];
    temp_data <<= 8;
    temp_data |= rd_buf[ 0 ];
    
    return temp_data;
}

void charger8_enable ( charger8_t *ctx, uint8_t enable )
{
    digital_out_write( &ctx->en, enable );
}

float charger8_get_temperature ( charger8_t *ctx )
{
    float temp;
    uint16_t r_data;
    
    r_data = charger8_generic_read( ctx, CHARGER8_M5REG_TEMPERATURE );
    temp = r_data / 256.0;
    
    return temp;
}

float charger8_get_current ( charger8_t *ctx )
{
    uint16_t r_data;
    float current;
    uint8_t temp_read[ 2 ];
    
    r_data = charger8_generic_read( ctx, CHARGER8_M5REG_CURRENT );

    if ( r_data > 32767 )
    {
        r_data = 65536 - r_data;
        current = ( double )r_data * ( -156.25e-3 );
    }
    else
    {
        current = ( double )r_data * ( 156.25e-3 );
    }
    
    if ( current <= 0)
    {
        return 0;
    }
    
    return current;
}

float charger8_get_voltage ( charger8_t *ctx )
{
    uint16_t r_data;
    float voltage;
    uint8_t temp_read[ 2 ];

    r_data = charger8_generic_read( ctx, CHARGER8_M5REG_VCELL ) ;
    
    voltage = ( float )r_data * 78.125e-3 ;
    return ( voltage - 250 );
}

uint8_t charger8_get_soc ( charger8_t *ctx )
{
    uint16_t r_data;
    uint8_t soc;
    uint8_t temp_read[ 2 ];

    r_data = charger8_generic_read( ctx, CHARGER8_M5REG_REP_SOC );

    soc = r_data / 256;
    return soc;
}

uint16_t charger8_get_capacity ( charger8_t *ctx )
{
    uint16_t r_data;
    uint16_t capacity;
    uint8_t temp_read[ 2 ];
    
    r_data = charger8_generic_read( ctx, CHARGER8_M5REG_REP_CAP );

    capacity = stat_map( r_data, ctx->max_bat_capacity ) ;
    return capacity;
}

float charger8_get_time_to_empty ( charger8_t *ctx )
{
    uint16_t r_data;
    float capacity;
    uint8_t temp_read[ 2 ];

    r_data = charger8_generic_read( ctx, CHARGER8_M5REG_TIME_TO_EMPTY );

    capacity = r_data * 5.625;
    return capacity;
}

float charger8_get_time_to_full ( charger8_t *ctx )
{
    uint16_t r_data;
    float capacity;
    uint8_t temp_read[ 2 ];

    r_data = charger8_generic_read( ctx, CHARGER8_M5REG_TIME_TO_FULL );
    capacity = r_data * 5.625;
    return capacity;
}

uint16_t charger8_get_status ( charger8_t *ctx )
{
    uint16_t r_data;
    uint8_t temp_read[ 2 ];

    r_data = charger8_generic_read( ctx, CHARGER8_M5REG_STATUS );

    return r_data;
}

void charger8_reset ( charger8_t *ctx )
{    
    charger8_generic_write( ctx, CHARGER8_COMMAND, 0x0F00 );
    Delay_100ms();

    charger8_generic_write( ctx, CHARGER8_M5REG_CONFIG_2, 0x0100 );
    Delay_100ms( );
}

uint8_t charger8_get_fault_output ( charger8_t *ctx )
{
    return digital_in_read( &ctx->flt );
}

void charger8_set_usb_suspend ( charger8_t *ctx, uint8_t mode )
{
    digital_out_write( &ctx->us, mode );
}

void charger8_set_alert ( charger8_t *ctx, uint8_t state )
{
    digital_out_write(  &ctx->alt, state );
}

uint8_t charger8_get_dc_power_ok ( charger8_t *ctx )
{
   return digital_in_read( &ctx->dok );
}

void charger8_set_max_battery_capacity ( charger8_t *ctx, uint16_t capacity )
{
    ctx->max_bat_capacity = capacity;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static long stat_map ( long x, long out_max )
{
    long in_min = 0;
    long in_max = 2700;
    long out_min = 0;
    
    return ( ( x - in_min ) * ( out_max - out_min ) / ( in_max - in_min ) + out_min );
}

// ------------------------------------------------------------------------- END

