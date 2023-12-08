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
 * \brief This file contains API for Hall Current 5 Click driver.
 *
 * \addtogroup hallcurrent5 Hall Current 5 Click Driver
 * @{
 */

#ifndef HALLCURRENT5_H
#define HALLCURRENT5_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define HALLCURRENT5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HALLCURRENT5_RETVAL  uint8_t

#define HALLCURRENT5_OK           0x00
#define HALLCURRENT5_INIT_ERROR   0xFF
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
typedef  uint16_t hallcurrent5_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    analog_in_t adc;
 
    uint16_t dev_init_volt;

} hallcurrent5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an_pin;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef   
    
    uint16_t init_volt;

} hallcurrent5_cfg_t;

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
void hallcurrent5_cfg_setup ( hallcurrent5_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HALLCURRENT5_RETVAL hallcurrent5_init ( hallcurrent5_t *ctx, hallcurrent5_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function read ADC data.
 */
hallcurrent5_data_t hallcurrent5_generic_read ( hallcurrent5_t *ctx );

/**
 * @brief Generic function for read voltage.
 *
 * @param ctx        Click object.
 * @return voltage value
 *
 * @description This function read voltage value.
 */
float hallcurrent5_generic_read_voltage ( hallcurrent5_t *ctx );


/**
 * @brief Get ADC current value function.
 *
 * @param ctx        Click object.
 *
 * @description This function gets ADC current value.
 */
float hallcurrent5_get_current ( hallcurrent5_t *ctx );

/**
 * @brief Get ADC fault function.
 *
 * @param ctx        Click object.
 *
 * @description This function gets fault.
 */
uint8_t hallcurrent5_get_fault ( hallcurrent5_t *ctx );

/**
 * @brief Get ADC current value function.
 *
 * @param ctx        Click object.
 * @param voltage    Voltage
 *
 * @description This function gets ADC value.
 */
void hallcurrent5_set_init_voltage ( hallcurrent5_t *ctx, uint16_t voltage );

#ifdef __cplusplus
}
#endif
#endif  // _HALLCURRENT5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
