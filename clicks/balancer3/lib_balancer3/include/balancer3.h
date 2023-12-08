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
 * \brief This file contains API for Balancer 3 Click driver.
 *
 * \addtogroup balancer3 Balancer 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BALANCER3_H
#define BALANCER3_H

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
#define BALANCER3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BALANCER3_OK                    0
#define BALANCER3_ERROR                -1
/** \} */

/**
 * \defgroup enable_disable   Enable Disable
 * \{
 */
#define BALANCER3_CELL_BALANCE_EN       0
#define BALANCER3_CELL_BALANCE_DIS      1
/** \} */

/**
 * \defgroup detected   Detected
 * \{
 */
#define BALANCER3_OV_COND_DETECTED      1
#define BALANCER3_OV_COND_NOT_DETECTED  0
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

} balancer3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 
    pin_name_t en;
    pin_name_t int_pin;

} balancer3_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void balancer3_cfg_setup ( balancer3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param balancer3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t balancer3_init ( balancer3_t *ctx, balancer3_cfg_t *cfg );

/**
 * @brief Cell Balance Enable function.
 *
 * @param ctx   Click object.
 * @param state 0 - enable, 1 (or other value different from 0) - disable.
 * 
 * @details This function allows user to enable or disable Cell Balance (cell mismatch correction circuitry).
 */
void balancer3_enable_cell_balance ( balancer3_t *ctx, uint8_t state );

/**
 * @brief Overvoltage Condition Check function.
 *
 * @param ctx Click object.
 * 
 * @details This fis function checks the Overvoltage condition.
 */
uint8_t balancer3_check_overvoltage ( balancer3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BALANCER3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
