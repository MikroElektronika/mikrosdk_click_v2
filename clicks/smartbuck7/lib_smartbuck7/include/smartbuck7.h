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
 * @file smartbuck7.h
 * @brief This file contains API for Smart Buck 7 Click Driver.
 */

#ifndef SMARTBUCK7_H
#define SMARTBUCK7_H

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
 * @addtogroup smartbuck7 Smart Buck 7 Click Driver
 * @brief API for configuring and manipulating Smart Buck 7 Click driver.
 * @{
 */

/**
 * @defgroup smartbuck7_reg Smart Buck 7 Registers List
 * @brief List of registers of Smart Buck 7 Click driver.
 */

/**
 * @addtogroup smartbuck7_reg
 * @{
 */

/**
 * @brief Smart Buck 7 register list.
 * @details Specified register list of Smart Buck 7 Click driver.
 */
#define SMARTBUCK7_REG_SLAVE_ADDRESS            0x15
#define SMARTBUCK7_REG_EN                       0x22
#define SMARTBUCK7_REG_STATUS_1                 0x27
#define SMARTBUCK7_REG_STATUS_2                 0x28

/*! @} */ // smartbuck7_reg

/**
 * @defgroup smartbuck7_set Smart Buck 7 Registers Settings
 * @brief Settings for registers of Smart Buck 7 Click driver.
 */

/**
 * @addtogroup smartbuck7_set
 * @{
 */

/**
 * @brief Smart Buck 7 buck selection setting.
 * @details Specified setting for buck selection of Smart Buck 7 Click driver.
 */
#define SMARTBUCK7_BUCK_4                       0x01
#define SMARTBUCK7_BUCK_3                       0x02
#define SMARTBUCK7_BUCK_2                       0x04
#define SMARTBUCK7_BUCK_1                       0x08
#define SMARTBUCK7_BUCK_ALL                     0x0F

/**
 * @brief Smart Buck 7 STATUS_1 register setting.
 * @details Specified setting for STATUS_1 register of Smart Buck 7 Click driver.
 */
#define SMARTBUCK7_STATUS_1_PGBUCK4             0x08
#define SMARTBUCK7_STATUS_1_PGBUCK3             0x04
#define SMARTBUCK7_STATUS_1_PGBUCK2             0x02
#define SMARTBUCK7_STATUS_1_PGBUCK1             0x01

/**
 * @brief Smart Buck 7 STATUS_2 register setting.
 * @details Specified setting for STATUS_2 register of Smart Buck 7 Click driver.
 */
#define SMARTBUCK7_STATUS_2_OTWARNING           0x80
#define SMARTBUCK7_STATUS_2_OTEMPP              0x40
#define SMARTBUCK7_STATUS_2_CLEAR               0xFF

/**
 * @brief Smart Buck 7 device address setting.
 * @details Specified setting for device slave address selection of
 * Smart Buck 7 Click driver.
 */
#define SMARTBUCK7_DEVICE_ADDRESS               0x69

/*! @} */ // smartbuck7_set

/**
 * @defgroup smartbuck7_map Smart Buck 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Smart Buck 7 Click driver.
 */

/**
 * @addtogroup smartbuck7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Smart Buck 7 Click to the selected MikroBUS.
 */
#define SMARTBUCK7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // smartbuck7_map
/*! @} */ // smartbuck7

/**
 * @brief Smart Buck 7 Click status object.
 * @details Status object definition of Smart Buck 7 Click driver.
 */
typedef struct
{
    uint8_t status_1;           /**< Status 1 register. */
    uint8_t status_2;           /**< Status 2 register. */

} smartbuck7_status_t;

/**
 * @brief Smart Buck 7 Click context object.
 * @details Context object definition of Smart Buck 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t on;           /**< Output enable pin (active low). */

    // Input pins
    digital_in_t pg;            /**< Power Good signal pin (active high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} smartbuck7_t;

/**
 * @brief Smart Buck 7 Click configuration object.
 * @details Configuration object definition of Smart Buck 7 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t on;              /**< Output enable pin (active low). */
    pin_name_t pg;              /**< Power Good signal pin (active high). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} smartbuck7_cfg_t;

/**
 * @brief Smart Buck 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SMARTBUCK7_OK = 0,
    SMARTBUCK7_ERROR = -1

} smartbuck7_return_value_t;

/*!
 * @addtogroup smartbuck7 Smart Buck 7 Click Driver
 * @brief API for configuring and manipulating Smart Buck 7 Click driver.
 * @{
 */

/**
 * @brief Smart Buck 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #smartbuck7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void smartbuck7_cfg_setup ( smartbuck7_cfg_t *cfg );

/**
 * @brief Smart Buck 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #smartbuck7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #smartbuck7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t smartbuck7_init ( smartbuck7_t *ctx, smartbuck7_cfg_t *cfg );

/**
 * @brief Smart Buck 7 default configuration function.
 * @details This function executes a default configuration of Smart Buck 7
 * Click board.
 * @param[in] ctx : Click context object.
 * See #smartbuck7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t smartbuck7_default_cfg ( smartbuck7_t *ctx );

/**
 * @brief Smart Buck 7 write register function.
 * @details This function writes a single byte of data to the specified register address.
 * @param[in] ctx : Click context object.
 * See #smartbuck7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck7_write_reg ( smartbuck7_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Smart Buck 7 read register function.
 * @details This function reads a single byte of data from the specified register address.
 * @param[in] ctx : Click context object.
 * See #smartbuck7_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to memory where read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck7_read_reg ( smartbuck7_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Smart Buck 7 enable device function.
 * @details This function sets the ON pin to logic low state to enable the device.
 * @param[in] ctx : Click context object.
 * See #smartbuck7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartbuck7_enable_device ( smartbuck7_t *ctx );

/**
 * @brief Smart Buck 7 disable device function.
 * @details This function sets the ON pin to logic high state to disable the device.
 * @param[in] ctx : Click context object.
 * See #smartbuck7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void smartbuck7_disable_device ( smartbuck7_t *ctx );

/**
 * @brief Smart Buck 7 get power-good pin function.
 * @details This function reads the logic level of the PG pin.
 * @param[in] ctx : Click context object.
 * See #smartbuck7_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t smartbuck7_get_pg_pin ( smartbuck7_t *ctx );

/**
 * @brief Smart Buck 7 read status registers function.
 * @details This function reads the STATUS_1 and STATUS_2 registers and stores them in the status structure.
 * @param[in] ctx : Click context object.
 * See #smartbuck7_t object definition for detailed explanation.
 * @param[out] status : Pointer to status structure.
 * See #smartbuck7_status_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck7_read_status ( smartbuck7_t *ctx, smartbuck7_status_t *status );

/**
 * @brief Smart Buck 7 clear status flags function.
 * @details This function clears the STATUS_2 register flags.
 * @param[in] ctx : Click context object.
 * See #smartbuck7_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck7_clear_status ( smartbuck7_t *ctx );

/**
 * @brief Smart Buck 7 enable selected buck function.
 * @details This function enables one or more buck regulators by setting their control bits.
 * @param[in] ctx : Click context object.
 * See #smartbuck7_t object definition for detailed explanation.
 * @param[in] buck_sel : Buck regulator selection mask (e.g. SMARTBUCK7_BUCK_1, BUCK_2, BUCK_3, BUCK_4, BUCK_ALL).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck7_enable_buck ( smartbuck7_t *ctx, uint8_t buck_sel );

/**
 * @brief Smart Buck 7 disable selected buck function.
 * @details This function disables one or more buck regulators by clearing their control bits.
 * @param[in] ctx : Click context object.
 * See #smartbuck7_t object definition for detailed explanation.
 * @param[in] buck_sel : Buck regulator selection mask (e.g. SMARTBUCK7_BUCK_1, BUCK_2, BUCK_3, BUCK_4, BUCK_ALL).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t smartbuck7_disable_buck ( smartbuck7_t *ctx, uint8_t buck_sel );

#ifdef __cplusplus
}
#endif
#endif // SMARTBUCK7_H

/*! @} */ // smartbuck7

// ------------------------------------------------------------------------ END
