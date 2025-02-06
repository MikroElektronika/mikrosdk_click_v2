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
 * @file tester2.c
 * @brief Tester 2 Click Driver.
 */

#include "tester2.h"

/**
 * @brief Tester 2 toggle delay function.
 * @details This function does nothing for a desired number of milliseconds.
 * @param[in] ctx : Click context object.
 * See #tester2_t object definition for detailed explanation.
 * @param[in] toggle_delay_ms : Delay in milliseconds.
 * @return None.
 * @note None.
 */
static void tester2_toggle_delay ( uint16_t toggle_delay_ms );

void tester2_cfg_setup ( tester2_cfg_t *cfg ) 
{
    cfg->an = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
}

err_t tester2_init ( tester2_t *ctx, tester2_cfg_t *cfg ) 
{
    err_t error_flag = TESTER2_OK;

    error_flag |= digital_out_init( &ctx->an, cfg->an );
    error_flag |= digital_out_init( &ctx->rst, cfg->rst );
    error_flag |= digital_out_init( &ctx->cs, cfg->cs );
    error_flag |= digital_out_init( &ctx->sck, cfg->sck );
    error_flag |= digital_out_init( &ctx->miso, cfg->miso );
    error_flag |= digital_out_init( &ctx->mosi, cfg->mosi );
    error_flag |= digital_out_init( &ctx->pwm, cfg->pwm );
    error_flag |= digital_out_init( &ctx->int_pin, cfg->int_pin );
    error_flag |= digital_out_init( &ctx->rx_pin, cfg->rx_pin );
    error_flag |= digital_out_init( &ctx->tx_pin, cfg->tx_pin );
    error_flag |= digital_out_init( &ctx->scl, cfg->scl );
    error_flag |= digital_out_init( &ctx->sda, cfg->sda );

    digital_out_low ( &ctx->an );
    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->cs );
    digital_out_low ( &ctx->sck );
    digital_out_low ( &ctx->miso );
    digital_out_low ( &ctx->mosi );
    digital_out_low ( &ctx->pwm );
    digital_out_low ( &ctx->int_pin );
    digital_out_low ( &ctx->rx_pin );
    digital_out_low ( &ctx->tx_pin );
    digital_out_low ( &ctx->scl );
    digital_out_low ( &ctx->sda );

    return error_flag;
}

void tester2_toggle_all ( tester2_t *ctx, uint16_t num_toggles, uint16_t toggle_delay_ms )
{
    uint16_t toggle_cnt = 0;
    for ( toggle_cnt = 0; toggle_cnt < num_toggles; toggle_cnt++ )
    {
        digital_out_high ( &ctx->an );
        digital_out_high ( &ctx->rst );
        digital_out_high ( &ctx->cs );
        digital_out_high ( &ctx->sck );
        digital_out_high ( &ctx->miso );
        digital_out_high ( &ctx->mosi );
        digital_out_high ( &ctx->pwm );
        digital_out_high ( &ctx->int_pin );
        digital_out_high ( &ctx->rx_pin );
        digital_out_high ( &ctx->tx_pin );
        digital_out_high ( &ctx->scl );
        digital_out_high ( &ctx->sda );
        tester2_toggle_delay ( toggle_delay_ms );

        digital_out_low ( &ctx->an );
        digital_out_low ( &ctx->rst );
        digital_out_low ( &ctx->cs );
        digital_out_low ( &ctx->sck );
        digital_out_low ( &ctx->miso );
        digital_out_low ( &ctx->mosi );
        digital_out_low ( &ctx->pwm );
        digital_out_low ( &ctx->int_pin );
        digital_out_low ( &ctx->rx_pin );
        digital_out_low ( &ctx->tx_pin );
        digital_out_low ( &ctx->scl );
        digital_out_low ( &ctx->sda );
        tester2_toggle_delay ( toggle_delay_ms );
    }
}

void tester2_toggle_seq ( tester2_t *ctx, uint16_t toggle_delay_ms )
{
    digital_out_high ( &ctx->an );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->an );

    digital_out_high ( &ctx->rst );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->rst );

    digital_out_high ( &ctx->cs );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->cs );

    digital_out_high ( &ctx->sck );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->sck );

    digital_out_high ( &ctx->miso );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->miso );

    digital_out_high ( &ctx->mosi );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->mosi );

    digital_out_high ( &ctx->pwm );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->pwm );

    digital_out_high ( &ctx->int_pin );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->int_pin );

    digital_out_high ( &ctx->rx_pin );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->rx_pin );

    digital_out_high ( &ctx->tx_pin );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->tx_pin );

    digital_out_high ( &ctx->scl );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->scl );

    digital_out_high ( &ctx->sda );
    tester2_toggle_delay ( toggle_delay_ms );
    digital_out_low ( &ctx->sda );

    tester2_toggle_delay ( toggle_delay_ms );
}

static void tester2_toggle_delay ( uint16_t toggle_delay_ms )
{
    uint16_t delay_cnt = 0;
    for ( delay_cnt = 0; delay_cnt < toggle_delay_ms; delay_cnt++ )
    {
        Delay_1ms ( );
    }
}

// ------------------------------------------------------------------------- END
