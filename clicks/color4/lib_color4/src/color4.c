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
 * @file color4.c
 * @brief Color 4 Click Driver.
 */

#include "color4.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                        0x00

/**
 * @brief Offset data.
 * @details Offset in open-air conditions.
 * Depending on the optical conditions (e.g. cover glass) this offset may change.
 */
#define COLOR4_OFFSET_OPEN_AIR       0.25168

/**
 * @brief CCT coefficients.
 * @details Coefficients used to calculate correlated color temperature data.
 */
#define COLOR4_CCT_COEFF             4278.6
#define COLOR4_CCT_EXPONENT         -1.2455

/**
 * @brief Sensitivity coefficients.
 * @details Coefficients used to calculate ambient light data in lux.
 */
#define COLOR4_GSENS_40MS             0.25168
#define COLOR4_GSENS_80MS             0.12584
#define COLOR4_GSENS_160MS            0.06292
#define COLOR4_GSENS_320MS            0.03146
#define COLOR4_GSENS_640MS            0.01573
#define COLOR4_GSENS_1280MS           0.007865

void color4_cfg_setup ( color4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COLOR4_DEVICE_ADDRESS;
}

err_t color4_init ( color4_t *ctx, color4_cfg_t *cfg ) 
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

err_t color4_default_cfg ( color4_t *ctx ) 
{
    ctx->offset = COLOR4_OFFSET_OPEN_AIR; 
    color4_config_t config;
    config.integration_time = COLOR4_INTEGRATION_TIME_320MS;
    config.trig             = COLOR4_TRIG_DISABLE;
    config.mode             = COLOR4_AF_AUTO;
    config.chip_shutdown    = COLOR4_SD_ENABLE;
    return color4_set_config( ctx, config );
}

err_t color4_generic_write ( color4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t color4_generic_read ( color4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t color4_set_config ( color4_t *ctx, color4_config_t config ) 
{
    uint8_t data_buf[ 2 ];
    data_buf[ 0 ]  = config.integration_time;
    data_buf[ 0 ] |= config.trig;
    data_buf[ 0 ] |= config.mode;
    data_buf[ 0 ] |= config.chip_shutdown;
    data_buf[ 1 ]  = DUMMY;
    return color4_generic_write( ctx, COLOR4_CMD_CODE_CONF, data_buf, 2 );
}

err_t color4_get_config ( color4_t *ctx, color4_config_t *config ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = color4_generic_read( ctx, COLOR4_CMD_CODE_CONF, data_buf, 2 );
    config->integration_time = data_buf[ 0 ] & COLOR4_INTEGRATION_BIT_MASK;
    config->trig             = data_buf[ 0 ] & COLOR4_TRIG_BIT_MASK;
    config->mode             = data_buf[ 0 ] & COLOR4_AF_BIT_MASK;
    config->chip_shutdown    = data_buf[ 0 ] & COLOR4_SD_BIT_MASK;
    return err_flag;
}

err_t color4_get_color_data ( color4_t *ctx, color4_ch_color_t ch_color, uint16_t *color_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = color4_generic_read( ctx, ch_color + COLOR4_CMD_CODE_RED, data_buf, 2 );
    *color_data = data_buf[ 1 ];
    *color_data <<= 8;
    *color_data |= data_buf[ 0 ];
    return err_flag;
}

err_t color4_get_ambient_light ( color4_t *ctx, float *ambient_light ) 
{
    uint16_t green_color_data;
    float green_sens = COLOR4_GSENS_40MS;
    color4_config_t dev_config;

    err_t err_flag = color4_get_color_data( ctx, COLOR4_GREEN, &green_color_data );
    err_flag |= color4_get_config( ctx, &dev_config );

    switch ( dev_config.integration_time ) 
    {
        case COLOR4_INTEGRATION_TIME_40MS:
        {
            green_sens = COLOR4_GSENS_40MS;
            break;
        }
        case COLOR4_INTEGRATION_TIME_80MS:
        {
            green_sens = COLOR4_GSENS_80MS;
            break;
        }
        case COLOR4_INTEGRATION_TIME_160MS:
        {
            green_sens = COLOR4_GSENS_160MS;
            break;
        }
        case COLOR4_INTEGRATION_TIME_320MS:
        {
            green_sens = COLOR4_GSENS_320MS;
            break;
        }
        case COLOR4_INTEGRATION_TIME_640MS:
        {
            green_sens = COLOR4_GSENS_640MS;
            break;
        }
        case COLOR4_INTEGRATION_TIME_1280MS:
        {
            green_sens = COLOR4_GSENS_1280MS;
            break;
        }
        default:
        {
            err_flag = COLOR4_ERROR;
            green_sens = ( float ) DUMMY;
            break; 
        }
    }

    *ambient_light = ( float ) green_color_data;
    *ambient_light *= ( float ) green_sens;
    return err_flag;
}

err_t color4_get_cct ( color4_t *ctx, float *cct )
{
    uint16_t red_data, blue_data, green_data;
    float ccti_raw;

    err_t err_flag = color4_get_color_data( ctx, COLOR4_RED, &red_data );
    err_flag |= color4_get_color_data( ctx, COLOR4_GREEN, &green_data );
    err_flag |= color4_get_color_data( ctx, COLOR4_BLUE, &blue_data );

    ccti_raw  = ( float ) red_data;
    ccti_raw -= ( float ) blue_data;
    ccti_raw /= ( float ) green_data;
    ccti_raw += ctx->offset; 
    *cct = COLOR4_CCT_COEFF;
    *cct *= pow( ccti_raw, COLOR4_CCT_EXPONENT );

    return err_flag;
}

// ------------------------------------------------------------------------- END
