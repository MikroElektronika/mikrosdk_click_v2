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
 * \brief This file contains API for DHT22 Click driver.
 *
 * \addtogroup dht22 DHT22 Click Driver
 * \{
 */

#ifndef DHT22_H
#define DHT22_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define DHT22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.sd1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sd2 = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DHT22_OK       0
#define DHT22_ERROR  (-1)
/** \} */

/**
 * \defgroup resp_status Response Status
 * \{
 */
#define DHT22_RESP_NOT_READY  0
#define DHT22_RESP_READY      1
/** \} */

/** \} */ // End group macro

/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click data pin selector.
 */
typedef enum
{
    DHT22_SDA_SEL_SDA1,
    DHT22_SDA_SEL_SDA2

} dht22_sda_sel_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output data pin object

    digital_out_t  sda_out;

    // Input data pin object

    digital_in_t  sda_in;

    // Data pin descriptors

    pin_name_t  sd1;
    pin_name_t  sd2;

    // Data pin selector

    dht22_sda_sel_t  sda_sel;

    // Data pin object status

    err_t  sda_out_stat;
    err_t  sda_in_stat;

} dht22_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Data pin descriptors

    pin_name_t  sd1;
    pin_name_t  sd2;

    // Data pin selector

    dht22_sda_sel_t  sda_sel;

} dht22_cfg_t;

/** \} */ // End types group

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
void dht22_cfg_setup ( dht22_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t dht22_init ( dht22_t *ctx, dht22_cfg_t *cfg );

/**
 * @brief Sends start signal to the sensor function.
 *
 * @param ctx  Click object.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description The function sends the start signal to the tempemperature and humidity
 * sensor AM2302 on the DHT22 Click.
 * @note Before calling this function it is necessary to set the SDA pin as output.
 */
err_t dht22_start_signal ( dht22_t *ctx );

/**
 * @brief Release the bus to wait the sensor response signal function.
 *
 * @param ctx  Click object.
 * @param check_out
 *      0 : ERROR, Sensor not responding.
 *      1 : The sensor responded and is ready to read data.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description The function release the bus to wait the sensor response signal from
 * the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * Before calling this function it is necessary to :
 * - 1. : sends start signal to the sensor by calling #dht22_start_signal function.
 * - 2. : set the SDA pin as input.
 */
err_t dht22_check_sensor_response ( dht22_t *ctx, uint8_t *check_out );

/**
 * @brief Reading data from the sensor function.
 *
 * @param ctx  Click object.
 * @param data_out 32-bit read value from the sensor ( temperature and humidity data ).
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description The function reading data from the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * Before calling this function it is necessary to :
 * - 1. : set the SDA pin as output.
 * - 2. : sends start signal to the sensor by calling #dht22_start_ignal function.
 * - 3. : set the SDA pin as input.
 * - 4. : release the bus to wait the sensor response signal by calling #dht22_check_sensor_response function.
 */
err_t dht22_get_sensor_data ( dht22_t *ctx, uint32_t *data_out );

/**
 * @brief Get the temperature data function.
 *
 * @param ctx  Click object.
 * @param sensor_data 32-bit read value from the sensor ( temperature and humidity data ).
 * @return 16-bit temperature data.
 *
 * @description The function calculate the temperature data from sensor data reading from
 * the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * The 16-bit temperature data should be divided by 10
 * to obtain the exact temperature value in degrees Celsius [ C ].
 */
uint16_t dht22_get_temperature ( dht22_t *ctx, uint32_t sensor_data );

/**
 * @brief Calculate the temperature in degrees Celsius function.
 *
 * @param ctx  Click object.
 * @param sensor_data 32-bit read value from the sensor ( temperature and humidity data ).
 * @return Float temperature value in degrees Celsius [ C ].
 *
 * @description The function calculate the temperature in degrees Celsius [ C ]
 * from sensor data reading from the sensor AM2302 on the DHT22 Click.
 */
float dht22_calculate_temperature ( dht22_t *ctx, uint32_t sensor_data );

/**
 * @brief Get the humidity data function.
 *
 * @param ctx  Click object.
 * @param sensor_data 32-bit read value from the sensor ( temperature and humidity data ).
 * @return 16-bit humidity data.
 *
 * @description The function calculate the humidity data from sensor data reading from
 * the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * The 16-bit humidity data should be divided by 10
 * to obtain the exact percentage of humidity [ % RH ].
 */
uint16_t dht22_get_humidity ( dht22_t *ctx, uint32_t sensor_data );

/**
 * @brief Calculate the humidity in percentage function.
 *
 * @param ctx  Click object.
 * @param sensor_data 32-bit read value from the sensor ( temperature and humidity data ).
 * @return Float percentage of relative humidity [ % RH ].
 *
 * @description The function calculate the percentage of humidity [ % RH ]
 * from sensor data reading from the sensor AM2302 on the DHT22 Click.
 */
float dht22_calculate_humidity ( dht22_t *ctx, uint32_t sensor_data );

/**
 * @brief Init SDA data pin as input.
 *
 * @param ctx Click object.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes SDA data pin as input.
 */
err_t dht22_init_sda_input ( dht22_t *ctx );

/**
 * @brief Init SDA data pin as output.
 *
 * @param ctx Click object.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function initializes SDA data pin as output.
 */
err_t dht22_init_sda_output ( dht22_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // DHT22_H

/** \} */  // End public_function group
/** \} */  // End click Driver group

// ------------------------------------------------------------------------ END
