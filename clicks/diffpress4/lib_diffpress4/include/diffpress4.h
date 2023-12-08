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
 * @file diffpress4.h
 * @brief This file contains API for Diff Press 4 Click Driver.
 */

#ifndef DIFFPRESS4_H
#define DIFFPRESS4_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup diffpress4 Diff Press 4 Click Driver
 * @brief API for configuring and manipulating Diff Press 4 Click driver.
 * @{
 */

/**
 * @defgroup diffpress4_reg Diff Press 4 Registers List
 * @brief List of registers of Diff Press 4 Click driver.
 */

/**
 * @addtogroup diffpress4_reg
 * @{
 */

/**
 * @brief Diff Press 4 description register.
 * @details Specified register for description of Diff Press 4 Click driver.
 */
#define DIFFPRESS4_REG_COMMAND                     0x22
#define DIFFPRESS4_REG_TEMPERATURE                 0x2E
#define DIFFPRESS4_REG_PRESSURE                    0x30
#define DIFFPRESS4_REG_STATUS_SYNC                 0x32
#define DIFFPRESS4_REG_STATUS                      0x36
#define DIFFPRESS4_REG_SER0                        0x50
#define DIFFPRESS4_REG_SER1                        0x52

/*! @} */ // diffpress4_reg

/**
 * @defgroup diffpress4_set Diff Press 4 Registers Settings
 * @brief Settings for registers of Diff Press 4 Click driver.
 */

/**
 * @addtogroup diffpress4_set
 * @{
 */

/**
 * @brief Diff Press 4 calculation data values.
 * @details Specified calculation data values of Diff Press 4 Click driver.
 */
#define DIFFPRESS4_P_MIN                          -250.0f
#define DIFFPRESS4_P_MAX                           250.0f
#define DIFFPRESS4_OUT_MIN                        -26215.0f
#define DIFFPRESS4_OUT_MAX                         26214.0f
#define DIFFPRESS4_B_0                            -16881.0f
#define DIFFPRESS4_B_1                             397.2f

/**
 * @brief Diff Press 4 status data values.
 * @details Specified status data values of Diff Press 4 Click driver.
 */
#define DIFFPRESS4_STATUS_IDLE_CHIP_BUSY           0x00
#define DIFFPRESS4_STATUS_IDLE_CHIP_IDLE           0x01
#define DIFFPRESS4_STATUS_DSP_S_CLEARED            0x00
#define DIFFPRESS4_STATUS_DSP_S_UPDATED            0x01
#define DIFFPRESS4_STATUS_DSP_T_CLEARED            0x00
#define DIFFPRESS4_STATUS_DSP_T_UPDATED            0x01
#define DIFFPRESS4_STATUS_BS_FAIL_NO_FAILURE       0x00
#define DIFFPRESS4_STATUS_BS_FAIL_OCCURRED         0x01
#define DIFFPRESS4_STATUS_BC_FAIL_NO_FAILURE       0x00
#define DIFFPRESS4_STATUS_BC_FAIL_OCCURRED         0x01
#define DIFFPRESS4_STATUS_DSP_SAT_NORMAL           0x00
#define DIFFPRESS4_STATUS_DSP_SAT_OVERFLOW         0x01
#define DIFFPRESS4_STATUS_COM_CRC_OK               0x00
#define DIFFPRESS4_STATUS_COM_CRC_ERROR            0x01
#define DIFFPRESS4_STATUS_DSP_S_MISSED             0x00
#define DIFFPRESS4_STATUS_DSP_S_M_UPDATED          0x01
#define DIFFPRESS4_STATUS_DSP_T_MISSED             0x00
#define DIFFPRESS4_STATUS_DSP_T_M_UPDATED          0x01

/**
 * @brief Diff Press 4 command register data sequence.
 * @details Specified command register data sequence of Diff Press 4 Click driver.
 */
#define DIFFPRESS4_SET_CMD_SLEEP_MODE              0x32, 0x6C 
#define DIFFPRESS4_SET_CMD_RESET                   0x69, 0xB1 

/**
 * @brief Diff Press 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Diff Press 4 Click driver.
 */
#define DIFFPRESS4_DEVICE_ADDRESS_UNPROTECTED      0x6C
#define DIFFPRESS4_DEVICE_ADDRESS_CRC_PROTECTED    0x6D

/*! @} */ // diffpress4_set

/**
 * @defgroup diffpress4_map Diff Press 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Diff Press 4 Click driver.
 */

/**
 * @addtogroup diffpress4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Diff Press 4 Click to the selected MikroBUS.
 */
#define DIFFPRESS4_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // diffpress4_map
/*! @} */ // diffpress4

/**
 * @brief Diff Press 4 Click context object.
 * @details Context object definition of Diff Press 4 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} diffpress4_t;

/**
 * @brief Diff Press 4 Click configuration object.
 * @details Configuration object definition of Diff Press 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} diffpress4_cfg_t;

/**
 * @brief Diff Press 4 Click status object.
 * @details Status object definition of Diff Press 4 Click driver.
 */
typedef struct
{
    uint8_t idle;             /**< Status: Chip state. */
    uint8_t dsp_s_up;         /**< Event: Pressure register has been updated. */
    uint8_t dsp_t_up;         /**< Event: Temperature register has been updated. */
    uint8_t bs_fail;          /**< Event: Bridge supply failure occurred. */
    uint8_t bc_fail;          /**< Event: Sensor bridge check failure occurred. */
    uint8_t dsp_sat;          /**< Status: Computation leading to current values 
                                           was saturated to prevent overflow. */
    uint8_t com_crc_error;    /**< Event: Communication CRC error. */
    uint8_t dsp_s_missed;     /**< Event: Pressure data is updated. */
    uint8_t dsp_t_missed;     /**< Event: Temperature data is updated. */

} diffpress4_status_t;

/**
 * @brief Diff Press 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIFFPRESS4_OK = 0,
    DIFFPRESS4_ERROR = -1

} diffpress4_return_value_t;

/*!
 * @addtogroup diffpress4 Diff Press 4 Click Driver
 * @brief API for configuring and manipulating Diff Press 4 Click driver.
 * @{
 */

/**
 * @brief Diff Press 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #diffpress4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void diffpress4_cfg_setup ( diffpress4_cfg_t *cfg );

/**
 * @brief Diff Press 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #diffpress4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #diffpress4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress4_init ( diffpress4_t *ctx, diffpress4_cfg_t *cfg );

/**
 * @brief Diff Press 4 set I2C Slave address function.
 * @details This function sets I2C address of the subordinate I2C device
 * to address which is targeted by read and write operations.
 * @param[in] ctx : Click context object.
 * See #diffpress4_t object definition for detailed explanation.
 * @param[in] slave_address Specified I2C slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note It is recommended to check return value for error.
 */
err_t diffpress4_set_slave_address ( diffpress4_t *ctx, uint8_t slave_address );

/**
 * @brief Diff Press 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #diffpress4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress4_generic_write ( diffpress4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Diff Press 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #diffpress4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress4_generic_read ( diffpress4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Diff Press 4 set sleep mode function.
 * @details This function is used to initiate a shutdown state
 * of the SM9336, SMI ultra-low pressure digital sensor
 * @param[in] ctx : Click context object.
 * See #diffpress4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress4_set_sleep_mode ( diffpress4_t *ctx );

/**
 * @brief Diff Press 4 software reset function.
 * @details This function performs the reset sequence
 * of the SM9336, SMI ultra-low pressure digital sensor
 * @param[in] ctx : Click context object.
 * See #diffpress4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note After reset the power-up sequence will be executed, i.e. the registers are loaded 
 * with data from the configuration memory, also a CRC check is performed.
 */
err_t diffpress4_sw_reset ( diffpress4_t *ctx );

/**
 * @brief Diff Press 4 get serial number function.
 * @details This function reads serial number data values
 * of the SM9336, SMI ultra-low pressure digital sensor
 * @param[in] ctx : Click context object.
 * See #diffpress4_t object definition for detailed explanation.
 * @param[out] serial_number : Serial number value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress4_get_serial_number ( diffpress4_t *ctx, uint32_t *serial_number );

/**
 * @brief Diff Press 4 get status function.
 * @details This function reads status data values
 * of the SM9336, SMI ultra-low pressure digital sensor
 * @param[in] ctx : Click context object.
 * See #diffpress4_t object definition for detailed explanation.
 * @param[out] status : Status object.
 * See #diffpress4_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress4_get_status ( diffpress4_t *ctx, diffpress4_status_t *status );

/**
 * @brief Diff Press 4 gets the raw data function.
 * @details This function reads the pressure and temperature raw data values
 * of the SM9336, SMI ultra-low pressure digital sensor
 * @param[in] ctx : Click context object.
 * See #diffpress4_t object definition for detailed explanation.
 * @param[out] temp_data : Temperature data.
 * @param[out] press_data : Pressure data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress4_get_raw_data ( diffpress4_t *ctx, int16_t *temp_data, int16_t *press_data );

/**
 * @brief Diff Press 4 gets the raw data function.
 * @details This function reads the pressure and temperature raw data values
 * of the SM9336, SMI ultra-low pressure digital sensor
 * @param[in] ctx : Click context object.
 * See #diffpress4_t object definition for detailed explanation.
 * @param[out] diff_press : Diff pressure [Pa].
 * @param[out] temperature : Temperature [degree Celsius].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress4_get_measurement_data ( diffpress4_t *ctx, float *diff_press, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // DIFFPRESS4_H

/*! @} */ // diffpress4

// ------------------------------------------------------------------------ END
