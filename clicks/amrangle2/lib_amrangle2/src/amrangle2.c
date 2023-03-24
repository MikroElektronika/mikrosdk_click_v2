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
 * @file amrangle2.c
 * @brief AMR Angle 2 Click Driver.
 */

#include "amrangle2.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void amrangle2_cfg_setup ( amrangle2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->cst  = HAL_PIN_NC;
    cfg->eoc  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->vref        = 3.3;
}

err_t amrangle2_init ( amrangle2_t *ctx, amrangle2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->cst, cfg->cst );
    digital_out_high( &ctx->cst );

    digital_in_init( &ctx->eoc, cfg->eoc );

    return SPI_MASTER_SUCCESS;
}

err_t amrangle2_default_cfg ( amrangle2_t *ctx ) 
{
    err_t error_flag = AMRANGLE2_OK;
    error_flag |= amrangle2_calibrate_temperature ( ctx );
    if ( AMRANGLE2_ERROR == amrangle2_spi_transfer ( ctx, AMRANGLE2_REG_ADC_CONFIGURATION | 
                                                          AMRANGLE2_REFSEL_EXT_DIFFERENTIAL | 
                                                          AMRANGLE2_AVGON | 
                                                          AMRANGLE2_NAVG_32 ) )
    {
        return AMRANGLE2_ERROR;
    }
    if ( AMRANGLE2_ERROR == amrangle2_spi_transfer ( ctx, AMRANGLE2_REG_BIPOLAR | 
                                                          AMRANGLE2_BCH01_BIPOLAR_FULLY_DIFF | 
                                                          AMRANGLE2_BCH23_BIPOLAR_FULLY_DIFF ) )
    {
        return AMRANGLE2_ERROR;
    }
    if ( AMRANGLE2_ERROR == amrangle2_spi_transfer ( ctx, AMRANGLE2_REG_RANGE | 
                                                          AMRANGLE2_RANGE01_FULL_VREF | 
                                                          AMRANGLE2_RANGE23_FULL_VREF ) )
    {
        return AMRANGLE2_ERROR;
    }
    if ( AMRANGLE2_ERROR == amrangle2_spi_transfer ( ctx, AMRANGLE2_REG_ADC_MODE_CONTROL | 
                                                          AMRANGLE2_SCAN_STANDARD_INT | 
                                                          AMRANGLE2_RESET_FIFO ) )
    {
        return AMRANGLE2_ERROR;
    }
    return error_flag;
}

err_t amrangle2_spi_transfer ( amrangle2_t *ctx, uint16_t data_in )
{
    err_t error_flag = AMRANGLE2_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, data_buf[ 0 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 0 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, data_buf[ 1 ] );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );
    if ( AMRANGLE2_OK == error_flag )
    {
        return ( err_t ) ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] );
    }
    return error_flag;
}

err_t amrangle2_read_an_pin_value ( amrangle2_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t amrangle2_read_an_pin_voltage ( amrangle2_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t amrangle2_calibrate_temperature ( amrangle2_t *ctx )
{
    err_t error_flag = AMRANGLE2_OK;
    float voltage;
    float avg_voltage = 0;
    uint32_t num_conv = 0;
    while ( num_conv < AMRANGLE2_TEMP_NUM_CONVERSIONS )
    {
        error_flag |= amrangle2_read_an_pin_voltage ( ctx, &voltage );
        avg_voltage += voltage;
        num_conv++;
    }
    avg_voltage /= AMRANGLE2_TEMP_NUM_CONVERSIONS;
    ctx->vcal = avg_voltage;
    return error_flag;
}

err_t amrangle2_read_temperature ( amrangle2_t *ctx, float *temperature )
{
    err_t error_flag = AMRANGLE2_OK;
    float voltage;
    float avg_voltage = 0;
    uint32_t num_conv = 0;
    while ( num_conv < AMRANGLE2_TEMP_NUM_CONVERSIONS )
    {
        error_flag |= amrangle2_read_an_pin_voltage ( ctx, &voltage );
        avg_voltage += voltage;
        num_conv++;
    }
    avg_voltage /= AMRANGLE2_TEMP_NUM_CONVERSIONS;
    if ( AMRANGLE2_OK == error_flag )
    {
        *temperature = ( ( avg_voltage - ctx->vcal ) / AMRANGLE2_TEMP_VDD + 
                         ( AMRANGLE2_TEMP_TCAL * AMRANGLE2_TEMP_TCO ) ) / AMRANGLE2_TEMP_TCO;
        return AMRANGLE2_OK;
    }
    return AMRANGLE2_ERROR;
}

err_t amrangle2_read_vsin_vcos ( amrangle2_t *ctx, float *vsin, float *vcos )
{
    err_t data_out;
    amrangle2_start_conversion ( ctx );
    data_out = amrangle2_spi_transfer ( ctx, AMRANGLE2_REG_ADC_MODE_CONTROL | 
                                             AMRANGLE2_SCAN_STANDARD_INT | 
                                             AMRANGLE2_CHSEL_AIN1 );
    if ( ( 0 == data_out ) || ( AMRANGLE2_ERROR == data_out ) )
    {
        return AMRANGLE2_ERROR;
    }
    *vsin = ( ( ( int16_t ) ( data_out << 4 ) ) >> 4 ) * AMRANGLE2_ADC_VREF * 2.0 / AMRANGLE2_ADC_RESOLUTION;
    amrangle2_start_conversion ( ctx );
    data_out = amrangle2_spi_transfer ( ctx, AMRANGLE2_REG_ADC_MODE_CONTROL | 
                                             AMRANGLE2_SCAN_STANDARD_INT | 
                                             AMRANGLE2_CHSEL_AIN3 );
    if ( ( 0 == data_out ) || ( AMRANGLE2_ERROR == data_out ) )
    {
        return AMRANGLE2_ERROR;
    }
    *vcos = ( ( ( int16_t ) ( data_out << 4 ) ) >> 4 ) * AMRANGLE2_ADC_VREF * 2.0 / AMRANGLE2_ADC_RESOLUTION;
    return AMRANGLE2_OK;
}

err_t amrangle2_read_angle ( amrangle2_t *ctx, float *angle )
{
    float vsin, vcos;
    if ( AMRANGLE2_OK == amrangle2_read_vsin_vcos( ctx, &vsin, &vcos ) )
    {
        if ( 0.0 != vcos )
        {
            *angle = ( atan2 ( vsin, vcos ) / 2 ) * AMRANGLE2_RADIANS_TO_DEGREES + AMRANGLE2_ANGLE_ZERO_OFFSET;
            return AMRANGLE2_OK;
        }
    }
    return AMRANGLE2_ERROR;
}

void amrangle2_set_cst_pin ( amrangle2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cst, state );
}

uint8_t amrangle2_get_eoc_pin ( amrangle2_t *ctx )
{
    return digital_in_read ( &ctx->eoc );
}

void amrangle2_start_conversion ( amrangle2_t *ctx )
{
    digital_out_low ( &ctx->cst );
    Delay_10us ( );
    digital_out_high ( &ctx->cst );
    Delay_10us ( );
    while ( amrangle2_get_eoc_pin ( ctx ) );
}

// ------------------------------------------------------------------------- END
