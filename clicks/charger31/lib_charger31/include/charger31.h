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
 * @file charger31.h
 * @brief This file contains API for Charger 31 Click Driver.
 */

#ifndef CHARGER31_H
#define CHARGER31_H

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
 * @addtogroup charger31 Charger 31 Click Driver
 * @brief API for configuring and manipulating Charger 31 Click driver.
 * @{
 */

/**
 * @defgroup charger31_reg Charger 31 Registers List
 * @brief List of registers of Charger 31 Click driver.
 */

/**
 * @addtogroup charger31_reg
 * @{
 */

/**
 * @brief Charger 31 register list.
 * @details Specified register list of Charger 31 Click driver.
 */
#define CHARGER31_REG_CHG_CTRL0                 0x00
#define CHARGER31_REG_IIN                       0x01
#define CHARGER31_REG_CHG_PAR0                  0x02
#define CHARGER31_REG_CHG_PAR1                  0x03
#define CHARGER31_REG_CHG_PAR2                  0x04
#define CHARGER31_REG_CHG_PAR3                  0x05
#define CHARGER31_REG_CHG_CTRL1                 0x06
#define CHARGER31_REG_CHG_CTRL2                 0x07
#define CHARGER31_REG_CHG_CTRL3                 0x08
#define CHARGER31_REG_CHG_CTRL4                 0x09
#define CHARGER31_REG_VIN_DET                   0x0A
#define CHARGER31_REG_CHG_CTRL5                 0x0C
#define CHARGER31_REG_NTC_ACTION                0x0D
#define CHARGER31_REG_NTC_TH                    0x0E
#define CHARGER31_REG_VIN_IMPD                  0x0F
#define CHARGER31_REG_INT_MASK                  0x10
#define CHARGER31_REG_STATUS0                   0x11
#define CHARGER31_REG_STATUS1                   0x12
#define CHARGER31_REG_STATUS2                   0x13
#define CHARGER31_REG_STATUS3                   0x14
#define CHARGER31_REG_STATUS4                   0x15
#define CHARGER31_REG_STATUS5                   0x16

/*! @} */ // charger31_reg

/**
 * @defgroup charger31_set Charger 31 Registers Settings
 * @brief Settings for registers of Charger 31 Click driver.
 */

/**
 * @addtogroup charger31_set
 * @{
 */

/**
 * @brief Charger 31 CHG_CTRL0 register setting.
 * @details Specified setting for CHG_CTRL0 register of Charger 31 Click driver.
 */
#define CHARGER31_CHG_CTRL0_REG_RST_KEEP        0x00
#define CHARGER31_CHG_CTRL0_REG_RST_RESET       0x80
#define CHARGER31_CHG_CTRL0_REG_RST_MASK        0x80
#define CHARGER31_CHG_CTRL0_EN_STAT_IB_STAT     0x00
#define CHARGER31_CHG_CTRL0_EN_STAT_IB_IB       0x40
#define CHARGER31_CHG_CTRL0_EN_STAT_IB_MASK     0x40
#define CHARGER31_CHG_CTRL0_EN_PG_NTC2_PG       0x00
#define CHARGER31_CHG_CTRL0_EN_PG_NTC2_NTC2     0x20
#define CHARGER31_CHG_CTRL0_EN_PG_NTC2_MASK     0x20
#define CHARGER31_CHG_CTRL0_LOCK_CHG_UNLOCKED   0x00
#define CHARGER31_CHG_CTRL0_LOCK_CHG_LOCKED     0x10
#define CHARGER31_CHG_CTRL0_LOCK_CHG_MASK       0x10
#define CHARGER31_CHG_CTRL0_HOLDOFF_TMR_DIS     0x00
#define CHARGER31_CHG_CTRL0_HOLDOFF_TMR_EN      0x08
#define CHARGER31_CHG_CTRL0_HOLDOFF_TMR_MASK    0x08
#define CHARGER31_CHG_CTRL0_SW_FREQ_750K        0x00
#define CHARGER31_CHG_CTRL0_SW_FREQ_1M          0x02
#define CHARGER31_CHG_CTRL0_SW_FREQ_1_25M       0x04
#define CHARGER31_CHG_CTRL0_SW_FREQ_1_5M        0x06
#define CHARGER31_CHG_CTRL0_SW_FREQ_MASK        0x06
#define CHARGER31_CHG_CTRL0_EN_VIN_TRK_FIXED    0x00
#define CHARGER31_CHG_CTRL0_EN_VIN_TRK_VBATT    0x01
#define CHARGER31_CHG_CTRL0_EN_VIN_TRK_MASK     0x01

/**
 * @brief Charger 31 IIN register setting.
 * @details Specified setting for IIN register of Charger 31 Click driver.
 */
#define CHARGER31_IIN_MODE_LIM                  0x00
#define CHARGER31_IIN_MODE_FORCE_100MA          0x20
#define CHARGER31_IIN_MODE_FORCE_500MA          0x40
#define CHARGER31_IIN_MODE_FORCE_900MA          0x60
#define CHARGER31_IIN_MODE_FORCE_1500MA         0x80
#define CHARGER31_IIN_MODE_FORCE_2000MA         0xA0
#define CHARGER31_IIN_MODE_FORCE_3000MA         0xC0
#define CHARGER31_IIN_MODE_MASK                 0xE0
#define CHARGER31_IIN_LIM_MASK                  0x1F
#define CHARGER31_IIN_LIM_MA_RES                100
#define CHARGER31_IIN_LIM_MA_OFFSET             100
#define CHARGER31_IIN_LIM_MA_MIN                100
#define CHARGER31_IIN_LIM_MA_DEFAULT            500
#define CHARGER31_IIN_LIM_MA_MAX                3200
#define CHARGER31_IIN_LIM_MA(x)                 ( ( ( x - CHARGER31_IIN_LIM_MA_OFFSET ) / \
                                                    CHARGER31_IIN_LIM_MA_RES ) & CHARGER31_IIN_LIM_MASK )

/**
 * @brief Charger 31 CHG_PAR0 register setting.
 * @details Specified setting for CHG_PAR0 register of Charger 31 Click driver.
 */
#define CHARGER31_CHG_PAR0_VPRE_2_6V            0x00
#define CHARGER31_CHG_PAR0_VPRE_2_8V            0x40
#define CHARGER31_CHG_PAR0_VPRE_3_0V            0x80
#define CHARGER31_CHG_PAR0_VPRE_3_2V            0xC0
#define CHARGER31_CHG_PAR0_VPRE_MASK            0xC0
#define CHARGER31_CHG_PAR0_ICC_MASK             0x3F
#define CHARGER31_CHG_PAR0_ICC_MA_RES           40
#define CHARGER31_CHG_PAR0_ICC_MA_OFFSET        0
#define CHARGER31_CHG_PAR0_ICC_MA_MIN           0
#define CHARGER31_CHG_PAR0_ICC_MA_DEFAULT       200
#define CHARGER31_CHG_PAR0_ICC_MA_MAX           2200
#define CHARGER31_CHG_PAR0_ICC_MA(x)            ( ( ( x - CHARGER31_CHG_PAR0_ICC_MA_OFFSET ) / \
                                                    CHARGER31_CHG_PAR0_ICC_MA_RES ) & CHARGER31_CHG_PAR0_ICC_MASK )

/**
 * @brief Charger 31 CHG_PAR1 register setting.
 * @details Specified setting for CHG_PAR1 register of Charger 31 Click driver.
 */
#define CHARGER31_CHG_PAR1_IPRE_MASK            0xF0
#define CHARGER31_CHG_PAR1_IPRE_SHIFT           4
#define CHARGER31_CHG_PAR1_IPRE_MA_RES          20
#define CHARGER31_CHG_PAR1_IPRE_MA_OFFSET       0
#define CHARGER31_CHG_PAR1_IPRE_MA_MIN          0
#define CHARGER31_CHG_PAR1_IPRE_MA_DEFAULT      20
#define CHARGER31_CHG_PAR1_IPRE_MA_MAX          300
#define CHARGER31_CHG_PAR1_IPRE_MA(x)           ( ( ( ( x - CHARGER31_CHG_PAR1_IPRE_MA_OFFSET ) / \
                                                      CHARGER31_CHG_PAR1_IPRE_MA_RES ) << CHARGER31_CHG_PAR1_IPRE_SHIFT ) & \
                                                  CHARGER31_CHG_PAR1_IPRE_MASK )
#define CHARGER31_CHG_PAR1_ITERM_MASK           0x0F
#define CHARGER31_CHG_PAR1_ITERM_MA_RES         15
#define CHARGER31_CHG_PAR1_ITERM_MA_OFFSET      15
#define CHARGER31_CHG_PAR1_ITERM_MA_MIN         15
#define CHARGER31_CHG_PAR1_ITERM_MA_DEFAULT     30
#define CHARGER31_CHG_PAR1_ITERM_MA_MAX         240
#define CHARGER31_CHG_PAR1_ITERM_MA(x)          ( ( ( x - CHARGER31_CHG_PAR1_ITERM_MA_OFFSET ) / \
                                                    CHARGER31_CHG_PAR1_ITERM_MA_RES ) & CHARGER31_CHG_PAR1_ITERM_MASK )

/**
 * @brief Charger 31 CHG_PAR2 register setting.
 * @details Specified setting for CHG_PAR2 register of Charger 31 Click driver.
 */
#define CHARGER31_CHG_PAR2_VRECHG_100MV         0x00
#define CHARGER31_CHG_PAR2_VRECHG_200MV         0x80
#define CHARGER31_CHG_PAR2_VRECHG_MASK          0x80
#define CHARGER31_CHG_PAR2_ITRICKLE_MASK        0x70
#define CHARGER31_CHG_PAR2_ITRICKLE_SHIFT       4
#define CHARGER31_CHG_PAR2_ITRICKLE_MA_RES      16
#define CHARGER31_CHG_PAR2_ITRICKLE_MA_OFFSET   0
#define CHARGER31_CHG_PAR2_ITRICKLE_MA_MIN      0
#define CHARGER31_CHG_PAR2_ITRICKLE_MA_DEFAULT  16
#define CHARGER31_CHG_PAR2_ITRICKLE_MA_MAX      112
#define CHARGER31_CHG_PAR2_ITRICKLE_MA(x)       ( ( ( ( x - CHARGER31_CHG_PAR2_ITRICKLE_MA_OFFSET ) / \
                                                      CHARGER31_CHG_PAR2_ITRICKLE_MA_RES ) << CHARGER31_CHG_PAR2_ITRICKLE_SHIFT ) & \
                                                  CHARGER31_CHG_PAR2_ITRICKLE_MASK )
#define CHARGER31_CHG_PAR2_VIN_LIM_MASK         0x0F
#define CHARGER31_CHG_PAR2_VIN_LIM_MV_RES       80
#define CHARGER31_CHG_PAR2_VIN_LIM_MV_OFFSET    3880
#define CHARGER31_CHG_PAR2_VIN_LIM_MV_MIN       3880
#define CHARGER31_CHG_PAR2_VIN_LIM_MV_DEFAULT   4360
#define CHARGER31_CHG_PAR2_VIN_LIM_MV_MAX       5080
#define CHARGER31_CHG_PAR2_VIN_LIM_MV(x)        ( ( ( x - CHARGER31_CHG_PAR2_VIN_LIM_MV_OFFSET ) / \
                                                    CHARGER31_CHG_PAR2_VIN_LIM_MV_RES ) & CHARGER31_CHG_PAR2_VIN_LIM_MASK )

/**
 * @brief Charger 31 CHG_PAR3 register setting.
 * @details Specified setting for CHG_PAR3 register of Charger 31 Click driver.
 */
#define CHARGER31_CHG_PAR3_TOPOFF_TMR_DIS       0x00
#define CHARGER31_CHG_PAR3_TOPOFF_TMR_15_MIN    0x40
#define CHARGER31_CHG_PAR3_TOPOFF_TMR_31_MIN    0x80
#define CHARGER31_CHG_PAR3_TOPOFF_TMR_45_MIN    0xC0
#define CHARGER31_CHG_PAR3_TOPOFF_TMR_MASK      0xC0
#define CHARGER31_CHG_PAR3_VBATT_MASK           0x3F
#define CHARGER31_CHG_PAR3_VBATT_MV_RES         25
#define CHARGER31_CHG_PAR3_VBATT_MV_OFFSET      3600
#define CHARGER31_CHG_PAR3_VBATT_MV_MIN         3600
#define CHARGER31_CHG_PAR3_VBATT_MV_DEFAULT     4200
#define CHARGER31_CHG_PAR3_VBATT_MV_MAX         4600
#define CHARGER31_CHG_PAR3_VBATT_MV(x)          ( ( ( x - CHARGER31_CHG_PAR3_VBATT_MV_OFFSET ) / \
                                                    CHARGER31_CHG_PAR3_VBATT_MV_RES ) & CHARGER31_CHG_PAR3_VBATT_MASK )

/**
 * @brief Charger 31 CHG_CTRL1 register setting.
 * @details Specified setting for CHG_CTRL1 register of Charger 31 Click driver.
 */
#define CHARGER31_CHG_CTRL1_SYS_MIN_2_975V      0x00
#define CHARGER31_CHG_CTRL1_SYS_MIN_3_15V       0x08
#define CHARGER31_CHG_CTRL1_SYS_MIN_3_325V      0x10
#define CHARGER31_CHG_CTRL1_SYS_MIN_3_5V        0x18
#define CHARGER31_CHG_CTRL1_SYS_MIN_3_588V      0x20
#define CHARGER31_CHG_CTRL1_SYS_MIN_3_675V      0x28
#define CHARGER31_CHG_CTRL1_SYS_MIN_3_763V      0x30
#define CHARGER31_CHG_CTRL1_SYS_MIN_MASK        0x38
#define CHARGER31_CHG_CTRL1_TREG_60_C           0x00
#define CHARGER31_CHG_CTRL1_TREG_70_C           0x01
#define CHARGER31_CHG_CTRL1_TREG_80_C           0x02
#define CHARGER31_CHG_CTRL1_TREG_90_C           0x03
#define CHARGER31_CHG_CTRL1_TREG_100_C          0x04
#define CHARGER31_CHG_CTRL1_TREG_110_C          0x05
#define CHARGER31_CHG_CTRL1_TREG_120_C          0x06
#define CHARGER31_CHG_CTRL1_TREG_MASK           0x07

/**
 * @brief Charger 31 CHG_CTRL2 register setting.
 * @details Specified setting for CHG_CTRL2 register of Charger 31 Click driver.
 */
#define CHARGER31_CHG_CTRL2_IB_EN_WHEN_SW_ON    0x00
#define CHARGER31_CHG_CTRL2_IB_EN_ALL_THE_TIME  0x80
#define CHARGER31_CHG_CTRL2_IB_EN_MASK          0x80
#define CHARGER31_CHG_CTRL2_WATCHDOG_RST_KEEP   0x00
#define CHARGER31_CHG_CTRL2_WATCHDOG_RST_RESET  0x40
#define CHARGER31_CHG_CTRL2_WATCHDOG_RST_MASK   0x40
#define CHARGER31_CHG_CTRL2_WATCHDOG_DIS        0x00
#define CHARGER31_CHG_CTRL2_WATCHDOG_40S        0x10
#define CHARGER31_CHG_CTRL2_WATCHDOG_80S        0x20
#define CHARGER31_CHG_CTRL2_WATCHDOG_160S       0x30
#define CHARGER31_CHG_CTRL2_WATCHDOG_MASK       0x30
#define CHARGER31_CHG_CTRL2_EN_TERM_DIS         0x00
#define CHARGER31_CHG_CTRL2_EN_TERM_EN          0x08
#define CHARGER31_CHG_CTRL2_EN_TERM_MASK        0x08
#define CHARGER31_CHG_CTRL2_EN_TMR2X_DIS        0x00
#define CHARGER31_CHG_CTRL2_EN_TMR2X_EN         0x04
#define CHARGER31_CHG_CTRL2_EN_TMR2X_MASK       0x04
#define CHARGER31_CHG_CTRL2_CHG_TIMER_DIS       0x00
#define CHARGER31_CHG_CTRL2_CHG_TIMER_5H        0x01
#define CHARGER31_CHG_CTRL2_CHG_TIMER_10H       0x02
#define CHARGER31_CHG_CTRL2_CHG_TIMER_15H       0x03
#define CHARGER31_CHG_CTRL2_CHG_TIMER_MASK      0x03

/**
 * @brief Charger 31 CHG_CTRL3 register setting.
 * @details Specified setting for CHG_CTRL3 register of Charger 31 Click driver.
 */
#define CHARGER31_CHG_CTRL3_BATTFET_DIS_OFF     0x00
#define CHARGER31_CHG_CTRL3_BATTFET_DIS_ON      0x80
#define CHARGER31_CHG_CTRL3_BATTFET_DIS_MASK    0x80
#define CHARGER31_CHG_CTRL3_BATTFET_DLY_DIS     0x00
#define CHARGER31_CHG_CTRL3_BATTFET_DLY_10S     0x40
#define CHARGER31_CHG_CTRL3_BATTFET_DLY_MASK    0x40
#define CHARGER31_CHG_CTRL3_BATTFET_RST_EN_OFF  0x00
#define CHARGER31_CHG_CTRL3_BATTFET_RST_EN_ON   0x20
#define CHARGER31_CHG_CTRL3_BATTFET_RST_EN_MASK 0x20
#define CHARGER31_CHG_CTRL3_OLIM_0_5A           0x00
#define CHARGER31_CHG_CTRL3_OLIM_1_5A           0x08
#define CHARGER31_CHG_CTRL3_OLIM_2_1A           0x10
#define CHARGER31_CHG_CTRL3_OLIM_3A             0x18
#define CHARGER31_CHG_CTRL3_OLIM_MASK           0x18
#define CHARGER31_CHG_CTRL3_VBOOST_5_2V         0x00
#define CHARGER31_CHG_CTRL3_VBOOST_5_25V        0x01
#define CHARGER31_CHG_CTRL3_VBOOST_5_3V         0x02
#define CHARGER31_CHG_CTRL3_VBOOST_5_35V        0x03
#define CHARGER31_CHG_CTRL3_VBOOST_5V           0x04
#define CHARGER31_CHG_CTRL3_VBOOST_5_05V        0x05
#define CHARGER31_CHG_CTRL3_VBOOST_5_1V         0x06
#define CHARGER31_CHG_CTRL3_VBOOST_5_15V        0x07
#define CHARGER31_CHG_CTRL3_VBOOST_MASK         0x07

/**
 * @brief Charger 31 CHG_CTRL4 register setting.
 * @details Specified setting for CHG_CTRL4 register of Charger 31 Click driver.
 */
#define CHARGER31_CHG_CTRL4_CC_CFG_EN           0x00
#define CHARGER31_CHG_CTRL4_CC_CFG_DIS          0x50
#define CHARGER31_CHG_CTRL4_CC_CFG_MASK         0x70
#define CHARGER31_CHG_CTRL4_EN_BOOST_DIS        0x00
#define CHARGER31_CHG_CTRL4_EN_BOOST_EN         0x04
#define CHARGER31_CHG_CTRL4_EN_BOOST_MASK       0x04
#define CHARGER31_CHG_CTRL4_EN_BUCK_DIS         0x00
#define CHARGER31_CHG_CTRL4_EN_BUCK_EN          0x02
#define CHARGER31_CHG_CTRL4_EN_BUCK_MASK        0x02
#define CHARGER31_CHG_CTRL4_EN_CHG_DIS          0x00
#define CHARGER31_CHG_CTRL4_EN_CHG_EN           0x01
#define CHARGER31_CHG_CTRL4_EN_CHG_MASK         0x01

/**
 * @brief Charger 31 VIN_DET register setting.
 * @details Specified setting for VIN_DET register of Charger 31 Click driver.
 */
#define CHARGER31_VIN_DET_AUTODPDM_DIS          0x00
#define CHARGER31_VIN_DET_AUTODPDM_EN           0x20
#define CHARGER31_VIN_DET_AUTODPDM_MASK         0x20
#define CHARGER31_VIN_DET_FORCEDPDM_DIS         0x00
#define CHARGER31_VIN_DET_FORCEDPDM_EN          0x10
#define CHARGER31_VIN_DET_FORCEDPDM_MASK        0x10
#define CHARGER31_VIN_DET_FORCE_CC_DIS          0x00
#define CHARGER31_VIN_DET_FORCE_CC_EN           0x03
#define CHARGER31_VIN_DET_FORCE_CC_MASK         0x03

/**
 * @brief Charger 31 CHG_CTRL5 register setting.
 * @details Specified setting for CHG_CTRL5 register of Charger 31 Click driver.
 */
#define CHARGER31_CHG_CTRL5_NTC1_ACTION_ON_CHG  0x00
#define CHARGER31_CHG_CTRL5_NTC1_ACTION_FULL    0x40
#define CHARGER31_CHG_CTRL5_NTC1_ACTION_MASK    0x40
#define CHARGER31_CHG_CTRL5_NTC2_ACTION_ON_CHG  0x00
#define CHARGER31_CHG_CTRL5_NTC2_ACTION_FULL    0x20
#define CHARGER31_CHG_CTRL5_NTC2_ACTION_MASK    0x20
#define CHARGER31_CHG_CTRL5_BATT_OVP_EN_OFF     0x00
#define CHARGER31_CHG_CTRL5_BATT_OVP_EN_ON      0x10
#define CHARGER31_CHG_CTRL5_BATT_OVP_EN_MASK    0x10
#define CHARGER31_CHG_CTRL5_BATT_LOW_3V         0x00
#define CHARGER31_CHG_CTRL5_BATT_LOW_3_1V       0x04
#define CHARGER31_CHG_CTRL5_BATT_LOW_3_2V       0x08
#define CHARGER31_CHG_CTRL5_BATT_LOW_3_3V       0x0C
#define CHARGER31_CHG_CTRL5_BATT_LOW_MASK       0x0C
#define CHARGER31_CHG_CTRL5_BOOST_STP_EN_OFF    0x00
#define CHARGER31_CHG_CTRL5_BOOST_STP_EN_ON     0x02
#define CHARGER31_CHG_CTRL5_BOOST_STP_EN_MASK   0x02
#define CHARGER31_CHG_CTRL5_BOOST_OTP_EN_OFF    0x00
#define CHARGER31_CHG_CTRL5_BOOST_OTP_EN_ON     0x01
#define CHARGER31_CHG_CTRL5_BOOST_OTP_EN_MASK   0x01

/**
 * @brief Charger 31 NTC_ACTION register setting.
 * @details Specified setting for NTC_ACTION register of Charger 31 Click driver.
 */
#define CHARGER31_NTC_ACTION_WARM_ACT_NO_ACTION 0x00
#define CHARGER31_NTC_ACTION_WARM_ACT_VBATT     0x40
#define CHARGER31_NTC_ACTION_WARM_ACT_ICC       0x80
#define CHARGER31_NTC_ACTION_WARM_ACT_BOTH      0xC0
#define CHARGER31_NTC_ACTION_WARM_ACT_MASK      0xC0
#define CHARGER31_NTC_ACTION_COOL_ACT_NO_ACTION 0x00
#define CHARGER31_NTC_ACTION_COOL_ACT_VBATT     0x10
#define CHARGER31_NTC_ACTION_COOL_ACT_ICC       0x20
#define CHARGER31_NTC_ACTION_COOL_ACT_BOTH      0x30
#define CHARGER31_NTC_ACTION_COOL_ACT_MASK      0x30
#define CHARGER31_NTC_ACTION_JEITA_VSET_100_MV  0x00
#define CHARGER31_NTC_ACTION_JEITA_VSET_150_MV  0x40
#define CHARGER31_NTC_ACTION_JEITA_VSET_200_MV  0x80
#define CHARGER31_NTC_ACTION_JEITA_VSET_250_MV  0xC0
#define CHARGER31_NTC_ACTION_JEITA_VSET_MASK    0xC0
#define CHARGER31_NTC_ACTION_JEITA_ISET_50_PCT  0x00
#define CHARGER31_NTC_ACTION_JEITA_ISET_33_PCT  0x01
#define CHARGER31_NTC_ACTION_JEITA_ISET_20_PCT  0x02
#define CHARGER31_NTC_ACTION_JEITA_ISET_MASK    0x03

/**
 * @brief Charger 31 NTC_TH register setting.
 * @details Specified setting for NTC_TH register of Charger 31 Click driver.
 */
#define CHARGER31_NTC_TH_VHOT_50_C              0x00
#define CHARGER31_NTC_TH_VHOT_55_C              0x40
#define CHARGER31_NTC_TH_VHOT_60_C              0x80
#define CHARGER31_NTC_TH_VHOT_65_C              0xC0
#define CHARGER31_NTC_TH_VHOT_MASK              0xC0
#define CHARGER31_NTC_TH_VWARM_40_C             0x00
#define CHARGER31_NTC_TH_VWARM_45_C             0x10
#define CHARGER31_NTC_TH_VWARM_50_C             0x20
#define CHARGER31_NTC_TH_VWARM_55_C             0x30
#define CHARGER31_NTC_TH_VWARM_MASK             0x30
#define CHARGER31_NTC_TH_VCOOL_0_C              0x00
#define CHARGER31_NTC_TH_VCOOL_5_C              0x04
#define CHARGER31_NTC_TH_VCOOL_10_C             0x08
#define CHARGER31_NTC_TH_VCOOL_15_C             0x0C
#define CHARGER31_NTC_TH_VCOOL_MASK             0x0C
#define CHARGER31_NTC_TH_VCOLD_MIN_5_C          0x00
#define CHARGER31_NTC_TH_VCOLD_0_C              0x01
#define CHARGER31_NTC_TH_VCOLD_5_C              0x02
#define CHARGER31_NTC_TH_VCOLD_10_C             0x03
#define CHARGER31_NTC_TH_VCOLD_MASK             0x03

/**
 * @brief Charger 31 VIN_IMPD register setting.
 * @details Specified setting for VIN_IMPD register of Charger 31 Click driver.
 */
#define CHARGER31_VIN_IMPD_VIN_SRC_EN_OFF       0x00
#define CHARGER31_VIN_IMPD_VIN_SRC_EN_ON        0x40
#define CHARGER31_VIN_IMPD_VIN_SRC_EN_MASK      0x40
#define CHARGER31_VIN_IMPD_IVIN_SRC_5_UA        0x00
#define CHARGER31_VIN_IMPD_IVIN_SRC_10_UA       0x04
#define CHARGER31_VIN_IMPD_IVIN_SRC_20_UA       0x08
#define CHARGER31_VIN_IMPD_IVIN_SRC_40_UA       0x0C
#define CHARGER31_VIN_IMPD_IVIN_SRC_80_UA       0x10
#define CHARGER31_VIN_IMPD_IVIN_SRC_160_UA      0x14
#define CHARGER31_VIN_IMPD_IVIN_SRC_320_UA      0x18
#define CHARGER31_VIN_IMPD_IVIN_SRC_640_UA      0x1C
#define CHARGER31_VIN_IMPD_IVIN_SRC_1280_UA     0x20
#define CHARGER31_VIN_IMPD_IVIN_SRC_MASK        0x3C
#define CHARGER31_VIN_IMPD_VIN_TEST_0_3V        0x00
#define CHARGER31_VIN_IMPD_VIN_TEST_0_5V        0x01
#define CHARGER31_VIN_IMPD_VIN_TEST_1V          0x02
#define CHARGER31_VIN_IMPD_VIN_TEST_1_5V        0x03
#define CHARGER31_VIN_IMPD_VIN_TEST_MASK        0x03

/**
 * @brief Charger 31 INT_MASK register setting.
 * @details Specified setting for INT_MASK register of Charger 31 Click driver.
 */
#define CHARGER31_INT_MASK_MASK_RESERVED        0x40
#define CHARGER31_INT_MASK_MASK_THERM_OFF       0x00
#define CHARGER31_INT_MASK_MASK_THERM_ON        0x20
#define CHARGER31_INT_MASK_MASK_THERM_MASK      0x20
#define CHARGER31_INT_MASK_MASK_DPM_OFF         0x00
#define CHARGER31_INT_MASK_MASK_DPM_ON          0x10
#define CHARGER31_INT_MASK_MASK_DPM_MASK        0x10
#define CHARGER31_INT_MASK_MASK_TOPOFF_OFF      0x00
#define CHARGER31_INT_MASK_MASK_TOPOFF_ON       0x08
#define CHARGER31_INT_MASK_MASK_TOPOFF_MASK     0x08
#define CHARGER31_INT_MASK_MASK_CC_INT_OFF      0x00
#define CHARGER31_INT_MASK_MASK_CC_INT_ON       0x04
#define CHARGER31_INT_MASK_MASK_CC_INT_MASK     0x04
#define CHARGER31_INT_MASK_MASK_BATT_LOW_OFF    0x00
#define CHARGER31_INT_MASK_MASK_BATT_LOW_ON     0x02
#define CHARGER31_INT_MASK_MASK_BATT_LOW_MASK   0x02
#define CHARGER31_INT_MASK_MASK_DEBUG_OFF       0x00
#define CHARGER31_INT_MASK_MASK_DEBUG_ON        0x01
#define CHARGER31_INT_MASK_MASK_DEBUG_MASK      0x01

/**
 * @brief Charger 31 STATUS0 register setting.
 * @details Specified setting for STATUS0 register of Charger 31 Click driver.
 */
#define CHARGER31_STATUS0_DPDM_STAT_NOT_STARTED 0x00
#define CHARGER31_STATUS0_DPDM_STAT_USB_SDP     0x10
#define CHARGER31_STATUS0_DPDM_STAT_USB_DCP     0x20
#define CHARGER31_STATUS0_DPDM_STAT_USB_CDP     0x30
#define CHARGER31_STATUS0_DPDM_STAT_DIV_1       0x40
#define CHARGER31_STATUS0_DPDM_STAT_DIV_2       0x50
#define CHARGER31_STATUS0_DPDM_STAT_DIV_3       0x60
#define CHARGER31_STATUS0_DPDM_STAT_DIV_4       0x70
#define CHARGER31_STATUS0_DPDM_STAT_UNKNOWN     0x80
#define CHARGER31_STATUS0_DPDM_STAT_USB_DCP_2   0x90
#define CHARGER31_STATUS0_DPDM_STAT_DIV_5       0xE0
#define CHARGER31_STATUS0_DPDM_STAT_MASK        0xF0
#define CHARGER31_STATUS0_VINDPM_STAT_IDLE      0x00
#define CHARGER31_STATUS0_VINDPM_STAT_SET       0x02
#define CHARGER31_STATUS0_VINDPM_STAT_MASK      0x02
#define CHARGER31_STATUS0_IINDPM_STAT_IDLE      0x00
#define CHARGER31_STATUS0_IINDPM_STAT_SET       0x01
#define CHARGER31_STATUS0_IINDPM_STAT_MASK      0x01

/**
 * @brief Charger 31 STATUS1 register setting.
 * @details Specified setting for STATUS1 register of Charger 31 Click driver.
 */
#define CHARGER31_STATUS1_VIN_GD                0x40
#define CHARGER31_STATUS1_VIN_RDY               0x20
#define CHARGER31_STATUS1_LEGACYCABLE           0x10
#define CHARGER31_STATUS1_THERM_STAT            0x08
#define CHARGER31_STATUS1_VSYS_STAT             0x04
#define CHARGER31_STATUS1_WATCHDOG_FAULT        0x02
#define CHARGER31_STATUS1_WATCHDOG_BARK         0x01

/**
 * @brief Charger 31 STATUS2 register setting.
 * @details Specified setting for STATUS2 register of Charger 31 Click driver.
 */
#define CHARGER31_STATUS2_CHG_STAT_NOT_CHARGING 0x00
#define CHARGER31_STATUS2_CHG_STAT_TRICKLE_CHG  0x20
#define CHARGER31_STATUS2_CHG_STAT_PRE_CHG      0x40
#define CHARGER31_STATUS2_CHG_STAT_FAST_CHG     0x60
#define CHARGER31_STATUS2_CHG_STAT_CV_CHG       0x80
#define CHARGER31_STATUS2_CHG_STAT_CHG_DONE     0xA0
#define CHARGER31_STATUS2_CHG_STAT_MASK         0xE0
#define CHARGER31_STATUS2_BOOST_FAULT_NORMAL    0x00
#define CHARGER31_STATUS2_BOOST_FAULT_IN_SHORT  0x04
#define CHARGER31_STATUS2_BOOST_FAULT_OVP       0x08
#define CHARGER31_STATUS2_BOOST_FAULT_OVTP      0x0C
#define CHARGER31_STATUS2_BOOST_FAULT_BATT_LOW  0x10
#define CHARGER31_STATUS2_BOOST_FAULT_MASK      0x1C
#define CHARGER31_STATUS2_CHG_FAULT_NORMAL      0x00
#define CHARGER31_STATUS2_CHG_FAULT_IN_OVP      0x01
#define CHARGER31_STATUS2_CHG_FAULT_TIMER       0x02
#define CHARGER31_STATUS2_CHG_FAULT_BATT_OVP    0x03
#define CHARGER31_STATUS2_CHG_FAULT_MASK        0x03

/**
 * @brief Charger 31 STATUS3 register setting.
 * @details Specified setting for STATUS3 register of Charger 31 Click driver.
 */
#define CHARGER31_STATUS3_NTC_MISSING           0x80
#define CHARGER31_STATUS3_BATT_MISSING          0x40
#define CHARGER31_STATUS3_NTC1_FAULT_NORMAL     0x00
#define CHARGER31_STATUS3_NTC1_FAULT_WARM       0x08
#define CHARGER31_STATUS3_NTC1_FAULT_COOL       0x10
#define CHARGER31_STATUS3_NTC1_FAULT_COLD       0x18
#define CHARGER31_STATUS3_NTC1_FAULT_HOT        0x20
#define CHARGER31_STATUS3_NTC1_FAULT_MASK       0x38
#define CHARGER31_STATUS3_NTC2_FAULT_NORMAL     0x00
#define CHARGER31_STATUS3_NTC2_FAULT_WARM       0x01
#define CHARGER31_STATUS3_NTC2_FAULT_COOL       0x02
#define CHARGER31_STATUS3_NTC2_FAULT_COLD       0x03
#define CHARGER31_STATUS3_NTC2_FAULT_HOT        0x04
#define CHARGER31_STATUS3_NTC2_FAULT_MASK       0x07

/**
 * @brief Charger 31 STATUS4 register setting.
 * @details Specified setting for STATUS4 register of Charger 31 Click driver.
 */
#define CHARGER31_STATUS4_CC1_SNK_STAT_VRA      0x00
#define CHARGER31_STATUS4_CC1_SNK_STAT_VRD_USB  0x40
#define CHARGER31_STATUS4_CC1_SNK_STAT_VRD_1_5  0x80
#define CHARGER31_STATUS4_CC1_SNK_STAT_VRD_3_0  0xC0
#define CHARGER31_STATUS4_CC1_SNK_STAT_MASK     0x38
#define CHARGER31_STATUS4_CC2_SNK_STAT_VRA      0x00
#define CHARGER31_STATUS4_CC2_SNK_STAT_VRD_USB  0x10
#define CHARGER31_STATUS4_CC2_SNK_STAT_VRD_1_5  0x20
#define CHARGER31_STATUS4_CC2_SNK_STAT_VRD_3_0  0x30
#define CHARGER31_STATUS4_CC2_SNK_STAT_MASK     0x38

/**
 * @brief Charger 31 STATUS5 register setting.
 * @details Specified setting for STATUS5 register of Charger 31 Click driver.
 */
#define CHARGER31_STATUS5_TOPOFF_ACTIVE         0x40
#define CHARGER31_STATUS5_BFET_STAT_DISCHARGING 0x20
#define CHARGER31_STATUS5_BATT_LOW              0x10
#define CHARGER31_STATUS5_VIN_TEST_HIGH         0x04
#define CHARGER31_STATUS5_DEBUGACC              0x02

/**
 * @brief Charger 31 device address setting.
 * @details Specified setting for device slave address selection of
 * Charger 31 Click driver.
 */
#define CHARGER31_DEVICE_ADDRESS                0x3F

/*! @} */ // charger31_set

/**
 * @defgroup charger31_map Charger 31 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 31 Click driver.
 */

/**
 * @addtogroup charger31_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 31 Click to the selected MikroBUS.
 */
#define CHARGER31_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.st_ib = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger31_map
/*! @} */ // charger31

/**
 * @brief Charger 31 Click status object.
 * @details Status object definition of Charger 31 Click driver.
 */
typedef struct
{
    uint8_t status_0;           /**< Status 0 register value. */
    uint8_t status_1;           /**< Status 1 register value. */
    uint8_t status_2;           /**< Status 2 register value. */
    uint8_t status_3;           /**< Status 3 register value. */
    uint8_t status_4;           /**< Status 4 register value. */
    uint8_t status_5;           /**< Status 5 register value. */

} charger31_status_t;

/**
 * @brief Charger 31 Click context object.
 * @details Context object definition of Charger 31 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t st_ib;         /**< Charge status (STA) or battery current indication (IB) pin (active low). */
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} charger31_t;

/**
 * @brief Charger 31 Click configuration object.
 * @details Configuration object definition of Charger 31 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t st_ib;           /**< Charge status (STA) or battery current indication (IB) pin (active low). */
    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} charger31_cfg_t;

/**
 * @brief Charger 31 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER31_OK = 0,
    CHARGER31_ERROR = -1

} charger31_return_value_t;

/*!
 * @addtogroup charger31 Charger 31 Click Driver
 * @brief API for configuring and manipulating Charger 31 Click driver.
 * @{
 */

/**
 * @brief Charger 31 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger31_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger31_cfg_setup ( charger31_cfg_t *cfg );

/**
 * @brief Charger 31 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #charger31_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger31_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger31_init ( charger31_t *ctx, charger31_cfg_t *cfg );

/**
 * @brief Charger 31 default configuration function.
 * @details This function executes a default configuration of Charger 31
 * Click board.
 * @param[in] ctx : Click context object.
 * See #charger31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t charger31_default_cfg ( charger31_t *ctx );

/**
 * @brief Charger 31 write register function.
 * @details This function writes a single byte of data to the selected register 
 * of the Charger 31 Click board.
 * @param[in] ctx : Click context object.
 * See #charger31_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger31_write_reg ( charger31_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Charger 31 write registers function.
 * @details This function writes a sequence of bytes starting from the selected register 
 * of the Charger 31 Click board.
 * @param[in] ctx : Click context object.
 * See #charger31_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger31_write_regs ( charger31_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Charger 31 read register function.
 * @details This function reads a single byte of data from the selected register 
 * of the Charger 31 Click board.
 * @param[in] ctx : Click context object.
 * See #charger31_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location to store the read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger31_read_reg ( charger31_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Charger 31 read registers function.
 * @details This function reads a sequence of bytes starting from the selected register 
 * of the Charger 31 Click board.
 * @param[in] ctx : Click context object.
 * See #charger31_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the data buffer to store read bytes.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger31_read_regs ( charger31_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Charger 31 get ST_IB pin function.
 * @details This function reads the logic state of the ST_IB pin.
 * @param[in] ctx : Click context object.
 * See #charger31_t object definition for detailed explanation.
 * @return Logic state of the ST_IB pin.
 * @note None.
 */
uint8_t charger31_get_st_ib_pin ( charger31_t *ctx );

/**
 * @brief Charger 31 get INT pin function.
 * @details This function reads the logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #charger31_t object definition for detailed explanation.
 * @return Logic state of the INT pin.
 * @note None.
 */
uint8_t charger31_get_int_pin ( charger31_t *ctx );

/**
 * @brief Charger 31 software reset function.
 * @details This function performs a software reset of the Charger 31 Click board 
 * by writing to the reset bit in the CHG_CTRL0 register.
 * @param[in] ctx : Click context object.
 * See #charger31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger31_sw_reset ( charger31_t *ctx );

/**
 * @brief Charger 31 read status function.
 * @details This function reads multiple status registers and stores the values into the provided status structure.
 * @param[in] ctx : Click context object.
 * See #charger31_t object definition for detailed explanation.
 * @param[out] status : Pointer to the structure to store the device status information.
 * See #charger31_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger31_read_status ( charger31_t *ctx, charger31_status_t *status );

#ifdef __cplusplus
}
#endif
#endif // CHARGER31_H

/*! @} */ // charger31

// ------------------------------------------------------------------------ END
