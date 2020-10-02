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
 * \brief This file contains API for Vibra sense Click driver.
 *
 * \addtogroup vibrasense Vibra sense Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef VIBRASENSE_H
#define VIBRASENSE_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define VIBRASENSE_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );      \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/**
 * \defgroup error_code Error Code
 * \{
 */
#define VIBRASENSE_RETVAL  uint8_t

#define VIBRASENSE_OK                0x00
#define VIBRASENSE_INIT_ERROR        0xFF
/** \} */

/**
 * \defgroup en_mode Enable mode
 * \{
 */
#define VIBRASENSE_DISABLE       0
#define VIBRASENSE_ENABLE        1
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

    digital_out_t en;

    // Input pins 

    digital_in_t int_pin;

} vibrasense_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t en;
    pin_name_t int_pin;

} vibrasense_cfg_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 

/** \} */ // End constants group
// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group
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
void vibrasense_cfg_setup ( vibrasense_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param vibrasense Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
VIBRASENSE_RETVAL vibrasense_init ( vibrasense_t *ctx, vibrasense_cfg_t *cfg );

/**
 * @brief Set vibra sense mode function
 *
 * @param vibrasense Click object.
 * @param[in] en_mode
 * <pre> 0 : Disable vibra sense;</pre>
 * <pre> 1 : Enable vibra sense;</pre>
 *
 * Function sets the vibra sense mode.
**/
void vibrasense_set_mode ( vibrasense_t *ctx, uint8_t en_mode );

/**
 * @brief Reset vibra sense function
 *
 * @param vibrasense Click object.
 * 
 * Function resets the device.
 * @note This function has small 200ms delay.
**/
void vibrasense_reset ( vibrasense_t *ctx );

/**
 * @brief Check interrupt function
 *
 * @param vibrasense Click object.
 * 
 * @returns 
 *  <pre> 0 Interrupt has not occured;</pre>
 *  <pre> 1 Interrupt has occured;</pre>
 *
 * Function is used to check for an interrupt that indicates that the device has detected vibrations.
**/
uint8_t vibrasense_check_interrupt ( vibrasense_t *ctx ) ;

#ifdef __cplusplus
}
#endif
#endif  // _VIBRASENSE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
