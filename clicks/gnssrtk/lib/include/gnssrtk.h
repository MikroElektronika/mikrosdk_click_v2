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
 * @file gnssrtk.h
 * @brief This file contains API for GNSS RTK Click Driver.
 */

#ifndef GNSSRTK_H
#define GNSSRTK_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup gnssrtk GNSS RTK Click Driver
 * @brief API for configuring and manipulating GNSS RTK Click driver.
 * @{
 */

/**
 * @addtogroup element
 * @{
 */

/**
 * @brief GNGGA elements.
 * @details Supported elements for parsing GNGGA responses of GNSS RTK Click driver.
 */

#define GNSSRTK_GNGGA_TIME                              1 
#define GNSSRTK_GNGGA_LATITUDE                          2
#define GNSSRTK_GNGGA_LATITUDE_SIDE                     3
#define GNSSRTK_GNGGA_LONGITUDE                         4
#define GNSSRTK_GNGGA_LONGITUDE_SIDE                    5
#define GNSSRTK_GNGGA_QUALITY_INDICATOR                 6
#define GNSSRTK_GNGGA_NUMBER_OF_SATELLITES              7
#define GNSSRTK_GNGGA_H_DILUTION_OF_POS                 8
#define GNSSRTK_GNGGA_ALTITUDE                          9
#define GNSSRTK_GNGGA_ALTITUDE_UNIT                     10
#define GNSSRTK_GNGGA_GEOIDAL_SEPARATION                11
#define GNSSRTK_GNGGA_GEOIDAL_SEPARATION_UNIT           12
#define GNSSRTK_GNGGA_TIME_SINCE_LAST_DGPS              13
#define GNSSRTK_GNGGA_DGPS_REFERENCE_STATION_ID         14

/**
 * @brief GNGLL elements.
 * @details Supported elements for parsing GNGLL responses of GNSS RTK Click driver.
 */

#define GNSSRTK_GNGLL_LATITUDE                          1
#define GNSSRTK_GNGLL_LATITUDE_SIDE                     2
#define GNSSRTK_GNGLL_LONGITUDE                         3
#define GNSSRTK_GNGLL_LONGITUDE_SIDE                    4

/*! @} */ // element

/**
 * @addtogroup gnssrtk_error_t
 * @{
 */

/**
 * @brief GNSS RTK error code.
 * @details Error code returns from parsing respones of GNSS RTK Click driver.
 */

#define GNSSRTK_ERROR_COMMAND_OR_ELEMENT                0xFF
#define GNSSRTK_ERROR_START_OR_END_COMMAND              0x8F
#define GNSSRTK_ERROR_NEXT_ELEMENT                      0x4F
#define GNSSRTK_ERROR_CURRENT_ELEMENT                   0x2F
#define GNSSRTK_NO_ERROR                                0x00

/*! @} */ // gnssrtk_error_t

/**
 * @addtogroup command
 * @{
 */

/**
 * @brief GNSS RTK support command.
 * @details Supported commands for parsing responses of GNSS RTK Click driver.
 */

#define GNSSRTK_NMEA_GNGGA                              1
#define GNSSRTK_NMEA_GNGLL                              3

/*! @} */ // command

/**
 * @addtogroup gnssrtk_set
 * @{
 */

/**
 * @brief GNSS RTK driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */

#define DRV_BUFFER_SIZE_RX                              200
#define DRV_BUFFER_SIZE_TX                              50

/*! @} */ // gnssrtk_set

/**
 * @defgroup gnssrtk_map GNSS RTK MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS RTK Click driver.
 */

/**
 * @addtogroup gnssrtk_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS RTK Click to the selected MikroBUS.
 */
#define GNSSRTK_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rtk = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.tmp = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gnssrtk_map
/*! @} */ // gnssrtk

/**
 * @brief GNSS RTK Click context object.
 * @details Context object definition of GNSS RTK Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t rst;                              /**< Output rst pin. */

    // Input pins

    digital_in_t rdy;                               /**< Input rdy pin. */
    digital_in_t rtk;                               /**< Input rtk pin. */
    digital_in_t tmp;                               /**< Input tmp pin. */

    // Modules

    uart_t uart;                                    /**< UART driver object. */

    // Buffers

    char uart_rx_buffer[ DRV_BUFFER_SIZE_RX ];      /**< RX Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE_TX ];      /**< TX Buffer size. */

} gnssrtk_t;

/**
 * @brief GNSS RTK Click configuration object.
 * @details Configuration object definition of GNSS RTK Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t rx_pin;                              /**< RX pin. */
    pin_name_t tx_pin;                              /**< TX pin. */

    // Additional gpio pins

    pin_name_t rdy;                                 /**< Input rdy pin. */
    pin_name_t rtk;                                 /**< Input rtk pin. */
    pin_name_t rst;                                 /**< Output rst pin. */
    pin_name_t tmp;                                 /**< Input tmp pin. */

    // Static variable

    uint32_t          baud_rate;                    /**< Clock speed. */
    bool              uart_blocking;                /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                     /**< Data bits. */
    uart_parity_t     parity_bit;                   /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                     /**< Stop bits. */

} gnssrtk_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t gnssrtk_error_t;

/*!
 * @addtogroup gnssrtk GNSS RTK Click Driver
 * @brief API for configuring and manipulating GNSS RTK Click driver.
 * @{
 */

/**
 * @brief GNSS RTK configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnssrtk_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnssrtk_cfg_setup ( gnssrtk_cfg_t *cfg );

/**
 * @brief GNSS RTK initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gnssrtk_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnssrtk_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk_init ( gnssrtk_t *ctx, gnssrtk_cfg_t *cfg );

/**
 * @brief GNSS RTK default configuration function.
 * @details This function executes a default configuration of GNSS RTK
 * click board.
 * @param[in] ctx : Click context object.
 * See #gnssrtk_t object definition for detailed explanation.
 *
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void gnssrtk_default_cfg ( gnssrtk_t *ctx );

/**
 * @brief Module cold start function.
 * @details Resets the module receiver.
 * @param[in] ctx : Click context object.
 * 
 * @note None.
 */
void gnssrtk_module_cold_start ( gnssrtk_t *ctx );

/**
 * @brief Set rst pin function.
 * @details This function sets the state of RST pin.
 * @param ctx Click object.
 * @param[in] state :
 *     @li @c 0 - Sets RST pin low.
 *     @li @c 1 - Sets RST pin high.
 * 
 * @note None.
 */
void gnssrtk_set_rst_pin ( gnssrtk_t *ctx, uint8_t state );

/**
 * @brief Check rdy pin function.
 * @details This function checks if the buffer is full and ready for
 * transmition of data from the module. Return depends on the
 * configuration of the polarity. By default, this feature is disabled.
 * @param[in] ctx : Click context object.
 * See #gnssrtk_t object definition for detailed explanation.
 * @return @li @c  0 - Bytes are not ready for transmition,
 *         @li @c  1 - Bytes are ready to be transmitted.
 *
 * @note None.
 */
uint8_t gnssrtk_get_rdy_pin ( gnssrtk_t *ctx );

/**
 * @brief Check rtk pin function.
 * @details This function checks the RTK_STAT of the module.
 * @param[in] ctx : Click context object.
 * See #gnssrtk_t object definition for detailed explanation.
 * @return @li @c  0 - RTK fixed,
 *         @li @c  1 - No carrier phase solution is available.
 *
 * @note None.
 */
uint8_t gnssrtk_get_rtk_pin ( gnssrtk_t *ctx );

/**
 * @brief Check tmp pin function.
 * @details This function checks the timepulse pin of the module
 * which triggers periodically.
 * @param[in] ctx : Click context object.
 * See #gnssrtk_t object definition for detailed explanation.
 * @return @li @c  0 - Timepulse status is inactive or low during period,
 *         @li @c  1 - Timepulse status is triggered for a period of time.
 *
 * @note None.
 */
uint8_t gnssrtk_get_tmp_pin ( gnssrtk_t *ctx );

/**
 * @brief GNSS RTK data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssrtk_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk_generic_write ( gnssrtk_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief GNSS RTK data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssrtk_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk_generic_read ( gnssrtk_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Generic parser function.
 * @param[in] rsp Response buffer intended for parsing.
 * @param[in] command NMEA ( GPS/GNSS ) command.
 * @param[in] element Element position in command.
 * @param[out] parser_buf Parser buffer for data storage.
 * @return GNSS RTK error code.
 * 
 * See #gnssrtk_error_t definition for detailed explanation.
 * @note None.
 */
gnssrtk_error_t gnssrtk_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );

#ifdef __cplusplus
}
#endif
#endif // GNSSRTK_H

/*! @} */ // gnssrtk

// ------------------------------------------------------------------------ END
