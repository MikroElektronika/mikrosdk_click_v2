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
 * @file ethwiz3.h
 * @brief This file contains API for ETH WIZ 3 Click Driver.
 */

#ifndef ETHWIZ3_H
#define ETHWIZ3_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup ETH WIZ 3 ETH WIZ 3 Click Driver
 * @brief API for configuring and manipulating ETH WIZ 3 Click driver.
 * @{
 */

/**
 * @defgroup ethwiz3_cmd ETH WIZ 3 Device Settings
 * @brief Settings for commands of ETH WIZ 3 Click driver.
 */

/**
 * @addtogroup ethwiz3_cmd
 * @{
 */

/**
 * @brief ETH WIZ 3 control commands.
 * @details Specified setting for control commands of ETH WIZ 3 Click driver.
 */
#define ETHWIZ3_CMD_MAC_ADDRESS                 "MC"
#define ETHWIZ3_CMD_FIRMWARE_VERSION            "VR"
#define ETHWIZ3_CMD_PRODUCT_NAME                "MN"
#define ETHWIZ3_CMD_OPERATION_STATUS            "ST"
#define ETHWIZ3_CMD_UART_INTERFACE_STR          "UN"
#define ETHWIZ3_CMD_UART_INTERFACE_CODE         "UI"
#define ETHWIZ3_CMD_NETWORK_OPERATION_MODE      "OP"
#define ETHWIZ3_CMD_IP_ADDRESS_METHOD           "IM"
#define ETHWIZ3_CMD_LOCAL_IP                    "LI"
#define ETHWIZ3_CMD_SUBNET_MASK                 "SM"
#define ETHWIZ3_CMD_GATEWAY_ADDRESS             "GW"
#define ETHWIZ3_CMD_DNS_SERVER_ADDRESS          "DS"
#define ETHWIZ3_CMD_LOCAL_PORT                  "LP"
#define ETHWIZ3_CMD_REMOTE_IP                   "RH"
#define ETHWIZ3_CMD_REMOTE_PORT                 "RP"
#define ETHWIZ3_CMD_UART_BAUD                   "BR"
#define ETHWIZ3_CMD_UART_DATA_BIT               "DB"
#define ETHWIZ3_CMD_UART_PARITY_BIT             "PR"
#define ETHWIZ3_CMD_UART_STOP_BIT               "SB"
#define ETHWIZ3_CMD_UART_FLOW_CONTROL           "FL"
#define ETHWIZ3_CMD_UART_ECHOBACK_EN            "EC"
#define ETHWIZ3_CMD_TIME_DELIMITER              "PT"
#define ETHWIZ3_CMD_SIZE_DELIMITER              "PS"
#define ETHWIZ3_CMD_CHAR_DELIMITER              "PD"
#define ETHWIZ3_CMD_INACTIVITY_TIMER            "IT"
#define ETHWIZ3_CMD_TCP_RECONNECTION_INTERVAL   "RI"
#define ETHWIZ3_CMD_CONNECTION_PASSWORD_EN      "CP"
#define ETHWIZ3_CMD_CONNECTION_PASSWORD         "NP"
#define ETHWIZ3_CMD_SEARCH_ID_CODE              "SP"
#define ETHWIZ3_CMD_SERIAL_DEBUG_MSG_EN         "DG"
#define ETHWIZ3_CMD_TCP_KEEP_EN                 "KA"
#define ETHWIZ3_CMD_TCP_KEEP_INIT_INTERVAL      "KI"
#define ETHWIZ3_CMD_TCP_KEEP_RETRY_INTERVAL     "KE"
#define ETHWIZ3_CMD_SSL_RX_TIMEOUT              "SO"
#define ETHWIZ3_CMD_SELECT_MODBUS_TYPE          "PO"
#define ETHWIZ3_CMD_MQTT_USERNAME               "QU"
#define ETHWIZ3_CMD_MQTT_PASSWORD               "QP"
#define ETHWIZ3_CMD_MQTT_CLIENT_ID              "QC"
#define ETHWIZ3_CMD_MQTT_KEEP                   "QK"
#define ETHWIZ3_CMD_MQTT_PUBLISH_TOPIC          "PU"
#define ETHWIZ3_CMD_MQTT_SUB_TOPIC_1            "U0"
#define ETHWIZ3_CMD_MQTT_SUB_TOPIC_2            "U1"
#define ETHWIZ3_CMD_MQTT_SUB_TOPIC_3            "U2"
#define ETHWIZ3_CMD_MQTT_QOS_LEVEL              "QO"
#define ETHWIZ3_CMD_ROOT_CA_VERIFY_OPTION       "RC"
#define ETHWIZ3_CMD_CLIENT_CERTIFICATE_EN       "CE"
#define ETHWIZ3_CMD_ROOT_CA                     "OC"
#define ETHWIZ3_CMD_CLIENT_CERTIFICATE          "LC"
#define ETHWIZ3_CMD_PRIVATE_KEY                 "PK"
#define ETHWIZ3_CMD_CMD_MODE_SWITCH_CODE_EN     "TE"
#define ETHWIZ3_CMD_CMD_MODE_SWITCH_CODE        "SS"
#define ETHWIZ3_CMD_CMD_MODE_EXIT               "EX"
#define ETHWIZ3_CMD_SAVE_SETTINGS               "SV"
#define ETHWIZ3_CMD_DEVICE_REBOOT               "RT"
#define ETHWIZ3_CMD_DEVICE_FACTORY_RESET        "FR"
#define ETHWIZ3_CMD_STATUS_S0_S1                "SC"
#define ETHWIZ3_CMD_STATUS_S0                   "S0"
#define ETHWIZ3_CMD_STATUS_S1                   "S1"

/**
 * @brief ETH WIZ 3 network operation mode settings.
 * @details Specified setting for network operation mode of ETH WIZ 3 Click driver.
 */
#define ETHWIZ3_OP_MODE_TCP_CLIENT              "0"
#define ETHWIZ3_OP_MODE_TCP_SERVER              "1"
#define ETHWIZ3_OP_MODE_TCP_MIXED               "2"
#define ETHWIZ3_OP_MODE_UDP                     "3"
#define ETHWIZ3_OP_MODE_SSL_TCP_CLIENT          "4"
#define ETHWIZ3_OP_MODE_MQTT_CLIENT             "5"
#define ETHWIZ3_OP_MODE_MQTTS_CLIENT            "6"

/**
 * @brief ETH WIZ 3 IP Address allocation method settings.
 * @details Specified setting for IP Address allocation method of ETH WIZ 3 Click driver.
 */
#define ETHWIZ3_IM_STATIC                       "0"
#define ETHWIZ3_IM_DHCP                         "1"

/**
 * @brief ETH WIZ 3 SPI setting.
 * @details Specified setting for SPI of ETH WIZ 3 Click driver.
 */
#define ETHWIZ3_TIMEOUT_MS                      2000
#define ETHWIZ3_SPI_DUMMY                       0xFF
#define ETHWIZ3_SPI_ACK                         0x0A
#define ETHWIZ3_SPI_NACK                        0x0B
#define ETHWIZ3_SPI_WRITE                       0xA0
#define ETHWIZ3_SPI_READ                        0xB0
#define ETHWIZ3_SPI_READ_LEN                    0xB1

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b ethwiz3_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define ETHWIZ3_SET_DATA_SAMPLE_EDGE            SET_SPI_DATA_SAMPLE_EDGE
#define ETHWIZ3_SET_DATA_SAMPLE_MIDDLE          SET_SPI_DATA_SAMPLE_MIDDLE

/**
 * @brief ETH WIZ 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define ETHWIZ3_TX_DRV_BUFFER_SIZE              200
#define ETHWIZ3_RX_DRV_BUFFER_SIZE              1000

/*! @} */ // ethwiz3_cmd

/**
 * @defgroup ethwiz3_map ETH WIZ 3 MikroBUS Map
 * @brief MikroBUS pin mapping of ETH WIZ 3 Click driver.
 */

/**
 * @addtogroup ethwiz3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ETH WIZ 3 Click to the selected MikroBUS.
 */
#define ETHWIZ3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cts  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.atm  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.tcp  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ethwiz3_map
/*! @} */ // ethwiz3

/**
 * @brief ETH WIZ 3 Click driver selector.
 * @details Selects target driver interface of ETH WIZ 3 Click driver.
 */
typedef enum
{
    ETHWIZ3_DRV_SEL_SPI,            /**< SPI driver descriptor. */
    ETHWIZ3_DRV_SEL_UART            /**< UART driver descriptor. */

} ethwiz3_drv_t;

/**
 * @brief ETH WIZ 3 Click context object.
 * @details Context object definition of ETH WIZ 3 Click driver.
 */
typedef struct ethwiz3_s
{
    digital_out_t atm;              /**< AT mode pin (active low). */
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< UART CTS or SPI chip select pin. */

    digital_in_t tcp;               /**< TCP connection active pin. */
    digital_in_t rts;               /**< UART RTS or SPI interrupt pin. */

    uart_t uart;                    /**< UART driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    ethwiz3_drv_t drv_sel;          /**< Master driver interface selector. */

    uint8_t uart_rx_buffer[ ETHWIZ3_RX_DRV_BUFFER_SIZE ];   /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ ETHWIZ3_TX_DRV_BUFFER_SIZE ];   /**< TX Buffer size. */

} ethwiz3_t;

/**
 * @brief ETH WIZ 3 Click configuration object.
 * @details Configuration object definition of ETH WIZ 3 Click driver.
 */
typedef struct
{
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cts;                 /**< UART CTS or SPI chip select pin. */
    pin_name_t atm;                 /**< AT mode pin (active low). */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t tcp;                 /**< TCP connection active pin. */
    pin_name_t rts;                 /**< UART RTS or SPI interrupt pin. */

    uint32_t          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t spi_mode;     /**< SPI master mode. */
    
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

    ethwiz3_drv_t drv_sel;          /**< Master driver interface selector. */

} ethwiz3_cfg_t;

/**
 * @brief ETH WIZ 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ETHWIZ3_OK = 0,
    ETHWIZ3_ERROR = -1,
    ETHWIZ3_ERROR_TIMEOUT = -2

} ethwiz3_return_value_t;

/*!
 * @addtogroup ETH WIZ 3 ETH WIZ 3 Click Driver
 * @brief API for configuring and manipulating ETH WIZ 3 Click driver.
 * @{
 */

/**
 * @brief ETH WIZ 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ethwiz3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ethwiz3_cfg_setup ( ethwiz3_cfg_t *cfg );

/**
 * @brief ETH WIZ 3 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #ethwiz3_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #ethwiz3_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void ethwiz3_drv_interface_sel ( ethwiz3_cfg_t *cfg, ethwiz3_drv_t drv_sel );

/**
 * @brief ETH WIZ 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ethwiz3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ethwiz3_init ( ethwiz3_t *ctx, ethwiz3_cfg_t *cfg );

/**
 * @brief ETH WIZ 3 command set function.
 * @details This function sends a two-character command followed by the input data
 * string and a CRLF termination, using the selected interface (UART or SPI).
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @param[in] cmd : Pointer to the two-character command string.
 * @param[in] data_in : Pointer to the input data string to be sent with the command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ethwiz3_cmd_set ( ethwiz3_t *ctx, uint8_t *cmd, uint8_t *data_in );

/**
 * @brief ETH WIZ 3 command get function.
 * @details This function sends a two-character command terminated with CRLF and reads
 * back the response data using the selected interface (UART or SPI).
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @param[in] cmd : Pointer to the two-character command string.
 * @param[out] data_out : Pointer to the output buffer for the received data.
 * @param[out] read_len : Pointer to the number of bytes read.
 * @param[in] data_buf_len : Size of the output data buffer in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ethwiz3_cmd_get ( ethwiz3_t *ctx, uint8_t *cmd, uint8_t *data_out, uint16_t *read_len, uint16_t data_buf_len );

/**
 * @brief ETH WIZ 3 data write function.
 * @details This function writes a raw data buffer of the specified length using the
 * selected interface (UART or SPI). For SPI, it sends a write header and waits for ACK.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @param[in] data_in : Pointer to the input data buffer to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ethwiz3_data_write ( ethwiz3_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief ETH WIZ 3 data read function.
 * @details This function reads raw data into the provided buffer using the selected
 * interface (UART or SPI). The number of bytes read is returned via the read_len parameter.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @param[out] data_out : Pointer to the output buffer for the received data.
 * @param[out] read_len : Pointer to the number of bytes read.
 * @param[in] data_buf_len : Size of the output data buffer in bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ethwiz3_data_read ( ethwiz3_t *ctx, uint8_t *data_out, uint16_t *read_len, uint16_t data_buf_len );

/**
 * @brief ETH WIZ 3 set reset pin function.
 * @details This function sets the state of the RST pin.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @param[in] state : RST pin state to be set.
 * @return None.
 * @note None.
 */
void ethwiz3_set_rst_pin ( ethwiz3_t *ctx, uint8_t state );

/**
 * @brief ETH WIZ 3 set CTS pin function.
 * @details This function sets the state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @param[in] state : CTS pin state to be set.
 * @return None.
 * @note None.
 */
void ethwiz3_set_cts_pin ( ethwiz3_t *ctx, uint8_t state );

/**
 * @brief ETH WIZ 3 set AT mode function.
 * @details This function sets the AT mode by setting the ATM pin low.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ethwiz3_set_at_mode ( ethwiz3_t *ctx );

/**
 * @brief ETH WIZ 3 set data mode function.
 * @details This function sets the data mode by setting the ATM pin high.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ethwiz3_set_data_mode ( ethwiz3_t *ctx );

/**
 * @brief ETH WIZ 3 get RTS pin function.
 * @details This function reads and returns the state of the RTS pin.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @return RTS pin logic state.
 * @note None.
 */
uint8_t ethwiz3_get_rts_pin ( ethwiz3_t *ctx );

/**
 * @brief ETH WIZ 3 get TCP pin function.
 * @details This function reads and returns the state of the TCP pin.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @return TCP pin logic state.
 * @note None.
 */
uint8_t ethwiz3_get_tcp_pin ( ethwiz3_t *ctx );

/**
 * @brief ETH WIZ 3 reset device function.
 * @details This function performs a hardware reset sequence by toggling the RST pin
 * with required delays.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ethwiz3_reset_device ( ethwiz3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // ETHWIZ3_H

/*! @} */ // ethwiz3

// ------------------------------------------------------------------------ END
