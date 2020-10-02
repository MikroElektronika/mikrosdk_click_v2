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
 * \brief This file contains API for Ammeter Click driver.
 *
 * \addtogroup ammeter Ammeter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AMMETER_H
#define AMMETER_H

#include "drv_digital_out.h"
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

#define AMMETER_MAP_MIKROBUS( cfg, mikrobus )       \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AMMETER_RETVAL  uint8_t

#define AMMETER_OK           0x00
#define AMMETER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup calc_const Calculation constants
 * \{
 */
#define AMMETER_SAMPLE_NUM           10
#define AMMETER_FILTER_USEFULL_DATA  0x1FFE
#define AMMETER_CALC_COEF            1024.0
#define AMMETER_STABULISATION_COEF   2.0
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

} ammeter_t;

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
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} ammeter_cfg_t;

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
void ammeter_cfg_setup ( ammeter_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AMMETER_RETVAL ammeter_init ( ammeter_t *ctx, ammeter_cfg_t *cfg );

/**
 * @brief Data read function
 *
 * @param ctx  Click object.
 * 
 * @returns result 16-bit value that represents readings from output register.
 *
 * Function is used to read data from output register.
**/
uint16_t ammeter_data_read ( ammeter_t *ctx );

/**
 * @brief Get raw data function
 *
 * @param ctx  Click object.
 * 
 * @returns result 12-bit value that represents raw data value.
 *
 * Function is used to read raw data value from output register.
**/
uint16_t ammeter_get_raw_data ( ammeter_t *ctx );

/**
 * @brief Get average average data function
 *
 * @param ctx  Click object.
 * 
 * @returns result 11-bit value that represents average data value.
 *
 * Function is used to calculate average data value.
 * @note Function calculates average value from 10 raw values and holds 
 * small 100 miliseconds delay.
**/
float ammeter_get_avg_data ( ammeter_t *ctx );

/**
 * @brief Get amperage function
 *
 * @param ctx  Click object.
 * 
 * @returns result 12-bit value that represents amperage.
 *
 * Function is used to measure amperage of a power consumer connected 
 * to the click board.
 * @note Ammeter click board can be used to saftly measure current up to 1A.
**/
float ammeter_amperage ( ammeter_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AMMETER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
