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
 * @file lr11868mhz.h
 * @brief This file contains API for LR 11 868MHz Click Driver.
 */

#ifndef LR11868MHZ_H
#define LR11868MHZ_H

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
 * @addtogroup lr11868mhz LR 11 868MHz Click Driver
 * @brief API for configuring and manipulating LR 11 868MHz Click driver.
 * @{
 */

/**
 * @defgroup lr11868mhz_cmd LR 11 868MHz Device Settings
 * @brief Settings for registers of LR 11 868MHz Click driver.
 */

/**
 * @addtogroup lr11868mhz_cmd
 * @{
 */

/**
 * @brief LR 11 868MHz control commands.
 * @details Specified setting for control commands of LR 11 868MHz Click driver.
 */
#define LR11868MHZ_CMD_AT                                   "AT"
#define LR11868MHZ_CMD_FACTORY_RESET                        "AT&F"
#define LR11868MHZ_CMD_SAVE_SETTINGS                        "AT&W"
#define LR11868MHZ_CMD_WARM_RESET                           "ATZ"
#define LR11868MHZ_CMD_GET_INFO                             "ATI"
#define LR11868MHZ_CMD_PARAM_ACCESS_STR                     "AT%S"
#define LR11868MHZ_CMD_PARAM_ACCESS_NUM                     "ATS"
#define LR11868MHZ_CMD_I2C_READ                             "AT+I2R"
#define LR11868MHZ_CMD_I2C_WRITE                            "AT+I2W"
#define LR11868MHZ_CMD_NET_DROP                             "AT+DROP"
#define LR11868MHZ_CMD_NET_JOIN                             "AT+JOIN"
#define LR11868MHZ_CMD_NET_CHECK_LINK                       "AT+LINKC"
#define LR11868MHZ_CMD_NET_SEND_DATA                        "AT+SEND"
#define LR11868MHZ_CMD_NET_GET_TIME                         "AT+TIME"
#define LR11868MHZ_CMD_GROUP_CREATE                         "AT+MCGA"
#define LR11868MHZ_CMD_GROUP_REMOVE                         "AT+MCGR"
#define LR11868MHZ_CMD_GROUP_START                          "AT+MCGS"
#define LR11868MHZ_CMD_GROUP_END                            "AT+MCGE"
#define LR11868MHZ_CMD_GROUP_LIST                           "AT+MCGL"
#define LR11868MHZ_CMD_P2P_END_SESSION                      "AT+P2PE"
#define LR11868MHZ_CMD_P2P_START_SESSION                    "AT+P2PS"
#define LR11868MHZ_CMD_P2P_SEND_DATA                        "AT+P2PT"
#define LR11868MHZ_CMD_SIO_CONFIG                           "AT+SIOC"
#define LR11868MHZ_CMD_SIO_READ                             "AT+SIOR"
#define LR11868MHZ_CMD_SIO_WRITE                            "AT+SIOW"
#define LR11868MHZ_CMD_SPI_READ                             "AT+SPR"
#define LR11868MHZ_CMD_SPI_WRITE                            "AT+SPW"

/**
 * @brief LR 11 868MHz get info (ATI) command parameters.
 * @details Specified setting for get info (ATI) command parameters of LR 11 868MHz Click driver.
 */
#define LR11868MHZ_PARAM_DEVICE_TYPE                        "0"
#define LR11868MHZ_PARAM_APP_FW_VERSION                     "3"
#define LR11868MHZ_PARAM_APP_STATE                          "42"
#define LR11868MHZ_PARAM_MIN_BAUD_RATE                      "1002"
#define LR11868MHZ_PARAM_MAX_BAUD_RATE                      "1003"
#define LR11868MHZ_PARAM_RESET_REASON                       "2000"
#define LR11868MHZ_PARAM_RESET_CAUSE                        "2001"
#define LR11868MHZ_PARAM_TX_POWER                           "2008"
#define LR11868MHZ_PARAM_RADIO_ACTIVITY                     "2016"
#define LR11868MHZ_PARAM_BANDWIDTH                          "3000"
#define LR11868MHZ_PARAM_CONNECTION_STATUS                  "3001"
#define LR11868MHZ_PARAM_DEVICE_ADDRESS                     "3002"
#define LR11868MHZ_PARAM_BOOTLOADER_VERSION                 "3003"
#define LR11868MHZ_PARAM_MODULATION_TYPE                    "3004"
#define LR11868MHZ_PARAM_MODULE_TYPE                        "3005"
#define LR11868MHZ_PARAM_PACKETS_RXED                       "3006"
#define LR11868MHZ_PARAM_PACKETS_TXED                       "3007"
#define LR11868MHZ_PARAM_RSSI                               "3008"
#define LR11868MHZ_PARAM_SNR                                "3009"
#define LR11868MHZ_PARAM_SPREADING_FACTOR                   "3010"
#define LR11868MHZ_PARAM_P2P_BEACON_TOA                     "4000"
#define LR11868MHZ_PARAM_P2P_BEACON_SETTLE_TIME             "4001"
#define LR11868MHZ_PARAM_P2P_SLOT_TOA                       "4002"
#define LR11868MHZ_PARAM_P2P_SLOT_PACKET_SIZE               "4003"
#define LR11868MHZ_PARAM_P2P_SLOT_DELAY                     "4004"
#define LR11868MHZ_PARAM_P2P_MIN_WINDOW_LENGTH              "4005"
#define LR11868MHZ_PARAM_P2P_MAX_SLOTS_PER_WINDOW           "4006"

/**
 * @brief LR 11 868MHz param access string (AT%S) command parameters ID.
 * @details Specified setting for param access string (AT%S) command parameters ID of LR 11 868MHz Click driver.
 */
#define LR11868MHZ_PARAM_ID_DEVICE_NAME                     "0"
#define LR11868MHZ_PARAM_ID_APP_KEY                         "500"
#define LR11868MHZ_PARAM_ID_DEV_EUI                         "501"
#define LR11868MHZ_PARAM_ID_JOIN_EUI                        "502"
#define LR11868MHZ_PARAM_ID_ABP_P2P_ADDRESS                 "635"
#define LR11868MHZ_PARAM_ID_ABP_P2P_NET_KEY                 "636"
#define LR11868MHZ_PARAM_ID_ABP_P2P_APP_KEY                 "637"

/**
 * @brief LR 11 868MHz param access numeric (ATS) command parameters ID.
 * @details Specified setting for param access numeric (ATS) command parameters ID of LR 11 868MHz Click driver.
 */
#define LR11868MHZ_PARAM_ID_START_FLAGS                     "100"
#define LR11868MHZ_PARAM_ID_SIO_NET                         "117"
#define LR11868MHZ_PARAM_ID_UART_IDLE_TIME                  "213"
#define LR11868MHZ_PARAM_ID_CORE_VOLTAGE                    "217"
#define LR11868MHZ_PARAM_ID_UART_BAUD_RATE                  "302"
#define LR11868MHZ_PARAM_ID_ADR_ENABLED                     "600"
#define LR11868MHZ_PARAM_ID_BEACON_FREQ                     "601"
#define LR11868MHZ_PARAM_ID_ACTIVATION_MODE                 "602"
#define LR11868MHZ_PARAM_ID_DEVICE_CLASS                    "603"
#define LR11868MHZ_PARAM_ID_CONFIRMED_PACKETS               "604"
#define LR11868MHZ_PARAM_ID_CONFIRMED_RETRY_COUNT           "605"
#define LR11868MHZ_PARAM_ID_JOIN_DELAY                      "606"
#define LR11868MHZ_PARAM_ID_JOIN_JITTER                     "607"
#define LR11868MHZ_PARAM_ID_PING_SLOT_PERIODICITY           "609"
#define LR11868MHZ_PARAM_ID_REGION                          "611"
#define LR11868MHZ_PARAM_ID_REQUEST_COUNT                   "612"
#define LR11868MHZ_PARAM_ID_RX1_DELAY                       "613"
#define LR11868MHZ_PARAM_ID_SUB_BAND                        "617"
#define LR11868MHZ_PARAM_ID_APP_PORT                        "629"
#define LR11868MHZ_PARAM_ID_CLASS_C_SCAN_TIME               "633"
#define LR11868MHZ_PARAM_ID_P2P_DEVICE_ADDRESS              "700"
#define LR11868MHZ_PARAM_ID_P2P_NET_SIZE                    "701"
#define LR11868MHZ_PARAM_ID_P2P_WINDOW_LENGTH               "702"
#define LR11868MHZ_PARAM_ID_P2P_DATA_RATE                   "703"
#define LR11868MHZ_PARAM_ID_P2P_LISTEN_DURATION             "704"
#define LR11868MHZ_PARAM_ID_P2P_LISTEN_INTERVAL             "705"
#define LR11868MHZ_PARAM_ID_P2P_BEACON_DATA_RATE            "706"
#define LR11868MHZ_PARAM_ID_P2P_PACKET_SIZE                 "707"
#define LR11868MHZ_PARAM_ID_P2P_TX_POWER                    "708"
#define LR11868MHZ_PARAM_ID_PUBLIC_MODE                     "709"
#define LR11868MHZ_PARAM_ID_SLOTS_PER_WINDOW                "710"

/**
 * @brief LR 11 868MHz device response for AT commands.
 * @details Device response after commands.
 */
#define LR11868MHZ_RSP_OK                                   "OK"
#define LR11868MHZ_RSP_ERROR                                "ERROR"

/**
 * @brief LR 11 868MHz device events settings.
 * @details Device events settings.
 */
#define LR11868MHZ_EVT_CLASS                                "CLASS "
#define LR11868MHZ_EVT_JOIN                                 "JOIN ["
#define LR11868MHZ_EVT_LINK_CHECK                           "LC S:"
#define LR11868MHZ_EVT_RX_LNS                               "RX: W:"
#define LR11868MHZ_EVT_RX_P2P                               "RX: [P2P] S:"
#define LR11868MHZ_EVT_TIME                                 "TIME ["
#define LR11868MHZ_EVT_TX                                   "TX ["
#define LR11868MHZ_EVT_WAKE                                 "WAKE"

/**
 * @brief LR 11 868MHz driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LR11868MHZ_TX_DRV_BUFFER_SIZE                       200
#define LR11868MHZ_RX_DRV_BUFFER_SIZE                       600

/*! @} */ // lr11868mhz_cmd

/**
 * @defgroup lr11868mhz_map LR 11 868MHz MikroBUS Map
 * @brief MikroBUS pin mapping of LR 11 868MHz Click driver.
 */

/**
 * @addtogroup lr11868mhz_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LR 11 868MHz Click to the selected MikroBUS.
 */
#define LR11868MHZ_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lr11868mhz_map
/*! @} */ // lr11868mhz

/**
 * @brief LR 11 868MHz Click context object.
 * @details Context object definition of LR 11 868MHz Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< Clear to send pin. */

    // Input pins
    digital_in_t rts;               /**< Ready to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LR11868MHZ_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LR11868MHZ_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LR11868MHZ_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} lr11868mhz_t;

/**
 * @brief LR 11 868MHz Click configuration object.
 * @details Configuration object definition of LR 11 868MHz Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cts;                 /**< Clear to send pin. */
    pin_name_t rts;                 /**< Ready to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} lr11868mhz_cfg_t;

/**
 * @brief LR 11 868MHz Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LR11868MHZ_OK = 0,
    LR11868MHZ_ERROR = -1,
    LR11868MHZ_ERROR_TIMEOUT = -2,
    LR11868MHZ_ERROR_CMD = -3

} lr11868mhz_return_value_t;

/*!
 * @addtogroup lr11868mhz LR 11 868MHz Click Driver
 * @brief API for configuring and manipulating LR 11 868MHz Click driver.
 * @{
 */

/**
 * @brief LR 11 868MHz configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lr11868mhz_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lr11868mhz_cfg_setup ( lr11868mhz_cfg_t *cfg );

/**
 * @brief LR 11 868MHz initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lr11868mhz_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lr11868mhz_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr11868mhz_init ( lr11868mhz_t *ctx, lr11868mhz_cfg_t *cfg );

/**
 * @brief LR 11 868MHz data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr11868mhz_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr11868mhz_generic_write ( lr11868mhz_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LR 11 868MHz data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr11868mhz_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr11868mhz_generic_read ( lr11868mhz_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LR 11 868MHz set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr11868mhz_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lr11868mhz_set_rst_pin ( lr11868mhz_t *ctx, uint8_t state );

/**
 * @brief LR 11 868MHz reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr11868mhz_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lr11868mhz_reset_device ( lr11868mhz_t *ctx );

/**
 * @brief LR 11 868MHz set CTS pin function.
 * @details This function sets the clear to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr11868mhz_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lr11868mhz_set_cts_pin ( lr11868mhz_t *ctx, uint8_t state );

/**
 * @brief LR 11 868MHz get RTS pin function.
 * @details This function returns the ready to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr11868mhz_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t lr11868mhz_get_rts_pin ( lr11868mhz_t *ctx );

/**
 * @brief LR 11 868MHz cmd run function.
 * @details This function sends a specified command with or without parameters to the Click module.
 * @param[in] ctx : Click context object.
 * See #lr11868mhz_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param : Parameters string (NULL - if the command doesn't need parameters).
 * @return None.
 * @note None.
 */
void lr11868mhz_cmd_run ( lr11868mhz_t *ctx, uint8_t *cmd, uint8_t *param );

/**
 * @brief LR 11 868MHz cmd set function.
 * @details This function sets a value to a specified command parameter of the Click module.
 * @param[in] ctx : Click context object.
 * See #lr11868mhz_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param_id : Command parameter ID string.
 * @param[in] value : Value string.
 * @return None.
 * @note Used only for LR11868MHZ_PARAM_ACCESS_x commands.
 */
void lr11868mhz_cmd_set ( lr11868mhz_t *ctx, uint8_t *cmd, uint8_t *param_id, uint8_t *value );

/**
 * @brief LR 11 868MHz cmd get function.
 * @details This function is used to get the value of a given command parameter from the Click module.
 * @param[in] ctx : Click context object.
 * See #lr11868mhz_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param_id : Command parameter ID string.
 * @return None.
 * @note Used only for LR11868MHZ_PARAM_ACCESS_x commands.
 */
void lr11868mhz_cmd_get ( lr11868mhz_t *ctx, uint8_t *cmd, uint8_t *param_id );

/**
 * @brief LR 11 868MHz cmd help function.
 * @details This function provides a short description of the given command parameter of the Click module.
 * @param[in] ctx : Click context object.
 * See #lr11868mhz_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param_id : Command parameter ID string.
 * @return None.
 * @note Used only for LR11868MHZ_PARAM_ACCESS_x commands.
 */
void lr11868mhz_cmd_help ( lr11868mhz_t *ctx, uint8_t *cmd, uint8_t *param_id );

#ifdef __cplusplus
}
#endif
#endif // LR11868MHZ_H

/*! @} */ // lr11868mhz

// ------------------------------------------------------------------------ END
