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
 * \brief This file contains API for AnyNet 3G Click driver.
 *
 * \addtogroup anynet3g AnyNet 3G Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ANYNET3G_H
#define ANYNET3G_H

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
#define ANYNET3G_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.slp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.dsr = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.dtr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.iot = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ANYNET3G_RETVAL  uint8_t

#define ANYNET3G_OK           0x00
#define ANYNET3G_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup parser_error Parser error
 * \{
 */
#define ANYNET3G_PARSER_NO_ERROR    0x00
#define ANYNET3G_PARSER_ERROR_REF   0x01
#define ANYNET3G_PARSER_ERROR_CMD   0x02
#define ANYNET3G_PARSER_ERROR_DATA  0x04
/** \} */

/**
 * \defgroup click_status G2C 3G click status
 * \{
 */
#define ANYNET3G_STATUS_DEVICE_READY            1
#define ANYNET3G_STATUS_ACT_NETWORK_AND_BROKER  4
#define ANYNET3G_STATUS_ACT_NETWORK             2
#define ANYNET3G_STATUS_ACT_BROKER              3
#define ANYNET3G_STATUS_DEVICE_BUSY             0
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define ANYNET3G_MODULE_POWER_ON   1
#define ANYNET3G_MODULE_POWER_OFF  0
/** \} */

/**
 * \defgroup at_command AT command 
 * \{
 */
#define ANYNET3G_SINGLE_CMD_AT        "AT"
#define ANYNET3G_SINGLE_CMD_AT_W      "AT+W"
#define ANYNET3G_SINGLE_CMD_AT_R      "AT+R"
#define ANYNET3G_SINGLE_CMD_ATE0      "ATE0"
#define ANYNET3G_SINGLE_CMD_ATE1      "ATE1"
#define ANYNET3G_SINGLE_CMD_AT_RST    "AT+RST"
#define ANYNET3G_SINGLE_CMD_AT_CRST   "AT+CRST"
#define ANYNET3G_SINGLE_CMD_AT_GMR    "AT+GMR"
#define ANYNET3G_SINGLE_CMD_AT_GMSTA  "AT+GMSTA"
#define ANYNET3G_SINGLE_CMD_AT_PUB    "AT+PUB"

#define ANYNET3G_SINGLE_CMD_SET_AT_LRSP_1 "AT+LRSP=1"
#define ANYNET3G_SINGLE_CMD_SET_AT_LRSP_0 "AT+LRSP=0"
#define ANYNET3G_SINGLE_CMD_SET_AT_CEN_1  "AT+CEN=1"
#define ANYNET3G_SINGLE_CMD_SET_AT_CEN_0  "AT+CEN=0"
#define ANYNET3G_SINGLE_CMD_SET_AT_NWC_1  "AT+NWC=1"
#define ANYNET3G_SINGLE_CMD_SET_AT_NWC_0  "AT+NWC=0"
#define ANYNET3G_SINGLE_CMD_SET_AT_BRC_1  "AT+BRC=1"
#define ANYNET3G_SINGLE_CMD_SET_AT_BRC_0  "AT+BRC=0"
#define ANYNET3G_SINGLE_CMD_SET_AT_GPEN_0 "AT+GPEN=0"
#define ANYNET3G_SINGLE_CMD_SET_AT_GPEN_1 "AT+GPEN=1"

#define ANYNET3G_SINGLE_CMD_GET_AT_LRSP "AT+LRSP?"
#define ANYNET3G_SINGLE_CMD_GET_AT_CEN  "AT+CEN?"
#define ANYNET3G_SINGLE_CMD_GET_AT_NWC  "AT+NWC?"
#define ANYNET3G_SINGLE_CMD_GET_AT_BRC  "AT+BRC?"
#define ANYNET3G_SINGLE_CMD_GET_AT_GPEN "AT+GPEN?"
#define ANYNET3G_SINGLE_CMD_GET_AT_NWCR "AT+NWCR?"
#define ANYNET3G_SINGLE_CMD_GET_AT_BRCR "AT+BRCR?"
#define ANYNET3G_SINGLE_CMD_GET_AT_DSET "AT+DSET?"

#define ANYNET3G_SINGLE_CMD_TEST_AT_LRSP "AT+LRSP=?"
#define ANYNET3G_SINGLE_CMD_TEST_AT_CEN  "AT+CEN=?"
#define ANYNET3G_SINGLE_CMD_TEST_AT_NWC  "AT+NWC=?"
#define ANYNET3G_SINGLE_CMD_TEST_AT_BRC  "AT+BRC=?"
#define ANYNET3G_SINGLE_CMD_TEST_AT_GPEN "AT+GPEN=?"
#define ANYNET3G_SINGLE_CMD_TEST_AT_NWCR "AT+NWCR=?"
#define ANYNET3G_SINGLE_CMD_TEST_AT_BRCR "AT+BRCR=?"
#define ANYNET3G_SINGLE_CMD_TEST_AT_DSET "AT+DSET=?"

#define ANYNET3G_MULTI_CMD_AT_DSET "AT+DSET"
#define ANYNET3G_MULTI_CMD_AT_BRCR "AT+BRCR"
#define ANYNET3G_MULTI_CMD_AT_NWCR "AT+NWCR"

#define AT_QCCID                   "AT+QCCID"
#define AT_AWSVER                  "AT+AWSVER"
#define AT_AWSSTATE                "AT+AWSSTATE=?"
#define AT_AWSPUBOPEN              "AT+AWSPUBOPEN=0,\"MY_TOPIC\""
#define AT_PUBLISH_SET             "AT+AWSPUBLISH=0,6,MIKROE"
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

    digital_out_t slp;
    digital_out_t dtr;

    // Input pins 

    digital_in_t an;
    digital_in_t dsr;
    digital_in_t iot;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} anynet3g_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t slp;
    pin_name_t dsr;
    pin_name_t dtr;
    pin_name_t iot;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} anynet3g_cfg_t;

/**
 * @brief Error type 
 */
// Actuator switch type
typedef uint8_t anynet3g_actuator_sw_t;

// Actuator counter type
typedef int16_t anynet3g_actuator_cnt_t;

// Actuator string type
typedef char anynet3g_actuator_str_t;

// Parser error type
typedef uint8_t anynet3g_error_t;

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
void anynet3g_cfg_setup ( anynet3g_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ANYNET3G_RETVAL anynet3g_init ( anynet3g_t *ctx, anynet3g_cfg_t *cfg );

/**
 * @brief Reset module.
 * @param ctx Click object.
 */
void anynet3g_reset ( anynet3g_t *ctx );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void anynet3g_generic_write ( anynet3g_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
int32_t anynet3g_generic_read ( anynet3g_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send Command function.
 * @param ctx  Click object.
 * @param command  Command.
 * @description This function sends comamnd.
 */
void anynet3g_send_command ( anynet3g_t *ctx, char *command );

#ifdef __cplusplus
}
#endif
#endif  // _ANYNET3G_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
