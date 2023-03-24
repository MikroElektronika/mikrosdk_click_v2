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
 * @file altitude5.c
 * @brief Altitude 5 Click Driver.
 */

#include "altitude5.h"
#include "math.h"

#define ALTITUDE5_DATA_12_BIT                        0x0FFF
#define ALTITUDE5_VREF_5000_mV                          5.0
#define ALTITUDE5_VDD_5000_mV                           5.0
#define ALTITUDE5_ADC_FULL_RESOLUTION                4096.0
#define ALTITUDE5_VCC_2                                 2.5
#define ALTITUDE5_CONVERT_kPa_TO_hPa                   10.0
#define ALTITUDE5_ADC_NUM_OF_MEASURE                   50
#define ALTITUDE5_OFFSET_A                              0.01067
#define ALTITUDE5_OFFSET_B                             -0.32667
#define ALTITUDE5_TEMP_CONVERT_C_TO_K                 273.15
#define ALTITUDE5_ISA_MODEL_PARAM                       0.1902225603956629
#define ALTITUDE5_CONVERT_NEG                          1
#define ALTITUDE5_STANDARD_TEMPERATURE_LAPSE_RATE       0.0065

/**
 * @brief Altitude 5 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #altitude5_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t altitude5_read_an_pin_value ( altitude5_t *ctx, uint16_t *data_out );

/**
 * @brief Altitude 5 read ADC value function.
 * @details This function reads 12-bit ADC data by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #altitude5_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t altitude5_read_adc_value ( altitude5_t *ctx, uint16_t *read_adc );

/**
 * @brief Altitude 5 measurement delay function.
 * @details This function executes a measurement delay of the 1 milliseconds.
 * @param[in] ctx : Click context object.
 * See #altitude5_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_measurement_delay ( void );

void altitude5_cfg_setup ( altitude5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->an = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ALTITUDE5_SET_DEV_ADDR;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_12_BIT;
    cfg->vref       = ALTITUDE5_VREF_5000_mV;
    
    cfg->adc_offset = 0;
    cfg->sea_level_pressure = 1013.25;
    cfg->temperature_degree_celsius = 20.0;
    
    cfg->drv_sel = ALTITUDE5_DRV_SEL_I2C;
}

err_t altitude5_init ( altitude5_t *ctx, altitude5_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->offset = cfg->adc_offset;
    ctx->sea_lvl_pressure = cfg->sea_level_pressure;
    ctx->temperature = cfg->temperature_degree_celsius;
    
    if ( ALTITUDE5_DRV_SEL_I2C == ctx->drv_sel )
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
        
        ctx->read_adc_f  = altitude5_read_adc_value;
    }
    else
    {
        analog_in_config_t adc_cfg;

        analog_in_configure_default( &adc_cfg );

        adc_cfg.input_pin = cfg->an;

        if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR ) 
        {
            return ADC_ERROR;
        }

        if ( analog_in_set_vref_value( &ctx->adc, cfg->vref ) == ADC_ERROR ) 
        {
            return ADC_ERROR;
        }

        if ( analog_in_set_resolution( &ctx->adc, cfg->resolution ) == ADC_ERROR ) 
        {
            return ADC_ERROR;
        } 
        
        ctx->read_adc_f  = altitude5_read_an_pin_value;    
    }

    return I2C_MASTER_SUCCESS;
}

err_t altitude5_default_cfg ( altitude5_t *ctx ) 
{
    uint16_t adc_val;
    
    return altitude5_get_adc( ctx, &adc_val );
}

err_t altitude5_get_adc ( altitude5_t *ctx, uint16_t *data_out ) 
{
    return ctx->read_adc_f( ctx, data_out );
}

err_t altitude5_read_an_pin_voltage ( altitude5_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t altitude5_get_adc_voltage ( altitude5_t *ctx, float *adc_vtg ) 
{
    uint16_t adc_val;
    
    err_t err_flag = altitude5_get_adc( ctx, &adc_val );
    
    *adc_vtg = ( float ) ( adc_val );
    *adc_vtg *= ALTITUDE5_VREF_5000_mV;
    *adc_vtg /= ALTITUDE5_ADC_FULL_RESOLUTION;

    return err_flag;
}

err_t altitude5_get_pressure ( altitude5_t *ctx, float *pressure ) 
{
    float adc_vtg_sum = 0;
    float adc_vtg;
    err_t err_flag;

    for ( uint8_t n_cnt = 0; n_cnt < ALTITUDE5_ADC_NUM_OF_MEASURE; n_cnt++ ) 
    {       
        err_flag |= altitude5_get_adc_voltage( ctx, &adc_vtg );
        adc_vtg_sum += adc_vtg;
        dev_measurement_delay( );
    }
    
    *pressure = adc_vtg_sum;
    *pressure /= ( float ) ALTITUDE5_ADC_NUM_OF_MEASURE;
    *pressure /= ALTITUDE5_VDD_5000_mV;
    *pressure -= ALTITUDE5_OFFSET_B;
    *pressure /= ALTITUDE5_OFFSET_A;
    *pressure *= ALTITUDE5_CONVERT_kPa_TO_hPa;
    
    return err_flag;
}

err_t altitude5_get_altitude ( altitude5_t *ctx, float *altitude ) 
{
    float tmp;
    float pressure;
    
    err_t err_flag = altitude5_get_pressure( ctx, &pressure );
    
    tmp = ctx->sea_lvl_pressure;
    tmp /= pressure;
    
    *altitude = pow( tmp, ALTITUDE5_ISA_MODEL_PARAM );
    *altitude -= ALTITUDE5_CONVERT_NEG;
    
    tmp = ctx->temperature;
    tmp += ALTITUDE5_TEMP_CONVERT_C_TO_K;
    
    *altitude *= tmp;
    *altitude /= ALTITUDE5_STANDARD_TEMPERATURE_LAPSE_RATE;
    
    return err_flag;
}

static err_t altitude5_read_an_pin_value ( altitude5_t *ctx, uint16_t *data_out ) 
{
    err_t err_flag = analog_in_read( &ctx->adc, data_out );
    *data_out += ctx->offset;
    
    return err_flag;
}

static err_t altitude5_read_adc_value ( altitude5_t *ctx, uint16_t *read_adc ) 
{
    uint8_t rx_buf[ 2 ];
    uint16_t adc_val;
    
    err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );

    adc_val = rx_buf[ 0 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 1 ];
    adc_val &= ALTITUDE5_DATA_12_BIT;
    
    *read_adc = adc_val;
    *read_adc += ctx->offset;

    return err_flag;
}

static void dev_measurement_delay ( void ) 
{
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END
