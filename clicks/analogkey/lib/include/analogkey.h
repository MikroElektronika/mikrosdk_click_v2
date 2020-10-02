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
 * \brief This file contains API for Analog Key Click driver.
 *
 * \addtogroup analogkey Analog Key Click Driver
 * @{
 */


#ifndef ANALOGKEY_H
#define ANALOGKEY_H

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
#define ANALOGKEY_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ANALOGKEY_RETVAL  uint8_t

#define ANALOGKEY_OK           0x00
#define ANALOGKEY_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup buttons Buttons
 * \{
 */
#define ANALOGKEY_TOUCH_KEY_1            0x01
#define ANALOGKEY_TOUCH_KEY_2            0x02
#define ANALOGKEY_TOUCH_KEY_3            0x03
#define ANALOGKEY_TOUCH_KEY_4            0x04
#define ANALOGKEY_TOUCH_KEY_5            0x05
#define ANALOGKEY_TOUCH_KEY_6            0x06
#define ANALOGKEY_NO_TOUCH                0x00
/** \} */

/**
* \defgroup resolution Resolution
* \{
*/
#define ANALOGKEY_ADC_RESOLUTION_10bit   0x01
#define ANALOGKEY_ADC_RESOLUTION_12bit   0x02
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
typedef  uint16_t analogkey_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Modules 

    analog_in_t adc;
    float key_flag;
    uint16_t max_adc;
    uint8_t prec;

} analogkey_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an_pin;

    // static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef  

    float dev_key_flag;
    uint16_t dev_max_adc;
    uint8_t dev_prec;

} analogkey_cfg_t;

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
void analogkey_cfg_setup ( analogkey_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ANALOGKEY_RETVAL analogkey_init ( analogkey_t *ctx, analogkey_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
analogkey_data_t analogkey_generic_read ( analogkey_t *ctx );

/**
 * @brief Detects which button is pressed
 *
 * @param ctx        Click object.
 * @param adc_value     ADC value
 * @return which button is pressed
 *
 * @description This function returns which button is pressed.
 */
uint8_t analogkey_get_key ( analogkey_t* ctx, uint16_t adc_value );

/**
 * @brief set ADC resolution
 *
 * @param ctx        Click object.
 * @param resolution     ADC resolution (10bit or 12 bit)
 *
 * @description This function sets the resolution.
 */
void analogkey_set_resolution ( analogkey_t* ctx, uint8_t resolution );

#ifdef __cplusplus
}
#endif
#endif  // _ANALOGKEY_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
