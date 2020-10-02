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
 * \brief This file contains API for BLE 7 Click driver.
 *
 * \addtogroup ble7 BLE 7 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BLE7_H
#define BLE7_H

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
#define BLE7_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define BLE7_RETVAL  uint8_t

#define BLE7_OK           0x00
#define BLE7_INIT_ERROR   0xFF

#define BLE7_END_BUFF          0

#define BLE7_RSP_READY         1
#define BLE7_RSP_NOT_READY     0
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define BLE7_MODULE_POWER_ON   1
#define BLE7_MODULE_POWER_OFF  0
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
 * @brief Handler definition.
 */
typedef void ( *ble7_hdl_t )( uint8_t* );

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    digital_out_t gp1;
    digital_out_t cts;

    // Input pins 

    digital_in_t gp0;
    digital_in_t rts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

    uint8_t  rsp_rdy;
    ble7_hdl_t  driver_hdl;

} ble7_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t gp0;
    pin_name_t rst;
    pin_name_t rts;
    pin_name_t gp1;
    pin_name_t cts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} ble7_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t ble7_error_t;

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
void ble7_cfg_setup ( ble7_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BLE7_RETVAL ble7_init ( ble7_t *ctx, ble7_cfg_t *cfg );

/**
 * @brief Reset function
 *
 * @description This function allows user to reset BGX module.
 */
void ble7_reset ( ble7_t *ctx );

/**
 * @brief Generic write function.

 * @param ctx         Click object.
 * @param data_buf    Data buffer for sends.
 * @param len         Number of bytes for sends.
 *
 * @description This function write specific number of bytes
 */
void ble7_generic_write ( ble7_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.

 * @param ctx         Click object.
 * @param data_buf    Data buffer for read data.
 * @param max_len     The maximum length of data that can be read.
 *
 * @returns Number of reads data.
 *
 * @description This function read maximum length of data.
 */
int32_t ble7_generic_read ( ble7_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Transmit function
 *
 * @param ctx         Click object. 
 * @param tx_data     Data to be transmitted
 *
 * @description This function allows user to transmit data to the BGX module.
 *
 * @note 
 * This function will send '\r' character automatically at the end of the tx_data transmitting.
 */
void ble7_send_command ( ble7_t *ctx, char *command );

/**
 * @brief Handler Setting function
 *
 * @param ctx         Click object.  
 * @param handler     Pointer to the function which should be performed to get response
 *
 * @description This function sets handler on the function which should be performed,
 * for example function for the results logging.
 */
void ble7_response_handler_set ( ble7_t *ctx, void ( *handler )( uint8_t* ) );

/**
 * @brief UART ISR function
 *
 * @param ctx         Click object. 
 *
 * @description This function reads response bytes from the BGX module and sets flag after 
 * each received byte.
 */
void ble7_uart_isr ( ble7_t *ctx, uint8_t rx_dat );

/**
 * @brief Response Ready function
 *
 * @param ctx         Click object. 
 * 
 * @returns 0 - response is not ready, 1 - response is ready
 *
 * @description This function checks does response ready or not.
 */
uint8_t ble7_response_ready ( ble7_t *ctx );

/**
 * @brief GP0 Pin Getting function
 *
 * @param ctx         Click object. 
 * 
 * @returns 0 or 1
 *
 * @description This function checks state of the GP0 pin.
 */
uint8_t ble7_get_gp0 ( ble7_t *ctx );

/**
 * @brief RTS Pin Getting function
 *
 * @param ctx         Click object. 
 * 
 * @returns 0 or 1
 *
 * @description This function checks state of the RTS pin.
 */
uint8_t ble7_get_rts ( ble7_t *ctx );

/**
 * @brief GP1 Pin Setting function
 *
 * @param ctx         Click object.  
 * @param state       0 or 1
 *
 * @description This function sets GP1 pin to the desired state.
 */
void ble7_set_gp1 ( ble7_t *ctx, uint8_t state );

/**
 * @brief CTS Pin Setting function
 *
 * @param ctx         Click object.  
 * @param state       0 or 1
 *
 * @description This function sets CTS pin to the desired state.
 */
void ble7_set_cts ( ble7_t *ctx, uint8_t state );

void ble7_receive_command( ble7_t *ctx, char* data_buf);

#ifdef __cplusplus
}
#endif
#endif  // _BLE7_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
