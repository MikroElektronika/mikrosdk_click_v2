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
 * @file isoadc6.h
 * @brief This file contains API for ISO ADC 6 Click Driver.
 */

#ifndef ISOADC6_H
#define ISOADC6_H

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
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup isoadc6 ISO ADC 6 Click Driver
 * @brief API for configuring and manipulating ISO ADC 6 Click driver.
 * @{
 */

/**
 * @defgroup isoadc6_reg ISO ADC 6 Registers List
 * @brief List of registers of ISO ADC 6 Click driver.
 */

/**
 * @addtogroup isoadc6_reg
 * @{
 */

/**
 * @brief ISO ADC 6 description register.
 * @details Specified register for description of ISO ADC 6 Click driver.
 */
#define ISOADC6_REG_COMM_STATUS                     0x00
#define ISOADC6_REG_CONTROL                         0x01
#define ISOADC6_REG_DATA                            0x02
#define ISOADC6_REG_IO_CONTROL_1                    0x03
#define ISOADC6_REG_IO_CONTROL_2                    0x04
#define ISOADC6_REG_ID                              0x05
#define ISOADC6_REG_ERR_STATUS                      0x06
#define ISOADC6_REG_ERR_EN                          0x07
#define ISOADC6_REG_MCLK_CNT                        0x08
#define ISOADC6_REG_CHANNEL_0                       0x09
#define ISOADC6_REG_CHANNEL_1                       0x0A
#define ISOADC6_REG_CHANNEL_2                       0x0B
#define ISOADC6_REG_CHANNEL_3                       0x0C
#define ISOADC6_REG_CHANNEL_4                       0x0D
#define ISOADC6_REG_CHANNEL_5                       0x0E
#define ISOADC6_REG_CHANNEL_6                       0x0F
#define ISOADC6_REG_CHANNEL_7                       0x10
#define ISOADC6_REG_CHANNEL_8                       0x11
#define ISOADC6_REG_CHANNEL_9                       0x12
#define ISOADC6_REG_CHANNEL_10                      0x13
#define ISOADC6_REG_CHANNEL_11                      0x14
#define ISOADC6_REG_CHANNEL_12                      0x15
#define ISOADC6_REG_CHANNEL_13                      0x16
#define ISOADC6_REG_CHANNEL_14                      0x17
#define ISOADC6_REG_CHANNEL_15                      0x18
#define ISOADC6_REG_CONFIG_0                        0x19
#define ISOADC6_REG_CONFIG_1                        0x1A
#define ISOADC6_REG_CONFIG_2                        0x1B
#define ISOADC6_REG_CONFIG_3                        0x1C
#define ISOADC6_REG_CONFIG_4                        0x1D
#define ISOADC6_REG_CONFIG_5                        0x1E
#define ISOADC6_REG_CONFIG_6                        0x1F
#define ISOADC6_REG_CONFIG_7                        0x20
#define ISOADC6_REG_FILTER_0                        0x21
#define ISOADC6_REG_FILTER_1                        0x22
#define ISOADC6_REG_FILTER_2                        0x23
#define ISOADC6_REG_FILTER_3                        0x24
#define ISOADC6_REG_FILTER_4                        0x25
#define ISOADC6_REG_FILTER_5                        0x26
#define ISOADC6_REG_FILTER_6                        0x27
#define ISOADC6_REG_FILTER_7                        0x28
#define ISOADC6_REG_OFFSET_0                        0x29
#define ISOADC6_REG_OFFSET_1                        0x2A
#define ISOADC6_REG_OFFSET_2                        0x2B
#define ISOADC6_REG_OFFSET_3                        0x2C
#define ISOADC6_REG_OFFSET_4                        0x2D
#define ISOADC6_REG_OFFSET_5                        0x2E
#define ISOADC6_REG_OFFSET_6                        0x2F
#define ISOADC6_REG_OFFSET_7                        0x30
#define ISOADC6_REG_GAIN_0                          0x31
#define ISOADC6_REG_GAIN_1                          0x32
#define ISOADC6_REG_GAIN_2                          0x33
#define ISOADC6_REG_GAIN_3                          0x34
#define ISOADC6_REG_GAIN_4                          0x35
#define ISOADC6_REG_GAIN_5                          0x36
#define ISOADC6_REG_GAIN_6                          0x37
#define ISOADC6_REG_GAIN_7                          0x38

/*! @} */ // isoadc6_reg

/**
 * @addtogroup isoadc6_cmd
 * @{
 */

/**
 * @brief ISO ADC 6 description command.
 * @details Specified commands for description of ISO ADC 6 Click driver.
 */
#define ISOADC6_CMD_SPI_WRITE                       0x00
#define ISOADC6_CMD_SPI_READ                        0x40
#define ISOADC6_CMD_SPI_WRITE_DIS                   0x80

/*! @} */ // isoadc6_cmd

/**
 * @defgroup isoadc6_set ISO ADC 6 Registers Settings
 * @brief Settings for registers of ISO ADC 6 Click driver.
 */

/**
 * @addtogroup isoadc6_set
 * @{
 */

/**
 * @brief ISO ADC 6 channel selection.
 * @details Specified channel selection of ISO ADC 6 Click driver.
 */
#define ISOADC6_SEL_CH_0                            0
#define ISOADC6_SEL_CH_1                            1
#define ISOADC6_SEL_CH_2                            2
#define ISOADC6_SEL_CH_3                            3
#define ISOADC6_SEL_CH_4                            4
#define ISOADC6_SEL_CH_5                            5
#define ISOADC6_SEL_CH_6                            6
#define ISOADC6_SEL_CH_7                            7
#define ISOADC6_SEL_CH_8                            8
#define ISOADC6_SEL_CH_9                            9
#define ISOADC6_SEL_CH_10                           10
#define ISOADC6_SEL_CH_11                           11
#define ISOADC6_SEL_CH_12                           12
#define ISOADC6_SEL_CH_13                           13
#define ISOADC6_SEL_CH_14                           14
#define ISOADC6_SEL_CH_15                           15

/**
 * @brief ISO ADC 6 data ready status.
 * @details Data ready status of ISO ADC 6 Click driver.
 */
#define ISOADC6_NEW_DATA_BIT_MASK                   0x80
#define ISOADC6_NEW_DATA_IS_READY                   0x00
#define ISOADC6_NEW_DATA_NOT_READY                  0x01

/**
 * @brief ISO ADC 6 device ID values.
 * @details Device ID values of ISO ADC 6 Click driver.
 */
#define ISOADC6_SIL_REV_BIT_MASK                    0x0F
#define ISOADC6_DEV_ID_REV_BIT_MASK                 0xF0
#define ISOADC6_DEVICE_ID                           0x01
#define ISOADC6_SILICON_REVISION                    0x04

/**
 * @brief ISO ADC 6 register length data value.
 * @details Register length data value of ISO ADC 6 Click driver.
 */
#define ISOADC6_LEN_REG_ERROR                       0
#define ISOADC6_LEN_REG_BYTE                        1
#define ISOADC6_LEN_REG_WORD                        2
#define ISOADC6_LEN_REG_DWORD                       3

/**
 * @brief ISO ADC 6 channel register control setting.
 * @details Channel register control setting of ISO ADC 6 Click driver.
 */
#define ISOADC6_CTRL_RDY_LOW_PWR_MODE_RDY_EN        0x00000000ul
#define ISOADC6_CTRL_RDY_DELAY_100NS                0x00001000ul
#define ISOADC6_CTRL_CONT_CONV_MODE                 0x00000800ul
#define ISOADC6_CTRL_DATA_STATUS_EN                 0x00000400ul
#define ISOADC6_CTRL_DOUT_PIN_EN                    0x00000200ul
#define ISOADC6_CTRL_INT_REF_VVTG_EN                0x00000100ul
#define ISOADC6_CTRL_MID_POWER_MODE                 0x00000040ul
#define ISOADC6_CTRL_FULL_POWER_MODE                0x00000080ul
#define ISOADC6_CTRL_SINGLE_CONV_MODE               0x00000004ul
#define ISOADC6_CTRL_STANDBY_MODE                   0x00000008ul
#define ISOADC6_CTRL_SINGLE_PWR_DOWN_MODE           0x0000000Cul
#define ISOADC6_CTRL_IDLE_MODE                      0x00000010ul
#define ISOADC6_CTRL_MODE_MASK                      0x0000003Cul
#define ISOADC6_CTRL_INT_ZERO_SCALE_OFFSET_CALIB    0x00000014ul
#define ISOADC6_CTRL_INT_FULL_SCALE_GAIN_CALIB      0x00000018ul
#define ISOADC6_CTRL_SYS_ZERO_SCALE_OFFSET_CALIB    0x0000001Cul
#define ISOADC6_CTRL_SYS_FULL_SCALE_GAIN_CALIB      0x00000020ul

/**
 * @brief ISO ADC 6 channel configuration data values.
 * @details Channel configuration data values of ISO ADC 6 Click driver.
 */
#define ISOADC6_IO_CON1_DOUT_PINS_DIS               0x00000000ul
#define ISOADC6_IO_CON1_SET_DOUT_PIN_P4             0x00800000ul
#define ISOADC6_IO_CON1_SET_DOUT_PIN_P3             0x00400000ul
#define ISOADC6_IO_CON1_SET_DOUT_PIN_P2             0x00200000ul
#define ISOADC6_IO_CON1_SET_DOUT_PIN_P1             0x00100000ul
#define ISOADC6_IO_CON1_DOUT_PIN_P4_EN              0x00080000ul
#define ISOADC6_IO_CON1_DOUT_PIN_P3_EN              0x00040000ul
#define ISOADC6_IO_CON1_DOUT_PIN_P2_EN              0x00020000ul
#define ISOADC6_IO_CON1_DOUT_PIN_P1_EN              0x00010000ul
#define ISOADC6_IO_CON1_BRIGDE_PWR_DOWN_EN          0x00008000ul
#define ISOADC6_IO_CON1_IOUT1_MIKRO_A_50            0x00000800ul
#define ISOADC6_IO_CON1_IOUT1_MIKRO_A_100           0x00001000ul
#define ISOADC6_IO_CON1_IOUT1_MIKRO_A_250           0x00001800ul
#define ISOADC6_IO_CON1_IOUT1_MIKRO_A_500           0x00002000ul
#define ISOADC6_IO_CON1_IOUT1_MIKRO_A_750           0x00002800ul
#define ISOADC6_IO_CON1_IOUT1_MIKRO_A_1000          0x00003000ul
#define ISOADC6_IO_CON1_IOUT0_MIKRO_A_50            0x00000100ul
#define ISOADC6_IO_CON1_IOUT0_MIKRO_A_100           0x00000200ul
#define ISOADC6_IO_CON1_IOUT0_MIKRO_A_250           0x00000300ul
#define ISOADC6_IO_CON1_IOUT0_MIKRO_A_500           0x00000400ul
#define ISOADC6_IO_CON1_IOUT0_MIKRO_A_750           0x00000500ul
#define ISOADC6_IO_CON1_IOUT0_MIKRO_A_1000          0x00000600ul
#define ISOADC6_IO_CON1_IOUT1_AIN0_PIN_ON           0x00000000ul
#define ISOADC6_IO_CON1_IOUT1_AIN1_PIN_ON           0x00000010ul
#define ISOADC6_IO_CON1_IOUT1_AIN2_PIN_ON           0x00000020ul
#define ISOADC6_IO_CON1_IOUT1_AIN3_PIN_ON           0x00000030ul
#define ISOADC6_IO_CON1_IOUT1_AIN4_PIN_ON           0x00000040ul
#define ISOADC6_IO_CON1_IOUT1_AIN5_PIN_ON           0x00000050ul
#define ISOADC6_IO_CON1_IOUT1_AIN6_PIN_ON           0x00000060ul
#define ISOADC6_IO_CON1_IOUT1_AIN7_PIN_ON           0x00000070ul
#define ISOADC6_IO_CON1_IOUT1_AIN8_PIN_ON           0x00000080ul
#define ISOADC6_IO_CON1_IOUT1_AIN9_PIN_ON           0x00000090ul
#define ISOADC6_IO_CON1_IOUT1_AIN10_PIN_ON          0x000000A0ul
#define ISOADC6_IO_CON1_IOUT1_AIN11_PIN_ON          0x000000B0ul
#define ISOADC6_IO_CON1_IOUT1_AIN12_PIN_ON          0x000000C0ul
#define ISOADC6_IO_CON1_IOUT1_AIN13_PIN_ON          0x000000D0ul
#define ISOADC6_IO_CON1_IOUT1_AIN14_PIN_ON          0x000000E0ul
#define ISOADC6_IO_CON1_IOUT1_AIN15_PIN_ON          0x000000F0ul
#define ISOADC6_IO_CON1_IOUT0_AIN0_PIN_ON           0x00000000ul
#define ISOADC6_IO_CON1_IOUT0_AIN1_PIN_ON           0x00000001ul
#define ISOADC6_IO_CON1_IOUT0_AIN2_PIN_ON           0x00000002ul
#define ISOADC6_IO_CON1_IOUT0_AIN3_PIN_ON           0x00000003ul
#define ISOADC6_IO_CON1_IOUT0_AIN4_PIN_ON           0x00000004ul
#define ISOADC6_IO_CON1_IOUT0_AIN5_PIN_ON           0x00000005ul
#define ISOADC6_IO_CON1_IOUT0_AIN6_PIN_ON           0x00000006ul
#define ISOADC6_IO_CON1_IOUT0_AIN7_PIN_ON           0x00000007ul
#define ISOADC6_IO_CON1_IOUT0_AIN8_PIN_ON           0x00000008ul
#define ISOADC6_IO_CON1_IOUT0_AIN9_PIN_ON           0x00000009ul
#define ISOADC6_IO_CON1_IOUT0_AIN10_PIN_ON          0x0000000Aul
#define ISOADC6_IO_CON1_IOUT0_AIN11_PIN_ON          0x0000000Bul
#define ISOADC6_IO_CON1_IOUT0_AIN12_PIN_ON          0x0000000Cul
#define ISOADC6_IO_CON1_IOUT0_AIN13_PIN_ON          0x0000000Dul
#define ISOADC6_IO_CON1_IOUT0_AIN14_PIN_ON          0x0000000Eul
#define ISOADC6_IO_CON1_IOUT0_AIN15_PIN_ON          0x0000000Ful

/**
 * @brief ISO ADC 6 I/O control 2 setting.
 * @details I/O control 2 setting of ISO ADC 6 Click driver.
 */
#define ISOADC6_IO_CON2_VBIAS_DISABLE               0x0000u
#define ISOADC6_IO_CON2_VBIAS_AIN0_CH_EN_ON         0x0001u
#define ISOADC6_IO_CON2_VBIAS_AIN1_CH_EN_ON         0x0002u
#define ISOADC6_IO_CON2_VBIAS_AIN2_CH_EN_ON         0x0004u
#define ISOADC6_IO_CON2_VBIAS_AIN3_CH_EN_ON         0x0008u
#define ISOADC6_IO_CON2_VBIAS_AIN4_CH_EN_ON         0x0010u
#define ISOADC6_IO_CON2_VBIAS_AIN5_CH_EN_ON         0x0020u
#define ISOADC6_IO_CON2_VBIAS_AIN6_CH_EN_ON         0x0040u
#define ISOADC6_IO_CON2_VBIAS_AIN7_CH_EN_ON         0x0080u
#define ISOADC6_IO_CON2_VBIAS_AIN8_CH_EN_ON         0x0100u
#define ISOADC6_IO_CON2_VBIAS_AIN9_CH_EN_ON         0x0200u
#define ISOADC6_IO_CON2_VBIAS_AIN10_CH_EN_ON        0x0400u
#define ISOADC6_IO_CON2_VBIAS_AIN11_CH_EN_ON        0x0800u
#define ISOADC6_IO_CON2_VBIAS_AIN12_CH_EN_ON        0x1000u
#define ISOADC6_IO_CON2_VBIAS_AIN13_CH_EN_ON        0x2000u
#define ISOADC6_IO_CON2_VBIAS_AIN14_CH_EN_ON        0x4000u
#define ISOADC6_IO_CON2_VBIAS_AIN15_CH_EN_ON        0x8000u

/**
 * @brief ISO ADC 6 I/O control 2 setting.
 * @details I/O control 2 setting of ISO ADC 6 Click driver.
 */
#define ISOADC6_CHANNEL_DISABLE                     0x0000u
#define ISOADC6_CHANNEL_ENABLE                      0x8000u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN0              0x0000u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN1              0x0020u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN2              0x0040u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN3              0x0060u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN4              0x0080u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN5              0x00A0u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN6              0x00C0u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN7              0x00E0u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN8              0x0100u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN9              0x0120u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN10             0x0140u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN11             0x0160u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN12             0x0180u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN13             0x01A0u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN14             0x01C0u
#define ISOADC6_CHANNEL_POS_AN_IN_AIN15             0x01E0u
#define ISOADC6_CHANNEL_POS_TEMP_SENSOR             0x0200u
#define ISOADC6_CHANNEL_POS_AVSS                    0x0220u
#define ISOADC6_CHANNEL_POS_INT_REF                 0x0240u
#define ISOADC6_CHANNEL_POS_DGND                    0x0260u
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN0              0x0000u
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN1              0x0001u
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN2              0x0002u
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN3              0x0003u
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN4              0x0004u
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN5              0x0005u
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN6              0x0006u
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN7              0x0007u
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN8              0x0008u
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN9              0x0009u
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN10             0x000Au
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN11             0x000Bu
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN12             0x000Cu
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN13             0x000Du
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN14             0x000Eu
#define ISOADC6_CHANNEL_NEG_AN_IN_AIN15             0x000Fu
#define ISOADC6_CHANNEL_NEG_TEMP_SENSOR             0x0010u
#define ISOADC6_CHANNEL_NEG_AVSS                    0x0011u
#define ISOADC6_CHANNEL_NEG_INT_REF                 0x0012u
#define ISOADC6_CHANNEL_NEG_DGND                    0x0013u

/**
 * @brief ISO ADC 6 error register data values.
 * @details Error register data values of ISO ADC 6 Click driver.
 */
#define ISOADC6_ALL_ERROR_FLAG_DIS                  0x00000000ul
#define ISOADC6MASTER_CLK_CNT_EN                    0x00400000ul
#define ISOADC6LDO_CAP_TEST_CHECK_EN                0x00200000ul
#define ISOADC6ANALOG_LDO_CALIB_CHECK_EN            0x00080000ul
#define ISOADC6DIGITAL_LDO_CALIB_CHECK_EN           0x00100000ul
#define ISOADC6LDO_CHECK_DIS                        0x00180000ul
#define ISOADC6_CALIB_FAIL_CHECK_EN                 0x00040000ul
#define ISOADC6_CONV_FAIL_CHECK_EN                  0x00020000ul
#define ISOADC6_SAT_CHECK_EN                        0x00010000ul
#define ISOADC6_OVERVTG_MON_ON_AINP_CH_EN           0x00008000ul
#define ISOADC6_UNDERVTG_MON_ON_AINP_CH_EN          0x00004000ul
#define ISOADC6_OVERVTG_MON_ON_AINM_CH_EN           0x00002000ul
#define ISOADC6_UNDERVTG_MON_ON_AINM_CH_EN          0x00001000ul
#define ISOADC6_EXT_REF_DET_ERROR                   0x00000800ul
#define ISOADC6_DIG_LDO_TEST_MECH_CHECK             0x00000400ul
#define ISOADC6_DIG_LDO_VTG_MONITORING              0x00000200ul
#define ISOADC6_AN_LDO_TEST_MECH_CHECK              0x00000100ul
#define ISOADC6_AN_LDO_VTG_MON                      0x00000080ul
#define ISOADC6_SPI_IGNORE_ERROR                    0x00000040ul
#define ISOADC6_SPI_SCLK_CNT_ERROR_CHECK            0x00000020ul
#define ISOADC6_SPI_READ_ERROR_CHECK                0x00000010ul
#define ISOADC6_SPI_WRITE_ERROR_CHECK               0x00000008ul
#define ISOADC6_SPI_CRC_CHECK                       0x00000004ul
#define ISOADC6_SPI_CRC_CALC_PERF_ON_MEMORY         0x00000002ul
#define ISOADC6_GAIN_COEFF                          0x00400000ul

/**
 * @brief ISO ADC 6 config register data values.
 * @details Config register data values of ISO ADC 6 Click driver.
 */
#define ISOADC6_CFG_UNP_OP_BUFF_BOUT_DIS            0x0000u
#define ISOADC6_CFG_BIP_OP_EN                       0x0800u
#define ISOADC6_CFG_BOUT_CURR_500_UA                0x0200u
#define ISOADC6_CFG_BOUT_CURR_2_MA                  0x0400u
#define ISOADC6_CFG_BOUT_CURR_4_MA                  0x0600u
#define ISOADC6_CFG_BUFF_ON_REFIN_POS_EN            0x0100u
#define ISOADC6_CFG_BUFF_ON_REFIN_NEG_EN            0x0080u
#define ISOADC6_CFG_BUFF_ON_AINP_EN                 0x0040u
#define ISOADC6_CFG_BUFF_ON_AINM_EN                 0x0020u
#define ISOADC6_CFG_SEL_REFIN1                      0x0000u
#define ISOADC6_CFG_SEL_REFIN2                      0x0008u
#define ISOADC6_CFG_SEL_INT_REF                     0x0010u
#define ISOADC6_CFG_SEL_AVDD_REF                    0x0018u
#define ISOADC6_CFG_SET_GAIN_1                      0x0000u
#define ISOADC6_CFG_SET_GAIN_2                      0x0001u
#define ISOADC6_CFG_SET_GAIN_4                      0x0002u
#define ISOADC6_CFG_SET_GAIN_8                      0x0003u
#define ISOADC6_CFG_SET_GAIN_16                     0x0004u
#define ISOADC6_CFG_SET_GAIN_32                     0x0005u
#define ISOADC6_CFG_SET_GAIN_64                     0x0006u
#define ISOADC6_CFG_SET_GAIN_128                    0x0007u

/**
 * @brief ISO ADC 6 voltage reference and calibration data values.
 * @details Voltage reference data of ISO ADC 6 Click driver.
 */
#define ISOADC6_VTG_REF_2_65_V                      2.65f
#define ISOADC6_CALIB_DEFAULT                       1.00f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b isoadc6_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ISOADC6_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define ISOADC6_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // isoadc6_set

/**
 * @defgroup isoadc6_map ISO ADC 6 MikroBUS Map
 * @brief MikroBUS pin mapping of ISO ADC 6 Click driver.
 */

/**
 * @addtogroup isoadc6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISO ADC 6 Click to the selected MikroBUS.
 */
#define ISOADC6_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // isoadc6_map
/*! @} */ // isoadc6

/**
 * @brief ISO ADC 6 Click context object.
 * @details Context object definition of ISO ADC 6 Click driver.
 */
typedef struct
{
    // Modules
    spi_master_t spi;            /**< SPI driver object. */

    pin_name_t   chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
    
    float vref;                  /**< Voltage reference. */
    float calib;                 /**< Calibration range of the ADC gain [0.4-1.05]. */
    uint8_t ch_sel;              /**< Channel selection. */

} isoadc6_t;

/**
 * @brief ISO ADC 6 Click configuration object.
 * @details Configuration object definition of ISO ADC 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */
    
    float vref;                  /**< Voltage reference. */
    float calib;                 /**< Calibration range of the ADC gain [0.4-1.05]. */
    uint8_t ch_sel;              /**< Channel selection. */

} isoadc6_cfg_t;

/**
 * @brief ISO ADC 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISOADC6_OK = 0,
    ISOADC6_ERROR = -1

} isoadc6_return_value_t;

/*!
 * @addtogroup isoadc6 ISO ADC 6 Click Driver
 * @brief API for configuring and manipulating ISO ADC 6 Click driver.
 * @{
 */

/**
 * @brief ISO ADC 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #isoadc6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void isoadc6_cfg_setup ( isoadc6_cfg_t *cfg );

/**
 * @brief ISO ADC 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #isoadc6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_init ( isoadc6_t *ctx, isoadc6_cfg_t *cfg );

/**
 * @brief ISO ADC 6 default configuration function.
 * @details This function executes a default configuration of ISO ADC 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t isoadc6_default_cfg ( isoadc6_t *ctx );

/**
 * @brief ISO ADC 6 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_generic_write ( isoadc6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief ISO ADC 6 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_generic_read ( isoadc6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief ISO ADC 6 byte writing function.
 * @details This function writes a desired data byte to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 8-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_write_byte ( isoadc6_t* ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief ISO ADC 6 byte reading function.
 * @details This function reads a desired data byte from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 8-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_read_byte ( isoadc6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief ISO ADC 6 word writing function.
 * @details This function writes a desired data word to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_write_word ( isoadc6_t* ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief ISO ADC 6 word reading function.
 * @details This function reads a desired data word from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 16-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_read_word ( isoadc6_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief ISO ADC 6 dword writing function.
 * @details This function writes a desired data dword to the selected register 
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : 32-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_write_dword ( isoadc6_t* ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief ISO ADC 6 dword reading function.
 * @details This function reads a desired data dword from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read 32-bit data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_read_dword ( isoadc6_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief ISO ADC 6 get device ID function.
 * @details This function read the device ID and silicon revision 
 * of the AD7124-8, 8-Channel, Low Noise, Low Power, 24-Bit, 
 * Sigma-Delta ADC with PGA and Reference
 * wired with ADuM341E, 5.7 kV rms Quad Digital Isolators
 * on the ISO ADC 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[out] device_id : Device ID.
 * @param[out] sil_rev : Silicon revision.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_get_device_id ( isoadc6_t* ctx, uint8_t *device_id, uint8_t *sil_rev );

/**
 * @brief ISO ADC 6 set channel function.
 * @details This function sets the channel configuration
 * of the AD7124-8, 8-Channel, Low Noise, Low Power, 24-Bit, 
 * Sigma-Delta ADC with PGA and Reference
 * wired with ADuM341E, 5.7 kV rms Quad Digital Isolators
 * on the ISO ADC 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] sel_ch : Channel selection [0-8].
 * @param[in] ch_data : Channel config data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_set_channel ( isoadc6_t* ctx, uint8_t sel_ch, uint16_t ch_data );

/**
 * @brief ISO ADC 6 set channel config function.
 * @details This function sets the configuration of the channel settings
 * of the AD7124-8, 8-Channel, Low Noise, Low Power, 24-Bit, 
 * Sigma-Delta ADC with PGA and Reference
 * wired with ADuM341E, 5.7 kV rms Quad Digital Isolators
 * on the ISO ADC 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] ch_data : Configuration data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_set_ch_config ( isoadc6_t* ctx, uint16_t cfg_data );

/**
 * @brief ISO ADC 6 set ADC control function.
 * @details This function sets the ADC control configuration
 * of the AD7124-8, 8-Channel, Low Noise, Low Power, 24-Bit, 
 * Sigma-Delta ADC with PGA and Reference
 * wired with ADuM341E, 5.7 kV rms Quad Digital Isolators
 * on the ISO ADC 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] adc_ctrl_data : ADC control configuration data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_set_adc_control ( isoadc6_t* ctx, uint16_t adc_ctrl );

/**
 * @brief ISO ADC 6 set channel offset function.
 * @details This function sets the channel offset
 * of the AD7124-8, 8-Channel, Low Noise, Low Power, 24-Bit, 
 * Sigma-Delta ADC with PGA and Reference
 * wired with ADuM341E, 5.7 kV rms Quad Digital Isolators
 * on the ISO ADC 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] ch_data : Channel offset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_set_ch_offset ( isoadc6_t* ctx, uint32_t offset );

/**
 * @brief ISO ADC 6 get channel offset function.
 * @details This function reads a channel offset data
 * of the AD7124-8, 8-Channel, Low Noise, Low Power, 24-Bit, 
 * Sigma-Delta ADC with PGA and Reference
 * wired with ADuM341E, 5.7 kV rms Quad Digital Isolators
 * on the ISO ADC 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[out] ch_data : Channel offset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_get_ch_offset ( isoadc6_t* ctx,  uint32_t *offset );

/**
 * @brief ISO ADC 6 set channel gain function.
 * @details This function sets the channel gain
 * of the AD7124-8, 8-Channel, Low Noise, Low Power, 24-Bit, 
 * Sigma-Delta ADC with PGA and Reference
 * wired with ADuM341E, 5.7 kV rms Quad Digital Isolators
 * on the ISO ADC 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[in] ch_data : Channel offset.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_set_ch_gain ( isoadc6_t* ctx, uint32_t gain );

/**
 * @brief ISO ADC 6 get channel gain function.
 * @details This function reads a channel gain data
 * of the AD7124-8, 8-Channel, Low Noise, Low Power, 24-Bit, 
 * Sigma-Delta ADC with PGA and Reference
 * wired with ADuM341E, 5.7 kV rms Quad Digital Isolators
 * on the ISO ADC 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[out] ch_data : Channel gain.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_get_ch_gain ( isoadc6_t* ctx, uint32_t *gain );

/**
 * @brief ISO ADC 6 get ADC data function.
 * @details This function is used to read 24-Bit ADC raw data value
 * of the AD7124-8, 8-Channel, Low Noise, Low Power, 24-Bit, 
 * Sigma-Delta ADC with PGA and Reference
 * wired with ADuM341E, 5.7 kV rms Quad Digital Isolators
 * on the ISO ADC 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[out] ch_data : 24-Bit ADC data value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_get_adc_data ( isoadc6_t* ctx, uint32_t *adc_data );

/**
 * @brief ISO ADC 6 get voltage level function.
 * @details This function reads results of 24-bit ADC raw data 
 * and converts them to proportional voltage level [V], 
 * of the AD7124-8, 8-Channel, Low Noise, Low Power, 24-Bit, 
 * Sigma-Delta ADC with PGA and Reference
 * wired with ADuM341E, 5.7 kV rms Quad Digital Isolators
 * on the ISO ADC 6 Click board™.
 * @param[in] ctx : Click context object.
 * See #isoadc6_t object definition for detailed explanation.
 * @param[out] voltage :Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t isoadc6_get_voltage ( isoadc6_t* ctx, float *voltage );

#ifdef __cplusplus
}
#endif
#endif // ISOADC6_H

/*! @} */ // isoadc6

// ------------------------------------------------------------------------ END
