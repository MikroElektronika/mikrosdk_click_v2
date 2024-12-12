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
 * @file rotaryswitch.h
 * @brief This file contains API for Rotary Switch Click Driver.
 */

#ifndef ROTARYSWITCH_H
#define ROTARYSWITCH_H

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
 * @addtogroup rotaryswitch Rotary Switch Click Driver
 * @brief API for configuring and manipulating Rotary Switch Click driver.
 * @{
 */

/**
 * @defgroup rotaryswitch_reg Rotary Switch Registers List
 * @brief List of registers of Rotary Switch Click driver.
 */

/**
 * @addtogroup rotaryswitch_reg
 * @{
 */

/**
 * @brief Rotary Switch register list.
 * @details Specified register list of Rotary Switch Click driver.
 */
#define ROTARYSWITCH_REG_INPUT_PORT             0x00
#define ROTARYSWITCH_REG_OUTPUT_PORT            0x01
#define ROTARYSWITCH_REG_POLARITY_INV           0x02
#define ROTARYSWITCH_REG_CONFIG                 0x03
#define ROTARYSWITCH_REG_SPECIAL_FUNC           0x50

/*! @} */ // rotaryswitch_reg

/**
 * @defgroup rotaryswitch_set Rotary Switch Registers Settings
 * @brief Settings for registers of Rotary Switch Click driver.
 */

/**
 * @addtogroup rotaryswitch_set
 * @{
 */

/**
 * @brief Rotary Switch default register settings.
 * @details Specified default register settings. of Rotary Switch Click driver.
 */
#define ROTARYSWITCH_CONFIG_DEFAULT             0xFF
#define ROTARYSWITCH_POLARITY_INV_DEFAULT       0x0F
#define ROTARYSWITCH_SPECIAL_FUNC_DEFAULT       0x00

/**
 * @brief Rotary Switch pin mask values.
 * @details Specified pin mask values of Rotary Switch Click driver.
 */
#define ROTARYSWITCH_NO_PIN_MASK                0x00
#define ROTARYSWITCH_PIN_0_MASK                 0x01
#define ROTARYSWITCH_PIN_1_MASK                 0x02
#define ROTARYSWITCH_PIN_2_MASK                 0x04
#define ROTARYSWITCH_PIN_3_MASK                 0x08
#define ROTARYSWITCH_ALL_PINS_MASK              0x0F

/**
 * @brief Rotary Switch device address setting.
 * @details Specified setting for device slave address selection of
 * Rotary Switch Click driver.
 */
#define ROTARYSWITCH_DEVICE_ADDRESS             0x41

/*! @} */ // rotaryswitch_set

/**
 * @defgroup rotaryswitch_map Rotary Switch MikroBUS Map
 * @brief MikroBUS pin mapping of Rotary Switch Click driver.
 */

/**
 * @addtogroup rotaryswitch_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Rotary Switch Click to the selected MikroBUS.
 */
#define ROTARYSWITCH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // rotaryswitch_map
/*! @} */ // rotaryswitch

/**
 * @brief Rotary Switch Click context object.
 * @details Context object definition of Rotary Switch Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} rotaryswitch_t;

/**
 * @brief Rotary Switch Click configuration object.
 * @details Configuration object definition of Rotary Switch Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} rotaryswitch_cfg_t;

/**
 * @brief Rotary Switch Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ROTARYSWITCH_OK = 0,
    ROTARYSWITCH_ERROR = -1

} rotaryswitch_return_value_t;

/*!
 * @addtogroup rotaryswitch Rotary Switch Click Driver
 * @brief API for configuring and manipulating Rotary Switch Click driver.
 * @{
 */

/**
 * @brief Rotary Switch configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rotaryswitch_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rotaryswitch_cfg_setup ( rotaryswitch_cfg_t *cfg );

/**
 * @brief Rotary Switch initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rotaryswitch_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rotaryswitch_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rotaryswitch_init ( rotaryswitch_t *ctx, rotaryswitch_cfg_t *cfg );

/**
 * @brief Rotary Switch default configuration function.
 * @details This function executes a default configuration of Rotary Switch
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rotaryswitch_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rotaryswitch_default_cfg ( rotaryswitch_t *ctx );

/**
 * @brief Rotary Switch write reg function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rotaryswitch_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rotaryswitch_write_reg ( rotaryswitch_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Rotary Switch read reg function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rotaryswitch_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rotaryswitch_read_reg ( rotaryswitch_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Rotary Switch get position function.
 * @details This function reads the rotary switch position.
 * @param[in] ctx : Click context object.
 * See #rotaryswitch_t object definition for detailed explanation.
 * @param[out] position : Switch position [0-F].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rotaryswitch_get_position ( rotaryswitch_t *ctx, uint8_t *position );

#ifdef __cplusplus
}
#endif
#endif // ROTARYSWITCH_H

/*! @} */ // rotaryswitch

// ------------------------------------------------------------------------ END
