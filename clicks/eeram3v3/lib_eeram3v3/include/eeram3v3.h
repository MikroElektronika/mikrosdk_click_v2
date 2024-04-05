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
 * @file eeram3v3.h
 * @brief This file contains API for EERAM 3v3 Click Driver.
 */
// ----------------------------------------------------------------------------

#ifndef EERAM3V3_H
#define EERAM3V3_H

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
 * @addtogroup eeram3v3 EERAM 3v3 Click Driver
 * @brief API for configuring and manipulating EERAM 3v3 Click driver.
 * @{
 */

/**
 * @defgroup eeram3v3_const EERAM 3v3 Const 
 * @brief List of Constants of EERAM 3v3 Click driver.
 */

/**
 * @addtogroup eeram3v3_const
 * @{
 */

/**
 * @brief EERAM 3v3 constants.
 * @details Specified values of constants of EERAM 3v3 Click driver.
 */
#define EERAM3V3_ADDRESS_SRAM       0x50
#define EERAM3V3_ADDRESS_CONTROL    0x18
#define EERAM3V3_CMD_STORE          0x33
#define EERAM3V3_CMD_RECALL         0xDD

/*! @} */ // eeram3v3_const

/**
 * @defgroup eeram3v3_map EERAM 3v3 MikroBUS Map
 * @brief MikroBUS pin mapping of EERAM 3v3 Click driver.
 */

/**
 * @addtogroup eeram3v3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EERAM 3v3 Click to the selected MikroBUS.
 */
#define EERAM3V3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.hs = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // eeram3v3_map
/*! @} */ // eeram3v3

/**
 * @brief EERAM 3v3 Click context object.
 * @details Context object definition of EERAM 3v3 Click driver.
 */
typedef struct
{

    digital_out_t  hs;            /**< Description. */

    // Modules
    
    i2c_master_t i2c;             /**< I2C driver object. */

    // I2C slave address
    
    uint8_t slave_address;        /**< Device slave address (used for I2C driver). */

} eeram3v3_t;

/**
 * @brief EERAM 3v3 Click configuration object.
 * @details Configuration object definition of EERAM 3v3 Click driver.
 */
typedef struct
{
    pin_name_t  scl;              /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;              /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  hs;               /**< Description. */

    uint32_t  i2c_speed;          /**< I2C serial speed. */
    uint8_t   i2c_address;        /**< I2C slave address. */

} eeram3v3_cfg_t;

/**
 * @brief EERAM 3v3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   EERAM3V3_OK = 0,
   EERAM3V3_ERROR = -1

} eeram3v3_return_value_t;

/*!
 * @addtogroup eeram3v3 EERAM 3v3 Click Driver
 * @brief API for configuring and manipulating EERAM 3v3 Click driver.
 * @{
 */

/**
 * @brief EERAM 3v3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eeram3v3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 *
 */
void eeram3v3_cfg_setup ( eeram3v3_cfg_t *cfg );

/**
 * @brief EERAM 3v3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #eeram3v3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eeram3v3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 */
err_t eeram3v3_init ( eeram3v3_t *ctx, eeram3v3_cfg_t *cfg );

/**
 * @brief EERAM 3v3 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #eeram3v3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 *
 */
void eeram3v3_generic_write ( eeram3v3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief EERAM 3v3 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #eeram3v3_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 * 
 */
void eeram3v3_generic_read ( eeram3v3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief EERAM 3v3 Click Status Write
 * @details Status register contains settings for write protection and auto-store
 * function. Use this function to configure them.
 * @param ctx          Click object.
 * @param command      Settings to be written to Status register.
 * @return Nothing.
 * @note None.
 * 
 */
void eeram3v3_status_write ( eeram3v3_t *ctx, uint8_t command );

/**
 * @brief EERAM Click Status Read
 * @details Returns the state of the status register.
 * @param ctx          Click object.
 * @returns            Value of the Status register.
 * @note None.
 * 
 */
uint8_t eeram3v3_status_read ( eeram3v3_t *ctx );

/**
 * @brief EERAM Click SRAM Read
 * @details Reads the data from the selected SRAM address onwards.
 * @param ctx          Click object.
 * @param address      SRAM  16 bit address.
 * @param data_out     Data buffer to be filled with read data.
 * @param count_out    Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 * 
 */
void eeram3v3_read ( eeram3v3_t *ctx, uint16_t address, uint8_t *data_out, uint8_t count_out );

/**
 * @brief EERAM Click SRAM Write
 * @details Writes the data to SRAM memory array.
 * @param ctx          Click object.
 * @param address      SRAM  16 bit address.
 * @param data_in      Write data.
 * @param count_in     Number of bytes to write.
 * @return Nothing.
 * @note None.
 * 
 */
 void eeram3v3_write ( eeram3v3_t *ctx, uint16_t address, uint8_t * data_in, uint8_t count_in );

#ifdef __cplusplus
}
#endif
#endif // EERAM3V3_H

/*! @} */ // eeram3v3

// ------------------------------------------------------------------------ END
