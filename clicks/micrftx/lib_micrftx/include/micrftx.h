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
 * @file micrftx.h
 * @brief This file contains API for MICRF TX Click Driver.
 */

#ifndef MICRFTX_H
#define MICRFTX_H

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
 * @addtogroup micrftx MICRF TX Click Driver
 * @brief API for configuring and manipulating MICRF TX Click driver.
 * @{
 */

/**
 * @defgroup micrftx_cfg MICRF TX Settings
 * @brief Settings for configuration of MICRF TX Click driver.
 */

/**
 * @addtogroup micrftx_cfg
 * @{
 */

/**
 * @brief MICRF TX default training bytes, manchester settings, and data length.
 * @details Specified setting for default training bytes, manchester settings, 
 * and data length of MICRF TX Click driver.
 */
#define MICRFTX_TRAINING_BYTES      { 0xAA, 0xAA, 0xAA, 0xAA }
#define MICRFTX_MAN_MSB             0x8000
#define MICRFTX_MAN_BIT_LEN_US      2000
#define MICRFTX_MAX_DATA_LEN        255

/*! @} */ // micrftx_cfg

/**
 * @defgroup micrftx_map MICRF TX MikroBUS Map
 * @brief MikroBUS pin mapping of MICRF TX Click driver.
 */

/**
 * @addtogroup micrftx_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MICRF TX Click to the selected MikroBUS.
 */
#define MICRFTX_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.din = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // micrftx_map
/*! @} */ // micrftx

/**
 * @brief MICRF TX Click context object.
 * @details Context object definition of MICRF TX Click driver.
 */
typedef struct
{
    digital_out_t en;       /**< Enable pin (Active high). */
    digital_out_t din;      /**< Data pin. */

    digital_in_t clk;       /**< Clock input pin. */

} micrftx_t;

/**
 * @brief MICRF TX Click configuration object.
 * @details Configuration object definition of MICRF TX Click driver.
 */
typedef struct
{
    pin_name_t en;          /**< Enable pin (Active high). */
    pin_name_t din;         /**< Data pin. */
    pin_name_t clk;         /**< Clock input pin. */

} micrftx_cfg_t;

/**
 * @brief MICRF TX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    MICRFTX_OK = 0,
    MICRFTX_ERROR = -1

} micrftx_return_value_t;

/*!
 * @addtogroup micrftx MICRF TX Click Driver
 * @brief API for configuring and manipulating MICRF TX Click driver.
 * @{
 */

/**
 * @brief MICRF TX configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #micrftx_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void micrftx_cfg_setup ( micrftx_cfg_t *cfg );

/**
 * @brief MICRF TX initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #micrftx_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #micrftx_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t micrftx_init ( micrftx_t *ctx, micrftx_cfg_t *cfg );

/**
 * @brief MICRF TX set data pin function.
 * @details This function sets the data pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #micrftx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrftx_set_data_pin ( micrftx_t *ctx );

/**
 * @brief MICRF TX clear data pin function.
 * @details This function clears the data pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #micrftx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrftx_clear_data_pin ( micrftx_t *ctx );

/**
 * @brief MICRF TX enable device function.
 * @details This function enables device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #micrftx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrftx_enable_device ( micrftx_t *ctx );

/**
 * @brief MICRF TX disable device function.
 * @details This function disables device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #micrftx_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void micrftx_disable_device ( micrftx_t *ctx );

/**
 * @brief MICRF TX get clock pin function.
 * @details This function returns the clock pin logic state.
 * @param[in] ctx : Click context object.
 * See #micrftx_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t micrftx_get_clock_pin ( micrftx_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // MICRFTX_H

/*! @} */ // micrftx

// ------------------------------------------------------------------------ END
