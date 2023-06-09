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
 * \brief This file contains API for BLE 8 Click driver.
 *
 * \addtogroup ble8 BLE 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BLE8_H
#define BLE8_H

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
#define BLE8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.dtr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.dsr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BLE8_RETVAL  uint8_t

#define BLE8_OK           0x00
#define BLE8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup term_char  String (data) termination character
 * \{
 */
#define BLE8_END_BUFF                           0
/** \} */

/**
 * \defgroup response_states  Response states
 * \{
 */
#define BLE8_RSP_READY                          1
#define BLE8_RSP_NOT_READY                      0
/** \} */

/**
 * \defgroup settings_for_echo  Settings to turn echo on/off 
 * \{
 */
#define BLE8_ECHO_ON                            1
#define BLE8_ECHO_OFF                           0
/** \} */

/**
 * \defgroup settings_for_device_mode  Settings to select device mode
 * \{
 */
#define BLE8_COMMAND_MODE                       0
#define BLE8_DATA_MODE                          1
#define BLE8_EXT_DATA_MODE                      2
#define BLE8_PPP_MODE                           3
/** \} */

/**
 * \defgroup  device_low_energy_role  Settings to select device low energy role
 * \{
 */
#define BLE8_DISABLED_ROLE                      0
#define BLE8_CENTRAL_ROLE                       1
#define BLE8_PERIPHERAL_ROLE                    2
#define BLE8_SIMULTANEOUS_ROLE                  3
/** \} */

/**
 * \defgroup settings_for_security_mode  Settings to select security mode
 * \{
 */
#define BLE8_SEC_DISABLED                       1
#define BLE8_SEC_JUST_WORKS                     2
#define BLE8_SEC_DISPLAY_ONLY                   3
#define BLE8_SEC_DISPLAY_YES_NO                 4
#define BLE8_SEC_KEYBOARD_ONLY                  5
#define BLE8_SEC_OUT_OF_BAND                    6
/** \} */

/**
 * \defgroup settings_for_paring_mode  Settings to enable/disable pairing mode
 * \{
 */
#define BLE8_GAP_NON_PAIRING_MODE               1
#define BLE8_GAP_PAIRING_MODE                   2
/** \} */

/**
 * \defgroup settings_for_connectable_mode  Settings to enable/disable connectable mode
 * \{
 */
#define BLE8_GAP_NON_CONNECTABLE_MODE           1
#define BLE8_GAP_CONNECTABLE_MODE               2
/** \} */

/**
 * \defgroup settings_for_discoverable_mode  Settings to enable/disable discoverable mode
 * \{
 */
#define BLE8_GAP_NON_DISCOVERABLE_MODE          1
#define BLE8_GAP_LIMITED_DISCOVERABLE_MODE      2
#define BLE8_GAP_GENERAL_DISCOVERABLE_MODE      3
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 100
#define DRV_TX_BUFFER_SIZE 100
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
    digital_out_t dsr;

    // Input pins 

    digital_in_t dtr;
    digital_in_t rts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

    uint8_t rsp_rdy;
    uint8_t termination_char;

} ble8_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t dtr;
    pin_name_t rst;
    pin_name_t cts;
    pin_name_t dsr;
    pin_name_t rts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} ble8_cfg_t;

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
void ble8_cfg_setup ( ble8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BLE8_RETVAL ble8_init ( ble8_t *ctx, ble8_cfg_t *cfg );

/**
 * @brief Reset function
 *
 * @param ctx  Click object.
 * 
 * @description This function allows user to reset a module.
 */
void ble8_reset ( ble8_t *ctx );

/**
 * @brief Generic write function.
 * @param ble8 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void ble8_generic_write ( ble8_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ble8 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t ble8_generic_read ( ble8_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Response Ready function
 *
 * @param ctx         Click object.  
 *
 * @returns 0 - response is not ready, 1 - response is ready
 *
 * @description This function checks does response ready or not.
 */
uint8_t ble8_response_ready( ble8_t *ctx );

/**
 * @brief Transmit function
 *
 * @param ctx         Click object.  
 * @param tx_data     Data to be transmitted
 * @param term_char   Command termination character
 *
 * @description This function allows user to transmit data and send commands to the module.
 *
 * @note This function will send a termination character ('\r' default) automatically at 
 * the end of the data transmitting.
 */
void ble8_send_command ( ble8_t *ctx, char * command, uint8_t term_char );

/**
 * @brief Factory Reset command
 *
 * @param ctx         Click object. 
 * 
 * @description This command reset a module to factory defined defaults. 
 *
 * @note A reboot will be executed to update the new settings.
 */
void ble8_fact_rst_cmd ( ble8_t *ctx );

/**
 * @brief Store Current Configuration command
 *
 * @param ctx         Click object. 
 *
 * @description This command commits all the settings to be stored in start up database.
 *
 * @note Executes +CPWROFF command to write the parameters to non-volatile memory.
 */
void ble8_store_cnfg_cmd ( ble8_t *ctx );

/**
 * @brief Get Local Address command
 *
 * @description This command reads the local address of the bluetooth module.
 */
void ble8_get_local_addr_cmd ( ble8_t *ctx );

/**
 * @brief Module Start Mode Setting command
 *
 * @param ctx         Click object.  
 * @param start_mode      0 - Command mode ( default )
 *                        1 - Data mode
 *                        2 - Extended data mode
 *                        3 - PPP mode
 *
 * @description This command sets the module start mode.
 */
void ble8_set_start_mode_cmd ( ble8_t *ctx, uint8_t start_mode );

/**
 * @brief Get Module Start Mode command
 *
 * @param ctx         Click object. 
 * 
 * @description This command reads the module start mode.
 */
void ble8_get_start_mode_cmd ( ble8_t *ctx );

/**
 * @brief Enter Data Mode command
 *
 * @param ctx         Click object.  
 * @param mode      0 - Command mode ( default )
 *                  1 - Data mode
 *                  2 - Extended data mode
 *                  3 - PPP mode
 *
 * @description This command requests the module to move to the new mode.
 * @note After executing the data mode command or the extended data mode command, 
 *       a delay of 50 ms is required before start of data transmission.
 */
void ble8_enter_mode_cmd ( ble8_t *ctx, uint8_t mode );

/**
 * @brief Echo On/Off command
 *
 * @param ctx           Click object.  
 * @param echo_en       0 - Unit does not echo the characters in Command Mode
 *                      1 - Unit echoes the characters in Command Mode ( default )
 *
 * @description This command configures whether or not the unit echoes the characters received from the DTE in Command Mode.
 */
void ble8_set_echo_cmd ( ble8_t *ctx, uint8_t echo_en );

/**
 * @brief Get Echo Setting command
 *
 * @param ctx           Click object.
 * 
 * @description This command reads current echo setting.
 */
void ble8_get_echo_cmd ( ble8_t *ctx );

/**
 * @brief Local Name Setting command
 *
 * @param ctx           Click object.
 * @param local_name    Local name string to be set (maximum 29 characters)
 *
 * @description This command sets the local Bluetooth device name.
 *
 * @note 
 If user was enter a empty string, the local device name will be set to 
        "Bluetooth Device". For ANNA-B1, the default name is "ANNA-B1-XXXXXX", where XXXXXX is the last 6 characters from the Bluetooth address.
 */
void ble8_set_local_name_cmd ( ble8_t *ctx, char *local_name );

/**
 * @brief Get Local Name command
 *
 * @param ctx           Click object.
 * 
 * @description This command reads the local Bluetooth device name.
 */
void ble8_get_local_name_cmd ( ble8_t *ctx );

/**
 * @brief Bluetooth Low Energy Role Setting command
 *
 * @param ctx           Click object. 
 * @param le_role  
 * <pre> 
 *        0 - Disabled
 *        1 - Bluetooth low energy Central
 *        2 - Bluetooth low energy Peripheral ( default )
 *        3 - Bluetooth low energy Simultaneous Peripheral and Central
 * </pre>  
 *
 * @description This command sets the Bluetooth low energy role.
 * @note For the settings to take effect on ANNA-B1, use the commands &W and +CPWROFF to store the configuration 
 *       to start up database and reboot the module.
 */
void ble8_set_low_energy_role_cmd ( ble8_t *ctx, uint8_t le_role );

/**
 * @brief Get Bluetooth Low Energy Role command
 *
 * @param ctx           Click object.
 * 
 * @description This command reads the Bluetooth low energy role.
 */
void ble8_get_low_energy_role_cmd ( ble8_t *ctx );

/**
 * @brief Get Peer List command
 *
 * @param ctx           Click object.
 * 
 * @description This command reads the connected peers (peer handle).
 *
 * @note The module will return a peer handle that identifies the connection, 
 *       protocol of the connection, local address and remote address if available.
 */
void ble8_get_list_peers_cmd ( ble8_t *ctx );

/**
 * @brief Get Server Configuration command
 *
 * @param ctx           Click object.
 * 
 * @description This command reads server configuration.
 *
 * @note 
 * <pre>
 * The module will return a type of server:
 *       0 - Disabled, 1 - TCP, 2 - UDP, 3 - SPP, 4 - DUN, 5 - UUID, 
 *       6 - SPS (supported by ANNA-B1), 7 - Reserved, 8 - ATP.
 * </pre>
 */
void ble8_get_server_cnfg_cmd ( ble8_t *ctx );

/**
 * @brief Default Configuration command
 *
 * @param ctx           Click object.
 * 
 * @description This command resets the profile to the last stored configuration. 
 *
 * @note Any settings committed with AT&W will be discarded. 
 *       The restored settings will be used after a reboot, which this function also executes.
 */
void ble8_set_default_cmd ( ble8_t *ctx );

/**
 * @brief Security Mode Setting command
 *
 * @param ctx           Click object. 
 * @param sec_mode  
 * <pre>
 *        1 - Security Disabled ( default )
 *        2 - Security Enabled - Just Works
 *        3 - Security Enabled - Display Only
 *        4 - Security Enabled - Display Yes/No
 *        5 - Security Enabled - Keyboard Only
 *        6 - Security Enabled - Out of band
 * </pre> 
 *
 * @description This command sets the security mode.
 *
 * @note 
 * <pre> For the settings to take effect on ANNA-B1, use the commands &W and +CPWROFF to 
 *       store the configuration to start up database and reboot the module.
 *       ANNA-B1 does not support Out of band and will fall back to Just Works pairing.
 * </pre>  
 */
void ble8_set_sec_mode_cmd ( ble8_t *ctx, uint8_t sec_mode );

/**
 * @brief Get Security Mode command
 *
 * @param ctx           Click object.
 * 
 * @description This command reads the security mode.
 */
void ble8_get_sec_mode_cmd ( ble8_t *ctx );

/**
 * @brief Pairing Mode Setting command
 *
 * @param ctx             Click object.
 * @param pairing_mode    1 - GAP non-pairing mode;   2 - GAP pairing mode ( default )
 *
 * @description This command sets the pairing mode.
 */
void ble8_pairing_en_cmd ( ble8_t *ctx, uint8_t pairing_mode );

/**
 * @brief Get Pairing Mode command
 *
 * @param ctx           Click object.
 * 
 * @description This command reads the pairing mode.
 */
void ble8_check_pairing_cmd ( ble8_t *ctx );

/**
 * @brief Connectability Mode Setting command
 *
 * @param ctx           Click object. 
 * @param conn_mode     1 - GAP non-connectable mode; 2 - GAP connectable mode ( default )
 *
 * @description This command sets the GAP connectability mode.
 */
void ble8_connectability_en_cmd ( ble8_t *ctx, uint8_t conn_mode );

/**
 * @brief Get Connectability Mode command
 *
 * @param ctx           Click object.
 * 
 * @description This command reads the GAP connectability mode.
 */
void ble8_check_connectability_cmd ( ble8_t *ctx );

/**
 * @brief Discoverability Mode Setting command
 *
 * @param ctx           Click object. 
 * @param discover_mode  
 * <pre> 
 *        1 - GAP non-discoverable mode
 *        2 - GAP limited discoverable mode
 *        3 - GAP general discoverable mode ( default )
 * </pre>  
 *
 * @description This command sets the GAP discoverability mode.
 *
 * @note For ANNA-B1, the device will stay in the limited discoverable mode for 180 seconds.
 */
void ble8_discoverability_en_cmd ( ble8_t *ctx, uint8_t discover_mode );

/**
 * @brief Get Discoverability Mode command
 *
 * @param ctx           Click object. 
 * 
 * @description This command reads the GAP discoverability mode.
 */
void ble8_check_discoverability_cmd ( ble8_t *ctx );

/**
 * @brief Get Info command
 *
 * @param ctx           Click object. 
 * 
 * @description This command reads the all device and serial interface informations.
 */
void ble8_get_info ( ble8_t *ctx );

/**
 * @brief SPS Pairing As Central Device command
 *
 * @param ctx          Click object.  
 * @param local_addr   Local address string of the target Bluetooth device ( peer ) 
 *                     [ 12 characters ]
 *
 * @description This command executes a SPS pairing as central device, sets data start mode 
 *              and reboot a module.
 *
 * @note This configuration will be stored to start up database.
 */
uint8_t ble8_sps_central_pairing ( ble8_t *ctx, uint8_t *local_addr );

/**
 * @brief SPS Pairing As Peripheral Device command
 *
 * @param ctx          Click object.   
 *
 * @description This command allows SPS pairing as peripheral device, sets data start mode 
 *              and reboot a module.
 *
 * @note This configuration will be stored to start up database.
 */
void ble8_sps_peripheral_pairing ( ble8_t *ctx );

/**
 * @brief CTS Pin Setting function
 *
 * @param ctx          Click object.   
 * @param state        0 - Low, 1 (or other value different from 0) - High
 *
 * @description This function sets the CTS pin to the desired state  
 *              ( UART clear to send control signal ).
 *
 * @note Used only when hardware flow control is enabled.
 *       The HW flow control is enabled by default.
 */
void ble8_set_cts_pin ( ble8_t *ctx, uint8_t state );

/**
 * @brief Set DSR Pin function
 *
 * @param ctx          Click object.    
 * @param state        0 - Low, 1 ( or other value different from 0 ) - High
 *
 * @description This function sets the DSR pin to the desired state 
 *              ( UART data set ready signal ).
 *
 * @note Used to change system modes by default.
 */
void ble8_set_dsr_pin ( ble8_t *ctx, uint8_t state );

/**
 * @brief Check DTR Pin function
 *
 * @param ctx          Click object. 
 *
 * @returns 0 or 1
 *
 * @description This function returns the state of the DTR pin
 *              ( UART data terminal ready signal).
 *
 * @note Used to indicate system status by default.
 */
uint8_t ble8_get_dtr_pin ( ble8_t *ctx );

/**
 * @brief Check RTS Pin function
 *
 * @returns 0 or 1
 *
 * @description This function returns the state of the RTS pin 
 *              ( UART ready to send control signal ).
 *
 * @note Used only when hardware flow control is enabled.
 *       The HW flow control is enabled by default.
 */
uint8_t ble8_get_rts_pin ( ble8_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _BLE8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
