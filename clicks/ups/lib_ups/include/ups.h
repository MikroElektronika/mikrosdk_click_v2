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
 * \brief This file contains API for UPS Click driver.
 *
 * \addtogroup ups UPS Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef UPS_H
#define UPS_H

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
#define UPS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.an= MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst= MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cs= MIKROBUS( mikrobus, MIKROBUS_CS ); \
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define UPS_RETVAL  uint8_t

#define UPS_OK           0x00
#define UPS_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup mode Mode
 * \{
 */
#define UPS_MODE_ACTIVE   1
#define UPS_MODE_SLEEP    0
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

    digital_out_t rst;

    // Input pins 

    digital_in_t an;
    digital_in_t cs;

} ups_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t rst;
    pin_name_t cs;

} ups_cfg_t;

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
void ups_cfg_setup ( ups_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
UPS_RETVAL ups_init ( ups_t *ctx, ups_cfg_t *cfg );

/**
 * @brief Functions for settings chip mode
 *
 * @param ctx     Click object.
 * @param mode    Mode which be set
 *
 * @note
 * <pre>
 * Options:
 *    Active mode,
 *	  Sleep mode
 * </pre>
 */
void usp_set_mode ( ups_t *ctx, uint8_t mode );

/**
 * @brief Functions for reading PGD state
 *
 * @param ctx     Click object.
 * 
 * @return PGD (Power good) pin state
 *
 * @description PGD goes high when Vout is within 6% of target value (4.98V)
 */
uint8_t ups_get_power_good ( ups_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _UPS_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
