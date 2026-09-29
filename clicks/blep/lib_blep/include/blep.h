/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file blep.h
 * @brief This file contains API for BLE P Click Driver.
 */

#ifndef BLEP_H
#define BLEP_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup blep BLE P Click Driver
 * @brief API for configuring and manipulating BLE P Click driver.
 * @{
 */

/**
 * @defgroup blep_cmd BLE P Commands
 * @brief List of commands of BLE P Click driver.
 */

/**
 * @addtogroup blep_cmd
 * @{
 */

/**
 * @brief BLE P ACI command opcodes.
 * @details Binary commands carried over SPI.
 */
#define BLEP_CMD_TEST                                   0x01
#define BLEP_CMD_ECHO                                   0x02
#define BLEP_CMD_DTM_COMMAND                            0x03
#define BLEP_CMD_SLEEP                                  0x04
#define BLEP_CMD_WAKEUP                                 0x05
#define BLEP_CMD_SETUP                                  0x06
#define BLEP_CMD_READ_DYNAMIC_DATA                      0x07
#define BLEP_CMD_WRITE_DYNAMIC_DATA                     0x08
#define BLEP_CMD_GET_DEVICE_VERSION                     0x09
#define BLEP_CMD_GET_DEVICE_ADDRESS                     0x0A
#define BLEP_CMD_GET_BATTERY_LEVEL                      0x0B
#define BLEP_CMD_GET_TEMPERATURE                        0x0C
#define BLEP_CMD_SET_LOCAL_DATA                         0x0D
#define BLEP_CMD_RADIO_RESET                            0x0E
#define BLEP_CMD_CONNECT                                0x0F
#define BLEP_CMD_BOND                                   0x10
#define BLEP_CMD_DISCONNECT                             0x11
#define BLEP_CMD_SET_TX_POWER                           0x12
#define BLEP_CMD_CHANGE_TIMING                          0x13
#define BLEP_CMD_OPEN_REMOTE_PIPE                       0x14
#define BLEP_CMD_SEND_DATA                              0x15
#define BLEP_CMD_SEND_DATA_ACK                          0x16
#define BLEP_CMD_REQUEST_DATA                           0x17
#define BLEP_CMD_SEND_DATA_NACK                         0x18
#define BLEP_CMD_SET_APP_LATENCY                        0x19
#define BLEP_CMD_SET_KEY                                0x1A
#define BLEP_CMD_OPEN_ADV_PIPE                          0x1B
#define BLEP_CMD_BROADCAST                              0x1C
#define BLEP_CMD_BOND_SECURITY_REQUEST                  0x1D
#define BLEP_CMD_CONNECT_DIRECT                         0x1E
#define BLEP_CMD_CLOSE_REMOTE_PIPE                      0x1F

/*! @} */ // blep_cmd

/**
 * @defgroup blep_set BLE P Settings
 * @brief BLE P event, status, and UART profile definitions.
 */

/**
 * @addtogroup blep_set
 * @{
 */

/**
 * @brief BLE P event opcodes.
 * @details Identifies the asynchronous event returned by BLE P Click.
 */
#define BLEP_EVT_DEVICE_STARTED                         0x81
#define BLEP_EVT_ECHO                                   0x82
#define BLEP_EVT_HW_ERROR                               0x83
#define BLEP_EVT_COMMAND_RESPONSE                       0x84
#define BLEP_EVT_CONNECTED                              0x85
#define BLEP_EVT_DISCONNECTED                           0x86
#define BLEP_EVT_BOND_STATUS                            0x87
#define BLEP_EVT_PIPE_STATUS                            0x88
#define BLEP_EVT_TIMING                                 0x89
#define BLEP_EVT_DATA_CREDIT                            0x8A
#define BLEP_EVT_DATA_ACK                               0x8B
#define BLEP_EVT_DATA_RECEIVED                          0x8C
#define BLEP_EVT_PIPE_ERROR                             0x8D
#define BLEP_EVT_DISPLAY_PASSKEY                        0x8E
#define BLEP_EVT_KEY_REQUEST                            0x8F

/**
 * @brief BLE P command response status.
 * @details Setup returns CONTINUE for intermediate packets and COMPLETE for the last packet.
 */
#define BLEP_STATUS_SUCCESS                             0x00
#define BLEP_STATUS_CONTINUE                            0x01
#define BLEP_STATUS_COMPLETE                            0x02
#define BLEP_STATUS_PEER_ATT_ERROR                      0x92

/**
 * @brief BLE P operating modes.
 * @details DeviceStarted reports the current BLE P Click operating mode.
 */
#define BLEP_MODE_TEST                                  0x01
#define BLEP_MODE_SETUP                                 0x02
#define BLEP_MODE_STANDBY                               0x03
#define BLEP_MODE_SLEEP                                 0x04

/**
 * @brief BLE P packet limits.
 * @details ACI length includes its opcode; UART characteristic values contain up to 20 bytes.
 */
#define BLEP_PACKET_SIZE                                31
#define BLEP_EVENT_QUEUE_SIZE                           4
#define BLEP_UART_DATA_SIZE                             20

/**
 * @brief BLE P default UART profile pipes.
 * @details Pipe numbers match the Nordic UART profile included in blep_setup.h.
 */
#define BLEP_PIPE_DEVICE_NAME                           1
#define BLEP_PIPE_HARDWARE_REVISION                     2
#define BLEP_PIPE_UART_RX                               3
#define BLEP_PIPE_UART_TX                               4
#define BLEP_DEVICE_NAME_SIZE                           20

/**
 * @brief BLE P advertising and disconnection settings.
 * @details The advertising interval is 100 ms in 0.625 ms units; timeout zero advertises indefinitely.
 */
#define BLEP_ADV_INTERVAL                               160
#define BLEP_ADV_NO_TIMEOUT                             0
#define BLEP_DISCONNECT_TERMINATE                       0x01

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b blep_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define BLEP_SET_DATA_SAMPLE_EDGE                       SET_SPI_DATA_SAMPLE_EDGE
#define BLEP_SET_DATA_SAMPLE_MIDDLE                     SET_SPI_DATA_SAMPLE_MIDDLE


/*! @} */ // blep_set

/**
 * @defgroup blep_map BLE P MikroBUS Map
 * @brief MikroBUS pin mapping of BLE P Click driver.
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BLE P Click to the selected MikroBUS.
 */
#define BLEP_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.act  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rdy  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // blep_map
/*! @} */ // blep

/**
 * @brief BLE P event object.
 * @details Stores an ACI event without the SPI status or length prefix.
 */
typedef struct
{
    uint8_t len;                                /**< Opcode and parameter length. */
    uint8_t opcode;                             /**< Event opcode. */
    uint8_t payload[ BLEP_PACKET_SIZE - 1 ];    /**< Event parameters. */

} blep_event_t;

/**
 * @brief BLE P Click context object.
 * @details Holds the peripherals, pending ACI events, link state, and transmit credits.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Active-low reset. */

    // Input pins
    digital_in_t act;                           /**< Radio activity indication. */
    digital_in_t rdy;                           /**< Active-low ACI ready indication. */

    // Modules
    spi_master_t spi;                           /**< SPI driver object. */
    pin_name_t chip_select;                     /**< Active-low REQN pin. */

    blep_event_t events[ BLEP_EVENT_QUEUE_SIZE ];   /**< Events received while writing commands. */
    uint8_t event_head;                         /**< Next queued event to read. */
    uint8_t event_count;                        /**< Number of queued events. */
    uint8_t device_mode;                        /**< Last reported operating mode. */
    uint8_t connected;                          /**< Connection state updated by read_event. */
    uint8_t credits;                            /**< Available notification credits. */
    uint8_t total_credits;                      /**< Credits reported at startup. */
    uint8_t open_pipes[ 8 ];                    /**< Open pipe bitmap updated by read_event. */

} blep_t;

/**
 * @brief BLE P Click configuration object.
 * @details Configuration object definition of BLE P Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                            /**< Master input - slave output pin descriptor. */
    pin_name_t mosi;                            /**< Master output - slave input pin descriptor. */
    pin_name_t sck;                             /**< Clock pin descriptor. */
    pin_name_t cs;                              /**< REQN pin descriptor. */

    // Additional gpio pins
    pin_name_t act;                             /**< Radio activity pin descriptor. */
    pin_name_t rst;                             /**< Reset pin descriptor. */
    pin_name_t rdy;                             /**< ACI ready pin descriptor. */

    // Communication settings
    uint32_t spi_speed;                         /**< SPI serial speed. */
    spi_master_mode_t spi_mode;                 /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} blep_cfg_t;

/**
 * @brief BLE P Click return values.
 * @details Separates idle polling and flow control from communication failures.
 */
typedef enum
{
    BLEP_OK = 0,
    BLEP_NO_EVENT = 1,
    BLEP_BUSY = 2,
    BLEP_ERROR = -1,
    BLEP_ERROR_TIMEOUT = -2,
    BLEP_ERROR_RESPONSE = -3

} blep_return_value_t;

/*!
 * @addtogroup blep BLE P Click Driver
 * @brief API for configuring and manipulating BLE P Click driver.
 * @{
 */

/**
 * @brief BLE P configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #blep_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void blep_cfg_setup ( blep_cfg_t *cfg );

/**
 * @brief BLE P initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #blep_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t blep_init ( blep_t *ctx, blep_cfg_t *cfg );

/**
 * @brief BLE P reset function.
 * @details This function pulses the BLE P Click reset pin and clears queued events and credits.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @return None.
 * @note The startup delay is 100 ms. The UART profile must be loaded again after reset.
 */
void blep_reset ( blep_t *ctx );

/**
 * @brief BLE P command writing function.
 * @details This function sends an ACI opcode and binary parameters to BLE P Click.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[in] command : ACI command opcode.
 * @param[in] param_in : Parameter buffer, or NULL when len is zero.
 * @param[in] len : Parameter length, from 0 to 30 bytes.
 * @return BLEP_OK, BLEP_BUSY when the event queue is full, or a negative error.
 * @note System commands are asynchronous; consume their CommandResponse before sending the next system command.
 */
err_t blep_write_command ( blep_t *ctx, uint8_t command, uint8_t *param_in, uint8_t len );

/**
 * @brief BLE P command execution function.
 * @details This function sends a parameterless ACI command to BLE P Click.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[in] command : ACI command opcode.
 * @return BLEP_OK, BLEP_BUSY, or a negative error.
 * @note Read the resulting event with blep_read_event.
 */
err_t blep_run_command ( blep_t *ctx, uint8_t command );

/**
 * @brief BLE P event reading function.
 * @details This function reads one queued or pending BLE P Click event and updates link and credit state.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[out] evt : Received event; len is zero when no event is available.
 * See #blep_event_t object definition for detailed explanation.
 * @return BLEP_OK for an event, BLEP_NO_EVENT when idle, or a negative error.
 * @note Poll regularly. Events received during command writes are preserved in the context queue.
 */
err_t blep_read_event ( blep_t *ctx, blep_event_t *evt );

/**
 * @brief BLE P UART profile configuration function.
 * @details This function loads the BLE P Click Nordic UART profile and waits for standby mode.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @return BLEP_OK, or a negative transport, timeout, or setup response error.
 * @note Call only in setup mode. Uses Nordic ble_modify_setup_data/services.h, generated by nRFgo Studio 1.17.1.3252.
 */
err_t blep_uart_cfg ( blep_t *ctx );

/**
 * @brief BLE P local data setting function.
 * @details This function writes a local BLE P Click characteristic value through its SET pipe.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[in] pipe : Profile pipe number.
 * @param[in] data_in : Characteristic value.
 * @param[in] len : Value length, from 0 to 20 bytes.
 * @return BLEP_OK, BLEP_BUSY, or a negative error.
 * @note Wait for the SetLocalData CommandResponse before issuing another system command.
 */
err_t blep_set_local_data ( blep_t *ctx, uint8_t pipe, uint8_t *data_in, uint8_t len );

/**
 * @brief BLE P advertising function.
 * @details This function starts BLE P Click connectable advertising.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[in] timeout : Advertising timeout in seconds, 0 for unlimited, otherwise up to 16383.
 * @param[in] interval : Advertising interval in 0.625 ms units, from 32 to 16384.
 * @return BLEP_OK, BLEP_BUSY, or a negative error.
 * @note Read the Connect CommandResponse, then wait for Connected and PipeStatus events.
 */
err_t blep_start_advertising ( blep_t *ctx, uint16_t timeout, uint16_t interval );

/**
 * @brief BLE P disconnection function.
 * @details This function requests termination of the BLE P Click connection.
 * @param[in,out] ctx : Click context object.
 * @return BLEP_OK, BLEP_BUSY, or a negative error.
 * @note Wait for the Disconnected event before restarting advertising.
 */
err_t blep_disconnect ( blep_t *ctx );

/**
 * @brief BLE P data sending function.
 * @details This function sends one BLE P Click notification using one available transmit credit.
 * @param[in,out] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[in] pipe : Open TX pipe number.
 * @param[in] data_in : Notification payload.
 * @param[in] len : Payload length, from 1 to 20 bytes.
 * @return BLEP_OK, BLEP_BUSY when no credit or queue space is available, or a negative error.
 * @note Split longer messages into multiple calls. Read events to return credits and detect pipe errors.
 */
err_t blep_send_data ( blep_t *ctx, uint8_t pipe, uint8_t *data_in, uint8_t len );

/**
 * @brief BLE P pipe state reading function.
 * @details This function checks the BLE P Click open pipe bitmap.
 * @param[in] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @param[in] pipe : Pipe number, from 1 to 62.
 * @return One for an open pipe, otherwise zero.
 * @note The bitmap is refreshed by blep_read_event.
 */
uint8_t blep_is_pipe_open ( blep_t *ctx, uint8_t pipe );

/**
 * @brief BLE P ready pin reading function.
 * @details This function reads the BLE P Click RDYN pin.
 * @param[in] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @return Zero when ready, one when inactive.
 * @note None.
 */
uint8_t blep_get_ready ( blep_t *ctx );

/**
 * @brief BLE P activity pin reading function.
 * @details This function reads the BLE P Click ACTIVE pin.
 * @param[in] ctx : Click context object.
 * See #blep_t object definition for detailed explanation.
 * @return Digital pin state.
 * @note Signal behavior is defined by the loaded setup profile.
 */
uint8_t blep_get_activity ( blep_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BLEP_H

/*! @} */ // blep

// ------------------------------------------------------------------------ END
