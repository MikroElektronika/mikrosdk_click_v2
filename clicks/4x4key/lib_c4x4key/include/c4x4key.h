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
 * \brief This file contains API for 4x4 Key Click driver.
 *
 * \addtogroup c4x4key 4x4 Key Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C4X4KEY_H
#define C4X4KEY_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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

#define C4X4KEY_MAP_MIKROBUS( cfg, mikrobus )       \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )  

/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C4X4KEY_RETVAL  uint8_t

#define C4X4KEY_OK           0x00
#define C4X4KEY_INIT_ERROR   0xFF

// Button value

#define C4X4KEY_BUTTON_0          0xEFFF
#define C4X4KEY_BUTTON_1          0xFFFE
#define C4X4KEY_BUTTON_2          0xFFFD
#define C4X4KEY_BUTTON_3          0xFFFB
#define C4X4KEY_BUTTON_4          0xFFEF
#define C4X4KEY_BUTTON_5          0xFFDF
#define C4X4KEY_BUTTON_6          0xFFBF
#define C4X4KEY_BUTTON_7          0xFEFF
#define C4X4KEY_BUTTON_8          0xFDFF
#define C4X4KEY_BUTTON_9          0xFBFF
#define C4X4KEY_BUTTON_A          0xFFF7
#define C4X4KEY_BUTTON_B          0xFF7F
#define C4X4KEY_BUTTON_C          0xF7FF
#define C4X4KEY_BUTTON_D          0xBFFF
#define C4X4KEY_BUTTON_STAR       0x7FFF
#define C4X4KEY_BUTTON_HASH       0xDFFF


// Max 16-bit

#define C4X4KEY_MAX_16_BIT        0xFFFF
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

} c4x4key_t;

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

} c4x4key_cfg_t;

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
void c4x4key_cfg_setup ( c4x4key_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C4X4KEY_RETVAL c4x4key_init ( c4x4key_t *ctx, c4x4key_cfg_t *cfg );

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
void c4x4key_generic_transfer ( c4x4key_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Get 16-bit data function.
 *
 * @param ctx          Click object.
 * @return             16-bit data.
 *
 * @description Function read 16-bit data from the 74HC165 chip.
 */
uint16_t c4x4key_get_data ( c4x4key_t *ctx );

/**
 * @brief Get position pressed button function.
 *
 * @param ctx          Click object.
 * @return             8-bit position value.
 *
 * @description Function get 8-bit position of the pressed button 
 * from the 74HC165 chip.
 */
uint8_t c4x4key_get_btn_position ( c4x4key_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C4X4KEY_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
