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
 * \brief This file contains API for AMR Current Click driver.
 *
 * \addtogroup amrcurent AMR Current Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AMRCURENT_H
#define AMRCURENT_H

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
#define AMRCURENT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
  
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMRCURENT_RETVAL  uint8_t

#define AMRCURENT_OK           0x00
#define AMRCURENT_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup pin_state Pin State
 * \{
 */
#define AMRCURRENT_PIN_STATE_HIGH  1
#define AMRCURRENT_PIN_STATE_LOW   0
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

    digital_out_t voc;
   
    // Input pins 

    digital_in_t an;
    digital_in_t flt;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} amrcurent_t;

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
    pin_name_t voc;
    pin_name_t flt;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} amrcurent_cfg_t;

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
void amrcurent_cfg_setup ( amrcurent_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AMRCURENT_RETVAL amrcurent_init ( amrcurent_t *ctx, amrcurent_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for AMRCurent click.
 */
void amrcurent_default_cfg ( amrcurent_t *ctx );

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
void amrcurent_generic_write ( amrcurent_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void amrcurent_generic_read ( amrcurent_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Reads ADC current data.
 * 
 * @param ctx          Click object.
 *
 * @description This function read value.
 */
uint16_t amrcurrent_read_value (  amrcurent_t *ctx );

/**
 * @brief Gets state of the FLTB pin on int.
 * 
 * @param ctx          Click object.
 *
 * @description This function state of the pin.
 */
uint8_t amrcurrent_get_int_pin_state ( amrcurent_t *ctx );

/**
 * @brief Sets state of the reset pin.
 * 
 * @param ctx          Click object.
 * @param pin_state    value of pin to be set.
 *
 * @description This function sets rst pin state.
 */
void amrcurrent_set_rst_pin_state ( amrcurent_t *ctx, uint8_t pin_state );

/**
 * @brief Hardware reset device.
 * 
 * @param ctx          Click object.
 *
 * @description This function reset hardware device.
 */
void amrcurrent_hw_reset ( amrcurent_t *ctx );

/**
 * @brief Reads current data in mA.
 * 
 * @param ctx          Click object.
 *
 * @description This function gets current.
 */
float amrcurrent_get_current ( amrcurent_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AMRCURENT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
