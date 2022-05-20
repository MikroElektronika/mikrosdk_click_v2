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
 * @file battmon4.h
 * @brief This file contains API for BATT-MON 4 Click Driver.
 */

#ifndef BATTMON4_H
#define BATTMON4_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup battmon4 BATT-MON 4 Click Driver
 * @brief API for configuring and manipulating BATT-MON 4 Click driver.
 * @{
 */

/**
 * @defgroup battmon4_reg BATT-MON 4 Registers List
 * @brief List of registers of BATT-MON 4 Click driver.
 */

/**
 * @addtogroup battmon4_reg
 * @{
 */

/**
 * @brief BATT-MON 4 Register Map.
 * @details Specified register map of BATT-MON 4 Click driver.
 */
#define BATTMON4_REG_A                      0x01
#define BATTMON4_REG_B                      0x02
#define BATTMON4_REG_C                      0x03
#define BATTMON4_REG_D                      0x04
#define BATTMON4_REG_E                      0x05
#define BATTMON4_REG_F                      0x06
#define BATTMON4_REG_G                      0x07
#define BATTMON4_REG_H                      0x08

/*! @} */ // battmon4_reg

/**
 * @defgroup battmon4_set BATT-MON 4 Registers Settings
 * @brief Settings for registers of BATT-MON 4 Click driver.
 */

/**
 * @addtogroup battmon4_set
 * @{
 */

/**
 * @brief BATT-MON 4 calculation values.
 * @details Specified calculation values of BATT-MON 4 Click driver.
 */
#define BATTMON4_TEMPERATURE_LSB            0.784
#define BATTMON4_TEMPERATURE_OFFSET         41.0
#define BATTMON4_TEMPERATURE_RESOLUTION     0x00FF
#define BATTMON4_VOLTAGE_LSB                1.465
#define BATTMON4_VOLTAGE_RESOLUTION         0x0FFF

/**
 * @brief BATT-MON 4 device address setting.
 * @details Specified setting for device slave address selection of
 * BATT-MON 4 Click driver.
 */
#define BATTMON4_DEVICE_ADDRESS             0x64

/*! @} */ // battmon4_set

/**
 * @defgroup battmon4_map BATT-MON 4 MikroBUS Map
 * @brief MikroBUS pin mapping of BATT-MON 4 Click driver.
 */

/**
 * @addtogroup battmon4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BATT-MON 4 Click to the selected MikroBUS.
 */
#define BATTMON4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.bok = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // battmon4_map
/*! @} */ // battmon4

/**
 * @brief BATT-MON 4 Click context object.
 * @details Context object definition of BATT-MON 4 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  bok;              /**< Battery OK status pin. */
    digital_in_t  int_pin;          /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} battmon4_t;

/**
 * @brief BATT-MON 4 Click configuration object.
 * @details Configuration object definition of BATT-MON 4 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  bok;                /**< Battery OK status pin. */
    pin_name_t  int_pin;            /**< Interrupt pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

} battmon4_cfg_t;

/**
 * @brief BATT-MON 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BATTMON4_OK = 0,
    BATTMON4_ERROR = -1

} battmon4_return_value_t;

/*!
 * @addtogroup battmon4 BATT-MON 4 Click Driver
 * @brief API for configuring and manipulating BATT-MON 4 Click driver.
 * @{
 */

/**
 * @brief BATT-MON 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #battmon4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void battmon4_cfg_setup ( battmon4_cfg_t *cfg );

/**
 * @brief BATT-MON 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #battmon4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #battmon4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon4_init ( battmon4_t *ctx, battmon4_cfg_t *cfg );

/**
 * @brief BATT-MON 4 write register function.
 * @details This function writes a desired data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written [2 bytes].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon4_write_register ( battmon4_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief BATT-MON 4 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon4_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data [2 bytes].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon4_read_register ( battmon4_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief BATT-MON 4 get die temperature function.
 * @details This function reads the chip DIE temperature in Celsius.
 * @param[in] ctx : Click context object.
 * See #battmon4_t object definition for detailed explanation.
 * @param[out] temperature : Die temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon4_get_die_temperature ( battmon4_t *ctx, float *temperature );

/**
 * @brief BATT-MON 4 get batt in voltage function.
 * @details This function reads the voltage from BATT IN when Ipeak is ON and OFF.
 * @param[in] ctx : Click context object.
 * See #battmon4_t object definition for detailed explanation.
 * @param[out] v_ipeak_on : BATT IN voltage in millivolts when Ipeak is ON.
 * @param[out] v_ipeak_off : BATT IN voltage in millivolts when Ipeak is OFF.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon4_get_batt_in_voltage ( battmon4_t *ctx, float *v_ipeak_on, float *v_ipeak_off );

/**
 * @brief BATT-MON 4 get batt out voltage function.
 * @details This function reads the voltage from BATT OUT when Ipeak is ON and OFF.
 * @param[in] ctx : Click context object.
 * See #battmon4_t object definition for detailed explanation.
 * @param[out] v_ipeak_on : BATT OUT voltage in millivolts when Ipeak is ON.
 * @param[out] v_ipeak_off : BATT OUT voltage in millivolts when Ipeak is OFF.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon4_get_batt_out_voltage ( battmon4_t *ctx, float *v_ipeak_on, float *v_ipeak_off );

/**
 * @brief BATT-MON 4 get bok pin function.
 * @details This function returns the BOK (Battery OK) pin logic state.
 * @param[in] ctx : Click context object.
 * See #battmon4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t battmon4_get_bok_pin ( battmon4_t *ctx );

/**
 * @brief BATT-MON 4 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #battmon4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t battmon4_get_int_pin ( battmon4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BATTMON4_H

/*! @} */ // battmon4

// ------------------------------------------------------------------------ END
