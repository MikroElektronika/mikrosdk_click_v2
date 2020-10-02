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
 * \brief This file contains API for TempHum 13 Click driver.
 *
 * \addtogroup temphum13 TempHum 13 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM13_H
#define TEMPHUM13_H

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
#define TEMPHUM13_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define  TEMPHUM13_RETVAL  uint8_t

#define  TEMPHUM13_OK                         0x00
#define  TEMPHUM13_INIT_ERROR                 0xFF
/** \} */

/**
 * \defgroup slave_addr Slave Address
 * \{
 */
#define  TEMPHUM13_DEVICE_ADDRESS             0x40
/** \} */

/**
 * \defgroup commands Commands
 * \{
 */
#define  TEMPHUM13_CMD_TRIG_TEMP_MEAS_HOLD    0xE3
#define  TEMPHUM13_CMD_TRIG_HUMI_MEAS_HOLD    0xE5
#define  TEMPHUM13_CMD_TRIG_TEMP_MEAS_NOHOLD  0xF3
#define  TEMPHUM13_CMD_TRIG_HUMI_MEAS_NOHOLD  0xF5
#define  TEMPHUM13_CMD_WRITE_USER_REG         0xE6
#define  TEMPHUM13_CMD_READ_USER_REG          0xE7
#define  TEMPHUM13_CMD_SOFT_RESET             0xFE
/** \} */


/**
 * \defgroup heater_switch Heater Switch
 * \{
 */
#define  TEMPHUM13_HEATER_ENABLE              0x01
#define  TEMPHUM13_HEATER_DISABLE             0x00
/** \} */

/**
 * \defgroup resolution Resolution
 * \{
 */
#define  TEMPHUM13_RESOLUTION_8               0x01
#define  TEMPHUM13_RESOLUTION_10              0x80
#define  TEMPHUM13_RESOLUTION_11              0x81
#define  TEMPHUM13_RESOLUTION_12              0x00
/** \} */

/**
 * \defgroup otp OTP
 * \{
 */
#define  TEMPHUM13_OTP_DISABLE                0x01
#define  TEMPHUM13_OTP_ENABLE                 0x00
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

} temphum13_t;

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

} temphum13_cfg_t;

/** \} */ // End types group
/** \} */ // End variable group
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
 * @param cfg               Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void temphum13_cfg_setup ( temphum13_cfg_t *cfg );

/**
 * @brief                   Initialization function.
 *
 * @param ctx               Click object.
 * @param cfg               Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHUM13_RETVAL temphum13_init ( temphum13_t *ctx, temphum13_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx               Click object.
 *
 * @description This function executes default configuration ( delay 0,5 secs - soft reset -
 * delay 0,5 secs ) for TempHum13 click.
 */
void temphum13_default_cfg ( temphum13_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx               Click object.
 * @param reg               Register address.
 * @param data_buf          Data buf to be written.
 * @param len               Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void temphum13_generic_write ( temphum13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx               Click object.
 * @param reg               Register address.
 * @param data_buf          Output data buf
 * @param len               Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void temphum13_generic_read ( temphum13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Get temperature value
 *
 * @param ctx               Click object.
 *
 * @returns  65536 on error i.e CRC missmatch, Temperature value otherwise
 *
 * @description This function calculates current temperature.
 */
float temphum13_get_temperature ( temphum13_t *ctx );

/**
 * @brief Get humidity value
 *
 * @param ctx               Click object.
 *
 * @returns  65536 on error i.e CRC missmatch, humidity value otherwise
 *
 * @description This function calculates humidity.
 */
float temphum13_get_humidity ( temphum13_t *ctx );

/**
 * @brief Get user register value
 *
 * @param ctx               Click object.
 *
 * @returns Value of user register
 *
 * @description This function gets user register value
 */
uint8_t temphum13_get_user_register ( temphum13_t *ctx );

/**
 * @brief Set user register
 *
 * @param ctx               Click object 
 * @param register_content  Desired register content to be set
 *
 * @description This function sets user register to desired value.
 */
void temphum13_set_user_register ( temphum13_t *ctx, uint8_t register_content );

/**
 * @brief Software reset
 *
 * @param ctx               Click object.
 *
 * @description This function performs click soft reset.
 */
void temphum13_soft_reset ( temphum13_t *ctx );

/**
 * @brief Enable heater
 *
 * @param ctx               Click object.
 * @param enable_heater     Heater enable/disable switch.
 *
 * @returns 0 - correct input value, 1 - incorrect input value
 *
 * @description This function enables or disables heater.
 *
 * @note
 * <pre>
 * enable_heater = 0 means disable heater; enable_heater = 1 means enable heater.
 * </pre>
 */
uint8_t temphum13_enable_heater ( temphum13_t *ctx, uint8_t enable_heater );

/**
 * @brief Change measurement resolution
 *
 * @param ctx               Click object.
 * @param meas_res          Resolution to be set.
 *
 * @returns 0 - correct input value, 1 - incorrect input value
 *
 * @description This function sets click measurement resolution.
 *
 * @note
 * <pre>
 * meas_res = 0x00 => resolution is 12-bit, 0x01 => resolution is 8-bit
 *            0x80 => resolution is 10-bit, 0x81 => resolution is 11-bit
 * </pre> 
 */
uint8_t temphum13_change_resolution ( temphum13_t *ctx, uint8_t meas_res );

/**
 * @brief Disable OTP
 *
 * @param ctx               Click object.
 * @param disable_otp_rel   OTP reload boolean.
 * 
 * @returns 0 - correct input value, 1 - incorrect input value
 *
 * @description This function disables or enables OTP.
 *
 * @note
 * <pre>
 * If disable_otp_rel = 1 => OTP disabled, 0 => OTP enabled.
 * </pre>
 */
uint8_t temphum13_disable_otp_reload ( temphum13_t *ctx, uint8_t disable_otp_rel );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM13_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
