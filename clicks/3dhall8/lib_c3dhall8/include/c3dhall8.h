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
 * @file c3dhall8.h
 * @brief This file contains API for 3D Hall 8 Click Driver.
 */

#ifndef C3DHALL8_H
#define C3DHALL8_H

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
 * @addtogroup c3dhall8 3D Hall 8 Click Driver
 * @brief API for configuring and manipulating 3D Hall 8 Click driver.
 * @{
 */

/**
 * @defgroup c3dhall8_reg 3D Hall 8 Registers List
 * @brief List of registers of 3D Hall 8 Click driver.
 */

/**
 * @addtogroup c3dhall8_reg
 * @{
 */

/**
 * @brief 3D Hall 8 description register.
 * @details Specified register for description of 3D Hall 8 Click driver.
 */
#define C3DHALL8_REG_MAGNETIC_X_MSB         0x00
#define C3DHALL8_REG_MAGNETIC_Y_MSB         0x01
#define C3DHALL8_REG_MAGENTIC_Z_MSB         0x02
#define C3DHALL8_REG_TEMPERATURE_MSB        0x03
#define C3DHALL8_REG_MAGNETIC_XY_LSB        0x04
#define C3DHALL8_REG_TEMPERATURE_Z_LSB      0x05
#define C3DHALL8_REG_STATUS                 0x06
#define C3DHALL8_REG_LOWER_THRESHOLD_X_MSB  0x07
#define C3DHALL8_REG_UPPER_THRESHOLD_X_MSB  0x08
#define C3DHALL8_REG_LOWER_THRESHOLD_Y_MSB  0x09
#define C3DHALL8_REG_UPPER_THRESHOLD_Y_MSB  0x0A
#define C3DHALL8_REG_LOWER_THRESHOLD_Z_MSB  0x0B
#define C3DHALL8_REG_UPPER_THRESHOLD_Z_MSB  0x0C
#define C3DHALL8_REG_THRESHOLDS_X_LSB       0x0D
#define C3DHALL8_REG_THRESHOLDS_Y_LSB       0x0E
#define C3DHALL8_REG_THRESHOLDS_Z_LSB       0x0F
#define C3DHALL8_REG_CONFIG_1               0x10
#define C3DHALL8_REG_MOD1                   0x11
#define C3DHALL8_REG_MOD2                   0x13
#define C3DHALL8_REG_CONFIG_2               0x14
#define C3DHALL8_REG_VERSION                0x16

/*! @} */ // c3dhall8_reg

/**
 * @defgroup c3dhall8_set 3D Hall 8 Registers Settings
 * @brief Settings for registers of 3D Hall 8 Click driver.
 */

/**
 * @addtogroup c3dhall8_set
 * @{
 */

/**
 * @brief 3D Hall 8 @b receiver_buff length
 * @details Macro for @b receiver_buff length in context object.
 */
#define C3DHALL8_RX_BUFFER 0x17

/**
 * @brief 3D Hall 8 device address setting.
 * @details Specified setting for device slave address selection of
 * 3D Hall 8 Click driver.
 */
#define C3DHALL8_SET_DEV_ADDR  0x35

/*! @} */ // c3dhall8_set

/**
 * @defgroup c3dhall8_map 3D Hall 8 MikroBUS Map
 * @brief MikroBUS pin mapping of 3D Hall 8 Click driver.
 */

/**
 * @addtogroup c3dhall8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3D Hall 8 Click to the selected MikroBUS.
 */
#define C3DHALL8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c3dhall8_map
/*! @} */ // c3dhall8

/**
 * @brief 3D Hall 8 Click context object.
 * @details Context object definition of 3D Hall 8 Click driver.
 */
typedef struct
{
    // Input pins
     digital_in_t  int_pin;       /**< Description. */

    // Modules
    i2c_master_t i2c;             /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;        /**< Device slave address (used for I2C driver). */
    
    uint8_t receiver_buff[ C3DHALL8_RX_BUFFER ];

} c3dhall8_t;

/**
 * @brief 3D Hall 8 Click configuration object.
 * @details Configuration object definition of 3D Hall 8 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;       /**< Description. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} c3dhall8_cfg_t;

/**
 * @brief 3D Hall 8 Click data object.
 * @details Data object definition of 3D Hall 8 Click driver.
 */
typedef struct
{
    float x_axis;
    float y_axis;
    float z_axis;
    float temperature;
    
} c3dhall8_data_t;

/**
 * @brief 3D Hall 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3DHALL8_OK = 0,
    C3DHALL8_ERROR = -1

} ismtx_return_value_t;

/*!
 * @addtogroup c3dhall8 3D Hall 8 Click Driver
 * @brief API for configuring and manipulating 3D Hall 8 Click driver.
 * @{
 */

/**
 * @brief 3D Hall 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3dhall8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void c3dhall8_cfg_setup ( c3dhall8_cfg_t *cfg );

/**
 * @brief 3D Hall 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c3dhall8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3dhall8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c3dhall8_init ( c3dhall8_t *ctx, c3dhall8_cfg_t *cfg );

/**
 * @brief 3D Hall 8 default configuration function.
 * @details This function executes a default configuration of 3D Hall 8
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c3dhall8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t c3dhall8_default_cfg ( c3dhall8_t *ctx );

/**
 * @brief 3D Hall 8 I2C writing function.
 * @details This function writes a data from the
 * selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c3dhall8_generic_write ( c3dhall8_t *ctx, uint8_t reg, uint8_t tx_buf );

/**
 * @brief 3D Hall 8 I2C reading function.
 * @details This function reads a data from the 
 * selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c3dhall8_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t c3dhall8_generic_read ( c3dhall8_t *ctx, uint8_t reg, uint8_t *rx_buf );

/**
 * @brief Reading sensor data function.
 * @details This function reads x, y, z axes and temperature from device.
 * @param[in] ctx : Click context object.
 * See #c3dhall8_t object definition for detailed explanation.
 * @param[out] sensor_data : Output sensor data.
 * See #c3dhall8_data_t object definition for detailed explanation.
 * @return Nothing.
 * See #err_t definition for detailed explanation.
 *
 * @endcode
 */
void c3dhall8_read_sensor_data ( c3dhall8_t *ctx, c3dhall8_data_t *sensor_data );

/**
 * @brief Calculating magnetic matching.
 * @details This function calculates magnetic matching from data @b sensor_data for x, y and z axes.
 * @param[in] ctx : Click context object.
 * See #c3dhall8_t object definition for detailed explanation.
 * @param[in] sensor_data : Read sensor data.
 * See #c3dhall8_data_t object definition for detailed explanation.
 * @return Calculated magnetic matching.
 * See #err_t definition for detailed explanation.
 *
 * @endcode
 */
float c3dhall8_get_xyz_magnetic_matching ( c3dhall8_t *ctx, c3dhall8_data_t sensor_data );

/**
 * @brief Calculating magnetic matching.
 * @details This function calculates magnetic matching from data @b sensor_data for x and y axes.
 * @param[in] ctx : Click context object.
 * See #c3dhall8_t object definition for detailed explanation.
 * @param[in] sensor_data : Read sensor data.
 * See #c3dhall8_data_t object definition for detailed explanation.
 * @return Calculated magnetic matching.
 * See #err_t definition for detailed explanation.
 *
 * @endcode
 */
float c3dhall8_get_xy_magnetic_matching ( c3dhall8_t *ctx, c3dhall8_data_t sensor_data );

#ifdef __cplusplus
}
#endif
#endif // C3DHALL8_H

/*! @} */ // c3dhall8

// ------------------------------------------------------------------------ END
