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
 * \brief This file contains API for PLL Click driver.
 *
 * \addtogroup pll PLL Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PLL_H
#define PLL_H

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
#define PLL_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.s1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.s0 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.oe = MIKROBUS( mikrobus, MIKROBUS_CS );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PLL_OK              0
#define PLL_ERROR          -1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PLL_CLOCK_ENABLE    0x01
#define PLL_CLOCK_DISABLE   0x00
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
    // Input/Output pins 
    pin_name_t s1;
    pin_name_t s0;
    
    // Output pins 
    digital_out_t oe;

} pll_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 
    pin_name_t s1;
    pin_name_t s0;
    pin_name_t oe;

} pll_cfg_t;

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
void pll_cfg_setup ( pll_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param pll Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t pll_init ( pll_t *ctx, pll_cfg_t *cfg );

/**
 * @brief Functions for settings clock output.
 *
 * @param ctx   Click object.
 * @param mode  Mode which be set.
 *
 * @details This function settings clock output.
 * @note Options:
 *   Clock Enable,
 *   Clock Disable
 */
void pll_set_clock_output ( pll_t *ctx, uint8_t mode );

/**
 * @brief Functions for settings PLL x4.
 *
 * @param ctx   Click object.
 *
 * @details This function settings PLL x4.
 * @note If you use PLL x4, set S0 (RST pin) and S1 (AN pin) as OUTPUT.
 */
void pll_set_pll_4x ( pll_t *ctx );

/**
 * @brief Functions for settings PLL x5.
 *
 * @param ctx   Click object.
 *
 * @details This function settings PLL x5.
 * @note If you use PLL x5, set S0 (RST pin) and S1 (AN pin) as OUTPUT.
 */
void pll_set_pll_5x ( pll_t *ctx );

/**
 * @brief Functions for settings PLL x6.
 *
 * @param ctx   Click object.
 *
 * @details This function settings PLL x6.
 * @note If you use PLL x6, set S0 (RST pin) and S1 (AN pin) as OUTPUT.
 */
void pll_set_pll_6x ( pll_t *ctx );

/**
 * @brief Functions for settings PLL x6.
 *
 * @param ctx   Click object.
 *
 * @details This function settings PLL x6.
 * @note If you use PLL x8, set S0 (RST pin) and S1 (AN pin) as OUTPUT.
 */
void pll_set_pll_8x ( pll_t *ctx );

/**
 * @brief Functions for settings PLL x2.
 *
 * @param ctx   Click object.
 *
 * @details This function settings PLL x2.
 * @note If you use PLL x2, set S0 ( RST pin ) and S1 ( AN pin ) as INPUT.
 */
void pll_set_pll_2x ( pll_t *ctx );

/**
 * @brief Functions for settings PLL x3.
 *
 * @param ctx   Click object.
 *
 * @details This function settings PLL x3.
 * @note If you use PLL x3, set S0 ( RST pin ) as INPUT and S1 ( AN pin ) as OUTPUT.
 */
void pll_set_pll_3x ( pll_t *ctx );

/**
 * @brief Functions for settings PLL clock x3.125.
 *
 * @param ctx   Click object.
 *
 * @details This function settings PLL x3.125.
 * @note If you use PLL x3.125, set S1 ( AN pin ) as INPUT and S0( RST pin ) as OUTPUT.
 */
void pll_set_pll_3_125x ( pll_t *ctx );

/**
 * @brief Functions for settings PLL clock x6.25.
 *
 * @param ctx   Click object.
 *
 * @details This function settings PLL x6.25.
 * @note If you use PLL x6.25, set S1 ( AN pin ) as INPUT and S0( RST pin ) as OUTPUT.
 */
void pll_set_pll_6_25x ( pll_t *ctx );

/**
 * @brief Functions for settings PLL clock x5.3125.
 *
 * @param ctx   Click object.
 *
 * @details This function settings PLL x5.3125.
 * @note If you use PLL x5.3125, set S0 ( RST pin ) as INPUT and S1 ( AN pin ) as OUTPUT.
 */
void pll_set_pll_5_3125x ( pll_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PLL_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
