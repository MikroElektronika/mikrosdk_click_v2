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
 * \brief This file contains API for heater  Click driver.
 *
 * \addtogroup heater heater  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HEATER_H
#define HEATER_H

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
#define HEATER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg1.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )
  
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HEATER_RETVAL  uint8_t

#define HEATER_OK                      0x00
#define HEATER_INIT_ERROR              0xFF
/** \} */

/**
 * \defgroup hts_slv_addr Heater Slave address
 * \{
 */
#define HEATER_SLAVE_ADDRESS               0x4D    
/** \} */

/**
 * \defgroup led_status Led status
 * \{
 */
#define  HEATER_LED_ON                             1
#define  HEATER_LED_OFF                            0
/** \} */

/**
 * \defgroup heater_resolution Heater resolution
 */
#define HEATER_SHIFT_DATA                       8 
#define HEATER_ADC_VREF                         3300.00f
#define HEATER_MV_RESOLUTION                    4096.00f
#define HEATER_TEMP_RESOLUTION                  10.0f
#define HEATER_TEMP_0                           500.0
/** \} */

#define HEATER_DEF_FREQ                         500

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

    digital_out_t rst;
    digital_out_t cs;
    
    // Modules 

    i2c_master_t i2c;
    pwm_t pwm;

    // ctx variable 

    uint8_t slave_address;
    uint32_t pwm_freq;

} heater_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
  
    // Additional gpio pins 
   
    pin_name_t rst;
    pin_name_t cs;
  
    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;
    
} heater_cfg_t;

typedef struct
{
    pin_name_t pwm;
    
    uint32_t dev_pwm_freq;
    
} heater_config_t;

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
void heater_cfg_setup ( heater_cfg_t *cfg, heater_config_t  *cfg1);

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HEATER_RETVAL heater_init ( heater_t *ctx, heater_cfg_t *cfg, heater_config_t *cfg1  );

/**
 * @brief Sets state of the rst pin
 * 
 * @param ctx          Click object.
 * 
 * @param status  status of the led
 */
void heater_set_led1_status ( heater_t *ctx, uint8_t status );

/**
 * @brief Sets state of the cs pin
 * 
 * @param ctx          Click object.
 * 
 * @param status status of the led
 */
void heater_set_led2_status ( heater_t *ctx, uint8_t status );

/**
 * @brief Generic function for reading data from device
 * 
 * @param ctx          Click object.
 * 
 * @return Raw adc data
 */
uint16_t heater_read_data ( heater_t *ctx );

/**
 * @brief Function reads data from device and converts it to mV value
 * 
 * @param ctx          Click object.
 * 
 * @return Read data in mV
 */
float heater_read_mv ( heater_t *ctx );

/**
 * @brief Function reads data and converts it to temperature data in degree C
 * 
 * @param ctx          Click object.
 * 
 * @return Read data in degree C
 */
float heater_read_temp ( heater_t *ctx );

/**
 * @brief Generic sets PWM duty cycle.
 *
 * 
 * @param ctx          Click object.
 * @param duty_cycle   Duty cycle.
 *
 * @description This function sets the PWM duty cycle.
 */
void heater_set_duty_cycle ( heater_t *ctx, float duty_cycle );

/**
 * @brief Stop PWM module.
 *
 * @param ctx Click object.
 *
 * @description This function stops PWM module.
 */
void heater_pwm_stop ( heater_t *ctx );

/**
 * @brief Start PWM module.
 *
 * @param ctx  Click object.
 *
 * @description This function starts PWM module.
 */
void heater_pwm_start ( heater_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _HEATER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
