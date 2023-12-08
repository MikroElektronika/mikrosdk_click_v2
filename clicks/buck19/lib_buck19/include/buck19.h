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
 * @file buck19.h
 * @brief This file contains API for Buck 19 Click Driver.
 */

#ifndef BUCK19_H
#define BUCK19_H

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
 * @addtogroup buck19 Buck 19 Click Driver
 * @brief API for configuring and manipulating Buck 19 Click driver.
 * @{
 */

/**
 * @defgroup buck19_reg Buck 19 Registers List
 * @brief List of registers of Buck 19 Click driver.
 */

/**
 * @addtogroup buck19_reg
 * @{
 */

/**
 * @brief Buck 19 register map.
 * @details Specified register map of Buck 19 Click driver.
 */
#define BUCK19_REG_VOUT                 0x00
#define BUCK19_REG_ILIMIT               0x01
#define BUCK19_REG_INT_STATUS           0x02
#define BUCK19_REG_INT_LATCH            0x03
#define BUCK19_REG_INT_MASK             0x04
#define BUCK19_REG_CONFIG_0             0x05
#define BUCK19_REG_CONFIG_1             0x06

/*! @} */ // buck19_reg

/**
 * @defgroup buck19_set Buck 19 Registers Settings
 * @brief Settings for registers of Buck 19 Click driver.
 */

/**
 * @addtogroup buck19_set
 * @{
 */

/**
 * @brief Buck 19 vout register setting.
 * @details Specified setting for vout register of Buck 19 Click driver.
 */
#define BUCK19_VOUT_MIN                 3.0f
#define BUCK19_VOUT_MAX                 20.0f
#define BUCK19_VOUT_DEFAULT             5.0f
#define BUCK19_VOUT_11V                 11.0f
#define BUCK19_VOUT_11V_STEP            0.2f
#define BUCK19_VOUT_5p9V                5.9f
#define BUCK19_VOUT_5p9V_STEP           0.1f
#define BUCK19_VOUT_STEP                0.02f
#define BUCK19_FLOAT_COMPARE_TOLERANCE  0.0001f

/**
 * @brief Buck 19 ilimit register setting.
 * @details Specified setting for ilimit register of Buck 19 Click driver.
 */
#define BUCK19_ILIMIT_MIN               100
#define BUCK19_ILIMIT_MAX               3000
#define BUCK19_ILIMIT_STEP              100
#define BUCK19_ILIMIT_DEFAULT           500

/**
 * @brief Buck 19 interrupt registers setting.
 * @details Specified setting for interrupt registers of Buck 19 Click driver.
 */
#define BUCK19_INT_INDUCTOR_PCP         0x80
#define BUCK19_INT_OT_WARNING           0x40
#define BUCK19_INT_OT_PROTECT           0x20
#define BUCK19_INT_WATCHDOG             0x10
#define BUCK19_INT_POWER_ON             0x08
#define BUCK19_INT_SHORT_PROTECT        0x04
#define BUCK19_INT_CC_FUNCTION          0x02
#define BUCK19_INT_OV_PROTECT           0x01
#define BUCK19_INT_DISABLE_ALL          0x00

/**
 * @brief Buck 19 config 0 register setting.
 * @details Specified setting for config 0 register of Buck 19 Click driver.
 */
#define BUCK19_CONFIG_0_WATCHDOG_100MS  0x00
#define BUCK19_CONFIG_0_WATCHDOG_500MS  0x40
#define BUCK19_CONFIG_0_WATCHDOG_1S     0x80
#define BUCK19_CONFIG_0_WATCHDOG_5S     0xC0
#define BUCK19_CONFIG_0_CDC_OFF         0x00
#define BUCK19_CONFIG_0_CDC_FULL        0x10
#define BUCK19_CONFIG_0_SW_FREQ_500KHZ  0x00
#define BUCK19_CONFIG_0_SW_FREQ_750KHZ  0x04
#define BUCK19_CONFIG_0_DITHERING_OFF   0x00
#define BUCK19_CONFIG_0_DITHERING_ON    0x02
#define BUCK19_CONFIG_0_DISCHARGE_OFF   0x00
#define BUCK19_CONFIG_0_DISCHARGE_ON    0x01

/**
 * @brief Buck 19 config 1 register setting.
 * @details Specified setting for config 1 register of Buck 19 Click driver.
 */
#define BUCK19_CONFIG_1_WATCHDOG_EN_OFF 0x00
#define BUCK19_CONFIG_1_WATCHDOG_EN_ON  0x02
#define BUCK19_CONFIG_1_DIG_EN_OFF      0x00
#define BUCK19_CONFIG_1_DIG_EN_ON       0x01

/**
 * @brief Buck 19 device address setting.
 * @details Specified setting for device slave address selection of
 * Buck 19 Click driver.
 */
#define BUCK19_DEVICE_ADDRESS_VCC       0x04
#define BUCK19_DEVICE_ADDRESS_GND       0x05
#define BUCK19_DEVICE_ADDRESS_SDA       0x06
#define BUCK19_DEVICE_ADDRESS_SCL       0x07

/*! @} */ // buck19_set

/**
 * @defgroup buck19_map Buck 19 MikroBUS Map
 * @brief MikroBUS pin mapping of Buck 19 Click driver.
 */

/**
 * @addtogroup buck19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck 19 Click to the selected MikroBUS.
 */
#define BUCK19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pon = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // buck19_map
/*! @} */ // buck19

/**
 * @brief Buck 19 Click context object.
 * @details Context object definition of Buck 19 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (Active low). */

    // Input pins
    digital_in_t pon;           /**< Power-on pin (Pulled high when Vout reaches the regulation value after startup). */
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} buck19_t;

/**
 * @brief Buck 19 Click configuration object.
 * @details Configuration object definition of Buck 19 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t pon;             /**< Power-on pin (Pulled high when Vout reaches the regulation value after startup). */
    pin_name_t en;              /**< Enable pin (Active high). */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} buck19_cfg_t;

/**
 * @brief Buck 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUCK19_OK = 0,
    BUCK19_ERROR = -1

} buck19_return_value_t;

/*!
 * @addtogroup buck19 Buck 19 Click Driver
 * @brief API for configuring and manipulating Buck 19 Click driver.
 * @{
 */

/**
 * @brief Buck 19 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buck19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buck19_cfg_setup ( buck19_cfg_t *cfg );

/**
 * @brief Buck 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buck19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buck19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck19_init ( buck19_t *ctx, buck19_cfg_t *cfg );

/**
 * @brief Buck 19 default configuration function.
 * @details This function executes a default configuration of Buck 19
 * click board.
 * @param[in] ctx : Click context object.
 * See #buck19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t buck19_default_cfg ( buck19_t *ctx );

/**
 * @brief Buck 19 write register function.
 * @details This function writes a desired data to the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck19_write_register ( buck19_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Buck 19 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #buck19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck19_read_register ( buck19_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Buck 19 enable device function.
 * @details This function enables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #buck19_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void buck19_enable_device ( buck19_t *ctx );

/**
 * @brief Buck 19 disable device function.
 * @details This function disables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #buck19_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void buck19_disable_device ( buck19_t *ctx );

/**
 * @brief Buck 19 get pon pin function.
 * @details This function returns the Power-on (PON) pin logic state.
 * @param[in] ctx : Click context object.
 * See #buck19_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t buck19_get_pon_pin ( buck19_t *ctx );

/**
 * @brief Buck 19 get int pin function.
 * @details This function returns the interrupt (INT) pin logic state.
 * @param[in] ctx : Click context object.
 * See #buck19_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t buck19_get_int_pin ( buck19_t *ctx );

/**
 * @brief Buck 19 set vout function.
 * @details This function sets the voltage output.
 * @param[in] ctx : Click context object.
 * See #buck19_t object definition for detailed explanation.
 * @param[in] vout : Voltage output. Valid values from 3.0 to 20.0 V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck19_set_vout ( buck19_t *ctx, float vout );

/**
 * @brief Buck 19 set ilimit function.
 * @details This function sets the current limit.
 * @param[in] ctx : Click context object.
 * See #buck19_t object definition for detailed explanation.
 * @param[in] ilimit : Current limit. Valid values from 100 to 3000 mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck19_set_ilimit ( buck19_t *ctx, uint16_t ilimit );

#ifdef __cplusplus
}
#endif
#endif // BUCK19_H

/*! @} */ // buck19

// ------------------------------------------------------------------------ END
