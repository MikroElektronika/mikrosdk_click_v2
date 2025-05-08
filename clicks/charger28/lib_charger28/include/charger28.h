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
 * @file charger28.h
 * @brief This file contains API for Charger 28 Click Driver.
 */

#ifndef CHARGER28_H
#define CHARGER28_H

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
 * @addtogroup charger28 Charger 28 Click Driver
 * @brief API for configuring and manipulating Charger 28 Click driver.
 * @{
 */

/**
 * @defgroup charger28_reg Charger 28 Registers List
 * @brief List of registers of Charger 28 Click driver.
 */

/**
 * @addtogroup charger28_reg
 * @{
 */

/**
 * @brief Charger 28 register list.
 * @details Specified register list of Charger 28 Click driver.
 */
#define CHARGER28_REG_CHARGE_CURRENT_LIMIT                  0x02
#define CHARGER28_REG_CHARGE_VOLTAGE_LIMIT                  0x04
#define CHARGER28_REG_INPUT_CURRENT_LIMIT                   0x06
#define CHARGER28_REG_INPUT_VOLTAGE_LIMIT                   0x08
#define CHARGER28_REG_IOTG_REGULATION                       0x0A
#define CHARGER28_REG_VOTG_REGULATION                       0x0C
#define CHARGER28_REG_MINIMAL_SYSTEM_VOLTAGE                0x0E
#define CHARGER28_REG_PRECHARGE_CONTROL                     0x10
#define CHARGER28_REG_TERMINATION_CONTROL                   0x12
#define CHARGER28_REG_CHARGE_TIMER_CONTROL                  0x14
#define CHARGER28_REG_CHARGER_CONTROL_0                     0x15
#define CHARGER28_REG_CHARGER_CONTROL_1                     0x16
#define CHARGER28_REG_CHARGER_CONTROL_2                     0x17
#define CHARGER28_REG_CHARGER_CONTROL_3                     0x18
#define CHARGER28_REG_CHARGER_CONTROL_4                     0x19
#define CHARGER28_REG_CHARGER_CONTROL_5                     0x1A
#define CHARGER28_REG_NTC_CONTROL_0                         0x1C
#define CHARGER28_REG_NTC_CONTROL_1                         0x1D
#define CHARGER28_REG_NTC_CONTROL_2                         0x1E
#define CHARGER28_REG_NTC_CONTROL_3                         0x1F
#define CHARGER28_REG_CHARGER_STATUS_0                      0x20
#define CHARGER28_REG_CHARGER_STATUS_1                      0x21
#define CHARGER28_REG_FAULT_STATUS                          0x22
#define CHARGER28_REG_CHARGER_FLAG_0                        0x23
#define CHARGER28_REG_CHARGER_FLAG_1                        0x24
#define CHARGER28_REG_FAULT_FLAG                            0x25
#define CHARGER28_REG_CHARGER_MASK_0                        0x26
#define CHARGER28_REG_CHARGER_MASK_1                        0x27
#define CHARGER28_REG_FAULT_MASK                            0x28
#define CHARGER28_REG_ICO_CURRENT_LIMIT                     0x29
#define CHARGER28_REG_ADC_CONTROL                           0x2B
#define CHARGER28_REG_ADC_CHANNEL_DISABLE                   0x2C
#define CHARGER28_REG_IBUS_ADC                              0x2D
#define CHARGER28_REG_IBAT_ADC                              0x2F
#define CHARGER28_REG_VBUS_ADC                              0x31
#define CHARGER28_REG_VPMID_ADC                             0x33
#define CHARGER28_REG_VBAT_ADC                              0x35
#define CHARGER28_REG_VSYS_ADC                              0x37
#define CHARGER28_REG_TS_ADC                                0x39
#define CHARGER28_REG_TDIE_ADC                              0x3B
#define CHARGER28_REG_ADCIN_ADC                             0x3D
#define CHARGER28_REG_PART_INFORMATION                      0x3F
#define CHARGER28_REG_VIRTUAL_CONTROL_0                     0x80
#define CHARGER28_REG_VIRTUAL_CONTROL_1                     0x81

/*! @} */ // charger28_reg

/**
 * @defgroup charger28_set Charger 28 Registers Settings
 * @brief Settings for registers of Charger 28 Click driver.
 */

/**
 * @addtogroup charger28_set
 * @{
 */

/**
 * @brief Charger 28 charger control 1 register setting.
 * @details Specified setting for charger control 1 register of Charger 28 Click driver.
 */
#define CHARGER28_CHARGER_CONTROL_1_EN_AUTO_IBAT_DSCHG_DIS  0x00
#define CHARGER28_CHARGER_CONTROL_1_EN_AUTO_IBAT_DSCHG_EN   0x80
#define CHARGER28_CHARGER_CONTROL_1_EN_AUTO_IBAT_DSCHG_MASK 0x80
#define CHARGER28_CHARGER_CONTROL_1_FORCE_IBAT_DSCHG_DIS    0x00
#define CHARGER28_CHARGER_CONTROL_1_FORCE_IBAT_DSCHG_EN     0x40
#define CHARGER28_CHARGER_CONTROL_1_FORCE_IBAT_DSCHG_MASK   0x40
#define CHARGER28_CHARGER_CONTROL_1_EN_CHG_DIS              0x00
#define CHARGER28_CHARGER_CONTROL_1_EN_CHG_EN               0x20
#define CHARGER28_CHARGER_CONTROL_1_EN_CHG_MASK             0x20
#define CHARGER28_CHARGER_CONTROL_1_EN_HIZ_DIS              0x00
#define CHARGER28_CHARGER_CONTROL_1_EN_HIZ_EN               0x10
#define CHARGER28_CHARGER_CONTROL_1_EN_HIZ_MASK             0x10
#define CHARGER28_CHARGER_CONTROL_1_FORCE_PMID_DSCHG_DIS    0x00
#define CHARGER28_CHARGER_CONTROL_1_FORCE_PMID_DSCHG_EN     0x08
#define CHARGER28_CHARGER_CONTROL_1_FORCE_PMID_DSCHG_MASK   0x08
#define CHARGER28_CHARGER_CONTROL_1_WD_RST_CLEAR            0x00
#define CHARGER28_CHARGER_CONTROL_1_WD_RST_SET              0x04
#define CHARGER28_CHARGER_CONTROL_1_WD_RST_MASK             0x04
#define CHARGER28_CHARGER_CONTROL_1_WATCHDOG_DISABLE        0x00
#define CHARGER28_CHARGER_CONTROL_1_WATCHDOG_40S            0x01
#define CHARGER28_CHARGER_CONTROL_1_WATCHDOG_80S            0x02
#define CHARGER28_CHARGER_CONTROL_1_WATCHDOG_160S           0x03
#define CHARGER28_CHARGER_CONTROL_1_WATCHDOG_MASK           0x03

/**
 * @brief Charger 28 charger control 2 register setting.
 * @details Specified setting for charger control 2 register of Charger 28 Click driver.
 */
#define CHARGER28_CHARGER_CONTROL_2_REG_RST_CLEAR           0x00
#define CHARGER28_CHARGER_CONTROL_2_REG_RST_SET             0x80
#define CHARGER28_CHARGER_CONTROL_2_REG_RST_MASK            0x80
#define CHARGER28_CHARGER_CONTROL_2_TREG_60C                0x00
#define CHARGER28_CHARGER_CONTROL_2_TREG_120C               0x40
#define CHARGER28_CHARGER_CONTROL_2_TREG_MASK               0x40
#define CHARGER28_CHARGER_CONTROL_2_EN_DITHER_DISABLE       0x00
#define CHARGER28_CHARGER_CONTROL_2_EN_DITHER_1X            0x10
#define CHARGER28_CHARGER_CONTROL_2_EN_DITHER_2X            0x20
#define CHARGER28_CHARGER_CONTROL_2_EN_DITHER_3X            0x30
#define CHARGER28_CHARGER_CONTROL_2_EN_DITHER_MASK          0x30
#define CHARGER28_CHARGER_CONTROL_2_SET_CONV_STRN_RED_3     0x00
#define CHARGER28_CHARGER_CONTROL_2_SET_CONV_STRN_RED_2     0x04
#define CHARGER28_CHARGER_CONTROL_2_SET_CONV_STRN_RED_1     0x08
#define CHARGER28_CHARGER_CONTROL_2_SET_CONV_STRN_MAX       0x0C
#define CHARGER28_CHARGER_CONTROL_2_SET_CONV_STRN_MASK      0x0C
#define CHARGER28_CHARGER_CONTROL_2_SET_BATFET_STRN_RED     0x00
#define CHARGER28_CHARGER_CONTROL_2_SET_BATFET_STRN_MAX     0x02
#define CHARGER28_CHARGER_CONTROL_2_SET_BATFET_STRN_MASK    0x02
#define CHARGER28_CHARGER_CONTROL_2_VBUS_OVP_6_3V           0x00
#define CHARGER28_CHARGER_CONTROL_2_VBUS_OVP_18_5V          0x01
#define CHARGER28_CHARGER_CONTROL_2_VBUS_OVP_MASK           0x01

/**
 * @brief Charger 28 NTC control 0 register setting.
 * @details Specified setting for NTC control 0 register of Charger 28 Click driver.
 */
#define CHARGER28_NTC_CONTROL_0_TS_IGNORE_CLEAR             0x00
#define CHARGER28_NTC_CONTROL_0_TS_IGNORE_SET               0x80
#define CHARGER28_NTC_CONTROL_0_TS_IGNORE_MASK              0x80
#define CHARGER28_NTC_CONTROL_0_CHG_RATE_1C                 0x00
#define CHARGER28_NTC_CONTROL_0_CHG_RATE_2C                 0x20
#define CHARGER28_NTC_CONTROL_0_CHG_RATE_4C                 0x40
#define CHARGER28_NTC_CONTROL_0_CHG_RATE_6C                 0x60
#define CHARGER28_NTC_CONTROL_0_CHG_RATE_MASK               0x60
#define CHARGER28_NTC_CONTROL_0_TS_TH_OTG_HOT_55C           0x00
#define CHARGER28_NTC_CONTROL_0_TS_TH_OTG_HOT_60C           0x08
#define CHARGER28_NTC_CONTROL_0_TS_TH_OTG_HOT_65C           0x10
#define CHARGER28_NTC_CONTROL_0_TS_TH_OTG_HOT_DISABLE       0x18
#define CHARGER28_NTC_CONTROL_0_TS_TH_OTG_HOT_MASK          0x18
#define CHARGER28_NTC_CONTROL_0_TS_TH_OTG_COLD_MIN_10C      0x00
#define CHARGER28_NTC_CONTROL_0_TS_TH_OTG_COLD_MIN_20C      0x04
#define CHARGER28_NTC_CONTROL_0_TS_TH_OTG_COLD_MASK         0x04
#define CHARGER28_NTC_CONTROL_0_TS_TH1_MIN_5C               0x00
#define CHARGER28_NTC_CONTROL_0_TS_TH1_0C                   0x02
#define CHARGER28_NTC_CONTROL_0_TS_TH1_MASK                 0x02
#define CHARGER28_NTC_CONTROL_0_TS_TH6_55C                  0x00
#define CHARGER28_NTC_CONTROL_0_TS_TH6_60C                  0x01
#define CHARGER28_NTC_CONTROL_0_TS_TH6_MASK                 0x01

/**
 * @brief Charger 28 charger status 0 register setting.
 * @details Specified setting for charger status 0 register of Charger 28 Click driver.
 */
#define CHARGER28_CHARGER_STATUS_0_PG_STAT                  0x80
#define CHARGER28_CHARGER_STATUS_0_ADC_DONE_STAT            0x40
#define CHARGER28_CHARGER_STATUS_0_TREG_STAT                0x20
#define CHARGER28_CHARGER_STATUS_0_VSYS_STAT                0x10
#define CHARGER28_CHARGER_STATUS_0_IINDPM_STAT              0x08
#define CHARGER28_CHARGER_STATUS_0_VINDPM_STAT              0x04
#define CHARGER28_CHARGER_STATUS_0_SAFETY_TMR_STAT          0x02
#define CHARGER28_CHARGER_STATUS_0_WD_STAT                  0x01

/**
 * @brief Charger 28 charger status 1 register setting.
 * @details Specified setting for charger status 1 register of Charger 28 Click driver.
 */
#define CHARGER28_CHARGER_STATUS_1_ICO_STAT_DIS             0x00
#define CHARGER28_CHARGER_STATUS_1_ICO_STAT_OPTIMIZATION    0x40
#define CHARGER28_CHARGER_STATUS_1_ICO_STAT_MAX_IN_CURRENT  0x80
#define CHARGER28_CHARGER_STATUS_1_ICO_STAT_SUSPENDED       0xC0
#define CHARGER28_CHARGER_STATUS_1_ICO_STAT_MASK            0xC0
#define CHARGER28_CHARGER_STATUS_1_CHG_STAT_NOT_CHARGING    0x00
#define CHARGER28_CHARGER_STATUS_1_CHG_STAT_TRICKLE_CHARGE  0x08
#define CHARGER28_CHARGER_STATUS_1_CHG_STAT_PRE_CHARGE      0x10
#define CHARGER28_CHARGER_STATUS_1_CHG_STAT_FAST_CHARGE     0x18
#define CHARGER28_CHARGER_STATUS_1_CHG_STAT_TAPER_CHARGE    0x20
#define CHARGER28_CHARGER_STATUS_1_CHG_STAT_TO_TIMER_ACT_CH 0x30
#define CHARGER28_CHARGER_STATUS_1_CHG_STAT_CHARGE_DONE     0x38
#define CHARGER28_CHARGER_STATUS_1_CHG_STAT_MASK            0x38
#define CHARGER28_CHARGER_STATUS_1_VBUS_STAT_NOT_POWERED    0x00
#define CHARGER28_CHARGER_STATUS_1_VBUS_STAT_IINDPM         0x04
#define CHARGER28_CHARGER_STATUS_1_VBUS_STAT_IN_BOOST_OTG   0x07
#define CHARGER28_CHARGER_STATUS_1_VBUS_STAT_MASK           0x07

/**
 * @brief Charger 28 fault status register setting.
 * @details Specified setting for fault status register of Charger 28 Click driver.
 */
#define CHARGER28_FAULT_STATUS_VBUS_FAULT_STAT              0x80
#define CHARGER28_FAULT_STATUS_BAT_FAULT_STAT               0x40
#define CHARGER28_FAULT_STATUS_VSYS_FAULT_STAT              0x20
#define CHARGER28_FAULT_STATUS_OTG_FAULT_STAT               0x10
#define CHARGER28_FAULT_STATUS_TSHUT_STAT                   0x08
#define CHARGER28_FAULT_STATUS_TS_STAT_TS_NORMAL            0x00
#define CHARGER28_FAULT_STATUS_TS_STAT_TS_COLD              0x01
#define CHARGER28_FAULT_STATUS_TS_STAT_TS_HOT               0x02
#define CHARGER28_FAULT_STATUS_TS_STAT_TS_COOL              0x03
#define CHARGER28_FAULT_STATUS_TS_STAT_TS_WARM              0x04
#define CHARGER28_FAULT_STATUS_TS_STAT_TS_PRECOOL           0x05
#define CHARGER28_FAULT_STATUS_TS_STAT_TS_PREWARM           0x06
#define CHARGER28_FAULT_STATUS_TS_STAT_MASK                 0x07

/**
 * @brief Charger 28 ADC control register setting.
 * @details Specified setting for ADC control register of Charger 28 Click driver.
 */
#define CHARGER28_ADC_CONTROL_EN_ADC_DIS                    0x00
#define CHARGER28_ADC_CONTROL_EN_ADC_EN                     0x80
#define CHARGER28_ADC_CONTROL_EN_ADC_MASK                   0x80
#define CHARGER28_ADC_CONTROL_ADC_RATE_CONTINUOUS           0x00
#define CHARGER28_ADC_CONTROL_ADC_RATE_ONE_SHOT             0x40
#define CHARGER28_ADC_CONTROL_ADC_RATE_MASK                 0x40
#define CHARGER28_ADC_CONTROL_ADC_SAMPLE_11BIT              0x00
#define CHARGER28_ADC_CONTROL_ADC_SAMPLE_10BIT              0x10
#define CHARGER28_ADC_CONTROL_ADC_SAMPLE_9BIT               0x20
#define CHARGER28_ADC_CONTROL_ADC_SAMPLE_8BIT               0x30
#define CHARGER28_ADC_CONTROL_ADC_SAMPLE_MASK               0x30
#define CHARGER28_ADC_CONTROL_ADC_AVG_DIS                   0x00
#define CHARGER28_ADC_CONTROL_ADC_AVG_EN                    0x08
#define CHARGER28_ADC_CONTROL_ADC_AVG_MASK                  0x08
#define CHARGER28_ADC_CONTROL_ADC_AVG_INIT_REG_VALUE        0x00
#define CHARGER28_ADC_CONTROL_ADC_AVG_INIT_NEW_CONV         0x04
#define CHARGER28_ADC_CONTROL_ADC_AVG_INIT_MASK             0x04
#define CHARGER28_ADC_CONTROL_DIS_ADCIN_ADC_EN              0x00
#define CHARGER28_ADC_CONTROL_DIS_ADCIN_ADC_DIS             0x01
#define CHARGER28_ADC_CONTROL_DIS_ADCIN_ADC_MASK            0x01

/**
 * @brief Charger 28 ADC measurement resolution setting.
 * @details Specified setting for ADC measurement resolution of Charger 28 Click driver.
 */
#define CHARGER28_LSB_ADC_IBUS                              2.5
#define CHARGER28_LSB_ADC_VBUS                              5
#define CHARGER28_LSB_ADC_VPMID                             5
#define CHARGER28_LSB_ADC_VBAT                              1.25
#define CHARGER28_LSB_ADC_IBAT                              5
#define CHARGER28_LSB_ADC_VSYS                              1.25
#define CHARGER28_LSB_ADC_ADCIN                             0.25
#define CHARGER28_LSB_ADC_TS                                0.098
#define CHARGER28_LSB_ADC_TDIE                              0.5

/**
 * @brief Charger 28 device part number setting.
 * @details Specified setting for device part number of Charger 28 Click driver.
 */
#define CHARGER28_PART_NUMBER                               0x04
#define CHARGER28_PART_NUMBER_MASK                          0x3C

/**
 * @brief Charger 28 device address setting.
 * @details Specified setting for device slave address selection of
 * Charger 28 Click driver.
 */
#define CHARGER28_DEVICE_ADDRESS                            0x6B

/*! @} */ // charger28_set

/**
 * @defgroup charger28_map Charger 28 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 28 Click driver.
 */

/**
 * @addtogroup charger28_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 28 Click to the selected MikroBUS.
 */
#define CHARGER28_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.cen = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger28_map
/*! @} */ // charger28

/**
 * @brief Charger 28 Click context object.
 * @details Context object definition of Charger 28 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cen;              /**< Charge enable pin (active low). */

    // Input pins
    digital_in_t pg;                /**< Power good indicator (active low). */
    digital_in_t sts;               /**< Charge status output (active low). */
    digital_in_t int_pin;           /**< Interrupt output (active low). */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} charger28_t;

/**
 * @brief Charger 28 Click configuration object.
 * @details Configuration object definition of Charger 28 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t pg;                  /**< Power good indicator (active low). */
    pin_name_t cen;                 /**< Charge enable pin (active low). */
    pin_name_t sts;                 /**< Charge status output (active low). */
    pin_name_t int_pin;             /**< Interrupt output (active low). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} charger28_cfg_t;

/**
 * @brief Charger 28 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER28_OK = 0,
    CHARGER28_ERROR = -1

} charger28_return_value_t;

/*!
 * @addtogroup charger28 Charger 28 Click Driver
 * @brief API for configuring and manipulating Charger 28 Click driver.
 * @{
 */

/**
 * @brief Charger 28 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger28_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger28_cfg_setup ( charger28_cfg_t *cfg );

/**
 * @brief Charger 28 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger28_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger28_init ( charger28_t *ctx, charger28_cfg_t *cfg );

/**
 * @brief Charger 28 default configuration function.
 * @details This function executes a default configuration of Charger 28
 * Click board.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t charger28_default_cfg ( charger28_t *ctx );

/**
 * @brief Charger 28 write multiple register bytes function.
 * @details This function writes multiple bytes to a specific register.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Pointer to the data to write.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_write_reg_bytes ( charger28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Charger 28 read multiple register bytes function.
 * @details This function reads multiple bytes from a specific register.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the data buffer for storing read values.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_read_reg_bytes ( charger28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Charger 28 write single register byte function.
 * @details This function writes a single byte to a specific register.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_write_reg_byte ( charger28_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Charger 28 read single register byte function.
 * @details This function reads a single byte from a specific register.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the data buffer for storing the read value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_read_reg_byte ( charger28_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Charger 28 write register word function.
 * @details This function writes a 16-bit word to a specific register.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit word to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_write_reg_word ( charger28_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Charger 28 read register word function.
 * @details This function reads a 16-bit word from a specific register.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the 16-bit word buffer for storing the read value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_read_reg_word ( charger28_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Charger 28 check communication function.
 * @details This function checks the communication with the device by verifying the part information.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_check_communication ( charger28_t *ctx );

/**
 * @brief Charger 28 enable charging function.
 * @details This function enables the charging process by setting the CEN pin low.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger28_enable_charging ( charger28_t *ctx );

/**
 * @brief Charger 28 disable charging function.
 * @details This function disables the charging process by setting the CEN pin high.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void charger28_disable_charging ( charger28_t *ctx );

/**
 * @brief Charger 28 get PG pin state function.
 * @details This function returns the logic state of the PG (Power Good) pin.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t charger28_get_pg_pin ( charger28_t *ctx );

/**
 * @brief Charger 28 get STS pin state function.
 * @details This function returns the logic state of the STS (Status) pin.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t charger28_get_sts_pin ( charger28_t *ctx );

/**
 * @brief Charger 28 get INT pin state function.
 * @details This function returns the logic state of the INT (Interrupt) pin.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t charger28_get_int_pin ( charger28_t *ctx );

/**
 * @brief Charger 28 get input current function.
 * @details This function reads and calculates the input current in milliamperes.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[out] ibus : Pointer to the variable for storing the calculated input current in milliamperes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_get_ibus ( charger28_t *ctx, float *ibus );

/**
 * @brief Charger 28 get battery current function.
 * @details This function reads and calculates the battery current in milliamperes.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[out] ibat : Pointer to the variable for storing the calculated battery current in milliamperes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_get_ibat ( charger28_t *ctx, int16_t *ibat );

/**
 * @brief Charger 28 get bus voltage function.
 * @details This function reads and calculates the bus voltage in millivolts.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[out] vbus : Pointer to the variable for storing the calculated bus voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_get_vbus ( charger28_t *ctx, uint16_t *vbus );

/**
 * @brief Charger 28 get PMID voltage function.
 * @details This function reads and calculates the PMID voltage in millivolts.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[out] vpmid : Pointer to the variable for storing the calculated PMID voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_get_vpmid ( charger28_t *ctx, uint16_t *vpmid );

/**
 * @brief Charger 28 get battery voltage function.
 * @details This function reads and calculates the battery voltage in millivolts.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[out] vbat : Pointer to the variable for storing the calculated battery voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_get_vbat ( charger28_t *ctx, float *vbat );

/**
 * @brief Charger 28 get system voltage function.
 * @details This function reads and calculates the system voltage in millivolts.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[out] vsys : Pointer to the variable for storing the calculated system voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_get_vsys ( charger28_t *ctx, float *vsys );

/**
 * @brief Charger 28 get TS percentage function.
 * @details This function reads and calculates the TS percentage of REGN.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[out] ts : Pointer to the variable for storing the calculated TS percentage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_get_ts ( charger28_t *ctx, float *ts );

/**
 * @brief Charger 28 get die temperature function.
 * @details This function reads and calculates the die temperature in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[out] tdie : Pointer to the variable for storing the calculated die temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_get_tdie ( charger28_t *ctx, float *tdie );

/**
 * @brief Charger 28 get ADC input function.
 * @details This function reads and calculates the ADC input voltage in millivolts.
 * @param[in] ctx : Click context object.
 * See #charger28_t object definition for detailed explanation.
 * @param[out] adcin : Pointer to the variable for storing the calculated ADC input voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t charger28_get_adcin ( charger28_t *ctx, float *adcin );

#ifdef __cplusplus
}
#endif
#endif // CHARGER28_H

/*! @} */ // charger28

// ------------------------------------------------------------------------ END
