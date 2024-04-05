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
 * @file charger17.h
 * @brief This file contains API for Charger 17 Click Driver.
 */

#ifndef CHARGER17_H
#define CHARGER17_H

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
 * @addtogroup charger17 Charger 17 Click Driver
 * @brief API for configuring and manipulating Charger 17 Click driver.
 * @{
 */

/**
 * @defgroup charger17_reg Charger 17 Registers List
 * @brief List of registers of Charger 17 Click driver.
 */

/**
 * @addtogroup charger17_reg
 * @{
 */

/**
 * @brief Charger 17 register list.
 * @details Specified register list of Charger 17 Click driver.
 */
#define CHARGER17_REG_OTG_CONFIG                0x00
#define CHARGER17_REG_TOP                       0x01
#define CHARGER17_REG_FUNCTION                  0x02
#define CHARGER17_REG_IBUS                      0x03
#define CHARGER17_REG_VBUS                      0x04
#define CHARGER17_REG_PRECHG                    0x05
#define CHARGER17_REG_REGU                      0x06
#define CHARGER17_REG_VCHG                      0x07
#define CHARGER17_REG_ICHG                      0x08
#define CHARGER17_REG_CHG_TIMER                 0x09
#define CHARGER17_REG_EOC                       0x0A
#define CHARGER17_REG_INFO                      0x0B
#define CHARGER17_REG_JEITA                     0x0C
#define CHARGER17_REG_PUMP_EXP                  0x0D
#define CHARGER17_REG_DPDM_DET                  0x0E
#define CHARGER17_REG_IC_STATUS                 0x0F
#define CHARGER17_REG_STAT0                     0x10
#define CHARGER17_REG_STAT1                     0x11
#define CHARGER17_REG_STAT2                     0x12
#define CHARGER17_REG_STAT3                     0x13
#define CHARGER17_REG_IRQ0                      0x20
#define CHARGER17_REG_IRQ1                      0x21
#define CHARGER17_REG_IRQ2                      0x22
#define CHARGER17_REG_IRQ3                      0x23
#define CHARGER17_REG_MASK0                     0x30
#define CHARGER17_REG_MASK1                     0x31
#define CHARGER17_REG_MASK2                     0x32
#define CHARGER17_REG_MASK3                     0x33

/*! @} */ // charger17_reg

/**
 * @defgroup charger17_set Charger 17 Registers Settings
 * @brief Settings for registers of Charger 17 Click driver.
 */

/**
 * @addtogroup charger17_set
 * @{
 */

/**
 * @brief Charger 17 OTG config register setting.
 * @details Specified setting for OTG config register of Charger 17 Click driver.
 */
#define CHARGER17_OTG_CV_4p85V                  0x00
#define CHARGER17_OTG_CV_5V                     0x40
#define CHARGER17_OTG_CV_5p15V                  0x80
#define CHARGER17_OTG_CV_5p3V                   0xC0
#define CHARGER17_OTG_CV_MASK                   0xC0
#define CHARGER17_OTG_LBP_2p8V                  0x00
#define CHARGER17_OTG_LBP_2p5V                  0x02
#define CHARGER17_OTG_LBP_MASK                  0x02
#define CHARGER17_OTG_CC_0p5A                   0x00
#define CHARGER17_OTG_CC_1p2A                   0x01
#define CHARGER17_OTG_CC_MASK                   0x01

/**
 * @brief Charger 17 TOP register setting.
 * @details Specified setting for TOP register of Charger 17 Click driver.
 */
#define CHARGER17_TOP_QON_RST_EN                0x80
#define CHARGER17_TOP_STAT_EN                   0x40
#define CHARGER17_TOP_DIS_I2C_TO                0x08
#define CHARGER17_TOP_WDT_CNT_RST               0x04
#define CHARGER17_TOP_WDT_DISABLE               0x00
#define CHARGER17_TOP_WDT_40S                   0x01
#define CHARGER17_TOP_WDT_80S                   0x02
#define CHARGER17_TOP_WDT_160S                  0x03
#define CHARGER17_TOP_WDT_MASK                  0x03

/**
 * @brief Charger 17 FUNCTION register setting.
 * @details Specified setting for FUNCTION register of Charger 17 Click driver.
 */
#define CHARGER17_FUNCTION_BATFET_DIS           0x80
#define CHARGER17_FUNCTION_BATFET_DIS_DLY_12S   0x40
#define CHARGER17_FUNCTION_HZ                   0x20
#define CHARGER17_FUNCTION_BUCK_PFM_DIS         0x08
#define CHARGER17_FUNCTION_UUG_FULLON           0x04
#define CHARGER17_FUNCTION_OTG_EN               0x02
#define CHARGER17_FUNCTION_CHG_EN               0x01

/**
 * @brief Charger 17 IBUS register setting.
 * @details Specified setting for IBUS register of Charger 17 Click driver.
 */
#define CHARGER17_IBUS_AICC_EN                  0x80
#define CHARGER17_IBUS_AUTO_AICR                0x40
#define CHARGER17_IBUS_IAICR(x)                 ( ( uint8_t ) ( x / 50 ) & 0x3F ) // valid values 50mA to 3200mA

/**
 * @brief Charger 17 VBUS register setting.
 * @details Specified setting for VBUS register of Charger 17 Click driver.
 */
#define CHARGER17_VBUS_VAC_OVP_5p8V             0x00
#define CHARGER17_VBUS_VAC_OVP_6p5V             0x40
#define CHARGER17_VBUS_VAC_OVP_10p9V            0x80
#define CHARGER17_VBUS_VAC_OVP_14V              0xC0
#define CHARGER17_VBUS_VAC_OVP_MASK             0xC0
#define CHARGER17_VBUS_VMIVR_BAT_TRACK_4300mV   0x00
#define CHARGER17_VBUS_VMIVR_BAT_TRACK_VBAT_200 0x10
#define CHARGER17_VBUS_VMIVR_BAT_TRACK_VBAT_250 0x20
#define CHARGER17_VBUS_VMIVR_BAT_TRACK_VBAT_350 0x30
#define CHARGER17_VBUS_VMIVR_BAT_TRACK_MASK     0x30
#define CHARGER17_VBUS_VMIVR(x)                 ( ( uint8_t ) ( ( x - 3900 ) / 100 ) & 0x0F ) // valid values 3900mV to 5400mV

/**
 * @brief Charger 17 PRECHG register setting.
 * @details Specified setting for PRECHG register of Charger 17 Click driver.
 */
#define CHARGER17_PRECHG_V(x)                   ( ( ( uint8_t ) ( ( x - 2700 ) / 100 ) & 0x07 ) << 4 ) // valid values 2700mV to 3400mV
#define CHARGER17_PRECHG_I(x)                   ( ( uint8_t ) ( ( x - 50 ) / 50 ) & 0x0F ) // valid values 50mA to 800mA

/**
 * @brief Charger 17 REGU register setting.
 * @details Specified setting for REGU register of Charger 17 Click driver.
 */
#define CHARGER17_REGU_THREG_100_DEGC           0x00
#define CHARGER17_REGU_THREG_120_DEGC           0x40
#define CHARGER17_REGU_THREG_MASK               0x40
#define CHARGER17_REGU_VSYS_MIN(x)              ( ( uint8_t ) ( ( x - 2600 ) / 100 ) & 0x0F ) // valid values 2600mV to 4100mV

/**
 * @brief Charger 17 VCHG register setting.
 * @details Specified setting for VCHG register of Charger 17 Click driver.
 */
#define CHARGER17_VCHG_VPRE_CHG_100mV           0x00
#define CHARGER17_VCHG_VPRE_CHG_200mV           0x80
#define CHARGER17_VCHG_VPRE_CHG_MASK            0x80
#define CHARGER17_VCHG_VBAT_REG(x)              ( ( uint8_t ) ( ( x - 3900 ) / 10 ) & 0x7F ) // valid values 3900mV to 4700mV

/**
 * @brief Charger 17 ICHG register setting.
 * @details Specified setting for ICHG register of Charger 17 Click driver.
 */
#define CHARGER17_ICHG_REG(x)                   ( ( uint8_t ) ( x / 50 ) & 0x3F ) // valid values 0mA to 3150mV

/**
 * @brief Charger 17 CHG timer register setting.
 * @details Specified setting for CHG timer register of Charger 17 Click driver.
 */
#define CHARGER17_CHG_TIMER_CHG_SAFE_TMR_EN     0x80
#define CHARGER17_CHG_TIMER_CHG_SAFE_TMR_2XT    0x40
#define CHARGER17_CHG_TIMER_CHG_SAFE_TMR_5HR    0x00
#define CHARGER17_CHG_TIMER_CHG_SAFE_TMR_10HR   0x10
#define CHARGER17_CHG_TIMER_CHG_SAFE_TMR_15HR   0x20
#define CHARGER17_CHG_TIMER_CHG_SAFE_TMR_20HR   0x30
#define CHARGER17_CHG_TIMER_MASK                0x30

/**
 * @brief Charger 17 EOC register setting.
 * @details Specified setting for EOC register of Charger 17 Click driver.
 */
#define CHARGER17_EOC_IEOC_CHG(x)               ( ( ( uint8_t ) ( ( x - 50 ) / 50 ) & 0x0F ) << 4 ) // valid values 50mA to 800mA
#define CHARGER17_EOC_BG_CHG_TMR_0MIN           0x00
#define CHARGER17_EOC_BG_CHG_TMR_15MIN          0x04
#define CHARGER17_EOC_BG_CHG_TMR_30MIN          0x08
#define CHARGER17_EOC_BG_CHG_TMR_45MIN          0x0C
#define CHARGER17_EOC_BG_CHG_TMR_MASK           0x0C
#define CHARGER17_EOC_TE                        0x02
#define CHARGER17_EOC_RST                       0x01

/**
 * @brief Charger 17 INFO register setting.
 * @details Specified setting for INFO register of Charger 17 Click driver.
 */
#define CHARGER17_INFO_REG_RST                  0x80
#define CHARGER17_INFO_DEVICE_ID                0x68
#define CHARGER17_INFO_DEVICE_ID_MASK           0x78
#define CHARGER17_INFO_DEVICE_RE_MASK           0x07

/**
 * @brief Charger 17 JEITA register setting.
 * @details Specified setting for JEITA register of Charger 17 Click driver.
 */
#define CHARGER17_JEITA_EN                      0x80
#define CHARGER17_JEITA_COLD                    0x40
#define CHARGER17_JEITA_COOL_ISET_50PCT         0x00
#define CHARGER17_JEITA_COOL_ISET_25PCT         0x20
#define CHARGER17_JEITA_COOL_ISET_MASK          0x20
#define CHARGER17_JEITA_COOL_VSET_4p1V          0x00
#define CHARGER17_JEITA_COOL_VSET_VBAT_REG      0x10
#define CHARGER17_JEITA_COOL_VSET_MASK          0x10
#define CHARGER17_JEITA_WARM_ISET_50PCT         0x00
#define CHARGER17_JEITA_WARM_ISET_ICHG_REG      0x08
#define CHARGER17_JEITA_WARM_ISET_MASK          0x08
#define CHARGER17_JEITA_WARM_VSET_4p1V          0x00
#define CHARGER17_JEITA_WARM_VSET_VBAT_REG      0x04
#define CHARGER17_JEITA_WARM_VSET_MASK          0x04
#define CHARGER17_JEITA_HOT                     0x02

/**
 * @brief Charger 17 PUMP exp register setting.
 * @details Specified setting for PUMP exp register of Charger 17 Click driver.
 */
#define CHARGER17_PUMP_EXP_PE_EN                0x80
#define CHARGER17_PUMP_EXP_PE_SEL_PE10          0x00
#define CHARGER17_PUMP_EXP_PE_SEL_PE20          0x40
#define CHARGER17_PUMP_EXP_PE_SEL_MASK          0x40
#define CHARGER17_PUMP_EXP_PE10_INC_VDOWN       0x00
#define CHARGER17_PUMP_EXP_PE10_INC_VUP         0x20
#define CHARGER17_PUMP_EXP_PE10_INC_MASK        0x20
#define CHARGER17_PUMP_EXP_PE_EN                0x80
#define CHARGER17_PUMP_EXP_PE_EN                0x80
#define CHARGER17_PUMP_EXP_PE20_CODE(x)         ( ( uint8_t ) ( ( ( float ) x - 5.5 ) / 0.5 ) & 0x1F ) // valid values 5.5V to 20V
#define CHARGER17_PUMP_EXP_PE20_CODE_SELF_TEST  0x1E
#define CHARGER17_PUMP_EXP_PE20_CODE_DIS_DROP   0x1F

/**
 * @brief Charger 17 DPDM det register setting.
 * @details Specified setting for DPDM det register of Charger 17 Click driver.
 */
#define CHARGER17_DPDM_DET_BC12_EN              0x80
#define CHARGER17_DPDM_DET_DCDT_SEL_DIS         0x00
#define CHARGER17_DPDM_DET_DCDT_SEL_300mS       0x20
#define CHARGER17_DPDM_DET_DCDT_SEL_600mS       0x40
#define CHARGER17_DPDM_DET_DCDT_SEL_WAIT_DATA   0x60
#define CHARGER17_DPDM_DET_DCDT_SEL_MASK        0x60
#define CHARGER17_DPDM_DET_SPEC_TA_EN           0x10
#define CHARGER17_DPDM_DET_DCP_DP_OPT           0x01

/**
 * @brief Charger 17 IC status register setting.
 * @details Specified setting for IC status register of Charger 17 Click driver.
 */
#define CHARGER17_PORT_STAT_VBUS_DEV_1          0x80
#define CHARGER17_PORT_STAT_VBUS_DEV_2          0x90
#define CHARGER17_PORT_STAT_VBUS_DEV_3          0xA0
#define CHARGER17_PORT_STAT_VBUS_DEV_4          0xB0
#define CHARGER17_PORT_STAT_VBUS_UNKNOWN        0xC0
#define CHARGER17_PORT_STAT_VBUS_SDP            0xD0
#define CHARGER17_PORT_STAT_VBUS_CDP            0xE0
#define CHARGER17_PORT_STAT_VBUS_DCP            0xF0
#define CHARGER17_PORT_STAT_BIT_MASK            0xF0
#define CHARGER17_IC_STAT_HZ_SLEEP              0x00
#define CHARGER17_IC_STAT_VBUS_READY            0x01
#define CHARGER17_IC_STAT_TRICKLE_CHG           0x02
#define CHARGER17_IC_STAT_PRE_CHG               0x03
#define CHARGER17_IC_STAT_FAST_CHG              0x04
#define CHARGER17_IC_STAT_IEOC_CHG              0x05
#define CHARGER17_IC_STAT_BACK_GROUND_CHG       0x06
#define CHARGER17_IC_STAT_CHG_DONE              0x07
#define CHARGER17_IC_STAT_CHG_FAULT             0x08
#define CHARGER17_IC_STAT_OTG                   0x0F
#define CHARGER17_IC_STAT_BIT_MASK              0x0F

/**
 * @brief Charger 17 status 0 register setting.
 * @details Specified setting for status 0 register of Charger 17 Click driver.
 */
#define CHARGER17_STAT0_VBUS_GD                 0x80
#define CHARGER17_STAT0_CHG_RDY                 0x40
#define CHARGER17_STAT0_IEOC                    0x20
#define CHARGER17_STAT0_BG_CHG                  0x10
#define CHARGER17_STAT0_CHG_DONE                0x08
#define CHARGER17_STAT0_BC12_DONE               0x01

/**
 * @brief Charger 17 status 1 register setting.
 * @details Specified setting for status 1 register of Charger 17 Click driver.
 */
#define CHARGER17_STAT1_CHG_MIVR                0x80
#define CHARGER17_STAT1_CHG_AICR                0x40
#define CHARGER17_STAT1_CHG_THREG               0x20
#define CHARGER17_STAT1_CHG_BUSUV               0x10
#define CHARGER17_STAT1_CHG_TOUT                0x08
#define CHARGER17_STAT1_CHG_SYSOV               0x04
#define CHARGER17_STAT1_CHG_BATOV               0x02

/**
 * @brief Charger 17 status 2 register setting.
 * @details Specified setting for status 2 register of Charger 17 Click driver.
 */
#define CHARGER17_STAT2_JEITA_HOT               0x80
#define CHARGER17_STAT2_JEITA_WARM              0x40
#define CHARGER17_STAT2_JEITA_COOL              0x20
#define CHARGER17_STAT2_JEITA_COLD              0x10
#define CHARGER17_STAT2_SYS_MIN                 0x02

/**
 * @brief Charger 17 status 3 register setting.
 * @details Specified setting for status 3 register of Charger 17 Click driver.
 */
#define CHARGER17_STAT3_OTP                     0x80
#define CHARGER17_STAT3_VAC_OV                  0x40
#define CHARGER17_STAT3_WDT                     0x20
#define CHARGER17_STAT3_OTG_CC                  0x04

/**
 * @brief Charger 17 device address setting.
 * @details Specified setting for device slave address selection of
 * Charger 17 Click driver.
 */
#define CHARGER17_DEVICE_ADDRESS                0x53

/*! @} */ // charger17_set

/**
 * @defgroup charger17_map Charger 17 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 17 Click driver.
 */

/**
 * @addtogroup charger17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 17 Click to the selected MikroBUS.
 */
#define CHARGER17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ce = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.qon = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.psel = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger17_map
/*! @} */ // charger17

/**
 * @brief Charger 17 Click context object.
 * @details Context object definition of Charger 17 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ce;           /**< Charge enable pin (Active low). */
    digital_out_t qon;          /**< BATFET (Q4) enable control pin. */
    digital_out_t psel;         /**< Power source selection pin. */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} charger17_t;

/**
 * @brief Charger 17 Click configuration object.
 * @details Configuration object definition of Charger 17 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t ce;              /**< Charge enable pin (Active low). */
    pin_name_t qon;             /**< BATFET (Q4) enable control pin. */
    pin_name_t psel;            /**< Power source selection pin. */
    pin_name_t int_pin;         /**< Interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} charger17_cfg_t;

/**
 * @brief Charger 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER17_OK = 0,
    CHARGER17_ERROR = -1

} charger17_return_value_t;

/*!
 * @addtogroup charger17 Charger 17 Click Driver
 * @brief API for configuring and manipulating Charger 17 Click driver.
 * @{
 */

/**
 * @brief Charger 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger17_cfg_setup ( charger17_cfg_t *cfg );

/**
 * @brief Charger 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger17_init ( charger17_t *ctx, charger17_cfg_t *cfg );

/**
 * @brief Charger 17 default configuration function.
 * @details This function executes a default configuration of Charger 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t charger17_default_cfg ( charger17_t *ctx );

/**
 * @brief Charger 17 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger17_generic_write ( charger17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Charger 17 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger17_generic_read ( charger17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Charger 17 write register function.
 * @details This function writes a data bytes to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger17_write_register ( charger17_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Charger 17 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger17_read_register ( charger17_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Charger 17 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger17_check_communication ( charger17_t *ctx );

/**
 * @brief Charger 17 set qon pin function.
 * @details This function sets the QON pin logic state.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void charger17_set_qon_pin ( charger17_t *ctx, uint8_t state );

/**
 * @brief Charger 17 enable charging function.
 * @details This function enables charging by setting the CE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger17_enable_charging ( charger17_t *ctx );

/**
 * @brief Charger 17 disable charging function.
 * @details This function disables charging by setting the CE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger17_disable_charging ( charger17_t *ctx );

/**
 * @brief Charger 17 set psel 500mA function.
 * @details This function sets charging current to 500mA by setting the PSEL pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger17_set_psel_500mA ( charger17_t *ctx );

/**
 * @brief Charger 17 set psel 2400mA function.
 * @details This function sets charging current to 2400mA by setting the PSEL pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger17_set_psel_2400mA ( charger17_t *ctx );

/**
 * @brief Charger 17 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #charger17_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t charger17_get_int_pin ( charger17_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CHARGER17_H

/*! @} */ // charger17

// ------------------------------------------------------------------------ END
