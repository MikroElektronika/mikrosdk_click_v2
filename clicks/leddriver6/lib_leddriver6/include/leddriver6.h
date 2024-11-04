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
 * \brief This file contains API for LED driver 6 Click driver.
 *
 * \addtogroup leddriver6 LED driver 6 Click Driver
 * \{
 */
// ----------------------------------------------------------------------------

#ifndef LEDDRIVER6_H
#define LEDDRIVER6_H

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

#include "drv_digital_in.h"
#include "drv_pwm.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define LEDDRIVER6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pwm     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LEDDRIVER6_OK            0
#define LEDDRIVER6_INIT_ERROR  (-1)
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define LEDDRIVER6_DEF_FREQ  10000
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

    // Input pins 

    digital_in_t int_pin;

    // Modules 

    pwm_t        pwm;
    i2c_master_t i2c;

    // ctx variables 

    uint32_t pwm_freq;
    uint8_t  slave_address;

} leddriver6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t pwm;

    // Additional gpio pins 

    pin_name_t int_pin;

    // Static variables 

    uint32_t i2c_speed;
    uint8_t  i2c_address;
    uint32_t dev_pwm_freq;

} leddriver6_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void leddriver6_cfg_setup ( leddriver6_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx  Click object.
 * @param cfg  Click configuration structure.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
err_t leddriver6_init ( leddriver6_t *ctx, leddriver6_cfg_t *cfg );

/**
 * @brief Sets PWM duty cycle.
 *
 * @param ctx  Click object.
 * @param duty_cycle  Duty ratio.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function sets the PWM duty cycle.
 */
err_t leddriver6_set_duty_cycle ( leddriver6_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx  Click object.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function stops PWM module.
 */
err_t leddriver6_pwm_stop ( leddriver6_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function starts PWM module.
 */
err_t leddriver6_pwm_start ( leddriver6_t *ctx );

/**
 * @brief Read ADC function.
 *
 * @param ctx  Click object.
 * @param data_out  Output converted data [12-bit].
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function reads the ADC converted results of Power Good voltage level.
 */
err_t leddriver6_read_adc ( leddriver6_t *ctx, uint16_t *data_out );

/**
 * @brief Function for reading current PG output voltage.
 *
 * @param ctx  Click object.
 * @param data_out  Output voltage level [V].
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function gets and calculates the Power Good voltage level.
 */
err_t leddriver6_get_pg_voltage ( leddriver6_t *ctx, float *data_out );

/**
 * @brief Function for getting interrupt pin state.
 *
 * @param ctx  Click object.
 * @return  0 (low) - fault conditions report,
 *          1 (high) - no fault conditions.
 *
 * @description This function checks the state of interrupt (INT) pin.
 */
uint8_t leddriver6_get_interrupt_state ( leddriver6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // LEDDRIVER6_H

/** \} */ // End public_function group
/** \} */ // End Click Driver group

// ------------------------------------------------------------------------ END
