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
 * @file dtmfgenerator.c
 * @brief DTMF Generator Click Driver.
 */

#include "dtmfgenerator.h"

/**
 * @brief DTMF Generator Click ASCII matrix.
 * @details Matrix storing ASCII codes for characters of DTMF Generator Click.
 */
static const uint8_t dev_ascii_matrix[ 17 ][ 5 ] =
{
    { 0, 1, 0, 1, 0 }, // 0
    { 1, 0, 0, 0, 0 }, // 1
    { 0, 1, 0, 0, 0 }, // 2
    { 1, 1, 0, 0, 0 }, // 3
    { 0, 0, 1, 0, 0 }, // 4
    { 1, 0, 1, 0, 0 }, // 5
    { 0, 1, 1, 0, 0 }, // 6
    { 1, 1, 1, 0, 0 }, // 7
    { 0, 0, 0, 1, 0 }, // 8
    { 1, 0, 0, 1, 0 }, // 9
    { 1, 0, 1, 1, 0 }, // A
    { 0, 1, 1, 1, 0 }, // B
    { 1, 1, 1, 1, 0 }, // C
    { 0, 0, 0, 0, 0 }, // D
    { 1, 1, 0, 1, 0 }, // *
    { 0, 0, 1, 1, 0 }, // #
    { 1, 1, 1, 1, 1 }  // STOP
};

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Clock delay function.
 * @details Time duration 1 millisecond.
 */
static void dev_clk_delay ( void );

/**
 * @brief Digits repeat counter delay function.
 * @details Time duration 10 microsecond.
 */
static void dev_digits_repeat_cnt_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void dtmfgenerator_cfg_setup ( dtmfgenerator_cfg_t *cfg ) {
    cfg->dat = HAL_PIN_NC;
    cfg->ce   = HAL_PIN_NC;
    cfg->clk = HAL_PIN_NC;
}

err_t dtmfgenerator_init ( dtmfgenerator_t *ctx, dtmfgenerator_cfg_t *cfg ) {
   err_t return_flag = 0;

    return_flag |= digital_out_init( &ctx->dat, cfg->dat );
    return_flag |= digital_out_init( &ctx->ce, cfg->ce );
    return_flag |= digital_out_init( &ctx->clk, cfg->clk );
    
    return return_flag;
}

void dtmfgenerator_set_dat ( dtmfgenerator_t *ctx, uint8_t pin_state ) {
    if ( pin_state == DTMFGENERATOR_GPIO_PIN_STATE_HIGH ) {
        digital_out_high( &ctx->dat );
    } else {
        digital_out_low( &ctx->dat );
    }
}

void dtmfgenerator_set_ce ( dtmfgenerator_t *ctx, uint8_t pin_state ) {
    if ( pin_state == DTMFGENERATOR_GPIO_PIN_STATE_HIGH ) {
        digital_out_high( &ctx->ce );
    } else {
        digital_out_low( &ctx->ce );
    }
}

void dtmfgenerator_set_clk ( dtmfgenerator_t *ctx, uint8_t pin_state ) {
    if ( pin_state == DTMFGENERATOR_GPIO_PIN_STATE_HIGH ) {
        digital_out_high( &ctx->clk );
    } else {
        digital_out_low( &ctx->clk );
    }
}

void dtmfgenerator_power_on ( dtmfgenerator_t *ctx ) {
    dtmfgenerator_set_ce( ctx, DTMFGENERATOR_GPIO_PIN_STATE_HIGH );
    dtmfgenerator_set_clk( ctx, DTMFGENERATOR_GPIO_PIN_STATE_LOW );
    
    dev_clk_delay( );

    dtmfgenerator_set_ce( ctx, DTMFGENERATOR_GPIO_PIN_STATE_LOW );
    dtmfgenerator_set_clk( ctx, DTMFGENERATOR_GPIO_PIN_STATE_HIGH );
}

void dtmfgenerator_transmit_out_tone ( dtmfgenerator_t *ctx, uint8_t out_tone, uint16_t delay_m_s ) {
    uint8_t n_cnt;
    
    while ( delay_m_s > 0 ) {
        for ( n_cnt = 0 ; n_cnt < 5 ; n_cnt++ ) {
            dtmfgenerator_set_clk ( ctx, DTMFGENERATOR_GPIO_PIN_STATE_HIGH );
            dev_clk_delay( );
                
            dtmfgenerator_set_dat ( ctx, dev_ascii_matrix[ out_tone][ n_cnt ] );
            dev_clk_delay( );
                
            dtmfgenerator_set_clk ( ctx, DTMFGENERATOR_GPIO_PIN_STATE_LOW );
            dev_clk_delay( );
        }
            
        delay_m_s--;
        dev_digits_repeat_cnt_delay( );
    }
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_clk_delay ( void ) {
    Delay_10us( );
}

static void dev_digits_repeat_cnt_delay ( void ) {
    Delay_1ms( );
}
// ------------------------------------------------------------------------- END
