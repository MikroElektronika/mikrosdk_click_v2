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
 * @file annab412.h
 * @brief This file contains API for ANNA-B412 Click Driver.
 */

#ifndef ANNAB412_H
#define ANNAB412_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup annab412 ANNA-B412 Click Driver
 * @brief API for configuring and manipulating ANNA-B412 Click driver.
 * @{
 */

/**
 * @defgroup annab412_cmd ANNA-B412 Device Settings
 * @brief Settings for registers of ANNA-B412 Click driver.
 */

/**
 * @addtogroup annab412_cmd
 * @{
 */

/**
 * @brief ANNA-B412 control commands.
 * @details Specified setting for control commands of ANNA-B412 Click driver.
 */
#define ANNAB412_CMD_AT                   "AT"
#define ANNAB412_CMD_ECHO_OFF             "ATE0"
#define ANNAB412_CMD_ECHO_ON              "ATE1"
#define ANNAB412_CMD_DEV_NAME             "AT+UBTLN"
#define ANNAB412_CMD_CONN_MODE            "AT+UBTCM"
#define ANNAB412_CMD_DISCOVER_MODE        "AT+UBTDM"
#define ANNAB412_CMD_ENTER_MODE           "ATO"

/**
 * @brief ANNA-B412 delimiters ascii codes data.
 * @details Specified delimiters ascii codes data of ANNA-B412 Click driver.
 */
#define ANNAB412_DELIMITER_TERMINATION    13
#define ANNAB412_DELIMITER_END_CMD        0
#define ANNAB412_DELIMITER_QUOTATION      0x22
#define ANNAB412_DELIMITER_EQUAL          0x3D
#define ANNAB412_ASCII_CHAR_0             48

/**
 * @brief ANNA-B412 device name length limits.
 * @details Specified device name length limits of ANNA-B412 Click driver.
 */
#define ANNAB412_DEV_NAME_MIN             1
#define ANNAB412_DEV_NAME_MAX             38

/**
 * @brief ANNA-B412 connectability mode selection data.
 * @details Specified connectability mode selection data of ANNA-B412 Click driver.
 */
#define ANNAB412_CONNECTABLE_MODE_OFF     1
#define ANNAB412_CONNECTABLE_MODE_ON      2

/**
 * @brief ANNA-B412 discoverability mode selection data.
 * @details Specified discoverability mode selection data of ANNA-B412 Click driver.
 */
#define ANNAB412_DISCOVERABLE_MODE_OFF    1
#define ANNAB412_DISCOVERABLE_MODE_LIM    2
#define ANNAB412_DISCOVERABLE_MODE_ON     3

/**
 * @brief ANNA-B412 enter mode selection data.
 * @details Specified enter mode selection data of ANNA-B412 Click driver.
 */
#define ANNAB412_ENTER_MODE_COMMAND       0
#define ANNAB412_ENTER_MODE_DATA          1
#define ANNAB412_ENTER_MODE_EXT_DATA      2
#define ANNAB412_ENTER_MODE_PPP           3

/**
 * @brief ANNA-B412 I/O logic pin state.
 * @details Specified I/O logic pin state of ANNA-B412 Click driver.
 */
#define ANNAB412_PIN_STATE_LOW            0
#define ANNAB412_PIN_STATE_HIGH           1

/**
 * @brief ANNA-B412 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define ANNAB412_TX_DRV_BUFFER_SIZE       100
#define ANNAB412_RX_DRV_BUFFER_SIZE       300

/*! @} */ // annab412_cmd

/**
 * @defgroup annab412_map ANNA-B412 MikroBUS Map
 * @brief MikroBUS pin mapping of ANNA-B412 Click driver.
 */

/**
 * @addtogroup annab412_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ANNA-B412 Click to the selected MikroBUS.
 */
#define ANNAB412_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.dtr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dsr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // annab412_map
/*! @} */ // annab412

/**
 * @brief ANNA-B412 Click context object.
 * @details Context object definition of ANNA-B412 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;    /**< Reset pin. */
    digital_out_t cts;    /**< Clear to send pin. */
    digital_out_t dsr;    /**< Data set ready pin */

    // Input pins
    digital_in_t dtr;     /**< Data terminal ready pin. */
    digital_in_t rts;     /**< Request to send pin. */

    // Modules
    uart_t uart;          /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ ANNAB412_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ ANNAB412_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} annab412_t;

/**
 * @brief ANNA-B412 Click configuration object.
 * @details Configuration object definition of ANNA-B412 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;    /**< RX pin. */
    pin_name_t tx_pin;    /**< TX pin. */

    // Additional gpio pins
    pin_name_t dtr;    /**< Data terminal ready pin. */
    pin_name_t rst;    /**< Reset pin. */
    pin_name_t cts;    /**< Clear to send pin. */
    pin_name_t dsr;    /**< Data set ready pin */
    pin_name_t rts;    /**< Request to send pin. */

    // Static variable
    uint32_t         baud_rate;        /**< Clock speed. */
    bool             uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;         /**< Data bits. */
    uart_parity_t    parity_bit;       /**< Parity bit. */
    uart_stop_bits_t stop_bit;         /**< Stop bits. */

} annab412_cfg_t;

/**
 * @brief ANNA-B412 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ANNAB412_OK = 0,
    ANNAB412_ERROR = -1

} annab412_return_value_t;

/*!
 * @addtogroup annab412 ANNA-B412 Click Driver
 * @brief API for configuring and manipulating ANNA-B412 Click driver.
 * @{
 */

/**
 * @brief ANNA-B412 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #annab412_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void annab412_cfg_setup ( annab412_cfg_t *cfg );

/**
 * @brief ANNA-B412 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #annab412_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t annab412_init ( annab412_t *ctx, annab412_cfg_t *cfg );

/**
 * @brief ANNA-B412 default configuration function.
 * @details This function executes a default configuration of ANNA-B412
 * click board.
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t annab412_default_cfg ( annab412_t *ctx );

/**
 * @brief ANNA-B412 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t annab412_generic_write ( annab412_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief ANNA-B412 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t annab412_generic_read ( annab412_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief ANNA-B412 set reset pin function.
 * @details This function sets a desired logic state of the RST pin.
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void annab412_set_rst_pin ( annab412_t *ctx, uint8_t state );

/**
 * @brief ANNA-B412 set data set ready pin function.
 * @details This function sets a desired logic state of the DSR pin.
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void annab412_set_dsr_pin ( annab412_t *ctx, uint8_t state );

/**
 * @brief ANNA-B412 set clear to send pin function.
 * @details This function sets a desired logic state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void annab412_set_cts_pin ( annab412_t *ctx, uint8_t state );

/**
 * @brief ANNA-B412 get data terminal ready pin function.
 * @details This function the logic state of the DTR pin
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Logic state of the DTR pin.
 * @note None.
 */
uint8_t annab412_get_dtr_pin ( annab412_t *ctx );

/**
 * @brief ANNA-B412 get request to send pin function.
 * @details This function the logic state of the RTS pin
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Logic state of the RTS pin.
 * @note None.
 */
uint8_t annab412_get_rts_pin ( annab412_t *ctx );

/**
 * @brief ANNA-B412 hw reset function.
 * @details This function resets the module by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void annab412_hw_reset ( annab412_t *ctx );

/**
 * @brief ANNA-B412 send command function.
 * @details This function sends a desired command
 * of the Stand-alone Bluetooth 5.1 low energy module
 * on the ANNA-B412 click board™. 
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] command : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t annab412_send_command ( annab412_t *ctx, char *command );

/**
 * @brief ANNA-B412 set command echo on function.
 * @details This function enables the echo mode 
 * of the Stand-alone Bluetooth 5.1 low energy module
 * on the ANNA-B412 click board™. 
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t annab412_set_cmd_echo_on ( annab412_t *ctx );

/**
 * @brief ANNA-B412 set command echo on function.
 * @details This function disable the echo mode 
 * of the Stand-alone Bluetooth 5.1 low energy module
 * on the ANNA-B412 click board™. 
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t annab412_set_cmd_echo_off ( annab412_t *ctx );

/**
 * @brief ANNA-B412 set device name function.
 * @details This function sets the device name
 * of the Stand-alone Bluetooth 5.1 low energy module
 * on the ANNA-B412 click board™. 
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] device_name : Desired device name.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t annab412_set_cmd_device_name ( annab412_t *ctx, char *device_name );

/**
 * @brief ANNA-B412 set connectability mode function.
 * @details This function sets the connectability mode
 * of the Stand-alone Bluetooth 5.1 low energy module
 * on the ANNA-B412 click board™. 
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] mode : Desired connectability mode [1-2].
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t annab412_set_cmd_conn_mode ( annab412_t *ctx, uint8_t mode );

/**
 * @brief ANNA-B412 set discoverability mode function.
 * @details This function sets the discoverability mode
 * of the Stand-alone Bluetooth 5.1 low energy module
 * on the ANNA-B412 click board™. 
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] mode : Desired discoverability mode [1-3].
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t annab412_set_cmd_discover_mode ( annab412_t *ctx, uint8_t mode );

/**
 * @brief ANNA-B412 set enter mode function.
 * @details This function sets the enter mode
 * of the Stand-alone Bluetooth 5.1 low energy module
 * on the ANNA-B412 click board™. 
 * @param[in] ctx : Click context object.
 * See #annab412_t object definition for detailed explanation.
 * @param[in] mode : Desired enter mode [0-4].
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t annab412_set_cmd_enter_mode ( annab412_t *ctx, uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif // ANNAB412_H

/*! @} */ // annab412

// ------------------------------------------------------------------------ END
