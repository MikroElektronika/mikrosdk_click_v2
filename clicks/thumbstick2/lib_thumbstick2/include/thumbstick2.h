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
 * @file thumbstick2.h
 * @brief This file contains API for Thumbstick 2 Click Driver.
 */

#ifndef THUMBSTICK2_H
#define THUMBSTICK2_H

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
 * @addtogroup thumbstick2 Thumbstick 2 Click Driver
 * @brief API for configuring and manipulating Thumbstick 2 Click driver.
 * @{
 */

/**
 * @defgroup thumbstick2_set Thumbstick 2 Settings
 * @brief Settings of Thumbstick 2 Click driver.
 */

/**
 * @addtogroup thumbstick2_set
 * @{
 */

/**
 * @brief Thumbstick 2 ADC calculation values.
 * @details Specified ADC calculation values of Thumbstick 2 Click driver.
 */
#define THUMBSTICK2_ADC_START_BIT               0x01
#define THUMBSTICK2_ADC_SINGLE_ENDED            0x80
#define THUMBSTICK2_ADC_CHANNEL_X               0x00
#define THUMBSTICK2_ADC_CHANNEL_Y               0x40
#define THUMBSTICK2_ADC_DATA_RESOLUTION         0x0FFF
#define THUMBSTICK2_ADC_DATA_RESOLUTION_HALF    ( ( float ) THUMBSTICK2_ADC_DATA_RESOLUTION / 2 )

/**
 * @brief Thumbstick 2 angle and position calculation values.
 * @details Specified angle and position calculation values of Thumbstick 2 Click driver.
 */
#define THUMBSTICK2_RADIANS_TO_DEGREES          57.295779513
#define THUMBSTICK2_ANGLE_ZERO_OFFSET           180.0
#define THUMBSTICK2_PI_RAD_OFFSET               1.0
#define THUMBSTICK2_NEUTRAL_POSITION_OFFSET     ( ( float ) THUMBSTICK2_ADC_DATA_RESOLUTION / 8 )
#define THUMBSTICK2_FULL_ANGLE                  360.0f
#define THUMBSTICK2_ZERO_ANGLE                  0.0f
#define THUMBSTICK2_ANGLE_POSITION_STEP         45.0f

/**
 * @brief Thumbstick 2 position values.
 * @details Specified position values of Thumbstick 2 Click driver.
 */
#define THUMBSTICK2_POSITION_NEUTRAL            0
#define THUMBSTICK2_POSITION_UP                 1
#define THUMBSTICK2_POSITION_UPPER_LEFT         2
#define THUMBSTICK2_POSITION_LEFT               3
#define THUMBSTICK2_POSITION_LOWER_LEFT         4
#define THUMBSTICK2_POSITION_DOWN               5
#define THUMBSTICK2_POSITION_LOWER_RIGHT        6
#define THUMBSTICK2_POSITION_RIGHT              7
#define THUMBSTICK2_POSITION_UPPER_RIGHT        8

/**
 * @brief Thumbstick 2 default PWM frequency.
 * @details Specified setting for default PWM frequency of Thumbstick 2 Click driver.
 */
#define THUMBSTICK2_PWM_DEF_FREQ                20000
#define THUMBSTICK2_PWM_MIN_DUTY                0.0
#define THUMBSTICK2_PWM_MAX_DUTY                1.0

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b thumbstick2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define THUMBSTICK2_SET_DATA_SAMPLE_EDGE        SET_SPI_DATA_SAMPLE_EDGE
#define THUMBSTICK2_SET_DATA_SAMPLE_MIDDLE      SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // thumbstick2_set

/**
 * @defgroup thumbstick2_map Thumbstick 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Thumbstick 2 Click driver.
 */

/**
 * @addtogroup thumbstick2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thumbstick 2 Click to the selected MikroBUS.
 */
#define THUMBSTICK2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.vb = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.sw = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thumbstick2_map
/*! @} */ // thumbstick2

/**
 * @brief Thumbstick 2 Click context object.
 * @details Context object definition of Thumbstick 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t vb;               /**< Vibro motor PWM pin. */

    // Input pins
    digital_in_t sw;                /**< Thumbstick button pin. */

    // Modules
    pwm_t pwm;                      /**< PWM driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */
    uint32_t pwm_freq;              /**< PWM frequency value. */

} thumbstick2_t;

/**
 * @brief Thumbstick 2 Click configuration object.
 * @details Configuration object definition of Thumbstick 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t vb;                  /**< Vibro motor PWM pin. */

    // Additional gpio pins
    pin_name_t sw;                  /**< Thumbstick button pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    uint32_t dev_pwm_freq;          /**< PWM frequency value. */

} thumbstick2_cfg_t;

/**
 * @brief Thumbstick 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THUMBSTICK2_OK = 0,
    THUMBSTICK2_ERROR = -1

} thumbstick2_return_value_t;

/*!
 * @addtogroup thumbstick2 Thumbstick 2 Click Driver
 * @brief API for configuring and manipulating Thumbstick 2 Click driver.
 * @{
 */

/**
 * @brief Thumbstick 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thumbstick2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thumbstick2_cfg_setup ( thumbstick2_cfg_t *cfg );

/**
 * @brief Thumbstick 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thumbstick2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thumbstick2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thumbstick2_init ( thumbstick2_t *ctx, thumbstick2_cfg_t *cfg );

/**
 * @brief Thumbstick 2 read raw adc function.
 * @details This function reads the raw ADC for X and Y axis by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #thumbstick2_t object definition for detailed explanation.
 * @param[out] raw_x : RAW X axis data (0-4095).
 * @param[out] raw_y : RAW Y axis data (0-4095).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thumbstick2_read_raw_adc ( thumbstick2_t *ctx, uint16_t *raw_x, uint16_t *raw_y );

/**
 * @brief Thumbstick 2 get angle function.
 * @details This function calculates and returns joystick angle in degrees from raw ADC values for X and Y axis.
 * @param[in] raw_x : RAW X axis data (0-4095).
 * @param[in] raw_y : RAW Y axis data (0-4095).
 * @return Joystick angle in degrees.
 * @note None.
 */
float thumbstick2_get_angle ( uint16_t raw_x, uint16_t raw_y );

/**
 * @brief Thumbstick 2 get position function.
 * @details This function calculates and returns joystick position flag from raw ADC values for X and Y axis.
 * @param[in] raw_x : RAW X axis data (0-4095).
 * @param[in] raw_y : RAW Y axis data (0-4095).
 * @return Joystick position flag. Refer to the position values macro definitions.
 * @note None.
 */
uint8_t thumbstick2_get_position ( uint16_t raw_x, uint16_t raw_y );

/**
 * @brief Thumbstick 2 set duty cycle function.
 * @details This function sets the PWM duty cycle.
 * @param[in] ctx : Click context object.
 * See #thumbstick2_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle value (0.0 to 1.0).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t thumbstick2_set_duty_cycle ( thumbstick2_t *ctx, float duty_cycle );

/**
 * @brief Thumbstick 2 stop PWM function.
 * @details This function stops the PWM output.
 * @param[in] ctx : Click context object.
 * See #thumbstick2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t thumbstick2_pwm_stop ( thumbstick2_t *ctx );

/**
 * @brief Thumbstick 2 start PWM function.
 * @details This function starts the PWM output.
 * @param[in] ctx : Click context object.
 * See #thumbstick2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t thumbstick2_pwm_start ( thumbstick2_t *ctx );

/**
 * @brief Thumbstick 2 get SW pin function.
 * @details This function returns the SW pin logic state.
 * @param[in] ctx : Click context object.
 * See #thumbstick2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thumbstick2_get_sw_pin ( thumbstick2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // THUMBSTICK2_H

/*! @} */ // thumbstick2

// ------------------------------------------------------------------------ END
