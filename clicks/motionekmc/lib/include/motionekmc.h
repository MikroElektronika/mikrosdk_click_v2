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
 * \brief This file contains API for Motion EKMC Click driver.
 *
 * \addtogroup motionekmc Motion EKMC Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MOTIONEKMC_H
#define MOTIONEKMC_H

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
#define MOTIONEKMC_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MOTIONEKMC_RETVAL  uint8_t

#define MOTIONEKMC_OK           0x00
#define MOTIONEKMC_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup active_state Active state
 * \{
 */
#define MOTIONEKMC_MODULE_ENABLE 0x00
#define MOTIONEKMC_MODULE_DISABLE 0x01
/** \} */

/**
 * \defgroup detect Detect state
 * \{
 */
#define MOTIONEKMC_DETECT_OBJECT 0x01

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

} motionekmc_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

   pin_name_t en;
   pin_name_t int_pin;

} motionekmc_cfg_t;

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
void motionekmc_cfg_setup ( motionekmc_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param motionekmc Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MOTIONEKMC_RETVAL motionekmc_init ( motionekmc_t *ctx, motionekmc_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Motion EKMC click.
 */
void motionekmc_default_cfg ( motionekmc_t *ctx );


/**
 * @brief Functions for active motion sensors
 *
 * @param status Enable or Disable sensor
 */
void motionekmc_active ( motionekmc_t *ctx, uint8_t state );

/**
 * @brief Gets detection state
 *
 * @return  Detection status
 *       ( 1 - Detected / 0 - Not detected )
 */
uint8_t motionekmc_detect_state ( motionekmc_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _MOTIONEKMC_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
