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
 * \brief This file contains API for UVC Click driver.
 *
 * \addtogroup uvc UVC Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UVC_H
#define UVC_H

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
#define UVC_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UVC_RETVAL  uint8_t

#define UVC_OK                  0x00
#define UVC_INIT_ERROR          0xFF
/** \} */

/**
 * \defgroup slave_addr Slave address
 * \{
 */
#define UVC_DEVICE_SLAVE_ADDR   0x4D
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

    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} uvc_t;

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

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} uvc_cfg_t;

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
void uvc_cfg_setup ( uvc_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
UVC_RETVAL uvc_init ( uvc_t *ctx, uvc_cfg_t *cfg );

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
void uvc_generic_write ( uvc_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void uvc_generic_read ( uvc_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read 12bit raw data
 *
 * @param ctx  Click object.
 *
 * @returns 12bit data
 *
 * @description This function reads 12bit raw data.
 */
uint16_t uvc_read_raw_data ( uvc_t *ctx );

/**
 * @brief Calculate voltage
 *
 * @param ctx   Click object. 
 *
 * @returns     Voltage on AN pin
 *
 * @description This function calculate voltage from raw data.
 */
float uvc_get_voltage ( uvc_t *ctx );

/**
 * @brief Calculate power
 *
 * @param ctx       Click object.
 * @param voltage   Voltage on AN pin  
 *
 * @returns power [ 0 - 14.1mW/cm2 ]
 *
 * @description This function calculate power from voltage.
 */
float uvc_calculate_power ( float voltage );

#ifdef __cplusplus
}
#endif
#endif  // _UVC_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
