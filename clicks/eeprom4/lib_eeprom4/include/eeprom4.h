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
 * \brief This file contains API for EEPROM 4 Click driver.
 *
 * \addtogroup eeprom4 EEPROM 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EEPROM4_H
#define EEPROM4_H

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
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 

/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define EEPROM4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.wp    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.hld   = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EEPROM4_RETVAL  uint8_t
/** \} */
#define EEPROM4_OK           0x00
#define EEPROM4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup value  Value 
 * \{
 */
#define EEPROM4_LOGIC_HIGH  1
#define EEPROM4_LOGIC_LOW   0
 /** \} */

/**
 * \defgroup bit  Bit
 * \{
 */
#define EEPROM4_READY_BIT                 0x01 
#define EEPROM4_WRITE_ENABLE_LATCH_BIT    0x02 
#define EEPROM4_WRITE_PROTECT_ENABLE_BIT  0x80 
/** \} */

/**
 * \defgroup command Command
 * \{
 */
#define EEPROM4_LOW_POWER_WRITE_POLL_COMMAND      0x08 
#define EEPROM4_SET_WRITE_ENABLE_LATCH_COMMAND    0x06 
#define EEPROM4_RESET_WRITE_ENABLE_LATCH_COMMAND  0x04 
/** \} */

/**
 * \defgroup memory_location Memory location
 * \{
 */
#define EEPROM4_FIRST_MEMORY_LOCATION                0x00000000 
#define EEPROM4_ONE_QUARTER_MEMORY_LOCATION          0x0000FFFF 
#define EEPROM4_HALF_MEMORY_LOCATION                 0x0001FFFF 
#define EEPROM4_TWO_QUARTER_MEMORY_LOCATION          0x0002FFFF 
#define EEPROM4_LAST_MEMORY_LOCATION                 0x0003FFFF 
/** \} */

/**
 * \defgroup memory_location Memory location
 * \{
 */
#define EEPROM4_NONE_PROTECTED_MEMORY_LOCATION         0x00 
#define EEPROM4_ONE_QUARTER_PROTECTED_MEMORY_LOCATION  0x04 
#define EEPROM4_HALF_PROTECTED_MEMORY_LOCATION         0x08 
#define EEPROM4_ALL_PROTECTED_MEMORY_LOCATION          0x0C 
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
    digital_out_t wp;
    digital_out_t hld;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} eeprom4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t wp;
    pin_name_t hld;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} eeprom4_cfg_t;

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
void eeprom4_cfg_setup ( eeprom4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
EEPROM4_RETVAL eeprom4_init ( eeprom4_t *ctx, eeprom4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for EEPROM 4 click.
 */
void eeprom4_default_cfg ( eeprom4_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void eeprom4_generic_transfer ( eeprom4_t *ctx, uint8_t *wr_buf, 
                                uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Command send function
 *
 * @param  command_byte     Click instruction
 *
 * @param ctx               Click object.    
 *
 * @description Function sends command (instruction) to click. In case that command byte is EEPROM4_LOW_POWER_WRITE_POLL_COMMAND (0x08)
 * function returns 0x00 if part is not in a write cycle and returns 0xFF is part still busy completing the write cycle.
 * In other case function returns 0.
 */
uint8_t eeprom4_send_command ( eeprom4_t *ctx, uint8_t command_byte );

/**
 * @brief Status register write function
 *
 * @param data_value        Data to be written in status register
 *
 * @param ctx               Click object.
 * 
 * @description Function writes data determined in parametar of function to status register.
 */
void eeprom4_write_status_reg ( eeprom4_t *ctx, uint8_t data_value );

/**
 * @brief Status register read function
 *
 * @param ctx               Click object.
 *
 * @description Function reads one byte data value from status register.
 */
uint8_t eeprom4_read_status_reg ( eeprom4_t *ctx );

/**
 * @brief Memory array write function
 *
 * @param ctx                    Click object.
 * @param memory_address         Address where data be written
 * @param data_input             Pointer to buffer witch from data be written
 * @param nBytes                 Number of bytes witch will be written
 *
 * @descripption Function writes number of bytes determined by nBytes parametar from buffer determined by data_input pointer
 * to memory location determined by memory_address parametar.
 */
void eeprom4_write_memory ( eeprom4_t *ctx, uint32_t memory_address, uint8_t *data_input, uint8_t n_bytes );

/**
 * @brief Memory array read function
 *
 * @param ctx                    Click object.
 * @param memory_address         Address where from data will be read
 * @param data_output            Pointer to buffer where data be storaged
 * @param nBytes                 Number of bytes witch will be read
 *
 * @description Function reads number of bytes determined by nBytes parametar from memory location determined by memory_address parametar
 * and stores bytes to buffer determined by data_output pointer.
 */
void eeprom4_read_memory ( eeprom4_t *ctx, uint32_t memory_address, uint8_t *data_output, uint8_t n_bytes );

/**
 * @brief Write Protect enable function
 *
 * @param ctx          Click object.
 * @param state        Value witch set or reset RST (WP) pin
 *
 *  @description Function sets RST pin on state value to enable or disable writting to status register and memory array.
 * WP pin is used in conjuction with the block protection bits of the status register and with WPEN and WEL
 * bits also.
 */
void eeprom4_enable_write_protect ( eeprom4_t *ctx, uint8_t state );

/**
 * @brief Hold operation enable function
 *
 * @param ctx          Click object.
 * @param state        Value witch set or reset PWM (HLD) pin
 *
 * @description Function enables or disables the Hold operation. To pause the serial communication with the master device without
 * resetting the serial sequence, the HOLD pin must be brought low. To resume serial communication, HOLD pin must be brought high.
 */
void eeprom4_enable_hold_operation ( eeprom4_t *ctx, uint8_t state );

/**
 * @brief Status register bits check function
 *
 * @param ctx          Click object.
 * @param check_bit    Determined witch bit in status register be checked
 *
 * @description Function checks value of status register bit determined by check_bit parametar.
 */
uint8_t eeprom4_check_status_reg ( eeprom4_t *ctx, uint8_t check_bit );


#ifdef __cplusplus
}
#endif
#endif  // _EEPROM4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
