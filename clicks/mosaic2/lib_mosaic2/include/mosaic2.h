/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file mosaic2.h
 * @brief This file contains API for Mosaic 2 Click Driver.
 */

#ifndef MOSAIC2_H
#define MOSAIC2_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup mosaic2 Mosaic 2 Click Driver
 * @brief API for configuring and manipulating Mosaic 2 Click driver.
 * @{
 */

/**
 * @defgroup mosaic2_cmd Mosaic 2 Device Settings
 * @brief Settings of Mosaic 2 Click driver.
 */

/**
 * @addtogroup mosaic2_cmd
 * @{
 */

/**
 * @brief Mosaic 2 control commands.
 * @details Specified setting for control commands of Mosaic 2 Click driver.
 */
#define MOSAIC2_CMD_SET_NMEA_OUTPUT             "setNMEAOutput"
#define MOSAIC2_CMD_GET_NMEA_VERSION            "getNMEAVersion"

/**
 * @brief Mosaic 2 device commands settings.
 * @details Device commands settings of Mosaic 2 Click driver.
 */
#define MOSAIC2_PROMPT_CMD                      "COM2>"
#define MOSAIC2_PARAM_DELIMITER                 ","
#define MOSAIC2_END_CMD                         "\r\n"

/**
 * @brief Mosaic 2 set NMEA output command parameters.
 * @details Specified setting for set NMEA output command parameters of Mosaic 2 Click driver.
 */
#define MOSAIC2_SNO_STREAM_1                    "Stream1"
#define MOSAIC2_SNO_STREAM_2                    "Stream2"
#define MOSAIC2_SNO_STREAM_3                    "Stream3"
#define MOSAIC2_SNO_STREAM_4                    "Stream4"
#define MOSAIC2_SNO_STREAM_5                    "Stream5"
#define MOSAIC2_SNO_STREAM_6                    "Stream6"
#define MOSAIC2_SNO_STREAM_7                    "Stream7"
#define MOSAIC2_SNO_STREAM_8                    "Stream8"
#define MOSAIC2_SNO_STREAM_9                    "Stream9"
#define MOSAIC2_SNO_STREAM_10                   "Stream10"
#define MOSAIC2_SNO_STREAM_ALL                  "all"
#define MOSAIC2_SNO_CD_NONE                     "none"
#define MOSAIC2_SNO_CD_COM2                     "COM2"
#define MOSAIC2_SNO_MESSAGES_NONE               "none"
#define MOSAIC2_SNO_MESSAGES_ALM                "ALM"
#define MOSAIC2_SNO_MESSAGES_DTM                "DTM"
#define MOSAIC2_SNO_MESSAGES_GBS                "GBS"
#define MOSAIC2_SNO_MESSAGES_GGA                "GGA"
#define MOSAIC2_SNO_MESSAGES_GLL                "GLL"
#define MOSAIC2_SNO_MESSAGES_GNS                "GNS"
#define MOSAIC2_SNO_MESSAGES_GRS                "GRS"
#define MOSAIC2_SNO_MESSAGES_GSA                "GSA"
#define MOSAIC2_SNO_MESSAGES_GST                "GST"
#define MOSAIC2_SNO_MESSAGES_GSV                "GSV"
#define MOSAIC2_SNO_MESSAGES_HDT                "HDT"
#define MOSAIC2_SNO_MESSAGES_RMC                "RMC"
#define MOSAIC2_SNO_MESSAGES_ROT                "ROT"
#define MOSAIC2_SNO_MESSAGES_VTG                "VTG"
#define MOSAIC2_SNO_MESSAGES_ZDA                "ZDA"
#define MOSAIC2_SNO_MESSAGES_HRP                "HRP"
#define MOSAIC2_SNO_MESSAGES_LLQ                "LLQ"
#define MOSAIC2_SNO_MESSAGES_RBP                "RBP"
#define MOSAIC2_SNO_MESSAGES_RBV                "RBV"
#define MOSAIC2_SNO_MESSAGES_RBD                "RBD"
#define MOSAIC2_SNO_MESSAGES_AVR                "AVR"
#define MOSAIC2_SNO_MESSAGES_GGK                "GGK"
#define MOSAIC2_SNO_MESSAGES_GFA                "GFA"
#define MOSAIC2_SNO_MESSAGES_GGQ                "GGQ"
#define MOSAIC2_SNO_MESSAGES_LLK                "LLK"
#define MOSAIC2_SNO_MESSAGES_GMP                "GMP"
#define MOSAIC2_SNO_MESSAGES_TXT_BASE           "TXTbase"
#define MOSAIC2_SNO_MESSAGES_TFM                "TFM"
#define MOSAIC2_SNO_MESSAGES_SNC                "SNC"
#define MOSAIC2_SNO_MESSAGES_THS                "THS"
#define MOSAIC2_SNO_INTERVAL_OFF                "off"
#define MOSAIC2_SNO_INTERVAL_ON_CHANGE          "OnChange"
#define MOSAIC2_SNO_INTERVAL_MSEC10             "msec10"
#define MOSAIC2_SNO_INTERVAL_MSEC20             "msec20"
#define MOSAIC2_SNO_INTERVAL_MSEC40             "msec40"
#define MOSAIC2_SNO_INTERVAL_MSEC50             "msec50"
#define MOSAIC2_SNO_INTERVAL_MSEC100            "msec100"
#define MOSAIC2_SNO_INTERVAL_MSEC200            "msec200"
#define MOSAIC2_SNO_INTERVAL_MSEC500            "msec500"
#define MOSAIC2_SNO_INTERVAL_SEC1               "sec1"
#define MOSAIC2_SNO_INTERVAL_SEC2               "sec2"
#define MOSAIC2_SNO_INTERVAL_SEC5               "sec5"
#define MOSAIC2_SNO_INTERVAL_SEC10              "sec10"
#define MOSAIC2_SNO_INTERVAL_SEC15              "sec15"
#define MOSAIC2_SNO_INTERVAL_SEC30              "sec30"
#define MOSAIC2_SNO_INTERVAL_SEC60              "sec60"
#define MOSAIC2_SNO_INTERVAL_MIN2               "min2"
#define MOSAIC2_SNO_INTERVAL_MIN5               "min5"
#define MOSAIC2_SNO_INTERVAL_MIN10              "min10"
#define MOSAIC2_SNO_INTERVAL_MIN15              "min15"
#define MOSAIC2_SNO_INTERVAL_MIN30              "min30"
#define MOSAIC2_SNO_INTERVAL_MIN60              "min60"

/**
 * @brief Mosaic 2 nmea buffer commands.
 * @details Specified nmea buffer commands of Mosaic 2 Click driver.
 */
#define MOSAIC2_NMEA_START                      "$"
#define MOSAIC2_NMEA_DELIMITER                  ","
#define MOSAIC2_NMEA_END                        "\r\n"
#define MOSAIC2_NMEA_GGA                        "GGA"

/**
 * @brief Mosaic 2 GGA command elements.
 * @details Specified GGA command elements of Mosaic 2 Click driver.
 */
#define MOSAIC2_GGA_ELEMENT_SIZE                15
#define MOSAIC2_GGA_TIME                        1
#define MOSAIC2_GGA_LATITUDE                    2
#define MOSAIC2_GGA_LATITUDE_SIDE               3
#define MOSAIC2_GGA_LONGITUDE                   4
#define MOSAIC2_GGA_LONGITUDE_SIDE              5
#define MOSAIC2_GGA_QUALITY_INDICATOR           6
#define MOSAIC2_GGA_NUMBER_OF_SATELLITES        7
#define MOSAIC2_GGA_H_DILUTION_OF_POS           8
#define MOSAIC2_GGA_ALTITUDE                    9
#define MOSAIC2_GGA_ALTITUDE_UNIT               10
#define MOSAIC2_GGA_GEOIDAL_SEPARATION          11
#define MOSAIC2_GGA_GEOIDAL_SEPARATION_UNIT     12
#define MOSAIC2_GGA_TIME_SINCE_LAST_DGPS        13
#define MOSAIC2_GGA_DGPS_REFERENCE_STATION_ID   14

/**
 * @brief Mosaic 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define MOSAIC2_RX_DRV_BUFFER_SIZE              400
#define MOSAIC2_TX_DRV_BUFFER_SIZE              200

/*! @} */ // mosaic2_cmd

/**
 * @defgroup mosaic2_map Mosaic 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Mosaic 2 Click driver.
 */

/**
 * @addtogroup mosaic2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Mosaic 2 Click to the selected MikroBUS.
 */
#define MOSAIC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.evt = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pps = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // mosaic2_map
/*! @} */ // mosaic2

/**
 * @brief Mosaic 2 Click context object.
 * @details Context object definition of Mosaic 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< UART CTS pin. */

    // Input pins
    digital_in_t evt;               /**< Event pin. */
    digital_in_t pps;               /**< Pulse per second pin. */
    digital_in_t rts;               /**< UART RTS pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ MOSAIC2_RX_DRV_BUFFER_SIZE ];   /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ MOSAIC2_TX_DRV_BUFFER_SIZE ];   /**< TX Buffer size. */
    uint8_t cmd_buffer[ MOSAIC2_TX_DRV_BUFFER_SIZE ];       /**< Command buffer. */

} mosaic2_t;

/**
 * @brief Mosaic 2 Click configuration object.
 * @details Configuration object definition of Mosaic 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t evt;                 /**< Event pin. */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cts;                 /**< UART CTS pin. */
    pin_name_t pps;                 /**< Pulse per second pin. */
    pin_name_t rts;                 /**< UART RTS pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} mosaic2_cfg_t;

/**
 * @brief Mosaic 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MOSAIC2_OK = 0,
    MOSAIC2_ERROR = -1,
    MOSAIC2_ERROR_TIMEOUT = -2

} mosaic2_return_value_t;

/*!
 * @addtogroup mosaic2 Mosaic 2 Click Driver
 * @brief API for configuring and manipulating Mosaic 2 Click driver.
 * @{
 */

/**
 * @brief Mosaic 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mosaic2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mosaic2_cfg_setup ( mosaic2_cfg_t *cfg );

/**
 * @brief Mosaic 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mosaic2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mosaic2_init ( mosaic2_t *ctx, mosaic2_cfg_t *cfg );

/**
 * @brief Mosaic 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mosaic2_generic_write ( mosaic2_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Mosaic 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mosaic2_generic_read ( mosaic2_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Mosaic 2 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void mosaic2_set_rst_pin ( mosaic2_t *ctx, uint8_t state );

/**
 * @brief Mosaic 2 set cts pin function.
 * @details This function sets the CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void mosaic2_set_cts_pin ( mosaic2_t *ctx, uint8_t state );

/**
 * @brief Mosaic 2 get evt pin function.
 * @details This function returns the event (EVT) pin logic state.
 * @param[in] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t mosaic2_get_evt_pin ( mosaic2_t *ctx );

/**
 * @brief Mosaic 2 get pps pin function.
 * @details This function returns the pulse per second (PPS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t mosaic2_get_pps_pin ( mosaic2_t *ctx );

/**
 * @brief Mosaic 2 get rts pin function.
 * @details This function returns the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t mosaic2_get_rts_pin ( mosaic2_t *ctx );

/**
 * @brief Mosaic 2 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void mosaic2_cmd_run ( mosaic2_t *ctx, uint8_t *cmd );

/**
 * @brief Mosaic 2 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void mosaic2_cmd_set ( mosaic2_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief Mosaic 2 enable nmea output function.
 * @details This function enables the NMEA output with the selected message parameters and an output interval.
 * @param[in] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @param[in] msg_param : Message parameter, see MOSAIC2_SNO_MESSAGES_x macro definisions.
 * @param[in] interval : Output interval, see MOSAIC2_SNO_INTERVAL_x macro definisions.
 * @return Nothing.
 * @note None.
 */
void mosaic2_enable_nmea_output ( mosaic2_t *ctx, uint8_t *msg_param, uint8_t *interval );

/**
 * @brief Mosaic 2 disable nmea output function.
 * @details This function disables the NMEA output for Stream1 on COM2.
 * @param[in] ctx : Click context object.
 * See #mosaic2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void mosaic2_disable_nmea_output ( mosaic2_t *ctx );

/**
 * @brief Mosaic 2 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mosaic2_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // MOSAIC2_H

/*! @} */ // mosaic2

// ------------------------------------------------------------------------ END
