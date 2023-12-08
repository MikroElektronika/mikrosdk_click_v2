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
 * @file pwrmeter3.h
 * @brief This file contains API for PWR Meter 3 Click Driver.
 */

#ifndef PWRMETER3_H
#define PWRMETER3_H

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
 * @addtogroup pwrmeter3 PWR Meter 3 Click Driver
 * @brief API for configuring and manipulating PWR Meter 3 Click driver.
 * @{
 */

/**
 * @defgroup pwrmeter3_reg PWR Meter 3 Registers List
 * @brief List of registers of PWR Meter 3 Click driver.
 */

/**
 * @addtogroup pwrmeter3_reg
 * @{
 */

/**
 * @brief PWR Meter 3 EEPROM registers.
 * @details Specified register for EEPROM of PWR Meter 3 Click driver.
 */
#define PWRMETER3_REG_EEPROM_0B             0x0B
#define PWRMETER3_REG_EEPROM_0C             0x0C
#define PWRMETER3_REG_EEPROM_0D             0x0D
#define PWRMETER3_REG_EEPROM_0E             0x0E
#define PWRMETER3_REG_EEPROM_0F             0x0F

/**
 * @brief PWR Meter 3 SHADOW registers.
 * @details Specified register for SHADOW of PWR Meter 3 Click driver.
 * @note At power up, all shadow registers are loaded from EEPROM, including all configuration parameters.
 * The shadow registers can be written to in order to change the device behavior without having to perform
 * an EEPROM write. Any changes made in shadow memory are volatile and do not persist through a reset event.
 */
#define PWRMETER3_REG_SHADOW_1B             0x1B
#define PWRMETER3_REG_SHADOW_1C             0x1C
#define PWRMETER3_REG_SHADOW_1D             0x1D
#define PWRMETER3_REG_SHADOW_1E             0x1E
#define PWRMETER3_REG_SHADOW_1F             0x1F

/**
 * @brief PWR Meter 3 VOLATILE registers.
 * @details Specified register for VOLATILE of PWR Meter 3 Click driver.
 */
#define PWRMETER3_REG_VOLATILE_20           0x20
#define PWRMETER3_REG_VOLATILE_21           0x21
#define PWRMETER3_REG_VOLATILE_22           0x22
#define PWRMETER3_REG_VOLATILE_25           0x25
#define PWRMETER3_REG_VOLATILE_26           0x26
#define PWRMETER3_REG_VOLATILE_27           0x27
#define PWRMETER3_REG_VOLATILE_28           0x28
#define PWRMETER3_REG_VOLATILE_29           0x29
#define PWRMETER3_REG_VOLATILE_2A           0x2A
#define PWRMETER3_REG_VOLATILE_2C           0x2C
#define PWRMETER3_REG_VOLATILE_2D           0x2D
#define PWRMETER3_REG_VOLATILE_2F           0x2F
#define PWRMETER3_REG_VOLATILE_30           0x30

/*! @} */ // pwrmeter3_reg

/**
 * @defgroup pwrmeter3_set PWR Meter 3 Registers Settings
 * @brief Settings for registers of PWR Meter 3 Click driver.
 */

/**
 * @addtogroup pwrmeter3_set
 * @{
 */

/**
 * @brief PWR Meter 3 access code values.
 * @details Specified access code values of PWR Meter 3 Click driver.
 */
#define PWRMETER3_CUST_ACCESS_CODE          0x4F70656Eul
#define PWRMETER3_CUST_ACCESS_CODE_CLEAR    0x00000000ul

/**
 * @brief PWR Meter 3 register 0E/1E settings.
 * @details Specified register 0E/1E settings of PWR Meter 3 Click driver.
 */
#define PWRMETER3_VEVENT_CYCS_MASK          0x0000003Ful
#define PWRMETER3_OVERVREG_MASK             0x00003F00ul
#define PWRMETER3_UNDERVREG_MASK            0x000FC000ul
#define PWRMETER3_DELAYCNT_SEL_MASK         0x00100000ul
#define PWRMETER3_HALFCYCLC_EN_MASK         0x00200000ul
#define PWRMETER3_SQUAREWAVE_EN_MASK        0x00400000ul
#define PWRMETER3_ZEROCROSSCHANSEL_MASK     0x00800000ul
#define PWRMETER3_ZEROCROSSEDGESEL_MASK     0x01000000ul
#define PWRMETER3_ECC_MASK                  0xFC000000ul
#define PWRMETER3_OVERVREG_MAX              63
#define PWRMETER3_UNDERVREG_MAX             63
#define PWRMETER3_OVERVREG_3                3
#define PWRMETER3_UNDERVREG_1               1

/**
 * @brief PWR Meter 3 register 0F/1F settings.
 * @details Specified register 0F/1F settings of PWR Meter 3 Click driver.
 */
#define PWRMETER3_I2C_SLV_ADDR_MASK         0x000001FCul
#define PWRMETER3_I2C_DIS_SLV_ADDR          0x00000200ul
#define PWRMETER3_DIO_0_SEL_MASK            0x00000C00ul
#define PWRMETER3_DIO_1_SEL_MASK            0x00003000ul
#define PWRMETER3_N_MASK                    0x00FFC000ul
#define PWRMETER3_BYPASS_N_EN_MASK          0x01000000ul
#define PWRMETER3_DIO_0_SEL_ZC              0
#define PWRMETER3_DIO_0_SEL_OV              1
#define PWRMETER3_DIO_0_SEL_UV              2
#define PWRMETER3_DIO_0_SEL_OV_UV           3
#define PWRMETER3_DIO_1_SEL_OCF             0
#define PWRMETER3_DIO_1_SEL_UV              1
#define PWRMETER3_DIO_1_SEL_OV              2
#define PWRMETER3_DIO_1_SEL_OV_UV_OCF       3
#define PWRMETER3_BYPASS_N_DISABLE          0
#define PWRMETER3_BYPASS_N_ENABLE           1
#define PWRMETER3_MAX_NUM_SAMPLES           1023u

/**
 * @brief PWR Meter 3 RMS voltage and current calculation values.
 * @details Specified RMS voltage and current calculation values of PWR Meter 3 Click driver.
 */
#define PWRMETER3_RSENSE_OHM                2000.0f
#define PWRMETER3_AC_RDIV_OHM               2000000.0f
#define PWRMETER3_DC_RDIV_OHM               4000000.0f
#define PWRMETER3_ADC_FSCALE                55000u
#define PWRMETER3_DELTA_VIN_MAX_mV          250
#define PWRMETER3_mV_TO_V                   1000u
#define PWRMETER3_MAX_CURRENT               90
#define PWRMETER3_DEF_AVG_SAMPLES           500u

/**
 * @brief PWR Meter 3 device address setting.
 * @details Specified setting for device slave address selection of
 * PWR Meter 3 Click driver.
 */
#define PWRMETER3_DEVICE_ADDRESS_0          0x60
#define PWRMETER3_DEVICE_ADDRESS_1          0x61
#define PWRMETER3_DEVICE_ADDRESS_2          0x64
#define PWRMETER3_DEVICE_ADDRESS_3          0x65

/*! @} */ // pwrmeter3_set

/**
 * @defgroup pwrmeter3_map PWR Meter 3 MikroBUS Map
 * @brief MikroBUS pin mapping of PWR Meter 3 Click driver.
 */

/**
 * @addtogroup pwrmeter3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PWR Meter 3 Click to the selected MikroBUS.
 */
#define PWRMETER3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.dio1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dio0 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pwrmeter3_map
/*! @} */ // pwrmeter3

/**
 * @brief PWR Meter 3 Click context object.
 * @details Context object definition of PWR Meter 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin. */
    
    // Input pins
    digital_in_t dio1;          /**< DIO1 pin. */
    digital_in_t dio0;          /**< DIO0 pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    
    uint8_t bypass_n_en;        /**< Bypass N enable setting. */

} pwrmeter3_t;

/**
 * @brief PWR Meter 3 Click configuration object.
 * @details Configuration object definition of PWR Meter 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t dio1;            /**< DIO1 pin. */
    pin_name_t dio0;            /**< DIO0 pin. */
    pin_name_t en;              /**< Enable pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} pwrmeter3_cfg_t;

/**
 * @brief PWR Meter 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PWRMETER3_OK = 0,
    PWRMETER3_ERROR = -1

} pwrmeter3_return_value_t;

/*!
 * @addtogroup pwrmeter3 PWR Meter 3 Click Driver
 * @brief API for configuring and manipulating PWR Meter 3 Click driver.
 * @{
 */

/**
 * @brief PWR Meter 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pwrmeter3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pwrmeter3_cfg_setup ( pwrmeter3_cfg_t *cfg );

/**
 * @brief PWR Meter 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pwrmeter3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pwrmeter3_init ( pwrmeter3_t *ctx, pwrmeter3_cfg_t *cfg );

/**
 * @brief PWR Meter 3 default configuration function.
 * @details This function executes a default configuration of PWR Meter 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pwrmeter3_default_cfg ( pwrmeter3_t *ctx );

/**
 * @brief PWR Meter 3 write register function.
 * @details This function writes a desired 32-bit data to the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 32-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pwrmeter3_write_register ( pwrmeter3_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief PWR Meter 3 read register function.
 * @details This function reads a 32-bit data from the selected register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pwrmeter3_read_register ( pwrmeter3_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief PWR Meter 3 get dio0 pin function.
 * @details This function returns the DIO0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t pwrmeter3_get_dio0_pin ( pwrmeter3_t *ctx );

/**
 * @brief PWR Meter 3 get dio1 pin function.
 * @details This function returns the DIO1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t pwrmeter3_get_dio1_pin ( pwrmeter3_t *ctx );

/**
 * @brief PWR Meter 3 enable device function.
 * @details This function enables device by setting the EN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void pwrmeter3_enable_device ( pwrmeter3_t *ctx );

/**
 * @brief PWR Meter 3 disable device function.
 * @details This function disables device by setting the EN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void pwrmeter3_disable_device ( pwrmeter3_t *ctx );

/**
 * @brief PWR Meter 3 allow write access function.
 * @details This function allows writing to registers by setting the correct write access code.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pwrmeter3_allow_write_access ( pwrmeter3_t *ctx );

/**
 * @brief PWR Meter 3 deny write access function.
 * @details This function denies writing to registers by setting the wrong write access code.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pwrmeter3_deny_write_access ( pwrmeter3_t *ctx );

/**
 * @brief PWR Meter 3 set bypass n state function.
 * @details This function sets whether RMS is calculated based on voltage zero crossing (AC measurement)
 * or predefined num samples (DC measurement).
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Disable N - RMS is calculated based on voltage zero crossing (AC measurement),
 *                    @li @c 1 - Enable N - RMS is calculated based on predefined num samples (DC measurement),
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Writing to registers must be allowed using @b pwrmeter3_allow_write_access function.
 */
err_t pwrmeter3_set_bypass_n_state ( pwrmeter3_t *ctx, uint8_t state );

/**
 * @brief PWR Meter 3 set num samples function.
 * @details This function sets the number of samples for RMS calculations.
 * Bypass N state must be set/true for this to have effect.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @param[in] num_samples : 0-1023 samples,
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Writing to registers must be allowed using @b pwrmeter3_allow_write_access function.
 */
err_t pwrmeter3_set_num_samples ( pwrmeter3_t *ctx, uint16_t num_samples );

/**
 * @brief PWR Meter 3 set dio0 sel function.
 * @details This function sets the DIO0 selection. Determines which flags are output on the DIO0 pin.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @param[in] dio_sel : @li @c 0 - ZC: zero crossing,
 *                      @li @c 1 - ovrms: the VRMS overvoltage flag (Default).
 *                      @li @c 2 - uvrms: the VRMS undervoltage flag.
 *                      @li @c 3 - The OR of ovrms and uvrms (if either flag is triggered, the DIO_0 pin will be asserted).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Writing to registers must be allowed using @b pwrmeter3_allow_write_access function.
 */
err_t pwrmeter3_set_dio0_sel ( pwrmeter3_t *ctx, uint8_t dio_sel );

/**
 * @brief PWR Meter 3 set dio1 sel function.
 * @details This function sets the DIO1 selection. Determines which flags are output on the DIO1 pin.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @param[in] dio_sel : @li @c 0 - OCF: Overcurrent fault,
 *                      @li @c 1 - uvrms: the VRMS undervoltage flag (Default),
 *                      @li @c 2 - ovrms: the VRMS overvoltage flag,
 *                      @li @c 3 - The OR of ovrms and uvrms, and OCF_LAT [Latched Overcurrent Fault].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Writing to registers must be allowed using @b pwrmeter3_allow_write_access function.
 */
err_t pwrmeter3_set_dio1_sel ( pwrmeter3_t *ctx, uint8_t dio_sel );

/**
 * @brief PWR Meter 3 set ovrms threshold function.
 * @details This function sets the overvoltage RMS threshold.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @param[in] ovrms : 0-63 steps, a single step represents about 9.3V,
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Writing to registers must be allowed using @b pwrmeter3_allow_write_access function.
 */
err_t pwrmeter3_set_ovrms_threshold ( pwrmeter3_t *ctx, uint8_t ovrms );

/**
 * @brief PWR Meter 3 set uvrms threshold function.
 * @details This function sets the undervoltage RMS threshold.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @param[in] uvrms : 0-63 steps, a single step represents about 9.3V,
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Writing to registers must be allowed using @b pwrmeter3_allow_write_access function.
 */
err_t pwrmeter3_set_uvrms_threshold ( pwrmeter3_t *ctx, uint8_t uvrms );

/**
 * @brief PWR Meter 3 read rms function.
 * @details This function reads the voltage and current RMS measurements.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @param[out] v_rms : Voltage RMS measurement in Volts.
 * @param[out] i_rms : Current RMS measurement in Ampers.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pwrmeter3_read_rms ( pwrmeter3_t *ctx, float *v_rms, float *i_rms );

/**
 * @brief PWR Meter 3 read average rms function.
 * @details This function reads the voltage and current RMS measurements averaged from
 * a specified number of samples.
 * @param[in] ctx : Click context object.
 * See #pwrmeter3_t object definition for detailed explanation.
 * @param[out] v_rms : Averaged voltage RMS measurement in Volts.
 * @param[out] i_rms : Averaged current RMS measurement in Ampers.
 * @param[in] num_avg : Number of samples for averaging RMS measurements.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pwrmeter3_read_average_rms ( pwrmeter3_t *ctx, float *v_rms, float *i_rms, uint16_t num_avg );

#ifdef __cplusplus
}
#endif
#endif // PWRMETER3_H

/*! @} */ // pwrmeter3

// ------------------------------------------------------------------------ END
