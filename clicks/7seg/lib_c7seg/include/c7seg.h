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
 * \brief This file contains API for 7seg Click driver.
 *
 * \addtogroup c7seg 7seg Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C7SEG_H
#define C7SEG_H

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

#define C7SEG_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS );   \
   cfg.mr    = MIKROBUS( mikrobus, MIKROBUS_RST );  \
   cfg.pwm   = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C7SEG_RETVAL  uint8_t

#define C7SEG_OK            0x00
#define C7SEG_INIT_ERROR    0xFF
/** \} */

/**
 * \defgroup display mode Display Mode
 * \{
 */
#define C7SEG_DISPLAY_OFF   0
#define C7SEG_DISPLAY_ON    1
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
    // Output pins 
    
    digital_out_t mr;
    digital_out_t pwm;
  
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} c7seg_t;

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

    pin_name_t mr;
    pin_name_t pwm;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} c7seg_cfg_t;

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
void c7seg_cfg_setup ( c7seg_cfg_t *cfg );

/**
 * @brief Initialization function.

 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C7SEG_RETVAL c7seg_init ( c7seg_t *ctx, c7seg_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for c7seg click.
 * @note
 *  Click default configuration:
 * -------------------------------------------------
 * <pre>
 *    Sets MR pin high
 * </pre>
 * 
 * <pre>
 *    Display on
 * </pre>
 */
void c7seg_default_cfg ( c7seg_t *ctx );

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
void c7seg_generic_transfer ( c7seg_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Generic write data function.
 *
 * @param ctx           Click object.
 * @param write_left    Left data to write.
 * @param write_right   Right data to write.
 * 
 * @description This function write left and right data on 7seg display.
 */
void c7seg_write_data ( c7seg_t *ctx, uint8_t write_left, uint8_t write_right );

/**
 * @brief Click Reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes device reset for 7seg click.
 */
void c7seg_reset ( c7seg_t *ctx );

/**
 * @brief Display mode function.
 *
 * @param ctx             Click object.
 * @param display_mode    State of display.
 *
 * @description This function sets display state for 7seg click.
 */
void c7seg_display_mode ( c7seg_t *ctx, uint8_t display_mode );

/**
 * @breif Write number on 7seg diaplay.
 *
 * @param ctx               Click object.
 * @param left_number       Left data to write.
 * @param right_number      Right data to write.
 *
 * @description This function writes left and right number on 7seg display.
 */
void c7seg_write_data_number ( c7seg_t *ctx, uint8_t left_number, uint8_t right_number );

/**
 * @breif Write character on 7seg diaplay.
 *
 * @param ctx               Click object.
 * @param left_char         Left character to write.
 * @param right_char        Right character to write.
 *
 * @description This function writes left and right character on 7seg display.
 */
void c7seg_write_data_character ( c7seg_t *ctx, char left_char, char right_char );

#ifdef __cplusplus
}
#endif
#endif  // _C7SEG_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */

// ------------------------------------------------------------------------- END
