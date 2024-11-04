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
 * @file lr9.h
 * @brief This file contains API for LR 9 Click Driver.
 */

#ifndef LR9_H
#define LR9_H

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
 * @addtogroup lr9 LR 9 Click Driver
 * @brief API for configuring and manipulating LR 9 Click driver.
 * @{
 */

/**
 * @defgroup lr9_cmd LR 9 Device Settings
 * @brief Settings for registers of LR 9 Click driver.
 */

/**
 * @addtogroup lr9_cmd
 * @{
 */

/**
 * @brief LR 9 AT Command.
 * @details Specified setting for AT Command of LR 9 Click driver.
 */
#define LR9_CMD_AT                  "AT"

/**
 * @brief LR 9 LoRaWAN General Command Sets commands.
 * @details Specified setting for LoRaWAN General Command Sets Commands of LR 9 Click driver.
 */
#define LR9_CMD_CGMI                "CGMI"
#define LR9_CMD_CGMM                "CGMM"
#define LR9_CMD_CGMR                "CGMR"
#define LR9_CMD_CGSN                "CGSN"
#define LR9_CMD_CGBR                "CGBR"

/**
 * @brief LR 9 LoRaWAN Network Related Parameter Setup Command Sets commands.
 * @details Specified setting for LoRaWAN Network Related Parameter Setup Command Sets Commands of LR 9 Click driver.
 */
#define LR9_CMD_CJOINMODE            "CJOINMODE"
#define LR9_CMD_CDEVEUI              "CDEVEUI"
#define LR9_CMD_CAPPEUI              "CAPPEUI"
#define LR9_CMD_CAPPKEY              "CAPPKEY"
#define LR9_CMD_CDEVADDR             "CDEVADDR"
#define LR9_CMD_CAPPSKEY             "CAPPSKEY"
#define LR9_CMD_CNWKSKEY             "CNWKSKEY"
#define LR9_CMD_CFREQBANDMASK        "CFREQBANDMASK"
#define LR9_CMD_CULDLMODE            "CULDLMODE"
#define LR9_CMD_CADDMUTICAST         "CADDMUTICAST"
#define LR9_CMD_CDELMUTICAST         "CDELMUTICAST"
#define LR9_CMD_CNUMMUTICAST         "CNUMMUTICAST"
#define LR9_CMD_CWORKMODE            "CWORKMODE"
#define LR9_CMD_CCLASS               "CCLASS"
#define LR9_CMD_CBL                  "CBL"
#define LR9_CMD_CSTATUS              "CSTATUS"
#define LR9_CMD_CJOIN                "CJOIN"
#define LR9_CMD_CPINGSLOTINFOREQ     "CPINGSLOTINFOREQ"
#define LR9_CMD_DTRX                 "DTRX"
#define LR9_CMD_DRX                  "DRX"

/**
 * @brief LR 9 LoRaWAN MAC Setup Command Sets.
 * @details Specified setting for LoRaWAN MAC Setup Command Sets of LR 9 Click driver.
 */
#define LR9_CMD_CCONFIRM             "CCONFIRM"
#define LR9_CMD_CAPPPORT             "CAPPPORT"
#define LR9_CMD_CDATARATE            "CDATARATE"
#define LR9_CMD_CRSSI                "CRSSI"
#define LR9_CMD_CNBTRIALS            "CNBTRIALS"
#define LR9_CMD_CRM                  "CRM"
#define LR9_CMD_CTXP                 "CTXP"
#define LR9_CMD_CLINKCHECK           "CLINKCHECK"
#define LR9_CMD_CADR                 "CADR"
#define LR9_CMD_CRXP                 "CRXP"
#define LR9_CMD_CRX1DELAY            "CRX1DELAY"
#define LR9_CMD_CSAVE                "CSAVE"
#define LR9_CMD_CRESTORE             "CRESTORE"

/**
 * @brief LR 9 Other Command Sets.
 * @details Specified setting for Other Command Sets of LR 9 Click driver.
 */
#define LR9_CMD_IREBOOT              "IREBOOT"
#define LR9_CMD_ILOGLVL              "ILOGLVL"

/**
 * @brief LR 9 Private Command Sets.
 * @details Specified setting for Private Command Sets of LR 9 Click driver.
 */
#define LR9_CMD_CKEYSPROTECT         "CKEYSPROTECT"

/**
 * @brief LR 9 LoRa Test Commands.
 * @details Specified setting for LoRa Test Commands of LR 9 Click driver.
 */
#define LR9_CMD_CTXADDRSET           "CTXADDRSET"
#define LR9_CMD_CADDRSET             "CADDRSET"
#define LR9_CMD_CTX                  "CTX"
#define LR9_CMD_CRX                  "CRX"
#define LR9_CMD_CRXS                 "CRXS"

/**
 * @brief LR 9 Data Receive Configuration Commands.
 * @details Specified setting for Data Receive Configuration Commands of LR 9 Click driver.
 */
#define LR9_DTRX_CONFIG              "0"
#define LR9_DTRX_UNCONFIG            "1"

/**
 * @brief LR 9 configuration and limits data values.
 * @details Specified setting for configuration data values of LR 9 Click driver.
 */
#define LR9_DTRX_CONFIG_DATA         0
#define LR9_DTRX_UNCONFIG_DATA       1
#define LR9_NB_TRIALS_MIN            1
#define LR9_NB_TRIALS_2              2
#define LR9_NB_TRIALS_MAX            15
#define LR9_DATA_FRAME_MAX           10
#define LR9_MSG_START_POS            16

/**
 * @brief LR 9 control symbols.
 * @details Specified setting for control symbols of LR 9 Click driver.
 */
#define LR9_SYMBOL_END_CMD           "\r\n"
#define LR9_SYMBOL_QUERY             "?"
#define LR9_SYMBOL_SET_VAL_CMD       "="
#define LR9_SYMBOL_PREFIX_CMD        "+"
#define LR9_SYMBOL_SEPARATOR         ","
#define LR9_SYMBOL_SPACE             " "
#define LR9_SYMBOL_NULL               ""
#define LR9_SYMBOL_QUOTE             "\""
#define LR9_ASCII_SPACE              0x20
#define LR9_ASCII_QUOTE              0x22

/**
 * @brief LR 9 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LR9_TX_DRV_BUFFER_SIZE       100
#define LR9_RX_DRV_BUFFER_SIZE       300

/*! @} */ // lr9_cmd

/**
 * @defgroup lr9_map LR 9 MikroBUS Map
 * @brief MikroBUS pin mapping of LR 9 Click driver.
 */

/**
 * @addtogroup lr9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LR 9 Click to the selected MikroBUS.
 */
#define LR9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.bt     = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // lr9_map
/*! @} */ // lr9

/**
 * @brief LR 9 Click context object.
 * @details Context object definition of LR 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t bt;   /**< Boot pin. */
    digital_out_t rst;  /**< Reset pin. */

    // Modules
    uart_t uart;  /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LR9_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ LR9_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} lr9_t;

/**
 * @brief LR 9 Click configuration object.
 * @details Configuration object definition of LR 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;  /**< RX pin. */
    pin_name_t tx_pin;  /**< TX pin. */

    // Additional gpio pins
    pin_name_t bt;   /**< Boot pin. */
    pin_name_t rst;  /**< Reset pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} lr9_cfg_t;

/**
 * @brief LR 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LR9_OK = 0,
    LR9_ERROR = -1

} lr9_return_value_t;

/**
 * @brief LR 9 Click enable equal to data symbol.
 * @details Predefined enum values for driver enable equal to data symbol.
 */
typedef enum
{
    LR9_EQUAL_DISABLE = 0,
    LR9_EQUAL_ENABLE

} lr9_en_set_t;

/*!
 * @addtogroup lr9 LR 9 Click Driver
 * @brief API for configuring and manipulating LR 9 Click driver.
 * @{
 */

/**
 * @brief LR 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lr9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lr9_cfg_setup ( lr9_cfg_t *cfg );

/**
 * @brief LR 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lr9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lr9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr9_init ( lr9_t *ctx, lr9_cfg_t *cfg );

/**
 * @brief LR 9 HW reset function.
 * @details This function performs a hardware reset of the device.
 * @param[in] ctx : Click context object.
 * See #lr9_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void lr9_hw_reset ( lr9_t *ctx );

/**
 * @brief LR 9 set BOOT pin state function.
 * @details This function sets a desired logic state of the BT pin.
 * @param[in] ctx : Click context object.
 * See #lr9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void lr9_set_boot_pin ( lr9_t *ctx, uint8_t state );

/**
 * @brief LR 9 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr9_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr9_generic_write ( lr9_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LR 9 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr9_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr9_generic_read ( lr9_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LR 9 command writing function.
 * @details This function writes a desired command and parameter by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr9_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @param[in] param : Parameter buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr9_write_command ( lr9_t *ctx, uint8_t *command, uint8_t *param );

/**
 * @brief LR 9 inquire writing function.
 * @details Using the UART serial interface, this function writes the desired query command 
 * with or without the included equals symbol.
 * @param[in] ctx : Click context object.
 * See #lr9_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @param[in] param : Parameter buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr9_inquire_command ( lr9_t *ctx, uint8_t *command, lr9_en_set_t en_set );

/**
 * @brief LR 9 send data frame function.
 * @details This function sends the desired data frame by using the UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr9_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @param[in] param : Parameter buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr9_send_data_frame ( lr9_t *ctx, uint8_t confirm, uint8_t nbtrials, uint8_t *data_frame );

#ifdef __cplusplus
}
#endif
#endif // LR9_H

/*! @} */ // lr9

// ------------------------------------------------------------------------ END
