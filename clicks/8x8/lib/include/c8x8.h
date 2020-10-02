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
 * \brief This file contains API for 8x8 Click driver.
 *
 * \addtogroup c8x8 8x8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C8X8_H
#define C8X8_H

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

#define C8X8_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C8X8_RETVAL  uint8_t

#define C8X8_OK           0x00
#define C8X8_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup scroll_speed Scroll speed
 * \{
 */
#define C8X8_SPEED_FAST    3
#define C8X8_SPEED_MEDIUM  2
#define C8X8_SPEED_SLOW    1
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define C8X8_DECODE_MODE_REG     0x09
#define C8X8_INTENSITY_REG       0x0A
#define C8X8_SCAN_LIMIT_REG      0x0B
#define C8X8_SHUTDOWN_REG        0x0C
#define C8X8_DISPLAY_TEST_REG    0x0F
/** \} */

/**
 * \defgroup decode_mode Decode-Mode Register
 * \{
 */
#define C8X8_NO_DECODE          0x00
#define C8X8_DECODE_DIGIT_0     0x01
#define C8X8_DECODE_DIGIT_3_0   0x0F
#define C8X8_DECODE_DIGIT_7     0xFF
/** \} */

/**
 * \defgroup intensity_format Intensity Register Format
 * \{
 */
#define C8X8_INTENSITY_1    0x00
#define C8X8_INTENSITY_3    0x01
#define C8X8_INTENSITY_5    0x02
#define C8X8_INTENSITY_7    0x03
#define C8X8_INTENSITY_9    0x04
#define C8X8_INTENSITY_11   0x05
#define C8X8_INTENSITY_13   0x06
#define C8X8_INTENSITY_15   0x07
#define C8X8_INTENSITY_17   0x08
#define C8X8_INTENSITY_19   0x09
#define C8X8_INTENSITY_21   0x0A
#define C8X8_INTENSITY_23   0x0B
#define C8X8_INTENSITY_25   0x0C
#define C8X8_INTENSITY_27   0x0D
#define C8X8_INTENSITY_29   0x0E
#define C8X8_INTENSITY_31   0x0F
/** \} */

/**
 * \defgroup scan_limit_format Scan-Limit Register Format
 * \{
 */
#define C8X8_DISPLAY_DIGIT_0     0x00
#define C8X8_DISPLAY_DIGIT_0_1   0x01
#define C8X8_DISPLAY_DIGIT_0_2   0x02
#define C8X8_DISPLAY_DIGIT_0_3   0x03
#define C8X8_DISPLAY_DIGIT_0_4   0x04
#define C8X8_DISPLAY_DIGIT_0_5   0x05
#define C8X8_DISPLAY_DIGIT_0_6   0x06
#define C8X8_DISPLAY_DIGIT_0_7   0x07
/** \} */

/**
 * \defgroup shutdown_format Shutdown Register Format
 * \{
 */
#define C8X8_SHUTDOWN_MODE       0x00
#define C8X8_NORMAL_OPERATION    0x01
/** \} */

/**
 * \defgroup display_test Display-Test Format
 * \{
 */
#define C8X8_DISPLAY_NORMAL_OPERATION  0x00
#define C8X8_DISPLAY_TEST_MODE         0X01
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
    
    // ctx variable
    uint8_t speed_scroll;

} c8x8_t;

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

} c8x8_cfg_t;

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
void c8x8_cfg_setup ( c8x8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C8X8_RETVAL c8x8_init ( c8x8_t *ctx, c8x8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for c8x8 click.
 */
void c8x8_default_cfg ( c8x8_t *ctx );

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
void c8x8_generic_transfer ( c8x8_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Function for sending the command
 *
 * @param ctx          Click object.
 * @param cmd         the command to be executed
 * @param tx_data     data to be sent
 */
void c8x8_write_cmd ( c8x8_t *ctx, uint8_t cmd, uint8_t tx_data );

/**
 * @brief Function for refresh display
 *
 * @param ctx          Click object.
 *
 * @note The function switches off all LEDs
 */
void c8x8_display_refresh ( c8x8_t *ctx );

/**
 * @brief Function for settings speed scroll display string
 *
 * @param ctx          Click object.
 * @param speed        Speed that will be set
 *
 * @note Options:
 * <pre>
 *     Fast speed (30ms per character),
 *     Medium speed (100ms per character) - default speed,
 *     Slow speed ( 200ms per character),
 * </pre>
 */
void c8x8_set_speed_scroll ( c8x8_t *ctx, uint8_t speed );

/**
 * @brief Scroll string function
 *
 * @param ctx          Click object.
 * @param p_array    Pointer to the string to be displayed
 *
 * @note
 * <pre>
 *  Function that displays scrolled string with set speed.
 *  If the speed is not set before calling the function,
 *  default scroll speed is 100ms per character.
 * </pre>
 */
void c8x8_display_string ( c8x8_t *ctx, char *p_array );

/**
 * @brief Function for displaying one character
 *
 * @param ctx          Click object.
 * @param tx_byte    Character to be displayed
 *
 */
void c8x8_display_byte ( c8x8_t *ctx, char tx_byte );

/**
 * @brief Image display function
 *
 * @param ctx          Click object.
 * @param p_array       Pointer to the image to be displayed
 *
 * @note
 * <pre>
 *  Function for displays the image.
 *  The image consists of eight elements (eight columns that build the image).
 * </pre>
 */
void c8x8_display_image ( c8x8_t *ctx, uint8_t *p_image );

#ifdef __cplusplus
}
#endif
#endif  // _C8X8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
