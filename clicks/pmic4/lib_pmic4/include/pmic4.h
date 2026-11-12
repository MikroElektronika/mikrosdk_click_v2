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
 * @file pmic4.h
 * @brief This file contains API for PMIC 4 Click Driver.
 */

#ifndef PMIC4_H
#define PMIC4_H

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

#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup pmic4 PMIC 4 Click Driver
 * @brief API for configuring and manipulating PMIC 4 Click driver.
 * @{
 */

/**
 * @defgroup pmic4_reg PMIC 4 Registers List
 * @brief List of registers of PMIC 4 Click driver.
 */

/**
 * @addtogroup pmic4_reg
 * @{
 */

/**
 * @brief PMIC 4 register addresses.
 * @details AEM13921 configuration, interrupt, monitoring, and identification
 * registers. IRQFLG0 and IRQFLG1 are cleared when read.
 */
#define PMIC4_REGISTER_BYTE_BITS               8
#define PMIC4_REG_VERSION                       0x00
#define PMIC4_REG_SRC1REGU0                     0x01
#define PMIC4_REG_SRC1REGU1                     0x02
#define PMIC4_REG_SRC2REGU0                     0x03
#define PMIC4_REG_SRC2REGU1                     0x04
#define PMIC4_REG_VOVDIS                        0x05
#define PMIC4_REG_VCHRDY                        0x06
#define PMIC4_REG_VOVCH                         0x07
#define PMIC4_REG_BST1CFG                       0x08
#define PMIC4_REG_BST2CFG                       0x09
#define PMIC4_REG_BUCKCFG                       0x0A
#define PMIC4_REG_VCHRDYBUCK                    0x0B
#define PMIC4_REG_CHG5V                         0x0C
#define PMIC4_REG_TEMPCOLDCH                    0x0D
#define PMIC4_REG_TEMPHOTCH                     0x0E
#define PMIC4_REG_TEMPCOLDDIS                   0x0F
#define PMIC4_REG_TEMPHOTDIS                    0x10
#define PMIC4_REG_TEMPPROTECT                   0x11
#define PMIC4_REG_SRCLOW                        0x12
#define PMIC4_REG_APM                           0x13
#define PMIC4_REG_APMACC                        0x14
#define PMIC4_REG_IRQEN0                        0x15
#define PMIC4_REG_IRQEN1                        0x16
#define PMIC4_REG_CTRL                          0x17
#define PMIC4_REG_IRQFLG0                       0x18
#define PMIC4_REG_IRQFLG1                       0x19
#define PMIC4_REG_STATUS0                       0x1A
#define PMIC4_REG_STATUS1                       0x1B
#define PMIC4_REG_APM0SRC1                      0x1C
#define PMIC4_REG_APM1SRC1                      0x1D
#define PMIC4_REG_APM2SRC1                      0x1E
#define PMIC4_REG_APM0SRC2                      0x1F
#define PMIC4_REG_APM1SRC2                      0x20
#define PMIC4_REG_APM2SRC2                      0x21
#define PMIC4_REG_APM0LOAD                      0x22
#define PMIC4_REG_APM1LOAD                      0x23
#define PMIC4_REG_APM2LOAD                      0x24
#define PMIC4_REG_APM0CHG5V                     0x25
#define PMIC4_REG_APM1CHG5V                     0x26
#define PMIC4_REG_APMERR                        0x27
#define PMIC4_REG_TEMP                          0x28
#define PMIC4_REG_STO                           0x29
#define PMIC4_REG_SRC1                          0x2A
#define PMIC4_REG_SRC2                          0x2B
#define PMIC4_REG_PN0                           0xE0
#define PMIC4_REG_PN1                           0xE1
#define PMIC4_REG_PN2                           0xE2
#define PMIC4_REG_PN3                           0xE3
#define PMIC4_REG_PN4                           0xE4

/*! @} */ // pmic4_reg

/**
 * @defgroup pmic4_set PMIC 4 Registers Settings
 * @brief Settings for registers of PMIC 4 Click driver.
 */

/**
 * @addtogroup pmic4_set
 * @{
 */

/**
 * @brief PMIC 4 configuration source settings.
 * @details CTRL.UPDATE selects GPIO straps or applies the complete I2C
 * configuration. Configuration register defaults do not mirror GPIO straps.
 */
#define PMIC4_CONFIG_GPIO                       0x00
#define PMIC4_CONFIG_I2C                        0x01
#define PMIC4_CTRL_UPDATE                       0x01
#define PMIC4_CTRL_SYNCBUSY                     0x04

/**
 * @brief PMIC 4 source regulation settings.
 * @details MPPT ratio values include their SRCxREGU0 field shift. Combine a
 * ratio with PMIC4_SOURCE_MODE_MPPT. Wait and period values form SRCxREGU1.
 */
#define PMIC4_SOURCE_MODE_CONSTANT              0x00
#define PMIC4_SOURCE_MODE_MPPT                  0x01
#define PMIC4_MPPT_RATIO_35                     0x00
#define PMIC4_MPPT_RATIO_50                     0x02
#define PMIC4_MPPT_RATIO_65                     0x04
#define PMIC4_MPPT_RATIO_70                     0x06
#define PMIC4_MPPT_RATIO_75                     0x08
#define PMIC4_MPPT_RATIO_80                     0x0A
#define PMIC4_MPPT_RATIO_85                     0x0C
#define PMIC4_MPPT_RATIO_ZMPP_OR_100            0x0E
#define PMIC4_MPPT_WAIT_1_8_MS                  0x00
#define PMIC4_MPPT_WAIT_3_6_MS                  0x01
#define PMIC4_MPPT_WAIT_7_3_MS                  0x02
#define PMIC4_MPPT_WAIT_15_MS                   0x03
#define PMIC4_MPPT_WAIT_29_MS                   0x04
#define PMIC4_MPPT_WAIT_116_MS                  0x05
#define PMIC4_MPPT_WAIT_233_MS                  0x06
#define PMIC4_MPPT_WAIT_465_MS                  0x07
#define PMIC4_MPPT_PERIOD_116_MS                0x00
#define PMIC4_MPPT_PERIOD_233_MS                0x08
#define PMIC4_MPPT_PERIOD_465_MS                0x10
#define PMIC4_MPPT_PERIOD_931_MS                0x18
#define PMIC4_MPPT_PERIOD_1862_MS               0x20
#define PMIC4_MPPT_PERIOD_3724_MS               0x28
#define PMIC4_MPPT_PERIOD_7447_MS               0x30
#define PMIC4_MPPT_PERIOD_14895_MS              0x38

/**
 * @brief PMIC 4 converter settings.
 * @details Timing multipliers x3 for the 33 uH boost inductors and x2 for the
 * 10 uH buck inductor match GPIO operation. LOAD values are I2C field values,
 * not strap codes. Do not select LOAD_OFF after the buck has been enabled.
 */
#define PMIC4_BOOST_ENABLE                      0x01
#define PMIC4_BOOST_HIGH_POWER_ENABLE           0x02
#define PMIC4_BOOST_TIMING_X3                   0x08
#define PMIC4_BUCK_TIMING_X2                    0x10
#define PMIC4_LOAD_OFF                          0x00
#define PMIC4_LOAD_0_6_V                        0x01
#define PMIC4_LOAD_0_9_V                        0x02
#define PMIC4_LOAD_1_2_V                        0x03
#define PMIC4_LOAD_1_5_V                        0x04
#define PMIC4_LOAD_1_8_V                        0x05
#define PMIC4_LOAD_2_2_V                        0x06
#define PMIC4_LOAD_2_5_V                        0x07
#define PMIC4_LOAD_2_8_V                        0x08
#define PMIC4_LOAD_3_0_V                        0x09
#define PMIC4_LOAD_3_3_V                        0x0A
#define PMIC4_CHARGER_ENABLE                    0x01
#define PMIC4_CHARGER_CV_ENABLE                 0x02
#define PMIC4_THERMAL_PROTECTION_ENABLE         0x01

/**
 * @brief PMIC 4 default board profile settings.
 * @details These I2C codes reproduce the default 3.00/3.21/4.13 V storage
 * limits and 0/45 C protection range. Temperature codes match the default
 * RT1 (10 kohm, beta 3380 K) and R29 (22 kohm). TH EN = 1 connects the NTC
 * divider; TH EN = 0 selects VINT instead. Ready/upper limits are quantized
 * to 3.20625 V and 4.125 V respectively.
 */
#define PMIC4_STORAGE_DISCHARGE_3_00_V          0x20
#define PMIC4_STORAGE_READY_3_21_V              0x28
#define PMIC4_STORAGE_UPPER_4_13_V              0x4C
#define PMIC4_TEMPERATURE_COLD_0_C              0x90
#define PMIC4_TEMPERATURE_HOT_45_C              0x2F
#define PMIC4_SOURCE_LOW_0_113_V                0x00

/**
 * @brief PMIC 4 average power monitoring settings.
 * @details Power-meter data needs a separate calibrated alpha factor for
 * each converter. APM channels measure transfers at STO, not SRCx input
 * current or LOAD output current. A 116 ms MPPT period overrides WINDOW.
 */
#define PMIC4_APM_SOURCE_1_ENABLE               0x01
#define PMIC4_APM_SOURCE_2_ENABLE               0x02
#define PMIC4_APM_LOAD_ENABLE                   0x04
#define PMIC4_APM_CHARGER_ENABLE                0x08
#define PMIC4_APM_POWER_METER                   0x10
#define PMIC4_APM_WINDOW_233_MS                 0x00
#define PMIC4_APM_WINDOW_116_MS                 0x20
#define PMIC4_APM_ACC_DISABLED                  0x00
#define PMIC4_APM_SOURCE_1_OVERFLOW             0x01
#define PMIC4_APM_SOURCE_1_INVALID              0x02
#define PMIC4_APM_SOURCE_2_OVERFLOW             0x04
#define PMIC4_APM_SOURCE_2_INVALID              0x08
#define PMIC4_APM_LOAD_OVERFLOW                 0x10
#define PMIC4_APM_LOAD_INVALID                  0x20
#define PMIC4_APM_CHARGER_LIMITED               0x40

/**
 * @brief PMIC 4 APM error field layout.
 * @details Each converter has an overflow/invalid pair in APMERR. The
 * charger precharge flag is separate and is not a converter data error.
 */
#define PMIC4_APM_ERROR_BITS_PER_CHANNEL        2
#define PMIC4_APM_CHANNEL_ERROR_MASK            ( PMIC4_APM_SOURCE_1_OVERFLOW | PMIC4_APM_SOURCE_1_INVALID )
#define PMIC4_APM_CONVERTER_ERROR_MASK          ( PMIC4_APM_SOURCE_1_OVERFLOW | PMIC4_APM_SOURCE_1_INVALID | \
                                                PMIC4_APM_SOURCE_2_OVERFLOW | PMIC4_APM_SOURCE_2_INVALID | \
                                                PMIC4_APM_LOAD_OVERFLOW | PMIC4_APM_LOAD_INVALID )

/**
 * @brief PMIC 4 nominal charger current factor.
 * @details CC current in mA = this factor / R10 in ohms (datasheet Section
 * 6.8). This resistor-based estimate is not a calibrated measurement.
 */
#define PMIC4_CHARGER_CC_FACTOR_MA_OHM           50000.0f

/**
 * @brief PMIC 4 current channel indexes and validity masks.
 * @details SOURCE_1, SOURCE_2, and CHARGER are currents into STO. LOAD is
 * current drawn from STO by the buck converter, including converter losses.
 * The corresponding mask is 1 shifted left by the channel index.
 */
#define PMIC4_CURRENT_SOURCE_1                  0
#define PMIC4_CURRENT_SOURCE_2                  1
#define PMIC4_CURRENT_LOAD                      2
#define PMIC4_CURRENT_CHARGER                   3
#define PMIC4_CURRENT_CONVERTER_COUNT           3
#define PMIC4_CURRENT_CHANNEL_COUNT             4
#define PMIC4_CURRENT_SOURCE_1_VALID            0x01
#define PMIC4_CURRENT_SOURCE_2_VALID            0x02
#define PMIC4_CURRENT_LOAD_VALID                0x04
#define PMIC4_CURRENT_CHARGER_VALID             0x08
#define PMIC4_CURRENT_ALL_VALID                 0x0F

/**
 * @brief PMIC 4 power status masks.
 * @details STATUS0 reports storage thresholds, low sources, and the presence
 * of a valid 5 V charger input; it does not measure charging current.
 */
#define PMIC4_STATUS_OVDIS                      0x01
#define PMIC4_STATUS_CHRDY                      0x02
#define PMIC4_STATUS_OVCH                       0x04
#define PMIC4_STATUS_SRC1_LOW                   0x08
#define PMIC4_STATUS_SRC2_LOW                   0x10
#define PMIC4_STATUS_CHARGER_CONNECTED          0x20

/**
 * @brief PMIC 4 temperature status masks.
 * @details STATUS1 reports active charge and discharge temperature limits.
 */
#define PMIC4_STATUS_CHARGE_COLD                0x01
#define PMIC4_STATUS_CHARGE_HOT                 0x02
#define PMIC4_STATUS_DISCHARGE_COLD             0x04
#define PMIC4_STATUS_DISCHARGE_HOT              0x08

/**
 * @brief PMIC 4 interrupt masks.
 * @details IRQEN0/IRQFLG0 occupy the low byte, IRQEN1/IRQFLG1 the high byte.
 * Reading the flags acknowledges the enabled events, unlike reading STATUSx.
 */
#define PMIC4_IRQ_I2C_READY                     0x0001
#define PMIC4_IRQ_OVDIS                         0x0002
#define PMIC4_IRQ_CHRDY                         0x0004
#define PMIC4_IRQ_OVCH                          0x0008
#define PMIC4_IRQ_SOURCE_LOW                    0x0010
#define PMIC4_IRQ_CHARGE_TEMPERATURE            0x0020
#define PMIC4_IRQ_DISCHARGE_TEMPERATURE         0x0040
#define PMIC4_IRQ_CHARGER_CONNECTED             0x0080
#define PMIC4_IRQ_SRC1_MPPT_START               0x0100
#define PMIC4_IRQ_SRC1_MPPT_DONE                0x0200
#define PMIC4_IRQ_SRC2_MPPT_START               0x0400
#define PMIC4_IRQ_SRC2_MPPT_DONE                0x0800
#define PMIC4_IRQ_STORAGE_DONE                  0x1000
#define PMIC4_IRQ_TEMPERATURE_DONE              0x2000
#define PMIC4_IRQ_APM_DONE                      0x4000
#define PMIC4_IRQ_APM_ERROR                     0x8000

/**
 * @brief PMIC 4 voltage measurement channels.
 * @details Selects storage or a source MPPT measurement. LOAD voltage is not
 * measured by the AEM13921 voltage monitoring registers.
 */
#define PMIC4_VOLTAGE_STORAGE                   0
#define PMIC4_VOLTAGE_SOURCE_1                  1
#define PMIC4_VOLTAGE_SOURCE_2                  2

/**
 * @brief PMIC 4 device address setting.
 * @details Specified setting for device slave address selection of
 * PMIC 4 Click driver.
 */
#define PMIC4_DEVICE_ADDRESS                    0x51

/*! @} */ // pmic4_set

/**
 * @defgroup pmic4_map PMIC 4 MikroBUS Map
 * @brief MikroBUS pin mapping of PMIC 4 Click driver.
 */

/**
 * @addtogroup pmic4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PMIC 4 Click to the selected MikroBUS.
 */
#define PMIC4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.stl = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pmic4_map
/*! @} */ // pmic4

/**
 * @brief PMIC 4 Click context object.
 * @details Context object definition of PMIC 4 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t stl;       /**< nSTL on mikroBUS AN, active low when LOAD is ready. */
    digital_in_t int_pin;   /**< IRQ: active-high interrupt indication. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} pmic4_t;

/**
 * @brief PMIC 4 Click configuration object.
 * @details Configuration object definition of PMIC 4 Click driver.
 */
typedef struct
{
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t stl;         /**< nSTL input pin descriptor. */
    pin_name_t int_pin;     /**< IRQ input pin descriptor. */

    uint32_t   i2c_speed;   /**< I2C serial speed. */
    uint8_t    i2c_address; /**< I2C slave address. */

} pmic4_cfg_t;

/**
 * @brief PMIC 4 status object.
 * @details Current power and temperature status registers, read without
 * acknowledging interrupts. Individual bits use the PMIC4_STATUS_* masks.
 */
typedef struct
{
    uint8_t power;          /**< STATUS0: source, storage, and charger state. */
    uint8_t temperature;    /**< STATUS1: charge/discharge temperature limits. */

} pmic4_status_t;

/**
 * @brief PMIC 4 current conversion configuration object.
 * @details Alpha is watts per decoded, single-window APM unit. Zero selects
 * activity monitoring; nonzero values must come from customer calibration.
 * @par Calibration
 * Keep the board, inductors, APM window, and converter timings unchanged.
 * Average several fresh, valid samples at a steady operating point. Use
 * the full apm_value, not the displayed value in millions of APM units.
 * Reject channel errors using errors; current valid bits remain clear while
 * conversion is disabled. Do not use zero APM values to calculate a factor.
 * Measure each path's contribution at STO, isolating other paths or accounting
 * for their contributions, PMIC quiescent current, and other STO loads.
 * Source input current and LOAD output current are not STO-side currents.
 * With a positive path current in amps and stable STO voltage:
 * @code
 * alpha = ( VSTO * Ipath_A ) / average_apm_value;
 * @endcode
 * Convert meter mA readings to amps before using the formula. Repeat at
 * several operating points; this API supports scale factors, not offset or
 * nonlinear correction. Calibrate SRC1, SRC2, and LOAD
 * separately. For LOAD, remove charging inputs and account for other STO
 * consumption. For sources, do not treat net battery current as source current
 * unless LOAD and other STO consumption have been accounted for.
 * Measure the charger CC current at STO during continuous, unrestricted CC
 * charging, not its duty-averaged current near the upper voltage limit.
 * Store that measured value in charger_current, not the R10-based estimate.
 * Enter the factors in the example's APP_SOURCE_1_ALPHA, APP_SOURCE_2_ALPHA,
 * APP_LOAD_ALPHA, and APP_CHARGER_CALIBRATED_CURRENT_MA settings. Leave
 * uncalibrated channels at zero and recalibrate after hardware/timing changes.
 * See AEM13921 datasheet Section 9.17 and e-peas support for fixture guidance.
 */
typedef struct
{
    float alpha[ PMIC4_CURRENT_CONVERTER_COUNT ]; /**< SRC1/SRC2/LOAD factors in W/APM unit. */
    float charger_current;  /**< Measured CC current in mA; zero disables conversion. */

} pmic4_current_cfg_t;

/**
 * @brief PMIC 4 current monitoring object.
 * @details Current values are average estimates referenced to STO. Check
 * valid before using a value; unavailable conversions are not zero current.
 * Activity indicates nonzero, valid APM data even without calibration.
 * Activity is not external load detection: the buck can transfer energy
 * without an attached load. Compare apm_value to observe relative demand.
 * Validity checks data and conversion availability, not calibration accuracy.
 * Form a net transfer only with all channels valid and customer-calibrated;
 * PMIC quiescent current and other loads connected to STO are not included.
 */
typedef struct
{
    float storage_voltage;  /**< Latest STO voltage, not a battery percentage. */
    float current[ PMIC4_CURRENT_CHANNEL_COUNT ]; /**< Current estimates in mA. */
    float apm_value[ PMIC4_CURRENT_CONVERTER_COUNT ]; /**< Unscaled SRC1/SRC2/LOAD APM units. */
    uint8_t valid;          /**< Valid conversions; precharge is excluded. */
    uint8_t activity;       /**< Channels with detected energy transfer. */
    uint8_t errors;         /**< APMERR: individual converter validity/overflow. */

} pmic4_currents_t;

/**
 * @brief PMIC 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PMIC4_OK = 0,              /**< Operation completed successfully. */
    PMIC4_ERROR = -1,          /**< Invalid argument or I2C transfer failure. */
    PMIC4_NOT_READY = -2,      /**< Synchronization or fresh-sample timeout. */
    PMIC4_ERROR_DEVICE = -3,   /**< Unexpected AEM13921 part number. */
    PMIC4_ERROR_CONFIG = -4,   /**< Configuration mismatch or unsupported mode. */
    PMIC4_ERROR_SAMPLE = -5    /**< Invalid or saturated monitoring sample. */

} pmic4_return_value_t;

/*!
 * @addtogroup pmic4 PMIC 4 Click Driver
 * @brief API for configuring and manipulating PMIC 4 Click driver.
 * @{
 */

/**
 * @brief PMIC 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pmic4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pmic4_cfg_setup ( pmic4_cfg_t *cfg );

/**
 * @brief PMIC 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pmic4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Q2 inverts ST_LOAD on mikroBUS AN, which R5 pulls up to
 * the selected VCC. ST_STO is available only at TP6. Use #pmic4_get_status
 * to read the storage threshold flags over I2C.
 */
err_t pmic4_init ( pmic4_t *ctx, pmic4_cfg_t *cfg );

/**
 * @brief PMIC 4 default configuration function.
 * @details This function verifies the AEM13921 part number and selects the
 * board's hardware configuration without programming charging thresholds.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or I2C error,
 *         @li @c -2 - Synchronization timeout,
 *         @li @c -3 - Unexpected part number,
 *         @li @c -4 - Configuration mode did not take effect.
 * See #err_t definition for detailed explanation.
 * @note Allows approximately one second for I2C readiness. VCC SEL supplies
 * the interface only; SRC1, SRC2, or 5V_IN must provide cold-start energy.
 * Existing I2C configuration is replaced by GPIO settings. IRQ flags are not
 * acknowledged, and APM data is not updated in GPIO configuration mode.
 */
err_t pmic4_default_cfg ( pmic4_t *ctx );

/**
 * @brief PMIC 4 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Only registers SRC1REGU0 through CTRL are writable. Configuration
 * writes require pmic4_set_config_mode with PMIC4_CONFIG_I2C to take effect.
 */
err_t pmic4_write_reg ( pmic4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief PMIC 4 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The complete transfer must stay within SRC1REGU0 through CTRL.
 * Reserved bits must remain zero. Writing CTRL may apply the staged settings.
 */
err_t pmic4_write_regs ( pmic4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief PMIC 4 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Reading IRQFLG0 or IRQFLG1 clears that register's interrupt flags.
 */
err_t pmic4_read_reg ( pmic4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief PMIC 4 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The complete transfer must stay within VERSION through SRC2, or PN0
 * through PN4. A transfer containing IRQFLGx acknowledges those interrupts.
 */
err_t pmic4_read_regs ( pmic4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief PMIC 4 configuration mode function.
 * @details This function applies GPIO or staged I2C configuration and waits
 * for system register synchronization to finish.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[in] mode : PMIC4_CONFIG_GPIO or PMIC4_CONFIG_I2C.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or I2C error,
 *         @li @c -2 - Synchronization timeout,
 *         @li @c -4 - Configuration mode did not take effect.
 * See #err_t definition for detailed explanation.
 * @note Before selecting I2C, stage a complete configuration suitable for the
 * storage element, sources, load, and fitted inductors. Register defaults do
 * not match GPIO settings. Never apply the default LOAD_OFF value after the
 * buck has been enabled. Each synchronization wait is bounded to about 1 s.
 */
err_t pmic4_set_config_mode ( pmic4_t *ctx, uint8_t mode );

/**
 * @brief PMIC 4 default board APM configuration function.
 * @details This function applies an I2C profile matching the default board
 * settings and enables average power monitoring for both sources, LOAD,
 * and the 5 V charger, with a 233 ms window and no accumulation.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or I2C error,
 *         @li @c -2 - Synchronization timeout,
 *         @li @c -4 - Configuration readback or mode mismatch.
 * See #err_t definition for detailed explanation.
 * @note Call after pmic4_default_cfg; GPIO mode cannot update APM. The profile
 * selects LOAD = 2.5 V and STO limits = 3.00/3.21/4.13 V. Both sources use
 * 80% MPPT with a 29 ms wait and 1862 ms period, matching the board straps.
 * It uses x3 boost, x2 buck, CC charging, and 0/45 C protection. Match the
 * battery, inductors, and NTC/divider to this profile. I2C overrides the
 * configuration straps. SHIP_MODE, I2C EN, and TH EN remain hardware
 * controls. Set TH EN = 1 for thermal protection. Limit SRCx current
 * externally; R10 limits only 5V_IN.
 */
err_t pmic4_configure_apm ( pmic4_t *ctx );

/**
 * @brief PMIC 4 current monitoring function.
 * @details This function waits for a fresh APM window and reports storage
 * voltage and transfer activity. Customer calibration optionally enables
 * average source, load, and 5 V charging current conversion at STO.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[in] cfg : Current conversion configuration object.
 * See #pmic4_current_cfg_t object definition for detailed explanation.
 * @param[out] currents : Current monitoring object.
 * See #pmic4_currents_t object definition for detailed explanation.
 * @return @li @c  0 - Fresh APM sample read; check per-channel validity,
 *         @li @c -1 - Invalid argument or I2C error,
 *         @li @c -2 - No coherent fresh APM sample within the bounded wait,
 *         @li @c -4 - Invalid conversion settings or unsupported configuration,
 *         @li @c -5 - Invalid STO voltage or charger duty count.
 * See #err_t definition for detailed explanation.
 * @note Requires applied I2C power-meter settings, all four APM channels,
 * APMDONE IRQ, and no accumulation. APM IRQ flags are acknowledged; IRQFLG0
 * is untouched. See #pmic4_current_cfg_t for calibration guidance. Zero
 * factors/current disable conversion, not activity or raw data. Check valid:
 * invalid, overflowed, disabled, and precharge conversions are unavailable.
 * Charger conversion accepts zero or a measured CC current of 13.5 to 135 mA;
 * CV mode is unsupported. Net current needs all channels calibrated and valid,
 * excluding PMIC quiescent current and other STO loads. The latest STO voltage
 * substitutes for its window average. Output changes only on success.
 */
err_t pmic4_get_currents ( pmic4_t *ctx, pmic4_current_cfg_t *cfg, pmic4_currents_t *currents );

/**
 * @brief PMIC 4 status reading function.
 * @details This function reads the power and temperature status registers.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[out] status : Current status object.
 * See #pmic4_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function does not clear interrupt flags. The output is updated
 * only after a successful I2C read.
 */
err_t pmic4_get_status ( pmic4_t *ctx, pmic4_status_t *status );

/**
 * @brief PMIC 4 voltage reading function.
 * @details This function reads the latest storage or source voltage in volts.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[in] channel : PMIC4_VOLTAGE_STORAGE, PMIC4_VOLTAGE_SOURCE_1, or PMIC4_VOLTAGE_SOURCE_2.
 * @param[out] voltage : Measured voltage in volts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Source values are MPPT samples, not continuous terminal measurements.
 * They may be stale before an MPPT evaluation or while harvesting is stopped.
 * Codes below the source ADC range read as 0.113 V, not zero. This function
 * does not trigger a conversion; an invalid source code leaves output intact.
 */
err_t pmic4_get_voltage ( pmic4_t *ctx, uint8_t channel, float *voltage );

/**
 * @brief PMIC 4 NTC temperature reading function.
 * @details This function converts the latest onboard NTC measurement to degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to the temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Invalid argument or I2C error,
 *         @li @c -5 - Zero/reset or saturated temperature code.
 * See #err_t definition for detailed explanation.
 * @note Set TH EN = 1 (JP2 pins 2-3); position 0 selects VINT, not the NTC.
 * Hardware updates TEMP about every 7.45 s. This function does not trigger
 * conversion or verify freshness or the jumper position.
 * Uses the default RT1 (10 kohm, B25/50 = 3380 K) and R29 (22 kohm). This beta
 * approximation is most accurate near 25 to 50 C and measures the PCB NTC,
 * not IC die or battery-cell temperature. Output changes only on success.
 */
err_t pmic4_get_temperature ( pmic4_t *ctx, float *temperature );

/**
 * @brief PMIC 4 interrupt flags reading function.
 * @details This function reads and acknowledges both interrupt flag registers.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @param[out] flags : IRQFLG0 in bits 7:0 and IRQFLG1 in bits 15:8.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Only enabled events set flags. Reading each register clears its
 * flags; an interrupted transfer can acknowledge only part of the events.
 */
err_t pmic4_get_interrupt_flags ( pmic4_t *ctx, uint16_t *flags );

/**
 * @brief PMIC 4 load status pin function.
 * @details This function reads the active-low nSTL input on mikroBUS AN
 * and returns the logical state of the AEM13921 ST_LOAD output.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @return @li @c 0 - LOAD is not ready (AN high),
 *         @li @c 1 - LOAD is ready (AN low).
 * @note TP7 carries ST_LOAD before Q2 inverts it. Readiness is
 * specified for LOAD voltages of at least 1.2 V and is independent of
 * whether an external load is connected.
 */
uint8_t pmic4_get_stl_pin ( pmic4_t *ctx );

/**
 * @brief PMIC 4 interrupt pin function.
 * @details This function reads the active-high IRQ pin state.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @return Pin logic state, 0 or 1.
 * @note Reading the pin does not acknowledge events. Use
 * pmic4_get_interrupt_flags to read and clear the interrupt cause.
 */
uint8_t pmic4_get_int_pin ( pmic4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PMIC4_H

/*! @} */ // pmic4

// ------------------------------------------------------------------------ END
