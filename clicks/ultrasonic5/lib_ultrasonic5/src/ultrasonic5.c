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
 * @file ultrasonic5.c
 * @brief Ultrasonic 5 Click Driver.
 */

#include "ultrasonic5.h"

/**
 * @brief Two bytes to word macro.
 * @details Definition of two bytes to word conversion.
 */
#define TWO_BYTES_TO_WORD( x )  ( ( ( uint16_t ) x[ 0 ] << 8 ) | x[ 1 ] )  

/**
 * @brief Dummy data and SPI read bit.
 * @details Definition of dummy data and SPI read bit.
 */
#define DUMMY                   0x00
#define SPI_READ_BIT            0x80

/**
 * @brief Ultrasonic 5 calculate parity bit function.
 * @details This function calculates the parity bit.
 * @param[in] data_in : Data from which it will calculate the parity bit.
 * @return @li @c  0 - Even parity,
 *         @li @c  1 - ODD parity.
 * @note None.
 */
static uint8_t ultrasonic5_cal_parity_bit ( uint16_t data_in );

void ultrasonic5_cfg_setup ( ultrasonic5_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->io1  = HAL_PIN_NC;
    cfg->io2  = HAL_PIN_NC;
    cfg->out4 = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->vref        = 3.3;
    cfg->dev_pwm_freq = ULTRASONIC5_DEF_FREQ;
}

err_t ultrasonic5_init ( ultrasonic5_t *ctx, ultrasonic5_cfg_t *cfg ) 
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
    
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }
    
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->io2;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    digital_out_init( &ctx->io1, cfg->io1 );

    digital_in_init( &ctx->out4, cfg->out4 );

    return ULTRASONIC5_OK;
}

err_t ultrasonic5_default_cfg ( ultrasonic5_t *ctx ) 
{
    err_t error_flag = ULTRASONIC5_OK;
    ULTRASONIC5_SET_DATA_SAMPLE_EDGE;
    
    if ( ULTRASONIC5_ERROR == ultrasonic5_check_communication ( ctx ) )
    {
        return ULTRASONIC5_ERROR;
    }
    ultrasonic5_set_io1_pin ( ctx );
    ultrasonic5_write_register ( ctx, ULTRASONIC5_REG_BPF_CONFIG_1, ULTRASONIC5_BPF_CONFIG_1_RESET );
    ultrasonic5_write_register ( ctx, ULTRASONIC5_REG_BPF_CONFIG_2, ULTRASONIC5_BPF_CONFIG_2_RESET );
    ultrasonic5_write_register ( ctx, ULTRASONIC5_REG_DEV_CTRL_1, ULTRASONIC5_DEV_CTRL_1_RESET );
    ultrasonic5_write_register ( ctx, ULTRASONIC5_REG_DEV_CTRL_2, ULTRASONIC5_DEV_CTRL_2_LOGAMP_DIS_FIRST | 
                                                                  ULTRASONIC5_DEV_CTRL_2_LOGAMP_DIS_LAST );
    ultrasonic5_write_register ( ctx, ULTRASONIC5_REG_DEV_CTRL_3, ULTRASONIC5_DEV_CTRL_3_IO_MODE_1 );
    ultrasonic5_write_register ( ctx, ULTRASONIC5_REG_VDRV_CTRL, ULTRASONIC5_VDRV_CTRL_VDRV_CURR_LVL_20MA | 
                                                                 ULTRASONIC5_VDRV_CTRL_VDRV_VOLT_LVL_5V );
    ultrasonic5_write_register ( ctx, ULTRASONIC5_REG_ECHO_INT_CONFIG, ULTRASONIC5_ECHO_INT_CONFIG_RESET );
    ultrasonic5_write_register ( ctx, ULTRASONIC5_REG_ZC_CONFIG, ULTRASONIC5_ZC_CONFIG_RESET );
    ultrasonic5_write_register ( ctx, ULTRASONIC5_REG_BURST_PULSE, ULTRASONIC5_BURST_PULSE_BURST_PULSE_16 );
    ultrasonic5_write_register ( ctx, ULTRASONIC5_REG_TOF_CONFIG, ULTRASONIC5_TOF_CONFIG_RESET );

    error_flag |= ultrasonic5_set_duty_cycle ( ctx, ULTRASONIC5_DEF_DYTY );
    return error_flag;
}

err_t ultrasonic5_write_register ( ultrasonic5_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = ULTRASONIC5_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( ( reg & 0x3F ) << 1 );
    data_buf[ 1 ] = data_in;
    data_buf[ 0 ] |= ultrasonic5_cal_parity_bit ( TWO_BYTES_TO_WORD ( data_buf ) );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, data_buf[ 0 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, data_buf[ 1 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ( data_buf[ 1 ] == ( ( reg & 0x3F ) << 1 ) ) && ( ULTRASONIC5_OK == error_flag ) )
    {
        return data_buf[ 0 ];
    }
    return ULTRASONIC5_ERROR;
}

err_t ultrasonic5_read_register ( ultrasonic5_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = ULTRASONIC5_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = SPI_READ_BIT | ( ( reg & 0x3F ) << 1 );
    data_buf[ 1 ] = DUMMY;
    data_buf[ 0 ] |= ultrasonic5_cal_parity_bit ( TWO_BYTES_TO_WORD ( data_buf ) );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, data_buf[ 0 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, data_buf[ 1 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ULTRASONIC5_OK == error_flag )
    {
        *data_out = data_buf[ 1 ];
        return data_buf[ 0 ];
    }
    return ULTRASONIC5_ERROR;
}

err_t ultrasonic5_check_communication ( ultrasonic5_t *ctx )
{
    uint8_t device_id = 0;
    if ( ULTRASONIC5_ERROR != ultrasonic5_read_register ( ctx, ULTRASONIC5_REG_DEVICE_ID, &device_id ) )
    {
        if ( ULTRASONIC5_DEVICE_ID == device_id )
        {
            return ULTRASONIC5_OK;
        }
    }
    return ULTRASONIC5_ERROR;
}

void ultrasonic5_set_io1_pin ( ultrasonic5_t *ctx )
{
    digital_out_high ( &ctx->io1 );
}

void ultrasonic5_clear_io1_pin ( ultrasonic5_t *ctx )
{
    digital_out_low ( &ctx->io1 );
}

uint8_t ultrasonic5_get_out4_pin ( ultrasonic5_t *ctx )
{
    return digital_in_read ( &ctx->out4 );
}

err_t ultrasonic5_read_an_pin_value ( ultrasonic5_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t ultrasonic5_read_an_pin_voltage ( ultrasonic5_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t ultrasonic5_set_duty_cycle ( ultrasonic5_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t ultrasonic5_pwm_stop ( ultrasonic5_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t ultrasonic5_pwm_start ( ultrasonic5_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

static uint8_t ultrasonic5_cal_parity_bit ( uint16_t data_in )
{
    uint8_t parity = 0;
    while ( data_in & 0xFFFE )
    {
        parity += ( data_in & ULTRASONIC5_ODD_PARITY );
        data_in >>= 1;
    }
    return parity & ULTRASONIC5_ODD_PARITY;
}

// ------------------------------------------------------------------------- END
