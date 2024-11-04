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
 * @file microsd.h
 * @brief This file contains API for microSD Click Driver.
 */

#ifndef MICROSD_H
#define MICROSD_H

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

#include "drv_digital_in.h"
#include "MikroSDK.PhysicalDrive"
#include "MikroSDK.FileSystem"

/*!
 * @addtogroup microsd microSD Click Driver
 * @brief API for configuring and manipulating microSD Click driver.
 * @{
 */

/**
 * @defgroup microsd_set microSD Registers Settings
 * @brief Settings for registers of microSD Click driver.
 */

/**
 * @addtogroup microsd_set
 * @{
 */

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b microsd_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define MICROSD_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define MICROSD_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // microsd_set

/**
 * @defgroup microsd_map microSD MikroBUS Map
 * @brief MikroBUS pin mapping of microSD Click driver.
 */

/**
 * @addtogroup microsd_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of microSD Click to the selected MikroBUS.
 */
#define MICROSD_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cd_pin = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // microsd_map
/*! @} */ // microsd

/**
 * @brief microSD Click context object.
 * @details Context object definition of microSD Click driver.
 */
typedef struct
{
    digital_in_t cd_pin;
    
    sdspi_physical_drive_t sd_pdrive;

    fatfs_logical_drive_t fat_ldrive;

} microsd_t;

/**
 * @brief microSD Click configuration object.
 * @details Configuration object definition of microSD Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    
    pin_name_t cd_pin;              /**< SD card detect pin (Active LOW). */

} microsd_cfg_t;

/**
 * @brief microSD Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MICROSD_OK = 0,
    MICROSD_ERROR = -1

} microsd_return_value_t;

/*!
 * @addtogroup microsd microSD Click Driver
 * @brief API for configuring and manipulating microSD Click driver.
 * @{
 */

/**
 * @brief microSD configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #microsd_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void microsd_cfg_setup ( microsd_cfg_t *cfg );

/**
 * @brief microSD initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #microsd_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #microsd_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t microsd_init ( microsd_t *ctx, microsd_cfg_t *cfg );

/**
 * @brief microSD get card detect function.
 * @details This function returns the card detect pin logic state.
 * @param[in] ctx : Click context object.
 * See #microsd_t object definition for detailed explanation.
 * @return @li @c 0 - Card detected,
 *         @li @c 1 - Card not detected.
 * @note None.
 */
uint8_t microsd_get_card_detect ( microsd_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // MICROSD_H

/*! @} */ // microsd

// ------------------------------------------------------------------------ END
