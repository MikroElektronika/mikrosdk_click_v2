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
 * @file dcmotor24.c
 * @brief DC Motor 24 Click Driver.
 */

#include "dcmotor24.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief DC Motor 24 reverse bits function.
 * @details This function returns a byte with reversed bits (from msb first to lsb first)
 * for a provided data byte.
 * @param[in] data_in : Data byte to reverse from msb first to lsb first.
 * @return Reversed byte.
 * @note None.
 */
static uint8_t dcmotor24_reverse_bits ( uint8_t data_in );

void dcmotor24_cfg_setup ( dcmotor24_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->dir  = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;

    cfg->spi_speed    = 100000;
    cfg->spi_mode     = SPI_MASTER_MODE_1;
    cfg->cs_polarity  = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->dev_pwm_freq = DCMOTOR24_DEF_FREQ;
}

err_t dcmotor24_init ( dcmotor24_t *ctx, dcmotor24_cfg_t *cfg ) 
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
    digital_out_init( &ctx->en, cfg->en );

    return SPI_MASTER_SUCCESS;
}

err_t dcmotor24_default_cfg ( dcmotor24_t *ctx ) 
{
    err_t error_flag = DCMOTOR24_OK;
    DCMOTOR24_SET_DATA_SAMPLE_EDGE;
    // Disable current slew rate control, set regulation current level to 4A, and reset diagnostics.
    error_flag |= dcmotor24_write_config ( ctx, DCMOTOR24_CFG_ISR_DIS | 
                                                DCMOTOR24_CFG_CL_4A | 
                                                DCMOTOR24_CFG_DR );
    
    // Set direction to forward, enable output and starts PWM with zero duty cycle.
    dcmotor24_set_direction ( ctx, DCMOTOR24_DIR_FORWARD );
    dcmotor24_enable_output ( ctx );
    error_flag |= dcmotor24_set_duty_cycle ( ctx, 0.0f );
    error_flag |= dcmotor24_pwm_start ( ctx );
    return error_flag;
}

err_t dcmotor24_write_config ( dcmotor24_t *ctx, uint16_t config_word )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = dcmotor24_reverse_bits ( ( uint8_t ) ( config_word & 0xFF ) );
    data_buf[ 1 ] = dcmotor24_reverse_bits ( ( uint8_t ) ( ( config_word >> 8 ) & 0xFF ) );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( DCMOTOR24_OK == error_flag )
    {
        ctx->config_word = config_word;
    }
    return error_flag;
}

err_t dcmotor24_read_diag ( dcmotor24_t *ctx, uint16_t *diag )
{
    uint8_t data_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    data_buf[ 0 ] = dcmotor24_reverse_bits ( ( uint8_t ) ( ctx->config_word & 0xFF ) );
    err_t error_flag = spi_master_set_default_write_data( &ctx->spi, data_buf[ 0 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    data_buf[ 1 ] = dcmotor24_reverse_bits ( ( uint8_t ) ( ( ctx->config_word >> 8 ) & 0xFF ) );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, data_buf[ 1 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( DCMOTOR24_OK == error_flag )
    {
        *diag = ( ( uint16_t ) dcmotor24_reverse_bits ( data_buf[ 1 ] ) << 8 ) | 
                dcmotor24_reverse_bits ( data_buf[ 0 ] );
    }
    return error_flag;
}

void dcmotor24_set_direction ( dcmotor24_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void dcmotor24_switch_direction ( dcmotor24_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void dcmotor24_enable_output ( dcmotor24_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void dcmotor24_disable_output ( dcmotor24_t *ctx )
{
    digital_out_low ( &ctx->en );
}

err_t dcmotor24_set_duty_cycle ( dcmotor24_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t dcmotor24_pwm_stop ( dcmotor24_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t dcmotor24_pwm_start ( dcmotor24_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

static uint8_t dcmotor24_reverse_bits ( uint8_t data_in )
{
    uint8_t data_out = 0;
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        data_out = ( data_out << 1 ) | ( ( data_in >> cnt ) & 1 );
    }
    return data_out;
}

// ------------------------------------------------------------------------- END
