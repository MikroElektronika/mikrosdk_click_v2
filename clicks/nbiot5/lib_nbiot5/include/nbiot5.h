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
 * @file nbiot5.h
 * @brief This file contains API for NB IoT 5 Click Driver.
 */

#ifndef NBIOT5_H
#define NBIOT5_H

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
 * @addtogroup nbiot5 NB IoT 5 Click Driver
 * @brief API for configuring and manipulating NB IoT 5 Click driver.
 * @{
 */

/**
 * @defgroup nbiot5_set NB IoT 5 Device Settings
 * @brief Settings for registers of NB IoT 5 Click driver.
 */

/**
 * @addtogroup nbiot5_set
 * @{
 */

/**
 * @brief NB IoT 5 control commands.
 * @details Specified setting for control commands of NB IoT 5 Click driver.
 */
#define NBIOT5_CMD_AT                           "AT"
#define NBIOT5_CMD_CFUN                         "AT+CFUN"
#define NBIOT5_CMD_CEREG                        "AT+CEREG"
#define NBIOT5_CMD_CGDCONT                      "AT+CGDCONT"
#define NBIOT5_CMD_CSQ                          "AT+CSQ"
#define NBIOT5_CMD_COPS                         "AT+COPS"
#define NBIOT5_CMD_CMGS                         "AT+CMGS"
#define NBIOT5_CMD_CMGF                         "AT+CMGF"
#define NBIOT5_CMD_ESOC                         "AT+ESOC"
#define NBIOT5_CMD_ESOCON                       "AT+ESOCON"
#define NBIOT5_CMD_ESOSEND                      "AT+ESOSEND"
#define NBIOT5_CMD_ESOCL                        "AT+ESOCL"

/**
 * @brief NB IoT 5 device response for AT commands.
 * @details Device response after commands.
 */
#define NBIOT5_RSP_OK                           "OK"
#define NBIOT5_RSP_ERROR                        "ERROR"

/**
 * @brief NB IoT 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NBIOT5_RX_DRV_BUFFER_SIZE               256
#define NBIOT5_TX_DRV_BUFFER_SIZE               256

/*! @} */ // nbiot5_set

/**
 * @defgroup nbiot5_map NB IoT 5 MikroBUS Map
 * @brief MikroBUS pin mapping of NB IoT 5 Click driver.
 */

/**
 * @addtogroup nbiot5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NB IoT 5 Click to the selected MikroBUS.
 */
#define NBIOT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.wup    = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs     = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en     = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // nbiot5_map
/*! @} */ // nbiot5

/**
 * @brief NB IoT 5 Click context object.
 * @details Context object definition of NB IoT 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;      /**< Reset pin (Active low). */
    digital_out_t cs;       /**< SPI chip select pin. */
    digital_out_t wup;      /**< Wakeup pin. */
    digital_out_t en;       /**< Enable pin. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ NBIOT5_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ NBIOT5_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} nbiot5_t;

/**
 * @brief NB IoT 5 Click configuration object.
 * @details Configuration object definition of NB IoT 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;         /**< Reset pin (Active low). */
    pin_name_t cs;          /**< SPI chip select pin. */
    pin_name_t wup;         /**< Wakeup pin. */
    pin_name_t en;          /**< Enable pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} nbiot5_cfg_t;

/**
 * @brief NB IoT 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NBIOT5_OK = 0,
    NBIOT5_ERROR = -1,
    NBIOT5_ERROR_TIMEOUT = -2,
    NBIOT5_ERROR_CMD = -3,
    NBIOT5_ERROR_UNKNOWN = -4

} nbiot5_return_value_t;

/*!
 * @addtogroup nbiot5 NB IoT 5 Click Driver
 * @brief API for configuring and manipulating NB IoT 5 Click driver.
 * @{
 */

/**
 * @brief NB IoT 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nbiot5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nbiot5_cfg_setup ( nbiot5_cfg_t *cfg );

/**
 * @brief NB IoT 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nbiot5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot5_init ( nbiot5_t *ctx, nbiot5_cfg_t *cfg );

/**
 * @brief NB IoT 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot5_generic_write ( nbiot5_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NB IoT 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot5_generic_read ( nbiot5_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NB IoT 5 set rst pin function.
 * @details This function sets the RESET pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot5_set_rst_pin ( nbiot5_t *ctx, uint8_t state );

/**
 * @brief NB IoT 5 set cs pin function.
 * @details This function sets the SPI chip select (CS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot5_set_cs_pin ( nbiot5_t *ctx, uint8_t state );

/**
 * @brief NB IoT 5 set wup pin function.
 * @details This function sets the wakeup (WUP) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot5_set_wup_pin ( nbiot5_t *ctx, uint8_t state );

/**
 * @brief NB IoT 5 set en pin function.
 * @details This function sets the enable (EN) pin logic state.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void nbiot5_set_en_pin ( nbiot5_t *ctx, uint8_t state );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 * @return Nothing.
 * @note None.
 */
void nbiot5_send_cmd ( nbiot5_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the Click module.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void nbiot5_send_cmd_with_par ( nbiot5_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void nbiot5_send_cmd_check ( nbiot5_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] at_cmd_buf : Command buffer.
 * @return Nothing.
 * @note None.
 */
void nbiot5_send_cmd_par_check ( nbiot5_t *ctx, uint8_t *at_cmd_buf );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] sim_apn : SIM card APN.
 * @return Nothing.
 * @note None.
 */
void nbiot5_set_sim_apn ( nbiot5_t *ctx, uint8_t *sim_apn );

/**
 * @brief NB IoT 5 send SMS in text mode.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return Nothing.
 * @note None.
 */
void nbiot5_send_sms_text ( nbiot5_t *ctx, uint8_t *phone_number, uint8_t *sms_text );

/**
 * @brief NB IoT 5 send SMS in PDU mode.
 * @details This function sends text message to a phone number in PDU mode.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] service_center_number : SMSC of the SIM card.
 * @param[in] phone_number : Phone number to message.
 * @param[in] sms_text : Message to be sent.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nbiot5_send_sms_pdu ( nbiot5_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );

#ifdef __cplusplus
}
#endif
#endif // NBIOT5_H

/*! @} */ // nbiot5

// ------------------------------------------------------------------------ END
