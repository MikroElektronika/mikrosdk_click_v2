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
 * \brief This file contains API for MUX 3 Click driver.
 *
 * \addtogroup mux3 MUX 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MUX3_H
#define MUX3_H

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
#define MUX3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.a1= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.a0= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.a2= MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MUX3_RETVAL  uint8_t

#define MUX3_OK           0x00
#define MUX3_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup channels Channels
 * \{
 */
#define MUX3_DISABLE_ALL_CHANNELS                                  0x00
#define MUX3_ENABLE_CHANNEL_S1                                     0x01
#define MUX3_ENABLE_CHANNEL_S2                                     0x02
#define MUX3_ENABLE_CHANNEL_S3                                     0x03
#define MUX3_ENABLE_CHANNEL_S4                                     0x04
#define MUX3_ENABLE_CHANNEL_S5                                     0x05
#define MUX3_ENABLE_CHANNEL_S6                                     0x06
#define MUX3_ENABLE_CHANNEL_S7                                     0x07
#define MUX3_ENABLE_CHANNEL_S8                                     0x08
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

    digital_out_t a1;
    digital_out_t a0;
    digital_out_t en;
    digital_out_t a2;

} mux3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t a1;
    pin_name_t a0;
    pin_name_t en;
    pin_name_t a2;

} mux3_cfg_t;

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
void mux3_cfg_setup ( mux3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param mux3 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
MUX3_RETVAL mux3_init ( mux3_t *ctx, mux3_cfg_t *cfg );

/**
 * @brief Set active MUX channel function
 *
 * @param ctx              Click object.
 * @param select_channel
 * Currently active channel:
 * - 0x00 ( MUX3_DISABLE_ALL_CHANNELS ): Disable all channels;
 * - 0x01 ( MUX3_ENABLE_CHANNEL_S1 )   : Enable channel S1;
 * - 0x02 ( MUX3_ENABLE_CHANNEL_S2 )   : Enable channel S2;
 * - 0x03 ( MUX3_ENABLE_CHANNEL_S3 )   : Enable channel S3;
 * - 0x04 ( MUX3_ENABLE_CHANNEL_S4 )   : Enable channel S4;
 * - 0x05 ( MUX3_ENABLE_CHANNEL_S5 )   : Enable channel S5;
 * - 0x06 ( MUX3_ENABLE_CHANNEL_S6 )   : Enable channel S6;
 * - 0x07 ( MUX3_ENABLE_CHANNEL_S7 )   : Enable channel S7;
 * - 0x08 ( MUX3_ENABLE_CHANNEL_S8 )   : Enable channel S8;
 *
 * @description Function enable MUX channel of the
 * TMUX1208 Bidirectional 8-Channel Multiplexer on the MUX 3 Click board.
 */
void mux3_set_channel ( mux3_t *ctx, uint8_t select_channel );

#ifdef __cplusplus
}
#endif
#endif  // _MUX3_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
