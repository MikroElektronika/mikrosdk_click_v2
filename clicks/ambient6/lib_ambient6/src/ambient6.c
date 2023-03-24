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

#include "ambient6.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ambient6_cfg_setup ( ambient6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AMBIENT6_DEVICE_SLAVE_ADDRESS;
}

AMBIENT6_RETVAL ambient6_init ( ambient6_t *ctx, ambient6_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    ctx->c_gain = 0.5f;
    ctx->c_time = 0.0576f;
    
    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AMBIENT6_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return AMBIENT6_OK;
}

void ambient6_default_cfg ( ambient6_t *ctx )
{
    uint8_t temp_c;
    ambient6_settings( ctx, AMBIENT6_CFG_ALS_SENSITIVITY_X2 | 
                            AMBIENT6_CFG_ALS_TIME_SETTING_25MS |
                            AMBIENT6_CFG_PERSISTENCE_NUMBER_1 |
                            AMBIENT6_CFG_ALS_INT_DISABLE | 
                            AMBIENT6_CFG_ALS_POWER_ON ); 
    
    temp_c = AMBIENT6_POWER_MODE_1 | AMBIENT6_POWER_MODE_ENABLE;
    ambient6_generic_write( ctx, AMBIENT6_CMD_MODE_SETTINGS, &temp_c, 1 );
}

void ambient6_generic_write ( ambient6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void ambient6_generic_read ( ambient6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t ambient6_get_ambient_data ( ambient6_t *ctx )
{
    uint16_t ambient_light;
    uint8_t  command;
    uint8_t read_data[ 2 ];
    
    command = AMBIENT6_CMD_ALS_DATA;

    ambient6_generic_read( ctx, command, read_data, 2 );
    
    ambient_light = read_data[ 1 ];
    ambient_light <<= 8;
    ambient_light |= read_data[ 0 ];

    return ambient_light;
}

void ambient6_settings ( ambient6_t *ctx, uint16_t config_data )
{
    uint8_t tmp[ 2 ];

    tmp[ 0 ] = config_data & 0x00FF;
    tmp[ 1 ] = config_data >> 8;

    ambient6_generic_write( ctx, AMBIENT6_CMD_CONFIGURATION, tmp, 2 );

    // GAIN - Sensitivity mode selection
    if ( ( config_data & AMBIENT6_CFG_ALS_SENSITIVITY_X2 ) != 0 )
    {
        ctx->c_gain = 0.5f;
    }
    else if ( ( config_data & AMBIENT6_CFG_ALS_SENSITIVITY_X1_4 ) != 0 )
    {
        ctx->c_gain = 4.f;
    }
    else if ( ( config_data & AMBIENT6_CFG_ALS_SENSITIVITY_X1_8 ) != 0 )
    {
       ctx->c_gain = 8.f;
    }
    else
    {
        ctx->c_gain = 1.f;
    }
    
    // ALS integration time setting
    if ( ( config_data & AMBIENT6_CFG_ALS_TIME_SETTING_50MS ) != 0 )
    {
        ctx->c_time = 0.1152f;
    }
    else if ( ( config_data & AMBIENT6_CFG_ALS_TIME_SETTING_100MS ) != 0 )
    {
        ctx->c_time = 0.0576f;
    }
    else if ( ( config_data & AMBIENT6_CFG_ALS_TIME_SETTING_25MS ) != 0 )
    {
        ctx->c_time = 0.0288f;
    }
    else if ( ( config_data & AMBIENT6_CFG_ALS_TIME_SETTING_400MS ) != 0 )
    {
        ctx->c_time = 0.0144f;
    }
    else if ( ( config_data & AMBIENT6_CFG_ALS_TIME_SETTING_800MS ) != 0 )
    {
        ctx->c_time = 0.0072f;
    }
    else
    {
        ctx->c_time = 0.2304f;
    }
}

float ambient6_get_ambient_light ( ambient6_t *ctx )
{
    float data_in_lux;
    float lux;
    uint16_t ambient_data;
    
    ambient_data = ambient6_get_ambient_data( ctx );
    
    lux = ambient_data * ctx->c_gain * ctx->c_time;
    data_in_lux = lux * ( 1.0023f + lux * ( 8.1488e-5f + lux * ( -9.3924e-9f + lux * 6.0135e-13f ) ) );

    return data_in_lux;
}

// ------------------------------------------------------------------------- END

