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
 * \brief This file contains API for Fingerprint 2 Click driver.
 *
 * \addtogroup fingerprint2 Fingerprint 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FINGERPRINT2_H
#define FINGERPRINT2_H

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
#define FINGERPRINT2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.ld1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.gp2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.ld2 = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FINGERPRINT2_RETVAL  uint8_t

#define FINGERPRINT2_OK           0x00
#define FINGERPRINT2_INIT_ERROR   0xFF
/** \} */


/**
 * \defgroup cmd Command
 * \{
 */
#define FINGERPRINT2_CMD_GET_FW_VER       "<C>GetFWVer</C>"
#define FINGERPRINT2_CMD_GET_DS           "<C>GetDS</C>"
#define FINGERPRINT2_CMD_FP_CMP           "<C>CompareFingerprint</C>"
#define FINGERPRINT2_CMD_FP_REG           "<C>RegisterFingerprint</C>"
#define FINGERPRINT2_CMD_FP_CLR           "<C>ClearRegisteredFp</C>"
#define FINGERPRINT2_CMD_FP_IMG_INFO      "<C>FpImageInformation</C>"
#define FINGERPRINT2_CMD_FP_IMG_SCAN      "<C>ScanFpImage</C>"
#define FINGERPRINT2_CMD_FP_REG_NO        "<C>CheckRegisteredNo</C>"
#define FINGERPRINT2_CMD_LOCK_DEV         "<C>LockDevice</C>"
#define FINGERPRINT2_CMD_UNLOCK_DEV       "<C>UnlockCompareFp</C>"
/** \} */

/**
 * \defgroup other_macros Other macros
 * \{
 */
#define MOD_NUM                           10
#define VAL_CHAR                          48
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 800
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
    digital_out_t gp1;
    digital_out_t gp2;

    // Input pins 

    digital_in_t ld1;
    digital_in_t ld2;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} fingerprint2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t ld1;
    pin_name_t rst;
    pin_name_t gp1;
    pin_name_t gp2;
    pin_name_t ld2;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} fingerprint2_cfg_t;

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
void fingerprint2_cfg_setup ( fingerprint2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
FINGERPRINT2_RETVAL fingerprint2_init ( fingerprint2_t *ctx, fingerprint2_cfg_t *cfg );

/**
 * @brief Generic write function.

 * @param ctx         Click object.
 * @param data_buf    Data buffer for sends.
 * @param len         Number of bytes for sends.
 *
 * @description This function write specific number of bytes
 */
void fingerprint2_generic_write ( fingerprint2_t *ctx, char *data_buf, uint16_t len );

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
int32_t fingerprint2_generic_read ( fingerprint2_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Generic function for reading ld1 pin status
 *
 * @param ctx  Click object.
 * 
 * @returns Pin status.
 *
 * @description This function read ld1 pin status.
 */
uint8_t fingerprint2_get_ld1_status ( fingerprint2_t *ctx );

/**
 * @brief Generic function for reading ld2 pin status
 *
 * @param ctx  Click object.
 * 
 * @returns Pin status
 *
 * @description This function read ld2 pin status
 */
uint8_t fingerprint2_get_ld2_status ( fingerprint2_t *ctx );

/**
 * @brief Generic function for setting rst pin status
 *
 * @param ctx              Click object. 
 * @param status           State of the pin
 *
 * @description This function sets rst pin status. 
 */
void fingerprint2_set_rst_status ( fingerprint2_t *ctx, uint8_t status );

/**
 * @brief Generic function for setting gp1 pin status
 *
 * @param ctx              Click object. 
 * @param status           State of the pin.
 *
 * @description This function sets gp1 pin status.
 */
void fingerprint2_set_gp1_status ( fingerprint2_t *ctx, uint8_t status );

/**
 * @brief Generic function for setting gp2 pin status
 *
 * @param ctx              Click object. 
 * @param status           state of the pin
 *
 * @description This function sets gp2 pin status.
 */
void fingerprint2_set_gp2_status ( fingerprint2_t *ctx, uint8_t status );

/**
 * @brief Function for restarting device
 *
 * @param ctx  Click object.
 *
 * @description This function restarts device.
 */
void fingerprint2_reset ( fingerprint2_t *ctx );

/**
 * @brief Function for fingerprint registration on index
 *
 * @param ctx                Click object. 
 * @param fp_index           Fingerprint index
 *
 * @description This function registrates fingerprint on index.
 */
void fingerprint2_reg_one_fp ( fingerprint2_t *ctx, uint8_t fp_index );

/**
 * @brief Function for deleting fingerprint on index
 *
 * @param ctx                Click object. 
 * @param fp_index           Fingerprint index
 *
 * @description This function deletes fingerprint on index
 */
void fingerprint2_delete_one_fp ( fingerprint2_t *ctx, uint8_t fp_index );

#ifdef __cplusplus
}
#endif
#endif  // _FINGERPRINT2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
