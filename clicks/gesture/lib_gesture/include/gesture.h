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
 * @file gesture.h
 * @brief This file contains API for Gesture Click Driver.
 */

#ifndef GESTURE_H
#define GESTURE_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup gesture Gesture Click Driver
 * @brief API for configuring and manipulating Gesture Click driver.
 * @{
 */

/**
 * @defgroup gesture_reg Gesture Registers List
 * @brief List of registers of Gesture Click driver.
 */

/**
 * @addtogroup gesture_reg
 * @{
 */

/**
 * @brief Gesture Bank 0 registers list.
 * @details Specified Bank 0 registers list of Gesture Click driver.
 */
#define GESTURE_REG_B0_PART_ID_L                        0x00
#define GESTURE_REG_B0_PART_ID_H                        0x01
#define GESTURE_REG_B0_VERSION_ID                       0x02
#define GESTURE_REG_B0_SW_SUSPEND_EN_L                  0x03
#define GESTURE_REG_B0_CURSOR_USE_TOP                   0x32
#define GESTURE_REG_B0_POS_FILTER_START_SIZE_TH_L       0x33
#define GESTURE_REG_B0_POS_FILTER_START_SIZE_TH_H       0x34
#define GESTURE_REG_B0_PROC_FILTER_START_SIZE_TH_L      0x35
#define GESTURE_REG_B0_PROC_FILTER_START_SIZE_TH_H      0x36
#define GESTURE_REG_B0_CURSOR_CLAMP_LEFT                0x37
#define GESTURE_REG_B0_CURSOR_CLAMP_RIGHT               0x38
#define GESTURE_REG_B0_CURSOR_CLAMP_UP                  0x39
#define GESTURE_REG_B0_CURSOR_CLAMP_DOWN                0x3A
#define GESTURE_REG_B0_CURSOR_CLAMP_CENTER_X_L          0x3B
#define GESTURE_REG_B0_CURSOR_CLAMP_CENTER_X_H          0x3C
#define GESTURE_REG_B0_CURSOR_CLAMP_CENTER_Y_L          0x3D
#define GESTURE_REG_B0_CURSOR_CLAMP_CENTER_Y_H          0x3E
#define GESTURE_REG_B0_MCU_INT_FLAG                     0x40
#define GESTURE_REG_B0_INT1_EN                          0x41
#define GESTURE_REG_B0_INT2_EN                          0x42
#define GESTURE_REG_B0_INT1_FLAG                        0x43
#define GESTURE_REG_B0_INT2_FLAG                        0x44
#define GESTURE_REG_B0_SLEEP_MODE_STAT                  0x45
#define GESTURE_REG_B0_AE_LED_OFF_UB                    0x46
#define GESTURE_REG_B0_AE_LED_OFF_LB                    0x47
#define GESTURE_REG_B0_AE_EXPOSURE_UB_L                 0x48
#define GESTURE_REG_B0_AE_EXPOSURE_UB_H                 0x49
#define GESTURE_REG_B0_AE_EXPOSURE_LB_L                 0x4A
#define GESTURE_REG_B0_AE_EXPOSURE_LB_H                 0x4B
#define GESTURE_REG_B0_AE_GAIN_UB                       0x4C
#define GESTURE_REG_B0_AE_GAIN_LB                       0x4D
#define GESTURE_REG_B0_AE_GAIN_STEP                     0x4E
#define GESTURE_REG_B0_AE_GAIN_DEFAULT                  0x4F
#define GESTURE_REG_B0_EXP_SEL                          0x50
#define GESTURE_REG_B0_MANUAL                           0x51
#define GESTURE_REG_B0_SLEEP_AE_12_AG_12                0x52
#define GESTURE_REG_B0_AG_STAGE_GG                      0x54
#define GESTURE_REG_B0_EXPOSURE_NUM_L                   0x55
#define GESTURE_REG_B0_EXPOSURE_NUM_H                   0x56
#define GESTURE_REG_B0_GLOBAL                           0x57
#define GESTURE_REG_B0_AE_LED_OFF_Y_AVG                 0x58
#define GESTURE_REG_B0_AE_DEC_INC                       0x59
#define GESTURE_REG_B0_AE_NORMAL_FACTOR                 0x5A
#define GESTURE_REG_B0_TRIGGER                          0x5B
#define GESTURE_REG_B0_TRIGGER                          0x5B
#define GESTURE_REG_B0_5E                               0x5E
#define GESTURE_REG_B0_60                               0x60
#define GESTURE_REG_B0_PROX_UB                          0x69
#define GESTURE_REG_B0_PROX_LB                          0x6A
#define GESTURE_REG_B0_S_STATE                          0x6B
#define GESTURE_REG_B0_S_AVG_Y                          0x6C
#define GESTURE_REG_B0_GPIO_01                          0x80
#define GESTURE_REG_B0_GPIO_23                          0x81
#define GESTURE_REG_B0_INT                              0x82
#define GESTURE_REG_B0_LIGHT_THD                        0x83
#define GESTURE_REG_B0_GESTURE_START_THD_L              0x84
#define GESTURE_REG_B0_GESTURE_START_THD_H              0x85
#define GESTURE_REG_B0_GESTURE_END_THD_L                0x86
#define GESTURE_REG_B0_GESTURE_END_THD_H                0x87
#define GESTURE_REG_B0_OBJECT_MIN_Z                     0x88
#define GESTURE_REG_B0_OBJECT_MAX_Z                     0x89
#define GESTURE_REG_B0_CURSOR_OBJECT_SIZE_TH            0x8B
#define GESTURE_REG_B0_POS_PROC_RESOLUTION              0x8C
#define GESTURE_REG_B0_TIME_DELAY_NUM                   0x8D
#define GESTURE_REG_B0_45_DEGREE                        0x8E
#define GESTURE_REG_B0_X_TO_Y_GAIN                      0x8F
#define GESTURE_REG_B0_NO_MOTION_COUNT_THD              0x90
#define GESTURE_REG_B0_NO_OBJECT_COUNT_THD              0x91
#define GESTURE_REG_B0_NORMAL_IMAGE_WIDTH               0x92
#define GESTURE_REG_B0_X_DIR_THD                        0x93
#define GESTURE_REG_B0_Y_DIR_THD                        0x94
#define GESTURE_REG_B0_Z_DIR_THD                        0x95
#define GESTURE_REG_B0_Z_DIR_XY_THD                     0x96
#define GESTURE_REG_B0_Z_DIR_ANGLE_THD                  0x97
#define GESTURE_REG_B0_ROTATE_ANGLE_THD                 0x98
#define GESTURE_REG_B0_ROTATE_CONTI                     0x99
#define GESTURE_REG_B0_ROTATE_XY_THD                    0x9A
#define GESTURE_REG_B0_ROTATE_Z_THD                     0x9B
#define GESTURE_REG_B0_FILTER                           0x9C
#define GESTURE_REG_B0_DIST_THD                         0x9D
#define GESTURE_REG_B0_GEST_DET_EN_BG_CFG               0x9F
#define GESTURE_REG_B0_BG_UPDATE_MAX_INT                0xA0
#define GESTURE_REG_B0_BG_FILTER_LEN                    0xA1
#define GESTURE_REG_B0_BG_DIFF_THD                      0xA2
#define GESTURE_REG_B0_BG_UPDATE_FREQ_L                 0xA3
#define GESTURE_REG_B0_BG_UPDATE_FREQ_H_RES             0xA4
#define GESTURE_REG_B0_FILTER_IMAGE                     0xA5
#define GESTURE_REG_B0_DIFF_ANGLE_THD                   0xA9
#define GESTURE_REG_B0_IMAGE_HEIGHT                     0xAA
#define GESTURE_REG_B0_IMAGE_WIDTH                      0xAB
#define GESTURE_REG_B0_OBJECT_CENTER_X_L                0xAC
#define GESTURE_REG_B0_OBJECT_CENTER_X_H                0xAD
#define GESTURE_REG_B0_OBJECT_CENTER_Y_L                0xAE
#define GESTURE_REG_B0_OBJECT_CENTER_Y_H                0xAF
#define GESTURE_REG_B0_OBJECT_AVG_Y                     0xB0
#define GESTURE_REG_B0_OBJECT_SIZE_L                    0xB1
#define GESTURE_REG_B0_OBJECT_SIZE_H                    0xB2
#define GESTURE_REG_B0_GESTURE_X                        0xB3
#define GESTURE_REG_B0_GESTURE_Y                        0xB4
#define GESTURE_REG_B0_GESTURE_Z                        0xB5
#define GESTURE_REG_B0_GESTURE_RESULT                   0xB6
#define GESTURE_REG_B0_WAVE_ABORT_COUNT                 0xB7
#define GESTURE_REG_B0_NO_OBJECT_COUNT                  0xB8
#define GESTURE_REG_B0_NO_MOTION_COUNT                  0xB9
#define GESTURE_REG_B0_LIGHT_COUNT                      0xBA
#define GESTURE_REG_B0_LIGHT_ACC_L                      0xBB
#define GESTURE_REG_B0_LIGHT_ACC_H                      0xBC
#define GESTURE_REG_B0_TIME_ACC_L                       0xBD
#define GESTURE_REG_B0_TIME_ACC_H                       0xBE
#define GESTURE_REG_B0_ANGLE_ACC_L                      0xC7
#define GESTURE_REG_B0_ANGLE_ACC_H                      0xC8
#define GESTURE_REG_B0_X_GAIN_VALUE                     0xCA
#define GESTURE_REG_B0_Y_GAIN_VALUE                     0xCB
#define GESTURE_REG_B0_Y_TO_Z_SUM                       0xCC
#define GESTURE_REG_B0_Y_TO_Z_FACTOR                    0xCD
#define GESTURE_REG_B0_FILTER_LEN                       0xCE
#define GESTURE_REG_B0_WAVE_THD                         0xCF
#define GESTURE_REG_B0_ABORT_COUNT_THD                  0xD0
#define GESTURE_REG_B0_ABORT_LEN                        0xD1
#define GESTURE_REG_B0_WAVE_EN_H                        0xD2
#define GESTURE_REG_B0_POS_FILTER_CENTER_X_L            0xD3
#define GESTURE_REG_B0_POS_FILTER_CENTER_XY_H           0xD4
#define GESTURE_REG_B0_POS_FILTER_CENTER_Y_L            0xD5
#define GESTURE_REG_B0_POS_FILTER_AVG_Y_L               0xD6
#define GESTURE_REG_B0_POS_FILTER_AVG_Y_H               0xD7
#define GESTURE_REG_B0_POS_FILTER_SIZE_L                0xD8
#define GESTURE_REG_B0_PROC_FILTER_AVG_Y_H              0xD9
#define GESTURE_REG_B0_PROC_FILTER_CENTER_X_L           0xDA
#define GESTURE_REG_B0_PROC_FILTER_CENTER_XY_H          0xDB
#define GESTURE_REG_B0_PROC_FILTER_CENTER_Y_L           0xDC
#define GESTURE_REG_B0_PROC_FILTER_SIZE_L               0xDD
#define GESTURE_REG_B0_PROC_FILTER_AVG_Y_L              0xDE
#define GESTURE_REG_B0_PROC_ABORT_INTERVAL_COUNT_L      0xDF

/**
 * @brief Gesture Bank 0 registers list.
 * @details Specified Bank 0 registers list of Gesture Click driver.
 */
#define GESTURE_REG_B1_CMD_H_SIZE                       0x00
#define GESTURE_REG_B1_CMD_V_SIZE                       0x01
#define GESTURE_REG_B1_CMD_H_START                      0x02
#define GESTURE_REG_B1_CMD_V_START                      0x03
#define GESTURE_REG_B1_CMD_HV                           0x04
#define GESTURE_REG_B1_LENS_SHADING_COMP_EN_H           0x25
#define GESTURE_REG_B1_OFFSET_X                         0x26
#define GESTURE_REG_B1_OFFSET_Y                         0x27
#define GESTURE_REG_B1_LSC                              0x28
#define GESTURE_REG_B1_LSFT                             0x29
#define GESTURE_REG_B1_LED_SOFT_START_TIME              0x30
#define GESTURE_REG_B1_LED12_DAC_EN_MAN                 0x31
#define GESTURE_REG_B1_LED1_DAC_UB                      0x32
#define GESTURE_REG_B1_LED2_DAC_UB                      0x33
#define GESTURE_REG_B1_LEDC_STEP_UP                     0x34
#define GESTURE_REG_B1_LEDC_STEP_DOWN                   0x35
#define GESTURE_REG_B1_3E                               0x3E
#define GESTURE_REG_B1_GLOBAL                           0x42
#define GESTURE_REG_B1_GGH                              0x44
#define GESTURE_REG_B1_5E                               0x5E
#define GESTURE_REG_B1_IDLE_TIME_L                      0x65
#define GESTURE_REG_B1_IDLE_TIME_H                      0x66
#define GESTURE_REG_B1_IDLE_TIME_SLEEP_1_L              0x67
#define GESTURE_REG_B1_IDLE_TIME_SLEEP_1_H              0x68
#define GESTURE_REG_B1_IDLE_TIME_SLEEP_2_L              0x69
#define GESTURE_REG_B1_IDLE_TIME_SLEEP_2_H              0x6A
#define GESTURE_REG_B1_OBJECT_TIME_1_L                  0x6B
#define GESTURE_REG_B1_OBJECT_TIME_1_H                  0x6C
#define GESTURE_REG_B1_OBJECT_TIME_2_L                  0x6D
#define GESTURE_REG_B1_OBJECT_TIME_2_H                  0x6E
#define GESTURE_REG_B1_TG_INIT_TIME                     0x6F
#define GESTURE_REG_B1_TG_POWERON_WAKEUP_TIME           0x71
#define GESTURE_REG_B1_TG_EN_H                          0x72
#define GESTURE_REG_B1_AUTO_SLEEP_MODE                  0x73
#define GESTURE_REG_B1_WAKE_UP_SIG_SEL                  0x74
#define GESTURE_REG_B1_SRAM_READ_EN_H                   0x77
#define GESTURE_REG_B1_SPIOUT_PXDNUM_L                  0x7C
#define GESTURE_REG_B1_SPIOUT_PXDNUM_H                  0x7D
#define GESTURE_REG_B1_SPIOUT                           0x7E

/**
 * @brief Gesture common registers list.
 * @details Specified common registers list of Gesture Click driver.
 */
#define GESTURE_REG_BANK_SELECT                         0xEF

/*! @} */ // gesture_reg

/**
 * @defgroup gesture_set Gesture Registers Settings
 * @brief Settings for registers of Gesture Click driver.
 */

/**
 * @addtogroup gesture_set
 * @{
 */

/**
 * @brief Gesture register bank selection setting.
 * @details Specified setting for register bank selection of Gesture Click driver.
 */
#define GESTURE_BANK_SELECT_0                           0
#define GESTURE_BANK_SELECT_1                           1

/**
 * @brief Gesture interrupt register setting.
 * @details Specified setting for interrupt register of Gesture Click driver.
 */
#define GESTURE_INT1_UP                                 0x01
#define GESTURE_INT1_DOWN                               0x02
#define GESTURE_INT1_LEFT                               0x04
#define GESTURE_INT1_RIGHT                              0x08
#define GESTURE_INT1_FORWARD                            0x10
#define GESTURE_INT1_BACKWARD                           0x20
#define GESTURE_INT1_CLOCKWISE                          0x40
#define GESTURE_INT1_COUNTER_CLOCKWISE                  0x80
#define GESTURE_INT2_WAVE                               0x01
#define GESTURE_INT2_PROXIMITY                          0x02
#define GESTURE_INT2_HAS_OBJECT                         0x04
#define GESTURE_INT2_WAKE_UP_TRIGGER                    0x08
#define GESTURE_INT2_NO_OBJECT                          0x80

/**
 * @brief Gesture gestures setting.
 * @details Specified setting for gestures of Gesture Click driver.
 */
#define GESTURE_UNKNOWN                                 0
#define GESTURE_UP                                      1
#define GESTURE_DOWN                                    2
#define GESTURE_LEFT                                    3
#define GESTURE_RIGHT                                   4
#define GESTURE_FORWARD                                 5
#define GESTURE_BACKWARD                                6
#define GESTURE_CLOCKWISE                               7
#define GESTURE_COUNTER_CLOCKWISE                       8
#define GESTURE_WAVE                                    9

/**
 * @brief Gesture get detected gesture timeout setting.
 * @details Specified setting for get detected gesture timeout of Gesture Click driver.
 */
#define GESTURE_TIMEOUT_INFINITE                        0
#define GESTURE_TIMEOUT_5S                              5000

/**
 * @brief Gesture PART_ID register setting.
 * @details Specified setting for PART_ID register of Gesture Click driver.
 */
#define GESTURE_PART_ID_L                               0x20
#define GESTURE_PART_ID_H                               0x76

/**
 * @brief Gesture device address setting.
 * @details Specified setting for device slave address selection of
 * Gesture Click driver.
 */
#define GESTURE_DEVICE_ADDRESS                          0x73

/*! @} */ // gesture_set

/**
 * @defgroup gesture_map Gesture MikroBUS Map
 * @brief MikroBUS pin mapping of Gesture Click driver.
 */

/**
 * @addtogroup gesture_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Gesture Click to the selected MikroBUS.
 */
#define GESTURE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.osc_en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gesture_map
/*! @} */ // gesture

/**
 * @brief Gesture Click context object.
 * @details Context object definition of Gesture Click driver.
 */
typedef struct
{
    digital_out_t osc_en;       /**< SPI master clock oscillator enable pin (active high). */
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} gesture_t;

/**
 * @brief Gesture Click configuration object.
 * @details Configuration object definition of Gesture Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t osc_en;          /**< SPI master clock oscillator enable pin (active high). */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} gesture_cfg_t;

/**
 * @brief Gesture Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GESTURE_OK = 0,
    GESTURE_ERROR = -1,
    GESTURE_ERROR_TIMEOUT = -2

} gesture_return_value_t;

/*!
 * @addtogroup gesture Gesture Click Driver
 * @brief API for configuring and manipulating Gesture Click driver.
 * @{
 */

/**
 * @brief Gesture configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gesture_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gesture_cfg_setup ( gesture_cfg_t *cfg );

/**
 * @brief Gesture initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gesture_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gesture_init ( gesture_t *ctx, gesture_cfg_t *cfg );

/**
 * @brief Gesture default configuration function.
 * @details This function executes a default configuration of Gesture
 * Click board.
 * @param[in] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t gesture_default_cfg ( gesture_t *ctx );

/**
 * @brief Gesture write multiple registers function.
 * @details This function writes multiple bytes of data starting from the specified register.
 * @param[in] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Pointer to the data to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t gesture_write_regs ( gesture_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Gesture read multiple registers function.
 * @details This function reads multiple bytes of data starting from the specified register.
 * @param[in] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the data buffer for storing read values.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t gesture_read_regs ( gesture_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Gesture write single register function.
 * @details This function writes a single byte of data to the specified register.
 * @param[in] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t gesture_write_reg ( gesture_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Gesture read single register function.
 * @details This function reads a single byte of data from the specified register.
 * @param[in] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the data buffer for storing the read value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t gesture_read_reg ( gesture_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Gesture SPI oscillator enable function.
 * @details This function enables the SPI oscillator by setting the OSC_EN pin high.
 * @param[in] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gesture_spi_osc_enable ( gesture_t *ctx );

/**
 * @brief Gesture SPI oscillator disable function.
 * @details This function disables the SPI oscillator by setting the OSC_EN pin low.
 * @param[in] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gesture_spi_osc_disable ( gesture_t *ctx );

/**
 * @brief Gesture get interrupt pin state function.
 * @details This function reads the logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gesture_get_int_pin ( gesture_t *ctx );

/**
 * @brief Gesture check communication function.
 * @details This function checks the communication with the device by verifying its part ID.
 * @param[in] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t gesture_check_communication ( gesture_t *ctx );

/**
 * @brief Gesture bank select function.
 * @details This function selects the specified memory bank of the device.
 * @param[in] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @param[in] bank_sel : Bank select value (0 or 1).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t gesture_bank_sel ( gesture_t *ctx, uint8_t bank_sel );

/**
 * @brief Gesture get detected gesture function.
 * @details This function detects a gesture based on the interrupt flags and assigns the corresponding gesture code.
 * @param[in] ctx : Click context object.
 * See #gesture_t object definition for detailed explanation.
 * @param[out] gesture : Pointer to the variable for storing the detected gesture.
 * @param[in] timeout : Timeout value in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout error.
 * @note None.
 */
err_t gesture_get_detected_gesture ( gesture_t *ctx, uint8_t *gesture, uint32_t timeout );

#ifdef __cplusplus
}
#endif
#endif // GESTURE_H

/*! @} */ // gesture

// ------------------------------------------------------------------------ END
