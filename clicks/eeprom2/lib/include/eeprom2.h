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
 * \brief This file contains API for EEPROM 2 Click driver.
 *
 * \addtogroup eeprom2 EEPROM 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EEPROM2_H
#define EEPROM2_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
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

#define EEPROM2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EEPROM2_RETVAL  uint8_t

#define EEPROM2_OK           0x00
#define EEPROM2_INIT_ERROR   0xFF
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
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} eeprom2_t;

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

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} eeprom2_cfg_t;

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
void eeprom2_cfg_setup ( eeprom2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
EEPROM2_RETVAL eeprom2_init ( eeprom2_t *ctx, eeprom2_cfg_t *cfg );

/**
 * @brief Generic write function.
 *
 * @param ctx                   Click object.
 * @param memory_address        Memory address.
 * @param value                 Value to be written to memory address.
 *
 * @description This function writes a single byte of data to the given memory address.
 */
void eeprom2_write ( eeprom2_t *ctx, uint32_t memory_address, uint8_t value );

/**
 * @brief Function to write bytes.
 *
 * @param ctx                   Click object.
 * @param memory_address        Memory address.
 * @param value                 Values to be written to memory address.
 * @param count                 Count of data (in bytes, max 256) to be written.
 *
 * @description This function writes bytes of data to the given memory address.
 */
void eeprom2_write_bytes( eeprom2_t *ctx, uint32_t memory_address, uint8_t *value, uint8_t count );

/**
 * @brief Generic read function.
 *
 * @param ctx                   Click object.
 * @param memory_address        Memory address.
 *
 * @returns                     Data read from the given memory address.
 * @description This function reads a single byte from the given memory address.
 */
uint8_t eeprom2_read( eeprom2_t *ctx, uint32_t memory_address );

/**
 * @brief Function to read bytes.
 *
 * @param ctx                   Click object.
 * @param memory_address        Memory address.
 * @param value                 Values read from the given memory address.
 * @param count                 Count of data read from memory.
 * 
 * @description This function reads bytes from the given memory address.
 */
void eeprom2_read_bytes( eeprom2_t *ctx, uint32_t memory_address, uint8_t *value, uint8_t count );

/**
 * @brief Enable EEPROM memory.
 *
 * @param ctx                   Click object.
 * 
 * @description This function enables EEPROM memory.
 */
void eeprom2_memory_enable ( eeprom2_t *ctx );

/**
 * @brief Disable EEPROM memory.
 *
 * @param ctx                   Click object.
 * 
 * @description This function disables EEPROM memory.
 */
void eeprom2_memory_disable ( eeprom2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _EEPROM2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
