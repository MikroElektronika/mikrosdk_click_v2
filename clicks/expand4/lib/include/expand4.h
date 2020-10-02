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
 * \brief This file contains API for Expand 4 Click driver.
 *
 * \addtogroup expand4 Expand 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef EXPAND4_H
#define EXPAND4_H

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

#define EXPAND4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.clr = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define EXPAND4_RETVAL  uint8_t

#define EXPAND4_OK           0x00
#define EXPAND4_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup expand_pin Expand Pins
 * \{
 */
#define EXPAND4_D0           0x01
#define EXPAND4_D1           0x02
#define EXPAND4_D2           0x04
#define EXPAND4_D3           0x08
#define EXPAND4_D4           0x10
#define EXPAND4_D5           0x20
#define EXPAND4_D6           0x40
#define EXPAND4_D7           0x80
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
    digital_out_t clr;
    digital_out_t en;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} expand4_t;

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

    pin_name_t clr;
    pin_name_t en;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} expand4_cfg_t;

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
void expand4_cfg_setup ( expand4_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
EXPAND4_RETVAL expand4_init ( expand4_t *ctx, expand4_cfg_t *cfg );

/**
 * @brief Enable output function
 *
 * @param ctx  Click object.
 * 
 * @description Function turn on output buffers - set PWM pin low
 */
void expand4_enable_output ( expand4_t *ctx );

/**
 * @brief Disable output function
 *
 * @param ctx  Click object.
 * 
 * @description Function turn off output buffers set PWM pin high
 */
void expand4_disable_output ( expand4_t *ctx );

/**
 * @brief Clear register function
 *
 * @param ctx  Click object.
 * 
 * @description Function clear input TPIC6A595 shift register.
 */
void expand4_reset ( expand4_t *ctx );

/**
 * @breif Generic write data function
 *
 * @param ctx  Click object.
 * @param write_command      8-bit data to write
 *
 * @description Function write 8-bit data function to TPIC6A595 shift register.
 */
void expand4_write_data ( expand4_t *ctx, uint8_t write_command );

/**
 * @breif Turn on output pin masks by position function
 *
 * @param ctx  Click object.
 * @param position      position from 0 to 7
 *
 * @description Function turning on output pin masks by position:
 * - 0 for D0
 * - 1 for D1
 * - 2 for D2
 * - 3 for D3
 * - 4 for D4
 * - 5 for D5
 * - 6 for D6
 * - 7 for D7
 */
void expand4_turn_on_by_position ( expand4_t *ctx, uint8_t position );

#ifdef __cplusplus
}
#endif
#endif  // _EXPAND4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
