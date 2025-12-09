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
 * @file pac1811.h
 * @brief This file contains API for PAC1811 Click Driver.
 */

#ifndef PAC1811_H
#define PAC1811_H

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
 * @addtogroup pac1811 PAC1811 Click Driver
 * @brief API for configuring and manipulating PAC1811 Click driver.
 * @{
 */

/**
 * @defgroup pac1811_reg PAC1811 Registers List
 * @brief List of registers of PAC1811 Click driver.
 */

/**
 * @addtogroup pac1811_reg
 * @{
 */

/**
 * @brief PAC1811 register list.
 * @details Specified register list of PAC1811 Click driver.
 */
#define PAC1811_REG_REFRESH                     0x00
#define PAC1811_REG_CTRL                        0x01
#define PAC1811_REG_ACC_COUNT                   0x02
#define PAC1811_REG_VACC                        0x03
#define PAC1811_REG_VBUS                        0x04
#define PAC1811_REG_VSENSE                      0x05
#define PAC1811_REG_VBUS_AVG                    0x06
#define PAC1811_REG_VSENSE_AVG                  0x07
#define PAC1811_REG_VPOWER                      0x08
#define PAC1811_REG_VBUS_MIN                    0x09
#define PAC1811_REG_VBUS_MAX                    0x0A
#define PAC1811_REG_VSENSE_MIN                  0x0B
#define PAC1811_REG_VSENSE_MAX                  0x0C
#define PAC1811_REG_VPOWER_MIN                  0x0D
#define PAC1811_REG_VPOWER_MAX                  0x0E
#define PAC1811_REG_CTRL_LAT                    0x0F
#define PAC1811_REG_NEG_PWR_FSR_LAT             0x10
#define PAC1811_REG_ALERT_STATUS                0x11
#define PAC1811_REG_SMBUS_SETTINGS              0x12
#define PAC1811_REG_NEG_PWR_FSR                 0x13
#define PAC1811_REG_REFRESH_G                   0x14
#define PAC1811_REG_REFRESH_V                   0x15
#define PAC1811_REG_SLOW                        0x16
#define PAC1811_REG_CTRL_ACT                    0x17
#define PAC1811_REG_NEG_PWR_FSR_ACT             0x18
#define PAC1811_REG_SLOW_ALERT1                 0x19
#define PAC1811_REG_GPIO_ALERT2                 0x1A
#define PAC1811_REG_ACC_FULLNESS_LIMITS         0x1B
#define PAC1811_REG_OC_LIMIT                    0x1C
#define PAC1811_REG_UC_LIMIT                    0x1D
#define PAC1811_REG_OP_WARNING_LIMIT            0x1E
#define PAC1811_REG_OP_CRITICAL_LIMIT           0x1F
#define PAC1811_REG_OV_LIMIT                    0x20
#define PAC1811_REG_UV_LIMIT                    0x21
#define PAC1811_REG_STEP_LIMIT                  0x22
#define PAC1811_REG_LIMIT_NSAMPLES              0x23
#define PAC1811_REG_ALERT_ENABLE                0x24
#define PAC1811_REG_ACCUMULATOR_COUNT_PRESET    0x25
#define PAC1811_REG_ACCUMULATOR_PRESET          0x26
#define PAC1811_REG_PRODUCT_ID                  0xFD
#define PAC1811_REG_MANUFACTURER_ID             0xFE
#define PAC1811_REG_REVISION_ID                 0xFF

/*! @} */ // pac1811_reg

/**
 * @defgroup pac1811_set PAC1811 Registers Settings
 * @brief Settings for registers of PAC1811 Click driver.
 */

/**
 * @addtogroup pac1811_set
 * @{
 */

/**
 * @brief PAC1811 FSR setting.
 * @details Specified setting for FSR of PAC1811 Click driver.
 */
#define PAC1811_FSR_UNIPOLAR                    0
#define PAC1811_FSR_BIPOLAR                     1
#define PAC1811_FSR_BIPOLAR_HALF                2

/**
 * @brief PAC1811 measurement calculation setting.
 * @details Specified setting for measurement calculation of PAC1811 Click driver.
 */
#define PAC1811_R9_RSENSE                       0.01
#define PAC1811_VSENSE_MAX                      0.1
#define PAC1811_VSOURCE_MAX                     42.0
#define PAC1811_FSC                             ( PAC1811_VSENSE_MAX / PAC1811_R9_RSENSE )
#define PAC1811_POWER_FSR                       ( PAC1811_FSC * PAC1811_VSOURCE_MAX )

/**
 * @brief PAC1811 device ID setting.
 * @details Specified setting for device ID of PAC1811 Click driver.
 */
#define PAC1811_PRODUCT_ID                      0x84
#define PAC1811_MANUFACTURER_ID                 0x54

/**
 * @brief PAC1811 device address setting.
 * @details Specified setting for device slave address selection of
 * PAC1811 Click driver.
 */
#define PAC1811_DEVICE_ADDRESS_GENERAL_CALL     0x00
#define PAC1811_DEVICE_ADDRESS_A1A0_GND_GND     0x40
#define PAC1811_DEVICE_ADDRESS_A1A0_GND_VCC     0x41
#define PAC1811_DEVICE_ADDRESS_A1A0_VCC_GND     0x44
#define PAC1811_DEVICE_ADDRESS_A1A0_VCC_VCC     0x45
#define PAC1811_DEVICE_ADDRESS_A1A0_SDA_GND     0x48
#define PAC1811_DEVICE_ADDRESS_A1A0_SDA_VCC     0x49
#define PAC1811_DEVICE_ADDRESS_A1A0_SCL_GND     0x4C
#define PAC1811_DEVICE_ADDRESS_A1A0_SCL_VCC     0x4D

/*! @} */ // pac1811_set

/**
 * @defgroup pac1811_map PAC1811 MikroBUS Map
 * @brief MikroBUS pin mapping of PAC1811 Click driver.
 */

/**
 * @addtogroup pac1811_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PAC1811 Click to the selected MikroBUS.
 */
#define PAC1811_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.a1_pin = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // pac1811_map
/*! @} */ // pac1811

/**
 * @brief PAC1811 Click data object.
 * @details Data object definition of PAC1811 Click driver.
 */
typedef struct
{
    uint32_t acc_count;         /**< Accumulator count value. */
    uint32_t acc_data_msb;      /**< Accumulator output data MSB [55:32]. */
    uint32_t acc_data_lsb;      /**< Accumulator output data LSB [31:0]. */
    float vbus;                 /**< VBUS measurement [V]. */
    float isense;               /**< ISENSE measurement [A]. */
    float vbus_avg;             /**< VBUS average on most recent measurements [V]. */
    float isense_avg;           /**< ISENSE average on most recent measurements [A]. */
    float power;                /**< POWER measurement [W]. */
    float vbus_min;             /**< VBUS minimum measurement [V]. */
    float vbus_max;             /**< VBUS maximum measurement [V]. */
    float isense_min;           /**< ISENSE minimum measurement [A]. */
    float isense_max;           /**< ISENSE maximum measurement [A]. */
    float power_min;            /**< POWER minimum measurement [W]. */
    float power_max;            /**< POWER maximum measurement [W]. */

} pac1811_data_t;

/**
 * @brief PAC1811 Click context object.
 * @details Context object definition of PAC1811 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pwr;          /**< Power shutdown pin (active low). */

    // Input pins
    digital_in_t a1_pin;        /**< Address/Alert 1 pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint8_t vsense_fsr;         /**< VSENSE full scale range setting. */
    uint8_t vbus_fsr;           /**< VBUS full scale range setting. */

} pac1811_t;

/**
 * @brief PAC1811 Click configuration object.
 * @details Configuration object definition of PAC1811 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t pwr;             /**< Power shutdown pin (active low). */
    pin_name_t a1_pin;          /**< Address/Alert 1 pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} pac1811_cfg_t;

/**
 * @brief PAC1811 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PAC1811_OK = 0,
    PAC1811_ERROR = -1

} pac1811_return_value_t;

/*!
 * @addtogroup pac1811 PAC1811 Click Driver
 * @brief API for configuring and manipulating PAC1811 Click driver.
 * @{
 */

/**
 * @brief PAC1811 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pac1811_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pac1811_cfg_setup ( pac1811_cfg_t *cfg );

/**
 * @brief PAC1811 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pac1811_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1811_init ( pac1811_t *ctx, pac1811_cfg_t *cfg );

/**
 * @brief PAC1811 default configuration function.
 * @details This function executes a default configuration of PAC1811
 * Click board.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t pac1811_default_cfg ( pac1811_t *ctx );

/**
 * @brief PAC1811 send single byte function.
 * @details This function transmits a single byte on the I2C bus.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @param[in] data_in : Data byte to send.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1811_send_byte ( pac1811_t *ctx, uint8_t data_in );

/**
 * @brief PAC1811 receive single byte function.
 * @details This function receives a single byte from the I2C bus.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @param[out] data_out : Output read data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1811_receive_byte ( pac1811_t *ctx, uint8_t *data_out );

/**
 * @brief PAC1811 write register function.
 * @details This function writes a single byte to the selected register address.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1811_write_byte ( pac1811_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief PAC1811 read register function.
 * @details This function reads a single byte from the selected register address.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1811_read_byte ( pac1811_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief PAC1811 write registers function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register address.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data buffer to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1811_block_write ( pac1811_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief PAC1811 read registers function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register address.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data buffer.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1811_block_read ( pac1811_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief PAC1811 communication check function.
 * @details This function verifies communication by reading product and manufacturer IDs
 * and comparing them against expected values.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @return @li @c  0 - Success (IDs match),
 *         @li @c -1 - Error (IDs mismatch or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1811_check_communication ( pac1811_t *ctx );

/**
 * @brief PAC1811 enable device function.
 * @details This function enables device by setting the PWR pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @return Non.
 * @note None.
 */
void pac1811_enable_device ( pac1811_t *ctx );

/**
 * @brief PAC1811 disable device function.
 * @details This function disables device by setting the PWR pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @return Non.
 * @note None.
 */
void pac1811_disable_device ( pac1811_t *ctx );

/**
 * @brief PAC1811 get A1 pin function.
 * @details This function reads the logic level of the A1 pin.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @return Pin state: @li @c 0 - Logic low,
 *                    @li @c 1 - Logic high.
 * @note None.
 */
uint8_t pac1811_get_a1_pin ( pac1811_t *ctx );

/**
 * @brief PAC1811 refresh function.
 * @details This function issues a REFRESH command to update measurement registers.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1811_refresh ( pac1811_t *ctx );

/**
 * @brief PAC1811 global refresh function.
 * @details This function sends a global REFRESH command via the general-call
 * address and then restores the device's slave address.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Temporarily switches to general-call address and restores it afterwards.
 */
err_t pac1811_refresh_global ( pac1811_t *ctx );

/**
 * @brief PAC1811 refresh without accumulator reset function.
 * @details This function issues a REFRESH_V command to update measurement registers
 * without resetting accumulators.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1811_refresh_wo_acc_reset ( pac1811_t *ctx );

/**
 * @brief PAC1811 set full-scale ranges function.
 * @details This function configures full-scale ranges (FSR) for V(SENSE) and V(BUS).
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @param[in] vsense_fsr : V(SENSE) FSR selection (see @ref PAC1811_FSR_*).
 * @param[in] vbus_fsr : V(BUS) FSR selection (see @ref PAC1811_FSR_*).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error (invalid range or bus error).
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pac1811_set_fsr ( pac1811_t *ctx, uint8_t vsense_fsr, uint8_t vbus_fsr );

/**
 * @brief PAC1811 read measurement data function.
 * @details This function reads accumulated count, voltage, current, and power data,
 * and converts raw codes into SI units, storing the results to the output structure.
 * @param[in] ctx : Click context object.
 * See #pac1811_t object definition for detailed explanation.
 * @param[out] data_out : Output measurement data structure.
 * See #pac1811_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Conversion depends on configured FSRs.
 */
err_t pac1811_read_data ( pac1811_t *ctx, pac1811_data_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // PAC1811_H

/*! @} */ // pac1811

// ------------------------------------------------------------------------ END
