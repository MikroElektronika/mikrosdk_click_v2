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
 * @file digipot7.h
 * @brief This file contains API for DIGI POT 7 Click Driver.
 */

#ifndef DIGIPOT7_H
#define DIGIPOT7_H

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
 * @addtogroup digipot7 DIGI POT 7 Click Driver
 * @brief API for configuring and manipulating DIGI POT 7 Click driver.
 * @{
 */

/**
 * @defgroup digipot7_set DIGI POT 7 Registers Settings
 * @brief Settings for registers of DIGI POT 7 Click driver.
 */

/**
 * @addtogroup digipot7_set
 * @{
 */

/**
 * @brief DIGI POT 7 description setting.
 * @details Specified setting for description of DIGI POT 7 Click driver.
 */

/**
 * @brief DIGI POT 7 device commands.
 * @details Specified commands of DIGI POT 7 Click driver.
 */
#define DIGIPOT7_COMMAND_NOP                        0x00
#define DIGIPOT7_COMMAND_WRITE_RDAC                 0x04
#define DIGIPOT7_COMMAND_READ_RDAC                  0x08
#define DIGIPOT7_COMMAND_STORE_WIPER                0x0C
#define DIGIPOT7_COMMAND_SW_RESET                   0x10
#define DIGIPOT7_COMMAND_READ_50TP                  0x14
#define DIGIPOT7_COMMAND_READ_MEMORY                0x18
#define DIGIPOT7_COMMAND_WRITE_MEMORY               0x1C
#define DIGIPOT7_COMMAND_READ_CONTROL               0x20
#define DIGIPOT7_COMMAND_SW_SHUTDOWN                0x24

/**
 * @brief DIGI POT 7 device software shutdown setting.
 * @details Specified setting for software shutdown of DIGI POT 7 Click driver.
 */
#define DIGIPOT7_SHUTDOWN_BIT_MASK                  0x01
#define DIGIPOT7_NORMAL_MODE                        0x00
#define DIGIPOT7_SHUTDOWN_MODE                      0x01

/**
 * @brief DIGI POT 7 device bit map setting.
 * @details Specified setting for bit map of DIGI POT 7 Click driver.
 */
#define DIGIPOT7_CTRL_REG_BIT_MASK                  0x0B
#define DIGIPOT7_FUSE_PROGRAM_SUCCESSFUL            0x00
#define DIGIPOT7_FUSE_PROGRAM_UNSUCCESSFUL          0x08
#define DIGIPOT7_WIPER_POS_FROZEN                   0x00
#define DIGIPOT7_UPDATE_WIPER_POS                   0x02
#define DIGIPOT7_50T_PROGRAM_DISABLED               0x00
#define DIGIPOT7_50T_PROGRAM_ENABLE                 0x01

/**
 * @brief DIGI POT 7 device state setting.
 * @details Specified setting for state of DIGI POT 7 Click driver.
 */
#define DIGIPOT7_10_BIT                           0x03FF
#define DIGIPOT7_DUMMY                            0x0000

/**
 * @brief DIGI POT 7 device address setting.
 * @details Specified setting for device slave address selection of
 * DIGI POT 7 Click driver.
 */
#define DIGIPOT7_I2C_SLAVE_ADDRESS_GND              0x2F
#define DIGIPOT7_I2C_SLAVE_ADDRESS_VCC              0x2C
#define DIGIPOT7_I2C_SLAVE_ADDRESS_NC               0x2E

/*! @} */ // digipot7_set

/**
 * @defgroup digipot7_map DIGI POT 7 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI POT 7 Click driver.
 */

/**
 * @addtogroup digipot7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI POT 7 Click to the selected MikroBUS.
 */
#define DIGIPOT7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )
    
/*! @} */ // digipot7_map
/*! @} */ // digipot7

/**
 * @brief DIGI POT 7 Click context object.
 * @details Context object definition of DIGI POT 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;     /**< Reset. */

    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} digipot7_t;

/**
 * @brief DIGI POT 7 Click configuration object.
 * @details Configuration object definition of DIGI POT 7 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;       /**< Reset. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} digipot7_cfg_t;

/**
 * @brief DIGI POT 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   DIGIPOT7_OK = 0,
   DIGIPOT7_ERROR = -1

} digipot7_return_value_t;

/*!
 * @addtogroup digipot7 DIGI POT 7 Click Driver
 * @brief API for configuring and manipulating DIGI POT 7 Click driver.
 * @{
 */

/**
 * @brief DIGI POT 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digipot7_cfg_t object definition for detailed explanation.
 * 
 * @return Nothing.
 * 
 * @note The all used pins will be set to unconnected state.
 */
void digipot7_cfg_setup ( digipot7_cfg_t *cfg );

/**
 * @brief DIGI POT 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digipot7_cfg_t object definition for detailed explanation.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t digipot7_init ( digipot7_t *ctx, digipot7_cfg_t *cfg );

/**
 * @brief DIGI POT 7 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * @param[in] cmd : Start register address.
 * @param[in] data_byte : Data to be written.
 *
 * @return Nothing.
 */
void digipot7_generic_write ( digipot7_t *ctx, uint8_t cmd, uint16_t data_byte );

/**
 * @brief DIGI POT 7 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * @param[in] cmd : Command operation.
 * See #digipot7_set object definition for detailed explanation.
 * @param[in] wiper_pos : 10-bit data to be written.
 * 
 * @return 10-bit read data.
 */
uint16_t digipot7_generic_read ( digipot7_t *ctx, uint8_t cmd, uint8_t wiper_pos );

/**
 * @brief Hardware reset function.
 * @details The function reset the
 * AD5175 Single-Channel, 1024-Position, Digital Rheostat with I2C Interface
 * and 50-TP Memory on the DIGI POT 7 click board.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * 
 * @return Nothing.
 */
void digipot7_hw_reset ( digipot7_t *ctx );

/**
 * @brief Enable write function.
 * @details The function enable write of the
 * AD5175 Single-Channel, 1024-Position, Digital Rheostat with I2C Interface
 * and 50-TP Memory on the DIGI POT 7 click board.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * 
 * @return Nothing.
 */
void digipot7_enable_write ( digipot7_t *ctx );

/**
 * @brief Read RDAC function.
 * @details The function read a 10-bit RDAC data of the
 * AD5175 Single-Channel, 1024-Position, Digital Rheostat with I2C Interface
 * and 50-TP Memory on the DIGI POT 7 click board.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * 
 * @return 10-bit read data.
 * 
 */
uint16_t digipot7_read_rdac ( digipot7_t *ctx );

/**
 * @brief Write RDAC function.
 * @details The function writes a 10-bit RDAC data of the
 * AD5175 Single-Channel, 1024-Position, Digital Rheostat with I2C Interface
 * and 50-TP Memory on the DIGI POT 7 click board.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * @param[in] rdac_data : 10-bit rdac data.
 * 
 * @return Nothing.
 * 
 */
void digipot7_write_rdac ( digipot7_t *ctx, uint16_t rdac_data );

/**
 * @brief Set resistance function.
 * @details The function writes a 10-bit RDAC data of the
 * AD5175 Single-Channel, 1024-Position, Digital Rheostat with I2C Interface
 * and 50-TP Memory on the DIGI POT 7 click board.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * @param[in] res_ohm : Resistance ( ohm ) from 0 to 10000.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t digipot7_set_resistance ( digipot7_t *ctx, uint16_t res_ohm );

/**
 * @brief Software reset function.
 * @details The function software reset the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the DIGI POT 7 click board.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * 
 * @return Nothing.
 */
void digipot7_sw_reset ( digipot7_t *ctx );

/**
 * @brief Store wiper setting function.
 * @details The function store wiper setting, store RDAC setting to 50-TP
 * of the AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the DIGI POT 7 click board.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * 
 * @return Nothing.
 */
void digipot7_store_wiper ( digipot7_t *ctx );

/**
 * @brief Set operating mode function.
 * @details The function set operating mode of the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the DIGI POT 7 click board.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * @param[in] mode : Software shutdown options.
 *
 * @return Nothing.
 */
void digipot7_operating_mode ( digipot7_t *ctx, uint8_t mode );

/**
 * @brief Next frame read function.
 * @details The function next frame read of the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the DIGI POT 7 click board.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * @param[in] wiper_location : Wiper location ( from 0x00 to the 0x38 ).
 *
 * @return 10-bit read data.
 */
uint16_t digipot7_next_frame_read ( digipot7_t *ctx, uint8_t wiper_location );

/**
 * @brief Read memory function.
 * @details The function read address of the
 * last 50-TP programmed memory location of the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the DIGI POT 7 click board.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * 
 * @return 10-bit read data.
 */
uint16_t digipot7_read_memory ( digipot7_t *ctx );

/**
 * @brief Read control register function.
 * @details The function read contents of the control register of the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the DIGI POT 7 click board.
 * @param[in] ctx : Click context object.
 * See #digipot7_t object definition for detailed explanation.
 * 
 * @return control data 
 */
uint8_t digipot7_read_control ( digipot7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DIGIPOT7_H

/*! @} */ // digipot7

// ------------------------------------------------------------------------ END
