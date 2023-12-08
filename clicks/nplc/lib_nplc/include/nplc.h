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
 * @file nplc.h
 * @brief This file contains API for N-PLC Click Driver.
 */

#ifndef NPLC_H
#define NPLC_H

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
 * @addtogroup nplc N-PLC Click Driver
 * @brief API for configuring and manipulating N-PLC Click driver.
 * @{
 */

/**
 * @defgroup nplc_cmd N-PLC Device Settings
 * @brief Settings for registers of N-PLC Click driver.
 */

/**
 * @addtogroup nplc_cmd
 * @{
 */

/**
 * @brief N-PLC control commands.
 * @details Specified setting for control commands of N-PLC Click driver.
 */
#define NPLC_CMD_COMMAND_MODE   "+++"       /**< Go to command mode. */
#define NPLC_CMD_DATA_MODE      "ATO"       /**< Go online - data mode. */
#define NPLC_CMD_S100           "ATS100"    /**< G3/IEEE modulation code. */
#define NPLC_CMD_S110           "ATS110"    /**< XXR sub-carriers. */
#define NPLC_CMD_S111           "ATS111"    /**< XXR band, 0=CENELEC, 1=FCC. */
#define NPLC_CMD_S112           "ATS112"    /**< XXR redundancy. */
#define NPLC_CMD_S113           "ATS113"    /**< G3/IEEE operation mode. */
#define NPLC_CMD_S114           "ATS114"    /**< Transmit level attenuation in dB. */
#define NPLC_CMD_S300           "ATS300"    /**< ASCII passthru default enabled. */
#define NPLC_CMD_S301           "ATS301"    /**< Default run mode, 0=command, 1=data. */
#define NPLC_CMD_S302           "ATS302"    /**< Packet terminator, 1=CR, 2=LF, 3=CRLF, 4=EOT. */
#define NPLC_CMD_S305           "ATS305"    /**< Packet timeout in ms. */
#define NPLC_CMD_S306           "ATS306"    /**< Hardware handshake enable (1). */
#define NPLC_CMD_FWI            "AT+FWI"    /**< Show firmware version. */
#define NPLC_CMD_X              "ATX"       /**< Exit ASCII mode. */
#define NPLC_CMD_Z              "ATZ"       /**< Do reset. */
#define NPLC_CMD_F              "AT&F"      /**< Load factory default configuration. */
#define NPLC_CMD_W              "AT&W"      /**< Write configuration to flash. */
#define NPLC_CMD_H              "AT&H"      /**< Show help (this). */
#define NPLC_CMD_V              "AT&V"      /**< Show current configuration. */

/**
 * @brief N-PLC mode selection.
 * @details Specified mode selection of N-PLC Click driver.
 */
#define NPLC_MODE_COMMAND       0
#define NPLC_MODE_DATA          1

/**
 * @brief N-PLC driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NPLC_DRV_BUFFER_SIZE    200

/*! @} */ // nplc_cmd

/**
 * @defgroup nplc_map N-PLC MikroBUS Map
 * @brief MikroBUS pin mapping of N-PLC Click driver.
 */

/**
 * @addtogroup nplc_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of N-PLC Click to the selected MikroBUS.
 */
#define NPLC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.md1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // nplc_map
/*! @} */ // nplc

/**
 * @brief N-PLC Click context object.
 * @details Context object definition of N-PLC Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cts;          /**< Handshake in pin. */
    digital_out_t rst;          /**< Reset pin (Active low). */
    digital_out_t md1;          /**< Mode select 1 pin (1-boot, 0-normal). */

    // Input pins
    digital_in_t rts;           /**< Handshake out pin. */

    // Modules
    uart_t uart;                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ NPLC_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    char uart_tx_buffer[ NPLC_DRV_BUFFER_SIZE ];    /**< Buffer size. */

} nplc_t;

/**
 * @brief N-PLC Click configuration object.
 * @details Configuration object definition of N-PLC Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t cts;             /**< Handshake in pin. */
    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t md1;             /**< Mode select 1 pin (1-boot, 0-normal). */
    pin_name_t rts;             /**< Handshake out pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} nplc_cfg_t;

/**
 * @brief N-PLC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NPLC_OK = 0,
    NPLC_ERROR = -1

} nplc_return_value_t;

/*!
 * @addtogroup nplc N-PLC Click Driver
 * @brief API for configuring and manipulating N-PLC Click driver.
 * @{
 */

/**
 * @brief N-PLC configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nplc_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nplc_cfg_setup ( nplc_cfg_t *cfg );

/**
 * @brief N-PLC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nplc_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nplc_init ( nplc_t *ctx, nplc_cfg_t *cfg );

/**
 * @brief N-PLC data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nplc_generic_write ( nplc_t *ctx, char *data_in, uint16_t len );

/**
 * @brief N-PLC data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nplc_generic_read ( nplc_t *ctx, char *data_out, uint16_t len );

/**
 * @brief N-PLC set rst pin function.
 * @details This function sets the reset (RST) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @param[in] state : Pin logic state (Active Low).
 * @return None.
 * @note None.
 */
void nplc_set_rst_pin ( nplc_t *ctx, uint8_t state );

/**
 * @brief N-PLC set md1 pin function.
 * @details This function sets the mode select 1 (MD1) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @param[in] state : Mode select 1 pin (1-boot, 0-normal).
 * @return None.
 * @note None.
 */
void nplc_set_md1_pin ( nplc_t *ctx, uint8_t state );

/**
 * @brief N-PLC set cts pin function.
 * @details This function sets the handshake in (CTS) pin to a desired state.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nplc_set_cts_pin ( nplc_t *ctx, uint8_t state );

/**
 * @brief N-PLC get rts pin function.
 * @details This function returns the handshake out (RTS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nplc_get_rts_pin ( nplc_t *ctx );

/**
 * @brief N-PLC hw reset function.
 * @details This function resets the module by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void nplc_hw_reset ( nplc_t *ctx );

/**
 * @brief N-PLC sw reset function.
 * @details This function software resets the device.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void nplc_sw_reset ( nplc_t *ctx );

/**
 * @brief N-PLC factory reset function.
 * @details This function factory resets the device.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void nplc_factory_reset ( nplc_t *ctx );

/**
 * @brief N-PLC firmware version function.
 * @details This function sends the show firmware version command.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void nplc_firmware_version ( nplc_t *ctx );

/**
 * @brief N-PLC set mode function.
 * @details This function sets operation mode to command or data.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Command mode,
 *                   @li @c 1 - Data mode.
 * @return None.
 * @note None.
 */
void nplc_set_mode ( nplc_t *ctx, uint8_t mode );

/**
 * @brief N-PLC send command function.
 * @details This function sends a desired command with the CR/LF bytes appended to.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @return None.
 * @note None.
 */
void nplc_send_cmd ( nplc_t *ctx, char *cmd );

/**
 * @brief N-PLC write s register function.
 * @details This function sends a desired write S register command with 
 * the parameter buffer and CR/LF bytes appended to.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @param[in] s_reg : S register command (without equal sign and CR/LF).
 * @param[in] param_buf : Parameters string.
 * @return None.
 * @note None.
 */
void nplc_write_s_register ( nplc_t *ctx, char *s_reg, char *param_buf );

/**
 * @brief N-PLC read s register function.
 * @details This function sends a desired read S register command with 
 * the question mark and CR/LF bytes appended to.
 * @param[in] ctx : Click context object.
 * See #nplc_t object definition for detailed explanation.
 * @param[in] s_reg : S register command (without question mark and CR/LF).
 * @return None.
 * @note None.
 */
void nplc_read_s_register ( nplc_t *ctx, char *s_reg );

#ifdef __cplusplus
}
#endif
#endif // NPLC_H

/*! @} */ // nplc

// ------------------------------------------------------------------------ END
