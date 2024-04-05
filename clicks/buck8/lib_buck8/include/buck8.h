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
 * \brief This file contains API for Buck 8 Click driver.
 *
 * \addtogroup buck8 Buck 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCK8_H
#define BUCK8_H

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
#define BUCK8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.rst= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.syn= MIKROBUS( mikrobus, MIKROBUS_PWM ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCK8_RETVAL  uint8_t

#define BUCK8_OK           0x00
#define BUCK8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mode Power mode
 * \{
 */
#define BUCK8_MODE_ACTIVE  0x01
#define BUCK8_MODE_SLEEP   0x00
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
    digital_in_t en;
    digital_out_t syn;

} buck8_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t en;
    pin_name_t syn;

} buck8_cfg_t;

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
void buck8_cfg_setup ( buck8_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param buck8 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BUCK8_RETVAL buck8_init ( buck8_t *ctx, buck8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Buck 8 click.
 * @note Defaut configuration contains: 
 * <pre>
 *    - Set power mode (Active)
 * </pre>
 */
void buck8_default_cfg ( buck8_t *ctx );

/**
 * @brief Function settings mode 
 *
 * @param ctx  Click object
 * 
 * @note Options:
 * <pre>
 *  - Active mode
 *  - Sleep mode
 * </pre>	  
 */
void buck8_set_power_mode ( buck8_t *ctx, uint8_t mode );

/**
 * @brief Function reads state of pin
 *
 * @param ctx  Click object
 * 
 * @return State of pin
 * <pre>
 *  - 1 / if the input voltage is greater than the set maximum range.
 *  - 0 / if the input voltage is lower than the set maximum range.
 * </pre>
 */
uint8_t buck8_get_state ( buck8_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _BUCK8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
