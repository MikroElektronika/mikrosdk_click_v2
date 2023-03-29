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

#include "uv2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void uv2_cfg_setup ( uv2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = UV2_I2C_ADDRESS;
}

UV2_RETVAL uv2_init ( uv2_t *ctx, uv2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return UV2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return UV2_OK;
}

void uv2_default_cfg ( uv2_t *ctx )
{
    uv2_write_data( ctx, UV2_REG_CONF, UV2_CONF_IT_50MS | 
                                       UV2_CONF_HD_NORM | 
                                       UV2_CONF_MODE_TRIG | 
                                       UV2_CONF_AF_OFF | 
                                       UV2_CONF_SD_PWR_ON );
}

void uv2_generic_write ( uv2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void uv2_generic_read ( uv2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void uv2_write_data ( uv2_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t buffer_write[ 2 ];

    buffer_write[ 0 ] = ( uint8_t ) write_data;
    buffer_write[ 1 ] = UV2_WRITE_MSB_BITS;

    uv2_generic_write ( ctx, reg_address, buffer_write, 2 );
}

uint16_t uv2_read_data ( uv2_t *ctx, uint8_t reg_address )
{
    uint8_t buffer_read[ 2 ];
    uint16_t result;

    uv2_generic_read ( ctx, reg_address, buffer_read, 2 );

    result = buffer_read[ 1 ];
    result <<= 8;
    result |= buffer_read [ 0 ];

    return result;
}

void uv2_set_config ( uv2_t *ctx, uint8_t config_value )
{
    uv2_write_data( ctx, UV2_REG_CONF, config_value );
}

void uv2_set_integration_time ( uv2_t *ctx, uint16_t intg_time )
{
    uint8_t temp_data;
    
    temp_data = UV2_CONF_IT_50MS;
    
    if ( intg_time == 100 )
    {
        temp_data = UV2_CONF_IT_100MS;
    }
    if ( intg_time == 200 )
    {
        temp_data = UV2_CONF_IT_200MS;
    }
    if ( intg_time == 400 )
    {
        temp_data = UV2_CONF_IT_400MS;
    }
    if ( intg_time == 800 )
    {
        temp_data = UV2_CONF_IT_800MS;
    }

    uv2_write_data( ctx, UV2_REG_CONF, temp_data );
}

void uv2_set_normal_dynamic ( uv2_t *ctx )
{
    uv2_write_data( ctx, UV2_REG_CONF, UV2_CONF_HD_NORM );
}

void uv2_set_high_dynamic ( uv2_t *ctx )
{
    uv2_write_data( ctx, UV2_REG_CONF, UV2_CONF_HD_HIGH );
}

void uv2_set_trigger_measurement ( uv2_t *ctx )
{
    uv2_write_data( ctx, UV2_REG_CONF, UV2_CONF_ONE_TRIG );
}

void uv2_set_active_force_mode ( uv2_t *ctx, uint8_t force_mode )
{
    uint8_t temp_data;

    temp_data = ( uint8_t ) uv2_read_data( ctx, UV2_REG_CONF );
    
    if ( force_mode )
    {
        temp_data |= UV2_CONF_AF_ON;
    }
    else
    {
        temp_data |= UV2_CONF_AF_OFF;
    }
       
    uv2_write_data( ctx, UV2_REG_CONF, temp_data );
}

void uv2_set_power_on ( uv2_t *ctx )
{
    uint8_t temp_data;

    temp_data = ( uint8_t ) uv2_read_data( ctx, UV2_REG_CONF );

    uv2_write_data( ctx, UV2_REG_CONF, temp_data | UV2_CONF_SD_PWR_ON );
}

void uv2_set_power_off ( uv2_t *ctx )
{
    uint8_t temp_data;

    temp_data = ( uint8_t ) uv2_read_data( ctx, UV2_REG_CONF );

    uv2_write_data( ctx, UV2_REG_CONF, temp_data | UV2_CONF_SD_PWR_OFF );
}

uint8_t uv2_check_id ( uv2_t *ctx )
{
    uint8_t result_id;

    result_id = ( uint8_t ) uv2_read_data( ctx, UV2_REG_DEVID );
    
    if ( result_id != UV2_DEV_ID )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

uint16_t uv2_get_uva ( uv2_t *ctx )
{
    uint16_t result;

    result = uv2_read_data( ctx, UV2_REG_UVA );

    return result;
}

uint16_t uv2_get_uvb ( uv2_t *ctx )
{
    uint16_t result;

    result = uv2_read_data( ctx, UV2_REG_UVB );

    return result;
}

float uv2_get_uv_index ( uv2_t *ctx )
{
    float value_uva;
    float value_uvb;
    float uv_comp_1;
    float uv_comp_2;
    float value_uva_comp;
    float value_uvb_comp;
    float result;

    value_uva = 0.0;
    value_uvb = 0.0;
    uv_comp_1 = 0.0;
    uv_comp_2 = 0.0;
    value_uva_comp = 0.0;
    value_uvb_comp = 0.0;
    result = 0.0;

    value_uva = ( float ) uv2_get_uva( ctx );
    value_uvb = ( float ) uv2_get_uvb( ctx );
    uv_comp_1 = ( float ) uv2_read_data( ctx, UV2_REG_UVCOMP1 );
    uv_comp_2 = ( float ) uv2_read_data( ctx, UV2_REG_UVCOMP2 );

    value_uva_comp = value_uva + ( ( UV2_UVI_UVA_VIS_COEFF * uv_comp_1 ) - ( UV2_UVI_UVA_IR_COEFF * uv_comp_2 ) );
    value_uvb_comp = value_uvb + ( ( UV2_UVI_UVB_VIS_COEFF * uv_comp_1 ) - ( UV2_UVI_UVB_IR_COEFF * uv_comp_2 ) );

    result = ( ( value_uvb_comp * UV2_UVI_UVB_RESPONSE ) + ( value_uva_comp * UV2_UVI_UVA_RESPONSE ) ) / 2.0;

    return result;
}

// ------------------------------------------------------------------------- END

