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
 * @file counter2.h
 * @brief This file contains API for Counter 2 Click Driver.
 */

#ifndef COUNTER2_H
#define COUNTER2_H

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
 * @addtogroup counter2 Counter 2 Click Driver
 * @brief API for configuring and manipulating Counter 2 Click driver.
 * @{
 */

/**
 * @defgroup counter2_set Counter 2 Settings
 * @brief Settings of Counter 2 Click driver.
 */

/**
 * @addtogroup counter2_set
 * @{
 */

/**
 * @brief Counter 2 free data register setting.
 * @details Specified setting for free data register of Counter 2 Click driver.
 */
#define COUNTER2_FREE_DATA_READ         0x01
#define COUNTER2_FREE_DATA_WRITE        0x81
#define COUNTER2_FREE_DATA_RESET_CNT    0x02

/**
 * @brief Counter 2 loop counter setting.
 * @details Specified setting for loop counter of Counter 2 Click driver.
 */
#define COUNTER2_LOOP_IDLE              0
#define COUNTER2_LOOP_TOGGLED           1
#define COUNTER2_LOOP_THRESHOLD         16777216ul

/**
 * @brief Counter 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Counter 2 Click driver.
 */
#define COUNTER2_DEVICE_ADDRESS         0x32

/*! @} */ // counter2_set

/**
 * @defgroup counter2_map Counter 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Counter 2 Click driver.
 */

/**
 * @addtogroup counter2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Counter 2 Click to the selected MikroBUS.
 */
#define COUNTER2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.loop = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // counter2_map
/*! @} */ // counter2

/**
 * @brief Counter 2 Click context object.
 * @details Context object definition of Counter 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (active low). */

    // Input pins
    digital_in_t loop;          /**< Counter loop back to 0 pin (toggle). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} counter2_t;

/**
 * @brief Counter 2 Click configuration object.
 * @details Configuration object definition of Counter 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t loop;            /**< Counter loop back to 0 pin (toggle). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} counter2_cfg_t;

/**
 * @brief Counter 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    COUNTER2_OK = 0,
    COUNTER2_ERROR = -1

} counter2_return_value_t;

/*!
 * @addtogroup counter2 Counter 2 Click Driver
 * @brief API for configuring and manipulating Counter 2 Click driver.
 * @{
 */

/**
 * @brief Counter 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #counter2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void counter2_cfg_setup ( counter2_cfg_t *cfg );

/**
 * @brief Counter 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #counter2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #counter2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t counter2_init ( counter2_t *ctx, counter2_cfg_t *cfg );

/**
 * @brief Counter 2 set RST pin state function.
 * @details This function sets the RST (reset) pin to the specified logic level.
 * @param[in] ctx : Click context object.
 * See #counter2_t object definition for detailed explanation.
 * @param[in] state : Logic level to set (0 or 1).
 * @return None.
 * @note None.
 */
void counter2_set_rst_pin ( counter2_t *ctx, uint8_t state );

/**
 * @brief Counter 2 reset counter function.
 * @details This function performs a hardware counter reset by toggling the RST pin and synchronizing with the LOOP pin.
 * @param[in] ctx : Click context object.
 * See #counter2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void counter2_reset_counter ( counter2_t *ctx );

/**
 * @brief Counter 2 get LOOP pin function.
 * @details This function reads the logic level of the LOOP pin.
 * @param[in] ctx : Click context object.
 * See #counter2_t object definition for detailed explanation.
 * @return Current logic state of the LOOP pin.
 * @note None.
 */
uint8_t counter2_get_loop_pin ( counter2_t *ctx );

/**
 * @brief Counter 2 check loop toggle function.
 * @details This function checks if the LOOP pin state has changed since the last call.
 * @param[in] ctx : Click context object.
 * See #counter2_t object definition for detailed explanation.
 * @return @li @c  0 - LOOP pin did not change,
 *         @li @c  1 - LOOP pin changed (toggled).
 * @note None.
 */
uint8_t counter2_check_loop ( counter2_t *ctx );

/**
 * @brief Counter 2 get counter value function.
 * @details This function reads the current 24-bit counter value via I2C.
 * @param[in] ctx : Click context object.
 * See #counter2_t object definition for detailed explanation.
 * @param[out] counter : Pointer to variable where 24-bit counter value will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t counter2_get_counter ( counter2_t *ctx, uint32_t *counter );

/**
 * @brief Counter 2 read free data register function.
 * @details This function reads a 21-bit value from the free data register of the device.
 * @param[in] ctx : Click context object.
 * See #counter2_t object definition for detailed explanation.
 * @param[out] free_data : Pointer to variable where free data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t counter2_read_free_data ( counter2_t *ctx, uint32_t *free_data );

/**
 * @brief Counter 2 write free data register function.
 * @details This function writes a 21-bit value to the free data register of the device.
 * @param[in] ctx : Click context object.
 * See #counter2_t object definition for detailed explanation.
 * @param[in] free_data : 21-bit value to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t counter2_write_free_data ( counter2_t *ctx, uint32_t free_data );

/**
 * @brief Counter 2 software counter reset function.
 * @details This function performs a software counter reset by modifying and writing the free data register.
 * @param[in] ctx : Click context object.
 * See #counter2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Internally checks and synchronizes with LOOP pin state.
 */
err_t counter2_sw_reset_counter ( counter2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // COUNTER2_H

/*! @} */ // counter2

// ------------------------------------------------------------------------ END
