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
 * \brief This file contains API for Thermo 15 Click driver.
 *
 * \addtogroup thermo15 Thermo 15 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO15_H
#define THERMO15_H

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
#define THERMO15_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.alt = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO15_RETVAL  uint8_t

#define THERMO15_OK           0x00
#define THERMO15_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_adderss Device slave address
 * \{
 */
#define THERMO15_DEVICE_SLAVE_ADDR_000 0x48
#define THERMO15_DEVICE_SLAVE_ADDR_001 0x49
#define THERMO15_DEVICE_SLAVE_ADDR_010 0x4A
#define THERMO15_DEVICE_SLAVE_ADDR_011 0x4B
#define THERMO15_DEVICE_SLAVE_ADDR_100 0x4C
#define THERMO15_DEVICE_SLAVE_ADDR_101 0x4D
#define THERMO15_DEVICE_SLAVE_ADDR_110 0x4E
#define THERMO15_DEVICE_SLAVE_ADDR_111 0x4F
/** \} */

/**
 * \defgroup register Registers
 * \{
 */
#define THERMO15_REG_STORED_TEMPERATURE     0x00
#define THERMO15_REG_CONFIGURATION          0x01
#define THERMO15_REG_TEMPERATURE_HYSTERESIS 0x02
#define THERMO15_REG_TEMPERATURE_LIMIT      0x03
#define THERMO15_REG_ONE_SHOT               0x04
/** \} */

/**
 * \defgroup def_val Default value in the register
 * \{
 */
#define THERMO15_DEF_TEMP_HYSTERESIS 75
#define THERMO15_DEF_TEMP_LIMIT      80
#define THERMO15_REG_ONE_SHOT               0x04
/** \} */

/**
 * \defgroup config Configuration
 * \{
 */
#define THERMO15_CFG_WMODE_NORMAL      0x00
#define THERMO15_CFG_WMODE_ONE_SHOT    0x20
#define THERMO15_CFG_WMODE_SHUTDOWN    0x01
#define THERMO15_CFG_FAULT_QUEUE_1     0x00
#define THERMO15_CFG_FAULT_QUEUE_2     0x08
#define THERMO15_CFG_FAULT_QUEUE_4     0x10
#define THERMO15_CFG_FAULT_QUEUE_6     0x18
#define THERMO15_CFG_ALERT_ACTIVE_LOW  0x00
#define THERMO15_CFG_ALERT_ACTIVE_HIGH 0x04
#define THERMO15_CFG_TMODE_COMPARATOR  0x00
#define THERMO15_CFG_TMODE_INTERRUPT   0x02
/** \} */

/**
 * \defgroup temp_format Temperature format
 * \{
 */
#define THERMO15_TEMP_IN_CELSIUS    0x00
#define THERMO15_TEMP_IN_KELVIN     0x01
#define THERMO15_TEMP_IN_FAHRENHEIT 0x02
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
    digital_in_t alt;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t  slave_address;

} thermo15_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t alt;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} thermo15_cfg_t;

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
void thermo15_cfg_setup ( thermo15_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param thermo15 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMO15_RETVAL thermo15_init ( thermo15_t *ctx, thermo15_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Thermo_15 click.
 */
void thermo15_default_cfg ( thermo15_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buffer  Output data buffer
 * @param len          Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void thermo15_generic_write ( thermo15_t *ctx, uint8_t reg, uint8_t *data_buffer, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buffer  Data buffer to be written.
 * @param len          Number of the bytes in data buffer.
 *
 * @description This function reads data from the desired register.
 */
void thermo15_generic_read ( thermo15_t *ctx, uint8_t reg, uint8_t *data_buffer, uint8_t len );

/**
 * @brief Ambient temperature data
 *
 * @param ctx      Click object
 * @param temp_format       Temperature format ... (FAHRENHEIT, KELVIN or CELSIUS)
 * @return (float) Temperature data in the range from -55 C to +125 C
 */
float thermo15_get_temperature_data ( thermo15_t *ctx,  uint8_t temp_format );

/**
 * @brief Set temperature register
 *
 * @param ctx      Click object
 * @param temp_reg      Temperature register (_TEMPERATURE_HYSTERESIS or _TEMPERATURE_LIMIT)
 * @param temp_data     Temperature data in Celsius
 *
 * @note: This function converts the temperature data in degrees Celsius to the ADC value written in the registers.
 *        Use this function when you want to set one of these two registers
 *        Default register values are:
 *        Temperature Hysteresis is 75 C and Temperature limit is 80 C
 */
void thermo15_set_temp_register ( thermo15_t *ctx, uint8_t temp_reg, float temp_data );

/**
 * @brief Get temperature register
 *
 * @param ctx      Click object
 * @param temp_reg     Temperature register (_TEMPERATURE_HYSTERESIS or _TEMPERATURE_LIMIT)
 * @return Temperature data in Celsius
 *
 * @note: This function converts the ADC value into the temperature data in degrees Celsius that is read from the register.
 *        Use this function when you want to read one of these two registers
 *        Default register values are:
 *        Temperature Hysteresis is 75 C and Temperature limit is 80 C
 */
float thermo15_get_temp_register ( thermo15_t *ctx, uint8_t temp_reg );

/**
 * @brief Interrupt state
 *
 * @return Interrupt state on the INT pin
 */
uint8_t thermo15_get_interrupt_state ( thermo15_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO15_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
