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
 * @file thyonei.h
 * @brief This file contains API for Thyone-I Click Driver.
 */

#ifndef THYONEI_H
#define THYONEI_H

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
 * @addtogroup thyonei Thyone-I Click Driver
 * @brief API for configuring and manipulating Thyone-I Click driver.
 * @{
 */

/**
 * @defgroup thyonei_cmd Thyone-I Device Settings
 * @brief Settings for registers of Thyone-I Click driver.
 */

/**
 * @addtogroup thyonei_cmd
 * @{
 */

/**
 * @brief Thyone-I control commands.
 * @details Specified setting for control commands of Thyone-I Click driver.
 */
#define THYONEI_CMD_BROADCAST_DATA_REQ          0x06
#define THYONEI_CMD_MULTICAST_DATA_REQ          0x05
#define THYONEI_CMD_UNICAST_DATA_REQ            0x04
#define THYONEI_CMD_MULTICAST_DATA_EX_REQ       0x08
#define THYONEI_CMD_UNICAST_DATA_EX_REQ         0x07
#define THYONEI_CMD_DATA_CNF                    0x44
#define THYONEI_CMD_TXCOMPLETE_RSP              0xC4
#define THYONEI_CMD_DATA_IND                    0x84
#define THYONEI_CMD_SNIFFER_IND                 0x99
#define THYONEI_CMD_SET_REQ                     0x11
#define THYONEI_CMD_GET_REQ                     0x10
#define THYONEI_CMD_START_IND                   0x73
#define THYONEI_CMD_GETSTATE_REQ                0x01
#define THYONEI_CMD_RESET_REQ                   0x00
#define THYONEI_CMD_SLEEP_REQ                   0x02
#define THYONEI_CMD_FACTORY_RESET_REQ           0x1C
#define THYONEI_CMD_BOOTLOADER_REQ              0x1F
#define THYONEI_CMD_TRANSPARENT_MODE_REQ        0x1B
#define THYONEI_CMD_SETCHANNEL_REQ              0x19
#define THYONEI_CMD_GPIO_LOCAL_SET_CONFIG_REQ   0x25
#define THYONEI_CMD_GPIO_LOCAL_GET_CONFIG_REQ   0x26
#define THYONEI_CMD_GPIO_REMOTE_SET_CONFIG_REQ  0x29
#define THYONEI_CMD_GPIO_REMOTE_GET_CONFIG_REQ  0x2A
#define THYONEI_CMD_GPIO_LOCAL_WRITE_REQ        0x27
#define THYONEI_CMD_GPIO_LOCAL_READ_REQ         0x28
#define THYONEI_CMD_GPIO_REMOTE_WRITE_REQ       0x2B
#define THYONEI_CMD_GPIO_REMOTE_READ_REQ        0x2C
#define THYONEI_CMD_GPIO_REMOTE_SET_CONFIG_IND  0xA9
#define THYONEI_CMD_GPIO_REMOTE_WRITE_IND       0xAB
#define THYONEI_CMD_ERROR_IND                   0xA2
#define THYONEI_CMD_DTM_START_REQ               0x1D
#define THYONEI_CMD_DTM_REQ                     0x1E

/**
 * @brief Thyone-I settings indexes.
 * @details Specified settings indexes of Thyone-I Click driver.
 */
#define THYONEI_INDEX_SERIAL_NUMBER             0x01
#define THYONEI_INDEX_FW_VERSION                0x02
#define THYONEI_INDEX_UART_CONFIG               0x04
#define THYONEI_INDEX_UART_MODE                 0x05
#define THYONEI_INDEX_UART_TRANSPARENT_TIMEOUT  0x06
#define THYONEI_INDEX_RF_CHANNEL                0x07
#define THYONEI_INDEX_ENCRYPTION_MODE           0x08
#define THYONEI_INDEX_RF_PROFILE                0x09
#define THYONEI_INDEX_RF_NUM_RETRIES            0x0A
#define THYONEI_INDEX_RF_TX_POWER               0x0B
#define THYONEI_INDEX_RF_RP_NUM_SLOTS           0x0C
#define THYONEI_INDEX_MAC_SOURCE_ADDRESS        0x10 
#define THYONEI_INDEX_MAC_DEST_ADDRESS          0x11 
#define THYONEI_INDEX_MAC_GROUP_ID              0x12 
#define THYONEI_INDEX_MAC_TRANSPARENT_ADDR_MODE 0x13 
#define THYONEI_INDEX_MAC_ENCRYPTION_KEY        0x14 
#define THYONEI_INDEX_MAC_TTL                   0x15 
#define THYONEI_INDEX_CCA_MODE                  0x16 
#define THYONEI_INDEX_CCA_THRESHOLD             0x17 
#define THYONEI_INDEX_GPIO_BLOCK_REMOTE         0x18 
#define THYONEI_INDEX_UART_TRANSP_ETX_CONFIG    0x19 
#define THYONEI_INDEX_UART_TRANSP_ETX           0x1A 
#define THYONEI_INDEX_UART_TRANSP_ETC_ENABLE    0x1B 
#define THYONEI_INDEX_UART_TRANSP_ETC           0x1C 
#define THYONEI_INDEX_RF_REPRATER_THRESHOLD     0x1D 
#define THYONEI_INDEX_MODULE_MODE               0x20 

/**
 * @brief Thyone-I Command structure settings.
 * @details Specified setting for Command structure of Thyone-I Click driver.
 */
#define THYONEI_RESPONSE_CODE                   0x40
#define THYONEI_START_SIGNAL                    0x02

/**
 * @brief Thyone-I pin mode settings.
 * @details Specified setting for pin mode of Thyone-I Click driver.
 */
#define THYONE_PIN_MODE_HIGH                    0x01    
#define THYONE_PIN_MODE_LOW                     0x00    

/**
 * @brief Thyone-I driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define THYONEI_TX_DRV_BUFFER_SIZE              300
#define THYONEI_RX_DRV_BUFFER_SIZE              300

/*! @} */ // thyonei_cmd

/**
 * @defgroup thyonei_map Thyone-I MikroBUS Map
 * @brief MikroBUS pin mapping of Thyone-I Click driver.
 */

/**
 * @addtogroup thyonei_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thyone-I Click to the selected MikroBUS.
 */
#define THYONEI_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.bt  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // thyonei_map
/*! @} */ // thyonei

/**
 * @brief Thyone-I Click context object.
 * @details Context object definition of Thyone-I Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t bt;                   /**< Boot pin. */
    digital_out_t rst;                  /**< Reset pin. */
    digital_out_t rts;                  /**< Ready to send pin. */
    digital_out_t wup;                  /**< Wake-up pin. */

    // Input pins
    digital_in_t cts;                   /**< Clear to send pin. */

    // Modules
    uart_t uart;                        /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ THYONEI_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ THYONEI_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} thyonei_t;

/**
 * @brief Thyone-I Click configuration object.
 * @details Configuration object definition of Thyone-I Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t bt;                      /**< Boot pin. */
    pin_name_t rst;                     /**< Reset pin. */
    pin_name_t rts;                     /**< Ready to send pin. */
    pin_name_t wup;                     /**< Wake-up pin. */
    pin_name_t cts;                     /**< Clear to send pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} thyonei_cfg_t;

/**
 * @brief Thyone-I Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THYONEI_OK = 0,
    THYONEI_ERROR = -1

} thyonei_return_value_t;

/*!
 * @addtogroup thyonei Thyone-I Click Driver
 * @brief API for configuring and manipulating Thyone-I Click driver.
 * @{
 */

/**
 * @brief Thyone-I configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thyonei_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thyonei_cfg_setup ( thyonei_cfg_t *cfg );

/**
 * @brief Thyone-I initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thyonei_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thyonei_init ( thyonei_t *ctx, thyonei_cfg_t *cfg );

/**
 * @brief Thyone-I default configuration function.
 * @details This function executes a default configuration of Thyone-I
 * click board.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void thyonei_default_cfg ( thyonei_t *ctx );

/**
 * @brief Thyone-I data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c >=0 - Success,
 *         @li @c  <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thyonei_generic_write ( thyonei_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Thyone-I data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thyonei_generic_read ( thyonei_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief  Thyone-I get CTS pin function.
 * @details This function returns the CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thyonei_get_cts_state ( thyonei_t *ctx );

/**
 * @brief Thyone-I set BT pin function.
 * @details This function sets the BT pin logic state.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void thyonei_set_bt ( thyonei_t *ctx, uint8_t pin_state );

/**
 * @brief Thyone-I set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void thyonei_set_rst ( thyonei_t *ctx, uint8_t pin_state );

/**
 * @brief Thyone-I set RTS pin function.
 * @details This function sets the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void thyonei_set_rts ( thyonei_t *ctx, uint8_t pin_state );

/**
 * @brief Thyone-I set WUP pin function.
 * @details This function sets the WUP pin logic state.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void thyonei_set_wup ( thyonei_t *ctx, uint8_t pin_state );

/**
 * @brief Thyone-I hardware reser function.
 * @details This function is used to perform hardware reset of Thyone-I
 * click board.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void thyonei_hw_reset ( thyonei_t *ctx );

/**
 * @brief Thyone-I send command function.
 * @details This function is used to send selected command and their payload to Thyone-I
 * click board.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] command : Command to be sent.
 * @param[in] payload_length : Length of data to be sent.
 * @param[in] payload : Data to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thyonei_send_command ( thyonei_t *ctx, uint8_t command, uint16_t payload_length, uint8_t *payload );

/**
 * @brief Thyone-I set individual parameters function.
 * @details This command can be used to set individual setting parameters in flash of Thyone-I
 * click board.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] settings_index : Index of the selected parameter.
 * @param[in] parameters_length : Length of data to be sent.
 * @param[in] parameters : Data to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thyonei_set_req ( thyonei_t *ctx, uint8_t settings_index, uint8_t parameters_length, uint8_t *parameters );

/**
 * @brief Thyone-I get individual parameters function.
 * @details This command can be used to query individual setting parameters stored in flash of Thyone-I
 * click board.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] settings_index : Index of the selected parameter.
 * @param[out] param_len : Length of read data.
 * @param[out] parameter : Read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thyonei_get_req ( thyonei_t *ctx, uint8_t settings_index, uint8_t *param_len, uint8_t *parameter );

/**
 * @brief Thyone-I brodcast data function.
 * @details This command provides the simple broadcast data transmission of Thyone-I
 * click board.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] settings_index : Index of the selected parameter.
 * @param[in] message_len : Data to be sent. ( Maximum of 224 bytes can be transmitted per packet )
 * @param[in] message : Data to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thyonei_broadcast_data_req ( thyonei_t *ctx, uint8_t message_len, uint8_t *message );

/**
 * @brief Thyone-I multicast data function.
 * @details This command provides the multicast data transmission to a group of modules 
 * configured with the same MAC GROUP ADDRESS of Thyone-I click board.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] settings_index : Index of the selected parameter.
 * @param[in] message_len : Data to be sent. ( Maximum of 223 bytes can be transmitted per packet )
 * @param[in] message : Data to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thyonei_multicast_data_req ( thyonei_t *ctx, uint8_t message_len, uint8_t *message );

/**
 * @brief Thyone-I unicast data function.
 * @details This command provides the unicast data transmission to the configured
 *  MAC DESTINATION ADDRESS of Thyone-I click board.
 * @param[in] ctx : Click context object.
 * See #thyonei_t object definition for detailed explanation.
 * @param[in] settings_index : Index of the selected parameter.
 * @param[in] message_len : Data to be sent. ( Maximum of 220 bytes can be transmitted per packet )
 * @param[in] message : Data to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thyonei_unicast_data_req ( thyonei_t *ctx, uint8_t message_len, uint8_t *message );

#ifdef __cplusplus
}
#endif
#endif // THYONEI_H

/*! @} */ // thyonei

// ------------------------------------------------------------------------ END
