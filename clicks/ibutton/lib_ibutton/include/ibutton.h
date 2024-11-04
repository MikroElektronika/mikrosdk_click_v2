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
 * @file ibutton.h
 * @brief This file contains API for iButton Click Driver.
 */

#ifndef IBUTTON_H
#define IBUTTON_H

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
#include "drv_one_wire.h"

/*!
 * @addtogroup ibutton iButton Click Driver
 * @brief API for configuring and manipulating iButton Click driver.
 * @{
 */

/**
 * @defgroup ibutton_cmd iButton Commands List
 * @brief List of commands of iButton Click driver.
 */

/**
 * @addtogroup ibutton_cmd
 * @{
 */

/**
 * @brief iButton commands list.
 * @details Specified commands list of iButton Click driver.
 */
#define IBUTTON_CMD_WRITE_SCRATCHPAD      0x4E
#define IBUTTON_CMD_READ_SCRATCHPAD       0xBE

/*! @} */ // ibutton_cmd

/**
 * @defgroup ibutton_set iButton Settings
 * @brief Settings of iButton Click driver.
 */

/**
 * @addtogroup ibutton_set
 * @{
 */

/**
 * @brief iButton family code value.
 * @details Specified family code value of iButton Click driver.
 */
#define IBUTTON_FAMILY_CODE             0x01

/**
 * @brief iButton max key number.
 * @details Specified max key number of iButton Click driver.
 */
#define IBUTTON_MAX_KEY_NUMBER          5

/*! @} */ // ibutton_set

/**
 * @defgroup ibutton_map iButton MikroBUS Map
 * @brief MikroBUS pin mapping of iButton Click driver.
 */

/**
 * @addtogroup ibutton_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of iButton Click to the selected MikroBUS.
 */
#define IBUTTON_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.st1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.st2 = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // ibutton_map
/*! @} */ // ibutton

/**
 * @brief iButton Click gpio selector.
 * @details Selects gpio pin of iButton Click driver.
 */
typedef enum
{
    IBUTTON_GPIO_0,                 /**< GPIO 0 pin. */
    IBUTTON_GPIO_1                  /**< GPIO 1 pin. */

} ibutton_gpio_sel_t;

/**
 * @brief iButton Click context object.
 * @details Context object definition of iButton Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t st2;              /**< Red LED control pin. */
    digital_out_t st1;              /**< Green LED control pin. */

    // Modules
    one_wire_t ow;                  /**< One Wire driver object. */

    one_wire_rom_address_t key_rom[ IBUTTON_MAX_KEY_NUMBER ];   /**< ROM address of device keys. */
    uint8_t num_keys;               /**< Number of registered keys. */

} ibutton_t;

/**
 * @brief iButton Click configuration object.
 * @details Configuration object definition of iButton Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t gp0;                 /**< GPIO 0 pin. */
    pin_name_t gp1;                 /**< GPIO 1 pin. */

    // Additional gpio pins
    pin_name_t st2;                 /**< Red LED control pin. */
    pin_name_t st1;                 /**< Green LED control pin. */

    ibutton_gpio_sel_t gpio_sel;    /**< GPIO selection. */

} ibutton_cfg_t;

/**
 * @brief iButton Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IBUTTON_OK = 0,
    IBUTTON_ERROR = -1,
    IBUTTON_KEY_ALREADY_EXIST = -2,
    IBUTTON_KEY_NO_MATCH = -3

} ibutton_return_value_t;

/**
 * @brief iButton Click led indication state.
 * @details Predefined enum values for led indication state.
 */
typedef enum
{
    IBUTTON_LED_DISABLE,
    IBUTTON_LED_WAIT_KEY,
    IBUTTON_LED_SUCCESS,
    IBUTTON_LED_WRONG_KEY

} ibutton_led_state_t;

/*!
 * @addtogroup ibutton iButton Click Driver
 * @brief API for configuring and manipulating iButton Click driver.
 * @{
 */

/**
 * @brief iButton configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ibutton_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ibutton_cfg_setup ( ibutton_cfg_t *cfg );

/**
 * @brief iButton driver interface setup function.
 * @details This function sets a communication GPIO pin which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #ibutton_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO pin selection.
 * See #ibutton_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This gpio selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void ibutton_gpio_selection ( ibutton_cfg_t *cfg, ibutton_gpio_sel_t gpio_sel );

/**
 * @brief iButton initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ibutton_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ibutton_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ibutton_init ( ibutton_t *ctx, ibutton_cfg_t *cfg );

/**
 * @brief iButton add key function.
 * @details This function reads the ROM address from a DS1990A Serial Number iButton and stores
 * it in the ctx->key_rom buffer.
 * @param[in] ctx : Click context object.
 * See #ibutton_t object definition for detailed explanation.
 * @return @li @c  0 - Success, the key is registered.
 *         @li @c -1 - Error, no communication with the key.
 *         @li @c -2 - The key is already registered.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ibutton_add_key ( ibutton_t *ctx );

/**
 * @brief iButton remove keys function.
 * @details This function removes all stored keys by clearing the ctx->key_rom buffer.
 * @param[in] ctx : Click context object.
 * See #ibutton_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ibutton_remove_keys ( ibutton_t *ctx );

/**
 * @brief iButton check key function.
 * @details This function reads the ROM address from a DS1990A Serial Number iButton and checks
 * if it is already stored in the ctx->key_rom buffer.
 * @param[in] ctx : Click context object.
 * See #ibutton_t object definition for detailed explanation.
 * @return @li @c  0 - Success, the key is found in the buffer.
 *         @li @c -1 - Error, no communication with the key.
 *         @li @c -3 - No match, the key is NOT found in the buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ibutton_check_key ( ibutton_t *ctx );

/**
 * @brief iButton enable red led function.
 * @details This function enables the red LED indication by setting the ST2 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ibutton_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ibutton_enable_red_led ( ibutton_t *ctx );

/**
 * @brief iButton disable red led function.
 * @details This function disables the red LED indication by setting the ST2 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ibutton_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ibutton_disable_red_led ( ibutton_t *ctx );

/**
 * @brief iButton enable green led function.
 * @details This function enables the green LED indication by setting the ST1 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ibutton_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ibutton_enable_green_led ( ibutton_t *ctx );

/**
 * @brief iButton disable green led function.
 * @details This function disables the green LED indication by setting the ST1 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ibutton_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ibutton_disable_green_led ( ibutton_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // IBUTTON_H

/*! @} */ // ibutton

// ------------------------------------------------------------------------ END
