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
 * \brief This file contains API for Thermo 11 Click driver.
 *
 * \addtogroup thermo11 Thermo 11 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THERMO11_H
#define THERMO11_H

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
#define THERMO11_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THERMO11_RETVAL  uint8_t

#define THERMO11_OK           0x00
#define THERMO11_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_address  Device address
 * \{
 */
#define THERMO11_DEV_ADDR                                 0x48
 /** \} */

/**
 * \defgroup register  Register
 * \{
 */
#define THERMO11_TEMPERATURE_REG                          0x00
#define THERMO11_CONFIG_REG                               0x01
#define THERMO11_HIGH_LIMIT_REG                           0x02
#define THERMO11_LOW_LIMIT_REG                            0x03
#define THERMO11_EEPROM_UNLOCK_REG                        0x04
#define THERMO11_EEPROM1_REG                              0x05
#define THERMO11_EEPROM2_REG                              0x06
#define THERMO11_TEMP_OFFSET_REG                          0x07
#define THERMO11_EEPROM3_REG                              0x08
#define THERMO11_DEV_ID_REG                               0x0F
 /** \} */

 /**
 * \defgroup time_mode  Time Mode
 * \{
 */
#define  THERMO11_CONTINUOUS_CONV_MODE                    0x0000
#define  THERMO11_SHUTDOWN_MODE                           0x0400
#define  THERMO11_ONESHOT_CONV_MODE                       0x0C00
#define  THERMO11_CONV_TIME_0                             0x0000
#define  THERMO11_CONV_TIME_1                             0x0080
#define  THERMO11_CONV_TIME_2                             0x0100
#define  THERMO11_CONV_TIME_3                             0x0180
#define  THERMO11_CONV_TIME_4                             0x0200
#define  THERMO11_CONV_TIME_5                             0x0280
#define  THERMO11_CONV_TIME_6                             0x0300
#define  THERMO11_CONV_TIME_7                             0x0380
#define  THERMO11_NO_AVRG                                 0x0000
#define  THERMO11_8_AVRG_CONV                             0x0020
#define  THERMO11_32_AVRG_CONV                            0x0040
#define  THERMO11_64_AVRG_CONV                            0x0060
#define  THERMO11_THERM_MODE                              0x0010
#define  THERMO11_ALERT_MODE                              0x0000
#define  THERMO11_INT_PIN_ACT_HIGH                        0x0008
#define  THERMO11_INT_PIN_ACT_LOW                         0x0000
#define  THERMO11_INT_PIN_DRDY_FLAG                       0x0004
#define  THERMO11_INT_PIN_ALERT_FLAGS                     0x0000
#define  THERMO11_SW_RESET_CMD                            0x0002
 /** \} */

 /**
 * \defgroup eeprom  Eeprom
 * \{
 */
#define  THERMO11_EEPROM_LOCK                             0x0000
#define  THERMO11_EEPROM_UNLOCK                           0x8000
#define  THERMO11_EEPROM_BUSY_FLAG                        0x4000
/** \} */

/**
 * \defgroup mask  Mask
 * \{
 */
#define  THERMO11_DEV_ID_MASK                             0x0FFF
#define  THERMO11_REVISION_MASK                           0xF000
/** \} */

/**
 * \defgroup alert_flag  Alert Flag
 * \{
 */
#define  THERMO11_DRDY_FLAG                               0x01
#define  THERMO11_LOW_ALERT_FLAG                          0x02
#define  THERMO11_HIGH_ALERT_FLAG                         0x04
#define  THERMO11_FLAG_IS_CLEARED                         0x00
/** \} */

/**
 * \defgroup invalid  Invalid
 * \{
 */
#define  THERMO11_INVALID_TEMP_RANGE                      0x02
#define  THERMO11_INVALID_ADDR                            0x01
#define  THERMO11_OK                                      0x00
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

} thermo11_t;

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

} thermo11_cfg_t;

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
void thermo11_cfg_setup ( thermo11_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THERMO11_RETVAL thermo11_init ( thermo11_t *ctx, thermo11_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @note
 *<pre>
 *    set: THERMO11_CONFIG_REG
 *        - THERMO11_CONTINUOUS_CONV_MODE
 *        - THERMO11_CONV_TIME_4  
 *        - THERMO11_8_AVRG_CONV  
 *        - THERMO11_ALERT_MODE    
 *        - THERMO11_INT_PIN_ACT_HIGH   
 *        - THERMO11_INT_PIN_DRDY_FLAG 
 *    set: THERMO11_HIGH_LIMIT_REG
 *        - 30.5
 *    set: THERMO11_LOW_LIMIT_REG
 *        - -5
 *</pre>
 * @description This function executes default configuration for Thermo11 click.
 */
void thermo11_default_cfg ( thermo11_t *ctx );

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
void thermo11_generic_write ( thermo11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void thermo11_generic_read ( thermo11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Repeated Write function
 *
 * @param ctx      Click object.
 * @param reg_addr Register adress
 * @param data_in  Memory location where data be stored
 *
 * @description This function write a 16bit data from the last accessed register.
 */
THERMO11_RETVAL thermo11_write_reg ( thermo11_t *ctx, uint8_t reg_addr, uint16_t data_in );

/**
 * @brief Repeated Read function
 * 
 * @param ctx      Click object.
 * @param reg_addr Register adress
 * @param data_out Memory location where data be stored
 *
 * @description This function reads a 16bit data from the last accessed register.
 */
THERMO11_RETVAL thermo11_read_reg ( thermo11_t *ctx, uint8_t reg_addr, uint16_t *data_out );

/**
 * @brief Temperature Get function
 *
 * @param ctx        Click object.
 * @param temp_addr  Address of the desired temperature register
 *
 * @returns 1 - Invalid register address, or temperature value
 *
 * @description This function returns the temperature value converted to the Celsius degrees.
 */
float thermo11_get_temp ( thermo11_t *ctx, uint8_t temp_addr );

/**
 * @brief INT Pin Check function
 *
*  @param ctx      Click object.
 * @returns        0 (Low) or 1 (High) state
 *
 * @description This function returns the state of the INT (ALERT) pin.
 */
THERMO11_RETVAL thermo11_get_int ( thermo11_t *ctx );

/**
 * @brief SMBus Alert Command
 *
 * @param ctx      Click object.
 * @returns        Device slave address + status alert limit bit (LSB)
 *
 * @description  This function sends an SMBus Alert command to the device, and if INT (ALERT) pin is active,
 * the device will respond by returning the slave address followed by status alert limit bit as LSB bit.
 */
uint8_t thermo11_sm_bus_alert_cmd ( thermo11_t *ctx );

/**
 * @brief General Call Reset Command
 *
 * @param ctx     Click object.
 * @description This function allows user to reset the device internal registers to power-up values by sending an
 * General Call Reset command to the device.
 */
void thermo11_general_call_reset_cmd ( thermo11_t *ctx );

/**
 * @brief Software Reset Command
 *
 * @param ctx      Click object.
 * @description This function performs a software reset command.
 */
void thermo11_sw_reset ( thermo11_t *ctx );

/**
 * @brief Status Check function
 *
 * @param ctx      Click object.
 * @returns        Status byte - 0b0000 0xxx
 *
 * @description This function allows user to check status byte which includes the high and low limit alert and data ready status.
 * @note If one of these conditions is asserted, the determined bit flag in status byte will be set.
 */
THERMO11_RETVAL thermo11_check_status ( thermo11_t *ctx );

/**
 * @brief EEPROM Program function
 *
 * @param ctx          Click object.
 * @param eeprom_addr  EEPROM memory address where data be written
 * @param eeprom_data  Data to be written in EEPROM
 *
 * @returns 0 - OK, 1 - Invalid register address
 *
 * @description This function allows user to perform a EEPROM memory programming on the desired value.
 * @note This function will unlock the EEPROM memory and after data writing this function will also perform a
 *       general call reset command to load the programmed data to the corresponding register.
 *       After the reset sequence the EEPROM will be automatically locked.
 */
THERMO11_RETVAL thermo11_program_eeprom ( thermo11_t *ctx, uint8_t eeprom_addr, uint16_t eeprom_data );

/**
 * @brief Temperature Set function
 *
 * @param ctx         Click object.
 * @param temp_addr   Address of the desired temperature register
 * @param temp_value  Desired temperature value in Celsius degrees
 *
 * @description This function allows user to set the desired temperature register on the desired value.
 * 
 * @returns 0 - OK, 1 - Invalid register address, 2 - Invalid temperature range
 */
THERMO11_RETVAL thermo11_set_temp ( thermo11_t *ctx, uint8_t temp_addr, float temp_value );

#ifdef __cplusplus
}
#endif
#endif  // _THERMO11_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
