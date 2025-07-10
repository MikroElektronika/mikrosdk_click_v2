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
 * @file servo2.h
 * @brief This file contains API for Servo 2 Click Driver.
 */

#ifndef SERVO2_H
#define SERVO2_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup servo2 Servo 2 Click Driver
 * @brief API for configuring and manipulating Servo 2 Click driver.
 * @{
 */

/**
 * @defgroup servo2_cfg Servo 2 PWM Settings
 * @brief Settings for configuration of Servo 2 Click driver.
 */

/**
 * @addtogroup servo2_cfg
 * @{
 */

/**
 * @brief Servo 2 PWM output setting.
 * @details Specified setting for PWM output values (0-4095) for 0.5ms and 2.5ms servo pulses of Servo 2 Click driver.
 * @note 
 * Measure the PWM output values that matches below settings using an oscilloscope or logic analyzer and adjust
 * SERVO2_PWM_ZERO_DEGREE_PULSE and SERVO2_PWM_180_DEGREE_PULSE macros.
 * DC -> 2.5% (at 50Hz frequency) for minimum position (0 degrees).
 * DC -> 12.5% (at 50Hz frequency) for maximum position (180 degrees).
 */
#define SERVO2_PWM_MAX                          4095
#define SERVO2_PWM_MIN                          0
#define SERVO2_PWM_ZERO_DEGREE_PULSE            3980
#define SERVO2_PWM_180_DEGREE_PULSE             3468

/**
 * @brief Servo 2 angle and channel setting.
 * @details Specified setting for servo angle and channel of Servo 2 Click driver.
 */
#define SERVO2_ANGLE_MIN                        0
#define SERVO2_ANGLE_MAX                        180
#define SERVO2_CHANNEL_0                        0
#define SERVO2_CHANNEL_1                        1
#define SERVO2_CHANNEL_2                        2
#define SERVO2_CHANNEL_3                        3
#define SERVO2_CHANNEL_4                        4
#define SERVO2_CHANNEL_5                        5
#define SERVO2_CHANNEL_6                        6
#define SERVO2_CHANNEL_7                        7
#define SERVO2_CHANNEL_8                        8
#define SERVO2_CHANNEL_9                        9
#define SERVO2_CHANNEL_10                       10
#define SERVO2_CHANNEL_11                       11
#define SERVO2_CHANNEL_12                       12
#define SERVO2_CHANNEL_13                       13
#define SERVO2_CHANNEL_14                       14
#define SERVO2_CHANNEL_15                       15
#define SERVO2_CHANNEL_ALL                      16
#define SERVO2_NUM_CHANNELS                     16

/**
 * @brief Servo 2 default PWM frequency.
 * @details Specified setting for default PWM frequency of Servo 2 Click driver.
 */
#define SERVO2_DEF_FREQ                         256000ul
#define SERVO2_DEF_DC                           0.5

/*! @} */ // servo2_cfg

/**
 * @defgroup servo2_map Servo 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Servo 2 Click driver.
 */

/**
 * @addtogroup servo2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Servo 2 Click to the selected MikroBUS.
 */
#define SERVO2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.sout = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.sin = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sclk = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.xlat = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.blank = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.gsclk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.xerr = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // servo2_map
/*! @} */ // servo2

/**
 * @brief Servo 2 Click context object.
 * @details Context object definition of Servo 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t xlat;         /**< XLAT pin (high pulse). */
    digital_out_t blank;        /**< Blank outputs pin (active high). */
    digital_out_t sclk;         /**< SCLK pin (active high). */
    digital_out_t sin;          /**< SIN pin (active high). */

    // Input pins
    digital_in_t sout;          /**< SOUT pin (active high). */
    digital_in_t xerr;          /**< Error pin (active low). */

    // Modules
    pwm_t pwm;                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

    uint16_t pwm_out[ SERVO2_NUM_CHANNELS ];    /**< PWM data channels output. */

} servo2_t;

/**
 * @brief Servo 2 Click configuration object.
 * @details Configuration object definition of Servo 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t xlat;            /**< XLAT pin (high pulse). */
    pin_name_t sclk;            /**< SCLK pin (active high). */
    pin_name_t sin;             /**< SIN pin (active high). */
    pin_name_t sout;            /**< SOUT pin (active high). */
    pin_name_t gsclk;           /**< Grayscale clock pin. */

    // Additional gpio pins
    pin_name_t blank;           /**< Blank outputs pin (active high). */
    pin_name_t xerr;            /**< Error pin (active low). */

    // Static variable
    uint32_t dev_pwm_freq;      /**< PWM frequency value. */

} servo2_cfg_t;

/**
 * @brief Servo 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SERVO2_OK = 0,
    SERVO2_ERROR = -1

} servo2_return_value_t;

/*!
 * @addtogroup servo2 Servo 2 Click Driver
 * @brief API for configuring and manipulating Servo 2 Click driver.
 * @{
 */

/**
 * @brief Servo 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #servo2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void servo2_cfg_setup ( servo2_cfg_t *cfg );

/**
 * @brief Servo 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #servo2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t servo2_init ( servo2_t *ctx, servo2_cfg_t *cfg );

/**
 * @brief Servo 2 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t servo2_set_duty_cycle ( servo2_t *ctx, float duty_cycle );

/**
 * @brief Servo 2 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t servo2_pwm_stop ( servo2_t *ctx );

/**
 * @brief Servo 2 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t servo2_pwm_start ( servo2_t *ctx );

/**
 * @brief Servo 2 write data function.
 * @details This function writes data to the device via the serial interface, updates the internal registers, 
 * and starts the PWM for grayscale data output.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @param[in] data_in : Pointer to the data to write.
 * @param[in] len : Number of bytes to write.
 * @return None.
 */
void servo2_write_data ( servo2_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief Servo 2 set SCLK pin function.
 * @details This function sets the SCLK (serial clock) pin to the specified logic state.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 */
void servo2_set_sclk_pin ( servo2_t *ctx, uint8_t state );

/**
 * @brief Servo 2 set SIN pin function.
 * @details This function sets the SIN (serial input) pin to the specified logic state.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 */
void servo2_set_sin_pin ( servo2_t *ctx, uint8_t state );

/**
 * @brief Servo 2 set XLAT pin function.
 * @details This function sets the XLAT (latch) pin to the specified logic state.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 */
void servo2_set_xlat_pin ( servo2_t *ctx, uint8_t state );

/**
 * @brief Servo 2 set BLANK pin function.
 * @details This function sets the BLANK pin to the specified logic state.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 */
void servo2_set_blank_pin ( servo2_t *ctx, uint8_t state );

/**
 * @brief Servo 2 get SOUT pin state function.
 * @details This function returns the logic state of the SOUT (serial output) pin.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @return Pin logic state.
 */
uint8_t servo2_get_sout_pin ( servo2_t *ctx );

/**
 * @brief Servo 2 get XERR pin state function.
 * @details This function returns the logic state of the XERR (error) pin.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @return Pin logic state.
 */
uint8_t servo2_get_xerr_pin ( servo2_t *ctx );

/**
 * @brief Servo 2 set channel PWM function.
 * @details This function sets the PWM output for a specific channel or all channels.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @param[in] ch_num : Channel number (0-15 or all channels).
 * @param[in] pwm_out : PWM output value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t servo2_set_channel_pwm ( servo2_t *ctx, uint8_t ch_num, uint16_t pwm_out );

/**
 * @brief Servo 2 set angle function.
 * @details This function sets the servo angle for a specific channel or all channels.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @param[in] ch_num : Channel number (0-15 or all channels).
 * @param[in] angle : Servo angle in degrees (0-180).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t servo2_set_angle ( servo2_t *ctx, uint8_t ch_num, uint8_t angle );

/**
 * @brief Servo 2 update output function.
 * @details This function updates the PWM output values for all channels by writing them to the device.
 * @param[in] ctx : Click context object.
 * See #servo2_t object definition for detailed explanation.
 * @return None.
 */
void servo2_update_output ( servo2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SERVO2_H

/*! @} */ // servo2

// ------------------------------------------------------------------------ END
