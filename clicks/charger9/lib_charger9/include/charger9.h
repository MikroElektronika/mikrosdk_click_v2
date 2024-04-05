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
 * \brief This file contains API for Charger 9 Click driver.
 *
 * \addtogroup charger9 Charger 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CHARGER9_H
#define CHARGER9_H

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
#define CHARGER9_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.flt= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.shd= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.chg= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.ful= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CHARGER9_RETVAL     uint8_t
#define CHARGER9_STATE      uint8_t

#define CHARGER9_OK           0x00
#define CHARGER9_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup status Status
 * \{
 */
#define CHARGER9_ENABLE              0x01
#define CHARGER9_DISABLE             0x00
/** \} */

/**
 * \defgroup possible_state Possible State
 * \{
 */
#define CHARGER9_INVALID_STATE       0xFF
#define CHARGER9_OK                  0x00
#define CHARGER9_IND_ACTIVE          0x00
#define CHARGER9_IND_INACTIVE        0x01
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

    digital_out_t shd;

    // Input pins 

    digital_in_t flt;
    digital_in_t chg;
    digital_in_t ful;

} charger9_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t flt;
    pin_name_t shd;
    pin_name_t chg;
    pin_name_t ful;

} charger9_cfg_t;

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
void charger9_cfg_setup ( charger9_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param charger9 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CHARGER9_RETVAL charger9_init ( charger9_t *ctx, charger9_cfg_t *cfg );

/**
 * @brief Enable function
 *
 * @param ctx        Click object.
 * @param pwr_state  0 - Shutdown state, 1 - Power ON state
 *
 * @returns 0 - OK, 1 - Invalid parameter value
 *
 * @description This function allows user to enable or disable the device.
 */
CHARGER9_RETVAL charger9_enable ( charger9_t *ctx, CHARGER9_STATE pwr_state );

/**
 * @brief Fast-Charge Indicate function
 *
 * @param ctx  Click object.
 * 
 * @returns 0 - Active process, 1 - Inactive process
 *
 * @description This function indicates the Fast-Charge mode, constant current charging.
 */
CHARGER9_RETVAL charger9_fast_charge_ind ( charger9_t *ctx );

/**
 * @brief Full-Charge Indicate function
 *
 * @param ctx  Click object.
 * 
 * @returns 0 - Active process, 1 - Inactive process
 *
 * @description This function indicates the Full-Charge mode, constant voltage charging.
 */
CHARGER9_RETVAL charger9_full_charge_ind ( charger9_t *ctx );

/**
 * @brief Fault Indicate function
 * 
 * @param ctx  Click object.
 * 
 * @returns 0 - Active process, 1 - Inactive process
 *
 * @description This function indicates the Fault condition, charging terminates abnormally.
 */
CHARGER9_RETVAL charger9_fault_ind ( charger9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _CHARGER9_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
