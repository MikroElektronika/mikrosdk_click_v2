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
 * @file raq.h
 * @brief This file contains API for RAQ Click Driver.
 */

#ifndef RAQ_H
#define RAQ_H

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
 * @addtogroup raq RAQ Click Driver
 * @brief API for configuring and manipulating RAQ Click driver.
 * @{
 */

/**
 * @defgroup raq_reg RAQ Register Addresses
 * @brief Register address map for RAQ Click.
 */

/**
 * @addtogroup raq_reg
 * @{
 */

/**
 * @brief RAQ register map.
 * @details Specified register map of RAQ Click driver.
 */
#define RAQ_REG_PID                        0x00
#define RAQ_REG_CONF                       0x20
#define RAQ_REG_PROD_DATA                  0x26
#define RAQ_REG_CMD                        0x93
#define RAQ_REG_STATUS                     0x94
#define RAQ_REG_ERR                        0xB7
#define RAQ_REG_HSPF                       0x40
#define RAQ_REG_DATA_SET_1                 0x50
#define RAQ_REG_DATA_SET_2                 0x60
#define RAQ_REG_DATA_SET_3                 0x68
#define RAQ_REG_MOX_PARAMS                 0x97
#define RAQ_REG_ADC_RESULT                 0x99

/*! @} */ // raq_reg

/**
 * @defgroup raq_set RAQ Settings
 * @brief Driver-specific settings and bit masks.
 */

/**
 * @addtogroup raq_set
 * @{
 */

/**
 * @brief Byte lengths of multi-byte RAQ registers.
 * @details Used when reading structured data blocks from the sensor.
 */
#define RAQ_LEN_PID                        0x02
#define RAQ_LEN_CONF                       0x06
#define RAQ_LEN_PROD_DATA                  0x05

/**
 * @brief Bit masks for RAQ status register.
 * @details Used to decode sequencer state and alarm flags from RAQ_REG_STATUS register.
 */
#define RAQ_STATUS_SEQUENCER_RUNNING_MASK  0x80
#define RAQ_STATUS_SLEEP_TIMER_EN_MASK     0x40
#define RAQ_STATUS_ALARM_MASK              0x20
#define RAQ_STATUS_LAST_SEQ_STEP_MASK      0x1F

/**
 * @brief Bit masks for sensor error flag register.
 * @details Used to detect access conflicts and power-on reset events.
 */
#define RAQ_STATUS_POR_EVENT_MASK          0x80
#define RAQ_STATUS_ACCESS_CONFLICT_MASK    0x40

/**
 * @brief Command register control values.
 * @details Used to stop the sequencer, run sensor initialization, or start continuous measurement mode.
 */
#define RAQ_CMD_STOP                       0x00
#define RAQ_CMD_INIT                       0x80
#define RAQ_CMD_START_CONT                 0xC0

/**
 * @brief Data block lengths used by RAQ driver.
 * @details Defines byte counts for multi-byte reads/writes.
 */
#define RAQ_LEN_HSPF                          2  
#define RAQ_LEN_MOX_PARAMS                    4
#define RAQ_LEN_WORK_BUF                      4
#define RAQ_LEN_ADC_RESULT                    2
#define RAQ_LEN_ERR_FLAG                      1
#define RAQ_LEN_STATUS                        1
#define RAQ_LEN_CMD                           1

/**
 * @brief Dataset byte lengths for RAQ sequencer configuration blocks.
 * @details Defines the exact payload sizes (in bytes) of vendor datasets written 
 * to RAQ_REG_DATA_SET_1/2/3 for continuous mode (CONT) and initialization (INIT) sequences.
 */
#define RAQ_CONT_DS1_LEN                      4
#define RAQ_CONT_DS2_LEN                      1
#define RAQ_CONT_DS3_LEN                      4
#define RAQ_INIT_DS1_LEN                      2
#define RAQ_INIT_DS2_LEN                      2
#define RAQ_INIT_DS3_LEN                      4  

/**
 * @brief Valid range limits for computed HSPF coefficient.
 * @details Used to validate calculated HSPF before writing it to the HSPF register.
 */
#define RAQ_HSPF_MAX                    4096.0f  
#define RAQ_HSPF_MIN                       0.0f

/**
 * @brief Invalid ADC values.
 * @details ADC results equal to these values are treated as invalid measurements.
 */
#define RAQ_ADC_INVALID_MIN               0x0000
#define RAQ_ADC_INVALID_MAX               0xFFFF

/**
 * @brief Sequencer step identifiers.
 * @details Used with RAQ_STATUS_LAST_SEQ_STEP_MASK to detect start/end of a measurement cycle.
 */
#define RAQ_FIRST_SEQ_STEP                  0x00
#define RAQ_LAST_SEQ_STEP                   0x01

/**
 * @brief Runtime limits used for gas measurement validation and timeout handling.
 * @details Defines maximum valid RMOX value and polling retry count before reporting timeout.
 */
#define RAQ_RMOX_MAX_VALID          100000000.0f
#define RAQ_GAS_INIT_TIMEOUT_CNT            1000

/**
 * @brief RAQ device address setting.
 * @details Specified setting for device slave address selection of
 * RAQ Click driver.
 */
#define RAQ_DEVICE_ADDRESS                  0x32

/*! @} */ // raq_set

/**
 * @defgroup raq_map RAQ MikroBUS Map
 * @brief MikroBUS pin mapping of RAQ Click driver.
 */

/**
 * @addtogroup raq_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RAQ Click to the selected MikroBUS.
 */
#define RAQ_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // raq_map
/*! @} */ // raq

/**
 * @brief RAQ Click context object.
 * @details Context object definition of RAQ Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Hardware reset pin used to control sensor reset state. */
    
    // Input pins
    digital_in_t int_pin;                       /**< Interrupt pin indicating sensor status/events. */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */
    
    // Calibration parameters cache
    uint16_t mox_lr;                            /**< Cached MOX_LR sensor specific parameter. */
    uint16_t mox_er;                            /**< Cached MOX_ER sensor specific parameter. */
    bool  calib_valid;                          /**< Calibration validity flag (1 = valid, 0 = not initialized). */

} raq_t;

/**
 * @brief RAQ Click configuration object.
 * @details Configuration object definition of RAQ Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Hardware reset pin descriptor. */
    pin_name_t int_pin;         /**< Interrupt pin descriptor. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} raq_cfg_t;

/**
 * @brief RAQ Click sensor info object.
 * @details Minimal info read by driver.
 */
typedef struct
{
    uint16_t pid;                             /**< PID (2 bytes from RAQ_REG_PID). */
    uint8_t  conf[ RAQ_LEN_CONF ];            /**< 6 bytes from RAQ_REG_CONF. */
    uint8_t  prod_data[ RAQ_LEN_PROD_DATA ];  /**< 5 bytes from RAQ_REG_PROD_DATA. */

} raq_info_t;

/**
 * @brief RAQ Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RAQ_OK = 0,                           /**< Operation completed successfully */
    RAQ_ERROR_INIT_OUT_OF_RANGE = -1,     /**< Initialization parameter out of valid range */
    RAQ_ERROR_GAS_TIMEOUT = -2,           /**< Operation timeout */
    RAQ_ERROR_I2C = -3,                   /**< I2C communication failure */
    RAQ_ERROR_SENSOR = -4,                /**< Sensor malfunction / invalid data */
    RAQ_ERROR_ACCESS_CONFLICT = -5,       /**< Sensor access conflict detected */
    RAQ_ERROR_POR_EVENT = -6              /**< Power-On Reset event detected */

} raq_return_value_t;

/*!
 * @addtogroup raq RAQ Click Driver
 * @brief API for configuring and manipulating RAQ Click driver.
 * @{
 */

/**
 * @brief RAQ configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #raq_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void raq_cfg_setup ( raq_cfg_t *cfg );

/**
 * @brief RAQ initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #raq_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t raq_init ( raq_t *ctx, raq_cfg_t *cfg );

/**
 * @brief RAQ I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t raq_generic_write ( raq_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RAQ I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t raq_generic_read ( raq_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RAQ hardware reset function.
 * @details This function toggles the RST pin (active-low) to reset the sensor.
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void raq_hw_reset ( raq_t *ctx );

/**
 * @brief RAQ reading sensor info function.
 * @details This function reads basic sensor identification and factory data (PID, CONF, PROD_DATA).
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @param[out] info : Pointer to sensor info structure to be filled.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t raq_get_sensor_info ( raq_t *ctx, raq_info_t *info );

/**
 * @brief RAQ sensor initialization (INIT) function.
 * @details This function runs the sensor init sequence (CMD=0x80), 
 * then reads MOX_LR/MOX_ER sensor specific parameters (0x97..0x9A).
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @param[out] mox_lr : Output mox_lr sensor specific parameter.
 * @param[out] mox_er : Output mox_er sensor specific parameter.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t raq_init_sensor ( raq_t *ctx, uint16_t *mox_lr, uint16_t *mox_er );

/**
 * @brief RAQ measurement configuration function.
 * @details This function programs continuous mode configuration (HSPF @0x40 and parameter blocks @0x50/0x60/0x68).
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t raq_init_measurement ( raq_t *ctx );

/**
 * @brief RAQ measurement start function.
 * @details This function writes CMD=0xC0 to RAQ_REG_CMD to start the continuous measurement.
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t raq_start_measurement ( raq_t *ctx );

/**
 * @brief RAQ reading sensor status function.
 * @details This function reads the status byte from RAQ_REG_STATUS.
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @return Status byte on success, otherwise 0.
 * @note None.
 */
uint8_t raq_get_status ( raq_t *ctx );

/**
 * @brief RAQ RMOX reading function.
 * @details This function reads ADC result (0x99..0x9A) and 
 * computes RMOX using sensor specific parameters (MOX_LR/MOX_ER).
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @param[out] rmox : Output computed RMOX value.
 * @param[in] mox_lr : mox_lr sensor specific parameter.
 * @param[in] mox_er : mox_er sensor specific parameter.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t raq_read_rmox ( raq_t *ctx, float *rmox, uint16_t mox_lr, uint16_t mox_er );

/**
 * @brief RAQ continuous mode initialization function.
 * @details This function starts continuous measurement and synchronizes
 * by waiting until the sequencer reports step 0.
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t raq_cont_init ( raq_t *ctx );

/**
 * @brief RAQ continuous mode run function.
 * @details This function waits for a new sample (last sequence step) and reads RMOX.
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @param[out] r_mox : Output computed RMOX value for the current sample.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t raq_cont_run ( raq_t *ctx, float *r_mox );

/**
 * @brief RAQ check interrupt function.
 * @details This function reads the current logic level of the sensor INT pin.
 * @param[in] ctx : Click context object.
 * See #raq_t object definition for detailed explanation.
 * @return Pin state (0/1).
 * @note None.
 */
uint8_t raq_check_interrupt ( raq_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RAQ_H

/*! @} */ // raq

// ------------------------------------------------------------------------ END
