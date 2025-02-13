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
 * @file bt122a.h
 * @brief This file contains API for BT122-A Click Driver.
 */

#ifndef BT122A_H
#define BT122A_H

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
 * @addtogroup bt122a BT122-A Click Driver
 * @brief API for configuring and manipulating BT122-A Click driver.
 * @{
 */

/**
 * @defgroup bt122a_cmd BT122-A Device Settings
 * @brief Settings for registers of BT122-A Click driver.
 */

/**
 * @addtogroup bt122a_cmd
 * @{
 */

/**
 * @brief BT122-A message type setting.
 * @details Specified settings for message type of BT122-A Click driver.
 */
#define BT122A_MSG_TYPE_COMMAND                 0x20
#define BT122A_MSG_TYPE_RESPONSE                0x20
#define BT122A_MSG_TYPE_EVENT                   0xA0

/**
 * @brief BT122-A message class setting.
 * @details Specified settings for message class of BT122-A Click driver.
 */
#define BT122A_MSG_CLASS_DFU                    0x00
#define BT122A_MSG_CLASS_SYSTEM                 0x01
#define BT122A_MSG_CLASS_GAP                    0x02
#define BT122A_MSG_CLASS_LE_GAP                 0x03
#define BT122A_MSG_CLASS_RFCOMM                 0x04
#define BT122A_MSG_CLASS_IDENTITY               0x05
#define BT122A_MSG_CLASS_SDP                    0x06
#define BT122A_MSG_CLASS_CONNECTION             0x07
#define BT122A_MSG_CLASS_LE_CONNECTION          0x08
#define BT122A_MSG_CLASS_GATT                   0x09
#define BT122A_MSG_CLASS_GATT_SERVER            0x0A
#define BT122A_MSG_CLASS_ENDPOINT               0x0B
#define BT122A_MSG_CLASS_HARDWARE               0x0C
#define BT122A_MSG_CLASS_FLASH_PS               0x0D
#define BT122A_MSG_CLASS_TEST                   0x0E
#define BT122A_MSG_CLASS_SM                     0x0F
#define BT122A_MSG_CLASS_UTIL                   0x11
#define BT122A_MSG_CLASS_HID                    0x13
#define BT122A_MSG_CLASS_LE_SERIAL              0x14

/**
 * @brief BT122-A message ID setting.
 * @details Specified settings for message ID of BT122-A Click driver.
 * @note Refer to the BT122 API reference manual for more message IDs.
 */
#define BT122A_MSG_ID_SYSTEM_RESET              0x01
#define BT122A_MSG_ID_SYSTEM_GET_BT_ADDRESS     0x03
#define BT122A_MSG_ID_SYSTEM_GET_CLASS_OF_DEV   0x05
#define BT122A_MSG_ID_SYSTEM_SET_CLASS_OF_DEV   0x06
#define BT122A_MSG_ID_SYSTEM_FACTORY_RESET      0x07
#define BT122A_MSG_ID_SYSTEM_SET_LOCAL_NAME     0x08
#define BT122A_MSG_ID_SYSTEM_GET_LOCAL_NAME     0x09
#define BT122A_MSG_ID_SM_SET_BONDABLE_MODE      0x00
#define BT122A_MSG_ID_SM_DELETE_BONDINGS        0x07
#define BT122A_MSG_ID_GAP_SET_MODE              0x03
#define BT122A_MSG_ID_ENDPOINT_SEND_DATA        0x00
#define BT122A_MSG_ID_RFCOMM_START_SERVER       0x01
#define BT122A_MSG_ID_RFCOMM_STOP_SERVER        0x03
#define BT122A_MSG_ID_EVT_ENDPOINT_DATA         0x01
#define BT122A_MSG_ID_EVT_CONNECTION_OPENED     0x00
#define BT122A_MSG_ID_EVT_CONNECTION_CLOSED     0x01
#define BT122A_MSG_ID_EVT_SM_BONDED             0x03
#define BT122A_MSG_ID_EVT_RFCOMM_OPENED         0x00
#define BT122A_MSG_ID_EVT_RFCOMM_MODEM_STATUS   0x01

/**
 * @brief BT122-A reset mode setting.
 * @details Specified settings for reset mode of BT122-A Click driver.
 */
#define BT122A_SYSTEM_RESET_NORMAL              0x00
#define BT122A_SYSTEM_RESET_BOOT_TO_DFU         0x01

/**
 * @brief BT122-A bondable mode setting.
 * @details Specified settings for bondable mode of BT122-A Click driver.
 */
#define BT122A_SM_SET_BONDABLE_NOT_ACCEPTED     0x00
#define BT122A_SM_SET_BONDABLE_ALLOWED          0x01

/**
 * @brief BT122-A gap mode setting.
 * @details Specified settings for gap mode of BT122-A Click driver.
 */
#define BT122A_GAP_MODE_NOT_CONNECTABLE         0x00
#define BT122A_GAP_MODE_CONNECTABLE             0x01
#define BT122A_GAP_MODE_NOT_DISCOVERABLE        0x00
#define BT122A_GAP_MODE_DISCOVERABLE            0x01
#define BT122A_GAP_MODE_NOT_LIMITED             0x00
#define BT122A_GAP_MODE_LIMITED                 0x01

/**
 * @brief BT122-A rfcomm server setting.
 * @details Specified settings for rfcomm server of BT122-A Click driver.
 */
#define BT122A_RFCOMM_SERVER_DEF_SDP_ID         0x02
#define BT122A_RFCOMM_SERVER_DEF_STREAM_DEST    0x00

/**
 * @brief BT122-A response timeout settings.
 * @details Specified response timeout settings of BT122-A Click driver.
 */
#define BT122A_RSP_TIMEOUT_1000MS               1000

/**
 * @brief BT122-A driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BT122A_TX_DRV_BUFFER_SIZE               256
#define BT122A_RX_DRV_BUFFER_SIZE               256
#define BT122A_MAX_PAYLOAD_LEN                  64

/*! @} */ // bt122a_cmd

/**
 * @defgroup bt122a_map BT122-A MikroBUS Map
 * @brief MikroBUS pin mapping of BT122-A Click driver
 */

/**
 * @addtogroup bt122a_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BT122-A Click to the selected MikroBUS.
 */
#define BT122A_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // bt122a_map
/*! @} */ // bt122a

/**
 * @brief BT122-A Click context object.
 * @details Context object definition of BT122-A Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< Clear to send pin. */

    // Input pins
    digital_in_t rts;               /**< Request to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BT122A_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ BT122A_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} bt122a_t;

/**
 * @brief BT122-A Click configuration object.
 * @details Configuration object definition of BT122-A Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cts;                 /**< Clear to send pin. */
    pin_name_t rts;                 /**< Request to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} bt122a_cfg_t;

/**
 * @brief BT122-A Click packet structure object.
 * @details Packet structure object definition of BT122-A Click driver.
 */
typedef struct
{
    uint8_t msg_type;
    uint8_t payload_len;
    uint8_t msg_class;
    uint8_t msg_id;
    uint8_t payload[ BT122A_MAX_PAYLOAD_LEN ];

} bt122a_package_t;

/**
 * @brief BT122-A Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BT122A_OK = 0,
    BT122A_ERROR = -1

} bt122a_return_value_t;

/*!
 * @addtogroup bt122a BT122-A Click Driver
 * @brief API for configuring and manipulating BT122-A Click driver.
 * @{
 */

/**
 * @brief BT122-A configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bt122a_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bt122a_cfg_setup ( bt122a_cfg_t *cfg );

/**
 * @brief BT122-A initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bt122a_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_init ( bt122a_t *ctx, bt122a_cfg_t *cfg );

/**
 * @brief BT122-A data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_generic_write ( bt122a_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief BT122-A data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_generic_read ( bt122a_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief BT122-A set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bt122a_set_rst_pin ( bt122a_t *ctx, uint8_t state );

/**
 * @brief BT122-A reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bt122a_reset_device ( bt122a_t *ctx );

/**
 * @brief BT122-A set CTS pin function.
 * @details This function sets the clear to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bt122a_set_cts_pin ( bt122a_t *ctx, uint8_t state );

/**
 * @brief BT122-A get RTS pin function.
 * @details This function returns the request to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t bt122a_get_rts_pin ( bt122a_t *ctx );

/**
 * @brief BT122-A send package function.
 * @details This function sends a data package to the Click board.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] pkg : Data package to be written.
 * See #bt122a_package_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void bt122a_send_package ( bt122a_t *ctx, bt122a_package_t pkg );

/**
 * @brief BT122-A read package function.
 * @details This function waits for the command or event type of message to arrive and then 
 * reads the complete message and stores it to the @b pkg structure.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[out] pkg : Pointer to structure where the read data is being stored.
 * See #bt122a_package_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_read_package ( bt122a_t *ctx, bt122a_package_t *pkg );

/**
 * @brief BT122-A set local name function.
 * @details This function sets the local name of the device.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] name : Local device name ( up to 30 characters ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_set_local_name ( bt122a_t *ctx, uint8_t *name );

/**
 * @brief BT122-A set bondable mode function.
 * @details This function sets the bondable mode of the device.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] mode : @li @c  0 - Not accepted,
 *                   @li @c  1 - Allowed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_set_bondable_mode ( bt122a_t *ctx, uint8_t mode );

/**
 * @brief BT122-A delete bondings function.
 * @details This function deletes all bondings.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_delete_bondings ( bt122a_t *ctx );

/**
 * @brief BT122-A set class of device function.
 * @details This function sets the class of the device.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] cod : Class of the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_set_class_of_device ( bt122a_t *ctx, uint32_t cod );

/**
 * @brief BT122-A set gap mode function.
 * @details This function sets the GAP mode.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] connectable : @li @c  0 - Not connectable,
 *                          @li @c  1 - Connectable.
 * @param[in] discoverable : @li @c  0 - Not discoverable,
 *                           @li @c  1 - Discoverable.
 * @param[in] limited : @li @c  0 - Limited,
 *                      @li @c  1 - Not limited.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_set_gap_mode ( bt122a_t *ctx, uint8_t connectable, uint8_t discoverable, uint8_t limited );

/**
 * @brief BT122-A rfcomm start server function.
 * @details This function starts the RFCOMM server as defined in the SDP-entry.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] sdp_id : ID of the SDP entry [ Default: 0x02 ].
 * @param[in] stream_dest : Streaming destination [ Default: 0x00 ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_rfcomm_start_server ( bt122a_t *ctx, uint8_t sdp_id, uint8_t stream_dest );

/**
 * @brief BT122-A rfcomm stop server function.
 * @details This function stops the RFCOMM server.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] sdp_id : ID of the SDP entry [ Default: 0x02 ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_rfcomm_stop_server ( bt122a_t *ctx, uint8_t sdp_id );

/**
 * @brief BT122-A factory reset function.
 * @details This function resets the device to factory settings.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_factory_reset ( bt122a_t *ctx );

/**
 * @brief BT122-A system reset function.
 * @details This function resets the device.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in] mode : @li @c  0 - Normal reset,
 *                   @li @c  1 - Boot to DFU.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_system_reset ( bt122a_t *ctx, uint8_t mode );

/**
 * @brief BT122-A endpoint send data function.
 * @details This function sends data to the defined endpoint.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @param[in,out] endpoint : The pointer to index of the endpoint to which the data will be sent.
 * It will be overwritten by the endpoint index value of the response to this command.
 * @param[in] msg : Data to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt122a_endpoint_send_data ( bt122a_t *ctx, uint8_t *endpoint, uint8_t *msg );

#ifdef __cplusplus
}
#endif
#endif // BT122A_H

/*! @} */ // bt122a

// ------------------------------------------------------------------------ END
