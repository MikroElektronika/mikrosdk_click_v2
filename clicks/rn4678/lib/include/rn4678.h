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
 * \brief This file contains API for RN4678 Click driver.
 *
 * \addtogroup rn4678 RN4678 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RN4678_H
#define RN4678_H

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
#define RN4678_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.sw_btn = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.wkup = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RN4678_RETVAL  uint8_t

#define RN4678_INIT_OK      0x00
#define RN4678_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup var_macros Variables
 * \{
 */
#define RN4678_CMD           0x01
#define RN4678_AOK           0x02
#define RN4678_CONN          0x03
#define RN4678_DONE          0x04
#define RN4678_ERR           0x00
#define RN4678_OK            0x01
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
    digital_out_t cts;
    digital_out_t sw_btn;
    digital_out_t wkup;

    // Modules 
    digital_in_t rts;

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} rn4678_t;

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
    pin_name_t wkup;
    pin_name_t cts;
    pin_name_t sw_btn;
    pin_name_t rts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} rn4678_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t rn4678_error_t;

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
void rn4678_cfg_setup ( rn4678_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param rn4678 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RN4678_RETVAL rn4678_init ( rn4678_t *ctx, rn4678_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param rn4678 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void rn4678_generic_write ( rn4678_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param rn4678 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t rn4678_generic_read ( rn4678_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Write command function.
 * @param rn4678 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void rn4678_write_command ( rn4678_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief CTS Pin Setting function
 *
 * @param ctx         Click object.
 * @param state        0 - Low, 1 (or other value different from 0) - High
 * 
 * @description This function sets the CTS pin to the desired state  
 *              ( UART clear to send control signal ).
 * @note Used only when hardware flow control is enabled.
 *       The HW flow control is enabled by default.
 */
void rn4678_set_cts_pin ( rn4678_t *ctx, uint8_t state );

/**
 * @brief Enable device function
 *
 * @param ctx         Click object.
 * 
 * @description The function enable RN-4678 Bluetooth module
 *              on RN4678 Click board by set to '1' state of RST pin.
 */
void rn4678_enable ( rn4678_t *ctx );

/**
 * @brief Hardwere reset function
 *
 * @param ctx         Click object.
 * 
 * @description The function hardwere reset RN-4678 Bluetooth module
 *              on RN4678 Click board by cleared to '0' state of RST pin,
 *              weit 200 ms, set to '1' state of RST pin and weit 1 sec.
 */
void rn4678_hw_reset ( rn4678_t *ctx );

/**
 * @brief Enter the command mode function
 *
 * @param ctx         Click object.
 *
 * @description The function enter the command mode of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_enter_command_mode ( rn4678_t *ctx );

/**
 * @brief Exit the command mode function
 *
 * @param ctx         Click object.
 *
 * @description The function exit the command mode of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_exit_command_mode ( rn4678_t *ctx );

/**
 * @brief Toggles echo function
 *
 * @param ctx         Click object. 
 *
 * @description The function toggles the local echo ON and OFF of
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_toggle_echo ( rn4678_t *ctx );

/**
 * @brief Set the device name function
 *
 * @param ctx         Click object. 
 * @param name        Pointer to the memory location where the name be stored
 *
 * @description The function set the device name of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_set_device_name ( rn4678_t *ctx, uint8_t *name );

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
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_set_operating_mode ( rn4678_t *ctx, uint8_t op_mode );

/**
 * @brief Enable 7-Bit data mode function
 *
 * @param ctx         Click object. 
 *
 * @description The function enable 7-Bit data mode of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_enable_7_bit_data_mode ( rn4678_t *ctx );

/**
 * @brief Disable 7-Bit data mode function
 *
 * @param ctx         Click object. 
 *
 * @description The function disable 7-Bit data mode of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_disable_7_bit_data_mode ( rn4678_t *ctx );

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
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_set_authentication ( rn4678_t *ctx, uint8_t auth_value );

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
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_set_break ( rn4678_t *ctx, uint8_t break_signal );

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
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
RN4678_RETVAL rn4678_set_cod ( rn4678_t *ctx, uint8_t *msw, uint8_t *lsw );

/**
 * @brief Set factory defaults settings function
 *
 * @param ctx         Click object. 
 *
 * @description The function set factory defaults settings to the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_set_factory_defaults ( rn4678_t *ctx );

/**
 * @brief Set enable an inquiry scan function
 *
 * @param ctx           Click object. 
 * @param d_hex_value   Pointer to the memory loc. where the discoverability hex value be stored
 *
 * @description The function set enable an inquiry scan to the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_set_discoverability ( rn4678_t *ctx, uint8_t *d_hex_value );

/**
 * @brief Set enable page scanning function
 *
 * @param ctx          Click object. 
 * @param c_hex_value  Pointer to the memory location where the connectability hex value be stored
 *
 * @description The function set enable page scanning to the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_setConnectability ( rn4678_t *ctx, uint8_t *c_hex_value );

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
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
RN4678_RETVAL rn4678_set_uart_parity ( rn4678_t *ctx, uint8_t character );

/**
 * @brief Set extended status string function
 *
 * @param ctx          Click object.   
 * @param es_string    Pointer to the memory location where the extended status string be stored
 *
 * @description The function set extended status string to the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 *
 * @note es_string up to 8 alphanumeric characters
 */
void rn4678_set_extended_status_string ( rn4678_t *ctx, uint8_t *es_string );

/**
 * @brief Set security pin code function
 *
 * @param ctx       Click object.   
 * @param sp_code   Pointer to the memory location where the security pin code string be stored
 *
 * @retval status: 0 - ERROR; 1 - OK;
 *
 * @description The function set security pin code string to the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 *
 * @note sp_code up to 20 alphanumeric characters
 */
RN4678_RETVAL rn4678_set_security_pin_code ( rn4678_t *ctx, uint8_t *sp_code );

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
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
RN4678_RETVAL rn4678_set_special_config ( rn4678_t *ctx, uint16_t special_config );

/**
 * @brief Set the remote Bluetooth address function
 *
 * @param ctx           Click object.    
 * @param r_addr        Pointer to the memory location where the remote address string be stored
 *
 * @description The function stores the remote Bluetooth address to the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 *
 * @note r_addr is string of the 12 hexadecimal digits
 */
void rn4678_set_remote_address ( rn4678_t *ctx, uint8_t *r_addr );

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
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
RN4678_RETVAL rn4678_set_baud_rate ( rn4678_t *ctx, uint32_t baud_rate );

/**
 * @brief Set bonding enable function
 *
 * @param ctx           Click object. 
 *
 * @description The function set bonding enable of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_enable_bonding ( rn4678_t *ctx );

/**
 * @brief Set bonding disable function
 *
 * @param ctx           Click object. 
 *
 * @description The function set bonding disable of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_disable_bonding ( rn4678_t *ctx );

/**
 * @brief Reboot the module function
 *
 * @param ctx           Click object. 
 *
 * @description The function set bonding disable of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_reboot ( rn4678_t *ctx );

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
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
RN4678_RETVAL rn4678_set_profile ( rn4678_t *ctx, uint8_t profile );

/**
 * @brief Enables the role switch function
 *
 * @param ctx           Click object. 
 *
 * @description The function enables the role switch of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_enable_role_switch ( rn4678_t *ctx );

/**
 * @brief Disables the role switch function
 *
 * @param ctx           Click object. 
 *
 * @description The function disables the role switch of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_disable_role_switch ( rn4678_t *ctx );

/**
 * @brief Connect the device to a remote address function
 *
 * @param ctx           Click object.  
 * @param r_addr        Pointer to the memory location where the remote address string be stored
 *
 * @description The function connect the device to a remote address to the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_connect_to_remote_address ( rn4678_t *ctx, uint8_t *r_addr );

/**
 * @brief Connect the device to a remote address fast mode function
 *
 * @param ctx           Click object. 
 * @param r_addr        Pointer to the memory location where the remote address string be stored
 *
 * @description The function connect the device to a remote address fast mode to the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_connect_to_remote_address_fast_mode ( rn4678_t *ctx, uint8_t *r_addr );

/**
 * @brief Ends configuration and puts the device into fast data mode function
 *
 * @param ctx           Click object. 
 *
 * @description The function ends configuration and puts the device into fast data mode to the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_endspecial_config ( rn4678_t *ctx );

/**
 * @brief Get displays a list of help command function
 *
 * @param ctx           Click object.  
 *
 * @description The function get displays a list of help command of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_get_help ( rn4678_t *ctx );

/**
 * @brief Get displays basic settings function
 *
 * @param ctx           Click object.  
 *
 * @description The function get displays basic settings of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_get_basic_settings ( rn4678_t *ctx );

/**
 * @brief Get displays the device�s extended settings function
 *
 * @param ctx           Click object.  
 *
 * @description The function get displays the device�s extended settings of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_get_extended_settings ( rn4678_t *ctx );

/**
 * @brief Get displays the device�s eBluetooth address function
 *
 * @param ctx           Click object.  
 *
 * @description The function get displays the Bluetooth address of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_get_device_address ( rn4678_t *ctx );

/**
 * @brief Scans for Bluetooth devices in pairing mode function
 *
 * @param ctx           Click object.  
 *
 * @description The function scans for Bluetooth devices in pairing mode of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_scans_device ( rn4678_t *ctx );

/**
 * @brief Displays the remote side modem signal status function
 *
 * @param ctx           Click object.  
 *
 * @description The function displays the remote side modem signal status of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_get_signal_status ( rn4678_t *ctx );

/**
 * @brief Set undiscoverable mode function
 *
 * @param ctx           Click object. 
 *
 * @description The function set undiscoverable mode of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_set_undiscoverable (  rn4678_t *ctx );

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
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
RN4678_RETVAL rn4678_set_quiet_mode ( rn4678_t *ctx, uint8_t q_mode );

/**
 * @brief Get firmware version function
 *
 * @param ctx                 Click object.  
 *
 * @description The function get firmware version of the
 *              RN-4678 Bluetooth module on RN4678 Click board.
 */
void rn4678_get_firmware_version ( rn4678_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _RN4678_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
