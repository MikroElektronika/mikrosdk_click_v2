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
 * @file xbee.h
 * @brief This file contains API for XBEE Click Driver.
 */

#ifndef XBEE_H
#define XBEE_H

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
 * @addtogroup xbee XBEE Click Driver
 * @brief API for configuring and manipulating XBEE Click driver.
 * @{
 */

/**
 * @defgroup xbee_cmd XBEE Device Settings
 * @brief Settings for registers of XBEE Click driver.
 */

/**
 * @addtogroup xbee_cmd
 * @{
 */

/**
 * @brief XBEE list of AT commands.
 * @brief AT commands list of XBEE Click driver.
 */
#define XBEE_ENTER_CMD_MODE                "+++"
#define XBEE_EXIT_CMD_MODE                 "CN"
#define XBEE_FACTORY_RESET                 "RE"
#define XBEE_SET_NODE_IDENTIFIER           "NI"
#define XBEE_GET_SERIAL_NUMBER             "SH,SL"
#define XBEE_SET_DEST_ADDR_HIGH            "DH"
#define XBEE_SET_DEST_ADDR_LOW             "DL"
#define XBEE_APPLY_CHANGES                 "AC"
#define XBEE_API_MODE                      "AP"
#define XBEE_SAVE_CHANGES                  "WR"
#define XBEE_CMD_AT                        "AT"
#define XBEE_DELIMITER                     ","
#define XBEE_CARRIAGE_RETURN               "\r"

/**
 * @brief XBEE mode settings.
 * @brief Mode settings of XBEE Click driver.
 */
#define XBEE_MODE_TRANSPARENT              0
#define XBEE_MODE_API_WITHOUT_ESC          1
#define XBEE_MODE_API_WITH_ESC             2

/**
 * @brief XBEE destination address settings.
 * @brief Destination address settings of XBEE Click driver.
 */
#define XBEE_BROADCAST_DEST_ADDRESS_HIGH   "00000000"
#define XBEE_BROADCAST_DEST_ADDRESS_LOW    "0000FFFF"

/**
 * @brief XBEE device response for AT commands.
 * @details Device response after commands.
 */
#define XBEE_RSP_OK                        "OK"
#define XBEE_RSP_ERROR                     "ERROR"

/**
 * @brief XBEE driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define XBEE_DRV_BUFFER_SIZE                200

/*! @} */ // xbee_cmd

/**
 * @defgroup xbee_map XBEE MikroBUS Map
 * @brief MikroBUS pin mapping of XBEE Click driver.
 */

/**
 * @addtogroup xbee_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of XBEE Click to the selected MikroBUS.
 */
#define XBEE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.att_dtr = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // xbee_map
/*! @} */ // xbee

/**
 * @brief XBEE Click context object.
 * @details Context object definition of XBEE Click driver.
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
    char uart_rx_buffer[ XBEE_DRV_BUFFER_SIZE ];     /**< Buffer size. */
    char uart_tx_buffer[ XBEE_DRV_BUFFER_SIZE ];     /**< Buffer size. */

} xbee_t;

/**
 * @brief XBEE Click configuration object.
 * @details Configuration object definition of XBEE Click driver.
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

} xbee_cfg_t;

/**
 * @brief XBEE Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    XBEE_OK = 0,
    XBEE_ERROR = -1

} xbee_return_value_t;

/*!
 * @addtogroup xbee XBEE Click Driver
 * @brief API for configuring and manipulating XBEE Click driver.
 * @{
 */

/**
 * @brief XBEE configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #xbee_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void xbee_cfg_setup ( xbee_cfg_t *cfg );

/**
 * @brief XBEE initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #xbee_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_init ( xbee_t *ctx, xbee_cfg_t *cfg );

/**
 * @brief XBEE data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_generic_write ( xbee_t *ctx, char *data_in, uint16_t len );

/**
 * @brief XBEE data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_generic_read ( xbee_t *ctx, char *data_out, uint16_t len );

/**
 * @brief XBEE set rts pin function.
 * @details This function sets the request to send (RTS) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee_set_rts_pin ( xbee_t *ctx, uint8_t state );

/**
 * @brief XBEE set rst pin function.
 * @details This function sets the reset (RST) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee_set_rst_pin ( xbee_t *ctx, uint8_t state );

/**
 * @brief XBEE set cs pin function.
 * @details This function sets the chip select (CS) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee_set_cs_pin ( xbee_t *ctx, uint8_t state );

/**
 * @brief XBEE get cts pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xbee_get_cts_pin ( xbee_t *ctx );

/**
 * @brief XBEE get att_dtr pin function.
 * @details This function returns the SPI Attention or UART Data Present indicator Or 
 * Sleep Control line (ATT_DTR) pin logic state.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xbee_get_att_dtr_pin ( xbee_t *ctx );

/**
 * @brief XBEE write command function.
 * @details This function sends a desired AT command with the CR byte appended to.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @param[in] data_buf : Command string.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_write_command ( xbee_t *ctx, char *data_buf );

/**
 * @brief XBEE hw reset function.
 * @details This function resets the module by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xbee_hw_reset ( xbee_t *ctx );

/**
 * @brief XBEE enter command mode function.
 * @details This function is used to enter to command mode by issuing the command character (CC).
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_enter_command_mode ( xbee_t *ctx );

/**
 * @brief XBEE exit command mode function.
 * @details This function is used to exits to command mode by issuing the exit command (CN).
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_exit_command_mode ( xbee_t *ctx );

/**
 * @brief XBEE factory reset function.
 * @details This function factory resets the device.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note xbee_save_changes( ) must be called after to save the changes enacted with factory reset.
 */
err_t xbee_factory_reset ( xbee_t *ctx );

/**
 * @brief XBEE get serial number function.
 * @details This function sends a get serial number command.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_get_serial_number ( xbee_t *ctx );

/**
 * @brief XBEE set device name function.
 * @details This function sets the device name (node identifier).
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @param[in] dev_name : Device name ( up to 20 characters ).
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_set_device_name ( xbee_t *ctx, char *dev_name );

/**
 * @brief XBEE set destination address function.
 * @details This function sets the destination address high and low bytes.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @param[in] dest_addr_high : Destination address high bytes as hex string ( up to 8 characters ).
 * @param[in] dest_addr_low : Destination address low bytes as hex string ( up to 8 characters ).
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_set_destination_address ( xbee_t *ctx, char *dest_addr_high, char *dest_addr_low );

/**
 * @brief XBEE set api mode function.
 * @details This function sets the api mode.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @param[in] api_mode : @li @c 0 - Transparent mode,
 *                       @li @c 1 - API mode without ESC.
 *                       @li @c 2 - API mode with ESC.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_set_api_mode ( xbee_t *ctx, uint8_t api_mode );

/**
 * @brief XBEE apply changes function.
 * @details This function applies changes by sending the AC command.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_apply_changes ( xbee_t *ctx );

/**
 * @brief XBEE save changes function.
 * @details This function saves changes by sending the WR command.
 * @param[in] ctx : Click context object.
 * See #xbee_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee_save_changes ( xbee_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // XBEE_H

/*! @} */ // xbee

// ------------------------------------------------------------------------ END
