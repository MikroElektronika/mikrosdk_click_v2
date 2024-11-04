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
 * @file boostinv3.h
 * @brief This file contains API for Boost-INV 3 Click Driver.
 */

#ifndef BOOSTINV3_H
#define BOOSTINV3_H

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
 * @addtogroup boostinv3 Boost-INV 3 Click Driver
 * @brief API for configuring and manipulating Boost-INV 3 Click driver.
 * @{
 */

/**
 * @defgroup boostinv3_reg Boost-INV 3 Registers List
 * @brief List of registers of Boost-INV 3 Click driver.
 */

/**
 * @addtogroup boostinv3_reg
 * @{
 */

/**
 * @brief Boost-INV 3 description register.
 * @details Specified register for description of Boost-INV 3 Click driver.
 */
#define BOOSTINV3_REG_P_OUT_VOLTAGE             0x00
#define BOOSTINV3_REG_N_OUT_VOLTAGE             0x01
#define BOOSTINV3_REG_CONFIG                    0x03
#define BOOSTINV3_REG_CONTROL                   0xFF


/*! @} */ // boostinv3_reg

/**
 * @defgroup boostinv3_set Boost-INV 3 Registers Settings
 * @brief Settings for registers of Boost-INV 3 Click driver.
 */

/**
 * @addtogroup boostinv3_set
 * @{
 */

/**
 * @brief Boost-INV 3 description setting.
 * @details Specified setting for description of Boost-INV 3 Click driver.
 */
#define BOOSTINV3_APPS_VALUE_40_MA              0x00
#define BOOSTINV3_APPS_VALUE_80_MA              0x40
#define BOOSTINV3_VPOS_NO_DISCHARGE             0x00
#define BOOSTINV3_VPOS_DISCHARGE_EN             0x02
#define BOOSTINV3_VPON_NO_DISCHARGE             0x00
#define BOOSTINV3_VPON_DISCHARGE_EN             0x01

/**
 * @brief Boost-INV 3 pin state setting.
 * @details Specified setting for pin state of Boost-INV 3 Click driver.
 */
#define BOOSTINV3_PIN_STATE_LOW                 0x00
#define BOOSTINV3_PIN_STATE_HIGH                0x01

/**
 * @brief Boost-INV 3 output voltage setting.
 * @details Specified setting for output voltage of Boost-INV 3 Click driver.
 */
#define BOOSTINV3_OUT_VOLTAGE_4V                0x00
#define BOOSTINV3_OUT_VOLTAGE_4V1               0x01
#define BOOSTINV3_OUT_VOLTAGE_4V2               0x02
#define BOOSTINV3_OUT_VOLTAGE_4V3               0x03
#define BOOSTINV3_OUT_VOLTAGE_4V4               0x04
#define BOOSTINV3_OUT_VOLTAGE_4V5               0x05
#define BOOSTINV3_OUT_VOLTAGE_4V6               0x06
#define BOOSTINV3_OUT_VOLTAGE_4V7               0x07
#define BOOSTINV3_OUT_VOLTAGE_4V8               0x08
#define BOOSTINV3_OUT_VOLTAGE_4V9               0x09
#define BOOSTINV3_OUT_VOLTAGE_5V                0x0A
#define BOOSTINV3_OUT_VOLTAGE_5V1               0x0B
#define BOOSTINV3_OUT_VOLTAGE_5V2               0x0C
#define BOOSTINV3_OUT_VOLTAGE_5V3               0x0D
#define BOOSTINV3_OUT_VOLTAGE_5V4               0x0E
#define BOOSTINV3_OUT_VOLTAGE_5V5               0x0F
#define BOOSTINV3_OUT_VOLTAGE_5V6               0x10
#define BOOSTINV3_OUT_VOLTAGE_5V7               0x11
#define BOOSTINV3_OUT_VOLTAGE_5V8               0x12
#define BOOSTINV3_OUT_VOLTAGE_5V9               0x13
#define BOOSTINV3_OUT_VOLTAGE_6V                0x14

/**
 * @brief Boost-INV 3 EEPROM commands setting.
 * @details Specified setting for EEPROM commands of Boost-INV 3 Click driver.
 */
#define BOOSTINV3_CMD_WRITE_EEPROM              0x80
#define BOOSTINV3_CMD_READ_EEPROM               0x01
#define BOOSTINV3_CMD_READ_REG                  0x00

/**
 * @brief Boost-INV 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Boost-INV 3 Click driver.
 */
#define BOOSTINV3_DEVICE_ADDRESS                0x3E

/*! @} */ // boostinv3_set

/**
 * @defgroup boostinv3_map Boost-INV 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Boost-INV 3 Click driver.
 */

/**
 * @addtogroup boostinv3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Boost-INV 3 Click to the selected MikroBUS.
 */
#define BOOSTINV3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.enp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.enn = MIKROBUS( mikrobus, MIKROBUS_PWM ); \

/*! @} */ // boostinv3_map
/*! @} */ // boostinv3

/**
 * @brief Boost-INV 3 Click context object.
 * @details Context object definition of Boost-INV 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t enp;              /**< Enable positive output. */
    digital_out_t enn;              /**< Enable negative output. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} boostinv3_t;

/**
 * @brief Boost-INV 3 Click configuration object.
 * @details Configuration object definition of Boost-INV 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t enp;             /**< Enable positive output. */
    pin_name_t enn;             /**< Enable negative output. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} boostinv3_cfg_t;

/**
 * @brief Boost-INV 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BOOSTINV3_OK = 0,
    BOOSTINV3_ERROR = -1

} boostinv3_return_value_t;

/*!
 * @addtogroup boostinv3 Boost-INV 3 Click Driver
 * @brief API for configuring and manipulating Boost-INV 3 Click driver.
 * @{
 */

/**
 * @brief Boost-INV 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #boostinv3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void boostinv3_cfg_setup ( boostinv3_cfg_t *cfg );

/**
 * @brief Boost-INV 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #boostinv3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #boostinv3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boostinv3_init ( boostinv3_t *ctx, boostinv3_cfg_t *cfg );

/**
 * @brief Boost-INV 3 default configuration function.
 * @details This function executes a default configuration of Boost-INV 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #boostinv3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t boostinv3_default_cfg ( boostinv3_t *ctx );

/**
 * @brief Boost-INV 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #boostinv3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boostinv3_generic_write ( boostinv3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Boost-INV 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #boostinv3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boostinv3_generic_read ( boostinv3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Boost-INV 3 set ENP pin state function.
 * @details This function is used to set output level of the ENP pin.
 * @param[in] ctx : Click context object.
 * See #boostinv3_t object definition for detailed explanation.
 * @param[in] out_state : ENP output state.
 * @return Nothing.
 * @note None.
 */
void boostinv3_set_enp ( boostinv3_t *ctx, uint8_t out_state );

/**
 * @brief Boost-INV 3 set ENN pin state function.
 * @details This function is used to set output level of the ENN pin.
 * @param[in] ctx : Click context object.
 * See #boostinv3_t object definition for detailed explanation.
 * @param[in] out_state : ENN output state.
 * @return Nothing.
 * @note None.
 */
void boostinv3_set_enn ( boostinv3_t *ctx, uint8_t out_state );

/**
 * @brief Boost-INV 3 register write function.
 * @details This function byte of data to 
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #boostinv3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boostinv3_write_reg ( boostinv3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Boost-INV 3 set positive output voltage function.
 * @details This function is used to set positive output voltage 
 * of the Boost-INV 3 Click.
 * @param[in] ctx : Click context object.
 * See #boostinv3_t object definition for detailed explanation.
 * @param[in] out_val : Output voltage value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boostinv3_set_pos_out ( boostinv3_t *ctx, uint8_t out_val );

/**
 * @brief Boost-INV 3 set negative output voltage function.
 * @details This function is used to set negative output voltage 
 * of the Boost-INV 3 Click.
 * @param[in] ctx : Click context object.
 * See #boostinv3_t object definition for detailed explanation.
 * @param[in] out_val : Output voltage value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boostinv3_set_neg_out ( boostinv3_t *ctx, uint8_t out_val );

#ifdef __cplusplus
}
#endif
#endif // BOOSTINV3_H

/*! @} */ // boostinv3

// ------------------------------------------------------------------------ END
