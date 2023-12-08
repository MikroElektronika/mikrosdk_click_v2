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
 * @file gps6.h
 * @brief This file contains API for GPS 6 Click Driver.
 */

#ifndef GPS6_H
#define GPS6_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup gps6 GPS 6 Click Driver
 * @brief API for configuring and manipulating GPS 6 Click driver.
 * @{
 */

/**
 * @defgroup gps6_cmd GPS 6 Device Settings
 * @brief Settings for registers of GPS 6 Click driver.
 */

/**
 * @addtogroup gps6_cmd
 * @{
 */

/**
 * @brief GPS 6 response buffer commands.
 * @details Specified response buffer commands of GPS 6 Click driver.
 */
#define GPS6_RSP_START                              "$"
#define GPS6_RSP_DELIMITER                          ","
#define GPS6_RSP_GPGGA                              "$GPGGA"

/**
 * @brief GPS 6 GPGGA command elements.
 * @details Specified GPGGA command elements of GPS 6 Click driver.
 */
#define GPS6_GPGGA_ELEMENT_SIZE                     15
#define GPS6_GPGGA_TIME                             1
#define GPS6_GPGGA_LATITUDE                         2
#define GPS6_GPGGA_LATITUDE_SIDE                    3
#define GPS6_GPGGA_LONGITUDE                        4
#define GPS6_GPGGA_LONGITUDE_SIDE                   5
#define GPS6_GPGGA_QUALITY_INDICATOR                6
#define GPS6_GPGGA_NUMBER_OF_SATELLITES             7
#define GPS6_GPGGA_H_DILUTION_OF_POS                8
#define GPS6_GPGGA_ALTITUDE                         9
#define GPS6_GPGGA_ALTITUDE_UNIT                    10
#define GPS6_GPGGA_GEOIDAL_SEPARATION               11
#define GPS6_GPGGA_GEOIDAL_SEPARATION_UNIT          12
#define GPS6_GPGGA_TIME_SINCE_LAST_DGPS             13
#define GPS6_GPGGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GPS 6 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_TX_BUFFER_SIZE                          300
#define DRV_RX_BUFFER_SIZE                          100

/*! @} */ // gps6_cmd

/**
 * @defgroup gps6_map GPS 6 MikroBUS Map
 * @brief MikroBUS pin mapping of GPS 6 Click driver.
 */

/**
 * @addtogroup gps6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GPS 6 Click to the selected MikroBUS.
 */
#define GPS6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // gps6_map
/*! @} */ // gps6

/**
 * @brief GPS 6 Click context object.
 * @details Context object definition of GPS 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Reset pin. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */

} gps6_t;

/**
 * @brief GPS 6 Click configuration object.
 * @details Configuration object definition of GPS 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                             /**< Reset pin. */

    // Static variable
    uint32_t          baud_rate;                /**< Clock speed. */
    bool              uart_blocking;            /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                 /**< Data bits. */
    uart_parity_t     parity_bit;               /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                 /**< Stop bits. */

} gps6_cfg_t;

/**
 * @brief GPS 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GPS6_OK = 0,
    GPS6_ERROR = -1

} gps6_return_value_t;

/*!
 * @addtogroup gps6 GPS 6 Click Driver
 * @brief API for configuring and manipulating GPS 6 Click driver.
 * @{
 */

/**
 * @brief GPS 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gps6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gps6_cfg_setup ( gps6_cfg_t *cfg );

/**
 * @brief GPS 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gps6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gps6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps6_init ( gps6_t *ctx, gps6_cfg_t *cfg );

/**
 * @brief GPS 6 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gps6_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps6_generic_write ( gps6_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief GPS 6 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gps6_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps6_generic_read ( gps6_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief GPS 6 enable device function.
 * @details This function enables device by setting the RST pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #gps6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gps6_enable_device ( gps6_t *ctx );

/**
 * @brief GPS 6 disable device function.
 * @details This function disables device by setting the RST pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #gps6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gps6_disable_device ( gps6_t *ctx ); 

/**
 * @brief GPS 6 parse GPGGA function.
 * @details This function parses the GPGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gpgga_element : GPGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps6_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // GPS6_H

/*! @} */ // gps6

// ------------------------------------------------------------------------ END
