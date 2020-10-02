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
 * \brief This file contains API for ECG 4 Click driver.
 *
 * \addtogroup ecg4 ECG 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ECG4_H
#define ECG4_H

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
#define ECG4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ECG4_RETVAL  uint8_t

#define ECG4_OK           0x00
#define ECG4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define ECG4_NEMA_GPGGA 1
#define ECG4_NEMA_GPGLL 3
#define ECG4_NEMA_GPGGA_NUM_ELEMENT 15
#define ECG4_NEMA_GPGLL_NUM_ELEMENT 5
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define ECG4_GPGGA_TIME                      1 
#define ECG4_GPGGA_LATITUDE                  2
#define ECG4_GPGGA_LATITUDE_SIDE             3
#define ECG4_GPGGA_LONGITUDE                 4
#define ECG4_GPGGA_LONGITUDE_SIDE            5
#define ECG4_GPGGA_QUALITY_INDICATOR         6
#define ECG4_GPGGA_NUMBER_OF_SATELLITES      7
#define ECG4_GPGGA_H_DILUTION_OF_POS         8
#define ECG4_GPGGA_ALTITUDE                  9
#define ECG4_GPGGA_ALTITUDE_UNIT             10
#define ECG4_GPGGA_GEOIDAL_SEPARATION        11
#define ECG4_GPGGA_GEOIDAL_SEPARATION_UNIT   12
#define ECG4_GPGGA_TIME_SINCE_LAST_DGPS      13
#define ECG4_GPGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define ECG4_ERROR_COMMAND_OR_ELEMENT   0xFF
#define ECG4_ERROR_START_OR_END_COMMAND 0x8F
#define ECG4_ERROR_NEXT_ELEMENT         0x4F
#define ECG4_ERROR_CURRENT_ELEMENT      0x2F
#define ECG4_NO_ERROR                   0x00
/** \} */

#define ECG4_SYNC_BYTE                  0xAA
#define ECG4_EXCODE_BYTE                0x55
#define ECG4_SIGNAL_QUALITY_CODE_BYTE   0x02
#define ECG4_HEART_RATE_CODE_BYTE       0x03
#define ECG4_RAW_DATA_CODE_BYTE         0x80
#define ECG4_RESPONSE_READY             0x01
#define ECG4_RESPONSE_NOT_READY         0x00
#define ECG4_ENABLE_LDO_CTRL            0x01
#define ECG4_DISABLE_LDO_CTRL           0x00

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
 * @defgroup ECG4_TYPES Types              
 * \{
 */
typedef void ( *ecg4_hdl_t )( uint8_t*, uint8_t*, uint8_t*, uint8_t* );

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

    ecg4_hdl_t driver_hdl;

} ecg4_t;

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

} ecg4_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t ecg4_error_t;

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
void ecg4_cfg_setup ( ecg4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ECG4_RETVAL ecg4_init ( ecg4_t *ctx, ecg4_cfg_t *cfg );

/**
 * @brief Reset module.
 * @param ctx Click object.
 */
void ecg4_module_reset ( ecg4_t *ctx );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void ecg4_generic_write ( ecg4_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
uint16_t ecg4_generic_read ( ecg4_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief LDO Control function
 *
 * @param ctx Click object.
 * @param state  
 *           <pre>
 *            0 - Disable LDO control
 *            1 - Enable LDO control3
 *           </pre>
 *
 * @description Function powers up or down control of LDO (Low Drop Out).
 * @note The BMD101 contains an internal LDO which consists of a bandgap cell to generate a 1.2V reference
 *       followed by two separate unity gain buffers, for the analog and digital supplies.
 */
void ecg4_enable_ldo_ctrl ( ecg4_t *ctx, uint8_t state );

/**
 * @brief Uart Interrupt Routine function
 *
 * @param ctx Click object.
 * 
 * @description Function performs the uart interrupt routine, reads a data from uart rx buffer and makes a response from the BMD101 device.
 */
void ecg4_uart_isr( ecg4_t *ctx, uint8_t rx_dat );

#ifdef __cplusplus
}
#endif
#endif  // _ECG4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
