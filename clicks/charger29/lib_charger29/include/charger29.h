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
 * @file charger29.h
 * @brief This file contains API for Charger 29 Click Driver.
 */

#ifndef CHARGER29_H
#define CHARGER29_H

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
 * @addtogroup charger29 Charger 29 Click Driver
 * @brief API for configuring and manipulating Charger 29 Click driver.
 * @{
 */

/**
 * @defgroup charger29_reg Charger 29 Registers List
 * @brief List of registers of Charger 29 Click driver.
 */

/**
 * @addtogroup charger29_reg
 * @{
 */

/**
 * @brief Charger 29 register map.
 * @details Specified register map of Charger 29 Click driver.
 */
#define CHARGER29_REG_STAT0                         0x00
#define CHARGER29_REG_STAT1                         0x01
#define CHARGER29_REG_FLAG0                         0x02
#define CHARGER29_REG_VBAT_CTRL                     0x03
#define CHARGER29_REG_ICHG_CTRL                     0x04
#define CHARGER29_REG_CHARGECTRL0                   0x05
#define CHARGER29_REG_CHARGECTRL1                   0x06
#define CHARGER29_REG_IC_CTRL                       0x07
#define CHARGER29_REG_TMR_ILIM                      0x08
#define CHARGER29_REG_SHIP_RST                      0x09
#define CHARGER29_REG_SYS_REG                       0x0A
#define CHARGER29_REG_TS_CONTROL                    0x0B
#define CHARGER29_REG_MASK_ID                       0x0C

/*! @} */ // charger29_reg

/**
 * @defgroup charger29_set Charger 29 Registers Settings
 * @brief Settings for registers of Charger 29 Click driver.
 */

/**
 * @addtogroup charger29_set
 * @{
 */

/**
 * @brief Charger 29 STAT0 register setting.
 * @details Specified setting for STAT0 register of Charger 29 Click driver.
 */
#define CHARGER29_STAT0_TS_OPEN_STAT                0x80
#define CHARGER29_STAT0_CHG_STAT_NOT_CHARGING       0x00
#define CHARGER29_STAT0_CHG_STAT_CC_CHARGING        0x20
#define CHARGER29_STAT0_CHG_STAT_CV_CHARGING        0x40
#define CHARGER29_STAT0_CHG_STAT_CHARGE_DONE        0x60
#define CHARGER29_STAT0_CHG_STAT_MASK               0x60
#define CHARGER29_STAT0_ILIM_ACTIVE_STAT            0x10
#define CHARGER29_STAT0_VDPPM_ACTIVE_STAT           0x08
#define CHARGER29_STAT0_VINDPM_ACTIVE_STAT          0x04
#define CHARGER29_STAT0_THERMREG_ACTIVE_STAT        0x02
#define CHARGER29_STAT0_VIN_PGOOD_STAT              0x01

/**
 * @brief Charger 29 STAT1 register setting.
 * @details Specified setting for STAT1 register of Charger 29 Click driver.
 */
#define CHARGER29_STAT1_VIN_OVP_STAT                0x80
#define CHARGER29_STAT1_BUVLO_STAT                  0x60
#define CHARGER29_STAT1_TS_STAT_NORMAL              0x00
#define CHARGER29_STAT1_TS_STAT_SUSPENDED           0x08
#define CHARGER29_STAT1_TS_STAT_CC_REDUCED          0x10
#define CHARGER29_STAT1_TS_STAT_CV_REDUCED          0x18
#define CHARGER29_STAT1_TS_STAT_MASK                0x18
#define CHARGER29_STAT1_SAFETY_TMR_FAULT_FLAG       0x04
#define CHARGER29_STAT1_WAKE1_FLAG                  0x02
#define CHARGER29_STAT1_WAKE2_FLAG                  0x01

/**
 * @brief Charger 29 FLAG0 register setting.
 * @details Specified setting for FLAG0 register of Charger 29 Click driver.
 */
#define CHARGER29_FLAG0_TS_FAULT                    0x80
#define CHARGER29_FLAG0_ILIM_ACTIVE_FLAG            0x40
#define CHARGER29_FLAG0_VDPPM_ACTIVE_FLAG           0x20
#define CHARGER29_FLAG0_VINDPM_ACTIVE_FLAG          0x10
#define CHARGER29_FLAG0_THERMREG_ACTIVE_FLAG        0x08
#define CHARGER29_FLAG0_VIN_OVP_FAULT_FLAG          0x04
#define CHARGER29_FLAG0_BUVLO_FAULT_FLAG            0x02
#define CHARGER29_FLAG0_BAT_OCP_FAULT               0x01

/**
 * @brief Charger 29 VBAT_CTRL register setting.
 * @details Specified setting for VBAT_CTRL register of Charger 29 Click driver.
 */
#define CHARGER29_VBAT_CTRL_PG_MODE_PG              0x00
#define CHARGER29_VBAT_CTRL_PG_MODE_GPO             0x80
#define CHARGER29_VBAT_CTRL_PG_MODE_MASK            0x80
#define CHARGER29_VBAT_CTRL_VBATREG_MASK            0x7F

/**
 * @brief Charger 29 ICHG_CTRL register setting.
 * @details Specified setting for ICHG_CTRL register of Charger 29 Click driver.
 */
#define CHARGER29_ICHG_CTRL_CHG_DIS_ENABLED         0x00
#define CHARGER29_ICHG_CTRL_CHG_DIS_DISABLED        0x80
#define CHARGER29_ICHG_CTRL_CHG_DIS_MASK            0x80
#define CHARGER29_ICHG_CTRL_ICHG_MASK               0x7F

/**
 * @brief Charger 29 CHARGECTRL0 register setting.
 * @details Specified setting for CHARGECTRL0 register of Charger 29 Click driver.
 */
#define CHARGER29_CHARGECTRL0_EN_FC_MODE_DIS        0x00
#define CHARGER29_CHARGECTRL0_EN_FC_MODE_EN         0x80
#define CHARGER29_CHARGECTRL0_EN_FC_MODE_MASK       0x80
#define CHARGER29_CHARGECTRL0_IPRECHG_2X_TERM       0x00
#define CHARGER29_CHARGECTRL0_IPRECHG_TERM          0x40
#define CHARGER29_CHARGECTRL0_IPRECHG_MASK          0x40
#define CHARGER29_CHARGECTRL0_ITERM_DISABLE         0x00
#define CHARGER29_CHARGECTRL0_ITERM_5PCT_ICHG       0x10
#define CHARGER29_CHARGECTRL0_ITERM_10PCT_ICHG      0x20
#define CHARGER29_CHARGECTRL0_ITERM_20PCT_ICHG      0x30
#define CHARGER29_CHARGECTRL0_ITERM_MASK            0x30
#define CHARGER29_CHARGECTRL0_VINDPM_VBAT_300MV     0x00
#define CHARGER29_CHARGECTRL0_VINDPM_4_5V           0x04
#define CHARGER29_CHARGECTRL0_VINDPM_4_7V           0x08
#define CHARGER29_CHARGECTRL0_VINDPM_DISABLE        0x0C
#define CHARGER29_CHARGECTRL0_VINDPM_MASK           0x0C
#define CHARGER29_CHARGECTRL0_THERM_REG_100C        0x00
#define CHARGER29_CHARGECTRL0_THERM_REG_80C         0x01
#define CHARGER29_CHARGECTRL0_THERM_REG_60C         0x02
#define CHARGER29_CHARGECTRL0_THERM_REG_DISABLE     0x03
#define CHARGER29_CHARGECTRL0_THERM_REG_MASK        0x03

/**
 * @brief Charger 29 CHARGECTRL1 register setting.
 * @details Specified setting for CHARGECTRL1 register of Charger 29 Click driver.
 */
#define CHARGER29_CHARGECTRL1_IBAT_OCP_500MA        0x00
#define CHARGER29_CHARGECTRL1_IBAT_OCP_1000MA       0x40
#define CHARGER29_CHARGECTRL1_IBAT_OCP_1500MA       0x80
#define CHARGER29_CHARGECTRL1_IBAT_OCP_3000MA       0xC0
#define CHARGER29_CHARGECTRL1_IBAT_OCP_MASK         0xC0
#define CHARGER29_CHARGECTRL1_BUVLO_3_0V            0x10
#define CHARGER29_CHARGECTRL1_BUVLO_2_8V            0x18
#define CHARGER29_CHARGECTRL1_BUVLO_2_6V            0x20
#define CHARGER29_CHARGECTRL1_BUVLO_2_4V            0x28
#define CHARGER29_CHARGECTRL1_BUVLO_2_2V            0x30
#define CHARGER29_CHARGECTRL1_BUVLO_2_0V            0x38
#define CHARGER29_CHARGECTRL1_BUVLO_MASK            0x38
#define CHARGER29_CHARGECTRL1_CHG_STATUS_INT_MASK   0x04
#define CHARGER29_CHARGECTRL1_ILIM_INT_MASK         0x02
#define CHARGER29_CHARGECTRL1_VINDPM_INT_MASK       0x01

/**
 * @brief Charger 29 IC_CTRL register setting.
 * @details Specified setting for IC_CTRL register of Charger 29 Click driver.
 */
#define CHARGER29_IC_CTRL_TS_EN_DISABLE             0x00
#define CHARGER29_IC_CTRL_TS_EN_ENABLE              0x80
#define CHARGER29_IC_CTRL_TS_EN_MASK                0x80
#define CHARGER29_IC_CTRL_VLOWV_SEL_3V              0x00
#define CHARGER29_IC_CTRL_VLOWV_SEL_2_8V            0x40
#define CHARGER29_IC_CTRL_VLOWV_SEL_MASK            0x40
#define CHARGER29_IC_CTRL_VRCH_100MV                0x00
#define CHARGER29_IC_CTRL_VRCH_200MV                0x20
#define CHARGER29_IC_CTRL_VRCH_MASK                 0x20
#define CHARGER29_IC_CTRL_2XTMR_EN_DISABLE          0x00
#define CHARGER29_IC_CTRL_2XTMR_EN_ENABLE           0x10
#define CHARGER29_IC_CTRL_2XTMR_EN_MASK             0x10
#define CHARGER29_IC_CTRL_SAFETY_TIMER_3H           0x00
#define CHARGER29_IC_CTRL_SAFETY_TIMER_6H           0x04
#define CHARGER29_IC_CTRL_SAFETY_TIMER_12H          0x08
#define CHARGER29_IC_CTRL_SAFETY_TIMER_DISABLE      0x0C
#define CHARGER29_IC_CTRL_SAFETY_TIMER_MASK         0x0C
#define CHARGER29_IC_CTRL_WATCHDOG_SEL_160S_DEFAULT 0x00
#define CHARGER29_IC_CTRL_WATCHDOG_SEL_160S_RESET   0x01
#define CHARGER29_IC_CTRL_WATCHDOG_SEL_40S_RESET    0x02
#define CHARGER29_IC_CTRL_WATCHDOG_SEL_DISABLE      0x03
#define CHARGER29_IC_CTRL_WATCHDOG_SEL_MASK         0x03

/**
 * @brief Charger 29 TMR_ILIM register setting.
 * @details Specified setting for TMR_ILIM register of Charger 29 Click driver.
 */
#define CHARGER29_TMR_ILIM_MR_LPRESS_5S             0x00
#define CHARGER29_TMR_ILIM_MR_LPRESS_10S            0x40
#define CHARGER29_TMR_ILIM_MR_LPRESS_15S            0x80
#define CHARGER29_TMR_ILIM_MR_LPRESS_20S            0xC0
#define CHARGER29_TMR_ILIM_MR_LPRESS_MASK           0xC0
#define CHARGER29_TMR_ILIM_MR_RESET_VIN             0x20
#define CHARGER29_TMR_ILIM_AUTOWAKE_0_5S            0x00
#define CHARGER29_TMR_ILIM_AUTOWAKE_1S              0x08
#define CHARGER29_TMR_ILIM_AUTOWAKE_2S              0x10
#define CHARGER29_TMR_ILIM_AUTOWAKE_4S              0x18
#define CHARGER29_TMR_ILIM_AUTOWAKE_MASK            0x18
#define CHARGER29_TMR_ILIM_ILIM_50MA                0x00
#define CHARGER29_TMR_ILIM_ILIM_100MA               0x01
#define CHARGER29_TMR_ILIM_ILIM_200MA               0x02
#define CHARGER29_TMR_ILIM_ILIM_300MA               0x03
#define CHARGER29_TMR_ILIM_ILIM_400MA               0x04
#define CHARGER29_TMR_ILIM_ILIM_500MA               0x05
#define CHARGER29_TMR_ILIM_ILIM_665MA               0x06
#define CHARGER29_TMR_ILIM_ILIM_1050MA              0x07
#define CHARGER29_TMR_ILIM_ILIM_MASK                0x07

/**
 * @brief Charger 29 SHIP_RST register setting.
 * @details Specified setting for SHIP_RST register of Charger 29 Click driver.
 */
#define CHARGER29_SHIP_RST_REG_RST_NOTHING          0x00
#define CHARGER29_SHIP_RST_REG_RST_RESET            0x80
#define CHARGER29_SHIP_RST_REG_RST_MASK             0x80
#define CHARGER29_SHIP_RST_EN_RST_SHIP_NOTHING      0x00
#define CHARGER29_SHIP_RST_EN_RST_SHIP_SHUTDOWN     0x20
#define CHARGER29_SHIP_RST_EN_RST_SHIP_SHIP         0x40
#define CHARGER29_SHIP_RST_EN_RST_SHIP_HW_RESET     0x60
#define CHARGER29_SHIP_RST_EN_RST_SHIP_MASK         0x60
#define CHARGER29_SHIP_RST_PB_LPRESS_ACTION_NOTHING 0x00
#define CHARGER29_SHIP_RST_PB_LPRESS_ACTION_RESET   0x08
#define CHARGER29_SHIP_RST_PB_LPRESS_ACTION_SHIP    0x10
#define CHARGER29_SHIP_RST_PB_LPRESS_ACTION_SHUTDN  0x18
#define CHARGER29_SHIP_RST_PB_LPRESS_ACTION_MASK    0x18
#define CHARGER29_SHIP_RST_WAKE1_TMR_300MS          0x00
#define CHARGER29_SHIP_RST_WAKE1_TMR_1S             0x04
#define CHARGER29_SHIP_RST_WAKE1_TMR_MASK           0x04
#define CHARGER29_SHIP_RST_WAKE2_TMR_2S             0x00
#define CHARGER29_SHIP_RST_WAKE2_TMR_3S             0x02
#define CHARGER29_SHIP_RST_WAKE2_TMR_MASK           0x02
#define CHARGER29_SHIP_RST_EN_PUSH_DISABLE          0x00
#define CHARGER29_SHIP_RST_EN_PUSH_ENABLE           0x01
#define CHARGER29_SHIP_RST_EN_PUSH_MASK             0x01

/**
 * @brief Charger 29 SYS_REG register setting.
 * @details Specified setting for SYS_REG register of Charger 29 Click driver.
 */
#define CHARGER29_SYS_REG_SYS_REG_CTRL_TRACKING     0x00
#define CHARGER29_SYS_REG_SYS_REG_CTRL_4_4V         0x20
#define CHARGER29_SYS_REG_SYS_REG_CTRL_4_5V         0x40
#define CHARGER29_SYS_REG_SYS_REG_CTRL_4_6V         0x60
#define CHARGER29_SYS_REG_SYS_REG_CTRL_4_7V         0x80
#define CHARGER29_SYS_REG_SYS_REG_CTRL_4_8V         0xA0
#define CHARGER29_SYS_REG_SYS_REG_CTRL_4_9V         0xC0
#define CHARGER29_SYS_REG_SYS_REG_CTRL_PASS_THROUGH 0xE0
#define CHARGER29_SYS_REG_SYS_REG_CTRL_MASK         0xE0
#define CHARGER29_SYS_REG_PG_GPO_HIGH_Z             0x00
#define CHARGER29_SYS_REG_PG_GPO_LOW                0x10
#define CHARGER29_SYS_REG_PG_GPO_MASK               0x10
#define CHARGER29_SYS_REG_SYS_MODE_VIN              0x00
#define CHARGER29_SYS_REG_SYS_MODE_VBAT             0x04
#define CHARGER29_SYS_REG_SYS_MODE_FLOAT            0x08
#define CHARGER29_SYS_REG_SYS_MODE_PULLDOWN         0x0C
#define CHARGER29_SYS_REG_SYS_MODE_MASK             0x0C
#define CHARGER29_SYS_REG_WATCHDOG_15S_ENABLE_DIS   0x00
#define CHARGER29_SYS_REG_WATCHDOG_15S_ENABLE_RESET 0x02
#define CHARGER29_SYS_REG_WATCHDOG_15S_ENABLE_MASK  0x02
#define CHARGER29_SYS_REG_VDPPM_DIS_ENABLE          0x00
#define CHARGER29_SYS_REG_VDPPM_DIS_DISABLE         0x01
#define CHARGER29_SYS_REG_VDPPM_DIS_MASK            0x01

/**
 * @brief Charger 29 TS_CONTROL register setting.
 * @details Specified setting for TS_CONTROL register of Charger 29 Click driver.
 */
#define CHARGER29_TS_CONTROL_TS_HOT_60C             0x00
#define CHARGER29_TS_CONTROL_TS_HOT_65C             0x40
#define CHARGER29_TS_CONTROL_TS_HOT_50C             0x80
#define CHARGER29_TS_CONTROL_TS_HOT_45C             0xC0
#define CHARGER29_TS_CONTROL_TS_HOT_MASK            0xC0
#define CHARGER29_TS_CONTROL_TS_COLD_0C             0x00
#define CHARGER29_TS_CONTROL_TS_COLD_3C             0x10
#define CHARGER29_TS_CONTROL_TS_COLD_5C             0x20
#define CHARGER29_TS_CONTROL_TS_COLD_MIN_3C         0x30
#define CHARGER29_TS_CONTROL_TS_COLD_MASK           0x30
#define CHARGER29_TS_CONTROL_TS_WARM_DIS_45C        0x00
#define CHARGER29_TS_CONTROL_TS_WARM_DIS_DISABLE    0x08
#define CHARGER29_TS_CONTROL_TS_WARM_DIS_MASK       0x08
#define CHARGER29_TS_CONTROL_TS_COOL_DIS_10C        0x00
#define CHARGER29_TS_CONTROL_TS_COOL_DIS_DISABLE    0x04
#define CHARGER29_TS_CONTROL_TS_COOL_DIS_MASK       0x04
#define CHARGER29_TS_CONTROL_TS_ICHG_0_5_ICHG       0x00
#define CHARGER29_TS_CONTROL_TS_ICHG_0_2_ICHG       0x02
#define CHARGER29_TS_CONTROL_TS_ICHG_MASK           0x02
#define CHARGER29_TS_CONTROL_TS_VRCG_VBATREG_100MV  0x00
#define CHARGER29_TS_CONTROL_TS_VRCG_VBATREG_200MV  0x01
#define CHARGER29_TS_CONTROL_TS_VRCG_MASK           0x01

/**
 * @brief Charger 29 MASK_ID register setting.
 * @details Specified setting for MASK_ID register of Charger 29 Click driver.
 */
#define CHARGER29_MASK_ID_TS_INT_MASK               0x80
#define CHARGER29_MASK_ID_TREG_INT_MASK             0x40
#define CHARGER29_MASK_ID_BAT_INT_MASK              0x20
#define CHARGER29_MASK_ID_PG_INT_MASK               0x10
#define CHARGER29_MASK_ID_DEVICE_ID                 0x04
#define CHARGER29_MASK_ID_DEVICE_ID_MASK            0x0F

/**
 * @brief Charger 29 charging current setting.
 * @details Specified setting for charging current of Charger 29 Click driver.
 */
#define CHARGER29_ICHG_MIN                          5
#define CHARGER29_ICHG_MAX                          1000
#define CHARGER29_ICHG_RES_POINT                    35
#define CHARGER29_ICHG_RES_DIVIDER                  10
#define CHARGER29_ICHG_RES_OFFSET                   31
#define CHARGER29_ICHG_DEFAULT                      200

/**
 * @brief Charger 29 battery voltage regulation setting.
 * @details Specified setting for battery voltage regulation of Charger 29 Click driver.
 */
#define CHARGER29_VBAT_MIN                          3500
#define CHARGER29_VBAT_MAX                          4650
#define CHARGER29_VBAT_RES_DIVIDER                  10
#define CHARGER29_VBAT_DEFAULT                      4200

/**
 * @brief Charger 29 device address setting.
 * @details Specified setting for device slave address selection of
 * Charger 29 Click driver.
 */
#define CHARGER29_DEVICE_ADDRESS                    0x6A

/*! @} */ // charger29_set

/**
 * @defgroup charger29_map Charger 29 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 29 Click driver.
 */

/**
 * @addtogroup charger29_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 29 Click to the selected MikroBUS.
 */
#define CHARGER29_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger29_map
/*! @} */ // charger29

/**
 * @brief Charger 29 Click status object.
 * @details Status object definition of Charger 29 Click driver.
 */
typedef struct
{
    uint8_t stat0;                  /**< STAT0 register value. */
    uint8_t stat1;                  /**< STAT1 register value. */
    uint8_t flag0;                  /**< FLAG0 register value. */

} charger29_status_t;

/**
 * @brief Charger 29 Click context object.
 * @details Context object definition of Charger 29 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;           /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} charger29_t;

/**
 * @brief Charger 29 Click configuration object.
 * @details Configuration object definition of Charger 29 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;             /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} charger29_cfg_t;

/**
 * @brief Charger 29 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER29_OK = 0,
    CHARGER29_ERROR = -1

} charger29_return_value_t;

/*!
 * @addtogroup charger29 Charger 29 Click Driver
 * @brief API for configuring and manipulating Charger 29 Click driver.
 * @{
 */

/**
 * @brief Charger 29 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger29_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger29_cfg_setup ( charger29_cfg_t *cfg );

/**
 * @brief Charger 29 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger29_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger29_init ( charger29_t *ctx, charger29_cfg_t *cfg );

/**
 * @brief Charger 29 default configuration function.
 * @details This function executes a default configuration of Charger 29
 * Click board.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t charger29_default_cfg ( charger29_t *ctx );

/**
 * @brief Charger 29 write register function.
 * @details This function writes a single byte of data to the selected register
 * of the Charger 29 Click board.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger29_write_reg ( charger29_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Charger 29 write registers function.
 * @details This function writes a sequence of bytes starting from the selected
 * register of the Charger 29 Click board.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger29_write_regs ( charger29_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Charger 29 read register function.
 * @details This function reads a single byte of data from the selected register
 * of the Charger 29 Click board.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory where the read byte will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger29_read_reg ( charger29_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Charger 29 read registers function.
 * @details This function reads a sequence of bytes starting from the selected
 * register of the Charger 29 Click board.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the memory where the read data will be stored.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger29_read_regs ( charger29_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Charger 29 get INT pin function.
 * @details This function reads the logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t charger29_get_int_pin ( charger29_t *ctx );

/**
 * @brief Charger 29 check communication function.
 * @details This function checks device communication by reading and verifying
 * the device ID from the Charger 29 Click board.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger29_check_communication ( charger29_t *ctx );

/**
 * @brief Charger 29 software reset function.
 * @details This function performs a software reset of the Charger 29 Click board.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger29_sw_reset ( charger29_t *ctx );

/**
 * @brief Charger 29 enable charging function.
 * @details This function enables charging by clearing the charging disable bit.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger29_enable_charging ( charger29_t *ctx );

/**
 * @brief Charger 29 disable charging function.
 * @details This function disables charging by setting the charging disable bit.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger29_disable_charging ( charger29_t *ctx );

/**
 * @brief Charger 29 set charging current function.
 * @details This function sets the charging current based on the specified value in milliamps.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @param[in] ichg : Charging current in milliamps [5mA to 1000mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger29_set_charging_current ( charger29_t *ctx, uint16_t ichg );

/**
 * @brief Charger 29 set battery regulation voltage function.
 * @details This function sets the battery regulation voltage in millivolts.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @param[in] vbat_mv : Battery voltage regulation value in millivolts [3500mV to 4650mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger29_set_vbat_reg ( charger29_t *ctx, uint16_t vbat_mv );

/**
 * @brief Charger 29 read status function.
 * @details This function reads the status and flag registers of the Charger 29 Click board.
 * @param[in] ctx : Click context object.
 * See #charger29_t object definition for detailed explanation.
 * @param[out] status : Pointer to the structure where status register values will be stored.
 * See #charger29_status_t structure definition for detailed information.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger29_read_status ( charger29_t *ctx, charger29_status_t *status );

#ifdef __cplusplus
}
#endif
#endif // CHARGER29_H

/*! @} */ // charger29

// ------------------------------------------------------------------------ END
