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
 * @file battman3.h
 * @brief This file contains API for BATT-MAN 3 Click Driver.
 */

#ifndef BATTMAN3_H
#define BATTMAN3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup battman3 BATT-MAN 3 Click Driver
 * @brief API for configuring and manipulating BATT-MAN 3 Click driver.
 * @{
 */

/**
 * @defgroup battman3_reg BATT-MAN 3 Registers List
 * @brief List of registers of BATT-MAN 3 Click driver.
 */

/**
 * @addtogroup battman3_reg
 * @{
 */

/**
 * @brief BATT-MAN 3 description register.
 * @details Specified register for description of BATT-MAN 3 Click driver.
 */
#define BATTMAN3_REG_MANUFACTURE_AND_MODEL_ID           0x00
#define BATTMAN3_REG_SILICON_REVSION                    0x01
#define BATTMAN3_REG_CHARGER_VBUS_ILIM                  0x02
#define BATTMAN3_REG_CHARGER_TERMINATION_SETTING        0x03
#define BATTMAN3_REG_CHARGER_CURRENT_SETTING            0x04
#define BATTMAN3_REG_CHARGER_VOLTAGE_THRESHOLD          0x05
#define BATTMAN3_REG_CHARGER_TIMER_SETTING              0x06
#define BATTMAN3_REG_CHARGER_FUNCTION_SETTING1          0x07
#define BATTMAN3_REG_CHARGER_STATUS1                    0x08
#define BATTMAN3_REG_CHARGER_STATUS2                    0x09
#define BATTMAN3_REG_CHARGER_FAULT                      0x0A
#define BATTMAN3_REG_BATTERY_SHORT                      0x0B
#define BATTMAN3_REG_BATTERY_THERMISTOR_CONTROL         0x0C
#define BATTMAN3_REG_V_SOC_0                            0x0D
#define BATTMAN3_REG_V_SOC_5                            0x0E
#define BATTMAN3_REG_V_SOC_11                           0x0F
#define BATTMAN3_REG_V_SOC_19                           0x10
#define BATTMAN3_REG_V_SOC_28                           0x11
#define BATTMAN3_REG_V_SOC_41                           0x12
#define BATTMAN3_REG_V_SOC_55                           0x13
#define BATTMAN3_REG_V_SOC_69                           0x14
#define BATTMAN3_REG_V_SOC_84                           0x15
#define BATTMAN3_REG_V_SOC_100                          0x16
#define BATTMAN3_REG_FILTER_SETTING1                    0x17
#define BATTMAN3_REG_FILTER_SETTING2                    0x18
#define BATTMAN3_REG_RBAT_0                             0x19
#define BATTMAN3_REG_RBAT_10                            0x1A
#define BATTMAN3_REG_RBAT_20                            0x1B
#define BATTMAN3_REG_RBAT_30                            0x1C
#define BATTMAN3_REG_RBAT_40                            0x1D
#define BATTMAN3_REG_RBAT_60                            0x1E
#define BATTMAN3_REG_K_RBAT_CHARGE                      0x1F
#define BATTMAN3_REG_BAT_TEMP                           0x20
#define BATTMAN3_REG_BAT_SOC                            0x21
#define BATTMAN3_REG_VBAT_READ_H                        0x22
#define BATTMAN3_REG_VBAT_READ_L                        0x23
#define BATTMAN3_REG_FUEL_GAUGE_MODE                    0x24
#define BATTMAN3_REG_SOC_RESET                          0x25
#define BATTMAN3_REG_BST_LED_CTRL                       0x26
#define BATTMAN3_REG_BST_CFG                            0x27
#define BATTMAN3_REG_IBL_SET                            0x28
#define BATTMAN3_REG_ILED2_SET                          0x29
#define BATTMAN3_REG_ILED3_SET                          0x2A
#define BATTMAN3_REG_ILED4_SET                          0x2B
#define BATTMAN3_REG_ILED5_SET                          0x2C
#define BATTMAN3_REG_BL_FR                              0x2D  
#define BATTMAN3_REG_LED3_BLINK                         0x2E
#define BATTMAN3_REG_LED4_BLINK                         0x2F
#define BATTMAN3_REG_LED5_BLINK                         0x30
#define BATTMAN3_REG_LED_STATUS                         0x31
#define BATTMAN3_REG_LDO_CTRL                           0x32
#define BATTMAN3_REG_LDO_CFG                            0x33
#define BATTMAN3_REG_VID_LDO12                          0x34
#define BATTMAN3_REG_VID_LDO3                           0x35
#define BATTMAN3_REG_PGOOD_STATUS                       0x36
#define BATTMAN3_REG_PGOOD_MASK                         0x37
#define BATTMAN3_REG_CHARGER_INTERRUPT_ENABLE           0x38
#define BATTMAN3_REG_CHARGER_INTERRUPT_FLAG             0x39
#define BATTMAN3_REG_BOOST_LDO_INTERRUPT_ENABLE         0x3A
#define BATTMAN3_REG_BOOST_LDO_INTERRUPT_FLAG           0x3B
#define BATTMAN3_REG_DEFAULT_SET                        0x3C
#define BATTMAN3_REG_NTC47K_SET                         0x3D



/*! @} */ // battman3_reg

/**
 * @defgroup battman3_set BATT-MAN 3 Registers Settings
 * @brief Settings for registers of BATT-MAN 3 Click driver.
 */

/**
 * @addtogroup battman3_set
 * @{
 */

/**
 * @brief BATT-MAN 3 charge status.
 * @details Specified values of charge status of BATT-MAN 3 Click driver.
 */
#define BATTMAN3_CHARGE_STATUS1_OFF                     0x0
#define BATTMAN3_CHARGE_STATUS1_TRICLE_CHARGE           0x1
#define BATTMAN3_CHARGE_STATUS1_FAST_CHARGE_CC          0x2
#define BATTMAN3_CHARGE_STATUS1_FAST_CHARGE_CV          0x3
#define BATTMAN3_CHARGE_STATUS1_CHARGE_COMPLETE         0x4
#define BATTMAN3_CHARGE_STATUS1_SUSPEND                 0x5
#define BATTMAN3_CHARGE_STATUS1_TIMER_EXPIRED           0x6
#define BATTMAN3_CHARGE_STATUS1_BATTERY_DETECTION       0x7
#define BATTMAN3_CHARGE_STATUS2_BATTERY_MONITOR_OFF     0x0
#define BATTMAN3_CHARGE_STATUS2_NO_BATTERY              0x1
#define BATTMAN3_CHARGE_STATUS2_VBSNS_LESSTHEN_VTRK     0x2
#define BATTMAN3_CHARGE_STATUS2_VBSNS_MIDDLE_VRK_VWEAK  0x3
#define BATTMAN3_CHARGE_STATUS2_VBSNS_MORETHEN_VWEAK    0x4

/**
 * @brief BATT-MAN 3 acitve state.
 * @details Specified values of active state of BATT-MAN 3 Click driver.
 */
#define BATTMAN3_ENABLE                                 0x1
#define BATTMAN3_DISABLE                                0x0

/**
 * @brief BATT-MAN 3 device address setting.
 * @details Specified setting for device slave address selection of
 * BATT-MAN 3 Click driver.
 */
#define BATTMAN3_SET_DEV_ADDR                           0x44

/*! @} */ // battman3_set

/**
 * @defgroup battman3_map BATT-MAN 3 MikroBUS Map
 * @brief MikroBUS pin mapping of BATT-MAN 3 Click driver.
 */

/**
 * @addtogroup battman3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BATT-MAN 3 Click to the selected MikroBUS.
 */
#define BATTMAN3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pgood = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.bok = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // battman3_map
/*! @} */ // battman3

/**
 * @brief BATT-MAN 3 Click context object.
 * @details Context object definition of BATT-MAN 3 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  pgood;    /**< Power good. */
    digital_in_t  bok;      /**< Battery OK. */
    digital_in_t  int_pin;  /**< Interrupt. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} battman3_t;

/**
 * @brief BATT-MAN 3 Click configuration object.
 * @details Configuration object definition of BATT-MAN 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  pgood;      /**< Power good. */
    pin_name_t  bok;        /**< Battery OK. */
    pin_name_t  int_pin;    /**< Interrupt. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} battman3_cfg_t;

/**
 * @brief BATT-MAN 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BATTMAN3_OK = 0,
    BATTMAN3_ERROR = -1

} battman3_return_value_t;

/**
 * @brief BATT-MAN 3 Click LDO voltage output.
 * @details Predefined enum values for driver LDO voltage output.
 */
typedef enum
{
    BATTMAN3_LDO_4p20V = 0,
    BATTMAN3_LDO_3p60V,
    BATTMAN3_LDO_3p30V,
    BATTMAN3_LDO_3p15V,
    BATTMAN3_LDO_3p00V,
    BATTMAN3_LDO_2p85V,
    BATTMAN3_LDO_2p50V,
    BATTMAN3_LDO_2p30V,
    BATTMAN3_LDO_2p10V,
    BATTMAN3_LDO_1p80V,
    BATTMAN3_LDO_1p50V,
    BATTMAN3_LDO_1p40V,
    BATTMAN3_LDO_1p30V,
    BATTMAN3_LDO_1p20V,
    BATTMAN3_LDO_1p10V,
    BATTMAN3_LDO_1p00V

} battman3_ldo_vout_t;

/**
 * @brief BATT-MAN 3 Click LDO.
 * @details Predefined enum values for driver LDO selecting.
 */
typedef enum
{
    BATTMAN3_LDO1,
    BATTMAN3_LDO2,
    BATTMAN3_LDO3

} battman3_ldo_t;

/**
 * @brief BATT-MAN 3 Click dead battery voltage.
 * @details Predefined enum values for driver dead battery voltage.
 */
typedef enum
{
    BATTMAN3_VTRK_DEAD_2p4V,
    BATTMAN3_VTRK_DEAD_2p5V,
    BATTMAN3_VTRK_DEAD_2p6V,
    BATTMAN3_VTRK_DEAD_3p3V

} battman3_vtrk_dead_t;

/*!
 * @addtogroup battman3 BATT-MAN 3 Click Driver
 * @brief API for configuring and manipulating BATT-MAN 3 Click driver.
 * @{
 */

/**
 * @brief BATT-MAN 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #battman3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void battman3_cfg_setup ( battman3_cfg_t *cfg );

/**
 * @brief BATT-MAN 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #battman3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t battman3_init ( battman3_t *ctx, battman3_cfg_t *cfg );

/**
 * @brief BATT-MAN 3 default configuration function.
 * @details This function executes a default configuration of BATT-MAN 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t battman3_default_cfg ( battman3_t *ctx );

/**
 * @brief BATT-MAN 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t battman3_generic_write ( battman3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Register writing function.
 * @details This function writes a data to the selected register.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] tx_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t battman3_reg_write ( battman3_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief BATT-MAN 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t battman3_generic_read ( battman3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Register reading  function.
 * @details This function reads a data from the selected register.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] rx_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t battman3_reg_read ( battman3_t *ctx, uint8_t reg, uint8_t *rx_data );

/**
 * @brief Get battery OK.
 * @details This function reads a state of the @b bok pin.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @return Battery ok pin state.
 */
uint8_t battman3_get_battery_ok ( battman3_t *ctx );

/**
 * @brief Get power good.
 * @details This function reads a state of the @b pgd pin.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @return Power good pin state.
 */
uint8_t battman3_get_power_good ( battman3_t *ctx );

/**
 * @brief Get interrupt.
 * @details This function reads a state of the @b int_pin pin.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @return Interrupt pin state.
 */
uint8_t battman3_get_interrupt ( battman3_t *ctx );

/**
 * @brief Enable/Disable charging.
 * @details This function sets or clears 1st bit of the 
 * @b CHARGER_FUNCTION_SETTING1 register.
 * @param[in,out] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[in] enable :  @li @c =0 Disable,
 *                      @li @c >0 Enable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t battman3_set_charge_state ( battman3_t *ctx, uint8_t enable );

/**
 * @brief Set charge termination voltage.
 * @details This function sets charge termination voltage.
 * @param[in,out] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[in] voltage :  Termination voltage in range from 3.7V to 4.5V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t battman3_set_charge_termination_voltage ( battman3_t *ctx, float voltage );

/**
 * @brief Set charge termination voltage.
 * @details This function sets charge termination voltage.
 * @param[in,out] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[in] vtrk_dead :  Trickle to fast charge dead battery voltage.
 * @param[in] vweak :  Weak voltage in range from 2.7V to 3.4V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t battman3_set_charge_voltage_threshold ( battman3_t *ctx, battman3_vtrk_dead_t vtrk_dead, float vweak );

/**
 * @brief Set charge current limit.
 * @details This function sets charge current limit on vbus pin.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[in] current :  Current limit in range from 100mA to 1500mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t battman3_set_charge_vbus_current_limit ( battman3_t *ctx, uint16_t current );

/**
 * @brief Enable/Disable LDO.
 * @details This function enable or disable LDO.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[in] ldo : Select whitch LDO to change state.
 * @param[in] enable :  @li @c =0 Disable,
 *                      @li @c >0 Enable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t battman3_set_ldo_state ( battman3_t *ctx, battman3_ldo_t ldo, uint8_t enable );

/**
 * @brief Set voltage output on LDO.
 * @details This function sets voltage output on LDO.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[in] ldo : Select whitch LDO.
 * @param[in] vout : LDO voltage output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t battman3_set_ldo_vout ( battman3_t *ctx, battman3_ldo_t ldo, battman3_ldo_vout_t vout );

/**
 * @brief Read battery voltage level.
 * @details This function reads and calculates battery voltage.
 * @param[in] ctx : Click context object.
 * See #battman3_t object definition for detailed explanation.
 * @param[out] vout : Battery voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t battman3_get_battery_voltage ( battman3_t *ctx, float *vout );

#ifdef __cplusplus
}
#endif
#endif // BATTMAN3_H

/*! @} */ // battman3

// ------------------------------------------------------------------------ END
