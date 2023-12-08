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
 * \brief This file contains API for MUX Click driver.
 *
 * \addtogroup mux MUX Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MUX_H
#define MUX_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
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
#define MUX_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.a0 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );  \
  cfg.a1 = MIKROBUS( mikrobus, MIKROBUS_PWM );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MUX_RETVAL  uint8_t

#define MUX_OK           0x00
#define MUX_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup select_channel Select channel
 * \{
 */
#define MUX_CHANNEL_1A_AND_1B    0x01
#define MUX_CHANNEL_2A_AND_2B    0x02
#define MUX_CHANNEL_3A_AND_3B    0x03
#define MUX_CHANNEL_4A_AND_4B    0x04
#define MUX_CHANNEL_END          0x05
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

    digital_out_t a0;
    digital_out_t en;
    digital_out_t a1;

} mux_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t a0;
    pin_name_t en;
    pin_name_t a1;

} mux_cfg_t;

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
void mux_cfg_setup ( mux_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param mux Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MUX_RETVAL mux_init ( mux_t *ctx, mux_cfg_t *cfg );

/**
 * @brief Enable MUX device function.
 *
 * @param ctx  Click object.
 *
 * @description This function enable MUX device for Mux click.
 */
void mux_device_enable ( mux_t *ctx );

/**
 * @brief Disable MUX device function.
 *
 * @param ctx  Click object.
 *
 * @description This function disable MUX device for Mux click.
 */
void mux_device_disable ( mux_t *ctx );

/**
 * @brief Seelect active MUX channel
 *
 * @param ctx       Click object.
 * @param sel_ch   
 * Currently active channel:
 * <pre>
 * 0x01 ( MUX_CHANNEL_1A_AND_1B ) : Enable channel 1A and 1B;
 * </pre>
 * 
 * <pre>
 * 0x02 ( MUX_CHANNEL_2A_AND_2B ) : Enable channel 2A and 2B;
 * </pre>
 * 
 * <pre>
 * 0x03 ( MUX_CHANNEL_3A_AND_3B ) : Enable channel 3A and 3B;
 * </pre>
 * 
 * <pre>
 * 0x04 ( MUX_CHANNEL_4A_AND_4B ) : Enable channel 4A and 4B;
 * </pre>
 *
 * @description This function active sel_ch MUX channel for Mux click.
 */
void mux_active_mux_channel ( mux_t *ctx, uint8_t sel_ch );

#ifdef __cplusplus
}
#endif
#endif  // _MUX_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
