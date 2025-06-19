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
 * @file smartnfc.h
 * @brief This file contains API for Smart NFC Click Driver.
 */

#ifndef SMARTNFC_H
#define SMARTNFC_H

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
 * @addtogroup smartnfc Smart NFC Click Driver
 * @brief API for configuring and manipulating Smart NFC Click driver.
 * @{
 */

/**
 * @defgroup smartnfc_cmd Smart NFC Device Settings
 * @brief Settings for registers of Smart NFC Click driver.
 */

/**
 * @addtogroup smartnfc_cmd
 * @{
 */

/**
 * @brief Smart NFC frame STX byte.
 * @details Specified frame STX byte of Smart NFC Click driver.
 */
#define SMARTNFC_FRAME_STX                      0xF5

/**
 * @brief Smart NFC generic commands.
 * @details Specified setting for generic commands of Smart NFC Click driver.
 */
#define SMARTNFC_CMD_ACK                        0x00
#define SMARTNFC_CMD_DUMMY                      0x01
#define SMARTNFC_CMD_GET_TAG_COUNT              0x02
#define SMARTNFC_CMD_GET_TAG_UID                0x03
#define SMARTNFC_CMD_ACTIVATE_TAG               0x04
#define SMARTNFC_CMD_HALT                       0x05
#define SMARTNFC_CMD_SET_POLLING                0x06
#define SMARTNFC_CMD_SET_KEY                    0x07
#define SMARTNFC_CMD_SAVE_KEYS                  0x08
#define SMARTNFC_CMD_NET_CONFIG                 0x09
#define SMARTNFC_CMD_REBOOT                     0x0A
#define SMARTNFC_CMD_GET_VERSION                0x0B
#define SMARTNFC_CMD_UART_PASSTHRU              0x0C
#define SMARTNFC_CMD_SLEEP                      0x0D
#define SMARTNFC_CMD_GPIO                       0x0E
#define SMARTNFC_CMD_SET_ACTIVE_ANT             0x0F
#define SMARTNFC_CMD_WPAN_PIN                   0x10
#define SMARTNFC_CMD_FACTORY_RESET              0x11
#define SMARTNFC_CMD_PROTOCOL_AUTH              0x12
#define SMARTNFC_CMD_PROTOCOL_CFG               0x13
#define SMARTNFC_CMD_LED                        0x14
#define SMARTNFC_CMD_WPAN_DATA                  0x15
#define SMARTNFC_CMD_POLLING_SETUP              0x16
#define SMARTNFC_CMD_LOG_FORWARDING             0xE4
#define SMARTNFC_CMD_ERROR                      0xFF

/**
 * @brief Smart NFC response timeout settings.
 * @details Specified response timeout settings of Smart NFC Click driver.
 */
#define SMARTNFC_RSP_TIMEOUT_1000MS             1000
#define SMARTNFC_RSP_NUM_TRIES                  3

/**
 * @brief Smart NFC driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define SMARTNFC_TX_DRV_BUFFER_SIZE             200
#define SMARTNFC_RX_DRV_BUFFER_SIZE             500
#define SMARTNFC_PAYLOAD_BUFFER_SIZE            500

/*! @} */ // smartnfc_cmd

/**
 * @defgroup smartnfc_map Smart NFC MikroBUS Map
 * @brief MikroBUS pin mapping of Smart NFC Click driver.
 */

/**
 * @addtogroup smartnfc_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart NFC Click to the selected MikroBUS.
 */
#define SMARTNFC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \

/*! @} */ // smartnfc_map
/*! @} */ // smartnfc

/**
 * @brief Smart NFC Click command frame structure object.
 * @details Command frame structure object definition of Smart NFC Click driver.
 */
typedef struct
{
    uint8_t cmd;                                        /**< Command code. */
    uint8_t payload[ SMARTNFC_PAYLOAD_BUFFER_SIZE ];    /**< Payload buffer. */
    uint16_t payload_len;                               /**< Payload length. */
    
} smartnfc_frame_t;

/**
 * @brief Smart NFC Click context object.
 * @details Context object definition of Smart NFC Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ SMARTNFC_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ SMARTNFC_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    smartnfc_frame_t cmd_frame;     /**< Command frame structure. */
    smartnfc_frame_t rsp_frame;     /**< Response frame structure. */

} smartnfc_t;

/**
 * @brief Smart NFC Click configuration object.
 * @details Configuration object definition of Smart NFC Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} smartnfc_cfg_t;

/**
 * @brief Smart NFC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTNFC_OK = 0,
    SMARTNFC_ERROR = -1,
    SMARTNFC_ERROR_TIMEOUT = -2

} smartnfc_return_value_t;

/*!
 * @addtogroup smartnfc Smart NFC Click Driver
 * @brief API for configuring and manipulating Smart NFC Click driver.
 * @{
 */

/**
 * @brief Smart NFC configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartnfc_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartnfc_cfg_setup ( smartnfc_cfg_t *cfg );

/**
 * @brief Smart NFC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #smartnfc_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartnfc_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartnfc_init ( smartnfc_t *ctx, smartnfc_cfg_t *cfg );

/**
 * @brief Smart NFC data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #smartnfc_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartnfc_generic_write ( smartnfc_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Smart NFC data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #smartnfc_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartnfc_generic_read ( smartnfc_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Smart NFC set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #smartnfc_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void smartnfc_set_rst_pin ( smartnfc_t *ctx, uint8_t state );

/**
 * @brief Smart NFC reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #smartnfc_t object definition for detailed explanation.
 * @return @li @c  0 - Correct frame received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartnfc_reset_device ( smartnfc_t *ctx );

/**
 * @brief Smart NFC send frame function.
 * @details This function sends a desired command frame from the Click context object.
 * @param[in] ctx : Click context object.
 * See #smartnfc_t object definition for detailed explanation.
 * @return @li @c  0 - Frame is sent,
 *         @li @c -1 - Timeout error.
 * @note None.
 */
err_t smartnfc_send_frame ( smartnfc_t *ctx );

/**
 * @brief Smart NFC read frame function.
 * @details This function reads response frame from the ring buffer and stores it in
 * the Click context object. It waits up to 1 second for a frame, and if there's no frame
 * received it returns an error.
 * @param[in] ctx : Click context object.
 * See #smartnfc_t object definition for detailed explanation.
 * @return @li @c  0 - Correct frame received,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartnfc_read_frame ( smartnfc_t *ctx );

/**
 * @brief Smart NFC read ack frame function.
 * @details This function waits for the desired acknowledge frame to arrive and stores it
 * in the Click context object.
 * @param[in] ctx : Click context object.
 * See #smartnfc_t object definition for detailed explanation.
 * @param[in] cmd : Expected frame command byte.
 * @return @li @c  0 - Correct frame received,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartnfc_read_ack_frame ( smartnfc_t *ctx, uint8_t cmd );

/**
 * @brief Smart NFC clear buffers function.
 * @details This function clears the ring buffers and the response frame object.
 * @param[in] ctx : Click context object.
 * See #smartnfc_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartnfc_clear_buffers ( smartnfc_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SMARTNFC_H

/*! @} */ // smartnfc

// ------------------------------------------------------------------------ END
