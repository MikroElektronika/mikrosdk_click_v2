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
 * \brief This file contains API for RN4870 Click driver.
 *
 * \addtogroup rn4870 RN4870 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RN4870_H
#define RN4870_H

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
#define RN4870_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.uart_rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.uart_cts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RN4870_RETVAL  uint8_t

#define RN4870_OK           0x00
#define RN4870_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
/** \} */

/**
 * \defgroup variables Variables
 * \{
 */
#define RN4870_DEVICETYPE_MASTER                         0x01
#define RN4870_DEVICETYPE_SLAVE                          0x02
#define RN4870_ID_MASTER                                 0x35
#define RN4870_ID_SLAVE                                  0x32
#define RN4870_MTYPE_MSG                                 'M'
#define RN4870_DTYPE_STRING                              0x5331
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
    digital_out_t uart_rts;
    digital_out_t pwm;

    // Input pins 

    digital_in_t uart_cts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

    char device_buffer[ 255 ];
    uint8_t end_flag;
    uint8_t sen_flag;
    uint8_t tmp_pos;

} rn4870_t;

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
    pin_name_t uart_rts;
    pin_name_t pwm;
    pin_name_t uart_cts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} rn4870_cfg_t;

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
void rn4870_cfg_setup ( rn4870_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RN4870_RETVAL rn4870_init ( rn4870_t *ctx, rn4870_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Rn4870 click.
 */
void rn4870_default_cfg ( rn4870_t *ctx );

/**
 * @brief Hardware reset function
 *
 * @param ctx  Click object.
 * 
 * @description The function Hardware reset - resets the RN4870 Bluetooth� 4.2 low energy module
 * by cleared to '0' RST state pin, wait for 100 ms, set to '1' RST state pin and wait for 200 ms.
 *
 * @note
 * Delay is 300 ms.
 */
void rn4870_reset ( rn4870_t *ctx );

/**
 * @brief Generic write function
 *
 * @param ctx         Click object.
 * @param data_buf    Buffer to be write.
 * @param len         Length of data to be write.
 *
 * @description This function write buffer of specific length
 */
void rn4870_generic_write ( rn4870_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function
 *
 * @param ctx       Click object.
 * @param data_buf  Buffer to be write.
 * @param max_len   Length of data to be read.
 *
 * @description This function read buffer of maximum length
 */
int16_t rn4870_generic_read ( rn4870_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief UART write function
 *
 * @param ctx       Click object.
 * @param tx_data   Tx buffer 
 *
 * @description This function is for UART writing 
 */
void rn4870_uart_write ( rn4870_t *ctx, uint8_t *tx_data );

/**
 * @brief Initialization RN4870 module
 *
 * @param ctx            Click object.
 * @param dev_addr       Pointer to the memory location where dev_addr be stored
 *
 * @description The function initializes RN4870 Bluetooth� 4.2 low energy module
 * by resets the RN4870 module, disable I2C communications pins,
 * reboots the device for change to take effect, enters CMD mode again,
 * and sets the address of the device.
 */
void rn4870_initialize ( rn4870_t *ctx, char *dev_addr );

/**
 * @brief Connecting to slave device
 *
 * @param ctx       Click object. 
 * @param dev_addr  Pointer to the memory location where slave device with be stored
 *
 * @description The function connects to slave device with desired register address
 * by secures the connection and entering data stream mode.
 */
void rn4870_connect ( rn4870_t *ctx, char *dev_addr );

/**
 * @brief Disconnecting from slave device
 *
 * @param ctx  Click object.
 * 
 * @description The function disconnects from slave device
 * by enters CMD mode and kills connection.
 */
void rn4870_disconnect ( rn4870_t *ctx );

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
void rn4870_send ( rn4870_t *ctx, uint8_t msg_type, uint16_t data_type, uint8_t dev_id, uint8_t *tx_data );

/**
 * @brief Receiving character function
 *
 * @param ctx                   Click object. 
 * @param character             Received character
 *
 * @description The function receives character by
 * waits for '#' - character to start parsing message,
 * waits for '*' - character to stop parsing message
 * and sets flag if whole and properly formated message is received.
 */
void rn4870_receive ( rn4870_t *ctx, char character );

/**
 * @brief Read received message function
 *
 * @param ctx                   Click object. 
 * @param rx_data               pointer to the memory location where the read text data is stored
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
uint8_t rn4870_read ( rn4870_t *ctx, uint8_t *rx_data );

/**
 * @brief Get interrupt state function
 *
 * @param ctx  Click object.
 * 
 * @returns interrupt state ( 0 : not active, 1 : active )
 *
 * @description The function gets interrupt state by return status of INT pin.
 */
uint8_t rn4870_get_interrupt ( rn4870_t *ctx );

/**
 * @brief Set states of RST pin to high function
 *
 * @param ctx  Click object.
 * 
 * @description The function set states of RST pin to high.
 */
void rn4870_set_rst ( rn4870_t *ctx );

/**
 * @brief Clear states of RST pin function
 *
 * @param ctx  Click object.
 * 
 * @description The function clear states of RST pin by sets states of RST pin to low.
 */
void rn4870_clear_rst ( rn4870_t *ctx );

/**
 * @brief Set states of RTS pin function
 *
 * @param ctx  Click object.
 * 
 * @description The function set states of RST pin by sets states of CS pin to high.
 */
void rn4870_set_rts ( rn4870_t *ctx );

/**
 * @brief Clear states of RTS pin function
 *
 * @param ctx  Click object.
 * 
 * @description The function clear states of RTS pin by sets states of CS pin to low.
 */
void rn4870_clear_rts ( rn4870_t *ctx );

/**
 * @brief Set states of PWM pin function
 *
 * @param ctx  Click object.
 * 
 * @description The function set states of PWM pin by sets states of PWM pin to high.
 */
void rn4870_set_pwm ( rn4870_t *ctx );

/**
 * @brief Clear states of PWM pin function
 *
 * @param ctx  Click object.
 * 
 * @description The function clear states of PWM pin by sets states of PWM pin to low.
 */
void rn4870_clear_pwm ( rn4870_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _RN4870_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
