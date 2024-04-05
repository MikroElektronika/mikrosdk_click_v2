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
 * \brief This file contains API for I2C MUX Click driver.
 *
 * \addtogroup i2cmux I2C MUX Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef I2CMUX_H
#define I2CMUX_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define I2CMUX_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define I2CMUX_RETVAL  uint8_t

#define I2CMUX_OK           0x00
#define I2CMUX_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_address Device address
 * \{
 */
#define I2CMUX_I2C_SLAVE_ADDRESS_0                                    0x70
#define I2CMUX_I2C_SLAVE_ADDRESS_1                                    0x71
#define I2CMUX_I2C_SLAVE_ADDRESS_2                                    0x72
#define I2CMUX_I2C_SLAVE_ADDRESS_3                                    0x73
#define I2CMUX_I2C_SLAVE_ADDRESS_4                                    0x74
#define I2CMUX_I2C_SLAVE_ADDRESS_5                                    0x75
#define I2CMUX_I2C_SLAVE_ADDRESS_6                                    0x76
#define I2CMUX_I2C_SLAVE_ADDRESS_7                                    0x77
/** \} */

/**
 * \defgroup set_channel Set channel
 * \{
 */
#define I2CMUX_CMD_NO_CH                                              0x00
#define I2CMUX_CMD_SET_CH_0                                           0x01
#define I2CMUX_CMD_SET_CH_1                                           0x02
#define I2CMUX_CMD_SET_CH_2                                           0x04
#define I2CMUX_CMD_SET_CH_3                                           0x08
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

    digital_out_t rst;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} i2cmux_t;

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

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} i2cmux_cfg_t;

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
void i2cmux_cfg_setup ( i2cmux_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
I2CMUX_RETVAL i2cmux_init ( i2cmux_t *ctx, i2cmux_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void i2cmux_generic_write ( i2cmux_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void i2cmux_generic_read ( i2cmux_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Hardware reset function.
 *
 * @param ctx          Click object.
 *
 * @description This function resets I2C MUX 2 click board
 * by clearing the RST pin for 100ms.
 */
void i2cmux_hw_reset ( i2cmux_t *ctx );

/**
 * @brief Write command function.
 *
 * @param ctx          Click object.
 * @param tx_data      8-bit data to be transmitted.
 *
 * @description This function executes writes command to the TCA9546A
 * Low Voltage 4-Channel I2C and SMBus Switch
 * on the I2C MUX click board.
 */
void i2cmux_write_cmd ( i2cmux_t *ctx, uint8_t tx_data );

/**
 * @brief Read command function.
 *
 * @param ctx          Click object.
 *
 * @description This function executes read command from the TCA9546A
 * Low Voltage 4-Channel I2C and SMBus Switch
 * on the I2C MUX click board.
 */
uint8_t i2cmux_read_cmd ( i2cmux_t *ctx );

/**
 * @brief Set channel function.
 *
 * @param ctx               Click object.
 * @param channel           8-bit register address.
 * @param ch_slave_address  Pointer to the data to be written.
 *
 * @description This function sets channel of the I2C MUX click board.
 */
void i2cmux_set_channel ( i2cmux_t *ctx, uint8_t channel, uint8_t ch_slave_address );

#ifdef __cplusplus
}
#endif
#endif  // _I2CMUX_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
