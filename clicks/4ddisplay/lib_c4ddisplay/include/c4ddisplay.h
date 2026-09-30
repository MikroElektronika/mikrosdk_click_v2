/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file c4ddisplay.h
 * @brief This file contains API for 4D - display Click Driver.
 */

#ifndef C4DDISPLAY_H
#define C4DDISPLAY_H

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
#include "drv_uart.h"

/*!
 * @addtogroup c4ddisplay 4D - display Click Driver
 * @brief API for configuring and manipulating 4D - display Click driver.
 * @{
 */

/**
 * @defgroup c4ddisplay_cmd 4D - display Device Settings
 * @brief Settings of 4D - display Click driver.
 * @{
 */

/**
 * @brief 4D - display Click ViSi-Genie commands.
 * @details These macros define standard object commands and display replies.
 * @note Object reports contain six bytes; ACK and NAK contain one byte.
 */
#define C4DDISPLAY_CMD_READ_OBJ          0x00
#define C4DDISPLAY_CMD_WRITE_OBJ         0x01
#define C4DDISPLAY_CMD_WRITE_CONTRAST    0x04
#define C4DDISPLAY_CMD_REPORT_OBJ        0x05
#define C4DDISPLAY_REPLY_ACK             0x06
#define C4DDISPLAY_CMD_REPORT_EVENT      0x07
#define C4DDISPLAY_REPLY_NAK             0x15

/**
 * @brief 4D - display Click ViSi-Genie object types.
 * @details These macros select standard Workshop4 object types, independently of their instance indexes.
 * @note The selected object and index must exist in the programmed display project.
 * Winbutton (6) and 4Dbutton (30) are distinct Workshop4 controls.
 */
#define C4DDISPLAY_OBJ_DIPSWITCH         0
#define C4DDISPLAY_OBJ_KNOB              1
#define C4DDISPLAY_OBJ_ROCKER            2
#define C4DDISPLAY_OBJ_ROTARY            3
#define C4DDISPLAY_OBJ_SLIDER            4
#define C4DDISPLAY_OBJ_TRACKBAR          5
#define C4DDISPLAY_OBJ_WINBUTTON         6
#define C4DDISPLAY_OBJ_ANGULAR_METER     7
#define C4DDISPLAY_OBJ_COOL_GAUGE        8
#define C4DDISPLAY_OBJ_CUSTOM_DIGITS     9
#define C4DDISPLAY_OBJ_FORM              10
#define C4DDISPLAY_OBJ_GAUGE             11
#define C4DDISPLAY_OBJ_IMAGE             12
#define C4DDISPLAY_OBJ_KEYBOARD          13
#define C4DDISPLAY_OBJ_LED               14
#define C4DDISPLAY_OBJ_LED_DIGITS        15
#define C4DDISPLAY_OBJ_METER             16
#define C4DDISPLAY_OBJ_STRINGS           17
#define C4DDISPLAY_OBJ_THERMOMETER       18
#define C4DDISPLAY_OBJ_USER_LED          19
#define C4DDISPLAY_OBJ_VIDEO             20
#define C4DDISPLAY_OBJ_STATIC_TEXT       21
#define C4DDISPLAY_OBJ_SOUND             22
#define C4DDISPLAY_OBJ_TIMER             23
#define C4DDISPLAY_OBJ_SPECTRUM          24
#define C4DDISPLAY_OBJ_SCOPE             25
#define C4DDISPLAY_OBJ_TANK              26
#define C4DDISPLAY_OBJ_BUTTON            30

/**
 * @brief 4D - display Click UART and buffer settings.
 * @details These macros define the demo baud rate, driver buffers, and pending touch-event capacity.
 * @note The UART baud rate must match the Workshop4 project.
 */
#define C4DDISPLAY_BAUD_RATE             115200
#define C4DDISPLAY_TX_DRV_BUFFER_SIZE    100
#define C4DDISPLAY_RX_DRV_BUFFER_SIZE    300
#define C4DDISPLAY_FRAME_SIZE            6
#define C4DDISPLAY_EVENT_COUNT           8

/**
 * @brief 4D - display Click communication limits.
 * @details These macros bound reply polling and select the maximum display brightness.
 * @note Waits use fixed one-millisecond polling delays; rendering can delay an ACK.
 */
#define C4DDISPLAY_REPLY_TIMEOUT         1000
#define C4DDISPLAY_FRAME_TIMEOUT         100
#define C4DDISPLAY_CONTRAST_MAX          15

/*! @} */ // c4ddisplay_cmd

/**
 * @defgroup c4ddisplay_map 4D - display MikroBUS Map
 * @brief MikroBUS pin mapping of 4D - display Click driver.
 * @{
 */

/**
 * @brief 4D - display Click MikroBUS pin mapping.
 * @details This macro maps the UART and display reset to the selected MikroBUS.
 * @note The display reset input is active low.
 */
#define C4DDISPLAY_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // c4ddisplay_map
/*! @} */ // c4ddisplay

/**
 * @brief 4D - display Click event object.
 * @details This structure identifies an object changed by a display touch event.
 */
typedef struct
{
    uint8_t object;                  /**< ViSi-Genie object type. */
    uint8_t index;                   /**< Zero-based object instance. */
    uint16_t value;                  /**< Reported 16-bit object value. */

} c4ddisplay_event_t;

/**
 * @brief 4D - display Click context object.
 * @details This structure stores the UART, current reply, and events received during commands.
 */
typedef struct
{
    digital_out_t rst;               /**< Active-low display reset output. */
    uart_t uart;                     /**< UART driver object. */

    uint8_t uart_rx_buffer[ C4DDISPLAY_RX_DRV_BUFFER_SIZE ]; /**< UART receive ring. */
    uint8_t uart_tx_buffer[ C4DDISPLAY_TX_DRV_BUFFER_SIZE ]; /**< UART transmit ring. */
    uint8_t reply[ C4DDISPLAY_FRAME_SIZE ];                /**< Last complete protocol reply. */
    uint8_t events[ C4DDISPLAY_EVENT_COUNT ][ C4DDISPLAY_FRAME_SIZE ]; /**< Pending event frames. */
    uint8_t event_head;              /**< Next queued event to return. */
    uint8_t event_count;             /**< Number of queued events. */
    uint8_t synchronized;            /**< Cleared when reset is needed to discard a late reply. */

} c4ddisplay_t;

/**
 * @brief 4D - display Click configuration object.
 * @details This structure defines the reset pin and host UART settings.
 */
typedef struct
{
    pin_name_t rx_pin;               /**< Host UART RX pin. */
    pin_name_t tx_pin;               /**< Host UART TX pin. */
    pin_name_t rst;                  /**< Active-low display reset pin. */

    uint32_t baud_rate;              /**< Baud rate selected in Workshop4. */
    bool uart_blocking;              /**< Must be false for bounded protocol waits. */
    uart_data_bits_t data_bit;       /**< Eight data bits. */
    uart_parity_t parity_bit;        /**< No parity. */
    uart_stop_bits_t stop_bit;       /**< One stop bit. */

} c4ddisplay_cfg_t;

/**
 * @brief 4D - display Click return values.
 * @details These values distinguish empty event queues, UART faults, and protocol errors.
 */
typedef enum
{
    C4DDISPLAY_OK = 0,               /**< Operation completed. */
    C4DDISPLAY_NO_EVENT = 1,         /**< No event is currently available. */
    C4DDISPLAY_ERROR = -1,           /**< UART or pin initialization failure. */
    C4DDISPLAY_TIMEOUT = -2,         /**< Transmit or response wait expired. */
    C4DDISPLAY_ERROR_NAK = -3,       /**< Display rejected the command. */
    C4DDISPLAY_ERROR_CHECKSUM = -4,  /**< Report checksum is invalid. */
    C4DDISPLAY_ERROR_ARGUMENT = -5,  /**< Invalid configuration or argument. */
    C4DDISPLAY_ERROR_FRAME = -6,     /**< Unexpected reply or unsupported message. */
    C4DDISPLAY_ERROR_OVERFLOW = -7,  /**< Pending event queue is full. */
    C4DDISPLAY_ERROR_STATE = -8      /**< Reset is required before another command. */

} c4ddisplay_return_value_t;

/*!
 * @addtogroup c4ddisplay 4D - display Click Driver
 * @brief API for configuring and manipulating 4D - display Click driver.
 * @{
 */

/**
 * @brief 4D - display Click configuration object setup function.
 * @details This function initializes Click configuration structure to initial values.
 * @param[out] cfg : Click configuration structure.
 * See #c4ddisplay_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note All pins are unconnected; UART defaults to 115200 baud, 8N1, and nonblocking mode.
 */
void c4ddisplay_cfg_setup ( c4ddisplay_cfg_t *cfg );

/**
 * @brief 4D - display Click initialization function.
 * @details This function initializes the UART, reset pin, and protocol state.
 * @param[out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c4ddisplay_cfg_t object definition for detailed explanation.
 * @return @li @c 0 - Success,
 *         @li @c <0 - Error.
 * See #c4ddisplay_return_value_t definition for detailed explanation.
 * @note Call c4ddisplay_default_cfg after initialization to start the display.
 */
err_t c4ddisplay_init ( c4ddisplay_t *ctx, c4ddisplay_cfg_t *cfg );

/**
 * @brief 4D - display Click default configuration function.
 * @details This function resets the display and confirms communication by setting maximum brightness.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @return @li @c 0 - Display acknowledged the configuration,
 *         @li @c <0 - Error.
 * See #c4ddisplay_return_value_t definition for detailed explanation.
 * @note The display must already contain a ViSi-Genie project and its matching microSD resources.
 */
err_t c4ddisplay_default_cfg ( c4ddisplay_t *ctx );

/**
 * @brief 4D - display Click reset function.
 * @details This function pulses reset low for 100 ms and allows five seconds for the display to boot.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @return Nothing.
 * @note Reset discards pending commands and events. There is no ready signal on this Click board;
 * the boot wait allows time to load display graphics. A subsequent command must confirm readiness.
 */
void c4ddisplay_reset ( c4ddisplay_t *ctx );

/**
 * @brief 4D - display Click object writing function.
 * @details This function writes a 16-bit value to a display object and waits for acknowledgment.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @param[in] object : ViSi-Genie object type.
 * @param[in] index : Zero-based object instance.
 * @param[in] value : Value accepted by the object's Workshop4 configuration.
 * @return @li @c 0 - Display acknowledged the write,
 *         @li @c <0 - Error.
 * See #c4ddisplay_return_value_t definition for detailed explanation.
 * @note Commands are serialized. After a timeout or framing error, reset before issuing another.
 */
err_t c4ddisplay_write_object ( c4ddisplay_t *ctx, uint8_t object, uint8_t index, uint16_t value );

/**
 * @brief 4D - display Click object reading function.
 * @details This function requests an object value and validates the matching object report.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @param[in] object : ViSi-Genie object type.
 * @param[in] index : Zero-based object instance.
 * @param[out] value : Reported object value; unchanged on failure.
 * @return @li @c 0 - Matching report received,
 *         @li @c <0 - Error.
 * See #c4ddisplay_return_value_t definition for detailed explanation.
 * @note READ_OBJ returns REPORT_OBJ, not ACK. Unsolicited touch events are queued separately.
 */
err_t c4ddisplay_read_object ( c4ddisplay_t *ctx, uint8_t object, uint8_t index, uint16_t *value );

/**
 * @brief 4D - display Click brightness function.
 * @details This function sets display contrast or backlight brightness and waits for acknowledgment.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @param[in] value : Brightness from 0 to 15; zero turns the backlight off.
 * @return @li @c 0 - Display acknowledged the command,
 *         @li @c <0 - Error.
 * See #c4ddisplay_return_value_t definition for detailed explanation.
 * @note Supported brightness levels depend on the connected display model.
 */
err_t c4ddisplay_set_contrast ( c4ddisplay_t *ctx, uint8_t value );

/**
 * @brief 4D - display Click event reading function.
 * @details This function returns the oldest queued touch event or reads a new event from the UART.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @param[out] event : Received object event; unchanged when no event is available.
 * See #c4ddisplay_event_t object definition for detailed explanation.
 * @return @li @c 0 - Event received,
 *         @li @c 1 - No event available,
 *         @li @c <0 - Error.
 * See #c4ddisplay_return_value_t definition for detailed explanation.
 * @note Enable Report Event in Workshop4 to receive touch events. An incomplete frame may wait
 * up to C4DDISPLAY_FRAME_TIMEOUT. Standard reports do not require a host ACK.
 */
err_t c4ddisplay_read_event ( c4ddisplay_t *ctx, c4ddisplay_event_t *event );

/**
 * @brief 4D - display Click raw UART writing function.
 * @details This function writes a desired number of bytes by using the UART serial interface.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @param[in] data_in : Input byte buffer.
 * @param[in] len : Number of bytes to queue.
 * @return Number of bytes queued, or a negative UART error.
 * @note Raw access bypasses framing and invalidates protocol state; reset before object commands.
 */
err_t c4ddisplay_generic_write ( c4ddisplay_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief 4D - display Click raw UART reading function.
 * @details This function reads a desired number of bytes by using the UART serial interface.
 * @param[in,out] ctx : Click context object.
 * See #c4ddisplay_t object definition for detailed explanation.
 * @param[out] data_out : Output byte buffer.
 * @param[in] len : Maximum number of bytes to read.
 * @return Number of bytes read, or a negative UART result when empty or on error.
 * @note Raw access can consume replies; reset before returning to object commands.
 */
err_t c4ddisplay_generic_read ( c4ddisplay_t *ctx, uint8_t *data_out, uint16_t len );

#ifdef __cplusplus
}
#endif
#endif // C4DDISPLAY_H

/*! @} */ // c4ddisplay

// ------------------------------------------------------------------------ END
