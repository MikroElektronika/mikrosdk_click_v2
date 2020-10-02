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
 * \brief This file contains API for Cap Touch 2 Click driver.
 *
 * \addtogroup captouch2 Cap Touch 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CAPTOUCH2_H
#define CAPTOUCH2_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define CAPTOUCH2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.alt   = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CAPTOUCH2_RETVAL  uint8_t

#define CAPTOUCH2_OK           0x00
#define CAPTOUCH2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define CAPTOUCH2_MAIN_CONTROL_REG                   0x00
#define CAPTOUCH2_GEN_STATUS_REG                     0x02
#define CAPTOUCH2_SENS_IN_STATUS_REG                 0x03
#define CAPTOUCH2_NOISE_FLAG_REG                     0x0A
#define CAPTOUCH2_SENS_IN1_DELTA_CNT_REG             0x10
#define CAPTOUCH2_SENS_IN2_DELTA_CNT_REG             0x11
#define CAPTOUCH2_SENS_IN3_DELTA_CNT_REG             0x12
#define CAPTOUCH2_SENS_IN4_DELTA_CNT_REG             0x13
#define CAPTOUCH2_SENS_IN5_DELTA_CNT_REG             0x14
#define CAPTOUCH2_SENS_IN6_DELTA_CNT_REG             0x15
#define CAPTOUCH2_SENSITIVITY_CON_REG                0x1F
#define CAPTOUCH2_CONFIG_REG                         0x20
#define CAPTOUCH2_SENS_IN_EN_REG                     0x21
#define CAPTOUCH2_SENS_IN_CONFIG_REG                 0x22
#define CAPTOUCH2_SENS_IN_CONFIG2_REG                0x23
#define CAPTOUCH2_AVRG_AND_SAMPL_CONFIG_REG          0x24
#define CAPTOUCH2_CALIB_ACTIVATE_REG                 0x26
#define CAPTOUCH2_INTERR_EN_REG                      0x27
#define CAPTOUCH2_REPEAT_RATE_EN_REG                 0x28
#define CAPTOUCH2_MULTIPLE_TOUCH_CONFIG_REG          0x2A
#define CAPTOUCH2_MULTIPLE_TOUCH_PATTERN_CONFIG_REG  0x2B
#define CAPTOUCH2_MULTIPLE_TOUCH_PATTERN_REG         0x2D
#define CAPTOUCH2_RECALIB_CONFIG_REG                 0x2F
#define CAPTOUCH2_SENS_IN1_THRESHOLD_REG             0x30
#define CAPTOUCH2_SENS_IN2_THRESHOLD_REG             0x31
#define CAPTOUCH2_SENS_IN3_THRESHOLD_REG             0x32
#define CAPTOUCH2_SENS_IN4_THRESHOLD_REG             0x33
#define CAPTOUCH2_SENS_IN5_THRESHOLD_REG             0x34
#define CAPTOUCH2_SENS_IN6_THRESHOLD_REG             0x35
#define CAPTOUCH2_SENS_IN_NOISE_THRESHOLD_REG        0x38
#define CAPTOUCH2_STANDBY_CHANN_REG                  0x40
#define CAPTOUCH2_STANDBY_CONFIG_REG                 0x41
#define CAPTOUCH2_STANDBY_SENSITIVITY_REG            0x42
#define CAPTOUCH2_STANDBY_THRESHOLD_REG              0x43
#define CAPTOUCH2_CONFIG2_REG                        0x44
#define CAPTOUCH2_SENS_IN1_BASE_CNT_REG              0x50
#define CAPTOUCH2_SENS_IN2_BASE_CNT_REG              0x51
#define CAPTOUCH2_SENS_IN3_BASE_CNT_REG              0x52
#define CAPTOUCH2_SENS_IN4_BASE_CNT_REG              0x53
#define CAPTOUCH2_SENS_IN5_BASE_CNT_REG              0x54
#define CAPTOUCH2_SENS_IN6_BASE_CNT_REG              0x55
#define CAPTOUCH2_LED_OUTPUT_TYPE_REG                0x71
#define CAPTOUCH2_SENS_IN_LED_LINK_REG               0x72
#define CAPTOUCH2_LED_POLARITY_REG                   0x73
#define CAPTOUCH2_LED_OUT_CON_REG                    0x74
#define CAPTOUCH2_LED_LINK_TRANS_CON_REG             0x77
#define CAPTOUCH2_LED_MIRROR_CON_REG                 0x79
#define CAPTOUCH2_LED_BEHAVIOR1_REG                  0x81
#define CAPTOUCH2_LED_BEHAVIOR2_REG                  0x82
#define CAPTOUCH2_LED_PULSE1_PERIOD_REG              0x84
#define CAPTOUCH2_LED_PULSE2_PERIOD_REG              0x85
#define CAPTOUCH2_LED_BREATHE_PERIOD_REG             0x86
#define CAPTOUCH2_LED_CONFIG_REG                     0x88
#define CAPTOUCH2_LED_PULSE1_DUTY_REG                0x90
#define CAPTOUCH2_LED_PULSE2_DUTY_REG                0x91
#define CAPTOUCH2_LED_BREATHE_DUTY_REG               0x92
#define CAPTOUCH2_LED_DIRECT_DUTY_REG                0x93
#define CAPTOUCH2_LED_DIRECT_RAMP_RATES_REG          0x94
#define CAPTOUCH2_LED_OFF_DELAY_REG                  0x95
#define CAPTOUCH2_SENS_IN1_CALIB_REG                 0xB1
#define CAPTOUCH2_SENS_IN2_CALIB_REG                 0xB2
#define CAPTOUCH2_SENS_IN3_CALIB_REG                 0xB3
#define CAPTOUCH2_SENS_IN4_CALIB_REG                 0xB4
#define CAPTOUCH2_SENS_IN5_CALIB_REG                 0xB5
#define CAPTOUCH2_SENS_IN6_CALIB_REG                 0xB6
#define CAPTOUCH2_SENS_IN_CALIB_LSB1_REG             0xB9
#define CAPTOUCH2_SENS_IN_CALIB_LSB2_REG             0xBA
#define CAPTOUCH2_PRODUCT_ID_REG                     0xFD
#define CAPTOUCH2_MANUFACT_ID_REG                    0xFE
#define CAPTOUCH2_REVISION_REG                       0xFF
/** \} */

/**
 * \defgroup sensitivity_control Sensitivity Control
 * \{
 */
#define CAPTOUCH2_SENSITIVITY_MULTIPLIER_128X 0x00
#define CAPTOUCH2_SENSITIVITY_MULTIPLIER_64X  0x10
#define CAPTOUCH2_SENSITIVITY_MULTIPLIER_32X  0x20
#define CAPTOUCH2_SENSITIVITY_MULTIPLIER_16X  0x30
#define CAPTOUCH2_SENSITIVITY_MULTIPLIER_8X   0x40
#define CAPTOUCH2_SENSITIVITY_MULTIPLIER_4X   0x50
#define CAPTOUCH2_SENSITIVITY_MULTIPLIER_2X   0x60
#define CAPTOUCH2_SENSITIVITY_MULTIPLIER_1X   0x70
#define CAPTOUCH2_DATA_SCALING_FACTOR_1X      0x00
#define CAPTOUCH2_DATA_SCALING_FACTOR_2X      0x01
#define CAPTOUCH2_DATA_SCALING_FACTOR_4X      0x02
#define CAPTOUCH2_DATA_SCALING_FACTOR_8X      0x03
#define CAPTOUCH2_DATA_SCALING_FACTOR_16X     0x04
#define CAPTOUCH2_DATA_SCALING_FACTOR_32X     0x05
#define CAPTOUCH2_DATA_SCALING_FACTOR_64X     0x06
#define CAPTOUCH2_DATA_SCALING_FACTOR_128X    0x07
#define CAPTOUCH2_DATA_SCALING_FACTOR_256X    0x08
/** \} */

/**
 * \defgroup  configuration  Configuration
 * \{
 */
#define CAPTOUCH2_TIMEOUT_DIS             0x00
#define CAPTOUCH2_TIMEOUT_EN              0x80
#define CAPTOUCH2_WAKE_PIN_NOT_ASSERTED   0x00
#define CAPTOUCH2_WAKE_PIN_ASSERTED       0x40
#define CAPTOUCH2_DIG_NOISE_THRESHOLD_EN  0x00
#define CAPTOUCH2_DIG_NOISE_THRESHOLD_DIS 0x20
#define CAPTOUCH2_AN_NOISE_FILTER_EN      0x00
#define CAPTOUCH2_AN_NOISE_FILTER_DIS     0x10
#define CAPTOUCH2_MAX_DUR_RECALIB_DIS     0x00
#define CAPTOUCH2_MAX_DUR_RECALIB_EN      0x08
/** \} */

/**
 * \defgroup configuration_2  Configuration 2 
 * \{
 */
#define CAPTOUCH2_NOT_INVERT_TOUCH_SIGNAL        0x00
#define CAPTOUCH2_INVERT_TOUCH_SIGNAL            0x80
#define CAPTOUCH2_ALERT_ACTIVE_HIGH              0x00
#define CAPTOUCH2_ALERT_ACTIVE_LOW               0x40
#define CAPTOUCH2_POWER_CONSUMPTION_REDUCE_EN    0x00
#define CAPTOUCH2_POWER_CONSUMPTION_REDUCE_DIS   0x20
#define CAPTOUCH2_AUTOSET_LED_MIRROR_CON         0x00
#define CAPTOUCH2_NOT_AUTOSET_LED_MIRROR_CON     0x10
#define CAPTOUCH2_SHOW_LOW_FREQ_NOISE            0x00
#define CAPTOUCH2_NOT_SHOW_LOW_FREQ_NOISE        0x08
#define CAPTOUCH2_RF_NOISE_FILTER_EN             0x00
#define CAPTOUCH2_RF_NOISE_FILTER_DIS            0x04
#define CAPTOUCH2_AN_CALIB_FAIL_INTERR_DIS       0x00
#define CAPTOUCH2_AN_CALIB_FAIL_INTERR_EN        0x02
#define CAPTOUCH2_DETECT_RELEASE_EN              0x00
#define CAPTOUCH2_DETECT_RELEASE_DIS             0x01
/** \} */

/**
 * \defgroup sensor_input_config Sensor Input Configuration
 * \{
 */
#define CAPTOUCH2_560MILISEC_BEFORE_RECALIB     0x00
#define CAPTOUCH2_840MILISEC_BEFORE_RECALIB     0x10
#define CAPTOUCH2_1120MILISEC_BEFORE_RECALIB    0x20
#define CAPTOUCH2_1400MILISEC_BEFORE_RECALIB    0x30
#define CAPTOUCH2_1680MILISEC_BEFORE_RECALIB    0x40
#define CAPTOUCH2_2240MILISEC_BEFORE_RECALIB    0x50
#define CAPTOUCH2_2800MILISEC_BEFORE_RECALIB    0x60
#define CAPTOUCH2_3360MILISEC_BEFORE_RECALIB    0x70
#define CAPTOUCH2_3920MILISEC_BEFORE_RECALIB    0x80
#define CAPTOUCH2_4480MILISEC_BEFORE_RECALIB    0x90
#define CAPTOUCH2_5600MILISEC_BEFORE_RECALIB    0xA0
#define CAPTOUCH2_6720MILISEC_BEFORE_RECALIB    0xB0
#define CAPTOUCH2_7840MILISEC_BEFORE_RECALIB    0xC0
#define CAPTOUCH2_8906MILISEC_BEFORE_RECALIB    0xD0
#define CAPTOUCH2_10080MILISEC_BEFORE_RECALIB   0xE0
#define CAPTOUCH2_11200MILISEC_BEFORE_RECALIB   0xF0
#define CAPTOUCH2_INTERR_REPEAT_RATE_35MILISEC    0x00
#define CAPTOUCH2_INTERR_REPEAT_RATE_70MILISEC    0x01
#define CAPTOUCH2_INTERR_REPEAT_RATE_105MILISEC   0x02
#define CAPTOUCH2_INTERR_REPEAT_RATE_140MILISEC   0x03
#define CAPTOUCH2_INTERR_REPEAT_RATE_175MILISEC   0x04
#define CAPTOUCH2_INTERR_REPEAT_RATE_210MILISEC   0x05
#define CAPTOUCH2_INTERR_REPEAT_RATE_245MILISEC   0x06
#define CAPTOUCH2_INTERR_REPEAT_RATE_280MILISEC   0x07
#define CAPTOUCH2_INTERR_REPEAT_RATE_315MILISEC   0x08
#define CAPTOUCH2_INTERR_REPEAT_RATE_350MILISEC   0x09
#define CAPTOUCH2_INTERR_REPEAT_RATE_385MILISEC   0x0A
#define CAPTOUCH2_INTERR_REPEAT_RATE_420MILISEC   0x0B
#define CAPTOUCH2_INTERR_REPEAT_RATE_455MILISEC   0x0C
#define CAPTOUCH2_INTERR_REPEAT_RATE_490MILISEC   0x0D
#define CAPTOUCH2_INTERR_REPEAT_RATE_525MILISEC   0x0E
#define CAPTOUCH2_INTERR_REPEAT_RATE_560MILISEC   0x0F
/** \} */

/**
 * \defgroup hold_event Hold Event
 * \{
 */
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_35MILISEC   0x00
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_70MILISEC   0x01
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_105MILISEC  0x02
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_140MILISEC  0x03
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_175MILISEC  0x04
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_210MILISEC  0x05
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_245MILISEC  0x06
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_280MILISEC  0x07
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_315MILISEC  0x08
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_350MILISEC  0x09
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_385MILISEC  0x0A
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_420MILISEC  0x0B
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_455MILISEC  0x0C
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_490MILISEC  0x0D
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_525MILISEC  0x0E
#define CAPTOUCH2_PRESS_AND_HOLD_EVENT_AFTER_560MILISEC  0x0F
/** \} */

/**
 * \defgroup averaging_sampling_config Averaging/Sampling Config
 * \{
 */
#define CAPTOUCH2_1_SAMPLE     0x00
#define CAPTOUCH2_2_SAMPLES    0x10
#define CAPTOUCH2_4_SAMPLES    0x20
#define CAPTOUCH2_8_SAMPLES    0x30
#define CAPTOUCH2_16_SAMPLES   0x40
#define CAPTOUCH2_32_SAMPLES   0x50
#define CAPTOUCH2_64_SAMPLES   0x60
#define CAPTOUCH2_128_SAMPLES  0x70
#define CAPTOUCH2_SAMPLE_TIME_320MICROSEC   0x00
#define CAPTOUCH2_SAMPLE_TIME_640MICROSEC   0x04
#define CAPTOUCH2_SAMPLE_TIME_1280MICROSEC  0x08
#define CAPTOUCH2_SAMPLE_TIME_2560MICROSEC  0x0C
#define CAPTOUCH2_CYCLE_TIME_35MILISEC   0x00
#define CAPTOUCH2_CYCLE_TIME_70MILISEC   0x01
#define CAPTOUCH2_CYCLE_TIME_105MILISEC  0x02
#define CAPTOUCH2_CYCLE_TIME_140MILISEC  0x03
/** \} */

/**
 * \defgroup in_calip_enable Input calib enable
 * \{
 */
#define CAPTOUCH2_ALL_INPUTS_CALIB_DIS  0x00
#define CAPTOUCH2_INPUT1_CALIB_EN       0x01
#define CAPTOUCH2_INPUT2_CALIB_EN       0x02
#define CAPTOUCH2_INPUT3_CALIB_EN       0x04
#define CAPTOUCH2_INPUT4_CALIB_EN       0x08
#define CAPTOUCH2_INPUT5_CALIB_EN       0x10
#define CAPTOUCH2_INPUT6_CALIB_EN       0x20
/** \} */

/**
 * \defgroup in_interr_enable Input error enable
 * \{
 */
#define CAPTOUCH2_ALL_INPUTS_INTERR_DIS   0x00
#define CAPTOUCH2_INPUT1_INTERR_EN        0x01
#define CAPTOUCH2_INPUT2_INTERR_EN        0x02
#define CAPTOUCH2_INPUT3_INTERR_EN        0x04
#define CAPTOUCH2_INPUT4_INTERR_EN        0x08
#define CAPTOUCH2_INPUT5_INTERR_EN        0x10
#define CAPTOUCH2_INPUT6_INTERR_EN        0x20
/** \} */

/**
 * \defgroup repeat_rate Repeat Rate
 * \{
 */
#define CAPTOUCH2_REPEAT_RATE_DIS        0x00
#define CAPTOUCH2_INPUT1_REPEAT_RATE_EN  0x01
#define CAPTOUCH2_INPUT2_REPEAT_RATE_EN  0x02
#define CAPTOUCH2_INPUT3_REPEAT_RATE_EN  0x04
#define CAPTOUCH2_INPUT4_REPEAT_RATE_EN  0x08
#define CAPTOUCH2_INPUT5_REPEAT_RATE_EN  0x10
#define CAPTOUCH2_INPUT6_REPEAT_RATE_EN  0x20
/** \} */

/**
 * \defgroup multiple_touch_config Multiple Touch Config
 * \{
 */
#define CAPTOUCH2_MULTIPLE_BLOCK_DIS  0x00
#define CAPTOUCH2_MULTIPLE_BLOCK_EN   0x80
#define CAPTOUCH2_SIMUL_TOUCH_NUM_1   0x00
#define CAPTOUCH2_SIMUL_TOUCH_NUM_2   0x04
#define CAPTOUCH2_SIMUL_TOUCH_NUM_3   0x08
#define CAPTOUCH2_SIMUL_TOUCH_NUM_4   0x0C
/** \} */

/**
 * \defgroup multiple_touch_pattern_cfg Multiple Touch Pattern Config
 * \{
 */
#define CAPTOUCH2_MULTIPLE_THRESHOLD_12_PERCENTS   0x00
#define CAPTOUCH2_MULTIPLE_THRESHOLD_25_PERCENTS   0x04
#define CAPTOUCH2_MULTIPLE_THRESHOLD_37_PERCENTS   0x08
#define CAPTOUCH2_MULTIPLE_THRESHOLD_100_PERCENTS  0x0C
#define CAPTOUCH2_MLTP_TOUCH_PATTERN    0x00
#define CAPTOUCH2_PATTERN_RECOGNITION   0x02
#define CAPTOUCH2_MLTP_EVENT_ALERT_DIS  0x00
#define CAPTOUCH2_MLTP_EVENT_ALERT_EN   0x01
/** \} */

/**
 * \defgroup multiple_touch_pattern Multiple Touch Pattern
 * \{
 */
#define CAPTOUCH2_MLTP_TOUCH_PATTERN_INPUTS_DIS  0x00
#define CAPTOUCH2_MLTP_TOUCH_PATTERN_INPUT1_EN  0x01
#define CAPTOUCH2_MLTP_TOUCH_PATTERN_INPUT2_EN  0x02
#define CAPTOUCH2_MLTP_TOUCH_PATTERN_INPUT3_EN  0x04
#define CAPTOUCH2_MLTP_TOUCH_PATTERN_INPUT4_EN  0x08
#define CAPTOUCH2_MLTP_TOUCH_PATTERN_INPUT5_EN  0x10
#define CAPTOUCH2_MLTP_TOUCH_PATTERN_INPUT6_EN  0x20
/** \} */

/**
 * \defgroup recalibration_config Recalibration Configuration 
 * \{
 */
#define CAPTOUCH2_INPUTS_THRESHOLD_UPDT_INDIVIDUALY  0x00
#define CAPTOUCH2_INPUT1_THRESHOLD_OVERWRITE         0x80
#define CAPTOUCH2_ACC_INTER_DATA_CLEAR               0x00
#define CAPTOUCH2_ACC_INTER_DATA_NOT_CLEAR           0x40
#define CAPTOUCH2_CONS_NEG_DELTA_CNT_CLEAR           0x00
#define CAPTOUCH2_CONS_NEG_DELTA_CNT_NOT_CLEAR       0x20
#define CAPTOUCH2_CONS_NEG_DELTA_CNT_8               0x00
#define CAPTOUCH2_CONS_NEG_DELTA_CNT_16              0x08
#define CAPTOUCH2_CONS_NEG_DELTA_CNT_32              0x10
#define CAPTOUCH2_CONS_NEG_DELTA_CNT_DIS             0x18
#define CAPTOUCH2_REC_SAMPLES_16_UPDT_TIME_16        0x00
#define CAPTOUCH2_REC_SAMPLES_32_UPDT_TIME_32        0x01
#define CAPTOUCH2_REC_SAMPLES_64_UPDT_TIME_64        0x02
#define CAPTOUCH2_REC_SAMPLES_128_UPDT_TIME_128      0x03
#define CAPTOUCH2_REC_SAMPLES_256_UPDT_TIME_256      0x04
#define CAPTOUCH2_REC_SAMPLES_256_UPDT_TIME_1024     0x05
#define CAPTOUCH2_REC_SAMPLES_256_UPDT_TIME_2048     0x06
#define CAPTOUCH2_REC_SAMPLES_256_UPDT_TIME_4096     0x07
/** \} */

/**
 * \defgroup based Based
 * \{
 */
#define CAPTOUCH2_AVERAGE_BASED  0x00
#define CAPTOUCH2_SUMMATION_BASED  0x80
/** \} */

/**
 * \defgroup  standby_sensitivity Standby Sensitivity 
 * \{
 */
#define CAPTOUCH2_STBY_SENSE_MULTIPLIER_128X  0x00
#define CAPTOUCH2_STBY_SENSE_MULTIPLIER_64X   0x01
#define CAPTOUCH2_STBY_SENSE_MULTIPLIER_32X   0x02
#define CAPTOUCH2_STBY_SENSE_MULTIPLIER_16X   0x03
#define CAPTOUCH2_STBY_SENSE_MULTIPLIER_8X    0x04
#define CAPTOUCH2_STBY_SENSE_MULTIPLIER_4X    0x05
#define CAPTOUCH2_STBY_SENSE_MULTIPLIER_2X    0x06
#define CAPTOUCH2_STBY_SENSE_MULTIPLIER_1X    0x07
/** \} */

/**
 * \defgroup led_output_type LED Output Type 
 * \{
 */
#define CAPTOUCH2_LED6_PIN_OPEN_DRAIN  0x00
#define CAPTOUCH2_LED6_PIN_PUSH_PULL   0x20
#define CAPTOUCH2_LED5_PIN_OPEN_DRAIN  0x00
#define CAPTOUCH2_LED5_PIN_PUSH_PULL   0x10
#define CAPTOUCH2_LED4_PIN_OPEN_DRAIN  0x00
#define CAPTOUCH2_LED4_PIN_PUSH_PULL   0x08
#define CAPTOUCH2_LED3_PIN_OPEN_DRAIN  0x00
#define CAPTOUCH2_LED3_PIN_PUSH_PULL   0x04
#define CAPTOUCH2_LED2_PIN_OPEN_DRAIN  0x00
#define CAPTOUCH2_LED2_PIN_PUSH_PULL   0x02
#define CAPTOUCH2_LED1_PIN_OPEN_DRAIN  0x00
#define CAPTOUCH2_LED1_PIN_PUSH_PULL   0x01
/** \} */

/**
 * \defgroup input_led_linking Input LED Linking
 * \{
 */
#define CAPTOUCH2_LED6_IN6_NOT_LINKED  0x00
#define CAPTOUCH2_LED6_IN6_LINKED      0x20
#define CAPTOUCH2_LED5_IN5_NOT_LINKED  0x00
#define CAPTOUCH2_LED5_IN5_LINKED      0x10
#define CAPTOUCH2_LED4_IN4_NOT_LINKED  0x00
#define CAPTOUCH2_LED4_IN4_LINKED      0x08
#define CAPTOUCH2_LED3_IN3_NOT_LINKED  0x00
#define CAPTOUCH2_LED3_IN3_LINKED      0x04
#define CAPTOUCH2_LED2_IN2_NOT_LINKED  0x00
#define CAPTOUCH2_LED2_IN2_LINKED      0x02
#define CAPTOUCH2_LED1_IN1_NOT_LINKED  0x00
#define CAPTOUCH2_LED1_IN1_LINKED      0x01
/** \} */

/**
 * \defgroup led_output_control LED Output Control
 * \{
 */
#define CAPTOUCH2_LED6_OUT_INVERTED      0x00
#define CAPTOUCH2_LED6_OUT_NOT_INVERTED  0x20
#define CAPTOUCH2_LED5_OUT_INVERTED      0x00
#define CAPTOUCH2_LED5_OUT_NOT_INVERTED  0x10
#define CAPTOUCH2_LED4_OUT_INVERTED      0x00
#define CAPTOUCH2_LED4_OUT_NOT_INVERTED  0x08
#define CAPTOUCH2_LED3_OUT_INVERTED      0x00
#define CAPTOUCH2_LED3_OUT_NOT_INVERTED  0x04
#define CAPTOUCH2_LED2_OUT_INVERTED      0x00
#define CAPTOUCH2_LED2_OUT_NOT_INVERTED  0x02
#define CAPTOUCH2_LED1_OUT_INVERTED      0x00
#define CAPTOUCH2_LED1_OUT_NOT_INVERTED  0x01
/** \} */

/**
 * \defgroup led_driven_toduty LED driven to Min/Max duty
 * \{
 */
#define CAPTOUCH2_LED6_DRIVEN_TO_MIN_DUTY  0x00
#define CAPTOUCH2_LED6_DRIVEN_TO_MAX_DUTY  0x20
#define CAPTOUCH2_LED5_DRIVEN_TO_MIN_DUTY  0x00
#define CAPTOUCH2_LED5_DRIVEN_TO_MAX_DUTY  0x10
#define CAPTOUCH2_LED4_DRIVEN_TO_MIN_DUTY  0x00
#define CAPTOUCH2_LED4_DRIVEN_TO_MAX_DUTY  0x08
#define CAPTOUCH2_LED3_DRIVEN_TO_MIN_DUTY  0x00
#define CAPTOUCH2_LED3_DRIVEN_TO_MAX_DUTY  0x04
#define CAPTOUCH2_LED2_DRIVEN_TO_MIN_DUTY  0x00
#define CAPTOUCH2_LED2_DRIVEN_TO_MAX_DUTY  0x02
#define CAPTOUCH2_LED1_DRIVEN_TO_MIN_DUTY  0x00
#define CAPTOUCH2_LED1_DRIVEN_TO_MAX_DUTY  0x01
/** \} */

/**
 * \defgroup led_change_state LED chaneg state
 * \{
 */
#define CAPTOUCH2_LED6_CHANGE_STATE      0x00
#define CAPTOUCH2_LED6_NOT_CHANGE_STATE  0x20
#define CAPTOUCH2_LED5_CHANGE_STATE      0x00
#define CAPTOUCH2_LED5_NOT_CHANGE_STATE  0x10
#define CAPTOUCH2_LED4_CHANGE_STATE      0x00
#define CAPTOUCH2_LED4_NOT_CHANGE_STATE  0x08
#define CAPTOUCH2_LED3_CHANGE_STATE      0x00
#define CAPTOUCH2_LED3_NOT_CHANGE_STATE  0x04
#define CAPTOUCH2_LED2_CHANGE_STATE      0x00
#define CAPTOUCH2_LED2_NOT_CHANGE_STATE  0x02
#define CAPTOUCH2_LED1_CHANGE_STATE      0x00
#define CAPTOUCH2_LED1_NOT_CHANGE_STATE  0x01
/** \} */

/**
 * \defgroup led_behavior_1234 LED behavior LED1/2/3/4
 * \{
 */
#define CAPTOUCH2_LED1_DIRECT_BEHAVIOR   0x00
#define CAPTOUCH2_LED1_PULSE1_BEHAVIOR   0x01
#define CAPTOUCH2_LED1_PULSE2_BEHAVIOR   0x02
#define CAPTOUCH2_LED1_BREATHE_BEHAVIOR  0x03
#define CAPTOUCH2_LED2_DIRECT_BEHAVIOR   0x00
#define CAPTOUCH2_LED2_PULSE1_BEHAVIOR   ( 0x01 << 2 )
#define CAPTOUCH2_LED2_PULSE2_BEHAVIOR   ( 0x02 << 2 )
#define CAPTOUCH2_LED2_BREATHE_BEHAVIOR  ( 0x03 << 2 )
#define CAPTOUCH2_LED3_DIRECT_BEHAVIOR   0x00
#define CAPTOUCH2_LED3_PULSE1_BEHAVIOR   ( 0x01 << 4 )
#define CAPTOUCH2_LED3_PULSE2_BEHAVIOR   ( 0x02 << 4 )
#define CAPTOUCH2_LED3_BREATHE_BEHAVIOR  ( 0x03 << 4 )
#define CAPTOUCH2_LED4_DIRECT_BEHAVIOR   ( 0x00 )
#define CAPTOUCH2_LED4_PULSE1_BEHAVIOR   ( 0x01 << 6 )
#define CAPTOUCH2_LED4_PULSE2_BEHAVIOR   ( 0x02 << 6 )
#define CAPTOUCH2_LED4_BREATHE_BEHAVIOR  ( 0x03 << 6 )
/** \} */

/**
 * \defgroup led_behavior_56 LED behavior LED5/6
 * \{
 */
#define CAPTOUCH2_LED5_DIRECT_BEHAVIOR   0x00
#define CAPTOUCH2_LED5_PULSE1_BEHAVIOR   0x01
#define CAPTOUCH2_LED5_PULSE2_BEHAVIOR   0x02
#define CAPTOUCH2_LED5_BREATHE_BEHAVIOR  0x03
#define CAPTOUCH2_LED6_DIRECT_BEHAVIOR   0x00
#define CAPTOUCH2_LED6_PULSE1_BEHAVIOR   ( 0x01 << 2 )
#define CAPTOUCH2_LED6_PULSE2_BEHAVIOR   ( 0x02 << 2 )
#define CAPTOUCH2_LED6_BREATHE_BEHAVIOR  ( 0x03 << 2 )
/** \} */

/**
 * \defgroup led_pulse LED pulse
 * \{
 */
#define CAPTOUCH2_LED_PULSE_ON_TOUCH          0x00
#define CAPTOUCH2_LED_PULSE_ON_RELEASE        0x80
#define CAPTOUCH2_LED_PULSE_PERIOD_32MILISEC  0x00
#define CAPTOUCH2_LED_PULSE_PERIOD_4064MILISEC  0x7F
/** \} */

/**
 * \defgroup sensitivity_multiplier Multiplier sensitivity
 * \{
 */
#define CAPTOUCH2_ALERT_NOT_ASSERTED_ON_LED_ACT   0x00
#define CAPTOUCH2_ALERT_ASSERTED_ON_LED_ACT       0x40
#define CAPTOUCH2_PULSE1_1_PULSE                  0x00
#define CAPTOUCH2_PULSE1_2_PULSES                 0x01
#define CAPTOUCH2_PULSE1_3_PULSES                 0x02
#define CAPTOUCH2_PULSE1_4_PULSES                 0x03
#define CAPTOUCH2_PULSE1_5_PULSES                 0x04
#define CAPTOUCH2_PULSE1_6_PULSES                 0x05
#define CAPTOUCH2_PULSE1_7_PULSES                 0x06
#define CAPTOUCH2_PULSE1_8_PULSES                 0x07
#define CAPTOUCH2_PULSE2_1_PULSE                  0x00
#define CAPTOUCH2_PULSE2_2_PULSES               ( 0x01 << 3 )
#define CAPTOUCH2_PULSE2_3_PULSES               ( 0x02 << 3 )
#define CAPTOUCH2_PULSE2_4_PULSES               ( 0x03 << 3 )
#define CAPTOUCH2_PULSE2_5_PULSES               ( 0x04 << 3 )
#define CAPTOUCH2_PULSE2_6_PULSES               ( 0x05 << 3 )
#define CAPTOUCH2_PULSE2_7_PULSES               ( 0x06 << 3 )
#define CAPTOUCH2_PULSE2_8_PULSES               ( 0x07 << 3 )
/** \} */

/**
 * \defgroup duty_in_percent Duty in percent
 * \{
 */
#define CAPTOUCH2_MIN_DUTY_0_PERCENT    0x00
#define CAPTOUCH2_MIN_DUTY_7_PERCENTS   0x01
#define CAPTOUCH2_MIN_DUTY_9_PERCENTS   0x02
#define CAPTOUCH2_MIN_DUTY_11_PERCENTS  0x03
#define CAPTOUCH2_MIN_DUTY_14_PERCENTS  0x04
#define CAPTOUCH2_MIN_DUTY_17_PERCENTS  0x05
#define CAPTOUCH2_MIN_DUTY_20_PERCENTS  0x06
#define CAPTOUCH2_MIN_DUTY_23_PERCENTS  0x07
#define CAPTOUCH2_MIN_DUTY_26_PERCENTS  0x08
#define CAPTOUCH2_MIN_DUTY_30_PERCENTS  0x09
#define CAPTOUCH2_MIN_DUTY_35_PERCENTS  0x0A
#define CAPTOUCH2_MIN_DUTY_40_PERCENTS  0x0B
#define CAPTOUCH2_MIN_DUTY_46_PERCENTS  0x0C
#define CAPTOUCH2_MIN_DUTY_53_PERCENTS  0x0D
#define CAPTOUCH2_MIN_DUTY_63_PERCENTS  0x0E
#define CAPTOUCH2_MIN_DUTY_77_PERCENTS  0x0F
#define CAPTOUCH2_MAX_DUTY_7_PERCENTS   0x00
#define CAPTOUCH2_MAX_DUTY_9_PERCENTS   0x10
#define CAPTOUCH2_MAX_DUTY_11_PERCENTS  0x20
#define CAPTOUCH2_MAX_DUTY_14_PERCENTS  0x30
#define CAPTOUCH2_MAX_DUTY_17_PERCENTS  0x40
#define CAPTOUCH2_MAX_DUTY_20_PERCENTS  0x50
#define CAPTOUCH2_MAX_DUTY_23_PERCENTS  0x60
#define CAPTOUCH2_MAX_DUTY_26_PERCENTS  0x70
#define CAPTOUCH2_MAX_DUTY_30_PERCENTS  0x80
#define CAPTOUCH2_MAX_DUTY_35_PERCENTS  0x90
#define CAPTOUCH2_MAX_DUTY_40_PERCENTS  0xA0
#define CAPTOUCH2_MAX_DUTY_46_PERCENTS  0xB0
#define CAPTOUCH2_MAX_DUTY_53_PERCENTS  0xC0
#define CAPTOUCH2_MAX_DUTY_63_PERCENTS  0xD0
#define CAPTOUCH2_MAX_DUTY_77_PERCENTS  0xE0
#define CAPTOUCH2_MAX_DUTY_100_PERCENTS 0xF0
/** \} */

/**
 * \defgroup gain_input_enable Gain and Input enable
 * \{
 */
#define CAPTOUCH2_GAIN_1     0x01
#define CAPTOUCH2_GAIN_2     0x02
#define CAPTOUCH2_GAIN_4     0x04
#define CAPTOUCH2_GAIN_8     0x08
#define CAPTOUCH2_ALL_INPUTS_DISABLE 0x00
#define CAPTOUCH2_INPUT1_EN  0x01
#define CAPTOUCH2_INPUT2_EN  0x02
#define CAPTOUCH2_INPUT3_EN  0x04
#define CAPTOUCH2_INPUT4_EN  0x08
#define CAPTOUCH2_INPUT5_EN  0x10
#define CAPTOUCH2_INPUT6_EN  0x20
#define CAPTOUCH2_ALL_INPUTS_ENABLE 0x3F
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
    // Output pins 

    digital_out_t cs;
    digital_out_t rst;

    // Input pins 

    digital_in_t alt;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    // ctx variable
    uint8_t release_check;
    uint8_t input_check[ 6 ];
    uint8_t cfg_byte_data;

} captouch2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t alt;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} captouch2_cfg_t;

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
void captouch2_cfg_setup ( captouch2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CAPTOUCH2_RETVAL captouch2_init ( captouch2_t *ctx, captouch2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for CapTouch2 click.
 *
 * @note
 * <pre>
 *     Cap Touch 2 is configured to works in Active mode (Normal mode).
 *     All inputs are enabled in this mode.
 *     In this example the interrupt will be generated when touch is detected and when touch is released.
 *     Also inputs 4, 5 and 6 will generate interrupt as long as the touch is detected (press and hold event),
 *     while inputs 1, 2 and 3 will generate interrupt only once on one touch detection, after which the touch will be released.
 *
 *     Note: Standby mode should be used when fewer sensor inputs are enabled, and when they are programmed to have more
 *     sensitivity.
 * </pre>
 */
void captouch2_default_cfg ( captouch2_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void captouch2_generic_transfer ( captouch2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Generic Write function
 *
 * @param ctx            Click object.
 * @param reg_addr       Address where data be written
 * @param tx_data        Data which be written
 *
 * @description  Function writes one byte to register.
 */
void captouch2_write_reg ( captouch2_t *ctx, uint8_t reg_addr, uint8_t tx_data );

/**
 * @brief Generic Read function
 *
 * @param ctx            Click object.
 * @param reg_addr         Address which from data be read
 * @param rx_data          Buffer where data be stored
 * @param n_bytes          Number of bytes which be read
 *
 * @description Function reads data from register.
 */
void captouch2_read_reg( captouch2_t *ctx, uint8_t reg_addr, uint8_t *rx_data, uint8_t n_bytes );

/**
 * @brief Touch Detect function
 *
 * @param ctx            Click object.
 * @param in_sens       Results of detecting touch on sensor inputs
 *
 * @note
 * <pre>
 *     Function detects touch on sensor inputs and checks is touch detected or is touch released.
 *     If noise occured on determined input, the touch will not be detected.
 * </pre>
 */
void captouch2_detect_touch( captouch2_t *ctx, uint8_t *in_sens );

/**
 * @brief Active Mode Set function
 *
 * @param ctx            Click object.
 * @param analog_gain          Possible gain value is 1, 2, 4 or 8
 * @param en_input             Enable or disable sensor inputs
 *
 * @description Function puts device in Active mode and enables desired inputs in Active mode.
 */
void captouch2_set_active_mode( captouch2_t *ctx, uint8_t analog_gain, uint8_t en_input );

/**
 * @brief Standby Mode Set function
 *
 * @param ctx            Click object.
 * @param analog_gain          Possible gain value is 1, 2, 4 or 8
 * @param en_input             Enable or disable sensor inputs
 *
 * @decscription Function puts device in Standby mode and enables desired inputs in Standby mode.
 */
void captouch2_set_standby_mode( captouch2_t *ctx, uint8_t analog_gain, uint8_t en_input );

/**
 * @brief DeepSleep Mode Set function
 *
 * @param ctx            Click object.
 *
 * @note In this mode the communication will not work and the sensor inputs will not detect touch.
 *
 * @description Function puts device in DeepSleep mode.
 */
void captouch2_set_deep_sleep_mode( captouch2_t *ctx );

/**
 * @brief Interrupt Check function
 *
 * @param ctx            Click object.
 * @return State of ALERT pin, 0 or 1
 *
 * @description Function checks interrupt state (ALERT pin).
 */
uint8_t captouch2_check_interrupt( captouch2_t *ctx );

/**
 * @brief Reset function
 *
 * @param ctx            Click object.
 *
 * @description Function performs device reset and waits until device exits from reset state.
 */
void captouch2_reset( captouch2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _CAPTOUCH2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
