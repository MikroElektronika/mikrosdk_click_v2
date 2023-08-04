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
 * @file digipot8.c
 * @brief DIGI POT 8 Click Driver.
 */

#include "digipot8.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void digipot8_cfg_setup ( digipot8_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an_pin   = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t digipot8_init ( digipot8_t *ctx, digipot8_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;
    analog_in_config_t adc_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );
    
    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an_pin;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR )
    {
        return ADC_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    ctx->vref = cfg->vref;
    
    return SPI_MASTER_SUCCESS;
}

err_t digipot8_write_data ( digipot8_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag;
    uint8_t tx_buf[ 2 ];
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = data_in ;
    
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );  
    
    return error_flag;
}

err_t digipot8_set_wiper_1 ( digipot8_t *ctx, uint8_t data_in )
{
    err_t error_flag = digipot8_write_data( ctx, DIGIPOT8_REG_RDAC1, data_in );
    
    return error_flag;
}

err_t digipot8_set_wiper_2 ( digipot8_t *ctx, uint8_t data_in )
{
    err_t error_flag = digipot8_write_data( ctx, DIGIPOT8_REG_RDAC2, data_in );
    
    return error_flag;
}

err_t digipot8_set_wiper_3 ( digipot8_t *ctx, uint8_t data_in )
{
    err_t error_flag = digipot8_write_data( ctx, DIGIPOT8_REG_RDAC3, data_in );
    
    return error_flag;
}

err_t digipot8_set_wiper_4 ( digipot8_t *ctx, uint8_t data_in )
{
    err_t error_flag = digipot8_write_data( ctx, DIGIPOT8_REG_RDAC4, data_in );
    
    return error_flag;
}

err_t digipot8_set_wiper_5 ( digipot8_t *ctx, uint8_t data_in )
{
    err_t error_flag = digipot8_write_data( ctx, DIGIPOT8_REG_RDAC5, data_in );
    
    return error_flag;
}

err_t digipot8_set_wiper_6 ( digipot8_t *ctx, uint8_t data_in )
{
    err_t error_flag = digipot8_write_data( ctx, DIGIPOT8_REG_RDAC6, data_in );
    
    return error_flag;
}

uint16_t digipot8_generic_read ( digipot8_t *ctx )
{
    uint16_t rx_data = 0;

    analog_in_read( &ctx->adc, &rx_data );

    return rx_data;
}

float digipot8_read_voltage ( digipot8_t *ctx )
{
    float rx_data = 0;

    analog_in_read_voltage( &ctx->adc, &rx_data );

    return rx_data;
}

// ------------------------------------------------------------------------- END
