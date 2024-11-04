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
 * @file motion4.h
 * @brief This file contains API for Motion 4 Click Driver.
 */

#ifndef MOTION4_H
#define MOTION4_H

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
 * @addtogroup motion4 Motion 4 Click Driver
 * @brief API for configuring and manipulating Motion 4 Click driver.
 * @{
 */

/**
 * @defgroup motion4_set Motion 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Motion 4 Click driver.
 */

/**
 * @addtogroup motion4_set
 * @{
 */

/**
 * @brief MikroBUS pin set.
 * @details Set pins state of Motion 4 Click to the selected MikroBUS.
 */
#define MOTION4_MODULE_ENABLE     0x00
#define MOTION4_MODULE_DISABLE    0x01
#define MOTION4_NO_DETECT_OBJECT  0x00
#define MOTION4_DETECT_OBJECT     0x01

/*! @} */ // motion4_set


/**
 * @defgroup motion4_map Motion 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Motion 4 Click driver.
 */

/**
 * @addtogroup motion4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Motion 4 Click to the selected MikroBUS.
 */
#define MOTION4_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // motion4_map
/*! @} */ // motion4

/**
 * @brief Motion 4 Click context object.
 * @details Context object definition of Motion 4 Click driver.
 */
typedef struct
{
     // Output pins 
    
    digital_out_t en;
    
      // Input pins 
    
    digital_in_t int_pin;


} motion4_t;

/**
 * @brief Motion 4 Click configuration object.
 * @details Configuration object definition of Motion 4 Click driver.
 */
typedef struct
{
    // Additional gpio pins 
    
    pin_name_t  en;    /**< Description. */
    pin_name_t  int_pin;    /**< Description. */

} motion4_cfg_t;

/**
 * @brief Motion 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   MOTION4_OK = 0,
   MOTION4_ERROR = -1

} motion4_return_value_t;

/*!
 * @addtogroup motion4 Motion 4 Click Driver
 * @brief API for configuring and manipulating Motion 4 Click driver.
 * @{
 */ 

typedef enum
{
    MOTION4_NO_DETECT = 0,
    MOTION4_DETECTED

} motion4_detect_state_t;

typedef enum
{
    MOTION4_PIN_STATE_LOW = 0,
    MOTION4_PIN_STATE_HIGH

} motion4_pin_state_t;


/**
 * @brief Motion 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #motion4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void motion4_cfg_setup ( motion4_cfg_t *cfg );

/**
 * @brief Motion 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #motion4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #motion4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t motion4_init ( motion4_t *ctx, motion4_cfg_t *cfg );

/**
 * @brief Enable motion sensor function.
 * @details This function enables/disables motion sensor by setting EN pin state.
 * @param[out] ctx : Click context object.
 * See #motion4_t object definition for detailed explanation.
 * @param[in] state Enable/Disable sensor
 * @return Nothing.
 * @note None.
 */
void motion4_enable ( motion4_t *ctx, uint8_t state );

/**
 * @brief Get detection state function.
 * @details This function returns INT pin state.
 * @param[out] ctx : Click context object.
 * See #motion4_t object definition for detailed explanation.
 * @return @li @c  1 - Detected.
 *         @li @c  0 - Not detected.
 * @note None.
 */
uint8_t motion4_detect_state ( motion4_t *ctx );



#ifdef __cplusplus
}
#endif
#endif // MOTION4_H

/*! @} */ // motion4

// ------------------------------------------------------------------------ END
