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
 * \brief This file contains API for 6DOF IMU 7 Click driver.
 *
 * \addtogroup c6dofimu7 6DOF IMU 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU7_H
#define C6DOFIMU7_H

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
#define C6DOFIMU7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int1 = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU7_RETVAL  uint8_t

#define C6DOFIMU7_OK           0x00
#define C6DOFIMU7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup configuration_registers Configuration Registers
 * \{
 */
#define C6DOFIMU7_SLAVE_ADDRESS     0x68
#define C6DOFIMU7_PWR_MGMT          0x06
#define C6DOFIMU7_PWM_MGMT_L        0x80
#define C6DOFIMU7_PWM_MGMT_H        0x01
#define C6DOFIMU7_TEMP_OUT_H        0x39
#define C6DOFIMU7_ACCEL_XOUT_H      0x2D
#define C6DOFIMU7_ACCEL_YOUT_H      0x2F
#define C6DOFIMU7_ACCEL_ZOUT_H      0x31
#define C6DOFIMU7_GYRO_XOUT_H       0x33
#define C6DOFIMU7_GYRO_YOUT_H       0x35
#define C6DOFIMU7_GYRO_ZOUT_H       0x37
/** \} */

/**
 * \defgroup conversion_constants Conversion Constants
 * \{
 */
#define C6DOFIMU7_TEMPERATURE_SENSITIVITY    333.87
#define C6DOFIMU7_TEMPERATURE_OFFSET         6.3
#define C6DOFIMU7_ACCEL_SENSITIVITY          8.192
#define C6DOFIMU7_GYRO_SENSITIVITY           65.5
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Sensor axis structure.
 */
typedef struct 
{
    float x_axis;
    float y_axis;
    float z_axis;
  
} c6dofimu7_axis_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 

    digital_in_t int2;
    digital_in_t int1;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} c6dofimu7_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t int2;
    pin_name_t int1;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} c6dofimu7_cfg_t;

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
void c6dofimu7_cfg_setup ( c6dofimu7_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C6DOFIMU7_RETVAL c6dofimu7_init ( c6dofimu7_t *ctx, c6dofimu7_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 6DofImu7 click.
 */
void c6dofimu7_default_cfg ( c6dofimu7_t *ctx );

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
void c6dofimu7_generic_write ( c6dofimu7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void c6dofimu7_generic_read ( c6dofimu7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read word function.
 *
 * @param ctx          Click object.
 * @param address      Register address.
 *
 * @description This function reads 2 bytes of data from the specified address.
 */
int16_t c6dofimu7_read_word ( c6dofimu7_t *ctx, uint8_t address );

/**
 * @brief Get temperature data function.
 *
 * @param ctx                  Click object.
 * @param temp_sensitivity     Temperature sensitivity value.
 * @param temp_offset          Temperature offset value. 
 *
 * @description This function reads and returns temperature data.
 */
float c6dofimu7_get_temp_data ( c6dofimu7_t *ctx, float temp_sensitivity, float temp_offset );

/**
 * @brief Get accelerometer data function.
 *
 * @param ctx                  Click object.
 * @param accel                Accelerometer axis structure.
 * @param sensitivity          Accelerometer sensitivity value. 
 *
 * @description This function reads accelerometer axis data and configures the accel axis struct.
 */
void c6dofimu7_get_accel_data ( c6dofimu7_t *ctx, c6dofimu7_axis_t *accel, float sensitivity );

/**
 * @brief Get gyroscope data function.
 *
 * @param ctx                  Click object.
 * @param gyro                 Gyroscope axis structure.
 * @param sensitivity          Gyroscope sensitivity value. 
 *
 * @description This function reads gyroscope axis data and configures the gyro axis struct.
 */
void c6dofimu7_get_gyro_data ( c6dofimu7_t *ctx, c6dofimu7_axis_t *gyro, float sensitivity );

/**
 * @brief Get PWM input function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads input from the pwm pin.
 */
uint8_t c6dofimu7_get_pwm_input ( c6dofimu7_t *ctx );

/**
 * @brief Get INT input function.
 *
 * @param ctx          Click object.
 *
 * @description This function reads input from the int pin.
 */
uint8_t c6dofimu7_get_int_input ( c6dofimu7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
