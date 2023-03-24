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
 * \brief This file contains API for Tester Click driver.
 *
 * \addtogroup tester Tester Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TESTER_H
#define TESTER_H

#include "drv_digital_out.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define TESTER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an      = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); \
  cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
  cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
  cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX )
  
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TESTER_RETVAL  uint8_t

#define TESTER_OK           0x00
#define TESTER_INIT_ERROR   0xFF
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
    // Communication pins 

    digital_out_t scl;
    digital_out_t sda;
    digital_out_t sck;
    digital_out_t miso;
    digital_out_t mosi;
    digital_out_t cs;
    digital_out_t tx_pin;
    digital_out_t rx_pin;

    // Gpio pins

    digital_out_t an;
    digital_out_t rst;
    digital_out_t pwm;
    digital_out_t int_pin;

} tester_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t sck;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t cs;
    pin_name_t tx_pin;
    pin_name_t rx_pin;
    
    // Gpio pins

    pin_name_t an;
    pin_name_t rst;
    pin_name_t pwm;
    pin_name_t int_pin;

} tester_cfg_t;

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
void tester_cfg_setup ( tester_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param tester Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
TESTER_RETVAL tester_init ( tester_t *ctx, tester_cfg_t *cfg );

/**
 * @brief Set pin high function.
 *
 * @param pin  Output pin adress variable.
 *
 * @description This function sets the output voltage on the specified pin to high.
 * 
 * @note The pin address should be acquired in the following way: { &click.pin }
 */
void tester_set_pin_high ( digital_out_t *pin );

/**
 * @brief Set pin low function.
 *
 * @param pin  Output pin adress variable.
 *
 * @description This function sets the output voltage on the specified pin to low.
 * 
 * @note The pin address should be acquired in the following way: { &click.pin }
 */
void tester_set_pin_low ( digital_out_t *pin );

#ifdef __cplusplus
}
#endif
#endif  // _TESTER_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
