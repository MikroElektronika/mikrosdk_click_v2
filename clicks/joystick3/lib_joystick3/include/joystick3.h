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
 * @file joystick3.h
 * @brief This file contains API for Joystick 3 Click Driver.
 */

#ifndef JOYSTICK3_H
#define JOYSTICK3_H

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
 * @addtogroup joystick3 Joystick 3 Click Driver
 * @brief API for configuring and manipulating Joystick 3 Click driver.
 * @{
 */

/**
 * @defgroup joystick3_set Joystick 3 Registers Settings
 * @brief Settings for registers of Joystick 3 Click driver.
 */

/**
 * @addtogroup joystick3_set
 * @{
 */

/**
 * @brief Joystick 3 ADC calculation values.
 * @details Specified ADC calculation values of Joystick 3 Click driver.
 */
#define JOYSTICK3_ADC_START_BIT             0x04
#define JOYSTICK3_ADC_SINGLE_ENDED          0x02
#define JOYSTICK3_ADC_CHANNEL_X             0x00
#define JOYSTICK3_ADC_CHANNEL_Y             0x40
#define JOYSTICK3_ADC_DATA_RESOLUTION       0x0FFF
#define JOYSTICK3_ADC_DATA_RESOLUTION_HALF  ( ( float ) JOYSTICK3_ADC_DATA_RESOLUTION / 2 )

/**
 * @brief Joystick 3 angle and position calculation values.
 * @details Specified angle and position calculation values of Joystick 3 Click driver.
 */
#define JOYSTICK3_RADIANS_TO_DEGREES        57.295779513
#define JOYSTICK3_ANGLE_ZERO_OFFSET         180.0
#define JOYSTICK3_PI_RAD_OFFSET             1.0
#define JOYSTICK3_NEUTRAL_POSITION_OFFSET   ( ( float ) JOYSTICK3_ADC_DATA_RESOLUTION / 8 )
#define JOYSTICK3_FULL_ANGLE                360.0f
#define JOYSTICK3_ZERO_ANGLE                0.0f
#define JOYSTICK3_ANGLE_POSITION_STEP       45.0f

/**
 * @brief Joystick 3 position values.
 * @details Specified position values of Joystick 3 Click driver.
 */
#define JOYSTICK3_POSITION_NEUTRAL          0
#define JOYSTICK3_POSITION_UP               1
#define JOYSTICK3_POSITION_UPPER_RIGHT      2
#define JOYSTICK3_POSITION_RIGHT            3
#define JOYSTICK3_POSITION_LOWER_RIGHT      4
#define JOYSTICK3_POSITION_DOWN             5
#define JOYSTICK3_POSITION_LOWER_LEFT       6
#define JOYSTICK3_POSITION_LEFT             7
#define JOYSTICK3_POSITION_UPPER_LEFT       8

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b joystick3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define JOYSTICK3_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define JOYSTICK3_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // joystick3_set

/**
 * @defgroup joystick3_map Joystick 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Joystick 3 Click driver.
 */

/**
 * @addtogroup joystick3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Joystick 3 Click to the selected MikroBUS.
 */
#define JOYSTICK3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );

/*! @} */ // joystick3_map
/*! @} */ // joystick3

/**
 * @brief Joystick 3 Click context object.
 * @details Context object definition of Joystick 3 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;                   /**< SPI driver object. */

    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */

} joystick3_t;

/**
 * @brief Joystick 3 Click configuration object.
 * @details Configuration object definition of Joystick 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} joystick3_cfg_t;

/**
 * @brief Joystick 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    JOYSTICK3_OK = 0,
    JOYSTICK3_ERROR = -1

} joystick3_return_value_t;

/*!
 * @addtogroup joystick3 Joystick 3 Click Driver
 * @brief API for configuring and manipulating Joystick 3 Click driver.
 * @{
 */

/**
 * @brief Joystick 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #joystick3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void joystick3_cfg_setup ( joystick3_cfg_t *cfg );

/**
 * @brief Joystick 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #joystick3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #joystick3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t joystick3_init ( joystick3_t *ctx, joystick3_cfg_t *cfg );

/**
 * @brief Joystick 3 read raw adc function.
 * @details This function reads the raw ADC for X and Y axis by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #joystick3_t object definition for detailed explanation.
 * @param[out] raw_x : RAW X axis data (0-4095).
 * @param[out] raw_y : RAW Y axis data (0-4095).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t joystick3_read_raw_adc ( joystick3_t *ctx, uint16_t *raw_x, uint16_t *raw_y );

/**
 * @brief Joystick 3 get angle function.
 * @details This function calculates and returns joystick angle in degrees from raw ADC values for X and Y axis.
 * @param[in] raw_x : RAW X axis data (0-4095).
 * @param[in] raw_y : RAW Y axis data (0-4095).
 * @return Joystick angle in degrees.
 * @note None.
 */
float joystick3_get_angle ( uint16_t raw_x, uint16_t raw_y );

/**
 * @brief Joystick 3 get position function.
 * @details This function calculates and returns joystick position flag from raw ADC values for X and Y axis.
 * @param[in] raw_x : RAW X axis data (0-4095).
 * @param[in] raw_y : RAW Y axis data (0-4095).
 * @return Joystick position flag. Refer to the position values macro definitions.
 * @note None.
 */
uint8_t joystick3_get_position ( uint16_t raw_x, uint16_t raw_y );

#ifdef __cplusplus
}
#endif
#endif // JOYSTICK3_H

/*! @} */ // joystick3

// ------------------------------------------------------------------------ END
