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
 * \brief This file contains API for Cap Touch Click driver.
 *
 * \addtogroup captouch Cap Touch Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CAPTOUCH_H
#define CAPTOUCH_H

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
#define CAPTOUCH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.mod = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CAPTOUCH_RETVAL  uint8_t

#define CAPTOUCH_OK           0x00
#define CAPTOUCH_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define CAPTOUCH_FAST_MODE 1
#define CAPTOUCH_LOW_POWER_MODE 0
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

    digital_out_t mod;

    // Input pins 

    digital_in_t out;

} captouch_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t mod;
    pin_name_t out;

} captouch_cfg_t;

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
void captouch_cfg_setup ( captouch_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param captouch Click object.
 * @param cfg Click configuration structure.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CAPTOUCH_RETVAL captouch_init ( captouch_t *ctx, captouch_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for CapTouch click.
 */
void captouch_default_cfg ( captouch_t *ctx );

/**
 * @brief Select mode
 *
 * @param ctx  Click object.
 * @param mode  Sensor mode (Low power mode or Fast mode(default)).
 */
void captouch_set_mode( captouch_t *ctx, uint8_t mode );

/**
 * @brief Get touch state
 *
 * @param ctx  Click object.
 * @return Touch state
 */
uint8_t captouch_get_touch( captouch_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _CAPTOUCH_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
