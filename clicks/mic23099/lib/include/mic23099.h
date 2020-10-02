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
 * \brief This file contains API for MIC23099 Click driver.
 *
 * \addtogroup mic23099 MIC23099 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MIC23099_H
#define MIC23099_H

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
#define MIC23099_MAP_MIKROBUS( cfg, mikrobus )     \
  cfg.en      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MIC23099_RETVAL  uint8_t

#define MIC23099_OK           0x00
#define MIC23099_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup en_mode Enable mode
 * \{
 */
#define MIC23099_DISABLE        0x00
#define MIC23099_ENABLE         0x01
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

} mic23099_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t en;
    pin_name_t int_pin;

} mic23099_cfg_t;

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
 * @param cfg           Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void mic23099_cfg_setup ( mic23099_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param mic23099      Click object
 * .
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MIC23099_RETVAL mic23099_init ( mic23099_t *ctx, mic23099_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx           Click object.
 *
 * @description This function executes default configuration for MIC23099 click.
 */
void mic23099_default_cfg ( mic23099_t *ctx );

/**
 * @brief Enable MIC23099 function.
 *
 * @param ctx           Click object.
 * @param en_mode
 * <pre> 0 : Disable; </pre>
 * <pre> 1 : Enable;  </pre>  
 *
 * @description This function enables the device by seting EN pin.
 */
void mic23099_set_enable ( mic23099_t *ctx, uint8_t en_mode );

/**
 * @brief Reset MIC23099 function.
 *
 * @param ctx           Click object.
 *
 * @description This function resets the device.
 * @note This function has small 200ms delay.
 */
void mic23099_reset ( mic23099_t *ctx );

/**
 * @brief Check Power Good pin function.
 *
 * @param ctx           Click object.
 * 
 * @return 
 * <pre> 0 : No Power Good </pre>
 * <pre> 1 : Power Good </pre>
 *
 * @description This function checks the state of Power Good output pin.
 */
uint8_t mic23099_check_power_good ( mic23099_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MIC23099_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
