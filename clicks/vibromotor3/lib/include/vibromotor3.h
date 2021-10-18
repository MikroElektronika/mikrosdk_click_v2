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
 * @file vibromotor3.h
 * @brief This file contains API for Vibro Motor 3 Click Driver.
 */

#ifndef VIBROMOTOR3_H
#define VIBROMOTOR3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_pwm.h"

/*!
 * @addtogroup vibromotor3 Vibro Motor 3 Click Driver
 * @brief API for configuring and manipulating Vibro Motor 3 Click driver.
 * @{
 */

/**
 * @defgroup vibromotor3_reg Vibro Motor 3 Registers List
 * @brief List of registers of Vibro Motor 3 Click driver.
 */

/**
 * @addtogroup vibromotor3_reg
 * @{
 */

/**
 * @brief Vibro Motor 3 description register.
 * @details Specified register for description of Vibro Motor 3 Click driver.
 */
#define VIBROMOTOR3_STATUS                0x00
#define VIBROMOTOR3_MODE                  0x01
#define VIBROMOTOR3_RT_PB_IN              0x02
#define VIBROMOTOR3_LIB_SEL               0x03
#define VIBROMOTOR3_WV_SEQ_1              0x04
#define VIBROMOTOR3_WV_SEQ_2              0x05
#define VIBROMOTOR3_WV_SEQ_3              0x06
#define VIBROMOTOR3_WV_SEQ_4              0x07
#define VIBROMOTOR3_WV_SEQ_5              0x08
#define VIBROMOTOR3_WV_SEQ_6              0x09
#define VIBROMOTOR3_WV_SEQ_7              0x0A
#define VIBROMOTOR3_WV_SEQ_8              0x0B
#define VIBROMOTOR3_REG_GO                0x0C
#define VIBROMOTOR3_OVERDRIVE_OFFS        0x0D
#define VIBROMOTOR3_SUSTAIN_P_OFFS        0x0E
#define VIBROMOTOR3_SUSTAIN_N_OFFS        0x0F
#define VIBROMOTOR3_BRAKE_OFF             0x10
#define VIBROMOTOR3_A_TO_V_CTRL           0x11
#define VIBROMOTOR3_A_TO_V_MIN_INPUT      0x12
#define VIBROMOTOR3_A_TO_V_MAX_INPUT      0x13
#define VIBROMOTOR3_A_TO_V_MIN_OUT        0x14
#define VIBROMOTOR3_A_TO_V_MAX_OUT        0x15
#define VIBROMOTOR3_RATED_VOLT            0x16
#define VIBROMOTOR3_OD_CLAMP_VOLT         0x17
#define VIBROMOTOR3_CAL_COMP              0x18
#define VIBROMOTOR3_CAL_BACK_EMF          0x19
#define VIBROMOTOR3_FEEDBACK_CTRL         0x1A
#define VIBROMOTOR3_CTRL1                 0x1B
#define VIBROMOTOR3_CTRL2                 0x1C
#define VIBROMOTOR3_CTRL3                 0x1D
#define VIBROMOTOR3_CTRL4                 0x1E
#define VIBROMOTOR3_CTRL5                 0x1F
#define VIBROMOTOR3_LRA_LOOP_PERIOD       0x20
#define VIBROMOTOR3_VBAT_MON              0x21
#define VIBROMOTOR3_LRA_RES_PERIOD        0x22

/*! @} */ // vibromotor3_reg

/**
 * @defgroup vibromotor3_set Vibro Motor 3 Registers Settings
 * @brief Settings for registers of Vibro Motor 3 Click driver.
 */

/**
 * @addtogroup vibromotor3_set
 * @{
 */

/**
 * @brief Vibro Motor 3 description setting.
 * @details Specified setting for description of Vibro Motor 3 Click driver.
 */
#define VIBROMOTOR3_STARTPPBOOST          0x80
#define VIBROMOTOR3_BYPASSCOMP            0x40
#define VIBROMOTOR3_AC_COUPLE             0x20
#define VIBROMOTOR3_DC_COUPLE             0x00
#define VIBROMOTOR3_DRV_TIME_0P5M         0x00
#define VIBROMOTOR3_DRV_TIME_0P6M         0x01
#define VIBROMOTOR3_DRV_TIME_0P7M         0x02
#define VIBROMOTOR3_DRV_TIME_0P8M         0x03
#define VIBROMOTOR3_DRV_TIME_0P9M         0x04
#define VIBROMOTOR3_DRV_TIME_1P0M         0x05
#define VIBROMOTOR3_DRV_TIME_1P1M         0x06
#define VIBROMOTOR3_DRV_TIME_1P2M         0x07
#define VIBROMOTOR3_DRV_TIME_1P3M         0x08
#define VIBROMOTOR3_DRV_TIME_1P4M         0x09
#define VIBROMOTOR3_DRV_TIME_1P5M         0x0A
#define VIBROMOTOR3_DRV_TIME_1P6M         0x0B
#define VIBROMOTOR3_DRV_TIME_1P7M         0x0C
#define VIBROMOTOR3_DRV_TIME_1P8M         0x0D
#define VIBROMOTOR3_DRV_TIME_1P9M         0x0E
#define VIBROMOTOR3_DRV_TIME_2P0M         0x0F
#define VIBROMOTOR3_DRV_TIME_2P1M         0x10
#define VIBROMOTOR3_DRV_TIME_2P2M         0x11
#define VIBROMOTOR3_DRV_TIME_2P3M         0x12
#define VIBROMOTOR3_DRV_TIME_2P4M         0x13
#define VIBROMOTOR3_DRV_TIME_2P5M         0x14
#define VIBROMOTOR3_DRV_TIME_2P6M         0x15
#define VIBROMOTOR3_DRV_TIME_2P7M         0x16
#define VIBROMOTOR3_DRV_TIME_2P8M         0x17
#define VIBROMOTOR3_DRV_TIME_2P9M         0x18
#define VIBROMOTOR3_DRV_TIME_3P0M         0x19
#define VIBROMOTOR3_DRV_TIME_3P1M         0x1A
#define VIBROMOTOR3_DRV_TIME_3P2M         0x1B
#define VIBROMOTOR3_DRV_TIME_3P3M         0x1C
#define VIBROMOTOR3_DRV_TIME_3P4M         0x1D
#define VIBROMOTOR3_DRV_TIME_3P5M         0x1E
#define VIBROMOTOR3_DRV_TIME_3P6M         0x1F
#define VIBROMOTOR3_BIDIR_IN              0x80
#define VIBROMOTOR3_UNIDIR_IN             0x00
#define VIBROMOTOR3_BRK_STABIL            0x40
#define VIBROMOTOR3_SAMP_TIME_150US       0x00
#define VIBROMOTOR3_SAMP_TIME_200US       0x10
#define VIBROMOTOR3_SAMP_TIME_250US       0x20
#define VIBROMOTOR3_SAMP_TIME_300US       0x30
#define VIBROMOTOR3_BLANK_TIME_V_SHORT    0x00
#define VIBROMOTOR3_BLANK_TIME_SHORT      0x04
#define VIBROMOTOR3_BLANK_TIME_MEDIUM     0x08
#define VIBROMOTOR3_BLANK_TIME_LONG       0x0C
#define VIBROMOTOR3_I_DIS_TIME_V_SHORT    0x00
#define VIBROMOTOR3_I_DIS_TIME_SHORT      0x01
#define VIBROMOTOR3_I_DIS_TIME_MEDIUM     0x02
#define VIBROMOTOR3_I_DIS_TIME_LONG       0x03
#define VIBROMOTOR3_NG_THRESH_OFF         0x00
#define VIBROMOTOR3_NG_THRESH_2_PERC      0x40
#define VIBROMOTOR3_NG_THRESH_4_PERC      0x80
#define VIBROMOTOR3_NG_THRESH_8_PERC      0xC0
#define VIBROMOTOR3_ERM_CLOSED_LOOP       0x00
#define VIBROMOTOR3_ERM_OPEN_LOOP         0x20
#define VIBROMOTOR3_SUP_COMP_DIS          0x10
#define VIBROMOTOR3_DATA_FORM_RTP_SIG     0x00
#define VIBROMOTOR3_DATA_FORM_RTP_UNS     0x08
#define VIBROMOTOR3_LRADRV_MODE           0x04
#define VIBROMOTOR3_LRADRV_MODE_ONCE      0x00
#define VIBROMOTOR3_LRADRV_MODE_TWICE     0x04
#define VIBROMOTOR3_IN_MODE_PWM           0x00
#define VIBROMOTOR3_IN_MODE_ANALOG        0x02
#define VIBROMOTOR3_LRA_AUTO_RESONA       0x00
#define VIBROMOTOR3_LRA_OPEN_LOOP         0x01
#define VIBROMOTOR3_LRA_CLOSED_LOOP       0x00

/**
 * @brief Vibro Motor 3 Mode register bits.
 * @details Mode register bits of Vibro Motor 3 Click driver.
 */
#define VIBROMOTOR3_DEV_RESRT             0x80
#define VIBROMOTOR3_STANDBY               0x40
#define VIBROMOTOR3_ACTIVE                0x00
#define VIBROMOTOR3_INT_TRIG              0x00
#define VIBROMOTOR3_EXT_TRIG_EDGE         0x01
#define VIBROMOTOR3_EXT_TRIG_LEVEL        0x02
#define VIBROMOTOR3_PWM_ANALOG            0x03
#define VIBROMOTOR3_AUDIO2HAPTIC          0x04
#define VIBROMOTOR3_RTP                   0x05
#define VIBROMOTOR3_DIAGNOSTICS           0x06
#define VIBROMOTOR3_AUTO_CALIBRATION      0x07

/**
 * @brief Vibro Motor 3 Library selection register bits.
 * @details Specified library selection register bits of Vibro Motor 3 Click driver.
 */
#define VIBROMOTOR3_HIZ                   0x10
#define VIBROMOTOR3_RAM                   0x00
#define VIBROMOTOR3_ROM_A                 0x01
#define VIBROMOTOR3_ROM_B                 0x02
#define VIBROMOTOR3_ROM_C                 0x03
#define VIBROMOTOR3_ROM_D                 0x04
#define VIBROMOTOR3_ROM_E                 0x05
#define VIBROMOTOR3_ROM_LRA               0x06

/**
 * @brief Vibro Motor 3 GO register bits.
 * @details GO register bits of Vibro Motor 3 Click driver.
 */
#define VIBROMOTOR3_GO                    0x01
#define VIBROMOTOR3_STOP                  0x00

/**
 * @brief Vibro Motor 3 Feedback control register bits.
 * @details Feedback control register bits of Vibro Motor 3 Click driver.
 */
#define VIBROMOTOR3_ERM_MODE              0x00
#define VIBROMOTOR3_LRA_MODE              0x80
#define VIBROMOTOR3_FB_BRAKE_FAC_1X       0x00
#define VIBROMOTOR3_FB_BRAKE_FAC_2X       0x10
#define VIBROMOTOR3_FB_BRAKE_FAC_3X       0x20
#define VIBROMOTOR3_FB_BRAKE_FAC_4X       0x30
#define VIBROMOTOR3_FB_BRAKE_FAC_6X       0x40
#define VIBROMOTOR3_FB_BRAKE_FAC_8X       0x50
#define VIBROMOTOR3_FB_BRAKE_FAC_16X      0x60
#define VIBROMOTOR3_FB_BRAKE_FAC_DIS      0x70
#define VIBROMOTOR3_LOOP_RESP_SLOW        0x00
#define VIBROMOTOR3_LOOP_RESP_MEDIUM      0x04
#define VIBROMOTOR3_LOOP_RESP_FAST        0x08
#define VIBROMOTOR3_LOOP_RESP_V_FAST      0x0C
#define VIBROMOTOR3_BEMF_GAIN_ERM_0P3X    0x00
#define VIBROMOTOR3_BEMF_GAIN_ERM_1X      0x01
#define VIBROMOTOR3_BEMF_GAIN_ERM_1P8X    0x02
#define VIBROMOTOR3_BEMF_GAIN_ERM_4X      0x03
#define VIBROMOTOR3_BEMF_GAIN_LRA_5X      0x00
#define VIBROMOTOR3_BEMF_GAIN_LRA_10X     0x01
#define VIBROMOTOR3_BEMF_GAIN_LRA_20X     0x02
#define VIBROMOTOR3_BEMF_GAIN_LRA_30X     0x03

/**
 * @brief Vibro Motor 3 Auto calibration memory interface register.
 * @details Auto calibration memory interface register of Vibro Motor 3 Click driver.
 */
#define VIBROMOTOR3_AUTO_CAL_TIME_150MS   0x00
#define VIBROMOTOR3_AUTO_CAL_TIME_250MS   0x10
#define VIBROMOTOR3_AUTO_CAL_TIME_500MS   0x20
#define VIBROMOTOR3_AUTO_CAL_TIME_1000MS  0x30
#define VIBROMOTOR3_OTP_PROG              0x01

/**
 * @brief Vibro Motor 3 Property enable or disable values.
 * @details Property enable or disable values of Vibro Motor 3 Click driver.
 */
#define VIBROMOTOR3_PROPERTY_DISABLE      0
#define VIBROMOTOR3_PROPERTY_ENABLE       1

/**
 * @brief Vibro Motor 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Vibro Motor 3 Click driver.
 */
#define VIBROMOTOR3_SET_DEV_ADDR          0x5A

/**
 * @brief Vibro Motor 3 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Vibro Motor 3 Click driver.
 */
#define VIBROMOTOR3_DEF_FREQ              235

/*! @} */ // vibromotor3_set

/**
 * @defgroup vibromotor3_map Vibro Motor 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Vibro Motor 3 Click driver.
 */

/**
 * @addtogroup vibromotor3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Vibro Motor 3 Click to the selected MikroBUS.
 */
#define VIBROMOTOR3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // vibromotor3_map
/*! @} */ // vibromotor3

/**
 * @brief Vibro Motor 3 Click context object.
 * @details Context object definition of Vibro Motor 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en;                                  /**< Enable. */

    // Modules
    i2c_master_t i2c;                                   /**< I2C driver object. */
    pwm_t  pwm;                                         /**< PWM driver object. */
    
    // I2C slave address
    uint8_t slave_address;                              /**< Device slave address (used for I2C driver). */
    
    uint32_t pwm_freq;                                  /**< PWM frequency value. */

} vibromotor3_t;

/**
 * @brief Vibro Motor 3 Click configuration object.
 * @details Configuration object definition of Vibro Motor 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                                    /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                                    /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;                                     /**< Enable. */
    pin_name_t  pwm;                                    /**< PWM Signal. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */
    
    uint32_t dev_pwm_freq;                              /**< PWM frequency value. */

} vibromotor3_cfg_t;

/**
 * @brief Vibro Motor 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   VIBROMOTOR3_OK = 0,
   VIBROMOTOR3_ERROR = -1

} vibromotor3_return_value_t;

/*!
 * @addtogroup vibromotor3 Vibro Motor 3 Click Driver
 * @brief API for configuring and manipulating Vibro Motor 3 Click driver.
 * @{
 */

/**
 * @brief Vibro Motor 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vibromotor3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * 
 * @note The all used pins will be set to unconnected state.
 */
void vibromotor3_cfg_setup ( vibromotor3_cfg_t *cfg );

/**
 * @brief Vibro Motor 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vibromotor3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibromotor3_init ( vibromotor3_t *ctx, vibromotor3_cfg_t *cfg );

/**
 * @brief Vibro Motor 3 default configuration function.
 * @details This function executes a default configuration of Vibro Motor 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t vibromotor3_default_cfg ( vibromotor3_t *ctx );

/**
 * @brief Vibro Motor 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibromotor3_generic_write ( vibromotor3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Vibro Motor 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibromotor3_generic_read ( vibromotor3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Vibro Motor 3 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibromotor3_set_duty_cycle ( vibromotor3_t *ctx, float duty_cycle );

/**
 * @brief Vibro Motor 3 stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibromotor3_pwm_stop ( vibromotor3_t *ctx );

/**
 * @brief Vibro Motor 3 start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibromotor3_pwm_start ( vibromotor3_t *ctx );

/**
 * @brief Enable the device function
 * @details The function is used to enable or disable the device.
 * @param[out] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] state : 8-bit value that defines the state of the device
 * @return Nothing.
 * 
 * @note "VIBROMOTOR3_PROPERTY_ENABLE"(1) turns the device on,
 * "VIBROMOTOR3_PROPERTY_DISABLE"(0) turns the device off.
**/
void vibromotor3_enable ( vibromotor3_t *ctx, uint8_t state );

/**
 * @brief Generic write the byte of data function
 * @details The function is used to write 8-bit data to the target 8-bit
 * register address.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] wr_data : 8-bit input data.
 * @return Nothing.
**/
void vibromotor3_write_byte ( vibromotor3_t *ctx, uint8_t reg, uint8_t wr_data );

/**
 * @brief Generic read the byte of data function
 * @details The function is used to read 8-bit data from the target 8-bit
 * register address.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @return 8-bit output data.
 * @return Nothing.
**/
uint8_t vibromotor3_read_byte ( vibromotor3_t *ctx, uint8_t reg );

/**
 * @brief Sets the desired mode function
 * @details Function is used to apply the desired mode.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] mode_sel : Value that defines selected mode
 * @return Nothing.
 *
 * @note Available modes :
 * 0: Internal trigger - Waveforms are fired by setting the GO bit in register
 * VIBROMOTOR3_REG_GO.
 * 1: External trigger (edge mode) - A rising edge on the IN/TRIG pin sets the
 * GO Bit. A second rising edge on the IN/TRIG pin cancels the waveform if the
 * second rising edge occurs before the GO bit has cleared.
 * 2: External trigger (level mode) - The GO bit follows the state of the
 * external trigger. A rising edge on the IN/TRIG pin sets the GO bit, and
 * a falling edge sends a cancel. If the GO bit is already in the appropriate
 * state, no change occurs.
 * 3: PWM input and analog input - A PWM or analog signal is accepted at the
 * IN/TRIG pin and used as the driving source. The device actively drives the
 * actuator while in this mode. The PWM or analog input selection occurs by
 * using the N_PWM_ANALOG bit.
 * 4: Audio-to-vibe - An AC-coupled audio signal is accepted at the IN/TRIG
 * pin. The device converts the audio signal into meaningful haptic vibration.
 * The AC_COUPLE and N_PWM_ANALOG bits should also be set.
 * 5: Real-time playback (RTP mode) - The device actively drives the actuator
 * with the contents of the RTP_INPUT bits in register VIBROMOTOR3_RT_PB_IN.
 * 6: Diagnostics - Set the device in this mode to perform a diagnostic test
 * on the actuator. The user must set the GO bit to start the test. The test
 * is complete when the GO bit self-clears. Results are stored in the
 * DIAG_RESULT bit in register VIBROMOTOR3_STATUS.
 * 7: Auto calibration -  Set the device in this mode to auto calibrate the
 * device for the actuator. Before starting the calibration, the user must
 * set the all required input parameters. The user must set the GO bit to
 * start the calibration. Calibration is complete when the GO bit self-clears.
**/
void vibromotor3_set_mode ( vibromotor3_t *ctx, uint8_t mode_sel );

/**
 * @brief Reset function.
 * @details The function is used to perform software reset.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @return Nothing.
**/
void vibromotor3_soft_rst ( vibromotor3_t *ctx );

/**
 * @brief Software standby mode
 * @details The function is used to enable or disable the standby mode.
 * @param[in] state : 8-bit value that defines the state of the standby mode
 * @return Nothing.
 * 
 * @note "VIBROMOTOR3_PROPERTY_ENABLE"(1) enables the standby mode,
 * "VIBROMOTOR3_PROPERTY_DISABLE"(0) disables the standby mode.
**/
void vibromotor3_stb_mode ( vibromotor3_t *ctx, uint8_t state );

/**
 * @brief Get status register value function
 * @details The function is used to read the value from the status register.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @returns result 8-bit device status data
 *
 * @note Status register holds device identifier, result of the auto-calibration
 * routine and the diagnostic routine, status for the feedback controller, 
 * overtemperature and overcurrent detection flags.
**/
uint8_t vibromotor3_get_stat ( vibromotor3_t *ctx );

/**
 * @brief Sets the desired input for RTP mode function
 * @details Function sets the desired Real-Time Playback Input.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] data_in : 8-bit desired input for RTP mode
 * @return Nothing.
**/
void vibromotor3_set_rtp_input ( vibromotor3_t *ctx, uint8_t data_in );

/**
 * @brief Set the devices in HI-Z state function
 * @details The function is used to enable or disable the HI-Z state.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] state : 8-bit value that defines the HI-Z state
 * @return Nothing.
 * @note "VIBROMOTOR3_PROPERTY_ENABLE"(1) enables the HI-Z state,
 * "VIBROMOTOR3_PROPERTY_DISABLE"(0) disables the HI-Z state.
**/
void vibromotor3_set_state_hi_z ( vibromotor3_t *ctx, uint8_t state );

/**
 * @brief Set the desired vibrating patterns library
 * @details Function is used to set waveform library selection value.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] lib_sel : Value that defines selected library
 * @return Nothing.
 * 
 * @note Available libraryes :
 * 0: Empty
 * 1: TS2200 Library A
 * 2: TS2200 Library B
 * 3: TS2200 Library C
 * 4: TS2200 Library D
 * 5: TS2200 Library E
 * 6: LRA Library
**/
void vibromotor3_set_library ( vibromotor3_t *ctx, uint8_t lib_sel );

/**
 * @brief Starts or stops moving the motor function
 * @details The function is used to start or stop the motor.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] state : 8-bit value that defines the motor's state
 * @return Nothing.
 * 
 * @note "VIBROMOTOR3_PROPERTY_ENABLE"(1) starts moving the motor,
 * "VIBROMOTOR3_PROPERTY_DISABLE"(0) stops moving the motor.
**/
void vibromotor3_start_motor ( vibromotor3_t *ctx, uint8_t state );

/**
 * @brief Sets overdrive offset function
 * @details Function sets the desired overdrive offset.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] data_in : 8-bit desired overdrive offset
 * @return Nothing.
**/
void vibromotor3_set_ovdr_offset ( vibromotor3_t *ctx, uint8_t data_in );

/**
 * @brief Sets sustain offset - positive function
 * @details Function sets the desired sustain offset - positive.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] data_in : 8-bit desired positive sustain offset
 * @return Nothing.
**/
void vibromotor3_set_sustain_offset_pos ( vibromotor3_t *ctx, uint8_t data_in );

/**
 * @brief Sets sustain offset - negative function
 * @details Function sets the desired sustain offset - negative.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] data_in : 8-bit desired negative sustain offset
 * @return Nothing.
**/
void vibromotor3_set_sustain_offset_neg ( vibromotor3_t *ctx, uint8_t data_in );

/**
 * @brief Sets brake time offset function
 * @details Function sets the desired brake time offset.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] data_in : 8-bit desired brake time offset
 * @return Nothing.
**/
void vibromotor3_set_brake_time_offset ( vibromotor3_t *ctx, uint8_t data_in );

/**
 * @brief Sets the reference voltage function
 * @details Function sets the reference voltage for full-scale output 
 * during closed-loop.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] data_in : 8-bit desired value represetning the voltage
 * @return Nothing.
**/
void vibromotor3_set_rated_volt ( vibromotor3_t *ctx, uint8_t data_in );

/**
 * @brief Sets a clamp function
 * @details Function sets a clamp so that the automatic overdrive is 
 * bounded.
 * @param[in] data_in : 8-bit desired imput value
 * @return Nothing.
**/
void vibromotor3_set_ovdrv_clamp_volt ( vibromotor3_t *ctx, uint8_t data_in );

/**
 * @brief Reads the voltage-compensation function
 * @details Function gets the voltage-compensation result after execution 
 * of auto calibration.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @returns res 8-bit value contained in the register
**/
uint8_t vibromotor3_get_calib_res_comp ( vibromotor3_t *ctx );

/**
 * @brief Reading of the supply voltage function
 * @details Function does a real-time reading of the supply voltage 
 * at the VDD pin.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @returns res float voltage on VDD pin
**/
float vibromotor3_get_supply_volt_val ( vibromotor3_t *ctx );

/**
 * @brief Reads the measurement of the LRA resonance period function
 * @details Function gets the measurement of the LRA resonance period.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @returns res float LRA resonance period
**/
float vibromotor3_get_lra_resonance_period ( vibromotor3_t *ctx );

/**
 * @brief Sets the device in LRA mode function
 * @details The function is used to sets the device in LRA mode.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] state : 8-bit value that defines the device's mode
 * @return Nothing.
 * 
 * @note "VIBROMOTOR3_PROPERTY_ENABLE"(1) enables the LRA mode,
 * "VIBROMOTOR3_PROPERTY_DISABLE"(0) enables the ERM Mode(NOT supported!!!).
**/
void vibromotor3_set_lra_mode ( vibromotor3_t *ctx, uint8_t state );

/**
 * @brief Set brake factor function
 * @details Function selects the feedback gain ratio between braking 
 * gain and driving gain.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] brk_fac : Value that defines brake factor
 * @return Nothing.
 * 
 * @note Available brake factors :
 * 0:  Braking disabled
 * 1:  1x
 * 2:  2x
 * 3:  3x
 * 4:  4x
 * 6:  6x
 * 8:  8x
 * 16: 16x
**/
void vibromotor3_set_brake_factor ( vibromotor3_t *ctx, uint8_t brk_fac );

/**
 * @brief Selects a loop gain function
 * @details Function selects a loop gain for the feedback control.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] gain : Value that defines a loop gain
 * @return Nothing.
 * 
 * @note Available loop gains :
 * 0: Low
 * 1: Medium
 * 2: High
 * 3: Very High
**/
void vibromotor3_set_loop_gain ( vibromotor3_t *ctx, uint8_t gain );

/**
 * @brief Sets the input to PWM or analog function
 * @details The function is used to select the input mode for 
 * the IN/TRIG(PWM) pin.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @param[in] state : 8-bit value that defines the input mode
 * @return Nothing.
 * 
 * @note "VIBROMOTOR3_PROPERTY_ENABLE"(1) sets PWM input mode,
 * "VIBROMOTOR3_PROPERTY_DISABLE"(0) sets analog input mode.
**/
void vibromotor3_set_input ( vibromotor3_t *ctx, uint8_t data_in );

/**
 * @brief Applies a 0.9-V common mode voltage function
 * @details Function applies a 0.9-V common mode voltage to the IN/TRIG pin.
 * @param[in] ctx : Click context object.
 * See #vibromotor3_t object definition for detailed explanation.
 * @return Nothing.
**/
void vibromotor3_enable_ac_coulping ( vibromotor3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VIBROMOTOR3_H

/*! @} */ // vibromotor3

// ------------------------------------------------------------------------ END
