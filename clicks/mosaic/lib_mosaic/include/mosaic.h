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
 * @file mosaic.h
 * @brief This file contains API for Mosaic Click Driver.
 */

#ifndef MOSAIC_H
#define MOSAIC_H

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
 * @addtogroup mosaic Mosaic Click Driver
 * @brief API for configuring and manipulating Mosaic Click driver.
 * @{
 */

/**
 * @defgroup mosaic_cmd Mosaic Device Settings
 * @brief Settings for registers of Mosaic Click driver.
 */

/**
 * @addtogroup mosaic_cmd
 * @{
 */

/**
 * @brief Mosaic control commands.
 * @details Specified setting for control commands of Mosaic Click driver.
 */
#define MOSAIC_CMD_SET_NMEA_OUTPUT              "setNMEAOutput"
#define MOSAIC_CMD_GET_NMEA_VERSION             "getNMEAVersion"

/**
 * @brief Mosaic device commands settings.
 * @details Device commands settings of Mosaic Click driver.
 */
#define MOSAIC_PROMPT_CMD                       "COM1>"
#define MOSAIC_PARAM_DELIMITER                  ","
#define MOSAIC_END_CMD                          "\r\n"

/**
 * @brief Mosaic set NMEA output command parameters.
 * @details Specified setting for set NMEA output command parameters of Mosaic Click driver.
 */
#define MOSAIC_SNO_STREAM_1                     "Stream1"
#define MOSAIC_SNO_STREAM_2                     "Stream2"
#define MOSAIC_SNO_STREAM_3                     "Stream3"
#define MOSAIC_SNO_STREAM_4                     "Stream4"
#define MOSAIC_SNO_STREAM_5                     "Stream5"
#define MOSAIC_SNO_STREAM_6                     "Stream6"
#define MOSAIC_SNO_STREAM_7                     "Stream7"
#define MOSAIC_SNO_STREAM_8                     "Stream8"
#define MOSAIC_SNO_STREAM_9                     "Stream9"
#define MOSAIC_SNO_STREAM_10                    "Stream10"
#define MOSAIC_SNO_STREAM_ALL                   "all"
#define MOSAIC_SNO_CD_NONE                      "none"
#define MOSAIC_SNO_CD_COM1                      "COM1"
#define MOSAIC_SNO_MESSAGES_NONE                "none"
#define MOSAIC_SNO_MESSAGES_ALM                 "ALM"
#define MOSAIC_SNO_MESSAGES_DTM                 "DTM"
#define MOSAIC_SNO_MESSAGES_GBS                 "GBS"
#define MOSAIC_SNO_MESSAGES_GGA                 "GGA"
#define MOSAIC_SNO_MESSAGES_GLL                 "GLL"
#define MOSAIC_SNO_MESSAGES_GNS                 "GNS"
#define MOSAIC_SNO_MESSAGES_GRS                 "GRS"
#define MOSAIC_SNO_MESSAGES_GSA                 "GSA"
#define MOSAIC_SNO_MESSAGES_GST                 "GST"
#define MOSAIC_SNO_MESSAGES_GSV                 "GSV"
#define MOSAIC_SNO_MESSAGES_HDT                 "HDT"
#define MOSAIC_SNO_MESSAGES_RMC                 "RMC"
#define MOSAIC_SNO_MESSAGES_ROT                 "ROT"
#define MOSAIC_SNO_MESSAGES_VTG                 "VTG"
#define MOSAIC_SNO_MESSAGES_ZDA                 "ZDA"
#define MOSAIC_SNO_MESSAGES_HRP                 "HRP"
#define MOSAIC_SNO_MESSAGES_LLQ                 "LLQ"
#define MOSAIC_SNO_MESSAGES_RBP                 "RBP"
#define MOSAIC_SNO_MESSAGES_RBV                 "RBV"
#define MOSAIC_SNO_MESSAGES_RBD                 "RBD"
#define MOSAIC_SNO_MESSAGES_AVR                 "AVR"
#define MOSAIC_SNO_MESSAGES_GGK                 "GGK"
#define MOSAIC_SNO_MESSAGES_GFA                 "GFA"
#define MOSAIC_SNO_MESSAGES_GGQ                 "GGQ"
#define MOSAIC_SNO_MESSAGES_LLK                 "LLK"
#define MOSAIC_SNO_MESSAGES_GMP                 "GMP"
#define MOSAIC_SNO_MESSAGES_TXT_BASE            "TXTbase"
#define MOSAIC_SNO_MESSAGES_TFM                 "TFM"
#define MOSAIC_SNO_MESSAGES_SNC                 "SNC"
#define MOSAIC_SNO_MESSAGES_THS                 "THS"
#define MOSAIC_SNO_INTERVAL_OFF                 "off"
#define MOSAIC_SNO_INTERVAL_ON_CHANGE           "OnChange"
#define MOSAIC_SNO_INTERVAL_MSEC10              "msec10"
#define MOSAIC_SNO_INTERVAL_MSEC20              "msec20"
#define MOSAIC_SNO_INTERVAL_MSEC40              "msec40"
#define MOSAIC_SNO_INTERVAL_MSEC50              "msec50"
#define MOSAIC_SNO_INTERVAL_MSEC100             "msec100"
#define MOSAIC_SNO_INTERVAL_MSEC200             "msec200"
#define MOSAIC_SNO_INTERVAL_MSEC500             "msec500"
#define MOSAIC_SNO_INTERVAL_SEC1                "sec1"
#define MOSAIC_SNO_INTERVAL_SEC2                "sec2"
#define MOSAIC_SNO_INTERVAL_SEC5                "sec5"
#define MOSAIC_SNO_INTERVAL_SEC10               "sec10"
#define MOSAIC_SNO_INTERVAL_SEC15               "sec15"
#define MOSAIC_SNO_INTERVAL_SEC30               "sec30"
#define MOSAIC_SNO_INTERVAL_SEC60               "sec60"
#define MOSAIC_SNO_INTERVAL_MIN2                "min2"
#define MOSAIC_SNO_INTERVAL_MIN5                "min5"
#define MOSAIC_SNO_INTERVAL_MIN10               "min10"
#define MOSAIC_SNO_INTERVAL_MIN15               "min15"
#define MOSAIC_SNO_INTERVAL_MIN30               "min30"
#define MOSAIC_SNO_INTERVAL_MIN60               "min60"

/**
 * @brief Mosaic nmea buffer commands.
 * @details Specified nmea buffer commands of Mosaic Click driver.
 */
#define MOSAIC_NMEA_START                       "$"
#define MOSAIC_NMEA_DELIMITER                   ","
#define MOSAIC_NMEA_END                         "\r\n"
#define MOSAIC_NMEA_GGA                         "GGA"

/**
 * @brief Mosaic GGA command elements.
 * @details Specified GGA command elements of Mosaic Click driver.
 */
#define MOSAIC_GGA_ELEMENT_SIZE                 15
#define MOSAIC_GGA_TIME                         1
#define MOSAIC_GGA_LATITUDE                     2
#define MOSAIC_GGA_LATITUDE_SIDE                3
#define MOSAIC_GGA_LONGITUDE                    4
#define MOSAIC_GGA_LONGITUDE_SIDE               5
#define MOSAIC_GGA_QUALITY_INDICATOR            6
#define MOSAIC_GGA_NUMBER_OF_SATELLITES         7
#define MOSAIC_GGA_H_DILUTION_OF_POS            8
#define MOSAIC_GGA_ALTITUDE                     9
#define MOSAIC_GGA_ALTITUDE_UNIT                10
#define MOSAIC_GGA_GEOIDAL_SEPARATION           11
#define MOSAIC_GGA_GEOIDAL_SEPARATION_UNIT      12
#define MOSAIC_GGA_TIME_SINCE_LAST_DGPS         13
#define MOSAIC_GGA_DGPS_REFERENCE_STATION_ID    14

/**
 * @brief Mosaic driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define MOSAIC_RX_DRV_BUFFER_SIZE               400
#define MOSAIC_TX_DRV_BUFFER_SIZE               200

/*! @} */ // mosaic_cmd

/**
 * @defgroup mosaic_map Mosaic MikroBUS Map
 * @brief MikroBUS pin mapping of Mosaic Click driver.
 */

/**
 * @addtogroup mosaic_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Mosaic Click to the selected MikroBUS.
 */
#define MOSAIC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rdy = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // mosaic_map
/*! @} */ // mosaic

/**
 * @brief Mosaic Click context object.
 * @details Context object definition of Mosaic Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;      /**< Reset pin (Active low). */
    digital_out_t cts;      /**< Clear to receive data signal pin (Active low). */

    // Input pins
    digital_in_t rdy;       /**< Module ready pin (Active high). */
    digital_in_t rts;       /**< Ready to receive data signal pin (Active low). */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ MOSAIC_RX_DRV_BUFFER_SIZE ];    /**< RX buffer size. */
    uint8_t uart_tx_buffer[ MOSAIC_TX_DRV_BUFFER_SIZE ];    /**< TX buffer size. */

} mosaic_t;

/**
 * @brief Mosaic Click configuration object.
 * @details Configuration object definition of Mosaic Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;         /**< Reset pin (Active low). */
    pin_name_t cts;         /**< Clear to receive data signal pin (Active low). */
    pin_name_t rdy;         /**< Module ready pin (Active high). */
    pin_name_t rts;         /**< Ready to receive data signal pin (Active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} mosaic_cfg_t;

/**
 * @brief Mosaic Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MOSAIC_OK = 0,
    MOSAIC_ERROR = -1,
    MOSAIC_ERROR_TIMEOUT = -2

} mosaic_return_value_t;

/*!
 * @addtogroup mosaic Mosaic Click Driver
 * @brief API for configuring and manipulating Mosaic Click driver.
 * @{
 */

/**
 * @brief Mosaic configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mosaic_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mosaic_cfg_setup ( mosaic_cfg_t *cfg );

/**
 * @brief Mosaic initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mosaic_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mosaic_init ( mosaic_t *ctx, mosaic_cfg_t *cfg );

/**
 * @brief Mosaic data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mosaic_generic_write ( mosaic_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Mosaic data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mosaic_generic_read ( mosaic_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Mosaic set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void mosaic_set_rst_pin ( mosaic_t *ctx, uint8_t state );

/**
 * @brief Mosaic set cts pin function.
 * @details This function sets the CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void mosaic_set_cts_pin ( mosaic_t *ctx, uint8_t state );

/**
 * @brief Mosaic get rdy pin function.
 * @details This function returns the module ready indication (RDY) pin logic state.
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t mosaic_get_rdy_pin ( mosaic_t *ctx );

/**
 * @brief Mosaic get rts pin function.
 * @details This function returns the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t mosaic_get_rts_pin ( mosaic_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 * @note None.
 */
void mosaic_send_cmd ( mosaic_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @param[in] cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void mosaic_send_cmd_with_par ( mosaic_t *ctx, uint8_t *cmd_buf, uint8_t *param_buf );

/**
 * @brief Mosaic enable nmea output function.
 * @details This function enables the NMEA output with the selected message parameters and an output interval.
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @param[in] msg_param : Message parameter, see MOSAIC_SNO_MESSAGES_x macro definisions.
 * @param[in] interval : Output interval, see MOSAIC_SNO_INTERVAL_x macro definisions.
 * @return Nothing.
 * @note None.
 */
void mosaic_enable_nmea_output ( mosaic_t *ctx, uint8_t *msg_param, uint8_t *interval );

/**
 * @brief Mosaic disable nmea output function.
 * @details This function disables the NMEA output for Stream1 on COM1.
 * @param[in] ctx : Click context object.
 * See #mosaic_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void mosaic_disable_nmea_output ( mosaic_t *ctx );

/**
 * @brief Mosaic parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mosaic_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // MOSAIC_H

/*! @} */ // mosaic

// ------------------------------------------------------------------------ END
