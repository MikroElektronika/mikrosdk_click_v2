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
 * \brief This file contains API for Thermo 13 Click driver.
 *
 * \addtogroup thermo13 Thermo 13 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO13_H
#define THERMO13_H

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


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define THERMO13_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO13_RETVAL  uint8_t

#define THERMO13_OK           0x00
#define THERMO13_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address  Slave address
 * \{
 */
#define  THERMO13_DEVICE_SLAVE_ADDR_000   0x48 
#define  THERMO13_DEVICE_SLAVE_ADDR_001   0x49 
#define  THERMO13_DEVICE_SLAVE_ADDR_010   0x4A 
#define  THERMO13_DEVICE_SLAVE_ADDR_011   0x4B 
#define  THERMO13_DEVICE_SLAVE_ADDR_100   0x4C 
#define  THERMO13_DEVICE_SLAVE_ADDR_101   0x4D 
#define  THERMO13_DEVICE_SLAVE_ADDR_110   0x4E 
#define  THERMO13_DEVICE_SLAVE_ADDR_111   0x4F 
/** \} */

/**
 * \defgroup register  Register
 * \{
 */
#define  THERMO13_REG_TEMPERATURE              0x00 
#define  THERMO13_REG_CONFIGURATION            0x01 
#define  THERMO13_REG_TEMPERATURE_LIMIT_LOW    0x02 
#define  THERMO13_REG_TEMPERATURE_LIMIT_HIGH   0x03 
#define  THERMO13_REG_SOFTWARE_RESET           0x04 
/** \} */

/**
 * \defgroup Temperature_data  Temperature data
 * \{
 */
#define  THERMO13_TEMP_IN_CELSIUS      0x00 
#define  THERMO13_TEMP_IN_KELVIN       0x01 
#define  THERMO13_TEMP_IN_FAHRENHEIT   0x02 
/** \} */

/**
 * \defgroup default_register  Default register
 * \{
 */
#define  THERMO13_DEF_TEMP_LIMIT_LOW    75 
#define  THERMO13_DEF_TEMP_LIMIT_HIGH   80 
/** \} */

/**
 * \defgroup configurations  Configurations
 * \{
 */
#define  THERMO13_CFG_CONTINUOUS_MEASUREMENT    0x0000 
#define  THERMO13_CFG_SINGLE_MEASUREMENT        0x8000 
#define  THERMO13_CFG_INTERRUPT_IS_NOT_ACTIVE   0x0000 
#define  THERMO13_CFG_INTERRUPT_IS_ACTIVE       0x4000 
#define  THERMO13_CFG_FAULT_QUEUE_1             0x0000 
#define  THERMO13_CFG_FAULT_QUEUE_2             0x0800 
#define  THERMO13_CFG_FAULT_QUEUE_4             0x1000 
#define  THERMO13_CFG_FAULT_QUEUE_6             0x1800 
#define  THERMO13_CFG_ALERT_ACTIVE_LOW          0x0000 
#define  THERMO13_CFG_ALERT_ACTIVE_HIGH         0x0400 
#define  THERMO13_CFG_NO_SHUTDOWN               0x0000 
#define  THERMO13_CFG_SHUTDOWN_ACTIVE           0x0100 
#define  THERMO13_CFG_WAIT_TIME_X16             0x0000 
#define  THERMO13_CFG_WAIT_TIME_X4              0x0001 
#define  THERMO13_CFG_WAIT_TIME_X1              0x0002 
#define  THERMO13_CFG_WAIT_TIME_X0p5            0x0003 
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
typedef struct thermo13_s
{
    // Output pins 

    digital_out_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} thermo13_t;

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
    uint8_t  i2c_address;
    
    
} thermo13_cfg_t;

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
void thermo13_cfg_setup ( thermo13_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param thermo13 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
THERMO13_RETVAL thermo13_init ( thermo13_t *ctx, thermo13_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Thermo13 Click.
 */
void thermo13_default_cfg ( thermo13_t *ctx );

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
void thermo13_generic_write ( thermo13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read.
 *
 * @description This function reads data from the desired register.
 */
void thermo13_generic_read ( thermo13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Functions for read data from registers
 *
 * @param ctx            Click object.
 * @param reg_addr       Register address (LSB first read).
 * @return 16-bit data that is reads from the register.
 */
uint16_t thermo13_read_data (  thermo13_t *ctx, uint8_t reg_addr );

/**
 * @brief Configuration register
 *
 * @param ctx            Click object.
 * @param cfg_data       Configuration data.
 *
 * @note: Use this functions to write new data to the configuration register.
 */
void thermo13_configuration ( thermo13_t *ctx,uint16_t  cfg_data );

/**
 * @brief Ambient temperature data
 *
 * @param ctx           Click object.
 * @param temp_in       Temperature in ... (FAHRENHEIT, KELVIN or CELSIUS)
 * @return Temperature data in the range from -40 C to +125 C
 */
float thermo13_get_ambient_temperature_data ( thermo13_t *ctx, uint8_t temp_in );

/**
 * @brief Set temperature limit register
 *
 * @param ctx           Click object.
 * @param temp_reg      Temperature register (TEMPERATURE_LIMIT_LOW or TEMPERATURE_LIMIT_HIGH)
 * @param temp          Temperature data in Celsius.
 *
 * @note: This function converts the temperature data in degrees Celsius to the ADC value written in the registers.
 *        Use this function when you want to set one of these two registers
 *        Default register values are:
 *        Temperature limit low is 75 C and Temperature limit high is 80 C
 */
void thermo13_set_temp_limit ( thermo13_t *ctx, uint8_t temp_reg, float temp );

/**
 * @brief Get temperature register
 *
 * @param ctx            Click object.
 * @param temp_reg       Temperature register (TEMPERATURE_LIMIT_LOW or TEMPERATURE_LIMIT_HIGH).
 * @return               Temperature data in Celsius.
 *
 * @note: This function converts the ADC value into the temperature data in degrees Celsius that is read from the register.
 *        Use this function when you want to read one of these two registers
 *        Default register values are:
 *        Temperature limit low is 75 C and Temperature limit high is 80 C
 */
float thermo13_get_temp_limit ( thermo13_t *ctx, uint8_t temp_reg );

/**
 * @brief Interrupt state
 *
 * @param ctx  Click object.
 * @return Interrupt state on the int_pin.
 */
uint8_t thermo13_get_interrupt_state( thermo13_t *ctx );

/**
 * @brief Software reset.
 */
void thermo13_software_reset ( thermo13_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // THERMO13_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
