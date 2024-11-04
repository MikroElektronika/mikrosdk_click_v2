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
 * \brief This file contains API for Buck Boost 2 Click driver.
 *
 * \addtogroup buckboost2 Buck Boost 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BUCKBOOST2_H
#define BUCKBOOST2_H

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
#define BUCKBOOST2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an= MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en= MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.mod= MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BUCKBOOST2_RETVAL  uint8_t

#define BUCKBOOST2_OK           0x00
#define BUCKBOOST2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup modes Modes
 * \{
 */
#define BUCKBOOST2_WITH_IMPROVEMENT       0x01
#define BUCKBOOST2_WITHOUT_IMPROVEMENT    0x00
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
    digital_out_t mod;

    // Input pins 

    digital_in_t an;

} buckboost2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t en;
    pin_name_t mod;

} buckboost2_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void buckboost2_cfg_setup ( buckboost2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param buckboost2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
BUCKBOOST2_RETVAL buckboost2_init ( buckboost2_t *ctx, buckboost2_cfg_t *cfg );

/**
 * @brief Power on function.
 * 
 * @param buckboost2 Click object.
 * 
 * @description This function powers on the chip.
 */
void buckboost2_power_on ( buckboost2_t *ctx  );

/**
 * @brief Power off function.
 * 
 * @param buckboost2 Click object.
 * 
 * @description This function powers OFF the chip
 */
void buckboost2_power_off ( buckboost2_t *ctx );

/**
 * @brief Mode setting functon
 *
 * @param buckboost2  Click object.
 * @param mode        sets chip's working mode.
 * 
 * @description This function sets the working mode.
 * @note Options:
 *    <pre>
       mode with improvement current, 
	     mode without improvement current
      </pre>
 */   
void buckboost2_set_mode ( buckboost2_t *ctx , uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif  // _BUCKBOOST2_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
