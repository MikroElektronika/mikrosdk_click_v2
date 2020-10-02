/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "loadcell.h"

// ------------------------------------------------------------- PRIVATE MACROS 


// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

// Clock delay
static void dev_clk_delay ( void );

// The pin state delay
static void dev_rst_delay ( void );

// Measurement delay
static void dev_measure_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void loadcell_cfg_setup ( loadcell_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->rte   = HAL_PIN_NC;
    cfg->clk = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

LOADCELL_RETVAL loadcell_init ( loadcell_t *ctx, loadcell_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->rte, cfg->rte );
    digital_out_init( &ctx->clk, cfg->clk );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    

    return LOADCELL_OK;
}

uint8_t loadcell_check_out ( loadcell_t *ctx )
{
    if ( digital_in_read( &ctx->int_pin ))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t loadcell_read_results ( loadcell_t *ctx, uint8_t input_sel, uint32_t *data_out )
{
    uint8_t count;
    uint8_t n_cnt;
    uint32_t ret_val = 0;
    uint32_t temp = 0;

    switch ( input_sel )
    {
        case LOADCELL_CHANN_A_GATE_128_NEXT :
        {
            count = 25;
            break;
        }
        case LOADCELL_CHANN_B_GATE_32_NEXT :
        {
            count = 26;
            break;
        }
        case LOADCELL_CHANN_A_GATE_64_NEXT :
        {
            count = 27;
            break;
        }
        default :
        {
            return LOADCELL_GET_RESULT_ERROR;
            break;
        }
    }

    while ( loadcell_check_out( ctx ) );
    
    dev_clk_delay( );

    for ( n_cnt = 24; n_cnt > 0; n_cnt-- )
    {
        digital_out_high( &ctx->clk );
    
        dev_clk_delay( );
        
        temp = loadcell_check_out( ctx );
        temp <<= n_cnt - 1;
        ret_val |= temp;
        digital_out_low( &ctx->clk );
        
        dev_clk_delay( );
    }
    
    count -= 24;
   
    while ( count )
    {
        digital_out_high( &ctx->clk );
        
        dev_clk_delay( );
        
       digital_out_low( &ctx->clk );
        
        dev_clk_delay( );
        
        count--;
    }
    
    *data_out = ret_val;

    return LOADCELL_GET_RESULT_OK;
}

void loadcell_set_rate ( loadcell_t *ctx, uint8_t rate_sel )
{
    if ( rate_sel )
    {
        digital_out_high( &ctx->rte );
    }
    else
    {
        digital_out_low( &ctx->rte );
    }
}

void loadcell_reset ( loadcell_t *ctx )
{
    digital_out_high( &ctx->clk );
    
    dev_rst_delay( );
    dev_rst_delay( );
    
    digital_out_low( &ctx->clk );
    
    dev_rst_delay( );
}

void loadcell_set_mode ( loadcell_t *ctx, uint8_t pwr_mode )
{
    if ( pwr_mode )
    {
        digital_out_high( &ctx->clk );
    }
    else
    {
        digital_out_low( &ctx->clk );
    }
    
    dev_rst_delay( );
    dev_rst_delay( );
}

void loadcell_tare ( loadcell_t *ctx, uint8_t input_sel, loadcell_data_t *cell_data )
{
    uint32_t results;
    uint8_t n_cnt;
    uint32_t sum_val;
    float average_val;
    
    for ( n_cnt = 0; n_cnt < 5; n_cnt++ )
    {
        loadcell_read_results( ctx, input_sel, &results );
        dev_measure_delay( );
    }
    
    sum_val = 0;
    
    for ( n_cnt = 0; n_cnt < 100; n_cnt++ )
    {
        loadcell_read_results( ctx, input_sel, &results );
        
        sum_val += results;

        dev_measure_delay( );
    }
    
    average_val = ( float ) sum_val;
    average_val /= 100.0;
    
    cell_data->tare = average_val;
    cell_data->tare_ok = LOADCELL_DATA_OK;
    cell_data->weight_data_100g_ok = LOADCELL_DATA_NO_DATA;
    cell_data->weight_data_500g_ok = LOADCELL_DATA_NO_DATA;
    cell_data->weight_data_1000g_ok = LOADCELL_DATA_NO_DATA;
    cell_data->weight_data_5000g_ok = LOADCELL_DATA_NO_DATA;
    cell_data->weight_data_10000g_ok = LOADCELL_DATA_NO_DATA;
}

uint8_t loadcell_calibration ( loadcell_t *ctx, uint8_t input_sel, uint16_t cal_val, loadcell_data_t *cell_data )
{
    uint32_t results;
    uint8_t n_cnt;
    uint32_t sum_val;
    float average_val;
    float tare_val;
    float weight_val;
    uint8_t status;
    
    status = LOADCELL_GET_RESULT_OK;
    
    tare_val = cell_data->tare;
    
    sum_val = 0;
    
    for ( n_cnt = 0; n_cnt < 20; n_cnt++ )
    {
        loadcell_read_results( ctx, input_sel, &results );

        sum_val += results;

        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= 20.0;
    
    weight_val = average_val - tare_val;
    
    switch ( cal_val )
    {
        case LOADCELL_WEIGHT_100G :
        {
            cell_data->weight_coeff_100g = 100.0 / weight_val;
            cell_data->weight_data_100g_ok = LOADCELL_DATA_OK;
            break;
        }
        case LOADCELL_WEIGHT_500G :
        {
            cell_data->weight_coeff_500g = 500.0 / weight_val;
            cell_data->weight_data_500g_ok = LOADCELL_DATA_OK;
            break;
        }
        case LOADCELL_WEIGHT_1000G :
        {
            cell_data->weight_coeff_1000g = 1000.0 / weight_val;
            cell_data->weight_data_1000g_ok = LOADCELL_DATA_OK;
            break;
        }
        case LOADCELL_WEIGHT_5000G :
        {
            cell_data->weight_coeff_5000g = 5000.0 / weight_val;
            cell_data->weight_data_5000g_ok = LOADCELL_DATA_OK;
            break;
        }
        case LOADCELL_WEIGHT_10000G :
        {
            cell_data->weight_coeff_10000g = 10000.0 / weight_val;
            cell_data->weight_data_10000g_ok = LOADCELL_DATA_OK;
            break;
        }
        default :
        {
            status = LOADCELL_GET_RESULT_ERROR;
            cell_data->weight_data_100g_ok = LOADCELL_DATA_NO_DATA;
            cell_data->weight_data_500g_ok = LOADCELL_DATA_NO_DATA;
            cell_data->weight_data_1000g_ok = LOADCELL_DATA_NO_DATA;
            cell_data->weight_data_5000g_ok = LOADCELL_DATA_NO_DATA;
            cell_data->weight_data_10000g_ok = LOADCELL_DATA_NO_DATA;
            break;
        }
    }
    
    return status;
}

float loadcell_get_weight ( loadcell_t *ctx, uint8_t input_sel, loadcell_data_t *cell_data )
{
    uint32_t results;
    uint8_t n_cnt;
    uint32_t sum_val;
    float average_val;
    float tare_val;
    float weight_val;
    uint8_t status;

    status = LOADCELL_GET_RESULT_OK;

    tare_val = cell_data->tare;

    sum_val = 0;

    for ( n_cnt = 0; n_cnt < 20; n_cnt++ )
    {
        loadcell_read_results( ctx, input_sel, &results );

        sum_val += results;

        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= 20.0;

    weight_val = average_val - tare_val;
    
    if ( cell_data->weight_data_100g_ok == LOADCELL_DATA_OK )
    {
        weight_val *= cell_data->weight_coeff_100g;
    }
    else if ( cell_data->weight_data_500g_ok == LOADCELL_DATA_OK )
    {
        weight_val *= cell_data->weight_coeff_500g;
    }
    else if ( cell_data->weight_data_1000g_ok == LOADCELL_DATA_OK )
    {
        weight_val *= cell_data->weight_coeff_1000g;
    }
    else if ( cell_data->weight_data_5000g_ok == LOADCELL_DATA_OK )
    {
        weight_val *= cell_data->weight_coeff_5000g;
    }
    else if ( cell_data->weight_data_10000g_ok == LOADCELL_DATA_OK )
    {
        weight_val *= cell_data->weight_coeff_10000g;
    }
    else
    {
        weight_val *= LOADCELL_DEFAULT_WEIGHT_SCALE_COEFFICIENT;
    }

    if ( weight_val < 0 )
    {
        weight_val = 0.0;
    }
    
    return weight_val;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_clk_delay ( void )
{
    Delay_1us( );
}

static void dev_rst_delay ( void )
{
    Delay_50us( );
}

static void dev_measure_delay ( void )
{
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END

