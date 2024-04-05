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
 * \brief This file contains API for SOLAR ENERGY Click driver.
 *
 * \addtogroup solarenergy SOLAR ENERGY Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SOLARENERGY_H
#define SOLARENERGY_H

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
#define SOLARENERGY_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.out= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin= MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SOLARENERGY_RETVAL  uint8_t

#define SOLARENERGY_OK           0x00
#define SOLARENERGY_INIT_ERROR   0xFF
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

    digital_in_t out;
    digital_in_t int_pin;

} solarenergy_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t out;
    pin_name_t en;
    pin_name_t int_pin;

} solarenergy_cfg_t;

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
void solarenergy_cfg_setup ( solarenergy_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param solarenergy Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SOLARENERGY_RETVAL solarenergy_init ( solarenergy_t *ctx, solarenergy_cfg_t *cfg );

/**
 * @brief Charge enable function.
 *
 * @param ctx  Click object.
 *
 * @description Function enable charging by set CS ( EN ) pin,
 * enable BQ25570 Nano Power Boost Charger on Solar Energy click board.
 */
 void solarenergy_charge_enable ( solarenergy_t *ctx );
 
 /**
 * @brief Charge disable functions.
 *
 * @param ctx  Click object.
 *
 * @description Function disable charging by clear CS ( EN ) pin,
 * disable BQ25570 Nano Power Boost Charger on Solar Energy click board.
 */
void solarenergy_charge_disable ( solarenergy_t *ctx );

 /**
 * @brief Battery good indicator functions.
 *
 * @param ctx  Click object.
 *
 * @return
 * battery good indicator state:
 * - 0 : battery empty status;
 * - 1 : battery full status;
 *
 * @description Function get state of INT pin by check battery good indicator
 * from BQ25570 Nano Power Boost Charger on Solar Energy click board.
 */
uint8_t solarenergy_check_indicator ( solarenergy_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _SOLARENERGY_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
