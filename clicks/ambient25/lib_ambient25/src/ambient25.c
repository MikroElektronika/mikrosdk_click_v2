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
 * @file ambient25.c
 * @brief Ambient 25 Click Driver.
 */

#include "ambient25.h"

void ambient25_cfg_setup ( ambient25_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->vsync = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT25_DEVICE_ADDRESS;
}

err_t ambient25_init ( ambient25_t *ctx, ambient25_cfg_t *cfg ) 
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
    digital_out_init( &ctx->vsync, cfg->vsync );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t ambient25_default_cfg ( ambient25_t *ctx ) 
{
    err_t error_flag = AMBIENT25_OK;
    ambient25_enable_device( ctx );
    Delay_100ms ( );
    if ( AMBIENT25_ERROR == ambient25_check_communication ( ctx ) )
    {
        return AMBIENT25_ERROR;
    }
    error_flag |= ambient25_soft_reset ( ctx );
    Delay_100ms ( );
    error_flag |= ambient25_write_reg ( ctx, AMBIENT25_REG_ENABLE, AMBIENT25_ENABLE_PON );
    
    // Set measurement rate to approx. 200ms
    error_flag |= ambient25_write_reg ( ctx, AMBIENT25_REG_WTIME, AMBIENT25_WTIME_DEFAULT );
    error_flag |= ambient25_write_reg ( ctx, AMBIENT25_REG_TRIGGER_MODE, AMBIENT25_TRIGGER_MODE_NORMAL );

    // Set ALS data MSB position
    error_flag |= ambient25_write_reg ( ctx, AMBIENT25_REG_MEAS_MODE1, AMBIENT25_MEAS_MODE1_ALS_MSB_POSITION_DEFAULT );

    // Enable FIFO interrupt at 6 bytes
    error_flag |= ambient25_write_reg ( ctx, AMBIENT25_REG_INTENAB, AMBIENT25_INTENAB_FIEN );
    error_flag |= ambient25_write_reg ( ctx, AMBIENT25_REG_FIFO_THR, ( uint8_t ) ( AMBIENT25_FIFO_THR_DEFAULT >> 1 ) );
    error_flag |= ambient25_write_reg ( ctx, AMBIENT25_REG_CFG2, ( uint8_t ) ( AMBIENT25_FIFO_THR_DEFAULT & 0x01 ) );
    
    // Set modulator 0 gain to 32x and modulator 1 to 4x
    error_flag |= ambient25_write_reg ( ctx, AMBIENT25_REG_MEAS_SEQR_STEP0_MOD_GAINX_L, AMBIENT25_GAIN_MOD1_4X | 
                                                                                        AMBIENT25_GAIN_MOD0_32X );

    // Enable sensor and clear FIFO
    error_flag |= ambient25_write_reg ( ctx, AMBIENT25_REG_ENABLE, AMBIENT25_ENABLE_PON | AMBIENT25_ENABLE_AEN );
    error_flag |= ambient25_clear_fifo ( ctx );
    return error_flag;
}

err_t ambient25_write_regs ( ambient25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t ambient25_read_regs ( ambient25_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t ambient25_write_reg ( ambient25_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ambient25_write_regs ( ctx, reg, &data_in, 1 );
}

err_t ambient25_read_reg ( ambient25_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ambient25_read_regs ( ctx, reg, data_out, 1 );
}

err_t ambient25_write_reg_word ( ambient25_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return ambient25_write_regs ( ctx, reg, data_buf, 2 );
}

err_t ambient25_read_reg_word ( ambient25_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = ambient25_read_regs ( ctx, reg, data_buf, 2 );
    if ( AMBIENT25_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return error_flag;
}

err_t ambient25_check_communication ( ambient25_t *ctx )
{
    uint8_t device_id = 0;
    if ( AMBIENT25_OK == ambient25_read_reg ( ctx, AMBIENT25_REG_ID, &device_id ) )
    {
        if ( AMBIENT25_DEVICE_ID == device_id )
        {
            return AMBIENT25_OK;
        }
    }
    return AMBIENT25_ERROR;
}

void ambient25_enable_device ( ambient25_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void ambient25_disable_device ( ambient25_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void ambient25_set_vsync_pin ( ambient25_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->vsync, state );
}

uint8_t ambient25_get_int_pin ( ambient25_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t ambient25_soft_reset ( ambient25_t *ctx )
{
    return ambient25_write_reg ( ctx, AMBIENT25_REG_CONTROL, AMBIENT25_CONTROL_SOFT_RESET );
}

err_t ambient25_clear_fifo ( ambient25_t *ctx )
{
    return ambient25_write_reg ( ctx, AMBIENT25_REG_CONTROL, AMBIENT25_CONTROL_FIFO_CLR );
}

err_t ambient25_read_fifo_size ( ambient25_t *ctx, uint16_t *fifo_size )
{
    uint8_t fifo_status[ 2 ] = { 0 };
    err_t error_flag = ambient25_read_regs ( ctx, AMBIENT25_REG_FIFO_STATUS0, fifo_status, 2 );
    if ( AMBIENT25_OK == error_flag )
    {
        *fifo_size = ( ( uint16_t ) fifo_status[ 0 ] << 2 ) | ( fifo_status[ 1 ] & 0x03 );
    }
    return error_flag;
}

err_t ambient25_read_data ( ambient25_t *ctx, ambient25_data_t *data_out )
{
    uint16_t fifo_size = 0;
    uint8_t fifo_data[ 6 ] = { 0 };
    err_t error_flag = ambient25_read_fifo_size ( ctx, &fifo_size );
    if ( ( AMBIENT25_OK == error_flag ) && ( fifo_size > AMBIENT25_FIFO_THR_DEFAULT ) )
    {
        error_flag |= ambient25_read_regs ( ctx, AMBIENT25_REG_FIFO_DATA, fifo_data, 6 );
        if ( AMBIENT25_OK == error_flag )
        {
            data_out->als_data_0 = ( ( uint16_t ) fifo_data[ 1 ] << 8 ) | fifo_data[ 0 ];
            data_out->als_data_1 = ( ( uint16_t ) fifo_data[ 3 ] << 8 ) | fifo_data[ 2 ];
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
