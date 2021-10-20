/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file currentlimit.h
 * @brief This file contains API for Current Limit Click Driver.
 */

#ifndef CURRENTLIMIT_H
#define CURRENTLIMIT_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup currentlimit Current Limit Click Driver
 * @brief API for configuring and manipulating Current Limit Click driver.
 * @{
 */

/**
 * @defgroup currentlimit_set Current Limit Registers Settings
 * @brief Settings for registers of Current Limit Click driver.
 */

/**
 * @addtogroup currentlimit_set
 * @{
 */

/**
 * @brief Current Limit description setting.
 * @details Specified setting for description of Current Limit Click driver.
 */
#define CURRENTLIMIT_ENABLE             1
#define CURRENTLIMIT_DISABLE            0

#define CURRENTLIMIT_LSB_VAL            392.2
#define CURRENTLIMIT_R_BASE             1200.0
#define CURRENTLIMIT_I_MAX              1.2
#define CURRENTLIMIT_CALC_COEF          1380.0

#define CURRENTLIMIT_CUR_LIM_VAL_0_1    224
#define CURRENTLIMIT_CUR_LIM_VAL_0_2    241
#define CURRENTLIMIT_CUR_LIM_VAL_0_3    247
#define CURRENTLIMIT_CUR_LIM_VAL_0_4    250
#define CURRENTLIMIT_CUR_LIM_VAL_0_5    252
#define CURRENTLIMIT_CUR_LIM_VAL_0_6    253
#define CURRENTLIMIT_CUR_LIM_VAL_0_7    254
#define CURRENTLIMIT_CUR_LIM_VAL_0_867  255

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b currentlimit_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CURRENTLIMIT_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define CURRENTLIMIT_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // currentlimit_set

/**
 * @defgroup currentlimit_map Current Limit MikroBUS Map
 * @brief MikroBUS pin mapping of Current Limit Click driver.
 */

/**
 * @addtogroup currentlimit_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current Limit Click to the selected MikroBUS.
 */
#define CURRENTLIMIT_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_AN )

/*! @} */ // currentlimit_map
/*! @} */ // currentlimit

/**
 * @brief Current Limit Click context object.
 * @details Context object definition of Current Limit Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en;       /**< Switch Enable. */

    // Modules
    spi_master_t  spi;                               /**< SPI driver object. */

    pin_name_t  chip_select;                         /**< Chip select pin descriptor (used for SPI driver). */

} currentlimit_t;

/**
 * @brief Current Limit Click configuration object.
 * @details Configuration object definition of Current Limit Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t   en;         /**< Switch Enable. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} currentlimit_cfg_t;

/**
 * @brief Current Limit Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   CURRENTLIMIT_OK = 0,
   CURRENTLIMIT_ERROR = -1

} currentlimit_return_value_t;

/*!
 * @addtogroup currentlimit Current Limit Click Driver
 * @brief API for configuring and manipulating Current Limit Click driver.
 * @{
 */

/**
 * @brief Current Limit configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #currentlimit_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void currentlimit_cfg_setup ( currentlimit_cfg_t *cfg );

/**
 * @brief Current Limit initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #currentlimit_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #currentlimit_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t currentlimit_init ( currentlimit_t *ctx, currentlimit_cfg_t *cfg );

/**
 * @brief Current Limit data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #currentlimit_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t currentlimit_generic_write ( currentlimit_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Current Limit data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #currentlimit_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t currentlimit_generic_read ( currentlimit_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Device enable function.
 * @details Function is used to enable or disable the device.
 * @param[out] ctx : Click context object.
 * See #currentlimit_t object definition for detailed explanation.
 * @param[in] state  value that defines state of the device
 * @return Nothing.
**/
void currentlimit_dev_enable ( currentlimit_t *ctx, uint8_t state );

/**
 * @brief Set Current With Predefined Values Limit function.
 * @details Function is used to set the current limit with predefined values.
 * @param[in] ctx : Click context object.
 * See #currentlimit_t object definition for detailed explanation.
 * @param[in] lim_val  8-bit value that defines current limit
 * @return Nothing.
 * 
 * @note Input value should not exceed 0.867.
 * @note For best performance, set the current limit (ILIMIT)
 * between 0.2 IMAX <= ILIMIT <= IMAX.
**/
void currentlimit_set_limit ( currentlimit_t *ctx, uint8_t lim_val );

/**
 * @brief Set Calculated Current Limit function.
 * @details Function is used to set the current limit with calculacion.
 * @param[in] ctx : Click context object.
 * See #currentlimit_t object definition for detailed explanation.
 * @param[in] lim_val  float value that defines current limit
 * @return Nothing.
 * 
 * @note Input value should not exceed 0.867.
 * @note For best performance, set the current limit (ILIMIT)
 * between 0.2 IMAX <= ILIMIT <= IMAX.
**/
void currentlimit_set_limit_calc ( currentlimit_t *ctx, float lim_val );

#ifdef __cplusplus
}
#endif
#endif // CURRENTLIMIT_H

/*! @} */ // currentlimit

// ------------------------------------------------------------------------ END
