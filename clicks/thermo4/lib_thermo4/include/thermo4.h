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
 * \brief This file contains API for Thermo 4  Click driver.
 *
 * \addtogroup thermo4 Thermo 4  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO4_H
#define THERMO4_H

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
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define THERMO4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO4_RETVAL  uint8_t

#define THERMO4_OK           0x00
#define THERMO4_INIT_ERROR   0xFF
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

} thermo4_t;

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

} thermo4_cfg_t;

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
void thermo4_cfg_setup ( thermo4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
THERMO4_RETVAL thermo4_init ( thermo4_t *ctx, thermo4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Thermo4 Click.
 */
void thermo4_default_cfg ( thermo4_t *ctx );

/**
 * @brief Byte write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_in      Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void thermo4_write_byte ( thermo4_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Byte read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_out     Output data.
 *
 * @description This function reads data from the desired register.
 */
void thermo4_read_byte ( thermo4_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Data write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_in      Data to be written.
 *
 * @description This function writes data to the desired register.
 */
void thermo4_write_data ( thermo4_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief Data read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_out     Output data.
 *
 * @description This function reads data from the desired register.
 */
void thermo4_read_data ( thermo4_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief Write configuration function.
 * 
 * @param ctx          Click object.
 * @param wr_cfg       Configuration register.
 *
 * @description        Function reads 8-bit data from configuration register.
 */
void thermo4_write_cfg ( thermo4_t *ctx, uint8_t wr_cfg );

/**
 * @brief Read configuration function
 *
 * @param ctx         Click object.
 *
 * @returns result 8-bit content of configuration register
 *
 * @description Function reads 8-bit data from configuration register.
**/
uint8_t thermo4_read_cfg ( thermo4_t *ctx );

/**
 * @brief Read configuration function.
 * 
 * @param ctx          Click object.
 *
 * @description Function sets B0 of the configuration register to 1 in order to shut the sensor down.
 */
void thermo4_shut_down ( thermo4_t *ctx );

/**
 * @brief Power up function
 *
 * @param ctx         Click object.
 *
 * @description Function sets B0 of the configuration register to 0 in order to shut the sensor down.
**/
void thermo4_power_up ( thermo4_t *ctx );

/**
 * @brief Reset function
 *
 * @param ctx         Click object.
 *
 * @description Function is used to reset sensor.
**/
void thermo4_reset ( thermo4_t *ctx );

/**
 * @brief Read Temperature in Celsius function
 *
 * @param ctx         Click object.
 *
 * @returns float result value representing current temperature in degrees centigrade
 *
 * @description Function reads sensor and performs calculations in order to return result value representing current temperature in degrees centigrade.
**/
float thermo4_read_temperature_c ( thermo4_t *ctx );

/**
 * @brief Read Temperature in Fahrenheit function
 *
 * @param ctx         Click object.
 *
 * @returns float result value representing current temperature in degrees fahrenheit
 *
 * @description Function reads sensor and performs calculations in order to return result value representing current temperature in degrees fahrenheit.
**/
float thermo4_read_temperature_f ( thermo4_t *ctx );

/**
 * @brief Read Temperature in Kelvin function
 *
 * @param ctx         Click object.
 *
 * @returns float result value representing current temperature in degrees kelvin
 *
 * @description Function reads sensor and performs calculations in order to return result value representing current temperature in degrees kelvin.
**/
float thermo4_read_temperature_k ( thermo4_t *ctx );

/**
 * @brief Read overtemperature shutdown threshold function
 *
 * @param ctx         Click object.
 *
 * @returns float result value representing current overtemperature shutdown threshold
 *
 * @description Function reads current overtemperature shutdown threshold.
 * @note Default value is 80�C.
**/
float thermo4_read_over_temp_shut_down ( thermo4_t *ctx );

/**
 * @brief Read hysteresis function
 *
 * @param ctx       Click object.
 *
 * @returns float result value representing current hysteresis
 *
 * @note Default value is 75�C.
**/
float thermo4_read_temp_hyst ( thermo4_t *ctx );

/**
 * @brief Write overtemperature shutdown threshold function
 *
 * @param ctx       Click objeact.
 * @param input_val  user defined float value representing new shutdown threshold
 *
 * @description Function sets new shutdown threshold value.
 * @note Default value is 80�C.
**/
void thermo4_write_over_temp_shut_down ( thermo4_t *ctx, float input_val );

/**
 * @brief Write hysteresis function
 *
 * @param ctx         Click object.
 * @param input_val  user defined float value representing new hysteresis
 *
 * @description Function sets new hysteresis value.
**/
void thermo4_write_temp_hyst( thermo4_t *ctx, float input_val );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO4_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
