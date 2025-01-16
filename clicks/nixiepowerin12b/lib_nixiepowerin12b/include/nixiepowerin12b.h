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
 * @file nixiepowerin12b.h
 * @brief This file contains API for Nixie Power IN-12B Click Driver.
 */

#ifndef NIXIEPOWERIN12B_H
#define NIXIEPOWERIN12B_H

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
 * @addtogroup nixiepowerin12b Nixie Power IN-12B Click Driver
 * @brief API for configuring and manipulating Nixie Power IN-12B Click driver.
 * @{
 */

/**
 * @defgroup nixiepowerin12b_reg Nixie Power IN-12B Registers List
 * @brief List of registers of Nixie Power IN-12B Click driver.
 */

/**
 * @addtogroup nixiepowerin12b_reg
 * @{
 */

/**
 * @brief Nixie Power IN-12B register map.
 * @details Specified register map of Nixie Power IN-12B Click driver.
 */
#define NIXIEPOWERIN12B_REG_IODIRA              0x00
#define NIXIEPOWERIN12B_REG_IODIRB              0x01
#define NIXIEPOWERIN12B_REG_IPOLA               0x02
#define NIXIEPOWERIN12B_REG_IPOLB               0x03
#define NIXIEPOWERIN12B_REG_GPINTENA            0x04
#define NIXIEPOWERIN12B_REG_GPINTENB            0x05
#define NIXIEPOWERIN12B_REG_DEFVALA             0x06
#define NIXIEPOWERIN12B_REG_DEFVALB             0x07
#define NIXIEPOWERIN12B_REG_INTCONA             0x08
#define NIXIEPOWERIN12B_REG_INTCONB             0x09
#define NIXIEPOWERIN12B_REG_IOCON               0x0A
#define NIXIEPOWERIN12B_REG_GPPUA               0x0C
#define NIXIEPOWERIN12B_REG_GPPUB               0x0D
#define NIXIEPOWERIN12B_REG_INTFA               0x0E
#define NIXIEPOWERIN12B_REG_INTFB               0x0F
#define NIXIEPOWERIN12B_REG_INTCAPA             0x10
#define NIXIEPOWERIN12B_REG_INTCAPB             0x11
#define NIXIEPOWERIN12B_REG_GPIOA               0x12
#define NIXIEPOWERIN12B_REG_GPIOB               0x13
#define NIXIEPOWERIN12B_REG_OLATA               0x14
#define NIXIEPOWERIN12B_REG_OLATB               0x15

/*! @} */ // nixiepowerin12b_reg

/**
 * @defgroup nixiepowerin12b_set Nixie Power IN-12B Registers Settings
 * @brief Settings for registers of Nixie Power IN-12B Click driver.
 */

/**
 * @addtogroup nixiepowerin12b_set
 * @{
 */

/**
 * @brief Nixie Power IN-12B pin direction setting.
 * @details Specified setting for pin direction of Nixie Power IN-12B Click driver.
 */
#define NIXIEPOWERIN12B_DIR_ALL_INPUT           0xFF
#define NIXIEPOWERIN12B_DIR_ALL_OUTPUT          0x00

/**
 * @brief Nixie Power IN-12B pin mask setting.
 * @details Specified setting for pin mask of Nixie Power IN-12B Click driver.
 */
#define NIXIEPOWERIN12B_PIN_PB6_LHCM            0x40
#define NIXIEPOWERIN12B_PIN_PB5_K1              0x20
#define NIXIEPOWERIN12B_PIN_PB4_K2              0x10
#define NIXIEPOWERIN12B_PIN_PB3_K3              0x08
#define NIXIEPOWERIN12B_PIN_PB2_K4              0x04
#define NIXIEPOWERIN12B_PIN_PB1_K5              0x02
#define NIXIEPOWERIN12B_PIN_PB0_K6              0x01
#define NIXIEPOWERIN12B_PIN_PA5_K7              0x20
#define NIXIEPOWERIN12B_PIN_PA3_K8              0x08
#define NIXIEPOWERIN12B_PIN_PA2_K9              0x04
#define NIXIEPOWERIN12B_PIN_PA1_K0              0x02
#define NIXIEPOWERIN12B_PIN_CLEAR               0x00

/**
 * @brief Nixie Power IN-12B digits setting.
 * @details Specified setting for digits of Nixie Power IN-12B Click driver.
 */
#define NIXIEPOWERIN12B_DIGIT_0                 0
#define NIXIEPOWERIN12B_DIGIT_1                 1
#define NIXIEPOWERIN12B_DIGIT_2                 2
#define NIXIEPOWERIN12B_DIGIT_3                 3
#define NIXIEPOWERIN12B_DIGIT_4                 4
#define NIXIEPOWERIN12B_DIGIT_5                 5
#define NIXIEPOWERIN12B_DIGIT_6                 6
#define NIXIEPOWERIN12B_DIGIT_7                 7
#define NIXIEPOWERIN12B_DIGIT_8                 8
#define NIXIEPOWERIN12B_DIGIT_9                 9
#define NIXIEPOWERIN12B_DIGIT_NONE              10
#define NIXIEPOWERIN12B_COMMA_CLEAR             0
#define NIXIEPOWERIN12B_COMMA_SET               1                   

/**
 * @brief Nixie Power IN-12B device address setting.
 * @details Specified setting for device slave address selection of
 * Nixie Power IN-12B Click driver.
 */
#define NIXIEPOWERIN12B_DEVICE_ADDRESS_0        0x20
#define NIXIEPOWERIN12B_DEVICE_ADDRESS_1        0x21
#define NIXIEPOWERIN12B_DEVICE_ADDRESS_2        0x22
#define NIXIEPOWERIN12B_DEVICE_ADDRESS_3        0x23
#define NIXIEPOWERIN12B_DEVICE_ADDRESS_4        0x24
#define NIXIEPOWERIN12B_DEVICE_ADDRESS_5        0x25
#define NIXIEPOWERIN12B_DEVICE_ADDRESS_6        0x26
#define NIXIEPOWERIN12B_DEVICE_ADDRESS_7        0x27

/*! @} */ // nixiepowerin12b_set

/**
 * @defgroup nixiepowerin12b_map Nixie Power IN-12B MikroBUS Map
 * @brief MikroBUS pin mapping of Nixie Power IN-12B Click driver.
 */

/**
 * @addtogroup nixiepowerin12b_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Nixie Power IN-12B Click to the selected MikroBUS.
 */
#define NIXIEPOWERIN12B_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // nixiepowerin12b_map
/*! @} */ // nixiepowerin12b

/**
 * @brief Nixie Power IN-12B Click context object.
 * @details Context object definition of Nixie Power IN-12B Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} nixiepowerin12b_t;

/**
 * @brief Nixie Power IN-12B Click configuration object.
 * @details Configuration object definition of Nixie Power IN-12B Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} nixiepowerin12b_cfg_t;

/**
 * @brief Nixie Power IN-12B Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NIXIEPOWERIN12B_OK = 0,
    NIXIEPOWERIN12B_ERROR = -1

} nixiepowerin12b_return_value_t;

/*!
 * @addtogroup nixiepowerin12b Nixie Power IN-12B Click Driver
 * @brief API for configuring and manipulating Nixie Power IN-12B Click driver.
 * @{
 */

/**
 * @brief Nixie Power IN-12B configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nixiepowerin12b_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nixiepowerin12b_cfg_setup ( nixiepowerin12b_cfg_t *cfg );

/**
 * @brief Nixie Power IN-12B initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #nixiepowerin12b_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nixiepowerin12b_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nixiepowerin12b_init ( nixiepowerin12b_t *ctx, nixiepowerin12b_cfg_t *cfg );

/**
 * @brief Nixie Power IN-12B default configuration function.
 * @details This function executes a default configuration of Nixie Power IN-12B
 * Click board.
 * @param[in] ctx : Click context object.
 * See #nixiepowerin12b_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t nixiepowerin12b_default_cfg ( nixiepowerin12b_t *ctx );

/**
 * @brief Nixie Power IN-12B write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nixiepowerin12b_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nixiepowerin12b_write_regs ( nixiepowerin12b_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Nixie Power IN-12B read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nixiepowerin12b_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nixiepowerin12b_read_regs ( nixiepowerin12b_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Nixie Power IN-12B write reg function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nixiepowerin12b_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nixiepowerin12b_write_reg ( nixiepowerin12b_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Nixie Power IN-12B read reg function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nixiepowerin12b_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nixiepowerin12b_read_reg ( nixiepowerin12b_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Nixie Power IN-12B set digit function.
 * @details This function sets the display output digit and comma.
 * @param[in] ctx : Click context object.
 * See #nixiepowerin12b_t object definition for detailed explanation.
 * @param[in] digit : 0-9 - digit selection to output, 10 - no digits output.
 * @param[in] comma : 1 - display comma, 0 - no comma displayed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nixiepowerin12b_set_digit ( nixiepowerin12b_t *ctx, uint8_t digit, uint8_t comma );

#ifdef __cplusplus
}
#endif
#endif // NIXIEPOWERIN12B_H

/*! @} */ // nixiepowerin12b

// ------------------------------------------------------------------------ END
