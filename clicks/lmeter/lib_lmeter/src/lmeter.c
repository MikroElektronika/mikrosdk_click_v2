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
 * @file lmeter.c
 * @brief L meter Click Driver.
 */

#include "lmeter.h"

void lmeter_cfg_setup ( lmeter_cfg_t *cfg ) 
{
    cfg->t_sw  = HAL_PIN_NC;
    cfg->f_out = HAL_PIN_NC;
}

err_t lmeter_init ( lmeter_t *ctx, lmeter_cfg_t *cfg ) 
{
    err_t error_flag = LMETER_OK;

    error_flag |= digital_out_init( &ctx->t_sw, cfg->t_sw );
    error_flag |= digital_in_init( &ctx->f_out, cfg->f_out );

    /* 
     * C2 stays disconnected during measurement as the inductance is calculated
     * from ratio of two counts and does not depent on the LC tank capacitance.
     */
    digital_out_low( &ctx->t_sw );

    ctx->zero_count = 0;

    /* Wait for output frequency to become stable */
    Delay_1sec( );
    Delay_1sec( );

    return error_flag;
}

void lmeter_set_cal_cap ( lmeter_t *ctx, uint8_t state )
{
    uint16_t cnt = 0;

    /* 
     * A high logic level switches Q1 on and connects C2 which increases the 
     * LC tank capacitance and lowers the oscillator frequency.
     */
    digital_out_write( &ctx->t_sw, state );

    /* Let the LC tank settle after the capacitance change */
    Delay_100ms( );
}

err_t lmeter_measure_counts ( lmeter_t *ctx, uint32_t *count )
{
    /* 
     * The measurement gate is a fixed number of loop passes instead of a fixed
     * amount of time, so no timer is needed. Every call of this function measures
     * over the same window, which is all that the ratio calculation requires.
     */
    uint32_t edge_cnt = 0;
    uint32_t cnt = 0;
    uint8_t curr_state = 0;
    uint8_t prev_state = 0;

    prev_state = ( uint8_t ) ( 0 != digital_in_read( &ctx->f_out ) );

    for ( cnt = 0; LMETER_GATE_SAMPLES > cnt; cnt++ )
    {
        curr_state = ( uint8_t ) ( 0 != digital_in_read( &ctx->f_out ) );
        edge_cnt += ( uint32_t ) ( curr_state & ( prev_state ^ 1 ) );
        prev_state = curr_state;
    }
    *count = edge_cnt;

    /* Too few edges means that the oscillator is not running */
    if ( LMETER_MIN_VALID_COUNT > edge_cnt )
    {
        return LMETER_ERROR;
    }

    return LMETER_OK;
}

err_t lmeter_calibrate ( lmeter_t *ctx )
{
    err_t error_flag = LMETER_OK;
    uint32_t zero_cnt = 0;

    /* Discard the old reference */
    ctx->zero_count = 0;

    /* 
     *  f = 1 / ( 2 * PI * sqrt( ( L1 + LX ) * C ) )
     *
     * With the measurement input shorted the tank holds only the on-board coil L1,
     * so this zero calibration count corresponds to the highest frequency the oscillator can reach.
     */
    error_flag |= lmeter_measure_counts( ctx, &zero_cnt );
    if ( LMETER_OK == error_flag )
    {
        ctx->zero_count = zero_cnt;
    }

    return error_flag;
}

err_t lmeter_get_inductance ( lmeter_t *ctx, float *inductance )
{
    err_t error_flag = LMETER_OK;
    uint32_t dut_cnt = 0;
    float count_ratio = 0;

    /* Without the zero reference the count ratio has no meaning */
    if ( 0 == ctx->zero_count )
    {
        return LMETER_ERROR;
    }

    error_flag |= lmeter_measure_counts( ctx, &dut_cnt );
    if ( LMETER_OK != error_flag )
    {
        return LMETER_ERROR;
    }

    /*
     * Both the zero calibration count and the count with added Lx are
     * taken over the same gate, therefor they are proportional to the 
     * oscillator frequency and the measurement time cancels out as long 
     * as its the same for both count measurements.
     *
     * f_zero^2 = 1 / ( 4 * PI^2 * L1 * C )
     * f_dut^2  = 1 / ( 4 * PI^2 * ( L1 + Lx ) * C )
     * 
     * f = N / T => f_zero / f_dut = N_zero / N_dut 
     *           => ( f_zero / f_dut )^2 = ( L1 + Lx ) / L1 = ( N_zero / N_dut )^2
     *     
     * Lx = ( ( N_zero / N_dut )^2 * L1 ) - L1
     */
    count_ratio = ( float ) ctx->zero_count / dut_cnt;
    *inductance = LMETER_REF_INDUCTANCE_UH * ( count_ratio * count_ratio - 1.0 );

    return error_flag;
}
  
// ------------------------------------------------------------------------- END
