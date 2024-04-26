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
 * @file micrfrx.h
 * @brief This file contains API for MICRF RX Click Driver.
 */

#ifndef MICRFRX_H
#define MICRFRX_H

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
 * @addtogroup micrfrx MICRF RX Click Driver
 * @brief API for configuring and manipulating MICRF RX Click driver.
 * @{
 */

/**
 * @defgroup micrfrx_cfg MICRF RX Settings
 * @brief Settings for configuration of MICRF RX Click driver.
 */

/**
 * @addtogroup micrfrx_cfg
 * @{
 */

/**
 * @brief MICRF RX default settings.
 * @details Specified setting of MICRF RX Click driver.
 */
#define MICRFRX_RSSI_VREF_3V3       3.3f
#define MICRFRX_RSSI_MIN_DBM      ( -110 )
#define MICRFRX_RSSI_MAX_DBM      ( -50 )
#define MICRFRX_RSSI_RANGE_DBM    ( MICRFRX_RSSI_MAX_DBM - MICRFRX_RSSI_MIN_DBM )
#define MICRFRX_RSSI_MIN_V          0.5f
#define MICRFRX_RSSI_MAX_V          2.0f
#define MICRFRX_RSSI_RANGE_V      ( MICRFRX_RSSI_MAX_V - MICRFRX_RSSI_MIN_V )
#define MICRFRX_RSSI_DBM_PER_V    ( MICRFRX_RSSI_RANGE_DBM / MICRFRX_RSSI_MAX_V )
#define MICRFRX_RSSI_V_TO_DBM(x)  ( MICRFRX_RSSI_MIN_DBM + ( ( x - MICRFRX_RSSI_MIN_V ) * MICRFRX_RSSI_DBM_PER_V ) )
#define MICRFRX_MAN_BIT_LEN_US      2000
#define MICRFRX_MAX_DATA_LEN        255

/*! @} */ // micrfrx_cfg

/**
 * @defgroup micrfrx_map MICRF RX MikroBUS Map
 * @brief MikroBUS pin mapping of MICRF RX Click driver.
 */

/**
 * @addtogroup micrfrx_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MICRF RX Click to the selected MikroBUS.
 */
#define MICRFRX_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rssi = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.shd = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sqc = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.dout = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // micrfrx_map
/*! @} */ // micrfrx

/**
 * @brief MICRF RX Click context object.
 * @details Context object definition of MICRF RX Click driver.
 */
typedef struct
{
    digital_out_t shd;      /**< Shutdown pin (Active high). */
    digital_out_t sqc;      /**< Squelch control pin (Active low). */

    digital_in_t dout;      /**< Data output pin. */

    analog_in_t adc;        /**< ADC module object. */

} micrfrx_t;

/**
 * @brief MICRF RX Click configuration object.
 * @details Configuration object definition of MICRF RX Click driver.
 */
typedef struct
{
    pin_name_t rssi;        /**< RSSI analog pin. */
    pin_name_t shd;         /**< Shutdown pin (Active high). */
    pin_name_t sqc;         /**< Squelch control pin (Active low). */
    pin_name_t dout;        /**< Data output pin. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} micrfrx_cfg_t;

/**
 * @brief MICRF RX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MICRFRX_OK = 0,
    MICRFRX_ERROR = -1

} micrfrx_return_value_t;

/*!
 * @addtogroup micrfrx MICRF RX Click Driver
 * @brief API for configuring and manipulating MICRF RX Click driver.
 * @{
 */

/**
 * @brief MICRF RX configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #micrfrx_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void micrfrx_cfg_setup ( micrfrx_cfg_t *cfg );

/**
 * @brief MICRF RX initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #micrfrx_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #micrfrx_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t micrfrx_init ( micrfrx_t *ctx, micrfrx_cfg_t *cfg );

/**
 * @brief MICRF RX enable squelch function.
 * @details This function enables squelch by setting the SQC pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #micrfrx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrfrx_enable_squelch ( micrfrx_t *ctx );

/**
 * @brief MICRF RX disable squelch function.
 * @details This function disables squelch by setting the SQC pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #micrfrx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrfrx_disable_squelch ( micrfrx_t *ctx );

/**
 * @brief MICRF RX enable device function.
 * @details This function enables device by setting the SHD pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #micrfrx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrfrx_enable_device ( micrfrx_t *ctx );

/**
 * @brief MICRF RX disable device function.
 * @details This function disables device by setting the SHD pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #micrfrx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrfrx_disable_device ( micrfrx_t *ctx );

/**
 * @brief MICRF RX get data pin function.
 * @details This function returns the DOUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #micrfrx_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t micrfrx_get_data_pin ( micrfrx_t *ctx );

/**
 * @brief MICRF RX read RSSI pin voltage level function.
 * @details This function reads results of AD conversion of the RSSI pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #micrfrx_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t micrfrx_read_rssi_voltage ( micrfrx_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // MICRFRX_H

/*! @} */ // micrfrx

// ------------------------------------------------------------------------ END
