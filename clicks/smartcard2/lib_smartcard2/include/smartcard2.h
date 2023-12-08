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
 * @file smartcard2.h
 * @brief This file contains API for Smart Card 2 Click Driver.
 */

#ifndef SMARTCARD2_H
#define SMARTCARD2_H

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
 * @addtogroup smartcard2 Smart Card 2 Click Driver
 * @brief API for configuring and manipulating Smart Card 2 Click driver.
 * @{
 */

/**
 * @defgroup smartcard2_cmd Smart Card 2 Device Settings
 * @brief Settings for registers of Smart Card 2 Click driver.
 */

/**
 * @addtogroup smartcard2_cmd
 * @{
 */

/**
 * @brief Smart Card 2 command pipe, bulk-out commands.
 * @details Specified setting for command pipe, bulk-out commands of Smart Card 2 Click driver.
 */
#define SMARTCARD2_CMD_ICC_POWER_ON             0x62
#define SMARTCARD2_CMD_ICC_POWER_OFF            0x63
#define SMARTCARD2_CMD_GET_SLOT_STATUS          0x65
#define SMARTCARD2_CMD_XFR_BLOCK                0x6F
#define SMARTCARD2_CMD_GET_PARAMETERS           0x6C
#define SMARTCARD2_CMD_RESET_PARAMETERS         0x6D
#define SMARTCARD2_CMD_SET_PARAMETERS           0x61
#define SMARTCARD2_CMD_ESCAPE                   0x6B
#define SMARTCARD2_CMD_ICC_ESCAPE               0x6E
#define SMARTCARD2_CMD_T0_APDU                  0x6A
#define SMARTCARD2_CMD_SECURE                   0x69
#define SMARTCARD2_CMD_MECHANICAL               0x71
#define SMARTCARD2_CMD_ABORT                    0x72
#define SMARTCARD2_CMD_SET_DATA_RATE_CLK_FREQ   0x73

/**
 * @brief Smart Card 2 response pipe, bulk-in messages.
 * @details Specified setting for response pipe, bulk-in messages of Smart Card 2 Click driver.
 */
#define SMARTCARD2_RSP_DATA_BLOCK               0x80
#define SMARTCARD2_RSP_SLOT_STATUS              0x81
#define SMARTCARD2_RSP_PARAMETERS               0x82
#define SMARTCARD2_RSP_ESCAPE                   0x83
#define SMARTCARD2_RSP_DATA_RATE_CLK_FREQ       0x84

/**
 * @brief Smart Card 2 interrupt-in messages.
 * @details Specified setting for interrupt-in messages of Smart Card 2 Click driver.
 */
#define SMARTCARD2_EVT_NOTIFY_SLOT_CHANGE       0x50
#define SMARTCARD2_CARD_ABSENT                  0x02
#define SMARTCARD2_CARD_PRESENT                 0x03
#define SMARTCARD2_EVT_HARDWARE_ERROR           0x51
#define SMARTCARD2_OVERCURRENT                  0x01

/**
 * @brief Smart Card 2 ccid message settings.
 * @details Specified setting for ccid message of Smart Card 2 Click driver.
 */
#define SMARTCARD2_SYNC                         0x03
#define SMARTCARD2_CTRL_ACK                     0x06
#define SMARTCARD2_CTRL_NACK                    0x15
#define SMARTCARD2_SHORT_APDU_MAX_SIZE          261
// sync + ack + 10-byte ccid header + short APDU size + checksum
#define SMARTCARD2_MAX_BUF_SIZE                 ( SMARTCARD2_SHORT_APDU_MAX_SIZE + 13 )
#define SMARTCARD2_TIMEOUT_MS                   5000

/**
 * @brief Smart Card 2 clock status bytes.
 * @details Specified setting for clock status bytes of Smart Card 2 Click driver.
 */
#define SMARTCARD2_CLK_STATUS_RUNNING           0x00
#define SMARTCARD2_CLK_STATUS_STATE_L           0x01
#define SMARTCARD2_CLK_STATUS_STATE_H           0x02

/**
 * @brief Smart Card 2 power select bytes.
 * @details Specified setting for power select bytes of Smart Card 2 Click driver.
 */
#define SMARTCARD2_POWER_SEL_AUTO               0x00
#define SMARTCARD2_POWER_SEL_5V                 0x01
#define SMARTCARD2_POWER_SEL_3V                 0x02
#define SMARTCARD2_POWER_SEL_1_8V               0x03

/**
 * @brief Smart Card 2 ICC status setting.
 * @details Specified setting for ICC status of Smart Card 2 Click driver.
 */
#define SMARTCARD2_ICC_ACTIVE                   0
#define SMARTCARD2_ICC_PRESENT                  1
#define SMARTCARD2_ICC_ABSENT                   2
#define SMARTCARD2_ICC_STATUS_MASK              0x03

/**
 * @brief Smart Card 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define SMARTCARD2_TX_DRV_BUFFER_SIZE           SMARTCARD2_MAX_BUF_SIZE
#define SMARTCARD2_RX_DRV_BUFFER_SIZE           ( SMARTCARD2_MAX_BUF_SIZE * 2 )

/*! @} */ // smartcard2_cmd

/**
 * @defgroup smartcard2_map Smart Card 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart Card 2 Click driver.
 */

/**
 * @addtogroup smartcard2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart Card 2 Click to the selected MikroBUS.
 */
#define SMARTCARD2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // smartcard2_map
/*! @} */ // smartcard2

/**
 * @brief Smart Card 2 Click context object.
 * @details Context object definition of Smart Card 2 Click driver.
 */
typedef struct
{
    uint8_t type;               /**< Message type. */
    uint32_t payload_size;      /**< Message specific data length. */
    uint8_t slot_num;           /**< The slot number for command. */
    uint8_t seq_num;            /**< The sequence number for command. */
    uint8_t spec_bytes[ 3 ];    /**< Either three message specific bytes, or a status field (1 byte), 
                                     an error field and one message specific byte. */
    uint8_t payload[ SMARTCARD2_SHORT_APDU_MAX_SIZE ];  /**< Message content. */
    
} smartcard2_ccid_t;

/**
 * @brief Smart Card 2 Click context object.
 * @details Context object definition of Smart Card 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                  /**< Reset pin (Active high). */

    // Modules
    uart_t uart;                        /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ SMARTCARD2_RX_DRV_BUFFER_SIZE ];   /**< Buffer size. */
    char uart_tx_buffer[ SMARTCARD2_TX_DRV_BUFFER_SIZE ];   /**< Buffer size. */
    
    uint8_t seq_num;                    /**< The sequence num of the last command sent. Updates on
                                             each call of smartcard2_send_ccid() function. */

} smartcard2_t;

/**
 * @brief Smart Card 2 Click configuration object.
 * @details Configuration object definition of Smart Card 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Reset pin (Active low). */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} smartcard2_cfg_t;

/**
 * @brief Smart Card 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTCARD2_OK = 0,
    SMARTCARD2_ERROR = -1,
    SMARTCARD2_READ_ERROR = -2,
    SMARTCARD2_CHECKSUM_ERROR = -3,
    SMARTCARD2_TIMEOUT_ERROR = -4,

} smartcard2_return_value_t;

/*!
 * @addtogroup smartcard2 Smart Card 2 Click Driver
 * @brief API for configuring and manipulating Smart Card 2 Click driver.
 * @{
 */

/**
 * @brief Smart Card 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartcard2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartcard2_cfg_setup ( smartcard2_cfg_t *cfg );

/**
 * @brief Smart Card 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #smartcard2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartcard2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartcard2_init ( smartcard2_t *ctx, smartcard2_cfg_t *cfg );

/**
 * @brief Smart Card 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #smartcard2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartcard2_generic_write ( smartcard2_t *ctx, char *data_in, uint16_t len );

/**
 * @brief Smart Card 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #smartcard2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartcard2_generic_read ( smartcard2_t *ctx, char *data_out, uint16_t len );

/**
 * @brief Smart Card 2 enable device function.
 * @details This function enables device by setting the RST pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #smartcard2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartcard2_enable_device ( smartcard2_t *ctx );

/**
 * @brief Smart Card 2 disable device function.
 * @details This function disables device by setting the RST pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #smartcard2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartcard2_disable_device ( smartcard2_t *ctx );

/**
 * @brief Smart Card 2 send ccid function.
 * @details This function sends the CCID command message by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #smartcard2_t object definition for detailed explanation.
 * @param[in] data_in : CCID command message.
 * See #smartcard2_ccid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - wrong parameter,
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartcard2_send_ccid ( smartcard2_t *ctx, smartcard2_ccid_t *data_in );

/**
 * @brief Smart Card 2 read ccid function.
 * @details This function reads a CCID response or event message by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #smartcard2_t object definition for detailed explanation.
 * @param[out] data_out : CCID response message.
 * See #smartcard2_ccid_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - wrong parameter,
 *         @li @c -2 - Error - read,
 *         @li @c -3 - Error - checksum,
 *         @li @c -4 - Error - timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartcard2_read_ccid ( smartcard2_t *ctx, smartcard2_ccid_t *data_out );

/**
 * @brief Smart Card 2 icc power on function.
 * @details This function activates the card by performing an ICC power ON command.
 * The device will respond with a data block containing ICC ATR (Answer to Reset) message.
 * @param[in] ctx : Click context object.
 * See #smartcard2_t object definition for detailed explanation.
 * @param[in] power_sel : Power selection: @li @c 0 - Auto,
 *                                         @li @c 1 - 5V,
 *                                         @li @c 2 - 3V,
 *                                         @li @c 3 - 1.8V.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - wrong parameter.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartcard2_icc_power_on ( smartcard2_t *ctx, uint8_t power_sel );

/**
 * @brief Smart Card 2 icc power off function.
 * @details This function deactivates the card by performing an ICC power OFF command.
 * The device will respond with a slot status message.
 * @param[in] ctx : Click context object.
 * See #smartcard2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - wrong parameter.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartcard2_icc_power_off ( smartcard2_t *ctx );

/**
 * @brief Smart Card 2 get slot status function.
 * @details This function performs a get slot status command.
 * The device will respond with a slot status message.
 * @param[in] ctx : Click context object.
 * See #smartcard2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - wrong parameter.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartcard2_get_slot_status ( smartcard2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SMARTCARD2_H

/*! @} */ // smartcard2

// ------------------------------------------------------------------------ END
