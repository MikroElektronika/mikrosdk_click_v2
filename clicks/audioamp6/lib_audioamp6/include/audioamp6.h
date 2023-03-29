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
 * \brief This file contains API for AudioAmp 6 Click driver.
 *
 * \addtogroup audioamp6 AudioAmp 6 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AUDIOAMP6_H
#define AUDIOAMP6_H

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
#define AUDIOAMP6_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.mds= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.gs= MIKROBUS( mikrobus, MIKROBUS_PWM );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AUDIOAMP6_RETVAL  uint8_t

#define AUDIOAMP6_OK           0x00
#define AUDIOAMP6_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup gain Gain
 * \{
 */
#define AUDIOAMP6_GAIN_20dB  0x00
#define AUDIOAMP6_GAIN_26dB  0x01
/** \} */

/**
 * \defgroup output Output
 * \{
 */
#define AUDIOAMP6_OUTPUT_ENABLE   0x01
#define AUDIOAMP6_OUTPUT_DISABLE  0x00
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define AUDIOAMP6_MODE_BD    0x00
#define AUDIOAMP6_MODE_1SPW  0x01
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

    digital_out_t mds;
    digital_out_t en;
    digital_out_t gs;

} audioamp6_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t mds;
    pin_name_t en;
    pin_name_t gs;

} audioamp6_cfg_t;

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
void audioamp6_cfg_setup ( audioamp6_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param audioamp6 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AUDIOAMP6_RETVAL audioamp6_init ( audioamp6_t *ctx, audioamp6_cfg_t *cfg );

/**
 * @brief Sets mode
 *
 * @param ctx  Click object.
 * @param mode
 * <pre>
 *     Low = BD Mode/UV Threshold = 7.5 V
 *     High = Low-Idle-Current 1SPW Mode/UV Threshold = 3.4V
 * </pre>
 */
void audioamp6_set_mode( audioamp6_t *ctx, uint8_t mode );

/**
 * @brief Enable or Disable output
 *
 * @param ctx    Click object.
 * @param out    Output enabled or disabled
 */
void audioamp6_set_output( audioamp6_t *ctx, uint8_t out );

/**
 * @brief Sets Gain
 *
 * @param ctx     Click object.
 * @param gain    GAIN 20 dB or 26 dB
 */
void audioamp6_set_gain( audioamp6_t *ctx, uint8_t gain );

#ifdef __cplusplus
}
#endif
#endif  // _AUDIOAMP6_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
