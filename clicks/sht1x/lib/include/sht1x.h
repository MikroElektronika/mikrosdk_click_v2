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
 * \brief This file contains API for SHT1x Click driver.
 *
 * \addtogroup sht1x SHT1x Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SHT1X_H
#define SHT1X_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define SHT1X_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl= MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda= MIKROBUS( mikrobus, MIKROBUS_SDA )

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SHT1X_RETVAL  uint8_t

#define SHT1X_OK           0x00
#define SHT1X_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup SHT1x_command_definitions    SHT1x Command Definitions
 * \{
 */
#define SHT1X_MEAS_TEMP                         0x03
#define SHT1X_MEAS_HUMI                         0x05
#define SHT1X_STAT_REG_W                        0x06
#define SHT1X_STAT_REG_R                        0x07
#define SHT1X_SOFT_RESET                        0x1E
/** \} */

/**
 * \defgroup status_register_writable_bits    Status Register Writable Bits
 * \{
 */
#define SHT1X_SR_MASK                           0x07
/** \} */

/**
 * \defgroup getByte_flags  GetByte Flags
 * \{
 */
#define SHT1X_NACK                              0
#define SHT1X_ACK                               1
/** \} */

/**
 * \defgroup temperature_& _humidity_equation_constants       Temperature & Humidity Equation Constants
 * \{
 */
#define SHT1X_D1                                  -40.1     
#define SHT1X_D2h                                   0.01    
#define SHT1X_D2l                                   0.04    
#define SHT1X_V3_C1                               -4.0000  
#define SHT1X_V3_C2h                               0.0405   
#define SHT1X_V3_C3h                              -2.8000E-6
#define SHT1X_V3_C2l                               0.6480   
#define SHT1X_V3_C3l                              -7.2000E-4
#define SHT1X_V4_C1                               -2.0468   
#define SHT1X_V4_C2h                               0.0367   
#define SHT1X_V4_C3h                              -1.5955E-6
#define SHT1X_V4_C2l                               0.5872   
#define SHT1X_V4_C3l                              -4.0845E-4
#define SHT1X_T1                                   0.01     
#define SHT1X_T2h                                  0.00008  
#define SHT1X_T2l                                  0.00128  
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

   digital_out_t scl;
   digital_out_t sda;

} sht1x_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

   pin_name_t scl;
   pin_name_t sda;

} sht1x_cfg_t;

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
void sht1x_cfg_setup ( sht1x_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SHT1X_RETVAL sht1x_init ( sht1x_t *ctx, sht1x_cfg_t *cfg );

/**
 * @brief Set pin on output.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function sets pins on output.
 */
void sht1x_output_sda ( sht1x_t *ctx, sht1x_cfg_t *cfg );

/**
 * @brief Set pin on input.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function Set pin on input.
 */
void sht1x_input_sda ( sht1x_t *ctx, sht1x_cfg_t *cfg );

/**
 * @brief Set SDA high function.
 *
 * @param ctx Click object.
 * 
 * @description This function is used to set state of SDA pin.
**/
void sht1x_sda_high ( sht1x_t *ctx );

/**
 * @brief Set SDA low function
 *
 * @param ctx Click object.
 * 
 * @description This function is used to set state of SDA pin.
**/
void sht1x_sda_low ( sht1x_t *ctx );

/**
 * @brief Check SDA state function
 *
 * @param ctx Click object.
 * 
 * @returns '0' pin state is low
 * @returns '1' pin state is high
 *
 * What is function job.
 * @note It is not necessary (only if you have specific description).
**/
uint8_t sht1x_get_sda ( sht1x_t *ctx );

/**
 * @brief Set SCL high function
 *
 * @param ctx Click object.
 * 
 * @description This function is used to set state of SDA pin.
**/
void sht1x_scl_high ( sht1x_t *ctx );

/**
 * @brief Set SCL low function
 *
 * @param ctx Click object.
 * 
 * @description This function is used to set state of SDA pin.
**/
void sht1x_scl_low ( sht1x_t *ctx );

/**
 * @brief Calculate temperature function
 *
 * @param ctx Click object.
 * @param t  14-bit value representing number of ticks
 *
 * @returns tempOut float value representing the temperature
 *
 * @description This function is used to calculate temperature.
**/
float sht1x_calc_temp ( sht1x_t *ctx, uint16_t t );

/**
 * @brief Calculate humidity function
 *
 * @param ctx Click object.
 * @param h  12-bit value representing number of ticks
 * @param t  14-bit value representing number of ticks
 *
 * @returns rh_true float value representing the humidity
 *
 * @description This function is used to calculate humidity.
**/
float sht1x_calc_humi ( sht1x_t *ctx, uint16_t h, uint16_t t );

#ifdef __cplusplus
}
#endif
#endif  // _SHT1X_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
