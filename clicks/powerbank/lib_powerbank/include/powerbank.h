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
 * \brief This file contains API for POWER BANK Click driver.
 *
 * \addtogroup powerbank POWER BANK Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef POWERBANK_H
#define POWERBANK_H

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
#define POWERBANK_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define POWERBANK_RETVAL  uint8_t

#define POWERBANK_OK                       0x00
#define POWERBANK_INIT_ERROR               0xFF
/** \} */

/**
 * \defgroup i2c_slave_address I2C slave address
 * \{
 */
#define POWERBANK_SLAVE_ADR                0x4D
/** \} */

/**
 * \defgroup ADC resolution and usefull data
 * \{
 */
#define POWERBANK_RESOLUTION               4096
#define POWERBANK_12_BIT_DATA              0x0FFF
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


    // Input pins 

    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} powerbank_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 


    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} powerbank_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void powerbank_cfg_setup ( powerbank_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param powerbank    Click object.
 * @param cfg          Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
POWERBANK_RETVAL powerbank_init ( powerbank_t *ctx, powerbank_cfg_t *cfg );

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
void powerbank_generic_write ( powerbank_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void powerbank_generic_read ( powerbank_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read data function
 *
 * @param ctx          Click object.
 *
 * @returns result 16-bit value that represents ADC value from output register
 *
 * @description This function is used to read raw data from MCP3221.
**/
uint16_t powerbank_read_data ( powerbank_t *ctx );

/**
 * @brief Read voltage function
 *
 * @param ctx          Click object.
 * @param v_ref        16-bit value representing power supply voltage.
 *
 * @returns result 12-bit value that represents voltage in millivolts.
 *
 * @description This function is used to calculate voltage of the connected battery.
**/
uint16_t powerbank_read_voltage ( powerbank_t *ctx, uint16_t v_ref );

#ifdef __cplusplus
}
#endif
#endif  // _POWERBANK_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
