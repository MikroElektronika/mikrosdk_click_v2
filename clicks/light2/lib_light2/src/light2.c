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
 * @file light2.c
 * @brief Light 2 Click Driver.
 */

#include "light2.h"

void light2_cfg_setup ( light2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LIGHT2_DEVICE_ADDRESS_0;
}

err_t light2_init ( light2_t *ctx, light2_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t light2_default_cfg ( light2_t *ctx ) 
{
    err_t error_flag = LIGHT2_OK;
    
    error_flag |= light2_write_config( ctx, LIGHT2_EN_DEVICE | LIGHT2_EN_CONT_MEASURE | LIGHT2_16_BIT_ADC | LIGHT2_RANGE_2 );
    error_flag |= light2_get_cal_const( ctx );

    return error_flag;
}

err_t light2_generic_write ( light2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t light2_generic_read ( light2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t light2_write_config ( light2_t *ctx, uint8_t data_in )
{
    return light2_generic_write( ctx, LIGHT2_REG_COMMAND, &data_in, 1 );
}

err_t light2_read_raw_data ( light2_t *ctx, uint16_t *data_out )
{
    err_t error_flag = LIGHT2_OK;
    uint8_t tmp_data[ 2 ] = { 0 };

    error_flag |= light2_generic_read( ctx, LIGHT2_REG_DATA_LSB, &tmp_data[ 0 ], 1 );
    error_flag |= light2_generic_read( ctx, LIGHT2_REG_DATA_MSB, &tmp_data[ 1 ], 1 );

    *data_out = ( ( uint16_t ) tmp_data[ 1 ] << 8 ) | tmp_data[ 0 ];

    return error_flag;
}

err_t light2_get_cal_const ( light2_t *ctx )
{
    err_t error_flag = LIGHT2_OK;
    uint8_t command_data = 0;
    uint16_t k_const = 0;
    uint16_t count_max = 0;

    error_flag |= light2_generic_read( ctx, LIGHT2_REG_COMMAND, &command_data, 1 );

    switch ( command_data & LIGHT2_RANGE_MASK )
    {
        case LIGHT2_RANGE_1:
        {
            k_const = LIGHT2_RANGE_1_MAX;
            break;
        }
        case LIGHT2_RANGE_2:
        {
            k_const = LIGHT2_RANGE_2_MAX;
            break;
        }
        case LIGHT2_RANGE_3:
        {
            k_const = LIGHT2_RANGE_3_MAX;
            break;
        }
        case LIGHT2_RANGE_4:
        {
            k_const = LIGHT2_RANGE_4_MAX;
            break;
        }
        default:
        {
            error_flag = LIGHT2_ERROR;  
        }
    }

    switch ( command_data & LIGHT2_ADC_RESOLUTION_MASK )
    {
        case LIGHT2_16_BIT_ADC:
        {
            count_max = LIGHT2_16_BIT_MAX;
            break;
        }
        case LIGHT2_12_BIT_ADC:
        {
            count_max = LIGHT2_12_BIT_MAX;
            break;
        }
        case LIGHT2_8_BIT_ADC:
        {
            count_max = LIGHT2_8_BIT_MAX;
            break;
        }
        case LIGHT2_4_BIT_ADC:
        {
            count_max = LIGHT2_4_BIT_MAX;
            break;
        }
        default:
        {
            error_flag = LIGHT2_ERROR;  
        }
    }

    ctx->a_const = ( ( float ) k_const / ( float ) count_max );

    return error_flag;
}

err_t light2_get_light_data ( light2_t *ctx, float *light_data )
{
    err_t error_flag = LIGHT2_OK;
    uint16_t adc_data = 0;

    error_flag |= light2_read_raw_data( ctx, &adc_data );

    *light_data = ctx->a_const * ( float ) adc_data;

    return error_flag;
}

// ------------------------------------------------------------------------- END
