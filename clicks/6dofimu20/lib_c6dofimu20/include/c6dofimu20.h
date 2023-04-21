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
 * @file c6dofimu20.h
 * @brief This file contains API for 6 DOF IMU 20 Click Driver.
 */

#ifndef C6DOFIMU20_H
#define C6DOFIMU20_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup c6dofimu20 6 DOF IMU 20 Click Driver
 * @brief API for configuring and manipulating 6 DOF IMU 20 Click driver.
 * @{
 */

/**
 * @defgroup c6dofimu20_reg 6 DOF IMU 20 Registers List
 * @brief List of registers of 6 DOF IMU 20 Click driver.
 */

/**
 * @addtogroup c6dofimu20_reg
 * @{
 */

/**
 * @brief 6 DOF IMU 20 description register.
 * @details Specified register for description of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_REG_CHIP_ID                          0x00
#define C6DOFIMU20_REG_ERR                              0x01
#define C6DOFIMU20_REG_STATUS                           0x02
#define C6DOFIMU20_REG_ACC_DATA_X                       0x03
#define C6DOFIMU20_REG_ACC_DATA_Y                       0x04
#define C6DOFIMU20_REG_ACC_DATA_Z                       0x05
#define C6DOFIMU20_REG_GYR_DATA_X                       0x06
#define C6DOFIMU20_REG_GYR_DATA_Y                       0x07
#define C6DOFIMU20_REG_GYR_DATA_Z                       0x08
#define C6DOFIMU20_REG_TEMP_DATA                        0x09
#define C6DOFIMU20_REG_SENSOR_TIME_0                    0x0A
#define C6DOFIMU20_REG_SENSOR_TIME_1                    0x0B
#define C6DOFIMU20_REG_SAT_FLAGS                        0x0C
#define C6DOFIMU20_REG_INT_STATUS_INT1                  0x0D
#define C6DOFIMU20_REG_INT_STATUS_INT2                  0x0E
#define C6DOFIMU20_REG_INT_STATUS_IBI                   0x0F
#define C6DOFIMU20_REG_FEATURE_IO0                      0x10
#define C6DOFIMU20_REG_FEATURE_IO1                      0x11
#define C6DOFIMU20_REG_FEATURE_IO2                      0x12
#define C6DOFIMU20_REG_FEATURE_IO3                      0x13
#define C6DOFIMU20_REG_FEATURE_IO_STATUS                0x14
#define C6DOFIMU20_REG_FIFO_FILL_LEVEL                  0x15
#define C6DOFIMU20_REG_FIFO_DATA                        0x16
#define C6DOFIMU20_REG_ACC_CONF                         0x20
#define C6DOFIMU20_REG_GYR_CONF                         0x21
#define C6DOFIMU20_REG_ALT_ACC_CONF                     0x28
#define C6DOFIMU20_REG_ALT_GYR_CONF                     0x29
#define C6DOFIMU20_REG_ALT_CONF                         0x2A
#define C6DOFIMU20_REG_ALT_STATUS                       0x2B
#define C6DOFIMU20_REG_FIFO_WATERMARK                   0x35
#define C6DOFIMU20_REG_FIFO_CONF                        0x36
#define C6DOFIMU20_REG_FIFO_CTRL                        0x37
#define C6DOFIMU20_REG_IO_INT_CTRL                      0x38
#define C6DOFIMU20_REG_INT_CONF                         0x39
#define C6DOFIMU20_REG_INT_MAP1                         0x3A
#define C6DOFIMU20_REG_INT_MAP2                         0x3B
#define C6DOFIMU20_REG_FEATURE_CTRL                     0x40
#define C6DOFIMU20_REG_FEATURE_DATA_ADDR                0x41
#define C6DOFIMU20_REG_FEATURE_DATA_TX                  0x42
#define C6DOFIMU20_REG_FEATURE_DATA_STATUS              0x43
#define C6DOFIMU20_REG_FEATURE_ENGINE_STATUS            0x45
#define C6DOFIMU20_REG_FEATURE_EVENT_EXT                0x47
#define C6DOFIMU20_REG_IO_PDN_CTRL                      0x4F
#define C6DOFIMU20_REG_IO_SPI_IF                        0x50
#define C6DOFIMU20_REG_IO_PAD_STRENGTH                  0x51
#define C6DOFIMU20_REG_IO_I2C_IF                        0x52
#define C6DOFIMU20_REG_IO_ODR_DEVIATION                 0x53
#define C6DOFIMU20_REG_ACC_DP_OFF_X                     0x60
#define C6DOFIMU20_REG_ACC_DP_DGAIN_X                   0x61
#define C6DOFIMU20_REG_ACC_DP_OFF_Y                     0x62
#define C6DOFIMU20_REG_ACC_DP_DGAIN_Y                   0x63
#define C6DOFIMU20_REG_ACC_DP_OFF_Z                     0x64
#define C6DOFIMU20_REG_ACC_DP_DGAIN_Z                   0x65
#define C6DOFIMU20_REG_GYR_DP_OFF_X                     0x66
#define C6DOFIMU20_REG_GYR_DP_DGAIN_X                   0x67
#define C6DOFIMU20_REG_GYR_DP_OFF_Y                     0x68
#define C6DOFIMU20_REG_GYR_DP_DGAIN_Y                   0x69
#define C6DOFIMU20_REG_GYR_DP_OFF_Z                     0x6A
#define C6DOFIMU20_REG_GYR_DP_DGAIN_Z                   0x6B
#define C6DOFIMU20_REG_CMD                              0x7E
#define C6DOFIMU20_REG_CFG_RES                          0x7F

/**
 * @brief 6 DOF IMU 20 extended register.
 * @details Specified extended register for description of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_REG_SC_ST_VALUE4                     0x2C
#define C6DOFIMU20_REG_SC_ST_VALUE3                     0x2B
#define C6DOFIMU20_REG_SC_ST_VALUE2                     0x2A
#define C6DOFIMU20_REG_SC_ST_VALUE1                     0x29
#define C6DOFIMU20_REG_SC_ST_VALUE0                     0x28
#define C6DOFIMU20_REG_GYR_SC_ST_CONF_RE                0x27
#define C6DOFIMU20_REG_GYR_SC_SELECT                    0x26
#define C6DOFIMU20_REG_ST_SELECT                        0x25
#define C6DOFIMU20_REG_ST_RESULT                        0x24
#define C6DOFIMU20_REG_ALT_CONFIG_CHG                   0x23
#define C6DOFIMU20_REG_TILT_2                           0x22
#define C6DOFIMU20_REG_TILT_1                           0x21
#define C6DOFIMU20_REG_TAP_3                            0x20
#define C6DOFIMU20_REG_TAP_2                            0x1F
#define C6DOFIMU20_REG_TAP_1                            0x1E
#define C6DOFIMU20_REG_ORIENT_2                         0x1D
#define C6DOFIMU20_REG_ORIENT_1                         0x1C
#define C6DOFIMU20_REG_SC_12                            0x1B
#define C6DOFIMU20_REG_SC_11                            0x1A
#define C6DOFIMU20_REG_SC_10                            0x19
#define C6DOFIMU20_REG_SC_9                             0x18
#define C6DOFIMU20_REG_SC_8                             0x17
#define C6DOFIMU20_REG_SC_7                             0x16
#define C6DOFIMU20_REG_SC_6                             0x15
#define C6DOFIMU20_REG_SC_5                             0x14
#define C6DOFIMU20_REG_SC_4                             0x13
#define C6DOFIMU20_REG_SC_3                             0x12
#define C6DOFIMU20_REG_SC_2                             0x11
#define C6DOFIMU20_REG_SC_1                             0x10
#define C6DOFIMU20_REG_SIGMO_3                          0x0F
#define C6DOFIMU20_REG_SIGMO_2                          0x0E
#define C6DOFIMU20_REG_SIGMO_1                          0x0D
#define C6DOFIMU20_REG_FLAT_2                           0x0C
#define C6DOFIMU20_REG_FLAT_1                           0x0B
#define C6DOFIMU20_REG_MOMO_3                           0x0A
#define C6DOFIMU20_REG_MOMO_2                           0x09
#define C6DOFIMU20_REG_MOMO_1                           0x08
#define C6DOFIMU20_REG_ANYMO_3                          0x07
#define C6DOFIMU20_REG_ANYMO_2                          0x06
#define C6DOFIMU20_REG_ANYMO_1                          0x05
#define C6DOFIMU20_REG_AXIS_MAP_1                       0x03
#define C6DOFIMU20_REG_GEN_SET_1                        0x02

/*! @} */ // c6dofimu20_reg

/**
 * @defgroup c6dofimu20_set 6 DOF IMU 20 Registers Settings
 * @brief Settings for registers of 6 DOF IMU 20 Click driver.
 */

/**
 * @addtogroup c6dofimu20_set
 * @{
 */

/**
 * @brief 6 DOF IMU 20 description setting.
 * @details Specified setting for description of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_SW_RESET_CMD                         0xDEAF

/**
 * @brief 6 DOF IMU 20 ERR register setting.
 * @details Specified ERR register setting of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_REG_ERR_FATAL_ERR_FLAG               0x0001
#define C6DOFIMU20_REG_ERR_FEAT_ENG_OVRLD_FLAG          0x0004
#define C6DOFIMU20_REG_ERR_ACC_CONF_ERR_FLAG            0x0020
#define C6DOFIMU20_REG_ERR_GYR_CONF_ERR_FLAG            0x0040

/**
 * @brief 6 DOF IMU 20 STATUS register setting.
 * @details Specified STATUS register setting of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_STATUS_POR_DETECTED_FLAG             0x0001
#define C6DOFIMU20_STATUS_DRDY_TEMP_FLAG                0x0020
#define C6DOFIMU20_STATUS_DRDY_GYR_FLAG                 0x0040
#define C6DOFIMU20_STATUS_DRDY_ACC_FLAG                 0x0080

/**
 * @brief 6 DOF IMU 20 SAT_FLAGS register setting.
 * @details Specified SAT_FLAGS register setting of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_SAT_FLAGS_SATF_ACC_X_FLAG            0x0001
#define C6DOFIMU20_SAT_FLAGS_SATF_ACC_Y_FLAG            0x0002
#define C6DOFIMU20_SAT_FLAGS_SATF_ACC_Z_FLAG            0x0004
#define C6DOFIMU20_SAT_FLAGS_SATF_GYR_X_FLAG            0x0008
#define C6DOFIMU20_SAT_FLAGS_SATF_GYR_Y_FLAG            0x0010
#define C6DOFIMU20_SAT_FLAGS_SATF_GYR_Z_FLAG            0x0020

/**
 * @brief 6 DOF IMU 20 INT_STATUS_INT1 register setting.
 * @details Specified INT_STATUS_INT1 register setting of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_INT_STATUS_INT1_NO_MOTION            0x0001
#define C6DOFIMU20_INT_STATUS_INT1_ANY_MOTION           0x0002
#define C6DOFIMU20_INT_STATUS_INT1_FLAT                 0x0004
#define C6DOFIMU20_INT_STATUS_INT1_ORIENTATION          0x0008
#define C6DOFIMU20_INT_STATUS_INT1_STEP_DETECTOR        0x0010
#define C6DOFIMU20_INT_STATUS_INT1_STEP_COUNTER         0x0020
#define C6DOFIMU20_INT_STATUS_INT1_SIG_MOTION           0x0040
#define C6DOFIMU20_INT_STATUS_INT1_TILT                 0x0080
#define C6DOFIMU20_INT_STATUS_INT1_TAP                  0x0100
#define C6DOFIMU20_INT_STATUS_INT1_ERR_STATUS           0x0400
#define C6DOFIMU20_INT_STATUS_INT1_TEMP_DRDY            0x0800
#define C6DOFIMU20_INT_STATUS_INT1_GYR_DRDY             0x1000
#define C6DOFIMU20_INT_STATUS_INT1_ACC_DRDY             0x2000
#define C6DOFIMU20_INT_STATUS_INT1_FWM                  0x4000
#define C6DOFIMU20_INT_STATUS_INT1_FFULL                0x8000

/**
 * @brief 6 DOF IMU 20 INT_STATUS_INT2 register setting.
 * @details Specified INT_STATUS_INT2 register setting of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_INT_STATUS_INT2_NO_MOTION            0x0001
#define C6DOFIMU20_INT_STATUS_INT2_ANY_MOTION           0x0002
#define C6DOFIMU20_INT_STATUS_INT2_FLAT                 0x0004
#define C6DOFIMU20_INT_STATUS_INT2_ORIENTATION          0x0008
#define C6DOFIMU20_INT_STATUS_INT2_STEP_DETECTOR        0x0010
#define C6DOFIMU20_INT_STATUS_INT2_STEP_COUNTER         0x0020
#define C6DOFIMU20_INT_STATUS_INT2_SIG_MOTION           0x0040
#define C6DOFIMU20_INT_STATUS_INT2_TILT                 0x0080
#define C6DOFIMU20_INT_STATUS_INT2_TAP                  0x0100
#define C6DOFIMU20_INT_STATUS_INT2_ERR_STATUS           0x0400
#define C6DOFIMU20_INT_STATUS_INT2_TEMP_DRDY            0x0800
#define C6DOFIMU20_INT_STATUS_INT2_GYR_DRDY             0x1000
#define C6DOFIMU20_INT_STATUS_INT2_ACC_DRDY             0x2000
#define C6DOFIMU20_INT_STATUS_INT2_FWM                  0x4000
#define C6DOFIMU20_INT_STATUS_INT2_FFULL                0x8000

/**
 * @brief 6 DOF IMU 20 ACC_CONF register setting.
 * @details Specified ACC_CONF register setting of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_ACC_CONF_ODR_0POINT78125_Hz          0x0001
#define C6DOFIMU20_ACC_CONF_ODR_1POINT5625_Hz           0x0002
#define C6DOFIMU20_ACC_CONF_ODR_3POINT125_Hz            0x0003
#define C6DOFIMU20_ACC_CONF_ODR_6POINT25_Hz             0x0004
#define C6DOFIMU20_ACC_CONF_ODR_12POINT5_Hz             0x0005
#define C6DOFIMU20_ACC_CONF_ODR_25_Hz                   0x0006
#define C6DOFIMU20_ACC_CONF_ODR_50_Hz                   0x0007
#define C6DOFIMU20_ACC_CONF_ODR_100_Hz                  0x0008
#define C6DOFIMU20_ACC_CONF_ODR_200_Hz                  0x0009
#define C6DOFIMU20_ACC_CONF_ODR_400_Hz                  0x000A
#define C6DOFIMU20_ACC_CONF_ODR_800_Hz                  0x000B
#define C6DOFIMU20_ACC_CONF_ODR_1POINT6_kHz             0x000C
#define C6DOFIMU20_ACC_CONF_ODR_3POINT2_kHz             0x000D
#define C6DOFIMU20_ACC_CONF_ODR_6POINT4_kHz             0x000E
#define C6DOFIMU20_ACC_CONF_ACC_RANGE_2G                0x0000
#define C6DOFIMU20_ACC_CONF_ACC_RANGE_4G                0x0010
#define C6DOFIMU20_ACC_CONF_ACC_RANGE_8G                0x0020
#define C6DOFIMU20_ACC_CONF_ACC_RANGE_16G               0x0030
#define C6DOFIMU20_ACC_CONF_ACC_BW_DIV_2                0x0000
#define C6DOFIMU20_ACC_CONF_ACC_BW_DIV_4                0x0080
#define C6DOFIMU20_ACC_CONF_ACC_AVG_NUM_0               0x0000
#define C6DOFIMU20_ACC_CONF_ACC_AVG_NUM_2               0x0100
#define C6DOFIMU20_ACC_CONF_ACC_AVG_NUM_4               0x0200
#define C6DOFIMU20_ACC_CONF_ACC_AVG_NUM_8               0x0300
#define C6DOFIMU20_ACC_CONF_ACC_AVG_NUM_16              0x0400
#define C6DOFIMU20_ACC_CONF_ACC_AVG_NUM_32              0x0500
#define C6DOFIMU20_ACC_CONF_ACC_AVG_NUM_64              0x0600
#define C6DOFIMU20_ACC_CONF_ACC_MODE_DIS                0x0000
#define C6DOFIMU20_ACC_CONF_ACC_MODE_DUTY_CYCLING       0x3000
#define C6DOFIMU20_ACC_CONF_ACC_MODE_CONSTANT_OPERATION 0x4000
#define C6DOFIMU20_ACC_CONF_ACC_MODE_HIGH_PERFORMANCE   0x7000

/**
 * @brief 6 DOF IMU 20 GYR_CONF register setting.
 * @details Specified GYR_CONF register setting of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_GYR_CONF_ODR_0POINT78125_Hz          0x0001
#define C6DOFIMU20_GYR_CONF_ODR_1POINT5625_Hz           0x0002
#define C6DOFIMU20_GYR_CONF_ODR_3POINT125_Hz            0x0003
#define C6DOFIMU20_GYR_CONF_ODR_6POINT25_Hz             0x0004
#define C6DOFIMU20_GYR_CONF_ODR_12POINT5_Hz             0x0005
#define C6DOFIMU20_GYR_CONF_ODR_25_Hz                   0x0006
#define C6DOFIMU20_GYR_CONF_ODR_50_Hz                   0x0007
#define C6DOFIMU20_GYR_CONF_ODR_100_Hz                  0x0008
#define C6DOFIMU20_GYR_CONF_ODR_200_Hz                  0x0009
#define C6DOFIMU20_GYR_CONF_ODR_400_Hz                  0x000A
#define C6DOFIMU20_GYR_CONF_ODR_800_Hz                  0x000B
#define C6DOFIMU20_GYR_CONF_ODR_1POINT6_kHz             0x000C
#define C6DOFIMU20_GYR_CONF_ODR_3POINT2_kHz             0x000D
#define C6DOFIMU20_GYR_CONF_ODR_6POINT4_kHz             0x000E
#define C6DOFIMU20_GYR_CONF_GYR_RANGE_2G                0x0000
#define C6DOFIMU20_GYR_CONF_GYR_RANGE_4G                0x0010
#define C6DOFIMU20_GYR_CONF_GYR_RANGE_8G                0x0020
#define C6DOFIMU20_GYR_CONF_GYR_RANGE_16G               0x0030
#define C6DOFIMU20_GYR_CONF_GYR_BW_DIV_2                0x0000
#define C6DOFIMU20_GYR_CONF_GYR_BW_DIV_4                0x0080
#define C6DOFIMU20_GYR_CONF_GYR_AVG_NUM_0               0x0000
#define C6DOFIMU20_GYR_CONF_GYR_AVG_NUM_2               0x0100
#define C6DOFIMU20_GYR_CONF_GYR_AVG_NUM_4               0x0200
#define C6DOFIMU20_GYR_CONF_GYR_AVG_NUM_8               0x0300
#define C6DOFIMU20_GYR_CONF_GYR_AVG_NUM_16              0x0400
#define C6DOFIMU20_GYR_CONF_GYR_AVG_NUM_32              0x0500
#define C6DOFIMU20_GYR_CONF_GYR_AVG_NUM_64              0x0600
#define C6DOFIMU20_GYR_CONF_GYR_MODE_DIS                0x0000
#define C6DOFIMU20_GYR_CONF_GYR_MODE_DUTY_CYCLING       0x3000
#define C6DOFIMU20_GYR_CONF_GYR_MODE_CONSTANT_OPERATION 0x4000
#define C6DOFIMU20_GYR_CONF_GYR_MODE_HIGH_PERFORMANCE   0x7000

/**
 * @brief 6 DOF IMU 20 IO_INT_CTRL register setting.
 * @details Specified IO_INT_CTRL register setting of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_IO_INT_CTRL_INT1_LVL_ACTIVE_HIGH     0x0001
#define C6DOFIMU20_IO_INT_CTRL_INT1_LVL_ACTIVE_LOW      0x0000
#define C6DOFIMU20_IO_INT_CTRL_INT1_OUTPUT_PUSH_PULL    0x0000
#define C6DOFIMU20_IO_INT_CTRL_INT1_OUTPUT_OPEN_DRAIN   0x0002
#define C6DOFIMU20_IO_INT_CTRL_INT1_OUTPUT_EN           0x0004
#define C6DOFIMU20_IO_INT_CTRL_INT2_LVL_ACTIVE_HIGH     0x0100
#define C6DOFIMU20_IO_INT_CTRL_INT2_LVL_ACTIVE_LOW      0x0000
#define C6DOFIMU20_IO_INT_CTRL_INT2_OUTPUT_PUSH_PULL    0x0000
#define C6DOFIMU20_IO_INT_CTRL_INT2_OUTPUT_OPEN_DRAIN   0x0200
#define C6DOFIMU20_IO_INT_CTRL_INT2_OUTPUT_EN           0x0400

/**
 * @brief 6 DOF IMU 20 INT_CONF register setting.
 * @details Specified INT_CONF register setting of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_INT_CONF_INT_LATCH_EN                0x0001
#define C6DOFIMU20_INT_CONF_INT_LATCH_DIS               0x0000

/**
 * @brief 6 DOF IMU 20 INT_MAP1 register setting.
 * @details Specified INT_MAP1 register setting of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_INT_MAP1_NO_MOTION_OUT_DIS           0x0000
#define C6DOFIMU20_INT_MAP1_NO_MOTION_OUT_INT1          0x0001
#define C6DOFIMU20_INT_MAP1_NO_MOTION_OUT_INT2          0x0002
#define C6DOFIMU20_INT_MAP1_ANY_MOTION_OUT_DIS          0x0000
#define C6DOFIMU20_INT_MAP1_ANY_MOTION_OUT_INT1         0x0004
#define C6DOFIMU20_INT_MAP1_ANY_MOTION_OUT_INT2         0x0008
#define C6DOFIMU20_INT_MAP1_FLAT_OUT_DIS                0x0000
#define C6DOFIMU20_INT_MAP1_FLAT_OUT_INT1               0x0010
#define C6DOFIMU20_INT_MAP1_FLAT_OUT_INT2               0x0020
#define C6DOFIMU20_INT_MAP1_ORIENTATION_OUT_DIS         0x0000
#define C6DOFIMU20_INT_MAP1_ORIENTATION_OUT_INT1        0x0040
#define C6DOFIMU20_INT_MAP1_ORIENTATION_OUT_INT2        0x0080
#define C6DOFIMU20_INT_MAP1_STEP_DETECTOR_OUT_DIS       0x0000
#define C6DOFIMU20_INT_MAP1_STEP_DETECTOR_OUT_INT1      0x0100
#define C6DOFIMU20_INT_MAP1_STEP_DETECTOR_OUT_INT2      0x0200
#define C6DOFIMU20_INT_MAP1_STEP_COUNTER_OUT_DIS        0x0000
#define C6DOFIMU20_INT_MAP1_STEP_COUNTER_OUT_INT1       0x0400
#define C6DOFIMU20_INT_MAP1_STEP_COUNTER_OUT_INT2       0x0800
#define C6DOFIMU20_INT_MAP1_SIG_MOTION_OUT_DIS          0x0000
#define C6DOFIMU20_INT_MAP1_SIG_MOTION_OUT_INT1         0x1000
#define C6DOFIMU20_INT_MAP1_SIG_MOTION_OUT_INT2         0x2000
#define C6DOFIMU20_INT_MAP1_TILT_OUT_DIS                0x0000
#define C6DOFIMU20_INT_MAP1_TILT_OUT_INT1               0x4000
#define C6DOFIMU20_INT_MAP1_TILT_OUT_INT2               0x8000

/**
 * @brief 6 DOF IMU 20 INT_MAP2 register setting.
 * @details Specified INT_MAP2 register setting of 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_INT_MAP2_TAP_OUT_OUT_DIS             0x0000
#define C6DOFIMU20_INT_MAP2_TAP_OUT_OUT_INT1            0x0001
#define C6DOFIMU20_INT_MAP2_TAP_OUT_OUT_INT2            0x0002
#define C6DOFIMU20_INT_MAP2_ERR_STATUS_DIS              0x0000
#define C6DOFIMU20_INT_MAP2_ERR_STATUS_INT1             0x0010
#define C6DOFIMU20_INT_MAP2_ERR_STATUS_INT2             0x0020
#define C6DOFIMU20_INT_MAP2_TEMP_DRDY_INT_DIS           0x0000
#define C6DOFIMU20_INT_MAP2_TEMP_DRDY_INT_INT1          0x0040
#define C6DOFIMU20_INT_MAP2_TEMP_DRDY_INT_INT2          0x0080
#define C6DOFIMU20_INT_MAP2_GYR_DRDY_INT_DIS            0x0000
#define C6DOFIMU20_INT_MAP2_GYR_DRDY_INT_INT1           0x0100
#define C6DOFIMU20_INT_MAP2_GYR_DRDY_INT_INT2           0x0200
#define C6DOFIMU20_INT_MAP2_ACC_DRDY_INT_DIS            0x0000
#define C6DOFIMU20_INT_MAP2_ACC_DRDY_INT_INT1           0x0400
#define C6DOFIMU20_INT_MAP2_ACC_DRDY_INT_INT2           0x0800
#define C6DOFIMU20_INT_MAP2_FIFO_WATERMARK_INT_DIS      0x0000
#define C6DOFIMU20_INT_MAP2_FIFO_WATERMARK_INT_INT1     0x1000
#define C6DOFIMU20_INT_MAP2_FIFO_WATERMARK_INT_INT2     0x2000
#define C6DOFIMU20_INT_MAP2_FIFO_FULL_INT_DIS           0x0000
#define C6DOFIMU20_INT_MAP2_FIFO_FULL_INT_INT1          0x4000
#define C6DOFIMU20_INT_MAP2_FIFO_FULL_INT_INT2          0x8000

/**
 * @brief 6 DOF IMU 20 temperature calculation setting.
 * @details Specified setting for temperature calculation of
 * 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_TEMP_CALC_DIVIDER                    512
#define C6DOFIMU20_TEMP_CALC_VALUE                      23

/**
 * @brief 6 DOF IMU 20 Chip ID.
 * @details Specified setting for chip id of
 * 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_CHIP_ID                              0x43

/**
 * @brief 6 DOF IMU 20 device address setting.
 * @details Specified setting for device slave address selection of
 * 6 DOF IMU 20 Click driver.
 */
#define C6DOFIMU20_DEVICE_ADDRESS_GND                   0x68
#define C6DOFIMU20_DEVICE_ADDRESS_VCC                   0x69

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c6dofimu20_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C6DOFIMU20_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define C6DOFIMU20_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c6dofimu20_set

/**
 * @defgroup c6dofimu20_map 6 DOF IMU 20 MikroBUS Map
 * @brief MikroBUS pin mapping of 6 DOF IMU 20 Click driver.
 */

/**
 * @addtogroup c6dofimu20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6 DOF IMU 20 Click to the selected MikroBUS.
 */
#define C6DOFIMU20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.it1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.it2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6dofimu20_map
/*! @} */ // c6dofimu20

/**
 * @brief 6 DOF IMU 20 Click driver selector.
 * @details Selects target driver interface of 6 DOF IMU 20 Click driver.
 */
typedef enum
{
    C6DOFIMU20_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    C6DOFIMU20_DRV_SEL_I2C       /**< I2C driver descriptor. */

} c6dofimu20_drv_t;

/**
 * @brief 6 DOF IMU 20 Click driver interface.
 * @details Definition of driver interface of 6 DOF IMU 20 Click driver.
 */
typedef err_t ( *c6dofimu20_master_io_t )( struct c6dofimu20_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief 6 DOF IMU 20 Click context object.
 * @details Context object definition of 6 DOF IMU 20 Click driver.
 */
typedef struct c6dofimu20_s
{
    digital_out_t cs;           /**< Chip select pin descriptor. */

    digital_in_t it1;           /**< Interrupt 1 pin. */
    digital_in_t it2;           /**< Interrupt 2 pin. */

    i2c_master_t i2c;           /**< I2C driver object. */
    spi_master_t spi;           /**< SPI driver object. */

    uint8_t      slave_address; /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */
    c6dofimu20_drv_t drv_sel;   /**< Master driver interface selector. */

    c6dofimu20_master_io_t write_f;          /**< Master write function. */
    c6dofimu20_master_io_t read_f;           /**< Master read function. */

} c6dofimu20_t;

/**
 * @brief 6 DOF IMU 20 Click configuration object.
 * @details Configuration object definition of 6 DOF IMU 20 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t it1;             /**< Interrupt 1 pin. */
    pin_name_t it2;             /**< Interrupt 2 pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    c6dofimu20_drv_t drv_sel;                /**< Master driver interface selector. */

} c6dofimu20_cfg_t;

/**
 * @brief 6 DOF IMU 20 Click data object.
 * @details Data object definition of 6 DOF IMU 20 Click driver.
 */
typedef struct
{
    int16_t data_x;
    int16_t data_y;
    int16_t data_z;

} c6dofimu20_data_t;

/**
 * @brief 6 DOF IMU 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C6DOFIMU20_OK = 0,
    C6DOFIMU20_ERROR = -1

} c6dofimu20_return_value_t;

/*!
 * @addtogroup c6dofimu20 6 DOF IMU 20 Click Driver
 * @brief API for configuring and manipulating 6 DOF IMU 20 Click driver.
 * @{
 */

/**
 * @brief 6 DOF IMU 20 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c6dofimu20_cfg_setup ( c6dofimu20_cfg_t *cfg );

/**
 * @brief 6 DOF IMU 20 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu20_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #c6dofimu20_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void c6dofimu20_drv_interface_selection ( c6dofimu20_cfg_t *cfg, c6dofimu20_drv_t drv_sel );

/**
 * @brief 6 DOF IMU 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6dofimu20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu20_init ( c6dofimu20_t *ctx, c6dofimu20_cfg_t *cfg );

/**
 * @brief 6 DOF IMU 20 default configuration function.
 * @details This function executes a default configuration of 6 DOF IMU 20
 * click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c6dofimu20_default_cfg ( c6dofimu20_t *ctx );

/**
 * @brief 6 DOF IMU 20 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu20_generic_write ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6 DOF IMU 20 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu20_generic_read ( c6dofimu20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6 DOF IMU 20 register data writing function.
 * @details This function writes a 16 bits of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu20_set_reg ( c6dofimu20_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief 6 DOF IMU 20 register data reading function.
 * @details This function reads a 16 bits of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu20_get_reg ( c6dofimu20_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief 6 DOF IMU 20 register chip id reading function.
 * @details This function reads a chip id from the CHIP_ID register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[out] chip_id : Rread chip id  data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu20_get_id ( c6dofimu20_t *ctx, uint8_t *chip_id );

/**
 * @brief 6 DOF IMU 20 IT1 state reading function.
 * @details This function reads a state of the IT1 pin.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @return State of the IN1 pin.
 * @note None.
 */
uint8_t c6dofimu20_get_int1_state ( c6dofimu20_t *ctx );

/**
 * @brief 6 DOF IMU 20 IT2 state reading function.
 * @details This function reads a state of the IT2 pin.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @return State of the IN2 pin.
 * @note None.
 */
uint8_t c6dofimu20_get_int2_state ( c6dofimu20_t *ctx );

/**
 * @brief 6 DOF IMU 20 accel data reading function.
 * @details This function reads a accel data from registers.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[out] acc_data : Read accel data.
 * See c6dofimu20_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu20_get_acc_data ( c6dofimu20_t *ctx, c6dofimu20_data_t *acc_data );

/**
 * @brief 6 DOF IMU 20 gyro data reading function.
 * @details This function reads a gyro data from registers.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[out] gyr_data : Read gyro data.
 * See c6dofimu20_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu20_get_gyr_data ( c6dofimu20_t *ctx, c6dofimu20_data_t *gyr_data );

/**
 * @brief 6 DOF IMU 20 temperature reading function.
 * @details This function reads a temperature from registers.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @param[out] temp_data : Read temperature data in degrees of celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu20_get_temperature ( c6dofimu20_t *ctx, float *temp_data );

/**
 * @brief 6 DOF IMU 20 software reset function.
 * @details This function performs software reset.
 * @param[in] ctx : Click context object.
 * See #c6dofimu20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu20_sw_reset ( c6dofimu20_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // C6DOFIMU20_H

/*! @} */ // c6dofimu20

// ------------------------------------------------------------------------ END
