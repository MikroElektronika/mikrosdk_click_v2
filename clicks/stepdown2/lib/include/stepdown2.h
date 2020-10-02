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
 * \brief This file contains API for Step Down 2 Click driver.
 *
 * \addtogroup stepdown2 Step Down 2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef STEPDOWN2_H
#define STEPDOWN2_H

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
#define STEPDOWN2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.err = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en  = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define STEPDOWN2_RETVAL  uint8_t

#define STEPDOWN2_OK           0x00
#define STEPDOWN2_INIT_ERROR   0xFF
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

    digital_out_t en;

    // Input pins 

    digital_in_t err;

} stepdown2_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t err;
    pin_name_t en;

} stepdown2_cfg_t;

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
void stepdown2_cfg_setup ( stepdown2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param stepdown2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
STEPDOWN2_RETVAL stepdown2_init ( stepdown2_t *ctx, stepdown2_cfg_t *cfg );

/**
 * @brief Digital read reset function.
 *
 * @param ctx  Click object.
 *
 * @description This function reads the digital signal from the RST pin.
 */
uint8_t stepdown2_digital_read_rst ( stepdown2_t *ctx );

/**
 * @brief Digital write chip select function.
 *
 * @param ctx      Click object.
 * @param signal   Digital output signal.
 *
 * @description This function writes the specified digital signal to the CS pin.
 */
void stepdown2_digital_write_cs ( stepdown2_t *ctx, uint8_t signal );

#ifdef __cplusplus
}
#endif
#endif  // _STEPDOWN2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
