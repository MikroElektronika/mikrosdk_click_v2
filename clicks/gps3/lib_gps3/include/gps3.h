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
 * @file gps3.h
 * @brief This file contains API for GPS 3 Click Driver.
 */

#ifndef GPS3_H
#define GPS3_H

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
 * @addtogroup gps3 GPS 3 Click Driver
 * @brief API for configuring and manipulating GPS 3 Click driver.
 * @{
 */

/**
 * @defgroup gps3_cmd GPS 3 Device Settings
 * @brief Settings for registers of GPS 3 Click driver.
 */

/**
 * @addtogroup gps3_cmd
 * @{
 */

/**
 * @brief GPS 3 response buffer commands.
 * @details Specified response buffer commands of GPS 3 Click driver.
 */
#define GPS3_RSP_START                              "$"
#define GPS3_RSP_DELIMITER                          ","
#define GPS3_RSP_END_SEQ                            "\r\n"
#define GPS3_RSP_GPGGA                              "$GPGGA"

/**
 * @brief GPS 3 GPGGA command elements.
 * @details Specified GPGGA command elements of GPS 3 Click driver.
 */
#define GPS3_GPGGA_ELEMENT_SIZE                     15
#define GPS3_GPGGA_TIME                             1
#define GPS3_GPGGA_LATITUDE                         2
#define GPS3_GPGGA_LATITUDE_SIDE                    3
#define GPS3_GPGGA_LONGITUDE                        4
#define GPS3_GPGGA_LONGITUDE_SIDE                   5
#define GPS3_GPGGA_QUALITY_INDICATOR                6
#define GPS3_GPGGA_NUMBER_OF_SATELLITES             7
#define GPS3_GPGGA_H_DILUTION_OF_POS                8
#define GPS3_GPGGA_ALTITUDE                         9
#define GPS3_GPGGA_ALTITUDE_UNIT                    10
#define GPS3_GPGGA_GEOIDAL_SEPARATION               11
#define GPS3_GPGGA_GEOIDAL_SEPARATION_UNIT          12
#define GPS3_GPGGA_TIME_SINCE_LAST_DGPS             13
#define GPS3_GPGGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GPS 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GPS3_DRV_TX_BUFFER_SIZE                     100
#define GPS3_DRV_RX_BUFFER_SIZE                     1000

/*! @} */ // gps3_cmd

/**
 * @defgroup gps3_map GPS 3 MikroBUS Map
 * @brief MikroBUS pin mapping of GPS 3 Click driver.
 */

/**
 * @addtogroup gps3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GPS 3 Click to the selected MikroBUS.
 */
#define GPS3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // gps3_map
/*! @} */ // gps3
    
/**
 * @brief GPS 3 Click context object.
 * @details Context object definition of GPS 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;

    // Modules
    uart_t uart;        /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ GPS3_DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ GPS3_DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */

} gps3_t;

/**
 * @brief GPS 3 Click configuration object.
 * @details Configuration object definition of GPS 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} gps3_cfg_t;

/**
 * @brief GPS 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GPS3_OK = 0,
    GPS3_ERROR = -1

} gps3_return_value_t;

/*!
 * @addtogroup gps3 GPS 3 Click Driver
 * @brief API for configuring and manipulating GPS 3 Click driver.
 * @{
 */

/**
 * @brief GPS 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gps3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gps3_cfg_setup ( gps3_cfg_t *cfg );

/**
 * @brief GPS 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gps3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gps3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps3_init ( gps3_t *ctx, gps3_cfg_t *cfg );

/**
 * @brief GPS 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gps3_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps3_generic_write ( gps3_t *ctx, char *data_in, uint16_t len );

/**
 * @brief GPS 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gps3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps3_generic_read ( gps3_t *ctx, char *data_out, uint16_t len );

/**
 * @brief GPS 3 clear ring buffers function.
 * @details This function clears UART tx and rx ring buffers.
 * @param[in] ctx : Click context object.
 * See #gps3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gps3_clear_ring_buffers ( gps3_t *ctx );

/**
 * @brief GPS 3 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gps3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gps3_set_rst_pin ( gps3_t *ctx, uint8_t state );

/**
 * @brief GPS 3 parse GPGGA function.
 * @details This function parses the GPGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gpgga_element : GPGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps3_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // GPS3_H

/*! @} */ // gps3

// ------------------------------------------------------------------------ END