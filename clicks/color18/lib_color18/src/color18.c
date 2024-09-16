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
 * @file color18.c
 * @brief Color 18 Click Driver.
 */

#include "color18.h"

void color18_cfg_setup ( color18_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->vsync = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COLOR18_DEVICE_ADDRESS;
}

err_t color18_init ( color18_t *ctx, color18_cfg_t *cfg ) 
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

    digital_out_init( &ctx->vsync, cfg->vsync );
    digital_out_high ( &ctx->vsync );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t color18_default_cfg ( color18_t *ctx ) 
{
    err_t error_flag = COLOR18_OK;
    if ( COLOR18_ERROR == color18_check_communication ( ctx ) )
    {
        return COLOR18_ERROR;
    }
    error_flag |= color18_soft_reset ( ctx );
    Delay_100ms ( );
    error_flag |= color18_write_reg ( ctx, COLOR18_REG_OSCEN, COLOR18_OSCEN_OSCEN );
    error_flag |= color18_write_reg ( ctx, COLOR18_REG_ENABLE, COLOR18_ENABLE_PON );
    
    // Set measurement rate to approx. 200ms
    error_flag |= color18_write_reg ( ctx, COLOR18_REG_WTIME, COLOR18_WTIME_DEFAULT );
    error_flag |= color18_write_reg ( ctx, COLOR18_REG_TRIGGER_MODE, COLOR18_TRIGGER_MODE_NORMAL );

    // Enable FIFO interrupt at 16 bytes
    error_flag |= color18_write_reg ( ctx, COLOR18_REG_INTENAB, COLOR18_INTENAB_FIEN );
    error_flag |= color18_write_reg ( ctx, COLOR18_REG_FIFO_THR, ( uint8_t ) ( COLOR18_FIFO_THR_DEFAULT >> 3 ) );
    error_flag |= color18_write_reg ( ctx, COLOR18_REG_CFG2, ( uint8_t ) ( COLOR18_FIFO_THR_DEFAULT & 0x07 ) );

    error_flag |= color18_write_reg ( ctx, COLOR18_REG_ENABLE, COLOR18_ENABLE_PON | COLOR18_ENABLE_AEN );
    error_flag |= color18_clear_fifo ( ctx );
    return error_flag;
}

err_t color18_write_regs ( color18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t color18_read_regs ( color18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t color18_write_reg ( color18_t *ctx, uint8_t reg, uint8_t data_in )
{
    return color18_write_regs ( ctx, reg, &data_in, 1 );
}

err_t color18_read_reg ( color18_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return color18_read_regs ( ctx, reg, data_out, 1 );
}

err_t color18_write_reg_word ( color18_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return color18_write_regs ( ctx, reg, data_buf, 2 );
}

err_t color18_read_reg_word ( color18_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = color18_read_regs ( ctx, reg, data_buf, 2 );
    if ( COLOR18_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return error_flag;
}

err_t color18_check_communication ( color18_t *ctx )
{
    uint8_t device_id = 0;
    if ( COLOR18_OK == color18_read_reg ( ctx, COLOR18_REG_ID, &device_id ) )
    {
        if ( COLOR18_DEVICE_ID == device_id )
        {
            return COLOR18_OK;
        }
    }
    return COLOR18_ERROR;
}

void color18_set_vsync_pin ( color18_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->vsync, state );
}

uint8_t color18_get_int_pin ( color18_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t color18_soft_reset ( color18_t *ctx )
{
    return color18_write_reg ( ctx, COLOR18_REG_CONTROL_SCL, COLOR18_CONTROL_SCL_SOFT_RESET );
}

err_t color18_clear_fifo ( color18_t *ctx )
{
    return color18_write_reg ( ctx, COLOR18_REG_CONTROL, COLOR18_CONTROL_FIFO_CLR );
}

err_t color18_read_fifo_size ( color18_t *ctx, uint16_t *fifo_size )
{
    uint8_t fifo_status[ 2 ] = { 0 };
    err_t error_flag = color18_read_regs ( ctx, COLOR18_REG_FIFO_STATUS0, fifo_status, 2 );
    if ( COLOR18_OK == error_flag )
    {
        *fifo_size = ( ( uint16_t ) fifo_status[ 0 ] << 3 ) | ( fifo_status[ 1 ] & 0x07 );
    }
    return error_flag;
}

err_t color18_read_data ( color18_t *ctx, color18_data_t *data_out )
{
    uint16_t fifo_size = 0;
    uint8_t fifo_data[ 16 ] = { 0 };
    err_t error_flag = color18_read_fifo_size ( ctx, &fifo_size );
    if ( ( COLOR18_OK == error_flag ) && ( fifo_size >= 16 ) )
    {
        error_flag |= color18_read_regs ( ctx, COLOR18_REG_FIFO_DATA, fifo_data, 16 );
        if ( COLOR18_OK == error_flag )
        {
            data_out->x = ( ( uint16_t ) fifo_data[ 1 ] << 8 ) | fifo_data[ 0 ];
            data_out->y = ( ( uint16_t ) fifo_data[ 3 ] << 8 ) | fifo_data[ 2 ];
            data_out->z = ( ( uint16_t ) fifo_data[ 5 ] << 8 ) | fifo_data[ 4 ];
            data_out->ir = ( ( uint16_t ) fifo_data[ 7 ] << 8 ) | fifo_data[ 6 ];
            data_out->hgl = ( ( uint16_t ) fifo_data[ 9 ] << 8 ) | fifo_data[ 8 ];
            data_out->hgh = ( ( uint16_t ) fifo_data[ 11 ] << 8 ) | fifo_data[ 10 ];
            data_out->clear = ( ( uint16_t ) fifo_data[ 13 ] << 8 ) | fifo_data[ 12 ];
            data_out->flicker = ( ( uint16_t ) fifo_data[ 15 ] << 8 ) | fifo_data[ 14 ];
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
