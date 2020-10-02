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
 * \brief This file contains API for R Meter Click driver.
 *
 * \addtogroup rmeter R Meter Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RMETER_H
#define RMETER_H

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

#define RMETER_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
   cfg.s3 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.s1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.s2 = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RMETER_RETVAL  uint8_t

#define RMETER_OK           0x00
#define RMETER_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup rmeter_value R-Meter value
 * \{
 */
#define RMETER_SELECT                   1
#define RMETER_DESELECT                 0
#define RMETER_OVER_RANGE               -1
#define RMETER_FILTER_USEFULL_DATA      0x1FFE
#define RMETER_DATA_SAMPLE_NUM          10
#define RMETER_RANGE_BASE_VALUE_0       88000
#define RMETER_RANGE_BASE_VALUE_1       236
#define RMETER_RANGE_BASE_VALUE_2       1100
#define RMETER_RANGE_BASE_VALUE_3       95000
#define RMETER_RANGE_VALUE              2000
#define RMETER_RANGE_VALUE_MAX          300000
#define RMETER_GAIN_CALC_CONST          100
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

    digital_out_t s3;
    digital_out_t s1;
    digital_out_t s2;
    digital_out_t cs;

    // Input pins 

    digital_in_t an;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} rmeter_t;

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

    pin_name_t an;
    pin_name_t s3;
    pin_name_t s1;
    pin_name_t s2;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} rmeter_cfg_t;

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
void rmeter_cfg_setup ( rmeter_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param rmeter Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RMETER_RETVAL rmeter_init ( rmeter_t *ctx, rmeter_cfg_t *cfg );

/**
 * @brief S1 defined range function
 *
 * @param ctx  Click object.
 * @param state  Select or deselect value.
 *
 * Function is used to set or clear s1 pin in order to select or deselect
 * apropriate range of readings.
 * @note Setting this pin defines range 0 - 1kOhm.
**/
void rmeter_range_s1 ( rmeter_t *ctx, uint8_t state );

/**
 * @brief S2 defined range function
 *
 * @param ctx  Click object.
 * @param state  Select or deselect value.
 *
 * Function is used to set or clear s2 pin in order to select or deselect
 * apropriate range of readings.
 * @note Setting this pin defines range 1kOhm - 100kOhm.
**/
void rmeter_range_s2 ( rmeter_t *ctx, uint8_t state );

/**
 * @brief S3 defined range function
 *
 * @param ctx  Click object.
 * @param state  Select or deselect value.
 *
 * Function is used to set or clear s3 pin in order to select or deselect
 * apropriate range of readings.
 * @note Setting this pin defines range 100kOhm - 1MOhm.
**/
void rmeter_range_s3 ( rmeter_t *ctx, uint8_t state );

/**
 * @brief Data read function
 *
 * @param ctx  Click object.
 *
 * @returns 16-bit value that represents readings from output register.
 *
 * Function is used to read raw data from output register.
**/
uint16_t rmeter_read_data ( rmeter_t *ctx );

/**
 * @brief Get voltage function
 *
 * @param ctx  Click object.
 *
 * @returns result value that represents raw voltage value.
 *
 * Function is used to read voltage.
**/
uint16_t rmeter_get_volage ( rmeter_t *ctx );

/**
 * @brief Get average voltage function
 *
 * @param ctx  Click object.
 *
 * @returns result  value that represents average voltage value
 *
 * Function is used to calculate average voltage.
 * @note Function calculates average value from 10 sample values and holds
 * small 100 miliseconds delay.
**/
float rmeter_avg_volt ( rmeter_t *ctx );

/**
 * @brief Calculations function
 *
 * @param ctx  Click object.
 * @param resFilt  compensation needed to calculate resistance.
 *
 * @returns rsem float value that represents calculations.
 *
 * Function is used to calculate raw resistance value based on constant current
 * of 100mA and voltage that changes depending on resistance.
**/
float rmeter_calc ( rmeter_t *ctx, uint32_t resFilt );

/**
 * @brief Get resistance in OHMs function
 *
 * @param ctx  Click object.
 *
 * @returns result float value that represents resistance.
 *
 * Function is used to measure resistance of a resistor conected to
 * the click board.
**/
float rmeter_get_ohms ( rmeter_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _RMETER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
