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
 * @file lteiot4.h
 * @brief This file contains API for LTE IoT 4 Click Driver.
 */

#ifndef LTEIOT4_H
#define LTEIOT4_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup lteiot4 LTE IoT 4 Click Driver
 * @brief API for configuring and manipulating LTE IoT 4 Click driver.
 * @{
 */

/**
 * @defgroup lteiot4_set LTE IoT 4 Device Settings
 * @brief Settings for registers of LTE IoT 4 Click driver.
 */

/**
 * @addtogroup lteiot4_set
 * @{
 */

/**
 * @brief LTE IoT 4 description setting.
 * @details Specified setting for description of LTE IoT 4 Click driver.
 */
#define LTEIOT4_CMD_AT                  "AT"
#define LTEIOT4_CMD_MODULE_VERSION      "AT+CGMM"
#define LTEIOT4_CMD_FW_VERSION          "AT+CGMR"
#define LTEIOT4_CMD_FLIGHT_MODE         "AT+CFUN=4"
#define LTEIOT4_CMD_NBIOT_MODE          "AT%XSYSTEMMODE=0,1,0,0"
#define LTEIOT4_CMD_ENABLE_NET_SMS      "AT+CIND=1,0,1"
#define LTEIOT4_CMD_FULL_FUNCTION       "AT+CFUN=1"
#define LTEIOT4_CMD_AUTO_NET_SRC        "AT+COPS=0"
#define LTEIOT4_CMD_SEARCH_NET          "AT+CEREG=2"
#define LTEIOT4_CMD_SIM_TEST            "AT+CIMI"
#define LTEIOT4_CMD_CHECK_CONNECTION    "AT+CGATT?"
#define LTEIOT4_CMD_CHECK_REGISTARTION  "AT+CEREG?"
#define LTEIOT4_CMD_SIGNAL_QUALITY      "AT+CESQ"
#define LTEIOT4_CMD_SET_DUMMY_CLOCK     "AT+CCLK=\"20/12/31,23:59:39+01\""
#define LTEIOT4_CMD_CHECK_TEMPERATURE   "AT%XTEMP?"
#define LTEIOT4_CMD_CHECK_CLOCK         "AT+CCLK?"

/**
 * @brief LTE IoT 4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       500

/*! @} */ // lteiot4_set

/**
 * @defgroup lteiot4_map LTE IoT 4 MikroBUS Map
 * @brief MikroBUS pin mapping of LTE IoT 4 Click driver.
 */

/**
 * @addtogroup lteiot4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LTE IoT 4 Click to the selected MikroBUS.
 */
#define LTEIOT4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \

/*! @} */ // lteiot4_map
/*! @} */ // lteiot4

/**
 * @brief LTE IoT 4 Click context object.
 * @details Context object definition of LTE IoT 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;     /**< Description. */
   
    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */

} lteiot4_t;

/**
 * @brief LTE IoT 4 Click configuration object.
 * @details Configuration object definition of LTE IoT 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;        /**< Description. */

    // Static variable

    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} lteiot4_cfg_t;

/*!
 * @addtogroup lteiot4 LTE IoT 4 Click Driver
 * @brief API for configuring and manipulating LTE IoT 4 Click driver.
 * @{
 */

/**
 * @brief LTE IoT 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #lteiot4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void lteiot4_cfg_setup ( lteiot4_cfg_t *cfg );

/**
 * @brief LTE IoT 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #lteiot4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #lteiot4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot4_init ( lteiot4_t *ctx, lteiot4_cfg_t *cfg );

/**
 * @brief LTE IoT 4 default configuration function.
 * @details This function executes a default configuration of LTE IoT 4
 * click board.
 * @param[in] ctx : Click context object.
 * See #lteiot4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t lteiot4_default_cfg ( lteiot4_t *ctx );

/**
 * @brief LTE IoT 4 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot4_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot4_generic_write ( lteiot4_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief LTE IoT 4 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #lteiot4_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t lteiot4_generic_read ( lteiot4_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Sets state of the @b rst pin setting.
 * @details This function sets @b rst pin output to
 * @b state setting.
 * @param[in] ctx Click context object.
 * See #lteiot4_t object definition for detailed explanation.
 * @param[in] state Output value setting.
 *         @li @c  0 - digital out high,
 *         @li @c  1 - digital out low.
 */
void lteiot4_set_rst ( lteiot4_t *ctx, uint8_t state );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #lteiot4_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 * 
 * @note Example of cmd -> "AT+CFUN=1".
 */
void lteiot4_send_cmd ( lteiot4_t *ctx, char *cmd );

/**
 * @brief Set sim card APN.
 * @details This function sets APN for sim card.
 * @param[in] ctx : Click context object.
 * See #lteiot4_t object definition for detailed explanation.
 * @param[in] sim_apn  SIM card APN.
 *
 * @return Nothing.
 * 
 * @note Example of sim_apn -> "vip.mobile".
 */
void lteiot4_set_sim_apn ( lteiot4_t *ctx, char *sim_apn );

#ifdef __cplusplus
}
#endif
#endif // LTEIOT4_H

/*! @} */ // lteiot4

// ------------------------------------------------------------------------ END
