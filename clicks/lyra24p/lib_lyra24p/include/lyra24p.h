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
 * @file lyra24p.h
 * @brief This file contains API for LYRA 24P Click Driver.
 */

#ifndef LYRA24P_H
#define LYRA24P_H

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
 * @addtogroup lyra24p LYRA 24P Click Driver
 * @brief API for configuring and manipulating LYRA 24P Click driver.
 * @{
 */

/**
 * @defgroup lyra24p_cmd LYRA 24P Device Settings
 * @brief Settings for registers of LYRA 24P Click driver.
 */

/**
 * @addtogroup lyra24p_cmd
 * @{
 */

/**
 * @brief LYRA 24P parameter access commands.
 * @details Parameter access commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_AT                     "AT"
#define LYRA24P_CMD_ATPS                   "AT%S"
#define LYRA24P_CMD_ATF                    "AT&F"
#define LYRA24P_CMD_ATW                    "AT&W"
#define LYRA24P_CMD_ATI                    "ATI"
#define LYRA24P_CMD_ATS                    "ATS"

/**
 * @brief LYRA 24P bond database commands.
 * @details Bond database commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATBNDD                 "AT+BNDD"
#define LYRA24P_CMD_ATBNDT                 "AT+BNDT"
#define LYRA24P_CMD_ATBNDX                 "AT+BNDX"

/**
 * @brief LYRA 24P GATT client commands.
 * @details GATT client commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATGCTM                 "AT+GCTM"
#define LYRA24P_CMD_ATGCFA                 "AT+GCFA"
#define LYRA24P_CMD_ATGCRD                 "AT+GCRD"
#define LYRA24P_CMD_ATGCWA                 "AT+GCWA"
#define LYRA24P_CMD_ATGCWC                 "AT+GCWC"
#define LYRA24P_CMD_ATLMTU                 "AT+LMTU"

/**
 * @brief LYRA 24P GATT server commands.
 * @details GATT Server commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATGSMD                 "AT+GSMD"
#define LYRA24P_CMD_ATGSCB                 "AT+GSCB"
#define LYRA24P_CMD_ATGSCE                 "AT+GSCE"
#define LYRA24P_CMD_ATGSSB                 "AT+GSSB"
#define LYRA24P_CMD_ATGSSE                 "AT+GSSE"
#define LYRA24P_CMD_ATGSNO                 "AT+GSNO"
#define LYRA24P_CMD_ATGSWC                 "AT+GSWC"
#define LYRA24P_CMD_ATUUID                 "AT+UUID"

/**
 * @brief LYRA 24P I2C commands.
 * @details I2C commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATI2R                  "AT+I2R"
#define LYRA24P_CMD_ATI2W                  "AT+I2W"

/**
 * @brief LYRA 24P advertising commands.
 * @details Advertising commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATAARA                 "AT+AARA"
#define LYRA24P_CMD_ATACMT                 "AT+ACMT"
#define LYRA24P_CMD_ATADAD                 "AT+ADAD"
#define LYRA24P_CMD_ATARST                 "AT+ARST"
#define LYRA24P_CMD_ATASRA                 "AT+ASRA"
#define LYRA24P_CMD_ATLADV                 "AT+LADV"
#define LYRA24P_CMD_ATLADVX                "AT+LADVX"
#define LYRA24P_CMD_ATEADV                 "AT+EADV"

/**
 * @brief LYRA 24P connection commands.
 * @details Connection commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATCSEC                 "AT+CSEC"
#define LYRA24P_CMD_ATLCON                 "AT+LCON"
#define LYRA24P_CMD_ATLDSC                 "AT+LDSC"
#define LYRA24P_CMD_ATLENC                 "AT+LENC"

/**
 * @brief LYRA 24P scanning commands.
 * @details Scanning commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATSFMT                 "AT+SFMT"
#define LYRA24P_CMD_ATLSCN                 "AT+LSCN"
#define LYRA24P_CMD_ATLSCNX                "AT+LSCNX"

/**
 * @brief LYRA 24P GAP commands.
 * @details GAP commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_LPHY                   "AT+LPHY"

/**
 * @brief LYRA 24P pairing commands.
 * @details Pairing commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATPAIR                 "AT+PAIR"
#define LYRA24P_CMD_ATPCFG                 "AT+PCFG"
#define LYRA24P_CMD_ATPCNF                 "AT+PCNF"
#define LYRA24P_CMD_ATPKEY                 "AT+PKEY"
#define LYRA24P_CMD_ATPRSP                 "AT+PRSP"
#define LYRA24P_CMD_ATOOBL                 "AT+OOBL"
#define LYRA24P_CMD_ATOOBR                 "AT+OOBR"
#define LYRA24P_CMD_ATSIOC                 "AT+SIOC"
#define LYRA24P_CMD_ATSIOR                 "AT+SIOR"
#define LYRA24P_CMD_ATSIOW                 "AT+SIOW"

/**
 * @brief LYRA 24P SPI commands.
 * @details SPI commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATSPR                  "AT+SPR"
#define LYRA24P_CMD_ATSPW                  "AT+SPW"

/**
 * @brief LYRA 24P transmit power commands.
 * @details Transmit power commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATREG                  "AT+REG"
#define LYRA24P_CMD_ATTXPO                 "AT+TXPO"

/**
 * @brief LYRA 24P user function commands.
 * @details User function commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATUFU                  "AT+UFU"

/**
 * @brief LYRA 24P VSP commands.
 * @details VSP commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATD                    "ATD"
#define LYRA24P_CMD_ATLVSP                 "AT+LVSP"

/**
 * @brief LYRA 24P module management commands.
 * @details Module management commands of LYRA 24P Click driver.
 */
#define LYRA24P_CMD_ATZ                    "ATZ"

/**
 * @brief LYRA 24P ATI commands arguments.
 * @details ATI commands arguments of LYRA 24P Click driver.
 */
#define LYRA24P_ATI_ARG_DEV_NAME           "0"
#define LYRA24P_ATI_ARG_FW_VER             "3"
#define LYRA24P_ATI_ARG_BT_ADDR            "4"

/**
 * @brief LYRA 24P ATS commands arguments.
 * @details ATS commands arguments of LYRA 24P Click driver.
 */
#define LYRA24P_ATS_ARG_DEVNAME_FORMAT     "103"
#define LYRA24P_ATS_VAL_DEVNAME            "0"

/**
 * @brief LYRA 24P response arguments.
 * @details Response arguments of LYRA 24P Click driver.
 */
#define LYRA24P_RSP_OK                     "OK"
#define LYRA24P_RSP_ERROR                  "ERROR"

/**
 * @brief LYRA 24P prefix symbols.
 * @details Specified prefix symbols of LYRA 24P Click driver.
 */
#define LYRA24P_PREFIX_SYMBOL_END          "\r\n"
#define LYRA24P_PREFIX_SYMBOL_QUERY        "?"
#define LYRA24P_PREFIX_SYMBOL_SET_VAL      "="
#define LYRA24P_PREFIX_SYMBOL_PLUS         "+"
#define LYRA24P_PREFIX_SYMBOL_SEPARATOR    ","
#define LYRA24P_PREFIX_SYMBOL_SPACE        " "
#define LYRA24P_PREFIX_SYMBOL_PERCENT      "%"
#define LYRA24P_PREFIX_SYMBOL_NULL         ""
#define LYRA24P_PREFIX_SYMBOL_QUOTE        "\""
#define LYRA24P_PREFIX_SYMBOL_ZERO         "0"

/**
 * @brief LYRA 24P pin logic states.
 * @details Pin logic states of LYRA 24P Click driver.
 */
#define LYRA24P_PIN_STATE_LOW               0
#define LYRA24P_PIN_STATE_HIGH              1

/**
 * @brief LYRA 24P pin logic states.
 * @details Pin logic states of LYRA 24P Click driver.
 */
#define LYRA24P_QUERY_DIS                   0
#define LYRA24P_QUERY_EN                    1

/**
 * @brief LYRA 24P driver buffer size.
 * @details Specified size of driver ring  uffer.
 * @note Increase buffer size if needed.
 */
#define LYRA24P_TX_DRV_BUFFER_SIZE         100
#define LYRA24P_RX_DRV_BUFFER_SIZE         300

/*! @} */ // lyra24p_cmd

/**
 * @defgroup lyra24p_map LYRA 24P MikroBUS Map
 * @brief MikroBUS pin mapping of LYRA 24P Click driver.
 */

/**
 * @addtogroup lyra24p_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LYRA 24P Click to the selected MikroBUS.
 */
#define LYRA24P_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX );  \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );  \
    cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts     = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.bt      = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts     = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // lyra24p_map
/*! @} */ // lyra24p

/**
 * @brief LYRA 24P Click context object.
 * @details Context object definition of LYRA 24P Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;    /**< Reset pin. */
    digital_out_t bt;     /**< Boot pin. */
    digital_out_t rts;    /**< Request to send pin. */

    // Input pins
    digital_in_t cts;    /**< Clear to send pin. */

    // Modules
    uart_t uart;         /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ LYRA24P_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ LYRA24P_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} lyra24p_t;

/**
 * @brief LYRA 24P Click configuration object.
 * @details Configuration object definition of LYRA 24P Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;    /**< RX pin. */
    pin_name_t tx_pin;    /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;    /**< Reset pin. */
    pin_name_t rts;    /**< Request to send pin. */
    pin_name_t bt;     /**< Boot pin. */
    pin_name_t cts;    /**< Clear to send pin. */

    // Static variable
    uint32_t         baud_rate;        /**< Clock speed. */
    bool             uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;         /**< Data bits. */
    uart_parity_t    parity_bit;       /**< Parity bit. */
    uart_stop_bits_t stop_bit;         /**< Stop bits. */

} lyra24p_cfg_t;

/**
 * @brief LYRA 24P Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LYRA24P_OK = 0,
    LYRA24P_ERROR = -1

} lyra24p_return_value_t;

/*!
 * @addtogroup lyra24p LYRA 24P Click Driver
 * @brief API for configuring and manipulating LYRA 24P Click driver.
 * @{
 */

/**
 * @brief LYRA 24P configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lyra24p_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lyra24p_cfg_setup ( lyra24p_cfg_t *cfg );

/**
 * @brief LYRA 24P initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lyra24p_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lyra24p_init ( lyra24p_t *ctx, lyra24p_cfg_t *cfg );

/**
 * @brief LYRA 24P HW reset function.
 * @details This function performs a hardware reset of the device.
 * @param[in] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void lyra24p_hw_reset ( lyra24p_t *ctx );

/**
 * @brief LYRA 24P set BT pin state function.
 * @details This function sets a desired logic state of the BT pin.
 * @param[in] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void lyra24p_set_bt_pin ( lyra24p_t *ctx, uint8_t state );

/**
 * @brief LYRA 24P set request to send pin state function.
 * @details This function sets a desired logic state of the RTS pin.
 * @param[in] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return Nothing.
 * @note None.
 */
void lyra24p_request_to_send ( lyra24p_t *ctx, uint8_t state );

/**
 * @brief LYRA 24P get clear to send pin state function.
 * @details This function return logic state of the CTS pin.
 * @param[in] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @return Logic state of the CTS pin.
 * @note None.
 */
uint8_t lyra24p_clear_to_send ( lyra24p_t *ctx );

/**
 * @brief LYRA 24P data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lyra24p_generic_write ( lyra24p_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief LYRA 24P data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lyra24p_generic_read ( lyra24p_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief LYRA 24P command writing function.
 * @details This function writes a desired command by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lyra24p_write_command ( lyra24p_t *ctx, uint8_t *command );

/**
 * @brief LYRA 24P command - command value - prefix - parameter writing function.
 * @details This function writes a desired command, command value, prefix 
 * and parameter by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @param[in] cmd_val : Command value buffer for sending.
 * @param[in] prefix : Prefix buffer for sending.
 * @param[in] param : Parameter buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lyra24p_write_cmd_param ( lyra24p_t *ctx, uint8_t *command, uint8_t *cmd_val, uint8_t *prefix, uint8_t *param );

/**
 * @brief LYRA 24P set device name function.
 * @details This function writes a desired name of the device by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @param[in] device_name : Device name buffer for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lyra24p_set_device_name ( lyra24p_t *ctx, uint8_t *device_name );

/**
 * @brief LYRA 24P inquire command function.
 * @details This function writes a desired inquire command, command value 
 * and enable/disable quote by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lyra24p_t object definition for detailed explanation.
 * @param[in] command : Command buffer for sending.
 * @param[in] cmd_val : Command value buffer for sending.
 * @param[in] en_query : Enable query.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lyra24p_inquire_command ( lyra24p_t *ctx, uint8_t *command, uint8_t *cmd_val, uint8_t en_query );

#ifdef __cplusplus
}
#endif
#endif // LYRA24P_H

/*! @} */ // lyra24p

// ------------------------------------------------------------------------ END
