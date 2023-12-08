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
 * \brief This file contains API for REED Click driver.
 *
 * \addtogroup reed REED Click Driver
 * \{
 */
// ----------------------------------------------------------------------------

#ifndef REED_H
#define REED_H

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
#define REED_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define REED_OK            0
#define REED_INIT_ERROR  (-1)
/** \} */

/**
 * \defgroup mag_state Magnetic field detection state
 * \{
 */
#define REED_NO_MAGNETIC_FIELD        0
#define REED_MAGNETIC_FIELD_DETECTED  1
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

    digital_in_t cs;

} reed_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t cs;

} reed_cfg_t;

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
void reed_cfg_setup ( reed_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t reed_init ( reed_t *ctx, reed_cfg_t *cfg );

/**
 * @brief Get sensor magnetic detected status function.
 *
 * @param ctx  Click object.
 *
 * @return
 * <pre> 0 : no magnetic field </pre>
 * <pre> 1 : magnetic field detected </pre>
 *
 * @description This will return 1 if a magnetic field detected
 * and 0 if not detected.
 */
uint8_t reed_get_status ( reed_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // REED_H

/** \} */ // End public_function group
/// \}    // End click Driver group

// ------------------------------------------------------------------------ END
