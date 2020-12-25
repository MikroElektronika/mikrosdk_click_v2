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
 * \brief This file contains API for UT 7-SEG Click driver.
 *
 * \addtogroup ut7seg UT 7-SEG Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UT7SEG_H
#define UT7SEG_H

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

#define UT7SEG_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.oe = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UT7SEG_RETVAL  uint8_t

#define UT7SEG_OK           0x00
#define UT7SEG_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup dot_position Dot position
 * \{
 */
#define UT7SEG_DOT_LEFT       0x02
#define UT7SEG_DOT_RIGHT      0x01
#define UT7SEG_DOT_LEFT_RIGHT 0x03
#define UT7SEG_NO_DOT         0x00
/** \} */

/**
 * \defgroup display_state Display state
 * \{
 */
#define UT7SEG_DISPLAY_ON 0x01
#define UT7SEG_DISPLAY_OFF 0x00
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

    digital_out_t oe;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} ut7seg_t;

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

    pin_name_t oe;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} ut7seg_cfg_t;

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
void ut7seg_cfg_setup ( ut7seg_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ut7seg Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
UT7SEG_RETVAL ut7seg_init ( ut7seg_t *ctx, ut7seg_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for ut7Seg click.
 * @note Default settings is: Sets the display to ON state..
 */
void ut7seg_default_cfg ( ut7seg_t *ctx );

/**
 * @brief Display number
 *
 * @param ctx          Click object.
 * @param number       Number from 0 to 99.
 * @param dot_pos      Dot position (No use dot, dot left, dot right and dot
 * left and right).
 *
 * @description This function is used to show the number on the display.
 */
void utl7segr_display_number ( ut7seg_t *ctx, uint8_t number, uint8_t dot_pos );

/**
 * @brief Display state
 *
 * @param ctx          Click object.
 * @param state        Display state (ON or OFF state).
 */
void ut7seg_display_state ( ut7seg_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // UT7SEG_H

/** \} */ // End public_function group
/// \}    // End click Driver group
/*! @} */
// ------------------------------------------------------------------------ END
