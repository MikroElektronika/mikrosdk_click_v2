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
 * @file hbridge15.h
 * @brief This file contains API for H-Bridge 15 Click Driver.
 */

#ifndef HBRIDGE15_H
#define HBRIDGE15_H

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
 * @addtogroup hbridge15 H-Bridge 15 Click Driver
 * @brief API for configuring and manipulating H-Bridge 15 Click driver.
 * @{
 */

/**
 * @defgroup hbridge15_reg H-Bridge 15 Registers List
 * @brief List of registers of H-Bridge 15 Click driver.
 */

/**
 * @addtogroup hbridge15_reg
 * @{
 */

/**
 * @brief H-Bridge 15 description register.
 * @details Specified register for description of H-Bridge 15 Click driver.
 */
#define HBRIDGE15_REG_INPUT_PORT                        0x00
#define HBRIDGE15_REG_OUTPUT_PORT                       0x01
#define HBRIDGE15_REG_POLARITY_INVERSION                0x02
#define HBRIDGE15_REG_CONFIGURATION                     0x03

/*! @} */ // hbridge15_reg

/**
 * @defgroup hbridge15_set H-Bridge 15 Registers Settings
 * @brief Settings for registers of H-Bridge 15 Click driver.
 */

/**
 * @addtogroup hbridge15_set
 * @{
 */

/**
 * @brief H-Bridge 15 description setting.
 * @details Specified setting for description of H-Bridge 15 Click driver.
 */
#define HBRIDGE15_PIN_MASK_NONE                         0x00
#define HBRIDGE15_PIN_MASK_SLP                          0x01
#define HBRIDGE15_PIN_MASK_FLT                          0x02
#define HBRIDGE15_PIN_MASK_CONFIG                       0x04
#define HBRIDGE15_PIN_MASK_M1                           0x08
#define HBRIDGE15_PIN_MASK_M0                           0x10
#define HBRIDGE15_PIN_MASK_DIR                          0x20
#define HBRIDGE15_PIN_MASK_EN_B                         0x40
#define HBRIDGE15_PIN_MASK_EN_A                         0x80
#define HBRIDGE15_PIN_MASK_ALL                          0xFF

/**
 * @brief H-Bridge 15 pin state setting.
 * @details Specified setting for pin state of H-Bridge 15 Click driver.
 */
#define HBRIDGE15_PIN_STATE_HIGH                        0x01
#define HBRIDGE15_PIN_STATE_LOW                         0x00

/**
 * @brief H-Bridge 15 sleep state setting.
 * @details Specified setting for sleep state of H-Bridge 15 Click driver.
 */
#define HBRIDGE15_SLEEP_STATE_ON                        0x01
#define HBRIDGE15_SLEEP_STATE_OFF                       0x00

/**
 * @brief H-Bridge 15 motor states setting.
 * @details Specified setting for motor states of H-Bridge 15 Click driver.
 */
#define HBRIDGE15_DRIVE_MOTOR_REVERSE                   0x00
#define HBRIDGE15_DRIVE_MOTOR_FORWARD                   0x01
#define HBRIDGE15_DRIVE_MOTOR_FREEWHEEL                 0x02
#define HBRIDGE15_DRIVE_MOTOR_BRAKE                     0x03

/**
 * @brief H-Bridge 15 device address setting.
 * @details Specified setting for device slave address selection of
 * H-Bridge 15 Click driver.
 */
#define HBRIDGE15_DEVICE_ADDRESS_00                     0x70
#define HBRIDGE15_DEVICE_ADDRESS_01                     0x71
#define HBRIDGE15_DEVICE_ADDRESS_10                     0x72
#define HBRIDGE15_DEVICE_ADDRESS_11                     0x73

/*! @} */ // hbridge15_set

/**
 * @defgroup hbridge15_map H-Bridge 15 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 15 Click driver.
 */

/**
 * @addtogroup hbridge15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 15 Click to the selected MikroBUS.
 */
#define HBRIDGE15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ena = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge15_map
/*! @} */ // hbridge15

/**
 * @brief H-Bridge 15 Click context object.
 * @details Context object definition of H-Bridge 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ena;      /**< Enable output a pin. */
    digital_out_t rst;      /**< Reset port expander pin. */

    // Input pins
    digital_in_t int_pin;   /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} hbridge15_t;

/**
 * @brief H-Bridge 15 Click configuration object.
 * @details Configuration object definition of H-Bridge 15 Click driver.
 */
typedef struct
{
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t ena;         /**< Enable output a pin. */
    pin_name_t rst;         /**< Reset port expander pin. */
    pin_name_t int_pin;     /**< Interrupt pin. */

    uint32_t   i2c_speed;   /**< I2C serial speed. */
    uint8_t    i2c_address; /**< I2C slave address. */

} hbridge15_cfg_t;

/**
 * @brief H-Bridge 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE15_OK = 0,
    HBRIDGE15_ERROR = -1

} hbridge15_return_value_t;

/*!
 * @addtogroup hbridge15 H-Bridge 15 Click Driver
 * @brief API for configuring and manipulating H-Bridge 15 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 15 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge15_cfg_setup ( hbridge15_cfg_t *cfg );

/**
 * @brief H-Bridge 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge15_init ( hbridge15_t *ctx, hbridge15_cfg_t *cfg );

/**
 * @brief H-Bridge 15 default configuration function.
 * @details This function executes a default configuration of H-Bridge 15
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge15_default_cfg ( hbridge15_t *ctx );

/**
 * @brief H-Bridge 15 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge15_generic_write ( hbridge15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief H-Bridge 15 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge15_generic_read ( hbridge15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief H-Bridge 15 set RST pin function.
 * @details This function is used to set state of the RST pin.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return None.
 * @note None.
 */
void hbridge15_set_rst_pin ( hbridge15_t *ctx, uint8_t pin_state );

/**
 * @brief H-Bridge 15 set ENA pin function.
 * @details This function is used to set state of the ENA pin.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @param[in] pin_state : Pin state.
 * @return None.
 * @note None.
 */
void hbridge15_set_ena_pin ( hbridge15_t *ctx, uint8_t pin_state );

/**
 * @brief H-Bridge 15 get INT pin state function.
 * @details This function is used to get INT pin state.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @return Interrupt pin state.
 * @note None.
 */
uint8_t hbridge15_get_int_state ( hbridge15_t *ctx );

/**
 * @brief H-Bridge 15 reset port expander function.
 * @details This function resets the port expander by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge15_reset_port_exp ( hbridge15_t *ctx );

/**
 * @brief H-Bridge 15 write register function.
 * @details This function writes a desired data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge15_write_reg ( hbridge15_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief H-Bridge 15 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge15_read_reg ( hbridge15_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief H-Bridge 15 set pins function.
 * @details This function sets and clears the value of the selected pins of PCA9538A port expander.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @param[in] clr_mask : Pin clear mask.
 * @param[in] set_mask : Pin set mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge15_set_pins ( hbridge15_t *ctx, uint8_t set_mask, uint8_t clr_mask );

/**
 * @brief H-Bridge 15 set sleep function.
 * @details This function is used to set sleep state of the H-Bridge 15
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @param[in] sleep_state : Sleep state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge15_set_sleep ( hbridge15_t *ctx, uint8_t sleep_state );

/**
 * @brief H-Bridge 15 set output function.
 * @details This function is used to set output state of the H-Bridge 15
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge15_t object definition for detailed explanation.
 * @param[in] out_state : Output state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge15_set_out_state ( hbridge15_t *ctx, uint8_t out_state );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE15_H

/*! @} */ // hbridge15

// ------------------------------------------------------------------------ END
