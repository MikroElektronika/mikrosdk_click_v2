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
 * \brief This file contains API for M-BUS RF 4 Click driver.
 *
 * \addtogroup mbusrf4 M-BUS RF 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MBUSRF4_H
#define MBUSRF4_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
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
#define MBUSRF4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.ind = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.sel = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MBUSRF4_RETVAL  uint8_t

#define MBUSRF4_OK           0x00
#define MBUSRF4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define MBUSRF4_ERROR_COMMAND_OR_ELEMENT   0xFF
#define MBUSRF4_ERROR_START_OR_END_COMMAND 0x8F
#define MBUSRF4_ERROR_NEXT_ELEMENT         0x4F
#define MBUSRF4_ERROR_CURRENT_ELEMENT      0x2F
#define MBUSRF4_NO_ERROR                   0x00
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 256
/** \} */

/**
 * \defgroup command Command
 * \{
 */
#define MBUSRF4_CMD_RESET                                   0x30
#define MBUSRF4_CMD_FACTORY_RESET                           0x31
#define MBUSRF4_CMD_SET_MODE                                0x32
#define MBUSRF4_CMD_EEPROM_WRITE                            0x33
#define MBUSRF4_CMD_EEPROM_READ                             0x34
#define MBUSRF4_CMD_TX_MSG                                  0x35
#define MBUSRF4_CMD_RX_MSG_IND                              0x36
#define MBUSRF4_CMD_GET_FW_VERSION                          0x37
#define MBUSRF4_CMD_GET_SERIALNO                            0x38
#define MBUSRF4_CMD_GET_RSSI                                0x39
#define MBUSRF4_CMD_SET_C_FIELD                             0x40
/** \} */

/**
 * \defgroup eeprom_addr EEPROM Address
 * \{
 */
#define MBUSRF4_EEADDR_WM_BUS_MODE                          0x00
#define MBUSRF4_EEADDR_RF_CHANNEL                           0x01
#define MBUSRF4_EEADDR_RF_POWER                             0x02
#define MBUSRF4_EEADDR_RF_AUTOSLEEP                         0x03
#define MBUSRF4_EEADDR_RX_WINDOW                            0x04

#define MBUSRF4_EEADDR_WMBUS_C_FIELD                        0x10
#define MBUSRF4_EEADDR_WMBUS_MANUFACTER_ID0                 0x11
#define MBUSRF4_EEADDR_WMBUS_MANUFACTER_ID1                 0x12
#define MBUSRF4_EEADDR_WMBUS_DEVICE_ID0                     0x13
#define MBUSRF4_EEADDR_WMBUS_DEVICE_ID1                     0x14
#define MBUSRF4_EEADDR_WMBUS_DEVICE_ID2                     0x15
#define MBUSRF4_EEADDR_WMBUS_DEVICE_ID3                     0x16
#define MBUSRF4_EEADDR_WMBUS_VERSION                        0x17
#define MBUSRF4_EEADDR_WMBUS_DEVICE_TYPE                    0x18
 
#define MBUSRF4_EEADDR_WMBUS_BLOCK1_FROM_MODULE_ENABLE      0x20
#define MBUSRF4_EEADDR_WMBUS_RSSI_ENABLE                    0x21
#define MBUSRF4_EEADDR_WMBUS_INDICATE_TIMEOUT_LSB           0x22
#define MBUSRF4_EEADDR_WMBUS_INDICATE_TIMEOUT_MSB           0x23
#define MBUSRF4_EEADDR_WMBUS_UART_BAUDREATE                 0x24
/** \} */

/**
 * \defgroup wm_bus_mode_addr   WM-BUS Mode addr(0x00) - def[0x00]
 * \{
 */
#define MBUSRF4_EEPARAM_WMBUS_MODE_S2_SHORT_PREAMBLE        0x00
#define MBUSRF4_EEPARAM_WMBUS_MODE_S2_LONG_PREAMBLE         0x01
#define MBUSRF4_EEPARAM_WMBUS_MODE_S1                       0x02
#define MBUSRF4_EEPARAM_WMBUS_MODE_S1_M                     0x03
#define MBUSRF4_EEPARAM_WMBUS_MODE_T1_METER                 0x04
#define MBUSRF4_EEPARAM_WMBUS_MODE_T2_METER                 0x05
#define MBUSRF4_EEPARAM_WMBUS_MODE_T2_OTHER                 0x06
#define MBUSRF4_EEPARAM_WMBUS_MODE_R2_METER                 0x07
#define MBUSRF4_EEPARAM_WMBUS_MODE_R2_OTHER                 0x08
#define MBUSRF4_EEPARAM_WMBUS_MODE_C1_METER_FRAME_A         0x09
#define MBUSRF4_EEPARAM_WMBUS_MODE_C1_METER_FRAME_B         0x0A
#define MBUSRF4_EEPARAM_WMBUS_MODE_C2_METER_FRAME_A         0x0B
#define MBUSRF4_EEPARAM_WMBUS_MODE_C2_METER_FRAME_B         0x0C
#define MBUSRF4_EEPARAM_WMBUS_MODE_C2_OTHER_FRAME_A         0x0D
#define MBUSRF4_EEPARAM_WMBUS_MODE_C2_OTHER_FRAME_B         0x0E
#define MBUSRF4_EEPARAM_WMBUS_MODE_T2_C2_OTHER              0x0F
/** \} */

/**
 * \defgroup rf_channel_addr  RF Channel addr(0x01) - def[0x00]
 * \{
 */
#define MBUSRF4_EEPARAM_RFGH_868p03MHz                      0x00
#define MBUSRF4_EEPARAM_RFGH_868p09MHz                      0x01
#define MBUSRF4_EEPARAM_RFGH_868p15MHz                      0x02
#define MBUSRF4_EEPARAM_RFGH_868p21MHz                      0x03
#define MBUSRF4_EEPARAM_RFGH_868p27MHz                      0x04
#define MBUSRF4_EEPARAM_RFGH_868p33MHz                      0x05
#define MBUSRF4_EEPARAM_RFGH_868p39MHz                      0x06
#define MBUSRF4_EEPARAM_RFGH_868p45MHz                      0x07
#define MBUSRF4_EEPARAM_RFGH_868p51MHz                      0x08
#define MBUSRF4_EEPARAM_RFGH_868p57MHz                      0x09
/** \} */

/**
 * \defgroup rf_power_addr  RF Power addr(0x02) - def[0x04]
 * \{
 */
#define MBUSRF4_EEPARAM_RFPWR_0dBm                          0x00
#define MBUSRF4_EEPARAM_RFPWR_5dBm                          0x01
#define MBUSRF4_EEPARAM_RFPWR_7dBm                          0x02
#define MBUSRF4_EEPARAM_RFPWR_10dBm                         0x03
#define MBUSRF4_EEPARAM_RFPWR_12dBm                         0x04
/** \} */

/**
 * \defgroup rf_auto_sleep_addr  RF Auto Sleep addr(0x03) - def[0x00] 
 * \{
 */
#define MBUSRF4_EEPARAM_RFAS_SLEEP_DISABLE                  0x00
#define MBUSRF4_EEPARAM_RFAS_SLEEP_ENABLE                   0x01
/** \} */

/**
 * \defgroup param_return  PARAM RETURN
 * \{
 */
#define MBUSRF4_WM_BUS_C_FIELD                              0x44
#define MBUSRF4_HEADER                                      0xAA
/** \} */

/**
 * \defgroup enable_wm_bus Enable management of WM-Bus from Module 
 * \{
 */
#define MBUSRF4_EEPARAM_BLOCK1_FROM_MODULE_ENABLE           0x01
#define MBUSRF4_EEPARAM_BLOCK1_FROM_MODULE_DISABLE          0x00
/** \} */

/**
 * \defgroup enable_rssi_ind Enable RSSI Indication in communication frame
 * \{
 */
#define MBUSRF4_EEPARAM_RSSI_ENABLE                         0x01
#define MBUSRF4_EEPARAM_RSSI_DISABLE                        0x00
/** \} */

/**
 * \defgroup uart_baud_selection Uart baudrate selection
 * \{
 */
#define MBUSRF4_EEPARAM_UART_BAUDRATE_9600                  0x00
#define MBUSRF4_EEPARAM_UART_BAUDRATE_19200                 0x01
#define MBUSRF4_EEPARAM_UART_BAUDRATE_38400                 0x02
#define MBUSRF4_EEPARAM_UART_BAUDRATE_57600                 0x03
#define MBUSRF4_EEPARAM_UART_BAUDRATE_115200                0x04
/** \} */

/**
 * \defgroup set_value_in_memory  Set value in RAM/EEPROM memory 
 * \{
 */
#define MBUSRF4_SET_VALUE_IN_RAM_MEMORY                     0x00
#define MBUSRF4_SET_VALUE_IN_EEPROM_MEMORY                  0xFF
/** \} */

/**
 * \defgroup example_user_mode  Example user mode
 * \{
 */
#define MBUSRF4_USER_APP_RX_MODE                            0x00
#define MBUSRF4_USER_APP_TX_MODE                            0x01
/** \} */

/**
 * \defgroup communication_mode Communication Mode
 * \{
 */
#define MBUSRF4_COMMUNICATION_UART_MODE                     0x01
#define MBUSRF4_COMMUNICATION_SPI_MODE                      0x00
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

    digital_out_t cs;
    digital_out_t sel;

    // Input pins 

    digital_in_t ind;
    digital_in_t rts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} mbusrf4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t ind;
    pin_name_t cs;
    pin_name_t sel;
    pin_name_t rts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} mbusrf4_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t mbusrf4_error_t;

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
void mbusrf4_cfg_setup ( mbusrf4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MBUSRF4_RETVAL mbusrf4_init ( mbusrf4_t *ctx, mbusrf4_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 *
 * @description This function write specific number of data.
 */
void mbusrf4_generic_write ( mbusrf4_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @returns Number of reads data.
 *
 * @description This function read data of maximum length.
 */
int32_t mbusrf4_generic_read ( mbusrf4_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Get Interrupt state of the RTS(INT) pin
 *
 * @param ctx Click object.
 *
 * @description This function get state of RTS pin.
 */
uint8_t mbusrf4_get_state_rts ( mbusrf4_t *ctx );

/**
 * @brief Set communication SPI/UART
 *
 * @param ctx Click object. 
 * @param mode Select communication SPI/UART (UART is default)
 *
 * @description This function sets desired mode.
 */
void mbusrf4_set_communication_mode ( mbusrf4_t *ctx, uint8_t mode );

/**
 * @brief Get Interrupt state of the RTS(INT) pin
 *
 * @param ctx Click object.
 *
 * @description This function gets state of RTS pin.
 */
uint8_t mbusrf4_get_state_rts ( mbusrf4_t *ctx );

/**
 * @brief Send command - UART communication
 *
 * @param ctx            Click object. 
 * @param command        Command
 * @param length         Number of bytes in Payload buffer
 * @param payload_buff   Pointer to a payload buffer
 *
 * @description Header and checksum are calculated and sent at the beginning (header) 
 *              and finally (checksum)
 */
void mbusrf4_send_command ( mbusrf4_t *ctx, uint8_t command, uint8_t length, uint8_t *payload_buff );


void mbusrf4_transmit_data ( mbusrf4_t *ctx, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Get Interrupt state of the IND(AN) pin
 *
 * @param ctx Click object.
 *
 * @description This function gets state of IND pin.
 */
uint8_t mbusrf4_get_state_ind ( mbusrf4_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MBUSRF4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
