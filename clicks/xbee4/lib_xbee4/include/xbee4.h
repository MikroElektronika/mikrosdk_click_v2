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
 * @file xbee4.h
 * @brief This file contains API for XBEE 4 Click Driver.
 */

#ifndef XBEE4_H
#define XBEE4_H

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
 * @addtogroup xbee4 XBEE 4 Click Driver
 * @brief API for configuring and manipulating XBEE 4 Click driver.
 * @{
 */

/**
 * @defgroup xbee4_cmd XBEE 4 Device Settings
 * @brief Settings for registers of XBEE 4 Click driver.
 */

/**
 * @addtogroup xbee4_cmd
 * @{
 */

/**
 * @brief XBEE 4 list of AT commands.
 * @brief AT commands list of XBEE 4 Click driver.
 */
#define XBEE4_ENTER_CMD_MODE                "+++"
#define XBEE4_EXIT_CMD_MODE                 "CN"
#define XBEE4_FACTORY_RESET                 "RE"
#define XBEE4_SET_NODE_IDENTIFIER           "NI"
#define XBEE4_GET_SERIAL_NUMBER             "SH,SL"
#define XBEE4_SET_DEST_ADDR_HIGH            "DH"
#define XBEE4_SET_DEST_ADDR_LOW             "DL"
#define XBEE4_APPLY_CHANGES                 "AC"
#define XBEE4_API_MODE                      "AP"
#define XBEE4_DEV_ROLE                      "CE"
#define XBEE4_SAVE_CHANGES                  "WR"
#define XBEE4_CMD_AT                        "AT"
#define XBEE4_DELIMITER                     ","
#define XBEE4_CARRIAGE_RETURN               "\r"

/**
 * @brief XBEE 4 mode settings.
 * @brief Mode settings of XBEE 4 Click driver.
 */
#define XBEE4_MODE_TRANSPARENT              0
#define XBEE4_MODE_API_WITHOUT_ESC          1
#define XBEE4_MODE_API_WITH_ESC             2

/**
 * @brief XBEE 4 device role settings.
 * @brief Device role settings of XBEE 4 Click driver.
 */
#define XBEE4_DEVICE_ROLE_JOIN_NETWORK      0
#define XBEE4_DEVICE_ROLE_FORM_NETWORK      1

/**
 * @brief XBEE 4 destination address settings.
 * @brief Destination address settings of XBEE 4 Click driver.
 */
#define XBEE4_BROADCAST_DEST_ADDRESS_HIGH   "00000000"
#define XBEE4_BROADCAST_DEST_ADDRESS_LOW    "0000FFFF"

/**
 * @brief XBEE 4 device response for AT commands.
 * @details Device response after commands.
 */
#define XBEE4_RSP_OK                        "OK"
#define XBEE4_RSP_ERROR                     "ERROR"
#define XBEE4_RSP_NEW_LINE                  "\r"

/**
 * @brief XBEE 4 device response timeout.
 * @details Device response timeout.
 */
#define XBEE4_TIMEOUT_3S                    3000

/**
 * @brief XBEE 4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define XBEE4_TX_DRV_BUFFER_SIZE            200
#define XBEE4_RX_DRV_BUFFER_SIZE            200

/*! @} */ // xbee4_cmd

/**
 * @defgroup xbee4_map XBEE 4 MikroBUS Map
 * @brief MikroBUS pin mapping of XBEE 4 Click driver.
 */

/**
 * @addtogroup xbee4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of XBEE 4 Click to the selected MikroBUS.
 */
#define XBEE4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.com = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // xbee4_map
/*! @} */ // xbee4

/**
 * @brief XBEE 4 Click context object.
 * @details Context object definition of XBEE 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t slp;              /**< Pin sleep control (active high). */
    digital_out_t rst;              /**< Device reset pin (active low). */
    digital_out_t rts;              /**< Request to send or SPI chip select pin. */
    digital_out_t com;              /**< RTS/CS pin select (1-CS, 0-RTS). */

    // Input pins
    digital_in_t cts;               /**< Clear to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ XBEE4_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ XBEE4_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} xbee4_t;

/**
 * @brief XBEE 4 Click configuration object.
 * @details Configuration object definition of XBEE 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t slp;                 /**< Pin sleep control (active high). */
    pin_name_t rst;                 /**< Device reset pin (active low). */
    pin_name_t rts;                 /**< Request to send pin. */
    pin_name_t com;                 /**< RTS/CS pin select (1-CS, 0-RTS). */
    pin_name_t cts;                 /**< Clear to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} xbee4_cfg_t;

/**
 * @brief XBEE 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    XBEE4_OK = 0,
    XBEE4_ERROR = -1,
    XBEE4_ERROR_TIMEOUT = -2

} xbee4_return_value_t;

/*!
 * @addtogroup xbee4 XBEE 4 Click Driver
 * @brief API for configuring and manipulating XBEE 4 Click driver.
 * @{
 */

/**
 * @brief XBEE 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #xbee4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void xbee4_cfg_setup ( xbee4_cfg_t *cfg );

/**
 * @brief XBEE 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #xbee4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee4_init ( xbee4_t *ctx, xbee4_cfg_t *cfg );

/**
 * @brief XBEE 4 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee4_generic_write ( xbee4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief XBEE 4 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee4_generic_read ( xbee4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief XBEE 4 set rts pin function.
 * @details This function sets the request to send (RTS) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee4_set_rts_pin ( xbee4_t *ctx, uint8_t state );

/**
 * @brief XBEE 4 set rst pin function.
 * @details This function sets the reset (RST) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee4_set_rst_pin ( xbee4_t *ctx, uint8_t state );

/**
 * @brief XBEE 4 set slp pin function.
 * @details This function sets the sleep (SLP) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee4_set_slp_pin ( xbee4_t *ctx, uint8_t state );

/**
 * @brief XBEE 4 set com pin function.
 * @details This function sets the communication select (COM) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee4_set_com_pin ( xbee4_t *ctx, uint8_t state );

/**
 * @brief XBEE 4 get cts pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xbee4_get_cts_pin ( xbee4_t *ctx );

/**
 * @brief XBEE 4 write command function.
 * @details This function sends a desired AT command with the CR byte appended to.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] data_buf : Command string.
 * @return None.
 * @note None.
 */
void xbee4_write_command ( xbee4_t *ctx, uint8_t *data_buf );

/**
 * @brief XBEE 4 hw reset function.
 * @details This function resets the module by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xbee4_hw_reset ( xbee4_t *ctx );

/**
 * @brief XBEE 4 enter command mode function.
 * @details This function is used to enter to command mode by issuing the command character (CC).
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xbee4_enter_command_mode ( xbee4_t *ctx );

/**
 * @brief XBEE 4 exit command mode function.
 * @details This function is used to exits to command mode by issuing the exit command (CN).
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xbee4_exit_command_mode ( xbee4_t *ctx );

/**
 * @brief XBEE 4 factory reset function.
 * @details This function factory resets the device.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @return None.
 * @note xbee4_save_changes( ) must be called after to save the changes enacted with factory reset.
 */
void xbee4_factory_reset ( xbee4_t *ctx );

/**
 * @brief XBEE 4 get serial number function.
 * @details This function sends a get serial number command.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xbee4_get_serial_number ( xbee4_t *ctx );

/**
 * @brief XBEE 4 set device name function.
 * @details This function sets the device name (node identifier).
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] dev_name : Device name ( up to 20 characters ).
 * @return None.
 * @note None.
 */
void xbee4_set_device_name ( xbee4_t *ctx, uint8_t *dev_name );

/**
 * @brief XBEE 4 set destination address function.
 * @details This function sets the destination address high and low bytes.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] dest_addr_high : Destination address high bytes as hex string ( up to 8 characters ).
 * @param[in] dest_addr_low : Destination address low bytes as hex string ( up to 8 characters ).
 * @return None.
 * @note None.
 */
void xbee4_set_destination_address ( xbee4_t *ctx, uint8_t *dest_addr_high, uint8_t *dest_addr_low );

/**
 * @brief XBEE 4 set api mode function.
 * @details This function sets the api mode.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] api_mode : @li @c 0 - Transparent mode,
 *                       @li @c 1 - API mode without ESC.
 *                       @li @c 2 - API mode with ESC.
 * @return None.
 * @note None.
 */
void xbee4_set_api_mode ( xbee4_t *ctx, uint8_t api_mode );

/**
 * @brief XBEE 4 set device role function.
 * @details This function sets the device role which determines whether the device should form or join a network.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @param[in] dev_role : @li @c 0 - Join network,
 *                       @li @c 1 - Form network.
 * @return None.
 * @note None.
 */
void xbee4_set_device_role ( xbee4_t *ctx, uint8_t dev_role );

/**
 * @brief XBEE 4 apply changes function.
 * @details This function applies changes by sending the AC command.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xbee4_apply_changes ( xbee4_t *ctx );

/**
 * @brief XBEE 4 save changes function.
 * @details This function saves changes by sending the WR command.
 * @param[in] ctx : Click context object.
 * See #xbee4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xbee4_save_changes ( xbee4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // XBEE4_H

/*! @} */ // xbee4

// ------------------------------------------------------------------------ END
