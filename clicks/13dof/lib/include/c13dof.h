/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright (c) 2019, MikroElektronika - www.mikroe.com
//  * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 * \brief This file contains API for 13DOF Click driver.
 *
 * \addtogroup c13dof 13DOF Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C13DOF_H
#define C13DOF_H

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
#define C13DOF_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C13DOF_RETVAL       uint8_t

#define C13DOF_OK           0x00
#define C13DOF_INIT_ERROR   0xFF
/** \} */

#define C13DOF_POLL_PERIOD_MS                                      10

/**
 * \defgroup macros BME680
 * \{
 */
#define C13DOF_BME680_DEVICE_SLAVE_ADDR_0                                 0x76
#define C13DOF_BME680_DEVICE_SLAVE_ADDR_1                                 0x77
#define C13DOF_BME680_CHIP_ID                                             0x61
#define C13DOF_BME680_COEFF_SIZE                                          41
#define C13DOF_BME680_COEFF_ADDR1_LEN                                     25
#define C13DOF_BME680_COEFF_ADDR2_LEN                                     16
#define C13DOF_BME680_FIELD_LENGTH                                        15
#define C13DOF_BME680_FIELD_ADDR_OFFSET                                   17
#define C13DOF_BME680_SOFT_RESET_CMD                                      0xB6
#define C13DOF_BME680_DEVICE_OK                                           0
#define C13DOF_BME680_DEVICE_ERROR                                        1
#define C13DOF_BME680_E_NULL_PTR                                          -1
#define C13DOF_BME680_E_COM_FAIL                                          -2
#define C13DOF_BME680_E_DEV_NOT_FOUND                                     -3
#define C13DOF_BME680_E_INVALID_LENGTH                                    -4
#define C13DOF_BME680_W_DEFINE_PWR_MODE                                   1
#define C13DOF_BME680_W_NO_NEW_DATA                                       2
#define C13DOF_BME680_I_MIN_CORRECTION                                    1
#define C13DOF_BME680_I_MAX_CORRECTION                                    2
#define C13DOF_BME680_ADDR_RES_HEAT_VAL_ADDR                              0x00
#define C13DOF_BME680_ADDR_RES_HEAT_RANGE_ADDR                            0x02
#define C13DOF_BME680_ADDR_RANGE_SW_ERR_ADDR                              0x04
#define C13DOF_BME680_ADDR_SENS_CONF_START                                0x5A
#define C13DOF_BME680_ADDR_GAS_CONF_START                                 0x64
#define C13DOF_BME680_FIELD0_ADDR                                         0x1D
#define C13DOF_BME680_RES_HEAT0_ADDR                                      0x5A
#define C13DOF_BME680_GAS_WAIT0_ADDR                                      0x64
#define C13DOF_BME680_CONF_HEAT_CTRL_ADDR                                 0x70
#define C13DOF_BME680_CONF_ODR_RUN_GAS_NBC_ADDR                           0x71
#define C13DOF_BME680_CONF_OS_H_ADDR                                      0x72
#define C13DOF_BME680_MEM_PAGE_ADDR                                       0xf3
#define C13DOF_BME680_CONF_T_P_MODE_ADDR                                  0x74
#define C13DOF_BME680_CONF_ODR_FILT_ADDR                                  0x75
#define C13DOF_BME680_COEFF_ADDR1                                         0x89
#define C13DOF_BME680_COEFF_ADDR2                                         0xe1
#define C13DOF_BME680_CHIP_ID_ADDR                                        0xD0
#define C13DOF_BME680_SOFT_RESET_ADDR                                     0xE0
#define C13DOF_BME680_ENABLE_HEATER                                       0x00
#define C13DOF_BME680_DISABLE_HEATER                                      0x08
#define C13DOF_BME680_DISABLE_GAS_MEAS                                    0x00
#define C13DOF_BME680_ENABLE_GAS_MEAS                                     0x01
#define C13DOF_BME680_OS_NONE                                             0
#define C13DOF_BME680_OS_1X                                               1
#define C13DOF_BME680_OS_2X                                               2
#define C13DOF_BME680_OS_4X                                               3
#define C13DOF_BME680_OS_8X                                               4
#define C13DOF_BME680_OS_16X                                              5
#define C13DOF_BME680_FILTER_SIZE_0                                       0
#define C13DOF_BME680_FILTER_SIZE_1                                       1
#define C13DOF_BME680_FILTER_SIZE_3                                       2
#define C13DOF_BME680_FILTER_SIZE_7                                       3
#define C13DOF_BME680_FILTER_SIZE_15                                      4
#define C13DOF_BME680_FILTER_SIZE_31                                      5
#define C13DOF_BME680_FILTER_SIZE_63                                      6
#define C13DOF_BME680_FILTER_SIZE_127                                     7
#define C13DOF_BME680_SLEEP_MODE                                          0
#define C13DOF_BME680_FORCED_MODE                                         1
#define C13DOF_BME680_RESET_PERIOD                                        10
#define C13DOF_BME680_MEM_PAGE0                                           0x10
#define C13DOF_BME680_MEM_PAGE1                                           0x00
#define C13DOF_BME680_HUM_REG_SHIFT_VAL                                   4
#define C13DOF_BME680_RUN_GAS_DISABLE                                     0
#define C13DOF_BME680_RUN_GAS_ENABLE                                      1
#define C13DOF_BME680_TMP_BUFFER_LENGTH                                   40
#define C13DOF_BME680_REG_BUFFER_LENGTH                                   6 
#define C13DOF_BME680_FIELD_DATA_LENGTH                                   3 
#define C13DOF_BME680_GAS_REG_BUF_LENGTH                                  20
#define C13DOF_BME680_OST_SEL                                             1
#define C13DOF_BME680_OSP_SEL                                             2
#define C13DOF_BME680_OSH_SEL                                             4
#define C13DOF_BME680_GAS_MEAS_SEL                                        8
#define C13DOF_BME680_FILTER_SEL                                          16
#define C13DOF_BME680_HCNTRL_SEL                                          32
#define C13DOF_BME680_RUN_GAS_SEL                                         64
#define C13DOF_BME680_NBCONV_SEL                                          128
#define C13DOF_BME680_GAS_SENSOR_SEL                                      ( C13DOF_BME680_GAS_MEAS_SEL | \
                                                                                      C13DOF_BME680_RUN_GAS_SEL | \
                                                                                      C13DOF_BME680_NBCONV_SEL )
#define C13DOF_BME680_NBCONV_MIN                                          0
#define C13DOF_BME680_NBCONV_MAX                                          10
#define C13DOF_BME680_GAS_MEAS_MSK                                        0x30
#define C13DOF_BME680_NBCONV_MSK                                          0X0F
#define C13DOF_BME680_FILTER_MSK                                          0X1C
#define C13DOF_BME680_OST_MSK                                             0XE0
#define C13DOF_BME680_OSP_MSK                                             0X1C
#define C13DOF_BME680_OSH_MSK                                             0X07
#define C13DOF_BME680_HCTRL_MSK                                           0x08
#define C13DOF_BME680_RUN_GAS_MSK                                         0x10
#define C13DOF_BME680_MODE_MSK                                            0x03
#define C13DOF_BME680_RHRANGE_MSK                                         0x30
#define C13DOF_BME680_RSERROR_MSK                                         0xf0
#define C13DOF_BME680_NEW_DATA_MSK                                        0x80
#define C13DOF_BME680_GAS_INDEX_MSK                                       0x0f
#define C13DOF_BME680_GAS_RANGE_MSK                                       0x0f
#define C13DOF_BME680_GASM_VALID_MSK                                      0x20
#define C13DOF_BME680_HEAT_STAB_MSK                                       0x10
#define C13DOF_BME680_MEM_PAGE_MSK                                        0x10
#define C13DOF_BME680_SPI_RD_MSK                                          0x80
#define C13DOF_BME680_SPI_WR_MSK                                          0x7f
#define C13DOF_BME680_BIT_H1_DATA_MSK                                     0x0F
#define C13DOF_BME680_GAS_MEAS_POS                                        4
#define C13DOF_BME680_FILTER_POS                                          2
#define C13DOF_BME680_OST_POS                                             5
#define C13DOF_BME680_OSP_POS                                             2
#define C13DOF_BME680_RUN_GAS_POS                                         4
#define C13DOF_BME680_T2_LSB_REG                                          1
#define C13DOF_BME680_T2_MSB_REG                                          2
#define C13DOF_BME680_T3_REG                                              3
#define C13DOF_BME680_P1_LSB_REG                                          5
#define C13DOF_BME680_P1_MSB_REG                                          6
#define C13DOF_BME680_P2_LSB_REG                                          7
#define C13DOF_BME680_P2_MSB_REG                                          8
#define C13DOF_BME680_P3_REG                                              9
#define C13DOF_BME680_P4_LSB_REG                                          11
#define C13DOF_BME680_P4_MSB_REG                                          12
#define C13DOF_BME680_P5_LSB_REG                                          13
#define C13DOF_BME680_P5_MSB_REG                                          14
#define C13DOF_BME680_P7_REG                                              15
#define C13DOF_BME680_P6_REG                                              16
#define C13DOF_BME680_P8_LSB_REG                                          19
#define C13DOF_BME680_P8_MSB_REG                                          20
#define C13DOF_BME680_P9_LSB_REG                                          21
#define C13DOF_BME680_P9_MSB_REG                                          22
#define C13DOF_BME680_P10_REG                                             23
#define C13DOF_BME680_H2_MSB_REG                                          25
#define C13DOF_BME680_H2_LSB_REG                                          26
#define C13DOF_BME680_H1_LSB_REG                                          26
#define C13DOF_BME680_H1_MSB_REG                                          27
#define C13DOF_BME680_H3_REG                                              28
#define C13DOF_BME680_H4_REG                                              29
#define C13DOF_BME680_H5_REG                                              30
#define C13DOF_BME680_H6_REG                                              31
#define C13DOF_BME680_H7_REG                                              32
#define C13DOF_BME680_T1_LSB_REG                                          33
#define C13DOF_BME680_T1_MSB_REG                                          34
#define C13DOF_BME680_GH2_LSB_REG                                         35
#define C13DOF_BME680_GH2_MSB_REG                                         36
#define C13DOF_BME680_GH1_REG                                             37
#define C13DOF_BME680_GH3_REG                                             38
#define C13DOF_BME680_REG_FILTER_INDEX                                    5
#define C13DOF_BME680_REG_TEMP_INDEX                                      4
#define C13DOF_BME680_REG_PRES_INDEX                                      4
#define C13DOF_BME680_REG_HUM_INDEX                                       2
#define C13DOF_BME680_REG_NBCONV_INDEX                                    1
#define C13DOF_BME680_REG_RUN_GAS_INDEX                                   1
#define C13DOF_BME680_REG_HCTRL_INDEX                                     0
#define C13DOF_BME680_MAX_OVERFLOW_VAL                                    0x40000000
#define C13DOF_BME680_DATA_TEMPERATURE                                    0x01
#define C13DOF_BME680_DATA_PRESSURE                                       0x02
#define C13DOF_BME680_DATA_HUMIDITY                                       0x03
#define C13DOF_BME680_OK                                                  0x01
#define C13DOF_BME680_ERROR                                               0x00
/** \} */

/**
 * \defgroup bmm150_registers BMM150 Registers 
 * \{
 */
#define C13DOF_BMM150_DEVICE_SLAVE_ADDR                                   0x10
#define C13DOF_BMM150_DUMMY                                               0x00
#define C13DOF_BMM150_ID_REG                                              0x40
#define C13DOF_BMM150_RESERVED1_REG                                       0x41
#define C13DOF_BMM150_DATAX_LSB_REG                                       0x42
#define C13DOF_BMM150_DATAX_MSB_REG                                       0x43
#define C13DOF_BMM150_DATAY_LSB_REG                                       0x44
#define C13DOF_BMM150_DATAY_MSB_REG                                       0x45
#define C13DOF_BMM150_DATAZ_LSB_REG                                       0x46
#define C13DOF_BMM150_DATAZ_MSB_REG                                       0x47
#define C13DOF_BMM150_RHALL_LSB_REG                                       0x48
#define C13DOF_BMM150_RHALL_MSB_REG                                       0x49
#define C13DOF_BMM150_INTERRUPT_STATUS_REG                                0x4A
#define C13DOF_BMM150_POWER_AND_RESET_CON_REG                             0x4B
#define C13DOF_BMM150_DATARATE_AND_OPMODE_CON_REG                         0x4C
#define C13DOF_BMM150_INTERR_AND_AXIS_EN_REG                              0x4D
#define C13DOF_BMM150_INTERR_AND_CHANNEL_EN_REG                           0x4E
#define C13DOF_BMM150_LOW_THRESHOLD_REG                                   0x4F
#define C13DOF_BMM150_HIGH_THRESHOLD_REG                                  0x50
#define C13DOF_BMM150_REPETITION_XY_CON_REG                               0x51
#define C13DOF_BMM150_REPETITION_Z_CON_REG                                0x52
#define C13DOF_BMM150_RESERVED2_REG                                       0x53
#define C13DOF_BMM150_RESERVED3_REG                                       0x54
#define C13DOF_BMM150_RESERVED4_REG                                       0x55
#define C13DOF_BMM150_RESERVED5_REG                                       0x56
#define C13DOF_BMM150_RESERVED6_REG                                       0x57
#define C13DOF_BMM150_RESERVED7_REG                                       0x58
#define C13DOF_BMM150_RESERVED8_REG                                       0x59
#define C13DOF_BMM150_RESERVED9_REG                                       0x5A
#define C13DOF_BMM150_RESERVED10_REG                                      0x5B
#define C13DOF_BMM150_RESERVED11_REG                                      0x5C
#define C13DOF_BMM150_RESERVED12_REG                                      0x5D
#define C13DOF_BMM150_RESERVED13_REG                                      0x5E
#define C13DOF_BMM150_RESERVED14_REG                                      0x5F
#define C13DOF_BMM150_RESERVED15_REG                                      0x60
#define C13DOF_BMM150_RESERVED16_REG                                      0x61
#define C13DOF_BMM150_RESERVED17_REG                                      0x62
#define C13DOF_BMM150_RESERVED18_REG                                      0x63
#define C13DOF_BMM150_RESERVED19_REG                                      0x64
#define C13DOF_BMM150_RESERVED20_REG                                      0x65
#define C13DOF_BMM150_RESERVED21_REG                                      0x66
#define C13DOF_BMM150_RESERVED22_REG                                      0x67
#define C13DOF_BMM150_RESERVED23_REG                                      0x68
#define C13DOF_BMM150_RESERVED24_REG                                      0x69
#define C13DOF_BMM150_RESERVED25_REG                                      0x6A
#define C13DOF_BMM150_RESERVED26_REG                                      0x6B
#define C13DOF_BMM150_RESERVED27_REG                                      0x6C
#define C13DOF_BMM150_RESERVED28_REG                                      0x6D
#define C13DOF_BMM150_RESERVED29_REG                                      0x6E
#define C13DOF_BMM150_RESERVED30_REG                                      0x6F
#define C13DOF_BMM150_RESERVED31_REG                                      0x70
#define C13DOF_BMM150_RESERVED32_REG                                      0x71
#define C13DOF_BMM150_OK                                                  0x00
#define C13DOF_BMM150_ADDR_ERR                                            0x01
#define C13DOF_BMM150_INTERRUPT_OCCURED                                   0x02
#define C13DOF_BMM150_NBYTES_ERR                                          0x03
#define C13DOF_BMM150_DATA_READY                                          0x01
#define C13DOF_BMM150_DATA_NOT_READY                                      0x00
#define C13DOF_BMM150_SUSPEND_MODE_SPI4_EN                                0x00
#define C13DOF_BMM150_SLEEP_MODE                                          0x01
#define C13DOF_BMM150_SOFT_RESET_EN                                       0x82
#define C13DOF_BMM150_SPI3_EN                                             0x04
#define C13DOF_BMM150_NORMAL_OPMODE_DR_10HZ                               0x00
#define C13DOF_BMM150_FORCED_OPMODE                                       0x02
#define C13DOF_BMM150_SLEEP_OPMODE                                        0x06
#define C13DOF_BMM150_DR_2HZ                                              0x08
#define C13DOF_BMM150_DR_6HZ                                              0x10
#define C13DOF_BMM150_DR_8HZ                                              0x18
#define C13DOF_BMM150_DR_15HZ                                             0x20
#define C13DOF_BMM150_DR_20HZ                                             0x28
#define C13DOF_BMM150_DR_25HZ                                             0x30
#define C13DOF_BMM150_DR_30HZ                                             0x38
#define C13DOF_BMM150_INTERR_DISABLED_THRESHOLDS_ENABLED                  0x00
#define C13DOF_BMM150_LOWTHRESHOLD_X_DISABLED                             0x01
#define C13DOF_BMM150_LOWTHRESHOLD_Y_DISABLED                             0x02
#define C13DOF_BMM150_LOWTHRESHOLD_Z_DISABLED                             0x04
#define C13DOF_BMM150_HIGHTHRESHOLD_X_DISABLED                            0x08
#define C13DOF_BMM150_HIGHTHRESHOLD_Y_DISABLED                            0x10
#define C13DOF_BMM150_HIGHTHRESHOLD_Z_DISABLED                            0x20
#define C13DOF_BMM150_OVERFLOW_PIN_IND_EN                                 0x40
#define C13DOF_BMM150_DATAOVERRUN_IND_EN                                  0x80
#define C13DOF_BMM150_CHANNELS_ENABLED_INTERR_DATAREADY_ACTIVE_LOW        0x00
#define C13DOF_BMM150_INTERR_PIN_ACTIVE_HIGH                              0x01
#define C13DOF_BMM150_INTERR_LATCHED                                      0x02
#define C13DOF_BMM150_DATAREADY_ACTIVE_HIGH                               0x04
#define C13DOF_BMM150_CHANNEL_X_DISABLED                                  0x08
#define C13DOF_BMM150_CHANNEL_Y_DISABLED                                  0x10
#define C13DOF_BMM150_CHANNEL_Z_DISABLED                                  0x20
#define C13DOF_BMM150_INTERR_PIN_EN                                       0x40
#define C13DOF_BMM150_DATAREADY_PIN_EN                                    0x80
/** \} */

/**
 * \defgroup bmi088_registers BMI088 Registers
 * \{
 */
#define C13DOF_BMI088_ACCEL_SLAVE_ADDR                                    0x18
#define C13DOF_BMI088_GYRO_SLAVE_ADDR                                     0x68
#define C13DOF_BMI088_ACCEL_CHIP_ID_REG                                   0x00
#define C13DOF_BMI088_ACCEL_ERR_REG                                       0x02
#define C13DOF_BMI088_ACCEL_STATUS_REG                                    0x03
#define C13DOF_BMI088_ACCEL_X_LSB_REG                                     0x12
#define C13DOF_BMI088_ACCEL_X_MSB_REG                                     0x13
#define C13DOF_BMI088_ACCEL_Y_LSB_REG                                     0x14
#define C13DOF_BMI088_ACCEL_Y_MSB_REG                                     0x15
#define C13DOF_BMI088_ACCEL_Z_LSB_REG                                     0x16
#define C13DOF_BMI088_ACCEL_Z_MSB_REG                                     0x17
#define C13DOF_BMI088_ACCEL_SENSORTIME_0_REG                              0x18
#define C13DOF_BMI088_ACCEL_SENSORTIME_1_REG                              0x19
#define C13DOF_BMI088_ACCEL_SENSORTIME_2_REG                              0x1A
#define C13DOF_BMI088_ACCEL_INT_STAT_0_REG                                0x1C
#define C13DOF_BMI088_ACCEL_INT_STAT_1_REG                                0x1D
#define C13DOF_BMI088_ACCEL_GP_0_REG                                      0x1E
#define C13DOF_BMI088_TEMP_MSB_REG                                        0x22
#define C13DOF_BMI088_TEMP_LSB_REG                                        0x23
#define C13DOF_BMI088_ACCEL_GP_4_REG                                      0x27
#define C13DOF_BMI088_ACCEL_INTERNAL_STAT_REG                             0x2A
#define C13DOF_BMI088_ACCEL_CONF_REG                                      0x40
#define C13DOF_BMI088_ACCEL_RANGE_REG                                     0x41
#define C13DOF_BMI088_ACCEL_INT1_IO_CONF_REG                              0x53
#define C13DOF_BMI088_ACCEL_INT2_IO_CONF_REG                              0x54
#define C13DOF_BMI088_ACCEL_INT_LATCH_CONF_REG                            0x55
#define C13DOF_BMI088_ACCEL_INT1_MAP_REG                                  0x56
#define C13DOF_BMI088_ACCEL_INT2_MAP_REG                                  0x57
#define C13DOF_BMI088_ACCEL_INT1_INT2_MAP_DATA_REG                        0x58
#define C13DOF_BMI088_ACCEL_INIT_CTRL_REG                                 0x59
#define C13DOF_BMI088_ACCEL_SELF_TEST_REG                                 0x6D
#define C13DOF_BMI088_ACCEL_PWR_CONF_REG                                  0x7C
#define C13DOF_BMI088_ACCEL_PWR_CTRL_REG                                  0x7D
#define C13DOF_BMI088_ACCEL_SOFTRESET_REG                                 0x7E
#define C13DOF_BMI088_ACCEL_CHIP_ID                                       0x1E
#define C13DOF_BMI088_ACCEL_I2C_ADDR_PRIMARY                              0x18
#define C13DOF_BMI088_ACCEL_I2C_ADDR_SECONDARY                            0x19
#define C13DOF_BMI088_ACCEL_RESERVED_5B_REG                               0x5B
#define C13DOF_BMI088_ACCEL_RESERVED_5C_REG                               0x5C
#define C13DOF_BMI088_ACCEL_FEATURE_CFG_REG                               0x5E
#define C13DOF_BMI088_ACCEL_DATA_READY_INT                                0x80
#define C13DOF_BMI088_ACCEL_BW_OSR4                                       0x00
#define C13DOF_BMI088_ACCEL_BW_OSR2                                       0x01
#define C13DOF_BMI088_ACCEL_BW_NORMAL                                     0x02
#define C13DOF_BMI088_ACCEL_ODR_12_5_HZ                                   0x05
#define C13DOF_BMI088_ACCEL_ODR_25_HZ                                     0x06
#define C13DOF_BMI088_ACCEL_ODR_50_HZ                                     0x07
#define C13DOF_BMI088_ACCEL_ODR_100_HZ                                    0x08
#define C13DOF_BMI088_ACCEL_ODR_200_HZ                                    0x09
#define C13DOF_BMI088_ACCEL_ODR_400_HZ                                    0x0A
#define C13DOF_BMI088_ACCEL_ODR_800_HZ                                    0x0B
#define C13DOF_BMI088_ACCEL_ODR_1600_HZ                                   0x0C
#define C13DOF_BMI088_ACCEL_SWITCH_OFF_SELF_TEST                          0x00
#define C13DOF_BMI088_ACCEL_POSITIVE_SELF_TEST                            0x0D
#define C13DOF_BMI088_ACCEL_NEGATIVE_SELF_TEST                            0x09
#define C13DOF_BMI088_ACCEL_PM_ACTIVE                                     0x00
#define C13DOF_BMI088_ACCEL_PM_SUSPEND                                    0x03
#define C13DOF_BMI088_ACCEL_POWER_DISABLE                                 0x00
#define C13DOF_BMI088_ACCEL_POWER_ENABLE                                  0x04
#define C13DOF_BMI088_ACCEL_INTA_DISABLE                                  0x00
#define C13DOF_BMI088_ACCEL_INTA_ENABLE                                   0x01
#define C13DOF_BMI088_ACCEL_INTB_DISABLE                                  0x00
#define C13DOF_BMI088_ACCEL_INTB_ENABLE                                   0x02
#define C13DOF_BMI088_ACCEL_SOFTRESET_DELAY_MS                            1
#define C13DOF_BMI088_FATAL_ERR_MASK                                      0x01
#define C13DOF_BMI088_ERR_CODE_MASK                                       0x1C
#define C13DOF_BMI088_CMD_ERR_POS                                         1
#define C13DOF_BMI088_ERR_CODE_POS                                        2
#define C13DOF_BMI088_ACCEL_STATUS_MASK                                   0x80
#define C13DOF_BMI088_ACCEL_STATUS_POS                                    7
#define C13DOF_BMI088_ACCEL_ODR_MASK                                      0x0F
#define C13DOF_BMI088_ACCEL_BW_MASK                                       0x70
#define C13DOF_BMI088_ACCEL_RANGE_MASK                                    0x03
#define C13DOF_BMI088_ACCEL_BW_POS                                        4
#define C13DOF_BMI088_ACCEL_INT_EDGE_MASK                                 0x01
#define C13DOF_BMI088_ACCEL_INT_LVL_MASK                                  0x02
#define C13DOF_BMI088_ACCEL_INT_OD_MASK                                   0x04
#define C13DOF_BMI088_ACCEL_INT_IO_MASK                                   0x08
#define C13DOF_BMI088_ACCEL_INT_IN_MASK                                   0x10
#define C13DOF_BMI088_ACCEL_INT_EDGE_POS                                  0
#define C13DOF_BMI088_ACCEL_INT_LVL_POS                                   1
#define C13DOF_BMI088_ACCEL_INT_OD_POS                                    2
#define C13DOF_BMI088_ACCEL_INT_IO_POS                                    3
#define C13DOF_BMI088_ACCEL_INT_IN_POS                                    4
#define C13DOF_BMI088_ACCEL_MAP_INTA_MASK                                 0x01
#define C13DOF_BMI088_ACCEL_MAP_INTA_POS                                  0x00
#define C13DOF_BMI088_ACCEL_INT1_DRDY_MASK                                0x04
#define C13DOF_BMI088_ACCEL_INT2_DRDY_MASK                                0x40
#define C13DOF_BMI088_ACCEL_INT1_DRDY_POS                                 2
#define C13DOF_BMI088_ACCEL_INT2_DRDY_POS                                 6
#define C13DOF_BMI088_ASIC_INITIALIZED                                    0x01
#define C13DOF_BMI088_GYRO_CHIP_ID_REG                                    0x00
#define C13DOF_BMI088_GYRO_X_LSB_REG                                      0x02
#define C13DOF_BMI088_GYRO_X_MSB_REG                                      0x03
#define C13DOF_BMI088_GYRO_Y_LSB_REG                                      0x04
#define C13DOF_BMI088_GYRO_Y_MSB_REG                                      0x05
#define C13DOF_BMI088_GYRO_Z_LSB_REG                                      0x06
#define C13DOF_BMI088_GYRO_Z_MSB_REG                                      0x07
#define C13DOF_BMI088_GYRO_INT_STAT_1_REG                                 0x0A
#define C13DOF_BMI088_GYRO_RANGE_REG                                      0x0F
#define C13DOF_BMI088_GYRO_BANDWIDTH_REG                                  0x10
#define C13DOF_BMI088_GYRO_LPM1_REG                                       0x11
#define C13DOF_BMI088_GYRO_SOFTRESET_REG                                  0x14
#define C13DOF_BMI088_GYRO_INT_CTRL_REG                                   0x15
#define C13DOF_BMI088_GYRO_INT3_INT4_IO_CONF_REG                          0x16
#define C13DOF_BMI088_GYRO_INT3_INT4_IO_MAP_REG                           0x18
#define C13DOF_BMI088_GYRO_SELF_TEST_REG                                  0x3C
#define C13DOF_BMI088_GYRO_CHIP_ID                                        0x0F
#define C13DOF_BMI088_GYRO_I2C_ADDR_PRIMARY                               0x68
#define C13DOF_BMI088_GYRO_I2C_ADDR_SECONDARY                             0x69
#define C13DOF_BMI088_GYRO_RANGE_2000_DPS                                 0x00
#define C13DOF_BMI088_GYRO_RANGE_1000_DPS                                 0x01
#define C13DOF_BMI088_GYRO_RANGE_500_DPS                                  0x02
#define C13DOF_BMI088_GYRO_RANGE_250_DPS                                  0x03
#define C13DOF_BMI088_GYRO_RANGE_125_DPS                                  0x04
#define C13DOF_BMI088_GYRO_BW_532_ODR_2000_HZ                             0x00
#define C13DOF_BMI088_GYRO_BW_230_ODR_2000_HZ                             0x01
#define C13DOF_BMI088_GYRO_BW_116_ODR_1000_HZ                             0x02
#define C13DOF_BMI088_GYRO_BW_47_ODR_400_HZ                               0x03
#define C13DOF_BMI088_GYRO_BW_23_ODR_200_HZ                               0x04
#define C13DOF_BMI088_GYRO_BW_12_ODR_100_HZ                               0x05
#define C13DOF_BMI088_GYRO_BW_64_ODR_200_HZ                               0x06
#define C13DOF_BMI088_GYRO_BW_32_ODR_100_HZ                               0x07
#define C13DOF_BMI088_GYRO_ODR_RESET_VAL                                  0x80
#define C13DOF_BMI088_GYRO_PM_NORMAL                                      0x00
#define C13DOF_BMI088_GYRO_PM_DEEP_SUSPEND                                0x20
#define C13DOF_BMI088_GYRO_PM_SUSPEND                                     0x80
#define C13DOF_BMI088_GYRO_DRDY_INT_DISABLE_VAL                           0x00
#define C13DOF_BMI088_GYRO_DRDY_INT_ENABLE_VAL                            0x80
#define C13DOF_BMI088_GYRO_MAP_DRDY_TO_INT3                               0x01
#define C13DOF_BMI088_GYRO_MAP_DRDY_TO_INT4                               0x80
#define C13DOF_BMI088_GYRO_MAP_DRDY_TO_BOTH_INT3_INT4                     0x81
#define C13DOF_BMI088_GYRO_SOFTRESET_DELAY                                30
#define C13DOF_BMI088_GYRO_POWER_MODE_CONFIG_DELAY                        30
#define C13DOF_BMI088_GYRO_RANGE_MASK                                     0x07
#define C13DOF_BMI088_GYRO_BW_MASK                                        0x0F
#define C13DOF_BMI088_GYRO_POWER_MASK                                     0xA0
#define C13DOF_BMI088_GYRO_POWER_POS                                      5
#define C13DOF_BMI088_GYRO_DATA_EN_MASK                                   0x80
#define C13DOF_BMI088_GYRO_DATA_EN_POS                                    7
#define C13DOF_BMI088_GYRO_INT3_LVL_MASK                                  0x01
#define C13DOF_BMI088_GYRO_INT3_OD_MASK                                   0x02
#define C13DOF_BMI088_GYRO_INT4_LVL_MASK                                  0x04
#define C13DOF_BMI088_GYRO_INT4_OD_MASK                                   0x08
#define C13DOF_BMI088_GYRO_INT3_OD_POS                                    1
#define C13DOF_BMI088_GYRO_INT4_LVL_POS                                   2
#define C13DOF_BMI088_GYRO_INT4_OD_POS                                    3
#define C13DOF_BMI088_GYRO_INT_EN_MASK                                    0x80
#define C13DOF_BMI088_GYRO_INT_EN_POS                                     7
#define C13DOF_BMI088_GYRO_INT3_MAP_MASK                                  0x01
#define C13DOF_BMI088_GYRO_INT4_MAP_MASK                                  0x80
#define C13DOF_BMI088_GYRO_INT3_MAP_POS                                   0
#define C13DOF_BMI088_GYRO_INT4_MAP_POS                                   7
#define C13DOF_BMI088_OK                                                  0x00
#define C13DOF_BMI088_ERROR                                               0x01
#define T_C13DOF_P                             const uint8_t*
#define C13DOF_BME680_RETVAL_T                       uint8_t
#define C13DOF_BMM150_RETVAL_T                       uint8_t
#define C13DOF_BMI088_RETVAL_T                       uint8_t
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
    uint8_t status;
    uint8_t gas_index;
    uint8_t meas_index;
    int16_t temperature;
    float pressure;
    uint32_t humidity;
    uint32_t gas_resistance;

}T_C13DOF_BME680_FIELD_DATA;

typedef struct
{
    
    uint16_t par_h1;
    uint16_t par_h2;
    int8_t par_h3;
    int8_t par_h4;
    int8_t par_h5;
    uint8_t par_h6;
    int8_t par_h7;
    
    int8_t par_gh1;
    int16_t par_gh2;
    int8_t par_gh3;
    
    uint16_t par_t1;
    int16_t par_t2;
    int8_t par_t3;
    
    uint16_t par_p1;
    int16_t par_p2;
    int8_t par_p3;
    int16_t par_p4;
    int16_t par_p5;
    int8_t par_p6;
    int8_t par_p7;
    int16_t par_p8;
    int16_t par_p9;
    uint8_t par_p10;
    
    int32_t t_fine;
    
    uint8_t res_heat_range;
    int8_t res_heat_val;
    int8_t range_sw_err;

} T_C13DOF_BME680_CALIB_DATA;

typedef struct
{
    uint8_t os_hum;

    uint8_t os_temp;

    uint8_t os_pres;

    uint8_t filter;

}T_C13DOF_BME680_TPH_SETTINGS;


typedef struct
{
    uint8_t nb_conv;

    uint8_t heatr_ctrl;
    
    uint8_t run_gas;
    
    uint16_t heatr_temp;
    
    uint16_t heatr_dur;

}T_C13DOF_BME680_GAS_SETTINGS;

typedef struct
{
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t bme680_slave_address;
    uint8_t bmm150_slave_address;
    uint8_t bmi088Gyro_slave_address;
    uint8_t bmi088Accel_slave_address;

    T_C13DOF_BME680_FIELD_DATA  d_data;
    T_C13DOF_BME680_CALIB_DATA calib;
    T_C13DOF_BME680_TPH_SETTINGS tph_sett;
    T_C13DOF_BME680_GAS_SETTINGS gas_sett;

    uint8_t device_mem_page;
    uint8_t device_power_mode;

} c13dof_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t bme680_slave_address;
    uint8_t bmm150_slave_address;
    uint8_t bmi088Gyro_slave_address;
    uint8_t bmi088Accel_slave_address;

} c13dof_cfg_t;

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
void c13dof_cfg_setup ( c13dof_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C13DOF_RETVAL c13dof_init ( c13dof_t *ctx, c13dof_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for c13DOF click.
 */
void c13dof_default_cfg ( c13dof_t *ctx );

/**
 * @brief Generic BME680 write the byte of data function
 *
 *
 * @param ctx  Click object.
 *
 * @param reg_address                8-bit BME680 register address
 *
 * @param write_data                 Byte of data to write
 *
 * @description  Function write the 8-bit of data to the
 * target 8-bit register address of BME680 sensor on 13DOF Click board.
 */
void c13dof_bme680_write_byte ( c13dof_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Generic BME680 read byte of data function
 *
 *
 * @param ctx  Click object.
 *
 * @param reg_address                8-bit BME680 register address
 *
 * @returns
 * 8-bit read data
 *
 * @description Function read the 8-bit of data from the
 * target 8-bit register address of BME680 sensor on 13DOF Click board.
 */
uint8_t c13dof_bme680_read_byte ( c13dof_t *ctx, uint8_t reg_address );

/**
 * @brief Check BME680 device ID function
 *
 *
 * @param ctx  Click object.
 *
 * @returns status:
 * - 0 : ERROR;
 * - 1 : OK;
 *
 * @description Function check device ID by read ID value from the
 * sensor ID register address of BME680 sensor on 13DOF Click board.
 */
C13DOF_BME680_RETVAL_T c13dof_bme680_check_id( c13dof_t *ctx );

/**
 * @brief Get BME680 device ID function
 *
 *
 * @param ctx  Click object.
 *
 * @returns
 * 8-bit device ID value
 *
 * @description Function read device ID from the
 * sensor ID register address of BME680 sensor on 13DOF Click board.
 *
 * @note
 * Default device: ID = 0x61.
 */
uint8_t c13dof_bme680_get_device_id ( c13dof_t *ctx );

/**
 * @brief Software BME680 reset function
 *
 *
 * @param ctx  Click object.
 *
 * @description Function software reset by write value of 0xB6 to the
 * sensor reset register address of BME680 sensor on 13DOF Click board.
 */
void c13dof_bme680_soft_reset ( c13dof_t *ctx );

/**
 * @brief Get BME680 factory calibration parameters function
 *
 *
 * @param ctx  Click object.
 *
 * Function read factory calibration parameters value from the
 * sensor calibration registers address of BME680 sensor on 13DOF Click board.
 *
 * @note
 * @description This function must be called at least once at the beginning of the program
 * to read and store the calibration parameters in the memory.
 */
void c13dof_bme680_get_calibration_data ( c13dof_t *ctx );


/**
 * @brief Get BME680 ambient data function
 *
 *
 * @param ctx  Click object.
 *
 * @param data_in    Data for reading:
 * - Temperature : _C13DOF_BME680_DATA_TEMPERATURE ( 0x01 );
 * - Pressure    : _C13DOF_BME680_DATA_PRESSURE    ( 0x02 );
 * - Humidity    : _C13DOF_BME680_DATA_HUMIDITY    ( 0x03 );
 *
 * @returns
 * float ambient ( temperature, pressure or humidity ) data
 *
 * @description Function get ambient data by sets device force mode and read data from the
 * sensor temperature,  pressure or humidity register address
 * of BME680 sensor on 13DOF Click board.
 */
float c13dof_bme680_get_ambient_data ( c13dof_t *ctx, uint8_t data_in );

/**
 * @brief Gets BME680 temperature in degrees Celsius function
 *
 *
 * @param ctx  Click object.
 *
 * @returns
 * float value of temperature in degrees Celsius
 *
 *@description Function get temperature value in degrees Celsius [ �C ] from the
 * sensor temperature register address of BME680 sensor on 13DOF Click board.
 */
float c13dof_bme680_get_temperature ( c13dof_t *ctx );

/**
 * @brief Gets BME680 humidity in percentage [ % ] function
 *
 *
 * @param ctx  Click object.
 *
 * @returns
 * float value of humidity in percentage [ % ]
 *
 *@description Function get humidity value in percentage [ % ] from the
 * sensor humidity register address of BME680 sensor on 13DOF Click board.
 */
float c13dof_bme680_get_humidity ( c13dof_t *ctx );

/**
 * @brief Gets BME680 pressure in degrees Celsius function
 *
 *
 * @param ctx  Click object.
 *
 * @returns
 * float value of pressure in [ mbar ]
 *
 * @description Function get pressure value in [ mbar ] from the
 * sensor pressure register address of BME680 sensor on 13DOF Click board.
 */
float c13dof_bme680_get_pressure ( c13dof_t *ctx );

/**
 * @brief Gets BME680 gas resistance data function
 *
 *
 * @param ctx  Click object.
 *
 * @returns
 * 32-bite gas resistance data
 *
 * @description Function get gas resistance value from the
 * sensor gas resistance register address of BME680 sensor on 13DOF Click board.
 */
uint32_t c13dof_bme680_get_gas_resistance ( c13dof_t *ctx );

/**
 * @brief Generic BMM150 write the byte of data function
 *
 *
 * @param ctx  Click object.
 *
 * @param reg_address                8-bit BMM150 register address
 *
 * @param write_data                 Byte of data to write
 *
 * Function write the 8-bit of data to the
 * target 8-bit register address of BMM150 sensor on 13DOF Click board.
 */
C13DOF_BMM150_RETVAL_T c13dof_bmm150_write_byte ( c13dof_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Generic BMM150 read byte of data function
 *
 *
 * @param ctx  Click object.
 *
 * @param reg_address                8-bit BMM150 register address
 *
 * @returns
 * 8-bit read data
 *
 * @description Function read the 8-bit of data from the
 * target 8-bit register address of BMM150 sensor on 13DOF Click board.
 */
uint8_t c13dof_bmm150_read_byte ( c13dof_t *ctx, uint8_t reg_address );

/**
 * @brief Generic BMM150 sequential data read function
 *
 *
 * @param ctx  Click object.
 *
 * @param data_out                  pointer to memory location where dataOut data be stored
 *
 * @param reg_address                8-bit BMM150 register address
 *
 * @param n_bytes                    number of bytes to be written
 *
 * @returns status:
 * - 0 : OK;
 * - 1 : ERROR;
 *
 * @description  Function read a sequential data starting from the
 * targeted 8-bit register address of BMM150 sensor on 13DOF Click board.
 */
C13DOF_BMM150_RETVAL_T c13dof_bmm150_read_bytes ( c13dof_t *ctx, uint8_t *data_out, uint8_t reg_address, uint8_t n_bytes );

/**
 * @brief Check BMM150 data ready status function
 *
 *
 * @param ctx  Click object.
 *
 * @returns status:
 * - 0 : OK;
 * - 1 : ERROR;
 *
 * @description Function check data ready status by read from the
 * targeted 8-bit register address of BMM150 sensor on 13DOF Click board.
 */
C13DOF_BMM150_RETVAL_T c13dof_bmm150_check_ready ( c13dof_t *ctx );

/**
 * @brief Get BMM150 Geomagnetic sensors data function
 *
 *
 * @param ctx  Click object.
 *
 * @param mag_x               pointer to memory location where Mag X-axis data be stored
 *
 * @param mag_y               pointer to memory location where Mag Y-axis data be stored
 *
 * @param mag_z               pointer to memory location where Mag Z-axis data be stored
 *
 * @param res_hall            pointer to memory location where hall resistance data be stored
 *
 * @description Function reads 16-bit X-axis and Y-axis data, 15-bit Z-axis data and 14-bit hall resistance data from the
 * targeted 8-bit register address of BMM150 sensor on 13DOF Click board.
 */
void c13dof_bmm150_read_geo_mag_data ( c13dof_t *ctx, int16_t *mag_x, int16_t *mag_y, int16_t *mag_z, uint16_t *res_hall );

/**
 * @brief Software BMM150 reset function
 *
 *
 * @param ctx  Click object.
 *
 * @description Function performs a software reset and after that puts device to normal operation mode
 * of BMM150 sensor on 13DOF Click board.
 */
void c13dof_bmm150_soft_reset ( c13dof_t *ctx );

/**
 * @brief BMM150 power ON reset function
 *
 *
 * @param ctx  Click object.
 *
 * @description Function performs a reset by putting device first to suspend mode and after that to sleep mode.
 * When power on reset is performed, function puts device to normal operation mode
 * of BMM150 sensor on 13DOF Click board.
 */ 
void c13dof_bmm150_power_on_reset ( c13dof_t *ctx );

/**
 * @brief Generic BMI088 Gyro write data function
 *
 *
 * @param ctx  Click object.
 *
 * @param reg_address                8-bit BMI088 Gyro register address
 *
 * @param write_data                 Byte of data to write
 *
 * @description Function write the 8-bit of data to the
 * target 8-bit register address of BMI088 Gyro sensor on 13DOF Click board.
 */
void c13dof_bmi088_gyro_write_byte ( c13dof_t *ctx,  uint8_t reg_address, uint8_t write_data );

/**
 * @brief Generic sequential BMI088 Gyro write data function
 *
 *
 * @param ctx  Click object.
 *
 * @param reg_address                8-bit BMI088 Gyro register address
 *
 * @param write_data                 pointer to memory location where writeData data be stored
 *
 * @param n_bytes                    number of bytes to be written
 *
 * @description Function writes a sequential data starting from the
 * targeted 8-bit register address of BMI088 Gyro sensor on 13DOF Click board.
 */
void c13dof_bmi088_gyro_write_bytes ( c13dof_t *ctx, uint8_t reg_address, uint8_t *write_data, uint8_t n_bytes );

/**
 * @brief Generic BMI088 Gyro read data function
 *
 *
 * @param ctx  Click object.
 *
 * @param reg_address                8-bit BMI088 Gyro register address
 *
 * @returns
 * 8-bit read data
 *
 * @description Function read the 8-bit of data from the
 * target 8-bit register address of BMI088 Gyro sensor on 13DOF Click board.
 */
uint8_t c13dof_bmi088_gyro_read_byte ( c13dof_t *ctx, uint8_t reg_address );

/**
 * @brief Generic BMI088 Gyro sequential data read function
 *
 *
 * @param ctx  Click object.
 *
 * @param data_out                  pointer to memory location where dataOut data be stored
 *
 * @param reg_address                8-bit BMI088 Gyro register address
 *
 * @param n_bytes                    number of bytes to be written
 *
 * @returns status:
 * - 0 : OK;
 * - 1 : ERROR;
 *
 * @description Function read a sequential data starting from the
 * targeted 8-bit register address of BMI088 Gyro sensor on 13DOF Click board.
 */
C13DOF_BMI088_RETVAL_T c13dof_bmi088_gyro_read_bytes ( c13dof_t *ctx, uint8_t *data_out, uint8_t reg_address, uint8_t n_bytes );

/**
 * @brief Get BMI088 Gyro ID function
 *
 *
 * @param ctx  Click object.
 *
 * @returns
 * 8-bit read BMI088 Gyro ID data
 *
 * @description Function read the 8-bit of data from the
 * target _C13DOF_BMI088_GYRO_CHIP_ID_REG register address 
 * of BMI088 Gyro sensor on 13DOF Click board.
 */ 
uint8_t c13dof_bmi088_get_gyro_id ( c13dof_t *ctx );

/**
 * @brief Set BMI088 Gyro range function
 *
 *
 * @param ctx  Click object.
 *
 * @param 8-bit gyro_range value:
 *
 * @returns status:
 * - 0 : OK;
 * - 1 : ERROR;
 *
 * @description Function set BMI088 Gyro range by write gyroRange data to the
 * targeted _C13DOF_BMI088_GYRO_RANGE_REG register address 
 * of BMI088 Gyro sensor on 13DOF Click board.
 */
C13DOF_BMI088_RETVAL_T c13dof_bmi088_set_gyro_range ( c13dof_t *ctx, uint8_t gyro_range );

/**
 * @brief Set BMI088 Gyro bandwidth function
 *
 *
 * @param ctx  Click object.
 *
 * @param 8-bit gyro_bandwidth value:
 *
 *
 * @returns status:
 * - 0 : OK;
 * - 1 : ERROR;
 *
 * @description Function set BMI088 Gyro range by write gyroBandwidth data to the
 * targeted _C13DOF_BMI088_GYRO_BANDWIDTH_REG register address
 * of BMI088 Gyro sensor on 13DOF Click board.
 */
C13DOF_BMI088_RETVAL_T c13dof_bmi088_set_gyro_bandwidth ( c13dof_t *ctx, uint8_t gyro_bandwidth );

/**
 * @brief Software BMI088 Gyro reset function
 *
 *
 * @param ctx  Click object.
 *
 * @description Function performs a software reset and after that puts device to normal operation mode
 * of BMI088 Gyro sensor on 13DOF Click board.
 */
void c13dof_bmi088_soft_reset_giro ( c13dof_t *ctx );

/**
 * @brief Get BMI088 Gyro axis data function
 *
 *
 * @param ctx  Click object.
 *
 * @param adr_reg_LSB           least significant bit register address
 *
 * @param adr_reg_MSB           most significant bit register address
 *
 * @returns
 * 16-bit ( signed ) target axis value
 *
 * @description Function get axis data by read two target register address 
 * of BMI088 Gyro sensor on 13DOF Click board.
 */
int16_t c13dof_bmi088_get_gyro_axis ( c13dof_t *ctx, uint8_t adr_reg_LSB, uint8_t adr_reg_MSB );

/**
 * @brief Get BMI088 Gyro X-axis, Y-axis and Z-axis function
 *
 *
 * @param ctx  Click object.
 *
 * @param gyro_x              pointer to memory location where Mag X-axis data be stored
 *
 * @param gyro_y              pointer to memory location where Mag Y-axis data be stored
 *
 * @param gyro_z              pointer to memory location where Mag Z-axis data be stored
 *
 * @description Function reads 16-bit X-axis, Y-axis data and Z-axis data from the
 * targeted starts from _C13DOF_BMI088_GYRO_X_LSB_REG
 * to the _C13DOF_BMI088_GYRO_Z_MSB_REG register address of BMM150 sensor on 13DOF Click board.
 */
void c13dof_bmi088_read_gyro ( c13dof_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );

/**
 * @brief Generic BMI088 Accel write data function
 *
 *
 * @param ctx  Click object.
 *
 * @param reg_address                8-bit BMI088 Gyro register address
 *
 * @param write_data                 Byte of data to write
 *
 * @description Function write the 8-bit of data to the
 * target 8-bit register address of BMI088 Accel sensor on 13DOF Click board.
 */
void c13dof_bmi088_accel_write_byte ( c13dof_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Generic sequential BMI088 Accel write data function
 *
 *
 * @param ctx  Click object.
 *
 * @param reg_address                8-bit BMI088 Accel register address
 *
 * @param write_data                 pointer to memory location where writeData data be stored
 *
 * @param n_bytes                    number of bytes to be written
 *
 * @description Function writes a sequential data starting from the
 * targeted 8-bit register address of BMI088 Accel sensor on 13DOF Click board.
 */
void c13dof_bmi088_accel_write_bytes ( c13dof_t *ctx, uint8_t reg_address, uint8_t *write_data, uint8_t n_bytes );

/**
 * @brief Generic BMI088 Accel read data function
 *
 *
 * @param ctx  Click object.
 *
 * @param reg_address                8-bit BMI088 Accel register address
 *
 * @returns
 * 8-bit read data
 *
 * @description Function read the 8-bit of data from the
 * target 8-bit register address of BMI088 Accel sensor on 13DOF Click board.
 */
uint8_t c13dof_bmi088_accel_read_byte ( c13dof_t *ctx, uint8_t reg_address );

/**
 * @brief Generic BMI088 Accel sequential data read function
 *
 *
 * @param ctx  Click object.
 *
 * @param data_out                  pointer to memory location where dataOut data be stored
 *
 * @param reg_address                8-bit BMI088 Gyro register address
 *
 * @param n_bytes                    number of bytes to be written
 *
 * @returns status:
 * - 0 : OK;
 * - 1 : ERROR;
 *
 * Function read a sequential data starting from the
 * targeted 8-bit register address of BMI088 Accel sensor on 13DOF Click board.
 */
C13DOF_BMI088_RETVAL_T c13dof_bmi088_accel_read_bytes ( c13dof_t *ctx, uint8_t *data_out, uint8_t reg_address, uint8_t n_bytes );

/**
 * @brief Get BMI088 Accel ID function
 *
 *
 * @param ctx  Click object.
 *
 * @returns
 * 8-bit read BMI088 Accel ID data
 *
 * @description Function read the 8-bit of data from the
 * target _C13DOF_BMI088_ACCEL_CHIP_ID_REG register address
 * of BMI088 Accel sensor on 13DOF Click board.
 */
uint8_t c13dof_bmi088_get_accel_id ( c13dof_t *ctx );

/**
 * @brief Get BMI088 Accel error function
 *
 *
 * @param ctx  Click object.
 *
 * @returns BMI088 Accel error data:
 *
 * @description Function read the 8-bit of data from the
 * target _C13DOF_BMI088_ACCEL_ERR_REG register address
 * of BMI088 Accel sensor on 13DOF Click board.
 */
// uint8_t c13dof_bmi088_get_accel_error ( c13dof_t *ctx );

/**
 * @brief Get BMI088 check Accel data ready function
 *
 *
 * @param ctx  Click object.
 *
 * @returns status:
 * - 0 : data is not ready;
 * - 1 : data is ready;
 *
 * @description Function read the 8-bit of data from the
 * target _C13DOF_BMI088_ACCEL_STATUS_REG register address
 * of BMI088 Accel sensor on 13DOF Click board.
 */
uint8_t c13dof_bmi088_check_accel_data_ready ( c13dof_t *ctx );

/**
 * @brief Set BMI088 Accel configuration function
 *
 *
 * @param ctx  Click object.
 *
 * @returns BMI088 Accel configuration data:
 *
 * @description Function set BMI088 Accel configurationread by write accelConfig value to the 8-bit
 * of data from the _C13DOF_BMI088_ACCEL_CONF_REG register address
 * of BMI088 Accel sensor on 13DOF Click board.
 */
void c13dof_bmi088_set_accel_config ( c13dof_t *ctx, uint8_t accel_config );

/**
 * @brief Set BMI088 Accel range function
 *
 *
 * @param ctx  Click object.
 *
 * @returns BMI088 Accel Range setting:
 *
 * @description Function set BMI088 Accel range by write accelRange value to the 8-bit
 * of data from the _C13DOF_BMI088_ACCEL_RANGE_REG register address
 * of BMI088 Accel sensor on 13DOF Click board.
 */
C13DOF_BMI088_RETVAL_T c13dof_bmi088_set_accel_range ( c13dof_t *ctx, uint8_t accel_range );

/**
 * @brief Set BMI088 Accel soft reset function
 *
 *
 * @param ctx  Click object.
 *
 * @description Function performs a BMI088 Accel software reset 
 * and after that puts device to normal operation mode
 * of BMI088 Accel sensor on 13DOF Click board.
 *
 * @note
 * delay is 1 ms.
 */
void c13dof_bmi088_soft_reset_accel ( c13dof_t *ctx );

/**
 * @brief Set BMI088 Accel mode function
 *
 *
 * @param ctx  Click object.
 *
 * @param Filter setting:
 * - 0x00 : Suspend mode;
 * - 0x01 : Active mode;
 *
 *
 * @returns status:
 * - 0 : OK;
 * - 1 : ERROR;
 *
 * @description Function set BMI088 Accel mode by write activeMode data to the
 * targeted _C13DOF_BMI088_ACCEL_PWR_CONF_REG register address
 * of BMI088 Accel sensor on 13DOF Click board.
 *
 * @note
 * delay is 5 ms.
 */
void c13dof_bmi088_set_accel_mode ( c13dof_t *ctx, uint8_t active_mode );

/**
 * @brief Enable BMI088 Accel function
 *
 *
 * @param ctx  Click object.
 *
 * @returns status:
 * - 0 : OK;
 * - 1 : ERROR;
 *
 * @description Function enable BMI088 Accel by write 0x04 data to the
 * targeted _C13DOF_BMI088_ACCEL_PWR_CTRL_REG register address
 * of BMI088 Accel sensor on 13DOF Click board.
 *
 * @note
 * delay is 5 ms.
 */
C13DOF_BMI088_RETVAL_T c13dof_bmi088_enable_accel ( c13dof_t *ctx );

/**
 * @brief Disable BMI088 Accel function
 *
 *
 * @param ctx  Click object.
 *
 * @returns status:
 * - 0 : OK;
 * - 1 : ERROR;
 *
 * @description Function disable BMI088 Accel by write 0x00 data to the
 * targeted _C13DOF_BMI088_ACCEL_PWR_CTRL_REG register address
 * of BMI088 Accel sensor on 13DOF Click board.
 *
 * @note
 * delay is 5 ms.
 */
C13DOF_BMI088_RETVAL_T c13dof_bmi088_disable_accel ( c13dof_t *ctx );

/**
 * @brief Get BMI088 Accel axis data function
 *
 *
 * @param ctx  Click object.
 *
 * @param adr_reg_LSB           least significant bit register address
 *
 * @param adr_reg_MSB           most significant bit register address
 *
 * @returns 16-bit ( signed ) target axis value
 *
 * @description Function get axis data by read two target register address
 * of BMI088 Accel sensor on 13DOF Click board.
 */
int16_t c13dof_bmi088_get_accel_axis ( c13dof_t *ctx, uint8_t adr_reg_LSB, uint8_t adr_reg_MSB );

/**
 * @brief Get BMI088 Accel X-axis, Y-axis and Z-axis function
 *
 *
 * @param ctx  Click object.
 *
 * @param accel_x              pointer to memory location where Accel X-axis data be stored
 *
 * @param accel_y              pointer to memory location where Accel Y-axis data be stored
 *
 * @param accel_z              pointer to memory location where Accel Z-axis data be stored
 *
 * Function reads 16-bit X-axis, Y-axis data and Z-axis data from the
 * targeted starts from _C13DOF_BMI088_ACCEL_X_LSB_REG
 * to the _C13DOF_BMI088_ACCEL_Z_MSB_REG register address of BMM150 sensor on 13DOF Click board.
 */
void c13dof_bmi088_read_accel ( c13dof_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );

/**
 * @brief Set BMI088 Accel & Gyro default configuration fuction
 *
 *
 * @param ctx  Click object.
 *
 * @description Function Set BMI088 Accel & Gyro default configuration
 * of BMI088 Accel sensor on 13DOF Click board.
 */
void c13dof_bmi088_default_config( c13dof_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C13DOF_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
