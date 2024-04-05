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
 * @file charger6.h
 * @brief This file contains API for Charger 6 Click Driver.
 */

#ifndef CHARGER6_H
#define CHARGER6_H

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
 * @addtogroup charger6 Charger 6 Click Driver
 * @brief API for configuring and manipulating Charger 6 Click driver.
 * @{
 */

/**
 * @defgroup charger6_reg Charger 6 Registers List
 * @brief List of registers of Charger 6 Click driver.
 */

/**
 * @addtogroup charger6_reg
 * @{
 */

/**
 * @brief Charger 6 description register.
 * @details Specified register for description of Charger 6 Click driver.
 */
#define CHARGER6_REGISTER_00                            0x00
#define CHARGER6_REGISTER_01                            0x01
#define CHARGER6_REGISTER_02                            0x02
#define CHARGER6_REGISTER_03                            0x03
#define CHARGER6_REGISTER_04                            0x04
#define CHARGER6_REGISTER_05                            0x05
#define CHARGER6_REGISTER_06                            0x06
#define CHARGER6_REGISTER_07                            0x07
#define CHARGER6_REGISTER_08                            0x08
#define CHARGER6_REGISTER_09                            0x09
#define CHARGER6_REGISTER_0A                            0x0A
#define CHARGER6_REGISTER_0B                            0x0B

/*! @} */ // charger6_reg

/**
 * @defgroup pwr_sel Charger 6 power source selection
 * @brief Power source selection of Charger 6 Click driver.
 */

/**
 * @addtogroup pwr_sel
 * @{
 */

/**
 * @brief Charger 6 description register.
 * @details Specified power source selection input 
 * for description of Charger 6 Click driver.
 */
#define CHARGER6_PSEL_SW_MANUAL                         0x00
#define CHARGER6_PSEL_500_mA                            0x01

/*! @} */ // pwr_sel

/**
 * @defgroup sys_min_voltage Charger 6 system minimum voltage.
 * @brief System minimum voltage of Charger 6 Click driver.
 */

/**
 * @addtogroup sys_min_voltage
 * @{
 */

/**
 * @brief Charger 6 description system minimum voltage.
 * @details System minimum voltage 
 * for description of Charger 6 Click driver.
 */
#define CHARGER6_SYS_MIN_VTG_2600mV                     2600
#define CHARGER6_SYS_MIN_VTG_2800mV                     2800
#define CHARGER6_SYS_MIN_VTG_3000mV                     3000
#define CHARGER6_SYS_MIN_VTG_3200mV                     3200
#define CHARGER6_SYS_MIN_VTG_3400mV                     3400
#define CHARGER6_SYS_MIN_VTG_3500mV                     3500
#define CHARGER6_SYS_MIN_VTG_3600mV                     3600
#define CHARGER6_SYS_MIN_VTG_3700mV                     3700

/*! @} */ // sys_min_voltage

/**
 * @defgroup top_off_time Charger 6 top off timer.
 * @brief Top off timer of Charger 6 Click driver.
 */

/**
 * @addtogroup top_off_time
 * @{
 */

/**
 * @brief Charger 6 description top off timer.
 * @details Top off timer voltage 
 * for description of Charger 6 Click driver.
 */
#define CHARGER6_TOPOFF_TIMER_DISABLE                   0
#define CHARGER6_TOPOFF_TIMER_15_MINUTES               15
#define CHARGER6_TOPOFF_TIMER_30_MINUTES               30
#define CHARGER6_TOPOFF_TIMER_45_MINUTES               45

/*! @} */ // top_off_time

/**
 * @defgroup charger6_set Charger 6 Registers Settings
 * @brief Settings for registers of Charger 6 Click driver.
 */

/**
 * @addtogroup charger6_set
 * @{
 */

/**
 * @brief Charger 6 description setting.
 * @details Specified setting for description of Charger 6 Click driver.
 */

/**
 * @brief Charger 6 REG00 Field Descriptions.
 * @details Specified REG00 Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R00_EN_HIZ_DISABLE                     0x00
#define CHARGER6_R00_EN_HIZ_ENABLE                      0x80
#define CHARGER6_R00_EN_ICHG_MON_ENABLE                 0x00
#define CHARGER6_R00_EN_ICHG_MON_DISABLE_STAT           0x60
#define CHARGER6_R00_IINDPM_1600mA                      0x10
#define CHARGER6_R00_IINDPM_800mA                       0x08
#define CHARGER6_R00_IINDPM_400mA                       0x04
#define CHARGER6_R00_IINDPM_200mA                       0x02
#define CHARGER6_R00_IINDPM_100mA                       0x01

/**
 * @brief Charger 6 REG01 Field Descriptions.
 * @details Specified REG01 Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R01_PFM_ENABLE                         0x00
#define CHARGER6_R01_PFM_DISABLE                        0x80
#define CHARGER6_R01_WD_RST_NORMAL                      0x00
#define CHARGER6_R01_WD_RST_RESET                       0x40
#define CHARGER6_R01_OTG_DISABLE                        0x00
#define CHARGER6_R01_OTG_ENABLE                         0x20
#define CHARGER6_R01_CHARGE_DISABLE                     0x00
#define CHARGER6_R01_CHARGE_ENABLE                      0x10
#define CHARGER6_R01_SYS_MIN_2600mV                     0x00
#define CHARGER6_R01_SYS_MIN_2800mV                     0x02
#define CHARGER6_R01_SYS_MIN_3000mV                     0x04
#define CHARGER6_R01_SYS_MIN_3200mV                     0x06
#define CHARGER6_R01_SYS_MIN_3400mV                     0x08
#define CHARGER6_R01_SYS_MIN_3500mV                     0x0A
#define CHARGER6_R01_SYS_MIN_3600mV                     0x0C
#define CHARGER6_R01_SYS_MIN_3700mV                     0x0E
#define CHARGER6_R01_MIN_VBAT_SEL_2800mV                0x00
#define CHARGER6_R01_MIN_VBAT_SEL_2500mV                0x01

/**
 * @brief Charger 6 REG02 Field Descriptions.
 * @details Specified REG02 Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R02_BOOST_LIM_500mA                    0x00
#define CHARGER6_R02_BOOST_LIM_1200mA                   0x80
#define CHARGER6_R02_Q1_FULLON_BETTER_ACCURACY          0x00
#define CHARGER6_R02_Q1_FULLON_BETTER_EFFICIENCY        0x40
#define CHARGER6_R02_ICHG_1920mA                        0x20
#define CHARGER6_R02_ICHG_960mA                         0x10
#define CHARGER6_R02_ICHG_480mA                         0x08
#define CHARGER6_R02_ICHG_240mA                         0x04
#define CHARGER6_R02_ICHG_120mA                         0x02
#define CHARGER6_R02_ICHG_60mA                          0x01

/**
 * @brief Charger 6 REG03 Field Descriptions.
 * @details Specified REG03 Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R03_IPRECHG_480mA                      0x80
#define CHARGER6_R03_IPRECHG_240mA                      0x40
#define CHARGER6_R03_IPRECHG_120mA                      0x20
#define CHARGER6_R03_IPRECHG_60mA                       0x10
#define CHARGER6_R03_ITERM_480mA                        0x08
#define CHARGER6_R03_ITERM_240mA                        0x04
#define CHARGER6_R03_ITERM_120mA                        0x02
#define CHARGER6_R03_ITERM_60mA                         0x01

/**
 * @brief Charger 6 REG04 Field Descriptions.
 * @details Specified REG04 Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R04_VREG_512mV                         0x80
#define CHARGER6_R04_VREG_256mV                         0x40
#define CHARGER6_R04_VREG_128mV                         0x20
#define CHARGER6_R04_VREG_64mV                          0x10
#define CHARGER6_R04_VREG_32mV                          0x08
#define CHARGER6_R04_TOPOFF_TIMER_DISABLED              0x00
#define CHARGER6_R04_TOPOFF_TIMER_15_MIN                0x02
#define CHARGER6_R04_TOPOFF_TIMER_30_MIN                0x04
#define CHARGER6_R04_TOPOFF_TIMER_45_MIN                0x06
#define CHARGER6_R04_VRECHG_100mV                       0x00
#define CHARGER6_R04_VRECHG_200mV                       0x01

/**
 * @brief Charger 6 REG05 Field Descriptions.
 * @details Specified REG05 Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R05_TERMINATION_DISABLE                0x00
#define CHARGER6_R05_TERMINATION_ENABLE                 0x80
#define CHARGER6_R05_WATCHDOG_DISABLE                   0x00
#define CHARGER6_R05_WATCHDOG_TIMER_40_SEC              0x10
#define CHARGER6_R05_WATCHDOG_TIMER_80_SEC              0x20
#define CHARGER6_R05_WATCHDOG_TIMER_160_SEC             0x30
#define CHARGER6_R05_TIMER_DISABLE                      0x00
#define CHARGER6_R05_TIMER_ENABLE                       0x08
#define CHARGER6_R05_CHG_TIMER_5_HOURS                  0x00
#define CHARGER6_R05_CHG_TIMER_10_HOURS                 0x04
#define CHARGER6_R05_TREG_90_C                          0x00
#define CHARGER6_R05_TREG_110_C                         0x02
#define CHARGER6_R05_JEITA_ISET_50                      0x00
#define CHARGER6_R05_JEITA_ISET_20                      0x01

/**
 * @brief Charger 6 REG06 Field Descriptions.
 * @details Specified REG06 Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R06_OVP_TSH_5500mV                     0x00
#define CHARGER6_R06_OVP_TSH_6500mV                     0x40
#define CHARGER6_R06_OVP_TSH_10500mV                    0x80
#define CHARGER6_R06_OVP_TSH_14000mV                    0xC0
#define CHARGER6_R06_BOOSTV_4850mV                      0x00
#define CHARGER6_R06_BOOSTV_5000mV                      0x10
#define CHARGER6_R06_BOOSTV_5150mV                      0x20
#define CHARGER6_R06_BOOSTV_5300mV                      0x30
#define CHARGER6_R06_VINDPM_800mV                       0x08
#define CHARGER6_R06_VINDPM_400mV                       0x04
#define CHARGER6_R06_VINDPM_200mV                       0x02
#define CHARGER6_R06_VINDPM_100mV                       0x01

/**
 * @brief Charger 6 REG07 Field Descriptions.
 * @details Specified REG07 Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R07_NOT_IN_INPUT_CURRENT_LIMIT         0x00
#define CHARGER6_R07_FORCE_INPUT_CURRENT_LIMIT          0x80
#define CHARGER6_R07_TMR2X_DISABLE                      0x00
#define CHARGER6_R07_TMR2X_ENABLE                       0x40
#define CHARGER6_R07_BATFET_ALLOW_Q4_TURN_ON            0x00
#define CHARGER6_R07_BATFET_TURN_OFF_Q4                 0x20
#define CHARGER6_R07_JEITA_VSET_TO_4100mV               0x00
#define CHARGER6_R07_JEITA_VSET_TO_VREG                 0x10
#define CHARGER6_R07_BATFET_IMMEDIATELY                 0x00
#define CHARGER6_R07_BATFET_AFTER_10_SEC                0x08
#define CHARGER6_R07_BATFET_RST_DISABLE                 0x00
#define CHARGER6_R07_BATFET_RST_ENABLE                  0x04
#define CHARGER6_R07_VDPM_BAT_TRACK_DISABLE             0x00
#define CHARGER6_R07_VDPM_BAT_TRACK_VBAT_PLUS_200mV     0x01
#define CHARGER6_R07_VDPM_BAT_TRACK_VBAT_PLUS_250mV     0x02
#define CHARGER6_R07_VDPM_BAT_TRACK_VBAT_PLUS_300mV     0x03

/**
 * @brief Charger 6 REG08 Field Descriptions.
 * @details Specified REG08 Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R08_VBUS_BIT_MASK                      0xE0
#define CHARGER6_R08_VBUS_STAT_NO_INPUT                 0x00
#define CHARGER6_R08_VBUS_STAT_USB_HOST_SDP             0x20
#define CHARGER6_R08_VBUS_STAT_ADAPTER_2_4_A            0x40
#define CHARGER6_R08_VBUS_OTG                           0xE0
#define CHARGER6_R08_CHRG_STAT_BIT_MASK                 0x18
#define CHARGER6_R08_CHRG_STAT_NOT_CHARGING             0x00
#define CHARGER6_R08_CHRG_STAT_PRE_CHARGE               0x08
#define CHARGER6_R08_CHRG_STAT_FAST_CHARGING            0x10
#define CHARGER6_R08_CHRG_STAT_CHARGE_TERMINATION       0x18
#define CHARGER6_R08_PG_STAT_BIT_MASK                   0x04
#define CHARGER6_R08_PG_STAT_POWER_NOT_GOOD             0x00
#define CHARGER6_R08_PG_STAT_POWER_GOOD                 0x04
#define CHARGER6_R08_THERM_STAT_BIT_MASK                0x02
#define CHARGER6_R08_THERM_STAT_NOT_mAl                 0x00
#define CHARGER6_R08_THERM_STAT_mAl                     0x02
#define CHARGER6_R08_VSYS_BIT_MASK                      0x01
#define CHARGER6_R08_VSYS_STAT_NOT                      0x00
#define CHARGER6_R08_VSYS_STAT_VSYSM                    0x01

/**
 * @brief Charger 6 REG09 Field Descriptions.
 * @details Specified REG09 Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R09_WATCHDOG_FAULT_BIT_MASK            0x80
#define CHARGER6_R09_WATCHDOG_FAULT_NORMAL              0x00
#define CHARGER6_R09_WATCHDOG_FAULT_TIMER_EXPIRATION    0x80
#define CHARGER6_R09_BOOST_FAULT_BIT_MASK               0x40
#define CHARGER6_R09_BOOST_FAULT_NORMAL                 0x00
#define CHARGER6_R09_BOOST_FAULT_VBUS_OVERLOADED        0x40
#define CHARGER6_R09_CHRG_FAULT_BIT_MASK                0x30
#define CHARGER6_R09_CHRG_FAULT_NORMAL                  0x00
#define CHARGER6_R09_CHRG_FAULT_INPUT_FAULT             0x10
#define CHARGER6_R09_CHRG_FAULT_THERMAL_SHUTDOWN        0x20
#define CHARGER6_R09_CHRG_FAULT_CHG_SAFETY_TIMER_EXP    0x30
#define CHARGER6_R09_BAT_FAULT_BIT_MASK                 0x08
#define CHARGER6_R09_BAT_FAULT_NORMAL                   0x00
#define CHARGER6_R09_BAT_FAULT_BATOVP                   0x08
#define CHARGER6_R09_NTC_FAULT_BIT_MASK                 0x07
#define CHARGER6_R09_NTC_FAULT_NORMAL                   0x00
#define CHARGER6_R09_NTC_FAULT_WARM                     0x02
#define CHARGER6_R09_NTC_FAULT_COOL                     0x03
#define CHARGER6_R09_NTC_FAULT_COLD                     0x05
#define CHARGER6_R09_NTC_FAULT_HOT                      0x06

/**
 * @brief Charger 6 REG0A Field Descriptions.
 * @details Specified REG0A Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R0A_VBUS_GD_BIT_MASK                   0x80
#define CHARGER6_R0A_VBUS_GD_NOT_VBUS                   0x00
#define CHARGER6_R0A_VBUS_GD_VBUS_ATTACHED              0x80
#define CHARGER6_R0A_VBUS_GD_VINDPM_BIT_MASK            0x40
#define CHARGER6_R0A_VBUS_GD_NOT_IN_VINDPM              0x00
#define CHARGER6_R0A_VBUS_GD_IN_VINDPM                  0x40
#define CHARGER6_R0A_VBUS_GD_IINDPM_BIT_MASK            0x20
#define CHARGER6_R0A_VBUS_GD_NOT_IN_IINDPM              0x00
#define CHARGER6_R0A_VBUS_GD_IN_IINDPM                  0x20
#define CHARGER6_R0A_TOP_OFF_BIT_MASK                   0x08
#define CHARGER6_R0A_TOP_OFF_TIMER_NOT_COUNTING         0x00
#define CHARGER6_R0A_TOP_OFF_TIMER_COUNTING             0x08
#define CHARGER6_R0A_ACOV_STAT_BIT_MASK                 0x04
#define CHARGER6_R0A_ACOV_STAT_NOT_IN_ACOV              0x00
#define CHARGER6_R0A_ACOV_STAT_IN_ACOV                  0x04
#define CHARGER6_R0A_VINDPM_INT_MASK_ALLOW              0x00
#define CHARGER6_R0A_VINDPM_INT_MASK_MASK               0x02
#define CHARGER6_R0A_IINDPM_INT_MASK_ALLOW              0x00
#define CHARGER6_R0A_IINDPM_INT_MASK_MASK               0x01

/**
 * @brief Charger 6 REG0B Field Descriptions.
 * @details Specified REG0B Field Descriptions of
 * Charger 6 Click driver.
 */
#define CHARGER6_R0B_DEV_ID_BIT_MASK                    0x78
#define CHARGER6_R0B_DEV_REV_BIT_MASK                   0x03


/**
 * @brief Charger 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Charger 6 Click driver.
 */
#define CHARGER6_SET_DEV_ADDR                           0x6B

/*! @} */ // charger6_set

/**
 * @defgroup charger6_map Charger 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 6 Click driver.
 */

/**
 * @addtogroup charger6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 6 Click to the selected MikroBUS.
 */
#define CHARGER6_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );    \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );    \
    cfg.ce = MIKROBUS( mikrobus, MIKROBUS_CS );      \
    cfg.qon = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.psel = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger6_map
/*! @} */ // charger6

/**
 * @brief Charger 6 Click context object.
 * @details Context object definition of Charger 6 Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  ce;      /**< Charge enable pin. */
    digital_out_t  qon;     /**< BATFET enable/reset control. */
    digital_out_t  psel;    /**< Power source selection. */

    // Input pins

    digital_in_t  int_pin;  /**< Charger device status. */

    // Modules

    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} charger6_t;

/**
 * @brief Charger 6 Click configuration object.
 * @details Configuration object definition of Charger 6 Click driver.
 */
typedef struct
{
    pin_name_t  scl;       /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;       /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  ce;        /**< Charge enable pin. */
    pin_name_t  qon;       /**< BATFET enable/reset control. */
    pin_name_t  psel;      /**< Power source selection. */
    pin_name_t  int_pin;   /**< Charger device status. */

    uint32_t  i2c_speed;   /**< I2C serial speed. */
    uint8_t   i2c_address; /**< I2C slave address. */

} charger6_cfg_t;

/**
 * @brief Charger 6 Click data status structure definition.
 * @details Data status object definition of Charger 6 Click driver.
 */
typedef struct
{
    uint8_t vbus_stat;
    uint8_t chrg_stat;
    uint8_t pg_stat;
    uint8_t therm_stat;
    uint8_t vsys_stat;
    uint8_t watchdog_fault;
    uint8_t boost_fault;
    uint8_t chrg_fault;
    uint8_t bat_fault;
    uint8_t ntc_fault;
    uint8_t vbus_gd;
    uint8_t vindpm_stat;
    uint8_t iindpm_stat;
    uint8_t topoff_active;
    uint8_t acov_stat;
    uint8_t vindpm_int;
    uint8_t iindpm_int;
    uint8_t dev_id;
    uint8_t dev_rev;
}
charger6_status_t;

/**
 * @brief Charger 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER6_OK = 0,
    CHARGER6_ERROR = -1

} charger6_return_value_t;

/*!
 * @addtogroup charger6 Charger 6 Click Driver
 * @brief API for configuring and manipulating Charger 6 Click driver.
 * @{
 */

/**
 * @brief Charger 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void charger6_cfg_setup ( charger6_cfg_t *cfg );

/**
 * @brief Charger 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t charger6_init ( charger6_t *ctx, charger6_cfg_t *cfg );

/**
 * @brief Charger 6 default configuration function.
 * @details This function executes a default configuration of Charger 6
 * click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t charger6_default_cfg ( charger6_t *ctx );

/**
 * @brief Charger 6 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
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
err_t charger6_generic_write ( charger6_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Charger 6 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
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
err_t charger6_generic_read ( charger6_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Charger 6 charge enable function.
 * @details This function enable battery charging of the BQ25601,
 * I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void charger6_enable_battery_charging ( charger6_t *ctx );

/**
 * @brief Charger 6 charge disable function.
 * @details This function disable battery charging of the BQ25601,
 * I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void charger6_disable_battery_charging ( charger6_t *ctx );

/**
 * @brief Charger 6 power source selection function.
 * @details This function performs input current limit power source mode selection
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @param[in] pwr_sel : 
 *         @li @c 0x00 ( CHARGER6_PSEL_SW_MANUAL ) - Set 2400 mA input current limit,
 *         @li @c 0x01 ( CHARGER6_PSEL_500_mA )    - Set 500 mA input current limit. 
 *                      
 * @return Nothing.
 *
 * @note Once the device gets into host ( Manual ) mode, 
 * the host can program different input current limits.
 *
 * @endcode
 */
void charger6_power_source_selection ( charger6_t *ctx, uint8_t pwr_sel );

/**
 * @brief Charger 6 set input current limit function.
 * @details This function set the input current limit ( Range : 100 mA – 3200 mA ) 
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @param[in] current_limit : Input Current Limit 100 mA – 3200 mA.
 *                      
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note If changed automatically after input source
 * detection is completed ( device gets into host ( Manual ) mode )
 * Host can over-write IINDPM register bits after input source
 * detection is completed.
 *
 * @endcode
 */
err_t charger6_set_input_current_limit ( charger6_t *ctx, uint16_t current_limit );

/**
 * @brief Charger 6 set system minimum voltage function.
 * @details This function set the system minimum voltag
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @param[in] sys_min_voltage : System Minimum Voltage 2600 mV – 3700 mV.
 *                      
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t charger6_set_system_minimum_voltage ( charger6_t *ctx, uint16_t sys_min_voltage );

/**
 * @brief Charger 6 get status function.
 * @details This function get status data
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @param[out] chg_status : Pointer to the memory location of the structure where data be stored.
 *                      
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t charger6_get_status ( charger6_t *ctx, charger6_status_t *chg_status );

/**
 * @brief Charger 6 set fast charge current function.
 * @details This function set fast charge current limit ( Range: 0 mA – 3000 mA ) 
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @param[in] fast_chg_current : Fast Charge Current 0 mA – 3000 mA.
 *                      
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Charge current regulation range from 0 mA to 3000 mA.
 * The device is compliant with USB 2.0 and USB 3.0 power spec with input current and
 * voltage regulation. The device also meets USB On-the-Go (OTG) operation power rating specification by
 * supplying 5150 mV on VBUS with constant current limit up to 1200 mA.
 *
 * @endcode
 */
err_t charger6_set_fast_charge_current ( charger6_t *ctx, uint16_t fast_chg_current );

/**
 * @brief Charger 6 get fast charge current function.
 * @details This function get fast charge current limit data 
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 *                      
 * @return Fast charge current limit ( mA ).
 *
 * @note None.
 *
 * @endcode
 */
uint16_t charger6_get_fast_charge_current ( charger6_t *ctx );

/**
 * @brief Charger 6 set precharge current function.
 * @details This function set precharge current limit ( Range: 60 mA – 780 mA ) 
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @param[in] precharge_current : Precharge Charge Current 60 mA – 780 mA.
 *                      
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t charger6_set_precharge_current ( charger6_t *ctx, uint16_t precharge_current );

/**
 * @brief Charger 6 set termination current function.
 * @details This function set termination current limit ( Range: 60 mA – 780 mA ) 
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @param[in] termination_current : Termination Charge Current 60 mA – 780 mA.
 *                      
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t charger6_set_termination_current ( charger6_t *ctx, uint16_t termination_current );

/**
 * @brief Charger 6 set charge voltage function.
 * @details This function set charge voltage ( Range: 3856 mV – 4624 mV ) 
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @param[in] charge_voltage : Charge Voltage 3856 mV – 4624 mV.
 *                      
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t charger6_set_charge_voltage ( charger6_t *ctx, uint16_t charge_voltage );

/**
 * @brief Charger 6 set top OFF timer function.
 * @details This function set top OFF timer value 
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 * @param[in] top_off_time : 
 *         @li @c  0 ( CHARGER6_TOPOFF_TIMER_DISABLE )    - Disabled (Default),
 *         @li @c 30 ( CHARGER6_TOPOFF_TIMER_30_MINUTES ) - 30 minutes,
 *         @li @c 15 ( CHARGER6_TOPOFF_TIMER_15_MINUTES ) - 15 minutes,
 *         @li @c 45 ( CHARGER6_TOPOFF_TIMER_45_MINUTES ) - 45 minutes.
 *                      
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t charger6_set_top_off_timer ( charger6_t *ctx, uint8_t top_off_time );

/**
 * @brief Charger 6 check interrupt function.
 * @details This function check the interrupt state, the state of the INT pin 
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #touchpad2_t object definition for detailed explanation.
 * @return @li @c 0 - INT pin state low,
 *         @li @c 1 - INT pin state high.
 *
 * @note None.
 *
 * @endcode
 */
uint8_t charger6_check_interrupt ( charger6_t *ctx );

/**
 * @brief Charger 6 hw reset function.
 * @details This function performs hardware  reset 
 * of the BQ25601, I2C Controlled 3-A Single-Cell Battery Charger 
 * for High Input Voltage and Narrow Voltage DC (NVDC) Power Path Management
 * on the Charger 6 Click board.
 * @param[in] ctx : Click context object.
 * See #charger6_t object definition for detailed explanation.
 *                      
 * @return Nothing.
 *
 * @note None.
 *
 * @endcode
 */
void charger6_hw_reset ( charger6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CHARGER6_H

/*! @} */ // charger6

// ------------------------------------------------------------------------ END
