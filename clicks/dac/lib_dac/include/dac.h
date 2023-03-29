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
 * \brief This file contains API for DAC Click driver.
 *
 * \addtogroup dac DAC Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef DAC_H
#define DAC_H

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

#define DAC_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define DAC_RETVAL  uint8_t

#define DAC_OK           0x00
#define DAC_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup calc_val Calculation values
 * \{
 */
#define DAC_APPLY_SETTINGS  0x30

#define DAC_4_BIT_DATA      0x0F
#define DAC_8_BIT_DATA      0xFF
#define DAC_PERCENTAGE      100
#define DAC_ONE_STEP_VAL    819
#define DAC_CLAC_VAL        20
#define DAC_CALIB_VAL_1     220
#define DAC_CALIB_VAL_2     273
#define DAC_RESOLUTION      4096
#define DAC_STEP_VALUE      1000
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

} dac_t;

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

} dac_cfg_t;

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
 * @description This function initializes click configuration structure 
 * to init state.
 * @note All used pins will be set to unconnected state.
 */
void dac_cfg_setup ( dac_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param dac Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals 
 * used for this click.
 */
DAC_RETVAL dac_init ( dac_t *ctx, dac_cfg_t *cfg );

/**
 * @brief Set voltage function 
 *
 * @param ctx  Click object.
 * @param v_out 12-bit data value
 *
 * @description This function is used to set output voltage.
 */
void dac_set_voltage ( dac_t *ctx, uint16_t v_out );

/**
 * @brief Function write procentage value 
 *
 * @param ctx          Click object.
 * @param v_out_pct        Data procentage value.
 *
 * @description This function is used to set output voltage in percents.
 */

void dac_set_voltage_pct ( dac_t *ctx, uint8_t v_out_pct );

#ifdef __cplusplus
}
#endif
#endif  // _DAC_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
