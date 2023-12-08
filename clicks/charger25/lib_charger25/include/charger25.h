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
 * @file charger25.h
 * @brief This file contains API for Charger 25 Click Driver.
 */

#ifndef CHARGER25_H
#define CHARGER25_H

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
 * @addtogroup charger25 Charger 25 Click Driver
 * @brief API for configuring and manipulating Charger 25 Click driver.
 * @{
 */

/**
 * @defgroup charger25_reg Charger 25 Registers List
 * @brief List of registers of Charger 25 Click driver.
 */

/**
 * @addtogroup charger25_reg
 * @{
 */

/**
 * @brief Charger 25 description register.
 * @details Specified register for description of Charger 25 Click driver.
 */
#define CHARGER25_REG_MINIMAL_SYSTEM_VOLTAGE     0x00
#define CHARGER25_REG_CHARGE_VOLTAGE_LIMIT       0x01
#define CHARGER25_REG_CHARGE_CURRENT_LIMIT       0x03
#define CHARGER25_REG_INPUT_VOLTAGE_LIMIT        0x05
#define CHARGER25_REG_INPUT_CURRENT_LIMIT        0x06
#define CHARGER25_REG_PRECHARGE_CONTROL          0x08
#define CHARGER25_REG_TERMINATION_CONTROL        0x09
#define CHARGER25_REG_RECHARGE_CONTROL           0x0A
#define CHARGER25_REG_VOTG_REGULATION            0x0B
#define CHARGER25_REG_IOTG_REGULATION            0x0D
#define CHARGER25_REG_TIMER_CONTROL              0x0E
#define CHARGER25_REG_CHARGER_CONTROL_0          0x0F
#define CHARGER25_REG_CHARGER_CONTROL_1          0x10
#define CHARGER25_REG_CHARGER_CONTROL_2          0x11
#define CHARGER25_REG_CHARGER_CONTROL_3          0x12
#define CHARGER25_REG_CHARGER_CONTROL_4          0x13
#define CHARGER25_REG_CHARGER_CONTROL_5          0x14
#define CHARGER25_REG_RESERVED                   0x15
#define CHARGER25_REG_TEMPERATURE_CONTROL        0x16
#define CHARGER25_REG_NTC_CONTROL_0              0x17
#define CHARGER25_REG_NTC_CONTROL_1              0x18
#define CHARGER25_REG_ICO_CURRENT_LIMIT          0x19
#define CHARGER25_REG_CHARGER_STATUS_0           0x1B
#define CHARGER25_REG_CHARGER_STATUS_1           0x1C
#define CHARGER25_REG_CHARGER_STATUS_2           0x1D
#define CHARGER25_REG_CHARGER_STATUS_3           0x1E
#define CHARGER25_REG_CHARGER_STATUS_4           0x1F
#define CHARGER25_REG_FAULT_STATUS_0             0x20
#define CHARGER25_REG_FAULT_STATUS_1             0x21
#define CHARGER25_REG_CHARGER_FLAG_0             0x22
#define CHARGER25_REG_CHARGER_FLAG_1             0x23
#define CHARGER25_REG_CHARGER_FLAG_2             0x24
#define CHARGER25_REG_CHARGER_FLAG_3             0x25
#define CHARGER25_REG_FAULT_FLAG_0               0x26
#define CHARGER25_REG_FAULT_FLAG_1               0x27
#define CHARGER25_REG_CHARGER_MASK_0             0x28
#define CHARGER25_REG_CHARGER_MASK_1             0x29
#define CHARGER25_REG_CHARGER_MASK_2             0x2A
#define CHARGER25_REG_CHARGER_MASK_3             0x2B
#define CHARGER25_REG_FAULT_MASK_0               0x2C
#define CHARGER25_REG_FAULT_MASK_1               0x2D
#define CHARGER25_REG_ADC_CONTROL                0x2E
#define CHARGER25_REG_ADC_FUNCTION_DISABLE_0     0x2F
#define CHARGER25_REG_ADC_FUNCTION_DISABLE_1     0x30
#define CHARGER25_REG_IBUS_ADC                   0x31
#define CHARGER25_REG_IBAT_ADC                   0x33
#define CHARGER25_REG_VBUS_ADC                   0x35
#define CHARGER25_REG_VAC1_ADC                   0x37
#define CHARGER25_REG_VAC2_ADC                   0x39
#define CHARGER25_REG_VBAT_ADC                   0x3B
#define CHARGER25_REG_VSYS_ADC                   0x3D
#define CHARGER25_REG_TS_ADC                     0x3F
#define CHARGER25_REG_TDIE_ADC                   0x41
#define CHARGER25_REG_D_P_ADC                    0x43
#define CHARGER25_REG_D_M_ADC                    0x45
#define CHARGER25_REG_DPDM_DRIVER                0x47
#define CHARGER25_REG_PART_INFORMATION           0x48

/*! @} */ // charger25_reg

/**
 * @defgroup charger25_set Charger 25 Registers Settings
 * @brief Settings for registers of Charger 25 Click driver.
 */

/**
 * @addtogroup charger25_set
 * @{
 */

/**
 * @brief Charger 25 software reset data.
 * @details Specified software reset of Charger 25 Click driver.
 */
#define CHARGER25_SOFT_RESET                     0x40

/**
 * @brief Charger 25 software reset data.
 * @details Specified software reset data of Charger 25 Click driver.
 */
#define CHARGER25_VSYS_MIN_BIT_MASK              0x3F
#define CHARGER25_VSYS_MIN_STEP_SIZE             250
#define CHARGER25_VSYS_MIN_FIXED_OFFSET          2500

/**
 * @brief Charger 25 minimal system voltage and battery cell count data.
 * @details Specified minimal system voltage and battery cell count data of Charger 25 Click driver.
 */
#define CHARGER25_VTG_LIM_MSB_BIT_MASK           0x07
#define CHARGER25_VTG_CONV_V_MV                  10
#define CHARGER25_VTG_CELL_COUNT_DIV             3
#define CHARGER25_VTG_CELL_SEL_1                 1
#define CHARGER25_VTG_CELL_SEL_2                 2
#define CHARGER25_VTG_CELL_SEL_3                 3
#define CHARGER25_VTG_CELL_SEL_4                 4
#define CHARGER25_VTG_CELL_COUNT_MIN             1
#define CHARGER25_VTG_CELL_COUNT_MAX             4
#define CHARGER25_VTG_CELL_COUNT_MUL             7

/**
 * @brief Charger 25 minimal system voltage and battery cell count data.
 * @details Specified minimal system voltage and battery cell count data of Charger 25 Click driver.
 */
#define CHARGER25_CURR_LIM_MSB_BIT_MASK          0x01
#define CHARGER25_CURR_CONV_A_MA                 10

/**
 * @brief Charger 25 input voltage convertor data.
 * @details Specified input voltage convertor data of Charger 25 Click driver.
 */
#define CHARGER25_INPUT_VTG_CONV_V_MV            100

/**
 * @brief Charger 25 ADC function and control data.
 * @details Specified ADC function and control data of Charger 25 Click driver.
 */
#define CHARGER25_SET_ADC_FUNC_ENABLE            0x00
#define CHARGER25_SET_ADC_FUNC_DISABLE           0x01
#define CHARGER25_SET_ADC_CTRL_DISABLE           0x00
#define CHARGER25_SET_ADC_CTRL_ENABLE            0x01

/**
 * @brief Charger 25 ADC conversion rate control and sample speed data.
 * @details Specified ADC conversion rate control and sample speed data of Charger 25 Click driver.
 */
#define CHARGER25_SET_ADC_RATE_CONT_CNV          0x00
#define CHARGER25_SET_ADC_ONES_HOT_CNV           0x01
#define CHARGER25_SET_ADC_SAMPLE_15_BIT          0x00
#define CHARGER25_SET_ADC_SAMPLE_14_BIT          0x01
#define CHARGER25_SET_ADC_SAMPLE_13_BIT          0x02
#define CHARGER25_SET_ADC_SAMPLE_12_BIT          0x03

/**
 * @brief Charger 25 ADC average initial value control data.
 * @details Specified ADC average initial value control data of Charger 25 Click driver.
 */
#define CHARGER25_SET_ADC_AVG_SINGLE_VAL         0x00
#define CHARGER25_SET_ADC_AVG_RUN_AVG            0x01
#define CHARGER25_SET_ADC_AVG_INIT_EXI_VAL       0x00
#define CHARGER25_SET_ADC_AVG_INIT_ADC_CNV       0x01

/**
 * @brief Charger 25 charge status data.
 * @details Specified charge status of Charger 25 Click driver.
 */
#define CHARGER25_CH_STAT_NOT_CHARGING           0x00
#define CHARGER25_CH_STAT_TRICKLE_CHARGE         0x01
#define CHARGER25_CH_STAT_PRE_CHARGE             0x02
#define CHARGER25_CH_STAT_FAST_CHARGE            0x03
#define CHARGER25_CH_STAT_TAPER_CHARGE           0x04
#define CHARGER25_CH_STAT_TIMER_ACT_CHARGING     0x06
#define CHARGER25_CH_STAT_CHARGE_TERMIN_DONE     0x07

/**
 * @brief Charger 25 I/O pins state data.
 * @details Specified I/O pins state data of Charger 25 Click driver.
 */
#define CHARGER25_STATE_PIN_QON_LOW              0x00
#define CHARGER25_STATE_PIN_QON_HIGH             0x01

/**
 * @brief Charger 25 device address setting.
 * @details Specified setting for device slave address selection of
 * Charger 25 Click driver.
 */
#define CHARGER25_DEVICE_ADDRESS                 0x6B

/*! @} */ // charger25_set

/**
 * @defgroup charger25_map Charger 25 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 25 Click driver.
 */

/**
 * @addtogroup charger25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 25 Click to the selected MikroBUS.
 */
#define CHARGER25_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.qon = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.ce = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger25_map
/*! @} */ // charger25

/**
 * @brief Charger 25 Click context object.
 * @details Context object definition of Charger 25 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t qon;        /**< Ship FET Enable or System Power Reset Control Input. */
    digital_out_t ce;         /**< Charge Enable Pin. */

    // Input pins
    digital_in_t int_pin;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} charger25_t;

/**
 * @brief Charger 25 Click configuration object.
 * @details Configuration object definition of Charger 25 Click driver.
 */
typedef struct
{
    pin_name_t scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t qon;            /**< Ship FET Enable or System Power Reset Control Input. */
    pin_name_t ce;             /**< Charge Enable Pin. */
    pin_name_t int_pin;        /**< Interrupt pin. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} charger25_cfg_t;

/**
 * @brief Charger 25 Click status object.
 * @details Status object definition of Charger 25 Click driver.
 */
typedef struct
{
    uint8_t iindpm_stat;          /**< IINDPM status (forward mode) or IOTG status (OTG mode). */
    uint8_t vindpm_stat;          /**< VINDPM status (forward mode) or VOTG status (OTG mode). */
    uint8_t wd_stat;              /**< I2C watch dog timer status. */
    uint8_t poorsrc_stat;         /**< Poor source detection status. */
    uint8_t pg_stat;              /**< Power Good Status. */
    uint8_t ac2_present_stat;     /**< VAC2 insert status. */
    uint8_t ac1_present_stat;     /**< VAC1 insert status. */
    uint8_t vbus_present_stat;    /**< VBUS present status. */
    uint8_t chg_stat;             /**< Charge Status. */
    uint8_t vbus_stat;            /**< VBUS status. */
    uint8_t bc1_2_done;           /**< BC1.2 status. */
    uint8_t ico_stat;             /**< Input Current Optimizer (ICO) status. */
    uint8_t treg_stat;            /**< IC thermal regulation status. */
    uint8_t dpdm_stat;            /**< D+/D- detection status. */
    uint8_t vbat_present_stat;    /**< Battery present status (VBAT > VBAT_UVLOZ). */
    uint8_t acrb2_stat;           /**< The ACFET2-RBFET2 status. */
    uint8_t acrb1_stat;           /**< The ACFET1-RBFET1 status. */
    uint8_t adc_done_stat;        /**< ADC Conversion Status (in one-shot mode only). */
    uint8_t vsys_stat;            /**< VSYS Regulation Status (forward mode). */
    uint8_t chg_tmr_stat;         /**< Fast charge timer status. */
    uint8_t trichg_tmr_stat;      /**< Trickle charge timer status. */
    uint8_t prechg_tmr_stat;      /**< Pre-charge timer status. */
    uint8_t vbatotg_low_stat;     /**< Battery voltage is too low to enable OTG mode. */
    uint8_t ts_cold_stat;         /**< TS temperature is in the cold range. */
    uint8_t ts_cool_stat;         /**< TS temperature is in the cool range. */
    uint8_t ts_warm_stat;         /**< TS temperature is in the warm range. */
    uint8_t ts_hot_stat;          /**< TS temperature is in the hot range. */

} charger25_status_t;

/**
 * @brief Charger 25 Click ADC control object.
 * @details ADC control object definition of Charger 25 Click driver.
 */
typedef struct
{
    uint8_t adc_en;          /**< ADC Control. */
    uint8_t adc_rate;        /**< ADC conversion rate control. */
    uint8_t adc_sample;      /**< ADC sample speed. */
    uint8_t adc_avg;         /**< ADC average control. */
    uint8_t adc_avg_init;    /**< ADC average initial value control. */    

} charger25_adc_ctrl_t;

/**
 * @brief Charger 25 Click ADC function object.
 * @details ADC function object definition of Charger 25 Click driver.
 */
typedef struct
{
    uint8_t ibus_adc_dis;    /**< IBUS ADC control. */
    uint8_t ibat_adc_dis;    /**< IBAT ADC control. */
    uint8_t vbus_adc_dis;    /**< VBUS ADC control. */
    uint8_t vbat_adc_dis;    /**< VBAT ADC control. */
    uint8_t vsys_adc_dis;    /**< VSYS ADC control. */ 
    uint8_t ts_adc_dis;      /**< TS ADC contro. */ 
    uint8_t tdie_adc_dis;    /**< TDIE ADC control. */
    uint8_t dp_adc_dis;      /**< D+ ADC Control. */
    uint8_t dm_adc_dis;      /**< D- ADC Control. */
    uint8_t vac2_adc_dis;    /**< VAC2 ADC Control. */
    uint8_t vac1_adc_dis;    /**< VAC1 ADC Control. */

} charger25_adc_func_t;

/**
 * @brief Charger 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER25_OK = 0,
    CHARGER25_ERROR = -1

} charger25_return_value_t;



/*!
 * @addtogroup charger25 Charger 25 Click Driver
 * @brief API for configuring and manipulating Charger 25 Click driver.
 * @{
 */

/**
 * @brief Charger 25 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger25_cfg_setup ( charger25_cfg_t *cfg );

/**
 * @brief Charger 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_init ( charger25_t *ctx, charger25_cfg_t *cfg );

/**
 * @brief Charger 25 default configuration function.
 * @details This function executes a default configuration of Charger 25
 * click board.
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t charger25_default_cfg ( charger25_t *ctx );

/**
 * @brief Charger 25 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_generic_write ( charger25_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Charger 25 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_generic_read ( charger25_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Charger 25 set QON pin state function.
 * @details This function sets the state of the ship fet enable 
 * or system power reset control input [QON] pin
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[in] state :QON pin state.
 * @return Nothing.
 * @note None.
 */
void charger25_set_qon_pin ( charger25_t *ctx, uint8_t state );

/**
 * @brief Charger 25 charge enable function.
 * @details This function enable charging by sets the state of the EN pin low
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void charger25_enable ( charger25_t *ctx );

/**
 * @brief Charger 25 charge disable function.
 * @details This function disable charging by sets the state of the EN pin high
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void charger25_disable ( charger25_t *ctx );

/**
 * @brief Charger 25 get interrupt function.
 * @details This function get states of the Interrupt [INT] pin
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t charger25_get_interrupt ( charger25_t *ctx );

/**
 * @brief Charger 25 software reset function.
 * @details This function is used to software reset
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_sw_reset ( charger25_t *ctx );

/**
 * @brief Charger 25 get VBAT function.
 * @details This function gets the battery remote sensing voltage ADC reading
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[out] vbat : Battery remote sensing voltage [0-20000mV]
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_get_vbat ( charger25_t *ctx, uint16_t *vbat );

/**
 * @brief Charger 25 get VSYS function.
 * @details This function gets the minimal system voltage
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[out] vsys_min : Minimal system voltage [2500-16000mV]
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_get_vsys_min ( charger25_t *ctx, uint16_t *vsys_min );

/**
 * @brief Charger 25 set ADC control function.
 * @details This function configure ADC control
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[in] adc_ctrl : ADC control object.
 * See #charger25_adc_ctrl_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_set_adc_control ( charger25_t *ctx, charger25_adc_ctrl_t adc_ctrl );

/**
 * @brief Charger 25 set ADC function function.
 * @details This function configure ADC function
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[in] adc_func : ADC function object.
 * See #charger25_adc_func_t definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_set_adc_function ( charger25_t *ctx, charger25_adc_func_t adc_func );

/**
 * @brief Charger 25 get battery voltage limit function.
 * @details This function gets the battery voltage limit
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[out] vtg_lim : Battery voltage limit [3000-18800mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_get_vbat_lim ( charger25_t *ctx, uint16_t *vtg_lim );

/**
 * @brief Charger 25 set battery voltage limit function.
 * @details This function set the battery voltage limit
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[in] vtg_lim : Battery voltage limit [3000-18800mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Default power-on battery voltage regulation limit:
 *         @li 1s: 4.2V,
 *         @li 2s: 8.4V,
 *         @li 3s: 12.6V,
 *         @li 4s: 16.8V.
 */
err_t charger25_set_vbat_lim ( charger25_t *ctx, uint16_t vtg_lim );

/**
 * @brief Charger 25 get battery cell count function.
 * @details This function gets the battery cell count
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[out] cell_count : Battery cell count.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Default power on VSYSMIN list below:
 *         @li 1s: 3.5V,
 *         @li 2s: 7V,
 *         @li 3s: 9V,
 *         @li 4s: 12V.
 */
err_t charger25_get_cell_count ( charger25_t *ctx, uint8_t *cell_count );

/**
 * @brief Charger 25 set battery cell count function.
 * @details This function set the battery cell count
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[in] cell_count : Battery cell count [1-4].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Default power on VSYSMIN list below:
 *         @li 1s: 3.5V,
 *         @li 2s: 7V,
 *         @li 3s: 9V,
 *         @li 4s: 12V.
 */
err_t charger25_set_cell_count ( charger25_t *ctx, uint8_t cell_count );

/**
 * @brief Charger 25 get charge current limit function.
 * @details This function gets the charge current limit
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[out] current_lim : Charge current limit [50mA-5000mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_get_current_limit ( charger25_t *ctx, uint16_t *current_lim );

/**
 * @brief Charger 25 set charge current limit function.
 * @details This function set the charge current limit
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[in] current_lim : Charge current limit [50mA-5000mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_set_current_limit ( charger25_t *ctx, uint16_t current_lim );

/**
 * @brief Charger 25 get input voltage limit function.
 * @details This function gets the absolute VINDPM threshold
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[out] input_vtg_limit : Input voltage limit [3600mV-22000mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_get_input_vtg_limit ( charger25_t *ctx, uint16_t *input_vtg_limit );

/**
 * @brief Charger 25 set input voltage limit function.
 * @details This function set the absolute VINDPM threshold
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[in] input_vtg_limit : Input voltage limit [3600mV-22000mV].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_set_input_vtg_limit ( charger25_t *ctx, uint16_t input_vtg_limit );

/**
 * @brief Charger 25 get input current limit function.
 * @details This function gets the input current limi
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[out] input_curr_limit : Input current limit [100mA-3300mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_get_input_curr_limit ( charger25_t *ctx, uint16_t *input_curr_limit );

/**
 * @brief Charger 25 set input current limit function.
 * @details This function set the input current limi
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[in] input_curr_limit : Input current limit [100mA-3300mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_set_input_curr_limit ( charger25_t *ctx, uint16_t input_curr_limit );

/**
 * @brief Charger 25 get charging status function.
 * @details This function gets charging status
 * of the BQ25792 I2C Controlled, 1-4 Cell, 5-A Buck-Boost Battery Charger 
 * with Dual-Input Selector and USB PD 3.0 OTG Output
 * on the Charger 25 click board™. 
 * @param[in] ctx : Click context object.
 * See #charger25_t object definition for detailed explanation.
 * @param[out] status : Charger status.
 * See #charger25_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger25_get_status ( charger25_t *ctx, charger25_status_t *status );

#ifdef __cplusplus
}
#endif
#endif // CHARGER25_H

/*! @} */ // charger25

// ------------------------------------------------------------------------ END
