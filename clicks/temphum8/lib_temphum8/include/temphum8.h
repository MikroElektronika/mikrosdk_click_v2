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
 * \brief This file contains API for Temp&Hum 8 Click driver.
 *
 * \addtogroup temphum8 Temp&Hum 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM8_H
#define TEMPHUM8_H

#include "drv_digital_out.h"
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
#define TEMPHUM8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPHUM8_RETVAL  uint8_t

#define TEMPHUM8_OK           0x00
#define TEMPHUM8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup command Command
 * \{
 */
#define TEMPHUM8_TEMP_MEASUREMENT_HOLD_MODE    0xE3
#define TEMPHUM8_HUM_MEASUREMENT_HOLD_MODE     0xE5
#define TEMPHUM8_TEMP_MEASUREMENT_NO_HOLD_MODE 0xF3
#define TEMPHUM8_HUM_MEASUREMENT_NO_HOLD_MODE  0xF5
#define TEMPHUM8_USER_REGISTER_WRITE           0xE6
#define TEMPHUM8_USER_REGISTER_READ            0xE7
#define TEMPHUM8_SOFT_RESET                    0xFE
/** \} */

/**
 * \defgroup user_register User Register
 * \{
 */
#define TEMPHUM8_CFG_RESOLUTION_H12_T14               0x00
#define TEMPHUM8_CFG_RESOLUTION_H8_T12                0x01
#define TEMPHUM8_CFG_RESOLUTION_H10_T13               0x80
#define TEMPHUM8_CFG_RESOLUTION_H11_T11               0x81
#define TEMPHUM8_CFG_END_OF_BATTERY_LESS_THAN_2_25V   0x40
#define TEMPHUM8_CFG_END_OF_BATTERY_BIGGER_THAN_2_25V 0x00
#define TEMPHUM8_CFG_ENABLE_ON_CHIP_HEATER            0x00
#define TEMPHUM8_CFG_DISABLE_OTP_RELOAD               0x02
/** \} */

/**
 * \defgroup slave_address Slave Address
 * \{
 */
#define TEMPHUM8_DEVICE_SLAVE_ADDRESS 0x40
/** \} */

/**
 * \defgroup temp_data Temp data format
 * \{
 */
#define TEMPHUM8_TEMPERATURE_IN_CELSIUS   0x00
#define TEMPHUM8_TEMPERATURE_IN_KELVIN    0x01
#define TEMPHUM8_TEMPERATURE_IN_FARENHAJT 0x02
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
    uint8_t measure_resolution;

} temphum8_t;

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
    uint8_t measure_res;

} temphum8_cfg_t;

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
void temphum8_cfg_setup ( temphum8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHUM8_RETVAL temphum8_init ( temphum8_t *ctx, temphum8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for TempHum8 click.
 *
 * @note Default configuration of the chip contains the settings :
 *    - Measurement resolution (Temp/Hum - 14bit/12bit)
 *    - Status: End of battery (VDD > 2.25V)
 *    - Enable on-chip heater
 *    - Disable OTP Reload
 */
void temphum8_default_cfg ( temphum8_t *ctx );

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
void temphum8_generic_write ( temphum8_t *ctx, uint8_t reg, uint8_t *data_buffer, uint8_t len );

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
void temphum8_generic_read ( temphum8_t *ctx, uint8_t reg, uint8_t *data_buffer, uint8_t len );

/**
 * @brief Functions for device software reset
 *
 * @param ctx      Click object.
 */
void temphum8_software_reset ( temphum8_t *ctx );

/**
 * @brief Configuration device for measurement
 *
 * @param ctx      Click object.
 * @param cfg    Data to be written in user register
 *
 * @note - Options for sets:
        * Measurement resolution (Temp/Hum - 14bit/12bit, 12bit/8bit, 13bit/10bit or 11bit/11bit)
        * Status: End of battery (VDD > 2.25V or VDD < 2.25V)
        * Enable on-chip heater
        * Disable OTP Reload
 */
void temphum8_set_cfg_register ( temphum8_t *ctx, uint8_t cfg );

/**
 * @brief Temperature data
 *
 * @param ctx      Click object.
 * @param temp_format       Temperature format ... (FAHRENHEIT, KELVIN, CELSIUS)
 *
 * @return Temperature data
 */
float temphum8_get_temperature_data ( temphum8_t *ctx, uint8_t temp_format );

/**
 * @brief Relative Huminidy data
 *
 * @param ctx      Click object.
 *
 *  @return Relative Huminidy data in [%RH]
 */
float temphum8_get_humidity_data ( temphum8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
