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
 * @file solidswitch.h
 * @brief This file contains API for SolidSwitch Click Driver.
 */

#ifndef SOLIDSWITCH_H
#define SOLIDSWITCH_H

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
 * @addtogroup solidswitch SolidSwitch Click Driver
 * @brief API for configuring and manipulating SolidSwitch Click driver.
 * @{
 */

/**
 * @defgroup solidswitch_set SolidSwitch Registers Settings
 * @brief Settings for registers of SolidSwitch Click driver.
 */

/**
 * @addtogroup solidswitch_set
 * @{
 */

/**
 * @brief SolidSwitch description setting.
 * @details Specified setting for description of SolidSwitch Click driver.
 */
#define SOLIDSWITCH_ENABLE_OUT7             0x80
#define SOLIDSWITCH_ENABLE_OUT6             0x40
#define SOLIDSWITCH_ENABLE_OUT1             0x02
#define SOLIDSWITCH_ENABLE_OUT0             0x01
#define SOLIDSWITCH_ENABLE_ALL_OUTPUTS      0xC3
#define SOLIDSWITCH_DISABLE_ALL_OUTPUTS     0x00

/**
 * @brief SolidSwitch device address setting.
 * @details Specified setting for device slave address selection of
 * SolidSwitch Click driver.
 */
#define SOLIDSWITCH_DEV_ADDR_A1_GND_A0_GND  0x68
#define SOLIDSWITCH_DEV_ADDR_A1_GND_A0_VCC  0x69
#define SOLIDSWITCH_DEV_ADDR_A1_VCC_A0_GND  0x6C
#define SOLIDSWITCH_DEV_ADDR_A1_VCC_A0_VCC  0x6D

/*! @} */ // solidswitch_set

/**
 * @defgroup solidswitch_map SolidSwitch MikroBUS Map
 * @brief MikroBUS pin mapping of SolidSwitch Click driver.
 */

/**
 * @addtogroup solidswitch_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SolidSwitch Click to the selected MikroBUS.
 */
#define SOLIDSWITCH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // solidswitch_map
/*! @} */ // solidswitch

/**
 * @brief SolidSwitch Click context object.
 * @details Context object definition of SolidSwitch Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  rst;        /**< Reset pin - output. */
    
    // Input pins
    
    digital_in_t  int_pin;     /**< Interrupt pin - input. */

    // Modules

    i2c_master_t i2c;          /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;     /**< Device slave address (used for I2C driver). */

} solidswitch_t;

/**
 * @brief SolidSwitch Click configuration object.
 * @details Configuration object definition of SolidSwitch Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;        /**< Reset pin. */
    pin_name_t  int_pin;    /**< Interrupt pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} solidswitch_cfg_t;

/**
 * @brief SolidSwitch Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SOLIDSWITCH_OK = 0,
    SOLIDSWITCH_ERROR = -1

} solidswitch_return_value_t;

/*!
 * @addtogroup solidswitch SolidSwitch Click Driver
 * @brief API for configuring and manipulating SolidSwitch Click driver.
 * @{
 */

/**
 * @brief SolidSwitch configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #solidswitch_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void solidswitch_cfg_setup ( solidswitch_cfg_t *cfg );

/**
 * @brief SolidSwitch initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #solidswitch_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #solidswitch_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t solidswitch_init ( solidswitch_t *ctx, solidswitch_cfg_t *cfg );

/**
 * @brief SolidSwitch default configuration function.
 * @details This function executes a default configuration of SolidSwitch
 * Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
err_t solidswitch_default_cfg ( solidswitch_t *ctx );

/**
 * @brief SolidSwitch I2C writing logic state function.
 * @details This function writes a single byte by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch_t object definition for detailed explanation.
 * @param[in] logic_state : Logic state mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t solidswitch_write_single ( solidswitch_t *ctx, uint8_t logic_state );

/**
 * @brief SolidSwitch I2C writing logic state and interrupt mask function.
 * @details This function writes two bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch_t object definition for detailed explanation.
 * @param[in] logic_state : Logic state mask.
 * @param[in] int_mask : Interrupt mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t solidswitch_write_two_bytes ( solidswitch_t *ctx, uint8_t logic_state, uint8_t int_mask );

/**
 * @brief SolidSwitch I2C reading logic state function.
 * @details This function reads a single byte by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch_t object definition for detailed explanation.
 * @param[out] logic_state : Logic state output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t solidswitch_read_single ( solidswitch_t *ctx, uint8_t *logic_state );

/**
 * @brief SolidSwitch I2C reading logic state and transition flags function.
 * @details This function reads two bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #solidswitch_t object definition for detailed explanation.
 * @param[out] logic_state : Logic state output.
 * @param[out] transition_flags : Transition flags output.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t solidswitch_read_two_bytes ( solidswitch_t *ctx, uint8_t *logic_state, uint8_t *transition_flags );

/**
 * @brief SolidSwitch reset function.
 * @details This function resets the device via rst pin.
 * @param[in] ctx : Click context object.
 * See #solidswitch_t object definition for detailed explanation.
 * @return None.
 *         
 * @note None.
 *
 * @endcode
 */
void solidswitch_reset ( solidswitch_t *ctx );

/**
 * @brief SolidSwitch get int pin state function.
 * @details This function reads the state of int pin.
 * @param[in] ctx : Click context object.
 * See #solidswitch_t object definition for detailed explanation.
 * @return INT pin state.
 *         
 * @note None.
 *
 * @endcode
 */
uint8_t solidswitch_get_int_state ( solidswitch_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SOLIDSWITCH_H

/*! @} */ // solidswitch

// ------------------------------------------------------------------------ END
