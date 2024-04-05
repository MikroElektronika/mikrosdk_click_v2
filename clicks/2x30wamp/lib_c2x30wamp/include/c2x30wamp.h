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
 * \brief This file contains API for c2x30W Amp Click driver.
 *
 * \addtogroup c2x30wamp c2x30W Amp Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C2X30WAMP_H
#define C2X30WAMP_H

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
#define C2X30WAMP_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rst= MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.mt= MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.flt= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C2X30WAMP_RETVAL  int8_t

#define C2X30WAMP_OK            0
#define C2X30WAMP_INIT_ERROR  (-1)
/** \} */

/**
 * \defgroup state  State
 * \{
 */
#define C2X30WAMP_ENABLE   1
#define C2X30WAMP_DISABLE  0
#define C2X30WAMP_MUTE     1
#define C2X30WAMP_UNMUTE   0
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

    digital_out_t rst;
    digital_out_t mt;

    // Input pins 

    digital_in_t flt;

} c2x30wamp_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t mt;
    pin_name_t flt;

} c2x30wamp_cfg_t;

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
void c2x30wamp_cfg_setup ( c2x30wamp_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c2x30wamp Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C2X30WAMP_RETVAL c2x30wamp_init ( c2x30wamp_t *ctx, c2x30wamp_cfg_t *cfg );

/**
 * @brief Device Enable function
 *
 * @param ctx       Click object.
 * @param state     0 - Disable, 1 - Enable
 *
 * @description Function allows the device to be enabled or disabled.
 */
void c2x30wamp_enable ( c2x30wamp_t *ctx, uint8_t state );

/**
 * @brief Device Mute function
 *
 * @param ctx     Click object.
 * @param state   0 - Unmute, 1 - Mute
 *
 * @description Function performs the mute or the unmute operation.
 */
void c2x30wamp_mute ( c2x30wamp_t *ctx, uint8_t state );

/**
 * @brief Diagnostic Check function
 *
 * @param ctx  Click object.
 * 
 * @return 0 - Fault condition, 1 - Normal operation
 *
 * @description Function checks is the device in fault condition or in normal operation state.
 */
uint8_t c2x30wamp_check_diagnostic ( c2x30wamp_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // C2X30WAMP_H

/** \} */ // End public_function group
/** \} */ // End click Driver group  

// ------------------------------------------------------------------------- END
