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
 * @file digiisolator2.c
 * @brief DIGI Isolator 2 Click Driver.
 */

#include "digiisolator2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY           0x00
#define SPI_WRITE_BIT   0x80

void digiisolator2_cfg_setup ( digiisolator2_cfg_t *cfg ) 
{
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->sync = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = DIGIISOLATOR2_DRV_SEL_SPI;
}

err_t digiisolator2_init ( digiisolator2_t *ctx, digiisolator2_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( DIGIISOLATOR2_DRV_SEL_SPI == ctx->drv_sel )
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

        digital_out_init( &ctx->rst, cfg->rst );
        digital_out_high( &ctx->rst );

        digital_in_init( &ctx->sync, cfg->sync );
        digital_in_init( &ctx->int_pin, cfg->int_pin );
    }
    else
    {
        digital_in_init( &ctx->out1, cfg->miso );
        digital_in_init( &ctx->out2, cfg->mosi );
        digital_in_init( &ctx->out3, cfg->sck );
        digital_in_init( &ctx->out4, cfg->cs );
        digital_in_init( &ctx->out5, cfg->int_pin );
        digital_in_init( &ctx->out6, cfg->rst );
        digital_in_init( &ctx->out8, cfg->sync );
    }
    digital_out_init( &ctx->en, cfg->en );

    return DIGIISOLATOR2_OK;
}

err_t digiisolator2_spi_write ( digiisolator2_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    if ( ( reg < DIGIISOLATOR2_REG_FILTER_CH1_CH2 ) || 
         ( reg > DIGIISOLATOR2_REG_FILTER_CH7_CH8 ) )
    {
        return DIGIISOLATOR2_ERROR;
    }
    uint8_t reg_adr = reg | SPI_WRITE_BIT;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg_adr, 1 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &data_in, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t digiisolator2_spi_read ( digiisolator2_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    if ( reg > DIGIISOLATOR2_REG_FILTER_CH7_CH8 )
    {
        return DIGIISOLATOR2_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void digiisolator2_set_rst_pin ( digiisolator2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

uint8_t digiisolator2_get_int_pin ( digiisolator2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t digiisolator2_get_sync_pin ( digiisolator2_t *ctx )
{
    return digital_in_read( &ctx->sync );
}

err_t digiisolator2_read_inputs ( digiisolator2_t *ctx, uint8_t *data_out )
{
    err_t error_flag = DIGIISOLATOR2_OK;
    uint8_t input_data = 0;
    if ( DIGIISOLATOR2_DRV_SEL_SPI == ctx->drv_sel )
    {
        error_flag = digiisolator2_spi_read ( ctx, DIGIISOLATOR2_REG_INPUT_DATA, &input_data );
    }
    else
    {
        input_data = digiisolator2_get_out1_pin ( ctx );
        input_data |= ( digiisolator2_get_out2_pin ( ctx ) << 1 );
        input_data |= ( digiisolator2_get_out3_pin ( ctx ) << 2 );
        input_data |= ( digiisolator2_get_out4_pin ( ctx ) << 3 );
        input_data |= ( digiisolator2_get_out5_pin ( ctx ) << 4 );
        input_data |= ( digiisolator2_get_out6_pin ( ctx ) << 5 );
        input_data |= ( digiisolator2_get_out8_pin ( ctx ) << 7 );
    }
    if ( ( DIGIISOLATOR2_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = input_data;
    }
    return error_flag;
}

uint8_t digiisolator2_get_out1_pin ( digiisolator2_t *ctx )
{
    return digital_in_read( &ctx->out1 );
}

uint8_t digiisolator2_get_out2_pin ( digiisolator2_t *ctx )
{
    return digital_in_read( &ctx->out2 );
}

uint8_t digiisolator2_get_out3_pin ( digiisolator2_t *ctx )
{
    return digital_in_read( &ctx->out3 );
}

uint8_t digiisolator2_get_out4_pin ( digiisolator2_t *ctx )
{
    return digital_in_read( &ctx->out4 );
}

uint8_t digiisolator2_get_out5_pin ( digiisolator2_t *ctx )
{
    return digital_in_read( &ctx->out5 );
}

uint8_t digiisolator2_get_out6_pin ( digiisolator2_t *ctx )
{
    return digital_in_read( &ctx->out6 );
}

uint8_t digiisolator2_get_out8_pin ( digiisolator2_t *ctx )
{
    return digital_in_read( &ctx->out8 );
}

void digiisolator2_enable_output ( digiisolator2_t *ctx )
{
    digital_out_high( &ctx->en );
}

void digiisolator2_disable_output ( digiisolator2_t *ctx )
{
    digital_out_low( &ctx->en );
}

// ------------------------------------------------------------------------- END
