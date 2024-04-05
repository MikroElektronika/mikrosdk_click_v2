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
 * \brief This file contains API for Slider Click driver.
 *
 * \addtogroup slider Slider Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SLIDER_H
#define SLIDER_H

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

#define SLIDER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.oe    = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.csl   = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SLIDER_RETVAL  uint8_t

#define SLIDER_OK           0x00
#define SLIDER_INIT_ERROR   0xFF
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
    digital_out_t csl;
    digital_in_t miso;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} slider_t;

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
    pin_name_t csl;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} slider_cfg_t;

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
void slider_cfg_setup ( slider_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param slider Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
SLIDER_RETVAL slider_init ( slider_t *ctx, slider_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Slider click.
 */
void slider_default_cfg ( slider_t *ctx );

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
void slider_generic_transfer 
( 
    slider_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief ADC read function
 *
 * @param ctx          Click object.
 * @returns            22-bit ADC conversion value
 *
 * @description Function reads via SPI bus ADC value and converts it to 22-bit value.
 */
uint32_t slider_read_adc ( slider_t *ctx );

/**
 * @brief ADC and READY read function
 *
 * @param ctx          Click object.
 * @return             22-bit ADC conversion value.
 *
 * @description Function calls slider_readADC function, but first checks is ADC conversion finished,
 * and waits until conversion is complete.
 */
uint32_t slider_read_adc_and_ready ( slider_t *ctx );

/**
 * @brief Output enable function
 *
 * @param ctx          Click object.
 * @param state        0 - logic low, 1 - logic high.
 *
 * @description Function enables LED output to shows output laches when state is low, and disables LED output
 * when state is high, by seting AN pin on state value.
 */
void slider_enable_led_output ( slider_t *ctx, uint8_t state );

/**
 * @brief Output laches enable function
 *
 * @param ctx          Click object.
 * @param state        0 - logic low, 1 - logic high.
 *
 * @description Function enables output laches to monitor converted ADC value, when state is high,
 * and disables monitoring when state is low, by seting RST pin on state value.
 */
void slider_enable_output_laches ( slider_t *ctx, uint8_t state );

/**
 * @brief Output write function
 *
 * @param ctx          Click object.
 * @return             22-bit ADC converted value.
 *
 * @description Function calls slider_readADCAndReady function, checks is conversion finished, reads converted value,
 * writes this value on LED output laches and returns 22-bit value as result of conversion.
 */
uint32_t slider_write_output ( slider_t *ctx);


#ifdef __cplusplus
}
#endif
#endif  // _SLIDER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
