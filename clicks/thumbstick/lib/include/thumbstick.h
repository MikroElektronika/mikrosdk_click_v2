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
 * \brief This file contains API for Thumbstiick Click driver.
 *
 * \addtogroup thumbstick Thumbstiick Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef THUMBSTICK_H
#define THUMBSTICK_H

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

#define THUMBSTICK_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define THUMBSTICK_RETVAL  uint8_t

#define THUMBSTICK_OK           0x00
#define THUMBSTICK_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup registers Registers
 * \{
 */
#define THUMBSTICK_START_SINGLE_ENDED_BIT 0x04
#define THUMBSTICK_CHANNEL_V              0x00
#define THUMBSTICK_CHANNEL_H              0x40
#define THUMBSTICK_POSITION_START         0x00
#define THUMBSTICK_POSITION_TOP           0x01
#define THUMBSTICK_POSITION_RIGHT         0x02
#define THUMBSTICK_CHANNEL_BOTTOM         0x03
#define THUMBSTICK_CHANNEL_LEFT           0x04
#define THUMBSTICK_BUTTON_INACTIVE        0x00
#define THUMBSTICK_BUTTON_ACTIVE          0x01
/** \} */

/**
 * \defgroup press_button Press button state
 * \{
 */
#define THUMBSTICK_PRESS_BUTTON 0x00
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

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} thumbstick_t;

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

    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} thumbstick_cfg_t;

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
void thumbstick_cfg_setup ( thumbstick_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param thumbstick Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
THUMBSTICK_RETVAL thumbstick_init ( thumbstick_t *ctx, thumbstick_cfg_t *cfg );

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
void thumbstick_generic_transfer 
( 
    thumbstick_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Generic read 2 byte of data function
 *
 * @param read_channel
 * <pre>
 * - Channel:
 * - 1 : first channel;
 * - 2 : secound channel;
 *</pre>
 *
 * @return 14-bit read ADC data
 *
 * @description Function read 14-bit ADC data from selected channel
 * from MCP3204 chip of the Thumbstick Click.
 */
uint16_t thumbstick_read_data( thumbstick_t *ctx, uint8_t channel );

/**
 * @brief Get thumbstick position function
 *
 * @return 8-bit data of position
 * <pre>
 * - 0 : Start           Position;
 * - 1 : Top             Position;
 * - 2 : Right           Position;
 * - 3 : Bottom          Position;
 * - 4 : Left            Position;
 *</pre>
 *
 * @description Function get position of thumbstick,
 * return position state value from 0 to 5 that calculeted
 * by the value read ADC value from the MCP3204 chip.
 */
uint8_t thumbstick_get_position( thumbstick_t *ctx );

/**
 * @brief Get state of thumbstick button function
 *
 * @return state of thumbstick button:
 * <pre>
 * - 1 : not active;
 * - 0 : active;
 *</pre>
 *
 * @description Function return state of thumbstick button 0 or 1
 * by read state of INT pin from MCP3204 chip of the Thumbstick Click.
 */
uint8_t thumbstick_button_state( thumbstick_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _THUMBSTICK_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
