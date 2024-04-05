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
 * @file irthermo5v.h
 * @brief This file contains API for IrThermo 5V Click Driver.
 */

#ifndef IRTHERMO5V_H
#define IRTHERMO5V_H

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
 * @addtogroup irthermo5v IrThermo 5V Click Driver
 * @brief API for configuring and manipulating IrThermo 5V Click driver.
 * @{
 */

/**
 * @defgroup irthermo5v_set IrThermo 5V Registers Settings
 * @brief Settings for registers of IrThermo 5V Click driver.
 */

/**
 * @addtogroup irthermo5v_set
 * @{
 */

/**
 * @brief IrThermo 5V device address setting.
 * @details Specified setting for device slave address selection of
 * IrThermo 5V Click driver.
 */
#define IRTHERMO5V_SET_DEV_ADDR  0x5A

/*! @} */ // irthermo5v_set

/**
 * @defgroup irthermo5v_map IrThermo 5V MikroBUS Map
 * @brief MikroBUS pin mapping of IrThermo 5V Click driver.
 */

/**
 * @addtogroup irthermo5v_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IrThermo 5V Click to the selected MikroBUS.
 */
#define IRTHERMO5V_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // irthermo5v_map
/*! @} */ // irthermo5v

/**
 * @brief IrThermo 5V Click context object.
 * @details Context object definition of IrThermo 5V Click driver.
 */
typedef struct
{
    // Input pins

    digital_in_t  pwm;       

    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} irthermo5v_t;

/**
 * @brief IrThermo 5V Click configuration object.
 * @details Configuration object definition of IrThermo 5V Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  pwm;      

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} irthermo5v_cfg_t;

/**
 * @brief IrThermo 5V Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   IRTHERMO5V_OK = 0,
   IRTHERMO5V_ERROR = -1

} irthermo5v_return_value_t;

/*!
 * @addtogroup irthermo5v IrThermo 5V Click Driver
 * @brief API for configuring and manipulating IrThermo 5V Click driver.
 * @{
 */

/**
 * @brief IrThermo 5V configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #irthermo5v_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 */
void irthermo5v_cfg_setup ( irthermo5v_cfg_t *cfg );

/**
 * @brief IrThermo 5V initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #irthermo5v_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #irthermo5v_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 */
err_t irthermo5v_init ( irthermo5v_t *ctx, irthermo5v_cfg_t *cfg );

/**
 * @brief Reads Temperature ambient from sensor.
 * @details Function returns ambient temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #irthermo5v_t object definition for detailed explanation.
 * @return Ambient temperature value in Celsius.
 * 
 * @note None.
 */
float irthermo5v_get_t_ambient ( irthermo5v_t* ctx );

/**
 * @brief Reads Temperature object1 from sensor.
 * @details Function returns object temperature value in Celsius.
 * @param[in] ctx : Click context object.
 * See #irthermo5v_t object definition for detailed explanation.
 * @return Object temperature value in Celsius.
 * 
 * @note None.
 */
float irthermo5v_get_t_object ( irthermo5v_t* ctx );

/**
 * @brief Generic function for reading values from RAM.
 * @details Function returns 16bit value of register.
 * @param[in] ctx : Click context object.
 * See #irthermo5v_t object definition for detailed explanation.
 * @param[in] address :  Address of register
 * @return 16bit value of register.
 * 
 * @note None.
 */
uint16_t irthermo5v_read_reg ( irthermo5v_t* ctx, uint8_t address );


#ifdef __cplusplus
}
#endif
#endif // IRTHERMO5V_H

/*! @} */ // irthermo5v

// ------------------------------------------------------------------------ END
