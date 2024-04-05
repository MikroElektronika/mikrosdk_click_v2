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
 * @file environment2.h
 * @brief This file contains API for Environment 2 Click Driver.
 */

#ifndef ENVIRONMENT2_H
#define ENVIRONMENT2_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup environment2 Environment 2 Click Driver
 * @brief API for configuring and manipulating Environment 2 Click driver.
 * @{
 */

/**
 * @defgroup environment2_reg Environment 2 Registers List
 * @brief List of registers of Environment 2 Click driver.
 */

/**
 * @addtogroup environment2_cmd
 * @{
 */

/**
 * @brief Environment 2 SGP40 description commands.
 * @details Specified SGP40 commands for description of Environment 2 Click driver.
 */
#define ENVIRONMENT2_SGP40_CMD_MEASURE_RAW                       0x260F
#define ENVIRONMENT2_SGP40_CMD_MEASURE_TEST                      0x280E 
#define ENVIRONMENT2_SGP40_CMD_HEATER_OFF                        0x3615
#define ENVIRONMENT2_SGP40_CMD_SOFT_RESET                        0x0006

/**
 * @brief Environment 2 SHT40 description commands.
 * @details Specified SHT40 commands for description of Environment 2 Click driver.
 */
#define ENVIRONMENT2_SHT40_CMD_MEASURE_T_RH_HIGH_PRECISION       0xFD
#define ENVIRONMENT2_SHT40_CMD_MEASURE_T_RH_MEDIUM_PRECISION     0xF6
#define ENVIRONMENT2_SHT40_CMD_MEASURE_T_RH_LOWEST_PRECISION     0xE0
#define ENVIRONMENT2_SHT40_CMD_READ_SERIAL                       0x89
#define ENVIRONMENT2_SHT40_CMD_SOFT_RESET                        0x94
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_HIGHEST_HEATER_1SEC      0x39
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_HIGHEST_HEATER_0_1SEC    0x32
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_MEDIUM_HEATER_1SEC       0x2F
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_MEDIUM_HEATER_0_1SEC     0x24
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_LOWEST_HEATER_1SEC       0x1E
#define ENVIRONMENT2_SHT40_CMD_ACTIVATE_LOWEST_HEATER_0_1SEC     0x15

/*! @} */ // environment2_cmd

/**
 * @defgroup environment2_set Environment 2 Registers Settings
 * @brief Settings for registers of Environment 2 Click driver.
 */

/**
 * @addtogroup environment2_set
 * @{
 */

/**
 * @brief Environment 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Environment 2 Click driver.
 */
#define ENVIRONMENT2_SGP40_SET_DEV_ADDR                          0x59
#define ENVIRONMENT2_SHT40_SET_DEV_ADDR                          0x44

/**
 * @brief Environment 2 device selection.
 * @details Specified selection for device slave address of
 * Environment 2 Click driver.
 */
#define ENVIRONMENT2_SEL_SGP40                                   0x00
#define ENVIRONMENT2_SEL_SHT40                                   0x01

/**
 * @brief Environment 2 fixed point arithmetic parts.
 * @details Specified the fixed point arithmetic parts for VOC algorithm of
 * Environment 2 Click driver.
 */
#define F16(x) \
    ((fix16_t)(((x) >= 0) ? ((x)*65536.0 + 0.5) : ((x)*65536.0 - 0.5)))
#define VocAlgorithm_SAMPLING_INTERVAL (1.)
#define VocAlgorithm_INITIAL_BLACKOUT (45.)
#define VocAlgorithm_VOC_INDEX_GAIN (230.)
#define VocAlgorithm_SRAW_STD_INITIAL (50.)
#define VocAlgorithm_SRAW_STD_BONUS (220.)
#define VocAlgorithm_TAU_MEAN_VARIANCE_HOURS (12.)
#define VocAlgorithm_TAU_INITIAL_MEAN (20.)
#define VocAlgorithm_INIT_DURATION_MEAN ((3600. * 0.75))
#define VocAlgorithm_INIT_TRANSITION_MEAN (0.01)
#define VocAlgorithm_TAU_INITIAL_VARIANCE (2500.)
#define VocAlgorithm_INIT_DURATION_VARIANCE ((3600. * 1.45))
#define VocAlgorithm_INIT_TRANSITION_VARIANCE (0.01)
#define VocAlgorithm_GATING_THRESHOLD (340.)
#define VocAlgorithm_GATING_THRESHOLD_INITIAL (510.)
#define VocAlgorithm_GATING_THRESHOLD_TRANSITION (0.09)
#define VocAlgorithm_GATING_MAX_DURATION_MINUTES ((60. * 3.))
#define VocAlgorithm_GATING_MAX_RATIO (0.3)
#define VocAlgorithm_SIGMOID_L (500.)
#define VocAlgorithm_SIGMOID_K (-0.0065)
#define VocAlgorithm_SIGMOID_X0 (213.)
#define VocAlgorithm_VOC_INDEX_OFFSET_DEFAULT (100.)
#define VocAlgorithm_LP_TAU_FAST (20.0)
#define VocAlgorithm_LP_TAU_SLOW (500.0)
#define VocAlgorithm_LP_ALPHA (-0.2)
#define VocAlgorithm_PERSISTENCE_UPTIME_GAMMA ((3. * 3600.))
#define VocAlgorithm_MEAN_VARIANCE_ESTIMATOR__GAMMA_SCALING (64.)
#define VocAlgorithm_MEAN_VARIANCE_ESTIMATOR__FIX16_MAX (32767.)

/*! @} */ // environment2_set

/**
 * @addtogroup environment2_get
 * @{
 */

/**
 * @brief Environment 2 SGP40 description setting.
 * @details Specified SGP40 setting for description of Environment 2 Click driver.
 */
#define ENVIRONMENT2_SGP40_TEST_PASSED                           0xD400
#define ENVIRONMENT2_SGP40_TEST_FAILED                           0x4B00


/*! @} */ // environment2_get

/**
 * @defgroup environment2_map Environment 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Environment 2 Click driver.
 */

/**
 * @addtogroup environment2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Environment 2 Click to the selected MikroBUS.
 */
#define ENVIRONMENT2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // environment2_map
/*! @} */ // environment2

/**
 * @brief Environment 2 Click context object.
 * @details Context object definition of Environment 2 Click driver.
 */
typedef struct
{
    // Modules

    i2c_master_t i2c;         /**< I2C driver object. */
                              
    // I2C slave address      
                              
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */
                          
} environment2_t;

/**
 * @brief Environment 2 Click configuration object.
 * @details Configuration object definition of Environment 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;          /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;      /**< I2C serial speed. */
    uint8_t   i2c_address;    /**< I2C slave address. */

} environment2_cfg_t;

typedef int32_t fix16_t;


/**
 * @brief Environment 2 Click VOC algorithm object.
 * @details Struct to hold all the states of the VOC algorithm.
 */
typedef struct {
    fix16_t mVoc_Index_Offset;
    fix16_t mTau_Mean_Variance_Hours;
    fix16_t mGating_Max_Duration_Minutes;
    fix16_t mSraw_Std_Initial;
    fix16_t mUptime;
    fix16_t mSraw;
    fix16_t mVoc_Index;
    fix16_t m_Mean_Variance_Estimator__Gating_Max_Duration_Minutes;
    bool m_Mean_Variance_Estimator___Initialized;
    fix16_t m_Mean_Variance_Estimator___Mean;
    fix16_t m_Mean_Variance_Estimator___Sraw_Offset;
    fix16_t m_Mean_Variance_Estimator___Std;
    fix16_t m_Mean_Variance_Estimator___Gamma;
    fix16_t m_Mean_Variance_Estimator___Gamma_Initial_Mean;
    fix16_t m_Mean_Variance_Estimator___Gamma_Initial_Variance;
    fix16_t m_Mean_Variance_Estimator__Gamma_Mean;
    fix16_t m_Mean_Variance_Estimator__Gamma_Variance;
    fix16_t m_Mean_Variance_Estimator___Uptime_Gamma;
    fix16_t m_Mean_Variance_Estimator___Uptime_Gating;
    fix16_t m_Mean_Variance_Estimator___Gating_Duration_Minutes;
    fix16_t m_Mean_Variance_Estimator___Sigmoid__L;
    fix16_t m_Mean_Variance_Estimator___Sigmoid__K;
    fix16_t m_Mean_Variance_Estimator___Sigmoid__X0;
    fix16_t m_Mox_Model__Sraw_Std;
    fix16_t m_Mox_Model__Sraw_Mean;
    fix16_t m_Sigmoid_Scaled__Offset;
    fix16_t m_Adaptive_Lowpass__A1;
    fix16_t m_Adaptive_Lowpass__A2;
    bool m_Adaptive_Lowpass___Initialized;
    fix16_t m_Adaptive_Lowpass___X1;
    fix16_t m_Adaptive_Lowpass___X2;
    fix16_t m_Adaptive_Lowpass___X3;
} environment2_voc_algorithm_params;

/**
 * @brief Environment 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ENVIRONMENT2_OK = 0,
    ENVIRONMENT2_ERROR = -1

} environment2_return_value_t;

/*!
 * @addtogroup environment2 Environment 2 Click Driver
 * @brief API for configuring and manipulating Environment 2 Click driver.
 * @{
 */

/**
 * @brief Environment 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #environment2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void environment2_cfg_setup ( environment2_cfg_t *cfg );

/**
 * @brief Environment 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #environment2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_init ( environment2_t *ctx, environment2_cfg_t *cfg );

/**
 * @brief Environment 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[in] select_device : Device selection.
 * @param[in] cmd : Command to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_generic_write ( environment2_t *ctx, uint8_t select_device, uint16_t cmd );

/**
 * @brief Environment 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[in] select_device : Device selection.
 * @param[in] cmd : Command to be written.
 * @param[out] rx_buf : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_generic_read ( environment2_t *ctx, uint8_t select_device, uint16_t cmd, uint8_t *rx_buf );

/**
 * @brief Environment 2 get temperature and relative humidity function.
 * @details This function reads a temperature and relative humidity from the
 * SHT40 4th Generation, High-Accuracy, Ultra-Low-Power, 16-bit
 * Relative Humidity and Temperature Sensor Platform
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[out] humidity    : Relative Humidity [ %RH ].
 * @param[out] temperature : Temperature [ degree Celsius ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_get_temp_hum ( environment2_t *ctx, float *humidity, float *temperature );

/**
 * @brief Environment 2 get air quality data function.
 * @details This function reads a air quality SRAW data from the
 * SGP40 Indoor Air Quality Sensor for VOC Measurements
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[out] air_quality    : Air quality SRAW data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_get_air_quality ( environment2_t *ctx, uint16_t *air_quality );

/**
 * @brief Environment 2 SGP40 measurement test function.
 * @details This function triggers the built-in self-test checking
 * for integrity of both hotplate and MOX materia of the
 * SGP40 Indoor Air Quality Sensor for VOC Measurements
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @return Result of this test:
 *         @li @c 0xD400 ( ENVIRONMENT2_SGP40_TEST_PASSED ) - All tests passed successfully,
 *         @li @c 0x4B00 ( ENVIRONMENT2_SGP40_TEST_FAILED ) - One or more tests have failed.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
uint16_t environment2_sgp40_measure_test ( environment2_t *ctx );

/**
 * @brief Environment 2 heater off function.
 * @details This function turns the hotplate off and stops the measurement of the
 * SGP40 Indoor Air Quality Sensor for VOC Measurements
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_sgp40_heater_off ( environment2_t *ctx );

/**
 * @brief Environment 2 soft reset function.
 * @details This function general call resetting all devices connected to the same I2C bus of the
 * SGP40 Indoor Air Quality Sensor for VOC Measurements.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The first byte refers to the general call address 
 * and the second byte refers to the reset command.
 * After calling this command, the SGP40 will restart entering the idle mode.
 *
 * @endcode
 */
err_t environment2_sgp40_soft_reset ( environment2_t *ctx );

/**
 * @brief Environment 2 VOC algorithm configuration function.
 * @details This function initialize VOC algorithm.
 * @param[in] environment2_voc_algorithm_params : Struct to hold all the states of the VOC algorithm.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None
 *
 * @endcode
 */
err_t environment2_voc_algorithm_configuration ( environment2_voc_algorithm_params *params );

/**
 * @brief Environment 2 sensors configuration  function.
 * @details This function general performs sensors configuration and initialize VOC algorithm of the
 * SGP40 Indoor Air Quality Sensor for VOC Measurements.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_config_sensors ( void );

/**
 * @brief Environment 2 VOC algorithm process function.
 * @details This function calculate the VOC index value from the raw sensor value.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[in] params : Pointer to the environment2_voc_algorithm_params struct.
 * @param[in] sraw : Air quality SRAW data.
 * @param[out] voc_index : Calculated VOC index value from the raw sensor value. 
 * Zero during initial blackout period and 1..500 afterwards.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_voc_algorithm_process ( environment2_voc_algorithm_params *params, int32_t sraw, int32_t *voc_index );

/**
 * @brief Environment 2 measure VOC index with relative humidity and temperature function.
 * @details This function measure the humidity-compensated VOC Index,  
 * ambient temperature and relative humidity.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[out] voc_index : Pointer to buffer for measured VOC index. Range 0..500. 
 * @param[out] relative_humidity : Relative Humidity [ milli %RH ].
 * @param[out] temperature : Temperature [ milli degree Celsius ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_measure_voc_index_with_rh_t ( environment2_t *ctx, int32_t *voc_index, int32_t *relative_humidity, int32_t *temperature );

/**
 * @brief Environment 2 get VOC index function.
 * @details This function measurement triggers a humidity reading,
 * sets the value on the SGP for humidity compensation 
 * and runs the gas signal through the VOC algorithm for
 * the final result.
 * @param[in] ctx : Click context object.
 * See #environment2_t object definition for detailed explanation.
 * @param[out] voc_index : Pointer to buffer for measured VOC index. Range 0..500. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t environment2_get_voc_index ( environment2_t *ctx, int32_t *voc_index );

#ifdef __cplusplus
}
#endif
#endif // ENVIRONMENT2_H

/*! @} */ // environment2

// ------------------------------------------------------------------------ END
