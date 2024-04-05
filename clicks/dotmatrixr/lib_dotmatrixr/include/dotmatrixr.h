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
 * \brief This file contains API for Dot-Matrix R Click driver.
 *
 * \addtogroup dotmatrixr Dot-Matrix R Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DOTMATRIXR_H
#define DOTMATRIXR_H

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

#define DOTMATRIXR_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rs = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.bl = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DOTMATRIXR_RETVAL  uint8_t

#define DOTMATRIXR_OK           0x00
#define DOTMATRIXR_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup byte_0  Byte 0
 * \{
 */
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_0                    0x00
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_1p7                  0x01
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_3p3                  0x02
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_5                    0x03
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_6p7                  0x04
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_8p3                  0x05
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_11p7                 0x06
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_15                   0x07
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_18                   0x08
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_23                   0x09
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_30                   0x0A
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_37                   0x0B
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_47                   0x0C
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_60                   0x0D
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_80                   0x0E
#define  DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_100                  0x0F
#define  DOTMATRIXR_CTRL_BYTE_0_PIXEL_PEAK_CURRENT_4mA          0x20
#define  DOTMATRIXR_CTRL_BYTE_0_PIXEL_PEAK_CURRENT_6p4mA        0x10
#define  DOTMATRIXR_CTRL_BYTE_0_PIXEL_PEAK_CURRENT_9p3mA        0x00
#define  DOTMATRIXR_CTRL_BYTE_0_PIXEL_PEAK_CURRENT_12p8mA       0x30
#define  DOTMATRIXR_CTRL_BYTE_0_MODE_SLEEP                      0x00
#define  DOTMATRIXR_CTRL_BYTE_0_MODE_NORMAL                     0x40
/** \} */

/**
 * \defgroup byte_1  Byte 1
 * \{
 */
#define  DOTMATRIXR_CTRL_BYTE_1_OSC_PRESCALER_1                 0x80
#define  DOTMATRIXR_CTRL_BYTE_1_OSC_PRESCALER_8                 0x82
#define  DOTMATRIXR_CTRL_BYTE_1_DOUT_D7                         0x80
#define  DOTMATRIXR_CTRL_BYTE_1_DOUT_DIN                        0x81
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
    digital_out_t rs;
    digital_out_t rst;
    digital_out_t bl;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} dotmatrixr_t;

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

    pin_name_t rs;
    pin_name_t rst;
    pin_name_t bl;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} dotmatrixr_cfg_t;

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
void dotmatrixr_cfg_setup ( dotmatrixr_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
DOTMATRIXR_RETVAL dotmatrixr_init ( dotmatrixr_t *ctx, dotmatrixr_cfg_t *cfg );

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
void dotmatrixr_generic_transfer ( dotmatrixr_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len );

/**
 * @brief Sets BL pin to high or low state
 *
 * @param ctx          Click object.
 * @param state        Pin state
 */
void dotmatrixr_set_bl_pin_state ( dotmatrixr_t *ctx, uint8_t state );

/**
 * @brief Sets RS pin to high or low state
 *
 * @param ctx          Click object.
 * @param state        Pin state
 */
void dotmatrixr_set_rs_pin_state ( dotmatrixr_t *ctx, uint8_t state );

/**
 * @brief Sets RST pin to high or low state
 *
 * @param ctx          Click object.
 * @param state        Pin state
 */
void dotmatrixr_set_rst_pin_state ( dotmatrixr_t *ctx, uint8_t state );

/**
 * @brief Restart device 
 * 
 * @param ctx          Click object.
 */
void dotmatrixr_restart ( dotmatrixr_t *ctx );

/**
 * @brief Function for writing control word 0
 *
 * @param ctx          Click object.
 * @param ctrl_byte    Control byte
 */
void dotmatrixr_ctrl_0 ( dotmatrixr_t *ctx, uint8_t ctrl_byte );

/**
 * @brief Function for writing control word 1
 *
 * @param ctx          Click object.
 * @param ctrl_byte    Control byte
 */
void dotmatrixr_ctrl_1 ( dotmatrixr_t *ctx, uint8_t ctrl_byte );

/**
 * @brief Sets display to written value
 *
 * @param ctx          Click object.
 * @param ascii_data   String to be displayed
 */
void dotmatrixr_write_ascii ( dotmatrixr_t *ctx, char *ascii_data );

#ifdef __cplusplus
}
#endif
#endif  // _DOTMATRIXR_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
