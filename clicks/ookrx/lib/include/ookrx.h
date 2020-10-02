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
 * \brief This file contains API for OOK RX Click driver.
 *
 * \addtogroup ookrx OOK RX Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OOKRX_H
#define OOKRX_H

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
#define OOKRX_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.rsi = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.en  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.sq  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.do_pin  = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OOKRX_RETVAL  uint8_t

#define OOKRX_OK           0x00
#define OOKRX_INIT_ERROR   0xFF
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
    digital_out_t sq;

    // Input pins 

    digital_in_t rsi;
    digital_in_t do_pin;

} ookrx_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t rsi;
    pin_name_t en;
    pin_name_t sq;
    pin_name_t do_pin;

} ookrx_cfg_t;

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
void ookrx_cfg_setup ( ookrx_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ookrx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OOKRX_RETVAL ookrx_init ( ookrx_t *ctx, ookrx_cfg_t *cfg );

/**
 * @brief Receive data function.
 * 
 * @param ctx              Click object.
 * @param start_package    Start package byte.
 * @param receive_buffer   Buffer to which data is written. 
 * @param bytes_num        Number of data packages to read.
 * 
 * @description This function receives data in the OOK communication.
 */
uint8_t ookrx_receive_data ( ookrx_t *ctx, uint16_t start_package, 
                             uint8_t *receive_buffer, uint8_t bytes_num );

/**
 * @brief Read DO pin function.
 * 
 * @param ctx              Click object.
 * 
 * @description This function reads the od pin digital input.
 */
uint8_t ookrx_read_do_pin ( ookrx_t *ctx );

/**
 * @brief Read RSI pin function.
 * 
 * @param ctx              Click object.
 * 
 * @description This function reads the rsi pin digital input.
 */
uint8_t ookrx_read_rsi_pin ( ookrx_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _OOKRX_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
