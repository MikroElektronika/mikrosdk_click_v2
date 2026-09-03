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
 * @file hbridge19.h
 * @brief This file contains API for H-Bridge 19 Click Driver.
 */

#ifndef HBRIDGE19_H
#define HBRIDGE19_H

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
 * @addtogroup hbridge19 H-Bridge 19 Click Driver
 * @brief API for configuring and manipulating H-Bridge 19 Click driver.
 * @{
 */

/**
 * @defgroup hbridge19_reg H-Bridge 19 Registers List
 * @brief List of registers of H-Bridge 19 Click driver.
 */

/**
 * @addtogroup hbridge19_reg
 * @{
 */

/**
 * @brief H-Bridge 19 register list.
 * @details Specified register list of H-Bridge 19 Click driver.
 */
#define HBRIDGE19_REG_INPUT_PORT            0x00
#define HBRIDGE19_REG_OUTPUT_PORT           0x01
#define HBRIDGE19_REG_POLARITY_INV          0x02
#define HBRIDGE19_REG_CONFIG                0x03

/*! @} */ // hbridge19_reg

/**
 * @defgroup hbridge19_set H-Bridge 19 Registers Settings
 * @brief Settings for registers of H-Bridge 19 Click driver.
 */

/**
 * @addtogroup hbridge19_set
 * @{
 */

/**
 * @brief H-Bridge 19 pin bit mask setting.
 * @details Specified setting for pin bit mask of H-Bridge 19 Click driver.
 */
#define HBRIDGE19_PIN_IN1A                  0x01
#define HBRIDGE19_PIN_IN1B                  0x02
#define HBRIDGE19_PIN_IN2B                  0x04
#define HBRIDGE19_PIN_IN2A                  0x08
#define HBRIDGE19_PIN_MODE                  0x10
#define HBRIDGE19_PIN_FAULT                 0x20
#define HBRIDGE19_PIN_PS                    0x40

/**
 * @brief H-Bridge 19 default configuration setting.
 * @details Specified setting for default configuration of H-Bridge 19 Click driver.
 */
#define HBRIDGE19_OUTPUT_DEFAULT            0x00
#define HBRIDGE19_POLARITY_DEFAULT          0x00
#define HBRIDGE19_CONFIG_DEFAULT            0x20

/**
 * @brief H-Bridge 19 motor selection setting.
 * @details Specified setting for motor selection of H-Bridge 19 Click driver.
 */
#define HBRIDGE19_MOTOR_SEL_0               0
#define HBRIDGE19_MOTOR_SEL_1               1

/**
 * @brief H-Bridge 19 motor state setting.
 * @details Specified setting for motor state of H-Bridge 19 Click driver.
 */
#define HBRIDGE19_MOTOR_STATE_HI_Z          0
#define HBRIDGE19_MOTOR_STATE_FORWARD       1
#define HBRIDGE19_MOTOR_STATE_REVERSE       2
#define HBRIDGE19_MOTOR_STATE_BRAKE         3

/**
 * @brief H-Bridge 19 device address setting.
 * @details Specified setting for device slave address selection of
 * H-Bridge 19 Click driver.
 */
#define HBRIDGE19_DEVICE_ADDRESS            0x38

/*! @} */ // hbridge19_set

/**
 * @defgroup hbridge19_map H-Bridge 19 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 19 Click driver.
 */

/**
 * @addtogroup hbridge19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 19 Click to the selected MikroBUS.
 */
#define HBRIDGE19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge19_map
/*! @} */ // hbridge19

/**
 * @brief H-Bridge 19 Click context object.
 * @details Context object definition of H-Bridge 19 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;                       /**< Interrupt pin(active low). */

    // Modules
    i2c_master_t i2c;                           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

} hbridge19_t;

/**
 * @brief H-Bridge 19 Click configuration object.
 * @details Configuration object definition of H-Bridge 19 Click driver.
 */
typedef struct
{
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;                         /**< Interrupt pin descriptor. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

} hbridge19_cfg_t;

/**
 * @brief H-Bridge 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE19_OK = 0,
    HBRIDGE19_ERROR = -1

} hbridge19_return_value_t;

/*!
 * @addtogroup hbridge19 H-Bridge 19 Click Driver
 * @brief API for configuring and manipulating H-Bridge 19 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 19 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge19_cfg_setup ( hbridge19_cfg_t *cfg );

/**
 * @brief H-Bridge 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #hbridge19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge19_init ( hbridge19_t *ctx, hbridge19_cfg_t *cfg );

/**
 * @brief H-Bridge 19 default configuration function.
 * @details This function executes a default configuration of H-Bridge 19
 * Click board.
 * @param[in] ctx : Click context object.
 * See #hbridge19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge19_default_cfg ( hbridge19_t *ctx );

/**
 * @brief H-Bridge 19 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #hbridge19_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge19_write_reg ( hbridge19_t *ctx, uint8_t cmd, uint8_t data_in );

/**
 * @brief H-Bridge 19 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #hbridge19_t object definition for detailed explanation.
 * @param[in] cmd : Command byte.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge19_read_reg ( hbridge19_t *ctx, uint8_t cmd, uint8_t *data_out );

/**
 * @brief H-Bridge 19 enable device function.
 * @details This function enables the device by setting the PS pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge19_enable_device ( hbridge19_t *ctx );

/**
 * @brief H-Bridge 19 disable device function.
 * @details This function disables the device by setting the PS pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge19_disable_device ( hbridge19_t *ctx );

/**
 * @brief H-Bridge 19 set motor state function.
 * @details This function sets the operating state for the selected motor.
 * @param[in] ctx : Click context object.
 * See #hbridge19_t object definition for detailed explanation.
 * @param[in] motor : @li @c 0 - Motor 1,
 *                    @li @c 1 - Motor 2.
 * @param[in] state : @li @c 0 - High-Z,
 *                    @li @c 1 - Forward,
 *                    @li @c 2 - Reverse,
 *                    @li @c 3 - Brake.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge19_set_motor_state ( hbridge19_t *ctx, uint8_t motor, uint8_t state );

/**
 * @brief H-Bridge 19 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge19_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t hbridge19_get_int_pin ( hbridge19_t *ctx );

/**
 * @brief H-Bridge 19 get fault function.
 * @details This function checks whether overcurrent protection or
 * thermal shutdown circuit is activated by reading the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge19_t object definition for detailed explanation.
 * @param[out] fault : @li @c 0 - No fault,
 *                     @li @c 1 - Fault active (OCP or TSD).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge19_get_fault ( hbridge19_t *ctx, uint8_t *fault );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE19_H

/*! @} */ // hbridge19

// ------------------------------------------------------------------------ END
