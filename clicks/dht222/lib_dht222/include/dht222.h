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
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DHT222_OK                               0
#define DHT222_ERROR                           -1
/** \} */

/**
 * \defgroup i2c_addr I2C Address
 * \{
 */
#define DHT222_I2C_ADDRESS_WRITE                0xB8
#define DHT222_I2C_ADDRESS_READ                 0xB9
/** \} */

/**
 * \defgroup reg_addr Register Address
 * \{
 */
#define DHT222_REG_HUMIDITY_MSB                 0x00
#define DHT222_REG_HUMIDITY_LSB                 0x01
#define DHT222_REG_TEMPERATURE_MSB              0x02
#define DHT222_REG_TEMPERATURE_LSB              0x03
#define DHT222_REG_MODEL_MSB                    0x08
#define DHT222_REG_MODEL_LSB                    0x09
#define DHT222_REG_VERSION                      0x0A
#define DHT222_REG_DEVICE_ID_3                  0x0B
#define DHT222_REG_DEVICE_ID_2                  0x0C
#define DHT222_REG_DEVICE_ID_1                  0x0D
#define DHT222_REG_DEVICE_ID_0                  0x0E
#define DHT222_REG_STATE                        0x0F
#define DHT222_REG_USER_REG_1_MSB               0x10
#define DHT222_REG_USER_REG_1_LSB               0x11
#define DHT222_REG_USER_REG_2_MSB               0x12
#define DHT222_REG_USER_REG_2_LSB               0x13
/** \} */

/**
 * \defgroup cmd Command
 * \{
 */
#define DHT222_CMD_READ                         0x03
#define DHT222_CMD_WRITE                        0x10
/** \} */

/**
 * \defgroup timeout Clock stretching timeout
 * \{
 */
#define DHT222_TIMEOUT                          100000ul
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
    pin_name_t scl;
    pin_name_t sda;
    
    uint8_t i2c_started;
    
} dht222_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    pin_name_t scl;
    pin_name_t sda;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void dht222_cfg_setup ( dht222_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx          Click object
 * @param cfg          Click configuration structure.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t dht222_init ( dht222_t *ctx, dht222_cfg_t *cfg );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_out     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function reads data from the desired register.
 */
err_t dht222_read_reg ( dht222_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_in      Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function writes data to the desired register.
 */
err_t dht222_write_reg ( dht222_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len );

/**
 * @brief Reads temperature from AM2322 sensor
 *
 * @param ctx           Click object
 * @param temperature   16-bit temperature data
 *
 * @details The function reads the temperature data from the sensor AM2322 on the DHT22 2 Click.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The 16-bit temperature data should be divided by 10 to obtain the exact
 * temperature value in degrees Celsius [ C ].
 */
err_t dht222_get_temperature ( dht222_t *ctx, uint16_t *temperature );

/**
 * @brief Reads humidity from AM2322 sensor
 *
 * @param ctx           Click object
 * @param humidity      16-bit humidity data
 *
 * @details The function reads the humidity data from the sensor AM2322 on the DHT22 2 Click.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The 16-bit humidity data should be divided by 10 to obtain the exact
 * humidity value in percentage [ % ].
 */
err_t dht222_get_humidity ( dht222_t *ctx, uint16_t *humidity );

/**
 * @brief Reads temperature and humidity from AM2322 sensor
 *
 * @param ctx           Click object
 * @param temperature   16-bit temperature data
 * @param humidity      16-bit humidity data
 *
 * @details The function reads the temperature and humidity data from the sensor AM2322 on the DHT22 2 Click.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The 16-bit temperature and humidity data should be divided by 10 to obtain the exact
 * values in degrees Celsius [ C ] and percentage [ % ].
 */
err_t dht222_get_temp_hum ( dht222_t *ctx, uint16_t *temperature, uint16_t *humidity );

#ifdef __cplusplus
}
#endif
#endif  // _DHT222_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
