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
 * @file stepdown12.h
 * @brief This file contains API for Step Down 12 Click Driver.
 */

#ifndef STEPDOWN12_H
#define STEPDOWN12_H

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
 * @addtogroup stepdown12 Step Down 12 Click Driver
 * @brief API for configuring and manipulating Step Down 12 Click driver.
 * @{
 */

/**
 * @defgroup stepdown12_set Step Down 12 Settings
 * @brief Settings of Step Down 12 Click driver.
 */

/**
 * @addtogroup stepdown12_set
 * @{
 */

/**
 * @brief Step Down 12 digipot settings.
 * @details Specified digipot settings of Step Down 12 Click driver.
 */
#define STEPDOWN12_DIGIPOT_MAX_VALUE        100000ul
#define STEPDOWN12_DIGIPOT_MIN_VALUE        0
#define STEPDOWN12_DIGIPOT_RESOLUTION       256
#define STEPDOWN12_ROUND_TO_NEAREST_INT     0.5
#define STEPDOWN12_WIPER_RESISTANCE         75

/**
 * @brief Step Down 12 voltage calculation.
 * @details Specified voltage calculation of Step Down 12 Click driver.
 */
#define STEPDOWN12_R1                       82000ul
#define STEPDOWN12_R2                       10000ul
#define STEPDOWN12_VFB                      0.6f
#define STEPDOWN12_VOUT_MIN                 1.05f
#define STEPDOWN12_VOUT_MAX                 5.5f

/**
 * @brief Step Down 12 device address setting.
 * @details Specified setting for device slave address selection of
 * Step Down 12 Click driver.
 */
#define STEPDOWN12_ADDR_A2A1A0_000          0x28
#define STEPDOWN12_ADDR_A2A1A0_001          0x29
#define STEPDOWN12_ADDR_A2A1A0_010          0x2A
#define STEPDOWN12_ADDR_A2A1A0_011          0x2B
#define STEPDOWN12_ADDR_A2A1A0_100          0x2C
#define STEPDOWN12_ADDR_A2A1A0_101          0x2D
#define STEPDOWN12_ADDR_A2A1A0_110          0x2E
#define STEPDOWN12_ADDR_A2A1A0_111          0x2F

/*! @} */ // stepdown12_set

/**
 * @defgroup stepdown12_map Step Down 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Step Down 12 Click driver.
 */

/**
 * @addtogroup stepdown12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Step Down 12 Click to the selected MikroBUS.
 */
#define STEPDOWN12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.mode = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepdown12_map
/*! @} */ // stepdown12

/**
 * @brief Step Down 12 Click context object.
 * @details Context object definition of Step Down 12 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t mode;     /**< Mode selection (Low - Auto PFM/PWM with AEE, High - Forced PWM). */
    digital_out_t en;       /**< Enable pin (Active high). */

    // Input pins
    digital_in_t pg;        /**< Power good pin (High - VOUT is ready). */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} stepdown12_t;

/**
 * @brief Step Down 12 Click configuration object.
 * @details Configuration object definition of Step Down 12 Click driver.
 */
typedef struct
{
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t mode;        /**< Mode selection (Low - Auto PFM/PWM with AEE, High - Forced PWM). */
    pin_name_t en;          /**< Enable pin (Active high). */
    pin_name_t pg;          /**< Power good pin (High - VOUT is ready). */

    uint32_t   i2c_speed;   /**< I2C serial speed. */
    uint8_t    i2c_address; /**< I2C slave address. */

} stepdown12_cfg_t;

/**
 * @brief Step Down 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPDOWN12_OK = 0,
    STEPDOWN12_ERROR = -1

} stepdown12_return_value_t;

/*!
 * @addtogroup stepdown12 Step Down 12 Click Driver
 * @brief API for configuring and manipulating Step Down 12 Click driver.
 * @{
 */

/**
 * @brief Step Down 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepdown12_cfg_setup ( stepdown12_cfg_t *cfg );

/**
 * @brief Step Down 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepdown12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepdown12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown12_init ( stepdown12_t *ctx, stepdown12_cfg_t *cfg );

/**
 * @brief Step Down 12 default configuration function.
 * @details This function executes a default configuration of Step Down 12
 * Click board.
 * @param[in] ctx : Click context object.
 * See #stepdown12_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void stepdown12_default_cfg ( stepdown12_t *ctx );

/**
 * @brief Step Down 12 set resistance function.
 * @details This function sets the digipot wiper resistance by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepdown12_t object definition for detailed explanation.
 * @param[in] res_ohm : Resistance value in Ohms [0 to 100000 Ohm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown12_set_resistance ( stepdown12_t *ctx, uint32_t res_ohm );

/**
 * @brief Step Down 12 set vout function.
 * @details This function sets the voltage output by setting the digipot wiper resistance.
 * @param[in] ctx : Click context object.
 * See #stepdown12_t object definition for detailed explanation.
 * @param[in] vout : Voltage output to be set [1.05 to 5.5 V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown12_set_vout ( stepdown12_t *ctx, float vout );

/**
 * @brief Step Down 12 get pg pin function.
 * @details This function returns the power good (PG) pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown12_t object definition for detailed explanation.
 * @return PG pin logic state.
 * @note None.
 */
uint8_t stepdown12_get_pg_pin ( stepdown12_t *ctx );

/**
 * @brief Step Down 12 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown12_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown12_enable_device ( stepdown12_t *ctx );

/**
 * @brief Step Down 12 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown12_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown12_disable_device ( stepdown12_t *ctx );

/**
 * @brief Step Down 12 mode forced pwm function.
 * @details This function sets the device to forced PWM mode by setting the MODE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown12_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown12_mode_forced_pwm ( stepdown12_t *ctx );

/**
 * @brief Step Down 12 mode auto pwm function.
 * @details This function sets the device to auto PWM mode by setting the MODE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown12_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown12_mode_auto_pwm ( stepdown12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // STEPDOWN12_H

/*! @} */ // stepdown12

// ------------------------------------------------------------------------ END
