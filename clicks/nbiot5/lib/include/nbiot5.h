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

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup nbiot5 NB IoT 5 Click Driver
 * @brief API for configuring and manipulating NB IoT 5 Click driver.
 * @{
 */

/**
 * @defgroup nbiot5_reg NB IoT 5 Commands List
 * @brief List of commands of NB IoT 5 Click driver.
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
 * @brief NB IoT 5 description setting.
 * @details Specified setting for description of NB IoT 5 Click driver.
 */

#define NBIOT5_CMD_ATI          "ATI"
#define NBIOT5_CMD_CIMI         "AT+CIMI"
#define NBIOT5_CMD_CSQ          "AT+CSQ"

#define NBIOT5_SET_CFUN         "AT+CFUN=1"
#define NBIOT5_SET_CREG         "AT+CREG=2"
#define NBIOT5_SET_COPS         "AT+COPS=0"
#define NBIOT5_SET_CMGF         "AT+CMGF=1"

#define NBIOT5_CHECK_CGATT      "AT+CGATT?"
#define NBIOT5_CHECK_CREG       "AT+CREG?"

/**
 * @brief NB IoT 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE         200

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
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.wkp = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM ); \

/*! @} */ // nbiot5_map
/*! @} */ // nbiot5

/**
 * @brief NB IoT 5 Click context object.
 * @details Context object definition of NB IoT 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wkp;                          /**< Description. */
    digital_out_t rst;                          /**< Description. */
    digital_out_t cs;                           /**< Description. */
    digital_out_t en;                           /**< Description. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];     /**< Buffer size. */

} nbiot5_t;

/**
 * @brief NB IoT 5 Click configuration object.
 * @details Configuration object definition of NB IoT 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins

    pin_name_t wkp;                             /**< Description. */
    pin_name_t rst;                             /**< Description. */
    pin_name_t cs;                              /**< Description. */
    pin_name_t en;                              /**< Description. */

    // Static variable
    uint32_t          baud_rate;                /**< Clock speed. */
    bool              uart_blocking;            /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                 /**< Data bits. */
    uart_parity_t     parity_bit;               /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                 /**< Stop bits. */

} nbiot5_cfg_t;

/*!
 * @addtogroup nbiot5 NB IoT 5 Click Driver
 * @brief API for configuring and manipulating NB IoT 5 Click driver.
 * @{
 */

/**
 * @brief NB IoT 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
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
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nbiot5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t nbiot5_init ( nbiot5_t *ctx, nbiot5_cfg_t *cfg );

/**
 * @brief NB IoT 5 default configuration function.
 * @details This function executes a default configuration of NB IoT 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t nbiot5_default_cfg ( nbiot5_t *ctx );

/**
 * @brief NB IoT 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t nbiot5_generic_write ( nbiot5_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief NB IoT 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 */
err_t nbiot5_generic_read ( nbiot5_t *ctx, char *data_buf, uint16_t max_len );


/**
 * @brief Sets state of the @b wkp pin setting.
 * @details This function sets @b wkp pin output to
 * @b state setting.
 * @param[in] ctx Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] state Output value setting.
 *         @li @c  0 - digital out high,
 *         @li @c  1 - digital out low.
 */
void nbiot5_set_wkp ( nbiot5_t *ctx, uint8_t state );

/**
 * @brief Sets state of the @b en pin setting.
 * @details This function sets @b en pin output to
 * @b state setting.
 * @param[in] ctx Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] state Output value setting.
 *         @li @c  0 - digital out high,
 *         @li @c  1 - digital out low.
 */
void nbiot5_set_en ( nbiot5_t *ctx, uint8_t state );

/**
 * @brief Sets state of the @b rst pin setting.
 * @details This function sets @b rst pin output to
 * @b state setting.
 * @param[in] ctx Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] state Output value setting.
 *         @li @c  0 - digital out high,
 *         @li @c  1 - digital out low.
 */
void nbiot5_set_rst ( nbiot5_t *ctx, uint8_t state );

/**
 * @brief Sets state of the @b cs pin setting.
 * @details This function sets @b cs pin output to
 * @b state setting.
 * @param[in] ctx Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] state Output value setting.
 *         @li @c  0 - digital out high,
 *         @li @c  1 - digital out low.
 */
void nbiot5_set_cs ( nbiot5_t *ctx, uint8_t state );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 * 
 * @note Example of cmd -> "AT+CFUN=1".
 */
void nbiot5_send_cmd ( nbiot5_t *ctx, char *cmd );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 *
 * @return Nothing.
 * 
 * @note Example of sim_apn -> "vip.mobile".
 */
void nbiot5_set_sim_apn ( nbiot5_t *ctx, char *sim_apn );

/**
 * @brief NB IoT 5 send text message.
 * @details This function sends text message to a phone number.
 * @param[in] ctx : Click context object.
 * See #nbiot5_t object definition for detailed explanation.
 * @param[in] phone_number  Phone number to message.
 * @param[in] message_context  Message to be sent.
 *
 * @return Nothing.
 */
void nbiot5_send_text_message ( nbiot5_t *ctx, char *phone_number, char *message_context );

#ifdef __cplusplus
}
#endif
#endif // NBIOT5_H

/*! @} */ // nbiot5

// ------------------------------------------------------------------------ END
