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
 * @file utl7segb.h
 * @brief This file contains API for UT-L 7-SEG B Click Driver.
 */

#ifndef UTL7SEGB_H
#define UTL7SEGB_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup utl7segb UT-L 7-SEG B Click Driver
 * @brief API for configuring and manipulating UT-L 7-SEG B Click driver.
 * @{
 */

/**
 * @defgroup utl7segb_base UT-L 7-SEG B Registers List
 * @brief List of registers of UT-L 7-SEG B Click driver.
 */

/**
 * @addtogroup utl7segb_base
 * @{
 */

/**
 * @brief UT-L 7-SEG B description of the base values.
 * @details Specified base values, number of digits used to represent numbers
 * of UT-L 7-SEG B Click driver.
 */
#define UTL7SEGB_BASE_NUM_SYS_BINARY                2
#define UTL7SEGB_BASE_NUM_SYS_TERNARY               3
#define UTL7SEGB_BASE_NUM_SYS_QUATERNARY            4
#define UTL7SEGB_BASE_NUM_SYS_QUINARY               5
#define UTL7SEGB_BASE_NUM_SYS_SENARY                6
#define UTL7SEGB_BASE_NUM_SYS_SEPTENARY             7
#define UTL7SEGB_BASE_NUM_SYS_OCTAL                 8
#define UTL7SEGB_BASE_NUM_SYS_NONARY                9
#define UTL7SEGB_BASE_NUM_SYS_DECIMAL               10
#define UTL7SEGB_BASE_NUM_SYS_UNDECIMAL             11
#define UTL7SEGB_BASE_NUM_SYS_DUODECIMAL            12
#define UTL7SEGB_BASE_NUM_SYS_HEXADECIMAL           16

/*! @} */ // utl7segb_base

/**
 * @defgroup utl7segb_set UT-L 7-SEG B Registers Settings
 * @brief Settings for registers of UT-L 7-SEG B Click driver.
 */

/**
 * @addtogroup utl7segb_set
 * @{
 */

/**
 * @brief UT-L 7-SEG B description setting.
 * @details Specified setting for description of UT-L 7-SEG B Click driver.
 */
#define UTL7SEGB_NO_DOT                             0
#define UTL7SEGB_DOT_RIGHT                          1
#define UTL7SEGB_DOT_LEFT                           2
#define UTL7SEGB_DOT_LEFT_RIGHT                     3

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b utl7segb_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define UTL7SEGB_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define UTL7SEGB_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // utl7segb_set

/**
 * @defgroup utl7segb_map UT-L 7-SEG B MikroBUS Map
 * @brief MikroBUS pin mapping of UT-L 7-SEG B Click driver.
 */

/**
 * @addtogroup utl7segb_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UT-L 7-SEG B Click to the selected MikroBUS.
 */
#define UTL7SEGB_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.oe = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // utl7segb_map
/*! @} */ // utl7segb

/**
 * @brief UT-L 7-SEG B Click context object.
 * @details Context object definition of UT-L 7-SEG B Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t oe;    /**< Enable control pin. */

    // Modules
    spi_master_t spi;    /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} utl7segb_t;

/**
 * @brief UT-L 7-SEG B Click configuration object.
 * @details Configuration object definition of UT-L 7-SEG B Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t oe;      /**< Enable control pin. */

    // static variable
    uint32_t                          spi_speed;      /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;       /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;    /**< Chip select pin polarity. */

} utl7segb_cfg_t;

/**
 * @brief UT-L 7-SEG B Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UTL7SEGB_OK = 0,
    UTL7SEGB_ERROR = -1

} utl7segb_return_value_t;

/*!
 * @addtogroup utl7segb UT-L 7-SEG B Click Driver
 * @brief API for configuring and manipulating UT-L 7-SEG B Click driver.
 * @{
 */

/**
 * @brief UT-L 7-SEG B configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #utl7segb_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void utl7segb_cfg_setup ( utl7segb_cfg_t *cfg );

/**
 * @brief UT-L 7-SEG B initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #utl7segb_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #utl7segb_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t utl7segb_init ( utl7segb_t *ctx, utl7segb_cfg_t *cfg );

/**
 * @brief UT-L 7-SEG B default configuration function.
 * @details This function executes a default configuration of UT-L 7-SEG B
 * click board.
 * @param[in] ctx : Click context object.
 * See #utl7segb_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t utl7segb_default_cfg ( utl7segb_t *ctx );

/**
 * @brief UT-L 7-SEG B data writing function.
 * @details This function writes a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #utl7segb_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t utl7segb_generic_write ( utl7segb_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief UT-L 7-SEG B data reading function.
 * @details This function reads a desired number of data bytes by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #utl7segb_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t utl7segb_generic_read ( utl7segb_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief UT-L 7-SEG B enable function.
 * @details This function enables outputs to follow the state of the output latches
 * of the MAX6969, 16-Port, 5.5V Constant-Current LED Driver
 * on the UT-L 7-SEG B Click board™.
 * @param[in] ctx : Click context object.
 * See #utl7segb_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void utl7segb_enable ( utl7segb_t *ctx );

/**
 * @brief UT-L 7-SEG B disable function.
 * @details This function disable the output, without altering the contents of the output latches
 * of the MAX6969, 16-Port, 5.5V Constant-Current LED Driver
 * on the UT-L 7-SEG B Click board™.
 * @param[in] ctx : Click context object.
 * See #utl7segb_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void utl7segb_disable ( utl7segb_t *ctx );

/**
 * @brief UT-L 7-SEG B display number function.
 * @details This function display the desired number
 * of the MAX6969, 16-Port, 5.5V Constant-Current LED Driver
 * on the UT-L 7-SEG B Click board™.
 * @param[in] ctx : Click context object.
 * See #utl7segb_t object definition for detailed explanation.
 * @param[in] base : Total count of digits used to express numbers in a number system [0-16].
 * @param[in] num : Number (range depends on the base).
 * @param[in] dot_pos : Dot position (No use dot, dot left, right and left and right) [0-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t utl7segb_display_number ( utl7segb_t *ctx, uint8_t base, uint8_t num, uint8_t dot_pos );

/**
 * @brief UT-L 7-SEG B get number function.
 * @details This function reads and calculates the number shown on the display
 * of the MAX6969, 16-Port, 5.5V Constant-Current LED Driver
 * on the UT-L 7-SEG B Click board™.
 * @param[in] ctx : Click context object.
 * See #utl7segb_t object definition for detailed explanation.
 * @param[in] base : Total count of digits used to express numbers in a number system [0-16].
 * @param[out] num : Number (range depends on the base).
 * @param[out] dot_pos : Dot position (No use dot, dot left, right and left and right) [0-3].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t utl7segb_get_number ( utl7segb_t *ctx, uint8_t base, uint8_t *num, uint8_t *dot_pos );

#ifdef __cplusplus
}
#endif
#endif // UTL7SEGB_H

/*! @} */ // utl7segb

// ------------------------------------------------------------------------ END
