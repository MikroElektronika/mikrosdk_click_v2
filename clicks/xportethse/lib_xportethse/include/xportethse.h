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
 * @file xportethse.h
 * @brief This file contains API for XPort ETH SE Click Driver.
 */

#ifndef XPORTETHSE_H
#define XPORTETHSE_H

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
 * @addtogroup xportethse XPort ETH SE Click Driver
 * @brief API for configuring and manipulating XPort ETH SE Click driver.
 * @{
 */

/**
 * @defgroup xportethse_cmd XPort ETH SE Device Settings
 * @brief Settings for registers of XPort ETH SE Click driver.
 */

/**
 * @addtogroup xportethse_cmd
 * @{
 */

/**
 * @brief XPort ETH SE control commands.
 * @details Specified setting for control commands of XPort ETH SE Click driver.
 */
#define XPORTETHSE_CMD_MODE_CONFIG                          "xxx"
#define XPORTETHSE_CMD_MODE_MONITOR                         "yyy"
#define XPORTETHSE_CMD_MODE_MONITOR_WITH_NET                "zzz"
#define XPORTETHSE_CMD_ENTER                                "\r"
#define XPORTETHSE_CMD_AT                                   "AT"
#define XPORTETHSE_CMD_SET_IP                               "co"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_0                "G0"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_1                "G1"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_2                "G2"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_3                "G3"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_4                "G4"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_5                "G5"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_6                "G6"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_7                "G7"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_8                "G8"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_9                "G9"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_A                "Ga"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_B                "Gb"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_C                "Gc"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_D                "Gd"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_E                "Ge"
#define XPORTETHSE_CMD_GET_MEM_PAGE_CONFIG_F                "Gf"
#define XPORTETHSE_CMD_GET_IP_CONFIG(ADR)                   "GC " ADR
#define XPORTETHSE_CMD_GET_MAC_ADDRESS                      "GM"
#define XPORTETHSE_CMD_NET_CONN                             "NC"
#define XPORTETHSE_CMD_NET_STAT                             "NS"
#define XPORTETHSE_CMD_PING(ADR)                            "PI " ADR
#define XPORTETHSE_CMD_QUIT                                 "QU"
#define XPORTETHSE_CMD_RESET                                "RS"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_0                "S0"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_1                "S1"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_2                "S2"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_3                "S3"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_4                "S4"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_5                "S5"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_6                "S6"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_7                "S7"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_8                "S8"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_9                "S9"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_A                "Sa"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_B                "Sb"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_C                "Sc"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_D                "Sd"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_E                "Se"
#define XPORTETHSE_CMD_SET_MEM_PAGE_CONFIG_F                "Sf"
#define XPORTETHSE_CMD_SCAN                                 "SA"
#define XPORTETHSE_CMD_SEND_CONFIG(ADR)                     "SC " ADR
#define XPORTETHSE_CMD_SET_SECURITY_RECORD                  "SS"
#define XPORTETHSE_CMD_SET_SECURITY_RECORD                  "SS"
#define XPORTETHSE_CMD_TCP_CONN_TABLE                       "TT"
#define XPORTETHSE_CMD_QUERY_FW_VERSION                     "VN"
#define XPORTETHSE_CMD_VERSION(ADR)                         "VS " ADR
#define XPORTETHSE_CMD_FLASH_WRITE_COUNT                    "WC"

/**
 * @brief XPort ETH SE response commands.
 * @details Specified setting for response commands of XPort ETH SE Click driver.
 */
#define XPORTETHSE_RSP_OK                                   "0>"
#define XPORTETHSE_RSP_NO_ANSWER                            "1>"
#define XPORTETHSE_RSP_NO_REACH                             "2>"
#define XPORTETHSE_RSP_WRONG_PAR                            "8>"
#define XPORTETHSE_RSP_INVALID_CMD                          "9>"

/**
 * @brief XPort ETH SE driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define XPORTETHSE_TX_DRV_BUFFER_SIZE                       200
#define XPORTETHSE_RX_DRV_BUFFER_SIZE                       1000

/*! @} */ // xportethse_cmd

/**
 * @defgroup xportethse_map XPort ETH SE MikroBUS Map
 * @brief MikroBUS pin mapping of XPort ETH SE Click driver.
 */

/**
 * @addtogroup xportethse_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of XPort ETH SE Click to the selected MikroBUS.
 */
#define XPORTETHSE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dtr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // xportethse_map
/*! @} */ // xportethse

/**
 * @brief XPort ETH SE Click context object.
 * @details Context object definition of XPort ETH SE Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t cts;              /**< Clear to send pin. */

    // Input pins
    digital_in_t dtr;               /**< Data terminal ready pin. */
    digital_in_t rts;               /**< Request to send pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ XPORTETHSE_RX_DRV_BUFFER_SIZE ];    /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ XPORTETHSE_TX_DRV_BUFFER_SIZE ];    /**< TX Buffer size. */

} xportethse_t;

/**
 * @brief XPort ETH SE Click configuration object.
 * @details Configuration object definition of XPort ETH SE Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t cts;                 /**< Clear to send pin. */
    pin_name_t dtr;                 /**< Data terminal ready pin. */
    pin_name_t rts;                 /**< Request to send pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} xportethse_cfg_t;

/**
 * @brief XPort ETH SE Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    XPORTETHSE_OK = 0,
    XPORTETHSE_ERROR = -1,
    XPORTETHSE_ERROR_TIMEOUT = -2,
    XPORTETHSE_ERROR_CMD = -3

} xportethse_return_value_t;

/*!
 * @addtogroup xportethse XPort ETH SE Click Driver
 * @brief API for configuring and manipulating XPort ETH SE Click driver.
 * @{
 */

/**
 * @brief XPort ETH SE configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #xportethse_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void xportethse_cfg_setup ( xportethse_cfg_t *cfg );

/**
 * @brief XPort ETH SE initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #xportethse_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xportethse_init ( xportethse_t *ctx, xportethse_cfg_t *cfg );

/**
 * @brief XPort ETH SE data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xportethse_generic_write ( xportethse_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief XPort ETH SE data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xportethse_generic_read ( xportethse_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief XPort ETH SE send cmd function.
 * @details This function sends a command string by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @param[in] cmd : Command string to send.
 * @return None.
 * @note None.
 */
void xportethse_send_cmd ( xportethse_t *ctx, uint8_t *cmd );

/**
 * @brief XPort ETH SE send enter function.
 * @details This function sends enter (new line) by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xportethse_send_enter ( xportethse_t *ctx );

/**
 * @brief XPort ETH SE set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xportethse_set_rst_pin ( xportethse_t *ctx, uint8_t state );

/**
 * @brief XPort ETH SE set CTS pin function.
 * @details This function sets the CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void xportethse_set_cts_pin ( xportethse_t *ctx, uint8_t state );

/**
 * @brief XPort ETH SE get RTS pin function.
 * @details This function returns the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xportethse_get_rts_pin ( xportethse_t *ctx );

/**
 * @brief XPort ETH SE get DTR pin function.
 * @details This function returns the DTR pin logic state.
 * @param[in] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t xportethse_get_dtr_pin ( xportethse_t *ctx );

/**
 * @brief XPort ETH SE reset device function.
 * @details This function resets device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #xportethse_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void xportethse_reset_device ( xportethse_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // XPORTETHSE_H

/*! @} */ // xportethse

// ------------------------------------------------------------------------ END
