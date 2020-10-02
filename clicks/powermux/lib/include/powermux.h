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
 * \brief This file contains API for Power MUX Click driver.
 *
 * \addtogroup powermux Power MUX Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef POWERMUX_H
#define POWERMUX_H

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
#define POWERMUX_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.d0      = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.d1      = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define POWERMUX_RETVAL  uint8_t

#define POWERMUX_OK               0x00
#define POWERMUX_INIT_ERROR       0xFF
/** \} */

/**
 * \defgroup pin_state_values Pin state values
 * \{
 */
#define POWERMUX_PIN_STATE_0      0x00
#define POWERMUX_PIN_STATE_1      0x01
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

    digital_out_t d0;
    digital_out_t d1;

    // Input pins 

    digital_in_t int_pin;

} powermux_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t d0;
    pin_name_t d1;
    pin_name_t int_pin;

} powermux_cfg_t;

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
void powermux_cfg_setup ( powermux_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
POWERMUX_RETVAL powermux_init ( powermux_t *ctx, powermux_cfg_t *cfg );

/**
 * @brief Set D0 state function
 *
 * @param ctx  Click object. 
 * @param state  defines desired state of D0 pin
 *
 * @description Function is used to set the state of D0 pin.
**/
void powermux_set_d0 ( powermux_t *ctx, uint8_t state );

/**
 * @brief Set D1 state function
 *
 * @param ctx  Click object. 
 * @param state  defines desired state of D1 pin
 *
 * @description Function is used to set the state of D1 pin.
**/
void powermux_set_d1 ( powermux_t *ctx, uint8_t state );

/**
 * @brief Check INT pin state function
 *
 * @param ctx  Click object. 
 * @returns
 * <pre>
 * - Hi-Z : if the IN2 switch is ON
 * - 0    : if the IN1 switch is ON or if OUT is Hi-Z
 * </pre> 
 *
 * @description Function is used to check state of INT pin.
**/
uint8_t powermux_int_pin_state ( powermux_t *ctx );

/**
 * @brief Output From Input Channel 2 function
 *
 * @param ctx  Click object. 
 *
 * @description Function is used to set output from input channel 2.
**/
void powermux_output_input_ch_2 ( powermux_t *ctx );

/**
 * @brief Output From Input Channel 1 function
 *
 * @param ctx  Click object. 
 *
 * @description Function is used to set output from input channel 1.
**/
void powermux_output_input_ch_1 ( powermux_t *ctx );

/**
 * @brief Automatic Output Channel Selection function
 *
 * @param ctx  Click object. 
 *
 * @description Function is used to set automatic output channel selection.
**/
void powermux_auto_sel_input_ch ( powermux_t *ctx );

/**
 * @brief No Output function
 *
 * @param ctx  Click object. 
 *
 * @description Function is used to disable output.
**/
void powermux_no_output ( powermux_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _POWERMUX_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
