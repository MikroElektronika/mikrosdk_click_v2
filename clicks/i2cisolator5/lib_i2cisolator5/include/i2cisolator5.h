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
 * @file i2cisolator5.h
 * @brief This file contains API for I2C Isolator 5 Click Driver.
 */

#ifndef I2CISOLATOR5_H
#define I2CISOLATOR5_H

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
 * @addtogroup i2cisolator5 I2C Isolator 5 Click Driver
 * @brief API for configuring and manipulating I2C Isolator 5 Click driver.
 * @{
 */

/**
 * @defgroup i2cisolator5_set I2C Isolator 5 Registers Settings
 * @brief Settings for registers of I2C Isolator 5 Click driver.
 */

/**
 * @addtogroup i2cisolator5_set
 * @{
 */

/**
 * @brief I2C Isolator 5 description setting.
 * @details Specified setting for description of I2C Isolator 5 Click driver.
 */
#define I2CISOLATOR5_PIN_STATE_HIGH        0x01
#define I2CISOLATOR5_PIN_STATE_LOW         0x00

/**
 * @brief I2C Isolator 5 device address setting.
 * @details Specified setting for device slave address selection of
 * I2C Isolator 5 Click driver.
 */
#define I2CISOLATOR5_DEVICE_ADDRESS        0x00

/*! @} */ // i2cisolator5_set

/**
 * @defgroup i2cisolator5_map I2C Isolator 5 MikroBUS Map
 * @brief MikroBUS pin mapping of I2C Isolator 5 Click driver.
 */

/**
 * @addtogroup i2cisolator5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C Isolator 5 Click to the selected MikroBUS.
 */
#define I2CISOLATOR5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.otb = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ota = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ina = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // i2cisolator5_map
/*! @} */ // i2cisolator5

/**
 * @brief I2C Isolator 5 Click context object.
 * @details Context object definition of I2C Isolator 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t otb;              /**< Output B pin. */
    digital_out_t ota;              /**< Output A pin. */

    // Input pins
    digital_in_t ina;               /**< Input A pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} i2cisolator5_t;

/**
 * @brief I2C Isolator 5 Click configuration object.
 * @details Configuration object definition of I2C Isolator 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t otb;             /**< Output B pin. */
    pin_name_t ota;             /**< Output A pin. */
    pin_name_t ina;             /**< Input A pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} i2cisolator5_cfg_t;

/**
 * @brief I2C Isolator 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    I2CISOLATOR5_OK = 0,
    I2CISOLATOR5_ERROR = -1

} i2cisolator5_return_value_t;

/*!
 * @addtogroup i2cisolator5 I2C Isolator 5 Click Driver
 * @brief API for configuring and manipulating I2C Isolator 5 Click driver.
 * @{
 */

/**
 * @brief I2C Isolator 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2cisolator5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void i2cisolator5_cfg_setup ( i2cisolator5_cfg_t *cfg );

/**
 * @brief I2C Isolator 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #i2cisolator5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2cisolator5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator5_init ( i2cisolator5_t *ctx, i2cisolator5_cfg_t *cfg );

/**
 * @brief I2C Isolator 5 default configuration function.
 * @details This function executes a default configuration of I2C Isolator 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #i2cisolator5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t i2cisolator5_default_cfg ( i2cisolator5_t *ctx );

/**
 * @brief I2C Isolator 5 I2C writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cisolator5_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator5_write ( i2cisolator5_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief I2C Isolator 5 I2C reading function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2cisolator5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator5_read ( i2cisolator5_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief I2C Isolator 5 I2C write then read function.
 * @details Function performs a write operation followed by a
 * read operation on the bus. The operation consists of a
 * start signal followed by a number of write operations
 * ( data from data_in ), a restart signal followed by
 * number of read operations ( placed in data_out ),
 * finishing the operation with a stop signal.
 * @param[in] ctx : Click context object.
 * See #i2cisolator5_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] data_in_len : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[in] data_out_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None
 */
err_t i2cisolator5_write_then_read ( i2cisolator5_t *ctx, uint8_t *data_in, uint8_t data_in_len, 
                                     uint8_t *data_out, uint8_t data_out_len );

/**
 * @brief I2C Isolator 5 set I2C Slave address function.
 * @details This function sets I2C address of the subordinate I2C device
 * to address which is targeted by read and write operations.
 * @param[in] ctx : Click context object.
 * See #i2cisolator5_t object definition for detailed explanation.
 * @param[in] address : Specified I2C slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator5_set_slave_address ( i2cisolator5_t *ctx, uint8_t address );

/**
 * @brief I2C Isolator 5 set output A state function.
 * @details This function sets the state of the out A pin.
 * @param[in] ctx : Click context object.
 * See #i2cisolator5_t object definition for detailed explanation.
 * @param[in] outa_state : Specified out A pin state.
 * @return Nothing.
 * @note None.
 */
void i2cisolator5_set_outa_state ( i2cisolator5_t *ctx, uint8_t outa_state );

/**
 * @brief I2C Isolator 5 set output B state function.
 * @details This function sets the state of the out B pin.
 * @param[in] ctx : Click context object.
 * See #i2cisolator5_t object definition for detailed explanation.
 * @param[in] outb_state : Specified out B pin state.
 * @return Nothing.
 * @note None.
 */
void i2cisolator5_set_outb_state ( i2cisolator5_t *ctx, uint8_t outb_state );

/**
 * @brief I2C Isolator 5 get input A state function.
 * @details This function reads the state of the input A pin.
 * @param[in] ctx : Click context object.
 * See #i2cisolator5_t object definition for detailed explanation.
 * @return State of the input A pin.
 * @note None.
 */
uint8_t i2cisolator5_get_ina_state ( i2cisolator5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // I2CISOLATOR5_H

/*! @} */ // i2cisolator5

// ------------------------------------------------------------------------ END
