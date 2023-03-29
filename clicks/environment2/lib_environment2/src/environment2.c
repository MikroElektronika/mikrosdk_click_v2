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
 * @file environment2.c
 * @brief Environment 2 Click Driver.
 */

#include "environment2.h"

/**
 * @brief Environment 2 the maximum value of fix16_t.
 *
 * @endcode
 */
#define FIX16_MAXIMUM         0x7FFFFFFF

/**
 * @brief Environment 2 the minimum value of fix16_t.
 *
 * @endcode
 */
#define FIX16_MINIMUM         0x80000000

/**
 * @brief Environment 2 the value used to indicate overflows when 
 * FIXMATH_NO_OVERFLOW is not specified.
 *
 * @endcode
 */
#define FIX16_OVERFLOW        0x80000000

/**
 * @brief Environment 2 fix16_t value of 1.
 *
 * @endcode
 */
#define FIX16_ONE             0x00010000

static environment2_voc_algorithm_params voc_algorithm_params;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static fix16_t dev_voc_algorithm_mox_model_process ( environment2_voc_algorithm_params* params, fix16_t sraw );

static fix16_t dev_voc_algorithm_sigmoid_scaled_process ( environment2_voc_algorithm_params *params, fix16_t sample );

static fix16_t dev_voc_algorithm_adaptive_lowpass_process ( environment2_voc_algorithm_params *params, fix16_t sample );

static fix16_t dev_voc_algorithm_mean_variance_estimator_sigmoid_process ( environment2_voc_algorithm_params *params, fix16_t sample );

static void dev_voc_algorithm_mean_variance_estimator_calculate_gamma ( environment2_voc_algorithm_params *params, fix16_t voc_index_from_prior );

static void dev_voc_algorithm_mean_variance_estimator_process ( environment2_voc_algorithm_params *params, fix16_t sraw, fix16_t voc_index_from_prior );

static void dev_voc_algorithm_mox_model_set_parameters ( environment2_voc_algorithm_params *params, fix16_t sraw_std, fix16_t sraw_mean );

static void dev_voc_algorithm_mean_variance_estimator_set_parameters ( environment2_voc_algorithm_params *params, 
                                                                       fix16_t std_initial, 
                                                                       fix16_t tau_mean_variance_hours, 
                                                                       fix16_t gating_max_duration_minutes );

static void dev_voc_algorithm_mean_variance_estimator_sigmoid_set_parameters ( environment2_voc_algorithm_params *params, fix16_t l_val, fix16_t x0_val, fix16_t k_val );

static void dev_voc_algorithm_mean_variance_estimator_sigmoid_init ( environment2_voc_algorithm_params *params );

static void dev_voc_algorithm_mean_variance_estimator_init_instances ( environment2_voc_algorithm_params *params );

static void dev_voc_algorithm_mean_variance_estimator_init ( environment2_voc_algorithm_params *params );

static void dev_voc_algorithm_mox_model_init ( environment2_voc_algorithm_params *params );

static fix16_t dev_voc_algorithm_mean_variance_estimator_get_std ( environment2_voc_algorithm_params *params );

static fix16_t dev_voc_algorithm_mean_variance_estimator_get_mean ( environment2_voc_algorithm_params *params );

static void dev_voc_algorithm_sigmoid_scaled_set_parameters ( environment2_voc_algorithm_params *params, fix16_t offset );

static void dev_voc_algorithm_sigmoid_scaled_init ( environment2_voc_algorithm_params *params );

static void dev_voc_algorithm_adaptive_lowpass_set_parameters ( environment2_voc_algorithm_params *params );

static void dev_voc_algorithm_adaptive_lowpass_init ( environment2_voc_algorithm_params *params );

static void dev_voc_algorithm_init_instances ( environment2_voc_algorithm_params *params );

inline fix16_t fix16_from_int ( int32_t a ) {
    return a * FIX16_ONE;
}

inline int32_t fix16_cast_to_int ( fix16_t a ) {
    return ( a >> 16 );
}

/**
 * @brief Environment 2 multiplies the two given fix16_t's function.
 * @details Multiplies the two given fix16_t's and returns the result.
 * @return Multiplies two fix16_t's.
 *
 * @note None.
 *
 * @endcode
 */
static fix16_t dev_fix16_mul ( fix16_t in_arg0, fix16_t in_arg1 );

/**
 * @brief Environment 2 divides the first given fix16_t by the second function.
 * @details Divides the first given fix16_t by the second and returns the result.
 * @return Division quotient.
 *
 * @note None.
 *
 * @endcode
 */
static fix16_t dev_fix16_div ( fix16_t in_arg0, fix16_t in_arg1 );

/**
 * @brief Environment 2 square root function.
 * @details Returns the square root of the given fix16_t.
 * @return Square root.
 *
 * @note None.
 *
 * @endcode
 */
static fix16_t dev_fix16_sqrt ( fix16_t in_value );

/**
 * @brief Environment 2 exponent function.
 * @details Returns the exponent (e^) of the given fix16_t.
 * @return Exponent.
 *
 * @note None.
 *
 * @endcode
 */
static fix16_t dev_fix16_exp ( fix16_t in_value );

/**
 * @brief Environment 2 duration of raw data measurement delay.
 * @details Reset delay for 30 milliseconds.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
static void dev_measurement_duration_raw_delay ( void );

/**
 * @brief Environment 2 duration of self-test delay.
 * @details Reset delay for 250 milliseconds.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
static void dev_measurement_duration_test_delay ( void );

/**
 * @brief Environment 2 duration of temperature and relative humidity data measurement delay.
 * @details Reset delay for 10 milliseconds.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
static void dev_measurement_duration_temp_hum_delay ( void );

/**
 * @brief Environment 2 CRC checksum calculation.
 * @details Generated by the CRC algorithm according to the 
 * properties as stated.
 * @return CRC checksum.
 *
 * @note None.
 *
 * @endcode
 */
static uint8_t dev_calc_crc ( uint8_t data_0, uint8_t data_1 );

/**
 * @brief Environment 2 set device slave address.
 * @details This function sets I2C address of the subordinate I2C device.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[in] select_device : 
 *         @li @c 0x00 ( ENVIRONMENT2_SEL_SGP40 ) - Sets I2C address of the SGP40 Sensor,
 *         @li @c 0x01 ( ENVIRONMENT2_SEL_SHT40 ) - Sets I2C address of the SHT40 Sensor.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
static err_t dev_set_device_slave_address ( environment2_t *ctx, uint8_t select_device );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void environment2_cfg_setup ( environment2_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ENVIRONMENT2_SGP40_SET_DEV_ADDR;
}

err_t environment2_init ( environment2_t *ctx, environment2_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t environment2_generic_write ( environment2_t *ctx, uint8_t select_device, uint16_t cmd, uint8_t *tx_buf ) {
    uint8_t tx_buf[ 2 ];
    err_t status;
    
    status = ENVIRONMENT2_ERROR;
    
    if ( select_device == ENVIRONMENT2_SEL_SGP40 ) {
        if ( dev_set_device_slave_address( ctx, ENVIRONMENT2_SEL_SGP40 ) == ENVIRONMENT2_OK ) {
            tx_buf[ 0 ] = ( uint8_t ) ( cmd >> 8 );
            tx_buf[ 1 ] = ( uint8_t ) cmd;
            
            i2c_master_write( &ctx->i2c, tx_buf, 2 );
            
            status = ENVIRONMENT2_OK;
        }   
    }

    return status;
}

err_t environment2_generic_read ( environment2_t *ctx, uint8_t select_device, uint16_t cmd, uint8_t *rx_buf ) {
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 6 ];
    err_t status;
    
    status = ENVIRONMENT2_ERROR;
    
    if ( select_device == ENVIRONMENT2_SEL_SGP40 ) {
        tx_buf[ 0 ] = ( uint8_t ) ( cmd >> 8 );
        tx_buf[ 1 ] = ( uint8_t ) cmd;
        
        i2c_master_write( &ctx->i2c, tx_buf, 2 );
        dev_measurement_duration_test_delay( );
        i2c_master_read( &ctx->i2c, rx_buf, 3 ); 
        
        status = ENVIRONMENT2_OK;
    } else if ( select_device == ENVIRONMENT2_SEL_SHT40 ) {
        tx_buf[ 0 ] = ( uint8_t ) cmd;
        
        i2c_master_write( &ctx->i2c, tx_buf, 1 );
        dev_measurement_duration_temp_hum_delay( );
        i2c_master_read( &ctx->i2c, rx_buf, 6 ); 
        
        status = ENVIRONMENT2_OK;
    }
    
    return status;
}

err_t environment2_get_temp_hum ( environment2_t *ctx, float *humidity, float *temperature ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 6 ];
    uint16_t t_ticks;
    uint16_t rh_ticks;
    err_t status;
    
    status = ENVIRONMENT2_OK;

    tx_buf[ 0 ] = ENVIRONMENT2_SHT40_CMD_MEASURE_T_RH_HIGH_PRECISION;
    
    if ( dev_set_device_slave_address( ctx, ENVIRONMENT2_SEL_SHT40 ) == ENVIRONMENT2_OK ) {
        i2c_master_write( &ctx->i2c, tx_buf, 1 );
        dev_measurement_duration_temp_hum_delay( );
        i2c_master_read( &ctx->i2c, rx_buf, 6 );

        t_ticks = rx_buf[ 0 ];
        t_ticks <<= 8;
        t_ticks |= rx_buf[ 1 ];
    
        rh_ticks = rx_buf[ 3 ];
        rh_ticks <<= 8;
        rh_ticks |= rx_buf[ 4 ];

        *temperature = ( 175 * ( ( ( float ) t_ticks ) / 65535 ) ) - 45;
        *humidity = ( 125 * ( ( ( float ) rh_ticks ) / 65535 ) ) - 6;    
    } else {
        status = ENVIRONMENT2_ERROR;
    }
    
    return status;
}

err_t environment2_get_air_quality ( environment2_t *ctx, uint16_t *air_quality ) {
    uint8_t tx_buf[ 8 ];
    uint8_t rx_buf[ 3 ];
    uint16_t tmp_hum;
    uint16_t tmp_temp;
    float temperature;
    float humidity;
    uint16_t result;
    err_t status;
    
    status = ENVIRONMENT2_OK;
    
    environment2_get_temp_hum ( ctx, &humidity, &temperature );

    tx_buf[ 0 ] = ( uint8_t ) ( ENVIRONMENT2_SGP40_CMD_MEASURE_RAW >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) ENVIRONMENT2_SGP40_CMD_MEASURE_RAW;
    
    tmp_hum = ( uint16_t ) ( humidity * ( 65535.0 / 100.0 ) );
    
    tx_buf[ 2 ] = ( uint8_t ) ( tmp_hum >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) tmp_hum;
    tx_buf[ 4 ] = dev_calc_crc( tx_buf[ 2 ], tx_buf[ 3 ] );
    
    tmp_temp = ( uint16_t ) ( ( temperature + 45.0 ) * ( 65535.0 / 175.0 ) );
    
    tx_buf[ 5 ] = ( uint8_t ) ( tmp_temp >> 8 );
    tx_buf[ 6 ] = ( uint8_t ) tmp_temp;
    tx_buf[ 7 ] = dev_calc_crc( tx_buf[ 5 ], tx_buf[ 6 ] );
    
    if ( dev_set_device_slave_address( ctx, ENVIRONMENT2_SEL_SGP40 ) == ENVIRONMENT2_OK ) {
        i2c_master_write( &ctx->i2c, tx_buf, 8 );
        dev_measurement_duration_raw_delay( );
        i2c_master_read( &ctx->i2c, rx_buf, 3 );

        result = rx_buf[ 0 ];
        result <<= 8;
        result |= rx_buf[ 1 ];
        
        *air_quality = result;
    } else {
        status = ENVIRONMENT2_ERROR;    
    }

    return status;
}

uint16_t environment2_sgp40_measure_test ( environment2_t *ctx ) {
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 3 ];
    uint16_t result;

    tx_buf[ 0 ] = ( uint8_t ) ( ENVIRONMENT2_SGP40_CMD_MEASURE_TEST >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) ENVIRONMENT2_SGP40_CMD_MEASURE_TEST;
    
    if ( dev_set_device_slave_address( ctx, ENVIRONMENT2_SEL_SGP40 ) == ENVIRONMENT2_OK ) {
        i2c_master_write( &ctx->i2c, tx_buf, 2 );
        dev_measurement_duration_test_delay( );
        i2c_master_read( &ctx->i2c, rx_buf, 3 );

        result = rx_buf[ 0 ];
        result <<= 8;
        result |= rx_buf[ 1 ];    
    }

    return result;
}

err_t environment2_sgp40_heater_off ( environment2_t *ctx ) {
    uint8_t tx_buf[ 2 ];
    err_t status;
    
    status = ENVIRONMENT2_OK;

    tx_buf[ 0 ] = ( uint8_t ) ( ENVIRONMENT2_SGP40_CMD_HEATER_OFF >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) ENVIRONMENT2_SGP40_CMD_HEATER_OFF;
    
    if ( dev_set_device_slave_address( ctx, ENVIRONMENT2_SEL_SGP40 ) == ENVIRONMENT2_OK ) {
        i2c_master_write( &ctx->i2c, tx_buf, 2 );     
    } else {
        status = ENVIRONMENT2_ERROR;
    }
    
    return status;    
}

err_t environment2_sgp40_soft_reset ( environment2_t *ctx ) {
    uint8_t tx_buf[ 2 ];
    err_t status;
    
    status = ENVIRONMENT2_OK;

    tx_buf[ 0 ] = ( uint8_t ) ( ENVIRONMENT2_SGP40_CMD_SOFT_RESET >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) ENVIRONMENT2_SGP40_CMD_SOFT_RESET;
    
    if ( dev_set_device_slave_address( ctx, ENVIRONMENT2_SEL_SGP40 ) == ENVIRONMENT2_OK ) {
        i2c_master_write( &ctx->i2c, tx_buf, 2 );    
    } else {
        status = ENVIRONMENT2_ERROR;
    }
    
    return status; 
}

err_t environment2_voc_algorithm_configuration ( environment2_voc_algorithm_params* params ) {

    params->mVoc_Index_Offset = F16(VocAlgorithm_VOC_INDEX_OFFSET_DEFAULT);
    params->mTau_Mean_Variance_Hours = F16( VocAlgorithm_TAU_MEAN_VARIANCE_HOURS );
    params->mGating_Max_Duration_Minutes = F16( VocAlgorithm_GATING_MAX_DURATION_MINUTES );
    params->mSraw_Std_Initial = F16( VocAlgorithm_SRAW_STD_INITIAL );
    params->mUptime = F16( 0. );
    params->mSraw = F16( 0. );
    params->mVoc_Index = 0;
    dev_voc_algorithm_init_instances( params );
    
    return ENVIRONMENT2_OK;
}

err_t environment2_config_sensors ( void ) {
    environment2_voc_algorithm_configuration( &voc_algorithm_params );
    
    return ENVIRONMENT2_OK;
}

err_t environment2_voc_algorithm_process ( environment2_voc_algorithm_params *params, int32_t sraw, int32_t *voc_index ) {
    if ( ( params->mUptime <= F16( VocAlgorithm_INITIAL_BLACKOUT ) ) ) {
        params->mUptime = ( params->mUptime + F16( VocAlgorithm_SAMPLING_INTERVAL ) );
    } else {
        if ( ( ( sraw > 0 ) && ( sraw < 65000 ) ) ) {
            if ( ( sraw < 20001 ) ) {
                sraw = 20001;
            } else if ( ( sraw > 52767 ) ) {
                sraw = 52767;
            }
            params->mSraw = ( fix16_from_int( ( sraw - 20000 ) ) );
        }
        params->mVoc_Index = dev_voc_algorithm_mox_model_process( params, params->mSraw );
        params->mVoc_Index = dev_voc_algorithm_sigmoid_scaled_process( params, params->mVoc_Index );
        params->mVoc_Index = dev_voc_algorithm_adaptive_lowpass_process( params, params->mVoc_Index );
        
        if ( ( params->mVoc_Index < F16( 0.5 ) ) ) {
            params->mVoc_Index = F16( 0.5 );
        }
        
        if ( ( params->mSraw > F16( 0. ) ) ) {
            dev_voc_algorithm_mean_variance_estimator_process( params, params->mSraw, params->mVoc_Index );
            dev_voc_algorithm_mox_model_set_parameters( params, dev_voc_algorithm_mean_variance_estimator_get_std( params ), dev_voc_algorithm_mean_variance_estimator_get_mean( params ));
        }
    }
    
    *voc_index = ( fix16_cast_to_int( ( params->mVoc_Index + F16( 0.5 ) ) ) );
    
    return ENVIRONMENT2_OK;
}


err_t environment2_measure_voc_index_with_rh_t (environment2_t *ctx, int32_t *voc_index, int32_t *relative_humidity, int32_t *temperature ) {
    int32_t int_temperature, int_humidity;
    uint16_t sraw;   
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 6 ];
    uint16_t t_ticks;
    uint16_t rh_ticks;
    err_t status;
    
    status = ENVIRONMENT2_OK;

    tx_buf[ 0 ] = ENVIRONMENT2_SHT40_CMD_MEASURE_T_RH_HIGH_PRECISION;
    
    if ( dev_set_device_slave_address( ctx, ENVIRONMENT2_SEL_SHT40 ) == ENVIRONMENT2_OK ) {
        i2c_master_write( &ctx->i2c, tx_buf, 1 );
        dev_measurement_duration_temp_hum_delay( );
        i2c_master_read( &ctx->i2c, rx_buf, 6 );

        t_ticks = rx_buf[ 0 ];
        t_ticks <<= 8;
        t_ticks |= rx_buf[ 1 ];
    
        rh_ticks = rx_buf[ 3 ];
        rh_ticks <<= 8;
        rh_ticks |= rx_buf[ 4 ];
        
        *temperature = ( ( 21875 * ( int32_t )t_ticks) >> 13 ) - 45000;
        *relative_humidity = ( ( 12500 * ( int32_t )rh_ticks ) >> 13 );

       
    } else {
        status = ENVIRONMENT2_ERROR;
    }
    
    environment2_get_air_quality( ctx, &sraw );
    dev_measurement_duration_raw_delay( );

    environment2_voc_algorithm_process(&voc_algorithm_params, sraw, voc_index);
    return ENVIRONMENT2_OK;
}

err_t environment2_get_voc_index ( environment2_t *ctx, int32_t *voc_index ) {
    int32_t int_temperature, int_humidity;
    uint16_t sraw;   
    err_t status;
       
    status = environment2_get_air_quality( ctx, &sraw );
    dev_measurement_duration_raw_delay( );

    environment2_voc_algorithm_process(&voc_algorithm_params, sraw, voc_index);
    return ENVIRONMENT2_OK;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static fix16_t dev_voc_algorithm_mox_model_process ( environment2_voc_algorithm_params *params, fix16_t sraw ) {

    return ( dev_fix16_mul( ( dev_fix16_div( ( sraw - params->m_Mox_Model__Sraw_Mean ), 
                                             ( -( params->m_Mox_Model__Sraw_Std + F16( VocAlgorithm_SRAW_STD_BONUS ) ) ) ) ), 
                                            F16(VocAlgorithm_VOC_INDEX_GAIN ) ) );
}

static fix16_t dev_voc_algorithm_sigmoid_scaled_process ( environment2_voc_algorithm_params *params, fix16_t sample ) {
    fix16_t x;
    fix16_t shift;

    x = ( dev_fix16_mul( F16( VocAlgorithm_SIGMOID_K ), ( sample - F16( VocAlgorithm_SIGMOID_X0 ) ) ) );
    if ( ( x < F16( -50. ) ) ) {
        return F16( VocAlgorithm_SIGMOID_L );
    } else if ( ( x > F16( 50. ) ) ) {
        return F16( 0. );
    } else {
        if ( ( sample >= F16( 0. ) ) ) {
            shift = ( dev_fix16_div( ( F16( VocAlgorithm_SIGMOID_L ) - ( dev_fix16_mul( F16( 5. ), params->m_Sigmoid_Scaled__Offset ) ) ), F16( 4. ) ) );
            return ( ( dev_fix16_div( ( F16(VocAlgorithm_SIGMOID_L ) + shift ), ( F16( 1. ) + dev_fix16_exp( x ) ) ) ) - shift );
        } else {
            return ( dev_fix16_mul( ( dev_fix16_div( params->m_Sigmoid_Scaled__Offset, 
                                                     F16( VocAlgorithm_VOC_INDEX_OFFSET_DEFAULT ) ) ), 
                                                    ( dev_fix16_div( F16( VocAlgorithm_SIGMOID_L ),
                                                    ( F16(1.) + dev_fix16_exp( x ) ) ) ) ) );
        }
    }
}

static fix16_t dev_voc_algorithm_adaptive_lowpass_process ( environment2_voc_algorithm_params *params, fix16_t sample ) {
    fix16_t abs_delta;
    fix16_t F1;
    fix16_t tau_a;
    fix16_t a3;

    if ( ( params->m_Adaptive_Lowpass___Initialized == false ) ) {
        params->m_Adaptive_Lowpass___X1 = sample;
        params->m_Adaptive_Lowpass___X2 = sample;
        params->m_Adaptive_Lowpass___X3 = sample;
        params->m_Adaptive_Lowpass___Initialized = true;
    }
    params->m_Adaptive_Lowpass___X1 = ( ( dev_fix16_mul( ( F16( 1. ) - params->m_Adaptive_Lowpass__A1 ),
                                                         params->m_Adaptive_Lowpass___X1)) + ( dev_fix16_mul( params->m_Adaptive_Lowpass__A1, sample ) ) );
    params->m_Adaptive_Lowpass___X2 = ( ( dev_fix16_mul( ( F16( 1. ) - params->m_Adaptive_Lowpass__A2 ),
                                                         params->m_Adaptive_Lowpass___X2 ) ) + ( dev_fix16_mul( params->m_Adaptive_Lowpass__A2, sample ) ) );
    abs_delta = ( params->m_Adaptive_Lowpass___X1 - params->m_Adaptive_Lowpass___X2 );
    if ( ( abs_delta < F16( 0. ) ) ) {
        abs_delta = ( -abs_delta );
    }
    F1 = dev_fix16_exp( ( dev_fix16_mul( F16( VocAlgorithm_LP_ALPHA ), abs_delta ) ) );
    tau_a = ( ( dev_fix16_mul( F16( ( VocAlgorithm_LP_TAU_SLOW - VocAlgorithm_LP_TAU_FAST ) ), F1 ) ) + F16( VocAlgorithm_LP_TAU_FAST ) );
    a3 = ( dev_fix16_div( F16( VocAlgorithm_SAMPLING_INTERVAL ), ( F16( VocAlgorithm_SAMPLING_INTERVAL ) + tau_a ) ) );
    params->m_Adaptive_Lowpass___X3 = ( ( dev_fix16_mul( ( F16( 1. ) - a3 ), params->m_Adaptive_Lowpass___X3 ) ) + ( dev_fix16_mul( a3, sample ) ) );
    
    return params->m_Adaptive_Lowpass___X3;
}

static fix16_t dev_voc_algorithm_mean_variance_estimator_sigmoid_process ( environment2_voc_algorithm_params *params, fix16_t sample ) {
    fix16_t x;

    x = ( dev_fix16_mul( params->m_Mean_Variance_Estimator___Sigmoid__K, ( sample - params->m_Mean_Variance_Estimator___Sigmoid__X0 ) ) );
    if ( ( x < F16( -50. ) ) ) {
        return params->m_Mean_Variance_Estimator___Sigmoid__L;
    } else if ( ( x > F16( 50. ) ) ) {
        return F16( 0. );
    } else {
        return ( dev_fix16_div( params->m_Mean_Variance_Estimator___Sigmoid__L, ( F16( 1. ) + dev_fix16_exp( x ) ) ) );
    }
}

static void dev_voc_algorithm_mean_variance_estimator_calculate_gamma ( environment2_voc_algorithm_params *params, fix16_t voc_index_from_prior ) {
    fix16_t uptime_limit;
    fix16_t sigmoid_gamma_mean;
    fix16_t gamma_mean;
    fix16_t gating_threshold_mean;
    fix16_t sigmoid_gating_mean;
    fix16_t sigmoid_gamma_variance;
    fix16_t gamma_variance;
    fix16_t gating_threshold_variance;
    fix16_t sigmoid_gating_variance;

    uptime_limit = F16( ( VocAlgorithm_MEAN_VARIANCE_ESTIMATOR__FIX16_MAX - VocAlgorithm_SAMPLING_INTERVAL ) );
    if ( ( params->m_Mean_Variance_Estimator___Uptime_Gamma < uptime_limit ) ) {
        params->m_Mean_Variance_Estimator___Uptime_Gamma = ( params->m_Mean_Variance_Estimator___Uptime_Gamma + F16( VocAlgorithm_SAMPLING_INTERVAL ) );
    }
    if ( ( params->m_Mean_Variance_Estimator___Uptime_Gating < uptime_limit ) ) {
        params->m_Mean_Variance_Estimator___Uptime_Gating = ( params->m_Mean_Variance_Estimator___Uptime_Gating + F16( VocAlgorithm_SAMPLING_INTERVAL ) );
    }
    dev_voc_algorithm_mean_variance_estimator_sigmoid_set_parameters( params, F16( 1. ), F16( VocAlgorithm_INIT_DURATION_MEAN ), F16( VocAlgorithm_INIT_TRANSITION_MEAN ) );
    sigmoid_gamma_mean = dev_voc_algorithm_mean_variance_estimator_sigmoid_process( params, params->m_Mean_Variance_Estimator___Uptime_Gamma );
    gamma_mean = ( params->m_Mean_Variance_Estimator___Gamma + ( dev_fix16_mul( ( params->m_Mean_Variance_Estimator___Gamma_Initial_Mean - params->m_Mean_Variance_Estimator___Gamma ),
                                                                                sigmoid_gamma_mean ) ) );
    gating_threshold_mean = ( F16( VocAlgorithm_GATING_THRESHOLD ) + ( dev_fix16_mul( F16( ( VocAlgorithm_GATING_THRESHOLD_INITIAL - VocAlgorithm_GATING_THRESHOLD ) ),
                                                                                      dev_voc_algorithm_mean_variance_estimator_sigmoid_process( params, params->m_Mean_Variance_Estimator___Uptime_Gating ) ) ) );
    dev_voc_algorithm_mean_variance_estimator_sigmoid_set_parameters( params, F16( 1. ), gating_threshold_mean, F16( VocAlgorithm_GATING_THRESHOLD_TRANSITION ) );
    sigmoid_gating_mean = dev_voc_algorithm_mean_variance_estimator_sigmoid_process( params, voc_index_from_prior );
    params->m_Mean_Variance_Estimator__Gamma_Mean = ( dev_fix16_mul( sigmoid_gating_mean, gamma_mean ) );
    dev_voc_algorithm_mean_variance_estimator_sigmoid_set_parameters( params, F16( 1. ), F16( VocAlgorithm_INIT_DURATION_VARIANCE ), F16( VocAlgorithm_INIT_TRANSITION_VARIANCE ) );
    sigmoid_gamma_variance = dev_voc_algorithm_mean_variance_estimator_sigmoid_process( params, params->m_Mean_Variance_Estimator___Uptime_Gamma );
    gamma_variance = ( params->m_Mean_Variance_Estimator___Gamma + ( dev_fix16_mul( ( params->m_Mean_Variance_Estimator___Gamma_Initial_Variance - 
                                                                                      params->m_Mean_Variance_Estimator___Gamma ),
                                                                   ( sigmoid_gamma_variance - sigmoid_gamma_mean ) ) ) );
    gating_threshold_variance = ( F16( VocAlgorithm_GATING_THRESHOLD ) + ( dev_fix16_mul( F16( ( VocAlgorithm_GATING_THRESHOLD_INITIAL - VocAlgorithm_GATING_THRESHOLD ) ),
                                                                                          dev_voc_algorithm_mean_variance_estimator_sigmoid_process( params, params->m_Mean_Variance_Estimator___Uptime_Gating ) ) ) );
    dev_voc_algorithm_mean_variance_estimator_sigmoid_set_parameters( params, F16( 1. ), gating_threshold_variance, F16( VocAlgorithm_GATING_THRESHOLD_TRANSITION ) );
    sigmoid_gating_variance = dev_voc_algorithm_mean_variance_estimator_sigmoid_process( params, voc_index_from_prior );
    params->m_Mean_Variance_Estimator__Gamma_Variance = ( dev_fix16_mul( sigmoid_gating_variance, gamma_variance ) );
    params->m_Mean_Variance_Estimator___Gating_Duration_Minutes = ( params->m_Mean_Variance_Estimator___Gating_Duration_Minutes + 
                                                                   ( dev_fix16_mul( F16( ( VocAlgorithm_SAMPLING_INTERVAL / 60.) ), 
                                                                   ( ( dev_fix16_mul( ( F16( 1. ) - sigmoid_gating_mean ), 
                                                                       F16( ( 1. + VocAlgorithm_GATING_MAX_RATIO ) ) ) ) - F16( VocAlgorithm_GATING_MAX_RATIO ) ) ) ) );
    if ( ( params->m_Mean_Variance_Estimator___Gating_Duration_Minutes < F16( 0. ) ) ) {
        params->m_Mean_Variance_Estimator___Gating_Duration_Minutes = F16( 0. );
    }
    if ( ( params->m_Mean_Variance_Estimator___Gating_Duration_Minutes > params->m_Mean_Variance_Estimator__Gating_Max_Duration_Minutes ) ) {
        params->m_Mean_Variance_Estimator___Uptime_Gating = F16( 0. );
    }
}

static void dev_voc_algorithm_mean_variance_estimator_process ( environment2_voc_algorithm_params *params, fix16_t sraw, fix16_t voc_index_from_prior ) {
    fix16_t delta_sgp;
    fix16_t c;
    fix16_t additional_scaling;

    if ( ( params->m_Mean_Variance_Estimator___Initialized == false ) ) {
        params->m_Mean_Variance_Estimator___Initialized = true;
        params->m_Mean_Variance_Estimator___Sraw_Offset = sraw;
        params->m_Mean_Variance_Estimator___Mean = F16( 0. );
    } else {
        if ( ( ( params->m_Mean_Variance_Estimator___Mean >= F16( 100. ) ) || ( params->m_Mean_Variance_Estimator___Mean <= F16( -100. ) ) ) ) {
            params->m_Mean_Variance_Estimator___Sraw_Offset = ( params->m_Mean_Variance_Estimator___Sraw_Offset + params->m_Mean_Variance_Estimator___Mean );
            params->m_Mean_Variance_Estimator___Mean = F16( 0. );
        }
        sraw = ( sraw - params->m_Mean_Variance_Estimator___Sraw_Offset );
        dev_voc_algorithm_mean_variance_estimator_calculate_gamma( params, voc_index_from_prior );
        delta_sgp = ( dev_fix16_div( ( sraw - params->m_Mean_Variance_Estimator___Mean ), F16( VocAlgorithm_MEAN_VARIANCE_ESTIMATOR__GAMMA_SCALING ) ) );
        if ( ( delta_sgp < F16( 0. ) ) ) {
            c = ( params->m_Mean_Variance_Estimator___Std - delta_sgp );
        } else {
            c = ( params->m_Mean_Variance_Estimator___Std + delta_sgp );
        }
        additional_scaling = F16( 1. );
        if ( ( c > F16( 1440. ) ) ) {
            additional_scaling = F16( 4. );
        }
        params->m_Mean_Variance_Estimator___Std = ( dev_fix16_mul( dev_fix16_sqrt( ( dev_fix16_mul( additional_scaling, 
                                                                                                    ( F16( VocAlgorithm_MEAN_VARIANCE_ESTIMATOR__GAMMA_SCALING) - params->m_Mean_Variance_Estimator__Gamma_Variance ) ) ) ),
                                                                   dev_fix16_sqrt( ( ( dev_fix16_mul( params->m_Mean_Variance_Estimator___Std, 
                                                                                                      ( dev_fix16_div ( params->m_Mean_Variance_Estimator___Std, ( dev_fix16_mul (F16(VocAlgorithm_MEAN_VARIANCE_ESTIMATOR__GAMMA_SCALING), additional_scaling ) ) ) ) ) ) + ( dev_fix16_mul( ( dev_fix16_div( ( dev_fix16_mul( params->m_Mean_Variance_Estimator__Gamma_Variance, delta_sgp ) ), additional_scaling ) ), delta_sgp ) ) ) ) ) );
        params->m_Mean_Variance_Estimator___Mean = ( params->m_Mean_Variance_Estimator___Mean + ( dev_fix16_mul( params->m_Mean_Variance_Estimator__Gamma_Mean, delta_sgp ) ) );
    }
}

static void dev_voc_algorithm_mox_model_set_parameters ( environment2_voc_algorithm_params *params, fix16_t SRAW_STD, fix16_t SRAW_MEAN ) {
    params->m_Mox_Model__Sraw_Std = SRAW_STD;
    params->m_Mox_Model__Sraw_Mean = SRAW_MEAN;
}

static void dev_voc_algorithm_mean_variance_estimator_set_parameters ( environment2_voc_algorithm_params* params, 
                                                                    fix16_t std_initial, 
                                                                    fix16_t tau_mean_variance_hours, 
                                                                    fix16_t gating_max_duration_minutes ) {

    params->m_Mean_Variance_Estimator__Gating_Max_Duration_Minutes = gating_max_duration_minutes;
    params->m_Mean_Variance_Estimator___Initialized = false;
    params->m_Mean_Variance_Estimator___Mean = F16( 0. );
    params->m_Mean_Variance_Estimator___Sraw_Offset = F16( 0. );
    params->m_Mean_Variance_Estimator___Std = std_initial;
    params->m_Mean_Variance_Estimator___Gamma = ( dev_fix16_div( F16( ( VocAlgorithm_MEAN_VARIANCE_ESTIMATOR__GAMMA_SCALING * ( VocAlgorithm_SAMPLING_INTERVAL / 3600. ) ) ),
                                                ( tau_mean_variance_hours + F16( ( VocAlgorithm_SAMPLING_INTERVAL / 3600. ) ) ) ) );
    params->m_Mean_Variance_Estimator___Gamma_Initial_Mean = F16( ( ( VocAlgorithm_MEAN_VARIANCE_ESTIMATOR__GAMMA_SCALING * VocAlgorithm_SAMPLING_INTERVAL ) / 
                                                                    ( VocAlgorithm_TAU_INITIAL_MEAN + VocAlgorithm_SAMPLING_INTERVAL ) ) );
    params->m_Mean_Variance_Estimator___Gamma_Initial_Variance = F16( ( ( VocAlgorithm_MEAN_VARIANCE_ESTIMATOR__GAMMA_SCALING * VocAlgorithm_SAMPLING_INTERVAL ) /
                                                                        ( VocAlgorithm_TAU_INITIAL_VARIANCE + VocAlgorithm_SAMPLING_INTERVAL ) ) );
    params->m_Mean_Variance_Estimator__Gamma_Mean = F16( 0. );
    params->m_Mean_Variance_Estimator__Gamma_Variance = F16( 0. );
    params->m_Mean_Variance_Estimator___Uptime_Gamma = F16( 0. );
    params->m_Mean_Variance_Estimator___Uptime_Gating = F16( 0. );
    params->m_Mean_Variance_Estimator___Gating_Duration_Minutes = F16( 0. );
}

static void dev_voc_algorithm_mean_variance_estimator_sigmoid_set_parameters ( environment2_voc_algorithm_params *params, fix16_t L, fix16_t X0, fix16_t K ) {

    params->m_Mean_Variance_Estimator___Sigmoid__L = L;
    params->m_Mean_Variance_Estimator___Sigmoid__K = K;
    params->m_Mean_Variance_Estimator___Sigmoid__X0 = X0;
}

static void dev_voc_algorithm_mean_variance_estimator_sigmoid_init ( environment2_voc_algorithm_params* params ) {
    dev_voc_algorithm_mean_variance_estimator_sigmoid_set_parameters( params, F16( 0. ), F16( 0. ), F16( 0. ) );
}

static void dev_voc_algorithm_mean_variance_estimator_init_instances ( environment2_voc_algorithm_params* params ) {
    dev_voc_algorithm_mean_variance_estimator_sigmoid_init( params );
}

static void dev_voc_algorithm_mean_variance_estimator_init ( environment2_voc_algorithm_params* params ) {
    dev_voc_algorithm_mean_variance_estimator_set_parameters( params, F16( 0. ), F16( 0. ), F16( 0. ) );
    dev_voc_algorithm_mean_variance_estimator_init_instances( params );
}

static void dev_voc_algorithm_mox_model_init ( environment2_voc_algorithm_params* params ) {
    dev_voc_algorithm_mox_model_set_parameters( params, F16( 1. ), F16( 0. ) );
}

static fix16_t dev_voc_algorithm_mean_variance_estimator_get_std ( environment2_voc_algorithm_params* params ) {
    return params->m_Mean_Variance_Estimator___Std;
}

static fix16_t dev_voc_algorithm_mean_variance_estimator_get_mean ( environment2_voc_algorithm_params* params ) {
    return ( params->m_Mean_Variance_Estimator___Mean + params->m_Mean_Variance_Estimator___Sraw_Offset );
}

static void dev_voc_algorithm_sigmoid_scaled_set_parameters ( environment2_voc_algorithm_params* params, fix16_t offset ) {
    params->m_Sigmoid_Scaled__Offset = offset;
}

static void dev_voc_algorithm_sigmoid_scaled_init ( environment2_voc_algorithm_params* params ) {
    dev_voc_algorithm_sigmoid_scaled_set_parameters( params, F16( 0. ) );
}

static void dev_voc_algorithm_adaptive_lowpass_set_parameters ( environment2_voc_algorithm_params* params ) {
    params->m_Adaptive_Lowpass__A1 = F16( ( VocAlgorithm_SAMPLING_INTERVAL / ( VocAlgorithm_LP_TAU_FAST + VocAlgorithm_SAMPLING_INTERVAL ) ) );
    params->m_Adaptive_Lowpass__A2 = F16( ( VocAlgorithm_SAMPLING_INTERVAL / ( VocAlgorithm_LP_TAU_SLOW + VocAlgorithm_SAMPLING_INTERVAL ) ) );
    params->m_Adaptive_Lowpass___Initialized = false;
}

static void dev_voc_algorithm_adaptive_lowpass_init ( environment2_voc_algorithm_params *params ) {
    dev_voc_algorithm_adaptive_lowpass_set_parameters( params );
}

static void dev_voc_algorithm_init_instances ( environment2_voc_algorithm_params *params ) {
    dev_voc_algorithm_mean_variance_estimator_init( params );
    dev_voc_algorithm_mean_variance_estimator_set_parameters( params, params->mSraw_Std_Initial, params->mTau_Mean_Variance_Hours, params->mGating_Max_Duration_Minutes );
    dev_voc_algorithm_mox_model_init( params );
    dev_voc_algorithm_mox_model_set_parameters( params, dev_voc_algorithm_mean_variance_estimator_get_std( params ), dev_voc_algorithm_mean_variance_estimator_get_mean( params ) );
    dev_voc_algorithm_sigmoid_scaled_init( params );
    dev_voc_algorithm_sigmoid_scaled_set_parameters( params, params->mVoc_Index_Offset );
    dev_voc_algorithm_adaptive_lowpass_init( params );
    dev_voc_algorithm_adaptive_lowpass_set_parameters( params );
}

static fix16_t dev_fix16_mul ( fix16_t inArg0, fix16_t inArg1 ) {
    int32_t A = ( inArg0 >> 16 ), C = ( inArg1 >> 16 );
    uint32_t B = ( inArg0 & 0xFFFF ), D = ( inArg1 & 0xFFFF );
    int32_t AC = A * C;
    int32_t AD_CB = A * D + C * B;
    uint32_t BD = B * D;
    int32_t product_hi = AC + ( AD_CB >> 16 );
    uint32_t ad_cb_temp = AD_CB << 16;
    uint32_t product_lo = BD + ad_cb_temp;
    
    if ( product_lo < BD )
        product_hi++;

#ifndef FIXMATH_NO_OVERFLOW
    if ( product_hi >> 31 != product_hi >> 15 )
        return FIX16_OVERFLOW;
#endif

#ifdef FIXMATH_NO_ROUNDING
    return ( product_hi << 16 ) | ( product_lo >> 16 );
#else
    uint32_t product_lo_tmp = product_lo;
    product_lo -= 0x8000;
    product_lo -= ( uint32_t )product_hi >> 31;
    if ( product_lo > product_lo_tmp )
        product_hi--;

    fix16_t result = ( product_hi << 16 ) | ( product_lo >> 16 );
    result += 1;
    return result;
#endif
}

static fix16_t dev_fix16_div ( fix16_t a, fix16_t b ) {
    if ( b == 0 )
        return FIX16_MINIMUM;

    uint32_t remainder = ( a >= 0 ) ? a : ( -a );
    uint32_t divider = ( b >= 0 ) ? b : ( -b );

    uint32_t quotient = 0;
    uint32_t _bit = 0x10000;

    while ( divider < remainder ) {
        divider <<= 1;
        _bit <<= 1;
    }

#ifndef FIXMATH_NO_OVERFLOW
    if ( !_bit )
        return FIX16_OVERFLOW;
#endif

    if ( divider & 0x80000000 ) {
        if ( remainder >= divider ) {
            quotient |= _bit;
            remainder -= divider;
        }
        divider >>= 1;
        _bit >>= 1;
    }

    while ( _bit && remainder ) {
        if ( remainder >= divider ) {
            quotient |= _bit;
            remainder -= divider;
        }

        remainder <<= 1;
        _bit >>= 1;
    }

#ifndef FIXMATH_NO_ROUNDING
    if ( remainder >= divider ) {
        quotient++;
    }
#endif

    fix16_t result = quotient;

    if ( ( a ^ b ) & 0x80000000 ) {
#ifndef FIXMATH_NO_OVERFLOW
        if ( result == FIX16_MINIMUM )
            return FIX16_OVERFLOW;
#endif

        result = -result;
    }

    return result;
}

static fix16_t dev_fix16_sqrt ( fix16_t x ) {
    uint32_t num = x;
    uint32_t result = 0;
    uint32_t _bit;
    uint8_t n;

    _bit = ( uint32_t )1 << 30;
    while ( _bit > num )
        _bit >>= 2;


    for ( n = 0; n < 2; n++ ) {
        while ( _bit ) {
            if ( num >= result + _bit ) {
                num -= result + _bit;
                result = ( result >> 1 ) + _bit;
            } else {
                result = ( result >> 1 );
            }
            _bit >>= 2;
        }

        if ( n == 0 ) {
            if ( num > 65535 ) {
                num -= result;
                num = ( num << 16 ) - 0x8000;
                result = ( result << 16 ) + 0x8000;
            } else {
                num <<= 16;
                result <<= 16;
            }

            _bit = 1 << 14;
        }
    }

#ifndef FIXMATH_NO_ROUNDING
    if ( num > result ) {
        result++;
    }
#endif

    return ( fix16_t )result;
}

static fix16_t dev_fix16_exp ( fix16_t x ) {
#define NUM_EXP_VALUES 4
    static const fix16_t exp_pos_values[ NUM_EXP_VALUES ] = { F16( 2.7182818 ), F16( 1.1331485 ), F16( 1.0157477 ), F16( 1.0019550 ) };
    static const fix16_t exp_neg_values[ NUM_EXP_VALUES ] = { F16( 0.3678794 ), F16( 0.8824969 ), F16( 0.9844964 ), F16( 0.9980488 ) };
    const fix16_t* exp_values;
    fix16_t res, arg;
    uint16_t i;

    if ( x >= F16( 10.3972 ) )
        return FIX16_MAXIMUM;
    if ( x <= F16( -11.7835 ) )
        return 0;

    if ( x < 0 ) {
        x = -x;
        exp_values = exp_neg_values;
    } else {
        exp_values = exp_pos_values;
    }

    res = FIX16_ONE;
    arg = FIX16_ONE;
    for ( i = 0; i < NUM_EXP_VALUES; i++ ) {
        while ( x >= arg ) {
            res = dev_fix16_mul( res, exp_values[ i ] );
            x -= arg;
        }
        arg >>= 3;
    }
    return res;
}

static void dev_measurement_duration_raw_delay ( void ) {
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
}

static void dev_measurement_duration_test_delay ( void ) {
    Delay_100ms( );
    Delay_100ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
}

static void dev_measurement_duration_temp_hum_delay ( void ) {
    Delay_10ms( );    
}

static uint8_t dev_calc_crc ( uint8_t data_0, uint8_t data_1 ) {
    uint8_t i_cnt;
    uint8_t j_cnt;
    uint8_t crc_data[ 2 ];
    uint8_t crc = 0xFF;
    
    crc_data[ 0 ] = data_0;
    crc_data[ 1 ] = data_1;
    
    for ( i_cnt = 0; i_cnt < 2; i_cnt++ ) {
        crc ^= crc_data[ i_cnt ];

        for ( j_cnt = 8; j_cnt > 0; --j_cnt ) {
            if ( crc & 0x80 ) {
                crc = ( crc << 1 ) ^ 0x31u;
            } else {
                crc = ( crc << 1 );
            }
        }
    }

    return crc;
}

static err_t dev_set_device_slave_address ( environment2_t *ctx, uint8_t select_device ) {
    err_t status;
    
    status = ENVIRONMENT2_ERROR;
    
    if ( select_device == ENVIRONMENT2_SEL_SGP40 ) {
        ctx->slave_address = ENVIRONMENT2_SGP40_SET_DEV_ADDR;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
         status = ENVIRONMENT2_OK;
    } else if ( select_device == ENVIRONMENT2_SEL_SHT40 ) {
        ctx->slave_address = ENVIRONMENT2_SHT40_SET_DEV_ADDR;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
         status = ENVIRONMENT2_OK;
    }
    
    return status; 
}

// ------------------------------------------------------------------------- END
