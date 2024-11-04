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
 * @file hallcurrent12.c
 * @brief Hall Current 12 Click Driver.
 */

#include "hallcurrent12.h"

#define HALLCURRENT12_DATA_12_BIT                        0x0FFF
#define HALLCURRENT12_VREF_3300_mV                       3.3
#define HALLCURRENT12_VCC_2                              1.65
#define HALLCURRENT12_ADC_NUM_OF_MEASURE                 200
#define HALLCURRENT12_CURRENT_SENSITIVITY_V              0.4

/**
 * @brief Hall Current 12 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #hallcurrent12_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t hallcurrent12_read_an_pin_value ( hallcurrent12_t *ctx, uint16_t *data_out );

/**
 * @brief Hall Current 12 read ADC value function.
 * @details This function reads 12-bit ADC data by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hallcurrent12_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t hallcurrent12_read_adc_value ( hallcurrent12_t *ctx, uint16_t *read_adc );

/**
 * @brief Hall Current 12 measurement delay function.
 * @details This function executes a measurement delay of the 1 milliseconds 
 * of Hall Current 12 Click board™.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_measurement_delay ( void );

void hallcurrent12_cfg_setup ( hallcurrent12_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->an = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HALLCURRENT12_SET_DEV_ADDR;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref       = HALLCURRENT12_VREF_3300_mV;

    cfg->drv_sel = HALLCURRENT12_DRV_SEL_AN;
}

err_t hallcurrent12_init ( hallcurrent12_t *ctx, hallcurrent12_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( HALLCURRENT12_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_adc_f = hallcurrent12_get_adc_voltage;
    }
    else
    {
        analog_in_config_t adc_cfg;

        analog_in_configure_default( &adc_cfg );

        adc_cfg.input_pin = cfg->an;

        if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
        {
            return ADC_ERROR;
        }

        if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
        {
            return ADC_ERROR;
        }

        if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
        {
            return ADC_ERROR;
        } 

        ctx->read_adc_f = hallcurrent12_get_pin_voltage;    
    }

    return I2C_MASTER_SUCCESS;
}

err_t hallcurrent12_get_adc ( hallcurrent12_t *ctx, float *adc_vtg ) 
{
    float adc_vtg_sum = 0;
    float adc_vtg_tmp = 0;
    err_t err_flag = 0;
    uint16_t n_cnt = 0;
    
    for ( n_cnt = 0; n_cnt < HALLCURRENT12_ADC_NUM_OF_MEASURE; n_cnt++ ) 
    {       
        err_flag |= ctx->read_adc_f( ctx, &adc_vtg_tmp );
        adc_vtg_sum += adc_vtg_tmp;
        dev_measurement_delay( );
    }

    *adc_vtg = adc_vtg_sum / HALLCURRENT12_ADC_NUM_OF_MEASURE;
    return err_flag;
}

err_t hallcurrent12_get_adc_voltage ( hallcurrent12_t *ctx, float *adc_vtg ) 
{
    uint16_t adc_val = 0;

    err_t err_flag = hallcurrent12_read_adc_value( ctx, &adc_val );

    *adc_vtg = ( float ) ( adc_val );
    *adc_vtg *= HALLCURRENT12_VREF_3300_mV;
    *adc_vtg /= HALLCURRENT12_DATA_12_BIT;

    return err_flag;
}

err_t hallcurrent12_get_current ( hallcurrent12_t *ctx, float *current ) 
{
    float adc_vtg = 0;
    err_t err_flag = 0;

    err_flag |= hallcurrent12_get_adc( ctx, &adc_vtg );    
    
    adc_vtg -= ( HALLCURRENT12_VCC_2 - ctx->offset );

    *current = adc_vtg / HALLCURRENT12_CURRENT_SENSITIVITY_V;

    return err_flag;
}

err_t hallcurrent12_get_pin_voltage ( hallcurrent12_t *ctx, float *adc_vtg ) 
{
    return analog_in_read_voltage( &ctx->adc, adc_vtg );
}

err_t hallcurrent12_calibration ( hallcurrent12_t *ctx )
{
    err_t err_flag = HALLCURRENT12_OK;
    float adc_vtg = 0;
    
    err_flag |= hallcurrent12_get_adc( ctx, &adc_vtg ); 
    
    ctx->offset = HALLCURRENT12_VCC_2 - adc_vtg; 
    
    return err_flag;
}

static err_t hallcurrent12_read_adc_value ( hallcurrent12_t *ctx, uint16_t *read_adc ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    uint16_t adc_val = 0;
    
    err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );

    adc_val = rx_buf[ 0 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 1 ];
    adc_val &= HALLCURRENT12_DATA_12_BIT;
    
    *read_adc = adc_val;

    return err_flag;
}

static void dev_measurement_delay ( void ) 
{
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END
