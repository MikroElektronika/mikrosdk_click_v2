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
 * @file magneticrotary3.h
 * @brief This file contains API for Magnetic Rotary 3 Click Driver.
 */

#ifndef MAGNETICROTARY3_H
#define MAGNETICROTARY3_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup magneticrotary3 Magnetic Rotary 3 Click Driver
 * @brief API for configuring and manipulating Magnetic Rotary 3 Click driver.
 * @{
 */

/**
 * @defgroup magneticrotary3_reg Magnetic Rotary 3 Registers List
 * @brief List of registers of Magnetic Rotary 3 Click driver.
 */

/**
 * @addtogroup magneticrotary3_reg
 * @{
 */

/**
 * @brief Magnetic Rotary 3 volatile registers list.
 * @details Specified list of volatile registers of Magnetic Rotary 3 Click driver.
 */
#define MAGNETICROTARY3_REG_NOP                 0x0000
#define MAGNETICROTARY3_REG_ERRFL               0x0001
#define MAGNETICROTARY3_REG_PROG                0x0003
#define MAGNETICROTARY3_REG_DIA                 0x3FF5
#define MAGNETICROTARY3_REG_AGC                 0x3FF9
#define MAGNETICROTARY3_REG_SIN_DATA            0x3FFA
#define MAGNETICROTARY3_REG_COS_DATA            0x3FFB
#define MAGNETICROTARY3_REG_VEL                 0x3FFC
#define MAGNETICROTARY3_REG_MAG                 0x3FFD
#define MAGNETICROTARY3_REG_ANGLEUNC            0x3FFE
#define MAGNETICROTARY3_REG_ANGLECOM            0x3FFF
#define MAGNETICROTARY3_REG_ECC_CHECKSUM        0x00D1

/**
 * @brief Magnetic Rotary 3 non-volatile registers list.
 * @details Specified list of non-volatile registers of Magnetic Rotary 3 Click driver.
 */
#define MAGNETICROTARY3_REG_DISABLE             0x0015
#define MAGNETICROTARY3_REG_ZPOSM               0x0016
#define MAGNETICROTARY3_REG_ZPOSL               0x0017
#define MAGNETICROTARY3_REG_SETTINGS1           0x0018
#define MAGNETICROTARY3_REG_SETTINGS2           0x0019
#define MAGNETICROTARY3_REG_SETTINGS3           0x001A
#define MAGNETICROTARY3_REG_ECC                 0x001B

/*! @} */ // magneticrotary3_reg

/**
 * @defgroup magneticrotary3_set Magnetic Rotary 3 Registers Settings
 * @brief Settings for registers of Magnetic Rotary 3 Click driver.
 */

/**
 * @addtogroup magneticrotary3_set
 * @{
 */

/**
 * @brief Magnetic Rotary 3 angle calculation values.
 * @details Specified angle calculation values of Magnetic Rotary 3 Click driver.
 */
#define MAGNETICROTARY3_DATA_RESOLUTION         0x3FFF
#define MAGNETICROTARY3_FULL_CIRCLE             360

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU.
 */
#define MAGNETICROTARY3_SET_DATA_SAMPLE_EDGE    SET_SPI_DATA_SAMPLE_EDGE
#define MAGNETICROTARY3_SET_DATA_SAMPLE_MIDDLE  SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // magneticrotary3_set

/**
 * @defgroup magneticrotary3_map Magnetic Rotary 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Magnetic Rotary 3 Click driver.
 */

/**
 * @addtogroup magneticrotary3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Magnetic Rotary 3 Click to the selected MikroBUS.
 */
#define MAGNETICROTARY3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // magneticrotary3_map
/*! @} */ // magneticrotary3

/**
 * @brief Magnetic Rotary 3 Click context object.
 * @details Context object definition of Magnetic Rotary 3 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} magneticrotary3_t;

/**
 * @brief Magnetic Rotary 3 Click configuration object.
 * @details Configuration object definition of Magnetic Rotary 3 Click driver.
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

} magneticrotary3_cfg_t;

/**
 * @brief Magnetic Rotary 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MAGNETICROTARY3_OK = 0,
    MAGNETICROTARY3_ERROR = -1

} magneticrotary3_return_value_t;

/*!
 * @addtogroup magneticrotary3 Magnetic Rotary 3 Click Driver
 * @brief API for configuring and manipulating Magnetic Rotary 3 Click driver.
 * @{
 */

/**
 * @brief Magnetic Rotary 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #magneticrotary3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void magneticrotary3_cfg_setup ( magneticrotary3_cfg_t *cfg );

/**
 * @brief Magnetic Rotary 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #magneticrotary3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #magneticrotary3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary3_init ( magneticrotary3_t *ctx, magneticrotary3_cfg_t *cfg );

/**
 * @brief Magnetic Rotary 3 write register function.
 * @details This function writes a desired data to the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #magneticrotary3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary3_write_register ( magneticrotary3_t *ctx, uint16_t reg, uint16_t data_in );

/**
 * @brief Magnetic Rotary 3 read register function.
 * @details This function reads data from the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #magneticrotary3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary3_read_register ( magneticrotary3_t *ctx, uint16_t reg, uint16_t *data_out );

/**
 * @brief Magnetic Rotary 3 get angle function.
 * @details This function reads the absolute position raw data and converts it to degrees (Angle).
 * @param[in] ctx : Click context object.
 * See #magneticrotary3_t object definition for detailed explanation.
 * @param[out] angle : Angle in degrees [0-360].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t magneticrotary3_get_angle ( magneticrotary3_t *ctx, float *angle );

#ifdef __cplusplus
}
#endif
#endif // MAGNETICROTARY3_H

/*! @} */ // magneticrotary3

// ------------------------------------------------------------------------ END
