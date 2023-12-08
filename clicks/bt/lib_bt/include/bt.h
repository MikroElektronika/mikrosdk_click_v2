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
 * @file bt.h
 * @brief This file contains API for BT Click Driver.
 */

#ifndef BT_H
#define BT_H

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
 * @addtogroup bt BT Click Driver
 * @brief API for configuring and manipulating BT Click driver.
 * @{
 */

/**
 * @defgroup bt_set BT Device Settings
 * @brief Settings for BT Click driver.
 */

/**
 * @addtogroup bt_set
 * @{
 */

/**
 * @brief BT message type setting.
 * @details Specified settings for message type of BT Click driver.
 */
#define BT_MSG_TYPE_COMMAND                 0x20
#define BT_MSG_TYPE_RESPONSE                0x20
#define BT_MSG_TYPE_EVENT                   0xA0

/**
 * @brief BT message class setting.
 * @details Specified settings for message class of BT Click driver.
 */
#define BT_MSG_CLASS_DFU                    0x00
#define BT_MSG_CLASS_SYSTEM                 0x01
#define BT_MSG_CLASS_GAP                    0x02
#define BT_MSG_CLASS_LE_GAP                 0x03
#define BT_MSG_CLASS_RFCOMM                 0x04
#define BT_MSG_CLASS_IDENTITY               0x05
#define BT_MSG_CLASS_SDP                    0x06
#define BT_MSG_CLASS_CONNECTION             0x07
#define BT_MSG_CLASS_LE_CONNECTION          0x08
#define BT_MSG_CLASS_GATT                   0x09
#define BT_MSG_CLASS_GATT_SERVER            0x0A
#define BT_MSG_CLASS_ENDPOINT               0x0B
#define BT_MSG_CLASS_HARDWARE               0x0C
#define BT_MSG_CLASS_FLASH_PS               0x0D
#define BT_MSG_CLASS_TEST                   0x0E
#define BT_MSG_CLASS_SM                     0x0F
#define BT_MSG_CLASS_UTIL                   0x11
#define BT_MSG_CLASS_HID                    0x13
#define BT_MSG_CLASS_LE_SERIAL              0x14

/**
 * @brief BT message ID setting.
 * @details Specified settings for message ID of BT Click driver.
 * @note Refer to the BT121 API reference manual for more message IDs.
 */
#define BT_MSG_ID_SYSTEM_RESET              0x01
#define BT_MSG_ID_SYSTEM_GET_BT_ADDRESS     0x03
#define BT_MSG_ID_SYSTEM_GET_CLASS_OF_DEV   0x05
#define BT_MSG_ID_SYSTEM_SET_CLASS_OF_DEV   0x06
#define BT_MSG_ID_SYSTEM_FACTORY_RESET      0x07
#define BT_MSG_ID_SYSTEM_SET_LOCAL_NAME     0x08
#define BT_MSG_ID_SYSTEM_GET_LOCAL_NAME     0x09
#define BT_MSG_ID_SM_SET_BONDABLE_MODE      0x00
#define BT_MSG_ID_SM_DELETE_BONDINGS        0x07
#define BT_MSG_ID_GAP_SET_MODE              0x03
#define BT_MSG_ID_HARDWARE_CONFIG_GPIO      0x01
#define BT_MSG_ID_HARDWARE_WRITE_GPIO       0x02
#define BT_MSG_ID_HARDWARE_READ_GPIO        0x03
#define BT_MSG_ID_ENDPOINT_SEND_DATA        0x00
#define BT_MSG_ID_RFCOMM_START_SERVER       0x01
#define BT_MSG_ID_RFCOMM_STOP_SERVER        0x03
#define BT_MSG_ID_EVT_ENDPOINT_DATA         0x01
#define BT_MSG_ID_EVT_CONNECTION_OPENED     0x00
#define BT_MSG_ID_EVT_CONNECTION_CLOSED     0x01
#define BT_MSG_ID_EVT_SM_BONDED             0x03
#define BT_MSG_ID_EVT_RFCOMM_OPENED         0x00
#define BT_MSG_ID_EVT_RFCOMM_MODEM_STATUS   0x01

/**
 * @brief BT reset mode setting.
 * @details Specified settings for reset mode of BT Click driver.
 */
#define BT_SYSTEM_RESET_NORMAL              0x00
#define BT_SYSTEM_RESET_BOOT_TO_DFU         0x01

/**
 * @brief BT bondable mode setting.
 * @details Specified settings for bondable mode of BT Click driver.
 */
#define BT_SM_SET_BONDABLE_NOT_ACCEPTED     0x00
#define BT_SM_SET_BONDABLE_ALLOWED          0x01

/**
 * @brief BT gap mode setting.
 * @details Specified settings for gap mode of BT Click driver.
 */
#define BT_GAP_MODE_NOT_CONNECTABLE         0x00
#define BT_GAP_MODE_CONNECTABLE             0x01
#define BT_GAP_MODE_NOT_DISCOVERABLE        0x00
#define BT_GAP_MODE_DISCOVERABLE            0x01
#define BT_GAP_MODE_NOT_LIMITED             0x00
#define BT_GAP_MODE_LIMITED                 0x01

/**
 * @brief BT rfcomm server setting.
 * @details Specified settings for rfcomm server of BT Click driver.
 */
#define BT_RFCOMM_SERVER_DEF_SDP_ID         0x02
#define BT_RFCOMM_SERVER_DEF_STREAM_DEST    0x00

/**
 * @brief BT hardware config gpio setting.
 * @details Specified settings for hardware config gpio of BT Click driver.
 */
#define BT_HARDWARE_CONFIG_PORT_A           0x00
#define BT_HARDWARE_CONFIG_PORT_B           0x01
#define BT_HARDWARE_CONFIG_GPIO_FLOAT       0x00
#define BT_HARDWARE_CONFIG_GPIO_PULLUP      0x01
#define BT_HARDWARE_CONFIG_GPIO_PULLDOWN    0x02
#define BT_HARDWARE_CONFIG_GPIO_INPUT       0x00
#define BT_HARDWARE_CONFIG_GPIO_OUTPUT      0x01
#define BT_HARDWARE_CONFIG_GPIO_FUNCTION    0x02
#define BT_HARDWARE_CONFIG_GPIO_ANALOG      0x03
#define BT_HARDWARE_BUTTON1_PIN_INDEX       0x08
#define BT_HARDWARE_BUTTON2_PIN_INDEX       0x09
#define BT_HARDWARE_BUTTON3_PIN_INDEX       0x0A
#define BT_HARDWARE_BUTTON4_PIN_INDEX       0x0C
#define BT_HARDWARE_BUTTON5_PIN_INDEX       0x0D
#define BT_HARDWARE_LED1_PIN_INDEX          0x0E
#define BT_HARDWARE_LED2_PIN_INDEX          0x0F
#define BT_HARDWARE_BUTTON1_PIN_MASK        0x0100
#define BT_HARDWARE_BUTTON2_PIN_MASK        0x0200
#define BT_HARDWARE_BUTTON3_PIN_MASK        0x0400
#define BT_HARDWARE_BUTTON4_PIN_MASK        0x1000
#define BT_HARDWARE_BUTTON5_PIN_MASK        0x2000
#define BT_HARDWARE_ALL_BUTTONS_PIN_MASK    0x3700
#define BT_HARDWARE_LED1_PIN_MASK           0x4000
#define BT_HARDWARE_LED2_PIN_MASK           0x8000
#define BT_HARDWARE_ALL_LEDS_PIN_MASK       0xC000

/**
 * @brief BT payload setting.
 * @details Specified settings for payload of BT Click driver.
 */
#define BT_MAX_PAYLOAD_LEN                  0x40

/**
 * @brief BT driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                     200

/*! @} */ // bt_set

/**
 * @defgroup bt_map BT MikroBUS Map
 * @brief MikroBUS pin mapping of BT Click driver.
 */

/**
 * @addtogroup bt_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BT Click to the selected MikroBUS.
 */
#define BT_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.an  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.bt0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // bt_map
/*! @} */ // bt

/**
 * @brief BT Click context object.
 * @details Context object definition of BT Click driver.
 */
typedef struct
{
    digital_out_t an;                        /**< GPIO. */
    digital_out_t rst;                       /**< Reset. */
    digital_out_t cts;                       /**< Clear to send. */
    digital_out_t bt0;                       /**< Boot mode. */

    digital_in_t rts;                        /**< Request to send. */

    // Modules
    uart_t uart;                             /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];  /**< Buffer size. */

} bt_t;

/**
 * @brief BT Click configuration object.
 * @details Configuration object definition of BT Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                       /**< RX pin. */
    pin_name_t tx_pin;                       /**< TX pin. */

    // Additional gpio pins
    pin_name_t an;                           /**< GPIO. */
    pin_name_t rst;                          /**< Reset. */
    pin_name_t cts;                          /**< Clear to send. */
    pin_name_t bt0;                          /**< Boot mode. */
    pin_name_t rts;                          /**< Request to send. */

    // Static variable
    uint32_t          baud_rate;             /**< Clock speed. */
    bool              uart_blocking;         /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;              /**< Data bits. */
    uart_parity_t     parity_bit;            /**< Parity bit. */
    uart_stop_bits_t  stop_bit;              /**< Stop bits. */

} bt_cfg_t;

/**
 * @brief BT Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BT_OK = 0,
    BT_ERROR = -1

} bt_return_value_t;

/**
 * @brief BT Click packet structure object.
 * @details Packet structure object definition of BT Click driver.
 */
typedef struct
{
    uint8_t msg_type;
    uint8_t payload_len;
    uint8_t msg_class;
    uint8_t msg_id;
    uint8_t payload[ BT_MAX_PAYLOAD_LEN ];

} bt_package_t;

/*!
 * @addtogroup bt BT Click Driver
 * @brief API for configuring and manipulating BT Click driver.
 * @{
 */

/**
 * @brief BT configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bt_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bt_cfg_setup ( bt_cfg_t *cfg );

/**
 * @brief BT initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bt_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_init ( bt_t *ctx, bt_cfg_t *cfg );

/**
 * @brief BT default configuration function.
 * @details This function executes a default configuration of BT
 * click board.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t bt_default_cfg ( bt_t *ctx );

/**
 * @brief BT data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_generic_write ( bt_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief BT data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_generic_read ( bt_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief BT set AN pin function.
 * @details This function sets the AN pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bt_set_an_pin ( bt_t *ctx, uint8_t state );

/**
 * @brief BT set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bt_set_rst_pin ( bt_t *ctx, uint8_t state );

/**
 * @brief BT set CTS pin function.
 * @details This function sets the CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bt_set_cts_pin ( bt_t *ctx, uint8_t state );

/**
 * @brief BT set BT0 pin function.
 * @details This function sets the BT0 pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void bt_set_bt0_pin ( bt_t *ctx, uint8_t state );

/**
 * @brief BT get RTS pin function.
 * @details This function returns the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t bt_get_rts_pin ( bt_t *ctx );

/**
 * @brief BT send package function.
 * @details This function sends a data package to the click board.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] pkg : Data package to be written.
 * See #bt_package_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_send_package ( bt_t *ctx, bt_package_t pkg );

/**
 * @brief BT read package function.
 * @details This function waits for the command or event type of message to arrive and then 
 * reads the complete message and stores it to @b pkg structure.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[out] pkg : Pointer to structure where the read data is being stored.
 * See #bt_package_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_read_package ( bt_t *ctx, bt_package_t *pkg );

/**
 * @brief BT set local name function.
 * @details This function sets the local name of the device.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] name : Local device name ( up to 30 characters ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_set_local_name ( bt_t *ctx, char *name );

/**
 * @brief BT set bondable mode function.
 * @details This function sets the bondable mode of the device.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] mode : @li @c  0 - Not accepted,
 *                   @li @c  1 - Allowed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_set_bondable_mode ( bt_t *ctx, uint8_t mode );

/**
 * @brief BT delete bondings function.
 * @details This function deletes all bondings.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_delete_bondings ( bt_t *ctx );

/**
 * @brief BT set class of device function.
 * @details This function sets the class of the device.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] cod : Class of the device.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_set_class_of_device ( bt_t *ctx, uint32_t cod );

/**
 * @brief BT set gap mode function.
 * @details This function sets the GAP mode.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] connectable : @li @c  0 - Not connectable,
 *                          @li @c  1 - Connectable.
 * @param[in] discoverable : @li @c  0 - Not discoverable,
 *                           @li @c  1 - Discoverable.
 * @param[in] limited : @li @c  0 - Limited,
 *                      @li @c  1 - Not limited.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_set_gap_mode ( bt_t *ctx, uint8_t connectable, uint8_t discoverable, uint8_t limited );

/**
 * @brief BT rfcomm start server function.
 * @details This function starts the RFCOMM server as defined in the SDP-entry.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] sdp_id : ID of the SDP entry [ Default: 0x02 ].
 * @param[in] stream_dest : Streaming destination [ Default: 0x00 ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_rfcomm_start_server ( bt_t *ctx, uint8_t sdp_id, uint8_t stream_dest );

/**
 * @brief BT rfcomm stop server function.
 * @details This function stops the RFCOMM server.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] sdp_id : ID of the SDP entry [ Default: 0x02 ].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_rfcomm_stop_server ( bt_t *ctx, uint8_t sdp_id );

/**
 * @brief BT factory reset function.
 * @details This function resets the device to factory settings.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_factory_reset ( bt_t *ctx );

/**
 * @brief BT system reset function.
 * @details This function resets the device.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] mode : @li @c  0 - Normal reset,
 *                   @li @c  1 - Boot to DFU.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_system_reset ( bt_t *ctx, uint8_t mode );

/**
 * @brief BT hardware config gpio function.
 * @details This function configures the GPIO pins.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - PORT A,
 *                   @li @c  1 - PORT B.
 * @param[in] pin_index : The index of the GPIO pin on the port which this function affects. 
 * @param[in] mode : @li @c  0 - Input,
 *                   @li @c  1 - Output,
 *                   @li @c  2 - Function,
 *                   @li @c  3 - Analog.
 * @param[in] pullup : @li @c  0 - Float,
 *                     @li @c  1 - Pull-up,
 *                     @li @c  2 - Pull-down.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_hardware_config_gpio ( bt_t *ctx, uint8_t port, uint16_t pin_index, uint8_t mode, uint8_t pullup );

/**
 * @brief BT hardware read gpio function.
 * @details This function reads the state of a desired GPIO pins.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - PORT A,
 *                   @li @c  1 - PORT B.
 * @param[in] mask : Bitmask of which pins on the port should be read. 
 * @param[in] port_data : Port data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_hardware_read_gpio ( bt_t *ctx, uint8_t port, uint16_t mask, uint16_t *port_data );

/**
 * @brief BT hardware write gpio function.
 * @details This function sets the state of a desired GPIO pins.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in] port : @li @c  0 - PORT A,
 *                   @li @c  1 - PORT B.
 * @param[in] mask : Bitmask which determines the pins this function is used to set.
 * @param[in] port_data : Bitmask of which pins to set high and which pins to set low (1 - high, 0 - low).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_hardware_write_gpio ( bt_t *ctx, uint8_t port, uint16_t mask, uint16_t port_data );

/**
 * @brief BT endpoint send data function.
 * @details This function sends data to the defined endpoint.
 * @param[in] ctx : Click context object.
 * See #bt_t object definition for detailed explanation.
 * @param[in,out] endpoint : The pointer to index of the endpoint to which the data will be sent.
 * It will be overwritten by the endpoint index value of the response to this command.
 * @param[in] msg : Data to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bt_endpoint_send_data ( bt_t *ctx, uint8_t *endpoint, char *msg );

#ifdef __cplusplus
}
#endif
#endif // BT_H

/*! @} */ // bt

// ------------------------------------------------------------------------ END
