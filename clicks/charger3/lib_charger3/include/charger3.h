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
 * @file charger3.h
 * @brief This file contains API for Charger 3 Click Driver.
 */

#ifndef CHARGER3_H
#define CHARGER3_H

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
 * @addtogroup charger3 Charger 3 Click Driver
 * @brief API for configuring and manipulating Charger 3 Click driver.
 * @{
 */

/**
 * @addtogroup charger3_command
 * @{
 */

/**
 * @brief Charger 3 description commands.
 * @details Specified command description of Charger 3 Click driver.
 */

#define CHARGER3_COMMAND_NOP                                         0x00
#define CHARGER3_COMMAND_WRITE_RDAC                                  0x04
#define CHARGER3_COMMAND_READ_RDAC                                   0x08
#define CHARGER3_COMMAND_STORE_WIPER                                 0x0C
#define CHARGER3_COMMAND_SW_RESET                                    0x10
#define CHARGER3_COMMAND_READ_50TP                                   0x14
#define CHARGER3_COMMAND_READ_MEMORY                                 0x18
#define CHARGER3_COMMAND_WRITE_MEMORY                                0x1C
#define CHARGER3_COMMAND_READ_CONTROL                                0x20
#define CHARGER3_COMMAND_SW_SHUTDOWN                                 0x24

/*! @} */ // charger3_command

/**
 * @defgroup charger3_set Charger 3 Registers Settings
 * @brief Settings for registers of Charger 3 Click driver.
 */

/**
 * @addtogroup charger3_set
 * @{
 */

/**
 * @brief Charger 3 description setting.
 * @details Specified bit map of Charger 3 Click driver.
 */

#define CHARGER3_CTRL_REG_BIT_MASK                                   0x0B
#define CHARGER3_FUSE_PROGRAM_SUCCESSFUL                             0x00
#define CHARGER3_FUSE_PROGRAM_UNSUCCESSFUL                           0x08
#define CHARGER3_WIPER_POS_FROZEN                                    0x00
#define CHARGER3_UPDATE_WIPER_POS                                    0x02
#define CHARGER3_50T_PROGRAM_DISABLED                                0x00
#define CHARGER3_50T_PROGRAM_ENABLE                                  0x01

/**
 * @brief Charger 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Charger 3 Click driver.
 */

#define CHARGER3_SET_DEV_ADDR  0x2F

/*! @} */ // charger3_set

/**
 * @addtogroup mode
 * @{
 */

/**
 * @brief Charger 3 operating mode.
 * @details Operating modes of Charger 3 Click driver.
 */

#define CHARGER3_ENABLE_CHARGING                                     0x00
#define CHARGER3_DISABLE_CHARGING                                    0x01

/*! @} */ // mode

/**
 * @addtogroup status
 * @{
 */

/**
 * @brief Charger 3 error code.
 * @details Error codes for settings of Charger 3 Click driver.
 */

#define CHARGER3_STATUS_ERROR_SUCCESS                                0x00
#define CHARGER3_STATUS_ERROR_FAILURE                                0x01

/*! @} */ // status

/**
 * @addtogroup charger3_dummy
 * @{
 */

/**
 * @brief Charger 3 dummy command.
 * @details Dummy command of Charger 3 Click driver.
 */

#define CHARGER3_DUMMY                                               0x00

/*! @} */ // charger3_dummy

/**
 * @defgroup charger3_map Charger 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 3 Click driver.
 */

/**
 * @addtogroup charger3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 3 Click to the selected MikroBUS.
 */
#define CHARGER3_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // charger3_map
/*! @} */ // charger3

/**
 * @brief Charger 3 Click context object.
 * @details Context object definition of Charger 3 Click driver.
 */
typedef struct
{
    // Modules

    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} charger3_t;

/**
 * @brief Charger 3 Click configuration object.
 * @details Configuration object definition of Charger 3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                             /**< I2C serial speed. */
    uint8_t   i2c_address;                           /**< I2C slave address. */

} charger3_cfg_t;

/*!
 * @addtogroup charger3 Charger 3 Click Driver
 * @brief API for configuring and manipulating Charger 3 Click driver.
 * @{
 */

/**
 * @brief Charger 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 * @endcode
 */
void charger3_cfg_setup ( charger3_cfg_t *cfg );

/**
 * @brief Charger 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #charger3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t charger3_init ( charger3_t *ctx, charger3_cfg_t *cfg );

/**
 * @brief Charger 3 default configuration function.
 * @details This function executes a default configuration of Charger 3
 * Click board.
 * @param[in] ctx : Click context object.
 * See #charger3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 *
 * @endcode
 */
void charger3_default_cfg ( charger3_t *ctx );

/**
 * @brief Charger 3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t charger3_generic_write ( charger3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Charger 3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 * @endcode
 */
err_t charger3_generic_read ( charger3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Charger 3 enable write function.
 * @details This function enables write to the AD5175 Single-Channel,
 * 1024-Position, Digital Rheostat over I2C Interface.
 * @param[in] ctx : Click context object.
 * See #charger3_t object definition for detailed explanation.
 * 
 * @note None.
 *
 * @endcode
 */
void charger3_enable_write ( charger3_t *ctx );

/**
 * @brief Charger 3 set operating mode function.
 * @details This function shorts or creates open circuit on PROG pin 
 * enabling or disabling charging of the battery.
 * @param[in] ctx : Click context object.
 * See #charger3_t object definition for detailed explanation.
 * @param[in] mode : Operating mode.
 *     @li @c 0x00 ( CHARGER3_ENABLE_CHARGING )- Shorts PROG pin, enabling battery charging,
 *     @li @c 0x01 ( CHARGER3_DISABLE_CHARGING )- Creates open circuit on PROG pin, disabling battery charging.
 * 
 * @note None.
 *
 * @endcode
 */
void charger3_operating_mode ( charger3_t *ctx, uint8_t mode );

/**
 * @brief Charger 3 write to rdac function.
 * @details This function writes 10-bit data directly to the RDAC register of AD5175.
 * @param[in] ctx : Click context object.
 * See #charger3_t object definition for detailed explanation.
 * @param[in] rdac_data : RDAC value.
 * 
 * @note None.
 *
 * @endcode
 */
void charger3_write_rdac ( charger3_t *ctx, uint16_t rdac_data );

/**
 * @brief Charger 3 set digital potentiometer resistance function.
 * @details This function sets the actual resistance of AD5175 digital potentiometer.
 * @param[in] ctx : Click context object.
 * See #charger3_t object definition for detailed explanation.
 * @param[in] res_ohm : Resistance value.
 * @return @li @c 0x00 ( CHARGER3_STATUS_ERROR_SUCCESS ),
 *         @li @c 0x01 ( CHARGER3_STATUS_ERROR_FAILURE ).
 * 
 * @note When setting the total resistance on PROG pin,
 * keep in mind that there is 1kohm resistor in series
 * with the AD5175 digipot.
 *
 * @endcode
 */
uint8_t charger3_set_digipot_res ( charger3_t *ctx, uint16_t res_ohm );

/**
 * @brief Charger 3 set current function.
 * @details This function sets the battery charging current.
 * @param[in] ctx : Click context object.
 * See #charger3_t object definition for detailed explanation.
 * @param[in] curr_value : Current value.
 * @return @li @c 0x00 ( CHARGER3_STATUS_ERROR_SUCCESS ),
 *         @li @c 0x01 ( CHARGER3_STATUS_ERROR_FAILURE ).
 * 
 * @note None.
 *
 * @endcode
 */
uint8_t charger3_set_current ( charger3_t *ctx, float curr_value );

/**
 * @brief Charger 3 read rdac function.
 * @details This function reads the 10-bit value of RDAC register of AD5175.
 * @param[in] ctx : Click context object.
 * See #charger3_t object definition for detailed explanation.
 * @return Value of 10-bit RDAC register content.
 * 
 * @note None.
 *
 * @endcode
 */
uint16_t charger3_read_rdac ( charger3_t *ctx );

/**
 * @brief Charger 3 calculate digipot resistance function.
 * @details This function returns calculated resistance of AD5175.
 * @param[in] ctx : Click context object.
 * See #charger3_t object definition for detailed explanation.
 * @return Digipot resistance value.
 * 
 * @note If calculating the total resistance on PROG pin,
 * keep in mind that there is 1kohm resistor in series
 * with the AD5175 digipot.
 *
 * @endcode
 */
float charger3_calc_digipot_res ( charger3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CHARGER3_H

/*! @} */ // charger3

// ------------------------------------------------------------------------ END
