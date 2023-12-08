/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for CapSense Click driver.
 *
 * \addtogroup capsense CapSense Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CAPSENSE_H
#define CAPSENSE_H

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


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define CAPSENSE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )
 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CAPSENSE_OK                               0
#define CAPSENSE_ERROR                           -1
/** \} */

/**
 * \defgroup register Register
 * \{
 */
#define CAPSENSE_COMMAND_REG                      0xA0
#define CAPSENSE_CS_ENABL0                        0x06
#define CAPSENSE_CS_ENABL1                        0x07
#define CAPSENSE_GPIO_ENABLE0                     0x08
#define CAPSENSE_DM_STRONG0                       0x11
#define CAPSENSE_CS_SLID_CONFIG                   0x75
#define CAPSENSE_CS_SLID_MULM                     0x77
#define CAPSENSE_CS_SLID_MULL                     0x78
#define CAPSENSE_OUTPUT_PORT0                     0x04
#define CAPSENSE_CS_READ_RAW                      0x87
#define CAPSENSE_CS_READ_STATUS0                  0x88
#define CAPSENSE_CS_READ_STATUS1                  0x89
#define CAPSENSE_CS_READ_CEN_POSM                 0x8A
#define CAPSENSE_CS_READ_CEN_POSL                 0x8B
#define CAPSENSE_CS_READ_CEN_PEAKM                0x8C
#define CAPSENSE_CS_READ_CEN_PEAKL                0x8D
#define CAPSENSE_DEVICE_ID                        0x7A
#define CAPSENSE_DEVICE_STATUS                    0x7B
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define CAPSENSE_I2C_ADDRESS_0                    0x00
#define CAPSENSE_I2C_ADDRESS_1                    0x4B
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 
    digital_out_t an;
    
    // Input pins
    digital_in_t rst;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;

} capsense_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t an;
    pin_name_t rst;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} capsense_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void capsense_cfg_setup ( capsense_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param capsense Click object.
 * @param cfg Click configuration structure.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t capsense_init ( capsense_t *ctx, capsense_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @description This function executes default configuration for CapSense click.
 * @note
 * <pre>
 * The following configuration is set in main:
 * 
 * -Enable pins on B0,B1 and slider as CapSense
 * -Five pins will be used for Slider pads
 * -Two pins will be used for Button pads
 * -Three pins will be used as GPIO 2 for LED and 1 as GPIO2
 * -Enable strong drive mode for GPIOs
 * -Enable slider
 * -Configure slider resolution
 * -Configure slider resolution
 * -Store Current Configuration to NVM
 * -Reconfigure Device (POR)
 * </pre>
 */
err_t capsense_default_cfg ( capsense_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @description This function writes data to the desired register.
 */
err_t capsense_generic_write ( capsense_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @description This function reads data from the desired register.
 */
err_t capsense_generic_read ( capsense_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write data function
 *
 * @param ctx                 Click object.
 * @param reg_address         Register address.
 * @param write_command       Command to write.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @description This function writes one byte to reg_address.
 */
err_t capsense_write_data( capsense_t *ctx, uint8_t reg_address, uint8_t write_command );

/**
 * @brief Read one byte from register address
 *
 * @param ctx                 Click object.
 * @param reg_address         Register address.
 * @param read_data           8-bit data from addressed register
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @description This function reads one byte from reg_address.
 */
err_t capsense_read_data( capsense_t *ctx, uint8_t reg_address, uint8_t *read_data );

/**
 * @brief Read two bytes from register address
 *
 * @param ctx                 Click object.
 * @param reg_address         Register address
 * @param read_data           16-bit data from addressed register
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @description This function reads two bytes from address reg_address.
 */
err_t capsense_read_data_bytes( capsense_t *ctx, uint8_t reg_address, uint16_t *read_data );

/**
 * @brief Function get slider level
 *
 * @param ctx           Click object.
 *
 * @param slider_lvl    Slider pressed position
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @description This function gets slider level of click object ctx.
 */
err_t capsense_get_slider_lvl( capsense_t *ctx, uint8_t *slider_lvl );

#ifdef __cplusplus
}
#endif
#endif  // _CAPSENSE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
