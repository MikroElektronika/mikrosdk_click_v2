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
 * @file xsensmti3.h
 * @brief This file contains API for XSENS MTi-3 Click Driver.
 */

#ifndef XSENSMTI3_H
#define XSENSMTI3_H

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
 * @addtogroup xsensmti3 XSENS MTi-3 Click Driver
 * @brief API for configuring and manipulating XSENS MTi-3 Click driver.
 * @{
 */

/**
 * @defgroup xsensmti3_cmd XSENS MTi-3 Device Settings
 * @brief Settings for registers of XSENS MTi-3 Click driver.
 */

/**
 * @addtogroup xsensmti3_cmd
 * @{
 */

/**
 * @brief XSENS MTi-3 control commands.
 * @details Specified setting for control commands of XSENS MTi-3 Click driver.
 */
#define XSENSMTI3_WAIT_FOR_START        0x00
#define XSENSMTI3_START_PROCESS         0x01
#define XSENSMTI3_DATA_PROCESSING       0x02
#define XSENSMTI3_PARSER_DATA           0x03

/**
 * @brief XSENS MTi-3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define XSENSMTI3_TX_DRV_BUFFER_SIZE    100
#define XSENSMTI3_RX_DRV_BUFFER_SIZE    1000

/*! @} */ // xsensmti3_cmd

/**
 * @defgroup xsensmti3_map XSENS MTi-3 MikroBUS Map
 * @brief MikroBUS pin mapping of XSENS MTi-3 Click driver.
 */

/**
 * @addtogroup xsensmti3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of XSENS MTi-3 Click to the selected MikroBUS.
 */
#define XSENSMTI3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.syn = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // xsensmti3_map
/*! @} */ // xsensmti3

/**
 * @brief XSENS MTi-3 Click context object.
 * @details Context object definition of XSENS MTi-3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t syn;      /**< Sync Interface. */
    digital_out_t rst;      /**< Reset. */
    digital_out_t cs;       /**< SPI Chip Select. */
    digital_out_t rts;      /**< UART TX CTRL Signal UART RTS. */

    // Input pins
    digital_in_t cts;       /**< Data Ready Output UART RX CTRL Signal UART CTS. */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ XSENSMTI3_RX_DRV_BUFFER_SIZE ]; /**< Buffer size. */
    uint8_t uart_tx_buffer[ XSENSMTI3_TX_DRV_BUFFER_SIZE ]; /**< Buffer size. */

} xsensmti3_t;

/**
 * @brief XSENS MTi-3 Click configuration object.
 * @details Configuration object definition of XSENS MTi-3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t syn;         /**< Sync Interface. */
    pin_name_t rst;         /**< Reset. */
    pin_name_t cs;          /**< SPI Chip Select. */
    pin_name_t rts;         /**< UART TX CTRL Signal UART RTS. */
    pin_name_t cts;         /**< Data Ready Output UART RX CTRL Signal UART CTS. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} xsensmti3_cfg_t;

/**
 * @brief Click quat structure definition.
 */
typedef struct
{
    uint16_t data_id;
    uint32_t raw_data[ 4 ];
    float    quat_data[ 4 ];

} xsensmti3_quat_t;

/**
 * @brief Click 32-bit data structure definition.
 */
typedef struct
{
    uint16_t data_id;
    uint32_t out_data;

} xsensmti3_u32_data_t;

/**
 * @brief Click 16-bit data structure definition.
 */
typedef struct
{
    uint16_t data_id;
    uint16_t out_data;

} xsensmti3_u16_data_t;

/**
 * @brief Click parse structure definition.
 */
typedef struct
{
    uint32_t                package_header;
    xsensmti3_quat_t        quat_obj;
    xsensmti3_u32_data_t    time_obj;
    xsensmti3_u32_data_t    status_obj;
    xsensmti3_u16_data_t    package_obj;
    uint8_t                 crc_data;

} xsensmti3_parse_t;

/**
 * @brief Click roll/pitch/yaw structure definition.
 */
typedef struct
{
    float roll;
    float pitch;
    float yaw;

} xsensmti3_data_t;

/**
 * @brief XSENS MTi-3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    XSENSMTI3_OK = 0,
    XSENSMTI3_ERROR = -1

} xsensmti3_return_value_t;

/*!
 * @addtogroup xsensmti3 XSENS MTi-3 Click Driver
 * @brief API for configuring and manipulating XSENS MTi-3 Click driver.
 * @{
 */

/**
 * @brief XSENS MTi-3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #xsensmti3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void xsensmti3_cfg_setup ( xsensmti3_cfg_t *cfg );

/**
 * @brief XSENS MTi-3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #xsensmti3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #xsensmti3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xsensmti3_init ( xsensmti3_t *ctx, xsensmti3_cfg_t *cfg );

/**
 * @brief XSENS MTi-3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xsensmti3_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xsensmti3_generic_write ( xsensmti3_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief XSENS MTi-3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #xsensmti3_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t xsensmti3_generic_read ( xsensmti3_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief XSENS MTi-3 general parser.
 * @details This function parses object for collecting data.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] start_cnt : Element from which the package starts.
 * @param[out] obj : Parse object for collecting data.
 * @return Nothing.
 */
void xsensmti3_parser ( uint8_t *rsp_buf, uint8_t start_cnt, xsensmti3_parse_t *obj );

/**
 * @brief XSENS MTi-3 get Roll, Pitch and Yaw.
 * @details This function get roll, pitch and yaw values.
 * @param[in] quat_obj : Quat objest structure.
 * @param[out] data_obj : Output object for collecting data.
 * @return Nothing.
 */
void xsensmti3_get_data( xsensmti3_quat_t *quat_obj, xsensmti3_data_t *data_obj );

/**
 * @brief XSENS MTi-3 checks package.
 * @details This function check for the starting elements.
 * @param[in] package_buf : Package buffer.
 * @param[in] start_package : Element from which the package starts.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t xsensmti3_check_package( uint8_t *package_buf, uint8_t *start_package );

#ifdef __cplusplus
}
#endif
#endif // XSENSMTI3_H

/*! @} */ // xsensmti3

// ------------------------------------------------------------------------ END
