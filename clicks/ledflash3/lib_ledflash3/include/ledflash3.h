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
 * @file ledflash3.h
 * @brief This file contains API for LED Flash 3 Click Driver.
 */

#ifndef LEDFLASH3_H
#define LEDFLASH3_H

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
 * @addtogroup ledflash3 LED Flash 3 Click Driver
 * @brief API for configuring and manipulating LED Flash 3 Click driver.
 * @{
 */

/**
 * @defgroup ledflash3_reg LED Flash 3 Registers List
 * @brief List of registers of LED Flash 3 Click driver.
 */

/**
 * @addtogroup ledflash3_reg
 * @{
 */

/**
 * @brief LED Flash 3 description register.
 * @details Specified register for description of LED Flash 3 Click driver.
 */
#define LEDFLASH3_REG_ENABLE                0x01
#define LEDFLASH3_REG_CONFIGURATION         0x02
#define LEDFLASH3_REG_FLASH_CURRENT         0x03
#define LEDFLASH3_REG_TOUCH_CURRENT         0x04
#define LEDFLASH3_REG_FAULT_FLAG            0x05
#define LEDFLASH3_REG_DEVICE_ID             0x06

/*! @} */ // ledflash3_reg

/**
 * @defgroup ledflash3_set LED Flash 3 Registers Settings
 * @brief Settings for registers of LED Flash 3 Click driver.
 */

/**
 * @addtogroup ledflash3_set
 * @{
 */

/**
 * @brief LED Flash 3 description setting.
 * @details Specified setting for description of LED Flash 3 Click driver.
 */
#define LEDFLASH3_LVP_ENABLE            0x10
#define LEDFLASH3_STROBE_LEVEL          0x00
#define LEDFLASH3_STROBE_EDGE           0x08
#define LEDFLASH3_STROBE_PIN_ENABLE     0x04
#define LEDFLASH3_MODE_FLASH            0x03
#define LEDFLASH3_MODE_TORCH            0x02
#define LEDFLASH3_MODE_IR               0x01
#define LEDFLASH3_MODE_STANDBY          0x00

/**
 * @brief LED Flash 3 Configuration register setting.
 * @details Specified setting for configuration register of LED Flash 3 Click driver.
 */
#define LEDFLASH3_LVP_THRESHOLD_2V9     0x00
#define LEDFLASH3_LVP_THRESHOLD_3V      0x02
#define LEDFLASH3_LVP_THRESHOLD_3V1     0x04
#define LEDFLASH3_LVP_THRESHOLD_3V2     0x06
#define LEDFLASH3_LVP_THRESHOLD_3V3     0x08
#define LEDFLASH3_LVP_THRESHOLD_3V4     0x0A
#define LEDFLASH3_LVP_THRESHOLD_3V5     0x0C
#define LEDFLASH3_LVP_THRESHOLD_3V6     0x0E
#define LEDFLASH3_TIME_OUT_40MS         0x00
#define LEDFLASH3_TIME_OUT_80MS         0x02
#define LEDFLASH3_TIME_OUT_120MS        0x04
#define LEDFLASH3_TIME_OUT_160MS        0x06
#define LEDFLASH3_TIME_OUT_200MS        0x08
#define LEDFLASH3_TIME_OUT_240MS        0x0A
#define LEDFLASH3_TIME_OUT_280MS        0x0C
#define LEDFLASH3_TIME_OUT_320MS        0x0E
#define LEDFLASH3_TIME_OUT_360MS        0x10
#define LEDFLASH3_TIME_OUT_400MS        0x12
#define LEDFLASH3_TIME_OUT_600MS        0x14
#define LEDFLASH3_TIME_OUT_800MS        0x16
#define LEDFLASH3_TIME_OUT_1000MS       0x18
#define LEDFLASH3_TIME_OUT_1200MS       0x1A
#define LEDFLASH3_TIME_OUT_1400MS       0x1C
#define LEDFLASH3_TIME_OUT_1600MS       0x1E
#define LEDFLASH3_TORCH_RAMP_TIME_1MS   0x01

/**
 * @brief LED Flash 3 Fault register setting.
 * @details Specified setting for fault register of LED Flash 3 Click driver.
 */
#define LEDFLASH3_LVP_FAULT_MASK        0x40
#define LEDFLASH3_LED_SHORT_FAULT_MASK  0x20
#define LEDFLASH3_THERMAL_SHDN_MASK     0x04
#define LEDFLASH3_THERMAL_SHDN_MASK     0x04
#define LEDFLASH3_OVLO_FAULT_MASK       0x02
#define LEDFLASH3_FLASH_TIMEOUT_MASK    0x01

/**
 * @brief LED Flash 3 software reset.
 * @details Specified software reset command of LED Flash 3 Click driver.
 */
#define LEDFLASH3_SW_RESET_MASK         0x80

/**
 * @brief LED Flash 3 Fault register setting.
 * @details Specified setting for fault register of LED Flash 3 Click driver.
 */
#define LEDFLASH3_TORCH_CURRENT_MAX     376.0f
#define LEDFLASH3_TORCH_CURRENT_MIN     2.94f
#define LEDFLASH3_FLASH_CURRENT_MAX     1500.0f
#define LEDFLASH3_FLASH_CURRENT_MIN     11.72f
#define LEDFLASH3_ROUND_TO_NEAR_INT     0.5f

/**
 * @brief LED Flash 3 device address setting.
 * @details Specified setting for device slave address selection of
 * LED Flash 3 Click driver.
 */
#define LEDFLASH3_DEVICE_ADDRESS        0x64

/*! @} */ // ledflash3_set

/**
 * @defgroup ledflash3_map LED Flash 3 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Flash 3 Click driver.
 */

/**
 * @addtogroup ledflash3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Flash 3 Click to the selected MikroBUS.
 */
#define LEDFLASH3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // ledflash3_map
/*! @} */ // ledflash3

/**
 * @brief LED Flash 3 Click context object.
 * @details Context object definition of LED Flash 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t stb;          /**< Strobe pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} ledflash3_t;

/**
 * @brief LED Flash 3 Click configuration object.
 * @details Configuration object definition of LED Flash 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t stb;             /**< Strobe pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} ledflash3_cfg_t;

/**
 * @brief LED Flash 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDFLASH3_OK = 0,
    LEDFLASH3_ERROR = -1

} ledflash3_return_value_t;

/*!
 * @addtogroup ledflash3 LED Flash 3 Click Driver
 * @brief API for configuring and manipulating LED Flash 3 Click driver.
 * @{
 */

/**
 * @brief LED Flash 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ledflash3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ledflash3_cfg_setup ( ledflash3_cfg_t *cfg );

/**
 * @brief LED Flash 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ledflash3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ledflash3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash3_init ( ledflash3_t *ctx, ledflash3_cfg_t *cfg );

/**
 * @brief LED Flash 3 default configuration function.
 * @details This function executes a default configuration of LED Flash 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #ledflash3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ledflash3_default_cfg ( ledflash3_t *ctx );

/**
 * @brief LED Flash 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ledflash3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash3_generic_write ( ledflash3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LED Flash 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ledflash3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash3_generic_read ( ledflash3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LED Flash 3 register writing function.
 * @details This function writes a data byte into
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ledflash3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash3_write_reg ( ledflash3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LED Flash 3 regiister reading function.
 * @details This function reads a data byte from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #ledflash3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash3_read_reg ( ledflash3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LED Flash 3 strobe function.
 * @details This function is used to generate strobe signal.
 * @param[in] ctx : Click context object.
 * See #ledflash3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void ledflash3_strobe_pin ( ledflash3_t *ctx );

/**
 * @brief LED Flash 3 set flash current function.
 * @details This function is used to set flash current value in mA.
 * @param[in] ctx : Click context object.
 * See #ledflash3_t object definition for detailed explanation.
 * @param[in] flash_current : Flash current in mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash3_set_flash_current ( ledflash3_t *ctx, float flash_current );

/**
 * @brief LED Flash 3 set torch current function.
 * @details This function is used to set torch current value in mA.
 * @param[in] ctx : Click context object.
 * See #ledflash3_t object definition for detailed explanation.
 * @param[in] torch_current : Torch current in mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ledflash3_set_torch_current ( ledflash3_t *ctx, float torch_current );

#ifdef __cplusplus
}
#endif
#endif // LEDFLASH3_H

/*! @} */ // ledflash3

// ------------------------------------------------------------------------ END
