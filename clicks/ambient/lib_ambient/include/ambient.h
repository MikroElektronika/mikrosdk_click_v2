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
 * \brief This file contains API for Ambient Click driver.
 *
 * \addtogroup ambient Ambient Click Driver
 * @{
 */


#ifndef AMBIENT_H
#define AMBIENT_H

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
#define AMBIENT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMBIENT_RETVAL  uint8_t

#define AMBIENT_OK           0x00
#define AMBIENT_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup ambient_parameters Ambient parameters.
 * \{
 */
#define AMBIENT_VCC_5_0                 5000
#define AMBIENT_VCC_3_3                 3300
#define AMBIENT_RES_10_BIT              1024
#define AMBIENT_RES_12_BIT              4096
#define AMBIENT_GAIN                    7
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
typedef  uint16_t ambient_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Modules 

    analog_in_t adc;

} ambient_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an_pin;

    // static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;                           // VRef        

} ambient_cfg_t;

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
void ambient_cfg_setup ( ambient_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AMBIENT_RETVAL ambient_init ( ambient_t *ctx, ambient_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
ambient_data_t ambient_generic_read ( ambient_t *ctx );

/**
 * @brief Calculate light intensity function.
 *
 * @param ctx        Click object.
 * @param adc_data   16-bit read ADC data.
 * @param vcc_val    16-bit VCC value.
 * @param adc_res    16-bit ADC resolution.
 *
 * @Function calculate light intensity from ADC data, VCC value and ADC resolution
 * of the Melexis MLX75305 IC on Ambient click board.
 */
uint16_t ambient_calculate_light_intensity ( ambient_t *ctx, uint16_t adc_data, uint16_t vcc_val, uint16_t adc_res );

#ifdef __cplusplus
}
#endif
#endif  // _AMBIENT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
