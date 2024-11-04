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
 * @file buck9.h
 * @brief This file contains API for Buck 9 Click Driver.
 */

#ifndef BUCK9_H
#define BUCK9_H

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
 * @addtogroup buck9 Buck 9 Click Driver
 * @brief API for configuring and manipulating Buck 9 Click driver.
 * @{
 */

/**
 * @defgroup buck9_mode Buck 9 Device mode.
 * @brief Settings for device mode of Buck 9 Click driver.
 */

/**
 * @addtogroup buck9_mode
 * @{
 */

/**
 * @brief Buck 9 mode settings.
 * @details Specified setting for device mode of Buck 9 Click driver.
 */
    #define BUCK9_DEVICE_ENABLE  0x01
    #define BUCK9_DEVICE_DISABLE 0x00

/*! @} */ // buck9_mode

/**
 * @defgroup buck9_map Buck 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Buck 9 Click driver.
 */

/**
 * @addtogroup buck9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck 9 Click to the selected MikroBUS.
 */
#define BUCK9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // buck9_map
/*! @} */ // buck9

/**
 * @brief Buck 9 Click context object.
 * @details Context object definition of Buck 9 Click driver.
 */
typedef struct
{
    // Output pins 
    
    digital_out_t  en; 
    
} buck9_t;

/**
 * @brief Buck 9 Click configuration object.
 * @details Configuration object definition of Buck 9 Click driver.
 */
typedef struct
{
    // Additional gpio pins 
    
    pin_name_t  en;  

} buck9_cfg_t;

/**
 * @brief Buck 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BUCK9_OK = 0,
   BUCK9_ERROR = -1

} buck9_return_value_t;

/*!
 * @addtogroup buck9 Buck 9 Click Driver
 * @brief API for configuring and manipulating Buck 9 Click driver.
 * @{
 */

/**
 * @brief Buck 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buck9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buck9_cfg_setup ( buck9_cfg_t *cfg );

/**
 * @brief Buck 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #buck9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buck9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buck9_init ( buck9_t *ctx, buck9_cfg_t *cfg );

/**
 * @brief Function for enable or disable device
 * @details This function enables and disables output of this Click board.
 * @param[in] ctx : Click context object.
 * See #buck9_t object definition for detailed explanation.
 * @param[in] mode : Disable or enable device
 * @return Nothing.
 * 
 * @note When the device is enabled at the output 
 * gives 3.3v or 5v depending on the position of the jumper.
 */
void buck9_set_device_mode ( buck9_t *ctx, uint8_t mode);

#ifdef __cplusplus
}
#endif
#endif // BUCK9_H

/*! @} */ // buck9

// ------------------------------------------------------------------------ END
