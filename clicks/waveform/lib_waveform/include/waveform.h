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
#define WAVEFORM_OK                         0
#define WAVEFORM_ERROR                     -1
/** \} */

/**
 * \defgroup bitmask  Bitmask
 * \{
 */
#define WAVEFORM_CR_B28_BITMASK             0x2000
#define WAVEFORM_CR_HLB_BITMASK             0x1000
#define WAVEFORM_CR_FSELECT_BITMASK         0x0800
#define WAVEFORM_CR_PSELECT_BITMASK         0x0400
#define WAVEFORM_CR_RESET_BITMASK           0x0100 
#define WAVEFORM_CR_SLEEP1_BITMASK          0x0080 
#define WAVEFORM_CR_SLEEP12_BITMASK         0x0040 
#define WAVEFORM_CR_OPBITEN_BITMASK         0x0020 
#define WAVEFORM_CR_DIV2_BITMASK            0x0008 
#define WAVEFORM_CR_MODE_BITMASK            0x0002 
/** \} */

/**
 * \defgroup output  Output
 * \{
 */
#define WAVEFORM_SINE_OUT                   0x01
#define WAVEFORM_TRIANGLE_OUT               0x02
#define WAVEFORM_SQUARE_OUT                 0x03
/** \} */

/**
 * \defgroup freq_settings  Frequency settings
 * \{
 */
#define WAVEFORM_OSC_FREQUENCY              25000000ul
#define WAVEFORM_FREQ_RESOLUTION            0x0FFFFFFFul
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
    
    // Modules 
    spi_master_t spi;
    pin_name_t chip_select;
    
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
    spi_master_mode_t spi_mode;
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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void waveform_cfg_setup ( waveform_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param waveform Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t waveform_init ( waveform_t *ctx, waveform_cfg_t *cfg );

/**
 * @brief Decrement function
 *
 * @param ctx           Click object.
 *
 * @details This function decreases amplitude.
 */             
void waveform_digipot_dec ( waveform_t *ctx );

/**
 * @brief Increment function
 *
 * @param ctx           Click object.
 * 
 * @details This function increases amplitude.
 */             
void waveform_digipot_inc ( waveform_t *ctx );

/**
 * @brief Registry function
 *
 * @param ctx              Click object.
 * @param reg_setting      Generic SPI function for writing 16bit values to the waveform generating chip. 
 */             
void waveform_write_reg ( waveform_t *ctx, uint16_t reg_setting );

/**
 * @brief Frequency function
 *
 * @param ctx    Click object.
 * @param freq   Set the frequency by passing the raw 24bit value.  
 *
 * @details This function sets frequency.
 */             
void waveform_write_frequency ( waveform_t *ctx, uint32_t freq );

/**
 * @brief Sinusoide output function
 *
 * @param ctx   Click object.
 * @param freq  Set the frequency by passing the raw 24bit value. 
 *
 * @details This function outputs sinusoide signal.
 */             
void waveform_sine_output ( waveform_t *ctx, uint32_t freq );

/**
 * @brief Triangle output function
 *
 * @param ctx   Click object.
 * @param freq  Set the frequency by passing the raw 24bit value. 
 *
 * @details This function outputs triangle signal.
 */             
void waveform_triangle_output ( waveform_t *ctx, uint32_t freq );

/**
 * @brief Square output function
 *
 * @param ctx   Click object.
 * @param freq  Set the frequency by passing the raw 24bit value. 
 *
 * @details This function outputs square signal.
 */             
void waveform_square_output ( waveform_t *ctx, uint32_t freq );

#ifdef __cplusplus
}
#endif
#endif  // _WAVEFORM_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
