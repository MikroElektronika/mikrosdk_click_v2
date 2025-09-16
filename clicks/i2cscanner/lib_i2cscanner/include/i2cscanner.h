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
 * @file i2cscanner.h
 * @brief This file contains API for I2C Scanner Driver.
 */

#ifndef I2CSCANNER_H
#define I2CSCANNER_H

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

/*!
 * @addtogroup i2cscanner I2C Scanner Driver
 * @brief API for configuring and manipulating I2C Scanner driver.
 * @{
 */

/**
 * @defgroup i2cscanner_set I2C Scanner Registers Settings
 * @brief Settings for registers of I2C Scanner driver.
 */

/**
 * @addtogroup i2cscanner_set
 * @{
 */

/**
 * @brief I2C Scanner I2C timeout setting.
 * @details Specified setting for I2C timeout of I2C Scanner driver.
 */
#define I2CSCANNER_I2C_TIMEOUT              100000ul

/*! @} */ // i2cscanner_set

/**
 * @defgroup i2cscanner_map I2C Scanner MikroBUS Map
 * @brief MikroBUS pin mapping of I2C Scanner driver.
 */

/**
 * @addtogroup i2cscanner_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C Scanner to the selected MikroBUS.
 */
#define I2CSCANNER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // i2cscanner_map
/*! @} */ // i2cscanner

/**
 * @brief I2C Scanner scan addresses object.
 * @details Scan addresses object definition of I2C Scanner driver.
 */
typedef struct
{
    uint8_t address[ 128 ];     /**< Slave addresses array. */
    uint8_t num_addr;           /**< Number of found addresses. */

} i2cscanner_scan_t;

/**
 * @brief I2C Scanner context object.
 * @details Context object definition of I2C Scanner driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint8_t i2c_started;        /**< I2C started flag. */

} i2cscanner_t;

/**
 * @brief I2C Scanner configuration object.
 * @details Configuration object definition of I2C Scanner driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

} i2cscanner_cfg_t;

/**
 * @brief I2C Scanner return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    I2CSCANNER_OK = 0,
    I2CSCANNER_ERROR = -1

} i2cscanner_return_value_t;

/*!
 * @addtogroup i2cscanner I2C Scanner Driver
 * @brief API for configuring and manipulating I2C Scanner driver.
 * @{
 */

/**
 * @brief I2C Scanner configuration object setup function.
 * @details This function initializes configuration structure to initial
 * values.
 * @param[out] cfg : Configuration structure.
 * See #i2cscanner_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void i2cscanner_cfg_setup ( i2cscanner_cfg_t *cfg );

/**
 * @brief I2C Scanner initialization function.
 * @details This function initializes all necessary pins and peripherals.
 * @param[out] ctx : Context object.
 * See #i2cscanner_t object definition for detailed explanation.
 * @param[in] cfg : Configuration structure.
 * See #i2cscanner_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cscanner_init ( i2cscanner_t *ctx, i2cscanner_cfg_t *cfg );

/**
 * @brief I2C Scanner scan I2C function.
 * @details This function scans the I2C bus for available slave addresses
 * and stores them into the scan structure.
 * @param[in] ctx : Context object.
 * See #i2cscanner_t object definition for detailed explanation.
 * @param[out] scan : Output scan results structure.
 * See #i2cscanner_scan_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cscanner_scan_i2c ( i2cscanner_t *ctx, i2cscanner_scan_t *scan );

#ifdef __cplusplus
}
#endif
#endif // I2CSCANNER_H

/*! @} */ // i2cscanner

// ------------------------------------------------------------------------ END
