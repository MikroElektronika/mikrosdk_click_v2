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
 * \brief This file contains API for H BRIDGE 2 Click driver.
 *
 * \addtogroup hbridge2 H BRIDGE 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef HBRIDGE2_H
#define HBRIDGE2_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define HBRIDGE2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.gin= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.dir= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.end= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm= MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define HBRIDGE2_RETVAL  uint8_t

#define HBRIDGE2_OK               0x00
#define HBRIDGE2_INIT_ERROR       0xFF
/** \} */

/**
 * \defgroup register Register 
 * \{
 */
#define HBRIDGE2_OUT1_H_OUT2_H    0x00
#define HBRIDGE2_OUT1_H_OUT2_L    0x01
#define HBRIDGE2_OUT1_L_OUT2_H    0x02
#define HBRIDGE2_OUT1_Z_OUT2_Z    0x03

#define HBRIDGE2_DISABLE          0x00
#define HBRIDGE2_ENABLE           0x01

#define HBRIDGE2_GOUT_HIGH        0x00
#define HBRIDGE2_GOUT_LOW         0x01
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

    digital_out_t gin;
    digital_out_t dir;
    digital_out_t end;
    digital_out_t pwm;

    // Input pins 

} hbridge2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t gin;
    pin_name_t dir;
    pin_name_t end;
    pin_name_t pwm;

} hbridge2_cfg_t;

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
void hbridge2_cfg_setup ( hbridge2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param hbridge2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
HBRIDGE2_RETVAL hbridge2_init ( hbridge2_t *ctx, hbridge2_cfg_t *cfg );

/**
 * @brief Output Set function.
 *
 * @param ctx           Click object.
 * @param out_state     Determines the state of OUT1 and OUT2.
 *
 * @note 0b0000000x determines the state of OUT1, and 0b000000x0 determines the state of OUT2
 *
 * @return 0 - OK, 1 - Wrong parameter value
 *
 * @description Function puts outputs (OUT1 (M1) and OUT2 (M2) ) to desired state.
 */
uint8_t hbridge2_set_output ( hbridge2_t *ctx, uint8_t out_state );

 /**
 * @brief Enable function.
 *
 * @param ctx    Click object.
 * @param state  0 - Disable, 1 - Enable.
 *
 * @note When device is disabled all outputs (OUT1, OUT2, GOUT) is in logic low state.
 *
 * @description Function puts the device in enable or disable state.
 */
void hbridge2_enable ( hbridge2_t *ctx, uint8_t state );

 /**
 * @brief GOUT Set function.
 *
 * @param ctx    Click object.
 * @param state  0 - GOUT is high, 1 - GOUT is low
 *
 * @description Function controls the state of the GOUT pin (MOSFET GAIN).
 */
void hbridge2_set_gout ( hbridge2_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif  // _HBRIDGE2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
