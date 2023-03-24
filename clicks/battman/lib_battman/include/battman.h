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
 * \brief This file contains API for BATT-MAN Click driver.
 *
 * \addtogroup battman BATT-MAN Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BATTMAN_H
#define BATTMAN_H

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
#define BATTMAN_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.chg = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BATTMAN_RETVAL  uint8_t

#define BATTMAN_OK           0x00
#define BATTMAN_INIT_ERROR   0xFF
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

    digital_in_t chg;
    digital_in_t flt;

} battman_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t chg;
    pin_name_t en;
    pin_name_t flt;

} battman_cfg_t;

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
void battman_cfg_setup ( battman_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BATTMAN_RETVAL battman_init ( battman_t *ctx, battman_cfg_t *cfg );

/**
 * @brief Enable/Disable control
 *
 * @param ctx     Click object. 
 * @param state   1 = enable, 0 = disable
 *
 * @description Controls the operation of the click.
 */
void battman_set_enable ( battman_t *ctx, uint8_t state );

/**
 * @brief Charging indicator status
 *
 * @param ctx     Click object. 
 *
 * @returns  status ( 0 or 1 )
 *
 * @description Function for getting charging indicator status.
 */
uint8_t battman_get_charging_indicator ( battman_t *ctx );

/**
 * @brief Fault indicator status
 *
 * @param ctx     Click object. 
 *
 * @returns  status ( 0 or 1 )
 *
 * @description Function for getting fault indicator status.
 */
uint8_t battman_get_fault_indicator ( battman_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _BATTMAN_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
