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
 * \brief This file contains API for Alpha Num RG Click driver.
 *
 * \addtogroup alphanumrg Alpha Num RG Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ALPHANUMRG_H
#define ALPHANUMRG_H

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

#define ALPHANUMRG_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.le2   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.ns1   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.ns    = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ALPHANUMRG_RETVAL  uint8_t

#define ALPHANUMRG_OK           0x00
#define ALPHANUMRG_INIT_ERROR   0xFF
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

    digital_out_t le2;
    digital_out_t ns1;
    digital_out_t ns;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    // Variables
    uint16_t display_speed;

} alphanumrg_t;

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

    pin_name_t le2;
    pin_name_t ns1;
    pin_name_t ns;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} alphanumrg_cfg_t;

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
void alphanumrg_cfg_setup ( alphanumrg_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param alphanumrg Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ALPHANUMRG_RETVAL alphanumrg_init ( alphanumrg_t *ctx, alphanumrg_cfg_t *cfg );

/**
 * @brief Delay character display function.
 * 
 * @param ctx                   Click object.
 * @param delay_char_display    Delay time interval in ms.
 * 
 * @description This function sets the time interval at which the symbols are displayed.
 */
void alphanumrg_set_display_interval ( alphanumrg_t *ctx, uint16_t delay_char_display );

/**
 * @brief Display write function.
 * 
 * @param ctx          Click object.
 * @param left_char    Left segment symbol.
 * @param right_char   Right segment symbol.
 * 
 * @description This function displays symbols on the left and right LED segments.
 */
void alphanumrg_display_write ( alphanumrg_t *ctx, uint16_t left_char, uint16_t right_char );

/**
 * @brief Character write function.
 * 
 * @param ctx          Click object.
 * @param left_char    Left segment symbol.
 * @param right_char   Right segment symbol.
 * 
 * @description This function displays characters on the left and right LED segments.
 */
void aplhanumrg_write_character ( alphanumrg_t *ctx, uint8_t left_char, uint8_t right_char );

/**
 * @brief Number write function.
 * 
 * @param ctx          Click object.
 * @param left_char    Left segment symbol.
 * @param right_char   Right segment symbol.
 * 
 * @description This function displays numbers on the left and right LED segments.
 */
void alphanumrg_write_number ( alphanumrg_t *ctx, uint8_t left_char, uint8_t right_char );

/**
 * @brief Reset set high function.
 * 
 * @param ctx                   Click object.
 * 
 * @description This function sets the output voltage on the reset pin to high.
 */
void alphanumrg_set_rst_high ( alphanumrg_t *ctx );

/**
 * @brief Reset set low function.
 * 
 * @param ctx                   Click object.
 * 
 * @description This function sets the output voltage on the reset pin to low.
 */
void alphanumrg_set_rst_low ( alphanumrg_t *ctx );

/**
 * @brief PWM set high function.
 * 
 * @param ctx                   Click object.
 * 
 * @description This function sets the output voltage on the PWM pin to high.
 */
void alphanumrg_set_pwm_high ( alphanumrg_t *ctx );

/**
 * @brief PWM set low function.
 * 
 * @param ctx                   Click object.
 * 
 * @description This function sets the output voltage on the PWM pin to highlow.
 */
void alphanumrg_set_pwm_low ( alphanumrg_t *ctx );

/**
 * @brief Interrupt set high function.
 * 
 * @param ctx                   Click object.
 * 
 * @description This function sets the output voltage on the interrupt pin to high.
 */
void alphanumrg_set_int_high ( alphanumrg_t *ctx );

/**
 * @brief Interrupt set low function.
 * 
 * @param ctx                   Click object.
 * 
 * @description This function sets the output voltage on the interrupt pin to high.
 */
void alphanumrg_set_int_low ( alphanumrg_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _ALPHANUMRG_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
