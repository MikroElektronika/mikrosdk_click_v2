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

#include "barometer2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define  TEMPERATURE_DATA_READY  0x02
#define  PRESSURE_DATA_READY     0x01

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void get_complement_of_two( int32_t *raw, uint8_t length );
static uint8_t wait_until_data_ready( barometer2_t *ctx, uint8_t tp );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void barometer2_cfg_setup ( barometer2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = BAROMETER2_DEVICE_SLAVE_ADDR_GND;
}

BAROMETER2_RETVAL barometer2_init ( barometer2_t *ctx, barometer2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return BAROMETER2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return BAROMETER2_OK;
}

void barometer2_default_cfg ( barometer2_t *ctx )
{
    // Configuration

    barometer2_write_byte( ctx, BAROMETER2_REG_CTRL_2, BAROMETER2_CTRL2_BOOT_NORMAL_MODE |
                                                 BAROMETER2_CTRL2_FIFO_DISABLED |
                                                 BAROMETER2_CTRL2_FIFO_THR_DISABLED |
                                                 BAROMETER2_CTRL2_ID_ADD_INC_ENABLED |
                                                 BAROMETER2_CTRL2_MODE_IDLE );
    
    barometer2_write_byte( ctx, BAROMETER2_REG_INTERRUPT_CONFIG, BAROMETER2_ICFG_INT_GENERATION_ENABLE |
                                                           BAROMETER2_ICFG_AUTORIFP_DISABLE |
                                                           BAROMETER2_ICFG_AUTORIFP_RESET |
                                                           BAROMETER2_ICFG_AUTOZERO_DISABLE  |
                                                           BAROMETER2_ICFG_AUTOZERO_RESET |
                                                           BAROMETER2_ICFG_INT_NOT_LATCHED );

    barometer2_write_byte( ctx, BAROMETER2_REG_CTRL_1, BAROMETER2_CTRL1_ODR_75Hz |
                                                 BAROMETER2_CTRL1_LPFP_ENABLE |
                                                 BAROMETER2_CTRL1_LPFP_CFG_ODR_10 |
                                                 BAROMETER2_CTRL1_BDU_CONT_UPDATE );

    barometer2_write_byte( ctx, BAROMETER2_REG_CTRL_3, BAROMETER2_CTRL3_INT_ACTIVE_HIGH |
                                                 BAROMETER2_CTRL3_INT_PUSH_PULL |
                                                 BAROMETER2_CTRL3_FIFO_FULL_DISABLED |
                                                 BAROMETER2_CTRL3_FIFO_WTM_DISABLED |
                                                 BAROMETER2_CTRL3_FIFO_OVERRUN_DISABLED |
                                                 BAROMETER2_CTRL3_DRDY_ENABLED |
                                                 BAROMETER2_CTRL3_DRDY_STATUS_P_HIGH |
                                                 BAROMETER2_CTRL3_DRDY_STATUS_P_LOW ); 
}

void barometer2_generic_write ( barometer2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void barometer2_generic_read ( barometer2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void barometer2_write_byte ( barometer2_t *ctx, uint8_t reg, uint8_t data_bytes )
{
    uint8_t data_buf[ 1 ];

    data_buf[ 0 ] = data_bytes;

    barometer2_generic_write( ctx, reg, data_buf, 1 );
}

uint8_t barometer2_read_byte ( barometer2_t *ctx, uint8_t reg )
{
    uint8_t read_buf[ 1 ];

    barometer2_generic_read( ctx, reg, read_buf, 1 );

    return read_buf[ 0 ];
}

float barometer2_get_temperature ( barometer2_t *ctx, uint8_t temp_format )
{
    int16_t temp_raw;
    float temperature;
    
    wait_until_data_ready( ctx, TEMPERATURE_DATA_READY );
    
    temp_raw = barometer2_read_byte( ctx, BAROMETER2_REG_TEMPERATURE_MSB );
    temp_raw <<= 8;
    temp_raw |= barometer2_read_byte( ctx, BAROMETER2_REG_TEMPERATURE_LSB );
    
    temperature = temp_raw / 100.0;
    
    if ( temp_format == BAROMETER2_TEMPERATURE_IN_FARENHAJT )
    {
        return temperature * 9/5 + 32;
    }
    else if ( temp_format == BAROMETER2_TEMPERATURE_IN_KELVIN )
    {
        return temperature + 273.15;
    }
    
    return temperature;
}

void barometer2_software_reset ( barometer2_t *ctx )
{
    barometer2_write_byte( ctx, BAROMETER2_REG_CTRL_2, BAROMETER2_CTRL2_SOFTWARE_RESET );
}

float barometer2_get_pressure ( barometer2_t *ctx, uint8_t press_format )
{
    int32_t press_raw;
    float pressure;

    wait_until_data_ready( ctx, PRESSURE_DATA_READY );
    
    press_raw = barometer2_read_byte( ctx, BAROMETER2_REG_PRESSURE_OUT_H );
    press_raw <<= 8;
    press_raw |= barometer2_read_byte( ctx, BAROMETER2_REG_PRESSURE_OUT_L );
    press_raw <<= 8;
    press_raw |= barometer2_read_byte( ctx, BAROMETER2_REG_PRESSURE_OUT_XL );
    
    get_complement_of_two( &press_raw, 24 );
    
    pressure = press_raw / 4094.0;
    
    if ( press_format == BAROMETER2_PRESSURE_DATA_IN_kPa )
    {
        pressure *= 0.1;
    }
    else if ( ( press_format == BAROMETER2_PRESSURE_DATA_IN_Torr ) || ( press_format == BAROMETER2_PRESSURE_DATA_IN_mmHg ) )
    {
        pressure *= 0.750062;
    }
    else if ( press_format == BAROMETER2_PRESSURE_DATA_IN_Bar )
    {
        pressure *= 0.001;
    }
    
    return pressure;
}

uint8_t barometer2_get_interrupt ( barometer2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void get_complement_of_two ( int32_t *raw, uint8_t length )
{
    if ( *raw & ( ( uint32_t ) 1 << ( length - 1 ) ) )
    {
        *raw -= ( uint32_t ) 1 << length;
    }
}

static uint8_t wait_until_data_ready ( barometer2_t *ctx, uint8_t tp )
{
    uint8_t tmp;
    uint16_t cnt = 0;

    do
    {
        cnt++;
        Delay_10ms( );

        if ( cnt > 20 )
        {
            return 1;
        }

        tmp = barometer2_read_byte( ctx, BAROMETER2_REG_STATUS );

    } while ( ( tmp & tp ) == 0 );

    return 0;
}

// ------------------------------------------------------------------------- END

