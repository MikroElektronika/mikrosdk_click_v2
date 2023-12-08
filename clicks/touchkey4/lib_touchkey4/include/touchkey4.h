/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for Touch Key 4 Click driver.
 *
 * \addtogroup touchkey4 Touch Key 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TOUCHKEY4_H
#define TOUCHKEY4_H

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
#include "drv_i2c_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define TOUCHKEY4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TOUCHKEY4_RETVAL  uint8_t

#define TOUCHKEY4_OK           0x00
#define TOUCHKEY4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_address Register Address
 * \{
 */
#define TOUCHKEY4_MAIN_CONTROL_REG                          0x00
#define TOUCHKEY4_GEN_STATUS_REG                            0x02
#define TOUCHKEY4_SENS_IN_STATUS_REG                        0x03
#define TOUCHKEY4_NOISE_FLAG_REG                            0x0A
#define TOUCHKEY4_SENS_IN1_DELTA_CNT_REG                    0x10
#define TOUCHKEY4_SENS_IN2_DELTA_CNT_REG                    0x11
#define TOUCHKEY4_SENS_IN3_DELTA_CNT_REG                    0x12
#define TOUCHKEY4_SENSITIVITY_CON_REG                       0x1F
#define TOUCHKEY4_CONFIG_REG                                0x20
#define TOUCHKEY4_SENS_IN_EN_REG                            0x21
#define TOUCHKEY4_SENS_IN_CONFIG_REG                        0x22
#define TOUCHKEY4_SENS_IN_CONFIG2_REG                       0x23
#define TOUCHKEY4_AVRG_AND_SAMPL_CONFIG_REG                 0x24
#define TOUCHKEY4_CALIB_ACTIVATE_REG                        0x26
#define TOUCHKEY4_INTERR_EN_REG                             0x27
#define TOUCHKEY4_REPEAT_RATE_EN_REG                        0x28
#define TOUCHKEY4_SIGNAL_GUARD_EN_REG                       0x29
#define TOUCHKEY4_MULTIPLE_TOUCH_CONFIG_REG                 0x2A
#define TOUCHKEY4_MULTIPLE_TOUCH_PATTERN_CONFIG_REG         0x2B
#define TOUCHKEY4_MULTIPLE_TOUCH_PATTERN_REG                0x2D
#define TOUCHKEY4_BASE_CNT_LIMIT_REG                        0x2E
#define TOUCHKEY4_RECALIB_CONFIG_REG                        0x2F
#define TOUCHKEY4_SENS_IN1_THRESHOLD_REG                    0x30
#define TOUCHKEY4_SENS_IN2_THRESHOLD_REG                    0x31
#define TOUCHKEY4_SENS_IN3_THRESHOLD_REG                    0x32
#define TOUCHKEY4_SENS_IN_NOISE_THRESHOLD_REG               0x38
#define TOUCHKEY4_STANDBY_CHANN_REG                         0x40
#define TOUCHKEY4_STANDBY_CONFIG_REG                        0x41
#define TOUCHKEY4_STANDBY_SENSITIVITY_REG                   0x42
#define TOUCHKEY4_STANDBY_THRESHOLD_REG                     0x43
#define TOUCHKEY4_CONFIG2_REG                               0x44
#define TOUCHKEY4_SENS_IN1_BASE_CNT_REG                     0x50
#define TOUCHKEY4_SENS_IN2_BASE_CNT_REG                     0x51
#define TOUCHKEY4_SENS_IN3_BASE_CNT_REG                     0x52
#define TOUCHKEY4_POWER_BUTTON_REG                          0x60
#define TOUCHKEY4_POWER_BUTTON_CONFIG_REG                   0x61
#define TOUCHKEY4_CALIB_SENSITIVITY_CONFIG_REG              0x80
#define TOUCHKEY4_SENS_IN1_CALIB_REG                        0xB1
#define TOUCHKEY4_SENS_IN2_CALIB_REG                        0xB2
#define TOUCHKEY4_SENS_IN3_CALIB_REG                        0xB3
#define TOUCHKEY4_SENS_IN_CALIB_LSB1_REG                    0xB9
#define TOUCHKEY4_PRODUCT_ID_REG                            0xFD
#define TOUCHKEY4_MANUFACT_ID_REG                           0xFE
#define TOUCHKEY4_REVISION_REG                              0xFF
/** \} */

/**
 * \defgroup sensitivity_control Sensitivity Control
 * \{
 */
#define TOUCHKEY4_SENSITIVITY_MULTIPLIER_128X               0x00
#define TOUCHKEY4_SENSITIVITY_MULTIPLIER_64X                0x10
#define TOUCHKEY4_SENSITIVITY_MULTIPLIER_32X                0x20
#define TOUCHKEY4_SENSITIVITY_MULTIPLIER_16X                0x30
#define TOUCHKEY4_SENSITIVITY_MULTIPLIER_8X                 0x40
#define TOUCHKEY4_SENSITIVITY_MULTIPLIER_4X                 0x50
#define TOUCHKEY4_SENSITIVITY_MULTIPLIER_2X                 0x60
#define TOUCHKEY4_SENSITIVITY_MULTIPLIER_1X                 0x70
#define TOUCHKEY4_DATA_SCALING_FACTOR_1X                    0x00
#define TOUCHKEY4_DATA_SCALING_FACTOR_2X                    0x01
#define TOUCHKEY4_DATA_SCALING_FACTOR_4X                    0x02
#define TOUCHKEY4_DATA_SCALING_FACTOR_8X                    0x03
#define TOUCHKEY4_DATA_SCALING_FACTOR_16X                   0x04
#define TOUCHKEY4_DATA_SCALING_FACTOR_32X                   0x05
#define TOUCHKEY4_DATA_SCALING_FACTOR_64X                   0x06
#define TOUCHKEY4_DATA_SCALING_FACTOR_128X                  0x07
#define TOUCHKEY4_DATA_SCALING_FACTOR_256X                  0x08
/** \} */

/**
 * \defgroup config_register_1 Configuration 1 Register
 * \{
 */
#define TOUCHKEY4_TIMEOUT_DIS                               0x00
#define TOUCHKEY4_TIMEOUT_EN                                0x80
#define TOUCHKEY4_DIG_NOISE_THRESHOLD_EN                    0x00
#define TOUCHKEY4_DIG_NOISE_THRESHOLD_DIS                   0x20
#define TOUCHKEY4_AN_NOISE_FILTER_EN                        0x00
#define TOUCHKEY4_AN_NOISE_FILTER_DIS                       0x10
#define TOUCHKEY4_MAX_DUR_RECALIB_DIS                       0x00
#define TOUCHKEY4_MAX_DUR_RECALIB_EN                        0x08
/** \} */

/**
 * \defgroup config_register_2 Configuration 2 Register
 * \{
 */
#define TOUCHKEY4_AN_CALIB_NO_RETRY                         0x00
#define TOUCHKEY4_AN_CALIB_RETRY                            0x40
#define TOUCHKEY4_POWER_CONSUMPTION_REDUCE_EN               0x00
#define TOUCHKEY4_POWER_CONSUMPTION_REDUCE_DIS              0x20
#define TOUCHKEY4_BASE_CNT_OUT_LIMIT_INTERR_DIS             0x00
#define TOUCHKEY4_BASE_CNT_OUT_LIMIT_INTERR_EN              0x10
#define TOUCHKEY4_SHOW_LOW_FREQ_NOISE                       0x00
#define TOUCHKEY4_NOT_SHOW_LOW_FREQ_NOISE                   0x08
#define TOUCHKEY4_RF_NOISE_FILTER_EN                        0x00
#define TOUCHKEY4_RF_NOISE_FILTER_DIS                       0x04
#define TOUCHKEY4_AN_CALIB_FAIL_INTERR_DIS                  0x00
#define TOUCHKEY4_AN_CALIB_FAIL_INTERR_EN                   0x02
#define TOUCHKEY4_DETECT_RELEASE_EN                         0x00
#define TOUCHKEY4_DETECT_RELEASE_DIS                        0x01
/** \} */

/**
 * \defgroup sensor_input_config_register_1 Sensor Input Configuration 1 Register
 * \{
 */
#define TOUCHKEY4_560MILISEC_BEFORE_RECALIB                 0x00
#define TOUCHKEY4_840MILISEC_BEFORE_RECALIB                 0x10
#define TOUCHKEY4_1120MILISEC_BEFORE_RECALIB                0x20
#define TOUCHKEY4_1400MILISEC_BEFORE_RECALIB                0x30
#define TOUCHKEY4_1680MILISEC_BEFORE_RECALIB                0x40
#define TOUCHKEY4_2240MILISEC_BEFORE_RECALIB                0x50
#define TOUCHKEY4_2800MILISEC_BEFORE_RECALIB                0x60
#define TOUCHKEY4_3360MILISEC_BEFORE_RECALIB                0x70
#define TOUCHKEY4_3920MILISEC_BEFORE_RECALIB                0x80
#define TOUCHKEY4_4480MILISEC_BEFORE_RECALIB                0x90
#define TOUCHKEY4_5600MILISEC_BEFORE_RECALIB                0xA0
#define TOUCHKEY4_6720MILISEC_BEFORE_RECALIB                0xB0
#define TOUCHKEY4_7840MILISEC_BEFORE_RECALIB                0xC0
#define TOUCHKEY4_8906MILISEC_BEFORE_RECALIB                0xD0
#define TOUCHKEY4_10080MILISEC_BEFORE_RECALIB               0xE0
#define TOUCHKEY4_11200MILISEC_BEFORE_RECALIB               0xF0
#define TOUCHKEY4_INTERR_REPEAT_RATE_35MILISEC              0x00
#define TOUCHKEY4_INTERR_REPEAT_RATE_70MILISEC              0x01
#define TOUCHKEY4_INTERR_REPEAT_RATE_105MILISEC             0x02
#define TOUCHKEY4_INTERR_REPEAT_RATE_140MILISEC             0x03
#define TOUCHKEY4_INTERR_REPEAT_RATE_175MILISEC             0x04
#define TOUCHKEY4_INTERR_REPEAT_RATE_210MILISEC             0x05
#define TOUCHKEY4_INTERR_REPEAT_RATE_245MILISEC             0x06
#define TOUCHKEY4_INTERR_REPEAT_RATE_280MILISEC             0x07
#define TOUCHKEY4_INTERR_REPEAT_RATE_315MILISEC             0x08
#define TOUCHKEY4_INTERR_REPEAT_RATE_350MILISEC             0x09
#define TOUCHKEY4_INTERR_REPEAT_RATE_385MILISEC             0x0A
#define TOUCHKEY4_INTERR_REPEAT_RATE_420MILISEC             0x0B
#define TOUCHKEY4_INTERR_REPEAT_RATE_455MILISEC             0x0C
#define TOUCHKEY4_INTERR_REPEAT_RATE_490MILISEC             0x0D
#define TOUCHKEY4_INTERR_REPEAT_RATE_525MILISEC             0x0E
#define TOUCHKEY4_INTERR_REPEAT_RATE_560MILISEC             0x0F
/** \} */

/**
 * \defgroup sensor_input_config_register_2 Sensor Input Configuration 2 Register
 * \{
 */
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_35MILISEC      0x00
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_70MILISEC      0x01
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_105MILISEC     0x02
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_140MILISEC     0x03
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_175MILISEC     0x04
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_210MILISEC     0x05
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_245MILISEC     0x06
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_280MILISEC     0x07
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_315MILISEC     0x08
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_350MILISEC     0x09
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_385MILISEC     0x0A
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_420MILISEC     0x0B
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_455MILISEC     0x0C
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_490MILISEC     0x0D
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_525MILISEC     0x0E
#define TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_560MILISEC     0x0F
/** \} */

/**
 * \defgroup averaging_sampling_standby_reg Averaging Sampling and Standby Configuration Register
 * \{
 */
#define TOUCHKEY4_1_SAMPLE                                  0x00
#define TOUCHKEY4_2_SAMPLES                                 0x10
#define TOUCHKEY4_4_SAMPLES                                 0x20
#define TOUCHKEY4_8_SAMPLES                                 0x30
#define TOUCHKEY4_16_SAMPLES                                0x40
#define TOUCHKEY4_32_SAMPLES                                0x50
#define TOUCHKEY4_64_SAMPLES                                0x60
#define TOUCHKEY4_128_SAMPLES                               0x70
#define TOUCHKEY4_SAMPLE_TIME_320MICROSEC                   0x00
#define TOUCHKEY4_SAMPLE_TIME_640MICROSEC                   0x04
#define TOUCHKEY4_SAMPLE_TIME_1280MICROSEC                  0x08
#define TOUCHKEY4_SAMPLE_TIME_2560MICROSEC                  0x0C
#define TOUCHKEY4_CYCLE_TIME_35MILISEC                      0x00
#define TOUCHKEY4_CYCLE_TIME_70MILISEC                      0x01
#define TOUCHKEY4_CYCLE_TIME_105MILISEC                     0x02
#define TOUCHKEY4_CYCLE_TIME_140MILISEC                     0x03
/** \} */

/**
 * \defgroup calibration_activate_and_status_reg Calibration Activate and Status Register
 * \{
 */
#define TOUCHKEY4_ALL_INPUTS_CALIB_DIS                      0x00
#define TOUCHKEY4_INPUT1_CALIB_EN                           0x01
#define TOUCHKEY4_INPUT2_CALIB_EN                           0x02
#define TOUCHKEY4_INPUT3_CALIB_EN                           0x04
/** \} */

/**
 * \defgroup interrupt_enable Interrupt Enable Options
 * \{
 */
#define TOUCHKEY4_ALL_INPUTS_INTERR_DIS                     0x00
#define TOUCHKEY4_INPUT1_INTERR_EN                          0x01
#define TOUCHKEY4_INPUT2_INTERR_EN                          0x02
#define TOUCHKEY4_INPUT3_INTERR_EN                          0x04
/** \} */

/**
 * \defgroup repeat_rate_enable_reg Options for Repeat Rate Enable Register
 * \{
 */
#define TOUCHKEY4_REPEAT_RATE_DIS                           0x00
#define TOUCHKEY4_INPUT1_REPEAT_RATE_EN                     0x01
#define TOUCHKEY4_INPUT2_REPEAT_RATE_EN                     0x02
#define TOUCHKEY4_INPUT3_REPEAT_RATE_EN                     0x04
 /** \} */

 /**
 * \defgroup signal_guard_enable_reg Options for Signal Guard Enable Register
 * \{
 */
#define TOUCHKEY4_SIGNAL_GUARD_DIS                          0x00
#define TOUCHKEY4_INPUT1_SIGNAL_GUARD_EN                    0x01
#define TOUCHKEY4_INPUT3_SIGNAL_GUARD_EN                    0x04
 /** \} */

 /**
 * \defgroup multiple_touch_config_reg Options for Multiple Touch Config Register
 * \{
 */
#define TOUCHKEY4_MULTIPLE_BLOCK_DIS                        0x00
#define TOUCHKEY4_MULTIPLE_BLOCK_EN                         0x80
#define TOUCHKEY4_SIMUL_TOUCH_NUM_1                         0x00
#define TOUCHKEY4_SIMUL_TOUCH_NUM_2                         0x04
#define TOUCHKEY4_SIMUL_TOUCH_NUM_3                         0x08
 /** \} */

/**
 * \defgroup multiple_touch_pattern_config_reg Options for Multiple Touch Pattern Config Register
 * \{
 */
#define TOUCHKEY4_MULTIPLE_THRESHOLD_12_PERCENTS            0x00
#define TOUCHKEY4_MULTIPLE_THRESHOLD_25_PERCENTS            0x04
#define TOUCHKEY4_MULTIPLE_THRESHOLD_37_PERCENTS            0x08
#define TOUCHKEY4_MULTIPLE_THRESHOLD_100_PERCENTS           0x0C
#define TOUCHKEY4_MLTP_TOUCH_PATTERN                        0x00
#define TOUCHKEY4_PATTERN_RECOGNITION                       0x02
#define TOUCHKEY4_MLTP_EVENT_ALERT_DIS                      0x00
#define TOUCHKEY4_MLTP_EVENT_ALERT_EN                       0x01
 /** \} */

/**
 * \defgroup multiple_touch_pattern_reg Options for Multiple Touch Pattern Register
 * \{
 */
#define TOUCHKEY4_MLTP_TOUCH_PATTERN_INPUTS_DIS             0x00
#define TOUCHKEY4_MLTP_TOUCH_PATTERN_INPUT1_EN              0x01
#define TOUCHKEY4_MLTP_TOUCH_PATTERN_INPUT2_EN              0x02
#define TOUCHKEY4_MLTP_TOUCH_PATTERN_INPUT3_EN              0x04
 /** \} */

/**
 * \defgroup recalibration_config_reg Options for Recalibration Configuration Register
 * \{
 */
#define TOUCHKEY4_INPUTS_THRESHOLD_UPDT_INDIVIDUALY         0x00
#define TOUCHKEY4_INPUT1_THRESHOLD_OVERWRITE                0x80
#define TOUCHKEY4_ACC_INTER_DATA_CLEAR                      0x00
#define TOUCHKEY4_ACC_INTER_DATA_NOT_CLEAR                  0x40
#define TOUCHKEY4_CONS_NEG_DELTA_CNT_CLEAR                  0x00
#define TOUCHKEY4_CONS_NEG_DELTA_CNT_NOT_CLEAR              0x20
#define TOUCHKEY4_CONS_NEG_DELTA_CNT_8                      0x00
#define TOUCHKEY4_CONS_NEG_DELTA_CNT_16                     0x08
#define TOUCHKEY4_CONS_NEG_DELTA_CNT_32                     0x10
#define TOUCHKEY4_CONS_NEG_DELTA_CNT_DIS                    0x18
#define TOUCHKEY4_REC_SAMPLES_16_UPDT_TIME_16               0x00
#define TOUCHKEY4_REC_SAMPLES_32_UPDT_TIME_32               0x01
#define TOUCHKEY4_REC_SAMPLES_64_UPDT_TIME_64               0x02
#define TOUCHKEY4_REC_SAMPLES_128_UPDT_TIME_128             0x03
#define TOUCHKEY4_REC_SAMPLES_256_UPDT_TIME_256             0x04
#define TOUCHKEY4_REC_SAMPLES_256_UPDT_TIME_1024            0x05
#define TOUCHKEY4_REC_SAMPLES_256_UPDT_TIME_2048            0x06
#define TOUCHKEY4_REC_SAMPLES_256_UPDT_TIME_4096            0x07
 /** \} */

/**
 * \defgroup standby_config_reg Options for Standby Configuration Register
 * \{
 */ 
#define TOUCHKEY4_AVERAGE_BASED                             0x00
#define TOUCHKEY4_SUMMATION_BASED                           0x80
 /** \} */

/**
 * \defgroup standby_sensitivity_reg Options for Standby Sensitivity Register
 * \{
 */
#define TOUCHKEY4_STBY_SENSE_MULTIPLIER_128X                0x00
#define TOUCHKEY4_STBY_SENSE_MULTIPLIER_64X                 0x01
#define TOUCHKEY4_STBY_SENSE_MULTIPLIER_32X                 0x02
#define TOUCHKEY4_STBY_SENSE_MULTIPLIER_16X                 0x03
#define TOUCHKEY4_STBY_SENSE_MULTIPLIER_8X                  0x04
#define TOUCHKEY4_STBY_SENSE_MULTIPLIER_4X                  0x05
#define TOUCHKEY4_STBY_SENSE_MULTIPLIER_2X                  0x06
#define TOUCHKEY4_STBY_SENSE_MULTIPLIER_1X                  0x07
 /** \} */

/**
 * \defgroup power_btn_reg Options for Power Button Register
 * \{
 */
#define TOUCHKEY4_INPUT1_POWER_BUTTON                       0x00
#define TOUCHKEY4_INPUT2_POWER_BUTTON                       0x01
#define TOUCHKEY4_INPUT3_POWER_BUTTON                       0x02
 /** \} */

/**
 * \defgroup power_btn_config_reg Options for Power Button Configuration Register
 * \{
 */
#define TOUCHKEY4_STBY_POWER_BUTTON_DIS                     0x00
#define TOUCHKEY4_STBY_POWER_BUTTON_EN                      0x40
#define TOUCHKEY4_PWR_BUTT_TOUCH_HOLD_280MILISEC            0x00
#define TOUCHKEY4_PWR_BUTT_TOUCH_HOLD_560MILISEC            0x11
#define TOUCHKEY4_PWR_BUTT_TOUCH_HOLD_1120MILISEC           0x22
#define TOUCHKEY4_PWR_BUTT_TOUCH_HOLD_2240MILISEC           0x33
#define TOUCHKEY4_ACT_POWER_BUTTON_DIS                      0x00
#define TOUCHKEY4_ACT_POWER_BUTTON_EN                       0x04
/** \} */

/**
 * \defgroup selective_parameters Selective Parameters for functions
 * \{
 */
#define TOUCHKEY4_GAIN_1                                    0x01
#define TOUCHKEY4_GAIN_2                                    0x02
#define TOUCHKEY4_GAIN_4                                    0x04
#define TOUCHKEY4_GAIN_8                                    0x08
#define TOUCHKEY4_SENS_INPUT_DIS                            0x00
#define TOUCHKEY4_SENS_INPUT_EN                             0x01
#define TOUCHKEY4_COMBO_SENS_IN_ACT_EN                      0x03
#define TOUCHKEY4_COMBO_SENS_IN_STBY_EN                     0x01
#define TOUCHKEY4_COMBO_SENS_IN_BOTH_MODES_EN               0x05
 /** \} */

/**
 * \defgroup slave_addr Slave Address
 * \{
 */
#define TOUCHKEY4_SLAVE_ADDRESS                             0x28
 /** \} */


/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} touchkey4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} touchkey4_cfg_t;

/** \} */ // End types group

// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void touchkey4_cfg_setup ( touchkey4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TOUCHKEY4_RETVAL touchkey4_init ( touchkey4_t *ctx, touchkey4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets some registers to certain values in order to initialize 
 * device.
 */
void touchkey4_default_cfg ( touchkey4_t *ctx );

/**
 * @brief Generic Write function
 *
 * @param ctx                   Click object.
 * @param register_address      Address where data be written.
 * @param transfer_data         Data which be written.
 *
 * @description This function writes one byte to register.
 */
void touchkey4_write_reg( touchkey4_t *ctx, const uint8_t register_address, 
                          const uint8_t transfer_data );

/**
 * @brief Generic Read function
 *
 * @param ctx                       Click object.
 * @param register_address          Address which from data be read.
 * @param data_out                  Buffer where data be stored.
 * @param n_bytes                   Number of bytes which be read.
 *
 * @description This function reads data from register.
 */
void touchkey4_read_reg ( touchkey4_t *ctx, const uint8_t register_address, 
                         uint8_t *data_out, const uint8_t n_bytes );

/**
 * @brief Read byte function
 *
 * @param ctx                       Click object.
 * @param register_address          Address which from data be read.
 * 
 * @retval Read byte
 *
 * @description This function reads data from register.
 */
uint8_t touchkey4_receive_byte( touchkey4_t *ctx, const uint8_t register_address );

/**
 * @brief Touch Detect function
 *
 * @param ctx                      Click object.
 * @param input_sens               Results of detecting touch on sensor inputs.
 *
 * @description This function detects touch on sensor inputs and checks is touch detected or released.
 * If noise occured on determined input, the touch will not be detected.
 */
void touchkey4_detect_touch ( touchkey4_t *ctx, uint8_t *input_sens );

/**
 * @brief Active Mode Set function
 *
 * @param ctx                  Click object.
 * @param analog_gain          Possible gain value is 1, 2, 4 or 8.
 * @param en_input1            Enable or disable sensor input 1.
 * @param en_input2            Enable or disable sensor input 2.
 * @param en_input3            Enable or disable sensor input 3.
 *
 * @description This function puts device in Active mode and enables desired inputs in Active mode.
 *
 * @note 
 * <pre> 1 - enable sensor input, 0 - disable sensor input </pre>
 */
void touchkey4_set_active_mode ( touchkey4_t *ctx, const uint8_t analog_gain, const uint8_t en_input1,const uint8_t en_input2, const uint8_t en_input3 );

/**
 * @brief Standby Mode Set function
 *
 * @param ctx                  Click object.
 * @param analog_gain          Possible gain value is 1, 2, 4 or 8.
 * @param en_input1            Enable or disable sensor input 1.
 * @param en_input2            Enable or disable sensor input 2.
 * @param en_input3            Enable or disable sensor input 3.
 *
 * @description This function puts device in Standby mode and enables desired inputs in Standby mode.
 *
 * @note
 * <pre> 1 - enable sensor input, 0 - disable sensor input </pre>
 *
 */
void touchkey4_set_standby_mode ( touchkey4_t *ctx, const uint8_t analog_gain, const uint8_t en_input1,
                                 const uint8_t en_input2, const uint8_t en_input3 );

/**
 * @brief Combo Mode Set function
 *
 * @param ctx                  Click object.
 * @param analog_gain          Possible gain value is 1, 2, 4 or 8.
 * @param en_input1            Enable or disable sensor input 1.
 * @param en_input2            Enable or disable sensor input 2.
 * @param en_input3            Enable or disable sensor input 3.
 *
 * @description Function puts device in Combo mode (Active and Standby) and enables desired inputs in Active mode,
 * Standby mode or both modes.
 *
 * @note 
 * <pre> 0 - disable input, 1 - enable input in Standby mode, 3 - enable input in Active mode,
 *       5 - enable input in both modes </pre>
 */
void touchkey4_set_combo_mode ( touchkey4_t *ctx, const uint8_t analog_gain, const uint8_t en_input1, const uint8_t en_input2, const uint8_t en_input3 );

/**
 * @brief DeepSleep Mode Set function
 *
 * @param ctx                  Click object.
 *
 * @description This function puts device in DeepSleep mode.
 *
 * @note 
 * <pre> In this mode the I2C communication will not work and the sensor inputs will not detect touch. </pre>
 *
 */
void touchkey4_set_deep_sleep_mode ( touchkey4_t *ctx );

/**
 * @brief Interrupt Check function
 *
 * @param ctx                  Click object.
 *
 * @returns State of ALERT pin, 0 or 1.
 *
 * @description This function checks interrupt state (ALERT pin).
 */
uint8_t touchkey4_check_interrupt ( touchkey4_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _TOUCHKEY4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
