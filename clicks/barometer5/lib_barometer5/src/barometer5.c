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
 * @file barometer5.c
 * @brief Barometer 5 Click Driver.
 */

#include "barometer5.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                                         0x00

/**
 * @brief Altitude, pressure and temperature calculation data.
 * @details Definition of altitude, pressure and temperature calculation data.
 */
#define BAROMETER5_CONVERT_Pa_TO_mbar                  100
#define BAROMETER5_TEMP_CONVERT_C_TO_K                 273.15
#define BAROMETER5_ISA_MODEL_PARAM                       0.1902225603956629
#define BAROMETER5_CONVERT_NEG                           1
#define BAROMETER5_STANDARD_TEMPERATURE_LAPSE_RATE       0.0065
#define BAROMETER5_TEMPERATURE_COEFF                  2000
#define BAROMETER5_6_BIT_DATA                           64
#define BAROMETER5_7_BIT_DATA                          128
#define BAROMETER5_8_BIT_DATA                          256
#define BAROMETER5_15_BIT_DATA                       32768
#define BAROMETER5_16_BIT_DATA                       65536
#define BAROMETER5_17_BIT_DATA                      131072
#define BAROMETER5_21_BIT_DATA                     2097152
#define BAROMETER5_23_BIT_DATA                     8388608
#define BAROMETER5_TEMPERATURE_CONV_TO_C               100
#define BAROMETER5_STANDARD_ATMOSPHERE_mbar           1013.25

/**
 * @brief Barometer 5 ADC conversion delay function.
 * @details This function executes a ADC conversion delay of the 10 milliseconds.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_adc_conversion_delay ( void );

/**
 * @brief Barometer 5 reset delay function.
 * @details This function executes a reset - reload delay of the 3 milliseconds.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_reset_reload_delay ( void );

void barometer5_cfg_setup ( barometer5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BAROMETER5_SET_DEV_ADDR;
    
    cfg->sea_level_pressure = BAROMETER5_STANDARD_ATMOSPHERE_mbar;
}

err_t barometer5_init ( barometer5_t *ctx, barometer5_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->sea_lvl_pressure = cfg->sea_level_pressure;

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

    return I2C_MASTER_SUCCESS;
}

err_t barometer5_default_cfg ( barometer5_t *ctx ) 
{
    err_t err_flag = barometer5_sw_reset( ctx );
    
    err_flag |= barometer5_get_calibration_data( ctx );
    
    barometer5_set_ratio ( ctx, BAROMETER5_RATIO_2048, BAROMETER5_RATIO_2048 );

    return err_flag;
}

err_t barometer5_generic_write ( barometer5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t barometer5_generic_read ( barometer5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t barometer5_set_command ( barometer5_t *ctx, uint8_t cmd ) 
{
    return barometer5_generic_write( ctx, cmd, DUMMY, DUMMY );
}

err_t barometer5_set_ratio ( barometer5_t *ctx, uint8_t temp_ratio, uint8_t press_ratio )
{
    if ( ( temp_ratio > BAROMETER5_RATIO_4096 ) || ( press_ratio > BAROMETER5_RATIO_4096 ) )
    {
        return BAROMETER5_ERROR;
    }
   
    ctx->ratio_temp = temp_ratio;
    ctx->ratio_press = press_ratio;

    return BAROMETER5_OK;
}

err_t barometer5_sw_reset ( barometer5_t *ctx )
{
    err_t err_flag = barometer5_set_command( ctx, BAROMETER5_CMD_RESET );
    dev_reset_reload_delay( );
    
    return err_flag;
}

err_t barometer5_get_calibration_data ( barometer5_t *ctx )
{
    uint8_t tmp_data;
    uint16_t prom_data[ 6 ];
    uint8_t data_out[ 2 ];
    err_t err_flag = BAROMETER5_OK;

    for ( uint8_t n_cnt = 1; n_cnt < 7; n_cnt++ )
    {
        tmp_data = BAROMETER5_CMD_PROM_READ_START | ( n_cnt << 1 );
        err_flag |= barometer5_generic_read( ctx, tmp_data, data_out, 2 );
        dev_adc_conversion_delay();
        
        prom_data[ n_cnt - 1 ] = data_out[ 0 ];
        prom_data[ n_cnt - 1 ] <<= 8;
        prom_data[ n_cnt - 1 ] |= data_out[ 1 ];
    } 
    
    ctx->press_sens_c1     = prom_data[ 0 ];
    ctx->press_off_c2      = prom_data[ 1 ];
    ctx->press_tcs_c3      = prom_data[ 2 ];
    ctx->press_tco_c4      = prom_data[ 3 ];
    ctx->press_tref_c5     = prom_data[ 4 ];
    ctx->press_tempsens_c6 = prom_data[ 5 ];

    return err_flag;
}

err_t barometer5_get_raw_data ( barometer5_t *ctx, uint32_t *temp_data, uint32_t *press_data )
{
    uint8_t buff_data[ 3 ];
        
    err_t err_flag = barometer5_set_command( ctx, BAROMETER5_CMD_CONV_D2_OSR_256 | ctx->ratio_temp );
    dev_adc_conversion_delay( );
    err_flag |= barometer5_generic_read( ctx, BAROMETER5_CMD_ADC_READ, buff_data, 3 );
    
    *temp_data = buff_data[ 0 ];
    *temp_data <<= 8;
    *temp_data |= buff_data[ 1 ];
    *temp_data <<= 8;
    *temp_data |= buff_data[ 2 ];
    
    err_flag |= barometer5_set_command( ctx, BAROMETER5_CMD_CONV_D1_OSR_256 | ctx->ratio_press );
    dev_adc_conversion_delay( );
    err_flag |= barometer5_generic_read( ctx, DUMMY, buff_data, 3 );
    
    *press_data = buff_data[ 0 ];
    *press_data <<= 8;
    *press_data |= buff_data[ 1 ];
    *press_data <<= 8;
    *press_data |= buff_data[ 2 ];
    
    return err_flag;
}

err_t barometer5_get_temperature ( barometer5_t *ctx, float *temperature )
{
    uint32_t temp_data;
    uint32_t press_data;
    float dT;
    
    err_t err_flag = barometer5_get_raw_data( ctx, &temp_data, &press_data );
    
    *temperature = BAROMETER5_TEMPERATURE_COEFF;
    dT = ( float ) temp_data;
    dT -= ( float ) ctx->press_tref_c5 * BAROMETER5_8_BIT_DATA;
    *temperature += dT * ( float ) ctx->press_tempsens_c6 / BAROMETER5_23_BIT_DATA;
    *temperature /= BAROMETER5_TEMPERATURE_CONV_TO_C;
    
    return err_flag;
}

err_t barometer5_get_pressure ( barometer5_t *ctx, float *pressure )
{
    uint32_t temp_data;
    uint32_t press_data;
    float dT;
    float off;
    float sens;
    
    err_t err_flag = barometer5_get_raw_data( ctx, &temp_data, &press_data );
    
    dT = ( float ) temp_data;
    dT -= ( float ) ctx->press_tref_c5 * BAROMETER5_8_BIT_DATA;
    
    off = ( float )ctx->press_off_c2 * BAROMETER5_17_BIT_DATA;
    off += ( ( float )ctx->press_tco_c4 * dT ) / BAROMETER5_6_BIT_DATA;
    
    sens = ( float )ctx->press_sens_c1 * BAROMETER5_16_BIT_DATA;
    sens += ( ( float )ctx->press_tcs_c3 * dT ) / BAROMETER5_7_BIT_DATA;
    
    *pressure = ( float ) press_data;
    *pressure *= sens;
    *pressure /= BAROMETER5_21_BIT_DATA;
    *pressure -= off;
    *pressure /= BAROMETER5_15_BIT_DATA;
    *pressure /= BAROMETER5_CONVERT_Pa_TO_mbar;
    
    return err_flag;
}

err_t barometer5_calculate_altitude ( barometer5_t *ctx, float *altitude )
{
    float tmp;
    float temperature;
    float pressure;
    
    err_t err_flag = barometer5_get_temperature ( ctx, &temperature );
    
    err_flag |= barometer5_get_pressure ( ctx, &pressure );
    
    tmp = ctx->sea_lvl_pressure;
    tmp /= pressure;
    
    *altitude = pow( tmp, BAROMETER5_ISA_MODEL_PARAM );
    *altitude -= BAROMETER5_CONVERT_NEG;
    
    tmp = temperature;
    tmp += BAROMETER5_TEMP_CONVERT_C_TO_K;
    
    *altitude *= tmp;
    *altitude /= BAROMETER5_STANDARD_TEMPERATURE_LAPSE_RATE;
    
    return err_flag;
}

err_t barometer5_get_data ( barometer5_t *ctx, float *temperature, float *pressure )
{   
    err_t err_flag = barometer5_get_temperature ( ctx, temperature );
    
    err_flag |= barometer5_get_pressure ( ctx, pressure );
    
    return err_flag;
}

static void dev_adc_conversion_delay ( void ) 
{
    Delay_10ms( );
}

static void dev_reset_reload_delay ( void ) 
{
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END
