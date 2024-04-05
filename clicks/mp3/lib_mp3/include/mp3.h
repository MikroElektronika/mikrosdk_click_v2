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
 * \brief This file contains API for MP3 Click driver.
 *
 * \addtogroup mp3 MP3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------


#ifndef MP3_H
#define MP3_H

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

#define MP3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.dreq = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.dcs = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup commands Commands
 * \{
 */
#define MP3_WRITE_CMD               0x02
#define MP3_READ_CMD                0x03
#define MP3_BASE_ADDR               0x00
#define MP3_MODE_ADDR               0x00
#define MP3_STATUS_ADDR             0x01
#define MP3_BASS_ADDR               0x02
#define MP3_CLOCKF_ADDR             0x03
#define MP3_DECODE_TIME_ADDR        0x04
#define MP3_AUDATA_ADDR             0x05
#define MP3_WRAM_ADDR               0x06
#define MP3_WRAMADDR_ADDR           0x07
#define MP3_HDAT0_ADDR              0x08
#define MP3_HDAT1_ADDR              0x09
#define MP3_AIADDR_ADDR             0x0A
#define MP3_VOL_ADDR                0x0B
#define MP3_AICTRL0_ADDR            0x0C
#define MP3_AICTRL1_ADDR            0x0D
#define MP3_AICTRL2_ADDR            0x0E
#define MP3_AICTRL3_ADDR            0x0F
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MP3_OK                      0
#define MP3_ERROR                  -1
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
    digital_out_t dcs;

    // Input pins 
    digital_in_t dreq;
    
    // Modules 
    spi_master_t spi;           /**< SPI driver object. */

    pin_name_t   chip_select;   /**< Chip select pin descriptor (used for SPI driver). */

} mp3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t miso;            /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;            /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;             /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;              /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins 
    pin_name_t dreq;
    pin_name_t rst;
    pin_name_t dcs;

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} mp3_cfg_t;

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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void mp3_cfg_setup ( mp3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param mp3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t mp3_init ( mp3_t *ctx, mp3_cfg_t *cfg );

/**
 * @brief Functions for reset MP3 module
 */
void mp3_reset( mp3_t *ctx );

/**
 * @brief Function that checks whether busy mp3
 * @param ctx          Click object.
 * @returns  1 - is Busy / 0 - is not busy
 */
uint8_t mp3_is_busy( mp3_t *ctx );

/**
 * @brief  Function writes one byte (command) to MP3
 * @param ctx          Click object.
 * @param address   adddress of register whitch be written
 * @param input     command which be written
 */
void mp3_cmd_write( mp3_t *ctx, uint8_t address, uint16_t input );

/**
 * @brief  Function reads command from MP3
 * @param ctx          Click object.
 * @returns command that is read
 */
uint16_t mp3_cmd_read( mp3_t *ctx, uint8_t address );

/**
 * @brief  Function writes one byte ( data ) to MP3
 * @param ctx          Click object.
 * @param input        data which be written
 */
err_t mp3_data_write( mp3_t *ctx, uint8_t input );

/**
 * @brief  Function Write 32 bytes ( data ) to MP3
 * @param ctx          Click object.
 * @param input32      buffer of 32 bytes which be written
 */
err_t mp3_data_write_32( mp3_t *ctx, uint8_t *input32 );

/**
 * @brief  Function set volume to MP3 click for left and right channels
 * @param ctx          Click object.
 * @param vol_left     Volume level for left channel.
 * @param vol_right    Volume level for right channel.
 * @note Maximum volume is 0x00 and total silence is 0xFE.
 */
void mp3_set_volume ( mp3_t *ctx, uint8_t vol_left, uint8_t vol_right );

#ifdef __cplusplus
}
#endif
#endif  // _MP3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
