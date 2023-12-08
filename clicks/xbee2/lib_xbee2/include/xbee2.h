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
 * @file xbee2.h
 * @brief This file contains API for XBEE 2 Click Driver.
 */

#ifndef XBEE2_H
#define XBEE2_H

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
 * @addtogroup xbee2 XBEE 2 Click Driver
 * @brief API for configuring and manipulating XBEE 2 Click driver.
 * @{
 */

/**
 * @defgroup xbee2_cmd XBEE 2 Device Settings
 * @brief Settings for registers of XBEE 2 Click driver.
 */

/**
 * @addtogroup xbee2_cmd
 * @{
 */

/**
 * @brief XBEE 2 list of AT commands.
 * @brief AT commands list of XBEE 2 Click driver.
 */
#define XBEE2_ENTER_CMD_MODE                "+++"
#define XBEE2_EXIT_CMD_MODE                 "CN"
#define XBEE2_FACTORY_RESET                 "RE"
#define XBEE2_SET_NODE_IDENTIFIER           "NI"
#define XBEE2_GET_SERIAL_NUMBER             "SH,SL"
#define XBEE2_SET_DEST_ADDR_HIGH            "DH"
#define XBEE2_SET_DEST_ADDR_LOW             "DL"
#define XBEE2_APPLY_CHANGES                 "AC"
#define XBEE2_API_MODE                      "AP"
#define XBEE2_DEV_ROLE                      "CE"
#define XBEE2_SAVE_CHANGES                  "WR"
#define XBEE2_CMD_AT                        "AT"
#define XBEE2_DELIMITER                     ","
#define XBEE2_CARRIAGE_RETURN               "\r"

/**
 * @brief XBEE 2 mode settings.
 * @brief Mode settings of XBEE 2 Click driver.
 */
#define XBEE2_MODE_TRANSPARENT              0
#define XBEE2_MODE_API_WITHOUT_ESC          1
#define XBEE2_MODE_API_WITH_ESC             2

/**
 * @brief XBEE 2 device role settings.
 * @brief Device role settings of XBEE 2 Click driver.
 */
#define XBEE2_DEVICE_ROLE_JOIN_NETWORK      0
#define XBEE2_DEVICE_ROLE_FORM_NETWORK      1

/**
 * @brief XBEE 2 destination address settings.
 * @brief Destination address settings of XBEE 2 Click driver.
 */
#define XBEE2_BROADCAST_DEST_ADDRESS_HIGH   "00000000"
#define XBEE2_BROADCAST_DEST_ADDRESS_LOW    "0000FFFF"

/**
 * @brief XBEE 2 device response for AT commands.
 * @details Device response after commands.
 */
#define XBEE2_RSP_OK                        "OK"
#define XBEE2_RSP_ERROR                     "ERROR"

/**
 * @brief XBEE 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                     200

/*! @} */ // xbee2_cmd

/**
 * @defgroup xbee2_map XBEE 2 MikroBUS Map
 * @brief MikroBUS pin mapping of XBEE 2 Click driver.
 */

/**
 * @addtogroup xbee2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of XBEE 2 Click to the selected MikroBUS.
 */
#define XBEE2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.att_dtr = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // xbee2_map
/*! @} */ // xbee2

/**
 * @brief XBEE 2 Click context object.
 * @details Context object definition of XBEE 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rts;              /**< Request to Send pin. */
    digital_out_t rst;              /**< Reset pin (Active low). */
    digital_out_t cs;               /**< SPI enable pin. */

    // Input pins
    digital_in_t cts;               /**< Clear to Send pin. */
    digital_in_t att_dtr;           /**< SPI Attention or UART Data Present indicator Or Sleep Control line. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */

} xbee2_t;

/**
 * @brief XBEE 2 Click configuration object.
 * @details Configuration object definition of XBEE 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rts;                 /**< Request to Send pin. */
    pin_name_t rst;                 /**< Reset pin (Active low). */
    pin_name_t cs;                  /**< SPI enable pin. */
    pin_name_t cts;                 /**< Clear to Send pin. */
    pin_name_t att_dtr;             /**< SPI Attention or UART Data Present indicator Or Sleep Control line. */

    // Static variable
    uint32_t          baud_rate;            /**< Clock speed. */
    bool              uart_blocking;        /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;             /**< Data bits. */
    uart_parity_t     parity_bit;           /**< Parity bit. */
    uart_stop_bits_t  stop_bit;             /**< Stop bits. */

} xbee2_cfg_t;

/**
 * @brief XBEE 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    XBEE2_OK = 0,
    XBEE2_ERROR = -1

} xbee2_return_value_t;

/*!
 * @addtogroup xbee2 XBEE 2 Click Driver
 * @brief API for configuring and manipulating XBEE 2 Click driver.
 * @{
 */

/**
 * @brief XBEE 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #xbee2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void xbee2_cfg_setup ( xbee2_cfg_t *cfg );

/**
 * @brief XBEE 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #xbee2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_init ( xbee2_t *ctx, xbee2_cfg_t *cfg );

/**
 * @brief XBEE 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_generic_write ( xbee2_t *ctx, char *data_in, uint16_t len );

/**
 * @brief XBEE 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_generic_read ( xbee2_t *ctx, char *data_out, uint16_t len );

/**
 * @brief XBEE 2 set rts pin function.
 * @details This function sets the request to send (RTS) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee2_set_rts_pin ( xbee2_t *ctx, uint8_t state );

/**
 * @brief XBEE 2 set rst pin function.
 * @details This function sets the reset (RST) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee2_set_rst_pin ( xbee2_t *ctx, uint8_t state );

/**
 * @brief XBEE 2 set cs pin function.
 * @details This function sets the chip select (CS) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee2_set_cs_pin ( xbee2_t *ctx, uint8_t state );

/**
 * @brief XBEE 2 get cts pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xbee2_get_cts_pin ( xbee2_t *ctx );

/**
 * @brief XBEE 2 get att_dtr pin function.
 * @details This function returns the SPI Attention or UART Data Present indicator Or 
 * Sleep Control line (ATT_DTR) pin logic state.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xbee2_get_att_dtr_pin ( xbee2_t *ctx );

/**
 * @brief XBEE 2 write command function.
 * @details This function sends a desired AT command with the CR byte appended to.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @param[in] data_buf : Command string.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_write_command ( xbee2_t *ctx, char *data_buf );

/**
 * @brief XBEE 2 hw reset function.
 * @details This function resets the module by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xbee2_hw_reset ( xbee2_t *ctx );

/**
 * @brief XBEE 2 enter command mode function.
 * @details This function is used to enter to command mode by issuing the command character (CC).
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_enter_command_mode ( xbee2_t *ctx );

/**
 * @brief XBEE 2 exit command mode function.
 * @details This function is used to exits to command mode by issuing the exit command (CN).
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_exit_command_mode ( xbee2_t *ctx );

/**
 * @brief XBEE 2 factory reset function.
 * @details This function factory resets the device.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note xbee2_save_changes( ) must be called after to save the changes enacted with factory reset.
 */
err_t xbee2_factory_reset ( xbee2_t *ctx );

/**
 * @brief XBEE 2 get serial number function.
 * @details This function sends a get serial number command.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_get_serial_number ( xbee2_t *ctx );

/**
 * @brief XBEE 2 set device name function.
 * @details This function sets the device name (node identifier).
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @param[in] dev_name : Device name ( up to 20 characters ).
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_set_device_name ( xbee2_t *ctx, char *dev_name );

/**
 * @brief XBEE 2 set destination address function.
 * @details This function sets the destination address high and low bytes.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @param[in] dest_addr_high : Destination address high bytes as hex string ( up to 8 characters ).
 * @param[in] dest_addr_low : Destination address low bytes as hex string ( up to 8 characters ).
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_set_destination_address ( xbee2_t *ctx, char *dest_addr_high, char *dest_addr_low );

/**
 * @brief XBEE 2 set api mode function.
 * @details This function sets the api mode.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @param[in] api_mode : @li @c 0 - Transparent mode,
 *                       @li @c 1 - API mode without ESC.
 *                       @li @c 2 - API mode with ESC.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_set_api_mode ( xbee2_t *ctx, uint8_t api_mode );

/**
 * @brief XBEE 2 set device role function.
 * @details This function sets the device role which determines whether the device should form or join a network.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @param[in] dev_role : @li @c 0 - Join network,
 *                       @li @c 1 - Form network.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_set_device_role ( xbee2_t *ctx, uint8_t dev_role );

/**
 * @brief XBEE 2 apply changes function.
 * @details This function applies changes by sending the AC command.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_apply_changes ( xbee2_t *ctx );

/**
 * @brief XBEE 2 save changes function.
 * @details This function saves changes by sending the WR command.
 * @param[in] ctx : Click context object.
 * See #xbee2_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee2_save_changes ( xbee2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // XBEE2_H

/*! @} */ // xbee2

// ------------------------------------------------------------------------ END
