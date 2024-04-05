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
 * @file lightranger8.h
 * @brief This file contains API for LightRanger 8 Click Driver.
 */

#ifndef LIGHTRANGER8_H
#define LIGHTRANGER8_H

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
 * @addtogroup lightranger8 LightRanger 8 Click Driver
 * @brief API for configuring and manipulating LightRanger 8 Click driver.
 * @{
 */

/**
 * @defgroup lightranger8_reg LightRanger 8 Registers List
 * @brief List of registers of LightRanger 8 Click driver.
 */

/**
 * @addtogroup lightranger8_reg
 * @{
 */

/**
 * @brief LightRanger 8 description register.
 * @details Specified register for description of LightRanger 8 Click driver.
 */

#define LIGHTRANGER8_SOFT_RESET                                                         0x0000
#define LIGHTRANGER8_I2C_SLAVE_DEVICE_ADDRESS                                           0x0001
#define LIGHTRANGER8_ANA_CONFIG_VHV_REF_SEL_VDDPIX                                      0x0002
#define LIGHTRANGER8_ANA_CONFIG_VHV_REF_SEL_VQUENCH                                     0x0003
#define LIGHTRANGER8_ANA_CONFIG_REG_AVDD1V2_SEL                                         0x0004
#define LIGHTRANGER8_ANA_CONFIG_FAST_OSC_TRIM                                           0x0005
#define LIGHTRANGER8_OSC_MEASURED_FAST_OSC_FREQUENCY                                    0x0006
#define LIGHTRANGER8_OSC_MEASURED_FAST_OSC_FREQUENCY_HI                                 0x0006
#define LIGHTRANGER8_OSC_MEASURED_FAST_OSC_FREQUENCY_LO                                 0x0007
#define LIGHTRANGER8_VHV_CONFIG_TIMEOUT_MACROP_LOOP_BOUND                               0x0008
#define LIGHTRANGER8_VHV_CONFIG_COUNT_THRESH                                            0x0009
#define LIGHTRANGER8_VHV_CONFIG_OFFSET                                                  0x000A
#define LIGHTRANGER8_VHV_CONFIG_INIT                                                    0x000B
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_REF_0                                   0x000D
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_REF_1                                   0x000E
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_REF_2                                   0x000F
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_REF_3                                   0x0010
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_REF_4                                   0x0011
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_REF_5                                   0x0012
#define LIGHTRANGER8_GLOBAL_CONFIG_REF_EN_START_SELECT                                  0x0013
#define LIGHTRANGER8_REF_SPAD_MAN_NUM_REQUESTED_REF_SPADS                               0x0014
#define LIGHTRANGER8_REF_SPAD_MAN_REF_LOCATION                                          0x0015
#define LIGHTRANGER8_ALGO_CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS                      0x0016
#define LIGHTRANGER8_ALGO_CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS_HI                   0x0016
#define LIGHTRANGER8_ALGO_CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS_LO                   0x0017
#define LIGHTRANGER8_ALGO_CROSSTALK_COMPENSATION_X_PLANE_GRADIENT_KCPS                  0x0018
#define LIGHTRANGER8_ALGO_CROSSTALK_COMPENSATION_X_PLANE_GRADIENT_KCPS_HI               0x0018
#define LIGHTRANGER8_ALGO_CROSSTALK_COMPENSATION_X_PLANE_GRADIENT_KCPS_LO               0x0019
#define LIGHTRANGER8_ALGO_CROSSTALK_COMPENSATION_Y_PLANE_GRADIENT_KCPS                  0x001A
#define LIGHTRANGER8_ALGO_CROSSTALK_COMPENSATION_Y_PLANE_GRADIENT_KCPS_HI               0x001A
#define LIGHTRANGER8_ALGO_CROSSTALK_COMPENSATION_Y_PLANE_GRADIENT_KCPS_LO               0x001B
#define LIGHTRANGER8_REF_SPAD_CHAR_TOTAL_RATE_TARGET_MCPS                               0x001C
#define LIGHTRANGER8_REF_SPAD_CHAR_TOTAL_RATE_TARGET_MCPS_HI                            0x001C
#define LIGHTRANGER8_REF_SPAD_CHAR_TOTAL_RATE_TARGET_MCPS_LO                            0x001D
#define LIGHTRANGER8_ALGO_PART_TO_PART_RANGE_OFFSET_MM                                  0x001E
#define LIGHTRANGER8_ALGO_PART_TO_PART_RANGE_OFFSET_MM_HI                               0x001E
#define LIGHTRANGER8_ALGO_PART_TO_PART_RANGE_OFFSET_MM_LO                               0x001F
#define LIGHTRANGER8_MM_CONFIG_INNER_OFFSET_MM                                          0x0020
#define LIGHTRANGER8_MM_CONFIG_INNER_OFFSET_MM_HI                                       0x0020
#define LIGHTRANGER8_MM_CONFIG_INNER_OFFSET_MM_LO                                       0x0021
#define LIGHTRANGER8_MM_CONFIG_OUTER_OFFSET_MM                                          0x0022
#define LIGHTRANGER8_MM_CONFIG_OUTER_OFFSET_MM_HI                                       0x0022
#define LIGHTRANGER8_MM_CONFIG_OUTER_OFFSET_MM_LO                                       0x0023
#define LIGHTRANGER8_DSS_CONFIG_TARGET_TOTAL_RATE_MCPS                                  0x0024
#define LIGHTRANGER8_DSS_CONFIG_TARGET_TOTAL_RATE_MCPS_HI                               0x0024
#define LIGHTRANGER8_DSS_CONFIG_TARGET_TOTAL_RATE_MCPS_LO                               0x0025
#define LIGHTRANGER8_DEBUG_CTRL                                                         0x0026
#define LIGHTRANGER8_TEST_MODE_CTRL                                                     0x0027
#define LIGHTRANGER8_CLK_GATING_CTRL                                                    0x0028
#define LIGHTRANGER8_NVM_BIST_CTRL                                                      0x0029
#define LIGHTRANGER8_NVM_BIST_NUM_NVM_WORDS                                             0x002A
#define LIGHTRANGER8_NVM_BIST_START_ADDRESS                                             0x002B
#define LIGHTRANGER8_HOST_IF_STATUS                                                     0x002C
#define LIGHTRANGER8_PAD_I2C_HV_CONFIG                                                  0x002D
#define LIGHTRANGER8_PAD_I2C_HV_EXTSUP_CONFIG                                           0x002E
#define LIGHTRANGER8_GPIO_HV_PAD_CTRL                                                   0x002F
#define LIGHTRANGER8_GPIO_HV_MUX_CTRL                                                   0x0030
#define LIGHTRANGER8_GPIO_TIO_HV_STATUS                                                 0x0031
#define LIGHTRANGER8_GPIO_FIO_HV_STATUS                                                 0x0032
#define LIGHTRANGER8_ANA_CONFIG_SPAD_SEL_PSWIDTH                                        0x0033
#define LIGHTRANGER8_ANA_CONFIG_VCSEL_PULSE_WIDTH_OFFSET                                0x0034
#define LIGHTRANGER8_ANA_CONFIG_FAST_OSC_CONFIG_CTRL                                    0x0035
#define LIGHTRANGER8_SIGMA_ESTIMATOR_EFFECTIVE_PULSE_WIDTH_NS                           0x0036
#define LIGHTRANGER8_SIGMA_ESTIMATOR_EFFECTIVE_AMBIENT_WIDTH_NS                         0x0037
#define LIGHTRANGER8_SIGMA_ESTIMATOR_SIGMA_REF_MM                                       0x0038
#define LIGHTRANGER8_ALGO_CROSSTALK_COMPENSATION_VALID_HEIGHT_MM                        0x0039
#define LIGHTRANGER8_SPARE_HOST_CONFIG_STATIC_CONFIG_SPARE_0                            0x003A
#define LIGHTRANGER8_SPARE_HOST_CONFIG_STATIC_CONFIG_SPARE_1                            0x003B
#define LIGHTRANGER8_ALGO_RANGE_IGNORE_THRESHOLD_MCPS                                   0x003C
#define LIGHTRANGER8_ALGO_RANGE_IGNORE_THRESHOLD_MCPS_HI                                0x003C
#define LIGHTRANGER8_ALGO_RANGE_IGNORE_THRESHOLD_MCPS_LO                                0x003D
#define LIGHTRANGER8_ALGO_RANGE_IGNORE_VALID_HEIGHT_MM                                  0x003E
#define LIGHTRANGER8_ALGO_RANGE_MIN_CLIP                                                0x003F
#define LIGHTRANGER8_ALGO_CONSISTENCY_CHECK_TOLERANCE                                   0x0040
#define LIGHTRANGER8_SPARE_HOST_CONFIG_STATIC_CONFIG_SPARE_2                            0x0041
#define LIGHTRANGER8_SD_CONFIG_RESET_STAGES_MSB                                         0x0042
#define LIGHTRANGER8_SD_CONFIG_RESET_STAGES_LSB                                         0x0043
#define LIGHTRANGER8_GPH_CONFIG_STREAM_COUNT_UPDATE_VALUE                               0x0044
#define LIGHTRANGER8_GLOBAL_CONFIG_STREAM_DIVIDER                                       0x0045
#define LIGHTRANGER8_SYSTEM_INTERRUPT_CONFIG_GPIO                                       0x0046
#define LIGHTRANGER8_CAL_CONFIG_VCSEL_START                                             0x0047
#define LIGHTRANGER8_CAL_CONFIG_REPEAT_RATE                                             0x0048
#define LIGHTRANGER8_CAL_CONFIG_REPEAT_RATE_HI                                          0x0048
#define LIGHTRANGER8_CAL_CONFIG_REPEAT_RATE_LO                                          0x0049
#define LIGHTRANGER8_GLOBAL_CONFIG_VCSEL_WIDTH                                          0x004A
#define LIGHTRANGER8_PHASECAL_CONFIG_TIMEOUT_MACROP                                     0x004B
#define LIGHTRANGER8_PHASECAL_CONFIG_TARGET                                             0x004C
#define LIGHTRANGER8_PHASECAL_CONFIG_OVERRIDE                                           0x004D
#define LIGHTRANGER8_DSS_CONFIG_ROI_MODE_CONTROL                                        0x004F
#define LIGHTRANGER8_SYSTEM_THRESH_RATE_HIGH                                            0x0050
#define LIGHTRANGER8_SYSTEM_THRESH_RATE_HIGH_HI                                         0x0050
#define LIGHTRANGER8_SYSTEM_THRESH_RATE_HIGH_LO                                         0x0051
#define LIGHTRANGER8_SYSTEM_THRESH_RATE_LOW                                             0x0052
#define LIGHTRANGER8_SYSTEM_THRESH_RATE_LOW_HI                                          0x0052
#define LIGHTRANGER8_SYSTEM_THRESH_RATE_LOW_LO                                          0x0053
#define LIGHTRANGER8_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT                           0x0054
#define LIGHTRANGER8_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT_HI                        0x0054
#define LIGHTRANGER8_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT_LO                        0x0055
#define LIGHTRANGER8_DSS_CONFIG_MANUAL_BLOCK_SELECT                                     0x0056
#define LIGHTRANGER8_DSS_CONFIG_APERTURE_ATTENUATION                                    0x0057
#define LIGHTRANGER8_DSS_CONFIG_MAX_SPADS_LIMIT                                         0x0058
#define LIGHTRANGER8_DSS_CONFIG_MIN_SPADS_LIMIT                                         0x0059
#define LIGHTRANGER8_MM_CONFIG_TIMEOUT_MACROP_A_HI                                      0x005A
#define LIGHTRANGER8_MM_CONFIG_TIMEOUT_MACROP_A_LO                                      0x005B
#define LIGHTRANGER8_MM_CONFIG_TIMEOUT_MACROP_B_HI                                      0x005C
#define LIGHTRANGER8_MM_CONFIG_TIMEOUT_MACROP_B_LO                                      0x005D
#define LIGHTRANGER8_RANGE_CONFIG_TIMEOUT_MACROP_A_HI                                   0x005E
#define LIGHTRANGER8_RANGE_CONFIG_TIMEOUT_MACROP_A_LO                                   0x005F
#define LIGHTRANGER8_RANGE_CONFIG_VCSEL_PERIOD_A                                        0x0060
#define LIGHTRANGER8_RANGE_CONFIG_TIMEOUT_MACROP_B_HI                                   0x0061
#define LIGHTRANGER8_RANGE_CONFIG_TIMEOUT_MACROP_B_LO                                   0x0062
#define LIGHTRANGER8_RANGE_CONFIG_VCSEL_PERIOD_B                                        0x0063
#define LIGHTRANGER8_RANGE_CONFIG_SIGMA_THRESH                                          0x0064
#define LIGHTRANGER8_RANGE_CONFIG_SIGMA_THRESH_HI                                       0x0064
#define LIGHTRANGER8_RANGE_CONFIG_SIGMA_THRESH_LO                                       0x0065
#define LIGHTRANGER8_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS                         0x0066
#define LIGHTRANGER8_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS_HI                      0x0066
#define LIGHTRANGER8_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS_LO                      0x0067
#define LIGHTRANGER8_RANGE_CONFIG_VALID_PHASE_LOW                                       0x0068
#define LIGHTRANGER8_RANGE_CONFIG_VALID_PHASE_HIGH                                      0x0069
#define LIGHTRANGER8_SYSTEM_INTERMEASUREMENT_PERIOD                                     0x006C
#define LIGHTRANGER8_SYSTEM_INTERMEASUREMENT_PERIOD_3                                   0x006C
#define LIGHTRANGER8_SYSTEM_INTERMEASUREMENT_PERIOD_2                                   0x006D
#define LIGHTRANGER8_SYSTEM_INTERMEASUREMENT_PERIOD_1                                   0x006E
#define LIGHTRANGER8_SYSTEM_INTERMEASUREMENT_PERIOD_0                                   0x006F
#define LIGHTRANGER8_SYSTEM_FRACTIONAL_ENABLE                                           0x0070
#define LIGHTRANGER8_SYSTEM_GROUPED_PARAMETER_HOLD_0                                    0x0071
#define LIGHTRANGER8_SYSTEM_THRESH_HIGH                                                 0x0072
#define LIGHTRANGER8_SYSTEM_THRESH_HIGH_HI                                              0x0072
#define LIGHTRANGER8_SYSTEM_THRESH_HIGH_LO                                              0x0073
#define LIGHTRANGER8_SYSTEM_THRESH_LOW                                                  0x0074
#define LIGHTRANGER8_SYSTEM_THRESH_LOW_HI                                               0x0074
#define LIGHTRANGER8_SYSTEM_THRESH_LOW_LO                                               0x0075
#define LIGHTRANGER8_SYSTEM_ENABLE_XTALK_PER_QUADRANT                                   0x0076
#define LIGHTRANGER8_SYSTEM_SEED_CONFIG                                                 0x0077
#define LIGHTRANGER8_SD_CONFIG_WOI_SD0                                                  0x0078
#define LIGHTRANGER8_SD_CONFIG_WOI_SD1                                                  0x0079
#define LIGHTRANGER8_SD_CONFIG_INITIAL_PHASE_SD0                                        0x007A
#define LIGHTRANGER8_SD_CONFIG_INITIAL_PHASE_SD1                                        0x007B
#define LIGHTRANGER8_SYSTEM_GROUPED_PARAMETER_HOLD_1                                    0x007C
#define LIGHTRANGER8_SD_CONFIG_FIRST_ORDER_SELECT                                       0x007D
#define LIGHTRANGER8_SD_CONFIG_QUANTIFIER                                               0x007E
#define LIGHTRANGER8_ROI_CONFIG_USER_ROI_CENTRE_SPAD                                    0x007F
#define LIGHTRANGER8_ROI_CONFIG_USER_ROI_REQUESTED_GLOBAL_XY_SIZE                       0x0080
#define LIGHTRANGER8_SYSTEM_SEQUENCE_CONFIG                                             0x0081
#define LIGHTRANGER8_SYSTEM_GROUPED_PARAMETER_HOLD                                      0x0082
#define LIGHTRANGER8_POWER_MANAGEMENT_GO1_POWER_FORCE                                   0x0083
#define LIGHTRANGER8_SYSTEM_STREAM_COUNT_CTRL                                           0x0084
#define LIGHTRANGER8_FIRMWARE_ENABLE                                                    0x0085
#define LIGHTRANGER8_SYSTEM_INTERRUPT_CLEAR                                             0x0086
#define LIGHTRANGER8_SYSTEM_MODE_START                                                  0x0087
#define LIGHTRANGER8_RESULT_INTERRUPT_STATUS                                            0x0088
#define LIGHTRANGER8_RESULT_RANGE_STATUS                                                0x0089
#define LIGHTRANGER8_RESULT_REPORT_STATUS                                               0x008A
#define LIGHTRANGER8_RESULT_STREAM_COUNT                                                0x008B
#define LIGHTRANGER8_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0                              0x008C
#define LIGHTRANGER8_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_HI                           0x008C
#define LIGHTRANGER8_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_LO                           0x008D
#define LIGHTRANGER8_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0                             0x008E
#define LIGHTRANGER8_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_HI                          0x008E
#define LIGHTRANGER8_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_LO                          0x008F
#define LIGHTRANGER8_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0                                 0x0090
#define LIGHTRANGER8_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_HI                              0x0090
#define LIGHTRANGER8_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_LO                              0x0091
#define LIGHTRANGER8_RESULT_SIGMA_SD0                                                   0x0092
#define LIGHTRANGER8_RESULT_SIGMA_SD0_HI                                                0x0092
#define LIGHTRANGER8_RESULT_SIGMA_SD0_LO                                                0x0093
#define LIGHTRANGER8_RESULT_PHASE_SD0                                                   0x0094
#define LIGHTRANGER8_RESULT_PHASE_SD0_HI                                                0x0094
#define LIGHTRANGER8_RESULT_PHASE_SD0_LO                                                0x0095
#define LIGHTRANGER8_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0                      0x0096
#define LIGHTRANGER8_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_HI                   0x0096
#define LIGHTRANGER8_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_LO                   0x0097
#define LIGHTRANGER8_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0                0x0098
#define LIGHTRANGER8_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_HI             0x0098
#define LIGHTRANGER8_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_LO             0x0099
#define LIGHTRANGER8_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0                         0x009A
#define LIGHTRANGER8_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_HI                      0x009A
#define LIGHTRANGER8_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_LO                      0x009B
#define LIGHTRANGER8_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0                         0x009C
#define LIGHTRANGER8_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_HI                      0x009C
#define LIGHTRANGER8_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_LO                      0x009D
#define LIGHTRANGER8_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0                              0x009E
#define LIGHTRANGER8_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_HI                           0x009E
#define LIGHTRANGER8_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_LO                           0x009F
#define LIGHTRANGER8_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1                              0x00A0
#define LIGHTRANGER8_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_HI                           0x00A0
#define LIGHTRANGER8_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_LO                           0x00A1
#define LIGHTRANGER8_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1                             0x00A2
#define LIGHTRANGER8_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_HI                          0x00A2
#define LIGHTRANGER8_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_LO                          0x00A3
#define LIGHTRANGER8_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1                                 0x00A4
#define LIGHTRANGER8_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_HI                              0x00A4
#define LIGHTRANGER8_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_LO                              0x00A5
#define LIGHTRANGER8_RESULT_SIGMA_SD1                                                   0x00A6
#define LIGHTRANGER8_RESULT_SIGMA_SD1_HI                                                0x00A6
#define LIGHTRANGER8_RESULT_SIGMA_SD1_LO                                                0x00A7
#define LIGHTRANGER8_RESULT_PHASE_SD1                                                   0x00A8
#define LIGHTRANGER8_RESULT_PHASE_SD1_HI                                                0x00A8
#define LIGHTRANGER8_RESULT_PHASE_SD1_LO                                                0x00A9
#define LIGHTRANGER8_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1                      0x00AA
#define LIGHTRANGER8_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_HI                   0x00AA
#define LIGHTRANGER8_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_LO                   0x00AB
#define LIGHTRANGER8_RESULT_SPARE_0_SD1                                                 0x00AC
#define LIGHTRANGER8_RESULT_SPARE_0_SD1_HI                                              0x00AC
#define LIGHTRANGER8_RESULT_SPARE_0_SD1_LO                                              0x00AD
#define LIGHTRANGER8_RESULT_SPARE_1_SD1                                                 0x00AE
#define LIGHTRANGER8_RESULT_SPARE_1_SD1_HI                                              0x00AE
#define LIGHTRANGER8_RESULT_SPARE_1_SD1_LO                                              0x00AF
#define LIGHTRANGER8_RESULT_SPARE_2_SD1                                                 0x00B0
#define LIGHTRANGER8_RESULT_SPARE_2_SD1_HI                                              0x00B0
#define LIGHTRANGER8_RESULT_SPARE_2_SD1_LO                                              0x00B1
#define LIGHTRANGER8_RESULT_SPARE_3_SD1                                                 0x00B2
#define LIGHTRANGER8_RESULT_THRESH_INFO                                                 0x00B3
#define LIGHTRANGER8_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0                              0x00B4
#define LIGHTRANGER8_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_3                            0x00B4
#define LIGHTRANGER8_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_2                            0x00B5
#define LIGHTRANGER8_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_1                            0x00B6
#define LIGHTRANGER8_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_0                            0x00B7
#define LIGHTRANGER8_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0                               0x00B8
#define LIGHTRANGER8_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_3                             0x00B8
#define LIGHTRANGER8_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_2                             0x00B9
#define LIGHTRANGER8_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_1                             0x00BA
#define LIGHTRANGER8_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_0                             0x00BB
#define LIGHTRANGER8_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0                                0x00BC
#define LIGHTRANGER8_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_3                              0x00BC
#define LIGHTRANGER8_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_2                              0x00BD
#define LIGHTRANGER8_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_1                              0x00BE
#define LIGHTRANGER8_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_0                              0x00BF
#define LIGHTRANGER8_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0                              0x00C0
#define LIGHTRANGER8_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_3                            0x00C0
#define LIGHTRANGER8_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_2                            0x00C1
#define LIGHTRANGER8_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_1                            0x00C2
#define LIGHTRANGER8_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_0                            0x00C3
#define LIGHTRANGER8_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1                              0x00C4
#define LIGHTRANGER8_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_3                            0x00C4
#define LIGHTRANGER8_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_2                            0x00C5
#define LIGHTRANGER8_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_1                            0x00C6
#define LIGHTRANGER8_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_0                            0x00C7
#define LIGHTRANGER8_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1                               0x00C8
#define LIGHTRANGER8_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_3                             0x00C8
#define LIGHTRANGER8_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_2                             0x00C9
#define LIGHTRANGER8_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_1                             0x00CA
#define LIGHTRANGER8_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_0                             0x00CB
#define LIGHTRANGER8_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1                                0x00CC
#define LIGHTRANGER8_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_3                              0x00CC
#define LIGHTRANGER8_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_2                              0x00CD
#define LIGHTRANGER8_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_1                              0x00CE
#define LIGHTRANGER8_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_0                              0x00CF
#define LIGHTRANGER8_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1                              0x00D0
#define LIGHTRANGER8_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_3                            0x00D0
#define LIGHTRANGER8_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_2                            0x00D1
#define LIGHTRANGER8_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_1                            0x00D2
#define LIGHTRANGER8_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_0                            0x00D3
#define LIGHTRANGER8_RESULT_CORE_SPARE_0                                                0x00D4
#define LIGHTRANGER8_PHASECAL_RESULT_REFERENCE_PHASE                                    0x00D6
#define LIGHTRANGER8_PHASECAL_RESULT_REFERENCE_PHASE_HI                                 0x00D6
#define LIGHTRANGER8_PHASECAL_RESULT_REFERENCE_PHASE_LO                                 0x00D7
#define LIGHTRANGER8_PHASECAL_RESULT_VCSEL_START                                        0x00D8
#define LIGHTRANGER8_REF_SPAD_CHAR_RESULT_NUM_ACTUAL_REF_SPADS                          0x00D9
#define LIGHTRANGER8_REF_SPAD_CHAR_RESULT_REF_LOCATION                                  0x00DA
#define LIGHTRANGER8_VHV_RESULT_COLDBOOT_STATUS                                         0x00DB
#define LIGHTRANGER8_VHV_RESULT_SEARCH_RESULT                                           0x00DC
#define LIGHTRANGER8_VHV_RESULT_LATEST_SETTING                                          0x00DD
#define LIGHTRANGER8_RESULT_OSC_CALIBRATE_VAL                                           0x00DE
#define LIGHTRANGER8_RESULT_OSC_CALIBRATE_VAL_HI                                        0x00DE
#define LIGHTRANGER8_RESULT_OSC_CALIBRATE_VAL_LO                                        0x00DF
#define LIGHTRANGER8_ANA_CONFIG_POWERDOWN_GO1                                           0x00E0
#define LIGHTRANGER8_ANA_CONFIG_REF_BG_CTRL                                             0x00E1
#define LIGHTRANGER8_ANA_CONFIG_REGDVDD1V2_CTRL                                         0x00E2
#define LIGHTRANGER8_ANA_CONFIG_OSC_SLOW_CTRL                                           0x00E3
#define LIGHTRANGER8_TEST_MODE_STATUS                                                   0x00E4
#define LIGHTRANGER8_FIRMWARE_SYSTEM_STATUS                                             0x00E5
#define LIGHTRANGER8_FIRMWARE_MODE_STATUS                                               0x00E6
#define LIGHTRANGER8_FIRMWARE_SECONDARY_MODE_STATUS                                     0x00E7
#define LIGHTRANGER8_FIRMWARE_CAL_REPEAT_RATE_COUNTER                                   0x00E8
#define LIGHTRANGER8_FIRMWARE_CAL_REPEAT_RATE_COUNTER_HI                                0x00E8
#define LIGHTRANGER8_FIRMWARE_CAL_REPEAT_RATE_COUNTER_LO                                0x00E9
#define LIGHTRANGER8_FIRMWARE_HISTOGRAM_BIN                                             0x00EA
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_HIGH                                             0x00EC
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_HIGH_HI                                          0x00EC
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_HIGH_LO                                          0x00ED
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_LOW                                              0x00EE
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_LOW_HI                                           0x00EE
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_LOW_LO                                           0x00EF
#define LIGHTRANGER8_GPH_SYSTEM_ENABLE_XTALK_PER_QUADRANT                               0x00F0
#define LIGHTRANGER8_GPH_SPARE_0                                                        0x00F1
#define LIGHTRANGER8_GPH_SD_CONFIG_WOI_SD0                                              0x00F2
#define LIGHTRANGER8_GPH_SD_CONFIG_WOI_SD1                                              0x00F3
#define LIGHTRANGER8_GPH_SD_CONFIG_INITIAL_PHASE_SD0                                    0x00F4
#define LIGHTRANGER8_GPH_SD_CONFIG_INITIAL_PHASE_SD1                                    0x00F5
#define LIGHTRANGER8_GPH_SD_CONFIG_FIRST_ORDER_SELECT                                   0x00F6
#define LIGHTRANGER8_GPH_SD_CONFIG_QUANTIFIER                                           0x00F7
#define LIGHTRANGER8_GPH_ROI_CONFIG_USER_ROI_CENTRE_SPAD                                0x00F8
#define LIGHTRANGER8_GPH_ROI_CONFIG_USER_ROI_REQUESTED_GLOBAL_XY_SIZE                   0x00F9
#define LIGHTRANGER8_GPH_SYSTEM_SEQUENCE_CONFIG                                         0x00FA
#define LIGHTRANGER8_GPH_GPH_ID                                                         0x00FB
#define LIGHTRANGER8_SYSTEM_INTERRUPT_SET                                               0x00FC
#define LIGHTRANGER8_INTERRUPT_MANAGER_ENABLES                                          0x00FD
#define LIGHTRANGER8_INTERRUPT_MANAGER_CLEAR                                            0x00FE
#define LIGHTRANGER8_INTERRUPT_MANAGER_STATUS                                           0x00FF
#define LIGHTRANGER8_MCU_TO_HOST_BANK_WR_ACCESS_EN                                      0x0100
#define LIGHTRANGER8_POWER_MANAGEMENT_GO1_RESET_STATUS                                  0x0101
#define LIGHTRANGER8_PAD_STARTUP_MODE_VALUE_RO                                          0x0102
#define LIGHTRANGER8_PAD_STARTUP_MODE_VALUE_CTRL                                        0x0103
#define LIGHTRANGER8_PLL_PERIOD_US                                                      0x0104
#define LIGHTRANGER8_PLL_PERIOD_US_3                                                    0x0104
#define LIGHTRANGER8_PLL_PERIOD_US_2                                                    0x0105
#define LIGHTRANGER8_PLL_PERIOD_US_1                                                    0x0106
#define LIGHTRANGER8_PLL_PERIOD_US_0                                                    0x0107
#define LIGHTRANGER8_INTERRUPT_SCHEDULER_DATA_OUT                                       0x0108
#define LIGHTRANGER8_INTERRUPT_SCHEDULER_DATA_OUT_3                                     0x0108
#define LIGHTRANGER8_INTERRUPT_SCHEDULER_DATA_OUT_2                                     0x0109
#define LIGHTRANGER8_INTERRUPT_SCHEDULER_DATA_OUT_1                                     0x010A
#define LIGHTRANGER8_INTERRUPT_SCHEDULER_DATA_OUT_0                                     0x010B
#define LIGHTRANGER8_NVM_BIST_COMPLETE                                                  0x010C
#define LIGHTRANGER8_NVM_BIST_STATUS                                                    0x010D
#define LIGHTRANGER8_IDENTIFICATION_MODEL_ID                                            0x010F
#define LIGHTRANGER8_IDENTIFICATION_MODULE_TYPE                                         0x0110
#define LIGHTRANGER8_IDENTIFICATION_REVISION_ID                                         0x0111
#define LIGHTRANGER8_IDENTIFICATION_MODULE_ID                                           0x0112
#define LIGHTRANGER8_IDENTIFICATION_MODULE_ID_HI                                        0x0112
#define LIGHTRANGER8_IDENTIFICATION_MODULE_ID_LO                                        0x0113
#define LIGHTRANGER8_ANA_CONFIG_FAST_OSC_TRIM_MAX                                       0x0114
#define LIGHTRANGER8_ANA_CONFIG_FAST_OSC_FREQ_SET                                       0x0115
#define LIGHTRANGER8_ANA_CONFIG_VCSEL_TRIM                                              0x0116
#define LIGHTRANGER8_ANA_CONFIG_VCSEL_SELION                                            0x0117
#define LIGHTRANGER8_ANA_CONFIG_VCSEL_SELION_MAX                                        0x0118
#define LIGHTRANGER8_PROTECTED_LASER_SAFETY_LOCK_BIT                                    0x0119
#define LIGHTRANGER8_LASER_SAFETY_KEY                                                   0x011A
#define LIGHTRANGER8_LASER_SAFETY_KEY_RO                                                0x011B
#define LIGHTRANGER8_LASER_SAFETY_CLIP                                                  0x011C
#define LIGHTRANGER8_LASER_SAFETY_MULT                                                  0x011D
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_0                                   0x011E
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_1                                   0x011F
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_2                                   0x0120
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_3                                   0x0121
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_4                                   0x0122
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_5                                   0x0123
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_6                                   0x0124
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_7                                   0x0125
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_8                                   0x0126
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_9                                   0x0127
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_10                                  0x0128
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_11                                  0x0129
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_12                                  0x012A
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_13                                  0x012B
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_14                                  0x012C
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_15                                  0x012D
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_16                                  0x012E
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_17                                  0x012F
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_18                                  0x0130
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_19                                  0x0131
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_20                                  0x0132
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_21                                  0x0133
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_22                                  0x0134
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_23                                  0x0135
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_24                                  0x0136
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_25                                  0x0137
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_26                                  0x0138
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_27                                  0x0139
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_28                                  0x013A
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_29                                  0x013B
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_30                                  0x013C
#define LIGHTRANGER8_GLOBAL_CONFIG_SPAD_ENABLES_RTN_31                                  0x013D
#define LIGHTRANGER8_ROI_CONFIG_MODE_ROI_CENTRE_SPAD                                    0x013E
#define LIGHTRANGER8_ROI_CONFIG_MODE_ROI_XY_SIZE                                        0x013F
#define LIGHTRANGER8_GO2_HOST_BANK_ACCESS_OVERRIDE                                      0x0300
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_MULTIPLICAND                                   0x0400
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_MULTIPLICAND_3                                 0x0400
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_MULTIPLICAND_2                                 0x0401
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_MULTIPLICAND_1                                 0x0402
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_MULTIPLICAND_0                                 0x0403
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_MULTIPLIER                                     0x0404
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_MULTIPLIER_3                                   0x0404
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_MULTIPLIER_2                                   0x0405
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_MULTIPLIER_1                                   0x0406
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_MULTIPLIER_0                                   0x0407
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_PRODUCT_HI                                     0x0408
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_PRODUCT_HI_3                                   0x0408
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_PRODUCT_HI_2                                   0x0409
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_PRODUCT_HI_1                                   0x040A
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_PRODUCT_HI_0                                   0x040B
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_PRODUCT_LO                                     0x040C
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_PRODUCT_LO_3                                   0x040C
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_PRODUCT_LO_2                                   0x040D
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_PRODUCT_LO_1                                   0x040E
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_PRODUCT_LO_0                                   0x040F
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_START                                          0x0410
#define LIGHTRANGER8_MCU_UTIL_MULTIPLIER_STATUS                                         0x0411
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_START                                             0x0412
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_STATUS                                            0x0413
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_DIVIDEND                                          0x0414
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_DIVIDEND_3                                        0x0414
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_DIVIDEND_2                                        0x0415
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_DIVIDEND_1                                        0x0416
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_DIVIDEND_0                                        0x0417
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_DIVISOR                                           0x0418
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_DIVISOR_3                                         0x0418
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_DIVISOR_2                                         0x0419
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_DIVISOR_1                                         0x041A
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_DIVISOR_0                                         0x041B
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_QUOTIENT                                          0x041C
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_QUOTIENT_3                                        0x041C
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_QUOTIENT_2                                        0x041D
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_QUOTIENT_1                                        0x041E
#define LIGHTRANGER8_MCU_UTIL_DIVIDER_QUOTIENT_0                                        0x041F
#define LIGHTRANGER8_TIMER0_VALUE_IN                                                    0x0420
#define LIGHTRANGER8_TIMER0_VALUE_IN_3                                                  0x0420
#define LIGHTRANGER8_TIMER0_VALUE_IN_2                                                  0x0421
#define LIGHTRANGER8_TIMER0_VALUE_IN_1                                                  0x0422
#define LIGHTRANGER8_TIMER0_VALUE_IN_0                                                  0x0423
#define LIGHTRANGER8_TIMER1_VALUE_IN                                                    0x0424
#define LIGHTRANGER8_TIMER1_VALUE_IN_3                                                  0x0424
#define LIGHTRANGER8_TIMER1_VALUE_IN_2                                                  0x0425
#define LIGHTRANGER8_TIMER1_VALUE_IN_1                                                  0x0426
#define LIGHTRANGER8_TIMER1_VALUE_IN_0                                                  0x0427
#define LIGHTRANGER8_TIMER0_CTRL                                                        0x0428
#define LIGHTRANGER8_TIMER1_CTRL                                                        0x0429
#define LIGHTRANGER8_MCU_GENERAL_PURPOSE_GP_0                                           0x042C
#define LIGHTRANGER8_MCU_GENERAL_PURPOSE_GP_1                                           0x042D
#define LIGHTRANGER8_MCU_GENERAL_PURPOSE_GP_2                                           0x042E
#define LIGHTRANGER8_MCU_GENERAL_PURPOSE_GP_3                                           0x042F
#define LIGHTRANGER8_MCU_RANGE_CALC_CONFIG                                              0x0430
#define LIGHTRANGER8_MCU_RANGE_CALC_OFFSET_CORRECTED_RANGE                              0x0432
#define LIGHTRANGER8_MCU_RANGE_CALC_OFFSET_CORRECTED_RANGE_HI                           0x0432
#define LIGHTRANGER8_MCU_RANGE_CALC_OFFSET_CORRECTED_RANGE_LO                           0x0433
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_4                                             0x0434
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_4_3                                           0x0434
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_4_2                                           0x0435
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_4_1                                           0x0436
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_4_0                                           0x0437
#define LIGHTRANGER8_MCU_RANGE_CALC_AMBIENT_DURATION_PRE_CALC                           0x0438
#define LIGHTRANGER8_MCU_RANGE_CALC_AMBIENT_DURATION_PRE_CALC_HI                        0x0438
#define LIGHTRANGER8_MCU_RANGE_CALC_AMBIENT_DURATION_PRE_CALC_LO                        0x0439
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_VCSEL_PERIOD                                   0x043C
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_5                                             0x043D
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_TOTAL_PERIODS                                  0x043E
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_TOTAL_PERIODS_HI                               0x043E
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_TOTAL_PERIODS_LO                               0x043F
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_ACCUM_PHASE                                    0x0440
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_ACCUM_PHASE_3                                  0x0440
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_ACCUM_PHASE_2                                  0x0441
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_ACCUM_PHASE_1                                  0x0442
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_ACCUM_PHASE_0                                  0x0443
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_SIGNAL_EVENTS                                  0x0444
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_SIGNAL_EVENTS_3                                0x0444
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_SIGNAL_EVENTS_2                                0x0445
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_SIGNAL_EVENTS_1                                0x0446
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_SIGNAL_EVENTS_0                                0x0447
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_AMBIENT_EVENTS                                 0x0448
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_AMBIENT_EVENTS_3                               0x0448
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_AMBIENT_EVENTS_2                               0x0449
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_AMBIENT_EVENTS_1                               0x044A
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_AMBIENT_EVENTS_0                               0x044B
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_6                                             0x044C
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_6_HI                                          0x044C
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_6_LO                                          0x044D
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_ADJUST_VCSEL_PERIOD                            0x044E
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_ADJUST_VCSEL_PERIOD_HI                         0x044E
#define LIGHTRANGER8_MCU_RANGE_CALC_ALGO_ADJUST_VCSEL_PERIOD_LO                         0x044F
#define LIGHTRANGER8_MCU_RANGE_CALC_NUM_SPADS                                           0x0450
#define LIGHTRANGER8_MCU_RANGE_CALC_NUM_SPADS_HI                                        0x0450
#define LIGHTRANGER8_MCU_RANGE_CALC_NUM_SPADS_LO                                        0x0451
#define LIGHTRANGER8_MCU_RANGE_CALC_PHASE_OUTPUT                                        0x0452
#define LIGHTRANGER8_MCU_RANGE_CALC_PHASE_OUTPUT_HI                                     0x0452
#define LIGHTRANGER8_MCU_RANGE_CALC_PHASE_OUTPUT_LO                                     0x0453
#define LIGHTRANGER8_MCU_RANGE_CALC_RATE_PER_SPAD_MCPS                                  0x0454
#define LIGHTRANGER8_MCU_RANGE_CALC_RATE_PER_SPAD_MCPS_3                                0x0454
#define LIGHTRANGER8_MCU_RANGE_CALC_RATE_PER_SPAD_MCPS_2                                0x0455
#define LIGHTRANGER8_MCU_RANGE_CALC_RATE_PER_SPAD_MCPS_1                                0x0456
#define LIGHTRANGER8_MCU_RANGE_CALC_RATE_PER_SPAD_MCPS_0                                0x0457
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_7                                             0x0458
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_8                                             0x0459
#define LIGHTRANGER8_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_MCPS                               0x045A
#define LIGHTRANGER8_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_MCPS_HI                            0x045A
#define LIGHTRANGER8_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_MCPS_LO                            0x045B
#define LIGHTRANGER8_MCU_RANGE_CALC_AVG_SIGNAL_RATE_MCPS                                0x045C
#define LIGHTRANGER8_MCU_RANGE_CALC_AVG_SIGNAL_RATE_MCPS_HI                             0x045C
#define LIGHTRANGER8_MCU_RANGE_CALC_AVG_SIGNAL_RATE_MCPS_LO                             0x045D
#define LIGHTRANGER8_MCU_RANGE_CALC_AMBIENT_RATE_MCPS                                   0x045E
#define LIGHTRANGER8_MCU_RANGE_CALC_AMBIENT_RATE_MCPS_HI                                0x045E
#define LIGHTRANGER8_MCU_RANGE_CALC_AMBIENT_RATE_MCPS_LO                                0x045F
#define LIGHTRANGER8_MCU_RANGE_CALC_XTALK                                               0x0460
#define LIGHTRANGER8_MCU_RANGE_CALC_XTALK_HI                                            0x0460
#define LIGHTRANGER8_MCU_RANGE_CALC_XTALK_LO                                            0x0461
#define LIGHTRANGER8_MCU_RANGE_CALC_CALC_STATUS                                         0x0462
#define LIGHTRANGER8_MCU_RANGE_CALC_DEBUG                                               0x0463
#define LIGHTRANGER8_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_XTALK_CORR_MCPS                    0x0464
#define LIGHTRANGER8_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_XTALK_CORR_MCPS_HI                 0x0464
#define LIGHTRANGER8_MCU_RANGE_CALC_PEAK_SIGNAL_RATE_XTALK_CORR_MCPS_LO                 0x0465
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_0                                             0x0468
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_1                                             0x0469
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_2                                             0x046A
#define LIGHTRANGER8_MCU_RANGE_CALC_SPARE_3                                             0x046B
#define LIGHTRANGER8_PATCH_CTRL                                                         0x0470
#define LIGHTRANGER8_PATCH_JMP_ENABLES                                                  0x0472
#define LIGHTRANGER8_PATCH_JMP_ENABLES_HI                                               0x0472
#define LIGHTRANGER8_PATCH_JMP_ENABLES_LO                                               0x0473
#define LIGHTRANGER8_PATCH_DATA_ENABLES                                                 0x0474
#define LIGHTRANGER8_PATCH_DATA_ENABLES_HI                                              0x0474
#define LIGHTRANGER8_PATCH_DATA_ENABLES_LO                                              0x0475
#define LIGHTRANGER8_PATCH_OFFSET_0                                                     0x0476
#define LIGHTRANGER8_PATCH_OFFSET_0_HI                                                  0x0476
#define LIGHTRANGER8_PATCH_OFFSET_0_LO                                                  0x0477
#define LIGHTRANGER8_PATCH_OFFSET_1                                                     0x0478
#define LIGHTRANGER8_PATCH_OFFSET_1_HI                                                  0x0478
#define LIGHTRANGER8_PATCH_OFFSET_1_LO                                                  0x0479
#define LIGHTRANGER8_PATCH_OFFSET_2                                                     0x047A
#define LIGHTRANGER8_PATCH_OFFSET_2_HI                                                  0x047A
#define LIGHTRANGER8_PATCH_OFFSET_2_LO                                                  0x047B
#define LIGHTRANGER8_PATCH_OFFSET_3                                                     0x047C
#define LIGHTRANGER8_PATCH_OFFSET_3_HI                                                  0x047C
#define LIGHTRANGER8_PATCH_OFFSET_3_LO                                                  0x047D
#define LIGHTRANGER8_PATCH_OFFSET_4                                                     0x047E
#define LIGHTRANGER8_PATCH_OFFSET_4_HI                                                  0x047E
#define LIGHTRANGER8_PATCH_OFFSET_4_LO                                                  0x047F
#define LIGHTRANGER8_PATCH_OFFSET_5                                                     0x0480
#define LIGHTRANGER8_PATCH_OFFSET_5_HI                                                  0x0480
#define LIGHTRANGER8_PATCH_OFFSET_5_LO                                                  0x0481
#define LIGHTRANGER8_PATCH_OFFSET_6                                                     0x0482
#define LIGHTRANGER8_PATCH_OFFSET_6_HI                                                  0x0482
#define LIGHTRANGER8_PATCH_OFFSET_6_LO                                                  0x0483
#define LIGHTRANGER8_PATCH_OFFSET_7                                                     0x0484
#define LIGHTRANGER8_PATCH_OFFSET_7_HI                                                  0x0484
#define LIGHTRANGER8_PATCH_OFFSET_7_LO                                                  0x0485
#define LIGHTRANGER8_PATCH_OFFSET_8                                                     0x0486
#define LIGHTRANGER8_PATCH_OFFSET_8_HI                                                  0x0486
#define LIGHTRANGER8_PATCH_OFFSET_8_LO                                                  0x0487
#define LIGHTRANGER8_PATCH_OFFSET_9                                                     0x0488
#define LIGHTRANGER8_PATCH_OFFSET_9_HI                                                  0x0488
#define LIGHTRANGER8_PATCH_OFFSET_9_LO                                                  0x0489
#define LIGHTRANGER8_PATCH_OFFSET_10                                                    0x048A
#define LIGHTRANGER8_PATCH_OFFSET_10_HI                                                 0x048A
#define LIGHTRANGER8_PATCH_OFFSET_10_LO                                                 0x048B
#define LIGHTRANGER8_PATCH_OFFSET_11                                                    0x048C
#define LIGHTRANGER8_PATCH_OFFSET_11_HI                                                 0x048C
#define LIGHTRANGER8_PATCH_OFFSET_11_LO                                                 0x048D
#define LIGHTRANGER8_PATCH_OFFSET_12                                                    0x048E
#define LIGHTRANGER8_PATCH_OFFSET_12_HI                                                 0x048E
#define LIGHTRANGER8_PATCH_OFFSET_12_LO                                                 0x048F
#define LIGHTRANGER8_PATCH_OFFSET_13                                                    0x0490
#define LIGHTRANGER8_PATCH_OFFSET_13_HI                                                 0x0490
#define LIGHTRANGER8_PATCH_OFFSET_13_LO                                                 0x0491
#define LIGHTRANGER8_PATCH_OFFSET_14                                                    0x0492
#define LIGHTRANGER8_PATCH_OFFSET_14_HI                                                 0x0492
#define LIGHTRANGER8_PATCH_OFFSET_14_LO                                                 0x0493
#define LIGHTRANGER8_PATCH_OFFSET_15                                                    0x0494
#define LIGHTRANGER8_PATCH_OFFSET_15_HI                                                 0x0494
#define LIGHTRANGER8_PATCH_OFFSET_15_LO                                                 0x0495
#define LIGHTRANGER8_PATCH_ADDRESS_0                                                    0x0496
#define LIGHTRANGER8_PATCH_ADDRESS_0_HI                                                 0x0496
#define LIGHTRANGER8_PATCH_ADDRESS_0_LO                                                 0x0497
#define LIGHTRANGER8_PATCH_ADDRESS_1                                                    0x0498
#define LIGHTRANGER8_PATCH_ADDRESS_1_HI                                                 0x0498
#define LIGHTRANGER8_PATCH_ADDRESS_1_LO                                                 0x0499
#define LIGHTRANGER8_PATCH_ADDRESS_2                                                    0x049A
#define LIGHTRANGER8_PATCH_ADDRESS_2_HI                                                 0x049A
#define LIGHTRANGER8_PATCH_ADDRESS_2_LO                                                 0x049B
#define LIGHTRANGER8_PATCH_ADDRESS_3                                                    0x049C
#define LIGHTRANGER8_PATCH_ADDRESS_3_HI                                                 0x049C
#define LIGHTRANGER8_PATCH_ADDRESS_3_LO                                                 0x049D
#define LIGHTRANGER8_PATCH_ADDRESS_4                                                    0x049E
#define LIGHTRANGER8_PATCH_ADDRESS_4_HI                                                 0x049E
#define LIGHTRANGER8_PATCH_ADDRESS_4_LO                                                 0x049F
#define LIGHTRANGER8_PATCH_ADDRESS_5                                                    0x04A0
#define LIGHTRANGER8_PATCH_ADDRESS_5_HI                                                 0x04A0
#define LIGHTRANGER8_PATCH_ADDRESS_5_LO                                                 0x04A1
#define LIGHTRANGER8_PATCH_ADDRESS_6                                                    0x04A2
#define LIGHTRANGER8_PATCH_ADDRESS_6_HI                                                 0x04A2
#define LIGHTRANGER8_PATCH_ADDRESS_6_LO                                                 0x04A3
#define LIGHTRANGER8_PATCH_ADDRESS_7                                                    0x04A4
#define LIGHTRANGER8_PATCH_ADDRESS_7_HI                                                 0x04A4
#define LIGHTRANGER8_PATCH_ADDRESS_7_LO                                                 0x04A5
#define LIGHTRANGER8_PATCH_ADDRESS_8                                                    0x04A6
#define LIGHTRANGER8_PATCH_ADDRESS_8_HI                                                 0x04A6
#define LIGHTRANGER8_PATCH_ADDRESS_8_LO                                                 0x04A7
#define LIGHTRANGER8_PATCH_ADDRESS_9                                                    0x04A8
#define LIGHTRANGER8_PATCH_ADDRESS_9_HI                                                 0x04A8
#define LIGHTRANGER8_PATCH_ADDRESS_9_LO                                                 0x04A9
#define LIGHTRANGER8_PATCH_ADDRESS_10                                                   0x04AA
#define LIGHTRANGER8_PATCH_ADDRESS_10_HI                                                0x04AA
#define LIGHTRANGER8_PATCH_ADDRESS_10_LO                                                0x04AB
#define LIGHTRANGER8_PATCH_ADDRESS_11                                                   0x04AC
#define LIGHTRANGER8_PATCH_ADDRESS_11_HI                                                0x04AC
#define LIGHTRANGER8_PATCH_ADDRESS_11_LO                                                0x04AD
#define LIGHTRANGER8_PATCH_ADDRESS_12                                                   0x04AE
#define LIGHTRANGER8_PATCH_ADDRESS_12_HI                                                0x04AE
#define LIGHTRANGER8_PATCH_ADDRESS_12_LO                                                0x04AF
#define LIGHTRANGER8_PATCH_ADDRESS_13                                                   0x04B0
#define LIGHTRANGER8_PATCH_ADDRESS_13_HI                                                0x04B0
#define LIGHTRANGER8_PATCH_ADDRESS_13_LO                                                0x04B1
#define LIGHTRANGER8_PATCH_ADDRESS_14                                                   0x04B2
#define LIGHTRANGER8_PATCH_ADDRESS_14_HI                                                0x04B2
#define LIGHTRANGER8_PATCH_ADDRESS_14_LO                                                0x04B3
#define LIGHTRANGER8_PATCH_ADDRESS_15                                                   0x04B4
#define LIGHTRANGER8_PATCH_ADDRESS_15_HI                                                0x04B4
#define LIGHTRANGER8_PATCH_ADDRESS_15_LO                                                0x04B5
#define LIGHTRANGER8_SPI_ASYNC_MUX_CTRL                                                 0x04C0
#define LIGHTRANGER8_CLK_CONFIG                                                         0x04C4
#define LIGHTRANGER8_GPIO_LV_MUX_CTRL                                                   0x04CC
#define LIGHTRANGER8_GPIO_LV_PAD_CTRL                                                   0x04CD
#define LIGHTRANGER8_PAD_I2C_LV_CONFIG                                                  0x04D0
#define LIGHTRANGER8_PAD_STARTUP_MODE_VALUE_RO_GO1                                      0x04D4
#define LIGHTRANGER8_HOST_IF_STATUS_GO1                                                 0x04D5
#define LIGHTRANGER8_MCU_CLK_GATING_CTRL                                                0x04D8
#define LIGHTRANGER8_TEST_BIST_ROM_CTRL                                                 0x04E0
#define LIGHTRANGER8_TEST_BIST_ROM_RESULT                                               0x04E1
#define LIGHTRANGER8_TEST_BIST_ROM_MCU_SIG                                              0x04E2
#define LIGHTRANGER8_TEST_BIST_ROM_MCU_SIG_HI                                           0x04E2
#define LIGHTRANGER8_TEST_BIST_ROM_MCU_SIG_LO                                           0x04E3
#define LIGHTRANGER8_TEST_BIST_RAM_CTRL                                                 0x04E4
#define LIGHTRANGER8_TEST_BIST_RAM_RESULT                                               0x04E5
#define LIGHTRANGER8_TEST_TMC                                                           0x04E8
#define LIGHTRANGER8_TEST_PLL_BIST_MIN_THRESHOLD                                        0x04F0
#define LIGHTRANGER8_TEST_PLL_BIST_MIN_THRESHOLD_HI                                     0x04F0
#define LIGHTRANGER8_TEST_PLL_BIST_MIN_THRESHOLD_LO                                     0x04F1
#define LIGHTRANGER8_TEST_PLL_BIST_MAX_THRESHOLD                                        0x04F2
#define LIGHTRANGER8_TEST_PLL_BIST_MAX_THRESHOLD_HI                                     0x04F2
#define LIGHTRANGER8_TEST_PLL_BIST_MAX_THRESHOLD_LO                                     0x04F3
#define LIGHTRANGER8_TEST_PLL_BIST_COUNT_OUT                                            0x04F4
#define LIGHTRANGER8_TEST_PLL_BIST_COUNT_OUT_HI                                         0x04F4
#define LIGHTRANGER8_TEST_PLL_BIST_COUNT_OUT_LO                                         0x04F5
#define LIGHTRANGER8_TEST_PLL_BIST_GONOGO                                               0x04F6
#define LIGHTRANGER8_TEST_PLL_BIST_CTRL                                                 0x04F7
#define LIGHTRANGER8_RANGING_CORE_DEVICE_ID                                             0x0680
#define LIGHTRANGER8_RANGING_CORE_REVISION_ID                                           0x0681
#define LIGHTRANGER8_RANGING_CORE_CLK_CTRL1                                             0x0683
#define LIGHTRANGER8_RANGING_CORE_CLK_CTRL2                                             0x0684
#define LIGHTRANGER8_RANGING_CORE_WOI_1                                                 0x0685
#define LIGHTRANGER8_RANGING_CORE_WOI_REF_1                                             0x0686
#define LIGHTRANGER8_RANGING_CORE_START_RANGING                                         0x0687
#define LIGHTRANGER8_RANGING_CORE_LOW_LIMIT_1                                           0x0690
#define LIGHTRANGER8_RANGING_CORE_HIGH_LIMIT_1                                          0x0691
#define LIGHTRANGER8_RANGING_CORE_LOW_LIMIT_REF_1                                       0x0692
#define LIGHTRANGER8_RANGING_CORE_HIGH_LIMIT_REF_1                                      0x0693
#define LIGHTRANGER8_RANGING_CORE_QUANTIFIER_1_MSB                                      0x0694
#define LIGHTRANGER8_RANGING_CORE_QUANTIFIER_1_LSB                                      0x0695
#define LIGHTRANGER8_RANGING_CORE_QUANTIFIER_REF_1_MSB                                  0x0696
#define LIGHTRANGER8_RANGING_CORE_QUANTIFIER_REF_1_LSB                                  0x0697
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_OFFSET_1_MSB                                  0x0698
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_OFFSET_1_LSB                                  0x0699
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_OFFSET_REF_1_MSB                              0x069A
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_OFFSET_REF_1_LSB                              0x069B
#define LIGHTRANGER8_RANGING_CORE_FILTER_STRENGTH_1                                     0x069C
#define LIGHTRANGER8_RANGING_CORE_FILTER_STRENGTH_REF_1                                 0x069D
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_EVENT_LIMIT_1_MSB                              0x069E
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_EVENT_LIMIT_1_LSB                              0x069F
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_EVENT_LIMIT_REF_1_MSB                          0x06A0
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_EVENT_LIMIT_REF_1_LSB                          0x06A1
#define LIGHTRANGER8_RANGING_CORE_TIMEOUT_OVERALL_PERIODS_MSB                           0x06A4
#define LIGHTRANGER8_RANGING_CORE_TIMEOUT_OVERALL_PERIODS_LSB                           0x06A5
#define LIGHTRANGER8_RANGING_CORE_INVERT_HW                                             0x06A6
#define LIGHTRANGER8_RANGING_CORE_FORCE_HW                                              0x06A7
#define LIGHTRANGER8_RANGING_CORE_STATIC_HW_VALUE                                       0x06A8
#define LIGHTRANGER8_RANGING_CORE_FORCE_CONTINUOUS_AMBIENT                              0x06A9
#define LIGHTRANGER8_RANGING_CORE_TEST_PHASE_SELECT_TO_FILTER                           0x06AA
#define LIGHTRANGER8_RANGING_CORE_TEST_PHASE_SELECT_TO_TIMING_GEN                       0x06AB
#define LIGHTRANGER8_RANGING_CORE_INITIAL_PHASE_VALUE_1                                 0x06AC
#define LIGHTRANGER8_RANGING_CORE_INITIAL_PHASE_VALUE_REF_1                             0x06AD
#define LIGHTRANGER8_RANGING_CORE_FORCE_UP_IN                                           0x06AE
#define LIGHTRANGER8_RANGING_CORE_FORCE_DN_IN                                           0x06AF
#define LIGHTRANGER8_RANGING_CORE_STATIC_UP_VALUE_1                                     0x06B0
#define LIGHTRANGER8_RANGING_CORE_STATIC_UP_VALUE_REF_1                                 0x06B1
#define LIGHTRANGER8_RANGING_CORE_STATIC_DN_VALUE_1                                     0x06B2
#define LIGHTRANGER8_RANGING_CORE_STATIC_DN_VALUE_REF_1                                 0x06B3
#define LIGHTRANGER8_RANGING_CORE_MONITOR_UP_DN                                         0x06B4
#define LIGHTRANGER8_RANGING_CORE_INVERT_UP_DN                                          0x06B5
#define LIGHTRANGER8_RANGING_CORE_CPUMP_1                                               0x06B6
#define LIGHTRANGER8_RANGING_CORE_CPUMP_2                                               0x06B7
#define LIGHTRANGER8_RANGING_CORE_CPUMP_3                                               0x06B8
#define LIGHTRANGER8_RANGING_CORE_OSC_1                                                 0x06B9
#define LIGHTRANGER8_RANGING_CORE_PLL_1                                                 0x06BB
#define LIGHTRANGER8_RANGING_CORE_PLL_2                                                 0x06BC
#define LIGHTRANGER8_RANGING_CORE_REFERENCE_1                                           0x06BD
#define LIGHTRANGER8_RANGING_CORE_REFERENCE_3                                           0x06BF
#define LIGHTRANGER8_RANGING_CORE_REFERENCE_4                                           0x06C0
#define LIGHTRANGER8_RANGING_CORE_REFERENCE_5                                           0x06C1
#define LIGHTRANGER8_RANGING_CORE_REGAVDD1V2                                            0x06C3
#define LIGHTRANGER8_RANGING_CORE_CALIB_1                                               0x06C4
#define LIGHTRANGER8_RANGING_CORE_CALIB_2                                               0x06C5
#define LIGHTRANGER8_RANGING_CORE_CALIB_3                                               0x06C6
#define LIGHTRANGER8_RANGING_CORE_TST_MUX_SEL1                                          0x06C9
#define LIGHTRANGER8_RANGING_CORE_TST_MUX_SEL2                                          0x06CA
#define LIGHTRANGER8_RANGING_CORE_TST_MUX                                               0x06CB
#define LIGHTRANGER8_RANGING_CORE_GPIO_OUT_TESTMUX                                      0x06CC
#define LIGHTRANGER8_RANGING_CORE_CUSTOM_FE                                             0x06CD
#define LIGHTRANGER8_RANGING_CORE_CUSTOM_FE_2                                           0x06CE
#define LIGHTRANGER8_RANGING_CORE_SPAD_READOUT                                          0x06CF
#define LIGHTRANGER8_RANGING_CORE_SPAD_READOUT_1                                        0x06D0
#define LIGHTRANGER8_RANGING_CORE_SPAD_READOUT_2                                        0x06D1
#define LIGHTRANGER8_RANGING_CORE_SPAD_PS                                               0x06D2
#define LIGHTRANGER8_RANGING_CORE_LASER_SAFETY_2                                        0x06D4
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_MODE                                         0x0780
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_PDN                                          0x0781
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_PROGN                                        0x0782
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_READN                                        0x0783
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_PULSE_WIDTH_MSB                              0x0784
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_PULSE_WIDTH_LSB                              0x0785
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_HV_RISE_MSB                                  0x0786
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_HV_RISE_LSB                                  0x0787
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_HV_FALL_MSB                                  0x0788
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_HV_FALL_LSB                                  0x0789
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_TST                                          0x078A
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_TESTREAD                                     0x078B
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_DATAIN_MMM                                   0x078C
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_DATAIN_LMM                                   0x078D
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_DATAIN_LLM                                   0x078E
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_DATAIN_LLL                                   0x078F
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_DATAOUT_MMM                                  0x0790
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_DATAOUT_LMM                                  0x0791
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_DATAOUT_LLM                                  0x0792
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_DATAOUT_LLL                                  0x0793
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_ADDR                                         0x0794
#define LIGHTRANGER8_RANGING_CORE_NVM_CTRL_DATAOUT_ECC                                  0x0795
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_0                                         0x0796
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_1                                         0x0797
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_2                                         0x0798
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_3                                         0x0799
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_4                                         0x079A
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_5                                         0x079B
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_6                                         0x079C
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_7                                         0x079D
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_8                                         0x079E
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_9                                         0x079F
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_10                                        0x07A0
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_11                                        0x07A1
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_12                                        0x07A2
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_13                                        0x07A3
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_14                                        0x07A4
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_15                                        0x07A5
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_16                                        0x07A6
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_17                                        0x07A7
#define LIGHTRANGER8_RANGING_CORE_SPAD_SHIFT_EN                                         0x07BA
#define LIGHTRANGER8_RANGING_CORE_SPAD_DISABLE_CTRL                                     0x07BB
#define LIGHTRANGER8_RANGING_CORE_SPAD_EN_SHIFT_OUT_DEBUG                               0x07BC
#define LIGHTRANGER8_RANGING_CORE_SPI_MODE                                              0x07BD
#define LIGHTRANGER8_RANGING_CORE_GPIO_DIR                                              0x07BE
#define LIGHTRANGER8_RANGING_CORE_VCSEL_PERIOD                                          0x0880
#define LIGHTRANGER8_RANGING_CORE_VCSEL_START                                           0x0881
#define LIGHTRANGER8_RANGING_CORE_VCSEL_STOP                                            0x0882
#define LIGHTRANGER8_RANGING_CORE_VCSEL_1                                               0x0885
#define LIGHTRANGER8_RANGING_CORE_VCSEL_STATUS                                          0x088D
#define LIGHTRANGER8_RANGING_CORE_STATUS                                                0x0980
#define LIGHTRANGER8_RANGING_CORE_LASER_CONTINUITY_STATE                                0x0981
#define LIGHTRANGER8_RANGING_CORE_RANGE_1_MMM                                           0x0982
#define LIGHTRANGER8_RANGING_CORE_RANGE_1_LMM                                           0x0983
#define LIGHTRANGER8_RANGING_CORE_RANGE_1_LLM                                           0x0984
#define LIGHTRANGER8_RANGING_CORE_RANGE_1_LLL                                           0x0985
#define LIGHTRANGER8_RANGING_CORE_RANGE_REF_1_MMM                                       0x0986
#define LIGHTRANGER8_RANGING_CORE_RANGE_REF_1_LMM                                       0x0987
#define LIGHTRANGER8_RANGING_CORE_RANGE_REF_1_LLM                                       0x0988
#define LIGHTRANGER8_RANGING_CORE_RANGE_REF_1_LLL                                       0x0989
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_WINDOW_EVENTS_1_MMM                           0x098A
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_WINDOW_EVENTS_1_LMM                           0x098B
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_WINDOW_EVENTS_1_LLM                           0x098C
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_WINDOW_EVENTS_1_LLL                           0x098D
#define LIGHTRANGER8_RANGING_CORE_RANGING_TOTAL_EVENTS_1_MMM                            0x098E
#define LIGHTRANGER8_RANGING_CORE_RANGING_TOTAL_EVENTS_1_LMM                            0x098F
#define LIGHTRANGER8_RANGING_CORE_RANGING_TOTAL_EVENTS_1_LLM                            0x0990
#define LIGHTRANGER8_RANGING_CORE_RANGING_TOTAL_EVENTS_1_LLL                            0x0991
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_TOTAL_EVENTS_1_MMM                             0x0992
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_TOTAL_EVENTS_1_LMM                             0x0993
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_TOTAL_EVENTS_1_LLM                             0x0994
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_TOTAL_EVENTS_1_LLL                             0x0995
#define LIGHTRANGER8_RANGING_CORE_TOTAL_PERIODS_ELAPSED_1_MM                            0x0996
#define LIGHTRANGER8_RANGING_CORE_TOTAL_PERIODS_ELAPSED_1_LM                            0x0997
#define LIGHTRANGER8_RANGING_CORE_TOTAL_PERIODS_ELAPSED_1_LL                            0x0998
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_MISMATCH_MM                                   0x0999
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_MISMATCH_LM                                   0x099A
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_MISMATCH_LL                                   0x099B
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_WINDOW_EVENTS_REF_1_MMM                       0x099C
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_WINDOW_EVENTS_REF_1_LMM                       0x099D
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_WINDOW_EVENTS_REF_1_LLM                       0x099E
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_WINDOW_EVENTS_REF_1_LLL                       0x099F
#define LIGHTRANGER8_RANGING_CORE_RANGING_TOTAL_EVENTS_REF_1_MMM                        0x09A0
#define LIGHTRANGER8_RANGING_CORE_RANGING_TOTAL_EVENTS_REF_1_LMM                        0x09A1
#define LIGHTRANGER8_RANGING_CORE_RANGING_TOTAL_EVENTS_REF_1_LLM                        0x09A2
#define LIGHTRANGER8_RANGING_CORE_RANGING_TOTAL_EVENTS_REF_1_LLL                        0x09A3
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_TOTAL_EVENTS_REF_1_MMM                         0x09A4
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_TOTAL_EVENTS_REF_1_LMM                         0x09A5
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_TOTAL_EVENTS_REF_1_LLM                         0x09A6
#define LIGHTRANGER8_RANGING_CORE_SIGNAL_TOTAL_EVENTS_REF_1_LLL                         0x09A7
#define LIGHTRANGER8_RANGING_CORE_TOTAL_PERIODS_ELAPSED_REF_1_MM                        0x09A8
#define LIGHTRANGER8_RANGING_CORE_TOTAL_PERIODS_ELAPSED_REF_1_LM                        0x09A9
#define LIGHTRANGER8_RANGING_CORE_TOTAL_PERIODS_ELAPSED_REF_1_LL                        0x09AA
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_MISMATCH_REF_MM                               0x09AB
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_MISMATCH_REF_LM                               0x09AC
#define LIGHTRANGER8_RANGING_CORE_AMBIENT_MISMATCH_REF_LL                               0x09AD
#define LIGHTRANGER8_RANGING_CORE_GPIO_CONFIG_A0                                        0x0A00
#define LIGHTRANGER8_RANGING_CORE_RESET_CONTROL_A0                                      0x0A01
#define LIGHTRANGER8_RANGING_CORE_INTR_MANAGER_A0                                       0x0A02
#define LIGHTRANGER8_RANGING_CORE_POWER_FSM_TIME_OSC_A0                                 0x0A06
#define LIGHTRANGER8_RANGING_CORE_VCSEL_ATEST_A0                                        0x0A07
#define LIGHTRANGER8_RANGING_CORE_VCSEL_PERIOD_CLIPPED_A0                               0x0A08
#define LIGHTRANGER8_RANGING_CORE_VCSEL_STOP_CLIPPED_A0                                 0x0A09
#define LIGHTRANGER8_RANGING_CORE_CALIB_2_A0                                            0x0A0A
#define LIGHTRANGER8_RANGING_CORE_STOP_CONDITION_A0                                     0x0A0B
#define LIGHTRANGER8_RANGING_CORE_STATUS_RESET_A0                                       0x0A0C
#define LIGHTRANGER8_RANGING_CORE_READOUT_CFG_A0                                        0x0A0D
#define LIGHTRANGER8_RANGING_CORE_WINDOW_SETTING_A0                                     0x0A0E
#define LIGHTRANGER8_RANGING_CORE_VCSEL_DELAY_A0                                        0x0A1A
#define LIGHTRANGER8_RANGING_CORE_REFERENCE_2_A0                                        0x0A1B
#define LIGHTRANGER8_RANGING_CORE_REGAVDD1V2_A0                                         0x0A1D
#define LIGHTRANGER8_RANGING_CORE_TST_MUX_A0                                            0x0A1F
#define LIGHTRANGER8_RANGING_CORE_CUSTOM_FE_2_A0                                        0x0A20
#define LIGHTRANGER8_RANGING_CORE_SPAD_READOUT_A0                                       0x0A21
#define LIGHTRANGER8_RANGING_CORE_CPUMP_1_A0                                            0x0A22
#define LIGHTRANGER8_RANGING_CORE_SPARE_REGISTER_A0                                     0x0A23
#define LIGHTRANGER8_RANGING_CORE_VCSEL_CONT_STAGE5_BYPASS_A0                           0x0A24
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_18                                        0x0A25
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_19                                        0x0A26
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_20                                        0x0A27
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_21                                        0x0A28
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_22                                        0x0A29
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_23                                        0x0A2A
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_24                                        0x0A2B
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_25                                        0x0A2C
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_26                                        0x0A2D
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_27                                        0x0A2E
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_28                                        0x0A2F
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_29                                        0x0A30
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_30                                        0x0A31
#define LIGHTRANGER8_RANGING_CORE_RET_SPAD_EN_31                                        0x0A32
#define LIGHTRANGER8_RANGING_CORE_REF_SPAD_EN_0_EWOK                                    0x0A33
#define LIGHTRANGER8_RANGING_CORE_REF_SPAD_EN_1_EWOK                                    0x0A34
#define LIGHTRANGER8_RANGING_CORE_REF_SPAD_EN_2_EWOK                                    0x0A35
#define LIGHTRANGER8_RANGING_CORE_REF_SPAD_EN_3_EWOK                                    0x0A36
#define LIGHTRANGER8_RANGING_CORE_REF_SPAD_EN_4_EWOK                                    0x0A37
#define LIGHTRANGER8_RANGING_CORE_REF_SPAD_EN_5_EWOK                                    0x0A38
#define LIGHTRANGER8_RANGING_CORE_REF_EN_START_SELECT                                   0x0A39
#define LIGHTRANGER8_RANGING_CORE_REGDVDD1V2_ATEST_EWOK                                 0x0A41
#define LIGHTRANGER8_SOFT_RESET_GO1                                                     0x0B00
#define LIGHTRANGER8_PRIVATE_PATCH_BASE_ADDR_RSLV                                       0x0E00
#define LIGHTRANGER8_PREV_SHADOW_RESULT_INTERRUPT_STATUS                                0x0ED0
#define LIGHTRANGER8_PREV_SHADOW_RESULT_RANGE_STATUS                                    0x0ED1
#define LIGHTRANGER8_PREV_SHADOW_RESULT_REPORT_STATUS                                   0x0ED2
#define LIGHTRANGER8_PREV_SHADOW_RESULT_STREAM_COUNT                                    0x0ED3
#define LIGHTRANGER8_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0                  0x0ED4
#define LIGHTRANGER8_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_HI               0x0ED4
#define LIGHTRANGER8_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_LO               0x0ED5
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0                 0x0ED6
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_HI              0x0ED6
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_LO              0x0ED7
#define LIGHTRANGER8_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0                     0x0ED8
#define LIGHTRANGER8_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_HI                  0x0ED8
#define LIGHTRANGER8_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_LO                  0x0ED9
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SIGMA_SD0                                       0x0EDA
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SIGMA_SD0_HI                                    0x0EDA
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SIGMA_SD0_LO                                    0x0EDB
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PHASE_SD0                                       0x0EDC
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PHASE_SD0_HI                                    0x0EDC
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PHASE_SD0_LO                                    0x0EDD
#define LIGHTRANGER8_PREV_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0          0x0EDE
#define LIGHTRANGER8_PREV_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_HI                     0x0EDE
#define LIGHTRANGER8_PREV_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_LO                     0x0EDF
#define LIGHTRANGER8_PREV_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0           0x0EE0
#define LIGHTRANGER8_PPEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_HI            0x0EE0
#define LIGHTRANGER8_PPEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_LO            0x0EE1
#define LIGHTRANGER8_PREV_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0             0x0EE2
#define LIGHTRANGER8_PREV_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_HI          0x0EE2
#define LIGHTRANGER8_PREV_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_LO          0x0EE3
#define LIGHTRANGER8_PREV_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0             0x0EE4
#define LIGHTRANGER8_PREV_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_HI          0x0EE4
#define LIGHTRANGER8_PREV_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_LO          0x0EE5
#define LIGHTRANGER8_PREV_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0                  0x0EE6
#define LIGHTRANGER8_PREV_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_HI               0x0EE6
#define LIGHTRANGER8_PREV_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_LO               0x0EE7
#define LIGHTRANGER8_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1                  0x0EE8
#define LIGHTRANGER8_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_HI               0x0EE8
#define LIGHTRANGER8_PREV_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_LO               0x0EE9
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1                 0x0EEA
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_HI              0x0EEA
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_LO              0x0EEB
#define LIGHTRANGER8_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1                     0x0EEC
#define LIGHTRANGER8_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_HI                  0x0EEC
#define LIGHTRANGER8_PREV_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_LO                  0x0EED
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SIGMA_SD1                                       0x0EEE
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SIGMA_SD1_HI                                    0x0EEE
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SIGMA_SD1_LO                                    0x0EEF
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PHASE_SD1                                       0x0EF0
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PHASE_SD1_HI                                    0x0EF0
#define LIGHTRANGER8_PREV_SHADOW_RESULT_PHASE_SD1_LO                                    0x0EF1
#define LIGHTRANGER8_PREV_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1          0x0EF2
#define LIGHTRANGER8_PFINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_HI                         0x0EF2
#define LIGHTRANGER8_PFINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_LO                         0x0EF3
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_0_SD1                                     0x0EF4
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_0_SD1_HI                                  0x0EF4
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_0_SD1_LO                                  0x0EF5
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_1_SD1                                     0x0EF6
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_1_SD1_HI                                  0x0EF6
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_1_SD1_LO                                  0x0EF7
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_2_SD1                                     0x0EF8
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_2_SD1_HI                                  0x0EF8
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_2_SD1_LO                                  0x0EF9
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_3_SD1                                     0x0EFA
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_3_SD1_HI                                  0x0EFA
#define LIGHTRANGER8_PREV_SHADOW_RESULT_SPARE_3_SD1_LO                                  0x0EFB
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0                  0x0EFC
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_3                0x0EFC
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_2                0x0EFD
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_1                0x0EFE
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_0                0x0EFF
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0                   0x0F00
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_3                 0x0F00
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_2                 0x0F01
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_1                 0x0F02
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_0                 0x0F03
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0                    0x0F04
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_3                  0x0F04
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_2                  0x0F05
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_1                  0x0F06
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_0                  0x0F07
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0                  0x0F08
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_3                0x0F08
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_2                0x0F09
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_1                0x0F0A
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_0                0x0F0B
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1                  0x0F0C
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_3                0x0F0C
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_2                0x0F0D
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_1                0x0F0E
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_0                0x0F0F
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1                   0x0F10
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_3                 0x0F10
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_2                 0x0F11
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_1                 0x0F12
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_0                 0x0F13
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1                    0x0F14
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_3                  0x0F14
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_2                  0x0F15
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_1                  0x0F16
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_0                  0x0F17
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1                  0x0F18
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_3                0x0F18
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_2                0x0F19
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_1                0x0F1A
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_0                0x0F1B
#define LIGHTRANGER8_PREV_SHADOW_RESULT_CORE_SPARE_0                                    0x0F1C
#define LIGHTRANGER8_RESULT_DEBUG_STATUS                                                0x0F20
#define LIGHTRANGER8_RESULT_DEBUG_STAGE                                                 0x0F21
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_RATE_HIGH                                        0x0F24
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_RATE_HIGH_HI                                     0x0F24
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_RATE_HIGH_LO                                     0x0F25
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_RATE_LOW                                         0x0F26
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_RATE_LOW_HI                                      0x0F26
#define LIGHTRANGER8_GPH_SYSTEM_THRESH_RATE_LOW_LO                                      0x0F27
#define LIGHTRANGER8_GPH_SYSTEM_INTERRUPT_CONFIG_GPIO                                   0x0F28
#define LIGHTRANGER8_GPH_DSS_CONFIG_ROI_MODE_CONTROL                                    0x0F2F
#define LIGHTRANGER8_GPH_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT                       0x0F30
#define LIGHTRANGER8_GPH_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT_HI                    0x0F30
#define LIGHTRANGER8_GPH_DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT_LO                    0x0F31
#define LIGHTRANGER8_GPH_DSS_CONFIG_MANUAL_BLOCK_SELECT                                 0x0F32
#define LIGHTRANGER8_GPH_DSS_CONFIG_MAX_SPADS_LIMIT                                     0x0F33
#define LIGHTRANGER8_GPH_DSS_CONFIG_MIN_SPADS_LIMIT                                     0x0F34
#define LIGHTRANGER8_GPH_MM_CONFIG_TIMEOUT_MACROP_A_HI                                  0x0F36
#define LIGHTRANGER8_GPH_MM_CONFIG_TIMEOUT_MACROP_A_LO                                  0x0F37
#define LIGHTRANGER8_GPH_MM_CONFIG_TIMEOUT_MACROP_B_HI                                  0x0F38
#define LIGHTRANGER8_GPH_MM_CONFIG_TIMEOUT_MACROP_B_LO                                  0x0F39
#define LIGHTRANGER8_GPH_RANGE_CONFIG_TIMEOUT_MACROP_A_HI                               0x0F3A
#define LIGHTRANGER8_GPH_RANGE_CONFIG_TIMEOUT_MACROP_A_LO                               0x0F3B
#define LIGHTRANGER8_GPH_RANGE_CONFIG_VCSEL_PERIOD_A                                    0x0F3C
#define LIGHTRANGER8_GPH_RANGE_CONFIG_VCSEL_PERIOD_B                                    0x0F3D
#define LIGHTRANGER8_GPH_RANGE_CONFIG_TIMEOUT_MACROP_B_HI                               0x0F3E
#define LIGHTRANGER8_GPH_RANGE_CONFIG_TIMEOUT_MACROP_B_LO                               0x0F3F
#define LIGHTRANGER8_GPH_RANGE_CONFIG_SIGMA_THRESH                                      0x0F40
#define LIGHTRANGER8_GPH_RANGE_CONFIG_SIGMA_THRESH_HI                                   0x0F40
#define LIGHTRANGER8_GPH_RANGE_CONFIG_SIGMA_THRESH_LO                                   0x0F41
#define LIGHTRANGER8_GPH_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS                     0x0F42
#define LIGHTRANGER8_GPH_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS_HI                  0x0F42
#define LIGHTRANGER8_GPH_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS_LO                  0x0F43
#define LIGHTRANGER8_GPH_RANGE_CONFIG_VALID_PHASE_LOW                                   0x0F44
#define LIGHTRANGER8_GPH_RANGE_CONFIG_VALID_PHASE_HIGH                                  0x0F45
#define LIGHTRANGER8_FIRMWARE_INTERNAL_STREAM_COUNT_DIV                                 0x0F46
#define LIGHTRANGER8_FIRMWARE_INTERNAL_STREAM_COUNTER_VAL                               0x0F47
#define LIGHTRANGER8_DSS_CALC_ROI_CTRL                                                  0x0F54
#define LIGHTRANGER8_DSS_CALC_SPARE_1                                                   0x0F55
#define LIGHTRANGER8_DSS_CALC_SPARE_2                                                   0x0F56
#define LIGHTRANGER8_DSS_CALC_SPARE_3                                                   0x0F57
#define LIGHTRANGER8_DSS_CALC_SPARE_4                                                   0x0F58
#define LIGHTRANGER8_DSS_CALC_SPARE_5                                                   0x0F59
#define LIGHTRANGER8_DSS_CALC_SPARE_6                                                   0x0F5A
#define LIGHTRANGER8_DSS_CALC_SPARE_7                                                   0x0F5B
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_0                                        0x0F5C
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_1                                        0x0F5D
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_2                                        0x0F5E
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_3                                        0x0F5F
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_4                                        0x0F60
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_5                                        0x0F61
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_6                                        0x0F62
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_7                                        0x0F63
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_8                                        0x0F64
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_9                                        0x0F65
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_10                                       0x0F66
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_11                                       0x0F67
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_12                                       0x0F68
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_13                                       0x0F69
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_14                                       0x0F6A
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_15                                       0x0F6B
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_16                                       0x0F6C
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_17                                       0x0F6D
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_18                                       0x0F6E
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_19                                       0x0F6F
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_20                                       0x0F70
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_21                                       0x0F71
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_22                                       0x0F72
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_23                                       0x0F73
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_24                                       0x0F74
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_25                                       0x0F75
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_26                                       0x0F76
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_27                                       0x0F77
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_28                                       0x0F78
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_29                                       0x0F79
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_30                                       0x0F7A
#define LIGHTRANGER8_DSS_CALC_USER_ROI_SPAD_EN_31                                       0x0F7B
#define LIGHTRANGER8_DSS_CALC_USER_ROI_0                                                0x0F7C
#define LIGHTRANGER8_DSS_CALC_USER_ROI_1                                                0x0F7D
#define LIGHTRANGER8_DSS_CALC_MODE_ROI_0                                                0x0F7E
#define LIGHTRANGER8_DSS_CALC_MODE_ROI_1                                                0x0F7F
#define LIGHTRANGER8_SIGMA_ESTIMATOR_CALC_SPARE_0                                       0x0F80
#define LIGHTRANGER8_VHV_RESULT_PEAK_SIGNAL_RATE_MCPS                                   0x0F82
#define LIGHTRANGER8_VHV_RESULT_PEAK_SIGNAL_RATE_MCPS_HI                                0x0F82
#define LIGHTRANGER8_VHV_RESULT_PEAK_SIGNAL_RATE_MCPS_LO                                0x0F83
#define LIGHTRANGER8_VHV_RESULT_SIGNAL_TOTAL_EVENTS_REF                                 0x0F84
#define LIGHTRANGER8_VHV_RESULT_SIGNAL_TOTAL_EVENTS_REF_3                               0x0F84
#define LIGHTRANGER8_VHV_RESULT_SIGNAL_TOTAL_EVENTS_REF_2                               0x0F85
#define LIGHTRANGER8_VHV_RESULT_SIGNAL_TOTAL_EVENTS_REF_1                               0x0F86
#define LIGHTRANGER8_VHV_RESULT_SIGNAL_TOTAL_EVENTS_REF_0                               0x0F87
#define LIGHTRANGER8_PHASECAL_RESULT_PHASE_OUTPUT_REF                                   0x0F88
#define LIGHTRANGER8_PHASECAL_RESULT_PHASE_OUTPUT_REF_HI                                0x0F88
#define LIGHTRANGER8_PHASECAL_RESULT_PHASE_OUTPUT_REF_LO                                0x0F89
#define LIGHTRANGER8_DSS_RESULT_TOTAL_RATE_PER_SPAD                                     0x0F8A
#define LIGHTRANGER8_DSS_RESULT_TOTAL_RATE_PER_SPAD_HI                                  0x0F8A
#define LIGHTRANGER8_DSS_RESULT_TOTAL_RATE_PER_SPAD_LO                                  0x0F8B
#define LIGHTRANGER8_DSS_RESULT_ENABLED_BLOCKS                                          0x0F8C
#define LIGHTRANGER8_DSS_RESULT_NUM_REQUESTED_SPADS                                     0x0F8E
#define LIGHTRANGER8_DSS_RESULT_NUM_REQUESTED_SPADS_HI                                  0x0F8E
#define LIGHTRANGER8_DSS_RESULT_NUM_REQUESTED_SPADS_LO                                  0x0F8F
#define LIGHTRANGER8_MM_RESULT_INNER_INTERSECTION_RATE                                  0x0F92
#define LIGHTRANGER8_MM_RESULT_INNER_INTERSECTION_RATE_HI                               0x0F92
#define LIGHTRANGER8_MM_RESULT_INNER_INTERSECTION_RATE_LO                               0x0F93
#define LIGHTRANGER8_MM_RESULT_OUTER_COMPLEMENT_RATE                                    0x0F94
#define LIGHTRANGER8_MM_RESULT_OUTER_COMPLEMENT_RATE_HI                                 0x0F94
#define LIGHTRANGER8_MM_RESULT_OUTER_COMPLEMENT_RATE_LO                                 0x0F95
#define LIGHTRANGER8_MM_RESULT_TOTAL_OFFSET                                             0x0F96
#define LIGHTRANGER8_MM_RESULT_TOTAL_OFFSET_HI                                          0x0F96
#define LIGHTRANGER8_MM_RESULT_TOTAL_OFFSET_LO                                          0x0F97
#define LIGHTRANGER8_XTALK_CALC_XTALK_FOR_ENABLED_SPADS                                 0x0F98
#define LIGHTRANGER8_XTALK_CALC_XTALK_FOR_ENABLED_SPADS_3                               0x0F98
#define LIGHTRANGER8_XTALK_CALC_XTALK_FOR_ENABLED_SPADS_2                               0x0F99
#define LIGHTRANGER8_XTALK_CALC_XTALK_FOR_ENABLED_SPADS_1                               0x0F9A
#define LIGHTRANGER8_XTALK_CALC_XTALK_FOR_ENABLED_SPADS_0                               0x0F9B
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_USER_ROI_KCPS                               0x0F9C
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_USER_ROI_KCPS_3                             0x0F9C
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_USER_ROI_KCPS_2                             0x0F9D
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_USER_ROI_KCPS_1                             0x0F9E
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_USER_ROI_KCPS_0                             0x0F9F
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_MM_INNER_ROI_KCPS                           0x0FA0
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_MM_INNER_ROI_KCPS_3                         0x0FA0
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_MM_INNER_ROI_KCPS_2                         0x0FA1
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_MM_INNER_ROI_KCPS_1                         0x0FA2
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_MM_INNER_ROI_KCPS_0                         0x0FA3
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_MM_OUTER_ROI_KCPS                           0x0FA4
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_MM_OUTER_ROI_KCPS_3                         0x0FA4
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_MM_OUTER_ROI_KCPS_2                         0x0FA5
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_MM_OUTER_ROI_KCPS_1                         0x0FA6
#define LIGHTRANGER8_XTALK_RESULT_AVG_XTALK_MM_OUTER_ROI_KCPS_0                         0x0FA7
#define LIGHTRANGER8_RANGE_RESULT_ACCUM_PHASE                                           0x0FA8
#define LIGHTRANGER8_RANGE_RESULT_ACCUM_PHASE_3                                         0x0FA8
#define LIGHTRANGER8_RANGE_RESULT_ACCUM_PHASE_2                                         0x0FA9
#define LIGHTRANGER8_RANGE_RESULT_ACCUM_PHASE_1                                         0x0FAA
#define LIGHTRANGER8_RANGE_RESULT_ACCUM_PHASE_0                                         0x0FAB
#define LIGHTRANGER8_RANGE_RESULT_OFFSET_CORRECTED_RANGE                                0x0FAC
#define LIGHTRANGER8_RANGE_RESULT_OFFSET_CORRECTED_RANGE_HI                             0x0FAC
#define LIGHTRANGER8_RANGE_RESULT_OFFSET_CORRECTED_RANGE_LO                             0x0FAD
#define LIGHTRANGER8_SHADOW_PHASECAL_RESULT_VCSEL_START                                 0x0FAE
#define LIGHTRANGER8_SHADOW_RESULT_INTERRUPT_STATUS                                     0x0FB0
#define LIGHTRANGER8_SHADOW_RESULT_RANGE_STATUS                                         0x0FB1
#define LIGHTRANGER8_SHADOW_RESULT_REPORT_STATUS                                        0x0FB2
#define LIGHTRANGER8_SHADOW_RESULT_STREAM_COUNT                                         0x0FB3
#define LIGHTRANGER8_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0                       0x0FB4
#define LIGHTRANGER8_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_HI                    0x0FB4
#define LIGHTRANGER8_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_LO                    0x0FB5
#define LIGHTRANGER8_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0                      0x0FB6
#define LIGHTRANGER8_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_HI                   0x0FB6
#define LIGHTRANGER8_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_LO                   0x0FB7
#define LIGHTRANGER8_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0                          0x0FB8
#define LIGHTRANGER8_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_HI                       0x0FB8
#define LIGHTRANGER8_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_LO                       0x0FB9
#define LIGHTRANGER8_SHADOW_RESULT_SIGMA_SD0                                            0x0FBA
#define LIGHTRANGER8_SHADOW_RESULT_SIGMA_SD0_HI                                         0x0FBA
#define LIGHTRANGER8_SHADOW_RESULT_SIGMA_SD0_LO                                         0x0FBB
#define LIGHTRANGER8_SHADOW_RESULT_PHASE_SD0                                            0x0FBC
#define LIGHTRANGER8_SHADOW_RESULT_PHASE_SD0_HI                                         0x0FBC
#define LIGHTRANGER8_SHADOW_RESULT_PHASE_SD0_LO                                         0x0FBD
#define LIGHTRANGER8_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0               0x0FBE
#define LIGHTRANGER8_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_HI            0x0FBE
#define LIGHTRANGER8_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_LO            0x0FBF
#define LIGHTRANGER8_SHPEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0              0x0FC0
#define LIGHTRANGER8_SHPEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_HI           0x0FC0
#define LIGHTRANGER8_SHPEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_LO           0x0FC1
#define LIGHTRANGER8_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0                  0x0FC2
#define LIGHTRANGER8_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_HI               0x0FC2
#define LIGHTRANGER8_SHADOW_RESULT_MM_INNER_ACTUAL_EFFECTIVE_SPADS_SD0_LO               0x0FC3
#define LIGHTRANGER8_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0                  0x0FC4
#define LIGHTRANGER8_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_HI               0x0FC4
#define LIGHTRANGER8_SHADOW_RESULT_MM_OUTER_ACTUAL_EFFECTIVE_SPADS_SD0_LO               0x0FC5
#define LIGHTRANGER8_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0                       0x0FC6
#define LIGHTRANGER8_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_HI                    0x0FC6
#define LIGHTRANGER8_SHADOW_RESULT_AVG_SIGNAL_COUNT_RATE_MCPS_SD0_LO                    0x0FC7
#define LIGHTRANGER8_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1                       0x0FC8
#define LIGHTRANGER8_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_HI                    0x0FC8
#define LIGHTRANGER8_SHADOW_RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD1_LO                    0x0FC9
#define LIGHTRANGER8_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1                      0x0FCA
#define LIGHTRANGER8_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_HI                   0x0FCA
#define LIGHTRANGER8_SHADOW_RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD1_LO                   0x0FCB
#define LIGHTRANGER8_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1                          0x0FCC
#define LIGHTRANGER8_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_HI                       0x0FCC
#define LIGHTRANGER8_SHADOW_RESULT_AMBIENT_COUNT_RATE_MCPS_SD1_LO                       0x0FCD
#define LIGHTRANGER8_SHADOW_RESULT_SIGMA_SD1                                            0x0FCE
#define LIGHTRANGER8_SHADOW_RESULT_SIGMA_SD1_HI                                         0x0FCE
#define LIGHTRANGER8_SHADOW_RESULT_SIGMA_SD1_LO                                         0x0FCF
#define LIGHTRANGER8_SHADOW_RESULT_PHASE_SD1                                            0x0FD0
#define LIGHTRANGER8_SHADOW_RESULT_PHASE_SD1_HI                                         0x0FD0
#define LIGHTRANGER8_SHADOW_RESULT_PHASE_SD1_LO                                         0x0FD1
#define LIGHTRANGER8_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1               0x0FD2
#define LIGHTRANGER8_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_HI            0x0FD2
#define LIGHTRANGER8_SHADOW_RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD1_LO            0x0FD3
#define LIGHTRANGER8_SHADOW_RESULT_SPARE_0_SD1                                          0x0FD4
#define LIGHTRANGER8_SHADOW_RESULT_SPARE_0_SD1_HI                                       0x0FD4
#define LIGHTRANGER8_SHADOW_RESULT_SPARE_0_SD1_LO                                       0x0FD5
#define LIGHTRANGER8_SHADOW_RESULT_SPARE_1_SD1                                          0x0FD6
#define LIGHTRANGER8_SHADOW_RESULT_SPARE_1_SD1_HI                                       0x0FD6
#define LIGHTRANGER8_SHADOW_RESULT_SPARE_1_SD1_LO                                       0x0FD7
#define LIGHTRANGER8_SHADOW_RESULT_SPARE_2_SD1                                          0x0FD8
#define LIGHTRANGER8_SHADOW_RESULT_SPARE_2_SD1_HI                                       0x0FD8
#define LIGHTRANGER8_SHADOW_RESULT_SPARE_2_SD1_LO                                       0x0FD9
#define LIGHTRANGER8_SHADOW_RESULT_SPARE_3_SD1                                          0x0FDA
#define LIGHTRANGER8_SHADOW_RESULT_THRESH_INFO                                          0x0FDB
#define LIGHTRANGER8_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0                       0x0FDC
#define LIGHTRANGER8_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_3                     0x0FDC
#define LIGHTRANGER8_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_2                     0x0FDD
#define LIGHTRANGER8_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_1                     0x0FDE
#define LIGHTRANGER8_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD0_0                     0x0FDF
#define LIGHTRANGER8_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0                        0x0FE0
#define LIGHTRANGER8_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_3                      0x0FE0
#define LIGHTRANGER8_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_2                      0x0FE1
#define LIGHTRANGER8_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_1                      0x0FE2
#define LIGHTRANGER8_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD0_0                      0x0FE3
#define LIGHTRANGER8_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0                         0x0FE4
#define LIGHTRANGER8_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_3                       0x0FE4
#define LIGHTRANGER8_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_2                       0x0FE5
#define LIGHTRANGER8_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_1                       0x0FE6
#define LIGHTRANGER8_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD0_0                       0x0FE7
#define LIGHTRANGER8_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0                       0x0FE8
#define LIGHTRANGER8_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_3                     0x0FE8
#define LIGHTRANGER8_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_2                     0x0FE9
#define LIGHTRANGER8_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_1                     0x0FEA
#define LIGHTRANGER8_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD0_0                     0x0FEB
#define LIGHTRANGER8_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1                       0x0FEC
#define LIGHTRANGER8_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_3                     0x0FEC
#define LIGHTRANGER8_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_2                     0x0FED
#define LIGHTRANGER8_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_1                     0x0FEE
#define LIGHTRANGER8_SHADOW_RESULT_CORE_AMBIENT_WINDOW_EVENTS_SD1_0                     0x0FEF
#define LIGHTRANGER8_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1                        0x0FF0
#define LIGHTRANGER8_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_3                      0x0FF0
#define LIGHTRANGER8_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_2                      0x0FF1
#define LIGHTRANGER8_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_1                      0x0FF2
#define LIGHTRANGER8_SHADOW_RESULT_CORE_RANGING_TOTAL_EVENTS_SD1_0                      0x0FF3
#define LIGHTRANGER8_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1                         0x0FF4
#define LIGHTRANGER8_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_3                       0x0FF4
#define LIGHTRANGER8_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_2                       0x0FF5
#define LIGHTRANGER8_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_1                       0x0FF6
#define LIGHTRANGER8_SHADOW_RESULT_CORE_SIGNAL_TOTAL_EVENTS_SD1_0                       0x0FF7
#define LIGHTRANGER8_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1                       0x0FF8
#define LIGHTRANGER8_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_3                     0x0FF8
#define LIGHTRANGER8_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_2                     0x0FF9
#define LIGHTRANGER8_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_1                     0x0FFA
#define LIGHTRANGER8_SHADOW_RESULT_CORE_TOTAL_PERIODS_ELAPSED_SD1_0                     0x0FFB
#define LIGHTRANGER8_SHADOW_RESULT_CORE_SPARE_0                                         0x0FFC
#define LIGHTRANGER8_SHADOW_PHASECAL_RESULT_REFERENCE_PHASE_HI                          0x0FFE
#define LIGHTRANGER8_SHADOW_PHASECAL_RESULT_REFERENCE_PHASE_LO                          0x0FFF

/*! @} */ // lightranger8_reg

/**
 * @addtogroup lightranger8_set
 * @{
 */

/**
 * @brief LightRanger 8 device address setting.
 * @details Specified setting for device slave address selection of
 * LightRanger 8 Click driver.
 */
#define LIGHTRANGER8_SET_DEV_ADDR                                0x29

/*! @} */ // lightranger8_set

/**
 * @addtogroup distance_mode
 * @{
 */

/**
 * @brief LightRanger 8 distance modes.
 * @details Settings of ranging distance modes of LightRanger 8 Click driver.
 */

#define LIGHTRANGER8_DISTANCE_MODE_SHORT                         0x00
#define LIGHTRANGER8_DISTANCE_MODE_MEDIUM                        0x01
#define LIGHTRANGER8_DISTANCE_MODE_LONG                          0x02

/*! @} */ // distance_mode

/**
 * @addtogroup ranging_mode
 * @{
 */

/**
 * @brief LightRanger 8 ranging modes.
 * @details Settings for enable/disable ranging of LightRanger 8 Click driver.
 */

#define LIGHTRANGER8_RANGING_ENABLE                              0x00
#define LIGHTRANGER8_RANGING_DISABLE                             0x01

/*! @} */ // ranging_mode

/**
 * @addtogroup lightranger8_resp
 * @{
 */

/**
 * @brief LightRanger 8 response codes.
 * @details Response returns from settings of LightRanger 8 Click driver.
 */

#define LIGHTRANGER8_RESP_INSUFFICIENT_BUDGET                    0x02
#define LIGHTRANGER8_RESP_TOO_HIGH_BUDGET                        0x01
#define LIGHTRANGER8_RESP_BUDGET_IS_SUCCESSFULLY_SET             0x00
#define LIGHTRANGER8_RESP_DEVICE_ERROR_ID_IS_NOT_VALID           0x01
#define LIGHTRANGER8_RESP_FIRMWARE_TIMEOUT_ERROR                 0x02
#define LIGHTRANGER8_RESP_INIT_IS_SUCCESSFUL                     0x00
#define LIGHTRANGER8_RESP_WRONG_MODE                             0x01
#define LIGHTRANGER8_RESP_MODE_SUCCESSFULLY_SET                  0x00
#define LIGHTRANGER8_MRESP_SIGNAL_FAIL                           0x04
#define LIGHTRANGER8_MRESP_PHASE_OUT_OF_VALID_LIMITS             0x05
#define LIGHTRANGER8_MRESP_SIGMA_FAIL                            0x06
#define LIGHTRANGER8_MRESP_WRAP_TARGET_FAIL                      0x07
#define LIGHTRANGER8_MRESP_MINIMUM_DETECTION_THRESHOLD           0x08

/*! @} */ // lightranger8_resp

/**
 * @addtogroup LightRanger 8 error_code
 * @{
 */

/**
 * @brief LightRanger 8 error codes.
 * @details Error codes from init of LightRanger 8 Click driver.
 */
#define LIGHTRANGER8_OK                                          0
#define LIGHTRANGER8_ERROR                                      -1

/*! @} */ // LightRanger 8 error_code

/**
 * @defgroup lightranger8_map LightRanger 8 MikroBUS Map
 * @brief MikroBUS pin mapping of LightRanger 8 Click driver.
 */

/**
 * @addtogroup lightranger8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LightRanger 8 Click to the selected MikroBUS.
 */
#define LIGHTRANGER8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );  \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );  \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );    \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lightranger8_map
/*! @} */ // lightranger8

/**
 * @brief LightRanger 8 Click context object.
 * @details Context object definition of LightRanger 8 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  en;                       /**< Digital output pin Xshut. */

    // Input pins

    digital_in_t  int_pin;                   /**< Digital input pin GPIO1. */

    // Modules

    i2c_master_t i2c;                        /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;                   /**< Device slave address (used for I2C driver). */
    
    uint16_t fast_osc_frequency;
    uint16_t osc_calibrate_val;

} lightranger8_t;

/**
 * @brief LightRanger 8 Click configuration object.
 * @details Configuration object definition of LightRanger 8 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                         /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                         /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;                          /**< Digital output pin Xshut. */
    pin_name_t  int_pin;                     /**< Digital input pin GPIO1. */

    uint32_t  i2c_speed;                     /**< I2C serial speed. */
    uint8_t   i2c_address;                   /**< I2C slave address. */

} lightranger8_cfg_t;

/*!
 * @addtogroup lightranger8 LightRanger 8 Click Driver
 * @brief API for configuring and manipulating LightRanger 8 Click driver.
 * @{
 */

/**
 * @brief LightRanger 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lightranger8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lightranger8_cfg_setup ( lightranger8_cfg_t *cfg );

/**
 * @brief LightRanger 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lightranger8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger8_init ( lightranger8_t *ctx, lightranger8_cfg_t *cfg );

/**
 * @brief LightRanger 8 default configuration function.
 * @details This function executes a default configuration of LightRanger 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @return @li @c  0x01 ( LIGHTRANGER8_RESP_DEVICE_ERROR_ID_IS_NOT_VALID ) - ID error,
 *         @li @c  0x02 ( LIGHTRANGER8_RESP_FIRMWARE_TIMEOUT_ERROR ) - Firmware timeout error,
 *         @li @c  0x00 ( LIGHTRANGER8_RESP_INIT_IS_SUCCESSFUL ) - Success.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lightranger8_default_cfg ( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger8_generic_write ( lightranger8_t *ctx, uint16_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief LightRanger 8 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger8_generic_read ( lightranger8_t *ctx, uint16_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief LightRanger 8 software reset function.
 * @details This function performs a software reset of the VL53Lx ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * 
 * @note None.
 */
void lightranger8_software_reset( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 system interrupt clear function.
 * @details This function clears the system interrupt bit of the VL53Lx ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * 
 * @note None.
 */
void lightranger8_system_interrupt_clear ( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 start ranging function.
 * @details This function sends either ranging enable or ranging disable
 * depending on the ranging mode parameter.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] ranging_mode : Ranging mode setting option.
 *         @li @c 0x40 ( DEV_CMD_RANGING_ENABLE ) - Ranging mode enable,
 *         @li @c 0x00 ( DEV_CMD_RANGING_DISABLE ) - Ranging mode disable.
 * 
 * @note None.
 */
void lightranger8_start_ranging_cmd ( lightranger8_t *ctx, uint8_t ranging_mode );

/**
 * @brief LightRanger 8 start measurement function.
 * @details This function enables the range measuring with the adjusted
 * intermeasurement period.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] period_ms : Intermeasurement period in miliseconds.
 * 
 * @note None.
 */
void lightranger8_start_measurement ( lightranger8_t *ctx, uint32_t period_ms );

/**
 * @brief LightRanger 8 stop measurement function.
 * @details This function stops the measurement of the VL53Lx ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * 
 * @note None.
 */
void lightranger8_stop_measurement ( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 data ready function.
 * @details This function returns the information if new data is ready
 * for acquiring the distance measured.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @return @li @c 0 - New data ready,
 *         @li @c 1 - Still measuring.
 *
 * @note None.
 */
uint8_t lightranger8_new_data_ready ( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 get distance function.
 * @details This function returns the corrected measured distance
 * from the VL53Lx ranging sensor described in milimeters.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @return Corrected distance in milimeters.
 *
 * @note None.
 */
uint16_t lightranger8_get_distance ( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 get signal rate function.
 * @details This function returns the corrected signal rate
 * MCPS from the VL53Lx ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @return Signal rate.
 *
 * @note None.
 */
uint16_t lightranger8_get_signal_rate ( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 set distance mode function.
 * @details This function sets the distance mode of the VL53Lx
 * ranging sensor with three possible modes.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] mode : Distance mode.
 *         @li @c 0x00 ( LIGHTRANGER8_DISTANCE_MODE_SHORT ) - Short distance mode,
 *         @li @c 0x01 ( LIGHTRANGER8_DISTANCE_MODE_MEDIUM ) - Medium distance mode,
 *         @li @c 0x02 ( LIGHTRANGER8_DISTANCE_MODE_LONG ) - Long distance mode.
 * @return @li @c 0x00 ( LIGHTRANGER8_RESP_MODE_SUCCESSFULLY_SET )- Distance mode successfully set,
 *         @li @c 0x01 ( LIGHTRANGER8_RESP_WRONG_MODE )- Wrong distance mode.
 *
 * @note None.
 */
uint8_t lightranger8_set_distance_mode ( lightranger8_t *ctx, uint8_t mode );

/**
 * @brief LightRanger 8 get range status function.
 * @details This function returns the range result status of the VL53Lx
 * ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @return LightRanger 8 response code.
 *
 * @note None.
 */
uint8_t lightranger8_get_range_status ( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 get roi center function.
 * @details This function returns the roi center value of the VL53Lx
 * ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @return ROI center.
 *
 * @note None.
 */
uint8_t lightranger8_get_roi_center ( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 set roi center function.
 * @details This function sets the roi center value of the VL53Lx
 * ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] roi_center : Desired roi center value.
 *
 * @note None.
 */
void lightranger8_set_roi_center ( lightranger8_t *ctx, uint8_t roi_center );

/**
 * @brief LightRanger 8 set roi function.
 * @details This function sets the roi x and y coords of the VL53Lx
 * ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] x : Desired x coord value.
 * @param[in] y : Desired y coord value.
 *
 * @note None.
 */
void lightranger8_set_roi ( lightranger8_t *ctx, uint16_t x, uint16_t y );

/**
 * @brief LightRanger 8 get roi function.
 * @details This function forwards the roi x and y coords of the VL53Lx
 * ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[out] roi_x : X coord value.
 * @param[out] roi_y : Y coord value.
 *
 * @note None.
 */
void lightranger8_get_roi ( lightranger8_t *ctx, uint16_t *roi_x, uint16_t *roi_y );

/**
 * @brief LightRanger 8 set offset function.
 * @details This function sets the offset of the final
 * corrected measurement from the VL53Lx ranging sensor.
 * The offset value is in milimeters.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] offset_value : Offset value in milimeters.
 *
 * @note None.
 */
void lightranger8_set_offset ( lightranger8_t *ctx, int16_t offset_value );

/**
 * @brief LightRanger 8 calibrate offset function.
 * @details This function calibrates the offset which affects the final
 * corrected measurement from the VL53Lx ranging sensor. The averaging
 * is concluded 50 times before the actual measurement sets in place.
 * The target distance value is in milimeters. Period should be set at
 * the same value as inteded measurement later on.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] target_distance_mm : Target distance value in milimeters.
 * @param[in] period_ms : Intermeasurement period in miliseconds.
 * @param[out] offset : Calibrated offset value.
 *
 * @note None.
 */
void lightranger8_calibrate_offset ( lightranger8_t *ctx, uint16_t target_distance_mm, uint32_t period_ms, int16_t *offset );

/**
 * @brief LightRanger 8 set measurement timing budget function.
 * @details This function sets the timing budget of the VL53Lx ranging sensor.
 * This is the time allocated by the user to perform one range measurement.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] budget_us : Timing budget in microseconds.
 * @return @li @c  0x02 ( LIGHTRANGER8_RESP_INSUFFICIENT_BUDGET ) - Low budget error,
 *         @li @c  0x01 ( LIGHTRANGER8_RESP_TOO_HIGH_BUDGET ) - High budget error,
 *         @li @c  0x00 ( LIGHTRANGER8_RESP_BUDGET_IS_SUCCESSFULLY_SET ) - Success.
 *
 * @note None.
 */
err_t lightranger8_set_measurement_timing_budget ( lightranger8_t *ctx, uint32_t budget_us );

/**
 * @brief LightRanger 8 get int pin state function.
 * @details This function checks the interrupt pin state.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @return INT pin state.
 *
 * @note None.
 * 
 */
uint8_t lightranger8_get_interrupt_state ( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 set xshut pin function.
 * @details This function sets the state of EN pin.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @param[in] state :
 *     @li @c 0 - Sets EN pin low.
 *     @li @c 1 - Sets EN pin high.
 * 
 * @note None.
 */
void lightranger8_set_xshut_pin ( lightranger8_t *ctx, uint8_t state );

/**
 * @brief LightRanger 8 power on function.
 * @details This function powers on the VL53Lx ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * 
 * @note None.
 */
void lightranger8_power_on ( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 get timing budget function.
 * @details This function returns the timing budget in microseconds
 * currently set in the VL53Lx ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @return Timing budget in microseconds.
 *
 * @note None.
 */
uint32_t lightranger8_get_timing_budget ( lightranger8_t *ctx );

/**
 * @brief LightRanger 8 get intermeasurement period function.
 * @details This function returns the intermeasurement period in
 * miliseconds currently set in the VL53Lx ranging sensor.
 * @param[in] ctx : Click context object.
 * See #lightranger8_t object definition for detailed explanation.
 * @return Intermeasurement period in miliseconds.
 *
 * @note None.
 */
uint16_t lightranger8_get_measurement_period ( lightranger8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LIGHTRANGER8_H

/*! @} */ // lightranger8

// ------------------------------------------------------------------------ END
