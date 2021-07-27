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
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FT_RETVAL  uint8_t

#define FT_OK                         0x00
#define FT_INIT_ERROR                 0xFF
/** \} */

/**
 * \defgroup data_structure Data Structure
 * \{
 */
#define DRV_HEADER_DATA               0x40
#define DRV_HEADER_LEN                0x05
#define DRV_DATA_CRC_LEN              0x02
/** \} */

/**
 * \defgroup status Status
 * \{
 */
#define DRV_NEW_DATA_AVAILABLE        1
#define DRV_CONFIRMED_PACKAGE         1
#define DRV_CHACK_HEDER_DATA_1        0
#define DRV_CHACK_HEDER_DATA_2        1
#define DRV_CHACK_LEN_DATA_LSB        2
#define DRV_CHACK_LEN_DATA_MSB        3
/** \} */

/**
 * \defgroup extern_status Extern Status
 * \{
 */
#define FT_NEW_DATA_AVAILABLE         1
#define FT_NEW_DATA_NOT_AVAILABLE     0
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE            500
#define MAX_DATA_BUFFER               512
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

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

    // Response flags
   uint8_t drv_new_data;
   uint8_t drv_start_package;
   uint8_t drv_rsp_buff[ MAX_DATA_BUFFER ];
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

/** \} */ // End types group
// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */

static const uint16_t CRC_TABLE[ 256 ] =
{
    0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
    0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
    0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
    0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
    0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
    0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
    0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
    0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
    0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
    0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
    0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
    0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
    0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
    0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
    0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
    0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
    0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
    0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
    0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
    0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
    0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
    0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
    0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
    0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
    0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
    0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
    0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
    0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
    0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
    0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
    0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
    0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040
};

/** \} */ // End variable group
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
void ft_cfg_setup ( ft_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
FT_RETVAL ft_init ( ft_t *ctx, ft_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Ft click.
 */
void ft_default_cfg ( ft_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 *
 * @description This function write specific number of data.
 */
void ft_generic_write ( ft_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 *
 * @returns Number of reads data.
 *
 * @description This function read data of maximum length.
 */
int32_t ft_generic_read ( ft_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Set RST pin state
 *
 * @param ctx  Click object. 
 * @param state RST pin state [ 0 or 1 ]
 *
 * @description Use this function for set new RST pin state
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
 * @description Use this function for send data to other module
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
 * @description Use this function for gets current status of data
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
 * @description Use this function for read received data
 * @note This function returns only the received data and not the full received packet.
 */
uint16_t ft_get_data ( ft_t *ctx, uint8_t *data_buf );

/**
 * @brief Collecting and preserving data received via uart interrupt routine
 *
 * @param ctx       Click object.  
 * @param rsp_data  One byte data that received via uart
 *
 * @description Used this function for collect and preser new data
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
