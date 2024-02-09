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
 * @file charger.h
 * @brief This file contains API for Charger Click Driver.
 */

#ifndef CHARGER_H
#define CHARGER_H

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
#include "drv_one_wire.h"

/*!
 * @addtogroup charger Charger Click Driver
 * @brief API for configuring and manipulating Charger Click driver.
 * @{
 */

/**
 * @defgroup charger_cmd Charger Commands List
 * @brief List of commands of Charger Click driver.
 */

/**
 * @addtogroup charger_cmd
 * @{
 */

/**
 * @brief Charger commands list.
 * @details Specified commands list of Charger Click driver.
 */
#define CHARGER_CMD_WRITE_SCRATCHPAD        0x4E
#define CHARGER_CMD_READ_SCRATCHPAD         0xBE
#define CHARGER_CMD_COPY_SCRATCHPAD         0x48
#define CHARGER_CMD_RECALL_MEMORY           0xB8
#define CHARGER_CMD_CONVERT_T               0x44
#define CHARGER_CMD_CONVERT_V               0xB4

/*! @} */ // charger_cmd

/**
 * @defgroup charger_set Charger Settings
 * @brief Settings of Charger Click driver.
 */

/**
 * @addtogroup charger_set
 * @{
 */

/**
 * @brief Charger memory page setting.
 * @details Specified memory page setting of Charger Click driver.
 */
#define CHARGER_PAGE_0                      0
#define CHARGER_PAGE_1                      1
#define CHARGER_PAGE_2                      2
#define CHARGER_PAGE_3                      3
#define CHARGER_PAGE_4                      4
#define CHARGER_PAGE_5                      5
#define CHARGER_PAGE_6                      6
#define CHARGER_PAGE_7                      7
#define CHARGER_PAGE_SIZE                   8

/**
 * @brief Charger Status/Config register setting.
 * @details Specified Status/Config register setting of Charger Click driver.
 */
#define CHARGER_CONFIG_IAD                  0x01
#define CHARGER_CONFIG_CA                   0x02
#define CHARGER_CONFIG_EE                   0x04
#define CHARGER_CONFIG_AD                   0x08
#define CHARGER_CONFIG_TB                   0x10
#define CHARGER_CONFIG_NVM                  0x20
#define CHARGER_CONFIG_ADB                  0x40

/**
 * @brief Charger measurement values.
 * @details Specified measurement values of Charger Click driver.
 */
#define CHARGER_TEMPERATURE_RES             0.03125f
#define CHARGER_VOLTAGE_RES                 0.01f
#define CHARGER_CURRENT_RES                 204.8f

/**
 * @brief Charger family code value.
 * @details Specified family code value of Charger Click driver.
 */
#define CHARGER_FAMILY_CODE                 0x26

/**
 * @brief Charger address selection macros.
 * @details Specified address selection macros of Charger Click driver.
 */
#define CHARGER_ADDRESS_0                   0x00
#define CHARGER_ADDRESS_ALL                 0xFF

/*! @} */ // charger_set

/**
 * @defgroup charger_map Charger MikroBUS Map
 * @brief MikroBUS pin mapping of Charger Click driver.
 */

/**
 * @addtogroup charger_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger Click to the selected MikroBUS.
 */
#define CHARGER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.ow1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ow2 = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // charger_map
/*! @} */ // charger

/**
 * @brief Charger Click gpio selector.
 * @details Selects gpio pin of Charger Click driver.
 */
typedef enum
{
    CHARGER_GPIO_OW1,                   /**< GPIO OW1 pin. */
    CHARGER_GPIO_OW2                    /**< GPIO OW2 pin. */

} charger_gpio_sel_t;

/**
 * @brief Charger Click context object.
 * @details Context object definition of Charger Click driver.
 */
typedef struct
{
    // Modules
    one_wire_t ow;                      /**< One Wire driver object. */

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t address;                    /**< Device address selection. */

} charger_t;

/**
 * @brief Charger Click configuration object.
 * @details Configuration object definition of Charger Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t ow1;                     /**< GPIO OW1 pin. */
    pin_name_t ow2;                     /**< GPIO OW2 pin. */

    charger_gpio_sel_t gpio_sel;        /**< GPIO selection. */

} charger_cfg_t;

/**
 * @brief Charger Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER_OK = 0,
    CHARGER_ERROR = -1

} charger_return_value_t;

/*!
 * @addtogroup charger Charger Click Driver
 * @brief API for configuring and manipulating Charger Click driver.
 * @{
 */

/**
 * @brief Charger configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger_cfg_setup ( charger_cfg_t *cfg );

/**
 * @brief Charger driver interface setup function.
 * @details This function sets a communication GPIO pin which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #charger_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO pin selection.
 * See #charger_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This gpio selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void charger_gpio_selection ( charger_cfg_t *cfg, charger_gpio_sel_t gpio_sel );

/**
 * @brief Charger initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_init ( charger_t *ctx, charger_cfg_t *cfg );

/**
 * @brief Charger default configuration function.
 * @details This function executes a default configuration of Charger
 * click board.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t charger_default_cfg ( charger_t *ctx );

/**
 * @brief Charger check communication function.
 * @details This function checks the communication by reading the ROM address 
 * as well as verifying family code and CRC 8.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_check_communication ( charger_t *ctx );

/**
 * @brief Charger select device function.
 * @details This function selects the device by performing a skip or match ROM commands depending
 * on the address value set in the @b ctx->address.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_select_device ( charger_t *ctx );

/**
 * @brief Charger read scratchpad function.
 * @details This function reads a desired number of scratchpad bytes using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @param[in] page : Page number 0-7.
 * @param[out] data_out : Output read scratchpad.
 * @param[in] len : Scratchpad length in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_read_scratchpad ( charger_t *ctx, uint8_t page, uint8_t *data_out, uint8_t len );

/**
 * @brief Charger write scratchpad function.
 * @details This function writes a desired number of scratchpad bytes using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @param[in] page : Page number 0-7.
 * @param[in] data_in : Scratchpad to be written.
 * @param[in] len : Scratchpad length in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_write_scratchpad ( charger_t *ctx, uint8_t page, uint8_t *data_in, uint8_t len );

/**
 * @brief Charger copy scratchpad function.
 * @details This function copies the scratchpad page into the EEPROM/SRAM memory page.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @param[in] page : Page number 0-7.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_copy_scratchpad ( charger_t *ctx, uint8_t page );

/**
 * @brief Charger recall scratchpad function.
 * @details This function recalls the stored values in EEPROM/SRAM memory page to the scratchpad page.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @param[in] page : Page number 0-7.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_recall_memory ( charger_t *ctx, uint8_t page );

/**
 * @brief Charger convert temperature function.
 * @details This function begins a temperature conversion.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_convert_temperature ( charger_t *ctx );

/**
 * @brief Charger convert voltage function.
 * @details This function initiates a voltage analog-to-digital conversion cycle.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_convert_voltage ( charger_t *ctx );

/**
 * @brief Charger read temperature function.
 * @details This function reads the chip internal temperature measurement in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @param[out] temperature : Temperature measurement output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_read_temperature ( charger_t *ctx, float *temperature );

/**
 * @brief Charger read battery VDD function.
 * @details This function reads the battery input voltage.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @param[out] voltage : Voltage measurement output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_read_batt_vdd ( charger_t *ctx, float *voltage );

/**
 * @brief Charger read system VDD function.
 * @details This function reads the mikroBUS system input voltage.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @param[out] voltage : Voltage measurement output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_read_system_vdd ( charger_t *ctx, float *voltage );

/**
 * @brief Charger read current function.
 * @details This function reads the battery charging current.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @param[out] current : Current measurement output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_read_current ( charger_t *ctx, float *current );

/**
 * @brief Charger calibrate current function.
 * @details This function calibrates the zero current charging output.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note No battery should be connected to the click board during this calibration.
 */
err_t charger_calibrate_current ( charger_t *ctx );

/**
 * @brief Charger write elapsed time function.
 * @details This function writes the elapsed time meter counter.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @param[in] seconds : 32-bit seconds counter value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_write_elapsed_time ( charger_t *ctx, uint32_t seconds );

/**
 * @brief Charger read elapsed time function.
 * @details This function reads the elapsed time meter counter.
 * @param[in] ctx : Click context object.
 * See #charger_t object definition for detailed explanation.
 * @param[out] seconds : 32-bit seconds counter value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger_read_elapsed_time ( charger_t *ctx, uint32_t *seconds );

#ifdef __cplusplus
}
#endif
#endif // CHARGER_H

/*! @} */ // charger

// ------------------------------------------------------------------------ END
