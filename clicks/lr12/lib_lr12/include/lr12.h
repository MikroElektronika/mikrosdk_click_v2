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
 * @file lr12.h
 * @brief This file contains API for LR 12 Click Driver.
 */

#ifndef LR12_H
#define LR12_H

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
 * @addtogroup lr12 LR 12 Click Driver
 * @brief API for configuring and manipulating LR 12 Click driver.
 * @{
 */

/**
 * @defgroup lr12_cmd LR 12 Device Settings
 * @brief Settings of LR 12 Click driver.
 */

/**
 * @addtogroup lr12_cmd
 * @{
 */

/**
 * @brief LR 12 control commands.
 * @details Specified setting for control commands of LR 12 Click driver.
 */
#define LR12_CMD_AT                                 "AT"
#define LR12_CMD_UART                               "AT+UART"
#define LR12_CMD_GET_FW_VERSION                     "AT+VER"
#define LR12_CMD_DEBUG                              "AT+DBG"
#define LR12_CMD_HW_TYPE                            "AT+DEV"
#define LR12_CMD_REBOOT                             "AT+REBOOT"
#define LR12_CMD_FACTORY_RESET                      "AT+FACNEW"
#define LR12_CMD_BAND                               "AT+BAND"
#define LR12_CMD_CLASS                              "AT+CLASS"
#define LR12_CMD_JOIN_MODE                          "AT+JOINMODE"
#define LR12_CMD_NETWORK_TYPE                       "AT+NWK"
#define LR12_CMD_DEVICE_ADDRESS                     "AT+DEVADDR"
#define LR12_CMD_DEVICE_EUI                         "AT+DEVEUI"
#define LR12_CMD_APPLICATION_EUI                    "AT+APPEUI"
#define LR12_CMD_NETWORK_SESSION_KEY                "AT+NWKSKEY"
#define LR12_CMD_APPLICATION_SESSION_KEY            "AT+APPSKEY"
#define LR12_CMD_APPLICATION_KEY                    "AT+APPKEY"
#define LR12_CMD_JOIN                               "AT+JOIN"
#define LR12_CMD_JOIN_STATUS                        "AT+JOINSTATUS"
#define LR12_CMD_RF_PARAM                           "AT+RFPARAM"
#define LR12_CMD_CHANNEL_MASK                       "AT+CHMASK"
#define LR12_CMD_ANTENNA_GAIN                       "AT+ANT"
#define LR12_CMD_MAX_EIRP                           "AT+MAXEIRP"
#define LR12_CMD_RF_POWER                           "AT+RFPOWER"
#define LR12_CMD_ADAPTIVE_DATA_RATE                 "AT+ADR"
#define LR12_CMD_ADAPTIVE_DATA_RATE_ACK             "AT+ADRACK"
#define LR12_CMD_DATA_RATE                          "AT+DR"
#define LR12_CMD_DELAY                              "AT+DELAY"
#define LR12_CMD_RX_2_PARAMS                        "AT+RX2"
#define LR12_CMD_PORT_NUMBER                        "AT+PORT"
#define LR12_CMD_DATA_FORMAT                        "AT+DFORMAT"
#define LR12_CMD_UNCONFIRMED_SEND                   "AT+UTX"
#define LR12_CMD_CONFIRMED_SEND                     "AT+CTX"
#define LR12_CMD_UNCONFIRMED_PORT_SEND              "AT+PUTX"
#define LR12_CMD_CONFIRMED_PORT_SEND                "AT+PCTX"
#define LR12_CMD_MAX_PAYLOAD_LEN                    "AT+MSIZE"
#define LR12_CMD_UNCONFIRMED_SEND_REPEAT_NUM        "AT+UTXREP"
#define LR12_CMD_CONFIRMED_SEND_RETRY_NUM           "AT+CTXRTY"
#define LR12_CMD_FRAME_COUNTER                      "AT+FRMCNT"
#define LR12_CMD_RF_SIGNAL                          "AT+RFQ"
#define LR12_CMD_NETWORK_STATUS                     "AT+LNCHECK"
#define LR12_CMD_DEVICE_TIME                        "AT+DEVTIME"
#define LR12_CMD_MULTICAST_GROUP                    "AT+MCAST"
#define LR12_CMD_JOIN_DUTY_CYCLE                    "AT+JOINDC"
#define LR12_CMD_DUTY_CYCLE                         "AT+DUTYCYCLE"
#define LR12_CMD_BACKOFF_TIME                       "AT+BACKOFF"
#define LR12_CMD_DWELL_TIME                         "AT+DWELL"
#define LR12_CMD_RSSI                               "AT+RSSITH"
#define LR12_CMD_CARRIER_SENSE_TIME                 "AT+CST"
#define LR12_CMD_AS_CHANNEL_PLAN                    "AT+ASPLAN"
#define LR12_CMD_POWER_SOURCE_TYPE                  "AT+PWRSRC"
#define LR12_CMD_BATTERY_LEVEL                      "AT+DEVBAT"
#define LR12_CMD_CERTIFICATION                      "AT+CERT"
#define LR12_CMD_RX_BOOST                           "AT+RXBOOST"
#define LR12_CMD_PING_SLOT_PERIOD                   "AT+PSPERIOD"
#define LR12_CMD_PING_SLOT_CHANNEL                  "AT+PSCHANNEL"
#define LR12_CMD_GPIO_INPUT                         "AT+GPIOI"
#define LR12_CMD_GPIO_OUTPUT                        "AT+GPIOO"
#define LR12_CMD_GPIO_INPUT_SETTING                 "AT+GPIOIT"
#define LR12_CMD_GPIO_OUTPUT_SETTING                "AT+GPIOOT"
#define LR12_CMD_HOST_KEEP_ALIVE                    "AT+HOSTKA"
#define LR12_CMD_TEST_CONTINUOUS_WAVE               "AT+TESTCW"
#define LR12_CMD_TEST_RX                            "AT+TESTRX"
#define LR12_CMD_STOP_TEST                          "AT+TESTSTOP"
#define LR12_CMD_ENTER_BOOTLOADER                   "AT+BL"
#define LR12_CMD_TRANSMIT_FW_BLOCK                  "AT+FWBLOCK"
#define LR12_CMD_START_FUOTA                        "AT+FUUL"

/**
 * @brief LR 12 device response for AT commands.
 * @details Device response after commands.
 */
#define LR12_RSP_OK                                 "+OK"
#define LR12_RSP_ERR                                "+ERR"

/**
 * @brief LR 12 device messages settings.
 * @details Device messages settings.
 */
#define LR12_MSG_RECEIVED_DATA                      "+RECV="
#define LR12_MSG_EVENT_REBOOT_SUCCESS               "+EVENT=0,0"
#define LR12_MSG_EVENT_RESTORE_FACTORY              "+EVENT=0,1"
#define LR12_MSG_EVENT_ENTER_BOOTLOADER             "+EVENT=0,2"
#define LR12_MSG_EVENT_JOIN_OK                      "+EVENT=1,1"
#define LR12_MSG_EVENT_JOIN_FAIL                    "+EVENT=1,0"
#define LR12_MSG_ACK                                "+ACK"
#define LR12_MSG_NOACK                              "+NOACK"
#define LR12_MSG_ANS                                "+ANS"

/**
 * @brief LR 12 device response time for AT commands.
 * @details Device response time after commands.
 */
#define LR12_MAX_RSP_TIME_DEFAULT                   300ul
#define LR12_MAX_RSP_TIME_RESET                     10000ul
#define LR12_MAX_RSP_TIME_FACTORY_RESET             30000ul
#define LR12_MAX_RSP_TIME_CONFIRMATION              60000ul
#define LR12_MAX_RSP_TIME_JOIN                      120000ul

/**
 * @brief LR 12 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LR12_TX_DRV_BUFFER_SIZE                     200
#define LR12_RX_DRV_BUFFER_SIZE                     600

/*! @} */ // lr12_cmd

/**
 * @defgroup lr12_map LR 12 MikroBUS Map
 * @brief MikroBUS pin mapping of LR 12 Click driver.
 */

/**
 * @addtogroup lr12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LR 12 Click to the selected MikroBUS.
 */
#define LR12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.boot = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // lr12_map
/*! @} */ // lr12

/**
 * @brief LR 12 Click context object.
 * @details Context object definition of LR 12 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t boot;             /**< Boot pin (active high). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LR12_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LR12_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LR12_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} lr12_t;

/**
 * @brief LR 12 Click configuration object.
 * @details Configuration object definition of LR 12 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t boot;                /**< Boot pin (active high). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} lr12_cfg_t;

/**
 * @brief LR 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LR12_OK = 0,
    LR12_ERROR = -1,
    LR12_ERROR_TIMEOUT = -2,
    LR12_ERROR_CMD = -3

} lr12_return_value_t;

/*!
 * @addtogroup lr12 LR 12 Click Driver
 * @brief API for configuring and manipulating LR 12 Click driver.
 * @{
 */

/**
 * @brief LR 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lr12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lr12_cfg_setup ( lr12_cfg_t *cfg );

/**
 * @brief LR 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lr12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr12_init ( lr12_t *ctx, lr12_cfg_t *cfg );

/**
 * @brief LR 12 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr12_generic_write ( lr12_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LR 12 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr12_generic_read ( lr12_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LR 12 set BOOT pin function.
 * @details This function sets the BOOT pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lr12_set_boot_pin ( lr12_t *ctx, uint8_t state );

/**
 * @brief LR 12 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lr12_set_rst_pin ( lr12_t *ctx, uint8_t state );

/**
 * @brief LR 12 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lr12_reset_device ( lr12_t *ctx );

/**
 * @brief LR 12 cmd run function.
 * @details This function sends a specified command with or without parameters to the Click module.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param : Parameters string (NULL - for executive commands that have no parameters).
 * @return None.
 * @note None.
 */
void lr12_cmd_run ( lr12_t *ctx, uint8_t *cmd, uint8_t *param );

/**
 * @brief LR 12 cmd set function.
 * @details This function sets data and parameters to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param : Command parameters string.
 * @param[in] value : Data value string (NULL - if CMD isn't UTX, CTX, PUTX or PCTX).
 * @return None.
 * @note None.
 */
void lr12_cmd_set ( lr12_t *ctx, uint8_t *cmd, uint8_t *param, uint8_t *value );

/**
 * @brief LR 12 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #lr12_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lr12_cmd_get ( lr12_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // LR12_H

/*! @} */ // lr12

// ------------------------------------------------------------------------ END
