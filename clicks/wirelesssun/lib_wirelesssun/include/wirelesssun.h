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
 * @file wirelesssun.h
 * @brief This file contains API for Wireless SUN Click Driver.
 */

#ifndef WIRELESSSUN_H
#define WIRELESSSUN_H

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
 * @addtogroup wirelesssun Wireless SUN Click Driver
 * @brief API for configuring and manipulating Wireless SUN Click driver.
 * @{
 */

/**
 * @defgroup wirelesssun_cmd Wireless SUN Device Settings
 * @brief Settings for registers of Wireless SUN Click driver.
 */

/**
 * @addtogroup wirelesssun_cmd
 * @{
 */

/**
 * @brief Wireless SUN control commands.
 * @details Specified setting for control commands of Wireless SUN Click driver.
 */
#define WIRELESSSUN_CMD_HELP            "help"      // help - disp help
#define WIRELESSSUN_CMD_VERS            "vers"      // vers - disp firmware version string
#define WIRELESSSUN_CMD_VERNUM          "vernum"    // vernum - disp firmware version number
#define WIRELESSSUN_CMD_RESET           "reset"     // reset [sec] execute to reset board
#define WIRELESSSUN_CMD_SLEEP           "sleep"     // sleep - execute to turn system sleep
#define WIRELESSSUN_CMD_ECHO            "echo"      // echo [0|1] - set/disp terminal echo
#define WIRELESSSUN_CMD_JSON            "json"      // json [0|1] - set/disp json command mode
#define WIRELESSSUN_CMD_MODE            "mode"      // mode [profile] - set/disp profile mode (0:NONE 1:FAN)
#define WIRELESSSUN_CMD_CHRATE          "chrate"    // chrate [rate] - disp parameter radio frequency rate (Kbps)
#define WIRELESSSUN_CMD_CHAN            "chan"      // chan [low] [high] - set/disp radio channel range
#define WIRELESSSUN_CMD_RCCAL           "rccal"     // rccal [rssi] - set/disp RSSI threshold of CCA
#define WIRELESSSUN_CMD_MAC             "mac"       // mac - disp MAC address
#define WIRELESSSUN_CMD_MACF            "macf"      // macf [allow|deny|del|clr] [mac] - set/disp MAC filtering table
#define WIRELESSSUN_CMD_MTXCTL          "mtxctl"    // mtxctl [0|1] - disp to control MAC TX//time
#define WIRELESSSUN_CMD_PAN             "pan"       // pan [id] - set/disp PAN ID
#define WIRELESSSUN_CMD_NETNAME         "netname"   // netname [name] - set/disp network name
#define WIRELESSSUN_CMD_IP              "ip"        // ip [ADDR] - set/disp self IPv6 address
#define WIRELESSSUN_CMD_INIT            "init"      // init [role] - disp/execute to start/stop node's role <role> 0:stop 1:BORDER 2:ROUTER 3:LEAF
#define WIRELESSSUN_CMD_ATSTART         "atstart"   // atstart [role] - set/disp auto//starting role
#define WIRELESSSUN_CMD_TCPCON          "tcpcon"    // tcpcon <ADDR> [port] - set/execute to connect TCP port
#define WIRELESSSUN_CMD_TCPDIS          "tcpdis"    // tcpdis <ADDR> [port] - set/execute to disconnect TCP port
#define WIRELESSSUN_CMD_LEASEIP         "leaseip"   // leaseip [MAC|del|clr] [ADDR] - set/disp fixed leasing address
#define WIRELESSSUN_CMD_LEASERNG        "leaserng"  // leaserng [num] - set/disp range of leasing address by DHCPv6 server
#define WIRELESSSUN_CMD_STAT            "stat"      // stat - disp system status
#define WIRELESSSUN_CMD_RSTAT           "rstat"     // rstat - disp radio status
#define WIRELESSSUN_CMD_MSTAT           "mstat"     // mstat - disp MAC statistics
#define WIRELESSSUN_CMD_FSTAT           "fstat"     // fstat - disp FAN state
#define WIRELESSSUN_CMD_CHCONFIG        "chconfig"  // chconfig - disp radio channel configuration
#define WIRELESSSUN_CMD_CHCUR           "chcur"     // chcur - disp currrent radio channel number
#define WIRELESSSUN_CMD_MTXAVL          "mtxavl"    // mtxavl - disp available bytes in MAC-TX limitation
#define WIRELESSSUN_CMD_FMSECKEY        "fmseckey"  // fmseckey - disp MAC Security KEY for FAN
#define WIRELESSSUN_CMD_NEBR            "nebr"      // nebr [del|clr] [ADDR] - set/disp neighbors
#define WIRELESSSUN_CMD_PARENT          "parent"    // parent - disp current parent address
#define WIRELESSSUN_CMD_RPLINF          "rplinf"    // rplinf - disp RPL information
#define WIRELESSSUN_CMD_TCPSTAT         "tcpstat"   // tcpstat - disp TCP stat
#define WIRELESSSUN_CMD_RPLSR           "rplsr"     // rplsr [del|clr] [ADDR] - disp RPL Source Route
#define WIRELESSSUN_CMD_LEASED          "leased"    // leased [del|clr] [ADDR] - set/disp leased address from DHCPv6 server
#define WIRELESSSUN_CMD_TCPS            "tcps"      // tcps <ADDR> [port] <data> - send TCP data
#define WIRELESSSUN_CMD_UDPS            "udps"      // udps <ADDR> [port] <data> - send UDP data
#define WIRELESSSUN_CMD_UDPST           "udpst"     // udpst <ADDR> [port] <text> - send UDP text data
#define WIRELESSSUN_CMD_PING            "ping"      // ping <start/stop/state/-> <ADDR>< [sz] [sec] [cnt] - send ping packet
#define WIRELESSSUN_CMD_TCPOPTS         "tcpopts"   // tcpopts [opt] [port|enable] - set/disp TCP options
#define WIRELESSSUN_CMD_UDPOPTS         "udpopts"   // udpopts [opt] [port|enable] - set/disp UDP options
#define WIRELESSSUN_CMD_RMTCMD          "rmtcmd"    // rmtcmd <ADDR> <cmd> [arg1] [arg2] ... - send remote command
#define WIRELESSSUN_CMD_RMTOPTS         "rmtopts"   // rmtopts [opt] [enable] - set/disp RMTCTL options
#define WIRELESSSUN_CMD_RFEC            "rfec"      // rfec [0|1] - set/disp radio FEC mode
#define WIRELESSSUN_CMD_RANTSW          "rantsw"    // rantsw [num] - set/disp anntena switch selection  <num> 0:diversity 1<= : antenna number
#define WIRELESSSUN_CMD_FNODE           "fnode"     // fnode [del|clr] [ADDR] - set/disp FAN connect node
#define WIRELESSSUN_CMD_AUTH            "auth"      // auth [0|1] - set/disp authentication mode
#define WIRELESSSUN_CMD_NODEF           "nodef"     // nodef [allow|deny|del|clr] [mac] - set/disp node filtering table
#define WIRELESSSUN_CMD_PARAM           "param"     // param - disp parameters
#define WIRELESSSUN_CMD_SAVE            "save"      // save - save parameters
#define WIRELESSSUN_CMD_CLEAR           "clear"     // clear - clear parameters
#define WIRELESSSUN_CMD_SVRST           "svrst"     // svrst [reset_delay_sec] - save parameters and reset
#define WIRELESSSUN_CMD_CLRST           "clrst"     // clrst [reset_delay_sec] - clear parameters and reset
#define WIRELESSSUN_CMD_PROMPT_SIGN     "\r\n>"     // Command prompt sign
#define WIRELESSSUN_CMD_DELIMITER       " "         // Command parameters delimiter
#define WIRELESSSUN_RSP_UDPR            "udpr"      // Command parameters delimiter

/**
 * @brief Wireless SUN UDP/TCP responses.
 * @details Specified UDP/TCP responses of Wireless SUN Click driver.
 */
#define WIRELESSSUN_RSP_UDPR            "udpr"
#define WIRELESSSUN_RSP_TCPR            "tcpr"

/**
 * @brief Wireless SUN device role settings.
 * @details Specified setting for device role of Wireless SUN Click driver.
 */
#define WIRELESSSUN_DEVICE_ROLE_STOP    "0"
#define WIRELESSSUN_DEVICE_ROLE_BORDER  "1"
#define WIRELESSSUN_DEVICE_ROLE_ROUTER  "2"
#define WIRELESSSUN_DEVICE_ROLE_LEAF    "3"

/**
 * @brief Wireless SUN TCP/UDP port settings.
 * @details Specified setting for TCP/UDP port of Wireless SUN Click driver.
 */
#define WIRELESSSUN_DEFAULT_PORT        "3610"

/**
 * @brief Wireless SUN driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define TX_DRV_BUFFER_SIZE              100
#define RX_DRV_BUFFER_SIZE              600

/*! @} */ // wirelesssun_cmd

/**
 * @defgroup wirelesssun_map Wireless SUN MikroBUS Map
 * @brief MikroBUS pin mapping of Wireless SUN Click driver.
 */

/**
 * @addtogroup wirelesssun_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Wireless SUN Click to the selected MikroBUS.
 */
#define WIRELESSSUN_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // wirelesssun_map
/*! @} */ // wirelesssun

/**
 * @brief Wireless SUN Click context object.
 * @details Context object definition of Wireless SUN Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;      /**< Reset pin (Active low). */
    digital_out_t cts;      /**< UART CTS pin. */

    // Input pins
    digital_in_t rts;       /**< UART RTS pin. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} wirelesssun_t;

/**
 * @brief Wireless SUN Click configuration object.
 * @details Configuration object definition of Wireless SUN Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;         /**< Reset pin (Active low). */
    pin_name_t cts;         /**< UART CTS pin. */
    pin_name_t rts;         /**< UART RTS pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} wirelesssun_cfg_t;

/**
 * @brief Wireless SUN Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WIRELESSSUN_OK = 0,
    WIRELESSSUN_ERROR = -1,
    WIRELESSSUN_ERROR_TIMEOUT = -2

} wirelesssun_return_value_t;

/*!
 * @addtogroup wirelesssun Wireless SUN Click Driver
 * @brief API for configuring and manipulating Wireless SUN Click driver.
 * @{
 */

/**
 * @brief Wireless SUN configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #wirelesssun_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void wirelesssun_cfg_setup ( wirelesssun_cfg_t *cfg );

/**
 * @brief Wireless SUN initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #wirelesssun_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #wirelesssun_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirelesssun_init ( wirelesssun_t *ctx, wirelesssun_cfg_t *cfg );

/**
 * @brief Wireless SUN data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wirelesssun_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirelesssun_generic_write ( wirelesssun_t *ctx, char *data_in, uint16_t len );

/**
 * @brief Wireless SUN data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #wirelesssun_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t wirelesssun_generic_read ( wirelesssun_t *ctx, char *data_out, uint16_t len );

/**
 * @brief Wireless SUN send cmd function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #wirelesssun_t object definition for detailed explanation.
 * @param[in] cmd : Command string to be send.
 * @return None.
 * @note None.
 */
void wirelesssun_send_cmd ( wirelesssun_t *ctx, char *cmd );

/**
 * @brief Wireless SUN send cmd function.
 * @details This function sends a specified command to the Click module with desired parameters appended to.
 * @param[in] ctx : Click context object.
 * See #wirelesssun_t object definition for detailed explanation.
 * @param[in] cmd : Command string to be send.
 * @param[in] param_buf : Command parameters string to be send.
 * @return None.
 * @note None.
 */
void wirelesssun_send_cmd_with_parameter ( wirelesssun_t *ctx, char *cmd, char *param_buf );

/**
 * @brief Wireless SUN reset device function.
 * @details This function resets the device by toggling the RST pin state.
 * @param[in] ctx : Click context object.
 * See #wirelesssun_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void wirelesssun_reset_device ( wirelesssun_t *ctx );

/**
 * @brief Wireless SUN set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #wirelesssun_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void wirelesssun_set_rst_pin ( wirelesssun_t *ctx, uint8_t state );

/**
 * @brief Wireless SUN set cts pin function.
 * @details This function sets the CTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #wirelesssun_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void wirelesssun_set_cts_pin ( wirelesssun_t *ctx, uint8_t state );

/**
 * @brief Wireless SUN get rts pin function.
 * @details This function returns the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #wirelesssun_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t wirelesssun_get_rts_pin ( wirelesssun_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // WIRELESSSUN_H

/*! @} */ // wirelesssun

// ------------------------------------------------------------------------ END
