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
 * \brief This file contains API for NB IoT Click driver.
 *
 * \addtogroup nbiot NB IoT Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef NBIOT_H
#define NBIOT_H

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
#define NBIOT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.stat = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define NBIOT_RETVAL  uint8_t

#define NBIOT_OK           0x00
#define NBIOT_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup parser_error Parser error
 * \{
 */
#define NBIOT_PARSER_NO_ERROR    0x00
#define NBIOT_PARSER_ERROR_REF   0x01
#define NBIOT_PARSER_ERROR_CMD   0x02
#define NBIOT_PARSER_ERROR_DATA  0x04
/** \} */

/**
 * \defgroup click_status G2C 3G click status
 * \{
 */
#define NBIOT_STATUS_DEVICE_READY            1
#define NBIOT_STATUS_ACT_NETWORK_AND_BROKER  4
#define NBIOT_STATUS_ACT_NETWORK             2
#define NBIOT_STATUS_ACT_BROKER              3
#define NBIOT_STATUS_DEVICE_BUSY             0
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define NBIOT_MODULE_POWER_ON   1
#define NBIOT_MODULE_POWER_OFF  0
/** \} */

/**
 * \defgroup at_command AT command 
 * \{
 */
#define NBIOT_SINGLE_CMD_AT        "AT"
#define NBIOT_SINGLE_CMD_ATI       "ATI"
#define NBIOT_SINGLE_CMD_AT_W      "AT+W"
#define NBIOT_SINGLE_CMD_AT_R      "AT+R"
#define NBIOT_SINGLE_CMD_ATE0      "ATE0"
#define NBIOT_SINGLE_CMD_ATE1      "ATE1"
#define NBIOT_SINGLE_CMD_AT_RST    "AT+RST"
#define NBIOT_SINGLE_CMD_AT_CRST   "AT+CRST"
#define NBIOT_SINGLE_CMD_AT_GMR    "AT+GMR"
#define NBIOT_SINGLE_CMD_AT_GMSTA  "AT+GMSTA"
#define NBIOT_SINGLE_CMD_AT_PUB    "AT+PUB"
#define NBIOT_SINGLE_CMD_AT_CIMI   "AT+CIMI"

#define NBIOT_SINGLE_CMD_SET_AT_LRSP_1 "AT+LRSP=1"
#define NBIOT_SINGLE_CMD_SET_AT_LRSP_0 "AT+LRSP=0"
#define NBIOT_SINGLE_CMD_SET_AT_CEN_1  "AT+CEN=1"
#define NBIOT_SINGLE_CMD_SET_AT_CEN_0  "AT+CEN=0"
#define NBIOT_SINGLE_CMD_SET_AT_NWC_1  "AT+NWC=1"
#define NBIOT_SINGLE_CMD_SET_AT_NWC_0  "AT+NWC=0"
#define NBIOT_SINGLE_CMD_SET_AT_BRC_1  "AT+BRC=1"
#define NBIOT_SINGLE_CMD_SET_AT_BRC_0  "AT+BRC=0"
#define NBIOT_SINGLE_CMD_SET_AT_GPEN_0 "AT+GPEN=0"
#define NBIOT_SINGLE_CMD_SET_AT_GPEN_1 "AT+GPEN=1"
#define NBIOT_SINGLE_CMD_SET_AT_CFUN   "AT+CFUN=1"

#define NBIOT_SINGLE_CMD_GET_AT_LRSP "AT+LRSP?"
#define NBIOT_SINGLE_CMD_GET_AT_CEN  "AT+CEN?"
#define NBIOT_SINGLE_CMD_GET_AT_NWC  "AT+NWC?"
#define NBIOT_SINGLE_CMD_GET_AT_BRC  "AT+BRC?"
#define NBIOT_SINGLE_CMD_GET_AT_GPEN "AT+GPEN?"
#define NBIOT_SINGLE_CMD_GET_AT_NWCR "AT+NWCR?"
#define NBIOT_SINGLE_CMD_GET_AT_BRCR "AT+BRCR?"
#define NBIOT_SINGLE_CMD_GET_AT_DSET "AT+DSET?"

#define NBIOT_SINGLE_CMD_TEST_AT_LRSP         "AT+LRSP=?"
#define NBIOT_SINGLE_CMD_TEST_AT_CEN          "AT+CEN=?"
#define NBIOT_SINGLE_CMD_TEST_AT_NWC          "AT+NWC=?"
#define NBIOT_SINGLE_CMD_TEST_AT_BRC          "AT+BRC=?"
#define NBIOT_SINGLE_CMD_TEST_AT_GPEN         "AT+GPEN=?"
#define NBIOT_SINGLE_CMD_TEST_AT_NWCR         "AT+NWCR=?"
#define NBIOT_SINGLE_CMD_TEST_AT_BRCR         "AT+BRCR=?"
#define NBIOT_SINGLE_CMD_TEST_AT_DSET         "AT+DSET=?"
#define NBIOT_SINGLE_CMD_TEST_ATAT_CGDCONT    "AT+CGDCONT?"
#define C5GNBIOT_SINGLE_CMD_GET_AT_CGATT      "AT+CGATT?"

#define NBIOT_MULTI_CMD_AT_DSET      "AT+DSET"
#define NBIOT_MULTI_CMD_AT_BRCR      "AT+BRCR"
#define NBIOT_MULTI_CMD_AT_NWCR      "AT+NWCR"

#define C5GNBIOT_SINGLE_CMD_SET_AT_CGDCONT_1  "AT+CGDCONT=1,\"IP\",\"vip.iot\""
#define NBIOT_CMD_AT_NCONFIG                  "AT+NCONFIG=CR_0354_0338_SCRAMBLING,TRUE"
#define NBIOT_CMD_AT_NCONFIG1                 "AT+NCONFIG=CR_0859_SI_AVOID,TRUE"
#define NBIOT_CMD_AT_NCONFIG2                 "AT+NCONFIG=AUTOCONNECT,FALSE"
#define NBIOT_CMD_AT_NBAND                    "AT+NBAND=8"
#define NBIOT_CMD_AT_CEREG                    "AT+CEREG=2"
#define NBIOT_CMD_AT_COPS                     "AT+COPS=1,2,\"12345\""
#define NBIOT_CMD_AT_NSOCR                    "AT+NSOCR= DGRAM,17,16666,1"
#define NBIOT_CMD_AT_NSOST                    "AT+NSOST=0,83.58.228.64,16666,2,ABCD"
#define NBIOT_CMD_AT_NSOCL                    "AT+NSOCL=0"

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

    // Input pins 

    digital_in_t stat;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} nbiot_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t stat;
    pin_name_t rst;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} nbiot_cfg_t;

/**
 * @brief Error type 
 */
// Actuator switch type
typedef uint8_t nbiot_actuator_sw_t;

// Actuator counter type
typedef int16_t nbiot_actuator_cnt_t;

// Actuator string type
typedef char nbiot_actuator_str_t;

// Parser error type
typedef uint8_t nbiot_error_t;

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
void nbiot_cfg_setup ( nbiot_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
NBIOT_RETVAL nbiot_init ( nbiot_t *ctx, nbiot_cfg_t *cfg );

/**
 * @brief Power up modules.
 * @param ctx Click object.
 */
void nbiot_module_power ( nbiot_t *ctx );

/**
 * @brief Reset module.
 * @param ctx Click object.
 */
void nbiot_reset ( nbiot_t *ctx );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void nbiot_generic_write ( nbiot_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t nbiot_generic_read ( nbiot_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send Command function.
 * @param ctx  Click object.
 * @param command  Command.
 * @description This function sends comamnd.
 */
void nbiot_send_command ( nbiot_t *ctx, char *command );

#ifdef __cplusplus
}
#endif
#endif  // _NBIOT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
