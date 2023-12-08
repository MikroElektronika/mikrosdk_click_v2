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
 * @file speakup3.h
 * @brief This file contains API for SpeakUp 3 Click Driver.
 */

#ifndef SPEAKUP3_H
#define SPEAKUP3_H

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
 * @addtogroup speakup3 SpeakUp 3 Click Driver
 * @brief API for configuring and manipulating SpeakUp 3 Click driver.
 * @{
 */

/**
 * @defgroup speakup3_cmd SpeakUp 3 Device Settings
 * @brief Settings for registers of SpeakUp 3 Click driver.
 */

/**
 * @addtogroup speakup3_cmd
 * @{
 */

/**
 * @brief SpeakUp 3 command codes.
 * @details Specified setting for command codes of SpeakUp 3 Click driver.
 */
#define SPEAKUP3_START_BYTE                 0x5A
#define SPEAKUP3_INS_ENTER_WAKE_UP          0x00 // Voice CMD: hey pudding / hello pudding
#define SPEAKUP3_INS_EXIT_WAKE_UP           0x01 // Voice CMD: goodbye / see you
#define SPEAKUP3_INS_LEARN_MATCH_AC         0x02 // Voice CMD: match the air conditioner
#define SPEAKUP3_INS_AC_TURN_ON             0x03 // Voice CMD: turn on the air conditioner
#define SPEAKUP3_INS_AC_TURN_OFF            0x04 // Voice CMD: turn off the air conditioner
#define SPEAKUP3_INS_AC_MODE_AUTO           0x05 // Voice CMD: automatic mode
#define SPEAKUP3_INS_AC_MODE_COLD           0x06 // Voice CMD: cold mode
#define SPEAKUP3_INS_AC_MODE_HEAT           0x07 // Voice CMD: heat mode
#define SPEAKUP3_INS_AC_MODE_DRY            0x08 // Voice CMD: dry mode
#define SPEAKUP3_INS_AC_MODE_FAN            0x09 // Voice CMD: fan mode
#define SPEAKUP3_INS_AC_MODE_SLEEP          0x0A // Voice CMD: sleeping mode
#define SPEAKUP3_INS_AC_WIND_AUTO           0x0B // Voice CMD: automatic fan
#define SPEAKUP3_INS_AC_WIND_LOW            0x0C // Voice CMD: low fan
#define SPEAKUP3_INS_AC_WIND_MID            0x0D // Voice CMD: medium fan
#define SPEAKUP3_INS_AC_WIND_HIGH           0x0E // Voice CMD: high fan
#define SPEAKUP3_INS_AC_WIND_INC            0x0F // Voice CMD: higher the fan
#define SPEAKUP3_INS_AC_WIND_DEC            0x10 // Voice CMD: lower the fan
#define SPEAKUP3_INS_AC_TMP_16              0x11 // Voice CMD: sixteen centigrade
#define SPEAKUP3_INS_AC_TMP_17              0x12 // Voice CMD: seventeen centigrade
#define SPEAKUP3_INS_AC_TMP_18              0x13 // Voice CMD: eighteen centigrade
#define SPEAKUP3_INS_AC_TMP_19              0x14 // Voice CMD: nineteen centigrade
#define SPEAKUP3_INS_AC_TMP_20              0x15 // Voice CMD: twenty centigrade
#define SPEAKUP3_INS_AC_TMP_21              0x16 // Voice CMD: twenty one centigrade
#define SPEAKUP3_INS_AC_TMP_22              0x17 // Voice CMD: twenty two centigrade
#define SPEAKUP3_INS_AC_TMP_23              0x18 // Voice CMD: twenty three centigrade
#define SPEAKUP3_INS_AC_TMP_24              0x19 // Voice CMD: twenty four centigrade
#define SPEAKUP3_INS_AC_TMP_25              0x1A // Voice CMD: twenty five centigrade
#define SPEAKUP3_INS_AC_TMP_26              0x1B // Voice CMD: twenty six centigrade
#define SPEAKUP3_INS_AC_TMP_27              0x1C // Voice CMD: twenty seven centigrade
#define SPEAKUP3_INS_AC_TMP_28              0x1D // Voice CMD: twenty eight centigrade
#define SPEAKUP3_INS_AC_TMP_29              0x1E // Voice CMD: twenty nine centigrade
#define SPEAKUP3_INS_AC_TMP_30              0x1F // Voice CMD: thirty centigrade
#define SPEAKUP3_INS_AC_TMP_INC             0x20 // Voice CMD: warmer
#define SPEAKUP3_INS_AC_TMP_DEC             0x21 // Voice CMD: cooler
#define SPEAKUP3_INS_AC_SWEPT_ON            0x22 // Voice CMD: start to fan
#define SPEAKUP3_INS_AC_SWEPT_OFF           0x23 // Voice CMD: stop to fan
#define SPEAKUP3_INS_AC_SWEPT_VERT          0x24 // Voice CMD: air swing up and down
#define SPEAKUP3_INS_AC_SWEPT_CROSS         0x25 // Voice CMD: air swing left and right
#define SPEAKUP3_INS_SET_RESTORE            0x26 // Voice CMD: air conditioner reset
#define SPEAKUP3_RESERVED_BYTE_1            0x00
#define SPEAKUP3_RESERVED_BYTE_2            0x00

/**
 * @brief SpeakUp 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define TX_DRV_BUFFER_SIZE                  100
#define RX_DRV_BUFFER_SIZE                  200

/*! @} */ // speakup3_cmd

/**
 * @defgroup speakup3_map SpeakUp 3 MikroBUS Map
 * @brief MikroBUS pin mapping of SpeakUp 3 Click driver.
 */

/**
 * @addtogroup speakup3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SpeakUp 3 Click to the selected MikroBUS.
 */
#define SPEAKUP3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX );

/*! @} */ // speakup3_map
/*! @} */ // speakup3

/**
 * @brief SpeakUp 3 Click context object.
 * @details Context object definition of SpeakUp 3 Click driver.
 */
typedef struct
{
    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} speakup3_t;

/**
 * @brief SpeakUp 3 Click configuration object.
 * @details Configuration object definition of SpeakUp 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} speakup3_cfg_t;

/**
 * @brief SpeakUp 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SPEAKUP3_OK = 0,
    SPEAKUP3_ERROR = -1

} speakup3_return_value_t;

/*!
 * @addtogroup speakup3 SpeakUp 3 Click Driver
 * @brief API for configuring and manipulating SpeakUp 3 Click driver.
 * @{
 */

/**
 * @brief SpeakUp 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #speakup3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void speakup3_cfg_setup ( speakup3_cfg_t *cfg );

/**
 * @brief SpeakUp 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #speakup3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #speakup3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speakup3_init ( speakup3_t *ctx, speakup3_cfg_t *cfg );

/**
 * @brief SpeakUp 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #speakup3_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speakup3_generic_write ( speakup3_t *ctx, char *data_in, uint16_t len );

/**
 * @brief SpeakUp 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #speakup3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speakup3_generic_read ( speakup3_t *ctx, char *data_out, uint16_t len );

/**
 * @brief SpeakUp 3 wait for reply function.
 * @details This function waits up to @b wait_ms for a reply to the voice command.
 * @param[in] ctx : Click context object.
 * See #speakup3_t object definition for detailed explanation.
 * @param[out] reply_ins : Reply instruction code.
 * @param[in] wait_ms : Wait period in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speakup3_wait_for_reply ( speakup3_t *ctx, uint8_t *reply_ins, uint32_t wait_ms );

#ifdef __cplusplus
}
#endif
#endif // SPEAKUP3_H

/*! @} */ // speakup3

// ------------------------------------------------------------------------ END
