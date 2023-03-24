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
 * \brief This file contains API for Light Temp Click driver.
 *
 * \addtogroup lighttemp Light Temp Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LIGHTTEMP_H
#define LIGHTTEMP_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_pwm.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define LIGHTTEMP_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.pwm1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.pwm2 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LIGHTTEMP_RETVAL  uint8_t

#define LIGHTTEMP_OK           0x00
#define LIGHTTEMP_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup default_freq Default frequency value
 * \{
 */
#define LIGHTTEMP_DEF_FREQ     20000
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

    i2c_master_t i2c;
    pwm_t pwm1;
    pwm_t pwm2;

    // ctx variable 

    uint8_t slave_address;
    uint32_t pwm_freq;
    
} lighttemp_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t pwm1;
    pin_name_t pwm2;

    // Additional gpio pins 

    pin_name_t int_pin;
    
    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    uint32_t dev_pwm_freq;

} lighttemp_cfg_t;

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
void lighttemp_cfg_setup ( lighttemp_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LIGHTTEMP_RETVAL lighttemp_init ( lighttemp_t *ctx, lighttemp_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void lighttemp_generic_write ( lighttemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void lighttemp_generic_read ( lighttemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get voltage
 *
 * @param ctx          Click object.
 *
 * @description This function get voltage.
 */
uint16_t lighttemp_get_pg_voltage ( lighttemp_t *ctx );

/**
 * @brief Get INT pin state
 *
 * 
 * @param ctx          Click object.
 *
 * @description This function get state of int_pin.
 */
uint8_t lighttemp_get_interrupt_state ( lighttemp_t *ctx );

/**
 * @brief Generic sets PWM duty cycle for LED1.
 *
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle for LED1.
 */
void lighttemp_led1_set_duty_cycle ( lighttemp_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module for LED1.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module for LED1.
 */
void lighttemp_led1_pwm_stop ( lighttemp_t *ctx );

/**
 * @brief Start PWM module for LED1.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module for LED1.
 */
void lighttemp_led1_pwm_start ( lighttemp_t *ctx );

/**
 * @brief Generic sets PWM duty cycle for LED2.
 *
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle for LED2.
 */
void lighttemp_led2_set_duty_cycle ( lighttemp_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module for LED2.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module for LED2.
 */
void lighttemp_led2_pwm_stop ( lighttemp_t *ctx );

/**
 * @brief Start PWM module for LED2.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module for LED2.
 */
void lighttemp_led2_pwm_start ( lighttemp_t *ctx );
#ifdef __cplusplus
}
#endif
#endif  // _LIGHTTEMP_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
