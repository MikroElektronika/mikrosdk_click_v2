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
 * \brief This file contains API for Temp&Hum 7 Click driver.
 *
 * \addtogroup temphum7 Temp&Hum 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM7_H
#define TEMPHUM7_H

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
#define TEMPHUM7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS ( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS ( mikrobus, MIKROBUS_SDA ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPHUM7_RETVAL  uint8_t

#define TEMPHUM7_OK           0x00
#define TEMPHUM7_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_address Device Address
 * \{
 */
#define TEMPHUM7_DEVICE_ADDRESS                     0x40
/** \} */

/**
 * \defgroup 
 * \{
 */
#define TEMPHUM7_HOLD_MASTER_MODE                   0x00
#define TEMPHUM7_NOHOLD_MASTER_MODE                 0x01
#define TEMPHUM7_DATA_FROM_PREVIOUS_RH_MEASUREMENT  0x02
/** \} */

/**
 * \defgroup device_register Device Register
 * \{
 */
#define TEMPHUM7_RESET                              0xFE
#define TEMPHUM7_WRITE_RHT_USER_REGISTER_1          0xE6
#define TEMPHUM7_READ_RHT_USER_REGISTER_1           0xE7
#define TEMPHUM7_WRITE_HEATER_CONTROL_REGISTER      0x51
#define TEMPHUM7_READ_HEATER_CONTROL_REGISTER       0x11
/** \} */

/**
 * \defgroup  user_register User Register
 * \{
 */
#define TEMPHUM7_RESOLUTION_12_BIT                  0x00
#define TEMPHUM7_RESOLUTION_8_BIT                   0x01
#define TEMPHUM7_RESOLUTION_10_BIT                  0x80
#define TEMPHUM7_RESOLUTION_11_BIT                  0x81
#define TEMPHUM7_HEATER_ENABLE                      0x04
#define TEMPHUM7_HEATER_DISABLE                     0x00
 /** \} */

/** 
 * \defgroup heater_current Heater Current
 * \{
 */
#define TEMPHUM7_HEATER_CURRENT_3p09               0x00
#define TEMPHUM7_HEATER_CURRENT_9p17               0x01
#define TEMPHUM7_HEATER_CURRENT_15p24              0x02
#define TEMPHUM7_HEATER_CURRENT_21p31              0x03
#define TEMPHUM7_HEATER_CURRENT_27p39              0x04
#define TEMPHUM7_HEATER_CURRENT_33p46              0x05
#define TEMPHUM7_HEATER_CURRENT_39p53              0x06
#define TEMPHUM7_HEATER_CURRENT_45p61              0x07
#define TEMPHUM7_HEATER_CURRENT_51p68              0x08
#define TEMPHUM7_HEATER_CURRENT_57p76              0x09
#define TEMPHUM7_HEATER_CURRENT_63p83              0x0A
#define TEMPHUM7_HEATER_CURRENT_69p90              0x0B
#define TEMPHUM7_HEATER_CURRENT_75p98              0x0C
#define TEMPHUM7_HEATER_CURRENT_82p05              0x0D
#define TEMPHUM7_HEATER_CURRENT_88p13              0x0E
#define TEMPHUM7_HEATER_CURRENT_94p20              0x0F
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

} temphum7_t;

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

} temphum7_cfg_t;

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
void temphum7_cfg_setup ( temphum7_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHUM7_RETVAL temphum7_init ( temphum7_t *ctx, temphum7_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for TempHum7 click.
 *
 * @note Default configuration note.
 * <pre>
 *    Set register : TEMPHUM7_WRITE_RHT_USER_REGISTER_1
 *    Data : TEMPHUM7_RESOLUTION_12_BIT
 * </pre>
 */
void temphum7_default_cfg ( temphum7_t *ctx );

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
void temphum7_generic_write ( temphum7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void temphum7_generic_read ( temphum7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Relative humidity.
 * 
 * @param ctx          Click object.
 * @param mode_data    Mode data.
 *
 * @description This function get relative humidity.
 */
float temphum7_get_relative_humidity ( temphum7_t *ctx, uint8_t mode_data );

/**
 * @brief Temerature.
 * 
 * @param ctx          Click object.
 * @param mode_data    Mode data.
 *
 * @description This function get temperature.
 */
float temphum7_get_temperature ( temphum7_t *ctx, uint8_t mode_data );

/**
 * @brief Electronic serial number.
 * 
 * @param ctx          Click object.
 * @param esn_buffer   Buffer.
 *
 * @description This function get electronical serial number.
 */
void temphum7_get_electronic_serial_number ( temphum7_t *ctx, uint8_t *esn_buffer );

/**
 * @brief Firmware revision.
 * 
 * @param ctx          Click object.
 *
 * @description This function get firmware revision.
 */
uint8_t temphum7_get_firmware_revision ( temphum7_t *ctx );

/**
 * @brief Heater current.
 * 
 * @param ctx          Click object.
 *
 * @description This function get heater current.
 */
float temphum7_get_heater_current ( temphum7_t *ctx );

/**
 * @brief Reset.
 * 
 * @param ctx          Click object.
 *
 * @description This function is reset.
 */
void temphum7_reset ( temphum7_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
