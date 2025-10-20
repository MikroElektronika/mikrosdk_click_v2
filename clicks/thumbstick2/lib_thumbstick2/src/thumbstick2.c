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
 * @file thumbstick2.c
 * @brief Thumbstick 2 Click Driver.
 */

#include "thumbstick2.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Thumbstick 2 atan2 function.
 * @details This function calculates the arctangent of given number, in range [-1..+1].
 * The atan2 function computes the principal value of the arc tangent of y/x,
 * using the signs of both arguments to determine the quadrant of the return value.
 * A domain error may occur if both arguments are zero.
 * @param[in] y : First value.
 * @param[in] x : Second value.
 * @return The atan2 function returns the arc tangent of y/x in the range [-PI, +PI] radians.
 * @note None.
 */
static double thumbstick2_atan2( double y, double x );

void thumbstick2_cfg_setup ( thumbstick2_cfg_t *cfg ) 
{
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->vb = HAL_PIN_NC;
    cfg->sw = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->dev_pwm_freq = THUMBSTICK2_PWM_DEF_FREQ;
}

err_t thumbstick2_init ( thumbstick2_t *ctx, thumbstick2_cfg_t *cfg ) 
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

    pwm_cfg.pin     = cfg->vb;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    digital_in_init( &ctx->sw, cfg->sw );

    thumbstick2_set_duty_cycle ( ctx, THUMBSTICK2_PWM_MIN_DUTY );
    thumbstick2_pwm_start( ctx );

    return THUMBSTICK2_OK;
}

err_t thumbstick2_read_raw_adc ( thumbstick2_t *ctx, uint16_t *raw_x, uint16_t *raw_y )
{
    err_t error_flag = THUMBSTICK2_OK;
    // read channel X raw adc
    uint8_t tmp_data = THUMBSTICK2_ADC_START_BIT;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &tmp_data, 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, THUMBSTICK2_ADC_CHANNEL_X | THUMBSTICK2_ADC_SINGLE_ENDED );
    error_flag |= spi_master_read( &ctx->spi, &tmp_data, 1 );
    *raw_x = ( uint16_t ) tmp_data << 8;
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &tmp_data, 1 );
    *raw_x = ( *raw_x | tmp_data ) & THUMBSTICK2_ADC_DATA_RESOLUTION;
    spi_master_deselect_device( ctx->chip_select );
    
    // read channel Y raw adc
    tmp_data = THUMBSTICK2_ADC_START_BIT;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &tmp_data, 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, THUMBSTICK2_ADC_CHANNEL_Y | THUMBSTICK2_ADC_SINGLE_ENDED );
    error_flag |= spi_master_read( &ctx->spi, &tmp_data, 1 );
    *raw_y = ( uint16_t ) tmp_data << 8;
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &tmp_data, 1 );
    *raw_y = ( *raw_y | tmp_data ) & THUMBSTICK2_ADC_DATA_RESOLUTION;
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

float thumbstick2_get_angle ( uint16_t raw_x, uint16_t raw_y )
{
    double atan2_x = ( THUMBSTICK2_PI_RAD_OFFSET - ( ( double ) raw_x / THUMBSTICK2_ADC_DATA_RESOLUTION_HALF ) );
    double atan2_y = ( THUMBSTICK2_PI_RAD_OFFSET - ( ( double ) raw_y / THUMBSTICK2_ADC_DATA_RESOLUTION_HALF ) );
    float angle = THUMBSTICK2_ZERO_ANGLE;
    if ( atan2_y )
    {
        angle = thumbstick2_atan2 ( atan2_x, atan2_y ) * THUMBSTICK2_RADIANS_TO_DEGREES + THUMBSTICK2_ANGLE_ZERO_OFFSET;
    }
    return angle;
}

uint8_t thumbstick2_get_position ( uint16_t raw_x, uint16_t raw_y )
{
    uint8_t position = THUMBSTICK2_POSITION_NEUTRAL;
    uint8_t pos_cnt = 0;
    float angle = thumbstick2_get_angle ( raw_x, raw_y );
    if ( ( ( raw_x + THUMBSTICK2_NEUTRAL_POSITION_OFFSET ) < THUMBSTICK2_ADC_DATA_RESOLUTION_HALF ) ||
         ( ( raw_x - THUMBSTICK2_NEUTRAL_POSITION_OFFSET ) > THUMBSTICK2_ADC_DATA_RESOLUTION_HALF ) ||
         ( ( raw_y + THUMBSTICK2_NEUTRAL_POSITION_OFFSET ) < THUMBSTICK2_ADC_DATA_RESOLUTION_HALF ) || 
         ( ( raw_y - THUMBSTICK2_NEUTRAL_POSITION_OFFSET ) > THUMBSTICK2_ADC_DATA_RESOLUTION_HALF ) )
    {
        if ( ( angle >= ( THUMBSTICK2_FULL_ANGLE - THUMBSTICK2_ANGLE_POSITION_STEP / 2 ) ) || 
             ( angle < ( THUMBSTICK2_ZERO_ANGLE + THUMBSTICK2_ANGLE_POSITION_STEP / 2 ) ) )
        {
            position = THUMBSTICK2_POSITION_UP;
        }
        else
        {
            for ( pos_cnt = THUMBSTICK2_POSITION_UPPER_LEFT; pos_cnt <= THUMBSTICK2_POSITION_UPPER_RIGHT; pos_cnt++ )
            {
                if ( angle < ( THUMBSTICK2_ZERO_ANGLE + THUMBSTICK2_ANGLE_POSITION_STEP / 2 + 
                               THUMBSTICK2_ANGLE_POSITION_STEP * ( pos_cnt - 1 ) ) )
                {
                    position = pos_cnt;
                    break;
                }
            }
        }
    }
    return position;
}

err_t thumbstick2_set_duty_cycle ( thumbstick2_t *ctx, float duty_cycle )
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t thumbstick2_pwm_stop ( thumbstick2_t *ctx )
{
    return pwm_stop( &ctx->pwm );
}

err_t thumbstick2_pwm_start ( thumbstick2_t *ctx )
{
    return pwm_start( &ctx->pwm );
}

uint8_t thumbstick2_get_sw_pin ( thumbstick2_t *ctx )
{
    return digital_in_read ( &ctx->sw );
}

static double thumbstick2_atan2( double y, double x )
{
    double v = 0;
    if ( x > 0 )
    {
        v = atan( y / x );
    }
    else if ( x < 0 )
    {
        if ( y >= 0 )
        {
            v = atan( y / x ) + PI;
        }
        else
        {
            v = atan( y / x ) - PI;
        }
    }
    else
    {
        if ( y > 0 )
        {
            v = PI / 2;
        }
        else
        {
            v = -( PI / 2 );
        }
    }
    return v;
}

// ------------------------------------------------------------------------- END
