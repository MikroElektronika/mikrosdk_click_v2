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
 * @file pressure17.h
 * @brief This file contains API for Pressure 17 Click Driver.
 */

#ifndef PRESSURE17_H
#define PRESSURE17_H

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
 * @addtogroup pressure17 Pressure 17 Click Driver
 * @brief API for configuring and manipulating Pressure 17 Click driver.
 * @{
 */

/**
 * @defgroup pressure17_reg Pressure 17 Registers List
 * @brief List of registers of Pressure 17 Click driver.
 */

/**
 * @addtogroup pressure17_reg
 * @{
 */

/**
 * @brief Pressure 17 Register List.
 * @details Specified Register List of Pressure 17 Click driver.
 */
#define PRESSURE17_REG_MANUFACTURER_ID          0x0F
#define PRESSURE17_REG_PART_ID                  0x10
#define PRESSURE17_REG_POWER_DOWN               0x12
#define PRESSURE17_REG_RESET                    0x13
#define PRESSURE17_REG_MODE_CONTROL             0x14
#define PRESSURE17_REG_IIR_FIFO_CONTROL         0x15
#define PRESSURE17_REG_FIFO_DATA                0x18
#define PRESSURE17_REG_STATUS                   0x19
#define PRESSURE17_REG_PRESS_OUT_MSB            0x1A
#define PRESSURE17_REG_PRESS_OUT_LSB            0x1B
#define PRESSURE17_REG_PRESS_OUT_XL             0x1C
#define PRESSURE17_REG_TEMP_OUT_MSB             0x1D
#define PRESSURE17_REG_TEMP_OUT_LSB             0x1E

/*! @} */ // pressure17_reg

/**
 * @defgroup pressure17_set Pressure 17 Registers Settings
 * @brief Settings for registers of Pressure 17 Click driver.
 */

/**
 * @addtogroup pressure17_set
 * @{
 */

/**
 * @brief Pressure 17 ID values.
 * @details Specified ID values of Pressure 17 Click driver.
 */
#define PRESSURE17_MANUFACTURER_ID              0xE0
#define PRESSURE17_PART_ID                      0x34

/**
 * @brief Pressure 17 Power Down register settings.
 * @details Specified settings for Power Down register of Pressure 17 Click driver.
 */
#define PRESSURE17_POWER_DOWN                   0x00
#define PRESSURE17_POWER_ACTIVE                 0x01

/**
 * @brief Pressure 17 Reset register settings.
 * @details Specified settings for Reset register of Pressure 17 Click driver.
 */
#define PRESSURE17_RSTB_RESET                   0x00
#define PRESSURE17_RSTB_ACTIVE                  0x01

/**
 * @brief Pressure 17 Mode Control register settings.
 * @details Specified settings for Mode Control register of Pressure 17 Click driver.
 */
#define PRESSURE17_MODE_AVE_NUM_8_TIMES         0x60
#define PRESSURE17_MODE_AVE_NUM_16_TIMES        0x80
#define PRESSURE17_MODE_AVE_NUM_32_TIMES        0xA0
#define PRESSURE17_MODE_AVE_NUM_64_TIMES        0xC0
#define PRESSURE17_MODE_DR_EN                   0x10
#define PRESSURE17_MODE_FULL_EN                 0x08
#define PRESSURE17_MODE_WTM_EN                  0x04
#define PRESSURE17_MODE_STANDBY_MODE            0x00
#define PRESSURE17_MODE_ONE_SHOT_MODE           0x01
#define PRESSURE17_MODE_CONTINUOUS_MODE         0x02

/**
 * @brief Pressure 17 IIR/FIFO Control register settings.
 * @details Specified settings for FIFO Control register of Pressure 17 Click driver.
 */
#define PRESSURE17_FIFO_EN                      0x80
#define PRESSURE17_WTM_LEVEL_2                  0x00
#define PRESSURE17_WTM_LEVEL_3                  0x40
#define PRESSURE17_IIR_OFF                      0x00
#define PRESSURE17_IIR_ON_WEAK                  0x01
#define PRESSURE17_IIR_ON_MIDDLE                0x02
#define PRESSURE17_IIR_ON_STRONG                0x03

/**
 * @brief Pressure 17 FIFO data register settings.
 * @details Specified settings for FIFO Control register of Pressure 17 Click driver.
 */
#define PRESSURE17_FIFO_LVL_FIFO_EMPTY          0x00
#define PRESSURE17_FIFO_LVL_FIFO_NUM_1          0x01
#define PRESSURE17_FIFO_LVL_FIFO_NUM_2          0x02
#define PRESSURE17_FIFO_LVL_FIFO_NUM_3          0x03
#define PRESSURE17_FIFO_LVL_FIFO_FULL           0x04

/**
 * @brief Pressure 17 STATUS register settings.
 * @details Specified settings for STATUS register of Pressure 17 Click driver.
 */
#define PRESSURE17_STATUS_RD_FULL               0x04
#define PRESSURE17_STATUS_RD_WTM                0x02
#define PRESSURE17_STATUS_RD_DRDY               0x01

/**
 * @brief Pressure 17 pressure and temperature calculation constants.
 * @details Specified pressure and temperature calculation constants of Pressure 17 Click driver.
 */
#define PRESSURE17_PRESS_COUNTS_PER_MBAR        2048
#define PRESSURE17_TEMP_COUNTS_PER_C            32

/**
 * @brief Pressure 17 device address setting.
 * @details Specified setting for device slave address selection of
 * Pressure 17 Click driver.
 */
#define PRESSURE17_SET_DEV_ADDR                 0x5D

/*! @} */ // pressure17_set

/**
 * @defgroup pressure17_map Pressure 17 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 17 Click driver.
 */

/**
 * @addtogroup pressure17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 17 Click to the selected MikroBUS.
 */
#define PRESSURE17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pressure17_map
/*! @} */ // pressure17

/**
 * @brief Pressure 17 Click context object.
 * @details Context object definition of Pressure 17 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} pressure17_t;

/**
 * @brief Pressure 17 Click configuration object.
 * @details Configuration object definition of Pressure 17 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} pressure17_cfg_t;

/**
 * @brief Pressure 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESSURE17_OK = 0,
    PRESSURE17_ERROR = -1

} pressure17_return_value_t;

/*!
 * @addtogroup pressure17 Pressure 17 Click Driver
 * @brief API for configuring and manipulating Pressure 17 Click driver.
 * @{
 */

/**
 * @brief Pressure 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure17_cfg_setup ( pressure17_cfg_t *cfg );

/**
 * @brief Pressure 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pressure17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure17_init ( pressure17_t *ctx, pressure17_cfg_t *cfg );

/**
 * @brief Pressure 17 default configuration function.
 * @details This function executes a default configuration of Pressure 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #pressure17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pressure17_default_cfg ( pressure17_t *ctx );

/**
 * @brief Pressure 17 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure17_generic_write ( pressure17_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Pressure 17 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure17_generic_read ( pressure17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Pressure 17 write register function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure17_write_register ( pressure17_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Pressure 17 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure17_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure17_read_register ( pressure17_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Pressure 17 check communication function.
 * @details This function checks the communication by reading and verifying the manufacturer and part IDs.
 * @param[in] ctx : Click context object.
 * See #pressure17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure17_check_communication ( pressure17_t *ctx );

/**
 * @brief Pressure 17 read data function.
 * @details This function checks if the data is ready and then reads the pressure and temperature
 * raw data and converts them to millibar and Celsius respectfully.
 * @param[in] ctx : Click context object.
 * See #pressure17_t object definition for detailed explanation.
 * @param[out] pressure : Pressure data [mbar].
 * @param[out] temperature : Temperature data [Celsius].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure17_read_data ( pressure17_t *ctx, float *pressure, float *temperature );

/**
 * @brief Pressure 17 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #pressure17_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t pressure17_get_int_pin ( pressure17_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE17_H

/*! @} */ // pressure17

// ------------------------------------------------------------------------ END
