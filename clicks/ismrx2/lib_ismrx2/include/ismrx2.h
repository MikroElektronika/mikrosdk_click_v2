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
 * @file ismrx2.h
 * @brief This file contains API for ISM RX 2 Click Driver.
 */

#ifndef ISMRX2_H
#define ISMRX2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup ismrx2 ISM RX 2 Click Driver
 * @brief API for configuring and manipulating ISM RX 2 Click driver.
 * @{
 */
/**
 * @addtogroup ismrx2_set
 * @{
 */

/**
 * @brief ISM RX 2 description setting.
 * @details Specified setting for description of ISM RX 2 Click driver.
 */
#define ISMRX2_PIN_STATE_HIGH                   1
#define ISMRX2_PIN_STATE_LOW                    0
#define ISMRX2_DEFAULT_SYNC_BYTE                0xCE35
#define ISMRX2_FSK_DEFAULT_SYNC_BYTE            0xFF


/*! @} */ // ismrx2_set

/**
 * @defgroup ismrx2_map ISM RX 2 MikroBUS Map
 * @brief MikroBUS pin mapping of ISM RX 2 Click driver.
 */

/**
 * @addtogroup ismrx2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of ISM RX 2 Click to the selected MikroBUS.
 */
#define ISMRX2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.mst = MIKROBUS( mikrobus, MIKROBUS_INT ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX )

/*! @} */ // ismrx2_map
/*! @} */ // ismrx2

/**
 * @brief ISM RX 2 Click context object.
 * @details Context object definition of ISM RX 2 Click driver.
 */
typedef struct
{
    digital_out_t rst;      /**< Reset pin. */
    digital_out_t stb;      /**< Operating Mode Selector. */

    digital_in_t rx_pin;    /**< Data pin. */
    digital_in_t mst;       /**< Operating Mode Indicator. */
    
} ismrx2_t;

/**
 * @brief ISM RX 2 Click configuration object.
 * @details Configuration object definition of ISM RX 2 Click driver.
 */
typedef struct
{
    pin_name_t rst;     /**< Reset pin. */
    pin_name_t stb;     /**< Operating Mode Selector. */
    pin_name_t rx_pin;  /**< Data pin. */
    pin_name_t mst;     /**< Operating Mode Indicator. */

} ismrx2_cfg_t;

/**
 * @brief ISM RX 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    ISMRX2_OK = 0,
    ISMRX2_ERROR = -1

} ismrx2_return_value_t;

/*!
 * @addtogroup ismrx2 ISM RX 2 Click Driver
 * @brief API for configuring and manipulating ISM RX 2 Click driver.
 * @{
 */

/**
 * @brief ISM RX 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ismrx2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ismrx2_cfg_setup ( ismrx2_cfg_t *cfg );

/**
 * @brief ISM RX 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ismrx2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ismrx2_init ( ismrx2_t *ctx, ismrx2_cfg_t *cfg );

/**
 * @brief ISM RX 2 default configuration function.
 * @details This function executes a default configuration of ISM RX 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ismrx2_default_cfg ( ismrx2_t *ctx );

/**
 * @brief ISM RX 2 set state of RST pin function.
 * @details This function sets state of the RST pin.
 * @param[in] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @param[in] state : Desired state of the pin.
 * @return Nothing.
 * @note None.
 */
void ismrx2_set_rst_pin_state ( ismrx2_t *ctx, uint8_t state );

/**
 * @brief ISM RX 2 set state of STB pin function.
 * @details This function sets state of the STB pin.
 * @param[in] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @param[in] state : Desired state of the pin.
 * @return Nothing.
 * @note None.
 */
void ismrx2_set_stb_pin_state ( ismrx2_t *ctx, uint8_t state );

/**
 * @brief ISM RX 2 get state of MST pin function.
 * @details This function get state of the MST pin.
 * @param[in] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @return State of the MST pin.
 * @note None.
 */
uint8_t ismrx2_get_mst_pin_state ( ismrx2_t *ctx );

/**
 * @brief ISM RX 2 get state of DATA pin function.
 * @details This function get state of the DATA pin.
 * @param[in] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @return State of the DATA pin.
 * @note None.
 */
uint8_t ismrx2_get_data_pin_state ( ismrx2_t *ctx );

/**
 * @brief ISM RX 2 read manchester encoded data function.
 * @details This function read manchester encoded data.
 * @param[in] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @param[out] data_out : Read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ismrx2_read_manchester_data ( ismrx2_t *ctx, uint8_t *data_out );

/**
 * @brief ISM RX 2 read data function.
 * @details This function read data.
 * @param[in] ctx : Click context object.
 * See #ismrx2_t object definition for detailed explanation.
 * @param[out] data_out : Read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ismrx2_read_rf_data ( ismrx2_t *ctx, uint8_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // ISMRX2_H

/*! @} */ // ismrx2

// ------------------------------------------------------------------------ END
