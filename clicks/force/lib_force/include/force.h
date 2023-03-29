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
 * \brief This file contains API for Force Click driver.
 *
 * \addtogroup force Force Click Driver
 * @{
 */


#ifndef FORCE_H
#define FORCE_H

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
#define FORCE_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FORCE_RETVAL  uint8_t

#define FORCE_OK           0x00
#define FORCE_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup constants Constants
 * \{
 */
#define FORCE_RLOAD      10.0
#define FORCE_RZERO      76.63
#define FORCE_PARA       116.6020682
#define FORCE_PARB       2.769034857
#define FORCE_CORA       0.00035
#define FORCE_CORB       0.02718
#define FORCE_CORC       1.39538
#define FORCE_CORD       0.0018
#define FORCE_ATMOCO2    397.13         
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
typedef  uint16_t force_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{   
    // Modules 

    analog_in_t adc;

} force_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an_pin;

    // static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef

} force_cfg_t;

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
void force_cfg_setup ( force_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
FORCE_RETVAL force_init ( force_t *ctx, force_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function reads ADC data.
 */
force_data_t force_generic_read ( force_t *ctx );

/**
 * @brief Get correction factor function.
 *
 * @param temperature    Temperature value.
 * @param humidity       Humidity value.
 *
 * @description This function calculates the correction factor based on temperature and 
 *              humidity data.
 */
float force_get_correction_factor ( float temperature, float humidity );

/**
 * @brief Get resistance function.
 *
 * @param adc_value    ADC value.
 *
 * @description This function calculates resistance data based on the ADC input.
 */
float force_get_resistance ( uint32_t adc_value );

/**
 * @brief Get corrected resistance function.
 *
 * @param temperature    Temperature value.
 * @param humidity       Humidity value.
 * @param adc_value      ADC value.
 *
 * @description This function calculates corrected resistance data based on the ADC input.
 */
float force_get_corrected_resistance ( float temperature, float humidity, uint32_t adc_value );

#ifdef __cplusplus
}
#endif
#endif  // _FORCE_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
