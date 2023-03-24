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
 * @file efuse5.c
 * @brief eFuse 5 Click Driver.
 */

#include "efuse5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                             0

/**
 * @brief eFuse 5 description resistance data.
 * @details Specified resistance data 
 * for description of eFuse 5 Click driver.
 */
#define ILIM_RES_4000_Ohm_MIN         4000
#define ILIM_RES_9000_Ohm             9000
#define ILIM_RES_12000_Ohm           12000
#define ILIM_RES_13000_Ohm           13000
#define ILIM_RES_15200_Ohm           15200
#define ILIM_RES_18000_Ohm           18000
#define ILIM_RES_20000_Ohm           20000
#define ILIM_RES_20720_Ohm           20720
#define ILIM_RES_24700_Ohm           24700
#define ILIM_RES_30000_Ohm_MAX       30000
#define ZERO_SCALE_RES_60_Ohm           60
#define FULL_SCALE_RES_50000_Ohm     50000

/**
 * @brief eFuse 5 description digital potentiometer wiper data.
 * @details Specified digital potentiometer wiper data 
 * for description of eFuse 5 Click driver.
 */
#define WIPER_START_POS                  1
#define WIPER_POS_MAX                 0x3F

void efuse5_cfg_setup ( efuse5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->mon   = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->pgd = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EFUSE5_DEVICE_ADDRESS;
}

err_t efuse5_init ( efuse5_t *ctx, efuse5_cfg_t *cfg ) 
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

    digital_in_init( &ctx->mon, cfg->mon );
    digital_in_init( &ctx->pgd, cfg->pgd );
    digital_in_init( &ctx->flt, cfg->flt );

    return I2C_MASTER_SUCCESS;
}

err_t efuse5_default_cfg ( efuse5_t *ctx ) 
{
    efuse5_enable_device( ctx );
    return efuse5_write_rdac( ctx, DUMMY );
}

err_t efuse5_write_byte ( efuse5_t *ctx, uint8_t inst, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = inst;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t efuse5_generic_read ( efuse5_t *ctx, uint8_t *data_out ) 
{
    return i2c_master_read( &ctx->i2c, data_out, 1 );
}

err_t efuse5_write_rdac ( efuse5_t *ctx, uint8_t rdac_data )
{
    return efuse5_write_byte( ctx, EFUSE5_WRITE_TO_RDAC, rdac_data );
}

err_t efuse5_read_rdac ( efuse5_t *ctx, uint8_t *rdac_data )
{
    err_t error_flag = EFUSE5_OK;
    uint8_t rx_data = DUMMY;
    error_flag = efuse5_generic_read( ctx, &rx_data );
    if ( rx_data & EFUSE5_OTP_V_ERROR )
    {
        error_flag = EFUSE5_ERROR;
    }
    else
    {
        *rdac_data = rx_data & WIPER_POS_MAX;
    }
    return error_flag;
}

err_t efuse5_set_digi_pot ( efuse5_t *ctx, uint8_t wiper_pos )
{
    return efuse5_write_rdac( ctx, wiper_pos & WIPER_POS_MAX );
}

err_t efuse5_set_resistance ( efuse5_t *ctx, uint16_t res_ohm )
{
    err_t err_flag = EFUSE5_ERROR;
    if ( ( res_ohm <= ILIM_RES_30000_Ohm_MAX ) && ( res_ohm >= ILIM_RES_4000_Ohm_MIN ) )
    {
        float tmp  = ( float ) res_ohm;
        tmp -= ZERO_SCALE_RES_60_Ohm;
        tmp /= FULL_SCALE_RES_50000_Ohm;
        tmp *= WIPER_POS_MAX;
        tmp -= WIPER_START_POS;
        err_flag = efuse5_set_digi_pot( ctx, ( uint8_t ) tmp );   
    }
    return err_flag;
}

err_t efuse5_set_current_limit ( efuse5_t *ctx, efuse5_current_limit_t current_limit )
{
    err_t err_flag = EFUSE5_ERROR;
    switch ( current_limit )
    {
        case EFUSE5_CURRENT_LIMIT_600_mA:
        {
            err_flag = efuse5_set_resistance( ctx, ILIM_RES_30000_Ohm_MAX );
            break;
        }
        case EFUSE5_CURRENT_LIMIT_720_mA:
        {
            err_flag = efuse5_set_resistance( ctx, ILIM_RES_24700_Ohm );
            break;
        }
        case EFUSE5_CURRENT_LIMIT_865_mA:
        {
            err_flag = efuse5_set_resistance( ctx, ILIM_RES_20720_Ohm );
            break;
        }
        case EFUSE5_CURRENT_LIMIT_900_mA:
        {
            err_flag = efuse5_set_resistance( ctx, ILIM_RES_20000_Ohm );
            break;
        }
        case EFUSE5_CURRENT_LIMIT_1030_mA:
        {
            err_flag = efuse5_set_resistance( ctx, ILIM_RES_18000_Ohm );
            break;
        }
        case EFUSE5_CURRENT_LIMIT_1200_mA:
        {
            err_flag = efuse5_set_resistance( ctx, ILIM_RES_15200_Ohm );
            break;
        }
        case EFUSE5_CURRENT_LIMIT_1445_mA:
        {
            err_flag = efuse5_set_resistance( ctx, ILIM_RES_13000_Ohm );
            break;
        }
        case EFUSE5_CURRENT_LIMIT_1550_mA:
        {
            err_flag = efuse5_set_resistance( ctx, ILIM_RES_12000_Ohm );
            break;
        }
        case EFUSE5_CURRENT_LIMIT_2000_mA: 
        {
            err_flag = efuse5_set_resistance( ctx, ILIM_RES_9000_Ohm );
            break;
        }
        case EFUSE5_CURRENT_LIMIT_4500_mA: 
        {
            err_flag = efuse5_set_resistance( ctx, ILIM_RES_4000_Ohm_MIN );
            break;
        }
        default: 
        {
            err_flag |= efuse5_set_resistance( ctx, ILIM_RES_30000_Ohm_MAX );
            break;
        }    
    }
    return err_flag;
}

void efuse5_enable_device ( efuse5_t *ctx )
{
    digital_out_high( &ctx->en );
}

void efuse5_shutdown ( efuse5_t *ctx )
{
    digital_out_low( &ctx->en );
}

uint8_t efuse5_get_imon ( efuse5_t *ctx )
{
    return digital_in_read( &ctx->mon );
}

uint8_t efuse5_get_pgood ( efuse5_t *ctx )
{
    return digital_in_read( &ctx->pgd );
}

uint8_t efuse5_get_fault ( efuse5_t *ctx )
{
    return digital_in_read( &ctx->flt );
}

// ------------------------------------------------------------------------- END
