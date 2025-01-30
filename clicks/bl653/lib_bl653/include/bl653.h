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
 * @file bl653.h
 * @brief This file contains API for BL653 Click Driver.
 */

#ifndef BL653_H
#define BL653_H

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
 * @addtogroup bl653 BL653 Click Driver
 * @brief API for configuring and manipulating BL653 Click driver.
 * @{
 */

/**
 * @defgroup bl653_cmd BL653 Device Settings
 * @brief Settings for registers of BL653 Click driver.
 */

/**
 * @addtogroup bl653_cmd
 * @{
 */

/**
 * @brief BL653 control commands.
 * @details Specified setting for control commands of BL653 Click driver.
 */
#define BL653_CMD_VSP_ESCAPE_CHAR                   "^"
#define BL653_CMD_AT                                "AT"
#define BL653_CMD_FACTORY_RESET                     "AT&F"
#define BL653_CMD_SAVE_SETTINGS                     "AT&W"
#define BL653_CMD_WARM_RESET                        "ATZ"
#define BL653_CMD_GET_INFO                          "ATI"
#define BL653_CMD_PARAM_ACCESS_STR                  "AT%S"
#define BL653_CMD_PARAM_ACCESS_NUM                  "ATS"
#define BL653_CMD_DISCONNECT                        "AT+LDSC"
#define BL653_CMD_SIO_CONFIG                        "AT+SIOC"
#define BL653_CMD_SIO_READ                          "AT+SIOR"
#define BL653_CMD_SIO_WRITE                         "AT+SIOW"

/**
 * @brief BL653 get info (ATI) command parameters.
 * @details Specified setting for get info (ATI) command parameters of BL653 Click driver.
 */
#define BL653_PARAM_DEVICE_TYPE                     "0"
#define BL653_PARAM_FW_VERSION                      "3"
#define BL653_PARAM_BT_ADDRESS                      "4"
#define BL653_PARAM_MANUFACTURER                    "10"
#define BL653_PARAM_CHECK_POWER_MODE                "11"
#define BL653_PARAM_SMARTBASIC_VERSION              "23"
#define BL653_PARAM_SMARTBASIC_VERSION_USER         "33"
#define BL653_PARAM_APP_STATE                       "42"
#define BL653_PARAM_NFC_COIL_EVENTS_COUNT           "50"
#define BL653_PARAM_NFC_TAG_READ_COUNT              "51"
#define BL653_PARAM_NUM_TRUSTED_DEVICES             "2009"
#define BL653_PARAM_MAX_NUM_TRUSTED_DEVICES         "2012"

/**
 * @brief BL653 param access string (AT%S) command parameters ID.
 * @details Specified setting for param access string (AT%S) command parameters ID of BL653 Click driver.
 */
#define BL653_PARAM_ID_DEVICE_NAME                  "0"
#define BL653_PARAM_ID_VSP_UUID                     "1"
#define BL653_PARAM_ID_SCAN_PATTERN                 "2"

/**
 * @brief BL653 param access numeric (ATS) command parameters ID.
 * @details Specified setting for param access numeric (ATS) command parameters ID of BL653 Click driver.
 */
#define BL653_PARAM_ID_START_FLAGS                  "100"
#define BL653_PARAM_ID_TX_POWER_DBM                 "101"
#define BL653_PARAM_ID_VSP_ENCRYPTION               "102"
#define BL653_PARAM_ID_DEVICE_NAME_FORMAT           "103"
#define BL653_PARAM_ID_SLAVE_LATENCY                "104"
#define BL653_PARAM_ID_FLAGS_AD                     "105"
#define BL653_PARAM_ID_SCAN_TIMEOUT_S               "106"
#define BL653_PARAM_ID_IO_CAPABILITY                "107"
#define BL653_PARAM_ID_IDLE_ADVERT_TYPE             "108"
#define BL653_PARAM_ID_VSP_CMD_MODE_PIN             "109"
#define BL653_PARAM_ID_CONN_TIMEOUT_S               "110"
#define BL653_PARAM_ID_NUM_CHARS_TO_DISC            "111"
#define BL653_PARAM_ID_SCAN_TYPE                    "112"
#define BL653_PARAM_ID_SCAN_RSSI_MIN_DBM            "113"
#define BL653_PARAM_ID_LINK_TIMEOUT_S_SLAVE         "114"
#define BL653_PARAM_ID_MIN_ENCRYPTION_KEY_LEN       "115"
#define BL653_PARAM_ID_MITM                         "116"
#define BL653_PARAM_ID_VSP_DCD_OUT                  "117"
#define BL653_PARAM_ID_VSP_MAX_CACHED_PACKETS       "118"
#define BL653_PARAM_ID_MAX_CONN_AS_MASTER           "126"
#define BL653_PARAM_ID_BLE_TX_BUFFERS               "127"
#define BL653_PARAM_ID_CONN_IND_PIN_POL             "137"
#define BL653_PARAM_ID_CONN_IND_PIN                 "138"
#define BL653_PARAM_ID_ENC_CONN_IND_PIN             "139"
#define BL653_PARAM_ID_VSP_ENC_DISC_TIMEOUT         "200"
#define BL653_PARAM_ID_VSP_ADVERT_INTERVAL          "201"
#define BL653_PARAM_ID_UART_TX_BUFFER_SIZE          "202"
#define BL653_PARAM_ID_UART_RX_BUFFER_SIZE          "203"
#define BL653_PARAM_ID_VSP_TX_BUFFER_SIZE           "204"
#define BL653_PARAM_ID_VSP_RX_BUFFER_SIZE           "205"
#define BL653_PARAM_ID_LINK_TIMEOUT_MS              "206"
#define BL653_PARAM_ID_APPEARANCE                   "207"
#define BL653_PARAM_ID_IDLE_ADVERT_INTERVAL_MS      "208"
#define BL653_PARAM_ID_GATT_CLIENT_MEM_SIZE         "209"
#define BL653_PARAM_ID_VSP_ESCAPE_CHAR_DELAY        "210"
#define BL653_PARAM_ID_SCAN_INVERVAL_MS             "211"
#define BL653_PARAM_ID_SCAN_WINDOW_MS               "212"
#define BL653_PARAM_ID_UART_IDLE_TIME_MS            "213"
#define BL653_PARAM_ID_DLE_ATTR_SIZE                "219"
#define BL653_PARAM_ID_MIN_CONN_INTERVAL_US         "300"
#define BL653_PARAM_ID_MAX_CONN_INTERVAL_US         "301"
#define BL653_PARAM_ID_UART_BAUD_RATE               "302"
#define BL653_PARAM_ID_VSP_TX_UUID                  "303"
#define BL653_PARAM_ID_VSP_RX_UUID                  "304"
#define BL653_PARAM_ID_VSP_MDM_IN_UUID              "305"
#define BL653_PARAM_ID_VSP_MDM_OUT_UUID             "306"
#define BL653_PARAM_ID_BLE_CONN_EVENT_LEN           "307"

/**
 * @brief BL653 device response for AT commands.
 * @details Device response after commands.
 */
#define BL653_RSP_OK                                "OK"
#define BL653_RSP_ERROR                             "ERROR"
#define BL653_RSP_CONNECT                           "CONNECT"
#define BL653_RSP_NO_CARRIER                        "NOCARRIER"
#define BL653_RSP_RING                              "RING"

/**
 * @brief BL653 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BL653_TX_DRV_BUFFER_SIZE                    200
#define BL653_RX_DRV_BUFFER_SIZE                    600

/*! @} */ // bl653_cmd

/**
 * @defgroup bl653_map BL653 MikroBUS Map
 * @brief MikroBUS pin mapping of BL653 Click driver.
 */

/**
 * @addtogroup bl653_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BL653 Click to the selected MikroBUS.
 */
#define BL653_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.arn = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // bl653_map
/*! @} */ // bl653

/**
 * @brief BL653 Click context object.
 * @details Context object definition of BL653 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t arn;              /**< Application autorun pin (active low on POR). */
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< UART clear to send pin. */

    // Input pins
    digital_in_t rts;               /**< UART ready to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BL653_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ BL653_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ BL653_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} bl653_t;

/**
 * @brief BL653 Click configuration object.
 * @details Configuration object definition of BL653 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t arn;                 /**< Application autorun pin (active low on POR). */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cts;                 /**< UART clear to send pin. */
    pin_name_t rts;                 /**< UART ready to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} bl653_cfg_t;

/**
 * @brief BL653 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BL653_OK = 0,
    BL653_ERROR = -1,
    BL653_ERROR_TIMEOUT = -2,
    BL653_ERROR_CMD = -3

} bl653_return_value_t;

/*!
 * @addtogroup bl653 BL653 Click Driver
 * @brief API for configuring and manipulating BL653 Click driver.
 * @{
 */

/**
 * @brief BL653 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bl653_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bl653_cfg_setup ( bl653_cfg_t *cfg );

/**
 * @brief BL653 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bl653_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bl653_init ( bl653_t *ctx, bl653_cfg_t *cfg );

/**
 * @brief BL653 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bl653_generic_write ( bl653_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief BL653 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bl653_generic_read ( bl653_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief BL653 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bl653_set_rst_pin ( bl653_t *ctx, uint8_t state );

/**
 * @brief BL653 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bl653_reset_device ( bl653_t *ctx );

/**
 * @brief BL653 set ARN pin function.
 * @details This function sets the autorun pin logic state.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bl653_set_arn_pin ( bl653_t *ctx, uint8_t state );

/**
 * @brief BL653 set CTS pin function.
 * @details This function sets the clear to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bl653_set_cts_pin ( bl653_t *ctx, uint8_t state );

/**
 * @brief BL653 get RTS pin function.
 * @details This function returns the ready to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t bl653_get_rts_pin ( bl653_t *ctx );

/**
 * @brief BL653 cmd run function.
 * @details This function sends a specified command with or without parameters to the Click module.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param : Parameters string (NULL - if the command doesn't need parameters).
 * @return None.
 * @note None.
 */
void bl653_cmd_run ( bl653_t *ctx, uint8_t *cmd, uint8_t *param );

/**
 * @brief BL653 cmd set function.
 * @details This function sets a value to a specified command parameter of the Click module.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param_id : Command parameter ID string.
 * @param[in] value : Value string.
 * @return None.
 * @note Used only for BL653_PARAM_ACCESS_x commands.
 */
void bl653_cmd_set ( bl653_t *ctx, uint8_t *cmd, uint8_t *param_id, uint8_t *value );

/**
 * @brief BL653 cmd get function.
 * @details This function is used to get the value of a given command parameter from the Click module.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param_id : Command parameter ID string.
 * @return None.
 * @note Used only for BL653_PARAM_ACCESS_x commands.
 */
void bl653_cmd_get ( bl653_t *ctx, uint8_t *cmd, uint8_t *param_id );

/**
 * @brief BL653 cmd help function.
 * @details This function provides a short description of the given command parameter of the Click module.
 * @param[in] ctx : Click context object.
 * See #bl653_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param_id : Command parameter ID string.
 * @return None.
 * @note Used only for BL653_PARAM_ACCESS_x commands.
 */
void bl653_cmd_help ( bl653_t *ctx, uint8_t *cmd, uint8_t *param_id );

#ifdef __cplusplus
}
#endif
#endif // BL653_H

/*! @} */ // bl653

// ------------------------------------------------------------------------ END
