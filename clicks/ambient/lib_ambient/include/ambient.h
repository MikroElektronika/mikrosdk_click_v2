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

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
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
#define AMBIENT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an_pin  = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMBIENT_OK                      0
#define AMBIENT_ERROR                  -1
/** \} */

/**
 * \defgroup ambient_parameters Ambient parameters.
 * \{
 */
#define AMBIENT_VCC_5_0                 5.0f
#define AMBIENT_VCC_3_3                 3.3f
#define AMBIENT_VOLTS_TO_MILLIVOLTS     1000.0f
#define AMBIENT_GAIN                    7
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
    analog_in_resolution_t resolution;   // Resolution
    float vref;                          // VRef        

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void ambient_cfg_setup ( ambient_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t ambient_init ( ambient_t *ctx, ambient_cfg_t *cfg );

/**
 * @brief Ambient read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #ambient_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ambient_read_an_pin_value ( ambient_t *ctx, uint16_t *data_out );

/**
 * @brief Ambient read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #ambient_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t ambient_read_an_pin_voltage ( ambient_t *ctx, float *data_out );

/**
 * @brief Calculate light intensity function.
 *
 * @param ctx        Click object.
 * @return Light intensity value.
 *
 * @details Calculates the light intensity from analog voltage measurement
 * of the Melexis MLX75305 IC on Ambient click board.
 */
uint16_t ambient_get_light_intensity ( ambient_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AMBIENT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------ END
