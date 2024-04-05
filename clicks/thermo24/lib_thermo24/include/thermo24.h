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
 * @file thermo24.h
 * @brief This file contains API for Thermo 24 Click Driver.
 */

#ifndef THERMO24_H
#define THERMO24_H

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
 * @addtogroup thermo24 Thermo 24 Click Driver
 * @brief API for configuring and manipulating Thermo 24 Click driver.
 * @{
 */

/**
 * @defgroup thermo24_cmd Thermo 24 Commands List
 * @brief List of commands of Thermo 24 Click driver.
 */

/**
 * @addtogroup thermo24_cmd
 * @{
 */

/**
 * @brief Thermo 24 commands list.
 * @details Specified commands list of Thermo 24 Click driver.
 */
#define THERMO24_CMD_MEASURE_HIGH_PRECISION     0xFD
#define THERMO24_CMD_MEASURE_MEDIUM_PRECISION   0xF6
#define THERMO24_CMD_MEASURE_LOWEST_PRECISION   0xE0
#define THERMO24_CMD_READ_SERIAL                0x89
#define THERMO24_CMD_SOFT_RESET                 0x94

/*! @} */ // thermo24_cmd

/**
 * @defgroup thermo24_set Thermo 24 Registers Settings
 * @brief Settings for registers of Thermo 24 Click driver.
 */

/**
 * @addtogroup thermo24_set
 * @{
 */

/**
 * @brief Thermo 24 temperature measurement precision selection.
 * @details Specified temperature measurement precision selection of Thermo 24 Click driver.
 */
#define THERMO24_MEASURE_PRECISION_LOW          0x00
#define THERMO24_MEASURE_PRECISION_MEDIUM       0x01
#define THERMO24_MEASURE_PRECISION_HIGH         0x02

/**
 * @brief Thermo 24 temperature calculation values.
 * @details Specified temperature calculation values of Thermo 24 Click driver.
 */
#define THERMO24_TEMP_RESOLUTION                0xFFFF
#define THERMO24_TEMP_MULTIPLIER_CELSIUS        175.0
#define THERMO24_TEMP_OFFSET                    45.0

/**
 * @brief Thermo 24 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermo 24 Click driver.
 */
#define THERMO24_SET_DEVICE_ADDRESS             0x44

/*! @} */ // thermo24_set

/**
 * @defgroup thermo24_map Thermo 24 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 24 Click driver.
 */

/**
 * @addtogroup thermo24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 24 Click to the selected MikroBUS.
 */
#define THERMO24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // thermo24_map
/*! @} */ // thermo24

/**
 * @brief Thermo 24 Click context object.
 * @details Context object definition of Thermo 24 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} thermo24_t;

/**
 * @brief Thermo 24 Click configuration object.
 * @details Configuration object definition of Thermo 24 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} thermo24_cfg_t;

/**
 * @brief Thermo 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO24_OK = 0,
    THERMO24_ERROR = -1

} thermo24_return_value_t;

/*!
 * @addtogroup thermo24 Thermo 24 Click Driver
 * @brief API for configuring and manipulating Thermo 24 Click driver.
 * @{
 */

/**
 * @brief Thermo 24 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo24_cfg_setup ( thermo24_cfg_t *cfg );

/**
 * @brief Thermo 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermo24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo24_init ( thermo24_t *ctx, thermo24_cfg_t *cfg );

/**
 * @brief Thermo 24 soft reset function.
 * @details This function performs the software reset by sending the soft reset command 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo24_soft_reset ( thermo24_t *ctx );

/**
 * @brief Thermo 24 read serial function.
 * @details This function reads the 4-byte chip serial number by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo24_t object definition for detailed explanation.
 * @param[out] serial_num : 4-byte unique chip serial number.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo24_read_serial ( thermo24_t *ctx, uint32_t *serial_num );

/**
 * @brief Thermo 24 read temperature function.
 * @details This function reads the temperature in Celsius with the specified measurement precision.
 * @param[in] ctx : Click context object.
 * See #thermo24_t object definition for detailed explanation.
 * @param[in] precision : Measurement precision
 *                        @li @c 0 - Low,
 *                        @li @c 1 - Medium,
 *                        @li @c 2 - High.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo24_read_temperature ( thermo24_t *ctx, uint8_t precision, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // THERMO24_H

/*! @} */ // thermo24

// ------------------------------------------------------------------------ END
