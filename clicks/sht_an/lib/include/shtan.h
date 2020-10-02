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
 * \brief This file contains API for SHT AN Click driver.
 *
 * \addtogroup shtan SHT AN Click Driver
 * @{
 */


#ifndef SHTAN_H
#define SHTAN_H

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
#define SHTAN_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SHTAN_RETVAL  uint8_t

#define SHTAN_OK           0x00
#define SHTAN_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup other_macros Other Macros
 * \{
 */
#define     SHTAN_SET_ADC_MODE_TEMP            0
#define     SHTAN_SET_ADC_MODE_HUM             1

#define     SHTAN_V_REF_2_048_mV               2.048
#define     SHTAN_V_REF_3_0_mV                 3.0
#define     SHTAN_V_REF_3_3_mV                 3.3

#define     SHTAN_V_DD_3_3_mV                  3.3
#define     SHTAN_V_DD_5_0_mV                  5.0

#define     SHTAN_ADC_RES_10_BIT            1024.0
#define     SHTAN_ADC_RES_12_BIT            4096.0
#define     SHTAN_ADC_RES_14_BIT           16383.0
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
typedef  uint16_t shtan_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    digital_out_t cs;
    
    // Modules 

    analog_in_t adc;

} shtan_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an_pin;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t cs;

    // static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;                           // VRef    

} shtan_cfg_t;

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
void shtan_cfg_setup ( shtan_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SHTAN_RETVAL shtan_init ( shtan_t *ctx, shtan_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for SHT AN click.
 */
void shtan_default_cfg ( shtan_t *ctx );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
shtan_data_t shtan_generic_read ( shtan_t *ctx );

/**
 * @brief Set ADC mode function
 *
 * @param ctx        Click object.
 * @param adc_mode
 * 
 * 8-bit ADC mode
 * - 0 ( SHTAN_SET_ADC_MODE_TEMP ) - Set signal output, ADC mode temperature.
 * - 1 ( SHTAN_SET_ADC_MODE_HUM )  - Set signal output, ADC mode humidity.
 *
 * @description Function sets signal output ADC mode 
 * of the SHT3x-ARP Humidity and Temperature Sensor IC on SHT AN Click.
**/
void shtan_set_mode ( shtan_t *ctx, uint8_t adc_mode );

/**
 * @brief Hardware reset function
 *
 * @param ctx        Click object.
 * 
 * @description Function hardware reset the SHT3x-ARP Humidity and Temperature Sensor IC
 * on SHT AN click by cleared to '0' state of the RST pin,
 * wait the 100 ms, sets to '1' state of the RST pin.
 *
 * @note
 * Delay is 100 ms.
**/
void shtan_reset ( shtan_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _SHTAN_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
