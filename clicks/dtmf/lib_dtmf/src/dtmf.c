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
 * @file dtmf.c
 * @brief DTMF Click Driver.
 */

#include "dtmf.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void dtmf_cfg_setup ( dtmf_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rdn  = HAL_PIN_NC;
    cfg->hsw  = HAL_PIN_NC;
    cfg->irq  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t dtmf_init ( dtmf_t *ctx, dtmf_cfg_t *cfg ) 
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

    digital_out_init( &ctx->hsw, cfg->hsw );
    digital_out_high ( &ctx->hsw );

    digital_in_init( &ctx->rdn, cfg->rdn );
    digital_in_init( &ctx->irq, cfg->irq );

    return SPI_MASTER_SUCCESS;
}

err_t dtmf_general_reset ( dtmf_t *ctx )
{
    uint8_t cmd = DTMF_CMD_GENERAL_RESET;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dtmf_set_control ( dtmf_t *ctx, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = DTMF_CMD_GENERAL_CONTROL;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    ctx->control = data_in;
    return error_flag;
}

err_t dtmf_set_transmit_mode ( dtmf_t *ctx, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = DTMF_CMD_TRANSMIT_MODE;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    ctx->tx_mode = data_in;
    return error_flag;
}

err_t dtmf_set_receive_mode ( dtmf_t *ctx, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = DTMF_CMD_RECEIVE_MODE;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    ctx->rx_mode = data_in;
    return error_flag;
}

err_t dtmf_transmit_data ( dtmf_t *ctx, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = DTMF_CMD_TRANSMIT_DATA;
    data_buf[ 1 ] = data_in;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dtmf_receive_data ( dtmf_t *ctx, uint8_t *data_out )
{
    uint8_t cmd = DTMF_CMD_RECEIVE_DATA;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dtmf_get_status ( dtmf_t *ctx, uint16_t *data_out )
{
    uint8_t cmd = DTMF_CMD_STATUS;
    uint8_t data_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    ctx->status = *data_out;
    return error_flag;
}

err_t dtmf_set_programming ( dtmf_t *ctx, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = DTMF_CMD_PROGRAMMING;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void dtmf_set_hsw_pin ( dtmf_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->hsw, state );
}

void dtmf_hook_off ( dtmf_t *ctx )
{
    digital_out_low ( &ctx->hsw );
}

void dtmf_hook_on ( dtmf_t *ctx )
{
    digital_out_high ( &ctx->hsw );
}

uint8_t dtmf_get_rdn_pin ( dtmf_t *ctx )
{
    return digital_in_read ( &ctx->rdn );
}

uint8_t dtmf_get_irq_pin ( dtmf_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

uint8_t dtmf_tx_ready ( dtmf_t *ctx )
{
    uint16_t status = 0;
    dtmf_get_status ( ctx, &status );
    return ( DTMF_STATUS_TX_READY == ( status & DTMF_STATUS_TX_READY ) ); 
}

uint8_t dtmf_rx_ready ( dtmf_t *ctx )
{
    uint16_t status = 0;
    dtmf_get_status ( ctx, &status );
    return ( DTMF_STATUS_RX_READY == ( status & DTMF_STATUS_RX_READY ) );
}

uint8_t dtmf_call_progress ( dtmf_t *ctx )
{
    uint16_t status = 0;
    dtmf_get_status ( ctx, &status );
    return ( DTMF_STATUS_ENERGY_RX_CP == ( status & DTMF_STATUS_ENERGY_RX_CP ) );
}

uint8_t dtmf_unscram_1s_det ( dtmf_t *ctx )
{
    uint16_t status = 0;
    dtmf_get_status ( ctx, &status );
    return ( ( DTMF_STATUS_ENERGY_RX_CP | DTMF_STATUS_CONT_1S ) == 
             ( status & ( DTMF_STATUS_ENERGY_RX_CP | DTMF_STATUS_CONT_0S | DTMF_STATUS_CONT_1S ) ) );
}

err_t dtmf_clear_interrupts ( dtmf_t *ctx )
{
    err_t error_flag = DTMF_OK;
    uint32_t timeout = 0;
    uint16_t status = 0;
    while ( !dtmf_get_irq_pin ( ctx ) && ( DTMF_OK == error_flag ) )
    {
        error_flag |= dtmf_get_status ( ctx, &status );
        Delay_1ms ( );
        if ( ++timeout > DTMF_TIMEOUT_CLEAR_IRQ )
        {
            error_flag |= DTMF_TIMEOUT;
        }
    }
    return error_flag;
}

err_t dtmf_dial ( dtmf_t *ctx, uint8_t *dial_num )
{
    if ( strlen ( dial_num ) > DTMF_DIAL_NUMBER_MAX_LEN )
    {
        return DTMF_ERROR;
    }
    uint8_t digit_cnt = 0;
    err_t error_flag = DTMF_OK;
    ctx->tx_mode &= DTMF_TX_LEVEL_MASK; // No change in tx level setting
    ctx->tx_mode |= DTMF_TX_MODE_DTMF_TONES; // Select DTMF/Tones
    for ( digit_cnt = 0; dial_num[ digit_cnt ]; digit_cnt++ )
    {
        switch ( dial_num[ digit_cnt ] )
        {
            case 'A': case 'a':
            {
                ctx->tx_mode |= DTMF_TX_TONE_A;
                break;
            }
            case 'B': case 'b':
            {
                ctx->tx_mode |= DTMF_TX_TONE_B;
                break;
            }
            case 'C': case 'c':
            {
                ctx->tx_mode |= DTMF_TX_TONE_C;
                break;
            }
            case 'D': case 'd':
            {
                ctx->tx_mode |= DTMF_TX_TONE_D;
                break;
            }
            case '*':
            {
                ctx->tx_mode |= DTMF_TX_TONE_STAR;
                break;
            }
            case '#':
            {
                ctx->tx_mode |= DTMF_TX_TONE_HASH;
                break;
            }
            case '0':
            {
                ctx->tx_mode |= DTMF_TX_TONE_0;
                break;
            }
            case '1':
            {
                ctx->tx_mode |= DTMF_TX_TONE_1;
                break;
            }
            case '2':
            {
                ctx->tx_mode |= DTMF_TX_TONE_2;
                break;
            }
            case '3':
            {
                ctx->tx_mode |= DTMF_TX_TONE_3;
                break;
            }
            case '4':
            {
                ctx->tx_mode |= DTMF_TX_TONE_4;
                break;
            }
            case '5':
            {
                ctx->tx_mode |= DTMF_TX_TONE_5;
                break;
            }
            case '6':
            {
                ctx->tx_mode |= DTMF_TX_TONE_6;
                break;
            }
            case '7':
            {
                ctx->tx_mode |= DTMF_TX_TONE_7;
                break;
            }
            case '8':
            {
                ctx->tx_mode |= DTMF_TX_TONE_8;
                break;
            }
            case '9':
            {
                ctx->tx_mode |= DTMF_TX_TONE_9;
                break;
            }
            default:
            {
                return DTMF_ERROR;
            }
        }
        error_flag |= dtmf_set_transmit_mode ( ctx, ctx->tx_mode );
        Delay_100ms ( );
        ctx->tx_mode ^= ( ctx->tx_mode & DTMF_TX_TONE_MASK ); // Turn tone OFF
        error_flag |= dtmf_set_transmit_mode ( ctx, ctx->tx_mode );
        Delay_100ms ( );
    }
    return error_flag;
}

err_t dtmf_send_message ( dtmf_t *ctx, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = DTMF_OK;
    uint32_t timeout = 0;
    uint8_t data_cnt = 0;
    uint16_t tx_mode = ctx->tx_mode;
    ctx->tx_mode &= DTMF_TX_LEVEL_MASK; // No change in tx level setting
    ctx->tx_mode |= ( DTMF_TX_MODE_V23_FSK_1200 | DTMF_TX_DATA_FORMAT_SS_NO_PAR | DTMF_TX_DATA_STOP_8_1 );
    error_flag |= dtmf_set_transmit_mode ( ctx, ctx->tx_mode );
    Delay_100ms ( ); 
    while ( ( data_cnt < len ) && ( DTMF_OK == error_flag ) )
    {
        if ( dtmf_tx_ready ( ctx ) )
        {
            error_flag |= dtmf_transmit_data ( ctx, data_in[ data_cnt++ ] );
            Delay_100ms ( );
        }
        else
        {
            Delay_1ms ( );
            if ( ++timeout > DTMF_TIMEOUT_TX_READY )
            {
                error_flag |= DTMF_TIMEOUT;
            }
        }
    }
    Delay_100ms ( ); 
    error_flag |= dtmf_set_transmit_mode ( ctx, tx_mode );
    return error_flag;
}

err_t dtmf_handshake_init ( dtmf_t *ctx )
{
    err_t error_flag = DTMF_OK;

    error_flag |= dtmf_general_reset ( ctx );
    error_flag |= dtmf_set_control ( ctx, DTMF_CONTROL_PWR | DTMF_CONTROL_RST );
    Delay_100ms ( );
    error_flag |= dtmf_set_control ( ctx, DTMF_CONTROL_PWR | DTMF_CONTROL_IRQN_EN | 
                                          DTMF_CONTROL_IRQ_ENERGY_RX_CP );
    Delay_100ms ( );
    error_flag |= dtmf_set_receive_mode ( ctx, DTMF_RX_LEVEL_0_DB );
    error_flag |= dtmf_set_transmit_mode ( ctx, DTMF_TX_LEVEL_0_DB );
    Delay_100ms ( );
    dtmf_clear_interrupts ( ctx );

    return error_flag;
}

// ------------------------------------------------------------------------- END
