/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file matrixg.h
 * @brief This file contains API for Matrix G Click Driver.
 */

/*!
 * @addtogroup matrixg Matrix G Click Driver
 * @brief API for configuring and manipulating Matrix G Click driver.
 * @{
 */

// ----------------------------------------------------------------------------

#ifndef MATRIXG_H
#define MATRIXG_H

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

#define MATRIXG_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.csn   = MIKROBUS( mikrobus, MIKROBUS_AN ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MATRIXG_RETVAL  uint8_t

#define MATRIXG_OK           0x00
#define MATRIXG_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_address_map Register Address Map
 * \{
 */
#define MATRIXG_DECODE_MODE_REG    0x09
#define MATRIXG_INTENSITY_REG      0x0A
#define MATRIXG_SCAN_LIMIT_REG     0x0B
#define MATRIXG_SHUTDOWN_REG       0x0C
#define MATRIXG_DISPLAY_TEST_REG   0x0F
/** \} */

/**
 * \defgroup decode_mode_register Decode Mode Register
 * \{
 */
#define MATRIXG_NO_DECODE          0x00
#define MATRIXG_DECODE_DIGIT_0     0x01
#define MATRIXG_DECODE_DIGIT_3_0   0x0F
#define MATRIXG_DECODE_DIGIT_7     0xFF
/** \} */

/**
 * \defgroup intensity_register_format Intensity Register Format
 * \{
 */
#define MATRIXG_INTEN_LVL_0   0x00
#define MATRIXG_INTEN_LVL_1   0x03
#define MATRIXG_INTEN_LVL_2   0x06
#define MATRIXG_INTEN_LVL_3   0x09
#define MATRIXG_INTEN_LVL_4   0x0C
#define MATRIXG_INTEN_LVL_5   0x0F
/** \} */

/**
 * \defgroup scan_limit_register_format Scan Limit Register Format
 * \{
 */
#define MATRIXG_DISPLAY_DIGIT_0     0x00
#define MATRIXG_DISPLAY_DIGIT_0_1   0x01
#define MATRIXG_DISPLAY_DIGIT_0_2   0x02
#define MATRIXG_DISPLAY_DIGIT_0_3   0x03
#define MATRIXG_DISPLAY_DIGIT_0_4   0x04
#define MATRIXG_DISPLAY_DIGIT_0_5   0x05
#define MATRIXG_DISPLAY_DIGIT_0_6   0x06
#define MATRIXG_DISPLAY_DIGIT_0_7   0x07
/** \} */

/**
 * \defgroup shutdown_register_format Shutdown Register Format
 * \{
 */
#define MATRIXG_SHUTDOWN_MODE      0x00
#define MATRIXG_NORMAL_OPERATION   0x01

/**
 * \defgroup display_test_register_format Display Test Register Format
 * \{
 */
#define MATRIXG_DISPLAY_NORMAL_OPERATION   0x00
#define MATRIXG_DISPLAY_TEST_MODE          0X01
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

    digital_out_t csn;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} matrixg_t;

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

    pin_name_t csn;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;


} matrixg_cfg_t;

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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void matrixg_cfg_setup ( matrixg_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param matrixg Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
MATRIXG_RETVAL matrixg_init ( matrixg_t *ctx, matrixg_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Matrix RG Click.
 */
void matrixg_default_cfg ( matrixg_t *ctx );

/**
 * @brief Display characters function.
 *
 * @param ctx          Click object.
 * @param left_char    ASCII value for the character printed on the left segment.
 * @param right_char   ASCII value for the character printed on the right segment.
 *
 * @description This function displays the specified characters on the L/R segments of the Click.
 */
void matrixg_display_characters ( matrixg_t *ctx, uint8_t left_char, uint8_t right_char );

/**
 * @brief Register write function.
 *
 * @param ctx          Click object.
 * @param address      Address to which the data is written.
 * @param input_data   Input data variable.
 *
 * @description This function writes one byte of data to the specified address.
 */
void matrixg_write_reg ( matrixg_t *ctx, uint8_t address, uint8_t input_data );

/**
 * @brief Set CSN pin to high function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the CSN pin output to high.
 */
void matrixg_set_csn_high ( matrixg_t *ctx );

/**
 * @brief Set CSN pin to low function.
 *
 * @param ctx  Click object.
 *
 * @description This function sets the CSN pin output to low.
 */
void matrixg_set_csn_low ( matrixg_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _MATRIXG_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
