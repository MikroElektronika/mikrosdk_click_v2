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
 * @file brushless28.c
 * @brief Brushless 28 Click Driver.
 */

#include "brushless28.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x2F (x8 + x5 + x3 + x2 + x + 1 )
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t brushless28_calc_crc8 ( uint8_t *data_buf, uint8_t len );

void brushless28_cfg_setup ( brushless28_cfg_t *cfg ) 
{
    cfg->sck   = HAL_PIN_NC;
    cfg->miso  = HAL_PIN_NC;
    cfg->mosi  = HAL_PIN_NC;
    cfg->cs    = HAL_PIN_NC;
    cfg->dir   = HAL_PIN_NC;
    cfg->brake = HAL_PIN_NC;
    cfg->pwm   = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->dev_pwm_freq = BRUSHLESS28_DEF_FREQ;
}

err_t brushless28_init ( brushless28_t *ctx, brushless28_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->pwm;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->brake, cfg->brake );

    digital_in_init( &ctx->fault, cfg->fault );
    
    return BRUSHLESS28_OK;
}

err_t brushless28_default_cfg ( brushless28_t *ctx ) 
{
    err_t error_flag = BRUSHLESS28_OK;

    SET_SPI_DATA_SAMPLE_EDGE;
    ctx->crc_en = BRUSHLESS28_SPI_FRAME_CRC_ENABLE;
    
    error_flag |= brushless28_set_duty_cycle ( ctx, BRUSHLESS28_DEF_DUTY );
    error_flag |= brushless28_pwm_start( ctx );
    brushless28_set_direction ( ctx, BRUSHLESS28_DIR_CW );
    brushless28_release_brake ( ctx );
    Delay_100ms ( );

    uint16_t spi_test = 0;
    error_flag |= brushless28_write_reg ( ctx, BRUSHLESS28_REG_SPI_TEST, BRUSHLESS28_SPI_TEST_WORD );
    error_flag |= brushless28_read_reg ( ctx, BRUSHLESS28_REG_SPI_TEST, &spi_test );
    if ( BRUSHLESS28_SPI_TEST_WORD != spi_test )
    {
        return BRUSHLESS28_ERROR;
    }
    uint16_t reg_data = 0;
    error_flag |= brushless28_write_reg ( ctx, BRUSHLESS28_REG_IC_CTRL2, BRUSHLESS28_IC_CTRL2_ENABLE_DRV | 
                                                                         BRUSHLESS28_IC_CTRL2_LOCK_UNLOCK | 
                                                                         BRUSHLESS28_IC_CTRL2_CLR_FLT );
    error_flag |= brushless28_write_reg ( ctx, BRUSHLESS28_REG_GD_CTRL1, BRUSHLESS28_GD_CTRL1_PWM_MODE_1X_PWM | 
                                                                         BRUSHLESS28_GD_CTRL1_SGD_TMP_EN | 
                                                                         BRUSHLESS28_GD_CTRL1_DEADT_2000NS );
    Delay_1sec ( );
    return error_flag;
}

err_t brushless28_write_reg ( brushless28_t *ctx, uint8_t reg, uint16_t data_in )
{
    err_t error_flag = BRUSHLESS28_OK;
    uint8_t data_buf_wr[ 4 ] = { 0 };
    uint8_t data_buf_rd[ 4 ] = { 0 };
    data_buf_wr[ 0 ] = ( reg << 1 );
    data_buf_wr[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf_wr[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    if ( BRUSHLESS28_SPI_FRAME_CRC_ENABLE == ( ctx->crc_en & BRUSHLESS28_SPI_FRAME_CRC_MASK ) )
    {
        data_buf_wr[ 3 ] = brushless28_calc_crc8 ( data_buf_wr, 3 );
        spi_master_select_device( ctx->chip_select );
        spi_master_transfer ( &ctx->spi, data_buf_wr, data_buf_rd, 4 );
        spi_master_deselect_device( ctx->chip_select );
        if ( data_buf_rd[ 3 ] != brushless28_calc_crc8 ( data_buf_rd, 3 ) )
        {
            error_flag |= BRUSHLESS28_ERROR;
        }
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_transfer ( &ctx->spi, data_buf_wr, data_buf_rd, 3 );
        spi_master_deselect_device( ctx->chip_select );
    }
    return error_flag;
}

err_t brushless28_read_reg ( brushless28_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = BRUSHLESS28_OK;
    uint8_t data_buf_wr[ 4 ] = { 0 };
    uint8_t data_buf_rd[ 4 ] = { 0 };
    data_buf_wr[ 0 ] = ( reg << 1 ) | BRUSHLESS28_SPI_FRAME_READ_BIT;
    data_buf_wr[ 1 ] = DUMMY;
    data_buf_wr[ 2 ] = DUMMY;
    if ( BRUSHLESS28_SPI_FRAME_CRC_ENABLE == ( ctx->crc_en & BRUSHLESS28_SPI_FRAME_CRC_MASK ) )
    {
        data_buf_wr[ 3 ] = brushless28_calc_crc8 ( data_buf_wr, 3 );
        spi_master_select_device( ctx->chip_select );
        spi_master_transfer ( &ctx->spi, data_buf_wr, data_buf_rd, 4 );
        spi_master_deselect_device( ctx->chip_select );
        if ( data_buf_rd[ 3 ] != brushless28_calc_crc8 ( data_buf_rd, 3 ) )
        {
            error_flag |= BRUSHLESS28_ERROR;
        }
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_transfer ( &ctx->spi, data_buf_wr, data_buf_rd, 3 );
        spi_master_deselect_device( ctx->chip_select );
    }
    if ( ( BRUSHLESS28_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf_rd[ 1 ] << 8 ) | data_buf_rd[ 2 ]; 
    }
    return error_flag;
}

err_t brushless28_set_duty_cycle ( brushless28_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless28_pwm_stop ( brushless28_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless28_pwm_start ( brushless28_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void brushless28_set_direction ( brushless28_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void brushless28_switch_direction ( brushless28_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void brushless28_pull_brake ( brushless28_t *ctx )
{
    digital_out_low ( &ctx->brake );
}

void brushless28_release_brake ( brushless28_t *ctx )
{
    digital_out_high ( &ctx->brake );
}

uint8_t brushless28_get_fault_pin ( brushless28_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

static uint8_t brushless28_calc_crc8 ( uint8_t *data_buf, uint8_t len )
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
                crc = ( uint8_t ) ( ( crc << 1 ) ^ 0x2F );
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
