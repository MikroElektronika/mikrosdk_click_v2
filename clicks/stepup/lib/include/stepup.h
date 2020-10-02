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
 * \brief This file contains API for Step Up Click driver.
 *
 * \addtogroup stepup Step Up Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef STEPUP_H
#define STEPUP_H

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

#define STEPUP_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.mod = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define STEPUP_RETVAL  uint8_t

#define STEPUP_OK           0x00
#define STEPUP_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup stepup_var Variables
 * \{
 */
#define STEPUP_DACB          0x8000
#define STEPUP_DACA          0x0000
#define STEPUP_BUFFERED      0x4000
#define STEPUP_UNBUFFERED    0x0000
#define STEPUP_GAIN_1X       0x2000
#define STEPUP_GAIN_2X       0x0000
#define STEPUP_POWER_UP      0x1000
#define STEPUP_POWER_DOWN    0x0000
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

    digital_out_t mod;
    digital_out_t en;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    uint16_t config_word;

} stepup_t;

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

    pin_name_t mod;
    pin_name_t en;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    uint16_t config_word_cfg;

} stepup_cfg_t;

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
void stepup_cfg_setup ( stepup_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param stepup Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
STEPUP_RETVAL stepup_init ( stepup_t *ctx, stepup_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx           Click object.
 * @param out_value     Output value (range : 0 to 4095)
 *
 * @description This function executes default configuration for Step Up click.
 */
void stepup_default_cfg ( stepup_t *ctx, uint16_t out_value );

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
void stepup_generic_transfer 
( 
    stepup_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Mod Pin set function.
 *
 * @param ctx          Click object.
 * @param pin_state    MOD pin state (0 for LOW and 1 for HIGH)
 * 
 * @description This function sets the MOD pin state
 */
void stepup_mod_set ( stepup_t *ctx, uint8_t pin_state );

/**
 * @brief En Pin set function.
 *
 * @param ctx          Click object.
 * @param pin_state    EN pin state (0 for LOW and 1 for HIGH)
 * 
 * @description This function sets the EN pin state
 */
void stepup_en_set ( stepup_t *ctx, uint8_t pin_state );

/**
 * @brief En Pin set function.
 *
 * @param ctx          Click object.
 * @param config       Command word configuration bits
 * 
 * @returns 0 for correct input value
 * @returns 1 for incorrect input value
 * 
 * @description This function sets first 4 bits in command word
 */
uint8_t stepup_set_config ( stepup_t *ctx, uint16_t config );

/**
 * @brief Setting output value.
 *
 * @param ctx          Click object.
 * @param out_value    Output value (range : 0 to 4095)
 * 
 * @returns 0 for correct input value
 * @returns 1 for incorrect input value
 * 
 * @description This function sets output value
 * 
 * @note Value of 0 means that output is at 100%, value of 4095 means that output is at 0%
 */
uint8_t stepup_set_out ( stepup_t *ctx, uint16_t out_value );

/**
 * @brief Calculate ouput value in percent.
 *
 * @param ctx          Click object.
 * @param out_value    Output value (range : 0 to 4095)
 * 
 * @returns output value in percent (range : 0% to 100%)
 * 
 * @description This function calculates ouput value in percent
 */
float stepup_get_percent ( uint16_t out_value );

#ifdef __cplusplus
}
#endif
#endif  // _STEPUP_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
