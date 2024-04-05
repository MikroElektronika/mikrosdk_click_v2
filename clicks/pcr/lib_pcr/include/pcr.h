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
 * @file pcr.h
 * @brief This file contains API for PCR Click Driver.
 */

#ifndef PCR_H
#define PCR_H

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
 * @addtogroup pcr PCR Click Driver
 * @brief API for configuring and manipulating PCR Click driver.
 * @{
 */

/**
 * @defgroup pcr_reg PCR Registers List
 * @brief List of registers of PCR Click driver.
 */

/**
 * @addtogroup pcr_reg
 * @{
 */

/**
 * @brief PCR description register.
 * @details Specified register for description of PCR Click driver.
 */
#define PCR_REG_VERSION                 0x0000
#define PCR_REG_PROTOCOL_STATUS         0x0001
#define PCR_REG_MEASURE_CNT             0x0002
#define PCR_REG_DETECTOR_STATUS         0x0003
#define PCR_REG_DISTANCE_RESULT         0x0010
#define PCR_REG_PEAK0_DISTANCE          0x0011
#define PCR_REG_PEAK1_DISTANCE          0x0012
#define PCR_REG_PEAK2_DISTANCE          0x0013
#define PCR_REG_PEAK3_DISTANCE          0x0014
#define PCR_REG_PEAK4_DISTANCE          0x0015
#define PCR_REG_PEAK5_DISTANCE          0x0016
#define PCR_REG_PEAK6_DISTANCE          0x0017
#define PCR_REG_PEAK7_DISTANCE          0x0018
#define PCR_REG_PEAK8_DISTANCE          0x0019
#define PCR_REG_PEAK9_DISTANCE          0x001A
#define PCR_REG_PEAK0_STRENGTH          0x001B
#define PCR_REG_PEAK1_STRENGTH          0x001C
#define PCR_REG_PEAK2_STRENGTH          0x001D
#define PCR_REG_PEAK3_STRENGTH          0x001E
#define PCR_REG_PEAK4_STRENGTH          0x001F
#define PCR_REG_PEAK5_STRENGTH          0x0020
#define PCR_REG_PEAK6_STRENGTH          0x0021
#define PCR_REG_PEAK7_STRENGTH          0x0022
#define PCR_REG_PEAK8_STRENGTH          0x0023
#define PCR_REG_PEAK9_STRENGTH          0x0024
#define PCR_REG_START                   0x0040
#define PCR_REG_END                     0x0041
#define PCR_REG_MAX_STEP_LEN            0x0042
#define PCR_REG_CLOSE_RANGE_LEAK        0x0043
#define PCR_REG_SIGNAL_QUALITY          0x0044
#define PCR_REG_MAX_PROFILE             0x0045
#define PCR_REG_TRESHOLD_SENSITIVITY    0x0046
#define PCR_REG_PEAK_SORTI              0x0047
#define PCR_REG_MAX_FRAMES_RECORDED     0x0048
#define PCR_REG_AMPLITUDE_TERSHOLD      0x0049
#define PCR_REG_TERSHOLD_SENSITIVITY    0x004A
#define PCR_REG_REFLECTOR_SHAPE         0x004B
#define PCR_REG_STRENGHT_TRESHOLD       0x004C
#define PCR_REG_MEASURE_ON_WAKEUP       0x0080
#define PCR_REG_COMMAND                 0x0100

/*! @} */ // pcr_reg

/**
 * @defgroup pcr_set PCR Registers Settings
 * @brief Settings for registers of PCR Click driver.
 */

/**
 * @addtogroup pcr_set
 * @{
 */

/**
 * @brief PCR description setting.
 * @details Specified setting for description of PCR Click driver.
 */

/**
 * @brief PCR Detector Status register setting.
 * @details Specified setting for Detector Status register of PCR Click driver.
 */
#define PCR_STATUS_RSS_REG_OK           0x00000001ul
#define PCR_STATUS_CFG_CREATE_OK        0x00000002ul
#define PCR_STATUS_SENSOR_CREATE_OK     0x00000004ul
#define PCR_STATUS_DETECTOR_CREATE_OK   0x00000008ul
#define PCR_STATUS_DETECTOR_BUFFER_OK   0x00000010ul
#define PCR_STATUS_SENSOR_BUFFER_OK     0x00000020ul
#define PCR_STATUS_CALIB_BUFFER_OK      0x00000040ul
#define PCR_STATUS_CFG_APPLY_OK         0x00000080ul
#define PCR_STATUS_SENSOR_CALIB_OK      0x00000100ul
#define PCR_STATUS_DETECTOR_CALIB_OK    0x00000200ul
#define PCR_STATUS_RSS_REG_ERR          0x00010000ul
#define PCR_STATUS_CFG_CREATE_ERR       0x00020000ul
#define PCR_STATUS_SENSOR_CREATE_ERR    0x00040000ul
#define PCR_STATUS_DETECTOR_CREATE_ERR  0x00080000ul
#define PCR_STATUS_DETECTOR_BUFFER_ERR  0x00100000ul
#define PCR_STATUS_SENSOR_BUFFER_ERR    0x00200000ul
#define PCR_STATUS_CALIB_BUFFER_ERR     0x00400000ul
#define PCR_STATUS_CFG_APPLY_ERR        0x00800000ul
#define PCR_STATUS_SENSOR_CALIB_ERR     0x01000000ul
#define PCR_STATUS_DETECTOR_CALIB_ERR   0x02000000ul
#define PCR_STATUS_DETECTOR_ERR         0x10000000ul
#define PCR_STATUS_BUSY                 0x80000000ul

/**
 * @brief PCR commands setting.
 * @details Specified commands of PCR Click driver.
 */
#define PCR_APPLY_CFG_AND_CALIB_CMD     0x00000001ul
#define PCR_MEASURE_DISTANCE_CMD        0x00000002ul
#define PCR_APPLY_CONFIGURATION_CMD     0x00000003ul
#define PCR_CALIBRATE_CMD               0x00000004ul
#define PCR_RECALIBRATE_CMD             0x00000005ul
#define PCR_ENABLE_UART_LOGS_CMD        0x00000020ul
#define PCR_DISABLE_UART_LOGS_CMD       0x00000021ul
#define PCR_LOG_CONFIGURATION_CMD       0x00000022ul
#define PCR_RESET_MODULE_CMD            0x52535421ul

/**
 * @brief PCR pin state setting.
 * @details Specified pin state of PCR Click driver.
 */
#define PCR_PIN_STATE_HIGH              0x01
#define PCR_PIN_STATE_LOW               0x00

/**
 * @brief PCR distance setting.
 * @details Specified minimum and maximum distance setting of PCR Click driver.
 */
#define PCR_MIN_DISTANCE                10
#define PCR_MAX_DISTANCE                5000

/**
 * @brief PCR device address setting.
 * @details Specified setting for device slave address selection of
 * PCR Click driver.
 */
#define PCR_DEVICE_ADDRESS              0x52

/*! @} */ // pcr_set

/**
 * @defgroup pcr_map PCR MikroBUS Map
 * @brief MikroBUS pin mapping of PCR Click driver.
 */

/**
 * @addtogroup pcr_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PCR Click to the selected MikroBUS.
 */
#define PCR_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pcr_map
/*! @} */ // pcr

/**
 * @brief PCR Click context object.
 * @details Context object definition of PCR Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin. */
    digital_out_t wup;          /**< Wake up pin. */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} pcr_t;

/**
 * @brief PCR Click configuration object.
 * @details Configuration object definition of PCR Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin. */
    pin_name_t wup;             /**< Wake up pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} pcr_cfg_t;

/**
 * @brief PCR Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PCR_OK = 0,
    PCR_BUSY = 1,
    PCR_ERROR = -1

} pcr_return_value_t;

/*!
 * @addtogroup pcr PCR Click Driver
 * @brief API for configuring and manipulating PCR Click driver.
 * @{
 */

/**
 * @brief PCR configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pcr_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pcr_cfg_setup ( pcr_cfg_t *cfg );

/**
 * @brief PCR initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pcr_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pcr_init ( pcr_t *ctx, pcr_cfg_t *cfg );

/**
 * @brief PCR default configuration function.
 * @details This function executes a default configuration of PCR
 * click board.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pcr_default_cfg ( pcr_t *ctx );

/**
 * @brief PCR I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pcr_generic_write ( pcr_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief PCR I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pcr_generic_read ( pcr_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief PCR set wake up pin state function.
 * @details This function is used to set wake up pin state of PCR
 * click board.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @param[in] pin_state : State of the pin.
 * @return Nothing.
 * @note None.
 */
void pcr_set_wup_pin ( pcr_t *ctx, uint8_t pin_state );

/**
 * @brief PCR set reset pin state function.
 * @details This function is used to set reset pin state of PCR
 * click board.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @param[in] pin_state : State of the pin.
 * @return Nothing.
 * @note None.
 */
void pcr_set_rst_pin ( pcr_t *ctx, uint8_t pin_state );

/**
 * @brief PCR get interrupt pin state function.
 * @details This function is used to read interrupt pin state of PCR
 * click board.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @return State of the interrupt pin.
 * @note None.
 */
uint8_t pcr_get_int_pin ( pcr_t *ctx );

/**
 * @brief PCR hardware reset function.
 * @details This function is used to perform hardware reset of PCR
 * click board.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void pcr_hw_reset ( pcr_t *ctx );

/**
 * @brief PCR register writing function.
 * @details This function writes a desired data bytes into
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pcr_write_reg ( pcr_t *ctx, uint16_t reg, uint32_t data_in );

/**
 * @brief PCR register reading function.
 * @details This function reads a desired data bytes from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pcr_read_reg ( pcr_t *ctx, uint16_t reg, uint32_t *data_out );

/**
 * @brief PCR get status function.
 * @details This function is used to read status register of the PCR
 * click board.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @param[out] status : Read status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pcr_get_status ( pcr_t *ctx, uint32_t *status );

/**
 * @brief PCR check if device is busy function.
 * @details This function is used to check if the PCR
 * click board is busy.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @return @li @c 0 - Success device not busy,
 *         @li @c 1 - Device busy.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pcr_check_if_busy ( pcr_t *ctx );

/**
 * @brief PCR check if device is ok function.
 * @details This function is used to read status register,
 * if any error flags are up, function will return error.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pcr_check_if_ok ( pcr_t *ctx );

/**
 * @brief PCR read distance function.
 * @details This function is used to read distance from the PCR
 * click board.
 * @param[in] ctx : Click context object.
 * See #pcr_t object definition for detailed explanation.
 * @param[out] distance_data : Read distance data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pcr_get_distance ( pcr_t *ctx, uint32_t *distance_data );

#ifdef __cplusplus
}
#endif
#endif // PCR_H

/*! @} */ // pcr

// ------------------------------------------------------------------------ END
