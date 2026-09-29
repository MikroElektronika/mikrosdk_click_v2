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
 * @file radiation.c
 * @brief Radiation Click Driver.
 */

#include "radiation.h"

void radiation_cfg_setup ( radiation_cfg_t *cfg ) 
{
    cfg->int_pin = HAL_PIN_NC;
}

err_t radiation_init ( radiation_t *ctx, radiation_cfg_t *cfg ) 
{
    err_t error_flag = RADIATION_OK;

    error_flag |= digital_in_init( &ctx->int_pin, cfg->int_pin );

    return error_flag;
}

uint8_t radiation_int_pin_read ( radiation_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

err_t radiation_count_pulses ( radiation_t *ctx, uint32_t window_ms, uint32_t *pulse_cnt )
{
    uint32_t ms_cnt = window_ms;
    uint8_t poll_cnt = 0;
    uint8_t curr_state = RADIATION_PIN_STATE_LOW;

    /* Start from the high state -> pulse already in proggress at the window beginning not counted */
    uint8_t prev_state = RADIATION_PIN_STATE_HIGH;

    if ( ( NULL == pulse_cnt ) || ( 0 == window_ms ) )
    {
        return RADIATION_ERROR;
    }

    *pulse_cnt = 0;

    /* 
     * Each detected particale produces one positive pulse on INT pin.
     * Pulse width is 50 to 200us (page 2).
     * Every pulse is counted once, on its LOW to HIGH transition.
     */
    while ( ms_cnt )
    {
        /* 45 samples, every 22us (enough to to capture the 50us pulse) => 990us */
        poll_cnt = RADIATION_POLLS_PER_MS;
        while ( poll_cnt )
        {
            curr_state = RADIATION_PIN_STATE_LOW;
            if ( radiation_int_pin_read( ctx ) )
            {
                curr_state = RADIATION_PIN_STATE_HIGH;
            }

            /* If rising edge -> new pulse detected */
            if ( ( RADIATION_PIN_STATE_HIGH == curr_state ) && ( RADIATION_PIN_STATE_LOW == prev_state ) )
            {
                ( *pulse_cnt )++;
            }

            prev_state = curr_state;
            Delay_22us( );
            poll_cnt--;
        }
        ms_cnt--;
    }

    return RADIATION_OK;
}

// ------------------------------------------------------------------------- END
