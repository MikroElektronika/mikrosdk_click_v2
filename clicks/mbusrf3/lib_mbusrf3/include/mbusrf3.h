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
 * @file mbusrf3.h
 * @brief This file contains API for M-BUS RF 3 Click Driver.
 */

#ifndef MBUSRF3_H
#define MBUSRF3_H

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
 * @addtogroup mbusrf3 M-BUS RF 3 Click Driver
 * @brief API for configuring and manipulating M-BUS RF 3 Click driver.
 * @{
 */

/**
 * @defgroup mbusrf3_cmd M-BUS RF 3 Device Settings
 * @brief Settings for registers of M-BUS RF 3 Click driver.
 */

/**
 * @addtogroup mbusrf3_cmd
 * @{
 */

/**
 * @brief M-BUS RF 3 control commands.
 * @details Specified setting for control commands of M-BUS RF 3 Click driver.
 */
#define MBUSRF3_CMD_SFD                         0xFF
#define MBUSRF3_CMD_DATA_REQ                    0x00
#define MBUSRF3_CMD_DATA_IND                    0x03
#define MBUSRF3_CMD_SET_MODE_REQ                0x04
#define MBUSRF3_CMD_RESET_REQ                   0x05
#define MBUSRF3_CMD_SET_REQ                     0x09
#define MBUSRF3_CMD_SETUARTSPEED_REQ            0x10
#define MBUSRF3_CMD_FACTORYRESET_REQ            0x11
#define MBUSRF3_CMD_GET_REQ                     0x0A
#define MBUSRF3_CMD_SERIALNO_REQ                0x0B
#define MBUSRF3_CMD_FWV_REQ                     0x0C
#define MBUSRF3_CMD_RSSI_REQ                    0x0D
#define MBUSRF3_CMD_SET_AES_KEY_REQ             0x50
#define MBUSRF3_CMD_CLR_AES_KEY_REQ             0x51
#define MBUSRF3_CMD_GET_AES_KEY_REQ             0x52
#define MBUSRF3_CMD_RESPONSE                    0x80

/**
 * @brief M-BUS RF 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define MBUSRF3_TX_DRV_BUFFER_SIZE              100
#define MBUSRF3_RX_DRV_BUFFER_SIZE              300

/*! @} */ // mbusrf3_cmd

/**
 * @defgroup mbusrf3_map M-BUS RF 3 MikroBUS Map
 * @brief MikroBUS pin mapping of M-BUS RF 3 Click driver.
 */

/**
 * @addtogroup mbusrf3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of M-BUS RF 3 Click to the selected MikroBUS.
 */
#define MBUSRF3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // mbusrf3_map
/*! @} */ // mbusrf3

/**
 * @brief M-BUS RF 3 Click context object.
 * @details Context object definition of M-BUS RF 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Reset pin. */

    // Input pins
    digital_in_t rts;                           /**< Ready to send pin. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ MBUSRF3_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ MBUSRF3_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} mbusrf3_t;

/**
 * @brief M-BUS RF 3 Click configuration object.
 * @details Configuration object definition of M-BUS RF 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                             /**< Reset pin. */
    pin_name_t rts;                             /**< Ready to send pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} mbusrf3_cfg_t;

/**
 * @brief M-BUS RF 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MBUSRF3_OK = 0,
    MBUSRF3_ERROR = -1,
    MBUSRF3_ERROR_TIMEOUT = -2

} mbusrf3_return_value_t;

/*!
 * @addtogroup mbusrf3 M-BUS RF 3 Click Driver
 * @brief API for configuring and manipulating M-BUS RF 3 Click driver.
 * @{
 */

/**
 * @brief M-BUS RF 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mbusrf3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mbusrf3_cfg_setup ( mbusrf3_cfg_t *cfg );

/**
 * @brief M-BUS RF 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #mbusrf3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mbusrf3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mbusrf3_init ( mbusrf3_t *ctx, mbusrf3_cfg_t *cfg );

/**
 * @brief M-BUS RF 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mbusrf3_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mbusrf3_generic_write ( mbusrf3_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief M-BUS RF 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #mbusrf3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mbusrf3_generic_read ( mbusrf3_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief M-BUS RF 3 set reset pin function.
 * @details This function is used to set reset pin state.
 * @param[in] ctx : Click context object.
 * See #mbusrf3_t object definition for detailed explanation.
 * @param[in] pin_state : Desired pin state.
 * @return Nothing.
 * @note None.
 */
void mbusrf3_set_rst_pin ( mbusrf3_t *ctx, uint8_t pin_state );

/**
 * @brief M-BUS RF 3 send command function.
 * @details This function is used to send a desired command.
 * @param[in] ctx : Click context object.
 * See #mbusrf3_t object definition for detailed explanation.
 * @param[in] cmd : Command value.
 * @param[in] data_in : Command string value.
 * @param[in] len : Command string length.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mbusrf3_send_command ( mbusrf3_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len );

/**
 * @brief M-BUS RF 3 send data function.
 * @details This function is used to data in transmitter mode.
 * @param[in] ctx : Click context object.
 * See #mbusrf3_t object definition for detailed explanation.
 * @param[in] data_in : Data to be sent.
 * @param[in] len : Data length.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mbusrf3_send_data ( mbusrf3_t *ctx, uint8_t *data_in, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif // MBUSRF3_H

/*! @} */ // mbusrf3

// ------------------------------------------------------------------------ END
