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
 * @file powerstep2.h
 * @brief This file contains API for Power Step 2 Click Driver.
 */

#ifndef POWERSTEP2_H
#define POWERSTEP2_H

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
 * @addtogroup powerstep2 Power Step 2 Click Driver
 * @brief API for configuring and manipulating Power Step 2 Click driver.
 * @{
 */

/**
 * @defgroup powerstep2_reg Power Step 2 Registers List
 * @brief List of registers of Power Step 2 Click driver.
 */

/**
 * @addtogroup powerstep2_reg
 * @{
 */

/**
 * @brief Power Step 2 commands list.
 * @details Specified commands list of Power Step 2 Click driver.
 */
#define POWERSTEP2_CMD_NOP                              0x00
#define POWERSTEP2_CMD_SET_PARAM                        0x00
#define POWERSTEP2_CMD_GET_PARAM                        0x20
#define POWERSTEP2_CMD_RUN                              0x50
#define POWERSTEP2_CMD_STEP_CLOCK                       0x58
#define POWERSTEP2_CMD_MOVE                             0x40
#define POWERSTEP2_CMD_GO_TO                            0x60
#define POWERSTEP2_CMD_GO_TO_DIR                        0x68
#define POWERSTEP2_CMD_GO_UNTIL                         0x82
#define POWERSTEP2_CMD_RELEASE_SW                       0x92
#define POWERSTEP2_CMD_GO_HOME                          0x70
#define POWERSTEP2_CMD_GO_MARK                          0x78
#define POWERSTEP2_CMD_RESET_POS                        0xD8
#define POWERSTEP2_CMD_RESET_DEVICE                     0xC0
#define POWERSTEP2_CMD_SOFT_STOP                        0xB0
#define POWERSTEP2_CMD_HARD_STOP                        0xB8
#define POWERSTEP2_CMD_SOFT_HIZ                         0xA0
#define POWERSTEP2_CMD_HARD_HIZ                         0xA8
#define POWERSTEP2_CMD_GET_STATUS                       0xD0

/**
 * @brief Power Step 2 parameter register list.
 * @details Specified parameter register list of Power Step 2 Click driver.
 */
#define POWERSTEP2_PARAM_GEN_ABS_POS                    0x01
#define POWERSTEP2_PARAM_GEN_EL_POS                     0x02
#define POWERSTEP2_PARAM_GEN_MARK                       0x03
#define POWERSTEP2_PARAM_GEN_SPEED                      0x04
#define POWERSTEP2_PARAM_GEN_ACC                        0x05
#define POWERSTEP2_PARAM_GEN_DEC                        0x06
#define POWERSTEP2_PARAM_GEN_MAX_SPEED                  0x07
#define POWERSTEP2_PARAM_GEN_MIN_SPEED                  0x08
#define POWERSTEP2_PARAM_V_KVAL_HOLD                    0x09
#define POWERSTEP2_PARAM_C_TVAL_HOLD                    0x09
#define POWERSTEP2_PARAM_V_KVAL_RUN                     0x0A
#define POWERSTEP2_PARAM_C_TVAL_RUN                     0x0A
#define POWERSTEP2_PARAM_V_KVAL_ACC                     0x0B
#define POWERSTEP2_PARAM_C_TVAL_ACC                     0x0B
#define POWERSTEP2_PARAM_V_KVAL_DEC                     0x0C
#define POWERSTEP2_PARAM_C_TVAL_DEC                     0x0C
#define POWERSTEP2_PARAM_V_INT_SPEED                    0x0D
#define POWERSTEP2_PARAM_V_ST_SLP                       0x0E
#define POWERSTEP2_PARAM_C_T_FAST                       0x0E
#define POWERSTEP2_PARAM_V_FN_SLP_ACC                   0x0F
#define POWERSTEP2_PARAM_C_TON_MIN                      0x0F
#define POWERSTEP2_PARAM_V_FN_SLP_DEC                   0x10
#define POWERSTEP2_PARAM_C_TOFF_MIN                     0x10
#define POWERSTEP2_PARAM_V_K_THERM                      0x11
#define POWERSTEP2_PARAM_GEN_ADC_OUT                    0x12
#define POWERSTEP2_PARAM_GEN_OCD_TH                     0x13
#define POWERSTEP2_PARAM_V_STALL_TH                     0x14
#define POWERSTEP2_PARAM_GEN_FS_SPD                     0x15
#define POWERSTEP2_PARAM_GEN_STEP_MODE                  0x16
#define POWERSTEP2_PARAM_GEN_ALARM_EN                   0x17
#define POWERSTEP2_PARAM_GEN_GATECFG1                   0x18
#define POWERSTEP2_PARAM_GEN_GATECFG2                   0x19
#define POWERSTEP2_PARAM_V_CONFIG                       0x1A
#define POWERSTEP2_PARAM_C_CONFIG                       0x1A
#define POWERSTEP2_PARAM_GEN_STATUS                     0x1B

/*! @} */ // powerstep2_reg

/**
 * @defgroup powerstep2_set Power Step 2 Registers Settings
 * @brief Settings for registers of Power Step 2 Click driver.
 */

/**
 * @addtogroup powerstep2_set
 * @{
 */

/**
 * @brief Power Step 2 parameter register settings.
 * @details Specified parameter register settings of Power Step 2 Click driver.
 */
#define POWERSTEP2_GEN_ABS_POS_HOME                     0x000000ul
#define POWERSTEP2_GEN_ABS_POS_MASK                     0x3FFFFFul
#define POWERSTEP2_GEN_EL_POS_STEP_ZERO                 0x0000
#define POWERSTEP2_GEN_EL_POS_STEP_MASK                 0x0180
#define POWERSTEP2_GEN_EL_POS_MICROSTEP_ZERO            0x0000
#define POWERSTEP2_GEN_EL_POS_MICROSTEP_MASK            0x007F
#define POWERSTEP2_GEN_EL_POS_MASK                      0x01FF
#define POWERSTEP2_GEN_MARK_ZERO                        0x000000ul
#define POWERSTEP2_GEN_MARK_MASK                        0x3FFFFFul
#define POWERSTEP2_GEN_SPEED_MASK                       0x0FFFFFul
#define POWERSTEP2_GEN_ACC_14_55_STEP_S2                0x0001
#define POWERSTEP2_GEN_ACC_29_1_STEP_S2                 0x0002
#define POWERSTEP2_GEN_ACC_101_85_STEP_S2               0x0007
#define POWERSTEP2_GEN_ACC_1004_STEP_S2                 0x0045
#define POWERSTEP2_GEN_ACC_1004_STEP_S2                 0x0045
#define POWERSTEP2_GEN_ACC_2008_STEP_S2                 0x008A
#define POWERSTEP2_GEN_ACC_59575_541_STEP_S2            0x0FFF
#define POWERSTEP2_GEN_ACC_MASK                         0x0FFF
#define POWERSTEP2_GEN_DEC_14_55_STEP_S2                0x0001
#define POWERSTEP2_GEN_DEC_29_1_STEP_S2                 0x0002
#define POWERSTEP2_GEN_DEC_101_85_STEP_S2               0x0007
#define POWERSTEP2_GEN_DEC_1004_STEP_S2                 0x0045
#define POWERSTEP2_GEN_DEC_2008_STEP_S2                 0x008A
#define POWERSTEP2_GEN_DEC_59575_541_STEP_S2            0x0FFF
#define POWERSTEP2_GEN_DEC_MASK                         0x0FFF
#define POWERSTEP2_GEN_MAX_SPEED_15_25_STEP_S           0x0001
#define POWERSTEP2_GEN_MAX_SPEED_30_5_STEP_S            0x0002
#define POWERSTEP2_GEN_MAX_SPEED_305_STEP_S             0x0014
#define POWERSTEP2_GEN_MAX_SPEED_991_25_STEP_S          0x0041
#define POWERSTEP2_GEN_MAX_SPEED_15610_STEP_S           0x03FF
#define POWERSTEP2_GEN_MAX_SPEED_MASK                   0x03FF
#define POWERSTEP2_GEN_MIN_SPEED_LSPD_OPT_LOW           0x0000
#define POWERSTEP2_GEN_MIN_SPEED_LSPD_OPT_HIGH          0x1000
#define POWERSTEP2_GEN_MIN_SPEED_LSPD_OPT_MASK          0x1000
#define POWERSTEP2_GEN_MIN_SPEED_MIN_SPEED_0_STEP_S     0x0000
#define POWERSTEP2_GEN_MIN_SPEED_MIN_SPEED_0_238_STEP_S 0x0001
#define POWERSTEP2_GEN_MIN_SPEED_MIN_SPEED_0_476_STEP_S 0x0002
#define POWERSTEP2_GEN_MIN_SPEED_MIN_SPEED_2_38_STEP_S  0x000A
#define POWERSTEP2_GEN_MIN_SPEED_MIN_SPEED_976_3_STEP_S 0x0FFF
#define POWERSTEP2_GEN_MIN_SPEED_MIN_SPEED_MASK         0x0FFF
#define POWERSTEP2_GEN_MIN_SPEED_MASK                   0x1FFF
#define POWERSTEP2_GEN_ADC_OUT_MASK                     0x1F
#define POWERSTEP2_GEN_OCD_TH_31_25_MV                  0x00
#define POWERSTEP2_GEN_OCD_TH_62_5_MV                   0x01
#define POWERSTEP2_GEN_OCD_TH_93_75_MV                  0x02
#define POWERSTEP2_GEN_OCD_TH_281_25_MV                 0x08
#define POWERSTEP2_GEN_OCD_TH_531_25_MV                 0x10
#define POWERSTEP2_GEN_OCD_TH_1000_MV                   0x1F
#define POWERSTEP2_GEN_OCD_TH_MASK                      0x1F
#define POWERSTEP2_GEN_FS_SPD_BOOST_MODE_DISABLE        0x0000
#define POWERSTEP2_GEN_FS_SPD_BOOST_MODE_ENABLE         0x0400
#define POWERSTEP2_GEN_FS_SPD_BOOST_MODE_MASK           0x0400
#define POWERSTEP2_GEN_FS_SPD_FS_SPD_7_63_STEP_S        0x0000
#define POWERSTEP2_GEN_FS_SPD_FS_SPD_22_88_STEP_S       0x0001
#define POWERSTEP2_GEN_FS_SPD_FS_SPD_38_13_STEP_S       0x0002
#define POWERSTEP2_GEN_FS_SPD_FS_SPD_15617_STEP_S       0x03FF
#define POWERSTEP2_GEN_FS_SPD_FS_SPD_MASK               0x03FF
#define POWERSTEP2_GEN_FS_SPD_MASK                      0x07FF
#define POWERSTEP2_GEN_STEP_MODE_SYNC_EN_DISABLE        0x00
#define POWERSTEP2_GEN_STEP_MODE_SYNC_EN_ENABLE         0x80
#define POWERSTEP2_GEN_STEP_MODE_SYNC_EN_MASK           0x80
#define POWERSTEP2_GEN_STEP_MODE_SYNC_SEL_FULL_STEP     0x00
#define POWERSTEP2_GEN_STEP_MODE_SYNC_SEL_HALF_STEP     0x10
#define POWERSTEP2_GEN_STEP_MODE_SYNC_SEL_QUARTER_STEP  0x20
#define POWERSTEP2_GEN_STEP_MODE_SYNC_SEL_1_OVER_8      0x30
#define POWERSTEP2_GEN_STEP_MODE_SYNC_SEL_1_OVER_16     0x40
#define POWERSTEP2_GEN_STEP_MODE_SYNC_SEL_1_OVER_32     0x50
#define POWERSTEP2_GEN_STEP_MODE_SYNC_SEL_1_OVER_64     0x60
#define POWERSTEP2_GEN_STEP_MODE_SYNC_SEL_1_OVER_128    0x70
#define POWERSTEP2_GEN_STEP_MODE_SYNC_SEL_MASK          0x70
#define POWERSTEP2_GEN_STEP_MODE_CM_VM_VOLTAGE          0x00
#define POWERSTEP2_GEN_STEP_MODE_CM_VM_CURRENT          0x08
#define POWERSTEP2_GEN_STEP_MODE_CM_VM_MASK             0x08
#define POWERSTEP2_GEN_STEP_MODE_STEP_SEL_FULL_STEP     0x00
#define POWERSTEP2_GEN_STEP_MODE_STEP_SEL_HALF_STEP     0x01
#define POWERSTEP2_GEN_STEP_MODE_STEP_SEL_QUARTER_STEP  0x02
#define POWERSTEP2_GEN_STEP_MODE_STEP_SEL_1_OVER_8      0x03
#define POWERSTEP2_GEN_STEP_MODE_STEP_SEL_1_OVER_16     0x04
#define POWERSTEP2_GEN_STEP_MODE_STEP_SEL_1_OVER_32     0x05
#define POWERSTEP2_GEN_STEP_MODE_STEP_SEL_1_OVER_64     0x06
#define POWERSTEP2_GEN_STEP_MODE_STEP_SEL_1_OVER_128    0x07
#define POWERSTEP2_GEN_STEP_MODE_STEP_SEL_MASK          0x07
#define POWERSTEP2_GEN_STEP_MODE_MASK                   0xFF
#define POWERSTEP2_GEN_ALARM_EN_CMD_ERROR_MASK          0x80
#define POWERSTEP2_GEN_ALARM_EN_SW_ON_MASK              0x40
#define POWERSTEP2_GEN_ALARM_EN_STALL_DET_MASK          0x20
#define POWERSTEP2_GEN_ALARM_EN_ADC_UVLO_MASK           0x10
#define POWERSTEP2_GEN_ALARM_EN_UVLO_MASK               0x08
#define POWERSTEP2_GEN_ALARM_EN_THERMAL_WARN_MASK       0x04
#define POWERSTEP2_GEN_ALARM_EN_THERMAL_SD_MASK         0x02
#define POWERSTEP2_GEN_ALARM_EN_OVERCURRENT_MASK        0x01
#define POWERSTEP2_GEN_ALARM_EN_MASK                    0xFF
#define POWERSTEP2_GEN_GATECFG1_WD_EN_DISABLE           0x0000
#define POWERSTEP2_GEN_GATECFG1_WD_EN_ENABLE            0x0800
#define POWERSTEP2_GEN_GATECFG1_WD_EN_MASK              0x0800
#define POWERSTEP2_GEN_GATECFG1_TBOOST_0_NS             0x0000
#define POWERSTEP2_GEN_GATECFG1_TBOOST_62_5_NS          0x0100
#define POWERSTEP2_GEN_GATECFG1_TBOOST_1000_NS          0x0700
#define POWERSTEP2_GEN_GATECFG1_TBOOST_MASK             0x0700
#define POWERSTEP2_GEN_GATECFG1_IGATE_4_MA              0x0020
#define POWERSTEP2_GEN_GATECFG1_IGATE_8_MA              0x0040
#define POWERSTEP2_GEN_GATECFG1_IGATE_16_MA             0x0060
#define POWERSTEP2_GEN_GATECFG1_IGATE_24_MA             0x0080
#define POWERSTEP2_GEN_GATECFG1_IGATE_32_MA             0x00A0
#define POWERSTEP2_GEN_GATECFG1_IGATE_64_MA             0x00C0
#define POWERSTEP2_GEN_GATECFG1_IGATE_96_MA             0x00E0
#define POWERSTEP2_GEN_GATECFG1_IGATE_MASK              0x00E0
#define POWERSTEP2_GEN_GATECFG1_TCC_125_NS              0x0000
#define POWERSTEP2_GEN_GATECFG1_TCC_250_NS              0x0001
#define POWERSTEP2_GEN_GATECFG1_TCC_375_NS              0x0002
#define POWERSTEP2_GEN_GATECFG1_TCC_500_NS              0x0003
#define POWERSTEP2_GEN_GATECFG1_TCC_3750_NS             0x001D
#define POWERSTEP2_GEN_GATECFG1_TCC_MASK                0x001F
#define POWERSTEP2_GEN_GATECFG1_MASK                    0x0FFF
#define POWERSTEP2_GEN_GATECFG2_TBLANK_125_NS           0x00
#define POWERSTEP2_GEN_GATECFG2_TBLANK_250_NS           0x20
#define POWERSTEP2_GEN_GATECFG2_TBLANK_375_NS           0x40
#define POWERSTEP2_GEN_GATECFG2_TBLANK_1000_NS          0xE0
#define POWERSTEP2_GEN_GATECFG2_TBLANK_MASK             0xE0
#define POWERSTEP2_GEN_GATECFG2_TDT_125_NS              0x00
#define POWERSTEP2_GEN_GATECFG2_TDT_250_NS              0x01
#define POWERSTEP2_GEN_GATECFG2_TDT_4000_NS             0x1F
#define POWERSTEP2_GEN_GATECFG2_TDT_MASK                0x1F
#define POWERSTEP2_GEN_GATECFG2_MASK                    0xFF
#define POWERSTEP2_GEN_STATUS_STALL_A_MASK              0x8000
#define POWERSTEP2_GEN_STATUS_STALL_B_MASK              0x4000
#define POWERSTEP2_GEN_STATUS_OCD_MASK                  0x2000
#define POWERSTEP2_GEN_STATUS_TH_STATUS_MASK            0x1800
#define POWERSTEP2_GEN_STATUS_UVLO_ADC_MASK             0x0400
#define POWERSTEP2_GEN_STATUS_UVLO_MASK                 0x0200
#define POWERSTEP2_GEN_STATUS_STCK_MOD_MASK             0x0100
#define POWERSTEP2_GEN_STATUS_CMD_ERROR_MASK            0x0080
#define POWERSTEP2_GEN_STATUS_MOT_STATUS_MASK           0x0060
#define POWERSTEP2_GEN_STATUS_DIR_MASK                  0x0010
#define POWERSTEP2_GEN_STATUS_SW_EVN_MASK               0x0008
#define POWERSTEP2_GEN_STATUS_SW_F_MASK                 0x0004
#define POWERSTEP2_GEN_STATUS_BUSY_MASK                 0x0002
#define POWERSTEP2_GEN_STATUS_HIZ_MASK                  0x0001
#define POWERSTEP2_GEN_STATUS_MASK                      0xFFFF
#define POWERSTEP2_V_KVAL_HOLD_0_VS                     0x00
#define POWERSTEP2_V_KVAL_HOLD_0_004_VS                 0x01
#define POWERSTEP2_V_KVAL_HOLD_0_008_VS                 0x02
#define POWERSTEP2_V_KVAL_HOLD_0_104_VS                 0x19
#define POWERSTEP2_V_KVAL_HOLD_0_168_VS                 0x29
#define POWERSTEP2_V_KVAL_HOLD_0_996_VS                 0xFF
#define POWERSTEP2_V_KVAL_HOLD_MASK                     0xFF
#define POWERSTEP2_V_KVAL_RUN_0_VS                      0x00
#define POWERSTEP2_V_KVAL_RUN_0_004_VS                  0x01
#define POWERSTEP2_V_KVAL_RUN_0_008_VS                  0x02
#define POWERSTEP2_V_KVAL_RUN_0_104_VS                  0x19
#define POWERSTEP2_V_KVAL_RUN_0_168_VS                  0x29
#define POWERSTEP2_V_KVAL_RUN_0_996_VS                  0xFF
#define POWERSTEP2_V_KVAL_RUN_MASK                      0xFF
#define POWERSTEP2_V_KVAL_ACC_0_VS                      0x00
#define POWERSTEP2_V_KVAL_ACC_0_004_VS                  0x01
#define POWERSTEP2_V_KVAL_ACC_0_008_VS                  0x02
#define POWERSTEP2_V_KVAL_ACC_0_104_VS                  0x19
#define POWERSTEP2_V_KVAL_ACC_0_168_VS                  0x29
#define POWERSTEP2_V_KVAL_ACC_0_996_VS                  0xFF
#define POWERSTEP2_V_KVAL_ACC_MASK                      0xFF
#define POWERSTEP2_V_KVAL_DEC_0_VS                      0x00
#define POWERSTEP2_V_KVAL_DEC_0_004_VS                  0x01
#define POWERSTEP2_V_KVAL_DEC_0_008_VS                  0x02
#define POWERSTEP2_V_KVAL_DEC_0_104_VS                  0x19
#define POWERSTEP2_V_KVAL_DEC_0_168_VS                  0x29
#define POWERSTEP2_V_KVAL_DEC_0_996_VS                  0xFF
#define POWERSTEP2_V_KVAL_DEC_MASK                      0xFF
#define POWERSTEP2_V_INT_SPEED_0_STEP_S                 0x0000
#define POWERSTEP2_V_INT_SPEED_0_0596_STEP_S            0x0001
#define POWERSTEP2_V_INT_SPEED_0_1192_STEP_S            0x0002
#define POWERSTEP2_V_INT_SPEED_61_5668_STEP_S           0x0408
#define POWERSTEP2_V_INT_SPEED_976_5_STEP_S             0x3FFF
#define POWERSTEP2_V_INT_SPEED_MASK                     0x3FFF
#define POWERSTEP2_V_ST_SLP_0                           0x00
#define POWERSTEP2_V_ST_SLP_0_000015                    0x01
#define POWERSTEP2_V_ST_SLP_0_00003                     0x02
#define POWERSTEP2_V_ST_SLP_0_000135                    0x08
#define POWERSTEP2_V_ST_SLP_0_004                       0xFF
#define POWERSTEP2_V_ST_SLP_MASK                        0xFF
#define POWERSTEP2_V_FN_SLP_ACC_0                       0x00
#define POWERSTEP2_V_FN_SLP_ACC_0_000015                0x01
#define POWERSTEP2_V_FN_SLP_ACC_0_00003                 0x02
#define POWERSTEP2_V_FN_SLP_ACC_0_000135                0x08
#define POWERSTEP2_V_FN_SLP_ACC_0_00063                 0x29
#define POWERSTEP2_V_FN_SLP_ACC_0_004                   0xFF
#define POWERSTEP2_V_FN_SLP_ACC_MASK                    0xFF
#define POWERSTEP2_V_FN_SLP_DEC_0                       0x00
#define POWERSTEP2_V_FN_SLP_DEC_0_000015                0x01
#define POWERSTEP2_V_FN_SLP_DEC_0_00003                 0x02
#define POWERSTEP2_V_FN_SLP_DEC_0_000135                0x08
#define POWERSTEP2_V_FN_SLP_DEC_0_00063                 0x29
#define POWERSTEP2_V_FN_SLP_DEC_0_004                   0xFF
#define POWERSTEP2_V_FN_SLP_DEC_MASK                    0xFF
#define POWERSTEP2_V_K_THERM_1                          0x00
#define POWERSTEP2_V_K_THERM_1_03125                    0x01
#define POWERSTEP2_V_K_THERM_1_0625                     0x02
#define POWERSTEP2_V_K_THERM_1_46875                    0x0F
#define POWERSTEP2_V_K_THERM_MASK                       0x0F
#define POWERSTEP2_V_STALL_TH_31_25_MV                  0x00
#define POWERSTEP2_V_STALL_TH_62_5_MV                   0x01
#define POWERSTEP2_V_STALL_TH_93_75_MV                  0x02
#define POWERSTEP2_V_STALL_TH_281_25_MV                 0x08
#define POWERSTEP2_V_STALL_TH_531_25_MV                 0x10
#define POWERSTEP2_V_STALL_TH_1000_MV                   0x1F
#define POWERSTEP2_V_STALL_TH_MASK                      0x1F
#define POWERSTEP2_V_CONFIG_F_PWM_INT_19_5_KHZ          0x0000
#define POWERSTEP2_V_CONFIG_F_PWM_INT_31_3_KHZ          0x0000
#define POWERSTEP2_V_CONFIG_F_PWM_INT_62_5_KHZ          0x0000
#define POWERSTEP2_V_CONFIG_F_PWM_INT_MASK              0xE000
#define POWERSTEP2_V_CONFIG_F_PWM_DEC_19_5_KHZ          0x0000
#define POWERSTEP2_V_CONFIG_F_PWM_DEC_31_3_KHZ          0x0C00
#define POWERSTEP2_V_CONFIG_F_PWM_DEC_62_5_KHZ          0x1C00
#define POWERSTEP2_V_CONFIG_F_PWM_DEC_MASK              0x1C00
#define POWERSTEP2_V_CONFIG_VCCVAL_7_5_V                0x0000
#define POWERSTEP2_V_CONFIG_VCCVAL_15_V                 0x0200
#define POWERSTEP2_V_CONFIG_VCCVAL_MASK                 0x0200
#define POWERSTEP2_V_CONFIG_UVLOVAL_LOW                 0x0000
#define POWERSTEP2_V_CONFIG_UVLOVAL_HIGH                0x0100
#define POWERSTEP2_V_CONFIG_UVLOVAL_MASK                0x0100
#define POWERSTEP2_V_CONFIG_OC_SD_DISABLE               0x0000
#define POWERSTEP2_V_CONFIG_OC_SD_ENABLE                0x0080
#define POWERSTEP2_V_CONFIG_OC_SD_MASK                  0x0080
#define POWERSTEP2_V_CONFIG_EN_VSCOMP_DISABLE           0x0000
#define POWERSTEP2_V_CONFIG_EN_VSCOMP_ENABLE            0x0020
#define POWERSTEP2_V_CONFIG_EN_VSCOMP_MASK              0x0020
#define POWERSTEP2_V_CONFIG_SW_MODE_HARD_STOP_INT       0x0000
#define POWERSTEP2_V_CONFIG_SW_MODE_USER_DISPOSAL       0x0010
#define POWERSTEP2_V_CONFIG_SW_MODE_MASK                0x0010
#define POWERSTEP2_V_CONFIG_EXT_CLK_DISABLE             0x0000
#define POWERSTEP2_V_CONFIG_EXT_CLK_ENABLE              0x0008
#define POWERSTEP2_V_CONFIG_EXT_CLK_MASK                0x0008
#define POWERSTEP2_V_CONFIG_OSC_SEL_INT_16_MHZ          0x0000
#define POWERSTEP2_V_CONFIG_OSC_SEL_MASK                0x0007
#define POWERSTEP2_V_CONFIG_MASK                        0xFFFF
#define POWERSTEP2_C_TVAL_HOLD_7_8_MV                   0x00
#define POWERSTEP2_C_TVAL_HOLD_15_6_MV                  0x01
#define POWERSTEP2_C_TVAL_HOLD_202_8_MV                 0x19
#define POWERSTEP2_C_TVAL_HOLD_327_6_MV                 0x29
#define POWERSTEP2_C_TVAL_HOLD_1000_MV                  0x7F
#define POWERSTEP2_C_TVAL_HOLD_MASK                     0x7F
#define POWERSTEP2_C_TVAL_RUN_7_8_MV                    0x00
#define POWERSTEP2_C_TVAL_RUN_15_6_MV                   0x01
#define POWERSTEP2_C_TVAL_RUN_202_8_MV                  0x19
#define POWERSTEP2_C_TVAL_RUN_327_6_MV                  0x29
#define POWERSTEP2_C_TVAL_RUN_1000_MV                   0x7F
#define POWERSTEP2_C_TVAL_RUN_MASK                      0x7F
#define POWERSTEP2_C_TVAL_ACC_7_8_MV                    0x00
#define POWERSTEP2_C_TVAL_ACC_15_6_MV                   0x01
#define POWERSTEP2_C_TVAL_ACC_202_8_MV                  0x19
#define POWERSTEP2_C_TVAL_ACC_327_6_MV                  0x29
#define POWERSTEP2_C_TVAL_ACC_1000_MV                   0x7F
#define POWERSTEP2_C_TVAL_ACC_MASK                      0x7F
#define POWERSTEP2_C_TVAL_DEC_7_8_MV                    0x00
#define POWERSTEP2_C_TVAL_DEC_15_6_MV                   0x01
#define POWERSTEP2_C_TVAL_DEC_202_8_MV                  0x19
#define POWERSTEP2_C_TVAL_DEC_327_6_MV                  0x29
#define POWERSTEP2_C_TVAL_DEC_1000_MV                   0x7F
#define POWERSTEP2_C_TVAL_DEC_MASK                      0x7F
#define POWERSTEP2_C_T_FAST_TOFF_FAST_2_US              0x00
#define POWERSTEP2_C_T_FAST_TOFF_FAST_4_US              0x10
#define POWERSTEP2_C_T_FAST_TOFF_FAST_10_US             0x40
#define POWERSTEP2_C_T_FAST_TOFF_FAST_32_US             0xF0
#define POWERSTEP2_C_T_FAST_TOFF_FAST_MASK              0xF0
#define POWERSTEP2_C_T_FAST_FAST_STEP_2_US              0x00
#define POWERSTEP2_C_T_FAST_FAST_STEP_4_US              0x01
#define POWERSTEP2_C_T_FAST_FAST_STEP_10_US             0x04
#define POWERSTEP2_C_T_FAST_FAST_STEP_16_US             0x07
#define POWERSTEP2_C_T_FAST_FAST_STEP_32_US             0x0F
#define POWERSTEP2_C_T_FAST_FAST_STEP_MASK              0x0F
#define POWERSTEP2_C_T_FAST_MASK                        0xFF
#define POWERSTEP2_C_TON_MIN_0_5_US                     0x00
#define POWERSTEP2_C_TON_MIN_1_US                       0x01
#define POWERSTEP2_C_TON_MIN_2_5_US                     0x04
#define POWERSTEP2_C_TON_MIN_64_US                      0x7F
#define POWERSTEP2_C_TON_MIN_MASK                       0x7F
#define POWERSTEP2_C_TOFF_MIN_0_5_US                    0x00
#define POWERSTEP2_C_TOFF_MIN_1_US                      0x01
#define POWERSTEP2_C_TOFF_MIN_2_5_US                    0x04
#define POWERSTEP2_C_TOFF_MIN_21_US                     0x29
#define POWERSTEP2_C_TOFF_MIN_64_US                     0x7F
#define POWERSTEP2_C_TOFF_MIN_MASK                      0x7F
#define POWERSTEP2_C_CONFIG_PRED_EN_DISABLE             0x0000
#define POWERSTEP2_C_CONFIG_PRED_EN_ENABLE              0x8000
#define POWERSTEP2_C_CONFIG_PRED_EN_MASK                0x8000
#define POWERSTEP2_C_CONFIG_TSW_4_US                    0x0400
#define POWERSTEP2_C_CONFIG_TSW_8_US                    0x0800
#define POWERSTEP2_C_CONFIG_TSW_48_US                   0x3000
#define POWERSTEP2_C_CONFIG_TSW_124_US                  0x7C00
#define POWERSTEP2_C_CONFIG_TSW_MASK                    0x7C00
#define POWERSTEP2_C_CONFIG_VCCVAL_7_5_V                0x0000
#define POWERSTEP2_C_CONFIG_VCCVAL_15_V                 0x0200
#define POWERSTEP2_C_CONFIG_VCCVAL_MASK                 0x0200
#define POWERSTEP2_C_CONFIG_UVLOVAL_LOW                 0x0000
#define POWERSTEP2_C_CONFIG_UVLOVAL_HIGH                0x0100
#define POWERSTEP2_C_CONFIG_UVLOVAL_MASK                0x0100
#define POWERSTEP2_C_CONFIG_OC_SD_DISABLE               0x0000
#define POWERSTEP2_C_CONFIG_OC_SD_ENABLE                0x0080
#define POWERSTEP2_C_CONFIG_OC_SD_MASK                  0x0080
#define POWERSTEP2_C_CONFIG_EN_TQREG_DISABLE            0x0000
#define POWERSTEP2_C_CONFIG_EN_TQREG_ENABLE             0x0020
#define POWERSTEP2_C_CONFIG_EN_TQREG_MASK               0x0020
#define POWERSTEP2_C_CONFIG_SW_MODE_HARD_STOP_INT       0x0000
#define POWERSTEP2_C_CONFIG_SW_MODE_USER_DISPOSAL       0x0010
#define POWERSTEP2_C_CONFIG_SW_MODE_MASK                0x0010
#define POWERSTEP2_C_CONFIG_EXT_CLK_DISABLE             0x0000
#define POWERSTEP2_C_CONFIG_EXT_CLK_ENABLE              0x0008
#define POWERSTEP2_C_CONFIG_EXT_CLK_MASK                0x0008
#define POWERSTEP2_C_CONFIG_OSC_SEL_INT_16_MHZ          0x0000
#define POWERSTEP2_C_CONFIG_OSC_SEL_MASK                0x0007
#define POWERSTEP2_C_CONFIG_MASK                        0xFFFF

/**
 * @brief Power Step 2 parameter register default settings.
 * @details Specified parameter register default settings of Power Step 2 Click driver.
 */
#define POWERSTEP2_GEN_ABS_POS_DEF                      ( POWERSTEP2_GEN_ABS_POS_HOME )
#define POWERSTEP2_GEN_EL_POS_DEF                       ( POWERSTEP2_GEN_EL_POS_STEP_ZERO | \
                                                          POWERSTEP2_GEN_EL_POS_MICROSTEP_ZERO )
#define POWERSTEP2_GEN_MARK_DEF                         ( POWERSTEP2_GEN_MARK_ZERO )
#define POWERSTEP2_GEN_ACC_DEF                          ( POWERSTEP2_GEN_ACC_101_85_STEP_S2 )
#define POWERSTEP2_GEN_DEC_DEF                          ( POWERSTEP2_GEN_DEC_101_85_STEP_S2 )
#define POWERSTEP2_GEN_MAX_SPEED_DEF                    ( POWERSTEP2_GEN_MAX_SPEED_305_STEP_S )
#define POWERSTEP2_GEN_MIN_SPEED_DEF                    ( POWERSTEP2_GEN_MIN_SPEED_LSPD_OPT_LOW | \
                                                          POWERSTEP2_GEN_MIN_SPEED_MIN_SPEED_0_STEP_S )
#define POWERSTEP2_GEN_OCD_TH_DEF                       ( POWERSTEP2_GEN_OCD_TH_531_25_MV )
#define POWERSTEP2_GEN_FS_SPD_DEF                       ( POWERSTEP2_GEN_FS_SPD_BOOST_MODE_DISABLE | \
                                                          POWERSTEP2_GEN_FS_SPD_FS_SPD_15617_STEP_S )
#define POWERSTEP2_GEN_STEP_MODE_DEF                    ( POWERSTEP2_GEN_STEP_MODE_SYNC_EN_DISABLE | \
                                                          POWERSTEP2_GEN_STEP_MODE_SYNC_SEL_FULL_STEP | \
                                                          POWERSTEP2_GEN_STEP_MODE_CM_VM_VOLTAGE | \
                                                          POWERSTEP2_GEN_STEP_MODE_STEP_SEL_1_OVER_32 )
#define POWERSTEP2_GEN_ALARM_EN_DEF                     ( POWERSTEP2_GEN_ALARM_EN_CMD_ERROR_MASK | \
                                                          POWERSTEP2_GEN_ALARM_EN_SW_ON_MASK | \
                                                          POWERSTEP2_GEN_ALARM_EN_STALL_DET_MASK | \
                                                          POWERSTEP2_GEN_ALARM_EN_UVLO_MASK | \
                                                          POWERSTEP2_GEN_ALARM_EN_THERMAL_WARN_MASK | \
                                                          POWERSTEP2_GEN_ALARM_EN_THERMAL_SD_MASK | \
                                                          POWERSTEP2_GEN_ALARM_EN_OVERCURRENT_MASK )
#define POWERSTEP2_GEN_GATECFG1_DEF                     ( POWERSTEP2_GEN_GATECFG1_WD_EN_DISABLE | \
                                                          POWERSTEP2_GEN_GATECFG1_TBOOST_0_NS | \
                                                          POWERSTEP2_GEN_GATECFG1_IGATE_64_MA | \
                                                          POWERSTEP2_GEN_GATECFG1_TCC_500_NS )
#define POWERSTEP2_GEN_GATECFG2_DEF                     ( POWERSTEP2_GEN_GATECFG2_TBLANK_375_NS | \
                                                          POWERSTEP2_GEN_GATECFG2_TDT_125_NS )
#define POWERSTEP2_V_CONFIG_DEF                         ( POWERSTEP2_V_CONFIG_F_PWM_INT_62_5_KHZ | \
                                                          POWERSTEP2_V_CONFIG_F_PWM_DEC_62_5_KHZ | \
                                                          POWERSTEP2_V_CONFIG_VCCVAL_15_V | \
                                                          POWERSTEP2_V_CONFIG_UVLOVAL_LOW | \
                                                          POWERSTEP2_V_CONFIG_OC_SD_DISABLE | \
                                                          POWERSTEP2_V_CONFIG_EN_VSCOMP_DISABLE | \
                                                          POWERSTEP2_V_CONFIG_SW_MODE_HARD_STOP_INT | \
                                                          POWERSTEP2_V_CONFIG_EXT_CLK_DISABLE | \
                                                          POWERSTEP2_V_CONFIG_OSC_SEL_INT_16_MHZ )
#define POWERSTEP2_V_KVAL_HOLD_DEF                      ( POWERSTEP2_V_KVAL_HOLD_0_168_VS )
#define POWERSTEP2_V_KVAL_RUN_DEF                       ( POWERSTEP2_V_KVAL_RUN_0_168_VS )
#define POWERSTEP2_V_KVAL_ACC_DEF                       ( POWERSTEP2_V_KVAL_ACC_0_168_VS )
#define POWERSTEP2_V_KVAL_DEC_DEF                       ( POWERSTEP2_V_KVAL_DEC_0_168_VS )
#define POWERSTEP2_V_INT_SPEED_DEF                      ( POWERSTEP2_V_INT_SPEED_61_5668_STEP_S )
#define POWERSTEP2_V_ST_SLP_DEF                         ( POWERSTEP2_V_ST_SLP_0_000135 )
#define POWERSTEP2_V_FN_SLP_ACC_DEF                     ( POWERSTEP2_V_FN_SLP_ACC_0_00063 )
#define POWERSTEP2_V_FN_SLP_DEC_DEF                     ( POWERSTEP2_V_FN_SLP_DEC_0_00063 )
#define POWERSTEP2_V_K_THERM_DEF                        ( POWERSTEP2_V_K_THERM_1 )
#define POWERSTEP2_V_STALL_TH_DEF                       ( POWERSTEP2_V_STALL_TH_531_25_MV )
#define POWERSTEP2_C_CONFIG_DEF                         ( POWERSTEP2_C_CONFIG_PRED_EN_DISABLE | \
                                                          POWERSTEP2_C_CONFIG_TSW_48_US | \
                                                          POWERSTEP2_C_CONFIG_VCCVAL_15_V | \
                                                          POWERSTEP2_C_CONFIG_UVLOVAL_LOW | \
                                                          POWERSTEP2_C_CONFIG_OC_SD_ENABLE | \
                                                          POWERSTEP2_C_CONFIG_EN_TQREG_DISABLE | \
                                                          POWERSTEP2_C_CONFIG_SW_MODE_HARD_STOP_INT | \
                                                          POWERSTEP2_C_CONFIG_EXT_CLK_DISABLE | \
                                                          POWERSTEP2_C_CONFIG_OSC_SEL_INT_16_MHZ )
#define POWERSTEP2_C_TVAL_HOLD_DEF                      ( POWERSTEP2_C_TVAL_HOLD_327_6_MV )
#define POWERSTEP2_C_TVAL_RUN_DEF                       ( POWERSTEP2_C_TVAL_RUN_327_6_MV )
#define POWERSTEP2_C_TVAL_ACC_DEF                       ( POWERSTEP2_C_TVAL_ACC_327_6_MV )
#define POWERSTEP2_C_TVAL_DEC_DEF                       ( POWERSTEP2_C_TVAL_DEC_327_6_MV )
#define POWERSTEP2_C_T_FAST_DEF                         ( POWERSTEP2_C_T_FAST_TOFF_FAST_10_US | \
                                                          POWERSTEP2_C_T_FAST_FAST_STEP_16_US )
#define POWERSTEP2_C_TON_MIN_DEF                        ( POWERSTEP2_C_TON_MIN_2_5_US )
#define POWERSTEP2_C_TOFF_MIN_DEF                       ( POWERSTEP2_C_TOFF_MIN_21_US )

/**
 * @brief Power Step 2 control mode setting.
 * @details Specified setting for control mode of Power Step 2 Click driver.
 */
#define POWERSTEP2_CONTROL_MODE_VOLTAGE                 0
#define POWERSTEP2_CONTROL_MODE_CURRENT                 1

/**
 * @brief Power Step 2 step mode setting.
 * @details Specified setting for step mode of Power Step 2 Click driver.
 */
#define POWERSTEP2_STEP_MODE_FULL_STEP                  0
#define POWERSTEP2_STEP_MODE_HALF_STEP                  1
#define POWERSTEP2_STEP_MODE_QUARTER_STEP               2
#define POWERSTEP2_STEP_MODE_1_OVER_8                   3
#define POWERSTEP2_STEP_MODE_1_OVER_16                  4
#define POWERSTEP2_STEP_MODE_1_OVER_32                  5
#define POWERSTEP2_STEP_MODE_1_OVER_64                  6
#define POWERSTEP2_STEP_MODE_1_OVER_128                 7

/**
 * @brief Power Step 2 acceleration and deceleration settings.
 * @details Specified acceleration and deceleration settings in step/s2 of Power Step 2 Click driver.
 */
#define POWERSTEP2_ACCELERATION_STEP                    14.55f
#define POWERSTEP2_ACCELERATION_MIN                     14.55f
#define POWERSTEP2_ACCELERATION_MAX                     59575.541f
#define POWERSTEP2_DECELERATION_STEP                    14.55f
#define POWERSTEP2_DECELERATION_MIN                     14.55f
#define POWERSTEP2_DECELERATION_MAX                     59575.541f

/**
 * @brief Power Step 2 speed min and max settings.
 * @details Specified speed min and max settings in step/s of Power Step 2 Click driver.
 */
#define POWERSTEP2_MIN_SPEED_STEP                       0.238f
#define POWERSTEP2_MIN_SPEED_MIN                        0.0f
#define POWERSTEP2_MIN_SPEED_MAX                        976.3f
#define POWERSTEP2_MAX_SPEED_STEP                       15.25f
#define POWERSTEP2_MAX_SPEED_MIN                        15.25f
#define POWERSTEP2_MAX_SPEED_MAX                        15610.0f

/**
 * @brief Power Step 2 direction setting.
 * @details Specified setting for direction of Power Step 2 Click driver.
 */
#define POWERSTEP2_DIR_CW                               1
#define POWERSTEP2_DIR_CCW                              0

/**
 * @brief Power Step 2 pin logic level setting.
 * @details Specified setting for pin logic level of Power Step 2 Click driver.
 */
#define POWERSTEP2_PIN_LOW_LEVEL                        0
#define POWERSTEP2_PIN_HIGH_LEVEL                       1

/**
 * @brief Power Step 2 driving speed in step clock mode settings.
 * @details Specified setting for rotation speed in step clock mode.
 */
#define POWERSTEP2_SPEED_VERY_SLOW                      0
#define POWERSTEP2_SPEED_SLOW                           1
#define POWERSTEP2_SPEED_MEDIUM                         2
#define POWERSTEP2_SPEED_FAST                           3
#define POWERSTEP2_SPEED_VERY_FAST                      4

/**
 * @brief Power Step 2 round to upper int settings.
 * @details Specified round to upper int settings of Power Step 2 Click driver.
 */
#define POWERSTEP2_ROUND_TO_INT                         0.5f

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b powerstep2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define POWERSTEP2_SET_DATA_SAMPLE_EDGE                 SET_SPI_DATA_SAMPLE_EDGE
#define POWERSTEP2_SET_DATA_SAMPLE_MIDDLE               SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // powerstep2_set

/**
 * @defgroup powerstep2_map Power Step 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Power Step 2 Click driver.
 */

/**
 * @addtogroup powerstep2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Power Step 2 Click to the selected MikroBUS.
 */
#define POWERSTEP2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.busy = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flag = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // powerstep2_map
/*! @} */ // powerstep2

/**
 * @brief Power Step 2 Click context object.
 * @details Context object definition of Power Step 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (active low). */
    digital_out_t step;         /**< Step clock pin. */

    // Input pins
    digital_in_t busy;          /**< Busy pin indication (active low). */
    digital_in_t flag;          /**< Status flag pin (active low). */

    // Modules
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t chip_select;     /**< Chip select pin descriptor (used for SPI driver). */

    uint8_t step_mode;          /**< Step mode resolution. */
    uint8_t control_mode;       /**< Control mode setting. */

} powerstep2_t;

/**
 * @brief Power Step 2 Click configuration object.
 * @details Configuration object definition of Power Step 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t busy;            /**< Busy pin indication (active low). */
    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t step;            /**< Step clock pin. */
    pin_name_t flag;            /**< Status flag pin (active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} powerstep2_cfg_t;

/**
 * @brief Power Step 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    POWERSTEP2_OK = 0,
    POWERSTEP2_ERROR = -1

} powerstep2_return_value_t;

/*!
 * @addtogroup powerstep2 Power Step 2 Click Driver
 * @brief API for configuring and manipulating Power Step 2 Click driver.
 * @{
 */

/**
 * @brief Power Step 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #powerstep2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void powerstep2_cfg_setup ( powerstep2_cfg_t *cfg );

/**
 * @brief Power Step 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #powerstep2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powerstep2_init ( powerstep2_t *ctx, powerstep2_cfg_t *cfg );

/**
 * @brief Power Step 2 default configuration function.
 * @details This function executes a default configuration of Power Step 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t powerstep2_default_cfg ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 SPI transfer function.
 * @details This function performs an SPI transfer for the Power Step 2 device.
 * It sends and receives data using the SPI interface.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in,out] data_io : Pointer to the data buffer for sending and receiving data.
 * @param[in] len : Length of the data buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note The function waits for the busy pin to go low before each data transfer.
 */
err_t powerstep2_spi_transfer ( powerstep2_t *ctx, uint8_t *data_io, uint8_t len );

/**
 * @brief Power Step 2 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void powerstep2_set_rst_pin ( powerstep2_t *ctx, uint8_t state );

/**
 * @brief Power Step 2 set step pin function.
 * @details This function sets the STEP clock pin logic state.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void powerstep2_set_step_pin ( powerstep2_t *ctx, uint8_t state );

/**
 * @brief Power Step 2 get busy pin function.
 * @details This function returns the BUSY pin logic state.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t powerstep2_get_busy_pin ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 get flag pin function.
 * @details This function returns the FLAG pin logic state.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t powerstep2_get_flag_pin ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void powerstep2_hw_reset_device ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 set parameter function.
 * @details This function sets a specific parameter register of the Power Step 2 device.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] param : Parameter register to set.
 * @param[in] data_in : Data to write to the parameter.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_set_param ( powerstep2_t *ctx, uint8_t param, uint32_t data_in );

/**
 * @brief Power Step 2 get parameter function.
 * @details This function retrieves the value of a specific parameter register from the Power Step 2 device.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] param : Parameter register to read.
 * @param[out] data_out : Pointer to store the retrieved parameter value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_get_param ( powerstep2_t *ctx, uint8_t param, uint32_t *data_out );

/**
 * @brief Power Step 2 run motor function.
 * @details This function runs the motor in a specified direction at a given speed.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] dir : Direction of motor rotation.
 * @param[in] speed : Motor speed (20-bit value).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_run ( powerstep2_t *ctx, uint8_t dir, uint32_t speed );

/**
 * @brief Power Step 2 step clock function.
 * @details This function puts the device in step-clock mode and sets the direction.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] dir : Direction of the step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_step_clock ( powerstep2_t *ctx, uint8_t dir );

/**
 * @brief Power Step 2 move motor function.
 * @details This function moves the motor a specified number of steps in a given direction.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] dir : Direction of motor movement.
 * @param[in] n_step : Number of steps to move (22-bit value).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_move ( powerstep2_t *ctx, uint8_t dir, uint32_t n_step );

/**
 * @brief Power Step 2 go to position function.
 * @details This function moves the motor to an absolute position.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] abs_pos : Absolute position to move to (22-bit value).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_go_to ( powerstep2_t *ctx, uint32_t abs_pos );

/**
 * @brief Power Step 2 go to position with direction function.
 * @details This function moves the motor to an absolute position in a specified direction.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] dir : Direction of movement.
 * @param[in] abs_pos : Absolute position to move to (22-bit value).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_go_to_dir ( powerstep2_t *ctx, uint8_t dir, uint32_t abs_pos );

/**
 * @brief Power Step 2 go until function.
 * @details This function moves the motor until SW is closed.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] act : If 1, copies ABS_POS to MARK, else, reset ABS_POS.
 * @param[in] dir : Direction of movement.
 * @param[in] speed : Speed of movement (20-bit value).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_go_until ( powerstep2_t *ctx, uint8_t act, uint8_t dir, uint32_t speed );

/**
 * @brief Power Step 2 release switch function.
 * @details This function moves the motor at minimum speed until the SW is released.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] act : If 1, copies ABS_POS to MARK, else, reset ABS_POS.
 * @param[in] dir : Direction of movement.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_release_sw ( powerstep2_t *ctx, uint8_t act, uint8_t dir );

/**
 * @brief Power Step 2 go home function.
 * @details This function moves the motor to its home position.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_go_home ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 go mark function.
 * @details This function moves the motor to a marked position.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_go_mark ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 reset position function.
 * @details This function resets the ABS_POS register to zero.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_reset_pos ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 reset device function.
 * @details This function resets the Power Step 2 device.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_reset_device ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 soft stop function.
 * @details This function stops the motor gently using a soft stop.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_soft_stop ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 hard stop function.
 * @details This function stops the motor immediately using a hard stop.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_hard_stop ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 soft HiZ function.
 * @details This function sets the device to high-impedance mode softly (without abrupt stops).
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_soft_hiz ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 hard HiZ function.
 * @details This function sets the device to high-impedance mode abruptly.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_hard_hiz ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 get status function.
 * @details This function retrieves the status register of the Power Step 2 device.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[out] status : Pointer to store the status register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_get_status ( powerstep2_t *ctx, uint16_t *status );

/**
 * @brief Power Step 2 clear status function.
 * @details This function clears the status register by reading it.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_clear_status ( powerstep2_t *ctx );

/**
 * @brief Power Step 2 set control mode function.
 * @details This function sets the control mode of the device to either voltage mode or current mode.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] ctrl_mode : Control mode.
 *                      - 0 : Voltage mode.
 *                      - 1 : Current mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_set_control_mode ( powerstep2_t *ctx, uint8_t ctrl_mode );

/**
 * @brief Power Step 2 set step mode function.
 * @details This function sets the step mode (microstepping level) of the Power Step 2 device.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] step_mode : Step mode value (e.g., full-step, half-step, 1/4-step, etc.).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_set_step_mode ( powerstep2_t *ctx, uint8_t step_mode );

/**
 * @brief Power Step 2 set acceleration and deceleration function.
 * @details This function sets the acceleration and deceleration rates for motor movement.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] acc_step_s2 : Acceleration rate in steps per second squared.
 * @param[in] dec_step_s2 : Deceleration rate in steps per second squared.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_set_acc_dec ( powerstep2_t *ctx, float acc_step_s2, float dec_step_s2 );

/**
 * @brief Power Step 2 set speed function.
 * @details This function sets the minimum and maximum speeds for motor movement.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] min_speed : Minimum speed in steps per second.
 * @param[in] max_speed : Maximum speed in steps per second.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 */
err_t powerstep2_set_speed ( powerstep2_t *ctx, float min_speed, float max_speed );

/**
 * @brief Power Step 2 drive motor function.
 * @details This function drives the motor in step-clock mode for a specified number of steps at a given speed.
 * @param[in] ctx : Click context object.
 * See #powerstep2_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to move.
 * @param[in] speed : Speed of the motor movement.
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast.
 * @return None.
 */
void powerstep2_drive_motor ( powerstep2_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // POWERSTEP2_H

/*! @} */ // powerstep2

// ------------------------------------------------------------------------ END
