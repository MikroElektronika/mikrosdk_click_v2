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
 * @file currentlimit5.c
 * @brief Current Limit 5 Click Driver.
 */

#include "currentlimit5.h"

void currentlimit5_cfg_setup ( currentlimit5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CURRENTLIMIT5_SET_DEV_ADDR;
}

err_t currentlimit5_init ( currentlimit5_t *ctx, currentlimit5_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->fault, cfg->fault );

    return I2C_MASTER_SUCCESS;
}

err_t currentlimit5_default_cfg ( currentlimit5_t *ctx ) 
{
    err_t error_flag = CURRENTLIMIT5_OK;
    
    error_flag |= currentlimit5_set_ilimit ( ctx, CURRENTLIMIT5_ILIMIT_200mA );
    
    currentlimit5_enable_limit ( ctx );
    
    return error_flag;
}

err_t currentlimit5_set_ilimit ( currentlimit5_t *ctx, currentlimit5_ilimit_t ilimit )
{
    uint16_t rlimit = CURRENTLIMIT5_DIGIPOT_MAX_VALUE + CURRENTLIMIT5_DIGIPOT_OFFSET;
    switch ( ilimit )
    {
        case CURRENTLIMIT5_ILIMIT_100mA:
        {
            rlimit -= 1920;
            break;
        }
        case CURRENTLIMIT5_ILIMIT_200mA:
        {
            rlimit -= 1000;
            break;
        }
        case CURRENTLIMIT5_ILIMIT_300mA:
        {
            rlimit -= 672;
            break;
        }
        case CURRENTLIMIT5_ILIMIT_400mA:
        {
            rlimit -= 508;
            break;
        }
        case CURRENTLIMIT5_ILIMIT_500mA:
        {
            rlimit -= 412;
            break;
        }
        case CURRENTLIMIT5_ILIMIT_600mA:
        {
            rlimit -= 344;
            break;
        }
        case CURRENTLIMIT5_ILIMIT_700mA:
        {
            rlimit -= 298;
            break;
        }
        case CURRENTLIMIT5_ILIMIT_800mA:
        {
            rlimit -= 263;
            break;
        }
        case CURRENTLIMIT5_ILIMIT_900mA:
        {
            rlimit -= 235;
            break;
        }
        case CURRENTLIMIT5_ILIMIT_1000mA:
        {
            rlimit -= 213;
            break;
        }
        case CURRENTLIMIT5_ILIMIT_1100mA:
        {
            rlimit -= 195;
            break;
        }
        default:
        {
            return CURRENTLIMIT5_ERROR;
        }
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 1 ] = ( uint8_t ) ( ( ( float ) rlimit / CURRENTLIMIT5_DIGIPOT_MAX_VALUE ) * 
                                  CURRENTLIMIT5_DIGIPOT_RESOLUTION + CURRENTLIMIT5_ROUND_TO_NEAREST_INT );
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

uint8_t currentlimit5_get_fault_pin ( currentlimit5_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

void currentlimit5_enable_limit ( currentlimit5_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void currentlimit5_disable_limit ( currentlimit5_t *ctx )
{
    digital_out_low ( &ctx->en );
}

// ------------------------------------------------------------------------- END
