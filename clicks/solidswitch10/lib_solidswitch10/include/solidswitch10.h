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
 * @file solidswitch10.h
 * @brief This file contains API for SolidSwitch 10 Click Driver.
 */

#ifndef SOLIDSWITCH10_H
#define SOLIDSWITCH10_H

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
 * @addtogroup solidswitch10 SolidSwitch 10 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 10 Click driver.
 * @{
 */

/**
 * @defgroup solidswitch10_reg SolidSwitch 10 Registers List
 * @brief List of registers of SolidSwitch 10 Click driver.
 */

/**
 * @addtogroup solidswitch10_reg
 * @{
 */

/**
 * @brief SolidSwitch 10 PCA9536 registers.
 * @details Specified PCA9536 registers of SolidSwitch 10 Click driver.
 */
#define SOLIDSWITCH10_REG_INPUT                 0x00
#define SOLIDSWITCH10_REG_OUTPUT                0x01
#define SOLIDSWITCH10_REG_POLARITY              0x02
#define SOLIDSWITCH10_REG_CONFIG                0x03

/*! @} */ // solidswitch10_reg

/**
 * @defgroup solidswitch10_set SolidSwitch 10 Registers Settings
 * @brief Settings for registers of SolidSwitch 10 Click driver.
 */

/**
 * @addtogroup solidswitch10_set
 * @{
 */

/**
 * @brief SolidSwitch 10 PCA9536 pin mask.
 * @details Specified PCA9536 pin mask of SolidSwitch 10 Click driver.
 */
#define SOLIDSWITCH10_PIN_IPD_1                 0x01
#define SOLIDSWITCH10_PIN_IPD_2                 0x02
#define SOLIDSWITCH10_PIN_IPD_3                 0x04

/**
 * @brief SolidSwitch 10 PCA9536 pin direction config.
 * @details Specified PCA9536 pin direction config of SolidSwitch 10 Click driver.
 */
#define SOLIDSWITCH10_DEFAULT_CONFIG            0xF8

/**
 * @brief SolidSwitch 10 current limit setting.
 * @details Specified current limit setting of SolidSwitch 10 Click driver.
 */
#define SOLIDSWITCH10_ILIMIT_1_2A               0
#define SOLIDSWITCH10_ILIMIT_2A                 1
#define SOLIDSWITCH10_ILIMIT_4A                 2
#define SOLIDSWITCH10_ILIMIT_8_2A               3
#define SOLIDSWITCH10_ILIMIT_12A                4
#define SOLIDSWITCH10_ILIMIT_16_5A              5
#define SOLIDSWITCH10_ILIMIT_22A                6
#define SOLIDSWITCH10_ILIMIT_25A                7

/**
 * @brief SolidSwitch 10 device address setting.
 * @details Specified setting for device slave address selection of
 * SolidSwitch 10 Click driver.
 */
#define SOLIDSWITCH10_DEVICE_ADDRESS            0x41

/*! @} */ // solidswitch10_set

/**
 * @defgroup solidswitch10_map SolidSwitch 10 MikroBUS Map
 * @brief MikroBUS pin mapping of SolidSwitch 10 Click driver.
 */

/**
 * @addtogroup solidswitch10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SolidSwitch 10 Click to the selected MikroBUS.
 */
#define SOLIDSWITCH10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.in_pin = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ovt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // solidswitch10_map
/*! @} */ // solidswitch10

/**
 * @brief SolidSwitch 10 Click context object.
 * @details Context object definition of SolidSwitch 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t in_pin;       /**< IN pin for voltage output state control. */

    // Input pins
    digital_in_t ovt;           /**< Overtemperature pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} solidswitch10_t;

/**
 * @brief SolidSwitch 10 Click configuration object.
 * @details Configuration object definition of SolidSwitch 10 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t in_pin;          /**< IN pin for voltage output state control. */
    pin_name_t ovt;             /**< Overtemperature pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} solidswitch10_cfg_t;

/**
 * @brief SolidSwitch 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SOLIDSWITCH10_OK = 0,
    SOLIDSWITCH10_ERROR = -1

} solidswitch10_return_value_t;

/*!
 * @addtogroup solidswitch10 SolidSwitch 10 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 10 Click driver.
 * @{
 */

/**
 * @brief SolidSwitch 10 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #solidswitch10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void solidswitch10_cfg_setup ( solidswitch10_cfg_t *cfg );

/**
 * @brief SolidSwitch 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #solidswitch10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #solidswitch10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch10_init ( solidswitch10_t *ctx, solidswitch10_cfg_t *cfg );

/**
 * @brief SolidSwitch 10 default configuration function.
 * @details This function executes a default configuration of SolidSwitch 10
 * Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t solidswitch10_default_cfg ( solidswitch10_t *ctx );

/**
 * @brief SolidSwitch 10 write reg function.
 * @details This function writes a desired data byte to the selected PCA9536 register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch10_write_reg ( solidswitch10_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief SolidSwitch 10 read reg function.
 * @details This function reads data from the selected PCA9536 register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch10_read_reg ( solidswitch10_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief SolidSwitch 10 enable output function.
 * @details This function sets the IN pin to high logic level, enabling the low-side switch output.
 * @param[in] ctx : Click context object.
 * See #solidswitch10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solidswitch10_enable_output ( solidswitch10_t *ctx );

/**
 * @brief SolidSwitch 10 disable output function.
 * @details This function sets the IN pin to low logic level, disabling the low-side switch output.
 * @param[in] ctx : Click context object.
 * See #solidswitch10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void solidswitch10_disable_output ( solidswitch10_t *ctx );

/**
 * @brief SolidSwitch 10 get OVT pin function.
 * @details This function reads the logic level of the OVT pin.
 * @param[in] ctx : Click context object.
 * See #solidswitch10_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t solidswitch10_get_ovt_pin ( solidswitch10_t *ctx );

/**
 * @brief SolidSwitch 10 set Ilimit function.
 * @details This function sets the current limit by setting the IPD1-3 pins state.
 * @param[in] ctx : Click context object.
 * See #solidswitch10_t object definition for detailed explanation.
 * @param[in] ilimit : Ilimit setting, see SOLIDSWITCH10_ILIMIT_x macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch10_set_ilimit ( solidswitch10_t *ctx, uint8_t ilimit );

#ifdef __cplusplus
}
#endif
#endif // SOLIDSWITCH10_H

/*! @} */ // solidswitch10

// ------------------------------------------------------------------------ END
