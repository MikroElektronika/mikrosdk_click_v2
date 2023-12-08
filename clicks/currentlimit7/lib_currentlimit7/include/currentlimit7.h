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
 * @file currentlimit7.h
 * @brief This file contains API for Current Limit 7 Click Driver.
 */

#ifndef CURRENTLIMIT7_H
#define CURRENTLIMIT7_H

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
 * @addtogroup currentlimit7 Current Limit 7 Click Driver
 * @brief API for configuring and manipulating Current Limit 7 Click driver.
 * @{
 */

/**
 * @defgroup currentlimit7_reg Current Limit 7 Registers List
 * @brief List of registers of Current Limit 7 Click driver.
 */

/**
 * @addtogroup currentlimit7_cmd
 * @{
 */

/**
 * @brief Current Limit 7 description register.
 * @details Specified commands for description of Current Limit 7 Click driver.
 */
#define CURRENTLIMIT7_CMD_NOP                        0x00
#define CURRENTLIMIT7_CMD_WRITE_RDAC                 0x04
#define CURRENTLIMIT7_CMD_READ_RDAC                  0x08
#define CURRENTLIMIT7_CMD_STORE_WIPER                0x0C
#define CURRENTLIMIT7_CMD_SW_RESET                   0x10
#define CURRENTLIMIT7_CMD_READ_CONTENTS              0x14
#define CURRENTLIMIT7_CMD_READ_MEMORY                0x18
#define CURRENTLIMIT7_CMD_WRITE_MEMORY               0x1C
#define CURRENTLIMIT7_CMD_READ_CTRL                  0x20
#define CURRENTLIMIT7_CMD_SW_SHUTDOWN                0x24

/*! @} */ // currentlimit7_cmd

/**
 * @defgroup currentlimit7_set Current Limit 7 Registers Settings
 * @brief Settings for registers of Current Limit 7 Click driver.
 */

/**
 * @addtogroup currentlimit7_set
 * @{
 */

/**
 * @brief Current Limit 7 description current limit values.
 * @details Specified current limit values for description of Current Limit 7 Click driver.
 */
#define CURRENTLIMIT7_OP_0_CURRENT_LIMIT_260_mA       260
#define CURRENTLIMIT7_OP_0_CURRENT_LIMIT_280_mA       280
#define CURRENTLIMIT7_OP_0_CURRENT_LIMIT_330_mA       330
#define CURRENTLIMIT7_OP_0_CURRENT_LIMIT_450_mA       450
#define CURRENTLIMIT7_OP_0_CURRENT_LIMIT_510_mA       510
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_510_mA       510
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_625_mA       625
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_860_mA       860
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1320_mA     1320
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1450_mA     1450
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1550_mA     1550
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1750_mA     1750
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_2020_mA     2020
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_2260_mA     2260
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_2500_mA     2500

/**
 * @brief Current Limit 7 description setting.
 * @details Specified setting for description of Current Limit 7 Click driver.
 */
#define CURRENTLIMIT7_SET_SHUTDOWN_BIT_MASK          0x01
#define CURRENTLIMIT7_SET_NORMAL_MODE                0x00
#define CURRENTLIMIT7_SET_SHUTDOWN_MODE              0x01
#define CURRENTLIMIT7_SET_ENABLE_WRITE_MEMORY        0x0002

/**
 * @brief Current Limit 7 description operation mode.
 * @details Specified operation mode for description of Current Limit 7 Click driver.
 */
#define CURRENTLIMIT7_OP_MODE_500_mA_2500_mA         0x00
#define CURRENTLIMIT7_OP_MODE_250_mA_500_mA          0x01

/**
 * @brief Current Limit 7 device address setting.
 * @details Specified setting for device slave address selection of
 * Current Limit 7 Click driver.
 */
#define CURRENTLIMIT7_SET_DEV_ADDR_0                 0x2E
#define CURRENTLIMIT7_SET_DEV_ADDR_1                 0x2C

/*! @} */ // currentlimit7_set

/**
 * @defgroup currentlimit7_map Current Limit 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Current Limit 7 Click driver.
 */

/**
 * @addtogroup currentlimit7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current Limit 7 Click to the selected MikroBUS.
 */
#define CURRENTLIMIT7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );   \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );   \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );     \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.flg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // currentlimit7_map
/*! @} */ // currentlimit7

/**
 * @brief Current Limit 7 Click context object.
 * @details Context object definition of Current Limit 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en;      /**< Enable pin. */
    digital_out_t  rst;     /**< Reset pin.  */

    // Input pins
    digital_in_t  flg;       /**< Flag pin . */

    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

} currentlimit7_t;

/**
 * @brief Current Limit 7 Click configuration object.
 * @details Configuration object definition of Current Limit 7 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;         /**< Enable pin. */
    pin_name_t  rst;        /**< Reset pin.  */
    pin_name_t  flg;        /**< Flag pin . */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} currentlimit7_cfg_t;

/**
 * @brief Current Limit 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENTLIMIT7_OK = 0,
    CURRENTLIMIT7_ERROR = -1

} currentlimit7_return_value_t;

/*!
 * @addtogroup currentlimit7 Current Limit 7 Click Driver
 * @brief API for configuring and manipulating Current Limit 7 Click driver.
 * @{
 */

/**
 * @brief Current Limit 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #currentlimit7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void currentlimit7_cfg_setup ( currentlimit7_cfg_t *cfg );

/**
 * @brief Current Limit 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #currentlimit7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_init ( currentlimit7_t *ctx, currentlimit7_cfg_t *cfg );

/**
 * @brief Current Limit 7 default configuration function.
 * @details This function executes a default configuration of Current Limit 7
 * click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t currentlimit7_default_cfg ( currentlimit7_t *ctx );

/**
 * @brief Current Limit 7 set I2C Slave address.
 * @details Sets I2C address of the subordinate I2C device
 * to \p slave_address which is targeted by read and write operations.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @param[in] slave_address Specified I2C slave address.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note It is recommended to check return value for error.
 */
err_t currentlimit7_set_slave_address ( currentlimit7_t *ctx, uint16_t slave_address );

/**
 * @brief Current Limit 7 hardware reset function.
 * @details This function performs the hardware reset 
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_hw_reset ( currentlimit7_t *ctx );

/**
 * @brief Current Limit 7 enable the device function.
 * @details This function enable the MAX14575,  
 * 250mA to 2.5A Adjustable Current-Limit Switches
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_set_enable ( currentlimit7_t *ctx );

/**
 * @brief Current Limit 7 disable the device function.
 * @details This function enable the MAX14575,  
 * 250mA to 2.5A Adjustable Current-Limit Switches
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_set_disable ( currentlimit7_t *ctx );

/**
 * @brief Current Limit 7 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] data_byte : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_generic_write ( currentlimit7_t *ctx, uint8_t cmd, uint16_t data_byte );

/**
 * @brief Current Limit 7 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[in] data_byte : Data to be written.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_generic_read ( currentlimit7_t *ctx, uint8_t cmd, uint16_t data_byte, uint16_t *data_out );

/**
 * @brief Current Limit 7 enable write function.
 * @details This function set command enable write 
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_enable_write ( currentlimit7_t *ctx );

/**
 * @brief Current Limit 7 write RDAC function.
 * @details This function writes a 10-bit RDAC 
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] data_in : 10-bit RDAC data.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_write_rdac ( currentlimit7_t *ctx, uint16_t data_in );

/**
 * @brief Current Limit 7 read RDAC function.
 * @details This function read a 10-bit RDAC 
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_read_rdac ( currentlimit7_t *ctx, uint16_t *data_out );

/**
 * @brief Current Limit 7 software reset function.
 * @details This function performs the software reset 
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_sw_reset ( currentlimit7_t *ctx );

/**
 * @brief Current Limit 7 store wiper function.
 * @details This function store wiper setting, store RDAC setting to 50-TP 
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_store_wiper ( currentlimit7_t *ctx );

/**
 * @brief Current Limit 7 next frame read function.
 * @details This function next frame read 
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @param[in] wiper_location : Wiper location ( from 0x00 to the 0x38 ).
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_next_frame_read ( currentlimit7_t *ctx, uint8_t wiper_location, uint16_t *data_out );

/**
 * @brief Current Limit 7 read memory function.
 * @details This function read memory
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @param[in] wiper_location : Wiper location ( from 0x00 to the 0x38 ).
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_read_memory ( currentlimit7_t *ctx, uint8_t wiper_location, uint16_t *data_out );

/**
 * @brief Current Limit 7 set operating mode function.
 * @details This function select operating mode, Shutdown or Normal mode
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @param[in] mode : Operating mode: Shutdown or Normal mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_operating_mode ( currentlimit7_t *ctx, uint8_t mode );

/**
 * @brief Current Limit 7 set DIGI POT function.
 * @details This function set DIGI POT wiper position 
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @param[in] wiper_pos : Wiper position ( from 0 to 2047 ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_set_digi_pot ( currentlimit7_t *ctx, uint16_t wiper_pos );

/**
 * @brief Current Limit 7 set resistance function.
 * @details This function set resistance 
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @param[in] res_ohm : Resistance [ Ohm ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_set_resistance ( currentlimit7_t *ctx, uint32_t res_ohm );

/**
 * @brief Current Limit 7 set current limit function.
 * @details This function set current limit 
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @param[in] op_mode : Operating mode:
 *         @li @c  0 ( CURRENTLIMIT7_OP_MODE_500_mA_2500_mA ) - Limit range from 500 mA to 2500 mA.
 *         @li @c  1 ( CURRENTLIMIT7_OP_MODE_250_mA_500_mA )  - Limit range from 250 mA to 500 mA.
 * @param[in] current_limit_ma : current limit [ mA ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit7_set_current_limit ( currentlimit7_t *ctx, uint8_t op_mode, uint16_t current_limit_ma );

/**
 * @brief Current Limit 7 get fault function.
 * @details This function get state of the FLT ( INT ) pin 
 * of the selected AD5272, 1024-Position, 1% Resistor Tolerance Error, 
 * I2C Interface and 50-TP Memory Digital Rheostat
 * on the Current Limit 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #currentlimit7_t object definition for detailed explanation.
 * @return @li @c 0 - Overload fault duration exceeds the blanking time, 
 * reverse current is detected, thermal shutdown mode is active.
 *         @li @c 1 - Ok.
 *
 * @note None.
 */
uint8_t currentlimit7_get_fault ( currentlimit7_t *ctx );



#ifdef __cplusplus
}
#endif
#endif // CURRENTLIMIT7_H

/*! @} */ // currentlimit7

// ------------------------------------------------------------------------ END
