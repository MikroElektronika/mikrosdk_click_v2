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
 * \brief This file contains API for Boost 6 Click driver.
 *
 * \addtogroup boost6 Boost 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BOOST6_H
#define BOOST6_H

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
#define BOOST6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.rst= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BOOST6_RETVAL  uint8_t

#define BOOST6_OK           0x00
#define BOOST6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup state State
 * \{
 */
#define BOOST6_DISABLE      0x00
#define BOOST6_ENABLE       0x01
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
    digital_out_t cs;
    digital_out_t pwm;

} boost6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t cs;
    pin_name_t pwm;

} boost6_cfg_t;

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
void boost6_cfg_setup ( boost6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BOOST6_RETVAL boost6_init ( boost6_t *ctx, boost6_cfg_t *cfg );

/**
 * @brief Hardware reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function hardware reset the TPS55332-Q1 60-V Output Step Up DC/DC Converter
 * on Boost 6 click by cleared to '0' state of the RST pin,
 * wait the 100 ms, sets to '1' state of the RST pin and wait another the 100 ms.
 */
void boost6_hw_reset ( boost6_t *ctx );

/**
 * @brief Power OFF function.
 *
 * @param ctx  Click object.
 *
 * @description This function power OFF provides electrical off control of the regulator
 * TPS55332-Q1 60-V Output Step Up DC/DC Converter
 * on Boost 6 click by cleared to '0' state of the EN pin.
 */
void boost6_power_off ( boost6_t *ctx );

/**
 * @brief Power ON function.
 *
 * @param ctx  Click object.
 *
 * @description This function power ON provides electrical off control of the regulator
 * TPS55332-Q1 60-V Output Step Up DC/DC Converter
 * on Boost 6 click by sets to '1' state of the EN pin.
 */
void boost6_power_on ( boost6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BOOST6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
