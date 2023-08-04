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
 * @file hallcurrent11.c
 * @brief Hall Current 11 Click Driver.
 */

#include "hallcurrent11.h"

#define HALLCURRENT11_DATA_12_BIT                        0x0FFF
#define HALLCURRENT11_ADC_FULL_RESOLUTION                4096.0
#define HALLCURRENT11_VREF_3300_mV                          3.3
#define HALLCURRENT11_VCC_2                                 1.65
#define HALLCURRENT11_ADC_NUM_OF_MEASURE                   50.0
#define HALLCURRENT11_CONV_TO_MILI                       1000.0
#define HALLCURRENT11_CURRENT_MULTIPLE_SENSITIVITY        100.0
#define HALLCURRENT11_OFFSET_ERROR                          7
#define HALLCURRENT11_BIDIRECTIONAL_OFFSET_ZERO             3.3

/**
 * @brief Hall Current 11 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #hallcurrent11_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
static err_t hallcurrent11_read_an_pin_value ( hallcurrent11_t *ctx, uint16_t *data_out );

/**
 * @brief Hall Current 11 read ADC value function.
 * @details This function reads 12-bit ADC data by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hallcurrent11_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
static err_t hallcurrent11_read_adc_value ( hallcurrent11_t *ctx, uint16_t *read_adc );

/**
 * @brief Hall Current 11 measurement delay function.
 * @details This function executes a measurement delay of the 1 milliseconds.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
static void dev_measurement_delay ( void );

void hallcurrent11_cfg_setup ( hallcurrent11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->an = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HALLCURRENT11_SET_DEV_ADDR;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref       = HALLCURRENT11_VREF_3300_mV;
    
    cfg->drv_sel = HALLCURRENT11_DRV_SEL_I2C;
}

err_t hallcurrent11_init ( hallcurrent11_t *ctx, hallcurrent11_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    
    if ( HALLCURRENT11_DRV_SEL_I2C == ctx->drv_sel ) 
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
        
        ctx->read_adc_f  = hallcurrent11_read_adc_value;
    }
    else
    {
        analog_in_config_t adc_cfg;

        analog_in_configure_default( &adc_cfg );

        adc_cfg.input_pin = cfg->an;

        if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR ) {
            return ADC_ERROR;
        }

        if ( analog_in_set_vref_value( &ctx->adc, cfg->vref ) == ADC_ERROR ) {
            return ADC_ERROR;
        }

        if ( analog_in_set_resolution( &ctx->adc, cfg->resolution ) == ADC_ERROR ) {
            return ADC_ERROR;
        } 
        
        ctx->read_adc_f  = hallcurrent11_read_an_pin_value;
    }
    
    return I2C_MASTER_SUCCESS;
}

err_t hallcurrent11_default_cfg ( hallcurrent11_t *ctx ) 
{
    uint16_t read_adc;
    
    return hallcurrent11_get_adc( ctx, &read_adc );
}

err_t hallcurrent11_get_adc ( hallcurrent11_t *ctx, uint16_t *data_out ) 
{
    return ctx->read_adc_f( ctx, data_out );
}

err_t hallcurrent11_get_adc_voltage ( hallcurrent11_t *ctx, float *adc_vtg ) 
{
    uint16_t adc_val;
    
    err_t err_flag = hallcurrent11_get_adc( ctx, &adc_val );
    
    *adc_vtg = ( float ) ( adc_val );
    *adc_vtg *= HALLCURRENT11_VREF_3300_mV;
    *adc_vtg /= HALLCURRENT11_ADC_FULL_RESOLUTION;

    return err_flag;
}

err_t hallcurrent11_get_current ( hallcurrent11_t *ctx, float *current ) 
{
    float adc_vtg_sum = 0;
    float adc_vtg;
    err_t err_flag;

    for ( uint8_t n_cnt = 0; n_cnt < HALLCURRENT11_ADC_NUM_OF_MEASURE; n_cnt++ ) 
    {       
        err_flag |= hallcurrent11_get_adc_voltage( ctx, &adc_vtg );
        adc_vtg_sum += adc_vtg;
        dev_measurement_delay( );
    }
    
    *current = adc_vtg_sum;
    *current /= HALLCURRENT11_ADC_NUM_OF_MEASURE;
    *current /= HALLCURRENT11_CURRENT_MULTIPLE_SENSITIVITY;
    *current *= HALLCURRENT11_CONV_TO_MILI;
    *current -= HALLCURRENT11_BIDIRECTIONAL_OFFSET_ZERO;

    return err_flag;
}

err_t hallcurrent11_read_an_pin_voltage ( hallcurrent11_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

static err_t hallcurrent11_read_an_pin_value ( hallcurrent11_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

static err_t hallcurrent11_read_adc_value ( hallcurrent11_t *ctx, uint16_t *read_adc ) 
{
     uint8_t rx_buf[ 2 ];
    uint16_t adc_val;
    
    err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );

    adc_val = rx_buf[ 0 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 1 ];
    adc_val &= HALLCURRENT11_DATA_12_BIT;
    
    *read_adc = adc_val;

    return err_flag;
}

static void dev_measurement_delay ( void ) {
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END
