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
 * @file smartdof5.h
 * @brief This file contains API for Smart DOF 5 Click Driver.
 */

#ifndef SMARTDOF5_H
#define SMARTDOF5_H

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
#include "spi_specifics.h"

/*!
 * @addtogroup smartdof5 Smart DOF 5 Click Driver
 * @brief API for configuring and manipulating Smart DOF 5 Click driver.
 * @{
 */

/**
 * @defgroup smartdof5_reg Smart DOF 5 Registers List
 * @brief List of registers of Smart DOF 5 Click driver.
 */

/**
 * @addtogroup smartdof5_reg
 * @{
 */

/**
 * @brief Smart DOF 5 user memory register list.
 * @details Specified user memory register list of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_REG_FUNC_CFG_ACCESS               0x01
#define SMARTDOF5_REG_PIN_CTRL                      0x02
#define SMARTDOF5_REG_FIFO_CTRL1                    0x07
#define SMARTDOF5_REG_FIFO_CTRL2                    0x08
#define SMARTDOF5_REG_FIFO_CTRL3                    0x09
#define SMARTDOF5_REG_FIFO_CTRL4                    0x0A
#define SMARTDOF5_REG_COUNTER_BDR_1                 0x0B
#define SMARTDOF5_REG_COUNTER_BDR_2                 0x0C
#define SMARTDOF5_REG_INT1_CTRL                     0x0D
#define SMARTDOF5_REG_INT2_CTRL                     0x0E
#define SMARTDOF5_REG_WHO_AM_I                      0x0F
#define SMARTDOF5_REG_CTRL1_XL                      0x10
#define SMARTDOF5_REG_CTRL2_G                       0x11
#define SMARTDOF5_REG_CTRL3_C                       0x12
#define SMARTDOF5_REG_CTRL4_C                       0x13
#define SMARTDOF5_REG_CTRL5_C                       0x14
#define SMARTDOF5_REG_CTRL6_C                       0x15
#define SMARTDOF5_REG_CTRL7_G                       0x16
#define SMARTDOF5_REG_CTRL8_XL                      0x17
#define SMARTDOF5_REG_CTRL9_XL                      0x18
#define SMARTDOF5_REG_CTRL10_C                      0x19
#define SMARTDOF5_REG_ALL_INT_SRC                   0x1A
#define SMARTDOF5_REG_WAKE_UP_SRC                   0x1B
#define SMARTDOF5_REG_D6D_SRC                       0x1D
#define SMARTDOF5_REG_STATUS                        0x1E
#define SMARTDOF5_REG_OUT_TEMP_L                    0x20
#define SMARTDOF5_REG_OUT_TEMP_H                    0x21
#define SMARTDOF5_REG_OUTX_L_G                      0x22
#define SMARTDOF5_REG_OUTX_H_G                      0x23
#define SMARTDOF5_REG_OUTY_L_G                      0x24
#define SMARTDOF5_REG_OUTY_H_G                      0x25
#define SMARTDOF5_REG_OUTZ_L_G                      0x26
#define SMARTDOF5_REG_OUTZ_H_G                      0x27
#define SMARTDOF5_REG_OUTX_L_A                      0x28
#define SMARTDOF5_REG_OUTX_H_A                      0x29
#define SMARTDOF5_REG_OUTY_L_A                      0x2A
#define SMARTDOF5_REG_OUTY_H_A                      0x2B
#define SMARTDOF5_REG_OUTZ_L_A                      0x2C
#define SMARTDOF5_REG_OUTZ_H_A                      0x2D
#define SMARTDOF5_REG_EMB_FUNC_STATUS_MAINPAGE      0x35
#define SMARTDOF5_REG_FSM_STATUS_A_MAINPAGE         0x36
#define SMARTDOF5_REG_FSM_STATUS_B_MAINPAGE         0x37
#define SMARTDOF5_REG_MLC_STATUS_MAINPAGE           0x38
#define SMARTDOF5_REG_STATUS_MASTER_MAINPAGE        0x39
#define SMARTDOF5_REG_FIFO_STATUS1                  0x3A
#define SMARTDOF5_REG_FIFO_STATUS2                  0x3B
#define SMARTDOF5_REG_TIMESTAMP0                    0x40
#define SMARTDOF5_REG_TIMESTAMP1                    0x41
#define SMARTDOF5_REG_TIMESTAMP2                    0x42
#define SMARTDOF5_REG_TIMESTAMP3                    0x43
#define SMARTDOF5_REG_INT_CFG0                      0x56
#define SMARTDOF5_REG_INT_CFG1                      0x58
#define SMARTDOF5_REG_THS_6D                        0x59
#define SMARTDOF5_REG_WAKE_UP_THS                   0x5B
#define SMARTDOF5_REG_WAKE_UP_DUR                   0x5C
#define SMARTDOF5_REG_FREE_FALL                     0x5D
#define SMARTDOF5_REG_MD1_CFG                       0x5E
#define SMARTDOF5_REG_MD2_CFG                       0x5F
#define SMARTDOF5_REG_I3C_BUS_AVB                   0x62
#define SMARTDOF5_REG_INTERNAL_FREQ_FINE            0x63
#define SMARTDOF5_REG_X_OFS_USR                     0x73
#define SMARTDOF5_REG_Y_OFS_USR                     0x74
#define SMARTDOF5_REG_Z_OFS_USR                     0x75
#define SMARTDOF5_REG_FIFO_DATA_OUT_TAG             0x78
#define SMARTDOF5_REG_FIFO_DATA_OUT_X_L             0x79
#define SMARTDOF5_REG_FIFO_DATA_OUT_X_H             0x7A
#define SMARTDOF5_REG_FIFO_DATA_OUT_Y_L             0x7B
#define SMARTDOF5_REG_FIFO_DATA_OUT_Y_H             0x7C
#define SMARTDOF5_REG_FIFO_DATA_OUT_Z_L             0x7D
#define SMARTDOF5_REG_FIFO_DATA_OUT_Z_H             0x7E

/**
 * @brief Smart DOF 5 sensor hub register list.
 * @details Specified sensor hub register list of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_1             0x02
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_2             0x03
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_3             0x04
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_4             0x05
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_5             0x06
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_6             0x07
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_7             0x08
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_8             0x09
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_9             0x0A
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_10            0x0B
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_11            0x0C
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_12            0x0D
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_13            0x0E
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_14            0x0F
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_15            0x10
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_16            0x11
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_17            0x12
#define SMARTDOF5_REG_SHUB_SENSOR_HUB_18            0x13
#define SMARTDOF5_REG_SHUB_MASTER_CONFIG            0x14
#define SMARTDOF5_REG_SHUB_SLV0_ADD                 0x15
#define SMARTDOF5_REG_SHUB_SLV0_SUBADD              0x16
#define SMARTDOF5_REG_SHUB_SLV0_CONFIG              0x17
#define SMARTDOF5_REG_SHUB_SLV1_ADD                 0x18
#define SMARTDOF5_REG_SHUB_SLV1_SUBADD              0x19
#define SMARTDOF5_REG_SHUB_SLV1_CONFIG              0x1A
#define SMARTDOF5_REG_SHUB_SLV2_ADD                 0x1B
#define SMARTDOF5_REG_SHUB_SLV2_SUBADD              0x1C
#define SMARTDOF5_REG_SHUB_SLV2_CONFIG              0x1D
#define SMARTDOF5_REG_SHUB_SLV3_ADD                 0x1E
#define SMARTDOF5_REG_SHUB_SLV3_SUBADD              0x1F
#define SMARTDOF5_REG_SHUB_SLV3_CONFIG              0x20
#define SMARTDOF5_REG_SHUB_DATAWRITE_SLV0           0x21
#define SMARTDOF5_REG_SHUB_STATUS_MASTER            0x22

/**
 * @brief Smart DOF 5 embedded functions register list.
 * @details Specified embedded functions register list of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_REG_EMBF_PAGE_SEL                 0x02
#define SMARTDOF5_REG_EMBF_EMB_FUNC_EN_B            0x05
#define SMARTDOF5_REG_EMBF_PAGE_ADDRESS             0x08
#define SMARTDOF5_REG_EMBF_PAGE_VALUE               0x09
#define SMARTDOF5_REG_EMBF_EMB_FUNC_INT1            0x0A
#define SMARTDOF5_REG_EMBF_FSM_INT1_A               0x0B
#define SMARTDOF5_REG_EMBF_FSM_INT1_B               0x0C
#define SMARTDOF5_REG_EMBF_MLC_INT1                 0x0D
#define SMARTDOF5_REG_EMBF_EMB_FUNC_INT2            0x0E
#define SMARTDOF5_REG_EMBF_FSM_INT2_A               0x0F
#define SMARTDOF5_REG_EMBF_FSM_INT2_B               0x10
#define SMARTDOF5_REG_EMBF_MLC_INT2                 0x11
#define SMARTDOF5_REG_EMBF_EMB_FUNC_STATUS          0x12
#define SMARTDOF5_REG_EMBF_FSM_STATUS_A             0x13
#define SMARTDOF5_REG_EMBF_FSM_STATUS_B             0x14
#define SMARTDOF5_REG_EMBF_MLC_STATUS               0x15
#define SMARTDOF5_REG_EMBF_PAGE_RW                  0x17
#define SMARTDOF5_REG_EMBF_FSM_ENABLE_A             0x46
#define SMARTDOF5_REG_EMBF_FSM_ENABLE_B             0x47
#define SMARTDOF5_REG_EMBF_FSM_LONG_COUNTER_L       0x48
#define SMARTDOF5_REG_EMBF_FSM_LONG_COUNTER_H       0x49
#define SMARTDOF5_REG_EMBF_FSM_LONG_COUNTER_CLEAR   0x4A
#define SMARTDOF5_REG_EMBF_FSM_OUTS1                0x4C
#define SMARTDOF5_REG_EMBF_FSM_OUTS2                0x4D
#define SMARTDOF5_REG_EMBF_FSM_OUTS3                0x4E
#define SMARTDOF5_REG_EMBF_FSM_OUTS4                0x4F
#define SMARTDOF5_REG_EMBF_FSM_OUTS5                0x50
#define SMARTDOF5_REG_EMBF_FSM_OUTS6                0x51
#define SMARTDOF5_REG_EMBF_FSM_OUTS7                0x52
#define SMARTDOF5_REG_EMBF_FSM_OUTS8                0x53
#define SMARTDOF5_REG_EMBF_FSM_OUTS9                0x54
#define SMARTDOF5_REG_EMBF_FSM_OUTS10               0x55
#define SMARTDOF5_REG_EMBF_FSM_OUTS11               0x56
#define SMARTDOF5_REG_EMBF_FSM_OUTS12               0x57
#define SMARTDOF5_REG_EMBF_FSM_OUTS13               0x58
#define SMARTDOF5_REG_EMBF_FSM_OUTS14               0x59
#define SMARTDOF5_REG_EMBF_FSM_OUTS15               0x5A
#define SMARTDOF5_REG_EMBF_FSM_OUTS16               0x5B
#define SMARTDOF5_REG_EMBF_EMB_FUNC_ODR_CFG_B       0x5F
#define SMARTDOF5_REG_EMBF_EMB_FUNC_ODR_CFG_C       0x60
#define SMARTDOF5_REG_EMBF_EMB_FUNC_INIT_B          0x67
#define SMARTDOF5_REG_EMBF_MLC0_SRC                 0x70
#define SMARTDOF5_REG_EMBF_MLC1_SRC                 0x71
#define SMARTDOF5_REG_EMBF_MLC2_SRC                 0x72
#define SMARTDOF5_REG_EMBF_MLC3_SRC                 0x73
#define SMARTDOF5_REG_EMBF_MLC4_SRC                 0x74
#define SMARTDOF5_REG_EMBF_MLC5_SRC                 0x75
#define SMARTDOF5_REG_EMBF_MLC6_SRC                 0x76
#define SMARTDOF5_REG_EMBF_MLC7_SRC                 0x77
#define SMARTDOF5_REG_EMBF_P0_MAG_SENSITIVITY_L     0xBA
#define SMARTDOF5_REG_EMBF_P0_MAG_SENSITIVITY_H     0xBB
#define SMARTDOF5_REG_EMBF_P0_MAG_OFFX_L            0xC0
#define SMARTDOF5_REG_EMBF_P0_MAG_OFFX_H            0xC1
#define SMARTDOF5_REG_EMBF_P0_MAG_OFFY_L            0xC2
#define SMARTDOF5_REG_EMBF_P0_MAG_OFFY_H            0xC3
#define SMARTDOF5_REG_EMBF_P0_MAG_OFFZ_L            0xC4
#define SMARTDOF5_REG_EMBF_P0_MAG_OFFZ_H            0xC5
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_XX_L           0xC6
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_XX_H           0xC7
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_XY_L           0xC8
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_XY_H           0xC9
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_XZ_L           0xCA
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_XZ_H           0xCB
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_YY_L           0xCC
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_YY_H           0xCD
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_YZ_L           0xCE
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_YZ_H           0xCF
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_ZZ_L           0xD0
#define SMARTDOF5_REG_EMBF_P0_MAG_SI_ZZ_H           0xD1
#define SMARTDOF5_REG_EMBF_P0_MAG_CFG_A             0xD4
#define SMARTDOF5_REG_EMBF_P0_MAG_CFG_B             0xD5
#define SMARTDOF5_REG_EMBF_P1_FSM_LC_TIMEOUT_L      0x7A
#define SMARTDOF5_REG_EMBF_P1_FSM_LC_TIMEOUT_H      0x7B
#define SMARTDOF5_REG_EMBF_P1_FSM_PROGRAMS          0x7C
#define SMARTDOF5_REG_EMBF_P1_FSM_START_ADD_L       0x7E
#define SMARTDOF5_REG_EMBF_P1_FSM_START_ADD_H       0x7F
#define SMARTDOF5_REG_EMBF_P1_MLC_MAG_SENSITIVITY_L 0xE8
#define SMARTDOF5_REG_EMBF_P1_MLC_MAG_SENSITIVITY_H 0xE9

/*! @} */ // smartdof5_reg

/**
 * @defgroup smartdof5_set Smart DOF 5 Registers Settings
 * @brief Settings for registers of Smart DOF 5 Click driver.
 */

/**
 * @addtogroup smartdof5_set
 * @{
 */
 
/**
 * @brief Smart DOF 5 FUNC_CFG_ACCESS register setting.
 * @details Specified setting for FUNC_CFG_ACCESS register of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_FUNC_CFG_ACCESS_MASK              0xC0

/**
 * @brief Smart DOF 5 WHO_AM_I register setting.
 * @details Specified setting for WHO_AM_I register of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_INT1_CTRL_DEN_DRDY                0x80
#define SMARTDOF5_INT1_CTRL_CNT_BDR                 0x40
#define SMARTDOF5_INT1_CTRL_FIFO_FULL               0x20
#define SMARTDOF5_INT1_CTRL_FIFO_OVR                0x10
#define SMARTDOF5_INT1_CTRL_FIFO_TH                 0x08
#define SMARTDOF5_INT1_CTRL_BOOT                    0x04
#define SMARTDOF5_INT1_CTRL_DRDY_G                  0x02
#define SMARTDOF5_INT1_CTRL_DRDY_XL                 0x01

/**
 * @brief Smart DOF 5 WHO_AM_I register setting.
 * @details Specified setting for WHO_AM_I register of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_WHO_AM_I                          0x6B

/**
 * @brief Smart DOF 5 CTRL1_XL register setting.
 * @details Specified setting for CTRL1_XL register of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_CTRL1_XL_ODR_MASK                 0xF0
#define SMARTDOF5_CTRL1_XL_FS_MASK                  0x0C
#define SMARTDOF5_CTRL1_XL_LPF2_EN_MASK             0x02

/**
 * @brief Smart DOF 5 CTRL2_G register setting.
 * @details Specified setting for CTRL2_G register of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_CTRL2_G_ODR_MASK                  0xF0
#define SMARTDOF5_CTRL2_G_FS_MASK                   0x0C
#define SMARTDOF5_CTRL2_G_FS_125_MASK               0x02
#define SMARTDOF5_CTRL2_G_FS_4000_MASK              0x01

/**
 * @brief Smart DOF 5 CTRL3_C register setting.
 * @details Specified setting for CTRL3_C register of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_CTRL3_C_BOOT                      0x80
#define SMARTDOF5_CTRL3_C_BDU                       0x40
#define SMARTDOF5_CTRL3_C_H_LACTIVE                 0x20
#define SMARTDOF5_CTRL3_C_PP_OD                     0x10
#define SMARTDOF5_CTRL3_C_SIM                       0x08
#define SMARTDOF5_CTRL3_C_IF_INC                    0x04
#define SMARTDOF5_CTRL3_C_SW_RESET                  0x01

/**
 * @brief Smart DOF 5 CTRL9_XL register setting.
 * @details Specified setting for CTRL9_XL register of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_CTRL9_XL_DEN_X                    0x80
#define SMARTDOF5_CTRL9_XL_DEN_Y                    0x40
#define SMARTDOF5_CTRL9_XL_DEN_Z                    0x20
#define SMARTDOF5_CTRL9_XL_DEN_XL_G                 0x10
#define SMARTDOF5_CTRL9_XL_DEN_XL_EN                0x08
#define SMARTDOF5_CTRL9_XL_DEN_LH                   0x04
#define SMARTDOF5_CTRL9_XL_I3C_DISABLE              0x02

/**
 * @brief Smart DOF 5 STATUS register setting.
 * @details Specified setting for STATUS register of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_STATUS_TDA                        0x04
#define SMARTDOF5_STATUS_GDA                        0x02
#define SMARTDOF5_STATUS_XLDA                       0x01

/**
 * @brief Smart DOF 5 memory bank setting.
 * @details Specified setting for memory bank of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_MEM_BANK_USER                     0
#define SMARTDOF5_MEM_BANK_SENSOR_HUB               1
#define SMARTDOF5_MEM_BANK_EMBEDDED_FUNC            2

/**
 * @brief Smart DOF 5 accel output data rate setting.
 * @details Specified setting for accel output data rate of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_ACCEL_ODR_OFF                     0
#define SMARTDOF5_ACCEL_ODR_12_5_HZ                 1
#define SMARTDOF5_ACCEL_ODR_26_HZ                   2
#define SMARTDOF5_ACCEL_ODR_52_HZ                   3
#define SMARTDOF5_ACCEL_ODR_104_HZ                  4
#define SMARTDOF5_ACCEL_ODR_208_HZ                  5
#define SMARTDOF5_ACCEL_ODR_417_HZ                  6
#define SMARTDOF5_ACCEL_ODR_833_HZ                  7
#define SMARTDOF5_ACCEL_ODR_1667_HZ                 8
#define SMARTDOF5_ACCEL_ODR_3333_HZ                 9
#define SMARTDOF5_ACCEL_ODR_6667_HZ                 10
#define SMARTDOF5_ACCEL_ODR_1_6_HZ                  11

/**
 * @brief Smart DOF 5 accel full scale setting.
 * @details Specified setting for accel full scale of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_ACCEL_FS_2G                       0
#define SMARTDOF5_ACCEL_FS_16G                      1
#define SMARTDOF5_ACCEL_FS_4G                       2
#define SMARTDOF5_ACCEL_FS_8G                       3

/**
 * @brief Smart DOF 5 gyro output data rate setting.
 * @details Specified setting for gyro output data rate of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_GYRO_ODR_OFF                      0
#define SMARTDOF5_GYRO_ODR_12_5_HZ                  1
#define SMARTDOF5_GYRO_ODR_26_HZ                    2
#define SMARTDOF5_GYRO_ODR_52_HZ                    3
#define SMARTDOF5_GYRO_ODR_104_HZ                   4
#define SMARTDOF5_GYRO_ODR_208_HZ                   5
#define SMARTDOF5_GYRO_ODR_417_HZ                   6
#define SMARTDOF5_GYRO_ODR_833_HZ                   7
#define SMARTDOF5_GYRO_ODR_1667_HZ                  8
#define SMARTDOF5_GYRO_ODR_3333_HZ                  9
#define SMARTDOF5_GYRO_ODR_6667_HZ                  10

/**
 * @brief Smart DOF 5 gyro full scale setting.
 * @details Specified setting for gyro full scale of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_GYRO_FS_250DPS                    0
#define SMARTDOF5_GYRO_FS_500DPS                    1
#define SMARTDOF5_GYRO_FS_1000DPS                   2
#define SMARTDOF5_GYRO_FS_2000DPS                   3
#define SMARTDOF5_GYRO_FS_4000DPS                   4
#define SMARTDOF5_GYRO_FS_125DPS                    5

/**
 * @brief Smart DOF 5 sensitivity setting.
 * @details Specified setting for sensitivity of Smart DOF 5 Click driver.
 */
#define SMARTDOF5_ACCEL_SENS_G_PER_LSB              0.000061
#define SMARTDOF5_GYRO_SENS_DPS_PER_LSB             0.004375
#define SMARTDOF5_TEMP_SENS_LSB_PER_C               256.0
#define SMARTDOF5_TEMP_OFFSET                       25.0

/**
 * @brief Smart DOF 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Smart DOF 5 Click driver.
 */
#define SMARTDOF5_DEVICE_ADDRESS_0                  0x6A
#define SMARTDOF5_DEVICE_ADDRESS_1                  0x6B

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b smartdof5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define SMARTDOF5_SET_DATA_SAMPLE_EDGE              SET_SPI_DATA_SAMPLE_EDGE
#define SMARTDOF5_SET_DATA_SAMPLE_MIDDLE            SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // smartdof5_set

/**
 * @defgroup smartdof5_map Smart DOF 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart DOF 5 Click driver.
 */

/**
 * @addtogroup smartdof5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart DOF 5 Click to the selected MikroBUS.
 */
#define SMARTDOF5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smartdof5_map
/*! @} */ // smartdof5

/**
 * @brief Smart DOF 5 Click driver selector.
 * @details Selects target driver interface of Smart DOF 5 Click driver.
 */
typedef enum
{
    SMARTDOF5_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    SMARTDOF5_DRV_SEL_I2C       /**< I2C driver descriptor. */

} smartdof5_drv_t;

/**
 * @brief Smart DOF 5 Click driver interface.
 * @details Definition of driver interface of Smart DOF 5 Click driver.
 */
struct smartdof5_s;
typedef err_t ( *smartdof5_master_io_t )( struct smartdof5_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Smart DOF 5 Click context object.
 * @details Context object definition of Smart DOF 5 Click driver.
 */
typedef struct smartdof5_s
{
    digital_in_t int_pin;               /**< Interrupt 1 pin. */

    i2c_master_t i2c;                   /**< I2C driver object. */
    spi_master_t spi;                   /**< SPI driver object. */

    uint8_t      slave_address;         /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;           /**< Chip select pin descriptor (used for SPI driver). */
    smartdof5_drv_t drv_sel;            /**< Master driver interface selector. */

    smartdof5_master_io_t write_f;      /**< Master write function. */
    smartdof5_master_io_t read_f;       /**< Master read function. */

    float gyro_sens;                    /**< Gyro sensitivity setting. */
    float accel_sens;                   /**< Accel sensitivity setting. */

} smartdof5_t;

/**
 * @brief Smart DOF 5 Click configuration object.
 * @details Configuration object definition of Smart DOF 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                    /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                    /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                     /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                      /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int_pin;                 /**< Description. */

    uint32_t   i2c_speed;               /**< I2C serial speed. */
    uint8_t    i2c_address;             /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    smartdof5_drv_t drv_sel;            /**< Master driver interface selector. */

} smartdof5_cfg_t;

/**
 * @brief Smart DOF 5 Click axes data structure.
 * @details Axes data object definition of Smart DOF 5 Click driver.
 */
typedef struct
{
    float x;                            /**< X axis. */
    float y;                            /**< Y axis. */
    float z;                            /**< Z axis. */

} smartdof5_axes_t;

/**
 * @brief Smart DOF 5 Click data structure.
 * @details Data object definition of Smart DOF 5 Click driver.
 */
typedef struct
{
    smartdof5_axes_t accel;             /**< Accel data. */
    smartdof5_axes_t gyro;              /**< Gyro data. */
    float temperature;                  /**< Temperature data. */

} smartdof5_data_t;

/**
 * @brief Smart DOF 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTDOF5_OK = 0,
    SMARTDOF5_ERROR = -1

} smartdof5_return_value_t;

/*!
 * @addtogroup smartdof5 Smart DOF 5 Click Driver
 * @brief API for configuring and manipulating Smart DOF 5 Click driver.
 * @{
 */

/**
 * @brief Smart DOF 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartdof5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartdof5_cfg_setup ( smartdof5_cfg_t *cfg );

/**
 * @brief Smart DOF 5 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #smartdof5_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #smartdof5_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void smartdof5_drv_interface_sel ( smartdof5_cfg_t *cfg, smartdof5_drv_t drv_sel );

/**
 * @brief Smart DOF 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartdof5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_init ( smartdof5_t *ctx, smartdof5_cfg_t *cfg );

/**
 * @brief Smart DOF 5 default configuration function.
 * @details This function executes a default configuration of Smart DOF 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartdof5_default_cfg ( smartdof5_t *ctx );

/**
 * @brief Smart DOF 5 write reg function.
 * @details This function writes a data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_write_reg ( smartdof5_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Smart DOF 5 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_write_regs ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart DOF 5 read reg function.
 * @details This function reads a data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_read_reg ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Smart DOF 5 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_read_regs ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smart DOF 5 get int pin function.
 * @details This function returns the interrupt 1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t smartdof5_get_int_pin ( smartdof5_t *ctx );

/**
 * @brief Smart DOF 5 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_check_communication ( smartdof5_t *ctx );

/**
 * @brief Smart DOF 5 set mem bank function.
 * @details This function sets the memory bank to user memory, sensor hub, or embedded functions 
 * configuration registers.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] mem_bank : @li @c 0 - User memory,
 *                       @li @c 1 - Sensor hub,
 *                       @li @c 2 - Embedded functions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_set_mem_bank ( smartdof5_t *ctx, uint8_t mem_bank );

/**
 * @brief Smart DOF 5 sw reset function.
 * @details This function restores the default values in user memory registers.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_sw_reset ( smartdof5_t *ctx );

/**
 * @brief Smart DOF 5 set accel odr function.
 * @details This function sets the accel measurement output data rate.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] odr : @li @c 0 - OFF,
 *                  @li @c 1 - 12.5Hz,
 *                  @li @c 2 - 26Hz,
 *                  @li @c 3 - 52Hz,
 *                  @li @c 4 - 104Hz,
 *                  @li @c 5 - 208Hz,
 *                  @li @c 6 - 416Hz,
 *                  @li @c 7 - 833Hz,
 *                  @li @c 8 - 1667Hz,
 *                  @li @c 9 - 3333Hz,
 *                  @li @c 10 - 6667Hz,
 *                  @li @c 11 - 1.6Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_set_accel_odr ( smartdof5_t *ctx, uint8_t odr );

/**
 * @brief Smart DOF 5 set gyro odr function.
 * @details This function sets the gyro measurement output data rate.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] odr : @li @c 0 - OFF,
 *                  @li @c 1 - 12.5Hz,
 *                  @li @c 2 - 26Hz,
 *                  @li @c 3 - 52Hz,
 *                  @li @c 4 - 104Hz,
 *                  @li @c 5 - 208Hz,
 *                  @li @c 6 - 416Hz,
 *                  @li @c 7 - 833Hz,
 *                  @li @c 8 - 1667Hz,
 *                  @li @c 9 - 3333Hz,
 *                  @li @c 10 - 6667Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_set_gyro_odr ( smartdof5_t *ctx, uint8_t odr );

/**
 * @brief Smart DOF 5 set accel fsr function.
 * @details This function sets the accel measurement full scale range.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] fsr : @li @c 0 - 2G,
 *                  @li @c 1 - 4G,
 *                  @li @c 2 - 8G,
 *                  @li @c 3 - 16G.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_set_accel_fsr ( smartdof5_t *ctx, uint8_t fsr );

/**
 * @brief Smart DOF 5 set gyro fsr function.
 * @details This function sets the gyro measurement full scale range.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] fsr : @li @c 0 - 250DPS,
 *                  @li @c 1 - 500DPS,
 *                  @li @c 2 - 1000DPS,
 *                  @li @c 3 - 2000DPS,
 *                  @li @c 4 - 4000DPS,
 *                  @li @c 5 - 125DPS.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_set_gyro_fsr ( smartdof5_t *ctx, uint8_t fsr );

/**
 * @brief Smart DOF 5 get accel drdy function.
 * @details This function gets the accel new data available flag.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[out] drdy : @li @c 0 - no new data available,
 *                    @li @c 1 - new data available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_get_accel_drdy ( smartdof5_t *ctx, uint8_t *drdy );

/**
 * @brief Smart DOF 5 get gyro drdy function.
 * @details This function gets the gyro new data available flag.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[out] drdy : @li @c 0 - no new data available,
 *                    @li @c 1 - new data available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_get_gyro_drdy ( smartdof5_t *ctx, uint8_t *drdy );

/**
 * @brief Smart DOF 5 get temp drdy function.
 * @details This function gets the temperature new data available flag.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[out] drdy : @li @c 0 - no new data available,
 *                    @li @c 1 - new data available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_get_temp_drdy ( smartdof5_t *ctx, uint8_t *drdy );

/**
 * @brief Smart DOF 5 get accel function.
 * @details This function reads the accelerometer of X, Y, and Z axis relative to standard gravity (g).
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[out] accel : Output accelerometer data.
 * See #smartdof5_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_get_accel ( smartdof5_t *ctx, smartdof5_axes_t *accel );

/**
 * @brief Smart DOF 5 get gyro function.
 * @details This function reads the angular rate of X, Y, and Z axis in degrees per second (dps).
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[out] gyro : Output gyro data.
 * See #smartdof5_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_get_gyro ( smartdof5_t *ctx, smartdof5_axes_t *gyro );

/**
 * @brief Smart DOF 5 get temp function.
 * @details This function reads the temperature measurement in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[out] temp : Temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_get_temp ( smartdof5_t *ctx, float *temp );

/**
 * @brief Smart DOF 5 get data function.
 * @details This function reads the accelerometer, gyroscope, and temperature measurement data.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[out] data_out : Output data structure read.
 * See #smartdof5_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartdof5_get_data ( smartdof5_t *ctx, smartdof5_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // SMARTDOF5_H

/*! @} */ // smartdof5

// ------------------------------------------------------------------------ END
