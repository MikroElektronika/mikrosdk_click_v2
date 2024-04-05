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
 * @file thermo25.h
 * @brief This file contains API for Thermo 25 Click Driver.
 */

#ifndef THERMO25_H
#define THERMO25_H

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
 * @addtogroup thermo25 Thermo 25 Click Driver
 * @brief API for configuring and manipulating Thermo 25 Click driver.
 * @{
 */

/**
 * @defgroup thermo25_set Thermo 25 Registers Settings
 * @brief Settings for registers of Thermo 25 Click driver.
 */

/**
 * @addtogroup thermo25_set
 * @{
 */

/**
 * @brief Thermo 25 mode select setting.
 * @details Specified setting for mode select of Thermo 25 Click driver.
 */
#define THERMO25_MODE_CONTINUOUS            0x00
#define THERMO25_MODE_SHUTDOWN              0xFF

/**
 * @brief Thermo 25 device ID setting.
 * @details Specified setting for device ID of Thermo 25 Click driver.
 */
#define THERMO25_DEVICE_ID                  0x900F

/**
 * @brief Thermo 25 temperature data resolution setting.
 * @details Specified setting for temperature data resolution of Thermo 25 Click driver.
 */
#define THERMO25_DATA_RESOLUTION            0.03125f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b thermo25_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define THERMO25_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define THERMO25_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // thermo25_set

/**
 * @defgroup thermo25_map Thermo 25 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 25 Click driver.
 */

/**
 * @addtogroup thermo25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 25 Click to the selected MikroBUS.
 */
#define THERMO25_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );
    
/*! @} */ // thermo25_map
/*! @} */ // thermo25

/**
 * @brief Thermo 25 Click context object.
 * @details Context object definition of Thermo 25 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */
    
    uint8_t      dev_mode;      /**< Device mode. */

} thermo25_t;

/**
 * @brief Thermo 25 Click configuration object.
 * @details Configuration object definition of Thermo 25 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} thermo25_cfg_t;

/**
 * @brief Thermo 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO25_OK = 0,
    THERMO25_ERROR = -1

} thermo25_return_value_t;

/*!
 * @addtogroup thermo25 Thermo 25 Click Driver
 * @brief API for configuring and manipulating Thermo 25 Click driver.
 * @{
 */

/**
 * @brief Thermo 25 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo25_cfg_setup ( thermo25_cfg_t *cfg );

/**
 * @brief Thermo 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermo25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo25_init ( thermo25_t *ctx, thermo25_cfg_t *cfg );

/**
 * @brief Thermo 25 set mode function.
 * @details This function sets the device operating mode to shutdown or continuous mode
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo25_t object definition for detailed explanation.
 * @param[in] mode : Device operating mode @li @c 0x00 - Continuous,
 *                                         @li @c 0xFF - Shutdown.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo25_set_mode ( thermo25_t *ctx, uint8_t mode );

/**
 * @brief Thermo 25 read data function.
 * @details This function reads 16-bit data and keeps the previously set operating mode unchanged
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo25_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo25_read_data ( thermo25_t *ctx, uint16_t *data_out );

/**
 * @brief Thermo 25 check communication function.
 * @details This function sets the operating mode to shutdown, then reads and verifies the device ID,
 * and switches back to the continuous mode.
 * @param[in] ctx : Click context object.
 * See #thermo25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo25_check_communication ( thermo25_t *ctx );

/**
 * @brief Thermo 25 read temperature function.
 * @details This function reads the temperature measurements in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo25_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo25_read_temperature ( thermo25_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // THERMO25_H

/*! @} */ // thermo25

// ------------------------------------------------------------------------ END
