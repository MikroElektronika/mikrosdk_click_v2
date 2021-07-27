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
 * \brief This file contains API for Current Click driver.
 *
 * \addtogroup current Current Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef CURRENT_H
#define CURRENT_H

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

#define CURRENT_MAP_MIKROBUS( cfg, mikrobus )       \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define CURRENT_RETVAL  uint8_t

#define CURRENT_OK           0x00
#define CURRENT_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup usefull_stuff Usefull stuff
 * \{
 */
#define CURRENT_FILTER_USEFULL_DATA  0x0FFF
#define CURRENT_SAMPLE_NUM           10
/** \} */

/**
 * \defgroup r_shunt Shunt Values
 * \{
 */
#define CURRENT_RSHUNT_0_05          0.05
#define CURRENT_RSHUNT_0_2           0.2
#define CURRENT_RSHUNT_1             1.0
#define CURRENT_RSHUNT_10            10.0
#define CURRENT_CAL_COEF             0.025
/** \} */

/**
 * \defgroup limits Limiting Values
 * \{
 */
#define RFMETER_DEF_LIMIT_HIGH       4096
#define RFMETER_DEF_LIMIT_LOW        800
#define CURRENT_OUT_OF_RANGE         -1.0
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

} current_t;

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
    spi_master_mode_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} current_cfg_t;

/** \} */ // End types group
// ------------------------------------------------------------------ CONSTANTS
/**
 * \defgroup constants Constants
 * \{
 */
 
 

/** \} */ // End constants group
// ------------------------------------------------------------------ VARIABLES
/**
 * \defgroup variable Variable
 * \{
 */


/** \} */ // End variable group
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
void current_cfg_setup ( current_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param current Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
CURRENT_RETVAL current_init ( current_t *ctx, current_cfg_t *cfg );

/**
 * @brief Data read function
 *
 * @param ctx    Click object.
 * 
 * @returns result 16-bit value that represents readings from output register.
 *
 * Function is used to read data from output register.
**/
uint16_t current_data_read ( current_t *ctx );

/**
 * @brief Get raw data function
 *
 * @param ctx    Click object.
 * 
 * @returns result 12-bit value that represents raw data value.
 *
 * Function is used to read raw data value from output register.
**/
uint16_t current_get_raw_data ( current_t *ctx );

/**
 * @brief Calculate average data function
 * 
 * @param ctx    Click object.
 *
 * @returns result 12-bit value that represents average raw data value.
 *
 * Function is used to calculate average raw data value.
 * @note Function calculates average value from 10 raw values and holds small 100 miliseconds delay.
**/
float current_avg_rata ( current_t *ctx );

/**
 * @brief Get current value function
 *
 * @param ctx    Click object.
 * 
 * @param[in] rShunt  float value representing shunt resistor.
 *
 * @returns result 12-bit value representing current in mA.
 *
 * Function is used to calculate current in mA.
 * @note In order to measure current values in various bands, you need to provide the shunt of the appropriate value.
**/
float current_get_current_data ( current_t *ctx, float r_hunt );

#ifdef __cplusplus
}
#endif
#endif  // _CURRENT_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
