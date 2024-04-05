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
  cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click adc mode descriptors.
 */
typedef enum
{
    SHTAN_SET_ADC_MODE_TEMP,
    SHTAN_SET_ADC_MODE_HUM

} shtan_adc_mode_t;

/**
 * @brief Click temperature unit mode descriptors.
 */
typedef enum
{
    SHTAN_SET_TEMP_MODE_DEG_C,
    SHTAN_SET_TEMP_MODE_DEG_F

} shtan_temp_mode_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    digital_out_t cs;

    float vdd;

    // Modules 

    analog_in_t adc;

} shtan_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t an;

    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t cs;

    // Static variable 

    analog_in_resolution_t resolution;   // Resolution
    float vref;                          // Reference voltage
    float vdd;                           // Power supply voltage

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
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t shtan_init ( shtan_t *ctx, shtan_cfg_t *cfg );

/**
 * @brief ADC read function.
 *
 * @param ctx Click object.
 * @param data_out Output read data.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads the ADC converted data.
 */
err_t shtan_read_adc ( shtan_t *ctx, uint16_t *data_out );

/**
 * @brief AN voltage read function.
 *
 * @param ctx  Click object.
 * @param data_out Output read voltage value.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads and calculates the voltage level of the AN pin.
 */
err_t shtan_read_an_voltage ( shtan_t *ctx, float *data_out );

/**
 * @brief Temperature measure function.
 *
 * @param ctx Click object.
 * @param data_out Output temperature value [deg C/F].
 * @param sel 0 - deg C,
 *            1 - deg F.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function measures a temperature results converting them to the selected unit.
 */
err_t shtan_meas_temperature ( shtan_t *ctx, float *data_out, shtan_temp_mode_t sel );

/**
 * @brief Humidity measure function.
 *
 * @param ctx Click object.
 * @param data_out Output relative humidity value [%].
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function measures a relative humidity level.
 */
err_t shtan_meas_humidity ( shtan_t *ctx, float *data_out );

/**
 * @brief Set ADC mode function.
 *
 * @param ctx Click object.
 * @param sel - 0 ( SHTAN_SET_ADC_MODE_TEMP ) - Set signal output, ADC mode temperature.
 *            - 1 ( SHTAN_SET_ADC_MODE_HUM )  - Set signal output, ADC mode humidity.
 *
 * @description Function sets signal output ADC mode of the SHT3x-ARP Humidity and Temperature
 * Sensor IC on SHT AN Click.
 */
void shtan_set_mode ( shtan_t *ctx, shtan_adc_mode_t sel );

/**
 * @brief Hardware reset function.
 *
 * @param ctx Click object.
 *
 * @description Function hardware reset the SHT3x-ARP Humidity and Temperature Sensor IC
 * on SHT AN click by cleared to '0' state of the RST pin, wait the 100 ms, then sets to
 * '1' state of the RST pin and wait for 1 second to establish the device.
 */
void shtan_reset ( shtan_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // SHTAN_H

/** \} */ // End public_function group
/// \}    // End click Driver group
/*! @} */
// ------------------------------------------------------------------------ END
