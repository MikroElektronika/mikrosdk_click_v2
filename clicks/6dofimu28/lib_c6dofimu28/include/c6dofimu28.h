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
 * @file c6dofimu28.h
 * @brief This file contains API for 6DOF IMU 28 Click Driver.
 */

#ifndef C6DOFIMU28_H
#define C6DOFIMU28_H

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
 * @addtogroup c6dofimu28 6DOF IMU 28 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 28 Click driver.
 * @{
 */

/**
 * @defgroup c6dofimu28_reg 6DOF IMU 28 Registers List
 * @brief List of registers of 6DOF IMU 28 Click driver.
 */

/**
 * @addtogroup c6dofimu28_reg
 * @{
 */

/**
 * @brief 6DOF IMU 28 user memory register list.
 * @details Specified user memory register list of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_REG_FUNC_CFG_ACCESS                  0x01
#define C6DOFIMU28_REG_PIN_CTRL                         0x02
#define C6DOFIMU28_REG_IF_CFG                           0x03
#define C6DOFIMU28_REG_ODR_TRIG_CFG                     0x06
#define C6DOFIMU28_REG_FIFO_CTRL1                       0x07
#define C6DOFIMU28_REG_FIFO_CTRL2                       0x08
#define C6DOFIMU28_REG_FIFO_CTRL3                       0x09
#define C6DOFIMU28_REG_FIFO_CTRL4                       0x0A
#define C6DOFIMU28_REG_COUNTER_BDR_1                    0x0B
#define C6DOFIMU28_REG_COUNTER_BDR_2                    0x0C
#define C6DOFIMU28_REG_INT1_CTRL                        0x0D
#define C6DOFIMU28_REG_INT2_CTRL                        0x0E
#define C6DOFIMU28_REG_WHO_AM_I                         0x0F
#define C6DOFIMU28_REG_CTRL1                            0x10
#define C6DOFIMU28_REG_CTRL2                            0x11
#define C6DOFIMU28_REG_CTRL3                            0x12
#define C6DOFIMU28_REG_CTRL4                            0x13
#define C6DOFIMU28_REG_CTRL5                            0x14
#define C6DOFIMU28_REG_CTRL6                            0x15
#define C6DOFIMU28_REG_CTRL7                            0x16
#define C6DOFIMU28_REG_CTRL8                            0x17
#define C6DOFIMU28_REG_CTRL9                            0x18
#define C6DOFIMU28_REG_CTRL10                           0x19
#define C6DOFIMU28_REG_CTRL_STATUS                      0x1A
#define C6DOFIMU28_REG_FIFO_STATUS1                     0x1B
#define C6DOFIMU28_REG_FIFO_STATUS2                     0x1C
#define C6DOFIMU28_REG_ALL_INT_SRC                      0x1D
#define C6DOFIMU28_REG_STATUS                           0x1E
#define C6DOFIMU28_REG_OUT_TEMP_L                       0x20
#define C6DOFIMU28_REG_OUT_TEMP_H                       0x21
#define C6DOFIMU28_REG_OUTX_L_G                         0x22
#define C6DOFIMU28_REG_OUTX_H_G                         0x23
#define C6DOFIMU28_REG_OUTY_L_G                         0x24
#define C6DOFIMU28_REG_OUTY_H_G                         0x25
#define C6DOFIMU28_REG_OUTZ_L_G                         0x26
#define C6DOFIMU28_REG_OUTZ_H_G                         0x27
#define C6DOFIMU28_REG_OUTX_L_A                         0x28
#define C6DOFIMU28_REG_OUTX_H_A                         0x29
#define C6DOFIMU28_REG_OUTY_L_A                         0x2A
#define C6DOFIMU28_REG_OUTY_H_A                         0x2B
#define C6DOFIMU28_REG_OUTZ_L_A                         0x2C
#define C6DOFIMU28_REG_OUTZ_H_A                         0x2D
#define C6DOFIMU28_REG_UI_OUTX_L_G_OIS_EIS              0x2E
#define C6DOFIMU28_REG_UI_OUTX_H_G_OIS_EIS              0x2F
#define C6DOFIMU28_REG_UI_OUTY_L_G_OIS_EIS              0x30
#define C6DOFIMU28_REG_UI_OUTY_H_G_OIS_EIS              0x31
#define C6DOFIMU28_REG_UI_OUTZ_L_G_OIS_EIS              0x32
#define C6DOFIMU28_REG_UI_OUTZ_H_G_OIS_EIS              0x33
#define C6DOFIMU28_REG_UI_OUTX_L_A_OIS_HG               0x34
#define C6DOFIMU28_REG_UI_OUTX_H_A_OIS_HG               0x35
#define C6DOFIMU28_REG_UI_OUTY_L_A_OIS_HG               0x36
#define C6DOFIMU28_REG_UI_OUTY_H_A_OIS_HG               0x37
#define C6DOFIMU28_REG_UI_OUTZ_L_A_OIS_HG               0x38
#define C6DOFIMU28_REG_UI_OUTZ_H_A_OIS_HG               0x39
#define C6DOFIMU28_REG_TIMESTAMP0                       0x40
#define C6DOFIMU28_REG_TIMESTAMP1                       0x41
#define C6DOFIMU28_REG_TIMESTAMP2                       0x42
#define C6DOFIMU28_REG_TIMESTAMP3                       0x43
#define C6DOFIMU28_REG_UI_STATUS_OIS                    0x44
#define C6DOFIMU28_REG_WAKE_UP_SRC                      0x45
#define C6DOFIMU28_REG_TAP_SRC                          0x46
#define C6DOFIMU28_REG_D6D_SRC                          0x47
#define C6DOFIMU28_REG_STATUS_CONTROLLER_MAINPAGE       0x48
#define C6DOFIMU28_REG_EMB_FUNC_STATUS_MAINPAGE         0x49
#define C6DOFIMU28_REG_FSM_STATUS_MAINPAGE              0x4A
#define C6DOFIMU28_REG_MLC_STATUS_MAINPAGE              0x4B
#define C6DOFIMU28_REG_HG_WAKE_UP_SRC                   0x4C
#define C6DOFIMU28_REG_CTRL2_XL_HG                      0x4D
#define C6DOFIMU28_REG_CTRL1_XL_HG                      0x4E
#define C6DOFIMU28_REG_INTERNAL_FREQ_FINE               0x4F
#define C6DOFIMU28_REG_FUNCTIONS_ENABLE                 0x50
#define C6DOFIMU28_REG_HG_FUNCTIONS_ENABLE              0x52
#define C6DOFIMU28_REG_HG_WAKE_UP_THS                   0x53
#define C6DOFIMU28_REG_INACTIVITY_DUR                   0x54
#define C6DOFIMU28_REG_INACTIVITY_THS                   0x55
#define C6DOFIMU28_REG_TAP_CFG0                         0x56
#define C6DOFIMU28_REG_TAP_CFG1                         0x57
#define C6DOFIMU28_REG_TAP_CFG2                         0x58
#define C6DOFIMU28_REG_TAP_THS_6D                       0x59
#define C6DOFIMU28_REG_TAP_DUR                          0x5A
#define C6DOFIMU28_REG_WAKE_UP_THS                      0x5B
#define C6DOFIMU28_REG_WAKE_UP_DUR                      0x5C
#define C6DOFIMU28_REG_FREE_FALL                        0x5D
#define C6DOFIMU28_REG_MD1_CFG                          0x5E
#define C6DOFIMU28_REG_MD2_CFG                          0x5F
#define C6DOFIMU28_REG_HAODR_CFG                        0x62
#define C6DOFIMU28_REG_EMB_FUNC_CFG                     0x63
#define C6DOFIMU28_REG_UI_HANDSHAKE_CTRL                0x64
#define C6DOFIMU28_REG_UI_IF2_SHARED_0                  0x65
#define C6DOFIMU28_REG_UI_IF2_SHARED_1                  0x66
#define C6DOFIMU28_REG_UI_IF2_SHARED_2                  0x67
#define C6DOFIMU28_REG_UI_IF2_SHARED_3                  0x68
#define C6DOFIMU28_REG_UI_IF2_SHARED_4                  0x69
#define C6DOFIMU28_REG_UI_IF2_SHARED_5                  0x6A
#define C6DOFIMU28_REG_CTRL_EIS                         0x6B
#define C6DOFIMU28_REG_XL_HG_X_OFS_USR                  0x6C
#define C6DOFIMU28_REG_XL_HG_Y_OFS_USR                  0x6D
#define C6DOFIMU28_REG_XL_HG_Z_OFS_USR                  0x6E
#define C6DOFIMU28_REG_UI_INT_OIS                       0x6F
#define C6DOFIMU28_REG_UI_CTRL1_OIS                     0x70
#define C6DOFIMU28_REG_UI_CTRL2_OIS                     0x71
#define C6DOFIMU28_REG_UI_CTRL3_OIS                     0x72
#define C6DOFIMU28_REG_X_OFS_USR                        0x73
#define C6DOFIMU28_REG_Y_OFS_USR                        0x74
#define C6DOFIMU28_REG_Z_OFS_USR                        0x75
#define C6DOFIMU28_REG_FIFO_DATA_OUT_TAG                0x78
#define C6DOFIMU28_REG_FIFO_DATA_OUT_BYTE_0             0x79
#define C6DOFIMU28_REG_FIFO_DATA_OUT_BYTE_1             0x7A
#define C6DOFIMU28_REG_FIFO_DATA_OUT_BYTE_2             0x7B
#define C6DOFIMU28_REG_FIFO_DATA_OUT_BYTE_3             0x7C
#define C6DOFIMU28_REG_FIFO_DATA_OUT_BYTE_4             0x7D
#define C6DOFIMU28_REG_FIFO_DATA_OUT_BYTE_5             0x7E

/**
 * @brief 6DOF IMU 28 sensor hub register list.
 * @details Specified sensor hub register list of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_1                0x02
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_2                0x03
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_3                0x04
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_4                0x05
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_5                0x06
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_6                0x07
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_7                0x08
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_8                0x09
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_9                0x0A
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_10               0x0B
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_11               0x0C
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_12               0x0D
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_13               0x0E
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_14               0x0F
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_15               0x10
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_16               0x11
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_17               0x12
#define C6DOFIMU28_REG_SHUB_SENSOR_HUB_18               0x13
#define C6DOFIMU28_REG_SHUB_CONTROLLER_CONFIG           0x14
#define C6DOFIMU28_REG_SHUB_TGT0_ADD                    0x15
#define C6DOFIMU28_REG_SHUB_TGT0_SUBADD                 0x16
#define C6DOFIMU28_REG_SHUB_TGT0_CONFIG                 0x17
#define C6DOFIMU28_REG_SHUB_TGT1_ADD                    0x18
#define C6DOFIMU28_REG_SHUB_TGT1_SUBADD                 0x19
#define C6DOFIMU28_REG_SHUB_TGT1_CONFIG                 0x1A
#define C6DOFIMU28_REG_SHUB_TGT2_ADD                    0x1B
#define C6DOFIMU28_REG_SHUB_TGT2_SUBADD                 0x1C
#define C6DOFIMU28_REG_SHUB_TGT2_CONFIG                 0x1D
#define C6DOFIMU28_REG_SHUB_TGT3_ADD                    0x1E
#define C6DOFIMU28_REG_SHUB_TGT3_SUBADD                 0x1F
#define C6DOFIMU28_REG_SHUB_TGT3_CONFIG                 0x20
#define C6DOFIMU28_REG_SHUB_DATAWRITE_TGT0              0x21
#define C6DOFIMU28_REG_SHUB_STATUS_CONTROLLER           0x22

/**
 * @brief 6DOF IMU 28 embedded functions register list.
 * @details Specified embedded functions register list of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_REG_EMBF_PAGE_SEL                    0x02
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_EN_A               0x04
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_EN_B               0x05
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_EXEC_STATUS        0x07
#define C6DOFIMU28_REG_EMBF_PAGE_ADDRESS                0x08
#define C6DOFIMU28_REG_EMBF_PAGE_VALUE                  0x09
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_INT1               0x0A
#define C6DOFIMU28_REG_EMBF_FSM_INT1                    0x0B
#define C6DOFIMU28_REG_EMBF_MLC_INT1                    0x0D
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_INT2               0x0E
#define C6DOFIMU28_REG_EMBF_FSM_INT2                    0x0F
#define C6DOFIMU28_REG_EMBF_MLC_INT2                    0x11
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_STATUS             0x12
#define C6DOFIMU28_REG_EMBF_FSM_STATUS                  0x13
#define C6DOFIMU28_REG_EMBF_MLC_STATUS                  0x15
#define C6DOFIMU28_REG_EMBF_PAGE_RW                     0x17
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASX_L               0x18
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASX_H               0x19
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASY_L               0x1A
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASY_H               0x1B
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASZ_L               0x1C
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASZ_H               0x1D
#define C6DOFIMU28_REG_EMBF_SFLP_GRAVX_L                0x1E
#define C6DOFIMU28_REG_EMBF_SFLP_GRAVX_H                0x1F
#define C6DOFIMU28_REG_EMBF_SFLP_GRAVY_L                0x20
#define C6DOFIMU28_REG_EMBF_SFLP_GRAVY_H                0x21
#define C6DOFIMU28_REG_EMBF_SFLP_GRAVZ_L                0x22
#define C6DOFIMU28_REG_EMBF_SFLP_GRAVZ_H                0x23
#define C6DOFIMU28_REG_EMBF_SFLP_QUATW_L                0x2A
#define C6DOFIMU28_REG_EMBF_SFLP_QUATW_H                0x2B
#define C6DOFIMU28_REG_EMBF_SFLP_QUATX_L                0x2C
#define C6DOFIMU28_REG_EMBF_SFLP_QUATX_H                0x2D
#define C6DOFIMU28_REG_EMBF_SFLP_QUATY_L                0x2E
#define C6DOFIMU28_REG_EMBF_SFLP_QUATY_H                0x2F
#define C6DOFIMU28_REG_EMBF_SFLP_QUATZ_L                0x30
#define C6DOFIMU28_REG_EMBF_SFLP_QUATZ_H                0x31
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASX_INIT_L          0x32
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASX_INIT_H          0x33
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASY_INIT_L          0x34
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASY_INIT_H          0x35
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASZ_INIT_L          0x36
#define C6DOFIMU28_REG_EMBF_SFLP_GBIASZ_INIT_H          0x37
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_FIFO_EN_A          0x44
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_FIFO_EN_B          0x45
#define C6DOFIMU28_REG_EMBF_FSM_ENABLE                  0x46
#define C6DOFIMU28_REG_EMBF_FSM_LONG_COUNTER_L          0x48
#define C6DOFIMU28_REG_EMBF_FSM_LONG_COUNTER_H          0x49
#define C6DOFIMU28_REG_EMBF_INT_ACK_MASK                0x4B
#define C6DOFIMU28_REG_EMBF_FSM_OUTS1                   0x4C
#define C6DOFIMU28_REG_EMBF_FSM_OUTS2                   0x4D
#define C6DOFIMU28_REG_EMBF_FSM_OUTS3                   0x4E
#define C6DOFIMU28_REG_EMBF_FSM_OUTS4                   0x4F
#define C6DOFIMU28_REG_EMBF_FSM_OUTS5                   0x50
#define C6DOFIMU28_REG_EMBF_FSM_OUTS6                   0x51
#define C6DOFIMU28_REG_EMBF_FSM_OUTS7                   0x52
#define C6DOFIMU28_REG_EMBF_FSM_OUTS8                   0x53
#define C6DOFIMU28_REG_EMBF_SFLP_ODR                    0x5E
#define C6DOFIMU28_REG_EMBF_FSM_ODR                     0x5F
#define C6DOFIMU28_REG_EMBF_MLC_ODR                     0x60
#define C6DOFIMU28_REG_EMBF_STEP_COUNTER_L              0x62
#define C6DOFIMU28_REG_EMBF_STEP_COUNTER_H              0x63
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_SRC                0x64
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_INIT_A             0x66
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_INIT_B             0x67
#define C6DOFIMU28_REG_EMBF_EMB_FUNC_SENSOR_CONV_EN     0x6E
#define C6DOFIMU28_REG_EMBF_MLC1_SRC                    0x70
#define C6DOFIMU28_REG_EMBF_MLC2_SRC                    0x71
#define C6DOFIMU28_REG_EMBF_MLC3_SRC                    0x72
#define C6DOFIMU28_REG_EMBF_MLC4_SRC                    0x73
#define C6DOFIMU28_REG_EMBF_MLC5_SRC                    0x74
#define C6DOFIMU28_REG_EMBF_MLC6_SRC                    0x75
#define C6DOFIMU28_REG_EMBF_MLC7_SRC                    0x76
#define C6DOFIMU28_REG_EMBF_MLC8_SRC                    0x77

/**
 * @brief 6DOF IMU 28 embedded advanced features register list.
 * @details Specified embedded advanced features register list of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_SENSITIVITY_L     0xBA
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_SENSITIVITY_H     0xBB
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_OFFX_L            0xC0
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_OFFX_H            0xC1
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_OFFY_L            0xC2
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_OFFY_H            0xC3
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_OFFZ_L            0xC4
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_OFFZ_H            0xC5
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_XX_L       0xC6
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_XX_H       0xC7
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_XY_L       0xC8
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_XY_H       0xC9
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_XZ_L       0xCA
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_XZ_H       0xCB
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_YY_L       0xCC
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_YY_H       0xCD
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_YZ_L       0xCE
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_YZ_H       0xCF
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_ZZ_L       0xD0
#define C6DOFIMU28_REG_EMBAF0_FSM_EXT_MATRIX_ZZ_H       0xD1
#define C6DOFIMU28_REG_EMBAF0_EXT_CFG_A                 0xD4
#define C6DOFIMU28_REG_EMBAF0_EXT_CFG_B                 0xD5
#define C6DOFIMU28_REG_EMBAF1_XL_HG_SENSITIVITY_L       0x58
#define C6DOFIMU28_REG_EMBAF1_XL_HG_SENSITIVITY_H       0x59
#define C6DOFIMU28_REG_EMBAF1_FSM_LC_TIMEOUT_L          0x7A
#define C6DOFIMU28_REG_EMBAF1_FSM_LC_TIMEOUT_H          0x7B
#define C6DOFIMU28_REG_EMBAF1_FSM_PROGRAMS              0x7C
#define C6DOFIMU28_REG_EMBAF1_FSM_START_ADD_L           0x7E
#define C6DOFIMU28_REG_EMBAF1_FSM_START_ADD_H           0x7F
#define C6DOFIMU28_REG_EMBAF1_PEDO_CMD                  0x83
#define C6DOFIMU28_REG_EMBAF1_PEDO_DEB_STEPS_CONF       0x84
#define C6DOFIMU28_REG_EMBAF1_PEDO_SC_DELTAT_L          0xD0
#define C6DOFIMU28_REG_EMBAF1_PEDO_SC_DELTAT_H          0xD1
#define C6DOFIMU28_REG_EMBAF1_MLC_EXT_SENSITIVITY_L     0xE8
#define C6DOFIMU28_REG_EMBAF1_MLC_EXT_SENSITIVITY_H     0xE9
#define C6DOFIMU28_REG_EMBAF2_EXT_FORMAT                0x00
#define C6DOFIMU28_REG_EMBAF2_EXT_3BYTE_SENSITIVITY_L   0x02
#define C6DOFIMU28_REG_EMBAF2_EXT_3BYTE_SENSITIVITY_H   0x03
#define C6DOFIMU28_REG_EMBAF2_EXT_3BYTE_OFFSET_XL       0x06
#define C6DOFIMU28_REG_EMBAF2_EXT_3BYTE_OFFSET_L        0x07
#define C6DOFIMU28_REG_EMBAF2_EXT_3BYTE_OFFSET_H        0x08

/*! @} */ // c6dofimu28_reg

/**
 * @defgroup c6dofimu28_set 6DOF IMU 28 Registers Settings
 * @brief Settings for registers of 6DOF IMU 28 Click driver.
 */

/**
 * @addtogroup c6dofimu28_set
 * @{
 */

/**
 * @brief 6DOF IMU 28 FUNC_CFG_ACCESS register setting.
 * @details Specified setting for FUNC_CFG_ACCESS register of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_FUNC_CFG_ACCESS_EMBF_MASK            0x80
#define C6DOFIMU28_FUNC_CFG_ACCESS_SHUB_MASK            0x40
#define C6DOFIMU28_FUNC_CFG_ACCESS_FSM_WR_CTRL_EN       0x08
#define C6DOFIMU28_FUNC_CFG_ACCESS_SW_POR               0x04
#define C6DOFIMU28_FUNC_CFG_ACCESS_IF2_RESET            0x02
#define C6DOFIMU28_FUNC_CFG_ACCESS_OIS_CTRL_FROM_UI     0x01

/**
 * @brief 6DOF IMU 28 INT1_CTRL register setting.
 * @details Specified setting for INT1_CTRL register of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_INT1_CTRL_CNT_BDR                    0x40
#define C6DOFIMU28_INT1_CTRL_FIFO_FULL                  0x20
#define C6DOFIMU28_INT1_CTRL_FIFO_OVR                   0x10
#define C6DOFIMU28_INT1_CTRL_FIFO_TH                    0x08
#define C6DOFIMU28_INT1_CTRL_DRDY_G                     0x02
#define C6DOFIMU28_INT1_CTRL_DRDY_XL                    0x01

/**
 * @brief 6DOF IMU 28 WHO_AM_I register setting.
 * @details Specified setting for WHO_AM_I register of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_WHO_AM_I                             0x73

/**
 * @brief 6DOF IMU 28 CTRL1 register setting.
 * @details Specified setting for CTRL1 register of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_CTRL1_OP_MODE_XL_MASK                0x70
#define C6DOFIMU28_CTRL1_ODR_XL_MASK                    0x0F

/**
 * @brief 6DOF IMU 28 CTRL2 register setting.
 * @details Specified setting for CTRL2 register of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_CTRL2_OP_MODE_G_MASK                 0x70
#define C6DOFIMU28_CTRL2_ODR_G_MASK                     0x0F

/**
 * @brief 6DOF IMU 28 CTRL3 register setting.
 * @details Specified setting for CTRL3 register of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_CTRL3_BOOT                           0x80
#define C6DOFIMU28_CTRL3_BDU                            0x40
#define C6DOFIMU28_CTRL3_IF_INC                         0x04
#define C6DOFIMU28_CTRL3_SW_RESET                       0x01

/**
 * @brief 6DOF IMU 28 CTRL6 register setting.
 * @details Specified setting for CTRL6 register of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_CTRL6_LPF1_G_BW_MASK                 0x70
#define C6DOFIMU28_CTRL6_FS_G_250DPS                    0x01
#define C6DOFIMU28_CTRL6_FS_G_500DPS                    0x02
#define C6DOFIMU28_CTRL6_FS_G_1000DPS                   0x03
#define C6DOFIMU28_CTRL6_FS_G_2000DPS                   0x04
#define C6DOFIMU28_CTRL6_FS_G_4000DPS                   0x0C
#define C6DOFIMU28_CTRL6_FS_G_MASK                      0x0F

/**
 * @brief 6DOF IMU 28 CTRL8 register setting.
 * @details Specified setting for CTRL8 register of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_CTRL8_HP_LPF2_XL_BW_MASK             0xE0
#define C6DOFIMU28_CTRL8_FS_XL_MASK                     0x03

/**
 * @brief 6DOF IMU 28 STATUS register setting.
 * @details Specified setting for STATUS register of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_STATUS_TIMESTAMP_ENDCOUNT            0x80
#define C6DOFIMU28_STATUS_OIS_DRDY                      0x20
#define C6DOFIMU28_STATUS_GDA_EIS                       0x10
#define C6DOFIMU28_STATUS_XLHGDA                        0x08
#define C6DOFIMU28_STATUS_TDA                           0x04
#define C6DOFIMU28_STATUS_GDA                           0x02
#define C6DOFIMU28_STATUS_XLDA                          0x01

/**
 * @brief 6DOF IMU 28 memory bank setting.
 * @details Specified setting for memory bank of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_MEM_BANK_USER                        0
#define C6DOFIMU28_MEM_BANK_SENSOR_HUB                  1
#define C6DOFIMU28_MEM_BANK_EMBEDDED_FUNC               2

/**
 * @brief 6DOF IMU 28 accel output data rate setting.
 * @details Specified setting for accel output data rate of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_ACCEL_ODR_OFF                        0
#define C6DOFIMU28_ACCEL_ODR_1_875_HZ                   1
#define C6DOFIMU28_ACCEL_ODR_7_5_HZ                     2
#define C6DOFIMU28_ACCEL_ODR_15_HZ                      3
#define C6DOFIMU28_ACCEL_ODR_30_HZ                      4
#define C6DOFIMU28_ACCEL_ODR_60_HZ                      5
#define C6DOFIMU28_ACCEL_ODR_120_HZ                     6
#define C6DOFIMU28_ACCEL_ODR_240_HZ                     7
#define C6DOFIMU28_ACCEL_ODR_480_HZ                     8
#define C6DOFIMU28_ACCEL_ODR_960_HZ                     9
#define C6DOFIMU28_ACCEL_ODR_1920_HZ                    10
#define C6DOFIMU28_ACCEL_ODR_3840_HZ                    11
#define C6DOFIMU28_ACCEL_ODR_7680_HZ                    12

/**
 * @brief 6DOF IMU 28 accel full scale setting.
 * @details Specified setting for accel full scale of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_ACCEL_FS_2G                          0
#define C6DOFIMU28_ACCEL_FS_4G                          1
#define C6DOFIMU28_ACCEL_FS_8G                          2
#define C6DOFIMU28_ACCEL_FS_16G                         3

/**
 * @brief 6DOF IMU 28 gyro output data rate setting.
 * @details Specified setting for gyro output data rate of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_GYRO_ODR_OFF                         0
#define C6DOFIMU28_GYRO_ODR_7_5_HZ                      2
#define C6DOFIMU28_GYRO_ODR_15_HZ                       3
#define C6DOFIMU28_GYRO_ODR_30_HZ                       4
#define C6DOFIMU28_GYRO_ODR_60_HZ                       5
#define C6DOFIMU28_GYRO_ODR_120_HZ                      6
#define C6DOFIMU28_GYRO_ODR_240_HZ                      7
#define C6DOFIMU28_GYRO_ODR_480_HZ                      8
#define C6DOFIMU28_GYRO_ODR_960_HZ                      9
#define C6DOFIMU28_GYRO_ODR_1920_HZ                     10
#define C6DOFIMU28_GYRO_ODR_3840_HZ                     11
#define C6DOFIMU28_GYRO_ODR_7680_HZ                     12

/**
 * @brief 6DOF IMU 28 gyro full scale setting.
 * @details Specified setting for gyro full scale of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_GYRO_FS_250DPS                       1
#define C6DOFIMU28_GYRO_FS_500DPS                       2
#define C6DOFIMU28_GYRO_FS_1000DPS                      3
#define C6DOFIMU28_GYRO_FS_2000DPS                      4
#define C6DOFIMU28_GYRO_FS_4000DPS                      5

/**
 * @brief 6DOF IMU 28 sensitivity setting.
 * @details Specified setting for sensitivity of 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_ACCEL_SENS_G_PER_LSB                 0.000061
#define C6DOFIMU28_GYRO_SENS_DPS_PER_LSB                0.00875
#define C6DOFIMU28_TEMP_SENS_LSB_PER_C                  256.0
#define C6DOFIMU28_TEMP_OFFSET                          25.0

/**
 * @brief 6DOF IMU 28 device address setting.
 * @details Specified setting for device slave address selection of
 * 6DOF IMU 28 Click driver.
 */
#define C6DOFIMU28_DEVICE_ADDRESS_0                     0x6A
#define C6DOFIMU28_DEVICE_ADDRESS_1                     0x6B

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c6dofimu28_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C6DOFIMU28_SET_DATA_SAMPLE_EDGE                 SET_SPI_DATA_SAMPLE_EDGE
#define C6DOFIMU28_SET_DATA_SAMPLE_MIDDLE               SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c6dofimu28_set

/**
 * @defgroup c6dofimu28_map 6DOF IMU 28 MikroBUS Map
 * @brief MikroBUS pin mapping of 6DOF IMU 28 Click driver.
 */

/**
 * @addtogroup c6dofimu28_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 6DOF IMU 28 Click to the selected MikroBUS.
 */
#define C6DOFIMU28_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c6dofimu28_map
/*! @} */ // c6dofimu28

/**
 * @brief 6DOF IMU 28 Click driver selector.
 * @details Selects target driver interface of 6DOF IMU 28 Click driver.
 */
typedef enum
{
    C6DOFIMU28_DRV_SEL_SPI,         /**< SPI driver descriptor. */
    C6DOFIMU28_DRV_SEL_I2C          /**< I2C driver descriptor. */

} c6dofimu28_drv_t;

/**
 * @brief 6DOF IMU 28 Click driver interface.
 * @details Definition of driver interface of 6DOF IMU 28 Click driver.
 */
struct c6dofimu28_s;
typedef err_t ( *c6dofimu28_master_io_t )( struct c6dofimu28_s*, uint8_t, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief 6DOF IMU 28 Click context object.
 * @details Context object definition of 6DOF IMU 28 Click driver.
 */
typedef struct c6dofimu28_s
{
    digital_in_t int2;              /**< Interrupt 2 pin. */
    digital_in_t int1;              /**< Interrupt 1 pin. */

    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t      slave_address;     /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;       /**< Chip select pin descriptor (used for SPI driver). */
    c6dofimu28_drv_t drv_sel;       /**< Master driver interface selector. */

    c6dofimu28_master_io_t write_f; /**< Master write function. */
    c6dofimu28_master_io_t read_f;  /**< Master read function. */

    float gyro_sens;                /**< Gyro sensitivity setting. */
    float accel_sens;               /**< Accel sensitivity setting. */

} c6dofimu28_t;

/**
 * @brief 6DOF IMU 28 Click configuration object.
 * @details Configuration object definition of 6DOF IMU 28 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t int2;                /**< Interrupt 2 pin. */
    pin_name_t int1;                /**< Interrupt 1 pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    c6dofimu28_drv_t drv_sel;       /**< Master driver interface selector. */

} c6dofimu28_cfg_t;

/**
 * @brief 6DOF IMU 28 Click axes data structure.
 * @details Axes data object definition of 6DOF IMU 28 Click driver.
 */
typedef struct
{
    float x;                        /**< X axis. */
    float y;                        /**< Y axis. */
    float z;                        /**< Z axis. */

} c6dofimu28_axes_t;

/**
 * @brief 6DOF IMU 28 Click data structure.
 * @details Data object definition of 6DOF IMU 28 Click driver.
 */
typedef struct
{
    c6dofimu28_axes_t accel;        /**< Accel data. */
    c6dofimu28_axes_t gyro;         /**< Gyro data. */
    float temperature;              /**< Temperature data. */

} c6dofimu28_data_t;

/**
 * @brief 6DOF IMU 28 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C6DOFIMU28_OK = 0,
    C6DOFIMU28_ERROR = -1

} c6dofimu28_return_value_t;

/*!
 * @addtogroup c6dofimu28 6DOF IMU 28 Click Driver
 * @brief API for configuring and manipulating 6DOF IMU 28 Click driver.
 * @{
 */

/**
 * @brief 6DOF IMU 28 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu28_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c6dofimu28_cfg_setup ( c6dofimu28_cfg_t *cfg );

/**
 * @brief 6DOF IMU 28 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #c6dofimu28_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #c6dofimu28_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void c6dofimu28_drv_interface_sel ( c6dofimu28_cfg_t *cfg, c6dofimu28_drv_t drv_sel );

/**
 * @brief 6DOF IMU 28 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c6dofimu28_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_init ( c6dofimu28_t *ctx, c6dofimu28_cfg_t *cfg );

/**
 * @brief 6DOF IMU 28 default configuration function.
 * @details This function executes a default configuration of 6DOF IMU 28
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c6dofimu28_default_cfg ( c6dofimu28_t *ctx );

/**
 * @brief 6DOF IMU 28 write reg function.
 * @details This function writes a data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_write_reg ( c6dofimu28_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 6DOF IMU 28 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_write_regs ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 28 read reg function.
 * @details This function reads a data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_read_reg ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 6DOF IMU 28 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_read_regs ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 28 get int1 pin function.
 * @details This function returns the interrupt 1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c6dofimu28_get_int1_pin ( c6dofimu28_t *ctx );

/**
 * @brief 6DOF IMU 28 get int2 pin function.
 * @details This function returns the interrupt 2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c6dofimu28_get_int2_pin ( c6dofimu28_t *ctx );

/**
 * @brief 6DOF IMU 28 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_check_communication ( c6dofimu28_t *ctx );

/**
 * @brief 6DOF IMU 28 set mem bank function.
 * @details This function sets the memory bank to user memory, sensor hub, or embedded functions 
 * configuration registers.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] mem_bank : @li @c 0 - User memory,
 *                       @li @c 1 - Sensor hub,
 *                       @li @c 2 - Embedded functions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_set_mem_bank ( c6dofimu28_t *ctx, uint8_t mem_bank );

/**
 * @brief 6DOF IMU 28 sw reset function.
 * @details This function restores the default values in user memory registers.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_sw_reset ( c6dofimu28_t *ctx );

/**
 * @brief 6DOF IMU 28 set accel odr function.
 * @details This function sets the accel measurement output data rate.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] odr : @li @c 0 - OFF,
 *                  @li @c 1 - 1.875Hz,
 *                  @li @c 2 - 7.5Hz,
 *                  @li @c 3 - 15Hz,
 *                  @li @c 4 - 30Hz,
 *                  @li @c 5 - 60Hz,
 *                  @li @c 6 - 120Hz,
 *                  @li @c 7 - 240Hz,
 *                  @li @c 8 - 480Hz,
 *                  @li @c 9 - 960Hz,
 *                  @li @c 10 - 1920Hz,
 *                  @li @c 11 - 3840Hz,
 *                  @li @c 12 - 7680Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_set_accel_odr ( c6dofimu28_t *ctx, uint8_t odr );

/**
 * @brief 6DOF IMU 28 set gyro odr function.
 * @details This function sets the gyro measurement output data rate.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] odr : @li @c 0 - OFF,
 *                  @li @c 2 - 7.5Hz,
 *                  @li @c 3 - 15Hz,
 *                  @li @c 4 - 30Hz,
 *                  @li @c 5 - 60Hz,
 *                  @li @c 6 - 120Hz,
 *                  @li @c 7 - 240Hz,
 *                  @li @c 8 - 480Hz,
 *                  @li @c 9 - 960Hz,
 *                  @li @c 10 - 1920Hz,
 *                  @li @c 11 - 3840Hz,
 *                  @li @c 12 - 7680Hz.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_set_gyro_odr ( c6dofimu28_t *ctx, uint8_t odr );

/**
 * @brief 6DOF IMU 28 set accel fsr function.
 * @details This function sets the accel measurement full scale range.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] fsr : @li @c 0 - 2G,
 *                  @li @c 1 - 4G,
 *                  @li @c 2 - 8G,
 *                  @li @c 3 - 16G.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_set_accel_fsr ( c6dofimu28_t *ctx, uint8_t fsr );

/**
 * @brief 6DOF IMU 28 set gyro fsr function.
 * @details This function sets the gyro measurement full scale range.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] fsr : @li @c 1 - 250DPS,
 *                  @li @c 2 - 500DPS,
 *                  @li @c 3 - 1000DPS,
 *                  @li @c 4 - 2000DPS,
 *                  @li @c 5 - 4000DPS.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_set_gyro_fsr ( c6dofimu28_t *ctx, uint8_t fsr );

/**
 * @brief 6DOF IMU 28 get accel drdy function.
 * @details This function gets the accel new data available flag.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[out] drdy : @li @c 0 - no new data available,
 *                    @li @c 1 - new data available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_get_accel_drdy ( c6dofimu28_t *ctx, uint8_t *drdy );

/**
 * @brief 6DOF IMU 28 get gyro drdy function.
 * @details This function gets the gyro new data available flag.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[out] drdy : @li @c 0 - no new data available,
 *                    @li @c 1 - new data available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_get_gyro_drdy ( c6dofimu28_t *ctx, uint8_t *drdy );

/**
 * @brief 6DOF IMU 28 get temp drdy function.
 * @details This function gets the temperature new data available flag.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[out] drdy : @li @c 0 - no new data available,
 *                    @li @c 1 - new data available.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_get_temp_drdy ( c6dofimu28_t *ctx, uint8_t *drdy );

/**
 * @brief 6DOF IMU 28 get accel function.
 * @details This function reads the accelerometer of X, Y, and Z axis relative to standard gravity (g).
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[out] accel : Output accelerometer data.
 * See #c6dofimu28_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_get_accel ( c6dofimu28_t *ctx, c6dofimu28_axes_t *accel );

/**
 * @brief 6DOF IMU 28 get gyro function.
 * @details This function reads the angular rate of X, Y, and Z axis in degrees per second (dps).
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[out] gyro : Output gyro data.
 * See #c6dofimu28_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_get_gyro ( c6dofimu28_t *ctx, c6dofimu28_axes_t *gyro );

/**
 * @brief 6DOF IMU 28 get temp function.
 * @details This function reads the temperature measurement in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[out] temp : Temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_get_temp ( c6dofimu28_t *ctx, float *temp );

/**
 * @brief 6DOF IMU 28 get data function.
 * @details This function reads the accelerometer, gyroscope, and temperature measurement data.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[out] data_out : Output data structure read.
 * See #c6dofimu28_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c6dofimu28_get_data ( c6dofimu28_t *ctx, c6dofimu28_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // C6DOFIMU28_H

/*! @} */ // c6dofimu28

// ------------------------------------------------------------------------ END
