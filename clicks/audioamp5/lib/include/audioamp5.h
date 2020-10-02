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
 * \brief This file contains API for Audio Amp 5 Click driver.
 *
 * \addtogroup audioamp5 Audio Amp 5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AUDIOAMP5_H
#define AUDIOAMP5_H

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
#define AUDIOAMP5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.mds= MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.gs= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AUDIOAMP5_RETVAL  uint8_t

#define AUDIOAMP5_OK           0x00
#define AUDIOAMP5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup enable_disable Device Enable/Disable
 * \{
 */
#define AUDIOAMP5_SHDWN_MUTE_OUTPUTS        0x00 
#define AUDIOAMP5_PWRUP_UNMUTE_OUTPUTS      0x01 
/** \} */

/**
 * \defgroup device_mode Device selection mode
 * \{
 */
#define AUDIOAMP5_BD_MODE                   0x00 
#define AUDIOAMP5_1SPW_MODE                 0x01 
/** \} */

/**
 * \defgroup gain  Device gain
 * \{
 */
#define AUDIOAMP5_GAIN_20DB                 0x00 
#define AUDIOAMP5_GAIN_26DB                 0x01 
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

} audioamp5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t mds;
    pin_name_t en;
    pin_name_t gs;

} audioamp5_cfg_t;

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
void audioamp5_cfg_setup ( audioamp5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param audioamp5 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AUDIOAMP5_RETVAL audioamp5_init ( audioamp5_t *ctx, audioamp5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Audio Amp 5 click.
 */
void audioamp5_default_cfg ( audioamp5_t *ctx );

/**
 * @brief Default Configuration function
 *
 * @param ctx    Click object.
 * 
 * @description Function sets a default configuration parameters to the module.
 * 
 * @note Default configuration
 * <pre>
 * Mode select : BD Mode   - AUDIOAMP5_BD_MODE
 * Gain select : 20DB Gain - AUDIOAMP5_GAIN_20DB
 * </pre> 
 */
void audioamp5_set_device_state ( audioamp5_t *ctx, uint8_t state );

/**
 * @brief Mode Selection function
 *
 * @param ctx    Click object.
 * @param state  0 - BD Mode, 1 - 1SPW Mode
 *
 * @description Function puts a device to the desired mode.
 */
void audioamp5_mode_select ( audioamp5_t *ctx, uint8_t state );

/**
 * @brief Gain Selection function
 *
 * @param ctx    Click object.
 * @param state  0 - 20dB, 1 - 26dB
 *
 * @description Function performs a desired gain selection.
 */
void audioamp5_gain_select ( audioamp5_t *ctx, uint8_t state );

/**
 * @brief Configuration Update function
 *
 * @param ctx    Click object.
 *
 * @description Function makes that desired configuration be updated.
 */
void audioamp5_config_update ( audioamp5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _AUDIOAMP5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
