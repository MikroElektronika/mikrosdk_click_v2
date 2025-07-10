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
 * @file ninab416.h
 * @brief This file contains API for NINA-B416 Click Driver.
 */

#ifndef NINAB416_H
#define NINAB416_H

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
 * @addtogroup ninab416 NINA-B416 Click Driver
 * @brief API for configuring and manipulating NINA-B416 Click driver.
 * @{
 */

/**
 * @defgroup ninab416_cmd NINA-B416 Device Settings
 * @brief Settings for registers of NINA-B416 Click driver.
 */

/**
 * @addtogroup ninab416_cmd
 * @{
 */

/**
 * @brief NINA-B416 control commands.
 * @details Specified setting for control commands of NINA-B416 Click driver.
 */
#define NINAB416_CMD_AT                         "AT"
#define NINAB416_CMD_GET_MODEL_ID               "AT+CGMM"
#define NINAB416_CMD_GET_SW_VERSION             "AT+CGMR"
#define NINAB416_CMD_GET_SERIAL_NUM             "AT+CGSN"
#define NINAB416_CMD_FACTORY_RESET              "AT+UFACTORY"
#define NINAB416_CMD_REBOOT_DEVICE              "AT+CPWROFF"
#define NINAB416_CMD_BT_LOCAL_NAME              "AT+UBTLN"
#define NINAB416_CMD_CONNECT_PEER               "AT+UDCP"
#define NINAB416_CMD_WRITE_DATA                 "AT+UDATW"
#define NINAB416_CMD_READ_DATA                  "AT+UDATR"
#define NINAB416_CMD_CLOSE_PEER                 "AT+UDCPC"
#define NINAB416_CMD_ENTER_DATA_MODE            "ATO1"
#define NINAB416_CMD_ENTER_CMD_MODE             "+++"

/**
 * @brief NINA-B416 device response to AT commands.
 * @details Device response to commands.
 */
#define NINAB416_RSP_OK                         "OK"
#define NINAB416_RSP_ERROR                      "ERROR"

/**
 * @brief NINA-B416 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define NINAB416_URC_GREETING                   "+STARTUP"
#define NINAB416_URC_PEER_CONNECTED             "+UUDPC:"
#define NINAB416_URC_PEER_DISCONNECTED          "+UUDPD:"
#define NINAB416_URC_READ_SOCKET_DATA           "+UUDATA:"

/**
 * @brief NINA-B416 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NINAB416_TX_DRV_BUFFER_SIZE             200
#define NINAB416_RX_DRV_BUFFER_SIZE             600

/*! @} */ // ninab416_cmd

/**
 * @defgroup ninab416_map NINA-B416 MikroBUS Map
 * @brief MikroBUS pin mapping of NINA-B416 Click driver.
 */

/**
 * @addtogroup ninab416_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NINA-B416 Click to the selected MikroBUS.
 */
#define NINAB416_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.dtr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dsr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // ninab416_map
/*! @} */ // ninab416

/**
 * @brief NINA-B416 Click context object.
 * @details Context object definition of NINA-B416 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< System reset pin (active low). */
    digital_out_t cts;              /**< UART clear to send control signal. */
    digital_out_t dsr;              /**< UART data set ready signal. */

    // Input pins
    digital_in_t dtr;               /**< UART data terminal ready signal. */
    digital_in_t rts;               /**< UART request to send control signal. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ NINAB416_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ NINAB416_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ NINAB416_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} ninab416_t;

/**
 * @brief NINA-B416 Click configuration object.
 * @details Configuration object definition of NINA-B416 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t dtr;                 /**< UART data terminal ready signal. */
    pin_name_t rst;                 /**< System reset pin (active low). */
    pin_name_t cts;                 /**< UART clear to send control signal. */
    pin_name_t dsr;                 /**< UART data set ready signal. */
    pin_name_t rts;                 /**< UART request to send control signal. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} ninab416_cfg_t;

/**
 * @brief NINA-B416 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NINAB416_OK = 0,
    NINAB416_ERROR = -1,
    NINAB416_ERROR_TIMEOUT = -2,
    NINAB416_ERROR_CMD = -3

} ninab416_return_value_t;

/*!
 * @addtogroup ninab416 NINA-B416 Click Driver
 * @brief API for configuring and manipulating NINA-B416 Click driver.
 * @{
 */

/**
 * @brief NINA-B416 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ninab416_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ninab416_cfg_setup ( ninab416_cfg_t *cfg );

/**
 * @brief NINA-B416 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ninab416_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab416_init ( ninab416_t *ctx, ninab416_cfg_t *cfg );

/**
 * @brief NINA-B416 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab416_generic_write ( ninab416_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NINA-B416 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ninab416_generic_read ( ninab416_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NINA-B416 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ninab416_set_rst_pin ( ninab416_t *ctx, uint8_t state );

/**
 * @brief NINA-B416 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ninab416_reset_device ( ninab416_t *ctx );

/**
 * @brief NINA-B416 set CTS pin function.
 * @details This function sets the clear to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ninab416_set_cts_pin ( ninab416_t *ctx, uint8_t state );

/**
 * @brief NINA-B416 get RTS pin function.
 * @details This function returns the ready to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ninab416_get_rts_pin ( ninab416_t *ctx );

/**
 * @brief NINA-B416 set DSR pin function.
 * @details This function sets the data set ready pin logic state.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void ninab416_set_dsr_pin ( ninab416_t *ctx, uint8_t state );

/**
 * @brief NINA-B416 get DTR pin function.
 * @details This function returns the data terminal ready pin logic state.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ninab416_get_dtr_pin ( ninab416_t *ctx );

/**
 * @brief NINA-B416 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see NINAB416_CMD_x definitions.
 * @return None.
 * @note None.
 */
void ninab416_cmd_run ( ninab416_t *ctx, uint8_t *cmd );

/**
 * @brief NINA-B416 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see NINAB416_CMD_x definitions.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void ninab416_cmd_set ( ninab416_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief NINA-B416 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #ninab416_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see NINAB416_CMD_x definitions.
 * @return None.
 * @note None.
 */
void ninab416_cmd_get ( ninab416_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // NINAB416_H

/*! @} */ // ninab416

// ------------------------------------------------------------------------ END
