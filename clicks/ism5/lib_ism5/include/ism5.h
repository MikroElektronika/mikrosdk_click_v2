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
 * @file ism5.h
 * @brief This file contains API for ISM 5 Click Driver.
 */

#ifndef ISM5_H
#define ISM5_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup ism5 ISM 5 Click Driver
 * @brief API for configuring and manipulating ISM 5 Click driver.
 * @{
 */

/**
 * @defgroup ism5_cmd ISM 5 Commands List
 * @brief List of commands of ISM 5 Click driver.
 */

/**
 * @addtogroup ism5_cmd
 * @{
 */

/**
 * @brief ISM 5 list of commands.
 * @details Specified commands list of ISM 5 Click driver.
 */
#define ISM5_CMD_POWER_UP                               0x02
#define ISM5_CMD_NOP                                    0x00
#define ISM5_CMD_PART_INFO                              0x01
#define ISM5_CMD_FUNC_INFO                              0x10
#define ISM5_CMD_SET_PROPERTY                           0x11
#define ISM5_CMD_GET_PROPERTY                           0x12
#define ISM5_CMD_GPIO_PIN_CFG                           0x13
#define ISM5_CMD_FIFO_INFO                              0x15
#define ISM5_CMD_GET_INT_STATUS                         0x20
#define ISM5_CMD_REQUEST_DEVICE_STATE                   0x33
#define ISM5_CMD_CHANGE_STATE                           0x34
#define ISM5_CMD_OFFLINE_RECAL                          0x38
#define ISM5_CMD_READ_CMD_BUFF                          0x44
#define ISM5_CMD_FRR_A_READ                             0x50
#define ISM5_CMD_FRR_B_READ                             0x51
#define ISM5_CMD_FRR_C_READ                             0x53
#define ISM5_CMD_FRR_D_READ                             0x57
#define ISM5_CMD_IRCAL                                  0x17
#define ISM5_CMD_START_TX                               0x31
#define ISM5_CMD_TX_HOP                                 0x37
#define ISM5_CMD_WRITE_TX_FIFO                          0x66
#define ISM5_CMD_PACKET_INFO                            0x16
#define ISM5_CMD_GET_MODEM_STATUS                       0x22
#define ISM5_CMD_START_RX                               0x32
#define ISM5_CMD_RX_HOP                                 0x36
#define ISM5_CMD_READ_RX_FIFO                           0x77
#define ISM5_CMD_GET_ADC_READING                        0x14
#define ISM5_CMD_GET_PH_STATUS                          0x21
#define ISM5_CMD_GET_CHIP_STATUS                        0x23

/*! @} */ // ism5_cmd

/**
 * @defgroup ism5_set ISM 5 Registers Settings
 * @brief Settings for registers of ISM 5 Click driver.
 */

/**
 * @addtogroup ism5_set
 * @{
 */

/**
 * @brief ISM 5 radio ready setting.
 * @details Specified setting for radio ready of ISM 5 Click driver.
 */
#define ISM5_CTS_READY_BYTE                             0xFF
#define ISM5_CTS_READY_TIMEOUT                          5000ul

/**
 * @brief ISM 5 part number setting.
 * @details Specified setting for part number of ISM 5 Click driver.
 */
#define ISM5_PART_NUMBER                                0x4461u

/**
 * @brief ISM 5 power up setting.
 * @details Specified setting for power up of ISM 5 Click driver.
 */
#define ISM5_POWER_UP_BOOT_FUNCTIONAL                   1
#define ISM5_POWER_UP_SELECT_TCXO                       1
#define ISM5_POWER_UP_TCXO_26MHZ                        26000000ul

/**
 * @brief ISM 5 property index setting.
 * @details Specified setting for property index of ISM 5 Click driver.
 */
#define ISM5_PROPERTY_GLOBAL_XO_TUNE                    0x0000
#define ISM5_PROPERTY_GLOBAL_CLK_CFG                    0x0001
#define ISM5_PROPERTY_GLOBAL_LOW_BATT_THRESH            0x0001
#define ISM5_PROPERTY_GLOBAL_CONFIG                     0x0003
#define ISM5_PROPERTY_GLOBAL_WUT_CONFIG                 0x0004
#define ISM5_PROPERTY_GLOBAL_WUT_M_15_8                 0x0005
#define ISM5_PROPERTY_GLOBAL_WUT_M_7_0                  0x0006
#define ISM5_PROPERTY_GLOBAL_WUT_R                      0x0007
#define ISM5_PROPERTY_GLOBAL_WUT_LDC                    0x0008
#define ISM5_PROPERTY_GLOBAL_WUT_CAL                    0x0009
#define ISM5_PROPERTY_INT_CTL_ENABLE                    0x0100
#define ISM5_PROPERTY_INT_CTL_PH_ENABLE                 0x0101
#define ISM5_PROPERTY_INT_CTL_MODEM_ENABLE              0x0102
#define ISM5_PROPERTY_INT_CTL_CHIP_ENABLE               0x0103
#define ISM5_PROPERTY_FRR_CTL_A_MODE                    0x0200
#define ISM5_PROPERTY_FRR_CTL_B_MODE                    0x0201
#define ISM5_PROPERTY_FRR_CTL_C_MODE                    0x0202
#define ISM5_PROPERTY_FRR_CTL_D_MODE                    0x0203
#define ISM5_PROPERTY_PREAMBLE_TX_LENGTH                0x1000
#define ISM5_PROPERTY_PREAMBLE_CONFIG_STD_1             0x1001
#define ISM5_PROPERTY_PREAMBLE_CONFIG_NSTD              0x1002
#define ISM5_PROPERTY_PREAMBLE_CONFIG_STD_2             0x1003
#define ISM5_PROPERTY_PREAMBLE_CONFIG                   0x1004
#define ISM5_PROPERTY_PREAMBLE_PATTERN_31_24            0x1005
#define ISM5_PROPERTY_PREAMBLE_PATTERN_23_16            0x1006
#define ISM5_PROPERTY_PREAMBLE_PATTERN_15_8             0x1007
#define ISM5_PROPERTY_PREAMBLE_PATTERN_7_0              0x1008
#define ISM5_PROPERTY_PREAMBLE_POSTAMBLE_CONFIG         0x1009
#define ISM5_PROPERTY_PREAMBLE_POSTAMBLE_PATTERN_31_24  0x100A
#define ISM5_PROPERTY_PREAMBLE_POSTAMBLE_PATTERN_23_16	0x100B
#define ISM5_PROPERTY_PREAMBLE_POSTAMBLE_PATTERN_15_8   0x100C
#define ISM5_PROPERTY_PREAMBLE_POSTAMBLE_PATTERN_7_0    0x100D
#define ISM5_PROPERTY_SYNC_CONFIG                       0x1100
#define ISM5_PROPERTY_SYNC_BITS_31_24                   0x1101
#define ISM5_PROPERTY_SYNC_BITS_23_16                   0x1102
#define ISM5_PROPERTY_SYNC_BITS_15_8                    0x1103
#define ISM5_PROPERTY_SYNC_BITS_7_0                     0x1104
#define ISM5_PROPERTY_PKT_CRC_CONFIG                    0x1200
#define ISM5_PROPERTY_PKT_CONFIG1                       0x1206
#define ISM5_PROPERTY_PKT_LEN                           0x1208
#define ISM5_PROPERTY_PKT_LEN_FIELD_SOURCE              0x1209
#define ISM5_PROPERTY_PKT_LEN_ADJUST                    0x120A
#define ISM5_PROPERTY_PKT_TX_THRESHOLD                  0x120B
#define ISM5_PROPERTY_PKT_RX_THRESHOLD                  0x120C
#define ISM5_PROPERTY_PKT_FIELD_1_LENGTH_12_8           0x120D
#define ISM5_PROPERTY_PKT_FIELD_1_LENGTH_7_0            0x120E
#define ISM5_PROPERTY_PKT_FIELD_1_CONFIG                0x120F
#define ISM5_PROPERTY_PKT_FIELD_1_CRC_CONFIG            0x1210
#define ISM5_PROPERTY_PKT_FIELD_2_LENGTH_12_8           0x1211
#define ISM5_PROPERTY_PKT_FIELD_2_LENGTH_7_0            0x1212
#define ISM5_PROPERTY_PKT_FIELD_2_CONFIG                0x1213
#define ISM5_PROPERTY_PKT_FIELD_2_CRC_CONFIG            0x1214
#define ISM5_PROPERTY_PKT_FIELD_3_LENGTH_12_8           0x1215
#define ISM5_PROPERTY_PKT_FIELD_3_LENGTH_7_0            0x1216
#define ISM5_PROPERTY_PKT_FIELD_3_CONFIG                0x1217
#define ISM5_PROPERTY_PKT_FIELD_3_CRC_CONFIG            0x1218
#define ISM5_PROPERTY_PKT_FIELD_4_LENGTH_12_8           0x1219
#define ISM5_PROPERTY_PKT_FIELD_4_LENGTH_7_0            0x121A
#define ISM5_PROPERTY_PKT_FIELD_4_CONFIG                0x121B
#define ISM5_PROPERTY_PKT_FIELD_4_CRC_CONFIG            0x121C
#define ISM5_PROPERTY_PKT_FIELD_5_LENGTH_12_8           0x121D
#define ISM5_PROPERTY_PKT_FIELD_5_LENGTH_7_0            0x121E
#define ISM5_PROPERTY_PKT_FIELD_5_CONFIG                0x121F
#define ISM5_PROPERTY_PKT_FIELD_5_CRC_CONFIG            0x1220
#define ISM5_PROPERTY_PKT_RX_FIELD_1_LENGTH_12_8        0x1221
#define ISM5_PROPERTY_PKT_RX_FIELD_1_LENGTH_7_0         0x1222
#define ISM5_PROPERTY_PKT_RX_FIELD_1_CONFIG             0x1223
#define ISM5_PROPERTY_PKT_RX_FIELD_1_CRC_CONFIG         0x1224
#define ISM5_PROPERTY_PKT_RX_FIELD_2_LENGTH_12_8        0x1225
#define ISM5_PROPERTY_PKT_RX_FIELD_2_LENGTH_7_0         0x1226
#define ISM5_PROPERTY_PKT_RX_FIELD_2_CONFIG             0x1227
#define ISM5_PROPERTY_PKT_RX_FIELD_2_CRC_CONFIG         0x1228
#define ISM5_PROPERTY_PKT_RX_FIELD_3_LENGTH_12_8	    0x1229
#define ISM5_PROPERTY_PKT_RX_FIELD_3_LENGTH_7_0         0x122A
#define ISM5_PROPERTY_PKT_RX_FIELD_3_CONFIG             0x122B
#define ISM5_PROPERTY_PKT_RX_FIELD_3_CRC_CONFIG         0x122C
#define ISM5_PROPERTY_PKT_RX_FIELD_4_LENGTH_12_8	    0x122D
#define ISM5_PROPERTY_PKT_RX_FIELD_4_LENGTH_7_0         0x122E
#define ISM5_PROPERTY_PKT_RX_FIELD_4_CONFIG             0x122F
#define ISM5_PROPERTY_PKT_RX_FIELD_4_CRC_CONFIG         0x1230
#define ISM5_PROPERTY_PKT_RX_FIELD_5_LENGTH_12_8	    0x1231
#define ISM5_PROPERTY_PKT_RX_FIELD_5_LENGTH_7_0         0x1232
#define ISM5_PROPERTY_PKT_RX_FIELD_5_CONFIG             0x1233
#define ISM5_PROPERTY_PKT_RX_FIELD_5_CRC_CONFIG         0x1234
#define ISM5_PROPERTY_MODEM_MOD_TYPE                    0x2000
#define ISM5_PROPERTY_MODEM_MAP_CONTROL                 0x2001
#define ISM5_PROPERTY_MODEM_DATA_RATE_2                 0x2003
#define ISM5_PROPERTY_MODEM_DATA_RATE_1                 0x2004
#define ISM5_PROPERTY_MODEM_DATA_RATE_0                 0x2005
#define ISM5_PROPERTY_MODEM_TX_NCO_MODE_3               0x2006
#define ISM5_PROPERTY_MODEM_TX_NCO_MODE_2               0x2007
#define ISM5_PROPERTY_MODEM_TX_NCO_MODE_1               0x2008
#define ISM5_PROPERTY_MODEM_TX_NCO_MODE_0               0x2009
#define ISM5_PROPERTY_MODEM_FREQ_DEV_2                  0x200A
#define ISM5_PROPERTY_MODEM_FREQ_DEV_1                  0x200B
#define ISM5_PROPERTY_MODEM_FREQ_DEV_0                  0x200C
#define ISM5_PROPERTY_MODEM_FREQ_OFFSET_1               0x200D
#define ISM5_PROPERTY_MODEM_FREQ_OFFSET_0               0x200E
#define ISM5_PROPERTY_MODEM_TX_FILTER_COEFF_8           0x200F
#define ISM5_PROPERTY_MODEM_TX_FILTER_COEFF_7           0x2010
#define ISM5_PROPERTY_MODEM_TX_FILTER_COEFF_6           0x2011
#define ISM5_PROPERTY_MODEM_TX_FILTER_COEFF_5           0x2012
#define ISM5_PROPERTY_MODEM_TX_FILTER_COEFF_4           0x2013
#define ISM5_PROPERTY_MODEM_TX_FILTER_COEFF_3           0x2014
#define ISM5_PROPERTY_MODEM_TX_FILTER_COEFF_2           0x2015
#define ISM5_PROPERTY_MODEM_TX_FILTER_COEFF_1           0x2016
#define ISM5_PROPERTY_MODEM_TX_FILTER_COEFF_0           0x2017
#define ISM5_PROPERTY_MODEM_TX_RAMP_DELAY               0x2018
#define ISM5_PROPERTY_MODEM_MDM_CTRL                    0x2019
#define ISM5_PROPERTY_MODEM_IF_CONTROL                  0x201A
#define ISM5_PROPERTY_MODEM_IF_FREQ_2                   0x201B
#define ISM5_PROPERTY_MODEM_IF_FREQ_1                   0x201C
#define ISM5_PROPERTY_MODEM_IF_FREQ_0                   0x201D
#define ISM5_PROPERTY_MODEM_DECIMATION_CFG1             0x201E
#define ISM5_PROPERTY_MODEM_DECIMATION_CFG0             0x201F
#define ISM5_PROPERTY_MODEM_BCR_OSR_1                   0x2022
#define ISM5_PROPERTY_MODEM_BCR_OSR_0                   0x2023
#define ISM5_PROPERTY_MODEM_BCR_NCO_OFFSET_2            0x2024
#define ISM5_PROPERTY_MODEM_BCR_NCO_OFFSET_1            0x2025
#define ISM5_PROPERTY_MODEM_BCR_NCO_OFFSET_0            0x2026
#define ISM5_PROPERTY_MODEM_BCR_GAIN_1                  0x2027
#define ISM5_PROPERTY_MODEM_BCR_GAIN_0                  0x2028
#define ISM5_PROPERTY_MODEM_BCR_GEAR                    0x2029
#define ISM5_PROPERTY_MODEM_BCR_MISC1                   0x202A
#define ISM5_PROPERTY_MODEM_BCR_MISC0                   0x202B
#define ISM5_PROPERTY_MODEM_AFC_GEAR                    0x202C
#define ISM5_PROPERTY_MODEM_AFC_WAIT                    0x202D
#define ISM5_PROPERTY_MODEM_AFC_GAIN_1                  0x202E
#define ISM5_PROPERTY_MODEM_AFC_GAIN_0                  0x202F
#define ISM5_PROPERTY_MODEM_AFC_LIMITER_1               0x2030
#define ISM5_PROPERTY_MODEM_AFC_LIMITER_0               0x2031
#define ISM5_PROPERTY_MODEM_AFC_MISC                    0x2032
#define ISM5_PROPERTY_MODEM_AFC_ZIFOFF                  0x2033
#define ISM5_PROPERTY_MODEM_ADC_CTRL                    0x2034
#define ISM5_PROPERTY_MODEM_AGC_CONTROL                 0x2035
#define ISM5_PROPERTY_MODEM_AGC_WINDOW_SIZE             0x2038
#define ISM5_PROPERTY_MODEM_AGC_RFPD_DECAY              0x2039
#define ISM5_PROPERTY_MODEM_AGC_IFPD_DECAY              0x203A
#define ISM5_PROPERTY_MODEM_FSK4_GAIN1                  0x203B
#define ISM5_PROPERTY_MODEM_FSK4_GAIN0                  0x203C
#define ISM5_PROPERTY_MODEM_FSK4_TH1                    0x203D
#define ISM5_PROPERTY_MODEM_FSK4_TH0                    0x203E
#define ISM5_PROPERTY_MODEM_FSK4_MAP                    0x203F
#define ISM5_PROPERTY_MODEM_OOK_PDTC                    0x2040
#define ISM5_PROPERTY_MODEM_OOK_BLOPK                   0x2041
#define ISM5_PROPERTY_MODEM_OOK_CNT1                    0x2042
#define ISM5_PROPERTY_MODEM_OOK_MISC                    0x2043
#define ISM5_PROPERTY_MODEM_RAW_SEARCH                  0x2044
#define ISM5_PROPERTY_MODEM_RAW_CONTROL                 0x2045
#define ISM5_PROPERTY_MODEM_RAW_EYE_1                   0x2046
#define ISM5_PROPERTY_MODEM_RAW_EYE_0                   0x2047
#define ISM5_PROPERTY_MODEM_ANT_DIV_MODE                0x2048
#define ISM5_PROPERTY_MODEM_ANT_DIV_CONTROL             0x2049
#define ISM5_PROPERTY_MODEM_RSSI_THRESH                 0x204A
#define ISM5_PROPERTY_MODEM_RSSI_JUMP_THRESH            0x204B
#define ISM5_PROPERTY_MODEM_RSSI_CONTROL                0x204C
#define ISM5_PROPERTY_MODEM_RSSI_CONTROL2               0x204D
#define ISM5_PROPERTY_MODEM_RSSI_COMP                   0x204E
#define ISM5_PROPERTY_MODEM_CLKGEN_BAND                 0x2051
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE13_7_0   0x2100
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE12_7_0   0x2101
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE11_7_0   0x2102
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE10_7_0	0x2103
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE9_7_0    0x2104
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE8_7_0    0x2105
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE7_7_0    0x2106
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE6_7_0    0x2107
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE5_7_0    0x2108
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE4_7_0    0x2109
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE3_7_0	0x210A
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE2_7_0    0x210B
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE1_7_0    0x210C
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COE0_7_0	0x210D
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COEM0       0x210E
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COEM1       0x210F
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COEM2       0x2110
#define ISM5_PROPERTY_MODEM_CHFLT_RX1_CHFLT_COEM3       0x2111
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE13_7_0	0x2112
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE12_7_0	0x2113
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE11_7_0	0x2114
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE10_7_0	0x2115
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE9_7_0    0x2116
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE8_7_0    0x2117
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE7_7_0    0x2118
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE6_7_0    0x2119
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE5_7_0    0x211A
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE4_7_0    0x211B
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE3_7_0    0x211C
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE2_7_0    0x211D
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE1_7_0	0x211E
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COE0_7_0    0x211F
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COEM0       0x2120
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COEM1       0x2121
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COEM2       0x2122
#define ISM5_PROPERTY_MODEM_CHFLT_RX2_CHFLT_COEM3       0x2123
#define ISM5_PROPERTY_PA_MODE                           0x2200
#define ISM5_PROPERTY_PA_PWR_LVL                        0x2201
#define ISM5_PROPERTY_PA_BIAS_CLKDUTY                   0x2202
#define ISM5_PROPERTY_PA_TC                             0x2203
#define ISM5_PROPERTY_PA_RAMP_EX                        0x2204
#define ISM5_PROPERTY_PA_RAMP_DOWN_DELAY                0x2205
#define ISM5_PROPERTY_SYNTH_PFDCP_CPFF                  0x2300
#define ISM5_PROPERTY_SYNTH_PFDCP_CPINT                 0x2301
#define ISM5_PROPERTY_SYNTH_VCO_KV                      0x2302
#define ISM5_PROPERTY_SYNTH_LPFILT3                     0x2303
#define ISM5_PROPERTY_SYNTH_LPFILT2                     0x2304
#define ISM5_PROPERTY_SYNTH_LPFILT1                     0x2305
#define ISM5_PROPERTY_SYNTH_LPFILT0                     0x2306
#define ISM5_PROPERTY_SYNTH_VCO_KVCAL                   0x2307
#define ISM5_PROPERTY_MATCH_VALUE_1                     0x3000
#define ISM5_PROPERTY_MATCH_MASK_1                      0x3001
#define ISM5_PROPERTY_MATCH_CTRL_1                      0x3002
#define ISM5_PROPERTY_MATCH_VALUE_2                     0x3003
#define ISM5_PROPERTY_MATCH_MASK_2                      0x3004
#define ISM5_PROPERTY_MATCH_CTRL_2                      0x3005
#define ISM5_PROPERTY_MATCH_VALUE_3                     0x3006
#define ISM5_PROPERTY_MATCH_MASK_3                      0x3007
#define ISM5_PROPERTY_MATCH_CTRL_3                      0x3008
#define ISM5_PROPERTY_MATCH_VALUE_4                     0x3009
#define ISM5_PROPERTY_MATCH_MASK_4                      0x300A
#define ISM5_PROPERTY_MATCH_CTRL_4                      0x300B
#define ISM5_PROPERTY_FREQ_CONTROL_INTE                 0x4000
#define ISM5_PROPERTY_FREQ_CONTROL_FRAC_2               0x4001
#define ISM5_PROPERTY_FREQ_CONTROL_FRAC_1               0x4002
#define ISM5_PROPERTY_FREQ_CONTROL_FRAC_0               0x4003
#define ISM5_PROPERTY_FREQ_CONTROL_CHANNEL_STEP_SIZE_1  0x4004
#define ISM5_PROPERTY_FREQ_CONTROL_CHANNEL_STEP_SIZE_0	0x4005
#define ISM5_PROPERTY_FREQ_CONTROL_W_SIZE               0x4006
#define ISM5_PROPERTY_FREQ_CONTROL_VCOCNT_RX_ADJ        0x4007
#define ISM5_PROPERTY_RX_HOP_CONTROL                    0x5000
#define ISM5_PROPERTY_RX_HOP_TABLE_SIZE                 0x5001
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_0              0x5002
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_1              0x5003
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_2              0x5004
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_3              0x5005
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_4              0x5006
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_5              0x5007
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_6              0x5008
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_7              0x5009
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_8              0x500A
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_9              0x500B
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_10             0x500C
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_11             0x500D
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_12             0x500E
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_13             0x500F
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_14             0x5010
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_15             0x5011
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_16             0x5012
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_17             0x5013
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_18             0x5014
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_19             0x5015
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_20             0x5016
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_21             0x5017
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_22             0x5018
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_23             0x5019
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_24             0x501A
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_25             0x501B
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_26             0x501C
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_27             0x501D
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_28             0x501E
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_29             0x501F
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_30             0x5020
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_31             0x5021
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_32             0x5022
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_33             0x5023
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_34             0x5024
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_35             0x5025
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_36             0x5026
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_37             0x5027
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_38             0x5028
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_39             0x5029
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_40             0x502A
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_41             0x502B
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_42             0x502C
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_43             0x502D
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_44             0x502E
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_45             0x502F
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_46             0x5030
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_47             0x5031
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_48             0x5032
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_49             0x5033
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_50             0x5034
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_51             0x5035
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_52             0x5036
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_53             0x5037
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_54             0x5038
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_55             0x5039
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_56             0x503A
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_57             0x503B
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_58             0x503C
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_59             0x503D
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_60             0x503E
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_61             0x503F
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_62             0x5040
#define ISM5_PROPERTY_RX_HOP_TABLE_ENTRY_63             0x5041

/**
 * @brief ISM 5 fifo reset flags setting.
 * @details Specified setting for fifo reset flags of ISM 5 Click driver.
 */
#define ISM5_FIFO_RESET_NONE                            0x00
#define ISM5_FIFO_RESET_TX                              0x01
#define ISM5_FIFO_RESET_RX                              0x02
#define ISM5_FIFO_RESET_TX_RX                           0x03
#define ISM5_FIFO_RESET_MASK                            0x03

/**
 * @brief ISM 5 operating state setting.
 * @details Specified setting for operating state of ISM 5 Click driver.
 */
#define ISM5_STATE_NO_CHANGE                            0x00
#define ISM5_STATE_SLEEP                                0x01
#define ISM5_STATE_SPI_ACTIVE                           0x02
#define ISM5_STATE_READY                                0x03
#define ISM5_STATE_TX_TUNE                              0x05
#define ISM5_STATE_RX_TUNE                              0x06
#define ISM5_STATE_TX                                   0x07
#define ISM5_STATE_RX                                   0x08
#define ISM5_STATE_MASK                                 0x0F

/**
 * @brief ISM 5 interrupts setting.
 * @details Specified setting for interrupts of ISM 5 Click driver.
 */
#define ISM5_INT_CLEAR                                  0x00
#define ISM5_INT_PEND_PH                                0x01
#define ISM5_INT_PEND_MODEM                             0x02
#define ISM5_INT_PEND_CHIP                              0x04
#define ISM5_INT_STATUS_PH                              0x01
#define ISM5_INT_STATUS_MODEM                           0x02
#define ISM5_INT_STATUS_CHIP                            0x04
#define ISM5_PH_PEND_RX_FIFO_ALMOST_FULL                0x01
#define ISM5_PH_PEND_TX_FIFO_ALMOST_EMPTY               0x02
#define ISM5_PH_PEND_ALT_CRC_ERROR                      0x04
#define ISM5_PH_PEND_CRC_ERROR                          0x08
#define ISM5_PH_PEND_PACKET_RX                          0x10
#define ISM5_PH_PEND_PACKET_SEND                        0x20
#define ISM5_PH_PEND_FILTER_MISS                        0x40
#define ISM5_PH_PEND_FILTER_MATCH                       0x80
#define ISM5_PH_STATUS_RX_FIFO_ALMOST_FULL              0x01
#define ISM5_PH_STATUS_TX_FIFO_ALMOST_EMPTY             0x02
#define ISM5_PH_STATUS_ALT_CRC_ERROR                    0x04
#define ISM5_PH_STATUS_CRC_ERROR                        0x08
#define ISM5_PH_STATUS_PACKET_RX                        0x10
#define ISM5_PH_STATUS_PACKET_SEND                      0x20
#define ISM5_PH_STATUS_FILTER_MISS                      0x40
#define ISM5_PH_STATUS_FILTER_MATCH                     0x80
#define ISM5_MODEM_PEND_SYNC_DETECT                     0x01
#define ISM5_MODEM_PEND_PREAMBLE_DETECT                 0x02
#define ISM5_MODEM_PEND_INVALID_PREAMBLE                0x04
#define ISM5_MODEM_PEND_RSSI                            0x08
#define ISM5_MODEM_PEND_RSSI_JUMP                       0x10
#define ISM5_MODEM_PEND_INVALID_SYNC                    0x20
#define ISM5_MODEM_PEND_POSTAMBLE_DETECT                0x40
#define ISM5_MODEM_PEND_RSSI_LATCH                      0x80
#define ISM5_MODEM_STATUS_SYNC_DETECT                   0x01
#define ISM5_MODEM_STATUS_PREAMBLE_DETECT               0x02
#define ISM5_MODEM_STATUS_INVALID_PREAMBLE              0x04
#define ISM5_MODEM_STATUS_RSSI                          0x08
#define ISM5_MODEM_STATUS_RSSI_JUMP                     0x10
#define ISM5_MODEM_STATUS_INVALID_SYNC                  0x20
#define ISM5_MODEM_STATUS_POSTAMBLE_DETECT              0x40
#define ISM5_MODEM_STATUS_RSSI_LATCH                    0x80
#define ISM5_CHIP_PEND_WUT                              0x01
#define ISM5_CHIP_PEND_LOW_BATT                         0x02
#define ISM5_CHIP_PEND_CHIP_READY                       0x04
#define ISM5_CHIP_PEND_CMD_ERROR                        0x08
#define ISM5_CHIP_PEND_STATE_CHANGE                     0x10
#define ISM5_CHIP_PEND_FIFO_UNDERFLOW_OVERFLOW_ERROR    0x20
#define ISM5_CHIP_PEND_CAL                              0x40
#define ISM5_CHIP_STATUS_WUT                            0x01
#define ISM5_CHIP_STATUS_LOW_BATT                       0x02
#define ISM5_CHIP_STATUS_CHIP_READY                     0x04
#define ISM5_CHIP_STATUS_CMD_ERROR                      0x08
#define ISM5_CHIP_STATUS_STATE_CHANGE                   0x10
#define ISM5_CHIP_STATUS_FIFO_UNDERFLOW_OVERFLOW_ERROR  0x20
#define ISM5_CHIP_STATUS_CAL                            0x40

/**
 * @brief ISM 5 PA output power level setting.
 * @details Specified setting for PA output power level of ISM 5 Click driver.
 */
#define ISM5_PA_PWR_LVL_MIN                             0x00
#define ISM5_PA_PWR_LVL_MAX                             0x7F

/**
 * @brief ISM 5 packet setting.
 * @details Specified setting for packet of ISM 5 Click driver.
 */
#define ISM5_PACKET_MAX_SIZE                            64
#define ISM5_PACKET_FIXED_SIZE                          0
#define ISM5_PACKET_TIMEOUT_DISABLE                     0
#define ISM5_PACKET_TIMEOUT_1_SEC                       1000

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ism5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ISM5_SET_DATA_SAMPLE_EDGE                       SET_SPI_DATA_SAMPLE_EDGE
#define ISM5_SET_DATA_SAMPLE_MIDDLE                     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // ism5_set

/**
 * @defgroup ism5_map ISM 5 MikroBUS Map
 * @brief MikroBUS pin mapping of ISM 5 Click driver.
 */

/**
 * @addtogroup ism5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISM 5 Click to the selected MikroBUS.
 */
#define ISM5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.shd  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ism5_map
/*! @} */ // ism5

/**
 * @brief ISM 5 Click context object.
 * @details Context object definition of ISM 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t shd;          /**< Shutdown pin (active low). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} ism5_t;

/**
 * @brief ISM 5 Click configuration object.
 * @details Configuration object definition of ISM 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t shd;             /**< Shutdown pin (active low). */
    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} ism5_cfg_t;

/**
 * @brief ISM 5 Click part info object.
 * @details Part info object definition of ISM 5 Click driver.
 */
typedef struct
{
    uint8_t chip_rev;           /**< Chip revision. */
    uint16_t part;              /**< Part number (e.g. 0x4461 for SI4461). */
    uint8_t part_build;         /**< Part build. */
    uint16_t id;                /**< ID number. */
    uint8_t customer;           /**< Customer. */
    uint8_t rom_id;             /**< ROM ID. */

} ism5_part_info_t;

/**
 * @brief ISM 5 Click gpio config object.
 * @details GPIO config object definition of ISM 5 Click driver.
 */
typedef struct
{
    uint8_t gpio_0;             /**< GPIO 0 config. */
    uint8_t gpio_1;             /**< GPIO 1 config. */
    uint8_t gpio_2;             /**< GPIO 2 config. */
    uint8_t gpio_3;             /**< GPIO 3 config. */
    uint8_t nirq;               /**< NIRQ config. */
    uint8_t sdo;                /**< SDO config. */
    uint8_t gen_config;         /**< General config. */

} ism5_gpio_config_t;

/**
 * @brief ISM 5 Click int status object.
 * @details INT status object definition of ISM 5 Click driver.
 */
typedef struct
{
    uint8_t int_pend;           /**< Interrupt pending. */
    uint8_t int_status;         /**< Interrupt status. */
    uint8_t ph_pend;            /**< Packet handler pending. */
    uint8_t ph_status;          /**< Packet handler status. */
    uint8_t modem_pend;         /**< Modem pending. */
    uint8_t modem_status;       /**< Modem status. */
    uint8_t chip_pend;          /**< Chip pending. */
    uint8_t chip_status;        /**< Chip status. */

} ism5_int_status_t;

/**
 * @brief ISM 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISM5_OK = 0,
    ISM5_ERROR = -1,
    ISM5_TIMEOUT = -2

} ism5_return_value_t;

/*!
 * @addtogroup ism5 ISM 5 Click Driver
 * @brief API for configuring and manipulating ISM 5 Click driver.
 * @{
 */

/**
 * @brief ISM 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ism5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ism5_cfg_setup ( ism5_cfg_t *cfg );

/**
 * @brief ISM 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ism5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_init ( ism5_t *ctx, ism5_cfg_t *cfg );

/**
 * @brief ISM 5 default configuration function.
 * @details This function executes a default configuration of ISM 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ism5_default_cfg ( ism5_t *ctx );

/**
 * @brief ISM 5 send cmd function.
 * @details This function waits for the device ready and sends a desired command
 * by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to send (Required).
 * @param[in] data_in : Data to be written (Optional).
 * @param[in] len : Number of bytes to be written (Optional).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_send_cmd ( ism5_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief ISM 5 read resp function.
 * @details This function reads a response to the last command by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_read_rsp ( ism5_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief ISM 5 send fast cmd function.
 * @details This function sends a desired command without waiting for device ready (CTS byte).
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to send.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_send_fast_cmd ( ism5_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief ISM 5 read fast cmd function.
 * @details This function reads command response which doesn't contain a CTS byte
 * (RX fifo for example).
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to send.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_read_fast_cmd ( ism5_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len );

/**
 * @brief ISM 5 wait ready function.
 * @details This function waits up to 5 seconds for a CTS byte ready response.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_wait_ready ( ism5_t *ctx );

/**
 * @brief ISM 5 check ready function.
 * @details This function checks the device ready by reading a CTS byte response.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_check_ready ( ism5_t *ctx );

/**
 * @brief ISM 5 enable device function.
 * @details This function enables the device by setting the SHD pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ism5_enable_device ( ism5_t *ctx );

/**
 * @brief ISM 5 disable device function.
 * @details This function disables the device by setting the SHD pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ism5_disable_device ( ism5_t *ctx );

/**
 * @brief ISM 5 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ism5_get_int_pin ( ism5_t *ctx );

/**
 * @brief ISM 5 check communication function.
 * @details This function checks the communication by reading and verifying the device part ID.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_check_communication ( ism5_t *ctx );

/**
 * @brief ISM 5 config init function.
 * @details This function loads all properties and commands from RADIO_CONFIGURATION_DATA_ARRAY macro.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_config_init ( ism5_t *ctx );

/**
 * @brief ISM 5 power up function.
 * @details This function powers up device in normal operation mode with 26 MHz external oscillator.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_power_up ( ism5_t *ctx );

/**
 * @brief ISM 5 get part info function.
 * @details This function reads the device part information.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[out] part_info : Device part information read.
 * See #ism5_part_info_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_get_part_info ( ism5_t *ctx, ism5_part_info_t *part_info );

/**
 * @brief ISM 5 set property function.
 * @details This function sets a desired number of properties starting from the selected property index.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] prop_idx : Starting property index (property group as MSB and sub-property address as LSB).
 * @param[in] data_in : Property data to be written.
 * @param[in] num_props : Number of properties to be written [1-12].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_set_property ( ism5_t *ctx, uint16_t prop_idx, uint8_t *data_in, uint8_t num_props );

/**
 * @brief ISM 5 get property function.
 * @details This function gets a desired number of properties starting from the selected property index.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] prop_idx : Starting property index (property group as MSB and sub-property address as LSB).
 * @param[out] data_out : Property data read.
 * @param[in] num_props : Number of properties to be read [1-16].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_get_property ( ism5_t *ctx, uint16_t prop_idx, uint8_t *data_out, uint8_t num_props );

/**
 * @brief ISM 5 set property byte function.
 * @details This function sets the selected property data.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] prop_idx : Property index (property group as MSB and sub-property address as LSB).
 * @param[in] data_in : Property data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_set_property_byte ( ism5_t *ctx, uint16_t prop_idx, uint8_t data_in );

/**
 * @brief ISM 5 get property byte function.
 * @details This function gets the selected property data.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] prop_idx : Property index (property group as MSB and sub-property address as LSB).
 * @param[out] data_out : Property data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_get_property_byte ( ism5_t *ctx, uint16_t prop_idx, uint8_t *data_out );

/**
 * @brief ISM 5 gpio config function.
 * @details This function writes the selected gpio config and reads their state as a response.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in,out] gpio_cfg : GPIO config structure.
 * See #ism5_gpio_config_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_gpio_config ( ism5_t *ctx, ism5_gpio_config_t *gpio_cfg );

/**
 * @brief ISM 5 fifo info function.
 * @details This function reads the RX FIFO count and TX FIFO space and clears the FIFO buffers if needed.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] fifo_reset : FIFO reset bits (Required).
 * @param[out] rx_fifo_count : Number of data bytes available in RX FIFO buffer (Optional).
 * @param[out] tx_fifo_space : Number of data bytes available in TX FIFO buffer (Optional).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_fifo_info ( ism5_t *ctx, uint8_t fifo_reset, uint8_t *rx_fifo_count, uint8_t *tx_fifo_space );

/**
 * @brief ISM 5 get int status function.
 * @details This function reads and clears the interrupt status.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[out] status : Interrupt status object read (Optional).
 * See #ism5_int_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_get_int_status ( ism5_t *ctx, ism5_int_status_t *status );

/**
 * @brief ISM 5 get device state function.
 * @details This function reads the device current state and tuned channel.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[out] state : Device current state (Optional).
 * @param[out] channel : Device current tuned channel (Optional).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_get_device_state ( ism5_t *ctx, uint8_t *state, uint8_t *channel );

/**
 * @brief ISM 5 change state function.
 * @details This function sets the device state.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] state : Device operating state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_change_state ( ism5_t *ctx, uint8_t state );

/**
 * @brief ISM 5 start tx function.
 * @details This function starts the transmission on the selected channel.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] channel : Channel number on which to transmit data.
 * @param[in] condition : Condition byte (tx complete state, update tx parameters, retransmit, start delay).
 * @param[in] len : Number of data bytes to transmit (0 for a fixed packet length).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_start_tx ( ism5_t *ctx, uint8_t channel, uint8_t condition, uint16_t len );

/**
 * @brief ISM 5 write tx fifo function.
 * @details This function writes data to the TX FIFO buffer.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_write_tx_fifo ( ism5_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief ISM 5 start rx function.
 * @details This function starts the reception on the selected channel.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] channel : Channel number on which to receive data.
 * @param[in] condition : Condition byte (update rx parameters, start delay).
 * @param[in] len : Number of data bytes to receive (0 for a fixed packet length).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_start_rx ( ism5_t *ctx, uint8_t channel, uint8_t condition, uint16_t len );

/**
 * @brief ISM 5 read rx fifo function.
 * @details This function reads data from the RX FIFO buffer.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[out] data_out : Output data read.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_read_rx_fifo ( ism5_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief ISM 5 wait tx finish function.
 * @details This function waits for the device to exits TX state after transmission.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] timeout : Waiting timeout in milliseconds (scaled to 100ms).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_wait_tx_finish ( ism5_t *ctx, uint32_t timeout );

/**
 * @brief ISM 5 transmit packet function.
 * @details This function transmits a desired data packet on the selected channel.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] channel : Channel number on which to transmit data.
 * @param[in] data_in : Data to be transmitted.
 * @param[in] len : Number of data bytes to transmit (up to 64 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_transmit_packet ( ism5_t *ctx, uint8_t channel, uint8_t *data_in, uint8_t len );

/**
 * @brief ISM 5 receive packet function.
 * @details This function waits for a data packet to arrive on the selected channel and reads it.
 * @param[in] ctx : Click context object.
 * See #ism5_t object definition for detailed explanation.
 * @param[in] channel : Channel number on which to receive data (Required).
 * @param[out] data_out : Received data (Required).
 * @param[out] len : Number of data bytes that were available in RX FIFO (Optional).
 * @param[in] timeout : Waiting timeout in milliseconds (Required).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ism5_receive_packet ( ism5_t *ctx, uint8_t channel, uint8_t *data_out, uint8_t *len, uint32_t timeout );

#ifdef __cplusplus
}
#endif
#endif // ISM5_H

/*! @} */ // ism5

// ------------------------------------------------------------------------ END
