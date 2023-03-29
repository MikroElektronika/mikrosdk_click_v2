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
 * \brief This file contains API for Thermo 7 Click driver.
 *
 * \addtogroup thermo7 Thermo 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO7_H
#define THERMO7_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
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
#define THERMO7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO7_RETVAL  uint8_t

#define THERMO7_OK           0x00
#define THERMO7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define THERMO7_REG_AMBIENT_TEMPERATURE             0x00
#define THERMO7_REG_CONFIGURATION                   0x01
#define THERMO7_REG_HYSTERESIS_TEMPERATURE          0x02
#define THERMO7_REG_TEMPERATURE_LIMIT_SET           0x03
/** \} */   

/**
 * \defgroup config_register Config Register
 * \{
 */
#define THERMO7_CONFIG_ONE_SHOT_ENABLE             (0x01 << 7)
#define THERMO7_CONFIG_ONE_SHOT_DISABLE            (0x00 << 7)
#define THERMO7_CONFIG_ADC_RESOLUTION_9bit         (0x00 << 5)
#define THERMO7_CONFIG_ADC_RESOLUTION_10bit        (0x01 << 5)
#define THERMO7_CONFIG_ADC_RESOLUTION_11bit        (0x02 << 5)
#define THERMO7_CONFIG_ADC_RESOLUTION_12bit        (0x03 << 5)
#define THERMO7_CONFIG_FAULT_QUEUE_MODE_1          (0x00 << 3)
#define THERMO7_CONFIG_FAULT_QUEUE_MODE_2          (0x01 << 3)
#define THERMO7_CONFIG_FAULT_QUEUE_MODE_4          (0x02 << 3)
#define THERMO7_CONFIG_FAULT_QUEUE_MODE_6          (0x03 << 3)
#define THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_HIGH  (0x01 << 2)
#define THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_LOW   (0x00 << 2)
#define THERMO7_CONFIG_COMPARATOR_MODE             (0x00 << 1)
#define THERMO7_CONFIG_INTERRUPT_MODE              (0x01 << 1)
#define THERMO7_CONFIG_SHUTDOWN_ENABLE              0x01
#define THERMO7_CONFIG_SHUTDOWN_DISABLE             0x00
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

    // ctx variable 

    uint8_t slave_address;

} thermo7_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} thermo7_cfg_t;

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
void thermo7_cfg_setup ( thermo7_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param thermo7 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMO7_RETVAL thermo7_init ( thermo7_t *ctx, thermo7_cfg_t *cfg );

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
void thermo7_generic_write ( thermo7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void thermo7_generic_read ( thermo7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for reads ambient temperature.
 *
 * @param ctx          Click object.
 *
 * @description Temperature register that contains 9-bit to 12-bit temperature data. 
 * ( 0.5�C to 0.0625�C resolutions, respectively )
 * The lower limit of reading the temperature is -55 �C and the upper limit is 125 �C.
 */
float thermo7_read_ambient_temperature ( thermo7_t *ctx );

/**
 * @brief Functions for configuration chip and measurement.
 *
 * @param ctx          Click object.
 * @param reg          Data which be written in configuration register.
 *
 * @description 
 *  Options for configuration:
 *      ONE-SHOT ( Enable or Disable ),
 *      ADC RESOLUTION ( 9bit - 0.5 C, 10bit - 0.25 C, 11bit - 0.125 C or 
12bit - 0.0625 C)
 *      FAULT QUEUE ( 1, 2, 4 or 6 )
 *      ALERT POLARITY ( Active HIGH or LOW )
 *      COMP/INT ( Interrupt mode or Comparator mode )
 *      SHUTDOWN ( Enable or Disable )
 *      
 * Power - up default:
 *      ONE-SHOT ( Disable ),
 *      ADC RESOLUTION ( 9bit - 0.5 �C )
 *      FAULT QUEUE ( 1 )
 *      ALERT POLARITY ( Active LOW )
 *      COMP/INT ( Comparator mode )
 *      SHUTDOWN ( Disable )
 */
void thermo7_set_configuration ( thermo7_t *ctx, uint8_t configuration );

/**
 * @brief Functions for reads Hysteresis Temperature.
 *
 * @param ctx          Click object.
 *
 * @description This fuction gets Hysteresis Temperature.
 */
int16_t thermo7_get_hysteresis_temperature ( thermo7_t *ctx );

/**
 * @brief Functions for settings Hysteresis Temperature.
 *
 * @param ctx          Click object.
 * @param temperature  Data which be written in Hysteresis register.
 *
 * @description This register is used to set a hysteresis for the Temperature set Limit. 
 * Therefore, the data represents a minimum temperature limit.
 * The power-up default value of THYST register is 75�C.
 */
void thermo7_set_hysteresis_temperature ( thermo7_t *ctx, int8_t temperature );

/**
 * @brief Functions for get Limit Temperature.
 *
 * @param ctx          Click object.
 *
 * @description This function gets limit temperature.
 */
int16_t thermo7_get_limit_temperature ( thermo7_t *ctx );

/**
 * @brief Functions for settings limit Temperature.
 *
 * @param ctx          Click object.
 *
 * @description This fuction sets limit temperature.
 */
void thermo7_set_limit_temperature ( thermo7_t *ctx, int16_t temperature );

/**
 * @brief Functions for reads state of interrupt pins.
 *
 * @param ctx          Click object.
 *
 * @description This fuction reads state of interrupt pins.
 */
uint8_t thermo7_get_interrupt ( thermo7_t *ctx );

/**
 * @brief  Functions for settings ADC resolution measurement.
 *
 * @param ctx          Click object.
 * @param resolution   Resolution which be written in configuration register.
 *
 * @description Options for configuration:
 *      ADC RESOLUTION:
 *         9bit - 0.5 C ( Power-up default ),
 *         10bit - 0.25 C,
 *         11bit - 0.125 C,
 *         12bit - 0.0625 C
 */
void thermo7_set_resolution ( thermo7_t *ctx, uint8_t resolution );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
