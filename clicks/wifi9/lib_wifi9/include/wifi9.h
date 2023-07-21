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
 * \brief This file contains API for Wifi 9 Click driver.
 *
 * \addtogroup wifi9 Wifi 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef WIFI9_H
#define WIFI9_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define WIFI9_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.adr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.mcr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define WIFI9_OK                            0
#define WIFI9_ERROR                        -1
#define WIFI9_ERROR_TIMEOUT                -2
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define WIFI9_MODULE_POWER_ON               1
#define WIFI9_MODULE_POWER_OFF              0
/** \} */

/**
 * \defgroup uart_sel UART Selection
 * \{
 */
#define WIFI9_SELECT_CMD_UART               0
#define WIFI9_SELECT_BIN_UART               1
/** \} */

/**
 * \defgroup wifi_cmd Wifi9 Commands
 * \{
 */
#define WIFI9_CMD_GET_SYSTEM_FIRMWARE       "get system firmware"
#define WIFI9_CMD_GET_SYSTEM_MAC_ADDR       "get system macaddr"
#define WIFI9_CMD_GET_SYSTEM_SERIAL_NUM     "get system serialnum"
#define WIFI9_CMD_GET_SYSTEM_RADIO_VER      "get system radio_ver"
#define WIFI9_CMD_GET_SYSTEM_BOOTL_VER      "get system bootl_ver"
#define WIFI9_CMD_GET_SYSTEM_HW_REV         "get system hwrev"
#define WIFI9_CMD_GET_WLAN_STATE            "get wlan state"
#define WIFI9_CMD_GET_WLAN_STATE_STA        "get wlan state sta"
#define WIFI9_CMD_SET_WLAN_STATE            "set wlan state"
#define WIFI9_CMD_SET_WLAN_STATE_STA_ON     "set wlan state sta on"
#define WIFI9_CMD_SET_WLAN_CFG              "set wlan cfg"
#define WIFI9_CMD_SET_WLAN_CFG_STA          "set wlan cfg sta"
#define WIFI9_CMD_SET_NETCAT_STATE          "set netcat state"
#define WIFI9_CMD_SET_NETCAT_STATE_OFF      "set netcat state off"
#define WIFI9_CMD_SET_NETCAT_STATE_ON       "set netcat state on"
#define WIFI9_CMD_SET_NETCAT_CFG            "set netcat cfg"
#define WIFI9_CMD_SET_NETCAT_CFG_SERVER     "set netcat cfg server"
#define WIFI9_CMD_SET_NETCAT_AUTH           "set netcat auth"
#define WIFI9_CMD_SET_NETCAT_AUTH_OFF       "set netcat auth off"
#define WIFI9_CMD_GET_NET_CFG               "get net cfg"
#define WIFI9_CMD_GET_NET_CFG_STA           "get net cfg sta"
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define WIFI9_DRV_TX_BUFFER_SIZE            300
#define WIFI9_DRV_RX_BUFFER_SIZE            500
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
    digital_out_t adr;
    digital_out_t rst;
    digital_out_t rts;

    // Input pins 
    digital_in_t mcr;
    digital_in_t cts;
    
    // Modules 
    uart_t uart;

    uint8_t uart_rx_buffer[ WIFI9_DRV_RX_BUFFER_SIZE ];
    uint8_t uart_tx_buffer[ WIFI9_DRV_TX_BUFFER_SIZE ];

} wifi9_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 
    pin_name_t adr;
    pin_name_t rst;
    pin_name_t rts;
    pin_name_t mcr;
    pin_name_t cts;

    // static variable 
    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} wifi9_cfg_t;

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
void wifi9_cfg_setup ( wifi9_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t wifi9_init ( wifi9_t *ctx, wifi9_cfg_t *cfg );

/**
 * @brief Module reset.
 * @param ctx Click object.
 */
void wifi9_reset_device ( wifi9_t *ctx );

/**
 * @brief Set RST pin state
 * @param ctx  Click object.
 * @param state  Pin state
 */
void wifi9_set_rst_pin ( wifi9_t *ctx, uint8_t state );

/**
 * @brief Set RTS pin state
 * @param ctx  Click object.
 * @param state  Pin state
 */
void wifi9_set_rts_pin ( wifi9_t *ctx, uint8_t state );

/**
 * @brief Switch to a command or binary uart
 * @param ctx  Click object.
 * @param uart_select  CMD_UART or BIN_UART
 */
void wifi9_select_uart ( wifi9_t *ctx, uint8_t uart_select );

/**
 * @brief Get MCR pin state
 * @param ctx  Click object.
 * @return Pin state
 */
uint8_t wifi9_get_mcr_pin ( wifi9_t *ctx );

/**
 * @brief Get CTS pin state
 * @param ctx  Click object.
 * @return Pin state
 */
uint8_t wifi9_get_cts_pin ( wifi9_t *ctx );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void wifi9_generic_write ( wifi9_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t wifi9_generic_read ( wifi9_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief Send Command function.
 * @param ctx  Click object.
 * @param command  Command.
 * @details This function sends comamnd.
 */
void wifi9_send_command ( wifi9_t *ctx, uint8_t *command );

#ifdef __cplusplus
}
#endif
#endif  // _WIFI9_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
