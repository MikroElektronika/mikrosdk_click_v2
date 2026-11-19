/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file rcpulse.c
 * @brief RC Pulse Click Driver.
 */

#include "rcpulse.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void rcpulse_cfg_setup ( rcpulse_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->cl   = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t rcpulse_init ( rcpulse_t *ctx, rcpulse_cfg_t *cfg ) 
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

    digital_out_init( &ctx->cl, cfg->cl );
    digital_out_init( &ctx->pwm, cfg->pwm );
    digital_in_init( &ctx->rdy, cfg->rdy );

    return SPI_MASTER_SUCCESS;
}

err_t rcpulse_default_cfg ( rcpulse_t *ctx ) 
{
    err_t error_flag = RCPULSE_OK;
    
    /* Set clear pin and trigger to inactive state */
    digital_out_high( &ctx->cl );
    digital_out_high( &ctx->pwm );
    Delay_1ms( );

    /* Set default wiper position to half the range */
    error_flag |= rcpulse_set_wiper( ctx, RCPULSE_CHANNEL_1, RCPULSE_WIPER_MIDSCALE );
    error_flag |= rcpulse_set_wiper( ctx, RCPULSE_CHANNEL_2, RCPULSE_WIPER_MIDSCALE );

    return error_flag;
}

err_t rcpulse_write_data ( rcpulse_t *ctx, uint8_t cmd, uint8_t addr, uint16_t data_in ) 
{
    /* Write frame: cs_low | command(4bits) + addr(4bits) | data_MSB | data_LSB | cs_high */
    err_t error_flag = RCPULSE_OK;
    uint8_t data_buf[ RCPULSE_DATA_WORD_LEN ] = { 0 };

    data_buf[ 0 ] = ( uint8_t ) ( ( ( cmd & RCPULSE_CMD_MASK ) << 4 ) | ( addr & RCPULSE_ADDR_MASK ) );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & RCPULSE_DATA_BYTE_MASK );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & RCPULSE_DATA_BYTE_MASK );

    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, RCPULSE_DATA_WORD_LEN );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t rcpulse_read_data ( rcpulse_t *ctx, uint8_t cmd, uint8_t addr, uint16_t *data_out ) 
{
    /* Read frame: cs_low | command(4bits) + addr(4bits) | dummy | dummy | cs_high */
    err_t error_flag = RCPULSE_OK;
    uint8_t data_buf[ RCPULSE_DATA_WORD_LEN ] = { 0 };

    if ( NULL == data_out ) 
    {
        return RCPULSE_ERROR;
    }

    data_buf[ 0 ] = ( uint8_t ) ( ( ( cmd & RCPULSE_CMD_MASK ) << 4 ) | ( addr & RCPULSE_ADDR_MASK ) );
    data_buf[ 1 ] = DUMMY;
    data_buf[ 2 ] = DUMMY;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, RCPULSE_DATA_WORD_LEN );
    spi_master_deselect_device( ctx->chip_select );

    /* Second frame clocks the data out on MISO, MSB first. */
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, RCPULSE_DATA_WORD_LEN );
    spi_master_deselect_device( ctx->chip_select );

    *data_out = ( uint16_t ) ( ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ] );

    return error_flag;
}

err_t rcpulse_set_wiper ( rcpulse_t *ctx, uint8_t channel, uint16_t wiper ) 
{
    err_t error_flag = RCPULSE_OK;

    /* Check against valid ranges */
    if ( ( RCPULSE_CHANNEL_2 < channel ) || ( RCPULSE_WIPER_MAX < wiper ) ) 
    {
        return RCPULSE_ERROR;
    }

    /* Command 0x0B writes contents of Serial Register Data to the RDAC */
    error_flag |= rcpulse_write_data( ctx, RCPULSE_CMD_WRITE_RDAC, channel, wiper );

    return error_flag;
}

err_t rcpulse_get_wiper ( rcpulse_t *ctx, uint8_t channel, uint16_t *wiper ) 
{
    err_t error_flag = RCPULSE_OK;
    uint16_t reg_data = 0;

    /* Check against valid ranges */
    if ( ( RCPULSE_CHANNEL_2 < channel ) || ( NULL == wiper ) )
    {
        return RCPULSE_ERROR;
    }

    /* Command 0x0A reads RDAC wiper setting in the next frame */
    error_flag |= rcpulse_read_data( ctx, RCPULSE_CMD_READ_RDAC, channel, &reg_data );

    *wiper = reg_data & RCPULSE_WIPER_MAX;

    return error_flag;
}

void rcpulse_trigger ( rcpulse_t *ctx )
{
    digital_out_low( &ctx->pwm );
    Delay_10us( );
    digital_out_high( &ctx->pwm );
}

void rcpulse_clear ( rcpulse_t *ctx ) 
{
    digital_out_low( &ctx->cl );
    Delay_10us( );
    digital_out_high( &ctx->cl );
}

uint8_t rcpulse_get_ready ( rcpulse_t *ctx ) 
{
    return digital_in_read( &ctx->rdy );
}

// ------------------------------------------------------------------------- END
