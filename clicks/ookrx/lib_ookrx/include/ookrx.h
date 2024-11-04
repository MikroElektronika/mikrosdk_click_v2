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
 * @file ookrx.h
 * @brief This file contains API for OOK RX Click Driver.
 */

#ifndef OOKRX_H
#define OOKRX_H

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
 * @addtogroup ookrx OOK RX Click Driver
 * @brief API for configuring and manipulating OOK RX Click driver.
 * @{
 */

/**
 * @defgroup ookrx_cfg OOK RX Settings
 * @brief Settings for configuration of OOK RX Click driver.
 */

/**
 * @addtogroup ookrx_cfg
 * @{
 */

/**
 * @brief OOK RX default settings.
 * @details Specified setting of OOK RX Click driver.
 */
#define OOKRX_RSSI_VREF_3V3       3.3f
#define OOKRX_RSSI_MIN_DBM      ( -110 )
#define OOKRX_RSSI_MAX_DBM      ( -50 )
#define OOKRX_RSSI_RANGE_DBM    ( OOKRX_RSSI_MAX_DBM - OOKRX_RSSI_MIN_DBM )
#define OOKRX_RSSI_MIN_V          0.4f
#define OOKRX_RSSI_MAX_V          2.06f
#define OOKRX_RSSI_RANGE_V      ( OOKRX_RSSI_MAX_V - OOKRX_RSSI_MIN_V )
#define OOKRX_RSSI_DBM_PER_V    ( OOKRX_RSSI_RANGE_DBM / OOKRX_RSSI_MAX_V )
#define OOKRX_RSSI_V_TO_DBM(x)  ( OOKRX_RSSI_MIN_DBM + ( ( x - OOKRX_RSSI_MIN_V ) * OOKRX_RSSI_DBM_PER_V ) )
#define OOKRX_MAN_BIT_LEN_US      2000
#define OOKRX_MAX_DATA_LEN        255

/*! @} */ // ookrx_cfg

/**
 * @defgroup ookrx_map OOK RX MikroBUS Map
 * @brief MikroBUS pin mapping of OOK RX Click driver.
 */

/**
 * @addtogroup ookrx_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of OOK RX Click to the selected MikroBUS.
 */
#define OOKRX_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rssi = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.sqc = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dout = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ookrx_map
/*! @} */ // ookrx

/**
 * @brief OOK RX Click context object.
 * @details Context object definition of OOK RX Click driver.
 */
typedef struct
{
    digital_out_t en;       /**< Enable pin (Active high). */
    digital_out_t sqc;      /**< Squelch control pin (Active low). */

    digital_in_t dout;      /**< Data output pin. */

    analog_in_t adc;        /**< ADC module object. */

} ookrx_t;

/**
 * @brief OOK RX Click configuration object.
 * @details Configuration object definition of OOK RX Click driver.
 */
typedef struct
{
    pin_name_t rssi;        /**< RSSI analog pin. */
    pin_name_t en;          /**< Enable pin (Active high). */
    pin_name_t sqc;         /**< Squelch control pin (Active low). */
    pin_name_t dout;        /**< Data output pin. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} ookrx_cfg_t;

/**
 * @brief OOK RX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    OOKRX_OK = 0,
    OOKRX_ERROR = -1

} ookrx_return_value_t;

/*!
 * @addtogroup ookrx OOK RX Click Driver
 * @brief API for configuring and manipulating OOK RX Click driver.
 * @{
 */

/**
 * @brief OOK RX configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ookrx_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ookrx_cfg_setup ( ookrx_cfg_t *cfg );

/**
 * @brief OOK RX initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ookrx_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ookrx_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ookrx_init ( ookrx_t *ctx, ookrx_cfg_t *cfg );

/**
 * @brief OOK RX enable squelch function.
 * @details This function enables squelch by setting the SQC pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ookrx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ookrx_enable_squelch ( ookrx_t *ctx );

/**
 * @brief OOK RX disable squelch function.
 * @details This function disables squelch by setting the SQC pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ookrx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ookrx_disable_squelch ( ookrx_t *ctx );

/**
 * @brief OOK RX enable device function.
 * @details This function enables device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #ookrx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ookrx_enable_device ( ookrx_t *ctx );

/**
 * @brief OOK RX disable device function.
 * @details This function disables device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #ookrx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void ookrx_disable_device ( ookrx_t *ctx );

/**
 * @brief OOK RX get data pin function.
 * @details This function returns the DOUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #ookrx_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t ookrx_get_data_pin ( ookrx_t *ctx );

/**
 * @brief OOK RX read RSSI pin voltage level function.
 * @details This function reads results of AD conversion of the RSSI pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #ookrx_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t ookrx_read_rssi_voltage ( ookrx_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // OOKRX_H

/*! @} */ // ookrx

// ------------------------------------------------------------------------ END
