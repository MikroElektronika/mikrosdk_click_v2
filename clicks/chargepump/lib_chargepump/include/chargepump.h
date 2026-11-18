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
 * @file chargepump.h
 * @brief This file contains API for Charge Pump Click Driver.
 */

#ifndef CHARGEPUMP_H
#define CHARGEPUMP_H

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
 * @addtogroup chargepump Charge Pump Click Driver
 * @brief API for configuring and manipulating Charge Pump Click driver.
 * @{
 */

/**
 * @defgroup chargepump_set Charge Pump Settings
 * @brief Settings of Charge Pump Click driver.
 */

/**
 * @addtogroup chargepump_set
 * @{
 */

/**
 * @brief Charge Pump fault pin state setting.
 * @details Specified setting for fault pin state of Charge Pump Click driver.
 */
#define CHARGEPUMP_FAULT_ACTIVE             0
#define CHARGEPUMP_FAULT_INACTIVE           1

/**
 * @brief Charge Pump timeout setting.
 * @details Specified setting for timeout of Charge Pump Click driver.
 */
#define CHARGEPUMP_TIMEOUT_MS               500

/*! @} */ // chargepump_set

/**
 * @defgroup chargepump_map Charge Pump MikroBUS Map
 * @brief MikroBUS pin mapping of Charge Pump Click driver.
 */

/**
 * @addtogroup chargepump_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charge Pump Click to the selected MikroBUS.
 */
#define CHARGEPUMP_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.run = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.md  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // chargepump_map
/*! @} */ // chargepump

/**
 * @brief Charge Pump Click context object.
 * @details Context object definition of Charge Pump Click driver.
 */
typedef struct
{
    digital_out_t run;      /**< RUN pin, device shutdown control (active high). */
    digital_out_t md;       /**< MODE pin, switching control (active high). */

    digital_in_t flt;       /**< FAULT indication pin (active low). */

} chargepump_t;

/**
 * @brief Charge Pump Click configuration object.
 * @details Configuration object definition of Charge Pump Click driver.
 */
typedef struct
{
    pin_name_t run;         /**< RUN pin descriptor. */
    pin_name_t md;          /**< MODE pin descriptor. */
    pin_name_t flt;         /**< FAULT pin descriptor. */

} chargepump_cfg_t;

/**
 * @brief Charge Pump Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CHARGEPUMP_OK = 0,
    CHARGEPUMP_ERROR = -1

} chargepump_return_value_t;

/*!
 * @addtogroup chargepump Charge Pump Click Driver
 * @brief API for configuring and manipulating Charge Pump Click driver.
 * @{
 */

/**
 * @brief Charge Pump configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #chargepump_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void chargepump_cfg_setup ( chargepump_cfg_t *cfg );

/**
 * @brief Charge Pump initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #chargepump_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #chargepump_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t chargepump_init ( chargepump_t *ctx, chargepump_cfg_t *cfg );

/**
 * @brief Charge Pump enable device function.
 * @details This function wakes the device from shutdown mode.
 * @param[out] ctx : Click context object.
 * See #chargepump_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void chargepump_enable_device ( chargepump_t *ctx );

/**
 * @brief Charge Pump disable device function.
 * @details This function puts the device into shutdown mode.
 * @param[out] ctx : Click context object.
 * See #chargepump_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void chargepump_disable_device ( chargepump_t *ctx );

/**
 * @brief Charge Pump enable switching function.
 * @details This function enables switching capacitors.
 * @param[out] ctx : Click context object.
 * See #chargepump_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void chargepump_enable_switching ( chargepump_t *ctx );

/**
 * @brief Charge Pump disable switching function.
 * @details This function disables switching capacitors.
 * @param[out] ctx : Click context object.
 * See #chargepump_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void chargepump_disable_switching ( chargepump_t *ctx );

/**
 * @brief Charge Pump get FLT pin function.
 * @details This function returns the FLT pin logic state.
 * @param[in] ctx : Click context object.
 * See #chargepump_t object definition for detailed explanation.
 * @return FLT pin logic state.
 * @note None.
 */
uint8_t chargepump_get_flt_pin ( chargepump_t *ctx );

/**
 * @brief Charge Pump wait output ready function.
 * @details This function waits for the FLT pin to be released.
 * @param[in] ctx : Click context object.
 * See #chargepump_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t chargepump_wait_output_ready ( chargepump_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CHARGEPUMP_H

/*! @} */ // chargepump

// ------------------------------------------------------------------------ END
