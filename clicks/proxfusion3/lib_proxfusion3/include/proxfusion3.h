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
 * @file proxfusion3.h
 * @brief This file contains API for ProxFusion 3 Click Driver.
 */

#ifndef PROXFUSION3_H
#define PROXFUSION3_H

#ifdef __cplusplus
extern "C"{
#endif

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
    

  

/*!
 * @addtogroup proxfusion3 ProxFusion 3 Click Driver
 * @brief API for configuring and manipulating ProxFusion 3 Click driver.
 * @{
 */

/**
 * @defgroup proxfusion3_reg ProxFusion 3 Registers List
 * @brief List of registers of ProxFusion 3 Click driver.
 */

/**
 * @addtogroup proxfusion3_reg
 * @{
 */

/**
 * @brief ProxFusion 3 description register.
 * @details Specified register for description of ProxFusion 3 Click driver.
 */

/**
 * @brief ProxFusion 3 Device Information register.
 * @details Specified register for Device Information of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_DEVICE_INFO                   0x00

/**
 * @brief ProxFusion 3 Flags register.
 * @details Specified register for Flags of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_SYS_FLAGS                     0x02

/**
 * @brief ProxFusion 3 Slider flags register.
 * @details Specified register for Slider flags of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_GESTURE_FLAGS                 0x03

/**
 * @brief ProxFusion 3 Channel Prox and Touch Flags register.
 * @details Specified register for Channel Prox and Touch Flags of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_CH_PROX_STATE                 0x04
#define PROXFUSION3_CH_TOUCH_STATE                0x05

/**
 * @brief ProxFusion 3 Channel Counts Bytes register.
 * @details Specified register for Channel Counts Bytes of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_ACF_CH0                       0x08
#define PROXFUSION3_ACF_CH1                       0x0A
#define PROXFUSION3_ACF_CH2                       0x0C
#define PROXFUSION3_ACF_CH3                       0x0E
#define PROXFUSION3_ACF_CH4                       0x10
#define PROXFUSION3_ACF_CH5                       0x12
#define PROXFUSION3_ACF_CH6                       0x14
#define PROXFUSION3_ACF_CH7                       0x16

/**
 * @brief ProxFusion 3 Channel LTA Bytes register.
 * @details Specified register for Channel LTA Bytes of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_LTA_CH0                       0x09
#define PROXFUSION3_LTA_CH1                       0x0B
#define PROXFUSION3_LTA_CH2                       0x0D
#define PROXFUSION3_LTA_CH3                       0x0F
#define PROXFUSION3_LTA_CH4                       0x11
#define PROXFUSION3_LTA_CH5                       0x13
#define PROXFUSION3_LTA_CH6                       0x15
#define PROXFUSION3_LTA_CH7                       0x17
 
/**
 * @brief ProxFusion 3 Channel Delta Bytes  register.
 * @details Specified register for Channel Delta Bytes  of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_DELTA_CH0                     0x18
#define PROXFUSION3_DELTA_CH1                     0x19
#define PROXFUSION3_DELTA_CH2                     0x1A
#define PROXFUSION3_DELTA_CH3                     0x1B
#define PROXFUSION3_DELTA_CH4                     0x1C
#define PROXFUSION3_DELTA_CH5                     0x1D
#define PROXFUSION3_DELTA_CH6                     0x1E
#define PROXFUSION3_DELTA_CH7                     0x1F

/**
 * @brief ProxFusion 3 Reference Channel Delta Bytes  register.
 * @details Specified register for Reference Channel Delta Bytes of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_REFDELTA_CH0                  0x20
#define PROXFUSION3_REFDELTA_CH1                  0x21
#define PROXFUSION3_REFDELTA_CH2                  0x22
#define PROXFUSION3_REFDELTA_CH3                  0x23
#define PROXFUSION3_REFDELTA_CH4                  0x24
#define PROXFUSION3_REFDELTA_CH5                  0x25
#define PROXFUSION3_REFDELTA_CH6                  0x26
#define PROXFUSION3_REFDELTA_CH7                  0x27

/**
 * @brief ProxFusion 3 Slider coordinates register.
 * @details Specified register for Reference Channel Delta Bytes of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_COORDINATES                   0x30

/**
 * @brief ProxFusion 3 Capacitance Measurement Variables register.
 * @details Specified register for Capacitance Measurement Variables of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_CAP_ABS_BASE                  0x31
#define PROXFUSION3_CAP_ABS_CS                    0x32
#define PROXFUSION3_CAP_ABS_CS_CAP0               0x33
#define PROXFUSION3_CAP_ABS_CS_CAP1               0x34

/**
 * @brief ProxFusion 3 Power mode settings Bytes register.
 * @details Specified register for Power mode settings Bytes of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PMU_SETTINGS                  0x80
#define PROXFUSION3_ACTIVE_CHANNELS               0x81
#define PROXFUSION3_CH_RESEED                     0x82

/**
 * @brief ProxFusion 3 Report Rate Bytes register.
 * @details Specified register for Report Rate Bytes of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_REPORT_RATES                  0x83
#define PROXFUSION3_ULP_MODE_RATES                0x84
#define PROXFUSION3_TIMEOUT_PERIODS               0x85

/**
 * @brief ProxFusion 3 General Settings register.
 * @details Specified register for General Settings of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_GEN_SETINGS                   0x86
#define PROXFUSION3_REF_SETTINGS                  0x87
#define PROXFUSION3_EVENT_SETTINGS                0x88
 
/**
 * @brief ProxFusion 3 Gesture Settings register.
 * @details Specified register for Gesture Settings of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_SLIDER0_CH                    0x89
#define PROXFUSION3_TAP_SETTINGS                  0x8A
#define PROXFUSION3_SWIPE_SETTINGS                0x8B

/**
 * @brief ProxFusion 3 Channel settings register.
 * @details Specified register for Channel settings of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_CH0_SETTINGS                  0x8C
#define PROXFUSION3_CH1_SETTINGS                  0x93
#define PROXFUSION3_CH3_SETTINGS                  0x9A
#define PROXFUSION3_CH4_SETTINGS                  0xA1
#define PROXFUSION3_CH5_SETTINGS                  0xA8
#define PROXFUSION3_CH6_SETTINGS                  0xAF
#define PROXFUSION3_CH7_SETTINGS                  0xB6
#define PROXFUSION3_CH8_SETTINGS                  0xBD
#define PROXFUSION3_CHx_REF_ASSOC                 0x92
#define PROXFUSION3_CH6_PROX_SETTINGS             0xB7
#define PROXFUSION3_CH6_ATI_MIRROR                0xB9
#define PROXFUSION3_CH7_ATI_MIRROR                0xC0
#define PROXFUSION3_ATI_TARGETS                   0x8E

/**
 * @brief ProxFusion 3 Engineering settings register.
 * @details Specified register for Engineering settings of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_ENG_DIRECT_ADDRESS            0xF0
#define PROXFUSION3_ENG_DIRECT_DATA               0xF1
#define PROXFUSION3_ENG_I2C_SETTINGS              0xF2
#define PROXFUSION3_ENG_LAST_CONV_LSB             0xF3
#define PROXFUSION3_ENG_LAST_CONV_MSB             0xF4
#define PROXFUSION3_ENG_PXS_DETECTION             0xF5

/*! @} */ // proxfusion3_reg

/**
 * @defgroup proxfusion3_set ProxFusion 3 Registers Settings
 * @brief Settings for registers of ProxFusion 3 Click driver.
 */

/**
 * @addtogroup proxfusion3_set
 * @{
 */

/**
 * @brief ProxFusion 3 description setting.
 * @details Specified setting for description of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PRODUCT_NUM                   0x4F
#define PROXFUSION3_SW_NUM_V1                     0x02
#define PROXFUSION3_SW_NUM_V2                     0x03

/**
 * @brief ProxFusion 3 System Flags Byte Bits setting.
 * @details Specified setting for System Flags Byte Bits of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_NP_SEG_ACTIVE_BIT             0x01
#define PROXFUSION3_GO_TO_NP_BIT                  0x02
#define PROXFUSION3_IN_ATI_BIT                    0x04
#define PROXFUSION3_NP_MODE_BITS                  0x00
#define PROXFUSION3_LP_MODE_BITS                  0x08
#define PROXFUSION3_ULP_MODE_BITS                 0x10
#define PROXFUSION3_HALT_MODE_BITS                0x18
#define PROXFUSION3_SHOW_RESET_BIT                0x80

/**
 * @brief ProxFusion 3 Event Byte Bits setting.
 * @details Specified setting for Event Byte Bits of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PROX_EVENT_BIT                0x01
#define PROXFUSION3_TOUCH_EVENT_BIT               0x02
#define PROXFUSION3_DEEP_EVENT_BIT                0x04
#define PROXFUSION3_GESTURE_EVENT_BIT             0x08
#define PROXFUSION3_MOV_EVENT_BIT                 0x10
#define PROXFUSION3_REF_EVENT_BIT                 0x20
#define PROXFUSION3_SYS_EVENT_BIT                 0x40
#define PROXFUSION3_LP_EVENT_BIT                  0x80

/**
 * @brief ProxFusion 3 Gesture Byte Bits setting.
 * @details Specified setting for Gesture Byte Bits of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_TAP0_BIT                      0x01
#define PROXFUSION3_HOLD0_BIT                     0x02
#define PROXFUSION3_SWIPE_UP_BIT                  0x04
#define PROXFUSION3_SWIPE_DOWN_BIT                0x08
#define PROXFUSION3_TAP1_BIT                      0x10
#define PROXFUSION3_HOLD1_BIT                     0x20
#define PROXFUSION3_SWIPE_LEFT_BIT                0x40
#define PROXFUSION3_SWIPE_RIGHT_BIT               0x80

/**
 * @brief ProxFusion 3 Utility Bits setting.
 * @details Specified setting for Utility Bits of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_ACK_RESET_BIT                 0x01
#define PROXFUSION3_SOFT_RESET_BIT                0x02
#define PROXFUSION3_REDO_ATI_BIT                  0x04
#define PROXFUSION3_EVENT_MODE_BIT                0x20

/**
 * @brief ProxFusion 3 Setting Bits setting.
 * @details Specified setting for Setting Bits of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_DISABLE_CH6_ATI               0xA0
#define PROXFUSION3_ENABLE_ABSCAP_UI              0x08
#define PROXFUSION3_ENABLE_4MHZ_FOSC              0x80
#define PROXFUSION3_DISABLE_AUTO_MODE             0x20
    
/**
 * @brief ProxFusion 3 Channel select, Power mode & System setting.
 * @details Specified setting for the Channel select, Power mode & System Settings
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PMU_GENERAL_SETTINGS          0x41
#define PROXFUSION3_I2C_GENERAL_SETTINGS          0x00
#define PROXFUSION3_SYS_CHB_ACTIVE                0xFF
#define PROXFUSION3_ACF_LTA_FILTER_SETTINGS       0xC4
#define PROXFUSION3_LTA_CHB_RESEED_ENABLED        0xFF
#define PROXFUSION3_UIS_GLOBAL_EVENTS_MASK        0x00

/**
 * @brief ProxFusion 3 Report Rates and Timing setting.
 * @details Specified setting for the Report Rates and Timing
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PMU_REPORT_RATE_NP            0x10
#define PROXFUSION3_PMU_REPORT_RATE_LP            0xA0
#define PROXFUSION3_PMU_REPORT_RATE_ULP           0x0D
#define PROXFUSION3_PMU_MODE_TIMOUT               0x0A
#define PROXFUSION3_I2C_WINDOW_TIMEOUT            0x14
#define PROXFUSION3_LTA_HALT_TIMEOUT              0x14

/**
 * @brief ProxFusion 3 Global setting.
 * @details Specified setting for the Global Settings
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PXS_GENERAL_SETTINGS0         0x00
#define PROXFUSION3_PXS_GENERAL_SETTINGS1         0x00
#define PROXFUSION3_UIS_ABSOLUTE_CAPACITANCE      0x00
#define PROXFUSION3_UIS_DCF_GENERAL_SETTINGS      0x11
#define PROXFUSION3_GEM_CHB_BLOCK_NFOLLOW         0x00
#define PROXFUSION3_MOV_CHB_MOVEMENT_CHANNEL      0x00
#define PROXFUSION3_UIS_CHB_SLIDER0               0x78
#define PROXFUSION3_UIS_CHB_SLIDER1               0x06
#define PROXFUSION3_UIS_GESTURE_TAP_TIMEOUT       0x40
#define PROXFUSION3_UIS_GESTURE_SWIPE_TIMEOUT     0xBB
#define PROXFUSION3_UIS_GESTURE_THRESHOLD         0x80
#define PROXFUSION3_LTA_CHB_RESEED                0x00

/**
 * @brief ProxFusion 3 CH0 Settings setting.
 * @details Specified setting for the CH0 Settings
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PXS_CRXSEL_CH0                0xFF
#define PROXFUSION3_PXS_CTXSEL_CH0                0xFF
#define PROXFUSION3_PXS_PROXCTRL_CH0              0xA3
#define PROXFUSION3_PXS_PROXCFG0_CH0              0x40
#define PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH0     0x06
#define PROXFUSION3_ATI_BASE_AND_TARGET_CH0       0x90
#define PROXFUSION3_ATI_MIRROR_CH0                0x2C
#define PROXFUSION3_ATI_PCC_CH0                   0xCD
#define PROXFUSION3_PXS_PROX_THRESHOLD_CH0        0x04
#define PROXFUSION3_PXS_TOUCH_THRESHOLD_CH0       0x09
#define PROXFUSION3_PXS_DEEP_THRESHOLD_CH0        0x10
#define PROXFUSION3_PXS_HYSTERESIS_CH0            0x04
#define PROXFUSION3_DCF_CHB_ASSOCIATION_CH0       0x00
#define PROXFUSION3_DCF_WEIGHT_CH0                0x00

/**
 * @brief ProxFusion 3 CH1 Settings setting.
 * @details Specified setting for the CH1 Settings
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PXS_CRXSEL_CH1                0x3A
#define PROXFUSION3_PXS_CTXSEL_CH1                0xFF
#define PROXFUSION3_PXS_PROXCTRL_CH1              0xA3
#define PROXFUSION3_PXS_PROXCFG0_CH1              0x40
#define PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH1     0x06
#define PROXFUSION3_ATI_BASE_AND_TARGET_CH1       0x90
#define PROXFUSION3_ATI_MIRROR_CH1                0x29
#define PROXFUSION3_ATI_PCC_CH1                   0xC6
#define PROXFUSION3_PXS_PROX_THRESHOLD_CH1        0x04
#define PROXFUSION3_PXS_TOUCH_THRESHOLD_CH1       0x09
#define PROXFUSION3_PXS_DEEP_THRESHOLD_CH1        0x10
#define PROXFUSION3_PXS_HYSTERESIS_CH1            0x04
#define PROXFUSION3_DCF_CHB_ASSOCIATION_CH1       0x00
#define PROXFUSION3_DCF_WEIGHT_CH1                0x00

/**
 * @brief ProxFusion 3 CH2 Settings setting.
 * @details Specified setting for the CH2 Settings
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PXS_CRXSEL_CH2                0xC5
#define PROXFUSION3_PXS_CTXSEL_CH2                0xFF
#define PROXFUSION3_PXS_PROXCTRL_CH2              0xA3
#define PROXFUSION3_PXS_PROXCFG0_CH2              0x40
#define PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH2     0x06
#define PROXFUSION3_ATI_BASE_AND_TARGET_CH2       0x90
#define PROXFUSION3_ATI_MIRROR_CH2                0x29
#define PROXFUSION3_ATI_PCC_CH2                   0xC0
#define PROXFUSION3_PXS_PROX_THRESHOLD_CH2        0x04
#define PROXFUSION3_PXS_TOUCH_THRESHOLD_CH2       0x09
#define PROXFUSION3_PXS_DEEP_THRESHOLD_CH2        0x10
#define PROXFUSION3_PXS_HYSTERESIS_CH2            0x04
#define PROXFUSION3_DCF_CHB_ASSOCIATION_CH2       0x00
#define PROXFUSION3_DCF_WEIGHT_CH2                0x00

/**
 * @brief ProxFusion 3 CH3 Settings setting.
 * @details Specified setting for the CH3 Settings
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PXS_CRXSEL_CH3                0x90
#define PROXFUSION3_PXS_CTXSEL_CH3                0xFF
#define PROXFUSION3_PXS_PROXCTRL_CH3              0xA3
#define PROXFUSION3_PXS_PROXCFG0_CH3              0x40
#define PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH3     0x06
#define PROXFUSION3_ATI_BASE_AND_TARGET_CH3       0x90
#define PROXFUSION3_ATI_MIRROR_CH3                0x1E
#define PROXFUSION3_ATI_PCC_CH3                   0xC8
#define PROXFUSION3_PXS_PROX_THRESHOLD_CH3        0x0A
#define PROXFUSION3_PXS_TOUCH_THRESHOLD_CH3       0x10
#define PROXFUSION3_PXS_DEEP_THRESHOLD_CH3        0x30
#define PROXFUSION3_PXS_HYSTERESIS_CH3            0x04
#define PROXFUSION3_DCF_CHB_ASSOCIATION_CH3       0x00
#define PROXFUSION3_DCF_WEIGHT_CH3                0x00

/**
 * @brief ProxFusion 3 CH4 Settings setting.
 * @details Specified setting for the CH4 Settings
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PXS_CRXSEL_CH4                0x42
#define PROXFUSION3_PXS_CTXSEL_CH4                0xFF
#define PROXFUSION3_PXS_PROXCTRL_CH4              0xA3
#define PROXFUSION3_PXS_PROXCFG0_CH4              0x40
#define PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH4     0x06
#define PROXFUSION3_ATI_BASE_AND_TARGET_CH4       0x90
#define PROXFUSION3_ATI_MIRROR_CH4                0x1E
#define PROXFUSION3_ATI_PCC_CH4                   0xCA
#define PROXFUSION3_PXS_PROX_THRESHOLD_CH4        0x0A
#define PROXFUSION3_PXS_TOUCH_THRESHOLD_CH4       0x10
#define PROXFUSION3_PXS_DEEP_THRESHOLD_CH4        0x30
#define PROXFUSION3_PXS_HYSTERESIS_CH4            0x04
#define PROXFUSION3_DCF_CHB_ASSOCIATION_CH4       0x00
#define PROXFUSION3_DCF_WEIGHT_CH4                0x00

/**
 * @brief ProxFusion 3 CH5 Settings setting.
 * @details Specified setting for the CH5 Settings
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PXS_CRXSEL_CH5                0x21
#define PROXFUSION3_PXS_CTXSEL_CH5                0xFF
#define PROXFUSION3_PXS_PROXCTRL_CH5              0xA3
#define PROXFUSION3_PXS_PROXCFG0_CH5              0x40
#define PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH5     0x06
#define PROXFUSION3_ATI_BASE_AND_TARGET_CH5       0x90
#define PROXFUSION3_ATI_MIRROR_CH5                0x1E
#define PROXFUSION3_ATI_PCC_CH5                   0xD0
#define PROXFUSION3_PXS_PROX_THRESHOLD_CH5        0x0A
#define PROXFUSION3_PXS_TOUCH_THRESHOLD_CH5       0x10
#define PROXFUSION3_PXS_DEEP_THRESHOLD_CH5        0x30
#define PROXFUSION3_PXS_HYSTERESIS_CH5            0x04
#define PROXFUSION3_DCF_CHB_ASSOCIATION_CH5       0x00
#define PROXFUSION3_DCF_WEIGHT_CH5                0x00

/**
 * @brief ProxFusion 3 CH6 Settings setting.
 * @details Specified setting for the CH6 Settings
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PXS_CRXSEL_CH6                0x0C
#define PROXFUSION3_PXS_CTXSEL_CH6                0xFF
#define PROXFUSION3_PXS_PROXCTRL_CH6              0xA3
#define PROXFUSION3_PXS_PROXCFG0_CH6              0x40
#define PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH6     0x06
#define PROXFUSION3_ATI_BASE_AND_TARGET_CH6       0x90
#define PROXFUSION3_ATI_MIRROR_CH6                0x26
#define PROXFUSION3_ATI_PCC_CH6                   0xCB
#define PROXFUSION3_PXS_PROX_THRESHOLD_CH6        0x0A
#define PROXFUSION3_PXS_TOUCH_THRESHOLD_CH6       0x10
#define PROXFUSION3_PXS_DEEP_THRESHOLD_CH6        0x30
#define PROXFUSION3_PXS_HYSTERESIS_CH6            0x04
#define PROXFUSION3_DCF_CHB_ASSOCIATION_CH6       0x00
#define PROXFUSION3_DCF_WEIGHT_CH6                0x00

/**
 * @brief ProxFusion 3 CH7 Settings setting.
 * @details Specified setting for the CH7 Settings
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PXS_CRXSEL_CH7                0x01
#define PROXFUSION3_PXS_CTXSEL_CH7                0xFF
#define PROXFUSION3_PXS_PROXCTRL_CH7              0xA3
#define PROXFUSION3_PXS_PROXCFG0_CH7              0xDE
#define PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH7     0x01
#define PROXFUSION3_ATI_BASE_AND_TARGET_CH7       0xD0
#define PROXFUSION3_ATI_MIRROR_CH7                0x57
#define PROXFUSION3_ATI_PCC_CH7                   0x60
#define PROXFUSION3_PXS_PROX_THRESHOLD_CH7        0x0A
#define PROXFUSION3_PXS_TOUCH_THRESHOLD_CH7       0x08
#define PROXFUSION3_PXS_DEEP_THRESHOLD_CH7        0x1A
#define PROXFUSION3_PXS_HYSTERESIS_CH7            0x04
#define PROXFUSION3_DCF_CHB_ASSOCIATION_CH7       0x00
#define PROXFUSION3_DCF_WEIGHT_CH7                0x00

//
/**
 * @brief ProxFusion 3 CRX selection for Channels setting.
 * @details Specified setting for the CRX selection for Channels
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_CH0_CRX                       0x8C 
#define PROXFUSION3_CH1_CRX                       0x93 
#define PROXFUSION3_CH2_CRX                       0x9A 
#define PROXFUSION3_CH3_CRX                       0xA1 
#define PROXFUSION3_CH4_CRX                       0xA8 
#define PROXFUSION3_CH5_CRX                       0xAF 
#define PROXFUSION3_CH6_CRX                       0xB6 
#define PROXFUSION3_CH7_CRX                       0xBD 

/**
 * @brief ProxFusion 3 touch number data.
 * @details Specified touch number data of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_TOUCH_NUMB_1                  0x13
#define PROXFUSION3_TOUCH_NUMB_2                  0x27
#define PROXFUSION3_TOUCH_NUMB_3                  0x4E
#define PROXFUSION3_TOUCH_NUMB_4                  0x0C
#define PROXFUSION3_TOUCH_NUMB_5                  0x30
#define PROXFUSION3_TOUCH_NUMB_6                  0x70
#define PROXFUSION3_TOUCH_NUMB_7                  0x60
#define PROXFUSION3_TOUCH_NUMB_8                  0x40

/**
 * @brief ProxFusion 3 channel of touch.
 * @details Specified channel of touch of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_TOUCH_CRX_0                   0x01
#define PROXFUSION3_TOUCH_CRX_1                   0x02
#define PROXFUSION3_TOUCH_CRX_2                   0x04
#define PROXFUSION3_TOUCH_CRX_3                   0x08
#define PROXFUSION3_TOUCH_CRX_4                   0x10
#define PROXFUSION3_TOUCH_CRX_5                   0x20
#define PROXFUSION3_TOUCH_CRX_6                   0x40
#define PROXFUSION3_TOUCH_CRX_7                   0x80

/**
 * @brief ProxFusion 3 position of touch.
 * @details Specified position of touch of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_TOUCH_POS_NO_TOUCH            0x00
#define PROXFUSION3_TOUCH_POS_1                   0x01
#define PROXFUSION3_TOUCH_POS_2                   0x02
#define PROXFUSION3_TOUCH_POS_3                   0x03
#define PROXFUSION3_TOUCH_POS_4                   0x04
#define PROXFUSION3_TOUCH_POS_5                   0x05
#define PROXFUSION3_TOUCH_POS_6                   0x06
#define PROXFUSION3_TOUCH_POS_7                   0x07
#define PROXFUSION3_TOUCH_POS_8                   0x08

/**
 * @brief ProxFusion 3 Channel Prox and Touch Threshold settings register.
 * @details Specified register forChannel Prox and Touch Threshold of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_CH0_PT_T                      0x90    
#define PROXFUSION3_CH1_PT_T                      0x97    
#define PROXFUSION3_CH2_PT_T                      0x9E    
#define PROXFUSION3_CH3_PT_T                      0xA5    
#define PROXFUSION3_CH4_PT_T                      0xAC    
#define PROXFUSION3_CH5_PT_T                      0xB3    
#define PROXFUSION3_CH6_PT_T                      0xBA    
#define PROXFUSION3_CH7_PT_T                      0xC1 

/**
 * @brief ProxFusion 3 Channel Deep Touch Threshold settings register.
 * @details Specified register forChannel Deep Touch Threshold of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_CH0_DT_T                      0x91
#define PROXFUSION3_CH1_DT_T                      0x98
#define PROXFUSION3_CH2_DT_T                      0x9F
#define PROXFUSION3_CH3_DT_T                      0xA6
#define PROXFUSION3_CH4_DT_T                      0xAD
#define PROXFUSION3_CH5_DT_T                      0xB4
#define PROXFUSION3_CH6_DT_T                      0xBB
#define PROXFUSION3_CH7_DT_T                      0xC2

/**
 * @brief ProxFusion 3 Check touch event.
 * @details Specified check touch event of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_EVENT_NO_TOUCH                0x00
#define PROXFUSION3_EVENT_TOUCH                   0x01

/**
 * @brief ProxFusion 3 device address setting.
 * @details Specified setting for device slave address selection of
 * ProxFusion 3 Click driver.
 */
#define PROXFUSION3_SET_DEV_ADDR                  0x44

/**
 * @brief ProxFusion 3 pin setting function.
 * @details Specified setting for the target pin state of 
 * ProxFusion 3 Click driver.
 */
#define PROXFUSION3_SET_PIN_STATE_LOW             0x00
#define PROXFUSION3_SET_PIN_STATE_HIGH            0x01

/**
 * @brief ProxFusion 3 threshold setting.
 * @details Specified setting for the proximity, touch and deep touch thresholds
 * of ProxFusion 3 Click driver.
 */
#define PROXFUSION3_PROX_THRESHOLD                 10        
#define PROXFUSION3_TOUCH_THRESHOLD_CH0            22   
#define PROXFUSION3_TOUCH_THRESHOLD_CH1            20
#define PROXFUSION3_TOUCH_THRESHOLD_CH2            10
#define PROXFUSION3_TOUCH_THRESHOLD_CH3            10
#define PROXFUSION3_TOUCH_THRESHOLD_CH4            22
#define PROXFUSION3_TOUCH_THRESHOLD_CH5            20
#define PROXFUSION3_TOUCH_THRESHOLD_CH6            12
#define PROXFUSION3_TOUCH_THRESHOLD_CH7            10
#define PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH0       32
#define PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH1       26
#define PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH2       26
#define PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH3       26
#define PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH4       32
#define PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH5       26
#define PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH6       26
#define PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH7       26
#define PROXFUSION3_TOUCH_CH_RX_THRESHOLD_7     16384


/*! @} */ // proxfusion3_set

/**
 * @defgroup proxfusion3_map ProxFusion 3 MikroBUS Map
 * @brief MikroBUS pin mapping of ProxFusion 3 Click driver.
 */

/**
 * @addtogroup proxfusion3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ProxFusion 3 Click to the selected MikroBUS.
 */
#define PROXFUSION3_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );    \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );    \
    cfg.gp = MIKROBUS( mikrobus, MIKROBUS_PWM );     \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proxfusion3_map
/*! @} */ // proxfusion3

/**
 * @brief ProxFusion 3 Click context object.
 * @details Context object definition of ProxFusion 3 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  int_pin;   /**< Indicate windows for communication from master. */

    // Input pins

    digital_in_t  gp;         /**< Touch output for CH0 from the POR event. */

    // Modules

    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} proxfusion3_t;

/**
 * @brief ProxFusion 3 Click configuration object.
 * @details Configuration object definition of ProxFusion 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;          /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;          /**< Bidirectional data pin descriptor for I2C driver. */
                              
    pin_name_t  gp;           /**< Touch output for CH0 from the POR event. */
    pin_name_t  int_pin;      /**< Indicate windows for communication from master. */
                              
    uint32_t  i2c_speed;      /**< I2C serial speed. */
    uint8_t   i2c_address;    /**< I2C slave address. */

} proxfusion3_cfg_t;

/*!
 * @addtogroup proxfusion3 ProxFusion 3 Click Driver
 * @brief API for configuring and manipulating ProxFusion 3 Click driver.
 * @{
 */

/**
 * @brief ProxFusion 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proxfusion3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void proxfusion3_cfg_setup ( proxfusion3_cfg_t *cfg );

/**
 * @brief ProxFusion 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proxfusion3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t proxfusion3_init ( proxfusion3_t *ctx, proxfusion3_cfg_t *cfg );

/**
 * @brief ProxFusion 3 default configuration function.
 * @details This function executes a default configuration of ProxFusion 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode. The delay is approximately 600 milliseconds.
 *
 * @endcode
 */
err_t proxfusion3_default_cfg ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 INT pin setting function.
 * @details This function sets the INT pin state to the desired level
 * ProxFusion 3 click board.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @param[in] pin_state : 
 *    @li @c 0x00 ( PROXFUSION3_SET_PIN_STATE_LOW )  - Set INT pin on the low level,
 *    @li @c 0x01 ( PROXFUSION3_SET_PIN_STATE_HIGH ) - Set INT pin on the high level.
 * @return Nothing.
 * @note None.
 */
void proxfusion3_set_state_int_pin ( proxfusion3_t *ctx, uint8_t pin_state );

/**
 * @brief ProxFusion 3 get state of GP pin function.
 * @details This function get State of GP pin 
 * on ProxFusion 3 click board.
 * @param[out] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return 
 *  @li @c 0x00 - Low,
 *  @li @c 0x01 - High.
 * 
 * @note None.
 */
uint8_t proxfusion3_get_state_gp_pin ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t proxfusion3_generic_write ( proxfusion3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief ProxFusion 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t proxfusion3_generic_read ( proxfusion3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief ProxFusion 3 I2C register writing function.
 * @details This function register writes a 16-bit data 
 * to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] tx_buf : 16-bit data to be written.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void proxfusion3_write_reg ( proxfusion3_t *ctx, uint8_t reg, uint16_t tx_data );

/**
 * @brief ProxFusion 3 I2C register reading function.
 * @details This function reads a 16-bit data
 * from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @return 16-bit read data.
 *
 * @note None.
 *
 * @endcode
 */
uint16_t proxfusion3_read_reg ( proxfusion3_t *ctx, uint8_t reg );

/**
 * @brief ProxFusion 3 get version info data function.
 * @details This function reads a  version info data
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @param[out] product_number : Output product number data.
 * @param[out] software_version : Output software version data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t proxfusion3_get_version_info ( proxfusion3_t *ctx, uint8_t *product_number, uint8_t *software_version );

/**
 * @brief ProxFusion 3 software reset function.
 * @details This function is a method which clears the Show Reset bit 
 * by writing it to a 0
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board. 
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void proxfusion3_sw_reset ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 enable channels function.
 * @details This function is a method which enables all channels
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board. 
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void proxfusion3_enable_channels ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 channel remap function.
 * @details This function is remap the channels
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board. 
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void proxfusion3_channel_remap ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 adjust touch thresholds function.
 * @details This function adjust touch thresholds
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board. 
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void proxfusion3_adjust_touch_thresholds ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 adjust deep touch thresholds function.
 * @details This function adjust deep touch thresholds
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board. 
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void proxfusion3_adjust_deep_touch_thresholds ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 auto tune function.
 * @details This function force the device to run the 
 * Automatic Tuning Implementation (ATI) routine
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board. 
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void proxfusion3_auto_tune ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 set event function.
 * @details This function set desired event
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @param[in] event : 
 *            @li @c 0x01 ( PROXFUSION3_PROX_EVENT_BIT )    - Proxy event,
 *            @li @c 0x02 ( PROXFUSION3_TOUCH_EVENT_BIT )   - Touch event,
 *            @li @c 0x04 ( PROXFUSION3_DEEP_EVENT_BIT )    - Deep event,
 *            @li @c 0x08 ( PROXFUSION3_GESTURE_EVENT_BIT ) - Gesture event,
 *            @li @c 0x10 ( PROXFUSION3_MOV_EVENT_BIT )     - Mov event,
 *            @li @c 0x20 ( PROXFUSION3_REF_EVENT_BIT )     - Reference event,
 *            @li @c 0x40 ( PROXFUSION3_SYS_EVENT_BIT )     - System event,
 *            @li @c 0x80 ( PROXFUSION3_LP_EVENT_BIT )      - LP event. 
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void proxfusion3_set_event ( proxfusion3_t *ctx, uint8_t event );

/**
 * @brief ProxFusion 3 get absolute measurement function.
 * @details This function read the absolute capacitance registers 
 * and calculate the absolute capacitance
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return absolute capacitance.
 *
 * @note None.
 *
 * @endcode
 */
float proxfusion3_get_absolute_measurement ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 read channel delta function.
 * @details This function reads and returns the Delta value of a specific channel
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @param[in] channel : The enumerator which specifes which channel's Delta value to return.
 * @return 16-bit Delta value of the channel.
 *
 * @note None.
 *
 * @endcode
 */
uint16_t proxfusion3_read_channel_delta ( proxfusion3_t *ctx, uint8_t channel );

/**
 * @brief ProxFusion 3 check touch event function.
 * @details This function reads and check touch event
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return  @li @c 0x00 ( PROXFUSION3_EVENT_NO_TOUCH ) - No Touch event,
 *          @li @c 0x01 ( PROXFUSION3_EVENT_TOUCH )    - Touch event.
 *
 * @note None.
 *
 * @endcode
 */
uint8_t proxfusion3_check_touch_event ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 get touch function.
 * @details This function reads and returns the position of the touch
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board.
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return position of the touch:
 *            @li @c 0x01 - Number 1,
 *            @li @c 0x02 - Number 2,
 *            @li @c 0x03 - Number 3,
 *            @li @c 0x04 - Number 4,
 *            @li @c 0x05 - Number 5,
 *            @li @c 0x06 - Number 6,
 *            @li @c 0x07 - Number 7,
 *            @li @c 0x08 - Number 8.
 *
 * @note None.
 *
 * @endcode
 */
uint8_t proxfusion3_get_touch ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 enables the absolute capacitiance function.
 * @details This function is a method which enables 
 * the absolute capacitiance UI
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board. 
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void proxfusion3_en_abs_cap ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 set even mode function.
 * @details This function set the desire even mode 
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board. 
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @param[in] mode : 
 *            @li @c 0x01 ( PROXFUSION3_PROX_EVENT_BIT )    - Proxy event,
 *            @li @c 0x02 ( PROXFUSION3_TOUCH_EVENT_BIT )   - Touch event,
 *            @li @c 0x04 ( PROXFUSION3_DEEP_EVENT_BIT )    - Deep event,
 *            @li @c 0x08 ( PROXFUSION3_GESTURE_EVENT_BIT ) - Gesture event,
 *            @li @c 0x10 ( PROXFUSION3_MOV_EVENT_BIT )     - Mov event,
 *            @li @c 0x20 ( PROXFUSION3_REF_EVENT_BIT )     - Reference event,
 *            @li @c 0x40 ( PROXFUSION3_SYS_EVENT_BIT )     - System event,
 *            @li @c 0x80 ( PROXFUSION3_LP_EVENT_BIT )      - LP event. 
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void proxfusion3_set_even_mode ( proxfusion3_t *ctx, uint8_t mode );

/**
 * @brief ProxFusion 3 get events function.
 * @details This function reads and returns the byte which holds the event flags 
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board. 
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return Byte which contains the event flags.
 *
 * @note None.
 *
 * @endcode
 */
uint8_t proxfusion3_get_events ( proxfusion3_t *ctx );

/**
 * @brief ProxFusion 3 get gestures function.
 * @details This function reads and returns the byte which holds the gesture flags 
 * of the IQS269A 8 Channel capacitive touch and proximity controller
 * on the ProxFusion 3 click board. 
 * @param[in] ctx : Click context object.
 * See #proxfusion3_t object definition for detailed explanation.
 * @return Byte which contains the gesture flags.
 *
 * @note The user must determine which gestures occurred by use of the gesture bit definitions.
 * It is up to the user to decide which one to use.
 *
 * @endcode
 */
uint8_t proxfusion3_get_gestures ( proxfusion3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PROXFUSION3_H

/*! @} */ // proxfusion3

// ------------------------------------------------------------------------ END
