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
 * \brief This file contains API for Rotary Click driver.
 *
 * \addtogroup rotary Rotary Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ROTARY_H
#define ROTARY_H

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

#define ROTARY_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.ecb = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.eca = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.sw = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ROTARY_RETVAL  uint8_t

#define ROTARY_OK           0x00
#define ROTARY_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup num_leds Number of LED's
 * \{
 */
#define ROTARY_ONE_LED      0x0001
#define ROTARY_TWO_LED      0x0101
#define ROTARY_FOUR_LED     0x1111
#define ROTARY_EIGHT_LED    0x5555
#define ROTARY_RESET_LED    0x0000
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
    digital_out_t cs;

    // Input pins 

    digital_in_t ecb;
    digital_in_t eca;
    digital_in_t sw;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} rotary_t;

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

    pin_name_t ecb;
    pin_name_t rst;
    pin_name_t eca;
    pin_name_t sw;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} rotary_cfg_t;

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
void rotary_cfg_setup ( rotary_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ROTARY_RETVAL rotary_init ( rotary_t *ctx, rotary_cfg_t *cfg );

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
void rotary_generic_transfer 
( 
    rotary_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Generic data write function
 *
 * @param cfg        Click configuration structure.
 * @param write_data Data to write
 *
 * @description Function turn on led by data
 */
void rotaryr_turn_on_led_by_data ( rotary_t *ctx, uint16_t write_data );

/**
 * @brief Turn on led by position
 *
 * @param cfg               Click configuration structure.
 * @param[in] led_position  Led position
 *
 * @description Function turn on led by position
 */
void rotaryr_turn_on_led_by_position ( rotary_t *ctx, uint8_t led_position );

/**
 * @brief Button push state
 *
 * @param cfg  Click configuration structure.
 *
 * @description Function return 1 if button is pushed and return 0 if not
 */
uint8_t rotaryr_button_push( rotary_t *ctx );

/**
 * @brief Get led data state
 *
 * @param current_led_state  Current state of led.
 *
 * @description Function return 16-bit data by current led state
 */
uint16_t rotaryr_get_led_data ( uint8_t current_led_state );

/**
 * @brief Reset led
 *
 * @param cfg  Click configuration structure.
 *
 * @description Function turn off all led
 */
void rotaryr_reset_led( rotary_t *ctx );

/**
 * @brief State ecb pin
 *
 * @param cfg  Click configuration structure.
 *
 * @description Function return ecb state
 */
uint8_t rotaryr_get_ecb_state( rotary_t *ctx );

/**
 * @brief State eca pin
 *
 * @param cfg  Click configuration structure.
 *
 * @description Function return eca state
 */
uint8_t rotaryr_get_eca_state( rotary_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ROTARY_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
