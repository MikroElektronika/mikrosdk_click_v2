/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file dht22.h
 * @brief This file contains API for DHT22 Click Driver.
 */

#ifndef DHT22_H
#define DHT22_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup dht22 DHT22 Click Driver
 * @brief API for configuring and manipulating DHT22 Click driver.
 * @{
 */

/**
 * @addtogroup dht22_set
 * @{
 */

/**
 *@defgroup dht22_set DHT22 response status.
 * @brief Settings for response status of DHT22 Click driver.
 */
#define DHT22_RESP_NOT_READY  0
#define DHT22_RESP_READY      1

/*! @} */ // dht22_set

/**
 * @defgroup dht22_map DHT22 MikroBUS Map
 * @brief MikroBUS pin mapping of DHT22 Click driver.
 */

/**
 * @addtogroup dht22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DHT22 Click to the selected MikroBUS.
 */
#define DHT22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.sd1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.sd2 = MIKROBUS( mikrobus, MIKROBUS_INT )
    
/*! @} */ // dht22_map
/*! @} */ // dht22


/**
 * @brief DHT22 Click data pin selector.
 * @details Predefined enum values for data pin selector.
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
    digital_out_t  sda_out;    /**<  Output data pin object. */

    digital_in_t  sda_in;      /**<  Input data pin object. */
    
    pin_name_t  sd1;           /**<  Data SD1 pin descriptors. */
    pin_name_t  sd2;           /**<  Data SD2 pin descriptors. */

    dht22_sda_sel_t  sda_sel;  /**<  Data pin selector. */

    err_t  sda_out_stat;      /**<  Data output pin object status. */
    err_t  sda_in_stat;       /**<  Data input pin object status. */

} dht22_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Data pin descriptors

    pin_name_t  sd1;    /**<  Data SD1 pin descriptors. */
    pin_name_t  sd2;    /**<  Data SD2 pin descriptors. */

    dht22_sda_sel_t  sda_sel;    /**<  Data pin selector. */

} dht22_cfg_t;


/**
 * @brief DHT22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DHT22_OK = 0,
    DHT22_ERROR = -1

} dht22_return_value_t;

/*!
 * @addtogroup dht22 DHT22 Click Driver
 * @brief API for configuring and manipulating DHT22 Click driver.
 * @{
 */

/**
 * @brief DHT22 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dht22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dht22_cfg_setup ( dht22_cfg_t *cfg );

/**
 * @brief DHT22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dht22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dht22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dht22_init ( dht22_t *ctx, dht22_cfg_t *cfg );

/**
 * @brief DHT22 sends start signal to the sensor function.
 * @details This function sends the start signal to the tempemperature and humidity
 * sensor AM2302 on DHT22 click board.
 * @param[in] ctx : Click context object.
 * See #dht22_t object definition for detailed explanation.
 * @return Nothing.
 * @note Before calling this function it is necessary to set the SDA pin as output.
 */
err_t dht22_start_signal ( dht22_t *ctx );

/**
 * @brief DHT22 release the bus to wait the sensor response signal function.
 * @details This function release the bus to wait the sensor response signal from
 * the sensor AM2302 on the DHT22 Click.
 * @param[in] ctx : Click context object.
 * See #dht22_t object definition for detailed explanation.
 * @return @li @c  0 - The sensor responded and is ready to read data,
 *         @li @c -1 - ERROR, Sensor not responding.
 * @note Before calling this function it is necessary to:
 * - 1. : sends start signal to the sensor by calling #dht22_start_signal function.
 * - 2. : set the SDA pin as input.
 */
err_t dht22_check_sensor_response ( dht22_t *ctx );

/**
 * @brief DHT22 reading data from the sensor function.
 * @details This function reading data from the sensor AM2302 on the DHT22 Click.
 * @param[in] ctx : Click context object.
 * See #dht22_t object definition for detailed explanation.
 * @param[out] hum_data 16-bit read humidity data value from the sensor.
 * @param[out] temp_data 16-bit read temperature data value from the sensor.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note  Before calling this function it is necessary to :
 * - 1. : set the SDA pin as output.
 * - 2. : sends start signal to the sensor by calling #dht22_start_ignal function.
 * - 3. : set the SDA pin as input.
 * - 4. : release the bus to wait the sensor response signal by calling #dht22_check_sensor_response function.
 */
err_t dht22_get_sensor_data ( dht22_t *ctx, uint16_t *hum_data, uint16_t *temp_data );

/**
 * @brief DHT22 get measurement data from the sensor function.
 * @details This function reading and calculate measurement data 
 * from the sensor AM2302 on the DHT22 Click.
 * @param[in] ctx : Click context object.
 * See #dht22_t object definition for detailed explanation.
 * @param[out] humidity Percentage of relative humidity [% RH].
 * @param[out] temperature Temperature value in degrees Celsius [degree Celsius].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dht22_get_measurement_data ( dht22_t *ctx, float *humidity, float *temperature );

/**
 * @brief DHT22 init SDA data pin as input function.
 * @details This functioninitializes SDA data pin as input
 * of the sensor AM2302 on the DHT22 Click.
 * @param[in] ctx : Click context object.
 * See #dht22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dht22_init_sda_input ( dht22_t *ctx );

/**
 * @brief DHT22 init SDA data pin as output function.
 * @details This functioninitializes SDA data pin as output
 * of the sensor AM2302 on the DHT22 Click.
 * @param[in] ctx : Click context object.
 * See #dht22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dht22_init_sda_output ( dht22_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // DHT22_H

/*! @} */ // dht22

// ------------------------------------------------------------------------ END
