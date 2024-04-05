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
 * @file thumbwheel.h
 * @brief This file contains API for Thumbwheel Click Driver.
 */

#ifndef THUMBWHEEL_H
#define THUMBWHEEL_H

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
 * @addtogroup thumbwheel Thumbwheel Click Driver
 * @brief API for configuring and manipulating Thumbwheel Click driver.
 * @{
 */

/**
 * @defgroup thumbwheel_cmd Thumbwheel Commands List
 * @brief List of commands of Thumbwheel Click driver.
 */

/**
 * @addtogroup thumbwheel_cmd
 * @{
 */

/**
 * @brief Thumbwheel commands list.
 * @details Specified commands list of Thumbwheel Click driver.
 */
#define THUMBWHEEL_CMD_CHANNEL_ACCESS_READ         0xF5
#define THUMBWHEEL_CMD_RESET_ACTIVITY_LATCHES      0xC3
#define THUMBWHEEL_CMD_WRITE_COND_SEARCH_REG       0xCC
#define THUMBWHEEL_CMD_READ_PIO_REG                0xF0

/*! @} */ // thumbwheel_cmd

/**
 * @defgroup thumbwheel_set Thumbwheel Settings
 * @brief Settings of Thumbwheel Click driver.
 */

/**
 * @addtogroup thumbwheel_reg
 * @{
 */

/**
 * @brief Thumbwheel register addresses.
 * @details Specified register addresses of Thumbwheel Click driver.
 */
#define THUMBWHEEL_REG_CONTROL_STATUS              0x008D
#define THUMBWHEEL_REG_COND_SEARCH_SELECTION       0x008B  
#define THUMBWHEEL_REG_PIO_LOGIC                   0x0088

/*! @} */ // thumbwheel_reg

/**
 * @addtogroup thumbwheel_set
 * @{
 */

/**
 * @brief Thumbwheel family code value and config. 
 * @details Specified family code value and config of Thumbwheel Click driver.
 */
#define THUMBWHEEL_FAMILY_CODE                     0x29
#define THUMBWHEEL_CONFIG_RESERVED_BITS            0x70

/*! @} */ // thumbwheel_set

/**
 * @defgroup thumbwheel_map Thumbwheel MikroBUS Map
 * @brief MikroBUS pin mapping of Thumbwheel Click driver.
 */

/**
 * @addtogroup thumbwheel_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thumbwheel Click to the selected MikroBUS.
 */
#define THUMBWHEEL_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // thumbwheel_map
/*! @} */ // thumbwheel

/**
 * @brief Thumbwheel Click gpio selector.
 * @details Selects gpio pin of Thumbwheel Click driver.
 */
typedef enum
{
    THUMBWHEEL_GPIO_0,                  /**< GPIO 0 pin. */
    THUMBWHEEL_GPIO_1                   /**< GPIO 1 pin. */

} thumbwheel_gpio_sel_t;

/**
 * @brief Thumbwheel Click context object.
 * @details Context object definition of Thumbwheel Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                  /**< Reset pin. */

    // Modules
    one_wire_t ow;                      /**< One Wire driver object. */

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */

} thumbwheel_t;

/**
 * @brief Thumbwheel Click configuration object.
 * @details Configuration object definition of Thumbwheel Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t gp0;                     /**< GPIO 0 pin. */
    pin_name_t gp1;                     /**< GPIO 1 pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Reset pin. */

    thumbwheel_gpio_sel_t gpio_sel;     /**< GPIO selection. */

} thumbwheel_cfg_t;

/**
 * @brief Thumbwheel Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THUMBWHEEL_OK = 0,
    THUMBWHEEL_ERROR = -1

} thumbwheel_return_value_t;

/*!
 * @addtogroup thumbwheel Thumbwheel Click Driver
 * @brief API for configuring and manipulating Thumbwheel Click driver.
 * @{
 */

/**
 * @brief Thumbwheel configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thumbwheel_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thumbwheel_cfg_setup ( thumbwheel_cfg_t *cfg );

/**
 * @brief Thumbwheel driver interface setup function.
 * @details This function sets a communication GPIO pin which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #thumbwheel_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO pin selection.
 * See #thumbwheel_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This gpio selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void thumbwheel_gpio_selection ( thumbwheel_cfg_t *cfg, thumbwheel_gpio_sel_t gpio_sel );

/**
 * @brief Thumbwheel initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thumbwheel_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thumbwheel_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thumbwheel_init ( thumbwheel_t *ctx, thumbwheel_cfg_t *cfg );

/**
 * @brief Thumbwheel check communication function.
 * @details This function checks the communication by reading the ROM address twice and comparing
 * the two results, as well as verifying the family code byte.
 * @param[in] ctx : Click context object.
 * See #thumbwheel_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thumbwheel_check_communication ( thumbwheel_t *ctx );

/**
 * @brief Thumbwheel write register function.
 * @details This function writes data into the register. 
 * @param[in] ctx : Click context object.
 * See #thumbwheel_t object definition for detailed explanation.
 * @param[in] reg : Register to write data in.  
 * @param[in] data_in : Data to be written. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thumbwheel_write_register ( thumbwheel_t *ctx, uint16_t reg, uint8_t data_in ); 

/**
 * @brief Thumbwheel read register function.
 * @details This function reads data from the register. 
 * @param[in] ctx : Click context object.
 * See #thumbwheel_t object definition for detailed explanation.
 * @param[in] reg : Register to read data from.  
 * @param[out] data_out : Pointing to the address where to store data. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thumbwheel_read_register ( thumbwheel_t *ctx, uint16_t reg, uint8_t *data_out );

/**
 * @brief Thumbwheel reset latches function.
 * @details This function resets activity latches. 
 * @param[in] ctx : Click context object.
 * See #thumbwheel_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thumbwheel_reset_latches ( thumbwheel_t *ctx ); 

/**
 * @brief Thumbwheel get position function.
 * @details This function gets the position of the rotary sprocket. 
 * @param[in] ctx : Click context object.
 * See #thumbwheel_t object definition for detailed explanation.
 * @param[out] position : Pointing to the address where to store the position value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thumbwheel_get_position ( thumbwheel_t *ctx, uint8_t *position ); 

/**
 * @brief Thumbwheel set reset pin function. 
 * @details This function sets the state of the reset pin. 
 * @param[in] ctx : Click context object.
 * See #thumbwheel_t object definition for detailed explanation.
 * @param[in] state : State of the reset pin to be set. 
 * @return None.
 * @note None.
 */
void thumbwheel_set_rst_pin ( thumbwheel_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // THUMBWHEEL_H

/*! @} */ // thumbwheel

// ------------------------------------------------------------------------ END
