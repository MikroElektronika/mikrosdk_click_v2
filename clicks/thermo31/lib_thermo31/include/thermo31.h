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
 * @file thermo31.h
 * @brief This file contains API for Thermo 31 Click Driver.
 */

#ifndef THERMO31_H
#define THERMO31_H

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
 * @addtogroup thermo31 Thermo 31 Click Driver
 * @brief API for configuring and manipulating Thermo 31 Click driver.
 * @{
 */

/**
 * @defgroup thermo31_reg Thermo 31 Registers List
 * @brief List of registers of Thermo 31 Click driver.
 */

/**
 * @addtogroup thermo31_reg
 * @{
 */

/**
 * @brief Thermo 31 register map.
 * @details Specified register map of Thermo 31 Click driver.
 */
#define THERMO31_REG_TEMP_RESULT                0x00
#define THERMO31_REG_CONFIGURATION              0x01
#define THERMO31_REG_TLOW_LIMIT                 0x02
#define THERMO31_REG_THIGH_LIMIT                0x03
#define THERMO31_REG_DEVICE_ID                  0x0B
#define THERMO31_REG_UNIQUE_ID0                 0x0C
#define THERMO31_REG_UNIQUE_ID1                 0x0D
#define THERMO31_REG_UNIQUE_ID2                 0x0E

/*! @} */ // thermo31_reg

/**
 * @defgroup thermo31_set Thermo 31 Registers Settings
 * @brief Settings for registers of Thermo 31 Click driver.
 */

/**
 * @addtogroup thermo31_set
 * @{
 */

/**
 * @brief Thermo 31 CONFIGURATION register setting.
 * @details Specified setting for CONFIGURATION register of Thermo 31 Click driver.
 */
#define THERMO31_CONFIGURATION_ONE_SHOT         0x8000
#define THERMO31_CONFIGURATION_FAULT_1          0x0000
#define THERMO31_CONFIGURATION_FAULT_2          0x0800
#define THERMO31_CONFIGURATION_FAULT_4          0x1000
#define THERMO31_CONFIGURATION_FAULT_6          0x1800
#define THERMO31_CONFIGURATION_FAULT_MASK       0x1800
#define THERMO31_CONFIGURATION_POLARITY_LOW     0x0000
#define THERMO31_CONFIGURATION_POLARITY_HIGH    0x0400
#define THERMO31_CONFIGURATION_POLARITY_MASK    0x0400
#define THERMO31_CONFIGURATION_MODE_CONTINUOUS  0x0000
#define THERMO31_CONFIGURATION_MODE_SHUTDOWN    0x0100
#define THERMO31_CONFIGURATION_MODE_MASK        0x0100
#define THERMO31_CONFIGURATION_CONV_RATE_4S     0x0000
#define THERMO31_CONFIGURATION_CONV_RATE_1S     0x0040
#define THERMO31_CONFIGURATION_CONV_RATE_0_25S  0x0080
#define THERMO31_CONFIGURATION_CONV_RATE_0_125S 0x00C0
#define THERMO31_CONFIGURATION_CONV_RATE_MASK   0x00C0
#define THERMO31_CONFIGURATION_ALERT_FLAG       0x0020
#define THERMO31_CONFIGURATION_AVG_NO_AVG       0x0000
#define THERMO31_CONFIGURATION_AVG_4X           0x0004
#define THERMO31_CONFIGURATION_AVG_8X           0x0008
#define THERMO31_CONFIGURATION_AVG_MOV_4X       0x000C
#define THERMO31_CONFIGURATION_AVG_MASK         0x000C
#define THERMO31_CONFIGURATION_RESERVED         0x6010
#define THERMO31_CONFIGURATION_DEFAULT          0x60D0

/**
 * @brief Thermo 31 temperature calculation setting.
 * @details Specified setting for temperature calculation of Thermo 31 Click driver.
 */
#define THERMO31_TEMP_RESOLUTION                0.0078125f

/**
 * @brief Thermo 31 device ID setting.
 * @details Specified setting for device ID of Thermo 31 Click driver.
 */
#define THERMO31_DEVICE_ID                      0x1180
#define THERMO31_DEVICE_ID_MASK                 0xFFF0
#define THERMO31_DEVICE_ID_REV_MASK             0x000F

/**
 * @brief Thermo 31 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermo 31 Click driver.
 */
#define THERMO31_DEVICE_ADDRESS                 0x48

/*! @} */ // thermo31_set

/**
 * @defgroup thermo31_map Thermo 31 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 31 Click driver.
 */

/**
 * @addtogroup thermo31_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 31 Click to the selected MikroBUS.
 */
#define THERMO31_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // thermo31_map
/*! @} */ // thermo31

/**
 * @brief Thermo 31 Click context object.
 * @details Context object definition of Thermo 31 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} thermo31_t;

/**
 * @brief Thermo 31 Click configuration object.
 * @details Configuration object definition of Thermo 31 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} thermo31_cfg_t;

/**
 * @brief Thermo 31 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO31_OK = 0,
    THERMO31_ERROR = -1

} thermo31_return_value_t;

/*!
 * @addtogroup thermo31 Thermo 31 Click Driver
 * @brief API for configuring and manipulating Thermo 31 Click driver.
 * @{
 */

/**
 * @brief Thermo 31 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo31_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo31_cfg_setup ( thermo31_cfg_t *cfg );

/**
 * @brief Thermo 31 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermo31_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo31_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo31_init ( thermo31_t *ctx, thermo31_cfg_t *cfg );

/**
 * @brief Thermo 31 default configuration function.
 * @details This function executes a default configuration of Thermo 31
 * Click board.
 * @param[in] ctx : Click context object.
 * See #thermo31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo31_default_cfg ( thermo31_t *ctx );

/**
 * @brief Therno 31 write register function.
 * @details This function writes a 16-bit data value to the selected register address.
 * @param[in] ctx : Click context object.
 * See #thermo31_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo31_write_reg ( thermo31_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Therno 31 read register function.
 * @details This function reads a 16-bit data value from the selected register address.
 * @param[in] ctx : Click context object.
 * See #thermo31_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the 16-bit output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo31_read_reg ( thermo31_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Therno 31 communication check function.
 * @details This function checks communication by reading the device ID register and
 * validating it against the expected device ID value.
 * @param[in] ctx : Click context object.
 * See #thermo31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo31_check_communication ( thermo31_t *ctx );

/**
 * @brief Therno 31 read unique ID function.
 * @details This function reads the three 16-bit words of the device unique ID and stores
 * them in the provided buffer.
 * @param[in] ctx : Click context object.
 * See #thermo31_t object definition for detailed explanation.
 * @param[out] unique_id : Pointer to the output buffer where unique ID words will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo31_read_unique_id ( thermo31_t *ctx, uint16_t *unique_id );

/**
 * @brief Therno 31 read temperature function.
 * @details This function reads the raw temperature result register and converts it to
 * temperature in degrees using the defined resolution.
 * @param[in] ctx : Click context object.
 * See #thermo31_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to the output temperature value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo31_read_temperature ( thermo31_t *ctx, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // THERMO31_H

/*! @} */ // thermo31

// ------------------------------------------------------------------------ END
