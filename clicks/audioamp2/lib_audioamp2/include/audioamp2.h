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
 * \brief This file contains API for Audio Amp 2 Click driver.
 *
 * \addtogroup audioamp2 Audio Amp 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AUDIOAMP2_H
#define AUDIOAMP2_H

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
#define AUDIOAMP2_MAP_MIKROBUS( cfg, mikrobus ) \
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
#define AUDIOAMP2_RETVAL  uint8_t

#define AUDIOAMP2_OK           0x00
#define AUDIOAMP2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mode  Mode
 * \{
 */
#define AUDIOAMP2_STANDBY_MODE   0x00
#define AUDIOAMP2_MUTE_MODE      0x01
#define AUDIOAMP2_PLAY_MODE      0x02
/** \} */

 /**
 * \defgroup gain  Gain
 * \{
 */
#define AUDIOAMP2_20DB_GAIN      0x00
#define AUDIOAMP2_26DB_GAIN      0x01
#define AUDIOAMP2_30DB_GAIN      0x02
#define AUDIOAMP2_32DB_GAIN      0x03
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

} audioamp2_t;

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

} audioamp2_cfg_t;

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
void audioamp2_cfg_setup ( audioamp2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx     Click object.
 * @param cfg     Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AUDIOAMP2_RETVAL audioamp2_init ( audioamp2_t *ctx, audioamp2_cfg_t *cfg );

/**
 * @brief Mode Set function
 *
 * @param ctx           Click object.
 * @param sel_mode      0 - Standby Mode, 1 - Mute Mode, 2 - Play Mode
 *
 * @return 0 - OK, 1 - Wrong sel_mode parameter
 *
 * @description Function puts device in desired mode.
 */
uint8_t audioamp2_set_mode ( audioamp2_t *ctx, uint8_t sel_mode );

/**
 * @brief Gain Set function
 *
 * @param ctx           Click object.
 * @param sel_gain      0 - 20dB, 1 - 26dB, 2 - 30dB, 3 - 32dB
 *
 * @return 0 - OK, 1 - Wrong sel_gain parameter
 *
 * @description Function performs the gain selection.
 */
uint8_t audioamp2_set_gain ( audioamp2_t *ctx, uint8_t sel_gain );

/**
 * @brief Diagnostic Check function
 *
 * @param ctx  Click object.
 * 
 * @return 0 - Protection is not activated, 1 - Protection is activated
 *
 * @description Function checks is undervoltage, overcurrent or thermal protection activated.
 */
uint8_t audioamp2_check_diagnostic ( audioamp2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AUDIOAMP2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
