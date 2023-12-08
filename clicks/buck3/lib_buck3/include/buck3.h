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
 * \brief This file contains API for Buck 3 Click driver.
 *
 * \addtogroup buck3 Buck 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCK3_H
#define BUCK3_H

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
#define BUCK3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.en= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.pgd= MIKROBUS( mikrobus, MIKROBUS_CS ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCK3_RETVAL  uint8_t

#define BUCK3_OK           0x00
#define BUCK3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mode Power mode
 * \{
 */
#define BUCK3_MODE_ACTIVE  0x01
#define BUCK3_MODE_SLEEP   0x00
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

    digital_in_t pgd;
    
} buck3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t en;
    pin_name_t pgd;

} buck3_cfg_t;

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
void buck3_cfg_setup ( buck3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buck3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCK3_RETVAL buck3_init ( buck3_t *ctx, buck3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Buck 3 click.
 * @note Default configuration contains:
 * <pre>
 *    - Power mode (Device actiive)
 * </pre>
 */
void buck3_default_cfg ( buck3_t *ctx );

/**
 * @brief Function reads state of PGD pin
 *
 * @param ctx  Click object.
 * @return State of PGD pin
 * <pre>
 *  - 1 / FB pin voltage is between 93% and 107% of the internal reference voltage (VREF).
 *  - 0 / Overvoltage detected or device is under thermal shutdown.
 * </pre>
 */
uint8_t buck3_get_power_good ( buck3_t *ctx );

/**
 * @brief Function for setting chip mode
 *
 * @param ctx  Click object.
 * @param state  Turns device ON or OFF
 * 
 * @note Options:
 * <pre>
 *   - ACTIVE mode
 *   - SLEEP mode
 * </pre>
 *
 */
void buck3_set_device_state ( buck3_t *ctx, uint8_t state );


#ifdef __cplusplus
}
#endif
#endif  // _BUCK3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
