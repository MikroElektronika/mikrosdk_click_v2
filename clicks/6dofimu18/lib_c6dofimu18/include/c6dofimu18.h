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
 * @file c6dofimu18.h
 * @brief This file contains API for 6DOF IMU 18 Click Driver.
 */

#ifndef C6DOFIMU18_H
#define C6DOFIMU18_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup c6dofimu18 6DOF IMU 18 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 18 Click driver.
 * @{
 */

/**
 * @defgroup c6dofimu18_reg 6DOF IMU 18 Registers List
 * @brief List of registers of 6DOF IMU 18 Click driver.
 */

/**
 * @addtogroup c6dofimu18_reg
 * @{
 */

/**
 * @brief 6DOF IMU 18 description register.
 * @details Specified register for description of 6DOF IMU 18 Click driver.
 */

/**
 * @brief 6DOF IMU 18 bank 0 registers.
 * @details Specified register from bank 0 of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_REG_DEVICE_CONFIG                0x11
#define C6DOFIMU18_REG_DRIVE_CONFIG                 0x13
#define C6DOFIMU18_REG_INT_CONFIG                   0x14
#define C6DOFIMU18_REG_FIFO_CONFIG                  0x16
#define C6DOFIMU18_REG_TEMP_DATA1                   0x1D
#define C6DOFIMU18_REG_TEMP_DATA0                   0x1E
#define C6DOFIMU18_REG_ACCEL_DATA_X1                0x1F
#define C6DOFIMU18_REG_ACCEL_DATA_X0                0x20
#define C6DOFIMU18_REG_ACCEL_DATA_Y1                0x21
#define C6DOFIMU18_REG_ACCEL_DATA_Y0                0x22
#define C6DOFIMU18_REG_ACCEL_DATA_Z1                0x23
#define C6DOFIMU18_REG_ACCEL_DATA_Z0                0x24
#define C6DOFIMU18_REG_GYRO_DATA_X1                 0x25
#define C6DOFIMU18_REG_GYRO_DATA_X0                 0x26
#define C6DOFIMU18_REG_GYRO_DATA_Y1                 0x27
#define C6DOFIMU18_REG_GYRO_DATA_Y0                 0x28
#define C6DOFIMU18_REG_GYRO_DATA_Z1                 0x29
#define C6DOFIMU18_REG_GYRO_DATA_Z0                 0x2A
#define C6DOFIMU18_REG_TMST_FSYNCH                  0x2B
#define C6DOFIMU18_REG_TMST_FSYNCL                  0x2C
#define C6DOFIMU18_REG_INT_STATUS                   0x2D
#define C6DOFIMU18_REG_FIFO_COUNTH                  0x2E
#define C6DOFIMU18_REG_FIFO_COUNTL                  0x2F
#define C6DOFIMU18_REG_FIFO_DATA                    0x30
#define C6DOFIMU18_REG_APEX_DATA0                   0x31
#define C6DOFIMU18_REG_APEX_DATA1                   0x32
#define C6DOFIMU18_REG_APEX_DATA2                   0x33
#define C6DOFIMU18_REG_APEX_DATA3                   0x34
#define C6DOFIMU18_REG_APEX_DATA4                   0x35
#define C6DOFIMU18_REG_APEX_DATA5                   0x36
#define C6DOFIMU18_REG_INT_STATUS2                  0x37
#define C6DOFIMU18_REG_INT_STATUS3                  0x38
#define C6DOFIMU18_REG_SIGNAL_PATH_RESET            0x4B
#define C6DOFIMU18_REG_INTF_CONFIG0                 0x4C
#define C6DOFIMU18_REG_INTF_CONFIG1                 0x4D
#define C6DOFIMU18_REG_PWR_MGMT0                    0x4E
#define C6DOFIMU18_REG_GYRO_CONFIG0                 0x4F
#define C6DOFIMU18_REG_ACCEL_CONFIG0                0x50
#define C6DOFIMU18_REG_GYRO_CONFIG1                 0x51
#define C6DOFIMU18_REG_GYRO_ACCEL_CONFIG0           0x52
#define C6DOFIMU18_REG_ACCEL_CONFIG1                0x53
#define C6DOFIMU18_REG_TMST_CONFIG                  0x54
#define C6DOFIMU18_REG_APEX_CONFIG0                 0x56
#define C6DOFIMU18_REG_SMD_CONFIG                   0x57
#define C6DOFIMU18_REG_FIFO_CONFIG1                 0x5F
#define C6DOFIMU18_REG_FIFO_CONFIG2                 0x60
#define C6DOFIMU18_REG_FIFO_CONFIG3                 0x61
#define C6DOFIMU18_REG_FSYNC_CONFIG                 0x62
#define C6DOFIMU18_REG_INT_CONFIG0                  0x63
#define C6DOFIMU18_REG_INT_CONFIG1                  0x64
#define C6DOFIMU18_REG_INT_SOURCE0                  0x65
#define C6DOFIMU18_REG_INT_SOURCE1                  0x66
#define C6DOFIMU18_REG_INT_SOURCE3                  0x68
#define C6DOFIMU18_REG_INT_SOURCE4                  0x69
#define C6DOFIMU18_REG_FIFO_LOST_PKT0               0x6C
#define C6DOFIMU18_REG_FIFO_LOST_PKT1               0x6D
#define C6DOFIMU18_REG_SELF_TEST_CONFIG             0x70
#define C6DOFIMU18_REG_WHO_AM_I                     0x75
#define C6DOFIMU18_REG_BANK_SEL                     0x76

/**
 * @brief 6DOF IMU 18 bank 1 registers.
 * @details Specified register from bank 1 of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_REG_SENSOR_CONFIG0               0x03
#define C6DOFIMU18_REG_GYRO_CONFIG_STATIC2          0x0B
#define C6DOFIMU18_REG_GYRO_CONFIG_STATIC3          0x0C
#define C6DOFIMU18_REG_GYRO_CONFIG_STATIC4          0x0D
#define C6DOFIMU18_REG_GYRO_CONFIG_STATIC5          0x0E
#define C6DOFIMU18_REG_GYRO_CONFIG_STATIC6          0x0F
#define C6DOFIMU18_REG_GYRO_CONFIG_STATIC7          0x10
#define C6DOFIMU18_REG_GYRO_CONFIG_STATIC8          0x11
#define C6DOFIMU18_REG_GYRO_CONFIG_STATIC9          0x12
#define C6DOFIMU18_REG_GYRO_CONFIG_STATIC10         0x13
#define C6DOFIMU18_REG_XG_ST_DATA                   0x5F
#define C6DOFIMU18_REG_YG_ST_DATA                   0x60
#define C6DOFIMU18_REG_ZG_ST_DATA                   0x61
#define C6DOFIMU18_REG_TMSTVAL0                     0x62
#define C6DOFIMU18_REG_TMSTVAL1                     0x63
#define C6DOFIMU18_REG_TMSTVAL2                     0x64
#define C6DOFIMU18_REG_INTF_CONFIG4                 0x7A
#define C6DOFIMU18_REG_INTF_CONFIG5                 0x7B
#define C6DOFIMU18_REG_INTF_CONFIG6                 0x7C

/**
 * @brief 6DOF IMU 18 bank 2 registers.
 * @details Specified register from bank 2 of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_REG_ACCEL_CONFIG_STATIC2         0x03
#define C6DOFIMU18_REG_ACCEL_CONFIG_STATIC3         0x04
#define C6DOFIMU18_REG_ACCEL_CONFIG_STATIC4         0x05
#define C6DOFIMU18_REG_XA_ST_DATA                   0x3B
#define C6DOFIMU18_REG_YA_ST_DATA                   0x3C
#define C6DOFIMU18_REG_ZA_ST_DATA                   0x3D

/**
 * @brief 6DOF IMU 18 bank 4 registers.
 * @details Specified register from bank 4 of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_REG_APEX_CONFIG1                 0x40
#define C6DOFIMU18_REG_APEX_CONFIG2                 0x41
#define C6DOFIMU18_REG_APEX_CONFIG3                 0x42
#define C6DOFIMU18_REG_APEX_CONFIG4                 0x43
#define C6DOFIMU18_REG_APEX_CONFIG5                 0x44
#define C6DOFIMU18_REG_APEX_CONFIG6                 0x45
#define C6DOFIMU18_REG_APEX_CONFIG7                 0x46
#define C6DOFIMU18_REG_APEX_CONFIG8                 0x47
#define C6DOFIMU18_REG_APEX_CONFIG9                 0x48
#define C6DOFIMU18_REG_ACCEL_WOM_X_THR              0x4A
#define C6DOFIMU18_REG_ACCEL_WOM_Y_THR              0x4B
#define C6DOFIMU18_REG_ACCEL_WOM_Z_THR              0x4C
#define C6DOFIMU18_REG_INT_SOURCE6                  0x4D
#define C6DOFIMU18_REG_INT_SOURCE7                  0x4E
#define C6DOFIMU18_REG_INT_SOURCE8                  0x4F
#define C6DOFIMU18_REG_INT_SOURCE9                  0x50
#define C6DOFIMU18_REG_INT_SOURCE10                 0x51
#define C6DOFIMU18_REG_OFFSET_USER0                 0x77
#define C6DOFIMU18_REG_OFFSET_USER1                 0x78
#define C6DOFIMU18_REG_OFFSET_USER2                 0x79
#define C6DOFIMU18_REG_OFFSET_USER3                 0x7A
#define C6DOFIMU18_REG_OFFSET_USER4                 0x7B
#define C6DOFIMU18_REG_OFFSET_USER5                 0x7C
#define C6DOFIMU18_REG_OFFSET_USER6                 0x7D
#define C6DOFIMU18_REG_OFFSET_USER7                 0x7E
#define C6DOFIMU18_REG_OFFSET_USER8                 0x7F

/*! @} */ // c6dofimu18_reg

/**
 * @defgroup c6dofimu18_set 6DOF IMU 18 Registers Settings
 * @brief Settings for registers of 6DOF IMU 18 Click driver.
 */

/**
 * @addtogroup c6dofimu18_set
 * @{
 */

/**
 * @brief 6DOF IMU 18 description setting.
 * @details Specified setting for description of 6DOF IMU 18 Click driver.
 */

#define C6DOFIMU18_BANK0_SEL                        0x00
#define C6DOFIMU18_BANK1_SEL                        0x01
#define C6DOFIMU18_BANK2_SEL                        0x02
#define C6DOFIMU18_BANK3_SEL                        0x03
#define C6DOFIMU18_BANK4_SEL                        0x04

/**
 * @brief 6DOF IMU 18 communication slew rate.
 * @details Specified setting for communication slew rate of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_SLEW_RATE_60nS                   0x00
#define C6DOFIMU18_SLEW_RATE_36nS                   0x01
#define C6DOFIMU18_SLEW_RATE_18nS                   0x02
#define C6DOFIMU18_SLEW_RATE_12nS                   0x03
#define C6DOFIMU18_SLEW_RATE_6nS                    0x04
#define C6DOFIMU18_SLEW_RATE_2nS                    0x05

/**
 * @brief 6DOF IMU 18 SPI mode.
 * @details Specified setting for SPI mode of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_SPI_MODE0_MODE3                  0x00
#define C6DOFIMU18_SPI_MODE1_MODE2                  0x01

#define C6DOFIMU18_ENABLE_SW_RESET                  0x01

/**
 * @brief 6DOF IMU 18 APEX DATA 3 register masks.
 * @details Specified setting for APEX DATA 3 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_DMP_IDEL_FLAG                    0x04
#define C6DOFIMU18_ACTIVITY_UNKNOWN                 0x00
#define C6DOFIMU18_ACTIVITY_WALK                    0x01
#define C6DOFIMU18_ACTIVITY_RUN                     0x02
#define C6DOFIMU18_ACTIVITY_MASK                    0x03

#define C6DOFIMU18_TAP_NUM_MASK                     0x18
#define C6DOFIMU18_TAP_SINGLE                       0x08
#define C6DOFIMU18_TAP_DOUBLE                       0x10
#define C6DOFIMU18_TAP_AXIS_MASK                    0x06
#define C6DOFIMU18_TAP_AXIS_X                       0x00
#define C6DOFIMU18_TAP_AXIS_Y                       0x02
#define C6DOFIMU18_TAP_AXIS_Z                       0x04
#define C6DOFIMU18_TAP_DIR_MASK                     0x01
#define C6DOFIMU18_TAP_DIR_POSITIVE                 0x00
#define C6DOFIMU18_TAP_DIR_NEGATIVE                 0x01

/**
 * @brief 6DOF IMU 18 INT CONFIG register masks.
 * @details Specified setting for INT CONFIG register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_INT_INT2_MODE_PULSED             0x00
#define C6DOFIMU18_INT_INT2_MODE_LATCHED            0x20
#define C6DOFIMU18_INT_INT2_OPEN_DRAIN              0x00
#define C6DOFIMU18_INT_INT2_PUSH_PULL               0x10
#define C6DOFIMU18_INT_INT2_ACTIVE_LOW              0x00
#define C6DOFIMU18_INT_INT2_ACTIVE_HIGH             0x08
#define C6DOFIMU18_INT_INT1_MODE_PULSED             0x00
#define C6DOFIMU18_INT_INT1_MODE_LATCHED            0x04
#define C6DOFIMU18_INT_INT1_OPEN_DRAIN              0x00
#define C6DOFIMU18_INT_INT1_PUSH_PULL               0x02
#define C6DOFIMU18_INT_INT1_ACTIVE_LOW              0x00
#define C6DOFIMU18_INT_INT1_ACTIVE_HIGH             0x01
#define C6DOFIMU18_INT_CONFIG_MASK                  0x3F

/**
 * @brief 6DOF IMU 18 INT CONFIG 0 register masks.
 * @details Specified setting for INT CONFIG 0 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_DRDY_INT_CLR_ON_STATUS_READ      0x00
#define C6DOFIMU18_DRDY_INT_CLR_FIFO_READ           0x20
#define C6DOFIMU18_DRDY_INT_CLR_STATUS_AND_REG      0x30
#define C6DOFIMU18_FIFO_INT_CLR_ON_STATUS_READ      0x00
#define C6DOFIMU18_FIFO_INT_CLR_FIFO_READ           0x80
#define C6DOFIMU18_FIFO_INT_CLR_STATUS_AND_REG      0xc0
#define C6DOFIMU18_FIFO_FULL_CLR_ON_STATUS_READ     0x00
#define C6DOFIMU18_FIFO_FULL_CLR_FIFO_READ          0x02
#define C6DOFIMU18_FIFO_FULL_CLR_STATUS_AND_REG     0x03

/**
 * @brief 6DOF IMU 18 INT CONFIG 1 register masks.
 * @details Specified setting for INT CONFIG 1 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_INT_TPULSE_100uS                 0x00
#define C6DOFIMU18_INT_TPULSE_8uS                   0x40
#define C6DOFIMU18_INT_TDEASSERT_DISABLE            0x20
#define C6DOFIMU18_INT_ASYNC_RESET_DISABLE          0x10
#define C6DOFIMU18_INT_ASYNC_RESET_ENABLE           0x00
#define C6DOFIMU18_INT_CONFIG1_MASK                 0x70

/**
 * @brief 6DOF IMU 18 INT SOURCE 0 register masks.
 * @details Specified setting for INT SOURCE 0 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_INT_UI_FSYNC_INT1_EN             0x40
#define C6DOFIMU18_INT_PLL_RDY_INT1_EN              0x20
#define C6DOFIMU18_INT_RESET_DONE_INT1_EN           0x10
#define C6DOFIMU18_INT_UI_DRDY_INT1_EN              0x08
#define C6DOFIMU18_INT_FIFO_THS_INT1_EN             0x04
#define C6DOFIMU18_INT_FIFO_FULL_INT1_EN            0x02
#define C6DOFIMU18_INT_UI_AGC_RDY_INT1_EN           0x01
#define C6DOFIMU18_INT_SOURCE0_MASK                 0x7F

/**
 * @brief 6DOF IMU 18 INT SOURCE 1 register masks.
 * @details Specified setting for INT SOURCE 1 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_SMD_INT1_EN                      0x08
#define C6DOFIMU18_WOM_Z_INT1_EN                    0x04
#define C6DOFIMU18_WOM_Y_INT1_EN                    0x02
#define C6DOFIMU18_WOM_X_INT1_EN                    0x01
#define C6DOFIMU18_INT_SOURCE1_MASK                 0x0F

/**
 * @brief 6DOF IMU 18 INT SOURCE 3 register masks.
 * @details Specified setting for INT SOURCE 3 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_INT_UI_FSYNC_INT2_EN             0x40
#define C6DOFIMU18_INT_PLL_RDY_INT2_EN              0x20
#define C6DOFIMU18_INT_RESET_DONE_INT2_EN           0x10
#define C6DOFIMU18_INT_UI_DRDY_INT2_EN              0x08
#define C6DOFIMU18_INT_FIFO_THS_INT2_EN             0x04
#define C6DOFIMU18_INT_FIFO_FULL_INT2_EN            0x02
#define C6DOFIMU18_INT_UI_AGC_RDY_INT2_EN           0x01
#define C6DOFIMU18_INT_SOURCE3_MASK                 0x7F

/**
 * @brief 6DOF IMU 18 INT SOURCE 4 register masks.
 * @details Specified setting for INT SOURCE 4 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_SMD_INT2_EN                      0x08
#define C6DOFIMU18_WOM_Z_INT2_EN                    0x04
#define C6DOFIMU18_WOM_Y_INT2_EN                    0x02
#define C6DOFIMU18_WOM_X_INT2_EN                    0x01
#define C6DOFIMU18_INT_SOURCE4_MASK                 0x0F

/**
 * @brief 6DOF IMU 18 INT SOURCE 6 register masks.
 * @details Specified setting for INT SOURCE 6 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_INT_SOURCE6_STEP_DET_INT1_EN     0x20
#define C6DOFIMU18_INT_SOURCE6_STEP_CNT_INT1_EN     0x10
#define C6DOFIMU18_INT_SOURCE6_TILT_DET_INT1_EN     0x08
#define C6DOFIMU18_INT_SOURCE6_TAP_DET_INT1_EN      0x01
#define C6DOFIMU18_INT_SOURCE6_MASK                 0x39

/**
 * @brief 6DOF IMU 18 INT SOURCE 7 register masks.
 * @details Specified setting for INT SOURCE 7 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_INT_SOURCE7_STEP_DET_INT2_EN     0x20
#define C6DOFIMU18_INT_SOURCE7_STEP_CNT_INT2_EN     0x10
#define C6DOFIMU18_INT_SOURCE7_TILT_DET_INT2_EN     0x08
#define C6DOFIMU18_INT_SOURCE7_TAP_DET_INT2_EN      0x01
#define C6DOFIMU18_INT_SOURCE7_MASK                 0x39

/**
 * @brief 6DOF IMU 18 INT STATUS register masks.
 * @details Specified setting for INT STATUS register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_UI_FSYNC_INT_FLAG                0x40
#define C6DOFIMU18_PLL_DONE_INT_FLAG                0x20
#define C6DOFIMU18_RESET_DONE_INT_FLAG              0x10
#define C6DOFIMU18_DATA_RDY_INT_FLAG                0x08
#define C6DOFIMU18_FIFO_THS_INT_FLAG                0x04
#define C6DOFIMU18_FIFO_FULL_INT_FLAG               0x02
#define C6DOFIMU18_AGC_RDY_INT_FLAG                 0x01

/**
 * @brief 6DOF IMU 18 INT STATUS 2 register masks.
 * @details Specified setting for INT STATUS 2 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_SMD_INT_FLAG                     0x08
#define C6DOFIMU18_WOM_Z_INT_FLAG                   0x04
#define C6DOFIMU18_WOM_Y_INT_FLAG                   0x02
#define C6DOFIMU18_WOM_X_INT_FLAG                   0x01

/**
 * @brief 6DOF IMU 18 INT STATUS 3 register masks.
 * @details Specified setting for INT STATUS 3 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_STEP_DET_INT_FLAG                0x10
#define C6DOFIMU18_STEP_CNT_OVF_INT_FLAG            0x08
#define C6DOFIMU18_TILT_DET_INT_FLAG                0x04
#define C6DOFIMU18_SLEEP_INT_FLAG                   0x02
#define C6DOFIMU18_TAP_DET_INT_FLAG                 0x01

/**
 * @brief 6DOF IMU 18 INTF CONFIG 0 register masks.
 * @details Specified setting for INTF CONFIG 0 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_FIFO_HLD_LAST_DATA_EN            0x80
#define C6DOFIMU18_FIFO_COUNT_REC                   0x40
#define C6DOFIMU18_FIFO_COUNT_ENDIAN                0x20
#define C6DOFIMU18_FIFO_DATA_ENDIAN                 0x10
#define C6DOFIMU18_UI_SIFS_CFG_DISABLE_I2C          0x03
#define C6DOFIMU18_UI_SIFS_CFG_DISABLE_SPI          0x02
#define C6DOFIMU18_INTF_CONFIG0_MASK                0xF3

/**
 * @brief 6DOF IMU 18 INTF CONFIG 1 register masks.
 * @details Specified setting for INTF CONFIG 1 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_ACCEL_LP_CLK_SEL_WAKE_UP_OSC     0x00
#define C6DOFIMU18_ACCEL_LP_CLK_SEL_RC_OSC          0x08
#define C6DOFIMU18_ACCEL_CLKSEL_RC                  0x00
#define C6DOFIMU18_ACCEL_CLKSEL_PLL_OR_RC           0x01
#define C6DOFIMU18_ACCEL_CLKSEL_DISABLE             0x03

/**
 * @brief 6DOF IMU 18 INTF CONFIG 4 register masks.
 * @details Specified setting for INTF CONFIG 4 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_SPI_3WIRE                        0x00
#define C6DOFIMU18_SPI_4WIRE                        0x02

/**
 * @brief 6DOF IMU 18 INTF CONFIG 5 register masks.
 * @details Specified setting for INTF CONFIG 5 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_PIN9_INT2                        0x00
#define C6DOFIMU18_PIN9_FSYNC                       0x01

/**
 * @brief 6DOF IMU 18 SIGNAL PATH RESET register masks.
 * @details Specified setting for SIGNAL PATH RESET register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_DMP_INIT_EN                      0x40
#define C6DOFIMU18_DMP_MEM_RESET_EN                 0x20
#define C6DOFIMU18_ABORT_AND_RESET                  0x08
#define C6DOFIMU18_TMST_STROBE                      0x04
#define C6DOFIMU18_FIFO_FLUSH                       0x02

/**
 * @brief 6DOF IMU 18 PWR MGMT0 register masks.
 * @details Specified setting for PWR MGMT0 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_PWR_TEMP_DIS                     0x20
#define C6DOFIMU18_PWR_IDLE_OFF                     0x10
#define C6DOFIMU18_PWR_GYRO_MODE_OFF                0x00
#define C6DOFIMU18_PWR_GYRO_STANDBY                 0x04
#define C6DOFIMU18_PWR_GYRO_LN_MODE                 0x0C
#define C6DOFIMU18_PWR_ACCEL_MODE_OFF               0x00
#define C6DOFIMU18_PWR_ACCEL_LP_MODE                0x02
#define C6DOFIMU18_PWR_ACCEL_LN_MODE                0x03

/**
 * @brief 6DOF IMU 18 GYRO CONFIG 0 register masks.
 * @details Specified setting for GYRO CONFIG 0 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_GYRO_FS_SEL_2000DPS              0x00
#define C6DOFIMU18_GYRO_FS_SEL_1000DPS              0x20
#define C6DOFIMU18_GYRO_FS_SEL_500DPS               0x40
#define C6DOFIMU18_GYRO_FS_SEL_250DPS               0x60
#define C6DOFIMU18_GYRO_FS_SEL_125DPS               0x80
#define C6DOFIMU18_GYRO_FS_SEL_62DPS                0xA0
#define C6DOFIMU18_GYRO_FS_SEL_32DPS                0xC0
#define C6DOFIMU18_GYRO_FS_SEL_15DPS                0xE0
#define C6DOFIMU18_GYRO_FS_SEL_MASK                 0xE0
#define C6DOFIMU18_GYRO_ODR_8kHz                    0x03
#define C6DOFIMU18_GYRO_ODR_4kHz                    0x04
#define C6DOFIMU18_GYRO_ODR_2kHz                    0x05
#define C6DOFIMU18_GYRO_ODR_1kHz                    0x06
#define C6DOFIMU18_GYRO_ODR_200Hz                   0x07
#define C6DOFIMU18_GYRO_ODR_100Hz                   0x08
#define C6DOFIMU18_GYRO_ODR_50Hz                    0x09
#define C6DOFIMU18_GYRO_ODR_25Hz                    0x0A
#define C6DOFIMU18_GYRO_ODR_12Hz                    0x0B
#define C6DOFIMU18_GYRO_ODR_500Hz                   0x0F
#define C6DOFIMU18_GYRO_ODR_MASK                    0x0F
#define C6DOFIMU18_GYRO_ODR_MASK                    0x0F

/**
 * @brief 6DOF IMU 18 GYRO CONFIG 1 register masks.
 * @details Specified setting for GYRO CONFIG 1 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_TEMP_FILT_BW_4kHz                0x00
#define C6DOFIMU18_TEMP_FILT_BW_170Hz               0x20
#define C6DOFIMU18_TEMP_FILT_BW_82Hz                0x40
#define C6DOFIMU18_TEMP_FILT_BW_40Hz                0x60
#define C6DOFIMU18_TEMP_FILT_BW_20Hz                0x80
#define C6DOFIMU18_TEMP_FILT_BW_10Hz                0xA0
#define C6DOFIMU18_TEMP_FILT_BW_5Hz_0               0xC0
#define C6DOFIMU18_TEMP_FILT_BW_5Hz_1               0xE0
#define C6DOFIMU18_GYRO_UI_FILT_ORD_1st             0x00
#define C6DOFIMU18_GYRO_UI_FILT_ORD_2nd             0x04
#define C6DOFIMU18_GYRO_UI_FILT_ORD_3rd             0x08
#define C6DOFIMU18_GYRO_UI_FILT_ORD_MASK            0x0C
#define C6DOFIMU18_GYRO_DEC2_M2_ORD_3rd             0x02
#define C6DOFIMU18_GYRO_CONFIG1_MASK                0xEF

/**
 * @brief 6DOF IMU 18 ACCEL CONFIG 0 register masks.
 * @details Specified setting for ACCEL CONFIG 0 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_ACCEL_FS_SEL_16G                 0x00
#define C6DOFIMU18_ACCEL_FS_SEL_8G                  0x20
#define C6DOFIMU18_ACCEL_FS_SEL_4G                  0x40
#define C6DOFIMU18_ACCEL_FS_SEL_2G                  0x60
#define C6DOFIMU18_ACCEL_FS_SEL_MASK                0x60
#define C6DOFIMU18_ACCEL_ODR_8kHz_LN                0x03
#define C6DOFIMU18_ACCEL_ODR_4kHz_LN                0x04
#define C6DOFIMU18_ACCEL_ODR_2kHz_LN                0x05
#define C6DOFIMU18_ACCEL_ODR_1kHz_LN                0x06
#define C6DOFIMU18_ACCEL_ODR_200Hz_LP_LN            0x07
#define C6DOFIMU18_ACCEL_ODR_100Hz_LP_LN            0x08
#define C6DOFIMU18_ACCEL_ODR_50Hz_LP_LN             0x09
#define C6DOFIMU18_ACCEL_ODR_25Hz_LP_LN             0x0A
#define C6DOFIMU18_ACCEL_ODR_12Hz_LP_LN             0x0B
#define C6DOFIMU18_ACCEL_ODR_6Hz_LP                 0x0C
#define C6DOFIMU18_ACCEL_ODR_3Hz_LP                 0x0D
#define C6DOFIMU18_ACCEL_ODR_1Hz_LP                 0x0E
#define C6DOFIMU18_ACCEL_ODR_500Hz_LP_LN            0x0F
#define C6DOFIMU18_ACCEL_ODR_MASK                   0x0F

/**
 * @brief 6DOF IMU 18 ACCEL CONFIG 1 register masks.
 * @details Specified setting for ACCEL CONFIG 1 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_ACCEL_UI_FILT_ORD_1st            0x00
#define C6DOFIMU18_ACCEL_UI_FILT_ORD_2nd            0x08
#define C6DOFIMU18_ACCEL_UI_FILT_ORD_3rd            0x10
#define C6DOFIMU18_ACCEL_UI_FILT_ORD_MASK           0x18
#define C6DOFIMU18_ACCEL_DEC2_M2_ORD_3rd            0x04

/**
 * @brief 6DOF IMU 18 TMST CONFIG register masks.
 * @details Specified setting for TMST CONFIG register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_TMST_TO_REGS_EN                  0x10
#define C6DOFIMU18_TMST_RES                         0x08
#define C6DOFIMU18_TMST_DELTA_EN                    0x04
#define C6DOFIMU18_TMST_FSYNC_EN                    0x02
#define C6DOFIMU18_TMST_EN                          0x01
#define C6DOFIMU18_TMST_MASK                        0x1F

/**
 * @brief 6DOF IMU 18 FIFO CONFIG register masks.
 * @details Specified setting for FIFO CONFIG register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_FIFO_BYPASS                      0x00
#define C6DOFIMU18_FIFO_STREAM_TO_FIFO              0x40
#define C6DOFIMU18_FIFO_STOP_ON_FULL                0x80
#define C6DOFIMU18_FIFO_CONFIG_MASK                 0xC0

/**
 * @brief 6DOF IMU 18 FIFO CONFIG 1 register masks.
 * @details Specified setting for FIFO CONFIG 1 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_FIFO_RESUME_PARTIAL_RD           0x40
#define C6DOFIMU18_FIFO_WM_GT_TH                    0x20
#define C6DOFIMU18_FIFO_TMST_FSYNC_EN               0x08
#define C6DOFIMU18_FIFO_TEMP_EN                     0x04
#define C6DOFIMU18_FIFO_GYRO_EN                     0x02
#define C6DOFIMU18_FIFO_ACCEL_EN                    0x01

/**
 * @brief 6DOF IMU 18 FSYNC CONFIG register masks.
 * @details Specified setting for FSYNC CONFIG register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_DO_NOT_TAG_FSYNC                 0x00
#define C6DOFIMU18_FSYNC_TAG_TEMP_OUT_LSB           0x10
#define C6DOFIMU18_FSYNC_GYRO_XOUT_LSB              0x20
#define C6DOFIMU18_FSYNC_GYRO_YOUT_LSB              0x30
#define C6DOFIMU18_FSYNC_GYRO_ZOUT_LSB              0x40
#define C6DOFIMU18_FSYNC_ACCEL_XOUT_LSB             0x50
#define C6DOFIMU18_FSYNC_ACCEL_YOUT_LSB             0x60
#define C6DOFIMU18_FSYNC_ACCEL_ZOUT_LSB             0x70
#define C6DOFIMU18_FSYNC_UI_SEL_MASK                0x70
#define C6DOFIMU18_FSYNC_UI_FLAG_CLEAR_SEL          0x02
#define C6DOFIMU18_FSYNC_POLARITY_RISING_EGDE       0x01
#define C6DOFIMU18_FSYNC_POLARITY_FALLING_EGDE      0x01

/**
 * @brief 6DOF IMU 18 APEX CONFIG 0 register masks.
 * @details Specified setting for APEX CONFIG 0 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_DMP_POVER_SAVE_EN                0x80
#define C6DOFIMU18_TAP_ENABLE                       0x40
#define C6DOFIMU18_PED_ENABLE                       0x20
#define C6DOFIMU18_TILT_ENABLE                      0x10
#define C6DOFIMU18_R2W_ENABLE                       0x08
#define C6DOFIMU18_DMP_ODR_25Hz                     0x00
#define C6DOFIMU18_DMP_ODR_50Hz                     0x02

/**
 * @brief 6DOF IMU 18 APEX CONFIG 1 register masks.
 * @details Specified setting for APEX CONFIG 1 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_LOW_ENERGY_AMP_TH_SEL            0xA0
#define C6DOFIMU18_DMP_POVER_SAVE_TIME_0S           0x00
#define C6DOFIMU18_DMP_POVER_SAVE_TIME_4S           0x01
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_8S           0x02
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_12S          0x03
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_16S          0x04
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_20S          0x05
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_24S          0x06
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_28S          0x07
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_32S          0x08
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_36S          0x09
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_40S          0x0A
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_44S          0x0B
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_48S          0x0C
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_52S          0x0D
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_56S          0x0E
#define C6DOFIMU18_DMP_POWER_SAVE_TIME_60S          0x0F

/**
 * @brief 6DOF IMU 18 APEX CONFIG 2 register masks.
 * @details Specified setting for APEX CONFIG 2 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_PED_AMP_TH_SEL                   0x80
#define C6DOFIMU18_PED_STEP_CNT_TH_0_STEPS          0x00
#define C6DOFIMU18_PED_STEP_CNT_TH_1_STEPS          0x01
#define C6DOFIMU18_PED_STEP_CNT_TH_2_STEPS          0x02
#define C6DOFIMU18_PED_STEP_CNT_TH_3_STEPS          0x03
#define C6DOFIMU18_PED_STEP_CNT_TH_4_STEPS          0x04
#define C6DOFIMU18_PED_STEP_CNT_TH_5_STEPS          0x05
#define C6DOFIMU18_PED_STEP_CNT_TH_6_STEPS          0x06
#define C6DOFIMU18_PED_STEP_CNT_TH_7_STEPS          0x07
#define C6DOFIMU18_PED_STEP_CNT_TH_8_STEPS          0x08
#define C6DOFIMU18_PED_STEP_CNT_TH_9_STEPS          0x09
#define C6DOFIMU18_PED_STEP_CNT_TH_10_STEPS         0x0A
#define C6DOFIMU18_PED_STEP_CNT_TH_11_STEPS         0x0B
#define C6DOFIMU18_PED_STEP_CNT_TH_12_STEPS         0x0C
#define C6DOFIMU18_PED_STEP_CNT_TH_13_STEPS         0x0D
#define C6DOFIMU18_PED_STEP_CNT_TH_14_STEPS         0x0E
#define C6DOFIMU18_PED_STEP_CNT_TH_15_STEPS         0x0F
#define C6DOFIMU18_PED_STEP_CNT_TH_MASK             0x0F

/**
 * @brief 6DOF IMU 18 APEX CONFIG 3 register masks.
 * @details Specified setting for APEX CONFIG 3 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_PED_STEP_DET_TH_0_STEPS          0x00
#define C6DOFIMU18_PED_STEP_DET_TH_1_STEPS          0x20
#define C6DOFIMU18_PED_STEP_DET_TH_2_STEPS          0x40
#define C6DOFIMU18_PED_STEP_DET_TH_3_STEPS          0x60
#define C6DOFIMU18_PED_STEP_DET_TH_4_STEPS          0x80
#define C6DOFIMU18_PED_STEP_DET_TH_5_STEPS          0xA0
#define C6DOFIMU18_PED_STEP_DET_TH_6_STEPS          0xC0
#define C6DOFIMU18_PED_STEP_DET_TH_7_STEPS          0xE0
#define C6DOFIMU18_PED_SB_TIMER_TH_0_SAMPLES        0x00
#define C6DOFIMU18_PED_SB_TIMER_TH_1_SAMPLES        0x04
#define C6DOFIMU18_PED_SB_TIMER_TH_2_SAMPLES        0x08
#define C6DOFIMU18_PED_SB_TIMER_TH_3_SAMPLES        0x0C
#define C6DOFIMU18_PED_SB_TIMER_TH_4_SAMPLES        0x10
#define C6DOFIMU18_PED_SB_TIMER_TH_5_SAMPLES        0x14
#define C6DOFIMU18_PED_SB_TIMER_TH_6_SAMPLES        0x18
#define C6DOFIMU18_PED_SB_TIMER_TH_7_SAMPLES        0x1C
#define C6DOFIMU18_PED_HI_EN_TH_SEL                 0x01

/**
 * @brief 6DOF IMU 18 APEX CONFIG 4 register masks.
 * @details Specified setting for APEX CONFIG 4 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_TILT_WAIT_TIME_0S                0x00
#define C6DOFIMU18_TILT_WAIT_TIME_2S                0x40
#define C6DOFIMU18_TILT_WAIT_TIME_4S                0x80
#define C6DOFIMU18_TILT_WAIT_TIME_6S                0xC0
#define C6DOFIMU18_TILT_WAIT_TIME_MASK              0xC0
#define C6DOFIMU18_SLEEP_TIME_OUT_1s28              0x00
#define C6DOFIMU18_SLEEP_TIME_OUT_2s56              0x08
#define C6DOFIMU18_SLEEP_TIME_OUT_3s84              0x10
#define C6DOFIMU18_SLEEP_TIME_OUT_5s12              0x18
#define C6DOFIMU18_SLEEP_TIME_OUT_6s4               0x20
#define C6DOFIMU18_SLEEP_TIME_OUT_7s68              0x28
#define C6DOFIMU18_SLEEP_TIME_OUT_8s96              0x30
#define C6DOFIMU18_SLEEP_TIME_OUT_10s24             0x38
#define C6DOFIMU18_SLEEP_TIME_OUT_MASK              0x38

/**
 * @brief 6DOF IMU 18 APEX CONFIG 7 register masks.
 * @details Specified setting for APEX CONFIG 7 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_TAP_MIN_JERK_THR                 0x44
#define C6DOFIMU18_TAP_MAX_OEAK_TOL                 0x01

/**
 * @brief 6DOF IMU 18 APEX CONFIG 8 register masks.
 * @details Specified setting for APEX CONFIG 8 register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_TAP_TMAX                         0x20
#define C6DOFIMU18_TAP_TAVG                         0x08
#define C6DOFIMU18_TAP_TMIN                         0x03

/**
 * @brief 6DOF IMU 18 APEX CONFIG 9 register masks.
 * @details Specified setting for APEX CONFIG 9 register of 6DOF IMU 18 Click driver.
 */ 
#define C6DOFIMU18_SENSITIVITY_MODE_HIGH_PERF       0x00
#define C6DOFIMU18_SENSITIVITY_MODE_SLOW_WALK       0x01

/**
 * @brief 6DOF IMU 18 Temperature calculation values.
 * @details Specified setting for temperature calculation of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_TEMPERATURE_DIV                  132.48
#define C6DOFIMU18_TEMPERATURE_ADD                  25

/**
 * @brief 6DOF IMU 18 who am i register values.
 * @details Specified value for who am i register of 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_WHO_AM_I_VALUE                   0x42

/**
 * @brief 6DOF IMU 18 device address setting.
 * @details Specified setting for device slave address selection of
 * 6DOF IMU 18 Click driver.
 */
#define C6DOFIMU18_DEVICE_ADDRESS_GND               0x68
#define C6DOFIMU18_DEVICE_ADDRESS_VCC               0x69

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c6dofimu18_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C6DOFIMU18_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define C6DOFIMU18_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c6dofimu18_set

/**
 * @defgroup c6dofimu18_map 6DOF IMU 18 MikroBUS Map
 * @brief MikroBUS pin mapping of 6DOF IMU 18 Click driver.
 */

/**
 * @addtogroup c6dofimu18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6DOF IMU 18 Click to the selected MikroBUS.
 */
#define C6DOFIMU18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ryc = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6dofimu18_map
/*! @} */ // c6dofimu18

/**
 * @brief 6DOF IMU 18 Click driver selector.
 * @details Selects target driver interface of 6DOF IMU 18 Click driver.
 */
typedef enum
{
    C6DOFIMU18_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    C6DOFIMU18_DRV_SEL_I2C       /**< I2C driver descriptor. */

} c6dofimu18_drv_t;

/**
 * @brief 6DOF IMU 18 Click driver interface.
 * @details Definition of driver interface of 6DOF IMU 18 Click driver.
 */
typedef err_t ( *c6dofimu18_master_io_t )( struct c6dofimu18_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief 6DOF IMU 18 Click context object.
 * @details Context object definition of 6DOF IMU 18 Click driver.
 */
typedef struct c6dofimu18_s
{
    digital_in_t ryc;                       /**< Interrupt 2. */
    digital_in_t int_pin;                   /**< Interrupt. */

    i2c_master_t i2c;                       /**< I2C driver object. */
    spi_master_t spi;                       /**< SPI driver object. */

    uint8_t      slave_address;             /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;               /**< Chip select pin descriptor (used for SPI driver). */
    spi_master_mode_t spi_mode;
    uint8_t     slew_rate;
    c6dofimu18_drv_t drv_sel;               /**< Master driver interface selector. */

    c6dofimu18_master_io_t write_f;         /**< Master write function. */
    c6dofimu18_master_io_t read_f;          /**< Master read function. */

} c6dofimu18_t;

/**
 * @brief 6DOF IMU 18 Click configuration object.
 * @details Configuration object definition of 6DOF IMU 18 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */
    pin_name_t ryc;             /**< Interrupt 2. */
    pin_name_t int_pin;         /**< Interrupt. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    c6dofimu18_drv_t drv_sel;                /**< Master driver interface selector. */

} c6dofimu18_cfg_t;

/**
 * @brief 6DOF IMU 18 data object.
 * @details Data object definition of 6DOF IMU 18 Click driver.
 */
typedef struct
{
    int16_t data_x;
    int16_t data_y;
    int16_t data_z;
    
} c6dofimu18_data_t;

/**
 * @brief 6DOF IMU 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C6DOFIMU18_OK = 0,
    C6DOFIMU18_ERROR = -1,
    C6DOFIMU18_RESET_ERROR = -2

} c6dofimu18_return_value_t;

/*!
 * @addtogroup c6dofimu18 6DOF IMU 18 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 18 Click driver.
 * @{
 */

/**
 * @brief 6DOF IMU 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c6dofimu18_cfg_setup ( c6dofimu18_cfg_t *cfg );

/**
 * @brief 6DOF IMU 18 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu18_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #c6dofimu18_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void c6dofimu18_drv_interface_selection ( c6dofimu18_cfg_t *cfg, c6dofimu18_drv_t drv_sel );

/**
 * @brief 6DOF IMU 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6dofimu18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_init ( c6dofimu18_t *ctx, c6dofimu18_cfg_t *cfg );

/**
 * @brief 6DOF IMU 18 default configuration function.
 * @details This function executes a default configuration of 6DOF IMU 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c6dofimu18_default_cfg ( c6dofimu18_t *ctx );

/**
 * @brief 6DOF IMU 18 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_generic_write ( c6dofimu18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 18 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_generic_read ( c6dofimu18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 18 set register bank function.
 * @details This function switches to the desired register bank in order to 
 * access specific registers on that bank.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @param[in] bank : Specific register bank.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_set_reg_bank( c6dofimu18_t *ctx, uint8_t bank );

/**
 * @brief 6DOF IMU 18 register data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register. Register addresses are self increasing according to the 
 * number of bytes of input data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @param[in] bank : Specific register bank.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_reg_write ( c6dofimu18_t *ctx, uint8_t reg_bank, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 18 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_reg_read ( c6dofimu18_t *ctx, uint8_t reg_bank, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 18 configure digital interface function.
 * @details This function sets a digital communication interface based on selected communication.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @param[in] slew_rate : Slew rate of selected interface.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_configure_digital_interface ( c6dofimu18_t *ctx, uint8_t slew_rate );

/**
 * @brief 6DOF IMU 18 read INT1 pin state function.
 * @details This function is used to get state of the INT1 (int_pin).
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @return State of INT1 pin.
 * @note None.
 */
uint8_t c6dofimu18_get_int1_state ( c6dofimu18_t *ctx );

/**
 * @brief 6DOF IMU 18 read INT2 pin state function.
 * @details This function is used to get state of the INT2 (int_pin).
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @return State of INT2 pin.
 * @note None.
 */
uint8_t c6dofimu18_get_int1_state ( c6dofimu18_t *ctx );

/**
 * @brief 6DOF IMU 18 software reset function.
 * @details This function is used to perform a software reset of the 6DOF IMU 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note All registers will be set at their default value.
 */
err_t c6dofimu18_sw_reset( c6dofimu18_t *ctx );

/**
 * @brief 6DOF IMU 18 read temperature function.
 * @details This function is used to read temperature from the 6DOF IMU 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @param[out] temperature_data : Temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_read_temperature ( c6dofimu18_t *ctx, float *temperature_data );

/**
 * @brief 6DOF IMU 18 read timestamp function.
 * @details This function is used to read data timestamp from the 6DOF IMU 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @param[out] tmst_data : Timestamp value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_read_timestamp ( c6dofimu18_t *ctx, uint32_t *tmst_data );

/**
 * @brief 6DOF IMU 18 read data function.
 * @details This function is used to read accel, gyro, temperature, and timestamp data from the 
 * 6DOF IMU 18 click board. This data can be then processed and used in a specific way.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @param[out] temperature_data : Temperature data value.
 * @param[out] accel_data : Accel data value.
 * @param[out] gyro_data : Gyro data value.
 * @param[out] tmst_data : Timestamp value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_get_data_from_register ( c6dofimu18_t *ctx, float *temperature_data, 
                                          c6dofimu18_data_t *accel_data, c6dofimu18_data_t *gyro_data, 
                                          uint32_t *tmst_data );

/**
 * @brief 6DOF IMU 18 basic tap detection configuration function.
 * @details This function is used to configure the 6DOF IMU 18 click board into tap detection configuration. 
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_set_basic_tap_detection ( c6dofimu18_t *ctx );

/**
 * @brief 6DOF IMU 18 get tap detection data function.
 * @details This function is used to read tap detection data from the 6DOF IMU 18 click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu18_t object definition for detailed explanation.
 * @param[out] tap_num : Numbers of taps.
 * @param[out] tap_axis : Axis of the tap direction.
 * @param[out] tap_dir : Direction of the tap in correspondence to the starting point.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu18_get_tap_detection ( c6dofimu18_t *ctx, uint8_t *tap_num, uint8_t *tap_axis, uint8_t *tap_dir );

#ifdef __cplusplus
}
#endif
#endif // C6DOFIMU18_H

/*! @} */ // c6dofimu18

// ------------------------------------------------------------------------ END
