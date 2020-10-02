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

#include "vcpmonitor2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void vcpmonitor2_cfg_setup ( vcpmonitor2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = VCPMONITOR2_DEVICE_SLAVE_ADDR_GND;
}

VCPMONITOR2_RETVAL vcpmonitor2_init ( vcpmonitor2_t *ctx, vcpmonitor2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return VCPMONITOR2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    return VCPMONITOR2_OK;
}

void vcpmonitor2_default_cfg ( vcpmonitor2_t *ctx )
{
    vcpmonitor2_configuration( ctx, VCPMONITOR2_CFG_CH_1_ENABLE | 
                               VCPMONITOR2_CFG_CH_2_ENABLE |
                               VCPMONITOR2_CFG_CH_3_ENABLE |
                               VCPMONITOR2_CFG_AVG_64 |
                               VCPMONITOR2_CFG_VBUS_CT_1100us | 
                               VCPMONITOR2_CFG_VSH_CT_1100us |
                               VCPMONITOR2_CFG_MODE_CONT_SHUNT_BUS_VOLT );
                               
    vcpmonitor2_reset_alert( ctx );
    vcpmonitor2_alert_config( ctx, VCPMONITOR2_ALERT_PVALID |
                              VCPMONITOR2_ALERT_WRNG | 
                              VCPMONITOR2_ALERT_CRTCL |
                              VCPMONITOR2_ALERT_TCTRL );
}

void vcpmonitor2_generic_write ( vcpmonitor2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void vcpmonitor2_generic_read ( vcpmonitor2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t vcpmonitor2_get_manifacture_id ( vcpmonitor2_t *ctx )
{
    uint16_t id;
    uint8_t tmp[ 2 ];
        
    i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );

    vcpmonitor2_generic_read( ctx, VCPMONITOR2_REG_MANUFACTURER_ID, tmp, 2 );

    id = tmp[ 0 ] << 8; 
    id |= tmp[ 1 ]; 

    if ( id == VCPMONITOR2_DEF_MANUFACTURE_ID )
    {
        return id;
    }
    return DEVICE_ERROR;
}

uint16_t vcpmonitor2_get_die_id ( vcpmonitor2_t *ctx )
{
    uint16_t id;
    uint8_t tmp[ 2 ];

    i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );
    
    vcpmonitor2_generic_read( ctx, VCPMONITOR2_REG_DIE_ID, tmp, 2 );

    id = tmp[ 0 ] << 8;
    id |= tmp[ 1 ];

    if ( id == VCPMONITOR2_DEF_DIE_ID )
    {
        return id;
    }
    return DEVICE_ERROR;
}

float vcpmonitor2_get_bus_voltage ( vcpmonitor2_t *ctx, uint8_t channel )
{
    float bus_volt;
    int16_t raw_data;
    uint8_t tmp[ 2 ];
    
    i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );
    
    if ( channel == VCPMONITOR2_CHANNEL_1 )
    {
        vcpmonitor2_generic_read( ctx, VCPMONITOR2_REG_CH_1_BUS_VOLT, tmp, 2 );
        raw_data = tmp[ 0 ] << 8;
        raw_data |= tmp[ 1 ];
        raw_data <<= 3;
    }

    else if ( channel == VCPMONITOR2_CHANNEL_2 )
    { 
        i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );
        
        vcpmonitor2_generic_read( ctx, VCPMONITOR2_REG_CH_2_BUS_VOLT, tmp, 2 );
        raw_data = tmp[ 0 ] << 8;
        raw_data |= tmp[ 1 ];
        raw_data <<= 3;
    }

    else if ( channel == VCPMONITOR2_CHANNEL_3 )
    {
        i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );
        
        vcpmonitor2_generic_read( ctx, VCPMONITOR2_REG_CH_3_BUS_VOLT, tmp, 2 );
        raw_data = tmp[ 0 ] << 8;
        raw_data |= tmp[ 1 ];
        raw_data <<= 3;
    }
    
    bus_volt = (float)( raw_data * 0.008 ) * 1000;
    return bus_volt;
}

float vcpmonitor2_get_shunt_voltage ( vcpmonitor2_t *ctx, uint8_t channel )
{
    float shunt_volt;
    int16_t raw_data;
    uint8_t tmp[ 2 ];

    if ( channel == VCPMONITOR2_CHANNEL_1 )
    {
        i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );
        
        vcpmonitor2_generic_read( ctx, VCPMONITOR2_REG_CH_1_SHUNT_VOLT, tmp, 2 );
        raw_data = tmp[ 0 ] << 8;
        raw_data |= tmp[ 1 ];
        raw_data <<= 3;
    }

    else if ( channel == VCPMONITOR2_CHANNEL_2 )
    {
        i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );
        
        vcpmonitor2_generic_read( ctx, VCPMONITOR2_REG_CH_2_SHUNT_VOLT, tmp, 2 );
        raw_data = tmp[ 0 ] << 8;
        raw_data |= tmp[ 1 ];
        raw_data <<= 3;
    }

    else if ( channel == VCPMONITOR2_CHANNEL_3 )
    {
        i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );
        
        vcpmonitor2_generic_read( ctx, VCPMONITOR2_REG_CH_3_SHUNT_VOLT, tmp, 2 );
        raw_data = tmp[ 0 ] << 8;
        raw_data |= tmp[ 1 ];
        raw_data <<= 3;
    }
    
    shunt_volt = (float)( raw_data * 0.00004 ) * 1000;
    return shunt_volt;
}

float vcpmonitor2_get_current ( vcpmonitor2_t *ctx, uint8_t channel )
{
    float current;
    uint8_t tmp;

    i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );

    if ( channel == VCPMONITOR2_CHANNEL_1 )
    {
        current = vcpmonitor2_get_shunt_voltage( ctx, VCPMONITOR2_CHANNEL_1 );
    }

    else if ( channel == VCPMONITOR2_CHANNEL_2 )
    {
        i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );
        
        vcpmonitor2_generic_read( ctx, VCPMONITOR2_REG_CH_2_SHUNT_VOLT, &tmp, 1 );
        current = tmp;
    }

    else if ( channel == VCPMONITOR2_CHANNEL_3 )
    {
        i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );
        
        vcpmonitor2_generic_read( ctx, VCPMONITOR2_REG_CH_3_SHUNT_VOLT, &tmp, 1 );
        current = tmp;
    }
    
    current /= 0.1;
    return current;
}

float vcpmonitor2_get_power ( vcpmonitor2_t *ctx, uint8_t channel )
{
    float bus_volt;
    float current;
    
    bus_volt = vcpmonitor2_get_bus_voltage( ctx, channel );
    current = vcpmonitor2_get_current( ctx, channel );

    return  ( bus_volt * current ) / 1000000;
}

void vcpmonitor2_configuration ( vcpmonitor2_t *ctx, uint16_t cfg )
{
    uint8_t tmp;
    
    i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );

    vcpmonitor2_generic_write( ctx, VCPMONITOR2_REG_CONFIGURATION, &tmp, 1 );
    cfg = tmp;
}

uint8_t vcpmonitor2_get_alert_status ( vcpmonitor2_t *ctx )
{
    uint8_t status;
    uint8_t reg = VCPMONITOR2_ALERT_REG_INPUT;
    
    i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );

    vcpmonitor2_generic_read( ctx, VCPMONITOR2_ALERT_REG_INPUT, &status, 1  );

    return status;
}

void vcpmonitor2_reset_alert ( vcpmonitor2_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );

    digital_out_low( &ctx->rst );
    Delay_100ms( );

    Delay_100ms( );
    digital_out_high( &ctx->rst );
}

void vcpmonitor2_alert_config ( vcpmonitor2_t *ctx, uint8_t cfg )
{
    uint8_t tx_data[ 2 ];

    // CONFIGURATION
    tx_data[ 0 ] = VCPMONITOR2_ALERT_REG_CONFIG;
    tx_data[ 1 ] = cfg;

    i2c_master_set_slave_address( &ctx->i2c, VCPMONITOR2_DEVICE_SLAVE_ADDR_GND );

    vcpmonitor2_generic_write( ctx, VCPMONITOR2_ALERT_REG_CONFIG, tx_data, 2 );
    
    // POLARITY SET
    tx_data[ 0 ] = VCPMONITOR2_ALERT_REG_POLARITY;
    tx_data[ 1 ] = 0x0F;  // Invert

    vcpmonitor2_generic_write( ctx, VCPMONITOR2_ALERT_REG_POLARITY, tx_data, 2 );
}

// ------------------------------------------------------------------------- END

