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
 * \brief This file contains API for Thumbstick Click driver.
 *
 * \addtogroup thumbstick Thumbstick Click Driver
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

#define THUMBSTICK_OK                       0x00
#define THUMBSTICK_INIT_ERROR               0xFF
#define THUMBSTICK_FUNCTION_ERROR           0xEE
/** \} */

/**
 * \defgroup reading_type Reading adc type
 * \{
 */
#define THUMBSTICK_START_SINGLE_CONV        0x06
#define THUMBSTICK_START_DIFF_CONV          0x04
/** \} */

/**
 * \defgroup axis_macro Axis macro for thumbstick
 * \{
 */
#define THUMBSTICK_VERTICAL                 0x00
#define THUMBSTICK_HORIZONTAL               0x60
/** \} */

/**
 * \defgroup postion_state Postion state of thumbstick axes
 * \{
 */
#define THUMBSTICK_POSITION_DEFAULT         0x01
#define THUMBSTICK_POSITION_TOP             0x02
#define THUMBSTICK_POSITION_RIGHT           0x03
#define THUMBSTICK_POSITION_BOTTOM          0x04
#define THUMBSTICK_POSITION_LEFT            0x05
/** \} */

/**
 * \defgroup button_state Button state
 * \{
 */
#define THUMBSTICK_BUTTON_INACTIVE          0x00
#define THUMBSTICK_BUTTON_ACTIVE            0x01
/** \} */

/**
 * \defgroup default_sensitivity Default sensitivity data
 * \{
 */
#define POSTION_SENS_DEFAULT    500
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
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} thumbstick_cfg_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    uint8_t vertical;
    uint8_t horizontal;

} thumbstick_position_t;

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
 * @param type
 * <pre>
 * - Channel:
 * - 0x06 : single channel adc;
 * - 0x04 : difference channell adc;
 *</pre>
 * @param channel
 * <pre>
 * - Channel:
 * - 0x00 : horizontal channel;
 * - 0x60 : vertical channel;
 *</pre>
 *
 * @return 12-bit read ADC data
 *
 * @description Function read 12-bit ADC data from selected channel
 * from MCP3204 chip of the Thumbstick Click.
 */
uint16_t thumbstick_read_rawadc ( thumbstick_t *ctx, uint8_t type, uint8_t channel );

/**
 * @brief Get thumbstick position by axis function
 *
 * @param axis
 * <pre>
 * - Channel:
 * - 0x00 : horizontal axis;
 * - 0x60 : vertical axis;
 *</pre>
 * 
 * @return 8-bit data of position
 * <pre>
 * - 1 : Default         Position;
 * - 2 : Top             Position;
 * - 3 : Right           Position;
 * - 4 : Bottom          Position;
 * - 5 : Left            Position;
 * - 0xEE: Error         Parameter;
 *</pre>
 *
 * @description Function get position of thumbstick,
 * return position state value from 1 to 5 that calculeted
 * by the value read ADC value from the MCP3204 chip.
 */
uint8_t thumbstick_get_single_axis_postion ( thumbstick_t *ctx, uint8_t axis );

/**
 * @brief Get thumbstick position by axis function
 *
 * @param postion   Potion data struct that stores data of axis thumbstic postion
 *
 * @description Function get position of thumbstick.
 */
void thumbstick_get_position ( thumbstick_t *ctx, thumbstick_position_t *position );

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


/**
 * @brief Set thumbstick sensitivity
 *
 * @param sensitivity   variable that offsets changeing state of thumbstick sensing state
 * 
 * @return status
 * <pre>
 * - 0x00: OK               
 * - 0xEE: Error
 *</pre>
 *
 * @description Function for setting sensitivity that state of thumbstick changes states.
 */
uint8_t thumbstick_set_sensitivity ( uint16_t sensitivity );


#ifdef __cplusplus
}
#endif
#endif  // _THUMBSTICK_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
