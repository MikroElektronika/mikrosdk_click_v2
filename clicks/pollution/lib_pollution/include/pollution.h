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
 * \brief This file contains API for Pollution Click driver.
 *
 * \addtogroup pollution Pollution Click Driver
 * @{
 */

#ifndef POLLUTION_H
#define POLLUTION_H

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
#define POLLUTION_MAP_MIKROBUS( cfg, mikrobus )   \
  cfg.an_pin = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.ena    = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define POLLUTION_RETVAL  uint8_t

#define POLLUTION_OK           0x00
#define POLLUTION_INIT_ERROR   0xFF
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
typedef  uint16_t pollution_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t ena;

    // Modules 

    analog_in_t adc;

} pollution_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an_pin;
    
    // Additional gpio pins 

    pin_name_t ena;

    // Static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef        

} pollution_cfg_t;

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
void pollution_cfg_setup ( pollution_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
POLLUTION_RETVAL pollution_init ( pollution_t *ctx, pollution_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Pollution click.
 * @note
 *    Click default configuration:
 * ------------------------------------------------------
 * <pre>
 *    Enable the WSP2110 sensor on Pollution Click Board.
 * </pre>
 * 
 * <pre>
 *    Reset the WSP2110 sensor on Pollution Click Board.
 * </pre>
 */
void pollution_default_cfg ( pollution_t *ctx );

/**
 * @brief Generic read function.
 *
 * @param ctx  Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
pollution_data_t pollution_generic_read ( pollution_t *ctx );

/**
 * @brief Enable sensor function.
 *
 * @param ctx  Click object.
 *
 * @description This function enable the WSP2110 sensor by set ENA pin 
 * on Pollution Click Board.
 */
void pollution_enable ( pollution_t *ctx );

/**
 * @brief Disable sensor function.
 *
 * @param ctx  Click object.
 *
 * @description This function disable the WSP2110 sensor by set ENA pin 
 * on Pollution Click Board.
 */
void pollution_disable ( pollution_t *ctx );

/**
 * @brief Reset sensor function.
 *
 * @param ctx  Click object.
 *
 * @description Function reset the WSP2110 sensor by set ENA pin,
 * wait and clear ENA pin on Pollution Click Board.
 * @note
 * ----------------------------------------------------
 * <pre>
 *    Inside Reset function exists two delays of 100ms.
 * </pre>
 */
void pollution_reset ( pollution_t *ctx );

/**
 * @brief Measure load voltage form ADC function.
 *
 * @param ctx  Click object.
 * @return Resault ( float value of the load voltage ).
 *
 * @description This function get load voltage from read ADC value
 * of the WSP2110 sensor on Pollution Click Board.
 */
float pollution_measure_load_voltage ( pollution_t *ctx );

/**
 * @brief Get the resistance of the sensor function.
 *
 * @param ctx  Click object.
 * @return Resault ( float value of the sensor resistance in kOhm ).
 *
 * @description This function get the resistance of the sensor, ie. measurement ADC value
 * of the WSP2110 sensor on Pollution Click Board.
 */
float pollution_get_resistance ( pollution_t *ctx );

/**
 * @brief Get the corrected resistance of the sensor function.
 *
 * @param ctx  Click object.
 * @return Resault ( float value of the corrected sensor resistance kOhm ).
 *
 * @description This function get the corrected resistance of the sensor, ie. measurement adc value
 * of the WSP2110 sensor on Pollution Click Board.
 */
float pollution_get_corrected_resistance ( pollution_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _POLLUTION_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
