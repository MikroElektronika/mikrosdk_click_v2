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
 * @file dac17.c
 * @brief DAC 17 Click Driver.
 */

#include "dac17.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void dac17_cfg_setup ( dac17_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->pd = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t dac17_init ( dac17_t *ctx, dac17_cfg_t *cfg ) 
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
    digital_out_init( &ctx->pd, cfg->pd );

    dac17_set_rst_pin( ctx, DAC17_PIN_STATE_HIGH );
    dac17_set_pd_pin( ctx, DAC17_PIN_STATE_HIGH );

    return SPI_MASTER_SUCCESS;
}

err_t dac17_default_cfg ( dac17_t *ctx ) 
{
    err_t error_flag = DAC17_OK;

    dac17_hw_reset( ctx );
    error_flag |= dac17_set_all_dac_output( ctx, 0 );

    return error_flag;
}

err_t dac17_generic_write ( dac17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void dac17_set_rst_pin ( dac17_t *ctx, uint8_t pin_state )
{
    if ( DAC17_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void dac17_set_pd_pin ( dac17_t *ctx, uint8_t pin_state )
{
    if ( DAC17_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->pd );
    }
    else
    {
        digital_out_low( &ctx->pd );
    }
}

void dac17_hw_reset ( dac17_t *ctx )
{
    dac17_set_rst_pin( ctx, DAC17_PIN_STATE_LOW );
    Delay_10ms();
    dac17_set_rst_pin( ctx, DAC17_PIN_STATE_HIGH );
}

err_t dac17_send_command ( dac17_t *ctx, uint8_t command, uint8_t ch_sel, uint16_t data_in )
{
    uint8_t tmp_data[ 3 ] = { 0 };
    uint16_t dac_data = 0;

    dac_data = ( data_in & DAC17_12BIT_VALUE ) << 4;
    tmp_data[ 0 ] = ch_sel << 1 | command;
    tmp_data[ 1 ] = ( uint8_t ) ( dac_data >> 8 );
    tmp_data[ 2 ] = ( uint8_t ) dac_data;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tmp_data, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dac17_set_dac_output ( dac17_t *ctx, uint8_t ch_sel, uint16_t dac_data )
{
    err_t error_flag = DAC17_OK;

    error_flag |= dac17_send_command( ctx, DAC17_CMD_WRITE_BUFER_AND_LOAD_ALL, ch_sel, dac_data );

    return error_flag;
}

err_t dac17_set_all_dac_output ( dac17_t *ctx, uint16_t dac_data )
{
    err_t error_flag = DAC17_OK;

    error_flag |= dac17_send_command( ctx, DAC17_CMD_WRITE_LOAD_BUFF, DAC17_LOAD_AND_WRITE_CH_ALL, dac_data );

    return error_flag;
}

// ------------------------------------------------------------------------- END
