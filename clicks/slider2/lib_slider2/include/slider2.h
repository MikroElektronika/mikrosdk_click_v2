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
 * \brief This file contains API for Slider 2 Click driver.
 *
 * \addtogroup slider2 Slider 2 Click Driver
 * @{
 */


#ifndef SLIDER2_H
#define SLIDER2_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define SLIDER2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.rsl = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SLIDER2_RETVAL  uint8_t

#define SLIDER2_OK           0x00
#define SLIDER2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_status Device Status
 * \{
 */
#define SLIDER2_DEVICE_ENABLE            1
#define SLIDER2_DEVICE_DISABLE           0 
/** \} */

/**
 * \defgroup reference_status Reference status
 * \{
 */
#define SLIDER2_MAX_VOLTAGE_2_048V       1
#define SLIDER2_MAX_VOLTAGE_4_096V       0
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
typedef  uint16_t slider2_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t en;
    digital_out_t rsl;
    
    // Modules 

    analog_in_t adc;

} slider2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an_pin;
    
    // Additional gpio pins 

    pin_name_t en;
    pin_name_t rsl;

    // static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef     

} slider2_cfg_t;

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
void slider2_cfg_setup ( slider2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SLIDER2_RETVAL slider2_init ( slider2_t *ctx, slider2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Slider 2 click.
 */
void slider2_default_cfg ( slider2_t *ctx );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
slider2_data_t slider2_generic_read ( slider2_t *ctx );

/**
 * @brief Setting state function.
 *
 * @param ctx  Click object.
 * @param state State.
 *
 * @description This function sets desired state to EN pin.
 */
void slider2_enable ( slider2_t *ctx, uint8_t state );

/**
 * @brief Setting reference function.
 *
 * @param ctx  Click object.
 * @param ref Reference.
 *
 * @description This function sets desired reference to RSL pin.
 */
void slider2_set_reference ( slider2_t *ctx, uint8_t ref );


#ifdef __cplusplus
}
#endif
#endif  // _SLIDER2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
