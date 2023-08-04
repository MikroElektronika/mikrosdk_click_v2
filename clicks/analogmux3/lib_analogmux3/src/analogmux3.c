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
 * @file analogmux3.c
 * @brief Analog MUX 3 Click Driver.
 */

#include "analogmux3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Reset delay.
 * @details Reset delay for 100 milliseconds.
 */
static void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void analogmux3_cfg_setup ( analogmux3_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_2;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref       = 2.048;
}

err_t analogmux3_init ( analogmux3_t *ctx, analogmux3_cfg_t *cfg ) {
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

    digital_out_init( &ctx->rst, cfg->rst );

    return SPI_MASTER_SUCCESS;
}

err_t analogmux3_default_cfg ( analogmux3_t *ctx ) {
   
    analogmux3_hw_reset( ctx );
    
    return ANALOGMUX3_OK;
}

void analogmux3_hw_reset ( analogmux3_t *ctx ) {
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
}

err_t analogmux3_generic_write ( analogmux3_t *ctx, uint8_t data_in ) {
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &data_in, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t analogmux3_set_channel ( analogmux3_t *ctx, uint8_t mux_ch ) {
    uint8_t mux_buf;
    err_t status;
    
    status = ANALOGMUX3_OK;
    mux_buf = ANALOGMUX3_VAL_CHANNEL_0;
    
    if ( mux_ch > ANALOGMUX3_SET_CHANNEL_7 ) {
        mux_buf = ANALOGMUX3_VAL_CHANNEL_OFF;
        status = ANALOGMUX3_ERROR;
    }
    
    mux_buf <<= mux_ch;
    analogmux3_generic_write( ctx, mux_buf );

    return status; 
}

err_t analogmux3_read_an_pin_value ( analogmux3_t *ctx, uint16_t *data_out ) {
    return analog_in_read( &ctx->adc, data_out );
}

err_t analogmux3_read_an_pin_voltage ( analogmux3_t *ctx, float *data_out ) {
    return analog_in_read_voltage( &ctx->adc, data_out );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void ) {
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
