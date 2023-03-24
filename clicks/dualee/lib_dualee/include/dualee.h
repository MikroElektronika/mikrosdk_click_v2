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
 * \brief This file contains API for Dual EE Click driver.
 *
 * \addtogroup dualee Dual EE Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DUALEE_H
#define DUALEE_H

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
#define DUALEE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DUALEE_RETVAL  uint8_t

#define DUALEE_OK           0x00
#define DUALEE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address  Slave address
 * \{
 */
#define DUALEE_SLAVEADDRESS_1  0x50
#define DUALEE_SLAVEADDRESS_2  0x54
/** \} */

/**
 * \defgroup starting_and_ending_adresses  Starting and Ending adresses
 * \{
 */
#define DUALEE_ADDRESS_START  0x00000000
#define DUALEE_ADDRESS_END    0x0007FFFE
/** \} */

/**
 * \defgroup start_and_end  Start and end
 * \{
 */
#define DUALEE_PAGE_START_OF_FIRST   0x00000000
#define DUALEE_PAGE_END_OF_FIRST     0x0003FFFF
#define DUALEE_PAGE_START_OF_SECOND  0x00040000
#define DUALEE_PAGE_END_OF_SECOND    0x0007FFFE
/** \} */

/**
 * \defgroup maximum_data_per_page  Maximum data per page
 * \{
 */
#define DUALEE_MAXIMUM_DATA    251
/** \} */

/**
 * \defgroup error_variables Error variables
 * \{
 */
#define DUALEE_ERROR_RW       0
#define DUALEE_SUCCESSFUL_RW  1
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
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    uint8_t slave_address_1;
    uint8_t slave_address_2;

} dualee_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    uint8_t i2c_address_1;
    uint8_t i2c_address_2;

} dualee_cfg_t;

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
void dualee_cfg_setup ( dualee_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DUALEE_RETVAL dualee_init ( dualee_t *ctx, dualee_cfg_t *cfg );

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
void dualee_generic_write ( dualee_t *ctx, uint8_t *reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void dualee_generic_read ( dualee_t *ctx, uint8_t *reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write data function
 *
 * @param ctx          Click object.
 * @param reg_address  Address from where data will be written
 * @param data_buff    INPUT buffer data
 * @param n_bytes      Number of bytes data
 *
 * @description either _DUALEE_SUCCESSFUL_RW or _DUALEE_ERROR_RW.
 */
uint8_t dualee_write ( dualee_t *ctx, uint32_t reg_address, uint8_t *data_buff, uint8_t n_bytes);

/**
 * @brief Generic write data function
 *
 * @param ctx          Click object.
 * @param reg_address  Address from where data will be read
 * @param data_buff    OUTPUT buffer data
 * @param n_bytes      Number of bytes data
 *
 * @description either _DUALEE_SUCCESSFUL_RW or _DUALEE_ERROR_RW.
 */
uint8_t dualee_read ( dualee_t *ctx, uint32_t reg_address, uint8_t *data_buff, uint8_t n_bytes );


#ifdef __cplusplus
}
#endif
#endif  // _DUALEE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
