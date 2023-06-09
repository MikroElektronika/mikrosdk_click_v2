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
 * @file vtohz3.c
 * @brief V to Hz 3 Click Driver.
 */

#include "vtohz3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void vtohz3_cfg_setup ( vtohz3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->buf  = HAL_PIN_NC;
    cfg->fout = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /**< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->vref       = VTOHZ3_VREF_3V3;
}

err_t vtohz3_init ( vtohz3_t *ctx, vtohz3_cfg_t *cfg ) 
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
    
    digital_out_init( &ctx->buf, cfg->buf );
    digital_out_low ( &ctx->buf );

    digital_in_init( &ctx->fout, cfg->fout );

    return SPI_MASTER_SUCCESS;
}

err_t vtohz3_set_input_frequency ( vtohz3_t *ctx, uint32_t freq )
{
    #define FREQ_IN_RANGE_UPPER_MINIMAL     2078
    #define ENABLE_IN_FREQUENCY             0x02
    uint8_t tx_buf[ 2 ] = { 0 };
    uint8_t oct = 0;
    uint16_t dac = 0;
    
    // Limited by the AD7740 Voltage-to-Frequency Converter
    if ( freq > VTOHZ3_MAXIMAL_IN_FREQUENCY || freq < VTOHZ3_MINIMAL_IN_FREQUENCY )
    {
        return VTOHZ3_ERROR;
    }
    ctx->clock_in_freq = freq;
    
    while ( ( freq >> oct ) > FREQ_IN_RANGE_UPPER_MINIMAL )
    {
        oct++;
    }
    
    dac = ( uint16_t )( ( 2.0 - ( float ) ( ( 1ul << oct ) * FREQ_IN_RANGE_UPPER_MINIMAL ) / freq ) * 1024 );
    tx_buf[ 0 ] = ( oct << 4 ) | ( ( dac >> 6 ) & 0x0F );
    tx_buf[ 1 ] = ( ( dac << 2 ) & 0xFC ) | ENABLE_IN_FREQUENCY;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t vtohz3_disable_input_frequency ( vtohz3_t *ctx ) 
{
    #define DISABLE_IN_FREQUENCY            0x03
    uint8_t tx_buf[ 2 ] = { 0, DISABLE_IN_FREQUENCY };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void vtohz3_set_buf_pin ( vtohz3_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->buf, state );
}

uint8_t vtohz3_get_fout_pin ( vtohz3_t *ctx ) 
{
    return digital_in_read( &ctx->fout );
}

err_t vtohz3_read_an_pin_value ( vtohz3_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t vtohz3_read_an_pin_voltage ( vtohz3_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

uint32_t vtohz3_get_frequency ( vtohz3_t *ctx, float voltage, float vref_in )
{
    uint32_t fout = ( uint32_t ) ( 0.1 * ctx->clock_in_freq + 0.8 * ( voltage / vref_in ) * ctx->clock_in_freq );
    for ( uint8_t step = 2; step <= 10; step++ )
    {
        uint32_t freq_step = ctx->clock_in_freq / ( step * ( step - 1 ) * 2 );
        if ( fout > ( ( ctx->clock_in_freq / step ) + freq_step ) )
        {
            fout = ctx->clock_in_freq / ( step - 1 );
            return fout;
        }
    }
    fout = ctx->clock_in_freq / 10;
    return fout;
}

// ------------------------------------------------------------------------- END
