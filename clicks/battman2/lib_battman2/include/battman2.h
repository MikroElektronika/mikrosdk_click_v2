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
 * @file battman2.h
 * @brief This file contains API for BATT-MAN 2 Click Driver.
 */

#ifndef BATTMAN2_H
#define BATTMAN2_H

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
 * @addtogroup battman2 BATT-MAN 2 Click Driver
 * @brief API for configuring and manipulating BATT-MAN 2 Click driver.
 * @{
 */

/**
 * @defgroup battman2_reg BATT-MAN 2 Registers List
 * @brief List of registers of BATT-MAN 2 Click driver.
 */

/**
 * @addtogroup battman2_reg
 * @{
 */

/**
 * @brief BATT-MAN 2 description register.
 * @details Specified register for description of BATT-MAN 2 Click driver.
 */
#define BATTMAN2_INT_GLBL0                                0x00
#define BATTMAN2_INT_GLBL1                                0x04
#define BATTMAN2_ERCFLAG                                  0x05 
#define BATTMAN2_STAT_GLBL                                0x06
#define BATTMAN2_INTM_GLBL1                               0x08
#define BATTMAN2_INTM_GLBL0                               0x09
#define BATTMAN2_CNFG_GLBL                                0x10
#define BATTMAN2_CNFG_GPIO0                               0x11
#define BATTMAN2_CNFG_GPIO1                               0x12
#define BATTMAN2_CNFG_GPIO2                               0x13
#define BATTMAN2_CID                                      0x14
#define BATTMAN2_CNFG_WDT                                 0x17                                       
#define BATTMAN2_INT_CHG                                  0x01
#define BATTMAN2_STAT_CHG_A                               0x02
#define BATTMAN2_STAT_CHG_B                               0x03
#define BATTMAN2_INT_M_CHG                                0x07
#define BATTMAN2_CNFG_CHG_A                               0x20
#define BATTMAN2_CNFG_CHG_B                               0x21
#define BATTMAN2_CNFG_CHG_C                               0x22
#define BATTMAN2_CNFG_CHG_D                               0x23
#define BATTMAN2_CNFG_CHG_E                               0x24
#define BATTMAN2_CNFG_CHG_F                               0x25
#define BATTMAN2_CNFG_CHG_G                               0x26
#define BATTMAN2_CNFG_CHG_H                               0x27
#define BATTMAN2_CNFG_CHG_I                               0x28                                    
#define BATTMAN2_CNFG_SBB0_A                              0x29
#define BATTMAN2_CNFG_SBB0_B                              0x2A
#define BATTMAN2_CNFG_SBB1_A                              0x2B
#define BATTMAN2_CNFG_SBB1_B                              0x2C
#define BATTMAN2_CNFG_SBB2_A                              0x2D
#define BATTMAN2_CNFG_SBB2_B                              0x2E
#define BATTMAN2_CNFG_SBB_TOP                             0x2F                                            
#define BATTMAN2_CNFG_LDO0_A                              0x38
#define BATTMAN2_CNFG_LDO0_B                              0x39
#define BATTMAN2_CNFG_LDO1_A                              0x3A
#define BATTMAN2_CNFG_LDO1_B                              0x3B

/*! @} */ // battman2_reg

/**
 * @defgroup battman2_set BATT-MAN 2 Registers Settings
 * @brief Settings for registers of BATT-MAN 2 Click driver.
 */

/**
 * @addtogroup battman2_set
 * @{
 */

/**
 * @brief BATT-MAN 2 description setting.
 * @details Specified setting for description of BATT-MAN 2 Click driver.
 */

/**
 * @brief BATT-MAN 2 GPIO selection.
 * @details Specified for device GPIO selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_SEL_LED_RED                              0x00
#define BATTMAN2_SEL_LED_YELLOW                           0x01
#define BATTMAN2_SEL_LED_BLUE                             0x02
#define BATTMAN2_PIN_STATE_OFF                            0x00
#define BATTMAN2_PIN_STATE_ON                             0x01

/**
 * @brief BATT-MAN 2 GPIO configuration.
 * @details Specified configuration for device GPIO of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_SEL_ALT_GPIO_STANDARD                    0x00
#define BATTMAN2_SEL_ALT_GPIO_A_OUTPUT_SBB2               0x20
#define BATTMAN2_DBEN_GPI_NO_DEBOUNCE                     0x00
#define BATTMAN2_DBEN_GPI_DEBOUNCE_30_ms                  0x10
#define BATTMAN2_DO_GPIO_LOGIC_LOW                        0x00
#define BATTMAN2_DO_GPIO_LOGIC_HIGH                       0x08
#define BATTMAN2_DRV_OPEN_DRAIN                           0x00
#define BATTMAN2_DRV_PUSH_PULL                            0x04
#define BATTMAN2_DI_GPIO_LOGIC_LOW                        0x00
#define BATTMAN2_DI_GPIO_LOGIC_HIGH                       0x02
#define BATTMAN2_DIR_OUTPUT                               0x00
#define BATTMAN2_DIR_INPUT                                0x01

/**
 * @brief BATT-MAN 2 JEITA Temperature Threshold setting.
 * @details Specified setting for device JEITA Temperature Threshold selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_THM_HOT_411_mV                           0x00
#define BATTMAN2_THM_HOT_367_mV                           0x01
#define BATTMAN2_THM_HOT_327_mV                           0x02
#define BATTMAN2_THM_HOT_291_mV                           0x03
#define BATTMAN2_THM_WARM_511_mV                          0x00
#define BATTMAN2_THM_WARM_459_mV                          0x01
#define BATTMAN2_THM_WARM_411_mV                          0x02
#define BATTMAN2_THM_WARM_367_mV                          0x03
#define BATTMAN2_THM_COOL_923_mV                          0x00
#define BATTMAN2_THM_COOL_867_mV                          0x01
#define BATTMAN2_THM_COOL_807_mV                          0x02
#define BATTMAN2_THM_COOL_747_mV                          0x03
#define BATTMAN2_THM_COLD_1024_mV                         0x00
#define BATTMAN2_THM_COLD_976_mV                          0x01
#define BATTMAN2_THM_COLD_923_mV                          0x02
#define BATTMAN2_THM_COLD_867_mV                          0x03

/**
 * @brief BATT-MAN 2 charger enable setting.
 * @details Specified setting for device charger enable of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_BIT_MASK_CHARGER_DISABLE                 0xFE
#define BATTMAN2_BIT_MASK_CHARGER_ENABLE                  0x01
#define BATTMAN2_SET_CHARGER_DISABLE                      0x00
#define BATTMAN2_SET_CHARGER_ENABLE                       0x01

/**
 * @brief BATT-MAN 2 prequalification charge current setting.
 * @details Specified setting for device prequalification charge
 * current selection as a percentage of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_I_PQ_10_PERCENTAGE                       0x00
#define BATTMAN2_I_PQ_20_PERCENTAGE                       0x01

/**
 * @brief BATT-MAN 2 Charger Termination Current setting.
 * @details Specified setting for device Charger Termination Current selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_I_TERM_5_PERCENTAGE                      0x00
#define BATTMAN2_I_TERM_7_5_PERCENTAGE                    0x01
#define BATTMAN2_I_TERM_10_PERCENTAGE                     0x02
#define BATTMAN2_I_TERM_15_PERCENTAGE                     0x03

/**
 * @brief BATT-MAN 2 Top-Off Timer Value setting.
 * @details Specified setting for device Top-Off Timer Value selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_T_TOPOFF_0_MIN                           0x00
#define BATTMAN2_T_TOPOFF_5_MIN                           0x01
#define BATTMAN2_T_TOPOFF_10_MIN                          0x02
#define BATTMAN2_T_TOPOFF_15_MIN                          0x03
#define BATTMAN2_T_TOPOFF_20_MIN                          0x04
#define BATTMAN2_T_TOPOFF_25_MIN                          0x05
#define BATTMAN2_T_TOPOFF_30_MIN                          0x06
#define BATTMAN2_T_TOPOFF_35_MIN                          0x07

/**
 * @brief BATT-MAN 2 die junction temperature regulation point setting.
 * @details Specified setting for device die junction temperature regulation point selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_TJ_REG_60_C                              0x00
#define BATTMAN2_TJ_REG_70_C                              0x01
#define BATTMAN2_TJ_REG_80_C                              0x02
#define BATTMAN2_TJ_REG_90_C                              0x03
#define BATTMAN2_TJ_REG_100_C                             0x04

/**
 * @brief BATT-MAN 2 fast-charge safety timer setting.
 * @details Specified setting for device fast-charge safety timer selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_T_FAST_CHG_TIMER_DISABLED                0x00
#define BATTMAN2_T_FAST_CHG_TIMER_3_HOURS                 0x01
#define BATTMAN2_T_FAST_CHG_TIMER_5_HOURS                 0x02
#define BATTMAN2_T_FAST_CHG_TIMER_7_HOURS                 0x03

/**
 * @brief BATT-MAN 2 Thermistor Enable setting.
 * @details Specified setting for device Thermistor Enable of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_THM_EN_THERMISTOR_DISABLED               0x00
#define BATTMAN2_THM_EN_THERMISTOR_ENABLED                0x01

/**
 * @brief BATT-MAN 2 CHGIN in USB suspend mode setting.
 * @details Specified setting for device places CHGIN in USB suspend mode selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_USBS_CHGIN_IS_NOT_SUSPENDED              0x00
#define BATTMAN2_USBS_CHGIN_IS_SUSPENDED                  0x01

/**
 * @brief BATT-MAN 2 CHGIN in battery discharge current fullscale current setting.
 * @details Specified setting for device battery discharge current 
 * fullscale current selection of BATT-MAN 2 Click driver.
 */
#define BATTMAN2_IMON_DISCHG_SCALE_8_2_mA                 0x00
#define BATTMAN2_IMON_DISCHG_SCALE_40_5_mA                0x01
#define BATTMAN2_IMON_DISCHG_SCALE_72_3_mA                0x02
#define BATTMAN2_IMON_DISCHG_SCALE_103_4_mA               0x03
#define BATTMAN2_IMON_DISCHG_SCALE_134_1_mA               0x04
#define BATTMAN2_IMON_DISCHG_SCALE_164_1_mA               0x05
#define BATTMAN2_IMON_DISCHG_SCALE_193_7_mA               0x06
#define BATTMAN2_IMON_DISCHG_SCALE_222_7_mA               0x07
#define BATTMAN2_IMON_DISCHG_SCALE_251_2_mA               0x08
#define BATTMAN2_IMON_DISCHG_SCALE_279_3_mA               0x09
#define BATTMAN2_IMON_DISCHG_SCALE_300_mA                 0x0A

/**
 * @brief BATT-MAN 2 analog channel to connect setting.
 * @details Specified setting for device analog channel to connect selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_MUX_SEL_MULTIPLEXER_DISABLED             0x00
#define BATTMAN2_MUX_SEL_CHGIN_VOLTAGE_MONITOR            0x01
#define BATTMAN2_MUX_SEL_CHGIN_CURRENT_MONITOR            0x02
#define BATTMAN2_MUX_SEL_BATT_VOLTAGE_MONITOR             0x03
#define BATTMAN2_MUX_SEL_BATT_CHARGE_CURRENT_MONITOR      0x04
#define BATTMAN2_MUX_SEL_BATT_DISCHARGE_CURRENT_NORMAL    0x05
#define BATTMAN2_MUX_SEL_BATT_DISCHARGE_CURRENT_NULLING   0x06
#define BATTMAN2_MUX_SEL_THM_VOLTAGE_MONITOR              0x07
#define BATTMAN2_MUX_SEL_TBIAS_VOLTAGE_MONITOR            0x08
#define BATTMAN2_MUX_SEL_AGND_VOLTAGE_MONITOR             0x09
#define BATTMAN2_MUX_SEL_SYS_VOLTAGE_MONITOR              0x0A

/**
 * @brief BATT-MAN 2 Operation Mode of SBB0 setting.
 * @details Specified setting for device CHGIN in Operation Mode of selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_OP_MODE_BUCK_AND_BOOST                   0x00
#define BATTMAN2_OP_MODE_BUCK                             0x01

/**
 * @brief BATT-MAN 2 SIMO Buck-Boost Peak Current Limit setting.
 * @details Specified setting for device IMO Buck-Boost Peak Current Limit selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_CURRENT_LIMIT_1000_mA                    0x00
#define BATTMAN2_CURRENT_LIMIT_750_mA                     0x01
#define BATTMAN2_CURRENT_LIMIT_500_mA                     0x02
#define BATTMAN2_CURRENT_LIMIT_333_mA                     0x03

/**
 * @brief BATT-MAN 2 SIMO Buck-Boost Active Discharge Enable setting.
 * @details Specified setting for device IMO Buck-Boost Active Discharge Enable selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_ACTIVE_DISCHARGE_DISABLE                 0x00
#define BATTMAN2_ACTIVE_DISCHARGE_ENABLE                  0x01

/**
 * @brief BATT-MAN 2 SIMO Buck-Boost FPS setting.
 * @details Specified setting for device IMO Buck-Boost FPS selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_ENABLE_CONTROL_FPS_SLOT_0                0x00
#define BATTMAN2_ENABLE_CONTROL_FPS_SLOT_1                0x01
#define BATTMAN2_ENABLE_CONTROL_FPS_SLOT_2                0x02
#define BATTMAN2_ENABLE_CONTROL_FPS_SLOT_3                0x03
#define BATTMAN2_ENABLE_CONTROL_OFF_IRRESPECTIVE_FPS      0x04
#define BATTMAN2_ENABLE_CONTROL_ON_IRRESPECTIVE_FPS       0x06

/**
 * @brief BATT-MAN 2 Buck-Boost interpreted modes setting.
 * @details Specified setting for device CHGIN in Buck-Boost interpreted modes selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_ICHGIN_LIM_95_mA                         0x00
#define BATTMAN2_ICHGIN_LIM_190_mA                        0x01
#define BATTMAN2_ICHGIN_LIM_285_mA                        0x02
#define BATTMAN2_ICHGIN_LIM_380_mA                        0x03
#define BATTMAN2_ICHGIN_LIM_475_mA                        0x04

/**
 * @brief BATT-MAN 2 SIMO Buck-Boost setting.
 * @details Specified setting for device CHGIN in SIMO Buck-Boost selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_DRV_SBB_FAST_TRANSITION_TIME             0x00
#define BATTMAN2_DRV_SBB_TRANSITION_TIME_1                0x01
#define BATTMAN2_DRV_SBB_TRANSITION_TIME_2                0x02
#define BATTMAN2_DRV_SBB_TRANSITION_TIME_3                0x03

/**
 * @brief BATT-MAN 2 SBB Channel selection.
 * @details Specified setting for device SBB Channel selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_SBB_CH_0                                 0x00
#define BATTMAN2_SBB_CH_1                                 0x01
#define BATTMAN2_SBB_CH_2                                 0x02
 
/**
 * @brief BATT-MAN 2 device address setting.
 * @details Specified setting for device slave address selection of
 * BATT-MAN 2 Click driver.
 */
#define BATTMAN2_SET_DEV_ADDR                             0x48

/*! @} */ // battman2_set

/**
 * @defgroup battman2_chrg_status BATT-MAN 2 Charger status
 * @brief Charger status of BATT-MAN 2 Click driver.
 */

/**
 * @addtogroup battman2_chrg_status
 * @{
 */

/**
 * @brief BATT-MAN 2 Charger Details description register.
 * @details Charger Details for description of BATT-MAN 2 Click driver.
 */
#define BATTMAN2_CHG_DTLS_OFF                             0x00
#define BATTMAN2_CHG_DTLS_PREQUALIFICATION_MODE           0x01
#define BATTMAN2_CHG_DTLS_FAST_CHARGE_CONSTANT_CURRENT    0x02 
#define BATTMAN2_CHG_DTLS_JEITA_MODIFIED_FAST_CHRG_CC     0x03
#define BATTMAN2_CHG_DTLS_FAST_CHARGE_CONSTANT_VOLTAGE    0x04
#define BATTMAN2_CHG_DTLS_JEITA_MODIFIED_FAST_CHRG_CV     0x05
#define BATTMAN2_CHG_DTLS_TOP_OFF_MODE                    0x06
#define BATTMAN2_CHG_DTLS_JEITA_MODIFIED_TOP_OFF_MODE     0x07
#define BATTMAN2_CHG_DTLS_DONE                            0x08
#define BATTMAN2_CHG_DTLS_JEITA_MODIFIED_DONE             0x09
#define BATTMAN2_CHG_DTLS_PREQUALIFICATION_TIMER_FAULT    0x0A
#define BATTMAN2_CHG_DTLS_FAST_CHARGE_TIMER_FAULT         0x0B
#define BATTMAN2_CHG_DTLS_BATTERY_TEMPERATURE_FAULT       0x0C

/**
 * @brief BATT-MAN 2 Quick Charger Status register.
 * @details Specified register for Quick Charger Status of BATT-MAN 2 Click driver.
 */
#define BATTMAN2_CHG_NO_CHARGING                          0x00
#define BATTMAN2_CHG_CHARGING                             0x01

/*! @} */ // battman2_chrg_status

/**
 * @defgroup battman2_map BATT-MAN 2 MikroBUS Map
 * @brief MikroBUS pin mapping of BATT-MAN 2 Click driver.
 */

/**
 * @addtogroup battman2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BATT-MAN 2 Click to the selected MikroBUS.
 */
#define BATTMAN2_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // battman2_map
/*! @} */ // battman2

/**
 * @brief BATT-MAN 2 Click context object.
 * @details Context object definition of BATT-MAN 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;      /**< Reset pin.      */

    // Input pins
    digital_in_t  irq;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

} battman2_t;

/**
 * @brief BATT-MAN 2 Click configuration object.
 * @details Configuration object definition of BATT-MAN 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;        /**< Reset pin.      */
    pin_name_t  irq;        /**< Interrupt pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} battman2_cfg_t;

/**
 * @brief BATT-MAN 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BATTMAN2_OK = 0,
   BATTMAN2_ERROR = -1

} battman2_return_value_t;

/**
 * @brief BATT-MAN 2 Click charger configuration object.
 * @details Charger configuration object definition of BATT-MAN 2 Click driver.
 */
typedef struct
{
    uint8_t   thm_hot;
    uint8_t   thm_warm;
    uint8_t   thm_cool;
    uint8_t   thm_cold;
    float     vchgin_min;
    float     ichgin_lim;
    uint8_t   i_pq;
    float     chg_pq;
    uint8_t   i_term;
    uint8_t   t_topoff;
    uint8_t   tj_reg;
    float     vsys_reg;
    float     chg_cc;
    uint8_t   t_fast_chg;
    float     chg_cc_jeita;
    uint8_t   thm_en;
    float     chg_cv;
    uint8_t   usbs;
    float     chg_cv_jeita;
    uint8_t   imon_dischg_scale;
    uint8_t   mux_sel;

} battman2_chg_cnfg_t;

/**
 * @brief BATT-MAN 2 Click charger status object.
 * @details Charger status object definition of BATT-MAN 2 Click driver.
 */
typedef struct
{
    uint8_t   vchgin_min_stat;
    uint8_t   ichgin_lim_stat;
    uint8_t   vsys_min_stat;
    uint8_t   tj_reg_stat;
    uint8_t   thm_dtls;
    uint8_t   chg_dtls;
    uint8_t   chgin_dtls;
    uint8_t   chg;
    uint8_t   time_sus;

} battman2_stat_chg_t;

/**
 * @brief BATT-MAN 2 Click Buck and boost configuration object.
 * @details Buck and boost configuration object definition of BATT-MAN 2 Click driver.
 */
typedef struct
{
    float     output_vtg;
    uint8_t   op_mode;
    uint8_t   current_limit;
    uint8_t   active_discharge_enable;
    uint8_t   enable_control;
    uint8_t   ichgin_lim_def;
    uint8_t   drv_sbb;

} battman2_sbb_cnfg_t;

/**
 * @brief BATT-MAN 2 Click LDO configuration object.
 * @details Linear regulator configuration object definition of BATT-MAN 2 Click driver.
 */
typedef struct
{
    float     output_vtg;
    uint8_t   op_mode;
    uint8_t   current_limit;
    uint8_t   active_discharge_enable;
    uint8_t   enable_control;

} battman2_ldo_cnfg_t;

/*!
 * @addtogroup battman2 BATT-MAN 2 Click Driver
 * @brief API for configuring and manipulating BATT-MAN 2 Click driver.
 * @{
 */

/**
 * @brief BATT-MAN 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #battman2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void battman2_cfg_setup ( battman2_cfg_t *cfg );

/**
 * @brief BATT-MAN 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #battman2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_init ( battman2_t *ctx, battman2_cfg_t *cfg );

/**
 * @brief BATT-MAN 2 default configuration function.
 * @details This function executes a default configuration of BATT-MAN 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t battman2_default_cfg ( battman2_t *ctx );

/**
 * @brief BATT-MAN 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_generic_write ( battman2_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief BATT-MAN 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_generic_read ( battman2_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief BATT-MAN 2 hw reset function.
 * @details This function performs a hardware reset of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_hw_reset ( battman2_t *ctx );

/**
 * @brief BATT-MAN 2 check global interrupts function.
 * @details This function check global interrupts of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[out] int_glbl0 : Global interrupts register 0 data.
 * @param[out] int_glbl1 : Global interrupts register 1 data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_check_int_glbl ( battman2_t *ctx, uint8_t *int_glbl0, uint8_t *int_glbl1 );

/**
 * @brief BATT-MAN 2 check faults occurred function.
 * @details This function check error flags of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[out] faults : Error flags data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_check_faults_occurred ( battman2_t *ctx, uint8_t *faults );

/**
 * @brief BATT-MAN 2 check states function.
 * @details This function check global states of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[out] stat : Global states data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_check_stat ( battman2_t *ctx, uint8_t *stat );


/**
 * @brief BATT-MAN 2 set gpio output state function.
 * @details This function sets desare gpio output state of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO selection:
 *         @li @c 0x00 ( BATTMAN2_SEL_LED_RED    ) - Red LED,
 *         @li @c 0x01 ( BATTMAN2_SEL_LED_YELLOW ) - Yellow LED,
 *         @li @c 0x02 ( BATTMAN2_SEL_LED_BLUE   ) - Blue LED.
 * @param[in] led_state : LED stete selection: 
 *         @li @c 0x00 ( BATTMAN2_PIN_STATE_OFF ) - Turn On LED,
 *         @li @c 0x01 ( BATTMAN2_PIN_STATE_ON  ) - Turn Off LED.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_set_gpio_output ( battman2_t *ctx, uint8_t gpio_sel, uint8_t led_state );

/**
 * @brief BATT-MAN 2 get device ID function.
 * @details This function read device ID data of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[out] cid : Device ID data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_get_id ( battman2_t *ctx, uint8_t *cid );

/**
 * @brief BATT-MAN 2 set charger enable function.
 * @details This function set desired charger work mode of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[in] en_chg : Desired charger work mode:
 *         @li @c 0x00 ( BATTMAN2_SET_CHARGER_DISABLE ) - Disable charging,
 *         @li @c 0x01 ( BATTMAN2_SET_CHARGER_ENABLE  ) - Enable charging.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_set_charger_enable ( battman2_t *ctx, uint8_t en_chg );

/**
 * @brief BATT-MAN 2 set charger configuration function.
 * @details This function set desired configuration of the charger of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[in] chg_cnfg : Charger configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_set_charger_cfg ( battman2_t *ctx, battman2_chg_cnfg_t chg_cnfg );

/**
 * @brief BATT-MAN 2 get charger configuration function.
 * @details This function get charger configuration of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[out] chg_cnfg : Charger configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_get_charger_cfg ( battman2_t *ctx, battman2_chg_cnfg_t *chg_cnfg );

/**
 * @brief BATT-MAN 2 get charger status function.
 * @details This function get charger status of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[out] chg_stat : Charger status object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_get_chg_status ( battman2_t *ctx, battman2_stat_chg_t *chg_stat );

/**
 * @brief BATT-MAN 2 set SBB configuration function.
 * @details This function set desired configuration of the SIMO Buck-Boost of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[in] sbb_sel : Buck and boost channel selection:
 *         @li @c 0x00 ( BATTMAN2_SBB_CH_0 ) - VSB0,
 *         @li @c 0x01 ( BATTMAN2_SBB_CH_1 ) - VSB1,
 *         @li @c 0x02 ( BATTMAN2_SBB_CH_2 ) - VSB1.
 * @param[in] sbb_cfg : Buck and boost configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_set_sbb_config ( battman2_t *ctx, uint8_t sbb_sel, battman2_sbb_cnfg_t sbb_cfg );

/**
 * @brief BATT-MAN 2 get SBB configuration function.
 * @details This function get Buck and Boost configuration of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[in] sbb_sel : Buck and boost channel selection:
 *         @li @c 0x00 ( BATTMAN2_SBB_CH_0 ) - VSB0,
 *         @li @c 0x01 ( BATTMAN2_SBB_CH_1 ) - VSB1,
 *         @li @c 0x02 ( BATTMAN2_SBB_CH_2 ) - VSB1.
 * @param[out] sbb_cfg : Buck and boost configuration object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_get_sbb_config ( battman2_t *ctx, uint8_t sbb_sel, battman2_sbb_cnfg_t *sbb_cfg );

/**
 * @brief BATT-MAN 2 set LDO configuration function.
 * @details This function set desired configuration of the linear regulator of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[in] ldo_cfg : Linear regulator object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_set_ldo_config ( battman2_t *ctx, battman2_ldo_cnfg_t ldo_cfg );

/**
 * @brief BATT-MAN 2 get LDO configuration function.
 * @details This function get linear regulator configuration of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @param[out] ldo_cfg : Linear regulator object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battman2_get_ldo_config ( battman2_t *ctx, battman2_ldo_cnfg_t *ldo_cfg );

/**
 * @brief BATT-MAN 2 check interrupt function.
 * @details This function check state of the interrupt ( IRQ pin ) of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @return @li @c 0 - IRQ pin state low,
 *         @li @c 1 - IRQ pin state high.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t battman2_check_interrupt ( battman2_t *ctx );

/**
 * @brief BATT-MAN 2 LED intro function.
 * @details This function LED indicator test of the 
 * MAX77654 Ultra-Low Power PMIC Featuring SingleInductor, 3-Output Buck-Boost, 
 * 2-LDOs, PowerPath Charger for Small Li+, and Ship Mode on the
 * BATT-MAN 2 click board™.
 * @param[in] ctx : Click context object.
 * See #battman2_t object definition for detailed explanation.
 * @return @li @c 0 - IRQ pin state low,
 *         @li @c 1 - IRQ pin state high.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void battman2_led_intro ( battman2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BATTMAN2_H

/*! @} */ // battman2

// ------------------------------------------------------------------------ END
