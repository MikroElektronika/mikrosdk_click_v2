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
 * \brief This file contains API for Fram Click driver.
 *
 * \addtogroup fram Fram Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FRAM_H
#define FRAM_H

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

#define FRAM_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.hld   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.wp    = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FRAM_RETVAL  uint8_t

#define FRAM_OK           0x00
#define FRAM_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup op_codes OP-CODEs
 * \{
 */
#define FRAM_WREN           0x06
#define FRAM_WRDI           0x04
#define FRAM_RDSR           0x05
#define FRAM_WRSR           0x01
#define FRAM_READ           0x03
#define FRAM_WRITE          0x02
/** \} */

/**
 * \defgroup status_register_bits Status Register Bits
 * \{
 */
#define FRAM_WPEN           0x80
#define FRAM_BP1            0x08
#define FRAM_BP0            0x04
#define FRAM_WEL            0x02

#define FRAM_MEM_SIZE       0x8000
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
    digital_out_t hld;
    digital_out_t wp;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} fram_t;

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

    pin_name_t hld;
    pin_name_t wp;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} fram_cfg_t;

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
void fram_cfg_setup ( fram_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
FRAM_RETVAL fram_init ( fram_t *ctx, fram_cfg_t *cfg );

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
void fram_generic_transfer ( fram_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Fram click init function.
 *
 * @param ctx  Click object.
 *
 * @description This function that initializes Fram click by setting Chip select.
 */
void fram_init_f ( fram_t *ctx );

/**
 * @brief Fram click Write Enable function.
 *
 * @param ctx  Click object.
 *
 * @description This function that sends write enable command to the chip.
 */
void fram_write_enable ( fram_t *ctx );

/**
 * @brief Fram click Write Disable function.
 *
 * @param ctx  Click object.
 *
 * @description This function that sends write disable command to the chip.
 */
void fram_write_disable ( fram_t *ctx );

/**
 * @brief Fram click Read Status function.
 *
 * @param ctx  Click object.
 *
 * @description This function returns content of FRAM status register.
 */
uint8_t fram_read_status ( fram_t *ctx ) ;

/**
 * @brief Fram click Write Status function.
 *
 * @param ctx  Click object.
 *
 * @description This function writes in FRAM status register.
 */
void fram_write_status ( fram_t *ctx, uint8_t value );

/**
 * @brief Fram read function.
 *
 * @param ctx       Click object.
 * @param address   Desired starting address (0x0000 to FRAM_MEM_SIZE).
 * @param buffer    Pointer to read buffer.
 * @param count     Number of bytes to be read.
 *
 * @description This function reads sequential memory locations to buffer.
 */
void fram_read ( fram_t *ctx, uint16_t address, uint8_t *buffer, uint16_t count );

/**
 * @brief Fram write function.
 *
 * @param ctx       Click object.
 * @param address   Desired starting address (0x0000 to FRAM_MEM_SIZE).
 * @param buffer    Pointer to read buffer.
 * @param count     Number of bytes to be read.
 *
 * @description This function writes to sequential memory locations from buffer.
 */
void fram_write ( fram_t *ctx, uint16_t address, uint8_t *buffer, uint16_t count );

/**
 * @brief Fram erase all function.
 *
 * @param ctx  Click object.
 *
 * @description This function flushes whole data memory and resets status reg.
 */
void fram_erase_all ( fram_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _FRAM_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
