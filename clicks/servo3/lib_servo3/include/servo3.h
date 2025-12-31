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
 * @file servo3.h
 * @brief This file contains API for Servo 3 Click Driver.
 */

#ifndef SERVO3_H
#define SERVO3_H

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
 * @addtogroup servo3 Servo 3 Click Driver
 * @brief API for configuring and manipulating Servo 3 Click driver.
 * @{
 */

/**
 * @defgroup servo3_cfg Servo 3 PWM Settings
 * @brief Settings for configuration of Servo 3 Click driver.
 */

/**
 * @addtogroup servo3_cfg
 * @{
 */

/**
 * @brief Servo 3 PWM output setting.
 * @details Specified setting for PWM output values (0-4095) for 0.5ms and 2.5ms servo pulses of Servo 3 Click driver.
 * @note 
 * Measure the PWM output values that matches below settings using an oscilloscope or logic analyzer and adjust
 * SERVO3_PWM_ZERO_DEGREE_PULSE and SERVO3_PWM_180_DEGREE_PULSE macros.
 * DC -> 2.5% (at 50Hz frequency) for minimum position (0 degrees).
 * DC -> 12.5% (at 50Hz frequency) for maximum position (180 degrees).
 */
#define SERVO3_PWM_MAX                          4095
#define SERVO3_PWM_MIN                          0
#define SERVO3_PWM_ZERO_DEGREE_PULSE            3969
#define SERVO3_PWM_180_DEGREE_PULSE             3461

/**
 * @brief Servo 3 function and brightness control.
 * @details Specified function and brightness control of Servo 3 Click driver.
 */
#define SERVO3_FC_PS_MODE_DISABLED              0x000000ul
#define SERVO3_FC_PS_MODE_ENABLED               0x038000ul
#define SERVO3_FC_PS_MODE_MASK                  0x038000ul
#define SERVO3_FC_OLDENA_DISABLED               0x000000ul
#define SERVO3_FC_OLDENA_ENABLED                0x004000ul
#define SERVO3_FC_OLDENA_MASK                   0x004000ul
#define SERVO3_FC_IDMCUR_2_UA                   0x000000ul
#define SERVO3_FC_IDMCUR_10_UA                  0x001000ul
#define SERVO3_FC_IDMCUR_20_UA                  0x002000ul
#define SERVO3_FC_IDMCUR_1_MA                   0x003000ul
#define SERVO3_FC_IDMCUR_MASK                   0x003000ul
#define SERVO3_FC_IDMRPT_NOT_REPEATED           0x000000ul
#define SERVO3_FC_IDMRPT_REPEATED               0x000800ul
#define SERVO3_FC_IDMRPT_MASK                   0x000800ul
#define SERVO3_FC_IDMENA_DISABLED               0x000000ul
#define SERVO3_FC_IDMENA_ENABLED                0x000400ul
#define SERVO3_FC_IDMENA_MASK                   0x000400ul
#define SERVO3_FC_LATTMG_17TH                   0x000000ul
#define SERVO3_FC_LATTMG_33TH                   0x000100ul
#define SERVO3_FC_LATTMG_65TH                   0x000200ul
#define SERVO3_FC_LATTMG_129TH                  0x000300ul
#define SERVO3_FC_LATTMG_MASK                   0x000300ul
#define SERVO3_FC_LSDVLT_35PCT_VCC              0x000000ul
#define SERVO3_FC_LSDVLT_45PCT_VCC              0x000040ul
#define SERVO3_FC_LSDVLT_55PCT_VCC              0x000080ul
#define SERVO3_FC_LSDVLT_65PCT_VCC              0x0000C0ul
#define SERVO3_FC_LSDVLT_MASK                   0x0000C0ul
#define SERVO3_FC_LODVLT_0_3_V                  0x000000ul
#define SERVO3_FC_LODVLT_0_6_V                  0x000010ul
#define SERVO3_FC_LODVLT_0_9_V                  0x000020ul
#define SERVO3_FC_LODVLT_1_2_V                  0x000030ul
#define SERVO3_FC_LODVLT_MASK                   0x000030ul
#define SERVO3_FC_ESPWM_DISABLED                0x000000ul
#define SERVO3_FC_ESPWM_ENABLED                 0x000008ul
#define SERVO3_FC_ESPWM_MASK                    0x000008ul
#define SERVO3_FC_TMGRST_DISABLED               0x000000ul
#define SERVO3_FC_TMGRST_ENABLED                0x000004ul
#define SERVO3_FC_TMGRST_MASK                   0x000004ul
#define SERVO3_FC_DSPRPT_DISABLED               0x000000ul
#define SERVO3_FC_DSPRPT_ENABLED                0x000002ul
#define SERVO3_FC_DSPRPT_MASK                   0x000002ul
#define SERVO3_FC_BLANK_ON                      0x000000ul
#define SERVO3_FC_BLANK_OFF                     0x000001ul
#define SERVO3_FC_BLANK_MASK                    0x000001ul
#define SERVO3_BC_MIN                           0x00
#define SERVO3_BC_MAX                           0x7F
#define SERVO3_BC_MASK                          0x7F

/**
 * @brief Servo 3 angle and channel setting.
 * @details Specified setting for servo angle and channel of Servo 3 Click driver.
 */
#define SERVO3_ANGLE_MIN                        0
#define SERVO3_ANGLE_MAX                        180
#define SERVO3_CHANNEL_0                        0
#define SERVO3_CHANNEL_1                        1
#define SERVO3_CHANNEL_2                        2
#define SERVO3_CHANNEL_3                        3
#define SERVO3_CHANNEL_4                        4
#define SERVO3_CHANNEL_5                        5
#define SERVO3_CHANNEL_6                        6
#define SERVO3_CHANNEL_7                        7
#define SERVO3_CHANNEL_8                        8
#define SERVO3_CHANNEL_9                        9
#define SERVO3_CHANNEL_10                       10
#define SERVO3_CHANNEL_11                       11
#define SERVO3_CHANNEL_12                       12
#define SERVO3_CHANNEL_13                       13
#define SERVO3_CHANNEL_14                       14
#define SERVO3_CHANNEL_15                       15
#define SERVO3_CHANNEL_ALL                      16
#define SERVO3_NUM_CHANNELS                     16

/**
 * @brief Servo 3 default PWM frequency.
 * @details Specified setting for default PWM frequency of Servo 3 Click driver.
 */
#define SERVO3_DEF_FREQ                         256000ul
#define SERVO3_DEF_DC                           0.5

/*! @} */ // servo3_cfg

/**
 * @defgroup servo3_map Servo 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Servo 3 Click driver.
 */

/**
 * @addtogroup servo3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Servo 3 Click to the selected MikroBUS.
 */
#define SERVO3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.sout = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.sin = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sclk = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.xlat = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.gsclk = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // servo3_map
/*! @} */ // servo3

/**
 * @brief Servo 3 Click context object.
 * @details Context object definition of Servo 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t xlat;         /**< XLAT pin (high pulse). */
    digital_out_t sclk;         /**< SCLK pin (active high). */
    digital_out_t sin;          /**< SIN pin (active high). */

    // Input pins
    digital_in_t sout;          /**< SOUT pin (active high). */

    // Modules
    pwm_t pwm;                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

    uint16_t pwm_out[ SERVO3_NUM_CHANNELS ];    /**< PWM data channels output. */

} servo3_t;

/**
 * @brief Servo 3 Click configuration object.
 * @details Configuration object definition of Servo 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t xlat;            /**< XLAT pin (high pulse). */
    pin_name_t sclk;            /**< SCLK pin (active high). */
    pin_name_t sin;             /**< SIN pin (active high). */
    pin_name_t sout;            /**< SOUT pin (active high). */
    pin_name_t gsclk;           /**< Grayscale clock pin. */

    // Static variable
    uint32_t dev_pwm_freq;      /**< PWM frequency value. */

} servo3_cfg_t;

/**
 * @brief Servo 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SERVO3_OK = 0,
    SERVO3_ERROR = -1

} servo3_return_value_t;

/*!
 * @addtogroup servo3 Servo 3 Click Driver
 * @brief API for configuring and manipulating Servo 3 Click driver.
 * @{
 */

/**
 * @brief Servo 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #servo3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void servo3_cfg_setup ( servo3_cfg_t *cfg );

/**
 * @brief Servo 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #servo3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t servo3_init ( servo3_t *ctx, servo3_cfg_t *cfg );

/**
 * @brief Servo 3 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t servo3_set_duty_cycle ( servo3_t *ctx, float duty_cycle );

/**
 * @brief Servo 3 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t servo3_pwm_stop ( servo3_t *ctx );

/**
 * @brief Servo 3 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t servo3_pwm_start ( servo3_t *ctx );

/**
 * @brief Servo 3 write control function.
 * @details This function writes control data to the device via the serial interface, updates the internal registers, 
 * and starts the PWM to clock out control data.
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @param[in] fc_data : 18-bits function control data.
 * @param[in] bc_data : 7-bits brightness control data.
 * @return None.
 * @note None.
 */
void servo3_write_control ( servo3_t *ctx, uint32_t fc_data, uint8_t bc_data );

/**
 * @brief Servo 3 write data function.
 * @details This function writes data to the device via the serial interface, updates the internal registers, 
 * and starts the PWM to clock out grayscale data.
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @param[in] data_in : Pointer to the data to write.
 * @param[in] len : Number of bytes to write.
 * @return None.
 * @note None.
 */
void servo3_write_data ( servo3_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief Servo 3 set SCLK pin function.
 * @details This function sets the SCLK (serial clock) pin to the specified logic state.
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void servo3_set_sclk_pin ( servo3_t *ctx, uint8_t state );

/**
 * @brief Servo 3 set SIN pin function.
 * @details This function sets the SIN (serial input) pin to the specified logic state.
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void servo3_set_sin_pin ( servo3_t *ctx, uint8_t state );

/**
 * @brief Servo 3 set XLAT pin function.
 * @details This function sets the XLAT (latch) pin to the specified logic state.
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void servo3_set_xlat_pin ( servo3_t *ctx, uint8_t state );

/**
 * @brief Servo 3 get SOUT pin state function.
 * @details This function returns the logic state of the SOUT (serial output) pin.
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t servo3_get_sout_pin ( servo3_t *ctx );

/**
 * @brief Servo 3 set channel PWM function.
 * @details This function sets the PWM output for a specific channel or all channels.
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @param[in] ch_num : Channel number (0-15 or all channels).
 * @param[in] pwm_out : PWM output value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t servo3_set_channel_pwm ( servo3_t *ctx, uint8_t ch_num, uint16_t pwm_out );

/**
 * @brief Servo 3 set angle function.
 * @details This function sets the servo angle for a specific channel or all channels.
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @param[in] ch_num : Channel number (0-15 or all channels).
 * @param[in] angle : Servo angle in degrees (0-180).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t servo3_set_angle ( servo3_t *ctx, uint8_t ch_num, uint8_t angle );

/**
 * @brief Servo 3 update output function.
 * @details This function updates the PWM output values for all channels by writing them to the device.
 * @param[in] ctx : Click context object.
 * See #servo3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void servo3_update_output ( servo3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SERVO3_H

/*! @} */ // servo3

// ------------------------------------------------------------------------ END
