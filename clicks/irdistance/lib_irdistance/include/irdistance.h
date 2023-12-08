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
 * \brief This file contains API for IR distance Click driver.
 *
 * \addtogroup irdistance IR distance Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRDISTANCE_H
#define IRDISTANCE_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
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
#define IRDISTANCE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.out = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en  = MIKROBUS( mikrobus, MIKROBUS_RST )
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

    // Modules

    analog_in_t adc;

} irdistance_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins

    pin_name_t out;
    pin_name_t en;

    // Static variable

    analog_in_resolution_t resolution;   /** ADC Resolution */
    float vref;                          /** Reference Voltage */

} irdistance_cfg_t;

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
 * @param cfg Click configuration structure.
 *
 * @description This function initializes click configuration structure to init
 * state.
 * @note All used pins will be set to unconnected state.
 */
void irdistance_cfg_setup ( irdistance_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 *
 * @return See #err_t definition of data type.
 *            0  - Success,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals
 * used for this click.
 */
err_t irdistance_init ( irdistance_t *ctx, irdistance_cfg_t *cfg );

/**
 * @brief Enable IR sensor function
 *
 * @param ctx Click object.
 *
 * @description Function enables distance measuring on the sensor by setting EN
 * pin on the IR distance click board.
 */
void irdistance_enable_device ( irdistance_t *ctx );

/**
 * @brief Disable IR sensor function
 *
 * @param ctx Click object.
 *
 * @description Function disables distance measuring on the sensor by clearing
 * EN pin on the IR distance click board.
*/
void irdistance_disable_device ( irdistance_t *ctx );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object.
 * @param data_out ADC value on the pin.
 *
 * @return See #err_t definition of data type.
 *
 * @description This function reads ADC value on the pin.
 */
err_t irdistance_read_adc ( irdistance_t *ctx, uint16_t *data_out );

/**
 * @brief Get the voltage output of the sensor function
 *
 * @param ctx Click object.
 * @param data_out Voltage value on the pin.
 *
 * @return See #err_t definition of data type.
 *
 * @description This function reads voltage value on the pin.
*/
err_t irdistance_get_pin_voltage ( irdistance_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif  // _IRDISTANCE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group
/*! @} */
// ------------------------------------------------------------------------- END
