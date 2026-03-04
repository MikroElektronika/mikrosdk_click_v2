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
 * @file ultrasonic4.h
 * @brief This file contains API for Ultrasonic 4 Click Driver.
 */

#ifndef ULTRASONIC4_H
#define ULTRASONIC4_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup ultrasonic4 Ultrasonic 4 Click Driver
 * @brief API for configuring and manipulating Ultrasonic 4 Click driver.
 * @{
 */

/**
 * @defgroup ultrasonic4_set Ultrasonic 4 Registers Settings
 * @brief Settings for registers of Ultrasonic 4 Click driver.
 */

/**
 * @addtogroup ultrasonic4_set
 * @{
 */

/**
 * @brief Ultrasonic 4 default PWM frequency.
 * @details Specified setting for default PWM frequency of Ultrasonic 4 Click driver.
 */
#define ULTRASONIC4_PWM_DEF_FREQ                32767
#define ULTRASONIC4_PWM_DEF_DC                  0.5

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ultrasonic4_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ULTRASONIC4_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define ULTRASONIC4_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // ultrasonic4_set

/**
 * @defgroup ultrasonic4_map Ultrasonic 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Ultrasonic 4 Click driver.
 */

/**
 * @addtogroup ultrasonic4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Ultrasonic 4 Click to the selected MikroBUS.
 */
#define ULTRASONIC4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwm  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ultrasonic4_map
/*! @} */ // ultrasonic4

/**
 * @brief Ultrasonic 4 Click context object.
 * @details Context object definition of Ultrasonic 4 Click driver.
 */
typedef struct
{
    digital_out_t int_pin_out;      /**< Interrupt Request output pin (INT1 or INT2 - SMD jumper selected). */
    digital_in_t int_pin_in;        /**< Interrupt Request input pin (INT1 or INT2 - SMD jumper selected). */

    pin_name_t int_pin_name;        /**< Interrupt Request pin name (INT1 or INT2 - SMD jumper selected). */

    spi_master_t spi;               /**< SPI driver object. */
    pwm_t pwm;                      /**< PWM driver object. */

    uint32_t pwm_freq;              /**< PWM frequency value. */
    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */

} ultrasonic4_t;

/**
 * @brief Ultrasonic 4 Click configuration object.
 * @details Configuration object definition of Ultrasonic 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t pwm;                 /**< External Input/Output Low Frequency Reference Clock - 32.768 kHz typical (optional). */
    pin_name_t int_pin;             /**< Interrupt Request pin (INT1 or INT2 - SMD jumper selected). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    uint32_t dev_pwm_freq;          /**< PWM frequency value. */

} ultrasonic4_cfg_t;

/**
 * @brief Ultrasonic 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ULTRASONIC4_OK = 0,
    ULTRASONIC4_ERROR = -1

} ultrasonic4_return_value_t;

/*!
 * @addtogroup ultrasonic4 Ultrasonic 4 Click Driver
 * @brief API for configuring and manipulating Ultrasonic 4 Click driver.
 * @{
 */

/**
 * @brief Ultrasonic 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ultrasonic4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ultrasonic4_cfg_setup ( ultrasonic4_cfg_t *cfg );

/**
 * @brief Ultrasonic 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ultrasonic4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ultrasonic4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic4_init ( ultrasonic4_t *ctx, ultrasonic4_cfg_t *cfg );

/**
 * @brief Ultrasonic 4 default configuration function.
 * @details This function executes a default configuration of Ultrasonic 4 Click board.
 * @param[in] ctx : Click context object.
 * See #ultrasonic4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ultrasonic4_default_cfg ( ultrasonic4_t *ctx );

/**
 * @brief Ultrasonic 4 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #ultrasonic4_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic4_set_duty_cycle ( ultrasonic4_t *ctx, float duty_cycle );

/**
 * @brief Ultrasonic 4 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #ultrasonic4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic4_pwm_stop ( ultrasonic4_t *ctx );

/**
 * @brief Ultrasonic 4 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #ultrasonic4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ultrasonic4_pwm_start ( ultrasonic4_t *ctx );

/**
 * @brief Ultrasonic 4 get measurements function.
 * @details This function triggers and reads the measurements and logs data.
 * @return None.
 * @note None.
 */
void ultrasonic4_get_measurements ( void );

#ifdef __cplusplus
}
#endif
#endif // ULTRASONIC4_H

/*! @} */ // ultrasonic4

// ------------------------------------------------------------------------ END
