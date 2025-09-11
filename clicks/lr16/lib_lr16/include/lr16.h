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
 * @file lr16.h
 * @brief This file contains API for LR 16 Click Driver.
 */

#ifndef LR16_H
#define LR16_H

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
 * @addtogroup lr16 LR 16 Click Driver
 * @brief API for configuring and manipulating LR 16 Click driver.
 * @{
 */

/**
 * @defgroup lr16_cmd LR 16 Device Settings
 * @brief Settings for registers of LR 16 Click driver.
 */

/**
 * @addtogroup lr16_cmd
 * @{
 */

/**
 * @brief LR 16 control commands.
 * @details Specified setting for control commands of LR 16 Click driver.
 */
#define LR16_CMD_AT                                 "AT"
#define LR16_CMD_RESET                              "ATZ"
#define LR16_CMD_GET_LOCAL_TIME                     "AT+LTIME"
#define LR16_CMD_GET_BATTERY_LEVEL                  "AT+BAT"
#define LR16_CMD_SLEEP                              "AT+SLEEP"
#define LR16_CMD_GET_SERIAL_NUMBER                  "AT+SN"
#define LR16_CMD_GET_FW_VERSION                     "AT+FWVER"
#define LR16_CMD_SET_OPERATING_MODE_USER            "AT+MODEUS"
#define LR16_CMD_SET_OPERATING_MODE_RUNTIME         "AT+MODERS"
#define LR16_CMD_FACTORY_RESET                      "AT+RUS"
#define LR16_CMD_STORE_FLASH_CONTEXT                "AT+CS"
#define LR16_CMD_ERASE_FLASH_CONTEXT                "AT+RFS"
#define LR16_CMD_APPLICATION_ID                     "AT+APPEUI"
#define LR16_CMD_APPLICATION_KEY                    "AT+APPKEY"
#define LR16_CMD_APPLICATION_SESSION_KEY            "AT+APPSKEY"
#define LR16_CMD_NETWORK_SESSION_KEY                "AT+NWKSKEY"
#define LR16_CMD_DEVICE_ADDRESS                     "AT+DADDR"
#define LR16_CMD_DEVICE_ID                          "AT+DEUI"
#define LR16_CMD_NETWORK_ID                         "AT+NWKID"
#define LR16_CMD_GET_LINK_LAYER_VERSION             "AT+LLVER"
#define LR16_CMD_GET_REG_PARAM_VERSION              "AT+RPVER"
#define LR16_CMD_ADAPTIVE_DATA_RATE                 "AT+ADR"
#define LR16_CMD_TX_DATA_RATE                       "AT+DR"
#define LR16_CMD_DUTY_CYCLE_RESTRICTION             "AT+DCS"
#define LR16_CMD_JOIN_1_DELAY                       "AT+JN1DL"
#define LR16_CMD_JOIN_2_DELAY                       "AT+JN2DL"
#define LR16_CMD_RX_1_DELAY                         "AT+RX1DL"
#define LR16_CMD_RX_2_DELAY                         "AT+RX2DL"
#define LR16_CMD_RX_2_DATA_RATE                     "AT+RX2DR"
#define LR16_CMD_RX_2_FREQUENCY                     "AT+RX2FQ"
#define LR16_CMD_TX_POWER                           "AT+TXP"
#define LR16_CMD_PING_SLOT                          "AT+PGSLOT"
#define LR16_CMD_JOIN                               "AT+JOIN"
#define LR16_CMD_LINK_CHECK                         "AT+LINKC"
#define LR16_CMD_SEND                               "AT+SEND"
#define LR16_CMD_CLASS                              "AT+CLASS"
#define LR16_CMD_START_CERTIFICATION_MODE           "AT+CERTIF"
#define LR16_CMD_START_RF_TONE_TEST                 "AT+TTONE"
#define LR16_CMD_START_RF_RSSI_TONE_TEST            "AT+TRSSI"
#define LR16_CMD_TEST_CONFIGURATION                 "AT+TCONF"
#define LR16_CMD_START_RF_TX_TEST                   "AT+TTX"
#define LR16_CMD_START_RF_RX_TEST                   "AT+TRX"
#define LR16_CMD_START_RF_TX_HOOPING_TEST           "AT+TTH"
#define LR16_CMD_STOP_RF_TONE_TEST                  "AT+TOFF"
#define LR16_CMD_P2P_UNICAST_TX                     "AT+P2PUNICASTTX"
#define LR16_CMD_P2P_UNICAST_EX_TX                  "AT+P2PUNICASTEXTX"
#define LR16_CMD_P2P_MULTICAST_TX                   "AT+P2PMULTICASTTX"
#define LR16_CMD_P2P_MULTICAST_EX_TX                "AT+P2PMULTICASTEXTX"
#define LR16_CMD_P2P_BROADCAST_TX                   "AT+P2PBROADCASTTX"
#define LR16_CMD_P2P_RX                             "AT+P2PRX"
#define LR16_CMD_P2P_GPIO_REMOTE_CFG_SET            "AT+P2PGPIORCFGSET"
#define LR16_CMD_P2P_GPIO_REMOTE_CFG_GET            "AT+P2PGPIORCFGGET"
#define LR16_CMD_P2P_GPIO_REMOTE_VALUE_SET          "AT+P2PGPIORVALUESET"
#define LR16_CMD_P2P_GPIO_REMOTE_VALUE_GET          "AT+P2PGPIORVALUEGET"
#define LR16_CMD_P2P_ROLE_USER                      "AT+P2PROLEUS"
#define LR16_CMD_P2P_ROLE_RUNTIME                   "AT+P2PROLERS"
#define LR16_CMD_P2P_DC_TRACKER_USER                "AT+P2PDCTRACKERUS"
#define LR16_CMD_P2P_DC_TRACKER_RUNTIME             "AT+P2PDCTRACKERRS"
#define LR16_CMD_P2P_DC_ENFORCE_USER                "AT+P2PDCENFORCEUS"
#define LR16_CMD_P2P_DC_ENFORCE_RUNTIME             "AT+P2PDCENFORCERS"
#define LR16_CMD_P2P_RF_PROFILE_USER                "AT+P2PRFPROFILEUS"
#define LR16_CMD_P2P_RF_PROFILE_RUNTIME             "AT+P2PRFPROFILERS"
#define LR16_CMD_P2P_TX_POWER_USER                  "AT+P2PTXPOWERUS"
#define LR16_CMD_P2P_TX_POWER_RUNTIME               "AT+P2PTXPOWERRS"
#define LR16_CMD_P2P_RF_CHANNEL_USER                "AT+P2PRFCHANNELUS"
#define LR16_CMD_P2P_RF_CHANNEL_RUNTIME             "AT+P2PRFCHANNELRS"
#define LR16_CMD_P2P_LBT_USER                       "AT+P2PLBTUS"
#define LR16_CMD_P2P_LBT_RUNTIME                    "AT+P2PLBTRS"
#define LR16_CMD_P2P_MAC_SRC_ADDR_USER              "AT+P2PMACSRCADDRUS"
#define LR16_CMD_P2P_MAC_SRC_ADDR_RUNTIME           "AT+P2PMACSRCADDRRS"
#define LR16_CMD_P2P_MAC_DEST_ADDR_USER             "AT+P2PMACDESTADDRUS"
#define LR16_CMD_P2P_MAC_DEST_ADDR_RUNTIME          "AT+P2PMACDESTADDRRS"
#define LR16_CMD_P2P_MAC_GRP_ID_USER                "AT+P2PMACGRPIDUS"
#define LR16_CMD_P2P_MAC_GRP_ID_RUNTIME             "AT+P2PMACGRPIDRS"
#define LR16_CMD_P2P_MAC_ENC_MODE_USER              "AT+P2PMACENCMODEUS"
#define LR16_CMD_P2P_MAC_ENC_MODE_RUNTIME           "AT+P2PMACENCMODERS"
#define LR16_CMD_P2P_MAC_ENC_KEY_USER               "AT+P2PMACENCKEYUS"
#define LR16_CMD_P2P_MAC_ENC_KEY_RUNTIME            "AT+P2PMACENCKEYRS"
#define LR16_CMD_P2P_MAC_TTL_USER                   "AT+P2PMACTTLUS"
#define LR16_CMD_P2P_MAC_TTL_RUNTIME                "AT+P2PMACTTLRS"
#define LR16_CMD_P2P_MAC_ACK_USER                   "AT+P2PMACACKUS"
#define LR16_CMD_P2P_MAC_ACK_RUNTIME                "AT+P2PMACACKRS"
#define LR16_CMD_P2P_RP_THRESH_USER                 "AT+P2PRPTHRESHUS"
#define LR16_CMD_P2P_RP_THRESH_RUNTIME              "AT+P2PRPTHRESHRS"
#define LR16_CMD_P2P_RP_NUM_SLOTS_USER              "AT+P2PRPNUMSLOTSUS"
#define LR16_CMD_P2P_RP_NUM_SLOTS_RUNTIME           "AT+P2PRPNUMSLOTSRS"
#define LR16_CMD_P2P_CMD_RESP_TIMEOUT_USER          "AT+P2PCMDRESPTIMEOUTUS"
#define LR16_CMD_P2P_CMD_RESP_TIMEOUT_RUNTIME       "AT+P2PCMDRESPTIMEOUTRS"
#define LR16_CMD_P2P_GPIO_REMOTE_BLOCK_CFG_USER     "AT+P2PGPIORBLOCKCFGUS"
#define LR16_CMD_P2P_GPIO_REMOTE_BLOCK_CFG_RUNTIME  "AT+P2PGPIORBLOCKCFGRS"

/**
 * @brief LR 16 device response for AT commands.
 * @details Device response after commands.
 */
#define LR16_RSP_OK                                 "OK"
#define LR16_RSP_ERROR                              "AT_ERROR"
#define LR16_RSP_PARAM_ERROR                        "AT_PARAM_ERROR"
#define LR16_RSP_BUSY_ERROR                         "AT_BUSY_ERROR"
#define LR16_RSP_TEST_PARAM_OVERFLOW                "AT_TEST_PARAM_OVERFLOW"
#define LR16_RSP_NO_NETWORK_JOINED                  "AT_NO_NETWORK_JOINED"
#define LR16_RSP_RX_ERROR                           "AT_RX_ERROR"
#define LR16_RSP_DUTYCYCLE_RESTRICTED               "AT_DUTYCYCLE_RESTRICTED"
#define LR16_RSP_CRYPTO_ERROR                       "AT_CRYPTO_ERROR"
#define LR16_RSP_INVALID_MODE                       "AT_INVALID_MODE"
#define LR16_RSP_INVALID_ROLE                       "AT_INVALID_ROLE"

/**
 * @brief LR 16 device events settings.
 * @details Device events settings.
 */
#define LR16_EVT_READY                              "+SYSNOTF:READY"
#define LR16_EVT_CONTEXT_STORAGE                    "+CS:"
#define LR16_EVT_JOIN                               "+JOIN:"
#define LR16_EVT_DATA_RECEIVED                      "+RXDATA:"
#define LR16_EVT_RECEIVE_INFO                       "+RXINFO:"
#define LR16_EVT_UPLINK_CONFIG                      "+TXCONF"
#define LR16_EVT_CLASS_SWITCH                       "+CLASSUPDATE:"
#define LR16_EVT_BEACON_INFO                        "+BEACONINFO:"
#define LR16_EVT_BEACON_LOST                        "+BEACONLOST"
#define LR16_EVT_BEACON_NOT_RECEIVED                "+BEACONNOTRECEIVED"
#define LR16_EVT_P2P_TX_CONF                        "+P2PTXCONF:"
#define LR16_EVT_P2P_TX_RESP                        "+P2PTXRESP:"
#define LR16_EVT_P2P_TX_TIME                        "+P2PTXTIME:"
#define LR16_EVT_P2P_RX_DATA                        "+P2PRXDATA:"
#define LR16_EVT_P2P_GPIO_REMOTE_CFG_SET            "+P2PGPIORCFGSET:"
#define LR16_EVT_P2P_GPIO_REMOTE_CFG_GET            "+P2PGPIORCFGGET:"
#define LR16_EVT_P2P_GPIO_REMOTE_VALUE_SET          "+P2PGPIORVALUESET:"
#define LR16_EVT_P2P_GPIO_REMOTE_VALUE_GET          "+P2PGPIORVALUEGET:"
#define LR16_EVT_P2P_GPIO_REMOTE_CFG_CHANGED        "+P2PGPIORCFGCHANGED:"
#define LR16_EVT_P2P_GPIO_REMOTE_VALUE_CHANGED      "+P2PGPIORVALUECHANGED:"

/**
 * @brief LR 16 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LR16_TX_DRV_BUFFER_SIZE                     200
#define LR16_RX_DRV_BUFFER_SIZE                     600

/*! @} */ // lr16_cmd

/**
 * @defgroup lr16_map LR 16 MikroBUS Map
 * @brief MikroBUS pin mapping of LR 16 Click driver.
 */

/**
 * @addtogroup lr16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LR 16 Click to the selected MikroBUS.
 */
#define LR16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // lr16_map
/*! @} */ // lr16

/**
 * @brief LR 16 Click context object.
 * @details Context object definition of LR 16 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;      /**< Reset pin (active low). */
    digital_out_t wup;      /**< Wake-up pin (active low). */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LR16_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LR16_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LR16_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} lr16_t;

/**
 * @brief LR 16 Click configuration object.
 * @details Configuration object definition of LR 16 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;         /**< Reset pin (active low). */
    pin_name_t wup;         /**< Wake-up pin (active low). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} lr16_cfg_t;

/**
 * @brief LR 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LR16_OK = 0,
    LR16_ERROR = -1,
    LR16_ERROR_TIMEOUT = -2,
    LR16_ERROR_CMD = -3

} lr16_return_value_t;

/*!
 * @addtogroup lr16 LR 16 Click Driver
 * @brief API for configuring and manipulating LR 16 Click driver.
 * @{
 */

/**
 * @brief LR 16 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lr16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lr16_cfg_setup ( lr16_cfg_t *cfg );

/**
 * @brief LR 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lr16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr16_init ( lr16_t *ctx, lr16_cfg_t *cfg );

/**
 * @brief LR 16 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr16_generic_write ( lr16_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LR 16 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr16_generic_read ( lr16_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LR 16 set WUP pin function.
 * @details This function sets the wake-up pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lr16_set_wup_pin ( lr16_t *ctx, uint8_t state );

/**
 * @brief LR 16 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lr16_set_rst_pin ( lr16_t *ctx, uint8_t state );

/**
 * @brief LR 16 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lr16_reset_device ( lr16_t *ctx );

/**
 * @brief LR 16 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lr16_cmd_run ( lr16_t *ctx, uint8_t *cmd );

/**
 * @brief LR 16 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void lr16_cmd_set ( lr16_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief LR 16 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lr16_cmd_get ( lr16_t *ctx, uint8_t *cmd );

/**
 * @brief LR 16 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lr16_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void lr16_cmd_help ( lr16_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // LR16_H

/*! @} */ // lr16

// ------------------------------------------------------------------------ END
