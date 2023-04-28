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
 * @file dcmotor25.c
 * @brief DC Motor 25 Click Driver.
 */

#include "dcmotor25.h"

void dcmotor25_cfg_setup ( dcmotor25_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->in1 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DCMOTOR25_DEVICE_ADDRESS;
}

err_t dcmotor25_init ( dcmotor25_t *ctx, dcmotor25_cfg_t *cfg ) 
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

    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_init( &ctx->in2, cfg->in2 );

    return I2C_MASTER_SUCCESS;
}

err_t dcmotor25_default_cfg ( dcmotor25_t *ctx ) 
{   
    dcmotor25_standby( ctx );
    
    return dcmotor25_set_resistance( ctx, DCMOTOR25_RES_DEFAULT_20_kOhm );
}

err_t dcmotor25_write_byte ( dcmotor25_t *ctx, uint8_t inst, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = inst;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t dcmotor25_read_byte ( dcmotor25_t *ctx, uint8_t *data_out ) 
{
    return i2c_master_read( &ctx->i2c, data_out, 1 );
}

err_t dcmotor25_write_rdac ( dcmotor25_t *ctx, uint8_t rdac_data )
{
    return dcmotor25_write_byte( ctx, DCMOTOR25_WRITE_TO_RDAC, rdac_data );
}

err_t dcmotor25_read_rdac ( dcmotor25_t *ctx, uint8_t *rdac_data )
{
    err_t error_flag = DCMOTOR25_OK;
    uint8_t rx_data = 0;
    error_flag = dcmotor25_read_byte( ctx, &rx_data );
    if ( rx_data & DCMOTOR25_OTP_V_ERROR )
    {
        error_flag = DCMOTOR25_ERROR;
    }
    else
    {
        *rdac_data = rx_data & DCMOTOR25_WIPER_POS_MAX;
    }
    return error_flag;
}

err_t dcmotor25_set_digi_pot ( dcmotor25_t *ctx, uint8_t wiper_pos )
{
    return dcmotor25_write_rdac( ctx, wiper_pos & DCMOTOR25_WIPER_POS_MAX );
}

err_t dcmotor25_set_resistance ( dcmotor25_t *ctx, uint16_t res_ohm )
{
    err_t err_flag = DCMOTOR25_ERROR;
    if ( ( res_ohm <= DCMOTOR25_FULL_SCALE_RES_50_kOhm ) && 
         ( res_ohm >= DCMOTOR25_RESISTANCE_MIN ) )
    {
        float tmp  = ( float ) res_ohm;
        tmp /= DCMOTOR25_FULL_SCALE_RES_50_kOhm;
        tmp *= DCMOTOR25_WIPER_POS_MAX;
        tmp = DCMOTOR25_WIPER_POS_MAX - tmp;
        err_flag = dcmotor25_set_digi_pot( ctx, ( uint8_t ) tmp );
    }
    return err_flag;
}

void dcmotor25_standby ( dcmotor25_t *ctx )
{
    digital_out_low( &ctx->in1 );
    digital_out_low( &ctx->in2 );
}

void dcmotor25_reverse ( dcmotor25_t *ctx )
{
    digital_out_low( &ctx->in1 );
    digital_out_high( &ctx->in2 );
}

void dcmotor25_forward ( dcmotor25_t *ctx )
{
    digital_out_high( &ctx->in1 );
    digital_out_low( &ctx->in2 );
}

void dcmotor25_brake ( dcmotor25_t *ctx )
{
    digital_out_high( &ctx->in1 );
    digital_out_high( &ctx->in2 );
}

// ------------------------------------------------------------------------- END
