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
 * @file stepdown3.h
 * @brief This file contains API for Step Down 3 Click Driver.
 */

#ifndef STEPDOWN3_H
#define STEPDOWN3_H

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
 * @addtogroup stepdown3 Step Down 3 Click Driver
 * @brief API for configuring and manipulating Step Down 3 Click driver.
 * @{
 */

/**
 * @defgroup stepdown3_set Step Down 3 Settings
 * @brief Settings of Step Down 3 Click driver.
 */

/**
 * @addtogroup stepdown3_set
 * @{
 */

/**
 * @brief Step Down 3 output voltage selection.
 * @details Specified output voltage selection of Step Down 3 Click driver.
 */
#define STEPDOWN3_OUT_VOLTAGE_1V6       0x00
#define STEPDOWN3_OUT_VOLTAGE_1V8       0x01
#define STEPDOWN3_OUT_VOLTAGE_2V1       0x02
#define STEPDOWN3_OUT_VOLTAGE_2V5       0x03
#define STEPDOWN3_OUT_VOLTAGE_2V7       0x04
#define STEPDOWN3_OUT_VOLTAGE_2V8       0x05
#define STEPDOWN3_OUT_VOLTAGE_3V0       0x06
#define STEPDOWN3_OUT_VOLTAGE_3V3       0x07

/*! @} */ // stepdown3_set

/**
 * @defgroup stepdown3_map Step Down 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Step Down 3 Click driver.
 */

/**
 * @addtogroup stepdown3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Step Down 3 Click to the selected MikroBUS.
 */
#define STEPDOWN3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.d2 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.aux = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.d1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.d0 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepdown3_map
/*! @} */ // stepdown3

/**
 * @brief Step Down 3 Click context object.
 * @details Context object definition of Step Down 3 Click driver.
 */
typedef struct
{
    digital_out_t  d2;      /**< Output voltage selection D2 pin. */
    digital_out_t  en;      /**< Enable device pin (Active High). */
    digital_out_t  aux;     /**< Enable auxilary output pin (Active High). */
    digital_out_t  d1;      /**< Output voltage selection D1 pin. */
    digital_out_t  d0;      /**< Output voltage selection D0 pin. */

} stepdown3_t;

/**
 * @brief Step Down 3 Click configuration object.
 * @details Configuration object definition of Step Down 3 Click driver.
 */
typedef struct
{
    pin_name_t  d2;         /**< Output voltage selection D2 pin. */
    pin_name_t  en;         /**< Enable device pin (Active High). */
    pin_name_t  aux;        /**< Enable auxilary output pin (Active High). */
    pin_name_t  d1;         /**< Output voltage selection D1 pin. */
    pin_name_t  d0;         /**< Output voltage selection D0 pin. */

} stepdown3_cfg_t;

/**
 * @brief Step Down 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPDOWN3_OK = 0,
    STEPDOWN3_ERROR = -1

} stepdown3_return_value_t;

/*!
 * @addtogroup stepdown3 Step Down 3 Click Driver
 * @brief API for configuring and manipulating Step Down 3 Click driver.
 * @{
 */

/**
 * @brief Step Down 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepdown3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepdown3_cfg_setup ( stepdown3_cfg_t *cfg );

/**
 * @brief Step Down 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepdown3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepdown3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepdown3_init ( stepdown3_t *ctx, stepdown3_cfg_t *cfg );

/**
 * @brief Step Down 3 enable device function.
 * @details This function enables the device by setting the EN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown3_enable_device ( stepdown3_t *ctx );

/**
 * @brief Step Down 3 disable device function.
 * @details This function disables the device by setting the EN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown3_disable_device ( stepdown3_t *ctx );

/**
 * @brief Step Down 3 enable aux output function.
 * @details This function enables the auxiliary output (VOUT_AUX) by setting the AUX pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown3_enable_aux_output ( stepdown3_t *ctx );

/**
 * @brief Step Down 3 disable aux output function.
 * @details This function disables the auxiliary output (VOUT_AUX) by setting the AUX pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #stepdown3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepdown3_disable_aux_output ( stepdown3_t *ctx );

/**
 * @brief Step Down 3 set output voltage function.
 * @details This function sets the output voltage by setting the D2, D1, and D0 pins to a desired state.
 * @param[in] ctx : Click context object.
 * See #stepdown3_t object definition for detailed explanation.
 * @param[in] vout : Voltage output @li @c 0 - 1.6 V,
 *                                  @li @c 1 - 1.8 V,
 *                                  @li @c 2 - 2.1 V,
 *                                  @li @c 3 - 2.5 V,
 *                                  @li @c 4 - 2.7 V,
 *                                  @li @c 5 - 2.8 V,
 *                                  @li @c 6 - 3.0 V,
 *                                  @li @c 7 - 3.3 V.
 * @return None.
 * @note None.
 */
void stepdown3_set_output_voltage ( stepdown3_t *ctx, uint8_t vout );

#ifdef __cplusplus
}
#endif
#endif // STEPDOWN3_H

/*! @} */ // stepdown3

// ------------------------------------------------------------------------ END
