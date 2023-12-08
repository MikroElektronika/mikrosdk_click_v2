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
#define ANALOGKEY_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/** \} */ // End group macro
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click touch key definition.
 */
typedef enum
{
    ANALOGKEY_TOUCH_KEY_NONE,
    ANALOGKEY_TOUCH_KEY_1,
    ANALOGKEY_TOUCH_KEY_2,
    ANALOGKEY_TOUCH_KEY_3,
    ANALOGKEY_TOUCH_KEY_4,
    ANALOGKEY_TOUCH_KEY_5,
    ANALOGKEY_TOUCH_KEY_6

} analogkey_key_id_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    analog_in_t  adc;   /**< ADC module. */
    float        vref;  /**< ADC reference voltage. */
    float        vdiv;  /**< Voltage divider between ADC ref voltage and voltage selection on the click board. */

} analogkey_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t  an_pin;                     /**< AN pin descriptor. */

    // Static variable

    analog_in_resolution_t  resolution;     /**< ADC resolution. */
    float  vref;                            /**< ADC reference voltage. */
    float  vsel;                            /**< Click voltage selection. */

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
 * @return 0 - Ok, (-1) - Error.
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t analogkey_init ( analogkey_t *ctx, analogkey_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object.
 * @return ADC data result.
 *
 * @description This function read ADC data.
 */
uint16_t analogkey_generic_read ( analogkey_t *ctx );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object.
 * @return ADC data result.
 *
 * @description This function read ADC data.
 */
float analogkey_read_voltage ( analogkey_t *ctx );

/**
 * @brief Detects which button is pressed.
 *
 * @param ctx Click object.
 * @param adc_value ADC value.
 * @return Which button is pressed.
 *
 * @description This function returns which button is pressed.
 */
analogkey_key_id_t analogkey_get_key ( analogkey_t* ctx, float an_value );

#ifdef __cplusplus
}
#endif
#endif  // ANALOGKEY_H

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
