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
 * \brief This file contains API for PWR Meter Click driver.
 *
 * \addtogroup pwrmeter PWR Meter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PWRMETER_H
#define PWRMETER_H

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
#define PWRMETER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PWRMETER_RETVAL  uint8_t
#define PWRMETER_P    const uint8_t*

#define PWRMETER_OK           0x00
#define PWRMETER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define PWRMETER_ERROR_COMMAND_OR_ELEMENT       0xFF
#define PWRMETER_ERROR_START_OR_END_COMMAND     0x8F
#define PWRMETER_ERROR_NEXT_ELEMENT             0x4F
#define PWRMETER_ERROR_CURRENT_ELEMENT          0x2F
#define PWRMETER_NO_ERROR                       0x00
/** \} */

/**
 * \defgroup header_byte Header byte
 * \{
 */
#define PWRMETER_HEADER_BYTE                    0xA5
/** \} */

/**
 * \defgroup commands Commands
 * \{
 */
#define PWRMETER_REG_READ_COMM                  0x4E
#define PWRMETER_REG_WRITE_COMM                 0x4D
#define PWRMETER_SET_ADDR_POINTER_COMM          0x41
#define PWRMETER_SAVE_TO_FLASH_COMM             0x53
#define PWRMETER_EEPROM_READ_COMM               0x42
#define PWRMETER_EEPROM_WRITE_COMM              0x50
#define PWRMETER_EEPROM_ERASE_COMM              0x4F
#define PWRMETER_GAIN_CALIB_COMM                0x5A
#define PWRMETER_REACTIVE_GAIN_CALIB_COMM       0x7A
#define PWRMETER_FREQ_CALIB_COMM                0x76
#define PWRMETER_SAVE_ENERGY_TO_EEPROM_COMM     0x45


/**
 * \defgroup 
 * \{
 */
#define PWRMETER_SUCCESSFUL                     0x06
#define PWRMETER_COMMAND_FAIL                   0x15
#define PWRMETER_CHECKSUM_FAIL                  0x51
#define PWRMETER_ADDRESS_FAIL                   0x00
#define PWRMETER_NBYTES_FAIL                    0x01
#define PWRMETER_PAGE_NUM_FAIL                  0x02

/**
 * \defgroup 
 * \{
 */
#define PWRMETER_16BIT_DATA                     0x00
#define PWRMETER_32BIT_DATA                     0x01

/**
 * \defgroup 
 * \{
 */
#define PWRMETER_DCMODE_MASK                    0x01
#define PWRMETER_DCCURR_SIGN_MASK               0x02
#define PWRMETER_DCVOLT_SIGN_MASK               0x04
#define PWRMETER_PR_SIGN_MASK                   0x08
#define PWRMETER_PA_SIGN_MASK                   0x10

/**
 * \defgroup 
 * \{
 */
#define PWRMETER_ENABLE                         0x00
#define PWRMETER_DISABLE                        0x01

/**
 * \defgroup 
 * \{
 */
#define PWRMETER_INSTR_POINTER_REG              0x0000
#define PWRMETER_SYS_STATUS_REG                 0x0002
#define PWRMETER_SYS_VERSION_REG                0x0004
#define PWRMETER_VOLT_RMS_REG                   0x0006
#define PWRMETER_LINE_FREQ_REG                  0x0008
#define PWRMETER_THERM_VOLT_REG                 0x000A
#define PWRMETER_PWR_FACTOR_REG                 0x000C
#define PWRMETER_CURR_RMS_REG                   0x000E
#define PWRMETER_ACTIVE_PWR_REG                 0x0012
#define PWRMETER_REACTIVE_PWR_REG               0x0016
#define PWRMETER_APPARENT_PWR_REG               0x001A
#define PWRMETER_IMPORT_ACTIVE_E_COUNT_REG      0x001E
#define PWRMETER_EXPORT_ACTIVE_E_COUNT_REG      0x0026
#define PWRMETER_IMPORT_REACTIVE_E_COUNT_REG    0x002E
#define PWRMETER_EXPORT_REACTIVE_E_COUNT_REG    0x0036
#define PWRMETER_MIN_RECORD_1_REG               0x003E
#define PWRMETER_MIN_RECORD_2_REG               0x0042
#define PWRMETER_MAX_RECORD_1_REG               0x0046
#define PWRMETER_MAX_RECORD_2_REG               0x004A
#define PWRMETER_CALIB_DELIMIT_REG              0x004E
#define PWRMETER_GAIN_CURR_RMS_REG              0x0050
#define PWRMETER_GAIN_VOLT_RMS_REG              0x0052
#define PWRMETER_GAIN_ACTIVE_PWR_REG            0x0054
#define PWRMETER_GAIN_REACTIVE_PWR_REG          0x0056
#define PWRMETER_OFFSET_CURR_RMS_REG            0x005A
#define PWRMETER_OFFSET_ACTIVE_PWR_REG          0x005C
#define PWRMETER_OFFSET_REACTIVE_PWR_REG        0x005E
#define PWRMETER_GAIN_LINE_FREQ_REG             0x0060
#define PWRMETER_PHASE_COMP_REG                 0x0062
#define PWRMETER_VOLT_DROP_COMP_REG             0x0064
#define PWRMETER_INCAP_CURR_COMP_REG            0x0066
#define PWRMETER_RANGE_VDROP_COMP_REG           0x0068
#define PWRMETER_DC_GAIN_CURR_RMS_REG           0x006C
#define PWRMETER_DC_GAIN_VOLT_RMS_REG           0x006E
#define PWRMETER_DC_GAIN_ACTIVE_PWR_REG         0x0070
#define PWRMETER_DC_OFFSET_CURR_RMS_REG         0x0072
#define PWRMETER_DC_OFFSET_AVTIVE_PWR_REG       0x0074
#define PWRMETER_OFFCAL_MSB_REG                 0x007A
#define PWRMETER_OFFCAL_CH0_REG                 0x007C
#define PWRMETER_OFFCAL_CH1_REG                 0x007E
#define PWRMETER_TEMP_POS_COMP_FREQ_REG         0x0080
#define PWRMETER_TEMP_NEG_COMP_FREQ_REG         0x0082
#define PWRMETER_TEMP_POS_COMP_CURR_REG         0x0084
#define PWRMETER_TEMP_NEG_COMP_CURR_REG         0x0086
#define PWRMETER_TEMP_POS_COMP_PWR_REG          0x0088
#define PWRMETER_TEMP_NEG_COMP_PWR_REG          0x008A
#define PWRMETER_SYS_CONFIG_REG                 0x0094
#define PWRMETER_EVENT_CONFIG_REG               0x0098
#define PWRMETER_RANGE_REG                      0x009C
#define PWRMETER_CALIB_CURR_REG                 0x00A0
#define PWRMETER_CALIB_VOLT_REG                 0x00A4
#define PWRMETER_CALIB_PWR_ACTIVE_REG           0x00A6
#define PWRMETER_CALIB_PWR_REACTIVE_REG         0x00AA
#define PWRMETER_APP_PWR_DIV_DIG_REG            0x00BE
#define PWRMETER_ACCUM_INTER_PAR_REG            0x00C0
#define PWRMETER_PWM_PERIOD_REG                 0x00C2
#define PWRMETER_PWM_DUTY_CYCLE_REG             0x00C4
#define PWRMETER_MIN_MAX_POINTER1_REG           0x00C6
#define PWRMETER_MIN_MAX_POINTER2_REG           0x00C8
#define PWRMETER_LINE_FREQ_REF_REG              0x00CA
#define PWRMETER_THERM_VOLT_CALIB_REG           0x00CC
#define PWRMETER_VOLT_SAG_LIMIT_REG             0x00CE
#define PWRMETER_VOLT_SURGE_LIMIT_REG           0x00D0
#define PWRMETER_OVER_CURR_LIMIT_REG            0x00D2
#define PWRMETER_OVER_PWR_LIMIT_REG             0x00D6
#define PWRMETER_OVER_TEMP_LIMIT_REG            0x00DA
#define PWRMETER_VOLT_LOW_THRESHOLD_REG         0x00DC
#define PWRMETER_VOLT_HIGH_THRESHOLD_REG        0x00DE
#define PWRMETER_NO_LOAD_THRESHOLD_REG          0x00E0

/**
 * \defgroup 
 * \{
 */
#define PWRMETER_VOLT_GAIN_32                   0x28000000
#define PWRMETER_VOLT_GAIN_16                   0x20000000
#define PWRMETER_VOLT_GAIN_8                    0x18000000
#define PWRMETER_VOLT_GAIN_4                    0x10000000
#define PWRMETER_VOLT_GAIN_2                    0x08000000
#define PWRMETER_VOLT_GAIN_1                    0x00000000
#define PWRMETER_CURR_GAIN_32                   0x05000000
#define PWRMETER_CURR_GAIN_16                   0x04000000
#define PWRMETER_CURR_GAIN_8                    0x03000000
#define PWRMETER_CURR_GAIN_4                    0x02000000
#define PWRMETER_CURR_GAIN_2                    0x01000000
#define PWRMETER_CURR_GAIN_1                    0x00000000
#define PWRMETER_UART_BR_1200                   0x0000E000
#define PWRMETER_UART_BR_2400                   0x0000C000
#define PWRMETER_UART_BR_4800                   0x0000A000
#define PWRMETER_UART_BR_9600                   0x00008000
#define PWRMETER_UART_BR_19200                  0x00006000
#define PWRMETER_UART_BR_38400                  0x00004000
#define PWRMETER_UART_BR_57600                  0x00002000
#define PWRMETER_UART_BR_115200                 0x00000000
#define PWRMETER_ZCD_INVERTED                   0x00001000
#define PWRMETER_ZCD_OUTPUT_DISABLED            0x00000400
#define PWRMETER_SINGLE_WIRE_EN                 0x00000100
#define PWRMETER_TEMP_COMP_EN                   0x00000080
#define PWRMETER_BOTH_RESET                     0x00000060
#define PWRMETER_VOLT_RESET                     0x00000040
#define PWRMETER_CURR_RESET                     0x00000020
#define PWRMETER_BOTH_SHUTDOWN                  0x00000018
#define PWRMETER_VOLT_SHUTDOWN                  0x00000010
#define PWRMETER_CURR_SHUTDOWN                  0x00000008
#define PWRMETER_INT_VOLT_REF_DISABLED          0x00000004
#define PWRMETER_PWM_TURNED_ON                  0x00000002
#define PWRMETER_ENERGY_ON                      0x00000001

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

    digital_out_t en;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} pwrmeter_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t en;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} pwrmeter_cfg_t;

/**
 * @brief Error type 
 */
typedef uint8_t pwrmeter_error_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void pwrmeter_cfg_setup ( pwrmeter_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
PWRMETER_RETVAL pwrmeter_init ( pwrmeter_t *ctx, pwrmeter_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for PwrMeter Click.
 */
void pwrmeter_default_cfg ( pwrmeter_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx Click object.
 * @param pwrmeter Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 *
 * @description Generic write function
 */
void pwrmeter_generic_write ( pwrmeter_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx Click object. 
 * @param pwrmeter Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 *
 * @returns Number of reads data.
 *
 * @description Generic read function
 */
int32_t pwrmeter_generic_read ( pwrmeter_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Bytes Read function
 *
 * @param ctx Click object. 
 * @param reg_addr  Start address which from data be read
 * @param n_bytes  Number of bytes to be read
 * @param data_out  Memory where data be stored
 *
 * @returns Response on the desired command
 *
 * @description Function reads data bytes from registers.
 */
PWRMETER_RETVAL pwrmeter_read_reg_bytes ( pwrmeter_t *ctx, uint16_t reg_addr, uint8_t n_bytes, uint8_t *data_out );

/**
 * @brief WORD Read function
 *
 * @param ctx Click object. 
 * @param register_addr  Address which from data be read
 * @param data_out  Memory where data be stored
 *
 * @returns Response on the desired command
 *
 * @description Function reads 16-bit data from the desired register.
 */
PWRMETER_RETVAL pwrmeter_read_reg_word ( pwrmeter_t *ctx, uint16_t register_addr, uint16_t *data_out );

/**
 * @brief DWORD Read function
 *
 * @param ctx Click object. 
 * @param register_addr  Address which from data be read
 * @param data_out  Memory where data be stored
 *
 * @returns Response on the desired command
 *
 * @description Function reads 32-bit data from the desired register.
 */
PWRMETER_RETVAL pwrmeter_read_reg_dword ( pwrmeter_t *ctx, uint16_t register_addr, uint32_t *data_out );

/**
 * @brief Signed Data Read function
 *
 * @param ctx Click object. 
 * @param register_addr  Address which from data be read
 * @param data_mode  0 - 16bit data, 1 - 32bit data
 * @param data_out  Memory where data be stored
 *
 * @returns Response on the desired command
 *
 * @description Function reads signed 16bit or 32bit data from the desired register.
 */
PWRMETER_RETVAL pwrmeter_read_reg_signed ( pwrmeter_t *ctx, uint16_t register_addr, uint8_t data_mode, int32_t *data_out );

/**
 * @brief Bytes Write function
 *
 * @param ctx Click object. 
 * @param reg_addr  Address where data be written
 * @param n_bytes  Number of bytes to be written
 * @param data_in  Data bytes to be written
 *
 * @returns Response on the desired command
 *
 * @description Function writes bytes to the registers.
 */
PWRMETER_RETVAL pwrmeter_write_reg_bytes ( pwrmeter_t *ctx, uint16_t reg_addr, uint8_t n_bytes, uint8_t *data_in );

/**
 * @brief WORD Write function
 *
 * @param ctx Click object. 
 * @param register_addr  Address where data be written
 * @param data_in  Data to be written
 *
 * @returns Response on the desired command
 *
 * @description Function writes 16-bit data to the register.
 */
PWRMETER_RETVAL pwrmeter_write_reg_word ( pwrmeter_t *ctx, uint16_t register_addr, uint16_t data_in );

/**
 * @brief DWORD Write function
 *
 * @param ctx Click object. 
 * @param register_addr  Address where data be written
 * @param data_in  Data to be written
 *
 * @returns Response on the desired command
 *
 * @description Function writes 32-bit data to the register.
 */
PWRMETER_RETVAL pwrmeter_write_reg_dword ( pwrmeter_t *ctx, uint16_t register_addr, uint32_t data_in );

/**
 * @brief Signed Data Write function
 *
 * @param ctx Click object. 
 * @param register_addr  Address where data be written
 * @param data_mode  0 - 16bit data, 1 - 32bit data
 * @param data_in  Data to be written
 *
 * @returns Response on the desired command
 *
 * @description Function writes 16bit or 32bit signed data to the register.
 */
PWRMETER_RETVAL pwrmeter_write_reg_signed ( pwrmeter_t *ctx, uint16_t register_addr, uint8_t data_mode, int32_t data_in );

/**
 * @brief Command Send function
 *
 * @param ctx Click object. 
 * @param command_byte  Command to be sent
 *
 * @returns Response on the desired command
 *
 * @description Function sends and performs a determined command.
 */
PWRMETER_RETVAL pwrmeter_send_command ( pwrmeter_t *ctx, uint8_t command_byte );

/**
 * @brief EEPROM Read function
 *
 * @param ctx Click object. 
 * @param page_num  Page number in EEPROM memory (from 0 to 31)
 * @param data_out  Memory where data be stored
 *
 * @returns Response on the desired command
 *
 * @description Function reads a 8 16bit data from EEPROM block determined by page number.
 */
PWRMETER_RETVAL pwrmeter_read_page_eeprom ( pwrmeter_t *ctx, uint8_t page_num, uint16_t *data_out );

/**
 * @brief EEPROM Write function
 *
 * @param ctx Click object. 
 * @param page_num  Page number in EEPROM memory (from 2 to 31)
 * @param data_in  Data to be written
 *
 * @returns Response on the desired command
 *
 * @description Function writes 8 16bit data to the EEPROM block determined by page number.
 */
PWRMETER_RETVAL pwrmeter_write_page_eeprom ( pwrmeter_t *ctx, uint8_t  page_num, uint16_t *data_in );

/**
 * @brief Status Get function
 *
 * @param ctx Click object. 
 * @param status_data  Status byte with determined status bits
 *
 * @returns Response on the desired command
 *
 * @description Function reads 16-bit Status register and makes one byte with determined status bits, which can be useful in code.
 * @note See status bit masks which can be find as constant global variables.
 */
PWRMETER_RETVAL pwrmeter_get_status ( pwrmeter_t *ctx, uint8_t *status_data );

/**
 * @brief Enable function
 *
 * @param ctx Click object. 
 * @param state  0 - active state; 1 - inactive state
 *
 * @description Function puts output of regulator in enabled or disabled state.
 */
void pwrmeter_enable ( pwrmeter_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _PWRMETER_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
