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
 * @file i2c1wire2.h
 * @brief This file contains API for I2C 1-Wire 2 Click Driver.
 */

#ifndef I2C1WIRE2_H
#define I2C1WIRE2_H

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
 * @addtogroup i2c1wire2 I2C 1-Wire 2 Click Driver
 * @brief API for configuring and manipulating I2C 1-Wire 2 Click driver.
 * @{
 */

/**
 * @defgroup i2c1wire2_reg I2C 1-Wire 2 Registers List
 * @brief List of registers of I2C 1-Wire 2 Click driver.
 */

/**
 * @addtogroup i2c1wire2_reg
 * @{
 */

/**
 * @brief I2C 1-Wire 2 description register.
 * @details Specified register for description of I2C 1-Wire 2 Click driver.
 */
#define I2C1WIRE2_REG_MASTER_CFG                    0x00
#define I2C1WIRE2_REG_STD_SPEED_TRSTL               0x01
#define I2C1WIRE2_REG_STD_SPEED_TMSI                0x02
#define I2C1WIRE2_REG_STD_SPEED_TMSP                0x03
#define I2C1WIRE2_REG_STD_SPEED_TRTH                0x04
#define I2C1WIRE2_REG_STD_SPEED_TW0L                0x05
#define I2C1WIRE2_REG_STD_SPEED_TW1L                0x06
#define I2C1WIRE2_REG_STD_SPEED_TMSR                0x07
#define I2C1WIRE2_REG_STD_SPEED_TREC                0x08
#define I2C1WIRE2_REG_OVER_SPEED_TRSTL              0x09
#define I2C1WIRE2_REG_OVER_SPEED_TMSI               0x0A
#define I2C1WIRE2_REG_OVER_SPEED_TMSP               0x0B
#define I2C1WIRE2_REG_OVER_SPEED_TRTH               0x0C
#define I2C1WIRE2_REG_OVER_SPEED_TW0L               0x0D
#define I2C1WIRE2_REG_OVER_SPEED_TW1L               0x0E
#define I2C1WIRE2_REG_OVER_SPEED_TMSR               0x0F
#define I2C1WIRE2_REG_OVER_SPEED_TREC               0x10
#define I2C1WIRE2_REG_PRUP_BUFF                     0x11
#define I2C1WIRE2_REG_PDSLEW                        0x12

/**
 * @brief I2C 1-Wire 2 commands.
 * @details Specified commands for description of I2C 1-Wire 2 Click driver.
 */
#define I2C1WIRE2_CMD_WRITE_MEMORY                  0x96
#define I2C1WIRE2_CMD_READ_MEMORY                   0x44
#define I2C1WIRE2_CMD_SET_PAGE_PROTECTION           0xC3
#define I2C1WIRE2_CMD_READ_STATUS                   0xAA
#define I2C1WIRE2_CMD_READ_1WIRE_PORT_CFG           0x52
#define I2C1WIRE2_CMD_WRITE_1WIRE_PORT_CFG          0x99
#define I2C1WIRE2_CMD_MASTER_RESET                  0x62
#define I2C1WIRE2_CMD_1WIRE_SCRIPT                  0x88
#define I2C1WIRE2_CMD_1WIRE_BLOCK                   0xAB
#define I2C1WIRE2_CMD_1WIRE_READ_BLOCK              0x50
#define I2C1WIRE2_CMD_1WIRE_WRITE_BLOCK             0x68
#define I2C1WIRE2_CMD_1WIRE_SEARCH                  0x11
#define I2C1WIRE2_CMD_FULL_COMMAND_SEQUENCE         0x57
#define I2C1WIRE2_CMD_COMPUTE_CRC16                 0xCC




/*! @} */ // i2c1wire2_reg

/**
 * @defgroup i2c1wire2_set I2C 1-Wire 2 Registers Settings
 * @brief Settings for registers of I2C 1-Wire 2 Click driver.
 */

/**
 * @addtogroup i2c1wire2_set
 * @{
 */

/**
 * @brief I2C 1-Wire 2 description setting.
 * @details Specified setting for description of I2C 1-Wire 2 Click driver.
 */
#define I2C1WIRE2_CUSTOM_VAL                        0x80
#define I2C1WIRE2_RWPU_EXT                          0x00
#define I2C1WIRE2_RWPU_500                          0x01
#define I2C1WIRE2_RWPU_1000                         0x02
#define I2C1WIRE2_RWPU_333                          0x03
#define I2C1WIRE2_VIAPO_LOW                         0x00
#define I2C1WIRE2_VIAPO_MEDIUM                      0x04
#define I2C1WIRE2_VIAPO_HIGH                        0x08
#define I2C1WIRE2_VIAPO_OFF                         0x0C
#define I2C1WIRE2_VTH_LOW                           0x00
#define I2C1WIRE2_VTH_MEDIUM                        0x01
#define I2C1WIRE2_VTH_HIGH                          0x02
#define I2C1WIRE2_VTH_OFF                           0x03

/**
 * @brief I2C 1-Wire 2 search command setting.
 * @details Specified setting for search command of I2C 1-Wire 2 Click driver.
 */
#define I2C1WIRE2_SEARCH_1WIRE_RESET                0x01
#define I2C1WIRE2_SEARCH_IGNORE_PULSE               0x02
#define I2C1WIRE2_SEARCH_RESET                      0x04

/**
 * @brief I2C 1-Wire 2 Result byte setting.
 * @details Specified setting for Result byte of I2C 1-Wire 2 Click driver.
 */
#define I2C1WIRE2_RESULT_BYTE_OK                    0xAA
#define I2C1WIRE2_RESULT_BYTE_ERROR                 0x55
#define I2C1WIRE2_NO_PRESENCE_PULS                  0x33
#define I2C1WIRE2_NO_DEVICE_DETECTED                0x00
#define I2C1WIRE2_RESULT_BYTE_ERROR_INVALID_PARAMS  0x77
#define I2C1WIRE2_RESULT_BYTE_ERROR_RESET_FAIL      0x22

/**
 * @brief I2C 1-Wire 2 device address setting.
 * @details Specified setting for device slave address selection of
 * I2C 1-Wire 2 Click driver.
 */
#define I2C1WIRE2_DEVICE_ADDRESS                    0x40

/*! @} */ // i2c1wire2_set

/**
 * @defgroup i2c1wire2_map I2C 1-Wire 2 MikroBUS Map
 * @brief MikroBUS pin mapping of I2C 1-Wire 2 Click driver.
 */

/**
 * @addtogroup i2c1wire2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of I2C 1-Wire 2 Click to the selected MikroBUS.
 */
#define I2C1WIRE2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // i2c1wire2_map
/*! @} */ // i2c1wire2

/**
 * @brief I2C 1-Wire 2 Click context object.
 * @details Context object definition of I2C 1-Wire 2 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} i2c1wire2_t;

/**
 * @brief I2C 1-Wire 2 Click configuration object.
 * @details Configuration object definition of I2C 1-Wire 2 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} i2c1wire2_cfg_t;

/**
 * @brief I2C 1-Wire 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    I2C1WIRE2_OK = 0,
    I2C1WIRE2_ERROR = -1

} i2c1wire2_return_value_t;

/*!
 * @addtogroup i2c1wire2 I2C 1-Wire 2 Click Driver
 * @brief API for configuring and manipulating I2C 1-Wire 2 Click driver.
 * @{
 */

/**
 * @brief I2C 1-Wire 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #i2c1wire2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void i2c1wire2_cfg_setup ( i2c1wire2_cfg_t *cfg );

/**
 * @brief I2C 1-Wire 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #i2c1wire2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #i2c1wire2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2c1wire2_init ( i2c1wire2_t *ctx, i2c1wire2_cfg_t *cfg );

/**
 * @brief I2C 1-Wire 2 default configuration function.
 * @details This function executes a default configuration of I2C 1-Wire 2 
 * Click board.
 * @param[in] ctx : Click context object.
 * See #i2c1wire2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t i2c1wire2_default_cfg ( i2c1wire2_t *ctx );

/**
 * @brief I2C 1-Wire 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2c1wire2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2c1wire2_generic_write ( i2c1wire2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief I2C 1-Wire 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #i2c1wire2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2c1wire2_generic_read ( i2c1wire2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief I2C 1-Wire 2 master reset function.
 * @details This function is used to reset device, and return all configuration registers to the default values.
 * @param[in] ctx : Click context object.
 * See #i2c1wire2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2c1wire2_master_reset ( i2c1wire2_t *ctx );

/**
 * @brief I2C 1-Wire 2 read port configuration function.
 * @details This function is used to read one or all configuration registers.
 * @param[in] ctx : Click context object.
 * See #i2c1wire2_t object definition for detailed explanation.
 * @param[in] reg : Selected register.
 * @param[out] data_out : Register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2c1wire2_read_port_cfg ( i2c1wire2_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief I2C 1-Wire 2 write port configuration function.
 * @details This function is used to write a 1-Wire configuration register.
 * @param[in] ctx : Click context object.
 * See #i2c1wire2_t object definition for detailed explanation.
 * @param[in] reg : Selected register.
 * @param[in] data_in : Register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2c1wire2_write_port_cfg ( i2c1wire2_t *ctx, uint8_t reg, uint8_t *data_in );

/**
 * @brief I2C 1-Wire 2 search function.
 * @details This function is used to perform 1-Wire Search algorithm and return one device ROMID.
 * @param[in] ctx : Click context object.
 * See #i2c1wire2_t object definition for detailed explanation.
 * @param[out] flag : Search algorithm result.
 * @param[out] rom_id : Read ROMID.
 * @param[out] last_flag : Last device flag.
 * @param[in] param_data : Search algorithm parameters.
 * @param[in] command_code : Search Command code for device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2c1wire2_search ( i2c1wire2_t *ctx, uint8_t *flag, uint8_t *rom_id, uint8_t *last_flag, uint8_t param_data, uint8_t command_code );

#ifdef __cplusplus
}
#endif
#endif // I2C1WIRE2_H

/*! @} */ // i2c1wire2

// ------------------------------------------------------------------------ END
