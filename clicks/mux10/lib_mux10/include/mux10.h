/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file mux10.h
 * @brief This file contains API for MUX 10 Click Driver.
 */

#ifndef MUX10_H
#define MUX10_H

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
 * @addtogroup mux10 MUX 10 Click Driver
 * @brief API for configuring and manipulating MUX 10 Click driver.
 * @{
 */

/**
 * @defgroup mux10_set MUX 10 Settings
 * @brief Settings of MUX 10 Click driver.
 */

/**
 * @addtogroup mux10_set
 * @{
 */

/**
 * @brief MUX 10 channel selection setting.
 * @details Specified setting for channel selection of MUX 10 Click driver.
 */
#define MUX10_SELECT_CH_1       1
#define MUX10_SELECT_CH_2       2
#define MUX10_SELECT_CH_3       3
#define MUX10_SELECT_CH_4       4

/**
 * @brief MUX 10 pin logic level setting.
 * @details Specified setting for pin logic level of MUX 10 Click driver.
 */
#define MUX10_HIGH_LOGIC_STATE  1
#define MUX10_LOW_LOGIC_STATE   0 

/*! @} */ // mux10_set

/**
 * @defgroup mux10_map MUX 10 MikroBUS Map
 * @brief MikroBUS pin mapping of MUX 10 Click driver.
 */

/**
 * @addtogroup mux10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MUX 10 Click to the selected MikroBUS.
 */
#define MUX10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.a1 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.a0 = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // mux10_map
/*! @} */ // mux10

/**
 * @brief MUX 10 Click context object.
 * @details Context object definition of MUX 10 Click driver.
 */
typedef struct
{
    digital_out_t a1;       /**< Address bit 1 pin. */
    digital_out_t a0;       /**< Address bit 0 pin. */

} mux10_t;

/**
 * @brief MUX 10 Click configuration object.
 * @details Configuration object definition of MUX 10 Click driver.
 */
typedef struct
{
    pin_name_t a1;          /**< Address bit 1 pin descriptor. */
    pin_name_t a0;          /**< Address bit 0 pin descriptor. */

} mux10_cfg_t;

/**
 * @brief MUX 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MUX10_OK = 0,
    MUX10_ERROR = -1

} mux10_return_value_t;

/*!
 * @addtogroup mux10 MUX 10 Click Driver
 * @brief API for configuring and manipulating MUX 10 Click driver.
 * @{
 */

/**
 * @brief MUX 10 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mux10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mux10_cfg_setup ( mux10_cfg_t *cfg );

/**
 * @brief MUX 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #mux10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mux10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t mux10_init ( mux10_t *ctx, mux10_cfg_t *cfg );

/**
 * @brief MUX 10 set A0 pin function.
 * @details This function sets the A0 pin to desired logic state.
 * @param[in] ctx : Click context object.
 * See #mux10_t object definition for detailed explanation.
 * @param[in] state : Pin logic level.
 * @return Nothing.
 * @note None.
 */
void mux10_set_a0 ( mux10_t *ctx, uint8_t state );

/**
 * @brief MUX 10 set A1 pin function.
 * @details This function sets the A1 pin to desired logic state.
 * @param[in] ctx : Click context object.
 * See #mux10_t object definition for detailed explanation.
 * @param[in] state : Pin logic level.
 * @return Nothing.
 * @note None.
 */
void mux10_set_a1 ( mux10_t *ctx, uint8_t state );

/**
 * @brief MUX 10 active channel selection function.
 * @details This function selects the active channel of the device
 * by driving the A0 and A1 address lines.
 * @param[in] ctx : Click context object.
 * See #mux10_t object definition for detailed explanation.
 * @param[in] sel_ch : @li @c 1 - Address lines A1A0 = 00 ( S1 if A2 low, S5 if A2 high ),
 *                     @li @c 2 - Address lines A1A0 = 01 ( S2 if A2 low, S6 if A2 high ),
 *                     @li @c 3 - Address lines A1A0 = 10 ( S3 if A2 low, S7 if A2 high ),
 *                     @li @c 4 - Address lines A1A0 = 11 ( S4 if A2 low, S8 if A2 high ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The A2 address line is set by the SW1 onboard switch and
 * selects the channel bank ( A2 low: S1-S4, A2 high: S5-S8 ).
 */
err_t mux10_active_channel_sel ( mux10_t *ctx, uint8_t sel_ch );

#ifdef __cplusplus
}
#endif
#endif // MUX10_H

/*! @} */ // mux10

// ------------------------------------------------------------------------ END
