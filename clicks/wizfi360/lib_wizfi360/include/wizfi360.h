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
 * @file wizfi360.h
 * @brief This file contains API for WIZFI360 Click Driver.
 */

#ifndef WIZFI360_H
#define WIZFI360_H

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
 * @addtogroup wizfi360 WIZFI360 Click Driver
 * @brief API for configuring and manipulating WIZFI360 Click driver.
 * @{
 */

/**
 * @defgroup wizfi360_cmd WIZFI360 Device Settings
 * @brief Settings for registers of WIZFI360 Click driver.
 */

/**
 * @addtogroup wizfi360_cmd
 * @{
 */

/**
 * @brief WIZFI360 system control commands.
 * @details Specified setting for system control commands of WIZFI360 Click driver.
 */
#define WIZFI360_CMD_AT                  "AT"
#define WIZFI360_CMD_RST                 "AT+RST"
#define WIZFI360_CMD_GMR                 "AT+GMR"
#define WIZFI360_CMD_GSLP                "AT+GSLP"
#define WIZFI360_CMD_ATE                 "ATE"
#define WIZFI360_CMD_RESTORE             "AT+RESTORE"
#define WIZFI360_CMD_UART_CUR            "AT+UART_CUR"
#define WIZFI360_CMD_UART_DEF            "AT+UART_DEF"
#define WIZFI360_CMD_SLEEP               "AT+SLEEP"
#define WIZFI360_CMD_SYSIOSETCFG         "AT+SYSIOSETCFG"
#define WIZFI360_CMD_SYSIOGETCFG         "AT+SYSIOGETCFG"
#define WIZFI360_CMD_SYSGPIODIR          "AT+SYSGPIODIR"
#define WIZFI360_CMD_SYSGPIOWRITE        "AT+SYSGPIOWRITE"
#define WIZFI360_CMD_SYSGPIOREAD         "AT+SYSGPIOREAD"
#define WIZFI360_CMD_EXECUTE_AT_CMD      "+++"

/**
 * @brief WIZFI360 WiFi commands.
 * @details Specified setting for WiFi commands of WIZFI360 Click driver.
 */
#define WIZFI360_CMD_CWMODE_CUR          "AT+CWMODE_CUR"
#define WIZFI360_CMD_CWMODE_DEF          "AT+CWMODE_DEF"
#define WIZFI360_CMD_CWJAP_CUR           "AT+CWJAP_CUR"
#define WIZFI360_CMD_CWJAP_DEF           "AT+CWJAP_DEF"
#define WIZFI360_CMD_CWLAPOPT            "AT+CWLAPOPT"
#define WIZFI360_CMD_CWLAP               "AT+CWLAP"
#define WIZFI360_CMD_CWQAP               "AT+CWQAP"
#define WIZFI360_CMD_CWSAP_CUR           "AT+CWSAP_CUR"
#define WIZFI360_CMD_CWSAP_DEF           "AT+CWSAP_DEF"
#define WIZFI360_CMD_CWLIF               "AT+CWLIF"
#define WIZFI360_CMD_CWDHCP_CUR          "AT+CWDHCP_CUR"
#define WIZFI360_CMD_CWDHCP_DEF          "AT+CWDHCP_DEF"
#define WIZFI360_CMD_CWDHCPS_CUR         "AT+CWDHCPS_CUR"
#define WIZFI360_CMD_CWDHCPS_DEF         "AT+CWDHCPS_DEF"
#define WIZFI360_CMD_CWAUTOCONN          "AT+CWAUTOCONN"
#define WIZFI360_CMD_CIPSTAMAC_CUR       "AT+CIPSTAMAC_CUR"
#define WIZFI360_CMD_CIPSTAMAC_DEF       "AT+CIPSTAMAC_DEF"
#define WIZFI360_CMD_CIPAPMAC_CUR        "AT+CIPAPMAC_CUR"
#define WIZFI360_CMD_CIPAPMAC_DEF        "AT+CIPAPMAC_DEF"
#define WIZFI360_CMD_CIPSTA_CUR          "AT+CIPSTA_CUR"
#define WIZFI360_CMD_CIPSTA_DEF          "AT+CIPSTA_DEF"
#define WIZFI360_CMD_CIPAP_CUR           "AT+CIPAP_CUR"
#define WIZFI360_CMD_CIPAP_DEF           "AT+CIPAP_DEF"
#define WIZFI360_CMD_CWSTARTSMART        "AT+CWSTARTSMART"
#define WIZFI360_CMD_CWSTOPSMART         "AT+CWSTOPSMART"
#define WIZFI360_CMD_WPS                 "AT+WPS"
#define WIZFI360_CMD_CWHOSTNAME          "AT+CWHOSTNAME"
#define WIZFI360_CMD_CWCOUNTRY_CUR       "AT+CWCOUNTRY_CUR"
#define WIZFI360_CMD_CWCOUNTRY_DEF       "AT+CWCOUNTRY_DEF"
#define WIZFI360_CMD_WIZ_NETCONFIG       "AT+WIZ_NETCONFIG"

/**
 * @brief WIZFI360 TCP/IP commands.
 * @details Specified setting for TCP/IP commands of WIZFI360 Click driver.
 */
#define WIZFI360_CMD_CIPSTATUS           "AT+CIPSTATUS"
#define WIZFI360_CMD_CIPDOMAIN           "AT+CIPDOMAIN"
#define WIZFI360_CMD_CIPSTART            "AT+CIPSTART"
#define WIZFI360_CMD_CIPSSLSIZE          "AT+CIPSSLSIZE"
#define WIZFI360_CMD_CIPSSLCCONF         "AT+CIPSSLCCONF"
#define WIZFI360_CMD_CASEND              "AT+CASEND"
#define WIZFI360_CMD_CIPSEND             "AT+CIPSEND"
#define WIZFI360_CMD_CIPSENDEX           "AT+CIPSENDEX"
#define WIZFI360_CMD_CIPSENDBUF          "AT+CIPSENDBUF"
#define WIZFI360_CMD_CIPBUFRESET         "AT+CIPBUFRESET"
#define WIZFI360_CMD_CIPBUFSTATUS        "AT+CIPBUFSTATUS"
#define WIZFI360_CMD_CIPCHECKSEQ         "AT+CIPCHECKSEQ"
#define WIZFI360_CMD_CIPCLOSE            "AT+CIPCLOSE"
#define WIZFI360_CMD_CIFSR               "AT+CIFSR"
#define WIZFI360_CMD_CIPMUX              "AT+CIPMUX"
#define WIZFI360_CMD_CIPSERVER           "AT+CIPSERVER"
#define WIZFI360_CMD_CIPSERVERMAXCONN    "AT+CIPSERVERMAXCONN"
#define WIZFI360_CMD_CIPMODE             "AT+CIPMODE"
#define WIZFI360_CMD_SAVETRANSLINK       "AT+SAVETRANSLINK"
#define WIZFI360_CMD_CIPSTO              "AT+CIPSTO"
#define WIZFI360_CMD_CIUPDATE            "AT+CIUPDATE"
#define WIZFI360_CMD_PING                "AT+PING"
#define WIZFI360_CMD_CIPDINFO            "AT+CIPDINFO"
#define WIZFI360_CMD_CIPSNTPCFG          "AT+CIPSNTPCFG"
#define WIZFI360_CMD_CIPSNTPTIME         "AT+CIPSNTPTIME"
#define WIZFI360_CMD_CIPDNS_CUR          "AT+CIPDNS_CUR"
#define WIZFI360_CMD_CIPDNS_DEF          "AT+CIPDNS_DEF"
#define WIZFI360_CMD_MQTTSET             "AT+MQTTSET"
#define WIZFI360_CMD_MQTTOPIC            "AT+MQTTOPIC"
#define WIZFI360_CMD_MQTTQOS             "AT+MQTTQOS"
#define WIZFI360_CMD_MQTTCON             "AT+MQTTCON"
#define WIZFI360_CMD_MQTTPUB             "AT+MQTTPUB"
#define WIZFI360_CMD_MQTTPUBSEND         "AT+MQTTPUBSEND"
#define WIZFI360_CMD_MQTTDIS             "AT+MQTTDIS"
#define WIZFI360_CMD_AZSET               "AT+AZSET"
#define WIZFI360_CMD_AZCON               "AT+AZCON"
#define WIZFI360_CMD_AWSPKSEND           "AT+AWSPKSEND"
#define WIZFI360_CMD_CLICASEND           "AT+CLICASEND"
#define WIZFI360_CMD_AWSCON              "AT+AWSCON"

/**
 * @brief WIZFI360 current WiFi mode selection.
 * @details Specified current WiFi mode selection of WIZFI360 Click driver.
 */
#define WIZFI360_CWMODE_STATION          "1"
#define WIZFI360_CWMODE_SOFTAP           "2"
#define WIZFI360_CWMODE_STATION_SOFTAP   "3"

/**
 * @brief WIZFI360 multiple connections selection.
 * @details Specified multiple connections selection of WIZFI360 Click driver.
 */
#define WIZFI360_CIPMUX_SINGLE_CONN      "0"
#define WIZFI360_CIPMUX_MULTIPLE_CONN    "1"

/**
 * @brief WIZFI360 multiple connections selection.
 * @details Specified multiple connections selection of WIZFI360 Click driver.
 */
#define WIZFI360_CWDHCP_SOFTAP           "0,0"
#define WIZFI360_CWDHCP_SOFTAP_DHCP      "0,1"
#define WIZFI360_CWDHCP_STATION          "1,0"
#define WIZFI360_CWDHCP_STATION_DHCP     "1,1"
#define WIZFI360_CWDHCP_SOFTAP_STATION   "2,0"
#define WIZFI360_CWDHCP_SFT_ST_DHCP      "2,1"

/**
 * @brief WIZFI360 SNTP configuration parameter.
 * @details Specified SNTP configuration parameter of WIZFI360 Click driver.
 */
#define WIZFI360_ENABLE_TIMEZONE_1       "1,1"

/**
 * @brief WIZFI360 prefix symbols.
 * @details Specified prefix symbols of WIZFI360 Click driver.
 */
#define WIZFI360_PREFIX_SYMB_END         "\r\n"
#define WIZFI360_PREFIX_SYMB_QUOTE       "\""
#define WIZFI360_PREFIX_SYMB_SEPARATOR   ","
#define WIZFI360_PREFIX_SYMB_QUERY       "?"
#define WIZFI360_PREFIX_SYMB_SET_VAL     "="
#define WIZFI360_PREFIX_SYMB_PLUS        "+"
#define WIZFI360_PREFIX_SYMB_SPACE       " "
#define WIZFI360_PREFIX_SYMB_NULL        ""

/**
 * @brief WIZFI360 response arguments.
 * @details Response arguments of WIZFI360 Click driver.
 */
#define WIZFI360_RSP_OK                  "OK"
#define WIZFI360_RSP_ERROR               "ERROR"
#define WIZFI360_RSP_READY_FOR_SEND      ">"
#define WIZFI360_RSP_SEND_OK             "SEND OK"
#define WIZFI360_RECEIVE                 "+IPD"
#define WIZFI360_MESSAGE_END             "\032"

/**
 * @brief WIZFI360 logic states of the digital output pins.
 * @details Logic states of the digital output pins of WIZFI360 Click driver.
 */
#define WIZFI360_PIN_STATE_LOW           0
#define WIZFI360_PIN_STATE_HIGH          1

/**
 * @brief WIZFI360 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define WIZFI360_TX_DRV_BUFFER_SIZE      100
#define WIZFI360_RX_DRV_BUFFER_SIZE      300

/*! @} */ // wizfi360_cmd

/**
 * @defgroup wizfi360_map WIZFI360 MikroBUS Map
 * @brief MikroBUS pin mapping of WIZFI360 Click driver.
 */

/**
 * @addtogroup wizfi360_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of WIZFI360 Click to the selected MikroBUS.
 */
#define WIZFI360_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX );  \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );  \
    cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.bt      = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.cts     = MIKROBUS( mikrobus, MIKROBUS_CS );  \
    cfg.wkp     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts     = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // wizfi360_map
/*! @} */ // wizfi360

/**
 * @brief WIZFI360 Click context object.
 * @details Context object definition of WIZFI360 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t bt;     /**< Boot pin. */
    digital_out_t rst;    /**< Reset pin. */
    digital_out_t cts;    /**< Clear to send pin. */
    digital_out_t wkp;    /**< Wake-up pin. */

    // Input pins
    digital_in_t rts;     /**< Request to send pin. */

    // Modules
    uart_t uart;          /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ WIZFI360_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ WIZFI360_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} wizfi360_t;

/**
 * @brief WIZFI360 Click configuration object.
 * @details Configuration object definition of WIZFI360 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;    /**< RX pin. */
    pin_name_t tx_pin;    /**< TX pin. */

    // Additional gpio pins
    pin_name_t bt;        /**< Boot pin. */
    pin_name_t rst;       /**< Reset pin. */
    pin_name_t cts;       /**< Clear to send pin. */
    pin_name_t wkp;       /**< Wake-up pin. */
    pin_name_t rts;       /**< Request to send pin. */

    // Static variable
    uint32_t         baud_rate;        /**< Clock speed. */
    bool             uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;         /**< Data bits. */
    uart_parity_t    parity_bit;       /**< Parity bit. */
    uart_stop_bits_t stop_bit;         /**< Stop bits. */

} wizfi360_cfg_t;

/**
 * @brief WIZFI360 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WIZFI360_OK = 0,
    WIZFI360_ERROR = -1

} wizfi360_return_value_t;

/*!
 * @addtogroup wizfi360 WIZFI360 Click Driver
 * @brief API for configuring and manipulating WIZFI360 Click driver.
 * @{
 */

/**
 * @brief WIZFI360 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #wizfi360_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void wizfi360_cfg_setup ( wizfi360_cfg_t *cfg );

/**
 * @brief WIZFI360 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wizfi360_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wizfi360_init ( wizfi360_t *ctx, wizfi360_cfg_t *cfg );

/**
 * @brief WIZFI360 set RST pin state function.
 * @details This function sets a desired logic state of the RST pin.
 * @param[out] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void wizfi360_set_rst_pin ( wizfi360_t *ctx, uint8_t state );

/**
 * @brief WIZFI360 set BT pin state function.
 * @details This function sets a desired logic state of the BT pin.
 * @param[out] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void wizfi360_set_bt_pin ( wizfi360_t *ctx, uint8_t state );

/**
 * @brief WIZFI360 wake up function.
 * @details This function performs the wake-up and the module is reset 
 * to the normal operating mode.
 * @param[out] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void wizfi360_wake_up ( wizfi360_t *ctx );

/**
 * @brief WIZFI360 standby function.
 * @details This function performs the standby mode.
 * @param[out] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void wizfi360_standby ( wizfi360_t *ctx );

/**
 * @brief WIZFI360 get request to send pin state function.
 * @details This function return logic state of the RTS pin.
 * to the normal operating mode.
 * @param[out] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @return Logic state of the CTS pin.
 * @note None.
 */
uint8_t wizfi360_request_to_send ( wizfi360_t *ctx );

/**
 * @brief WIZFI360 set clear to send pin state function.
 * @details This function sets a desired logic state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void wizfi360_clear_to_send ( wizfi360_t *ctx, uint8_t state );

/**
 * @brief WIZFI360 data writing function.
 * @details This function writes a desired number of data bytes 
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wizfi360_generic_write ( wizfi360_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief WIZFI360 data reading function.
 * @details This function reads a desired number of data bytes 
 * by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wizfi360_generic_read ( wizfi360_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief WIZFI360 command writing function.
 * @details This function writes a desired command by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wizfi360_write_command ( wizfi360_t *ctx, uint8_t *command );

/**
 * @brief WIZFI360 command - prefix - parameter writing function.
 * @details This function writes a desired command, prefix 
 * and parameter by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @param[in] prefix : Prefix buffer for sending.
 * @param[in] param : Parameter buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wizfi360_write_cmd_param ( wizfi360_t *ctx, uint8_t *command, uint8_t *prefix, uint8_t *param );

/**
 * @brief WIZFI360 inquire command function.
 * @details This function writes a desired inquire command 
 * by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @param[in] command : Inquire command buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wizfi360_inquire_command ( wizfi360_t *ctx, uint8_t *command );

/**
 * @brief WIZFI360 send message function.
 * @details This function sends messages to the host in normal transmission mode 
 * using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wizfi360_t object definition for detailed explanation.
 * @param[in] message : Message data buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wizfi360_send_message ( wizfi360_t *ctx, uint8_t *message );

#ifdef __cplusplus
}
#endif
#endif // WIZFI360_H

/*! @} */ // wizfi360

// ------------------------------------------------------------------------ END
