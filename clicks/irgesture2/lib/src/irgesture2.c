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
 * @file irgesture2.c
 * @brief IR Gesture 2 Click Driver.
 */

#include "irgesture2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY       0x00

void irgesture2_cfg_setup ( irgesture2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t irgesture2_init ( irgesture2_t *ctx, irgesture2_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t irgesture2_default_cfg ( irgesture2_t *ctx ) 
{
    err_t error_flag = IRGESTURE2_OK;

    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_MAIN_CONFIG_1, IRGESTRURE2_EOCINTE_ENABLE );
    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_MAIN_CONFIG_2, IRGESTURE2_CONTINUOUS_CONVERSION );
    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_SEQ_CONFIG_1, IRGESTURE2_EOC_DELAY_99p94MS | 
                                                                                IRGESTURE2_INTEGRATION_TIME_50US );
    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_SEQ_CONFIG_2, IRGESTURE2_NRPT_16 | 
                                                                                IRGESTURE2_NCDS_16 );
    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_AFE_CONFIG, IRGESTURE2_ALCEN_ENABLE | 
                                                                              IRGESTURE2_PGA_1 );
    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_LED_CONFIG, IRGESTURE2_DUTY_CYCLE_16 );
    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_COLUMN_GAIN_2_1, IRGESTURE2_UPPER_CGAIN_FACTOR_1p00 | 
                                                                                   IRGESTURE2_LOWER_CGAIN_FACTOR_1p00 );
    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_COLUMN_GAIN_4_3, IRGESTURE2_UPPER_CGAIN_FACTOR_1p00 | 
                                                                                   IRGESTURE2_LOWER_CGAIN_FACTOR_1p00 );
    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_COLUMN_GAIN_6_5, IRGESTURE2_UPPER_CGAIN_FACTOR_1p00 | 
                                                                                   IRGESTURE2_LOWER_CGAIN_FACTOR_1p00 );
    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_COLUMN_GAIN_8_7, IRGESTURE2_UPPER_CGAIN_FACTOR_1p00 | 
                                                                                   IRGESTURE2_LOWER_CGAIN_FACTOR_1p00 );
    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_COLUMN_GAIN_10_9, IRGESTURE2_UPPER_CGAIN_FACTOR_1p00 | 
                                                                                    IRGESTURE2_LOWER_CGAIN_FACTOR_1p00 );
    error_flag |= irgesture2_write_register ( ctx, IRGESTURE2_REG_LED_CTRL, IRGESTURE2_GAINSEL_CGAIN | 
                                                                            IRGESTURE2_ELED_EN_ENABLE );
    Delay_100ms ( );
    
    // clear status
    uint8_t status;
    irgesture2_read_register ( ctx, IRGESTURE2_REG_INT_STATUS, &status );
    
    return error_flag;
}

err_t irgesture2_generic_write ( irgesture2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 2 ] = { 0 };
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = IRGESTURE2_SPI_WRITE;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t irgesture2_generic_read ( irgesture2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t tx_buf[ 2 ] = { 0 };
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = IRGESTURE2_SPI_READ;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t irgesture2_write_register ( irgesture2_t *ctx, uint8_t reg, uint8_t data_in )
{
    return irgesture2_generic_write ( ctx, reg, &data_in, 1 );
}

err_t irgesture2_read_register ( irgesture2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return irgesture2_generic_read ( ctx, reg, data_out, 1 );
}

err_t irgesture2_read_pixels ( irgesture2_t *ctx, int16_t *pixels, bool flip_pixels )
{
    uint8_t data_buf[ IRGESTURE2_NUM_SENSOR_PIXELS * 2 ] = { 0 };
    if ( IRGESTURE2_ERROR == irgesture2_generic_read( ctx, IRGESTURE2_REG_ADC00H, data_buf, 
                                                      IRGESTURE2_NUM_SENSOR_PIXELS * 2 ) )
    {
        return IRGESTURE2_ERROR;
    }
    
    for ( uint8_t cnt = 0; cnt < IRGESTURE2_NUM_SENSOR_PIXELS; cnt++ )
    {
        pixels[ cnt ] = ( ( int16_t ) data_buf[ 2 * cnt ] << 8 ) | data_buf[ 2 * cnt + 1 ];
    }
    if ( true == flip_pixels )
    {
        for ( uint8_t cnt = 0; cnt < ( IRGESTURE2_NUM_SENSOR_PIXELS / 2 ); cnt++ )
        {
            int16_t tmp = pixels[ cnt ];
            pixels[ cnt ] = pixels[ IRGESTURE2_NUM_SENSOR_PIXELS - cnt - 1 ];
            pixels[ IRGESTURE2_NUM_SENSOR_PIXELS - cnt - 1 ] = tmp;
        }
    }
    return IRGESTURE2_OK;
}

uint8_t irgesture2_get_int_pin ( irgesture2_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
