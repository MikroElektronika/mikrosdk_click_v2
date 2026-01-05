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
 * @file nbiot7.h
 * @brief This file contains API for NB IoT 7 Click Driver.
 */

#ifndef NBIOT7_H
#define NBIOT7_H

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
 * @addtogroup nbiot7 NB IoT 7 Click Driver
 * @brief API for configuring and manipulating NB IoT 7 Click driver.
 * @{
 */

/**
 * @defgroup nbiot7_cmd NB IoT 7 Device Settings
 * @brief Settings for registers of NB IoT 7 Click driver.
 */

/**
 * @addtogroup nbiot7_cmd
 * @{
 */

/**
 * @brief NB IoT 7 control commands.
 * @details Specified setting for control commands of NB IoT 7 Click driver.
 */
#define NBIOT7_CMD_AT                               "AT"
#define NBIOT7_CMD_GET_MODEL_ID                     "AT+CGMM"
#define NBIOT7_CMD_GET_SW_VERSION                   "AT+CGMR"
#define NBIOT7_CMD_GET_SERIAL_NUM                   "AT+CGSN"
#define NBIOT7_CMD_DISABLE_ECHO                     "ATE0"
#define NBIOT7_CMD_ENABLE_ECHO                      "ATE1"
#define NBIOT7_CMD_SET_PHONE_FUNCTIONALITY          "AT+CFUN"
#define NBIOT7_CMD_NETWORK_REGISTRATION             "AT+CREG"
#define NBIOT7_CMD_EPS_NETWORK_REGISTRATION         "AT+CEREG"
#define NBIOT7_CMD_SIGNAL_QUALITY_REPORT            "AT+CSQ"
#define NBIOT7_CMD_OPERATOR_SELECTION               "AT+COPS"
#define NBIOT7_CMD_DEFINE_PDP_CONTEXT               "AT+CGDCONT"
#define NBIOT7_CMD_SHOW_PDP_ADDRESS                 "AT+IPADDR"
#define NBIOT7_CMD_START_TCPIP_SERVICE              "AT+NETOPEN"
#define NBIOT7_CMD_OPEN_TCP_UDP_CONNECTION          "AT+CIPOPEN"
#define NBIOT7_CMD_SEND_DATA_VIA_CONNECTION         "AT+CIPSEND"
#define NBIOT7_CMD_RECEIVE_DATA_VIA_CONNECTION      "AT+CIPRXGET"
#define NBIOT7_CMD_CLOSE_TCP_UDP_CONNECTION         "AT+CIPCLOSE"

/**
 * @brief NB IoT 7 device response for AT commands.
 * @details Device response after commands.
 */
#define NBIOT7_RSP_OK                               "OK"
#define NBIOT7_RSP_ERROR                            "ERROR"

/**
 * @brief NB IoT 7 device response time for AT commands.
 * @details Device response time after commands.
 */
#define NBIOT7_MAX_RSP_TIME_DEFAULT                 500ul
#define NBIOT7_MAX_RSP_TIME_COPS                    120000ul
#define NBIOT7_MAX_RSP_TIME_CFUN                    10000ul
#define NBIOT7_MAX_RSP_TIME_NETOPEN                 120000ul
#define NBIOT7_MAX_RSP_TIME_IPADDR                  9000ul
#define NBIOT7_MAX_RSP_TIME_CIPRXGET                8000ul
#define NBIOT7_MAX_RSP_TIME_CIPOPEN                 120000ul
#define NBIOT7_MAX_RSP_TIME_CIPSEND                 120000ul
#define NBIOT7_MAX_RSP_TIME_CIPCLOSE                120000ul
#define NBIOT7_MAX_RSP_TIME_URC                     30000ul

/**
 * @brief NB IoT 7 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define NBIOT7_URC_AT_READY                         "ATREADY:"
#define NBIOT7_URC_RECEIVED_DATA                    "+CIPRXGET:"
#define NBIOT7_URC_CONNECTION_OPEN                  "+CIPOPEN:"
#define NBIOT7_URC_CONNECTION_CLOSED                "+CIPCLOSE:"
#define NBIOT7_URC_NETWORK_REGISTERED               "+CEREG: 2,1"
#define NBIOT7_URC_NETWORK_OPEN                     "+NETOPEN: 1"

/**
 * @brief NB IoT 7 power state settings.
 * @details Specified power state settings of NB IoT 7 Click driver.
 */
#define NBIOT7_POWER_STATE_ON                       0
#define NBIOT7_POWER_STATE_OFF                      1

/**
 * @brief NB IoT 7 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NBIOT7_TX_DRV_BUFFER_SIZE                   256
#define NBIOT7_RX_DRV_BUFFER_SIZE                   256

/*! @} */ // nbiot7_cmd

/**
 * @defgroup nbiot7_map NB IoT 7 MikroBUS Map
 * @brief MikroBUS pin mapping of NB IoT 7 Click driver.
 */

/**
 * @addtogroup nbiot7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NB IoT 7 Click to the selected MikroBUS.
 */
#define NBIOT7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.wkp = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ring = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // nbiot7_map
/*! @} */ // nbiot7

/**
 * @brief NB IoT 7 Click context object.
 * @details Context object definition of NB IoT 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wkp;              /**< Wakeup pin. */
    digital_out_t rst;              /**< Reset pin. */
    digital_out_t rts;              /**< UART ready to send pin. */

    // Input pins
    digital_in_t ring;              /**< Ring indicator pin. */
    digital_in_t cts;               /**< UART clear to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ NBIOT7_RX_DRV_BUFFER_SIZE ];    /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ NBIOT7_TX_DRV_BUFFER_SIZE ];    /**< TX Buffer size. */
    uint8_t cmd_buffer[ NBIOT7_TX_DRV_BUFFER_SIZE ];        /**< Command buffer. */

} nbiot7_t;

/**
 * @brief NB IoT 7 Click configuration object.
 * @details Configuration object definition of NB IoT 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t wkp;                 /**< Wakeup pin. */
    pin_name_t rst;                 /**< Reset pin. */
    pin_name_t rts;                 /**< UART ready to send pin. */
    pin_name_t ring;                /**< Ring indicator pin. */
    pin_name_t cts;                 /**< UART clear to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} nbiot7_cfg_t;

/**
 * @brief NB IoT 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NBIOT7_OK = 0,
    NBIOT7_ERROR = -1,
    NBIOT7_ERROR_TIMEOUT = -2,
    NBIOT7_ERROR_CMD = -3

} nbiot7_return_value_t;

/*!
 * @addtogroup nbiot7 NB IoT 7 Click Driver
 * @brief API for configuring and manipulating NB IoT 7 Click driver.
 * @{
 */

/**
 * @brief NB IoT 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nbiot7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nbiot7_cfg_setup ( nbiot7_cfg_t *cfg );

/**
 * @brief NB IoT 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nbiot7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot7_init ( nbiot7_t *ctx, nbiot7_cfg_t *cfg );

/**
 * @brief NB IoT 7 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot7_generic_write ( nbiot7_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NB IoT 7 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot7_generic_read ( nbiot7_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NB IoT 7 set WKP pin function.
 * @details This function sets the WAKEUP pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot7_set_wkp_pin ( nbiot7_t *ctx, uint8_t state );

/**
 * @brief NB IoT 7 set RST pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot7_set_rst_pin ( nbiot7_t *ctx, uint8_t state );

/**
 * @brief NB IoT 7 set RTS pin function.
 * @details This function sets the request to send (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot7_set_rts_pin ( nbiot7_t *ctx, uint8_t state );

/**
 * @brief NB IoT 7 get RING pin function.
 * @details This function returns the ring indication (RING) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nbiot7_get_ring_pin ( nbiot7_t *ctx );

/**
 * @brief NB IoT 7 get CTS pin function.
 * @details This function returns the clear to send (CTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nbiot7_get_cts_pin ( nbiot7_t *ctx );

/**
 * @brief NB IoT 7 set power state function.
 * @details This function sets a desired power state by toggling WKP and RST pins with a specific timing.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - ON,
 *                    @li @c 1 - OFF.
 * @return None.
 * @note None.
 */
void nbiot7_set_power_state ( nbiot7_t *ctx, uint8_t state );

/**
 * @brief NB IoT 7 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void nbiot7_cmd_run ( nbiot7_t *ctx, uint8_t *cmd );

/**
 * @brief NB IoT 7 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void nbiot7_cmd_set ( nbiot7_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief NB IoT 7 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void nbiot7_cmd_get ( nbiot7_t *ctx, uint8_t *cmd );

/**
 * @brief NB IoT 7 cmd help function.
 * @details This function provides a short description of the given command of the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void nbiot7_cmd_help ( nbiot7_t *ctx, uint8_t *cmd );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #nbiot7_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void nbiot7_set_sim_apn ( nbiot7_t *ctx, uint8_t *sim_apn );

#ifdef __cplusplus
}
#endif
#endif // NBIOT7_H

/*! @} */ // nbiot7

// ------------------------------------------------------------------------ END
