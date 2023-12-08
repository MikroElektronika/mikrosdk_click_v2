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
 * @file illuminance.h
 * @brief This file contains API for Illuminance Click Driver.
 */

#ifndef ILLUMINANCE_H
#define ILLUMINANCE_H

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
 * @addtogroup illuminance Illuminance Click Driver
 * @brief API for configuring and manipulating Illuminance Click driver.
 * @{
 */

/**
 * @defgroup illuminance_reg Illuminance Registers List
 * @brief List of registers of Illuminance Click driver.
 */

/**
 * @addtogroup illuminance_reg
 * @{
 */

/**
 * @brief Illuminance registers list.
 * @details Specified registers list of Illuminance Click driver.
 */
#define ILLUMINANCE_REG_CONTROL               0x00
#define ILLUMINANCE_REG_TIMING                0x01
#define ILLUMINANCE_REG_INTERRUPT             0x02
#define ILLUMINANCE_REG_THL_LOW               0x03
#define ILLUMINANCE_REG_THL_HIGH              0x04
#define ILLUMINANCE_REG_THH_LOW               0x05
#define ILLUMINANCE_REG_THH_HIGH              0x06
#define ILLUMINANCE_REG_ANALOG                0x07
#define ILLUMINANCE_REG_ID                    0x12
#define ILLUMINANCE_REG_DATA0_LOW             0x14
#define ILLUMINANCE_REG_DATA0_HIGH            0x15
#define ILLUMINANCE_REG_DATA1_LOW             0x16
#define ILLUMINANCE_REG_DATA1_HIGH            0x17
#define ILLUMINANCE_REG_TIMER_LOW             0x18
#define ILLUMINANCE_REG_TIMER_HIGH            0x19
#define ILLUMINANCE_REG_ID2                   0x1E

/*! @} */ // illuminance_reg

/**
 * @defgroup illuminance_set Illuminance Registers Settings
 * @brief Settings for registers of Illuminance Click driver.
 */

/**
 * @addtogroup illuminance_set
 * @{
 */

/**
 * @brief Illuminance Command register setting.
 * @details Specified setting for Command register of Illuminance Click driver.
 */
#define ILLUMINANCE_CMD_BIT                   0x80
#define ILLUMINANCE_TRANSACTION_REPEATED      0x00
#define ILLUMINANCE_TRANSACTION_AUTO_INC      0x20
#define ILLUMINANCE_TRANSACTION_SPEC_FUNC     0x60
#define ILLUMINANCE_SPEC_FUNC_INT_CLEAR       0x01
#define ILLUMINANCE_SPEC_FUNC_STOP_MAN_INT    0x02
#define ILLUMINANCE_SPEC_FUNC_START_MAN_INT   0x03

/**
 * @brief Illuminance control register setting.
 * @details Specified setting for control register of Illuminance Click driver.
 */
#define ILLUMINANCE_CONTROL_ADC_INTR          0x20
#define ILLUMINANCE_CONTROL_ADC_VALID         0x10
#define ILLUMINANCE_CONTROL_ADC_ENABLE        0x02
#define ILLUMINANCE_CONTROL_POWER_ON          0x01

/**
 * @brief Illuminance timing register setting.
 * @details Specified setting for timing register of Illuminance Click driver.
 */
#define ILLUMINANCE_ATIME_MAX                 688.5
#define ILLUMINANCE_ATIME_MIN                 2.7
#define ILLUMINANCE_ATIME_STEP                2.7
#define ILLUMINANCE_DEFAULT_ATIME             200.0

/**
 * @brief Illuminance interrupt register setting.
 * @details Specified setting for interrupt register of Illuminance Click driver.
 */
#define ILLUMINANCE_ENABLE_INTERRUPT          0x10

/**
 * @brief Illuminance analog register setting.
 * @details Specified setting for analog register of Illuminance Click driver.
 */
#define ILLUMINANCE_GAIN_1X                   0x00
#define ILLUMINANCE_GAIN_8X                   0x01
#define ILLUMINANCE_GAIN_16X                  0x02
#define ILLUMINANCE_GAIN_111X                 0x03

/**
 * @brief Illuminance ID values.
 * @details Specified ID values of Illuminance Click driver.
 */
#define ILLUMINANCE_ID_PARTNO                 0x90
#define ILLUMINANCE_ID2                       0x30

/**
 * @brief Illuminance device address setting.
 * @details Specified setting for device slave address selection of
 * Illuminance Click driver.
 */
#define ILLUMINANCE_SET_DEV_ADDR_GND          0x29
#define ILLUMINANCE_SET_DEV_ADDR_FLOAT        0x39
#define ILLUMINANCE_SET_DEV_ADDR_VCC          0x49

/*! @} */ // illuminance_set

/**
 * @defgroup illuminance_map Illuminance MikroBUS Map
 * @brief MikroBUS pin mapping of Illuminance Click driver.
 */

/**
 * @addtogroup illuminance_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Illuminance Click to the selected MikroBUS.
 */
#define ILLUMINANCE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // illuminance_map
/*! @} */ // illuminance

/**
 * @brief Illuminance Click context object.
 * @details Context object definition of Illuminance Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;      /**< Interrupt pin (Active low). */

    // Modules
    i2c_master_t  i2c;          /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    float   atime_ms;           /**< ALS time in milliseconds. */
    uint8_t gain;               /**< Gain level. */

} illuminance_t;

/**
 * @brief Illuminance Click configuration object.
 * @details Configuration object definition of Illuminance Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} illuminance_cfg_t;

/**
 * @brief Illuminance Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ILLUMINANCE_OK = 0,
    ILLUMINANCE_ERROR = -1

} illuminance_return_value_t;

/*!
 * @addtogroup illuminance Illuminance Click Driver
 * @brief API for configuring and manipulating Illuminance Click driver.
 * @{
 */

/**
 * @brief Illuminance configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #illuminance_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void illuminance_cfg_setup ( illuminance_cfg_t *cfg );

/**
 * @brief Illuminance initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #illuminance_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #illuminance_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t illuminance_init ( illuminance_t *ctx, illuminance_cfg_t *cfg );

/**
 * @brief Illuminance default configuration function.
 * @details This function executes a default configuration of Illuminance
 * click board.
 * @param[in] ctx : Click context object.
 * See #illuminance_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t illuminance_default_cfg ( illuminance_t *ctx );

/**
 * @brief Illuminance I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #illuminance_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t illuminance_generic_write ( illuminance_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Illuminance I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #illuminance_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t illuminance_generic_read ( illuminance_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Illuminance write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #illuminance_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t illuminance_write_register ( illuminance_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Illuminance read register function.
 * @details This function reads a desired data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #illuminance_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t illuminance_read_register ( illuminance_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Illuminance get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #illuminance_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t illuminance_get_int_pin ( illuminance_t *ctx );

/**
 * @brief Illuminance check communication function.
 * @details This function checks the communication by reading and verifying the chip ID values.
 * @param[in] ctx : Click context object.
 * See #illuminance_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t illuminance_check_communication ( illuminance_t *ctx );

/**
 * @brief Illuminance set atime function.
 * @details This function sets the timing register for the selected integration time.
 * @param[in] ctx : Click context object.
 * See #illuminance_t object definition for detailed explanation.
 * @param[in] atime_ms : Als integration time. Valid values from 2.7 to 688.5 milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t illuminance_set_atime ( illuminance_t *ctx, float atime_ms );

/**
 * @brief Illuminance set gain function.
 * @details This function sets the gain level.
 * @param[in] ctx : Click context object.
 * See #illuminance_t object definition for detailed explanation.
 * @param[in] gain : Gain level value [0-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t illuminance_set_gain ( illuminance_t *ctx, uint8_t gain );

/**
 * @brief Illuminance read raw data function.
 * @details This function checks if the data is ready and then reads the raw ADC data from two channels.
 * @param[in] ctx : Click context object.
 * See #illuminance_t object definition for detailed explanation.
 * @param[out] ch_0 : Raw data from channel 0.
 * @param[out] ch_1 : Raw data from channel 1.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t illuminance_read_raw_data ( illuminance_t *ctx, uint16_t *ch_0, uint16_t *ch_1 );

#ifdef __cplusplus
}
#endif
#endif // ILLUMINANCE_H

/*! @} */ // illuminance

// ------------------------------------------------------------------------ END
