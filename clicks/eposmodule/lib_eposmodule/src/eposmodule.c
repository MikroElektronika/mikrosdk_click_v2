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
 * @file eposmodule.c
 * @brief EPOS Module Click Driver.
 */

#include "eposmodule.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void eposmodule_cfg_setup ( eposmodule_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->irq  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t eposmodule_init ( eposmodule_t *ctx, eposmodule_cfg_t *cfg ) 
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

    digital_in_init( &ctx->irq, cfg->irq );

    return SPI_MASTER_SUCCESS;
}

err_t eposmodule_general_reset ( eposmodule_t *ctx )
{
    uint8_t cmd = EPOSMODULE_CMD_GENERAL_RESET;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t eposmodule_set_control ( eposmodule_t *ctx, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = EPOSMODULE_CMD_GENERAL_CONTROL;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    ctx->control = data_in;
    return error_flag;
}

err_t eposmodule_set_transmit_mode ( eposmodule_t *ctx, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = EPOSMODULE_CMD_TRANSMIT_MODE;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    ctx->tx_mode = data_in;
    return error_flag;
}

err_t eposmodule_set_receive_mode ( eposmodule_t *ctx, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = EPOSMODULE_CMD_RECEIVE_MODE;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    ctx->rx_mode = data_in;
    return error_flag;
}

err_t eposmodule_transmit_data ( eposmodule_t *ctx, uint16_t data_in )
{
    err_t error_flag = EPOSMODULE_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = EPOSMODULE_CMD_TRANSMIT_DATA;
    if ( ctx->control & EPOSMODULE_CONTROL_2C )
    {
        data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 3 );
        spi_master_deselect_device( ctx->chip_select );
    }
    else
    {
        data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
        spi_master_deselect_device( ctx->chip_select );
    }
    return error_flag;
}

err_t eposmodule_receive_data ( eposmodule_t *ctx, uint8_t *data_out )
{
    err_t error_flag = EPOSMODULE_OK;
    uint8_t cmd = EPOSMODULE_CMD_RECEIVE_DATA;
    if ( ctx->control & EPOSMODULE_CONTROL_2C )
    {
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, 2 );
        spi_master_deselect_device( ctx->chip_select );
    }
    else
    {
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, 1 );
        spi_master_deselect_device( ctx->chip_select );
    }
    return error_flag;
}

err_t eposmodule_get_status ( eposmodule_t *ctx, uint16_t *data_out )
{
    uint8_t cmd = EPOSMODULE_CMD_STATUS;
    uint8_t data_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    ctx->status = *data_out;
    return error_flag;
}

err_t eposmodule_set_programming ( eposmodule_t *ctx, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = EPOSMODULE_CMD_PROGRAMMING;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t eposmodule_hook_off ( eposmodule_t *ctx )
{
    ctx->control |= EPOSMODULE_CONTROL_RLY_DRV;
    return eposmodule_set_control ( ctx, ctx->control );
}

err_t eposmodule_hook_on ( eposmodule_t *ctx )
{
    ctx->control &= ~EPOSMODULE_CONTROL_RLY_DRV;
    return eposmodule_set_control ( ctx, ctx->control );
}

uint8_t eposmodule_get_irq_pin ( eposmodule_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

uint8_t eposmodule_ring_detect ( eposmodule_t *ctx )
{
    uint16_t status = 0;
    eposmodule_get_status ( ctx, &status );
    return ( EPOSMODULE_STATUS_RING == ( status & EPOSMODULE_STATUS_RING ) ); 
}

uint8_t eposmodule_tx_ready ( eposmodule_t *ctx )
{
    uint16_t status = 0;
    eposmodule_get_status ( ctx, &status );
    return ( EPOSMODULE_STATUS_TX_READY == ( status & EPOSMODULE_STATUS_TX_READY ) ); 
}

uint8_t eposmodule_rx_ready ( eposmodule_t *ctx )
{
    uint16_t status = 0;
    eposmodule_get_status ( ctx, &status );
    return ( EPOSMODULE_STATUS_RX_READY == ( status & EPOSMODULE_STATUS_RX_READY ) );
}

uint8_t eposmodule_call_progress ( eposmodule_t *ctx )
{
    uint16_t status = 0;
    eposmodule_get_status ( ctx, &status );
    return ( EPOSMODULE_STATUS_ENERGY_RX_CP == ( status & EPOSMODULE_STATUS_ENERGY_RX_CP ) );
}

uint8_t eposmodule_unscram_1s_det ( eposmodule_t *ctx )
{
    uint16_t status = 0;
    eposmodule_get_status ( ctx, &status );
    return ( ( EPOSMODULE_STATUS_ENERGY_RX_CP | EPOSMODULE_STATUS_CONT_1S ) == 
             ( status & ( EPOSMODULE_STATUS_ENERGY_RX_CP | EPOSMODULE_STATUS_CONT_0S | EPOSMODULE_STATUS_CONT_1S ) ) );
}

err_t eposmodule_clear_interrupts ( eposmodule_t *ctx )
{
    err_t error_flag = EPOSMODULE_OK;
    uint32_t timeout = 0;
    uint16_t status = 0;
    while ( !eposmodule_get_irq_pin ( ctx ) && ( EPOSMODULE_OK == error_flag ) )
    {
        error_flag |= eposmodule_get_status ( ctx, &status );
        Delay_1ms ( );
        if ( ++timeout > EPOSMODULE_TIMEOUT_CLEAR_IRQ )
        {
            error_flag |= EPOSMODULE_TIMEOUT;
        }
    }
    return error_flag;
}

err_t eposmodule_dial ( eposmodule_t *ctx, uint8_t *dial_num )
{
    if ( strlen ( dial_num ) > EPOSMODULE_DIAL_NUMBER_MAX_LEN )
    {
        return EPOSMODULE_ERROR;
    }
    uint8_t digit_cnt = 0;
    err_t error_flag = EPOSMODULE_OK;
    ctx->tx_mode &= EPOSMODULE_TX_LEVEL_MASK; // No change in tx level setting
    ctx->tx_mode |= EPOSMODULE_TX_MODE_DTMF_TONES; // Select DTMF/Tones
    for ( digit_cnt = 0; dial_num[ digit_cnt ]; digit_cnt++ )
    {
        switch ( dial_num[ digit_cnt ] )
        {
            case 'A': case 'a':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_A;
                break;
            }
            case 'B': case 'b':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_B;
                break;
            }
            case 'C': case 'c':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_C;
                break;
            }
            case 'D': case 'd':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_D;
                break;
            }
            case '*':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_STAR;
                break;
            }
            case '#':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_HASH;
                break;
            }
            case '0':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_0;
                break;
            }
            case '1':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_1;
                break;
            }
            case '2':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_2;
                break;
            }
            case '3':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_3;
                break;
            }
            case '4':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_4;
                break;
            }
            case '5':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_5;
                break;
            }
            case '6':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_6;
                break;
            }
            case '7':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_7;
                break;
            }
            case '8':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_8;
                break;
            }
            case '9':
            {
                ctx->tx_mode |= EPOSMODULE_TX_DTMF_TONE_9;
                break;
            }
            default:
            {
                return EPOSMODULE_ERROR;
            }
        }
        error_flag |= eposmodule_set_transmit_mode ( ctx, ctx->tx_mode );
        Delay_100ms ( );
        ctx->tx_mode ^= ( ctx->tx_mode & EPOSMODULE_TX_DTMF_TONE_MASK ); // Turn tone OFF
        error_flag |= eposmodule_set_transmit_mode ( ctx, ctx->tx_mode );
        Delay_100ms ( );
    }
    return error_flag;
}

err_t eposmodule_send_message ( eposmodule_t *ctx, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = EPOSMODULE_OK;
    uint32_t timeout = 0;
    uint8_t data_cnt = 0;
    uint16_t tx_mode = ctx->tx_mode;
    ctx->tx_mode &= EPOSMODULE_TX_LEVEL_MASK; // No change in tx level setting
    ctx->tx_mode |= ( EPOSMODULE_TX_MODE_V23_FSK_1200 | EPOSMODULE_TX_DATA_FORMAT_SS_NO_PAR | EPOSMODULE_TX_DATA_STOP_8_1 );
    error_flag |= eposmodule_set_transmit_mode ( ctx, ctx->tx_mode );
    Delay_100ms ( ); 
    while ( ( data_cnt < len ) && ( EPOSMODULE_OK == error_flag ) )
    {
        if ( eposmodule_tx_ready ( ctx ) )
        {
            error_flag |= eposmodule_transmit_data ( ctx, data_in[ data_cnt++ ] );
            Delay_100ms ( );
        }
        else
        {
            Delay_1ms ( );
            if ( ++timeout > EPOSMODULE_TIMEOUT_TX_READY )
            {
                error_flag |= EPOSMODULE_TIMEOUT;
            }
        }
    }
    Delay_100ms ( ); 
    error_flag |= eposmodule_set_transmit_mode ( ctx, tx_mode );
    return error_flag;
}

err_t eposmodule_handshake_init ( eposmodule_t *ctx )
{
    err_t error_flag = EPOSMODULE_OK;

    error_flag |= eposmodule_general_reset ( ctx );
    error_flag |= eposmodule_set_control ( ctx, EPOSMODULE_CONTROL_PWR | EPOSMODULE_CONTROL_RST );
    Delay_100ms ( );
    error_flag |= eposmodule_set_control ( ctx, EPOSMODULE_CONTROL_PWR | EPOSMODULE_CONTROL_IRQN_EN | 
                                                EPOSMODULE_CONTROL_IRQ_ENERGY_RX_CP );
    Delay_100ms ( );
    error_flag |= eposmodule_set_receive_mode ( ctx, EPOSMODULE_RX_LEVEL_0_DB );
    error_flag |= eposmodule_set_transmit_mode ( ctx, EPOSMODULE_TX_LEVEL_0_DB );
    Delay_100ms ( );
    eposmodule_clear_interrupts ( ctx );

    return error_flag;
}

// ------------------------------------------------------------------------- END
