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
 * \brief This file contains API for XSENS MTi 3 Click driver.
 *
 * \addtogroup xsensmti3 XSENS MTi 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef XSENSMTI3_H
#define XSENSMTI3_H

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
#define XSENSMTI3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.syn = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define XSENSMTI3_RETVAL  uint8_t

#define XSENSMTI3_OK           0x00
#define XSENSMTI3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup process PROCESS
 * \{
 */
#define XSENSMTI3_WAIT_FOR_START      0x00
#define XSENSMTI3_START_PROCESS       0x01
#define XSENSMTI3_DATA_PROCESSING     0x02
#define XSENSMTI3_PARSER_DATA         0x03
/** \} */

/**
 * \defgroup for_pic MIKROC PRO FOR PIC
 * \{
 */
#ifdef MIKROC_PRO_FOR_PIC

  #define DBL_MAX                     6.80564713e+38
  #define EXCESS                      126
  #define MAX_EXPONENT                255

  #define _FRNDINT(x)                 ( ( double ) ( long ) ( x ) )
  #define DBL_MANT_DIG                24
  #define CHAR_BIT                    8

  #define DBL_MAX                     6.80564713e+38
  #define EXP_MAX                     89.415986
  #define EXP_MIN                    -87.336544

  #define PI                          3.14159265358979
  #define TWO_PI                      6.28318530717958
  #define HALF_PI                     1.570796326794895

#else               

  #define DBL_MAX                     3.40282347e+38
  #define EXCESS                      126
  #define MAX_EXPONENT                255

  #define _FRNDINT(x)                 ( ( double ) ( long ) ( x ) )
  #define DBL_MANT_DIG                23
  #define CHAR_BIT                    8

  #define EXP_MAX                     89.416
  #define EXP_MIN                    -87.33655

  #define PI                          3.14159265358979
  #define TWO_PI                      6.28318530717958
  #define HALF_PI                     1.570796326794895

#endif
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

    digital_out_t syn;
    digital_out_t rst;
    digital_out_t cs;
    digital_out_t rts;

    // Input pins 

    digital_in_t cts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} xsensmti3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t syn;
    pin_name_t rst;
    pin_name_t cs;
    pin_name_t rts;
    pin_name_t cts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} xsensmti3_cfg_t;

/**
 * @brief Click quat structure definition.
 */
typedef struct
{
    uint16_t data_id;
    uint32_t raw_data[ 4 ];
    float quat_data[ 4 ];

} xsensmti3_quat_t;

/**
 * @brief Click 32-bit data structure definition.
 */
typedef struct
{
    uint16_t data_id;
    uint32_t out_data;

} xsensmti3_u32_data_t;

/**
 * @brief Click 16-bit data structure definition.
 */
typedef struct
{
    uint16_t data_id;
    uint16_t out_data;

} xsensmti3_u16_data_t;

/**
 * @brief Click parse structure definition.
 */
typedef struct
{
    uint32_t package_header;
    xsensmti3_quat_t     quat_obj;
    xsensmti3_u32_data_t time_obj;
    xsensmti3_u32_data_t status_obj;
    xsensmti3_u16_data_t package_obj;
    uint8_t crc_data;

} xsensmti3_parse_t;

/**
 * @brief Click roll/pitch/yaw structure definition.
 */
typedef struct
{
    float roll;
    float pitch;
    float yaw;

} xsensmti3_data_t;

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
void xsensmti3_cfg_setup ( xsensmti3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
XSENSMTI3_RETVAL xsensmti3_init ( xsensmti3_t *ctx, xsensmti3_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx         Click object.
 * @param data_buf    Data buffer for send.
 * @param len         Number of bytes for send.
 *
 * @description This function write specific number of bytes
 */
void xsensmti3_generic_write ( xsensmti3_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx         Click object.
 * @param data_buf    Data buffer for read data.
 * @param max_len     The maximum length of data that can be read.
 *
 * @returns Number of read data.
 *
 * @description This function read maximum length of data.
 */
int32_t xsensmti3_generic_read ( xsensmti3_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief General Parser
 *
 * @param ctx            Click object. 
 * @param rsp_buf        Response buffer.
 * @param start_cnt      Element from which the package starts.
 * @param obj            Parse object for collecting data.
 *
 * @description This function parses object for collecting data.
 */
void xsensmti3_parser ( uint8_t *rsp_buf, uint8_t start_cnt, xsensmti3_parse_t *obj );

/**
 * @brief Get Roll, Pitch and Yaw
 *
 * @param ctx            Click object.  
 * @param quat_obj       Quat objest structure.
 * @param data_obj       Output object for collecting data.
 *
 * @description This function get roll, pitch and yaw values.
 */
void xsensmti3_get_data( xsensmti3_quat_t *quat_obj, xsensmti3_data_t *data_obj );

/**
 * @brief Checks package
 *
 * @param ctx            Click object.  
 * @param package_buf    Package buffer.
 * @param start_package  Element from which the package starts.
 * 
 * @description This function check for the starting elements.
 */
uint8_t xsensmti3_check_package( uint8_t *package_buf, uint8_t *start_package );


#ifdef __cplusplus
}
#endif
#endif  // _XSENSMTI3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
