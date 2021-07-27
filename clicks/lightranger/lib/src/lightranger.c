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

#include "lightranger.h"
// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void dev_enable( lightranger_t* ctx );
// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lightranger_cfg_setup ( lightranger_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en   = HAL_PIN_NC;
  
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = LIGHTRANGER_I2C_ADDRESS;
}

LIGHTRANGER_RETVAL lightranger_init ( lightranger_t *ctx, lightranger_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return LIGHTRANGER_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    dev_enable( ctx );

    return LIGHTRANGER_OK;
}

void lightranger_default_cfg ( lightranger_t* ctx )
{
    uint8_t reset;

    reset = lightranger_read_byte( ctx, LIGHTRANGER_SYSTEM_FRESH_OUT_OF_RESET );

    if ( reset == 1 )
    {
        lightranger_write_byte( ctx, 0x0207, 0x01 );
        lightranger_write_byte( ctx, 0x0208, 0x01 );
        lightranger_write_byte( ctx, 0x0096, 0x00 );
        lightranger_write_byte( ctx, 0x0097, 0xFD );
        lightranger_write_byte( ctx, 0x00e3, 0x00 );
        lightranger_write_byte( ctx, 0x00e4, 0x04 );
        lightranger_write_byte( ctx, 0x00e5, 0x02 );
        lightranger_write_byte( ctx, 0x00e6, 0x01 );
        lightranger_write_byte( ctx, 0x00e7, 0x03 );
        lightranger_write_byte( ctx, 0x00f5, 0x02 );
        lightranger_write_byte( ctx, 0x00d9, 0x05 );
        lightranger_write_byte( ctx, 0x00db, 0xce );
        lightranger_write_byte( ctx, 0x00dc, 0x03 );
        lightranger_write_byte( ctx, 0x00dd, 0xf8 );
        lightranger_write_byte( ctx, 0x009f, 0x00 );
        lightranger_write_byte( ctx, 0x00a3, 0x3c );
        lightranger_write_byte( ctx, 0x00b7, 0x00 );
        lightranger_write_byte( ctx, 0x00bb, 0x3c );
        lightranger_write_byte( ctx, 0x00b2, 0x09 );
        lightranger_write_byte( ctx, 0x00ca, 0x09 );
        lightranger_write_byte( ctx, 0x0198, 0x01 );
        lightranger_write_byte( ctx, 0x01b0, 0x17 );
        lightranger_write_byte( ctx, 0x01ad, 0x00 );
        lightranger_write_byte( ctx, 0x00ff, 0x05 );
        lightranger_write_byte( ctx, 0x0100, 0x05 );
        lightranger_write_byte( ctx, 0x0199, 0x05 );
        lightranger_write_byte( ctx, 0x01a6, 0x1b );
        lightranger_write_byte( ctx, 0x01ac, 0x3e );
        lightranger_write_byte( ctx, 0x01a7, 0x1f );
        lightranger_write_byte( ctx, 0x0030, 0x00 );
        lightranger_write_byte( ctx, LIGHTRANGER_SYSTEM_MODE_GPIO1, 0x10 );
        lightranger_write_byte( ctx, LIGHTRANGER_READOUT_AVERAGING_SAMPLE_PERIOD, 0x30 );
        lightranger_write_byte( ctx, LIGHTRANGER_SYSALS_ANALOGUE_GAIN, 0x46 );
        lightranger_write_byte( ctx, LIGHTRANGER_SYSRANGE_VHV_REPEAT_RATE, 0xFF );
        lightranger_write_data( ctx, LIGHTRANGER_SYSALS_INTEGRATION_PERIOD, 0x63 );
        lightranger_write_byte( ctx, LIGHTRANGER_SYSRANGE_VHV_RECALIBRATE, 0x01 );
        lightranger_write_byte( ctx, LIGHTRANGER_SYSRANGE_INTERMEASUREMENT_PERIOD, 0x09 );
        lightranger_write_byte( ctx, LIGHTRANGER_SYSALS_INTERMEASUREMENT_PERIOD, 0x31 );
        lightranger_write_byte( ctx, LIGHTRANGER_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x24 );
        lightranger_write_byte( ctx, LIGHTRANGER_SYSTEM_FRESH_OUT_OF_RESET, 0x00 );
    }
}

void lightranger_write_byte ( lightranger_t* ctx, uint16_t reg_addr, uint8_t write_command )
{
    uint8_t buffer[ 3 ];

    buffer[ 0 ] = ( reg_addr >> 8 ) & 0xFF;
    buffer[ 1 ] = reg_addr & 0xFF;
    buffer[ 2 ] = write_command;

    i2c_master_write( &ctx->i2c, buffer, 3 );  
}

uint8_t lightranger_read_byte ( lightranger_t* ctx, uint16_t reg_addr )
{
    uint8_t write_reg[ 2 ];
    uint8_t read_reg[ 2 ];

    write_reg[ 0 ] = (reg_addr >> 8) & 0xFF;
    write_reg[ 1 ] = reg_addr & 0xFF;

    i2c_master_write_then_read( &ctx->i2c, write_reg, 2, read_reg, 1 );

    return read_reg[ 0 ];
}

void lightranger_write_data ( lightranger_t* ctx, uint16_t reg_addr, uint16_t write_command )
{
    uint8_t buffer[ 4 ];

    buffer[ 0 ] = ( reg_addr >> 8 ) & 0xFF;
    buffer[ 1 ] = reg_addr & 0xFF;
    buffer[ 3 ] = ( write_command >> 8 ) & 0xFF;
    buffer[ 4 ] = write_command & 0xFF;

    i2c_master_write( &ctx->i2c, buffer, 4 );
}

uint16_t lightranger_read_data ( lightranger_t* ctx, uint16_t reg_addr)
{
    uint8_t write_reg[ 2 ];
    uint8_t read_reg[ 2 ];
    uint16_t result;

    write_reg[ 0 ] = (reg_addr >> 8) & 0xFF;
    write_reg[ 1 ] = reg_addr & 0xFF;

    i2c_master_write_then_read( &ctx->i2c, write_reg, 2, read_reg, 2 );

    result = 0x00;
    result = read_reg[ 0 ];
    result <<= 8;
    result |= read_reg[ 1 ];

    return result;
}

void lightranger_start_single_shot_range_mode ( lightranger_t* ctx )
{
    lightranger_write_byte( ctx, LIGHTRANGER_SYSRANGE_START, 0x01 );
}

float lightranger_get_ambiant_light ( lightranger_t* ctx, uint8_t als_gain_check )
{
    uint16_t als_raw;
    uint16_t als_integration_period;
    float als_integration_period_float;
    float als_gain;
    float lux_value;

    als_raw = 0;
    als_integration_period = 0;

    lightranger_write_byte( ctx, LIGHTRANGER_SYSALS_ANALOGUE_GAIN, ( 0x40 | als_gain_check ) );
    lightranger_write_byte( ctx, LIGHTRANGER_SYSALS_START, 0x01 );
    Delay_100ms();
    lightranger_write_byte( ctx, LIGHTRANGER_SYSTEM_INTERRUPT_CLEAR, 0x07 );
    als_raw = lightranger_read_data( ctx, LIGHTRANGER_RESULT_ALS_VAL );
    als_integration_period = lightranger_read_data( ctx, LIGHTRANGER_SYSALS_INTEGRATION_PERIOD );
    als_integration_period_float = 100.0 / ( als_integration_period + 1 );
    als_gain = 0.0;
    switch ( als_gain_check )
    {
        case 0:
        {
            als_gain = 20.0;
            break;
        }
        case 1:
        {
            als_gain = 10.32;
            break;
        }
        case 2:
        {
            als_gain = 5.21;
            break;
        }
        case 3:
        {
            als_gain = 2.60;
            break;
        }
        case 4:
        {
            als_gain = 1.72;
            break;
        }
        case 5:
        {
            als_gain = 1.28;
            break;
        }
        case 6:
        {
            als_gain = 1.01;
            break;
        }
        case 7:
        {
            als_gain = 40.0;
            break;
        }

        default:
        {
            break;
        }		
    }

    lux_value = ( float )0.32 * ( ( float )als_raw / als_gain ) * als_integration_period_float;

    return lux_value;
}

uint8_t lightranger_get_distance ( lightranger_t* ctx )
{
    uint8_t range;

    range = lightranger_read_byte( ctx, LIGHTRANGER_RESULT_RANGE_VAL );

    return range;
}

void lightranger_poll_range ( lightranger_t* ctx )
{
    uint8_t status;
    uint8_t range_status;

    status = lightranger_read_byte( ctx, LIGHTRANGER_RESULT_INTERRUPT_STATUS_GPIO );
    range_status = status & 0x07;

    while ( range_status != 0x04 )
    {
        status = lightranger_read_byte( ctx, LIGHTRANGER_RESULT_INTERRUPT_STATUS_GPIO );
        range_status = status & 0x07;
        Delay_1ms();
    }

}

void lightranger_interrupts_clear ( lightranger_t* ctx )
{
    lightranger_write_byte( ctx, LIGHTRANGER_SYSTEM_INTERRUPT_CLEAR, LIGHTRANGER_CMD_INTERRUPT_CLEAR );
}

// ------------------------------------------------ PRIVATE FUNCTION DEFINITIONS

static void dev_enable( lightranger_t* ctx )
{
    digital_out_low( &ctx->en );
    Delay_10ms( );
    Delay_10ms( );
    digital_out_high( &ctx->en );
    Delay_10ms( );
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

