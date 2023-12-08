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
 * @file leddriver10.h
 * @brief This file contains API for LED Driver 10 Click Driver.
 */

#ifndef LEDDRIVER10_H
#define LEDDRIVER10_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "drv_pwm.h"

/*!
 * @addtogroup leddriver10 LED Driver 10 Click Driver
 * @brief API for configuring and manipulating LED Driver 10 Click driver.
 * @{
 */

/**
 * @defgroup leddriver10_set LED Driver 10 Registers Settings
 * @brief Settings for registers of LED Driver 10 Click driver.
 */

/**
 * @addtogroup leddriver10_set
 * @{
 */

/**
 * @brief LED Driver 10 output flags.
 * @details Specified flags for output channels of LED Driver 10 Click driver.
 */
#define LEDDRIVER10_ENABLE_ALL_CH     0xFFFF
#define LEDDRIVER10_DISABLE_ALL_CH    0x0000
#define LEDDRIVER10_ENABLE_CH_0       0x0001
#define LEDDRIVER10_ENABLE_CH_1       0x0002
#define LEDDRIVER10_ENABLE_CH_2       0x0004
#define LEDDRIVER10_ENABLE_CH_3       0x0008
#define LEDDRIVER10_ENABLE_CH_4       0x0010
#define LEDDRIVER10_ENABLE_CH_5       0x0020
#define LEDDRIVER10_ENABLE_CH_6       0x0040
#define LEDDRIVER10_ENABLE_CH_7       0x0080
#define LEDDRIVER10_ENABLE_CH_8       0x0100
#define LEDDRIVER10_ENABLE_CH_9       0x0200
#define LEDDRIVER10_ENABLE_CH_10      0x0400
#define LEDDRIVER10_ENABLE_CH_11      0x0800
#define LEDDRIVER10_ENABLE_CH_12      0x1000
#define LEDDRIVER10_ENABLE_CH_13      0x2000
#define LEDDRIVER10_ENABLE_CH_14      0x4000
#define LEDDRIVER10_ENABLE_CH_15      0x8000

/**
 * @brief LED Driver 10 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of LED Driver 10 Click driver.
 */
#define LEDDRIVER10_DEF_FREQ          10000

/*! @} */ // leddriver10_set

/**
 * @defgroup leddriver10_map LED Driver 10 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Driver 10 Click driver.
 */

/**
 * @addtogroup leddriver10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Driver 10 Click to the selected MikroBUS.
 */
#define LEDDRIVER10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwm  = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // leddriver10_map
/*! @} */ // leddriver10

/**
 * @brief LED Driver 10 Click context object.
 * @details Context object definition of LED Driver 10 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t  spi;          /**< SPI driver object. */
    pwm_t         pwm;          /**< PWM driver object. */

    pin_name_t    chip_select;  /**< Chip select pin descriptor (used for SPI driver). */    
    uint32_t      pwm_freq;     /**< PWM frequency value. */

} leddriver10_t;

/**
 * @brief LED Driver 10 Click configuration object.
 * @details Configuration object definition of LED Driver 10 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;                                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                                      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  pwm;                                     /**< Blank pin. */

    // Static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */
    uint32_t                           dev_pwm_freq;     /**< PWM frequency value. */
    
} leddriver10_cfg_t;

/**
 * @brief LED Driver 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDDRIVER10_OK = 0,
    LEDDRIVER10_ERROR = -1

} leddriver10_return_value_t;

/*!
 * @addtogroup leddriver10 LED Driver 10 Click Driver
 * @brief API for configuring and manipulating LED Driver 10 Click driver.
 * @{
 */

/**
 * @brief LED Driver 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #leddriver10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void leddriver10_cfg_setup ( leddriver10_cfg_t *cfg );

/**
 * @brief LED Driver 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #leddriver10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #leddriver10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver10_init ( leddriver10_t *ctx, leddriver10_cfg_t *cfg );

/**
 * @brief LED Driver 10 set channels function.
 * @details This function sets all channels to desired value by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver10_t object definition for detailed explanation.
 * @param[in] ch_mask : Channel mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function affects all channel outputs.
 */
err_t leddriver10_set_channels ( leddriver10_t *ctx, uint16_t ch_mask );

/**
 * @brief LED Driver 10 read channels function.
 * @details This function reads the current state of all channels by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver10_t object definition for detailed explanation.
 * @param[out] ch_mask : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function doesn't affect the channels output state.
 */
err_t leddriver10_read_channels ( leddriver10_t *ctx, uint16_t *ch_mask );

/**
 * @brief LED Driver 10 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #leddriver10_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty_cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver10_set_duty_cycle ( leddriver10_t *ctx, float duty_cycle );

/**
 * @brief LED Driver 10 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[out] ctx : Click context object.
 * See #leddriver10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver10_pwm_stop ( leddriver10_t *ctx );

/**
 * @brief LED Driver 10 start PWM module.
 * @details This function starts the PWM module output.
 * @param[out] ctx : Click context object.
 * See #leddriver10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver10_pwm_start ( leddriver10_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LEDDRIVER10_H

/*! @} */ // leddriver10

// ------------------------------------------------------------------------ END
