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
 * \brief This file contains API for Altitude 3 Click driver.
 *
 * \addtogroup altitude3 Altitude 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ALTITUDE3_H
#define ALTITUDE3_H

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

#include "math.h"
#include "string.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define ALTITUDE3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ALTITUDE3_RETVAL  uint8_t

#define ALTITUDE3_OK           0x00
#define ALTITUDE3_INIT_ERROR   0xFF
/** \} */

#define ALTITUDE3_SLAVE_ADDR                         0x63

#define ALTITUDE3_LOW_POWER_T_FIRST                  0x609C
#define ALTITUDE3_LOW_POWER_P_FIRST                  0x401A
#define ALTITUDE3_NORMAL_T_FIRST                     0x6825
#define ALTITUDE3_NORMAL_P_FIRST                     0x48A3
#define ALTITUDE3_LOW_NOISE_T_FIRST                  0x70DF
#define ALTITUDE3_LOW_NOISE_P_FIRST                  0x5059
#define ALTITUDE3_ULTRA_LOW_NOISE_T_FIRST            0x7866
#define ALTITUDE3_ULTRA_LOW_NOISE_P_FIRST            0x58E0

#define ALTITUDE3_OK                                 0x00
#define ALTITUDE3_T_FIRST_ORDER                      0x01
#define ALTITUDE3_P_FIRST_ORDER                      0x02
#define ALTITUDE3_INITIALIZED                        0x03
#define ALTITUDE3_ERROR                              0xFF

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct 
{
  
  uint32_t  min_delay_us;
  uint16_t  sensor_const[ 4 ];
  uint32_t  p_pa_calib[ 3 ];
  float     lut_lower;
  float     lut_upper;
  double    quadr_factor;
  uint16_t  offst_factor;

} altitude3_param_t;

typedef struct
{
  //Sensor data

  int8_t temperature; 
  uint32_t pressure; 
  int16_t altitude;

} sensor_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    uint8_t update_check;

    sensor_data_t sens_data;

} altitude3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

    uint8_t update_check_cfg;

} altitude3_cfg_t;

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
void altitude3_cfg_setup ( altitude3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ALTITUDE3_RETVAL altitude3_init ( altitude3_t *ctx, altitude3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Altitude3 click.
 */
void altitude3_default_cfg ( altitude3_t *ctx );

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
void altitude3_generic_write ( altitude3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void altitude3_generic_read ( altitude3_t *ctx, uint8_t *reg_buf, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set Measurement Mode function
 *
 * @param ctx          Click object.
 * @param modeCmd      Command which selects a measurement mode
 *
 * @returns 0x01 - Temperature goes first, 0x02 - Pressure goes first, 0xFF - Command Error
 *
 * @description Function sends a command which selects a measurement mode and data reading order.
 */
uint8_t altitude3_measurement_mode ( altitude3_t *ctx, uint16_t mode_cmd );

/**
 * @brief Software Reset function
 *
 * @param ctx          Click object.
 * 
 * @description Function sends a command to perform a SW Reset of the device.
 * @note This command triggers the sensor to reset all internal state machines and reload calibration data from the memory.
 */
void altitude3_soft_reset ( altitude3_t *ctx );

/**
 * @brief Read AD Conversion function
 *
 * @param ctx           Click object.
 * @param read_order    Determines in which order data be read
 * @param temperature   Memory where temperature converted data be stored
 * @param pressure      Memory where pressure converted data be stored
 *
 * @returns 0x00 - OK, 0xFF - Data Order Error
 *
 * @description Function reads results of AD conversion, which consists of the 16bit temperature and 24bit pressure data in determined order.
 */
uint8_t altitude3_read_adc_results ( altitude3_t *ctx, uint8_t read_order, int16_t *temperature, uint32_t *pressure );

/**
 * @brief Init configuration function
 *
 * @param s  Object where initialization data and data from OTP sensor be stored
 *
 * @description Function sends a command to read calibration data from OTP sensor and other initialization data, which is necessary for calculations.
 * @note The reading from OTP sensor should be performed after power up or after SW reset.
 */
void altitude3_init_cfg( altitude3_t *ctx, altitude3_param_t *s );

/**
 * @brief Get Data function
 *
 * @param read_order    Determines in which order data be read
 * @param temperature   Memory where temperature data calculated to Celsius degrees be stored
 * @param pressure      Memory where pressure data calculated to mbar[hPa] be stored
 * @param altitude      Memory where altitude data calculated to meters be stored
 *
 * @returns 0x00 - OK, 0x03 - Calibration Done, 0xFF - Data Order Error
 *
 * @description Function performs a calibration data reading, only once, and then reads a temperature and pressure data and calculates these values
 * to standard units. Also calculates the altitude depending on the temperature and pressure data.
 */
uint8_t altitude3_get_data ( altitude3_t *ctx, uint8_t read_order );

#ifdef __cplusplus
}
#endif
#endif  // _ALTITUDE3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
