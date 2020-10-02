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

#include "lightranger2.h"
// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint32_t milliseconds_count ( lightranger2_t* ctx );

static uint8_t check_timeout_expired ( lightranger2_t* ctx );

static void set_timeout ( lightranger2_t* ctx, uint16_t timeout);

static uint16_t get_timeout ( lightranger2_t* ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lightranger2_cfg_setup ( lightranger2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = LIGHTRANGER2_I2C_ADDR;
}

LIGHTRANGER2_RETVAL lightranger2_init ( lightranger2_t *ctx, lightranger2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return LIGHTRANGER2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
  
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return LIGHTRANGER2_OK;

}

LIGHTRANGER2_RETVAL lightranger2_default_cfg ( lightranger2_t *ctx )
{
    uint8_t spad_cnt;
    uint8_t spad_type_aperture;
    uint8_t first_spad_enable;
    uint8_t spads_enabled;
    uint8_t cnt;
    uint8_t tmp_buff;
    uint8_t stop_val;
    uint32_t m_timing_us;
    uint8_t ref_spad_map[ 6 ];
    uint8_t w_buffer[ 7 ];

    Delay_100ms( );
    lightranger2_enable( ctx );
    Delay_100ms( );

    lightranger2_hw_reset( ctx );
    Delay_100ms( );

    tmp_buff = lightranger2_read_byte( ctx, LIGHTRANGER2_VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV );
    tmp_buff |= 0x01;

    lightranger2_write_byte( ctx, LIGHTRANGER2_VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV, tmp_buff );

    lightranger2_write_byte( ctx, 0x88, 0x00 );

    lightranger2_write_byte( ctx, 0x80, 0x01 );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x00, 0x00 );

    stop_val = lightranger2_read_byte( ctx, 0x91 );

    lightranger2_write_byte( ctx, 0x00, 0x01 );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, 0x80, 0x00 );

    tmp_buff = lightranger2_read_byte( ctx, LIGHTRANGER2_MSRC_CONFIG_CONTROL );
    tmp_buff |= 0x12;

    lightranger2_write_byte( ctx, LIGHTRANGER2_MSRC_CONFIG_CONTROL, tmp_buff );
    lightranger2_write_data( ctx, LIGHTRANGER2_FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, 0x0010 );
    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSTEM_SEQUENCE_CONFIG, 0xFF );

    if ( !lightranger2_get_spad_info( ctx, &spad_cnt, &spad_type_aperture ) )
    {
        return LIGHTRANGER2_INIT_ERROR;
    }

    ref_spad_map[ 0 ] = LIGHTRANGER2_GLOBAL_CONFIG_SPAD_ENABLES_REF_0;

    i2c_master_write_then_read( &ctx->i2c, 0, 0, ref_spad_map, 6 );

    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, LIGHTRANGER2_DYNAMIC_SPAD_REF_EN_START_OFFSET, 0x00 );
    lightranger2_write_byte( ctx, LIGHTRANGER2_DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD, 0x2C );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, LIGHTRANGER2_GLOBAL_CONFIG_REF_EN_START_SELECT, 0xB4 );

    first_spad_enable = spad_type_aperture ? 12 : 0;
    spads_enabled = 0;

    for ( cnt = 0; cnt < 48; cnt++ )
    {
        if ( cnt < first_spad_enable || spads_enabled == spad_cnt )
        {
            ref_spad_map[ cnt / 8 ] &= ~(1 << (cnt % 8));
        }
        else if ( ( ref_spad_map[ cnt / 8 ] >> ( cnt % 8 ) ) & 0x01 )
        {
            spads_enabled++;
        }
    }

    w_buffer[ 0 ] = LIGHTRANGER2_GLOBAL_CONFIG_SPAD_ENABLES_REF_0;

    for ( cnt = 1; cnt < 7; cnt++ )
    {
        w_buffer[ cnt ] = ref_spad_map[ cnt - 1 ];
    }

    i2c_master_write( &ctx->i2c, w_buffer, 6 );

    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x00, 0x00 );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, 0x09, 0x00 );
    lightranger2_write_byte( ctx, 0x10, 0x00 );
    lightranger2_write_byte( ctx, 0x11, 0x00 );
    lightranger2_write_byte( ctx, 0x24, 0x01 );
    lightranger2_write_byte( ctx, 0x25, 0xFF );
    lightranger2_write_byte( ctx, 0x75, 0x00 );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x4E, 0x2C );
    lightranger2_write_byte( ctx, 0x48, 0x00 );
    lightranger2_write_byte( ctx, 0x30, 0x20 );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, 0x30, 0x09 );
    lightranger2_write_byte( ctx, 0x54, 0x00 );
    lightranger2_write_byte( ctx, 0x31, 0x04 );
    lightranger2_write_byte( ctx, 0x32, 0x03 );
    lightranger2_write_byte( ctx, 0x40, 0x83 );
    lightranger2_write_byte( ctx, 0x46, 0x25 );
    lightranger2_write_byte( ctx, 0x60, 0x00 );
    lightranger2_write_byte( ctx, 0x27, 0x00 );
    lightranger2_write_byte( ctx, 0x50, 0x06 );
    lightranger2_write_byte( ctx, 0x51, 0x00 );
    lightranger2_write_byte( ctx, 0x52, 0x96 );
    lightranger2_write_byte( ctx, 0x56, 0x08 );
    lightranger2_write_byte( ctx, 0x57, 0x30 );
    lightranger2_write_byte( ctx, 0x61, 0x00 );
    lightranger2_write_byte( ctx, 0x62, 0x00 );
    lightranger2_write_byte( ctx, 0x64, 0x00 );
    lightranger2_write_byte( ctx, 0x65, 0x00 );
    lightranger2_write_byte( ctx, 0x66, 0xA0 );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x22, 0x32 );
    lightranger2_write_byte( ctx, 0x47, 0x14 );
    lightranger2_write_byte( ctx, 0x49, 0xFF );
    lightranger2_write_byte( ctx, 0x4A, 0x00 );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, 0x7A, 0x0A );
    lightranger2_write_byte( ctx, 0x7B, 0x00 );
    lightranger2_write_byte( ctx, 0x78, 0x21 );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x23, 0x34 );
    lightranger2_write_byte( ctx, 0x42, 0x00 );
    lightranger2_write_byte( ctx, 0x44, 0xFF );
    lightranger2_write_byte( ctx, 0x45, 0x26 );
    lightranger2_write_byte( ctx, 0x46, 0x05 );
    lightranger2_write_byte( ctx, 0x40, 0x40 );
    lightranger2_write_byte( ctx, 0x0E, 0x06 );
    lightranger2_write_byte( ctx, 0x20, 0x1A );
    lightranger2_write_byte( ctx, 0x43, 0x40 );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, 0x34, 0x03 );
    lightranger2_write_byte( ctx, 0x35, 0x44 );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x31, 0x04 );
    lightranger2_write_byte( ctx, 0x4B, 0x09 );
    lightranger2_write_byte( ctx, 0x4C, 0x05 );
    lightranger2_write_byte( ctx, 0x4D, 0x04 );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, 0x44, 0x00 );
    lightranger2_write_byte( ctx, 0x45, 0x20 );
    lightranger2_write_byte( ctx, 0x47, 0x08 );
    lightranger2_write_byte( ctx, 0x48, 0x28 );
    lightranger2_write_byte( ctx, 0x67, 0x00 );
    lightranger2_write_byte( ctx, 0x70, 0x04 );
    lightranger2_write_byte( ctx, 0x71, 0x01 );
    lightranger2_write_byte( ctx, 0x72, 0xFE );
    lightranger2_write_byte( ctx, 0x76, 0x00 );
    lightranger2_write_byte( ctx, 0x77, 0x00 );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x0D, 0x01 );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, 0x80, 0x01 );
    lightranger2_write_byte( ctx, 0x01, 0xF8 );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x8E, 0x01 );
    lightranger2_write_byte( ctx, 0x00, 0x01 );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, 0x80, 0x00 );

    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x04 );

    tmp_buff = lightranger2_read_byte( ctx, LIGHTRANGER2_GPIO_HV_MUX_ACTIVE_HIGH );
    tmp_buff &= ~0x10;

    lightranger2_write_byte( ctx, LIGHTRANGER2_GPIO_HV_MUX_ACTIVE_HIGH, tmp_buff );
    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSTEM_INTERRUPT_CLEAR, 0x01 );

    m_timing_us = 10000;

    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSTEM_SEQUENCE_CONFIG, 0xE8 );
    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSTEM_SEQUENCE_CONFIG, 0x01 );

    if ( !lightranger2_single_calibration( ctx, 0x40 ) )
    {
        return LIGHTRANGER2_INIT_ERROR;
    }

    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSTEM_SEQUENCE_CONFIG, 0x02 );

    if ( !lightranger2_single_calibration( ctx, 0x00 ) )
    {
        return LIGHTRANGER2_INIT_ERROR;
    }

    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSTEM_SEQUENCE_CONFIG, 0xE8 );
    
    return LIGHTRANGER2_OK;
}


void lightranger2_write_byte ( lightranger2_t* ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = reg_address;
    w_buffer[ 1 ] = write_data;

    i2c_master_write( &ctx->i2c, w_buffer, 2 );   
}


uint8_t lightranger2_read_byte ( lightranger2_t* ctx, uint8_t reg_address )
{
    uint8_t w_buffer[ 1 ];
    uint8_t r_buffer[ 1 ];

    w_buffer[ 0 ] = reg_address;

    i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, r_buffer, 1 );

    return r_buffer[ 0 ];
}

void lightranger2_write_data ( lightranger2_t* ctx, uint8_t reg_address, uint16_t write_data )
{
    uint8_t buffer[ 3 ];

    buffer[ 0 ] = reg_address;
    buffer[ 1 ] = (write_data >> 8) & 0xFF;
    buffer[ 2 ] = write_data & 0xFF;


    i2c_master_write( &ctx->i2c, buffer, 3 );  
}

uint16_t lightranger2_read_data ( lightranger2_t* ctx, uint8_t reg_address )
{
    uint8_t w_buffer[ 1 ];
    uint8_t r_buffer[ 2 ];
    uint16_t result;

    w_buffer[ 0 ] = reg_address;

    i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, r_buffer, 2 );

    result = 0x00;
    result = r_buffer[ 0 ];
    result <<= 8;
    result |= r_buffer[ 1 ];

    return result;
}

void lightranger2_write_bytes( lightranger2_t* ctx, uint8_t reg_address, uint8_t* write_data, uint8_t n_bytes )
{
    uint16_t cnt;
    uint8_t w_buffer[ 255 ];

    w_buffer[0] = reg_address;

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        w_buffer[ cnt + 1 ] = write_data[ cnt ];
    }

    i2c_master_write( &ctx->i2c, w_buffer, n_bytes + 1 );   
}

void lightranger2_read_bytes ( lightranger2_t* ctx, uint8_t reg_address, uint8_t* read_data, uint8_t n_bytes )
{
    i2c_master_write_then_read( &ctx->i2c, &reg_address, 1, read_data, n_bytes );
}

void lightranger2_hw_reset ( lightranger2_t* ctx )
{
    digital_out_low( &ctx->en );
    Delay_100ms();
    digital_out_high( &ctx->en );
    Delay_100ms();
}

void lightranger2_enable ( lightranger2_t* ctx )
{
    digital_out_high( &ctx->en );
}

void lightranger2_disable ( lightranger2_t* ctx )
{
    digital_out_low(&ctx->en);
}

uint8_t lightranger2_get_interrupt( lightranger2_t* ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void lightranger2_start_continuous( lightranger2_t* ctx, uint32_t period_ms )
{
    uint16_t osc_calibrate;
    uint8_t stop_val;

    lightranger2_write_byte( ctx, 0x80, 0x01 );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x00, 0x00 );

    stop_val = lightranger2_read_byte( ctx, 0x91 );

    lightranger2_write_byte( ctx, 0x91, stop_val );
    lightranger2_write_byte( ctx, 0x00, 0x01 );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, 0x80, 0x00 );

    if ( period_ms != 0 )
    {
        osc_calibrate = lightranger2_read_data( ctx, LIGHTRANGER2_OSC_CALIBRATE_VAL );

        if ( osc_calibrate != 0 )
        {
            period_ms *= osc_calibrate;
        }

        lightranger2_write_data( ctx, LIGHTRANGER2_SYSTEM_INTERMEASUREMENT_PERIOD, 0x03E8 );

        lightranger2_write_byte( ctx, LIGHTRANGER2_SYSRANGE_START, 0x04 );
    }
    else
    {
        lightranger2_write_byte( ctx, LIGHTRANGER2_SYSRANGE_START, 0x02 );
    }
}

void lightranger2_stop_continuous ( lightranger2_t* ctx )
{
    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSRANGE_START, 0x01 );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x00, 0x00 );
    lightranger2_write_byte( ctx, 0x91, 0x00 );
    lightranger2_write_byte( ctx, 0x00, 0x01 );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
}

LIGHTRANGER2_RETVAL lightranger2_set_signal_rate_limit ( lightranger2_t* ctx, float limit_mcps )
{
    uint16_t tmp_data;

    if ( limit_mcps < 0.0 || limit_mcps > 511.99 )
    {
        return LIGHTRANGER2_INIT_ERROR;
    }

    tmp_data = ( uint16_t )limit_mcps;
    tmp_data *= 0x80;

    lightranger2_write_data( ctx, LIGHTRANGER2_FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, tmp_data );

    return LIGHTRANGER2_OK;
}

float lightranger2_get_signal_rate_limit ( lightranger2_t* ctx )
{
    float sr_limit;

    sr_limit = ( float )lightranger2_read_data( ctx, LIGHTRANGER2_FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT );
    sr_limit /= 128.0;

    return sr_limit;
}

LIGHTRANGER2_RETVAL lightranger2_get_spad_info ( lightranger2_t* ctx, uint8_t* count_data, uint8_t* aperture_type )
{
    uint8_t tmp;

    lightranger2_write_byte( ctx, 0x80, 0x01 );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x00, 0x00 );
    lightranger2_write_byte( ctx, 0xFF, 0x06 );

    tmp = lightranger2_read_byte( ctx, 0x83 );
    tmp |= 0x04;

    lightranger2_write_byte( ctx, 0x83, tmp );
    lightranger2_write_byte( ctx, 0xFF, 0x07 );
    lightranger2_write_byte( ctx, 0x81, 0x01 );

    lightranger2_write_byte( ctx, 0x80, 0x01 );

    lightranger2_write_byte( ctx, 0x94, 0x6b );
    lightranger2_write_byte( ctx, 0x83, 0x00 );

    Delay_10ms();

    lightranger2_write_byte( ctx, 0x83, 0x01 );

    tmp = lightranger2_read_byte( ctx, 0x92 );

    *count_data = tmp & 0x7f;
    *aperture_type = ( tmp >> 7 ) & 0x01;

    lightranger2_write_byte( ctx, 0x81, 0x00 );
    lightranger2_write_byte( ctx, 0xFF, 0x06 );

    tmp = lightranger2_read_byte( ctx, 0x83 & ( ~0x04 ) );

    lightranger2_write_byte( ctx, 0x83, tmp );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x00, 0x01 );

    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, 0x80, 0x00 );

    return LIGHTRANGER2_OK;
}

LIGHTRANGER2_RETVAL lightranger2_single_calibration ( lightranger2_t*ctx, uint8_t vhv_init_byte )
{
    vhv_init_byte |= 0x01;

    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSRANGE_START, vhv_init_byte );
                             
    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSTEM_INTERRUPT_CLEAR, 0x01 );
                             
    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSRANGE_START, 0x00 );

    return LIGHTRANGER2_OK;
}

uint16_t lightranger2_get_range_continuous ( lightranger2_t* ctx )
{
    uint16_t range;
    uint16_t timeout = 1000;
    
    while ( 0 == ( lightranger2_read_byte( ctx, LIGHTRANGER2_RESULT_RANGE_STATUS )& 0x07 ) )
    {
        if ( 0 == ( timeout-- ) )
        {
            return 0;
        }
        Delay_1ms();
    }

    range = lightranger2_read_data( ctx, LIGHTRANGER2_RESULT_RANGE_STATUS + 10 );

    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSTEM_INTERRUPT_CLEAR, 0x01 );

    return range;
}

uint16_t lightranger2_get_range_single ( lightranger2_t* ctx )
{
    uint8_t stop_val;
    uint16_t range;

    lightranger2_write_byte( ctx, 0x80, 0x01 );
    lightranger2_write_byte( ctx, 0xFF, 0x01 );
    lightranger2_write_byte( ctx, 0x00, 0x00 );

    stop_val = lightranger2_read_data( ctx, 0x91 );
    lightranger2_write_byte( ctx, 0x91, stop_val );

    lightranger2_write_byte( ctx, 0x00, 0x01 );
    lightranger2_write_byte( ctx, 0xFF, 0x00 );
    lightranger2_write_byte( ctx, 0x80, 0x00 );

    lightranger2_write_byte( ctx, LIGHTRANGER2_SYSRANGE_START, 0x01 );

    while (lightranger2_read_data( ctx, LIGHTRANGER2_SYSRANGE_START) & 0x01 )
    {
        if ( check_timeout_expired( ctx ) )
        {
            ctx->did_timeout = 1;
            return 65535;
        }
    }

    range = lightranger2_get_range_continuous( ctx );

    return range;
}


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint32_t milliseconds_count ( lightranger2_t *ctx )
{
    return ctx->milliseconds_counter;
}

static uint8_t check_timeout_expired ( lightranger2_t* ctx )
{
    return ( ctx->io_timeout > 0 && ( ( uint16_t )milliseconds_count( ctx ) - ctx->timeout_start_ms ) > ctx->io_timeout );
}

static void set_timeout ( lightranger2_t* ctx, uint16_t timeout )
{
    ctx->io_timeout = timeout;
}

static uint16_t get_timeout ( lightranger2_t* ctx )
{
    return ctx->io_timeout;
}


// ------------------------------------------------------------------------- END

