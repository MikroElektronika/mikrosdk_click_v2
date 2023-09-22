/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file uv5.c
 * @brief UV 5 Click Driver.
 */

#include "uv5.h"

void uv5_cfg_setup ( uv5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->syn = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = UV5_DEVICE_ADDRESS_00;
}

err_t uv5_init ( uv5_t *ctx, uv5_cfg_t *cfg ) 
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

    digital_out_init( &ctx->syn, cfg->syn );

    digital_in_init( &ctx->rdy, cfg->rdy );

    return I2C_MASTER_SUCCESS;
}

err_t uv5_default_cfg ( uv5_t *ctx ) 
{
    err_t error_flag = UV5_OK;
    uint8_t tmp_data = 0;
    
    error_flag |= uv5_sw_reset( ctx );
    
    error_flag |= uv5_write_cfg_reg( ctx, UV5_CFG_STATE_REG_OSR, 
                                            UV5_START_MEASURMENT | UV5_CONFIGURATION_MODE );
    
    error_flag |= uv5_write_cfg_reg( ctx, UV5_CFG_STATE_REG_CREG1, 
                                            UV5_GAIN_4X | UV5_TIME_4096_MS );
    
    error_flag |= uv5_read_cfg_reg( ctx, UV5_CFG_STATE_REG_CREG2, &tmp_data );
    tmp_data |= UV5_EN_TM | UV5_EN_DIV;
    
    error_flag |= uv5_write_cfg_reg( ctx, UV5_CFG_STATE_REG_CREG2, tmp_data );
    
    error_flag |= uv5_write_cfg_reg( ctx, UV5_CFG_STATE_REG_CREG3, UV5_MMODE_CONT );
    
    error_flag |= uv5_write_cfg_reg( ctx, UV5_CFG_STATE_REG_BREAK, 0x52 );
    
    error_flag |= uv5_write_cfg_reg( ctx, UV5_CFG_STATE_REG_EDGES, 0x01 );
    
    error_flag |= uv5_write_cfg_reg( ctx, UV5_CFG_STATE_REG_OSR, 
                                            UV5_START_MEASURMENT | UV5_MEASUREMENT_MODE );
    

    return error_flag;
}

err_t uv5_generic_write ( uv5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t uv5_generic_read ( uv5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t uv5_write_cfg_reg ( uv5_t *ctx, uint8_t reg, uint8_t data_in )
{
    return uv5_generic_write( ctx, reg, &data_in, 1 );
}

err_t uv5_write_measu_reg ( uv5_t *ctx, uint8_t reg, uint8_t *data_in )
{
    return uv5_generic_write( ctx, reg, data_in, 2 );
}

err_t uv5_read_cfg_reg ( uv5_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return uv5_generic_read( ctx, reg, data_out, 1 );
}

err_t uv5_read_measu_reg ( uv5_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return uv5_generic_read( ctx, reg, data_out, 2 );
}

void uv5_set_syn_pin ( uv5_t *ctx, uint8_t pin_state )
{
    if ( 1 == pin_state )
    {
        digital_out_high( &ctx->syn );
    }
    else
    {
        digital_out_low( &ctx->syn );
    }
}

uint8_t uv5_get_rdy_pin ( uv5_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

err_t uv5_sw_reset ( uv5_t *ctx )
{
    return uv5_write_cfg_reg( ctx, UV5_CFG_STATE_REG_OSR, UV5_SW_RESET );
}

err_t uv5_temperature_read ( uv5_t *ctx, float *temp_data )
{
    err_t error_flag = UV5_OK;
    uint8_t rx_data[ 2 ] = { 0 };
    uint16_t tmp_data = 0;
    
    error_flag |= uv5_generic_read( ctx, UV5_MESASURE_STATE_REG_TEMP, rx_data, 2 );
    
    tmp_data = ( uint16_t ) ( ( ( uint16_t ) rx_data[ 1 ] ) << 8 | rx_data[ 0 ] );
    
    *temp_data = ( ( float  ) tmp_data * UV5_TEMPERATURE_CALC_CONST ) - UV5_TEMPERATURE_CALC_VALUE;
    
    return error_flag;
}

err_t uv5_channel_uva_read ( uv5_t *ctx, uint16_t *uva_data )
{
    err_t error_flag = UV5_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= uv5_read_measu_reg( ctx, UV5_MESASURE_STATE_REG_MRES1, tmp_data );
    
    *uva_data = ( uint16_t ) ( ( ( uint16_t ) tmp_data[ 1 ] ) << 8 | tmp_data[ 0 ] );
    
    
    return error_flag;
}

err_t uv5_channel_uvb_read ( uv5_t *ctx, uint16_t *uvb_data )
{
    err_t error_flag = UV5_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= uv5_read_measu_reg( ctx, UV5_MESASURE_STATE_REG_MRES2, tmp_data );
    
    *uvb_data = ( uint16_t ) ( ( ( uint16_t ) tmp_data[ 1 ] ) << 8 | tmp_data[ 0 ] );
    
    
    return error_flag;
}

err_t uv5_channel_uvc_read ( uv5_t *ctx, uint16_t *uvc_data )
{
    err_t error_flag = UV5_OK;
    uint8_t tmp_data[ 2 ] = { 0 };
    
    error_flag |= uv5_read_measu_reg( ctx, UV5_MESASURE_STATE_REG_MRES3, tmp_data );
    
    *uvc_data = ( uint16_t ) ( ( ( uint16_t ) tmp_data[ 1 ] ) << 8 | tmp_data[ 0 ] );
    
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
