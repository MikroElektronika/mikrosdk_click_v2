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
 * @file grideye3.c
 * @brief Grid-EYE 3 Click Driver.
 */

#include "grideye3.h"

void grideye3_cfg_setup ( grideye3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GRIDEYE3_DEVICE_ADDRESS_1;
}

err_t grideye3_init ( grideye3_t *ctx, grideye3_cfg_t *cfg ) 
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

err_t grideye3_default_cfg ( grideye3_t *ctx ) 
{
    err_t error_flag = GRIDEYE3_OK;
    error_flag |= grideye3_write_reg_byte ( ctx, GRIDEYE3_REG_PCLT, GRIDEYE3_PCLT_NORMAL_MODE );
    error_flag |= grideye3_write_reg_byte ( ctx, GRIDEYE3_REG_RST, GRIDEYE3_RST_FLAG );
    Delay_100ms ( );
    error_flag |= grideye3_write_reg_byte ( ctx, GRIDEYE3_REG_FPSC, GRIDEYE3_FPSC_10FPS );
    error_flag |= grideye3_write_reg_byte ( ctx, GRIDEYE3_REG_INTC, GRIDEYE3_INTC_INTMOD_DIFF | 
                                                                    GRIDEYE3_INTC_INTEN_ACTIVE );
    error_flag |= grideye3_write_reg_byte ( ctx, GRIDEYE3_REG_AVE_SET, GRIDEYE3_AVE_SET_0 );
    error_flag |= grideye3_write_reg_byte ( ctx, GRIDEYE3_REG_AVE_SET, GRIDEYE3_AVE_SET_1 );
    error_flag |= grideye3_write_reg_byte ( ctx, GRIDEYE3_REG_AVE_SET, GRIDEYE3_AVE_SET_2 );
    error_flag |= grideye3_write_reg_byte ( ctx, GRIDEYE3_REG_AVE, GRIDEYE3_AVE_MAMOD_OFF );
    error_flag |= grideye3_write_reg_byte ( ctx, GRIDEYE3_REG_AVE_SET, GRIDEYE3_AVE_SET_3 );
    error_flag |= grideye3_clear_status ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t grideye3_write_reg_bytes ( grideye3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t grideye3_write_reg_byte ( grideye3_t *ctx, uint8_t reg, uint8_t data_in )
{
    return grideye3_write_reg_bytes( ctx, reg, &data_in, 1 );
}

err_t grideye3_write_reg_word ( grideye3_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return grideye3_write_reg_bytes( ctx, reg, data_buf, 2 );
}

err_t grideye3_read_reg_bytes ( grideye3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t grideye3_read_reg_byte ( grideye3_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return grideye3_read_reg_bytes( ctx, reg, data_out, 1 );
}

err_t grideye3_read_reg_word ( grideye3_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = grideye3_read_reg_bytes( ctx, reg, data_buf, 2 );
    if ( ( GRIDEYE3_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return error_flag;
}

uint8_t grideye3_get_int_pin ( grideye3_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t grideye3_read_grid ( grideye3_t *ctx )
{
    uint8_t data_buf[ GRIDEYE3_NUM_PIXELS * 2 ] = { 0 };
    int16_t pixel_data = 0;
    err_t error_flag = grideye3_read_reg_bytes ( ctx, GRIDEYE3_REG_TO1L, data_buf, GRIDEYE3_NUM_PIXELS * 2 );
    for ( uint8_t cnt = 0; ( cnt < GRIDEYE3_NUM_PIXELS ) && ( GRIDEYE3_OK == error_flag ); cnt++ )
    {
        pixel_data = ( ( uint16_t ) data_buf[ cnt * 2 + 1 ] << 8 ) | data_buf[ cnt * 2 ];
        if ( pixel_data & GRIDEYE3_DATA_SIGN_BIT )
        {
            pixel_data |= GRIDEYE3_DATA_FILL_SIGN;
        }
        ctx->grid_temp[ cnt ] = pixel_data * GRIDEYE3_DATA_LSB;
    }
    return error_flag;
}

err_t grideye3_clear_status ( grideye3_t *ctx )
{
    uint8_t status = 0;
    err_t error_flag = grideye3_read_reg_byte ( ctx, GRIDEYE3_REG_STAT, &status );
    error_flag |= grideye3_write_reg_byte ( ctx, GRIDEYE3_REG_SCLR, status );
    return error_flag;
}

// ------------------------------------------------------------------------- END
