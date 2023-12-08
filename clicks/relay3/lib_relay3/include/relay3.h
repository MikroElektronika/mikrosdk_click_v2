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
 * \brief This file contains API for Relay 3 Click driver.
 *
 * \addtogroup relay3 Relay 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RELAY3_H
#define RELAY3_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define RELAY3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.re1= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.re2= MIKROBUS( mikrobus, MIKROBUS_CS ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RELAY3_RETVAL  uint8_t

#define RELAY3_OK           0x00
#define RELAY3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup relays Relays
 * \{
 */
#define RELAY3_RELAY_1       0x01
#define RELAY3_RELAY_2       0x02
#define RELAY3_BOTH_RELAYS   0x03
/** \} */

/**
 * \defgroup units Units
 * \{
 */
#define RELAY3_SECONDS       0x00
#define RELAY3_MILISECONDS   0x01
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

    digital_out_t re1;
    digital_out_t re2;

} relay3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t re1;
    pin_name_t re2;

} relay3_cfg_t;

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
void relay3_cfg_setup ( relay3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param relay3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RELAY3_RETVAL relay3_init ( relay3_t *ctx, relay3_cfg_t *cfg );

/**
 * @brief Relay on function.
 * 
 * @param cfg   Click configuration structure.
 * @param relay Relay choice (1/2).
 * 
 * @description This function turns on either the 1st or the 2nd relay on the click.
 */
void relay3_relay_on ( relay3_t *ctx, uint8_t relay );

/**
 * @brief Relay off function.
 * 
 * @param cfg   Click configuration structure.
 * @param relay Relay choice (1/2).
 * 
 * @description This function turns off either the 1st or the 2nd relay on the click.
 */
void relay3_relay_off ( relay3_t *ctx, uint8_t relay );

/**
 * @brief Relay on with delay function.
 * 
 * @param cfg   Click configuration structure.
 * @param relay Relay choice (1/2).
 * @param units Unit variable (ms/s).
 * @param time  Delay duration variable.
 * 
 * @description This function turns on one of the relays after the delay time passes.
 */
void relay3_on_delay ( relay3_t *ctx, uint8_t relay, uint8_t units, uint16_t time );

/**
 * @brief Relay off with delay function.
 * 
 * @param cfg   Click configuration structure.
 * @param relay Relay choice (1/2).
 * @param units Unit variable (ms/s).
 * @param time  Delay duration variable.
 * 
 * @description This function turns off one of the relays after the delay time passes.
 */
void relay3_on_delay ( relay3_t *ctx, uint8_t relay, uint8_t units, uint16_t time );

#ifdef __cplusplus
}
#endif
#endif  // _RELAY3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
