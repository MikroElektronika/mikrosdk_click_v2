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
 * @file airvelocity.h
 * @brief This file contains API for Air Velocity Click Driver.
 */

#ifndef AIRVELOCITY_H
#define AIRVELOCITY_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup airvelocity Air Velocity Click Driver
 * @brief API for configuring and manipulating Air Velocity Click driver.
 * @{
 */


/**
 * @defgroup airvelocity_set Air Velocity Registers Settings
 * @brief Settings for registers of Air Velocity Click driver.
 */

/**
 * @addtogroup airvelocity_set
 * @{
 */

/**
 * @brief Air Velocity description setting.
 * @details Specified setting for description of Air Velocity Click driver.
 */
// TODO -- dodati makroe koji definisu komande/vrednosti koje se upisuju u registre

/**
 * @brief Air Velocity device address setting.
 * @details Specified setting for device slave address selection of
 * Air Velocity Click driver.
 */
#define AIRVELOCITY_DEVICE_ADDRESS          0x28

/*! @} */ // airvelocity_set

/**
 * @defgroup airvelocity_map Air Velocity MikroBUS Map
 * @brief MikroBUS pin mapping of Air Velocity Click driver.
 */

/**
 * @addtogroup airvelocity_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Air Velocity Click to the selected MikroBUS.
 */
#define AIRVELOCITY_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // airvelocity_map
/*! @} */ // airvelocity

/**
 * @brief Air Velocity Click context object.
 * @details Context object definition of Air Velocity Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} airvelocity_t;

/**
 * @brief Air Velocity Click configuration object.
 * @details Configuration object definition of Air Velocity Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} airvelocity_cfg_t;

/**
 * @brief Air Velocity Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    AIRVELOCITY_OK = 0,
    AIRVELOCITY_ERROR = -1

} airvelocity_return_value_t;

/*!
 * @addtogroup airvelocity Air Velocity Click Driver
 * @brief API for configuring and manipulating Air Velocity Click driver.
 * @{
 */

/**
 * @brief Air Velocity configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #airvelocity_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void airvelocity_cfg_setup ( airvelocity_cfg_t *cfg );

/**
 * @brief Air Velocity initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #airvelocity_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #airvelocity_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airvelocity_init ( airvelocity_t *ctx, airvelocity_cfg_t *cfg );

/**
 * @brief Air Velocity read output function.
 * @details This function reads the raw output counts by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #airvelocity_t object definition for detailed explanation.
 * @param[out] out_counts : Output counts raw data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t airvelocity_read_output ( airvelocity_t *ctx, uint16_t *out_counts );

/**
 * @brief Air Velocity convert counts to mps function.
 * @details This function converts raw output counts to velocity in m/sec (0-7.23).
 * @param[in] out_counts : Output counts raw data.
 * @return Float value of velocity in m/sec (0-7.23).
 * @note None.
 */
float airvelocity_convert_counts_to_mps ( uint16_t out_counts );

#ifdef __cplusplus
}
#endif
#endif // AIRVELOCITY_H

/*! @} */ // airvelocity

// ------------------------------------------------------------------------ END
