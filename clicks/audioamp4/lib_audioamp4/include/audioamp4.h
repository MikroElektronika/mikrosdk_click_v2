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
 * \brief This file contains API for AudioAmp 4 Click driver.
 *
 * \addtogroup audioamp4 AudioAmp 4 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef AUDIOAMP4_H
#define AUDIOAMP4_H

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
#define AUDIOAMP4_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.s0  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.s1  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.s2  = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define AUDIOAMP4_RETVAL  uint8_t

#define AUDIOAMP4_OK                0x00
#define AUDIOAMP4_SHTDWN_STATE_ERR  0x01
#define AUDIOAMP4_VOL_CHANN_ERR     0x02
/** \} */

/**
 * \defgroup volume_channels Volume Channels
 * \{
 */
#define AUDIOAMP4_VOLUME_CHANN_0               0x00 
#define AUDIOAMP4_VOLUME_CHANN_1               0x01 
#define AUDIOAMP4_VOLUME_CHANN_2               0x02 
#define AUDIOAMP4_VOLUME_CHANN_3               0x03 
#define AUDIOAMP4_VOLUME_CHANN_4               0x04 
#define AUDIOAMP4_VOLUME_CHANN_5               0x05 
#define AUDIOAMP4_VOLUME_CHANN_6               0x06 
#define AUDIOAMP4_VOLUME_CHANN_7               0x07 
/** \} */

/**
 * \defgroup shutdown_state Shutdown State
 * \{
 */
#define AUDIOAMP4_SHUTDOWN_ON          0x01
#define AUDIOAMP4_SHUTDOWN_OFF         0x00
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

    digital_out_t s0;
    digital_out_t s1;
    digital_out_t en;
    digital_out_t pwm;
    digital_out_t s2;

} audioamp4_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t s0;
    pin_name_t s1;
    pin_name_t en;
    pin_name_t pwm;
    pin_name_t s2;

} audioamp4_cfg_t;

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
void audioamp4_cfg_setup ( audioamp4_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param audioamp4 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
AUDIOAMP4_RETVAL audioamp4_init ( audioamp4_t *ctx, audioamp4_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for AudioAmp 4 click.
 * 
 * @note Default Configuration
 * <pre>
 *    Device State       : OFF        - AUDIOAMP4_SHUTDOWN_OFF 
 *    Set Channel        : Channel 0  - AUDIOAMP4_VOLUME_CHANN_0
 * </pre>
 */
void audioamp4_default_cfg ( audioamp4_t *ctx );


/**
 * @brief Set channel function function.
 *
 * @param ctx        Click object.
 * @param channel    Selected channel
 *  
 * @returns          Returns device response
 * 
 * @description This function executes default configuration for AudioAmp 4 click.
 */
AUDIOAMP4_RETVAL audioamp4_set_channel ( audioamp4_t *ctx, uint8_t channel );

/**
 * @brief Set channel function function.
 *
 * @param ctx        Click object.
 * @param state      State of device
 *  
 * @returns          Returns device response
 * 
 * @description This function executes default configuration for AudioAmp 4 click.
 */
AUDIOAMP4_RETVAL audioamp4_shutdown ( audioamp4_t *ctx, uint8_t state );


#ifdef __cplusplus
}
#endif
#endif  // _AUDIOAMP4_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
