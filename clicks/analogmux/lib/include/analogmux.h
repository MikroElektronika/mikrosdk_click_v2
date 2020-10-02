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
 * \brief This file contains API for Analog MUX Click driver.
 *
 * \addtogroup analogmux Analog MUX Click Driver
 * @{
 */

#ifndef ANALOGMUX_H
#define ANALOGMUX_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_analog_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 

/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define ANALOGMUX_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.s0 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.s3 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.s1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.s2 = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ANALOGMUX_RETVAL  uint8_t

#define ANALOGMUX_OK           0x00
#define ANALOGMUX_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_cfg Default Configuration
 * \{
 */
#define ANALOGMUX_DEF_VREF    3000
#define ANALOGMUX_DEF_REZ     4096
/** \} */

/**
 * \defgroup channels Channels
 * \{
 */
#define ANALOGMUX_CHANNEL_0     0x00
#define ANALOGMUX_CHANNEL_1     0x01
#define ANALOGMUX_CHANNEL_2     0x02
#define ANALOGMUX_CHANNEL_3     0x03
#define ANALOGMUX_CHANNEL_4     0x04
#define ANALOGMUX_CHANNEL_5     0x05
#define ANALOGMUX_CHANNEL_6     0x06
#define ANALOGMUX_CHANNEL_7     0x07
#define ANALOGMUX_CHANNEL_8     0x08
#define ANALOGMUX_CHANNEL_9     0x09
#define ANALOGMUX_CHANNEL_10    0x10
#define ANALOGMUX_CHANNEL_11    0x11
#define ANALOGMUX_CHANNEL_12    0x12
#define ANALOGMUX_CHANNEL_13    0x13
#define ANALOGMUX_CHANNEL_14    0x14
#define ANALOGMUX_CHANNEL_15    0x15
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
typedef  uint16_t analogmux_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t s0;
    digital_out_t s3;
    digital_out_t s1;
    digital_out_t s2;
    
    // Modules 

    analog_in_t adc;

} analogmux_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an_pin;
    
    // Additional gpio pins 

    pin_name_t s0;
    pin_name_t s3;
    pin_name_t s1;
    pin_name_t s2;

    // static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef    

} analogmux_cfg_t;

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
void analogmux_cfg_setup ( analogmux_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ANALOGMUX_RETVAL analogmux_init ( analogmux_t *ctx, analogmux_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
analogmux_data_t analogmux_generic_read ( analogmux_t *ctx );

/**
 * @brief Generic function for read voltage.
 *
 * @param ctx        Click object.
 * @return voltage value
 *
 * @description This function read voltage value.
 */
float analogmux_generic_read_voltage ( analogmux_t *ctx );

/**
 * @brief Set channel function.
 *
 * @param ctx        Click object.
 * @param cfg        Configuration byte.
 *
 * @description This function sets the active channel on the MUX.
 */
void analogmux_set_channel ( analogmux_t *ctx, uint8_t cfg );

#ifdef __cplusplus
}
#endif
#endif  // _ANALOGMUX_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
