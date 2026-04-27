/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file bldcfoc.c
 * @brief BLDC FOC Click Driver.
 */

#include "bldcfoc.h"

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
static uint8_t bldcfoc_calc_crc8 ( uint8_t *data_buf, uint8_t len );

void bldcfoc_cfg_setup ( bldcfoc_cfg_t *cfg ) 
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
    cfg->i2c_address = BLDCFOC_DEVICE_ADDRESS;

    cfg->dev_pwm_freq = BLDCFOC_DEF_FREQ;
}

err_t bldcfoc_init ( bldcfoc_t *ctx, bldcfoc_cfg_t *cfg ) 
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

err_t bldcfoc_default_cfg ( bldcfoc_t *ctx ) 
{
    err_t error_flag = BLDCFOC_OK;
    uint32_t read_data = 0;
    
    error_flag |= bldcfoc_set_duty_cycle ( ctx, 0.0 );
    error_flag |= bldcfoc_pwm_start( ctx );
    bldcfoc_set_direction ( ctx, BLDCFOC_DIR_CW );
    bldcfoc_release_brake ( ctx );

    ctx->crc_en = BLDCFOC_CTRL_CRC_ENABLE;
    error_flag |= bldcfoc_clear_fault ( ctx );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_ISD_CONFIG, BLDCFOC_DEFAULT_ISD_CONFIG );
    error_flag |= bldcfoc_read_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_ISD_CONFIG, &read_data );
    if ( ( BLDCFOC_DEFAULT_ISD_CONFIG != read_data ) || ( BLDCFOC_OK != error_flag ) )
    {
        return BLDCFOC_ERROR;
    }
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_REV_DRIVE_CONFIG, BLDCFOC_DEFAULT_REV_DRIVE_CONFIG );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_MOTOR_STARTUP1, BLDCFOC_DEFAULT_MOTOR_STARTUP1 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_MOTOR_STARTUP2, BLDCFOC_DEFAULT_MOTOR_STARTUP2 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_CLOSED_LOOP1, BLDCFOC_DEFAULT_CLOSED_LOOP1 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_CLOSED_LOOP2, BLDCFOC_DEFAULT_CLOSED_LOOP2 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_CLOSED_LOOP3, BLDCFOC_DEFAULT_CLOSED_LOOP3 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_CLOSED_LOOP4, BLDCFOC_DEFAULT_CLOSED_LOOP4 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_REF_PROFILES1, BLDCFOC_DEFAULT_REF_PROFILES1 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_REF_PROFILES2, BLDCFOC_DEFAULT_REF_PROFILES2 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_REF_PROFILES3, BLDCFOC_DEFAULT_REF_PROFILES3 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_REF_PROFILES4, BLDCFOC_DEFAULT_REF_PROFILES4 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_REF_PROFILES5, BLDCFOC_DEFAULT_REF_PROFILES5 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_ALG_CFG_REF_PROFILES6, BLDCFOC_DEFAULT_REF_PROFILES6 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_FAULT_CFG_FAULT_CONFIG1, BLDCFOC_DEFAULT_FAULT_CONFIG1 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_FAULT_CFG_FAULT_CONFIG2, BLDCFOC_DEFAULT_FAULT_CONFIG2 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_HW_CFG_PIN_CONFIG, BLDCFOC_DEFAULT_PIN_CONFIG );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_HW_CFG_DEVICE_CONFIG1, BLDCFOC_DEFAULT_DEVICE_CONFIG1 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_HW_CFG_DEVICE_CONFIG2, BLDCFOC_DEFAULT_DEVICE_CONFIG2 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_HW_CFG_PERI_CONFIG1, BLDCFOC_DEFAULT_PERI_CONFIG1 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_HW_CFG_GD_CONFIG1, BLDCFOC_DEFAULT_GD_CONFIG1 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_HW_CFG_GD_CONFIG2, BLDCFOC_DEFAULT_GD_CONFIG2 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_INT_ALG_CFG_INT_ALGO_1, BLDCFOC_DEFAULT_INT_ALGO_1 );
    error_flag |= bldcfoc_write_reg_32 ( ctx, BLDCFOC_EREG_INT_ALG_CFG_INT_ALGO_2, BLDCFOC_DEFAULT_INT_ALGO_2 );
    Delay_1sec ( );
    return error_flag;
}

err_t bldcfoc_write_reg_16 ( bldcfoc_t *ctx, uint32_t mem_addr, uint16_t data_in ) 
{
    err_t error_flag = BLDCFOC_OK;
    uint8_t data_buf[ 7 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = ( ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) << 6 ) | 
                    ( BLDCFOC_CTRL_DLEN_16_BIT << 4 ) | 
                    ( ( uint8_t ) ( ( mem_addr >> 16 ) & 0x0F ) );
    data_buf[ 2 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( mem_addr & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    if ( BLDCFOC_CTRL_CRC_ENABLE == ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) )
    {
        data_buf[ 6 ] = bldcfoc_calc_crc8 ( data_buf, 6 );
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 6 );
    }
    else
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 5 );
    }
    return error_flag;
}

err_t bldcfoc_write_reg_32 ( bldcfoc_t *ctx, uint32_t mem_addr, uint32_t data_in ) 
{
    err_t error_flag = BLDCFOC_OK;
    uint8_t data_buf[ 9 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = ( ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) << 6 ) | 
                    ( BLDCFOC_CTRL_DLEN_32_BIT << 4 ) | 
                    ( ( uint8_t ) ( ( mem_addr >> 16 ) & 0x0F ) );
    data_buf[ 2 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( mem_addr & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 7 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    if ( BLDCFOC_CTRL_CRC_ENABLE == ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) )
    {
        data_buf[ 8 ] = bldcfoc_calc_crc8 ( data_buf, 8 );
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 8 );
    }
    else
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 7 );
    }
    return error_flag;
}

err_t bldcfoc_write_reg_64 ( bldcfoc_t *ctx, uint32_t mem_addr, uint32_t data_in_msb, uint32_t data_in_lsb ) 
{
    err_t error_flag = BLDCFOC_OK;
    uint8_t data_buf[ 13 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = ( ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) << 6 ) | 
                    ( BLDCFOC_CTRL_DLEN_64_BIT << 4 ) | 
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
    if ( BLDCFOC_CTRL_CRC_ENABLE == ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) )
    {
        data_buf[ 12 ] = bldcfoc_calc_crc8 ( data_buf, 12 );
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 12 );
    }
    else
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 11 );
    }
    return error_flag;
}

err_t bldcfoc_read_reg_16 ( bldcfoc_t *ctx, uint32_t mem_addr, uint16_t *data_out ) 
{
    err_t error_flag = BLDCFOC_OK;
    uint8_t data_buf[ 8 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = BLDCFOC_CTRL_READ_BIT | 
                    ( ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) << 6 ) | 
                    ( BLDCFOC_CTRL_DLEN_16_BIT << 4 ) | 
                    ( ( uint8_t ) ( ( mem_addr >> 16 ) & 0x0F ) );
    data_buf[ 2 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( mem_addr & 0xFF );
    data_buf[ 4 ] = ( ctx->slave_address << 1 ) | BLDCFOC_I2C_READ_BIT;

    if ( BLDCFOC_CTRL_CRC_ENABLE == ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) )
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 3 );
        error_flag |= i2c_master_read( &ctx->i2c, &data_buf[ 5 ], 3 );
        if ( data_buf[ 7 ] != bldcfoc_calc_crc8 ( data_buf, 7 ) )
        {
            error_flag |= BLDCFOC_ERROR;
        }
    }
    else
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 3 );
        error_flag |= i2c_master_read( &ctx->i2c, &data_buf[ 5 ], 2 );
    }

    if ( ( BLDCFOC_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 5 ];
    }
    return error_flag;
}

err_t bldcfoc_read_reg_32 ( bldcfoc_t *ctx, uint32_t mem_addr, uint32_t *data_out ) 
{
    err_t error_flag = BLDCFOC_OK;
    uint8_t data_buf[ 10 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = BLDCFOC_CTRL_READ_BIT | 
                    ( ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) << 6 ) | 
                    ( BLDCFOC_CTRL_DLEN_32_BIT << 4 ) | 
                    ( ( uint8_t ) ( ( mem_addr >> 16 ) & 0x0F ) );
    data_buf[ 2 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( mem_addr & 0xFF );
    data_buf[ 4 ] = ( ctx->slave_address << 1 ) | BLDCFOC_I2C_READ_BIT;

    if ( BLDCFOC_CTRL_CRC_ENABLE == ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) )
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 3 );
        error_flag |= i2c_master_read( &ctx->i2c, &data_buf[ 5 ], 5 );
        if ( data_buf[ 9 ] != bldcfoc_calc_crc8 ( data_buf, 9 ) )
        {
            error_flag |= BLDCFOC_ERROR;
        }
    }
    else
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 3 );
        error_flag |= i2c_master_read( &ctx->i2c, &data_buf[ 5 ], 4 );
    }

    if ( ( BLDCFOC_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint32_t ) data_buf[ 8 ] << 24 ) | ( ( uint32_t ) data_buf[ 7 ] << 16 ) | 
                    ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 5 ];
    }
    return error_flag;
}

err_t bldcfoc_read_reg_64 ( bldcfoc_t *ctx, uint32_t mem_addr, uint32_t *data_out_msb, uint32_t *data_out_lsb ) 
{
    err_t error_flag = BLDCFOC_OK;
    uint8_t data_buf[ 14 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = BLDCFOC_CTRL_READ_BIT | 
                    ( ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) << 6 ) | 
                    ( BLDCFOC_CTRL_DLEN_64_BIT << 4 ) | 
                    ( ( uint8_t ) ( ( mem_addr >> 16 ) & 0x0F ) );
    data_buf[ 2 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( mem_addr & 0xFF );
    data_buf[ 4 ] = ( ctx->slave_address << 1 ) | BLDCFOC_I2C_READ_BIT;

    if ( BLDCFOC_CTRL_CRC_ENABLE == ( ctx->crc_en & BLDCFOC_CTRL_CRC_MASK ) )
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 3 );
        error_flag |= i2c_master_read( &ctx->i2c, &data_buf[ 5 ], 9 );
        if ( data_buf[ 13 ] != bldcfoc_calc_crc8 ( data_buf, 13 ) )
        {
            error_flag |= BLDCFOC_ERROR;
        }
    }
    else
    {
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 3 );
        error_flag |= i2c_master_read( &ctx->i2c, &data_buf[ 5 ], 8 );
    }

    if ( ( BLDCFOC_OK == error_flag ) && ( NULL != data_out_msb ) && ( NULL != data_out_lsb ) )
    {
        *data_out_msb = ( ( uint32_t ) data_buf[ 12 ] << 24 ) | ( ( uint32_t ) data_buf[ 11 ] << 16 ) | 
                        ( ( uint16_t ) data_buf[ 10 ] << 8 ) | data_buf[ 9 ];
        *data_out_lsb = ( ( uint32_t ) data_buf[ 8 ] << 24 ) | ( ( uint32_t ) data_buf[ 7 ] << 16 ) | 
                        ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 5 ];
    }
    return error_flag;
}

err_t bldcfoc_set_duty_cycle ( bldcfoc_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t bldcfoc_pwm_stop ( bldcfoc_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t bldcfoc_pwm_start ( bldcfoc_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void bldcfoc_set_direction ( bldcfoc_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void bldcfoc_switch_direction ( bldcfoc_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void bldcfoc_pull_brake ( bldcfoc_t *ctx )
{
    digital_out_high ( &ctx->brake );
}

void bldcfoc_release_brake ( bldcfoc_t *ctx )
{
    digital_out_low ( &ctx->brake );
}

uint8_t bldcfoc_get_fault_pin ( bldcfoc_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

err_t bldcfoc_read_fault ( bldcfoc_t *ctx, uint32_t *gate_drv_flt, uint32_t *controller_flt )
{
    return bldcfoc_read_reg_64 ( ctx, BLDCFOC_RREG_FAULT_STATUS_GATE_DRIVER, gate_drv_flt, controller_flt );
}

err_t bldcfoc_clear_fault ( bldcfoc_t *ctx )
{
    return bldcfoc_write_reg_32 ( ctx, BLDCFOC_RREG_DEV_CTRL, BLDCFOC_DEV_CTRL_CLR_FLT | 
                                                              BLDCFOC_DEV_CTRL_CLR_FLT_RETRY_CNT );
}

static uint8_t bldcfoc_calc_crc8 ( uint8_t *data_buf, uint8_t len )
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
