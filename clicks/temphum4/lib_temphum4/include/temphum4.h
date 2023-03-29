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
 * \brief This file contains API for Temp&Hum 4 Click driver.
 *
 * \addtogroup temphum4 Temp&Hum 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TEMPHUM4_H
#define TEMPHUM4_H

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
#define TEMPHUM4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.ad0 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.ad1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TEMPHUM4_RETVAL  uint8_t

#define TEMPHUM4_OK           0x00
#define TEMPHUM4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup device_mod Device mode
 * \{
 */
#define TEMPHUM4_MODE_ACTIVE    0x01 
#define TEMPHUM4_MODE_SLEEP     0x00 
/** \} */

/**
 * \defgroup registers Device registers
 * \{
 */
#define TEMPHUM4_REG_TEMPERATURE       0x00 
#define TEMPHUM4_REG_HUMINIDY          0x01 
#define TEMPHUM4_REG_CONFIGURATION     0x02 
#define TEMPHUM4_REG_MANUFACTURER_ID   0xFE 
#define TEMPHUM4_REG_DEVICE_ID         0xFF 
#define TEMPHUM4_REG_SERIAL_ID         0xFB 
/** \} */

/**
 * \defgroup device_configuration Device configuration registers
 * \{
 */
#define TEMPHUM4_CONF_NORMAL_OPERATION         ( 0x00 << 14 )
#define TEMPHUM4_CONF_SOFT_RESET               ( 0x01 << 14 )
#define TEMPHUM4_CONF_HEATER_DISABLED          ( 0x00 << 12 )
#define TEMPHUM4_CONF_HEATER_ENABLED           ( 0x01 << 12 )
#define TEMPHUM4_CONF_MODE_TEMP_OR_HUM         ( 0x00 << 11 )
#define TEMPHUM4_CONF_MODE_TEMP_AND_HUM        ( 0x01 << 11 )
#define TEMPHUM4_CONF_BATTERY_VOLTAGE_2_8_V    ( 0x00 << 10 )
#define TEMPHUM4_CONF_TEMPERATURE_14bit        ( 0x00 << 9  )
#define TEMPHUM4_CONF_TEMPERATURE_11bit        ( 0x01 << 9  )
#define TEMPHUM4_CONF_HUMINIDY_14bit           ( 0x00 << 7  )
#define TEMPHUM4_CONF_HUMINIDY_11bit           ( 0x01 << 7  )
#define TEMPHUM4_CONF_HUMINIDY_9bit            ( 0x02 << 7  )
/** \} */

/**
 * \defgroup dev_id Device ID value
 * \{
 */
#define TEMPHUM4_MANUFACTURER_ID                0x5449
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

    digital_out_t ad0;
    digital_out_t ad1;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} temphum4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t ad0;
    pin_name_t ad1;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} temphum4_cfg_t;

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
void temphum4_cfg_setup ( temphum4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TEMPHUM4_RETVAL temphum4_init ( temphum4_t *ctx, temphum4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Temp&Hum4 click.
 */
void temphum4_default_cfg ( temphum4_t *ctx );

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
void temphum4_generic_write ( temphum4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void temphum4_generic_read ( temphum4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Set device mode function.
 * 
 * @param ctx          Click object.
 * @param value        Device mode value.
 *
 * @description This function sets device mode.
 */
void temphum4_set_mode ( temphum4_t *ctx, uint8_t value );

/**
 * @brief Get manufacturer's id
 * 
 * @param ctx          Click object.
 * 
 * @description This function gets manifacturer's id from the device.
 */
uint16_t temphum4_get_manifacturer_id ( temphum4_t *ctx );

/**
 * @brief Get device id
 * 
 * @param ctx          Click object.
 * 
 * @description This function gets device id from the device.
 */
uint16_t temphum4_get_device_id ( temphum4_t *ctx );

/**
 * @brief Set device configuration function
 *
 * @param ctx          Click object.
 * @param conf_data    Configuration data values
 *
 * @description This function sets device configuration registers
 */
void temphum4_configuration( temphum4_t *ctx, uint16_t conf_data);
   
/**
 * @brief Get temperature function.
 *
 * @param ctx         Click object.
 *
 * @description This function reads temperature data from the module.
 */
float temphum4_get_temperature ( temphum4_t *ctx );

/**
 * @brief Get humidity function.
 *
 * @param ctx         Click object.
 *
 * @description This function reads humidity data from the module.
 */
float temphum4_get_humidity ( temphum4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _TEMPHUM4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
