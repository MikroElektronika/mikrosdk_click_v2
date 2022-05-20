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
 * @file hbridge10.c
 * @brief H-Bridge 10 Click Driver.
 */

#include "hbridge10.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void hbridge10_cfg_setup ( hbridge10_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->flt  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = HBRIDGE10_ADC_VREF;
}

err_t hbridge10_init ( hbridge10_t *ctx, hbridge10_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->flt, cfg->flt );

    return HBRIDGE10_OK;
}

err_t hbridge10_default_cfg ( hbridge10_t *ctx ) 
{
    hbridge10_enable_device ( ctx );
    Delay_100ms ( );
    SET_SPI_DATA_SAMPLE_EDGE;
    
    uint16_t dummy_status;
    return hbridge10_transfer_data ( ctx, HBRIDGE10_IN_OPEN_LOAD_OFF |
                                          HBRIDGE10_IN_SHORT_SD_DELAY_12MS |
                                          HBRIDGE10_IN_SOFT_ENABLE, &dummy_status );
}

err_t hbridge10_transfer_data ( hbridge10_t *ctx, uint16_t data_in, uint16_t *data_out )
{
    err_t error_flag = HBRIDGE10_OK;
    ctx->input_data = data_in;
    spi_master_select_device( ctx->chip_select );
    uint8_t reg_data = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, reg_data );
    error_flag |= spi_master_read( &ctx->spi, &reg_data, 1 );
    *data_out = ( uint16_t ) reg_data << 8;
    reg_data = ( uint8_t ) ( data_in & 0xFF );
    error_flag |= spi_master_set_default_write_data( &ctx->spi, reg_data );
    error_flag |= spi_master_read( &ctx->spi, &reg_data, 1 );
    *data_out = *data_out | reg_data;
    error_flag |= spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t hbridge10_set_output_state ( hbridge10_t *ctx, uint8_t channel, uint8_t state )
{
    if ( ( channel < HBRIDGE10_CHANNEL_OUT1 ) || 
         ( channel > HBRIDGE10_CHANNEL_OUT3 ) || 
         ( state > HBRIDGE10_OUT_LOW ) )
    {
        return HBRIDGE10_ERROR;
    }
    // clear channel bits
    uint8_t shift_ch = ( 4 - channel ) * 4 - 1;
    ctx->input_data &= ~( HBRIDGE10_OUT_MASK << shift_ch );
    ctx->input_data |= ( state << shift_ch );
    uint16_t dummy_status;
    return hbridge10_transfer_data ( ctx, ctx->input_data, &dummy_status );
}

err_t hbridge10_get_status ( hbridge10_t *ctx, uint16_t *status )
{
    ctx->input_data |= HBRIDGE10_IN_STATUS_RESET;
    err_t error_flag = hbridge10_transfer_data ( ctx, ctx->input_data, status );
    ctx->input_data &= ~HBRIDGE10_IN_STATUS_RESET;
    return error_flag;
}

err_t hbridge10_read_an_pin_value ( hbridge10_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t hbridge10_read_an_pin_voltage ( hbridge10_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

void hbridge10_enable_device ( hbridge10_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void hbridge10_disable_device ( hbridge10_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

uint8_t hbridge10_get_fault_pin ( hbridge10_t *ctx )
{
    return digital_in_read ( &ctx->flt );
}

// ------------------------------------------------------------------------- END
