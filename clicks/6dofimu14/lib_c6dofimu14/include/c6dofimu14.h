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
 * @file c6dofimu14.h
 * @brief This file contains API for 6DOF IMU 14 Click Driver.
 */

#ifndef C6DOFIMU14_H
#define C6DOFIMU14_H

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
#include "drv_spi_master.h"

/*!
 * @addtogroup c6dofimu14 6DOF IMU 14 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 14 Click driver.
 * @{
 */

/**
 * @defgroup c6dofimu14_reg 6DOF IMU 14 Registers List
 * @brief List of registers of 6DOF IMU 14 Click driver.
 */

/**
 * @addtogroup c6dofimu14_reg
 * @{
 */

/**
 * @brief 6DOF IMU 14 USER BANK 0 register map summary.
 * @details The list of USER BANK 0 registers.
 */
#define C6DOFIMU14_REG0_DEVICE_CONFIG           0x11
#define C6DOFIMU14_REG0_DRIVE_CONFIG            0x13
#define C6DOFIMU14_REG0_INT_CONFIG              0x14
#define C6DOFIMU14_REG0_FIFO_CONFIG             0x16
#define C6DOFIMU14_REG0_TEMP_DATA_MSB           0x1D
#define C6DOFIMU14_REG0_TEMP_DATA_LSB           0x1E
#define C6DOFIMU14_REG0_ACCEL_X_MSB             0x1F
#define C6DOFIMU14_REG0_ACCEL_X_LSB             0x20
#define C6DOFIMU14_REG0_ACCEL_Y_MSB             0x21
#define C6DOFIMU14_REG0_ACCEL_Y_LSB             0x22
#define C6DOFIMU14_REG0_ACCEL_Z_MSB             0x23
#define C6DOFIMU14_REG0_ACCEL_Z_LSB             0x24
#define C6DOFIMU14_REG0_GYRO_X_MSB              0x25
#define C6DOFIMU14_REG0_GYRO_X_LSB              0x26
#define C6DOFIMU14_REG0_GYRO_Y_MSB              0x27
#define C6DOFIMU14_REG0_GYRO_Y_LSB              0x28
#define C6DOFIMU14_REG0_GYRO_Z_MSB              0x29
#define C6DOFIMU14_REG0_GYRO_Z_LSB              0x2A
#define C6DOFIMU14_REG0_TMST_FSYNC_MSB          0x2B
#define C6DOFIMU14_REG0_TMST_FSYNC_LSB          0x2C
#define C6DOFIMU14_REG0_INT_STATUS_1            0x2D
#define C6DOFIMU14_REG0_FIFO_COUNT_MSB          0x2E
#define C6DOFIMU14_REG0_FIFO_COUNT_LSB          0x2F
#define C6DOFIMU14_REG0_FIFO_DATA               0x30
#define C6DOFIMU14_REG0_APEX_DATA_LSB           0x31
#define C6DOFIMU14_REG0_APEX_DATA_MSB           0x32
#define C6DOFIMU14_REG0_APEX_STEP_CADENCE       0x33
#define C6DOFIMU14_REG0_APEX_DATA_3             0x34
#define C6DOFIMU14_REG0_APEX_DATA_4             0x35
#define C6DOFIMU14_REG0_APEX_DATA_5             0x36
#define C6DOFIMU14_REG0_INT_STATUS_2            0x37
#define C6DOFIMU14_REG0_INT_STATUS_3            0x38
#define C6DOFIMU14_REG0_SIGNAL_PATH_RESET       0x4B
#define C6DOFIMU14_REG0_INTF_CONFIG_0           0x4C
#define C6DOFIMU14_REG0_INTF_CONFIG_1           0x4D
#define C6DOFIMU14_REG0_PWR_MGMT_0              0x4E
#define C6DOFIMU14_REG0_GYRO_CONFIG_0           0x4F
#define C6DOFIMU14_REG0_ACCEL_CONFIG_0          0x50
#define C6DOFIMU14_REG0_GYRO_CONFIG_1           0x51
#define C6DOFIMU14_REG0_GYRO_ACCEL_CFG_0        0x52
#define C6DOFIMU14_REG0_ACCEL_CONFIG_1          0x53
#define C6DOFIMU14_REG0_TMST_CONFIG             0x54
#define C6DOFIMU14_REG0_APRX_CONFIG_0           0x56
#define C6DOFIMU14_REG0_SMD_CONFIG              0x57
#define C6DOFIMU14_REG0_FIFO_CONFIG_1           0x5F
#define C6DOFIMU14_REG0_FIFO_CONFIG_2           0x60
#define C6DOFIMU14_REG0_FIFO_CONFIG_3           0x61
#define C6DOFIMU14_REG0_FSYNC_CONFIG            0x62
#define C6DOFIMU14_REG0_INT_CONFIG_0            0x63
#define C6DOFIMU14_REG0_INT_CONFIG_1            0x64
#define C6DOFIMU14_REG0_INT_SOURCE_0            0x65
#define C6DOFIMU14_REG0_INT_SOURCE_1            0x66
#define C6DOFIMU14_REG0_INT_SOURCE_3            0x68
#define C6DOFIMU14_REG0_INT_SOURCE_4            0x69
#define C6DOFIMU14_REG0_FIFO_LOST_PKT_0         0x6C
#define C6DOFIMU14_REG0_FIFO_LOST_PKT_1         0x6D
#define C6DOFIMU14_REG0_SELF_TEST_CONFIG        0x70
#define C6DOFIMU14_REG0_WHO_AM_I                0x75
#define C6DOFIMU14_REG0_BANK_SEL                0x76

/**
 * @brief 6DOF IMU 14 USER BANK 1 register map summary.
 * @details The list of USER BANK 1 registers.
 */
#define C6DOFIMU14_REG1_SENSOR_CONFIG_0         0x03
#define C6DOFIMU14_REG1_GYRO_CONFIG_2           0x0B
#define C6DOFIMU14_REG1_GYRO_CONFIG_3           0x0C
#define C6DOFIMU14_REG1_GYRO_CONFIG_4           0x0D
#define C6DOFIMU14_REG1_GYRO_CONFIG_5           0x0E
#define C6DOFIMU14_REG1_GYRO_CONFIG_6           0x0F
#define C6DOFIMU14_REG1_GYRO_CONFIG_7           0x10
#define C6DOFIMU14_REG1_GYRO_CONFIG_8           0x11
#define C6DOFIMU14_REG1_GYRO_CONFIG_9           0x12
#define C6DOFIMU14_REG1_GYRO_CONFIG_10          0x13
#define C6DOFIMU14_REG1_XG_ST_DATA              0x5F
#define C6DOFIMU14_REG1_YG_ST_DATA              0x60
#define C6DOFIMU14_REG1_ZG_ST_DATA              0x61
#define C6DOFIMU14_REG1_TMST_VALUE_LSB          0x62
#define C6DOFIMU14_REG1_TMST_VALUE_MID          0x63
#define C6DOFIMU14_REG1_TMST_VALUE_MSB          0x64
#define C6DOFIMU14_REG1_INTF_CONFIG_4           0x7A
#define C6DOFIMU14_REG1_INTF_CONFIG_5           0x7B
#define C6DOFIMU14_REG1_INTF_CONFIG_6           0x7C

/**
 * @brief 6DOF IMU 14 USER BANK 2 register map summary.
 * @details The list of USER BANK 2 registers.
 */
#define C6DOFIMU14_REG2_ACCEL_CONFIG_2          0x03
#define C6DOFIMU14_REG2_ACCEL_CONFIG_3          0x04
#define C6DOFIMU14_REG2_ACCEL_CONFIG_4          0x05
#define C6DOFIMU14_REG2_XA_ST_DATA              0x3B
#define C6DOFIMU14_REG2_YA_ST_DATA              0x3C
#define C6DOFIMU14_REG2_ZA_ST_DATA              0x3D

/**
 * @brief 6DOF IMU 14 USER BANK 4 register map summary.
 * @details The list of USER BANK 4 registers.
 */
#define C6DOFIMU14_REG4_APEX_CONFIG_1           0x40
#define C6DOFIMU14_REG4_APEX_CONFIG_2           0x41
#define C6DOFIMU14_REG4_APEX_CONFIG_3           0x42
#define C6DOFIMU14_REG4_APEX_CONFIG_4           0x43
#define C6DOFIMU14_REG4_APEX_CONFIG_5           0x44
#define C6DOFIMU14_REG4_APEX_CONFIG_6           0x45
#define C6DOFIMU14_REG4_APEX_CONFIG_7           0x46
#define C6DOFIMU14_REG4_APEX_CONFIG_8           0x47
#define C6DOFIMU14_REG4_APEX_CONFIG_9           0x48
#define C6DOFIMU14_REG4_ACCEL_WOM_X_THR         0x4A
#define C6DOFIMU14_REG4_ACCEL_WOM_Y_THR         0x4B
#define C6DOFIMU14_REG4_ACCEL_WOM_Z_THR         0x4C
#define C6DOFIMU14_REG4_INT_SOURCE_6            0x4D
#define C6DOFIMU14_REG4_INT_SOURCE_7            0x4E
#define C6DOFIMU14_REG4_INT_SOURCE_8            0x4F
#define C6DOFIMU14_REG4_INT_SOURCE_9            0x50
#define C6DOFIMU14_REG4_INT_SOURCE_10           0x51
#define C6DOFIMU14_REG4_OFFSET_USER_0           0x77
#define C6DOFIMU14_REG4_OFFSET_USER_1           0x78
#define C6DOFIMU14_REG4_OFFSET_USER_2           0x79
#define C6DOFIMU14_REG4_OFFSET_USER_3           0x7A
#define C6DOFIMU14_REG4_OFFSET_USER_4           0x7B
#define C6DOFIMU14_REG4_OFFSET_USER_5           0x7C
#define C6DOFIMU14_REG4_OFFSET_USER_6           0x7D
#define C6DOFIMU14_REG4_OFFSET_USER_7           0x7E
#define C6DOFIMU14_REG4_OFFSET_USER_8           0x7F


/*! @} */ // c6dofimu14_reg

/**
 * @defgroup c6dofimu14_set 6DOF IMU 14 Registers Settings
 * @brief Settings for registers of 6DOF IMU 14 Click driver.
 */

/**
 * @addtogroup c6dofimu14_set
 * @{
 */

/**
 * @brief 6DOF IMU 14 Signal path reset register settings.
 * @details Signal path reset register setting flags.
 */
#define C6DOFIMU14_SPR_DMP_INIT_EN                  0x40
#define C6DOFIMU14_SPR_DMP_MEM_RST_EN               0x20
#define C6DOFIMU14_SPR_ABORT_AND_RESET              0x08
#define C6DOFIMU14_SPR_TMST_STROBE                  0x04
#define C6DOFIMU14_SPR_FIFO_FLUSH                   0x02

/**
 * @brief 6DOF IMU 14 INTF config 0 register settings.
 * @details INTF config 0 register setting flags ( Default - 0x30 ).
 */
#define C6DOFIMU14_INTF0_FIFO_HOLD_LAST_DATA_EN     0x80
#define C6DOFIMU14_INTF0_FIFO_HOLD_LAST_DATA_DIS    0x00 
#define C6DOFIMU14_INTF0_FIFO_COUNT_REC_0           0x00 
#define C6DOFIMU14_INTF0_FIFO_COUNT_REC_1           0x40
#define C6DOFIMU14_INTF0_FIFO_COUNT_ENDIAN_0        0x00
#define C6DOFIMU14_INTF0_FIFO_COUNT_ENDIAN_1        0x20 
#define C6DOFIMU14_INTF0_SENSOR_DATA_ENDIAN_0       0x00
#define C6DOFIMU14_INTF0_SENSOR_DATA_ENDIAN_1       0x10 
#define C6DOFIMU14_INTF0_UI_SIFS_CFG_DISABLE_SPI    0x00 
#define C6DOFIMU14_INTF0_UI_SIFS_CFG_DISABLE_I2C    0x01

/**
 * @brief 6DOF IMU 14 INTF config 1 register settings.
 * @details INTF config 1 register setting flags ( Default - 0x91 ).
 */
#define C6DOFIMU14_INTF1_ACLP_CLK_SEL_WAKEUP_CLK    0x00
#define C6DOFIMU14_INTF1_ACLP_CLK_SEL_RC_CLK        0x08
#define C6DOFIMU14_INTF1_RTC_MODE_NO_INPUT          0x00
#define C6DOFIMU14_INTF1_RTC_MODE_INPUT             0x04
#define C6DOFIMU14_INTF1_CLKSEL_RC_OS               0x00
#define C6DOFIMU14_INTF1_CLKSEL_PLL_RC_OS           0x01
#define C6DOFIMU14_INTF1_CLKSEL_DISABLE_ALL_OS      0x11

/**
 * @brief 6DOF IMU 14 PWR-MEGMT0 register settings.
 * @details PWR-MEGMT0 register setting flags ( Default - 0x00 ).
 */
#define C6DOFIMU14_PWR_TEMP_ENABLE                  0x00
#define C6DOFIMU14_PWR_TEMP_DISABLE                 0x20
#define C6DOFIMU14_PWR_IDLE_1                       0x10
#define C6DOFIMU14_PWR_IDLE_0                       0x00
#define C6DOFIMU14_PWR_GYRO_MODE_OFF                0x00
#define C6DOFIMU14_PWR_GYRO_MODE_STAND_BY           0x04
#define C6DOFIMU14_PWR_GYRO_MODE_LOW_NOISE          0x0C
#define C6DOFIMU14_PWR_ACCEL_MODE_OFF               0x00
#define C6DOFIMU14_PWR_ACCEL_MODE_LOW_POWER         0x02
#define C6DOFIMU14_PWR_ACCEL_MODE_LOW_NOISE         0x03

/**
 * @brief 6DOF IMU 14 GYRO CONFIG 0 register settings.
 * @details GYRO CONFIG 0 register setting flags ( Default - 0x06 ).
 */
#define C6DOFIMU14_GCFG0_FS_SEL_2000DPS             0x00
#define C6DOFIMU14_GCFG0_FS_SEL_1000DPS             0x20
#define C6DOFIMU14_GCFG0_FS_SEL_500DPS              0x40
#define C6DOFIMU14_GCFG0_FS_SEL_250DPS              0x60
#define C6DOFIMU14_GCFG0_FS_SEL_125DPS              0x80
#define C6DOFIMU14_GCFG0_FS_SEL_62p5DPS             0xA0
#define C6DOFIMU14_GCFG0_FS_SEL_31p25DPS            0xC0
#define C6DOFIMU14_GCFG0_FS_SEL_15p625DPS           0xE0
#define C6DOFIMU14_GCFG0_ODR_32KHZ                  0x01
#define C6DOFIMU14_GCFG0_ODR_16KHZ                  0x02
#define C6DOFIMU14_GCFG0_ODR_8KHZ                   0x03
#define C6DOFIMU14_GCFG0_ODR_4KHZ                   0x04
#define C6DOFIMU14_GCFG0_ODR_2KHZ                   0x05
#define C6DOFIMU14_GCFG0_ODR_1KHZ                   0x06
#define C6DOFIMU14_GCFG0_ODR_200HZ                  0x07
#define C6DOFIMU14_GCFG0_ODR_100HZ                  0x08
#define C6DOFIMU14_GCFG0_ODR_50HZ                   0x09
#define C6DOFIMU14_GCFG0_ODR_25HZ                   0x0A
#define C6DOFIMU14_GCFG0_ODR_12p5HZ                 0x0B
#define C6DOFIMU14_GCFG0_ODR_500HZ                  0x0F

/**
 * @brief 6DOF IMU 14 ACCEL CONFIG 0 register settings.
 * @details ACCEL CONFIG 0 register setting flags ( Default - 0x06 ).
 */
#define C6DOFIMU14_ACFG0_FS_SEL_16G                 0x00
#define C6DOFIMU14_ACFG0_FS_SEL_8G                  0x20
#define C6DOFIMU14_ACFG0_FS_SEL_4G                  0x40
#define C6DOFIMU14_ACFG0_FS_SEL_2G                  0x60
#define C6DOFIMU14_ACFG0_ODR_32KHZ                  0x01
#define C6DOFIMU14_ACFG0_ODR_16KHZ                  0x02
#define C6DOFIMU14_ACFG0_ODR_8KHZ                   0x03
#define C6DOFIMU14_ACFG0_ODR_4KHZ                   0x04
#define C6DOFIMU14_ACFG0_ODR_2KHZ                   0x05
#define C6DOFIMU14_ACFG0_ODR_1KHZ                   0x06
#define C6DOFIMU14_ACFG0_ODR_200HZ                  0x07
#define C6DOFIMU14_ACFG0_ODR_100HZ                  0x08
#define C6DOFIMU14_ACFG0_ODR_50HZ                   0x09
#define C6DOFIMU14_ACFG0_ODR_25HZ                   0x0A
#define C6DOFIMU14_ACFG0_ODR_12p5HZ                 0x0B
#define C6DOFIMU14_ACFG0_ODR_6p25HZ                 0x0C
#define C6DOFIMU14_ACFG0_ODR_3p125HZ                0x0D
#define C6DOFIMU14_ACFG0_ODR_1p562HZ                0x0E
#define C6DOFIMU14_ACFG0_ODR_500HZ                  0x0F

/**
 * @brief 6DOF IMU 14 GYRO CONFIG 1 register settings.
 * @details GYRO CONFIG 1 register setting flags ( Default - 0x16 ).
 */
#define C6DOFIMU14_GCFG1_FILT_BW_4000HZ             0x00
#define C6DOFIMU14_GCFG1_FILT_BW_170HZ              0x20
#define C6DOFIMU14_GCFG1_FILT_BW_82HZ               0x40
#define C6DOFIMU14_GCFG1_FILT_BW_40HZ               0x60
#define C6DOFIMU14_GCFG1_FILT_BW_20HZ               0x80
#define C6DOFIMU14_GCFG1_FILT_BW_10HZ               0xA0
#define C6DOFIMU14_GCFG1_FILT_BW_5HZ                0xC0
#define C6DOFIMU14_GCFG1_UI_FILT_ORD_1ST_OTHER      0x00
#define C6DOFIMU14_GCFG1_UI_FILT_ORD_2ND_OTHER      0x04
#define C6DOFIMU14_GCFG1_UI_FILT_ORD_3RD_OTHER      0x08
#define C6DOFIMU14_GCFG1_DEC2_M2_ORD_3RD_OTHER      0x02

/**
 * @brief 6DOF IMU 14 GYRO ACCEL CONFIG 0 register settings.
 * @details GYRO ACCEL CONFIG 0 register setting flags ( Default - 0x11 ).
 */
#define C6DOFIMU14_GACFG0_AC_UI_BW_ODR_2            0x00
#define C6DOFIMU14_GACFG0_AC_UI_BW_ODR_4            0x10
#define C6DOFIMU14_GACFG0_AC_UI_BW_ODR_5            0x20
#define C6DOFIMU14_GACFG0_AC_UI_BW_ODR_8            0x30
#define C6DOFIMU14_GACFG0_AC_UI_BW_ODR_10           0x40
#define C6DOFIMU14_GACFG0_AC_UI_BW_ODR_16           0x50
#define C6DOFIMU14_GACFG0_AC_UI_BW_ODR_20           0x60
#define C6DOFIMU14_GACFG0_AC_UI_BW_ODR_40           0x70
#define C6DOFIMU14_GACFG0_GY_UI_BW_ODR_2            0x00
#define C6DOFIMU14_GACFG0_GY_UI_BW_ODR_4            0x01
#define C6DOFIMU14_GACFG0_GY_UI_BW_ODR_5            0x02
#define C6DOFIMU14_GACFG0_GY_UI_BW_ODR_8            0x03
#define C6DOFIMU14_GACFG0_GY_UI_BW_ODR_10           0x04
#define C6DOFIMU14_GACFG0_GY_UI_BW_ODR_16           0x05
#define C6DOFIMU14_GACFG0_GY_UI_BW_ODR_20           0x06
#define C6DOFIMU14_GACFG0_GY_UI_BW_ODR_40           0x07

/**
 * @brief 6DOF IMU 14 ACCEL CONFIG 1 register settings.
 * @details ACCEL CONFIG 1 register setting flags ( Default - 0x0D ).
 */
#define C6DOFIMU14_ACFG1_UI_FILT_ORD_1ST_OTHER      0x00
#define C6DOFIMU14_ACFG1_UI_FILT_ORD_2ND_OTHER      0x04
#define C6DOFIMU14_ACFG1_UI_FILT_ORD_3RD_OTHER      0x08
#define C6DOFIMU14_ACFG1_DEC2_M2_ORD_3RD_OTHER      0x02

/**
 * @brief 6DOF IMU 14 TMST CONFIG register settings.
 * @details TMST CONFIG register setting flags ( Default - 0x23 ).
 */
#define C6DOFIMU14_TMSTCFG_TO_REGS_EN               0x10  
#define C6DOFIMU14_TMSTCFG_TO_REGS_DIS              0x00  
#define C6DOFIMU14_TMSTCFG_RES_0                    0x00  
#define C6DOFIMU14_TMSTCFG_RES_1                    0x08  
#define C6DOFIMU14_TMSTCFG_DELTA_EN                 0x04  
#define C6DOFIMU14_TMSTCFG_DELTA_DIS                0x00  
#define C6DOFIMU14_TMSTCFG_FSYNC_EN                 0x02  
#define C6DOFIMU14_TMSTCFG_FSYNC_DIS                0x00  
#define C6DOFIMU14_TMSTCFG_TMST_ENABLE              0x01  
#define C6DOFIMU14_TMSTCFG_TMST_DISABLE             0x00

/**
 * @brief 6DOF IMU 14 APEX CONFIG 0 register settings.
 * @details APEX CONFIG 0 register setting flags.
 */
#define C6DOFIMU14_APEXCFG0_DMP_NOT_ACTIVE          0x00 
#define C6DOFIMU14_APEXCFG0_DMP_ACTIVE              0x80 
#define C6DOFIMU14_APEXCFG0_TAP_ENABLE              0x40 
#define C6DOFIMU14_APEXCFG0_TAP_DISABLE             0x00 
#define C6DOFIMU14_APEXCFG0_PED_ENABLE              0x20 
#define C6DOFIMU14_APEXCFG0_PED_DISABLE             0x00 
#define C6DOFIMU14_APEXCFG0_TILT_ENABLE             0x10 
#define C6DOFIMU14_APEXCFG0_TILT_DISABLE            0x00 
#define C6DOFIMU14_APEXCFG0_R2W_EMABLE              0x08 
#define C6DOFIMU14_APEXCFG0_R2W_DISABLE             0x00 
#define C6DOFIMU14_APEXCFG0_DMP_ODR_25HZ            0x00 
#define C6DOFIMU14_APEXCFG0_DMP_ODR_50HZ            0x03

/**
 * @brief 6DOF IMU 14 SMD CONFIG register settings.
 * @details SMD CONFIG register setting flags.
 */
#define C6DOFIMU14_SMDCFG_WOM_INT_MODE_0            0x00 
#define C6DOFIMU14_SMDCFG_WOM_INT_MODE_1            0x08 
#define C6DOFIMU14_SMDCFG_WOM_MODE_0                0x00 
#define C6DOFIMU14_SMDCFG_WOM_MODE_1                0x04 
#define C6DOFIMU14_SMDCFG_SMD_MODE_DISABLE          0x00 
#define C6DOFIMU14_SMDCFG_SMD_MODE_SHORT            0x02 
#define C6DOFIMU14_SMDCFG_SMD_MODE_LONG             0x03 

/**
 * @brief 6DOF IMU 14 INT SOURCE 0 register settings.
 * @details INT SOURCE 0 register setting flags.
 */
#define C6DOFIMU14_ISRC0_UI_FSYNC_INT1_EN           0x40
#define C6DOFIMU14_ISRC0_UI_FSYNC_INT1_DIS          0x00
#define C6DOFIMU14_ISRC0_PLL_RDY_INT1_EN            0x20
#define C6DOFIMU14_ISRC0_PLL_RDY_INT1_DIS           0x00
#define C6DOFIMU14_ISRC0_RESET_DONE_INT1_EN         0x10
#define C6DOFIMU14_ISRC0_RESET_DONE_INT1_DIS        0x00
#define C6DOFIMU14_ISRC0_UI_DRDY_INT1_EN            0x08
#define C6DOFIMU14_ISRC0_UI_DRDY_INT1_DIS           0x00
#define C6DOFIMU14_ISRC0_FIFO_THS_INT1_EN           0x04
#define C6DOFIMU14_ISRC0_FIFO_THS_INT1_DIS          0x00
#define C6DOFIMU14_ISRC0_FIFO_FULL_INT1_EN          0x02
#define C6DOFIMU14_ISRC0_FIFO_FULL_INT1_DIS         0x00
#define C6DOFIMU14_ISRC0_UI_AGC_RDY_INT1_EN         0x01
#define C6DOFIMU14_ISRC0_UI_AGC_RDY_INT1_DIS        0x00

/**
 * @brief 6DOF IMU 14 WHO AM I register settings.
 * @details WHO AM I register setting ( Default - 0x47 ).
 */
#define C6DOFIMU14_DEF_WHO_AM_I                     0x47

/**
 * @brief 6DOF IMU 14 REG BANK SELECT register settings.
 * @details REG BANK SELECT register setting flags ( Default - 0x00 ).
 */
#define C6DOFIMU14_BANK_0                           0x00
#define C6DOFIMU14_BANK_1                           0x01
#define C6DOFIMU14_BANK_2                           0x02
#define C6DOFIMU14_BANK_3                           0x03
#define C6DOFIMU14_BANK_4                           0x04

/**
 * @brief 6DOF IMU 14 SENSOR CONFIG 0 register settings.
 * @details SENSOR CONFIG 0 register setting flags.
 */
#define C6DOFIMU14_SENSOR_CFG_GYRO_Z_EN             0x00
#define C6DOFIMU14_SENSOR_CFG_GYRO_Z_DIS            0x20
#define C6DOFIMU14_SENSOR_CFG_GYRO_Y_EN             0x00
#define C6DOFIMU14_SENSOR_CFG_GYRO_Y_DIS            0x10
#define C6DOFIMU14_SENSOR_CFG_GYRO_X_EN             0x00
#define C6DOFIMU14_SENSOR_CFG_GYRO_X_DIS            0x08
#define C6DOFIMU14_SENSOR_CFG_ACCEL_Z_EN            0x00
#define C6DOFIMU14_SENSOR_CFG_ACCEL_Z_DIS           0x04
#define C6DOFIMU14_SENSOR_CFG_ACCEL_Y_EN            0x00
#define C6DOFIMU14_SENSOR_CFG_ACCEL_Y_DIS           0x02
#define C6DOFIMU14_SENSOR_CFG_ACCEL_X_EN            0x00
#define C6DOFIMU14_SENSOR_CFG_ACCEL_X_DIS           0x01

/**
 * @brief 6DOF IMU 14 APEX CONFIG 1 register settings.
 * @details APEX CONFIG 1 register setting flags.
 */
#define C6DOFIMU14_APEX_CFG1_LOW_ENERGY_SEL         0xA0
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_0SEC          0x00
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_4SEC          0x01
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_8SEC          0x02
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_12SEC         0x03
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_16SEC         0x04
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_20SEC         0x05
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_24SEC         0x06
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_28SEC         0x07
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_32SEC         0x08
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_36SEC         0x09
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_40SEC         0x0A
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_44SEC         0x0B
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_48SEC         0x0C
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_52SEC         0x0D
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_56SEC         0x0E
#define C6DOFIMU14_APEX_CFG1_TIME_SEL_60SEC         0x0F

/**
 * @brief 6DOF IMU 14 APEX CONFIG 2 register settings.
 * @details APEX CONFIG 2 register setting flags.
 */
#define C6DOFIMU14_APEX_CFG2_PED_AMP_TH_SEL         0x80
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_0          0x00
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_1          0x01
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_2          0x02
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_3          0x03
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_4          0x04
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_5          0x05
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_6          0x06
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_7          0x07
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_8          0x08
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_9          0x09
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_10         0x0A
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_11         0x0B
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_12         0x0C
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_13         0x0D
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_14         0x0E
#define C6DOFIMU14_APEX_CFG2_PED_CNT_SEL_15         0x0F

/**
 * @brief 6DOF IMU 14 APEX CONFIG 3 register settings.
 * @details APEX CONFIG 3 register setting flags.
 */
#define C6DOFIMU14_APEX_CFG3_STEP_DET_SEL_0         0x00
#define C6DOFIMU14_APEX_CFG3_STEP_DET_SEL_1         0x20
#define C6DOFIMU14_APEX_CFG3_STEP_DET_SEL_2         0x40
#define C6DOFIMU14_APEX_CFG3_STEP_DET_SEL_3         0x60
#define C6DOFIMU14_APEX_CFG3_STEP_DET_SEL_4         0x80
#define C6DOFIMU14_APEX_CFG3_STEP_DET_SEL_5         0xA0
#define C6DOFIMU14_APEX_CFG3_STEP_DET_SEL_6         0xC0
#define C6DOFIMU14_APEX_CFG3_STEP_DET_SEL_7         0xE0
#define C6DOFIMU14_APEX_CFG3_TIMER_SEL_0            0x00
#define C6DOFIMU14_APEX_CFG3_TIMER_SEL_1            0x04
#define C6DOFIMU14_APEX_CFG3_TIMER_SEL_2            0x08
#define C6DOFIMU14_APEX_CFG3_TIMER_SEL_3            0x0C
#define C6DOFIMU14_APEX_CFG3_TIMER_SEL_4            0x10
#define C6DOFIMU14_APEX_CFG3_TIMER_SEL_5            0x14
#define C6DOFIMU14_APEX_CFG3_TIMER_SEL_6            0x18
#define C6DOFIMU14_APEX_CFG3_TIMER_SEL_7            0x1C
#define C6DOFIMU14_APEX_CFG3_HI_EN_TH_SEL           0x01

/**
 * @brief 6DOF IMU 14 APEX CONFIG 4 register settings.
 * @details APEX CONFIG 4 register setting flags.
 */
#define C6DOFIMU14_APEX_CFG4_TILT_WAIT_SEL_0S         0x00
#define C6DOFIMU14_APEX_CFG4_TILT_WAIT_SEL_2S         0x40
#define C6DOFIMU14_APEX_CFG4_TILT_WAIT_SEL_4S         0x80
#define C6DOFIMU14_APEX_CFG4_TILT_WAIT_SEL_6S         0xC0
#define C6DOFIMU14_APEX_CFG4_TILT_SLEEP_TIME_1p28SEC  0x00
#define C6DOFIMU14_APEX_CFG4_TILT_SLEEP_TIME_2p56SEC  0x08
#define C6DOFIMU14_APEX_CFG4_TILT_SLEEP_TIME_3p84SEC  0x10
#define C6DOFIMU14_APEX_CFG4_TILT_SLEEP_TIME_5p12SEC  0x18
#define C6DOFIMU14_APEX_CFG4_TILT_SLEEP_TIME_6p40SEC  0x20
#define C6DOFIMU14_APEX_CFG4_TILT_SLEEP_TIME_7p68SEC  0x28
#define C6DOFIMU14_APEX_CFG4_TILT_SLEEP_TIME_8p96SEC  0x30
#define C6DOFIMU14_APEX_CFG4_TILT_SLEEP_TIME_10p24SEC 0x38

/**
 * @brief 6DOF IMU 14 INT SOURCE 6 register settings.
 * @details INT SOURCE 6 register setting flags.
 */
#define C6DOFIMU14_INTSRC6_STEP_DET_INT1_EN         0x20
#define C6DOFIMU14_INTSRC6_STEP_DET_INT1_DIS        0x00
#define C6DOFIMU14_INTSRC6_STEP_CNT_OFL_INT1_EN     0x10
#define C6DOFIMU14_INTSRC6_STEP_CNT_OFL_INT1_DIS    0x00
#define C6DOFIMU14_INTSRC6_TILT_DET_INT1_EN         0x08
#define C6DOFIMU14_INTSRC6_TILT_DET_INT1_DIS        0x00
#define C6DOFIMU14_INTSRC6_WAKE_DET_INT1_EN         0x04
#define C6DOFIMU14_INTSRC6_WAKE_DET_INT1_DIS        0x00
#define C6DOFIMU14_INTSRC6_SLEEP_DET_INT1_EN        0x02
#define C6DOFIMU14_INTSRC6_SLEEP_DET_INT1_DIS       0x00
#define C6DOFIMU14_INTSRC6_TAP_DET_INT1_EN          0x01
#define C6DOFIMU14_INTSRC6_TAP_DET_INT1_DIS         0x00

/**
 * @brief 6DOF IMU 14 INT SOURCE 7 register settings.
 * @details INT SOURCE 7 register setting flags.
 */
#define C6DOFIMU14_INTSRC7_STEP_DET_INT2_EN         0x20
#define C6DOFIMU14_INTSRC7_STEP_DET_INT2_DIS        0x00
#define C6DOFIMU14_INTSRC7_STEP_CNT_OFL_INT2_EN     0x10
#define C6DOFIMU14_INTSRC7_STEP_CNT_OFL_INT2_DIS    0x00
#define C6DOFIMU14_INTSRC7_TILT_DET_INT2_EN         0x08
#define C6DOFIMU14_INTSRC7_TILT_DET_INT2_DIS        0x00
#define C6DOFIMU14_INTSRC7_WAKE_DET_INT2_EN         0x04
#define C6DOFIMU14_INTSRC7_WAKE_DET_INT2_DIS        0x00
#define C6DOFIMU14_INTSRC7_SLEEP_DET_INT2_EN        0x02
#define C6DOFIMU14_INTSRC7_SLEEP_DET_INT2_DIS       0x00
#define C6DOFIMU14_INTSRC7_TAP_DET_INT2_EN          0x01
#define C6DOFIMU14_INTSRC7_TAP_DET_INT2_DIS         0x00

/**
 * @brief 6DOF IMU 14 DEVICE CONFIG register settings.
 * @details DEVICE CONFIG register setting flags.
 */
#define C6DOFIMU14_DEVCONFIG_SPI_MODE_03            0x00
#define C6DOFIMU14_DEVCONFIG_SPI_MODE_12            0x10
#define C6DOFIMU14_DEVCONFIG_SOFT_RESET_NORMAL      0x00
#define C6DOFIMU14_DEVCONFIG_SOFT_RESET_ENABLE      0x01

/**
 * @brief 6DOF IMU 14 DRIVE CONFIG register settings.
 * @details DRIVE CONFIG register setting flags.
 */
#define C6DOFIMU14_DRIVECONFIG_MAX_SLEW_RATE        0x55
#define C6DOFIMU14_DRIVECONFIG_MIN_SLEW_RATE        0x00

/**
 * @brief 6DOF IMU 14 FIFO CONFIG register settings.
 * @details FIFO CONFIG register setting flags.
 */
#define C6DOFIMU14_FIFOCONFIG_BYPASS_MODE           0x00
#define C6DOFIMU14_FIFOCONFIG_STREAM_TO_FIFO_MODE   0x40
#define C6DOFIMU14_FIFOCONFIG_STOP_ON_FULL_MODE     0x80

/**
 * @brief 6DOF IMU 14 FIFO CONFIG 1 register settings.
 * @details FIFO CONFIG 1 register setting flags.
 */
#define C6DOFIMU14_FIFOCONFIG1_RESUME_PARTIAL_RD     0x40
#define C6DOFIMU14_FIFOCONFIG1_HIRES_EN              0x10
#define C6DOFIMU14_FIFOCONFIG1_TMST_FSYNC_EN         0x08
#define C6DOFIMU14_FIFOCONFIG1_TEMP_EN               0x04
#define C6DOFIMU14_FIFOCONFIG1_GYRO_EN               0x02
#define C6DOFIMU14_FIFOCONFIG1_ACCEL_EN              0x01

/**
 * @brief 6DOF IMU 14 INT STATUS register settings.
 * @details INT STATUS register setting flags.
 */
#define C6DOFIMU14_INTSTATUS_UI_FSYNC                0x40
#define C6DOFIMU14_INTSTATUS_PLL_RDY                 0x20
#define C6DOFIMU14_INTSTATUS_RESET_DONE              0x10
#define C6DOFIMU14_INTSTATUS_DATA_RDY                0x08
#define C6DOFIMU14_INTSTATUS_FIFO_THS                0x04
#define C6DOFIMU14_INTSTATUS_FIFO_FULL               0x02
#define C6DOFIMU14_INTSTATUS_AGC_RDY                 0x01

/**
 * @brief 6DOF IMU 14 FIFO HEADER byte settings.
 * @details FIFO HEADER byte setting flags.
 */
#define C6DOFIMU14_FIFOHEADER_MSG                    0x80
#define C6DOFIMU14_FIFOHEADER_ACCEL                  0x40
#define C6DOFIMU14_FIFOHEADER_GYRO                   0x20
#define C6DOFIMU14_FIFOHEADER_20                     0x10
#define C6DOFIMU14_FIFOHEADER_TIMESTAMP_ODR          0x08
#define C6DOFIMU14_FIFOHEADER_ODR_ACCEL              0x02
#define C6DOFIMU14_FIFOHEADER_ODR_GYRO               0x01

/**
 * @brief 6DOF IMU 14 SPI read/write bit settings.
 * @details SPI read/write bit setting flags.
 */
#define C6DOFIMU14_SPI_READ_MASK                    0x80
#define C6DOFIMU14_SPI_WRITE_MASK                   0x7F

/**
 * @brief 6DOF IMU 14 device address setting.
 * @details Specified setting for device slave address selection of
 * 6DOF IMU 14 Click driver.
 */
#define C6DOFIMU14_SET_DEV_ADDR_GND                 0x68
#define C6DOFIMU14_SET_DEV_ADDR_VCC                 0x69

/*! @} */ // c6dofimu14_set

/**
 * @defgroup c6dofimu14_map 6DOF IMU 14 MikroBUS Map
 * @brief MikroBUS pin mapping of 6DOF IMU 14 Click driver.
 */

/**
 * @addtogroup c6dofimu14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6DOF IMU 14 Click to the selected MikroBUS.
 */
#define C6DOFIMU14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.snc = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6dofimu14_map
/*! @} */ // c6dofimu14

/**
 * @brief 6DOF IMU 14 Click driver selector.
 * @details Selects target driver interface of 6DOF IMU 14 Click driver.
 */
typedef enum
{
    C6DOFIMU14_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    C6DOFIMU14_DRV_SEL_I2C       /**< I2C driver descriptor. */

} c6dofimu14_drv_t;

/**
 * @brief 6DOF IMU 14 Click driver interface.
 * @details Definition of driver interface of 6DOF IMU 14 Click driver.
 */
typedef err_t ( *c6dofimu14_master_io_t )( struct c6dofimu14_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief 6DOF IMU 14 Axis structure object.
 * @details Axis structure object definition of 6DOF IMU 14 Click driver.
 */
typedef struct 
{
    int16_t x;
    int16_t y;
    int16_t z;

} c6dofimu14_axis_t;

/**
 * @brief 6DOF IMU 14 Click context object.
 * @details Context object definition of 6DOF IMU 14 Click driver.
 */
typedef struct c6dofimu14_s
{
    digital_out_t cs;                   /**< Chip select. */
    digital_in_t  snc;                  /**< External sync. */
    digital_in_t  int_pin;              /**< Interrupt. */

    i2c_master_t  i2c;                  /**< I2C driver object. */
    spi_master_t  spi;                  /**< SPI driver object. */

    uint8_t     slave_address;          /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;            /**< Chip select pin descriptor (used for SPI driver). */
    c6dofimu14_drv_t  drv_sel;          /**< Master driver interface selector. */

    c6dofimu14_master_io_t  write_f;    /**< Master write function. */
    c6dofimu14_master_io_t  read_f;     /**< Master read function. */

} c6dofimu14_t;

/**
 * @brief 6DOF IMU 14 Click configuration object.
 * @details Configuration object definition of 6DOF IMU 14 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                    /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                    /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;                   /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;                   /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                    /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                     /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  snc;                    /**< External sync. */
    pin_name_t  int_pin;                /**< Interrupt. */

    uint32_t    i2c_speed;              /**< I2C serial speed. */
    uint8_t     i2c_address;            /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

    c6dofimu14_drv_t                   drv_sel;         /**< Master driver interface selector. */

} c6dofimu14_cfg_t;

/**
 * @brief 6DOF IMU 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C6DOFIMU14_OK = 0,
    C6DOFIMU14_ERROR = -1

} c6dofimu14_return_value_t;

/*!
 * @addtogroup c6dofimu14 6DOF IMU 14 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 14 Click driver.
 * @{
 */

/**
 * @brief 6DOF IMU 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c6dofimu14_cfg_setup ( c6dofimu14_cfg_t *cfg );

/**
 * @brief 6DOF IMU 14 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu14_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #c6dofimu14_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void c6dofimu14_drv_interface_selection ( c6dofimu14_cfg_t *cfg, c6dofimu14_drv_t drv_sel );

/**
 * @brief 6DOF IMU 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6dofimu14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu14_init ( c6dofimu14_t *ctx, c6dofimu14_cfg_t *cfg );

/**
 * @brief 6DOF IMU 14 default configuration function.
 * @details This function executes a default configuration of 6DOF IMU 14
 * click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c6dofimu14_default_cfg ( c6dofimu14_t *ctx );

/**
 * @brief 6DOF IMU 14 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu14_generic_write ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 14 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu14_generic_read ( c6dofimu14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 14 get INT pin state function.
 * @details This function returns the state of INT pin.
 * @param[in] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @note None.
 */
uint8_t c6dofimu14_get_int_pin ( c6dofimu14_t *ctx );

/**
 * @brief 6DOF IMU 14 get SNC pin state function.
 * @details This function returns the state of SNC pin.
 * @param[in] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @note None.
 */
uint8_t c6dofimu14_get_snc_pin ( c6dofimu14_t *ctx );

/**
 * @brief 6DOF IMU 14 software reset function.
 * @details This function performs the device software reset.
 * @param[in] ctx : Click context object.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu14_software_reset ( c6dofimu14_t *ctx );

/**
 * @brief 6DOF IMU 14 get accel and gyro data function.
 * @details This function reads accel and gyro data for all three axis.
 * @param[in] ctx : Click context object.
 * @param[out] acc_axis : Accel axis output.
 * @param[out] gyro_axis : Gyro axis output.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu14_get_data ( c6dofimu14_t *ctx, c6dofimu14_axis_t *acc_axis, c6dofimu14_axis_t *gyro_axis );

/**
 * @brief 6DOF IMU 14 get temperature data function.
 * @details This function reads the raw temperature data and converts it to Celsius.
 * @param[in] ctx : Click context object.
 * @param[out] temp : Temperature in Celsius.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu14_get_temperature ( c6dofimu14_t *ctx, float *temp );

/**
 * @brief 6DOF IMU 14 get accel data function.
 * @details This function reads accel data for all three axis.
 * @param[in] ctx : Click context object.
 * @param[out] axis : Accel axis output.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu14_get_accel_axis ( c6dofimu14_t *ctx, c6dofimu14_axis_t *axis );

/**
 * @brief 6DOF IMU 14 get gyro data function.
 * @details This function reads gyro data for all three axis.
 * @param[in] ctx : Click context object.
 * @param[out] axis : Gyro axis output.
 * See #c6dofimu14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu14_get_gyro_axis ( c6dofimu14_t *ctx, c6dofimu14_axis_t *axis );

#ifdef __cplusplus
}
#endif
#endif // C6DOFIMU14_H

/*! @} */ // c6dofimu14

// ------------------------------------------------------------------------ END
