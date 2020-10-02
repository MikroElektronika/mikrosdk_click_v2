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
 * \brief This file contains API for Light Ranger 4 Click driver.
 *
 * \addtogroup lightranger4 Light Ranger 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LIGHTRANGER4_H
#define LIGHTRANGER4_H

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
#define LIGHTRANGER4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.xsh = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LIGHTRANGER4_RETVAL  uint8_t

#define LIGHTRANGER4_OK           0x00
#define LIGHTRANGER4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Light Ranger registers
 * \{
 */
#define LR4_REG_SOFT_RESET                       0x0000
#define LR4_REG_SLAVE_DEVICE_ADDRESS             0x0001
#define LR4_REG_CFG_VHV_REF_SEL_VDDPIX           0x0002
#define LR4_REG_CFG_VHV_REF_SEL_VQUENCH          0x0003
#define LR4_REG_CFG_AVDD1V2_SEL                  0x0004
#define LR4_REG_FAST_OSC_TRIM                    0x0005
#define LR4_REG_FAST_OSC_FREQUENCY               0x0006
#define LR4_REG_FAST_OSC_FREQUENCY_MSB           0x0006
#define LR4_REG_FAST_OSC_FREQUENCY_LSB           0x0007
#define LR4_REG_CFG_TIMEOUT_MACROP_LOOP_BOUND    0x0008
#define LR4_REG_CFG_COUNT_THRESH                 0x0009
#define LR4_REG_CFG_OFFSET                       0x000A
#define LR4_REG_CFG_INIT                         0x000B
#define LR4_REG_GLOBAL_CFG_SPAD_ENABLES_REF_0    0x000D
#define LR4_REG_GLOBAL_CFG_SPAD_ENABLES_REF_1    0x000E
#define LR4_REG_GLOBAL_CFG_SPAD_ENABLES_REF_2    0x000F
#define LR4_REG_GLOBAL_CFG_SPAD_ENABLES_REF_3    0x0010
#define LR4_REG_GLOBAL_CFG_SPAD_ENABLES_REF_4    0x0011
#define LR4_REG_GLOBAL_CFG_SPAD_ENABLES_REF_5    0x0012
#define LR4_REG_GLOBAL_CFG_REF_EN_START_SELECT   0x0013
#define LR4_REG_NUM_REQUESTED_REF_SPADS          0x0014
#define LR4_REG_REF_LOCATION                     0x0015
#define LR4_REG_COMP_PLANE_OFFSET_KCPS           0x0016
#define LR4_REG_COMP_PLANE_OFFSET_KCPS_LSB       0x0016
#define LR4_REG_COMP_PLANE_OFFSET_KCPS_MSB       0x0017
#define LR4_REG_COMP_X_PLANE_GRADIENT_KCPS       0x0018
#define LR4_REG_COMP_X_PLANE_GRADIENT_KCPS_MSB   0x0018
#define LR4_REG_COMP_X_PLANE_GRADIENT_KCPS_LSB   0x0019
#define LR4_REG_COMP_Y_PLANE_GRADIENT_KCPS       0x001A
#define LR4_REG_COMP_Y_PLANE_GRADIENT_KCPS_MSB   0x001A
#define LR4_REG_COMP_Y_PLANE_GRADIENT_KCPS_LSB   0x001B
#define LR4_REG_TOTAL_RATE_TARGET_MCPS           0x001C
#define LR4_REG_TOTAL_RATE_TARGET_MCPS_MSB       0x001C
#define LR4_REG_TOTAL_RATE_TARGET_MCPS_LSB       0x001D
#define LR4_REG_PART_TO_PART_RANGE_OFFSET_MM     0x001E
#define LR4_REG_PART_TO_PART_RANGE_OFFSET_MM_MSB 0x001E
#define LR4_REG_PART_TO_PART_RANGE_OFFSET_MM_LSB 0x001F
#define LR4_REG_INNER_OFFSET_MM                  0x0020
#define LR4_REG_INNER_OFFSET_MM_MSB              0x0020
#define LR4_REG_INNER_OFFSET_MM_LSB              0x0021
#define LR4_REG_OUTER_OFFSET_MM                  0x0022
#define LR4_REG_OUTER_OFFSET_MM_MSB              0x0022
#define LR4_REG_OUTER_OFFSET_MM_LSB              0x0023
#define LR4_REG_TARGET_TOTAL_RATE_MCPS           0x0024
#define LR4_REG_TARGET_TOTAL_RATE_MCPS_MSB       0x0024
#define LR4_REG_TARGET_TOTAL_RATE_MCPS_LSB       0x0025
#define LR4_REG_DEBUG_CTRL                       0x0026
#define LR4_REG_TEST_MODE_CTRL                   0x0027
#define LR4_REG_CLK_GATING_CTRL                  0x0028


#define LR4_NVM_BIST_CTRL                                     0x0029
#define LR4_NVM_BIST_NUM_NVM_WORDS                            0x002A
#define LR4_NVM_BIST_START_ADDRESS                            0x002B
#define LR4_HOST_IF_STATUS                                    0x002C
#define LR4_PAD_I2C_HV_CONFIG                                 0x002D
#define LR4_PAD_I2C_HV_EXTSUP_CONFIG                          0x002E
#define LR4_GPIO_HV_PAD_CTRL                                  0x002F
#define LR4_GPIO_HV_MUX_CTRL                                  0x0030
#define LR4_GPIO_TIO_HV_STATUS                                0x0031
#define LR4_GPIO_FIO_HV_STATUS                                0x0032
#define LR4_ANA_CONFIG_SPAD_SEL_PSWIDTH                       0x0033
#define LR4_ANA_CONFIG_VCSEL_PULSE_WIDTH_OFFSET               0x0034
#define LR4_ANA_CONFIG_FAST_OSC_CONFIG_CTRL                   0x0035
#define LR4_SIGMA_ESTIMATOR_EFFECTIVE_PULSE_WIDTH_NS          0x0036
#define LR4_SIGMA_ESTIMATOR_EFFECTIVE_AMBIENT_WIDTH_NS        0x0037
#define LR4_SIGMA_ESTIMATOR_SIGMA_REF_MM                      0x0038
#define LR4_ALGO_CROSSTALK_COMPENSATION_VALID_HEIGHT_MM       0x0039
#define LR4_SPARE_HOST_CONFIG_STATIC_CONFIG_SPARE_0           0x003A
#define LR4_SPARE_HOST_CONFIG_STATIC_CONFIG_SPARE_1           0x003B
#define LR4_ALGO_RANGE_IGNORE_THRESHOLD_MCPS                  0x003C
#define LR4_ALGO_RANGE_IGNORE_THRESHOLD_MCPS_HI               0x003C
#define LR4_ALGO_RANGE_IGNORE_THRESHOLD_MCPS_LO               0x003D
#define LR4_ALGO_RANGE_IGNORE_VALID_HEIGHT_MM                 0x003E
#define LR4_ALGO_RANGE_MIN_CLIP                               0x003F
#define LR4_ALGO_CONSISTENCY_CHECK_TOLERANCE                  0x0040
#define LR4_SPARE_HOST_CONFIG_STATIC_CONFIG_SPARE_2           0x0041
#define LR4_SD_CONFIG_RESET_STAGES_MSB                        0x0042
#define LR4_SD_CONFIG_RESET_STAGES_LSB                        0x0043
#define LR4_GPH_CONFIG_STREAM_COUNT_UPDATE_VALUE              0x0044
#define LR4_GLOBAL_CONFIG_STREAM_DIVIDER                      0x0045
#define LR4_SYSTEM_INTERRUPT_CONFIG_GPIO                      0x0046
#define LR4_CAL_CONFIG_VCSEL_START                            0x0047
#define LR4_CAL_CONFIG_REPEAT_RATE                            0x0048
#define LR4_CAL_CONFIG_REPEAT_RATE_HI                         0x0048
#define LR4_CAL_CONFIG_REPEAT_RATE_LO                         0x0049
#define LR4_GLOBAL_CONFIG_VCSEL_WIDTH                         0x004A
#define LR4_PHASECAL_CONFIG_TIMEOUT_MACROP                    0x004B
#define LR4_PHASECAL_CONFIG_TARGET                            0x004C
#define LR4_PHASECAL_CONFIG_OVERRIDE                          0x004D
#define LR4_DSS_CONFIG_ROI_MODE_CONTROL                       0x004F
#define LR4_SYSTEM_THRESH_RATE_HIGH                           0x0050
#define LR4_SYSTEM_THRESH_RATE_HIGH_HI                        0x0050
#define LR4_SYSTEM_THRESH_RATE_HIGH_LO                        0x0051
#define LR4_SYSTEM_THRESH_RATE_LOW                            0x0052
#define LR4_SYSTEM_THRESH_RATE_LOW_HI                         0x0052
#define LR4_SYSTEM_THRESH_RATE_LOW_LO                         0x0053
#define LR4_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT          0x0054
#define LR4_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT_HI       0x0054
#define LR4_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT_LO       0x0055
#define LR4_DSS_CONFIG_MANUAL_BLOCK_SELECT                    0x0056
#define LR4_DSS_CONFIG_APERTURE_ATTENUATION                   0x0057
#define LR4_DSS_CONFIG_MAX_SPADS_LIMIT                        0x0058
#define LR4_DSS_CONFIG_MIN_SPADS_LIMIT                        0x0059
#define LR4_MM_CONFIG_TIMEOUT_MACROP_A_HI                     0x005A
#define LR4_MM_CONFIG_TIMEOUT_MACROP_A_LO                     0x005B
#define LR4_MM_CONFIG_TIMEOUT_MACROP_B_HI                     0x005C
#define LR4_MM_CONFIG_TIMEOUT_MACROP_B_LO                     0x005D
#define LR4_RANGE_CONFIG_TIMEOUT_MACROP_A_HI                  0x005E
#define LR4_RANGE_CONFIG_TIMEOUT_MACROP_A_LO                  0x005F
#define LR4_RANGE_CONFIG_VCSEL_PERIOD_A                       0x0060
#define LR4_RANGE_CONFIG_TIMEOUT_MACROP_B_HI                  0x0061
#define LR4_RANGE_CONFIG_TIMEOUT_MACROP_B_LO                  0x0062
#define LR4_RANGE_CONFIG_VCSEL_PERIOD_B                       0x0063
#define LR4_RANGE_CONFIG_SIGMA_THRESH                         0x0064
#define LR4_RANGE_CONFIG_SIGMA_THRESH_HI                      0x0064
#define LR4_RANGE_CONFIG_SIGMA_THRESH_LO                      0x0065
#define LR4_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS        0x0066
#define LR4_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS_HI     0x0066
#define LR4_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS_LO     0x0067
#define LR4_RANGE_CONFIG_VALID_PHASE_LOW                      0x0068
#define LR4_RANGE_CONFIG_VALID_PHASE_HIGH                     0x0069
#define LR4_SYSTEM_INTERMEASUREMENT_PERIOD                    0x006C
#define LR4_SYSTEM_INTERMEASUREMENT_PERIOD_3                  0x006C
#define LR4_SYSTEM_INTERMEASUREMENT_PERIOD_2                  0x006D
#define LR4_SYSTEM_INTERMEASUREMENT_PERIOD_1                  0x006E
#define LR4_SYSTEM_INTERMEASUREMENT_PERIOD_0                  0x006F
#define LR4_SYSTEM_FRACTIONAL_ENABLE                          0x0070
#define LR4_SYSTEM_GROUPED_PARAMETER_HOLD_0                   0x0071
#define LR4_SYSTEM_THRESH_HIGH                                0x0072
#define LR4_SYSTEM_THRESH_HIGH_HI                             0x0072
#define LR4_SYSTEM_THRESH_HIGH_LO                             0x0073
#define LR4_SYSTEM_THRESH_LOW                                 0x0074
#define LR4_SYSTEM_THRESH_LOW_HI                              0x0074
#define LR4_SYSTEM_THRESH_LOW_LO                              0x0075
#define LR4_SYSTEM_ENABLE_XTALK_PER_QUADRANT                  0x0076
#define LR4_SYSTEM_SEED_CONFIG                                0x0077
#define LR4_SD_CONFIG_WOI_SD0                                 0x0078
#define LR4_SD_CONFIG_WOI_SD1                                 0x0079
#define LR4_SD_CONFIG_INITIAL_PHASE_SD0                       0x007A
#define LR4_SD_CONFIG_INITIAL_PHASE_SD1                       0x007B
#define LR4_SYSTEM_GROUPED_PARAMETER_HOLD_1                   0x007C
#define LR4_SD_CONFIG_FIRST_ORDER_SELECT                      0x007D
#define LR4_SD_CONFIG_QUANTIFIER                              0x007E
#define LR4_ROI_CONFIG_USER_ROI_CENTRE_SPAD                   0x007F
#define LR4_ROI_CONFIG_USER_ROI_REQUESTED_GLOBAL_XY_SIZE      0x0080
#define LR4_SYSTEM_SEQUENCE_CONFIG                            0x0081
#define LR4_SYSTEM_GROUPED_PARAMETER_HOLD                     0x0082
#define LR4_POWER_MANAGEMENT_GO1_POWER_FORCE                  0x0083
#define LR4_SYSTEM_STREAM_COUNT_CTRL                          0x0084
#define LR4_FIRMWARE_ENABLE                                   0x0085
#define LR4_SYSTEM_INTERRUPT_CLEAR                            0x0086
#define LR4_SYSTEM_MODE_START                                 0x0087
/** \} */

/**
 * \defgroup result Result
 * \{
 */
#define LR4_RESULT_INTERRUPT_STATUS                                           0x0088
#define LR4_RESULT_RANGE_STATUS                                               0x0089
#define LR4_RESULT_REPORT_STATUS                                              0x008A
#define LR4_RESULT_STREAM_COUNT                                               0x008B
#define LR4_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0                             0x008C
#define LR4_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_HI                          0x008C
#define LR4_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_LO                          0x008D
#define LR4_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0                            0x008E
#define LR4_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_HI                         0x008E
#define LR4_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_LO                         0x008F
#define LR4_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0                                0x0090
#define LR4_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_HI                             0x0090
#define LR4_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_LO                             0x0091
#define LR4_RESULT_SIGMA_SD0                                                  0x0092
#define LR4_RESULT_SIGMA_SD0_HI                                               0x0092
#define LR4_RESULT_SIGMA_SD0_LO                                               0x0093
#define LR4_RESULT_PHASE_SD0                                                  0x0094
#define LR4_RESULT_PHASE_SD0_HI                                               0x0094
#define LR4_RESULT_PHASE_SD0_LO                                               0x0095
#define LR4_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0                     0x0096
#define LR4_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_HI                  0x009
#define LR4_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_LO                  0x0097
#define LR4_RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0        0x0098
#define LR4_RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_HI     0x0098
#define LR4_RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_LO     0x0099
#define LR4_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0                        0x009A
#define LR4_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_HI                     0x009A
#define LR4_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_LO                     0x009B
#define LR4_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0                        0x009C
#define LR4_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_HI                     0x009C
#define LR4_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_LO                     0x009D
#define LR4_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0                             0x009E
#define LR4_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_HI                          0x009E
#define LR4_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_LO                          0x009F
#define LR4_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1                             0x00A0
#define LR4_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_HI                          0x00A0
#define LR4_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_LO                          0x00A1
#define LR4_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1                            0x00A2
#define LR4_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_HI                         0x00A2
#define LR4_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_LO                         0x00A3
#define LR4_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1                                0x00A4
#define LR4_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_HI                             0x00A4
#define LR4_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_LO                             0x00A5
#define LR4_RESULT_SIGMA_SD1                                                  0x00A6
#define LR4_RESULT_SIGMA_SD1_HI                                               0x00A6
#define LR4_RESULT_SIGMA_SD1_LO                                               0x00A7
#define LR4_RESULT_PHASE_SD1                                                  0x00A8
#define LR4_RESULT_PHASE_SD1_HI                                               0x00A8
#define LR4_RESULT_PHASE_SD1_LO                                               0x00A9
#define LR4_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1                     0x00AA
#define LR4_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_HI                  0x00AA
#define LR4_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_LO                  0x00AB
#define LR4_RESULT_SPARE_0_SD1                                                0x00AC
#define LR4_RESULT_SPARE_0_SD1_HI                                             0x00AC
#define LR4_RESULT_SPARE_0_SD1_LO                                             0x00AD
#define LR4_RESULT_SPARE_1_SD1                                                0x00AE
#define LR4_RESULT_SPARE_1_SD1_HI                                             0x00AE
#define LR4_RESULT_SPARE_1_SD1_LO                                             0x00AF
#define LR4_RESULT_SPARE_2_SD1                                                0x00B0
#define LR4_RESULT_SPARE_2_SD1_HI                                             0x00B0
#define LR4_RESULT_SPARE_2_SD1_LO                                             0x00B1
#define LR4_RESULT_SPARE_3_SD1                                                0x00B2
#define LR4_RESULT_THRESH_INFO                                                0x00B3
/** \} */

/**
 * \defgroup core Core
 * \{
 */
#define LR4_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0     0x00B4
#define LR4_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_3   0x00B4
#define LR4_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_2   0x00B5
#define LR4_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_1   0x00B6
#define LR4_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_0   0x00B7
#define LR4_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0      0x00B8
#define LR4_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_3    0x00B8
#define LR4_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_2    0x00B9
#define LR4_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_1    0x00BA
#define LR4_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_0    0x00BB
#define LR4_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0       0x00BC
#define LR4_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_3     0x00BC
#define LR4_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_2     0x00BD
#define LR4_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_1     0x00BE
#define LR4_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_0     0x00BF
#define LR4_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0     0x00C0
#define LR4_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_3   0x00C0
#define LR4_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_2   0x00C1
#define LR4_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_1   0x00C2
#define LR4_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_0   0x00C3
#define LR4_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1     0x00C4
#define LR4_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_3   0x00C4
#define LR4_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_2   0x00C5
#define LR4_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_1   0x00C6
#define LR4_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_0   0x00C7
#define LR4_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1      0x00C8
#define LR4_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_3    0x00C8
#define LR4_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_2    0x00C9
#define LR4_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_1    0x00CA
#define LR4_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_0    0x00CB
#define LR4_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1       0x00CC
#define LR4_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_3     0x00CC
#define LR4_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_2     0x00CD
#define LR4_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_1     0x00CE
#define LR4_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_0     0x00CF
#define LR4_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1     0x00D0
#define LR4_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_3   0x00D0
#define LR4_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_2   0x00D1
#define LR4_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_1   0x00D2
#define LR4_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_0   0x00D3
#define LR4_RESULT_CORE_SPARE_0                       0x00D4
/** \} */

/**
 * \defgroup phasecal_result Phasecal result
 * \{
 */
#define LR4_PHASECAL_RESULT_REFERENCE_PHASE           0x00D6
#define LR4_PHASECAL_RESULT_REFERENCE_PHASE_HI        0x00D6
#define LR4_PHASECAL_RESULT_REFERENCE_PHASE_LO        0x00D7
#define LR4_PHASECAL_RESULT_VCSEL_START               0x00D8


#define LR4_REF_SPAD_CHAR_RESULT__NUM_ACTUAL_REF_SPADS  0x00D9
#define LR4_REF_SPAD_CHAR_RESULT__REF_LOCATION          0x00DA
#define LR4_VHV_RESULT_COLDBOOT_STATUS                  0x00DB
#define LR4_VHV_RESULT_SEARCH_RESULT                    0x00DC
#define LR4_VHV_RESULT_LATEST_SETTING                   0x00DD
#define LR4_RESULT_OSC_CALIBRATE_VAL                    0x00DE
#define LR4_RESULT_OSC_CALIBRATE_VAL_HI                 0x00DE
#define LR4_RESULT_OSC_CALIBRATE_VAL_LO                 0x00DF
#define LR4_ANA_CONFIG_POWERDOWN_GO1                    0x00E0
#define LR4_ANA_CONFIG_REF_BG_CTRL                      0x00E1
#define LR4_ANA_CONFIG_REGDVDD1V2_CTRL                  0x00E2
#define LR4_ANA_CONFIG_OSC_SLOW_CTRL                    0x00E3
#define LR4_TEST_MODE_STATUS                            0x00E4
/** \} */

/**
 * \defgroup firmware Firmware
 * \{
 */
#define LR4_FIRMWARE_SYSTEM_STATUS                0x00E5
#define LR4_FIRMWARE_MODE_STATUS                  0x00E6
#define LR4_FIRMWARE_SECONDARY_MODE_STATUS        0x00E7
#define LR4_FIRMWARE_CAL_REPEAT_RATE_COUNTER      0x00E8
#define LR4_FIRMWARE_CAL_REPEAT_RATE_COUNTER_HI   0x00E8
#define LR4_FIRMWARE_CAL_REPEAT_RATE_COUNTER_LO   0x00E9
#define LR4_FIRMWARE_HISTOGRAM_BIN                0x00EA
/** \} */

/**
 * \defgroup gph_system_cfg GPH system config
 * \{
 */
#define LR4_GPH_SYSTEM_THRESH_HIGH                0x00EC
#define LR4_GPH_SYSTEM_THRESH_HIGH_HI             0x00EC
#define LR4_GPH_SYSTEM_THRESH_HIGH_LO             0x00ED
#define LR4_GPH_SYSTEM_THRESH_LOW                 0x00EE
#define LR4_GPH_SYSTEM_THRESH_LOW_HI              0x00EE
#define LR4_GPH_SYSTEM_THRESH_LOW_LO              0x00EF
#define LR4_GPH_SYSTEM_ENABLE_XTALK_PER_QUADRANT  0x00F0

#define LR4_GPH_SPARE_0                                       0x00F1
#define LR4_GPH_SD_CONFIG_WOI_SD0                             0x00F2
#define LR4_GPH_SD_CONFIG_WOI_SD1                             0x00F3
#define LR4_GPH_SD_CONFIG_INITIAL_PHASE_SD0                   0x00F4
#define LR4_GPH_SD_CONFIG_INITIAL_PHASE_SD1                   0x00F5
#define LR4_GPH_SD_CONFIG_FIRST_ORDER_SELECT                  0x00F6
#define LR4_GPH_SD_CONFIG_QUANTIFIER                          0x00F7
#define LR4_GPH_ROI_CONFIG_USER_ROI_CENTRE_SPAD               0x00F8
#define LR4_GPH_ROI_CONFIG_USER_ROI_REQUESTED_GLOBAL_XY_SIZE  0x00F9
#define LR4_GPH_SYSTEM_SEQUENCE_CONFIG                        0x00FA
#define LR4_GPH_GPH_ID                                        0x00FB


#define LR4_SYSTEM_INTERRUPT_SET                                              0x00FC
#define LR4_INTERRUPT_MANAGER_ENABLES                                         0x00FD
#define LR4_INTERRUPT_MANAGER_CLEAR                                           0x00FE
#define LR4_INTERRUPT_MANAGER_STATUS                                          0x00FF
#define LR4_MCU_TO_HOST_BANK_WR_ACCESS_EN                                     0x0100
#define LR4_POWER_MANAGEMENT_GO1_RESET_STATUS                                 0x0101
#define LR4_PAD_STARTUP_MODE_VALUE_RO                                         0x0102
#define LR4_PAD_STARTUP_MODE_VALUE_CTRL                                       0x0103
#define LR4_PLL_PERIOD_US                                                     0x0104
#define LR4_PLL_PERIOD_US_3                                                   0x0104
#define LR4_PLL_PERIOD_US_2                                                   0x0105
#define LR4_PLL_PERIOD_US_1                                                   0x0106
#define LR4_PLL_PERIOD_US_0                                                   0x0107
#define LR4_INTERRUPT_SCHEDULER_DATA_OUT                                      0x0108
#define LR4_INTERRUPT_SCHEDULER_DATA_OUT_3                                    0x0108
#define LR4_INTERRUPT_SCHEDULER_DATA_OUT_2                                    0x0109
#define LR4_INTERRUPT_SCHEDULER_DATA_OUT_1                                    0x010A
#define LR4_INTERRUPT_SCHEDULER_DATA_OUT_0                                    0x010B
#define LR4_NVM_BIST_COMPLETE                                                 0x010C
#define LR4_NVM_BIST_STATUS                                                   0x010D
/** \} */

/**
 * \defgroup identification Identification
 * \{
 */
#define LR4_IDENTIFICATION_MODEL_ID                                           0x010F
#define LR4_IDENTIFICATION_MODULE_TYPE                                        0x0110
#define LR4_IDENTIFICATION_REVISION_ID                                        0x0111
#define LR4_IDENTIFICATION_MODULE_ID                                          0x0112
#define LR4_IDENTIFICATION_MODULE_ID_HI                                       0x0112
#define LR4_IDENTIFICATION_MODULE_ID_LO                                       0x0113
/** \} */

/**
 * \defgroup ana_cfg ANA Config
 * \{
 */
#define LR4_ANA_CONFIG_FAST_OSC__TRIM_MAX                                     0x0114
#define LR4_ANA_CONFIG_FAST_OSC__FREQ_SET                                     0x0115
#define LR4_ANA_CONFIG_VCSEL_TRIM                                             0x0116
#define LR4_ANA_CONFIG_VCSEL_SELION                                           0x0117
#define LR4_ANA_CONFIG_VCSEL_SELION_MAX                                       0x0118
/** \} */

/**
 * \defgroup laser Laser
 * \{
 */
#define LR4_PROTECTED_LASER_SAFETY__LOCK_BIT                                  0x0119
#define LR4_LASER_SAFETY_KEY                                                  0x011A
#define LR4_LASER_SAFETY_KEY_RO                                               0x011B
#define LR4_LASER_SAFETY_CLIP                                                 0x011C
#define LR4_LASER_SAFETY_MULT                                                 0x011D
/** \} */

/**
 * \defgroup global_cfg Global config
 * \{
 */
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_0                                  0x011E
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_1                                  0x011F
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_2                                  0x0120
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_3                                  0x0121
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_4                                  0x0122
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_5                                  0x0123
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_6                                  0x0124
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_7                                  0x0125
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_8                                  0x0126
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_9                                  0x0127
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_10                                 0x0128
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_11                                 0x0129
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_12                                 0x012A
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_13                                 0x012B
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_14                                 0x012C
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_15                                 0x012D
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_16                                 0x012E
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_17                                 0x012F
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_18                                 0x0130
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_19                                 0x0131
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_20                                 0x0132
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_21                                 0x0133
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_22                                 0x0134
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_23                                 0x0135
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_24                                 0x0136
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_25                                 0x0137
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_26                                 0x0138
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_27                                 0x0139
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_28                                 0x013A
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_29                                 0x013B
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_30                                 0x013C
#define LR4_GLOBAL_CONFIG_SPAD_ENABLES_RTN_31                                 0x013D
/** \} */

/**
 * \defgroup roi_cfg ROI config
 * \{
 */
#define LR4_ROI_CONFIG_MODE_ROI_CENTRE_SPAD                                   0x013E
#define LR4_ROI_CONFIG_MODE_ROI_XY_SIZE                                       0x013F

#define LR4_GO2_HOST_BANK_ACCESS_OVERRIDE                                     0x0300
/** \} */

/**
 * \defgroup mcu_util_multiplier MCU-util multiplier
 * \{
 */
#define LR4_MCU_UTIL_MULTIPLIER_MULTIPLICAND     0x0400
#define LR4_MCU_UTIL_MULTIPLIER_MULTIPLICAND_3   0x0400
#define LR4_MCU_UTIL_MULTIPLIER_MULTIPLICAND_2   0x0401
#define LR4_MCU_UTIL_MULTIPLIER_MULTIPLICAND_1   0x0402
#define LR4_MCU_UTIL_MULTIPLIER_MULTIPLICAND_0   0x0403
#define LR4_MCU_UTIL_MULTIPLIER_MULTIPLIER       0x0404
#define LR4_MCU_UTIL_MULTIPLIER_MULTIPLIER_3     0x0404
#define LR4_MCU_UTIL_MULTIPLIER_MULTIPLIER_2     0x0405
#define LR4_MCU_UTIL_MULTIPLIER_MULTIPLIER_1     0x0406
#define LR4_MCU_UTIL_MULTIPLIER_MULTIPLIER_0     0x0407
#define LR4_MCU_UTIL_MULTIPLIER_PRODUCT_HI       0x0408
#define LR4_MCU_UTIL_MULTIPLIER_PRODUCT_HI_3     0x0408
#define LR4_MCU_UTIL_MULTIPLIER_PRODUCT_HI_2     0x0409
#define LR4_MCU_UTIL_MULTIPLIER_PRODUCT_HI_1     0x040A
#define LR4_MCU_UTIL_MULTIPLIER_PRODUCT_HI_0     0x040B
#define LR4_MCU_UTIL_MULTIPLIER_PRODUCT_LO       0x040C
#define LR4_MCU_UTIL_MULTIPLIER_PRODUCT_LO_3     0x040C
#define LR4_MCU_UTIL_MULTIPLIER_PRODUCT_LO_2     0x040D
#define LR4_MCU_UTIL_MULTIPLIER_PRODUCT_LO_1     0x040E
#define LR4_MCU_UTIL_MULTIPLIER_PRODUCT_LO_0     0x040F
#define LR4_MCU_UTIL_MULTIPLIER_START            0x0410
#define LR4_MCU_UTIL_MULTIPLIER_STATUS           0x0411
/** \} */

/**
 * \defgroup mcu_util_divider MCU-util divider
 * \{
 */
#define LR4_MCU_UTIL_DIVIDER_START          0x0412
#define LR4_MCU_UTIL_DIVIDER_STATUS         0x0413
#define LR4_MCU_UTIL_DIVIDER_DIVIDEND       0x0414
#define LR4_MCU_UTIL_DIVIDER_DIVIDEND_3     0x0414
#define LR4_MCU_UTIL_DIVIDER_DIVIDEND_2     0x0415
#define LR4_MCU_UTIL_DIVIDER_DIVIDEND_1     0x0416
#define LR4_MCU_UTIL_DIVIDER_DIVIDEND_0     0x0417
#define LR4_MCU_UTIL_DIVIDER_DIVISOR        0x0418
#define LR4_MCU_UTIL_DIVIDER_DIVISOR_3      0x0418
#define LR4_MCU_UTIL_DIVIDER_DIVISOR_2      0x0419
#define LR4_MCU_UTIL_DIVIDER_DIVISOR_1      0x041A
#define LR4_MCU_UTIL_DIVIDER_DIVISOR_0      0x041B
#define LR4_MCU_UTIL_DIVIDER_QUOTIENT       0x041C
#define LR4_MCU_UTIL_DIVIDER_QUOTIENT_3     0x041C
#define LR4_MCU_UTIL_DIVIDER_QUOTIENT_2     0x041D
#define LR4_MCU_UTIL_DIVIDER_QUOTIENT_1     0x041E
#define LR4_MCU_UTIL_DIVIDER_QUOTIENT_0     0x041F
/** \} */

/**
 * \defgroup timer Timer
 * \{
 */
#define LR4_TIMER0_VALUE_IN      0x0420
#define LR4_TIMER0_VALUE_IN_3    0x0420
#define LR4_TIMER0_VALUE_IN_2    0x0421
#define LR4_TIMER0_VALUE_IN_1    0x0422
#define LR4_TIMER0_VALUE_IN_0    0x0423
#define LR4_TIMER1_VALUE_IN      0x0424
#define LR4_TIMER1_VALUE_IN_3    0x0424
#define LR4_TIMER1_VALUE_IN_2    0x0425
#define LR4_TIMER1_VALUE_IN_1    0x0426
#define LR4_TIMER1_VALUE_IN_0    0x0427
#define LR4_TIMER0_CTRL          0x0428
#define LR4_TIMER1_CTRL          0x0429
/** \} */

/**
 * \defgroup general_purpose General purpose
 * \{
 */
#define LR4_MCU_GENERAL_PURPOSE_GP_0   0x042C
#define LR4_MCU_GENERAL_PURPOSE_GP_1   0x042D
#define LR4_MCU_GENERAL_PURPOSE_GP_2   0x042E
#define LR4_MCU_GENERAL_PURPOSE_GP_3   0x042F
/** \} */

/**
 * \defgroup range_calc Range calc.
 * \{
 */
#define LR4_MCU_RANGE_CALC_CONFIG                                             0x0430
#define LR4_MCU_RANGE_CALC_OFFSET_CORRECTED_RANGE                             0x0432
#define LR4_MCU_RANGE_CALC_OFFSET_CORRECTED_RANGE_HI                          0x0432
#define LR4_MCU_RANGE_CALC_OFFSET_CORRECTED_RANGE_LO                          0x0433
#define LR4_MCU_RANGE_CALC_SPARE_4                                            0x0434
#define LR4_MCU_RANGE_CALC_SPARE_4_3                                          0x0434
#define LR4_MCU_RANGE_CALC_SPARE_4_2                                          0x0435
#define LR4_MCU_RANGE_CALC_SPARE_4_1                                          0x0436
#define LR4_MCU_RANGE_CALC_SPARE_4_0                                          0x0437
#define LR4_MCU_RANGE_CALC_AMBIENT_DURATION_PRE_CALC                          0x0438
#define LR4_MCU_RANGE_CALC_AMBIENT_DURATION_PRE_CALC_HI                       0x0438
#define LR4_MCU_RANGE_CALC_AMBIENT_DURATION_PRE_CALC_LO                       0x0439
#define LR4_MCU_RANGE_CALC_ALGO_VCSEL_PERIOD                                  0x043C
#define LR4_MCU_RANGE_CALC_SPARE_5                                            0x043D
#define LR4_MCU_RANGE_CALC_ALGO_TOTAL_PERIODS                                 0x043E
#define LR4_MCU_RANGE_CALC_ALGO_TOTAL_PERIODS_HI                              0x043E
#define LR4_MCU_RANGE_CALC_ALGO_TOTAL_PERIODS_LO                              0x043F
#define LR4_MCU_RANGE_CALC_ALGO_ACCUM_PHASE                                   0x0440
#define LR4_MCU_RANGE_CALC_ALGO_ACCUM_PHASE_3                                 0x0440
#define LR4_MCU_RANGE_CALC_ALGO_ACCUM_PHASE_2                                 0x0441
#define LR4_MCU_RANGE_CALC_ALGO_ACCUM_PHASE_1                                 0x0442
#define LR4_MCU_RANGE_CALC_ALGO_ACCUM_PHASE_0                                 0x0443
#define LR4_MCU_RANGE_CALC_ALGO_SIGNAL_EVENTS                                 0x0444
#define LR4_MCU_RANGE_CALC_ALGO_SIGNAL_EVENTS_3                               0x0444
#define LR4_MCU_RANGE_CALC_ALGO_SIGNAL_EVENTS_2                               0x0445
#define LR4_MCU_RANGE_CALC_ALGO_SIGNAL_EVENTS_1                               0x0446
#define LR4_MCU_RANGE_CALC_ALGO_SIGNAL_EVENTS_0                               0x0447
#define LR4_MCU_RANGE_CALC_ALGO_AMBIENT_EVENTS                                0x0448
#define LR4_MCU_RANGE_CALC_ALGO_AMBIENT_EVENTS_3                              0x0448
#define LR4_MCU_RANGE_CALC_ALGO_AMBIENT_EVENTS_2                              0x0449
#define LR4_MCU_RANGE_CALC_ALGO_AMBIENT_EVENTS_1                              0x044A
#define LR4_MCU_RANGE_CALC_ALGO_AMBIENT_EVENTS_0                              0x044B
#define LR4_MCU_RANGE_CALC_SPARE_6                                            0x044C
#define LR4_MCU_RANGE_CALC_SPARE_6_HI                                         0x044C
#define LR4_MCU_RANGE_CALC_SPARE_6_LO                                         0x044D
#define LR4_MCU_RANGE_CALC_ALGO_ADJUST_VCSEL_PERIOD                           0x044E
#define LR4_MCU_RANGE_CALC_ALGO_ADJUST_VCSEL_PERIOD_HI                        0x044E
#define LR4_MCU_RANGE_CALC_ALGO_ADJUST_VCSEL_PERIOD_LO                        0x044F
#define LR4_MCU_RANGE_CALC_NUM_SPADS                                          0x0450
#define LR4_MCU_RANGE_CALC_NUM_SPADS_HI                                       0x0450
#define LR4_MCU_RANGE_CALC_NUM_SPADS_LO                                       0x0451
#define LR4_MCU_RANGE_CALC_PHASE_OUTPUT                                       0x0452
#define LR4_MCU_RANGE_CALC_PHASE_OUTPUT_HI                                    0x0452
#define LR4_MCU_RANGE_CALC_PHASE_OUTPUT_LO                                    0x0453
#define LR4_MCU_RANGE_CALC_RATE_PER_SPAD_MCPS                                 0x0454
#define LR4_MCU_RANGE_CALC_RATE_PER_SPAD_MCPS_3                               0x0454
#define LR4_MCU_RANGE_CALC_RATE_PER_SPAD_MCPS_2                               0x0455
#define LR4_MCU_RANGE_CALC_RATE_PER_SPAD_MCPS_1                               0x0456
#define LR4_MCU_RANGE_CALC_RATE_PER_SPAD_MCPS_0                               0x0457
#define LR4_MCU_RANGE_CALC_SPARE_7                                            0x0458
#define LR4_MCU_RANGE_CALC_SPARE_8                                            0x0459
#define LR4_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_MCPS                              0x045A
#define LR4_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_MCPS_HI                           0x045A
#define LR4_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_MCPS_LO                           0x045B
#define LR4_MCU_RANGE_CALC_AVG_SIGNAL_RATE_MCPS                               0x045C
#define LR4_MCU_RANGE_CALC_AVG_SIGNAL_RATE_MCPS_HI                            0x045C
#define LR4_MCU_RANGE_CALC_AVG_SIGNAL_RATE_MCPS_LO                            0x045D
#define LR4_MCU_RANGE_CALC_AMBIENT_RATE_MCPS                                  0x045E
#define LR4_MCU_RANGE_CALC_AMBIENT_RATE_MCPS_HI                               0x045E
#define LR4_MCU_RANGE_CALC_AMBIENT_RATE_MCPS_LO                               0x045F
#define LR4_MCU_RANGE_CALC_XTALK                                              0x0460
#define LR4_MCU_RANGE_CALC_XTALK_HI                                           0x0460
#define LR4_MCU_RANGE_CALC_XTALK_LO                                           0x0461
#define LR4_MCU_RANGE_CALC_CALC_STATUS                                        0x0462
#define LR4_MCU_RANGE_CALC_DEBUG                                              0x0463
#define LR4_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_XTALK_CORR_MCPS                   0x0464
#define LR4_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_XTALK_CORR_MCPS_HI                0x0464
#define LR4_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_XTALK_CORR_MCPS_LO                0x0465
#define LR4_MCU_RANGE_CALC_SPARE_0                                            0x0468
#define LR4_MCU_RANGE_CALC_SPARE_1                                            0x0469
#define LR4_MCU_RANGE_CALC_SPARE_2                                            0x046A
#define LR4_MCU_RANGE_CALC_SPARE_3                                            0x046B
/** \} */

/**
 * \defgroup patch Patch
 * \{
 */
#define LR4_PATCH_CTRL                0x0470
#define LR4_PATCH_JMP_ENABLES         0x0472
#define LR4_PATCH_JMP_ENABLES_HI      0x0472
#define LR4_PATCH_JMP_ENABLES_LO      0x0473
#define LR4_PATCH_DATA_ENABLES        0x0474
#define LR4_PATCH_DATA_ENABLES_HI     0x0474
#define LR4_PATCH_DATA_ENABLES_LO     0x0475
#define LR4_PATCH_OFFSET_0            0x0476
#define LR4_PATCH_OFFSET_0_HI         0x0476
#define LR4_PATCH_OFFSET_0_LO         0x0477
#define LR4_PATCH_OFFSET_1            0x0478
#define LR4_PATCH_OFFSET_1_HI         0x0478
#define LR4_PATCH_OFFSET_1_LO         0x0479
#define LR4_PATCH_OFFSET_2            0x047A
#define LR4_PATCH_OFFSET_2_HI         0x047A
#define LR4_PATCH_OFFSET_2_LO         0x047B
#define LR4_PATCH_OFFSET_3            0x047C
#define LR4_PATCH_OFFSET_3_HI         0x047C
#define LR4_PATCH_OFFSET_3_LO         0x047D
#define LR4_PATCH_OFFSET_4            0x047E
#define LR4_PATCH_OFFSET_4_HI         0x047E
#define LR4_PATCH_OFFSET_4_LO         0x047F
#define LR4_PATCH_OFFSET_5            0x0480
#define LR4_PATCH_OFFSET_5_HI         0x0480
#define LR4_PATCH_OFFSET_5_LO         0x0481
#define LR4_PATCH_OFFSET_6            0x0482
#define LR4_PATCH_OFFSET_6_HI         0x0482
#define LR4_PATCH_OFFSET_6_LO         0x0483
#define LR4_PATCH_OFFSET_7            0x0484
#define LR4_PATCH_OFFSET_7_HI         0x0484
#define LR4_PATCH_OFFSET_7_LO         0x0485
#define LR4_PATCH_OFFSET_8            0x0486
#define LR4_PATCH_OFFSET_8_HI         0x0486
#define LR4_PATCH_OFFSET_8_LO         0x0487
#define LR4_PATCH_OFFSET_9            0x0488
#define LR4_PATCH_OFFSET_9_HI         0x0488
#define LR4_PATCH_OFFSET_9_LO         0x0489
#define LR4_PATCH_OFFSET_10           0x048A
#define LR4_PATCH_OFFSET_10_HI        0x048A
#define LR4_PATCH_OFFSET_10_LO        0x048B
#define LR4_PATCH_OFFSET_11           0x048C
#define LR4_PATCH_OFFSET_11_HI        0x048C
#define LR4_PATCH_OFFSET_11_LO        0x048D
#define LR4_PATCH_OFFSET_12           0x048E
#define LR4_PATCH_OFFSET_12_HI        0x048E
#define LR4_PATCH_OFFSET_12_LO        0x048F
#define LR4_PATCH_OFFSET_13           0x0490
#define LR4_PATCH_OFFSET_13_HI        0x0490
#define LR4_PATCH_OFFSET_13_LO        0x0491
#define LR4_PATCH_OFFSET_14           0x0492
#define LR4_PATCH_OFFSET_14_HI        0x0492
#define LR4_PATCH_OFFSET_14_LO        0x0493
#define LR4_PATCH_OFFSET_15           0x0494
#define LR4_PATCH_OFFSET_15_HI        0x0494
#define LR4_PATCH_OFFSET_15_LO        0x0495
#define LR4_PATCH_ADDRESS_0           0x0496
#define LR4_PATCH_ADDRESS_0_HI        0x0496
#define LR4_PATCH_ADDRESS_0_LO        0x0497
#define LR4_PATCH_ADDRESS_1           0x0498
#define LR4_PATCH_ADDRESS_1_HI        0x0498
#define LR4_PATCH_ADDRESS_1_LO        0x0499
#define LR4_PATCH_ADDRESS_2           0x049A
#define LR4_PATCH_ADDRESS_2_HI        0x049A
#define LR4_PATCH_ADDRESS_2_LO        0x049B
#define LR4_PATCH_ADDRESS_3           0x049C
#define LR4_PATCH_ADDRESS_3_HI        0x049C
#define LR4_PATCH_ADDRESS_3_LO        0x049D
#define LR4_PATCH_ADDRESS_4           0x049E
#define LR4_PATCH_ADDRESS_4_HI        0x049E
#define LR4_PATCH_ADDRESS_4_LO        0x049F
#define LR4_PATCH_ADDRESS_5           0x04A0
#define LR4_PATCH_ADDRESS_5_HI        0x04A0
#define LR4_PATCH_ADDRESS_5_LO        0x04A1
#define LR4_PATCH_ADDRESS_6           0x04A2
#define LR4_PATCH_ADDRESS_6_HI        0x04A2
#define LR4_PATCH_ADDRESS_6_LO        0x04A3
#define LR4_PATCH_ADDRESS_7           0x04A4
#define LR4_PATCH_ADDRESS_7_HI        0x04A4
#define LR4_PATCH_ADDRESS_7_LO        0x04A5
#define LR4_PATCH_ADDRESS_8           0x04A6
#define LR4_PATCH_ADDRESS_8_HI        0x04A6
#define LR4_PATCH_ADDRESS_8_LO        0x04A7
#define LR4_PATCH_ADDRESS_9           0x04A8
#define LR4_PATCH_ADDRESS_9_HI        0x04A8
#define LR4_PATCH_ADDRESS_9_LO        0x04A9
#define LR4_PATCH_ADDRESS_10          0x04AA
#define LR4_PATCH_ADDRESS_10_HI       0x04AA
#define LR4_PATCH_ADDRESS_10_LO       0x04AB
#define LR4_PATCH_ADDRESS_11          0x04AC
#define LR4_PATCH_ADDRESS_11_HI       0x04AC
#define LR4_PATCH_ADDRESS_11_LO       0x04AD
#define LR4_PATCH_ADDRESS_12          0x04AE
#define LR4_PATCH_ADDRESS_12_HI       0x04AE
#define LR4_PATCH_ADDRESS_12_LO       0x04AF
#define LR4_PATCH_ADDRESS_13          0x04B0
#define LR4_PATCH_ADDRESS_13_HI       0x04B0
#define LR4_PATCH_ADDRESS_13_LO       0x04B1
#define LR4_PATCH_ADDRESS_14          0x04B2
#define LR4_PATCH_ADDRESS_14_HI       0x04B2
#define LR4_PATCH_ADDRESS_14_LO       0x04B3
#define LR4_PATCH_ADDRESS_15          0x04B4
#define LR4_PATCH_ADDRESS_15_HI       0x04B4
#define LR4_PATCH_ADDRESS_15_LO       0x04B5


#define LR4_SPI_ASYNC_MUX_CTRL               0x04C0
#define LR4_CLK_CONFIG                       0x04C4
#define LR4_GPIO_LV_MUX_CTRL                 0x04CC
#define LR4_GPIO_LV_PAD_CTRL                 0x04CD
#define LR4_PAD_I2C_LV_CONFIG                0x04D0
#define LR4_PAD_STARTUP_MODE_VALUE_RO_GO1    0x04D4
#define LR4_HOST_IF_STATUS_GO1               0x04D5
#define LR4_MCU_CLK_GATING_CTRL              0x04D8
/** \} */

/**
 * \defgroup test Test
 * \{
 */
#define LR4_TEST_BIST_ROM_CTRL                0x04E0
#define LR4_TEST_BIST_ROM_RESULT              0x04E1
#define LR4_TEST_BIST_ROM_MCU_SIG             0x04E2
#define LR4_TEST_BIST_ROM_MCU_SIG_HI          0x04E2
#define LR4_TEST_BIST_ROM_MCU_SIG_LO          0x04E3
#define LR4_TEST_BIST_RAM_CTRL                0x04E4
#define LR4_TEST_BIST_RAM_RESULT              0x04E5
#define LR4_TEST_TMC                          0x04E8
#define LR4_TEST_PLL_BIST_MIN_THRESHOLD       0x04F0
#define LR4_TEST_PLL_BIST_MIN_THRESHOLD_HI    0x04F0
#define LR4_TEST_PLL_BIST_MIN_THRESHOLD_LO    0x04F1
#define LR4_TEST_PLL_BIST_MAX_THRESHOLD       0x04F2
#define LR4_TEST_PLL_BIST_MAX_THRESHOLD_HI    0x04F2
#define LR4_TEST_PLL_BIST_MAX_THRESHOLD_LO    0x04F3
#define LR4_TEST_PLL_BIST_COUNT_OUT           0x04F4
#define LR4_TEST_PLL_BIST_COUNT_OUT_HI        0x04F4
#define LR4_TEST_PLL_BIST_COUNT_OUT_LO        0x04F5
#define LR4_TEST_PLL_BIST_GONOGO              0x04F6
#define LR4_TEST_PLL_BIST_CTRL                0x04F7
/** \} */

/**
 * \defgroup raning_core Raning core
 * \{
 */
#define LR4_RANGING_CORE_DEVICE_ID                                            0x0680
#define LR4_RANGING_CORE_REVISION_ID                                          0x0681
#define LR4_RANGING_CORE_CLK_CTRL1                                            0x0683
#define LR4_RANGING_CORE_CLK_CTRL2                                            0x0684
#define LR4_RANGING_CORE_WOI_1                                                0x0685
#define LR4_RANGING_CORE_WOI_REF_1                                            0x0686
#define LR4_RANGING_CORE_START_RANGING                                        0x0687
#define LR4_RANGING_CORE_LOW_LIMIT_1                                          0x0690
#define LR4_RANGING_CORE_HIGH_LIMIT_1                                         0x0691
#define LR4_RANGING_CORE_LOW_LIMIT_REF_1                                      0x0692
#define LR4_RANGING_CORE_HIGH_LIMIT_REF_1                                     0x0693
#define LR4_RANGING_CORE_QUANTIFIER_1_MSB                                     0x0694
#define LR4_RANGING_CORE_QUANTIFIER_1_LSB                                     0x0695
#define LR4_RANGING_CORE_QUANTIFIER_REF_1_MSB                                 0x0696
#define LR4_RANGING_CORE_QUANTIFIER_REF_1_LSB                                 0x0697
#define LR4_RANGING_CORE_AMBIENT_OFFSET_1_MSB                                 0x0698
#define LR4_RANGING_CORE_AMBIENT_OFFSET_1_LSB                                 0x0699
#define LR4_RANGING_CORE_AMBIENT_OFFSET_REF_1_MSB                             0x069A
#define LR4_RANGING_CORE_AMBIENT_OFFSET_REF_1_LSB                             0x069B
#define LR4_RANGING_CORE_FILTER_STRENGTH_1                                    0x069C
#define LR4_RANGING_CORE_FILTER_STRENGTH_REF_1                                0x069D
#define LR4_RANGING_CORE_SIGNAL_EVENT_LIMIT_1_MSB                             0x069E
#define LR4_RANGING_CORE_SIGNAL_EVENT_LIMIT_1_LSB                             0x069F
#define LR4_RANGING_CORE_SIGNAL_EVENT_LIMIT_REF_1_MSB                         0x06A0
#define LR4_RANGING_CORE_SIGNAL_EVENT_LIMIT_REF_1_LSB                         0x06A1
#define LR4_RANGING_CORE_TIMEOUT_OVERALL_PERIODS_MSB                          0x06A4
#define LR4_RANGING_CORE_TIMEOUT_OVERALL_PERIODS_LSB                          0x06A5
#define LR4_RANGING_CORE_INVERT_HW                                            0x06A6
#define LR4_RANGING_CORE_FORCE_HW                                             0x06A7
#define LR4_RANGING_CORE_STATIC_HW_VALUE                                      0x06A8
#define LR4_RANGING_CORE_FORCE_CONTINUOUS_AMBIENT                             0x06A9
#define LR4_RANGING_CORE_TEST_PHASE_SELECT_TO_FILTER                          0x06AA
#define LR4_RANGING_CORE_TEST_PHASE_SELECT_TO_TIMING_GEN                      0x06AB
#define LR4_RANGING_CORE_INITIAL_PHASE_VALUE_1                                0x06AC
#define LR4_RANGING_CORE_INITIAL_PHASE_VALUE_REF_1                            0x06AD
#define LR4_RANGING_CORE_FORCE_UP_IN                                          0x06AE
#define LR4_RANGING_CORE_FORCE_DN_IN                                          0x06AF
#define LR4_RANGING_CORE_STATIC_UP_VALUE_1                                    0x06B0
#define LR4_RANGING_CORE_STATIC_UP_VALUE_REF_1                                0x06B1
#define LR4_RANGING_CORE_STATIC_DN_VALUE_1                                    0x06B2
#define LR4_RANGING_CORE_STATIC_DN_VALUE_REF_1                                0x06B3
#define LR4_RANGING_CORE_MONITOR_UP_DN                                        0x06B4
#define LR4_RANGING_CORE_INVERT_UP_DN                                         0x06B5
#define LR4_RANGING_CORE_CPUMP_1                                              0x06B6
#define LR4_RANGING_CORE_CPUMP_2                                              0x06B7
#define LR4_RANGING_CORE_CPUMP_3                                              0x06B8
#define LR4_RANGING_CORE_OSC_1                                                0x06B9
#define LR4_RANGING_CORE_PLL_1                                                0x06BB
#define LR4_RANGING_CORE_PLL_2                                                0x06BC
#define LR4_RANGING_CORE_REFERENCE_1                                          0x06BD
#define LR4_RANGING_CORE_REFERENCE_3                                          0x06BF
#define LR4_RANGING_CORE_REFERENCE_4                                          0x06C0
#define LR4_RANGING_CORE_REFERENCE_5                                          0x06C1
#define LR4_RANGING_CORE_REGAVDD1V2                                           0x06C3
#define LR4_RANGING_CORE_CALIB_1                                              0x06C4
#define LR4_RANGING_CORE_CALIB_2                                              0x06C5
#define LR4_RANGING_CORE_CALIB_3                                              0x06C6
#define LR4_RANGING_CORE_TST_MUX_SEL1                                         0x06C9
#define LR4_RANGING_CORE_TST_MUX_SEL2                                         0x06CA
#define LR4_RANGING_CORE_TST_MUX                                              0x06CB
#define LR4_RANGING_CORE_GPIO_OUT_TESTMUX                                     0x06CC
#define LR4_RANGING_CORE_CUSTOM_FE                                            0x06CD
#define LR4_RANGING_CORE_CUSTOM_FE_2                                          0x06CE
#define LR4_RANGING_CORE_SPAD_READOUT                                         0x06CF
#define LR4_RANGING_CORE_SPAD_READOUT_1                                       0x06D0
#define LR4_RANGING_CORE_SPAD_READOUT_2                                       0x06D1
#define LR4_RANGING_CORE_SPAD_PS                                              0x06D2
#define LR4_RANGING_CORE_LASER_SAFETY_2                                       0x06D4
#define LR4_RANGING_CORE_NVM_CTRL_MODE                                        0x0780
#define LR4_RANGING_CORE_NVM_CTRL_PDN                                         0x0781
#define LR4_RANGING_CORE_NVM_CTRL_PROGN                                       0x0782
#define LR4_RANGING_CORE_NVM_CTRL_READN                                       0x0783
#define LR4_RANGING_CORE_NVM_CTRL_PULSE_WIDTH_MSB                             0x0784
#define LR4_RANGING_CORE_NVM_CTRL_PULSE_WIDTH_LSB                             0x0785
#define LR4_RANGING_CORE_NVM_CTRL_HV_RISE_MSB                                 0x0786
#define LR4_RANGING_CORE_NVM_CTRL_HV_RISE_LSB                                 0x0787
#define LR4_RANGING_CORE_NVM_CTRL_HV_FALL_MSB                                 0x0788
#define LR4_RANGING_CORE_NVM_CTRL_HV_FALL_LSB                                 0x0789
#define LR4_RANGING_CORE_NVM_CTRL_TST                                         0x078A
#define LR4_RANGING_CORE_NVM_CTRL_TESTREAD                                    0x078B
#define LR4_RANGING_CORE_NVM_CTRL_DATAIN_MMM                                  0x078C
#define LR4_RANGING_CORE_NVM_CTRL_DATAIN_LMM                                  0x078D
#define LR4_RANGING_CORE_NVM_CTRL_DATAIN_LLM                                  0x078E
#define LR4_RANGING_CORE_NVM_CTRL_DATAIN_LLL                                  0x078F
#define LR4_RANGING_CORE_NVM_CTRL_DATAOUT_MMM                                 0x0790
#define LR4_RANGING_CORE_NVM_CTRL_DATAOUT_LMM                                 0x0791
#define LR4_RANGING_CORE_NVM_CTRL_DATAOUT_LLM                                 0x0792
#define LR4_RANGING_CORE_NVM_CTRL_DATAOUT_LLL                                 0x0793
#define LR4_RANGING_CORE_NVM_CTRL_ADDR                                        0x0794
#define LR4_RANGING_CORE_NVM_CTRL_DATAOUT_ECC                                 0x0795
#define LR4_RANGING_CORE_RET_SPAD_EN_0                                        0x0796
#define LR4_RANGING_CORE_RET_SPAD_EN_1                                        0x0797
#define LR4_RANGING_CORE_RET_SPAD_EN_2                                        0x0798
#define LR4_RANGING_CORE_RET_SPAD_EN_3                                        0x0799
#define LR4_RANGING_CORE_RET_SPAD_EN_4                                        0x079A
#define LR4_RANGING_CORE_RET_SPAD_EN_5                                        0x079B
#define LR4_RANGING_CORE_RET_SPAD_EN_6                                        0x079C
#define LR4_RANGING_CORE_RET_SPAD_EN_7                                        0x079D
#define LR4_RANGING_CORE_RET_SPAD_EN_8                                        0x079E
#define LR4_RANGING_CORE_RET_SPAD_EN_9                                        0x079F
#define LR4_RANGING_CORE_RET_SPAD_EN_10                                       0x07A0
#define LR4_RANGING_CORE_RET_SPAD_EN_11                                       0x07A1
#define LR4_RANGING_CORE_RET_SPAD_EN_12                                       0x07A2
#define LR4_RANGING_CORE_RET_SPAD_EN_13                                       0x07A3
#define LR4_RANGING_CORE_RET_SPAD_EN_14                                       0x07A4
#define LR4_RANGING_CORE_RET_SPAD_EN_15                                       0x07A5
#define LR4_RANGING_CORE_RET_SPAD_EN_16                                       0x07A6
#define LR4_RANGING_CORE_RET_SPAD_EN_17                                       0x07A7
#define LR4_RANGING_CORE_SPAD_SHIFT_EN                                        0x07BA
#define LR4_RANGING_CORE_SPAD_DISABLE_CTRL                                    0x07BB
#define LR4_RANGING_CORE_SPAD_EN_SHIFT_OUT_DEBUG                              0x07BC
#define LR4_RANGING_CORE_SPI_MODE                                             0x07BD
#define LR4_RANGING_CORE_GPIO_DIR                                             0x07BE
#define LR4_RANGING_CORE_VCSEL_PERIOD                                         0x0880
#define LR4_RANGING_CORE_VCSEL_START                                          0x0881
#define LR4_RANGING_CORE_VCSEL_STOP                                           0x0882
#define LR4_RANGING_CORE_VCSEL_1                                              0x0885
#define LR4_RANGING_CORE_VCSEL_STATUS                                         0x088D
#define LR4_RANGING_CORE_STATUS                                               0x0980
#define LR4_RANGING_CORE_LASER_CONTINUITY_STATE                               0x0981
#define LR4_RANGING_CORE_RANGE_1_MMM                                          0x0982
#define LR4_RANGING_CORE_RANGE_1_LMM                                          0x0983
#define LR4_RANGING_CORE_RANGE_1_LLM                                          0x0984
#define LR4_RANGING_CORE_RANGE_1_LLL                                          0x0985
#define LR4_RANGING_CORE_RANGE_REF_1_MMM                                      0x0986
#define LR4_RANGING_CORE_RANGE_REF_1_LMM                                      0x0987
#define LR4_RANGING_CORE_RANGE_REF_1_LLM                                      0x0988
#define LR4_RANGING_CORE_RANGE_REF_1_LLL                                      0x0989
#define LR4_RANGING_CORE_AMBIENT_WINDOW_EVENTS_1_MMM                          0x098A
#define LR4_RANGING_CORE_AMBIENT_WINDOW_EVENTS_1_LMM                          0x098B
#define LR4_RANGING_CORE_AMBIENT_WINDOW_EVENTS_1_LLM                          0x098C
#define LR4_RANGING_CORE_AMBIENT_WINDOW_EVENTS_1_LLL                          0x098D
#define LR4_RANGING_CORE_RANGING_TOTAL_EVENTS_1_MMM                           0x098E
#define LR4_RANGING_CORE_RANGING_TOTAL_EVENTS_1_LMM                           0x098F
#define LR4_RANGING_CORE_RANGING_TOTAL_EVENTS_1_LLM                           0x0990
#define LR4_RANGING_CORE_RANGING_TOTAL_EVENTS_1_LLL                           0x0991
#define LR4_RANGING_CORE_SIGNAL_TOTAL_EVENTS_1_MMM                            0x0992
#define LR4_RANGING_CORE_SIGNAL_TOTAL_EVENTS_1_LMM                            0x0993
#define LR4_RANGING_CORE_SIGNAL_TOTAL_EVENTS_1_LLM                            0x0994
#define LR4_RANGING_CORE_SIGNAL_TOTAL_EVENTS_1_LLL                            0x0995
#define LR4_RANGING_CORE_TOTAL_PERIODS_ELAPSED_1_MM                           0x0996
#define LR4_RANGING_CORE_TOTAL_PERIODS_ELAPSED_1_LM                           0x0997
#define LR4_RANGING_CORE_TOTAL_PERIODS_ELAPSED_1_LL                           0x0998
#define LR4_RANGING_CORE_AMBIENT_MISMATCH_MM                                  0x0999
#define LR4_RANGING_CORE_AMBIENT_MISMATCH_LM                                  0x099A
#define LR4_RANGING_CORE_AMBIENT_MISMATCH_LL                                  0x099B
#define LR4_RANGING_CORE_AMBIENT_WINDOW_EVENTS_REF_1_MMM                      0x099C
#define LR4_RANGING_CORE_AMBIENT_WINDOW_EVENTS_REF_1_LMM                      0x099D
#define LR4_RANGING_CORE_AMBIENT_WINDOW_EVENTS_REF_1_LLM                      0x099E
#define LR4_RANGING_CORE_AMBIENT_WINDOW_EVENTS_REF_1_LLL                      0x099F
#define LR4_RANGING_CORE_RANGING_TOTAL_EVENTS_REF_1_MMM                       0x09A0
#define LR4_RANGING_CORE_RANGING_TOTAL_EVENTS_REF_1_LMM                       0x09A1
#define LR4_RANGING_CORE_RANGING_TOTAL_EVENTS_REF_1_LLM                       0x09A2
#define LR4_RANGING_CORE_RANGING_TOTAL_EVENTS_REF_1_LLL                       0x09A3
#define LR4_RANGING_CORE_SIGNAL_TOTAL_EVENTS_REF_1_MMM                        0x09A4
#define LR4_RANGING_CORE_SIGNAL_TOTAL_EVENTS_REF_1_LMM                        0x09A5
#define LR4_RANGING_CORE_SIGNAL_TOTAL_EVENTS_REF_1_LLM                        0x09A6
#define LR4_RANGING_CORE_SIGNAL_TOTAL_EVENTS_REF_1_LLL                        0x09A7
#define LR4_RANGING_CORE_TOTAL_PERIODS_ELAPSED_REF_1_MM                       0x09A8
#define LR4_RANGING_CORE_TOTAL_PERIODS_ELAPSED_REF_1_LM                       0x09A9
#define LR4_RANGING_CORE_TOTAL_PERIODS_ELAPSED_REF_1_LL                       0x09AA
#define LR4_RANGING_CORE_AMBIENT_MISMATCH_REF_MM                              0x09AB
#define LR4_RANGING_CORE_AMBIENT_MISMATCH_REF_LM                              0x09AC
#define LR4_RANGING_CORE_AMBIENT_MISMATCH_REF_LL                              0x09AD
#define LR4_RANGING_CORE_GPIO_CONFIG__A0                                      0x0A00
#define LR4_RANGING_CORE_RESET_CONTROL__A0                                    0x0A01
#define LR4_RANGING_CORE_INTR_MANAGER__A0                                     0x0A02
#define LR4_RANGING_CORE_POWER_FSM_TIME_OSC__A0                               0x0A06
#define LR4_RANGING_CORE_VCSEL_ATEST__A0                                      0x0A07
#define LR4_RANGING_CORE_VCSEL_PERIOD_CLIPPED__A0                             0x0A08
#define LR4_RANGING_CORE_VCSEL_STOP_CLIPPED__A0                               0x0A09
#define LR4_RANGING_CORE_CALIB_2__A0                                          0x0A0A
#define LR4_RANGING_CORE_STOP_CONDITION__A0                                   0x0A0B
#define LR4_RANGING_CORE_STATUS_RESET__A0                                     0x0A0C
#define LR4_RANGING_CORE_READOUT_CFG__A0                                      0x0A0D
#define LR4_RANGING_CORE_WINDOW_SETTING__A0                                   0x0A0E
#define LR4_RANGING_CORE_VCSEL_DELAY__A0                                      0x0A1A
#define LR4_RANGING_CORE_REFERENCE_2__A0                                      0x0A1B
#define LR4_RANGING_CORE_REGAVDD1V2__A0                                       0x0A1D
#define LR4_RANGING_CORE_TST_MUX__A0                                          0x0A1F
#define LR4_RANGING_CORE_CUSTOM_FE_2__A0                                      0x0A20
#define LR4_RANGING_CORE_SPAD_READOUT__A0                                     0x0A21
#define LR4_RANGING_CORE_CPUMP_1__A0                                          0x0A22
#define LR4_RANGING_CORE_SPARE_REGISTER__A0                                   0x0A23
#define LR4_RANGING_CORE_VCSEL_CONT_STAGE5_BYPASS__A0                         0x0A24
#define LR4_RANGING_CORE_RET_SPAD_EN_18                                       0x0A25
#define LR4_RANGING_CORE_RET_SPAD_EN_19                                       0x0A26
#define LR4_RANGING_CORE_RET_SPAD_EN_20                                       0x0A27
#define LR4_RANGING_CORE_RET_SPAD_EN_21                                       0x0A28
#define LR4_RANGING_CORE_RET_SPAD_EN_22                                       0x0A29
#define LR4_RANGING_CORE_RET_SPAD_EN_23                                       0x0A2A
#define LR4_RANGING_CORE_RET_SPAD_EN_24                                       0x0A2B
#define LR4_RANGING_CORE_RET_SPAD_EN_25                                       0x0A2C
#define LR4_RANGING_CORE_RET_SPAD_EN_26                                       0x0A2D
#define LR4_RANGING_CORE_RET_SPAD_EN_27                                       0x0A2E
#define LR4_RANGING_CORE_RET_SPAD_EN_28                                       0x0A2F
#define LR4_RANGING_CORE_RET_SPAD_EN_29                                       0x0A30
#define LR4_RANGING_CORE_RET_SPAD_EN_30                                       0x0A31
#define LR4_RANGING_CORE_RET_SPAD_EN_31                                       0x0A32
#define LR4_RANGING_CORE_REF_SPAD_EN_0__EWOK                                  0x0A33
#define LR4_RANGING_CORE_REF_SPAD_EN_1__EWOK                                  0x0A34
#define LR4_RANGING_CORE_REF_SPAD_EN_2__EWOK                                  0x0A35
#define LR4_RANGING_CORE_REF_SPAD_EN_3__EWOK                                  0x0A36
#define LR4_RANGING_CORE_REF_SPAD_EN_4__EWOK                                  0x0A37
#define LR4_RANGING_CORE_REF_SPAD_EN_5__EWOK                                  0x0A38
#define LR4_RANGING_CORE_REF_EN_START_SELECT                                  0x0A39
#define LR4_RANGING_CORE_REGDVDD1V2_ATEST__EWOK                               0x0A41

#define LR4_SOFT_RESET_GO1                                                    0x0B00
#define LR4_PRIVATE__PATCH_BASE_ADDR_RSLV                                     0x0E00
/** \} */

/**
 * \defgroup shutdown Shutdown
 * \{
 */
#define LR4_PREV_SHADOW_RESULT_INTERRUPT_STATUS                               0x0ED0
#define LR4_PREV_SHADOW_RESULT_RANGE_STATUS                                   0x0ED1
#define LR4_PREV_SHADOW_RESULT_REPORT_STATUS                                  0x0ED2
#define LR4_PREV_SHADOW_RESULT_STREAM_COUNT                                   0x0ED3
#define LR4_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0                 0x0ED4
#define LR4_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_HI              0x0ED4
#define LR4_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_LO              0x0ED5
#define LR4_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0                0x0ED6
#define LR4_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_HI             0x0ED6
#define LR4_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_LO             0x0ED7
#define LR4_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0                    0x0ED8
#define LR4_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_HI                 0x0ED8
#define LR4_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_LO                 0x0ED9
#define LR4_PREV_SHADOW_RESULT_SIGMA_SD0                                      0x0EDA
#define LR4_PREV_SHADOW_RESULT_SIGMA_SD0_HI                                   0x0EDA
#define LR4_PREV_SHADOW_RESULT_SIGMA_SD0_LO                                   0x0EDB
#define LR4_PREV_SHADOW_RESULT_PHASE_SD0                                      0x0EDC
#define LR4_PREV_SHADOW_RESULT_PHASE_SD0_HI                                   0x0EDC
#define LR4_PREV_SHADOW_RESULT_PHASE_SD0_LO                                   0x0EDD
#define LR4_PREV_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0         0x0EDE
#define LR4_PREV_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_HI      0x0EDE
#define LR4_PREV_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_LO      0x0EDF

#define LR4_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCP     0x0EE0
#define LR4_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCP_MSB 0x0EE0
#define LR4_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCP_LSB 0x0EE1

#define LR4_PREV_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0           0x0EE2
#define LR4_PREV_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_HI        0x0EE2
#define LR4_PREV_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_LO        0x0EE3
#define LR4_PREV_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0           0x0EE4
#define LR4_PREV_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_HI        0x0EE4
#define LR4_PREV_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_LO        0x0EE5
#define LR4_PREV_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0                0x0EE6
#define LR4_PREV_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_HI             0x0EE6
#define LR4_PREV_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_LO             0x0EE7
#define LR4_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1                0x0EE8
#define LR4_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_HI             0x0EE8
#define LR4_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_LO             0x0EE9
#define LR4_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1               0x0EEA
#define LR4_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_HI            0x0EEA
#define LR4_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_LO            0x0EEB
#define LR4_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1                   0x0EEC
#define LR4_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_HI                0x0EEC
#define LR4_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_LO                0x0EED
#define LR4_PREV_SHADOW_RESULT_SIGMA_SD1                                     0x0EEE
#define LR4_PREV_SHADOW_RESULT_SIGMA_SD1_HI                                  0x0EEE
#define LR4_PREV_SHADOW_RESULT_SIGMA_SD1_LO                                  0x0EEF
#define LR4_PREV_SHADOW_RESULT_PHASE_SD1                                     0x0EF0
#define LR4_PREV_SHADOW_RESULT_PHASE_SD1_HI                                  0x0EF0
#define LR4_PREV_SHADOW_RESULT_PHASE_SD1_LO                                  0x0EF1
#define LR4_PREV_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1        0x0EF2
#define LR4_PREV_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_HI     0x0EF2
#define LR4_PREV_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_LO     0x0EF3
#define LR4_PREV_SHADOW_RESULT_SPARE_0_SD1                                   0x0EF4
#define LR4_PREV_SHADOW_RESULT_SPARE_0_SD1_HI                                0x0EF4
#define LR4_PREV_SHADOW_RESULT_SPARE_0_SD1_LO                                0x0EF5
#define LR4_PREV_SHADOW_RESULT_SPARE_1_SD1                                   0x0EF6
#define LR4_PREV_SHADOW_RESULT_SPARE_1_SD1_HI                                0x0EF6
#define LR4_PREV_SHADOW_RESULT_SPARE_1_SD1_LO                                0x0EF7
#define LR4_PREV_SHADOW_RESULT_SPARE_2_SD1                                   0x0EF8
#define LR4_PREV_SHADOW_RESULT_SPARE_2_SD1_HI                                0x0EF8
#define LR4_PREV_SHADOW_RESULT_SPARE_2_SD1_LO                                0x0EF9
#define LR4_PREV_SHADOW_RESULT_SPARE_3_SD1                                   0x0EFA
#define LR4_PREV_SHADOW_RESULT_SPARE_3_SD1_HI                                0x0EFA
#define LR4_PREV_SHADOW_RESULT_SPARE_3_SD1_LO                                0x0EFB

#define LR4_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0                0x0EFC
#define LR4_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_3              0x0EFC
#define LR4_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_2              0x0EFD
#define LR4_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_1              0x0EFE
#define LR4_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_0              0x0EFF
#define LR4_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0                 0x0F00
#define LR4_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_3               0x0F00
#define LR4_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_2               0x0F01
#define LR4_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_1               0x0F02
#define LR4_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_0               0x0F03
#define LR4_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0                  0x0F04
#define LR4_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_3                0x0F04
#define LR4_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_2                0x0F05
#define LR4_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_1                0x0F06
#define LR4_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_0                0x0F07
#define LR4_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0                0x0F08
#define LR4_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_3              0x0F08
#define LR4_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_2              0x0F09
#define LR4_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_1              0x0F0A
#define LR4_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_0              0x0F0B
#define LR4_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1                0x0F0C
#define LR4_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_3              0x0F0C
#define LR4_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_2              0x0F0D
#define LR4_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_1              0x0F0E
#define LR4_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_0              0x0F0F
#define LR4_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1                 0x0F10
#define LR4_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_3               0x0F10
#define LR4_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_2               0x0F11
#define LR4_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_1               0x0F12
#define LR4_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_0               0x0F13
#define LR4_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1                  0x0F14
#define LR4_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_3                0x0F14
#define LR4_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_2                0x0F15
#define LR4_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_1                0x0F16
#define LR4_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_0                0x0F17
#define LR4_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1                0x0F18
#define LR4_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_3              0x0F18
#define LR4_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_2              0x0F19
#define LR4_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_1              0x0F1A
#define LR4_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_0              0x0F1B
#define LR4_PREV_SHADOW_RESULT_CORE_SPARE_0                                  0x0F1C
/** \} */

/**
 * \defgroup debug Debug
 * \{
 */
#define LR4_RESULT_DEBUG_STATUS                                              0x0F20
#define LR4_RESULT_DEBUG_STAGE                                               0x0F21
/** \} */

/**
 * \defgroup gph_system_cfg GPH system-cfg
 * \{
 */
#define LR4_GPH_SYSTEM_THRESH_RATE_HIGH                                     0x0F24
#define LR4_GPH_SYSTEM_THRESH_RATE_HIGH_HI                                  0x0F24
#define LR4_GPH_SYSTEM_THRESH_RATE_HIGH_LO                                  0x0F25
#define LR4_GPH_SYSTEM_THRESH_RATE_LOW                                      0x0F26
#define LR4_GPH_SYSTEM_THRESH_RATE_LOW_HI                                   0x0F26
#define LR4_GPH_SYSTEM_THRESH_RATE_LOW_LO                                   0x0F27
#define LR4_GPH_SYSTEM_INTERRUPT_CONFIG_GPIO                                0x0F28
#define LR4_GPH_DSS_CONFIG_ROI_MODE_CONTROL                                 0x0F2F
#define LR4_GPH_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT                    0x0F30
#define LR4_GPH_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT_HI                 0x0F30
#define LR4_GPH_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT_LO                 0x0F31
#define LR4_GPH_DSS_CONFIG_MANUAL_BLOCK_SELECT                              0x0F32
#define LR4_GPH_DSS_CONFIG_MAX_SPADS_LIMIT                                  0x0F33
#define LR4_GPH_DSS_CONFIG_MIN_SPADS_LIMIT                                  0x0F34
#define LR4_GPH_MM_CONFIG_TIMEOUT_MACROP_A_HI                               0x0F36
#define LR4_GPH_MM_CONFIG_TIMEOUT_MACROP_A_LO                               0x0F37
#define LR4_GPH_MM_CONFIG_TIMEOUT_MACROP_B_HI                               0x0F38
#define LR4_GPH_MM_CONFIG_TIMEOUT_MACROP_B_LO                               0x0F39
#define LR4_GPH_RANGE_CONFIG_TIMEOUT_MACROP_A_HI                            0x0F3A
#define LR4_GPH_RANGE_CONFIG_TIMEOUT_MACROP_A_LO                            0x0F3B
#define LR4_GPH_RANGE_CONFIG_VCSEL_PERIOD_A                                 0x0F3C
#define LR4_GPH_RANGE_CONFIG_VCSEL_PERIOD_B                                 0x0F3D
#define LR4_GPH_RANGE_CONFIG_TIMEOUT_MACROP_B_HI                            0x0F3E
#define LR4_GPH_RANGE_CONFIG_TIMEOUT_MACROP_B_LO                            0x0F3F
#define LR4_GPH_RANGE_CONFIG_SIGMA_THRESH                                   0x0F40
#define LR4_GPH_RANGE_CONFIG_SIGMA_THRESH_HI                                0x0F40
#define LR4_GPH_RANGE_CONFIG_SIGMA_THRESH_LO                                0x0F41
#define LR4_GPH_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS                  0x0F42
#define LR4_GPH_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS_HI               0x0F42
#define LR4_GPH_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS_LO               0x0F43
#define LR4_GPH_RANGE_CONFIG_VALID_PHASE_LOW                                0x0F44
#define LR4_GPH_RANGE_CONFIG_VALID_PHASE_HIGH                               0x0F45


#define LR4_FIRMWARE__INTERNAL_STREAM_COUNT_DIV                             0x0F46
#define LR4_FIRMWARE__INTERNAL_STREAM_COUNTER_VAL                           0x0F47
/** \} */

/**
 * \defgroup dss_calc Dss calc.
 * \{
 */
#define LR4_DSS_CALC_ROI_CTRL                0x0F54
#define LR4_DSS_CALC_SPARE_1                 0x0F55
#define LR4_DSS_CALC_SPARE_2                 0x0F56
#define LR4_DSS_CALC_SPARE_3                 0x0F57
#define LR4_DSS_CALC_SPARE_4                 0x0F58
#define LR4_DSS_CALC_SPARE_5                 0x0F59
#define LR4_DSS_CALC_SPARE_6                 0x0F5A
#define LR4_DSS_CALC_SPARE_7                 0x0F5B
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_0      0x0F5C
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_1      0x0F5D
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_2      0x0F5E
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_3      0x0F5F
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_4      0x0F60
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_5      0x0F61
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_6      0x0F62
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_7      0x0F63
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_8      0x0F64
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_9      0x0F65
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_10     0x0F66
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_11     0x0F67
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_12     0x0F68
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_13     0x0F69
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_14     0x0F6A
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_15     0x0F6B
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_16     0x0F6C
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_17     0x0F6D
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_18     0x0F6E
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_19     0x0F6F
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_20     0x0F70
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_21     0x0F71
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_22     0x0F72
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_23     0x0F73
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_24     0x0F74
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_25     0x0F75
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_26     0x0F76
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_27     0x0F77
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_28     0x0F78
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_29     0x0F79
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_30     0x0F7A
#define LR4_DSS_CALC_USER_ROI_SPAD_EN_31     0x0F7B
#define LR4_DSS_CALC_USER_ROI_0              0x0F7C
#define LR4_DSS_CALC_USER_ROI_1              0x0F7D
#define LR4_DSS_CALC_MODE_ROI_0              0x0F7E
#define LR4_DSS_CALC_MODE_ROI_1              0x0F7F
/** \} */

/**
 * \defgroup sigma_estimator Sigma estimator
 * \{
 */
#define LR4_SIGMA_ESTIMATOR_CALC_SPARE_0                                     0x0F80
/** \} */

/**
 * \defgroup vhv_result VHV result
 * \{
 */
#define LR4_VHV_RESULT_PEAK_SIGNAL_RATE_MCPS        0x0F82
#define LR4_VHV_RESULT_PEAK_SIGNAL_RATE_MCPS_HI     0x0F82
#define LR4_VHV_RESULT_PEAK_SIGNAL_RATE_MCPS_LO     0x0F83
#define LR4_VHV_RESULT_SIGNAL_TOTAL_EVENTS_REF      0x0F84
#define LR4_VHV_RESULT_SIGNAL_TOTAL_EVENTS_REF_3    0x0F84
#define LR4_VHV_RESULT_SIGNAL_TOTAL_EVENTS_REF_2    0x0F85
#define LR4_VHV_RESULT_SIGNAL_TOTAL_EVENTS_REF_1    0x0F86
#define LR4_VHV_RESULT_SIGNAL_TOTAL_EVENTS_REF_0    0x0F87
/** \} */

/**
 * \defgroup phasecal_result_phase Phasecal result phase
 * \{
 */
#define LR4_PHASECAL_RESULT_PHASE_OUTPUT_REF                                 0x0F88
#define LR4_PHASECAL_RESULT_PHASE_OUTPUT_REF_HI                              0x0F88
#define LR4_PHASECAL_RESULT_PHASE_OUTPUT_REF_LO                              0x0F89
/** \} */

/**
 * \defgroup dss_result DSS result
 * \{
 */
#define LR4_DSS_RESULT_TOTAL_RATE_PER_SPAD                                   0x0F8A
#define LR4_DSS_RESULT_TOTAL_RATE_PER_SPAD_HI                                0x0F8A
#define LR4_DSS_RESULT_TOTAL_RATE_PER_SPAD_LO                                0x0F8B
#define LR4_DSS_RESULT_ENABLED_BLOCKS                                        0x0F8C
#define LR4_DSS_RESULT_NUM_REQUESTED_SPADS                                   0x0F8E
#define LR4_DSS_RESULT_NUM_REQUESTED_SPADS_HI                                0x0F8E
#define LR4_DSS_RESULT_NUM_REQUESTED_SPADS_LO                                0x0F8F
/** \} */

/**
 * \defgroup mm_result MM result
 * \{
 */
#define LR4_MM_RESULT_INNER_INTERSECTION_RATE                                0x0F92
#define LR4_MM_RESULT_INNER_INTERSECTION_RATE_HI                             0x0F92
#define LR4_MM_RESULT_INNER_INTERSECTION_RATE_LO                             0x0F93
#define LR4_MM_RESULT_OUTER_COMPLEMENT_RATE                                  0x0F94
#define LR4_MM_RESULT_OUTER_COMPLEMENT_RATE_HI                               0x0F94
#define LR4_MM_RESULT_OUTER_COMPLEMENT_RATE_LO                               0x0F95
#define LR4_MM_RESULT_TOTAL_OFFSET                                           0x0F96
#define LR4_MM_RESULT_TOTAL_OFFSET_HI                                        0x0F96
#define LR4_MM_RESULT_TOTAL_OFFSET_LO                                        0x0F97
/** \} */

/**
 * \defgroup xtalk_calc XTALK calc.
 * \{
 */
#define LR4_XTALK_CALC_XTALK_FOR_ENABLED_SPADS                               0x0F98
#define LR4_XTALK_CALC_XTALK_FOR_ENABLED_SPADS_3                             0x0F98
#define LR4_XTALK_CALC_XTALK_FOR_ENABLED_SPADS_2                             0x0F99
#define LR4_XTALK_CALC_XTALK_FOR_ENABLED_SPADS_1                             0x0F9A
#define LR4_XTALK_CALC_XTALK_FOR_ENABLED_SPADS_0                             0x0F9B
/** \} */

/**
 * \defgroup xtalk_result XTALK result
 * \{
 */
#define LR4_XTALK_RESULT_AVG_XTALK_USER_ROI_KCPS                             0x0F9C
#define LR4_XTALK_RESULT_AVG_XTALK_USER_ROI_KCPS_3                           0x0F9C
#define LR4_XTALK_RESULT_AVG_XTALK_USER_ROI_KCPS_2                           0x0F9D
#define LR4_XTALK_RESULT_AVG_XTALK_USER_ROI_KCPS_1                           0x0F9E
#define LR4_XTALK_RESULT_AVG_XTALK_USER_ROI_KCPS_0                           0x0F9F
#define LR4_XTALK_RESULT_AVG_XTALK_MM_INNER_ROI_KCPS                         0x0FA0
#define LR4_XTALK_RESULT_AVG_XTALK_MM_INNER_ROI_KCPS_3                       0x0FA0
#define LR4_XTALK_RESULT_AVG_XTALK_MM_INNER_ROI_KCPS_2                       0x0FA1
#define LR4_XTALK_RESULT_AVG_XTALK_MM_INNER_ROI_KCPS_1                       0x0FA2
#define LR4_XTALK_RESULT_AVG_XTALK_MM_INNER_ROI_KCPS_0                       0x0FA3
#define LR4_XTALK_RESULT_AVG_XTALK_MM_OUTER_ROI_KCPS                         0x0FA4
#define LR4_XTALK_RESULT_AVG_XTALK_MM_OUTER_ROI_KCPS_3                       0x0FA4
#define LR4_XTALK_RESULT_AVG_XTALK_MM_OUTER_ROI_KCPS_2                       0x0FA5
#define LR4_XTALK_RESULT_AVG_XTALK_MM_OUTER_ROI_KCPS_1                       0x0FA6
#define LR4_XTALK_RESULT_AVG_XTALK_MM_OUTER_ROI_KCPS_0                       0x0FA7
#define LR4_RANGE_RESULT_ACCUM_PHASE                                         0x0FA8
#define LR4_RANGE_RESULT_ACCUM_PHASE_3                                       0x0FA8
#define LR4_RANGE_RESULT_ACCUM_PHASE_2                                       0x0FA9
#define LR4_RANGE_RESULT_ACCUM_PHASE_1                                       0x0FAA
#define LR4_RANGE_RESULT_ACCUM_PHASE_0                                       0x0FAB
#define LR4_RANGE_RESULT_OFFSET_CORRECTED_RANGE                              0x0FAC
#define LR4_RANGE_RESULT_OFFSET_CORRECTED_RANGE_HI                           0x0FAC
#define LR4_RANGE_RESULT_OFFSET_CORRECTED_RANGE_LO                           0x0FAD
/** \} */

/**
 * \defgroup shadow_result Shadow result
 * \{
 */
#define LR4_SHADOW_PHASECAL_RESULT_VCSEL_START                               0x0FAE
#define LR4_SHADOW_RESULT_INTERRUPT_STATUS                                   0x0FB0
#define LR4_SHADOW_RESULT_RANGE_STATUS                                       0x0FB1
#define LR4_SHADOW_RESULT_REPORT_STATUS                                      0x0FB2
#define LR4_SHADOW_RESULT_STREAM_COUNT                                       0x0FB3
#define LR4_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0                     0x0FB4
#define LR4_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_HI                  0x0FB4
#define LR4_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_LO                  0x0FB5
#define LR4_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0                    0x0FB6
#define LR4_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_HI                 0x0FB6
#define LR4_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_LO                 0x0FB7
#define LR4_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0                        0x0FB8
#define LR4_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_HI                     0x0FB8
#define LR4_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_LO                     0x0FB9
#define LR4_SHADOW_RESULT_SIGMA_SD0                                          0x0FBA
#define LR4_SHADOW_RESULT_SIGMA_SD0_HI                                       0x0FBA
#define LR4_SHADOW_RESULT_SIGMA_SD0_LO                                       0x0FBB
#define LR4_SHADOW_RESULT_PHASE_SD0                                          0x0FBC
#define LR4_SHADOW_RESULT_PHASE_SD0_HI                                       0x0FBC
#define LR4_SHADOW_RESULT_PHASE_SD0_LO                                       0x0FBD
#define LR4_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0             0x0FBE
#define LR4_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_HI          0x0FBE

#define LR4_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_LO                   0x0FBF
#define LR4_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0         0x0FC0
#define LR4_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_HI      0x0FC0
#define LR4_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_LO      0x0FC1
#define LR4_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0                         0x0FC2
#define LR4_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_HI                      0x0FC2
#define LR4_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_LO                      0x0FC3
#define LR4_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0                         0x0FC4
#define LR4_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_HI                      0x0FC4
#define LR4_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_LO                      0x0FC5
#define LR4_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0                              0x0FC6
#define LR4_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_HI                           0x0FC6
#define LR4_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_LO                           0x0FC7
#define LR4_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1                              0x0FC8
#define LR4_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_HI                           0x0FC8
#define LR4_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_LO                           0x0FC9
#define LR4_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1                             0x0FCA
#define LR4_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_HI                          0x0FCA
#define LR4_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_LO                          0x0FCB
#define LR4_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1                                 0x0FCC
#define LR4_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_HI                              0x0FCC
#define LR4_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_LO                              0x0FCD
#define LR4_SHADOW_RESULT_SIGMA_SD1                                                   0x0FCE
#define LR4_SHADOW_RESULT_SIGMA_SD1_HI                                                0x0FCE
#define LR4_SHADOW_RESULT_SIGMA_SD1_LO                                                0x0FCF
#define LR4_SHADOW_RESULT_PHASE_SD1                                                   0x0FD0
#define LR4_SHADOW_RESULT_PHASE_SD1_HI                                                0x0FD0
#define LR4_SHADOW_RESULT_PHASE_SD1_LO                                                0x0FD1
#define LR4_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1                      0x0FD2
#define LR4_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_HI                   0x0FD2
#define LR4_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_LO                   0x0FD3
#define LR4_SHADOW_RESULT_SPARE_0_SD1                                                 0x0FD4
#define LR4_SHADOW_RESULT_SPARE_0_SD1_HI                                              0x0FD4
#define LR4_SHADOW_RESULT_SPARE_0_SD1_LO                                              0x0FD5
#define LR4_SHADOW_RESULT_SPARE_1_SD1                                                 0x0FD6
#define LR4_SHADOW_RESULT_SPARE_1_SD1_HI                                              0x0FD6
#define LR4_SHADOW_RESULT_SPARE_1_SD1_LO                                              0x0FD7
#define LR4_SHADOW_RESULT_SPARE_2_SD1                                                 0x0FD8
#define LR4_SHADOW_RESULT_SPARE_2_SD1_HI                                              0x0FD8
#define LR4_SHADOW_RESULT_SPARE_2_SD1_LO                                              0x0FD9
#define LR4_SHADOW_RESULT_SPARE_3_SD1                                                 0x0FDA
#define LR4_SHADOW_RESULT_THRESH_INFO                                                 0x0FDB
#define LR4_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0                              0x0FDC
#define LR4_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_3                            0x0FDC
#define LR4_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_2                            0x0FDD
#define LR4_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_1                            0x0FDE
#define LR4_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_0                            0x0FDF
#define LR4_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0                               0x0FE0
#define LR4_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_3                             0x0FE0
#define LR4_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_2                             0x0FE1
#define LR4_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_1                             0x0FE2
#define LR4_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_0                             0x0FE3
#define LR4_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0                                0x0FE4
#define LR4_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_3                              0x0FE4
#define LR4_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_2                              0x0FE5
#define LR4_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_1                              0x0FE6
#define LR4_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_0                              0x0FE7
#define LR4_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0                              0x0FE8
#define LR4_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_3                            0x0FE8
#define LR4_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_2                            0x0FE9
#define LR4_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_1                            0x0FEA
#define LR4_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_0                            0x0FEB
#define LR4_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1                              0x0FEC
#define LR4_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_3                            0x0FEC
#define LR4_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_2                            0x0FED
#define LR4_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_1                            0x0FEE
#define LR4_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_0                            0x0FEF
#define LR4_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1                               0x0FF0
#define LR4_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_3                             0x0FF0
#define LR4_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_2                             0x0FF1
#define LR4_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_1                             0x0FF2
#define LR4_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_0                             0x0FF3
#define LR4_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1                                0x0FF4
#define LR4_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_3                              0x0FF4
#define LR4_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_2                              0x0FF5
#define LR4_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_1                              0x0FF6
#define LR4_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_0                              0x0FF7
#define LR4_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1                              0x0FF8
#define LR4_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_3                            0x0FF8
#define LR4_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_2                            0x0FF9
#define LR4_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_1                            0x0FFA
#define LR4_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_0                            0x0FFB
#define LR4_SHADOW_RESULT_CORE_SPARE_0                                                0x0FFC
#define LR4_SHADOW_PHASECAL_RESULT_REFERENCE_PHASE_HI                                 0x0FFE
#define LR4_SHADOW_PHASECAL_RESULT_REFERENCE_PHASE_LO                                 0x0FFF
/** \} */

/**
 * \defgroup distance Distance
 * \{
 */
#define LR4_DISTANCE_MODE_SHORT   0x00
#define LR4_DISTANCE_MODE_MEDIUM  0x01
#define LR4_DISTANCE_MODE_LONG    0x02
/** \} */

/**
 * \defgroup resp Response
 * \{
 */
#define LR4_RESP_INSUFFICIENT_BUDGET           0x02
#define LR4_RESP_TOO_HIGH_BUDGET               0x01
#define LR4_RESP_BUDGET_IS_SUCCESSFULLY_SET    0x00
#define LR4_RESP_DEVICE_ERROR_ID_IS_NOT_VALID  0x01
#define LR4_RESP_FIRMWARE_TIMEOUT_ERROR        0x02
#define LR4_RESP_INIT_IS_SUCCESSFUL            0x00
#define LR4_RESP_WRONG_MODE                    0x01
#define LR4_RESP_MODE_SUCCESSFULLY_SET         0x00
#define LR4_MRESP_SIGNAL_FAIL                  0x04
#define LR4_MRESP_PHASE_OUT_OF_VALID_LIMITS    0x05
#define LR4_MRESP_SIGMA_FAIL                   0x06
#define LR4_MRESP_WRAP_TARGET_FAIL             0x07
#define LR4_MRESP_MINIMUM_DETECTION_THRESHOLD  0x08
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define LR4_DEFAULT_SLAVE_ADDRESS 0x29
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

    digital_out_t xsh;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    uint16_t fast_osc_frequency;
    uint16_t osc_calibrate_val;

} lightranger4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t xsh;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} lightranger4_cfg_t;

/**
 * @brief User ROI structure definition.
 */
typedef struct
{
    uint8_t top_left_x;
    uint8_t top_left_y;
    uint8_t bottom_right_x;
    uint8_t bottom_right_y;

}lightranger4_user_roi_t;

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
void lightranger4_cfg_setup ( lightranger4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param lightranger4 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LIGHTRANGER4_RETVAL lightranger4_init ( lightranger4_t *ctx, lightranger4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 * @retval Function return device error status (_ID_IS_NOT_VALID or _FIRMWARE_TIMEOUT_ERROR) or device ok status (_INIT_IS_SUCCESSFUL)
 * @note This function should be called in the start program after the power on procedure, in order to check the chip communication and configure the chip for the operation.
 *
 * @description This function executes default configuration for LightRanger4 click.
 */
LIGHTRANGER4_RETVAL lightranger4_default_cfg ( lightranger4_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void lightranger4_generic_write ( lightranger4_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void lightranger4_generic_read ( lightranger4_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function for software reset
 *
 * @param ctx          Click object.
 */
void lightranger4_software_reset ( lightranger4_t *ctx );

/**
 * @brief Functions for start measurement
 *
 * @param ctx          Click object.
 * @param perion_ms  Inter measurement period in ms
 * @note This function should be called in the start program after the device configuration, in order to sets chip for start measurement.
 */
void lightranger4_start_measurement ( lightranger4_t *ctx, uint32_t period_ms );


/**
 * @brief Function that checks whether the new data is ready for reading
 *
 * @param ctx          Click object.
 * @retval Funstion return information about new data (0 - if new data is ready or 1 - if new data is not ready)
 * @note Call this function before measuring the distance.
 */
uint8_t lightranger4_new_data_ready ( lightranger4_t *ctx );

/**
 * @brief Function reads distance of the object in front of the sensor
 *
 * @param ctx          Click object.
 * @retval Distance in mm
 *
 * @note Distance depends on the set distance measurement mode,
 *        - In _DISTANCE_MODE_SHORT the maximum measurement distance is 1300mm,
 *        - in _DISTANCE_MODE_MEDIUM the maximum measurement distance is 3000mm, and
 *        - in _DISTANCE_MODE_LONG the maximum measurement distance is 4000mm.
 */
uint16_t lightranger4_get_distance ( lightranger4_t *ctx );

/**
 * @brief Function reads signal rate
 *
 * @param ctx          Click object.
 * @retval signal rate
 */
uint16_t lightranger4_get_signal_rate ( lightranger4_t *ctx );

/**
 * @brief Functions for sets distance measurement mode
 *
 * @param ctx          Click object.
 * @param mode  Distance measurement mode
 *
 * @note Distance mode:
 *        - _DISTANCE_MODE_SHORT the maximum measurement distance is 1300mm
 *        - _DISTANCE_MODE_MEDIUM the maximum measurement distance is 3000mm
 *        - _DISTANCE_MODE_LONG the maximum measurement distance is 4000mm
 */
uint8_t lightranger4_set_distance_mode ( lightranger4_t *ctx, uint8_t mode );

/**
 * @brief Function reads range status
 *
 * @param ctx          Click object.
 * @retval Range status
 */
uint8_t lightranger4_get_range_status ( lightranger4_t *ctx );

/**
 * @brief Functions for set center position
 *
 * @param ctx            Click object.
 * @param center_x       Center X position
 * @param center_y       Center Y position
 */
void lightranger4_set_center ( lightranger4_t *ctx, uint8_t center_x, uint8_t center_y);

/**
 * @brief Functions for sets zone size
 *
 * @param ctx            Click object.
 * @param width       Width zone size min(4) and max(16)
 * @param height      Height zone size min(4) and max(16)
 */
void lightranger4_set_zone_size ( lightranger4_t *ctx, uint8_t width, uint8_t height );

/**
 * @brief Functions for sets user Roi
 *
 * @param ctx            Click object.
 * @param (struct)roi   User Roi
 */
void lightranger4_set_user_roi ( lightranger4_t *ctx, lightranger4_user_roi_t *roi);

/**
 * @brief Functions for sets measurement timing budget
 *
 * @param ctx            Click object.
 * @param budget_us  Measurement timing budget in us
 *
 * @retval Function return error status (_INSUFFICIENT_BUDGET or _TOO_HIGH_BUDGET) or device ok status (_BUDGET_IS_SUCCESSFULLY_SET)
 */
LIGHTRANGER4_RETVAL lightranger4_set_measurement_timing_budget ( lightranger4_t *ctx, uint32_t budget_us);

/**
 * @brief Function reads interrupt pin state
 *
 * @param ctx            Click object.
 * @retval Interrupt pin state
 */
uint8_t lightranger4_get_intrrupt_state ( lightranger4_t *ctx );

/**
 * @brief Function for sets XSHUT pin
 *
 * @param ctx            Click object.
 * @param state  Pin state
 *
 * @note Xshutdown pin - active low
 */
void lightranger4_set_xshut_pin ( lightranger4_t *ctx, uint8_t state );

/**
 * @brief Function for starts power ON procedure
 *
 * @param ctx            Click object.
 */
void lightranger4_power_on ( lightranger4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _LIGHTRANGER4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
