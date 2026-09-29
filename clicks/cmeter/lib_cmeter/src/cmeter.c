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
 * @file cmeter.c
 * @brief C Meter Click Driver.
 */

#include "cmeter.h"

void cmeter_cfg_setup ( cmeter_cfg_t *cfg ) 
{
    cfg->reset = HAL_PIN_NC;
    cfg->out = HAL_PIN_NC;
}

err_t cmeter_init ( cmeter_t *ctx, cmeter_cfg_t *cfg ) 
{
    err_t error_flag = CMETER_OK;

    error_flag |= digital_out_init( &ctx->reset, cfg->reset );
    error_flag |= digital_in_init( &ctx->out, cfg->out );

    /* Set zero referance to 0 until the calibration is done */
    ctx->zero_period = 0;

    digital_out_high( &ctx->reset );

    return error_flag;
}

err_t cmeter_measure_period ( cmeter_t *ctx, float *period )
{
    uint32_t timeout_cnt = CMETER_TIMEOUT_PASSES;
    uint32_t pass_cnt = 0;
    uint32_t edge_cnt = 0;
    uint8_t prev_state = 0;
    uint8_t curr_state = 0;
    uint8_t edge_flag = 0;
    uint8_t gate_open = 1;

    /* 
     * Wait for a rising edge first, so the measurement window starts and ends
     * at the same phase of the oscillator signal.
     */
    prev_state = ( uint8_t ) ( 0 != digital_in_read( &ctx->out ) );
    do
    {
        curr_state = ( uint8_t ) ( 0 != digital_in_read( &ctx->out ) );
        edge_flag = curr_state & ( prev_state ^ 1 );
        prev_state = curr_state;
        timeout_cnt--;
    }
    while ( ( !edge_flag ) && ( timeout_cnt ) );

    /*  No rising edge means that the oscillator is stopped */
    if ( !edge_flag )
    {
        return CMETER_ERROR;
    }

    /* 
     * The window lasts at least CMETER_GATE_PASSES loop passes and
     * then extends to the next rising edge, so it always holds a
     * whole number of oscillator periods.
     * 
     * The loop body has no branches that depend on the input signal, so every
     * pass lasts the same and the pass count is proportional to the window time.
     */
    timeout_cnt = CMETER_TIMEOUT_PASSES;
    do
    {
        curr_state = ( uint8_t ) ( 0 != digital_in_read( &ctx->out ) );
        edge_flag = curr_state & ( prev_state ^ 1 );
        edge_cnt += ( uint32_t ) edge_flag;
        prev_state = curr_state;
        pass_cnt++;
        timeout_cnt--;
        gate_open = ( uint8_t ) ( CMETER_GATE_PASSES > pass_cnt );
    }
    while ( ( gate_open | ( edge_flag ^ 1 ) ) && ( timeout_cnt ) );

    /* A valid window ends on a rising edge after the gate */
    if ( gate_open || ( !edge_flag ) )
    {
        return CMETER_ERROR;
    }

    /* Average oscillator period expressed in loop passes */
    *period = ( float ) pass_cnt / edge_cnt;

    return CMETER_OK;
}

err_t cmeter_calibrate ( cmeter_t *ctx )
{
    err_t error_flag = CMETER_OK;
    float zero_period = 0;

    /* Discard the old reference */
    ctx->zero_period = 0;

    /* With the measurement input open only the on-board CX sets the oscillator period */
    error_flag |= cmeter_measure_period( ctx, &zero_period );
    if ( CMETER_OK == error_flag )
    {
        ctx->zero_period = zero_period;
    }

    return error_flag;
}

err_t cmeter_get_capacitance ( cmeter_t *ctx, float *capacitance )
{
    err_t error_flag = CMETER_OK;
    float dut_period = 0;

    /* Check if the calibration has been done */
    if ( 0 == ctx->zero_period )
    {
        return CMETER_ERROR;
    }

    error_flag |= cmeter_measure_period( ctx, &dut_period );
    if ( CMETER_OK != error_flag )
    {
        return CMETER_ERROR;
    }

    /* A capacitor in parallel with CX can only lengthen the oscillator period */
    if ( ctx->zero_period >= dut_period )
    {
        *capacitance = 0;
        return error_flag;
    }

    /*
     * Both the zero reference period and the period with added C_dut are
     * measured in the same loop passes, therefore the duration of one loop
     * pass cancels out as long as it is the same for both measurements.
     *
     * Astable NE555 period (NE555 datasheet, page 11):
     * T_zero = 0.693 * ( R1 + 2 * R2 ) * CX
     * T_dut  = 0.693 * ( R1 + 2 * R2 ) * ( CX + C_dut )
     *
     * T = P * t_pass => T_dut / T_zero = P_dut / P_zero
     *                => T_dut / T_zero = ( CX + C_dut ) / CX
     *
     * C_dut = ( ( P_dut / P_zero ) * CX ) - CX
     */
    *capacitance = CMETER_REF_CAPACITANCE_NF * ( dut_period / ctx->zero_period - 1 );

    return error_flag;
}

// ------------------------------------------------------------------------- END
