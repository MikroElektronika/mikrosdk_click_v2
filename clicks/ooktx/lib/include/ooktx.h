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
 * \brief This file contains API for OOK TX Click driver.
 *
 * \addtogroup ooktx OOK TX Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef OOKTX_H
#define OOKTX_H

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
#define OOKTX_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define OOKTX_RETVAL  uint8_t

#define OOKTX_OK           0x00
#define OOKTX_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup configuration_values Configuration Values
 * \{
 */
#define OOKTX_CALIBRATION_ENABLE      0x01
#define OOKTX_CALIBRATION_DISABLE     0x00
#define OOKTX_CONFIGURATION_ENABLE    0x01
#define OOKTX_CONFIGURATION_DISABLE   0x00
#define OOKTX_CFG_DEFAULT             0xF6F0
#define OOKTX_CFG_F_433MHZ            0xF000
#define OOKTX_CFG_CX_18PF             0x0600
#define OOKTX_CFG_P_13DB              0x00F0
#define OOKTX_CFG_P_10DB              0x00C0
#define OOKTX_CFG_P_7DB               0x0090
#define OOKTX_CFG_P_3DB               0x0050
#define OOKTX_CFG_P_0DB               0x0020
#define OOKTX_CFG_CT_0PF              0x0000
#define OOKTX_PREAMBULE               0xAA
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

    digital_out_t sda;
    digital_out_t scl;

} ooktx_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t sda;
    pin_name_t scl;

} ooktx_cfg_t;

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
void ooktx_cfg_setup ( ooktx_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ooktx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
OOKTX_RETVAL ooktx_init ( ooktx_t *ctx, ooktx_cfg_t *cfg );

/**
 * @brief Communication initiation function.
 * 
 * @param ctx             Click object.
 * @param calibration     Calibration byte.
 * @param configuration   Configuration byte. 
 * @param cfg_settings    Config settings byte.
 * 
 * @description This function initiates the OOK communication.
 */
void ooktx_communication_init ( ooktx_t *ctx, uint8_t calibration, 
                                uint8_t configuration, uint16_t cfg_settings );
/**
 * @brief Communication stop function.
 * 
 * @param ctx   Click object.
 * 
 * @description This function stops the OOK communication.
 */
void ooktx_communication_stop ( ooktx_t *ctx );

/**
 * @brief Communication transmit function.
 * 
 * @param ctx             Click object.
 * @param transmit_data   Data package byte. 
 * 
 * @description This function transmits data in the OOK communication.
 */
void ooktx_communication_transmit ( ooktx_t *ctx, uint8_t transmit_data );

/**
 * @brief Communication transmit function.
 * 
 * @param ctx             Click object.
 * @param preable_word   Preable word. 
 * @param transmit_byte   Data package byte. 
 * 
 * @description This function transmits data in the OOK communication.
 */
void ooktx_transmit_byte ( ooktx_t *ctx, uint16_t preable_word, uint8_t transmit_byte );

/**
 * @brief Communication transmit function.
 * 
 * @param ctx             Click object.
 * @param preable_word   Preable word. 
 * @param transmit_data   Data package. 
 * @param transmit_len   Data package length. 
 * 
 * @description This function transmits data in the OOK communication.
 */
void ooktx_transmit_data ( ooktx_t *ctx, uint16_t preable_word, uint8_t *transmit_data, uint8_t transmit_len );

#ifdef __cplusplus
}
#endif
#endif  // _OOKTX_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
