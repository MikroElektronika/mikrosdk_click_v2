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
 * \brief This file contains API for Ambient 4 Click driver.
 *
 * \addtogroup ambient4 Ambient 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AMBIENT4_H
#define AMBIENT4_H

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
#define AMBIENT4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ) 
  
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMBIENT4_RETVAL  uint8_t

#define AMBIENT4_OK           0x00
#define AMBIENT4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mode   Mode
 * \{
 */
#define AMBIENT4_CMD_POWER_DOWN             0x00
#define AMBIENT4_CMD_POWER_ON               0x01
#define AMBIENT4_CMD_AUTO_RESOLUTION_MODE   0x10
#define AMBIENT4_CMD_HIGH_RESOLUTION_MODE   0x12
#define AMBIENT4_CMD_LOW_RESOLUTION_MODE    0x13
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

} ambient4_t;

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

} ambient4_cfg_t;

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
void ambient4_cfg_setup ( ambient4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AMBIENT4_RETVAL ambient4_init ( ambient4_t *ctx, ambient4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Ambient4 click.
 */
void ambient4_default_cfg ( ambient4_t *ctx );

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
void ambient4_generic_write ( ambient4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void ambient4_generic_read ( ambient4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Function for send command.
 *
 * 
 * @param ctx          Click object.
 * @param cmd          Command.
 *
 * @description This function for send command.
 */
void ambient4_send_command ( ambient4_t *ctx, uint8_t cmd );

/**
 * @brief Function for read 16bit data.
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function for read 16bit data.
 */
uint16_t ambient4_read_data ( ambient4_t *ctx );

/**
 * @brief Function for device reset.
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function for device reset.
 */
void ambient4_device_reset ( ambient4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AMBIENT4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
