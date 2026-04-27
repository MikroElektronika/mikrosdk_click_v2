/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file bldcfoc.h
 * @brief This file contains API for BLDC FOC Click Driver.
 */

#ifndef BLDCFOC_H
#define BLDCFOC_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup bldcfoc BLDC FOC Click Driver
 * @brief API for configuring and manipulating BLDC FOC Click driver.
 * @{
 */

/**
 * @defgroup bldcfoc_reg BLDC FOC Registers List
 * @brief List of registers of BLDC FOC Click driver.
 */

/**
 * @addtogroup bldcfoc_reg
 * @{
 */

/**
 * @brief BLDC FOC EEPROM (Non-Volatile) Register Map.
 * @details Specified EEPROM (Non-Volatile) Register Map of BLDC FOC Click driver.
 */
#define BLDCFOC_EREG_ALG_CFG_ISD_CONFIG                 0x00080ul
#define BLDCFOC_EREG_ALG_CFG_REV_DRIVE_CONFIG           0x00082ul
#define BLDCFOC_EREG_ALG_CFG_MOTOR_STARTUP1             0x00084ul
#define BLDCFOC_EREG_ALG_CFG_MOTOR_STARTUP2             0x00086ul
#define BLDCFOC_EREG_ALG_CFG_CLOSED_LOOP1               0x00088ul
#define BLDCFOC_EREG_ALG_CFG_CLOSED_LOOP2               0x0008Aul
#define BLDCFOC_EREG_ALG_CFG_CLOSED_LOOP3               0x0008Cul
#define BLDCFOC_EREG_ALG_CFG_CLOSED_LOOP4               0x0008Eul
#define BLDCFOC_EREG_FAULT_CFG_FAULT_CONFIG1            0x00090ul
#define BLDCFOC_EREG_FAULT_CFG_FAULT_CONFIG2            0x00092ul
#define BLDCFOC_EREG_ALG_CFG_REF_PROFILES1              0x00094ul
#define BLDCFOC_EREG_ALG_CFG_REF_PROFILES2              0x00096ul
#define BLDCFOC_EREG_ALG_CFG_REF_PROFILES3              0x00098ul
#define BLDCFOC_EREG_ALG_CFG_REF_PROFILES4              0x0009Aul
#define BLDCFOC_EREG_ALG_CFG_REF_PROFILES5              0x0009Cul
#define BLDCFOC_EREG_ALG_CFG_REF_PROFILES6              0x0009Eul
#define BLDCFOC_EREG_INT_ALG_CFG_INT_ALGO_1             0x000A0ul
#define BLDCFOC_EREG_INT_ALG_CFG_INT_ALGO_2             0x000A2ul
#define BLDCFOC_EREG_HW_CFG_PIN_CONFIG                  0x000A4ul
#define BLDCFOC_EREG_HW_CFG_DEVICE_CONFIG1              0x000A6ul
#define BLDCFOC_EREG_HW_CFG_DEVICE_CONFIG2              0x000A8ul
#define BLDCFOC_EREG_HW_CFG_PERI_CONFIG1                0x000AAul
#define BLDCFOC_EREG_HW_CFG_GD_CONFIG1                  0x000ACul
#define BLDCFOC_EREG_HW_CFG_GD_CONFIG2                  0x000AEul

/**
 * @brief BLDC FOC RAM (Volatile) Register Map.
 * @details Specified RAM (Volatile) Register Map of BLDC FOC Click driver.
 */
#define BLDCFOC_RREG_FAULT_STATUS_GATE_DRIVER           0x000E0ul
#define BLDCFOC_RREG_FAULT_STATUS_CONTROLLER            0x000E2ul
#define BLDCFOC_RREG_SYS_STATUS_ALGO                    0x000E4ul
#define BLDCFOC_RREG_SYS_STATUS_MTR_PARAMS              0x000E6ul
#define BLDCFOC_RREG_SYS_STATUS_ALGO_MPET               0x000E8ul
#define BLDCFOC_RREG_DEV_CTRL                           0x000EAul
#define BLDCFOC_RREG_ALG_CTRL_ALGO_DEBUG1               0x000ECul
#define BLDCFOC_RREG_ALG_CTRL_ALGO_DEBUG2               0x000EEul
#define BLDCFOC_RREG_ALG_CTRL_CURRENT_PI                0x000F0ul
#define BLDCFOC_RREG_ALG_CTRL_SPEED_PI                  0x000F2ul
#define BLDCFOC_RREG_ALG_CTRL_DAC_1                     0x000F4ul
#define BLDCFOC_RREG_ALG_VAR_ALGORITHM_STATE            0x00196ul
#define BLDCFOC_RREG_ALG_VAR_FG_SPEED_FDBK              0x0019Cul
#define BLDCFOC_RREG_ALG_VAR_BUS_CURRENT                0x0040Eul
#define BLDCFOC_RREG_ALG_VAR_PHASE_CURRENT_A            0x0043Cul
#define BLDCFOC_RREG_ALG_VAR_PHASE_CURRENT_B            0x0043Eul
#define BLDCFOC_RREG_ALG_VAR_PHASE_CURRENT_C            0x00440ul
#define BLDCFOC_RREG_ALG_VAR_CSA_GAIN_FEEDBACK          0x00450ul
#define BLDCFOC_RREG_ALG_VAR_VOLTAGE_GAIN_FEEDBACK      0x00458ul
#define BLDCFOC_RREG_ALG_VAR_VM_VOLTAGE                 0x0045Cul
#define BLDCFOC_RREG_ALG_VAR_PHASE_VOLTAGE_VA           0x00460ul
#define BLDCFOC_RREG_ALG_VAR_PHASE_VOLTAGE_VB           0x00462ul
#define BLDCFOC_RREG_ALG_VAR_PHASE_VOLTAGE_VC           0x00464ul
#define BLDCFOC_RREG_ALG_VAR_SIN_COMMUTATION_ANGLE      0x004AAul
#define BLDCFOC_RREG_ALG_VAR_COS_COMMUTATION_ANGLE      0x004ACul
#define BLDCFOC_RREG_ALG_VAR_IALPHA                     0x004CCul
#define BLDCFOC_RREG_ALG_VAR_IBETA                      0x004CEul
#define BLDCFOC_RREG_ALG_VAR_VALPHA                     0x004D0ul
#define BLDCFOC_RREG_ALG_VAR_VBETA                      0x004D2ul
#define BLDCFOC_RREG_ALG_VAR_ID                         0x004DCul
#define BLDCFOC_RREG_ALG_VAR_IQ                         0x004DEul
#define BLDCFOC_RREG_ALG_VAR_VD                         0x004E0ul
#define BLDCFOC_RREG_ALG_VAR_VQ                         0x004E2ul
#define BLDCFOC_RREG_ALG_VAR_IQ_REF_ROTOR_ALIGN         0x0051Aul
#define BLDCFOC_RREG_ALG_VAR_SPEED_REF_OPEN_LOOP        0x00532ul
#define BLDCFOC_RREG_ALG_VAR_IQ_REF_OPEN_LOOP           0x00542ul
#define BLDCFOC_RREG_ALG_VAR_SPEED_REF_CLOSED_LOOP      0x005D0ul
#define BLDCFOC_RREG_ALG_VAR_ID_REF_CLOSED_LOOP         0x0060Aul
#define BLDCFOC_RREG_ALG_VAR_IQ_REF_CLOSED_LOOP         0x0060Cul
#define BLDCFOC_RREG_ALG_VAR_ISD_STATE                  0x006B0ul
#define BLDCFOC_RREG_ALG_VAR_ISD_SPEED                  0x006BAul
#define BLDCFOC_RREG_ALG_VAR_IPD_STATE                  0x006E4ul
#define BLDCFOC_RREG_ALG_VAR_IPD_ANGLE                  0x0071Aul
#define BLDCFOC_RREG_ALG_VAR_ED                         0x0075Cul
#define BLDCFOC_RREG_ALG_VAR_EQ                         0x0075Eul
#define BLDCFOC_RREG_ALG_VAR_SPEED_FDBK                 0x0076Eul
#define BLDCFOC_RREG_ALG_VAR_THETA_EST                  0x00774ul

/*! @} */ // bldcfoc_reg

/**
 * @defgroup bldcfoc_set BLDC FOC Registers Settings
 * @brief Settings for registers of BLDC FOC Click driver.
 */

/**
 * @addtogroup bldcfoc_set
 * @{
 */

/**
 * @brief BLDC FOC ISD_CONFIG register setting.
 * @details Specified setting for ISD_CONFIG register of BLDC FOC Click driver.
 */
#define BLDCFOC_ISD_CONFIG_PARITY                       0x80000000ul
#define BLDCFOC_ISD_CONFIG_ISD_EN_MASK                  0x40000000ul
#define BLDCFOC_ISD_CONFIG_BRAKE_EN_MASK                0x20000000ul
#define BLDCFOC_ISD_CONFIG_HIZ_EN_MASK                  0x10000000ul
#define BLDCFOC_ISD_CONFIG_RVS_DR_EN_MASK               0x08000000ul
#define BLDCFOC_ISD_CONFIG_RESYNC_EN_MASK               0x04000000ul
#define BLDCFOC_ISD_CONFIG_FW_DRV_RESYN_THR_MASK        0x03C00000ul
#define BLDCFOC_ISD_CONFIG_SINGLE_SHUNT_BLANK_TIME_MASK 0x001E0000ul
#define BLDCFOC_ISD_CONFIG_BRK_TIME_MASK                0x0001E000ul
#define BLDCFOC_ISD_CONFIG_HIZ_TIME_MASK                0x00001E00ul
#define BLDCFOC_ISD_CONFIG_STAT_DETECT_THR_MASK         0x000001C0ul
#define BLDCFOC_ISD_CONFIG_REV_DRV_HANDOFF_THR_MASK     0x0000003Cul
#define BLDCFOC_ISD_CONFIG_REV_DRV_OL_CURRENT_MASK      0x00000003ul

/**
 * @brief BLDC FOC REV_DRIVE_CONFIG register setting.
 * @details Specified setting for REV_DRIVE_CONFIG register of BLDC FOC Click driver.
 */
#define BLDCFOC_REV_DRIVE_CONFIG_PARITY                 0x80000000ul
#define BLDCFOC_REV_DRIVE_CONFIG_OL_ACC_A1_MASK         0x78000000ul
#define BLDCFOC_REV_DRIVE_CONFIG_OL_ACC_A2_MASK         0x07800000ul
#define BLDCFOC_REV_DRIVE_CONFIG_ACT_BRK_CURR_LIM_MASK  0x00700000ul
#define BLDCFOC_REV_DRIVE_CONFIG_ACT_BRK_KP_MASK        0x000FFC00ul
#define BLDCFOC_REV_DRIVE_CONFIG_ACT_BRK_KI_MASK        0x000003FFul

/**
 * @brief BLDC FOC MOTOR_STARTUP1 register setting.
 * @details Specified setting for MOTOR_STARTUP1 register of BLDC FOC Click driver.
 */
#define BLDCFOC_MOTOR_STARTUP1_PARITY                   0x80000000ul
#define BLDCFOC_MOTOR_STARTUP1_MTR_STARTUP_MASK         0x60000000ul
#define BLDCFOC_MOTOR_STARTUP1_ALIGN_SLR_RATE_MASK      0x1E000000ul
#define BLDCFOC_MOTOR_STARTUP1_ALIGN_TIME_MASK          0x01E00000ul
#define BLDCFOC_MOTOR_STARTUP1_ALIGN_SL_CUR_LIM_MASK    0x001E0000ul
#define BLDCFOC_MOTOR_STARTUP1_IPD_CLK_FREQ_MASK        0x0001C000ul
#define BLDCFOC_MOTOR_STARTUP1_IPD_CURR_THR_MASK        0x00003E00ul
#define BLDCFOC_MOTOR_STARTUP1_IPD_ADV_ANGLE_MASK       0x000000C0ul
#define BLDCFOC_MOTOR_STARTUP1_IPD_REPEAT_MASK          0x00000030ul
#define BLDCFOC_MOTOR_STARTUP1_OL_LIM_CONFIG_MASK       0x00000008ul
#define BLDCFOC_MOTOR_STARTUP1_IQ_RAMP_EN_MASK          0x00000004ul
#define BLDCFOC_MOTOR_STARTUP1_ACT_BRAKE_EN_MASK        0x00000002ul
#define BLDCFOC_MOTOR_STARTUP1_REV_DRV_CONFIG_MASK      0x00000001ul

/**
 * @brief BLDC FOC MOTOR_STARTUP2 register setting.
 * @details Specified setting for MOTOR_STARTUP2 register of BLDC FOC Click driver.
 */
#define BLDCFOC_MOTOR_STARTUP2_PARITY                   0x80000000ul
#define BLDCFOC_MOTOR_STARTUP2_OL_ILIMIT_MASK           0x78000000ul
#define BLDCFOC_MOTOR_STARTUP2_OL_ACC_A1_MASK           0x07800000ul
#define BLDCFOC_MOTOR_STARTUP2_OL_ACC_A2_MASK           0x00780000ul
#define BLDCFOC_MOTOR_STARTUP2_AUTO_HANDOFF_EN_MASK     0x00040000ul
#define BLDCFOC_MOTOR_STARTUP2_OPN_CL_HANDOFF_THR_MASK  0x0003E000ul
#define BLDCFOC_MOTOR_STARTUP2_ALIGN_ANGLE_MASK         0x00001F00ul
#define BLDCFOC_MOTOR_STARTUP2_SLOW_FC_FREQ_MASK        0x000000F0ul
#define BLDCFOC_MOTOR_STARTUP2_FC_FREQ_SEL_MASK         0x00000008ul
#define BLDCFOC_MOTOR_STARTUP2_THETA_ERR_R_RATE_MASK    0x00000007ul

/**
 * @brief BLDC FOC CLOSED_LOOP1 register setting.
 * @details Specified setting for CLOSED_LOOP1 register of BLDC FOC Click driver.
 */
#define BLDCFOC_CLOSED_LOOP1_PARITY                     0x80000000ul
#define BLDCFOC_CLOSED_LOOP1_CL_ACC_MASK                0x3E000000ul
#define BLDCFOC_CLOSED_LOOP1_CL_DEC_CONFIG_MASK         0x01000000ul
#define BLDCFOC_CLOSED_LOOP1_CL_DEC_MASK                0x00F80000ul
#define BLDCFOC_CLOSED_LOOP1_PWM_FREQ_OUT_MASK          0x00078000ul
#define BLDCFOC_CLOSED_LOOP1_FG_SEL_MASK                0x00003000ul
#define BLDCFOC_CLOSED_LOOP1_FG_DIV_MASK                0x00000F00ul
#define BLDCFOC_CLOSED_LOOP1_FG_CONFIG_MASK             0x00000080ul
#define BLDCFOC_CLOSED_LOOP1_FG_BEMF_THR_MASK           0x00000070ul
#define BLDCFOC_CLOSED_LOOP1_AVS_EN_MASK                0x00000008ul
#define BLDCFOC_CLOSED_LOOP1_DEADTIME_COMP_EN_MASK      0x00000004ul
#define BLDCFOC_CLOSED_LOOP1_LOW_SPEED_R_BRAKE_EN_MASK  0x00000001ul

/**
 * @brief BLDC FOC CLOSED_LOOP2 register setting.
 * @details Specified setting for CLOSED_LOOP2 register of BLDC FOC Click driver.
 */
#define BLDCFOC_CLOSED_LOOP2_PARITY                     0x80000000ul
#define BLDCFOC_CLOSED_LOOP2_MTR_STOP_MASK              0x70000000ul
#define BLDCFOC_CLOSED_LOOP2_MTR_STOP_BRK_TIME_MASK     0x0F000000ul
#define BLDCFOC_CLOSED_LOOP2_ACT_SPIN_THR_MASK          0x00F00000ul
#define BLDCFOC_CLOSED_LOOP2_BRAKE_SPEED_THR_MASK       0x000F0000ul
#define BLDCFOC_CLOSED_LOOP2_MOTOR_RES_MASK             0x0000FF00ul
#define BLDCFOC_CLOSED_LOOP2_MOTOR_IND_MASK             0x000000FFul

/**
 * @brief BLDC FOC CLOSED_LOOP3 register setting.
 * @details Specified setting for CLOSED_LOOP3 register of BLDC FOC Click driver.
 */
#define BLDCFOC_CLOSED_LOOP3_PARITY                     0x80000000ul
#define BLDCFOC_CLOSED_LOOP3_MOTOR_BEMF_CONST_MASK      0x7F800000ul
#define BLDCFOC_CLOSED_LOOP3_CURR_LOOP_KP_MASK          0x007FE000ul
#define BLDCFOC_CLOSED_LOOP3_CURR_LOOP_KI_MASK          0x00001FF8ul
#define BLDCFOC_CLOSED_LOOP3_SPD_LOOP_KP_MASK           0x00000007ul

/**
 * @brief BLDC FOC CLOSED_LOOP4 register setting.
 * @details Specified setting for CLOSED_LOOP4 register of BLDC FOC Click driver.
 */
#define BLDCFOC_CLOSED_LOOP4_PARITY                     0x80000000ul
#define BLDCFOC_CLOSED_LOOP4_SPD_LOOP_KP_MASK           0x7F000000ul
#define BLDCFOC_CLOSED_LOOP4_SPD_LOOP_KI_MASK           0x00FFC000ul
#define BLDCFOC_CLOSED_LOOP4_MAX_SPEED_MASK             0x00003FFFul

/**
 * @brief BLDC FOC REF_PROFILES1 register setting.
 * @details Specified setting for REF_PROFILES1 register of BLDC FOC Click driver.
 */
#define BLDCFOC_REF_PROFILES1_PARITY                    0x80000000ul
#define BLDCFOC_REF_PROFILES1_REF_PROF_CONFIG_MASK      0x60000000ul
#define BLDCFOC_REF_PROFILES1_DUTY_ON1_MASK             0x1FE00000ul
#define BLDCFOC_REF_PROFILES1_DUTY_OFF1_MASK            0x001FE000ul
#define BLDCFOC_REF_PROFILES1_DUTY_CLAMP1_MASK          0x00001FE0ul
#define BLDCFOC_REF_PROFILES1_DUTY_A_MASK               0x0000001Ful

/**
 * @brief BLDC FOC REF_PROFILES2 register setting.
 * @details Specified setting for REF_PROFILES2 register of BLDC FOC Click driver.
 */
#define BLDCFOC_REF_PROFILES2_PARITY                    0x80000000ul
#define BLDCFOC_REF_PROFILES2_DUTY_A_MASK               0x70000000ul
#define BLDCFOC_REF_PROFILES2_DUTY_B_MASK               0x0FF00000ul
#define BLDCFOC_REF_PROFILES2_DUTY_C_MASK               0x000FF000ul
#define BLDCFOC_REF_PROFILES2_DUTY_D_MASK               0x00000FF0ul
#define BLDCFOC_REF_PROFILES2_DUTY_E_MASK               0x0000000Ful

/**
 * @brief BLDC FOC REF_PROFILES3 register setting.
 * @details Specified setting for REF_PROFILES3 register of BLDC FOC Click driver.
 */
#define BLDCFOC_REF_PROFILES3_PARITY                    0x80000000ul
#define BLDCFOC_REF_PROFILES3_DUTY_E_MASK               0x78000000ul
#define BLDCFOC_REF_PROFILES3_DUTY_ON2_MASK             0x07F80000ul
#define BLDCFOC_REF_PROFILES3_DUTY_OFF2_MASK            0x0007F800ul
#define BLDCFOC_REF_PROFILES3_DUTY_CLAMP2_MASK          0x000007F8ul
#define BLDCFOC_REF_PROFILES3_DUTY_HYS_MASK             0x00000006ul

/**
 * @brief BLDC FOC REF_PROFILES4 register setting.
 * @details Specified setting for REF_PROFILES4 register of BLDC FOC Click driver.
 */
#define BLDCFOC_REF_PROFILES4_PARITY                    0x80000000ul
#define BLDCFOC_REF_PROFILES4_REF_OFF1_MASK             0x7F800000ul
#define BLDCFOC_REF_PROFILES4_REF_CLAMP1_MASK           0x007F8000ul
#define BLDCFOC_REF_PROFILES4_REF_A_MASK                0x00007F80ul
#define BLDCFOC_REF_PROFILES4_REF_B_MASK                0x0000007Ful

/**
 * @brief BLDC FOC REF_PROFILES5 register setting.
 * @details Specified setting for REF_PROFILES5 register of BLDC FOC Click driver.
 */
#define BLDCFOC_REF_PROFILES5_PARITY                    0x80000000ul
#define BLDCFOC_REF_PROFILES5_REF_B_MASK                0x40000000ul
#define BLDCFOC_REF_PROFILES5_REF_C_MASK                0x3FC00000ul
#define BLDCFOC_REF_PROFILES5_REF_D_MASK                0x003FC000ul
#define BLDCFOC_REF_PROFILES5_REF_E_MASK                0x00003FC0ul

/**
 * @brief BLDC FOC REF_PROFILES6 register setting.
 * @details Specified setting for REF_PROFILES6 register of BLDC FOC Click driver.
 */
#define BLDCFOC_REF_PROFILES6_PARITY                    0x80000000ul
#define BLDCFOC_REF_PROFILES6_REF_OFF2_MASK             0x7F800000ul
#define BLDCFOC_REF_PROFILES6_REF_CLAMP2_MASK           0x007F8000ul

/**
 * @brief BLDC FOC FAULT_CONFIG1 register setting.
 * @details Specified setting for FAULT_CONFIG1 register of BLDC FOC Click driver.
 */
#define BLDCFOC_FAULT_CONFIG1_PARITY                    0x80000000ul
#define BLDCFOC_FAULT_CONFIG1_ILIMIT_MASK               0x78000000ul
#define BLDCFOC_FAULT_CONFIG1_HW_LOCK_ILIMIT_MASK       0x07800000ul
#define BLDCFOC_FAULT_CONFIG1_LOCK_ILIMIT_MASK          0x00780000ul
#define BLDCFOC_FAULT_CONFIG1_LOCK_ILIMIT_MODE_MASK     0x00078000ul
#define BLDCFOC_FAULT_CONFIG1_LOCK_ILIMIT_DEG_MASK      0x00007800ul
#define BLDCFOC_FAULT_CONFIG1_LCK_RETRY_MASK            0x00000780ul
#define BLDCFOC_FAULT_CONFIG1_MTR_LCK_MODE_MASK         0x00000078ul
#define BLDCFOC_FAULT_CONFIG1_IPD_TIMEOUT_FAULT_EN_MASK 0x00000004ul
#define BLDCFOC_FAULT_CONFIG1_IPD_FREQ_FAULT_EN_MASK    0x00000002ul
#define BLDCFOC_FAULT_CONFIG1_SATURATION_FLAGS_EN_MASK  0x00000001ul

/**
 * @brief BLDC FOC FAULT_CONFIG2 register setting.
 * @details Specified setting for FAULT_CONFIG2 register of BLDC FOC Click driver.
 */
#define BLDCFOC_FAULT_CONFIG2_PARITY                    0x80000000ul
#define BLDCFOC_FAULT_CONFIG2_LOCK1_EN_MASK             0x40000000ul
#define BLDCFOC_FAULT_CONFIG2_LOCK2_EN_MASK             0x20000000ul
#define BLDCFOC_FAULT_CONFIG2_LOCK3_EN_MASK             0x10000000ul
#define BLDCFOC_FAULT_CONFIG2_LOCK_ABN_SPEED_MASK       0x0E000000ul
#define BLDCFOC_FAULT_CONFIG2_ABNORMAL_BEMF_THR_MASK    0x01C00000ul
#define BLDCFOC_FAULT_CONFIG2_NO_MTR_THR_MASK           0x00380000ul
#define BLDCFOC_FAULT_CONFIG2_HW_LOCK_ILIMIT_MODE_MASK  0x00078000ul
#define BLDCFOC_FAULT_CONFIG2_HW_LOCK_ILIMIT_DEG_MASK   0x00007000ul
#define BLDCFOC_FAULT_CONFIG2_VM_UV_OV_HYS_MASK         0x00000800ul
#define BLDCFOC_FAULT_CONFIG2_MIN_VM_MOTOR_MASK         0x00000700ul
#define BLDCFOC_FAULT_CONFIG2_MIN_VM_MODE_MASK          0x00000080ul
#define BLDCFOC_FAULT_CONFIG2_MAX_VM_MOTOR_MASK         0x00000070ul
#define BLDCFOC_FAULT_CONFIG2_MAX_VM_MODE_MASK          0x00000008ul
#define BLDCFOC_FAULT_CONFIG2_AUTO_RETRY_TIMES_MASK     0x00000007ul

/**
 * @brief BLDC FOC PIN_CONFIG register setting.
 * @details Specified setting for PIN_CONFIG register of BLDC FOC Click driver.
 */
#define BLDCFOC_PIN_CONFIG_PARITY                       0x80000000ul
#define BLDCFOC_PIN_CONFIG_FLUX_WEAK_CURRENT_RATIO_MASK 0x70000000ul
#define BLDCFOC_PIN_CONFIG_VDC_FILTER_DIS_MASK          0x08000000ul
#define BLDCFOC_PIN_CONFIG_LEAD_ANGLE_MASK              0x07C00000ul
#define BLDCFOC_PIN_CONFIG_MAX_POWER_MASK               0x003FF800ul
#define BLDCFOC_PIN_CONFIG_FG_IDLE_CONFIG_MASK          0x00000600ul
#define BLDCFOC_PIN_CONFIG_FG_FAULT_CONFIG_MASK         0x00000180ul
#define BLDCFOC_PIN_CONFIG_BRAKE_PIN_MODE_MASK          0x00000020ul
#define BLDCFOC_PIN_CONFIG_BRAKE_INPUT_MASK             0x0000000Cul
#define BLDCFOC_PIN_CONFIG_SPEED_MODE_MASK              0x00000003ul

/**
 * @brief BLDC FOC DEVICE_CONFIG1 register setting.
 * @details Specified setting for DEVICE_CONFIG1 register of BLDC FOC Click driver.
 */
#define BLDCFOC_DEVICE_CONFIG1_PARITY                   0x80000000ul
#define BLDCFOC_DEVICE_CONFIG1_MTPA_EN_MASK             0x40000000ul
#define BLDCFOC_DEVICE_CONFIG1_DAC_SOX_ANA_CONFIG_MASK  0x30000000ul
#define BLDCFOC_DEVICE_CONFIG1_I2C_TARGET_ADDR_MASK     0x07F00000ul
#define BLDCFOC_DEVICE_CONFIG1_SLEW_RATE_I2C_PINS_MASK  0x00000018ul
#define BLDCFOC_DEVICE_CONFIG1_PULLUP_ENABLE_MASK       0x00000004ul
#define BLDCFOC_DEVICE_CONFIG1_BUS_VOLT_MASK            0x00000003ul

/**
 * @brief BLDC FOC DEVICE_CONFIG2 register setting.
 * @details Specified setting for DEVICE_CONFIG2 register of BLDC FOC Click driver.
 */
#define BLDCFOC_DEVICE_CONFIG2_PARITY                   0x80000000ul
#define BLDCFOC_DEVICE_CONFIG2_INPUT_MAX_FREQ_MASK      0x7FFF0000ul
#define BLDCFOC_DEVICE_CONFIG2_SLEEP_ENTRY_TIME_MASK    0x0000C000ul
#define BLDCFOC_DEVICE_CONFIG2_DYNAMIC_V_GAIN_EN_MASK   0x00001000ul
#define BLDCFOC_DEVICE_CONFIG2_DEV_MODE_MASK            0x00000800ul
#define BLDCFOC_DEVICE_CONFIG2_CLK_SEL_MASK             0x00000600ul
#define BLDCFOC_DEVICE_CONFIG2_EXT_CLK_EN_MASK          0x00000100ul
#define BLDCFOC_DEVICE_CONFIG2_EXT_CLK_CONFIG_MASK      0x000000E0ul
#define BLDCFOC_DEVICE_CONFIG2_EXT_WD_EN_MASK           0x00000010ul
#define BLDCFOC_DEVICE_CONFIG2_EXT_WD_CONFIG_MASK       0x0000000Cul
#define BLDCFOC_DEVICE_CONFIG2_EXT_WD_FAULT_MASK        0x00000001ul

/**
 * @brief BLDC FOC PERI_CONFIG1 register setting.
 * @details Specified setting for PERI_CONFIG1 register of BLDC FOC Click driver.
 */
#define BLDCFOC_PERI_CONFIG1_PARITY                     0x80000000ul
#define BLDCFOC_PERI_CONFIG1_SS_MODULATION_DIS_MASK     0x40000000ul
#define BLDCFOC_PERI_CONFIG1_DIG_DEAD_TIME_MASK         0x3C000000ul
#define BLDCFOC_PERI_CONFIG1_BUS_CURRENT_LIMIT_MASK     0x03C00000ul
#define BLDCFOC_PERI_CONFIG1_BUS_CURRENT_LIMIT_EN_MASK  0x00200000ul
#define BLDCFOC_PERI_CONFIG1_DIR_INPUT_MASK             0x00180000ul
#define BLDCFOC_PERI_CONFIG1_DIR_CHANGE_MODE_MASK       0x00040000ul
#define BLDCFOC_PERI_CONFIG1_SELF_TEST_EN_MASK          0x00020000ul
#define BLDCFOC_PERI_CONFIG1_ACT_BRK_SPEED_D_LIM_MASK   0x0001E000ul
#define BLDCFOC_PERI_CONFIG1_ACT_BRK_MOD_IDX_LIM_MASK   0x00001C00ul
#define BLDCFOC_PERI_CONFIG1_SPEED_RANGE_SEL_MASK       0x00000200ul
#define BLDCFOC_PERI_CONFIG1_FLUX_WEAK_REF_MASK         0x000000C0ul
#define BLDCFOC_PERI_CONFIG1_CTRL_MODE_MASK             0x00000030ul
#define BLDCFOC_PERI_CONFIG1_SALIENCY_PCT_MASK          0x0000000Ful

/**
 * @brief BLDC FOC GD_CONFIG1 register setting.
 * @details Specified setting for GD_CONFIG1 register of BLDC FOC Click driver.
 */
#define BLDCFOC_GD_CONFIG1_PARITY                       0x80000000ul
#define BLDCFOC_GD_CONFIG1_BST_CHRG_TIME_MASK           0x03000000ul
#define BLDCFOC_GD_CONFIG1_SNS_FLT_MODE_MASK            0x00800000ul
#define BLDCFOC_GD_CONFIG1_VDS_FLT_MODE_MASK            0x00400000ul
#define BLDCFOC_GD_CONFIG1_BST_UV_MODE_MASK             0x00200000ul
#define BLDCFOC_GD_CONFIG1_GVDD_UV_MODE_MASK            0x00100000ul
#define BLDCFOC_GD_CONFIG1_DIS_BST_FLT_MASK             0x00010000ul
#define BLDCFOC_GD_CONFIG1_OTS_AUTO_REC_MASK            0x00008000ul
#define BLDCFOC_GD_CONFIG1_DIS_SNS_FLT_MASK             0x00000200ul
#define BLDCFOC_GD_CONFIG1_DIS_VDS_FLT_MASK             0x00000100ul
#define BLDCFOC_GD_CONFIG1_SEL_VDS_LVL_MASK             0x00000078ul
#define BLDCFOC_GD_CONFIG1_CSA_GAIN_MASK                0x00000003ul

/**
 * @brief BLDC FOC GD_CONFIG2 register setting.
 * @details Specified setting for GD_CONFIG2 register of BLDC FOC Click driver.
 */
#define BLDCFOC_GD_CONFIG2_PARITY                       0x80000000ul
#define BLDCFOC_GD_CONFIG2_BASE_CURRENT_MASK            0x00007FFFul

/**
 * @brief BLDC FOC INT_ALGO_1 register setting.
 * @details Specified setting for INT_ALGO_1 register of BLDC FOC Click driver.
 */
#define BLDCFOC_INT_ALGO_1_PARITY                       0x80000000ul
#define BLDCFOC_INT_ALGO_1_ACT_BRAKE_SPD_DEL_LIM_MASK   0x60000000ul
#define BLDCFOC_INT_ALGO_1_SPEED_PIN_GL_FILTER_MASK     0x18000000ul
#define BLDCFOC_INT_ALGO_1_FAST_ISD_EN_MASK             0x04000000ul
#define BLDCFOC_INT_ALGO_1_ISD_STOP_TIME_MASK           0x03000000ul
#define BLDCFOC_INT_ALGO_1_ISD_RUN_TIME_MASK            0x00C00000ul
#define BLDCFOC_INT_ALGO_1_ISD_TIMEOUT_MASK             0x00300000ul
#define BLDCFOC_INT_ALGO_1_AUTO_HANDOFF_MIN_BEMF_MASK   0x000E0000ul
#define BLDCFOC_INT_ALGO_1_MPET_OL_CURR_REF_MASK        0x00000700ul
#define BLDCFOC_INT_ALGO_1_MPET_OL_SPEED_REF_MASK       0x000000C0ul
#define BLDCFOC_INT_ALGO_1_MPET_OL_SLEW_RATE_MASK       0x00000038ul
#define BLDCFOC_INT_ALGO_1_REV_DRV_OL_DEC_MASK          0x00000007ul

/**
 * @brief BLDC FOC INT_ALGO_2 register setting.
 * @details Specified setting for INT_ALGO_2 register of BLDC FOC Click driver.
 */
#define BLDCFOC_INT_ALGO_2_PARITY                       0x80000000ul
#define BLDCFOC_INT_ALGO_2_FLUX_WEAK_KP_MASK            0x7FE00000ul
#define BLDCFOC_INT_ALGO_2_FLUX_WEAK_KI_MASK            0x001FF800ul
#define BLDCFOC_INT_ALGO_2_FLUX_WEAK_EN_MASK            0x00000400ul
#define BLDCFOC_INT_ALGO_2_CL_SLOW_ACC_MASK             0x000003C0ul
#define BLDCFOC_INT_ALGO_2_ACT_BRK_BUS_CURR_S_RATE_MASK 0x00000038ul
#define BLDCFOC_INT_ALGO_2_MPET_KE_MEAS_PAR_SEL_MASK    0x00000002ul
#define BLDCFOC_INT_ALGO_2_IPD_HRES_EN_MASK             0x00000001ul

/**
 * @brief BLDC FOC FAULT_STATUS_GATE_DRIVER register setting.
 * @details Specified setting for FAULT_STATUS_GATE_DRIVER register of BLDC FOC Click driver.
 */
#define BLDCFOC_FAULT_STATUS_GATE_DRIVER_DRIVER_FLT     0x80000000ul
#define BLDCFOC_FAULT_STATUS_GATE_DRIVER_OTS_FLT        0x20000000ul
#define BLDCFOC_FAULT_STATUS_GATE_DRIVER_OCP_VDS        0x10000000ul
#define BLDCFOC_FAULT_STATUS_GATE_DRIVER_OCP_SNS        0x08000000ul
#define BLDCFOC_FAULT_STATUS_GATE_DRIVER_BST_UV         0x04000000ul
#define BLDCFOC_FAULT_STATUS_GATE_DRIVER_GVDD_UV        0x02000000ul
#define BLDCFOC_FAULT_STATUS_GATE_DRIVER_DRV_OFF        0x01000000ul

/**
 * @brief BLDC FOC FAULT_STATUS_GATE_DRIVER register setting.
 * @details Specified setting for FAULT_STATUS_GATE_DRIVER register of BLDC FOC Click driver.
 */
#define BLDCFOC_FAULT_STATUS_CONTROLLER_CONTROLLER_FLT  0x80000000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_IPD_FREQ_FLT    0x20000000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_IPD_T1_FLT      0x10000000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_BUS_C_LIM_STAT  0x04000000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_MPET_BEMF_FLT   0x01000000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_ABN_SPEED       0x00800000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_ABN_BEMF        0x00400000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_NO_MTR          0x00200000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_MTR_LCK         0x00100000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_LCK_ILIMIT      0x00080000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_HW_LOCK_ILIMIT  0x00040000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_DCBUS_UNDER_V   0x00020000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_DCBUS_OVER_V    0x00010000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_SPEED_LOOP_SAT  0x00008000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_CURR_LOOP_SAT   0x00004000ul
#define BLDCFOC_FAULT_STATUS_CONTROLLER_WATCHDOG_FLT    0x00000008ul

/**
 * @brief BLDC FOC DEV_CTRL register setting.
 * @details Specified setting for DEV_CTRL register of BLDC FOC Click driver.
 */
#define BLDCFOC_DEV_CTRL_EEPROM_WRITE                   0x80000000ul
#define BLDCFOC_DEV_CTRL_EEPROM_READ                    0x40000000ul
#define BLDCFOC_DEV_CTRL_CLR_FLT                        0x20000000ul
#define BLDCFOC_DEV_CTRL_CLR_FLT_RETRY_CNT              0x10000000ul
#define BLDCFOC_DEV_CTRL_EERPOM_WRITE_ACCESS_KEY_MASK   0x0FF00000ul
#define BLDCFOC_DEV_CTRL_FORCED_ALIGN_ANGLE_MASK        0x000FF800ul
#define BLDCFOC_DEV_CTRL_WATCHDOG_TICKLE                0x00000400ul
#define BLDCFOC_DEV_CTRL_FLUX_MODE_REF                  0x000003FFul

/**
 * @brief BLDC FOC default register setting.
 * @details Specified default setting registers of BLDC FOC Click driver.
 * Speed controlled over PWM duty cycle, settings adjusted for A2212/13T 1000KV brushless motor. 
 */
#define BLDCFOC_DEFAULT_ISD_CONFIG                      0x64A2D419ul
#define BLDCFOC_DEFAULT_REV_DRIVE_CONFIG                0x48300000ul
#define BLDCFOC_DEFAULT_MOTOR_STARTUP1                  0x53260740ul
#define BLDCFOC_DEFAULT_MOTOR_STARTUP2                  0x2D81C007ul
#define BLDCFOC_DEFAULT_CLOSED_LOOP1                    0x26A9C1BAul
#define BLDCFOC_DEFAULT_CLOSED_LOOP2                    0x0BAC330Ful
#define BLDCFOC_DEFAULT_CLOSED_LOOP3                    0x0F64DD8Aul
#define BLDCFOC_DEFAULT_CLOSED_LOOP4                    0x44071770ul
#define BLDCFOC_DEFAULT_REF_PROFILES1                   0x00000000ul
#define BLDCFOC_DEFAULT_REF_PROFILES2                   0x00000000ul
#define BLDCFOC_DEFAULT_REF_PROFILES3                   0x00000004ul
#define BLDCFOC_DEFAULT_REF_PROFILES4                   0x00000000ul
#define BLDCFOC_DEFAULT_REF_PROFILES5                   0x00000000ul
#define BLDCFOC_DEFAULT_REF_PROFILES6                   0x00000000ul
#define BLDCFOC_DEFAULT_FAULT_CONFIG1                   0x465A31A6ul
#define BLDCFOC_DEFAULT_FAULT_CONFIG2                   0x71422888ul
#define BLDCFOC_DEFAULT_PIN_CONFIG                      0x4801F301ul
#define BLDCFOC_DEFAULT_DEVICE_CONFIG1                  0x00100001ul
#define BLDCFOC_DEFAULT_DEVICE_CONFIG2                  0x83E8E006ul
#define BLDCFOC_DEFAULT_PERI_CONFIG1                    0x69845CC0ul
#define BLDCFOC_DEFAULT_GD_CONFIG1                      0x0C04807Aul
#define BLDCFOC_DEFAULT_GD_CONFIG2                      0x00040199ul
#define BLDCFOC_DEFAULT_INT_ALGO_1                      0x09428005ul
#define BLDCFOC_DEFAULT_INT_ALGO_2                      0x02008320ul

/**
 * @brief BLDC FOC control word setting.
 * @details Specified setting for control word of BLDC FOC Click driver.
 */
#define BLDCFOC_CTRL_READ_BIT                           0x80
#define BLDCFOC_CTRL_CRC_DISABLE                        0x00
#define BLDCFOC_CTRL_CRC_ENABLE                         0x01
#define BLDCFOC_CTRL_CRC_MASK                           0x01
#define BLDCFOC_CTRL_DLEN_16_BIT                        0x00
#define BLDCFOC_CTRL_DLEN_32_BIT                        0x01
#define BLDCFOC_CTRL_DLEN_64_BIT                        0x02
#define BLDCFOC_CTRL_DLEN_MASK                          0x03
#define BLDCFOC_I2C_READ_BIT                            0x01

/**
 * @brief BLDC FOC direction settings.
 * @details Specified setting for direction of BLDC FOC Click driver.
 */
#define BLDCFOC_DIR_CCW                                 0
#define BLDCFOC_DIR_CW                                  1

/**
 * @brief BLDC FOC default PWM frequency.
 * @details Specified setting for default PWM frequency of BLDC FOC Click driver.
 */
#define BLDCFOC_DEF_FREQ                                10000

/**
 * @brief BLDC FOC device address setting.
 * @details Specified setting for device slave address selection of
 * BLDC FOC Click driver.
 */
#define BLDCFOC_DEVICE_ADDRESS                          0x01

/*! @} */ // bldcfoc_set

/**
 * @defgroup bldcfoc_map BLDC FOC MikroBUS Map
 * @brief MikroBUS pin mapping of BLDC FOC Click driver.
 */

/**
 * @addtogroup bldcfoc_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BLDC FOC Click to the selected MikroBUS.
 */
#define BLDCFOC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.brake = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.speed = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // bldcfoc_map
/*! @} */ // bldcfoc

/**
 * @brief BLDC FOC Click context object.
 * @details Context object definition of BLDC FOC Click driver.
 */
typedef struct
{
    digital_out_t brake;        /**< Brake pin (active high). */
    digital_out_t dir;          /**< Direction control pin (high - CW, low - CCW). */

    digital_in_t fault;         /**< Fault indicator pin (active low). */

    i2c_master_t i2c;           /**< I2C driver object. */
    pwm_t pwm;                  /**< PWM driver object. */

    uint32_t pwm_freq;          /**< PWM frequency value. */

    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint8_t crc_en;             /**< CRC enable flag. */

} bldcfoc_t;

/**
 * @brief BLDC FOC Click configuration object.
 * @details Configuration object definition of BLDC FOC Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t speed;           /**< Speed control PWM pin. */

    pin_name_t brake;           /**< Brake pin (active high). */
    pin_name_t dir;             /**< Direction control pin (high - CW, low - CCW). */
    pin_name_t fault;           /**< Fault indicator pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */
    uint32_t   dev_pwm_freq;    /**< PWM frequency value. */

} bldcfoc_cfg_t;

/**
 * @brief BLDC FOC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BLDCFOC_OK = 0,
    BLDCFOC_ERROR = -1

} bldcfoc_return_value_t;

/*!
 * @addtogroup bldcfoc BLDC FOC Click Driver
 * @brief API for configuring and manipulating BLDC FOC Click driver.
 * @{
 */

/**
 * @brief BLDC FOC configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bldcfoc_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bldcfoc_cfg_setup ( bldcfoc_cfg_t *cfg );

/**
 * @brief BLDC FOC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bldcfoc_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_init ( bldcfoc_t *ctx, bldcfoc_cfg_t *cfg );

/**
 * @brief BLDC FOC default configuration function.
 * @details This function executes a default configuration of BLDC FOC
 * Click board.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t bldcfoc_default_cfg ( bldcfoc_t *ctx );

/**
 * @brief BLDC FOC write reg 16 function.
 * @details This function writes a 16-bit data to the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_write_reg_16 ( bldcfoc_t *ctx, uint32_t mem_addr, uint16_t data_in );

/**
 * @brief BLDC FOC write reg 32 function.
 * @details This function writes a 32-bit data to the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[in] data_in : 32-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_write_reg_32 ( bldcfoc_t *ctx, uint32_t mem_addr, uint32_t data_in );

/**
 * @brief BLDC FOC write reg 64 function.
 * @details This function writes a 64-bit data starting from the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[in] data_in_msb : 32-bit MSB data to be written.
 * @param[in] data_in_lsb : 32-bit LSB data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_write_reg_64 ( bldcfoc_t *ctx, uint32_t mem_addr, uint32_t data_in_msb, uint32_t data_in_lsb );

/**
 * @brief BLDC FOC read reg 16 function.
 * @details This function reads a 16-bit data from the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[out] data_out : 16-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_read_reg_16 ( bldcfoc_t *ctx, uint32_t mem_addr, uint16_t *data_out );

/**
 * @brief BLDC FOC read reg 32 function.
 * @details This function reads a 32-bit data from the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[out] data_out : 32-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_read_reg_32 ( bldcfoc_t *ctx, uint32_t mem_addr, uint32_t *data_out );

/**
 * @brief BLDC FOC read reg 64 function.
 * @details This function reads a 64-bit data starting from the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[out] data_out_msb : 32-bit MSB output read data.
 * @param[out] data_out_lsb : 32-bit LSB output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_read_reg_64 ( bldcfoc_t *ctx, uint32_t mem_addr, uint32_t *data_out_msb, uint32_t *data_out_lsb );

/**
 * @brief BLDC FOC sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_set_duty_cycle ( bldcfoc_t *ctx, float duty_cycle );

/**
 * @brief BLDC FOC stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_pwm_stop ( bldcfoc_t *ctx );

/**
 * @brief BLDC FOC start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_pwm_start ( bldcfoc_t *ctx );

/**
 * @brief BLDC FOC set direction function.
 * @details This function sets the direction of motor rotation by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - CCW,
 *                  @li @c 1 - CW.
 * @return None.
 * @note None.
 */
void bldcfoc_set_direction ( bldcfoc_t *ctx, uint8_t dir );

/**
 * @brief BLDC FOC switch direction function.
 * @details This function switches the direction of motor rotation by toggling the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bldcfoc_switch_direction ( bldcfoc_t *ctx );

/**
 * @brief BLDC FOC pull brake function.
 * @details This function pulls brake by setting the BRAKE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bldcfoc_pull_brake ( bldcfoc_t *ctx );

/**
 * @brief BLDC FOC release brake function.
 * @details This function releases brake by setting the BRAKE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bldcfoc_release_brake ( bldcfoc_t *ctx );

/**
 * @brief BLDC FOC get fault pin function.
 * @details This function returns the fault indication pin logic state.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t bldcfoc_get_fault_pin ( bldcfoc_t *ctx );

/**
 * @brief BLDC FOC read fault function.
 * @details This function reads gate driver and controller fault registers.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @param[out] gate_drv_flt : Gate driver fault.
 * @param[out] controller_flt : Controller fault.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_read_fault ( bldcfoc_t *ctx, uint32_t *gate_drv_flt, uint32_t *controller_flt );

/**
 * @brief BLDC FOC clear fault function.
 * @details This function clears gate driver and controller fault registers.
 * @param[in] ctx : Click context object.
 * See #bldcfoc_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bldcfoc_clear_fault ( bldcfoc_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BLDCFOC_H

/*! @} */ // bldcfoc

// ------------------------------------------------------------------------ END
