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
 * @file brushless33.h
 * @brief This file contains API for Brushless 33 Click Driver.
 */

#ifndef BRUSHLESS33_H
#define BRUSHLESS33_H

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
 * @addtogroup brushless33 Brushless 33 Click Driver
 * @brief API for configuring and manipulating Brushless 33 Click driver.
 * @{
 */

/**
 * @defgroup brushless33_reg Brushless 33 Registers List
 * @brief List of registers of Brushless 33 Click driver.
 */

/**
 * @addtogroup brushless33_reg
 * @{
 */

/**
 * @brief Brushless 33 EEPROM (Non-Volatile) Register Map.
 * @details Specified EEPROM (Non-Volatile) Register Map of Brushless 33 Click driver.
 */
#define BRUSHLESS33_EREG_ALG_CFG_ISD_CONFIG                 0x00080ul
#define BRUSHLESS33_EREG_ALG_CFG_REV_DRIVE_CONFIG           0x00082ul
#define BRUSHLESS33_EREG_ALG_CFG_MOTOR_STARTUP1             0x00084ul
#define BRUSHLESS33_EREG_ALG_CFG_MOTOR_STARTUP2             0x00086ul
#define BRUSHLESS33_EREG_ALG_CFG_CLOSED_LOOP1               0x00088ul
#define BRUSHLESS33_EREG_ALG_CFG_CLOSED_LOOP2               0x0008Aul
#define BRUSHLESS33_EREG_ALG_CFG_CLOSED_LOOP3               0x0008Cul
#define BRUSHLESS33_EREG_ALG_CFG_CLOSED_LOOP4               0x0008Eul
#define BRUSHLESS33_EREG_FAULT_CFG_FAULT_CONFIG1            0x00090ul
#define BRUSHLESS33_EREG_FAULT_CFG_FAULT_CONFIG2            0x00092ul
#define BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES1            0x00094ul
#define BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES2            0x00096ul
#define BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES3            0x00098ul
#define BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES4            0x0009Aul
#define BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES5            0x0009Cul
#define BRUSHLESS33_EREG_ALG_CFG_SPEED_PROFILES6            0x0009Eul
#define BRUSHLESS33_EREG_INT_ALG_CFG_INT_ALGO_1             0x000A0ul
#define BRUSHLESS33_EREG_INT_ALG_CFG_INT_ALGO_2             0x000A2ul
#define BRUSHLESS33_EREG_HW_CFG_PIN_CONFIG                  0x000A4ul
#define BRUSHLESS33_EREG_HW_CFG_DEVICE_CONFIG1              0x000A6ul
#define BRUSHLESS33_EREG_HW_CFG_DEVICE_CONFIG2              0x000A8ul
#define BRUSHLESS33_EREG_HW_CFG_PERI_CONFIG1                0x000AAul
#define BRUSHLESS33_EREG_HW_CFG_GD_CONFIG1                  0x000ACul
#define BRUSHLESS33_EREG_HW_CFG_GD_CONFIG2                  0x000AEul

/**
 * @brief Brushless 33 RAM (Volatile) Register Map.
 * @details Specified RAM (Volatile) Register Map of Brushless 33 Click driver.
 */
#define BRUSHLESS33_RREG_FAULT_STATUS_GATE_DRIVER           0x000E0ul
#define BRUSHLESS33_RREG_FAULT_STATUS_CONTROLLER            0x000E2ul
#define BRUSHLESS33_RREG_SYS_STATUS_ALGO                    0x000E4ul
#define BRUSHLESS33_RREG_SYS_STATUS_MTR_PARAMS              0x000E6ul
#define BRUSHLESS33_RREG_SYS_STATUS_ALGO_MPET               0x000E8ul
#define BRUSHLESS33_RREG_DEV_CTRL                           0x000EAul
#define BRUSHLESS33_RREG_ALG_CTRL_ALGO_CTRL1                0x000ECul
#define BRUSHLESS33_RREG_ALG_CTRL_ALGO_CTRL2                0x000EEul
#define BRUSHLESS33_RREG_ALG_CTRL_CURRENT_PI                0x000F0ul
#define BRUSHLESS33_RREG_ALG_CTRL_SPEED_PI                  0x000F2ul
#define BRUSHLESS33_RREG_ALG_VAR_ALGORITHM_STATE            0x00210ul
#define BRUSHLESS33_RREG_ALG_VAR_FG_SPEED_FDBK              0x00216ul
#define BRUSHLESS33_RREG_ALG_VAR_BUS_CURRENT                0x00410ul
#define BRUSHLESS33_RREG_ALG_VAR_PHASE_CURRENT_A            0x0043Eul
#define BRUSHLESS33_RREG_ALG_VAR_PHASE_CURRENT_B            0x00440ul
#define BRUSHLESS33_RREG_ALG_VAR_PHASE_CURRENT_C            0x00442ul
#define BRUSHLESS33_RREG_ALG_VAR_CSA_GAIN_FEEDBACK          0x00466ul
#define BRUSHLESS33_RREG_ALG_VAR_VOLTAGE_GAIN_FEEDBACK      0x00476ul
#define BRUSHLESS33_RREG_ALG_VAR_VM_VOLTAGE                 0x00478ul
#define BRUSHLESS33_RREG_ALG_VAR_PHASE_VOLTAGE_VA           0x0047Eul
#define BRUSHLESS33_RREG_ALG_VAR_PHASE_VOLTAGE_VB           0x00480ul
#define BRUSHLESS33_RREG_ALG_VAR_PHASE_VOLTAGE_VC           0x00482ul
#define BRUSHLESS33_RREG_ALG_VAR_SIN_COMMUTATION_ANGLE      0x004BAul
#define BRUSHLESS33_RREG_ALG_VAR_COS_COMMUTATION_ANGLE      0x004BCul
#define BRUSHLESS33_RREG_ALG_VAR_IALPHA                     0x004D4ul
#define BRUSHLESS33_RREG_ALG_VAR_IBETA                      0x004D6ul
#define BRUSHLESS33_RREG_ALG_VAR_VALPHA                     0x004D8ul
#define BRUSHLESS33_RREG_ALG_VAR_VBETA                      0x004DAul
#define BRUSHLESS33_RREG_ALG_VAR_ID                         0x004E4ul
#define BRUSHLESS33_RREG_ALG_VAR_IQ                         0x004E6ul
#define BRUSHLESS33_RREG_ALG_VAR_VD                         0x004E8ul
#define BRUSHLESS33_RREG_ALG_VAR_VQ                         0x004EAul
#define BRUSHLESS33_RREG_ALG_VAR_IQ_REF_ROTOR_ALIGN         0x00524ul
#define BRUSHLESS33_RREG_ALG_VAR_SPEED_REF_OPEN_LOOP        0x0053Aul
#define BRUSHLESS33_RREG_ALG_VAR_IQ_REF_OPEN_LOOP           0x00548ul
#define BRUSHLESS33_RREG_ALG_VAR_SPEED_REF_CLOSED_LOOP      0x005CCul
#define BRUSHLESS33_RREG_ALG_VAR_ID_REF_CLOSED_LOOP         0x005FCul
#define BRUSHLESS33_RREG_ALG_VAR_IQ_REF_CLOSED_LOOP         0x005FEul
#define BRUSHLESS33_RREG_ALG_VAR_ISD_STATE                  0x0067Aul
#define BRUSHLESS33_RREG_ALG_VAR_ISD_SPEED                  0x00684ul
#define BRUSHLESS33_RREG_ALG_VAR_IPD_STATE                  0x006B8ul
#define BRUSHLESS33_RREG_ALG_VAR_IPD_ANGLE                  0x006FCul
#define BRUSHLESS33_RREG_ALG_VAR_ED                         0x00742ul
#define BRUSHLESS33_RREG_ALG_VAR_EQ                         0x00744ul
#define BRUSHLESS33_RREG_ALG_VAR_SPEED_FDBK                 0x00752ul
#define BRUSHLESS33_RREG_ALG_VAR_THETA_EST                  0x00756ul

/*! @} */ // brushless33_reg

/**
 * @defgroup brushless33_set Brushless 33 Registers Settings
 * @brief Settings for registers of Brushless 33 Click driver.
 */

/**
 * @addtogroup brushless33_set
 * @{
 */

/**
 * @brief Brushless 33 ISD_CONFIG register setting.
 * @details Specified setting for ISD_CONFIG register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_ISD_CONFIG_PARITY                       0x80000000ul
#define BRUSHLESS33_ISD_CONFIG_ISD_EN_MASK                  0x40000000ul
#define BRUSHLESS33_ISD_CONFIG_BRAKE_EN_MASK                0x20000000ul
#define BRUSHLESS33_ISD_CONFIG_HIZ_EN_MASK                  0x10000000ul
#define BRUSHLESS33_ISD_CONFIG_RVS_DR_EN_MASK               0x08000000ul
#define BRUSHLESS33_ISD_CONFIG_RESYNC_EN_MASK               0x04000000ul
#define BRUSHLESS33_ISD_CONFIG_FW_DRV_RESYN_THR_MASK        0x03C00000ul
#define BRUSHLESS33_ISD_CONFIG_BRK_MODE_MASK                0x00200000ul
#define BRUSHLESS33_ISD_CONFIG_BRK_TIME_MASK                0x0001E000ul
#define BRUSHLESS33_ISD_CONFIG_HIZ_TIME_MASK                0x00001E00ul
#define BRUSHLESS33_ISD_CONFIG_STAT_DETECT_THR_MASK         0x000001C0ul
#define BRUSHLESS33_ISD_CONFIG_REV_DRV_HANDOFF_THR_MASK     0x0000003Cul
#define BRUSHLESS33_ISD_CONFIG_REV_DRV_OL_CURRENT_MASK      0x00000003ul

/**
 * @brief Brushless 33 REV_DRIVE_CONFIG register setting.
 * @details Specified setting for REV_DRIVE_CONFIG register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_REV_DRIVE_CONFIG_PARITY                 0x80000000ul
#define BRUSHLESS33_REV_DRIVE_CONFIG_OL_ACC_A1_MASK         0x78000000ul
#define BRUSHLESS33_REV_DRIVE_CONFIG_OL_ACC_A2_MASK         0x07800000ul
#define BRUSHLESS33_REV_DRIVE_CONFIG_ACT_BRK_CURR_LIM_MASK  0x00700000ul
#define BRUSHLESS33_REV_DRIVE_CONFIG_ACT_BRK_KP_MASK        0x000FFC00ul
#define BRUSHLESS33_REV_DRIVE_CONFIG_ACT_BRK_KI_MASK        0x000003FFul

/**
 * @brief Brushless 33 MOTOR_STARTUP1 register setting.
 * @details Specified setting for MOTOR_STARTUP1 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_MOTOR_STARTUP1_PARITY                   0x80000000ul
#define BRUSHLESS33_MOTOR_STARTUP1_MTR_STARTUP_MASK         0x60000000ul
#define BRUSHLESS33_MOTOR_STARTUP1_ALIGN_SLR_RATE_MASK      0x1E000000ul
#define BRUSHLESS33_MOTOR_STARTUP1_ALIGN_TIME_MASK          0x01E00000ul
#define BRUSHLESS33_MOTOR_STARTUP1_ALIGN_SL_CUR_LIM_MASK    0x001E0000ul
#define BRUSHLESS33_MOTOR_STARTUP1_IPD_CLK_FREQ_MASK        0x0001C000ul
#define BRUSHLESS33_MOTOR_STARTUP1_IPD_CURR_THR_MASK        0x00003E00ul
#define BRUSHLESS33_MOTOR_STARTUP1_IPD_RLS_MODE_MASK        0x00000100ul
#define BRUSHLESS33_MOTOR_STARTUP1_IPD_ADV_ANGLE_MASK       0x000000C0ul
#define BRUSHLESS33_MOTOR_STARTUP1_IPD_REPEAT_MASK          0x00000030ul
#define BRUSHLESS33_MOTOR_STARTUP1_OL_LIM_CONFIG_MASK       0x00000008ul
#define BRUSHLESS33_MOTOR_STARTUP1_IQ_RAMP_EN_MASK          0x00000004ul
#define BRUSHLESS33_MOTOR_STARTUP1_ACT_BRAKE_EN_MASK        0x00000002ul
#define BRUSHLESS33_MOTOR_STARTUP1_REV_DRV_CONFIG_MASK      0x00000001ul

/**
 * @brief Brushless 33 MOTOR_STARTUP2 register setting.
 * @details Specified setting for MOTOR_STARTUP2 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_MOTOR_STARTUP2_PARITY                   0x80000000ul
#define BRUSHLESS33_MOTOR_STARTUP2_OL_ILIMIT_MASK           0x78000000ul
#define BRUSHLESS33_MOTOR_STARTUP2_OL_ACC_A1_MASK           0x07800000ul
#define BRUSHLESS33_MOTOR_STARTUP2_OL_ACC_A2_MASK           0x00780000ul
#define BRUSHLESS33_MOTOR_STARTUP2_AUTO_HANDOFF_EN_MASK     0x00040000ul
#define BRUSHLESS33_MOTOR_STARTUP2_OPN_CL_HANDOFF_THR_MASK  0x0003E000ul
#define BRUSHLESS33_MOTOR_STARTUP2_ALIGN_ANGLE_MASK         0x00001F00ul
#define BRUSHLESS33_MOTOR_STARTUP2_SLOW_FC_FREQ_MASK        0x000000F0ul
#define BRUSHLESS33_MOTOR_STARTUP2_FC_FREQ_SEL_MASK         0x00000008ul
#define BRUSHLESS33_MOTOR_STARTUP2_THETA_ERR_R_RATE_MASK    0x00000007ul

/**
 * @brief Brushless 33 CLOSED_LOOP1 register setting.
 * @details Specified setting for CLOSED_LOOP1 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_CLOSED_LOOP1_PARITY                     0x80000000ul
#define BRUSHLESS33_CLOSED_LOOP1_OVERMODULATION_EN_MASK     0x40000000ul
#define BRUSHLESS33_CLOSED_LOOP1_CL_ACC_MASK                0x3E000000ul
#define BRUSHLESS33_CLOSED_LOOP1_CL_DEC_CONFIG_MASK         0x01000000ul
#define BRUSHLESS33_CLOSED_LOOP1_CL_DEC_MASK                0x00F80000ul
#define BRUSHLESS33_CLOSED_LOOP1_PWM_FREQ_OUT_MASK          0x00078000ul
#define BRUSHLESS33_CLOSED_LOOP1_PWM_MODE_MASK              0x00004000ul
#define BRUSHLESS33_CLOSED_LOOP1_FG_SEL_MASK                0x00003000ul
#define BRUSHLESS33_CLOSED_LOOP1_FG_DIV_MASK                0x00000F00ul
#define BRUSHLESS33_CLOSED_LOOP1_FG_CONFIG_MASK             0x00000080ul
#define BRUSHLESS33_CLOSED_LOOP1_FG_BEMF_THR_MASK           0x00000070ul
#define BRUSHLESS33_CLOSED_LOOP1_AVS_EN_MASK                0x00000008ul
#define BRUSHLESS33_CLOSED_LOOP1_DEADTIME_COMP_EN_MASK      0x00000004ul
#define BRUSHLESS33_CLOSED_LOOP1_SPEED_LOOP_DIS_MASK        0x00000002ul
#define BRUSHLESS33_CLOSED_LOOP1_LOW_SPEED_R_BRAKE_EN_MASK  0x00000001ul

/**
 * @brief Brushless 33 CLOSED_LOOP2 register setting.
 * @details Specified setting for CLOSED_LOOP2 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_CLOSED_LOOP2_PARITY                     0x80000000ul
#define BRUSHLESS33_CLOSED_LOOP2_MTR_STOP_MASK              0x70000000ul
#define BRUSHLESS33_CLOSED_LOOP2_MTR_STOP_BRK_TIME_MASK     0x0F000000ul
#define BRUSHLESS33_CLOSED_LOOP2_ACT_SPIN_THR_MASK          0x00F00000ul
#define BRUSHLESS33_CLOSED_LOOP2_BRAKE_SPEED_THR_MASK       0x000F0000ul
#define BRUSHLESS33_CLOSED_LOOP2_MOTOR_RES_MASK             0x0000FF00ul
#define BRUSHLESS33_CLOSED_LOOP2_MOTOR_IND_MASK             0x000000FFul

/**
 * @brief Brushless 33 CLOSED_LOOP3 register setting.
 * @details Specified setting for CLOSED_LOOP3 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_CLOSED_LOOP3_PARITY                     0x80000000ul
#define BRUSHLESS33_CLOSED_LOOP3_MOTOR_BEMF_CONST_MASK      0x7F800000ul
#define BRUSHLESS33_CLOSED_LOOP3_CURR_LOOP_KP_MASK          0x007FE000ul
#define BRUSHLESS33_CLOSED_LOOP3_CURR_LOOP_KI_MASK          0x00001FF8ul
#define BRUSHLESS33_CLOSED_LOOP3_SPD_LOOP_KP_MASK           0x00000007ul

/**
 * @brief Brushless 33 CLOSED_LOOP4 register setting.
 * @details Specified setting for CLOSED_LOOP4 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_CLOSED_LOOP4_PARITY                     0x80000000ul
#define BRUSHLESS33_CLOSED_LOOP4_SPD_LOOP_KP_MASK           0x7F000000ul
#define BRUSHLESS33_CLOSED_LOOP4_SPD_LOOP_KI_MASK           0x00FFC000ul
#define BRUSHLESS33_CLOSED_LOOP4_MAX_SPEED_MASK             0x00003FFFul

/**
 * @brief Brushless 33 SPEED_PROFILES1 register setting.
 * @details Specified setting for SPEED_PROFILES1 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_SPEED_PROFILES1_PARITY                  0x80000000ul
#define BRUSHLESS33_SPEED_PROFILES1_SPD_PROF_CONFIG_MASK    0x60000000ul
#define BRUSHLESS33_SPEED_PROFILES1_DUTY_ON1_MASK           0x1FE00000ul
#define BRUSHLESS33_SPEED_PROFILES1_DUTY_OFF1_MASK          0x001FE000ul
#define BRUSHLESS33_SPEED_PROFILES1_DUTY_CLAMP1_MASK        0x00001FE0ul
#define BRUSHLESS33_SPEED_PROFILES1_DUTY_A_MASK             0x0000001Ful

/**
 * @brief Brushless 33 SPEED_PROFILES2 register setting.
 * @details Specified setting for SPEED_PROFILES2 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_SPEED_PROFILES2_PARITY                  0x80000000ul
#define BRUSHLESS33_SPEED_PROFILES2_DUTY_A_MASK             0x70000000ul
#define BRUSHLESS33_SPEED_PROFILES2_DUTY_B_MASK             0x0FF00000ul
#define BRUSHLESS33_SPEED_PROFILES2_DUTY_C_MASK             0x000FF000ul
#define BRUSHLESS33_SPEED_PROFILES2_DUTY_D_MASK             0x00000FF0ul
#define BRUSHLESS33_SPEED_PROFILES2_DUTY_E_MASK             0x0000000Ful

/**
 * @brief Brushless 33 SPEED_PROFILES3 register setting.
 * @details Specified setting for SPEED_PROFILES3 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_SPEED_PROFILES3_PARITY                  0x80000000ul
#define BRUSHLESS33_SPEED_PROFILES3_DUTY_E_MASK             0x78000000ul
#define BRUSHLESS33_SPEED_PROFILES3_DUTY_ON2_MASK           0x07F80000ul
#define BRUSHLESS33_SPEED_PROFILES3_DUTY_OFF2_MASK          0x0007F800ul
#define BRUSHLESS33_SPEED_PROFILES3_DUTY_CLAMP2_MASK        0x000007F8ul

/**
 * @brief Brushless 33 SPEED_PROFILES4 register setting.
 * @details Specified setting for SPEED_PROFILES4 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_SPEED_PROFILES4_PARITY                  0x80000000ul
#define BRUSHLESS33_SPEED_PROFILES4_SPEED_OFF1_MASK         0x7F800000ul
#define BRUSHLESS33_SPEED_PROFILES4_SPEED_CLAMP1_MASK       0x007F8000ul
#define BRUSHLESS33_SPEED_PROFILES4_SPEED_A_MASK            0x00007F80ul
#define BRUSHLESS33_SPEED_PROFILES4_SPEED_B_MASK            0x0000007Ful

/**
 * @brief Brushless 33 SPEED_PROFILES5 register setting.
 * @details Specified setting for SPEED_PROFILES5 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_SPEED_PROFILES5_PARITY                  0x80000000ul
#define BRUSHLESS33_SPEED_PROFILES5_SPEED_B_MASK            0x40000000ul
#define BRUSHLESS33_SPEED_PROFILES5_SPEED_C_MASK            0x3FC00000ul
#define BRUSHLESS33_SPEED_PROFILES5_SPEED_D_MASK            0x003FC000ul
#define BRUSHLESS33_SPEED_PROFILES5_SPEED_E_MASK            0x00003FC0ul

/**
 * @brief Brushless 33 SPEED_PROFILES6 register setting.
 * @details Specified setting for SPEED_PROFILES6 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_SPEED_PROFILES6_PARITY                  0x80000000ul
#define BRUSHLESS33_SPEED_PROFILES6_SPEED_OFF2_MASK         0x7F800000ul
#define BRUSHLESS33_SPEED_PROFILES6_SPEED_CLAMP2_MASK       0x007F8000ul

/**
 * @brief Brushless 33 FAULT_CONFIG1 register setting.
 * @details Specified setting for FAULT_CONFIG1 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_FAULT_CONFIG1_PARITY                    0x80000000ul
#define BRUSHLESS33_FAULT_CONFIG1_ILIMIT_MASK               0x78000000ul
#define BRUSHLESS33_FAULT_CONFIG1_HW_LOCK_ILIMIT_MASK       0x07800000ul
#define BRUSHLESS33_FAULT_CONFIG1_LOCK_ILIMIT_MASK          0x00780000ul
#define BRUSHLESS33_FAULT_CONFIG1_LOCK_ILIMIT_MODE_MASK     0x00078000ul
#define BRUSHLESS33_FAULT_CONFIG1_LOCK_ILIMIT_DEG_MASK      0x00007800ul
#define BRUSHLESS33_FAULT_CONFIG1_LCK_RETRY_MASK            0x00000780ul
#define BRUSHLESS33_FAULT_CONFIG1_MTR_LCK_MODE_MASK         0x00000078ul
#define BRUSHLESS33_FAULT_CONFIG1_IPD_TIMEOUT_FAULT_EN_MASK 0x00000004ul
#define BRUSHLESS33_FAULT_CONFIG1_IPD_FREQ_FAULT_EN_MASK    0x00000002ul
#define BRUSHLESS33_FAULT_CONFIG1_SATURATION_FLAGS_EN_MASK  0x00000001ul

/**
 * @brief Brushless 33 FAULT_CONFIG2 register setting.
 * @details Specified setting for FAULT_CONFIG2 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_FAULT_CONFIG2_PARITY                    0x80000000ul
#define BRUSHLESS33_FAULT_CONFIG2_LOCK1_EN_MASK             0x40000000ul
#define BRUSHLESS33_FAULT_CONFIG2_LOCK2_EN_MASK             0x20000000ul
#define BRUSHLESS33_FAULT_CONFIG2_LOCK3_EN_MASK             0x10000000ul
#define BRUSHLESS33_FAULT_CONFIG2_LOCK_ABN_SPEED_MASK       0x0E000000ul
#define BRUSHLESS33_FAULT_CONFIG2_ABNORMAL_BEMF_THR_MASK    0x01C00000ul
#define BRUSHLESS33_FAULT_CONFIG2_NO_MTR_THR_MASK           0x00380000ul
#define BRUSHLESS33_FAULT_CONFIG2_HW_LOCK_ILIMIT_MODE_MASK  0x00078000ul
#define BRUSHLESS33_FAULT_CONFIG2_HW_LOCK_ILIMIT_DEG_MASK   0x00007800ul
#define BRUSHLESS33_FAULT_CONFIG2_MIN_VM_MOTOR_MASK         0x00000780ul
#define BRUSHLESS33_FAULT_CONFIG2_MAX_VM_MOTOR_MASK         0x00000070ul
#define BRUSHLESS33_FAULT_CONFIG2_MAX_VM_MODE_MASK          0x00000008ul
#define BRUSHLESS33_FAULT_CONFIG2_AUTO_RETRY_TIMES_MASK     0x00000007ul

/**
 * @brief Brushless 33 PIN_CONFIG register setting.
 * @details Specified setting for PIN_CONFIG register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_PIN_CONFIG_PARITY                       0x80000000ul
#define BRUSHLESS33_PIN_CONFIG_BRAKE_PIN_MODE_MASK          0x00000020ul
#define BRUSHLESS33_PIN_CONFIG_ALIGN_BRAKE_ANGLE_SEL_MASK   0x00000010ul
#define BRUSHLESS33_PIN_CONFIG_BRAKE_INPUT_MASK             0x0000000Cul
#define BRUSHLESS33_PIN_CONFIG_SPEED_MODE_MASK              0x00000003ul

/**
 * @brief Brushless 33 DEVICE_CONFIG1 register setting.
 * @details Specified setting for DEVICE_CONFIG1 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_DEVICE_CONFIG1_PARITY                   0x80000000ul
#define BRUSHLESS33_DEVICE_CONFIG1_PIN_38_CONFIG_MASK       0x30000000ul
#define BRUSHLESS33_DEVICE_CONFIG1_I2C_TARGET_ADDR_MASK     0x07F00000ul
#define BRUSHLESS33_DEVICE_CONFIG1_BUS_VOLT_MASK            0x00000003ul

/**
 * @brief Brushless 33 DEVICE_CONFIG2 register setting.
 * @details Specified setting for DEVICE_CONFIG2 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_DEVICE_CONFIG2_PARITY                   0x80000000ul
#define BRUSHLESS33_DEVICE_CONFIG2_INPUT_MAX_FREQ_MASK      0x7FFF0000ul
#define BRUSHLESS33_DEVICE_CONFIG2_SLEEP_ENTRY_TIME_MASK    0x0000C000ul
#define BRUSHLESS33_DEVICE_CONFIG2_DYNAMIC_CSA_GAIN_EN_MASK 0x00002000ul
#define BRUSHLESS33_DEVICE_CONFIG2_DYNAMIC_V_GAIN_EN_MASK   0x00001000ul
#define BRUSHLESS33_DEVICE_CONFIG2_DEV_MODE_MASK            0x00000800ul
#define BRUSHLESS33_DEVICE_CONFIG2_CLK_SEL_MASK             0x00000600ul
#define BRUSHLESS33_DEVICE_CONFIG2_EXT_CLK_EN_MASK          0x000001E0ul
#define BRUSHLESS33_DEVICE_CONFIG2_EXT_WD_EN_MASK           0x00000010ul
#define BRUSHLESS33_DEVICE_CONFIG2_EXT_WD_CONFIG_MASK       0x0000000Cul
#define BRUSHLESS33_DEVICE_CONFIG2_EXT_WD_INPUT_MASK        0x00000002ul
#define BRUSHLESS33_DEVICE_CONFIG2_EXT_WD_FAULT_MASK        0x00000001ul

/**
 * @brief Brushless 33 PERI_CONFIG1 register setting.
 * @details Specified setting for PERI_CONFIG1 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_PERI_CONFIG1_PARITY                     0x80000000ul
#define BRUSHLESS33_PERI_CONFIG1_SS_MODULATION_DIS_MASK     0x40000000ul
#define BRUSHLESS33_PERI_CONFIG1_BUS_CURRENT_LIMIT_MASK     0x03C00000ul
#define BRUSHLESS33_PERI_CONFIG1_BUS_CURRENT_LIMIT_EN_MASK  0x00200000ul
#define BRUSHLESS33_PERI_CONFIG1_DIR_INPUT_MASK             0x00180000ul
#define BRUSHLESS33_PERI_CONFIG1_DIR_CHANGE_MODE_MASK       0x00040000ul
#define BRUSHLESS33_PERI_CONFIG1_SELF_TEST_EN_MASK          0x00020000ul
#define BRUSHLESS33_PERI_CONFIG1_ACT_BRK_SPEED_D_LIM_MASK   0x0001E000ul
#define BRUSHLESS33_PERI_CONFIG1_ACT_BRK_MOD_IDX_LIM_MASK   0x00001C00ul
#define BRUSHLESS33_PERI_CONFIG1_SPEED_RANGE_SEL_MASK       0x00000200ul
#define BRUSHLESS33_PERI_CONFIG1_ALARM_PIN_DIS_MASK         0x00000100ul

/**
 * @brief Brushless 33 GD_CONFIG1 register setting.
 * @details Specified setting for GD_CONFIG1 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_GD_CONFIG1_PARITY                       0x80000000ul
#define BRUSHLESS33_GD_CONFIG1_SLEW_RATE_MASK               0x0C000000ul
#define BRUSHLESS33_GD_CONFIG1_OVP_SEL_MASK                 0x00080000ul
#define BRUSHLESS33_GD_CONFIG1_OVP_EN_MASK                  0x00040000ul
#define BRUSHLESS33_GD_CONFIG1_OTW_REP_MASK                 0x00010000ul
#define BRUSHLESS33_GD_CONFIG1_OCP_DEG_MASK                 0x00003000ul
#define BRUSHLESS33_GD_CONFIG1_TRETRY_MASK                  0x00000800ul
#define BRUSHLESS33_GD_CONFIG1_OCP_LVL_MASK                 0x00000400ul
#define BRUSHLESS33_GD_CONFIG1_OCP_MODE_MASK                0x00000300ul
#define BRUSHLESS33_GD_CONFIG1_CSA_GAIN_MASK                0x00000001ul

/**
 * @brief Brushless 33 GD_CONFIG2 register setting.
 * @details Specified setting for GD_CONFIG2 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_GD_CONFIG2_PARITY                       0x80000000ul
#define BRUSHLESS33_GD_CONFIG2_DELAY_COMP_EN_MASK           0x40000000ul
#define BRUSHLESS33_GD_CONFIG2_TARGET_DELAY_MASK            0x3C000000ul
#define BRUSHLESS33_GD_CONFIG2_BUCK_SR_MASK                 0x02000000ul
#define BRUSHLESS33_GD_CONFIG2_BUCK_PS_DIS_MASK             0x01000000ul
#define BRUSHLESS33_GD_CONFIG2_BUCK_CL_MASK                 0x00800000ul
#define BRUSHLESS33_GD_CONFIG2_BUCK_SEL_MASK                0x00600000ul
#define BRUSHLESS33_GD_CONFIG2_BUCK_DIS_MASK                0x00100000ul

/**
 * @brief Brushless 33 INT_ALGO_1 register setting.
 * @details Specified setting for INT_ALGO_1 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_INT_ALGO_1_PARITY                       0x80000000ul
#define BRUSHLESS33_INT_ALGO_1_FG_ANGLE_INT_EN_MASK         0x20000000ul
#define BRUSHLESS33_INT_ALGO_1_SPEED_PIN_GL_FILTER_MASK     0x18000000ul
#define BRUSHLESS33_INT_ALGO_1_FAST_ISD_EN_MASK             0x04000000ul
#define BRUSHLESS33_INT_ALGO_1_ISD_STOP_TIME_MASK           0x03000000ul
#define BRUSHLESS33_INT_ALGO_1_ISD_RUN_TIME_MASK            0x00C00000ul
#define BRUSHLESS33_INT_ALGO_1_ISD_TIMEOUT_MASK             0x00300000ul
#define BRUSHLESS33_INT_ALGO_1_AUTO_HANDOFF_MIN_BEMF_MASK   0x000E0000ul
#define BRUSHLESS33_INT_ALGO_1_MPET_IPD_CURR_LIMIT_MASK     0x00006000ul
#define BRUSHLESS33_INT_ALGO_1_MPET_IPD_FREQ_MASK           0x00001800ul
#define BRUSHLESS33_INT_ALGO_1_MPET_OL_CURR_REF_MASK        0x00000700ul
#define BRUSHLESS33_INT_ALGO_1_MPET_OL_SPEED_REF_MASK       0x000000C0ul
#define BRUSHLESS33_INT_ALGO_1_MPET_OL_SLEW_RATE_MASK       0x00000038ul
#define BRUSHLESS33_INT_ALGO_1_REV_DRV_OL_DEC_MASK          0x00000007ul

/**
 * @brief Brushless 33 INT_ALGO_2 register setting.
 * @details Specified setting for INT_ALGO_2 register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_INT_ALGO_2_PARITY                       0x80000000ul
#define BRUSHLESS33_INT_ALGO_2_CL_SLOW_ACC_MASK             0x000003C0ul
#define BRUSHLESS33_INT_ALGO_2_ACT_BRK_BUS_CURR_S_RATE_MASK 0x00000038ul
#define BRUSHLESS33_INT_ALGO_2_MPET_IPD_SEL_MASK            0x00000004ul
#define BRUSHLESS33_INT_ALGO_2_MPET_KE_MEAS_PAR_SEL_MASK    0x00000002ul
#define BRUSHLESS33_INT_ALGO_2_IPD_HRES_EN_MASK             0x00000001ul

/**
 * @brief Brushless 33 FAULT_STATUS_GATE_DRIVER register setting.
 * @details Specified setting for FAULT_STATUS_GATE_DRIVER register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_DRIVER_FLT     0x80000000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_BK_FLT         0x40000000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_OCP            0x10000000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_NPOR           0x08000000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_OVP            0x04000000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_OT             0x02000000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_OTW            0x00800000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_TSD            0x00400000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_OCP_HC         0x00200000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_OCP_LC         0x00100000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_OCP_HB         0x00080000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_OCP_LB         0x00040000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_OCP_HA         0x00020000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_OCP_LA         0x00010000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_OTP_ERR        0x00004000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_BUCK_OCP       0x00002000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_BUCK_UV        0x00001000ul
#define BRUSHLESS33_FAULT_STATUS_GATE_DRIVER_VCP_UV         0x00000800ul

/**
 * @brief Brushless 33 FAULT_STATUS_GATE_DRIVER register setting.
 * @details Specified setting for FAULT_STATUS_GATE_DRIVER register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_CONTROLLER_FLT  0x80000000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_IPD_FREQ_FLT    0x20000000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_IPD_T1_FLT      0x10000000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_IPD_T2_FLT      0x08000000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_BUS_C_LIM_STAT  0x04000000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_MPET_IPD_FLT    0x02000000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_MPET_BEMF_FLT   0x01000000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_ABN_SPEED       0x00800000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_ABN_BEMF        0x00400000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_NO_MTR          0x00200000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_MTR_LCK         0x00100000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_LCK_ILIMIT      0x00080000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_HW_LOCK_ILIMIT  0x00040000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_MTR_UNDER_V     0x00020000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_MTR_OVER_V      0x00010000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_SPEED_LOOP_SAT  0x00008000ul
#define BRUSHLESS33_FAULT_STATUS_CONTROLLER_CURR_LOOP_SAT   0x00004000ul

/**
 * @brief Brushless 33 DEV_CTRL register setting.
 * @details Specified setting for DEV_CTRL register of Brushless 33 Click driver.
 */
#define BRUSHLESS33_DEV_CTRL_EEPROM_WRITE                   0x80000000ul
#define BRUSHLESS33_DEV_CTRL_EEPROM_READ                    0x40000000ul
#define BRUSHLESS33_DEV_CTRL_CLR_FLT                        0x20000000ul
#define BRUSHLESS33_DEV_CTRL_CLR_FLT_RETRY_CNT              0x10000000ul
#define BRUSHLESS33_DEV_CTRL_EERPOM_WRITE_ACCESS_KEY_MASK   0x0FF00000ul
#define BRUSHLESS33_DEV_CTRL_FORCED_ALIGN_ANGLE_MASK        0x000FF800ul
#define BRUSHLESS33_DEV_CTRL_WATCHDOG_TICKLE                0x00000400ul

/**
 * @brief Brushless 33 default register setting.
 * @details Specified default setting registers of Brushless 33 Click driver.
 * Speed controlled over PWM duty cycle, settings adjusted for A2212/13T 1000KV brushless motor. 
 */
#define BRUSHLESS33_DEFAULT_ISD_CONFIG                      0x74610C0Eul
#define BRUSHLESS33_DEFAULT_REV_DRIVE_CONFIG                0x28300000ul
#define BRUSHLESS33_DEFAULT_MOTOR_STARTUP1                  0x0F080DD0ul
#define BRUSHLESS33_DEFAULT_MOTOR_STARTUP2                  0x23066000ul
#define BRUSHLESS33_DEFAULT_CLOSED_LOOP1                    0x1C9981B4ul
#define BRUSHLESS33_DEFAULT_CLOSED_LOOP2                    0x4ADD320Ful
#define BRUSHLESS33_DEFAULT_CLOSED_LOOP3                    0x1800000Aul
#define BRUSHLESS33_DEFAULT_CLOSED_LOOP4                    0x218720D0ul
#define BRUSHLESS33_DEFAULT_SPEED_PROFILES1                 0x00000000ul
#define BRUSHLESS33_DEFAULT_SPEED_PROFILES2                 0x00000000ul
#define BRUSHLESS33_DEFAULT_SPEED_PROFILES3                 0x00000000ul
#define BRUSHLESS33_DEFAULT_SPEED_PROFILES4                 0x00000000ul
#define BRUSHLESS33_DEFAULT_SPEED_PROFILES5                 0x00000000ul
#define BRUSHLESS33_DEFAULT_SPEED_PROFILES6                 0x00000000ul
#define BRUSHLESS33_DEFAULT_FAULT_CONFIG1                   0x1FE80206ul
#define BRUSHLESS33_DEFAULT_FAULT_CONFIG2                   0x74000000ul
#define BRUSHLESS33_DEFAULT_PIN_CONFIG                      0x00000001ul
#define BRUSHLESS33_DEFAULT_DEVICE_CONFIG1                  0x00100000ul
#define BRUSHLESS33_DEFAULT_DEVICE_CONFIG2                  0x0000B000ul
#define BRUSHLESS33_DEFAULT_PERI_CONFIG1                    0x40000000ul
#define BRUSHLESS33_DEFAULT_GD_CONFIG1                      0x00000100ul
#define BRUSHLESS33_DEFAULT_GD_CONFIG2                      0x00200000ul
#define BRUSHLESS33_DEFAULT_INT_ALGO_1                      0x00B2407Dul
#define BRUSHLESS33_DEFAULT_INT_ALGO_2                      0x000001A7ul

/**
 * @brief Brushless 33 control word setting.
 * @details Specified setting for control word of Brushless 33 Click driver.
 */
#define BRUSHLESS33_CTRL_READ_BIT                           0x80
#define BRUSHLESS33_CTRL_CRC_DISABLE                        0x00
#define BRUSHLESS33_CTRL_CRC_ENABLE                         0x01
#define BRUSHLESS33_CTRL_CRC_MASK                           0x01
#define BRUSHLESS33_CTRL_DLEN_16_BIT                        0x00
#define BRUSHLESS33_CTRL_DLEN_32_BIT                        0x01
#define BRUSHLESS33_CTRL_DLEN_64_BIT                        0x02
#define BRUSHLESS33_CTRL_DLEN_MASK                          0x03
#define BRUSHLESS33_I2C_READ_BIT                            0x01

/**
 * @brief Brushless 33 direction settings.
 * @details Specified setting for direction of Brushless 31 Click driver.
 */
#define BRUSHLESS33_DIR_CCW                                 0
#define BRUSHLESS33_DIR_CW                                  1

/**
 * @brief Brushless 33 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 33 Click driver.
 */
#define BRUSHLESS33_DEVICE_ADDRESS                          0x01

/**
 * @brief Brushless 33 default PWM frequency.
 * @details Specified setting for default PWM frequency of Brushless 33 Click driver.
 */
#define BRUSHLESS33_DEF_FREQ                                5000

/*! @} */ // brushless33_set

/**
 * @defgroup brushless33_map Brushless 33 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 33 Click driver.
 */

/**
 * @addtogroup brushless33_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 33 Click to the selected MikroBUS.
 */
#define BRUSHLESS33_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.brake = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.speed = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless33_map
/*! @} */ // brushless33

/**
 * @brief Brushless 33 Click context object.
 * @details Context object definition of Brushless 33 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t brake;        /**< Brake control pin (active high). */
    digital_out_t dir;          /**< Direction control pin (low - CCW, high - CW). */

    // Input pins
    digital_in_t fault;         /**< Fault indication pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */
    pwm_t pwm;                  /**< PWM driver object. */

    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    uint32_t pwm_freq;          /**< PWM frequency value. */

    uint8_t crc_en;             /**< CRC enable flag. */

} brushless33_t;

/**
 * @brief Brushless 33 Click configuration object.
 * @details Configuration object definition of Brushless 33 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t speed;           /**< Speed input PWM pin. */

    pin_name_t brake;           /**< Brake control pin (active high). */
    pin_name_t dir;             /**< Direction control pin (low - CCW, high - CW). */
    pin_name_t fault;           /**< Fault indication pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

    uint32_t   dev_pwm_freq;    /**< PWM frequency value. */

} brushless33_cfg_t;

/**
 * @brief Brushless 33 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS33_OK = 0,
    BRUSHLESS33_ERROR = -1

} brushless33_return_value_t;

/*!
 * @addtogroup brushless33 Brushless 33 Click Driver
 * @brief API for configuring and manipulating Brushless 33 Click driver.
 * @{
 */

/**
 * @brief Brushless 33 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless33_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless33_cfg_setup ( brushless33_cfg_t *cfg );

/**
 * @brief Brushless 33 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless33_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_init ( brushless33_t *ctx, brushless33_cfg_t *cfg );

/**
 * @brief Brushless 33 default configuration function.
 * @details This function executes a default configuration of Brushless 33
 * Click board.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless33_default_cfg ( brushless33_t *ctx );

/**
 * @brief Brushless 33 write reg 16 function.
 * @details This function writes a 16-bit data to the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_write_reg_16 ( brushless33_t *ctx, uint32_t mem_addr, uint16_t data_in );

/**
 * @brief Brushless 33 write reg 32 function.
 * @details This function writes a 32-bit data to the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[in] data_in : 32-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_write_reg_32 ( brushless33_t *ctx, uint32_t mem_addr, uint32_t data_in );

/**
 * @brief Brushless 33 write reg 64 function.
 * @details This function writes a 64-bit data starting from the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[in] data_in_msb : 32-bit MSB data to be written.
 * @param[in] data_in_lsb : 32-bit LSB data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_write_reg_64 ( brushless33_t *ctx, uint32_t mem_addr, uint32_t data_in_msb, uint32_t data_in_lsb );

/**
 * @brief Brushless 33 read reg 16 function.
 * @details This function reads a 16-bit data from the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[out] data_out : 16-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_read_reg_16 ( brushless33_t *ctx, uint32_t mem_addr, uint16_t *data_out );

/**
 * @brief Brushless 33 read reg 32 function.
 * @details This function reads a 32-bit data from the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[out] data_out : 32-bit output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_read_reg_32 ( brushless33_t *ctx, uint32_t mem_addr, uint32_t *data_out );

/**
 * @brief Brushless 33 read reg 64 function.
 * @details This function reads a 64-bit data starting from the selected memory address by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @param[in] mem_addr : 20-bit memory address.
 * @param[out] data_out_msb : 32-bit MSB output read data.
 * @param[out] data_out_lsb : 32-bit LSB output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_read_reg_64 ( brushless33_t *ctx, uint32_t mem_addr, uint32_t *data_out_msb, uint32_t *data_out_lsb );

/**
 * @brief Brushless 33 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_set_duty_cycle ( brushless33_t *ctx, float duty_cycle );

/**
 * @brief Brushless 33 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_pwm_stop ( brushless33_t *ctx );

/**
 * @brief Brushless 33 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_pwm_start ( brushless33_t *ctx );

/**
 * @brief Brushless 33 set direction function.
 * @details This function sets the direction of motor rotation by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - CCW,
 *                  @li @c 1 - CW.
 * @return None.
 * @note None.
 */
void brushless33_set_direction ( brushless33_t *ctx, uint8_t dir );

/**
 * @brief Brushless 33 switch direction function.
 * @details This function switches the direction of motor rotation by toggling the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless33_switch_direction ( brushless33_t *ctx );

/**
 * @brief Brushless 33 pull brake function.
 * @details This function pulls brake by setting the BRAKE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless33_pull_brake ( brushless33_t *ctx );

/**
 * @brief Brushless 33 release brake function.
 * @details This function releases brake by setting the BRAKE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless33_release_brake ( brushless33_t *ctx );

/**
 * @brief Brushless 33 get fault pin function.
 * @details This function returns the fault indication pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t brushless33_get_fault_pin ( brushless33_t *ctx );

/**
 * @brief Brushless 33 read fault function.
 * @details This function reads gate driver and controller fault registers.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @param[out] gate_drv_flt : Gate driver fault.
 * @param[out] controller_flt : Controller fault.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_read_fault ( brushless33_t *ctx, uint32_t *gate_drv_flt, uint32_t *controller_flt );

/**
 * @brief Brushless 33 clear fault function.
 * @details This function clears gate driver and controller fault registers.
 * @param[in] ctx : Click context object.
 * See #brushless33_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless33_clear_fault ( brushless33_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS33_H

/*! @} */ // brushless33

// ------------------------------------------------------------------------ END
