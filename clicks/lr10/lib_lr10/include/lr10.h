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
 * @file lr10.h
 * @brief This file contains API for LR 10 Click Driver.
 */

#ifndef LR10_H
#define LR10_H

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
 * @addtogroup lr10 LR 10 Click Driver
 * @brief API for configuring and manipulating LR 10 Click driver.
 * @{
 */

/**
 * @defgroup lr10_cmd LR 10 Device Settings
 * @brief Settings for registers of LR 10 Click driver.
 */

/**
 * @addtogroup lr10_cmd
 * @{
 */

/**
 * @brief LR 10 control commands.
 * @details Specified setting for control commands of LR 10 Click driver.
 */
#define LR10_CMD_AT                  "AT"
#define LR10_CMD_FDEFAULT            "FDEFAULT"
#define LR10_CMD_RESET               "RESET"
#define LR10_CMD_LOWPOWER            "LOWPOWER"
#define LR10_CMD_VER                 "VER"
#define LR10_CMD_MSG                 "MSG"
#define LR10_CMD_MSGHEX              "MSGHEX"
#define LR10_CMD_CMSG                "CMSG"
#define LR10_CMD_CMSGHEX             "CMSGHEX"
#define LR10_CMD_PMSG                "PMSG"
#define LR10_CMD_PMSGHEX             "PMSGHEX"
#define LR10_CMD_CH                  "CH"
#define LR10_CMD_DR                  "DR"
#define LR10_CMD_ADR                 "ADR"
#define LR10_CMD_REPT                "REPT"
#define LR10_CMD_RETRY               "RETRY"
#define LR10_CMD_POWER               "POWER"
#define LR10_CMD_RXWIN2              "RXWIN2"
#define LR10_CMD_RXWIN1              "RXWIN1"
#define LR10_CMD_PORT                "PORT"
#define LR10_CMD_MODE                "MODE"
#define LR10_CMD_ID                  "ID"
#define LR10_CMD_KEY                 "KEY"
#define LR10_CMD_CLASS               "CLASS"
#define LR10_CMD_JOIN                "JOIN"
#define LR10_CMD_LW                  "LW"
#define LR10_CMD_BEACON              "BEACON"
#define LR10_CMD_TEST                "TEST"
#define LR10_CMD_UART                "UART"
#define LR10_CMD_DELAY               "DELAY"
#define LR10_CMD_VDD                 "VDD"
#define LR10_CMD_RTC                 "RTC"
#define LR10_CMD_EEPROM              "EEPROM"
#define LR10_CMD_WDT                 "WDT"
#define LR10_CMD_TEMP                "TEMP"
#define LR10_CMD_LOG                 "LOG"

/**
 * @brief LR 10 control subcommands.
 * @details Specified setting for control subcommands of LR 10 Click driver.
 */
#define LR10_SUB_CMD_ID_DEVADDR      "DEVADDR"
#define LR10_SUB_CMD_ID_DEVEUI       "DEVEUI"
#define LR10_SUB_CMD_ID_APPEUI       "APPEUI"
#define LR10_SUB_CMD_CH_NUM          "NUM"
#define LR10_SUB_CMD_KEY_NWKSKEY     "NWKSKEY"
#define LR10_SUB_CMD_KEY_APPSKEY     "APPSKEY"
#define LR10_SUB_CMD_MODE_TEST       "TEST"
#define LR10_SUB_CMD_MODE_LWOTAA     "LWOTAA"
#define LR10_SUB_CMD_MODE_LWABP      "LWABP"
#define LR10_SUB_CMD_JOIN_FORCE      "FORCE"
#define LR10_SUB_CMD_JOIN_AUTO       "AUTO"
#define LR10_SUB_CMD_BEACON_DMMUL    "DMMUL"
#define LR10_SUB_CMD_BEACON_INFO     "INFO"
#define LR10_SUB_CMD_BEACON_GWGPS    "GWGPS"
#define LR10_SUB_CMD_DELAY_RX1       "RX1"
#define LR10_SUB_CMD_DELAY_RX2       "RX2"
#define LR10_SUB_CMD_DELAY_JRX1      "JRX1"
#define LR10_SUB_CMD_DELAY_JRX2      "JRX2"
#define LR10_SUB_CMD_LW_CDR          "CDR"
#define LR10_SUB_CMD_LW_ULDL         "ULDL"
#define LR10_SUB_CMD_LW_DC           "DC"
#define LR10_SUB_CMD_LW_NET          "NET"
#define LR10_SUB_CMD_LW_MC           "MC"
#define LR10_SUB_CMD_LW_THLD         "THLD"
#define LR10_SUB_CMD_LW_BAT          "BAT"
#define LR10_SUB_CMD_LW_TPS          "TPS"
#define LR10_SUB_CMD_LW_SCR          "SCR"
#define LR10_SUB_CMD_LW_JDC          "JDC"
#define LR10_SUB_CMD_LW_CT           "CT"
#define LR10_SUB_CMD_LW_LEN          "LEN"
#define LR10_SUB_CMD_LW_VER          "VER"
#define LR10_SUB_CMD_LW_DTR          "DTR"
#define LR10_SUB_CMD_LW_LCR          "LCR"
#define LR10_SUB_CMD_LW_LDRO         "LDRO"
#define LR10_SUB_CMD_LW_DCMRX        "DCMRX"
#define LR10_SUB_CMD_LW_DUMRX        "DUMRX"
#define LR10_SUB_CMD_LW_AFPACK       "AFPACK"
#define LR10_SUB_CMD_LW_CHRB         "CHRB"
#define LR10_SUB_CMD_RTC_ZONE        "ZONE"
#define LR10_SUB_CMD_RTC_FULL        "FULL"
#define LR10_SUB_CMD_RTC_LEAPSEC     "LEAPSEC"
#define LR10_SUB_CMD_RTC_UTCMS       "UTCMS"
#define LR10_SUB_CMD_EEPROM_ADDR     "ADDR"
#define LR10_SUB_CMD_UART_TIMEOUT    "TIMEOUT"
#define LR10_SUB_CMD_UART_BR         "BR"
#define LR10_SUB_CMD_TEST_STOP       "STOP"
#define LR10_SUB_CMD_TEST_HELP       "HELP"
#define LR10_SUB_CMD_TEST_TXCW       "TXCW"
#define LR10_SUB_CMD_TEST_TXCLORA    "TXCLORA"
#define LR10_SUB_CMD_TEST_RFCFG      "RFCFG"
#define LR10_SUB_CMD_TEST_RX         "RXLRPKT"
#define LR10_SUB_CMD_TEST_TX_HEX     "TXLRPKT"
#define LR10_SUB_CMD_TEST_TX_STR     "TXLRSTR"
#define LR10_SUB_CMD_TEST_RSSI       "RSSI"
#define LR10_SUB_CMD_LOG_DEBUG       "DEBUG"
#define LR10_SUB_CMD_LOG_QUIET       "QUIET"

/**
 * @brief LR 10 control symbols.
 * @details Specified setting for control symbols of LR 10 Click driver.
 */
#define LR10_SYMBOL_END_CMD           "\r\n"
#define LR10_SYMBOL_QUERY             "?"
#define LR10_SYMBOL_SET_VAL_CMD       "="
#define LR10_SYMBOL_PREFIX_CMD        "+"
#define LR10_SYMBOL_SEPARATOR         ","
#define LR10_SYMBOL_SPACE             " "
#define LR10_SYMBOL_NULL               ""
#define LR10_SYMBOL_QUOTE             "\""
#define LR10_ASCII_SPACE              0x20
#define LR10_ASCII_QUOTE              0x22


/**
 * @brief LR 10 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LR10_TX_DRV_BUFFER_SIZE      100
#define LR10_RX_DRV_BUFFER_SIZE      300

/*! @} */ // lr10_cmd

/**
 * @defgroup lr10_map LR 10 MikroBUS Map
 * @brief MikroBUS pin mapping of LR 10 Click driver.
 */

/**
 * @addtogroup lr10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LR 10 Click to the selected MikroBUS.
 */
#define LR10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // lr10_map
/*! @} */ // lr10

/**
 * @brief LR 10 Click context object.
 * @details Context object definition of LR 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;  /**< Reset pin. */

    // Modules
    uart_t uart;        /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LR10_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ LR10_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} lr10_t;

/**
 * @brief LR 10 Click configuration object.
 * @details Configuration object definition of LR 10 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;    /**< RX pin. */
    pin_name_t tx_pin;    /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;    /**< Reset pin. */

    // Static variable
    uint32_t         baud_rate;        /**< Clock speed. */
    bool             uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;         /**< Data bits. */
    uart_parity_t    parity_bit;       /**< Parity bit. */
    uart_stop_bits_t stop_bit;         /**< Stop bits. */

} lr10_cfg_t;

/**
 * @brief LR 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LR10_OK = 0,
    LR10_ERROR = -1

} lr10_return_value_t;

/**
 * @brief LR 10 Click enable quote value data.
 * @details Predefined enum values for driver enable quote values.
 */
typedef enum
{
    LR10_QUOTE_DISABLE = 0,
    LR10_QUOTE_ENABLE

} lr10_en_quote_t;

/*!
 * @addtogroup lr10 LR 10 Click Driver
 * @brief API for configuring and manipulating LR 10 Click driver.
 * @{
 */

/**
 * @brief LR 10 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lr10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lr10_cfg_setup ( lr10_cfg_t *cfg );

/**
 * @brief LR 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lr10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lr10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr10_init ( lr10_t *ctx, lr10_cfg_t *cfg );

/**
 * @brief LR 10 HW reset function.
 * @details This function performs a hardware reset of the device.
 * @param[in] ctx : Click context object.
 * See #lr10_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void lr10_hw_reset ( lr10_t *ctx );

/**
 * @brief LR 10 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr10_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr10_generic_write ( lr10_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LR 10 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr10_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr10_generic_read ( lr10_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LR 10 command writing function.
 * @details This function writes a desired command by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr10_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr10_write_cmd ( lr10_t *ctx, uint8_t *command );

/**
 * @brief LR 10 command - parameter writing function.
 * @details This function writes a desired command and parameter by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr10_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @param[in] param : Parameter buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr10_write_cmd_param ( lr10_t *ctx, uint8_t *command, uint8_t *param );

/**
 * @brief LR 10 command - subcommands - parameter writing function.
 * @details This function writes a desired command, subcommands and parameter 
 * by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr10_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @param[in] sub_param : Subcommands buffer for sending.
 * @param[in] param : Parameter buffer for sending.
 * @param[in] en_quote : Enable quote.
 * See #lr10_en_quote_t definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr10_write_cmd_sub_param ( lr10_t *ctx, uint8_t *command, uint8_t *sub_param, 
                                              uint8_t *param, lr10_en_quote_t en_quote );

/**
 * @brief LR 10 inquire command function.
 * @details This function writes a desired inquire command by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr10_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr10_inquire_cmd ( lr10_t *ctx, uint8_t *command );


#ifdef __cplusplus
}
#endif
#endif // LR10_H

/*! @} */ // lr10

// ------------------------------------------------------------------------ END
