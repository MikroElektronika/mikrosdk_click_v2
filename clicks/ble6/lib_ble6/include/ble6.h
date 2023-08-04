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
 * @file ble6.h
 * @brief This file contains API for BLE 6 Click Driver.
 */

#ifndef BLE6_H
#define BLE6_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup ble6 BLE 6 Click Driver
 * @brief API for configuring and manipulating BLE 6 Click driver.
 * @{
 */

/**
 * @defgroup ble6_cmd BLE 6 Device Settings
 * @brief Settings for registers of BLE 6 Click driver.
 */

/**
 * @addtogroup ble6_cmd
 * @{
 */

/**
 * @brief BLE 6 control commands.
 * @details Specified setting for control commands of BLE 6 Click driver.
 */
#define BLE6_MODULE_POWER_OFF                   0x00
#define BLE6_MODULE_POWER_ON                    0x01

/**
 * @brief BLE 6 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BLE6_DRV_BUFFER_SIZE                    256

/*! @} */ // ble6_cmd

/**
 * @defgroup ble6_map BLE 6 MikroBUS Map
 * @brief MikroBUS pin mapping of BLE 6 Click driver.
 */

/**
 * @addtogroup ble6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BLE 6 Click to the selected MikroBUS.
 */
#define BLE6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.bl = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // ble6_map
/*! @} */ // ble6

/**
 * @brief BLE 6 Click context object.
 * @details Context object definition of BLE 6 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< Reset. */
    digital_out_t bl;           /**< Boot. */

    // Input pins
    digital_in_t an;            /**< Analog Input. */

    // Modules
    uart_t uart;                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BLE6_DRV_BUFFER_SIZE ];     /**< Buffer size. */
    uint8_t uart_tx_buffer[ BLE6_DRV_BUFFER_SIZE ];     /**< Buffer size. */

} ble6_t;

/**
 * @brief BLE 6 Click configuration object.
 * @details Configuration object definition of BLE 6 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t an;              /**< Analog Input. */
    pin_name_t rst;             /**< Reset. */
    pin_name_t bl;              /**< Boot. */

    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} ble6_cfg_t;

/**
 * @brief Driver Default Response type.
 * @details Response type of BLE 6 Click driver.
 */
typedef struct
{
    uint8_t event_code;
    uint8_t length;
    uint8_t num_hci_cmd;
    uint16_t cmd_opcode;
    uint8_t status;
    uint8_t payload[ BLE6_DRV_BUFFER_SIZE ];
    
} ble6_rsp_t;

/**
 * @brief Driver Response Le Meta Event.
 * @details Response le meta event of BLE 6 Click driver.
 */
typedef struct
{
    uint8_t le_event_code;
    uint8_t le_length;
    uint8_t le_subevent_code;
    uint8_t le_status;
    uint16_t le_conn_hdl;
    uint8_t le_role;
    uint8_t le_peer_addr_type;
    uint8_t le_peer_addr[ 6 ];
    uint16_t le_conn_interval;
    uint16_t le_conn_latency;
    uint16_t le_sup_timeout;
    uint8_t le_master_clk_accuracy;
    
} ble6_le_meta_event_t;

/**
 * @brief Driver Response type.
 * @details Response read type of BLE 6 Click driver.
 */
typedef struct
{
    uint8_t event_code;
    uint8_t length;
    uint16_t e_code;
    uint16_t conn_hdl;
    uint16_t attr_hdl;
    uint16_t offset;
    uint16_t attr_data_len;
    uint8_t attr_data[ 255 ];
    
} ble6_rx_rsp_t;

/**
 * @brief BLE 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BLE6_OK = 0,
    BLE6_ERROR = -1

} ble6_return_value_t;

/*!
 * @addtogroup ble6 BLE 6 Click Driver
 * @brief API for configuring and manipulating BLE 6 Click driver.
 * @{
 */

/**
 * @brief BLE 6 Click driver handler.
 * @details Definition of driver handler of BLE 6 Click driver.
 */
typedef void ( *ble6_handler_t )( uint8_t *message_buf, uint32_t message_len );

/**
 * @brief BLE 6 Click driver handler.
 * @details Definition of driver handler of BLE 6 Click driver.
 */
typedef void ( *ble6_hdl_t )( uint8_t* );

/**
 * @brief BLE 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ble6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ble6_cfg_setup ( ble6_cfg_t *cfg );

/**
 * @brief BLE 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ble6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ble6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ble6_init ( ble6_t *ctx, ble6_cfg_t *cfg );

/**
 * @brief BLE 6 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ble6_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ble6_generic_write ( ble6_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief BLE 6 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ble6_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ble6_generic_read ( ble6_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Lexicographically compares function
 * @details Function lexicographically compares not more than len characters
 * ( characters that follow the null character are not compared )
 * from the string pointed by string1 to the string pointed by string2.
 * @param[in] string1 : Pointer to the memory location where string1 string be stored.
 * @param[in] string2 : Pointer to the memory location where string2 string be stored..
 * @param[in] len : Number of compare characters.
 * @return Value indicating the string1 and string2 relationship.
 */
int8_t ble6_strncmp ( uint8_t *string1, uint8_t *string2, uint8_t len );

/**
 * @brief Check for new byte received
 * @details Checks is there a new byte received.
 * @param[in] ctx : Click context object.
 * See #ble6_t object definition for detailed explanation.
 * @return Returns the number of bytes that are available for reading.
 */
uint8_t ble6_byte_ready ( ble6_t *ctx );

/**
 * @brief Set Power On function
 * @details The function enable/disble power on 
 * by set states of the RST pin of BLUENRG-M2SP, 
 * Very low power application processor module for Bluetooth� low energy v5.0
 * on BLE 6 click.
 * @param[out] ctx : Click context object.
 * See #ble6_t object definition for detailed explanation.
 * @param[in] en_pwr : State of the RST pin.
 * @return Nothing.
 */
void ble6_power_on ( ble6_t *ctx, uint8_t en_pwr );

/**
 * @brief Send command function
 * @details The function send command to the BLUENRG-M2SP,
 * Very low power application processor module for Bluetooth� low energy v5.0
 * on BLE 6 click.
 * @param[in] ctx : Click context object.
 * See #ble6_t object definition for detailed explanation.
 * @param[in] tx_data : Pointer to the memory location where at_command be stored.
 * @param[in] n_bytes : Number of bytes to send.
 * @return Nothing.
 */
void ble6_send_command ( ble6_t *ctx, uint8_t *tx_data, uint8_t n_bytes );

/**
 * @brief Set response handlers function.
 * @details The function set response handler.
 * @param[in] handler : Pointer of response handler.
 * @return Nothing.
 */
void ble6_set_response_handler ( void ( *handler )( uint8_t* ), ble6_hdl_t driver_hdl );

/**
 * @brief Set handlers function.
 * @details The function set event handler.
 * @param[in] event_handler : Pointer of event handler.
 * See #ble6_handler_t object definition for detailed explanation.
 * @return Nothing.
 */
void ble6_set_handlers ( ble6_handler_t event_handler, ble6_handler_t eve_hdlr );

/**
 * @brief Response parser function.
 * @details The function parser device response.
 * @param[in] ctx : Click context object.
 * See #ble6_t object definition for detailed explanation.
 * @param[in] response : Pointer to the memory location where response be stored.
 * @return Nothing.
 */
void ble6_parser_rsp ( ble6_t *ctx, ble6_rsp_t *response );

#ifdef __cplusplus
}
#endif
#endif // BLE6_H

/*! @} */ // ble6

// ------------------------------------------------------------------------ END
