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

#include "temphum3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum3_cfg_setup ( temphum3_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->addr = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x41;
}

err_t temphum3_init ( temphum3_t *ctx, temphum3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    // Output pins 
    digital_out_init( &ctx->addr, cfg->addr );
   
    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TEMPHUM3_OK;
}

void temphum3_default_cfg ( temphum3_t *ctx )
{
    temphum3_set_mode( ctx, TEMPHUM3_MODE_ACTIVE );

    temphum3_set_measurement( ctx, TEMPHUM3_MCONF_TEMP_RES_14BIT |
                                   TEMPHUM3_MCONF_HUM_RES_14BIT | 
                                   TEMPHUM3_MCONF_HUM_TEMP | 
                                   TEMPHUM3_MCONF_MEAS_START );
    
    temphum3_set_configuration( ctx, TEMPHUM3_CONF_NORMAL_MODE |
                                     TEMPHUM3_CONF_ODR_REPEATED_1SEC |
                                     TEMPHUM3_CONF_HEATER_OFF |
                                     TEMPHUM3_CONF_INT_DRDY_HIGH_Z |
                                     TEMPHUM3_CONF_INT_POL_LOW |
                                     TEMPHUM3_CONF_INT_MODE_SENSITIVE ); 
                             
    temphum3_set_high_temp ( ctx, 45 );
    temphum3_set_low_temp ( ctx, 10 );
    temphum3_set_high_hum ( ctx, 30 );
    temphum3_set_low_hum ( ctx, 70 );
}

void temphum3_generic_write ( temphum3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
}

void temphum3_generic_read ( temphum3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void temphum3_set_measurement ( temphum3_t *ctx, uint8_t value )
{
    temphum3_generic_write( ctx, TEMPHUM3_REG_MEASUREMENT_CONF, &value, 1 );
}

void temphum3_set_configuration ( temphum3_t *ctx, uint8_t value )
{
    temphum3_generic_write ( ctx, TEMPHUM3_REG_RST_DRDY_INT_CONF, &value, 1 );
}

void temphum3_set_mode ( temphum3_t *ctx, uint8_t value )
{
    digital_out_write( &ctx->addr, value );
}

float temphum3_get_temperature ( temphum3_t *ctx )
{
    uint8_t reg_data[ 2 ] = { 0 };
    uint16_t temp_data = 0;
    float temp = 0;
    
    temphum3_generic_read( ctx, TEMPHUM3_REG_TEMPERATURE, reg_data, 2 );

    temp_data = ( ( uint16_t ) reg_data[ 1 ] << 8 ) | reg_data[ 0 ]; 
    temp = temp_data / 65535.0;
    temp = temp * 165;
    temp = temp - 40.0;
    
    return temp; 
}

float temphum3_get_humidity ( temphum3_t *ctx )
{
    uint8_t reg_data[ 2 ] = { 0 };
    uint16_t hum_data = 0;
    float hum = 0;

    temphum3_generic_read( ctx, TEMPHUM3_REG_HUMIDITY, reg_data, 2 );

    hum_data = ( ( uint16_t ) reg_data[ 1 ] << 8 ) | reg_data[ 0 ];  
    hum = hum_data / 65535.0;
    hum = hum * 100;
    
    return hum;
}

uint16_t temphum3_get_id ( temphum3_t *ctx )
{
    uint8_t reg_data[ 2 ] = { 0 };
    temphum3_generic_read( ctx, TEMPHUM3_REG_DEVICE_ID, &reg_data, 2 );
    return ( ( uint16_t ) reg_data[ 1 ] << 8 ) | reg_data[ 0 ];  
}

uint16_t temphum3_get_manufacturer_id ( temphum3_t *ctx )
{
    uint8_t reg_data[ 2 ] = { 0 };
    temphum3_generic_read( ctx, TEMPHUM3_REG_MANUFACTURER_ID, &reg_data, 2 );
    return ( ( uint16_t ) reg_data[ 1 ] << 8 ) | reg_data[ 0 ]; 
}

uint8_t temphum3_get_status_interrupt ( temphum3_t *ctx, uint8_t mask )
{
    uint8_t reg_data = 0;
    
    temphum3_generic_read( ctx, TEMPHUM3_REG_INTERRUPT_DRDY, &reg_data, 1 );
    
    if ( reg_data & mask )
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

uint8_t temphum3_get_interrupt_mask ( temphum3_t *ctx, uint8_t mask )
{
    uint8_t reg_data = 0;
    
    temphum3_generic_read( ctx, TEMPHUM3_REG_INTERRUPT_MASK, &reg_data, 1 );
    
    if ( reg_data & mask )
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

void temphum3_set_offset ( temphum3_t *ctx, uint8_t reg, uint8_t value )
{
    temphum3_generic_write( ctx, reg, &value, 1 );
}

void temphum3_set_high_temp ( temphum3_t *ctx, uint8_t temp_data )
{
    uint8_t reg_data = ( uint8_t )( ( temp_data + 40 ) / 165.0 * 0xFF );

    temphum3_generic_write( ctx, TEMPHUM3_REG_TEMP_THRESHOLD_HIGH, &reg_data, 1 );
}

void temphum3_set_low_temp ( temphum3_t *ctx, uint8_t temp_data )
{
    uint8_t reg_data = ( uint8_t )( ( temp_data + 40 ) / 165.0 * 0xFF );

    temphum3_generic_write( ctx, TEMPHUM3_REG_TEMP_THRESHOLD_LOW, &reg_data, 1 );
}

void temphum3_set_high_hum( temphum3_t *ctx, uint8_t hum_data )
{
    uint8_t reg_data = ( uint8_t )( ( hum_data / 100.0 ) * 0xFF );

    temphum3_generic_write( ctx, TEMPHUM3_REG_HUM_THRESHOLD_HIGH, &reg_data, 1 );
}

void temphum3_set_low_hum( temphum3_t *ctx, uint8_t hum_data )
{
    uint8_t reg_data = ( uint8_t )( ( hum_data / 100.0 ) * 0xFF );

    temphum3_generic_write( ctx, TEMPHUM3_REG_HUM_THRESHOLD_LOW, &reg_data, 1 );
}

float temphum3_get_max_hum ( temphum3_t *ctx )
{
    uint8_t reg_data = 0;
    float hum_data = 0;

    temphum3_generic_read( ctx, TEMPHUM3_REG_HUMIDITY_MAX, &reg_data, 1 );
    
    hum_data = ( reg_data / 255.0 ) * 100;
    return hum_data;
}

float temphum3_get_max_temp ( temphum3_t *ctx )
{
    uint8_t reg_data = 0;
    float temp_data = 0;

    temphum3_generic_read( ctx, TEMPHUM3_REG_TEMPERATURE_MAX, &reg_data, 1 );
    
    temp_data = ( reg_data / 255.0 ) * 100;  
    temp_data = temp_data - 40.0;

    return temp_data;
}

// ------------------------------------------------------------------------- END

