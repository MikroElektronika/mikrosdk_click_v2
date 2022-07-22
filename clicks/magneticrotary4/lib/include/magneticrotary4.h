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
 * @file magneticrotary4.h
 * @brief This file contains API for Magnetic Rotary 4 Click Driver.
 */

#ifndef MAGNETICROTARY4_H
#define MAGNETICROTARY4_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup magneticrotary4 Magnetic Rotary 4 Click Driver
 * @brief API for configuring and manipulating Magnetic Rotary 4 Click driver.
 * @{
 */

/**
 * @defgroup magneticrotary4_reg Magnetic Rotary 4 Registers List
 * @brief List of registers of Magnetic Rotary 4 Click driver.
 */

/**
 * @addtogroup magneticrotary4_reg
 * @{
 */

/**
 * @brief Magnetic Rotary 4 volatile registers list.
 * @details Specified list of volatile registers of Magnetic Rotary 4 Click driver.
 */
#define MAGNETICROTARY4_REG_NOP                 0x0000
#define MAGNETICROTARY4_REG_ERRFL               0x0001
#define MAGNETICROTARY4_REG_PROG                0x0003
#define MAGNETICROTARY4_REG_DIAAGC              0x3FFC
#define MAGNETICROTARY4_REG_MAG                 0x3FFD
#define MAGNETICROTARY4_REG_ANGLEUNC            0x3FFE
#define MAGNETICROTARY4_REG_ANGLECOM            0x3FFF

/**
 * @brief Magnetic Rotary 4 non-volatile registers list.
 * @details Specified list of non-volatile registers of Magnetic Rotary 4 Click driver.
 */
#define MAGNETICROTARY4_REG_ZPOSM               0x0016
#define MAGNETICROTARY4_REG_ZPOSL               0x0017
#define MAGNETICROTARY4_REG_SETTINGS1           0x0018
#define MAGNETICROTARY4_REG_SETTINGS2           0x0019

/*! @} */ // magneticrotary4_reg

/**
 * @defgroup magneticrotary4_set Magnetic Rotary 4 Registers Settings
 * @brief Settings for registers of Magnetic Rotary 4 Click driver.
 */

/**
 * @addtogroup magneticrotary4_set
 * @{
 */

/**
 * @brief Magnetic Rotary 4 angle calculation values.
 * @details Specified angle calculation values of Magnetic Rotary 4 Click driver.
 */
#define MAGNETICROTARY4_DATA_RESOLUTION         0x3FFF
#define MAGNETICROTARY4_FULL_CIRCLE             360

/**
 * @brief Magnetic Rotary 4 ODD parity flag.
 * @details Specified flag for ODD parity of Magnetic Rotary 4 Click driver.
 */
#define MAGNETICROTARY4_ODD_PARITY              0x01

/**
 * @brief Magnetic Rotary 4 rotation direction values.
 * @details Specified rotation direction values of Magnetic Rotary 4 Click driver.
 */
#define MAGNETICROTARY4_DIRECTION_CW            0
#define MAGNETICROTARY4_DIRECTION_CCW           1

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b magneticrotary4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MAGNETICROTARY4_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define MAGNETICROTARY4_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // magneticrotary4_set

/**
 * @defgroup magneticrotary4_map Magnetic Rotary 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Magnetic Rotary 4 Click driver.
 */

/**
 * @addtogroup magneticrotary4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magnetic Rotary 4 Click to the selected MikroBUS.
 */
#define MAGNETICROTARY4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // magneticrotary4_map
/*! @} */ // magneticrotary4

/**
 * @brief Magnetic Rotary 4 Click context object.
 * @details Context object definition of Magnetic Rotary 4 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} magneticrotary4_t;

/**
 * @brief Magnetic Rotary 4 Click configuration object.
 * @details Configuration object definition of Magnetic Rotary 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;           /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;           /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;            /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;             /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} magneticrotary4_cfg_t;

/**
 * @brief Magnetic Rotary 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETICROTARY4_OK = 0,
    MAGNETICROTARY4_ERROR = -1

} magneticrotary4_return_value_t;

/*!
 * @addtogroup magneticrotary4 Magnetic Rotary 4 Click Driver
 * @brief API for configuring and manipulating Magnetic Rotary 4 Click driver.
 * @{
 */

/**
 * @brief Magnetic Rotary 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneticrotary4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneticrotary4_cfg_setup ( magneticrotary4_cfg_t *cfg );

/**
 * @brief Magnetic Rotary 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #magneticrotary4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneticrotary4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary4_init ( magneticrotary4_t *ctx, magneticrotary4_cfg_t *cfg );

/**
 * @brief Magnetic Rotary 4 write register function.
 * @details This function writes a desired data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #magneticrotary4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary4_write_register ( magneticrotary4_t *ctx, uint16_t reg, uint16_t data_in );

/**
 * @brief Magnetic Rotary 4 read register function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #magneticrotary4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary4_read_register ( magneticrotary4_t *ctx, uint16_t reg, uint16_t *data_out );

/**
 * @brief Magnetic Rotary 4 get angle function.
 * @details This function reads the absolute position raw data and converts it to degrees (Angle).
 * @param[in] ctx : Click context object.
 * See #magneticrotary4_t object definition for detailed explanation.
 * @param[out] angle : Angle in degrees [0-360].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary4_get_angle ( magneticrotary4_t *ctx, float *angle );

/**
 * @brief Magnetic Rotary 4 calibrate zero position function.
 * @details This function calibrates the sensor to zero Angle position.
 * @param[in] ctx : Click context object.
 * See #magneticrotary4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function will clear the comp_l_error_en and comp_h_error_en bits from ZPOSL register.
 */
err_t magneticrotary4_calibrate_zero_position ( magneticrotary4_t *ctx );

/**
 * @brief Magnetic Rotary 4 set rotation direction function.
 * @details This function sets the magnet rotation direction to clockwise or counter-clockwise.
 * @param[in] ctx : Click context object.
 * See #magneticrotary4_t object definition for detailed explanation.
 * @param[in] direction : @li @c 0 - Clockwise,
 *                        @li @c 1 - Counter-clockwise.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function will set the DIR bit from SETTINGS1 register, and clear the others to default state.
 */
err_t magneticrotary4_set_rotation_direction ( magneticrotary4_t *ctx, uint8_t direction );

#ifdef __cplusplus
}
#endif
#endif // MAGNETICROTARY4_H

/*! @} */ // magneticrotary4

// ------------------------------------------------------------------------ END
