/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for wifiesp Click driver.
 *
 * \addtogroup wifiesp wifiesp Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef WIFIESP_H
#define WIFIESP_H

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
#include "log.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define WIFIESP_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define WIFIESP_DRV_RX_BUFFER_SIZE          610
#define WIFIESP_DRV_TX_BUFFER_SIZE          150
/** \} */

/**
 * \defgroup commands AT commands 
 * \{
 */
#define WIFIESP_CHECK                       "AT"
#define WIFIESP_RESTORE                     "AT+RESTORE"
#define WIFIESP_RST                         "AT+RST"
#define WIFIESP_CHECK_FIRMWARE              "AT+GMR"
#define WIFIESP_SET_MODE                    "AT+CWMODE"
#define WIFIESP_CONNECT                     "AT+CWJAP"
#define WIFIESP_LIST_AP                     "AT+CWLAP"
#define WIFIESP_QUIT_AP                     "AT+CWQAP"
#define WIFIESP_SET_AP_PARAMETERS           "AT+CWSAP"
#define WIFIESP_JOIN_DEV_IP                 "AT+CWLIF"
#define WIFIESP_CONNESTION_STATUS           "AT+CIPSTATUS"
#define WIFIESP_START                       "AT+CIPSTART"
#define WIFIESP_MODE                        "AT+CIPMODE"
#define WIFIESP_SEND                        "AT+CIPSEND"
#define WIFIESP_CLOSE                       "AT+CIPCLOSE"
#define WIFIESP_GET_IP                      "AT+CIFSR"
#define WIFIESP_SET_MULTIPLE_CONNECTION     "AT+CIPMUX"
#define WIFIESP_SET_AS_SERVER               "AT+CIPSERVER"
#define WIFIESP_CHECK_SERVER_TIMEOUT        "AT+CIPSTO?"
#define WIFIESP_RECEIVE                     "+IPD"
/** \} */

/**
 * \defgroup response Response to AT commands 
 * \{
 */
#define WIFIESP_RSP_OK                      "OK"
#define WIFIESP_RSP_READY_FOR_SEND          ">"
#define WIFIESP_RSP_SEND_OK                 "SEND OK"
#define WIFIESP_RSP_ERROR                   "ERROR"
#define WIFIESP_RSP_CONNECT                 "CONNECT"
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 
    digital_out_t rst;
    digital_out_t cs;

    // Modules 
    uart_t uart;

    char uart_rx_buffer[ WIFIESP_DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ WIFIESP_DRV_TX_BUFFER_SIZE ];

} wifiesp_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 
    pin_name_t rst;
    pin_name_t cs;

    // static variable 
    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits. 
    
} wifiesp_cfg_t;

/**
 * @brief WiFi ESP Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WIFIESP_OK = 0,
    WIFIESP_ERROR = -1,
    WIFIESP_ERROR_TIMEOUT = -2,
    WIFIESP_ERROR_CMD = -3,
    WIFIESP_ERROR_UNKNOWN = -4

} wifiesp_return_value_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void wifiesp_cfg_setup ( wifiesp_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t wifiesp_init ( wifiesp_t *ctx, wifiesp_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx Click object.
 *
 * @details This function executes default configuration for wifiesp click.
 */
void wifiesp_default_cfg ( wifiesp_t *ctx );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void wifiesp_generic_write ( wifiesp_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t wifiesp_generic_read ( wifiesp_t *ctx, char *data_buf, int32_t max_len );

/**
 * @brief Sends AT command to the module.
 * @param ctx Click object.
 * @param cmd AT command
 * @param args AT command arguments string pointer (NULL if no arguments).
 * 
 * @details This function sends AT command to wifiesp click. 
 */
void wifiesp_send_cmd( wifiesp_t* ctx, uint8_t* cmd, uint8_t* args );

#ifdef __cplusplus
}
#endif
#endif  // _WIFIESP_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
