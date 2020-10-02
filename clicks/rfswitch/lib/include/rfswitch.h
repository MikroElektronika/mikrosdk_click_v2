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
 * \brief This file contains API for RF Switch Click driver.
 *
 * \addtogroup rfswitch RF Switch Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RFSWITCH_H
#define RFSWITCH_H

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
#define RFSWITCH_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.on= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.sel= MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RFSWITCH_RETVAL  uint8_t

#define RFSWITCH_OK                                               0x00
#define RFSWITCH_INIT_ERROR                                       0xFF
/** \} */

/**
 * \defgroup power_mode Power Mode
 * \{
 */
#define RFSWITCH_PWR_MODE_DISABLE                                 0x00
#define RFSWITCH_PWR_MODE_ENABLE                                  0x01
/** \} */

/**
 * \defgroup select_pin_state Select Pin State
 * \{
 */
#define RFSWITCH_SEL_PIN_STATE_LOW                                0x00
#define RFSWITCH_SEL_PIN_STATE_HIGH                               0x01
/** \} */

/**
 * \defgroup channel_select Channel Select
 * \{
 */
#define RFSWITCH_SELECT_CHANNEL_1                                 1
#define RFSWITCH_SELECT_CHANNEL_2                                 2
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

    digital_out_t on;
    digital_out_t sel;


} rfswitch_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t on;
    pin_name_t sel;

} rfswitch_cfg_t;

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
void rfswitch_cfg_setup ( rfswitch_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RFSWITCH_RETVAL rfswitch_init ( rfswitch_t *ctx, rfswitch_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for RF Switch click.
 */
void rfswitch_default_cfg ( rfswitch_t *ctx );

/**
 * @brief Set Power mode state
 *
 * @param ctx  Click object
 * @param enable
 * <pre>
 * - 0x00 ( RFSWITCH_PWR_MODE_DISABLE ) : Power OFF.
 * - 0x01 ( RFSWITCH_PWR_MODE_ENABLE )  : Power ON.
 * </pre>  
 *
 * @description The function set power mode.
 */
void rfswitch_set_mode ( rfswitch_t *ctx, uint8_t enable );

/**
 * @brief Set SEL pin state
 *
 * @param ctx  Click object 
 * @param sel_state
 * <pre>
 * - 0x00 ( RFSWITCH_SEL_PIN_STATE_LOW )  : Low state.
 * - 0x01 ( RFSWITCH_SEL_PIN_STATE_HIGH ) : High state.
 * </pre>  
 *
 * @description The function set SEL pin state.
 */
void rfswitch_sel_state (  rfswitch_t *ctx, uint8_t sel_state );

/**
 * @brief Select RF channel function
 *
 * @param ctx  Click object 
 * @param select_channel
 * <pre> 
 * - 1 ( RFSWITCH_SELECT_CHANNEL_1 ) : Select RF channel 1.
 * - 2 ( RFSWITCH_SELECT_CHANNEL_2 ) : Select RF channel 2.
 * </pre> 
 *
 * @description The function switching signal to RF channel 1 or 2 of the RF Switch click board.
 */
void rfswitch_select_channel ( rfswitch_t *ctx, uint8_t select_channel );

#ifdef __cplusplus
}
#endif
#endif  // _RFSWITCH_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
