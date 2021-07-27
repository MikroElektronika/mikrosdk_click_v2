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
 * \brief This file contains API for G2C Click driver.
 *
 * \addtogroup g2c G2C Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef G2C_H
#define G2C_H

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
#define G2C_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define G2C_RETVAL  uint8_t

#define G2C_OK           0x00
#define G2C_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup parser_error Parser error
 * \{
 */
#define G2C_PARSER_NO_ERROR    0x00
#define G2C_PARSER_ERROR_REF   0x01
#define G2C_PARSER_ERROR_CMD   0x02
#define G2C_PARSER_ERROR_DATA  0x04
/** \} */

/**
 * \defgroup click_status G2C 3G click status
 * \{
 */
#define G2C_STATUS_DEVICE_READY            1
#define G2C_STATUS_ACT_NETWORK_AND_BROKER  4
#define G2C_STATUS_ACT_NETWORK             2
#define G2C_STATUS_ACT_BROKER              3
#define G2C_STATUS_DEVICE_BUSY             0
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define G2C_MODULE_POWER_ON   1
#define G2C_MODULE_POWER_OFF  0
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

    // Input pins 

    digital_in_t rts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} g2c_t;

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
    pin_name_t cts;
    pin_name_t rts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} g2c_cfg_t;

/**
 * @brief Error type 
 */
// Actuator switch type
typedef uint8_t g2c_actuator_sw_t;

// Actuator counter type
typedef int16_t g2c_actuator_cnt_t;

// Actuator string type
typedef char g2c_actuator_str_t;

// Parser error type
typedef uint8_t g2c_error_t;

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
 * @param cfg           Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void g2c_cfg_setup ( g2c_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param g2c           Click object.
 * @param cfg           Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
G2C_RETVAL g2c_init ( g2c_t *ctx, g2c_cfg_t *cfg );

/**
 * @brief Power module.
 * 
 * @param g2c           Click object.
 * @param power_state   State of pin.
 * @param bootloader    Bootloader ( 0 or 1 ).
 */
void g2c_module_power( g2c_t *ctx, uint8_t power_state, uint8_t bootloader );

/**
 * @brief Reset module.
 * 
 * @param g2c           Click object.
 */
void g2c_reset ( g2c_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param g2c           Click object.
 * @param data_buf      Data buffer for sends.
 * @param len           Number of bytes for sends.
 */
void g2c_generic_write ( g2c_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param g2c           Click object.
 * @param data_buf      Data buffer for read data.
 * @param max_len       The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
int32_t g2c_generic_read ( g2c_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Function for send command.
 * 
 * @param g2c           Click object.
 * @param command       Command to send.
 */
void g2c_send_command ( g2c_t *ctx, char *command );

/**
 * @brief Operater ( Network ) configuration.
 * 
 * @param g2c           Click object.
 * @param op_username   Network username.
 * @param op_password   Network password.
 */
void g2c_send_operator_cfg( g2c_t *ctx, char *op_username, char *op_password );

/**
 * @brief Broker configuration.
 * 
 * @param g2c           Click object.
 * @param brc_key       Device key.
 * @param brc_password  Device password.
 */
void g2c_send_broker_cfg( g2c_t *ctx, char *brc_key, char *brc_password );

/**
 * @brief Send data reference.
 * 
 * @param g2c           Click object.
 * @param reference_buf Reference.
 * @param data_buf      
 */
void g2c_send_data_ref(  g2c_t *ctx, char *reference_buf, char *data_buf );

/**
 * @brief Switch parser function.
 * 
 * @param g2c           Click object.
 * @param act_ref       Actuator reference.
 * @param sw_state      Switch state of pin.
 * 
 * @return error data
 */
g2c_error_t g2c_actuator_sw_parser ( char *rsp, char *act_ref, g2c_actuator_sw_t *sw_state );

/**
 * @brief Counter parser function.
 * 
 * @param g2c           Click object.
 * @param act_ref       Actuator reference.
 * @param num_data      Number of data.
 * 
 * @return error data
 */
g2c_error_t g2c_actuator_cnt_parser ( char *rsp, char *act_ref, g2c_actuator_cnt_t *num_data );

/**
 * @brief String parser function.
 * 
 * @param g2c           Click object.
 * @param act_ref       Actuator reference.
 * @param str_data      String to send.
 * 
 * @return error data
 */
g2c_error_t g2c_actuator_str_parser ( char *rsp, char *act_ref, g2c_actuator_str_t *str_data );

#ifdef __cplusplus
}
#endif
#endif  // _G2C_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
