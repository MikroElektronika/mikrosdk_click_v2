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
 * \brief This file contains API for Peltier Click driver.
 *
 * \addtogroup peltier Peltier Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef PELTIER_H
#define PELTIER_H

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
#define PELTIER_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.en2= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.en1= MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.chg= MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.con= MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define PELTIER_RETVAL  uint8_t

#define PELTIER_OK           0x00
#define PELTIER_INIT_ERROR   0xFF
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

    digital_out_t en2;
    digital_out_t en1;

    // Input pins 

    digital_in_t chg;
    digital_in_t con;

} peltier_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t en2;
    pin_name_t en1;
    pin_name_t chg;
    pin_name_t con;

} peltier_cfg_t;

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
void peltier_cfg_setup ( peltier_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param peltier Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
PELTIER_RETVAL peltier_init ( peltier_t *ctx, peltier_cfg_t *cfg );

/**
 * @brief Enables LDO2 function.
 *
 * @param ctx  Click object.
 *
 * @description This function is used to enable 3.3V output.
 */
void peltier_enable_ldo2 ( peltier_t *ctx );

/**
 * @brief Disables LDO2 function.
 *
 * @param ctx  Click object.
 *
 * @description This function is used to disable 3.3V output..
 */
void peltier_disable_ldo2 ( peltier_t *ctx );

/**
 * @brief Enables LDO1 function.
 *
 * @param ctx  Click object.
 *
 * @description This function is used to enable 1.8V output.
 */
void peltier_enable_ldo1 ( peltier_t *ctx );

/**
 * @brief Disables LDO1 function.
 *
 * @param ctx  Click object.
 *
 * @description This function is used to disable 1.8V output.
 */
void peltier_disable_ldo1 ( peltier_t *ctx );

/**
 * @brief Check ongoing battery charge flag pin function.
 *
 * @param ctx  Click object.
 *
 * @description This function is used to check ongoing battery charge flag pin.
 */
uint8_t peltier_battery_charge ( peltier_t *ctx );

/**
 * @brief Check input voltage good flag pin function.
 *
 * @param ctx  Click object.
 *
 * @description This function is used to check input voltage flag pin.
 */
uint8_t peltier_vin_good_flag ( peltier_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _PELTIER_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
