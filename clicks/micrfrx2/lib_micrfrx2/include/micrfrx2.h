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
 * @file micrfrx2.h
 * @brief This file contains API for MICRF RX 2 Click Driver.
 */

#ifndef MICRFRX2_H
#define MICRFRX2_H

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
 * @addtogroup micrfrx2 MICRF RX 2 Click Driver
 * @brief API for configuring and manipulating MICRF RX 2 Click driver.
 * @{
 */

/**
 * @defgroup micrfrx2_cfg MICRF RX 2 Settings
 * @brief Settings for configuration of MICRF RX 2 Click driver.
 */

/**
 * @addtogroup micrfrx2_cfg
 * @{
 */

/**
 * @brief MICRF RX 2 default settings.
 * @details Specified setting of MICRF RX 2 Click driver.
 */
#define MICRFRX2_RSSI_VREF_3V3      3.3f
#define MICRFRX2_RSSI_MIN_DBM     ( -110 )
#define MICRFRX2_RSSI_MAX_DBM     ( -50 )
#define MICRFRX2_RSSI_RANGE_DBM   ( MICRFRX2_RSSI_MAX_DBM - MICRFRX2_RSSI_MIN_DBM )
#define MICRFRX2_RSSI_MIN_V         0.5f
#define MICRFRX2_RSSI_MAX_V         2.0f
#define MICRFRX2_RSSI_RANGE_V     ( MICRFRX2_RSSI_MAX_V - MICRFRX2_RSSI_MIN_V )
#define MICRFRX2_RSSI_DBM_PER_V   ( MICRFRX2_RSSI_RANGE_DBM / MICRFRX2_RSSI_MAX_V )
#define MICRFRX2_RSSI_V_TO_DBM(x) ( MICRFRX2_RSSI_MIN_DBM + ( ( x - MICRFRX2_RSSI_MIN_V ) * MICRFRX2_RSSI_DBM_PER_V ) )
#define MICRFRX2_MAN_BIT_LEN_US     2000
#define MICRFRX2_MAX_DATA_LEN       255

/*! @} */ // micrfrx2_cfg

/**
 * @defgroup micrfrx2_map MICRF RX 2 MikroBUS Map
 * @brief MikroBUS pin mapping of MICRF RX 2 Click driver.
 */

/**
 * @addtogroup micrfrx2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MICRF RX 2 Click to the selected MikroBUS.
 */
#define MICRFRX2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rssi = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.shd = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.dout = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // micrfrx2_map
/*! @} */ // micrfrx2

/**
 * @brief MICRF RX 2 Click context object.
 * @details Context object definition of MICRF RX 2 Click driver.
 */
typedef struct
{
    digital_out_t shd;      /**< Shutdown pin (Active high). */
    digital_out_t clk;      /**< Programming clock pin. */

    digital_in_t dout;      /**< Data output pin. */

    analog_in_t adc;        /**< ADC module object. */

} micrfrx2_t;

/**
 * @brief MICRF RX 2 Click configuration object.
 * @details Configuration object definition of MICRF RX 2 Click driver.
 */
typedef struct
{
    pin_name_t rssi;        /**< RSSI analog pin. */
    pin_name_t shd;         /**< Shutdown pin (Active high). */
    pin_name_t clk;         /**< Programming clock pin. */
    pin_name_t dout;        /**< Data output pin. */

    analog_in_resolution_t resolution;  /**< ADC resolution. */
    float                  vref;        /**< ADC reference voltage. */

} micrfrx2_cfg_t;

/**
 * @brief MICRF RX 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MICRFRX2_OK = 0,
    MICRFRX2_ERROR = -1

} micrfrx2_return_value_t;

/*!
 * @addtogroup micrfrx2 MICRF RX 2 Click Driver
 * @brief API for configuring and manipulating MICRF RX 2 Click driver.
 * @{
 */

/**
 * @brief MICRF RX 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #micrfrx2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void micrfrx2_cfg_setup ( micrfrx2_cfg_t *cfg );

/**
 * @brief MICRF RX 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #micrfrx2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #micrfrx2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t micrfrx2_init ( micrfrx2_t *ctx, micrfrx2_cfg_t *cfg );

/**
 * @brief MICRF RX 2 set clock pin function.
 * @details This function sets clock pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #micrfrx2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrfrx2_set_clock_pin ( micrfrx2_t *ctx );

/**
 * @brief MICRF RX 2 clear clock pin function.
 * @details This function clears clock pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #micrfrx2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrfrx2_clear_clock_pin ( micrfrx2_t *ctx );

/**
 * @brief MICRF RX 2 enable device function.
 * @details This function enables device by setting the SHD pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #micrfrx2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrfrx2_enable_device ( micrfrx2_t *ctx );

/**
 * @brief MICRF RX 2 disable device function.
 * @details This function disables device by setting the SHD pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #micrfrx2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrfrx2_disable_device ( micrfrx2_t *ctx );

/**
 * @brief MICRF RX 2 get data pin function.
 * @details This function returns the DOUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #micrfrx2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t micrfrx2_get_data_pin ( micrfrx2_t *ctx );

/**
 * @brief MICRF RX 2 read RSSI pin voltage level function.
 * @details This function reads results of AD conversion of the RSSI pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #micrfrx2_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t micrfrx2_read_rssi_voltage ( micrfrx2_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // MICRFRX2_H

/*! @} */ // micrfrx2

// ------------------------------------------------------------------------ END
