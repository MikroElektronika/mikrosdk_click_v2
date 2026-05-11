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
 * @file hvac2.h
 * @brief This file contains API for HVAC 2 Click Driver.
 */

#ifndef HVAC2_H
#define HVAC2_H

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
 * @addtogroup hvac2 HVAC 2 Click Driver
 * @brief API for configuring and manipulating HVAC 2 Click driver.
 * @{
 */

/**
 * @defgroup hvac2_reg HVAC 2 Registers List
 * @brief List of registers of HVAC 2 Click driver.
 */

/**
 * @addtogroup hvac2_reg
 * @{
 */

/**
 * @brief HVAC 2 SCD43 commands list.
 * @details Specified SCD43 commands list of HVAC 2 Click driver.
 */
#define HVAC2_SCD43_CMD_START_PERIODIC_MEASUREMENT          0x21B1
#define HVAC2_SCD43_CMD_READ_MEASUREMENT                    0xEC05
#define HVAC2_SCD43_CMD_STOP_PERIODIC_MEASUREMENT           0x3F86
#define HVAC2_SCD43_CMD_SET_TEMPERATURE_OFFSET              0x241D
#define HVAC2_SCD43_CMD_GET_TEMPERATURE_OFFSET              0x2318
#define HVAC2_SCD43_CMD_SET_SENSOR_ALTITUDE                 0x2427
#define HVAC2_SCD43_CMD_GET_SENSOR_ALTITUDE                 0x2322
#define HVAC2_SCD43_CMD_SET_AMBIENT_PRESSURE                0xE000
#define HVAC2_SCD43_CMD_GET_AMBIENT_PRESSURE                0xE000
#define HVAC2_SCD43_CMD_PERFORM_FORCED_RECALIB              0x362F
#define HVAC2_SCD43_CMD_SET_AUTO_SELF_CALIB_EN              0x2416
#define HVAC2_SCD43_CMD_GET_AUTO_SELF_CALIB_EN              0x2313
#define HVAC2_SCD43_CMD_SET_AUTO_SELF_CALIB_TARGET          0x243A
#define HVAC2_SCD43_CMD_GET_AUTO_SELF_CALIB_TARGET          0x233F
#define HVAC2_SCD43_CMD_START_LP_PERIODIC_MEASUREMENT       0x21AC
#define HVAC2_SCD43_CMD_GET_DATA_READY_STATUS               0xE4B8
#define HVAC2_SCD43_CMD_PERSIST_SETTINGS                    0x3615
#define HVAC2_SCD43_CMD_GET_SERIAL_NUMBER                   0x3682
#define HVAC2_SCD43_CMD_PERFORM_SELF_TEST                   0x3639
#define HVAC2_SCD43_CMD_PERFORM_FACTORY_RESET               0x3632
#define HVAC2_SCD43_CMD_REINIT                              0x3646
#define HVAC2_SCD43_CMD_GET_SENSOR_VARIANT                  0x202F
#define HVAC2_SCD43_CMD_MEASURE_SINGLE_SHOT                 0x219D
#define HVAC2_SCD43_CMD_MEASURE_SINGLE_SHOT_RHT_ONLY        0x2196
#define HVAC2_SCD43_CMD_POWER_DOWN                          0x36E0
#define HVAC2_SCD43_CMD_WAKE_UP                             0x36F6
#define HVAC2_SCD43_CMD_SET_AUTO_SELF_CALIB_INIT_PERIOD     0x2445
#define HVAC2_SCD43_CMD_GET_AUTO_SELF_CALIB_INIT_PERIOD     0x2340
#define HVAC2_SCD43_CMD_SET_AUTO_SELF_CALIB_STANDARD_PERIOD 0x244E
#define HVAC2_SCD43_CMD_GET_AUTO_SELF_CALIB_STANDARD_PERIOD 0x234B

/**
 * @brief HVAC 2 SEN5x commands list.
 * @details Specified SEN5x commands list of HVAC 2 Click driver.
 */
#define HVAC2_SEN5X_CMD_START_MEASUREMENT                   0x0021
#define HVAC2_SEN5X_CMD_START_MEASUREMENT_RHT               0x0037
#define HVAC2_SEN5X_CMD_STOP_MEASUREMENT                    0x0104
#define HVAC2_SEN5X_CMD_READ_DATA_READY_FLAG                0x0202
#define HVAC2_SEN5X_CMD_READ_MEASURED_VALUES                0x03C4
#define HVAC2_SEN5X_CMD_RW_TEMP_COMP_PARAMS                 0x60B2
#define HVAC2_SEN5X_CMD_RW_WARM_START_PARAMS                0x60C6
#define HVAC2_SEN5X_CMD_RW_VOC_ALGO_TUNING_PARAMS           0x60D0
#define HVAC2_SEN5X_CMD_RW_NOX_ALGO_TUNING_PARAMS           0x60E1
#define HVAC2_SEN5X_CMD_RW_RHT_ACC_MODE                     0x60F7
#define HVAC2_SEN5X_CMD_RW_VOC_ALGO_STATE                   0x6181
#define HVAC2_SEN5X_CMD_START_FAN_CLEANING                  0x5607
#define HVAC2_SEN5X_CMD_RW_AUTO_CLEANING_INTERVAL           0x8004
#define HVAC2_SEN5X_CMD_READ_PRODUCT_NAME                   0xD014
#define HVAC2_SEN5X_CMD_READ_SERIAL_NUM                     0xD033
#define HVAC2_SEN5X_CMD_READ_FIRMWARE_VERSION               0xD100
#define HVAC2_SEN5X_CMD_READ_DEVICE_STATUS                  0xD206
#define HVAC2_SEN5X_CMD_CLEAR_DEVICE_STATUS                 0xD210
#define HVAC2_SEN5X_CMD_RESET                               0xD304

/**
 * @brief HVAC 2 SEN6x commands list.
 * @details Specified SEN6x commands list of HVAC 2 Click driver.
 */
#define HVAC2_SEN6X_CMD_START_MEASUREMENT                   0x0021
#define HVAC2_SEN6X_CMD_STOP_MEASUREMENT                    0x0104
#define HVAC2_SEN6X_CMD_GET_DATA_READY                      0x0202
#define HVAC2_SEN6X_CMD_READ_MEASURED_VALUES_SEN62          0x04A3
#define HVAC2_SEN6X_CMD_READ_MEASURED_VALUES_SEN63C         0x0471
#define HVAC2_SEN6X_CMD_READ_MEASURED_VALUES_SEN65          0x0446
#define HVAC2_SEN6X_CMD_READ_MEASURED_VALUES_SEN66          0x0300
#define HVAC2_SEN6X_CMD_READ_MEASURED_VALUES_SEN68          0x0467
#define HVAC2_SEN6X_CMD_READ_MEASURED_VALUES_SEN69C         0x04B5
#define HVAC2_SEN6X_CMD_READ_MEASURED_RAW_VALUES_SEN62_3C   0x0492
#define HVAC2_SEN6X_CMD_READ_MEASURED_RAW_VALUES_SEN65_8_9C 0x0455
#define HVAC2_SEN6X_CMD_READ_MEASURED_RAW_VALUES_SEN66      0x0405
#define HVAC2_SEN6X_CMD_READ_NUM_CONCENTRATION_VALUES       0x0316
#define HVAC2_SEN6X_CMD_SET_TEMP_OFFSET_PARAMS              0x60B2
#define HVAC2_SEN6X_CMD_SET_TEMP_ACCEL_PARAMS               0x6100
#define HVAC2_SEN6X_CMD_GET_PRODUCT_NAME                    0xD014
#define HVAC2_SEN6X_CMD_GET_SERIAL_NUM                      0xD033
#define HVAC2_SEN6X_CMD_READ_DEVICE_STATUS                  0xD206
#define HVAC2_SEN6X_CMD_READ_CLEAR_DEVICE_STATUS            0xD210
#define HVAC2_SEN6X_CMD_GET_VERSION                         0xD100
#define HVAC2_SEN6X_CMD_DEVICE_RESET                        0xD304
#define HVAC2_SEN6X_CMD_START_FAN_CLEANING                  0x5607
#define HVAC2_SEN6X_CMD_ACTIVATE_SHT_HEATER                 0x6765
#define HVAC2_SEN6X_CMD_GET_SHT_HEATER_MEASUREMENTS         0x6790
#define HVAC2_SEN6X_CMD_RW_VOC_ALGO_TUNING_PARAMS           0x60D0
#define HVAC2_SEN6X_CMD_RW_VOC_ALGO_STATE                   0x6181
#define HVAC2_SEN6X_CMD_RW_NOX_ALGO_TUNING_PARAMS           0x60E1
#define HVAC2_SEN6X_CMD_PERFORM_FORCED_CO2_RECALIB          0x6707
#define HVAC2_SEN6X_CMD_PERFORM_CO2_SENSOR_FACTORY_RESET    0x6754
#define HVAC2_SEN6X_CMD_RW_CO2_SENSOR_AUTO_SELF_CALIB       0x6711
#define HVAC2_SEN6X_CMD_RW_AMBIENT_PRESSURE                 0x6720
#define HVAC2_SEN6X_CMD_RW_SENSOR_ALTITUDE                  0x6736

/*! @} */ // hvac2_reg

/**
 * @defgroup hvac2_set HVAC 2 Registers Settings
 * @brief Settings for registers of HVAC 2 Click driver.
 */

/**
 * @addtogroup hvac2_set
 * @{
 */

/**
 * @brief HVAC 2 SCD43 measurement calculation setting.
 * @details Specified setting for SCD43 measurement calculation of HVAC 2 Click driver.
 */
#define HVAC2_SCD43_MAX_RH                                  100.0f
#define HVAC2_SCD43_DATA_RESOLUTION                         65535.0f
#define HVAC2_SCD43_ABS_MIN_TEMP                            ( -45.0f )
#define HVAC2_SCD43_ABS_MAX_TEMP                            ( 130.0f )

/**
 * @brief HVAC 2 SEN5x measurement calculation setting.
 * @details Specified setting for SEN5x measurement calculation of HVAC 2 Click driver.
 */
#define HVAC2_SEN5X_PM_SCALE_FACTOR                         10
#define HVAC2_SEN5X_HUM_SCALE_FACTOR                        100
#define HVAC2_SEN5X_TEMP_SCALE_FACTOR                       200
#define HVAC2_SEN5X_VOC_SCALE_FACTOR                        10
#define HVAC2_SEN5X_NOX_SCALE_FACTOR                        10

/**
 * @brief HVAC 2 SEN65 measurement calculation setting.
 * @details Specified setting for SEN65 measurement calculation of HVAC 2 Click driver.
 */
#define HVAC2_SEN65_PM_SCALE_FACTOR                         10
#define HVAC2_SEN65_HUM_SCALE_FACTOR                        100
#define HVAC2_SEN65_TEMP_SCALE_FACTOR                       200
#define HVAC2_SEN65_VOC_SCALE_FACTOR                        10
#define HVAC2_SEN65_NOX_SCALE_FACTOR                        10

/**
 * @brief HVAC 2 SEN65 external sensor selection setting.
 * @details Specified setting for external sensor selection of HVAC 2 Click driver.
 */
#define HVAC2_EXTERNAL_SENSOR_NONE                          0
#define HVAC2_EXTERNAL_SENSOR_SEN5X                         1
#define HVAC2_EXTERNAL_SENSOR_SEN65                         2

/**
 * @brief HVAC 2 device address setting.
 * @details Specified setting for device slave address selection of
 * HVAC 2 Click driver.
 */
#define HVAC2_DEVICE_ADDRESS_SCD43                          0x62
#define HVAC2_DEVICE_ADDRESS_SEN5X                          0x69
#define HVAC2_DEVICE_ADDRESS_SEN6X                          0x6B

/*! @} */ // hvac2_set

/**
 * @defgroup hvac2_map HVAC 2 MikroBUS Map
 * @brief MikroBUS pin mapping of HVAC 2 Click driver.
 */

/**
 * @addtogroup hvac2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of HVAC 2 Click to the selected MikroBUS.
 */
#define HVAC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // hvac2_map
/*! @} */ // hvac2

/**
 * @brief HVAC 2 Click SCD43 data object.
 * @details SCD43 data object definition of HVAC 2 Click driver.
 */
typedef struct
{
    uint16_t co2;               /**< CO2 in ppm. */
    float temperature;          /**< Temperature in Celsius. */
    float humidity;             /**< Relative humidity in percents. */
    
} hvac2_scd43_data_t;

/**
 * @brief HVAC 2 Click SEN5x data object.
 * @details SEN5x data object definition of HVAC 2 Click driver.
 */
typedef struct
{
    float pm1_0;                /**< Mass Concentration PM1.0 [µg/m³]. */
    float pm2_5;                /**< Mass Concentration PM2.5 [µg/m³]. */
    float pm4_0;                /**< Mass Concentration PM4.0 [µg/m³]. */
    float pm10;                 /**< Mass Concentration PM10 [µg/m³]. */
    float humidity;             /**< Compensated Ambient Humidity [%RH]. */
    float temperature;          /**< Compensated Ambient Temperature [°C]. */
    float voc;                  /**< VOC Index. */
    float nox;                  /**< NOx Index. */
    
} hvac2_sen5x_data_t;

/**
 * @brief HVAC 2 Click SEN65 data object.
 * @details SEN5x data object definition of HVAC 2 Click driver.
 */
typedef struct
{
    float pm1_0;                /**< Mass Concentration PM1.0 [µg/m³]. */
    float pm2_5;                /**< Mass Concentration PM2.5 [µg/m³]. */
    float pm4_0;                /**< Mass Concentration PM4.0 [µg/m³]. */
    float pm10;                 /**< Mass Concentration PM10 [µg/m³]. */
    float humidity;             /**< Ambient Humidity [%RH]. */
    float temperature;          /**< Ambient Temperature [°C]. */
    float voc;                  /**< VOC Index. */
    float nox;                  /**< NOx Index. */
    
} hvac2_sen65_data_t;

/**
 * @brief HVAC 2 Click context object.
 * @details Context object definition of HVAC 2 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} hvac2_t;

/**
 * @brief HVAC 2 Click configuration object.
 * @details Configuration object definition of HVAC 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} hvac2_cfg_t;

/**
 * @brief HVAC 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HVAC2_OK = 0,
    HVAC2_ERROR = -1

} hvac2_return_value_t;

/*!
 * @addtogroup hvac2 HVAC 2 Click Driver
 * @brief API for configuring and manipulating HVAC 2 Click driver.
 * @{
 */

/**
 * @brief HVAC 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hvac2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hvac2_cfg_setup ( hvac2_cfg_t *cfg );

/**
 * @brief HVAC 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hvac2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_init ( hvac2_t *ctx, hvac2_cfg_t *cfg );

/**
 * @brief HVAC 2 send command function.
 * @details This function sends a desired command by using I2C serial interface and waits for
 * a specified execution time.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[in] cmd : Command word to be sent.
 * @param[in] exec_time_ms : Command execution time in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_send_command ( hvac2_t *ctx, uint16_t cmd, uint16_t exec_time_ms );

/**
 * @brief HVAC 2 write register function.
 * @details This function writes a desired data word to the selected register by using I2C serial interface 
 * and waits for a specified execution time.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[in] reg : Register address word.
 * @param[in] data_in : Data word to be written.
 * @param[in] exec_time_ms : Command execution time in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_write_register ( hvac2_t *ctx, uint16_t reg, uint16_t data_in, uint16_t exec_time_ms );

/**
 * @brief HVAC 2 read register function.
 * @details This function sends the selected register address word, then waits for a specified execution time,
 * and reads a desired number of data words by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[in] reg : Register address word.
 * @param[out] data_out : Output read data words.
 * @param[in] len : Number of words to be read.
 * @param[in] exec_time_ms : Command execution time in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_read_register ( hvac2_t *ctx, uint16_t reg, uint16_t *data_out, uint8_t len, uint16_t exec_time_ms );

/**
 * @brief HVAC 2 scd43 start measurement function.
 * @details This function starts a periodic measurement of SCD43 device by issuing a desired command for it.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_scd43_start_measurement ( hvac2_t *ctx );

/**
 * @brief HVAC 2 scd43 stop measurement function.
 * @details This function stops a periodic measurement of SCD43 device by issuing a desired command for it.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_scd43_stop_measurement ( hvac2_t *ctx );

/**
 * @brief HVAC 2 scd43 read measurement function.
 * @details This function checks if the SCD43 data is ready and then reads the CO2, temperature, and 
 * humidity measurements.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[out] scd43_data : Measurement data.
 * See #hvac2_scd43_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The periodic measurement must be started before calling this function.
 * The signal update interval is about 5 seconds.
 */
err_t hvac2_scd43_read_measurement ( hvac2_t *ctx, hvac2_scd43_data_t *scd43_data );

/**
 * @brief HVAC 2 scd43 get data ready function.
 * @details This function reads the SCD43 data ready status register.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[out] data_ready : Data ready status value. @li @c 0 - Data not ready,
 *                                                   @li @c 1 - Data is ready.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_scd43_get_data_ready ( hvac2_t *ctx, uint8_t *data_ready );

/**
 * @brief HVAC 2 scd43 get serial number function.
 * @details This function reads the SCD43 48-bit unique serial number in form of 3 data words.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[out] serial_num : 48-bit serial number in form of 3 data words.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_scd43_get_serial_num ( hvac2_t *ctx, uint16_t *serial_num );

/**
 * @brief HVAC 2 sen5x stop measurement function.
 * @details This function stops a periodic measurement of SEN5x device by issuing a desired command for it.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen5x_start_measurement ( hvac2_t *ctx );

/**
 * @brief HVAC 2 sen5x stop measurement function.
 * @details This function stops a periodic measurement of SEN5x device by issuing a desired command for it.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen5x_stop_measurement ( hvac2_t *ctx );

/**
 * @brief HVAC 2 sen5x read measurement function.
 * @details This function checks if the SEN5x data is ready and then reads the PM mass concentration,
 * relative humidity, temperature, VOC and NOx indexes. 
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[out] sen5x_data : Measurement data.
 * See #hvac2_sen5x_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The periodic measurement must be started before calling this function.
 * The signal update interval is about 1 second.
 */
err_t hvac2_sen5x_read_measurement ( hvac2_t *ctx, hvac2_sen5x_data_t *sen5x_data );

/**
 * @brief HVAC 2 sen5x get data ready function.
 * @details This function reads the SEN5x data ready flag register.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[out] data_ready : Data ready flag value. @li @c 0 - Data not ready,
 *                                                 @li @c 1 - Data is ready.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen5x_get_data_ready ( hvac2_t *ctx, uint8_t *data_ready );

/**
 * @brief HVAC 2 sen5x get serial number function.
 * @details This function reads the SEN5x serial number. It is defined as a string value with a maximum
 * length of 32 ASCII characters (including terminating null-character).
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[out] serial_num : Serial number (up to 32 ASCII characters).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen5x_get_serial_num ( hvac2_t *ctx, uint8_t *serial_num );

/**
 * @brief HVAC 2 sen5x get product name function.
 * @details This function reads the SEN5x product name (SEN50, SEN54 or SEN55). It is defined as a string
 * value with a maximum length of 32 ASCII characters (including terminating null-character).
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[out] product_name : Product name (up to 32 ASCII characters).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen5x_get_product_name ( hvac2_t *ctx, uint8_t *product_name );

/**
 * @brief HVAC 2 sen5x start fan cleaning function.
 * @details This function starts the fan-cleaning manually. This command can only be executed in measurement mode.
 * This will accelerate the fan to maximum speed for 10 seconds to blow out the accumulated dust inside the fan.
 * Measurement values are not updated while the fan-cleaning is running.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen5x_start_fan_cleaning ( hvac2_t *ctx );

/**
 * @brief HVAC 2 sen6x stop measurement function.
 * @details This function stops a periodic measurement of SEN6x device by issuing a desired command for it.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen6x_start_measurement ( hvac2_t *ctx );

/**
 * @brief HVAC 2 sen6x stop measurement function.
 * @details This function stops a periodic measurement of SEN6x device by issuing a desired command for it.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen6x_stop_measurement ( hvac2_t *ctx );

/**
 * @brief HVAC 2 sen65 read measurement function.
 * @details This function checks if the SEN65 data is ready and then reads the PM mass concentration,
 * relative humidity, temperature, VOC and NOx indexes. 
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[out] sen65_data : Measurement data.
 * See #hvac2_sen65_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The periodic measurement must be started before calling this function.
 * The signal update interval is about 1 second.
 */
err_t hvac2_sen65_read_measurement ( hvac2_t *ctx, hvac2_sen65_data_t *sen65_data );

/**
 * @brief HVAC 2 sen6x get data ready function.
 * @details This function reads the SEN6x data ready flag register.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[out] data_ready : Data ready flag value. @li @c 0 - Data not ready,
 *                                                 @li @c 1 - Data is ready.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen6x_get_data_ready ( hvac2_t *ctx, uint8_t *data_ready );

/**
 * @brief HVAC 2 sen6x get serial number function.
 * @details This function reads the SEN6x serial number. It is defined as a string value with a maximum
 * length of 32 ASCII characters (including terminating null-character).
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[out] serial_num : Serial number (up to 32 ASCII characters).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen6x_get_serial_num ( hvac2_t *ctx, uint8_t *serial_num );

/**
 * @brief HVAC 2 sen6x get product name function.
 * @details This function reads the SEN6x product name (SEN62, SEN63C, SEN65, SEN66, SEN68, or SEN69C).
 * It is defined as a string value with a maximum length of 32 ASCII characters (including terminating null-character).
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @param[out] product_name : Product name (up to 32 ASCII characters).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen6x_get_product_name ( hvac2_t *ctx, uint8_t *product_name );

/**
 * @brief HVAC 2 sen65 start fan cleaning function.
 * @details This function triggers fan cleaning. The fan is set to the maximum speed for 10 seconds and
 * then automatically stopped. Wait at least 10s after this command before starting a measurement.
 * @param[in] ctx : Click context object.
 * See #hvac2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hvac2_sen65_start_fan_cleaning ( hvac2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HVAC2_H

/*! @} */ // hvac2

// ------------------------------------------------------------------------ END
