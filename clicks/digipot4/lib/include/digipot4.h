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
 * \brief This file contains API for Digi Pot 4 Click driver.
 *
 * \addtogroup digipot4 Digi Pot 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DIGIPOT4_H
#define DIGIPOT4_H

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

#define DIGIPOT4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DIGIPOT4_RETVAL  uint8_t

#define DIGIPOT4_OK           0x00
#define DIGIPOT4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup write_wiper_register_1_and_2   Write Wiper Register 1 and 2
 * \{
 */
#define DIGIPOT4_WIPER_REG_1  0x01
#define DIGIPOT4_WIPER_REG_2  0x02
/** \} */

/**
 * \defgroup write_nv_register_1_and_2   Write NV Register 1 and 2
 * \{
 */
#define DIGIPOT4_NV_REG_1     0x11
#define DIGIPOT4_NV_REG_2     0x12
/** \} */

/**
 * \defgroup copy_wiper_register_1_to_nv_register_1_or_2_or_both    Copy Wiper Register 1 to NV Register 1(or 2 or both)
 * \{
 */
#define DIGIPOT4_COPY_WIPER_TO_NV_1     0x21
#define DIGIPOT4_COPY_WIPER_TO_NV_2     0x22
#define DIGIPOT4_COPY_WIPER_TO_NV_1_2   0x23
/** \} */

/**
 * \defgroup copy_nv_register_1_to_wiper_register_1_or_2_or_both    Copy NV Register 1 to Wiper Register 1(or 2 or both)
 * \{
 */
#define DIGIPOT4_COPY_NV_TO_WIPER_1     0x31
#define DIGIPOT4_COPY_NV_TO_WIPER_2     0x32
#define DIGIPOT4_COPY_NV_TO_WIPER_1_2   0x33
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
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} digipot4_t;

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

} digipot4_cfg_t;

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
void digipot4_cfg_setup ( digipot4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DIGIPOT4_RETVAL digipot4_init ( digipot4_t *ctx, digipot4_cfg_t *cfg );

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
void digipot4_generic_transfer ( digipot4_t *ctx, uint8_t *wr_buf, 
                                uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Writes data in register.
 *
 * @param ctx          Click object.
 * @param reg          Register
 * @param value        Value
 *
 * @description This function writes data in wiper register and NV register.
 */
void digipot4_write_reg ( digipot4_t *ctx, uint8_t reg, uint16_t value );

/**
 * @brief Copy data.
 *
 * @param ctx          Click object.
 * @param reg          Register
 *
 * @description This function is used to copy the data from the wipers to the NV memory
   and from the NV memory it wipers.
 */
void digipot4_copy_reg ( digipot4_t *ctx, uint8_t reg );

#ifdef __cplusplus
}
#endif
#endif  // _DIGIPOT4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
