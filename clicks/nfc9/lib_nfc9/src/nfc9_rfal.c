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
 * @file nfc9_rfal.c
 * @brief RFAL platform bridge for NFC 9 Click.
 */

#include "nfc9_rfal.h"

static nfc9_t *nfc9_rfal_ctx;
static uint32_t nfc9_rfal_tick_ms;

static void nfc9_rfal_timer_advance_1ms ( void )
{
    Delay_1ms( );
    nfc9_rfal_tick_ms++;
}

void nfc9_rfal_set_context ( nfc9_t *ctx )
{
    nfc9_rfal_ctx = ctx;
    nfc9_rfal_tick_ms = 0;
}

void nfc9_rfal_spi_select ( void )
{
    if ( NULL != nfc9_rfal_ctx )
    {
        spi_master_select_device( nfc9_rfal_ctx->chip_select );
    }
}

void nfc9_rfal_spi_deselect ( void )
{
    if ( NULL != nfc9_rfal_ctx )
    {
        spi_master_deselect_device( nfc9_rfal_ctx->chip_select );
    }
}

void nfc9_rfal_spi_tx_rx ( const uint8_t *tx_buf, uint8_t *rx_buf, uint16_t len )
{
    if ( ( NULL == nfc9_rfal_ctx ) || ( 0 == len ) )
    {
        return;
    }

    if ( NULL == rx_buf )
    {
        spi_master_write( &nfc9_rfal_ctx->spi, ( uint8_t * ) tx_buf, len );
    }
    else if ( NULL == tx_buf )
    {
        spi_master_read( &nfc9_rfal_ctx->spi, rx_buf, len );
    }
    else if ( tx_buf == rx_buf )
    {
        spi_master_read( &nfc9_rfal_ctx->spi, rx_buf, len );
    }
    else
    {
        spi_master_write( &nfc9_rfal_ctx->spi, ( uint8_t * ) tx_buf, len );
    }
}

void nfc9_rfal_delay ( uint32_t ms )
{
    while ( ms-- )
    {
        nfc9_rfal_timer_advance_1ms( );
    }
}

uint32_t nfc9_rfal_timer_create ( uint16_t ms )
{
    return nfc9_rfal_tick_ms + ms;
}

uint8_t nfc9_rfal_timer_is_expired ( uint32_t timer )
{
    nfc9_rfal_timer_advance_1ms( );
    return ( nfc9_rfal_tick_ms >= timer );
}

uint32_t nfc9_rfal_timer_get_remaining ( uint32_t timer )
{
    if ( nfc9_rfal_tick_ms >= timer )
    {
        return 0;
    }
    return timer - nfc9_rfal_tick_ms;
}

uint32_t nfc9_rfal_timer_get_tick ( void )
{
    return nfc9_rfal_tick_ms;
}

uint8_t nfc9_rfal_irq_is_high ( void )
{
    if ( NULL == nfc9_rfal_ctx )
    {
        return 0;
    }
    return nfc9_get_irq_pin( nfc9_rfal_ctx );
}

uint8_t nfc9_rfal_irq_is_low ( void )
{
    return !nfc9_rfal_irq_is_high( );
}

// ------------------------------------------------------------------------ END
