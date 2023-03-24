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
 * \brief This file contains API for ADC 2 Click driver.
 *
 * \addtogroup adc2 ADC 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ADC2_H
#define ADC2_H

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

#define ADC2_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ADC2_RETVAL  uint8_t

#define ADC2_OK                 0x00
#define ADC2_INIT_ERROR         0xFF
/** \} */


#define ADC2_VCC_3v3            3300.0
#define ADC2_VCC_5V             5000.0
#define ADC2_VCC_4v096          4096.0

/**
 * \defgroup flags Flags
 * \{
 */
#define ADC2_INTERRUPT_FLAG                                    -4000000
#define ADC2_OVERFLOW_HIGH_FLAG                                 3000000
#define ADC2_OVERFLOW_LOW_FLAG                                 -3000000
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

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;
    
    float vref;
    uint8_t ovf_h;
    uint8_t ovf_l;

} adc2_t;

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

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} adc2_cfg_t;

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
void adc2_cfg_setup ( adc2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ADC2_RETVAL adc2_init ( adc2_t *ctx, adc2_cfg_t *cfg );

/**
 * @brief Read adc data function
 * 
 * @param ctx          Click object.
 * 
 * @returns Reading 3 bytes from Click board and returning it in one variable
 *
 * @description Function is used to read 3 bytes from ADC convertor.
 */
float adc2_read_adc_data ( adc2_t *ctx );

/**
 * @brief Setting reference voltage.
 * 
 * @param ctx          Click object.
 * @param vref         Reference mV.
 * 
 * @description Function is used to set reference voltage.
 */
void adc2_set_vref ( adc2_t *ctx, float vref );

#ifdef __cplusplus
}
#endif
#endif  // _ADC2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
