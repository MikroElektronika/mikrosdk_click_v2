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
 * @file joystick3.c
 * @brief Joystick 3 Click Driver.
 */

#include "joystick3.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Joystick 3 atan2 function.
 * @details This function calculates the arctangent of given number, in range [-1..+1].
 * The atan2 function computes the principal value of the arc tangent of y/x,
 * using the signs of both arguments to determine the quadrant of the return value.
 * A domain error may occur if both arguments are zero.
 * @param[in] y First value.
 * @param[in] x Second value.
 * @return The atan2 function returns the arc tangent of y/x in the range [-?, +?] radians.
 * @note None.
 */
static double joystick3_atan2( double y, double x );

void joystick3_cfg_setup ( joystick3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t joystick3_init ( joystick3_t *ctx, joystick3_cfg_t *cfg ) 
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

    return SPI_MASTER_SUCCESS;
}

err_t joystick3_read_raw_adc ( joystick3_t *ctx, uint16_t *raw_x, uint16_t *raw_y )
{
    err_t error_flag = JOYSTICK3_OK;
    // read channel X raw adc
    uint8_t tmp_data = JOYSTICK3_ADC_START_BIT | JOYSTICK3_ADC_SINGLE_ENDED;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &tmp_data, 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, JOYSTICK3_ADC_CHANNEL_X );
    error_flag |= spi_master_read( &ctx->spi, &tmp_data, 1 );
    *raw_x = ( uint16_t ) tmp_data << 8;
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &tmp_data, 1 );
    *raw_x = ( *raw_x | tmp_data ) & JOYSTICK3_ADC_DATA_RESOLUTION;
    spi_master_deselect_device( ctx->chip_select );
    
    // read channel Y raw adc
    tmp_data = JOYSTICK3_ADC_START_BIT | JOYSTICK3_ADC_SINGLE_ENDED;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &tmp_data, 1 );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, JOYSTICK3_ADC_CHANNEL_Y );
    error_flag |= spi_master_read( &ctx->spi, &tmp_data, 1 );
    *raw_y = ( uint16_t ) tmp_data << 8;
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, &tmp_data, 1 );
    *raw_y = ( *raw_y | tmp_data ) & JOYSTICK3_ADC_DATA_RESOLUTION;
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

float joystick3_get_angle ( uint16_t raw_x, uint16_t raw_y )
{
    if ( raw_x )
    {
        return ( float ) ( joystick3_atan2 ( ( ( ( double ) raw_y / JOYSTICK3_ADC_DATA_RESOLUTION_HALF ) - 
                                               JOYSTICK3_PI_RAD_OFFSET ), 
                                             ( ( ( double ) raw_x / JOYSTICK3_ADC_DATA_RESOLUTION_HALF ) - 
                                               JOYSTICK3_PI_RAD_OFFSET ) ) * 
                           JOYSTICK3_RADIANS_TO_DEGREES + JOYSTICK3_ANGLE_ZERO_OFFSET );
    }
    return JOYSTICK3_ZERO_ANGLE;
    
}

uint8_t joystick3_get_position ( uint16_t raw_x, uint16_t raw_y )
{
    if ( ( ( raw_x + JOYSTICK3_NEUTRAL_POSITION_OFFSET ) < JOYSTICK3_ADC_DATA_RESOLUTION_HALF ) ||
         ( ( raw_x - JOYSTICK3_NEUTRAL_POSITION_OFFSET ) > JOYSTICK3_ADC_DATA_RESOLUTION_HALF ) ||
         ( ( raw_y + JOYSTICK3_NEUTRAL_POSITION_OFFSET ) < JOYSTICK3_ADC_DATA_RESOLUTION_HALF ) || 
         ( ( raw_y - JOYSTICK3_NEUTRAL_POSITION_OFFSET ) > JOYSTICK3_ADC_DATA_RESOLUTION_HALF ) )
    {
        float angle = joystick3_get_angle ( raw_x, raw_y );
        if ( ( angle >= ( JOYSTICK3_FULL_ANGLE - JOYSTICK3_ANGLE_POSITION_STEP / 2 ) ) || 
             ( angle < ( JOYSTICK3_ZERO_ANGLE + JOYSTICK3_ANGLE_POSITION_STEP / 2 ) ) )
        {
            return JOYSTICK3_POSITION_UP;
        }
        for ( uint8_t dir = JOYSTICK3_POSITION_UPPER_RIGHT; dir <= JOYSTICK3_POSITION_UPPER_LEFT; dir++ )
        {
            if ( angle < ( JOYSTICK3_ZERO_ANGLE + JOYSTICK3_ANGLE_POSITION_STEP / 2 + 
                           JOYSTICK3_ANGLE_POSITION_STEP * ( dir - 1 ) ) )
            {
                return dir;
            }
        }
    }
    return JOYSTICK3_POSITION_NEUTRAL;
}

static double joystick3_atan2( double y, double x )
{
    double v;
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
