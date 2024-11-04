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
 * \brief This file contains API for FRAM 2 Click driver.
 *
 * \addtogroup fram2 FRAM 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef FRAM2_H
#define FRAM2_H

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

#define FRAM2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.wp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.hld = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define FRAM2_RETVAL  uint8_t

#define FRAM2_OK           0x00
#define FRAM2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup other_macros Other Macros
 * \{
 */
#define FRAM_WREN       0x06
#define FRAM_WRDI       0x04
#define FRAM_RDSR       0x05
#define FRAM_WRSR       0x01
#define FRAM_READ       0x03
#define FRAM_WRITE      0x02
#define FRAM_MEM_SIZE   0x80000
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

} fram2_t;

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

} fram2_cfg_t;

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
void fram2_cfg_setup ( fram2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
FRAM2_RETVAL fram2_init ( fram2_t *ctx, fram2_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration i.e enable write operation for
 * FRAM 2 Click.
 */
void fram2_default_cfg ( fram2_t *ctx );

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
void fram2_generic_transfer ( fram2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len );

/**
 * @brief Enable write operation
 *
 * @param ctx          Click object.
 *
 * @description This function sends write enable command to the Click.
 */
void fram2_write_enable ( fram2_t *ctx );

/**
 * @brief Disable write operation
 *
 * @param ctx          Click object.
 *
 * @description This function sends write disable command to the Click.
 */
void fram2_write_disable ( fram2_t *ctx );

/**
 * @brief Read Fram Click status
 *
 * @param ctx          Click object.
 *
 * @returns Content of FRAM status register.
 *
 * @description This function reads content of FRAM status register.
 */
uint8_t fram2_read_status ( fram2_t *ctx ); 

/**
 * @brief Write Fram Click status
 *
 * @param ctx          Click object.
 * @param value        Value to be written.
 *
 * @description This function writes value to FRAM status register.
 */
void fram2_write_status ( fram2_t *ctx, uint8_t value ); 

/**
 * @brief Read from FRAM Click memory.
 *
 * @param ctx          Click object.
 * @param address      Desired starting address (0x0000 to FRAM_MEM_SIZE).
 * @param buffer       Pointer to read buffer.
 * @param count        Number of bytes to be read.
 * 
 * @description This function reads content from address and saves it
 * to buffer.
 */
void fram2_read ( fram2_t *ctx, uint32_t address, uint8_t *buffer, uint8_t count ); 

/**
 * @brief Write to FRAM Click memory.
 *
 * @param ctx          Click object.
 * @param address      Address to write to (0x0000 to FRAM_MEM_SIZE).
 * @param buffer       Pointer to write buffer.
 * @param counter      Number of bytes to be written.
 * 
 * @description This function writes content from buffer to address.
 */
void fram2_write( fram2_t *ctx, uint32_t address, uint8_t *buffer, uint8_t counter ); 


#ifdef __cplusplus
}
#endif
#endif  // _FRAM2_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
