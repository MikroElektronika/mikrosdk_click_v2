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
 * @file force5.h
 * @brief This file contains API for Force 5 Click Driver.
 */

#ifndef FORCE5_H
#define FORCE5_H

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
 * @addtogroup force5 Force 5 Click Driver
 * @brief API for configuring and manipulating Force 5 Click driver.
 * @{
 */

/**
 * @defgroup force5_set Force 5 Registers Settings
 * @brief Settings for registers of Force 5 Click driver.
 */

/**
 * @addtogroup force5_set
 * @{
 */

/**
 * @brief Force 5 states.
 * @details Specified states of Force 5 Click driver.
 */
#define FORCE5_STATES_BIT_MASK                                        0x03
#define FORCE5_STATES_NORMAL_OPERATION                                0x00
#define FORCE5_STATES_COMMAND_MODE                                    0x01
#define FORCE5_STATES_STALE_DATA                                      0x02
#define FORCE5_STATES_DIAGNOSTIC_CONDITION                            0x03

/**
 * @brief Force 5 force calculation.
 * @details Specified setting for force calculation of Force 5 Click driver.
 */
#define FORCE5_FORCE_SENSOR_10_N                                      10.0
#define FORCE5_FORCE_SENSOR_25_N                                      25.0

#define FORCE5_FORCE_MAX_VALUE                                     14745.0

/**
 * @brief Force 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Force 5 Click driver.
 */
#define FORCE5_SET_DEV_ADDR  0x28

/*! @} */ // force5_set

/**
 * @defgroup force5_map Force 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Force 5 Click driver.
 */

/**
 * @addtogroup force5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Force 5 Click to the selected MikroBUS.
 */
#define FORCE5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // force5_map
/*! @} */ // force5

/**
 * @brief Force 5 Click context object.
 * @details Context object definition of Force 5 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} force5_t;

/**
 * @brief Force 5 Click configuration object.
 * @details Configuration object definition of Force 5 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} force5_cfg_t;

/**
 * @brief Force 5 Click data object.
 * @details Data object definition of Force 5 Click driver.
 */
typedef struct
{
    uint8_t status_data;
    uint16_t force_data;
    uint16_t temp_data;
}force5_data_t;

/**
 * @brief Force 5 Click calibration object.
 * @details Calibration object definition of Force 5 Click driver.
 */
typedef struct
{
    uint16_t force_claib_data;
}force5_calibration_t; 

/**
 * @brief Force 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   FORCE5_OK = 0,
   FORCE5_ERROR = -1

} force5_return_value_t;

/*!
 * @addtogroup force5 Force 5 Click Driver
 * @brief API for configuring and manipulating Force 5 Click driver.
 * @{
 */

/**
 * @brief Force 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #force5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void force5_cfg_setup ( force5_cfg_t *cfg );

/**
 * @brief Force 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #force5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #force5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t force5_init ( force5_t *ctx, force5_cfg_t *cfg );

/**
 * @brief Force 5 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #force5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t force5_generic_write ( force5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Force 5 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #force5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t force5_generic_read ( force5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Generic read data function.
 * @details The function read data is used 
 * to read multiple data bytes ( 2, 3 or 4 )
 * @param[in] ctx : Click context object.
 * See #force5_t object definition for detailed explanation.
 * @param[out] rx_data : Pointer to the memory location where data be stored.
 * @param[in] n_bytes : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t force5_read_byte ( force5_t *ctx, uint8_t *rx_data, uint8_t n_bytes );

/**
 * @brief Read all data function.
 * @details The function read all data and store to the structure
 * @param[in] ctx : Click context object.
 * See #force5_t object definition for detailed explanation.
 * @param[out] force_data : Pointer to the memory location where data be stored.
 * @return Nothing.
 */
void force5_read_all_data ( force5_t *ctx, force5_data_t *force_data );

/**
 * @brief Get force value function.
 * @details The function get force value.
 * @param[in] ctx : Click context object.
 * See #force5_t object definition for detailed explanation.
 * @param[out] force : Pointer to the memory location where 14-bit data be stored.
 * @return Force 5 states bit 
 * See #force5_set object definition for detailed explanation.
 */
uint8_t force5_get_force_value ( force5_t *ctx, uint16_t *force );

/**
 * @brief Get temperature value function.
 * @details The function get temperature value.
 * @param[in] ctx : Click context object.
 * See #force5_t object definition for detailed explanation.
 * @param[out] temp : Pointer to the memory location where 14-bit data be stored.
 * @return Force 5 states bit 
 * See #force5_set object definition for detailed explanation.
 */
uint8_t force5_get_temperature_value ( force5_t *ctx, uint16_t *temp );

/**
 * @brief Calibration the sensor function.
 * @details The function calibrate.
 * @param[in] ctx : Click context object.
 * See #force5_t object definition for detailed explanation.
 * @param[out] calib_data : Pointer to the memory location where data is stored.
 * @return Force 5 states bit 
 * See #force5_set object definition for detailed explanation.
 */
uint8_t force5_calibration ( force5_t *ctx, force5_calibration_t *calib_data );

/**
 * @brief Get force function.
 * @details The function get force.
 * @param[in] ctx : Click context object.
 * See #force5_t object definition for detailed explanation.
 * @param[in] calib_data : Structure where calibration data be stored.
 * @return Float force ( N ).
 */
float force5_get_force ( force5_t *ctx, force5_calibration_t calib_data );

/**
 * @brief Get temperature function.
 * @details The function get temperature.
 * @param[in] ctx : Click context object.
 * See #force5_t object definition for detailed explanation.
 * @return Float temperature ( degree Celsius ).
 */
float force5_get_temperature ( force5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // FORCE5_H

/*! @} */ // force5

// ------------------------------------------------------------------------ END
