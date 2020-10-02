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
 * \brief This file contains API for Temp Hum Click driver.
 *
 * \addtogroup temphum Temp Hum Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHIM_H
#define TEMPHIM_H

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
#define TEMPHIM_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPHIM_RETVAL  uint8_t

#define TEMPHIM_OK           0x00
#define TEMPHIM_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_addr Slave Address
 * \{
 */
#define TEMPANDHUM_I2C_ADDRESS                                      0x5F
/** \} */

/**
 * \defgroup register_addresses Register Addresses
 * \{
 */
#define TEMPANDHUM_WHO_AM_I                                         0x0F
#define TEMPANDHUM_AV_CONF                                          0x10
#define TEMPANDHUM_CTRL_REG1                                        0x20
#define TEMPANDHUM_CTRL_REG2                                        0x21
#define TEMPANDHUM_CTRL_REG3                                        0x22
#define TEMPANDHUM_STATUS_REG                                       0x27
#define TEMPANDHUM_HUMIDITY_OUT_L                                   0x28
#define TEMPANDHUM_HUMIDITY_OUT_H                                   0x29
#define TEMPANDHUM_TEMP_OUT_L                                       0x2A
#define TEMPANDHUM_TEMP_OUT_H                                       0x2B
#define TEMPANDHUM_H0_RH_X2                                         0x30
#define TEMPANDHUM_H1_RH_X2                                         0x31
#define TEMPANDHUM_T0_DEGC_X8                                       0x32
#define TEMPANDHUM_T1_DEGC_X8                                       0x33
#define TEMPANDHUM_T1_T0_MSB                                        0x35
#define TEMPANDHUM_H0_T0_OUT_L                                      0x36
#define TEMPANDHUM_H0_T0_OUT_H                                      0x37
#define TEMPANDHUM_H1_T0_OUT_L                                      0x3A
#define TEMPANDHUM_H1_T0_OUT_H                                      0x3B
#define TEMPANDHUM_T0_OUT_L                                         0x3C
#define TEMPANDHUM_T0_OUT_H                                         0x3D
#define TEMPANDHUM_T1_OUT_L                                         0x3E
#define TEMPANDHUM_T1_OUT_H                                         0x3F
/** \} */

/**
 * \defgroup default_value Default Value
 * \{
 */
#define TEMPANDHUM_AV_CONF_DEFAULT_VALUE                            0x1B
#define TEMPANDHUM_CTRL_REG1_DEFAULT_VALUE                          0x85
#define TEMPANDHUM_CTRL_REG2_DEFAULT_VALUE                          0x00
#define TEMPANDHUM_CTRL_REG3_DEFAULT_VALUE                          0x00
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

    float float_h_out;
    float float_t_out;
    uint8_t h0_rh_x2;
    uint8_t h1_rh_x2;
    uint8_t t0_deg_c_x8;
    uint8_t t1_deg_c_x8;
    int16_t h0_t0_out;
    int16_t h1_t0_out;
    int16_t t0_out;
    int16_t t1_out;
    float t0_deg_c_cal;
    float t1_deg_c_cal;
    float h0_rh_cal;
    float h1_rh_cal;

} temphum_t;

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

} temphum_cfg_t;

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
void temphum_cfg_setup ( temphum_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHIM_RETVAL temphum_init ( temphum_t *ctx, temphum_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for TempHum click.
 */
void temphum_default_cfg ( temphum_t *ctx );

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
void temphum_generic_write ( temphum_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void temphum_generic_read ( temphum_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Gets humidity data function
 *
 * @param ctx          Click object.
 * 
 * @return 16-bit humidity data
 *
 * @description Function get humidity data by reading from two
 * target 8-bit register address of HTS221 sensor on Temp&Hum Click.
 */
uint16_t temphum_get_hum_data ( temphum_t *ctx );

/**
 * @brief Gets temperature data function
 *
 * @param ctx          Click object.
 * 
 * @return 16-bit temperature data
 *
 * @description Function gets temperature data by reading from two
 * target 8-bit register address of HTS221 sensor on Temp&Hum Click.
 */
uint16_t temphum_get_temp_data( temphum_t *ctx );

/**
 * @brief Gets temperature and humidity function
 *
 * @param temperature              pointer to float value of temperature [ �C ]
 *
 * @param humidity                 pointer to float value of humidity [ % ]
 *
 * @description Function gets temperature value in degrees Celsius [ �C ]
 * and humidity value in percentage [ % ] by reading from the
 * two target 8-bit register address of HTS221 sensor on Temp&Hum Click
 * and converts it by performing linear interpolation on read data.
 */
void temphum_get_temp_hum ( temphum_t *ctx, float *temperature, float *humidity );

/**
 * @brief Gets temperature in degrees Celsius function
 *
 * @param ctx          Click object.
 * 
 * @return float value of temperature in degrees Celsius
 *
 * @description Function get temperature value in degrees Celsius [ �C ]
 * from HTS221 sensor on Temp&Hum Click.
 */
float temphum_get_temperature( temphum_t *ctx );

/**
 * @brief Gets humidity in degrees Celsius function
 *
 * @param ctx          Click object.
 * 
 * @return float value of humidity in percentage
 *
 * @description Function get humidity value in percentage [ % ]
 * from HTS221 sensor on Temp&Hum Click.
 */
float temphum_get_humidity( temphum_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPHIM_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
