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
 * \brief This file contains API for FT Click driver.
 *
 * \addtogroup ft FT Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FT_H
#define FT_H

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
#define FT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FT_OK                           0
#define FT_ERROR                       -1
/** \} */

/**
 * \defgroup data_structure Data Structure
 * \{
 */
#define FT_DRV_HEADER_DATA              0x40
#define FT_DRV_HEADER_LEN               5
#define FT_DRV_DATA_CRC_LEN             2
/** \} */

/**
 * \defgroup status Status
 * \{
 */
#define FT_DRV_NEW_DATA_AVAILABLE       1
#define FT_DRV_CONFIRMED_PACKAGE        1
#define FT_DRV_CHECK_HEADER_DATA_1      0
#define FT_DRV_CHECK_HEADER_DATA_2      1
#define FT_DRV_CHECK_LEN_DATA_LSB       2
#define FT_DRV_CHECK_LEN_DATA_MSB       3
/** \} */

/**
 * \defgroup extern_status Extern Status
 * \{
 */
#define FT_NEW_DATA_AVAILABLE           1
#define FT_NEW_DATA_NOT_AVAILABLE       0
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define FT_DRV_BUFFER_SIZE              ( FT_MAX_DATA_BUFFER + FT_DRV_HEADER_LEN + FT_DRV_DATA_CRC_LEN )
#define FT_MAX_DATA_BUFFER              256
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

    uint8_t uart_rx_buffer[ FT_DRV_BUFFER_SIZE ];
    uint8_t uart_tx_buffer[ FT_DRV_BUFFER_SIZE ];

    // Response flags
    uint8_t drv_new_data;
    uint8_t drv_start_package;
    uint8_t drv_rsp_buff[ FT_MAX_DATA_BUFFER ];
    uint8_t drv_rsp_flag;
    uint16_t drv_buff_cnt;
    uint16_t drv_rsp_lenght;

} ft_t;

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

} ft_cfg_t;

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
void ft_cfg_setup ( ft_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t ft_init ( ft_t *ctx, ft_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 *
 * @details This function write specific number of data.
 */
void ft_generic_write ( ft_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 *
 * @returns Number of reads data.
 *
 * @details This function read data of maximum length.
 */
int32_t ft_generic_read ( ft_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief Set RST pin state
 *
 * @param ctx  Click object. 
 * @param state RST pin state [ 0 or 1 ]
 *
 * @details Use this function to set new RST pin state
 */
void ft_set_rst_pin ( ft_t *ctx, uint8_t state );

/**
 * @brief Sends full package to other module
 *
 * @param ctx         Click object. 
 * @param data_buf    Buffer with data that will be sends
 * @param len         Number of data in the data buffer
 * @param queue       Queue value for this package
 *
 * @details Use this function to send data to other module
 *
 * @note Package format contains:
 * <pre>
 *    [0] - Header data [ '@' - 0x40 ] 
 *    [1] - Header data [ '@' - 0x40 ]
 *    [2] - Package lenth LSB
 *    [3] - Package lenth MSB
 *    [4] - Package queue - param(queue)
 *    [ 5 -> param( len ) ] - Data for sends [ param( data_buf ) ]
 *    [ param( len ) + 1 ] - CRC data LSB
 *    [ param( len ) + 2 ] - CRC data MSB
 * </pre>
 */
void ft_send_package ( ft_t *ctx, uint8_t *data_buf, uint16_t len, uint8_t queue );

/**
 * @brief Gets current status of data
 *
 * @param ctx         Click object. 
 * 
 * @returns current data status [ new data package available or not]
 *
 * @details Use this function to get current status of data
 */
uint8_t ft_get_data_status ( ft_t *ctx );

/**
 * @brief Gets new received data
 *
 * @param ctx         Click object.  
 * @param data_buf    Pointer to the buffer in which the received data will be stored
 *
 * @returns number of data that received
 *
 * @details Use this function to read received data
 * @note This function returns only the received data and not the full received packet.
 */
uint16_t ft_get_data ( ft_t *ctx, uint8_t *data_buf );

/**
 * @brief Collecting and preserving data received via uart interrupt routine
 *
 * @param ctx       Click object.  
 * @param rsp_data  One byte data that received via uart
 *
 * @details Used this function to collect and preserve new data
 *
 * @note This function must be called as soon as possible
 */
void ft_isr_parser ( ft_t *ctx, uint8_t rsp_data );

#ifdef __cplusplus
}
#endif
#endif  // _FT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
