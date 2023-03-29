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
 * @file uniqueid.h
 * @brief API for UNIQUE ID Click driver.
 */

#ifndef UNIQUEID_H
#define UNIQUEID_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_one_wire.h"

/*!
 * @addtogroup uniqueid UNIQUE ID click criver
 * @brief API for configuring and manipulating UNIQUEID click driver.
 * @{
 */

/**
 * @defgroup uniqueid_set UNIQUE ID Settings
 * @brief Settings of UNIQUE ID click driver.
 */

/**
 * @addtogroup uniqueid_set
 * @{
 */

/**
 * @brief UNIQUE ID Family Code value.
 * @details Specified Family Code value of UNIQUE ID click driver.
 */
#define UNIQUEID_FAMILY_CODE               0x01

/*! @} */ // uniqueid_set

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UNIQUE ID click to the selected MikroBUS.
 */

/**
 * @addtogroup uniqueid_map
 * @{
 */
#define UNIQUEID_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_AN ); 
   
/*! @} */ // uniqueid_map

/**
 * @brief UNIQUE ID click GPIO selector.
 * @details Selecting GPIO pins of UNIQUE ID click driver.
 */
typedef enum
{
    UNIQUEID_GPIO_0,      /**< GPIO_0 pin. */
    UNIQUEID_GPIO_1       /**< GPIO_1 pin. */

} uniqueid_gpio_sel_t;

/**
 * @brief UNIQUE ID click context object.
 * @details Context object definition of UNIQUE ID click driver.
 */
typedef struct
{
    // Modules
    one_wire_t ow;                      /**< One Wire driver object. */

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t address;                    /**< Device address selection. */

} uniqueid_t;

/**
 * @brief UNIQUE ID click configuration object.
 * @details Configuration object definition of UNIQUE ID click driver.
 */
typedef struct
{
    // Communication GPIO pins
    pin_name_t gp0;                     /**< GPIO 0 pin. */
    pin_name_t gp1;                     /**< GPIO 1 pin. */

    uniqueid_gpio_sel_t gpio_sel;       /**< GPIO selector. */

} uniqueid_cfg_t;

/**
 * @brief UNIQUE ID click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UNIQUEID_OK = 0,
    UNIQUEID_ERROR = -1

} uniqueid_return_value_t;

/*! @} */ // uniqueid

/*!
 * @addtogroup uniqueid UNIQUE ID click Driver
 * @brief API for configuring and manipulating UNIQUE ID click driver.
 * @{
 */

/**
 * @brief UNIQUE ID configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uniqueid_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uniqueid_cfg_setup ( uniqueid_cfg_t *cfg );

/**
 * @brief UNIQUE ID driver interface setup function.
 * @details This function sets a communication GPIO pins which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #uniqueid_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO selector.
 * See #uniqueid_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function should be called before init function in order to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void uniqueid_gpio_selection ( uniqueid_cfg_t *cfg, uniqueid_gpio_sel_t gpio_sel );

/**
 * @brief UNIQUE ID initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #uniqueid_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uniqueid_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uniqueid_init ( uniqueid_t *ctx, uniqueid_cfg_t *cfg );

/**
 * @brief UNIQUE ID read Family Code and Serial Number function.
 * @details This function reads Family Code and Serial Number of device's ROM memory. 
 * @param[in] ctx : Click context object.
 * See #uniqueid_t object definition for detailed explanation.
 * @param[out] family : Address pointing where to store Family Code information.
 * @param[out] serial_num : Address pointing where to store Serial Number information.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uniqueid_read_id ( uniqueid_t *ctx, uint8_t *family, uint8_t *serial_num ); 

#ifdef __cplusplus
}
#endif
#endif // UNIQUEID_H

/*! @} */ // uniqueid

// ------------------------------------------------------------------------ END
