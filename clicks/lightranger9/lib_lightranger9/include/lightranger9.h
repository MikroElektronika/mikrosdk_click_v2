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
 * @file lightranger9.h
 * @brief This file contains API for LightRanger 9 Click Driver.
 */

#ifndef LIGHTRANGER9_H
#define LIGHTRANGER9_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup lightranger9 LightRanger 9 Click Driver
 * @brief API for configuring and manipulating LightRanger 9 Click driver.
 * @{
 */

/**
 * @defgroup lightranger9_reg LightRanger 9 Registers List
 * @brief List of registers of LightRanger 9 Click driver.
 */

/**
 * @addtogroup lightranger9_reg
 * @{
 */

/**
 * @brief LightRanger 9 always available registers list.
 * @details Specified always available registers list 
 * (any appid, any cid_rid) of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_REG_APPID                      0x00
#define LIGHTRANGER9_REG_MINOR                      0x01
#define LIGHTRANGER9_REG_ENABLE                     0xE0
#define LIGHTRANGER9_REG_INT_STATUS                 0xE1
#define LIGHTRANGER9_REG_INT_ENAB                   0xE2
#define LIGHTRANGER9_REG_ID                         0xE3
#define LIGHTRANGER9_REG_REVID                      0xE4

/**
 * @brief LightRanger 9 main application registers list.
 * @details Specified main application registers list 
 * (appid = 0x03, any cid_rid) of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_REG_PATCH                      0x02
#define LIGHTRANGER9_REG_BUILD_TYPE                 0x03
#define LIGHTRANGER9_REG_APPLICATION_STATUS         0x04
#define LIGHTRANGER9_REG_MEASURE_STATUS             0x05
#define LIGHTRANGER9_REG_ALGORITHM_STATUS           0x06
#define LIGHTRANGER9_REG_CALIBRATION_STATUS         0x07
#define LIGHTRANGER9_REG_CMD_STAT                   0x08
#define LIGHTRANGER9_REG_PREV_CMD                   0x09
#define LIGHTRANGER9_REG_MODE                       0x10
#define LIGHTRANGER9_REG_LIVE_BEAT                  0x0A
#define LIGHTRANGER9_REG_ACTIVE_RANGE               0x19
#define LIGHTRANGER9_REG_SERIAL_NUMBER_0            0x1C
#define LIGHTRANGER9_REG_SERIAL_NUMBER_1            0x1D
#define LIGHTRANGER9_REG_SERIAL_NUMBER_2            0x1E
#define LIGHTRANGER9_REG_SERIAL_NUMBER_3            0x1F
#define LIGHTRANGER9_REG_CONFIG_RESULT              0x20
#define LIGHTRANGER9_REG_TID                        0x21
#define LIGHTRANGER9_REG_SIZE_LSB                   0x22
#define LIGHTRANGER9_REG_SIZE_MSB                   0x23

/**
 * @brief LightRanger 9 measurements results registers list.
 * @details Specified measurements results registers list 
 * (appid = 0x03, cid_rid = 0x10) of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_REG_BLOCKREAD                  0x20
#define LIGHTRANGER9_REG_RESULT_NUMBER              0x24
#define LIGHTRANGER9_REG_TEMPERATURE                0x25
#define LIGHTRANGER9_REG_NUMBER_VALID_RESULTS       0x26
#define LIGHTRANGER9_REG_AMBIENT_LIGHT_0            0x28
#define LIGHTRANGER9_REG_AMBIENT_LIGHT_1            0x29
#define LIGHTRANGER9_REG_AMBIENT_LIGHT_2            0x2A
#define LIGHTRANGER9_REG_AMBIENT_LIGHT_3            0x2B
#define LIGHTRANGER9_REG_PHOTON_COUNT_0             0x2C
#define LIGHTRANGER9_REG_PHOTON_COUNT_1             0x2D
#define LIGHTRANGER9_REG_PHOTON_COUNT_2             0x2E
#define LIGHTRANGER9_REG_PHOTON_COUNT_3             0x2F
#define LIGHTRANGER9_REG_REFERENCE_COUNT_0          0x30
#define LIGHTRANGER9_REG_REFERENCE_COUNT_1          0x31
#define LIGHTRANGER9_REG_REFERENCE_COUNT_2          0x32
#define LIGHTRANGER9_REG_REFERENCE_COUNT_3          0x33
#define LIGHTRANGER9_REG_SYS_TICK_0                 0x34
#define LIGHTRANGER9_REG_SYS_TICK_1                 0x35
#define LIGHTRANGER9_REG_SYS_TICK_2                 0x36
#define LIGHTRANGER9_REG_SYS_TICK_3                 0x37
#define LIGHTRANGER9_REG_RES_CONFIDENCE_0           0x38
#define LIGHTRANGER9_REG_RES_DISTANCE_0_LSB         0x39
#define LIGHTRANGER9_REG_RES_DISTANCE_0_MSB         0x3A
#define LIGHTRANGER9_REG_RES_CONFIDENCE_1           0x3B
#define LIGHTRANGER9_REG_RES_DISTANCE_1_LSB         0x3C
#define LIGHTRANGER9_REG_RES_DISTANCE_1_MSB         0x3D
#define LIGHTRANGER9_REG_RES_CONFIDENCE_2           0x3E
#define LIGHTRANGER9_REG_RES_DISTANCE_2_LSB         0x3F
#define LIGHTRANGER9_REG_RES_DISTANCE_2_MSB         0x40
#define LIGHTRANGER9_REG_RES_CONFIDENCE_3           0x41
#define LIGHTRANGER9_REG_RES_DISTANCE_3_LSB         0x42
#define LIGHTRANGER9_REG_RES_DISTANCE_3_MSB         0x43
#define LIGHTRANGER9_REG_RES_CONFIDENCE_4           0x44
#define LIGHTRANGER9_REG_RES_DISTANCE_4_LSB         0x45
#define LIGHTRANGER9_REG_RES_DISTANCE_4_MSB         0x46
#define LIGHTRANGER9_REG_RES_CONFIDENCE_5           0x47
#define LIGHTRANGER9_REG_RES_DISTANCE_5_LSB         0x48
#define LIGHTRANGER9_REG_RES_DISTANCE_5_MSB         0x49
#define LIGHTRANGER9_REG_RES_CONFIDENCE_6           0x4A
#define LIGHTRANGER9_REG_RES_DISTANCE_6_LSB         0x4B
#define LIGHTRANGER9_REG_RES_DISTANCE_6_MSB         0x4C
#define LIGHTRANGER9_REG_RES_CONFIDENCE_7           0x4D
#define LIGHTRANGER9_REG_RES_DISTANCE_7_LSB         0x4E
#define LIGHTRANGER9_REG_RES_DISTANCE_7_MSB         0x4F
#define LIGHTRANGER9_REG_RES_CONFIDENCE_8           0x50
#define LIGHTRANGER9_REG_RES_DISTANCE_8_LSB         0x51
#define LIGHTRANGER9_REG_RES_DISTANCE_8_MSB         0x52
#define LIGHTRANGER9_REG_RES_CONFIDENCE_9           0x53
#define LIGHTRANGER9_REG_RES_DISTANCE_9_LSB         0x54
#define LIGHTRANGER9_REG_RES_DISTANCE_9_MSB         0x55
#define LIGHTRANGER9_REG_RES_CONFIDENCE_10          0x56
#define LIGHTRANGER9_REG_RES_DISTANCE_10_LSB        0x57
#define LIGHTRANGER9_REG_RES_DISTANCE_10_MSB        0x58
#define LIGHTRANGER9_REG_RES_CONFIDENCE_11          0x59
#define LIGHTRANGER9_REG_RES_DISTANCE_11_LSB        0x5A
#define LIGHTRANGER9_REG_RES_DISTANCE_11_MSB        0x5B
#define LIGHTRANGER9_REG_RES_CONFIDENCE_12          0x5C
#define LIGHTRANGER9_REG_RES_DISTANCE_12_LSB        0x5D
#define LIGHTRANGER9_REG_RES_DISTANCE_12_MSB        0x5E
#define LIGHTRANGER9_REG_RES_CONFIDENCE_13          0x5F
#define LIGHTRANGER9_REG_RES_DISTANCE_13_LSB        0x60
#define LIGHTRANGER9_REG_RES_DISTANCE_13_MSB        0x61
#define LIGHTRANGER9_REG_RES_CONFIDENCE_14          0x62
#define LIGHTRANGER9_REG_RES_DISTANCE_14_LSB        0x63
#define LIGHTRANGER9_REG_RES_DISTANCE_14_MSB        0x64
#define LIGHTRANGER9_REG_RES_CONFIDENCE_15          0x65
#define LIGHTRANGER9_REG_RES_DISTANCE_15_LSB        0x66
#define LIGHTRANGER9_REG_RES_DISTANCE_15_MSB        0x67
#define LIGHTRANGER9_REG_RES_CONFIDENCE_16          0x68
#define LIGHTRANGER9_REG_RES_DISTANCE_16_LSB        0x69
#define LIGHTRANGER9_REG_RES_DISTANCE_16_MSB        0x6A
#define LIGHTRANGER9_REG_RES_CONFIDENCE_17          0x6B
#define LIGHTRANGER9_REG_RES_DISTANCE_17_LSB        0x6C
#define LIGHTRANGER9_REG_RES_DISTANCE_17_MSB        0x6D
#define LIGHTRANGER9_REG_RES_CONFIDENCE_18          0x6E
#define LIGHTRANGER9_REG_RES_DISTANCE_18_LSB        0x6F
#define LIGHTRANGER9_REG_RES_DISTANCE_18_MSB        0x70
#define LIGHTRANGER9_REG_RES_CONFIDENCE_19          0x71
#define LIGHTRANGER9_REG_RES_DISTANCE_19_LSB        0x72
#define LIGHTRANGER9_REG_RES_DISTANCE_19_MSB        0x73
#define LIGHTRANGER9_REG_RES_CONFIDENCE_20          0x74
#define LIGHTRANGER9_REG_RES_DISTANCE_20_LSB        0x75
#define LIGHTRANGER9_REG_RES_DISTANCE_20_MSB        0x76
#define LIGHTRANGER9_REG_RES_CONFIDENCE_21          0x77
#define LIGHTRANGER9_REG_RES_DISTANCE_21_LSB        0x78
#define LIGHTRANGER9_REG_RES_DISTANCE_21_MSB        0x79
#define LIGHTRANGER9_REG_RES_CONFIDENCE_22          0x7A
#define LIGHTRANGER9_REG_RES_DISTANCE_22_LSB        0x7B
#define LIGHTRANGER9_REG_RES_DISTANCE_22_MSB        0x7C
#define LIGHTRANGER9_REG_RES_CONFIDENCE_23          0x7D
#define LIGHTRANGER9_REG_RES_DISTANCE_23_LSB        0x7E
#define LIGHTRANGER9_REG_RES_DISTANCE_23_MSB        0x7F
#define LIGHTRANGER9_REG_RES_CONFIDENCE_24          0x80
#define LIGHTRANGER9_REG_RES_DISTANCE_24_LSB        0x81
#define LIGHTRANGER9_REG_RES_DISTANCE_24_MSB        0x82
#define LIGHTRANGER9_REG_RES_CONFIDENCE_25          0x83
#define LIGHTRANGER9_REG_RES_DISTANCE_25_LSB        0x84
#define LIGHTRANGER9_REG_RES_DISTANCE_25_MSB        0x85
#define LIGHTRANGER9_REG_RES_CONFIDENCE_26          0x86
#define LIGHTRANGER9_REG_RES_DISTANCE_26_LSB        0x87
#define LIGHTRANGER9_REG_RES_DISTANCE_26_MSB        0x88
#define LIGHTRANGER9_REG_RES_CONFIDENCE_27          0x89
#define LIGHTRANGER9_REG_RES_DISTANCE_27_LSB        0x8A
#define LIGHTRANGER9_REG_RES_DISTANCE_27_MSB        0x8B
#define LIGHTRANGER9_REG_RES_CONFIDENCE_28          0x8C
#define LIGHTRANGER9_REG_RES_DISTANCE_28_LSB        0x8D
#define LIGHTRANGER9_REG_RES_DISTANCE_28_MSB        0x8E
#define LIGHTRANGER9_REG_RES_CONFIDENCE_29          0x8F
#define LIGHTRANGER9_REG_RES_DISTANCE_29_LSB        0x90
#define LIGHTRANGER9_REG_RES_DISTANCE_29_MSB        0x91
#define LIGHTRANGER9_REG_RES_CONFIDENCE_30          0x92
#define LIGHTRANGER9_REG_RES_DISTANCE_30_LSB        0x93
#define LIGHTRANGER9_REG_RES_DISTANCE_30_MSB        0x94
#define LIGHTRANGER9_REG_RES_CONFIDENCE_31          0x95
#define LIGHTRANGER9_REG_RES_DISTANCE_31_LSB        0x96
#define LIGHTRANGER9_REG_RES_DISTANCE_31_MSB        0x97
#define LIGHTRANGER9_REG_RES_CONFIDENCE_32          0x98
#define LIGHTRANGER9_REG_RES_DISTANCE_32_LSB        0x99
#define LIGHTRANGER9_REG_RES_DISTANCE_32_MSB        0x9A
#define LIGHTRANGER9_REG_RES_CONFIDENCE_33          0x9B
#define LIGHTRANGER9_REG_RES_DISTANCE_33_LSB        0x9C
#define LIGHTRANGER9_REG_RES_DISTANCE_33_MSB        0x9D
#define LIGHTRANGER9_REG_RES_CONFIDENCE_34          0x9E
#define LIGHTRANGER9_REG_RES_DISTANCE_34_LSB        0x9F
#define LIGHTRANGER9_REG_RES_DISTANCE_34_MSB        0xA0
#define LIGHTRANGER9_REG_RES_CONFIDENCE_35          0xA1
#define LIGHTRANGER9_REG_RES_DISTANCE_35_LSB        0xA2
#define LIGHTRANGER9_REG_RES_DISTANCE_35_MSB        0xA3

/**
 * @brief LightRanger 9 configuration page registers list.
 * @details Specified configuration page registers list 
 * (appid = 0x03, cid_rid = 0x16) of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_REG_PERIOD_MS_LSB              0x24
#define LIGHTRANGER9_REG_PERIOD_MS_MSB              0x25
#define LIGHTRANGER9_REG_KILO_ITERATIONS_LSB        0x26
#define LIGHTRANGER9_REG_KILO_ITERATIONS_MSB        0x27
#define LIGHTRANGER9_REG_INT_THRESHOLD_LOW_LSB      0x28
#define LIGHTRANGER9_REG_INT_THRESHOLD_LOW_MSB      0x29
#define LIGHTRANGER9_REG_INT_THRESHOLD_HIGH_LSB     0x2A
#define LIGHTRANGER9_REG_INT_THRESHOLD_HIGH_MSB     0x2B
#define LIGHTRANGER9_REG_INT_ZONE_MASK_0            0x2C
#define LIGHTRANGER9_REG_INT_ZONE_MASK_1            0x2D
#define LIGHTRANGER9_REG_INT_ZONE_MASK_2            0x2E
#define LIGHTRANGER9_REG_INT_PERSISTANCE            0x2F
#define LIGHTRANGER9_REG_CONFIDENCE_THRESHOLD       0x30
#define LIGHTRANGER9_REG_GPIO_0                     0x31
#define LIGHTRANGER9_REG_GPIO_1                     0x32
#define LIGHTRANGER9_REG_POWER_CFG                  0x33
#define LIGHTRANGER9_REG_SPAD_MAP_ID                0x34
#define LIGHTRANGER9_REG_ALG_SETTING_0              0x35
#define LIGHTRANGER9_REG_HIST_DUMP                  0x39
#define LIGHTRANGER9_REG_SPREAD_SPECTRUM            0x3A
#define LIGHTRANGER9_REG_I2C_SLAVE_ADDRESS          0x3B
#define LIGHTRANGER9_REG_OSC_TRIM_VALUE_LSB         0x3C
#define LIGHTRANGER9_REG_OSC_TRIM_VALUE_MSB         0x3D
#define LIGHTRANGER9_REG_I2C_ADDR_CHANGE            0x3E

/**
 * @brief LightRanger 9 user defined SPAD configuration registers list.
 * @details Specified user defined SPAD configuration registers list 
 * (appid = 0x03, cid_rid = 0x17/0x18) of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_REG_SPAD_ENABLE_FIRST          0x24
#define LIGHTRANGER9_REG_SPAD_ENABLE_LAST           0x41
#define LIGHTRANGER9_REG_SPAD_TDC_FIRST             0x42
#define LIGHTRANGER9_REG_SPAD_TDC_LAST              0x8C
#define LIGHTRANGER9_REG_SPAD_X_OFFSET_2            0x8D
#define LIGHTRANGER9_REG_SPAD_Y_OFFSET_2            0x8E
#define LIGHTRANGER9_REG_SPAD_X_SIZE                0x8F
#define LIGHTRANGER9_REG_SPAD_Y_SIZE                0x90

/**
 * @brief LightRanger 9 factory calibration registers list.
 * @details Specified factory calibration registers list 
 * (appid = 0x03, cid_rid = 0x19) of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_REG_FACTORY_CALIBRATION_FIRST  0x24
#define LIGHTRANGER9_REG_CROSSTALK_ZONE1            0x60
#define LIGHTRANGER9_REG_CROSSTALK_ZONE2            0x64
#define LIGHTRANGER9_REG_CROSSTALK_ZONE3            0x68
#define LIGHTRANGER9_REG_CROSSTALK_ZONE4            0x6C
#define LIGHTRANGER9_REG_CROSSTALK_ZONE5            0x70
#define LIGHTRANGER9_REG_CROSSTALK_ZONE6            0x74
#define LIGHTRANGER9_REG_CROSSTALK_ZONE7            0x78
#define LIGHTRANGER9_REG_CROSSTALK_ZONE8            0x7C
#define LIGHTRANGER9_REG_CROSSTALK_ZONE9            0x80
#define LIGHTRANGER9_REG_CROSSTALK_ZONE1_TMUX       0xB8
#define LIGHTRANGER9_REG_CROSSTALK_ZONE2_TMUX       0xBC
#define LIGHTRANGER9_REG_CROSSTALK_ZONE3_TMUX       0xC0
#define LIGHTRANGER9_REG_CROSSTALK_ZONE4_TMUX       0xC4
#define LIGHTRANGER9_REG_CROSSTALK_ZONE5_TMUX       0xC8
#define LIGHTRANGER9_REG_CROSSTALK_ZONE6_TMUX       0xCC
#define LIGHTRANGER9_REG_CROSSTALK_ZONE7_TMUX       0xD0
#define LIGHTRANGER9_REG_CROSSTALK_ZONE8_TMUX       0xD4
#define LIGHTRANGER9_REG_CROSSTALK_ZONE9_TMUX       0xD8
#define LIGHTRANGER9_REG_CALIBRATION_STATUS_FC      0xDC
#define LIGHTRANGER9_REG_FACTORY_CALIBRATION_LAST   0xDF

/**
 * @brief LightRanger 9 raw data histograms registers list.
 * @details Specified raw data histograms registers list 
 * (appid = 0x03, cid_rid = 0x81) of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_REG_SUBPACKET_NUMBER           0x24
#define LIGHTRANGER9_REG_SUBPACKET_PAYLOAD          0x25
#define LIGHTRANGER9_REG_SUBPACKET_CONFIG           0x26
#define LIGHTRANGER9_REG_SUBPACKET_DATA0            0x27
#define LIGHTRANGER9_REG_SUBPACKET_DATA127          0xA6

/**
 * @brief LightRanger 9 bootloader registers list.
 * @details Specified bootloader registers list 
 * (appid = 0x80) of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_REG_BL_CMD_STAT                0x08
#define LIGHTRANGER9_REG_BL_SIZE                    0x09
#define LIGHTRANGER9_REG_BL_DATA                    0x0A

/*! @} */ // lightranger9_reg

/**
 * @defgroup lightranger9_set LightRanger 9 Registers Settings
 * @brief Settings for registers of LightRanger 9 Click driver.
 */

/**
 * @addtogroup lightranger9_set
 * @{
 */

/**
 * @brief LightRanger 9 timeout value.
 * @details Specified timeout value of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_TIMEOUT                        5000

/**
 * @brief LightRanger 9 enable register settings.
 * @details Specified enable register settings of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_ENABLE_CPU_READY               0x40
#define LIGHTRANGER9_ENABLE_POWERUP_BL              0x00
#define LIGHTRANGER9_ENABLE_POWERUP_BL_NO_SLP       0x10
#define LIGHTRANGER9_ENABLE_POWERUP_RAM             0x20
#define LIGHTRANGER9_ENABLE_PON                     0x01

/**
 * @brief LightRanger 9 int enable register settings.
 * @details Specified int enable register settings of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_INT_ENAB_REG_STATUS            0x40
#define LIGHTRANGER9_INT_ENAB_COMMAND               0x20
#define LIGHTRANGER9_INT_ENAB_HIST_READY            0x08
#define LIGHTRANGER9_INT_ENAB_MEAS_READY            0x02

/**
 * @brief LightRanger 9 int status register settings.
 * @details Specified int status register settings of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_INT_STATUS_REG_STATUS          0x40
#define LIGHTRANGER9_INT_STATUS_COMMAND             0x20
#define LIGHTRANGER9_INT_STATUS_HIST_READY          0x08
#define LIGHTRANGER9_INT_STATUS_MEAS_READY          0x02

/**
 * @brief LightRanger 9 cmd stat register write settings.
 * @details Specified cmd stat register write settings of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_CMD_STAT_MEASURE               0x10
#define LIGHTRANGER9_CMD_STAT_CLEAR_STATUS          0x11
#define LIGHTRANGER9_CMD_STAT_GPIO                  0x12
#define LIGHTRANGER9_CMD_STAT_WRITE_CFG_PAGE        0x15
#define LIGHTRANGER9_CMD_STAT_LOAD_CFG_PAGE_COMMON  0x16
#define LIGHTRANGER9_CMD_STAT_LOAD_CFG_PAGE_SPAD_1  0x17
#define LIGHTRANGER9_CMD_STAT_LOAD_CFG_PAGE_SPAD_2  0x18
#define LIGHTRANGER9_CMD_STAT_LOAD_CFG_PAGE_F_Y_CAL 0x19
#define LIGHTRANGER9_CMD_STAT_FACTORY_CALIBRATION   0x20
#define LIGHTRANGER9_CMD_STAT_I2C_SLAVE_ADDRESS     0x21
#define LIGHTRANGER9_CMD_STAT_FORCE_TMF8820         0x65
#define LIGHTRANGER9_CMD_STAT_FORCE_TMF8828         0x6C
#define LIGHTRANGER9_CMD_STAT_RESET                 0xFE
#define LIGHTRANGER9_CMD_STAT_STOP                  0xFF

/**
 * @brief LightRanger 9 cmd stat register read settings.
 * @details Specified cmd stat register read settings of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_CMD_STAT_OK                    0x00
#define LIGHTRANGER9_CMD_STAT_ACCEPTED              0x01
#define LIGHTRANGER9_CMD_ERR_CONFIG                 0x02
#define LIGHTRANGER9_CMD_ERR_APPLICATION            0x03
#define LIGHTRANGER9_CMD_ERR_WAKEUP_TIMED           0x04
#define LIGHTRANGER9_CMD_ERR_RESET_UNEXPECTED       0x05
#define LIGHTRANGER9_CMD_ERR_UNKNOWN_CMD            0x06
#define LIGHTRANGER9_CMD_ERR_NO_REF_SPAD            0x07
#define LIGHTRANGER9_CMD_ERR_UNKNOWN_CID            0x09
#define LIGHTRANGER9_CMD_WARNING_CFG_SPAD_1         0x0A
#define LIGHTRANGER9_CMD_WARNING_CFG_SPAD_2         0x0B
#define LIGHTRANGER9_CMD_WARNING_OSC_TRIP           0x0C
#define LIGHTRANGER9_CMD_WARNING_I2C_ADDRESS        0x0D
#define LIGHTRANGER9_CMD_ERR_UNKNOWN_MODE           0x0E

/**
 * @brief LightRanger 9 config result register settings.
 * @details Specified config result register settings of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_CONFIG_RESULT_MEAS             0x10
#define LIGHTRANGER9_CONFIG_RESULT_COMMON_CID       0x16
#define LIGHTRANGER9_CONFIG_RESULT_SPAD_1_CID       0x17
#define LIGHTRANGER9_CONFIG_RESULT_SPAD_2_CID       0x18
#define LIGHTRANGER9_CONFIG_RESULT_FAC_CALIB_CID    0x19
#define LIGHTRANGER9_CONFIG_RESULT_HIST_RAW_CID     0x81

/**
 * @brief LightRanger 9 bootloader commands list.
 * @details Specified bootloader commands list of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_BL_CMD_RAMREMAP_RESET          0x11
#define LIGHTRANGER9_BL_CMD_DOWNLOAD_INIT           0x14
#define LIGHTRANGER9_BL_CMD_RAM_BIST                0x2A
#define LIGHTRANGER9_BL_CMD_I2C_BIST                0x2C
#define LIGHTRANGER9_BL_CMD_W_RAM                   0x41
#define LIGHTRANGER9_BL_CMD_ADDR_RAM                0x43

/**
 * @brief LightRanger 9 bootloader commands status list.
 * @details Specified bootloader commands status list of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_BL_CMD_STAT_READY              0x00
#define LIGHTRANGER9_BL_CMD_STAT_ERR_SIZE           0x01
#define LIGHTRANGER9_BL_CMD_STAT_ERR_CSUM           0x02
#define LIGHTRANGER9_BL_CMD_STAT_ERR_RANGE          0x03
#define LIGHTRANGER9_BL_CMD_STAT_ERR_MORE           0x04

/**
 * @brief LightRanger 9 app id settings.
 * @details Specified app id settings of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_APP_ID_BOOTLOADER              0x80
#define LIGHTRANGER9_APP_ID_MEASUREMENT             0x03

/**
 * @brief LightRanger 9 capture settings.
 * @details Specified capture settings of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_BLOCKREAD_SIZE                 132
#define LIGHTRANGER9_MAX_MEAS_RESULTS               36
#define LIGHTRANGER9_SUBCAPTURE_0                   0
#define LIGHTRANGER9_SUBCAPTURE_1                   1
#define LIGHTRANGER9_SUBCAPTURE_2                   2
#define LIGHTRANGER9_SUBCAPTURE_3                   3
#define LIGHTRANGER9_SUBCAPTURE_MASK                0x03
#define LIGHTRANGER9_RESULT_NUMBER_MASK             0x3F
#define LIGHTRANGER9_SYS_TICK_TO_SEC                0.0000002
#define LIGHTRANGER9_OBJECT_MAP_SIZE                64

/**
 * @brief LightRanger 9 default measurement period and confidence threshold.
 * @details Specified default measurement period and confidence threshold of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_DEFAULT_MEASUREMENT_PERIOD_MS  500
#define LIGHTRANGER9_CONFIDENCE_THRESHOLD           100

/**
 * @brief LightRanger 9 device ID value.
 * @details Specified device ID value of LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_DEVICE_ID                      0x08

/**
 * @brief LightRanger 9 device address setting.
 * @details Specified setting for device slave address selection of
 * LightRanger 9 Click driver.
 */
#define LIGHTRANGER9_DEVICE_ADDRESS                 0x41

/*! @} */ // lightranger9_set

/**
 * @defgroup lightranger9_map LightRanger 9 MikroBUS Map
 * @brief MikroBUS pin mapping of LightRanger 9 Click driver.
 */

/**
 * @addtogroup lightranger9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LightRanger 9 Click to the selected MikroBUS.
 */
#define LIGHTRANGER9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.gpio0 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.gpio1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // lightranger9_map
/*! @} */ // lightranger9

/**
 * @brief LightRanger 9 Click context object.
 * @details Context object definition of LightRanger 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (Active High). */
    digital_out_t gpio0;        /**< GPIO 0 pin. */
    digital_out_t gpio1;        /**< GPIO 1 pin. */

    // Input pins
    digital_in_t  int_pin;      /**< Interrupt pin. */

    // Modules
    i2c_master_t  i2c;          /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} lightranger9_t;

/**
 * @brief LightRanger 9 Click configuration object.
 * @details Configuration object definition of LightRanger 9 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;             /**< Enable pin (Active High). */
    pin_name_t  gpio0;          /**< GPIO 0 pin. */
    pin_name_t  gpio1;          /**< GPIO 1 pin. */
    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} lightranger9_cfg_t;

/**
 * @brief LightRanger 9 measurement result data object.
 * @details Measurement result data object definition of LightRanger 9 Click driver.
 */
typedef struct
{
    uint8_t confidence;
    uint16_t distance_mm;

} lightranger9_meas_result_t;

/**
 * @brief LightRanger 9 capture data object.
 * @details Capture data object definition of LightRanger 9 Click driver.
 */
typedef struct
{
    uint8_t sub_capture;
    uint8_t result_number;
    int8_t temperature;
    uint8_t valid_results;
    uint32_t ambient_light;
    uint32_t photon_count;
    uint32_t reference_count;
    float sys_tick_sec;
    lightranger9_meas_result_t result[ LIGHTRANGER9_MAX_MEAS_RESULTS ];

} lightranger9_capture_t;

/**
 * @brief LightRanger 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LIGHTRANGER9_OK = 0,
    LIGHTRANGER9_ERROR = -1

} lightranger9_return_value_t;

/*!
 * @addtogroup lightranger9 LightRanger 9 Click Driver
 * @brief API for configuring and manipulating LightRanger 9 Click driver.
 * @{
 */

/**
 * @brief LightRanger 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lightranger9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lightranger9_cfg_setup ( lightranger9_cfg_t *cfg );

/**
 * @brief LightRanger 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lightranger9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger9_init ( lightranger9_t *ctx, lightranger9_cfg_t *cfg );

/**
 * @brief LightRanger 9 default configuration function.
 * @details This function executes a default configuration of LightRanger 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lightranger9_default_cfg ( lightranger9_t *ctx );

/**
 * @brief LightRanger 9 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger9_generic_write ( lightranger9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LightRanger 9 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger9_generic_read ( lightranger9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LightRanger 9 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger9_write_register ( lightranger9_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief LightRanger 9 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger9_read_register ( lightranger9_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief LightRanger 9 write bl cmd function.
 * @details This function writes a desired number of data bytes to the selected bootloader command
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger9_write_bl_cmd ( lightranger9_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief LightRanger 9 read bl cmd status function.
 * @details This function reads a bootloader command status by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @param[out] status : Bootloader command status byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger9_read_bl_cmd_status ( lightranger9_t *ctx, uint8_t *status );

/**
 * @brief LightRanger 9 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger9_check_communication ( lightranger9_t *ctx );

/**
 * @brief LightRanger 9 set gpio0 pin function.
 * @details This function sets the GPIO 0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lightranger9_set_gpio0_pin ( lightranger9_t *ctx, uint8_t state );

/**
 * @brief LightRanger 9 set gpio1 pin function.
 * @details This function sets the GPIO 1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lightranger9_set_gpio1_pin ( lightranger9_t *ctx, uint8_t state );

/**
 * @brief LightRanger 9 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger9_enable_device ( lightranger9_t *ctx );

/**
 * @brief LightRanger 9 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lightranger9_disable_device ( lightranger9_t *ctx );

/**
 * @brief LightRanger 9 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lightranger9_get_int_pin ( lightranger9_t *ctx );

/**
 * @brief LightRanger 9 download fw bin function.
 * @details This function checks if the bootloader is running and then writes 
 * the @b tof_bin_image FW image to the device.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger9_download_fw_bin ( lightranger9_t *ctx );

/**
 * @brief LightRanger 9 clear interrupts function.
 * @details This function reads and clears the interrupt status register.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lightranger9_clear_interrupts ( lightranger9_t *ctx );

/**
 * @brief LightRanger 9 get capture function.
 * @details This function reads and parses a single sub-capture block of 132 bytes.
 * @param[in] ctx : Click context object.
 * See #lightranger9_t object definition for detailed explanation.
 * @param[out] capture : Capture data object.
 * See #lightranger9_capture_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Increase the @b LIGHTRANGER9_CONFIDENCE_THRESHOLD in order to improve the distance measurement accuracy.
 */
err_t lightranger9_get_capture ( lightranger9_t *ctx, lightranger9_capture_t *capture );

#ifdef __cplusplus
}
#endif
#endif // LIGHTRANGER9_H

/*! @} */ // lightranger9

// ------------------------------------------------------------------------ END
