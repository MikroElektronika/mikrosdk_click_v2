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
 * \brief This file contains API for I2C MUX 2 Click driver.
 *
 * \addtogroup i2cmux2 I2C MUX 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef I2CMUX2_H
#define I2CMUX2_H

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
#define I2CMUX2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define I2CMUX2_OK                              0
#define I2CMUX2_ERROR                          -1
/** \} */

// Device address
#define I2CMUX2_I2C_SLAVE_ADDRESS_0             0x70
#define I2CMUX2_I2C_SLAVE_ADDRESS_1             0x71
#define I2CMUX2_I2C_SLAVE_ADDRESS_2             0x72
#define I2CMUX2_I2C_SLAVE_ADDRESS_3             0x73
#define I2CMUX2_I2C_SLAVE_ADDRESS_4             0x74
#define I2CMUX2_I2C_SLAVE_ADDRESS_5             0x75
#define I2CMUX2_I2C_SLAVE_ADDRESS_6             0x76
#define I2CMUX2_I2C_SLAVE_ADDRESS_7             0x77

// Set channel
#define I2CMUX2_CMD_NO_CH                       0x00
#define I2CMUX2_CMD_SET_CH_0                    0x01
#define I2CMUX2_CMD_SET_CH_1                    0x02
#define I2CMUX2_CMD_SET_CH_2                    0x04
#define I2CMUX2_CMD_SET_CH_3                    0x08

// Interrupt bit mask
#define I2CMUX2_INT_BITS                        0xF0

// Interrupt of channel
#define I2CMUX2_INT_NO_CH                       0x00
#define I2CMUX2_INT_CH_0                        0x01
#define I2CMUX2_INT_CH_1                        0x02
#define I2CMUX2_INT_CH_2                        0x04
#define I2CMUX2_INT_CH_3                        0x08

// Interrupt pin state
#define I2CMUX2_INT_PIN_STATE_ACTIVE            0x00
#define I2CMUX2_INT_PIN_STATE_NOT_ACTIVE        0x01

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
    digital_out_t rst;

    // Input pins 
    digital_in_t int_pin;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;

} i2cmux2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} i2cmux2_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void i2cmux2_cfg_setup ( i2cmux2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t i2cmux2_init ( i2cmux2_t *ctx, i2cmux2_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @details This function writes data to the desired register.
 */
void i2cmux2_generic_write ( i2cmux2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @details This function reads data from the desired register.
 */
void i2cmux2_generic_read ( i2cmux2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Hardware reset function.
 *
 * @param ctx    Click object.
 * 
 * @details This function resets I2C MUX 2 click board
 * by clearing the RST pin for 100ms.
 */
void i2cmux2_hw_reset ( i2cmux2_t *ctx );

/**
 * @brief Write command function.
 *
 * @param ctx    Click object.
 * @param tx_data      8-bit data to be transmitted.
 *
 * @details Function executes writes command to the TCA9545A
 * Low Voltage 4-Channel I2C on the I2C MUX 2 click board.
 */
void i2cmux2_write_cmd ( i2cmux2_t *ctx, uint8_t tx_data );

/**
 * @brief Read command function.
 *
 * @param ctx    Click object.
 * 
 * @return
 * 8-bit read data.
 *
 * @details Function executes read command from the TCA9545A
 * Low Voltage 4-Channel I2C on the I2C MUX 2 click board.
 */
uint8_t i2cmux2_read_cmd ( i2cmux2_t *ctx );

/**
 * @brief Set channel function
 * 
 * @param ctx    Click object.
 * @param channel            8-bit register address.
 *
 * @param ch_slave_address   pointer to the data to be written.
 *
 * @details Function sets channel of the I2C MUX 2 click board.
 */
void i2cmux2_set_channel ( i2cmux2_t *ctx, uint8_t channel, uint8_t ch_slave_address );

/**
 * @brief Read interrupt status function
 *
 * @param ctx    Click object.
 * 
 * @return
 * Interrupt of channel state:
 * - [ bit 0 ] : Interrupt on channel 0;
 * - [ bit 1 ] : Interrupt on channel 1;
 * - [ bit 2 ] : Interrupt on channel 2;
 * - [ bit 3 ] : Interrupt on channel 3;
 *
 * @details Function get interrupt status by reading from the TCA9545A
 * Low Voltage 4-Channel I2C on the I2C MUX 2 click board.
*/
uint8_t i2cmux2_read_interrupt ( i2cmux2_t *ctx );

/**
 * @brief Check interrupt status function
 *
 * @param ctx    Click object.
 * 
 * @return
 * Interrupt pin state:
 * - 0 : Active;
 * - 1 : Not active;
 *
 * @details Function check interrupt state by returning the state
 * of the INT pin of I2C MUX 2 click board.
*/
uint8_t i2cmux2_check_int ( i2cmux2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _I2CMUX2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
