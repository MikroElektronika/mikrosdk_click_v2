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
 * \brief This file contains API for Pedometer Click driver.
 *
 * \addtogroup pedometer Pedometer Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PEDOMETER_H
#define PEDOMETER_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define PEDOMETER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PEDOMETER_RETVAL  uint8_t

#define PEDOMETER_OK           0x00
#define PEDOMETER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup step_detected Step Detected
 * \{
 */
#define PEDOMETER_NEW_STEP_DETECTED  0x01
#define PEDOMETER_NO_STEP_DETECTED   0x00
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

    // Input pins 

    digital_in_t int_pin;
    int16_t step_counter;


} pedometer_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t int_pin;
    int16_t dev_step_counter;
    
} pedometer_cfg_t;

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
void pedometer_cfg_setup ( pedometer_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param pedometer Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PEDOMETER_RETVAL pedometer_init ( pedometer_t *ctx, pedometer_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Pedometer click.
 */
void pedometer_default_cfg ( pedometer_t *ctx );

/**
 * @brief Functions for reset Step counter.
 *
 * 
 * @param ctx          Click object.
 * @param new_cnt      New cnt.
 *
 * @description This function reset step counter.
 */
void pedometer_reset_step_counter ( pedometer_t *ctx, uint32_t new_cnt );

/**
 * @brief Functions for get Interrupt state on the INT pin.
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function gets interrupt state.
 */
uint8_t pedometer_get_interrupt_state ( pedometer_t *ctx );

/**
 * @brief Functions for get step counter.
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function gets counter.
 */
uint32_t pedometer_get_step_counter ( pedometer_t *ctx );

/**
 * @brief Pedometer process.
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function gets pedometer process.
 */
uint8_t pedometer_process ( pedometer_t *ctx  );

#ifdef __cplusplus
}
#endif
#endif  // _PEDOMETER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
