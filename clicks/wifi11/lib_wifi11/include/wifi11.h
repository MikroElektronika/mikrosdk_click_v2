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
 * \brief This file contains API for WiFi 11 Click driver.
 *
 * \addtogroup wifi11 WiFi 11 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef WIFI11_H
#define WIFI11_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define WIFI11_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.en      = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.gp1     = MIKROBUS( mikrobus, MIKROBUS_INT ); \
  cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define WIFI11_RETVAL  uint8_t

#define WIFI11_OK           0x00
#define WIFI11_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup common_command Common command list 
 * \{
 */
#define WIFI11_CMD_AT          "AT"             // Test AT command ready
#define WIFI11_CMD_ATS         "ATS?"           // List all AT command
#define WIFI11_CMD_ATSR        "ATSR"           // Restart module
#define WIFI11_CMD_ATSV        "ATSV"           // Query version info
#define WIFI11_CMD_ATSP        "ATSP"           // Set power saving mode
#define WIFI11_CMD_ATSE        "ATSE"           // Set AT command echo mode
#define WIFI11_CMD_ATSY        "ATSY"           // Factory Reset
#define WIFI11_CMD_ATSU        "ATSU"           // UART configuration
#define WIFI11_CMD_ATSW        "ATSW"           // Start Webserver
#define WIFI11_CMD_ATSO        "ATSO"           // OTA upgrade
#define WIFI11_CMD_ATSC        "ATSC"           // Choose Activated Image
#define WIFI11_CMD_ATSG        "ATSG"           // GPIO control
/** \} */

/**
 * \defgroup wifi_command WiFi command list 
 * \{
 */
#define WIFI11_CMD_ATPW        "ATPW"           // Set WiFi mode
#define WIFI11_CMD_ATPN        "ATPN"           // Connect to AP (STA mode)
#define WIFI11_CMD_ATWD        "ATWD"           // Disconnect from AP
#define WIFI11_CMD_ATWS        "ATWS"           // Scan AP
#define WIFI11_CMD_ATPA        "ATPA"           // Set AP mode
#define WIFI11_CMD_ATW         "ATW?"           // Wifi information
#define WIFI11_CMD_ATPH        "ATPH"           // Set DHCP mode
#define WIFI11_CMD_ATPE        "ATPE"           // Set static IP for STA
#define WIFI11_CMD_ATPF        "ATPF"           // Set static IP for AP, and DHCP rule
#define WIFI11_CMD_ATPG        "ATPG"           // Set Auto connect
#define WIFI11_CMD_ATPM        "ATPM"           // Set MAC address
#define WIFI11_CMD_ATWQ        "ATWQ"           // Start simple config
/** \} */

/**
 * \defgroup tcp_ip_command TCP/IP command list 
 * \{
 */
#define WIFI11_CMD_ATP0        "ATP0"           // Get LWIP errno
#define WIFI11_CMD_ATPS        "ATPS"           // Create TCP/UDP Server
#define WIFI11_CMD_ATPC        "ATPC"           // Create TCP/UDP Client
#define WIFI11_CMD_ATPD        "ATPD"           // Close TCP or UDP connection
#define WIFI11_CMD_ATPT        "ATPT"           // Send data
#define WIFI11_CMD_ATPR        "ATPR"           // Receive data
#define WIFI11_CMD_ATPK        "ATPK"           // Set auto receive data mode
#define WIFI11_CMD_ATPI        "ATPI"           // Check network connection status
#define WIFI11_CMD_ATPP        "ATPP"           // PING Command
#define WIFI11_CMD_ATPU        "ATPU"           // Set transparent transmission mode
#define WIFI11_CMD_ATPL        "ATPL"           // Save translink and enable autolink
/** \} */

/**
 * \defgroup tcp_udp_mode TCP/UDP mode flags 
 * \{
 */
#define WIFI11_TCP_MODE         0
#define WIFI11_UDP_MODE         1
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
#define DRV_TX_BUFFER_SIZE 500
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

    digital_out_t en;
    digital_out_t cs;
    digital_out_t gp1;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} wifi11_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t en;
    pin_name_t cs;
    pin_name_t gp1;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.   

} wifi11_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void wifi11_cfg_setup ( wifi11_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param[in] ctx Click object.
 * See #wifi11_t object definition for detailed explanation.
 * @param[in] cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this Click.
 */
WIFI11_RETVAL wifi11_init ( wifi11_t *ctx, wifi11_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @details This function writes the specified number of data bytes.
 * @param[in] ctx Click object.
 * See #wifi11_t object definition for detailed explanation.
 * @param[in] data_buf Data buffer for sends.
 * @param[in] len Number of bytes for sends.
 */
void wifi11_generic_write ( wifi11_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @details This function reads the specified number of data bytes.
 * @param[in] ctx Click object.
 * See #wifi11_t object definition for detailed explanation.
 * @param[out] data_buf Data buffer for read data.
 * @param[in] max_len The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
int32_t wifi11_generic_read ( wifi11_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Device reset function.
 * @details This function resets the device.
 * @param ctx Click object.
 * See #wifi11_t object definition for detailed explanation.
 * 
 * @return Nothing.
 */
void wifi11_reset_device ( wifi11_t *ctx );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #wifi11_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 */
void wifi11_send_cmd ( wifi11_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the Click module.
 * @param[in] ctx : Click context object.
 * See #wifi11_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 *
 * @return Nothing.
 */
void wifi11_send_cmd_with_parameter ( wifi11_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Connect to AP function.
 * @details This function connects to the desired AP.
 * @param[in] ctx : Click context object.
 * See #wifi11_t object definition for detailed explanation.
 * @param[in] ssid      SSID of AP.
 * @param[in] password  AP password ( NULL - if the AP is OPEN ).
 *
 * @return Nothing.
 */
void wifi11_connect_to_ap ( wifi11_t *ctx, char *ssid, char *password );

/**
 * @brief Create TCP/UDP server function.
 * @details This function creates TCP/UDP server on the desired port.
 * @param[in] ctx : Click context object.
 * See #wifi11_t object definition for detailed explanation.
 * @param[in] mode      TCP - 0, UDP - 1.
 * @param[in] port      Local port: 1-65535.
 *
 * @return Nothing.
 */
void wifi11_create_tcp_udp_server ( wifi11_t *ctx, uint8_t mode, uint16_t port );

#ifdef __cplusplus
}
#endif
#endif  // _WIFI11_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
