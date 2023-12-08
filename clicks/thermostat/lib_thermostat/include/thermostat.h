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
 * \brief This file contains API for Thermostat Click driver.
 *
 * \addtogroup thermostat Thermostat Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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
#define THERMOSTAT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.te = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMOSTAT_RETVAL  uint8_t

#define THERMOSTAT_OK           0x00
#define THERMOSTAT_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_address I2C Address
 * \{
 */
#define THERMOSTAT_I2C_ADDRESS_0                                 0x48
#define THERMOSTAT_I2C_ADDRESS_1                                 0x49
#define THERMOSTAT_I2C_ADDRESS_2                                 0x4A
#define THERMOSTAT_I2C_ADDRESS_3                                 0x4B
/** \} */

/**
 * \defgroup register_address Register Address
 * \{
 */
#define THERMOSTAT_REG_TEMP_OUT                                  0x00
#define THERMOSTAT_REG_CONFIG                                    0x01
#define THERMOSTAT_REG_TEMP_HYST                                 0x02
#define THERMOSTAT_REG_TEMP_REF                                  0x03

#define THERMOSTAT_CHECK_SIGN                                    0x80
#define THERMOSTAT_DEFAULT_CONFIG                                0x0000
#define THERMOSTAT_MSB_BITS                                      0xFF00
#define THERMOSTAT_LSB_BITS                                      0x00FF
#define THERMOSTAT_START_RESULT                                  0x0000

#define THERMOSTAT_UPPER_LIMITS_TEMP                             126.00
#define THERMOSTAT_LOWER_LIMITS_TEMP                             -55.00
#define THERMOSTAT_CALCULATE_COEF_MULT                           1.8000
#define THERMOSTAT_CALCULATE_COEF_PLUS                           32.000
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
 
    digital_out_t rst;
    digital_out_t te;
  
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} thermostat_t;

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
    pin_name_t te;
  
    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} thermostat_cfg_t;

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
void thermostat_cfg_setup ( thermostat_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMOSTAT_RETVAL thermostat_init ( thermostat_t *ctx, thermostat_cfg_t *cfg );

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
void thermostat_generic_write ( thermostat_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf.
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void thermostat_generic_read ( thermostat_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic write 16-bit data function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param write_data   Data for write.
 *
 * @description This function generic write 16-bit data.
 */
void thermostat_write_data( thermostat_t *ctx, uint8_t reg_address, uint16_t write_data );

/**
 * @brief Generic read 16-bit data function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function generic read 16-bit data.
 */
 uint16_t thermostat_read_data( thermostat_t *ctx, uint8_t reg_address );

/**
 * @brief Get temperature in degrees Celsius.
 *
 * @param ctx          Click object.
 *
 * @description This function get temperature in degrees Celsius.
 */
float thermostat_get_temperature( thermostat_t *ctx );

/**
 * @brief Convert temperature in degrees Celsius to Fahrenheit.
 *
 * @param ctx          Click object.
 * @param temp_celsius Temperature in celsius.
 *
 * @description This function convert temperature in degrees Celsius to Fahrenheit.
 */
float thermostat_convert_fahrenheit( thermostat_t *ctx, float temp_celsius );

/**
 * @brief  Set configuration function.
 *
 * @param ctx          Click object.
 * @param config_value Configuration value.
 *
 * @description This function set configuration value.
 */
 void thermostat_set_configuration( thermostat_t *ctx, uint16_t config_value );

/**
 * @brief Set temperature hysterezis function
 *
 * @param ctx          Click object.
 * @param temp_hyst    Temperature hysterezis.
 *
 * @description This function set temperature hysterezis.
 */
 void thermostat_set_temp_hyst( thermostat_t *ctx, int8_t temp_hyst );

/**
 * @brief Set referent temperature function.
 *
 * @param ctx          Click object.
 * @param temp_ref     Referent temperature.
 *
 * @description This function set referent temperature.
 */
void thermostat_set_temp_ref( thermostat_t *ctx, int8_t temp_ref );

/**
 * @brief Soft reset function.
 *
 * @param ctx          Click object.
 *
 * @description This function enables soft reset.
 */
void thermostat_soft_reset( thermostat_t *ctx );

/**
 * @brief Set on thermal switch function
 * 
 * @param ctx          Click object.
 *
 * @description This function set on thermal switch.
 */
void thermostat_switch_on( thermostat_t *ctx );

/**
 * @brief Set off thermal switch function
 * 
 * @param ctx          Click object.
 *
 * @description This function set off thermal switch.
 */
void thermostat_switch_off( thermostat_t *ctx );

/**
 * @brief Thermostat enabled function.
 * 
 * @param ctx          Click object.
 *
 * @description This function enables thermostat.
 */
void thermostat_enable( thermostat_t *ctx );

/**
 * @brief Thermostat disabled function.
 * 
 * @param ctx          Click object.
 *
 * @description This function disabled thermostat
 */
void thermostat_disable( thermostat_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _THERMOSTAT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
