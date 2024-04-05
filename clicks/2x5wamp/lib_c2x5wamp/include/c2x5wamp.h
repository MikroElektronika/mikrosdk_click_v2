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
 * \brief This file contains API for 2x5W AMP Click driver.
 *
 * \addtogroup c2x5wamp 2x5W AMP Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C2X5WAMP_H
#define C2X5WAMP_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define C2X5WAMP_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.gn0= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.gn1= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.stb= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.mute= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.dia= MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C2X5WAMP_RETVAL  uint8_t

#define C2X5WAMP_OK           0x00
#define C2X5WAMP_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup Mode ( standby, mute, play)
 * \{
 */
#define C2X5WAMP_MODE_STANDBY                                     0x00
#define C2X5WAMP_MODE_MUTE                                        0x01
#define C2X5WAMP_MODE_PLAY                                        0x02
/** \} */

/**
 * \defgroup Gain noise
 * \{
 */
#define C2X5WAMP_GAIN_20DB                                        0x00
#define C2X5WAMP_GAIN_26DB                                        0x01
#define C2X5WAMP_GAIN_30DB                                        0x02
#define C2X5WAMP_GAIN_32DB                                        0x03
/** \} */

/**
 * \defgroup Result value
 * \{
 */
#define C2X5WAMP_RESULT_ERROR                                     0x00
#define C2X5WAMP_RESULT_OK                                        0x01
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

    digital_out_t gn0;
    digital_out_t gn1;
    digital_out_t stb;
    digital_out_t mute;

    // Input pins 

    digital_in_t dia;

} c2x5wamp_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t gn0;
    pin_name_t gn1;
    pin_name_t stb;
    pin_name_t mute;
    pin_name_t dia;

} c2x5wamp_cfg_t;

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
void c2x5wamp_cfg_setup ( c2x5wamp_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx  Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C2X5WAMP_RETVAL c2x5wamp_init ( c2x5wamp_t *ctx, c2x5wamp_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 2x5W AMP click.
 * @note
 * <pre>Set Standby mode</pre>
 * <pre>Set amplifier gain to 20dB</pre>
 */
void c2x5wamp_default_cfg ( c2x5wamp_t *ctx );

/**
 * @brief Set mode selection of the amplifier function
 *
 * @param ctx  Click object.
 * @param select_mode
 * - 0 : Standby mode, all circuits are turned off, very low current consumption.
 * - 1 : Mute mode, inputs are connected to ground and the positive and
 * negative PWM outputs are at 50% duty cycle.
 * - 2 : Play mode, the amplifiers are active.
 *
 * @return
 * - 0 : ERROR, there is no desired mode.
 * - 1 : OK, the desired mode is selected.
 *
 * @description Function set one of the three operating mode of the amplifier
 * by setting the TDA7491LP chip on 2x5W Amp Click.
 */
uint8_t c2x5wamp_set_mode ( c2x5wamp_t *ctx, uint8_t select_mode );

/**
 * @brief Set gain resistors of the amplifier function
 *
 * @param ctx  Click object.
 * @param select_gain
 * - 0 : 20dB.
 * - 1 : 26dB.
 * - 2 : 30dB.
 * - 3 : 32dB.
 *
 * @return
 * - 0 : ERROR, nominal amplifier gain is not set.
 * - 1 : OK, nominal amplifier gain is set.
 *
 * @description Function set amplifier gain resistors of the amplifier
 * by setting the TDA7491LP chip on 2x5W Amp Click.
 */
uint8_t c2x5wamp_set_gain ( c2x5wamp_t *ctx, uint8_t select_gain );

/**
 * @brief Check input impedance function
 *
 * @param ctx  Click object.
 * 
 * @return
 * - 0 : Protection is not activated.
 * - 1 : Protection is activated.
 *
 * @description Function checks input impedance is undervoltage, 
 * or is overcurrent or is thermal protection activated
 * of the TDA7491LP chip on 2x5W Amp Click.
 */
uint8_t c2x5wamp_check_input ( c2x5wamp_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C2X5WAMP_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
