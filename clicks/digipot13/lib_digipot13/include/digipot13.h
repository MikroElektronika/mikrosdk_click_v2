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
 * @file digipot13.h
 * @brief This file contains API for DIGI POT 13 Click Driver.
 */

#ifndef DIGIPOT13_H
#define DIGIPOT13_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup digipot13 DIGI POT 13 Click Driver
 * @brief API for configuring and manipulating DIGI POT 13 Click driver.
 * @{
 */

/**
 * @defgroup digipot13_cmd DIGI POT 13 Registers List
 * @brief List of registers of DIGI POT 13 Click driver.
 */

/**
 * @addtogroup digipot13_cmd
 * @{
 */

/**
 * @brief DIGI POT 13 description command.
 * @details Specified control byte command for description of DIGI POT 13 Click driver.
 */
#define DIGIPOT13_CMD_VREG                           0x11
#define DIGIPOT13_CMD_NVREG                          0x21
#define DIGIPOT13_CMD_VREGxNVREG                     0x51
#define DIGIPOT13_CMD_NVREGxVREG                     0x61

/*! @} */ // digipot13_cmd

/**
 * @defgroup digipot13_set DIGI POT 13 Registers Settings
 * @brief Settings for registers of DIGI POT 13 Click driver.
 */

/**
 * @addtogroup digipot13_set
 * @{
 */

/**
 * @brief DIGI POT 13 wiper and resistance data values.
 * @details Specified wiper and resistance data values of DIGI POT 13 Click driver.
 */
#define DIGIPOT13_WIPER_POS_MIN                        0
#define DIGIPOT13_WIPER_POS_MIDDLE                   127
#define DIGIPOT13_WIPER_POS_MAX                      255
#define DIGIPOT13_RES_0_KOHM                           0
#define DIGIPOT13_RES_50_KOHM                         50
#define DIGIPOT13_RES_200_KOHM                       200

/**
 * @brief DIGI POT 13 device address setting.
 * @details Specified setting for device slave address selection of
 * DIGI POT 13 Click driver.
 */
#define DIGIPOT13_DEVICE_ADDRESS_GND                 0x28
#define DIGIPOT13_DEVICE_ADDRESS_VCC                 0x29

/*! @} */ // digipot13_set

/**
 * @defgroup digipot13_map DIGI POT 13 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI POT 13 Click driver.
 */

/**
 * @addtogroup digipot13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI POT 13 Click to the selected MikroBUS.
 */
#define DIGIPOT13_MAP_MIKROBUS( cfg, mikrobus )   \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )
/*! @} */ // digipot13_map
/*! @} */ // digipot13

/**
 * @brief DIGI POT 13 Click context object.
 * @details Context object definition of DIGI POT 13 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;         /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */

} digipot13_t;

/**
 * @brief DIGI POT 13 Click configuration object.
 * @details Configuration object definition of DIGI POT 13 Click driver.
 */
typedef struct
{
    pin_name_t scl;    /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;    /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;      /**< I2C serial speed. */
    uint8_t    i2c_address;    /**< I2C slave address. */

} digipot13_cfg_t;

/**
 * @brief DIGI POT 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIPOT13_OK = 0,
    DIGIPOT13_ERROR = -1

} digipot13_return_value_t;

/**
 * @brief DIGI POT 13 Click resistance configuration value data.
 * @details Predefined enum values for driver resistance configuration values.
 */
typedef enum
{
    DIGIPOT13_CFG_RES_WL = 0,    /**< Wiper to L. */
    DIGIPOT13_CFG_RES_WH         /**< Wiper to H. */

} digipot13_cfg_res_t;

/*!
 * @addtogroup digipot13 DIGI POT 13 Click Driver
 * @brief API for configuring and manipulating DIGI POT 13 Click driver.
 * @{
 */

/**
 * @brief DIGI POT 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digipot13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digipot13_cfg_setup ( digipot13_cfg_t *cfg );

/**
 * @brief DIGI POT 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #digipot13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digipot13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot13_init ( digipot13_t *ctx, digipot13_cfg_t *cfg );

/**
 * @brief DIGI POT 13 default configuration function.
 * @details This function executes a default configuration of DIGI POT 13
 * click board.
 * @param[in] ctx : Click context object.
 * See #digipot13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t digipot13_default_cfg ( digipot13_t *ctx );

/**
 * @brief DIGI POT 13 write data function.
 * @details This function writes a data bytes by using a desired command
 * of the MAX5419LETA+T, 256-Tap, Nonvolatile, I2C-Interface, Digital Potentiometers 
 * on the DIGI POT 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot13_t object definition for detailed explanation.
 * @param[in] cmd : Control byte.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot13_write_data ( digipot13_t *ctx, uint8_t cmd, uint8_t data_in );

/**
 * @brief DIGI POT 13 set the wiper position function.
 * @details This function sets the position of the wiper
 * of the MAX5419LETA+T, 256-Tap, Nonvolatile, I2C-Interface, Digital Potentiometers 
 * on the DIGI POT 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot13_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position [0-255].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot13_set_wiper_pos ( digipot13_t *ctx, uint8_t wiper_pos );

/**
 * @brief DIGI POT 13 set the resistance function.
 * @details This function sets the resistance
 * of the MAX5419LETA+T, 256-Tap, Nonvolatile, I2C-Interface, Digital Potentiometers 
 * on the DIGI POT 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot13_t object definition for detailed explanation.
 * @param[in] cfg_res : Resistance configuration.
 * See digipot13_cfg_res_t definition for detailed explanation.
 * @param[in] res_kohm : Resistance from 0.0 to 200.0 [kOhm].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot13_set_resistance ( digipot13_t *ctx, digipot13_cfg_res_t cfg_res, float res_kohm );

/**
 * @brief DIGI POT 13 data transfers volatile to nonvolatile function.
 * @details This function gets the value stored in the volatile memory
 * and writes in the non-volatile memory
 * of the MAX5419LETA+T, 256-Tap, Nonvolatile, I2C-Interface, Digital Potentiometers 
 * on the DIGI POT 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot13_switch_v_to_nv ( digipot13_t *ctx );

/**
 * @brief DIGI POT 13 data transfers nonvolatile to volatile function.
 * @details This function gets the value stored in the non-volatile memory
 * and writes in the volatile memory
 * of the MAX5419LETA+T, 256-Tap, Nonvolatile, I2C-Interface, Digital Potentiometers 
 * on the DIGI POT 13 Click board™.
 * @param[in] ctx : Click context object.
 * See #digipot13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot13_switch_nv_to_v ( digipot13_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DIGIPOT13_H

/*! @} */ // digipot13

// ------------------------------------------------------------------------ END
