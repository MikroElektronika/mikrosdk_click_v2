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
 * @file loadcell8.c
 * @brief Load Cell 8 Click Driver.
 */

#include "loadcell8.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief Load Cell 8 get average measurement data function.
 * @param[in] ctx : Click context object.
 * See #loadcell8_t object definition for detailed explanation.
 * @param[out] avr_measure : Average measurement data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t loadcell8_get_avr_measure ( loadcell8_t *ctx, float *avr_measure );

void loadcell8_cfg_setup ( loadcell8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LOADCELL8_DEVICE_ADDRESS;
}

err_t loadcell8_init ( loadcell8_t *ctx, loadcell8_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->an, cfg->an );

    return I2C_MASTER_SUCCESS;
}

err_t loadcell8_default_cfg ( loadcell8_t *ctx ) 
{   
    uint32_t raw_adc = 0;

    loadcell8_hw_reset( ctx );
    Delay_100ms( );

    err_t err_flag = loadcell8_read_raw_adc( ctx, &raw_adc );
    Delay_100ms( );

    return err_flag;
}

err_t loadcell8_generic_write ( loadcell8_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t loadcell8_generic_read ( loadcell8_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void loadcell8_hw_reset ( loadcell8_t *ctx ) 
{
    digital_out_high( &ctx->en );
    Delay_10ms( );
    Delay_10ms( );
    digital_out_low( &ctx->en );
}

err_t loadcell8_read_raw_adc ( loadcell8_t *ctx, uint32_t *raw_adc ) 
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t err_flag = i2c_master_read( &ctx->i2c, data_buf, 4 );
    *raw_adc = data_buf[ 0 ];
    *raw_adc <<= 8;
    *raw_adc |= data_buf[ 1 ];
    *raw_adc <<= 8;
    *raw_adc |= data_buf[ 2 ];
    *raw_adc <<= 8;
    *raw_adc |= data_buf[ 3 ];
    return err_flag;
}

err_t loadcell8_tare_scale ( loadcell8_t *ctx, loadcell8_data_t *cell_data ) 
{
    float weight_val = 0;
    err_t err_flag = loadcell8_get_avr_measure( ctx, &weight_val );

    cell_data->tare = ( float ) weight_val;
    cell_data->tare_ok = LOADCELL8_OK;
    cell_data->weight_data_100g_ok = LOADCELL8_OK;
    cell_data->weight_data_500g_ok = LOADCELL8_OK;
    cell_data->weight_data_1000g_ok = LOADCELL8_OK;
    cell_data->weight_data_5000g_ok = LOADCELL8_OK;
    cell_data->weight_data_10000g_ok = LOADCELL8_OK;
    return err_flag;
}

err_t loadcell8_calibration_weight ( loadcell8_t *ctx, uint16_t cal_val, loadcell8_data_t *cell_data ) 
{
    float weight_val = 0;
    err_t err_flag = loadcell8_get_avr_measure( ctx, &weight_val );
    weight_val -= cell_data->tare;

    switch ( cal_val ) 
    {
        case LOADCELL8_WEIGHT_100G: 
        {
            cell_data->weight_coeff_100g = ( float ) LOADCELL8_WEIGHT_100G / weight_val;
            cell_data->weight_data_100g_ok = LOADCELL8_DATA_OK;
            break;
        }
        case LOADCELL8_WEIGHT_500G: 
        {
            cell_data->weight_coeff_500g = ( float ) LOADCELL8_WEIGHT_500G / weight_val;
            cell_data->weight_data_500g_ok = LOADCELL8_DATA_OK;
            break;
        }
        case LOADCELL8_WEIGHT_1000G: 
        {
            cell_data->weight_coeff_1000g = ( float ) LOADCELL8_WEIGHT_1000G / weight_val;
            cell_data->weight_data_1000g_ok = LOADCELL8_DATA_OK;
            break;
        }
        case LOADCELL8_WEIGHT_5000G: 
        {
            cell_data->weight_coeff_5000g = ( float ) LOADCELL8_WEIGHT_5000G / weight_val;
            cell_data->weight_data_5000g_ok = LOADCELL8_DATA_OK;
            break;
        }
        case LOADCELL8_WEIGHT_10000G: 
        {
            cell_data->weight_coeff_10000g = ( float ) LOADCELL8_WEIGHT_10000G / weight_val;
            cell_data->weight_data_10000g_ok = LOADCELL8_DATA_OK;
            break;
        }
        default : 
        {
            err_flag = LOADCELL8_ERROR;
            cell_data->weight_data_100g_ok   = LOADCELL8_ERROR;
            cell_data->weight_data_500g_ok   = LOADCELL8_ERROR;
            cell_data->weight_data_1000g_ok  = LOADCELL8_ERROR;
            cell_data->weight_data_5000g_ok  = LOADCELL8_ERROR;
            cell_data->weight_data_10000g_ok = LOADCELL8_ERROR;
            break;
        }
    }
    return err_flag;
}

err_t loadcell8_get_weight ( loadcell8_t *ctx, loadcell8_data_t *cell_data, float *weight_g ) 
{
    float weight_val = 0;
    err_t err_flag = loadcell8_get_avr_measure( ctx, &weight_val );
    weight_val -= cell_data->tare;

    if ( LOADCELL8_DATA_OK == cell_data->weight_data_100g_ok ) 
    {
        weight_val *= cell_data->weight_coeff_100g;
        Delay_1ms( );
    } 
    else if ( LOADCELL8_DATA_OK == cell_data->weight_data_500g_ok ) 
    {
        weight_val *= cell_data->weight_coeff_500g;
        Delay_1ms( );
    } 
    else if ( LOADCELL8_DATA_OK == cell_data->weight_data_1000g_ok ) 
    {
        weight_val *= cell_data->weight_coeff_1000g;
        Delay_1ms( );
    } 
    else if ( LOADCELL8_DATA_OK == cell_data->weight_data_5000g_ok ) 
    {
        weight_val *= cell_data->weight_coeff_5000g;
        Delay_1ms( );
    } 
    else if ( LOADCELL8_DATA_OK == cell_data->weight_data_10000g_ok ) 
    {
        weight_val *= cell_data->weight_coeff_10000g;
        Delay_1ms( );
    }

    *weight_g = ( float ) weight_val;
    if ( weight_val < LOADCELL8_WEIGHT_ZERO ) 
    {
        *weight_g = LOADCELL8_WEIGHT_ZERO;
        err_flag = LOADCELL8_ERROR;
    }
    return err_flag;
}

static err_t loadcell8_get_avr_measure ( loadcell8_t *ctx, float *avr_measure ) 
{
    err_t err_flag = LOADCELL8_OK;
    uint32_t raw_data = 0;
    for ( uint8_t n_cnt = 0; n_cnt < 100; n_cnt++ ) 
    {
        err_flag |= loadcell8_read_raw_adc( ctx, &raw_data );
        raw_data >>= 16;
        raw_data &= LOADCELL8_MEASURE_DATA_RES;
        *avr_measure += ( float ) raw_data;
        Delay_1ms( );
    }
    *avr_measure /= LOADCELL8_AVG_MEASURE_100;
    return err_flag;
}

// ------------------------------------------------------------------------- END
