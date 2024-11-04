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
 * @file charger19.h
 * @brief This file contains API for Charger 19 Click Driver.
 */

#ifndef CHARGER19_H
#define CHARGER19_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup charger19 Charger 19 Click Driver
 * @brief API for configuring and manipulating Charger 19 Click driver.
 * @{
 */

/**
 * @defgroup charger19_set Charger 19 Registers Settings
 * @brief Settings for registers of Charger 19 Click driver.
 */

/**
 * @addtogroup charger19_set
 * @{
 */

/**
 * @brief Charger 19 description setting.
 * @details Specified setting for description of Charger 19 Click driver.
 */
#define CHARGER19_VOUT_1V8          0x00
#define CHARGER19_VOUT_2V1          0x01
#define CHARGER19_VOUT_2V7          0x02
#define CHARGER19_VOUT_3V0          0x03

/**
 * @brief Charger 19 ship mode setting.
 * @details Specified setting for ship mode of Charger 19 Click driver.
 */
#define CHARGER19_SHIP_MODE_ON      0x01
#define CHARGER19_SHIP_MODE_OFF     0x00

/*! @} */ // charger19_set

/**
 * @defgroup charger19_map Charger 19 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 19 Click driver.
 */

/**
 * @addtogroup charger19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 19 Click to the selected MikroBUS.
 */
#define CHARGER19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sac = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.vs1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.vs2 = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger19_map
/*! @} */ // charger19

/**
 * @brief Charger 19 Click context object.
 * @details Context object definition of Charger 19 Click driver.
 */
typedef struct
{
    digital_out_t sac;              /**< Enables Ship mode pin. */
    digital_out_t vs1;              /**< VOUTB voltage configuration pin 1. */
    digital_out_t vs2;              /**< VOUTB voltage configuration pin 2. */

    analog_in_t adc;                /**< ADC module object. */

} charger19_t;

/**
 * @brief Charger 19 Click configuration object.
 * @details Configuration object definition of Charger 19 Click driver.
 */
typedef struct
{
    pin_name_t an;                      /**< Analog pin descriptor. */
    pin_name_t sac;                     /**< Enables Ship mode pin. */
    pin_name_t vs1;                     /**< VOUTB voltage configuration pin 1. */
    pin_name_t vs2;                     /**< VOUTB voltage configuration pin 2. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} charger19_cfg_t;

/**
 * @brief Charger 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGER19_OK = 0,
    CHARGER19_ERROR = -1

} charger19_return_value_t;

/*!
 * @addtogroup charger19 Charger 19 Click Driver
 * @brief API for configuring and manipulating Charger 19 Click driver.
 * @{
 */

/**
 * @brief Charger 19 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger19_cfg_setup ( charger19_cfg_t *cfg );

/**
 * @brief Charger 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #charger19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger19_init ( charger19_t *ctx, charger19_cfg_t *cfg );

/**
 * @brief Charger 19 default configuration function.
 * @details This function executes a default configuration of Charger 19
 * Click board.
 * @param[in] ctx : Click context object.
 * See #charger19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t charger19_default_cfg ( charger19_t *ctx );

/**
 * @brief Charger 19 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #charger19_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger19_read_an_pin_value ( charger19_t *ctx, uint16_t *data_out );

/**
 * @brief Charger 19 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #charger19_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t charger19_read_an_pin_voltage ( charger19_t *ctx, float *data_out );

/**
 * @brief Charger 19 set output voltage function.
 * @details This function is used to set voltage output.
 * @param[in] ctx : Click context object.
 * See #charger19_t object definition for detailed explanation.
 * @param[in] vout_sel : Output voltage selection.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can be used only when Vsys is not existing.
 */
err_t charger19_set_vout ( charger19_t *ctx, uint8_t vout_sel );

/**
 * @brief Charger 19 set Ship mode function.
 * @details This function is used to enable ship mode.
 * @param[in] ctx : Click context object.
 * See #charger19_t object definition for detailed explanation.
 * @param[in] ship_sel : Ship mode selection.
 * @return Nothing.
 * @note None.
 */
void charger19_set_ship_mode ( charger19_t *ctx, uint8_t ship_sel );

/**
 * @brief Charger 19 get battery voltage function.
 * @details This function is used to get battery voltage.
 * @param[in] ctx : Click context object.
 * See #charger19_t object definition for detailed explanation.
 * @param[out] vbat : Battery voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger19_get_vbat ( charger19_t *ctx, float *vbat );

#ifdef __cplusplus
}
#endif
#endif // CHARGER19_H

/*! @} */ // charger19

// ------------------------------------------------------------------------ END
