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
 * @file brushless33.c
 * @brief Brushless 33 Click Driver.
 */

#include "brushless33.h"

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x07 (x8 + x2 + x + 1 )
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t brushless33_calc_crc8 ( uint8_t *data_buf, uint8_t len );

void brushless33_cfg_setup ( brushless33_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->speed = HAL_PIN_NC;

    // Additional gpio pins
    cfg->brake = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BRUSHLESS33_DEVICE_ADDRESS;
    cfg->dev_pwm_freq = BRUSHLESS33_DEF_FREQ;
}

err_t brushless33_init ( brushless33_t *ctx, brushless33_cfg_t *cfg ) 
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

    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->speed;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    digital_out_init( &ctx->brake, cfg->brake );
    digital_out_init( &ctx->dir, cfg->dir );

    digital_in_init( &ctx->fault, cfg->fault );

    return I2C_MASTER_SUCCESS;
}

err_t brushless33_default_cfg ( brushless33_t *ctx ) 
{
    err_t error_flag = BRUSHLESS33_OK;
    uint32_t read_data = 0;
    
    error_flag |= brushless33_set_duty_cycle ( ctx, 0.0 );
    error_flag |= brushless33_pwm_start( ctx );
    brushless33_set_direction ( ctx, BRUSHLESS33_DIR_CW );
    brushless33_release_brake ( ctx );

    ctx->crc_en = BRUSHLESS33_CTRL_CRC_ENABLE;
    error_flag |= brushless33_clear_fault ( ctx );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_ISD_CONFIG, BRUSHLESS33_DEFAULT_ISD_CONFIG );
    error_flag |= brushless33_read_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_ISD_CONFIG, &read_data );
    if ( ( BRUSHLESS33_DEFAULT_ISD_CONFIG != read_data ) || ( BRUSHLESS33_OK != error_flag ) )
    {
        return BRUSHLESS33_ERROR;
    }
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_REV_DRIVE_CONFIG, BRUSHLESS33_DEFAULT_REV_DRIVE_CONFIG );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_MOTOR_STARTUP1, BRUSHLESS33_DEFAULT_MOTOR_STARTUP1 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_MOTOR_STARTUP2, BRUSHLESS33_DEFAULT_MOTOR_STARTUP2 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_CLOSED_LOOP1, BRUSHLESS33_DEFAULT_CLOSED_LOOP1 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_CLOSED_LOOP2, BRUSHLESS33_DEFAULT_CLOSED_LOOP2 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_CLOSED_LOOP3, BRUSHLESS33_DEFAULT_CLOSED_LOOP3 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_CLOSED_LOOP4, BRUSHLESS33_DEFAULT_CLOSED_LOOP4 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES1, BRUSHLESS33_DEFAULT_SPEED_PROFILES1 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES2, BRUSHLESS33_DEFAULT_SPEED_PROFILES2 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES3, BRUSHLESS33_DEFAULT_SPEED_PROFILES3 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES4, BRUSHLESS33_DEFAULT_SPEED_PROFILES4 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES5, BRUSHLESS33_DEFAULT_SPEED_PROFILES5 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES6, BRUSHLESS33_DEFAULT_SPEED_PROFILES6 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_FAULT_CFG_FAULT_CONFIG1, BRUSHLESS33_DEFAULT_FAULT_CONFIG1 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_FAULT_CFG_FAULT_CONFIG2, BRUSHLESS33_DEFAULT_FAULT_CONFIG2 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_HW_CFG_PIN_CONFIG, BRUSHLESS33_DEFAULT_PIN_CONFIG );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_HW_CFG_DEVICE_CONFIG1, BRUSHLESS33_DEFAULT_DEVICE_CONFIG1 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_HW_CFG_DEVICE_CONFIG2, BRUSHLESS33_DEFAULT_DEVICE_CONFIG2 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_HW_CFG_PERI_CONFIG1, BRUSHLESS33_DEFAULT_PERI_CONFIG1 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_HW_CFG_GD_CONFIG1, BRUSHLESS33_DEFAULT_GD_CONFIG1 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_HW_CFG_GD_CONFIG2, BRUSHLESS33_DEFAULT_GD_CONFIG2 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_INT_ALG_CFG_INT_ALGO_1, BRUSHLESS33_DEFAULT_INT_ALGO_1 );
    error_flag |= brushless33_write_reg_32 ( ctx, BRUSHLESS33_EREG_INT_ALG_CFG_INT_ALGO_2, BRUSHLESS33_DEFAULT_INT_ALGO_2 );
    Delay_1sec ( );
    return error_flag;
}

err_t brushless33_write_reg_16 ( brushless33_t *ctx, uint32_t mem_addr, uint16_t data_in ) 
{
    err_t error_flag = BRUSHLESS33_OK;
    uint8_t data_buf[ 7 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = ( ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) << 6 ) | 
                    ( BRUSHLESS33_CTRL_DLEN_16_BIT << 4 ) | 
                    ( ( uint8_t ) ( ( mem_addr >> 16 ) & 0x0F ) );
    data_buf[ 2 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( mem_addr & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    if ( BRUSHLESS33_CTRL_CRC_ENABLE == ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) )
    {
        data_buf[ 6 ] = brushless33_calc_crc8 ( data_buf, 6 );
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 6 );
    }
    else
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 5 );
    }
    return error_flag;
}

err_t brushless33_write_reg_32 ( brushless33_t *ctx, uint32_t mem_addr, uint32_t data_in ) 
{
    err_t error_flag = BRUSHLESS33_OK;
    uint8_t data_buf[ 9 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = ( ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) << 6 ) | 
                    ( BRUSHLESS33_CTRL_DLEN_32_BIT << 4 ) | 
                    ( ( uint8_t ) ( ( mem_addr >> 16 ) & 0x0F ) );
    data_buf[ 2 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( mem_addr & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 7 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    if ( BRUSHLESS33_CTRL_CRC_ENABLE == ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) )
    {
        data_buf[ 8 ] = brushless33_calc_crc8 ( data_buf, 8 );
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 8 );
    }
    else
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 7 );
    }
    return error_flag;
}

err_t brushless33_write_reg_64 ( brushless33_t *ctx, uint32_t mem_addr, uint32_t data_in_msb, uint32_t data_in_lsb ) 
{
    err_t error_flag = BRUSHLESS33_OK;
    uint8_t data_buf[ 13 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = ( ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) << 6 ) | 
                    ( BRUSHLESS33_CTRL_DLEN_64_BIT << 4 ) | 
                    ( ( uint8_t ) ( ( mem_addr >> 16 ) & 0x0F ) );
    data_buf[ 2 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( mem_addr & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( data_in_lsb & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( data_in_lsb >> 8 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( ( data_in_lsb >> 16 ) & 0xFF );
    data_buf[ 7 ] = ( uint8_t ) ( ( data_in_lsb >> 24 ) & 0xFF );
    data_buf[ 8 ] = ( uint8_t ) ( data_in_msb & 0xFF );
    data_buf[ 9 ] = ( uint8_t ) ( ( data_in_msb >> 8 ) & 0xFF );
    data_buf[ 10 ] = ( uint8_t ) ( ( data_in_msb >> 16 ) & 0xFF );
    data_buf[ 11 ] = ( uint8_t ) ( ( data_in_msb >> 24 ) & 0xFF );
    if ( BRUSHLESS33_CTRL_CRC_ENABLE == ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) )
    {
        data_buf[ 12 ] = brushless33_calc_crc8 ( data_buf, 12 );
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 12 );
    }
    else
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 11 );
    }
    return error_flag;
}

err_t brushless33_read_reg_16 ( brushless33_t *ctx, uint32_t mem_addr, uint16_t *data_out ) 
{
    err_t error_flag = BRUSHLESS33_OK;
    uint8_t data_buf[ 8 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = BRUSHLESS33_CTRL_READ_BIT | 
                    ( ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) << 6 ) | 
                    ( BRUSHLESS33_CTRL_DLEN_16_BIT << 4 ) | 
                    ( ( uint8_t ) ( ( mem_addr >> 16 ) & 0x0F ) );
    data_buf[ 2 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( mem_addr & 0xFF );
    data_buf[ 4 ] = ( ctx->slave_address << 1 ) | BRUSHLESS33_I2C_READ_BIT;

    if ( BRUSHLESS33_CTRL_CRC_ENABLE == ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) )
    {
        error_flag |= i2c_master_write_then_read( &ctx->i2c, &data_buf[ 1 ], 3, &data_buf[ 5 ], 3 );
        if ( data_buf[ 7 ] != brushless33_calc_crc8 ( data_buf, 7 ) )
        {
            error_flag |= BRUSHLESS33_ERROR;
        }
    }
    else
    {
        error_flag |= i2c_master_write_then_read( &ctx->i2c, &data_buf[ 1 ], 3, &data_buf[ 5 ], 2 );
    }

    if ( ( BRUSHLESS33_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 5 ];
    }
    return error_flag;
}

err_t brushless33_read_reg_32 ( brushless33_t *ctx, uint32_t mem_addr, uint32_t *data_out ) 
{
    err_t error_flag = BRUSHLESS33_OK;
    uint8_t data_buf[ 10 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = BRUSHLESS33_CTRL_READ_BIT | 
                    ( ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) << 6 ) | 
                    ( BRUSHLESS33_CTRL_DLEN_32_BIT << 4 ) | 
                    ( ( uint8_t ) ( ( mem_addr >> 16 ) & 0x0F ) );
    data_buf[ 2 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( mem_addr & 0xFF );
    data_buf[ 4 ] = ( ctx->slave_address << 1 ) | BRUSHLESS33_I2C_READ_BIT;

    if ( BRUSHLESS33_CTRL_CRC_ENABLE == ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) )
    {
        error_flag |= i2c_master_write_then_read( &ctx->i2c, &data_buf[ 1 ], 3, &data_buf[ 5 ], 5 );
        if ( data_buf[ 9 ] != brushless33_calc_crc8 ( data_buf, 9 ) )
        {
            error_flag |= BRUSHLESS33_ERROR;
        }
    }
    else
    {
        error_flag |= i2c_master_write_then_read( &ctx->i2c, &data_buf[ 1 ], 3, &data_buf[ 5 ], 4 );
    }

    if ( ( BRUSHLESS33_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint32_t ) data_buf[ 8 ] << 24 ) | ( ( uint32_t ) data_buf[ 7 ] << 16 ) | 
                    ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 5 ];
    }
    return error_flag;
}

err_t brushless33_read_reg_64 ( brushless33_t *ctx, uint32_t mem_addr, uint32_t *data_out_msb, uint32_t *data_out_lsb ) 
{
    err_t error_flag = BRUSHLESS33_OK;
    uint8_t data_buf[ 14 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = BRUSHLESS33_CTRL_READ_BIT | 
                    ( ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) << 6 ) | 
                    ( BRUSHLESS33_CTRL_DLEN_64_BIT << 4 ) | 
                    ( ( uint8_t ) ( ( mem_addr >> 16 ) & 0x0F ) );
    data_buf[ 2 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( mem_addr & 0xFF );
    data_buf[ 4 ] = ( ctx->slave_address << 1 ) | BRUSHLESS33_I2C_READ_BIT;

    if ( BRUSHLESS33_CTRL_CRC_ENABLE == ( ctx->crc_en & BRUSHLESS33_CTRL_CRC_MASK ) )
    {
        error_flag |= i2c_master_write_then_read( &ctx->i2c, &data_buf[ 1 ], 3, &data_buf[ 5 ], 9 );
        if ( data_buf[ 13 ] != brushless33_calc_crc8 ( data_buf, 13 ) )
        {
            error_flag |= BRUSHLESS33_ERROR;
        }
    }
    else
    {
        error_flag |= i2c_master_write_then_read( &ctx->i2c, &data_buf[ 1 ], 3, &data_buf[ 5 ], 8 );
    }

    if ( ( BRUSHLESS33_OK == error_flag ) && ( NULL != data_out_msb ) && ( NULL != data_out_lsb ) )
    {
        *data_out_msb = ( ( uint32_t ) data_buf[ 12 ] << 24 ) | ( ( uint32_t ) data_buf[ 11 ] << 16 ) | 
                        ( ( uint16_t ) data_buf[ 10 ] << 8 ) | data_buf[ 9 ];
        *data_out_lsb = ( ( uint32_t ) data_buf[ 8 ] << 24 ) | ( ( uint32_t ) data_buf[ 7 ] << 16 ) | 
                        ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 5 ];
    }
    return error_flag;
}

err_t brushless33_set_duty_cycle ( brushless33_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless33_pwm_stop ( brushless33_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless33_pwm_start ( brushless33_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void brushless33_set_direction ( brushless33_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void brushless33_switch_direction ( brushless33_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void brushless33_pull_brake ( brushless33_t *ctx )
{
    digital_out_high ( &ctx->brake );
}

void brushless33_release_brake ( brushless33_t *ctx )
{
    digital_out_low ( &ctx->brake );
}

uint8_t brushless33_get_fault_pin ( brushless33_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

err_t brushless33_read_fault ( brushless33_t *ctx, uint32_t *gate_drv_flt, uint32_t *controller_flt )
{
    return brushless33_read_reg_64 ( ctx, BRUSHLESS33_RREG_FAULT_STATUS_GATE_DRIVER, gate_drv_flt, controller_flt );
}

err_t brushless33_clear_fault ( brushless33_t *ctx )
{
    return brushless33_write_reg_32 ( ctx, BRUSHLESS33_RREG_DEV_CTRL, BRUSHLESS33_DEV_CTRL_CLR_FLT | 
                                                                      BRUSHLESS33_DEV_CTRL_CLR_FLT_RETRY_CNT );
}

static uint8_t brushless33_calc_crc8 ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0xFF;
    uint8_t cnt_0 = 0;
    uint8_t cnt_1 = 0;
    
    for ( cnt_0 = 0; cnt_0 < len; cnt_0++ ) 
    {
        crc ^= data_buf[ cnt_0 ];
        for ( cnt_1 = 0; cnt_1 < 8; cnt_1++ ) 
        {
            if ( crc & 0x80 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ 0x07 );
            }
            else 
            {
                crc <<= 1;
            }
        }
    }
    
    return crc;
}

// ------------------------------------------------------------------------- END
