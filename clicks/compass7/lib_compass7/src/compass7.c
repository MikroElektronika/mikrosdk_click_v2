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
 * @file compass7.c
 * @brief Compass 7 Click Driver.
 */

#include "compass7.h"

void compass7_cfg_setup ( compass7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = COMPASS7_DEVICE_ADDRESS;
}

err_t compass7_init ( compass7_t *ctx, compass7_cfg_t *cfg ) 
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

err_t compass7_default_cfg ( compass7_t *ctx ) 
{
    err_t error_flag = COMPASS7_OK;
    if ( COMPASS7_ERROR == compass7_check_communication ( ctx ) )
    {
        return COMPASS7_ERROR;
    }
    error_flag |= compass7_soft_reset ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t compass7_generic_write ( compass7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t compass7_generic_read ( compass7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t compass7_write_register ( compass7_t *ctx, uint8_t reg, uint8_t data_in )
{
    return compass7_generic_write( ctx, reg, &data_in, 1 );
}

err_t compass7_read_register ( compass7_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return compass7_generic_read( ctx, reg, data_out, 1 );
}

err_t compass7_check_communication ( compass7_t *ctx )
{
    uint8_t product_id;
    if ( COMPASS7_OK == compass7_read_register ( ctx, COMPASS7_REG_PRODUCT_ID, &product_id ) )
    {
        if ( COMPASS7_PRODUCT_ID == product_id )
        {
            return COMPASS7_OK;
        }
    }
    return COMPASS7_ERROR;
}

err_t compass7_soft_reset ( compass7_t *ctx )
{
    return compass7_write_register ( ctx, COMPASS7_REG_CONTROL1, COMPASS7_CONTROL1_SW_RESET );
}

err_t compass7_set_measurement_mode ( compass7_t *ctx, uint8_t mode )
{
    err_t error_flag = COMPASS7_OK;
    if ( mode > COMPASS7_MEAS_CONTINUOUS_M_100HZ )
    {
        return COMPASS7_ERROR;
    }
    if ( ( COMPASS7_MEAS_SINGLE_T == mode ) || ( COMPASS7_MEAS_SINGLE_M == mode ) )
    {
        error_flag |= compass7_write_register ( ctx, COMPASS7_REG_ODR, COMPASS7_ODR_DISABLE );
        error_flag |= compass7_write_register ( ctx, COMPASS7_REG_CONTROL2, COMPASS7_CONTROL2_EN_PRD_SET | 
                                                                            COMPASS7_CONTROL2_PRD_SET_1_SMPL );
        if ( COMPASS7_MEAS_SINGLE_T == mode )
        {
            error_flag |= compass7_write_register ( ctx, COMPASS7_REG_CONTROL0, COMPASS7_CONTROL0_AUTO_SR_EN | 
                                                                                COMPASS7_CONTROL0_TAKE_MEAS_T );
        }
        else
        {
            error_flag |= compass7_write_register ( ctx, COMPASS7_REG_CONTROL0, COMPASS7_CONTROL0_AUTO_SR_EN | 
                                                                                COMPASS7_CONTROL0_TAKE_MEAS_M );
        }
    }
    else
    {
        switch ( mode )
        {
            case COMPASS7_MEAS_CONTINUOUS_M_1HZ:
            {
                error_flag |= compass7_write_register ( ctx, COMPASS7_REG_ODR, COMPASS7_ODR_1HZ );
                break;
            }
            case COMPASS7_MEAS_CONTINUOUS_M_2HZ:
            {
                error_flag |= compass7_write_register ( ctx, COMPASS7_REG_ODR, COMPASS7_ODR_2HZ );
                break;
            }
            case COMPASS7_MEAS_CONTINUOUS_M_5HZ:
            {
                error_flag |= compass7_write_register ( ctx, COMPASS7_REG_ODR, COMPASS7_ODR_5HZ );
                break;
            }
            case COMPASS7_MEAS_CONTINUOUS_M_10HZ:
            {
                error_flag |= compass7_write_register ( ctx, COMPASS7_REG_ODR, COMPASS7_ODR_10HZ );
                break;
            }
            case COMPASS7_MEAS_CONTINUOUS_M_25HZ:
            {
                error_flag |= compass7_write_register ( ctx, COMPASS7_REG_ODR, COMPASS7_ODR_25HZ );
                break;
            }
            case COMPASS7_MEAS_CONTINUOUS_M_50HZ:
            {
                error_flag |= compass7_write_register ( ctx, COMPASS7_REG_ODR, COMPASS7_ODR_50HZ );
                break;
            }
            case COMPASS7_MEAS_CONTINUOUS_M_100HZ:
            {
                error_flag |= compass7_write_register ( ctx, COMPASS7_REG_ODR, COMPASS7_ODR_100HZ );
                break;
            }
        }
        error_flag |= compass7_write_register ( ctx, COMPASS7_REG_CONTROL0, COMPASS7_CONTROL0_CMM_FREQ_EN | 
                                                                            COMPASS7_CONTROL0_AUTO_SR_EN );
        error_flag |= compass7_write_register ( ctx, COMPASS7_REG_CONTROL2, COMPASS7_CONTROL2_CMM_EN | 
                                                                            COMPASS7_CONTROL2_EN_PRD_SET | 
                                                                            COMPASS7_CONTROL2_PRD_SET_1_SMPL );
    }
    return error_flag;
}

err_t compass7_get_magnetic_flux ( compass7_t *ctx, compass7_magnetic_flux_t *flux )
{
    uint8_t data_buf[ 9 ] = { 0 };
    uint16_t timeout_cnt = 0;
    do 
    {
        Delay_1ms ( );
        if ( ( COMPASS7_ERROR == compass7_read_register ( ctx, COMPASS7_REG_STATUS1, data_buf ) ) || 
             ( timeout_cnt++ > COMPASS7_TIMEOUT ) )
        {
            return COMPASS7_ERROR;
        }
    } while ( COMPASS7_STATUS1_MEAS_M_DONE != ( data_buf[ 0 ] & COMPASS7_STATUS1_MEAS_M_DONE ) );
    if ( COMPASS7_OK == compass7_generic_read ( ctx, COMPASS7_REG_XOUT0, data_buf, 9 ) )
    {
        int32_t raw_data;
        raw_data = ( ( int32_t ) data_buf[ 0 ] << 12 ) | 
                   ( ( int32_t ) data_buf[ 1 ] << 4 ) | 
                   ( ( int32_t ) data_buf[ 6 ] >> 4 );
        flux->x_axis = ( raw_data - COMPASS7_MAGNETIC_OFFSET ) * 
                        COMPASS7_MAGNETIC_RESOLUTION * COMPASS7_MILLIGAUSS_TO_GAUSS;
        raw_data = ( ( int32_t ) data_buf[ 2 ] << 12 ) | 
                   ( ( int32_t ) data_buf[ 3 ] << 4 ) | 
                   ( ( int32_t ) data_buf[ 7 ] >> 4 );
        flux->y_axis = ( raw_data - COMPASS7_MAGNETIC_OFFSET ) * 
                        COMPASS7_MAGNETIC_RESOLUTION * COMPASS7_MILLIGAUSS_TO_GAUSS;
        raw_data = ( ( int32_t ) data_buf[ 4 ] << 12 ) | 
                   ( ( int32_t ) data_buf[ 5 ] << 4 ) | 
                   ( ( int32_t ) data_buf[ 8 ] >> 4 );
        flux->z_axis = ( raw_data - COMPASS7_MAGNETIC_OFFSET ) * 
                        COMPASS7_MAGNETIC_RESOLUTION * COMPASS7_MILLIGAUSS_TO_GAUSS;
        return COMPASS7_OK;
    }
    return COMPASS7_ERROR;
}

err_t compass7_get_temperature ( compass7_t *ctx, float *temperature )
{
    uint8_t reg_data;
    uint16_t timeout_cnt = 0;
    do 
    {
        Delay_1ms ( );
        if ( ( COMPASS7_ERROR == compass7_read_register ( ctx, COMPASS7_REG_STATUS1, &reg_data ) ) || 
             ( timeout_cnt++ > COMPASS7_TIMEOUT ) )
        {
            return COMPASS7_ERROR;
        }
    } while ( COMPASS7_STATUS1_MEAS_T_DONE != ( reg_data & COMPASS7_STATUS1_MEAS_T_DONE ) );
    if ( COMPASS7_OK == compass7_read_register ( ctx, COMPASS7_REG_TOUT, &reg_data ) )
    {
        *temperature = reg_data * COMPASS7_TEMPERATURE_RESOLUTION - COMPASS7_TEMPERATURE_OFFSET;
        return COMPASS7_OK;
    }
    return COMPASS7_ERROR;
}

// ------------------------------------------------------------------------- END
