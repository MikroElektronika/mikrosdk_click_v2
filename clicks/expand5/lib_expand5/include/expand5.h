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
 * \brief This file contains API for Expand 5 Click driver.
 *
 * \addtogroup expand5 Expand 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EXPAND5_H
#define EXPAND5_H

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
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define EXPAND5_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EXPAND5_RETVAL  uint8_t

#define EXPAND5_OK           0x00
#define EXPAND5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address  Slave Address
 * \{
 */
#define  EXPAND5_I2C_ADR_GND          0x22
#define  EXPAND5_I2C_ADR_VCC          0x23
/** \} */

/**
 * \defgroup register_map_and_configurations Register map and Configurations
 * \{
 */
#define  EXPAND5_RA_IN_0              0x00
#define  EXPAND5_RA_IN_1              0x01
#define  EXPAND5_RA_IN_2              0x02
#define  EXPAND5_RA_OUT_0             0x04
#define  EXPAND5_RA_OUT_1             0x05
#define  EXPAND5_RA_OUT_2             0x06
#define  EXPAND5_RA_POL_0             0x08
#define  EXPAND5_RA_POL_1             0x09
#define  EXPAND5_RA_POL_2             0x0A
#define  EXPAND5_RA_CFG_0             0x0C
#define  EXPAND5_RA_CFG_1             0x0D
#define  EXPAND5_RA_CFG_2             0x0E

#define  EXPAND5_AUTO_INC             0x80

#define  EXPAND5_LOW                  0
#define  EXPAND5_HIGH                 1

#define  EXPAND5_POL_NORMAL           0
#define  EXPAND5_POL_INVERTED         1

#define  EXPAND5_OUT                  0
#define  EXPAND5_IN                   1

#define  EXPAND5_P00                  0
#define  EXPAND5_P01                  1
#define  EXPAND5_P02                  2
#define  EXPAND5_P03                  3
#define  EXPAND5_P04                  4
#define  EXPAND5_P05                  5
#define  EXPAND5_P06                  6
#define  EXPAND5_P07                  7
#define  EXPAND5_P10                  8
#define  EXPAND5_P11                  9
#define  EXPAND5_P12                  10
#define  EXPAND5_P13                  11
#define  EXPAND5_P14                  12
#define  EXPAND5_P15                  13
#define  EXPAND5_P16                  14
#define  EXPAND5_P17                  15
#define  EXPAND5_P20                  16
#define  EXPAND5_P21                  17
#define  EXPAND5_P22                  18
#define  EXPAND5_P23                  19
#define  EXPAND5_P24                  20
#define  EXPAND5_P25                  21
#define  EXPAND5_P26                  22
#define  EXPAND5_P27                  23
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

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} expand5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} expand5_cfg_t;

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
void expand5_cfg_setup ( expand5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
EXPAND5_RETVAL expand5_init ( expand5_t *ctx, expand5_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void expand5_generic_write ( expand5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void expand5_generic_read ( expand5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Read bit function
 *
 * @param ctx          Click object.
 * @param reg_adr  8-bit value that defines the register
 * @param bit_num  8-bit value that defines the specific bit
 *
 * @returns 8-bit value that represents the specific bit's value
 *
 * Function is used to read state of a single bit of data from user defined register.
**/
uint8_t expand5_read_bit ( expand5_t *ctx, uint8_t reg_adr, uint8_t bit_num );

/**
 * @brief Write bit function
 *
 * @param ctx      Click object.
 * @param reg_adr  8-bit value that defines the register
 * @param bit_num  8-bit value that defines the specific bit
 * @param pin_val  8-bit value that defines the specific bit's value
 *
 * Function is used to set or clear the specific bit.
**/
void expand5_write_bit ( expand5_t *ctx, uint8_t reg_adr, uint8_t bit_num, uint8_t pin_val );

/**
 * @brief Get a single INPUT pin's logic level function
 *
 * @param ctx  Click object.
 * @param pin  16-bit value that defines the specific pin
 *
 * @returns 8-bit value that represents the specific pin's state
 *
 * Function is used to read the state of a defined pin.
**/
uint8_t expand5_read_pin ( expand5_t *ctx, uint16_t pin );

/**
 * @brief Get all pin logic levels from one bank function
 *
 * @param ctx  Click object.
 * @param bank 8-bit value that defines the bank
 *
 * @returns 8-bit value that represents the states of pins in selected bank.
 *
 * Function is used to read the states of pins in selected bank.
**/
uint8_t expand5_read_bank ( expand5_t *ctx, uint8_t bank );

/**
 * @brief Get all pins logic levels from all banks function
 *
 * @param ctx    Click object.
 * @param bank0  8-bit value that represents the states of pins in first bank
 * @param bank1  8-bit value that represents the states of pins in second bank
 * @param bank2  8-bit value that represents the states of pins in third bank
 *
 * Function is used to read the states of pins in all banks.
**/
void expand5_read_all_banks ( expand5_t *ctx, uint8_t *bank0, uint8_t *bank1, uint8_t *bank2 );

/**
 * @brief Get a single OUTPUT pin's setting function
 *
 * @param ctx  Click object.
 * @param pin  16-bit value that defines the specific pin
 *
 * @returns Pin output setting (0 or 1)
 *
 * Function is used to get a single OUTPUT pin's setting.
 * @note Note that this returns the level set in the flip-flop, and does not
 * necessarily represent the actual logic level present at the pin..
**/
uint8_t expand5_get_pin_out_lvl ( expand5_t *ctx, uint16_t pin );

/**
 * @brief Get all pin output settings from one bank function
 *
 * @param ctx  Click object.
 * @param bank 8-bit value that defines the bank
 *
 * @returns Pin output setting (0 or 1)
 *
 * Function is used to get all pin output settings from one bank.
 * @note Note that this returns the level set in the flip-flop, and does not
 * necessarily represent the actual logic level present at the pin.
**/
uint8_t expand5_get_bank_out_lvl ( expand5_t *ctx, uint8_t bank );

/**
 * @brief Get all pin output settings from all banks function
 *
 * @param ctx    Click object.
 * @param bank0  8-bit value that represents the pin output setting of the first bank
 * @param bank1  8-bit value that represents the pin output setting of the second bank
 * @param bank2  8-bit value that represents the pin output setting of the third bank
 *
 * Function is used to get all pin output settings from all banks.
 * @note Note that this returns the level set in the flip-flop, and does not
 * necessarily represent the actual logic level present at the pin.
**/
void expand5_get_all_banks_out_lvl ( expand5_t *ctx, uint8_t *bank0, uint8_t *bank1, uint8_t *bank2 );

/**
 * @brief Set a single OUTPUT pin's logic level function
 *
 * @param ctx  Click object.
 * @param pin 8-bit value that defines the specific pin
 * @param pin_val 8-bit value that defines the specific pin's value
 *
 * Function is used to set a single output pin's logic level.
**/
void expand5_write_pin ( expand5_t *ctx, uint16_t pin, uint8_t pin_val );

/**
 * @brief Set all OUTPUT pins' logic levels in one bank function
 *
 * @param ctx  Click object.
 * @param bank  8-bit value that defines which bank to write to ( 0/1/2 for P0*, P1*, P2* respectively )
 * @param value  8-bit value that defines pins' output logic level (0 or 1 for each pin).
 *
 * Function is used to set logic levels in one bank.
**/
void expand5_write_bank ( expand5_t *ctx, uint8_t bank, uint8_t value );

/**
 * @brief Set all OUTPUT pins' logic levels in all banks function
 *
 * @param ctx    Click object.
 * @param bank0  8-bit value that defines the first bank's new logic values
 * @param bank1  8-bit value that defines the second bank's new logic values
 * @param bank2  8-bit value that defines the third bank's new logic values
 *
 * Function is used to set logic levels in all banks.
**/
void expand5_write_all_banks ( expand5_t *ctx, uint8_t bank0, uint8_t bank1, uint8_t bank2 );

/**
 * @brief Get a single pin's polarity ( normal/inverted ) setting function
 *
 * @param ctx  Click object.
 * @param pin  16-bit value that defines the specific pin
 *
 * @returns single pin's polarity setting (0 or 1)
 *
 * Function is used to get a single pin's polarity.
**/
uint8_t expand5_get_pin_pol ( expand5_t *ctx, uint16_t pin );

/**
 * @brief Get all pin polarity ( normal/inverted ) settings from one bank function
 *
 * @param ctx  Click object.
 * @param bank 8-bit value that defines which bank to read ( 0/1/2 for P0*, P1*, P2* respectively )
 *
 * @returns 8 pins' polarity settings (0 or 1 for each pin)
 *
 * Function is used to get polarity settings from one bank.
**/
uint8_t expand5_get_bank_pol ( expand5_t *ctx, uint8_t bank );

/**
 * @brief Get all pin polarity ( normal/inverted ) settings from all banks function
 *
 * @param ctx    Click object.
 * @param bank0  8-bit value that represents the pin polarity settings of the first bank
 * @param bank1  8-bit value that represents the pin polarity settings of the second bank
 * @param bank2  8-bit value that represents the pin polarity settings of the third bank
 *
 * Function is used to get polarity settings from all banks.
**/
void expand5_get_all_banks_pol ( expand5_t *ctx, uint8_t *bank0, uint8_t *bank1, uint8_t *bank2 );

/**
 * @brief Set a single pin's polarity ( normal/inverted ) setting function
 *
 * @param ctx  Click object.
 * @param pin  16-bit value that defines the specific pin
 * @param polarity  pin polarity setting (0 or 1)
 *
 * Function is used to set a single pin's polarity.
**/
void expand5_set_pin_pol ( expand5_t *ctx, uint16_t pin, uint8_t polarity );

/**
 * @brief Set all pin polarity ( normal/inverted ) settings in one bank function
 *
 * @param ctx  Click object.
 * @param bank 8-bit value that defines which bank to write to (0/1/2 for P0*, P1*, P2* respectively)
 * @param polarity  8-bit value that defines new pins' polarity settings (0 or 1 for each pin)
 *
 * Function is used to set a pin polarity settings in one bank.
**/
void expand5_set_bank_pol ( expand5_t *ctx, uint8_t bank, uint8_t polarity );

/**
 * @brief Set all pin polarity ( normal/inverted ) settings in all banks function
 *
 * @param ctx    Click object.
 * @param bank0  8-bit value that defines the new pin polarity settings of the first bank
 * @param bank1  8-bit value that defines the new pin polarity settings of the second bank
 * @param bank2  8-bit value that defines the new pin polarity settings of the third bank
 *
 * Function is used to set a pin polarity settings in all banks.
**/
void expand5_set_all_banks_pol ( expand5_t *ctx, uint8_t bank0, uint8_t bank1, uint8_t bank2 );

/**
 * @brief Get a single pin's direction ( I/O ) setting function
 *
 * @param ctx  Click object.
 * @param pin  16-bit value that defines the specific pin
 *
 * @returns Pin direction setting (0 for output or 1 for input)
 *
 * Function is used to get a single pin's direction ( I/O ) setting.
**/
uint8_t expand5_get_pin_dir ( expand5_t *ctx, uint16_t pin );

/**
 * @brief Get all pin direction ( I/O ) settings from one bank function
 *
 * @param ctx   Click object.
 * @param bank  8-bit value that defines which bank to read ( 0/1/2 for P0*, P1*, P2* respectively )
 *
 * @returns direction settings (0 or 1) for each pin in the bank.
 *
 * Function is used to get all pins direction settings from one bank.
**/
uint8_t expand5_get_bank_dir ( expand5_t *ctx, uint8_t bank );

/**
 * @brief Get all pin direction ( I/O ) settings from all banks function
 *
 * @param ctx    Click object.
 * @param bank0  8-bit value that represents pins' direction settings of the first bank
 * @param bank1  8-bit value that represents pins' direction settings of the second bank
 * @param bank2  8-bit value that represents pins' direction settings of the third bank
 *
 * Function is used to get all pins direction settings from all banks.
**/
void expand5_get_all_dir ( expand5_t *ctx, uint8_t *bank0, uint8_t *bank1, uint8_t *bank2 );

/**
 * @brief Set a single pin's direction ( I/O ) setting function
 *
 * @param ctx  Click object.
 * @param pin  16-bit value that defines the specific pin
 * @param direction  pin's direction setting (0 or 1)
 *
 * Function is used to set a single pin's direction ( I/O ) setting.
**/
void expand5_set_pin_dir( expand5_t *ctx, uint16_t pin, uint8_t direction );

/**
 * @brief Set all pin direction ( I/O ) settings in one bank function
 *
 * @param ctx   Click object.
 * @param bank  8-bit value that defines which bank to write to ( 0/1/2 for P0*, P1*, P2* respectively )
 * @param direction  pins' direction settings (0 or 1) for each pin.
 *
 * Function is used to set pins' direction ( I/O ) setting in one bank.
**/
void expand5_set_bank_dir ( expand5_t *ctx, uint8_t bank, uint8_t direction );

/**
 * @brief Set all pin direction ( I/O ) settings in all banks function
 *
 * @param ctx    Click object.
 * @param bank0  8-bit value that defines pins' new direction settings of the first bank
 * @param bank1  8-bit value that defines pins' new direction settings of the second bank
 * @param bank2  8-bit value that defines pins' new direction settings of the third bank
 *
 * Function is used to set pins' direction ( I/O ) setting in all banks.
**/
void expand5_set_all_dir ( expand5_t *ctx, uint8_t bank0, uint8_t bank1, uint8_t bank2 );

/**
 * @brief Reset function
 *
 * @param ctx  Click object.
 * 
 * Function is used to reset the device.
 * @note Functon holds two 100 ms reset delays.
**/
void expand5_reset ( expand5_t *ctx );

/**
 * @brief Get Interrupt state function
 *
 * @param ctx  Click object.
 * 
 * @return
 * - 1 : Interrupt has not occured
 * - 0 : Interrupt has occured
 *
 * Function is used to check if an interrupt has occured.
**/
uint8_t expand5_check_int ( expand5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _EXPAND5_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
