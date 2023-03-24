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
 * \brief This file contains API for HZ to V 2 Click driver.
 *
 * \addtogroup hztov2 HZ to V 2 Click Driver
 * @{
 */


#ifndef HZTOV2_H
#define HZTOV2_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_analog_in.h"
#include "drv_pwm.h"

// -------------------------------------------------------------- PUBLIC MACROS 

/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define HZTOV2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.fin = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HZTOV2_RETVAL  uint8_t

#define HZTOV2_OK           0x00
#define HZTOV2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define HZTOV2_DEF_FREQ     10000
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
typedef  uint16_t hztov2_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t en;
    
    // Modules 

    pwm_t fin;
    analog_in_t adc;
    
    // ctx variable 
    
    uint32_t  pwm_freq;

} hztov2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an_pin;
    pin_name_t fin;
    
    // Additional gpio pins 

    pin_name_t en;

    // static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef 
    uint32_t  dev_pwm_freq;

} hztov2_cfg_t;

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
void hztov2_cfg_setup ( hztov2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HZTOV2_RETVAL hztov2_init ( hztov2_t *ctx, hztov2_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
hztov2_data_t hztov2_generic_read ( hztov2_t *ctx );

/**
 * @brief Read voltage function.
 *
 * @param ctx        Click object.
 * @return Voltage
 *
 * @description This function read ADC data and converts it to voltage.
 */
float hztov2_read_voltage ( hztov2_t *ctx );

/**
 * @brief Function for enabling the click board.
 * 
 * @param ctx       Click object.
 * @param pin_state Pin state.
 * 
 * @description This function enable the click board.
 */
void hztov2_en_pin ( hztov2_t *ctx, uint8_t pin_state );

/**
 * @brief PWM frequency set function.
 *
 * @param ctx      Click object.
 * @param fin       PWM frequency input value in the range of 200 to 120000 Hz.
 *
 * @return HZTOV2_RETVAL
 *
 * @description This function sets PWM clock frequency at FIN pin.
 */
HZTOV2_RETVAL hztov2_fin_set ( hztov2_t *ctx, uint32_t fin );

#ifdef __cplusplus
}
#endif
#endif  // _HZTOV2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
