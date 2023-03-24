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
 * @file amrangle.c
 * @brief AMR Angle Click Driver.
 */

// ------------------------------------------------------------- PRIVATE MACROS

#include "amrangle.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief ADC acquire mask.
 * @details Mask of valid bits acquired from adc.
 */
#define DEV_AMRANGLE_ADC_ACQ_MASK                                        0x3FFC

/**
 * @brief ADC resolution.
 * @details Resolution of adc.
 */
#define DEV_AMRANGLE_ADC_RESOLUTION                                      4095

/**
 * @brief ADC power supply value.
 * @details Power supply voltage value of adc.
 */
#define DEV_AMRANGLE_ADC_VSUPPLY                                         3.3

/**
 * @brief Degrees range constant.
 * @details Conversion constant from radian to degrees.
 */
#define DEV_AMRANGLE_ADC_CONV_DEG                                        180

/**
 * @brief Pi value constant.
 * @details Conversion constant from radian to degrees.
 */
#define DEV_AMRANGLE_ADC_CONV_PI                                         3.14159265

/**
 * @brief Temperature intercept constant.
 * @details Constant value calculated from Vtemp linear function.
 */
#define DEV_AMRANGLE_TEMP_INTERCEPT                                      0.77

/**
 * @brief Temperature slope constant.
 * @details Constant value calculated from Vtemp linear function.
 */
#define DEV_AMRANGLE_TEMP_SLOPE                                          0.011

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void adc_conv_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void amrangle_cfg_setup ( amrangle_cfg_t *cfg, uint8_t sel_toolchain ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->gc   = HAL_PIN_NC;
    cfg->pd   = HAL_PIN_NC;

    cfg->spi_speed = 100000;
    if ( sel_toolchain == AMRANGLE_ARM_TOOLCHAIN ) {
        cfg->spi_mode = SPI_MASTER_MODE_1;
    } else {
        cfg->spi_mode = SPI_MASTER_MODE_0;
    }
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_12_BIT;
    cfg->vref       = 3.3;  // Should be set via CODEGRIP since it uses the dev board Vref
}

err_t amrangle_init ( amrangle_t *ctx, amrangle_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
    
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    if ( analog_in_set_vref_value( &ctx->adc, cfg->vref ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    if ( analog_in_set_resolution( &ctx->adc, cfg->resolution ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->gc, cfg->gc );
    digital_out_init( &ctx->pd, cfg->pd );

    return SPI_MASTER_SUCCESS;
}

void amrangle_default_cfg ( amrangle_t *ctx ) {
    // Click default configuration.
    amrangle_gain_control_mode( ctx, AMRANGLE_GAIN_CONTROL_DIS );
    amrangle_power_down_pin( ctx, AMRANGLE_POWER_DOWN_DIS );
    spi_master_select_device( ctx->chip_select );
}

float amrangle_angle_read ( amrangle_t *ctx ) {
    uint8_t rx_buf[ 4 ];
    uint16_t sin_adc;
    uint16_t cos_adc;
    float v_sin;
    float v_cos;
    float result;
    
    spi_master_deselect_device( ctx->chip_select );
    adc_conv_delay( );
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, rx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    
    sin_adc = rx_buf[ 0 ];
    sin_adc <<= 8;
    sin_adc |= rx_buf[ 1 ];
    sin_adc &= DEV_AMRANGLE_ADC_ACQ_MASK;
    sin_adc >>= 2;
    
    cos_adc = rx_buf[ 2 ];
    cos_adc <<= 8;
    cos_adc |= rx_buf[ 3 ];
    cos_adc &= DEV_AMRANGLE_ADC_ACQ_MASK;
    cos_adc >>= 2;
    
    v_sin = ( ( float )sin_adc / DEV_AMRANGLE_ADC_RESOLUTION ) * DEV_AMRANGLE_ADC_VSUPPLY;
    v_cos = ( ( float )cos_adc / DEV_AMRANGLE_ADC_RESOLUTION ) * DEV_AMRANGLE_ADC_VSUPPLY;
    v_sin -= DEV_AMRANGLE_ADC_VSUPPLY / 2;
    v_cos -= DEV_AMRANGLE_ADC_VSUPPLY / 2;
    
    result = atan2( v_cos, v_sin );
    result *= DEV_AMRANGLE_ADC_CONV_DEG;
    result /= 2 * DEV_AMRANGLE_ADC_CONV_PI;
    
    return result;
}

err_t amrangle_read_vtp_voltage ( amrangle_t *ctx, float *vtp_volts ) {
    return analog_in_read_voltage( &ctx->adc, vtp_volts );
}

float amrangle_read_vtp_temp ( amrangle_t *ctx ) {
    float temp;
    
    amrangle_read_vtp_voltage( ctx, &temp );
    temp = ( temp - DEV_AMRANGLE_TEMP_INTERCEPT ) / DEV_AMRANGLE_TEMP_SLOPE;
    return temp;
}

void amrangle_gain_control_mode ( amrangle_t *ctx, uint8_t gain_control ) {
    digital_out_write( &ctx->gc, gain_control );
}

void amrangle_power_down_pin ( amrangle_t *ctx, uint8_t pd_state ) {
    digital_out_write( &ctx->pd, pd_state );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void adc_conv_delay ( void ) {
    Delay_10us( );
}

// ------------------------------------------------------------------------- END
