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
 * @file vibromotor4.h
 * @brief This file contains API for Vibro Motor 4 Click Driver.
 */

#ifndef VIBROMOTOR4_H
#define VIBROMOTOR4_H

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
#include "drv_i2c_master.h"
#include "drv_pwm.h"

/*!
 * @addtogroup vibromotor4 Vibro Motor 4 Click Driver
 * @brief API for configuring and manipulating Vibro Motor 4 Click driver.
 * @{
 */

/**
 * @defgroup vibromotor4_reg Vibro Motor 4 Registers List
 * @brief List of registers of Vibro Motor 4 Click driver.
 */

/**
 * @addtogroup vibromotor4_reg
 * @{
 */

/**
 * @brief Vibro Motor 4 description register.
 * @details Specified register for description of Vibro Motor 4 Click driver.
 */
#define VIBROMOTOR4_STATUS                                      0x00
#define VIBROMOTOR4_MODE                                        0x01
#define VIBROMOTOR4_RT_PB_IN                                    0x02
#define VIBROMOTOR4_LIB_SEL                                     0x03
#define VIBROMOTOR4_WV_SEQ_1                                    0x04
#define VIBROMOTOR4_WV_SEQ_2                                    0x05
#define VIBROMOTOR4_WV_SEQ_3                                    0x06
#define VIBROMOTOR4_WV_SEQ_4                                    0x07
#define VIBROMOTOR4_WV_SEQ_5                                    0x08
#define VIBROMOTOR4_WV_SEQ_6                                    0x09
#define VIBROMOTOR4_WV_SEQ_7                                    0x0A
#define VIBROMOTOR4_WV_SEQ_8                                    0x0B
#define VIBROMOTOR4_REG_GO                                      0x0C
#define VIBROMOTOR4_OVERDRIVE_OFFS                              0x0D
#define VIBROMOTOR4_SUSTAIN_P_OFFS                              0x0E
#define VIBROMOTOR4_SUSTAIN_N_OFFS                              0x0F
#define VIBROMOTOR4_BRAKE_OFF                                   0x10
#define VIBROMOTOR4_A_TO_V_CTRL                                 0x11
#define VIBROMOTOR4_A_TO_V_MIN_INPUT                            0x12
#define VIBROMOTOR4_A_TO_V_MAX_INPUT                            0x13
#define VIBROMOTOR4_A_TO_V_MIN_OUT                              0x14
#define VIBROMOTOR4_A_TO_V_MAX_OUT                              0x15
#define VIBROMOTOR4_RATED_VOLT                                  0x16
#define VIBROMOTOR4_OD_CLAMP_VOLT                               0x17
#define VIBROMOTOR4_CAL_COMP                                    0x18
#define VIBROMOTOR4_CAL_BACK_EMF                                0x19
#define VIBROMOTOR4_FEEDBACK_CTRL                               0x1A
#define VIBROMOTOR4_CTRL1                                       0x1B
#define VIBROMOTOR4_CTRL2                                       0x1C
#define VIBROMOTOR4_CTRL3                                       0x1D
#define VIBROMOTOR4_CTRL4                                       0x1E
#define VIBROMOTOR4_CTRL5                                       0x1F
#define VIBROMOTOR4_LRA_LOOP_PERIOD                             0x20
#define VIBROMOTOR4_VBAT_MON                                    0x21
#define VIBROMOTOR4_LRA_RES_PERIOD                              0x22

/*! @} */ // vibromotor4_reg

/**
 * @defgroup vibromotor4_set Vibro Motor 4 Registers Settings
 * @brief Settings for registers of Vibro Motor 4 Click driver.
 */

/**
 * @addtogroup vibromotor4_set
 * @{
 */

/**
 * @brief Vibro Motor 4 description setting.
 * @details Specified setting for description of Vibro Motor 4 Click driver.
 */
#define VIBROMOTOR4_STARTPPBOOST                                0x80
#define VIBROMOTOR4_BYPASSCOMP                                  0x40
#define VIBROMOTOR4_AC_COUPLE                                   0x20
#define VIBROMOTOR4_DC_COUPLE                                   0x00
#define VIBROMOTOR4_DRV_TIME_0P5M                               0x00
#define VIBROMOTOR4_DRV_TIME_0P6M                               0x01
#define VIBROMOTOR4_DRV_TIME_0P7M                               0x02
#define VIBROMOTOR4_DRV_TIME_0P8M                               0x03
#define VIBROMOTOR4_DRV_TIME_0P9M                               0x04
#define VIBROMOTOR4_DRV_TIME_1P0M                               0x05
#define VIBROMOTOR4_DRV_TIME_1P1M                               0x06
#define VIBROMOTOR4_DRV_TIME_1P2M                               0x07
#define VIBROMOTOR4_DRV_TIME_1P3M                               0x08
#define VIBROMOTOR4_DRV_TIME_1P4M                               0x09
#define VIBROMOTOR4_DRV_TIME_1P5M                               0x0A
#define VIBROMOTOR4_DRV_TIME_1P6M                               0x0B
#define VIBROMOTOR4_DRV_TIME_1P7M                               0x0C
#define VIBROMOTOR4_DRV_TIME_1P8M                               0x0D
#define VIBROMOTOR4_DRV_TIME_1P9M                               0x0E
#define VIBROMOTOR4_DRV_TIME_2P0M                               0x0F
#define VIBROMOTOR4_DRV_TIME_2P1M                               0x10
#define VIBROMOTOR4_DRV_TIME_2P2M                               0x11
#define VIBROMOTOR4_DRV_TIME_2P3M                               0x12
#define VIBROMOTOR4_DRV_TIME_2P4M                               0x13
#define VIBROMOTOR4_DRV_TIME_2P5M                               0x14
#define VIBROMOTOR4_DRV_TIME_2P6M                               0x15
#define VIBROMOTOR4_DRV_TIME_2P7M                               0x16
#define VIBROMOTOR4_DRV_TIME_2P8M                               0x17
#define VIBROMOTOR4_DRV_TIME_2P9M                               0x18
#define VIBROMOTOR4_DRV_TIME_3P0M                               0x19
#define VIBROMOTOR4_DRV_TIME_3P1M                               0x1A
#define VIBROMOTOR4_DRV_TIME_3P2M                               0x1B
#define VIBROMOTOR4_DRV_TIME_3P3M                               0x1C
#define VIBROMOTOR4_DRV_TIME_3P4M                               0x1D
#define VIBROMOTOR4_DRV_TIME_3P5M                               0x1E
#define VIBROMOTOR4_DRV_TIME_3P6M                               0x1F
#define VIBROMOTOR4_BIDIR_IN                                    0x80
#define VIBROMOTOR4_UNIDIR_IN                                   0x00
#define VIBROMOTOR4_BRK_STABIL                                  0x40
#define VIBROMOTOR4_SAMP_TIME_150US                             0x00
#define VIBROMOTOR4_SAMP_TIME_200US                             0x10
#define VIBROMOTOR4_SAMP_TIME_250US                             0x20
#define VIBROMOTOR4_SAMP_TIME_300US                             0x30
#define VIBROMOTOR4_BLANK_TIME_V_SHORT                          0x00
#define VIBROMOTOR4_BLANK_TIME_SHORT                            0x04
#define VIBROMOTOR4_BLANK_TIME_MEDIUM                           0x08
#define VIBROMOTOR4_BLANK_TIME_LONG                             0x0C
#define VIBROMOTOR4_I_DIS_TIME_V_SHORT                          0x00
#define VIBROMOTOR4_I_DIS_TIME_SHORT                            0x01
#define VIBROMOTOR4_I_DIS_TIME_MEDIUM                           0x02
#define VIBROMOTOR4_I_DIS_TIME_LONG                             0x03
#define VIBROMOTOR4_NG_THRESH_OFF                               0x00
#define VIBROMOTOR4_NG_THRESH_2_PERC                            0x40
#define VIBROMOTOR4_NG_THRESH_4_PERC                            0x80
#define VIBROMOTOR4_NG_THRESH_8_PERC                            0xC0
#define VIBROMOTOR4_ERM_CLOSED_LOOP                             0x00
#define VIBROMOTOR4_ERM_OPEN_LOOP                               0x20
#define VIBROMOTOR4_SUP_COMP_DIS                                0x10
#define VIBROMOTOR4_DATA_FORM_RTP_SIG                           0x00
#define VIBROMOTOR4_DATA_FORM_RTP_UNS                           0x08
#define VIBROMOTOR4_LRADRV_MODE                                 0x04
#define VIBROMOTOR4_LRADRV_MODE_ONCE                            0x00
#define VIBROMOTOR4_LRADRV_MODE_TWICE                           0x04
#define VIBROMOTOR4_IN_MODE_PWM                                 0x00
#define VIBROMOTOR4_IN_MODE_ANALOG                              0x02
#define VIBROMOTOR4_LRA_AUTO_RESONA                             0x00
#define VIBROMOTOR4_LRA_OPEN_LOOP                               0x01
#define VIBROMOTOR4_LRA_CLOSED_LOOP                             0x00

/**
 * @brief Vibro Motor 4 Mode register bits.
 * @details Mode register bits of Vibro Motor 4 Click driver.
 */
#define VIBROMOTOR4_DEV_RESRT                                   0x80
#define VIBROMOTOR4_STANDBY                                     0x40
#define VIBROMOTOR4_ACTIVE                                      0x00
#define VIBROMOTOR4_INT_TRIG                                    0x00
#define VIBROMOTOR4_EXT_TRIG_EDGE                               0x01
#define VIBROMOTOR4_EXT_TRIG_LEVEL                              0x02
#define VIBROMOTOR4_PWM_ANALOG                                  0x03
#define VIBROMOTOR4_AUDIO2HAPTIC                                0x04
#define VIBROMOTOR4_RTP                                         0x05
#define VIBROMOTOR4_DIAGNOSTICS                                 0x06
#define VIBROMOTOR4_AUTO_CALIBRATION                            0x07

/**
 * @brief Vibro Motor 4 Library selection register bits.
 * @details Specified library selection register bits of Vibro Motor 4 Click driver.
 */
#define VIBROMOTOR4_HIZ                                         0x10
#define VIBROMOTOR4_RAM                                         0x00
#define VIBROMOTOR4_ROM_A                                       0x01
#define VIBROMOTOR4_ROM_B                                       0x02
#define VIBROMOTOR4_ROM_C                                       0x03
#define VIBROMOTOR4_ROM_D                                       0x04
#define VIBROMOTOR4_ROM_E                                       0x05
#define VIBROMOTOR4_ROM_LRA                                     0x06

/**
 * @brief Vibro Motor 4 GO register bits.
 * @details GO register bits of Vibro Motor 4 Click driver.
 */
#define VIBROMOTOR4_STOP                                        0x00
#define VIBROMOTOR4_GO                                          0x01

/**
 * @brief Vibro Motor 4 Feedback control register bits.
 * @details Feedback control register bits of Vibro Motor 4 Click driver.
 */
#define VIBROMOTOR4_ERM_MODE                                    0x00
#define VIBROMOTOR4_LRA_MODE                                    0x80
#define VIBROMOTOR4_FB_BRAKE_FAC_1X                             0x00
#define VIBROMOTOR4_FB_BRAKE_FAC_2X                             0x10
#define VIBROMOTOR4_FB_BRAKE_FAC_3X                             0x20
#define VIBROMOTOR4_FB_BRAKE_FAC_4X                             0x30
#define VIBROMOTOR4_FB_BRAKE_FAC_6X                             0x40
#define VIBROMOTOR4_FB_BRAKE_FAC_8X                             0x50
#define VIBROMOTOR4_FB_BRAKE_FAC_16X                            0x60
#define VIBROMOTOR4_FB_BRAKE_FAC_DIS                            0x70
#define VIBROMOTOR4_LOOP_RESP_SLOW                              0x00
#define VIBROMOTOR4_LOOP_RESP_MEDIUM                            0x04
#define VIBROMOTOR4_LOOP_RESP_FAST                              0x08
#define VIBROMOTOR4_LOOP_RESP_V_FAST                            0x0C
#define VIBROMOTOR4_BEMF_GAIN_ERM_0P3X                          0x00
#define VIBROMOTOR4_BEMF_GAIN_ERM_1X                            0x01
#define VIBROMOTOR4_BEMF_GAIN_ERM_1P8X                          0x02
#define VIBROMOTOR4_BEMF_GAIN_ERM_4X                            0x03
#define VIBROMOTOR4_BEMF_GAIN_LRA_5X                            0x00
#define VIBROMOTOR4_BEMF_GAIN_LRA_10X                           0x01
#define VIBROMOTOR4_BEMF_GAIN_LRA_20X                           0x02
#define VIBROMOTOR4_BEMF_GAIN_LRA_30X                           0x03

/**
 * @brief Vibro Motor 4 Auto calibration memory interface register.
 * @details Auto calibration memory interface register of Vibro Motor 4 Click driver.
 */
#define VIBROMOTOR4_AUTO_CAL_TIME_150ms                         0x00
#define VIBROMOTOR4_AUTO_CAL_TIME_250ms                         0x10
#define VIBROMOTOR4_AUTO_CAL_TIME_500ms                         0x20
#define VIBROMOTOR4_AUTO_CAL_TIME_1000ms                        0x30
#define VIBROMOTOR4_OTP_PROG                                    0x01

/**
 * @brief Vibro Motor 4 device address setting.
 * @details Specified setting for device slave address selection of
 * Vibro Motor 4 Click driver.
 */
#define VIBROMOTOR4_SET_DEV_ADDR  0x5A

/**
 * @brief Vibro Motor 4 default PWM frequency.
 * @details Specified setting for setting default PWM frequency
 * of Vibro Motor 4 Click driver.
 */
#define VIBROMOTOR4_DEFAULT_FREQUENCY                           175

/*! @} */ // vibromotor4_set

/**
 * @defgroup vibromotor4_map Vibro Motor 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Vibro Motor 4 Click driver.
 */

/**
 * @addtogroup vibromotor4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Vibro Motor 4 Click to the selected MikroBUS.
 */
#define VIBROMOTOR4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // vibromotor4_map
/*! @} */ // vibromotor4

/**
 * @brief Vibro Motor 4 Click context object.
 * @details Context object definition of Vibro Motor 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en;       /**< Enable pin. */

    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

    pwm_t  pwm;              /**< PWM driver object. */
    uint32_t pwm_freq;       /**< PWM frequency value. */

} vibromotor4_t;

/**
 * @brief Vibro Motor 4 Click configuration object.
 * @details Configuration object definition of Vibro Motor 4 Click driver.
 */
typedef struct
{
    pin_name_t  scl;       /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;       /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;        /**< Enable pin. */

    uint32_t  i2c_speed;   /**< I2C serial speed. */
    uint8_t   i2c_address; /**< I2C slave address. */

    pin_name_t  pwm;       /**< PWM driver object. */
    uint32_t dev_pwm_freq; /**< PWM frequency value. */

} vibromotor4_cfg_t;

/**
 * @brief Vibro Motor 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   VIBROMOTOR4_OK = 0,
   VIBROMOTOR4_ERROR = -1

} vibromotor4_return_value_t;

/**
 * @brief Vibro Motor 4 Click property data.
 * @details Predefined enum values for driver property values.
 */
typedef enum
{
   VIBROMOTOR4_PROPERTY_DISABLE = 0,
   VIBROMOTOR4_PROPERTY_ENABLE

} vibromotor4_property_mode_t;

/*!
 * @addtogroup vibromotor4 Vibro Motor 4 Click Driver
 * @brief API for configuring and manipulating Vibro Motor 4 Click driver.
 * @{
 */

/**
 * @brief Vibro Motor 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vibromotor4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vibromotor4_cfg_setup ( vibromotor4_cfg_t *cfg );

/**
 * @brief Vibro Motor 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vibromotor4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_init ( vibromotor4_t *ctx, vibromotor4_cfg_t *cfg );

/**
 * @brief Vibro Motor 4 default configuration function.
 * @details This function executes a default configuration of Vibro Motor 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t vibromotor4_default_cfg ( vibromotor4_t *ctx );

/**
 * @brief Vibro Motor 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting to
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_generic_write ( vibromotor4_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Vibro Motor 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_generic_read ( vibromotor4_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Vibro Motor 4 enable the device function.
 * @details This function is used to enable or disable the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] pr_mode : Property mode object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_enable ( vibromotor4_t *ctx, vibromotor4_property_mode_t pr_mode );

/**
 * @brief Vibro Motor 4 I2C writing function.
 * @details This function writes a byte of the data to
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_write_byte ( vibromotor4_t *ctx, uint8_t reg, uint8_t tx_buf );

/**
 * @brief Vibro Motor 4 I2C reading function.
 * @details This function reads a byte of the data from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_read_byte ( vibromotor4_t *ctx, uint8_t reg, uint8_t *rx_buf );

/**
 * @brief Vibro Motor 4 sets the desired mode function.
 * @details This function is used to apply the desired mode of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] mode_sel : Selected mode data:
 *         @li @c 0: Internal trigger - Waveforms are fired by setting the GO bit in register
 *                   VIBROMOTOR4_REG_GO.
 *          @li @c 1: External trigger (edge mode) - A rising edge on the IN/TRIG pin sets the
 *                   GO Bit. A second rising edge on the IN/TRIG pin cancels the waveform if the
 *                   second rising edge occurs before the GO bit has cleared.
 *          @li @c 2: External trigger (level mode) - The GO bit follows the state of the
 *                   external trigger. A rising edge on the IN/TRIG pin sets the GO bit, and
 *                   a falling edge sends a cancel. If the GO bit is already in the appropriate
 *                   state, no change occurs.
 *          @li @c 3: PWM input and analog input - A PWM or analog signal is accepted at the
 *                   IN/TRIG pin and used as the driving source. The device actively drives the
 *                   actuator while in this mode. The PWM or analog input selection occurs by
 *                   using the N_PWM_ANALOG bit.
 *          @li @c 4: Audio-to-vibe - An AC-coupled audio signal is accepted at the IN/TRIG
 *                   pin. The device converts the audio signal into meaningful haptic vibration.
 *                   The AC_COUPLE and N_PWM_ANALOG bits should also be set.
 *          @li @c 5: Real-time playback (RTP mode) - The device actively drives the actuator
 *                   with the contents of the RTP_INPUT bits in register VIBROMOTOR4_RT_PB_IN.
 *          @li @c 6: Diagnostics - Set the device in this mode to perform a diagnostic test
 *                   on the actuator. The user must set the GO bit to start the test. The test
 *                   is complete when the GO bit self-clears. Results are stored in the
 *                   DIAG_RESULT bit in register VIBROMOTOR4_STATUS.
 *          @li @c 7: Auto calibration -  Set the device in this mode to auto calibrate the
 *                   device for the actuator. Before starting the calibration, the user must
 *                   set the all required input parameters. The user must set the GO bit to
 *                   start the calibration. Calibration is complete when the GO bit self-clears.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_mode ( vibromotor4_t *ctx, uint8_t mode_sel );

/**
 * @brief Vibro Motor 4 software reset function.
 * @details This function is used to perform software reset of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_soft_rst ( vibromotor4_t *ctx );

/**
 * @brief Vibro Motor 4 software standby mode function.
 * @details This function is used to enable or disable the standby mode of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] state : Defines the state of the standby mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_stb_mode ( vibromotor4_t *ctx, uint8_t state );

/**
 * @brief Vibro Motor 4 get status function.
 * @details This function is used to read the status data of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[out] status : Device status data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_get_stat ( vibromotor4_t *ctx, uint8_t *status );

/**
 * @brief Vibro Motor 4 sets the desired input for RTP mode function.
 * @details This function is used to sets the desired Real-Time Playback Input of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] rtp_input : Desired input for RTP mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_rtp_input ( vibromotor4_t *ctx, uint8_t rtp_input );

/**
 * @brief Vibro Motor 4 sets the devices in HI-Z state function.
 * @details This function is used to enable or disable the HI-Z state of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] state : Defines the HI-Z state:
 *         @li @c  0 - Disables the HI-Z state,
 *         @li @c  1 - Enables the HI-Z state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_state_hi_z ( vibromotor4_t *ctx, uint8_t state );

/**
 * @brief Vibro Motor 4 sets the desired vibrating patterns library function.
 * @details This function is used to set waveform library selection of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] lib_sel : Available libraryes:
 *         @li @c  0 - Empty,
 *         @li @c  1 - TS2200 Library A,
 *         @li @c  2 - TS2200 Library B,
 *         @li @c  3 - TS2200 Library C,
 *         @li @c  4 - TS2200 Library D,
 *         @li @c  5 - TS2200 Library E,
 *         @li @c  6 - LRA Library.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_library ( vibromotor4_t *ctx, uint8_t lib_sel );

/**
 * @brief Vibro Motor 4 starts the motor function.
 * @details This function is used to start or stop the motor using of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] state : Defines the HI-Z state:
 *         @li @c  0 - Stops moving the motor,
 *         @li @c  1 - Starts moving the motor.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_start_motor ( vibromotor4_t *ctx, uint8_t state );

/**
 * @brief Vibro Motor 4 sets overdrive offset function.
 * @details This function is used to sets the desired overdrive offset of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] ovdr_offset : Desired overdrive offset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_ovdr_offset ( vibromotor4_t *ctx, uint8_t ovdr_offset );

/**
 * @brief Vibro Motor 4 sets sustain offset - positive function.
 * @details This function is used to sets the desired sustain offset - positive of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] sustain_offset_pos : Desired positive sustain offset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_sustain_offset_pos ( vibromotor4_t *ctx, uint8_t sustain_offset_pos );

/**
 * @brief Vibro Motor 4 sets sustain offset - negative function.
 * @details This function is used to sets the desired sustain offset - negative of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] sustain_offset_neg : Desired negative sustain offset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_sustain_offset_neg ( vibromotor4_t *ctx, uint8_t sustain_offset_neg );

/**
 * @brief Vibro Motor 4 sets brake time offset function.
 * @details This function is used to sets the desired brake time offset of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] brake_time_offset : Desired brake time offset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_brake_time_offset ( vibromotor4_t *ctx, uint8_t brake_time_offset );

/**
 * @brief Vibro Motor 4 sets reference voltage function.
 * @details This function is used to sets the desired reference voltage of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] rated_volt : Desired brake time offset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_rated_volt ( vibromotor4_t *ctx, uint8_t rated_volt );

/**
 * @brief Vibro Motor 4 sets a clamp function.
 * @details This function is used to sets a clamp so that the
 * automatic overdrive is bounded the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] ovdrv_clamp_volt : Desired brake time offset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_ovdrv_clamp_volt ( vibromotor4_t *ctx, uint8_t ovdrv_clamp_volt );

/**
 * @brief Vibro Motor 4 get voltage-compensation function.
 * @details This function is used to gets the voltage-compensation result after execution
 * of auto calibration of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[out] calib_res_comp : Output contained data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_get_calib_res_comp ( vibromotor4_t *ctx, uint8_t *calib_res_comp );

/**
 * @brief Vibro Motor 4 get the supply voltage function.
 * @details This function does a real-time reading of the supply voltage
 * at the VDD pin of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[out] supply_volt : Voltage on VDD pin data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_get_supply_volt_val ( vibromotor4_t *ctx, float *supply_volt );

/**
 * @brief Vibro Motor 4 get the measurement of the LRA resonance period function.
 * @details This function gets the measurement of the LRA resonance period of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[out] lra_res : LRA resonance period data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_get_lra_resonance_period ( vibromotor4_t *ctx, float *lra_res );

/**
 * @brief Vibro Motor 4 sets the device in LRA mode function.
 * @details This function is used to sets the device in LRA mode of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] lra_mode : Defines the device's mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_lra_mode ( vibromotor4_t *ctx, uint8_t lra_mode );

/**
 * @brief Vibro Motor 4 set brake factor function.
 * @details This function selects the feedback gain ratio between braking
 * gain and driving gain of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] brk_fac : Available brake factors:
 *         @li @c  0 - Braking disabled,
 *         @li @c  1 - x1,
 *         @li @c  2 - x2,
 *         @li @c  3 - x3,
 *         @li @c  4 - x4,
 *         @li @c  6 - x6,
 *         @li @c  8 - x8,
 *         @li @c 16 - x16
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_brake_factor ( vibromotor4_t *ctx, uint8_t brk_fac );

/**
 * @brief Vibro Motor 4 selects a loop gain function.
 * @details This function selects a loop gain for the feedback control of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] gain : Available brake factors:
 *         @li @c  0 - Low,
 *         @li @c  1 - Medium,
 *         @li @c  2 - High,
 *         @li @c  3 - Very High.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_loop_gain ( vibromotor4_t *ctx, uint8_t gain );

/**
 * @brief Vibro Motor 4 sets the input to PWM or analog function.
 * @details This function is used to select the input mode for
 * the IN/TRIG(PWM) pin of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] gain : Available brake factors:
 *         @li @c  0 - Analog input mode,
 *         @li @c  1 - Sets PWM input mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_set_input ( vibromotor4_t *ctx, uint8_t state );

/**
 * @brief Vibro Motor 4 enable AC coulping function.
 * @details This function applies a 0.9-V common mode voltage
 * to the IN/TRIG pin of the DRV2605L,
 * 2- to 5.2-V Haptic Driver for LRA and ERM with Effect Library and Smart-Loop Architecture
 * on the Vibro Motor 4 click board™.
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor4_enable_ac_coulping ( vibromotor4_t *ctx );

/**
 * @brief Vibro Motor 4 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibromotor4_set_duty_cycle ( vibromotor4_t *ctx, float duty_cycle );

/**
 * @brief Vibro Motor 4 stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibromotor4_pwm_stop ( vibromotor4_t *ctx );

/**
 * @brief Vibro Motor 4 start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #vibromotor4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibromotor4_pwm_start ( vibromotor4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VIBROMOTOR4_H

/*! @} */ // vibromotor4

// ------------------------------------------------------------------------ END
