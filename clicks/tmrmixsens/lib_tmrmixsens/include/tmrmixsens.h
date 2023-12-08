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
 * \brief This file contains API for TMR MIX SENS Click driver.
 *
 * \addtogroup tmrmixsens TMR MIX SENS Click Driver
 * @{
 */


#ifndef TMRMIXSENS_H
#define TMRMIXSENS_H

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
#include "drv_analog_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 

/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define TMRMIXSENS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.omn = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.bi = MIKROBUS( mikrobus, MIKROBUS_CS )

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TMRMIXSENS_RETVAL  uint8_t

#define TMRMIXSENS_OK           0x00
#define TMRMIXSENS_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup south_and_north_pole South And North Pole
 * \{
 */
#define TMRMIXSENS_SOUTH_POLE      0
#define TMRMIXSENS_NORTH_POLE       1
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Analog data type 
 */
typedef  uint16_t tmrmixsens_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 

    digital_in_t omn;
    digital_in_t bi;
    
    // Modules 

    analog_in_t adc;

} tmrmixsens_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an_pin;
    
    // Additional gpio pins 

    pin_name_t omn;
    pin_name_t bi;

    // static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;                           // VRef    

} tmrmixsens_cfg_t;

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
void tmrmixsens_cfg_setup ( tmrmixsens_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TMRMIXSENS_RETVAL tmrmixsens_init ( tmrmixsens_t *ctx, tmrmixsens_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
tmrmixsens_data_t tmrmixsens_generic_read ( tmrmixsens_t *ctx );

/**
 * @brief Get state of the omnipolar ( OMN ) pin function.
 *
 * @param ctx Click object.
 * 
 * @returns
 * state of the omnipolar:
 * - 0 : inactive;
 * - 1 : active state;
 *
 * @description This function react to the presence of a magnetic field
 * and returns a state of the omnipolar ( OMN ) pin
 * on the TMR mix-sens Click.
 */
uint8_t tmrmixsens_get_omnipolar ( tmrmixsens_t *ctx );

/**
 * @brief Get state of the bipolar ( BI ) pin function.
 *
 * @param ctx Click object.
 * 
 * @returns
 * state of the bipolar:
 * - 0 : inactive, Nort pole;
 * - 1 : active state, South pole;
 *
 * @description This function respond to changes north or south magnetic pole
 * and return a state of the bipolar ( BI ) pin
 * on the TMR mix-sens Click.
 */
uint8_t tmrmixsens_get_bipolar ( tmrmixsens_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TMRMIXSENS_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
