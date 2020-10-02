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

#include "pressure7.h"

// ------------------------------------------------------------------ VARIABLES

static uint16_t PROM_C1;
static uint16_t PROM_C2;
static uint16_t PROM_C3;
static uint16_t PROM_C4;
static uint16_t PROM_C5;
static uint16_t PROM_C6;
static uint16_t PROM_CRC;
static uint32_t pressure_d1;
static uint32_t temperature_d2;
static int32_t dT;
static uint8_t OSR_D1 = PRESSURE7_CMD_CONVERT_D1_OSR_4096;
static uint8_t OSR_D2 = PRESSURE7_CMD_CONVERT_D2_OSR_4096;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t crc4 ( uint16_t *n_prom );
static uint16_t package_data16 ( uint8_t *in_data );
static uint32_t package_data24 ( uint8_t *in_data );
static float pow ( uint8_t base, uint8_t ex );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pressure7_cfg_setup ( pressure7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x76;
}

PRESSURE7_RETVAL pressure7_init ( pressure7_t *ctx, pressure7_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PRESSURE7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return PRESSURE7_OK;
}

void pressure7_default_cfg ( pressure7_t *ctx )
{
    pressure7_reset( ctx );
    Delay_1sec( );
    pressure7_set_over_sampling_ratio( PRESSURE7_CMD_CONVERT_D1_OSR_2048,
                                       PRESSURE7_CMD_CONVERT_D2_OSR_2048 );  
}

void pressure7_generic_read ( pressure7_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, data_buf, len );
}

void pressure7_send_command ( pressure7_t *ctx, uint8_t cmd )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = cmd;

    i2c_master_write( &ctx->i2c, tx_buf, 1 );    
}

void pressure7_reset ( pressure7_t *ctx )
{
    pressure7_send_command( ctx, PRESSURE7_CMD_RESET );
}

uint8_t pressure7_read_prom ( pressure7_t *ctx )
{
    uint8_t read_data[ 2 ];
    uint16_t crc_test[ 8 ];
    uint8_t crc_error;
    
    pressure7_generic_read( ctx, PRESSURE7_CMD_PROM_READ | PRESSURE7_PROM_ADDR_CRC, read_data, 2 );
    PROM_CRC = package_data16( read_data );

    pressure7_generic_read( ctx, PRESSURE7_CMD_PROM_READ | PRESSURE7_PROM_ADDR_C1, read_data, 2 );
    PROM_C1 = package_data16( read_data );
    
    pressure7_generic_read( ctx, PRESSURE7_CMD_PROM_READ | PRESSURE7_PROM_ADDR_C2, read_data, 2 );
    PROM_C2 = package_data16( read_data );
    
    pressure7_generic_read( ctx, PRESSURE7_CMD_PROM_READ | PRESSURE7_PROM_ADDR_C3, read_data, 2 );
    PROM_C3 = package_data16( read_data );
    
    pressure7_generic_read( ctx, PRESSURE7_CMD_PROM_READ | PRESSURE7_PROM_ADDR_C4, read_data, 2 );
    PROM_C4 = package_data16( read_data );
    
    pressure7_generic_read( ctx, PRESSURE7_CMD_PROM_READ | PRESSURE7_PROM_ADDR_C5, read_data, 2 );
    PROM_C5 = package_data16( read_data );
    
    pressure7_generic_read( ctx, PRESSURE7_CMD_PROM_READ | PRESSURE7_PROM_ADDR_C6, read_data, 2 );
    PROM_C6 = package_data16( read_data );
    
    crc_test[ 0 ] = PROM_CRC;
    crc_test[ 1 ] = PROM_C1;
    crc_test[ 2 ] = PROM_C2;
    crc_test[ 3 ] = PROM_C3;
    crc_test[ 4 ] = PROM_C4;
    crc_test[ 5 ] = PROM_C5; 
    crc_test[ 6 ] = PROM_C6;

    crc_error = crc4( crc_test );
    if ( crc_error == ( PROM_CRC >> 12 ) )
    {
        crc_error = PRESSURE7_PROM_READ_OK;
    }
    else
    {
        crc_error = PRESSURE7_PROM_READ_ERROR;
    }

    return crc_error;
}

void pressure7_start_measurement ( pressure7_t *ctx )
{
    uint8_t read_data[ 3 ];
    float tmp_1, tmp_2, tmp_3;

    pressure7_send_command( ctx, OSR_D2 );
    Delay_10ms( );
    pressure7_generic_read( ctx, PRESSURE7_CMD_ADC_READ, read_data, 3 );
    temperature_d2 = package_data24( read_data );

    dT = temperature_d2 - PROM_C5 * pow( 2, 8 );
    ctx->temperature = 2000 + dT * ( PROM_C6 / pow( 2,23 ) );

    pressure7_send_command( ctx, OSR_D1 );
    Delay_10ms( );
    pressure7_generic_read( ctx, PRESSURE7_CMD_ADC_READ, read_data, 3 );
    pressure_d1 = package_data24( read_data );

    tmp_1 = PROM_C1 * pow( 2,15 );
    tmp_2 = PROM_C3 * dT;
    tmp_2 /= pow( 2,8 );
    tmp_3 = tmp_1 + tmp_2;
   
    ctx->pressure = pressure_d1 * tmp_3;
    ctx->pressure /= pow( 2,21 );
    
    tmp_1 = PROM_C2 * pow( 2,16 );
    ctx->pressure -= tmp_1;
    tmp_2 = PROM_C4 * dT;
    tmp_2 /= pow( 2,7 );
    ctx->pressure -= tmp_2;
    ctx->pressure /= pow( 2,13 );
    
}

void pressure7_get_sensor_data ( pressure7_t *ctx, float *temper, float *press )
{
    *temper = ( float )( ctx->temperature / 100.00 );
    *press = ( float )( ctx->pressure / 10.0 ); 
}

void pressure7_set_over_sampling_ratio ( uint8_t osr_d1, uint8_t osr_d2 )
{
    OSR_D1 = osr_d1;
    OSR_D2 = osr_d2;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t package_data16 ( uint8_t *in_data )
{
    uint16_t out_data;
    
    out_data = in_data[ 0 ];
    out_data = out_data << 8;
    out_data = out_data | in_data[ 1 ];
    
    return out_data;
}

static uint32_t package_data24 ( uint8_t *in_data )
{
    static uint32_t out_data;

    out_data = in_data[ 0 ];
    out_data <<= 8;
    out_data |= in_data[ 1 ];
    out_data <<= 8;
    out_data |= in_data[ 2 ];

    return out_data;
}

static uint8_t crc4 ( uint16_t *n_prom )
{
    uint8_t cnt;
    uint16_t n_rem = 0;
    uint8_t n_bit;
    
    n_prom[ 0 ] = n_prom[ 0 ] & 0x0FFF;
    n_prom[ 7 ] = 0;
    
    for ( cnt = 0; cnt < 16; cnt++ )
    {
        if ( cnt % 2 == 1 )
        {
            n_rem^= n_prom[ cnt >> 1 ] & 0x00FF;
        }
        else
        {
            n_rem^= n_prom[ cnt >> 1 ] >> 8;
        }
        
        for ( n_bit = 8; n_bit > 0; n_bit-- )
        {
            if ( n_rem & 0x8000 )
            {
                n_rem = ( n_rem << 1 )^0x3000;
            }
            else
            {
                n_rem = n_rem << 1;
            }
        }
    }
    n_rem = ( n_rem >> 12 ) & 0x000F;
    return ( n_rem ^ 0x00 );
}

static float pow ( uint8_t base, uint8_t ex )
{
    uint8_t cnt;
    uint32_t tmp = 1;
    
    for ( cnt = 0; cnt < ex; cnt++ )
    {
        tmp *= base;
    }
    
    return tmp;
}

// ------------------------------------------------------------------------- END
