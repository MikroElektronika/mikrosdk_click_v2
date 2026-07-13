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
 * @file buckboost6.h
 * @brief This file contains API for Buck-Boost 6 Click Driver.
 */

#ifndef BUCKBOOST6_H
#define BUCKBOOST6_H

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
 * @addtogroup buckboost6 Buck-Boost 6 Click Driver
 * @brief API for configuring and manipulating Buck-Boost 6 Click driver.
 * @{
 */

/**
 * @defgroup buckboost6_reg Buck-Boost 6 Registers List
 * @brief List of registers of Buck-Boost 6 Click driver.
 */

/**
 * @addtogroup buckboost6_reg
 * @{
 */

/**
 * @brief Buck-Boost 6 register map.
 * @details Specified register map of Buck-Boost 6 Click driver.
 */
#define BUCKBOOST6_REG_CONTROL                  0x01
#define BUCKBOOST6_REG_STATUS                   0x02
#define BUCKBOOST6_REG_DEVID                    0x03
#define BUCKBOOST6_REG_VOUT1                    0x04
#define BUCKBOOST6_REG_VOUT2                    0x05

/*! @} */ // buckboost6_reg

/**
 * @defgroup buckboost6_set Buck-Boost 6 Registers Settings
 * @brief Settings for registers of Buck-Boost 6 Click driver.
 */

/**
 * @addtogroup buckboost6_set
 * @{
 */

/**
 * @brief Buck-Boost 6 CONTROL register setting.
 * @details Specified setting for CONTROL register of Buck-Boost 6 Click driver.
 */
#define BUCKBOOST6_CONTROL_SDA_SLEW_HIGH        0x00
#define BUCKBOOST6_CONTROL_SDA_SLEW_MEDIUM      0x20
#define BUCKBOOST6_CONTROL_SDA_SLEW_LOW         0x40
#define BUCKBOOST6_CONTROL_SDA_SLEW_VERY_LOW    0x60
#define BUCKBOOST6_CONTROL_SDA_SLEW_MASK        0x60
#define BUCKBOOST6_CONTROL_ULTRASONIC_DIS       0x00
#define BUCKBOOST6_CONTROL_ULTRASONIC_EN        0x10
#define BUCKBOOST6_CONTROL_ULTRASONIC_MASK      0x10
#define BUCKBOOST6_CONTROL_FORCED_PWM_DIS       0x00
#define BUCKBOOST6_CONTROL_FORCED_PWM_EN        0x08
#define BUCKBOOST6_CONTROL_FORCED_PWM_MASK      0x08
#define BUCKBOOST6_CONTROL_RAMP_PWM_DIS         0x00
#define BUCKBOOST6_CONTROL_RAMP_PWM_EN          0x04
#define BUCKBOOST6_CONTROL_RAMP_PWM_MASK        0x04
#define BUCKBOOST6_CONTROL_DVS_SLEW_1V_MS       0x00
#define BUCKBOOST6_CONTROL_DVS_SLEW_2V5_MS      0x01
#define BUCKBOOST6_CONTROL_DVS_SLEW_5V_MS       0x02
#define BUCKBOOST6_CONTROL_DVS_SLEW_10V_MS      0x03
#define BUCKBOOST6_CONTROL_DVS_SLEW_MASK        0x03

/**
 * @brief Buck-Boost 6 STATUS register setting.
 * @details Specified setting for STATUS register of Buck-Boost 6 Click driver.
 */
#define BUCKBOOST6_STATUS_VINUV                 0x10
#define BUCKBOOST6_STATUS_UV                    0x08
#define BUCKBOOST6_STATUS_OC                    0x04
#define BUCKBOOST6_STATUS_TSD                   0x02
#define BUCKBOOST6_STATUS_NPG                   0x01

/**
 * @brief Buck-Boost 6 DEVID register setting.
 * @details Specified setting for DEVID register of Buck-Boost 6 Click driver.
 */
#define BUCKBOOST6_DEVID_MANUFACTURER_RICHTEK   0xB0
#define BUCKBOOST6_DEVID_MANUFACTURER_MASK      0xF0
#define BUCKBOOST6_DEVID_MAJOR_MASK             0x0C
#define BUCKBOOST6_DEVID_MINOR_MASK             0x03

/**
 * @brief Buck-Boost 6 VOUT register setting.
 * @details Specified setting for VOUT registers of Buck-Boost 6 Click driver.
 */
#define BUCKBOOST6_VOUT_MIN_MV                  1800
#define BUCKBOOST6_VOUT_MAX_MV                  4975
#define BUCKBOOST6_VOUT_STEP_MV                 25
#define BUCKBOOST6_VOUT_MASK                    0x7F
#define BUCKBOOST6_VOUT_DEFAULT_MV              2500

/**
 * @brief Buck-Boost 6 device address setting.
 * @details Specified setting for device slave address selection of
 * Buck-Boost 6 Click driver.
 */
#define BUCKBOOST6_DEVICE_ADDRESS               0x75

/*! @} */ // buckboost6_set

/**
 * @defgroup buckboost6_map Buck-Boost 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Buck-Boost 6 Click driver.
 */

/**
 * @addtogroup buckboost6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck-Boost 6 Click to the selected MikroBUS.
 */
#define BUCKBOOST6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sel = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // buckboost6_map
/*! @} */ // buckboost6

/**
 * @brief Buck-Boost 6 Click context object.
 * @details Context object definition of Buck-Boost 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Device enable pin (active high). */

    // Input pins
    digital_in_t sel;           /**< VOUT selection pin (low-VOUT1, high-VOUT2). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} buckboost6_t;

/**
 * @brief Buck-Boost 6 Click configuration object.
 * @details Configuration object definition of Buck-Boost 6 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Device enable pin (active high). */
    pin_name_t sel;             /**< VOUT selection pin (low-VOUT1, high-VOUT2). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} buckboost6_cfg_t;

/**
 * @brief Buck-Boost 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUCKBOOST6_OK = 0,
    BUCKBOOST6_ERROR = -1

} buckboost6_return_value_t;

/*!
 * @addtogroup buckboost6 Buck-Boost 6 Click Driver
 * @brief API for configuring and manipulating Buck-Boost 6 Click driver.
 * @{
 */

/**
 * @brief Buck-Boost 6 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buckboost6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buckboost6_cfg_setup ( buckboost6_cfg_t *cfg );

/**
 * @brief Buck-Boost 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #buckboost6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buckboost6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost6_init ( buckboost6_t *ctx, buckboost6_cfg_t *cfg );

/**
 * @brief Buck-Boost 6 default configuration function.
 * @details This function executes a default configuration of Buck-Boost 6
 * Click board.
 * @param[in] ctx : Click context object.
 * See #buckboost6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t buckboost6_default_cfg ( buckboost6_t *ctx );

/**
 * @brief Buck-Boost 6 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #buckboost6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost6_write_reg ( buckboost6_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Buck-Boost 6 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #buckboost6_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost6_read_reg ( buckboost6_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Buck-Boost 6 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #buckboost6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void buckboost6_enable_device ( buckboost6_t *ctx );

/**
 * @brief Buck-Boost 6 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #buckboost6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void buckboost6_disable_device ( buckboost6_t *ctx );

/**
 * @brief Buck-Boost 6 get SEL pin function.
 * @details This function returns the SEL pin logic state.
 * @param[in] ctx : Click context object.
 * See #buckboost6_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t buckboost6_get_sel_pin ( buckboost6_t *ctx );

/**
 * @brief Buck-Boost 6 check com function.
 * @details This function check communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #buckboost6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buckboost6_check_com ( buckboost6_t *ctx );

/**
 * @brief Buck-Boost 6 set VOUT function.
 * @details This function sets the VOUT output voltage.
 * @param[in] ctx : Click context object.
 * See #buckboost6_t object definition for detailed explanation.
 * @param[in] voltage_mv : Output voltage in millivolts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note VOUT register is selected with the VSEL on-board switch.
 */
err_t buckboost6_set_vout ( buckboost6_t *ctx, uint16_t voltage_mv );

#ifdef __cplusplus
}
#endif
#endif // BUCKBOOST6_H

/*! @} */ // buckboost6

// ------------------------------------------------------------------------ END
