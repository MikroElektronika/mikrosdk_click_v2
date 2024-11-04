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
 * \brief This file contains API for MAC Address  Click driver.
 *
 * \addtogroup macaddress MAC Address  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MACADDRESS_H
#define MACADDRESS_H

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
#define MACADDRESS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MACADDRESS_RETVAL  uint8_t

#define MACADDRESS_OK                                              0x00
#define MACADDRESS_INIT_ERROR                                      0xFF
/** \} */

/**
 * \defgroup i2c_address I2C address
 * \{
 */
#define MACADDRESS_I2C_ADDRESS_0                                   0x50
#define MACADDRESS_I2C_ADDRESS_1                                   0x51
#define MACADDRESS_I2C_ADDRESS_2                                   0x52
#define MACADDRESS_I2C_ADDRESS_3                                   0x53
/** \} */ 

/**
 * \defgroup addr  Addr
 * \{
 */
#define MACADDRESS_END_ADDR                                        0x80
#define MACADDRESS_MAC_ADDR                                        0xF8
/** \} */

/**
 * \defgroup status  Status
 * \{
 */
#define MACADDRESS_OK                                              0x00
#define MACADDRESS_PAR_ERR                                         0x01
#define MACADDRESS_COM_ERR                                         0x02
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 * 
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} macaddress_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    uint32_t i2c_speed;
    uint8_t i2c_address;

} macaddress_cfg_t;

/** \} */ // End types group

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Initialization function.
 * @param macaddress Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
MACADDRESS_RETVAL macaddress_init ( macaddress_t *ctx, macaddress_cfg_t *cfg );

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void macaddress_cfg_setup ( macaddress_cfg_t *cfg );

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
void macaddress_generic_write ( macaddress_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buffer.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */                 
void macaddress_generic_read ( macaddress_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read mac address function
 *
 * @param ctx               Click object.
 * @param read_mac          pointer of memory location where data be stored
 *
 * @description Function performs a data reading from the
 * target MACADDRESS_MAC_ADDR register address of 24AA025E64 2K I2C Serial EEPROMs
 * with EUI-64� node identity on MAC Address Click board.
 */
void macaddress_get_mac ( macaddress_t *ctx, uint8_t *read_mac );

#ifdef __cplusplus
}
#endif
#endif  // _MACADDRESS_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
