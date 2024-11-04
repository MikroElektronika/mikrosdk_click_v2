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
 * @file volume.h
 * @brief This file contains API for Volume Click Driver.
 */

#ifndef VOLUME_H
#define VOLUME_H

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
#include "drv_spi_master.h"

/*!
 * @addtogroup volume Volume Click Driver
 * @brief API for configuring and manipulating Volume Click driver.
 * @{
 */

/**
 * @addtogroup zce_state
 * @{
 */

/**
 * @brief Zero Crossing definitions.
 * @details Specified definitions for zero crossing of Volume Click driver.
 */

#define VOLUME_ZCE_DISABLE  0x00
#define VOLUME_ZCE_ENABLE   0x01

/*! @} */ // zce_state

/**
 * @addtogroup mute_state
 * @{
 */

/**
 * @brief Hardware mute definitions.
 * @details Specified definitions for hardware mute control of Volume Click driver.
 */

#define VOLUME_MUTE_ENABLE  0x00
#define VOLUME_MUTE_DISABLE 0x01

/*! @} */ // mute_state


/**
 * @defgroup volume_map Volume MikroBUS Map
 * @brief MikroBUS pin mapping of Volume Click driver.
 */

/**
 * @addtogroup volume_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Volume Click to the selected MikroBUS.
 */
#define VOLUME_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.zce = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sen = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // volume_map
/*! @} */ // volume

/**
 * @brief Volume Click context object.
 * @details Context object definition of Volume Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  zce;                                  /**< Output pin for Zero Crossing option. */
    digital_out_t  sen;                                  /**< Output pin for Hardware MUTE. */

    // Modules

    spi_master_t  spi;                                   /**< SPI driver object. */

    pin_name_t    chip_select;                           /**< Chip select pin descriptor (used for SPI driver). */

} volume_t;

/**
 * @brief Volume Click configuration object.
 * @details Configuration object definition of Volume Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins

    pin_name_t   zce;                                    /**< Output pin for Zero Crossing option. */
    pin_name_t   sen;                                    /**< Output pin for Hardware MUTE. */

    // static variable

    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} volume_cfg_t;

/*!
 * @addtogroup volume Volume Click Driver
 * @brief API for configuring and manipulating Volume Click driver.
 * @{
 */

/**
 * @brief Volume configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #volume_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void volume_cfg_setup ( volume_cfg_t *cfg );

/**
 * @brief Volume initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #volume_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #volume_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t volume_init ( volume_t *ctx, volume_cfg_t *cfg );

/**
 * @brief Volume default configuration function.
 * @details This function executes a default configuration of Volume
 * Click board.
 * @param[in] ctx : Click context object.
 * See #volume_t object definition for detailed explanation.
 * 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void volume_default_cfg ( volume_t *ctx );

/**
 * @brief Power Up function.
 * @details This function should be called upon initial power-up sequence.
 * This sequence sets the serial shift register and the volume control register to
 * zero and performs an offset calibration.
 * @param ctx Click object.
 * 
 * @note None.
 */
void volume_power_up ( volume_t *ctx );

/**
 * @brief Hardware MUTE function.
 * @details This function performs hardware mute by setting the state of SEN pin.
 * @param ctx Click object.
 * @param[in] mute_state :
 *     @li @c 0x00 ( VOLUME_MUTE_ENABLE ) - Sets SEN pin low, thus enabling the mute option,
 *     @li @c 0x01 ( VOLUME_MUTE_DISABLE ) - Sets SEN pin high, thus disabling the mute option.
 * 
 * @note None.
 */
void volume_hw_mute ( volume_t *ctx, uint8_t mute_state );

/**
 * @brief Zero Crossing option function.
 * @details This function enables the zero crossing option by setting the state of ZCE pin.
 * @param ctx Click object.
 * @param[in] zce_state :
 *     @li @c 0x00 ( VOLUME_ZCE_DISABLE ) - Sets ZCE pin low, thus disabling the zero crossing option,
 *     @li @c 0x01 ( VOLUME_ZCE_ENABLE ) - Sets ZCE pin high, thus enabling the zero crossing option.
 * 
 * @note None.
 */
void volume_zero_crossing ( volume_t *ctx, uint8_t zce_state );

/**
 * @brief Set volume gain function.
 * @details This function sets a desired gain volume of left and right channel speaker.
 * @param[in] ctx : Click context object.
 * @param[in] volume_left : Gain in [dB] on the left channel ranging from -96.0 to +31.5.
 * @param[in] volume_right : Gain in [dB] on the right channel ranging from -96.0 to +31.5.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The step of the gain is 0.5 [dB], hence the values between will be rounded by the compiler.
 */
err_t volume_set_vol_gain ( volume_t *ctx, float volume_left_dB, float volume_right_dB );

#ifdef __cplusplus
}
#endif
#endif // VOLUME_H

/*! @} */ // volume

// ------------------------------------------------------------------------ END
