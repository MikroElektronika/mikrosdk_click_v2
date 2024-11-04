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
 * @file profet15a.h
 * @brief This file contains API for PROFET 15A Click Driver.
 */

#ifndef PROFET15A_H
#define PROFET15A_H

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
 * @addtogroup profet15a PROFET 15A Click Driver
 * @brief API for configuring and manipulating PROFET 15A Click driver.
 * @{
 */

/**
 * @defgroup profet15a_set PROFET 15A Registers Settings
 * @brief Settings for registers of PROFET 15A Click driver.
 */

/**
 * @addtogroup profet15a_set
 * @{
 */

/**
 * @brief PROFET 15A description setting.
 * @details Specified setting for description of PROFET 15A Click driver.
 */
#define PROFET15A_MODE_ON          1
#define PROFET15A_MODE_OFF         2
#define PROFET15A_DIAGNOSTIC_ON    3
#define PROFET15A_DIAGNOSTIC_OFF   4
#define PROFET15A_FAULT            5

/*! @} */ // profet15a_set

/**
 * @defgroup profet15a_map PROFET 15A MikroBUS Map
 * @brief MikroBUS pin mapping of PROFET 15A Click driver.
 */

/**
 * @addtogroup profet15a_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PROFET 15A Click to the selected MikroBUS.
 */
#define PROFET15A_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.den = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.in = MIKROBUS( mikrobus, MIKROBUS_PWM ); 

/*! @} */ // profet15a_map
/*! @} */ // profet15a

/**
 * @brief PROFET 15A Click context object.
 * @details Context object definition of PROFET 15A Click driver.
 */
typedef struct
{
    digital_out_t  den; /**< Diagnostic enable. */
    digital_out_t  in;  /**< Output enable. */

    analog_in_t  adc;   /**< ADC module object. */
    
    uint8_t mode;       /**< Device mode. */
    uint16_t rsens;     /**< SENSE resistor. */
    uint16_t kilis;     /**< Current Sense. */
    float offset;     /**< Current Sense. */

} profet15a_t;

/**
 * @brief PROFET 15A Click configuration object.
 * @details Configuration object definition of PROFET 15A Click driver.
 */
typedef struct
{
    pin_name_t  an;     /**< Analog pin descriptor. */
    pin_name_t  den;    /**< Diagnostic enable. */
    pin_name_t  in;     /**< Output enable. */

    analog_in_resolution_t  resolution; /**< ADC resolution. */
    float                   vref;       /**< ADC reference voltage. */

} profet15a_cfg_t;

/**
 * @brief PROFET 15A Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   PROFET15A_OK = 0,
   PROFET15A_ERROR = -1

} profet15a_return_value_t;

/*!
 * @addtogroup profet15a PROFET 15A Click Driver
 * @brief API for configuring and manipulating PROFET 15A Click driver.
 * @{
 */

/**
 * @brief PROFET 15A configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #profet15a_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void profet15a_cfg_setup ( profet15a_cfg_t *cfg );

/**
 * @brief PROFET 15A initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #profet15a_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #profet15a_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t profet15a_init ( profet15a_t *ctx, profet15a_cfg_t *cfg );

/**
 * @brief PROFET 15A read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #profet15a_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t profet15a_read_an_pin_value ( profet15a_t *ctx, uint16_t *data_out );

/**
 * @brief PROFET 15A read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #profet15a_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t profet15a_read_an_pin_voltage ( profet15a_t *ctx, float *data_out );

/**
 * @brief PROFET 15A set mode.
 * @details This function sets DEN and IN pins state to set device in selected mode.
 * @param[in] ctx : Click context object.
 * See #profet15a_t object definition for detailed explanation.
 * @param[in] mode : Mode to set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t profet15a_set_mode ( profet15a_t *ctx, uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif // PROFET15A_H

/*! @} */ // profet15a

// ------------------------------------------------------------------------ END
