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
 * \brief This file contains API for HZ to V Click driver.
 *
 * \addtogroup hztov HZ to V Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HZTOV_H
#define HZTOV_H

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
#include "drv_pwm.h"
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
#define HZTOV_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.vo = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HZTOV_RETVAL  uint8_t

#define HZTOV_OK           0x00
#define HZTOV_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define HZTOV_DEF_FREQ     5000
/** \} */

/**
 * \defgroup enable_disable Enable/Disable flags
 * \{
 */
#define HZTOV_ENABLE        1
#define HZTOV_DISABLE       0

/** \} */

/**
 * \defgroup freq_range MAX and MIN input frequency values
 * \{
 */
#define HZTOV_MAX_FREQ      10000
#define HZTOV_MIN_FREQ      1000

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
typedef uint16_t hztov_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t en;
    
    // Modules 

    pwm_t pwm;
    analog_in_t adc;

    // ctx variable 
    
    uint32_t pwm_freq;
    
} hztov_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t pwm;
    pin_name_t vo;
    
    // Additional gpio pins 

    pin_name_t en;

    // static variable 

    analog_in_resolution_t  resolution;   // Resolution
    float vref;                           // VRef 
    uint32_t dev_pwm_freq;
} hztov_cfg_t;

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
void hztov_cfg_setup ( hztov_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param hztov Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HZTOV_RETVAL hztov_init ( hztov_t *ctx, hztov_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx        Click object.
 * @return ADC data
 *
 * @description This function reads ADC data.
 */
hztov_data_t hztov_generic_read ( hztov_t *ctx );

/**
 * @brief Read voltage function.
 *
 * @param ctx        Click object.
 * @return Voltage
 *
 * @description This function reads ADC data and converts it to voltage.
 */
float hztov_read_voltage ( hztov_t *ctx );

/**
 * @brief Set enable pin state.
 *
 * @param ctx          Click object.
 * @param state        Enable/Disable state.
 *
 * @description This function sets the state of EN pin.
 */
void hztov_set_enable ( hztov_t *ctx, uint8_t state );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void hztov_set_duty_cycle ( hztov_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void hztov_pwm_stop ( hztov_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void hztov_pwm_start ( hztov_t *ctx );

/**
 * @brief Changing the output voltage function.
 *
 * @param ctx           Click object.
 * @param freq          Input frequency in Hz, ranges from 1000 to 10000 Hz 
 *
 * @description This function sets the PWM frequency to required value, changing the output voltage.
 */
void hztov_set_input_frequency ( hztov_t *ctx, uint16_t freq );

#ifdef __cplusplus
}
#endif
#endif  // _HZTOV_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
