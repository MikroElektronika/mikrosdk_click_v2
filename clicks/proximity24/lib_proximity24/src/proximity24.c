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
 * @file proximity24.c
 * @brief Proximity 24 Click Driver.
 */

#include "proximity24.h"

void proximity24_cfg_setup ( proximity24_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY24_DEVICE_ADDRESS;
}

err_t proximity24_init ( proximity24_t *ctx, proximity24_cfg_t *cfg ) 
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

err_t proximity24_default_cfg ( proximity24_t *ctx ) 
{
    err_t error_flag = PROXIMITY24_OK;
    if ( PROXIMITY24_ERROR == proximity24_check_com ( ctx ) )
    {
        return PROXIMITY24_ERROR;
    }
    error_flag |= proximity24_write_reg ( ctx, PROXIMITY24_REG_ALS_CONF12, PROXIMITY24_ALS_CONF2_ALS_NS_X1 |
                                                                           PROXIMITY24_ALS_CONF2_WHITE_SD_POWER_ON | 
                                                                           PROXIMITY24_ALS_CONF1_ALS_IT_100MS | 
                                                                           PROXIMITY24_ALS_CONF1_ALS_HD_X1 | 
                                                                           PROXIMITY24_ALS_CONF1_ALS_PERS_4 | 
                                                                           PROXIMITY24_ALS_CONF1_ALS_INT_DIS | 
                                                                           PROXIMITY24_ALS_CONF1_ALS_SD_POWER_ON );
    error_flag |= proximity24_write_reg ( ctx, PROXIMITY24_REG_PS_CONF12, PROXIMITY24_PS_CONF2_PS_GAIN_TWO_STEP | 
                                                                          PROXIMITY24_PS_CONF2_PS_HD_12BITS | 
                                                                          PROXIMITY24_PS_CONF2_PS_NS_TWO_STEP_X1 |
                                                                          PROXIMITY24_PS_CONF2_PS_INT_DIS | 
                                                                          PROXIMITY24_PS_CONF1_PS_DUTY_1_OF_40 | 
                                                                          PROXIMITY24_PS_CONF1_PS_PERS_4 | 
                                                                          PROXIMITY24_PS_CONF1_PS_IT_8T | 
                                                                          PROXIMITY24_PS_CONF1_PS_SD_POWER_ON );
    error_flag |= proximity24_write_reg ( ctx, PROXIMITY24_REG_PS_CONF3_MS, PROXIMITY24_PS_MS_PS_SC_CUR_1X | 
                                                                            PROXIMITY24_PS_MS_PS_SP_1X_CAP | 
                                                                            PROXIMITY24_PS_MS_PS_SPO_00H | 
                                                                            PROXIMITY24_PS_MS_LED_I_100MA | 
                                                                            PROXIMITY24_PS_CONF3_LED_I_LOW_DIS | 
                                                                            PROXIMITY24_PS_CONF3_PS_SMART_PERS_DIS | 
                                                                            PROXIMITY24_PS_CONF3_PS_AF_DIS | 
                                                                            PROXIMITY24_PS_CONF3_PS_TRIG_NO_TRIG | 
                                                                            PROXIMITY24_PS_CONF3_PS_MS_NORMAL | 
                                                                            PROXIMITY24_PS_CONF3_PS_SC_EN_TURN_OFF );

    error_flag |= proximity24_set_als_int_time ( ctx, PROXIMITY24_ALS_IT_100MS );
    return error_flag;
}

err_t proximity24_write_reg ( proximity24_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t proximity24_read_reg ( proximity24_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = PROXIMITY24_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    if ( ( PROXIMITY24_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return error_flag;
}

err_t proximity24_check_com ( proximity24_t *ctx )
{
    err_t error_flag = PROXIMITY24_OK;
    uint16_t device_id = 0;
    error_flag = proximity24_read_reg( ctx, PROXIMITY24_REG_ID, &device_id );
    if ( ( PROXIMITY24_OK == error_flag ) && 
         ( PROXIMITY24_DEVICE_ID != ( device_id & PROXIMITY24_DEVICE_ID_MASK ) ) )
    {
        error_flag = PROXIMITY24_ERROR;
    }
    return error_flag;
}

uint8_t proximity24_get_int_pin ( proximity24_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t proximity24_set_als_int_time ( proximity24_t *ctx, uint8_t als_it )
{
    err_t error_flag = PROXIMITY24_OK;
    uint16_t als_conf12 = 0;
    if ( als_it > PROXIMITY24_ALS_IT_800MS )
    {
        error_flag = PROXIMITY24_ERROR;
    }
    if ( PROXIMITY24_OK == error_flag )
    {
        error_flag = proximity24_read_reg ( ctx, PROXIMITY24_REG_ALS_CONF12, &als_conf12 );
    }
    if ( PROXIMITY24_OK == error_flag )
    {
        als_conf12 &= ( ~PROXIMITY24_ALS_CONF1_ALS_IT_MASK );
        als_conf12 |= ( ( als_it << 5 ) & PROXIMITY24_ALS_CONF1_ALS_IT_MASK );
        error_flag = proximity24_write_reg ( ctx, PROXIMITY24_REG_ALS_CONF12, als_conf12 );
    }
    if ( PROXIMITY24_OK == error_flag )
    {
        ctx->als_sens = PROXIMITY24_ALS_SENS / ( 1 << als_it );
    }
    return error_flag;
}

err_t proximity24_read_proximity ( proximity24_t *ctx, uint16_t *ps_data )
{
    return proximity24_read_reg ( ctx, PROXIMITY24_REG_PS_DATA, ps_data );
}

err_t proximity24_read_als_data ( proximity24_t *ctx, uint16_t *als_data )
{
    return proximity24_read_reg ( ctx, PROXIMITY24_REG_ALS_DATA, als_data );
}

err_t proximity24_read_white_data ( proximity24_t *ctx, uint16_t *white_data )
{
    return proximity24_read_reg ( ctx, PROXIMITY24_REG_WHITE_DATA, white_data );
}

// ------------------------------------------------------------------------- END
