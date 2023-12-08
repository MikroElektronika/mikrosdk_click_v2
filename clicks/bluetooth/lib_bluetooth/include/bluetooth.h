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
 * \brief This file contains API for Bluetooth Click driver.
 *
 * \addtogroup bluetooth Bluetooth Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

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


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define BLUETOOTH_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BLUETOOTH_RETVAL  uint8_t

#define BLUETOOTH_INIT_OK      0x00
#define BLUETOOTH_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup var_macros Variables
 * \{
 */
#define BLUETOOTH_CMD           0x01
#define BLUETOOTH_AOK           0x02
#define BLUETOOTH_CONN          0x03
#define BLUETOOTH_DONE          0x04
#define BLUETOOTH_ERR           0x00
#define BLUETOOTH_OK            0x01
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
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

    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} bluetooth_t;

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

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} bluetooth_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t bluetooth_error_t;

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
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void bluetooth_cfg_setup ( bluetooth_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param bluetooth Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BLUETOOTH_RETVAL bluetooth_init ( bluetooth_t *ctx, bluetooth_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param bluetooth Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void bluetooth_generic_write ( bluetooth_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param bluetooth Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t bluetooth_generic_read ( bluetooth_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Write command function.
 * @param bluetooth Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void bluetooth_write_command ( bluetooth_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Enable device function
 *
 * @param ctx         Click object.
 * 
 * @description The function enable RN-41 Bluetooth module
 *              on Bluetooth Click board by set to '1' state of RST pin.
 */
void bluetooth_enable ( bluetooth_t *ctx );

/**
 * @brief Hardwere reset function
 *
 * @param ctx         Click object.
 * 
 * @description The function hardwere reset RN-41 Bluetooth module
 *              on Bluetooth Click board by cleared to '0' state of RST pin,
 *              weit 200 ms, set to '1' state of RST pin and weit 1 sec.
 */
void bluetooth_hw_reset ( bluetooth_t *ctx );

/**
 * @brief Enter the command mode function
 *
 * @param ctx         Click object.
 *
 * @description The function enter the command mode of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_enter_command_mode ( bluetooth_t *ctx );

/**
 * @brief Exit the command mode function
 *
 * @param ctx         Click object.
 *
 * @description The function exit the command mode of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_exit_command_mode ( bluetooth_t *ctx );

/**
 * @brief Toggles echo function
 *
 * @param ctx         Click object. 
 *
 * @description The function toggles the local echo ON and OFF of
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_toggle_echo ( bluetooth_t *ctx );

/**
 * @brief Set the device name function
 *
 * @param ctx         Click object. 
 * @param name        Pointer to the memory location where the name be stored
 *
 * @description The function set the device name of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_set_device_name ( bluetooth_t *ctx, uint8_t *name );

/**
 * @brief Set the operating mode function
 *
 * @param ctx         Click object. 
 * @param op_mode
 * <pre>
 * - 0 : [ Slave Mode ] Default mode, in which other Bluetooth devices can discover
 * and connect to the module;
 * - 1 : [ Master Mode ] In this low-speed connection mode, the module makes
 * connections when a connect command (C) is received;
 * - 2 : [ Trigger Mode ] In this low-speed connection mode, the module makes
 * connections automatically when a character is received on the serial port (UART);
 * - 3 : [ Auto-Connect Master Mode ] In this mode, the module makes connections
 *  automatically on power-up and re-connects when the connection is lost;
 * - 4 : [ Auto-Connect DTR Mode ] Its operates like Auto-Connect Master Mode
 * except that you control connection and disconnect evaluation kits;
 * - 5 : [ Auto-Connect ANY Mode ] This mode operates like Auto-Connect DTR Mode;
 * - 6 : [ Pairing Mode ] In this mode, the module attempts to connect with the
 * remote device matching the store remote address;
 * </pre>
 *
 * @description The function sets the operating mode of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_set_operating_mode ( bluetooth_t *ctx, uint8_t op_mode );

/**
 * @brief Enable 7-Bit data mode function
 *
 * @param ctx         Click object. 
 *
 * @description The function enable 7-Bit data mode of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_enable_7_bit_data_mode ( bluetooth_t *ctx );

/**
 * @brief Disable 7-Bit data mode function
 *
 * @param ctx         Click object. 
 *
 * @description The function disable 7-Bit data mode of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_disable_7_bit_data_mode ( bluetooth_t *ctx );

/**
 * @brief Set the authentication function
 *
 * @param ctx         Click object.  
 * @param auth_value
 * <pre>
 * - 0 : [ Open mode ] The module uses Bluetooth version 2.0 with NO encryption;
 * - 1 : [ SSP keyboard I/O mode ] Default; The remote host receives a prompt, reply yes to pair;
 * - 2 : [ SSP �just works� mode ] The mode works with iOS device and newer PCs;
 * - 4 : [ Pin code mode ] Pin code mode authentication, which requires the host device to
 * enter a pin code that matches the stored pin code;
 * </pre>
 *
 * @description The function set the authentication value to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_set_authentication ( bluetooth_t *ctx, uint8_t auth_value );

/**
 * @brief Set the break function
 *
 * @param ctx         Click object.  
 * @param break_signal
 * <pre>
 * Break Length :
 * - 1 : 37   ms;
 * - 2 : 18.5 ms;
 * - 3 : 12   ms;
 * - 4 :  9   ms;
 * - 5 :  7   ms;
 * - 6 :  6   ms;
 * </pre>
 *
 * @description The function set the break signal length to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_set_break ( bluetooth_t *ctx, uint8_t break_signal );

/**
 * @brief Sets the class of device (COD) function
 *
 * @param ctx         Click object.  
 * @param msw         Pointer to the memory location where the msw hex value be stored
 * @param lsw         Pointer to the memory location where the lsw hex value be stored
 *
 * @retval status: 0 - ERROR; 1 - OK;
 *
 * @description The function set the bthe class of device (COD) to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
BLUETOOTH_RETVAL bluetooth_set_cod ( bluetooth_t *ctx, uint8_t *msw, uint8_t *lsw );

/**
 * @brief Set factory defaults settings function
 *
 * @param ctx         Click object. 
 *
 * @description The function set factory defaults settings to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_set_factory_defaults ( bluetooth_t *ctx );

/**
 * @brief Set enable an inquiry scan function
 *
 * @param ctx           Click object. 
 * @param d_hex_value   Pointer to the memory loc. where the discoverability hex value be stored
 *
 * @description The function set enable an inquiry scan to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_set_discoverability ( bluetooth_t *ctx, uint8_t *d_hex_value );

/**
 * @brief Set enable page scanning function
 *
 * @param ctx          Click object. 
 * @param c_hex_value  Pointer to the memory location where the connectability hex value be stored
 *
 * @description The function set enable page scanning to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_setConnectability ( bluetooth_t *ctx, uint8_t *c_hex_value );

/**
 * @brief Set UART parity function
 *
 * @param ctx           Click object.  
 * @param character
 * <pre>
 * UART parity values:
 * - 'E' : Even;
 * - 'O' : Odd;
 * - 'N' : None;
 * </pre>
 *
 * @retval status: 0 - ERROR; 1 - OK;
 *
 * @description The function set UART parity to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
BLUETOOTH_RETVAL bluetooth_set_uart_parity ( bluetooth_t *ctx, uint8_t character );

/**
 * @brief Set extended status string function
 *
 * @param ctx          Click object.   
 * @param es_string    Pointer to the memory location where the extended status string be stored
 *
 * @description The function set extended status string to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 *
 * @note es_string up to 8 alphanumeric characters
 */
void bluetooth_set_extended_status_string ( bluetooth_t *ctx, uint8_t *es_string );

/**
 * @brief Set security pin code function
 *
 * @param ctx       Click object.   
 * @param sp_code   Pointer to the memory location where the security pin code string be stored
 *
 * @retval status: 0 - ERROR; 1 - OK;
 *
 * @description The function set security pin code string to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 *
 * @note sp_code up to 20 alphanumeric characters
 */
BLUETOOTH_RETVAL bluetooth_set_security_pin_code ( bluetooth_t *ctx, uint8_t *sp_code );

/**
 * @brief Set special configuration settings function
 *
 * @param ctx             Click object.   
 * @param special_config
 * <pre> 
 * -   0 : Default. The device does not use any special configuration;
 * -   4 : With this option set, the device does not read the GPIO3 and GPIO6 pin
 *  values on power-up;
 * -   8 : Disables discoverability at power up;
 * -  16 : This option configures the firmware to optimize for low latency data
 * transfers rather than throughput;
 * - 128 : This option causes the device to reboot after disconnect;
 * - 256 : This option sets 2 stop bit mode on the UART;
 * </pre>
 *
 * @retval status: 0 - ERROR; 1 - OK;
 *
 * @description The function set special configuration settings to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
BLUETOOTH_RETVAL bluetooth_set_special_config ( bluetooth_t *ctx, uint16_t special_config );

/**
 * @brief Set the remote Bluetooth address function
 *
 * @param ctx           Click object.    
 * @param r_addr        Pointer to the memory location where the remote address string be stored
 *
 * @description The function stores the remote Bluetooth address to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 *
 * @note r_addr is string of the 12 hexadecimal digits
 */
void bluetooth_set_remote_address ( bluetooth_t *ctx, uint8_t *r_addr );

/**
 * @brief Set the baud rate function
 *
 * @param ctx           Click object.  
 * @param baud_rate
 * <pre> 
 * Baud rate :
 * -   1200 :  1200 bps;
 * -   2400 :  2400 bps;
 * -   9600 :  9600 bps;
 * -  19200 : 19200 bps;
 * -  38400 : 38400 bps;
 * -  57600 : 57600 bps;
 * - 115200 : 115200 bps [ Default ];
 * </pre> 
 *
 * @retval status: 0 - ERROR; 1 - OK;
 *
 * @description The function set the baud rate value to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
BLUETOOTH_RETVAL bluetooth_set_baud_rate ( bluetooth_t *ctx, uint32_t baud_rate );

/**
 * @brief Set bonding enable function
 *
 * @param ctx           Click object. 
 *
 * @description The function set bonding enable of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_enable_bonding ( bluetooth_t *ctx );

/**
 * @brief Set bonding disable function
 *
 * @param ctx           Click object. 
 *
 * @description The function set bonding disable of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_disable_bonding ( bluetooth_t *ctx );

/**
 * @brief Reboot the module function
 *
 * @param ctx           Click object. 
 *
 * @description The function set bonding disable of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_reboot ( bluetooth_t *ctx );

/**
 * @brief Set the profile function
 *
 * @param ctx           Click object.  
 * @param profile
 * <pre> 
 * Profile :
 * - 0 : [ SPP ], Default, no modem control;
 * - 1 : [ DUN-DCE ], Slave or gateway;
 * - 2 : [ DUN-DTE ], Master or client;
 * - 3 : [ MDM SPP ], With modem control signals;
 * - 4 : [ SPP and DUN-DCE ], Multi-profile;
 * - 5 : [ APL ], Apple (iAP) profile, Refer to the iAP Bluetooth Evaluation Kit for
 * Developing Accessories Compatible with iOS Devices User
 * Manual for more information on using this profile;
 * - 6 : [ HID ], Device must be running a special firmware version
 * </pre> 
 *
 * @retval status: 0 - ERROR; 1 - OK;
 *
 * @description The function set the profile of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
BLUETOOTH_RETVAL bluetooth_set_profile ( bluetooth_t *ctx, uint8_t profile );

/**
 * @brief Enables the role switch function
 *
 * @param ctx           Click object. 
 *
 * @description The function enables the role switch of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_enable_role_switch ( bluetooth_t *ctx );

/**
 * @brief Disables the role switch function
 *
 * @param ctx           Click object. 
 *
 * @description The function disables the role switch of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_disable_role_switch ( bluetooth_t *ctx );

/**
 * @brief Connect the device to a remote address function
 *
 * @param ctx           Click object.  
 * @param r_addr        Pointer to the memory location where the remote address string be stored
 *
 * @description The function connect the device to a remote address to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_connect_to_remote_address ( bluetooth_t *ctx, uint8_t *r_addr );

/**
 * @brief Connect the device to a remote address fast mode function
 *
 * @param ctx           Click object. 
 * @param r_addr        Pointer to the memory location where the remote address string be stored
 *
 * @description The function connect the device to a remote address fast mode to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_connect_to_remote_address_fast_mode ( bluetooth_t *ctx, uint8_t *r_addr );

/**
 * @brief Ends configuration and puts the device into fast data mode function
 *
 * @param ctx           Click object. 
 *
 * @description The function ends configuration and puts the device into fast data mode to the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_endspecial_config ( bluetooth_t *ctx );

/**
 * @brief Get displays a list of help command function
 *
 * @param ctx           Click object.  
 *
 * @description The function get displays a list of help command of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_get_help ( bluetooth_t *ctx );

/**
 * @brief Get displays basic settings function
 *
 * @param ctx           Click object.  
 *
 * @description The function get displays basic settings of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_get_basic_settings ( bluetooth_t *ctx );

/**
 * @brief Get displays the device�s extended settings function
 *
 * @param ctx           Click object.  
 *
 * @description The function get displays the device�s extended settings of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_get_extended_settings ( bluetooth_t *ctx );

/**
 * @brief Get displays the device�s eBluetooth address function
 *
 * @param ctx           Click object.  
 *
 * @description The function get displays the Bluetooth address of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_get_device_address ( bluetooth_t *ctx );

/**
 * @brief Scans for Bluetooth devices in pairing mode function
 *
 * @param ctx           Click object.  
 *
 * @description The function scans for Bluetooth devices in pairing mode of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_scans_device ( bluetooth_t *ctx );

/**
 * @brief Displays the remote side modem signal status function
 *
 * @param ctx           Click object.  
 *
 * @description The function displays the remote side modem signal status of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_get_signal_status ( bluetooth_t *ctx );

/**
 * @brief Set undiscoverable mode function
 *
 * @param ctx           Click object. 
 *
 * @description The function set undiscoverable mode of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_set_undiscoverable (  bluetooth_t *ctx );

/**
 * @brief Set quiet mode function
 *
 * @param ctx           Click object.  
 * @param q_mode
 * <pre> 
 * - 0 : The module is discoverable and able to connect.;
 * - 1 : The module is not discoverable and not able to connect;
 * - 2 : The module is able to connect but is not discoverable;
 * - 3 : Displays the current quiet mode is defined above;
 * </pre> 
 *
 * @retval status: 0 - ERROR; 1 - OK;
 *
 * @description The function set quiet mode of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
BLUETOOTH_RETVAL bluetooth_set_quiet_mode ( bluetooth_t *ctx, uint8_t q_mode );

/**
 * @brief Get firmware version function
 *
 * @param ctx                 Click object.  
 *
 * @description The function get firmware version of the
 *              RN-41 Bluetooth module on Bluetooth Click board.
 */
void bluetooth_get_firmware_version ( bluetooth_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _BLUETOOTH_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
