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
 * @file pressure27.h
 * @brief This file contains API for Pressure 27 Click Driver.
 */

#ifndef PRESSURE27_H
#define PRESSURE27_H

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
 * @addtogroup pressure27 Pressure 27 Click Driver
 * @brief API for configuring and manipulating Pressure 27 Click driver.
 * @{
 */

/**
 * @defgroup pressure27_cmd Pressure 27 Commands List
 * @brief List of Commands of Pressure 27 Click driver.
 */

/**
 * @addtogroup pressure27_cmd
 * @{
 */

/**
 * @brief Pressure 27 command list.
 * @details Specified command list of Pressure 27 Click driver.
 */
#define PRESSURE27_CMD_MEASURE               0xAA
#define PRESSURE27_CMD_NOP                   0xF0

/*! @} */ // pressure27_cmd

/**
 * @defgroup pressure27_set Pressure 27 Commands Settings
 * @brief Settings for Commands of Pressure 27 Click driver.
 */

/**
 * @addtogroup pressure27_set
 * @{
 */

/**
 * @brief Pressure 27 status byte bit masks setting.
 * @details Specified setting for status byte bit masks of Pressure 27 Click driver.
 */
#define PRESSURE27_STATUS_POWER_BIT          0x40   
#define PRESSURE27_STATUS_BUSY_BIT           0x20   
#define PRESSURE27_STATUS_MEM_ERR_BIT        0x04   
#define PRESSURE27_STATUS_MATH_SAT_BIT       0x01   

/**
 * @brief Pressure 27 transfer function A output counts setting.
 * @details Specified setting for transfer function A output counts of Pressure 27 Click driver.
 */
#define PRESSURE27_OUTPUT_MIN                1677722.0f
#define PRESSURE27_OUTPUT_MAX                15099494.0f

/**
 * @brief Pressure 27 pressure range setting.
 * @details Specified setting for pressure range of Pressure 27 Click driver.
 */
#define PRESSURE27_PMIN_KPA                  0.0f    
#define PRESSURE27_PMAX_KPA                  250.0f  

/**
 * @brief Pressure 27 timing setting.
 * @details Specified setting for timing of Pressure 27 Click driver.        
 */
#define PRESSURE27_CONVERSION_TIMEOUT_MS     10u     

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b pressure27_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define PRESSURE27_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define PRESSURE27_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // pressure27_set

/**
 * @defgroup pressure27_map Pressure 27 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 27 Click driver.
 */

/**
 * @addtogroup pressure27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 27 Click to the selected MikroBUS.
 */
#define PRESSURE27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.eoc  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pressure27_map
/*! @} */ // pressure27

/**
 * @brief Pressure 27 Click context object.
 * @details Context object definition of Pressure 27 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Hardware reset pin (active-low, drives sensor RES). */

    // Input pins
    digital_in_t eoc;               /**< End-of-Conversion pin (HIGH = data ready). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */

} pressure27_t;

/**
 * @brief Pressure 27 Click configuration object.
 * @details Configuration object definition of Pressure 27 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rst;             /**< Hardware reset output pin descriptor. */
    pin_name_t eoc;             /**< End-of-Conversion input pin descriptor. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} pressure27_cfg_t;

/**
 * @brief Pressure 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESSURE27_OK = 0,
    PRESSURE27_ERROR = -1

} pressure27_return_value_t;

/*!
 * @addtogroup pressure27 Pressure 27 Click Driver
 * @brief API for configuring and manipulating Pressure 27 Click driver.
 * @{
 */

/**
 * @brief Pressure 27 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure27_cfg_setup ( pressure27_cfg_t *cfg );

/**
 * @brief Pressure 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pressure27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure27_init ( pressure27_t *ctx, pressure27_cfg_t *cfg );

/**
 * @brief Pressure 27 hardware reset function.
 * @details This function performs a hardware reset of the sensor by driving
 * the RES pin low for 1 ms, then high again. 
 * @param[in] ctx : Click context object.
 * See #pressure27_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void pressure27_hw_reset ( pressure27_t *ctx );

/**
 * @brief Pressure 27 get End-of-Conversion state function.
 * @details This function reads the current logic level of the EOC pin.
 * @param[in] ctx : Click context object.
 * See #pressure27_t object definition for detailed explanation.
 * @return @li @c 0 - Conversion not complete,
 *         @li @c 1 - Conversion complete, data ready.
 * @note None.
 */
uint8_t pressure27_get_eoc ( pressure27_t *ctx );

/**
 * @brief Pressure 27 get pressure function.
 * @details This function triggers a pressure measurement, waits for the
 * End-of-Conversion signal, reads back the 24-bit result, checks the status
 * byte for errors, and converts the raw counts to pressure in kPa using
 * the Transfer Function A formula.
 * @param[in] ctx : Click context object.
 * See #pressure27_t object definition for detailed explanation.
 * @param[out] pressure : Pointer to output Pressure value in kPa.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure27_get_pressure ( pressure27_t *ctx, float *pressure );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE27_H

/*! @} */ // pressure27

// ------------------------------------------------------------------------ END
