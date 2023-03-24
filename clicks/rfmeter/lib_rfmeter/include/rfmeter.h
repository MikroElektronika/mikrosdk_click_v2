/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright (c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 * \brief This file contains API for RF Meter Click driver.
 *
 * \addtogroup rfmeter RF Meter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RFMETER_H
#define RFMETER_H

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

#define RFMETER_MAP_MIKROBUS( cfg, mikrobus )       \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RFMETER_RETVAL  uint8_t

#define RFMETER_OK           0x00
#define RFMETER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup calc_const Calculation constants
 * \{
 */
#define RFMETER_FILTER_USEFULL_DATA  0x1FFE
#define RFMETER_ADC_RESOLUTION       4096
#define RFMETER_DATA_SAMPLE_NUM      10
#define RFMETER_DEF_VREF             2.5
#define RFMETER_DEF_SLOPE            -0.025
#define RFMETER_DEF_INTERCEPT        20.0
#define RFMETER_DEF_LIMIT_HIGH       2.0
#define RFMETER_DEF_LIMIT_LOW        0.5
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

} rfmeter_t;

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

} rfmeter_cfg_t;

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
void rfmeter_cfg_setup ( rfmeter_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param rfmeter Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RFMETER_RETVAL rfmeter_init ( rfmeter_t *ctx, rfmeter_cfg_t *cfg );

/**
 * @brief Data read function
 *
 * @param ctx  Click object.
 * 
 * @returns result 16-bit value that represents readings from output register.
 *
 * Function is used to read data from output register.
**/
uint16_t rfmeter_read_data ( rfmeter_t *ctx );

/**
 * @brief Get raw data function
 *
 * @param ctx  Click object.
 * 
 * @returns result 12-bit value that represents raw data value.
 *
 * Function is used to read raw data value from output register.
**/
uint16_t rfmeter_get_raw_data ( rfmeter_t *ctx );

/**
 * @brief Get voltage function
 *
 * @param ctx  Click object.
 * 
 * @returns result 12-bit value that represents raw voltage value.
 *
 * Function is used to read raw voltage value from output register.
**/
float rfmeter_get_voltage ( rfmeter_t *ctx );

/**
 * @brief Get signal strenght function
 *
 * @param ctx  Click object.
 * @param slope float value that represents slope
 * @param intercept float value that represents intercept
 *
 * @returns result float value that represents signal strenght
 *
 * Function is used to calculate radio frequency signal strenght in a vicinity.
**/
float rfmeter_get_signal_strenght ( rfmeter_t *ctx, float slope, float intercept );

#ifdef __cplusplus
}
#endif
#endif  // _RFMETER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
