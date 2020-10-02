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
 * \brief This file contains API for EERAM Click driver.
 *
 * \addtogroup eeram EERAM Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EERAM_H
#define EERAM_H

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
#define EERAM_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.hs = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EERAM_RETVAL  uint8_t

#define EERAM_OK           0x00
#define EERAM_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup eeram_const EERAM Const
 * \{
 */
#define EERAM_ADDRESS_SRAM       0x50
#define EERAM_ADDRESS_CONTROL    0x18
#define EERAM_CMD_STORE          0x33
#define EERAM_CMD_RECALL         0xDD
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

    digital_out_t hs;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address_control;
    uint8_t slave_address_sram;

} eeram_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t hs;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_control_address;
    uint8_t i2c_sram_address;

} eeram_cfg_t;

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
void eeram_cfg_setup ( eeram_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
EERAM_RETVAL eeram_init ( eeram_t *ctx, eeram_cfg_t *cfg );

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
void eeram_generic_write ( eeram_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void eeram_generic_read ( eeram_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief EERAM Click Command Write
 *
 * @param ctx          Click object.
 * @param command      Either _EERAM_CMD_STORE or _EERAM_CMD_RECALL.
 *
 * @description Depending on the parameter, will either store the data from SRAM to EERAM,
 * or recall that data back to SRAM.
 */
void eeram_command ( eeram_t *ctx, uint8_t command );

/**
 * @brief EERAM Click Status Write
 *
 * @param ctx          Click object.
 * @param command      Settings to be written to Status register.
 *
 * @description Status register contains settings for write protection and auto-store
 * function. Use this function to configure them.
 */
void eeram_status_write ( eeram_t *ctx, uint8_t command );

/**
 * @brief EERAM Click Status Read
 *
 * @param ctx          Click object.
 * @returns            Value of the Status register.
 *
 * @description Returns the state of the status register.
 */
uint8_t eeram_status_read ( eeram_t *ctx );

/**
 * @brief EERAM Click SRAM Read
 *
 * @param ctx          Click object.
 * @param address      SRAM  16 bit address.
 * @param data_out     Data buffer to be filled with read data.
 * @param count_out    Number of bytes to read.
 *
 * @description Reads the data from the selected SRAM address onwards.
 */
void eeram_read ( eeram_t *ctx, uint16_t address, uint8_t *data_out, uint8_t count_out );

/**
 * @brief EERAM Click SRAM Write
 *
 * @param ctx          Click object.
 * @param address      SRAM  16 bit address.
 * @param data_in      Write data.
 * @param count_in     Number of bytes to write.
 *
 * @description Writes the data to SRAM memory array.
 */
 void eeram_write ( eeram_t *ctx, uint16_t address, uint8_t * data_in, uint8_t count_in );

#ifdef __cplusplus
}
#endif
#endif  // _EERAM_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
