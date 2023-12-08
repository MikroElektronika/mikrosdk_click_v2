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
 * @file thermostat4.c
 * @brief This file contains API for Thermostat 4 Click Driver.
 */

#ifndef THERMOSTAT4_H
#define THERMOSTAT4_H

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
#include "drv_spi_master.h"

/*!
 * @addtogroup thermostat4 Thermostat 4 Click Driver
 * @brief API for configuring and manipulating Thermostat 4 Click driver.
 * @{
 */

/**
 * @defgroup thermostat4_set Thermostat 4 Registers Settings
 * @brief Settings for registers of Thermostat 4 Click driver.
 */

/**
 * @addtogroup thermostat4_set
 * @{
 */

/**
 * @brief Thermostat 4 description setting.
 * @details Specified setting for description of Thermostat 4 Click driver.
 */
#define THERMOSTAT4_RELAY_ON                0x01
#define THERMOSTAT4_RELAY_OFF               0x00

#define THERMOSTAT4_RESET_ON                0x01
#define THERMOSTAT4_RESET_OFF               0x00

#define THERMOSTAT4_WARM_ALERT              0x00
#define THERMOSTAT4_HOT_ALERT               0x00

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b thermostat4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define THERMOSTAT4_SET_DATA_SAMPLE_EDGE    SET_SPI_DATA_SAMPLE_EDGE
#define THERMOSTAT4_SET_DATA_SAMPLE_MIDDLE  SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // thermostat4_set

/**
 * @defgroup thermostat4_map Thermostat 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermostat 4 Click driver.
 */

/**
 * @addtogroup thermostat4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermostat 4 Click to the selected MikroBUS.
 */
#define THERMOSTAT4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.oa  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.rly = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.ob  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thermostat4_map
/*! @} */ // thermostat4

/**
 * @brief Thermostat 4 Click context object.
 * @details Context object definition of Thermostat 4 Click driver.
 */
typedef struct
{
    // Output pins
   digital_out_t rst;       /**< Reset. */
   digital_out_t rly;       /**< Relay Control. */
   digital_out_t cs;        /**< SPI Chip Select. */

    // Input pins
   digital_in_t oa;         /**< Channel A Output. */
   digital_in_t ob;         /**< Channel B Output. */

    // Modules
    spi_master_t  spi;      /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} thermostat4_t;

/**
 * @brief Thermostat 4 Click configuration object.
 * @details Configuration object definition of Thermostat 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;         /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;         /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;          /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;           /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t   oa;          /**< Channel A Output. */
    pin_name_t   rst;         /**< Reset. */
    pin_name_t rly;           /**< Relay Control. */
    pin_name_t ob;            /**< Channel B Output. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} thermostat4_cfg_t;

/**
 * @brief Thermostat 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMOSTAT4_OK = 0,
    THERMOSTAT4_ERROR = -1

} thermostat4_return_value_t;

/*!
 * @addtogroup thermostat4 Thermostat 4 Click Driver
 * @brief API for configuring and manipulating Thermostat 4 Click driver.
 * @{
 */

/**
 * @brief Thermostat 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermostat4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermostat4_cfg_setup ( thermostat4_cfg_t *cfg );

/**
 * @brief Thermostat 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermostat4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermostat4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t thermostat4_init ( thermostat4_t *ctx, thermostat4_cfg_t *cfg );

/**
 * @brief Relay Control.
 * @details This function write desired state on RLY pin.
 * @param[in] ctx : Click context object.
 * See #thermostat4_t object definition for detailed explanation. 
 * @param[in] state : Relay ( ON or OFF state ).
 * @return Nothing.
 */
void thermostat4_relay_ctrl ( thermostat4_t *ctx, uint8_t state );

/**
 * @brief Sets reset pin state.
 * @details This function write desired state om RST pin.
 * @param[in] ctx : Click context object.
 * See #thermostat4_t object definition for detailed explanation.
 * @param state   Reset ( 1 - ON or 0 - OFF state ).
 * @return Nothing.
 */
void thermostat4_rst_pin_ctrl ( thermostat4_t *ctx, uint8_t state );

/**
 * @brief Hot temperature alert.
 * @details This function read state from OA pin.
 * @param[in] ctx : Click context object.
 * See #thermostat4_t object definition for detailed explanation. 
 * @returns Alert( 0 - ON or 1 - OFF state ).
 */
uint8_t thermostat4_hot_alert_state ( thermostat4_t *ctx );

/**
 * @brief Warm temperature alert.
 * @details This function read state from OB pin.
 * @param[in] ctx : Click context object.
 * See #thermostat4_t object definition for detailed explanation.  
 * @returns Alert( 0 - ON or 1 - OFF state ).
 */
uint8_t thermostat4_warm_alert_state ( thermostat4_t *ctx );

/**
 * @brief Hysteresis on the Warm channel.
 * @details This function write hysteresis data.
 * @param[in] ctx : Click context object.
 * See #thermostat4_t object definition for detailed explanation. 
 * @param[in] hyst_data : Potentiometer data 0 - 255.
 * @return Nothing.
 */
void thermostat4_set_warm_hysteresis ( thermostat4_t *ctx, uint8_t hyst_data );

/**
 * @brief Reset module and upload new configuration on the Warm channel.
 * @details This function reset module and upload new configuration on the Warm channel.
 * @param[in] ctx : Click context object.
 * See #thermostat4_t object definition for detailed explanation. 
 * @return Nothing.
 */
void thermostat4_new_cfg_upload ( thermostat4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _THERMOSTAT4_H_

/*! @} */ // thermostat 4
// ------------------------------------------------------------------------- END
