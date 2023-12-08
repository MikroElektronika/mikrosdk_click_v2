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
 * \brief This file contains API for BLE 3 Click driver.
 *
 * \addtogroup ble3 BLE 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef BLE3_H
#define BLE3_H

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
#define BLE3_MAP_MIKROBUS( cfg, mikrobus ) \
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
#define BLE3_RETVAL  uint8_t

#define BLE3_OK           0x00
#define BLE3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup parser_error Parser error
 * \{
 */
#define BLE3_PARSER_NO_ERROR    0x00
#define BLE3_PARSER_ERROR_REF   0x01
#define BLE3_PARSER_ERROR_CMD   0x02
#define BLE3_PARSER_ERROR_DATA  0x04
/** \} */

/**
 * \defgroup click_status G2C 3G click status
 * \{
 */
#define BLE3_STATUS_DEVICE_READY            1
#define BLE3_STATUS_ACT_NETWORK_AND_BROKER  4
#define BLE3_STATUS_ACT_NETWORK             2
#define BLE3_STATUS_ACT_BROKER              3
#define BLE3_STATUS_DEVICE_BUSY             0
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define BLE3_MODULE_POWER_ON   1
#define BLE3_MODULE_POWER_OFF  0
/** \} */

/**
 * \defgroup at_command AT command 
 * \{
 */
#define BLE3_SINGLE_CMD_AT        "AT"
#define BLE3_SINGLE_CMD_AT_W      "AT+W"
#define BLE3_SINGLE_CMD_AT_R      "AT+R"
#define BLE3_SINGLE_CMD_ATE0      "ATE0"
#define BLE3_SINGLE_CMD_ATE1      "ATE1"
#define BLE3_SINGLE_CMD_AT_RST    "AT+RST"
#define BLE3_SINGLE_CMD_AT_CRST   "AT+CRST"
#define BLE3_SINGLE_CMD_AT_GMR    "AT+GMR"
#define BLE3_SINGLE_CMD_AT_GMSTA  "AT+GMSTA"
#define BLE3_SINGLE_CMD_AT_PUB    "AT+PUB"

#define BLE3_SINGLE_CMD_SET_AT_LRSP_1 "AT+LRSP=1"
#define BLE3_SINGLE_CMD_SET_AT_LRSP_0 "AT+LRSP=0"
#define BLE3_SINGLE_CMD_SET_AT_CEN_1  "AT+CEN=1"
#define BLE3_SINGLE_CMD_SET_AT_CEN_0  "AT+CEN=0"
#define BLE3_SINGLE_CMD_SET_AT_NWC_1  "AT+NWC=1"
#define BLE3_SINGLE_CMD_SET_AT_NWC_0  "AT+NWC=0"
#define BLE3_SINGLE_CMD_SET_AT_BRC_1  "AT+BRC=1"
#define BLE3_SINGLE_CMD_SET_AT_BRC_0  "AT+BRC=0"
#define BLE3_SINGLE_CMD_SET_AT_GPEN_0 "AT+GPEN=0"
#define BLE3_SINGLE_CMD_SET_AT_GPEN_1 "AT+GPEN=1"

#define BLE3_SINGLE_CMD_GET_AT_LRSP "AT+LRSP?"
#define BLE3_SINGLE_CMD_GET_AT_CEN  "AT+CEN?"
#define BLE3_SINGLE_CMD_GET_AT_NWC  "AT+NWC?"
#define BLE3_SINGLE_CMD_GET_AT_BRC  "AT+BRC?"
#define BLE3_SINGLE_CMD_GET_AT_GPEN "AT+GPEN?"
#define BLE3_SINGLE_CMD_GET_AT_NWCR "AT+NWCR?"
#define BLE3_SINGLE_CMD_GET_AT_BRCR "AT+BRCR?"
#define BLE3_SINGLE_CMD_GET_AT_DSET "AT+DSET?"

#define BLE3_SINGLE_CMD_TEST_AT_LRSP "AT+LRSP=?"
#define BLE3_SINGLE_CMD_TEST_AT_CEN  "AT+CEN=?"
#define BLE3_SINGLE_CMD_TEST_AT_NWC  "AT+NWC=?"
#define BLE3_SINGLE_CMD_TEST_AT_BRC  "AT+BRC=?"
#define BLE3_SINGLE_CMD_TEST_AT_GPEN "AT+GPEN=?"
#define BLE3_SINGLE_CMD_TEST_AT_NWCR "AT+NWCR=?"
#define BLE3_SINGLE_CMD_TEST_AT_BRCR "AT+BRCR=?"
#define BLE3_SINGLE_CMD_TEST_AT_DSET "AT+DSET=?"

#define BLE3_MULTI_CMD_AT_DSET "AT+DSET"
#define BLE3_MULTI_CMD_AT_BRCR "AT+BRCR"
#define BLE3_MULTI_CMD_AT_NWCR "AT+NWCR"
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
    digital_out_t rts;

    // Input pins 

    digital_in_t cts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];

} ble3_t;

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

} ble3_cfg_t;

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
void ble3_cfg_setup ( ble3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
BLE3_RETVAL ble3_init ( ble3_t *ctx, ble3_cfg_t *cfg );

/**
 * @brief Generic write function.
 * @param ble3 Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void ble3_generic_write ( ble3_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ble3 Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t ble3_generic_read ( ble3_t *ctx, char *data_buf, uint16_t max_len );


#ifdef __cplusplus
}
#endif
#endif  // _BLE3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
