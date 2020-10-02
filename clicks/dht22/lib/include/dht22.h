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
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DHT22_H
#define DHT22_H

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
#define DHT22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.sd11= MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sd12= MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sd2= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DHT22_RETVAL  uint8_t

#define DHT22_OK           0x00
#define DHT22_INIT_ERROR   0xFF
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

    digital_out_t  sd12;

    // Input pins 

    digital_in_t  sd11;
    digital_in_t sd2;

} dht22_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t  sd11;
    pin_name_t  sd12;
    pin_name_t sd2;

} dht22_cfg_t;

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
void dht22_cfg_setup ( dht22_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param dht22 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DHT22_RETVAL dht22_init ( dht22_t *ctx, dht22_cfg_t *cfg );

/**
 * @brief Sends start signal to the sensor function.
 *
 * @param ctx  Click object.
 * 
 * The function sends the start signal to
 * the tempemperature and humidity sensor AM2302 on the DHT22 Click.
 *
 * @note
 * @description Before calling this function it is necessary to set the CS pin as output.
 */
void dht22_start_signal ( dht22_t *ctx );

/**
 * @brief Release the bus to wait the sensor response signal function.
 *
 * @param ctx  Click object.
 * 
 * @return result
 * - 0 : ERROR, Sensor not responding.
 * - 1 : The sensor responded and is ready to read data.
 *
 * @description The function release the bus to wait the sensor response signal from
 * the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * Before calling this function it is necessary to :
 * - 1. : sends start signal to the sensor by calling dht22_startSignal() function.
 * - 2. : set the CS pin as input.
 */
uint8_t dht22_check_sensor_response ( dht22_t *ctx );

/**
 * @brief Reading data from the sensor function.
 *
 * @param ctx  Click object.
 * 
 * @return result                    
 * 32-bit read value from the sensor ( temperature and humidity data )
 *
 * @description The function reading data from
 * the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * Before calling this function it is necessary to :
 * - 1. : set the CS pin as output.
 * - 2. : sends start signal to the sensor by calling dht22_startSignal() function.
 * - 3. : set the CS pin as input.
 * - 4. : release the bus to wait the sensor response signal by calling dht22_checkSensorResponse() function.
 */
uint32_t dht22_get_sensor_data ( dht22_t *ctx );

/**
 * @brief Calculate the temperature data function
 *
 * @param ctx  Click object.
 * @param sensor_data                   
 * 32-bit read value from the sensor ( temperature and humidity data )
 *
 * @return result
 * 16-bit temperature data
 *
 * @description The function calculate the temperature data from sensor data reading from
 * the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * The 16-bit temperature data should be divided by 10
 * to obtain the exact temperature value in degrees Celsius [ C ].
 */
uint16_t dht22_calculate_temperature ( dht22_t *ctx, uint32_t sensor_data );

/**
 * @brief Calculate the temperature in degrees Celsius function
 *
 * @param ctx  Click object.
 * @param sensor_data
 * 32-bit read value from the sensor ( temperature and humidity data )
 *
 * @return result
 * float temperature in degrees Celsius [ C ]
 *
 * @description The function calculate the temperature in degrees Celsius [ C ] 
 * from sensor data reading from the sensor AM2302 on the DHT22 Click.
 */
float dht22_calc_temp_c ( dht22_t *ctx, uint32_t sensor_data );

/**
 * @brief Calculate the humidity data function
 *
 * @param ctx  Click object.
 * @param sensor_data
 * 32-bit read value from the sensor ( temperature and humidity data )
 *
 * @return result
 * 16-bit humidity data
 *
 * @description The function calculate the humidity data from sensor data reading from
 * the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * The 16-bit humidity data should be divided by 10
 * to obtain the exact percentage of humidity [ % RH ].
 */
uint16_t dht22_calculate_humidity ( dht22_t *ctx, uint32_t sensor_data );

/**
 * @brief Calculate the humidity in percentage function
 *
 * @param ctx  Click object.
 * @param sensor_data
 * 32-bit read value from the sensor ( temperature and humidity data )
 *
 * @return result
 * float percentage of humidity [ % RH ]
 *
 * @description The function calculate the percentage of humidity [ % RH ]
 * from sensor data reading from the sensor AM2302 on the DHT22 Click.
 */
float dht22_calc_humidity ( dht22_t *ctx, uint32_t sensor_data );

/**
 * @brief Cs input.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes cs on input.
 */
void cs_input (dht22_t *ctx,dht22_cfg_t *cfg);

/**
 * @brief Cs output.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes cs on output.
 */
void cs_output (dht22_t *ctx,dht22_cfg_t *cfg);

#ifdef __cplusplus
}
#endif
#endif  // _DHT22_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
