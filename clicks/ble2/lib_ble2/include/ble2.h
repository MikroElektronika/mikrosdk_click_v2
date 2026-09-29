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
 * @file ble2.h
 * @brief This file contains API for BLE2 Click Driver.
 */

#ifndef BLE2_H
#define BLE2_H

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
 * @addtogroup ble2 BLE2 Click Driver
 * @brief API for configuring and manipulating BLE2 Click driver.
 * @{
 */

/**
 * @defgroup ble2_cmd BLE2 Device Settings
 * @brief Settings of BLE2 Click driver.
 */

/**
 * @addtogroup ble2_cmd
 * @{
 */

/**
 * @brief BLE2 set/get command identifiers.
 * @details Use these identifiers with #ble2_cmd_set and #ble2_cmd_get.
 */
#define BLE2_CMD_SERIALIZED_NAME                    "-"
#define BLE2_CMD_UART_BAUD_RATE                     "B"
#define BLE2_CMD_DEVICE_FIRMWARE_REVISION           "DF"
#define BLE2_CMD_DEVICE_HARDWARE_REVISION           "DH"
#define BLE2_CMD_DEVICE_MODEL_NAME                  "DM"
#define BLE2_CMD_DEVICE_MANUFACTURER_NAME           "DN"
#define BLE2_CMD_DEVICE_SOFTWARE_REVISION           "DR"
#define BLE2_CMD_DEVICE_SERIAL_NUMBER               "DS"
#define BLE2_CMD_FACTORY_DEFAULT                    "F"
#define BLE2_CMD_TIMERS                             "M"
#define BLE2_CMD_DEVICE_NAME                        "N"
#define BLE2_CMD_TX_POWER                           "P"
#define BLE2_CMD_SUPPORTED_FEATURES                 "R"
#define BLE2_CMD_SUPPORTED_SERVICES                 "S"
#define BLE2_CMD_CONNECTION_PARAMETERS              "T"
#define BLE2_CMD_MLDP_SECURITY                      "E"

/**
 * @brief BLE2 action commands.
 * @details ASCII action commands supported by BLE2 Click.
 */
#define BLE2_CMD_TOGGLE_ECHO                        "+"
#define BLE2_CMD_WRITE_ANALOG                       "@O"
#define BLE2_CMD_READ_ANALOG                        "@I"
#define BLE2_CMD_WRITE_DIGITAL                      "|O"
#define BLE2_CMD_READ_DIGITAL                       "|I"
#define BLE2_CMD_START_ADVERTISING                  "A"
#define BLE2_CMD_BOND                               "B"
#define BLE2_CMD_DISPLAY_CRITICAL_INFO              "D"
#define BLE2_CMD_CONNECT                            "E"
#define BLE2_CMD_START_SCAN                         "F"
#define BLE2_CMD_HELP                               "H"
#define BLE2_CMD_SET_OBSERVER_ROLE                  "J"
#define BLE2_CMD_DISCONNECT                         "K"
#define BLE2_CMD_GET_RSSI                           "M"
#define BLE2_CMD_ENTER_BROADCASTER                  "N"
#define BLE2_CMD_ENTER_DORMANT                      "O"
#define BLE2_CMD_GET_CONNECTION_STATUS              "Q"
#define BLE2_CMD_REBOOT                             "R"
#define BLE2_CMD_CHANGE_CONNECTION_PARAMETERS       "T"
#define BLE2_CMD_UNBOND                             "U"
#define BLE2_CMD_GET_FIRMWARE_VERSION               "V"
#define BLE2_CMD_STOP_SCAN                          "X"
#define BLE2_CMD_STOP_ADVERTISING                   "Y"
#define BLE2_CMD_STOP_CONNECTING                    "Z"

/**
 * @brief BLE2 I2C and PWM commands.
 * @details I2C and PWM interface commands supported by BLE2 Click.
 */
#define BLE2_CMD_I2C_ENABLE                         "]A"
#define BLE2_CMD_I2C_DISABLE                        "]Z"
#define BLE2_CMD_I2C_EEPROM_READ                    "]ER"
#define BLE2_CMD_I2C_EEPROM_WRITE                   "]EW"
#define BLE2_CMD_I2C_EVENT                          "]C"
#define BLE2_CMD_I2C_READ                           "]R"
#define BLE2_CMD_I2C_WRITE                          "]W"
#define BLE2_CMD_PWM_START                          "["

/**
 * @brief BLE2 characteristic access commands.
 * @details GATT characteristic access commands supported by BLE2 Click.
 */
#define BLE2_CMD_LIST_CLIENT_SERVICES               "LC"
#define BLE2_CMD_LIST_SERVER_SERVICES               "LS"
#define BLE2_CMD_READ_CLIENT_HANDLE                 "CHR"
#define BLE2_CMD_WRITE_CLIENT_HANDLE                "CHW"
#define BLE2_CMD_READ_CLIENT_UUID_CONFIG            "CURC"
#define BLE2_CMD_READ_CLIENT_UUID_VALUE             "CURV"
#define BLE2_CMD_WRITE_CLIENT_UUID_CONFIG           "CUWC"
#define BLE2_CMD_WRITE_CLIENT_UUID_VALUE            "CUWV"
#define BLE2_CMD_READ_SERVER_HANDLE                 "SHR"
#define BLE2_CMD_WRITE_SERVER_HANDLE                "SHW"
#define BLE2_CMD_READ_SERVER_UUID                   "SUR"
#define BLE2_CMD_WRITE_SERVER_UUID                  "SUW"

/**
 * @brief BLE2 private service and MLDP commands.
 * @details Private GATT service and Microchip Low-energy Data Profile commands.
 */
#define BLE2_CMD_SET_PRIVATE_CHARACTERISTIC         "PC"
#define BLE2_CMD_SET_PRIVATE_SERVICE_FILTER         "PF"
#define BLE2_CMD_SET_PRIVATE_SERVICE                "PS"
#define BLE2_CMD_CLEAR_PRIVATE_SERVICE              "PZ"
#define BLE2_CMD_ENTER_MLDP                         "I"

/**
 * @brief BLE2 scripting, remote, and firmware commands.
 * @details Scripting, remote command, and device firmware update commands.
 */
#define BLE2_CMD_SHOW_SCRIPT                        "LW"
#define BLE2_CMD_CLEAR_SCRIPT                       "WC"
#define BLE2_CMD_PAUSE_SCRIPT                       "WP"
#define BLE2_CMD_RUN_SCRIPT                         "WR"
#define BLE2_CMD_WRITE_SCRIPT                       "WW"
#define BLE2_CMD_REMOTE                             "!"
#define BLE2_CMD_DEVICE_FIRMWARE_UPDATE             "~"

/**
 * @brief BLE2 command parameters.
 * @details Parameters used to configure the BT terminal example.
 */
#define BLE2_FACTORY_RESET                          "1"
#define BLE2_FEATURE_MLDP                           "10000000"
#define BLE2_REBOOT                                 "1"

/**
 * @brief BLE2 command responses.
 * @details Common command responses returned by BLE2 Click.
 */
#define BLE2_RSP_COMMAND_MODE                       "CMD"
#define BLE2_RSP_MLDP_MODE                          "MLDP"
#define BLE2_RSP_FIRMWARE_VERSION                   "MCHP BTLE"
#define BLE2_RSP_SERVER_SERVICE                     "Server Service="
#define BLE2_RSP_OK                                 "AOK"
#define BLE2_RSP_ERROR                              "ERR"
#define BLE2_RSP_CONNECTED                          "Connected"
#define BLE2_RSP_DISCONNECTED                       "Connection End"
#define BLE2_RSP_END                                "END"

/**
 * @brief BLE2 control pin settings.
 * @details Logic states used to control and monitor BLE2 Click.
 */
#define BLE2_WAKE_SLEEP                             0
#define BLE2_WAKE_ACTIVE                            1
#define BLE2_MODE_COMMAND                           0
#define BLE2_MODE_MLDP                              1
#define BLE2_CONNECTION_DISCONNECTED                0
#define BLE2_CONNECTION_CONNECTED                   1
#define BLE2_CMD_PREFIX_SET                         'S'
#define BLE2_CMD_PREFIX_GET                         'G'
#define BLE2_CMD_SEPARATOR                          ','
#define BLE2_CMD_TERMINATOR                         '\r'

/**
 * @brief BLE2 UART settings.
 * @details Default UART communication settings for BLE2 Click.
 */
#define BLE2_UART_BAUD_RATE                         115200

/**
 * @brief BLE2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BLE2_TX_DRV_BUFFER_SIZE                     100
#define BLE2_RX_DRV_BUFFER_SIZE                     300
#define BLE2_CMD_BUFFER_SIZE                        100

/*! @} */ // ble2_cmd

/**
 * @defgroup ble2_map BLE2 MikroBUS Map
 * @brief MikroBUS pin mapping of BLE2 Click driver.
 */

/**
 * @addtogroup ble2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BLE2 Click to the selected MikroBUS.
 */
#define BLE2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.con = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.wake_sw = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cmd = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // ble2_map
/*! @} */ // ble2

/**
 * @brief BLE2 Click context object.
 * @details Context object definition of BLE2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wake_sw;                  /**< Software wake pin (active high). */
    digital_out_t cmd;                      /**< Command/MLDP mode selection pin. */

    // Input pins
    digital_in_t con;                       /**< Connection status pin (active high). */

    // Modules
    uart_t uart;                            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BLE2_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ BLE2_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ BLE2_CMD_BUFFER_SIZE ];         /**< Command buffer. */

} ble2_t;

/**
 * @brief BLE2 Click configuration object.
 * @details Configuration object definition of BLE2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                      /**< RX pin. */
    pin_name_t tx_pin;                      /**< TX pin. */

    // Additional gpio pins
    pin_name_t con;                         /**< Connection status pin. */
    pin_name_t wake_sw;                     /**< Software wake pin. */
    pin_name_t cmd;                         /**< Command/MLDP mode selection pin. */

    // Static variable
    uint32_t         baud_rate;             /**< Clock speed. */
    bool             uart_blocking;         /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;              /**< Data bits. */
    uart_parity_t    parity_bit;            /**< Parity bit. */
    uart_stop_bits_t stop_bit;              /**< Stop bits. */

} ble2_cfg_t;

/**
 * @brief BLE2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BLE2_OK = 0,
    BLE2_ERROR = -1,
    BLE2_ERROR_TIMEOUT = -2,
    BLE2_ERROR_CMD = -3

} ble2_return_value_t;

/*!
 * @addtogroup ble2 BLE2 Click Driver
 * @brief API for configuring and manipulating BLE2 Click driver.
 * @{
 */

/**
 * @brief BLE2 configuration object setup function.
 * @details This function initializes the Click configuration structure to its
 * default values.
 * @param[out] cfg : Click configuration structure.
 * See #ble2_cfg_t object definition for detailed explanation.
 * @return None.
 * @note All used pins will be set to the unconnected state.
 */
void ble2_cfg_setup ( ble2_cfg_t *cfg );

/**
 * @brief BLE2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ble2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble2_init ( ble2_t *ctx, ble2_cfg_t *cfg );

/**
 * @brief BLE2 default configuration function.
 * @details This function places BLE2 Click in Command mode and wakes the module.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function does not modify the stored module configuration.
 */
err_t ble2_default_cfg ( ble2_t *ctx );

/**
 * @brief BLE2 data writing function.
 * @details This function writes a desired number of data bytes using the UART
 * serial interface.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble2_generic_write ( ble2_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief BLE2 data reading function.
 * @details This function reads a desired number of data bytes using the UART
 * serial interface.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ble2_generic_read ( ble2_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief BLE2 set wake pin function.
 * @details This function sets the WAKE_SW pin logic state.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note Set the pin high to wake the module and low to enter Deep Sleep mode.
 */
void ble2_set_wake_pin ( ble2_t *ctx, uint8_t state );

/**
 * @brief BLE2 set mode pin function.
 * @details This function sets the CMD/MLDP pin logic state.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note Set the pin low for Command mode and high for MLDP mode.
 */
void ble2_set_mode_pin ( ble2_t *ctx, uint8_t state );

/**
 * @brief BLE2 get connection pin function.
 * @details This function reads the CON connection status pin logic state.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @return @li @c  0 - Disconnected,
 *         @li @c  1 - Connected.
 * @note The connection status signal is active high.
 */
uint8_t ble2_get_connection_pin ( ble2_t *ctx );

/**
 * @brief BLE2 command run function.
 * @details This function sends an ASCII command followed by a carriage return.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The command must not contain a line terminator.
 */
err_t ble2_cmd_run ( ble2_t *ctx, uint8_t *cmd );

/**
 * @brief BLE2 command set function.
 * @details This function builds and sends a BLE2 Click set command.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @param[in] cmd : Set/get command identifier, see BLE2_CMD_x definitions.
 * @param[in] value : Command parameter string.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The command and value must fit in #BLE2_CMD_BUFFER_SIZE.
 */
err_t ble2_cmd_set ( ble2_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief BLE2 command get function.
 * @details This function builds and sends a BLE2 Click get command.
 * @param[in] ctx : Click context object.
 * See #ble2_t object definition for detailed explanation.
 * @param[in] cmd : Set/get command identifier, see BLE2_CMD_x definitions.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The command must fit in #BLE2_CMD_BUFFER_SIZE.
 */
err_t ble2_cmd_get ( ble2_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // BLE2_H

/*! @} */ // ble2

// ------------------------------------------------------------------------ END
