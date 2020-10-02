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
 * \brief This file contains API for Fingerprint 3 Click driver.
 *
 * \addtogroup fingerprint3 Fingerprint 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FINGERPRINT3_H
#define FINGERPRINT3_H

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
#define FINGERPRINT3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FINGERPRINT3_RETVAL  uint8_t

#define FINGERPRINT3_OK           0x00
#define FINGERPRINT3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup confirmation_code  Confirmation code
 * \{
 */
#define FINGERPRINT3_OK                                             0x00
#define FINGERPRINT3_PACKET_RECIEVE_ERR                             0x01
#define FINGERPRINT3_NO_FINGER                                      0x02
#define FINGERPRINT3_IMAGE_FAIL                                     0x03
#define FINGERPRINT3_IMAGE_MESS                                     0x06
#define FINGERPRINT3_FEATURE_FAIL                                   0x07
#define FINGERPRINT3_NO_MATCH                                       0x08
#define FINGERPRINT3_NOT_FOUND                                      0x09
#define FINGERPRINT3_ENROLL_MIS_MATCH                               0x0A
#define FINGERPRINT3_BAD_LOCATION                                   0x0B
#define FINGERPRINT3_DB_RANGE_FAIL                                  0x0C
#define FINGERPRINT3_UPLOAD_FEATURE_FAIL                            0x0D
#define FINGERPRINT3_PACKET_RESPONSE_FAIL                           0x0E
#define FINGERPRINT3_UPLOAD_FAIL                                    0x0F
#define FINGERPRINT3_DELETE_FAIL                                    0x10
#define FINGERPRINT3_DB_CLEAR_FAIL                                  0x11
#define FINGERPRINT3_PASS_FAIL                                      0x13
#define FINGERPRINT3_INVALID_IMAGE                                  0x15
#define FINGERPRINT3_FLASH_ERR                                      0x18
#define FINGERPRINT3_INVALID_REG                                    0x1A
#define FINGERPRINT3_ADDR_CODE                                      0x20
#define FINGERPRINT3_PASS_VERIFY                                    0x21

#define FINGERPRINT3_START_CODE                                     0xEF01

#define FINGERPRINT3_COMMAND_PACKET                                 0x01
#define FINGERPRINT3_DATA_PACKET                                    0x02
#define FINGERPRINT3_ACK_PACKET                                     0x07
#define FINGERPRINT3_END_DATA_PACKET                                0x08

#define FINGERPRINT3_TIMEOUT                                        0xFF
#define FINGERPRINT3_BAD_PACKET                                     0xFE

#define FINGERPRINT3_GET_IMAGE                                      0x01
#define FINGERPRINT3_IMAGE_2_TZ                                     0x02
#define FINGERPRINT3_REG_MODEL                                      0x05
#define FINGERPRINT3_STORE                                          0x06
#define FINGERPRINT3_LOAD                                           0x07
#define FINGERPRINT3_UPLOAD                                         0x08
#define FINGERPRINT3_DELETE                                         0x0C
#define FINGERPRINT3_EMPTY                                          0x0D
#define FINGERPRINT3_SET_PASSWORD                                   0x12
#define FINGERPRINT3_VERIFY_PASSWORD                                0x13
#define FINGERPRINT3_HISPEED_SEARCH                                 0x04
#define FINGERPRINT3_TEMPLATE_COUNT                                 0x1D

#define FINGERPRINT3_RSP_READY                                      1
#define FINGERPRINT3_RSP_NOT_READY                                  0

#define FINGERPRINT3_EMPTY_LOG                                      0x00
/** \} */

/**
 * \defgroup finger_detection  Finger detection
 * \{
 */
#define FINGERPRINT3_DETECT_FINGER                                  0x00
#define FINGERPRINT3_DETECT_NO_FINGER                               0x01
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

typedef struct
{
    uint16_t header;
    uint32_t addr;
    uint8_t pkg_ident;
    uint16_t pkg_len;
    uint8_t confirm_code;
    uint8_t pkg_contents[ 256 ];
    uint16_t checksum;

} fingerprint3_rsp_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} fingerprint3_t;

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
    pin_name_t int_pin;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.     

} fingerprint3_cfg_t;

/**
 * @brief Error type 
 */

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
void fingerprint3_cfg_setup ( fingerprint3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
FINGERPRINT3_RETVAL fingerprint3_init ( fingerprint3_t *ctx, fingerprint3_cfg_t *cfg );

/**
 * @brief Set set RST pin state function
 *
 * @param ctx Click object.
 * @param pin_state
 * - 0 : Inactive.
 * - 1 : Active.
 *
 * @description The function set states of the RST pin 
 * of the Fingerprint 3 Click board.
 */
void fingerprint3_set_rst_pin ( fingerprint3_t *ctx, uint8_t rst_pin );

/**
 * @brief Generic write function.
 * 
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void fingerprint3_generic_write ( fingerprint3_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * 
 * @return Number of reads data.
 */
uint16_t fingerprint3_generic_read ( fingerprint3_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Process function.
 *
 * @param tmp        byte to be added to driver buffer.
 *
 * @description The function for collecting bytes and adds it to driver buffer.
 */
void fingerprint3_process ( uint8_t tmp );

/**
 * @brief Buffer clear function.
 *
 * @param tmp        byte to be added to driver buffer.
 *
 * @description The function for clearing driver buffer.
 */
void fingerprint3_buf_clear ( void );

/**
 * @brief Response parser and display function.
 *
 * @param response     pointer to the memory location where response be stored.
 *
 * @description The function parser and display device response
 * of the R503 Fingerprint Module on the Fingerprint 3 Click board.
 */
void fingerprint3_parser_and_display_rsp ( fingerprint3_rsp_t *response );

/**
 * @brief Response parser function.
 *
 * @param response     pointer to the memory location where response be stored.
 *
 * @description The function parser device response 
 * of the R503 Fingerprint Module on the Fingerprint 3 Click board.
 */
void fingerprint3_parser_rsp ( fingerprint3_rsp_t *response );

/**
 * @brief Finger indicator function.
 *
 * @param ctx Click object.
 * 
 * @return
 * ALERT state:
 * - 0 : No active.
 * - 1 : Active.
 *
 * Function check alert stauts.
 * of the High-Side Current-Sense and Dual 1�C
 * Temperature Monitor on Current 3 Click board.
 * When the ALERT pin is configured to operate in Comparator mode,
 * it will be asserted if any of the
 * measured temperatures meets or exceeds the respective high limit.
 */
uint8_t fingerprint3_finger_indicator ( fingerprint3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _FINGERPRINT3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
