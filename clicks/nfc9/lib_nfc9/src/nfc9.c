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
 * @file nfc9.c
 * @brief NFC 9 Click Driver.
 */

#include "nfc9.h"
#include "nfc9_rfal.h"
#include "rfal_nfc.h"

/**
 * @brief Discovery parameters.
 * @details Definition of discovery parameters.
 */
static rfalNfcDiscoverParam nfc9_disc_params;

void nfc9_cfg_setup ( nfc9_cfg_t *cfg )
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->rst = HAL_PIN_NC;
    cfg->irq = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t nfc9_init ( nfc9_t *ctx, nfc9_cfg_t *cfg )
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, NFC9_SPI_DUMMY_BYTE ) )
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

    digital_in_init( &ctx->irq, cfg->irq );

    return SPI_MASTER_SUCCESS;
}

err_t nfc9_default_cfg ( nfc9_t *ctx )
{
    err_t error_flag = NFC9_OK;

    nfc9_rfal_set_context( ctx );
    nfc9_reset_device( ctx );

    error_flag = nfc9_check_com( ctx );

    if ( NFC9_OK == error_flag )
    {
        error_flag = nfc9_direct_command( ctx, NFC9_CMD_SET_DEFAULT );
    }

    if ( NFC9_OK == error_flag )
    {
        error_flag = nfc9_direct_command( ctx, NFC9_CMD_CLEAR_FIFO );
    }

    if ( NFC9_OK == error_flag )
    {
        if ( RFAL_ERR_NONE != rfalNfcInitialize( ) )
        {
            error_flag = NFC9_ERROR;
        }
    }

    if ( NFC9_OK == error_flag )
    {
        rfalNfcDefaultDiscParams( &nfc9_disc_params );
        nfc9_disc_params.devLimit = 1;
        nfc9_disc_params.totalDuration = 100;
        nfc9_disc_params.techs2Find = RFAL_NFC_POLL_TECH_A;
        nfc9_disc_params.techs2Bail = RFAL_NFC_TECH_NONE;
    }

    if ( RFAL_ERR_NONE != rfalNfcDiscover( &nfc9_disc_params ) )
    {
        error_flag = NFC9_ERROR;
    }

    return error_flag;
}

err_t nfc9_generic_write ( nfc9_t *ctx, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = NFC9_OK;

    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t nfc9_generic_read ( nfc9_t *ctx, uint8_t *data_out, uint16_t len )
{
    err_t error_flag = NFC9_OK;

    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t nfc9_register_write ( nfc9_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tx_buf[ 2 ] = { 0 };

    tx_buf[ 0 ] = NFC9_SPI_WRITE_MODE | ( reg & NFC9_REG_ADDR_MASK );
    tx_buf[ 1 ] = data_in;

    return nfc9_generic_write( ctx, tx_buf, 2 );
}

err_t nfc9_register_read ( nfc9_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t cmd = NFC9_SPI_READ_MODE | ( reg & NFC9_REG_ADDR_MASK );
    err_t error_flag = NFC9_OK;

    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t nfc9_register_set_bits ( nfc9_t *ctx, uint8_t reg, uint8_t mask )
{
    uint8_t reg_val = 0;

    if ( NFC9_OK != nfc9_register_read( ctx, reg, &reg_val ) )
    {
        return NFC9_ERROR;
    }

    reg_val |= mask;
    return nfc9_register_write( ctx, reg, reg_val );
}

err_t nfc9_register_clear_bits ( nfc9_t *ctx, uint8_t reg, uint8_t mask )
{
    uint8_t reg_val = 0;

    if ( NFC9_OK != nfc9_register_read( ctx, reg, &reg_val ) )
    {
        return NFC9_ERROR;
    }

    reg_val &= ( uint8_t ) ~mask;
    return nfc9_register_write( ctx, reg, reg_val );
}

err_t nfc9_direct_command ( nfc9_t *ctx, uint8_t command )
{
    uint8_t cmd = NFC9_SPI_CMD_MODE | ( command & NFC9_CMD_MASK );

    return nfc9_generic_write( ctx, &cmd, 1 );
}

err_t nfc9_fifo_write ( nfc9_t *ctx, uint8_t *data_in, uint16_t len )
{
    uint8_t cmd = NFC9_SPI_FIFO_WRITE;
    err_t error_flag = NFC9_OK;

    if ( len > NFC9_FIFO_SIZE )
    {
        return NFC9_ERROR;
    }

    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t nfc9_fifo_read ( nfc9_t *ctx, uint8_t *data_out, uint16_t len )
{
    uint8_t cmd = NFC9_SPI_FIFO_READ;
    err_t error_flag = NFC9_OK;

    if ( len > NFC9_FIFO_SIZE )
    {
        return NFC9_ERROR;
    }

    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t nfc9_check_com ( nfc9_t *ctx )
{
    uint8_t ic_identity = 0;

    if ( NFC9_OK != nfc9_register_read( ctx, NFC9_REG_IC_IDENTITY, &ic_identity ) )
    {
        return NFC9_ERROR;
    }

    if ( NFC9_IC_IDENTITY_TYPE != ( ic_identity & NFC9_IC_IDENTITY_TYPE_MASK ) )
    {
        return NFC9_ERROR;
    }

    return NFC9_OK;
}

void nfc9_reset_device ( nfc9_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_10ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );
}

uint8_t nfc9_get_irq_pin ( nfc9_t *ctx )
{
    return digital_in_read( &ctx->irq );
}

err_t nfc9_read_tag ( nfc9_t *ctx, nfc9_tag_t *tag )
{
    err_t error_flag = NFC9_OK;
    rfalNfcDevice *active_dev;

    if ( NULL == tag )
    {
        return NFC9_ERROR;
    }

    rfalNfcWorker( );

    if ( rfalNfcIsDevActivated( rfalNfcGetState( ) ) )
    {
        if ( RFAL_ERR_NONE != rfalNfcGetActiveDevice( &active_dev ) )
        {
            error_flag = NFC9_ERROR;
        }

        if ( NFC9_OK == error_flag )
        {
            if ( RFAL_NFC_LISTEN_TYPE_NFCA == active_dev->type )
            {
                tag->uid = active_dev->nfcid;
                tag->uid_len = active_dev->nfcidLen;
                tag->atqa = ( ( uint16_t ) active_dev->dev.nfca.sensRes.platformInfo << 8 ) | 
                                           active_dev->dev.nfca.sensRes.anticollisionInfo;
                tag->sak = active_dev->dev.nfca.selRes.sak;
            }
            else
            {
                error_flag = NFC9_ERROR;
            }
        }

        if ( RFAL_ERR_NONE != rfalNfcDeactivate( RFAL_NFC_DEACTIVATE_IDLE ) )
        {
            error_flag = NFC9_ERROR;
        }

        if ( RFAL_ERR_NONE != rfalNfcDiscover( &nfc9_disc_params ) )
        {
            error_flag = NFC9_ERROR;
        }
    }
    else if ( RFAL_NFC_STATE_IDLE == rfalNfcGetState( ) )
    {
        if ( RFAL_ERR_NONE != rfalNfcDiscover( &nfc9_disc_params ) )
        {
            error_flag = NFC9_ERROR;
        }
    }
    else
    {
        error_flag = NFC9_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
