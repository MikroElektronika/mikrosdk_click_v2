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
 * \brief This file contains API for MCP73871 Click driver.
 *
 * \addtogroup mcp73871 MCP73871 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef MCP73871_H
#define MCP73871_H

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
#define MCP73871_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.pg2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.ce = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.te = MIKROBUS( mikrobus, MIKROBUS_PWM ) 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define MCP73871_RETVAL  uint8_t

#define MCP73871_OK           0x00
#define MCP73871_INIT_ERROR   0xFF
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

    digital_out_t pg2;
    digital_out_t ce;
    digital_out_t te;

} mcp73871_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t pg2;
    pin_name_t ce;
    pin_name_t te;

} mcp73871_cfg_t;

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
void mcp73871_cfg_setup ( mcp73871_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param mcp73871 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
MCP73871_RETVAL mcp73871_init ( mcp73871_t *ctx, mcp73871_cfg_t *cfg );

/**
 * @brief Enable pin control
 *
 * @param ctx         Click object.
 * @param pin_state   1 = click enabled, 0 = click disabled
 *
 * @description Controls the CE pin, enabling or disabling the click operation.
 */
void mcp73871_enable_pin_control ( mcp73871_t *ctx, uint8_t pin_state );

/**
 * @brief Prog pin control
 *
 * @param ctx         Click object.
 * @param pin_state   1 = 500 mA input current, 0 = 100 mA input current
 *
 * @description Controls the PROG pin, setting the USB input current.
 */
void mcp73871_prog_pin_control ( mcp73871_t *ctx, uint8_t pin_state );

/**
 * @brief Timer pin control
 *
 * @param ctx         Click object.
 * @param pin_state   1 = timer disabled, 0 = timer enabled.
 *
 * @description Controls the TE pin, disabling or enabling safety timer.
 */
void mcp73871_timer_pin_control ( mcp73871_t *ctx, uint8_t pin_state );

#ifdef __cplusplus
}
#endif
#endif  // _MCP73871_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
