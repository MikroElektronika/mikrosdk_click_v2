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
 * \brief This file contains API for Relay 2 Click driver.
 *
 * \addtogroup relay2 Relay 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RELAY2_H
#define RELAY2_H

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
#define RELAY2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an     = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.pwm  = MIKROBUS( mikrobus, MIKROBUS_PWM );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RELAY2_RETVAL  uint8_t

#define RELAY2_OK           0x70
#define RELAY2_INIT_ERROR   0xFF
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
   digital_out_t pwm;
  
} relay2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

   pin_name_t an;
   pin_name_t pwm;

} relay2_cfg_t;

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
void relay2_cfg_setup ( relay2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param relay2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RELAY2_RETVAL relay2_init ( relay2_t *ctx, relay2_cfg_t *cfg );

/**
 * @brief relay2_relay2Control
 *
 * 
 * @param pin_state 1  = On, 0 = off
 * 
 * @description Controls the Relay 2 pin
 */
void relay2_relay2_control (relay2_t *ctx, uint8_t pin_state );

/**
 * @brief relay2_relay2Control
 *
 * @param pin_state 1  = On, 0 = off
 * 
 *
 * @description Controls the Relay 1 pin
 * 
 */
void relay2_relay1_control (relay2_t *ctx, uint8_t pin_state );

#ifdef __cplusplus
}
#endif
#endif  // _RELAY2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
