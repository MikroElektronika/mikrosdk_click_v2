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
 * @file ismrx3.c
 * @brief ISM RX 3 Click Driver.
 */

#include "ismrx3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Configuration data.
 * @details Data configuration to send to device for configuration for selected
 * combination of modulation,frequency, [deviation,] data rate.
 */
const uint8_t ASK_F315_DR2[ ] = { 0x46,0x26,0x08,0x24,0xA7,0x09,0x0A,0x1F,
                                  0x00,0x13,0xAC,0xCD,0x0F,0xAA,0xAA, 0x97 };

const uint8_t ASK_F315_DR1[ ] = { 0x44,0x26,0x0B,0x14,0x91,0x10,0x05,0x1F,
                                  0x00,0x13,0xAC,0xCD,0x0F,0x00,0xAA,0xAA, 0x97 };

const uint8_t ASK_F433p92_DR5[ ] = { 0x45,0x26,0x08,0x1A,0xAA,0x0D,0x0A,0x1F,
                                     0x00,0x1B,0x1B,0x85,0x0F,0xAA,0xAA, 0x95 };

const uint8_t ASK_F433p92_DR1[ ] = { 0x44,0x26,0x0B,0x14,0x91,0x10,0x05,0x1F,
                                     0x00,0x1B,0x1B,0x85,0x0F,0xAA,0xAA, 0x95 };

const uint8_t ASK_F868p3_DR10[ ] = { 0x45,0x26,0x00,0x1A,0xB3,0x0D,0x0B,0x1F,
                                     0x00,0x36,0x3E,0x66,0x0F,0xAA,0xAA, 0x93 };

const uint8_t ASK_F868p3_DR2[ ] = { 0x44,0x26,0x03,0x14,0x99,0x10,0x07,0x1F,
                                    0x00,0x36,0x3E,0x66,0x0F,0xAA,0xAA, 0x93 };

const uint8_t FSK_F315_FD_40_DR2[ ] = { 0x44,0x26,0x18,0x24,0x00,0x00,0x00,0x1E,
                                         0x00,0x13,0xAC,0xCD,0x0F,0xAA,0xAA, 0x97 };

const uint8_t FSK_F315_FD_5_DR2[ ] = { 0x61,0x26,0x1B,0x0C,0x00,0x00,0x00,0x1E,
                                        0x00,0x13,0xAC,0xCD,0x0F,0xAA,0xAA, 0x97 };

const uint8_t FSK_F433p92_FD_40_DR5[ ] = { 0x44,0x26,0x18,0x1A,0x00,0x00,0x00,0x1E,
                                            0x00,0x1B,0x1B,0x85,0x0F,0xAA,0xAA, 0x95 };

const uint8_t FSK_F433p92_FD_5_DR5[ ] = { 0x61,0x26,0x1B,0x02,0x00,0x00,0x00,0x1E,
                                           0x00,0x1B,0x1B,0x85,0x0F,0xAA,0xAA, 0x95 };

const uint8_t FSK_F868p3_FD_40_DR50[ ] = { 0x44,0x26,0x18,0x24,0x00,0x00,0x00,0x1E,
                                         0x00,0x13,0xAC,0xCD,0x0F,0xAA,0xAA, 0x93 };

const uint8_t FSK_F868p3_FD_5_DR5[ ] = { 0x61,0x26,0x1B,0x0C,0x00,0x00,0x00,0x1E,
                                        0x00,0x13,0xAC,0xCD,0x0F,0xAA,0xAA, 0x93 };

const uint8_t FSK_F868p3_FD_80_DR100[ ] = { 0x44,0x26,0x18,0x1A,0x00,0x00,0x00,0x1E,
                                            0x00,0x1B,0x1B,0x85,0x0F,0xAA,0xAA, 0x93 };

const uint8_t FSK_F868p3_FD_10_DR10[ ] = { 0x61,0x26,0x1B,0x02,0x00,0x00,0x00,0x1E,
                                           0x00,0x1B,0x1B,0x85,0x0F,0xAA,0xAA, 0x93 };

/**
 * @brief FSK configuration setter.
 * @details This function configures device for FSK modulation.
 * @param[in] ctx : Click context object.
 * See #ismrx3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t ismrx3_fsk_modulation ( ismrx3_t *ctx );

/**
 * @brief ASK configuration setter.
 * @details This function configures device for ASK modulation.
 * @param[in] ctx : Click context object.
 * See #ismrx3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t ismrx3_ask_modulation ( ismrx3_t *ctx );

/**
 * @brief Configuration setter.
 * @details This function configures device with predefined configuration array.
 * @param[in] ctx : Click context object.
 * See #ismrx3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static void ismrx3_configure_device ( ismrx3_t *ctx, const uint8_t *config_array );

void ismrx3_cfg_setup ( ismrx3_cfg_t *cfg )
{
    cfg->sck        = HAL_PIN_NC;
    cfg->miso       = HAL_PIN_NC;
    cfg->mosi       = HAL_PIN_NC;
    cfg->cs         = HAL_PIN_NC;
    cfg->dat        = HAL_PIN_NC;
    cfg->pdn        = HAL_PIN_NC;
    cfg->sw         = HAL_PIN_NC;
    cfg->int_pin    = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t ismrx3_init ( ismrx3_t *ctx, ismrx3_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

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

    digital_out_init( &ctx->pdn, cfg->pdn );
    digital_out_init( &ctx->sw, cfg->sw );

    digital_in_init( &ctx->dat, cfg->dat );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t ismrx3_default_cfg ( ismrx3_t *ctx )
{
    err_t ret_val = ISMRX3_OK;
    //Enable oscilator
    ret_val |= ismrx3_generic_write( ctx, ISMRX3_STATE_CTRL_1, 0x04 );
    //Select configuration
    switch( ctx->modulation )
    {
        case ISMRX3_MODULATION_ASK:
        {
            ret_val |= ismrx3_ask_modulation( ctx );
            break;
        }
        case ISMRX3_MODULATION_FSK:
        {
            ret_val |= ismrx3_fsk_modulation( ctx );
            break;
        }
        default:
        {
            ret_val |= ISMRX3_ERROR;
            break;
        }
    }
    //Enable clock output
    ret_val |= ismrx3_generic_write( ctx, ISMRX3_CDR_CFG, 0x01 );
    //Enable oscilator and receiver
    ret_val |= ismrx3_generic_write( ctx, ISMRX3_STATE_CTRL_1, 0x05 );

    return ret_val;
}

err_t ismrx3_generic_write ( ismrx3_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg & 0x7F;
    tx_buf[ 1 ] = data_in;

    digital_out_low( &ctx->sw );
    spi_master_select_device( ctx->chip_select );
    Delay_1us();
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    Delay_1us();
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t ismrx3_generic_read ( ismrx3_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg | 0x80;
    tx_buf[ 1 ] = DUMMY;

    digital_out_low( &ctx->sw );
    spi_master_select_device( ctx->chip_select );
    Delay_1us();
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    digital_out_high( &ctx->sw );
    error_flag |= spi_master_read( &ctx->spi, data_out, 1 );
    Delay_1us();
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void ismrx3_reset( ismrx3_t *ctx )
{
    digital_out_high( &ctx->pdn );
    Delay_1ms( );
    digital_out_low( &ctx->pdn );
    Delay_1ms( );
}

uint8_t ismrx3_get_clk( ismrx3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t ismrx3_get_data( ismrx3_t *ctx )
{
    return digital_in_read( &ctx->dat );
}

static err_t ismrx3_fsk_modulation ( ismrx3_t *ctx )
{
    if ( ISMRX3_FREQUENCY_MHZ_315 == ctx->reference_freq )
    {
        if ( ( ISMRX3_DEVIATION_KHZ_40 == ctx->freq_deviation ) && ( ISMRX3_DATA_RATE_KBPS_2 == ctx->data_rate ) )
        {
            ismrx3_configure_device( ctx, FSK_F315_FD_40_DR2 );
            return ISMRX3_OK;
        }
        else if ( ( ISMRX3_DEVIATION_KHZ_5 == ctx->freq_deviation ) && ( ISMRX3_DATA_RATE_KBPS_2 == ctx->data_rate ) )
        {
            ismrx3_configure_device( ctx, FSK_F315_FD_5_DR2 );
            return ISMRX3_OK;
        }
        else
        {
            return ISMRX3_ERROR;
        }
    }
    else if ( ISMRX3_FREQUENCY_MHZ_433p92 == ctx->reference_freq )
    {
        if ( ( ISMRX3_DEVIATION_KHZ_40 == ctx->freq_deviation ) && ( ISMRX3_DATA_RATE_KBPS_5 == ctx->data_rate ) )
        {
            ismrx3_configure_device( ctx, FSK_F433p92_FD_40_DR5 );
            return ISMRX3_OK;
        }
        else if ( ( ISMRX3_DEVIATION_KHZ_5 == ctx->freq_deviation ) && ( ISMRX3_DATA_RATE_KBPS_5 == ctx->data_rate ) )
        {
            ismrx3_configure_device( ctx, FSK_F433p92_FD_5_DR5 );
            return ISMRX3_OK;
        }
        else
        {
            return ISMRX3_ERROR;
        }
    }
    else if ( ISMRX3_FREQUENCY_MHZ_868p3 == ctx->reference_freq )
    {
        if ( ( ISMRX3_DEVIATION_KHZ_40 == ctx->freq_deviation ) && ( ISMRX3_DATA_RATE_KBPS_50 == ctx->data_rate ) )
        {
            ismrx3_configure_device( ctx, FSK_F868p3_FD_40_DR50 );
            return ISMRX3_OK;
        }
        else if ( ( ISMRX3_DEVIATION_KHZ_5 == ctx->freq_deviation ) && ( ISMRX3_DATA_RATE_KBPS_5 == ctx->data_rate ) )
        {
            ismrx3_configure_device( ctx, FSK_F868p3_FD_5_DR5 );
            return ISMRX3_OK;
        }
        else if ( ( ISMRX3_DEVIATION_KHZ_80 == ctx->freq_deviation ) && ( ISMRX3_DATA_RATE_KBPS_100 == ctx->data_rate ) )
        {
            ismrx3_configure_device( ctx, FSK_F868p3_FD_80_DR100 );
            return ISMRX3_OK;
        }
        else if ( ( ISMRX3_DEVIATION_KHZ_10 == ctx->freq_deviation ) && ( ISMRX3_DATA_RATE_KBPS_10 == ctx->data_rate ) )
        {
            ismrx3_configure_device( ctx, FSK_F868p3_FD_10_DR10 );
            return ISMRX3_OK;
        }
        else
        {
            return ISMRX3_ERROR;
        }
    }
    else
    {
        return ISMRX3_ERROR;
    }
}

static err_t ismrx3_ask_modulation ( ismrx3_t *ctx )
{
    if ( ISMRX3_FREQUENCY_MHZ_315 == ctx->reference_freq )
    {
        if ( ISMRX3_DATA_RATE_KBPS_2 == ctx->data_rate )
        {
            ismrx3_configure_device( ctx, ASK_F315_DR2 );
            return ISMRX3_OK;
        }
        else if ( ISMRX3_DATA_RATE_KBPS_1 == ctx->data_rate )
        {
            ismrx3_configure_device( ctx, ASK_F315_DR1 );
            return ISMRX3_OK;
        }
        else
        {
            return ISMRX3_ERROR;
        }
    }
    else if ( ISMRX3_FREQUENCY_MHZ_433p92 == ctx->reference_freq )
    {
        if ( ISMRX3_DATA_RATE_KBPS_5 == ctx->data_rate )
        {
            ismrx3_configure_device( ctx, ASK_F433p92_DR5 );
            return ISMRX3_OK;
        }
        else if ( ISMRX3_DATA_RATE_KBPS_1 == ctx->data_rate )
        {
            ismrx3_configure_device( ctx, ASK_F433p92_DR1 );
            return ISMRX3_OK;
        }
        else
        {
            return ISMRX3_ERROR;
        }
    }
    else if ( ISMRX3_FREQUENCY_MHZ_868p3 == ctx->reference_freq )
    {
        if ( ISMRX3_DATA_RATE_KBPS_10 == ctx->data_rate )
        {
            ismrx3_configure_device( ctx, ASK_F868p3_DR10 );
            return ISMRX3_OK;
        }
        else if ( ISMRX3_DATA_RATE_KBPS_2 == ctx->data_rate )
        {
            ismrx3_configure_device( ctx, ASK_F868p3_DR2 );
            return ISMRX3_OK;
        }
        else
        {
            return ISMRX3_ERROR;
        }
    }
    else
    {
        return ISMRX3_ERROR;
    }
}

static void ismrx3_configure_device ( ismrx3_t *ctx, const uint8_t *config_array )
{
    uint8_t reg;
    for ( reg = 0; reg < 0x0F; reg++ )
    {
        ismrx3_generic_write( ctx, reg, config_array[ reg ] );
    }
    ismrx3_generic_write( ctx, 0x19, config_array[ reg ] );
}

// ------------------------------------------------------------------------- END
