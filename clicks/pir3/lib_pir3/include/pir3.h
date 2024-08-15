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
 * @file pir3.h
 * @brief This file contains API for PIR 3 Click Driver.
 */

#ifndef PIR3_H
#define PIR3_H

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
 * @addtogroup pir3 PIR 3 Click Driver
 * @brief API for configuring and manipulating PIR 3 Click driver.
 * @{
 */

/**
 * @defgroup pir3_set PIR 3 Registers Settings
 * @brief Settings for registers of PIR 3 Click driver.
 */

/**
 * @addtogroup pir3_set
 * @{
 */

/**
 * @brief PIR 3 control register setting.
 * @details Specified setting for control register of PIR 3 Click driver.
 */
#define PIR3_CONFIG_DETLVL_MASK_MSB 0x7F
#define PIR3_CONFIG_DETLVL_MASK_LSB 0x01
#define PIR3_CONFIG_DETLVL_DEFAULT  0x1C
#define PIR3_CONFIG_TRIGOM_DISABLED 0x00
#define PIR3_CONFIG_TRIGOM_ENABLED  0x01
#define PIR3_CONFIG_TRIGOM_MASK     0x01
#define PIR3_CONFIG_TRIGOM_DEFAULT  PIR3_CONFIG_TRIGOM_DISABLED
#define PIR3_CONFIG_FSTEP_1         0x01
#define PIR3_CONFIG_FSTEP_2         0x03
#define PIR3_CONFIG_FSTEP_3         0x00
#define PIR3_CONFIG_FSTEP_MASK      0x03
#define PIR3_CONFIG_FSTEP_DEFAULT   PIR3_CONFIG_FSTEP_2
#define PIR3_CONFIG_FILSEL_TYPE_A   0x07
#define PIR3_CONFIG_FILSEL_TYPE_B   0x00
#define PIR3_CONFIG_FILSEL_TYPE_C   0x01
#define PIR3_CONFIG_FILSEL_TYPE_D   0x02
#define PIR3_CONFIG_FILSEL_DIRECT   0x03
#define PIR3_CONFIG_FILSEL_MASK     0x07
#define PIR3_CONFIG_FILSEL_DEFAULT  PIR3_CONFIG_FILSEL_TYPE_B

/**
 * @brief PIR 3 device address setting.
 * @details Specified setting for device slave address selection of
 * PIR 3 Click driver.
 */
#define PIR3_DEVICE_ADDRESS         0x00

/*! @} */ // pir3_set

/**
 * @defgroup pir3_map PIR 3 MikroBUS Map
 * @brief MikroBUS pin mapping of PIR 3 Click driver.
 */

/**
 * @addtogroup pir3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PIR 3 Click to the selected MikroBUS.
 */
#define PIR3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // pir3_map
/*! @} */ // pir3

/**
 * @brief PIR 3 Click config object.
 * @details Config object definition of PIR 3 Click driver.
 */
typedef struct
{
    uint8_t detlvl;             /**< Detection Threshold Level. */
    uint8_t trigom;             /**< Trigger Output Mode:: 0-disabled, 1-enabled. */
    uint8_t fstep;              /**< Digital Band-Pass Filter Step Selection. */
    uint8_t filsel;             /**< Digital Band-Pass Filter Type Selection. */

} pir3_config_t;

/**
 * @brief PIR 3 Click context object.
 * @details Context object definition of PIR 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t on;           /**< Enable pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */           

    pir3_config_t config;       /**< Sensor device config. */

} pir3_t;

/**
 * @brief PIR 3 Click configuration object.
 * @details Configuration object definition of PIR 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t on;              /**< Enable pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} pir3_cfg_t;

/**
 * @brief PIR 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PIR3_OK = 0,
    PIR3_ERROR = -1

} pir3_return_value_t;

/*!
 * @addtogroup pir3 PIR 3 Click Driver
 * @brief API for configuring and manipulating PIR 3 Click driver.
 * @{
 */

/**
 * @brief PIR 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pir3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pir3_cfg_setup ( pir3_cfg_t *cfg );

/**
 * @brief PIR 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pir3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pir3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir3_init ( pir3_t *ctx, pir3_cfg_t *cfg );

/**
 * @brief PIR 3 default configuration function.
 * @details This function executes a default configuration of PIR 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #pir3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pir3_default_cfg ( pir3_t *ctx );

/**
 * @brief PIR 3 write config function.
 * @details This function writes a config structure to the sensor by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pir3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir3_write_config ( pir3_t *ctx );

/**
 * @brief PIR 3 read peak hold function.
 * @details This function reads a 12-bit signed peak hold data by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pir3_t object definition for detailed explanation.
 * @param[out] peak_hold : 12-bit signed peak hold data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pir3_read_peak_hold ( pir3_t *ctx, int16_t *peak_hold );

/**
 * @brief PIR 3 enable device function.
 * @details This function enables the device by setting the ON pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #pir3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void pir3_enable_device ( pir3_t *ctx );

/**
 * @brief PIR 3 disable device function.
 * @details This function disables the device by setting the OFF pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #pir3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void pir3_disable_device ( pir3_t *ctx );

/**
 * @brief PIR 3 set detection level function.
 * @details This function sets the detection threshold level in the ctx->config structure.
 * @param[in] ctx : Click context object.
 * See #pir3_t object definition for detailed explanation.
 * @param[in] detlvl : Detection threshold level.
 * @return None.
 * @note The config changes are applied using the pir3_write_config function.
 */
void pir3_set_detection_level ( pir3_t *ctx, uint8_t detlvl );

/**
 * @brief PIR 3 set trigger out function.
 * @details This function sets the trigger output mode in the ctx->config structure.
 * @param[in] ctx : Click context object.
 * See #pir3_t object definition for detailed explanation.
 * @param[in] trigom : Trigger output mode: 0-disabled, 1-enabled.
 * @return None.
 * @note The config changes are applied using the pir3_write_config function.
 */
void pir3_set_trigger_out ( pir3_t *ctx, uint8_t trigom );

/**
 * @brief PIR 3 set filter step function.
 * @details This function sets the digital band-pass filter step selection in the ctx->config structure.
 * @param[in] ctx : Click context object.
 * See #pir3_t object definition for detailed explanation.
 * @param[in] fstep : Filter step selection: 1-step 1, 3-step 2, 0-step 3.
 * @return None.
 * @note The config changes are applied using the pir3_write_config function.
 */
void pir3_set_filter_step ( pir3_t *ctx, uint8_t fstep );

/**
 * @brief PIR 3 set filter type function.
 * @details This function sets the digital band-pass filter type selection in the ctx->config structure.
 * @param[in] ctx : Click context object.
 * See #pir3_t object definition for detailed explanation.
 * @param[in] filsel : Filter type selection: 7-A, 0-B, 1-C, 2-D, 3-digital.
 * @return None.
 * @note The config changes are applied using the pir3_write_config function.
 */
void pir3_set_filter_type ( pir3_t *ctx, uint8_t filsel );

#ifdef __cplusplus
}
#endif
#endif // PIR3_H

/*! @} */ // pir3

// ------------------------------------------------------------------------ END
