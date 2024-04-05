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
 * \brief This file contains API for MOTION Click driver.
 *
 * \addtogroup motion MOTION Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MOTION_H
#define MOTION_H

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
#define MOTION_MAP_MIKROBUS( cfg, mikrobus )    \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );  \
  cfg.out = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MOTION_RETVAL  uint8_t

#define MOTION_OK           0x00
#define MOTION_INIT_ERROR   0xFF
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
    
    digital_in_t out;

} motion_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 
    
    pin_name_t en;
    pin_name_t out;

} motion_cfg_t;

/**
 * @brief Pin states.
 */
typedef enum
{
    MOTION_PIN_STATE_LOW = 0,
    MOTION_PIN_STATE_HIGH

} motion_pin_state_t;

/**
 * @brief Motion OUT ( INT ) Pin states.
 */
typedef enum
{
    MOTION_NO_DETECT = 0,
    MOTION_DETECTED

} motion_detect_state_t;

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
void motion_cfg_setup ( motion_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param motion Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MOTION_RETVAL motion_init ( motion_t *ctx, motion_cfg_t *cfg );


/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Motion click.
 * @note Places the sensor in detection mode.
 */
void motion_default_cfg ( motion_t *ctx );

/**
 * @brief Set states of the enable pin
 *
 * @param ctx       Click object.
 * @param en_state  
 * <pre>
 * - MOTION_PIN_STATE_LOW  : disables the sensor.
 * - MOTION_PIN_STATE_HIGH : enable, places the sensor in detection mode.
 * </pre>
 *
 * @description This function sets states of the EN ( RST ) pin
 * for Motion click.
 * @note Places the sensor in detection mode.
 */
void motion_set_en_pin (  motion_t *ctx, motion_pin_state_t en_state );

/**
 * @brief Motion detected function
 * 
 * @param ctx       Click object.
 * @param out_pin_state
 * <pre>
 * - MOTION_NO_DETECT : motion is not detected.
 * - MOTION_DETECTED  : motion is detected.
 * </pre> 
 * 
 * @description Function detect motion and return 
 * MOTION_DETECTED ( 1 ) if a motion is detected or
 * MOTION_NO_DETECT ( 0 ) if a motion is not detected. 
 */
motion_detect_state_t motion_get_detected ( motion_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MOTION_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
