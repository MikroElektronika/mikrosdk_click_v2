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
 * \brief This file contains API for Signal Realy Click driver.
 *
 * \addtogroup signalrelay Signal Realy Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SIGNALRELAY_H
#define SIGNALRELAY_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define SIGNALRELAY_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.re1= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.re2= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.re3= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.re4= MIKROBUS( mikrobus, MIKROBUS_PWM );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SIGNALRELAY_RETVAL  uint8_t

#define SIGNALRELAY_OK           0x00
#define SIGNALRELAY_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup number_of_relay Number of Relay
 * \{
 */
#define SIGNALRELAY_RELAY_1 1
#define SIGNALRELAY_RELAY_2 2
#define SIGNALRELAY_RELAY_3 3
#define SIGNALRELAY_RELAY_4 4
/** \} */

/**
 * \defgroup  relay_state Relay state
 * \{
 */
#define SIGNALRELAY_STATE_ON 0x01
#define SIGNALRELAY_STATE_OFF 0x00
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
    digital_out_t re3;
    digital_out_t re4;

} signalrelay_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

     pin_name_t re1;
     pin_name_t re2;
     pin_name_t re3;
     pin_name_t re4;

} signalrelay_cfg_t;

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
void signalrelay_cfg_setup ( signalrelay_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param signalrelay Click object.
 * @param cfg Click configuration structure.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SIGNALRELAY_RETVAL signalrelay_init ( signalrelay_t *ctx, signalrelay_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for SignalRelay click.
 * @note All relays are initially set to OFF state.
 */
void signalrelay_default_cfg ( signalrelay_t *ctx );

/**
 * @brief Relays state
 *
 * @param ctx  Click object.
 * @param relay  Number of relay (Relay 1/2/3/4)
 * @param state  Relay state (ON or OFF)
 */
void signalrelay_relay_state( signalrelay_t *ctx, uint8_t relay, uint8_t state );


#ifdef __cplusplus
}
#endif
#endif  // _SIGNALRELAY_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
