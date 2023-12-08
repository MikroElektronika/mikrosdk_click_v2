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
 * @file gps5.h
 * @brief This file contains API for GPS 5 Click Driver.
 */

#ifndef GPS5_H
#define GPS5_H

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
 * @addtogroup gps5 GPS 5 Click Driver
 * @brief API for configuring and manipulating GPS 5 Click driver.
 * @{
 */

/**
 * @defgroup gps5_cmd GPS 5 Device Settings
 * @brief Settings for registers of GPS 5 Click driver.
 */

/**
 * @addtogroup gps5_cmd
 * @{
 */

/**
 * @brief GPS 5 response buffer commands.
 * @details Specified response buffer commands of GPS 5 Click driver.
 */
#define GPS5_RSP_START                              "$"
#define GPS5_RSP_DELIMITER                          ","
#define GPS5_RSP_GNGGA                              "$GNGGA"

/**
 * @brief GPS 5 GNGGA command elements.
 * @details Specified GNGGA command elements of GPS 5 Click driver.
 */
#define GPS5_GNGGA_ELEMENT_SIZE                     15
#define GPS5_GNGGA_TIME                             1
#define GPS5_GNGGA_LATITUDE                         2
#define GPS5_GNGGA_LATITUDE_SIDE                    3
#define GPS5_GNGGA_LONGITUDE                        4
#define GPS5_GNGGA_LONGITUDE_SIDE                   5
#define GPS5_GNGGA_QUALITY_INDICATOR                6
#define GPS5_GNGGA_NUMBER_OF_SATELLITES             7
#define GPS5_GNGGA_H_DILUTION_OF_POS                8
#define GPS5_GNGGA_ALTITUDE                         9
#define GPS5_GNGGA_ALTITUDE_UNIT                    10
#define GPS5_GNGGA_GEOIDAL_SEPARATION               11
#define GPS5_GNGGA_GEOIDAL_SEPARATION_UNIT          12
#define GPS5_GNGGA_TIME_SINCE_LAST_DGPS             13
#define GPS5_GNGGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GPS 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_RX_BUFFER_SIZE                          300
#define DRV_TX_BUFFER_SIZE                          100

/*! @} */ // gps5_cmd

/**
 * @defgroup gps5_map GPS 5 MikroBUS Map
 * @brief MikroBUS pin mapping of GPS 5 Click driver.
 */

/**
 * @addtogroup gps5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GPS 5 Click to the selected MikroBUS.
 */
#define GPS5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // gps5_map
/*! @} */ // gps5

/**
 * @brief GPS 5 Click context object.
 * @details Context object definition of GPS 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;                           /**< Enable antenna pin. */
    digital_out_t rst;                          /**< Reset pin. */
    digital_out_t stb;                          /**< Standby pin. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */

} gps5_t;

/**
 * @brief GPS 5 Click configuration object.
 * @details Configuration object definition of GPS 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t en;                              /**< Enable antenna pin. */
    pin_name_t rst;                             /**< Reset pin. */
    pin_name_t stb;                             /**< Standby pin. */

    // Static variable
    uint32_t          baud_rate;                /**< Clock speed. */
    bool              uart_blocking;            /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                 /**< Data bits. */
    uart_parity_t     parity_bit;               /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                 /**< Stop bits. */

} gps5_cfg_t;

/**
 * @brief GPS 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GPS5_OK = 0,
    GPS5_ERROR = -1

} gps5_return_value_t;

/*!
 * @addtogroup gps5 GPS 5 Click Driver
 * @brief API for configuring and manipulating GPS 5 Click driver.
 * @{
 */

/**
 * @brief GPS 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gps5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gps5_cfg_setup ( gps5_cfg_t *cfg );

/**
 * @brief GPS 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gps5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gps5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps5_init ( gps5_t *ctx, gps5_cfg_t *cfg );

/**
 * @brief GPS 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gps5_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps5_generic_write ( gps5_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief GPS 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gps5_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps5_generic_read ( gps5_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief GPS 5 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gps5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gps5_set_rst_pin ( gps5_t *ctx, uint8_t state );

/**
 * @brief GPS 5 set STB pin function.
 * @details This function sets the STB pin logic state.
 * @param[in] ctx : Click context object.
 * See #gps5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gps5_set_stb_pin ( gps5_t *ctx, uint8_t state );

/**
 * @brief GPS 5 set EN pin function.
 * @details This function sets the EN pin logic state.
 * @param[in] ctx : Click context object.
 * See #gps5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gps5_set_en_pin ( gps5_t *ctx, uint8_t state );

/**
 * @brief GPS 5 parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : GNGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gps5_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // GPS5_H

/*! @} */ // gps5

// ------------------------------------------------------------------------ END
