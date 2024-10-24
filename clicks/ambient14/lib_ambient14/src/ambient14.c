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
 * @file ambient14.c
 * @brief Ambient 14 Click Driver.
 */

#include "ambient14.h"

void ambient14_cfg_setup ( ambient14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sby = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT14_DEVICE_ADDRESS;
}

err_t ambient14_init ( ambient14_t *ctx, ambient14_cfg_t *cfg ) 
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

    digital_out_init( &ctx->sby, cfg->sby );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t ambient14_default_cfg ( ambient14_t *ctx ) 
{
    err_t error_flag = AMBIENT14_OK;
    ambient14_enable_device ( ctx );
    if ( AMBIENT14_ERROR == ambient14_check_communication ( ctx ) )
    {
        return AMBIENT14_ERROR;
    }
    error_flag |= ambient14_soft_reset ( ctx );
    Delay_100ms ( );
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_ENABLE, AMBIENT14_ENABLE_PON );
    Delay_100ms ( );
    error_flag |= ambient14_set_atime ( ctx, AMBIENT14_ATIME_DEFAULT );
    error_flag |= ambient14_set_awtime ( ctx, AMBIENT14_AWTIME_DEFAULT );
    error_flag |= ambient14_set_pwtime ( ctx, AMBIENT14_PWTIME_DEFAULT );

    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_PCFG0, AMBIENT14_PCFG0_PGAIN1_4X | 
                                                                  AMBIENT14_PCFG0_PPULSE_DEFAULT );
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_PCFG1, AMBIENT14_PCFG1_PPULSE_LENH_DEFAULT | 
                                                                  AMBIENT14_PCFG1_RESERVED | 
                                                                  AMBIENT14_PCFG1_PLDRIVE_10_MA );
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_PCFG2, AMBIENT14_PCFG2_PPULSE_LENL_DEFAULT ); 
    
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_CFG1, AMBIENT14_CFG1_PGAIN2_10X | 
                                                                 AMBIENT14_CFG1_AGAIN_16X );
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_CFG8, AMBIENT14_CFG8_RESERVED );
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_CFG6, AMBIENT14_CFG6_APC_ENABLE | 
                                                                 AMBIENT14_CFG6_RESERVED );

    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_STATUS, AMBIENT14_STATUS_CLEAR_ALL );
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_INTENAB, AMBIENT14_INTENAB_CIEN );
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_CALIBCFG, AMBIENT14_CALIBCFG_BINSRCH_TARGET_15 | 
                                                                     AMBIENT14_CALIBCFG_RESERVED | 
                                                                     AMBIENT14_CALIBCFG_AUTO_OFFSET_ADJ | 
                                                                     AMBIENT14_CALIBCFG_PROX_AVG_16 );
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_CALIB, AMBIENT14_CALIB_START_OFFSET_CAL );
    uint8_t status = 0;
    while ( AMBIENT14_CALIBSTAT_CALIB_FINISHED != ( status & AMBIENT14_CALIBSTAT_CALIB_FINISHED ) )
    {
        error_flag |= ambient14_read_reg ( ctx, AMBIENT14_REG_CALIBSTAT, &status );
        Delay_100ms ( );
    }
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_INTENAB, AMBIENT14_INTENAB_PIEN | 
                                                                    AMBIENT14_INTENAB_AIEN );
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_STATUS, AMBIENT14_STATUS_CLEAR_ALL );
    error_flag |= ambient14_write_reg ( ctx, AMBIENT14_REG_ENABLE, AMBIENT14_ENABLE_PWEN | 
                                                                   AMBIENT14_ENABLE_PEN | 
                                                                   AMBIENT14_ENABLE_AEN | 
                                                                   AMBIENT14_ENABLE_PON );
    Delay_100ms ( );
    return error_flag;
}

err_t ambient14_write_regs ( ambient14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t ambient14_read_regs ( ambient14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t ambient14_write_reg ( ambient14_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ambient14_write_regs ( ctx, reg, &data_in, 1 );
}

err_t ambient14_read_reg ( ambient14_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ambient14_read_regs ( ctx, reg, data_out, 1 );
}

void ambient14_enable_device ( ambient14_t *ctx )
{
    digital_out_high ( &ctx->sby );
}

void ambient14_disable_device ( ambient14_t *ctx )
{
    digital_out_low ( &ctx->sby );
}

uint8_t ambient14_get_int_pin ( ambient14_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t ambient14_check_communication ( ambient14_t *ctx )
{
    uint8_t dev_id = 0;
    for ( uint8_t to_cnt = 0; to_cnt < 10; to_cnt++ )
    {
        if ( AMBIENT14_OK == ambient14_read_reg ( ctx, AMBIENT14_REG_ID, &dev_id ) )
        {
            if ( AMBIENT14_DEVICE_ID == dev_id )
            {
                return AMBIENT14_OK;
            }
        }
        Delay_100ms ( );
    }
    return AMBIENT14_ERROR;
}

err_t ambient14_soft_reset ( ambient14_t *ctx )
{
    return ambient14_write_reg ( ctx, AMBIENT14_REG_SOFTRST, AMBIENT14_SOFT_RESET );
}

err_t ambient14_clear_interrupts ( ambient14_t *ctx )
{
    return ambient14_write_reg ( ctx, AMBIENT14_REG_STATUS, AMBIENT14_STATUS_CLEAR_ALL );
}

err_t ambient14_set_atime ( ambient14_t *ctx, float atime_ms )
{
    if ( ( atime_ms > AMBIENT14_ATIME_MAX ) || ( atime_ms < AMBIENT14_ATIME_MIN ) )
    {
        return AMBIENT14_ERROR;
    }
    uint16_t atime = ( atime_ms / AMBIENT14_SINGLE_STEP_MS ) + AMBIENT14_ROUND_TO_INT;
    if ( atime )
    {
        atime--;
    }
    return ambient14_write_reg ( ctx, AMBIENT14_REG_ATIME, ( uint8_t ) ( atime & 0xFF ) );
}

err_t ambient14_set_awtime ( ambient14_t *ctx, float awtime_ms )
{
    if ( ( awtime_ms > AMBIENT14_AWTIME_MAX ) || ( awtime_ms < AMBIENT14_AWTIME_MIN ) )
    {
        return AMBIENT14_ERROR;
    }
    uint16_t awtime = ( awtime_ms / AMBIENT14_SINGLE_STEP_MS ) + AMBIENT14_ROUND_TO_INT;
    if ( awtime )
    {
        awtime--;
    }
    return ambient14_write_reg ( ctx, AMBIENT14_REG_AWTIME, ( uint8_t ) ( awtime & 0xFF ) );
}

err_t ambient14_set_pwtime ( ambient14_t *ctx, float pwtime_ms )
{
    if ( ( pwtime_ms > AMBIENT14_PWTIME_MAX ) || ( pwtime_ms < AMBIENT14_PWTIME_MIN ) )
    {
        return AMBIENT14_ERROR;
    }
    uint16_t pwtime = ( pwtime_ms / AMBIENT14_SINGLE_STEP_MS ) + AMBIENT14_ROUND_TO_INT;
    if ( pwtime )
    {
        pwtime--;
    }
    return ambient14_write_reg ( ctx, AMBIENT14_REG_PWTIME, ( uint8_t ) ( pwtime & 0xFF ) );
}

err_t ambient14_read_proximity ( ambient14_t *ctx, uint16_t *prox_data )
{
    err_t error_flag = AMBIENT14_OK;
    uint8_t status = 0;
    uint8_t data_buf[ 2 ] = { 0 };
    error_flag |= ambient14_read_reg( ctx, AMBIENT14_REG_STATUS, &status );
    if ( ( AMBIENT14_OK == error_flag ) && ( status & AMBIENT14_STATUS_PINT ) )
    {
        error_flag |= ambient14_read_regs( ctx, AMBIENT14_REG_PDATAL, data_buf, 2 );
        *prox_data = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        error_flag |= ambient14_write_reg( ctx, AMBIENT14_REG_STATUS, AMBIENT14_STATUS_PINT );
    }
    return error_flag;
}

err_t ambient14_read_als_ir ( ambient14_t *ctx, uint16_t *als_data, uint16_t *ir_data )
{
    err_t error_flag = AMBIENT14_OK;
    uint8_t status = 0;
    uint8_t data_buf[ 4 ] = { 0 };
    error_flag |= ambient14_read_reg( ctx, AMBIENT14_REG_STATUS, &status );
    if ( ( AMBIENT14_OK == error_flag ) && ( status & AMBIENT14_STATUS_AINT ) )
    {
        error_flag |= ambient14_read_regs( ctx, AMBIENT14_REG_ALSL, data_buf, 4 );
        *als_data = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        *ir_data = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
        error_flag |= ambient14_write_reg( ctx, AMBIENT14_REG_STATUS, AMBIENT14_STATUS_AINT );
    }
    return error_flag;
}

err_t ambient14_get_illuminance ( ambient14_t *ctx, uint16_t als_data, float *illuminance )
{
    err_t error_flag = AMBIENT14_OK;
    uint8_t reg_data = 0;
    uint8_t data_buf[ 4 ] = { 0 };
    error_flag |= ambient14_read_reg( ctx, AMBIENT14_REG_CFG1, &reg_data );
    if ( AMBIENT14_OK == error_flag )
    {
        if ( AMBIENT14_CFG1_AGAIN_16X == ( reg_data & AMBIENT14_CFG1_AGAIN_MASK ) )
        {
            *illuminance = als_data * AMBIENT14_ILLUMINANCE_ATIME_100_GAIN_128 / AMBIENT14_ILLUMINANCE_GAIN_16_TO_128;
        }
        else if ( AMBIENT14_CFG1_AGAIN_128X == ( reg_data & AMBIENT14_CFG1_AGAIN_MASK ) )
        {
            *illuminance = als_data * AMBIENT14_ILLUMINANCE_ATIME_100_GAIN_128;
        }
        else if ( AMBIENT14_CFG1_AGAIN_1024X == ( reg_data & AMBIENT14_CFG1_AGAIN_MASK ) )
        {
            *illuminance = als_data * AMBIENT14_ILLUMINANCE_ATIME_100_GAIN_128 / AMBIENT14_ILLUMINANCE_GAIN_1024_TO_128;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
