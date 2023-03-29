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
 * \brief This file contains API for Pressure 7 Click driver.
 *
 * \addtogroup pressure7 Pressure 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PRESSURE7_H
#define PRESSURE7_H

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
#define PRESSURE7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
   
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PRESSURE7_RETVAL  uint8_t

#define PRESSURE7_OK           0x00
#define PRESSURE7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup command_registers Command registers 
 * \{
 */
#define PRESSURE7_CMD_RESET                             0x1E
#define PRESSURE7_CMD_CONVERT_D1_OSR_256                0x40
#define PRESSURE7_CMD_CONVERT_D1_OSR_512                0x42
#define PRESSURE7_CMD_CONVERT_D1_OSR_1024               0x44
#define PRESSURE7_CMD_CONVERT_D1_OSR_2048               0x46
#define PRESSURE7_CMD_CONVERT_D1_OSR_4096               0x48
#define PRESSURE7_CMD_CONVERT_D1_OSR_8192               0x4A
#define PRESSURE7_CMD_CONVERT_D2_OSR_256                0x50
#define PRESSURE7_CMD_CONVERT_D2_OSR_512                0x52
#define PRESSURE7_CMD_CONVERT_D2_OSR_1024               0x54
#define PRESSURE7_CMD_CONVERT_D2_OSR_2048               0x56
#define PRESSURE7_CMD_CONVERT_D2_OSR_4096               0x58
#define PRESSURE7_CMD_CONVERT_D2_OSR_8912               0x5A
#define PRESSURE7_CMD_ADC_READ                          0x00
#define PRESSURE7_CMD_PROM_READ                         0xA0
/** \} */

/**
 * \defgroup prom_address PROM Address 
 * \{
 */
#define PRESSURE7_PROM_ADDR_CRC                         0x00
#define PRESSURE7_PROM_ADDR_C1                          0x01 << 1
#define PRESSURE7_PROM_ADDR_C2                          0x02 << 1
#define PRESSURE7_PROM_ADDR_C3                          0x03 << 1
#define PRESSURE7_PROM_ADDR_C4                          0x04 << 1
#define PRESSURE7_PROM_ADDR_C5                          0x05 << 1
#define PRESSURE7_PROM_ADDR_C6                          0x06 << 1
#define PRESSURE7_PROM_ADDR_C7                          0x07 << 1
/** \} */

/**
 * \defgroup prom_error PROM Error 
 * \{
 */
#define PRESSURE7_PROM_READ_ERROR                1
#define PRESSURE7_PROM_READ_OK                   0
 /** \} */

/**
 * \defgroup slave_address Slave Address 
 * \{
 */
#define PRESSURE7_DEVICE_SLAVE_ADDRESS                 0x76
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
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    // additional ctx variables

    float temperature;
    float pressure;

} pressure7_t;

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

} pressure7_cfg_t;
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
void pressure7_cfg_setup ( pressure7_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
PRESSURE7_RETVAL pressure7_init ( pressure7_t *ctx, pressure7_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Pressure7 click.
 */
void pressure7_default_cfg ( pressure7_t *ctx );

/**
 * @brief Generic read function.
 * 
 * @param ctx               Click object.
 * @param reg_addr          Register address.
 * @param data_buf          Output data buf
 * @param len               Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */

 /**
 * @brief Generic read function.
 * 
 * @param ctx               Click object.
 * @param reg_addr          Register address.
 * @param data_buf          Output data buf
 * @param len               Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void pressure7_generic_read ( pressure7_t *ctx, uint8_t reg_addr, uint8_t *data_buf, uint8_t len );

/**
 * @brief Send command to click.
 * 
 * @param ctx               Click object.
 * @param cmd               Action to be commited.
 *
 * @description This function sends command cmd to click object ctx. 
 */
void pressure7_send_command ( pressure7_t *ctx, uint8_t cmd );

/**
 * @brief Start reset sequence.
 *
 * @param ctx               Click object.
 *
 * @description This function starts reset sequence of click object ctx.
 */
void pressure7_reset ( pressure7_t *ctx );

/**
 * @brief Read calibration data from PROM
 *
 * @param ctx               Click object.
 *
 * @returns CRC information: 0-ok, 1-error
 *
 * @description This function must be performed at the beginning of the program
 * in order to read the calibrated data from the PROM required to calculate 
 * the Pressure and Temperature measurement.
 */
uint8_t pressure7_read_prom ( pressure7_t *ctx );

/**
 * @brief Start measurement and calculation data.
 *
 * @param ctx               Click object.
 *
 * @note This function are called at the beginning of each measurement
 * before the function returns the Temperature and Pressure values.
 * This function reads digital pressure and temperature data, 
 * then calculates these values with values read from the PROM.
 * Before calling this function, you need to set OSR 
 * (Over sampling ratio) for Pressure(D1) and Temperature(D2) data.
 *
 * @description This function starts measurement and calculation data.
 */
void pressure7_start_measurement (pressure7_t *ctx);

/**
 * @brief Read Pressure and Temperature data.
 *
 * @param ctx                       Click object.
 * @param Temperature               Output Temperature data in C
 * @param Pressure                  Output Pressure data in mBar
 *
 *
 * @description This function reads pressure and temperature data.
 */
void pressure7_get_sensor_data ( pressure7_t *ctx, float *Temperature, float *Pressure );

/**
 * @brief Set OSR(Over sampling ratio) for Pressure(D1) and Temperature(D2) data.
 *
 * @param ctx           Click object.
 * @param osr_d1        OSR for Pressure data
 * @param osr_d2        OSR for Temperature data
 *
 * @note OSR data (256,512,1024,2048,4095,8192)
 *
 * @description This function sets OSR(Over sampling ratio) for Pressure(D1) and 
 * Temperature(D2) data.
 */
void pressure7_set_over_sampling_ratio ( uint8_t osr_d1, uint8_t osr_d2 );

#ifdef __cplusplus
}
#endif
#endif  // _PRESSURE7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
