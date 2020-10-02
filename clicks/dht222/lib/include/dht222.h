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
 * \brief This file contains API for DHT22 2 Click driver.
 *
 * \addtogroup dht222 DHT22 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DHT222_H
#define DHT222_H

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
#define DHT222_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.ow   = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DHT222_RETVAL  uint8_t

#define DHT222_OK           0x00
#define DHT222_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup i2c_addr I2C Address
 * \{
 */
#define DHT222_I2C_ADDRESS                                         0x5C
/** \} */

/**
 * \defgroup reg_addr Register Address
 * \{
 */
#define DHT222_HUMIDITY_DATA_REG                                   0x00
#define DHT222_TEMPERATURE_DATA_REG                                0x02
#define DHT222_READ_REG                                            0x03
#define DHT222_MODEL_DATA_REG                                      0x08
#define DHT222_USERS_REG_1                                         0x10
#define DHT222_USERS_REG_2                                         0x12
#define DHT222_VERSION_DATA_REG                                    0x0A
#define DHT222_ID_DATA_REG                                         0x0B
/** \} */

/**
 * \defgroup cmd Command
 * \{
 */
#define DHT222_WAKE_DATA_CMD                                       0x00
#define DHT222_READ_REQUEST_4_BYTE_CMD                             0x04
#define DHT222_READ_REQUEST_2_BYTE_CMD                             0x02
#define DHT222_READ_REQUEST_1_BYTE_CMD                             0x01
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

    digital_in_t ow;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} dht222_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t ow;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} dht222_cfg_t;

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
void dht222_cfg_setup ( dht222_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx          Click object
 * @param dht222 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DHT222_RETVAL dht222_init ( dht222_t *ctx, dht222_cfg_t *cfg );

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
void dht222_generic_write ( dht222_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void dht222_generic_read ( dht222_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read 8-bit data function
 *
 * @param ctx          Click object 
 * @param address                    8-bit address of data that has to be read
 *
 * @returns response                      8-bit data from given address
 *
 * @description Function read 8-bit data from 8-bit register address.
 */
uint8_t dht222_read_byte ( dht222_t *ctx, uint8_t address );

/**
 * @brief Generic read 16-bit data function
 *
 * @param ctx          Click object 
 * @param address      8-bit address of data that has to be read
 *
 * @returns result                        16-bit data from given address
 *
 * @description Function read 16-bit data from 8-bit register address.
 */
uint16_t dht222_read_data ( dht222_t *ctx, uint8_t address );

/**
 * @brief Reads 32-bit value from given address
 *
 * @param ctx          Click object 
 * @param address      8-bit address of data that has to be read
 *
 * @returns result                        32-bit data from given address
 *
 * @description Function read 32-bit data from 8-bit register address.
 */
uint32_t dht222_read_all_data ( dht222_t *ctx, uint8_t address );

/**
 * @brief Reads temperature from AM2322 sensor
 *
 * @param ctx          Click object

 * @returns temperature                    16-bit temperature data
 *
 * @description The function calculate the temperature data from sensor data reading from
 * the sensor AM2322 on the DHT22 2 Click.
 *
 * @note
 * The 16-bit temperature data should be divided by 10
 * to obtain the exact temperature value in degrees Celsius [ �C ].
 */
uint16_t dht222_get_temperature ( dht222_t *ctx );

/**
 * @brief Reads humidity from AM2322 sensor
 *
 * @param ctx          Click object
 * 
 * @returns humidity 16-bit humidity data
 *
 * @description The function calculate the humidity data from sensor data reading from
 * the sensor AM2322 on the DHT22 2 Click.
 *
 * @note
 * The 16-bit humidity data should be divided by 10
 * to obtain the exact percentage of humidity [ % RH ].
 */
uint16_t dht222_get_humidity ( dht222_t *ctx );
 
/**
 * @brief Get model of AM2322 sensor
 *
 * @returns model                         16-bit model data
 *
 * @description Function read from the model register of AM2322 sensor and
 * return 16-bit model data.
 */
uint16_t dht222_get_model ( dht222_t *ctx );

/**
 * @brief Get users register 1 of AM2322 sensor
 *
 * @param ctx          Click object
 * 
 * @returns users_register                 16-bit users register data
 *
 * @description Function read from the users register 1 of AM2322 sensor and
 * return 16-bit users register 1 data.
 */
uint16_t dht222_get_users_reg1 ( dht222_t *ctx );

/**
 * @brief Get users register 2 of AM2322 sensor
 *
 * @param ctx          Click object
 * 
 * @returns users_register                 16-bit users register data
 *
 * @description Function read from the users register 2 of AM2322 sensor and
 * return 16-bit users register 2 data.
 */
uint16_t dht222_get_users_reg2 ( dht222_t *ctx );
 
/**
 * @brief Get version of AM2322 sensor
 *
 * @param ctx          Click object
 * 
 * @returns version                         16-bit version data
 *
 * @description Function read from the version register of AM2322 sensor and
 * return 16-bit version data.
 */
uint8_t dht222_get_version ( dht222_t *ctx );

/**
 * @brief Get ID of AM2322 sensor
 *
 * @param ctx          Click object 
 *
 * @returns ID                              16-bit version data
 *
 * @description Function read from the ID register of AM2322 sensor and
 * return 16-bit ID data.
 */
uint32_t dht222_get_id ( dht222_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _DHT222_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
