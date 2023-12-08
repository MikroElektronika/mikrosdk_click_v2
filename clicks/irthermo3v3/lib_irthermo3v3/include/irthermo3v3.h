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
 * @file irthermo3v3.h
 * @brief This file contains API for IrThermo 3V3 Click Driver.
 */

#ifndef IRTHERMO3V3_H
#define IRTHERMO3V3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup irthermo3v3 IrThermo 3V3 Click Driver
 * @brief API for configuring and manipulating IrThermo 3V3 Click driver.
 * @{
 */

/**
 * @defgroup irthermo3v3_set IrThermo 3V3 Registers Settings
 * @brief Settings for registers of IrThermo 3V3 Click driver.
 */

/**
 * @addtogroup irthermo3v3_set
 * @{
 */

/**
 * @brief IrThermo 3V3 device address setting.
 * @details Specified setting for device slave address selection of
 * IrThermo 3V3 Click driver.
 */
#define IRTHERMO3V3_SET_DEV_ADDR  0x5A

/*! @} */ // irthermo3v3_set

/**
 * @defgroup irthermo3v3_map IrThermo 3V3 MikroBUS Map
 * @brief MikroBUS pin mapping of IrThermo 3V3 Click driver.
 */

/**
 * @addtogroup irthermo3v3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IrThermo 3V3 Click to the selected MikroBUS.
 */
#define IRTHERMO3V3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // irthermo3v3_map
/*! @} */ // irthermo3v3

/**
 * @brief IrThermo 3V3 Click context object.
 * @details Context object definition of IrThermo 3V3 Click driver.
 */
typedef struct
{
    // Input pins

    digital_in_t  pwm;       

    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} irthermo3v3_t;

/**
 * @brief IrThermo 3V3 Click configuration object.
 * @details Configuration object definition of IrThermo 3V3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  pwm;      

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} irthermo3v3_cfg_t;

/**
 * @brief IrThermo 3V3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   IRTHERMO3V3_OK = 0,
   IRTHERMO3V3_ERROR = -1

} irthermo3v3_return_value_t;

/*!
 * @addtogroup irthermo3v3 IrThermo 3V3 Click Driver
 * @brief API for configuring and manipulating IrThermo 3V3 Click driver.
 * @{
 */

/**
 * @brief IrThermo 3V3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irthermo3v3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 */
void irthermo3v3_cfg_setup ( irthermo3v3_cfg_t *cfg );

/**
 * @brief IrThermo 3V3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #irthermo3v3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irthermo3v3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 */
err_t irthermo3v3_init ( irthermo3v3_t *ctx, irthermo3v3_cfg_t *cfg );

/**
 * @brief Reads Temperature ambient from sensor.
 * @details Function returns ambient temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #irthermo3v3_t object definition for detailed explanation.
 * @return Ambient temperature value in Celsius.
 * 
 * @note None.
 */
float irthermo3v3_get_t_ambient ( irthermo3v3_t* ctx );

/**
 * @brief Reads Temperature object1 from sensor.
 * @details Function returns object temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #irthermo3v3_t object definition for detailed explanation.
 * @return Object temperature value in Celsius.
 * 
 * @note None.
 */
float irthermo3v3_get_t_object ( irthermo3v3_t* ctx );

/**
 * @brief Generic function for reading values from RAM.
 * @details Function returns 16bit value of register.
 * @param[in] ctx : Click context object.
 * See #irthermo3v3_t object definition for detailed explanation.
 * @param[in] address :  Address of register
 * @return 16bit value of register.
 * 
 * @note None.
 */
uint16_t irthermo3v3_read_reg ( irthermo3v3_t* ctx, uint8_t address );


#ifdef __cplusplus
}
#endif
#endif // IRTHERMO3V3_H

/*! @} */ // irthermo3v3

// ------------------------------------------------------------------------ END
