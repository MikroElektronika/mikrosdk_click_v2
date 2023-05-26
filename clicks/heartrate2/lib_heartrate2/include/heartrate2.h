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
 * \brief This file contains API for Heart rate 2 Click driver.
 *
 * \addtogroup heartrate2 Heart rate 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HEARTRATE2_H
#define HEARTRATE2_H

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
#define HEARTRATE2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HEARTRATE2_RETVAL  uint8_t

#define HEARTRATE2_OK_OK           0x00
#define HEARTRATE2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_slave_address Device slave address
 * \{
 */
#define HEARTRATE2_SLAVE_ADDRESS                            0x62
/** \} */

/**
 * \defgroup device_register_address Device register address
 * \{
 */
#define HEARTRATE2_REG_INT_STATUS_1                         0x00
#define HEARTRATE2_REG_INT_STATUS_2                         0x01
#define HEARTRATE2_REG_INT_ENABLE_1                         0x02
#define HEARTRATE2_REG_INT_ENABLE_2                         0x03
#define HEARTRATE2_REG_FIFO_WRITE_PTR                       0x04
#define HEARTRATE2_REG_FIFO_READ_PTR                        0x05
#define HEARTRATE2_REG_OVERFLOW_CNT                         0x06
#define HEARTRATE2_REG_FIFO_DATA_CNT                        0x07
#define HEARTRATE2_REG_FIFO_DATA_REG                        0x08
#define HEARTRATE2_REG_FIFO_CFG_1                           0x09
#define HEARTRATE2_REG_FIFO_CFG_2                           0x0A
#define HEARTRATE2_REG_SYSTEM_CTRL                          0x0D
#define HEARTRATE2_REG_PPG_SYNC_CTRL                        0x10
#define HEARTRATE2_REG_PPG_CFG_1                            0x11
#define HEARTRATE2_REG_PPG_CFG_2                            0x12
#define HEARTRATE2_REG_PPG_CFG_3                            0x13
#define HEARTRATE2_REG_PROX_INT_THRESHOLD                   0x14
#define HEARTRATE2_REG_PHOTO_DIODE_BIAS                     0x15
#define HEARTRATE2_REG_PICKET_FENCE                         0x16
#define HEARTRATE2_REG_LED_SQUENCE_REG_1                    0x20
#define HEARTRATE2_REG_LED_SQUENCE_REG_2                    0x21
#define HEARTRATE2_REG_LED_SQUENCE_REG_3                    0x22
#define HEARTRATE2_REG_LED_1_PA                             0x23
#define HEARTRATE2_REG_LED_2_PA                             0x24
#define HEARTRATE2_REG_LED_3_PA                             0x25
#define HEARTRATE2_REG_LED_PILOT_PA                         0x29
#define HEARTRATE2_REG_LED_RANGE_1                          0x2A
#define HEARTRATE2_REG_S1_HI_RES_DAC_1                      0x2C
#define HEARTRATE2_REG_S2_HI_RES_DAC_1                      0x2D
#define HEARTRATE2_REG_S3_HI_RES_DAC_1                      0x2E
#define HEARTRATE2_REG_S4_HI_RES_DAC_1                      0x2F
#define HEARTRATE2_REG_S5_HI_RES_DAC_1                      0x30
#define HEARTRATE2_REG_S6_HI_RES_DAC_1                      0x31
#define HEARTRATE2_REG_DIE_TEMP_CFG                         0x40
#define HEARTRATE2_REG_DIE_TEMP_INT                         0x41
#define HEARTRATE2_REG_DIE_TEMP_FRAC                        0x42
#define HEARTRATE2_REG_DAC_CALIBRATION_EN                   0x50
#define HEARTRATE2_REG_SHA_CMD                              0xF0
#define HEARTRATE2_REG_SHA_CFG                              0xF1
#define HEARTRATE2_REG_MEM_CTRL                             0xF2
#define HEARTRATE2_REG_MEM_INDEX                            0xF3
#define HEARTRATE2_REG_MEM_DATA                             0xF4
#define HEARTRATE2_REG_REV_ID                               0xFE
#define HEARTRATE2_REG_PART_ID                              0xFF
/** \} */

/**
 * \defgroup system_control_values System control values
 * \{
 */
#define HEARTRATE2_SYS_CTRL_SW_RESET                        0x01
#define HEARTRATE2_SYS_CTRL_SHUT_DOWN                       0x02
#define HEARTRATE2_SYS_CTRL_POWER_ON                        0x00
#define HEARTRATE2_SYS_CTRL_LOW_PWR_MODE                    0x04
#define HEARTRATE2_SYS_CTRL_SINGLE_PPG                      0x08
#define HEARTRATE2_SYS_CTRL_DUAL_PPG                        0x00
/** \} */

/**
 * \defgroup ppg_configuration_1_values PPG configuration 1 values
 * \{
 */
#define HEARTRATE2_PPG_CFG_1_ALC_ENABLE                     0x00
#define HEARTRATE2_PPG_CFG_1_ALC_DISABLE                    0x80
#define HEARTRATE2_PPG_CFG_1_ADD_OFFSET                     0x40
#define HEARTRATE2_PPG_CFG_1_NO_OFFSET                      0x00
#define HEARTRATE2_PPG_CFG_1_ADC_RANGE_4096                 0x00
#define HEARTRATE2_PPG_CFG_1_ADC_RANGE_8192                 0x04
#define HEARTRATE2_PPG_CFG_1_ADC_RANGE_16384                0x08
#define HEARTRATE2_PPG_CFG_1_ADC_RANGE_32768                0x0C
#define HEARTRATE2_PPG_CFG_1_PPG_TINT_21p3                  0x00
#define HEARTRATE2_PPG_CFG_1_PPG_TINT_35p9                  0x01
#define HEARTRATE2_PPG_CFG_1_PPG_TINT_65p2                  0x02
#define HEARTRATE2_PPG_CFG_1_PPG_TINT_123p8                 0x03
/** \} */

/**
 * \defgroup ppg_configuration_2_values PPG configuration 2 values
 * \{
 */
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_24p995_N1             0x00
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_50p027_N1             0x08
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_84p021_N1             0x10
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_99p902_N1             0x18
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_199p805_N1            0x20
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_399p610_N1            0x28
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_24p995_N2             0x30
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_50p027_N2             0x38
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_84p021_N2             0x40
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_99p902_N2             0x48
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_8p000_N1              0x50
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_16p000_N1             0x58
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_32p000_N1             0x60
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_64p000_N1             0x68
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_128p000_N1            0x70
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_256p000_N1            0x78
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_512p000_N1            0x80
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_1024p000_N1           0x88
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_2048p000_N1           0x90
#define HEARTRATE2_PPG_CFG_2_CLK_FREQ_4096p000_N1           0x98
#define HEARTRATE2_PPG_CFG_2_SMP_AVG_1                      0x00
#define HEARTRATE2_PPG_CFG_2_SMP_AVG_2                      0x01
#define HEARTRATE2_PPG_CFG_2_SMP_AVG_4                      0x02
#define HEARTRATE2_PPG_CFG_2_SMP_AVG_8                      0x03
#define HEARTRATE2_PPG_CFG_2_SMP_AVG_16                     0x04
#define HEARTRATE2_PPG_CFG_2_SMP_AVG_32                     0x05
#define HEARTRATE2_PPG_CFG_2_SMP_AVG_64                     0x06
#define HEARTRATE2_PPG_CFG_2_SMP_AVG_128                    0x07
/** \} */

/**
 * \defgroup ppg_configuration_3_values PPG configuration 3 values
 * \{
 */
#define HEARTRATE2_PPG_CFG_3_LED_SETLNG_4                   0x00
#define HEARTRATE2_PPG_CFG_3_LED_SETLNG_6                   0x40
#define HEARTRATE2_PPG_CFG_3_LED_SETLNG_8                   0x80
#define HEARTRATE2_PPG_CFG_3_LED_SETLNG_12                  0xC0
#define HEARTRATE2_PPG_CFG_3_FILTER_CDM                     0x00
#define HEARTRATE2_PPG_CFG_3_FILTER_FDM                     0x20
#define HEARTRATE2_PPG_CFG_3_BURST_RATE_8HZ                 0x00
#define HEARTRATE2_PPG_CFG_3_BURST_RATE_32HZ                0x02
#define HEARTRATE2_PPG_CFG_3_BURST_RATE_84HZ                0x04
#define HEARTRATE2_PPG_CFG_3_BURST_RATE_256HZ               0x06
#define HEARTRATE2_PPG_CFG_3_BURST_ENABLE                   0x01
#define HEARTRATE2_PPG_CFG_3_BURST_DISABLE                  0x00
/** \} */

/**
 * \defgroup photo_diode_values Photo diode values
 * \{
 */
#define HEARTRATE2_PHOTO_DIODE_BIAS1_0_65_PF                0x01
#define HEARTRATE2_PHOTO_DIODE_BIAS1_65_130_PF              0x05
#define HEARTRATE2_PHOTO_DIODE_BIAS1_130_260_PF             0x06
#define HEARTRATE2_PHOTO_DIODE_BIAS1_260_520_PF             0x07
#define HEARTRATE2_PHOTO_DIODE_BIAS2_0_65_PF                0x10
#define HEARTRATE2_PHOTO_DIODE_BIAS2_65_130_PF              0x50
#define HEARTRATE2_PHOTO_DIODE_BIAS2_130_260_PF             0x60
#define HEARTRATE2_PHOTO_DIODE_BIAS2_260_520_PF             0x70
/** \} */

/**
 * \defgroup led_range_values Led range values
 * \{
 */
#define HEARTRATE2_LED_RANGE1_LED1_CURRENT_31_MA            0x00
#define HEARTRATE2_LED_RANGE1_LED1_CURRENT_62_MA            0x01
#define HEARTRATE2_LED_RANGE1_LED1_CURRENT_93_MA            0x02
#define HEARTRATE2_LED_RANGE1_LED1_CURRENT_124_MA           0x03
#define HEARTRATE2_LED_RANGE1_LED2_CURRENT_31_MA            0x00
#define HEARTRATE2_LED_RANGE1_LED2_CURRENT_62_MA            0x04
#define HEARTRATE2_LED_RANGE1_LED2_CURRENT_93_MA            0x08
#define HEARTRATE2_LED_RANGE1_LED2_CURRENT_124_MA           0x0C
#define HEARTRATE2_LED_RANGE1_LED3_CURRENT_31_MA            0x00
#define HEARTRATE2_LED_RANGE1_LED3_CURRENT_62_MA            0x10
#define HEARTRATE2_LED_RANGE1_LED3_CURRENT_93_MA            0x20
#define HEARTRATE2_LED_RANGE1_LED3_CURRENT_124_MA           0x30
/** \} */

/**
 * \defgroup fifo_configuration_2_values Fifo configuration 2 values
 * \{
 */
#define HEARTRATE2_FIFO_CFG_2_FLUSH_FIFO                    0x10
#define HEARTRATE2_FIFO_CFG_2_FIFO_READ_DATA_CLR            0x08
#define HEARTRATE2_FIFO_CFG_2_FIFO_STAT_DATA_CLR            0x00
#define HEARTRATE2_FIFO_CFG_2_FULL_TYPE_RPT                 0x00
#define HEARTRATE2_FIFO_CFG_2_FULL_TYPE_ONCE                0x04
#define HEARTRATE2_FIFO_CFG_2_FIFO_ROLL_OVER                0x02
#define HEARTRATE2_FIFO_CFG_2_FIFO_STOP                     0x00
/** \} */

/**
 * \defgroup interrupt_values Interrupt values
 * \{
 */
#define HEARTRATE2_INT_1_FULL                               0x80
#define HEARTRATE2_INT_1_NOT_FULL                           0x00
#define HEARTRATE2_INT_1_DATA_RDY                           0x40
#define HEARTRATE2_INT_1_DATA_NOT_RDY                       0x00
#define HEARTRATE2_INT_1_ALC_OVERFLOW                       0x20
#define HEARTRATE2_INT_1_ALC_NORMAL                         0x00
#define HEARTRATE2_INT_1_PROXIMITY_INT                      0x10
#define HEARTRATE2_INT_1_PROXIMITY_NORMAL                   0x00
#define HEARTRATE2_INT_1_LED_COMPLIANT                      0x08
#define HEARTRATE2_INT_1_LED_NOT_COMPLIANT                  0x00
#define HEARTRATE2_INT_1_DIE_TEMP_RDY                       0x04
#define HEARTRATE2_INT_1_DIE_TEMP_NOT_RDY                   0x00
#define HEARTRATE2_INT_1_PWR_RDY                            0x01
#define HEARTRATE2_INT_1_PWR_NOT_RDY                        0x00
/** \} */

/**
 * \defgroup interrupt_values Interrupt values
 * \{
 */
#define HEARTRATE2_INT_1_FULL                               0x80
#define HEARTRATE2_INT_1_NOT_FULL                           0x00
#define HEARTRATE2_INT_1_DATA_RDY                           0x40
#define HEARTRATE2_INT_1_DATA_NOT_RDY                       0x00
#define HEARTRATE2_INT_1_ALC_OVERFLOW                       0x20
#define HEARTRATE2_INT_1_ALC_NORMAL                         0x00
#define HEARTRATE2_INT_1_PROXIMITY_INT                      0x10
#define HEARTRATE2_INT_1_PROXIMITY_NORMAL                   0x00
#define HEARTRATE2_INT_1_LED_COMPLIANT                      0x08
#define HEARTRATE2_INT_1_LED_NOT_COMPLIANT                  0x00
#define HEARTRATE2_INT_1_DIE_TEMP_RDY                       0x04
#define HEARTRATE2_INT_1_DIE_TEMP_NOT_RDY                   0x00
#define HEARTRATE2_INT_1_PWR_RDY                            0x01
#define HEARTRATE2_INT_1_PWR_NOT_RDY                        0x00
#define HEARTRATE2_INT_2_SHA_AUTHENTICATION_DONE            0x01
#define HEARTRATE2_INT_2_SHA_AUTHENTICATION_NOT_DONE        0x00
/** \} */

/**
 * \defgroup fifo_tag_stucture_values Fifo tag stucture values
 * \{
 */
#define HEARTRATE2_FIFO_TAG_PPG1_LEDC1                      0x01
#define HEARTRATE2_FIFO_TAG_PPG1_LEDC2                      0x02
#define HEARTRATE2_FIFO_TAG_PPG1_LEDC3                      0x03
#define HEARTRATE2_FIFO_TAG_PPG1_LEDC4                      0x04
#define HEARTRATE2_FIFO_TAG_PPG1_LEDC5                      0x05
#define HEARTRATE2_FIFO_TAG_PPG1_LEDC6                      0x06
#define HEARTRATE2_FIFO_TAG_PPF1_LEDC1                      0x0D
#define HEARTRATE2_FIFO_TAG_PPF1_LEDC2                      0x0E
#define HEARTRATE2_FIFO_TAG_PPF1_LEDC3                      0x0F
#define HEARTRATE2_FIFO_TAG_PROX1                           0x19
#define HEARTRATE2_FIFO_TAG_SUB_DAC_UPDATE                  0x1D
#define HEARTRATE2_FIFO_TAG_INVALID_DATA                    0x1E
#define HEARTRATE2_FIFO_TAG_TIME_STAMP                      0x1F
/** \} */

/**
 * \defgroup led_sequence_stucture_values Led sequence structure values
 * \{
 */
#define HEARTRATE2_LEDSQ_GREEN                              0x1
#define HEARTRATE2_LEDSQ_IR                                 0x2
#define HEARTRATE2_LEDSQ_RED                                0x3
#define HEARTRATE2_LEDSQ_PILOT_LED1                         0x8
#define HEARTRATE2_LEDSQ_DIRECT_AMBIENT                     0x9
#define HEARTRATE2_LEDSQ_OFF                                0x0
/** \} */

/**
 * \defgroup device_status_values Device status values
 * \{
 */
#define HEARTRATE2_DEV_ID                                   0x36
#define HEARTRATE2_ERROR                                    0xEE
#define HEARTRATE2_OK                                         0xFF
/** \} */

/**
 * \defgroup int_stucture_values Int structure values
 * \{
 */
#define HEARTRATE2_INT_ENABLE                               0x01
#define HEARTRATE2_INT_DISABLE                              0x00
/** \} */

/**
 * \defgroup ppg_configuration_alc PPG configuration Alc
 * \{
 */
#define HEARTRATE2_PPG_CFG_ALC_EN                           0x01
#define HEARTRATE2_PPG_CFG_ALC_DS                           0x00
/** \} */

/**
 * \defgroup ppg_configuration_offset PPG configuration Offset
 * \{
 */
#define HEARTRATE2_PPG_CFG_OFFSET_ADD                       0x01
#define HEARTRATE2_PPG_CFG_OFFSET_NO                        0x00
/** \} */

/**
 * \defgroup ppg_configuration_tint PPG configuration Tint
 * \{
 */
#define HEARTRATE2_PPG_CFG_TINT_14p8_US                     0x00
#define HEARTRATE2_PPG_CFG_TINT_29p4_US                     0x01
#define HEARTRATE2_PPG_CFG_TINT_58p7_US                     0x02
#define HEARTRATE2_PPG_CFG_TINT_117p3_US                    0x03
/** \} */

/**
 * \defgroup ppg_configuration_led_range PPG configuration Led Range
 * \{
 */
#define HEARTRATE2_PPG_CFG_LED_RANGE_4k                     0x00
#define HEARTRATE2_PPG_CFG_LED_RANGE_8k                     0x01
#define HEARTRATE2_PPG_CFG_LED_RANGE_16k                    0x02
#define HEARTRATE2_PPG_CFG_LED_RANGE_32k                    0x03
/** \} */

/**
 * \defgroup ppg_configuration_smp_rate_p1 PPG configuration Smp Rate P1
 * \{
 */
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_24sps                0x00
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_50sps                0x01
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_84sps                0x02
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_99sps                0x03
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_199sps               0x04
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_399sps               0x05
#define HEARTRATE2_PPG_CFG_SMP_RATE_P2_24sps                0x06
#define HEARTRATE2_PPG_CFG_SMP_RATE_P2_50sps                0x07
#define HEARTRATE2_PPG_CFG_SMP_RATE_P2_84sps                0x08
#define HEARTRATE2_PPG_CFG_SMP_RATE_P2_99sps                0x09
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_8sps                 0x0A
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_16sps                0x0B
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_32sps                0x0C
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_64sps                0x0D
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_128sps               0x0E
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_256sps               0x0F
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_512sps               0x10
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_1024sps              0x11
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_2048sps              0x12
#define HEARTRATE2_PPG_CFG_SMP_RATE_P1_4096sps              0x13
/** \} */

/**
 * \defgroup ppg_configuration_smp_avg PPG configuration Smp Avg
 * \{
 */
#define HEARTRATE2_PPG_CFG_SMP_AVG_1                        0x00
#define HEARTRATE2_PPG_CFG_SMP_AVG_2                        0x01
#define HEARTRATE2_PPG_CFG_SMP_AVG_4                        0x02
#define HEARTRATE2_PPG_CFG_SMP_AVG_8                        0x03
#define HEARTRATE2_PPG_CFG_SMP_AVG_16                       0x04
#define HEARTRATE2_PPG_CFG_SMP_AVG_32                       0x05
#define HEARTRATE2_PPG_CFG_SMP_AVG_64                       0x06
#define HEARTRATE2_PPG_CFG_SMP_AVG_128                      0x07
/** \} */

/**
 * \defgroup led_range_current Led Range Current
 * \{
 */
#define HEARTRATE2_LED_RANGE_CURRENT_31_MA                  0x00
#define HEARTRATE2_LED_RANGE_CURRENT_62_MA                  0x01
#define HEARTRATE2_LED_RANGE_CURRENT_93_MA                  0x02
#define HEARTRATE2_LED_RANGE_CURRENT_124_MA                 0x03
/** \} */

/**
 * \defgroup conf_macro Conf Macro
 * \{
 */
#define HEARTRATE2_CONFIG_GREEN                             0xAA
#define HEARTRATE2_CONFIG_IR                                0xBB
#define HEARTRATE2_CONFIG_RED                               0xCC
/** \} */

/**
 * \defgroup pin_state Pin state
 * \{
 */
#define HEARTRATE2_PIN_HIGH                                 1
#define HEARTRATE2_PIN_LOW                                  0
/** \} */

/**
 * \defgroup temp_res_and_mask Temp Res and Mask
 * \{
 */
#define HEARTRATE2_TEMPERATURE_RESOLUTION                       0.0625f
#define HEARTRATE2_TEMPERATURE_MASK                             0x0F
/** \} */

/**
 * \defgroup data_mask_and_res_and_tag_mask Data Mask and Res and Tag Mask
 * \{
 */
#define HEARTRATE2_FIFO_DATA_MASK                               0x07FFFF
#define HEARTRATE2_FIFO_RES                                     19
#define HEARTRATE2_FIFO_TAG_MASK                                0x1F
/** \} */

/**
 * \defgroup led_sequence_shift Led sequence shift
 * \{
 */
#define HEARTRATE2_LEDSQ_SHIFT                                  4
/** \} */

/**
 * \defgroup int_shift_data_and_int_mask Int shift data and int mask
 * \{
 */
#define HEARTRATE2_INT_SHIFT_FULL                               7
#define HEARTRATE2_INT_SHIFT_DATA_RDY                           6
#define HEARTRATE2_INT_SHIFT_ALC_OVF                            5
#define HEARTRATE2_INT_SHIFT_PROXY                              4
#define HEARTRATE2_INT_SHIFT_LED_COMPLIANT                      3
#define HEARTRATE2_INT_SHIFT_DIE_TEMEP                          2
#define HEARTRATE2_INT_SHIFT_PWR_RDY                            0
#define HEARTRATE2_INT_SHIFT_SHA                                0
#define HEARTRATE2_INT_MASK                                     0x01
/** \} */

/**
 * \defgroup cfg_shift_data Cfg shift data
 * \{
 */
#define HEARTRATE2_PPG_CFG_ALC                                  7
#define HEARTRATE2_PPG_CFG_OFFSET                               6
#define HEARTRATE2_PPG_CFG_ADC_RANGE                            2
#define HEARTRATE2_PPG_CFG_TINT                                 0
#define HEARTRATE2_PPG_CFG_SMP_RATE                             3
#define HEARTRATE2_PPG_CFG_SMP_AVG                              0
/** \} */

/**
 * \defgroup led_range_shift_data Led range shift data
 * \{
 */
#define HEARTRATE2_LED_RANGE_SHIFT_GREEN                        0
#define HEARTRATE2_LED_RANGE_SHIFT_IR                           2
#define HEARTRATE2_LED_RANGE_SHIFT_RED                          4
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Structure for reading fifo data
 */
typedef struct
{
  uint32_t data_val;
  uint8_t  tag;
} heartrate2_fifo_data_t;

/**
 * @brief Structure configurating led sequence
 */
typedef struct
{
  uint8_t ledsq1;
  uint8_t ledsq2;
  uint8_t ledsq3;
  uint8_t ledsq4;
  uint8_t ledsq5;
  uint8_t ledsq6;
} heartrate2_ledsq_cfg_t;

/**
 * @brief Structure led brightness
 */
typedef struct
{
  uint8_t green;
  uint8_t ir;
  uint8_t red;
} heartrate2_ledpa_t;

/**
 * @brief Structure setting led current range
 */
typedef struct
{
  uint8_t green;
  uint8_t ir;
  uint8_t red;
} heartrate2_led_range_curr_t;

/**
 * @brief Structure configurating ppg
 */
typedef struct
{
  uint8_t alc;
  uint8_t offset;
  uint8_t ppg_tint;
  uint8_t led_range;
  uint8_t smp_rate;
  uint8_t smp_freq;
} heartrate2_ppg_cfg_t;

/**
 * @brief Structure for interrupt status
 */
typedef struct
{
  uint8_t full_fifo;
  uint8_t data_rdy;
  uint8_t alc_ovf;
  uint8_t proxy;
  uint8_t led_compliant;
  uint8_t die_temp;
  uint8_t pwr_rdy;
  uint8_t sha;
} heartrate2_int_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t cs;

    // Input pins 

    digital_in_t an;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} heartrate2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t cs;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} heartrate2_cfg_t;

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
void heartrate2_cfg_setup ( heartrate2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HEARTRATE2_RETVAL heartrate2_init ( heartrate2_t *ctx, heartrate2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx       Click object.
 * @param cfg_led   select one of led macros to enable and 
 *                  set configuration for selected led
 *                  ( HEARTRATE2_CONFIG_GREEN or HEARTRATE2_CONFIG_IR or
 *                    HEARTRATE2_CONFIG_RED )
 *
 * @description This function executes default configuration for HeartRate2 click.
 */
void heartrate2_default_cfg ( heartrate2_t *ctx, uint8_t cfg_led );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg_adr      Register address.
 * @param data_buf     Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void heartrate2_generic_write ( heartrate2_t *ctx, uint8_t reg_adr, uint8_t write_data );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg_adr      Register address.
 *
 * @description This function reads data from the desired register.
 */
uint8_t heartrate2_generic_read ( heartrate2_t *ctx, uint8_t reg_adr );

/**
 * @brief Function for reading data buffer from registar.
 *
 * @param ctx          Click object.
 * @param reg_adr      Register address.
 * @param data_buf     Read buffer to store data.
 * @param len          Size of read buffer.
 *
 * @description This function reads data buffer from the desired register.
 */
void heartrate2_read_buf ( heartrate2_t *ctx, uint8_t reg_adr, uint8_t *read_buf, uint8_t buf_size );

/**
 * @brief Generic function for reading data from fifo registar.
 *
 * @param ctx       Click object.
 * @param fifo      Pointer to fifo register.
 *
 * @description This function reads data buffer from the desired register.
 */
void heartrate2_read_fifo ( heartrate2_t *ctx, heartrate2_fifo_data_t *fifo );

/**
 * @brief Function for reading temperature of device.
 *
 * @param ctx       Click object.
 *
 * @description This function reads temperature of device.
 * 
 * @note You should enable die temperature interrupt status, 
 *       and you should turn off leds to get right temperature.
 */
float heartrate2_read_temp ( heartrate2_t *ctx );

/**
 * @brief Function for restarting device.
 *
 * @param ctx       Click object.
 *
 * @description This function restarts device.
 */
void heartrate2_soft_reset ( heartrate2_t *ctx );

/**
 * @brief Function for configurating ppg registers.
 *
 * @param ctx       Click object.
 * @param ppg_cfg   Struct with stored configuration.
 *
 * @description This function configure ppg registars.
 * 
 * @note Error can occure if you input values are wrong.
 */
uint8_t heartrate2_ppg_config ( heartrate2_t *ctx, heartrate2_ppg_cfg_t *ppg_cfg );

/**
 * @brief Function for configurating led pa registers.
 *
 * @param ctx     Click object.
 * @param ledpa   Struct with stored configuration.
 *
 * @description This function configure led pa registars.
 */
void heartrate2_ledpa_config ( heartrate2_t *ctx, heartrate2_ledpa_t *ledpa );

/**
 * @brief Function for configurating led current range registers.
 *
 * @param ctx         Click object.
 * @param led_range   Struct with stored configuration.
 *
 * @description This function configure led current range registars.
 * 
 * @note Error can occure if you input values are wrong.
 */
uint8_t heartrate2_led_range_curr_config ( heartrate2_t *ctx, heartrate2_led_range_curr_t *led_range );

/**
 * @brief Function for configurating led sequence registers.
 *
 * @param ctx     Click object.
 * @param ledsq   Struct with stored configuration.
 *
 * @description This function configure led sequence registars.
 * 
 * @note Error can occure if you input values are wrong.
 */
uint8_t heartrate2_led_sequence_config ( heartrate2_t *ctx, heartrate2_ledsq_cfg_t *ledsq );

/**
 * @brief Function for configurating interrupt registers.
 *
 * @param ctx         Click object.
 * @param int_ctrl    Struct with stored configuration.
 *
 * @description This function configure interrupt registars.
 * 
 * @note Error can occure if you input values are wrong.
 */
uint8_t heartrate2_int_control ( heartrate2_t *ctx, heartrate2_int_t *int_ctrl );

/**
 * @brief Function for reading interrupt status.
 *
 * @param ctx           Click object.
 * @param int_status    Struct with stored configuration.
 *
 * @description This function reads interrupt status.
 */
void heartrate2_int_status ( heartrate2_t *ctx, heartrate2_int_t *int_status );

/**
 * @brief Function for reading int pin status.
 *
 * @param ctx           Click object.
 *
 * @description This function reads int pin status.
 */
uint8_t heartrate2_get_int ( heartrate2_t *ctx );

/**
 * @brief Function for reading gp pin status.
 *
 * @param ctx           Click object.
 *
 * @description This function reads gp pin status.
 */
uint8_t heartrate2_get_gp ( heartrate2_t *ctx );

/**
 * @brief Function for setting en pin status.
 *
 * @param ctx           Click object.
 *
 * @description This function settings en pin status.
 */
void heartrate2_set_en ( heartrate2_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _HEARTRATE2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
