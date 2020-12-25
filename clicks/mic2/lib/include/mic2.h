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
 * \brief This file contains API for MIC 2 Click driver.
 *
 * \addtogroup mic2 MIC 2 Click Driver
 * @{
 */


#ifndef MIC2_H
#define MIC2_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_analog_in.h"
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
#define MIC2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN )

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MIC2_RETVAL  uint8_t

#define MIC2_OK           0x00
#define MIC2_INIT_ERROR   0xFF
#define MIC2_DEVICE_SLAVE_ADDRESS  0x2C
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Analog data type 
 */
typedef  uint16_t mic2_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
   // Modules 
    i2c_master_t i2c;
   
   // ctx variable 
   uint8_t slave_address;

   analog_in_t adc;

} mic2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    pin_name_t an_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef     

} mic2_cfg_t;

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
void mic2_cfg_setup ( mic2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MIC2_RETVAL mic2_init ( mic2_t *ctx, mic2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for MIC 2 click.
 */
void mic2_generic_write ( mic2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set potenciometer value.
 *
 * @param ctx  Click object.
 *
 * @description This function set the value of digital potencionetar.
 */
void mic2_set_potentiometer ( mic2_t *ctx, uint8_t ptt_value );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
mic2_data_t mic2_generic_read ( mic2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MIC2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
