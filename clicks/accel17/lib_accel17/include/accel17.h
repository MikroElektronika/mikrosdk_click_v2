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
 * @file accel17.h
 * @brief This file contains API for Accel 17 Click Driver.
 */

#ifndef ACCEL17_H
#define ACCEL17_H

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
 * @addtogroup accel17 Accel 17 Click Driver
 * @brief API for configuring and manipulating Accel 17 Click driver.
 * @{
 */

/**
 * @defgroup accel17_reg Accel 17 Registers List
 * @brief List of registers of Accel 17 Click driver.
 */

/**
 * @addtogroup accel17_reg
 * @{
 */

/**
 * @brief Accel 17 description register.
 * @details Specified register for description of Accel 17 Click driver.
 */
#define ACCEL17_REG_ACCEL_CONFIG    0x00
#define ACCEL17_REG_ACCEL_X_MSB     0x01
#define ACCEL17_REG_ACCEL_X_LSB     0x02
#define ACCEL17_REG_ACCEL_Y_MSB     0x03
#define ACCEL17_REG_ACCEL_Y_LSB     0x04

/*! @} */ // accel17_reg

/**
 * @defgroup accel17_set Accel 17 Registers Settings
 * @brief Settings for registers of Accel 17 Click driver.
 */

/**
 * @addtogroup accel17_set
 * @{
 */

/**
 * @brief Accel 17 description setting.
 * @details Specified setting for description of Accel 17 Click driver.
 */
#define ACCEL17_TOEN_MASK           0x08      // Temperature Out Status
#define ACCEL17_TOEN_DISABLE        0x00      // Temperature Out Disable
#define ACCEL17_TOEN_ENABLE         0x08      // Temperature Out Enable
#define ACCEL17_BGTST_MASK          0x04      // BandGap Test Status
#define ACCEL17_BGTST_NORMAL        0x00      // Normal Test
#define ACCEL17_BGTST_BANDGAP       0x04      // Bandga Test
#define ACCEL17_ST_MASK             0x02      // Self Test Status
#define ACCEL17_ST_OFF              0x00      // Self Test Off
#define ACCEL17_ST_ON               0x02      // Self Test On
#define ACCEL17_PD_MASK             0x01      // Power Status
#define ACCEL17_PD_ON               0x00      // Power On
#define ACCEL17_PD_DOWN             0x01      // Power Down

/**
 * @brief Accel 17 calculation macros.
 * @details Specified marcros for calculation of Accel 17 Click driver.
 */
#define ACCEL17_OFFSET              2048
#define ACCEL17_SENSITIVITY         512.0
#define ACCEL17_DEGREE_RES          90

/**
 * @brief Accel 17 device address setting.
 * @details Specified setting for device slave address selection of
 * Accel 17 Click driver.
 */
#define ACCEL17_SET_DEV_ADDR        0x10

/*! @} */ // accel17_set

/**
 * @defgroup accel17_map Accel 17 MikroBUS Map
 * @brief MikroBUS pin mapping of Accel 17 Click driver.
 */

/**
 * @addtogroup accel17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Accel 17 Click to the selected MikroBUS.
 */
#define ACCEL17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // accel17_map
/*! @} */ // accel17

/**
 * @brief Accel 17 Click context object.
 * @details Context object definition of Accel 17 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} accel17_t;

/**
 * @brief Accel 17 Click configuration object.
 * @details Configuration object definition of Accel 17 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} accel17_cfg_t;

/**
 * @brief Accel 17 Click axes data.
 * @details Axes data object definition of Accel 17 Click driver.
 */
typedef struct
{
   float x; /**< X axis. */
   float y; /**< Y axis. */

} accel17_axes_t;

/**
 * @brief Accel 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   ACCEL17_OK = 0,
   ACCEL17_ERROR = -1

} accel17_return_value_t;

/*!
 * @addtogroup accel17 Accel 17 Click Driver
 * @brief API for configuring and manipulating Accel 17 Click driver.
 * @{
 */

/**
 * @brief Accel 17 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #accel17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void accel17_cfg_setup ( accel17_cfg_t *cfg );

/**
 * @brief Accel 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #accel17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #accel17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t accel17_init ( accel17_t *ctx, accel17_cfg_t *cfg );

/**
 * @brief Accel 17 default configuration function.
 * @details This function executes a default configuration of Accel 17
 * Click board.
 * @param[in] ctx : Click context object.
 * See #accel17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t accel17_default_cfg ( accel17_t *ctx );

/**
 * @brief Accel 17 I2C writing function.
 * @details This function writes a byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #accel17_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] tx_data : Data to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t accel17_generic_write ( accel17_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Accel 17 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #accel17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t accel17_generic_read ( accel17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Accel data reading.
 * @details This function reads a accel data and calculates it with 
 * resolution set in @b ctx object. Data will be set in @b axes object.
 * @param[in] ctx : Click context object.
 * See #accel17_t object definition for detailed explanation.
 * @param[out] axes : Axes data object.
 * See #accel17_axes_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t accel17_get_axes_data ( accel17_t *ctx, accel17_axes_t *axes );

#ifdef __cplusplus
}
#endif
#endif // ACCEL17_H

/*! @} */ // accel17

// ------------------------------------------------------------------------ END
