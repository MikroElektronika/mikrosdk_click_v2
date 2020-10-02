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
 * \brief This file contains API for Waveform  Click driver.
 *
 * \addtogroup waveform Waveform  Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef WAVEFORM_H
#define WAVEFORM_H

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

#define WAVEFORM_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.pwm   = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define WAVEFORM_RETVAL  uint8_t

#define WAVEFORM_OK                           0x00
#define WAVEFORM_INIT_ERROR                   0xFF
/** \} */

/**
 * \defgroup bitmask  Bitmask
 * \{
 */
#define WAVEFORM_CR_B28_BITMASK              1<<13
#define WAVEFORM_CR_HLB_BITMASK              1<<12
#define WAVEFORM_CR_FSELECT_BITMASK          1<<11
#define WAVEFORM_CR_PSELECT_BITMASK          1<<10
#define WAVEFORM_CR_RESET_BITMASK             1<<8 
#define WAVEFORM_CR_SLEEP1_BITMASK            1<<7 
#define WAVEFORM_CR_SLEEP12_BITMASK           1<<6 
#define WAVEFORM_CR_OPBITEN_BITMASK           1<<5 
#define WAVEFORM_CR_DIV2_BITMASK              1<<3 
#define WAVEFORM_CR_MODE_BITMASK              1<<1 
/** \} */

/**
 * \defgroup output  Output
 * \{
 */
#define WAVEFORM_SINE_OUT                     0x01
#define WAVEFORM_TRIANGLE_OUT                 0x02
#define WAVEFORM_SQUARE_OUT                   0x03
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
    digital_out_t pwm;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;
    
    uint8_t  dumy_rec_buf[ 5 ];
    uint16_t wavwform_control_reg;

} waveform_t;

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

    pin_name_t rst;
    pin_name_t pwm;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} waveform_cfg_t;

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
void waveform_cfg_setup ( waveform_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param waveform Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
WAVEFORM_RETVAL waveform_init ( waveform_t *ctx, waveform_cfg_t *cfg );

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
void waveform_generic_transfer 
( 
    waveform_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Decrement function
 *
 * @param ctx           Click object.
 *
 * @description This function  
 */             
void waveform_digipot_dec ( waveform_t *ctx );

/**
 * @brief Increment function
 *
 * @param ctx           Click object.
 */             
void waveform_digipot_inc ( waveform_t *ctx );

/**
 * @brief Registry finction
 *
 * @param ctx              Click object.
 * @param reg_setting      Generic SPI function for writing 16bit values to the waveform generating chip. 
 */             
void waveform_write_reg ( waveform_t *ctx, uint16_t reg_setting );

/**
 * @brief Freqency function
 *
 * @param ctx    Click object.
 * @param f      Output a sine wave and set the frequency by passing the raw 24bit value.  
 *
 * @description This function returns freqency.
 */             
void waveform_write_freqency ( waveform_t *ctx, uint32_t f );

/**
 * @brief Sinusoide output function
 *
 * @param ctx   Click object.
 * @param f     Output a sine wave and set the frequency by passing the raw 24bit value. 
 *
 * @description  This functin outputs sinusodie signal.
 */             
void waveform_sine_output ( waveform_t *ctx, uint32_t f );

/**
 * @brief Triangle output function
 *
 * @param ctx   Click object.
 * @param f     Output a sine wave and set the frequency by passing the raw 24bit value. 
 *
 * @description  This functin outputs triangle signal.
 */             
void waveform_triangle_output ( waveform_t *ctx, uint32_t f );

/**
 * @brief Square output function
 *
 * @param ctx   Click object.
 * @param f     Output a sine wave and set the frequency by passing the raw 24bit value. 
 *
 * @description  This functin outputs square signal.
 */             
void waveform_square_output ( waveform_t *ctx, uint32_t f );

#ifdef __cplusplus
}
#endif
#endif  // _WAVEFORM_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
