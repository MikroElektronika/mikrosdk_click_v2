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
 * @file ledflash3.c
 * @brief LED Flash 3 Click Driver.
 */

#include "ledflash3.h"

void ledflash3_cfg_setup ( ledflash3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->stb = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LEDFLASH3_DEVICE_ADDRESS;
}

err_t ledflash3_init ( ledflash3_t *ctx, ledflash3_cfg_t *cfg ) 
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

    digital_out_init( &ctx->stb, cfg->stb );

    return I2C_MASTER_SUCCESS;
}

err_t ledflash3_default_cfg ( ledflash3_t *ctx ) 
{
    err_t error_flag = LEDFLASH3_OK;
    
    error_flag |= ledflash3_write_reg( ctx, LEDFLASH3_REG_DEVICE_ID, LEDFLASH3_SW_RESET_MASK );
    error_flag |= ledflash3_write_reg( ctx, LEDFLASH3_REG_ENABLE, LEDFLASH3_STROBE_EDGE | LEDFLASH3_STROBE_PIN_ENABLE );
    error_flag |= ledflash3_write_reg( ctx, LEDFLASH3_REG_CONFIGURATION, LEDFLASH3_TIME_OUT_1000MS );
    error_flag |= ledflash3_set_flash_current( ctx, LEDFLASH3_FLASH_CURRENT_MIN );
    error_flag |= ledflash3_set_torch_current( ctx, LEDFLASH3_TORCH_CURRENT_MIN );
    digital_out_low( &ctx->stb );
    
    return error_flag;
}

err_t ledflash3_generic_write ( ledflash3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t ledflash3_generic_read ( ledflash3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t ledflash3_write_reg ( ledflash3_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = LEDFLASH3_OK;
    
    error_flag |= ledflash3_generic_write ( ctx, reg, &data_in, 1 ); 
    
    return error_flag; 
}

err_t ledflash3_read_reg ( ledflash3_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = LEDFLASH3_OK;
    
    error_flag |= ledflash3_generic_read ( ctx, reg, data_out, 1 ); 
    
    return error_flag; 
}

void ledflash3_strobe_pin ( ledflash3_t *ctx )
{
    digital_out_low( &ctx->stb );
    digital_out_high( &ctx->stb );
}

err_t ledflash3_set_flash_current ( ledflash3_t *ctx, float flash_current )
{
    err_t error_flag = LEDFLASH3_OK;
    uint8_t tmp_data = 0;
    
    if ( ( LEDFLASH3_FLASH_CURRENT_MIN > flash_current ) || ( LEDFLASH3_FLASH_CURRENT_MAX < flash_current ) )
    {
        error_flag = LEDFLASH3_ERROR;
    }
    else
    {
        tmp_data = ( uint8_t ) ( ( flash_current / LEDFLASH3_FLASH_CURRENT_MIN ) + LEDFLASH3_ROUND_TO_NEAR_INT ) - 1;
        error_flag = ledflash3_write_reg( ctx, LEDFLASH3_REG_FLASH_CURRENT, tmp_data );
    }
    
    return error_flag; 
}

err_t ledflash3_set_torch_current ( ledflash3_t *ctx, float torch_current )
{
    err_t error_flag = LEDFLASH3_OK;
    uint8_t tmp_data = 0;
    
    if ( ( LEDFLASH3_TORCH_CURRENT_MIN > torch_current ) || ( LEDFLASH3_TORCH_CURRENT_MAX < torch_current ) )
    {
        error_flag = LEDFLASH3_ERROR;
    }
    else
    {
        tmp_data = ( uint8_t ) ( ( torch_current / LEDFLASH3_TORCH_CURRENT_MIN ) + LEDFLASH3_ROUND_TO_NEAR_INT ) - 1;
        error_flag = ledflash3_write_reg( ctx, LEDFLASH3_REG_TOUCH_CURRENT, tmp_data );
    }
    
    return error_flag; 
}

// ------------------------------------------------------------------------- END
