/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file motion2.h
 * @brief This file contains API for Motion 2 Click Driver.
 */

#ifndef MOTION2_H
#define MOTION2_H

#ifdef __cplusplus
extern "C"{
#endif

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
    
/*!
 * @addtogroup motion2 Motion 2 Click Driver
 * @brief API for configuring and manipulating Motion 2 Click driver.
 * @{
 */

/**
 * @defgroup motion2_set Motion 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Motion 2 Click driver.
 */

/**
 * @addtogroup motion2_set
 * @{
 */

/**
 * @brief MikroBUS pin set.
 * @details Set pins state of Motion 2 Click to the selected MikroBUS.
 */
#define MOTION2_MODULE_ENABLE     0x00
#define MOTION2_MODULE_DISABLE    0x01
#define MOTION2_NO_DETECT_OBJECT  0x00
#define MOTION2_DETECT_OBJECT     0x01

/*! @} */ // motion2_set

/**
 * @defgroup motion2_map Motion 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Motion 2 Click driver.
 */

/**
 * @addtogroup motion2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Motion 2 Click to the selected MikroBUS.
 */
#define MOTION2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );  \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // motion2_map
/*! @} */ // motion2

/**
 * @brief Motion 2 Click context object.
 * @details Context object definition of Motion 2 Click driver.
 */
typedef struct
{
    // Output pins 
    
    digital_out_t en;
    
      // Input pins 
    
    digital_in_t int_pin;
    
} motion2_t;

/**
 * @brief Motion 2 Click configuration object.
 * @details Configuration object definition of Motion 2 Click driver.
 */
typedef struct
{
    // Additional gpio pins 
    
    pin_name_t en;
    pin_name_t int_pin;

} motion2_cfg_t;

/**
 * @brief Motion 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   MOTION2_OK = 0,
   MOTION2_ERROR = -1

} motion2_return_value_t;
/*! @} */ // 
/*!
 * @addtogroup motion2 Motion 2 Click Driver
 * @brief API for configuring and manipulating Motion 2 Click driver.
 * @{
 */
typedef enum
{
    MOTION2_NO_DETECT = 0,
    MOTION2_DETECTED

} motion2_detect_state_t;

typedef enum
{
    MOTION2_PIN_STATE_LOW = 0,
    MOTION2_PIN_STATE_HIGH

} motion2_pin_state_t;


/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void motion2_cfg_setup ( motion2_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param motion2 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
err_t motion2_init ( motion2_t *ctx, motion2_cfg_t *cfg );

/**
 * @brief Enable motion sensor function.
 *
 * @param state Enable/Disable sensor
 * 
 * @description This function enables/disables motion sensor by setting EN pin state.
 */
void motion2_enable ( motion2_t *ctx, uint8_t state );

/**
 * @brief Get detection state function.
 *
 * @return  Detection status
 *          ( 1 - Detected / 0 - Not detected )
 * 
 * @description This function returns INT pin state.
 */
uint8_t motion2_detect_state ( motion2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // MOTION2_H

/*! @} */ // motion2

// ------------------------------------------------------------------------ END
