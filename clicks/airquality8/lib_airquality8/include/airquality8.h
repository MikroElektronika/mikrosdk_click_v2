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
 * @file airquality8.h
 * @brief This file contains API for Air Quality 8 Click Driver.
 */

#ifndef AIRQUALITY8_H
#define AIRQUALITY8_H

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

/**
 * @addtogroup airquality8_reg
 * @{
 */

/**
 * @brief Air Quality 8 description register.
 * @details Specified register for description of Air Quality 8 Click driver.
 */
#define AIRQUALITY8_REG_PID                                             0x00
#define AIRQUALITY8_REG_CONF                                            0x20
#define AIRQUALITY8_REG_PROD_DATA                                       0x26
#define AIRQUALITY8_REG_CMD                                             0x93
#define AIRQUALITY8_REG_STATUS                                          0x94
#define AIRQUALITY8_REG_TRACKING                                        0x3A

#define AIRQUALITY8_REG_CFG_H                                           0x40
#define AIRQUALITY8_REG_CFG_D                                           0x50
#define AIRQUALITY8_REG_CFG_M                                           0x60
#define AIRQUALITY8_REG_CFG_S                                           0x68
#define AIRQUALITY8_REG_CFG_R                                           0x97

/*! @} */ // airquality8_reg

/**
 * @defgroup airquality8_set Air Quality 8 Registers Settings
 * @brief Settings for registers of Air Quality 8 Click driver.
 */

/**
 * @addtogroup airquality8_set
 * @{
 */

/**
 * @brief Air Quality 8 product ID.
 * @details Specified setting for product ID of Air Quality 8 Click driver.
 */
#define AIRQUALITY8_PRODUCT_ID                                          0x6320

/**
 * @brief Air Quality 8 gas detection strategy setting.
 * @details Specified setting for gas detection strategy of Air Quality 8 Click driver.
 */
#define AIRQUALITY8_GAS_DETECTION_STRATEGY_AUTO                         0 
#define AIRQUALITY8_GAS_DETECTION_STRATEGY_FORCE_O3                     1 
#define AIRQUALITY8_GAS_DETECTION_STRATEGY_FORCE_NO2                    2

/**
 * @brief Air Quality 8 RCDA strategy setting.
 * @details Specified setting for RCDA strategy of Air Quality 8 Click driver.
 */
#define AIRQUALITY8_RCDA_STRATEGY_FIX                                   0
#define AIRQUALITY8_RCDA_STRATEGY_SET                                   1
#define AIRQUALITY8_RCDA_STRATEGY_ADJ                                   2

/**
 * @brief Air Quality 8 status bit mask setting.
 * @details Specified setting for status bit mask of Air Quality 8 Click driver.
 */
#define AIRQUALITY8_STATUS_SEQUENCER_RUNNING_MASK                       0x80
#define AIRQUALITY8_STATUS_SLEEP_TIMER_ENABLED_MASK                     0x40
#define AIRQUALITY8_STATUS_ALARM_MASK                                   0x20
#define AIRQUALITY8_STATUS_LAST_SEQ_STEP_MASK                           0x1F
#define AIRQUALITY8_STATUS_POR_EVENT_MASK                               0x80
#define AIRQUALITY8_STATUS_ACCESS_CONFLICT_MASK                         0x40

/**
 * @brief Air Quality 8 device address setting.
 * @details Specified setting for device slave address selection of
 * Air Quality 8 Click driver.
 */
#define AIRQUALITY8_SET_DEV_ADDR                                        0x33

/*! @} */ // airquality8_set

/**
 * @defgroup airquality8_map Air Quality 8 MikroBUS Map
 * @brief MikroBUS pin mapping of Air Quality 8 Click driver.
 */

/**
 * @addtogroup airquality8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Air Quality 8 Click to the selected MikroBUS.
 */
#define AIRQUALITY8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // airquality8_map
/*! @} */ // airquality8

/**
 * @brief Air Quality 8 Click context object.
 * @details Context object definition of Air Quality 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;     /**< Reset pin. */

    // Input pins
    digital_in_t  int_pin;  /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

} airquality8_t;

/**
 * @brief Air Quality 8 Click configuration object.
 * @details Configuration object definition of Air Quality 8 Click driver.
 */
typedef struct
{
    pin_name_t  scl;       /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;       /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;       /**< Reset pin. */
    pin_name_t  int_pin;   /**< Interrupt pin. */

    uint32_t  i2c_speed;   /**< I2C serial speed. */
    uint8_t   i2c_address; /**< I2C slave address. */

} airquality8_cfg_t;

/**
 * @brief Air Quality 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AIRQUALITY8_OK                       = 0,
    AIRQUALITY8_ERROR                    = -1,
    AIRQUALITY8_ERROR_INIT_OUT_OF_RANGE  = 1,
    AIRQUALITY8_ERROR_GAS_TIMEOUT        = 2,
    AIRQUALITY8_ERROR_I2C                = 3,
    AIRQUALITY8_ERROR_SENSOR_UNSUPPORTED = 4,
    AIRQUALITY8_ERROR_CONFIG_MISSING     = 5,
    AIRQUALITY8_ERROR_SENSOR             = 6,
    AIRQUALITY8_ERROR_ACCESS_CONFLICT    = 7,
    AIRQUALITY8_ERROR_POR_EVENT          = 8

} airquality8_return_value_t;

/*!
 * @addtogroup airquality8 Air Quality 8 Click Driver
 * @brief API for configuring and manipulating Air Quality 8 Click driver.
 * @{
 */

/**
 * @brief Air Quality 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #airquality8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void airquality8_cfg_setup ( airquality8_cfg_t *cfg );

/**
 * @brief Air Quality 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #airquality8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality8_init ( airquality8_t *ctx, airquality8_cfg_t *cfg );

/**
 * @brief Air Quality 8 default configuration function.
 * @details This function executes a default configuration of Air Quality 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t airquality8_default_cfg ( airquality8_t *ctx );

/**
 * @brief Air Quality 8 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality8_generic_write ( airquality8_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Air Quality 8 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality8_generic_read ( airquality8_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Air Quality 8 reset function.
 * @details This function executes a hardware reset
 * of the ZMOD4510 Gas Sensor Module for OAQ targeting NO2 & O3
 * on the Air Quality 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void airquality8_hw_reset ( airquality8_t *ctx );

/**
 * @brief Air Quality 8 get status function.
 * @details This function read status data
 * of the ZMOD4510 Gas Sensor Module for OAQ targeting NO2 & O3
 * on the Air Quality 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @param[out] status : Output status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality8_get_status ( airquality8_t *ctx, uint8_t *status );

/**
 * @brief Air Quality 8 get sensor info function.
 * @details This function read product ID and configuration parameters
 * of the ZMOD4510 Gas Sensor Module for OAQ targeting NO2 & O3
 * on the Air Quality 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @param[out] cfg_data : Output configuration data.
 * @param[out] prod_data : Output product data.
 * @param[out] pid : Output product ID data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c  1 - Error initialization out of range,
 *         @li @c  2 - Error Gas timeout,
 *         @li @c  3 - Error I2C,
 *         @li @c  4 - Error sensor unsupported,
 *         @li @c  5 - Error config missing,
 *         @li @c  6 - Error sensor,
 *         @li @c  7 - Error access conflict,
 *         @li @c  8 - Error por event.
 *
 * See #err_t definition for detailed explanation.
 * @note This step is required to select the correct configuration for the sensor.
 */
err_t airquality8_get_sensor_info ( airquality8_t *ctx, uint8_t *cfg_data, uint8_t *prod_data, uint16_t *pid );

/**
 * @brief Air Quality 8 init sensor function.
 * @details This function sensor initialization after power on
 * of the ZMOD4510 Gas Sensor Module for OAQ targeting NO2 & O3
 * on the Air Quality 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @param[out] mox_lr : Output sensor specific parameter data.
 * @param[out] mox_er : Output sensor specific parameter data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c  1 - Error initialization out of range,
 *         @li @c  2 - Error Gas timeout,
 *         @li @c  3 - Error I2C,
 *         @li @c  4 - Error sensor unsupported,
 *         @li @c  5 - Error config missing,
 *         @li @c  6 - Error sensor,
 *         @li @c  7 - Error access conflict,
 *         @li @c  8 - Error por event.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality8_init_sensor ( airquality8_t *ctx, uint16_t *mox_lr, uint16_t *mox_er );

/**
 * @brief Air Quality 8 init measurement function.
 * @details This function sensor measurement initialization 
 * of the ZMOD4510 Gas Sensor Module for OAQ targeting NO2 & O3
 * on the Air Quality 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c  1 - Error initialization out of range,
 *         @li @c  2 - Error Gas timeout,
 *         @li @c  3 - Error I2C,
 *         @li @c  4 - Error sensor unsupported,
 *         @li @c  5 - Error config missing,
 *         @li @c  6 - Error sensor,
 *         @li @c  7 - Error access conflict,
 *         @li @c  8 - Error por event.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality8_init_measurement ( airquality8_t *ctx );

/**
 * @brief Air Quality 8 start measurement function.
 * @details This function start measurement  
 * of the ZMOD4510 Gas Sensor Module for OAQ targeting NO2 & O3
 * on the Air Quality 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality8_start_measurement ( airquality8_t *ctx );

/**
 * @brief Air Quality 8 calculate rmox resistance function.
 * @details This function calculate rmox resistance data
 * of the ZMOD4510 Gas Sensor Module for OAQ targeting NO2 & O3
 * on the Air Quality 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @param[out] rmox : Output srmox data.
 * @param[in] mox_lr : Output sensor specific parameter data.
 * @param[in] mox_er : Output sensor specific parameter data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c  1 - Error initialization out of range,
 *         @li @c  2 - Error Gas timeout,
 *         @li @c  3 - Error I2C,
 *         @li @c  4 - Error sensor unsupported,
 *         @li @c  5 - Error config missing,
 *         @li @c  6 - Error sensor,
 *         @li @c  7 - Error access conflict,
 *         @li @c  8 - Error por event.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airquality8_read_rmox ( airquality8_t *ctx, float *rmox, uint16_t mox_lr, uint16_t mox_er );

/**
 * @brief Air Quality 8 calculates AQI function.
 * @details This function calculates AQI from present sample
 * of the ZMOD4510 Gas Sensor Module for OAQ targeting NO2 & O3
 * on the Air Quality 8 Click board™.
 * @param[in] rmox : Pointer to array of the 15 sequencer rmox measurements.
 * @param[in] rcda_strategy : Strategy how to handle Rcda data
 *         @li @c  0 ( AIRQUALITY8_RCDA_STRATEGY_FIX ) - Hold rcda fixed,
 *         @li @c  1 ( AIRQUALITY8_RCDA_STRATEGY_SET ) - Set the rcda to the actal measurement,
 *         @li @c  2 ( AIRQUALITY8_RCDA_STRATEGY_ADJ ) - Adjust rcda to follow slow drifts.
 * @param[in] gas_detection_strategy : Gas detection strategy handle
 *         @li @c  0 ( AIRQUALITY8_GAS_DETECTION_STRATEGY_AUTO )      - Automatic gas discrimination,
 *         @li @c  1 ( AIRQUALITY8_GAS_DETECTION_STRATEGY_FORCE_O3 )  - Handle the measurements as O3,
 *         @li @c  2 ( AIRQUALITY8_GAS_DETECTION_STRATEGY_FORCE_NO2 ) - Handle the measurements as NO2.
 * @return Air quality index ( AQI ) value.
 *
 * @note None.
 */
float airquality8_calc_oaq ( float *rmox, uint8_t rcda_strategy, uint8_t gas_detection_strategy );

/**
 * @brief Air Quality 8 check interrupt function.
 * @details This function get states of the Interrupt ( INT pin )
 * of the ZMOD4510 Gas Sensor Module for OAQ targeting NO2 & O3
 * on the Air Quality 8 Click board™.
 * @param[in] ctx : Click context object.
 * See #airquality8_t object definition for detailed explanation.
 * @return @li @c 0 - Low INT pin state,
 *         @li @c 1 - High INT pin state.
 *
 * @note None.
 */
uint8_t raq_check_interrupt ( airquality8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // AIRQUALITY8_H

/*! @} */ // airquality8

// ------------------------------------------------------------------------ END
