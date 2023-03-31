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
 * @file ambient22.c
 * @brief Ambient 22 Click Driver.
 */

#include "ambient22.h"

void ambient22_cfg_setup ( ambient22_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT22_DEVICE_ADDRESS_0;
}

err_t ambient22_init ( ambient22_t *ctx, ambient22_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t ambient22_default_cfg ( ambient22_t *ctx ) 
{
    err_t error_flag = AMBIENT22_OK;
    if ( AMBIENT22_ERROR == ambient22_check_communication ( ctx ) )
    {
        return AMBIENT22_ERROR;
    }
    error_flag |= ambient22_write_register ( ctx, AMBIENT22_REG_CONFIGURATION, AMBIENT22_CONFIG_RN_AUTO_SCALE | 
                                                                               AMBIENT22_CONFIG_CT_800_mS | 
                                                                               AMBIENT22_CONFIG_M_CONTINUOUS | 
                                                                               AMBIENT22_CONFIG_L_LATCH | 
                                                                               AMBIENT22_CONFIG_POL_LOW | 
                                                                               AMBIENT22_CONFIG_FC_ONE );
    error_flag |= ambient22_write_register ( ctx, AMBIENT22_REG_LOW_LIMIT, AMBIENT22_RESULT_MAX );
    error_flag |= ambient22_write_register ( ctx, AMBIENT22_REG_HIGH_LIMIT, AMBIENT22_RESULT_MIN );
    return error_flag;
}

err_t ambient22_write_register ( ambient22_t *ctx, uint8_t reg, uint16_t data_in )
{
    if ( ( reg < AMBIENT22_REG_CONFIGURATION ) || ( reg > AMBIENT22_REG_HIGH_LIMIT ) )
    {
        return AMBIENT22_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t ambient22_read_register ( ambient22_t *ctx, uint8_t reg, uint16_t *data_out )
{
    if ( ( reg > AMBIENT22_REG_HIGH_LIMIT ) && 
         ( reg != AMBIENT22_REG_MANUFACTURER_ID ) && 
         ( reg != AMBIENT22_REG_DEVICE_ID ) )
    {
        return AMBIENT22_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    if ( AMBIENT22_OK == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        return AMBIENT22_OK;
    }
    return AMBIENT22_ERROR;
}

err_t ambient22_check_communication ( ambient22_t *ctx )
{
    uint16_t device_id = 0, manufacturer_id = 0;
    if ( ( AMBIENT22_OK == ambient22_read_register( ctx, AMBIENT22_REG_MANUFACTURER_ID, &manufacturer_id ) ) &&
         ( AMBIENT22_OK == ambient22_read_register( ctx, AMBIENT22_REG_DEVICE_ID, &device_id ) ) )
    {
        if ( ( AMBIENT22_MANUFACTURER_ID == manufacturer_id ) && ( AMBIENT22_DEVICE_ID == device_id ) )
        {
            return AMBIENT22_OK;
        }
    }
    return AMBIENT22_ERROR;
}

err_t ambient22_read_lux ( ambient22_t *ctx, float *lux )
{
    uint16_t config, raw_data;
    if ( AMBIENT22_ERROR == ambient22_read_register ( ctx, AMBIENT22_REG_CONFIGURATION, &config ) )
    {
        return AMBIENT22_ERROR;
    }
    // Check the conversion ready flag bit and read result data
    if ( ( AMBIENT22_CONFIG_CRF_MASK != ( config & AMBIENT22_CONFIG_CRF_MASK ) ) || 
         ( AMBIENT22_ERROR == ambient22_read_register( ctx, AMBIENT22_REG_RESULT, &raw_data ) ) )
    {
        return AMBIENT22_ERROR;
    }
    *lux = pow ( 2, ( ( ( raw_data & AMBIENT22_RESULT_EXP ) >> 12 ) ) ) * AMBIENT22_RESULT_LUX_PER_LSB * 
           ( raw_data & AMBIENT22_RESULT_FRACT );
    return AMBIENT22_OK;
}

uint8_t ambient22_get_int_pin ( ambient22_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
