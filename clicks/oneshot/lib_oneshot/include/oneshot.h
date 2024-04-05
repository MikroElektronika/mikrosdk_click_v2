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
 * \brief This file contains API for One Shot Click driver.
 *
 * \addtogroup oneshot One Shot Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ONESHOT_H
#define ONESHOT_H

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
#define ONESHOT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.out  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.trg  = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ONESHOT_RETVAL  uint8_t

#define ONESHOT_OK           0x00
#define ONESHOT_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define ONESHOT_SLAVE_ADDRESS   0x2C
/** \} */

/**
 * \defgroup scale Scale
 * \{
 */
#define ONESHOT_FULL_SCALE   0xFF
#define ONESHOT_MIDSCALE     0x80
#define ONESHOT_1_LSB        0x01
#define ONESHOT_ZERO_SCALE   0x00
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

    digital_out_t trg;

    // Input pins 

    digital_in_t out;

    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} oneshot_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t out;
    pin_name_t trg;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} oneshot_cfg_t;

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
void oneshot_cfg_setup ( oneshot_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ONESHOT_RETVAL oneshot_init ( oneshot_t *ctx, oneshot_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for OneShot click.
 */
void oneshot_default_cfg ( oneshot_t *ctx );

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
void oneshot_generic_write ( oneshot_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void oneshot_generic_read ( oneshot_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get resistance function.
 *
 * @param ctx  Click object.
 *
 * @description This function reads the resistance data from the AD5241 chip.
 */
float oneshot_get_resistance ( oneshot_t *ctx );

/**
 * @brief Digital read reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function reads the digital signal from the RST pin.
 */
uint8_t oneshot_digital_read_rst ( oneshot_t *ctx );

/**
 * @brief Digital write chip select function.
 *
 * @param ctx      Click object.
 * @param signal   Digital output signal.
 *
 * @description This function writes the specified digital signal to the CS pin.
 */
void oneshot_digital_write_cs ( oneshot_t *ctx, uint8_t signal );

#ifdef __cplusplus
}
#endif
#endif  // _ONESHOT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
