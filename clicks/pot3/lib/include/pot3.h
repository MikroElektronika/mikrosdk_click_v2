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
 * \brief This file contains API for Pot 3 Click driver.
 *
 * \addtogroup pot3 Pot 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef POT3_H
#define POT3_H

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

#define POT3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.vo = MIKROBUS( mikrobus, MIKROBUS_AN )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define POT3_RETVAL  uint8_t

#define POT3_OK           0x00
#define POT3_INIT_ERROR   0xFF
/** \} */

/**
  * \defgroup VREF_value VREF Value
  * \{
  */
#define POT3_VREF_2V       0
#define POT3_VREF_3V3      1
  /** \} */ // End group VREF_value 


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

    digital_in_t vo;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} pot3_t;

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

    pin_name_t vo;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} pot3_cfg_t;

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
void pot3_cfg_setup ( pot3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 *
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
POT3_RETVAL pot3_init ( pot3_t* ctx, pot3_cfg_t* cfg );

/**
 * @brief ADC Read function
 *.
 * @param pot3 Click object.
 *
 * @returns 12-bit ADC value.
 * 
 * @description This function reads the result of AD conversion.
 */
uint16_t pot3_read_adc ( pot3_t* ctx );

/**
 * @brief ADC Averaged Read function.
 *
 * @param ctx          Click object.
 * @param n_samples    Number of conversions to be read.
 *
 * @returns            12-bit averaged ADC value.
 *
 * @description This function reads the averaged result of AD conversions.
 */
uint16_t pot3_read_avg_adc ( pot3_t* ctx, uint16_t n_samples );

/**
 * @brief ADC Averaged Read function.
 *
 * @param ctx          Click object.
 * @param vref_sel     VREF selection: 0 - 2V, 1 - 3V3
 * @param n_samples    Number of conversions to be read.
 *
 * @returns            VOUT value calculated to millivolts.
 *
 * @description This function returns VOUT value calculated to millivolts,
 * with desired number of AD conversions included in calculations.
 */
uint16_t pot3_get_vout ( pot3_t* ctx, uint8_t vref_sel, uint16_t n_samples );

#ifdef __cplusplus
}
#endif
#endif  // _POT3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
