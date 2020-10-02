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
  cfg.sw_btn  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst_n   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.rts     = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.wkup    = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cts     = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RN4678_RETVAL       uint8_t
#define RN4678_STATUS_T     uint8_t

#define RN4678_INIT_OK           0x00
#define RN4678_INIT_ERROR        0xFF
/** \} */

/**
 * \defgroup var Variables
 * \{
 */
#define RN4678_CMD                    0x01
#define RN4678_AOK                    0x02
#define RN4678_CONN                   0x03
#define RN4678_DONE                   0x04
#define RN4678_ERR                    0x00
#define RN4678_OK                     0x01
#define RN4678_DEVICE_TYPE_MASTER     0x02
#define RN4678_DEVICE_TYPE_SLAVE      0x03
#define RN4678_ID_MASTER              0x35
#define RN4678_ID_SLAVE               0x32
#define RN4678_MTYPE_MSG              'M'
#define RN4678_DTYPE_STRING           0x5331
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

    digital_out_t sw_btn;
    digital_out_t rst_n;
    digital_out_t rts;
    digital_out_t wkup;

    // Input pins 

    digital_in_t cts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

    uint8_t end_flag;
    uint8_t sen_flag;
    char device_buffer[ 255 ];
    uint8_t tmp_pos;

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

    pin_name_t sw_btn;
    pin_name_t rst_n;
    pin_name_t rts;
    pin_name_t wkup;
    pin_name_t cts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} rn4678_cfg_t;

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
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RN4678_RETVAL rn4678_init ( rn4678_t *ctx, rn4678_cfg_t *cfg );

/**
 * @brief Hardwere reset function
 *
 * @param ctx  Click object.
 *
 * @description The function hardwere reset RN4678 Bluetooth� 4.2 dual mode module
 * on RN4678 Click board by cleared to '0' state of RST pin,
 * weit 200 ms, set to '1' state of RST pin and weit 1 sec.
 */
void rn4678_hw_reset ( rn4678_t *ctx );

/**
 * @brief UART write function
 *
 * @param ctx       Click object. 
 * @param tx_data   Pointer to the memory location where tx_data be stored
 *
 * @description The function write text data to the
 * RN4678 Bluetooth� 4.2 dual mode module
 */
void rn4678_uart_write ( rn4678_t *ctx, uint8_t *tx_data );

/**
 * @brief Initialization RN4678 module
 *
 * @param ctx           Click object. 
 * @param dev_addr      Pointer to the memory location where dev_addr be stored
 *
 * @description The function initializes RN4678 Bluetooth� 4.2 dual mode module
 * by resets the module, disable I2C communications pins,
 * reboots the device for change to take effect, enters CMD mode again,
 * and sets the address of the device.
 */
void rn4678_initialize ( rn4678_t *ctx, char *dev_addr );

/**
 * @brief Connecting to slave device
 *
 * @param ctx         Click object. 
 * @param dev_addr    Pointer to the memory location where slave device with be stored
 *
 * @description The function connects to slave device with desired register address
 * by secures the connection and entering data stream mode.
 */
void rn4678_connect ( rn4678_t *ctx, char *dev_addr );

/**
 * @brief Disconnecting from slave device
 *
 * @param ctx  Click object.
 * 
 * @description The function disconnects from slave device
 * by enters CMD mode and kills connection.
 */
void rn4678_disconnect ( rn4678_t *ctx );

/**
 * @brief Send message function
 *
 * @param ctx                    Click object.
 * @param msg_type               8-bit message type ( e.g. message - 'M' = 0x4D )
 * @param data_type              16-bit data type ( e.g. sensor 1 - S1 = 0x5331 )
 * @param dev_id                 8-bit device id ( e.g. slave - 'S' = 0x53 )
 * @param tx_data                Pointer to the memory location where the text data is stored
 *
 * @description The function sends message to slave device.
 */
void rn4678_send ( rn4678_t *ctx, uint8_t msg_type, uint16_t data_type, uint8_t dev_id, uint8_t *tx_data );

/**
 * @brief Receiving character function
 *
 * @param ctx                   Click object. 
 * @param character             received character
 *
 * @description The function receives character by
 * waits for '#' - character to start parsing message,
 * waits for '*' - character to stop parsing message
 * and sets flag if whole and properly formated message is received.
 */
void rn4678_receive ( rn4678_t *ctx, char character );

/**
 * @brief Read received message function
 *
 * @param ctx               Click object.  
 * @param rx_data           pointer to the memory location where the read text data is stored
 *
 * @retval
 * <pre>
 * - 0 : if whole and properly formated message was not received and stored
 * - 1 : if whole and properly formated message was received and stored
 * </pre> 
 *
 * @description The function check message from if data received ( if flag was set ),
 * stores received message to rx_data pointer to the memory location where the read text data is stored
 * and replaces '*' - character with end of string - '0x00'.
 */
uint8_t rn4678_read ( rn4678_t *ctx, uint8_t *rx_data );

/**
 * @brief Set the authentication function
 *
 * @param ctx               Click object.   
 * @param auth_value
 * <pre> 
 * - 1 : Secure Simple Pairing (SSP) Pin Code Confirm mode;
 * - 2 : Default; SSP �Just Works� mode;
 * - 3 : SSP Pin Code Input mode;
 * - 4 : Legacy Pin Code mode;
 * </pre>
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function set the authentication value.
 */
RN4678_STATUS_T rn4678_set_authentication ( rn4678_t *ctx, uint8_t auth_value );

/**
 * @brief Sets the class of device (COD) function
 *
 * @param ctx     Click object.   
 * @param msw     Pointer to the memory location where the msw hex value be stored
 * @param lsw     Pointer to the memory location where the lsw hex value be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function set the bthe class of device (COD)
 */
RN4678_STATUS_T rn4678_set_cod ( rn4678_t *ctx, uint8_t *msw, uint8_t *lsw );

/**
 * @brief Set the model string in the BLE device information service function
 *
 * @param ctx             Click object.   
 * @param model_string    Pointer to the memory location where the model string be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function set the model string in the BLE device information service
 */
RN4678_STATUS_T rn4678_set_model_string ( rn4678_t *ctx, uint8_t *model_string );

/**
 * @brief Set the manufacturer in the BLE device information service function
 *
 * @param ctx             Click object.    
 * @param manufacturer_string Pointer to the memory location where the manuf. string be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function set the manufacturer in the BLE device information service.
 */
RN4678_STATUS_T rn4678_set_manufacturer_string ( rn4678_t *ctx, uint8_t *manufacturer_string );

/**
 * @brief Set the software revision of the firmware function
 *
 * @param ctx             Click object.    
 * @param software_revision Pointer to the memory location where the software rev. be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function set the software revision.
 */
RN4678_STATUS_T rn4678_set_software_revision ( rn4678_t *ctx, uint8_t *software_revision );

/**
 * @brief Set the serial number of the device function
 *
 * @param ctx             Click object.    
 * @param serial_number Pointer to the memory location where the serial number string be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function set the serial number.
 */
RN4678_STATUS_T rn4678_set_serial_number ( rn4678_t *ctx, uint8_t *serial_number );

/* Set the Universally Unique Identifier function */
RN4678_STATUS_T rn4678_set_unique_identifier ( rn4678_t *ctx, uint8_t *unique_identifier );

/**
 * @brief Set factory defaults settings function
 *
 * @param ctx             Click object.   
 * 
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function set factory defaults settings.
 */
RN4678_STATUS_T rn4678_set_factory_defaults ( rn4678_t *ctx );

/**
 * @brief Set Bluetooth modes function
 *
 * @param ctx             Click object.    
 * @param modes
 * <pre>
 * Bluetooth Mode:
 * - 0 : Dual mode;
 * - 1 : Bluetooth Low Energy only;
 * - 2 : Bluetooth Classic only;
 * </pre> 
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function set the Bluetooth modes.
 */
RN4678_STATUS_T rn4678_set_bluetooth_modes ( rn4678_t *ctx, uint8_t modes );

/**
 * @brief Enable low-power operation mode function
 *
 * @param ctx             Click object.    
 * @param clock_idle
 * <pre>
 *  Clock in Idle Mode:
 * - 0 : 32 kHz clock in Idle mode and thus has lower power consumption;
 * - 1 : 16 MHz clock in Idle mode and UART is always operationa;
 * </pre>
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function enable low-power operation mode
 */
RN4678_STATUS_T rn4678_enable_low_power_mode ( rn4678_t *ctx, uint8_t clock_idle );

/**
 * @brief Sets the length of time the device spends enabling discoverability function
 *
 * @param ctx     Click object.  
 * @param time    16-bit time the device spends enabling discoverability
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function sets the length of time the device spends enabling discoverability 
 */
RN4678_STATUS_T rn4678_discoverability ( rn4678_t *ctx, uint16_t time );

/**
 * @brief Set the device name function
 *
 * @param ctx     Click object.   
 * @param name    Pointer to the memory location where the name be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function sets the device name
 */
RN4678_STATUS_T rn4678_set_device_name ( rn4678_t *ctx, uint8_t *name );

/**
 * @brief Set security pin code function
 *
 * @param ctx     Click object.   
 * @param sp_code Pointer to the memory location where the security pin code string be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function set security pin code string to the
 * RN4678 Bluetooth� 4.2 dual mode module
 */
RN4678_STATUS_T rn4678_set_security_pin_code ( rn4678_t *ctx, uint8_t *sp_code );

/**
 * @brief Set the remote Bluetooth Classic address function
 *
 * @param ctx     Click object.   
 * @param r_addr  Pointer to the memory location where the remote classic bt address string be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function stores the remote Bluetooth Classic address to the
 * RN-41 Bluetooth module on Bluetooth Click board.
 *
 * @note
 * r_addr is string of the 12 hexadecimal digits
 */
RN4678_STATUS_T rn4678_set_remote_address ( rn4678_t *ctx, uint8_t *r_addr );

/**
 * @brief Set the remote Bluetooth BLE address function
 *
 * @param ctx       Click object.   
 * @param r_addr    Pointer to the memory location where the remote BLE address string be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function stores the remote BLE address to the
 * RN-41 Bluetooth module on Bluetooth Click board.
 *
 * @note
 * r_addr is string of the 12 hexadecimal digits
 */
RN4678_STATUS_T rn4678_set_remote_ble_address ( rn4678_t *ctx, uint8_t *r_addr );

/**
 * @brief Clear stored address function
 *
 * @param ctx       Click object.   
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function clears stored address function
 */
RN4678_STATUS_T rn4678_clear_stored_address ( rn4678_t *ctx );

/**
 * @brief Set the service name for Bluetooth Classic function
 *
 * @param ctx       Click object.   
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function sets the service name for Bluetooth Classic function
 */
RN4678_STATUS_T rn4678_set_service_name ( rn4678_t *ctx, uint8_t *service_name );

/**
 * @brief Set the baud rate function
 *
 * @param ctx       Click object.  
 * @param b_rate
 * <pre>
 * Baud rate :
 * -   2400 :   2400 bps;
 * -   4800 :   4800 bps;
 * -   9600 :   9600 bps;
 * -  14400 :  14400 bps;
 * -  19200 :  19200 bps;
 * -  38400 :  38400 bps;
 * -  57600 :  57600 bps [ Default ];
 * - 115200 : 115200 bps;
 * </pre>
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function set the baud rate value to the
 * RN4678 Bluetooth� 4.2 dual mode module
 */
RN4678_STATUS_T rn4678_set_baud_rate ( rn4678_t *ctx, uint32_t b_rate );

/**
 * @brief Enable BeaconThings feature function
 *
 * @param ctx       Click object. 
 * 
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function enable BeaconThings feature
 */
RN4678_STATUS_T rn4678_enable_beacon ( rn4678_t *ctx );

/**
 * @brief Disable BeaconThings feature function
 *
 * @param ctx       Click object. 
 * 
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function disable BeaconThings feature
 */
RN4678_STATUS_T rn4678_disable_beacon ( rn4678_t *ctx );

/**
 * @brief Set the serialized friendly name of the device function
 *
 * @param ctx  Click object.  
 * @param name Pointer to the memory location where the serial. friendly name of the device be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function sets the serialized friendly name of the device
 */
RN4678_STATUS_T rn4678_set_friendly_device_name ( uint8_t *name );

/**
 * @brief Enable role switch function
 *
 * @param ctx  Click object. 
 * 
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function enable role switch
 */
RN4678_STATUS_T rn4678_enable_role_switch ( rn4678_t *ctx );

/**
 * @brief Disable role switch function
 *
 * @param ctx  Click object. 
 * 
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function disable role switch
 */
RN4678_STATUS_T rn4678_disable_role_switch ( rn4678_t *ctx );

/**
 * @brief Set the configuration detect character string function
 *
 * @param ctx        Click object.  
 * @param dc_string  Pointer to the memory location where the detect character string be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function sets the configuration detect character string
 */
RN4678_STATUS_T rn4678_set_configuration ( rn4678_t *ctx, uint8_t *dc_string );

/**
 * @brief Displays basic settings function
 *
 * @param ctx       Click object.   
 * @param response Pointer to the memory location where the response be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function get the basic settings
 */
RN4678_STATUS_T rn4678_get_basic_settings ( rn4678_t *ctx, uint8_t *response );

/**
 * @brief Displays address of the device function
 *
 * @param ctx      Click object.  
 * @param response Pointer to the memory location where the response be stored
 *
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function get the address of the device
 */
RN4678_STATUS_T rn4678_get_device_address ( rn4678_t *ctx, uint8_t *response );

/**
 * @brief Displays current connection status of the device function
 *
 * @param ctx       Click object.  
 * 
 * @returns device_status
 * <pre>
 * - 0 : No iAP or BLE authentication;
 * - 1 : Successful authentication;
 * - 2 : APP open; Bluetooth connection over iAP ready;
 * - 3 : APP closed; no data transfer possible;
 * - 4 : On power-up, the authentication co-processor test failed;
 * - 5 : Authentication attempted and failed;
 * - 6 : BLE link authenticated;
 * </pre> 
 *
 * @description The function get the current connection status of the device
 */
uint8_t rn4678_get_device_status ( rn4678_t *ctx );

/**
 * @brief Enter Command mode function
 *
 * @param ctx       Click object.  
 * 
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function enter command mode
 */
RN4678_STATUS_T rn4678_enter_commandmode ( rn4678_t *ctx );

/**
 * @brief Exit Command mode function
 *
 * @param ctx       Click object.  
 * 
 * @retval status ( 0 : ERROR; 1 : OK )
 *
 * @description The function exit command mode
 */
RN4678_STATUS_T rn4678_exit_commandmode( rn4678_t *ctx );

/**
 * @brief Get interrupt state function
 *
 * @param ctx       Click object.  
 * 
 * @returns interrupt state ( 0 : not active, 1 : active )
 *
 * @description The function gets interrupt state
 * by return status of INT pin of on the RN4678 Bluetooth� 4.2 dual mode module
 */
uint8_t rn4678_get_interrupt ( rn4678_t *ctx );

/**
 * @brief Set states of RST pin to high function
 *
 * @param ctx       Click object.  
 * 
 * @description The function set states of RST pin to high
 */
void rn4678_set_rst ( rn4678_t *ctx );

/**
 * @brief Clear states of RST pin to high function
 *
 * @param ctx       Click object.  
 * 
 * @description The function clear states of RST pin to high
 */
void rn4678_clear_rst ( rn4678_t *ctx );

/**
 * @brief Set states of RTS pin to high function
 *
 * @param ctx       Click object.  
 * 
 * @description The function set states of RTS pin to high
 */
void rn4678_set_rts ( rn4678_t *ctx );

/**
 * @brief Clear states of RTS pin to high function
 *
 * @param ctx       Click object.  
 * 
 * @description The function clear states of RTS pin to high
 */
void rn4678_clear_rts ( rn4678_t *ctx );

/**
 * @brief Set states of PWM pin to high function
 *
 * @param ctx       Click object. 
 * 
 * @description The function set states of PWM pin to high
 */
void rn4678_set_pwm ( rn4678_t *ctx );

/**
 * @brief Clear states of PWM pin to high function
 *
 * @param ctx       Click object. 
 * 
 * @description The function clear states of PWM pin to high
 */
void rn4678_clear_pwm ( rn4678_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _RN4678_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
