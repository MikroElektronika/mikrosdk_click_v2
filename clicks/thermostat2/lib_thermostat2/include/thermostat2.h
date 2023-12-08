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
 * @file thermostat2.h
 * @brief This file contains API for Thermostat 2 Click Driver.
 */

#ifndef THERMOSTAT2_H
#define THERMOSTAT2_H

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
 * @addtogroup thermostat2 Thermostat 2 Click Driver
 * @brief API for configuring and manipulating Thermostat 2 Click driver.
 * @{
 */

/**
 * @defgroup thermostat2_cmd Thermostat 2 Commands List
 * @brief List of commands of Thermostat 2 Click driver.
 */

/**
 * @addtogroup thermostat2_cmd
 * @{
 */

/**
 * @brief Thermostat 2 commands list.
 * @details Specified commands list of Thermostat 2 Click driver.
 */
#define THERMOSTAT2_CMD_WRITE_SCRATCHPAD          0x4E
#define THERMOSTAT2_CMD_READ_SCRATCHPAD           0xBE
#define THERMOSTAT2_CMD_COPY_SCRATCHPAD           0x48
#define THERMOSTAT2_CMD_CONVERT_TEMPERATURE       0x44
#define THERMOSTAT2_CMD_RECALL_SCRATCHPAD         0xB8
#define THERMOSTAT2_CMD_READ_POWER_SUPPLY         0xB4

/*! @} */ // thermostat2_cmd

/**
 * @defgroup thermostat2_set Thermostat 2 Settings
 * @brief Settings of Thermostat 2 Click driver.
 */

/**
 * @addtogroup thermostat2_set
 * @{
 */

/**
 * @brief Thermostat 2 default config values.
 * @details Specified default config values of Thermostat 2 Click driver.
 */
#define THERMOSTAT2_CONFIG_RESOLUTION_9BIT        0x00
#define THERMOSTAT2_CONFIG_RESOLUTION_10BIT       0x20
#define THERMOSTAT2_CONFIG_RESOLUTION_11BIT       0x40
#define THERMOSTAT2_CONFIG_RESOLUTION_12BIT       0x60
#define THERMOSTAT2_CONFIG_RESOLUTION_BIT_MASK    0x60
#define THERMOSTAT2_CONFIG_RESERVED_BITS          0x1F

/**
 * @brief Thermostat 2 family code value.
 * @details Specified family code value of Thermostat 2 Click driver.
 */
#define THERMOSTAT2_FAMILY_CODE                   0x10

/**
 * @brief Thermostat 2 temperature calculation values.
 * @details Specified temperature calculation values of Thermostat 2 Click driver.
 */
#define THERMOSTAT2_RESOLUTION_9BIT               0.5
#define THERMOSTAT2_RESOLUTION_10BIT              0.25
#define THERMOSTAT2_RESOLUTION_11BIT              0.125
#define THERMOSTAT2_RESOLUTION_12BIT              0.0625

/**
 * @brief Thermostat 2 default config values.
 * @details Specified default config values of Thermostat 2 Click driver.
 */
#define THERMOSTAT2_DEFAULT_RESOLUTION            THERMOSTAT2_CONFIG_RESOLUTION_9BIT
#define THERMOSTAT2_DEFAULT_TEMP_HIGH_ALARM       0xFF
#define THERMOSTAT2_DEFAULT_TEMP_LOW_ALARM        0x00

/**
 * @brief Thermostat 2 temperature values and relay states.
 * @details Specified temperature values and relay states of Thermostat 2 Click driver.
 */
#define THERMOSTAT2_RELAY_ON                      0x01
#define THERMOSTAT2_RELAY_OFF                     0x00
#define THERMOSTAT2_TEMPERATURE_LIMIT             28.0

/*! @} */ // thermostat2_set

/**
 * @defgroup thermostat2_map Thermostat 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermostat 2 Click driver.
 */

/**
 * @addtogroup thermostat2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermostat 2 Click to the selected MikroBUS.
 */
#define THERMOSTAT2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); 

/*! @} */ // thermostat2_map
/*! @} */ // thermostat2

/**
 * @brief Thermostat 2 Click context object.
 * @details Context object definition of Thermostat 2 Click driver.
 */
typedef struct
{
    digital_out_t cs;                   /**< Relay control pin. */

    // Modules
    one_wire_t ow;                      /**< One Wire driver object. */

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t config;                     /**< Device configuration register setting. */

} thermostat2_t;

/**
 * @brief Thermostat 2 Click configuration object.
 * @details Configuration object definition of Thermostat 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t gp0;                     /**< GPIO 0 pin. */
    pin_name_t cs;                      /**< Relay control pin. */

} thermostat2_cfg_t;

/**
 * @brief Thermostat 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMOSTAT2_OK = 0,
    THERMOSTAT2_ERROR = -1

} thermostat2_return_value_t;

/*!
 * @addtogroup thermostat2 Thermostat 2 Click Driver
 * @brief API for configuring and manipulating Thermostat 2 Click driver.
 * @{
 */

/**
 * @brief Thermostat 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermostat2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermostat2_cfg_setup ( thermostat2_cfg_t *cfg );

/**
 * @brief Thermostat 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermostat2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermostat2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat2_init ( thermostat2_t *ctx, thermostat2_cfg_t *cfg );

/**
 * @brief Thermostat 2 default configuration function.
 * @details This function executes a default configuration of Thermostat 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #thermostat2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermostat2_default_cfg ( thermostat2_t *ctx );

/**
 * @brief Thermostat 2 check communication function.
 * @details This function checks the communication by reading the ROM address twice and comparing
 * the two results, as well as verifying the family code byte.
 * @param[in] ctx : Click context object.
 * See #thermostat2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat2_check_communication ( thermostat2_t *ctx );

/**
 * @brief Thermostat 2 read scratchpad function.
 * @details This function reads a desired number of scratchpad bytes using One Wire communication protocol.
 * @param[in] ctx : Click context object.
 * See #thermostat2_t object definition for detailed explanation.
 * @param[out] scratchpad : Output read scratchpad.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat2_read_scratchpad ( thermostat2_t *ctx, uint8_t *scratchpad ); 

/**
 * @brief Thermostat 2 write scratchpad function.
 * @details This function writes the temperature thresholds and configuration byte to the scratchpad.
 * @param[in] ctx : Click context object.
 * See #thermostat2_t object definition for detailed explanation.
 * @param[in] temp_high : Temperature high limit.
 * @param[in] temp_low : Temperature low limit.
 * @param[in] config : Configuration byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat2_write_scratchpad ( thermostat2_t *ctx, uint8_t temp_high, uint8_t temp_low, uint8_t config ); 

/**
 * @brief Thermostat 2 start measurement function.
 * @details This function starts the measurement by sending an appropriate command for that.
 * @param[in] ctx : Click context object.
 * See #thermostat2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat2_start_measurement ( thermostat2_t *ctx ); 

/**
 * @brief Thermostat 2 relay state function. 
 * @details This function turns the relay on/off. 
 * @param[in] ctx : Click context object.
 * See #thermostat2_t object definition for detailed explanation.
 * @param[in] state : On/off state of the relay. 
 * @return Nothing.  
 * @note None.
 */
void thermostat2_relay_state ( thermostat2_t *ctx, uint8_t state );

/**
 * @brief Thermostat 2 read temperature function.
 * @details This function reads the temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #thermostat2_t object definition for detailed explanation.
 * @param[out] temperature : Pointing to the address where to store temperature. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermostat2_read_temperature ( thermostat2_t *ctx, float *temperature ); 

#ifdef __cplusplus
}
#endif
#endif // THERMOSTAT2_H

/*! @} */ // thermostat2

// ------------------------------------------------------------------------ END
