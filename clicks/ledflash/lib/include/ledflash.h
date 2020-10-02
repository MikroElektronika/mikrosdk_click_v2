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
 * \brief This file contains API for LED Flash Click driver.
 *
 * \addtogroup ledflash LED Flash Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef LEDFLASH_H
#define LEDFLASH_H

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
#define LEDFLASH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.ch_ena = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.fls    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.tor    = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flg    = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define LEDFLASH_RETVAL  uint8_t

#define LEDFLASH_OK           0x00
#define LEDFLASH_INIT_ERROR   0xFF
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

    digital_out_t ch_ena;
    digital_out_t fls;
    digital_out_t tor;

    // Input pins 

    digital_in_t flg;

} ledflash_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t ch_ena;
    pin_name_t fls;
    pin_name_t tor;
    pin_name_t flg;

} ledflash_cfg_t;

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
void ledflash_cfg_setup ( ledflash_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ledflash Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
LEDFLASH_RETVAL ledflash_init ( ledflash_t *ctx, ledflash_cfg_t *cfg );

/**
 * @brief Charge Supercapacitor Enable function
 *
 * @param ctx Click object.
 *
 * @description Function enables charging of the supercapacitor.
**/
void ledflash_char_supcap_enable ( ledflash_t *ctx );

/**
 * @brief Flash Enable function
 *
 * @param ctx Click object.
 *
 * @description Function enables flash.
**/
void ledflash_flash_enable ( ledflash_t *ctx );

/**
 * @brief Torch Enable function
 *
 * @param ctx Click object.
 *
 * @description Function enables torch.
**/
void ledflash_torch_enable ( ledflash_t *ctx );

/**
 * @brief Charge Supercapacitor Disable function
 *
 * @param ctx Click object.
 *
 * @description Function disables charging of the supercapacitor.
**/
void ledflash_char_supcap_disable ( ledflash_t *ctx );

/**
 * @brief Flash Disable function
 *
 * @param ctx Click object.
 *
 * @description Function disables flash.
**/
void ledflash_flash_disable ( ledflash_t *ctx );

/**
 * @brief Torch Disable function
 *
 * @param ctx Click object.
 *
 * @description Function disables torch.
**/
void ledflash_torch_disable ( ledflash_t *ctx );

/**
 * @brief Check Flash Ready Flag function
 *
 * @param ctx Click object.
 *
 * @returns '0' if flash is not ready
 * @returns '1' if flash is ready
 *
 * @description Functions checks the flash ready flag.
**/
uint8_t ledflash_flash_rdy_flag ( ledflash_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _LEDFLASH_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
