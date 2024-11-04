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
 * @file thermo2.h
 * @brief This file contains API for Thermo 2 Click Driver.
 */

#ifndef THERMO2_H
#define THERMO2_H

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
 * @addtogroup thermo2 Thermo 2 Click Driver
 * @brief API for configuring and manipulating Thermo 2 Click driver.
 * @{
 */

/**
 * @defgroup thermo2_cmd Thermo 2 Commands List
 * @brief List of commands of Thermo 2 Click driver.
 */

/**
 * @addtogroup thermo2_cmd
 * @{
 */

/**
 * @brief Thermo 2 commands list.
 * @details Specified commands list of Thermo 2 Click driver.
 */
#define THERMO2_CMD_CONVERT_TEMPERATURE     0x44
#define THERMO2_CMD_WRITE_SCRATCHPAD        0x4E
#define THERMO2_CMD_READ_SCRATCHPAD         0xBE
#define THERMO2_CMD_COPY_SCRATCHPAD         0x48
#define THERMO2_CMD_RECALL_SCRATCHPAD       0xB8
#define THERMO2_CMD_READ_POWER_SUPPLY       0xB4

/*! @} */ // thermo2_cmd

/**
 * @defgroup thermo2_set Thermo 2 Settings
 * @brief Settings of Thermo 2 Click driver.
 */

/**
 * @addtogroup thermo2_set
 * @{
 */

/**
 * @brief Thermo 2 config register settings.
 * @details Specified config register settings of Thermo 2 Click driver.
 */
#define THERMO2_CONFIG_ADDRESS_0            0x00
#define THERMO2_CONFIG_ADDRESS_1            0x01
#define THERMO2_CONFIG_ADDRESS_2            0x02
#define THERMO2_CONFIG_ADDRESS_3            0x03
#define THERMO2_CONFIG_ADDRESS_4            0x04
#define THERMO2_CONFIG_ADDRESS_5            0x05
#define THERMO2_CONFIG_ADDRESS_6            0x06
#define THERMO2_CONFIG_ADDRESS_7            0x07
#define THERMO2_CONFIG_ADDRESS_8            0x08
#define THERMO2_CONFIG_ADDRESS_9            0x09
#define THERMO2_CONFIG_ADDRESS_10           0x0A
#define THERMO2_CONFIG_ADDRESS_11           0x0B
#define THERMO2_CONFIG_ADDRESS_12           0x0C
#define THERMO2_CONFIG_ADDRESS_13           0x0D
#define THERMO2_CONFIG_ADDRESS_14           0x0E
#define THERMO2_CONFIG_ADDRESS_15           0x0F
#define THERMO2_CONFIG_ADDRESS_ALL          0x10
#define THERMO2_CONFIG_ADDRESS_BIT_MASK     0x1F
#define THERMO2_CONFIG_RESOLUTION_9BIT      0x00
#define THERMO2_CONFIG_RESOLUTION_10BIT     0x20
#define THERMO2_CONFIG_RESOLUTION_11BIT     0x40
#define THERMO2_CONFIG_RESOLUTION_12BIT     0x60
#define THERMO2_CONFIG_RESOLUTION_BIT_MASK  0x60
#define THERMO2_CONFIG_RESERVED_BITS        0x10

/**
 * @brief Thermo 2 temperature calculation values.
 * @details Specified temperature calculation values of Thermo 2 Click driver.
 */
#define THERMO2_DATA_RESOLUTION             0.0625

/**
 * @brief Thermo 2 family code value.
 * @details Specified family code value of Thermo 2 Click driver.
 */
#define THERMO2_FAMILY_CODE                 0x3B

/**
 * @brief Thermo 2 default config values.
 * @details Specified default config values of Thermo 2 Click driver.
 */
#define THERMO2_DEFAULT_ADDRESS             THERMO2_CONFIG_ADDRESS_ALL
#define THERMO2_DEFAULT_RESOLUTION          THERMO2_CONFIG_RESOLUTION_12BIT
#define THERMO2_DEFAULT_TEMP_HIGH_ALARM     0xFF
#define THERMO2_DEFAULT_TEMP_LOW_ALARM      0x00

/*! @} */ // thermo2_set

/**
 * @defgroup thermo2_map Thermo 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 2 Click driver.
 */

/**
 * @addtogroup thermo2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 2 Click to the selected MikroBUS.
 */
#define THERMO2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // thermo2_map
/*! @} */ // thermo2

/**
 * @brief Thermo 2 Click gpio selector.
 * @details Selects gpio pin of Thermo 2 Click driver.
 */
typedef enum
{
    THERMO2_GPIO_0,      /**< GPIO 0 pin. */
    THERMO2_GPIO_1       /**< GPIO 1 pin. */

} thermo2_gpio_sel_t;

/**
 * @brief Thermo 2 Click context object.
 * @details Context object definition of Thermo 2 Click driver.
 */
typedef struct
{
    // Modules
    one_wire_t ow;                      /**< One Wire driver object. */
    
    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t config;                     /**< Device configuration register setting. */
    
} thermo2_t;

/**
 * @brief Thermo 2 Click configuration object.
 * @details Configuration object definition of Thermo 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t gp0;                     /**< GPIO 0 pin. */
    pin_name_t gp1;                     /**< GPIO 1 pin. */
    
    thermo2_gpio_sel_t gpio_sel;        /**< GPIO selection. */

} thermo2_cfg_t;

/**
 * @brief Thermo 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO2_OK = 0,
    THERMO2_ERROR = -1

} thermo2_return_value_t;

/*!
 * @addtogroup thermo2 Thermo 2 Click Driver
 * @brief API for configuring and manipulating Thermo 2 Click driver.
 * @{
 */

/**
 * @brief Thermo 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo2_cfg_setup ( thermo2_cfg_t *cfg );

/**
 * @brief Thermo 2 driver interface setup function.
 * @details This function sets a communication GPIO pin which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #thermo2_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO pin selection.
 * See #thermo2_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This gpio selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void thermo2_gpio_selection ( thermo2_cfg_t *cfg, thermo2_gpio_sel_t gpio_sel );

/**
 * @brief Thermo 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermo2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo2_init ( thermo2_t *ctx, thermo2_cfg_t *cfg );

/**
 * @brief Thermo 2 default configuration function.
 * @details This function executes a default configuration of Thermo 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #thermo2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo2_default_cfg ( thermo2_t *ctx );

/**
 * @brief Thermo 2 check communication function.
 * @details This function checks the communication by reading the ROM address twice and comparing
 * the two results, as well as verifying the family code byte.
 * @param[in] ctx : Click context object.
 * See #thermo2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo2_check_communication ( thermo2_t *ctx );

/**
 * @brief Thermo 2 select device function.
 * @details This function selects the device by performing a skip or match ROM commands depending
 * on the address value set in the configuration byte.
 * @param[in] ctx : Click context object.
 * See #thermo2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo2_select_device ( thermo2_t *ctx );

/**
 * @brief Thermo 2 start measurement function.
 * @details This function starts the measurement by sending an appropriate command for that.
 * @param[in] ctx : Click context object.
 * See #thermo2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo2_start_measurement ( thermo2_t *ctx );

/**
 * @brief Thermo 2 read scratchpad function.
 * @details This function reads the scratchpad bytes.
 * @param[in] ctx : Click context object.
 * See #thermo2_t object definition for detailed explanation.
 * @param[out] scratchpad : Scratchpad [5-bytes] of device with the address set in @b ctx->config.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo2_read_scratchpad ( thermo2_t *ctx, uint8_t *scratchpad );

/**
 * @brief Thermo 2 write scratchpad function.
 * @details This function writes the temperature thresholds and configuration byte to the scratchpad.
 * @param[in] ctx : Click context object.
 * See #thermo2_t object definition for detailed explanation.
 * @param[in] temp_high : Temperature high limit.
 * @param[in] temp_low : Temperature low limit.
 * @param[in] config : Configuration byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo2_write_scratchpad ( thermo2_t *ctx, uint8_t temp_high, uint8_t temp_low, uint8_t config );

/**
 * @brief Thermo 2 read temperature function.
 * @details This function reads the temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo2_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo2_read_temperature ( thermo2_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // THERMO2_H

/*! @} */ // thermo2

// ------------------------------------------------------------------------ END
