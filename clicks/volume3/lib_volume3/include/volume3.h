/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file volume3.h
 * @brief This file contains API for Volume 3 Click Driver.
 */

#ifndef VOLUME3_H
#define VOLUME3_H

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
 * @addtogroup volume3 Volume 3 Click Driver
 * @brief API for configuring and manipulating Volume 3 Click driver.
 * @{
 */

/**
 * @defgroup volume3_set Volume 3 Settings
 * @brief Settings of Volume 3 Click driver.
 */

/**
 * @addtogroup volume3_set
 * @{
 */

/**
 * @brief Volume 3 volume setting.
 * @details Specified setting for volume of Volume 3 Click driver.
 */
#define VOLUME3_GAIN_DB_STEP                0.5
#define VOLUME3_GAIN_DB_MIN                -95.5
#define VOLUME3_GAIN_DB_MAX                 35.5
#define VOLUME3_GAIN_DB_VOLUME_MIN         -55.0
#define VOLUME3_GAIN_DB_VOLUME_MAX         -5.0
#define VOLUME3_VOLUME_MUTE                 0
#define VOLUME3_VOLUME_MIN                  1
#define VOLUME3_VOLUME_MAX                  100

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b volume3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define VOLUME3_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define VOLUME3_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // volume3_set

/**
 * @defgroup volume3_map Volume 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Volume 3 Click driver.
 */

/**
 * @addtogroup volume3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Volume 3 Click to the selected MikroBUS.
 */
#define VOLUME3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.zce  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sen  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \

/*! @} */ // volume3_map
/*! @} */ // volume3

/**
 * @brief Volume 3 Click context object.
 * @details Context object definition of Volume 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t zce;          /**< Active high zero-crossing detection enable pin. */
    digital_out_t sen;          /**< Active low MUTE pin i.e. active high sound enable pin. */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    float gain_left;            /**< Volume gain level in dB for left channel. */
    float gain_right;           /**< Volume gain level in dB for right channel. */

} volume3_t;

/**
 * @brief Volume 3 Click configuration object.
 * @details Configuration object definition of Volume 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t zce;             /**< Active high zero-crossing detection enable pin. */
    pin_name_t sen;             /**< Active low MUTE pin i.e. active high sound enable pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} volume3_cfg_t;

/**
 * @brief Volume 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    VOLUME3_OK = 0,
    VOLUME3_ERROR = -1

} volume3_return_value_t;

/*!
 * @addtogroup volume3 Volume 3 Click Driver
 * @brief API for configuring and manipulating Volume 3 Click driver.
 * @{
 */

/**
 * @brief Volume 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #volume3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void volume3_cfg_setup ( volume3_cfg_t *cfg );

/**
 * @brief Volume 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #volume3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #volume3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t volume3_init ( volume3_t *ctx, volume3_cfg_t *cfg );

/**
 * @brief Volume 3 set gain function.
 * @details This function sets the left and right channel gain in dB.
 * The gain values are converted into register values and written via SPI.
 * @param[in] ctx : Click context object.
 * See #volume3_t object definition for detailed explanation.
 * @param[in] gain_left : Left channel gain value in dB.
 * @param[in] gain_right : Right channel gain value in dB.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t volume3_set_gain ( volume3_t *ctx, float gain_left, float gain_right );

/**
 * @brief Volume 3 set volume function.
 * @details This function sets the left and right channel volume levels in percents.
 * @param[in] ctx : Click context object.
 * See #volume3_t object definition for detailed explanation.
 * @param[in] volume_left : Left channel volume level (0 to 100).
 * @param[in] volume_right : Right channel volume level (0 to 100).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t volume3_set_volume ( volume3_t *ctx, uint8_t volume_left, uint8_t volume_right );

/**
 * @brief Volume 3 enable zero-crossing detection function.
 * @details This function enables the zero-crossing detection feature by setting the ZCE pin high.
 * @param[in] ctx : Click context object.
 * See #volume3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void volume3_zero_crossing_enable ( volume3_t *ctx );

/**
 * @brief Volume 3 disable zero-crossing detection function.
 * @details This function disables the zero-crossing detection feature by setting the ZCE pin low.
 * @param[in] ctx : Click context object.
 * See #volume3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void volume3_zero_crossing_disable ( volume3_t *ctx );

/**
 * @brief Volume 3 sound enable function.
 * @details This function enables the audio output by setting the SEN pin high.
 * @param[in] ctx : Click context object.
 * See #volume3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void volume3_sound_enable ( volume3_t *ctx );

/**
 * @brief Volume 3 sound disable function.
 * @details This function disables the audio output by setting the SEN pin low.
 * @param[in] ctx : Click context object.
 * See #volume3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void volume3_sound_disable ( volume3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VOLUME3_H

/*! @} */ // volume3

// ------------------------------------------------------------------------ END
