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
 * @file lr15.h
 * @brief This file contains API for LR 15 Click Driver.
 */

#ifndef LR15_H
#define LR15_H

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
 * @addtogroup lr15 LR 15 Click Driver
 * @brief API for configuring and manipulating LR 15 Click driver.
 * @{
 */

/**
 * @defgroup lr15_cmd LR 15 Device Settings
 * @brief Settings for registers of LR 15 Click driver.
 */

/**
 * @addtogroup lr15_cmd
 * @{
 */

/**
 * @brief LR 15 control commands.
 * @details Specified setting for control commands of LR 15 Click driver.
 */
#define LR15_CMD_AT                                 "AT"
#define LR15_CMD_VER                                "AT+VER"
#define LR15_CMD_ID                                 "AT+ID"
#define LR15_CMD_RESET                              "AT+RESET"
#define LR15_CMD_MSG                                "AT+MSG"
#define LR15_CMD_CMSG                               "AT+CMSG"
#define LR15_CMD_MSGHEX                             "AT+MSGHEX"
#define LR15_CMD_CMSGHEX                            "AT+CMSGHEX"
#define LR15_CMD_PMSG                               "AT+PMSG"
#define LR15_CMD_PMSGHEX                            "AT+PMSGHEX"
#define LR15_CMD_PORT                               "AT+PORT"
#define LR15_CMD_ADR                                "AT+ADR"
#define LR15_CMD_DR                                 "AT+DR"
#define LR15_CMD_CH                                 "AT+CH"
#define LR15_CMD_POWER                              "AT+POWER"
#define LR15_CMD_REPT                               "AT+REPT"
#define LR15_CMD_RETRY                              "AT+RETRY"
#define LR15_CMD_RXWIN2                             "AT+RXWIN2"
#define LR15_CMD_RXWIN1                             "AT+RXWIN1"
#define LR15_CMD_KEY                                "AT+KEY"
#define LR15_CMD_FDEFAULT                           "AT+FDEFAULT"
#define LR15_CMD_DFU                                "AT+DFU"
#define LR15_CMD_MODE                               "AT+MODE"
#define LR15_CMD_JOIN                               "AT+JOIN"
#define LR15_CMD_BEACON                             "AT+BEACON"
#define LR15_CMD_CLASS                              "AT+CLASS"
#define LR15_CMD_DELAY                              "AT+DELAY"
#define LR15_CMD_LW                                 "AT+LW"
#define LR15_CMD_WDT                                "AT+WDT"
#define LR15_CMD_LOWPOWER                           "AT+LOWPOWER"
#define LR15_CMD_VDD                                "AT+VDD"
#define LR15_CMD_TEMP                               "AT+TEMP"
#define LR15_CMD_RTC                                "AT+RTC"
#define LR15_CMD_EEPROM                             "AT+EEPROM"
#define LR15_CMD_UART                               "AT+UART"
#define LR15_CMD_TEST                               "AT+TEST"
#define LR15_CMD_LOG                                "AT+LOG"

/**
 * @brief LR 15 command parameters list.
 * @details Specified list of command parameters of LR 15 Click driver.
 */
#define LR10_PARAM_ID_DEVADDR                       "DEVADDR"
#define LR10_PARAM_ID_DEVEUI                        "DEVEUI"
#define LR10_PARAM_ID_APPEUI                        "APPEUI"
#define LR10_PARAM_CH_NUM                           "NUM"
#define LR10_PARAM_KEY_NWKSKEY                      "NWKSKEY"
#define LR10_PARAM_KEY_APPSKEY                      "APPSKEY"
#define LR15_PARAM_MODE_TEST                        "TEST"
#define LR15_PARAM_MODE_LWOTAA                      "LWOTAA"
#define LR15_PARAM_MODE_LWABP                       "LWABP"
#define LR15_PARAM_JOIN_FORCE                       "FORCE"
#define LR15_PARAM_JOIN_AUTO                        "AUTO"
#define LR15_PARAM_BEACON_DMMUL                     "DMMUL"
#define LR15_PARAM_BEACON_INFO                      "INFO"
#define LR15_PARAM_BEACON_GWGPS                     "GWGPS"
#define LR15_PARAM_DELAY_RX1                        "RX1"
#define LR15_PARAM_DELAY_RX2                        "RX2"
#define LR15_PARAM_DELAY_JRX1                       "JRX1"
#define LR15_PARAM_DELAY_JRX2                       "JRX2"
#define LR15_PARAM_LW_CDR                           "CDR"
#define LR15_PARAM_LW_ULDL                          "ULDL"
#define LR15_PARAM_LW_DC                            "DC"
#define LR15_PARAM_LW_NET                           "NET"
#define LR15_PARAM_LW_MC                            "MC"
#define LR15_PARAM_LW_THLD                          "THLD"
#define LR15_PARAM_LW_BAT                           "BAT"
#define LR15_PARAM_LW_TPS                           "TPS"
#define LR15_PARAM_LW_SCR                           "SCR"
#define LR15_PARAM_LW_JDC                           "JDC"
#define LR15_PARAM_LW_CT                            "CT"
#define LR15_PARAM_LW_LEN                           "LEN"
#define LR15_PARAM_LW_VER                           "VER"
#define LR15_PARAM_LW_DTR                           "DTR"
#define LR15_PARAM_LW_LCR                           "LCR"
#define LR15_PARAM_LW_LDRO                          "LDRO"
#define LR15_PARAM_LW_DCMRX                         "DCMRX"
#define LR15_PARAM_LW_DUMRX                         "DUMRX"
#define LR15_PARAM_LW_AFPACK                        "AFPACK"
#define LR15_PARAM_LW_CHRB                          "CHRB"
#define LR15_PARAM_RTC_ZONE                         "ZONE"
#define LR15_PARAM_RTC_FULL                         "FULL"
#define LR15_PARAM_RTC_LEAPSEC                      "LEAPSEC"
#define LR15_PARAM_RTC_UTCMS                        "UTCMS"
#define LR15_PARAM_EEPROM_ADDR                      "ADDR"
#define LR15_PARAM_UART_TIMEOUT                     "TIMEOUT"
#define LR15_PARAM_UART_BR                          "BR"
#define LR15_PARAM_TEST_STOP                        "STOP"
#define LR15_PARAM_TEST_HELP                        "HELP"
#define LR15_PARAM_TEST_TXCW                        "TXCW"
#define LR15_PARAM_TEST_TXCLORA                     "TXCLORA"
#define LR15_PARAM_TEST_RFCFG                       "RFCFG"
#define LR15_PARAM_TEST_RXLRPKT                     "RXLRPKT"
#define LR15_PARAM_TEST_TXLRPKT                     "TXLRPKT"
#define LR15_PARAM_TEST_TXLRSTR                     "TXLRSTR"
#define LR15_PARAM_TEST_RSSI                        "RSSI"
#define LR15_PARAM_LOG_DEBUG                        "DEBUG"
#define LR15_PARAM_LOG_QUIET                        "QUIET"

/**
 * @brief LR 15 device response for AT commands.
 * @details Device response after commands.
 */
#define LR15_RSP_ERROR                              "ERROR"
#define LR15_RSP_AT                                 "+AT"
#define LR15_RSP_VER                                "+VER"
#define LR15_RSP_ID                                 "+ID"
#define LR15_RSP_RESET                              "+RESET"
#define LR15_RSP_MSG                                "+MSG"
#define LR15_RSP_CMSG                               "+CMSG"
#define LR15_RSP_MSGHEX                             "+MSGHEX"
#define LR15_RSP_CMSGHEX                            "+CMSGHEX"
#define LR15_RSP_PMSG                               "+PMSG"
#define LR15_RSP_PMSGHEX                            "+PMSGHEX"
#define LR15_RSP_PORT                               "+PORT"
#define LR15_RSP_ADR                                "+ADR"
#define LR15_RSP_DR                                 "+DR"
#define LR15_RSP_CH                                 "+CH"
#define LR15_RSP_POWER                              "+POWER"
#define LR15_RSP_REPT                               "+REPT"
#define LR15_RSP_RETRY                              "+RETRY"
#define LR15_RSP_RXWIN2                             "+RXWIN2"
#define LR15_RSP_RXWIN1                             "+RXWIN1"
#define LR15_RSP_KEY                                "+KEY"
#define LR15_RSP_FDEFAULT                           "+FDEFAULT"
#define LR15_RSP_DFU                                "+DFU"
#define LR15_RSP_MODE                               "+MODE"
#define LR15_RSP_JOIN                               "+JOIN"
#define LR15_RSP_BEACON                             "+BEACON"
#define LR15_RSP_CLASS                              "+CLASS"
#define LR15_RSP_DELAY                              "+DELAY"
#define LR15_RSP_LW                                 "+LW"
#define LR15_RSP_WDT                                "+WDT"
#define LR15_RSP_LOWPOWER                           "+LOWPOWER"
#define LR15_RSP_VDD                                "+VDD"
#define LR15_RSP_TEMP                               "+TEMP"
#define LR15_RSP_RTC                                "+RTC"
#define LR15_RSP_EEPROM                             "+EEPROM"
#define LR15_RSP_UART                               "+UART"
#define LR15_RSP_TEST                               "+TEST"
#define LR15_RSP_TEST_STOP                          "+TEST: STOP"
#define LR15_RSP_TEST_HELP                          "+TEST: HELP"
#define LR15_RSP_TEST_TXCW                          "+TEST: TXCW"
#define LR15_RSP_TEST_TXCLORA                       "+TEST: TXCLORA"
#define LR15_RSP_TEST_RFCFG                         "+TEST: RFCFG"
#define LR15_RSP_TEST_RXLRPKT                       "+TEST: RXLRPKT"
#define LR15_RSP_TEST_TXLRPKT                       "+TEST: TXLRPKT"
#define LR15_RSP_TEST_TXLRSTR                       "+TEST: TXLRSTR"
#define LR15_RSP_TEST_TX_DONE                       "+TEST: TX DONE"
#define LR15_RSP_TEST_RXLEN                         "+TEST: LEN:"
#define LR15_RSP_TEST_RX                            "+TEST: RX "
#define LR15_RSP_LOG                                "+LOG"
#define LR15_RSP_TIMEOUT_DEFAULT                    2000

/**
 * @brief LR 15 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define LR15_TX_DRV_BUFFER_SIZE                     200
#define LR15_RX_DRV_BUFFER_SIZE                     600

/*! @} */ // lr15_cmd

/**
 * @defgroup lr15_map LR 15 MikroBUS Map
 * @brief MikroBUS pin mapping of LR 15 Click driver.
 */

/**
 * @addtogroup lr15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LR 15 Click to the selected MikroBUS.
 */
#define LR15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.boot = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // lr15_map
/*! @} */ // lr15

/**
 * @brief LR 15 Click context object.
 * @details Context object definition of LR 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                  /**< Reset pin (active low). */
    digital_out_t boot;                 /**< Boot mode pin (active low). */

    // Modules
    uart_t uart;                        /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LR15_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ LR15_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ LR15_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} lr15_t;

/**
 * @brief LR 15 Click configuration object.
 * @details Configuration object definition of LR 15 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Reset pin (active low). */
    pin_name_t boot;                    /**< Boot mode pin (active low). */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} lr15_cfg_t;

/**
 * @brief LR 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LR15_OK = 0,
    LR15_ERROR = -1,
    LR15_ERROR_TIMEOUT = -2,
    LR15_ERROR_CMD = -3

} lr15_return_value_t;

/*!
 * @addtogroup lr15 LR 15 Click Driver
 * @brief API for configuring and manipulating LR 15 Click driver.
 * @{
 */

/**
 * @brief LR 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lr15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lr15_cfg_setup ( lr15_cfg_t *cfg );

/**
 * @brief LR 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lr15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr15_init ( lr15_t *ctx, lr15_cfg_t *cfg );

/**
 * @brief LR 15 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr15_generic_write ( lr15_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LR 15 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lr15_generic_read ( lr15_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LR 15 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lr15_set_rst_pin ( lr15_t *ctx, uint8_t state );

/**
 * @brief LR 15 set BOOT pin function.
 * @details This function sets the boot pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void lr15_set_boot_pin ( lr15_t *ctx, uint8_t state );

/**
 * @brief LR 15 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void lr15_reset_device ( lr15_t *ctx );

/**
 * @brief LR 15 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see LR15_CMD_x definitions.
 * @return None.
 * @note None.
 */
void lr15_cmd_run ( lr15_t *ctx, uint8_t *cmd );

/**
 * @brief LR 15 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see LR15_CMD_x definitions.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void lr15_cmd_set ( lr15_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief LR 15 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see LR15_CMD_x definitions.
 * @return None.
 * @note None.
 */
void lr15_cmd_get ( lr15_t *ctx, uint8_t *cmd );

/**
 * @brief LR 15 cmd param set function.
 * @details This function sets a value to a specified command parameter of the Click module.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see LR15_CMD_x definitions.
 * @param[in] param : Parameter string, see LR15_PARAM_x definitions.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void lr15_cmd_param_set ( lr15_t *ctx, uint8_t *cmd, uint8_t *param, uint8_t *value );

/**
 * @brief LR 15 cmd param get function.
 * @details This function is used to get the value of a given command parameter from the Click module.
 * @param[in] ctx : Click context object.
 * See #lr15_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see LR15_CMD_x definitions.
 * @param[in] param : Parameter string, see LR15_PARAM_x definitions.
 * @return None.
 * @note None.
 */
void lr15_cmd_param_get ( lr15_t *ctx, uint8_t *cmd, uint8_t *param );

#ifdef __cplusplus
}
#endif
#endif // LR15_H

/*! @} */ // lr15

// ------------------------------------------------------------------------ END
