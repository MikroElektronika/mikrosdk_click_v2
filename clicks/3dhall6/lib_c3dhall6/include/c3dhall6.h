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
 * \brief This file contains API for 3D Hall 6 Click driver.
 *
 * \addtogroup c3dhall6 3D Hall 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C3DHALL6_H
#define C3DHALL6_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define C3DHALL6_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C3DHALL6_OK             0
#define C3DHALL6_ERROR         -1
/** \} */

/**
 * \defgroup channel Channel
 * \{
 */
#define C3DHALL6_CHANNEL_0      0x00
#define C3DHALL6_CHANNEL_1      0x40
#define C3DHALL6_CHANNEL_2      0x80
#define C3DHALL6_CHANNEL_3      0xC0
/** \} */

/**
 * \defgroup die Die
 * \{
 */
#define C3DHALL6_DIE_A          0x01
#define C3DHALL6_DIE_B          0x02
/** \} */

/**
 * \defgroup pi_const Pi Const
 * \{
 */
#define SINGLE_PI_CONST         3.14
#define HALF_PI_CONST            1.57
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct 
{
    uint16_t aux_ch0;
    uint16_t aux_ch1;
    uint16_t aux_ch2;
    uint16_t aux_ch3;
    
} c3dhall6_aux_ch_t;

typedef struct 
{
    float aux_float_ch0;
    float aux_float_ch1;
    float aux_float_ch2;
    float aux_float_ch3;
    
} c3dhall6_aux_float_ch_t ;

typedef struct 
{
   float aux_ref_adc_ch0;
   float aux_ref_adc_ch1;
   float aux_ref_adc_ch2;
   float aux_ref_adc_ch3;
   float aux_ref_volt;
   
} c3dhall6_aux_ref_t ;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;
    
    c3dhall6_aux_ref_t device_aux_ref;
    c3dhall6_aux_ch_t device_aux_ch;
    c3dhall6_aux_float_ch_t device_float_ch;

} c3dhall6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // static variable 
    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;
    
    c3dhall6_aux_ref_t  dev_aux_ref;

} c3dhall6_cfg_t;

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
void c3dhall6_cfg_setup ( c3dhall6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t c3dhall6_init ( c3dhall6_t *ctx, c3dhall6_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @details This function executes default configuration for 3D Hall 6 click.
 */
void c3dhall6_default_cfg ( c3dhall6_t *ctx );

/**
 * @brief Setting reference values function.
 *
 * @param ctx           Click object.
 * @param ref_val       Reference voltage in Volts or miliVolts ( measure this voltage between GND and 3V3 pin ).
 *                      Reference adc value from channel 0 - perform adc measurement on channel 0 with no permanent magnet.
 *                      Reference adc value from channel 1 - perform adc measurement on channel 1 with no permanent magnet.
 *                      Reference adc value from channel 2 - perform adc measurement on channel 2 with no permanent magnet.
 *                      Reference adc value from channel 3 - perform adc measurement on channel 3 with no permanent magnet.
 *
 * @details This function sets reference values for voltage and angle calculations.
 */
void c3dhall6_set_reference_values ( c3dhall6_t *ctx, c3dhall6_aux_ref_t ref_val );

/**
 * @brief Getting ADC value on each channel function.
 *
 * @param ctx          Click object.
 * @param channel_no   Channel number (channels: CH0, CH1, CH2, CH3).
 * @param adc_value    ADC value on selected channel.
 *
 * @details This function reads ADC value on selected channel.
 */
void c3dhall6_get_adc_value ( c3dhall6_t *ctx, uint8_t channel_no, uint16_t *adc_value );

/**
 * @brief Getting voltage on each channel function.
 *
 * @param ctx                Click object.
 * @param channel_no         Channel number (channels: CH0, CH1, CH2, CH3).
 * @param channel_voltage    voltage value on selected channel.
 *
 * @details This function reads ADC value on selected channel and converts that value to Volts or miliVolts - depending on reference voltage setting.
 */
void c3dhall6_get_volt( c3dhall6_t *ctx, uint8_t channel_no, float *channel_voltage );

/**
 * @brief GGetting angle value function.
 *
 * @param ctx                Click object.
 * @param die                Device uses two dies for measurement (dies: die A, die B).
 * @param angle_value        Calculated angle value (range: from -180 to 180 degrees).
 *
 * @details This function reads ADC values for selected die and calculates angle value in degrees.
 */
void c3dhall6_get_angle_deg ( c3dhall6_t *ctx, uint8_t die, float *angle_value );

/**
 * @brief GGetting angle value function.
 *
 * @param ctx                Click object.
 * @param die                Device uses two dies for measurement (dies: die A, die B).
 * @param angle_value        Calculated angle value (range: from -1 to 1 pi radians).
 *
 * @details This function reads ADC values for selected die and calculates angle value in radians.
 */
void c3dhall6_get_angle_rad ( c3dhall6_t *ctx, uint8_t die, float *angle_value );

#ifdef __cplusplus
}
#endif
#endif  // _C3DHALL6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
