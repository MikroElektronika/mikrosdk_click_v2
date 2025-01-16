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
 * @file nixiepowerin12b.c
 * @brief Nixie Power IN-12B Click Driver.
 */

#include "nixiepowerin12b.h"

void nixiepowerin12b_cfg_setup ( nixiepowerin12b_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = NIXIEPOWERIN12B_DEVICE_ADDRESS_4;
}

err_t nixiepowerin12b_init ( nixiepowerin12b_t *ctx, nixiepowerin12b_cfg_t *cfg ) 
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

err_t nixiepowerin12b_default_cfg ( nixiepowerin12b_t *ctx ) 
{
    err_t error_flag = NIXIEPOWERIN12B_OK;
    error_flag |= nixiepowerin12b_write_reg ( ctx, NIXIEPOWERIN12B_REG_IODIRA, NIXIEPOWERIN12B_DIR_ALL_OUTPUT );
    error_flag |= nixiepowerin12b_write_reg ( ctx, NIXIEPOWERIN12B_REG_IODIRB, NIXIEPOWERIN12B_DIR_ALL_OUTPUT );
    error_flag |= nixiepowerin12b_write_reg ( ctx, NIXIEPOWERIN12B_REG_OLATA, NIXIEPOWERIN12B_PIN_CLEAR );
    error_flag |= nixiepowerin12b_write_reg ( ctx, NIXIEPOWERIN12B_REG_OLATB, NIXIEPOWERIN12B_PIN_CLEAR );
    return error_flag;
}

err_t nixiepowerin12b_write_regs ( nixiepowerin12b_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t nixiepowerin12b_read_regs ( nixiepowerin12b_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t nixiepowerin12b_write_reg ( nixiepowerin12b_t *ctx, uint8_t reg, uint8_t data_in )
{
    return nixiepowerin12b_write_regs ( ctx, reg, &data_in, 1 );
}

err_t nixiepowerin12b_read_reg ( nixiepowerin12b_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t nixiepowerin12b_set_digit ( nixiepowerin12b_t *ctx, uint8_t digit, uint8_t comma )
{
    err_t error_flag = NIXIEPOWERIN12B_OK;
    uint8_t outa = NIXIEPOWERIN12B_PIN_CLEAR;
    uint8_t outb = NIXIEPOWERIN12B_PIN_CLEAR;
    if ( ( digit > NIXIEPOWERIN12B_DIGIT_NONE ) || ( comma > NIXIEPOWERIN12B_COMMA_SET ) )
    {
        return NIXIEPOWERIN12B_ERROR;
    }
    if ( NIXIEPOWERIN12B_COMMA_SET == comma )
    {
        outb |= NIXIEPOWERIN12B_PIN_PB6_LHCM;
    }
    switch ( digit )
    {
        case NIXIEPOWERIN12B_DIGIT_0:
        {
            outa |= NIXIEPOWERIN12B_PIN_PA1_K0;
            break;
        }
        case NIXIEPOWERIN12B_DIGIT_1:
        {
            outb |= NIXIEPOWERIN12B_PIN_PB5_K1;
            break;
        }
        case NIXIEPOWERIN12B_DIGIT_2:
        {
            outb |= NIXIEPOWERIN12B_PIN_PB4_K2;
            break;
        }
        case NIXIEPOWERIN12B_DIGIT_3:
        {
            outb |= NIXIEPOWERIN12B_PIN_PB3_K3;
            break;
        }
        case NIXIEPOWERIN12B_DIGIT_4:
        {
            outb |= NIXIEPOWERIN12B_PIN_PB2_K4;
            break;
        }
        case NIXIEPOWERIN12B_DIGIT_5:
        {
            outb |= NIXIEPOWERIN12B_PIN_PB1_K5;
            break;
        }
        case NIXIEPOWERIN12B_DIGIT_6:
        {
            outb |= NIXIEPOWERIN12B_PIN_PB0_K6;
            break;
        }
        case NIXIEPOWERIN12B_DIGIT_7:
        {
            outa |= NIXIEPOWERIN12B_PIN_PA5_K7;
            break;
        }
        case NIXIEPOWERIN12B_DIGIT_8:
        {
            outa |= NIXIEPOWERIN12B_PIN_PA3_K8;
            break;
        }
        case NIXIEPOWERIN12B_DIGIT_9:
        {
            outa |= NIXIEPOWERIN12B_PIN_PA2_K9;
            break;
        }
        default:
        {
            break;
        }
    }
    error_flag |= nixiepowerin12b_write_reg ( ctx, NIXIEPOWERIN12B_REG_OLATA, outa );
    error_flag |= nixiepowerin12b_write_reg ( ctx, NIXIEPOWERIN12B_REG_OLATB, outb );
    return error_flag;
}

// ------------------------------------------------------------------------- END
