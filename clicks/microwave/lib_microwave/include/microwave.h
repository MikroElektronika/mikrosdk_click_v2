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
 * \file microwave.h
 *
 * \brief This file contains API for Microwave Click driver.
 *
 * \addtogroup microwave Microwave Click Driver
 * @{
 */


#ifndef _MICROWAVE_H_
#define _MICROWAVE_H_

#include "drv_analog_in.h"

// -------------------------------------------------------------- PUBLIC MACROS
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup sample_cnt Samples Count Target
 * \{
 */
#define MICROWAVE_SAMPLES_COUNT_50   50
#define MICROWAVE_SAMPLES_COUNT_100  100
#define MICROWAVE_SAMPLES_COUNT_200  200
/** \} */

/**
 * \defgroup threshold Threshold Target
 * \{
 */
#define MICROWAVE_THRESHOLD_10       10
#define MICROWAVE_THRESHOLD_25       25
#define MICROWAVE_THRESHOLD_50       50
#define MICROWAVE_THRESHOLD_100      100
#define MICROWAVE_THRESHOLD_200      200
#define MICROWAVE_THRESHOLD_500      500
/** \} */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define MICROWAVE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/** \} */ //  End macros group
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup types Types
 * \{
 */

/**
 * @brief Analog data type 
 */
typedef  uint16_t microwave_data_t;

/**
 * @brief Click code error definition.
 */
typedef enum
{
    MICROWAVE_OK = 0x0,
    MICROWAVE_ERR_INIT_ADC = 0xFF

} microwave_err_t;

/**
 * @brief Click context object definition.
 */
typedef struct
{
    analog_in_t  adc;

} microwave_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    //  Analog gpio pin.
    pin_name_t  out;

    //  Configuration variables.
    analog_in_resolution_t  resolution;   // Resolution
    float vref;   // VRef    

} microwave_cfg_t;

/** \} */ //  End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public Function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Configuration Object Setup function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to
 * initial state.
 * @note All used pins will be set to unconnected state and AD conversion
 *       configuration will be set to default value using channel 3 on the
 *       MIKROBUS 1. ADC will be set to 12-bit resolution using external VREF
 *       by default.
 */
void
microwave_cfg_setup( microwave_cfg_t *cfg );

/**
 * @brief Click Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 *
 * @returns 0x0 - Ok,
 *          0xFF - ADC init error.
 *
 * @description This function initializes the AD conversion.
 */
microwave_err_t
microwave_init( microwave_t *ctx, microwave_cfg_t *cfg );

/**
 * @brief Generic ADC Read function.
 *
 * @param ctx  Click object.
 *
 * @returns Result of the AD conversion.
 *
 * @description This function allows the ADC data reading from the selected
 * channel.
 */
microwave_data_t
microwave_generic_read( microwave_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  //  _MICROWAVE_H_

/** \} */ //  End public_function group
/// \}    //  End microwave group
/*! @} */
// ------------------------------------------------------------------------ END
