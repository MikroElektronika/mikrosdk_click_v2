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
 * @file currentlimit6.h
 * @brief This file contains API for Current Limit 6 Click Driver.
 */

#ifndef CURRENTLIMIT6_H
#define CURRENTLIMIT6_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup currentlimit6 Current Limit 6 Click Driver
 * @brief API for configuring and manipulating Current Limit 6 Click driver.
 * @{
 */

/**
 * @defgroup currentlimit6_set Current Limit 6 Registers Settings
 * @brief Settings for registers of Current Limit 6 Click driver.
 */

/**
 * @addtogroup currentlimit6_set
 * @{
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b currentlimit6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CURRENTLIMIT6_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define CURRENTLIMIT6_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // currentlimit6_set

/**
 * @defgroup currentlimit6_map Current Limit 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Current Limit 6 Click driver.
 */

/**
 * @addtogroup currentlimit6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current Limit 6 Click to the selected MikroBUS.
 */
#define CURRENTLIMIT6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.er2 = MIKROBUS( mikrobus, MIKROBUS_AN );    \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.er1 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // currentlimit6_map
/*! @} */ // currentlimit6

/**
 * @brief Current Limit 6 Click context object.
 * @details Context object definition of Current Limit 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en;          /**< Enable pin. */

    // Input pins
    digital_in_t  er2;          /**< UVOV Fault Indicator pin. */
    digital_in_t  er1;          /**< FLAG Fault Indicator pin. */

    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} currentlimit6_t;

/**
 * @brief Current Limit 6 Click configuration object.
 * @details Configuration object definition of Current Limit 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  er2;     /**< UVOV Fault Indicator pin. */
    pin_name_t  en;      /**< Enable pin. */
    pin_name_t  er1;     /**< FLAG Fault Indicator pin. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} currentlimit6_cfg_t;

/**
 * @brief Current Limit 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENTLIMIT6_OK = 0,
    CURRENTLIMIT6_ERROR = -1

} currentlimit6_return_value_t;

/**
 * @brief Current Limit 6 Click power mode data.
 * @details Predefined enum values for driver power mode values.
 */
typedef enum
{
    CURRENTLIMIT6_PWR_OFF = 0,
    CURRENTLIMIT6_PWR_ON  = 1

} currentlimit6_pwr_mode_value_t;

/*!
 * @addtogroup currentlimit6 Current Limit 6 Click Driver
 * @brief API for configuring and manipulating Current Limit 6 Click driver.
 * @{
 */

/**
 * @brief Current Limit 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #currentlimit6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void currentlimit6_cfg_setup ( currentlimit6_cfg_t *cfg );

/**
 * @brief Current Limit 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #currentlimit6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #currentlimit6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit6_init ( currentlimit6_t *ctx, currentlimit6_cfg_t *cfg );

/**
 * @brief Current Limit 6 default configuration function.
 * @details This function executes a default configuration of Current Limit 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t currentlimit6_default_cfg ( currentlimit6_t *ctx );

/**
 * @brief Current Limit 6 power mode function.
 * @details This function executes the desired power mode of the
 * MAX17608 4.5V to 60V, 1A Current Limiter with OV, UV, and Reverse Protection
 * on the Current Limit 6 click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit6_t object definition for detailed explanation.
 * @param[in] pwr_mode :
 *         @li @c  0 ( CURRENTLIMIT6_PWR_OFF ) - Power off,
 *         @li @c  1 ( CURRENTLIMIT6_PWR_ON )  - Power on.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit6_power_mode ( currentlimit6_t *ctx, currentlimit6_pwr_mode_value_t pwr_mode );

/**
 * @brief Current Limit 6 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #currentlimit6_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit6_generic_write ( currentlimit6_t *ctx, uint8_t data_in );

/**
 * @brief Current Limit 6 set current limit function.
 * @details This function set current limit ( A ) of the
 * MAX17608 4.5V to 60V, 1A Current Limiter with OV, UV, and Reverse Protection
 * on the Current Limit 6 click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit6_t object definition for detailed explanation.
 * @param[in] current_limit : Desired current limit [ 0.100 A : 1.0 A ]
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit6_set_current_limit ( currentlimit6_t *ctx, float current_limit );

/**
 * @brief Current Limit 6 check limit exceeded function.
 * @details This function checks limit exceeded of the
 * MAX17608 4.5V to 60V, 1A Current Limiter with OV, UV, and Reverse Protection
 * on the Current Limit 6 click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit6_t object definition for detailed explanation.
 * @return @li @c  0 - Overcurrent duration exceeds the blanking time,
 * reverse current is detected, thermal shutdown is active or Rseti is less than 1kΩ,
 *         @li @c  1 - Normal.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t currentlimit6_check_limit_exceeded ( currentlimit6_t *ctx );

/**
 * @brief Current Limit 6 check voltage error function.
 * @details This function check the voltage error of the
 * MAX17608 4.5V to 60V, 1A Current Limiter with OV, UV, and Reverse Protection
 * on the Current Limit 6 click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit6_t object definition for detailed explanation.
 * @return @li @c  0 - Input voltage falls below UVLO threshold or 
 * input voltage rises above OVLO threshold,
 *         @li @c  1 - Input voltage is OK.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t currentlimit6_check_voltage_err ( currentlimit6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CURRENTLIMIT6_H

/*! @} */ // currentlimit6

// ------------------------------------------------------------------------ END
