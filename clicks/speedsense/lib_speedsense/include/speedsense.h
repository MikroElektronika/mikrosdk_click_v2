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
 * @file speedsense.h
 * @brief This file contains API for Speed Sense Click Driver.
 */

#ifndef SPEEDSENSE_H
#define SPEEDSENSE_H

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
 * @addtogroup speedsense Speed Sense Click Driver
 * @brief API for configuring and manipulating Speed Sense Click driver.
 * @{
 */

/**
 * @addtogroup speedsense_set
 * @{
 */

/**
 * @brief Speed Sense conversion of minutes to milliseconds data value.
 * @details Conversion of minutes to milliseconds data value of Speed Sense Click driver.
 */
#define SPEEDSENSE_CNV_MIN_TO_MS          60000.0f

/**
 * @brief Speed Sense output signal states data value.
 * @details Output signal states data value of Speed Sense Click driver.
 */
#define SPEEDSENSE_DIR_STATE_FWD          0
#define SPEEDSENSE_DIR_STATE_RVS          1
#define SPEEDSENSE_SPEED_STATE_LOW        0
#define SPEEDSENSE_SPEED_STATE_HIGH       1

/**
 * @brief Speed Sense measurement state data values.
 * @details Measurement state data values of Speed Sense Click driver.
 */
#define SPEEDSENSE_STOP_MEASURE           0
#define SPEEDSENSE_START_NEW_MEASURE      1

/*! @} */ // speedsense_set

/**
 * @defgroup speedsense_map Speed Sense MikroBUS Map
 * @brief MikroBUS pin mapping of Speed Sense Click driver.
 */

/**
 * @addtogroup speedsense_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Speed Sense Click to the selected MikroBUS.
 */
#define SPEEDSENSE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.chb = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.cha = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // speedsense_map
/*! @} */ // speedsense

/**
 * @brief Speed Sense Click context object.
 * @details Context object definition of Speed Sense Click driver.
 */
typedef struct
{
    digital_in_t chb;    /**< Digital output direction signal. */
    digital_in_t cha;    /**< Digital output speed signal. */

} speedsense_t;

/**
 * @brief Speed Sense Click configuration object.
 * @details Configuration object definition of Speed Sense Click driver.
 */
typedef struct
{
    pin_name_t chb;    /**< Digital output direction signal. */
    pin_name_t cha;    /**< Digital output speed signal. */

} speedsense_cfg_t;

/**
 * @brief Speed Sense Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SPEEDSENSE_OK = 0,
    SPEEDSENSE_ERROR = -1

} speedsense_return_value_t;

/*!
 * @addtogroup speedsense Speed Sense Click Driver
 * @brief API for configuring and manipulating Speed Sense Click driver.
 * @{
 */

/**
 * @brief Speed Sense configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #speedsense_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void speedsense_cfg_setup ( speedsense_cfg_t *cfg );

/**
 * @brief Speed Sense initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #speedsense_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #speedsense_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speedsense_init ( speedsense_t *ctx, speedsense_cfg_t *cfg );

/**
 * @brief Speed Sense CHA pin reading function.
 * @details This function reads the state of the CHA pin used for speed output protocols
 * Speed Sense Click board.
 * @param[in] ctx : Click context object.
 * See #speedsense_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t speedsense_get_speed ( speedsense_t *ctx );

/**
 * @brief Speed Sense CHB pin reading function.
 * @details This function reads the state of the CHB pin used for direction output protocols
 * of Speed Sens Click board.
 * @param[in] ctx : Click context object.
 * See #speedsense_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t speedsense_get_direction ( speedsense_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SPEEDSENSE_H

/*! @} */ // speedsense

// ------------------------------------------------------------------------ END
