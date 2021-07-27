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

#include "thermoj.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermoj_cfg_setup ( thermoj_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->alert4   = HAL_PIN_NC;
    cfg->alert3 = HAL_PIN_NC;
    cfg->alert2 = HAL_PIN_NC;
    cfg->alert1 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMOJ_I2C_ADDR_0;
}

THERMOJ_RETVAL thermoj_init ( thermoj_t *ctx, thermoj_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed   = cfg->i2c_speed;
    i2c_cfg.scl     = cfg->scl;
    i2c_cfg.sda     = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR  )
    {
        return THERMOJ_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->alert4, cfg->alert4 );
    digital_in_init( &ctx->alert3, cfg->alert3 );
    digital_in_init( &ctx->alert2, cfg->alert2 );
    digital_in_init( &ctx->alert1, cfg->alert1 );
    
    return THERMOJ_OK;
}

void thermoj_generic_write ( thermoj_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void thermoj_generic_read ( thermoj_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void thermoj_write_byte ( thermoj_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    thermoj_generic_write( ctx, reg_address, &write_data, 1 );
}

uint8_t thermoj_read_byte ( thermoj_t *ctx, uint8_t reg_address )
{
    uint8_t r_buffer[ 1 ];

    thermoj_generic_read( ctx, reg_address, r_buffer, 1 );

    return r_buffer[0];
}

uint8_t thermoj_get_status ( thermoj_t *ctx )
{
    uint8_t r_status;

    r_status = thermoj_read_byte( ctx, THERMOJ_STATUS );

    return r_status;
}

uint8_t thermoj_check_burst_complete ( thermoj_t *ctx )
{
    uint8_t r_status;

    r_status = thermoj_read_byte( ctx, THERMOJ_STATUS );

    r_status &= 0x80;

    r_status >>= 7;

    return r_status;
}

uint8_t thermoj_check_data_ready ( thermoj_t *ctx )
{
    uint8_t r_status;

    r_status = thermoj_read_byte( ctx, THERMOJ_STATUS );

    r_status &= 0x40;

    r_status >>= 6;

    return r_status;
}

uint8_t thermoj_check_over_voltage ( thermoj_t *ctx )
{
    uint8_t r_status;

    r_status = thermoj_read_byte( ctx, THERMOJ_STATUS );

    r_status &= 0x10;

    r_status >>= 4;

    return r_status;
}

void thermoj_check_alert_status ( thermoj_t *ctx, uint8_t *alert_1, uint8_t *alert_2, uint8_t *alert_3, uint8_t *alert_4 )
{
    uint8_t r_status;
    uint8_t temp;

    r_status = thermoj_read_byte( ctx, THERMOJ_STATUS );

    r_status &= 0x0F;

    temp = r_status & 0x08;

    if ( temp >> 3 )
    {
        *alert_4 = 1;
    }
    else
    {
        *alert_4 = 0;
    }

    temp = r_status & 0x04;

    if ( temp >> 2 )
    {
        *alert_3 = 1;
    }
    else
    {
        *alert_3 = 0;
    }

    temp = r_status & 0x02;

    if ( temp >> 2 )
    {
        *alert_2 = 1;
    }
    else
    {
        *alert_2 = 0;
    }

    temp = r_status & 0x01;

    if ( temp >> 2 )
    {
        *alert_1 = 1;
    }
    else
    {
        *alert_1 = 0;
    }
}

void thermoj_set_sensor_config ( thermoj_t *ctx, uint8_t config_val )
{
    thermoj_write_byte( ctx, THERMOJ_SENSOR_CONFIG, config_val );
}

void thermoj_set_thermocouple_type ( thermoj_t *ctx, uint8_t thermocouple_type )
{
    uint8_t r_config;
    
    thermocouple_type %= 8;

    r_config = thermoj_read_byte( ctx, THERMOJ_SENSOR_CONFIG );
    
    r_config |= thermocouple_type << 4;
    
    thermoj_write_byte( ctx, THERMOJ_SENSOR_CONFIG, r_config );
}

void thermoj_set_filter_coefficient ( thermoj_t *ctx, uint8_t filter_coeff )
{
    uint8_t r_config;

    filter_coeff %= 8;

    r_config = thermoj_read_byte( ctx, THERMOJ_SENSOR_CONFIG );

    r_config |= filter_coeff;

    thermoj_write_byte( ctx, THERMOJ_SENSOR_CONFIG, r_config );
}

uint8_t thermoj_get_sensor_config ( thermoj_t *ctx )
{
    uint8_t r_config;

    r_config = thermoj_read_byte( ctx, THERMOJ_SENSOR_CONFIG );

    return r_config;
}

void thermoj_set_config ( thermoj_t *ctx, uint8_t config_val )
{
    thermoj_write_byte( ctx, THERMOJ_DEVICE_CONFIG, config_val );
}

void thermoj_set_cold_junction_resolution ( thermoj_t *ctx, uint8_t cj_res )
{
    uint8_t r_status;

    r_status = thermoj_read_byte( ctx, THERMOJ_DEVICE_CONFIG );

    r_status |= cj_res << 7;

    thermoj_write_byte( ctx, THERMOJ_DEVICE_CONFIG, r_status );
}

void thermoj_set_adc_resolution ( thermoj_t *ctx, uint8_t adc_res )
{
    uint8_t r_status;

    r_status = thermoj_read_byte( ctx, THERMOJ_DEVICE_CONFIG );

    r_status |= adc_res << 5;

    thermoj_write_byte( ctx, THERMOJ_DEVICE_CONFIG, r_status );
}

void thermoj_set_number_of_temperature_samples ( thermoj_t *ctx, uint8_t num_temp_samp )
{
    uint8_t r_status;

    r_status = thermoj_read_byte( ctx, THERMOJ_DEVICE_CONFIG );

    r_status |= num_temp_samp << 3;

    thermoj_write_byte( ctx, THERMOJ_DEVICE_CONFIG, r_status );
}

void thermoj_set_shutdown_modes ( thermoj_t *ctx, uint8_t sd_mod )
{
    uint8_t r_status;

    r_status = thermoj_read_byte( ctx, THERMOJ_DEVICE_CONFIG );

    r_status |= sd_mod;

    thermoj_write_byte( ctx, THERMOJ_DEVICE_CONFIG, r_status );
}

void thermoj_write_data ( thermoj_t *ctx, uint8_t reg_address, uint16_t write_data )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = write_data;
    w_buffer[ 1 ] = write_data << 8;

    thermoj_generic_write( ctx, reg_address, w_buffer, 2 );
}

uint16_t thermoj_read_data ( thermoj_t *ctx, uint8_t reg_address )
{
    uint8_t r_buffer[ 2 ];

    uint16_t result;

    thermoj_generic_read( ctx, reg_address, r_buffer, 2 );

    result = r_buffer[ 0 ];
    result <<= 8;
    result |= r_buffer[ 1 ];

    return result;
}

uint8_t thermoj_get_device_id ( thermoj_t *ctx )
{
    uint8_t r_status;

    r_status = thermoj_read_byte( ctx, THERMOJ_DEVICE_ID );

    return r_status;
}

float thermoj_get_temperature ( thermoj_t *ctx )
{
    float temperature;

    uint8_t r_buffer[ 2 ];

    thermoj_generic_read( ctx, THERMOJ_TH, r_buffer, 2 );

    if ( ( r_buffer[ 0 ] & 0x80 ) == 0x80 )
    {
        r_buffer[ 0 ] = r_buffer[ 0 ] & 0x7F;

        temperature = 1024.0;
        temperature -= ( ( float ) r_buffer[ 0 ] ) * 16;
        temperature -= ( ( float ) r_buffer[ 1 ] ) / 16;
    }
    else
    {
        temperature = ( ( float ) r_buffer[ 0 ] ) * 16;
        temperature += ( ( float ) r_buffer[ 1 ] ) / 16;
    }

    return temperature;
}

float thermoj_get_temperature_fahrenheit ( thermoj_t *ctx )
{
    float temperature;
    float result;

    temperature = thermoj_get_temperature( ctx );

    result = temperature * 1.8;
    result += 32.0;

    return result;
}

uint8_t thermoj_get_alert_1 ( thermoj_t *ctx )
{
    return digital_in_read( &ctx->alert1 );
}

uint8_t thermoj_get_alert_2 ( thermoj_t *ctx )
{
    return digital_in_read( &ctx->alert2 );
}

uint8_t thermoj_get_alert_3 ( thermoj_t *ctx )
{
    return digital_in_read( &ctx->alert3 );
}

uint8_t thermoj_get_alert_4 ( thermoj_t *ctx )
{
    return digital_in_read( &ctx->alert4 );
}

void thermoj_set_alerts_limits ( thermoj_t *ctx, uint8_t pos_alert, float temp_alert_limit )
{
    uint16_t temp;
    uint16_t temp_l;
    uint16_t temp_r;
    uint16_t temp_alert_lim;

    temp_alert_limit *= 100;

    temp = ( uint16_t ) temp_alert_limit;

    temp_l = temp / 100;
    temp_r = temp % 100;

    temp_alert_lim = temp_l << 4;

    if ( temp_r == 75 )
    {
        temp_alert_lim |= 0x0003;
    }

    if ( temp_r == 50 )
    {
        temp_alert_lim |= 0x0002;
    }

    if ( temp_r == 25 )
    {
        temp_alert_lim |= 0x0001;
    }

    if ( temp_alert_lim < 0 )
    {
        temp_alert_lim |= 0x8000;
    }

    if ( pos_alert == 1 )
    {
        thermoj_write_data( ctx, THERMOJ_TALERT1, temp_alert_lim );
    }

    if ( pos_alert == 2 )
    {
        thermoj_write_data( ctx, THERMOJ_TALERT2, temp_alert_lim );
    }

    if ( pos_alert == 3 )
    {
        thermoj_write_data( ctx, THERMOJ_TALERT3, temp_alert_lim );
    }

    if ( pos_alert == 4 )
    {
        thermoj_write_data( ctx, THERMOJ_TALERT4, temp_alert_lim );
    }
}

void thermoj_set_alert_config ( thermoj_t *ctx, uint8_t pos_alert, uint8_t alert_config )
{
    uint8_t alert_register;

    alert_register = THERMOJ_ALERT1_CONFIG;
    alert_register |= pos_alert - 1;

    thermoj_write_byte( ctx, alert_register , alert_config );
}

void thermoj_enable_alert ( thermoj_t *ctx, uint8_t pos_alert )
{
    uint8_t r_status;
    uint8_t alert_register;

    alert_register = THERMOJ_ALERT1_CONFIG;
    alert_register |= pos_alert - 1;

    r_status = thermoj_read_byte( ctx, THERMOJ_ALERT1_CONFIG );

    r_status |= 1;

    thermoj_write_byte( ctx, alert_register , r_status );
}

void thermoj_disable_alert ( thermoj_t *ctx, uint8_t pos_alert )
{
    uint8_t r_status;
    uint8_t alert_register;

    alert_register = THERMOJ_ALERT1_CONFIG;
    alert_register |= pos_alert - 1;

    r_status = thermoj_read_byte( ctx, THERMOJ_ALERT1_CONFIG );

    r_status &= 0xFE;

    thermoj_write_byte( ctx, alert_register , r_status );
}

// ------------------------------------------------------------------------- END

