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
 * @file digipot11.h
 * @brief This file contains API for DIGI POT 11 Click Driver.
 */

#ifndef DIGIPOT11_H
#define DIGIPOT11_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup digipot11 DIGI POT 11 Click Driver
 * @brief API for configuring and manipulating DIGI POT 11 Click driver.
 * @{
 */

/**
 * @addtogroup digipot11_set
 * @{
 */

/**
 * @brief DIGI POT 11 wiper selection setting.
 * @details Specified setting for wiper selection of DIGI POT 11 Click driver.
 */
#define DIGIPOT11_WIPER_SEL_A                   0x11
#define DIGIPOT11_WIPER_SEL_B                   0x12
#define DIGIPOT11_WIPER_SEL_BOTH                0x13

/**
 * @brief DIGI POT 11 Wiper setting.
 * @details Specified setting for wiper of DIGI POT 11 Click driver.
 */
#define DIGIPOT11_WIPER_FULL_SCALE              0xFF
#define DIGIPOT11_WIPER_MID_SCALE               0x80
#define DIGIPOT11_WIPER_ZERO_SCALE              0x00

/**
 * @brief DIGI POT 11 device address setting.
 * @details Specified setting for device slave address selection of
 * DIGI POT 11 Click driver.
 */
#define DIGIPOT11_U1_DEVICE_ADDRESS_A1A0_00     0x2C
#define DIGIPOT11_U1_DEVICE_ADDRESS_A1A0_01     0x2D
#define DIGIPOT11_U1_DEVICE_ADDRESS_A1A0_10     0x2E
#define DIGIPOT11_U1_DEVICE_ADDRESS_A1A0_11     0x2F
#define DIGIPOT11_U2_DEVICE_ADDRESS_A1A0_00     0x28
#define DIGIPOT11_U2_DEVICE_ADDRESS_A1A0_01     0x29
#define DIGIPOT11_U2_DEVICE_ADDRESS_A1A0_10     0x2A
#define DIGIPOT11_U2_DEVICE_ADDRESS_A1A0_11     0x2B

/*! @} */ // digipot11_set

/**
 * @defgroup digipot11_map DIGI POT 11 MikroBUS Map
 * @brief MikroBUS pin mapping of DIGI POT 11 Click driver.
 */

/**
 * @addtogroup digipot11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DIGI POT 11 Click to the selected MikroBUS.
 */
#define DIGIPOT11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // digipot11_map
/*! @} */ // digipot11

/**
 * @brief DIGI POT 11 Click context object.
 * @details Context object definition of DIGI POT 11 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t u1_slave_address;       /**< U1 device slave address (used for I2C driver). */
    uint8_t u2_slave_address;       /**< U2 device slave address (used for I2C driver). */

} digipot11_t;

/**
 * @brief DIGI POT 11 Click configuration object.
 * @details Configuration object definition of DIGI POT 11 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address_u1;      /**< I2C slave address U1. */
    uint8_t    i2c_address_u2;      /**< I2C slave address U2. */

} digipot11_cfg_t;

/**
 * @brief DIGI POT 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DIGIPOT11_OK = 0,
    DIGIPOT11_ERROR = -1

} digipot11_return_value_t;

/*!
 * @addtogroup digipot11 DIGI POT 11 Click Driver
 * @brief API for configuring and manipulating DIGI POT 11 Click driver.
 * @{
 */

/**
 * @brief DIGI POT 11 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #digipot11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void digipot11_cfg_setup ( digipot11_cfg_t *cfg );

/**
 * @brief DIGI POT 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #digipot11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #digipot11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot11_init ( digipot11_t *ctx, digipot11_cfg_t *cfg );

/**
 * @brief DIGI POT 11 set u1 wiper function.
 * @details This function sets the position of the selected wiper of U1 device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot11_t object definition for detailed explanation.
 * @param[in] wiper_sel : Wiper selector: @li @c DIGIPOT11_WIPER_SEL_A,
 *                                        @li @c DIGIPOT11_WIPER_SEL_B.
 *                                        @li @c DIGIPOT11_WIPER_SEL_BOTH.
 * @param[in] data_in : Wiper position to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot11_set_u1_wiper ( digipot11_t *ctx, uint8_t wiper_sel, uint8_t data_in );

/**
 * @brief DIGI POT 11 set u2 wiper function.
 * @details This function sets the position of the selected wiper of U2 device by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #digipot11_t object definition for detailed explanation.
 * @param[in] wiper_sel : Wiper selector: @li @c DIGIPOT11_WIPER_SEL_A,
 *                                        @li @c DIGIPOT11_WIPER_SEL_B.
 *                                        @li @c DIGIPOT11_WIPER_SEL_BOTH.
 * @param[in] data_in : Wiper position to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t digipot11_set_u2_wiper ( digipot11_t *ctx, uint8_t wiper_sel, uint8_t data_in );

#ifdef __cplusplus
}
#endif
#endif // DIGIPOT11_H

/*! @} */ // digipot11

// ------------------------------------------------------------------------ END
