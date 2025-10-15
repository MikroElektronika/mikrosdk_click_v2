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
 * @file charger30.h
 * @brief This file contains API for Charger 30 Click Driver.
 */

#ifndef CHARGER30_H
#define CHARGER30_H

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

/*!
 * @addtogroup charger30 Charger 30 Click Driver
 * @brief API for configuring and manipulating Charger 30 Click driver.
 * @{
 */

/**
 * @defgroup charger30_reg Charger 30 Registers List
 * @brief List of registers of Charger 30 Click driver.
 */

/**
 * @addtogroup charger30_reg
 * @{
 */

/**
 * @brief Charger 30 register map.
 * @details Specified register map of Charger 30 Click driver.
 */
#define CHARGER30_REG_INPUT_CURRENT_LIMIT           0x00
#define CHARGER30_REG_INPUT_VOLTAGE_REG             0x01
#define CHARGER30_REG_NTC_CONFIG_THERMAL_REG        0x02
#define CHARGER30_REG_ADC_CTRL_OTG_CONFIG           0x03
#define CHARGER30_REG_CHARGE_CTRL_VSYS_CONFIG       0x04
#define CHARGER30_REG_CHARGE_CURRENT_CONFIG         0x05
#define CHARGER30_REG_PRE_CHARGE_TERM_CURRENT       0x06
#define CHARGER30_REG_CHARGE_VOLTAGE_REG            0x07
#define CHARGER30_REG_TIMER_CONFIG                  0x08
#define CHARGER30_REG_BANDGAP                       0x09
#define CHARGER30_REG_BATFET_CONFIG                 0x0A
#define CHARGER30_REG_INT_MASK_USB_DETECTION        0x0B
#define CHARGER30_REG_STATUS                        0x0C
#define CHARGER30_REG_FAULT                         0x0D
#define CHARGER30_REG_BATTERY_VOLTAGE_ADC           0x0E
#define CHARGER30_REG_SYSTEM_VOLTAGE_ADC            0x0F
#define CHARGER30_REG_NTC_VOLTAGE_ADC               0x10
#define CHARGER30_REG_INPUT_VOLTAGE_ADC             0x11
#define CHARGER30_REG_CHARGE_CURRENT_ADC            0x12
#define CHARGER30_REG_INPUT_CURRENT_ADC             0x13
#define CHARGER30_REG_POWER_MANAGEMENT_STATUS       0x14
#define CHARGER30_REG_DPM_MASK                      0x15
#define CHARGER30_REG_JEITA_CONFIG                  0x16
#define CHARGER30_REG_SAFETY_TIMER_STATUS_PART_NUM  0x17

/*! @} */ // charger30_reg

/**
 * @defgroup charger30_set Charger 30 Registers Settings
 * @brief Settings for registers of Charger 30 Click driver.
 */

/**
 * @addtogroup charger30_set
 * @{
 */

/**
 * @brief Charger 30 INPUT_CURRENT_LIMIT register setting.
 * @details Specified setting for INPUT_CURRENT_LIMIT register of Charger 30 Click driver.
 */
#define CHARGER30_ICL_EN_HIZ_DISABLE                0x00
#define CHARGER30_ICL_EN_HIZ_ENABLE                 0x80
#define CHARGER30_ICL_EN_HIZ_MASK                   0x80
#define CHARGER30_ICL_EN_LIM_DISABLE                0x00
#define CHARGER30_ICL_EN_LIM_ENABLE                 0x40
#define CHARGER30_ICL_EN_LIM_MASK                   0x40
#define CHARGER30_ICL_IIN_LIM_MASK                  0x3F
#define CHARGER30_ICL_IIN_LIM_MA_RES                50
#define CHARGER30_ICL_IIN_LIM_MA_OFFSET             100
#define CHARGER30_ICL_IIN_LIM_MA_MIN                100
#define CHARGER30_ICL_IIN_LIM_MA_DEFAULT            500
#define CHARGER30_ICL_IIN_LIM_MA_MAX                3250
#define CHARGER30_ICL_IIN_LIM_MA(x)                 ( ( ( x - CHARGER30_ICL_IIN_LIM_MA_OFFSET ) / \
                                                        CHARGER30_ICL_IIN_LIM_MA_RES ) & CHARGER30_ICL_IIN_LIM_MASK )

/**
 * @brief Charger 30 INPUT_VOLTAGE_REG register setting.
 * @details Specified setting for INPUT_VOLTAGE_REG register of Charger 30 Click driver.
 */
#define CHARGER30_IVR_REG_RESET_KEEP                0x00
#define CHARGER30_IVR_REG_RESET_RESET               0x80
#define CHARGER30_IVR_REG_RESET_MASK                0x80
#define CHARGER30_IVR_VIN_MIN_MASK                  0x7F
#define CHARGER30_IVR_VIN_MIN_MV_RES                100
#define CHARGER30_IVR_VIN_MIN_MV_OFFSET             3700
#define CHARGER30_IVR_VIN_MIN_MV_MIN                3700
#define CHARGER30_IVR_VIN_MIN_MV_DEFAULT            4300
#define CHARGER30_IVR_VIN_MIN_MV_MAX                15200
#define CHARGER30_IVR_VIN_MIN_MV(x)                 ( ( ( x - CHARGER30_IVR_VIN_MIN_MV_OFFSET ) / \
                                                        CHARGER30_IVR_VIN_MIN_MV_RES ) & CHARGER30_IVR_VIN_MIN_MASK )

/**
 * @brief Charger 30 NTC_CONFIG_THERMAL_REG register setting.
 * @details Specified setting for NTC_CONFIG_THERMAL_REG register of Charger 30 Click driver.
 */
#define CHARGER30_NCTR_TSM_DLY_NO_DELAY             0x00
#define CHARGER30_NCTR_TSM_DLY_10S                  0x80
#define CHARGER30_NCTR_TSM_DLY_MASK                 0x80
#define CHARGER30_NCTR_NTC_TYPE_STANDARD            0x00
#define CHARGER30_NCTR_NTC_TYPE_JEITA               0x40
#define CHARGER30_NCTR_NTC_TYPE_MASK                0x40
#define CHARGER30_NCTR_EN_OTG_NTC_DISABLE           0x00
#define CHARGER30_NCTR_EN_OTG_NTC_ENABLE            0x20
#define CHARGER30_NCTR_EN_OTG_NTC_MASK              0x20
#define CHARGER30_NCTR_EN_CHG_NTC_DISABLE           0x00
#define CHARGER30_NCTR_EN_CHG_NTC_ENABLE            0x10
#define CHARGER30_NCTR_EN_CHG_NTC_MASK              0x10
#define CHARGER30_NCTR_TJ_REG_60C                   0x00
#define CHARGER30_NCTR_TJ_REG_80C                   0x04
#define CHARGER30_NCTR_TJ_REG_100C                  0x08
#define CHARGER30_NCTR_TJ_REG_120C                  0x0C
#define CHARGER30_NCTR_TJ_REG_MASK                  0x0C
#define CHARGER30_NCTR_NTC_OPT_BATTERY              0x00
#define CHARGER30_NCTR_NTC_OPT_PCB                  0x02
#define CHARGER30_NCTR_NTC_OPT_MASK                 0x02
#define CHARGER30_NCTR_AICO_EN_DISABLE              0x00
#define CHARGER30_NCTR_AICO_EN_ENABLE               0x01
#define CHARGER30_NCTR_AICO_EN_MASK                 0x01

/**
 * @brief Charger 30 ADC_CTRL_OTG_CONFIG register setting.
 * @details Specified setting for ADC_CTRL_OTG_CONFIG register of Charger 30 Click driver.
 */
#define CHARGER30_ACOC_ADC_START_DISABLE            0x00
#define CHARGER30_ACOC_ADC_START_ENABLE             0x80
#define CHARGER30_ACOC_ADC_START_MASK               0x80
#define CHARGER30_ACOC_ADC_RATE_ONE_SHOT            0x00
#define CHARGER30_ACOC_ADC_RATE_CONTINUOUS          0x40
#define CHARGER30_ACOC_ADC_RATE_MASK                0x40
#define CHARGER30_ACOC_VIN_DSCHG_4800MV             0x00
#define CHARGER30_ACOC_VIN_DSCHG_4900MV             0x08
#define CHARGER30_ACOC_VIN_DSCHG_5000MV             0x10
#define CHARGER30_ACOC_VIN_DSCHG_5100MV             0x18
#define CHARGER30_ACOC_VIN_DSCHG_5200MV             0x20
#define CHARGER30_ACOC_VIN_DSCHG_5300MV             0x28
#define CHARGER30_ACOC_VIN_DSCHG_5400MV             0x30
#define CHARGER30_ACOC_VIN_DSCHG_5500MV             0x38
#define CHARGER30_ACOC_VIN_DSCHG_MASK               0x38
#define CHARGER30_ACOC_IIN_DSCHG_500MA              0x00
#define CHARGER30_ACOC_IIN_DSCHG_800MA              0x01
#define CHARGER30_ACOC_IIN_DSCHG_1100MA             0x02
#define CHARGER30_ACOC_IIN_DSCHG_1500MA             0x03
#define CHARGER30_ACOC_IIN_DSCHG_1800MA             0x04
#define CHARGER30_ACOC_IIN_DSCHG_2100MA             0x05
#define CHARGER30_ACOC_IIN_DSCHG_2400MA             0x06
#define CHARGER30_ACOC_IIN_DSCHG_3000MA             0x07
#define CHARGER30_ACOC_IIN_DSCHG_MASK               0x07

/**
 * @brief Charger 30 CHARGE_CTRL_VSYS_CONFIG register setting.
 * @details Specified setting for CHARGE_CTRL_VSYS_CONFIG register of Charger 30 Click driver.
 */
#define CHARGER30_CCVC_BAT_LOADEN_DISABLE           0x00
#define CHARGER30_CCVC_BAT_LOADEN_ENABLE            0x80
#define CHARGER30_CCVC_BAT_LOADEN_MASK              0x80
#define CHARGER30_CCVC_STAT_EN_DISABLE              0x00
#define CHARGER30_CCVC_STAT_EN_ENABLE               0x40
#define CHARGER30_CCVC_STAT_EN_MASK                 0x40
#define CHARGER30_CCVC_CHG_CONFIG_CHARGE_DISABLE    0x00
#define CHARGER30_CCVC_CHG_CONFIG_CHARGE_ENABLE     0x10
#define CHARGER30_CCVC_CHG_CONFIG_OTG               0x30
#define CHARGER30_CCVC_CHG_CONFIG_MASK              0x30
#define CHARGER30_CCVC_VSYS_MIN_3000MV              0x00
#define CHARGER30_CCVC_VSYS_MIN_3150MV              0x02
#define CHARGER30_CCVC_VSYS_MIN_3300MV              0x04
#define CHARGER30_CCVC_VSYS_MIN_3450MV              0x06
#define CHARGER30_CCVC_VSYS_MIN_3525MV              0x08
#define CHARGER30_CCVC_VSYS_MIN_3600MV              0x0A
#define CHARGER30_CCVC_VSYS_MIN_3675MV              0x0C
#define CHARGER30_CCVC_VSYS_MIN_3750MV              0x0E
#define CHARGER30_CCVC_VSYS_MIN_MASK                0x0E
#define CHARGER30_CCVC_VTRACK_100MV                 0x00
#define CHARGER30_CCVC_VTRACK_150MV                 0x01
#define CHARGER30_CCVC_VTRACK_MASK                  0x01

/**
 * @brief Charger 30 CHARGE_CURRENT_CONFIG register setting.
 * @details Specified setting for CHARGE_CURRENT_CONFIG register of Charger 30 Click driver.
 */
#define CHARGER30_CCC_VBATT_PRE_2800MV              0x00
#define CHARGER30_CCC_VBATT_PRE_3000MV              0x80
#define CHARGER30_CCC_VBATT_PRE_MASK                0x80
#define CHARGER30_CCC_ICC_MASK                      0x7F
#define CHARGER30_CCC_ICC_MA_RES                    40
#define CHARGER30_CCC_ICC_MA_OFFSET                 320
#define CHARGER30_CCC_ICC_MA_MIN                    320
#define CHARGER30_CCC_ICC_MA_DEFAULT                1840
#define CHARGER30_CCC_ICC_MA_MAX                    4520
#define CHARGER30_CCC_ICC_MA(x)                     ( ( ( x - CHARGER30_CCC_ICC_MA_OFFSET ) / \
                                                        CHARGER30_CCC_ICC_MA_RES ) & CHARGER30_CCC_ICC_MASK )

/**
 * @brief Charger 30 PRE_CHARGE_TERM_CURRENT register setting.
 * @details Specified setting for PRE_CHARGE_TERM_CURRENT register of Charger 30 Click driver.
 */
#define CHARGER30_PCTC_IPRE_MASK                    0xF0
#define CHARGER30_PCTC_IPRE_SHIFT                   4
#define CHARGER30_PCTC_IPRE_MA_RES                  40
#define CHARGER30_PCTC_IPRE_MA_OFFSET               150
#define CHARGER30_PCTC_IPRE_MA_MIN                  150
#define CHARGER30_PCTC_IPRE_MA_DEFAULT              300
#define CHARGER30_PCTC_IPRE_MA_MAX                  750
#define CHARGER30_PCTC_IPRE_MA(x)                   ( ( ( ( x - CHARGER30_PCTC_IPRE_MA_OFFSET ) / \
                                                          CHARGER30_PCTC_IPRE_MA_RES ) << CHARGER30_PCTC_IPRE_SHIFT ) & \
                                                      CHARGER30_PCTC_IPRE_MASK )
#define CHARGER30_PCTC_ITERM_MASK                   0x0F
#define CHARGER30_PCTC_ITERM_MA_RES                 40
#define CHARGER30_PCTC_ITERM_MA_OFFSET              120
#define CHARGER30_PCTC_ITERM_MA_MIN                 120
#define CHARGER30_PCTC_ITERM_MA_DEFAULT             200
#define CHARGER30_PCTC_ITERM_MA_MAX                 720
#define CHARGER30_PCTC_ITERM_MA(x)                  ( ( ( x - CHARGER30_PCTC_ITERM_MA_OFFSET ) / \
                                                        CHARGER30_PCTC_ITERM_MA_RES ) & CHARGER30_PCTC_ITERM_MASK )

/**
 * @brief Charger 30 CHARGE_VOLTAGE_REG register setting.
 * @details Specified setting for CHARGE_VOLTAGE_REG register of Charger 30 Click driver.
 */
#define CHARGER30_CVR_VBATT_REG_MASK                0xFE
#define CHARGER30_CVR_VBATT_REG_SHIFT               1
#define CHARGER30_CVR_VBATT_REG_MV_RES              10
#define CHARGER30_CVR_VBATT_REG_MV_OFFSET           3400
#define CHARGER30_CVR_VBATT_REG_MV_MIN              3400
#define CHARGER30_CVR_VBATT_REG_MV_DEFAULT          4200
#define CHARGER30_CVR_VBATT_REG_MV_MAX              4670
#define CHARGER30_CVR_VBATT_REG_MV(x)               ( ( ( ( x - CHARGER30_CVR_VBATT_REG_MV_OFFSET ) / \
                                                          CHARGER30_CVR_VBATT_REG_MV_RES ) << CHARGER30_CVR_VBATT_REG_SHIFT ) & \
                                                      CHARGER30_CVR_VBATT_REG_MASK )
#define CHARGER30_CVR_VRECH_100MV                   0x00
#define CHARGER30_CVR_VRECH_200MV                   0x01
#define CHARGER30_CVR_VRECH_MASK                    0x01

/**
 * @brief Charger 30 TIMER_CONFIG register setting.
 * @details Specified setting for TIMER_CONFIG register of Charger 30 Click driver.
 */
#define CHARGER30_TC_EN_TERM_DISABLE                0x00
#define CHARGER30_TC_EN_TERM_ENABLE                 0x80
#define CHARGER30_TC_EN_TERM_MASK                   0x80
#define CHARGER30_TC_WATCHDOG_DISABLE               0x00
#define CHARGER30_TC_WATCHDOG_40S                   0x10
#define CHARGER30_TC_WATCHDOG_80S                   0x20
#define CHARGER30_TC_WATCHDOG_160S                  0x30
#define CHARGER30_TC_WATCHDOG_MASK                  0x30
#define CHARGER30_TC_WATCHDOG_RESET_NORMAL          0x00
#define CHARGER30_TC_WATCHDOG_RESET_RESET           0x08
#define CHARGER30_TC_WATCHDOG_RESET_MASK            0x08
#define CHARGER30_TC_CHG_TMR_5HRS                   0x00
#define CHARGER30_TC_CHG_TMR_8HRS                   0x02
#define CHARGER30_TC_CHG_TMR_12HRS                  0x04
#define CHARGER30_TC_CHG_TMR_20HRS                  0x06
#define CHARGER30_TC_CHG_TMR_MASK                   0x06
#define CHARGER30_TC_EN_TIMER_DISABLE               0x00
#define CHARGER30_TC_EN_TIMER_ENABLE                0x01
#define CHARGER30_TC_EN_TIMER_MASK                  0x01

/**
 * @brief Charger 30 BANDGAP register setting.
 * @details Specified setting for BANDGAP register of Charger 30 Click driver.
 */
#define CHARGER30_BANDGAP_ENABLE                    0x00
#define CHARGER30_BANDGAP_DISABLE                   0x08
#define CHARGER30_BANDGAP_MASK                      0x08

/**
 * @brief Charger 30 BATFET_CONFIG register setting.
 * @details Specified setting for BATFET_CONFIG register of Charger 30 Click driver.
 */
#define CHARGER30_BC_SW_FREQ_1_35MHZ                0x00
#define CHARGER30_BC_SW_FREQ_1_MHZ                  0x80
#define CHARGER30_BC_SW_FREQ_MASK                   0x80
#define CHARGER30_BC_TMR2X_EN_DISABLE               0x00
#define CHARGER30_BC_TMR2X_EN_ENABLE                0x40
#define CHARGER30_BC_TMR2X_EN_MASK                  0x40
#define CHARGER30_BC_BATFET_DIS_ALLOW_ON            0x00
#define CHARGER30_BC_BATFET_DIS_FORCE_OFF           0x20
#define CHARGER30_BC_BATFET_DIS_MASK                0x20
#define CHARGER30_BC_SYSRST_SEL_HW                  0x00
#define CHARGER30_BC_SYSRST_SEL_SW                  0x10
#define CHARGER30_BC_SYSRST_SEL_MASK                0x10
#define CHARGER30_BC_TDISC_H_0_5S                   0x00
#define CHARGER30_BC_TDISC_H_2S                     0x04
#define CHARGER30_BC_TDISC_H_4S                     0x08
#define CHARGER30_BC_TDISC_H_8S                     0x0C
#define CHARGER30_BC_TDISC_H_MASK                   0x0C
#define CHARGER30_BC_TDISC_L_8S                     0x00
#define CHARGER30_BC_TDISC_L_10S                    0x01
#define CHARGER30_BC_TDISC_L_12S                    0x02
#define CHARGER30_BC_TDISC_L_16S                    0x03
#define CHARGER30_BC_TDISC_L_MASK                   0x03

/**
 * @brief Charger 30 INT_MASK_USB_DETECTION register setting.
 * @details Specified setting for INT_MASK_USB_DETECTION register of Charger 30 Click driver.
 */
#define CHARGER30_IMUD_INT_SAFETY_TIMER_DISABLE     0x00
#define CHARGER30_IMUD_INT_SAFETY_TIMER_ENABLE      0x80
#define CHARGER30_IMUD_INT_SAFETY_TIMER_MASK        0x80
#define CHARGER30_IMUD_INT_BAT_FAULT_DISABLE        0x00
#define CHARGER30_IMUD_INT_BAT_FAULT_ENABLE         0x40
#define CHARGER30_IMUD_INT_BAT_FAULT_MASK           0x40
#define CHARGER30_IMUD_USB_DET_EN_DISABLE           0x00
#define CHARGER30_IMUD_USB_DET_EN_ENABLE            0x20
#define CHARGER30_IMUD_USB_DET_EN_MASK              0x20
#define CHARGER30_IMUD_DM_3300MV                    0x00
#define CHARGER30_IMUD_DM_600MV                     0x10
#define CHARGER30_IMUD_DM_MASK                      0x10
#define CHARGER30_IMUD_DP_600MV                     0x00
#define CHARGER30_IMUD_DP_3300MV                    0x08
#define CHARGER30_IMUD_DP_MASK                      0x08
#define CHARGER30_IMUD_USB_FAST_CHG_DP_L_DM_HIZ     0x00
#define CHARGER30_IMUD_USB_FAST_CHG_DP_H_DM_L       0x02
#define CHARGER30_IMUD_USB_FAST_CHG_DP_L_DM_L       0x04
#define CHARGER30_IMUD_USB_FAST_CHG_DP_L_DM_H       0x06
#define CHARGER30_IMUD_USB_FAST_CHG_MASK            0x06
#define CHARGER30_IMUD_USB_FAST_CHG_RESET_VDP_SRC   0x00
#define CHARGER30_IMUD_USB_FAST_CHG_RESET_ZERO      0x01
#define CHARGER30_IMUD_USB_FAST_CHG_RESET_MASK      0x01

/**
 * @brief Charger 30 STATUS register setting.
 * @details Specified setting for STATUS register of Charger 30 Click driver.
 */
#define CHARGER30_STATUS_VIN_STAT_NO_INPUT          0x00
#define CHARGER30_STATUS_VIN_STAT_NONSTANDARD_ADAPT 0x20
#define CHARGER30_STATUS_VIN_STAT_SDP               0x40
#define CHARGER30_STATUS_VIN_STAT_CDP               0x60
#define CHARGER30_STATUS_VIN_STAT_DCP               0x80
#define CHARGER30_STATUS_VIN_STAT_FAST_CHARGE       0xA0
#define CHARGER30_STATUS_VIN_STAT_OTG               0xE0
#define CHARGER30_STATUS_VIN_STAT_MASK              0xE0
#define CHARGER30_STATUS_CHG_STAT_NOT_CHARGING      0x00
#define CHARGER30_STATUS_CHG_STAT_TRICKLE_CHARGE    0x08
#define CHARGER30_STATUS_CHG_STAT_CC_CHARGE         0x10
#define CHARGER30_STATUS_CHG_STAT_CHARGE_DONE       0x18
#define CHARGER30_STATUS_CHG_STAT_MASK              0x18
#define CHARGER30_STATUS_NTC_FLOAT_NO_FLOAT         0x00
#define CHARGER30_STATUS_NTC_FLOAT_FLOAT            0x04
#define CHARGER30_STATUS_NTC_FLOAT_MASK             0x04
#define CHARGER30_STATUS_THERM_STAT_NORMAL          0x00
#define CHARGER30_STATUS_THERM_STAT_THERMAL_REG     0x02
#define CHARGER30_STATUS_THERM_STAT_MASK            0x02
#define CHARGER30_STATUS_VSYS_STAT_IN_REG           0x00
#define CHARGER30_STATUS_VSYS_STAT_NOT_IN_REG       0x01
#define CHARGER30_STATUS_VSYS_STAT_MASK             0x01

/**
 * @brief Charger 30 FAULT register setting.
 * @details Specified setting for FAULT register of Charger 30 Click driver.
 */
#define CHARGER30_FAULT_WATCHDOG                    0x80
#define CHARGER30_FAULT_OTG                         0x40
#define CHARGER30_FAULT_INPUT                       0x20
#define CHARGER30_FAULT_THERMAL_SHUTDOWN            0x10
#define CHARGER30_FAULT_BAT                         0x08
#define CHARGER30_FAULT_NTC_NORMAL                  0x00
#define CHARGER30_FAULT_NTC_WARM                    0x02
#define CHARGER30_FAULT_NTC_COOL                    0x03
#define CHARGER30_FAULT_NTC_COLD                    0x05
#define CHARGER30_FAULT_NTC_HOT                     0x06
#define CHARGER30_FAULT_NTC_MASK                    0x07

/**
 * @brief Charger 30 BATTERY_VOLTAGE_ADC register setting.
 * @details Specified setting for BATTERY_VOLTAGE_ADC register of Charger 30 Click driver.
 */
#define CHARGER30_VBAT_ADC_TO_MV_RES                20
#define CHARGER30_VBAT_ADC_TO_MV(x)                 ( ( uint16_t ) x * CHARGER30_VBAT_ADC_TO_MV_RES )

/**
 * @brief Charger 30 SYSTEM_VOLTAGE_ADC register setting.
 * @details Specified setting for SYSTEM_VOLTAGE_ADC register of Charger 30 Click driver.
 */
#define CHARGER30_VSYS_ADC_TO_MV_RES                20
#define CHARGER30_VSYS_ADC_TO_MV(x)                 ( ( uint16_t ) x * CHARGER30_VSYS_ADC_TO_MV_RES )

/**
 * @brief Charger 30 NTC_VOLTAGE_ADC register setting.
 * @details Specified setting for NTC_VOLTAGE_ADC register of Charger 30 Click driver.
 */
#define CHARGER30_NTC_ADC_TO_PCT_RES                0.392
#define CHARGER30_NTC_ADC_TO_PCT(x)                 ( x * CHARGER30_NTC_ADC_TO_PCT_RES )

/**
 * @brief Charger 30 INPUT_VOLTAGE_ADC register setting.
 * @details Specified setting for INPUT_VOLTAGE_ADC register of Charger 30 Click driver.
 */
#define CHARGER30_VIN_ADC_TO_MV_RES                 60
#define CHARGER30_VIN_ADC_TO_MV(x)                  ( ( uint16_t ) x * CHARGER30_VIN_ADC_TO_MV_RES )

/**
 * @brief Charger 30 INPUT_VOLTAGE_ADC register setting.
 * @details Specified setting for INPUT_VOLTAGE_ADC register of Charger 30 Click driver.
 */
#define CHARGER30_VIN_ADC_TO_MV_RES                 60
#define CHARGER30_VIN_ADC_TO_MV(x)                  ( ( uint16_t ) x * CHARGER30_VIN_ADC_TO_MV_RES )

/**
 * @brief Charger 30 CHARGE_CURRENT_ADC register setting.
 * @details Specified setting for CHARGE_CURRENT_ADC register of Charger 30 Click driver.
 */
#define CHARGER30_ICHG_ADC_TO_MA_RES                17.5
#define CHARGER30_ICHG_ADC_TO_MA(x)                 ( x * CHARGER30_ICHG_ADC_TO_MA_RES )

/**
 * @brief Charger 30 INPUT_CURRENT_ADC register setting.
 * @details Specified setting for INPUT_CURRENT_ADC register of Charger 30 Click driver.
 */
#define CHARGER30_IIN_ADC_TO_MA_RES                 13.3
#define CHARGER30_IIN_ADC_TO_MA(x)                  ( x * CHARGER30_IIN_ADC_TO_MA_RES )

/**
 * @brief Charger 30 POWER_MANAGEMENT_STATUS register setting.
 * @details Specified setting for POWER_MANAGEMENT_STATUS register of Charger 30 Click driver.
 */
#define CHARGER30_PMS_VINPPM_STAT                   0x80
#define CHARGER30_PMS_IINPPM_STAT                   0x40
#define CHARGER30_PMS_IIN_DPM_MASK                  0x3F
#define CHARGER30_PMS_IIN_DPM_ADC_TO_MA_RES         50
#define CHARGER30_PMS_IIN_DPM_ADC_TO_MA_OFFSET      100
#define CHARGER30_PMS_IIN_DPM_ADC_TO_MA(x)          ( ( x & CHARGER30_PMS_IIN_DPM_MASK ) * CHARGER30_PMS_IIN_DPM_ADC_TO_MA_RES + \
                                                      CHARGER30_PMS_IIN_DPM_ADC_TO_MA_OFFSET )

/**
 * @brief Charger 30 DPM_MASK register setting.
 * @details Specified setting for DPM_MASK register of Charger 30 Click driver.
 */
#define CHARGER30_DM_AICO_STAT                      0x80
#define CHARGER30_DM_VINPPM_INT_DISABLE             0x00
#define CHARGER30_DM_VINPPM_INT_ENABLE              0x40
#define CHARGER30_DM_VINPPM_INT_MASK                0x40
#define CHARGER30_DM_IINPPM_INT_DISABLE             0x00
#define CHARGER30_DM_IINPPM_INT_ENABLE              0x20
#define CHARGER30_DM_IINPPM_INT_MASK                0x20

/**
 * @brief Charger 30 JEITA_CONFIG register setting.
 * @details Specified setting for JEITA_CONFIG register of Charger 30 Click driver.
 */
#define CHARGER30_JC_JEITA_VSET_100MV               0x00
#define CHARGER30_JC_JEITA_VSET_200MV               0x80
#define CHARGER30_JC_JEITA_VSET_MASK                0x80
#define CHARGER30_JC_JEITA_ISET_50PCT               0x00
#define CHARGER30_JC_JEITA_ISET_16_7PCT             0x40
#define CHARGER30_JC_JEITA_ISET_MASK                0x40
#define CHARGER30_JC_VTH_HOT_60C                    0x00
#define CHARGER30_JC_VTH_HOT_55C                    0x20
#define CHARGER30_JC_VTH_HOT_MASK                   0x20
#define CHARGER30_JC_VTH_WARM_40C                   0x00
#define CHARGER30_JC_VTH_WARM_45C                   0x08
#define CHARGER30_JC_VTH_WARM_50C                   0x10
#define CHARGER30_JC_VTH_WARM_55C                   0x18
#define CHARGER30_JC_VTH_WARM_MASK                  0x18
#define CHARGER30_JC_VTH_COOL_0C                    0x00
#define CHARGER30_JC_VTH_COOL_5C                    0x02
#define CHARGER30_JC_VTH_COOL_10C                   0x04
#define CHARGER30_JC_VTH_COOL_15C                   0x06
#define CHARGER30_JC_VTH_COOL_MASK                  0x06
#define CHARGER30_JC_VTH_COLD_0C                    0x00
#define CHARGER30_JC_VTH_COLD_5C                    0x01
#define CHARGER30_JC_VTH_COLD_MASK                  0x01

/**
 * @brief Charger 30 SAFETY_TIMER_STATUS_PART_NUM register setting.
 * @details Specified setting for SAFETY_TIMER_STATUS_PART_NUM register of Charger 30 Click driver.
 */
#define CHARGER30_STSPN_SAFETY_TIMER                0x80
#define CHARGER30_STSPN_PART_NUMBER                 0x00
#define CHARGER30_STSPN_PART_NUMBER_MASK            0x38

/**
 * @brief Charger 30 device address setting.
 * @details Specified setting for device slave address selection of
 * Charger 30 Click driver.
 */
#define CHARGER30_DEVICE_ADDRESS                    0x4B

/*! @} */ // charger30_set

/**
 * @defgroup charger30_map Charger 30 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 30 Click driver.
 */

/**
 * @addtogroup charger30_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 30 Click to the selected MikroBUS.
 */
#define CHARGER30_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ce = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.otg = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger30_map
/*! @} */ // charger30

/**
 * @brief Charger 30 Click status object.
 * @details Status object definition of Charger 30 Click driver.
 */
typedef struct
{
    uint8_t status;             /**< Status register value. */
    uint8_t fault;              /**< Fault register value. */
    uint16_t vbat;              /**< VBAT in mV. */
    uint16_t vsys;              /**< VSYS in mV. */
    float ntc;                  /**< NTC in percents. */
    uint16_t vin;               /**< VIN in mV. */
    float ichg;                 /**< Ichg in mA. */
    float iin;                  /**< Iin in mA. */
    uint16_t iin_dpm;           /**< Iin_dpm in mA. */

} charger30_status_t;

/**
 * @brief Charger 30 Click context object.
 * @details Context object definition of Charger 30 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ce;           /**< Charge enable pin (active low). */
    digital_out_t otg;          /**< Boost mode enable pin (active high). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} charger30_t;

/**
 * @brief Charger 30 Click configuration object.
 * @details Configuration object definition of Charger 30 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t ce;              /**< Charge enable pin (active low). */
    pin_name_t otg;             /**< Boost mode enable pin (active high). */
    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} charger30_cfg_t;

/**
 * @brief Charger 30 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER30_OK = 0,
    CHARGER30_ERROR = -1

} charger30_return_value_t;

/*!
 * @addtogroup charger30 Charger 30 Click Driver
 * @brief API for configuring and manipulating Charger 30 Click driver.
 * @{
 */

/**
 * @brief Charger 30 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger30_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger30_cfg_setup ( charger30_cfg_t *cfg );

/**
 * @brief Charger 30 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger30_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger30_init ( charger30_t *ctx, charger30_cfg_t *cfg );

/**
 * @brief Charger 30 default configuration function.
 * @details This function executes a default configuration of Charger 30
 * Click board.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t charger30_default_cfg ( charger30_t *ctx );

/**
 * @brief Charger 30 write register function.
 * @details This function writes a single byte of data to the selected register 
 * of the Charger 30 Click board.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger30_write_reg ( charger30_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Charger 30 write registers function.
 * @details This function writes a sequence of bytes starting from the selected register 
 * of the Charger 30 Click board.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger30_write_regs ( charger30_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Charger 30 read register function.
 * @details This function reads a single byte of data from the selected register 
 * of the Charger 30 Click board.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location to store the read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger30_read_reg ( charger30_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Charger 30 read registers function.
 * @details This function reads a sequence of bytes starting from the selected register 
 * of the Charger 30 Click board.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the data buffer to store read bytes.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger30_read_regs ( charger30_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Charger 30 enable boost function.
 * @details This function enables boost mode by setting the OTG pin to HIGH 
 * on the Charger 30 Click board.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger30_enable_boost ( charger30_t *ctx );

/**
 * @brief Charger 30 disable boost function.
 * @details This function disables boost mode by setting the OTG pin to LOW 
 * on the Charger 30 Click board.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger30_disable_boost ( charger30_t *ctx );

/**
 * @brief Charger 30 enable charging function.
 * @details This function enables battery charging by setting the CE pin to LOW 
 * on the Charger 30 Click board.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger30_enable_charging ( charger30_t *ctx );

/**
 * @brief Charger 30 disable charging function.
 * @details This function disables battery charging by setting the CE pin to HIGH 
 * on the Charger 30 Click board.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger30_disable_charging ( charger30_t *ctx );

/**
 * @brief Charger 30 get INT pin function.
 * @details This function reads the logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @return Logic state of the INT pin.
 * @note None.
 */
uint8_t charger30_get_int_pin ( charger30_t *ctx );

/**
 * @brief Charger 30 check communication function.
 * @details This function checks device communication by reading the part number 
 * register and comparing it with expected value.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger30_check_communication ( charger30_t *ctx );

/**
 * @brief Charger 30 software reset function.
 * @details This function performs a software reset of the Charger 30 Click board 
 * by writing to the reset bit in the input voltage regulation register.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger30_sw_reset ( charger30_t *ctx );

/**
 * @brief Charger 30 read status function.
 * @details This function reads multiple status and monitoring registers and stores 
 * the values into the provided status structure.
 * @param[in] ctx : Click context object.
 * See #charger30_t object definition for detailed explanation.
 * @param[out] status : Pointer to the structure to store the device status information.
 * See #charger30_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger30_read_status ( charger30_t *ctx, charger30_status_t *status );

#ifdef __cplusplus
}
#endif
#endif // CHARGER30_H

/*! @} */ // charger30

// ------------------------------------------------------------------------ END
