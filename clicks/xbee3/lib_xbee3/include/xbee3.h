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
 * @file xbee3.h
 * @brief This file contains API for XBEE 3 Click Driver.
 */

#ifndef XBEE3_H
#define XBEE3_H

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
 * @addtogroup xbee3 XBEE 3 Click Driver
 * @brief API for configuring and manipulating XBEE 3 Click driver.
 * @{
 */

/**
 * @defgroup xbee3_cmd XBEE 3 Device Settings
 * @brief Settings for registers of XBEE 3 Click driver.
 */

/**
 * @addtogroup xbee3_cmd
 * @{
 */

/**
 * @brief XBEE 3 list of AT commands.
 * @brief AT commands list of XBEE 3 Click driver.
 */
#define XBEE3_ENTER_CMD_MODE                "+++"
#define XBEE3_EXIT_CMD_MODE                 "CN"
#define XBEE3_FACTORY_RESET                 "RE"
#define XBEE3_SET_NODE_IDENTIFIER           "NI"
#define XBEE3_GET_SERIAL_NUMBER             "SH,SL"
#define XBEE3_SET_DEST_ADDR_HIGH            "DH"
#define XBEE3_SET_DEST_ADDR_LOW             "DL"
#define XBEE3_APPLY_CHANGES                 "AC"
#define XBEE3_API_MODE                      "AP"
#define XBEE3_SAVE_CHANGES                  "WR"
#define XBEE3_CMD_AT                        "AT"
#define XBEE3_DELIMITER                     ","
#define XBEE3_CARRIAGE_RETURN               "\r"

/**
 * @brief XBEE 3 mode settings.
 * @brief Mode settings of XBEE 3 Click driver.
 */
#define XBEE3_MODE_TRANSPARENT              0
#define XBEE3_MODE_API_WITHOUT_ESC          1
#define XBEE3_MODE_API_WITH_ESC             2

/**
 * @brief XBEE 3 destination address settings.
 * @brief Destination address settings of XBEE 3 Click driver.
 */
#define XBEE3_BROADCAST_DEST_ADDRESS_HIGH   "00000000"
#define XBEE3_BROADCAST_DEST_ADDRESS_LOW    "0000FFFF"

/**
 * @brief XBEE 3 device response for AT commands.
 * @details Device response after commands.
 */
#define XBEE3_RSP_OK                        "OK"
#define XBEE3_RSP_ERROR                     "ERROR"

/**
 * @brief XBEE 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                     200

/*! @} */ // xbee3_cmd

/**
 * @defgroup xbee3_map XBEE 3 MikroBUS Map
 * @brief MikroBUS pin mapping of XBEE 3 Click driver.
 */

/**
 * @addtogroup xbee3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of XBEE 3 Click to the selected MikroBUS.
 */
#define XBEE3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.att_dtr = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // xbee3_map
/*! @} */ // xbee3

/**
 * @brief XBEE 3 Click context object.
 * @details Context object definition of XBEE 3 Click driver.
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

} xbee3_t;

/**
 * @brief XBEE 3 Click configuration object.
 * @details Configuration object definition of XBEE 3 Click driver.
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

} xbee3_cfg_t;

/**
 * @brief XBEE 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    XBEE3_OK = 0,
    XBEE3_ERROR = -1

} xbee3_return_value_t;

/*!
 * @addtogroup xbee3 XBEE 3 Click Driver
 * @brief API for configuring and manipulating XBEE 3 Click driver.
 * @{
 */

/**
 * @brief XBEE 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #xbee3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void xbee3_cfg_setup ( xbee3_cfg_t *cfg );

/**
 * @brief XBEE 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #xbee3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_init ( xbee3_t *ctx, xbee3_cfg_t *cfg );

/**
 * @brief XBEE 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_generic_write ( xbee3_t *ctx, char *data_in, uint16_t len );

/**
 * @brief XBEE 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_generic_read ( xbee3_t *ctx, char *data_out, uint16_t len );

/**
 * @brief XBEE 3 set rts pin function.
 * @details This function sets the request to send (RTS) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee3_set_rts_pin ( xbee3_t *ctx, uint8_t state );

/**
 * @brief XBEE 3 set rst pin function.
 * @details This function sets the reset (RST) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee3_set_rst_pin ( xbee3_t *ctx, uint8_t state );

/**
 * @brief XBEE 3 set cs pin function.
 * @details This function sets the chip select (CS) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xbee3_set_cs_pin ( xbee3_t *ctx, uint8_t state );

/**
 * @brief XBEE 3 get cts pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xbee3_get_cts_pin ( xbee3_t *ctx );

/**
 * @brief XBEE 3 get att_dtr pin function.
 * @details This function returns the SPI Attention or UART Data Present indicator Or 
 * Sleep Control line (ATT_DTR) pin logic state.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xbee3_get_att_dtr_pin ( xbee3_t *ctx );

/**
 * @brief XBEE 3 write command function.
 * @details This function sends a desired AT command with the CR byte appended to.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @param[in] data_buf : Command string.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_write_command ( xbee3_t *ctx, char *data_buf );

/**
 * @brief XBEE 3 hw reset function.
 * @details This function resets the module by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xbee3_hw_reset ( xbee3_t *ctx );

/**
 * @brief XBEE 3 enter command mode function.
 * @details This function is used to enter to command mode by issuing the command character (CC).
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_enter_command_mode ( xbee3_t *ctx );

/**
 * @brief XBEE 3 exit command mode function.
 * @details This function is used to exits to command mode by issuing the exit command (CN).
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_exit_command_mode ( xbee3_t *ctx );

/**
 * @brief XBEE 3 factory reset function.
 * @details This function factory resets the device.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note xbee3_save_changes( ) must be called after to save the changes enacted with factory reset.
 */
err_t xbee3_factory_reset ( xbee3_t *ctx );

/**
 * @brief XBEE 3 get serial number function.
 * @details This function sends a get serial number command.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_get_serial_number ( xbee3_t *ctx );

/**
 * @brief XBEE 3 set device name function.
 * @details This function sets the device name (node identifier).
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @param[in] dev_name : Device name ( up to 20 characters ).
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_set_device_name ( xbee3_t *ctx, char *dev_name );

/**
 * @brief XBEE 3 set destination address function.
 * @details This function sets the destination address high and low bytes.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @param[in] dest_addr_high : Destination address high bytes as hex string ( up to 8 characters ).
 * @param[in] dest_addr_low : Destination address low bytes as hex string ( up to 8 characters ).
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_set_destination_address ( xbee3_t *ctx, char *dest_addr_high, char *dest_addr_low );

/**
 * @brief XBEE 3 set api mode function.
 * @details This function sets the api mode.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @param[in] api_mode : @li @c 0 - Transparent mode,
 *                       @li @c 1 - API mode without ESC.
 *                       @li @c 2 - API mode with ESC.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_set_api_mode ( xbee3_t *ctx, uint8_t api_mode );

/**
 * @brief XBEE 3 apply changes function.
 * @details This function applies changes by sending the AC command.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_apply_changes ( xbee3_t *ctx );

/**
 * @brief XBEE 3 save changes function.
 * @details This function saves changes by sending the WR command.
 * @param[in] ctx : Click context object.
 * See #xbee3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xbee3_save_changes ( xbee3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // XBEE3_H

/*! @} */ // xbee3

// ------------------------------------------------------------------------ END
