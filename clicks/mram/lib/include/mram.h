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
 * \brief This file contains API for MRAM Click driver.
 *
 * \addtogroup mram MRAM Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MRAM_H
#define MRAM_H

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

#define MRAM_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.wp    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.hld   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MRAM_RETVAL  uint8_t
#define MRAM_OK           0x00
#define MRAM_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mram_registers Mram registers
 * \{
 */
#define MRAM_WRITE_ENABLE_BIT               0x02
#define MRAM_MEMORY_BLOCK_BIT0              0x04
#define MRAM_MEMORY_BLOCK_BIT1              0x08
#define MRAM_STATUS_WRITE_DISABLE_BIT       0x80
#define MRAM_FIRST_ADDRESS_LOCATION         0x0000
#define MRAM_ADDRESS_LOCATION_0             0x000F
#define MRAM_ADDRESS_LOCATION_1             0x00FF
#define MRAM_ADDRESS_LOCATION_2             0x0FFF
#define MRAM_LAST_ADDRESS_LOCATION          0x7FFF
#define MRAM_LOGIC_HIGH                     0x01
#define MRAM_LOGIC_LOW                      0x00
#define MRAM_NONE_PROTECTED_MEMORY          0x82
#define MRAM_UPPER_QUARTER_PROTECTED_MEMORY 0x86
#define MRAM_UPPER_HALF_PROTECTED_MEMORY    0x8A
#define MRAM_ALL_PROTECTED_MEMORY           0x8E
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

    digital_out_t wp;
    digital_out_t hld;
    digital_out_t cs;
    
    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;

} mram_t;

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
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} mram_cfg_t;

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
void mram_cfg_setup ( mram_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param mram Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MRAM_RETVAL mram_init ( mram_t *ctx, mram_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for MRAM click.
 */
void mram_default_cfg ( mram_t *ctx );

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
void mram_generic_transfer 
( 
    mram_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Read status reg.
 *
 * @param ctx          Click object.
 * 
 * @returns              Value of reg.
 * 
 * @description Function read status register.
 */
uint8_t mram_read_status_reg ( mram_t *ctx );

/**
 * @brief Check status bit.
 *
 * @param ctx                     Click object.
 * @param status_bit          Bit to be checked.
 * 
 * @returns                         0x01 or 0x00
 * 
 * @description                     Function return 0x01 or 0x00 depending on the status_bit.
 */
uint8_t mram_check_status_bit (mram_t *ctx, uint8_t status_bit );

/**
 * @brief Enable write.
 *
 * @param ctx   Click object.
 * 
 * @returns       If write is enabled.
 * 
 * @description     Function enables write and returs if enabling was successful.
 */
uint8_t mram_enable_write (mram_t *ctx );

/**
 * @brief Disable write.
 *
 * @param ctx   Click object.
 * 
 * @returns       If write is disabled.
 * 
 * @description     Function disables write and returs if disabling was successful.
 */
uint8_t mram_disable_write ( mram_t *ctx );

/**
 * @brief Write status reg.
 *
 * @param ctx   Click object.
 * @param transfer_data   Data to be written.
 * 
 * 
 * @description     Function writes data in status reg.
 */
void mram_write_status_reg ( mram_t *ctx, uint8_t transfer_data);

/**
 * @brief Read n byte data.
 *
 * @param ctx   Click object.
 * @param address   Adress.
 * @param buffer   Buffer holding read data.
 * @param n_bytes   Number of bytes to be read.
 * 
 * 
 * @description     Function reads n bytes of data and saves it in buffer.
 */
void mram_read_data_bytes ( mram_t *ctx, const uint16_t address, uint8_t *buffer, const uint16_t n_bytes );

/**
 * @brief Write n byte data.
 *
 * @param ctx   Click object.
 * @param address   Adress.
 * @param buffer   Buffer holding data to be written.
 * @param n_bytes   Number of bytes to be written.
 * 
 * 
 * @description     Function writes n bytes of data from the buffer.
 */
void mram_write_data_bytes ( mram_t *ctx, const uint16_t address, uint8_t *buffer, const uint16_t n_bytes );

/**
 * @brief Sleep mode.
 *
 * @param ctx   Click object.
 * 
 * 
 * @description     Function puts click board into sleep mode.
 */
void mram_enter_sleep_mode ( mram_t *ctx );

/**
 * @brief Wake up.
 *
 * @param ctx   Click object.
 * 
 * 
 * @description     Function wakes up the click board.
 */
void mram_wake_up_mode ( mram_t *ctx );

/**
 * @brief Enable write protection.
 *
 * @param ctx   Click object.
 * @param state State to be changed for write protect.      
 * 
 * 
 * @description     Function enables or disables write protect.
 */
void mram_enable_write_protect ( mram_t *ctx, uint8_t state);

/**
 * @brief Enable hold mode.
 *
 * @param ctx   Click object.
 * @param state State to be changed for hold mode.      
 * 
 * 
 * @description     Function enables or disables hold mode.
 */
void mram_enable_hold_mode ( mram_t *ctx, uint8_t state);

#ifdef __cplusplus
}
#endif
#endif  // _MRAM_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
