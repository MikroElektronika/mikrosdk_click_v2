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
 * @file pmic3.h
 * @brief This file contains API for PMIC 3 Click Driver.
 */

#ifndef PMIC3_H
#define PMIC3_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup pmic3 PMIC 3 Click Driver
 * @brief API for configuring and manipulating PMIC 3 Click driver.
 * @{
 */

/**
 * @defgroup pmic3_reg PMIC 3 Registers List
 * @brief List of registers of PMIC 3 Click driver.
 */

/**
 * @addtogroup pmic3_reg
 * @{
 */

/**
 * @brief PMIC 3 top-level system control registers.
 * @details Register addresses for device identification, interrupt handling,
 * system status, watchdog control, and top-level reset configuration.
 */
#define PMIC3_REG_DEV_INFO                      0x00
#define PMIC3_REG_TOP_INT                       0x01
#define PMIC3_REG_SUB_INT0                      0x02
#define PMIC3_REG_SUB_INT0_MASK                 0x03
#define PMIC3_REG_SUB_INT1                      0x04
#define PMIC3_REG_SUB_INT1_MASK                 0x05
#define PMIC3_REG_SUB_INT2                      0x06
#define PMIC3_REG_SUB_INT2_MASK                 0x07
#define PMIC3_REG_TOP_STAT                      0x08
#define PMIC3_REG_TOP_CNTL0                     0x09
#define PMIC3_REG_TOP_CNTL1                     0x0A
#define PMIC3_REG_TOP_CNTL2                     0x0B
#define PMIC3_REG_TOP_CNTL3                     0x0C
#define PMIC3_REG_TOP_CNTL4                     0x0D

/**
 * @brief PMIC 3 regulator control registers.
 * @details Register addresses for power-state monitoring, switcher and LDO
 * configuration, regulator status, GPIO, LED, and wake-up sequencing.
 */
#define PMIC3_REG_INT1                          0x0E
#define PMIC3_REG_INT1_MASK                     0x0F
#define PMIC3_REG_INT1_STATUS                   0x10
#define PMIC3_REG_PWR_STATE                     0x11
#define PMIC3_REG_RESET_CTRL                    0x12
#define PMIC3_REG_SW_RST                        0x13
#define PMIC3_REG_PWR_SEQ_CTRL                  0x14
#define PMIC3_REG_SYS_CFG1                      0x15
#define PMIC3_REG_SYS_CFG2                      0x16
#define PMIC3_REG_REG_STATUS                    0x17
#define PMIC3_REG_BUCK123_DVS_CFG1              0x18
#define PMIC3_REG_BUCK123_DVS_CFG2              0x19
#define PMIC3_REG_BUCK1_CTRL                    0x1A
#define PMIC3_REG_BUCK1_OUT_DVS0                0x1B
#define PMIC3_REG_BUCK1_OUT_DVS1                0x1C
#define PMIC3_REG_BUCK1_OUT_DVS2                0x1D
#define PMIC3_REG_BUCK1_OUT_DVS3                0x1E
#define PMIC3_REG_BUCK1_OUT_DVS4                0x1F
#define PMIC3_REG_BUCK1_OUT_DVS5                0x20
#define PMIC3_REG_BUCK1_OUT_DVS6                0x21
#define PMIC3_REG_BUCK1_OUT_DVS7                0x22
#define PMIC3_REG_BUCK1_OUT_STBY                0x23
#define PMIC3_REG_BUCK1_OUT_MAX                 0x24
#define PMIC3_REG_BUCK1_OUT_SLEEP               0x25
#define PMIC3_REG_BUCK2_CTRL                    0x26
#define PMIC3_REG_BUCK2_OUT_DVS0                0x27
#define PMIC3_REG_BUCK2_OUT_DVS1                0x28
#define PMIC3_REG_BUCK2_OUT_DVS2                0x29
#define PMIC3_REG_BUCK2_OUT_DVS3                0x2A
#define PMIC3_REG_BUCK2_OUT_DVS4                0x2B
#define PMIC3_REG_BUCK2_OUT_DVS5                0x2C
#define PMIC3_REG_BUCK2_OUT_DVS6                0x2D
#define PMIC3_REG_BUCK2_OUT_DVS7                0x2E
#define PMIC3_REG_BUCK2_OUT_STBY                0x2F
#define PMIC3_REG_BUCK2_OUT_MAX                 0x30
#define PMIC3_REG_BUCK2_OUT_SLEEP               0x31
#define PMIC3_REG_BUCK3_CTRL                    0x32
#define PMIC3_REG_BUCK3_OUT_DVS0                0x33
#define PMIC3_REG_BUCK3_OUT_DVS1                0x34
#define PMIC3_REG_BUCK3_OUT_DVS2                0x35
#define PMIC3_REG_BUCK3_OUT_DVS3                0x36
#define PMIC3_REG_BUCK3_OUT_DVS4                0x37
#define PMIC3_REG_BUCK3_OUT_DVS5                0x38
#define PMIC3_REG_BUCK3_OUT_DVS6                0x39
#define PMIC3_REG_BUCK3_OUT_DVS7                0x3A
#define PMIC3_REG_BUCK3_OUT_STBY                0x3B
#define PMIC3_REG_BUCK3_OUT_MAX                 0x3C
#define PMIC3_REG_BUCK3_OUT_SLEEP               0x3D
#define PMIC3_REG_LPM_FPWM                      0x3E
#define PMIC3_REG_LDO2_CFG                      0x3F
#define PMIC3_REG_LDO2_OUT                      0x40
#define PMIC3_REG_LDO2_OUT_STBY                 0x41
#define PMIC3_REG_LDO3_CFG                      0x42
#define PMIC3_REG_LDO3_OUT                      0x43
#define PMIC3_REG_LDO3_OUT_STBY                 0x44
#define PMIC3_REG_LDO23_CFG                     0x45
#define PMIC3_REG_LDO4_CFG                      0x46
#define PMIC3_REG_LDO4_OUT                      0x47
#define PMIC3_REG_LDO4_OUT_STBY                 0x48
#define PMIC3_REG_LDO1_CFG1                     0x49
#define PMIC3_REG_LDO1_CFG2                     0x4A
#define PMIC3_REG_LDO2_OUT_SLEEP                0x4B
#define PMIC3_REG_LDO3_OUT_SLEEP                0x4C
#define PMIC3_REG_LDO4_OUT_SLEEP                0x4D
#define PMIC3_REG_SW4_BB_CFG1                   0x4E
#define PMIC3_REG_SW4_BB_CFG2                   0x4F
#define PMIC3_REG_SW4_BB_CFG3                   0x50
#define PMIC3_REG_SW4_BB_CFG4                   0x51
#define PMIC3_REG_SW4_BB_MAX                    0x52
#define PMIC3_REG_SW4_BB_MIN                    0x53
#define PMIC3_REG_SW4_BB_SLEEP                  0x54
#define PMIC3_REG_LED_CFG1                      0x55
#define PMIC3_REG_LED_CFG2                      0x56
#define PMIC3_REG_GPIO_STATUS                   0x57
#define PMIC3_REG_GPIO_CFG                      0x58
#define PMIC3_REG_REGULATOR_EN                  0x59
#define PMIC3_REG_WAKEUP_SEQ1                   0x5A
#define PMIC3_REG_WAKEUP_SEQ2                   0x5B

/**
 * @brief PMIC 3 battery charger registers.
 * @details Register addresses for charger interrupts, live device and charger
 * status, VIN control, charger configuration, and analog multiplexer control.
 */
#define PMIC3_REG_INT_DEVICE0                   0x5C
#define PMIC3_REG_INT_DEVICE1                   0x5D
#define PMIC3_REG_INT_CHARGER0                  0x5E
#define PMIC3_REG_INT_CHARGER1                  0x5F
#define PMIC3_REG_INT_CHARGER2                  0x60
#define PMIC3_REG_INT_CHARGER3                  0x61
#define PMIC3_REG_INT_DEVICE0_MASK              0x62
#define PMIC3_REG_INT_DEVICE1_MASK              0x63
#define PMIC3_REG_INT_CHARGER0_MASK             0x64
#define PMIC3_REG_INT_CHARGER1_MASK             0x65
#define PMIC3_REG_INT_CHARGER2_MASK             0x66
#define PMIC3_REG_INT_CHARGER3_MASK             0x67
#define PMIC3_REG_DEVICE0_STS                   0x68
#define PMIC3_REG_DEVICE1_STS                   0x69
#define PMIC3_REG_CHARGER0_STS                  0x6A
#define PMIC3_REG_CHARGER1_STS                  0x6B
#define PMIC3_REG_CHARGER2_STS                  0x6C
#define PMIC3_REG_CHARGER3_STS                  0x6D
#define PMIC3_REG_VIN_CNTL0                     0x6E
#define PMIC3_REG_VIN_CNTL1                     0x6F
#define PMIC3_REG_VIN_CNTL2                     0x70
#define PMIC3_REG_VIN_CNTL3                     0x71
#define PMIC3_REG_CHARGER_CNTL0                 0x72
#define PMIC3_REG_CHARGER_CNTL1                 0x73
#define PMIC3_REG_CHARGER_CNTL2                 0x74
#define PMIC3_REG_CHARGER_CNTL3                 0x75
#define PMIC3_REG_CHARGER_CNTL4                 0x76
#define PMIC3_REG_CHARGER_CNTL5                 0x77
#define PMIC3_REG_CHARGER_CNTL6                 0x78
#define PMIC3_REG_CHARGER_CNTL7                 0x79
#define PMIC3_REG_CHARGER_CNTL8                 0x7A
#define PMIC3_REG_CHARGER_CNTL9                 0x7B
#define PMIC3_REG_CHARGER_CNTL10                0x7C
#define PMIC3_REG_LOCK                          0x80

/*! @} */ // pmic3_reg

/**
 * @defgroup pmic3_set PMIC 3 Registers Settings
 * @brief Settings for registers of PMIC 3 Click driver.
 */

/**
 * @addtogroup pmic3_set
 * @{
 */

/**
 * @brief PMIC 3 pin logic settings.
 * @details Defines the inactive and active logic levels for the active-low ON
 * input and the active-low interrupt output.
 */
#define PMIC3_PIN_STATE_LOW                     0
#define PMIC3_PIN_STATE_HIGH                    1
#define PMIC3_ON_ACTIVE                         PMIC3_PIN_STATE_LOW
#define PMIC3_ON_INACTIVE                       PMIC3_PIN_STATE_HIGH
#define PMIC3_INT_ACTIVE                        PMIC3_PIN_STATE_LOW

/**
 * @brief PMIC 3 device information settings.
 * @details DEV_INFO contains a five-bit device identifier and a three-bit
 * silicon revision code. PCA9422 revisions A0 through B2 use device ID zero.
 */
#define PMIC3_DEV_INFO_ID_MASK                  0xF8
#define PMIC3_DEV_INFO_REV_MASK                 0x07
#define PMIC3_DEV_INFO_ID_PCA9422               0x00
#define PMIC3_DEV_INFO_REV_A0                   0x00
#define PMIC3_DEV_INFO_REV_B0                   0x01
#define PMIC3_DEV_INFO_REV_B1                   0x02
#define PMIC3_DEV_INFO_REV_B2                   0x03
#define PMIC3_DEV_INFO_REV_MAX                  PMIC3_DEV_INFO_REV_B2

/**
 * @brief PMIC 3 top-level interrupt flags.
 * @details TOP_INT identifies the subsystem with a pending interrupt. Reading
 * this register does not clear the corresponding sub-level interrupt flags.
 */
#define PMIC3_TOP_INT_SYS_MASK                  0x10
#define PMIC3_TOP_INT_CHG_MASK                  0x08
#define PMIC3_TOP_INT_SW4_MASK                  0x04
#define PMIC3_TOP_INT_BUCK_MASK                 0x02
#define PMIC3_TOP_INT_LDO_MASK                  0x01

/**
 * @brief PMIC 3 power state settings.
 * @details PWR_STATE reports the current state in the upper nibble and the
 * active DVS or low-power mode in the lower nibble.
 */
#define PMIC3_PWR_STATE_STAT_MASK               0xF0
#define PMIC3_PWR_STATE_MODE_MASK               0x0F
#define PMIC3_PWR_STATE_OFF                     0x00
#define PMIC3_PWR_STATE_AUTO_SNVS               0x40
#define PMIC3_PWR_STATE_PWRUP_SEQ               0x50
#define PMIC3_PWR_STATE_RUN                     0x80
#define PMIC3_PWR_STATE_SNVS                    0xA0
#define PMIC3_PWR_STATE_PWRDN_SEQ               0xC0
#define PMIC3_PWR_STATE_FAULT_SD                0xE0
#define PMIC3_PWR_MODE_ACTIVE_DVS0              0x00
#define PMIC3_PWR_MODE_ACTIVE_DVS1              0x01
#define PMIC3_PWR_MODE_ACTIVE_DVS2              0x02
#define PMIC3_PWR_MODE_ACTIVE_DVS3              0x03
#define PMIC3_PWR_MODE_ACTIVE_DVS4              0x04
#define PMIC3_PWR_MODE_ACTIVE_DVS5              0x05
#define PMIC3_PWR_MODE_ACTIVE_DVS6              0x06
#define PMIC3_PWR_MODE_ACTIVE_DVS7              0x07
#define PMIC3_PWR_MODE_STANDBY                  0x08
#define PMIC3_PWR_MODE_DPSTANDBY                0x0A
#define PMIC3_PWR_MODE_SLEEP                    0x0B

/**
 * @brief PMIC 3 buck regulator identifiers.
 * @details Selects the active-output voltage register used by
 * #pmic3_set_buck_voltage. BUCK4 identifies the SW4 buck-boost regulator.
 */
#define PMIC3_BUCK_1                            1
#define PMIC3_BUCK_2                            2
#define PMIC3_BUCK_3                            3
#define PMIC3_BUCK_4                            4

/**
 * @brief PMIC 3 LDO regulator identifiers.
 * @details Selects the active-output voltage register used by
 * #pmic3_set_ldo_voltage.
 */
#define PMIC3_LDO_1                             1
#define PMIC3_LDO_2                             2
#define PMIC3_LDO_3                             3
#define PMIC3_LDO_4                             4

/**
 * @brief PMIC 3 regulator register lock settings.
 * @details REG_LOCK accepts 0x5C to enable writes to protected regulator
 * registers. Any other value restores write protection.
 */
#define PMIC3_REGULATOR_LOCKED                  0x00
#define PMIC3_REGULATOR_UNLOCKED                0x5C

/**
 * @brief PMIC 3 BUCK1 and BUCK3 voltage settings.
 * @details The active DVS0 output range is 400 mV to 1975 mV in 6.25 mV
 * steps. Integer millivolt requests are rounded to the nearest supported
 * output setting.
 */
#define PMIC3_BUCK13_VOLTAGE_MIN_MV             400
#define PMIC3_BUCK13_VOLTAGE_MAX_MV             1975
#define PMIC3_BUCK13_VOLTAGE_SCALE              4
#define PMIC3_BUCK13_STEP_SCALED                25
#define PMIC3_BUCK13_ROUND_SCALED               12
#define PMIC3_BUCK13_VOLTAGE_MASK               0xFF

/**
 * @brief PMIC 3 BUCK2 voltage settings.
 * @details The active DVS0 output range is 400 mV to 3400 mV in 25 mV steps.
 */
#define PMIC3_BUCK2_VOLTAGE_MIN_MV              400
#define PMIC3_BUCK2_VOLTAGE_MAX_MV              3400
#define PMIC3_BUCK2_VOLTAGE_STEP_MV             25
#define PMIC3_BUCK2_VOLTAGE_ROUND_MV            12
#define PMIC3_BUCK2_VOLTAGE_MASK                0x7F

/**
 * @brief PMIC 3 BUCK4 voltage settings.
 * @details The SW4 buck-boost active output range is 1800 mV to 5000 mV in
 * 25 mV steps. Its output register requires regulator-register unlocking.
 */
#define PMIC3_BUCK4_VOLTAGE_MIN_MV              1800
#define PMIC3_BUCK4_VOLTAGE_MAX_MV              5000
#define PMIC3_BUCK4_VOLTAGE_STEP_MV             25
#define PMIC3_BUCK4_VOLTAGE_ROUND_MV            12
#define PMIC3_BUCK4_VOLTAGE_MASK                0xFF

/**
 * @brief PMIC 3 LDO voltage settings.
 * @details LDO1 supports 800 mV to 3000 mV, LDO2 and LDO3 support 500 mV to
 * 1950 mV, and LDO4 supports 800 mV to 3300 mV. Every LDO uses a 25 mV step;
 * non-voltage control bits in each output register are preserved.
 */
#define PMIC3_LDO1_VOLTAGE_MIN_MV               800
#define PMIC3_LDO1_VOLTAGE_MAX_MV               3000
#define PMIC3_LDO1_VOLTAGE_MASK                 0x7F
#define PMIC3_LDO23_VOLTAGE_MIN_MV              500
#define PMIC3_LDO23_VOLTAGE_MAX_MV              1950
#define PMIC3_LDO23_VOLTAGE_MASK                0x3F
#define PMIC3_LDO4_VOLTAGE_MIN_MV               800
#define PMIC3_LDO4_VOLTAGE_MAX_MV               3300
#define PMIC3_LDO4_VOLTAGE_MASK                 0x7F
#define PMIC3_LDO_VOLTAGE_STEP_MV               25
#define PMIC3_LDO_VOLTAGE_ROUND_MV              12

/**
 * @brief PMIC 3 PCA9422M active-output defaults.
 * @details Default regulator voltages programmed by #pmic3_default_cfg for
 * the PCA9422M OTP configuration.
 */
#define PMIC3_PCA9422M_BUCK1_MV                 1000
#define PMIC3_PCA9422M_BUCK2_MV                 1100
#define PMIC3_PCA9422M_BUCK3_MV                 1000
#define PMIC3_PCA9422M_BUCK4_MV                 1800
#define PMIC3_PCA9422M_LDO1_MV                  1800
#define PMIC3_PCA9422M_LDO2_MV                  1800
#define PMIC3_PCA9422M_LDO3_MV                  1200
#define PMIC3_PCA9422M_LDO4_MV                  3300

/**
 * @brief PMIC 3 regulator power-good flags.
 * @details REG_STATUS reports whether each switcher and LDO output is above
 * 90 percent of its programmed target voltage.
 */
#define PMIC3_REG_STATUS_SW1_OK                 0x80
#define PMIC3_REG_STATUS_SW2_OK                 0x40
#define PMIC3_REG_STATUS_SW3_OK                 0x20
#define PMIC3_REG_STATUS_SW4_OK                 0x10
#define PMIC3_REG_STATUS_LDO1_OK                0x08
#define PMIC3_REG_STATUS_LDO2_OK                0x04
#define PMIC3_REG_STATUS_LDO3_OK                0x02
#define PMIC3_REG_STATUS_LDO4_OK                0x01

/**
 * @brief PMIC 3 input supply status flags.
 * @details DEVICE0_STS reports the live VIN validity conditions without
 * clearing the corresponding interrupt latches.
 */
#define PMIC3_DEVICE0_VIN_SAFE_0V               0x04
#define PMIC3_DEVICE0_VIN_NOK                   0x02
#define PMIC3_DEVICE0_VIN_OK                    0x01

/**
 * @brief PMIC 3 input path status flags.
 * @details DEVICE1_STS reports current-limit, supplement, overload, AICL, and
 * VIN overvoltage conditions.
 */
#define PMIC3_DEVICE1_VIN_I_LIMIT               0x80
#define PMIC3_DEVICE1_VSYS_SUP_EXIT             0x40
#define PMIC3_DEVICE1_VSYS_SUPPLEMENT           0x20
#define PMIC3_DEVICE1_VSYS_OVERLOAD             0x10
#define PMIC3_DEVICE1_AICL_RELEASE              0x08
#define PMIC3_DEVICE1_AICL_ACTIVE               0x04
#define PMIC3_DEVICE1_VIN_OVP_EXIT              0x02
#define PMIC3_DEVICE1_VIN_OVP                   0x01

/**
 * @brief PMIC 3 VIN input-current limit settings.
 * @details VIN_CNTL2 bits 4:0 select the maximum current drawn from VIN. The
 * 470 mA setting is the PCA9422 default and provides sufficient headroom for
 * the default 200 mA battery-charge current and the active system load.
 */
#define PMIC3_VIN_CURRENT_LIMIT_MASK            0x1F
#define PMIC3_VIN_CURRENT_LIMIT_470MA           0x11
#define PMIC3_VIN_CURRENT_LIMIT_695MA           0x1A
#define PMIC3_VIN_CURRENT_LIMIT_1195MA          0x1F
#define PMIC3_VIN_CURRENT_LIMIT_DEFAULT         PMIC3_VIN_CURRENT_LIMIT_470MA

/**
 * @brief PMIC 3 charger state flags.
 * @details CHARGER0_STS reports the active charging phase and qualification
 * result. More than one state bit can be present during a transition.
 */
#define PMIC3_CHARGER0_TOP_OFF                  0x80
#define PMIC3_CHARGER0_CV_MODE                  0x40
#define PMIC3_CHARGER0_FAST_CHARGE              0x20
#define PMIC3_CHARGER0_PRECHARGE                0x10
#define PMIC3_CHARGER0_OFF                      0x08
#define PMIC3_CHARGER0_ON                       0x04
#define PMIC3_CHARGER0_QUAL_NOK                 0x02
#define PMIC3_CHARGER0_QUAL_OK                  0x01

/**
 * @brief PMIC 3 battery and thermistor status flags.
 * @details CHARGER1_STS reports JEITA temperature zones, battery overvoltage,
 * and battery-presence status.
 */
#define PMIC3_CHARGER1_THERM_HOT                0x80
#define PMIC3_CHARGER1_THERM_WARM_PLUS          0x40
#define PMIC3_CHARGER1_THERM_WARM               0x20
#define PMIC3_CHARGER1_THERM_COOL               0x10
#define PMIC3_CHARGER1_THERM_COLD               0x08
#define PMIC3_CHARGER1_VBAT_OVP_EXIT            0x04
#define PMIC3_CHARGER1_VBAT_OVP                 0x02
#define PMIC3_CHARGER1_NO_BATTERY               0x01

/**
 * @brief PMIC 3 battery-presence interrupt flags.
 * @details INT_CHARGER1 latches battery overvoltage and absence events. The
 * flags are set even when the corresponding INT pin source is masked and are
 * cleared when the register is read.
 */
#define PMIC3_INT_CHARGER1_VBAT_OVP             0x02
#define PMIC3_INT_CHARGER1_NO_BATTERY           0x01

/**
 * @brief PMIC 3 charger completion and fault flags.
 * @details CHARGER2_STS reports recharge, charge completion, thermal
 * regulation, timer expiration, and thermistor fault conditions.
 */
#define PMIC3_CHARGER2_RECHARGE                 0x80
#define PMIC3_CHARGER2_CHARGE_DONE              0x40
#define PMIC3_CHARGER2_THERMAL_REG              0x20
#define PMIC3_CHARGER2_TOPOFF_TIMEOUT           0x10
#define PMIC3_CHARGER2_FAST_TIMEOUT             0x08
#define PMIC3_CHARGER2_PRECHG_TIMEOUT           0x04
#define PMIC3_CHARGER2_THERM_DISABLED           0x02
#define PMIC3_CHARGER2_THERM_OPEN               0x01
#define PMIC3_CHARGER3_VBAT_OCP                 0x01

/**
 * @brief PMIC 3 battery detection settings.
 * @details Defines the reported battery states, insertion confirmation count,
 * and idle requalification interval.
 */
#define PMIC3_BATTERY_UNKNOWN                   0
#define PMIC3_BATTERY_PRESENT                   1
#define PMIC3_BATTERY_ABSENT                    2
#define PMIC3_BATTERY_CONFIRM_COUNT             2
#define PMIC3_BATTERY_RECHECK_COUNT             2

/**
 * @brief PMIC 3 charger register lock settings.
 * @details CHARGER_CNTL0 protects charger control registers 1 through 10.
 * The unlock value must be written before reading or changing a protected
 * setting. Protected registers can return zero while locked.
 */
#define PMIC3_CHARGER_LOCK_MASK                 0x30
#define PMIC3_CHARGER_LOCKED                    0x00
#define PMIC3_CHARGER_UNLOCKED                  0x30

/**
 * @brief PMIC 3 battery-presence detection settings.
 * @details CHARGER_CNTL1 bit 6 disables the internal battery-presence current
 * sink and source test when set. The default configuration keeps this test
 * enabled so insertion and removal can be reported by the charger status.
 */
#define PMIC3_BATTERY_DETECT_MASK               0x40
#define PMIC3_BATTERY_DETECT_ENABLED            0x00
#define PMIC3_BATTERY_DETECT_DISABLED           0x40

/**
 * @brief PMIC 3 automatic charge-stop settings.
 * @details CHARGER_CNTL1 bit 5 controls whether charging enters the DONE state
 * after the configured top-off timer expires.
 */
#define PMIC3_AUTOSTOP_CHARGE_MASK              0x20
#define PMIC3_AUTOSTOP_CHARGE_DISABLED          0x00
#define PMIC3_AUTOSTOP_CHARGE_ENABLED           0x20

/**
 * @brief PMIC 3 charger enable settings.
 * @details CHARGER_CNTL1 controls the charger state. Enabling the charger after
 * it has been disabled starts a new charging qualification cycle.
 */
#define PMIC3_CHARGER_ENABLE_MASK               0x10
#define PMIC3_CHARGER_DISABLED                  0x00
#define PMIC3_CHARGER_ENABLED                   0x10

/**
 * @brief PMIC 3 warm-temperature threshold settings.
 * @details CHARGER_CNTL1 bits 3:2 select the JEITA warm-temperature threshold
 * as a percentage of THERM_BIAS. Temperature labels assume a standard 10 kOhm
 * NTC thermistor.
 */
#define PMIC3_WARM_THRESHOLD_MASK               0x0C
#define PMIC3_WARM_THRESHOLD_35C                0x00
#define PMIC3_WARM_THRESHOLD_40C                0x04
#define PMIC3_WARM_THRESHOLD_45C                0x08
#define PMIC3_WARM_THRESHOLD_50C                0x0C

/**
 * @brief PMIC 3 pre-charge current settings.
 * @details CHARGER_CNTL1 bit 1 selects the pre-charge current as a percentage
 * of the programmed fast-charge current.
 */
#define PMIC3_PRECHARGE_CURRENT_MASK            0x02
#define PMIC3_PRECHARGE_CURRENT_7_PERCENT       0x00
#define PMIC3_PRECHARGE_CURRENT_16_PERCENT      0x02

/**
 * @brief PMIC 3 charge-current settings.
 * @details CHARGER_CNTL1 selects the current step and CHARGER_CNTL3 contains
 * the seven-bit fast-charge current code. The programmed current is one step
 * above the zero-based register code.
 */
#define PMIC3_CHARGE_STEP_MASK                  0x01
#define PMIC3_CHARGE_STEP_2_5MA                 0x00
#define PMIC3_CHARGE_STEP_5MA                   0x01
#define PMIC3_CHARGE_CFG_VERIFY_MASK            ( PMIC3_CHARGER_ENABLE_MASK | PMIC3_CHARGE_STEP_MASK )
#define PMIC3_FAST_CHARGE_CURRENT_MASK          0x7F
#define PMIC3_FAST_CHARGE_CODE_OFFSET           1
#define PMIC3_CHARGE_STEP_2_5MA_VALUE           2.5
#define PMIC3_CHARGE_STEP_5MA_VALUE             5.0
#define PMIC3_CHARGE_CURRENT_MIN_MA             2.5
#define PMIC3_CHARGE_CURRENT_STEP_LIMIT_MA      320.0
#define PMIC3_CHARGE_CURRENT_MAX_MA             640.0
#define PMIC3_DEFAULT_CHARGE_CURRENT_MA         200.0

/**
 * @brief PMIC 3 battery-regulation voltage settings.
 * @details CHARGER_CNTL2 bits 6:0 program the battery regulation voltage from
 * 3.6 V in 10 mV steps. The default 0x3C setting selects 4.2 V.
 */
#define PMIC3_BATTERY_REGULATION_MASK           0x7F
#define PMIC3_BATTERY_REGULATION_4_2V           0x3C

/**
 * @brief PMIC 3 default charger configuration.
 * @details Restores the PCA9422 charger defaults used by PMIC 3 Click before
 * the example programs its charge-current setpoint.
 */
#define PMIC3_CHARGER_CFG1_DEFAULT              ( PMIC3_BATTERY_DETECT_ENABLED | PMIC3_AUTOSTOP_CHARGE_ENABLED | \
                                                  PMIC3_CHARGER_ENABLED | PMIC3_WARM_THRESHOLD_45C | \
                                                  PMIC3_PRECHARGE_CURRENT_16_PERCENT | PMIC3_CHARGE_STEP_2_5MA )
#define PMIC3_CHARGER_CFG2_DEFAULT              PMIC3_BATTERY_REGULATION_4_2V

/**
 * @brief PMIC 3 analog multiplexer settings.
 * @details CHARGER_CNTL10 selects the AMUX source, operating mode, automatic
 * shutoff delay, and divider gain used by the VBAT, VSYS, and THERM channels.
 */
#define PMIC3_AMUX_WAIT_MASK                    0xC0
#define PMIC3_AMUX_WAIT_256US                   0x00
#define PMIC3_AMUX_WAIT_1088US                  0x40
#define PMIC3_AMUX_WAIT_8192US                  0x80
#define PMIC3_AMUX_WAIT_32768US                 0xC0
#define PMIC3_AMUX_MODE_MASK                    0x20
#define PMIC3_AMUX_MODE_MANUAL                  0x00
#define PMIC3_AMUX_MODE_AUTO                    0x20
#define PMIC3_AMUX_VBAT_VSYS_GAIN_MASK          0x10
#define PMIC3_AMUX_VBAT_VSYS_GAIN_1_3           0x00
#define PMIC3_AMUX_VBAT_VSYS_GAIN_1_4           0x10
#define PMIC3_AMUX_THERM_GAIN_MASK              0x08
#define PMIC3_AMUX_THERM_GAIN_1                 0x00
#define PMIC3_AMUX_THERM_GAIN_1_1_5             0x08
#define PMIC3_AMUX_CHANNEL_MASK                 0x07
#define PMIC3_AMUX_CHANNEL_OFF                  0x00
#define PMIC3_AMUX_CHANNEL_VBAT                 0x01
#define PMIC3_AMUX_CHANNEL_THERM                0x02
#define PMIC3_AMUX_CHANNEL_THERM_BIAS           0x03
#define PMIC3_AMUX_CHANNEL_VSYS                 0x04
#define PMIC3_AMUX_CHANNEL_VIN                  0x05

/**
 * @brief PMIC 3 AMUX conversion constants.
 * @details Typical PCA9422 AMUX gains used to reconstruct the selected source
 * voltage from the voltage measured on the mikroBUS AN pin.
 */
#define PMIC3_AMUX_GAIN_VIN                     0.25095
#define PMIC3_AMUX_GAIN_VBAT_1_3                0.33489
#define PMIC3_AMUX_GAIN_VBAT_1_4                0.25148
#define PMIC3_AMUX_GAIN_VSYS_1_3                0.33500
#define PMIC3_AMUX_GAIN_VSYS_1_4                0.25155
#define PMIC3_AMUX_GAIN_THERM_1                 1.0
#define PMIC3_AMUX_GAIN_THERM_1_1_5             0.66667

/**
 * @brief PMIC 3 temperature conversion settings.
 * @details Defines the electrical characteristics of the onboard 10 kOhm
 * Murata NCP18XH103F03RB NTC thermistor and the matching PCA9422 THERM bias
 * network used by #pmic3_read_temperature.
 */
#define PMIC3_NTC_PULLUP_RESISTANCE_OHM         10000.0
#define PMIC3_NTC_R25_RESISTANCE_OHM            10000.0
#define PMIC3_NTC_BETA_25_85_K                  3434.0
#define PMIC3_NTC_REFERENCE_TEMP_K              298.15
#define PMIC3_KELVIN_OFFSET                     273.15
#define PMIC3_RECIPROCAL                        1.0
#define PMIC3_NTC_BIAS_VOLTAGE_MIN              0.0
#define PMIC3_NTC_RATIO_MIN                     0.03
#define PMIC3_NTC_RATIO_MAX                     0.88

/**
 * @brief PMIC 3 ADC settings.
 * @details The AMUX output is limited to 1.8 V. The default 3.3 V reference
 * matches common mikroBUS host boards and can be changed through the config.
 */
#define PMIC3_NUM_CONVERSIONS                   50
#define PMIC3_VREF_3V3                          3.3
#define PMIC3_VREF_5V                           5.0
#define PMIC3_VREF                              PMIC3_VREF_3V3
#define PMIC3_TIMEOUT_MS                        2000

/**
 * @brief PMIC 3 device address setting.
 * @details The PCA9422 default 7-bit address is 0x61. An alternate 0x69
 * address can be selected through the device OTP option.
 */
#define PMIC3_DEVICE_ADDRESS                    0x61
#define PMIC3_DEVICE_ADDRESS_ALT                0x69

/*! @} */ // pmic3_set

/**
 * @defgroup pmic3_map PMIC 3 MikroBUS Map
 * @brief MikroBUS pin mapping of PMIC 3 Click driver.
 */

/**
 * @addtogroup pmic3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PMIC 3 Click to the selected MikroBUS.
 */
#define PMIC3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.amux = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pmic3_map
/*! @} */ // pmic3

/**
 * @brief PMIC 3 Click context object.
 * @details Context object definition of PMIC 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t on;                   /**< Active-low PCA9422 ON input. */

    // Input pins
    digital_in_t int_pin;               /**< Active-low PCA9422 interrupt output. */

    // Modules
    i2c_master_t i2c;                   /**< I2C driver object. */
    analog_in_t adc;                    /**< ADC module object. */

    uint8_t slave_address;              /**< Device slave address (used for I2C driver). */
    float   vref;                       /**< ADC reference voltage. */
    uint8_t battery_state;              /**< Debounced battery-presence state. */
    uint8_t battery_confirm_cnt;        /**< Battery detection debounce count. */

} pmic3_t;

/**
 * @brief PMIC 3 Click configuration object.
 * @details Configuration object definition of PMIC 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;                     /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                     /**< Bidirectional data pin descriptor for I2C driver. */

    // Additional gpio pins
    pin_name_t amux;                    /**< AMUX analog output pin descriptor. */
    pin_name_t on;                      /**< Active-low PCA9422 ON pin descriptor. */
    pin_name_t int_pin;                 /**< Active-low interrupt pin descriptor. */

    // Static variables
    uint32_t               i2c_speed;   /**< I2C serial speed. */
    uint8_t                i2c_address; /**< I2C slave address. */
    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} pmic3_cfg_t;

/**
 * @brief PMIC 3 status object.
 * @details Contains non-destructive PCA9422 system, regulator, input, and
 * charger status register values returned by #pmic3_read_status.
 */
typedef struct
{
    uint8_t top_int;                    /**< Top-level pending interrupt summary. */
    uint8_t power_state;                /**< Current PCA9422 power state and mode. */
    uint8_t regulator_status;           /**< Switcher and LDO power-good flags. */
    uint8_t device_0_status;            /**< VIN validity flags. */
    uint8_t device_1_status;            /**< VIN path and VSYS condition flags. */
    uint8_t charger_0_status;           /**< Charger phase and qualification flags. */
    uint8_t charger_1_status;           /**< Battery and thermistor flags. */
    uint8_t charger_2_status;           /**< Charger completion and fault flags. */
    uint8_t charger_3_status;           /**< Battery overcurrent flag. */

} pmic3_status_t;

/**
 * @brief PMIC 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PMIC3_OK = 0,
    PMIC3_ERROR = -1

} pmic3_return_value_t;

/*!
 * @addtogroup pmic3 PMIC 3 Click Driver
 * @brief API for configuring and manipulating PMIC 3 Click driver.
 * @{
 */

/**
 * @brief PMIC 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pmic3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pmic3_cfg_setup ( pmic3_cfg_t *cfg );

/**
 * @brief PMIC 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pmic3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic3_init ( pmic3_t *ctx, pmic3_cfg_t *cfg );

/**
 * @brief PMIC 3 default configuration function.
 * @details This function verifies the PCA9422 identity, starts the PMIC when it
 * is in the OFF state, programs the PCA9422M active regulator voltages,
 * configures the VIN current limit, restores the 4.2 V battery regulation
 * configuration, programs the default charge current, enables
 * battery-presence detection and charging, and leaves the analog multiplexer
 * disabled.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Active rail voltages are restored to the PCA9422M defaults. The VIN
 * input-current limit is selected by #PMIC3_VIN_CURRENT_LIMIT_DEFAULT and the
 * battery charge current is defined by #PMIC3_DEFAULT_CHARGE_CURRENT_MA.
 */
err_t pmic3_default_cfg ( pmic3_t *ctx );

/**
 * @brief PMIC 3 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic3_write_reg ( pmic3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief PMIC 3 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic3_write_regs ( pmic3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief PMIC 3 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic3_read_reg ( pmic3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief PMIC 3 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic3_read_regs ( pmic3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief PMIC 3 read raw ADC value function.
 * @details This function reads raw ADC value.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[out] raw_adc : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic3_read_raw_adc ( pmic3_t *ctx, uint16_t *raw_adc );

/**
 * @brief PMIC 3 read voltage level function.
 * @details This function reads raw ADC value and converts it to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[out] voltage : Output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t pmic3_read_voltage ( pmic3_t *ctx, float *voltage );

/**
 * @brief PMIC 3 read average voltage level function.
 * @details This function reads a desired number of ADC samples and calculates the average voltage level.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] num_conv : Number of ADC samples.
 * @param[out] voltage_avg : Average output voltage level [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered reference voltage.
 */
err_t pmic3_read_voltage_avg ( pmic3_t *ctx, uint16_t num_conv, float *voltage_avg );

/**
 * @brief PMIC 3 set vref function.
 * @details This function sets the voltage reference for PMIC 3 Click driver.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] vref : Reference voltage (volts).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The default voltage reference set with @b pmic3_init is defined in PMIC3_VREF.
 */
err_t pmic3_set_vref ( pmic3_t *ctx, float vref );

/**
 * @brief PMIC 3 set ON pin function.
 * @details This function sets the logic state of the active-low ON input.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note Keep the pin low for at least the configured ON short-press deglitch
 * time before returning it high.
 */
void pmic3_set_on_pin ( pmic3_t *ctx, uint8_t state );

/**
 * @brief PMIC 3 get INT pin function.
 * @details This function reads the logic state of the active-low INT pin.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note A low state indicates at least one unmasked interrupt event.
 */
uint8_t pmic3_get_int_pin ( pmic3_t *ctx );

/**
 * @brief PMIC 3 check communication function.
 * @details This function reads DEV_INFO and validates the PCA9422 device ID and
 * supported silicon revision fields.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pmic3_check_communication ( pmic3_t *ctx );

/**
 * @brief PMIC 3 set buck voltage function.
 * @details This function programs the active DVS0 output of BUCK1, BUCK2, or
 * BUCK3, or the active output of the SW4 buck-boost regulator. The requested
 * millivolt value is rounded to the nearest supported setting and verified by
 * register readback.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] buck_id : Buck regulator identifier.
 * @param[in] voltage_mv : Requested output voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use #PMIC3_BUCK_1 through #PMIC3_BUCK_4 for @p buck_id. BUCK4 is the
 * SW4 buck-boost regulator.
 */
err_t pmic3_set_buck_voltage ( pmic3_t *ctx, uint8_t buck_id, uint16_t voltage_mv );

/**
 * @brief PMIC 3 set LDO voltage function.
 * @details This function programs the active output of the selected LDO while
 * preserving its active-discharge and reserved control bits. The requested
 * millivolt value is rounded to the nearest supported setting and verified by
 * register readback.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] ldo_id : LDO regulator identifier.
 * @param[in] voltage_mv : Requested output voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use #PMIC3_LDO_1 through #PMIC3_LDO_4 for @p ldo_id.
 */
err_t pmic3_set_ldo_voltage ( pmic3_t *ctx, uint8_t ldo_id, uint16_t voltage_mv );

/**
 * @brief PMIC 3 set charger register lock function.
 * @details This function writes the CHARGER_LOCK field in CHARGER_CNTL0.
 * Reserved register bits are always written as zero.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] lock_state : Charger register lock setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use #PMIC3_CHARGER_LOCKED or #PMIC3_CHARGER_UNLOCKED.
 */
err_t pmic3_set_charger_lock ( pmic3_t *ctx, uint8_t lock_state );

/**
 * @brief PMIC 3 set battery-presence detection function.
 * @details This function updates the BAT_PRESENCE_DET_DISABLE field in
 * CHARGER_CNTL1 while preserving the remaining charger settings. Protected
 * register access is restored after the programmed value is verified.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] detect_state : Battery-presence detection setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use #PMIC3_BATTERY_DETECT_ENABLED or
 * #PMIC3_BATTERY_DETECT_DISABLED.
 */
err_t pmic3_set_battery_detection ( pmic3_t *ctx, uint8_t detect_state );

/**
 * @brief PMIC 3 set charger function.
 * @details This function updates the CHARGER_EN field in CHARGER_CNTL1 while
 * preserving all other charger settings and restoring register protection.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] charger_state : Charger enable setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use #PMIC3_CHARGER_DISABLED or #PMIC3_CHARGER_ENABLED.
 */
err_t pmic3_set_charger ( pmic3_t *ctx, uint8_t charger_state );

/**
 * @brief PMIC 3 set charge-current function.
 * @details This function unlocks and reads the charger configuration, selects
 * the appropriate current step, then writes the unlock key together with
 * CHARGER_CNTL1 through CHARGER_CNTL3 in one auto-increment transaction. It
 * preserves unrelated settings, verifies the programmed values, and restores
 * charger-register write protection.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] charge_current : Requested charge-current setpoint in mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The supported range is 2.5 mA to 640 mA. Values that do not fall on a
 * supported current step are rounded down.
 */
err_t pmic3_set_charge_current ( pmic3_t *ctx, float charge_current );

/**
 * @brief PMIC 3 read charge-current setting function.
 * @details This function unlocks the charger-control block, reads
 * CHARGER_CNTL1 and CHARGER_CNTL3, converts the programmed fast-charge current
 * code to milliamperes, and restores charger-register write protection.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[out] charge_current : Programmed charge-current setpoint in mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The returned value is a configured setpoint, not a measurement of the
 * current flowing into the battery.
 */
err_t pmic3_read_charge_current ( pmic3_t *ctx, float *charge_current );

/**
 * @brief PMIC 3 set AMUX channel function.
 * @details This function unlocks the protected charger registers, places the
 * AMUX in manual mode, selects the requested source, verifies the selection,
 * and restores charger-register write protection.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] channel : AMUX channel setting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use the PMIC3_AMUX_CHANNEL_x macros for channel selection.
 */
err_t pmic3_set_amux_channel ( pmic3_t *ctx, uint8_t channel );

/**
 * @brief PMIC 3 read AMUX source voltage function.
 * @details This function selects an AMUX source, waits for the output to
 * settle, averages the ADC samples, reconstructs the source voltage with the
 * configured AMUX gain, and disables the AMUX after the measurement.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] channel : AMUX source channel setting.
 * @param[out] source_voltage : Pointer to the reconstructed source voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion uses typical AMUX gains from the PCA9422 datasheet.
 */
err_t pmic3_read_amux ( pmic3_t *ctx, uint8_t channel, float *source_voltage );

/**
 * @brief PMIC 3 read temperature function.
 * @details This function measures the THERM and THERM_BIAS channels, validates
 * the divider ratio against the PCA9422 short/open limits, calculates the NTC
 * resistance ratiometrically, and converts the result to degrees Celsius using
 * the beta equation.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to the measured temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion constants match the onboard Murata
 * NCP18XH103F03RB 10 kOhm NTC thermistor.
 */
err_t pmic3_read_temperature ( pmic3_t *ctx, float *temperature );

/**
 * @brief PMIC 3 read status function.
 * @details This function reads the non-destructive system, regulator, input,
 * and charger status registers into one status object.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[out] status : Click status object.
 * See #pmic3_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Interrupt source registers are not read or cleared by this function.
 */
err_t pmic3_read_status ( pmic3_t *ctx, pmic3_status_t *status );

/**
 * @brief PMIC 3 detect battery function.
 * @details This function uses the latched no-battery interrupt and live
 * no-battery status to debounce battery insertion and removal. It restarts
 * charger qualification periodically while the battery remains absent.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] status : Click status object.
 * See #pmic3_status_t object definition for detailed explanation.
 * @param[out] battery_state : Detected battery-presence state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Reading INT_CHARGER1 clears its latched interrupt flags. A cleared live
 * NO_BATTERY status is confirmed across consecutive calls before a battery is
 * reported as present.
 */
err_t pmic3_detect_battery ( pmic3_t *ctx, pmic3_status_t *status, uint8_t *battery_state );

#ifdef __cplusplus
}
#endif
#endif // PMIC3_H

/*! @} */ // pmic3

// ------------------------------------------------------------------------ END
