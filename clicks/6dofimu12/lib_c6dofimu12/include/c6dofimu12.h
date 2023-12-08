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
 * \brief This file contains API for 6DOF IMU 12 Click driver.
 *
 * \addtogroup c6dofimu12 6DOF IMU 12 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU12_H
#define C6DOFIMU12_H

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

#define C6DOFIMU12_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C6DOFIMU12_MASTER_I2C 0
#define C6DOFIMU12_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU12_RETVAL  uint8_t

#define C6DOFIMU12_OK           0x00
#define C6DOFIMU12_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_address I2C slave address
 * \{
 */
#define        C6DOFIMU12_REG_I2C_ADDR_GND                        0x68
#define        C6DOFIMU12_REG_I2C_ADDR_VCC                        0x69
/** \} */


/**
 * \defgroup reg_addr Register address
 * \{
 */
#define        C6DOFIMU12_REG_CHIP_ID_ADDR                        0x00
#define        C6DOFIMU12_REG_ERROR                               0x02
#define        C6DOFIMU12_REG_STATUS_ADDR                         0x03
#define        C6DOFIMU12_REG_AUX_X_LSB_ADDR                      0x04
#define        C6DOFIMU12_REG_ACC_X_LSB_ADDR                      0x0C
#define        C6DOFIMU12_REG_GYR_X_LSB_ADDR                      0x12
#define        C6DOFIMU12_REG_EVENT_ADDR                          0x1B
#define        C6DOFIMU12_REG_INT_STATUS_0_ADDR                   0x1C
#define        C6DOFIMU12_REG_INT_STATUS_1_ADDR                   0x1D
#define        C6DOFIMU12_REG_SC_OUT_0_ADDR                       0x1E
#define        C6DOFIMU12_REG_SYNC_COMMAND_ADDR                   0x1E
#define        C6DOFIMU12_REG_GYR_CAS_GPIO0_ADDR                  0x1E
#define        C6DOFIMU12_REG_INTERNAL_STATUS_ADDR                0x21
#define        C6DOFIMU12_REG_FIFO_LENGTH_0_ADDR                  0X24
#define        C6DOFIMU12_REG_FIFO_DATA_ADDR                      0X26
#define        C6DOFIMU12_REG_FEAT_PAGE_ADDR                      0x2F
#define        C6DOFIMU12_REG_FEATURES_REG_ADDR                   0x30
#define        C6DOFIMU12_REG_ACC_CONF_ADDR                       0x40
#define        C6DOFIMU12_REG_GYR_CONF_ADDR                       0x42
#define        C6DOFIMU12_REG_AUX_CONF_ADDR                       0x44
#define        C6DOFIMU12_REG_FIFO_DOWNS_ADDR                     0X45
#define        C6DOFIMU12_REG_FIFO_WTM_0_ADDR                     0X46
#define        C6DOFIMU12_REG_FIFO_WTM_1_ADDR                     0X47
#define        C6DOFIMU12_REG_FIFO_CONFIG_0_ADDR                  0X48
#define        C6DOFIMU12_REG_FIFO_CONFIG_1_ADDR                  0X49
#define        C6DOFIMU12_REG_AUX_DEV_ID_ADDR                     0x4B
#define        C6DOFIMU12_REG_AUX_IF_CONF_ADDR                    0x4C
#define        C6DOFIMU12_REG_AUX_RD_ADDR                         0x4D
#define        C6DOFIMU12_REG_AUX_WR_ADDR                         0x4E
#define        C6DOFIMU12_REG_AUX_WR_DATA_ADDR                    0x4F
#define        C6DOFIMU12_REG_INT1_IO_CTRL_ADDR                   0x53
#define        C6DOFIMU12_REG_INT2_IO_CTRL_ADDR                   0x54
#define        C6DOFIMU12_REG_INT1_MAP_FEAT_ADDR                  0x56
#define        C6DOFIMU12_REG_INT2_MAP_FEAT_ADDR                  0x57
#define        C6DOFIMU12_REG_INT_MAP_DATA_ADDR                   0x58
#define        C6DOFIMU12_REG_INIT_CTRL_ADDR                      0x59
#define        C6DOFIMU12_REG_INIT_ADDR_0                         0x5B
#define        C6DOFIMU12_REG_INIT_ADDR_1                         0x5C
#define        C6DOFIMU12_REG_INIT_DATA_ADDR                      0x5E
#define        C6DOFIMU12_REG_GYR_CRT_CONF_ADDR                   0X69
#define        C6DOFIMU12_REG_NVM_CONF_ADDR                       0x6A
#define        C6DOFIMU12_REG_IF_CONF_ADDR                        0X6B
#define        C6DOFIMU12_REG_ACC_SELF_TEST_ADDR                  0X6D
#define        C6DOFIMU12_REG_GYR_SELF_TEST_AXES_ADDR             0x6E
#define        C6DOFIMU12_REG_SELF_TEST_MEMS_ADDR                 0X6F
#define        C6DOFIMU12_REG_NV_CONF_ADDR                        0x70
#define        C6DOFIMU12_REG_ACC_OFF_COMP_0_ADDR                 0X71
#define        C6DOFIMU12_REG_GYR_OFF_COMP_3_ADDR                 0X74
#define        C6DOFIMU12_REG_GYR_OFF_COMP_6_ADDR                 0X77
#define        C6DOFIMU12_REG_GYR_USR_GAIN_0_ADDR                 0X78
#define        C6DOFIMU12_REG_PWR_CONF_ADDR                       0x7C
#define        C6DOFIMU12_REG_PWR_CTRL_ADDR                       0x7D
#define        C6DOFIMU12_REG_CMD_REG_ADDR                        0x7E
/** \} */

/**
 * \defgroup dev_id Device ID value
 * \{
 */
#define        C6DOFIMU12_DEVICE_ID_VAL                           0x24
/** \} */

/**
 * \defgroup def_for_power Definitions for power control register
 * \{
 */
#define        C6DOFIMU12_AUX_EN_MASK                             0x01
#define        C6DOFIMU12_GYR_EN_MASK                             0x02
#define        C6DOFIMU12_ACC_EN_MASK                             0x04
#define        C6DOFIMU12_TEMP_EN_MASK                            0x08
/** \} */

/**
 * \defgroup acc_filter Accelerometer filter performance mode
 * \{
 */
#define        C6DOFIMU12_ACC_PWR_OPTIMIZED                       0x00
#define        C6DOFIMU12_ACC_OSR2_PWR_PERFORMANCE                0x80
/** \} */

/**
 * \defgroup acc_param Accelerometer parameters
 * \{
 */
#define        C6DOFIMU12_ACC_OSR4_AVG1                           0x00
#define        C6DOFIMU12_ACC_OSR2_AVG2                           0x10
#define        C6DOFIMU12_ACC_NORMAL_AVG4                         0x20
#define        C6DOFIMU12_ACC_CIC_AVG8                            0x30
#define        C6DOFIMU12_ACC_RES_AVG16                           0x40
#define        C6DOFIMU12_ACC_RES_AVG32                           0x50
#define        C6DOFIMU12_ACC_RES_AVG64                           0x60
#define        C6DOFIMU12_ACC_RES_AVG128                          0x70
/** \} */

/**
 * \defgroup acc_out Accelerometer Output Data Rate
 * \{
 */
#define        C6DOFIMU12_ACC_ODR_0_78HZ                          0x01
#define        C6DOFIMU12_ACC_ODR_1_56HZ                          0x02
#define        C6DOFIMU12_ACC_ODR_3_12HZ                          0x03
#define        C6DOFIMU12_ACC_ODR_6_25HZ                          0x04
#define        C6DOFIMU12_ACC_ODR_12_5HZ                          0x05
#define        C6DOFIMU12_ACC_ODR_25HZ                            0x06
#define        C6DOFIMU12_ACC_ODR_50HZ                            0x07
#define        C6DOFIMU12_ACC_ODR_100HZ                           0x08
#define        C6DOFIMU12_ACC_ODR_200HZ                           0x09
#define        C6DOFIMU12_ACC_ODR_400HZ                           0x0A
#define        C6DOFIMU12_ACC_ODR_800HZ                           0x0B
#define        C6DOFIMU12_ACC_ODR_1600HZ                          0x0C
/** \} */

/**
 * \defgroup acc_g_range Accelerometer G Range
 * \{
 */
#define        C6DOFIMU12_ACC_RANGE_2G                            0x00
#define        C6DOFIMU12_ACC_RANGE_4G                            0x01
#define        C6DOFIMU12_ACC_RANGE_8G                            0x02
#define        C6DOFIMU12_ACC_RANGE_16G                           0x03
/** \} */

/**
 * \defgroup mask_def Mask definitions for accelerometer configuration register
 * \{
 */
#define        C6DOFIMU12_ACC_RANGE_MASK                          0x03
#define        C6DOFIMU12_ACC_ODR_MASK                            0x0F
#define        C6DOFIMU12_ACC_BW_PARAM_MASK                       0x70
#define        C6DOFIMU12_ACC_FILTER_PERF_MODE_MASK               0x80
/** \} */

/** \defgroup bit_pos Bit position definitions for accelerometer configuration register
 * \{
 */
#define        C6DOFIMU12_ACC_BW_PARAM_POS                        0x04
#define        C6DOFIMU12_ACC_FILTER_PERF_MODE_POS                0x07
/** \} */

/** \defgroup self_test_range Self test macro to define range
 * \{
 */
#define        C6DOFIMU12_ACC_SELF_TEST_RANGE                        16
/** \} */

/** \defgroup self_test  Self test
 * \{
 */
#define        C6DOFIMU12_ST_ACC_X_SIG_MIN_DIFF                    1800
#define        C6DOFIMU12_ST_ACC_X_SIG_MAX_DIFF                   10200
#define        C6DOFIMU12_ST_ACC_Y_SIG_MIN_DIFF                  -10200
#define        C6DOFIMU12_ST_ACC_Y_SIG_MAX_DIFF                   -1800
#define        C6DOFIMU12_ST_ACC_Z_SIG_MIN_DIFF                     800
#define        C6DOFIMU12_ST_ACC_Z_SIG_MAX_DIFF                   10200
/** \} */

/** \defgroup mask_def_self Mask definitions for accelerometer self-test
 * \{
 */
#define       C6DOFIMU12_ACC_SELF_TEST_EN_MASK                    0x01
#define       C6DOFIMU12_ACC_SELF_TEST_SIGN_MASK                  0x04
#define       C6DOFIMU12_ACC_SELF_TEST_AMP_MASK                   0x08
/** \} */

/** \defgroup bit_pos_acc Bit Positions for accelerometer self-test
 * \{
 */
#define       C6DOFIMU12_ACC_SELF_TEST_SIGN_POS                   0x02
#define       C6DOFIMU12_ACC_SELF_TEST_AMP_POS                    0x03
/** \} */

// MASK definition for gyro self test status
#define       C6DOFIMU12_GYR_ST_AXES_DONE_MASK                    0X01
#define       C6DOFIMU12_GYR_AXIS_X_OK_MASK                       0x02
#define       C6DOFIMU12_GYR_AXIS_Y_OK_MASK                       0x04
#define       C6DOFIMU12_GYR_AXIS_Z_OK_MASK                       0x08

// Bit position for gyro self test status
#define       C6DOFIMU12_GYR_AXIS_X_OK_POS                        0x01
#define       C6DOFIMU12_GYR_AXIS_Y_OK_POS                        0x02
#define       C6DOFIMU12_GYR_AXIS_Z_OK_POS                        0x03

// Gyroscope filter performance mode
#define       C6DOFIMU12_GYR_PWR_OPTIMIZED                        0x00
#define       C6DOFIMU12_GYR_PWR_PERFORMANCE                      0x80

// Gyroscope noise performance
#define       C6DOFIMU12_GYR_NOISE_OPTIMIZED                      0x00
#define       C6DOFIMU12_GYR_NOISE_PERFORMANCE                    0x40

// Gyroscope parameters
#define       C6DOFIMU12_GYR_OSR4_MODE                            0x00
#define       C6DOFIMU12_GYR_OSR2_MODE                            0x10
#define       C6DOFIMU12_GYR_NORMAL_MODE                          0x20
#define       C6DOFIMU12_GYR_CIC_MODE                             0x30

// Gyroscope Output Data Rate
#define       C6DOFIMU12_GYR_ODR_25HZ                             0x06
#define       C6DOFIMU12_GYR_ODR_50HZ                             0x07
#define       C6DOFIMU12_GYR_ODR_100HZ                            0x08
#define       C6DOFIMU12_GYR_ODR_200HZ                            0x09
#define       C6DOFIMU12_GYR_ODR_400HZ                            0x0A
#define       C6DOFIMU12_GYR_ODR_800HZ                            0x0B
#define       C6DOFIMU12_GYR_ODR_1600HZ                           0x0C
#define       C6DOFIMU12_GYR_ODR_3200HZ                           0x0D

// Gyroscope OIS Range
#define       C6DOFIMU12_GYR_OIS_250                              0x00
#define       C6DOFIMU12_GYR_OIS_2000                             0x01

// Gyroscope Angular Rate Measurement Range
#define       C6DOFIMU12_GYR_RANGE_2000                           0x00
#define       C6DOFIMU12_GYR_RANGE_1000                           0x01
#define       C6DOFIMU12_GYR_RANGE_500                            0x02
#define       C6DOFIMU12_GYR_RANGE_250                            0x03
#define       C6DOFIMU12_GYR_RANGE_125                            0x04

// Mask definitions for gyroscope configuration register
#define       C6DOFIMU12_GYR_RANGE_MASK                           0x07
#define       C6DOFIMU12_GYR_OIS_RANGE_MASK                       0x08
#define       C6DOFIMU12_GYR_ODR_MASK                             0x0F
#define       C6DOFIMU12_GYR_BW_PARAM_MASK                        0x30
#define       C6DOFIMU12_GYR_NOISE_PERF_MODE_MASK                 0x40
#define       C6DOFIMU12_GYR_FILTER_PERF_MODE_MASK                0x80

// Bit position definitions for gyroscope configuration register
#define       C6DOFIMU12_GYR_OIS_RANGE_POS                        0x03
#define       C6DOFIMU12_GYR_BW_PARAM_POS                         0x04
#define       C6DOFIMU12_GYR_NOISE_PERF_MODE_POS                  0x06
#define       C6DOFIMU12_GYR_FILTER_PERF_MODE_POS                 0x07

// Auxiliary Output Data Rate
#define       C6DOFIMU12_AUX_ODR_RESERVED                         0x00
#define       C6DOFIMU12_AUX_ODR_0_78HZ                           0x01
#define       C6DOFIMU12_AUX_ODR_1_56HZ                           0x02
#define       C6DOFIMU12_AUX_ODR_3_12HZ                           0x03
#define       C6DOFIMU12_AUX_ODR_6_25HZ                           0x04
#define       C6DOFIMU12_AUX_ODR_12_5HZ                           0x05
#define       C6DOFIMU12_AUX_ODR_25HZ                             0x06
#define       C6DOFIMU12_AUX_ODR_50HZ                             0x07
#define       C6DOFIMU12_AUX_ODR_100HZ                            0x08
#define       C6DOFIMU12_AUX_ODR_200HZ                            0x09
#define       C6DOFIMU12_AUX_ODR_400HZ                            0x0A
#define       C6DOFIMU12_AUX_ODR_800HZ                            0x0B

// Power mode configuration register
#define       C6DOFIMU12_PWR_CONF_ADV_PWR_SAVE_DISABLED           0x00
#define       C6DOFIMU12_PWR_CONF_ADV_PWR_SAVE_ENABLED            0x01
#define       C6DOFIMU12_FIFO_READ_DISABLED                       0x00
#define       C6DOFIMU12_FIFO_READ_ENABLED                        0x02
#define       C6DOFIMU12_FAST_PWR_UP_DISABLED                     0x00
#define       C6DOFIMU12_FAST_PWR_UP_ENABLED                      0x04

// Start initialization register
#define       C6DOFIMU12_CMD_INITIALIZATION_START                 0x00
#define       C6DOFIMU12_CMD_INITIALIZATION_STOP                  0x01

// Macro to define burst read lengths for both manual and auto modes
#define       C6DOFIMU12_AUX_READ_LEN_0                           0x00
#define       C6DOFIMU12_AUX_READ_LEN_1                           0x01
#define       C6DOFIMU12_AUX_READ_LEN_2                           0x02
#define       C6DOFIMU12_AUX_READ_LEN_3                           0x03

// Mask definitions for auxiliary interface configuration register
#define       C6DOFIMU12_AUX_SET_I2C_ADDR_MASK                    0xFE
#define       C6DOFIMU12_AUX_MAN_MODE_EN_MASK                     0x80
#define       C6DOFIMU12_AUX_FCU_WR_EN_MASK                       0x40
#define       C6DOFIMU12_AUX_MAN_READ_BURST_MASK                  0x0C
#define       C6DOFIMU12_AUX_READ_BURST_MASK                      0x03
#define       C6DOFIMU12_AUX_ODR_EN_MASK                          0x0F
#define       C6DOFIMU12_AUX_OFFSET_READ_OUT_MASK                 0xF0

// Bit positions for auxiliary interface configuration register
#define       C6DOFIMU12_AUX_SET_I2C_ADDR_POS                     0x01
#define       C6DOFIMU12_AUX_MAN_MODE_EN_POS                      0x07
#define       C6DOFIMU12_AUX_FCU_WR_EN_POS                        0x06
#define       C6DOFIMU12_AUX_MAN_READ_BURST_POS                   0x02
#define       C6DOFIMU12_AUX_OFFSET_READ_OUT_POS                  0x04

// FIFO Definitions
#define       C6DOFIMU12_FIFO_VIRT_FRM_MODE                       0x03

// FIFO Header Mask definitions
#define       C6DOFIMU12_FIFO_HEADER_ACC_FRM                      0x84
#define       C6DOFIMU12_FIFO_HEADER_AUX_FRM                      0x90
#define       C6DOFIMU12_FIFO_HEADER_GYR_FRM                      0x88
#define       C6DOFIMU12_FIFO_HEADER_GYR_ACC_FRM                  0x8C
#define       C6DOFIMU12_FIFO_HEADER_AUX_ACC_FRM                  0x94
#define       C6DOFIMU12_FIFO_HEADER_AUX_GYR_FRM                  0x98
#define       C6DOFIMU12_FIFO_HEADER_ALL_FRM                      0x9C
#define       C6DOFIMU12_FIFO_HEADER_SENS_TIME_FRM                0x44
#define       C6DOFIMU12_FIFO_HEADER_SKIP_FRM                     0x40
#define       C6DOFIMU12_FIFO_HEADER_INPUT_CFG_FRM                0x48
#define       C6DOFIMU12_FIFO_HEAD_OVER_READ_MSB                  0x80
#define       C6DOFIMU12_FIFO_VIRT_ACT_RECOG_FRM                  0xC8

// Sensor selection for header-less frames
#define       C6DOFIMU12_FIFO_HEAD_LESS_ACC_FRM                   0x40
#define       C6DOFIMU12_FIFO_HEAD_LESS_AUX_FRM                   0x20
#define       C6DOFIMU12_FIFO_HEAD_LESS_GYR_FRM                   0x80
#define       C6DOFIMU12_FIFO_HEAD_LESS_GYR_AUX_FRM               0xA0
#define       C6DOFIMU12_FIFO_HEAD_LESS_GYR_ACC_FRM               0xC0
#define       C6DOFIMU12_FIFO_HEAD_LESS_AUX_ACC_FRM               0x60
#define       C6DOFIMU12_FIFO_HEAD_LESS_ALL_FRM                   0xE0

// Mask definitions for FIFO frame content configuration
#define       C6DOFIMU12_FIFO_STOP_ON_FULL                      0x0001
#define       C6DOFIMU12_FIFO_TIME_EN                           0x0002
#define       C6DOFIMU12_FIFO_TAG_INT1                          0x0300
#define       C6DOFIMU12_FIFO_TAG_INT2                          0x0C00
#define       C6DOFIMU12_FIFO_HEADER_EN                         0x1000
#define       C6DOFIMU12_FIFO_AUX_EN                            0x2000
#define       C6DOFIMU12_FIFO_ACC_EN                            0x4000
#define       C6DOFIMU12_FIFO_GYR_EN                            0x8000
#define       C6DOFIMU12_FIFO_ALL_EN                            0xE000

// FIFO sensor data lengths
#define       C6DOFIMU12_FIFO_ACC_LENGTH                             6
#define       C6DOFIMU12_FIFO_GYR_LENGTH                             6
#define       C6DOFIMU12_FIFO_AUX_LENGTH                             8
#define       C6DOFIMU12_FIFO_ACC_AUX_LENGTH                        14
#define       C6DOFIMU12_FIFO_GYR_AUX_LENGTH                        14
#define       C6DOFIMU12_FIFO_ACC_GYR_LENGTH                        12
#define       C6DOFIMU12_FIFO_ALL_LENGTH                            20
#define       C6DOFIMU12_SENSOR_TIME_LENGTH                          3
#define       C6DOFIMU12_FIFO_CONFIG_LENGTH                          2
#define       C6DOFIMU12_FIFO_WM_LENGTH                              2
#define       C6DOFIMU12_MAX_VALUE_FIFO_FILTER                       1
#define       C6DOFIMU12_FIFO_DATA_LENGTH                            2
#define       C6DOFIMU12_FIFO_LENGTH_MSB_BYTE                        1
#define       C6DOFIMU12_FIFO_INPUT_CFG_LENGTH                       4
#define       C6DOFIMU12_FIFO_SKIP_FRM_LENGTH                        1

// FIFO sensor virtual data lengths: sensor data plus sensor time
#define       C6DOFIMU12_FIFO_VIRT_ACC_LENGTH                        9
#define       C6DOFIMU12_FIFO_VIRT_GYR_LENGTH                        9
#define       C6DOFIMU12_FIFO_VIRT_AUX_LENGTH                       11
#define       C6DOFIMU12_FIFO_VIRT_ACC_AUX_LENGTH                   17
#define       C6DOFIMU12_FIFO_VIRT_GYR_AUX_LENGTH                   17
#define       C6DOFIMU12_FIFO_VIRT_ACC_GYR_LENGTH                   15
#define       C6DOFIMU12_FIFO_VIRT_ALL_LENGTH                       23

// FIFO sensor virtual data lengths: activity recognition
#define       C6DOFIMU12_FIFO_VIRT_ACT_DATA_LENGTH                   6
#define       C6DOFIMU12_FIFO_VIRT_ACT_TIME_LENGTH                   4
#define       C6DOFIMU12_FIFO_VIRT_ACT_TYPE_LENGTH                   1
#define       C6DOFIMU12_FIFO_VIRT_ACT_STAT_LENGTH                   1

// FIFO data filter modes
#define       C6DOFIMU12_FIFO_UNFILTERED_DATA                        0
#define       C6DOFIMU12_FIFO_FILTERED_DATA                          1

// FIFO frame masks
#define       C6DOFIMU12_FIFO_LSB_CONFIG_CHECK                    0x00
#define       C6DOFIMU12_FIFO_MSB_CONFIG_CHECK                    0x80
#define       C6DOFIMU12_FIFO_TAG_INTR_MASK                       0xFF

// Mask definitions of FIFO configuration registers
#define       C6DOFIMU12_FIFO_CONFIG_0_MASK                     0x0003
#define       C6DOFIMU12_FIFO_CONFIG_1_MASK                     0xFF00

// FIFO self wake-up mask definition
#define      C6DOFIMU12_FIFO_SELF_WAKE_UP_MASK                    0x02

// FIFO down sampling mask definition
#define      C6DOFIMU12_ACC_FIFO_DOWNS_MASK                       0x70
#define      C6DOFIMU12_GYR_FIFO_DOWNS_MASK                       0x07

// FIFO down sampling bit positions
#define      C6DOFIMU12_ACC_FIFO_DOWNS_POS                        0x04

// FIFO filter mask definition
#define      C6DOFIMU12_ACC_FIFO_FILT_DATA_MASK                   0x80
#define      C6DOFIMU12_GYR_FIFO_FILT_DATA_MASK                   0x08

// FIFO filter bit positions
#define      C6DOFIMU12_ACC_FIFO_FILT_DATA_POS                    0x07
#define      C6DOFIMU12_GYR_FIFO_FILT_DATA_POS                    0x03

// FIFO byte counter mask definition
#define      C6DOFIMU12_FIFO_BYTE_COUNTER_MSB_MASK                0x3F

// FIFO self wake-up bit positions
#define      C6DOFIMU12_FIFO_SELF_WAKE_UP_POS                     0x02

// Mask Definitions for Virtual FIFO frames
#define      C6DOFIMU12_FIFO_VIRT_FRM_MODE_MASK                   0xC0
#define      C6DOFIMU12_FIFO_VIRT_PAYLOAD_MASK                    0x3C

// Bit Positions for Virtual FIFO frames
#define      C6DOFIMU12_FIFO_VIRT_FRM_MODE_POS                    0x06
#define      C6DOFIMU12_FIFO_VIRT_PAYLOAD_POS                     0x02

// Interrupt Definitions
#define      C6DOFIMU12_INT_NON_LATCH                                0

// Permanently latched
#define      C6DOFIMU12_INT_LATCH                                    1

// Interrupt Pin Behavior
#define      C6DOFIMU12_INT_PUSH_PULL                                0
#define      C6DOFIMU12_INT_OPEN_DRAIN                               1

// Interrupt Pin Level
#define      C6DOFIMU12_INT_ACTIVE_LOW                               0
#define      C6DOFIMU12_INT_ACTIVE_HIGH                              1

// Interrupt Output Enable
#define      C6DOFIMU12_INT_OUTPUT_DISABLE                           0
#define      C6DOFIMU12_INT_OUTPUT_ENABLE                            1

// Interrupt Input Enable
#define      C6DOFIMU12_INT_INPUT_DISABLE                            0
#define      C6DOFIMU12_INT_INPUT_ENABLE                             1

// Mask definitions for interrupt pin configuration
#define      C6DOFIMU12_INT_LATCH_MASK                            0x01
#define      C6DOFIMU12_INT_LEVEL_MASK                            0x02
#define      C6DOFIMU12_INT_OPEN_DRAIN_MASK                       0x04
#define      C6DOFIMU12_INT_OUTPUT_EN_MASK                        0x08
#define      C6DOFIMU12_INT_INPUT_EN_MASK                         0x10

// Bit position definitions for interrupt pin configuration
#define      C6DOFIMU12_INT_LEVEL_POS                             0x01
#define      C6DOFIMU12_INT_OPEN_DRAIN_POS                        0x02
#define      C6DOFIMU12_INT_OUTPUT_EN_POS                         0x03
#define      C6DOFIMU12_INT_INPUT_EN_POS                          0x04

// Mask definitions for data interrupt mapping
#define      C6DOFIMU12_FFULL_INT                                 0x01
#define      C6DOFIMU12_FWM_INT                                   0x02
#define      C6DOFIMU12_DRDY_INT                                  0x04
#define      C6DOFIMU12_ERR_INT                                   0x08

// Mask definitions for data interrupt status bits
#define      C6DOFIMU12_FFULL_INT_STATUS_MASK                   0x0100
#define      C6DOFIMU12_FWM_INT_STATUS_MASK                     0x0200
#define      C6DOFIMU12_ERR_INT_STATUS_MASK                     0x0400
#define      C6DOFIMU12_AUX_DRDY_INT_MASK                       0x2000
#define      C6DOFIMU12_GYR_DRDY_INT_MASK                       0x4000
#define      C6DOFIMU12_ACC_DRDY_INT_MASK                       0x8000

// Maximum number of interrupt pins
#define      C6DOFIMU12_INT_PIN_MAX_NUM                              2

// Macro for mapping feature interrupts
#define      C6DOFIMU12_FEAT_BIT_DISABLE                             0
#define      C6DOFIMU12_FEAT_BIT0                                    1
#define      C6DOFIMU12_FEAT_BIT1                                    2
#define      C6DOFIMU12_FEAT_BIT2                                    3
#define      C6DOFIMU12_FEAT_BIT3                                    4
#define      C6DOFIMU12_FEAT_BIT4                                    5
#define      C6DOFIMU12_FEAT_BIT5                                    6
#define      C6DOFIMU12_FEAT_BIT6                                    7
#define      C6DOFIMU12_FEAT_BIT7                                    8
#define      C6DOFIMU12_FEAT_BIT_MAX                                 9

// OIS Interface configuration register
#define      C6DOFIMU12_OIS_IF_EN_MASK                            0x10
#define      C6DOFIMU12_AUX_IF_EN_MASK                            0x20

// Bit positions for OIS interface enable
#define      C6DOFIMU12_OIS_IF_EN_POS                             0x04
#define      C6DOFIMU12_AUX_IF_EN_POS                             0x05

// Macros for the user-defined values of axes and their polarities
#define      C6DOFIMU12_X                                         0x01
#define      C6DOFIMU12_NEG_X                                     0x09
#define      C6DOFIMU12_Y                                         0x02
#define      C6DOFIMU12_NEG_Y                                     0x0A
#define      C6DOFIMU12_Z                                         0x04
#define      C6DOFIMU12_NEG_Z                                     0x0C
#define      C6DOFIMU12_AXIS_MASK                                 0x07
#define      C6DOFIMU12_AXIS_SIGN                                 0x08

// Mask definitions of gyroscope offset compensation registers
#define      C6DOFIMU12_GYR_GAIN_EN_MASK                          0x80
#define      C6DOFIMU12_GYR_OFF_COMP_EN_MASK                      0x40

// Bit positions of gyroscope offset compensation registers
#define      C6DOFIMU12_GYR_OFF_COMP_EN_POS                       0x06

// Mask definitions of gyroscope user-gain registers
#define      C6DOFIMU12_GYR_USR_GAIN_X_MASK                       0x7F
#define      C6DOFIMU12_GYR_USR_GAIN_Y_MASK                       0x7F
#define      C6DOFIMU12_GYR_USR_GAIN_Z_MASK                       0x7F

// Bit positions of gyroscope offset compensation registers
#define      C6DOFIMU12_GYR_GAIN_EN_POS                           0x07

// Macro Definitions for internal status
#define      C6DOFIMU12_NOT_INIT                                  0x00
#define      C6DOFIMU12_INIT_OK                                   0x01
#define      C6DOFIMU12_INIT_ERR                                  0x02
#define      C6DOFIMU12_DRV_ERR                                   0x03
#define      C6DOFIMU12_SNS_STOP                                  0x04
#define      C6DOFIMU12_NVM_ERROR                                 0x05
#define      C6DOFIMU12_START_UP_ERROR                            0x06
#define      C6DOFIMU12_COMPAT_ERROR                              0x07
#define      C6DOFIMU12_VFM_SKIPPED                               0x10
#define      C6DOFIMU12_AXES_MAP_ERROR                            0x20
#define      C6DOFIMU12_ODR_50_HZ_ERROR                           0x40
#define      C6DOFIMU12_ODR_HIGH_ERROR                            0x80

// Error status form gyro gain update status
#define      C6DOFIMU12_G_TRIGGER_NO_ERROR                        0x00
#define      C6DOFIMU12_G_TRIGGER_PRECON_ERROR                    0x01
#define      C6DOFIMU12_G_TRIGGER_DL_ERROR                        0x02
#define      C6DOFIMU12_G_TRIGGER_ABORT_ERROR                     0x03

// Variant specific features selection
#define      C6DOFIMU12_CRT_RTOSK_ENABLE                          0x01
#define      C6DOFIMU12_GYRO_CROSS_SENS_ENABLE                    0x02
#define      C6DOFIMU12_GYRO_USER_GAIN_ENABLE                     0x08
#define      C6DOFIMU12_NO_FEATURE_ENABLE                         0x00
#define      C6DOFIMU12_CRT_IN_FIFO_NOT_REQ                       0x10
#define      C6DOFIMU12_MINIMAL_VARIANT                           0x20

// Check error
#define      C6DOFIMU12_ERROR                                     0x00
#define      C6DOFIMU12_SUCCESS                                   0x01

/** \defgroup spi SPI
 * \{
 */
#define      C6DOFIMU12_SPI_CMD_WRITE                             0x00
#define      C6DOFIMU12_SPI_CMD_READ                              0x80
#define      C6DOFIMU12_SPI_COMMUNICATION_DUMMY                   0x00
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  c6dofimu12_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c6dofimu12_master_io_t )( struct c6dofimu12_s*, uint8_t, uint8_t*, uint16_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct c6dofimu12_s
{
    // Input pins 

    digital_out_t cs;
    digital_in_t pwm;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    c6dofimu12_master_io_t  write_f;
    c6dofimu12_master_io_t  read_f;
    c6dofimu12_select_t master_sel;
} c6dofimu12_t;

typedef struct c6dofimu12_accel_t
{
    int16_t x;
    int16_t y;
    int16_t z;
} c6dofimu12_accel_t;

typedef struct c6dofimu12_gyro_t
{
    int16_t x;
    int16_t y;
    int16_t z;
} c6dofimu12_gyro_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;
    
    // Additional gpio pins 

    pin_name_t pwm;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    c6dofimu12_select_t sel;

} c6dofimu12_cfg_t;

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
void c6dofimu12_cfg_setup ( c6dofimu12_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C6DOFIMU12_RETVAL c6dofimu12_init ( c6dofimu12_t *ctx, c6dofimu12_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 6DOF IMU 12 click.
 */
void c6dofimu12_default_cfg ( c6dofimu12_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void c6dofimu12_generic_write ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void c6dofimu12_generic_read ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

/**
 * @brief Check ID function
 * 
 * @param ctx                    Click object.
 * 
 * @return ID status:
 * - 0 ( C6DOFIMU12_ERROR )    : Check ID Error;
 * - 1 ( C6DOFIMU12_SUCCESS )  : Check ID Success;
 * 
 * @description Function check status initialization of the device
 * of BMI270 6-axis, smart, low-power Inertial Measurement
 * on 6DOF IMU 12 Click board.
 */
C6DOFIMU12_RETVAL c6dofimu12_check_id ( c6dofimu12_t *ctx );

/**
 * @brief Check ID function
 * 
 * @param ctx                   Click object.
 * 
 * @return ID status:
 * - 0 ( C6DOFIMU12_ERROR )    : Check init Error;
 * - 1 ( C6DOFIMU12_SUCCESS )  : Check init Success;
 * 
 * @description Function check status initialization of the device
 * of BMI270 6-axis, smart, low-power Inertial Measurement
 * on 6DOF IMU 12 Click board.
 */
C6DOFIMU12_RETVAL c6dofimu12_check_init_status ( c6dofimu12_t *ctx );

/**
 * @brief Read Accel and Gyro data function
 *
 * 
 * @param ctx           Click object.
 * @param accel_data    Pointer to memory location where Accel data be stored
 * @param gyro_data     Pointer to memory location where Gyro data be stored
 *
 * @description Function reads Accel and Gyro 16-bit ( signed )
 * X-axis, Y-axis data and Z-axis data from the 12
 * targeted starts from C6DOFIMU12_REG_ACC_X_LSB_ADDR register address
 * of BMI270 6-axis, smart, low-power Inertial Measurement
 * on 6DOF IMU 12 Click board.
 */
void c6dofimu12_get_data ( c6dofimu12_t *ctx, c6dofimu12_accel_t *accel_data, c6dofimu12_gyro_t *gyro_data );


/**
 * @brief Get interrupt 1 status function
 *
 * @param ctx     Click object.
 * 
 * @return   Interrupt 1 state: 0 - Not active | 1 - Active
 *
 * @description Function check interrupt 1 state by return state
 * of the INT pin of 6DOF IMU 12 Click board.
*/
C6DOFIMU12_RETVAL c6dofimu12_check_int1 ( c6dofimu12_t *ctx );


/**
 * @brief Get interrupt 2 status function
 *
 * @param ctx     Click object.
 * 
 * @return   Interrupt 2 state: 0 - Not active | 1 - Active
 *
 * @description Function check interrupt 2 state by return state
 * of the INT pin of 6DOF IMU 12 Click board.
*/
C6DOFIMU12_RETVAL c6dofimu12_check_int2 ( c6dofimu12_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU12_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
